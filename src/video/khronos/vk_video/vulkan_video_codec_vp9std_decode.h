#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

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



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_vp9std_decode 1

#ضمن "vulkan_video_codec_vp9std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

تعريفنوع بنية StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_گهڻائي : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_مٿاهون_precision_mv : 1;
    uint32_t    refresh_چوکٺو_context : 1;
    uint32_t    چوکٺو_parallel_decoding_گهڻائي : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_چوکٺو : 1;
    uint32_t    Use_Prev_چوکٺو_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_چوکٺو_Type                 چوکٺو_type;
    uint8_t                              چوکٺو_context_idx;
    uint8_t                              reset_چوکٺو_context;
    uint8_t                              refresh_چوکٺو_flags;
    uint8_t                              ref_چوکٺو_sign_bias_نقاب;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              بنياد_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_کانن_ڳڻپ_log2;
    uint8_t                              tile_صفون_log2;
    uint16_t                             reserved1[3];
    ثابت StdVideoVP9ColorConfig*        pColorConfig;
    ثابت StdVideoVP9LoopFilter*         pLoopFilter;
    ثابت StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
