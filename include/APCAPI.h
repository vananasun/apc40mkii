/*
  Unofficial APC40 MKII C++ API.
  By Maxim van Dijk (mvandijk303@gmail.com)

  For nomenclature of the knobs and buttons, please read page 4 through 6 of the
  provided official "APC40 mkII User Guide.pdf".
  
  If you are a developer that wants to contribute to this API, make sure to read
  the provided official "APC40 mkII Communications Protocol v1.2.pdf".
*/

#pragma once
#include "./APCAPI_Colors.h"
#include "./APCAPI_Events.h"
#include <string>

namespace APCAPI
{

    typedef void (*ErrorCallback)(const std::string& msg, void *userData);


    class APC40MkII
    {
    private:
        struct APCCore;
        APCCore* _;

    public:
        APC40MkII(ErrorCallback callback, void* userData);
        ~APC40MkII();
        bool connect();
        void disconnect();
        void resetDisplay();
        bool poll(Event* event);


        /* Host to device output methods */

        void setPlay(bool enabled);
        void setRecord(bool enabled);
        void setSession(bool enabled);
        void setMetronome(bool enabled);
        void setTapTempo(bool enabled);
        void setPan(bool enabled);
        void setSends(bool enabled);
        void setUser(bool enabled);

        void setSceneLaunch(int row, Color color);
        void setTrackSelector(int trackId);
        void setTrackActivator(int trackId, bool enabled);
        void setTrackSolo(int trackId, bool enabled);
        void setTrackRecord(int trackId, bool enabled);
        void setTrackAB(int trackId, int state);
        void setTrackKnob(int knobIndex, unsigned char value);
        void setClipStop(int trackId, bool enabled);
        void setClip(int x, int y, Color color);
    
        void setDeviceOnOff(bool enabled);
        void setDeviceLock(bool enabled);
        void setDeviceLeft(bool enabled);
        void setDeviceRight(bool enabled);
        void setDeviceKnob(int knobIndex, unsigned char value);
        void setBank(bool enabled);
        void setBankLeft(bool enabled);
        void setBankRight(bool enabled);
        void setClipDeviceView(bool enabled);
        void setDetailView(bool enabled);

    };



    /**
     *  \brief Converts a clip ID to a set of X,Y coordinates.
     *         [0,0] = Bottom left!
     * 
     *  \param clipId
     * 
     *  \returns [ x, y ]
     */
    template <typename T>
    inline const constexpr std::pair<T,T> clipNum2Coords(T clipId)
    {
        T x, y;
        if constexpr (std::is_floating_point_v<T>) {
            y = static_cast<T>(static_cast<int>(clipId) >> 3);
            x = static_cast<T>(static_cast<int>(clipId) & 7);
        } else {
            y = static_cast<T>(static_cast<std::make_unsigned<T>::type>(clipId) >> 3);
            x = static_cast<T>(static_cast<std::make_unsigned<T>::type>(clipId) & 7);
        }
        return { x, y };
    }


};
