#include "colors.hpp"

namespace tabcol {
	_V4 line = colors::Transparent;
	_V4 lineAct = colors::Main;

	_V4 textC = colors::LWhite3;
	_V4 textAct = colors::Main;
}

struct STab {
	_V4 line, text;
	float lx, time = 0.1;
};

bool Items::Tab(const std::string& label, const _V2& pos_arg, bool cond) {
	using namespace tabcol;
	ImGuiWindow* window = GetCurrentWindow();

	if (pos_arg.x != 0) SetCursorPosX(pos_arg.x);
	if (pos_arg.y != 0) SetCursorPosY(pos_arg.y);

	ImGuiID id(window->GetID(label.c_str()));
	_V2 pos(window->DC.CursorPos);
	_V2 size(_C(label.c_str()));

	bool r = InvisibleButton(label.c_str(), size);
	bool act(cond);

	_V4 linecol = act ? lineAct : line;
	_V4 textcol = act ? textAct : textC;
	float l = act ? size.x / 3 : 0;

	static std::map<ImGuiID, STab> anim;
	STab& w = anim.emplace(id, STab(linecol, textcol)).first->second;

	w.line = ImLerp(w.line, linecol, w.time);
	w.text = ImLerp(w.text, textcol, w.time);
	w.lx = ImLerp(w.lx, l, w.time);

	window->DrawList->AddText(pos, _CO(w.text), label.c_str());
	window->DrawList->AddLine(pos + _V2(0, size.y), pos + _V2(w.lx, size.y), _CO(w.line));

	return r;
}