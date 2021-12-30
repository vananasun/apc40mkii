//
// scons c-binding=1 && build\debug\test-c-binding
//

#include <APCAPI_C.h>
#include <stdio.h>
#include <signal.h>

// SleepMs function stuff
void SleepMs(int ms);
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif



bool g_done = false;
void Finish(int ignore) { g_done = true; } // interrupt handler
void ErrorCallback(const char* msg, void* userData);



int main(int argc, char** argv)
{
    (void)signal(SIGINT, Finish); // the quit interrupt handler
    
    APCDev* apc = APCDev_Create(ErrorCallback, 0);
    if (!APCDev_Connect(apc, APC_MODE_ABLETON)) return 0;

    while (!g_done) {
        APCEvent event;
        while (APCDev_Poll(apc, &event)) {
            puts(APC_GetEventTypeString(event.type));
        }
        SleepMs(30);
    }


    APCDev_Destroy(apc);
    return 0;
}




void ErrorCallback(const char* msg, void* userData)
{
    puts(msg);
}



void SleepMs(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}

