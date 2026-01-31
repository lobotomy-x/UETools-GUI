#pragma once
#include <Windows.h>
#include <string>
#include <algorithm>

#include "definitions.h"
#include "FileInstance.h"





namespace Utilities
{
	class Clipboard
	{
	public:
		static std::string GetClipboardText();
		static bool SetClipboardText(const std::string& str);
	};






	class String
	{
	public:
		static std::string ToLowerCase(const std::string& str);
		static std::string ToUpperCase(const std::string& str);
	};




	class Exception
	{
	public:
		static LONG Handle(LPEXCEPTION_POINTERS exceptionInfo, const char* title);
	};
};

