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


void APC40MkII::setPlay(bool enabled) { setBooleanLED(0x5B); }

void APC40MkII::setRecord(bool enabled) { setBooleanLED(0x5D); }

void APC40MkII::setSession(bool enabled) { setBooleanLED(0x66); }

void APC40MkII::setMetronome(bool enabled) { setBooleanLED(0x5A); }

void APC40MkII::setTapTempo(bool enabled) { setBooleanLED(0x63); }

void APC40MkII::setPan(bool enabled) { setBooleanLED(0x57); }

void APC40MkII::setSends(bool enabled) { setBooleanLED(0x58); }

void APC40MkII::setUser(bool enabled) { setBooleanLED(0x59); }

void APC40MkII::setDeviceOnOff(bool enabled) { setBooleanLED(0x3E); }

void APC40MkII::setDeviceLock(bool enabled) { setBooleanLED(0x3F); }

void APC40MkII::setDeviceLeft(bool enabled) { setBooleanLED(0x3A); }

void APC40MkII::setDeviceRight(bool enabled) { setBooleanLED(0x3B); }

void APC40MkII::setBank(bool enabled) { setBooleanLED(0x67); }

void APC40MkII::setBankLeft(bool enabled) { setBooleanLED(0x3C); }

void APC40MkII::setBankRight(bool enabled) { setBooleanLED(0x3D); }

void APC40MkII::setClipDeviceView(bool enabled) { setBooleanLED(0x40); }

void APC40MkII::setDetailView(bool enabled) { setBooleanLED(0x41); }



void APC40MkII::setSceneLaunch(int row, Color color, LEDType type)
{
    if (!_->m_connected) return;
    if (row < 0 || row > 4) return;
    _->sendMsg({
        (unsigned char)((color == Color::Off ? 0x80 : 0x90) | (unsigned char)type),
        (unsigned char)(0x52 + row),
        (unsigned char)color
    });
    // 1  - White half
    // 2  - White
    // 3  - White strong
    // 4  - Pink strong
    // 5  - Red strong
    // 6  - Red half
    // 7  - Red softest
    // 8  - Beige
    // 9  - Orange light
    // 10 - Orange dark
    // 11 - Yellow ugly lightest
    // 12 - Yellow ugly darker
    // 13 - Neon yellow
    // 14 - Neon yellow half
    // 15 - Yellow ugly
    // 16 - Soft Green lightest
    // 17 - Soft Green darker
}

void APC40MkII::setTrackSelector(int trackId)
{
    if (!_->m_connected) return;
    if (trackId > 8) return;
    for (int iTrack = 0; iTrack < 9; iTrack++) {
        _->sendMsg({
            (unsigned char)(0x90 | iTrack),
            (unsigned char)0x33,
            (unsigned char)(iTrack == trackId)
        });
	}
}

void APC40MkII::setTrackActivator(int trackId, bool enabled)
{
    if (!_->m_connected) return;
    if (trackId < 0 || trackId > 7) return;
    unsigned char status = 0x80 | (enabled ? 0x10 : 0x00) | trackId;
    _->sendMsg({
        (unsigned char)status,
        (unsigned char)0x32,
        (unsigned char)0x7F
    });
}

void APC40MkII::setTrackSolo(int trackId, bool enabled)
{
    if (!_->m_connected) return;
    if (trackId < 0 || trackId > 7) return;
    unsigned char status = 0x80 | (enabled ? 0x10 : 0x00) | trackId;
    _->sendMsg({
        (unsigned char)status,
        (unsigned char)0x31,
        (unsigned char)0x7F
    });
}


void APC40MkII::setTrackRecord(int trackId, bool enabled)
{
    if (!_->m_connected) return;
    if (trackId < 0 || trackId > 7) return;
    unsigned char status = 0x80 | (enabled ? 0x10 : 0x00) | trackId;
    _->sendMsg({
        (unsigned char)status,
        (unsigned char)0x30,
        (unsigned char)0x7F
    });
}


void APC40MkII::setTrackAB(int trackId, int state)
{
    if (!_->m_connected) return;
    if (trackId < 0 || trackId > 7) return;
    unsigned char status = 0x80 | (state ? 0x10 : 0x00) | trackId;
    _->sendMsg({
        (unsigned char)status,
        (unsigned char)0x42,
        (unsigned char)0x7F
    });
}


void APC40MkII::setTrackKnob(int knobIndex, unsigned char value)
{
    if (!_->m_connected) return;
    if (knobIndex < 0 || knobIndex > 7) return;
    _->sendMsg({
        (unsigned char)0xB0,
        (unsigned char)(48 + knobIndex),
        (unsigned char)CLAMP(value, 0, 127)
    });
}


void APC40MkII::setClipStop(int trackId, bool enabled)
{
    if (!_->m_connected) return;
    if (trackId < 0 || trackId > 7) return;
    unsigned char status = 0x80 | (enabled ? 0x10 : 0x00) | trackId;
    _->sendMsg({
        (unsigned char)status,
        (unsigned char)0x34,
        (unsigned char)0x7F
    });
}



void APC40MkII::setClip(int x, int y, Color color, LEDType type)
{
    if (!_->m_connected) return;
    if (x < 0 || x > 7 || y < 0 || y > 4) return;
    _->sendMsg({
        (unsigned char)((color == Color::Off ? 0x80 : 0x90) | (unsigned char)type),
        (unsigned char)(x + (y * 8)),
        (unsigned char)(color)
    });
}



void APC40MkII::setDeviceKnob(int knobIndex, unsigned char value)
{
    if (!_->m_connected) return;
    if (knobIndex < 0 || knobIndex > 7) return;
    _->sendMsg({
        (unsigned char)0xB0,
        (unsigned char)(16 + knobIndex),
        (unsigned char)CLAMP(value, 0, 127)
    });
}

