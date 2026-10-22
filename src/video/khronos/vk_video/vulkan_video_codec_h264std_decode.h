#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_h264std_decode 1

#ضمن "vulkan_video_codec_h264std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#تعریف_کړه STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_LIST_اندازه 2U

تعريفنوع تعداد Std_Video_Decode_H264_ډګر_ترتیب_شمېر {
    STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_سر = 0,
    STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_ډګر_ترتیب_شمېر;

تعريفنوع بنية StdVideoDecodeH264PictureInfoFlags {
    uint32_t    ډګر_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_ډګر_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_ډګر_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_سېټ_id;
    uint8_t                               pic_parameter_سېټ_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              چوکاټ_عدد;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_LIST_اندازه];
} StdVideoDecodeH264PictureInfo;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    سر_ډګر_flag : 1;
    uint32_t    bottom_ډګر_flag : 1;
    uint32_t    کارول_شوی_for_long_غړی_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                چوکاټ_عدد_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_ډګر_ترتیب_شمېر_LIST_اندازه];
} StdVideoDecodeH264ReferenceInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
