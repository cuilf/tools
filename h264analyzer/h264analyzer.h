/*************************************************************************
    > File Name: h264analyzer.h
    > Author: cuilf
    > Mail: cuilongfeiii@163.com 
    > Created Time: 04/08/17 - 16:42
 ************************************************************************/
#ifndef __H264ANALYZER_H__
#define __H264ANALYZER_H__

typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;
typedef __INT32_TYPE__ int32_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __INT16_TYPE__ int16_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __INT8_TYPE__  int8_t;
typedef __UINT8_TYPE__  uint8_t;



#define NALU_TYPE_MASK 0x1f
#define SLICE_TYPE_MASK 0x0e
#define NALU_HDR_LEN    4


#define bool int
#define true 1
#define false 0


typedef enum
{
  AM_VIDEO_FRAME_TYPE_NONE  = 0x0,
  AM_VIDEO_FRAME_TYPE_IDR   = 0x1,
  AM_VIDEO_FRAME_TYPE_I     = 0x2,   //regular I-frame (non IDR)
  AM_VIDEO_FRAME_TYPE_P     = 0x3,
  AM_VIDEO_FRAME_TYPE_B     = 0x4,
  AM_VIDEO_FRAME_TYPE_MJPEG = 0x9,
  AM_VIDEO_FRAME_TYPE_SJPEG = 0xa,    //still JPEG
} AM_VIDEO_FRAME_TYPE;



static AM_VIDEO_FRAME_TYPE frame_type_anyalyze(uint8_t *data);


#endif 
