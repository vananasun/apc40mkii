#ifdef APCAPI_EXPORT_C
#include <APCAPI_C.h>
#include <APCAPI.h>
#include <stdlib.h>

using namespace APCAPI;


typedef struct {
    APCErrorCallback originalCallback;
    void* originalUserData;
} ErrorCallbackData;

static void ErrorCallbackWrapper(const std::string& msg, void* userData)
{
    ErrorCallbackData* newUserData = (ErrorCallbackData*)userData;
    newUserData->originalCallback(msg.c_str(), newUserData->originalUserData);
}


APCDev* APCDev_Create(APCErrorCallback callback, void* originalUserData) {
    ErrorCallbackData* newUserData = (ErrorCallbackData*)malloc(sizeof(ErrorCallbackData));
    newUserData->originalCallback = callback;
    newUserData->originalUserData = originalUserData;
    return reinterpret_cast<APCDev*>(new APC40MkII(ErrorCallbackWrapper, newUserData));
}

void APCDev_Destroy(APCDev* me) {
    delete reinterpret_cast<APC40MkII*>(me);
}

bool APCDev_Connect(APCDev* me,  APCMode mode) {
    return reinterpret_cast<APC40MkII*>(me)->connect((Mode)mode);
}

void APCDev_Disconnect(APCDev* me) {
    reinterpret_cast<APC40MkII*>(me)->disconnect();
}

void APCDev_ResetDisplay(APCDev* me) {
    reinterpret_cast<APC40MkII*>(me)->resetDisplay();
}

bool APCDev_Poll(APCDev* me,  APCEvent* event) {
    return reinterpret_cast<APC40MkII*>(me)->poll((Event*)event);
}


void APCDev_SetBank(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setBank(enabled);
}

void APCDev_SetPlay(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setPlay(enabled);
}

void APCDev_SetRecord(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setRecord(enabled);
}

void APCDev_SetSession(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setSession(enabled);
}

void APCDev_SetMetronome(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setMetronome(enabled);
}

void APCDev_SetPan(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setPan(enabled);
}

void APCDev_SetSends(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setSends(enabled);
}

void APCDev_SetUser(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setUser(enabled);
}

void APCDev_SetMasterSelector(APCDev* me,  bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setMasterSelector(enabled);
}

void APCDev_SetClipDeviceView(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setClipDeviceView(enabled, (PageIndex)page);
}

void APCDev_SetDetailView(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDetailView(enabled, (PageIndex)page);
}

void APCDev_SetBankLeft(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setBankLeft(enabled, (PageIndex)page);
}

void APCDev_SetBankRight(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setBankRight(enabled, (PageIndex)page);
}

void APCDev_SetDeviceLeft(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceLeft(enabled, (PageIndex)page);
}

void APCDev_SetDeviceRight(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceRight(enabled, (PageIndex)page);
}

void APCDev_SetDeviceOnOff(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceOnOff(enabled, (PageIndex)page);
}

void APCDev_SetDeviceLock(APCDev* me,  bool enabled, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceLock(enabled, (PageIndex)page);
}

void APCDev_SetDeviceKnob(APCDev* me,  APCKnob knob, APCKnobValue value, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceKnob((KnobIndex)knob, (KnobValue)value, (PageIndex)page);
}

void APCDev_SetDeviceKnobRingType(APCDev* me,  APCKnob knob, APCRingType type, APCPage page) {
    reinterpret_cast<APC40MkII*>(me)->setDeviceKnobRingType((KnobIndex)knob, (RingType)type, (PageIndex)page);
}

void APCDev_SetTrackSelector(APCDev* me,  APCTrack track, bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setTrackSelector((TrackIndex)track, enabled);
}

void APCDev_SetTrackActivator(APCDev* me,  APCTrack track, bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setTrackActivator((TrackIndex)track, enabled);
}

void APCDev_SetTrackSolo(APCDev* me,  APCTrack track, bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setTrackSolo((TrackIndex)track, enabled);
}

void APCDev_SetTrackRecord(APCDev* me,  APCTrack track, bool enabled) {
    reinterpret_cast<APC40MkII*>(me)->setTrackRecord((TrackIndex)track, enabled);
}

void APCDev_SetTrackAB(APCDev* me,  APCTrack track, APCDualColor state) {
    reinterpret_cast<APC40MkII*>(me)->setTrackAB((TrackIndex)track, (DualColor)state);
}

void APCDev_SetTrackKnob(APCDev* me,  APCKnob knob, APCKnobValue value) {
    reinterpret_cast<APC40MkII*>(me)->setTrackKnob((KnobIndex)knob, (KnobValue)value);
}

void APCDev_SetTrackKnobRingType(APCDev* me,  APCKnob knob, APCRingType type) {
    reinterpret_cast<APC40MkII*>(me)->setTrackKnobRingType((KnobIndex)knob, (RingType)type);
}

void APCDev_SetClipStop(APCDev* me,  APCTrack track, APCClipStopLED state) {
    reinterpret_cast<APC40MkII*>(me)->setClipStop((TrackIndex)track, (ClipStopLED)state);
}

void APCDev_SetClip(APCDev* me,  APCClipCoords coords, APCColor color, APCLEDType type) {
    reinterpret_cast<APC40MkII*>(me)->setClip((ClipCoord)coords.x, (ClipCoord)coords.y, (Color)color, (LEDType)type);
}

void APCDev_SetSceneLaunch(APCDev* me,  APCScene row, APCColor color, APCLEDType type) {
    reinterpret_cast<APC40MkII*>(me)->setSceneLaunch((SceneIndex)row, (Color)color, (LEDType)type);
}




const char* APC_GetEventTypeString(APCEventType type) {
    return GetEventTypeString((EventType)type);
}

APCColor APC_GetNearestColor(APCRGB rgb) {
    return (APCColor)GetNearestColor(*(RGB*)&rgb);
}

APCRGB APC_Color2RGB(APCColor color) {
    return *reinterpret_cast<APCRGB*>(&Color2RGB((Color)color));
}

APCClipCoords APC_ClipId2Coords(APCClip id) {
    return { (unsigned char)(id & 7), (unsigned char)(id >> 3) };
}

#endif // APCAPI_EXPORT_C
