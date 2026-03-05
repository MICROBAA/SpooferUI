#include "colors.hpp"

namespace ibuttoncol {
	_V4 textC = colors::LWhite3;
	_V4 textHov = colors::LWhite2;
}

struct SIconButton {
	_V4 text;
	float time = 0.1;
};

bool Items::IconButton(const std::string& label, const _V2& pos_arg) {
	using namespace ibuttoncol;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(label.c_str()));

	SetCursorPos(pos_arg);
	PushFont(f.icons);
	_V2 pos(window->DC.CursorPos);
	_V2 size(_C(label.c_str()));

	bool r = InvisibleButton(label.c_str(), size);
	bool act(IsItemHovered());

	_V4 textcol = act ? textHov : textC;

	static std::map<ImGuiID, SIconButton> anim;
	SIconButton& w = anim.emplace(id, SIconButton(textcol)).first->second;

	w.text = ImLerp(w.text, textcol, w.time);

	Misc::Text(label, pos_arg + (size - _C(label.c_str())) / _(2), w.text);
	PopFont();
	return r;
}