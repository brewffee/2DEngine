#include "../../include/color/RGBAColor.h"

RGBAColor::RGBAColor(const unsigned int hex) noexcept:
    r((hex >> 24u & 0xFFu) / 255.0),
    g((hex >> 16u & 0xFFu) / 255.0),
    b((hex >> 8u & 0xFFu) / 255.0),
    a((hex & 0xFFu) / 255.0) {}

RGBAColor::RGBAColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a) noexcept:
    r(r / 255.0),
    g(g / 255.0),
    b(b / 255.0),
    a(a / 255.0) {}
