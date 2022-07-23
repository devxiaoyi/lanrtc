#ifndef INCLUDE_YVRTC_INTERFACE_H_
#define INCLUDE_YVRTC_INTERFACE_H_

#include <stdint.h>
#include <iostream>
#include <string>

#define SEND_KBPS_AUTO_CALCULATE -1

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

    enum P2PRole {
        kP2PRoleClient = 0,
        kP2PRoleServer = 1,
    };

    struct EngineConfig {
        const char* app_id = nullptr;
        P2PRole role = kP2PRoleClient;
        const char* server_ip = nullptr;
        int server_port_min = 50000;
        int server_port_max = 50004;
    };

    enum StreamIndex{
        kStreamIndexIndex0,
        kStreamIndexIndex1
    };

    enum ConnectionState {
        kConnectionStateDisconnected = 1,
        kConnectionStateConnecting = 2,
        kConnectionStateConnected = 3,
        kConnectionStateReconnecting = 4,
        kConnectionStateReconnected = 5,
    };

    enum VideoCodecType {
        /**
         * @hidden
         * @brief 未知类型
         */
        kVideoCodecTypeUnknown = 0,
        /**
         * @brief 标准 H264 编码器
         */
        kVideoCodecTypeH264 = 1,
        /**
         * @brief 标准 ByteVC1 编码器
         */
        kVideoCodecTypeByteVC1 = 2,
    };

    enum VideoPictureType {
        /**
         * @brief 未知类型
         */
        kVideoPictureTypeUnknown = 0,
        /**
         * @brief I帧，关键帧，编解码不需要参考其他视频帧
         */
        kVideoPictureTypeI,
        /**
         * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
         */
        kVideoPictureTypeP,
        /**
         * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
         */
        kVideoPictureTypeB
    };

    class IEncodedVideoFrame {
    public:
        /**
         * @brief 获取视频编码类型
         * @return VideoCodecType 视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
         */
        virtual VideoCodecType codec_type() const = 0;
        /**
         * @brief 获取视频采集时间戳
         * @return 视频采集时间戳，单位：微秒
         */
        virtual int64_t timestamp_us() const = 0;
        /**
         * @brief 获取视频编码时间戳
         * @return 视频编码时间戳，单位：微秒
         */
        virtual int64_t timestamp_dts_us() const = 0;
        /**
         * @brief 获取视频帧宽度
         * @return 视频帧宽度，单位：px
         */
        virtual int width() const = 0;
        /**
         * @brief 获取视频帧高度
         * @return 视频帧高度，单位：px
         */
        virtual int height() const = 0;
        /**
         * @brief 获取视频编码帧类型
         * @return 视频编码格式，参看 VideoPictureType{@link #VideoPictureType}
         */
        virtual VideoPictureType picture_type() const = 0;
        /**
         * @brief 获取视频帧旋转角度
         * @return 视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
         */
        virtual VideoRotation rotation() const = 0;
        /**
         * @brief 获取视频帧数据指针地址
         * @return 视频帧数据指针地址
         */
        virtual uint8_t* data() const = 0;
        /**
         * @brief 获取视频帧数据大小
         * @return 视频帧数据大小
         */
        virtual int data_size() const = 0;

         /**
         * @brief 浅拷贝视频帧并返回指针
         */
        virtual IEncodedVideoFrame* shallow_copy() const = 0;
        /**
         * @brief 释放视频帧
         */
        virtual void release() = 0;
        /**
         * @brief 根据视频帧参数创建视频帧并返回指针
         * @param [in] VideoFrameBuilder 视频帧创建类对象，详见 VideoFrameBuilder：{@link #VideoFrameBuilder}
         */
        static IEncodedVideoFrame* build_encoded_video_frame(const EncodedVideoFrameBuilder& builder);
        /**
         * @hidden
         */
    protected:
        /**
         * @brief 析构函数
         */
        virtual ~IEncodedVideoFrame() = default;
    };

    enum VideoStreamScaleMode {
        /**
         * @brief 自动模式，默认值为 FitWithCropping。
         */
        kVideoStreamScaleModeAuto = 0,
        /**
         * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
         */
        kVideoStreamScaleModeStretch = 1,
        /**
         * @brief 视窗填满优先。<br>
         *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
         *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
         */
        kVideoStreamScaleModeFitWithCropping = 2,
        /**
         * @brief 视频帧内容全部显示优先。<br>
         *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
         *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
         */
        kVideoStreamScaleModeFitWithFilling = 3,
    };

    /**
     * @type keytype
     * @brief 网络不好时的视频编码降级策略
     */
    enum VideoEncodePreference {
        /**
         * @brief 不降级
         */
        kVideoEncodePreferenceDisabled = 0,
        /**
         * @brief 优先保证帧率，以保证视频流畅度
         */
        kVideoEncodePreferenceFramerate,
        /**
         * @brief 优先保证画质
         */
        kVideoEncodePreferenceQuality,
        /**
         * @brief 平衡模式
         */
        kVideoEncodePreferenceBalance,
    };

    enum VideoRotation {
        /**
         * @brief 顺时针旋转 0 度
        */
        kVideoRotation0 = 0,
        /**
         * @brief 顺时针旋转 90 度
        */
        kVideoRotation90 = 90,
        /**
         * @brief 顺时针旋转 180 度
        */
        kVideoRotation180 = 180,
        /**
         * @brief 顺时针旋转 270 度
        */
        kVideoRotation270 = 270
    };

    struct VideoSolution {
        int width;
        int height;
        int fps;
        int max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
        VideoStreamScaleMode scale_mode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
        VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
    };

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


//**********android ***********//
    class YVPlayEngine {
    public:
        YVPlayEngine();
        virtual ~YVPlayEngine();

        int32_t YVPlayStart(std::string url);
        int32_t YVPlayStop();
        int32_t PollVideoFrame(YVRFrame *pFrame);

        void SetP2PBinaryMessageReceived(YVRDataChannelRecvCallback callback,void* pUser);
        void SendP2PBinaryMessage(const uint8_t* message, int length, bool reliable);

    public:
        YVRDataChannelRecvCallback m_callback;
        void* m_pUser;
    };

//*********************server******************
    class IStreamingRTCEngine;
    class IStreamingRTCEventHandler;

    class IStreamingRTCEngine {
    public:
        static IStreamingRTCEngine* CreateStreamingRTCEngine(const EngineConfig& config,
                                        IStreamingRTCEventHandler* handler, const char* params);

        int64_t SendP2PBinaryMessage(const uint8_t* message, int length, bool reliable);

        int PutVideoFrame(YVRFrame *pFrame);

        virtual int Startup() = 0;
        virtual int Shutdown() = 0;
        virtual int SetVideoEncoderConfig(yvrtc::StreamIndex stream_index, const VideoSolution* solutions, int solution_num) = 0;
        virtual bool PushEncodedVideoFrame(yvrtc::StreamIndex stream_index, int video_index, IEncodedVideoFrame* video_stream) = 0;

    private:
        IStreamingRTCEngine();
        ~IStreamingRTCEngine() {}

        bool Init(IStreamingRTCEventHandler* rtcHandle);
    public:
        IStreamingRTCEventHandler* m_rtcEventHandler;

    };



    class IStreamingRTCEventHandler {
    public:
        virtual void OnP2PBinaryMessageReceived(const uint8_t* message, int size) {
            (void)message;
            (void)size;
        }

        virtual void OnConnectionStateChanged(yvrtc::ConnectionState state) {
                (void)state;
            }

        virtual ~IStreamingRTCEventHandler() {}
    };
}

#endif /* INCLUDE_YVRTC_INTERFACE_H_ */
