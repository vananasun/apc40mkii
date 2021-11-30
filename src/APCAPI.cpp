#include "APCAPI.h"
#include "./APCCore.h"
#include "./RtMidi.h"
#include <stdlib.h>

using namespace APCAPI;



APC40MkII::APC40MkII(ErrorCallback errorCallback, void* userData)
{
    _ = (APCCore*)calloc(1, sizeof(APCCore));
    _->m_errorCallback = errorCallback;
    _->m_userData = userData;

    // @TODO: Figure out a way to gracefully swallow any std::cerr output from
    //        these constructors. Error callbacks do not work.
    //        See: https://github.com/thestk/rtmidi/issues/266
    _->m_midiIn = new RtMidiIn();
    _->m_midiOut = new RtMidiOut();
    if (0 == _->m_midiIn->getPortCount()) {
        _->m_errored = true;
        _->m_errorCallback("The APC40 mkII does not seem to be on and connected.", _->m_userData);
    }

}


APC40MkII::~APC40MkII()
{
    disconnect();
    delete _->m_midiIn;
    delete _->m_midiOut;
    free(_);
}



bool APC40MkII::connect()
{
    if (_->m_connected) return false;
    if (_->m_errored) { _->m_connected = false; return false; }

    int portIn = _->findInputPortIndex();
    int portOut = _->findOutputPortIndex();
    if (portIn == -1 || portOut == -1) {
        _->m_errorCallback("The APC40 mkII does not seem to be on and connected.", _->m_userData);
        return false;
    }

    try {
        _->m_midiIn->openPort(portIn);
        _->m_midiIn->ignoreTypes(true, true, true);
        _->m_midiOut->openPort(portOut);
    } catch (RtMidiError& error) {
        _->m_errorCallback("The APC40 mkII is in use by another application.", _->m_userData);
        return false;
    }
    
    _->m_midiIn->setErrorCallback(APCCore::RtMidiErrorCallback, this);
    _->m_midiOut->setErrorCallback(APCCore::RtMidiErrorCallback, this);

    _->sendStartupMessage();
    _->m_connected = true;
    resetDisplay();
    return true;
}


void APC40MkII::disconnect()
{
    if (!_->m_connected) return;
    resetDisplay();
    _->m_midiIn->closePort();
    _->m_midiOut->closePort();
    _->m_connected = false;
}



/** \brief Our assumption is that this gets called only when sending a MIDI message fails. */
void APC40MkII::APCCore::RtMidiErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData)
{
    // In the future, a type param switch to create fancy custom error messages
    // would be cool.
    APC40MkII* apc = reinterpret_cast<APC40MkII*>(userData);
    apc->disconnect();
    apc->_->m_errorCallback("The APC40 mkII has disconnected.", apc->_->m_userData);
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
