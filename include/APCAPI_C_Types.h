/*
  Unofficial C binding of APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

#ifndef __APCAPI_C_Types__
#define __APCAPI_C_Types__

/*******************************************************************************
 * 
 * APCAPI_Types.h
 * 
 ******************************************************************************/

typedef void (*APCErrorCallback)(const char* message, void* userData);

typedef unsigned char APCScene;
typedef unsigned char APCTrack;
typedef unsigned char APCPage;
typedef unsigned char APCClip;
typedef unsigned char APCClipCoord;
typedef unsigned char APCKnob;
typedef unsigned char APCKnobValue;

typedef enum
{
    APC_RINGTYPE_OFF = 0,
    APC_RINGTYPE_SINGLE = 1,
    APC_RINGTYPE_VOLUME = 2,
    APC_RINGTYPE_PAN = 3,
} APCRingType;

typedef enum
{
    APC_MODE_GENERIC = 0,
    APC_MODE_ABLETON = 1,
    APC_MODE_ALTERNATEABLETON = 2
} APCMode;


/*******************************************************************************
 * 
 * APCAPI_Events.h
 * 
 ******************************************************************************/

typedef enum
{
    APC_EVENTTYPE_NONE = 0,
    APC_EVENTTYPE_PLAYSTOP,
    APC_EVENTTYPE_RECORD,
    APC_EVENTTYPE_SESSION,
    APC_EVENTTYPE_METRONOME,
    APC_EVENTTYPE_TAPTEMPO,
    APC_EVENTTYPE_NUDGE,
    APC_EVENTTYPE_PAN,
    APC_EVENTTYPE_SENDS,
    APC_EVENTTYPE_USER,
    APC_EVENTTYPE_TEMPO,
    APC_EVENTTYPE_CLIPLAUNCH,
    APC_EVENTTYPE_CLIPSTOP,
    APC_EVENTTYPE_STOPALLCLIPS,
    APC_EVENTTYPE_SCENELAUNCH,
    APC_EVENTTYPE_CUELEVEL,
    APC_EVENTTYPE_MASTERSELECTOR,
    APC_EVENTTYPE_MASTERFADER,
    APC_EVENTTYPE_TRACKSELECTOR,
    APC_EVENTTYPE_TRACKACTIVATOR,
    APC_EVENTTYPE_TRACKFADER,
    APC_EVENTTYPE_TRACKSOLO,
    APC_EVENTTYPE_TRACKRECORD,
    APC_EVENTTYPE_TRACKAB,
    APC_EVENTTYPE_BANKSELECTLEFT,
    APC_EVENTTYPE_BANKSELECTUP,
    APC_EVENTTYPE_BANKSELECTRIGHT,
    APC_EVENTTYPE_BANKSELECTDOWN,
    APC_EVENTTYPE_SHIFT,
    APC_EVENTTYPE_BANK,
    APC_EVENTTYPE_TRACKKNOB,
    APC_EVENTTYPE_DEVICEKNOB,
    APC_EVENTTYPE_DEVICEONOFF,
    APC_EVENTTYPE_DEVICELOCK,
    APC_EVENTTYPE_DEVICELEFT,
    APC_EVENTTYPE_DEVICERIGHT,
    APC_EVENTTYPE_BANKLEFT,
    APC_EVENTTYPE_BANKRIGHT,
    APC_EVENTTYPE_CLIPDEVICEVIEW,
    APC_EVENTTYPE_DETAILVIEW,
    APC_EVENTTYPE_CROSSFADER,
    APC_EVENTTYPE_FOOTSWITCH
} APCEventType;

typedef struct
{
    unsigned char x;
    unsigned char y;
} APCClipCoords;


typedef struct APCEvent_
{
    APCEventType type;
    union {
        unsigned char value; // 0 to 127
        char direction; // +, -
        bool pressed;
    };
    union {
        APCTrack trackId;
        APCScene sceneId;
        APCClip clipId;
        APCKnob knobId;
    };
    APCPage pageId; // only for mode 0 banked stuff
} APCEvent;


/*******************************************************************************
 * 
 * APCAPI_Colors.h
 * 
 ******************************************************************************/

typedef enum
{
    APC_COLOR_OFF = 0,
    APC_COLOR_WHITE = 3,
    APC_COLOR_RED = 5,
    APC_COLOR_YELLOW = 13,
    APC_COLOR_GREEN = 21,
    APC_COLOR_BLUE = 45,
    APC_COLOR_PURPLE = 48,
    APC_COLOR_CYAN = 37,
    APC_COLOR_MAGENTA = 53,
    APC_COLOR_ORANGE = 96,
    APC_COLOR_DARKGREY = 117,
    APC_COLOR_GREY = 2,
} APCColor;

typedef enum
{
    APC_LEDTYPE_PRIMARY = 0,
    APC_LEDTYPE_ONESHOT_1_24 = 1,
    APC_LEDTYPE_ONESHOT_1_16 = 2,
    APC_LEDTYPE_ONESHOT_1_8 = 3,
    APC_LEDTYPE_ONESHOT_1_4 = 4,
    APC_LEDTYPE_ONESHOT_1_2 = 5,
    APC_LEDTYPE_PULSING_1_24 = 6,
    APC_LEDTYPE_PULSING_1_16 = 7,
    APC_LEDTYPE_PULSING_1_8 = 8,
    APC_LEDTYPE_PULSING_1_4 = 9,
    APC_LEDTYPE_PULSING_1_2 = 10,
    APC_LEDTYPE_BLINKING_1_24= 11,
    APC_LEDTYPE_BLINKING_1_16 = 12,
    APC_LEDTYPE_BLINKING_1_8 = 13,
    APC_LEDTYPE_BLINKING_1_4 = 14,
    APC_LEDTYPE_BLINKING_1_2 = 15,
} APCLEDType;

typedef enum
{
    APC_CLIPSTOPLED_OFF = 0,
    APC_CLIPSTOPLED_ON = 1,
    APC_CLIPSTOPLED_BLINK = 2,
} APCClipStopLED;

typedef enum
{
    APC_DUALCOLOR_OFF = 0,
    APC_DUALCOLOR_YELLOW = 1,
    APC_DUALCOLOR_ORANGE = 2,
} APCDualColor;

typedef struct { unsigned char r,g,b; } APCRGB;


/*******************************************************************************
 * 
 * C Binding stuff
 * 
 ******************************************************************************/

typedef struct {
    void* _;
} APCDev;


#endif