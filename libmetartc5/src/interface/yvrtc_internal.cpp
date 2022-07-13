#include <yangp2p/YangP2pFactory.h>
#include <yvrtc_interface.h>

YangP2pFactory *mf = NULL;

yvrtc::YVRTCEngine::YVRTCEngine()
{
    mf = new YangP2pFactory();
    mf->init();
}

yvrtc::YVRTCEngine::~YVRTCEngine() {
    if (mf) {
        delete(mf);
    }
}

int32_t yvrtc::YVRTCEngine::putVideoFrame(YVRFrame *pFrame) {
    int32_t ret = 0;
    YangFrame YFrame;
    YFrame.payload = pFrame->payload;
    YFrame.nb = pFrame->size;
    YFrame.mediaType = 9;
    YFrame.dts = pFrame->timestamp;
    YFrame.pts = pFrame->timestamp;
    YFrame.uid = pFrame->uid;
    YFrame.frametype = pFrame->frameType;
    if (mf) { 
        mf->putTxVideo(&YFrame);
    }
    else {
        ret = -1;
    }
    return ret;
}
