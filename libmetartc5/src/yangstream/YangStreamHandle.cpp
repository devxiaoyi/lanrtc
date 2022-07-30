//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangstream/YangStreamHandle.h>
#include <yangutil/sys/YangLog.h>
//#include <yangstream/YangStreamSrt.h>

#include <stdio.h>
#include <string.h>


void yang_create_streamHandle(YangStreamHandle* streamHandle,YangStreamConfig* streamconfig,YangAVInfo* avinfo) {
	if(streamHandle==NULL) return;
	yang_create_stream(avinfo->sys.mediaServer,avinfo->sys.transType,streamHandle,streamconfig,avinfo);
}

void yang_destroy_streamHandle(YangStreamHandle* streamHandle) {
	if(streamHandle==NULL) return;
	yang_destroy_stream(streamHandle);
}




