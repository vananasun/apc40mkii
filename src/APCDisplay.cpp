#include "./APCCore.h"
#include "./RtMidi.h"
#include <APCAPI.h>

using namespace APCAPI;

void APC40MkII::resetDisplay()
{
    if (!_->m_connected) return;

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 8; x++) {
            setClip(x, y, Color::Off);
        }
    }

    for (int iTrack = 0; iTrack < 8; iTrack++) {
        setClipStop(iTrack, false);
        setTrackActivator(iTrack, false);
        setTrackAB(iTrack, TrackAB::Off);
        setTrackSolo(iTrack, false);
        setTrackRecord(iTrack, false);
        setTrackKnob(iTrack, 0);
    }

    for (int iScene = 0; iScene < 5; iScene++) {
        setSceneLaunch(iScene, Color::Off);
    }

    for (int iKnob = 0; iKnob < 8; iKnob++) {
        setDeviceKnob(iKnob, 0);
    }

    setPan(false);
    setSends(false);
    setUser(false);
    setMetronome(false);
    setPlay(false);
    setRecord(false);
    setSession(false);
    setDetailView(false);
    setClipDeviceView(false);
    setDeviceLeft(false);
    setDeviceRight(false);
    setDeviceOnOff(false);
    setDeviceLock(false);
    setBankLeft(false);
    setBankRight(false);
    setTapTempo(false);
    setTrackSelector(0);
    setMasterSelector(false);

}



// static float S_PATTERN[8 * 5] = { // outward
//     12, 11, 10,  9,  8, 7,  6,  5,
//     13, 30, 29, 28, 27, 26, 25,  4,
//     14, 31, 40, 39, 38, 37, 24,  3,
//     15, 32, 33, 34, 35, 36, 23,  2,
//     16, 17, 18, 19, 20, 21, 22,  1,
// };

// // static const unsigned char S_PATTERNSPIRAL[8 * 5] = { // inward
// //     75, 24,  9, 10, 11, 12, 31, 56,
// //     74, 23,  8,  1,  2, 13, 32, 57,
// //     73, 22,  7,  0,  3, 14, 33, 58,
// //     72, 21,  6,  5,  4, 15, 34, 59,
// //     71, 20, 19, 18, 17, 16, 35, 60,
// // };

// // static float S_PATTERN[8 * 5] = { // snake
// //     32,33,34,35,36,37,38,39,
// //     31,30,29,28,27,26,25,24,
// //     16,17,18,19,20,21,22,23,
// //     15,14,13,12,11,10,9 ,8 ,
// //     0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,
// // };

// /**
//  * Preprocesses table.
//  **/
// static void setupAnimationTable() {
//     for (int iSlot = 0; iSlot < 8 * 5; iSlot++) {
//         S_PATTERN[iSlot] /= 14.0f; // how many steps per color change
//     }
// }

// void APC40MkII::displayPattern(unsigned char step) {
//     return;


//     // if (!m_connected) return;
    
//     // float stepScaled = (float)step / 50; // speed

//     // unsigned char msg[3];
//     // msg[0] = 144; // 144 for on(color), 128 for off(no color)
//     // msg[1] = 0;
    
//     // for (int iSlot = 0; msg[1] < 8 * 5; iSlot++) {
//     //     // 58 = pink, 62 = dark yellow, 13 = bright yellow
//     //     msg[2] = ((int)(S_PATTERN[iSlot] + stepScaled) & 1) ? 58 : 13;
//     //     m_midiout->sendMessage(msg, sizeof(msg));
//     //     msg[1]++;
//     // }

// }




// // static const unsigned char S_COLORMAP[] = {
// //     3, 44, 45, 67,
// //     79, 91, 41, 40,
// //     37, 78, 36, 119,
// //     90, 33, 32, 77,
// //     114, 28, 29, 89,
// //     24, 25, 20, 21,
// //     87, 88, 17, 16,
// //     75, 86, 98, 73,
// //     113, 12, 13, 109,
// //     8, 96, 9, 84,
// //     60, 4, 5, 72,
// //     57, 56, 95, 52,
// //     53, 94, 81, 48,
// //     49, 116, 80, 115,
// //     0, 1, 2, 46,
// //     47, 70, 71, 103,
// //     112, 117, 118, 104,
// //     92, 43, 42, 39,
// //     66, 38, 68, 35,
// //     102, 65, 34, 31,
// //     30, 26, 27, 22,
// //     23, 64, 101, 123,
// //     76, 122, 18, 19,
// //     111, 85, 110, 63,
// //     74, 14, 15, 97,
// //     124, 125, 100, 99,
// //     11, 62, 126, 83,
// //     105, 108, 61, 10,
// //     127, 107, 6, 7,
// //     120, 121, 106, 58,
// //     59, 82, 54, 55,
// //     51, 50, 69, 93,
// // };




// void APC40MkII::displayWelcome(APC40MK2::Color col) {

//     // H
//     this->setClip(0, 0, col);
//     this->setClip(0, 1, col);
//     this->setClip(0, 2, col);
//     this->setClip(0, 3, col);
//     this->setClip(0, 4, col);

//     this->setClip(1, 2, col);

//     this->setClip(2, 0, col);
//     this->setClip(2, 1, col);
//     this->setClip(2, 2, col);
//     this->setClip(2, 3, col);
//     this->setClip(2, 4, col);

//     // I
//     this->setClip(4, 0, col);
//     this->setClip(4, 2, col);
//     this->setClip(4, 3, col);
//     this->setClip(4, 4, col);

//     // !
//     this->setClip(6, 0, col);
//     this->setClip(6, 1, col);
//     this->setClip(6, 2, col);
//     this->setClip(6, 4, col);

//     // knobs
//     for (int num = 0; num < 8; num++) {
//         unsigned char value = (col + (num * 16)) % 127;
//         this->setAssignableKnob(num, value);
//         this->setDeviceControlKnob(num, value);
//     }



// }
