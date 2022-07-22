#include <yangp2p/YangP2pFactory.h>
#include <yvrtc_interface.h>
#include <yangplayer/YangPlayerHandle.h>
#include <iostream>
#include <string>

static std::unique_ptr<YangP2pFactory> g_p2p;
static std::unique_ptr<YangPlayerHandle> g_player;

void g_qt_Engine_receiveData(void *context, YangFrame *msgFrame)
{
    yvrtc::YVRTCEngine *engin = (yvrtc::YVRTCEngine *)context;
    yvrtc::YVRFrame yvrFrame = {0};
    yvrFrame.payload = msgFrame->payload;
    yvrFrame.size = msgFrame->nb;
    engin->m_callback(&yvrFrame, engin->m_pUser);
}

yvrtc::YVRTCEngine::YVRTCEngine()
{
    if (!g_p2p) {
        g_p2p.reset(new YangP2pFactory());
        g_p2p->init(g_qt_Engine_receiveData, this);
    }
}

yvrtc::YVRTCEngine::~YVRTCEngine()
{

}

void yvrtc::YVRTCEngine::setReceiveDataChannel(YVRDataChannelRecvCallback callback,void* pUser)
{
    m_callback = callback;
    m_pUser = pUser;
}

void yvrtc::YVRTCEngine::sendDataChannelData(YVRFrame* yvrFrame)
{
    YangFrame YFrame;
    YFrame.payload = yvrFrame->payload;
    YFrame.nb = yvrFrame->size;
    YFrame.mediaType=YANG_DATA_CHANNEL_STRING;
    if (g_p2p)
    {
        g_p2p->sendDataChannelData(&YFrame);
    }
}

int32_t yvrtc::YVRTCEngine::putVideoFrame(YVRFrame *pFrame)
{
    int32_t ret = 0;
    YangFrame YFrame;
    YFrame.payload = pFrame->payload;
    YFrame.nb = pFrame->size;
    YFrame.mediaType = 9;
    YFrame.dts = pFrame->timestamp;
    YFrame.pts = pFrame->timestamp;
    YFrame.uid = pFrame->uid;
    YFrame.frametype = pFrame->frameType;
    if (g_p2p)
    {
        ret = g_p2p->putTxVideo(&YFrame);
    }
    else
    {
        ret = -1;
    }
    return ret;
}

void g_qt_play_receiveData(void* context,YangFrame* msgFrame){
    yvrtc::YVPlayEngine* play=(yvrtc::YVPlayEngine*)context;
    yvrtc::YVRFrame yvrFrame = {0};
    yvrFrame.payload = msgFrame->payload;
    yvrFrame.size = msgFrame->nb;
    play->m_callback(&yvrFrame, play->m_pUser);
}

yvrtc::YVPlayEngine::YVPlayEngine()
{
    if (!g_player)
    {
        g_player.reset(YangPlayerHandle::createPlayerHandle());
        g_player->initDataChannel(g_qt_play_receiveData,this);
    }

}

yvrtc::YVPlayEngine::~YVPlayEngine()
{

}

void yvrtc::YVPlayEngine::setReceiveDataChannel(YVRDataChannelRecvCallback callback,void* pUser)
{
    m_callback = callback;
    m_pUser = pUser;
}

void yvrtc::YVPlayEngine::sendDataChannelData(YVRFrame* yvrFrame)
{
    YangFrame YFrame;
    YFrame.payload = yvrFrame->payload;
    YFrame.nb = yvrFrame->size;
    YFrame.mediaType=YANG_DATA_CHANNEL_STRING;
    if (g_player)
    {
        g_player->dataChannelSend(&YFrame);
    }
}

int32_t yvrtc::YVPlayEngine::YVPlayStart(std::string url)
{
    int ret = -1;
    if (g_player->play((char*)url.c_str()) == Yang_Ok)
    {
        ret = 0;
    }
    return ret;
}

int32_t yvrtc::YVPlayEngine::YVPlayStop()
{
    if (nullptr != g_player)
    {
        g_player->stopPlay();
    }
    return 0;
}

int32_t yvrtc::YVPlayEngine::PollVideoFrame(YVRFrame *pFrame)
{
    int32_t ret = -1;
    if (nullptr != g_player)
    {
        YangFrame Frame = {0};
        ret = g_player->getVideoFrame(&Frame);
        if (ret == 0) {
            pFrame->payload = Frame.payload;
            pFrame->frameType = (VideoFrameType)Frame.frametype;
            pFrame->size = Frame.nb;
            pFrame->timestamp = Frame.dts;
            pFrame->uid = Frame.uid;
        }
        else {
            pFrame->payload = nullptr;
            pFrame->frameType = VideoFrameUnknow;
            pFrame->size = 0;
            pFrame->timestamp = 0;
            pFrame->uid = 0;
        }
    }
    return ret;
}

int32_t yvrtc::YVPlayEngine::RegisterVideoReceiver(int32_t (*receiver)(YVRFrame *pFrame))
{
    return 0;
}


