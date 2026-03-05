#define IMGUI_DEFINE_MATH_OPERATORS
#pragma comment(lib, "D3DX11.lib")

#include <iostream>
#include <windows.h>
#include <d3d11.h>
#include <D3DX11tex.h>
#include <tchar.h>
#include <dwmapi.h>
#include <map>
#include <algorithm>
#include <array>

#include "imgui.h"
#include "imgui_freetype.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "../__ext/fonts.h"
using namespace ImGui;

#define _(arg) (arg * eScale)
inline float x = GetSystemMetrics(SM_CXSCREEN);
inline float eScale = (x / 1920);

/* ----------------------------DEFINES------------------------------------ */

//#define DBG
//#define DXBG

#define _C(ARG) (CalcTextSize(ARG))
#define _CO(ARG) (GetColorU32(ARG))
#define _S(ARG) ((int)(sizeof(ARG) / sizeof(*(ARG)))) 

#define _V2 ImVec2
#define _V4 ImVec4
#define RGBA ImColor
#define TIME (Time(17))

#define EIMAGE(DVC, PDATA, TARGET) \
 (D3DX11CreateShaderResourceViewFromMemory(DVC, PDATA, sizeof(PDATA), nullptr, nullptr, &TARGET, nullptr))

#define EFONT(PDATA, FSIZE, CFG) \
    (io.Fonts->AddFontFromMemoryTTF(PDATA, sizeof(PDATA), FSIZE, &CFG))

/* ----------------------------------------------------------------------- */

enum tabs {
    login,
    home,
    spoofer,
    checker
};

/* ------------------------------WINDOW----------------------------------- */
inline float Time(float t) { return GetIO().DeltaTime * t; }

namespace window
{
    namespace ui
    {
        inline _V2 size = ImVec2(_(485), _(630));
        inline _V2 SizeOnChange = window::ui::size;
        inline float rounding = _(10.f);
    }

    namespace dx
    {
        inline HWND hwnd;
#ifdef DXBG
        inline _V2 size = { 1200, 800 };
#else
        inline _V2 &size = ui::size;
#endif 
    }
}

/* ----------------------------------------------------------------------- */


/* ------------------------------RENDER----------------------------------- */

namespace ui
{
    void BeforeLoop(ID3D11Device* dvc);
    void Render();
}

/* ----------------------------------------------------------------------- */

enum SerialStatus {
    null,
    changed,
    unchanged
};

/* ----------------------------FONTS-&-IMAGES------------------------------ */

struct Fonts {
    std::array<float, 4> PoppinsSizes = { _(15), _(16), _(14), _(12)};
    std::array<float, 4> PoppinsMediumSizes = { _(18), _(20), _(16), _(15) };
    std::array<float, 2> LexendSizes = { _(20), _(26) };
    
    std::array<ImFont*, 4> Poppins = {  };
    std::array<ImFont*, 4> PoppinsMedium = {  };
    std::array<ImFont*, 2> Lexend = {  };
    ImFont* icons;
    ImFont* pass;

    void RenderFonts();
}; inline Fonts f;

inline void Fonts::RenderFonts() {
    ImGuiIO& io = GetIO();
    ImFontConfig cfg;
    cfg.FontDataOwnedByAtlas = false;
    cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

    for (int i = 0; i < f.PoppinsSizes.size(); i++)
        f.Poppins[i] = EFONT(__Poppins, f.PoppinsSizes[i] + _(6), cfg);

    for (int i = 0; i < f.PoppinsMediumSizes.size(); i++)
        f.PoppinsMedium[i] = EFONT(__PoppinsMedium, f.PoppinsMediumSizes[i] + _(6), cfg);

    for (int i = 0; i < f.LexendSizes.size(); i++)
        f.Lexend[i] = EFONT(__Lexend, f.LexendSizes[i] + _(5), cfg);

    f.icons = EFONT(__Icons, _(20), cfg);
    f.pass = EFONT(__Passw, _(25), cfg);
}

namespace Images 
{
    inline ID3D11ShaderResourceView* bg;
    inline ID3D11ShaderResourceView* logo;
}

/* ----------------------------------------------------------------------- */

struct alpha_s {
    int index, tab;
    float alpha, time;

    bool render() {
        if (alpha == 0)
            tab = index;

        time = GetIO().DeltaTime * 9;
        return alpha = std::clamp(alpha + (time * (index == tab ? 1.f : -1.f)), 0.f, 1.f);
    }
};

/* ----------------------------------------------------------------------- */