﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangrtc/YangStreamUrl.h>
#include <yangutil/sys/YangCUrl.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangMath.h>
#include <yangutil/yangtype.h>
int32_t yang_stream_parseUrl(char* url,YangStreamConfig* stream,YangAVInfo* avinfo,YangStreamOptType opt){
	int32_t err=Yang_Ok;
	YangUrlData data;
	memset(&data,0,sizeof(YangUrlData));

    if((err=yang_url_parse(url,&data))!=Yang_Ok){
		return yang_error_wrap(err,"stream parse url error");
	}

	stream->localPort = 10000+yang_random()%15000;
	strncpy(stream->remoteIp, data.server, sizeof(stream->remoteIp) - 1);
	stream->remotePort = data.port;
	strncpy(stream->app, data.app, sizeof(stream->app) - 1);
	strncpy(stream->stream, data.stream, sizeof(stream->stream) - 1);
	stream->uid = 0;
	stream->streamOptType = opt;//Yang_Stream_Play;

	yang_init_avinfo(avinfo);

return err;

}
