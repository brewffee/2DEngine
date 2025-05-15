#include "2DEngine/color/RGBAColor.h"

RGBAColor::RGBAColor(const unsigned int hex) noexcept:
    r((hex >> 24u & 0xFFu) / 255.f),
    g((hex >> 16u & 0xFFu) / 255.f),
    b((hex >> 8u & 0xFFu) / 255.f),
    a((hex & 0xFFu) / 255.f) {}

RGBAColor::RGBAColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a) noexcept:
    r(r / 255.f),
    g(g / 255.f),
    b(b / 255.f),
    a(a / 255.f) {}
