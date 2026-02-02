#pragma once
#include <Windows.h>
#include <string>
#include <algorithm>
#include <cwctype>
#include <cstdlib>

#include "definitions.h"
#include "FileInstance.h"





namespace Utilities
{
	class Clipboard
	{
	public:
		static std::string GetClipboardText();
		static bool SetClipboardText(const std::string& string);
	};




	class String
	{
	public:
		static std::string ToString(const std::wstring& wideString);
		static std::string ToString(const char* cString);
		static std::string ToString(const wchar_t* wcString);

		static std::wstring ToWString(const std::string& string);
		static std::wstring ToWString(const char* cString);
		static std::wstring ToWString(const wchar_t* wcString);




		static std::string ToLowerCase(const std::string& string);
		static std::wstring ToLowerCase(const std::wstring& wString);

		static std::string ToUpperCase(const std::string& string);
		static std::wstring ToUpperCase(const std::wstring& wString);




		static std::vector<std::string> Split(const std::string& string, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const std::wstring& wString, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const char* cString, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const wchar_t* wcString, const char& separator, const bool& removeSeparatorSpaces = true);

		static std::vector<std::wstring> Split(const std::string& string, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const char* cString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const wchar_t* wcString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);




		static std::wstring NormalizeObjectPath(std::wstring objectPath);
	};




	class Exception
	{
	public:
		static LONG Handle(LPEXCEPTION_POINTERS exceptionInfo, const char* title);
	};
};

