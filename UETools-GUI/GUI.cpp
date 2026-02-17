#include "GUI.h"






// ==============================
// |          #ImGui			|
// ==============================
ImGui::Viewport ImGui::GetViewport()
{
	ImGui::Viewport viewport;

	ImGuiViewport* iViewport = ImGui::GetMainViewport();
	if (iViewport == nullptr)
		return viewport;

	viewport.iViewport = iViewport;
	viewport.iViewportPosition = { iViewport->Pos.x, iViewport->Pos.y };
	viewport.iViewportSize = { iViewport->Size.x, iViewport->Size.y };

	return viewport;
}


ImDrawList* ImGui::GetDrawList()
{
	ImDrawList* iDrawList = ImGui::GetBackgroundDrawList();
	return iDrawList ? iDrawList : nullptr;
}




void ImGui::TextBool(const char* label, const bool& inBool, const char* text_true, const char* text_false, const bool& useColoring, const ImU32& color_true, const ImU32& color_false)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, inBool ? color_true : color_false);
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));
		ImGui::PopStyleColor();
	}
	else
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));

}

void ImGui::TextBool(const char* label, const bool& inBool)
{
	TextBool(label, inBool, "True", "False", false, ImU32(), ImU32());
}

void ImGui::TextBoolColored(const char* label, const bool& status)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, status, "True", "False", true, color_true, color_false);
}

void ImGui::TextBoolPresence(const char* label, const bool& presence)
{
	TextBool(label, presence, "Is Present", "Doesn't Exist!", false, ImU32(), ImU32());
}

void ImGui::TextBoolPresenceColored(const char* label, const bool& presence)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, presence, "Is Present", "Doesn't Exist!", true, color_true, color_false);
}

void ImGui::TextBoolMultiplePresence(const char* label, const bool& presence)
{
	TextBool(label, presence, "Are Present", "Are Non Existent!", false, ImU32(), ImU32());
}

void ImGui::TextBoolMultiplePresenceColored(const char* label, const bool& presence)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, presence, "Are Present", "Are Non Existent!", true, color_true, color_false);
}




void ImGui::TextFloat(const char* label, const float& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0.0f)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%f", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%f", value);
}

void ImGui::TextFloat(const char* label, const float& value)
{
	TextFloat(label, value, false, ImU32(), ImU32());
}

void ImGui::TextFloatColored(const char* label, const float& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextFloat(label, value, true, color_positive, color_negative);
}




void ImGui::TextInt(const char* label, const int32_t& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%d", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%d", value);
}

void ImGui::TextInt(const char* label, const int32_t& value)
{
	TextInt(label, value, false, ImU32(), ImU32());
}

void ImGui::TextIntColored(const char* label, const int32_t& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextInt(label, value, true, color_positive, color_negative);
}




void ImGui::TextVector(const char* label, const SDK::FVector& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"X:",
		"Y:",
		"Z:"
	};

	const double coords[3]
	{
		value.X,
		value.Y,
		value.Z
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = coords[i] > -0.0000001 && coords[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, coords[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%f", neutralValue ? 0.0 : coords[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
}

void ImGui::TextVector(const char* label, const SDK::FVector& value)
{
	TextVector(label, value, false, ImU32(), ImU32());
}

void ImGui::TextVectorColored(const char* label, const SDK::FVector& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextVector(label, value, true, color_positive, color_negative);
}




void ImGui::TextRotator(const char* label, const SDK::FRotator& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"Pitch:",
		"Yaw:",
		"Roll:"
	};

	const double angles[3]
	{
		value.Pitch,
		value.Yaw,
		value.Roll
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = angles[i] > -0.0000001 && angles[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, angles[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%f", neutralValue ? 0.0 : angles[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
}

void ImGui::TextRotator(const char* label, const SDK::FRotator& value)
{
	TextRotator(label, value, false, ImU32(), ImU32());
}

void ImGui::TextRotatorColored(const char* label, const SDK::FRotator& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextRotator(label, value, true, color_positive, color_negative);
}




void ImGui::TextHint(const char* hint)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(hint);
		ImGui::EndTooltip();
	}
}




void ImGui::ReadOnlyInputText(const char* label, const char* text, const bool& showCopyButton)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : (text ? text : "ReadOnlyInputText"));
	const size_t length = text ? strlen(text) : 0;

	static std::vector<char> buffer;
	buffer.clear();

	if (text && length)
		buffer.insert(buffer.end(), text, text + length);
	buffer.push_back('\0');

	ImGui::InputText("##ReadOnlyInputText", buffer.data(), buffer.size(), ImGuiInputTextFlags_ReadOnly);
	if (showCopyButton)
	{
		ImGui::SameLine();
		if (ImGui::Button("Copy"))
		{
			GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(buffer.data()));
		}
	}

	ImGui::PopID();
}






void ImGui::ObjectFilterModeComboBox(const char* label, E_ObjectFilterMode* v)
{
	ImGui::PushID(label);

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	static const char* items[] = { "Class Name", "Object Name", "All" };
	int index = static_cast<int>(*v);

	ImGui::SetNextItemWidth(200);
	if (ImGui::Combo("##object_filter_combo", &index, items, IM_ARRAYSIZE(items))) 
	{
		*v = static_cast<E_ObjectFilterMode>(index);
	}

	ImGui::PopID();
}




int ImGui::ImGuiKey_ToWinAPI(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab: return VK_TAB;
		case ImGuiKey_LeftArrow: return VK_LEFT;
		case ImGuiKey_RightArrow: return VK_RIGHT;
		case ImGuiKey_UpArrow: return VK_UP;
		case ImGuiKey_DownArrow: return VK_DOWN;
		case ImGuiKey_PageUp: return VK_PRIOR;
		case ImGuiKey_PageDown: return VK_NEXT;
		case ImGuiKey_Home: return VK_HOME;
		case ImGuiKey_End: return VK_END;
		case ImGuiKey_Insert: return VK_INSERT;
		case ImGuiKey_Delete: return VK_DELETE;
		case ImGuiKey_Backspace: return VK_BACK;
		case ImGuiKey_Space: return VK_SPACE;
		case ImGuiKey_Enter: return VK_RETURN;
		case ImGuiKey_Escape: return VK_ESCAPE;

		case ImGuiKey_PrintScreen: return VK_SNAPSHOT;
		case ImGuiKey_Pause: return VK_PAUSE;
		case ImGuiKey_CapsLock: return VK_CAPITAL;
		case ImGuiKey_ScrollLock: return VK_SCROLL;
		case ImGuiKey_NumLock: return VK_NUMLOCK;
		case ImGuiKey_Menu: return VK_APPS;

		case ImGuiKey_A: return 'A'; case ImGuiKey_B: return 'B';
		case ImGuiKey_C: return 'C'; case ImGuiKey_D: return 'D';
		case ImGuiKey_E: return 'E'; case ImGuiKey_F: return 'F';
		case ImGuiKey_G: return 'G'; case ImGuiKey_H: return 'H';
		case ImGuiKey_I: return 'I'; case ImGuiKey_J: return 'J';
		case ImGuiKey_K: return 'K'; case ImGuiKey_L: return 'L';
		case ImGuiKey_M: return 'M'; case ImGuiKey_N: return 'N';
		case ImGuiKey_O: return 'O'; case ImGuiKey_P: return 'P';
		case ImGuiKey_Q: return 'Q'; case ImGuiKey_R: return 'R';
		case ImGuiKey_S: return 'S'; case ImGuiKey_T: return 'T';
		case ImGuiKey_U: return 'U'; case ImGuiKey_V: return 'V';
		case ImGuiKey_W: return 'W'; case ImGuiKey_X: return 'X';
		case ImGuiKey_Y: return 'Y'; case ImGuiKey_Z: return 'Z';

		case ImGuiKey_0: return '0'; case ImGuiKey_1: return '1';
		case ImGuiKey_2: return '2'; case ImGuiKey_3: return '3';
		case ImGuiKey_4: return '4'; case ImGuiKey_5: return '5';
		case ImGuiKey_6: return '6'; case ImGuiKey_7: return '7';
		case ImGuiKey_8: return '8'; case ImGuiKey_9: return '9';

		case ImGuiKey_Minus: return VK_OEM_MINUS;
		case ImGuiKey_Equal: return VK_OEM_PLUS;
		case ImGuiKey_LeftBracket: return VK_OEM_4;
		case ImGuiKey_RightBracket: return VK_OEM_6;
		case ImGuiKey_Semicolon: return VK_OEM_1;
		case ImGuiKey_Apostrophe: return VK_OEM_7;
		case ImGuiKey_Comma: return VK_OEM_COMMA;
		case ImGuiKey_Period: return VK_OEM_PERIOD;
		case ImGuiKey_Slash: return VK_OEM_2;
		case ImGuiKey_Backslash: return VK_OEM_5;
		case ImGuiKey_GraveAccent: return VK_OEM_3;

		case ImGuiKey_Keypad0: return VK_NUMPAD0;
		case ImGuiKey_Keypad1: return VK_NUMPAD1;
		case ImGuiKey_Keypad2: return VK_NUMPAD2;
		case ImGuiKey_Keypad3: return VK_NUMPAD3;
		case ImGuiKey_Keypad4: return VK_NUMPAD4;
		case ImGuiKey_Keypad5: return VK_NUMPAD5;
		case ImGuiKey_Keypad6: return VK_NUMPAD6;
		case ImGuiKey_Keypad7: return VK_NUMPAD7;
		case ImGuiKey_Keypad8: return VK_NUMPAD8;
		case ImGuiKey_Keypad9: return VK_NUMPAD9;
		case ImGuiKey_KeypadMultiply: return VK_MULTIPLY;
		case ImGuiKey_KeypadAdd: return VK_ADD;
		case ImGuiKey_KeypadSubtract: return VK_SUBTRACT;
		case ImGuiKey_KeypadDecimal: return VK_DECIMAL;
		case ImGuiKey_KeypadDivide: return VK_DIVIDE;

		case ImGuiKey_F1: return VK_F1; case ImGuiKey_F2: return VK_F2;
		case ImGuiKey_F3: return VK_F3; case ImGuiKey_F4: return VK_F4;
		case ImGuiKey_F5: return VK_F5; case ImGuiKey_F6: return VK_F6;
		case ImGuiKey_F7: return VK_F7; case ImGuiKey_F8: return VK_F8;
		case ImGuiKey_F9: return VK_F9; case ImGuiKey_F10: return VK_F10;
		case ImGuiKey_F11: return VK_F11; case ImGuiKey_F12: return VK_F12;

		case ImGuiKey_LeftCtrl: return VK_LCONTROL;
		case ImGuiKey_RightCtrl: return VK_RCONTROL;
		case ImGuiKey_LeftShift: return VK_LSHIFT;
		case ImGuiKey_RightShift: return VK_RSHIFT;
		/* Left Alt recognition was disabled due to glitch with ALT + TABing. */
		// case ImGuiKey_LeftAlt: return VK_LMENU;
		case ImGuiKey_RightAlt: return VK_RMENU;
		case ImGuiKey_LeftSuper: return VK_LWIN;
		case ImGuiKey_RightSuper: return VK_RWIN;

		default: return 0;
	}
}

const char* ImGui::ImGuiKey_GetName(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab:            return "Tab";
		case ImGuiKey_LeftArrow:      return "Left";
		case ImGuiKey_RightArrow:     return "Right";
		case ImGuiKey_UpArrow:        return "Up";
		case ImGuiKey_DownArrow:      return "Down";
		case ImGuiKey_PageUp:         return "PgUp";
		case ImGuiKey_PageDown:       return "PgDn";
		case ImGuiKey_Home:           return "Home";
		case ImGuiKey_End:            return "End";
		case ImGuiKey_Insert:         return "Ins";
		case ImGuiKey_Delete:         return "Del";
		case ImGuiKey_Backspace:      return "Bspace";
		case ImGuiKey_Space:          return "Space";
		case ImGuiKey_Enter:          return "Enter";
		case ImGuiKey_Escape:         return "Esc";

		case ImGuiKey_PrintScreen:    return "PrtSc";
		case ImGuiKey_Pause:          return "Pause";
		case ImGuiKey_CapsLock:       return "Caps";
		case ImGuiKey_ScrollLock:     return "ScrLk";
		case ImGuiKey_NumLock:        return "NumLk";
		case ImGuiKey_Menu:           return "Menu";

		case ImGuiKey_A: return "A";  case ImGuiKey_B: return "B";
		case ImGuiKey_C: return "C";  case ImGuiKey_D: return "D";
		case ImGuiKey_E: return "E";  case ImGuiKey_F: return "F";
		case ImGuiKey_G: return "G";  case ImGuiKey_H: return "H";
		case ImGuiKey_I: return "I";  case ImGuiKey_J: return "J";
		case ImGuiKey_K: return "K";  case ImGuiKey_L: return "L";
		case ImGuiKey_M: return "M";  case ImGuiKey_N: return "N";
		case ImGuiKey_O: return "O";  case ImGuiKey_P: return "P";
		case ImGuiKey_Q: return "Q";  case ImGuiKey_R: return "R";
		case ImGuiKey_S: return "S";  case ImGuiKey_T: return "T";
		case ImGuiKey_U: return "U";  case ImGuiKey_V: return "V";
		case ImGuiKey_W: return "W";  case ImGuiKey_X: return "X";
		case ImGuiKey_Y: return "Y";  case ImGuiKey_Z: return "Z";

		case ImGuiKey_0: return "0";  case ImGuiKey_1: return "1";
		case ImGuiKey_2: return "2";  case ImGuiKey_3: return "3";
		case ImGuiKey_4: return "4";  case ImGuiKey_5: return "5";
		case ImGuiKey_6: return "6";  case ImGuiKey_7: return "7";
		case ImGuiKey_8: return "8";  case ImGuiKey_9: return "9";

		case ImGuiKey_Minus:          return "-";
		case ImGuiKey_Equal:          return "=";
		case ImGuiKey_LeftBracket:    return "[";
		case ImGuiKey_RightBracket:   return "]";
		case ImGuiKey_Semicolon:      return ";";
		case ImGuiKey_Apostrophe:     return "'";
		case ImGuiKey_Comma:          return ",";
		case ImGuiKey_Period:         return ".";
		case ImGuiKey_Slash:          return "/";
		case ImGuiKey_Backslash:      return "\\";
		case ImGuiKey_GraveAccent:    return "`";

		case ImGuiKey_Keypad0:        return "Num0";
		case ImGuiKey_Keypad1:        return "Num1";
		case ImGuiKey_Keypad2:        return "Num2";
		case ImGuiKey_Keypad3:        return "Num3";
		case ImGuiKey_Keypad4:        return "Num4";
		case ImGuiKey_Keypad5:        return "Num5";
		case ImGuiKey_Keypad6:        return "Num6";
		case ImGuiKey_Keypad7:        return "Num7";
		case ImGuiKey_Keypad8:        return "Num8";
		case ImGuiKey_Keypad9:        return "Num9";
		case ImGuiKey_KeypadMultiply: return "Num*";
		case ImGuiKey_KeypadAdd:      return "Num+";
		case ImGuiKey_KeypadSubtract: return "Num-";
		case ImGuiKey_KeypadDecimal:  return "Num.";
		case ImGuiKey_KeypadDivide:   return "Num/";

		case ImGuiKey_F1:  return "F1";   case ImGuiKey_F2:  return "F2";
		case ImGuiKey_F3:  return "F3";   case ImGuiKey_F4:  return "F4";
		case ImGuiKey_F5:  return "F5";   case ImGuiKey_F6:  return "F6";
		case ImGuiKey_F7:  return "F7";   case ImGuiKey_F8:  return "F8";
		case ImGuiKey_F9:  return "F9";   case ImGuiKey_F10: return "F10";
		case ImGuiKey_F11: return "F11";  case ImGuiKey_F12: return "F12";

		case ImGuiKey_LeftCtrl:   return "LCtrl";
		case ImGuiKey_RightCtrl:  return "RCtrl";
		case ImGuiKey_LeftShift:  return "LShift";
		case ImGuiKey_RightShift: return "RShift";
		case ImGuiKey_LeftAlt:    return "LAlt";
		case ImGuiKey_RightAlt:   return "RAlt";
		case ImGuiKey_LeftSuper:  return "LWin";
		case ImGuiKey_RightSuper: return "RWin";

		default: return "???";
	}
}




bool ImGui::KeyBindingInput(const char* label, KeyBinding* binding)
{
	if (!binding)
		return false;

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : "KeyBindingInput");

	SameLine();

	/* 0 corresponds for default vertical size. */
	static const ImVec2 buttonSize = { 96.0f, 0.0f };

	static const ImVec4 buttonColor = { 0.20f, 0.50f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_unbound = { 0.50f, 0.20f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_capturing = { 0.25f, 0.25f, 0.25f, 1.00f };

	bool hasBindingChanged = false;
	if (binding->isDetermined)
	{
		const char* bindingName;

		if (binding->key == ImGuiKey_None)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_unbound);
			bindingName = "?";
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			bindingName = ImGuiKey_GetName(binding->key);
		}

		if (Button(bindingName, buttonSize))
			binding->isDetermined = false;
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_capturing);

		Button("...", buttonSize);
		for (int keyCode = ImGuiKey_NamedKey_BEGIN; keyCode < ImGuiKey_NamedKey_END; keyCode++)
		{
			if (IsKeyPressed((ImGuiKey)keyCode))
			{
				/* Verify that keyCode is within pre-determined list of keys. */
				if (ImGuiKey_ToWinAPI((ImGuiKey)keyCode) == 0)
					continue;

				/* When user tries to assign same key that is already set, consider that as will to unbind. */
				if (keyCode == binding->key)
					binding->key = ImGuiKey_None;
				else
					binding->key = (ImGuiKey)keyCode;

				binding->isDetermined = true;
				hasBindingChanged = true;

				Inputs::Config::Save();

				break;
			}
		}
	}

	ImGui::PopStyleColor();
	ImGui::PopID();

	return hasBindingChanged;
}

bool ImGui::IsKeyBindingPressed(KeyBinding* binding, const bool& waitForRelease)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (waitForRelease)
	{
		if (GetAsyncKeyState(keyCode) & 0x8000)
		{
			binding->isInUse = true;
			while (GetAsyncKeyState(keyCode) & 0x8000)
			{
				Sleep(1);
			}

			binding->isInUse = false;
			return true;
		}
	}
	else
		return (GetAsyncKeyState(keyCode) & 1);

	return false;
}

bool ImGui::IsKeyBindingDown(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return true; // <-- !

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (GetAsyncKeyState(keyCode) & 0x8000)
		return true;

	return false;
}

bool ImGui::IsKeyBindingReleased(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	return (GetAsyncKeyState(keyCode) & 0x8000) == false;
}






// ==============================
// |            #GUI			|
// ==============================
bool GUI::StartWindowThread()
{
	if (windowThread)
		return false;

	windowThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DirectWindow11::Create, 0, 0, 0);
	return windowThread;
}




void GUI::Init(const HMODULE& applicationModule)
{
	/* Before creating a DirectWindow, we need to make it aware of our DLL HMODULE. */
	DirectWindow11::SetApplicationModule(applicationModule);
	StartWindowThread();

	Features::Config::Load();
	Features::Positions::Load();
	Inputs::Config::Load();

	Inputs::Keybindings::EnableProcessing();
}

#ifdef WAIT_FOR_TITLE_INIT
void GUI::InitOnTitleInitialized(const HMODULE& applicationModule)
{
	while (Unreal::IsTitleInitialized() == false)
		Sleep(100);

	Init(applicationModule);
}
#endif




void GUI::Draw()
{
	if (GetIsMenuActive())
	{
		if (ImGui::BeginMainMenuBar())
		{
			ImGui::Text("UETools GUI (v4.3)");
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			if (ImGui::IsItemClicked())
			{
				ShellExecuteA(NULL, "open", "https://github.com/Cranch-fur/UETools-GUI", NULL, NULL, SW_SHOWNORMAL);
			}
#ifdef _DEBUG
			if (GetIsMenuDebugEnabled())
				ImGui::Text("[%d]", GetMenuDebugLevel());
			else 
				ImGui::Text("[D]");

			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			if (ImGui::IsItemClicked())
			{
				SwitchMenuDebugLevel();
			}

			if (GetIsMenuDebugEnabled())
			{
				ImGui::ShowDemoWindow();

				if (GetIsMenuDebugDetailed())
				{
					ImGui::ShowDebugLogWindow();
					ImGui::ShowIDStackToolWindow();
				}
			}

			ImGui::Text(" | ");
			ImGui::Text("%.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
				ImGui::BeginTooltip();
				ImGui::Text("%d visible windows", ImGui::GetIO().MetricsRenderWindows);
				ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);
				ImGui::EndTooltip();
			}
#endif

			ImGui::Text(" | ");

			Templates::Menus::Debug::Draw();

			Templates::Menus::World::Draw();

			Templates::Menus::Character::Draw();

#ifdef FREE_CAMERA
			Templates::Menus::FreeCamera::Draw();
#endif

			Templates::Menus::Settings::Draw();

			ImGui::Text(" | ");

			Templates::Console::Draw();


			ImGui::EndMainMenuBar();
		}
	}

#ifdef ACTOR_TRACE
	if (Features::ActorTrace::enabled)
		Features::ActorTrace::ThreadSafeDraw();
#endif

#ifdef ACTORS_TRACKING
	if (Features::ActorsTracker::enabled)
		Features::ActorsTracker::ThreadSafeDraw();
#endif

#ifdef COLLISION_VISUALIZER
	if (Features::CollisionVisualizer::enabled)
		Features::CollisionVisualizer::ThreadSafeDraw();
#endif
}




void GUI::PlayUISound(const E_Sound& soundToPlay)
{
	if (Features::Menu::enableSound == false)
		return;

	uint16_t soundFrequency;
	uint16_t soundDuration;

	switch (soundToPlay)
	{
		case E_Sound::BUTTON_PRESS:
			soundFrequency = 245;
			soundDuration = 50;
			break;

		case E_Sound::BUTTON_CANCEL:
			soundFrequency = 100;
			soundDuration = 150;
			break;

		case E_Sound::ACTION_SUCCESS:
			soundFrequency = 350;
			soundDuration = 300;
			break;

		case E_Sound::ACTION_ERROR:
			soundFrequency = 175;
			soundDuration = 300;
			break;

		default:
			soundFrequency = 500;
			soundDuration = 1000;
			break;
	}

	/*
		Dedicate sound playback in to separate thread.
		This prevents the main thread from blocking while Beep() is playing the sound.
	*/
	std::thread([=]()
		{
			Beep(soundFrequency, soundDuration);
		}).detach();
}






// ==============================
// |        #Features			|
// ==============================
template<typename T>
inline void Features::Config::ReadFeatureFromConfig(ConfigInstance* featuresConfig, const std::string& entryName, T* featureValue)
{
	if (featuresConfig == nullptr || featureValue == nullptr)
		return;

	if (featuresConfig->HasKey(entryName) == false)
		return;

	*featureValue = featuresConfig->Get<T>(entryName).value_or(*featureValue);
}

void Features::Config::Load()
{
	ConfigInstance featuresConfig(PATH_CONFIG_FEATURES);
	if (featuresConfig.Load() == false)
	{
		Features::Config::Save();
		featuresConfig.Load();
	}

	ReadFeatureFromConfig(&featuresConfig, "Features_Menu_enableSound", &Features::Menu::enableSound);
	ReadFeatureFromConfig(&featuresConfig, "Features_Menu_autoConstructConsole", &Features::Menu::autoConstructConsole);
	if (Features::Menu::autoConstructConsole)
		Unreal::Console::Construct();
	ReadFeatureFromConfig(&featuresConfig, "Features_Menu_enableConsoleOutput", &Features::Menu::enableConsoleOutput);

	ReadFeatureFromConfig(&featuresConfig, "Features_Debug_autoUpdate", &Features::Debug::autoUpdate);
	ReadFeatureFromConfig(&featuresConfig, "Features_Debug_autoUpdateDelay", &Features::Debug::autoUpdateDelay);

	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_enabled", &Features::DirectionalMovement::enabled);
	if (Features::DirectionalMovement::enabled)
		Features::DirectionalMovement::Enable();
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_omniMovement", &Features::DirectionalMovement::omniMovement);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_step", &Features::DirectionalMovement::step);
	ReadFeatureFromConfig(&featuresConfig, "Features_DirectionalMovement_delay", &Features::DirectionalMovement::delay);

#ifdef FREE_CAMERA
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_cameraMovementStep", &Features::FreeCamera::cameraMovementStep);
	ReadFeatureFromConfig(&featuresConfig, "Features_FreeCamera_cameraRotationStep", &Features::FreeCamera::cameraRotationStep);
#endif
}

void Features::Config::Save()
{
	ConfigInstance featuresConfig(PATH_CONFIG_FEATURES);

	featuresConfig.Set("Features_Menu_enableSound", Features::Menu::enableSound);
	featuresConfig.Set("Features_Menu_autoConstructConsole", Features::Menu::autoConstructConsole);
	featuresConfig.Set("Features_Menu_enableConsoleOutput", Features::Menu::enableConsoleOutput);

	featuresConfig.Set("Features_Debug_autoUpdate", Features::Debug::autoUpdate);
	featuresConfig.Set("Features_Debug_autoUpdateDelay", Features::Debug::autoUpdateDelay);

	featuresConfig.Set("Features_DirectionalMovement_enabled", Features::DirectionalMovement::enabled);
	featuresConfig.Set("Features_DirectionalMovement_omniMovement", Features::DirectionalMovement::omniMovement);
	featuresConfig.Set("Features_DirectionalMovement_step", Features::DirectionalMovement::step);
	featuresConfig.Set("Features_DirectionalMovement_delay", Features::DirectionalMovement::delay);

#ifdef FREE_CAMERA
	featuresConfig.Set("Features_FreeCamera_cameraMovementStep", Features::FreeCamera::cameraMovementStep);
	featuresConfig.Set("Features_FreeCamera_cameraRotationStep", Features::FreeCamera::cameraRotationStep);
#endif

	featuresConfig.Save();
}




void Features::Debug::Update()
{
	SDK::UEngine* engine = Unreal::Engine::Get();
	if (Features::Debug::engine.reference = engine)
	{
		Features::Debug::engine.className = engine->Class->GetFullName();
		Features::Debug::engine.objectName = engine->GetFullName();

		Features::Debug::engine.fixedFrameRateEnabled = engine->bUseFixedFrameRate;
		Features::Debug::engine.fixedFrameRate = engine->FixedFrameRate;

		Features::Debug::engine.smoothFrameRateEnabled = engine->bSmoothFrameRate;
		Features::Debug::engine.smoothFrameRateRange = engine->SmoothedFrameRateRange;

		Features::Debug::engine.subtitlesEnabled = engine->bSubtitlesEnabled;
		Features::Debug::engine.subtitlesForcedOff = engine->bSubtitlesForcedOff;

		Features::Debug::engine.pauseOnLossOfFocus = engine->bPauseOnLossOfFocus;

		SDK::UGameViewportClient* viewportClient = engine->GameViewport;
		if (Features::Debug::engine.gameViewportClient.reference = viewportClient)
		{
			Features::Debug::engine.gameViewportClient.className = viewportClient->Class->GetFullName();
			Features::Debug::engine.gameViewportClient.objectName = viewportClient->GetFullName();

			SDK::UConsole* console = viewportClient->ViewportConsole;
			if (Features::Debug::engine.gameViewportClient.console.reference = console)
			{
				Features::Debug::engine.gameViewportClient.console.className = console->Class->GetFullName();
				Features::Debug::engine.gameViewportClient.console.objectName = console->GetFullName();
			}
		}
	}


	SDK::UGameInstance* gameInstance = Unreal::GameInstance::Get();
	if (Features::Debug::gameInstance.reference = gameInstance)
	{
		Features::Debug::gameInstance.className = gameInstance->Class->GetFullName();
		Features::Debug::gameInstance.objectName = gameInstance->GetFullName();

		SDK::UOnlineSession* onlineSession = gameInstance->OnlineSession;
		if (Features::Debug::gameInstance.onlineSession.reference = onlineSession)
		{
			Features::Debug::gameInstance.onlineSession.className = gameInstance->Class->GetFullName();
			Features::Debug::gameInstance.onlineSession.objectName = gameInstance->GetFullName();
		}
	}


	SDK::AGameModeBase* gameMode = Unreal::GameMode::Get();
	if (Features::Debug::gameMode.reference = gameMode)
	{
		Features::Debug::gameMode.className = gameMode->Class->GetFullName();
		Features::Debug::gameMode.objectName = gameMode->GetFullName();

		SDK::AGameSession* gameSession = gameMode->GameSession;
		if (Features::Debug::gameMode.gameSession.reference = gameSession)
		{
			Features::Debug::gameMode.gameSession.className = gameSession->Class->GetFullName();
			Features::Debug::gameMode.gameSession.objectName = gameSession->GetFullName();

			Features::Debug::gameMode.gameSession.maxPlayers = gameSession->MaxPlayers;
			Features::Debug::gameMode.gameSession.maxSpectators = gameSession->MaxSpectators;
			Features::Debug::gameMode.gameSession.maxPartySize = gameSession->MaxPartySize;
			Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = gameSession->MaxSplitscreensPerConnection;

			Features::Debug::gameMode.gameSession.sessionName = gameSession->SessionName.ToString();
		}

		Features::Debug::gameMode.playersCount = gameMode->GetNumPlayers();
		Features::Debug::gameMode.spectatorsCount = gameMode->GetNumSpectators();

		Features::Debug::gameMode.startPlayersAsSpectators = gameMode->bStartPlayersAsSpectators;
		Features::Debug::gameMode.defaultPlayerName = gameMode->DefaultPlayerName.ToString();

		Features::Debug::gameMode.useSeamlessTravel = gameMode->bUseSeamlessTravel;
		Features::Debug::gameMode.options = gameMode->OptionsString.ToString();

		Features::Debug::gameMode.isPausable = gameMode->bPauseable;
	}


	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (Features::Debug::playerController.reference = playerController)
	{
		Features::Debug::playerController.className = playerController->Class->GetFullName();
		Features::Debug::playerController.objectName = playerController->GetFullName();


		SDK::UPlayer* player = playerController->Player;
		if (Features::Debug::playerController.player.reference = player)
		{
			Features::Debug::playerController.player.className = player->Class->GetFullName();
			Features::Debug::playerController.player.objectName = player->GetFullName();
		}


		SDK::APawn* pawn = playerController->AcknowledgedPawn;
		if (Features::Debug::playerController.pawn.reference = pawn)
		{
			Features::Debug::playerController.pawn.className = pawn->Class->GetFullName();
			Features::Debug::playerController.pawn.objectName = pawn->GetFullName();

			Features::Debug::playerController.pawn.transform = Unreal::Actor::GetTransform(pawn);

			Features::Debug::playerController.pawn.isControlled = pawn->IsControlled();
			Features::Debug::playerController.pawn.isPawnControlled = pawn->IsPawnControlled();
			Features::Debug::playerController.pawn.isPlayerControlled = pawn->IsPlayerControlled();
			Features::Debug::playerController.pawn.isLocallyControlled = pawn->IsLocallyControlled();
			Features::Debug::playerController.pawn.isBotControlled = pawn->IsBotControlled();
		}


		SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
		if (Features::Debug::playerController.cameraManager.reference = cameraManager)
		{
			Features::Debug::playerController.cameraManager.className = cameraManager->Class->GetFullName();
			Features::Debug::playerController.cameraManager.objectName = cameraManager->GetFullName();

			Features::Debug::playerController.cameraManager.transform = Unreal::Actor::GetTransform(cameraManager);
		}


		SDK::UCheatManager* cheatManager = playerController->CheatManager;
		if (Features::Debug::playerController.cheatManager.reference = cheatManager)
		{
			Features::Debug::playerController.cheatManager.className = cheatManager->Class->GetFullName();
			Features::Debug::playerController.cheatManager.objectName = cheatManager->GetFullName();
		}
	}


	SDK::UWorld* world = SDK::UWorld::GetWorld();
	if (Features::Debug::world.reference = world)
	{
		Features::Debug::world.className = world->Class->GetFullName();
		Features::Debug::world.objectName = world->GetFullName();

		if (SDK::AGameStateBase* gameState = world->GameState)
		{
			Features::Debug::world.gameState.reference = gameState;

			Features::Debug::world.gameState.className = gameState->Class->GetFullName();
			Features::Debug::world.gameState.objectName = gameState->GetFullName();
		}

		if (SDK::UNetDriver* netDriver = world->NetDriver)
		{
			Features::Debug::world.netDriver.reference = netDriver;

			Features::Debug::world.netDriver.className = netDriver->Class->GetFullName();
			Features::Debug::world.netDriver.objectName = netDriver->GetFullName();
		}

		if (SDK::UNetDriver* demoNetDriver = world->NetDriver)
		{
			Features::Debug::world.demoNetDriver.reference = demoNetDriver;

			Features::Debug::world.demoNetDriver.className = demoNetDriver->Class->GetFullName();
			Features::Debug::world.demoNetDriver.objectName = demoNetDriver->GetFullName();
		}

		if (SDK::ULevel* persistentLevel = world->PersistentLevel)
		{
			Features::Debug::world.persistentLevel.reference = persistentLevel;

			Features::Debug::world.persistentLevel.className = persistentLevel->Class->GetFullName();
			Features::Debug::world.persistentLevel.objectName = persistentLevel->GetFullName();

			Features::Debug::world.persistentLevel.isVisible = persistentLevel->bIsVisible;

			if (SDK::AWorldSettings* worldSettings = persistentLevel->WorldSettings)
			{
				Features::Debug::world.persistentLevel.worldSettings.reference = worldSettings;
				Features::Debug::world.persistentLevel.worldSettings.className = worldSettings->Class->GetFullName();
				Features::Debug::world.persistentLevel.worldSettings.objectName = worldSettings->GetFullName();

				Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
				Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

				Features::Debug::world.persistentLevel.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
			}
		}

		SDK::TArray<SDK::ULevelStreaming*> streamingLevels = world->StreamingLevels;
		if (streamingLevels.Num() > 0)
		{
			Features::Debug::world.streamingLevels.clear();

			for (SDK::ULevelStreaming* streamingLevel : streamingLevels)
			{
				if (streamingLevel == nullptr)
					continue;

#ifdef UE5
				std::string streamingLevelPath = streamingLevel->WorldAsset.ObjectID.AssetPath.AssetName.GetRawString();
#else
				std::string streamingLevelPath = streamingLevel->WorldAsset.ObjectID.AssetPathName.GetRawString();
#endif
				if (streamingLevelPath.empty())
					continue;

				Unreal::LevelStreaming::DataStructure levelStreamingData = {};

				levelStreamingData.reference = streamingLevel;
				levelStreamingData.className = streamingLevel->Class->GetFullName();
				levelStreamingData.objectName = streamingLevel->GetFullName();

				levelStreamingData.levelPath = streamingLevelPath;
				levelStreamingData.levelColor = streamingLevel->LevelColor;

				SDK::ULevel* loadedLevel = streamingLevel->LoadedLevel;
				if (levelStreamingData.level.reference = loadedLevel)
				{
					levelStreamingData.level.className = loadedLevel->Class->GetFullName();
					levelStreamingData.level.objectName = loadedLevel->GetFullName();

					levelStreamingData.level.isVisible = loadedLevel->bIsVisible;

					SDK::AWorldSettings* worldSettings = loadedLevel->WorldSettings;
					if (levelStreamingData.level.worldSettings.reference = worldSettings)
					{
						levelStreamingData.level.worldSettings.className = worldSettings->Class->GetFullName();
						levelStreamingData.level.worldSettings.objectName = worldSettings->GetFullName();

						levelStreamingData.level.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
						levelStreamingData.level.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

						levelStreamingData.level.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
					}
				}

				Features::Debug::world.streamingLevels.push_back(levelStreamingData);
			}
		}

		Features::Debug::world.gameTimeInSeconds = SDK::UKismetSystemLibrary::GetGameTimeInSeconds(world);

		Features::Debug::world.isServer = SDK::UKismetSystemLibrary::IsServer(world);
		Features::Debug::world.isDedicatedServer = SDK::UKismetSystemLibrary::IsDedicatedServer(world);
		Features::Debug::world.isSplitScreen = SDK::UKismetSystemLibrary::IsSplitScreen(world);
		Features::Debug::world.isStandalone = SDK::UKismetSystemLibrary::IsStandalone(world);
	}


	if (Features::Debug::wasProjectNameObtained == false)
	{
		std::string projectName = SDK::UKismetSystemLibrary::GetGameName().ToString();
		if (projectName.empty() == false)
		{
			Features::Debug::projectName = projectName;
			Features::Debug::wasProjectNameObtained = true;
		}
	}


	if (Features::Debug::wasProjectPlatformObtained == false)
	{
		std::string projectPlatform = SDK::UGameplayStatics::GetPlatformName().ToString();
		if (projectPlatform.empty() == false)
		{
			Features::Debug::projectPlatform = projectPlatform;
			Features::Debug::wasProjectPlatformObtained = true;
		}
	}


	if (Features::Debug::wasProjectEngineVersionObtained == false)
	{
		std::string engineVersion = SDK::UKismetSystemLibrary::GetEngineVersion().ToString();
		if (engineVersion.empty() == false)
		{
			Features::Debug::projectEngineVersion = engineVersion;
			Features::Debug::wasProjectEngineVersionObtained = true;
		}
	}


	if (Features::Debug::wasUsernameObtained == false)
	{
		std::string username = SDK::UKismetSystemLibrary::GetPlatformUserName().ToString();
		if (username.empty() == false)
		{
			Features::Debug::username = username;
			Features::Debug::wasUsernameObtained = true;
		}
	}


	if (Features::Debug::wasCommandLineObtained == false)
	{
		LPWSTR lCommandLine = GetCommandLineW();
		std::wstring wCommandLine = std::wstring(lCommandLine);
		std::string commandLine = std::string(wCommandLine.begin(), wCommandLine.end());

		Features::Debug::commandLine = commandLine;
		Features::Debug::wasCommandLineObtained = true;
	}


	Features::Debug::lastUpdateTime = ImGui::GetTime();
}

void Features::Debug::ThreadSafeUpdate()
{
	__try
	{
		Features::Debug::Update();
	}
	__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)) {}
}




void Features::ActorsList::Update()
{
	Features::ActorsList::actors.clear();

	std::vector<SDK::AActor*> foundActors = Unreal::Actor::GetAll();
	for (SDK::AActor* actor : foundActors)
	{
		Unreal::Actor::DataStructure actorData = {};

		actorData.reference = actor;

		Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(actor);
		actorData.className = classHierarchy.derivedClass->GetFullName();
		for (SDK::UClass* superClass : classHierarchy.superClasses)
		{
			actorData.superClassesNames.push_back(superClass->GetFullName());
		}

		actorData.objectName = actor->GetFullName();

#ifdef ACTOR_KIND
		actorData.kind = Unreal::Actor::GetActorKind(actor);
#endif

		actorData.transform = Unreal::Actor::GetTransform(actor);

		std::vector<SDK::UActorComponent*> foundComponents = Unreal::ActorComponent::GetAll(actor);
		for (SDK::UActorComponent* component : foundComponents)
		{
			Unreal::ActorComponent::DataStructure componentData = {};

			componentData.reference = component;
			componentData.className = component->Class->GetFullName();
			componentData.objectName = component->GetFullName();

			componentData.isActive = component->bIsActive;
			componentData.autoActivate = component->bAutoActivate;
			componentData.editorOnly = component->bIsEditorOnly;

			componentData.netAddressible = component->bNetAddressable;
			componentData.replicates = component->bReplicates;

			componentData.creationMethod = component->CreationMethod;

			actorData.components.push_back(componentData);
		}

		Features::ActorsList::actors.push_back(actorData);
	}
}

void Features::ActorsList::Filter()
{
	/* Filter Actors by "Search Filter" */
	switch (Features::ActorsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassAndObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
			break;
	}
}




void Features::WidgetsList::Update()
{
	Features::WidgetsList::widgets.clear();

	std::vector<SDK::UUserWidget*> foundWidgets = Unreal::UserWidget::GetAll();
	for (SDK::UUserWidget* widget : foundWidgets)
	{
		Unreal::UserWidget::DataStructure widgetData = {};

		widgetData.reference = widget;
		widgetData.className = widget->Class->GetFullName();
		widgetData.objectName = widget->GetFullName();

		widgetData.parent = widget->GetParent();

		widgetData.isInViewport = widget->IsInViewport();
		widgetData.visibility = widget->Visibility;

		Features::WidgetsList::widgets.push_back(widgetData);
	}
}

void Features::WidgetsList::Filter()
{
	/* Filter User Widgets by "Search Filter" */
	switch (Features::WidgetsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassAndObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
			break;
	}
}




void Features::ObjectsList::Update()
{
	Features::ObjectsList::objects.clear();

	static const std::vector<SDK::TSubclassOf<SDK::UObject>> excludeClasses =
	{
		SDK::AActor::StaticClass(), // Actors List.
		SDK::UActorComponent::StaticClass(), // Actors List -> Actor -> Components.
		SDK::UUserWidget::StaticClass() // Widgets List.
	};
	std::vector<SDK::UObject*> foundObjects = Unreal::Object::GetAll(excludeClasses);
	for (SDK::UObject* object : foundObjects)
	{
		Unreal::Object::DataStructure objectData = {};

		objectData.reference = object;

		Unreal::Class::Hierarchy classHierarchy = Unreal::Class::GetClassHierarchy(object);
		objectData.className = classHierarchy.derivedClass->GetFullName();
		for (SDK::UClass* superClass : classHierarchy.superClasses)
		{
			objectData.superClassesNames.push_back(superClass->GetFullName());
		}

		objectData.objectName = object->GetFullName();

		Features::ObjectsList::objects.push_back(objectData);
	}
}

void Features::ObjectsList::Filter()
{
	/* Filter Objects by "Search Filter" */
	switch (Features::ObjectsList::filterMode)
	{
		case ImGui::E_ObjectFilterMode::ClassName:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByClassName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;

		case ImGui::E_ObjectFilterMode::ObjectName:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByObjectName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;

		case ImGui::E_ObjectFilterMode::All:
			Features::ObjectsList::filteredObjects = Unreal::Object::FilterByClassAndObjectName(Features::ObjectsList::objects, Features::ObjectsList::filterBuffer, Features::ObjectsList::filterCaseSensitive);
			break;
	}
}




void Features::CharacterMovement::Ghost()
{
	GUI::PlayActionSound(Unreal::Character::Ghost(0));
}

void Features::CharacterMovement::Fly()
{
	GUI::PlayActionSound(Unreal::Character::Fly(0));
}

void Features::CharacterMovement::Walk()
{
	GUI::PlayActionSound(Unreal::Character::Walk(0));
}




void Features::CharacterMovement::Jump()
{
	GUI::PlayActionSound(Unreal::Character::Jump(0));
}




void Features::CharacterMovement::Launch()
{
	GUI::PlayActionSound(Unreal::Character::Launch(0, { Features::CharacterMovement::launchVelocity[0], Features::CharacterMovement::launchVelocity[1], Features::CharacterMovement::launchVelocity[2] }));
}

void Features::CharacterMovement::Dash()
{
	SDK::ACharacter* character = Unreal::Character::Get();
	if (character == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FVector forwardVector = character->GetActorForwardVector();

	/* Dash shouldn't involve any vertical movement. */
	forwardVector.Z = 0.0;
	forwardVector.Normalize();

	SDK::FVector launchVelocity = forwardVector * Features::CharacterMovement::dashStrength;
	GUI::PlayActionSound(Unreal::Character::Launch(character, launchVelocity));
}




void Features::Camera::StartFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FLinearColor fadeColor;
	fadeColor.R = Features::Camera::fadeColor[0];
	fadeColor.G = Features::Camera::fadeColor[1];
	fadeColor.B = Features::Camera::fadeColor[2];
	fadeColor.A = Features::Camera::fadeColor[3];

	playerController->PlayerCameraManager->StartCameraFade(Features::Camera::fadeFromAlpha, Features::Camera::fadeToAlpha, Features::Camera::fadeDuration, fadeColor, Features::Camera::fadeAudio, Features::Camera::fadePersistent);
	GUI::PlayActionSound(true);
}

void Features::Camera::StopFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	playerController->PlayerCameraManager->StopCameraFade();
	GUI::PlayActionSound(true);
}




void Features::DirectionalMovement::Worker()
{
	while (Features::DirectionalMovement::enabled)
	{
		__try
		{
			/* See if we have a Player Controller alongside the Camera Manager. */
			SDK::APlayerController* playerController = Unreal::PlayerController::Get();
			if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
				continue;

			/* See if we have a Character under control and verify that Character is cheat flying. */
			SDK::ACharacter* character = playerController->Character;
			if (character == nullptr || character->CharacterMovement == nullptr || character->CharacterMovement->bCheatFlying != true)
				continue;

			/* Get Character velocity and see if we have any horizontal movement. */
			SDK::FVector characterVelocity = character->CharacterMovement->Velocity;
			if (Features::DirectionalMovement::omniMovement == false)  // For Omni-Movement Up & Down Keybindings we need to get past that check.
			{
				if (characterVelocity.X == 0.0 && characterVelocity.Y == 0.0)
					continue;
			}
			
			/* Normalize Character velocity (-1.0 to 1.0) and get Camera forward vector. */
			SDK::FVector characterVelocityNormalized = Math::Vector_Normal(characterVelocity);
			SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();

			bool movementExpected = false;
			SDK::FVector movementDirection = { 0.0f, 0.0f, 0.0f };

			/*
				Compute the dot product of the normalized character velocity and the camera's forward vector.
				Result interpretation:
				  +1.0 -> character moves exactly forward,
				  -1.0 -> character moves exactly backward,
				   0.0 -> movement is perpendicular to the camera.
			*/
			double dotForward = Math::Vector_Dot(characterVelocityNormalized, cameraForwardVector);
			if (dotForward > 0.5f) // Check if Ñharacter is attempting to move forward relative to the camera.
			{
				movementExpected = true;
				movementDirection = cameraForwardVector;
			}

			/* Handle multi-directional movement (Backward, Left, Right) if Omni-Movement is enabled. */
			if (Features::DirectionalMovement::omniMovement)
			{
				if (movementExpected == false && dotForward < -0.5f) // Check for backward movement (dot product is negative) if not already moving forward.
				{
					movementExpected = true;
					movementDirection = cameraForwardVector * -1.0f;
				}

				/* Retrieve the Camera right vector to calculate strafing. */
				SDK::FVector cameraRightVector = playerController->PlayerCameraManager->GetActorRightVector();
				double dotRight = Math::Vector_Dot(characterVelocityNormalized, cameraRightVector);

				if (dotRight > 0.5f) // Check if Character is strafing right.
				{
					movementExpected = true;
					movementDirection = Math::Vector_Add(movementDirection, cameraRightVector);
				}
				else if (dotRight < -0.5f) // Check if Character is strafing left
				{
					movementExpected = true;
					movementDirection = Math::Vector_Add(movementDirection, cameraRightVector * -1.0f);
				}

				if (Features::DirectionalMovement::isUpMovementExpected || Features::DirectionalMovement::isDownMovementExpected)
				{
					SDK::FVector characterUpVector = character->GetActorUpVector();
					if (Features::DirectionalMovement::isUpMovementExpected)
					{
						movementExpected = true;
						movementDirection = Math::Vector_Add(movementDirection, characterUpVector);
					}
					else if (Features::DirectionalMovement::isDownMovementExpected)
					{
						movementExpected = true;
						movementDirection = Math::Vector_Add(movementDirection, characterUpVector * -1.0f);
					}
				}
			}

			if (movementExpected)
			{
				/* Normalize the final accumulated direction vector to ensure consistent speed (account for forward/backward and strafing movement double speed). */
				SDK::FVector finalDirection = Math::Vector_Normal(movementDirection);

				/* Calculate the target location based on the current location, direction, and step size. */
				SDK::FVector currentLocation = character->K2_GetActorLocation();
				SDK::FVector finalLocation = Math::Vector_Add(currentLocation, finalDirection * Features::DirectionalMovement::step);

				Unreal::Actor::SweepTo(character, finalLocation);
			}
		}
		__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)) {}

		/* Sleep for a defined delay to control the update rate (tick) of the movement logic. */
		Sleep(Math::Seconds_ToMilliseconds(Features::DirectionalMovement::delay));
	}
}


void Features::DirectionalMovement::Enable()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Features::DirectionalMovement::Worker, 0, 0, 0);
	}
}

void Features::DirectionalMovement::Disable()
{
	if (thread)
	{
		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
	}
}




bool Features::Positions::ReadPositionFromConfig(ConfigInstance* positionsConfig, const int& positionId, Positions::PositionEntry* positionEntry)
{
	if (positionsConfig == nullptr || positionEntry == nullptr)
		return false;

	std::string entryName_Base = Positions::entryPrefix + std::to_string(positionId);
	std::string entryName_Title = entryName_Base + Positions::entryTitleSuffix;
	std::string entryName_Location = entryName_Base + Positions::entryLocationSuffix;
	std::string entryName_Rotation = entryName_Base + Positions::entryRotationSuffix;

	if (positionsConfig->HasKey(entryName_Title) == false || positionsConfig->HasKey(entryName_Location) == false)
		return false;

	positionEntry->title = positionsConfig->Get<std::string>(entryName_Title).value_or(std::string());
	positionEntry->location = positionsConfig->Get<SDK::FVector>(entryName_Location).value_or(SDK::FVector());
	SDK::FVector vRotation = positionsConfig->Get<SDK::FVector>(entryName_Rotation).value_or(SDK::FVector());
	positionEntry->rotation = SDK::FRotator(vRotation.X, vRotation.Y, vRotation.Z);

	return true;
}

void Features::Positions::Load()
{
	ConfigInstance positionsConfig(PATH_CONFIG_POSITIONS);
	if (positionsConfig.Load() == false)
	{
		Features::Positions::Save();
		positionsConfig.Load();
	}

	std::vector<Positions::PositionEntry> outVector;
	for (int32_t i = 0; i < Features::Positions::entriesLimit; i++)
	{
		Positions::PositionEntry entry{};
		if (ReadPositionFromConfig(&positionsConfig, i, &entry) == false)
			break;

		outVector.push_back(entry);
	}

	Positions::entries = outVector;
}

void Features::Positions::Save()
{
	ConfigInstance positionsConfig(PATH_CONFIG_POSITIONS);

	int32_t entriesCount = Positions::entries.size();
	for (int32_t i = 0; i < entriesCount; i++)
	{
		std::string entryName_Base = Positions::entryPrefix + std::to_string(i);
		std::string entryName_Title = entryName_Base + Positions::entryTitleSuffix;
		std::string entryName_Location = entryName_Base + Positions::entryLocationSuffix;
		std::string entryName_Rotation = entryName_Base + Positions::entryRotationSuffix;

		positionsConfig.Set(entryName_Title, entries[i].title);
		positionsConfig.Set(entryName_Location, entries[i].location);
		SDK::FRotator rotation = entries[i].rotation;
		positionsConfig.Set(entryName_Rotation, SDK::FVector(rotation.Pitch, rotation.Yaw, rotation.Roll));
	}

	positionsConfig.Save();
}




#ifdef ACTOR_TRACE
bool Features::ActorTrace::Trace()
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
		return false;

	SDK::FVector cameraLocation = playerController->PlayerCameraManager->K2_GetActorLocation();
	SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();
	SDK::FVector traceEndLocation = cameraLocation + (cameraForwardVector * Features::ActorTrace::traceLength);

	SDK::TArray<SDK::AActor*> actorsToIgnore;
	if (SDK::ACharacter* character = Unreal::Character::Get())
		actorsToIgnore.Add(character);

	SDK::FHitResult hitResult;
	Features::ActorTrace::traceHit = SDK::UKismetSystemLibrary::LineTraceSingle(world, cameraLocation, traceEndLocation, SDK::ETraceTypeQuery::TraceTypeQuery1, false, actorsToIgnore, SDK::EDrawDebugTrace::ForDuration, &hitResult, true, SDK::FLinearColor(), SDK::FLinearColor(), 5.0f);
	if (traceHit)
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = hitResult.Location;

#ifdef UE5
		/* UE 5.3.2 and older: hitResult.HitObjectHandle.Actor.Get() */
		SDK::UObject* hitObject = hitResult.HitObjectHandle.ReferenceObject.Get();
		if (hitObject)
		{

			Features::ActorTrace::object.reference = hitObject;
			Features::ActorTrace::object.className = hitObject->Class->GetFullName();
			Features::ActorTrace::object.objectName = hitObject->GetFullName();

			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] " + Features::ActorTrace::object.objectName);
		}
		else
		{
			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] Didn't hit any object.");
		}
#else
		SDK::AActor* hitActor = hitResult.Actor.Get();
		if (hitActor)
		{

			Features::ActorTrace::actor.reference = hitActor;
			Features::ActorTrace::actor.className = hitActor->Class->GetFullName();
			Features::ActorTrace::actor.objectName = hitActor->GetFullName();

			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] " + Features::ActorTrace::actor.objectName);
		}
		else
		{
			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] Didn't hit any actor.");
		}
#endif
	}
	else
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = traceEndLocation;
	}

	Features::ActorTrace::traceCast = true;
	return true;
}


void Features::ActorTrace::Draw()
{
	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList)
	{
		if (Features::ActorTrace::showOnScreen)
		{
			ImGui::Viewport viewport = ImGui::GetViewport();

#ifdef UE5
			const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::object.objectName.c_str() : "No Object Traced";
#else
			const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::actor.objectName.c_str() : "No Actor Traced";
#endif
			ImVec2 labelSize = ImGui::CalcTextSize(labelText);
			ImVec2 labelPosition = ImVec2
			(
				/*
					Horizontal: ImGui Viewport center;
					Vertical: ImGui Viewport bottom - 12 pixels.

					Flooring the values allows to avoid potential subpixel conflicts.
				*/
				floorf(viewport.iViewportSize.x + (viewport.iViewportSize.x - labelSize.x) * 0.5f),
				floorf(viewport.iViewportSize.y - labelSize.y - 12.0f)
			);

			drawList->AddText(labelPosition, ImGui::GetColorU32(ImGuiCol_Text), labelText);
		}

		if (Features::ActorTrace::showLineTrace && Features::ActorTrace::traceCast)
		{
			SDK::FVector2D screenStartPosition;
			SDK::FVector2D screenEndPosition;

			/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
			SDK::APlayerController* playerController = Unreal::PlayerController::Get();
			bool startPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceStartLocation, &screenStartPosition, false);
			bool endPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceEndLocation, &screenEndPosition, false);

			/* Inverse Normalize RGBA values set by color picker. */
			ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(Features::ActorTrace::traceColor[0], Features::ActorTrace::traceColor[1], Features::ActorTrace::traceColor[2], Features::ActorTrace::traceColor[3]));

			static float traceStartCircleRadius;
			if (startPositionProjected)
				traceStartCircleRadius = Features::ActorTrace::traceThickness * 1.5f;

			static float traceEndCircleRadius;
			static float traceCrossSize;
			if (endPositionProjected)
			{
				traceEndCircleRadius = Features::ActorTrace::traceThickness * 1.75f;
				traceCrossSize = 8.0f + (Features::ActorTrace::traceThickness * 0.5f);
			}

			/* Both start and end position are within player view. */
			if (startPositionProjected && endPositionProjected)
			{
				ImVec2 startPosition = { (float)screenStartPosition.X, (float)screenStartPosition.Y };
				ImVec2 endPosition = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				/* Draw the trace. */
				drawList->AddLine(startPosition, endPosition, color, Features::ActorTrace::traceThickness);

				/* Draw a hollow circle to mark position where trace was sent from. */
				drawList->AddCircle(startPosition, traceStartCircleRadius, color);

				/*
					If trace has hit something, draw a cross to mark position where the trace hit;
					Otherwise draw a filled circle to mark position where the trace ends.
				*/
				if (Features::ActorTrace::traceHit)
				{
					drawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y - traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					drawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y + traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					drawList->AddCircleFilled(endPosition, traceEndCircleRadius, color);
			}
			/* Only start position is within player view. */
			else if (startPositionProjected)
			{
				ImVec2 position = { (float)screenStartPosition.X, (float)screenStartPosition.Y };

				drawList->AddCircle(position, traceStartCircleRadius, color);
			}
			/* Only end position is within player view. */
			else if (endPositionProjected)
			{
				ImVec2 position = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				if (Features::ActorTrace::traceHit)
				{
					drawList->AddLine({ position.x - traceCrossSize, position.y - traceCrossSize }, { position.x + traceCrossSize, position.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					drawList->AddLine({ position.x - traceCrossSize, position.y + traceCrossSize }, { position.x + traceCrossSize, position.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					drawList->AddCircleFilled(position, traceEndCircleRadius, color);
			}
		}
	}
}

void Features::ActorTrace::ThreadSafeDraw()
{
	__try
	{
		Features::ActorTrace::Draw();
	}
	__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)) {}
}
#endif




#ifdef ACTORS_TRACKING
void Features::ActorsTracker::Draw()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController)
	{
		ImDrawList* drawList = ImGui::GetDrawList();
		if (drawList)
		{
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				SDK::FVector2D screenPosition;
				if (SDK::UGameplayStatics::ProjectWorldToScreen(playerController, actor.transform.location, &screenPosition, false))
				{
					ImU32 color;
					if (Features::ActorsList::filterCheckValidness)
						color = Math::ColorFloat4_ToU32(Unreal::Actor::IsValid(actor.reference) ? Features::ActorsList::color_Valid : Features::ActorsList::color_Invalid);
					else
						color = IM_COL32(255, 255, 255, 255);

					drawList->AddCircleFilled({ (float)screenPosition.X, (float)screenPosition.Y }, 8.0f, color);

					const char* labelText = actor.objectName.c_str();
					ImVec2 labelSize = ImGui::CalcTextSize(labelText);
					ImVec2 labelPosition = ImVec2
					(
						/* Flooring the values allows to avoid potential subpixel conflicts. */
						floorf(screenPosition.X - (labelSize.x * 0.5)),
						floorf(screenPosition.Y - 32.0f)
					);

					drawList->AddText(labelPosition, color, labelText);
				}
			}
		}
	}
}

void Features::ActorsTracker::ThreadSafeDraw()
{
	__try
	{
		Features::ActorsTracker::Draw();
	}
	__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)) {}
}
#endif




#ifdef COLLISION_VISUALIZER
void Features::CollisionVisualizer::Draw()
{
	/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController)
	{
		SDK::FVector playerLocation = Unreal::PlayerController::GetLocation(0);
	
		for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
		{
			if (actor.reference == nullptr)
				continue;
	
			if (actor.reference->IsA(SDK::AVolume::StaticClass()))
			{
				if (actor.reference->IsA(SDK::APhysicsVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_PhysicsVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::ABlockingVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_BlockingVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::ATriggerVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_TriggerVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				if (actor.reference->IsA(SDK::APostProcessVolume::StaticClass()))
				{
					DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_PostProcessVolume), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				DebugDraw::DrawVolume(static_cast<SDK::AVolume*>(actor.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Other), Features::CollisionVisualizer::thickness);
				continue;
			}
	
	
			for (Unreal::ActorComponent::DataStructure& actorComponent : actor.components) // <-- Reference!
			{
				if (actorComponent.reference == nullptr)
					continue;
	
				/* #1 Static Mesh. */
				if (actorComponent.reference->IsA(SDK::UStaticMeshComponent::StaticClass()))
				{
					DebugDraw::DrawStaticMeshComponent(static_cast<SDK::UStaticMeshComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_StaticMesh), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #2 Instanced Static Mesh. */
				if (actorComponent.reference->IsA(SDK::UInstancedStaticMeshComponent::StaticClass()))
				{
					DebugDraw::DrawInstancedStaticMeshComponent(static_cast<SDK::UInstancedStaticMeshComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_StaticMesh), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #3 Skeletal Mesh. */
				if (actorComponent.reference->IsA(SDK::USkeletalMeshComponent::StaticClass()))
				{
					DebugDraw::DrawSkeletalMeshComponent(static_cast<SDK::USkeletalMeshComponent*>(actorComponent.reference), false, Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Other), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #4 Capsule Component. */
				if (actorComponent.reference->IsA(SDK::UCapsuleComponent::StaticClass()))
				{
					DebugDraw::DrawCapsuleComponent(static_cast<SDK::UCapsuleComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #5 Sphere Component. */
				if (actorComponent.reference->IsA(SDK::USphereComponent::StaticClass()))
				{
					DebugDraw::DrawSphereComponent(static_cast<SDK::USphereComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #6 Box Component. */
				if (actorComponent.reference->IsA(SDK::UBoxComponent::StaticClass()))
				{
					DebugDraw::DrawBoxComponent(static_cast<SDK::UBoxComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
	
				/* #1 Spline Component. */
				if (actorComponent.reference->IsA(SDK::USplineComponent::StaticClass()))
				{
					DebugDraw::DrawSplineComponent(static_cast<SDK::USplineComponent*>(actorComponent.reference), Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Primitive), Features::CollisionVisualizer::thickness);
					continue;
				}
			}
		}
	}
}

void Features::CollisionVisualizer::ThreadSafeDraw()
{
	__try
	{
		Features::CollisionVisualizer::Draw();
	}
	__except (Utilities::Exception::Handle(GetExceptionInformation(), __FUNCSIG__)) {}
}
#endif




#ifdef FREE_CAMERA
bool Features::FreeCamera::IsEnabled()
{
	if (Features::FreeCamera::cameraReference == nullptr)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::AActor* viewTarget = playerController->GetViewTarget();
	if (viewTarget == nullptr)
		return false;

	return Features::FreeCamera::cameraReference == viewTarget;
}

bool Features::FreeCamera::Enable()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	if (Unreal::Actor::IsValid(Features::FreeCamera::cameraReference) == false)
	{
		SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::ACameraActor::StaticClass());
		if (actorReference == nullptr)
			return false;

		Features::FreeCamera::cameraReference = static_cast<SDK::ACameraActor*>(actorReference);
	}

	if (playerController->PlayerCameraManager)
	{
		SDK::APlayerCameraManager* playerCameraManager = playerController->PlayerCameraManager;
		Unreal::Transform playerCameraTransform = Unreal::Actor::GetTransform(playerCameraManager);

		Features::FreeCamera::cameraReference->SetActorEnableCollision(false);
		Features::FreeCamera::cameraReference->FOVAngle = 83.0f;

		Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, playerCameraTransform.location, playerCameraTransform.rotation);
	}

	if (Features::FreeCamera::lastViewTarget = playerController->GetViewTarget())
	{
		Features::FreeCamera::lastViewTargetCustomTimeDilation = Features::FreeCamera::lastViewTarget->CustomTimeDilation;
		Features::FreeCamera::lastViewTarget->CustomTimeDilation = 0.0f;
	}

	Unreal::PlayerController::SetViewTarget(Features::FreeCamera::cameraReference);
	return true;
}

bool Features::FreeCamera::Disable()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	if (Features::FreeCamera::lastViewTarget != nullptr)
	{
		Features::FreeCamera::lastViewTarget->CustomTimeDilation = Features::FreeCamera::lastViewTargetCustomTimeDilation;
		Unreal::PlayerController::SetViewTarget(Features::FreeCamera::lastViewTarget);

		Features::FreeCamera::lastViewTarget = nullptr;
		return true;
	}
	else if (playerController->Pawn != nullptr)
	{
		Unreal::PlayerController::SetViewTarget(playerController->Pawn);
		return true;
	}
	else
		return false;
}

void Features::FreeCamera::Toggle()
{
	if (IsEnabled() == false)
	{
		Enable();
		GUI::PlayActionSound(true);
	}
	else
	{
		Disable();
		GUI::PlayActionSound(false);
	}
}


bool Features::FreeCamera::Move(const float& forwardStep, const float& rightStep, const float& upStep)
{
	if (IsEnabled() == false)
		return false;

	Unreal::Transform freeCameraTransform = Unreal::Actor::GetTransform(Features::FreeCamera::cameraReference);
	SDK::FVector forwardVector = Math::Rotator_ForwardVector(freeCameraTransform.rotation);
	SDK::FVector rightVector = Math::Rotator_RightVector(freeCameraTransform.rotation);
	SDK::FVector upVector = Math::Rotator_UpVector(freeCameraTransform.rotation);

	SDK::FVector locationOffset;
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(forwardVector, forwardStep));
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(rightVector, rightStep));
	locationOffset = Math::Vector_Add(locationOffset, Math::Vector_Multiply(upVector, upStep));

	SDK::FVector newLocation = Math::Vector_Add(freeCameraTransform.location, locationOffset);
	return Unreal::Actor::SweepTo(Features::FreeCamera::cameraReference, newLocation);
}

bool Features::FreeCamera::Rotate(const float& horizontalStep, const float& verticalStep)
{
	if (IsEnabled() == false)
		return false;

	SDK::FRotator freeCameraRotation = Features::FreeCamera::cameraReference->K2_GetActorRotation();
	freeCameraRotation.Yaw += horizontalStep;

	float newPitch = freeCameraRotation.Pitch + verticalStep;
	freeCameraRotation.Pitch = std::clamp(newPitch, -89.0f, 89.0f);

	freeCameraRotation.Roll = 0.0f;

	return Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, freeCameraRotation);
}


bool Features::FreeCamera::TeleportCameraToPlayer()
{
	if (IsEnabled() == false)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return false;

	SDK::FVector playerLocation;
	if (Features::FreeCamera::lastViewTarget != nullptr)
		playerLocation = Features::FreeCamera::lastViewTarget->K2_GetActorLocation();
	else if (playerController->Pawn != nullptr)
		playerLocation = playerController->Pawn->K2_GetActorLocation();
	else
		return false;

	return Unreal::Actor::TeleportTo(Features::FreeCamera::cameraReference, playerLocation);
}

bool Features::FreeCamera::TeleportPlayerToCamera()
{
	if (IsEnabled() == false)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->Pawn == nullptr)
		return false;

	SDK::FVector cameraLocation = Features::FreeCamera::cameraReference->K2_GetActorLocation();
	return Unreal::Actor::TeleportTo(playerController->Pawn, cameraLocation);
}
#endif






// ==============================
// |          #Inputs			|
// ==============================
void Inputs::Config::ReadKeyBindingFromConfig(ConfigInstance* keybindingsConfig, const std::string& entryName, ImGui::KeyBinding* keyBinding)
{
	if (keybindingsConfig == nullptr || keyBinding == nullptr)
		return;

	if (keybindingsConfig->HasKey(entryName) == false)
		return;

	keyBinding->key = static_cast<ImGuiKey>(keybindingsConfig->Get<int>(entryName).value_or((int)keyBinding->key));
}

void Inputs::Config::Load()
{
	ConfigInstance keybindingsConfig(PATH_CONFIG_KEYBINDINGS);
	if (keybindingsConfig.Load() == false)
	{
		Inputs::Config::Save();
		keybindingsConfig.Load();
	}

	ReadKeyBindingFromConfig(&keybindingsConfig, "general_MenuOpenClose", &Inputs::Keybindings::general_MenuOpenClose);

#ifdef ACTOR_TRACE
	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorTrace", &Inputs::Keybindings::debug_ActorTrace);
#endif
	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListUpdate", &Inputs::Keybindings::debug_ActorsListUpdate);
#ifdef ACTORS_TRACKING
	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListTracking", &Inputs::Keybindings::debug_ActorsListTracking);
#endif
#ifdef COLLISION_VISUALIZER
	ReadKeyBindingFromConfig(&keybindingsConfig, "debug_ActorsListCollisionDraw", &Inputs::Keybindings::debug_ActorsListCollisionDraw);
#endif

	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Ghost", &Inputs::Keybindings::characterMovement_Ghost);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Fly", &Inputs::Keybindings::characterMovement_Fly);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Walk", &Inputs::Keybindings::characterMovement_Walk);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Jump", &Inputs::Keybindings::characterMovement_Jump);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Launch", &Inputs::Keybindings::characterMovement_Launch);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterMovement_Dash", &Inputs::Keybindings::characterMovement_Dash);

	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Up", &Inputs::Keybindings::characterOmniMovement_Up);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterOmniMovement_Down", &Inputs::Keybindings::characterOmniMovement_Down);
	
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterCamera_StartFade", &Inputs::Keybindings::characterCamera_StartFade);
	ReadKeyBindingFromConfig(&keybindingsConfig, "characterCamera_StopFade", &Inputs::Keybindings::characterCamera_StopFade);

#ifdef FREE_CAMERA
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_TeleportCameraToPlayer", &Inputs::Keybindings::freeCamera_TeleportCameraToPlayer);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_Toggle", &Inputs::Keybindings::freeCamera_Toggle);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_TeleportPlayerToCamera", &Inputs::Keybindings::freeCamera_TeleportPlayerToCamera);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveForward", &Inputs::Keybindings::freeCamera_MoveForward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveBackward", &Inputs::Keybindings::freeCamera_MoveBackward);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveLeft", &Inputs::Keybindings::freeCamera_MoveLeft);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveRight", &Inputs::Keybindings::freeCamera_MoveRight);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveUp", &Inputs::Keybindings::freeCamera_MoveUp);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_MoveDown", &Inputs::Keybindings::freeCamera_MoveDown);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateUp", &Inputs::Keybindings::freeCamera_RotateUp);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateDown", &Inputs::Keybindings::freeCamera_RotateDown);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateLeft", &Inputs::Keybindings::freeCamera_RotateLeft);
	ReadKeyBindingFromConfig(&keybindingsConfig, "freeCamera_RotateRight", &Inputs::Keybindings::freeCamera_RotateRight);
#endif
}

void Inputs::Config::Save()
{
	ConfigInstance keybindingsConfig(PATH_CONFIG_KEYBINDINGS);
	
	keybindingsConfig.Set("general_MenuOpenClose", static_cast<int>(Inputs::Keybindings::general_MenuOpenClose.key));

#ifdef ACTOR_TRACE
	keybindingsConfig.Set("debug_ActorTrace", static_cast<int>(Keybindings::debug_ActorTrace.key));
#endif
	keybindingsConfig.Set("debug_ActorsListUpdate", static_cast<int>(Inputs::Keybindings::debug_ActorsListUpdate.key));
#ifdef ACTORS_TRACKING
	keybindingsConfig.Set("debug_ActorsListTracking", static_cast<int>(Keybindings::debug_ActorsListTracking.key));
#endif
#ifdef COLLISION_VISUALIZER
	keybindingsConfig.Set("debug_ActorsListCollisionDraw", static_cast<int>(Keybindings::debug_ActorsListCollisionDraw.key));
#endif

	keybindingsConfig.Set("characterMovement_Ghost", static_cast<int>(Inputs::Keybindings::characterMovement_Ghost.key));
	keybindingsConfig.Set("characterMovement_Fly", static_cast<int>(Inputs::Keybindings::characterMovement_Fly.key));
	keybindingsConfig.Set("characterMovement_Walk", static_cast<int>(Inputs::Keybindings::characterMovement_Walk.key));
	keybindingsConfig.Set("characterMovement_Launch", static_cast<int>(Inputs::Keybindings::characterMovement_Launch.key));
	keybindingsConfig.Set("characterMovement_Dash", static_cast<int>(Inputs::Keybindings::characterMovement_Dash.key));

	keybindingsConfig.Set("characterOmniMovement_Up", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Up.key));
	keybindingsConfig.Set("characterOmniMovement_Down", static_cast<int>(Inputs::Keybindings::characterOmniMovement_Down.key));

	keybindingsConfig.Set("characterCamera_StartFade", static_cast<int>(Inputs::Keybindings::characterCamera_StartFade.key));
	keybindingsConfig.Set("characterCamera_StopFade", static_cast<int>(Inputs::Keybindings::characterCamera_StopFade.key));

#ifdef FREE_CAMERA
	keybindingsConfig.Set("freeCamera_TeleportCameraToPlayer", static_cast<int>(Keybindings::freeCamera_TeleportCameraToPlayer.key));
	keybindingsConfig.Set("freeCamera_Toggle", static_cast<int>(Keybindings::freeCamera_Toggle.key));
	keybindingsConfig.Set("freeCamera_TeleportPlayerToCamera", static_cast<int>(Keybindings::freeCamera_TeleportPlayerToCamera.key));
	keybindingsConfig.Set("freeCamera_MoveForward", static_cast<int>(Keybindings::freeCamera_MoveForward.key));
	keybindingsConfig.Set("freeCamera_MoveBackward", static_cast<int>(Keybindings::freeCamera_MoveBackward.key));
	keybindingsConfig.Set("freeCamera_MoveLeft", static_cast<int>(Keybindings::freeCamera_MoveLeft.key));
	keybindingsConfig.Set("freeCamera_MoveRight", static_cast<int>(Keybindings::freeCamera_MoveRight.key));
	keybindingsConfig.Set("freeCamera_MoveUp", static_cast<int>(Keybindings::freeCamera_MoveUp.key));
	keybindingsConfig.Set("freeCamera_MoveDown", static_cast<int>(Keybindings::freeCamera_MoveDown.key));
	keybindingsConfig.Set("freeCamera_RotateUp", static_cast<int>(Keybindings::freeCamera_RotateUp.key));
	keybindingsConfig.Set("freeCamera_RotateDown", static_cast<int>(Keybindings::freeCamera_RotateDown.key));
	keybindingsConfig.Set("freeCamera_RotateLeft", static_cast<int>(Keybindings::freeCamera_RotateLeft.key));
	keybindingsConfig.Set("freeCamera_RotateRight", static_cast<int>(Keybindings::freeCamera_RotateRight.key));
#endif

	keybindingsConfig.Save();
}




void Inputs::Keybindings::EnableProcessing()
{
	if (thread == nullptr)
	{
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Inputs::Keybindings::Worker, 0, 0, 0);
		isProcessing = thread;
	}
}

void Inputs::Keybindings::DisableProcessing()
{
	if (thread)
	{
		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);

		thread = nullptr;
		isProcessing = false;
	}
}

void Inputs::Keybindings::Worker()
{
	while (isProcessing)
	{
		/* Following inputs are only processed while title window is in focus. */
		if (GUI::GetIsTitleInFocus())
		{
			if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::general_MenuOpenClose))
				GUI::ToggleIsMenuActive();

			if (GUI::GetIsMenuActive() == false)
			{
#ifdef ACTOR_TRACE
				if (Features::ActorTrace::enabled)
				{
					if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorTrace))
					{
						GUI::PlayActionSound(Features::ActorTrace::Trace());
					}
				}
#endif

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListUpdate))
				{
					Features::ActorsList::Update();
					Features::ActorsList::Filter();

					GUI::PlayActionSound(true);
				}

#ifdef ACTORS_TRACKING
				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListTracking))
				{
					if (Features::ActorsTracker::enabled)
						Features::ActorsTracker::enabled = false;
					else
					{
						Features::ActorsList::Update();

						if (Features::ActorsList::filterDistance == 0.0f)
							Features::ActorsList::filterDistance = 2400.0f; // 24 meters.

						Features::ActorsList::Filter();

						Features::ActorsTracker::enabled = true;
					}

					GUI::PlayActionSound(true);
				}
#endif

#ifdef COLLISION_VISUALIZER
				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::debug_ActorsListCollisionDraw))
				{
					if (Features::CollisionVisualizer::enabled)
						Features::CollisionVisualizer::enabled = false;
					else
					{
						Features::ActorsList::Update();

						if (Features::ActorsList::filterDistance == 0.0f)
							Features::ActorsList::filterDistance = 2400.0f; // 24 meters.

						Features::ActorsList::Filter();

						Features::CollisionVisualizer::enabled = true;
					}

					GUI::PlayActionSound(true);
				}
#endif




				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Ghost))
				{
					Features::CharacterMovement::Ghost();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Fly))
				{
					Features::CharacterMovement::Fly();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Walk))
				{
					Features::CharacterMovement::Walk();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Jump))
				{
					Features::CharacterMovement::Jump();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Launch))
				{
					Features::CharacterMovement::Launch();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterMovement_Dash))
				{
					Features::CharacterMovement::Dash();
				}




				if (Features::DirectionalMovement::omniMovement)
				{
					Features::DirectionalMovement::isUpMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Up);
					Features::DirectionalMovement::isDownMovementExpected = ImGui::IsKeyBindingDown(&Inputs::Keybindings::characterOmniMovement_Down);
				}




				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterCamera_StartFade))
				{
					Features::Camera::StartFade();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::characterCamera_StopFade))
				{
					Features::Camera::StopFade();
				}




#ifdef FREE_CAMERA
				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_TeleportCameraToPlayer))
				{
					GUI::PlayActionSound(Features::FreeCamera::TeleportCameraToPlayer());
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_Toggle))
				{
					Features::FreeCamera::Toggle();
				}

				if (ImGui::IsKeyBindingPressed(&Inputs::Keybindings::freeCamera_TeleportPlayerToCamera))
				{
					GUI::PlayActionSound(Features::FreeCamera::TeleportPlayerToCamera());
				}

				if (Features::FreeCamera::cameraReference)
				{
					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveForward))
					{
						Features::FreeCamera::Move(Features::FreeCamera::cameraMovementStep, 0.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveBackward))
					{
						Features::FreeCamera::Move(Features::FreeCamera::cameraMovementStep * -1.0f, 0.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveLeft))
					{
						Features::FreeCamera::Move(0.0f, Features::FreeCamera::cameraMovementStep * -1.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveRight))
					{
						Features::FreeCamera::Move(0.0f, Features::FreeCamera::cameraMovementStep, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveUp))
					{
						Features::FreeCamera::Move(0.0f, 0.0f, Features::FreeCamera::cameraMovementStep);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_MoveDown))
					{
						Features::FreeCamera::Move(0.0f, 0.0f, Features::FreeCamera::cameraMovementStep * -1.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateUp))
					{
						Features::FreeCamera::Rotate(0.0f, Features::FreeCamera::cameraRotationStep);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateDown))
					{
						Features::FreeCamera::Rotate(0.0f, Features::FreeCamera::cameraRotationStep * -1.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateLeft))
					{
						Features::FreeCamera::Rotate(Features::FreeCamera::cameraRotationStep * -1.0f, 0.0f);
					}

					if (ImGui::IsKeyBindingDown(&Inputs::Keybindings::freeCamera_RotateRight))
					{
						Features::FreeCamera::Rotate(Features::FreeCamera::cameraRotationStep, 0.0f);
					}
				}
#endif
			}
		}

		Sleep(1);
	}
}






// ==============================
// |        #DebugDraw			|
// ==============================
#ifdef COLLISION_VISUALIZER
void DebugDraw::DrawBodySetup(SDK::UBodySetup* bodySetup, const Unreal::Transform& componentTransform, const uint32_t& drawColor, const float& drawThickness)
{
	if (bodySetup == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	for (SDK::FKConvexElem& convexElement : bodySetup->AggGeom.ConvexElems)
	{
		const SDK::TArray<SDK::FVector>& vertexData = convexElement.VertexData;
		const size_t vertexDataLength = vertexData.Num();
		if (vertexDataLength == 0)
			continue;

		const SDK::TArray<int32_t>& indexData = convexElement.IndexData;
		const size_t indexDataLength = indexData.Num();
		if (indexDataLength < 3 || indexDataLength % 3 != 0)
			continue;

		for (int32_t i = 0; i + 2 < indexDataLength; i += 3)
		{
			int32_t A_Index = indexData[i];
			int32_t B_Index = indexData[i + 1];
			int32_t C_Index = indexData[i + 2];

			if (A_Index < 0 || A_Index >= vertexDataLength ||
				B_Index < 0 || B_Index >= vertexDataLength ||
				C_Index < 0 || C_Index >= vertexDataLength)
				continue;

			if (A_Index == B_Index || B_Index == C_Index || C_Index == A_Index)
				continue;

			SDK::FVector A_Local = vertexData[A_Index];
			SDK::FVector B_Local = vertexData[B_Index];
			SDK::FVector C_Local = vertexData[C_Index];

			SDK::FVector A_World = Math::Vector_LocalToWorld(componentTransform, A_Local);
			SDK::FVector B_World = Math::Vector_LocalToWorld(componentTransform, B_Local);
			SDK::FVector C_World = Math::Vector_LocalToWorld(componentTransform, C_Local);

			SDK::FVector2D A_Screen, B_Screen, C_Screen;
			bool A_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, A_World, &A_Screen, false);
			bool B_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, B_World, &B_Screen, false);
			bool C_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, C_World, &C_Screen, false);

			if (A_Project && B_Project && C_Project)
			{
				drawList->AddLine(ImVec2(A_Screen.X, A_Screen.Y), ImVec2(B_Screen.X, B_Screen.Y), drawColor, drawThickness);
				drawList->AddLine(ImVec2(B_Screen.X, B_Screen.Y), ImVec2(C_Screen.X, C_Screen.Y), drawColor, drawThickness);
				drawList->AddLine(ImVec2(C_Screen.X, C_Screen.Y), ImVec2(A_Screen.X, A_Screen.Y), drawColor, drawThickness);
			}
		}
	}
}

void DebugDraw::DrawVolume(SDK::AVolume* volume, const uint32_t& drawColor, const float& drawThickness)
{
	if (volume == nullptr)
		return;

	if (volume->BrushComponent == nullptr)
		return;

	SDK::UBrushComponent* brushComponent = volume->BrushComponent;
	if (brushComponent->BrushBodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = brushComponent->BrushBodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(brushComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}




void DebugDraw::DrawStaticMeshComponent(SDK::UStaticMeshComponent* staticMeshComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (staticMeshComponent == nullptr)
		return;

	if (staticMeshComponent->StaticMesh == nullptr)
		return;

	SDK::UStaticMesh* staticMesh = static_cast<SDK::UStaticMesh*>(staticMeshComponent->StaticMesh);
	if (staticMesh->BodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = staticMesh->BodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(staticMeshComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}

void DebugDraw::DrawInstancedStaticMeshComponent(SDK::UInstancedStaticMeshComponent* instancedStaticMeshComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (instancedStaticMeshComponent == nullptr)
		return;

	if (instancedStaticMeshComponent->StaticMesh == nullptr)
		return;

	SDK::UStaticMesh* staticMesh = static_cast<SDK::UStaticMesh*>(instancedStaticMeshComponent->StaticMesh);
	if (staticMesh->BodySetup == nullptr)
		return;

	SDK::UBodySetup* bodySetup = staticMesh->BodySetup;
	Unreal::Transform componentTransform = Unreal::ActorComponent::GetTransform(instancedStaticMeshComponent);

	DrawBodySetup(bodySetup, componentTransform, drawColor, drawThickness);
}




void DebugDraw::DrawSkeletalMeshComponent(SDK::USkeletalMeshComponent* skeletalMeshComponent, const bool& drawAllSockets, const uint32_t& drawColor, const float& drawThickness)
{
	if (skeletalMeshComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	static const std::vector<std::string> commonBoneNames =
	{
		"root", "pelvis", "spine", "neck", "head",
		"hand", "foot", "calf", "thigh", "arm",
		"clavicle", "joint"
	};

	std::vector<SDK::FName> socketNamesToDraw;
	std::vector<SDK::FName> spottedBonesNames;
	SDK::TArray<SDK::FName> socketNamesCollection = skeletalMeshComponent->GetAllSocketNames();
	for (SDK::FName socketName : socketNamesCollection)
	{
		SDK::FName boneName = skeletalMeshComponent->GetSocketBoneName(socketName);

		bool isUniqueBone = true;
		for (SDK::FName spottedBoneName : spottedBonesNames)
		{
			if (boneName == spottedBoneName)
				isUniqueBone = false;
		}

		if (isUniqueBone == false)
			continue;


		if (drawAllSockets == false)
		{
			bool isCommonBone = false;
			for (std::string commonBoneName : commonBoneNames)
			{
				std::string sBoneName = boneName.ToString();
				if (Utilities::String::ToLowerCase(sBoneName).find(commonBoneName) != std::string::npos)
					isCommonBone = true;
			}

			if (isCommonBone == false)
				continue;
		}


		spottedBonesNames.push_back(boneName);
		socketNamesToDraw.push_back(socketName);
	}

	for (SDK::FName socketName : socketNamesToDraw)
	{
		/* GetSocketLocation() returns world location out of the box. */
		SDK::FVector socket_World = skeletalMeshComponent->GetSocketLocation(socketName);

		SDK::FVector2D socket_Screen;
		if (SDK::UGameplayStatics::ProjectWorldToScreen(playerController, socket_World, &socket_Screen, false))
		{
			drawList->AddCircleFilled(ImVec2(socket_Screen.X, socket_Screen.Y), drawThickness * 2, drawColor);
		}
	}
}




void DebugDraw::DrawCapsuleComponent(SDK::UCapsuleComponent* capsuleComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (capsuleComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	float capsuleRadius = capsuleComponent->GetScaledCapsuleRadius();
	float capsuleHalfHeight = capsuleComponent->GetScaledCapsuleHalfHeight();

	Unreal::Transform capsuleTransform = Unreal::ActorComponent::GetTransform(capsuleComponent);
	SDK::FVector capsuleUpVector = Math::Rotator_UpVector(capsuleTransform.rotation);

	/* Construct an orthonormal basis (axis, U, V) for building capsule rings. */
	SDK::FVector ortho_Temp = (fabsf(capsuleUpVector.Z) < 0.99f) ? SDK::FVector(0.f, 0.f, 1.f) : SDK::FVector(0.f, 1.f, 0.f); // Choose a temporary vector that is not parallel to the capsule axis.
	SDK::FVector ortho_U = Math::Vector_Normal(Math::Vector_Cross(capsuleUpVector, ortho_Temp), 0.01f); // Compute 'U' as a normalized vector perpendicular to 'axis'.
	SDK::FVector ortho_V = Math::Vector_Normal(Math::Vector_Cross(capsuleUpVector, ortho_U), 0.01f); // Compute 'V' as a normalized vector perpendicular to both 'axis' and 'U'.

	/* True top/bottom endpoints of the capsule (tips). */
	const SDK::FVector capsuleTopTip = capsuleTransform.location + capsuleUpVector * capsuleHalfHeight;
	const SDK::FVector capsuleBottomTip = capsuleTransform.location - capsuleUpVector * capsuleHalfHeight;

	/* Centers of the hemispherical caps. These are located radius units away from the tips toward the middle. */
	const SDK::FVector sphereTopCenter = capsuleTransform.location + capsuleUpVector * (capsuleHalfHeight - capsuleRadius);
	const SDK::FVector sphereBottomCenter = capsuleTransform.location - capsuleUpVector * (capsuleHalfHeight - capsuleRadius);

	/* Project tips to optionally use for hemisphere polylines. */
	SDK::FVector2D capsuleTopTip_Screen, capsuleBottomTip_Screen;
	const bool capsuleTopTip_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleTopTip, &capsuleTopTip_Screen, false);
	const bool capsuleBottomTip_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleBottomTip, &capsuleBottomTip_Screen, false);

	static const int32_t capsuleSegments = 24;
	static const int32_t hemisphereSegments = 6; // Number of segments from tip to seam to approximate the spherical rounding.
	for (int32_t i = 0; i < capsuleSegments; i++)
	{
		/*
			A ----------> B

			A - Current ring angle (azimuth).
			B - Next ring angle (azimuth).
		*/

		/* Compute the start (ringA_Angle) and end (ringB_Angle) angles for the current ring segment in radians. */
		const float ringA_Angle = (2.0f * Math::PI) * (float)i / (float)capsuleSegments;
		const float ringB_Angle = (2.0f * Math::PI) * (float)(i + 1) / (float)capsuleSegments;

		/* Unit directions around the capsule axis for current and next azimuths. */
		const SDK::FVector unitDirectionA = ortho_U * cosf(ringA_Angle) + ortho_V * sinf(ringA_Angle);
		const SDK::FVector unitDirectionB = ortho_U * cosf(ringB_Angle) + ortho_V * sinf(ringB_Angle);

		/* Rings at the cylinder/hemisphere seam (equators of the spherical caps). */
		SDK::FVector ringA_Top = sphereTopCenter + unitDirectionA * capsuleRadius;
		SDK::FVector ringB_Top = sphereTopCenter + unitDirectionB * capsuleRadius;
		SDK::FVector ringA_Bottom = sphereBottomCenter + unitDirectionA * capsuleRadius;
		SDK::FVector ringB_Bottom = sphereBottomCenter + unitDirectionB * capsuleRadius;

		SDK::FVector2D ringA_Top_Screen, ringB_Top_Screen, ringA_Bottom_Screen, ringB_Bottom_Screen;
		bool ringA_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Top, &ringA_Top_Screen, false);
		bool ringB_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Top, &ringB_Top_Screen, false);
		bool ringA_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Bottom, &ringA_Bottom_Screen, false);
		bool ringB_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Bottom, &ringB_Bottom_Screen, false);

		/* Outlines the top seam ring. */
		if (ringA_Top_Project && ringB_Top_Project)
			drawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringB_Top_Screen.X, ringB_Top_Screen.Y), drawColor, drawThickness);

		/* Outlines the bottom seam ring. */
		if (ringA_Bottom_Project && ringB_Bottom_Project)
			drawList->AddLine(ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), ImVec2(ringB_Bottom_Screen.X, ringB_Bottom_Screen.Y), drawColor, drawThickness);

		/* Outlines side walls (cylindrical part). */
		if (ringA_Top_Project && ringA_Bottom_Project)
			drawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), drawColor, drawThickness);

		/* Draw spherical rounding for top and bottom by tracing meridian polylines from tip to seam. */
		for (int32_t segment = 0; segment < hemisphereSegments; ++segment)
		{
			/*
				phi goes from 0 (tip) to PI/2 (seam). We connect successive samples to approximate a meridian.
				Top hemisphere position (for azimuth dirA): P(phi) = sphereTopCenter + capsuleRadius * ( dirA * sin(phi) + capsuleUpVector * cos(phi) )
				Bottom hemisphere: P(phi) = sphereBottomCenter + capsuleRadius * ( dirA * sin(phi) - capsuleUpVector * cos(phi) )
			*/
			float phi0 = (Math::PI * 0.5f) * (float)segment / (float)hemisphereSegments;
			float phi1 = (Math::PI * 0.5f) * (float)(segment + 1) / (float)hemisphereSegments;

			SDK::FVector pointA_Top = sphereTopCenter + (unitDirectionA * sinf(phi0) + capsuleUpVector * cosf(phi0)) * capsuleRadius;
			SDK::FVector pointB_Top = sphereTopCenter + (unitDirectionA * sinf(phi1) + capsuleUpVector * cosf(phi1)) * capsuleRadius;

			SDK::FVector pointA_Bottom = sphereBottomCenter + (unitDirectionA * sinf(phi0) - capsuleUpVector * cosf(phi0)) * capsuleRadius;
			SDK::FVector pointB_Bottom = sphereBottomCenter + (unitDirectionA * sinf(phi1) - capsuleUpVector * cosf(phi1)) * capsuleRadius;

			SDK::FVector2D PointA_Top_Screen, PointB_Top_Screen, PointA_Bottom_Screen, PointB_Bottom_Screen;
			bool pointA_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA_Top, &PointA_Top_Screen, false);
			bool pointB_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB_Top, &PointB_Top_Screen, false);
			bool pointA_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA_Bottom, &PointA_Bottom_Screen, false);
			bool pointB_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB_Bottom, &PointB_Bottom_Screen, false);

			if (pointA_Top_Project && pointB_Top_Project)
				drawList->AddLine(ImVec2(PointA_Top_Screen.X, PointA_Top_Screen.Y), ImVec2(PointB_Top_Screen.X, PointB_Top_Screen.Y), drawColor, drawThickness);

			if (pointA_Bottom_Project && pointB_Bottom_Project)
				drawList->AddLine(ImVec2(PointA_Bottom_Screen.X, PointA_Bottom_Screen.Y), ImVec2(PointB_Bottom_Screen.X, PointB_Bottom_Screen.Y), drawColor, drawThickness);
		}
	}
}


void DebugDraw::DrawSphereComponent(SDK::USphereComponent* sphereComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (sphereComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get sphere data. */
	float sphereRadius = sphereComponent->GetScaledSphereRadius();
	Unreal::Transform sphereTransform = Unreal::ActorComponent::GetTransform(sphereComponent);
	SDK::FVector sphereCenter = sphereTransform.location;

	/* Build local orthonormal frame from component rotation. */
	SDK::FVector sphereForwardVector = Math::Rotator_ForwardVector(sphereTransform.rotation);
	SDK::FVector sphereRightVector = Math::Rotator_RightVector(sphereTransform.rotation);
	SDK::FVector sphereUpVector = Math::Rotator_UpVector(sphereTransform.rotation);

	/* We draw three great circles: in planes (Right,Forward), (Up,Forward), (Up,Right). */
	static const int32_t sphereSegments = 48;
	for (int32_t ring = 0; ring < 3; ++ring)
	{
		/* Choose two perpendicular axes spanning the ring's plane. */
		SDK::FVector U, V;
		if (ring == 0) { U = sphereRightVector;  V = sphereForwardVector; }   // Equatorial ring (perpendicular to Up)
		else if (ring == 1) { U = sphereUpVector; V = sphereForwardVector; }  // Ring perpendicular to Right
		else { U = sphereUpVector; V = sphereRightVector; }                   // Ring perpendicular to Forward

		for (int32_t segment = 0; segment < sphereSegments; ++segment)
		{
			/* Parametric angles for current and next segment. */
			float angleA = (2.0f * Math::PI) * (float)segment / (float)sphereSegments;
			float angleB = (2.0f * Math::PI) * (float)(segment + 1) / (float)sphereSegments;

			/* Points on the ring in world space. */
			SDK::FVector pointA = sphereCenter + (U * cosf(angleA) + V * sinf(angleA)) * sphereRadius;
			SDK::FVector pointB = sphereCenter + (U * cosf(angleB) + V * sinf(angleB)) * sphereRadius;

			/* Project and draw the segment if visible. */
			SDK::FVector2D pointA_Screen, pointB_Screen;
			bool pointA_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA, &pointA_Screen, false);
			bool pointB_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB, &pointB_Screen, false);

			if (pointA_Project && pointB_Project)
				drawList->AddLine(ImVec2(pointA_Screen.X, pointA_Screen.Y), ImVec2(pointB_Screen.X, pointB_Screen.Y), drawColor, drawThickness);
		}
	}
}

void DebugDraw::DrawBoxComponent(SDK::UBoxComponent* boxComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (boxComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get box transform and half extents in world units. */
	Unreal::Transform boxTransform = Unreal::ActorComponent::GetTransform(boxComponent);
	SDK::FVector boxLocation = boxTransform.location;
	SDK::FVector boxExtent = boxComponent->GetScaledBoxExtent();

	/* Local basis vectors from rotation (orthonormal). */
	SDK::FVector boxForwardVector = Math::Rotator_ForwardVector(boxTransform.rotation);
	SDK::FVector boxRightVector = Math::Rotator_RightVector(boxTransform.rotation);
	SDK::FVector boxUpVector = Math::Rotator_UpVector(boxTransform.rotation);

	/* Precompute axis-length vectors. */
	SDK::FVector boxForwardExtent = boxForwardVector * boxExtent.X;
	SDK::FVector boxRightExtent = boxRightVector * boxExtent.Y;
	SDK::FVector boxUpExtent = boxUpVector * boxExtent.Z;

	/* Compute the 8 corners of the oriented box. Indexing convention: XYZ, where X/Y/Z in {0, 1} mean -/+ along UpExtent/RightExtent/ForwardExtent. */
	SDK::FVector boxCorners_Location[8];
	boxCorners_Location[0] = boxLocation - boxForwardExtent - boxRightExtent - boxUpExtent; // c000
	boxCorners_Location[1] = boxLocation - boxForwardExtent - boxRightExtent + boxUpExtent; // c001
	boxCorners_Location[2] = boxLocation - boxForwardExtent + boxRightExtent - boxUpExtent; // c010
	boxCorners_Location[3] = boxLocation - boxForwardExtent + boxRightExtent + boxUpExtent; // c011
	boxCorners_Location[4] = boxLocation + boxForwardExtent - boxRightExtent - boxUpExtent; // c100
	boxCorners_Location[5] = boxLocation + boxForwardExtent - boxRightExtent + boxUpExtent; // c101
	boxCorners_Location[6] = boxLocation + boxForwardExtent + boxRightExtent - boxUpExtent; // c110
	boxCorners_Location[7] = boxLocation + boxForwardExtent + boxRightExtent + boxUpExtent; // c111

	/* Project all corners once. */
	SDK::FVector2D boxCorners_Screen[8];
	bool boxCorners_Project[8];
	for (int32_t i = 0; i < 8; ++i)
		boxCorners_Project[i] = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, boxCorners_Location[i], &boxCorners_Screen[i], false);

	/* Box edges as index pairs (12 edges). */
	static const int32_t boxEdges[12][2] = {
		{0,1}, {0,2}, {0,4}, // from c000
		{7,3}, {7,5}, {7,6}, // from c111
		{1,3}, {1,5},        // edges on -F face
		{2,3}, {2,6},        // edges on +R face
		{4,5}, {4,6}         // edges on +F / -R faces
	};

	for (int32_t edge = 0; edge < 12; ++edge)
	{
		int32_t i0 = boxEdges[edge][0];
		int32_t i1 = boxEdges[edge][1];
		if (boxCorners_Project[i0] && boxCorners_Project[i1])
		{
			SDK::FVector2D p0 = boxCorners_Screen[i0];
			SDK::FVector2D p1 = boxCorners_Screen[i1];
			drawList->AddLine(ImVec2(p0.X, p0.Y), ImVec2(p1.X, p1.Y), drawColor, drawThickness);
		}
	}
}

void DebugDraw::DrawSplineComponent(SDK::USplineComponent* splineComponent, const uint32_t& drawColor, const float& drawThickness)
{
	if (splineComponent == nullptr)
		return;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr)
		return;

	ImDrawList* drawList = ImGui::GetDrawList();
	if (drawList == nullptr)
		return;

	/* Get spline data. */
	int32_t splinePointsCount = splineComponent->GetNumberOfSplinePoints();
	if (splinePointsCount < 2)
		return;

	/* Get spline world transform. */
	Unreal::Transform splineTransform = Unreal::ActorComponent::GetTransform(splineComponent);

	/* Number of segments per spline section for smoothness. */
	static const int32_t splineSegments = 16;
	for (int32_t pointIndex = 0; pointIndex < splinePointsCount - 1; ++pointIndex)
	{
		/* Get distances along the spline for this segment. */
		float segmentStartDistance = splineComponent->GetDistanceAlongSplineAtSplinePoint(pointIndex);
		float segmentEndDistance = splineComponent->GetDistanceAlongSplineAtSplinePoint(pointIndex + 1);
		float segmentLength = segmentEndDistance - segmentStartDistance;

		/* Subdivide spline segment for a smooth visual curve. */
		for (int32_t segment = 0; segment < splineSegments; ++segment)
		{
			float tA = (float)segment / (float)splineSegments;
			float tB = (float)(segment + 1) / (float)splineSegments;

			float distanceA = segmentStartDistance + tA * segmentLength;
			float distanceB = segmentStartDistance + tB * segmentLength;

			/* Get world-space positions along the spline. */
			SDK::FVector pointA = splineComponent->GetLocationAtDistanceAlongSpline(distanceA, SDK::ESplineCoordinateSpace::World);
			SDK::FVector pointB = splineComponent->GetLocationAtDistanceAlongSpline(distanceB, SDK::ESplineCoordinateSpace::World);

			/* Project and draw the segment if visible. */
			SDK::FVector2D pointA_Screen, pointB_Screen;
			bool pointA_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointA, &pointA_Screen, false);
			bool pointB_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, pointB, &pointB_Screen, false);

			if (pointA_Project && pointB_Project)
				drawList->AddLine(ImVec2(pointA_Screen.X, pointA_Screen.Y), ImVec2(pointB_Screen.X, pointB_Screen.Y), drawColor, drawThickness);
		}
	}
}
#endif






// ==============================
// |        #Templates			|
// ==============================
void Templates::Functions::Draw(SDK::UObject* objectReference)
{
	ImGui::SetFontTitle();
	ImGui::Text("Functions");
	ImGui::SetFontRegular();
	if (ImGui::TreeNode("Details##Functions"))
	{
		if (ImGui::Button("Update##Functions"))
		{
			Features::Functions::functions = Unreal::Function::GetFunctions(objectReference);
			Features::Functions::functionsOwner = objectReference;
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::InputText("Search Filter##Functions", Features::Functions::functionsFilterBuffer, Features::Functions::functionsFilterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Functions", &Features::Functions::functionsFilterCaseSensitive);

		ImGui::NewLine();

		if (objectReference == Features::Functions::functionsOwner)
		{
			std::vector<Unreal::Function::DataStructure> filteredFunctions = Unreal::Function::FilterByName(Features::Functions::functions, Features::Functions::functionsFilterBuffer, Features::Functions::functionsFilterCaseSensitive);
			for (Unreal::Function::DataStructure function : filteredFunctions)
			{
				ImGui::PushID(function.address.c_str());
				if (ImGui::TreeNode(function.name.c_str()))
				{
					ImGui::Text("Address: %s", function.address);
					if (ImGui::Button("Call"))
					{
						bool wasSuccessful = Unreal::Function::CallFunction(objectReference, function.reference);
						GUI::PlayActionSound(wasSuccessful);
					}
					ImGui::TreePop();
				}
				ImGui::PopID();
			}
		}

		ImGui::TreePop();
	}
}


void Templates::Console::Draw()
{
	ImGui::Text("Console:");
	ImGui::SameLine();
	ImGui::PushItemWidth(320);
	ImGui::InputText("##Console", Features::Console::consoleBuffer, Features::Console::consoleBufferSize);
	ImGui::SameLine();
	if (ImGui::Button("Execute"))
	{
		std::wstring command = Utilities::String::ToWString(Features::Console::consoleBuffer);
		if (command.size() > 0)
		{
			GUI::PlayActionSound(Unreal::Console::ExecuteConsoleCommand(command));
		}
		else
			GUI::PlayActionSound(false);
	}
	ImGui::PopItemWidth();
}


void Templates::Menus::Settings::Draw()
{
	if (ImGui::BeginMenu("Settings"))
	{
		if (ImGui::Checkbox("Enable Sound", &Features::Menu::enableSound))
		{
			Features::Config::Save();
		}
		ImGui::NewLine();
		if (ImGui::Checkbox("Construct Console Automatically", &Features::Menu::autoConstructConsole))
		{
			if (Features::Menu::autoConstructConsole)
				Unreal::Console::Construct();

			Features::Config::Save();
		}
		if (ImGui::Checkbox("Enable Console Output", &Features::Menu::enableConsoleOutput))
		{
			Features::Config::Save();
		}

		ImGui::EndMenu();
	}
}




void Templates::Descriptions::HDR::Draw()
{
#ifndef UE5
	ImGui::SetFontTitle();
	ImGui::Text("[!] DirectX 12 [!]");
	ImGui::SetFontRegular();
	ImGui::Text("Unreal Engine 4.14 - 4.27 only support HDR while running under DirectX 11.");
	ImGui::NewLine();
#endif

	ImGui::SetFontSmall();
	ImGui::Text("HDR must be allowed through configuration file in order to be enabled.");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRAllowConfigDescription = "[/Script/Engine.RendererSettings]\n"
		"r.AllowHDR = 1";
	static const size_t HDRAllowConfigDescriptionLength = strlen(HDRAllowConfigDescription);
	ImGui::InputTextMultiline("##HDRAllowConfigDescription", const_cast<char*>(HDRAllowConfigDescription), HDRAllowConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRAllowConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(HDRAllowConfigDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Behavior can be adjusted through configuration file or Unreal Engine Console (Engine -> Game Viewport Client -> Console).");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRSettingsConfigDescription =
		"[/Script/Engine.RendererSettings]\n"
		"r.HDR.EnableHDROutput = 1\n"
		"; 0 - LDR.\n"
		"; 1 - HDR.\n"
		"\n"
		"r.HDR.Display.ColorGamut = 2\n"
		"; Color space of the output display.\n"
		"; 0 - Rec709.\n"
		"; 1 - DCI - P3.\n"
		"; 2 - Rec2020.\n"
		"; 3 - ACES.\n"
		"; 4 - ACEScg.\n"
		"\n"
		"r.HDR.Display.OutputDevice = 5\n"
		"; Device format of the output display\n"
		"; 0 - sRGB (LDR).\n"
		"; 1 - Rec709 (LDR).\n"
		"; 2 - Explicit gamma mapping (LDR).\n"
		"; 3 - ACES 1000 nit ST-2084 (Dolby PQ) (HDR).\n"
		"; 4 - ACES 2000 nit ST-2084 (Dolby PQ) (HDR).\n"
		"; 5 - ACES 1000 nit ScRGB (HDR).\n"
		"; 6 - ACES 2000 nit ScRGB (HDR).\n"
		"; 7 - Linear EXR (HDR).\n"
		"; 8 - Linear final color, no tone curve (HDR).\n"
		"; 9 - Linear final color with tone curve (HDR).\n"
		"\n"
#ifdef UE5																		  										  
		"r.HDR.Display.MaxLuminance = 1000\n"
		"; Output peak nit level.\n"
		"\n"
		"r.HDR.Display.MidLuminance = 15\n"
		"; Output nit level for 18% gray."
		"\n"
#endif																			  										  
		"r.HDR.UI.CompositeMode = 1\n"
		"; Preserve LDR visuals and blending for UI elements.\n"
		"\n"
		"r.HDR.UI.Level = 0.65\n"
		"; Luminance level for UI elements.";
	static const size_t HDRSettingsConfigDescriptionLength = strlen(HDRSettingsConfigDescription);
	ImGui::InputTextMultiline("##HDRSettingsConfigDescription", const_cast<char*>(HDRSettingsConfigDescription), HDRSettingsConfigDescriptionLength, { 800, 600 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRSettingsConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(HDRSettingsConfigDescription));
	}

	ImGui::SetFontRegular();
	ImGui::Text("Unreal Engine Console");
	ImGui::SetFontSmall();
	static const char* HDRSettingsConsoleDescription =
		"r.HDR.EnableHDROutput 1 | "
		"r.HDR.Display.ColorGamut 2 | "
		"r.HDR.Display.OutputDevice 5 | "
#ifdef UE5																		   
		"r.HDR.Display.MaxLuminance 1000 | "
		"r.HDR.Display.MidLuminance 15 | "
#endif																			   
		"r.HDR.UI.CompositeMode 1 | "
		"r.HDR.UI.Level 0.65";
	static const size_t HDRSettingsConsoleDescriptionLength = strlen(HDRSettingsConsoleDescription);
	ImGui::InputTextMultiline("##HDRSettingsConsoleDescription", const_cast<char*>(HDRSettingsConsoleDescription), HDRSettingsConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRSettingsConsoleDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(HDRSettingsConsoleDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Autoexposure and fake HDR can cause scenes to appear overly dark.");

	ImGui::SetFontRegular();
	ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
	ImGui::SetFontSmall();
	static const char* HDRDisturbanceConfigDescription = "[/Script/Engine.RendererSettings]\n"
		"r.DefaultFeature.AutoExposure = 0\n"
		"r.EyeAdaptationQuality = 0";
	static const size_t HDRDisturbanceConfigDescriptionLength = strlen(HDRDisturbanceConfigDescription);
	ImGui::InputTextMultiline("##HDRDisturbanceConfigDescription", const_cast<char*>(HDRDisturbanceConfigDescription), HDRDisturbanceConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRDisturbanceConfigDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(HDRDisturbanceConfigDescription));
	}

	ImGui::SetFontRegular();
	ImGui::Text("Unreal Engine Console");
	ImGui::SetFontSmall();
	static const char* HDRDisturbanceConsoleDescription = "r.DefaultFeature.AutoExposure 0 | "
		"r.EyeAdaptationQuality 0";
	static const size_t HDRDisturbanceConsoleDescriptionLength = strlen(HDRDisturbanceConsoleDescription);
	ImGui::InputTextMultiline("##HDRDisturbanceConsoleDescription", const_cast<char*>(HDRDisturbanceConsoleDescription), HDRDisturbanceConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Copy##HDRDisturbanceConsoleDescription"))
	{
		GUI::PlayActionSound(Utilities::Clipboard::SetClipboardText(HDRDisturbanceConsoleDescription));
	}

	ImGui::NewLine();

	ImGui::Text("Certain titles may try deleting \"Engine.ini\" configuration file from the system!\nIt's recommended to set it as for read-only (RMB -> Properties).");

	ImGui::SetFontRegular();
}


#ifdef SOFT_PATH
void Templates::Descriptions::SoftPath::Draw(const char* typeName, const char* examplePath)
{
	ImGui::SetFontSmall();
	ImGui::Text("Dynamic %s loading by soft path, for example \"%s\".", typeName ? typeName : "#TYPE#", examplePath ? examplePath : "#EXAMPLEPATH#");
	ImGui::SameLine();
	ImGui::TextHint("Format: Automatically converts FModel/Windows paths to UE-native.\nShortcut: Use '--' (.{name}) or '..' (.{name}_C) suffixes to complete the path.\nMulti-input: Use '|' as a separator between paths.");
	ImGui::SetFontRegular();
}
#endif




void Templates::Menus::Debug::Sub_Engine()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Engine:", Features::Debug::engine.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::engine.reference)
	{
		if (ImGui::CollapsingHeader("Details##Engine"))
		{
			ImGui::Text("Engine Class: %s", Features::Debug::engine.className.c_str());
			ImGui::Text("Engine Object: %s", Features::Debug::engine.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game Viewport Client:", Features::Debug::engine.gameViewportClient.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::engine.gameViewportClient.reference)
			{
				if (ImGui::TreeNode("Details##GameViewportClient"))
				{
					ImGui::Text("Viewport Client Class: %s", Features::Debug::engine.gameViewportClient.className.c_str());
					ImGui::Text("Viewport Client Object: %s", Features::Debug::engine.gameViewportClient.objectName.c_str());

					ImGui::NewLine();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Console:", Features::Debug::engine.gameViewportClient.console.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::engine.gameViewportClient.console.reference)
					{
						ImGui::SameLine();
						ImGui::TextHint("Press ~ (Tilde) or F10 to open. Second press will switch console to detailed mode.");

						if (ImGui::TreeNode("Details##Console"))
						{
							ImGui::Text("Console Class: %s", Features::Debug::engine.gameViewportClient.console.className.c_str());
							ImGui::Text("Console Object: %s", Features::Debug::engine.gameViewportClient.console.objectName.c_str());

							ImGui::TreePop();
						}
					}
					else
					{
						if (ImGui::Button("Construct Console"))
						{
							bool wasConstructed = Unreal::Console::Construct() && Unreal::InputSettings::AssignConsoleBindings();
							if (wasConstructed) // Only gather debug information if we're aware of changes.
								Features::Debug::ThreadSafeUpdate();

							GUI::PlayActionSound(wasConstructed);
						}
					}

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::Text("High Dynamic Range");
			ImGui::SetFontRegular();
			if (ImGui::TreeNode("Details##HDR"))
			{
				Templates::Descriptions::HDR::Draw();
				ImGui::TreePop();
			}


			ImGui::NewLine();

			bool fixedFrameRateEnabled = Features::Debug::engine.fixedFrameRateEnabled;
			if (ImGui::Checkbox("Fixed FrameRate Enabled", &fixedFrameRateEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.fixedFrameRateEnabled = fixedFrameRateEnabled;
					Features::Debug::engine.reference->bUseFixedFrameRate = fixedFrameRateEnabled;
				}
			}
			float fixedFrameRate = Features::Debug::engine.fixedFrameRate;
			if (ImGui::InputFloat("Fixed FrameRate", &fixedFrameRate, 1.0f, 10.0f))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.fixedFrameRate = fixedFrameRate;
					Features::Debug::engine.reference->FixedFrameRate = fixedFrameRate;
				}
			}

			ImGui::NewLine();

			bool smoothFrameRateEnabled = Features::Debug::engine.smoothFrameRateEnabled;
			if (ImGui::Checkbox("Smooth FrameRate Enabled", &smoothFrameRateEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.smoothFrameRateEnabled = smoothFrameRateEnabled;
					Features::Debug::engine.reference->bSmoothFrameRate = smoothFrameRateEnabled;
				}
			}
			float smoothFrameRateRange[2] = { Features::Debug::engine.smoothFrameRateRange.LowerBound.Value, Features::Debug::engine.smoothFrameRateRange.UpperBound.Value };
			if (ImGui::InputFloat2("Smooth FrameRate Range", smoothFrameRateRange))
			{
				if (Features::Debug::engine.reference)
				{
					SDK::FFloatRange floatRange = Features::Debug::engine.smoothFrameRateRange;
					floatRange.LowerBound.Value = smoothFrameRateRange[0];
					floatRange.UpperBound.Value = smoothFrameRateRange[1];

					Features::Debug::engine.smoothFrameRateRange = floatRange;
					Features::Debug::engine.reference->SmoothedFrameRateRange = floatRange;
				}
			}

			ImGui::NewLine();

			bool subtitlesEnabled = Features::Debug::engine.subtitlesEnabled;
			if (ImGui::Checkbox("Subtitles Enabled", &subtitlesEnabled))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.subtitlesEnabled = subtitlesEnabled;
					Features::Debug::engine.reference->bSubtitlesEnabled = subtitlesEnabled;
				}
			}
			bool subtitlesForcedOff = Features::Debug::engine.subtitlesForcedOff;
			if (ImGui::Checkbox("Subtitles Forced Off", &subtitlesForcedOff))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.subtitlesForcedOff = subtitlesForcedOff;
					Features::Debug::engine.reference->bSubtitlesForcedOff = subtitlesForcedOff;
				}
			}

			ImGui::NewLine();

			bool pauseOnLossOfFocus = Features::Debug::engine.pauseOnLossOfFocus;
			if (ImGui::Checkbox("Pause On Loss Of Focus", &pauseOnLossOfFocus))
			{
				if (Features::Debug::engine.reference)
				{
					Features::Debug::engine.pauseOnLossOfFocus = pauseOnLossOfFocus;
					Features::Debug::engine.reference->bPauseOnLossOfFocus = pauseOnLossOfFocus;
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_GameInstance()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Game Instance:", Features::Debug::gameInstance.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::gameInstance.reference)
	{
		if (ImGui::CollapsingHeader("Details##GameInstance"))
		{
			ImGui::Text("Game Instance Class: %s", Features::Debug::gameInstance.className.c_str());
			ImGui::Text("Game Instance Object: %s", Features::Debug::gameInstance.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Online Session:", Features::Debug::gameInstance.onlineSession.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::gameInstance.onlineSession.reference)
			{
				if (ImGui::TreeNode("Details##OnlineSession"))
				{
					ImGui::Text("Online Session Class: %s", Features::Debug::gameInstance.onlineSession.className.c_str());
					ImGui::Text("Online Session Object: %s", Features::Debug::gameInstance.onlineSession.objectName.c_str());

					ImGui::TreePop();
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_GameMode()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Game Mode:", Features::Debug::gameMode.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::gameMode.reference)
	{
		if (ImGui::CollapsingHeader("Details##GameMode"))
		{
			ImGui::Text("Game Mode Class: %s", Features::Debug::gameMode.className.c_str());
			ImGui::Text("Game Mode Object: %s", Features::Debug::gameMode.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game Session:", Features::Debug::gameMode.gameSession.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::gameMode.gameSession.reference)
			{
				if (ImGui::TreeNode("Details##GameSession"))
				{
					ImGui::Text("Game Session Class: %s", Features::Debug::gameMode.gameSession.className.c_str());
					ImGui::Text("Game Session Object: %s", Features::Debug::gameMode.gameSession.objectName.c_str());

					ImGui::NewLine();

					int32_t maxPlayers = Features::Debug::gameMode.gameSession.maxPlayers;
					if (ImGui::InputInt("Max Players", &maxPlayers, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxPlayers = maxPlayers;
							Features::Debug::gameMode.gameSession.reference->MaxPlayers = maxPlayers;
						}
					}
					int32_t maxSpectators = Features::Debug::gameMode.gameSession.maxSpectators;
					if (ImGui::InputInt("Max Spectators", &maxSpectators, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxSpectators = maxSpectators;
							Features::Debug::gameMode.gameSession.reference->MaxSpectators = maxSpectators;
						}
					}
					int32_t maxPartySize = Features::Debug::gameMode.gameSession.maxPartySize;
					if (ImGui::InputInt("Max Party Size", &maxPartySize, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxPartySize = maxPartySize;
							Features::Debug::gameMode.gameSession.reference->MaxPartySize = maxPartySize;
						}
					}
					int32_t maxSplitScreensPerConnection = Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection;
					if (ImGui::InputInt("Max Split Screens Per Connection", &maxSplitScreensPerConnection, 1, 10))
					{
						if (Features::Debug::gameMode.gameSession.reference)
						{
							Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = maxSplitScreensPerConnection;
							Features::Debug::gameMode.gameSession.reference->MaxSplitscreensPerConnection = maxSplitScreensPerConnection;
						}
					}

					ImGui::NewLine();

					ImGui::ReadOnlyInputText("Session Name:", Features::Debug::gameMode.gameSession.sessionName.c_str(), true);

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::TextIntColored("Players Count:", Features::Debug::gameMode.playersCount);
			ImGui::TextIntColored("Spectators Count:", Features::Debug::gameMode.spectatorsCount);

			ImGui::NewLine();

			ImGui::TextBoolColored("Start Players As Spectator:", Features::Debug::gameMode.startPlayersAsSpectators);
			ImGui::ReadOnlyInputText("Default Player Name:", Features::Debug::gameMode.defaultPlayerName.c_str(), true);

			ImGui::NewLine();

			bool useSeamlessTravel = Features::Debug::gameMode.useSeamlessTravel;
			if (ImGui::Checkbox("Use Seamless Travel", &useSeamlessTravel))
			{
				if (Features::Debug::gameMode.reference)
				{
					Features::Debug::gameMode.useSeamlessTravel = useSeamlessTravel;
					Features::Debug::gameMode.reference->bUseSeamlessTravel = useSeamlessTravel;
				}
			}
			bool isPausable = Features::Debug::gameMode.isPausable;
			if (ImGui::Checkbox("Is Pausable", &isPausable))
			{
				if (Features::Debug::gameMode.reference)
				{
					Features::Debug::gameMode.isPausable = isPausable;
					Features::Debug::gameMode.reference->bPauseable = isPausable;
				}
			}

			ImGui::NewLine();

			ImGui::ReadOnlyInputText("Options:", Features::Debug::gameMode.options.c_str(), true);
		}
	}
}

void Templates::Menus::Debug::Sub_PlayerController()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("Player Controller:", Features::Debug::playerController.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::playerController.reference)
	{
		if (ImGui::CollapsingHeader("Details##PlayerController"))
		{
			ImGui::Text("Player Controller Class: %s", Features::Debug::playerController.className.c_str());
			ImGui::Text("Player Controller Object: %s", Features::Debug::playerController.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Pawn:", Features::Debug::playerController.pawn.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.pawn.reference)
			{
				if (ImGui::TreeNode("Details##Pawn"))
				{
					ImGui::Text("Pawn Class: %s", Features::Debug::playerController.pawn.className.c_str());
					ImGui::Text("Pawn Object: %s", Features::Debug::playerController.pawn.objectName.c_str());
					ImGui::TextVectorColored("Location:", Features::Debug::playerController.pawn.transform.location);
					ImGui::TextRotatorColored("Rotation:", Features::Debug::playerController.pawn.transform.rotation);
					ImGui::TextVectorColored("Scale:", Features::Debug::playerController.pawn.transform.scale);

					ImGui::NewLine();

					ImGui::TextBoolColored("Is Controlled:", Features::Debug::playerController.pawn.isControlled);
					ImGui::TextBoolColored("Is Pawn Controlled:", Features::Debug::playerController.pawn.isPawnControlled);
					ImGui::TextBoolColored("Is Player Controlled:", Features::Debug::playerController.pawn.isPlayerControlled);
					ImGui::TextBoolColored("Is Locally Controlled:", Features::Debug::playerController.pawn.isLocallyControlled);
					ImGui::TextBoolColored("Is Bot Controlled:", Features::Debug::playerController.pawn.isBotControlled);

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Camera Manager:", Features::Debug::playerController.cameraManager.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.cameraManager.reference)
			{
				if (ImGui::TreeNode("Details##CameraManager"))
				{
					ImGui::Text("Camera Manager Class: %s", Features::Debug::playerController.cameraManager.className.c_str());
					ImGui::Text("Camera Manager Object: %s", Features::Debug::playerController.cameraManager.objectName.c_str());
					ImGui::TextVectorColored("Location:", Features::Debug::playerController.cameraManager.transform.location);
					ImGui::TextRotatorColored("Rotation:", Features::Debug::playerController.cameraManager.transform.rotation);
					ImGui::TextVectorColored("Scale:", Features::Debug::playerController.cameraManager.transform.scale);

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Cheat Manager:", Features::Debug::playerController.cheatManager.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::playerController.cheatManager.reference)
			{
				if (ImGui::TreeNode("Details##CheatManager"))
				{
					ImGui::Text("Cheat Manager Class: %s", Features::Debug::playerController.cheatManager.className.c_str());
					ImGui::Text("Cheat Manager Object: %s", Features::Debug::playerController.cheatManager.objectName.c_str());

					ImGui::TreePop();
				}
			}
			else
			{
				if (ImGui::Button("Construct Cheat Manager"))
				{
					bool wasConstructed = Unreal::CheatManager::Construct();
					if (wasConstructed) // Only gather debug information if we're aware of changes.
						Features::Debug::ThreadSafeUpdate();

					GUI::PlayActionSound(wasConstructed);
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_World()
{
	ImGui::SetFontTitle();
	ImGui::TextBoolPresenceColored("World:", Features::Debug::world.reference);
	ImGui::SetFontRegular();
	if (Features::Debug::world.reference)
	{
		if (ImGui::CollapsingHeader("Details##World"))
		{
			ImGui::Text("World Class: %s", Features::Debug::world.className.c_str());
			ImGui::Text("World Object: %s", Features::Debug::world.objectName.c_str());

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Game State:", Features::Debug::world.gameState.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.gameState.reference)
			{
				if (ImGui::TreeNode("Details##GameState"))
				{
					ImGui::Text("Game State Class: %s", Features::Debug::world.gameState.className.c_str());
					ImGui::Text("Game State Object: %s", Features::Debug::world.gameState.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Net Driver:", Features::Debug::world.netDriver.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.netDriver.reference)
			{
				if (ImGui::TreeNode("Details##NetDriver"))
				{
					ImGui::Text("Net Driver Class: %s", Features::Debug::world.netDriver.className.c_str());
					ImGui::Text("Net Driver Object: %s", Features::Debug::world.netDriver.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Demo Net Driver:", Features::Debug::world.demoNetDriver.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.demoNetDriver.reference)
			{
				if (ImGui::TreeNode("Details##DemoNetDriver"))
				{
					ImGui::Text("Demo Net Driver Class: %s", Features::Debug::world.demoNetDriver.className.c_str());
					ImGui::Text("Demo Net Driver Object: %s", Features::Debug::world.demoNetDriver.objectName.c_str());

					ImGui::TreePop();
				}
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::TextBoolPresenceColored("Persistent Level:", Features::Debug::world.persistentLevel.reference);
			ImGui::SetFontRegular();
			if (Features::Debug::world.persistentLevel.reference)
			{
				if (ImGui::TreeNode("Details##PersistentLevel"))
				{
					ImGui::Text("Persistent Level Class: %s", Features::Debug::world.persistentLevel.className.c_str());
					ImGui::Text("Persistent Level Object: %s", Features::Debug::world.persistentLevel.objectName.c_str());
					ImGui::TextBoolColored("Is Visible:", Features::Debug::world.persistentLevel.isVisible);

					ImGui::NewLine();

					bool worldSettingsPresent = Features::Debug::world.persistentLevel.worldSettings.reference;
					ImGui::TextBoolPresenceColored("World Settings:", worldSettingsPresent);
					if (worldSettingsPresent)
					{
						if (ImGui::TreeNode("World Settings"))
						{
							ImGui::Text("World Settings Class: %s", Features::Debug::world.persistentLevel.worldSettings.className.c_str());
							ImGui::Text("World Settings Object: %s", Features::Debug::world.persistentLevel.worldSettings.objectName.c_str());

							ImGui::NewLine();

							ImGui::TextBoolColored("High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading);
							ImGui::TextBoolColored("Local High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading);

							ImGui::NewLine();

							ImGui::TextFloat("Unreal Units = 1m:", Features::Debug::world.persistentLevel.worldSettings.unitsToMeters);

							ImGui::TreePop();
						}
					}

					ImGui::NewLine();

					bool areStreamingLevelsPresent = Features::Debug::world.streamingLevels.size() > 0;
					ImGui::TextBoolMultiplePresenceColored("Streaming Levels:", areStreamingLevelsPresent);
					if (areStreamingLevelsPresent)
					{
						if (ImGui::TreeNode("Streaming Levels"))
						{
							ImGui::InputText("Search Filter", Features::Debug::streamingLevelsFilterBuffer, Features::Debug::streamingLevelsFilterBufferSize);
							ImGui::SameLine();
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Checkbox("Case Sensitive", &Features::Debug::streamingLevelsFilterCaseSensitive);
							ImGui::SameLine();
							ImGui::Spacing();
							ImGui::SameLine();
							ImGui::Checkbox("Editor Colors", &Features::Debug::streamingLevelsEditorColors);

							std::vector<Unreal::LevelStreaming::DataStructure> filteredStreamingLevels = Unreal::LevelStreaming::FilterByLevelPath(Features::Debug::world.streamingLevels, Features::Debug::streamingLevelsFilterBuffer, Features::Debug::streamingLevelsFilterCaseSensitive);
							for (Unreal::LevelStreaming::DataStructure& streamingLevel : filteredStreamingLevels) // <-- Reference!
							{
								ImGui::PushID(streamingLevel.objectName.c_str());

								ImVec4 levelColor;
								if (Features::Debug::streamingLevelsEditorColors)
								{
									levelColor = { streamingLevel.levelColor.R, streamingLevel.levelColor.G, streamingLevel.levelColor.B, streamingLevel.levelColor.A };
								}
								else
								{
									static const ImVec4 color_visible = ImGui::ColorConvertU32ToFloat4(IM_COL32(51, 204, 77, 255));
									static const ImVec4 color_loaded = ImGui::ColorConvertU32ToFloat4(IM_COL32(51, 102, 204, 255));
									static const ImVec4 color_null = ImGui::ColorConvertU32ToFloat4(IM_COL32(204, 77, 51, 255));

									if (streamingLevel.level.reference)
										levelColor = streamingLevel.level.isVisible ? color_visible : color_loaded;
									else
										levelColor = color_null;
								}

								ImGui::PushStyleColor(ImGuiCol_Text, levelColor);
								bool isTreeNodeOpen = ImGui::TreeNode(streamingLevel.levelPath.c_str());
								ImGui::PopStyleColor();

								if (isTreeNodeOpen)
								{
									if (Features::Debug::autoUpdate == false)
									{
										ImGui::Text("Debug section isn't set to auto-update!");
										ImGui::SetFontSmall();
										ImGui::Text("In order to see level related changes in UI, use \"Update\" button.");
										ImGui::SetFontRegular();
										ImGui::NewLine();
									}

									bool isLevelLoaded = streamingLevel.level.reference;

									ImGui::TextBoolColored("Is Loaded:", isLevelLoaded);
									ImGui::SameLine();
									ImGui::Spacing();
									ImGui::SameLine();
									if (ImGui::Button(isLevelLoaded ? "Unload" : "Load"))
									{
										if (streamingLevel.reference != nullptr)
										{
											streamingLevel.reference->SetShouldBeLoaded(!isLevelLoaded);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::TextBoolColored("Is Visible:", streamingLevel.level.isVisible);
									ImGui::SameLine();
									ImGui::Spacing();
									ImGui::SameLine();
									ImGui::BeginDisabled(isLevelLoaded == false);
									if (ImGui::Button(streamingLevel.level.isVisible ? "Hide" : "Show"))
									{
										if (isLevelLoaded && streamingLevel.reference != nullptr)
										{
											streamingLevel.reference->SetShouldBeVisible(!streamingLevel.level.isVisible);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::EndDisabled();

									ImGui::NewLine();

									bool worldSettingsPresent = streamingLevel.level.worldSettings.reference;
									ImGui::TextBoolPresence("World Settings:", worldSettingsPresent);
									if (worldSettingsPresent)
									{
										if (ImGui::TreeNode("World Settings"))
										{
											ImGui::Text("World Settings Class: %s", streamingLevel.level.worldSettings.className.c_str());
											ImGui::Text("World Settings Object: %s", streamingLevel.level.worldSettings.objectName.c_str());

											ImGui::NewLine();

											ImGui::TextBoolColored("High Priority Loading:", streamingLevel.level.worldSettings.highPriorityLoading);
											ImGui::TextBoolColored("Local High Priority Loading:", streamingLevel.level.worldSettings.localHighPriorityLoading);

											ImGui::NewLine();

											ImGui::TextFloat("Unreal Units = 1m:", streamingLevel.level.worldSettings.unitsToMeters);

											ImGui::TreePop();
										}
									}

									ImGui::TreePop();
								}

								ImGui::PopID();
							}

							ImGui::TreePop();
						}
					}

					ImGui::NewLine();

					ImGui::TextFloatColored("Game Time (In Seconds):", Features::Debug::world.gameTimeInSeconds);

					ImGui::NewLine();

					ImGui::TextBoolColored("Is Server:", Features::Debug::world.isServer);
					ImGui::TextBoolColored("Is Dedicated Server:", Features::Debug::world.isDedicatedServer);
					ImGui::TextBoolColored("Is Split Screen:", Features::Debug::world.isSplitScreen);
					ImGui::TextBoolColored("Is Standalone:", Features::Debug::world.isStandalone);

					ImGui::TreePop();
				}
			}
		}
	}
}

void Templates::Menus::Debug::Sub_Actors()
{
	ImGui::SetFontTitle();
	ImGui::Text("Actors");
	ImGui::SetFontRegular();
	if (ImGui::CollapsingHeader("Details##Actors"))
	{
#ifdef ACTOR_TRACE
		ImGui::SetFontTitle();
		ImGui::Text("Actor Trace");
		ImGui::SetFontSmall();
		ImGui::Text("Performs a trace starting at the camera's position and outputs the name of the Actor hit by the trace.");
		ImGui::Text("X - Location at where trace has hit an Actor.");
		ImGui::Text("@ - Location at where trace has ended without a hit.");
		ImGui::Text("O - Location at where trace has started.");
		ImGui::SetFontRegular();
		ImGui::Checkbox("Enabled##ActorTrace", &Features::ActorTrace::enabled);
		ImGui::BeginDisabled(Features::ActorTrace::enabled == false);
		if (ImGui::TreeNode("Settings##ActorTrace"))
		{
			ImGui::KeyBindingInput("Key Binding:", &Inputs::Keybindings::debug_ActorTrace);

			ImGui::NewLine();

			ImGui::Checkbox("Show On Screen##ActorTrace", &Features::ActorTrace::showOnScreen);
			ImGui::Checkbox("Show Line Trace##ActorTrace", &Features::ActorTrace::showLineTrace);

			ImGui::NewLine();

			ImGui::ColorPicker4("Trace Color", Features::ActorTrace::traceColor);
			ImGui::InputFloat("Trace Thickness", &Features::ActorTrace::traceThickness, 0.1f, 1.0f);
			ImGui::InputFloat("Trace Length", &Features::ActorTrace::traceLength, 1.0f, 10.0f);

			ImGui::TreePop();
		}
		ImGui::EndDisabled();

		ImGui::NewLine();
#endif


		ImGui::SetFontTitle();
		ImGui::Text("Actor Spawn");
#ifdef SOFT_PATH
		Templates::Descriptions::SoftPath::Draw("Actor", "/Game/Blueprints/BP_CoinPickable.BP_CoinPickable_C");
#else
		ImGui::SetFontSmall();
		ImGui::Text("Dynamic Actor spawning from ready to go presets.");
		ImGui::SetFontRegular();
#endif

		if (ImGui::TreeNode("Details##ActorSpawn"))
		{
			ImGui::SetFontTitle();
			ImGui::Text("Quick Summon");
			ImGui::SetFontRegular();

			if (ImGui::Button("Point Light"))
			{
				SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::APointLight::StaticClass());
				GUI::PlayActionSound(actorReference);
			}
			ImGui::SameLine();
			if (ImGui::Button("Spot Light"))
			{
				SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::ASpotLight::StaticClass());
				GUI::PlayActionSound(actorReference);
			}

#ifdef SOFT_PATH
			ImGui::CategorySeparator();

			ImGui::SetFontTitle();
			ImGui::Text("Soft Summon");
			ImGui::SetFontRegular();

			ImGui::Text("Actor Path:    ");
			ImGui::SameLine();
			ImGui::InputText("##ActorSpawn", Features::ActorSpawn::actorPathBuffer, Features::ActorSpawn::actorPathBufferSize);

			ImGui::Checkbox("Use Character Location##ActorSpawn", &Features::ActorSpawn::useCharacterLocation);
			ImGui::BeginDisabled(Features::ActorSpawn::useCharacterLocation);
			ImGui::Text("Actor Location:");
			ImGui::SameLine();
			ImGui::InputFloat3("##ActorSpawnLocation", Features::ActorSpawn::location);
			ImGui::EndDisabled();

			ImGui::Checkbox("Use Character Rotation##ActorSpawn", &Features::ActorSpawn::useCharacterRotation);
			ImGui::BeginDisabled(Features::ActorSpawn::useCharacterRotation);
			ImGui::Text("Actor Rotation:");
			ImGui::SameLine();
			ImGui::InputFloat3("##ActorSpawnRotation", Features::ActorSpawn::rotation);
			ImGui::EndDisabled();

			ImGui::Text("Actor Scale:   ");
			ImGui::SameLine();
			ImGui::InputFloat3("##ActorSpawnScale", Features::ActorSpawn::scale);

			if (ImGui::Button("Spawn Actor##ActorSpawn"))
			{
				SDK::UWorld* world = Unreal::World::Get();
				if (world)
				{
					Unreal::Transform spawnTransform;
					spawnTransform.location = spawnTransform.location = { Features::ActorSpawn::location[0], Features::ActorSpawn::location[1], Features::ActorSpawn::location[2] };
					spawnTransform.rotation = { Features::ActorSpawn::rotation[0], Features::ActorSpawn::rotation[1], Features::ActorSpawn::rotation[2] };
					spawnTransform.scale = { Features::ActorSpawn::scale[0], Features::ActorSpawn::scale[1], Features::ActorSpawn::scale[2] };

					if (Features::ActorSpawn::useCharacterLocation || Features::ActorSpawn::useCharacterRotation)
					{
						SDK::APlayerController* playerController = Unreal::PlayerController::Get();
						if (playerController)
						{
							Unreal::Transform playerTransform;

							if (playerController->Pawn)
								playerTransform = Unreal::Actor::GetTransform(playerController->Pawn);
							else if (playerController->PlayerCameraManager)
								playerTransform = Unreal::Actor::GetTransform(playerController->PlayerCameraManager);

							if (Features::ActorSpawn::useCharacterLocation)
								spawnTransform.location = playerTransform.location;

							if (Features::ActorSpawn::useCharacterRotation)
								spawnTransform.rotation = playerTransform.rotation;
						}
					}

					std::vector<std::wstring> actorPathCollection = Utilities::String::Split(Features::ActorSpawn::actorPathBuffer, L'|');
					if (actorPathCollection.size() > 0)
					{
						bool anyActorSpawned = false;

						for (std::wstring& actorPath : actorPathCollection) // <-- Reference!
						{
							std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(actorPath);
							if (SDK::AActor* actorReference = Unreal::Actor::SoftSummon(normalizedPath, spawnTransform))
								anyActorSpawned = true;
						}

						GUI::PlayActionSound(anyActorSpawned);
					}
					else
						GUI::PlayActionSound(false);
				}
				else
					GUI::PlayActionSound(false);
			}
#endif

			ImGui::TreePop();
		}

		ImGui::NewLine();

		if (ImGui::Button("Update##Actors"))
		{
			Features::ActorsList::Update();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::InputText("Search Filter##Actors", Features::ActorsList::filterBuffer, Features::ActorsList::filterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Actors", &Features::ActorsList::filterCaseSensitive);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::ObjectFilterModeComboBox("##Actors", &Features::ActorsList::filterMode);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Check Validness##Actors", &Features::ActorsList::filterCheckValidness);

#ifdef COLLISION_VISUALIZER
		ImGui::Checkbox("Draw Collision##Actors", &Features::CollisionVisualizer::enabled);
		ImGui::SameLine();
		ImGui::TextHint("Draws polygonal wireframe color of which depends on collision type:\n\nBlueish - Collision/Physics.\n* Static Mesh.\n* Primitive (Capsule/Sphere/Box/Spline).\n* Physics Volume.\n\nReddish - Damage/Restriction.\n* Blocking Volume.\n\nGreenish - Event.\n* Trigger Volume.\n\nPinkish - Post Processing.\n* Post Process Volume.\n\nWhite - Unknown/Other.");
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
#endif

#ifdef ACTORS_TRACKING
		ImGui::Checkbox("Enable Tracking##Actors", &Features::ActorsTracker::enabled);
		ImGui::SameLine();
		ImGui::TextHint("Draws circle at root location alongside Actor technical name.\n\nExtremely useful when it's needed to find an specific Actor in 3D space.");
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
#endif

		ImGui::Text("In Distance:");
		ImGui::SameLine();
		if (ImGui::InputFloat("##FilterDistance##Actors", &Features::ActorsList::filterDistance, 100.0f, 1000.0f))
		{
			Features::ActorsList::filterDistance = std::clamp(Features::ActorsList::filterDistance, 0.0f, 1000000.0f);
		}
		ImGui::SameLine();
		ImGui::TextHint("Maximum Actor distance from Player in centimetres. Calculations doesn't update in background!\n\nThat allows to return to the game while keeping needed Actors filtered.");

		ImGui::KeyBindingInput("Update & Re-Filter Actors List:", &Inputs::Keybindings::debug_ActorsListUpdate);
		ImGui::SameLine();
		ImGui::TextHint("Can be found useful when tracking/drawing while filtering Actors In Distance, allowing to update dataset w/o opening the menu.");
#ifdef ACTORS_TRACKING
		ImGui::KeyBindingInput("Toggle Actors Tracking:        ", &Inputs::Keybindings::debug_ActorsListTracking);
#endif
#ifdef COLLISION_VISUALIZER
		ImGui::KeyBindingInput("Toggle Collision Draw:         ", &Inputs::Keybindings::debug_ActorsListCollisionDraw);
#endif

		ImGui::NewLine();

		if (ImGui::Button("Enable Collision (All)##Actors"))
		{
			bool anyActorCollisionEnabled = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					actor.reference->SetActorEnableCollision(true);
					anyActorCollisionEnabled = true;
				}
			}

			GUI::PlayActionSound(anyActorCollisionEnabled);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Button("Disable Collision (All)##Actors"))
		{
			bool anyActorCollisionDisabled = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					actor.reference->SetActorEnableCollision(false);
					anyActorCollisionDisabled = true;
				}
			}

			GUI::PlayActionSound(anyActorCollisionDisabled);
		}

		if (ImGui::Button("Set Visible (All)##Actors"))
		{
			bool anyActorShown = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					Unreal::Actor::SetIsVisible(actor.reference, true);
					anyActorShown = true;
				}
			}

			GUI::PlayActionSound(anyActorShown);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		if (ImGui::Button("Set Hidden (All)##Actors"))
		{
			bool anyActorHidden = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					Unreal::Actor::SetIsVisible(actor.reference, false);
					anyActorHidden = true;
				}
			}

			GUI::PlayActionSound(anyActorHidden);
		}

		if (ImGui::Button("Destroy (All)##Actors"))
		{
			bool anyActorDestroyed = false;
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference)
				{
					actor.reference->K2_DestroyActor();
					anyActorDestroyed = true;
				}
			}

			GUI::PlayActionSound(anyActorDestroyed);
		}

		ImGui::NewLine();

		Features::ActorsList::Filter();

		/* Output to user interface Actors that are matching "Search Filter" */
		for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
		{
			bool isTreeNodeOpen;
			if (Features::ActorsList::filterCheckValidness)
			{
				ImU32 color = Math::ColorFloat4_ToU32(Unreal::Actor::IsValid(actor.reference) ? Features::ActorsList::color_Valid : Features::ActorsList::color_Invalid);

				ImGui::PushStyleColor(ImGuiCol_Text, color);
				isTreeNodeOpen = ImGui::TreeNode(actor.objectName.c_str());
				ImGui::PopStyleColor();
			}
			else
				isTreeNodeOpen = ImGui::TreeNode(actor.objectName.c_str());

			if (isTreeNodeOpen)
			{
				ImGui::PushID(actor.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::ActorsList::filterBuffer, actor.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::ActorsList::filterBuffer, sizeof(Features::ActorsList::filterBuffer), actor.objectName.c_str());
					Features::ActorsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::Text("Actor Class: %s", actor.className.c_str());
				if (ImGui::TreeNode("Class Hierarchy"))
				{
					for (std::string className : actor.superClassesNames)
					{
						ImGui::Text(("- " + className).c_str());
					}

					ImGui::TreePop();
				}
				ImGui::Text("Actor Object: %s", actor.objectName.c_str());

				ImGui::NewLine();

				ImGui::TextVectorColored("Location:", actor.transform.location);
				static float customLocation[3];
				if (ImGui::Button("Copy##Location"))
				{
					customLocation[0] = actor.transform.location.X;
					customLocation[1] = actor.transform.location.Y;
					customLocation[2] = actor.transform.location.Z;
					GUI::PlayActionSound(true);
				}
				ImGui::SameLine();
				ImGui::InputFloat3("##Location", customLocation);
				ImGui::SameLine();
				if (ImGui::Button("Set##Location"))
				{
					if (actor.reference)
					{
						bool isSuccess = Unreal::Actor::TeleportTo(actor.reference, SDK::FVector(customLocation[0], customLocation[1], customLocation[2]));
						GUI::PlayActionSound(isSuccess);

						Features::ActorsList::Update();
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TextRotatorColored("Rotation:", actor.transform.rotation);
				static float customRotation[3];
				if (ImGui::Button("Copy##Rotation"))
				{
					customRotation[0] = actor.transform.rotation.Pitch;
					customRotation[1] = actor.transform.rotation.Yaw;
					customRotation[2] = actor.transform.rotation.Roll;
					GUI::PlayActionSound(true);
				}
				ImGui::SameLine();
				ImGui::InputFloat3("##Rotation", customRotation);
				ImGui::SameLine();
				if (ImGui::Button("Set##Rotation"))
				{
					if (actor.reference)
					{
						bool isSuccess = Unreal::Actor::TeleportTo(actor.reference, SDK::FRotator(customRotation[0], customRotation[1], customRotation[2]));
						GUI::PlayActionSound(isSuccess);

						Features::ActorsList::Update();
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TextVectorColored("Scale:", actor.transform.scale);
				static float customScale[3];
				if (ImGui::Button("Copy##Scale"))
				{
					customScale[0] = actor.transform.scale.X;
					customScale[1] = actor.transform.scale.Y;
					customScale[2] = actor.transform.scale.Z;
					GUI::PlayActionSound(true);
				}
				ImGui::SameLine();
				ImGui::InputFloat3("##Scale", customScale);
				ImGui::SameLine();
				if (ImGui::Button("Set##Scale"))
				{
					if (actor.reference)
					{
						actor.reference->SetActorScale3D(SDK::FVector(customScale[0], customScale[1], customScale[2]));
						GUI::PlayActionSound(true);

						Features::ActorsList::Update();
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				if (ImGui::Button("Make Static"))
				{
					if (actor.reference && actor.reference->RootComponent)
					{
						actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Static;
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Make Stationary"))
				{
					if (actor.reference && actor.reference->RootComponent)
					{
						actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Stationary;
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Make Movable"))
				{
					if (actor.reference && actor.reference->RootComponent)
					{
						actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Movable;
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				ImGui::TextHint("Static - Never moves and relies entirely on baked lightmaps and shadows for lighting.\nLowest performance cost, ideal for architecture and environment pieces.\n\nStationary - Cannot move but allows changes to materials and visibility, and combines baked lighting with some dynamic shadow interactions.\nSlightly higher cost than Static, good for objects that stay in place but need minor runtime variations.\n\nMovable - Can move, rotate, scale, or animate and uses fully dynamic lighting and shadows.\nHighest performance cost, suited for characters, doors, vehicles, and interactive gameplay objects.");

				if (ImGui::Button("Enable Collision"))
				{
					if (actor.reference)
					{
						actor.reference->SetActorEnableCollision(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Disable Collision"))
				{
					if (actor.reference)
					{
						actor.reference->SetActorEnableCollision(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				static bool visibilityPropagateToComponents = false;
				if (ImGui::Button("Set Visible"))
				{
					if (actor.reference)
					{
						Unreal::Actor::SetIsVisible(actor.reference, true, visibilityPropagateToComponents);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Set Hidden"))
				{
					if (actor.reference)
					{
						Unreal::Actor::SetIsVisible(actor.reference, false, visibilityPropagateToComponents);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				ImGui::Checkbox("Propagate To Components", &visibilityPropagateToComponents);

				if (ImGui::Button("Teleport To Actor"))
				{
					SDK::ACharacter* character = Unreal::Character::Get();
					if (character)
					{
						bool isSuccess = Unreal::Actor::TeleportTo(character, actor.transform.location);
						GUI::PlayActionSound(isSuccess);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Teleport Actor To Me"))
				{
					if (actor.reference)
					{
						SDK::ACharacter* character = Unreal::Character::Get();
						if (character)
						{
							SDK::FVector location = character->K2_GetActorLocation();

							bool isSuccess = Unreal::Actor::TeleportTo(actor.reference, location);
							GUI::PlayActionSound(isSuccess);
						}
						else
							GUI::PlayActionSound(false);
					}
					else
						GUI::PlayActionSound(false);
				}

				if (ImGui::Button("Destroy"))
				{
					if (actor.reference)
					{
						actor.reference->K2_DestroyActor();
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				ImGui::Text("Custom Time Dilation");
				static float customTimeDilation = 1.0f;
				if (ImGui::Button("Get##CustomTimeDilation"))
				{
					if (actor.reference)
					{
						customTimeDilation = actor.reference->CustomTimeDilation;
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				ImGui::InputFloat("##CustomTimeDilation", &customTimeDilation, 0.1f, 1.0f);
				ImGui::SameLine();
				if (ImGui::Button("Set##CustomTimeDilation"))
				{
					if (actor.reference)
					{
						actor.reference->CustomTimeDilation = customTimeDilation;
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				ImGui::Text("Blend Time");
				ImGui::SameLine();
				static float viewTargetBlendTime = 1.0f;
				ImGui::InputFloat("##ViewTargetBlendTime", &viewTargetBlendTime, 0.1f, 1.0f);

				ImGui::Text("Blend Exponent");
				ImGui::SameLine();
				static float viewTargetBlendExponent = 1.0f;
				ImGui::InputFloat("##ViewTargetBlendExponent", &viewTargetBlendExponent, 0.1f, 1.0f);

				if (ImGui::Button("View Target (Linear)"))
				{
					if (actor.reference)
					{
						Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Linear, viewTargetBlendTime, viewTargetBlendExponent);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("View Target (Cubic)"))
				{
					if (actor.reference)
					{
						Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Cubic, viewTargetBlendTime, viewTargetBlendExponent);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

#ifdef ACTOR_KIND
				if (actor.kind != Unreal::Actor::E_ActorKind::General)
				{
					ImGui::NewLine();

					switch (actor.kind)
					{
					case Unreal::Actor::E_ActorKind::PointLight:
						if (SDK::APointLight* pointLight = static_cast<SDK::APointLight*>(actor.reference))
						{
							ImGui::SetFontTitle();
							ImGui::Text("Point Light Settings");
							ImGui::SetFontRegular();

							ImGui::BeginDisabled(pointLight->PointLightComponent == nullptr);
							if (ImGui::TreeNode("Details##PointLightSettings"))
							{
								if (SDK::UPointLightComponent* pointLightComponent = pointLight->PointLightComponent)
								{
									if (ImGui::Button("Enable Cast Shadows##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastShadows(true);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Shadows##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastShadows(false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									if (ImGui::Button("Enable Cast Volumetric Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastVolumetricShadow(true);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Volumetric Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastVolumetricShadow(false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}


									if (ImGui::Button("Enable Cast Deep Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastDeepShadow(true);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Deep Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastDeepShadow(false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									if (ImGui::Button("Enable Cast Raytaced Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastRaytracedShadow(true);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Raytaced Shadow##PointLight"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetCastRaytracedShadow(false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Intensity");
									static float pointLightIntensity = 0.0f;
									if (ImGui::Button("Get##PointLightIntensity"))
									{
										if (pointLightComponent)
										{
											pointLightIntensity = pointLightComponent->Intensity;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##PointLightIntensity", &pointLightIntensity, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##PointLightIntensity"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetIntensity(pointLightIntensity);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Source Radius");
									static float pointLightSourceRadius = 0.0f;
									if (ImGui::Button("Get##PointLightSourceRadius"))
									{
										if (pointLightComponent)
										{
											pointLightSourceRadius = pointLightComponent->SourceRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##PointLightSourceRadius", &pointLightSourceRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##PointLightSourceRadius"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetSourceRadius(pointLightSourceRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Soft Source Radius");
									static float pointLightSoftSourceRadius = 0.0f;
									if (ImGui::Button("Get##PointLightSoftSourceRadius"))
									{
										if (pointLightComponent)
										{
											pointLightSoftSourceRadius = pointLightComponent->SoftSourceRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##PointLightSoftSourceRadius", &pointLightSoftSourceRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##PointLightSoftSourceRadius"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetSoftSourceRadius(pointLightSoftSourceRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Attenuation Radius");
									static float pointLightAttenuationRadius = 0.0f;
									if (ImGui::Button("Get##PointLightAttenuationRadius"))
									{
										if (pointLightComponent)
										{
											pointLightAttenuationRadius = pointLightComponent->AttenuationRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##PointLightAttenuationRadius", &pointLightAttenuationRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##PointLightAttenuationRadius"))
									{
										if (pointLightComponent)
										{
											pointLightComponent->SetAttenuationRadius(pointLightAttenuationRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Color");
									static float pointLightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
									if (ImGui::Button("Get##PointLightColor"))
									{
										if (pointLightComponent)
										{
											/* ColorPicker4 can only understand normalized values (in range of 0.0f to 1.0f) */
											pointLightColor[0] = pointLightComponent->LightColor.R / 255.0f;
											pointLightColor[1] = pointLightComponent->LightColor.G / 255.0f;
											pointLightColor[2] = pointLightComponent->LightColor.B / 255.0f;
											pointLightColor[3] = pointLightComponent->LightColor.A / 255.0f;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Set##PointLightColor"))
									{
										if (pointLightComponent)
										{
											SDK::FLinearColor linearColor;
											linearColor.R = pointLightColor[0];
											linearColor.G = pointLightColor[1];
											linearColor.B = pointLightColor[2];
											linearColor.A = pointLightColor[3];

											pointLightComponent->SetLightColor(linearColor, false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::ColorPicker4("##PointLightColor", pointLightColor);
								}
								else
									ImGui::Text("Point Light Component Doesn't Exist!");

								ImGui::TreePop();
							}
							ImGui::EndDisabled();
						}
						break;

					case Unreal::Actor::E_ActorKind::SpotLight:
						if (SDK::ASpotLight* spotLight = static_cast<SDK::ASpotLight*>(actor.reference))
						{
							ImGui::SetFontTitle();
							ImGui::Text("Spot Light Settings");
							ImGui::SetFontRegular();

							ImGui::BeginDisabled(spotLight->SpotLightComponent == nullptr);
							if (ImGui::TreeNode("Details##SpotLightSettings"))
							{
								if (SDK::USpotLightComponent* spotLightComponent = spotLight->SpotLightComponent)
								{
									if (ImGui::Button("Enable Cast Shadows##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastShadows(true);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Shadows##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastShadows(false);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}

									if (ImGui::Button("Enable Cast Volumetric Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastVolumetricShadow(true);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Volumetric Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastVolumetricShadow(false);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}


									if (ImGui::Button("Enable Cast Deep Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastDeepShadow(true);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Deep Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastDeepShadow(false);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}

									if (ImGui::Button("Enable Cast Raytaced Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastRaytracedShadow(true);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Disable Cast Raytaced Shadow##SpotLight"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetCastRaytracedShadow(false);
											GUI::PlayActionSound(false);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Intensity");
									static float spotLightIntensity = 0.0f;
									if (ImGui::Button("Get##SpotLightIntensity"))
									{
										if (spotLightComponent)
										{
											spotLightIntensity = spotLightComponent->Intensity;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightIntensity", &spotLightIntensity, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightIntensity"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetIntensity(spotLightIntensity);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Source Radius");
									static float spotLightSourceRadius = 0.0f;
									if (ImGui::Button("Get##SpotLightSourceRadius"))
									{
										if (spotLightComponent)
										{
											spotLightSourceRadius = spotLightComponent->SourceRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightSourceRadius", &spotLightSourceRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightSourceRadius"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetSourceRadius(spotLightSourceRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Soft Source Radius");
									static float spotLightSoftSourceRadius = 0.0f;
									if (ImGui::Button("Get##SpotLightSoftSourceRadius"))
									{
										if (spotLightComponent)
										{
											spotLightSoftSourceRadius = spotLightComponent->SoftSourceRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightSoftSourceRadius", &spotLightSoftSourceRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightSoftSourceRadius"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetSoftSourceRadius(spotLightSoftSourceRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Attenuation Radius");
									static float spotLightAttenuationRadius = 0.0f;
									if (ImGui::Button("Get##SpotLightAttenuationRadius"))
									{
										if (spotLightComponent)
										{
											spotLightAttenuationRadius = spotLightComponent->AttenuationRadius;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightAttenuationRadius", &spotLightAttenuationRadius, 10.0f, 100.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightAttenuationRadius"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetAttenuationRadius(spotLightAttenuationRadius);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Inner Cone Angle");
									static float spotLightInnerConeAngle = 0.0f;
									if (ImGui::Button("Get##SpotLightInnerConeAngle"))
									{
										if (spotLightComponent)
										{
											spotLightInnerConeAngle = spotLightComponent->InnerConeAngle;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightInnerConeAngle", &spotLightInnerConeAngle, 1.0f, 10.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightInnerConeAngle"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetInnerConeAngle(spotLightInnerConeAngle);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Outer Cone Angle");
									static float spotLightOuterConeAngle = 0.0f;
									if (ImGui::Button("Get##SpotLightOuterConeAngle"))
									{
										if (spotLightComponent)
										{
											spotLightOuterConeAngle = spotLightComponent->OuterConeAngle;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##SpotLightOuterConeAngle", &spotLightOuterConeAngle, 1.0f, 10.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightOuterConeAngle"))
									{
										if (spotLightComponent)
										{
											spotLightComponent->SetOuterConeAngle(spotLightOuterConeAngle);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}

									ImGui::NewLine();

									ImGui::Text("Color");
									static float spotLightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
									if (ImGui::Button("Get##SpotLightColor"))
									{
										if (spotLightComponent)
										{
											/* ColorPicker4 can only understand normalized values (in range of 0.0f to 1.0f) */
											spotLightColor[0] = spotLightComponent->LightColor.R / 255.0f;
											spotLightColor[1] = spotLightComponent->LightColor.G / 255.0f;
											spotLightColor[2] = spotLightComponent->LightColor.B / 255.0f;
											spotLightColor[3] = spotLightComponent->LightColor.A / 255.0f;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									if (ImGui::Button("Set##SpotLightColor"))
									{
										if (spotLightComponent)
										{
											SDK::FLinearColor linearColor;
											linearColor.R = spotLightColor[0];
											linearColor.G = spotLightColor[1];
											linearColor.B = spotLightColor[2];
											linearColor.A = spotLightColor[3];

											spotLightComponent->SetLightColor(linearColor, false);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::ColorPicker4("##SpotLightColor", spotLightColor);
								}
								else
									ImGui::Text("Spot Light Component Doesn't Exist!");

								ImGui::TreePop();
							}
							ImGui::EndDisabled();
						}
						break;

					case Unreal::Actor::E_ActorKind::Pawn:
						if (SDK::APawn* pawn = static_cast<SDK::APawn*>(actor.reference))
						{
#ifdef SOFT_PATH
							ImGui::SetFontTitle();
							ImGui::Text("Pawn Animation");
							ImGui::SetFontSmall();
							ImGui::Text("Dynamic Animation playing by soft path, for example \"/Game/Character/AnimAsset_Jump.AnimAsset_Jump\".");
							ImGui::SetFontRegular();

							if (ImGui::TreeNode("Details##PawnAnimation"))
							{
								ImGui::SetFontTitle();
								ImGui::Text("Animation Montage");
								ImGui::SetFontRegular();
								ImGui::Text("Animation Montage Path:");
								ImGui::SameLine();
								ImGui::InputText("##PawnAnimationMontage", Features::PawnAnimation::animationMontagePathBuffer, Features::PawnAnimation::animationMontagePathBufferSize);

								ImGui::Text("Start At:              ");
								ImGui::SameLine();
								ImGui::InputFloat("##PawnAnimationMontageStartAt", &Features::PawnAnimation::animationMontageStartAt, 0.1f, 1.0f);

								ImGui::Text("Play Rate:             ");
								ImGui::SameLine();
								ImGui::InputFloat("##PawnAnimationMontagePlayRate", &Features::PawnAnimation::animationMontagePlayRate, 0.1f, 1.0f);

								ImGui::Checkbox("Stop All Montages", &Features::PawnAnimation::animationMontageStopAllMontages);

								if (ImGui::Button("Play##PawnAnimationMontage"))
								{
									std::wstring assetPath = Utilities::String::ToWString(Features::PawnAnimation::animationPathBuffer);
									std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(assetPath);
									GUI::PlayActionSound(Unreal::Pawn::PlayAnimationMontage(pawn, normalizedPath, Features::PawnAnimation::animationMontageStartAt, Features::PawnAnimation::animationMontagePlayRate, Features::PawnAnimation::animationMontageStopAllMontages));
								}

								ImGui::NewLine();

								ImGui::SetFontTitle();
								ImGui::Text("Animation Asset");
								ImGui::SetFontRegular();
								ImGui::Text("Animation Path:");
								ImGui::SameLine();
								ImGui::InputText("##PawnAnimation", Features::PawnAnimation::animationPathBuffer, Features::PawnAnimation::animationPathBufferSize);

								ImGui::Checkbox("Animation Looping", &Features::PawnAnimation::animationLooping);

								if (ImGui::Button("Play##PawnAnimation"))
								{
									std::wstring assetPath = Utilities::String::ToWString(Features::PawnAnimation::animationPathBuffer);
									std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(assetPath);
									GUI::PlayActionSound(Unreal::Pawn::PlayAnimation(pawn, normalizedPath.c_str(), Features::PawnAnimation::animationLooping));
								}

								ImGui::TreePop();
							}

							ImGui::NewLine();
#endif

							ImGui::SetFontTitle();
							ImGui::Text("Pawn Actions");
							ImGui::SetFontRegular();

							if (ImGui::TreeNode("Details##PawnActions"))
							{
								if (ImGui::Button("Possess"))
								{
									if (pawn)
									{
										SDK::APlayerController* playerController = Unreal::PlayerController::Get();
										if (playerController)
										{
											playerController->Possess(pawn);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									else
										GUI::PlayActionSound(false);
								}

								ImGui::TreePop();
							}
						}
						break;

					case Unreal::Actor::E_ActorKind::TextRender:
						if (SDK::ATextRenderActor* textRender = static_cast<SDK::ATextRenderActor*>(actor.reference))
						{
							ImGui::SetFontTitle();
							ImGui::Text("Text Render Settings");
							ImGui::SetFontRegular();

							ImGui::BeginDisabled(textRender->TextRender == nullptr);
							if (ImGui::TreeNode("Details##TextRender"))
							{
								if (SDK::UTextRenderComponent* textRenderComponent = textRender->TextRender)
								{
									ImGui::Text("Content");
									static const size_t textRenderContentBufferSize = 255;
									static char textRenderContentBuffer[textRenderContentBufferSize] = {};
									if (ImGui::Button("Get##TextRenderContent"))
									{
										if (textRenderComponent)
										{
											strcpy_s(textRenderContentBuffer, textRenderComponent->Text.ToString().c_str());
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputText("##TextRenderContent", textRenderContentBuffer, textRenderContentBufferSize);

									ImGui::NewLine();

									ImGui::Text("Font Size");
									static float textRenderFontSize = 26.0f;
									if (ImGui::Button("Get##TextRenderFontSize"))
									{
										if (textRenderComponent)
										{
											textRenderFontSize = textRenderComponent->WorldSize;
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
									ImGui::SameLine();
									ImGui::InputFloat("##TextRenderFontSize", &textRenderFontSize, 1.0f, 10.0f);
									ImGui::SameLine();
									if (ImGui::Button("Set##TextRenderFontSize"))
									{
										if (textRenderComponent)
										{
											textRenderComponent->SetWorldSize(textRenderFontSize);
											GUI::PlayActionSound(true);
										}
										else
											GUI::PlayActionSound(false);
									}
								}
								else
									ImGui::Text("Text Render Component Doesn't Exist!");

								ImGui::TreePop();
							}

							ImGui::EndDisabled();
						}
						break;
					}
				}

				ImGui::NewLine();
#endif
				Templates::Functions::Draw(actor.reference);

				ImGui::NewLine();

				ImGui::SetFontTitle();
				ImGui::Text("Components");
				ImGui::SetFontRegular();
				if (ImGui::TreeNode("Details##Components"))
				{
					ImGui::InputText("Search Filter##Components", Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterBufferSize);
					ImGui::SameLine();
					ImGui::Spacing();
					ImGui::SameLine();
					ImGui::Checkbox("Case Sensitive##Components", &Features::ActorsList::componentsFilterCaseSensitive);
					ImGui::SameLine();
					ImGui::Spacing();
					ImGui::SameLine();
					ImGui::ObjectFilterModeComboBox("##Components", &Features::ActorsList::componentsFilterMode);

					ImGui::NewLine();

					/* Filter Components by "Search Filter" */
					std::vector<Unreal::ActorComponent::DataStructure> filteredComponents;
					switch (Features::ActorsList::componentsFilterMode)
					{
					case ImGui::E_ObjectFilterMode::ClassName:
						filteredComponents = Unreal::ActorComponent::FilterByClassName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
						break;

					case ImGui::E_ObjectFilterMode::ObjectName:
						filteredComponents = Unreal::ActorComponent::FilterByObjectName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
						break;

					case ImGui::E_ObjectFilterMode::All:
						filteredComponents = Unreal::ActorComponent::FilterByClassAndObjectName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
						break;
					}

					for (Unreal::ActorComponent::DataStructure& component : filteredComponents) // <-- Reference!
					{
						if (ImGui::TreeNode(component.objectName.c_str()))
						{
							ImGui::Text("Component Class: %s", component.className.c_str());
							ImGui::Text("Component Object: %s", component.objectName.c_str());

							ImGui::NewLine();

							ImGui::TextBoolColored("Is Active:", component.isActive);
							ImGui::TextBoolColored("Auto Activate:", component.autoActivate);
							ImGui::TextBoolColored("Editor Only:", component.editorOnly);
							if (ImGui::Button("Activate"))
							{
								if (component.reference)
								{
									component.reference->Activate(false);
									component.isActive = true;
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
							ImGui::SameLine();
							if (ImGui::Button("Reset"))
							{
								if (component.reference)
								{
									component.reference->Activate(true);
									component.isActive = true;
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}
							ImGui::SameLine();
							if (ImGui::Button("Deactivate"))
							{
								if (component.reference)
								{
									component.reference->Deactivate();
									component.isActive = false;
									GUI::PlayActionSound(true);
								}
								else
									GUI::PlayActionSound(false);
							}

							ImGui::NewLine();

							ImGui::TextBoolColored("Net Addressible:", component.netAddressible);
							ImGui::TextBoolColored("Replicates:", component.replicates);

							ImGui::NewLine();

							ImGui::Text("Creation Method: %d", component.creationMethod);

							ImGui::NewLine();

							Templates::Functions::Draw(component.reference);

							ImGui::NewLine();
							ImGui::TreePop();
						}
					}

					ImGui::TreePop();
				}

				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		}
	}
}

void Templates::Menus::Debug::Sub_Widgets()
{
	ImGui::SetFontTitle();
	ImGui::Text("Widgets");
	ImGui::SetFontRegular();
	if (ImGui::CollapsingHeader("Details##Widgets"))
	{
#ifdef SOFT_PATH
		ImGui::SetFontTitle();
		ImGui::Text("Widget Construct");
		Templates::Descriptions::SoftPath::Draw("Widget", "/Game/Widgets/WBP_Credits.WBP_Credits_C");

		if (ImGui::TreeNode("Details##WidgetConstruct"))
		{
			ImGui::Text("Widget Path:");
			ImGui::SameLine();
			ImGui::InputText("##WidgetConstruct", Features::WidgetConstruct::widgetPathBuffer, Features::WidgetConstruct::widgetPathBufferSize);

			ImGui::Text("Z Order:    ");
			ImGui::SameLine();
			ImGui::InputInt("##WidgetZOrder", &Features::WidgetConstruct::zOrder, 1, 10);

			if (ImGui::Button("Construct Widget##WidgetConstruct"))
			{
				std::vector<std::wstring> widgetPathCollection = Utilities::String::Split(Features::WidgetConstruct::widgetPathBuffer, L'|');
				if (widgetPathCollection.size() > 0)
				{
					bool anyWidgetConstructed = false;

					for (std::wstring& widgetPath : widgetPathCollection) // <-- Reference!
					{
						std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(widgetPath);
						if (SDK::UUserWidget* widgetReference = Unreal::UserWidget::SoftConstruct(normalizedPath))
						{
							widgetReference->AddToViewport(Features::WidgetConstruct::zOrder);
							anyWidgetConstructed = true;
						}
					}

					GUI::PlayActionSound(anyWidgetConstructed);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::TreePop();
		}

		ImGui::NewLine();
#endif

		if (ImGui::Button("Update##Widgets"))
		{
			Features::WidgetsList::Update();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::InputText("Search Filter##Widgets", Features::WidgetsList::filterBuffer, Features::WidgetsList::filterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Widgets", &Features::WidgetsList::filterCaseSensitive);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::ObjectFilterModeComboBox("##Widgets", &Features::WidgetsList::filterMode);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Top Level Only##Widgets", &Features::WidgetsList::filterTopLevelOnly);

		ImGui::NewLine();

		if (ImGui::Button("Set Visible (All)##Widgets"))
		{
			Features::WidgetsList::storedWidgetsVisibility.clear();
			bool anyWidgetAffected = false;

			for (Unreal::UserWidget::DataStructure widget : Features::WidgetsList::filteredWidgets)
			{
				if (widget.reference == nullptr)
					continue;

				Features::WidgetsList::storedWidgetsVisibility.push_back({ widget.reference, widget.visibility });
				widget.reference->SetVisibility(SDK::ESlateVisibility::Visible);

				anyWidgetAffected = true;
			}

			GUI::PlayActionSound(anyWidgetAffected);
		}
		ImGui::SameLine();
		if (ImGui::Button("Set Hidden (All)##Widgets"))
		{
			Features::WidgetsList::storedWidgetsVisibility.clear();
			bool anyWidgetAffected = false;

			for (Unreal::UserWidget::DataStructure widget : Features::WidgetsList::filteredWidgets)
			{
				if (widget.reference == nullptr)
					continue;

				Features::WidgetsList::storedWidgetsVisibility.push_back({ widget.reference, widget.visibility });
				widget.reference->SetVisibility(SDK::ESlateVisibility::Hidden);

				anyWidgetAffected = true;
			}

			GUI::PlayActionSound(anyWidgetAffected);
		}
		ImGui::SameLine();
		if (ImGui::Button("Restore Previous State##Widgets"))
		{
			bool anyWidgetAffected = false;

			for (std::pair<SDK::UUserWidget*, SDK::ESlateVisibility> widgetVisibility : Features::WidgetsList::storedWidgetsVisibility)
			{
				if (widgetVisibility.first == nullptr)
					continue;

				widgetVisibility.first->SetVisibility(widgetVisibility.second);
				anyWidgetAffected = true;
			}

			GUI::PlayActionSound(anyWidgetAffected);
		}

		ImGui::NewLine();

		Features::WidgetsList::Filter();

		for (Unreal::UserWidget::DataStructure& widget : Features::WidgetsList::filteredWidgets) // <-- Reference!
		{
			if (ImGui::TreeNode(widget.objectName.c_str()))
			{
				ImGui::PushID(widget.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::WidgetsList::filterBuffer, widget.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::WidgetsList::filterBuffer, sizeof(Features::WidgetsList::filterBuffer), widget.objectName.c_str());
					Features::WidgetsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::Text("Widget Class: %s", widget.className.c_str());
				ImGui::Text("Widget Object: %s", widget.objectName.c_str());

				ImGui::NewLine();

				ImGui::Text("Parent: %s", widget.parent ? widget.parent->GetFullName().c_str() : "None");

				ImGui::NewLine();

				ImGui::TextBoolColored("Is Top Level:", widget.isInViewport);
				ImGui::Text("Visibility: %d", widget.visibility);
				ImGui::SameLine();
				ImGui::TextHint("ESlateVisibility\n\n0 - Visible\n1 - Collapsed\n2 - Hidden\n3 - HitTestInvisible\n4 - SelfHitTestInvisible");
				static int32_t customVisibility = 0;
				ImGui::SliderInt("##CustomVisibility", &customVisibility, 0, 4);
				ImGui::SameLine();
				if (ImGui::Button("Set##Visibility"))
				{
					if (widget.reference)
					{
						widget.reference->SetVisibility(static_cast<SDK::ESlateVisibility>(customVisibility));
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				if (ImGui::Button("Remove From Parent"))
				{
					if (widget.reference)
					{
						widget.reference->RemoveFromParent();
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove From Viewport"))
				{
					if (widget.reference)
					{
						widget.reference->RemoveFromViewport();
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				Templates::Functions::Draw(widget.reference);

				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		}
	}
}

void Templates::Menus::Debug::Sub_Objects()
{
	ImGui::SetFontTitle();
	ImGui::Text("Objects");
	ImGui::SetFontRegular();
	if (ImGui::CollapsingHeader("Details##Objects"))
	{
#ifdef SOFT_PATH
		ImGui::SetFontTitle();
		ImGui::Text("Object Construct");
		Templates::Descriptions::SoftPath::Draw("Object", "/Game/Subsystems/WeatherController.WeatherController");

		if (ImGui::TreeNode("Details##ObjectConstruct"))
		{
			ImGui::Text("Object Path:");
			ImGui::SameLine();
			ImGui::InputText("##ObjectConstruct", Features::ObjectConstruct::objectPathBuffer, Features::ObjectConstruct::objectPathBufferSize);

			if (ImGui::Button("Construct Object##ObjectConstruct"))
			{
				std::vector<std::wstring> objectPathCollection = Utilities::String::Split(Features::ObjectConstruct::objectPathBuffer, L'|');
				if (objectPathCollection.size() > 0)
				{
					bool anyObjectConstructed = false;

					for (std::wstring& objectPath : objectPathCollection) // <-- Reference!
					{
						std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(objectPath);
						if (SDK::UObject* objectReference = Unreal::Object::SoftLoadObject(normalizedPath))
						{
							SDK::UClass* objectClass = objectReference->Class;

							if (SDK::UObject* objectInstance = SDK::UGameplayStatics::SpawnObject(objectClass, objectReference))
							{
								anyObjectConstructed = true;
							}
						}
					}

					GUI::PlayActionSound(anyObjectConstructed);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::TreePop();
		}

		ImGui::NewLine();
#endif

		if (ImGui::Button("Update##Objects"))
		{
			Features::ObjectsList::Update();
			GUI::PlayActionSound(true);
		}
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::InputText("Search Filter##Objects", Features::ObjectsList::filterBuffer, Features::ObjectsList::filterBufferSize);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::Checkbox("Case Sensitive##Objects", &Features::ObjectsList::filterCaseSensitive);
		ImGui::SameLine();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::ObjectFilterModeComboBox("##Objects", &Features::ObjectsList::filterMode);

		ImGui::NewLine();

		Features::ObjectsList::Filter();

		for (Unreal::Object::DataStructure& object : Features::ObjectsList::filteredObjects) // <-- Reference!
		{
			if (ImGui::TreeNode(object.objectName.c_str()))
			{
				ImGui::PushID(object.objectName.c_str());

				ImGui::BeginDisabled(std::strcmp(Features::ObjectsList::filterBuffer, object.objectName.c_str()) == 0);
				if (ImGui::Button("Focus On"))
				{
					std::snprintf(Features::ObjectsList::filterBuffer, sizeof(Features::ObjectsList::filterBuffer), object.objectName.c_str());
					Features::ObjectsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

					GUI::PlayActionSound(true);
				}
				ImGui::EndDisabled();

				ImGui::NewLine();

				ImGui::Text("Class: %s", object.className.c_str());
				if (ImGui::TreeNode("Class Hierarchy"))
				{
					for (std::string className : object.superClassesNames)
					{
						ImGui::Text(("- " + className).c_str());
					}

					ImGui::TreePop();
				}

				ImGui::Text("Object: %s", object.objectName.c_str());

				ImGui::NewLine();

				Templates::Functions::Draw(object.reference);

				ImGui::NewLine();
				ImGui::PopID();
				ImGui::TreePop();
			}
		}
	}
}


void Templates::Menus::Debug::Draw()
{
	if (ImGui::BeginMenu("Debug"))
	{
		if (Features::Debug::enabled == false)
		{
			if (ImGui::Button("Start"))
			{
				if (Features::Debug::autoUpdate == false)
					Features::Debug::ThreadSafeUpdate();

				Features::Debug::enabled = true;
				GUI::PlayActionSound(true);
			}
		}
		else
		{
			if (Features::Debug::autoUpdate)
			{
				float updatesPerSecond = 1.0f / Features::Debug::autoUpdateDelay;
				if (updatesPerSecond > 1.0f)
					ImGui::Text("Updates %d times per second", (int32_t)(updatesPerSecond));
				else
				{
					float updatesPerMinute = 60.0f / Features::Debug::autoUpdateDelay;
					if (updatesPerMinute > 1.0f)
						ImGui::Text("Updates %d times per minute", (int32_t)(updatesPerMinute));
					else
					{
						float updatesPerHour = 3600.0f / Features::Debug::autoUpdateDelay;
						if (updatesPerHour > 1.0f)
							ImGui::Text("Updates %d times per hour", (int32_t)(updatesPerHour));
						else
						{
							float updatesPerDay = 86400.0f / Features::Debug::autoUpdateDelay;
							if (updatesPerDay > 1.0f)
								ImGui::Text("Updates %d times per day", (int32_t)(updatesPerDay));
							else
								ImGui::Text("Updates periodically", (int32_t)(updatesPerDay));
						}
					}
				}
				if (ImGui::InputFloat("Auto Update Delay", &Features::Debug::autoUpdateDelay, 0.01f, 0.1f))
				{
					if (Features::Debug::autoUpdateDelay < 0.01f)
						Features::Debug::autoUpdateDelay = 0.01f;

					Features::Config::Save();
				}

				const double now = ImGui::GetTime();
				const double elapsed = now - Features::Debug::lastUpdateTime;

				if (elapsed >= Features::Debug::autoUpdateDelay)
					Features::Debug::ThreadSafeUpdate();
			}
			else
			{
				const double now = ImGui::GetTime();
				const double elapsed = now - Features::Debug::lastUpdateTime;
				if (elapsed < 60.0)
				{
					int seconds = (int)elapsed;
					ImGui::Text("Last Update: %d %s ago", seconds, (seconds == 1 ? "second" : "seconds"));
				}
				else if (elapsed < 3600.0)
				{
					int minutes = (int)(elapsed / 60.0);
					ImGui::Text("Last Update: %d %s ago", minutes, (minutes == 1 ? "minute" : "minutes"));
				}
				else if (elapsed < 86400.0)
				{
					int hours = (int)(elapsed / 3600.0);
					ImGui::Text("Last Update: %d %s ago", hours, (hours == 1 ? "hour" : "hours"));
				}
				else
				{
					int days = (int)(elapsed / 86400.0);
					ImGui::Text("Last Update: %d %s ago", days, (days == 1 ? "day" : "days"));
				}
			}


			ImGui::BeginDisabled(Features::Debug::autoUpdate);
			if (ImGui::Button("Update##DebugInformation"))
			{
				Features::Debug::ThreadSafeUpdate();
				GUI::PlayActionSound(true);
			}
			ImGui::EndDisabled();
			ImGui::SameLine();
			if (ImGui::Checkbox("Auto", &Features::Debug::autoUpdate))
			{
				Features::Config::Save();
			}
			if (ImGui::Button("Stop"))
			{
				Features::Debug::enabled = false;
				GUI::PlayActionSound(true);
			}

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Engine();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_GameInstance();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_GameMode();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_PlayerController();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_World();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Actors();
			
			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Widgets();

			ImGui::CategorySeparator();

			Templates::Menus::Debug::Sub_Objects();
			
			ImGui::CategorySeparator();

			if (Features::Debug::wasProjectNameObtained)
				ImGui::Text("Project Name: %s", Features::Debug::projectName.c_str());

			if (Features::Debug::wasProjectPlatformObtained)
				ImGui::Text("Project Platform: %s", Features::Debug::projectPlatform.c_str());

			if (Features::Debug::wasUsernameObtained)
				ImGui::Text("Username: %s", Features::Debug::username.c_str());

			if (Features::Debug::wasCommandLineObtained)
			{
				ImGui::ReadOnlyInputText("Command Line:", Features::Debug::commandLine.c_str(), true);
			}

			ImGui::MenuSpacer();
		}

		ImGui::EndMenu();
	}
}




void Templates::Menus::World::Draw()
{
	SDK::UWorld* world = SDK::UWorld::GetWorld();
	SDK::ULevel* persistentLevel = world ? world->PersistentLevel : nullptr;
	SDK::AWorldSettings* worldSettings = persistentLevel ? persistentLevel->WorldSettings : nullptr;

	bool worldObtained = world && persistentLevel && worldSettings;
	ImGui::BeginDisabled(worldObtained == false);
	if (ImGui::BeginMenu("World"))
	{
		if (worldObtained)
		{
#ifdef SOFT_PATH
			ImGui::SetFontTitle();
			ImGui::Text("Level Instance");
			Templates::Descriptions::SoftPath::Draw("Level", "/Game/OpenWorld/Tile_X2Y8");

			if (ImGui::TreeNode("Details##LoadLevelInstance"))
			{
				ImGui::Text("Level Path:    ");
				ImGui::SameLine();
				ImGui::InputText("##LoadLevelInstance", Features::LoadLevelInstance::levelPathBuffer, Features::LoadLevelInstance::levelPathBufferSize);

				ImGui::Text("Level Location:");
				ImGui::SameLine();
				ImGui::InputFloat3("##LevelLocationOffset", Features::LoadLevelInstance::locationOffset);

				ImGui::Text("Level Rotation:");
				ImGui::SameLine();
				ImGui::InputFloat3("##LevelRotationOffset", Features::LoadLevelInstance::rotationOffset);

				if (ImGui::Button("Load Level##LoadLevelInstance"))
				{
					std::vector<std::wstring> levelPathCollection = Utilities::String::Split(Features::LoadLevelInstance::levelPathBuffer, L'|');
					if (levelPathCollection.size() > 0)
					{
						bool anyLevelLoaded = false;
						SDK::FVector locationOffset = SDK::FVector(Features::LoadLevelInstance::locationOffset[0], Features::LoadLevelInstance::locationOffset[1], Features::LoadLevelInstance::locationOffset[2]);
						SDK::FRotator rotationOffset = SDK::FRotator(Features::LoadLevelInstance::rotationOffset[0], Features::LoadLevelInstance::rotationOffset[1], Features::LoadLevelInstance::rotationOffset[2]);

						for (std::wstring levelPath : levelPathCollection)
						{
							std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(levelPath);
							if (Unreal::LevelStreaming::LoadLevelInstance(normalizedPath, locationOffset, rotationOffset))
								anyLevelLoaded = true;
						}

						GUI::PlayActionSound(anyLevelLoaded);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();
#ifdef LEVEL_SEQUENCE

			ImGui::SetFontTitle();
			ImGui::Text("Level Sequence");
			ImGui::SetFontSmall();
			ImGui::Text("Dynamic level sequence playing by soft path, for example \"/Game/OpenWorld/Sequences/LS_TowerExplosion.LS_TowerExplosion\".");
			ImGui::Text("Feature supports combined input using the '|' separator between paths.");
			ImGui::SetFontRegular();

			if (ImGui::TreeNode("Details##PlayLevelSequence"))
			{
				ImGui::Text("Level Sequence Path:");
				ImGui::SameLine();
				ImGui::InputText("##PlayLevelSequence", Features::PlayLevelSequence::levelSequencePathBuffer, Features::PlayLevelSequence::levelSequencePathBufferSize);

				ImGui::Text("Start Time:         ");
				ImGui::SameLine();
				ImGui::InputFloat("##LevelSequenceStartTime", &Features::PlayLevelSequence::startTime, 0.1f, 1.0f);

				ImGui::Text("Play Rate:          ");
				ImGui::SameLine();
				ImGui::InputFloat("##LevelSequencePlayRate", &Features::PlayLevelSequence::playRate, 0.1f, 1.0f);

				ImGui::Text("Loop Count:         ");
				ImGui::SameLine();
				ImGui::InputInt("##LevelSequenceLoopCount", &Features::PlayLevelSequence::loopCount, 1, 10);

				if (ImGui::Button("Create Level Sequence##PlayLevelSequence"))
				{
					std::vector<std::wstring> levelSequencePathCollection = Utilities::String::Split(Features::PlayLevelSequence::levelSequencePathBuffer, L'|');
					if (levelSequencePathCollection.size() > 0)
					{
						bool anySequenceCreated = false;

						for (std::wstring levelSequencePath : levelSequencePathCollection)
						{
							std::wstring normalizedPath = Utilities::String::NormalizeObjectPath(levelSequencePath);
							if (Unreal::Level::CreateLevelSequence(normalizedPath, Features::PlayLevelSequence::startTime, Features::PlayLevelSequence::playRate, Features::PlayLevelSequence::loopCount))
								anySequenceCreated = true;
						}

						GUI::PlayActionSound(anySequenceCreated);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::TreePop();
			}
#endif
			ImGui::NewLine();
#endif

			ImGui::SetFontTitle();
			ImGui::Text("Gravity");
			ImGui::SetFontRegular();
			if (ImGui::TreeNode("Details##WorldGravity"))
			{
				bool globalGravitySet = worldSettings->bGlobalGravitySet == 1;
				ImGui::Checkbox("Global Gravity Set", &globalGravitySet);
				worldSettings->bGlobalGravitySet = globalGravitySet ? 1 : 0;

				ImGui::BeginDisabled(globalGravitySet == false);
				ImGui::InputFloat("Global Gravity", &worldSettings->GlobalGravityZ, 0.1f, 1.0f);
				ImGui::EndDisabled();

				bool worldGravitySet = worldSettings->bWorldGravitySet == 1;
				ImGui::Checkbox("World Gravity Set", &worldGravitySet);
				worldSettings->bWorldGravitySet = worldGravitySet ? 1 : 0;

				ImGui::BeginDisabled(worldGravitySet == false);
				ImGui::InputFloat("World Gravity", &worldSettings->WorldGravityZ, 0.1f, 1.0f);
				ImGui::EndDisabled();

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			ImGui::SetFontTitle();
			ImGui::Text("Time");
			ImGui::SetFontRegular();
			if (ImGui::TreeNode("Details##WorldTime"))
			{
				if (ImGui::Button("Game Pause"))
				{
					GUI::PlayActionSound(SDK::UGameplayStatics::SetGamePaused(world, true));
				}
				ImGui::SameLine();
				if (ImGui::Button("Game Unpause"))
				{
					GUI::PlayActionSound(SDK::UGameplayStatics::SetGamePaused(world, false));
				}

				ImGui::NewLine();

				ImGui::InputFloat("Minimum Time Dilation", &worldSettings->MinGlobalTimeDilation, 0.1f, 1.0f);
				ImGui::InputFloat("Maximum Time Dilation", &worldSettings->MaxGlobalTimeDilation, 0.1f, 1.0f);
				double timeDilation = worldSettings->TimeDilation;
				ImGui::InputDouble("Time Dilation", &timeDilation, 0.1, 1.0);
				worldSettings->TimeDilation = std::clamp(timeDilation, (double)worldSettings->MinGlobalTimeDilation, (double)worldSettings->MaxGlobalTimeDilation);

				ImGui::NewLine();

				ImGui::InputFloat("Demo Time Dilation", &worldSettings->DemoPlayTimeDilation, 0.1f, 1.0f);

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			bool enableAISystem = worldSettings->bEnableAISystem == 1;
			ImGui::Checkbox("Enable AI System", &enableAISystem);
			worldSettings->bEnableAISystem = enableAISystem ? 1 : 0;

			bool enableNavigationSystem = worldSettings->bEnableNavigationSystem == 1;
			ImGui::Checkbox("Enable Navigation System", &enableNavigationSystem);
			worldSettings->bEnableNavigationSystem = enableNavigationSystem ? 1 : 0;

			ImGui::NewLine();

			ImGui::InputFloat("Kill Volume Z", &worldSettings->KillZ, 0.1f, 1.0f);
		}
		else
		{
			if (world == nullptr)
				ImGui::Text("World Doesn't Exist!");
			else if (persistentLevel == nullptr)
				ImGui::Text("Persistent Level Doesn't Exist!");
			else if (worldSettings == nullptr)
				ImGui::Text("World Settings Doesn't Exist!");
			else
				ImGui::Text("Something Went Wrong.");
		}

		ImGui::MenuSpacer();

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}




void Templates::Menus::Character::Draw()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	SDK::ACharacter* character = playerController ? playerController->Character : nullptr;
	SDK::UCharacterMovementComponent* movementComponent = (character && character->CharacterMovement) ? character->CharacterMovement : nullptr;

	bool characterObtained = playerController && character && movementComponent;
	ImGui::BeginDisabled(characterObtained == false);
	if (ImGui::BeginMenu("Character"))
	{
		if (characterObtained)
		{
			ImGui::Text("Character: %s", character->GetFullName().c_str());
			Unreal::Transform characterTransform = Unreal::Actor::GetTransform(character);
			ImGui::TextVectorColored("Location:", characterTransform.location);
			static float customLocation[3];
			if (ImGui::Button("Copy##Location"))
			{
				customLocation[0] = characterTransform.location.X;
				customLocation[1] = characterTransform.location.X;
				customLocation[2] = characterTransform.location.Z;
				GUI::PlayActionSound(true);
			}
			ImGui::SameLine();
			ImGui::InputFloat3("##Location", customLocation);
			ImGui::SameLine();
			if (ImGui::Button("Set##Location"))
			{
				if (character)
				{
					bool isSuccess = Unreal::Actor::TeleportTo(character, SDK::FVector(customLocation[0], customLocation[1], customLocation[2]), characterTransform.rotation);
					GUI::PlayActionSound(isSuccess);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::TextRotatorColored("Rotation:", characterTransform.rotation);
			static float customRotation[3];
			if (ImGui::Button("Copy##Rotation"))
			{
				customRotation[0] = characterTransform.rotation.Pitch;
				customRotation[1] = characterTransform.rotation.Yaw;
				customRotation[2] = characterTransform.rotation.Roll;
				GUI::PlayActionSound(true);
			}
			ImGui::SameLine();
			ImGui::InputFloat3("##Rotation", customRotation);
			ImGui::SameLine();
			if (ImGui::Button("Set##Rotation"))
			{
				if (character)
				{
					bool isSuccess = Unreal::Actor::TeleportTo(character, characterTransform.location, SDK::FRotator(customRotation[0], customRotation[1], customRotation[2]));
					GUI::PlayActionSound(isSuccess);
				}
				else
					GUI::PlayActionSound(false);
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::Text("Positions");
			ImGui::SetFontRegular();
			if (ImGui::TreeNode("Details##Positions"))
			{
				if (ImGui::Button("Reload"))
				{
					Features::Positions::Load();
					GUI::GUI::PlayActionSound(true);
				}

				static int selectedPositionIndex = -1;

				if (ImGui::BeginTable("PositionsLayout", 2, ImGuiTableFlags_SizingFixedFit))
				{
					ImGui::TableSetupColumn("PositionsLeftSide", ImGuiTableColumnFlags_WidthFixed, 400.0f);
					ImGui::TableSetupColumn("PositionsRightSide", ImGuiTableColumnFlags_WidthFixed);

					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);

					/* LEFT SIDE - Table. */
					ImGui::Text("Stored Positions:");
					if (ImGui::BeginChild("PositionsList", ImVec2(0, 600), true, ImGuiWindowFlags_HorizontalScrollbar))
					{
						/* 2 columns: ID, Title */
						if (ImGui::BeginTable("PositionsTable", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit))
						{
							ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 30.0f);
							ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthStretch);
							ImGui::TableHeadersRow();

							for (size_t i = 0; i < Features::Positions::entries.size(); i++)
							{
								ImGui::TableNextRow();

								// ID + Selectable
								ImGui::TableSetColumnIndex(0);

								char positionIdLabel[Features::Positions::newEntryTitleBufferSize];
								sprintf_s(positionIdLabel, "%d", (int)i);

								/* Make line highlighted by clicking on ID. */
								if (ImGui::Selectable(positionIdLabel, selectedPositionIndex == i, ImGuiSelectableFlags_SpanAllColumns))
								{
									selectedPositionIndex = (int)i;
								}

								/* Title */
								ImGui::TableSetColumnIndex(1);
								ImGui::TextUnformatted(Features::Positions::entries[i].title.c_str());
							}

							ImGui::EndTable();
						}
					}
					ImGui::EndChild();

					ImGui::TableSetColumnIndex(1);

					/* RIGHT SIDE - Buttons. */
					ImGui::Text("Actions:");

					bool isPositionsListFull = Features::Positions::entries.size() >= Features::Positions::entriesLimit;
					ImGui::BeginDisabled(isPositionsListFull);
					ImGui::InputTextWithHint("##PositionTitle", "Position Title", Features::Positions::newEntryTitleBuffer, Features::Positions::newEntryTitleBufferSize);

					if (ImGui::Button("Store Current Position"))
					{
						if (isPositionsListFull == false)
						{
							Features::Positions::PositionEntry newPositionEntry;
							newPositionEntry.title = Utilities::String::ToString(Features::Positions::newEntryTitleBuffer);
							newPositionEntry.location = characterTransform.location;
							newPositionEntry.rotation = characterTransform.rotation;
							Features::Positions::entries.push_back(newPositionEntry);

							Features::Positions::Save();
							GUI::PlayActionSound(true);
						}
						else
							GUI::PlayActionSound(false);
					}
					ImGui::EndDisabled();

					ImGui::NewLine();

					bool isPositionEntrySelected = (selectedPositionIndex >= 0) && (selectedPositionIndex < Features::Positions::entries.size());
					if (isPositionEntrySelected)
					{
						ImGui::TextVectorColored("Location:", Features::Positions::entries[selectedPositionIndex].location);
						ImGui::TextRotatorColored("Rotation:", Features::Positions::entries[selectedPositionIndex].rotation);
						if (ImGui::Button("Teleport To Selected"))
						{
							if (selectedPositionIndex >= 0 && selectedPositionIndex < Features::Positions::entries.size())
							{
								bool isSuccess = Unreal::Actor::TeleportTo(character, Features::Positions::entries[selectedPositionIndex].location, Features::Positions::entries[selectedPositionIndex].rotation);
								GUI::PlayActionSound(isSuccess);
							}
							else
								GUI::PlayActionSound(false);
						}
						ImGui::SameLine();
						if (ImGui::Button("Remove Selected"))
						{
							if (selectedPositionIndex >= 0 && selectedPositionIndex < Features::Positions::entries.size())
							{
								Features::Positions::entries.erase(Features::Positions::entries.begin() + selectedPositionIndex);
								selectedPositionIndex = -1;

								Features::Positions::Save();
								GUI::PlayActionSound(true);
							}
							else
								GUI::PlayActionSound(false);
						}
					}

					ImGui::EndTable();
				}

				ImGui::TreePop();
			}

			ImGui::NewLine();

			ImGui::SetFontTitle();
			ImGui::Text("Movement");
			ImGui::SetFontRegular();
			if (ImGui::TreeNode("Details##CharacterMovement"))
			{
				if (movementComponent->bCheatFlying)
					ImGui::Text("Character Is In %s Mode", character->bActorEnableCollision ? "Fly" : "Ghost");
				else
				{
					SDK::EMovementMode movementMode = movementComponent->MovementMode;
					switch (movementMode)
					{
					case SDK::EMovementMode::MOVE_Walking:
						ImGui::Text("Character Is Walking");
						break;

					case SDK::EMovementMode::MOVE_NavWalking:
						ImGui::Text("Character Is Nav Walking");
						break;

					case SDK::EMovementMode::MOVE_Falling:
						ImGui::Text("Character Is Falling");
						break;

					case SDK::EMovementMode::MOVE_Swimming:
						ImGui::Text("Character Is Swimming");
						break;

					case SDK::EMovementMode::MOVE_Flying:
						ImGui::Text("Character Is Flying");
						break;

					default:
						ImGui::Text("Character Is In %d Mode", movementMode);
						break;
					}
				}
				ImGui::Text("Custom Movement Mode: %d", movementComponent->CustomMovementMode);

				ImGui::NewLine();

				/* 0 corresponds for default vertical size. */
				static const ImVec2 buttonSize = { 128.0f, 0.0f };

				if (ImGui::Button("Ghost", buttonSize))
				{
					Features::CharacterMovement::Ghost();
				}
				ImGui::SameLine();
				if (ImGui::Button("Fly", buttonSize))
				{
					Features::CharacterMovement::Fly();
				}
				ImGui::SameLine();
				if (ImGui::Button("Walk", buttonSize))
				{
					Features::CharacterMovement::Walk();
				}

				ImGui::NewLine();

				ImGui::KeyBindingInput("Ghost Key Binding:##Ghost", &Inputs::Keybindings::characterMovement_Ghost);
				ImGui::KeyBindingInput("Fly Key Binding:  ##Fly", &Inputs::Keybindings::characterMovement_Fly);
				ImGui::KeyBindingInput("Walk Key Binding: ##Walk", &Inputs::Keybindings::characterMovement_Walk);

				ImGui::NewLine();

				if (ImGui::Button("Enable Input"))
				{
					if (character)
					{
						character->EnableInput(playerController);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Disable Input"))
				{
					if (character)
					{
						character->DisableInput(playerController);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				if (ImGui::Button("Ignore Move Input"))
				{
					if (playerController)
					{
						playerController->SetIgnoreMoveInput(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Do Not Ignore Move Input"))
				{
					if (playerController)
					{
						playerController->SetIgnoreMoveInput(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				if (ImGui::Button("Ignore Look Input"))
				{
					if (playerController)
					{
						playerController->SetIgnoreLookInput(true);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}
				ImGui::SameLine();
				if (ImGui::Button("Do Not Ignore Look Input"))
				{
					if (playerController)
					{
						playerController->SetIgnoreLookInput(false);
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				if (ImGui::Button("Input Mode: Game Only"))
				{
					if (playerController)
					{
#ifdef UE5
						SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController, true);
#else
						SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
#endif
						GUI::PlayActionSound(true);
					}
					else
						GUI::PlayActionSound(false);
				}

				ImGui::NewLine();

				ImGui::SetFontTitle();
				ImGui::Text("Directional Movement");
				ImGui::SetFontSmall();
				ImGui::Text("When the character is Flying or in Ghost mode, moving forward teleports them in the direction the camera is facing,");
				ImGui::Text("allowing for quick and easy navigation through the world.");
				ImGui::SetFontRegular();
				if (ImGui::TreeNode("Settings##DirectionalMovement"))
				{
					if (ImGui::Checkbox("Enabled##DirectionalMovement", &Features::DirectionalMovement::enabled))
					{
						if (Features::DirectionalMovement::enabled)
							Features::DirectionalMovement::Enable();
						else Features::DirectionalMovement::Disable();

						Features::Config::Save();
					}
					if (ImGui::Checkbox("Omni-Movement##DirectionalMovement", &Features::DirectionalMovement::omniMovement))
					{
						Features::Config::Save();
					}
					ImGui::SameLine();
					ImGui::TextHint("Allows movement in all directions (Backward, Left, Right, Up & Down).");
					ImGui::BeginDisabled(Features::DirectionalMovement::omniMovement == false);
					ImGui::KeyBindingInput("Move Up  ", &Inputs::Keybindings::characterOmniMovement_Up);
					ImGui::KeyBindingInput("Move Down", &Inputs::Keybindings::characterOmniMovement_Down);
					ImGui::EndDisabled();

					ImGui::NewLine();

					if (ImGui::InputFloat("Movement Step##DirectionalMovement", &Features::DirectionalMovement::step, 0.1, 1.0))
					{
						Features::Config::Save();
					}
					if (ImGui::InputFloat("Movement Delay##DirectionalMovement", &Features::DirectionalMovement::delay, 0.01, 0.1))
					{
						if (Features::DirectionalMovement::delay < 0.001)
							Features::DirectionalMovement::delay = 0.001;

						Features::Config::Save();
					}

					ImGui::TreePop();
				}

				ImGui::CategorySeparator();

				ImGui::InputFloat("Gravity Scale", &movementComponent->GravityScale, 0.1f, 1.0f);

				ImGui::NewLine();

				ImGui::InputFloat("Max Acceleration", &movementComponent->MaxAcceleration, 1.0f, 10.0f);
				ImGui::InputFloat("Max Step Height", &movementComponent->MaxStepHeight, 1.0f, 10.0f);
				ImGui::InputFloat("Weight", &movementComponent->Mass, 1.0f, 10.0f);

				ImGui::NewLine();

				ImGui::InputFloat("Max Walk Speed", &movementComponent->MaxWalkSpeed, 1.0f, 10.0f);
				ImGui::InputFloat("Max Crouch Speed", &movementComponent->MaxWalkSpeedCrouched, 1.0f, 10.0f);
				ImGui::InputFloat("Max Swim Speed", &movementComponent->MaxSwimSpeed, 1.0f, 10.0f);
				ImGui::InputFloat("Max Fly Speed", &movementComponent->MaxFlySpeed, 1.0f, 10.0f);
				ImGui::InputFloat("Max Custom Movement Speed", &movementComponent->MaxCustomMovementSpeed, 1.0f, 10.0f);

				ImGui::NewLine();

				ImGui::TextFloatColored("Walkable Floor Z:", movementComponent->WalkableFloorZ);

				ImGui::CategorySeparator();

				if (ImGui::Button("Jump"))
				{
					Features::CharacterMovement::Jump();
				}
				ImGui::InputInt("Jump Limit", &character->JumpMaxCount, 1, 1);
				ImGui::InputFloat("Jump Height", &movementComponent->JumpZVelocity, 0.1f, 1.0f);
				ImGui::KeyBindingInput("Jump Key Binding:##Jump", &Inputs::Keybindings::characterMovement_Jump);

				ImGui::NewLine();

				if (ImGui::Button("Launch"))
				{
					Features::CharacterMovement::Launch();
				}
				ImGui::InputFloat3("Launch Velocity", Features::CharacterMovement::launchVelocity);
				ImGui::KeyBindingInput("Launch Key Binding:##Launch", &Inputs::Keybindings::characterMovement_Launch);

				ImGui::NewLine();

				if (ImGui::Button("Dash"))
				{
					Features::CharacterMovement::Dash();
				}
				ImGui::InputDouble("Dash Strength", &Features::CharacterMovement::dashStrength, 0.1f, 1.0f);
				ImGui::KeyBindingInput("Dash Key Binding:##Dash", &Inputs::Keybindings::characterMovement_Dash);

				ImGui::TreePop();
			}

			ImGui::CategorySeparator();

			SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
			ImGui::SetFontTitle();
			ImGui::Text("Camera");
			ImGui::SetFontRegular();
			ImGui::BeginDisabled(cameraManager == nullptr);
			if (ImGui::TreeNode("Details##Camera"))
			{
				if (cameraManager)
				{
					/* 0 corresponds for default vertical size. */
					static const ImVec2 buttonSize = { 204.0f, 0.0f };

					if (ImGui::Button("Start Fade", buttonSize))
					{
						Features::Camera::StartFade();
					}
					ImGui::SameLine();
					if (ImGui::Button("Stop Fade", buttonSize))
					{
						Features::Camera::StopFade();
					}

					if (ImGui::InputFloat("Fade From Alpha", &Features::Camera::fadeFromAlpha, 0.01f, 0.1f))
					{
						if (Features::Camera::fadeFromAlpha < 0.0f)
							Features::Camera::fadeFromAlpha = 0.0f;

						if (Features::Camera::fadeFromAlpha > 1.0f)
							Features::Camera::fadeFromAlpha = 1.0f;
					}

					if (ImGui::InputFloat("Fade To Alpha", &Features::Camera::fadeToAlpha, 0.01f, 0.1f))
					{
						if (Features::Camera::fadeToAlpha < 0.0f)
							Features::Camera::fadeToAlpha = 0.0f;

						if (Features::Camera::fadeToAlpha > 1.0f)
							Features::Camera::fadeToAlpha = 1.0f;
					}

					ImGui::InputFloat("Fade Duration", &Features::Camera::fadeDuration, 0.1f, 1.0f);
					ImGui::ColorPicker4("Fade Color", Features::Camera::fadeColor);

					ImGui::NewLine();

					ImGui::Checkbox("Fade Audio", &Features::Camera::fadeAudio);
					ImGui::Checkbox("Fade Persistent", &Features::Camera::fadePersistent);

					ImGui::NewLine();

					ImGui::KeyBindingInput("Start Fade Key Binding:", &Inputs::Keybindings::characterCamera_StartFade);
					ImGui::KeyBindingInput("Stop Fade Key Binding:", &Inputs::Keybindings::characterCamera_StopFade);
				}
				else
					ImGui::Text("Camera Manager Doesn't Exist!");

				ImGui::TreePop();
			}
			ImGui::EndDisabled();

			ImGui::MenuSpacer();
		}
		else
		{
			if (playerController == nullptr)
				ImGui::Text("Player Controller Doesn't Exist!");
			else if (character == nullptr)
				ImGui::Text("Character Doesn't Exist!");
			else if (movementComponent == nullptr)
				ImGui::Text("Movement Component Doesn't Exist!");
			else
				ImGui::Text("Something Went Wrong.");
		}

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}




#ifdef FREE_CAMERA
void Templates::Menus::FreeCamera::Draw()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	ImGui::BeginDisabled(playerController == nullptr);
	if (ImGui::BeginMenu("FreeCamera"))
	{
		if (playerController)
		{
			ImGui::PushID("##FreeCamera");

			if (ImGui::Button("Toggle"))
			{
				Features::FreeCamera::Toggle();
			}
			ImGui::KeyBindingInput("Toggle:       ", &Inputs::Keybindings::freeCamera_Toggle);

			ImGui::NewLine();

			ImGui::Text("Movement Step:");
			ImGui::SameLine();
			if (ImGui::InputFloat("##MovementStep", &Features::FreeCamera::cameraMovementStep, 0.1f, 1.0f))
			{
				Features::Config::Save();
			}
			ImGui::KeyBindingInput("Move Forward: ", &Inputs::Keybindings::freeCamera_MoveForward);
			ImGui::KeyBindingInput("Move Backward:", &Inputs::Keybindings::freeCamera_MoveBackward);
			ImGui::KeyBindingInput("Move Left:    ", &Inputs::Keybindings::freeCamera_MoveLeft);
			ImGui::KeyBindingInput("Move Right:   ", &Inputs::Keybindings::freeCamera_MoveRight);
			ImGui::KeyBindingInput("Move Up:      ", &Inputs::Keybindings::freeCamera_MoveUp);
			ImGui::KeyBindingInput("Move Down:    ", &Inputs::Keybindings::freeCamera_MoveDown);

			ImGui::NewLine();

			ImGui::Text("Rotation Step:");
			ImGui::SameLine();
			if (ImGui::InputFloat("##RotationStep", &Features::FreeCamera::cameraRotationStep, 0.1f, 1.0f))
			{
				Features::Config::Save();
			}
			ImGui::KeyBindingInput("Rotate Up:    ", &Inputs::Keybindings::freeCamera_RotateUp);
			ImGui::KeyBindingInput("Rotate Down:  ", &Inputs::Keybindings::freeCamera_RotateDown);
			ImGui::KeyBindingInput("Rotate Left:  ", &Inputs::Keybindings::freeCamera_RotateLeft);
			ImGui::KeyBindingInput("Rotate Right: ", &Inputs::Keybindings::freeCamera_RotateRight);

			ImGui::NewLine();

			ImGui::KeyBindingInput("Teleport Camera To Player:", &Inputs::Keybindings::freeCamera_TeleportCameraToPlayer);
			ImGui::KeyBindingInput("Teleport Player To Camera:", &Inputs::Keybindings::freeCamera_TeleportPlayerToCamera);

			ImGui::PopID();
			ImGui::MenuSpacer();
		}
		else
			ImGui::Text("Player Controller Doesn't Exist!");

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}
#endif