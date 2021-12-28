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
        setClipStop(iTrack, ClipStopLED::Off);
        setTrackActivator(iTrack, false);
        setTrackAB(iTrack, TrackAB::Off);
        setTrackSolo(iTrack, false);
        setTrackRecord(iTrack, false);
        setTrackKnob(iTrack, 0);
        setTrackKnobRingType(iTrack, RingType::Off);
    }

    for (int iScene = 0; iScene < 5; iScene++) {
        setSceneLaunch(iScene, Color::Off);
    }

    for (int iKnob = 0; iKnob < 8; iKnob++) {
        setDeviceKnob(iKnob, 0);
        setDeviceKnobRingType(iKnob, RingType::Off);
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
