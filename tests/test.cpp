#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <csignal>
#include <APCAPI.h>

using namespace std;

APCAPI::APC40MkII* g_apc;
bool g_done = false;

void Finish(int ignore) { g_done = true;  } // interrupt handler
void ErrorCallback(const std::string& msg, void *userData);
void ShowHello();
void TestSceneColors();
string GetEventInfo(APCAPI::Event &e);



int main()
{
    (void)signal(SIGINT, Finish); // the quit interrupt handler



    g_apc = new APCAPI::APC40MkII(ErrorCallback, nullptr);
    if (!g_apc->connect()) {
        cout << "Connection failed!" << endl;
        return 0;
    }

    ShowHello();


    while (!g_done) {

        APCAPI::Event e;
        while (g_apc->poll(&e)) {
            if (e.type == APCAPI::EventType::None) continue;

            cout << GetEventInfo(e) << endl;
            
            //cout << "type: " << (int)e.type << " value: " << (int)e.value << " trackId: " << (int)e.trackId << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(30));
    }


    g_apc->disconnect();
    return 0;
}






void ErrorCallback(const std::string& msg, void *userData)
{
    (void)(userData);
    cout << "Error: " << msg << endl;
    g_done = true;
}



void ShowHello()
{
    g_apc->setTrackSelector(7);
    g_apc->setMasterSelector(true);
    g_apc->setTrackActivator(2, true);
    g_apc->setTrackAB(0, APCAPI::TrackAB::Off);
    g_apc->setTrackAB(1, APCAPI::TrackAB::Yellow);
    g_apc->setTrackAB(2, APCAPI::TrackAB::Orange);

    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 8; x++)
            g_apc->setClip(x, y, APCAPI::Color::White, APCAPI::LEDType::Pulsing_1_4);

    APCAPI::Color col = APCAPI::Color::Red;
    g_apc->setClip(1, 0, col);
    g_apc->setClip(1, 1, col);
    g_apc->setClip(1, 2, col);
    g_apc->setClip(1, 3, col);
    g_apc->setClip(1, 4, col);

    g_apc->setClip(2, 2, col);

    g_apc->setClip(3, 0, col);
    g_apc->setClip(3, 1, col);
    g_apc->setClip(3, 2, col);
    g_apc->setClip(3, 3, col);
    g_apc->setClip(3, 4, col);

    g_apc->setClip(5, 0, col);
    g_apc->setClip(5, 1, col);
    g_apc->setClip(5, 2, col);
    g_apc->setClip(5, 4, col);

    g_apc->setClip(7, 0, col);
    g_apc->setClip(7, 2, col);
    g_apc->setClip(7, 3, col);
    g_apc->setClip(7, 4, col);
}



void TestSceneColors()
{
    APCAPI::Color c = (APCAPI::Color)APCAPI::Color::Orange;
    for (int i = 0; i < 5; i++) {
        g_apc->setSceneLaunch(i, c);
    }

    g_apc->setClip(7, 4, c);

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
        case APCAPI::EventType::TrackKnob:
        case APCAPI::EventType::ClipStop:
            str += ", trackId: " + to_string(e.trackId);
            str += ", value: " + to_string(e.value);
            break;

        case APCAPI::EventType::DeviceKnob:
            str += ", knobId: " + to_string(e.knobId);
            str += ", value: " + to_string(e.value);
            break;

        case APCAPI::EventType::SceneLaunch:
            str += ", sceneId: " + to_string(e.sceneId);
            str += ", value: " + to_string(e.value);
            break;

        case APCAPI::EventType::ClipLaunch: {
            const auto [ x, y ] = APCAPI::ClipId2Coords(e.clipId);
            str += ", clipId: " + to_string(e.clipId);
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