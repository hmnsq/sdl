#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_vp9std_decode 1

#अन्तर्भाव "vulkan_video_codec_vp9std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

प्रकारनिर्देश संरचना StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_बहुलकम् : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_उच्चः_precision_mv : 1;
    uint32_t    refresh_frame_context : 1;
    uint32_t    frame_parallel_decoding_बहुलकम् : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_frame : 1;
    uint32_t    Use_पूर्व_Frame_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    StdVideoVP9FrameType                 frame_type;
    uint8_t                              frame_context_idx;
    uint8_t                              reset_frame_context;
    uint8_t                              refresh_frame_flags;
    uint8_t                              ref_frame_sign_bias_आवरणम्;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              आधारः_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_स्तम्भसङ्ख्या_log2;
    uint8_t                              tile_पङ्क्तिकाः_log2;
    uint16_t                             reserved1[3];
    ध्रुव StdVideoVP9ColorConfig*        pColorConfig;
    ध्रुव StdVideoVP9LoopFilter*         pLoopFilter;
    ध्रुव StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
