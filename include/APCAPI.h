/*
  Unofficial APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

#pragma once
#include "./APCAPI_Types.h"
#include "./APCAPI_Colors.h"
#include "./APCAPI_Events.h"

namespace APCAPI
{

    class APC40MkII
    {
    private:
        struct APCCore;
        APCCore* _;

    public:
        APC40MkII(ErrorCallback callback, void* userData);
        ~APC40MkII();
        bool connect(Mode mode = Mode::Ableton);
        void disconnect();
        void resetDisplay();
        bool poll(Event* event);


        /* Host to device output methods */

        void setBank(bool enabled);
        void setPlay(bool enabled);
        void setRecord(bool enabled);
        void setSession(bool enabled);
        void setMetronome(bool enabled);
        void setPan(bool enabled);
        void setSends(bool enabled);
        void setUser(bool enabled);
        void setMasterSelector(bool enabled);
        void setClipDeviceView(bool enabled, PageIndex page = 0);
        void setDetailView(bool enabled, PageIndex page = 0);
        void setBankLeft(bool enabled, PageIndex page = 0);
        void setBankRight(bool enabled, PageIndex page = 0);
        void setDeviceLeft(bool enabled, PageIndex page = 0);
        void setDeviceRight(bool enabled, PageIndex page = 0);
        void setDeviceOnOff(bool enabled, PageIndex page = 0);
        void setDeviceLock(bool enabled, PageIndex page = 0);
        void setDeviceKnob(KnobIndex knob, KnobValue value, PageIndex page = 0);
        void setDeviceKnobRingType(KnobIndex knob, RingType type, PageIndex page = 0);

        void setTrackSelector(TrackIndex track, bool enabled); // unavailable in Generic mode
        void setTrackActivator(TrackIndex track, bool enabled);
        void setTrackSolo(TrackIndex track, bool enabled);
        void setTrackRecord(TrackIndex track, bool enabled);
        void setTrackAB(TrackIndex track, DualColor state);
        void setTrackKnob(KnobIndex knob, KnobValue value);
        void setTrackKnobRingType(KnobIndex knob, RingType type);
        void setClipStop(TrackIndex track, ClipStopLED state = ClipStopLED::On);

        void setClip(ClipCoord x, ClipCoord y, Color color, LEDType type = LEDType::Primary);
        void setSceneLaunch(SceneIndex row, Color color, LEDType type = LEDType::Primary);

    };

    

};
