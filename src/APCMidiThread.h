#pragma once
#include "./RtMidi.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


struct MIDIMessage
{
    unsigned char channel;
    unsigned char note;
    unsigned char value;
};


class APCMidiThread
{
private:
    std::deque<MIDIMessage> m_messageQueue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::thread m_thread;
    bool m_threadRunning = false;
    RtMidiOut* m_midiOut;

public:
    void spawn(RtMidiOut* midiOut);
    void close();
    void threadProc();
    void sendMsg(MIDIMessage msg);

};

