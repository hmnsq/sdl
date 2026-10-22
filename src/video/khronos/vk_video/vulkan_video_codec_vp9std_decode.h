#अगर_अघोषित VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_
#घोषणा VULKAN_VIDEO_CODEC_VP9STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// vulkan_video_codec_vp9std_decode is a preprocessor guard. Do not pass it to API calls.
#घोषणा vulkan_video_codec_vp9std_decode 1

#समावेश "vulkan_video_codec_vp9std.h"

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_VERSION_1_0_0
#घोषणा VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"

प्रकार काष्ठा StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_mode : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_ऊपरी_precision_mv : 1;
    uint32_t    refresh_frame_context : 1;
    uint32_t    frame_parallel_decoding_mode : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_frame : 1;
    uint32_t    Use_पूर्व_Frame_Mvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

प्रकार काष्ठा StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    StdVideoVP9FrameType                 frame_type;
    uint8_t                              frame_context_idx;
    uint8_t                              reset_frame_context;
    uint8_t                              refresh_frame_flags;
    uint8_t                              ref_frame_sign_bias_mask;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              base_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_cols_log2;
    uint8_t                              tile_rows_log2;
    uint16_t                             reserved1[3];
    स्थिर StdVideoVP9ColorConfig*        pColorConfig;
    स्थिर StdVideoVP9LoopFilter*         pLoopFilter;
    स्थिर StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
