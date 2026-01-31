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

bool Utilities::Clipboard::SetClipboardText(const std::string& str)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        size_t textSize = str.size() + 1;

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (hGlobal)
        {
            void* pMem = GlobalLock(hGlobal);
            if (pMem)
            {
                std::memcpy(pMem, str.c_str(), textSize);
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






std::string Utilities::String::ToLowerCase(const std::string& str)
{
    std::string outString = str;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    return outString;
}

std::string Utilities::String::ToUpperCase(const std::string& str)
{
    std::string outString = str;
    std::transform(outString.begin(), outString.end(), outString.begin(), [](unsigned char c) 
    { 
        return std::toupper(c); 
    });

    return outString;
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
