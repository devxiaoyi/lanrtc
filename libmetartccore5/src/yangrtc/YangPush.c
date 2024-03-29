//
// Copyright (c) 2019-2022 yanggaofeng
//

#include <yangrtc/YangPush.h>
#include <yangrtc/YangRtcUdp.h>
#include <yangutil/sys/YangLog.h>
int32_t yang_send_avpacket(YangRtcSession *session, YangRtpPacket *pkt,	YangBuffer *pbuf) {
	int32_t err = Yang_Ok;
	int32_t nn_encrypt = yang_buffer_pos(pbuf);

	if (session->push)	session->push->cache_nack(session->push->pubStream, pkt, pbuf->data,	nn_encrypt);
#if YVRTC_RTPRTCP_DTLS
	if ((err = yang_enc_rtp(&session->context.srtp, pbuf->data, &nn_encrypt)) != Yang_Ok) {
		return yang_error_wrap(err, "srtp protect");
	}
#endif
	return session->context.udp->sendData(&session->context.udp->session, pbuf->data, nn_encrypt);
}

int32_t yang_send_nackpacket(YangRtcContext *context, char *data, int32_t nb) {
	int32_t err = Yang_Ok;
	int32_t nn_encrypt = nb;
#if YVRTC_RTPRTCP_DTLS
	if ((err = yang_enc_rtp(&context->srtp, data, &nn_encrypt)) != Yang_Ok) {
		return yang_error_wrap(err, "srtp protect");
	}
#endif
	return context->udp->sendData(&context->udp->session, data, nn_encrypt);
}
