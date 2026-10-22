#ifndef VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#define VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
வெளி "C" {
#endif



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codec_h264std_decode 1

#அந்தர்பாவ "vulkan_video_codec_h264std.h"

#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0
#define VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#define STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_LIST_SIZE 2U

வகைவரை எண்ணிக்கை Std_Video_Decode_H264_Field_Order_மொத்தம் {
    STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_உச்சி = 0,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_Field_Order_மொத்தம்;

வகைவரை கட்டமைப்பு StdVideoDecodeH264PictureInfoFlags {
    uint32_t    field_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_field_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_field_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

வகைவரை கட்டமைப்பு StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_set_id;
    uint8_t                               pic_parameter_set_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              frame_இலக்கம்;
    uint16_t                              idr_pic_id;
    int32_t                               PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_LIST_SIZE];
} StdVideoDecodeH264PictureInfo;

வகைவரை கட்டமைப்பு StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    உச்சி_field_flag : 1;
    uint32_t    bottom_field_flag : 1;
    uint32_t    used_for_long_term_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

வகைவரை கட்டமைப்பு StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                Frame_இலக்கம்;
    uint16_t                                reserved;
    int32_t                                 PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_மொத்தம்_LIST_SIZE];
} StdVideoDecodeH264ReferenceInfo;


#ifdef __cplusplus
}
#endif

#endif
