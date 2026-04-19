#include "ConfigInstance.h"






ConfigInstance::ConfigInstance(const std::filesystem::path& filePath)
    : FileInstance(filePath)
{
}




template <typename T>
struct IsSupportedConfigType
{
    /* Keep this in sync with ConfigInstance::Value (std::variant<...>). */
    static constexpr bool Value = std::is_same_v<T, bool>
                                  || std::is_same_v<T, int>
                                  || std::is_same_v<T, float>
                                  || std::is_same_v<T, SDK::FVector>
                                  || std::is_same_v<T, std::string>;
};




bool ConfigInstance::Load()
{
    _values.clear();

    std::vector<std::string> lines;
    if (LoadLines(&lines) == false) // I/O error (file missing, access denied, etc.).
        return false;

    for (const std::string& rawLine : lines)
    {
        const std::string line = Trim(rawLine);
        if (IsLineCommentOrEmpty(line) == true) // Skip blank lines and full-line comments
            continue;

        const std::optional<std::pair<std::string, std::string>> KeyValue = SplitKeyValue(line);
        if (KeyValue.has_value() == false) // Skip malformed lines (no "=").
            continue;

        const std::string key = Trim(KeyValue->first);
        if (key.empty() == true) // Skip entries with empty keys.
            continue;

        const std::string rawValue = Trim(KeyValue->second);
        const std::optional<Value> value = ParseValueWithOptionalType(rawValue);
        if (value.has_value() == false) // Skip entries with invalid typed values.
            continue;

        if (_values.find(key) == _values.end())
        {
            _keysOrder.push_back(key);
        }

        _values[key] = *value; // Last occurrence of entry (key) wins.
    }

    return true;
}

bool ConfigInstance::Save()
{
    std::vector<std::string> lines;
    lines.reserve(_values.size());

    /* Serialize in "key = type:value" form following the original insertion order. */
    for (const std::string& key : _keysOrder)
    {
        lines.push_back(Value_ToLine(key, _values[key]));
    }

    return SaveLines(lines);
}




template <typename T>
std::optional<T> ConfigInstance::Get(const std::string& key)
{
    static_assert(IsSupportedConfigType<T>::Value == true, "Unsupported config type.");

    const auto value = _values.find(key);
    if (value == _values.end()) // Key not found.
        return std::nullopt;

    /* Fast path: exact type match in the variant. */
    if (std::holds_alternative<T>(value->second) == true)
        return std::get<T>(value->second);

    /* Backward/forward compatibility: allow reading typed values from stored strings. */
    if (std::holds_alternative<std::string>(value->second) == true)
    {
        const std::string& text = std::get<std::string>(value->second);

        if constexpr (std::is_same_v<T, bool>)
            return TryParseBool(text);

        if constexpr (std::is_same_v<T, int>)
            return TryParseInt(text);

        if constexpr (std::is_same_v<T, float>)
            return TryParseFloat(text);

        if constexpr (std::is_same_v<T, SDK::FVector>)
            return TryParseFVector(text);

        if constexpr (std::is_same_v<T, std::string>)
            return text;
    }

    return std::nullopt;
}

template <typename T>
void ConfigInstance::Set(const std::string& key, const T& value)
{
    static_assert(IsSupportedConfigType<T>::Value == true, "Unsupported config type.");

    if (key.empty() == true) // Ignore invalid key.
        return;

    if (_values.find(key) == _values.end())
        _keysOrder.push_back(key);

    _values[key] = value;
}
void ConfigInstance::Set(const std::string& key, const char* value)
{
    if (key.empty() == true || value == nullptr) // Ignore invalid key/value.
        return;

    if (_values.find(key) == _values.end())
        _keysOrder.push_back(key);

    _values[key] = std::string(value);
}
void ConfigInstance::Set(const std::string& key, const SDK::FVector& value)
{
    if (key.empty() == true) // Ignore invalid key.
        return;

    if (_values.find(key) == _values.end())
        _keysOrder.push_back(key);

    _values[key] = value;
}




bool ConfigInstance::HasKey(const std::string& key)
{
    return _values.find(key) != _values.end();
}

void ConfigInstance::Remove(const std::string& key)
{
    if (_values.find(key) != _values.end())
    {
        _values.erase(key);
        _keysOrder.erase(std::remove(_keysOrder.begin(), _keysOrder.end(), key), _keysOrder.end());
    }
}

void ConfigInstance::Clear()
{
    _values.clear();
    _keysOrder.clear();
}




std::string ConfigInstance::Trim(const std::string& text)
{
    /* ASCII whitespace trimming; safe cast to unsigned char for std::isspace. */
    size_t start = 0;
    size_t end = text.size();

    while (start < end && std::isspace(static_cast<unsigned char>(text[start])) != 0)
        ++start;

    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0)
        --end;

    return text.substr(start, end - start);
}

bool ConfigInstance::IsLineCommentOrEmpty(const std::string& line)
{
    if (line.empty() == true) // Empty line.
        return true;

    if (line.rfind("#", 0) == 0) // Shell-style comment.
        return true;

    if (line.rfind(";", 0) == 0) // INI-style comment.
        return true;

    if (line.rfind("//", 0) == 0) // C++-style comment.
        return true;

    return false;
}




bool ConfigInstance::ReadFloat(const std::string& text, const size_t& inPos, size_t* outPos, float* outValue)
{
    if (outPos == nullptr || outValue == nullptr)
        return false;

    /* Skip separators between numbers: spaces/tabs/commas. */
    size_t position = inPos;
    while (position < text.size() && (text[position] == ' ' || text[position] == '\t' || text[position] == ','))
        ++position;

    if (position >= text.size())
        return false;

    const char* begin = text.data() + position;
    const char* end = text.data() + text.size();

    /* from_chars is locale-independent and does not allocate. */
    float value = 0.0f;
    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value, std::chars_format::general);
    if (fromCharsResult.ec != std::errc())
        return false;

    *outPos = static_cast<size_t>(fromCharsResult.ptr - text.data());
    *outValue = value;

    return true;
}




std::optional<std::pair<std::string, std::string>> ConfigInstance::SplitKeyValue(const std::string& line)
{
    const size_t pos = line.find('=');
    if (pos == std::string::npos) // No key/value delimiter.
        return std::nullopt;

    const std::string left = line.substr(0, pos);
    const std::string right = line.substr(pos + 1);

    return std::make_pair(left, right);
}

std::optional<ConfigInstance::Value> ConfigInstance::ParseValueWithOptionalType(const std::string& rawValue)
{
    /* If no "type:" prefix is present, keep it as a string. */
    const size_t colonPos = rawValue.find(':');

    if (colonPos == std::string::npos)
        return Value(rawValue);

    const std::string typePart = String_ToLower(Trim(rawValue.substr(0, colonPos)));
    const std::string valuePart = Trim(rawValue.substr(colonPos + 1));

    if (typePart == "bool")
    {
        const std::optional<bool> value = TryParseBool(valuePart);
        if (value.has_value() == false) // Invalid bool token.
            return std::nullopt;

        return Value(*value);
    }

    if (typePart == "int")
    {
        const std::optional<int> value = TryParseInt(valuePart);
        if (value.has_value() == false) // Invalid integer token.
            return std::nullopt;

        return Value(*value);
    }

    if (typePart == "float")
    {
        const std::optional<float> value = TryParseFloat(valuePart);
        if (value.has_value() == false) // Invalid float token.
            return std::nullopt;

        return Value(*value);
    }

    if (typePart == "fvector")
    {
        const std::optional<SDK::FVector> value = TryParseFVector(valuePart);
        if (value.has_value() == false) // Invalid vector token.
            return std::nullopt;

        return Value(*value);
    }

    if (typePart == "string")
        return Value(valuePart);

    /* Unknown type token -> treat everything as string. */
    return Value(rawValue);
}




std::string ConfigInstance::String_ToLower(const std::string& text)
{
    std::string outText = text;
    for (char& c : outText)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

    return outText;
}

std::string ConfigInstance::Float_ToString(const float& value)
{
    /* Use fixed precision to avoid excessive digits while keeping round-trip reasonable. */
    std::ostringstream stringStream = {};
    stringStream << std::setprecision(9) << value;

    return stringStream.str();
}

std::string ConfigInstance::Value_ToLine(const std::string& key, const Value& value)
{
    /* Always write explicit type tags to preserve original types on reload. */
    if (std::holds_alternative<bool>(value) == true)
        return key + " = bool:" + (std::get<bool>(value) ? "true" : "false");

    if (std::holds_alternative<int>(value) == true)
        return key + " = int:" + std::to_string(std::get<int>(value));

    if (std::holds_alternative<float>(value) == true)
        return key + " = float:" + Float_ToString(std::get<float>(value));

    if (std::holds_alternative<SDK::FVector>(value) == true)
    {
        const SDK::FVector& fVector = std::get<SDK::FVector>(value);

        /* Vector format: "X Y Z" (spaces). */
        std::ostringstream stringStream;
        stringStream << key << " = fvector:"
            << std::setprecision(9) << fVector.X << " "
            << std::setprecision(9) << fVector.Y << " "
            << std::setprecision(9) << fVector.Z;

        return stringStream.str();
    }

    return key + " = " + std::get<std::string>(value);
}




std::optional<bool> ConfigInstance::TryParseBool(const std::string& text)
{
    const std::string v = String_ToLower(Trim(text));

    if (v == "true" || v == "1")
        return true;

    if (v == "false" || v == "0")
        return false;

    return std::nullopt;
}

std::optional<int> ConfigInstance::TryParseInt(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty() == true)
        return std::nullopt;

    int value = 0;

    const char* begin = token.data();
    const char* end = token.data() + token.size();

    /* Require full consumption (no trailing garbage). */
    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value);
    if (fromCharsResult.ec != std::errc() || fromCharsResult.ptr != end) // Parse failed or extra characters.
        return std::nullopt;

    return value;
}

std::optional<float> ConfigInstance::TryParseFloat(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty() == true) // Missing token.
        return std::nullopt;

    float value = 0.0f;

    const char* begin = token.data();
    const char* end = token.data() + token.size();

    /* Require full consumption (no trailing garbage). */
    std::from_chars_result fromCharsResult = std::from_chars(begin, end, value, std::chars_format::general);
    if (fromCharsResult.ec != std::errc() || fromCharsResult.ptr != end) // Parse failed or extra characters.
        return std::nullopt;

    return value;
}

std::optional<SDK::FVector> ConfigInstance::TryParseFVector(const std::string& text)
{
    const std::string token = Trim(text);
    if (token.empty() == true) // Missing token.
        return std::nullopt;

    size_t pos = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (ReadFloat(token, pos, &pos, &x) == false)
        return std::nullopt;

    if (ReadFloat(token, pos, &pos, &y) == false)
        return std::nullopt;

    if (ReadFloat(token, pos, &pos, &z) == false)
        return std::nullopt;

    SDK::FVector fVector;
    fVector.X = x;
    fVector.Y = y;
    fVector.Z = z;

    return fVector;
}




/* Explicit instantiations to keep all template logic in .cpp */
template std::optional<bool> ConfigInstance::Get<bool>(const std::string& key);
template std::optional<int> ConfigInstance::Get<int>(const std::string& key);
template std::optional<float> ConfigInstance::Get<float>(const std::string& key);
template std::optional<SDK::FVector> ConfigInstance::Get<SDK::FVector>(const std::string& key);
template std::optional<std::string> ConfigInstance::Get<std::string>(const std::string& key);

template void ConfigInstance::Set<bool>(const std::string& key, const bool& value);
template void ConfigInstance::Set<int>(const std::string& key, const int& value);
template void ConfigInstance::Set<float>(const std::string& key, const float& value);
template void ConfigInstance::Set<SDK::FVector>(const std::string& key, const SDK::FVector& value);
template void ConfigInstance::Set<std::string>(const std::string& key, const std::string& value);