/*
  Unofficial APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

// You do not need to include this file separately.

#pragma once
#include <string>

namespace APCAPI
{

    typedef void (*ErrorCallback)(const std::string& msg, void *userData);
    
    typedef unsigned char SceneIndex;
    typedef unsigned char TrackIndex;
    typedef unsigned char PageIndex;
    typedef unsigned char KnobIndex;
    typedef unsigned char KnobValue;

    
    /**
     *  \brief A knob's LED style. Default is Single.
     *         Off is no usable knob.
     *         Single means that only a single LED is ever lit up.
     *         Volume fills up all LEDs until the knob value.
     *         Pan fills up LEDs starting from the center.
     */
    enum class RingType {
        Off = 0,
        Single = 1,
        Volume = 2,
        Pan = 3,
    };

    /**
     *  \brief The firmware mode.
     *         Read page 11-12 of the Communications Protocol pdf.
     */
    enum class Mode
    {
        Generic = 0, // Banked. I highly recommend against this mode!
        Ableton = 1, // Default (and recommended!) for this API
        AlternateAbleton = 2, // Full control by host, which makes it laggier
    };


    typedef unsigned char ClipIndex;
    typedef unsigned char ClipCoord;
    typedef struct {
        ClipCoord x;
        ClipCoord y;
    } ClipCoords;

    /**
     *  \brief Converts a clip ID to a set of X,Y coordinates.
     *         [0,0] = Bottom left!
     * 
     *  \param clipId
     * 
     *  \returns [ x, y ]
     */
    inline constexpr ClipCoords ClipId2Coords(ClipIndex clipId)
    {
        return { static_cast<ClipCoord>(clipId & 7), static_cast<ClipCoord>(clipId >> 3) };
    }

    /**
     *  \brief Converts clip X,Y coordinates to it's corresponding clip index.
     * 
     *  \param coords [0,0] = Bottom left!
     * 
     *  \returns ClipIndex
     */
    inline constexpr ClipIndex ClipCoords2Id(ClipCoords coords)
    {
        return coords.x | (coords.y << 3);
    }

}