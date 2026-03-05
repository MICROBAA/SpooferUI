#include "colors.hpp"

void Items::Serial(const std::string& label, const std::string& serial, const _V2& pos, SerialStatus status) {

	_V4 col = (status == null) ? colors::white : (status == changed) ? colors::green : colors::red;

	Misc::MultiColoredText(label, pos);
	Misc::Text(serial, pos + _V2(_C(label.c_str()).x, 0), col);
}