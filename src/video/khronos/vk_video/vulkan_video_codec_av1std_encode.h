#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_av1std_encode 1

#ضمن "vulkan_video_codec_av1std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

تعريفنوع بنية StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     بفر_delay_اوږدتیا_minus_1;
    uint8_t     بفر_removal_وخت_اوږدتیا_minus_1;
    uint8_t     چوکاټ_presentation_وخت_اوږدتیا_minus_1;
    uint8_t     reserved1;
    uint32_t    عدد_units_دننه_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

تعريفنوع بنية Std_Video_Encode_AV1_Extension_سرلیک {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_سرلیک;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_ټکی_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    ټیټ_delay_ډېرپېښ_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_ټکی_Info_Flags;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_ټکی_Info {
    Std_Video_Encode_AV1_Operating_ټکی_Info_Flags    flags;
    uint16_t                                    operating_ټکی_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_بفر_delay;
    uint32_t                                    encoder_بفر_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_ټکی_Info;

تعريفنوع بنية StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_ډېرپېښ : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_چوکاټ_اندازه_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    چوکاټ_اندازه_override_flag : 1;
    uint32_t    بفر_removal_وخت_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    چوکاټ_refs_short_signaling : 1;
    uint32_t    allow_لوړ_precision_mv : 1;
    uint32_t    is_motion_ډېرپېښ_switchable : 1;
    uint32_t    use_ref_چوکاټ_mvs : 1;
    uint32_t    disable_چوکاټ_پای_ټکی_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_سېټ : 1;
    uint32_t    skip_ډېرپېښ_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_معلومات : 1;
    uint32_t    کاروي_Lr : 1;
    uint32_t    کاروي_Chroma_Lr : 1;
    uint32_t    show_چوکاټ : 1;
    uint32_t    showable_چوکاټ : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_چوکاټ_Type                       چوکاټ_type;
    uint32_t                                   چوکاټ_presentation_وخت;
    uint32_t                                   current_چوکاټ_id;
    uint8_t                                    ترتیب_hint;
    uint8_t                                    primary_ref_چوکاټ;
    uint8_t                                    refresh_چوکاټ_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_پلنوالی_minus_1;
    uint16_t                                   render_لوړوالی_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_ډېرپېښ                          Tx_ډېرپېښ;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ترتیب_hint[STD_VIDEO_AV1_عدد_REF_چوکاټونه];
    int8_t                                     ref_چوکاټ_idx[STD_VIDEO_AV1_REFS_فی_چوکاټ];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_چوکاټ_id_minus_1[STD_VIDEO_AV1_REFS_فی_چوکاټ];
    ثابت StdVideoAV1TileInfo*                 pTileInfo;
    ثابت StdVideoAV1Quantization*             pQuantization;
    ثابت StdVideoAV1Segmentation*             pSegmentation;
    ثابت StdVideoAV1LoopFilter*               pLoopFilter;
    ثابت StdVideoAV1CDEF*                     pCDEF;
    ثابت StdVideoAV1LoopRestoration*          pLoopRestoration;
    ثابت StdVideoAV1GlobalMotion*             pGlobalMotion;
    ثابت Std_Video_Encode_AV1_Extension_سرلیک*    p_Extension_سرلیک;
    ثابت uint32_t*                            p_بفر_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_چوکاټ_پای_ټکی_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_چوکاټ_Id;
    Std_Video_AV1_چوکاټ_Type                       چوکاټ_type;
    uint8_t                                    ترتیب_Hint;
    uint8_t                                    reserved1[3];
    ثابت Std_Video_Encode_AV1_Extension_سرلیک*    p_Extension_سرلیک;
} StdVideoEncodeAV1ReferenceInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
