#include "APCAPI.h"
#include "./APCCore.h"
#include <vector>
#ifdef DEBUG
#include <iostream>
#endif

using namespace APCAPI;

/**
 *  \param msg MIDI message byte vector
 *  \returns Whether the given MIDI message was a Note-On or Note-Off message.
 */
static bool isOnMsg(std::vector<unsigned char>& msg)
{
    return ((msg[0] & 0x90) == 0x90);
}



void APC40MkII::APCCore::handleKnobsAndFaders(std::vector<unsigned char>& msg, Event* event)
{
    if (msg[1] == 0x07) {
        event->type = EventType::TrackFader;
        event->trackId = msg[0] & 0x0F; // track index
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
        event->trackId = msg[1] - 0x10; // physical knob index
    } else if (msg[1] == 0x2F) {
        event->type = EventType::CueLevel;
        event->direction = msg[2];
        return;
    } else if (msg[1] >= 0x30 && msg[1] <= 0x37) {
        event->type = EventType::AssignableKnob;
        event->trackId = msg[1] - 0x30; // knob index
    }
    event->value = msg[2];  
}


void APC40MkII::APCCore::handleTrackMessages(std::vector<unsigned char>& msg, Event* event)
{
    event->trackId = msg[0] & 0x0F;

    if        (msg[1] == 0x30) { event->type = EventType::RecordArm;
    } else if (msg[1] == 0x31) { event->type = EventType::Solo;
    } else if (msg[1] == 0x32) { event->type = EventType::TrackActivator;
    } else if (msg[1] == 0x33) { event->type = EventType::TrackSelector;
    } else if (msg[1] == 0x34) { event->type = EventType::ClipStop;
    } else if (msg[1] == 0x3A) { event->type = EventType::DeviceLeft;
    } else if (msg[1] == 0x3B) { event->type = EventType::DeviceRight;
    } else if (msg[1] == 0x3C) { event->type = EventType::BankLeft;
    } else if (msg[1] == 0x3D) { event->type = EventType::BankRight;
    } else if (msg[1] == 0x3E) { event->type = EventType::DeviceOnOff;
    } else if (msg[1] == 0x3F) { event->type = EventType::DeviceLock;
    } else if (msg[1] == 0x40) { event->type = EventType::ClipDeviceView;
    } else if (msg[1] == 0x41) { event->type = EventType::DetailView;
    } else if (msg[1] == 0x42) {
        event->type = EventType::CrossfadeAssign;
        event->value = msg[2]; // 0 = none, 1 = A, 2 = B
        return;
    }
    
    event->value = static_cast<unsigned char>(isOnMsg(msg));
}


void APC40MkII::APCCore::handleButtons(std::vector<unsigned char>& msg, Event* event)
{
    #define handleToggleMsg(cc, event_type) handleToggleMsgCode((cc), (event_type), {})
    #define handleToggleMsgCode(cc, event_type, code)/**/\
        if (msg[1] == cc) {\
            event->type = event_type;\
            event->value = isOnMsg(msg);\
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

    event->value = isOnMsg(msg);
    if (msg[1] >= 0x00 && msg[1] <= 0x27) {
        event->type = EventType::ClipLaunch;
        event->clipId = msg[1];
    } else if (msg[1] >= 0x52 && msg[1] <= 0x56) {
        event->type = EventType::SceneLaunch;
        event->sceneId = msg[1] - 0x52;
    }

}



bool APC40MkII::poll(Event* event)
{
    if (!_->m_connected) return false;

    std::vector<unsigned char> msg;
    _->m_midiIn->getMessage(&msg);
    if (msg.size() < 3) return false;
    
#ifdef DEBUG
    // for (int i = 0; i < msg.size(); i++)
    //     std::cout << (int)msg[i] << " ";
    // std::cout << std::endl;
#endif

    memset(event, 0, sizeof(Event));
    if ((msg[0] & 0xF0) == 0xB0) {
        _->handleKnobsAndFaders(msg, event);
    } else if (msg[1] >= 0x30 && msg[1] <= 0x49) {
        _->handleTrackMessages(msg, event);
    } else {
        _->handleButtons(msg, event);
    }

    return true;
}
