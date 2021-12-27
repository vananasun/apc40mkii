#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <APCAPI.h>


APCAPI::APC40MkII* g_apc;
bool g_done = false;

// interrupt handler
void finish(int ignore) { g_done = true;  }

void error_callback(const std::string& msg, void *userData)
{
    (void)(userData);
    std::cout << "Error: " << msg << std::endl;
    g_done = true;
}



void show_hello()
{
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 8; x++) {
            g_apc->setClip(x, y, APCAPI::Color::White, APCAPI::LEDType::Pulsing_1_4);
        }
    }

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

void test_scene_colors()
{
    APCAPI::Color c = (APCAPI::Color)APCAPI::Color::Orange;
    for (int i = 0; i < 5; i++) {
        g_apc->setSceneLaunch(i, c);
    }

    g_apc->setClip(7, 4, c);

}




int main()
{
    g_apc = new APCAPI::APC40MkII(error_callback, nullptr);
    if (!g_apc->connect()) {
        std::cout << "Connection failed!" << std::endl;
        return 0;
    }

    (void)signal(SIGINT, finish); // the quit interrupt handler

    show_hello();
    g_apc->setTrackSelector(7);
    g_apc->setTrackActivator(2, true);

    while (!g_done) {

        //test_scene_colors();

        // Read events
        APCAPI::Event e;
        while (g_apc->poll(&e)) {
            if (e.type == APCAPI::EventType::None) continue;
            std::cout << "type: " << (int)e.type << " value: " << (int)e.value << " trackId: " << (int)e.trackId << std::endl;
        }

        _sleep(30);
    }

    g_apc->disconnect();

    return 0;
}
