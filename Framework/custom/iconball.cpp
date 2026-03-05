#include "colors.hpp"

namespace ball {
	_V4 textC = RGBA(190, 190, 190, 255);
	_V4 textAct = colors::White;
}

struct SButton {
	_V4 text;
	float time = 0.2;
};

bool Items::Ball(const std::string& icon, const _V2& pos_arg) {
	using namespace ball;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(icon.c_str()));

	if (pos_arg.x != 0) SetCursorPosX(pos_arg.x);
	if (pos_arg.y != 0) SetCursorPosY(pos_arg.y);

	_V2 pos(window->DC.CursorPos);
	_V2 size(_(48), _(48));

	bool r = InvisibleButton(icon.c_str(), size);
	bool hov(IsItemHovered());

	_V4 textcol = hov ? textAct : textC;

	static std::map<ImGuiID, SButton> anim;
	SButton& w = anim.emplace(id, SButton(textcol)).first->second;

	w.text = ImLerp(w.text, textcol, w.time);

	const int vtx_size = window->DrawList->VtxBuffer.Size;
	Draw::Circle(pos_arg + size / 2, _(20), colors::Main, 0);
	ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vtx_size, window->DrawList->VtxBuffer.Size, pos, pos + size, _CO(colors::Second),
		_CO(colors::Main));
	
	PushFont(f.icons);
	Misc::Text(icon, pos_arg + (size - _C(icon.c_str())) / 2, w.text);
	PopFont();

	return r;
}