#include "APCAPI.h"
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



void APC40MkII::setPlay(bool enabled)
{
    setBooleanLED(0x5B);
}

void APC40MkII::setRecord(bool enabled)
{
    setBooleanLED(0x5D);
}

void APC40MkII::setSession(bool enabled)
{
    setBooleanLED(0x66);
}

void APC40MkII::setMetronome(bool enabled)
{
    setBooleanLED(0x5A);
}

void APC40MkII::setTapTempo(bool enabled)
{
    setBooleanLED(0x63);
}

void APC40MkII::setPan(bool enabled)
{
    setBooleanLED(0x57);
}

void APC40MkII::setSends(bool enabled)
{
    setBooleanLED(0x58);
}

void APC40MkII::setUser(bool enabled)
{
    setBooleanLED(0x59);
}

void APC40MkII::setSceneLaunch(int row, bool enabled)
{

}

void APC40MkII::setTrackSelector(int trackId)
{
    if (!_->m_connected) return;
    if (trackId > 8) return;
    _->sendMsg({
        (unsigned char)(0x90 | trackId),
        (unsigned char)0x33,
        (unsigned char)0x01
    });
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


void APC40MkII::setClip(int x, int y, Color color)
{
    if (!_->m_connected) return;
    if (x < 0 || x > 7 || y < 0 || y > 4) return;
    _->sendMsg({
        (unsigned char)(color == Color::Off ? 0x80 : 0x90),
        (unsigned char)((32 + x) - (y * 8)),
        (unsigned char)(color)
    });
}

void APC40MkII::setStopAllClips(bool enabled)
{
    setBooleanLED(0x51);
}

void APC40MkII::setDeviceOnOff(bool enabled)
{
    setBooleanLED(0x3E);
}

void APC40MkII::setDeviceLock(bool enabled)
{
    setBooleanLED(0x3F);
}

void APC40MkII::setDeviceLeft(bool enabled)
{
    setBooleanLED(0x3A);
}

void APC40MkII::setDeviceRight(bool enabled)
{
    setBooleanLED(0x3B);
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

void APC40MkII::setBank(bool enabled)
{
    setBooleanLED(0x67);
}

void APC40MkII::setBankLeft(bool enabled)
{
    setBooleanLED(0x3C);
}

void APC40MkII::setBankRight(bool enabled)
{
    setBooleanLED(0x3D);
}

void APC40MkII::setClipDeviceView(bool enabled)
{
    setBooleanLED(0x40);
}

void APC40MkII::setDetailView(bool enabled)
{
    setBooleanLED(0x41);
}








// void APC40MkII::setSolo(int track, bool enabled)
// {
//     if (!m_connected) return;
//     if (track < 0 || track > 7) return;
//     unsigned char status = 128 + track + (enabled ? 16 : 0);

//     std::vector<unsigned char> msg;
//     msg.push_back(status);
//     msg.push_back(49);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);

// }

// void APC40MkII::setRecordArm(int track, bool enabled)
// {
//     if (!m_connected) return;
//     if (track < 0 || track > 7) return;
//     unsigned char status = 128 + track + (enabled ? 16 : 0);

//     std::vector<unsigned char> msg;
//     msg.push_back(status);
//     msg.push_back(48);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);

// }

// /**
//  * @param {int}           track
//  * @param {unsigned char} value - 0 = none, 1 = A, 2 = B
//  */
// void APC40MkII::setCrossfadeAssign(int track, unsigned char value)
// {
//     if (!m_connected) return;
//     if (track < 0 || track > 7) return;
//     if (value > 2) return;
//     unsigned char status = 128 + track + (value ? 16 : 0);

//     std::vector<unsigned char> msg;
//     msg.push_back(status);
//     msg.push_back(66);
//     msg.push_back(value);
//     m_midiout->sendMessage(&msg);
// }



// void APC40MkII::setClipStop(int track, bool enabled)
// {
//     if (!m_connected) return;
//     if (track < 0 || track > 7) return;
//     unsigned char status = 128 + track + (enabled ? 16 : 0);
//     std::vector<unsigned char> msg;
//     msg.push_back(status);
//     msg.push_back(52);
//     msg.push_back(enabled ? 127 : 0);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setClip(int x, int y, APC40MK2::Color color)
// {
//     if (!m_connected) return;
//     if (x < 0 || x > 7 || y < 0 || y > 4) return;
//     unsigned char btnByte = (32 + x) - (y * 8);

//     std::vector<unsigned char> msg;
//     msg.push_back((color ? 144 : 128));
//     msg.push_back(btnByte);
//     msg.push_back(color);
//     m_midiout->sendMessage(&msg);
// }


// void APC40MkII::setAssignableKnob(int num, unsigned char value)
// {
//     if (!m_connected) return;
//     if (num < 0 || num > 7) return;
//     value = CLAMP(value, 0, 127);

//     std::vector<unsigned char> msg;
//     msg.push_back(176);
//     msg.push_back(48 + num);
//     msg.push_back(value);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setDeviceControlKnob(int num, unsigned char value)
// {
//     if (!m_connected) return;
//     if (num < 0 || num > 7) return;
//     value = CLAMP(value, 0, 127);

//     std::vector<unsigned char> msg;
//     msg.push_back(176);
//     msg.push_back(16 + num);
//     msg.push_back(value);
//     m_midiout->sendMessage(&msg);
// }







// void APC40MkII::setPlay(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(91);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setRecord(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(93);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setSession(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(102);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setPan(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(87);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setSends(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(88);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setUser(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(89);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }

// void APC40MkII::setMetronome(bool enabled)
// {
//     if (!m_connected) return;
//     std::vector<unsigned char> msg;
//     msg.push_back((enabled ? 144 : 128));
//     msg.push_back(90);
//     msg.push_back(127);
//     m_midiout->sendMessage(&msg);
// }




