/*
  Unofficial C binding of APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

#ifndef __APCAPI_C__
#define __APCAPI_C__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "./APCAPI_C_Types.h"

#if defined(APCAPI_EXPORT_C)
#if defined(_WIN32) || defined(__CYGWIN__)
#define APC_API __declspec(dllexport)
#else
#define APC_API __attribute__((visibility("default")))
#endif
#else
#define APC_API //__declspec(dllimport)
#endif





APC_API APCDev* APCDev_Create(APCErrorCallback callback, void* userData);
APC_API void APCDev_Destroy(APCDev*);
APC_API bool APCDev_Connect(APCDev*,  APCMode mode);
APC_API void APCDev_Disconnect(APCDev*);
APC_API void APCDev_ResetDisplay(APCDev*);
APC_API bool APCDev_Poll(APCDev*,  APCEvent* event);

APC_API void APCDev_SetBank(APCDev*,  bool enabled);
APC_API void APCDev_SetPlay(APCDev*,  bool enabled);
APC_API void APCDev_SetRecord(APCDev*,  bool enabled);
APC_API void APCDev_SetSession(APCDev*,  bool enabled);
APC_API void APCDev_SetMetronome(APCDev*,  bool enabled);
APC_API void APCDev_SetPan(APCDev*,  bool enabled);
APC_API void APCDev_SetSends(APCDev*,  bool enabled);
APC_API void APCDev_SetUser(APCDev*,  bool enabled);
APC_API void APCDev_SetMasterSelector(APCDev*,  bool enabled);
APC_API void APCDev_SetClipDeviceView(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDetailView(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetBankLeft(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetBankRight(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDeviceLeft(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDeviceRight(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDeviceOnOff(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDeviceLock(APCDev*,  bool enabled, APCPage page);
APC_API void APCDev_SetDeviceKnob(APCDev*,  APCKnob knob, APCKnobValue value, APCPage page);
APC_API void APCDev_SetDeviceKnobRingType(APCDev*,  APCKnob knob, APCRingType type, APCPage page);
APC_API void APCDev_SetTrackSelector(APCDev*,  APCTrack track, bool enabled); // unavailable in Generic mode
APC_API void APCDev_SetTrackActivator(APCDev*,  APCTrack track, bool enabled);
APC_API void APCDev_SetTrackSolo(APCDev*,  APCTrack track, bool enabled);
APC_API void APCDev_SetTrackRecord(APCDev*,  APCTrack track, bool enabled);
APC_API void APCDev_SetTrackAB(APCDev*,  APCTrack track, APCDualColor state);
APC_API void APCDev_SetTrackKnob(APCDev*,  APCKnob knob, APCKnobValue value);
APC_API void APCDev_SetTrackKnobRingType(APCDev*,  APCKnob knob, APCRingType type);
APC_API void APCDev_SetClipStop(APCDev*,  APCTrack track, APCClipStopLED state);
APC_API void APCDev_SetClip(APCDev*,  APCClipCoords coords, APCColor color, APCLEDType type);
APC_API void APCDev_SetSceneLaunch(APCDev*,  APCScene row, APCColor color, APCLEDType type);


APC_API const char* APC_GetEventTypeString(APCEventType type);
APC_API APCClipCoords APC_ClipId2Coords(APCClip id);
APC_API APCClip APC_ClipCoords2Id(APCClipCoords coords) {

APC_API APCColor APC_GetNearestColor(APCRGB rgb);
APC_API APCRGB APC_Color2RGB(APCColor color);

#ifdef __cplusplus
}
#endif

#endif