#अगर_अघोषित VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#घोषणा VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#घोषणा vulkan_video_codec_av1std_decode 1

#समावेश "vulkan_video_codec_av1std.h"

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_VERSION_1_0_0
#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

प्रकार काष्ठा StdVideoDecodeAV1PictureInfoFlags {
    uint32_t    error_resilient_mode : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_frame_आकार_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    frame_आकार_override_flag : 1;
    uint32_t    बफर_removal_time_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    frame_refs_short_signaling : 1;
    uint32_t    allow_ऊपरी_precision_mv : 1;
    uint32_t    is_motion_mode_switchable : 1;
    uint32_t    use_ref_frame_mvs : 1;
    uint32_t    disable_frame_end_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_set : 1;
    uint32_t    reference_select : 1;
    uint32_t    skip_mode_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_तथ्य : 1;
    uint32_t    UsesLr : 1;
    uint32_t    usesChromaLr : 1;
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

प्रकार काष्ठा StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    StdVideoAV1FrameType                 frame_type;
    uint32_t                             current_frame_id;
    uint8_t                              OrderHint;
    uint8_t                              primary_ref_frame;
    uint8_t                              refresh_frame_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    StdVideoAV1TxMode                    TxMode;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              SkipModeFrame[STD_VIDEO_AV1_SKIP_MODE_FRAMES];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              OrderHints[STD_VIDEO_AV1_अंक_REF_FRAMES];
    uint32_t                             expectedFrameId[STD_VIDEO_AV1_अंक_REF_FRAMES];
    स्थिर StdVideoAV1TileInfo*           pTileInfo;
    स्थिर StdVideoAV1Quantization*       pQuantization;
    स्थिर StdVideoAV1Segmentation*       pSegmentation;
    स्थिर StdVideoAV1LoopFilter*         pLoopFilter;
    स्थिर StdVideoAV1CDEF*               pCDEF;
    स्थिर StdVideoAV1LoopRestoration*    pLoopRestoration;
    स्थिर StdVideoAV1GlobalMotion*       pGlobalMotion;
    स्थिर StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

प्रकार काष्ठा StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_frame_end_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

प्रकार काष्ठा StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                frame_type;
    uint8_t                                RefFrameSignBias;
    uint8_t                                OrderHint;
    uint8_t                                SavedOrderHints[STD_VIDEO_AV1_अंक_REF_FRAMES];
} StdVideoDecodeAV1ReferenceInfo;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
