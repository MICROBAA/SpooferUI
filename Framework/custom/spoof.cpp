#include "colors.hpp"

namespace spof {
	_V4 ibg = RGBA(14, 14, 14, 255);
	_V4 border = RGBA(21, 21, 21, 255);
}

bool Items::SpoofItem(const std::string& label, const std::string& desc, const _V2& pos_arg) {
	using namespace spof;
	_V2 size(_(620), _(175));
	Draw::Rect(pos_arg, size, ibg, _(7));
	Draw::Rect(pos_arg, size, border, _(7), NoFill);
	PushFont(f.PoppinsMedium[0]);
	Misc::MultiColoredText(label, pos_arg + _V2(_(20), _(20)));
	PopFont();
	Misc::Text(desc, pos_arg + _V2(_(20), _(55)), colors::LWhite);

	bool result = Items::Button(label, pos_arg + _V2((size.x - _(590)) / 2, _(120)), _V2(_(590), _(37)));
	return result;
}