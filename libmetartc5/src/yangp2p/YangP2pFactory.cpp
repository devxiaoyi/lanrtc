//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangp2p/YangP2pFactory.h>
#include "YangP2pMessageHandle.h"
#include <yangp2p/YangP2pCaputreCamera.h>
#include <yangp2p/recordmainwindow.h>

YangP2pFactory::YangP2pFactory() {
    w = new RecordMainWindow();
    sysmessage = createP2pMessageHandle(w->m_hasAudio, w->m_context, w, w);
}

YangP2pFactory::~YangP2pFactory() {
	delete w;
}

YangP2pHandle* YangP2pFactory::createP2pHandle(bool hasAudio, YangContext *pcontext,YangSysMessageI *pmessage) {
	return new YangP2pHandleImpl(hasAudio,pcontext, pmessage);
}

YangSysMessageHandle* YangP2pFactory::createP2pMessageHandle(bool hasAudio, YangContext *pcontext,
        YangSysMessageI *pmessage,YangSysMessageHandleI* pmessagehandle) {
    return new YangP2pMessageHandle(hasAudio,pcontext, pmessage,pmessagehandle);
}

YangVideoBuffer* YangP2pFactory::getPreVideoBuffer(YangSysMessageHandle* pmessageHandle){
	if(!pmessageHandle) return NULL;
	YangP2pMessageHandle* mess=dynamic_cast<YangP2pMessageHandle*>(pmessageHandle);
	if(mess&&mess->m_p2p) return mess->m_p2p->getPreVideoBuffer();
	return NULL;

}

vector<YangVideoBuffer*>* YangP2pFactory::getPlayVideoBuffer(YangSysMessageHandle* pmessageHandle){
	if(!pmessageHandle) return NULL;
	YangP2pMessageHandle* mess=dynamic_cast<YangP2pMessageHandle*>(pmessageHandle);
	if(mess&&mess->m_p2p) return mess->m_p2p->getPlayVideoBuffer();
	return NULL;
}
void* YangP2pFactory::getP2pCapture(int32_t pcapturetype,YangContext *pcontext){
  
    return new YangP2pCaputreCamera(pcontext);
}

YangVideoEncoderBuffer* YangP2pFactory::getTxVideoBuffer(){
    if(!sysmessage) return NULL;
    YangP2pMessageHandle* mess=dynamic_cast<YangP2pMessageHandle*>(sysmessage);
    if(mess&&mess->m_p2p) return mess->m_p2p->getTxVideoBuffer();
    return NULL;
}
