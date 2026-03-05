// Want to change colors? Navigate to -> "./custom/colors"
#include "colors.hpp"
#include <thread>

void ui::BeforeLoop(ID3D11Device* dvc) {
	f.RenderFonts();
	EIMAGE(dvc, __Logo, Images::logo);
	EIMAGE(dvc, __Background, Images::bg);
	Misc::Blur(window::dx::hwnd);
}

char usrbuf[20];
char licbuf[20];
bool remember, tpm, tpm2, fspoof, ReadyToChange;
float _x = 15;
bool CheckBuf(char* buf) {
	return (strlen(buf) != 0);
}

void ui::Render() {
	static alpha_s a;

	Misc::Begin("Saturn Spoofer"); 
	{
		ImGuiWindow* window = GetCurrentWindow();

		window->DrawList->AddRectFilled(window->Pos + _V2(_x, _(15)), window->Pos + window->Size - _V2(_(15), _(15)), _CO(colors::Bg2), window::ui::rounding);
		window->DrawList->AddImageRounded((ImTextureID)Images::bg, window->Pos + _V2(_x,_ (15)), window->Pos + window->Size - _V2(_(15), _(15)), { 0, 0 }, { 1, 1 }, _CO(colors::White), window::ui::rounding);
		if (Items::IconButton("d", { window->Size.x - _(55), _(37) })) exit(0);

		a.render();
		
		if (a.tab == login) {
			PushStyleVar(ImGuiStyleVar_Alpha, a.alpha);

			PushFont(f.Lexend[1]);
			Draw::Image(Images::logo, { (window->Size.x - _(270)) / 2, _(5) }, { _(270), _(155) });
			Misc::MultiColoredText("SATURN", { (window->Size.x - _C("SATURN").x) / 2, _(160) });
			PopFont();

			PushFont(f.Poppins[0]);
			Items::Input("Discord Username", "a", { (window->Size.x - _(320)) / 2, _(250) }, usrbuf, _S(usrbuf), 0);
			Items::Input("License", "c", { (window->Size.x - _(320)) / 2, _(320) }, licbuf, _S(licbuf));
			Items::Checkbox("Remember me", { _(88), _(395) }, &remember, _(312));
			if (Items::Button("SIGN IN", { (window->Size.x - _(320)) / 2, _(435) }, { _(320), _(40) })) {
				std::thread login([]() {
					if (!CheckBuf(usrbuf))
						Items::CallNotif("Please enter a valid discord username.", error);
					if (!CheckBuf(licbuf) /*|| !license.login(licbuf)*/)
						Items::CallNotif("Please enter a valid license key.", error);
					else
						a.index = home;
				}); login.detach();
			}
			PopFont();

			const int vtx = window->DrawList->VtxBuffer.Size;
			ImVec2 center = window->Pos + window->Size * 0.5f;
			window->DrawList->AddLine(ImVec2(center.x - _(125), _(510)), ImVec2(center.x + _(125), _(510)), _CO(colors::Main), _(1.0f));
			ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vtx, window->DrawList->VtxBuffer.Size, { center.x - _(125), _(510) },
				{ center.x + _(125), _(510) }, _CO(colors::Main), _CO(colors::Second));

			Items::Ball("e", { _(155), _(535) });
			Items::Ball("f", { _(285), _(535) });
			PopStyleVar();
		}

		if (a.tab > login) {
			Draw::Image(Images::logo, _V2(_(-30), (window->Size.y - _(94)) / 2), _V2(_(167), _(94)));
			PushFont(f.Lexend[0]);
			Misc::MultiColoredText("SATURN SPOOFER", { _(140), _(35) });
			PopFont();

			PushFont(f.Poppins[1]);
			if (Items::Tab("Home", { _(455), _(35) }, a.tab == home)) a.index = home;  SameLine();
			if (Items::Tab("Spoofer", { 0, _(35) }, a.tab == spoofer)) a.index = spoofer; SameLine();
			if (Items::Tab("Checker", { 0, _(35) }, a.tab == checker)) a.index = checker;
			PopFont();

			Draw::Line({ _(425), _(40) }, { 0, _(17) }, colors::LWhite3);
			Draw::Line({ _(705), _(40) }, { 0, _(17) }, colors::LWhite3);
		}

		if (a.tab == home) {
			window::ui::SizeOnChange.x = _(790.f);
			if (window::ui::size.x >= _(788)) _x = ImLerp(_x, _(100.f), TIME);

			PushStyleVar(ImGuiStyleVar_Alpha, a.alpha);
			
			PushFont(f.PoppinsMedium[1]);
			Misc::Text("Welcome, ", { _(125), _(110) }, colors::LWhite2);
			Misc::MultiColoredText(usrbuf, { _(125) + _C("Welcome, ").x, _(110) });
			PopFont();

			PushFont(f.Poppins[0]);
			Misc::Text("If you experience any error contact the support via discord.", { _(125), _(140) }, colors::LWhite3);
			PopFont();
			
			Items::Announcement("SATURN LAST UPDATE", "Release of Saturn Permanent woofer. Added new protection & advanced\nmotherboard detection.", { _(115), _(200) });
			Items::Announcement("SATURN UPDATE V 0.1", "Saturn permanent testing phase. Bug fixes & more.", { _(115), _(315) });
				
			PopStyleVar();
		}

		if (a.tab == spoofer) {
			PushStyleVar(ImGuiStyleVar_Alpha, a.alpha);
			Items::Checkbox2("TPM BYPASS", "Bypasses TPM bans.\nRequired for Valorant users.", { _(125), _(120) }, &tpm);
			Items::Checkbox2("ARP FIX", "Fix your ARP & prevent delay bans.", { _(440), _(120) }, &tpm2);
			if (Items::SpoofItem("PERMANENT SPOOF", "Virtualize your system to its fullest. Get permanently unbanned & spoofed.", { _(125), _(250) })) {
				std::thread nigger([]() {
					Items::CallNotif("Started spoofing. Be patient, this process can take up to two minutes.", info);
					fspoof = true;
				});
				nigger.detach();

			}
			PopStyleVar();
		}
		
		if (a.tab == checker) {
			PushStyleVar(ImGuiStyleVar_Alpha, a.alpha);
			PushFont(f.PoppinsMedium[1]);
			Misc::MultiColoredText("SYSTEM INFORMATION", { _(125), _(125) });
			Misc::MultiColoredText("HARDWARE IDENTIFIERS", { _(125), _(315) });
			PopFont();
			PushFont(f.PoppinsMedium[2]);
			Items::Serial("Bios Manufacturer: ", "American Megatrends International, Ltd.", { _(125), _(170) }, null);
			Items::Serial("Motherboard Manufacturer: ", "Gigabyte Technology Co., Ltd.", { _(125), _(200) }, null);
			Items::Serial("Motherboard Model: ", "A320M-S2H-CF", { _(125), _(230) }, null);
			Items::Serial("CPU: ", "AMD Ryzen 5 5600X 6-Core Processor", { _(125), _(260) }, null);

			std::string MoboSerial = ReadyToChange ? "ZFGA62HBAX61F" : "Z4S49C28N3ECF";
			std::string MacSerial = ReadyToChange ? "1C:6A:53:FA:19:BE" : "2F:B1:20:AC:12:AF";
			std::string UUID = ReadyToChange ? "43DBEB2C-AAF8-4028-BA92-A8021073648A" : "55E32C71-37CC-4B35-8214-B8009C1CA764";

			SerialStatus status = ReadyToChange ? changed : unchanged;

			Items::Serial("Motherboard: ", MoboSerial, { _(125), _(360) }, status);
			Items::Serial("MAC Address: ", MacSerial, { _(125), _(390) }, status);
			Items::Serial("SMBIOS: ", "To be filled by O.E.M", { _(125), _(420) }, changed);
			Items::Serial("CPU: ", "Unknown", { _(125), _(450) }, changed);
			Items::Serial("UUID: ", UUID, { _(125), _(480) }, status);

			PopFont();

			PushFont(f.Poppins[3]);
			Misc::Text("Note: Serial number 'Unknown', 'To be filled by O.E.M' & 'Default String' do not have to change.", {_(125), _(550)}, colors::LWhite4);
			PopFont();

			PopStyleVar();
		}
		Items::RenderNotif();

		if (fspoof) {
			static float timer = 0;
			if (timer < 60) {
				ImGuiIO& io = GetIO();
				timer += io.DeltaTime * 5;
			}
			else {
				ReadyToChange = true;
				Items::CallNotif("Successfully spoofed your PC", success);
				fspoof = false;
			}
		}
	}
	ImGui::End();
}
