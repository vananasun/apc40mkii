/*
  Unofficial APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

#pragma once

namespace APCAPI
{
    
    /**
     *  \brief Read the color table at page 18 through 22 of the provided
     *         "APC40 mkII Communications Protocol v1.2.pdf".
     *         The "Velocity" column is the color ID.
     */
    enum class Color {
        Off = 0,
        White = 3,
        Red = 5,
        Green = 21,
        Blue = 45,
        Cyan = 37,
        Yellow = 13,
        Magenta = 53,
        Orange = 96,
    };

    /**
     *  \brief The type of LED.
     *         Primary is just a solid color.
     *         Oneshot fades toward a color.
     *         Pulsing fades in and out.
     *         Blinking flashes on and off.
     */
    enum class LEDType {
        Primary = 0,
        Oneshot_1_24 = 1,
        Oneshot_1_16 = 2,
        Oneshot_1_8 = 3,
        Oneshot_1_4 = 4,
        Oneshot_1_2 = 5,
        Pulsing_1_24 = 6,
        Pulsing_1_16 = 7,
        Pulsing_1_8 = 8,
        Pulsing_1_4 = 9,
        Pulsing_1_2 = 10,
        Blinking_1_24= 11,
        Blinking_1_16 = 12,
        Blinking_1_8 = 13,
        Blinking_1_4 = 14,
        Blinking_1_2 = 15,
    };


}