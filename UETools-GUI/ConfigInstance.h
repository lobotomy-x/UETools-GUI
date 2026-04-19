#pragma once
#include "FileInstance.h"
#include "SDK\Engine_classes.hpp"

#include <unordered_map>
#include <optional>
#include <variant>
#include <iomanip>
#include <charconv>
#include <cctype>






class ConfigInstance : public FileInstance
{
public:
	explicit ConfigInstance(const std::filesystem::path& filePath);

    bool Load();
    bool Save();

    template <typename T>
    std::optional<T> Get(const std::string& key);

    template <typename T>
    void Set(const std::string& key, const T& value);
    void Set(const std::string& key, const char* value);
    void Set(const std::string& key, const SDK::FVector& value);

    bool HasKey(const std::string& key);
    void Remove(const std::string& key);
    void Clear();


private:
    using Value = std::variant<bool, int, float, SDK::FVector, std::string>;
    std::unordered_map<std::string, Value> _values;
    std::vector<std::string> _keysOrder;

    static std::string Trim(const std::string& text);
    static bool IsLineCommentOrEmpty(const std::string& line);

    static bool ReadFloat(const std::string& text, const size_t& inPos, size_t* outPos, float* outValue);

    static std::optional<std::pair<std::string, std::string>> SplitKeyValue(const std::string& line);
    static std::optional<Value> ParseValueWithOptionalType(const std::string& rawValue);

    static std::string String_ToLower(const std::string& text);
    static std::string Float_ToString(const float& value);
    static std::string Value_ToLine(const std::string& key, const Value& value);

    static std::optional<bool> TryParseBool(const std::string& text);
    static std::optional<int> TryParseInt(const std::string& text);
    static std::optional<float> TryParseFloat(const std::string& text);
    static std::optional<SDK::FVector> TryParseFVector(const std::string& text);
};

