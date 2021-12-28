#include "./APCMidiThread.h"
#include "./APCCore.h"
#include "./RtMidi.h"
#include <APCAPI.h>

using namespace APCAPI;


/**
 *  \brief Starts MIDI output thread.
 * 
 *  \param midiOut
 */
void APCMidiThread::spawn(RtMidiOut *midiOut)
{
    m_midiOut = midiOut;
    m_messageQueue = std::deque<MIDIMessage>();
    
    m_threadRunning = true;
    m_thread = std::thread( [this] { this->threadProc(); } );
}


/**
 *  \brief Stops MIDI output thread.
 */
void APCMidiThread::close()
{
    m_threadRunning = false;
    m_cond.notify_one();
    if (m_thread.joinable()) m_thread.join();
}


/**
 *  \brief This message pump safely pops messages off the queue and sends them.
 */
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


/**
 *  \brief  Pushes a 3 byte MIDI message to the queue.
 *          The reason we use a message queue is because sending RtMidi messages
 *          is a blocking operation.
 * 
 *  \param msg
 */
void APCMidiThread::sendMsg(MIDIMessage msg)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_messageQueue.push_back(msg);
    lock.unlock();
    m_cond.notify_one();
}

