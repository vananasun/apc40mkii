#include <APCAPI.h>
#include "./APCCore.h"

using namespace APCAPI;

#define CLAMP(value, min, max) (value > max ? max : (value < min ? min : value))

#define setBooleanLED(controlId)\
    if (!_->m_connected) return;\
    _->sendMsg({\
        (unsigned char)(enabled ? 0x90 : 0x80),\
        (unsigned char)(controlId),\
        (unsigned char)0x7F\
    })

#define setBooleanLEDBanked(controlId, pageId)\
    if (!_->m_connected) return;\
    _->sendMsg({\
        (unsigned char)((enabled ? 0x90 : 0x80) | pageId),\
        (unsigned char)(controlId),\
        (unsigned char)0x7F\
    })



/* Regular buttons */

void APC40MkII::setPlay(bool enabled) { setBooleanLED(0x5B); }
void APC40MkII::setRecord(bool enabled) { setBooleanLED(0x5D); }
void APC40MkII::setSession(bool enabled) { setBooleanLED(0x66); }
void APC40MkII::setMetronome(bool enabled) { setBooleanLED(0x5A); }
void APC40MkII::setPan(bool enabled) { setBooleanLED(0x57); }
void APC40MkII::setSends(bool enabled) { setBooleanLED(0x58); }
void APC40MkII::setUser(bool enabled) { setBooleanLED(0x59); }
void APC40MkII::setBank(bool enabled) { setBooleanLED(0x67); }
void APC40MkII::setMasterSelector(bool enabled) { setBooleanLED(0x50); }



/* Mode 0 banked device stuff */

void APC40MkII::setDeviceLeft(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3A, page); }
void APC40MkII::setDeviceRight(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3B, page); }
void APC40MkII::setBankLeft(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3C, page); }
void APC40MkII::setBankRight(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3D, page); }
void APC40MkII::setDeviceOnOff(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3E, page); }
void APC40MkII::setDeviceLock(bool enabled, PageIndex page) { setBooleanLEDBanked(0x3F, page); }
void APC40MkII::setClipDeviceView(bool enabled, PageIndex page) { setBooleanLEDBanked(0x40, page); }
void APC40MkII::setDetailView(bool enabled, PageIndex page) { setBooleanLEDBanked(0x41, page); }

void APC40MkII::setDeviceKnob(KnobIndex knob, KnobValue value, PageIndex page)
{
    if (!_->m_connected) return;
    if (knob > 7) return;
    if (page > 8) return;
    _->sendMsg({
        (unsigned char)(0xB0 | page),
        (unsigned char)(0x10 | knob),
        (unsigned char)CLAMP(value, 0, 127)
    });
}

void APC40MkII::setDeviceKnobRingType(KnobIndex knob, RingType type, PageIndex page)
{
    if (!_->m_connected) return;
    if (knob > 7) return;
    if (page > 8) return;
    _->sendMsg({
        (unsigned char)(0xB0 | page),
        (unsigned char)(0x18 | knob),
        (unsigned char)type
    });
}



/* Track specific */

void APC40MkII::setTrackSelector(TrackIndex track, bool enabled)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((enabled ? 0x90 : 0x80) | track),
        (unsigned char)0x33,
        (unsigned char)0x7F
    });
}

void APC40MkII::setTrackActivator(TrackIndex track, bool enabled)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((enabled ? 0x90 : 0x80) | track),
        (unsigned char)0x32,
        (unsigned char)0x7F
    });
}

void APC40MkII::setTrackSolo(TrackIndex track, bool enabled)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((enabled ? 0x90 : 0x80) | track),
        (unsigned char)0x31,
        (unsigned char)0x7F
    });
}

void APC40MkII::setTrackRecord(TrackIndex track, bool enabled)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((enabled ? 0x90 : 0x80) | track),
        (unsigned char)0x30,
        (unsigned char)0x7F
    });
}

void APC40MkII::setTrackAB(TrackIndex track, DualColor state)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((state ? 0x90 : 0x80) | track),
        (unsigned char)0x42,
        (unsigned char)state
    });
}

void APC40MkII::setTrackKnob(TrackIndex track, KnobValue value)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)0xB0,
        (unsigned char)(0x30 | track),
        (unsigned char)CLAMP(value, 0, 127)
    });
}

void APC40MkII::setTrackKnobRingType(TrackIndex track, RingType type)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)0xB0,
        (unsigned char)(0x38 + track),
        (unsigned char)type
    });
}

void APC40MkII::setClipStop(TrackIndex track, ClipStopLED state)
{
    if (!_->m_connected) return;
    if (track > 7) return;
    _->sendMsg({
        (unsigned char)((state == ClipStopLED::Off ? 0x80 : 0x90) | track),
        (unsigned char)0x34,
        (unsigned char)state
    });
}



/* Miscellaneous */

void APC40MkII::setSceneLaunch(SceneIndex row, Color color, LEDType type)
{
    if (!_->m_connected) return;
    if (row > 4) return;
    _->sendMsg({
        (unsigned char)((color == Color::Off ? 0x80 : 0x90) | (unsigned char)type),
        (unsigned char)(0x52 + row),
        (unsigned char)color
    });
}

void APC40MkII::setClip(ClipCoord x, ClipCoord y, Color color, LEDType type)
{
    if (!_->m_connected) return;
    if (x > 7 || y > 4) return;
    _->sendMsg({
        (unsigned char)((color == Color::Off ? 0x80 : 0x90) | (unsigned char)type),
        (unsigned char)(x + (y * 8)),
        (unsigned char)color
    });
}
