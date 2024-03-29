#ifndef INCLUDE_YVRTC_INTERFACE_H_
#define INCLUDE_YVRTC_INTERFACE_H_

#include <stdint.h>
#include <iostream>
#include <string>

namespace yvrtc
{
    enum VideoFrameType
    {
        VideoFrameTypeP = 0,
        VideoFrameTypeI,
        VideoFrameTypeB,
        VideoFrameUnknow
    };

    typedef struct
    {
        int32_t uid;
        VideoFrameType frameType;
        int32_t size;
        int64_t timestamp;
        uint8_t *payload;
    } YVRFrame;

    class YVRTCEngine {
    public:
        YVRTCEngine();
        virtual ~YVRTCEngine();

        int32_t putVideoFrame(YVRFrame *pFrame);

        int32_t putDataFrame(YVRFrame *pFrame);
        int32_t RegisterDataReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user);
    };

    class YVPlayEngine {
    public:
        YVPlayEngine();
        virtual ~YVPlayEngine();

        int32_t YVPlayStart(std::string url);
        int32_t YVPlayStop();
        int32_t RegisterVideoReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user);

        int32_t putDataFrame(YVRFrame *pFrame);
        int32_t RegisterDataReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user);
    };
}

#endif /* INCLUDE_YVRTC_INTERFACE_H_ */
