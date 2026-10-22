#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_vp9std_decode 1

#అన్తర్భావ "vulkan_video_codec_vp9std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

రకనిర్వచనం నిర్మాణం StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_బహుళకం : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_ఎగువ_precision_mv : 1;
    uint32_t    refresh_చట్రం_context : 1;
    uint32_t    చట్రం_parallel_decoding_బహుళకం : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_చట్రం : 1;
    uint32_t    Use_Prev_చట్రం_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    Std_Video_VP9_చట్రం_Type                 చట్రం_type;
    uint8_t                              చట్రం_context_idx;
    uint8_t                              reset_చట్రం_context;
    uint8_t                              refresh_చట్రం_flags;
    uint8_t                              ref_చట్రం_sign_bias_ముసుగు;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              పునాది_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_నిలువుల_సంఖ్య_log2;
    uint8_t                              tile_అడ్డువరుసలు_log2;
    uint16_t                             reserved1[3];
    స్థిరరాశి StdVideoVP9ColorConfig*        pColorConfig;
    స్థిరరాశి StdVideoVP9LoopFilter*         pLoopFilter;
    స్థిరరాశి StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
