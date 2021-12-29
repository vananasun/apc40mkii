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
#include <utility>

namespace APCAPI
{
    
    enum class EventType
    {
        None = 0,

        PlayStop,
        Record,
        Session,
        Metronome,
        TapTempo,
        Nudge,
        Pan,
        Sends,
        User,
        Tempo,
        ClipLaunch,
        ClipStop,
        StopAllClips,
        SceneLaunch,
        CueLevel,
        MasterSelector,
        MasterFader,
        TrackSelector,
        TrackActivator,
        TrackFader,
        TrackSolo,
        TrackRecord,
        TrackAB,
        BankSelectLeft,
        BankSelectUp,
        BankSelectRight,
        BankSelectDown,
        Shift,
        Bank,
        TrackKnob,
        DeviceKnob,
        DeviceOnOff,
        DeviceLock,
        DeviceLeft,
        DeviceRight,
        BankLeft,
        BankRight,
        ClipDeviceView,
        DetailView,
        Crossfader,
        Footswitch

    };
    
    inline const char *EventTypeAsString[] =
    {
        "None",
        "PlayStop",
        "Record",
        "Session",
        "Metronome",
        "TapTempo",
        "Nudge",
        "Pan",
        "Sends",
        "User",
        "Tempo",
        "ClipLaunch",
        "ClipStop",
        "StopAllClips",
        "SceneLaunch",
        "CueLevel",
        "MasterSelector",
        "MasterFader",
        "TrackSelector",
        "TrackActivator",
        "TrackFader",
        "TrackSolo",
        "TrackRecord",
        "TrackAB",
        "BankSelectLeft",
        "BankSelectUp",
        "BankSelectRight",
        "BankSelectDown",
        "Shift",
        "Bank",
        "TrackKnob",
        "DeviceKnob",
        "DeviceOnOff",
        "DeviceLock",
        "DeviceLeft",
        "DeviceRight",
        "BankLeft",
        "BankRight",
        "ClipDeviceView",
        "DetailView",
        "Crossfader",
        "Footswitch"
    };

    inline const char *GetEventTypeString(EventType type)
    {
        if (type >= EventType::None && type <= EventType::Footswitch)
            return EventTypeAsString[static_cast<int>(type)];
        return nullptr;
    };


    /**
     *  \brief Converts a clip ID to a set of X,Y coordinates.
     *         [0,0] = Bottom left!
     * 
     *  \param clipId
     * 
     *  \returns [ x, y ]
     */
    inline const constexpr std::pair<ClipCoord,ClipCoord> ClipId2Coords(ClipIndex clipId)
    {
        return { static_cast<ClipCoord>(clipId & 7), static_cast<ClipCoord>(clipId >> 3) };
    }


    /**  \see tests/test.cpp GetEventInfo() */
    struct Event
    {
        EventType type = EventType::None;
        union {
            unsigned char value = 0; // 0 to 127
            char direction; // +, -
            bool pressed;
        };
        union {
            TrackIndex trackId = 0;
            SceneIndex sceneId;
            ClipIndex clipId;
            KnobIndex knobId;
        };
        PageIndex pageId; // only for mode 0 banked stuff
    };


}

