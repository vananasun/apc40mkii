#include "./APCCore.h"
#include <APCAPI.h>
#include <vector>
#include <iostream>

using namespace APCAPI;

/**
 *  \param msg MIDI message byte vector
 *  \returns Whether the given MIDI message was a Note-On or Note-Off message.
 */
static inline bool isOnMsg(std::vector<unsigned char>& msg)
{
    return ((msg[0] >> 4) & 0x01); // 0x9x becomes true, 0x8x becomes false
}

/**
 *  \param msg MIDI message byte vector
 *  \returns Whether the given MIDI message was a controller change message.
 */
static inline bool isControllerMsg(std::vector<unsigned char>& msg)
{
    return ((msg[0] >> 5) & 0x01); // 0xBx becomes true
}

/**
 *  \brief Used for banked device controls and track IDs.
 *  \param msg MIDI message byte vector
 *  \returns MIDI channel of message
 */
static inline unsigned char getChannel(std::vector<unsigned char>& msg)
{
    return (msg[0] & 0x0F);
}



void APC40MkII::APCCore::handleValueControls(std::vector<unsigned char>& msg, Event* event)
{
    if (msg[1] == 0x07) {
        event->type = EventType::TrackFader;
        event->trackId = getChannel(msg); // track index
    } else if (msg[1] == 0x0D) {
        event->type = EventType::Tempo;
        event->direction = (msg[2] == 1) ? 1 : -1;
        return;
    } else if (msg[1] == 0x0E) {
        event->type = EventType::MasterFader;
    } else if (msg[1] == 0x0F) {
        event->type = EventType::Crossfader;
    } else if (msg[1] >= 0x10 && msg[1] <= 0x17) {
        event->type = EventType::DeviceKnob;
        event->knobId = msg[1] - 0x10; // physical knob index
        event->pageId = getChannel(msg); // for mode 0 banking
    } else if (msg[1] == 0x2F) {
        event->type = EventType::CueLevel;
        event->direction = (msg[2] <= 63) ? msg[2] : msg[2] + 0x80;
        return;
    } else if (msg[1] >= 0x30 && msg[1] <= 0x37) {
        event->type = EventType::TrackKnob;
        event->knobId = msg[1] - 0x30; // knob index (same as trackId)
    }
    event->value = msg[2];  
}


void APC40MkII::APCCore::handleTrackControls(std::vector<unsigned char>& msg, Event* event)
{
    unsigned char chan = getChannel(msg);

    if        (msg[1] == 0x30) { event->type = EventType::TrackRecord;    event->trackId = chan;
    } else if (msg[1] == 0x31) { event->type = EventType::TrackSolo;      event->trackId = chan;
    } else if (msg[1] == 0x32) { event->type = EventType::TrackActivator; event->trackId = chan;
    } else if (msg[1] == 0x33) { event->type = EventType::TrackSelector;  event->trackId = chan;
    } else if (msg[1] == 0x34) { event->type = EventType::ClipStop;       event->trackId = chan;
    } else if (msg[1] == 0x3A) { event->type = EventType::DeviceLeft;     event->pageId  = chan;
    } else if (msg[1] == 0x3B) { event->type = EventType::DeviceRight;    event->pageId  = chan;
    } else if (msg[1] == 0x3C) { event->type = EventType::BankLeft;       event->pageId  = chan;
    } else if (msg[1] == 0x3D) { event->type = EventType::BankRight;      event->pageId  = chan;
    } else if (msg[1] == 0x3E) { event->type = EventType::DeviceOnOff;    event->pageId  = chan;
    } else if (msg[1] == 0x3F) { event->type = EventType::DeviceLock;     event->pageId  = chan;
    } else if (msg[1] == 0x40) { event->type = EventType::ClipDeviceView; event->pageId  = chan;
    } else if (msg[1] == 0x41) { event->type = EventType::DetailView;     event->pageId  = chan;
    } else if (msg[1] == 0x42) { event->type = EventType::TrackAB;        event->trackId = chan;
    }
    
    event->pressed = isOnMsg(msg);
}


void APC40MkII::APCCore::handleButtons(std::vector<unsigned char>& msg, Event* event)
{
    #define handleToggleMsg(cc, event_type) handleToggleMsgCode((cc), (event_type), {})
    #define handleToggleMsgCode(cc, event_type, code)/**/\
        if (msg[1] == cc) {\
            event->type = event_type;\
            event->pressed = isOnMsg(msg);\
            code\
            return;\
        }

    handleToggleMsg(0x50, EventType::MasterSelector);
    handleToggleMsg(0x51, EventType::StopAllClips);
    handleToggleMsg(0x57, EventType::Pan);
    handleToggleMsg(0x58, EventType::Sends);
    handleToggleMsg(0x59, EventType::User);
    handleToggleMsg(0x5A, EventType::Metronome);
    handleToggleMsg(0x5B, EventType::PlayStop);
    handleToggleMsg(0x5D, EventType::Record);
    handleToggleMsg(0x5E, EventType::BankSelectUp);
    handleToggleMsg(0x5F, EventType::BankSelectDown);
    handleToggleMsg(0x60, EventType::BankSelectRight);
    handleToggleMsg(0x61, EventType::BankSelectLeft);
    handleToggleMsg(0x62, EventType::Shift);
    handleToggleMsg(0x63, EventType::TapTempo);
    handleToggleMsg(0x66, EventType::Session);
    handleToggleMsg(0x67, EventType::Bank);
    handleToggleMsgCode(0x64, EventType::Nudge, { event->direction = -1; });
    handleToggleMsgCode(0x65, EventType::Nudge, { event->direction = 1; });

    if (msg[1] >= 0x00 && msg[1] <= 0x27) {
        event->type = EventType::ClipLaunch;
        event->clipId = msg[1];
        event->pressed = isOnMsg(msg);
    } else if (msg[1] >= 0x52 && msg[1] <= 0x56) {
        event->type = EventType::SceneLaunch;
        event->sceneId = msg[1] - 0x52;
        event->pressed = isOnMsg(msg);
    } else if (msg[1] == 0x40) {
        event->type = EventType::Footswitch;
        event->pressed = msg[2] & 1; // said to be 0x7F when pressed, 0x00 when released
    }

}



bool APC40MkII::poll(Event* event)
{
    if (!_->m_connected) return false;

    std::vector<unsigned char> msg;
    _->m_midiIn->getMessage(&msg);
    if (msg.size() < 3) return false;

    memset(event, 0, sizeof(Event));
    if (isControllerMsg(msg)) {
        _->handleValueControls(msg, event);
    } else if (msg[1] >= 0x30 && msg[1] <= 0x49) {
        _->handleTrackControls(msg, event);
    } else {
        _->handleButtons(msg, event);
    }

    return true;
}
