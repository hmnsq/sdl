#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_h264std_decode 1

#ضمن "vulkan_video_codec_h264std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#وصف_ڪريو STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_LIST_سائيز 2U

تعريفنوع تعداد Std_Video_Decode_H264_ميدان_ترتيب_ڳڻپ {
    STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_چوٽي = 0,
    STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_ميدان_ترتيب_ڳڻپ;

تعريفنوع بنية StdVideoDecodeH264PictureInfoFlags {
    uint32_t    ميدان_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_ميدان_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_ميدان_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_سيٽ_id;
    uint8_t                               pic_parameter_سيٽ_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              چوکٺو_انگ;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ترتيب_Cnt[STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_LIST_سائيز];
} StdVideoDecodeH264PictureInfo;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    چوٽي_ميدان_flag : 1;
    uint32_t    bottom_ميدان_flag : 1;
    uint32_t    استعمال_ٿيل_for_long_رڪن_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                چوکٺو_انگ_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ترتيب_Cnt[STD_VIDEO_DECODE_H264_ميدان_ترتيب_ڳڻپ_LIST_سائيز];
} StdVideoDecodeH264ReferenceInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
