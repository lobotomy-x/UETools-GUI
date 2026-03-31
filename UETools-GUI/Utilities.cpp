#include "Utilities.h"






std::string Utilities::Clipboard::GetClipboardText()
{
    if (OpenClipboard(nullptr))
    {
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData)
        {
            char* pData = static_cast<char*>(GlobalLock(hData));
            if (pData)
            {
                std::string text(pData);
                GlobalUnlock(hData);

                CloseClipboard();
                return text;
            }

            GlobalUnlock(hData);
        }

        CloseClipboard();
    }

    return std::string();
}

bool Utilities::Clipboard::SetClipboardText(const std::string& string)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        size_t textSize = string.size() + 1;

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (hGlobal)
        {
            void* pMem = GlobalLock(hGlobal);
            if (pMem)
            {
                std::memcpy(pMem, string.c_str(), textSize);
                GlobalUnlock(hGlobal);

                SetClipboardData(CF_TEXT, hGlobal);

                CloseClipboard();
                return true;
            }

            GlobalUnlock(hGlobal);
        }

        CloseClipboard();
    }

    return true;
}






std::string Utilities::String::ToString(const std::wstring& wideString)
{
	if (wideString.empty())
	{
		return std::string();
	}

	const wchar_t* wcString = wideString.c_str();
	return ToString(wcString);
}

std::string Utilities::String::ToString(const char* cString)
{
	if (cString == nullptr)
	{
		return std::string();
	}

	return std::string(cString);
}

std::string Utilities::String::ToString(const wchar_t* wcString)
{
	if (wcString == nullptr)
	{
		return std::string();
	}

	size_t convertedCount = 0;
	errno_t errorCode = wcstombs_s(&convertedCount, nullptr, 0, wcString, 0);

	if (errorCode != 0 || convertedCount == 0)
	{
		return std::string();
	}

	std::vector<char> buffer(convertedCount);
	errorCode = wcstombs_s(&convertedCount, buffer.data(), buffer.size(), wcString, _TRUNCATE);

	if (errorCode != 0)
	{
		return std::string();
	}

	/* Return string excluding the null terminator. */
	return std::string(buffer.data(), convertedCount - 1);
}


std::wstring Utilities::String::ToWString(const std::string& string)
{
	if (string.empty())
	{
		return std::wstring();
	}

	const char* cString = string.c_str();
	return ToWString(cString);
}

std::wstring Utilities::String::ToWString(const char* cString)
{
	if (cString == nullptr)
	{
		return std::wstring();
	}

	size_t convertedCount = 0;
	errno_t errorCode = mbstowcs_s(&convertedCount, nullptr, 0, cString, 0);

	if (errorCode != 0 || convertedCount == 0)
	{
		return std::wstring();
	}

	std::vector<wchar_t> buffer(convertedCount);
	errorCode = mbstowcs_s(&convertedCount, buffer.data(), buffer.size(), cString, _TRUNCATE);

	if (errorCode != 0)
	{
		return std::wstring();
	}

	/* Return wide string excluding the null terminator. */
	return std::wstring(buffer.data(), convertedCount - 1);
}

std::wstring Utilities::String::ToWString(const wchar_t* wcString)
{
	if (wcString == nullptr)
	{
		return std::wstring();
	}

	return std::wstring(wcString);
}




std::string Utilities::String::ToLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    return string;
}

std::wstring Utilities::String::ToLowerCase(std::wstring wString)
{
	std::transform(wString.begin(), wString.end(), wString.begin(), [](wchar_t c)
	{
		return std::towlower(c);
	});

	return wString;
}



std::string Utilities::String::ToUpperCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c)
    { 
        return std::toupper(c); 
    });

    return string;
}

std::wstring Utilities::String::ToUpperCase(std::wstring wString)
{
	std::transform(wString.begin(), wString.end(), wString.begin(), [](wchar_t c)
	{
		return std::towupper(c);
	});

	return wString;
}




std::string Utilities::String::Replace(std::string string, const std::string& from, const std::string& to)
{
	if (from.empty())
	{
		return string;
	}

	size_t start_pos = 0;
	while ((start_pos = string.find(from, start_pos)) != std::string::npos)
	{
		string.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}

	return string;
}

std::string Utilities::String::Replace(const std::string& string, const std::string& from, const std::wstring& to)
{
	return Replace(string, from, ToString(to));
}

std::string Utilities::String::Replace(const std::string& string, const std::wstring& from, const std::string& to)
{
	return Replace(string, ToString(from), to);
}

std::string Utilities::String::Replace(const std::string& string, const std::wstring& from, const std::wstring& to)
{
	return Replace(string, ToString(from), ToString(to));
}


std::wstring Utilities::String::Replace(std::wstring wString, const std::wstring& from, const std::wstring& to)
{
	if (from.empty())
	{
		return wString;
	}

	size_t start_pos = 0;
	while ((start_pos = wString.find(from, start_pos)) != std::wstring::npos)
	{
		wString.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}

	return wString;
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::wstring& from, const std::string& to)
{
	return Replace(wString, from, ToWString(to));
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::string& from, const std::wstring& to)
{
	return Replace(wString, ToWString(from), to);
}

std::wstring Utilities::String::Replace(const std::wstring& wString, const std::string& from, const std::string& to)
{
	return Replace(wString, ToWString(from), ToWString(to));
}




std::vector<std::string> Utilities::String::Split(const std::string& string, const char& separator, const bool& removeSeparatorSpaces)
{
	std::vector<std::string> outCollection;

	if (string.empty())
		return outCollection;

	size_t position = 0;
	while (true)
	{
		const size_t separatorPosition = string.find(separator, position);

		std::string token = (separatorPosition == std::string::npos)
			? string.substr(position)
			: string.substr(position, separatorPosition - position);

		if (removeSeparatorSpaces)
		{
			size_t first = 0;
			while (first < token.size() && std::isspace(token[first]))
				++first;

			size_t last = token.size();
			while (last > first && std::isspace(token[last - 1]))
				--last;

			token = token.substr(first, last - first);
		}

		if (token.empty() == false)
			outCollection.push_back(token);

		if (separatorPosition == std::string::npos)
			break;

		position = separatorPosition + 1;
	}

	return outCollection;
}

std::vector<std::string> Utilities::String::Split(const std::wstring& wString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(wString);
	return Split(string, separator, removeSeparatorSpaces);
}

std::vector<std::string> Utilities::String::Split(const char* cString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(cString);
	return Split(string, separator, removeSeparatorSpaces);
}

std::vector<std::string> Utilities::String::Split(const wchar_t* wcString, const char& separator, const bool& removeSeparatorSpaces)
{
	std::string string = ToString(wcString);
	return Split(string, separator, removeSeparatorSpaces);
}


std::vector<std::wstring> Utilities::String::Split(const std::string& string, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(string);
	return Split(wString, separator, removeSeparatorSpaces);
}

std::vector<std::wstring> Utilities::String::Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::vector<std::wstring> outCollection;

	if (wideString.empty())
		return outCollection;

	size_t position = 0;
	while (true)
	{
		const size_t separatorPosition = wideString.find(separator, position);

		std::wstring token = (separatorPosition == std::wstring::npos)
			? wideString.substr(position)
			: wideString.substr(position, separatorPosition - position);

		if (removeSeparatorSpaces)
		{
			size_t first = 0;
			while (first < token.size() && std::iswspace(token[first]))
				++first;

			size_t last = token.size();
			while (last > first && std::iswspace(token[last - 1]))
				--last;

			token = token.substr(first, last - first);
		}

		if (token.empty() == false)
			outCollection.push_back(token);

		if (separatorPosition == std::wstring::npos)
			break;

		position = separatorPosition + 1;
	}

	return outCollection;
}

std::vector<std::wstring> Utilities::String::Split(const char* cString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(cString);
	return Split(wString, separator, removeSeparatorSpaces);
}

std::vector<std::wstring> Utilities::String::Split(const wchar_t* wcString, const wchar_t& separator, const bool& removeSeparatorSpaces)
{
	std::wstring wString = ToWString(wcString);
	return Split(wString, separator, removeSeparatorSpaces);
}




std::wstring Utilities::String::NormalizeObjectPath(std::wstring objectPath)
{
	const std::wstring contentKey = L"/Content/";
	const std::wstring pluginsKey = L"/Plugins/";
	const std::wstring engineContentKey = L"Engine/Content/";
	const std::wstring engineContentMidKey = L"/Engine/Content/";

	if (objectPath.empty())
	{
		return objectPath;
	}

	static const std::vector<std::wstring> unrealFileExtensions = { L".uasset", L".umap", L".uexp", L".ubulk" };
	for (const std::wstring& fileExtension : unrealFileExtensions)
	{
		objectPath = String::Replace(objectPath, fileExtension, std::wstring());
	}
	objectPath = String::Replace(objectPath, "\\", "/");

	enum E_ObjectPathSuffixType
	{
		None,
		Object,
		Actor

	};
	E_ObjectPathSuffixType objectPathSuffixType = E_ObjectPathSuffixType::None;

	size_t objectPathLength = objectPath.length();
	if (objectPathLength >= 2)
	{
		size_t objectPathNoSuffixLength = objectPathLength - 2;

		std::wstring objectPathEndChars = objectPath.substr(objectPathNoSuffixLength);
		if (objectPathEndChars == L"--")
		{
			objectPathSuffixType = E_ObjectPathSuffixType::Object;
		}
		if (objectPathEndChars == L"..")
		{
			objectPathSuffixType = E_ObjectPathSuffixType::Actor;
		}

		if (objectPathSuffixType != E_ObjectPathSuffixType::None)
			objectPath = objectPath.substr(0, objectPathNoSuffixLength);
	}

	std::wstring normalizedObjectPath = objectPath;
	bool wasObjectPathNormalized = false;

	if (objectPath.find(engineContentKey) == 0)
	{
		normalizedObjectPath = L"/Engine/" + objectPath.substr(engineContentKey.length());
		wasObjectPathNormalized = true;
	}
	else
	{
		size_t contentPos = objectPath.find(contentKey);
		if (contentPos != std::wstring::npos)
		{
			std::wstring relativePath = objectPath.substr(contentPos + contentKey.length());
			std::wstring rootPath = objectPath.substr(0, contentPos);

			size_t pluginsPos = rootPath.find(pluginsKey);
			if (pluginsPos != std::wstring::npos)
			{
				size_t lastSlash = rootPath.find_last_of('/');
				if (lastSlash != std::wstring::npos)
				{
					std::wstring pluginName = rootPath.substr(lastSlash + 1);

					normalizedObjectPath = L"/" + pluginName + L"/" + relativePath;
					wasObjectPathNormalized = true;
				}
			}

			if (wasObjectPathNormalized == false)
			{
				normalizedObjectPath = L"/Game/" + relativePath;
				wasObjectPathNormalized = true;
			}
		}
	}

	if (objectPathSuffixType != E_ObjectPathSuffixType::None)
	{
		std::wstring assetName = GetObjectNameFromPath(normalizedObjectPath);
		if (objectPathSuffixType == E_ObjectPathSuffixType::Object)
		{
			normalizedObjectPath = normalizedObjectPath + L"." + assetName;
		}
		else
		{
			normalizedObjectPath = normalizedObjectPath + L"." + assetName + L"_C";
		}
	}

	return wasObjectPathNormalized ? normalizedObjectPath : objectPath;
}

std::wstring Utilities::String::GetObjectNameFromPath(std::wstring objectPath)
{
	if (objectPath.empty())
	{
		return std::wstring();
	}

	size_t lastDotPos = objectPath.find_last_of(L'.');
	if (lastDotPos != std::wstring::npos)
	{
		return objectPath.substr(lastDotPos + 1);
	}

	size_t lastSlashPos = objectPath.find_last_of(L"/\\");
	if (lastSlashPos != std::wstring::npos)
	{
		return objectPath.substr(lastSlashPos + 1);
	}

	return objectPath;
}






LONG Utilities::Exception::Handle(LPEXCEPTION_POINTERS exceptionInfo, const char* title)
{
#ifdef _DEBUG
    void* crashAddress = exceptionInfo->ExceptionRecord->ExceptionAddress;

    HMODULE hModule = GetModuleHandle(nullptr);
    uintptr_t baseAddress = (uintptr_t)hModule;
    uintptr_t relativeOffset = (uintptr_t)crashAddress - baseAddress;

    std::string stringTitle = title != nullptr ? std::string(title) : "FAILED TO READ TITLE";
    std::stringstream stringStream;
    stringStream << "[" << stringTitle << "]" << "\n";
    stringStream << "Exception Code: 0x" << std::hex << std::uppercase << exceptionInfo->ExceptionRecord->ExceptionCode << "\n";
    stringStream << "Absolute Address: 0x" << crashAddress << "\n";
    stringStream << "Module Base:      0x" << (void*)baseAddress << "\n";
    stringStream << "Relative Offset:  +0x" << relativeOffset << "\n";
    stringStream << "--------------------------------------------------\n";

    std::string logEntry = stringStream.str();
    FileInstance exceptionsFile(PATH_LOG_EXCEPTIONS);
    std::string fileContents = std::string();

    if (exceptionsFile.DoesFileExist())
    {
        exceptionsFile.LoadText(&fileContents);

        if (fileContents.empty() == false && fileContents.back() != '\n')
        {
            fileContents += "\n";
        }
    }

    fileContents += logEntry;
    exceptionsFile.SaveText(fileContents);
#endif

    return EXCEPTION_EXECUTE_HANDLER;
}