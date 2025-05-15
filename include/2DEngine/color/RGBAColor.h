#pragma once

/**
 * Spreads the RGB values of a color for use in functions that accept a 3-tuple of r, g, and b arguments.
 * It is recommended that you define your color elsewhere before passing it to this macro to avoid
 * unnecessary recalculations.
 */
#define RGB(x) (x).r, (x).g, (x).b

/**
 * Spreads the RGBA values of a color for use in functions that accept a 4-tuple of r, g, b, and a arguments.
 * It is recommended that you define your color elsewhere before passing it to this macro to avoid
 * unnecessary recalculations.
 */
#define RGBA(x) (x).r, (x).g, (x).b, (x).a

/**
 * A struct representing a color in RGBA space. Accepts construction from either a hex value or RGBA values.
 * Provides the properties r, g, b, and a. Instances of this struct can be spread using the `RGB` macro or
 * `RGBA` macros.
 */
struct alignas(4) RGBAColor {
    float r{}, g{}, b{}, a{};
    
    /**
     * Constructs a new color from a hex code
     * @param hex - The hex color in the format 0xRRGGBBAA
     */
    explicit RGBAColor(unsigned int hex) noexcept;

    /**
     * Constructs a new color from RGBA values
     * @param r - The red value
     * @param g - The green value
     * @param b - The blue value
     * @param a - The alpha value, can be omitted
     */
    RGBAColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) noexcept;
};

/**
 * A namespace providing commonly used colors for ease of access.
 *
 * Predefined colors include: red, orange, yellow, green, blue,
 * purple, pink, white, light_gray, gray, and black
 */
namespace RGBAColors {
    inline const auto red         = RGBAColor(0xFF0000FF);
    inline const auto orange      = RGBAColor(0xFFA500FF);
    inline const auto yellow      = RGBAColor(0xFFFF00FF);
    inline const auto green       = RGBAColor(0x00FF00FF);
    inline const auto blue        = RGBAColor(0x518bf7FF);
    inline const auto purple      = RGBAColor(0x9E00FFFF);
    inline const auto pink        = RGBAColor(0xFF00FFFF);
    inline const auto white       = RGBAColor(0xFFFFFFFF);
    inline const auto light_gray  = RGBAColor(0x5f5f5fFF);
    inline const auto gray        = RGBAColor(0x939393FF);
    inline const auto black       = RGBAColor(0x4b4b4bFF);
}
