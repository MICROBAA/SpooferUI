#include "colors.hpp"
#include <vector>

struct SNotif {
	std::string label;
	NotifType type;
	float alpha, timer, Ypos;
};

std::vector<SNotif> notifs;

void Items::CallNotif(const std::string& notif, NotifType type) {
	notifs.push_back({ notif, type });
}

void Items::RenderNotif() {
	ImGuiWindow* window = GetCurrentWindow();
	ImDrawList* foreground = GetForegroundDrawList();
	ImGuiIO& io = GetIO();

	int index = 1;

	for (auto it = notifs.begin(); it != notifs.end();)
	{
		_V4 green = { colors::green.x, colors::green.y, colors::green.z, it->alpha };
		_V4 red = { colors::red.x, colors::red.y, colors::red.z, it->alpha };
		_V4 orange = { colors::orange.x, colors::orange.y, colors::orange.z, it->alpha };
		_V4 _bg = RGBA(14, 14, 14, 255); _V4 bg = _V4(_bg.x, _bg.y, _bg.z, it->alpha);
		_V4 text = _V4(colors::LWhite.x, colors::LWhite.y, colors::LWhite.z, it->alpha);
		_V4 _border = RGBA(21, 21, 21, 255); _V4 border = _V4(_border.x, _border.y, _border.z, it->alpha);

		std::string LabelStatus = (it->type == info) ? "[INFO]" : (it->type == success) ? "[SUCCESS]" : "[ERROR]";
		_V4 Col = (it->type == info) ? orange : (it->type == success) ? green : red;

		PushFont(f.PoppinsMedium[3]);
		_V2 StatusSize(_C(LabelStatus.c_str()));
		PopFont();

		PushFont(f.Poppins[2]);
		_V2 LabelSize(_C(it->label.c_str()));
		PopFont();

		_V2 TotalSize(StatusSize.x + LabelSize.x + _(27), _(45));
		const _V2 pos(window->Size.x - TotalSize.x - _(15), window->Size.y - (index) * (TotalSize.y + _(15)));

		if (it->Ypos == 0) it->Ypos = (window->Size.y - 15 - TotalSize.y);
		it->Ypos = ImLerp(it->Ypos, pos.y, 0.15);

		float duration = 5;
		(it->timer > duration - 0.5) ? it->alpha = std::clamp(it->alpha - (2.f * io.DeltaTime), 0.0f, 1.0f) :
			it->alpha = std::clamp(it->alpha + (2.f * io.DeltaTime), 0.0f, 1.0f);

		it->timer += 0.01;

		_V2 fpos(pos.x, it->Ypos);

		foreground->AddRectFilled(fpos, fpos + TotalSize, _CO(bg), _(7));
		foreground->AddRect(fpos, fpos + TotalSize, _CO(border), _(7));
		PushFont(f.PoppinsMedium[3]);
		foreground->AddText(fpos + _V2(_(11), (TotalSize.y - StatusSize.y) / 2), _CO(Col), LabelStatus.c_str());
		PopFont();

		PushFont(f.Poppins[2]);
		foreground->AddText(fpos + _V2(_(11) + StatusSize.x + _(5), (TotalSize.y - LabelSize.y) / 2), _CO(text), it->label.c_str());
		PopFont();

		if (it->timer > duration) notifs.erase(it);
		else it++, index++;
	}
}