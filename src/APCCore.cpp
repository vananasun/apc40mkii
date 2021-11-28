#include <RtMidi.h>
#include "APCAPI.h"
#include "./APCCore.h"

using namespace APCAPI;

void APC40MkII::APCCore::RtMidiErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData)
{
    // In the future, a type param switch to create fancy custom error messages
    // would be cool.
    APCCore* me = reinterpret_cast<APCCore*>(userData);
    me->m_errorCallback(errorText, me->m_userData);
    me->m_connected = false;
}


void APC40MkII::APCCore::sendStartupMessage()
{
    unsigned char msg[12] = {
        0xF0,   // MIDI System exclusive message start
        0x47,   // Manufacturers ID Byte
        0x00,   // System Exclusive Device ID
        0x29,   // Product model ID
        0x60,   // Message type identifier
        0x00,   // Number of data bytes to follow (most significant)
        0x04,   // Number of data bytes to follow (least significant)
        0x41,   // Application/Configuration identifier (0x41 is Ableton Live Mode)
        0x00,   // PC application Software version major
        0x00,   // PC application Software version minor
        0x00,   // PC Application Software bug-fix level
        0xF7    // MIDI System exclusive message terminator
    };
    m_midiOut->sendMessage(msg, sizeof(msg));
}


void APC40MkII::APCCore::sendMsg(APCMessage msg)
{
    m_midiOut->sendMessage(reinterpret_cast<unsigned char*>(&msg), sizeof(APCMessage));
}


int APC40MkII::APCCore::findInputPortIndex()
{
    for (unsigned i = 0; i < m_midiIn->getPortCount(); i++) {
        if (m_midiIn->getPortName(i).find(APC40MKII_PORTNAME) != std::string::npos)
            return i;
    }
    return -1; // not found
}


int APC40MkII::APCCore::findOutputPortIndex()
{
    for (unsigned i = 0; i < m_midiOut->getPortCount(); i++) {
        if (m_midiOut->getPortName(i).find(APC40MKII_PORTNAME) != std::string::npos)
            return i;
    }
    return -1; // not found
}

