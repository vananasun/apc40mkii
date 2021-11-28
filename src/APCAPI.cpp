#include "APCAPI.h"
#include "./APCCore.h"
#include "./RtMidi.h"
#include <stdlib.h>

using namespace APCAPI;


APC40MkII::APC40MkII(ErrorCallback errorCallback, void* userData)
{
    _ = (APCCore*)calloc(1, sizeof(APCCore));
    _->m_midiIn = new RtMidiIn();
    _->m_midiOut = new RtMidiOut();
    _->m_midiIn->setErrorCallback(APCCore::RtMidiErrorCallback, _);
    _->m_midiOut->setErrorCallback(APCCore::RtMidiErrorCallback, _);
    _->m_errorCallback = errorCallback;
    _->m_userData = userData;
}


APC40MkII::~APC40MkII()
{
    disconnect();
    free(_);
    delete _->m_midiIn;
    delete _->m_midiOut;
}



bool APC40MkII::connect()
{
    if (_->m_connected) return false;

    int portIn = _->findInputPortIndex();
    int portOut = _->findOutputPortIndex();
    if (portIn == -1 || portOut == -1) {
        _->m_errorCallback("The APC40 MkII does not seem to be on and connected.", _->m_userData);
        return false;
    }

    try {
        _->m_midiIn->openPort(portIn);
        _->m_midiIn->ignoreTypes(true, true, true);
        _->m_midiOut->openPort(portOut);
    } catch (RtMidiError& error) {
        _->m_errorCallback("The APC40 MkII is in use by another application.", _->m_userData);
        return false;
    }

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


