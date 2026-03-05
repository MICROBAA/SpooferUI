#include "..\main.hpp"
#define FRAMEWORK

inline DWORD WindowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar |
ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse;

typedef int DrawFlags;
FRAMEWORK enum __DrawFlags : DrawFlags {
    NoFill       = 1 << 0,
    RoundTop     = 1 << 1,
    RoundBottom  = 1 << 2,
    RoundTopLeft = 1 << 3,
    RoundTopRight= 1 << 4,
    RoundBotLeft = 1 << 5,
    RoundBotRight= 1 << 6
};

enum NotifType {
    info,
    success,
    error
};

namespace Misc {
    FRAMEWORK void Begin(const std::string& name);
    FRAMEWORK void Text(const std::string& text, const _V2& pos_arg, _V4& col);
    FRAMEWORK void MultiColoredText(const std::string& text, const _V2& pos_arg);
    FRAMEWORK void Blur(HWND hwnd);
}

namespace Items {
    FRAMEWORK bool Input(const std::string& label, const std::string& icon, const _V2& pos_arg, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0);
    FRAMEWORK bool Checkbox(const std::string& label, const _V2& pos_arg, bool* v, float x);
    FRAMEWORK bool Checkbox2(const std::string& label, const std::string& label2, const _V2& pos_arg, bool* v);
    FRAMEWORK bool Button(const std::string& label, const _V2& pos_arg, const _V2& size);
    FRAMEWORK bool Ball(const std::string& icon, const _V2& pos_arg);
    FRAMEWORK bool Tab(const std::string& label, const _V2& pos_arg, bool cond);
    FRAMEWORK bool IconButton(const std::string& label, const _V2& pos_arg);
    FRAMEWORK void Announcement(const std::string& title, const std::string& desc, const _V2& pos_arg);
    FRAMEWORK bool SpoofItem(const std::string& label, const std::string& desc, const _V2& pos_arg);
    FRAMEWORK void Serial(const std::string& label, const std::string& serial, const _V2& pos, SerialStatus status);
    FRAMEWORK void CallNotif(const std::string& notif, NotifType type);
    FRAMEWORK void RenderNotif();
}

namespace Draw {
    FRAMEWORK void Rect(const _V2& p1, const _V2& p2, const _V4& col, const float& rounding = 0, DrawFlags flags = 0);
    FRAMEWORK void Circle(const _V2& p1, float rad, const _V4& col, DrawFlags flags);
    FRAMEWORK void Image(ID3D11ShaderResourceView* texture, const _V2& p1, const _V2& p2, const _V4& col = _V4(1,1,1,1), const float& rounding = 0);
    FRAMEWORK void Line(const _V2& p1, const _V2& p2, const _V4& col);
}