﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef INCLUDE_YANGPUSH_YANGP2pFACTORY_H_
#define INCLUDE_YANGPUSH_YANGP2pFACTORY_H_
#include <yangp2p/YangP2pHandle.h>
#include <yangutil/sys/YangSysMessageHandle.h>
#include <yangutil/buffer/YangVideoEncoderBuffer.h>
#include <yangp2p/recordmainwindow.h>

class YangP2pFactory {
public:
	YangP2pFactory();
	virtual ~YangP2pFactory();
	YangP2pHandle* createP2pHandle(bool hasAudio,YangContext* pcontext,YangSysMessageI* pmessage);
    YangSysMessageHandle* createP2pMessageHandle(bool hasAudio,YangContext* pcontext,YangSysMessageI* pmessage,YangSysMessageHandleI* pmessagehandle);
	YangVideoBuffer* getPreVideoBuffer(YangSysMessageHandle* pmessageHandle);
	std::vector<YangVideoBuffer*>* getPlayVideoBuffer(YangSysMessageHandle* pmessageHandle);
	void* getP2pCapture(int32_t pcapturetype,YangContext *pcontext);
	int32_t putTxVideo(YangFrame *pFrame);
	int32_t init();
    int32_t deinit();

private:
    RecordMainWindow* w;
	YangSysMessageHandle *sysmessage;
};

#endif /* INCLUDE_YANGPUSH_YANGPUSHFACTORY_H_ */
