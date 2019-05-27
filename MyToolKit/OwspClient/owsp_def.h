/*
 *  Version 3.5
 *  Time: 20090226
 */
 
#ifndef __LVSP_DEF_H_INCLUDED__
#define __LVSP_DEF_H_INCLUDED__


#define STR_LEN_32		32
#define STR_LEN_16		16

#define MAX_TLV_LEN		65535		//最大TLV长为(64K-1)

//版本信息
#define VERSION_MAJOR	3
#define VERSION_MINOR	8

//
//  如果已经定义
//
#ifndef u_int32
typedef unsigned long	u_int32;
typedef unsigned short	u_int16;
typedef unsigned char	u_int8;
#endif

#pragma pack(push)
#pragma pack(4)

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM								0x0001
#endif 

#ifndef WAVE_FORMAT_MPEGLAYER3
#define WAVE_FORMAT_MPEGLAYER3					    0x0055	// ISO/MPEG Layer 3 格式标记
#endif                                      
                                            
#ifndef WAVE_FORMAT_QUALCOMM_PUREVOICE      
#define WAVE_FORMAT_QUALCOMM_PUREVOICE	    	    0x0150
#endif                                      
                                            
//AMR_NB CBR wave format                    
#ifndef WAVE_FORMAT_AMR_CBR                 
#define WAVE_FORMAT_AMR_CBR 						0x7A21 
#endif                                      
                                            
//AMR VBR Not support yet                   
#ifndef WAVE_FORMAT_AMR_VBR                 
#define WAVE_FORMAT_AMR_VBR 						0x7A22
#endif                                      
                                            
//AMR_WB Wave format                        
#ifndef WAVE_FORMAT_VOICEAGE_AMR_WB         
#define WAVE_FORMAT_VOICEAGE_AMR_WB			        0xA104
#endif                                      
                                            
#define CODEC_H264									0x34363248	//H264
#define CODEC_H265									0x35363248	//H265


/* TLV 类型命令字 */

#define TLV_T_VERSION_INFO_ANSWER			   39
#define TLV_T_VERSION_INFO_REQUEST		   40
#define TLV_T_LOGIN_REQUEST					     41
#define TLV_T_LOGIN_ANSWER						   42
#define TLV_T_TOTAL_CHANNEL						   43		//NOT USED
#define TLV_T_SENDDATA_REQUEST				     44		//通道请求
#define TLV_T_SENDDATA_ANSWER					 45		//通道请求应答
#define TLV_T_TOTAL_CHANEL_ANSWER				 46		//Not used
#define TLV_T_SUSPENDSENDDATA_REQUEST		     47		//停止发送数据
#define TLV_T_SUSPENDSENDDATA_ANSWER		     48
#define TLV_T_DEVICE_KEEP_ALIVE					 49		//心跳包
#define TLV_T_DEVICE_FORCE_EXIT					 50		
#define TLV_T_CONTROL_REQUEST					 51		//云台等控制请求
#define TLV_T_CONTROL_ANSWER					 52		//云台等响应
#define TLV_T_RECORD_REQUEST				     53		//录像请求
#define TLV_T_RECORD_ANSWER						 54
#define TLV_T_DEVICE_SETTING_REQUEST			 55		//设备参数设置请求
#define TLV_T_DEVICE_SETTING_ANSWER				 56		//设备参数设置应答
#define TLV_T_KEEP_ALIVE_ANSWER					 57		//心跳包响应
#define TLV_T_DEVICE_RESET						 58		//通知设备重启
#define TLV_T_DEVICE_RESET_ANSWER				 59		//设备接收到重启命令后的响应，通常不用发出
#define TLV_T_ALERT_REQUEST     				 60   //报警请求，由设备发出
#define TLV_T_ALERT_ANSWER      				 61   //报警请求回应，由服务器发出，通常可以不用发出
#define TLV_T_ALERT_SEND_PHOTO    			     62   //报警后，设备采集当时的图片，发送到服务器
#define TLV_T_ALERT_SEND_PHOTO_ANSWER 	         63   //设备发送MSG_CMD_ALERT_SEND_PHOTO后，服务器的回应
#define TLV_T_CHANNLE_REQUEST		    		 64   		//切换到另一通道
#define TLV_T_CHANNLE_ANSWER					 65   		//切换另一通道应答
#define TLV_T_SUSPEND_CHANNLE_REQUEST		     66   		//挂起某一通道
#define TLV_T_SUSPEND_CHANNLE_ANSWER			 67   		//应答
#define TLV_T_VALIDATE_REQUEST					 68   		//程序验证请求
#define TLV_T_VALIDATE_ANSWER					 69   		//应答
#define TLV_T_DVS_INFO_REQUEST					 70			//设备DVS通知连接方设备信息请求
#define TLV_T_DVS_INFO_ANSWER					 71			//
#define TLV_T_PHONE_INFO_REQUEST					 72			//手机通知连接方手机信息请求
#define TLV_T_PHONE_INFO_ANSWER					 73			//



//vod & live
#define TLV_T_AUDIO_INFO							 0x61   //97		音频信息, 表示V为音频信息
#define TLV_T_AUDIO_DATA							 0x62   //98		音频数据, 表示V为音频数据
#define TLV_T_VIDEO_FRAME_INFO					     0x63   //99    视频帧信息, 表示V的数据描述帧信息
#define TLV_T_VIDEO_IFRAME_DATA					     0x64   //100   视频关键帧数据，表示V的数据为关键帧
#define TLV_T_VIDEO_PFRAME_DATA					     0x66   //102   视频P帧(参考帧)数据, 表示V的数据为参考帧
#define TLV_T_VIDEO_FRAME_INFO_EX				     0x65   //101   扩展视频帧信息支持>=64KB的视频帧
#define TLV_T_STREAM_FORMAT_INFO				     200    //			流格式信息 ,描述视频属性,音频属性

//vod
#define TLV_T_STREAM_FILE_INDEX						 213
#define TLV_T_STREAM_FILE_ATTRIBUTE				     214
#define TLV_T_STREAM_FILE_END					     0x0000FFFF

// 对于 owsp_def.h ，以下补充定义 owsp 协议的命令类型
#define TLV_T_DISCONNECT		220
#define TLV_T_SAY_BYE				221

//	录像回放 2015-9-7
#define	TLV_T_SEARCH_RECORD_REQ						0x014d		//	录像查询请求
#define	TLV_T_SEARCH_RECORD_RSP						0x014e		//	搜索录像文件应答
#define	TLV_T_RECORD_INFO							0x014f		//	录像文件信息		
#define	TLV_T_PLAY_RECORD_REQ						0x0150		//	录像回放请求
#define	TLV_T_PLAY_RECORD_RSP						0x0151		//	录像回放应答


/* response result */
#define _RESPONSECODE_SUCC						 0x01		//	成功
#define _RESPONSECODE_USER_PWD_ERROR			 0x02		//  用户名或密码错
#define _RESPONSECODE_PDA_VERSION_ERROR			 0x04		//	版本不一致
#define _RESPONSECODE_MAX_USER_ERROR			 0x05	
#define _RESPONSECODE_DEVICE_OFFLINE			 0x06		//	设备已经离线
#define _RESPONSECODE_DEVICE_HAS_EXIST			 0x07		//  设备已经存在
#define _RESPONSECODE_DEVICE_OVERLOAD				 0x08		//  设备性能超载(设备忙)
#define _RESPONSECODE_INVALID_CHANNLE				 0x09		//  设备不支持的通道
#define _RESPONSECODE_PROTOCOL_ERROR				0X0A		//协议解析出错
#define _RESPONSECODE_NOT_START_ENCODE			0X0B		//未启动编码
#define _RESPONSECODE_TASK_DISPOSE_ERROR		0X0C		//任务处理过程出错



//云台控制码,取值范围为0~255
 typedef enum _OWSP_ACTIONCode
 {
   OWSP_ACTION_MD_STOP      = 0,            // 停止运动
   OWSP_ACTION_ZOOMReduce=5,
   OWSP_ACTION_ZOOMADD=6,
   OWSP_ACTION_FOCUSADD=7,    //焦距
   OWSP_ACTION_FOCUSReduce=8,
   OWSP_ACTION_MD_UP=9,                    // 向上
   OWSP_ACTION_MD_DOWN=10,              // 向下
   OWSP_ACTION_MD_LEFT=11,              // 向左
   OWSP_ACTION_MD_RIGHT=12,            // 向右
   OWSP_ACTION_Circle_Add = 13,    //光圈
   OWSP_ACTION_Circle_Reduce = 14,    //
   OWSP_ACTION_AUTO_CRUISE = 15,			//自动巡航
   OWSP_ACTION_GOTO_PRESET_POSITION = 16, 	//跳转预置位
   OWSP_ACTION_SET_PRESET_POSITION = 17, 	//设置预置位点
   OWSP_ACTION_CLEAR_PRESET_POSITION = 18, //清除预置位点
   OWSP_ACTION_ACTION_RESET = 20,

   OWSP_ACTION_MD_LEFT_UP=21,             // 向上
   OWSP_ACTION_MD_LEFT_DOWN=22,              // 向下
   OWSP_ACTION_MD_RIGHT_UP=23,              // 向左
   OWSP_ACTION_MD_RIGHT_DOWN=24,            // 向右

   OWSP_ACTION_TV_SWITCH = 128,		//切换视频源,消息参数为INT*,1--TV, 2--SV,3--CV1, 4--CV2 
   OWSP_ACTION_TV_TUNER = 129,		//切换频道, 消息参数为INT*, 为频道号
   OWSP_ACTION_TV_SET_QUALITY  = 130,		//画质设置, 亮度,色度,饱和度,对比度结构体
 } OWSP_ACTIONCode;

//报警种类，目前只支持探头报警，也就是ATC_INFRARED
typedef enum _AlertTypeCode
{
	ATC_VIDEO = 0,//视频帧预测
	ATC_DEVICE_SERSTART = 1,	/* 设备启动 */	
	ATC_MOTION = 2,						/* 移动侦测报警 */
	ATC_VIDEOLOST = 3,				/* 视频丢失报警 */
	ATC_DISKFULL = 4,					/* 硬盘满报警 */
	ATC_HIDEALARM=5,					/* 视频遮挡报警 */	
	ATC_STOP = 6,							/* 服务器停止 */
	ATC_SDERROR = 7,         	/* SD卡异常*/
	ATC_INFRARED = 20					//开关量探头（比如红外探头）
}AlertTypeCode;

//报警级别，主要针对帧预测，开光量探头报警时该值统一为0，目前只支持探头报警，当触发报警时，发送报警级别ALC_ALERT，当报警停止时，发送ALC_STOP
typedef enum _AlertLevelCode
{
	ALC_ALERT = 0,//报警，警报级别最高，通常用户开关量探头
	ALC_LEVEL1 = 10,//1级警告，AlertLevelCode的值越大，警告级别越低
	ALC_STOP = 255//报警停止，发送停止信息
}AlertLevelCode;



//码流类型  2015-9-7
typedef enum _OWSP_StreamType
{
	OWSP_STREAM_MAIN	= 0,        //请求主码流
	OWSP_STREAM_SUB	= 1,        //请求次码流1
	OWSP_STREAM_SUB1	= 2,        //请求次码流2
	OWSP_STREAM_VOD	= 3,        //请求录像文件
	OWSP_MODE_SETTING	= 4         //远程配置模式， 
} OWSP_StreamType;

//数据类型
typedef enum _OWSP_StreamDataType
{
	OWSP_VIDEO_DATA	= 0,    // video data only
	OWSP_AUDIO_DATA	= 1,    // audio data only
	OWSP_MIXED_DATA	= 2     // video & audio data
} OWSP_StreamDataType;

// 播放控制命令
typedef enum _OWSP_PlayCommand
{
	PlayCommandStart  = 1,  //播放
	PlayCommandPause  = 2,  //暂停
	PlayCommandResume = 3,  //继续
	PlayCommandStop   = 4   //停止
} OWSP_PlayCommand;

/* the common packet header, must be placed in front of any packets. */
typedef struct _OwspPacketHeader
{
	u_int32 packet_length;		//length of the following packet, donot include this header
	u_int32 packet_seq;			//packet sequence 包序号,每发送一个包就自增
	
} OwspPacketHeader;

/////////////////////////////////////////////////////////////////////////
//For TLV 
//////////////////////////////////////////////////////////////////////////
struct _TLV_Header {
	u_int16 tlv_type;
	u_int16 tlv_len;
};
//__attribute ((packed));
typedef struct _TLV_Header  TLV_HEADER;

/* version info: remote -> streaming server.  No response need */
// TLV_T: TLV_T_VERSION_INFO_ANSWER
// TLV_L: sizeof(TLV_V_VersionInfoRequest)
typedef struct _TLV_V_VersionInfoRequest
{
	u_int16   versionMajor;		// major version
	u_int16   versionMinor;		// minor version
}TLV_V_VersionInfoRequest;

// TLV_T: TLV_T_VERSION_INFO_ANSWER
// TLV_L: sizeof(TLV_V_VersionInfoResponse)
typedef struct _TLV_V_VersionInfoResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
}TLV_V_VersionInfoResponse;

/* login request: remote -> streaming server */
typedef struct _TLV_V_LoginRequest
{
	char userName[STR_LEN_32];			//用户名, 后面不足部分为数字0      (为ASCII字符串)
	char password[STR_LEN_16];			//密码, 后面不足部分为数字0        (为ASCII字符串) 
	u_int32 deviceId;					//设备ID. CS模式下由服务器统一分配, P2P模式下为固定值
	u_int8  flag;						//should be set to 1 to be compatible with the previous version.
	u_int8  channel;					//channel
	//u_int8  reserve[2];
	u_int8	streamMode;
	u_int8	dataType;
} TLV_V_LoginRequest;


/* login response, streaming server -> remote */
typedef struct _TLV_V_LoginResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_LoginResponse;

 
/* send data request, streaming server -> remote. 
 * Now this command is ignored, the remote will send data to server actively and immidietely after logining.*/
typedef struct _TLV_V_SendDataRequest
{
	u_int32 deviceId;			//device id generating by the remote device
	u_int8  videoChannel;	
	u_int8  audioChannel;   
	u_int16 reserve;
} TLV_V_SendDataRequest;

/* send data response, remote -> streaming server */
typedef struct _TLV_V_SendDataResponse
{
	u_int16 result;			//result of send data request
	u_int16 reserve;
} TLV_V_SendDataResponse;

/* suspend sending data request, streaming server -> remote */
typedef struct _TLV_V_SuspendSendDataRequest
{
	u_int32 deviceId;			//device id generating by the remote device
	u_int8  videoChannel;
	u_int8  audioChannel; 
	u_int16 reserve;
} TLV_V_SuspendSendDataRequest;

/* suspend sending data response, remote -> streaming server */
typedef struct _TLV_V_SuspendSendDataResponse
{
	u_int16 result;			//result of send data request
	u_int16 reserve;
} TLV_V_SuspendSendDataResponse;



/* specify the format of video, this info is sent to server immidiately after StreamDataFormat*/
typedef struct _OWSP_VideoDataFormat
{
	u_int32 codecId;			//FOUR CC code，’H264’
	u_int32 bitrate;			//bps
	u_int16 width;				//image widht
	u_int16 height;				//image height
	u_int8 framerate;			//fps
	u_int8 colorDepth;			//should be 24 bits 
	u_int16 reserve;		

} OWSP_VideoDataFormat;

/* specify the format of audio, this info is sent to server immidiately after StreamDataFormat or VideoDataFormat*/
typedef struct _OWSP_AudioDataFormat
{
	u_int32 samplesPerSecond;		//samples per second
	u_int32 bitrate;			//bps
	u_int16 waveFormat;			//wave format, such as WAVE_FORMAT_PCM,WAVE_FORMAT_MPEGLAYER3
	u_int16 channelNumber;		//audio channel number
	u_int16 blockAlign;			//block alignment defined by channelSize * (bitsSample/8)
	u_int16 bitsPerSample;			//bits per sample
	u_int16 frameInterval;		//interval between frames, in milliseconds
	u_int16 reserve;

} OWSP_AudioDataFormat;

/* this format should be sent to the server before any other stream data,
 Plus if any format of video/audio has changed, it should send this info to server at the first time.
 followed by VideoDataFormat/AudioDataFormat*/
typedef struct _TLV_V_StreamDataFormat
{
	u_int8 videoChannel;					//视频通道号
	u_int8 audioChannel;					//音频通道号
	u_int8 dataType;							//流数据类型, 取值见StreamDataType
	u_int8 reserve;								//保留
	OWSP_VideoDataFormat videoFormat;	//视频格式
	OWSP_AudioDataFormat audioFormat;  //音频格式
} TLV_V_StreamDataFormat;


/* 视频帧信息 TLV */
typedef struct _TLV_V_VideoFrameInfo
{
	u_int8  channelId;			//通道ID
	u_int8  reserve;				//备用
	u_int16 checksum;				//校验和.目前为0未用
	u_int32 frameIndex;			//视频帧序号
	u_int32 time;				    //时间戳.
} TLV_V_VideoFrameInfo;

//之后是视频数据TLV, V部分是视频编码后的Raw Data.

/* 扩展视频帧信息 TLV, 当视频数据>64K时使用 */
typedef struct _TLV_V_VideoFrameInfoEx
{
	u_int8  channelId;			//通道ID
	u_int8  reserve;				//备用
	u_int16 checksum;				//校验和.目前为0未用
	u_int32 frameIndex;			//视频帧序号
	u_int32 time;				    //时间戳.
	u_int32 dataSize;				//视频数据长度
} TLV_V_VideoFrameInfoEx;

//之后是若干个视频数据TLV, V部分是视频编码后的Raw Data.


/* 音频信息 TLV */
typedef struct _TLV_V_AudioInfo
{
	u_int8 channelId;			//channel id
	u_int8  reserve;			//备用
	u_int16 checksum;			//checksum of audio data.
	u_int32 time;					// specify the time when this audio data is created.
} TLV_V_AudioInfo;

//之后是音频数据TLV, V部分就是音频编码后的Raw Data.

/* 扩展控制协议, 包括云台及TV控制 */
typedef struct _TLV_V_ControlRequest
{
		u_int32 deviceId;			// device id generating by the remote device
		u_int8  channel;			// channel id 
		u_int8  cmdCode;			// 控制命令字，参见_PTZCode
		u_int16 size;				// 控制参数数据长度,如果size==0 表示无控制参数
} TLV_V_ControlRequest;

//u_int8 * data;		//array of data followed.
// size = sizeof(PTZArgData);
//如果是上下左右，牵涉到速度的话，有水平速度arg1，垂直速度arg2；
//如果是预置位的话，操作第几个预制位使用arg1标明
//如果是清除预置位，操作第几个预置位使用arg1标明，如果0xffffffff表示清除全部
//如果是自动巡航，arg1=1表示启动，0表示停止
typedef struct _ControlArgData
{		
		u_int32 arg1;
		u_int32 arg2;
		u_int32 arg3;
		u_int32 arg4;
} ControlArgData;

/* 云台请求响应 */
typedef struct _TLV_V_ControlResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_ControlResponse;

/* 
  通道请求协议 
  Streaming server -> Device
*/
typedef struct _TLV_V_ChannelRequest
{
	u_int32 deviceId;
	u_int8  sourceChannel;	//源通道ID
	u_int8  destChannel;		//切换的目的通道ID
	u_int8	reserve[2];		
} TLV_V_ChannelRequest;

/*
  通道请求响应
  Device -> Streaming server
  message: MSG_CMD_CHANNEL_RESPONSE
*/
typedef struct _TLV_V_ChannelResponse
{
  u_int16 result;					//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
  u_int8	currentChannel;	//如果不支持的通道，则返回当前通道号
	u_int8 reserve;	
} TLV_V_ChannelResponse;


/* 
	通道挂起协议 
  Streaming server -> Device 
  message: MSG_CMD_CHANNEL_SUSPEND
*/
typedef struct _TLV_V_ChannelSuspendRequest
{
	u_int8  channelId;	//Chanel id
	u_int8  reserve[3];	
} TLV_V_ChannelSuspendRequest;

/*
  通道挂起响应
  Device -> Streaming server
  message: MSG_CMD_SUSPEND_RESPONSE
*/
typedef struct _TLV_V_ChannelSuspendResponse
{
  u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_ChannelSuspendResponse;


/*
  心跳包
  Device -> Streaming server
  message: MSG_CMD_DEVICE_KEEP_ALIVE
*/
typedef struct _TLV_V_KeepAliveRequest
{
	u_int8  channelID;	//Channel id
	u_int8  reserve[3];	
} TLV_V_KeepAliveRequest;

/*
  心跳包响应
  Streaming server -> Device
  message: MSG_CMD_KEEP_ALIVE_ANSWER
*/
typedef struct _TLV_V_KeepAliveResponse
{
  u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_KeepAliveResponse;

/* 扩展报警协议，设备发到服务器 */
typedef struct _TLV_V_AlertRequest
{
  u_int32  	deviceId;   	// device id generating by the remote device
  u_int8   	channelId;   	// channel id 
  u_int8  	alertType;   	// 报警种类，参见 _AlertTypeCode
  u_int8  	alertLevel;   // 报警级别，参见 _AlertLevelCode
	u_int8  	reserve;    	//保留
  u_int8   	localTime[14];			//报警时本地时间字符串，格式为yyyymmddhhmmss,如"20080919132059"代表2008年9月19日13点20分59秒，时间精度为秒
  u_int16  	size;     		// array of data size followed，default =  0
} TLV_V_AlertRequest;

/* 报警请求响应，服务器发送到设备 */
typedef struct _TLV_V_AlertResponse
{
 u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
 u_int16 reserve;
} TLV_V_AlertResponse;


/* 日期定义 */
typedef struct _OWSP_DATE
{
	u_int16 	m_year;			//年,2009
	u_int8		m_month;		//月,1-12
	u_int8		m_day;			//日,1-31
}OWSP_DATE;

/* 时间定义 */
typedef struct _OWSP_TIME
{
	u_int8		m_hour;			//0-24
	u_int8		m_minute;		//0-59
	u_int8		m_second;		//0-59
	u_int16		m_microsecond;	//毫秒	0-1000
}OWSP_TIME;


/* DVS报告设备信息 */
typedef struct _TLV_V_DVSInfoRequest
{
	char		companyIdentity[STR_LEN_16];			//公司识别码,最多16个字符,后面不足部分为数字0      (为ASCII字符串)
	char   		equipmentIdentity[STR_LEN_16];			//设备识别码,本字段中为DVS的物理地址,即MAC地址,后面不足部分为数字0  (为ASCII字符串)
	char		equipmentName[STR_LEN_16];				//设备名称,最多16个字符,后面不足部分为数字0        (为ASCII字符串)
	char		equipmentVersion[STR_LEN_16];			//设备的软件版本,最多16个字符, 后面不足部分为数字0 (为ASCII字符串)
	OWSP_DATE	equipmentDate;							//设备的出厂日期20090120 
	u_int8		channleNumber;			//设备支持多少个通道
	u_int8		reserve1;						//保留
	u_int8		reserve2;						//保留
	u_int8		reserve3;						//保留
} TLV_V_DVSInfoRequest;

/* DVS报告设备信息应答 */
typedef struct _TLV_V_DVSInfoResponse
{
	u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_DVSInfoResponse;


/* 手机报告设备信息 */
typedef struct _TLV_V_PhoneInfoRequest
{
	u_int8   	equipmentIdentity[STR_LEN_16];		//设备识别码,本字段中为DVS的物理地址,即MAC地址
	u_int8   	equipmentOS[STR_LEN_16];						//手机的操作系统
	u_int8		reserve1;						//保留
	u_int8		reserve2;						//保留
	u_int8		reserve3;						//保留
	u_int8		reserve4;						//保留
} TLV_V_PhoneInfoRequest;

/* 手机报告设备信息应答 */
typedef struct _TLV_V_PhoneInfoResponse
{
	u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_PhoneInfoResponse;

/////////////////////////////////////////////////////////////////////////
//For TLV 
//////////////////////////////////////////////////////////////////////////
struct _TLV {
    u_int16 tlv_type;
    u_int16 tlv_len;
    u_int8  tlv_data[0];
};				//	 __attribute ((packed))
typedef struct _TLV  TLV;


#define FILEFLAG	"DSV"
//////////////////////////////////////////////////////////////////////////
//For vod streaming  only Keyframe 
//////////////////////////////////////////////////////////////////////////
typedef struct _TLV_V_FileAttributeData
{
	u_int32 totalframes;
	u_int32 totaltimes;
}TLV_V_FileAttributeData;

typedef struct _TLV_V_StreamIndexDataHeader
{
	u_int32 count;			//
	u_int32 reserve;		//在文件
	u_int32 datasize;		//
}TLV_V_StreamIndexDataHeader;

typedef struct _TLV_V_StreamIndexData
{
	u_int32 timestamp;
	u_int32 pos;		//在文件
}TLV_V_StreamIndexData;

typedef struct _TLV_V_StreamEndData
{
	u_int32 timestamp;
	u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_StreamEndData;

typedef struct _TLV_V_StreamFileDataHeader
{
	u_int32 timestamp;
}TLV_V_StreamFileDataHeader;


#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
//	2015-9-7	录像文件回放
//////////////////////////////////////////////////////////////////////////

#pragma pack(push)
#pragma pack(1)


typedef struct _OWSP_DateTime
{
	u_int16 m_year;			//年,2009
	u_int8	m_month;		//月,1-12
	u_int8	m_day;			//日,1-31
	u_int8	m_hour;			//0-24
	u_int8	m_minute;		//0-59
	u_int8	m_second;		//0-59
} OWSP_DateTime;

typedef struct _TLV_V_SearchRecordRequest
{
	u_int32 deviceId;           //设备编号（默认为0）
	u_int8  channel;           //通道号
	u_int8  recordTypeMask;    //录像类型掩码 0x01 = 开关量告警录像, 0x02 = 移动侦测录像, 0x04 = 定时录像, 0x08 = 手动录像
	u_int8	count;            //返回最大记录个数
	OWSP_DateTime startTime;   //查询起始时间
	OWSP_DateTime endTime;   //查询终止时间
	u_int8  reserve[3];
} TLV_V_SearchRecordRequest;


typedef struct _TLV_V_SearchRecordResponse
{
	u_int8	result;                //结果
	u_int8	count;                //查询结果记录数
	u_int8	reserve;
} TLV_V_SearchRecordResponse;

typedef struct _TLV_V_RecordInfo
{
	u_int32          deviceId;
	OWSP_DateTime	startTime;
	OWSP_DateTime	endTime;
	u_int8	        channel;
	u_int8           recordTypeMask;    //录像类型掩码 0x01 = 开关量告警录像, 0x02 = 移动侦测录像, 0x04 = 定时录像, 0x08 = 手动录像;
	u_int8           reserve[2];
} TLV_V_RecordInfo;


typedef struct _TLV_V_PlayRecordRequest
{
	u_int32       deviceId;
	OWSP_DateTime	startTime;         //暂停、继续、停止命令无效
	u_int8        channel;
	u_int8        command;            //回放控制命令
	u_int8        reserve;

} TLV_V_PlayRecordRequest;


typedef struct _TLV_V_PlayRecordResponse
{
	u_int8	result;
	u_int8	reserve;
} TLV_V_PlayRecordResponse;

#pragma pack(pop)

#endif