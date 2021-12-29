#include "./APCCore.h"
#include "./RtMidi.h"
#include <APCAPI.h>
#include <cmath>

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
        setClipStop(iTrack, ClipStopLED::Off);
        setTrackActivator(iTrack, false);
        setTrackAB(iTrack, DualColor::Off);
        setTrackSolo(iTrack, false);
        setTrackRecord(iTrack, false);
        setTrackKnob(iTrack, 0);
        setTrackKnobRingType(iTrack, RingType::Off);
        setTrackSelector(iTrack, false);
    }

    for (int iScene = 0; iScene < 5; iScene++) {
        setSceneLaunch(iScene, Color::Off);
    }

    for (int iPage = 0; iPage < 9; iPage++) {
        for (int iKnob = 0; iKnob < 8; iKnob++) {
            setDeviceKnob(iKnob, 0, iPage);
            setDeviceKnobRingType(iKnob, RingType::Off, iPage);
        }
        setDeviceLeft(false, iPage);
        setDeviceRight(false, iPage);
        setDeviceOnOff(false, iPage);
        setDeviceLock(false, iPage);
        setDetailView(false, iPage);
        setClipDeviceView(false, iPage);
        setBankLeft(false, iPage);
        setBankRight(false, iPage);
    }

    setPan(false);
    setSends(false);
    setUser(false);
    setMetronome(false);
    setPlay(false);
    setRecord(false);
    setSession(false);
    setTapTempo(false);
    setMasterSelector(false);

}



/*******************************************************************************
 * 
 * Color utils
 * 
 ******************************************************************************/

static inline float calcColorDistance(RGB one, RGB two)
{
    int rmean = (one.r + two.r) / 2;
    int r = one.r - two.r;
    int g = one.g - two.g;
    int b = one.b - two.b;
    return sqrtf(((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8);
}

inline static const RGB S_COLORS[] = {
    {   0,  0,  0 },{  30, 30, 30 },{ 127,127,127 },{ 255,255,255 },{ 255, 76, 76 },{ 255,  0,  0 },{  89,  0,  0 },{  25,  0,  0 },
    { 255,189,108 },{ 255, 84,  0 },{  89, 29,  0 },{  39, 27,  0 },{ 255,255, 76 },{ 255,255,  0 },{  89, 89,  0 },{  25, 25,  0 },
    { 136,255, 76 },{  84,255,  0 },{  29, 89,  0 },{  20, 43,  0 },{  76,255, 76 },{   0,255,  0 },{   0, 89,  0 },{   0, 25,  0 },
    {  76,255, 94 },{   0,255, 25 },{   0, 89, 13 },{   0, 25,  2 },{  76,255,136 },{   0,255, 85 },{   0, 89, 29 },{   0, 31, 18 },
    {  76,255,183 },{   0,255,153 },{   0, 89, 53 },{   0, 25, 18 },{  76,195,255 },{   0,169,255 },{   0, 65, 82 },{   0, 16, 25 },
    {  76,136,255 },{   0, 85,255 },{   0, 29, 89 },{   0,  8, 25 },{  76, 76,255 },{   0,  0,255 },{   0,  0, 89 },{   0,  0, 25 },
    { 135, 76,255 },{  84,  0,255 },{  25,  0,100 },{  15,  0, 48 },{ 255, 76,255 },{ 255,  0,255 },{  89,  0, 89 },{  25,  0, 25 },
    { 255, 76,135 },{ 255,  0, 84 },{  89,  0, 29 },{  34,  0, 19 },{ 255, 21,  0 },{ 153, 53,  0 },{ 121, 81,  0 },{  67,100,  0 },
    {   3, 57,  0 },{   0, 87, 53 },{   0, 84,127 },{   0,  0,255 },{   0, 69, 79 },{  37,  0,204 },{ 127,127,127 },{  32, 32, 32 },
    { 255,  0,  0 },{ 189,255, 45 },{ 175,237,  6 },{ 100,255,  9 },{  16,139,  0 },{   0,255,135 },{   0,169,255 },{   0, 42,255 },
    {  63,  0,255 },{ 122,  0,255 },{ 178, 26,125 },{  64, 33,  0 },{ 255, 74,  0 },{ 136,225,  6 },{ 114,255, 21 },{   0,255,  0 },
    {  59,255, 38 },{  89,255,113 },{  56,255,204 },{  91,138,255 },{  49, 81,198 },{ 135,127,233 },{ 211, 29,255 },{ 255,  0, 93 },
    { 255,127,  0 },{ 185,176,  0 },{ 144,255,  0 },{ 131, 93,  7 },{  57, 43,  0 },{  20, 76, 16 },{  13, 80, 56 },{  21, 21, 42 },
    {  22, 32, 90 },{ 105, 60, 28 },{ 168,  0, 10 },{ 222, 81, 61 },{ 216,106, 28 },{ 255,225, 38 },{ 158,225, 47 },{ 103,181, 15 },
    {  30, 30, 48 },{ 220,255,107 },{ 128,255,189 },{ 154,153,255 },{ 142,102,255 },{  64, 64, 64 },{ 117,117,117 },{ 224,255,255 },
    { 160,  0,  0 },{  53,  0,  0 },{  26,208,  0 },{   7, 66,  0 },{ 185,176,  0 },{  63, 49,  0 },{ 179, 95,  0 },{  75, 21,  2 }
};

const RGB APCAPI::Color2RGB(Color color)
{
    return S_COLORS[(int)color];
}

Color APCAPI::GetNearestColor(RGB col)
{
    if (col.r + col.g + col.b < 1) return (Color)0;

    float minDist = 10000.0f;
    int closestColorId = 0;

    for (int iColor = 0; iColor < 128; iColor++) {
        float dist = calcColorDistance(Color2RGB(static_cast<Color>(iColor)), col);
        if (dist < minDist) {
            minDist = dist;
            closestColorId = iColor;
        }
    }

    return (Color)closestColorId;
}

