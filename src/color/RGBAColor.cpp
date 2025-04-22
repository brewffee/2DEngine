#include "../../include/color/RGBAColor.h"

RGBAColor::RGBAColor(unsigned int hex):
    r((hex >> 24 & 0xFF) / 255.0),
    g((hex >> 16 & 0xFF) / 255.0),
    b((hex >> 8 & 0xFF) / 255.0),
    a((hex & 0xFF) / 255.0) {}

RGBAColor::RGBAColor(int r, int g, int b, int a):
    r(r / 255.0),
    g(g / 255.0),
    b(b / 255.0),
    a(a / 255.0) {}
