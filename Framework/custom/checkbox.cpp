#include "colors.hpp"

namespace cbox {
	_V4 bg = RGBA(23, 23, 23, 255);
	_V4 bgAct = colors::Thrid;

	_V4 textC = colors::LWhite;
	_V4 textAct = RGBA(230, 230, 230, 255);

	_V4 circle = RGBA(156, 156, 156, 255);
	_V4 circleAct = RGBA(230, 230, 230, 255);
}

struct SCheckbox {
	_V4 bg, text, circle;
	float x, time = 0.2;
};

bool Items::Checkbox(const std::string& label, const _V2& pos_arg, bool* v, float x) {
	using namespace cbox;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(label.c_str()));

	SetCursorPos(pos_arg);
	_V2 pos(window->DC.CursorPos);
	_V2 labelsize(_C(label.c_str()));
	_V2 csize(_(29), _(19));
	_V2 tsize(x, csize.y);

	bool r = InvisibleButton(label.c_str(), tsize);
	bool act(*v);

	if (r) *v = !*v;

	_V4 bgcol = act ? bgAct : bg;
	_V4 textcol = act ? textAct : textC;
	_V4 circlecol = act ? circleAct : circle;
	float circleX = *v ? (tsize.x - _(9)) : (tsize.x - csize.x + _(9));

	static std::map<ImGuiID, SCheckbox> anim;
	SCheckbox& w = anim.emplace(id, SCheckbox(bgcol, textcol, circlecol, circleX)).first->second;

	w.bg = ImLerp(w.bg, bgcol, w.time);
	w.circle = ImLerp(w.circle, circlecol, w.time);
	w.text = ImLerp(w.text, textcol, w.time);
	w.x = ImLerp(w.x, circleX, w.time);

	Misc::Text(label, pos_arg + _V2(0, (tsize.y - labelsize.y) / 2), w.text);
	Draw::Rect(pos_arg + _V2(tsize.x - csize.x, 0), csize, w.bg, 1000);
	Draw::Circle(pos_arg + _V2(w.x, tsize.y / 2), _(6), w.circle, 0);

	return r;
}

namespace cbox2 {
	_V4 bg = RGBA(23, 23, 23, 255);
	_V4 bgAct = colors::Thrid;

	_V4 ibg = RGBA(14, 14, 14, 255);
	_V4 border = RGBA(21, 21, 21, 255);

	_V4 textC = colors::LWhite;
	_V4 textAct = RGBA(230, 230, 230, 255);

	_V4 circle = RGBA(156, 156, 156, 255);
	_V4 circleAct = RGBA(230, 230, 230, 255);
}

struct SCheckbox2 {
	_V4 bg, text, circle;
	float x, time = 0.2;
};

bool Items::Checkbox2(const std::string& label, const std::string& desc, const _V2& pos_arg, bool* v) {
	using namespace cbox2;
	ImGuiWindow* window = GetCurrentWindow();
	ImGuiID id(window->GetID(label.c_str()));

	SetCursorPos(pos_arg);
	_V2 pos(window->DC.CursorPos);
	_V2 labelsize(_C(label.c_str()));
	_V2 csize(_(29), _(19));
	_V2 tsize(_(305), _(120));

	bool r = InvisibleButton(label.c_str(), tsize);
	bool act(*v);

	if (r) *v = !*v;

	_V4 bgcol = act ? bgAct : bg;
	_V4 textcol = act ? textAct : textC;
	_V4 circlecol = act ? circleAct : circle;
	float circleX = *v ? (tsize.x - _(29)) : (tsize.x - csize.x + _(-11));

	static std::map<ImGuiID, SCheckbox2> anim;
	SCheckbox2& w = anim.emplace(id, SCheckbox2(bgcol, textcol, circlecol, circleX)).first->second;

	w.bg = ImLerp(w.bg, bgcol, w.time);
	w.circle = ImLerp(w.circle, circlecol, w.time);
	w.x = ImLerp(w.x, circleX, w.time);
	w.text = ImLerp(w.text, textcol, w.time);

	Draw::Rect(pos_arg, tsize, ibg, _(7));
	Draw::Rect(pos_arg, tsize, border, _(7), NoFill);
	PushFont(f.PoppinsMedium[0]);
	Misc::MultiColoredText(label, pos_arg + _V2(_(20), _(15)));
	PopFont();
	Misc::Text(desc, pos_arg + _V2(_(20), _(50)), w.text);
	Draw::Rect(pos_arg + _V2(tsize.x - csize.x - _(20), _(15)), csize, w.bg, 1000);
	Draw::Circle(pos_arg + _V2(w.x, (csize.y + _(30)) / 2), _(6), w.circle, 0);

	return r;
}