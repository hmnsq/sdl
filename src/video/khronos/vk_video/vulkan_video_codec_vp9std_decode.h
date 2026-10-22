#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_vp9std_decode 1

#شامل "vulkan_video_codec_vp9std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

قسمتعریف ساخت StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_منوال : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_بلند_precision_mv : 1;
    uint32_t    refresh_چوکھٹا_context : 1;
    uint32_t    چوکھٹا_parallel_decoding_منوال : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_چوکھٹا : 1;
    uint32_t    Use_پچھلا_چوکھٹا_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

قسمتعریف ساخت StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_چوکھٹا_Type                 چوکھٹا_type;
    uint8_t                              چوکھٹا_context_idx;
    uint8_t                              reset_چوکھٹا_context;
    uint8_t                              refresh_چوکھٹا_flags;
    uint8_t                              ref_چوکھٹا_sign_bias_نقاب;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              بنیاد_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_ستون_تعداد_log2;
    uint8_t                              tile_صفیں_log2;
    uint16_t                             reserved1[3];
    ثابت StdVideoVP9ColorConfig*        pColorConfig;
    ثابت StdVideoVP9LoopFilter*         pLoopFilter;
    ثابت StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
