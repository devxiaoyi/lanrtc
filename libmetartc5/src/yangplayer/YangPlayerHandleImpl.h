//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YANGMEETING_INCLUDE_YANGPLAYERHANDLE_H_
#define YANGMEETING_INCLUDE_YANGPLAYERHANDLE_H_
#include <yangplayer/YangPlayerHandle.h>
//#include <yangplayer/YangPlayerBase.h>
//#include <yangplayer/YangPlayReceive.h>
#include <yangstream/YangSynBuffer.h>
#include <yangutil/yangavinfotype.h>
#include <yangutil/sys/YangUrl.h>
#include "YangRtcReceive.h"


class YangPlayerHandleImpl :public YangPlayerHandle{
public:
    YangPlayerHandleImpl(YangContext* pcontext);
	virtual ~YangPlayerHandleImpl();
	// YangVideoBuffer* getVideoBuffer();
	int play(char* url);

	int32_t playRtc(int32_t puid,char* localIp, char* server, int32_t pport,char* app,char* stream);
	void stopPlay();

	int32_t getVideoFrame(YangFrame* pFrame);
	int32_t checkConnectionState();

	int32_t setVideoReceiver(int32_t (*func)(YangFrame *pFrame));
	int32_t setDataReceiver(int32_t (*func)(YangFrame *pFrame));

	int32_t putTxData(YangFrame *pFrame);

protected:

	YangUrlData m_url;
	void initList();
	// YangPlayReceive *m_recv;
	// YangPlayerBase *m_play;
	YangRtcReceive *m_rtcRecv;

private:
	YangContext* m_context;
	// YangVideoDecoderBuffer* m_outVideoBuffer;
	// YangAudioEncoderBuffer* m_outAudioBuffer;

	uint8_t* externalBuffer;
	// YangSysMessageI* m_message;
};

#endif /* YANGMEETING_INCLUDE_YANGPLAYERHANDLE_H_ */
