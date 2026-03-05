#include "colors.hpp"

namespace input {
	float rounding = 5.f;
	inline _V4 bg = RGBA(20, 20, 20, 255);
	inline _V4 TextC = colors::LWhite;
	inline _V4 TextAct = colors::White;

	inline _V4 IconAct = colors::Main;
	inline _V4 IconC = RGBA(58, 58, 58, 255);
}

struct SInput {
	_V4 textcol, iconcol;
	float time = 0.1;
};

bool Items::Input(const std::string& label, const std::string& icon, const _V2& pos_arg, char* buf, size_t buf_size, ImGuiInputTextFlags flags) {
	using namespace input;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(label.c_str()));

	SetCursorPos(pos_arg);
	_V2 pos(window->DC.CursorPos);
	_V2 _size(_(320), _(14));

	std::string L = "###" + label;

	PushStyleVar(ImGuiStyleVar_FramePadding, _V2(10, _size.y));
	PushStyleColor(ImGuiCol_FrameBg, colors::Transparent);
	PushStyleColor(ImGuiCol_Text, TextAct);

	_V2 size(_size.x, GetFrameHeight());
	Draw::Rect(pos_arg, size, bg, rounding);

	bool r = InputText(L.c_str(), buf, buf_size, flags);
	bool act(IsItemActive() || (strlen(buf) != 0));

	_V4 textcol = act ? colors::Transparent : TextC;
	_V4 iconcol = act ? IconAct : IconC;

	static std::map<ImGuiID, SInput> anim;
	SInput& w = anim.emplace(id, SInput(textcol, iconcol)).first->second;

	w.textcol = ImLerp(w.textcol, textcol, w.time);
	w.iconcol = ImLerp(w.iconcol, iconcol, w.time);

	Misc::Text(label, pos_arg + _V2(10, _size.y), w.textcol);
	
	PushFont(f.icons);
	_V2 iconsize(_C(icon.c_str()));
	Misc::Text(icon, pos_arg + _V2(size.x - iconsize.x - 10, (size.y - iconsize.y) / 2), w.iconcol);
	PopFont();

	PopStyleVar();
	PopStyleColor(2);

	return r;
}