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




std::string Utilities::String::ToLowerCase(const std::string& string)
{
    std::string outString = string;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    return outString;
}

std::wstring Utilities::String::ToLowerCase(const std::wstring& wString)
{
	std::wstring outString = wString;
	std::transform(outString.begin(), outString.end(), outString.begin(), [](wchar_t c)
	{
		return std::towlower(c);
	});

	return outString;
}



std::string Utilities::String::ToUpperCase(const std::string& string)
{
    std::string outString = string;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c) 
    { 
        return std::toupper(c); 
    });

    return outString;
}

std::wstring Utilities::String::ToUpperCase(const std::wstring& wString)
{
	std::wstring outString = wString;
	std::transform(outString.begin(), outString.end(), outString.begin(), [](wchar_t c)
	{
		return std::towupper(c);
	});

	return outString;
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

	size_t objectPathLength = objectPath.length();
	if (objectPathLength == 0)
	{
		return objectPath;
	}

	std::replace(objectPath.begin(), objectPath.end(), L'\\', L'/');

	/*
		0 = NONE,
		1 = -- (Object),
		2 = .. (Actor)
	*/
	short objectPathSuffixType = 0;
	if (objectPathLength >= 2)
	{
		size_t objectPathNoSuffixLength = objectPathLength - 2;

		std::wstring objectPathEndChars = objectPath.substr(objectPathNoSuffixLength);
		if (objectPathEndChars == L"--")
		{
			objectPathSuffixType = 1;
		}
		if (objectPathEndChars == L"..")
		{
			objectPathSuffixType = 2;
		}

		if (objectPathSuffixType != 0)
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

	if (objectPathSuffixType != 0)
	{
		size_t lastSlash = normalizedObjectPath.find_last_of(L'/');
		if (lastSlash != std::wstring::npos)
		{
			std::wstring assetName = normalizedObjectPath.substr(lastSlash + 1);
			if (objectPathSuffixType == 1)
			{
				normalizedObjectPath = normalizedObjectPath + L"." + assetName;
			}
			if (objectPathSuffixType == 2)
			{
				normalizedObjectPath = normalizedObjectPath + L"." + assetName + L"_C";
			}
		}
	}

	return wasObjectPathNormalized ? normalizedObjectPath : objectPath;
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
