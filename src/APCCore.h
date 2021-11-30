#pragma once
#include "./RtMidi.h"

using namespace APCAPI;

#define APC40MKII_PORTNAME "APC40 mkII"

struct APCMessage
{
    unsigned char channel;
    unsigned char note;
    unsigned char value;
};

struct APC40MkII::APCCore
{
    RtMidiIn* m_midiIn;
    RtMidiOut* m_midiOut;
    ErrorCallback m_errorCallback;
    void* m_userData;
    bool m_connected = false;
    bool m_errored = false;

    static void RtMidiErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData);
    int findInputPortIndex();
    int findOutputPortIndex();
    void sendStartupMessage();
    void sendMsg(APCMessage msg); // @FIXME: may be better to get rid of this and APCMessage and use a byte vector
    void handleKnobsAndFaders(std::vector<unsigned char>& msg, Event* event);
    void handleTrackMessages(std::vector<unsigned char>& msg, Event* event);
    void handleButtons(std::vector<unsigned char>& msg, Event* event);
    void resetDisplayImp();

};
