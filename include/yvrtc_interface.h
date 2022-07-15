#ifndef INCLUDE_YVRTC_INTERFACE_H_
#define INCLUDE_YVRTC_INTERFACE_H_

#include <stdint.h>

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
    };
}

#endif /* INCLUDE_YVRTC_INTERFACE_H_ */