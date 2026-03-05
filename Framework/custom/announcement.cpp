#include "colors.hpp"

void Items::Announcement(const std::string& title, const std::string& desc, const _V2& pos_arg) {
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(title.c_str()));

	SetCursorPos(pos_arg);
	_V2 pos(window->DC.CursorPos);
	_V2 size(_(645), _(100));

	_V4 bg = RGBA(14, 14, 14, 255);
	_V4 border = RGBA(21, 21, 21, 255);
	_V4 text = colors::LWhite2;

	ItemSize(size, id); ItemAdd({ pos, pos + size }, id);

	Draw::Rect(pos_arg, size, bg, _(7));
	Draw::Rect(pos_arg, size, border, _(7), NoFill);

	PushFont(f.PoppinsMedium[0]);
	Misc::MultiColoredText(title, pos_arg + _V2(_(20), _(12)));
	PopFont();

	PushFont(f.Poppins[0]);
	Misc::Text(desc, pos_arg + _V2(_(20), _(43)), text);
	PopFont();
}