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

}