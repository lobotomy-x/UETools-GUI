#include "FileInstance.h"






FileInstance::FileInstance(const std::string& filePath)
{
    _filePath = Utilities::String::ToWString(filePath);
}

FileInstance::FileInstance(const std::wstring& filePath)
    : _filePath(filePath)
{
}




const bool FileInstance::Exists()
{
    if (_filePath.empty()) // Check if path is invalid.
    {
        return false;
    }

    return Utilities::File::Exists(_filePath);
}


const bool FileInstance::ReadText(std::string* outText)
{
    if (outText == nullptr) // Check if output pointer is invalid.
    {
        return false;
    }

    if (Exists() == false) // Check if file doesn't exist before reading.
    {
        return false;
    }

    *outText = Utilities::File::ReadTextASCII(_filePath);
    return true;
}

const bool FileInstance::SaveText(const std::string& text)
{
    if (EnsureDirectoryExists() == false) // Check if parent directory couldn't be created.
    {
        return false;
    }

    return Utilities::File::WriteTextASCII(_filePath, text);
}


const bool FileInstance::ReadLines(std::vector<std::string>* outLines)
{
    if (outLines == nullptr) // Check if output pointer is invalid.
    {
        return false;
    }

    if (Exists() == false) // Check if file doesn't exist before reading.
    {
        return false;
    }

    *outLines = Utilities::File::ReadLinesASCII(_filePath);
    return true;
}

const bool FileInstance::SaveLines(const std::vector<std::string>& lines)
{
    if (EnsureDirectoryExists() == false) // Check if parent directory couldn't be created.
    {
        return false;
    }

    return Utilities::File::WriteLinesASCII(_filePath, lines);
}


const bool FileInstance::AppendLine(const std::string& line)
{
    if (EnsureDirectoryExists() == false) // Check if parent directory couldn't be created.
    {
        return false;
    }

    return Utilities::File::AppendLineASCII(_filePath, line);
}

const bool FileInstance::AppendLines(const std::vector<std::string>& lines)
{
    if (EnsureDirectoryExists() == false) // Check if parent directory couldn't be created.
    {
        return false;
    }

    return Utilities::File::AppendLinesASCII(_filePath, lines);
}


const bool FileInstance::Clear()
{
    if (Exists() == false) // Check if file exists before clearing.
    {
        return false;
    }

    // Writing an empty string with CREATE_ALWAYS flag effectively clears the file.
    return Utilities::File::WriteText(_filePath, std::wstring());
}

const bool FileInstance::Destroy()
{
    if (Exists() == false) // Check if file already doesn't exist.
    {
        return true;
    }

    if (Utilities::File::Destroy(_filePath) == false) // Check if file deletion failed.
    {
        return false;
    }

    return true;
}


const std::wstring FileInstance::GetAbsolutePath()
{
    return std::filesystem::absolute(_filePath).wstring();
}

const bool FileInstance::EnsureDirectoryExists()
{
    std::filesystem::path path(_filePath);
    std::filesystem::path parentPath = path.parent_path();

    if (parentPath.empty()) // Check if no parent directory is specified (use current working directory).
    {
        return true;
    }

    std::error_code errorCode;
    if (std::filesystem::exists(parentPath, errorCode)) // Check if directory already exists.
    {
        return true;
    }

    return std::filesystem::create_directories(parentPath, errorCode);
}