#pragma once

/**
 * Spreads the RGB values of a color for use in functions that accept a 3-tuple of r, g, and b arguments.
 * It is recommended that you define your color elsewhere before passing it to this macro to avoid
 * unnecessary recalculations.
 */
#define RGB(x) x.r, x.g, x.b

/**
 * Spreads the RGBA values of a color for use in functions that accept a 4-tuple of r, g, b, and a arguments.
 * It is recommended that you define your color elsewhere before passing it to this macro to avoid
 * unnecessary recalculations.
 */
#define RGBA(x) x.r, x.g, x.b, x.a

/**
 * A struct representing a color in RGBA space. Accepts construction from either a hex value or RGBA values.
 * Provides the properties r, g, b, and a. Instances of this struct can be spread using the `RGB` macro or
 * `RGBA` macros.
 */
struct RGBAColor {
    public:
        double r, g, b, a;
        
        /**
         * Constructs a new color from a hex code
         * @param hex - The hex color in the format 0xRRGGBBAA
         */
        explicit RGBAColor(unsigned int hex);
        
        /**
         * Constructs a new color from RGBA values
         * @param r - The red value
         * @param g - The green value
         * @param b - The blue value
         * @param a - The alpha value, can be omitted
         */
        RGBAColor(int r, int g, int b, int a = 255);
};

/**
 * A namespace providing commonly used colors for ease of access.
 *
 * Predefined colors include: red, orange, yellow, green, blue,
 * purple, pink, white, light_gray, gray, and black
 */
namespace RGBAColors {
    inline auto red         = RGBAColor(0xFF0000FF);
    inline auto orange      = RGBAColor(0xFFA500FF);
    inline auto yellow      = RGBAColor(0xFFFF00FF);
    inline auto green       = RGBAColor(0x00FF00FF);
    inline auto blue        = RGBAColor(0x518bf7FF);
    inline auto purple      = RGBAColor(0x9E00FFFF);
    inline auto pink        = RGBAColor(0xFF00FFFF);
    inline auto white       = RGBAColor(0xFFFFFFFF);
    inline auto light_gray  = RGBAColor(0x5f5f5fFF);
    inline auto gray        = RGBAColor(0x939393FF);
    inline auto black       = RGBAColor(0x4b4b4bFF);
}
