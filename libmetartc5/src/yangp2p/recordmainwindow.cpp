//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangp2p/recordmainwindow.h>
#include <yangp2p/YangP2pCommon.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangFile.h>
#include <yangutil/sys/YangSocket.h>
#include <yangutil/sys/YangIni.h>
#include <yangutil/sys/YangString.h>
#include <yangp2p/YangP2pFactory.h>
#include <iostream>

void g_qt_p2p_receiveData(void *context, YangFrame *msgFrame)
{
    RecordMainWindow *win = (RecordMainWindow *)context;

    win->setRecvText((char *)msgFrame->payload, msgFrame->nb);
}
RecordMainWindow::RecordMainWindow()
{
    m_context = new YangContext();
    m_context->init((char *)"yvrtc_config.ini");
    m_context->avinfo.video.videoEncoderFormat = YangI420;

    yang_setLogLevle(m_context->avinfo.sys.logLevel);
    yang_setLogFile(m_context->avinfo.sys.hasLogFile);

    m_context->avinfo.sys.httpPort = 1988;
    m_context->avinfo.sys.mediaServer = Yang_Server_P2p; // Yang_Server_Srs/Yang_Server_Zlm/Yang_Server_P2p
    m_context->avinfo.sys.rtcLocalPort = 10000 + yang_random() % 15000;
    memset(m_context->avinfo.sys.localIp, 0, sizeof(m_context->avinfo.sys.localIp));
    yang_getLocalInfo(m_context->avinfo.sys.localIp);

    m_hasAudio = false;
    m_isStartpushplay = false;
    // using h264 h265
    m_context->avinfo.video.videoEncoderType = Yang_VED_264; // Yang_VED_265;

    m_context->streams.m_streamState = this;
    m_context->avinfo.audio.hasAec = 1;

    m_context->channeldataRecv.context = this;
    m_context->channeldataRecv.receiveData = g_qt_p2p_receiveData;

    m_context->avinfo.rtc.usingDatachannel = 1;
}

RecordMainWindow::~RecordMainWindow()
{
    closeAll();
}

void RecordMainWindow::setRecvText(char *data, int32_t nb)
{
    printf("dataChannel receive:%s\n", data);
}

void RecordMainWindow::closeAll()
{

    if (m_context)
    {
        yang_delete(m_message);
        yang_delete(m_context);
    }
}

void RecordMainWindow::streamStateNotify(int32_t puid, YangStreamOptType opt, bool isConnect)
{
    std::cout << "online user play count==" << m_context->streams.getPlayOnlineCount() << ",push count==" << m_context->streams.getPushOnlineCount();
}

void RecordMainWindow::success()
{
    std::cout << "RecordMainWindow::success" << std::endl;
}

void RecordMainWindow::failure(int32_t errcode)
{
    std::cout << "RecordMainWindow::failure" << std::endl;
}

void RecordMainWindow::receiveSysMessage(YangSysMessage *mss, int32_t err)
{
    switch (mss->messageId)
    {
    case YangM_P2p_Connect:
    {
        if (err)
        {
            std::cout << "receiveSysMessage YangM_P2p_Connect err:" << err << std::endl;
        }
    }
    break;
    case YangM_P2p_Disconnect:
        break;
    case YangM_P2p_Play_Start:
        break;
    case YangM_P2p_Play_Stop:
        break;
    case YangM_P2p_StartVideoCapture:
        break;
    }
    std::cout << "receiveSysMessage::mss->messageId:" << mss->messageId << std::endl;
}
