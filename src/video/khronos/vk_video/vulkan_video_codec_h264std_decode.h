#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#تعریف_کن VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_h264std_decode 1

#ضمن "vulkan_video_codec_h264std.h"

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخه_1_0_0
#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#تعریف_کن STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_LIST_اندازه 2U

تعريفنوع تعداد Std_Video_Decode_H264_فیلد_ترتیب_شمار {
    STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_بالاترین = 0,
    STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_فیلد_ترتیب_شمار;

تعريفنوع بنية StdVideoDecodeH264PictureInfoFlags {
    uint32_t    فیلد_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_فیلد_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_فیلد_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_مجموعه_id;
    uint8_t                               pic_parameter_مجموعه_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              قاب_رقم;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_LIST_اندازه];
} StdVideoDecodeH264PictureInfo;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    بالاترین_فیلد_flag : 1;
    uint32_t    bottom_فیلد_flag : 1;
    uint32_t    استفاده_شده_for_long_جمله_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                قاب_رقم_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_فیلد_ترتیب_شمار_LIST_اندازه];
} StdVideoDecodeH264ReferenceInfo;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
