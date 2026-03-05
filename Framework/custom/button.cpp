#include "colors.hpp"

namespace buttoncol {
	_V4 bg = RGBA(29, 29, 29, 255);
	_V4 bgAct = colors::Thrid;

	_V4 textC = RGBA(185, 185, 185, 255);
	_V4 textAct = colors::White;
}

struct SButton {
	_V4 bg, text;
	float time = 0.2;
};

bool Items::Button(const std::string& label, const _V2& pos_arg, const _V2& size) {
	using namespace buttoncol;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(label.c_str()));

	SetCursorPos(pos_arg);
	_V2 pos(window->DC.CursorPos);

	bool r = InvisibleButton(label.c_str(), size);
	bool act(IsItemActive());

	_V4 bgcol = act ? bgAct : bg;
	_V4 textcol = act ? textAct : textC;

	static std::map<ImGuiID, SButton> anim;
	SButton& w = anim.emplace(id, SButton(bgcol, textcol)).first->second;

	w.bg = ImLerp(w.bg, bgcol, w.time);
	w.text = ImLerp(w.text, textcol, w.time);

	Draw::Rect(pos_arg, size, w.bg, 5);
	Misc::Text(label, pos_arg + (size - _C(label.c_str())) / 2, w.text);

	return r;
}	