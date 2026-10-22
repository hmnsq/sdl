#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_av1std_encode 1

#ضمن "vulkan_video_codec_av1std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

تعريفنوع بنية StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     بفر_delay_ڊيگهائي_minus_1;
    uint8_t     بفر_removal_وقت_ڊيگهائي_minus_1;
    uint8_t     چوکٺو_presentation_وقت_ڊيگهائي_minus_1;
    uint8_t     reserved1;
    uint32_t    انگ_units_اندريون_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

تعريفنوع بنية Std_Video_Encode_AV1_Extension_سرو {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_سرو;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_نقطو_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    هيٺيون_delay_گهڻائي_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_نقطو_Info_Flags;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_نقطو_Info {
    Std_Video_Encode_AV1_Operating_نقطو_Info_Flags    flags;
    uint16_t                                    operating_نقطو_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_بفر_delay;
    uint32_t                                    encoder_بفر_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_نقطو_Info;

تعريفنوع بنية StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_گهڻائي : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_چوکٺو_سائيز_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    چوکٺو_سائيز_override_flag : 1;
    uint32_t    بفر_removal_وقت_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    چوکٺو_refs_short_signaling : 1;
    uint32_t    allow_مٿاهون_precision_mv : 1;
    uint32_t    is_motion_گهڻائي_switchable : 1;
    uint32_t    use_ref_چوکٺو_mvs : 1;
    uint32_t    disable_چوکٺو_پڇاڙي_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_سيٽ : 1;
    uint32_t    skip_گهڻائي_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_معلومات : 1;
    uint32_t    استعمال_ڪري_Lr : 1;
    uint32_t    استعمال_ڪري_Chroma_Lr : 1;
    uint32_t    show_چوکٺو : 1;
    uint32_t    showable_چوکٺو : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_چوکٺو_Type                       چوکٺو_type;
    uint32_t                                   چوکٺو_presentation_وقت;
    uint32_t                                   current_چوکٺو_id;
    uint8_t                                    ترتيب_hint;
    uint8_t                                    primary_ref_چوکٺو;
    uint8_t                                    refresh_چوکٺو_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_ويڪر_minus_1;
    uint16_t                                   render_اوچائي_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_گهڻائي                          Tx_گهڻائي;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ترتيب_hint[STD_VIDEO_AV1_انگ_REF_چوکٺا];
    int8_t                                     ref_چوکٺو_idx[STD_VIDEO_AV1_REFS_في_چوکٺو];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_چوکٺو_id_minus_1[STD_VIDEO_AV1_REFS_في_چوکٺو];
    ثابت StdVideoAV1TileInfo*                 pTileInfo;
    ثابت StdVideoAV1Quantization*             pQuantization;
    ثابت StdVideoAV1Segmentation*             pSegmentation;
    ثابت StdVideoAV1LoopFilter*               pLoopFilter;
    ثابت StdVideoAV1CDEF*                     pCDEF;
    ثابت StdVideoAV1LoopRestoration*          pLoopRestoration;
    ثابت StdVideoAV1GlobalMotion*             pGlobalMotion;
    ثابت Std_Video_Encode_AV1_Extension_سرو*    p_Extension_سرو;
    ثابت uint32_t*                            p_بفر_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_چوکٺو_پڇاڙي_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_چوکٺو_Id;
    Std_Video_AV1_چوکٺو_Type                       چوکٺو_type;
    uint8_t                                    ترتيب_Hint;
    uint8_t                                    reserved1[3];
    ثابت Std_Video_Encode_AV1_Extension_سرو*    p_Extension_سرو;
} StdVideoEncodeAV1ReferenceInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
