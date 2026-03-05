#include "colors.hpp"

void SetStyle() {
    ImGuiStyle& style = GetStyle();

    style.WindowBorderSize = 0.f;
    style.ScrollbarSize = 0.f;
    style.WindowPadding = { 0.f, 0.f };
    style.Colors[ImGuiCol_ChildBg] = colors::Transparent;
    style.Colors[ImGuiCol_TextSelectedBg] = colors::Main;
    style.ItemSpacing = _V2(_(30), _(10));
} 

void MoveWindow(HWND g_hwnd) {
    RECT rc, winRect;
    ImGuiIO& io = GetIO();

    GetWindowRect(g_hwnd, &rc);
    MoveWindow(g_hwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, window::dx::size.x, window::dx::size.y, TRUE);

    window::ui::size = ImLerp(window::ui::size, window::ui::SizeOnChange, TIME);

    GetWindowRect(window::dx::hwnd, &winRect);

    int Width = window::ui::size.x;
    int Height = window::ui::size.y;

    int CenterX = winRect.left + (winRect.right - winRect.left) / 2;
    int CenterY = winRect.top + (winRect.bottom - winRect.top) / 2;

    int NewX = CenterX - Width / 2;
    int NewY = CenterY - Height / 2;

    MoveWindow(window::dx::hwnd, NewX, NewY, Width, Height, true);

    ImGui::SetWindowPos(ImVec2(0.f, 0.f));
}

void RenderBorder() {
    ImGuiWindow* window = GetCurrentWindow();

    float time = GetTime();
    float balpha = ((sin(time * 4.0f) * 0.5f + 0.5f) * (255 - 100) + 100) / 255.0f;
    _V4 col = { colors::Main.x, colors::Main.y, colors::Main.z, balpha };

    const int vtx_buf(window->DrawList->VtxBuffer.Size);
    window->DrawList->AddRect(window->Pos, window->Pos + window->Size, _CO(col), window::ui::rounding);
    ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vtx_buf, window->DrawList->VtxBuffer.Size, window->Pos,
        window->Pos + window->Size / 2, _CO(col), _CO(colors::Bg));
}

void Misc::Begin(const std::string& name) {
#ifndef DXBG
    SetNextWindowPos({ 0, 0 }, ImGuiCond_Appearing);
#endif
    SetNextWindowSize(window::ui::size);
    ImGui::Begin(name.c_str(), 0, WindowFlags);
    Draw::Rect({ 0, 0 }, window::ui::size, colors::Bg, window::ui::rounding);
    RenderBorder();
    SetStyle();

#ifndef DXBG
    MoveWindow(window::dx::hwnd);
#endif
}

void Misc::Text(const std::string& text, const _V2& pos_arg, _V4& col) {
    ImGuiWindow* window = GetCurrentWindow();

    if (pos_arg.x != 0) SetCursorPosX(pos_arg.x);
    if (pos_arg.y != 0) SetCursorPosY(pos_arg.y);

    _V2 pos = window->DC.CursorPos;
    window->DrawList->AddText(pos, _CO(col), text.c_str());
}

void Misc::MultiColoredText(const std::string& text, const _V2& pos_arg) {
    ImGuiWindow* window = GetCurrentWindow();

    if (pos_arg.x != 0) SetCursorPosX(pos_arg.x);
    if (pos_arg.y != 0) SetCursorPosY(pos_arg.y);

    _V2 pos = window->DC.CursorPos;
    _V2 size(_C(text.c_str()));
    const int vtx_buf(window->DrawList->VtxBuffer.Size);
    window->DrawList->AddText(pos, _CO(colors::Main), text.c_str());
    ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vtx_buf, window->DrawList->VtxBuffer.Size, pos, pos + size,
        _CO(colors::Second), _CO(colors::Main));
}

/* Draw */

void Draw::Rect(const _V2& p1, const _V2& p2, const _V4& col, const float& rounding, DrawFlags flags) {
    ImGuiWindow* window = GetCurrentWindow(); 

    SetCursorPos(p1);
    _V2 pos(window->DC.CursorPos);
    static DWORD fFlags;

    if (flags & RoundTop)       fFlags |= ImDrawFlags_RoundCornersTop;
    if (flags & RoundBottom)    fFlags |= ImDrawFlags_RoundCornersBottom;
    if (flags & RoundTopLeft)   fFlags |= ImDrawFlags_RoundCornersTopLeft;
    if (flags & RoundTopRight)  fFlags |= ImDrawFlags_RoundCornersTopRight;
    if (flags & RoundBotLeft)   fFlags |= ImDrawFlags_RoundCornersBottomLeft;
    if (flags & RoundBotRight)  fFlags |= ImDrawFlags_RoundCornersBottomRight;

    if (!(flags & NoFill))
        window->DrawList->AddRectFilled(pos, pos + p2, _CO(col), rounding, fFlags);
    else
        window->DrawList->AddRect(pos, pos + p2, _CO(col), rounding, fFlags);
}

void Draw::Circle(const _V2& p1, float rad, const _V4& col, DrawFlags flags) {
    ImGuiWindow* window = GetCurrentWindow();

    SetCursorPos(p1);
    _V2 pos(window->DC.CursorPos);

    if (!(flags & NoFill))
        window->DrawList->AddCircleFilled(pos, rad, _CO(col), 1000);
    else
        window->DrawList->AddCircle(pos, rad, _CO(col), 1000);
}

void Draw::Image(ID3D11ShaderResourceView* texture, const _V2& p1, const _V2& p2, const _V4& col, const float& rounding) {
    ImGuiWindow* window = GetCurrentWindow();

    SetCursorPos(p1);
    _V2 pos(window->DC.CursorPos);

    window->DrawList->AddImageRounded((ImTextureID)texture, pos, pos + p2, { 0, 0 }, { 1, 1 }, _CO(col), rounding);
}

void Draw::Line(const _V2& p1, const _V2& p2, const _V4& col) {
    ImGuiWindow* window = GetCurrentWindow();

    SetCursorPos(p1);
    _V2 pos(window->DC.CursorPos);
    window->DrawList->AddLine(pos, pos + p2, _CO(col));
}

void Misc::Blur(HWND hwnd) {
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary(L"user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 };

            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}