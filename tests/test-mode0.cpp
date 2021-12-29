#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <csignal>
#include <APCAPI.h>

using namespace std;

bool g_done = false;

void Finish(int ignore) { g_done = true;  } // interrupt handler
void ErrorCallback(const std::string &msg, void *userData);
void ShowHello(APCAPI::APC40MkII &apc);
string GetEventInfo(APCAPI::Event &e);



int main()
{
    (void)signal(SIGINT, Finish); // the quit interrupt handler



    APCAPI::APC40MkII apc(ErrorCallback, nullptr);
    if (!apc.connect(APCAPI::Mode::Generic)) return 0;

    ShowHello(apc);


    while (!g_done) {

        APCAPI::Event e;
        while (apc.poll(&e)) {
            cout << GetEventInfo(e) << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(30));
    }


    apc.disconnect();
    return 0;
}






void ErrorCallback(const std::string &msg, void *userData)
{
    (void)(userData);
    cout << "Error: " << msg << endl;
    g_done = true;
}



void ShowHello(APCAPI::APC40MkII &apc)
{
    apc.setTrackSelector(7);
    apc.setMasterSelector(true);
    apc.setTrackActivator(2, true);
    apc.setTrackAB(0, APCAPI::TrackAB::Off);
    apc.setTrackAB(1, APCAPI::TrackAB::Yellow);
    apc.setTrackAB(2, APCAPI::TrackAB::Orange);
    apc.setTrackKnobRingType(0, APCAPI::RingType::Off);
    apc.setTrackKnobRingType(1, APCAPI::RingType::Pan);
    apc.setTrackKnobRingType(2, APCAPI::RingType::Single);
    apc.setTrackKnobRingType(3, APCAPI::RingType::Volume);
    apc.setDeviceKnobRingType(0, APCAPI::RingType::Off);
    apc.setDeviceKnobRingType(1, APCAPI::RingType::Pan);
    apc.setDeviceKnobRingType(2, APCAPI::RingType::Single);
    apc.setDeviceKnobRingType(3, APCAPI::RingType::Volume);
    apc.setClipStop(0, APCAPI::ClipStopLED::Off);
    apc.setClipStop(1, APCAPI::ClipStopLED::On);
    apc.setClipStop(2, APCAPI::ClipStopLED::Blink);

    // Gradient
    for (int x = 0; x < 9; x++) {
        APCAPI::RGB rgb = { (unsigned char)(255.0f / 8.0f * x), 0, 255 };
        APCAPI::Color col = APCAPI::GetNearestColor(rgb);

        if (x == 8)
            for (int y = 0; y < 5; y++)
                apc.setSceneLaunch(y, col);
        else
            for (int y = 0; y < 5; y++)
                apc.setClip(x, y, col);
    }

}




string GetEventInfo(APCAPI::Event &e)
{
    string str = "type: " + string(APCAPI::GetEventTypeString(e.type));

    switch (e.type) {

        case APCAPI::EventType::TrackAB:
        case APCAPI::EventType::TrackActivator:
        case APCAPI::EventType::TrackSolo:
        case APCAPI::EventType::TrackFader:
        case APCAPI::EventType::TrackRecord:
        case APCAPI::EventType::TrackSelector:
        case APCAPI::EventType::ClipStop:
        case APCAPI::EventType::TrackKnob:
            str += ", track: " + to_string(e.trackId);
            str += ", value: " + to_string(e.value);
            break;
        
        /* Mode 0 banked stuff */
        case APCAPI::EventType::DeviceKnob:
            str += ", page: " + to_string(e.pageId);
            str += ", knob: " + to_string(e.knobId);
            str += ", value: " + to_string(e.value);
            break;
        
        case APCAPI::EventType::DeviceLeft:
        case APCAPI::EventType::DeviceRight:
        case APCAPI::EventType::BankLeft:
        case APCAPI::EventType::BankRight:
        case APCAPI::EventType::DeviceOnOff:
        case APCAPI::EventType::DeviceLock:
        case APCAPI::EventType::ClipDeviceView:
        case APCAPI::EventType::DetailView:
            str += ", page: " + to_string(e.pageId);
            str += ", pressed: " + to_string(e.pressed);
            break;

        case APCAPI::EventType::SceneLaunch:
            str += ", scene: " + to_string(e.sceneId);
            str += ", value: " + to_string(e.value);
            break;

        case APCAPI::EventType::ClipLaunch: {
            const auto [ x, y ] = APCAPI::ClipId2Coords(e.clipId);
            str += ", clip: " + to_string(e.clipId);
            str += " (x=" + to_string(x) + ",y=" + to_string(y);
            str += "), value: " + to_string(e.value);
        }   break;

        case APCAPI::EventType::Nudge:
        case APCAPI::EventType::Tempo:
        case APCAPI::EventType::CueLevel:
            str += ", direction: " + to_string(e.direction);
            break;
        
        default:
            str += ", value: " + to_string(e.value);
            break;
        
    }

    return str;
}