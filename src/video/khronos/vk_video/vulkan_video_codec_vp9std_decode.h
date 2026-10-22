#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#تعریف_کن VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

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



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_vp9std_decode 1

#ضمن "vulkan_video_codec_vp9std.h"

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخه_1_0_0
#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

تعريفنوع بنية StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_نما : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_بالا_precision_mv : 1;
    uint32_t    refresh_قاب_context : 1;
    uint32_t    قاب_parallel_decoding_نما : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_قاب : 1;
    uint32_t    Use_Prev_قاب_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_قاب_Type                 قاب_type;
    uint8_t                              قاب_context_idx;
    uint8_t                              reset_قاب_context;
    uint8_t                              refresh_قاب_flags;
    uint8_t                              ref_قاب_sign_bias_ماسک;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              پایه_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_تعداد_ستون_log2;
    uint8_t                              tile_ردیفها_log2;
    uint16_t                             reserved1[3];
    ثابت StdVideoVP9ColorConfig*        pColorConfig;
    ثابت StdVideoVP9LoopFilter*         pLoopFilter;
    ثابت StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
