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
     *  \brief Input types received from the APC
     */
    enum class EventType {
        None = 0,

        PlayStop = 1,
        Record = 2,
        Session = 3,
        Metronome = 10,
        TapTempo = 11,
        Nudge = 15,
        Pan = 12,
        Sends = 13,
        User = 14,
        Tempo = 37,

        ClipLaunch = 38,
        ClipStop = 9,
        StopAllClips = 39,
        SceneLaunch = 4,
        CueLevel = 36,
        MasterSelector = 40,
        MasterFader = 35,

        TrackSelector = 25,
        TrackActivator = 5,
        TrackFader = 24,
        TrackSolo = 6,
        TrackRecord = 7,
        TrackAB = 8,

        BankSelectLeft = 16,
        BankSelectUp = 17,
        BankSelectRight = 18,
        BankSelectDown = 19,
        Shift = 20,
        Bank = 21,

        TrackKnob = 22,
        DeviceKnob = 23,

        DeviceOnOff = 32,
        DeviceLock = 33,
        DeviceLeft = 26,
        DeviceRight = 27,

        BankLeft = 30,
        BankRight = 31,

        ClipDeviceView = 33,
        DetailView = 34,
        Crossfader = 41,

    };


    struct Event {
        APCAPI::EventType type = APCAPI::EventType::None;
        union {
            unsigned char value = 0;
            char direction;
        };
        union {
            unsigned char trackId = 0;
            unsigned char sceneId;
            unsigned char clipId;
        };
    };

}

