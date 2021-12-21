#include "APCAPI.h"
#include "./APCCore.h"
#include "./RtMidi.h"

using namespace APCAPI;


void APC40MkII::APCCore::spawnMidiThread()
{
    m_midiThread = std::thread( [this] { this->midiThreadProc(); } );
    std::queue<APCMessage> empty;
    std::swap(m_messageQueue, empty);
}


void APC40MkII::APCCore::midiThreadProc()
{
    m_midiThreadRunning = true;
    do {
        while (m_messageQueue.size() > 0) {
            APCMessage msg = m_messageQueue.front();
            m_midiOut->sendMessage(reinterpret_cast<unsigned char*>(&msg), sizeof(APCMessage));
            m_messageQueue.pop();
        }

        #define THREAD_UPDATE_INTERVAL_MS 4
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_UPDATE_INTERVAL_MS));
    } while (m_midiThreadRunning);
}