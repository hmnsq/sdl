#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_vp9std_decode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_vp9std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_ਬਹੁਲਕ : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_ਉੱਚਾ_precision_mv : 1;
    uint32_t    refresh_ਚੌਖਟਾ_context : 1;
    uint32_t    ਚੌਖਟਾ_parallel_decoding_ਬਹੁਲਕ : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_ਚੌਖਟਾ : 1;
    uint32_t    Use_Prev_ਚੌਖਟਾ_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_ਚੌਖਟਾ_Type                 ਚੌਖਟਾ_type;
    uint8_t                              ਚੌਖਟਾ_context_idx;
    uint8_t                              reset_ਚੌਖਟਾ_context;
    uint8_t                              refresh_ਚੌਖਟਾ_flags;
    uint8_t                              ref_ਚੌਖਟਾ_sign_bias_ਨਕਾਬ;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              ਅਧਾਰ_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_ਖਾਨੇ_ਗਿਣਤੀ_log2;
    uint8_t                              tile_ਪੰਕਤੀਆਂ_log2;
    uint16_t                             reserved1[3];
    ਅਚਲ StdVideoVP9ColorConfig*        pColorConfig;
    ਅਚਲ StdVideoVP9LoopFilter*         pLoopFilter;
    ਅਚਲ StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
