#अगर_अघोषित VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#घोषणा VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#घोषणा vulkan_video_codec_av1std_encode 1

#समावेश "vulkan_video_codec_av1std.h"

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_VERSION_1_0_0
#घोषणा VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

प्रकार काष्ठा StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     बफर_delay_लंबाई_minus_1;
    uint8_t     बफर_removal_time_लंबाई_minus_1;
    uint8_t     frame_presentation_time_लंबाई_minus_1;
    uint8_t     reserved1;
    uint32_t    अंक_units_in_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

प्रकार काष्ठा StdVideoEncodeAV1ExtensionHeader {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} StdVideoEncodeAV1ExtensionHeader;

प्रकार काष्ठा StdVideoEncodeAV1OperatingPointInfoFlags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    निचला_delay_mode_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} StdVideoEncodeAV1OperatingPointInfoFlags;

प्रकार काष्ठा StdVideoEncodeAV1OperatingPointInfo {
    StdVideoEncodeAV1OperatingPointInfoFlags    flags;
    uint16_t                                    operating_point_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_बफर_delay;
    uint32_t                                    encoder_बफर_delay;
    uint8_t                                     initial_display_delay_minus_1;
} StdVideoEncodeAV1OperatingPointInfo;

प्रकार काष्ठा StdVideoEncodeAV1PictureInfoFlags {
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
    uint32_t    show_frame : 1;
    uint32_t    showable_frame : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

प्रकार काष्ठा StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    StdVideoAV1FrameType                       frame_type;
    uint32_t                                   frame_presentation_time;
    uint32_t                                   current_frame_id;
    uint8_t                                    order_hint;
    uint8_t                                    primary_ref_frame;
    uint8_t                                    refresh_frame_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_width_minus_1;
    uint16_t                                   render_height_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    StdVideoAV1TxMode                          TxMode;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_order_hint[STD_VIDEO_AV1_अंक_REF_FRAMES];
    int8_t                                     ref_frame_idx[STD_VIDEO_AV1_REFS_PER_FRAME];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_frame_id_minus_1[STD_VIDEO_AV1_REFS_PER_FRAME];
    स्थिर StdVideoAV1TileInfo*                 pTileInfo;
    स्थिर StdVideoAV1Quantization*             pQuantization;
    स्थिर StdVideoAV1Segmentation*             pSegmentation;
    स्थिर StdVideoAV1LoopFilter*               pLoopFilter;
    स्थिर StdVideoAV1CDEF*                     pCDEF;
    स्थिर StdVideoAV1LoopRestoration*          pLoopRestoration;
    स्थिर StdVideoAV1GlobalMotion*             pGlobalMotion;
    स्थिर StdVideoEncodeAV1ExtensionHeader*    pExtensionHeader;
    स्थिर uint32_t*                            p_बफर_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

प्रकार काष्ठा StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_frame_end_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

प्रकार काष्ठा StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   RefFrameId;
    StdVideoAV1FrameType                       frame_type;
    uint8_t                                    OrderHint;
    uint8_t                                    reserved1[3];
    स्थिर StdVideoEncodeAV1ExtensionHeader*    pExtensionHeader;
} StdVideoEncodeAV1ReferenceInfo;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
