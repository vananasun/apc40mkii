#pragma once
#include <APCAPI.h>
#include "./APCMidiThread.h"
#include "./RtMidi.h"

using namespace APCAPI;


struct APC40MkII::APCCore
{
    APCMidiThread* m_midiThread;
    RtMidiIn* m_midiIn;
    RtMidiOut* m_midiOut;
    ErrorCallback m_errorCallback;
    void* m_userData;
    bool m_connected = false;
    bool m_errored = false;

    static void RtMidiErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData);
    int findInputPortIndex();
    int findOutputPortIndex();
    void sendStartupMessage(Mode mode);
    void sendMsg(MIDIMessage msg);
    void handleKnobsAndFaders(std::vector<unsigned char>& msg, Event* event);
    void handleTrackMessages(std::vector<unsigned char>& msg, Event* event);
    void handleButtons(std::vector<unsigned char>& msg, Event* event);

};
