#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

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



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_vp9std_decode 1

#ضمن "vulkan_video_codec_vp9std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

تعريفنوع بنية StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_ډېرپېښ : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_لوړ_precision_mv : 1;
    uint32_t    refresh_چوکاټ_context : 1;
    uint32_t    چوکاټ_parallel_decoding_ډېرپېښ : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_چوکاټ : 1;
    uint32_t    Use_Prev_چوکاټ_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_چوکاټ_Type                 چوکاټ_type;
    uint8_t                              چوکاټ_context_idx;
    uint8_t                              reset_چوکاټ_context;
    uint8_t                              refresh_چوکاټ_flags;
    uint8_t                              ref_چوکاټ_sign_bias_ماسک;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              بنسټ_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_ستون_شمېر_log2;
    uint8_t                              tile_لیکې_log2;
    uint16_t                             reserved1[3];
    ثابت StdVideoVP9ColorConfig*        pColorConfig;
    ثابت StdVideoVP9LoopFilter*         pLoopFilter;
    ثابت StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
