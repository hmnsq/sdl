#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_vp9std_decode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_vp9std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_ಬಹುಲಕ : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_ಮೇಲಿನ_precision_mv : 1;
    uint32_t    refresh_ಚೌಕಟ್ಟು_context : 1;
    uint32_t    ಚೌಕಟ್ಟು_parallel_decoding_ಬಹುಲಕ : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_ಚೌಕಟ್ಟು : 1;
    uint32_t    Use_Prev_ಚೌಕಟ್ಟು_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_ಚೌಕಟ್ಟು_Type                 ಚೌಕಟ್ಟು_type;
    uint8_t                              ಚೌಕಟ್ಟು_context_idx;
    uint8_t                              reset_ಚೌಕಟ್ಟು_context;
    uint8_t                              refresh_ಚೌಕಟ್ಟು_flags;
    uint8_t                              ref_ಚೌಕಟ್ಟು_sign_bias_ಮುಖವಾಡ;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              ತಳ_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_log2;
    uint8_t                              tile_ಅಡ್ಡಸಾಲುಗಳು_log2;
    uint16_t                             reserved1[3];
    ಸ್ಥಿರಾಂಕ StdVideoVP9ColorConfig*        pColorConfig;
    ಸ್ಥಿರಾಂಕ StdVideoVP9LoopFilter*         pLoopFilter;
    ಸ್ಥಿರಾಂಕ StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
