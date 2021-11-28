#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <APCAPI.h>


APCAPI::APC40MkII* g_apc;
bool g_done = false;

void finish(int ignore) // interrupt handler
{
    g_done = true; 
}


void test_colors() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 8; x++) {
            g_apc->setClip(x, y, APCAPI::Color::Magenta);
        }
    }
}

void error_callback(const std::string& msg, void *userData)
{
    (void)(userData);
    std::cout << msg << std::endl;
    g_done = true;
}




int main()
{
    g_apc = new APCAPI::APC40MkII(error_callback, nullptr);
    if (!g_apc->connect()) {
        std::cout << "Connection failed!" << std::endl;
        return 0;
    }

    (void)signal(SIGINT, finish); // the quit interrupt handler


    while (!g_done) {

        test_colors();
        g_apc->setTrackSelector(7);

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
