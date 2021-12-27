#include "./APCMidiThread.h"
#include "./APCCore.h"
#include "./RtMidi.h"
#include <APCAPI.h>

using namespace APCAPI;



void APCMidiThread::spawn(RtMidiOut *midiOut)
{
    m_midiOut = midiOut;
    m_messageQueue = std::deque<MIDIMessage>();
    
    // std::deque<MIDIMessage> empty;
    // std::swap(m_messageQueue, empty);
    m_threadRunning = true;
    m_thread = std::thread( [this] { this->threadProc(); } );
}


void APCMidiThread::close()
{
    m_threadRunning = false;
    m_cond.notify_one();
    if (m_thread.joinable()) m_thread.join();
}


void APCMidiThread::threadProc()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    do {
        m_cond.wait(lock, [this] { return m_messageQueue.size(); } );

        while (m_messageQueue.size() > 0) {
            MIDIMessage msg = m_messageQueue.front();
            m_messageQueue.pop_front();
            lock.unlock();
            m_midiOut->sendMessage(reinterpret_cast<unsigned char*>(&msg), sizeof(MIDIMessage));
            lock.lock();
        }

    } while (m_threadRunning);
}


void APCMidiThread::sendMsg(MIDIMessage msg)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_messageQueue.push_back(msg);
    lock.unlock();
    m_cond.notify_one();
}

