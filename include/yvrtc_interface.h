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

    typedef void (*YVRDataChannelRecvCallback)(YVRFrame* msgFrame, void* pUser);

    class YVRTCEngine {
    public:
        YVRTCEngine();
        virtual ~YVRTCEngine();

        void setReceiveDataChannel(YVRDataChannelRecvCallback callback,void* pUser);
        void sendDataChannelData(YVRFrame* yvrFrame);

        int32_t putVideoFrame(YVRFrame *pFrame);

    public:
        YVRDataChannelRecvCallback m_callback;
        void* m_pUser;
    };

    class YVPlayEngine {
    public:
        YVPlayEngine();
        virtual ~YVPlayEngine();

        int32_t YVPlayStart(std::string url);
        int32_t YVPlayStop();
        int32_t PollVideoFrame(YVRFrame *pFrame);
        int32_t RegisterVideoReceiver(int32_t (*receiver)(YVRFrame *pFrame));

        void setReceiveDataChannel(YVRDataChannelRecvCallback callback,void* pUser);
        void sendDataChannelData(YVRFrame* yvrFrame);

    public:
        YVRDataChannelRecvCallback m_callback;
        void* m_pUser;
    };
}

#endif /* INCLUDE_YVRTC_INTERFACE_H_ */
