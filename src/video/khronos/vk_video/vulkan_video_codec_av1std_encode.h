#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_av1std_encode 1

#شامل "vulkan_video_codec_av1std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

قسمتعریف ساخت StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     بفر_delay_لمبائی_minus_1;
    uint8_t     بفر_removal_وقت_لمبائی_minus_1;
    uint8_t     چوکھٹا_presentation_وقت_لمبائی_minus_1;
    uint8_t     reserved1;
    uint32_t    عدد_units_اندر_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

قسمتعریف ساخت Std_Video_Encode_AV1_Extension_سرخی {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_سرخی;

قسمتعریف ساخت Std_Video_Encode_AV1_Operating_نقطہ_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    کم_delay_منوال_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_نقطہ_Info_Flags;

قسمتعریف ساخت Std_Video_Encode_AV1_Operating_نقطہ_Info {
    Std_Video_Encode_AV1_Operating_نقطہ_Info_Flags    flags;
    uint16_t                                    operating_نقطہ_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_بفر_delay;
    uint32_t                                    encoder_بفر_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_نقطہ_Info;

قسمتعریف ساخت StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_منوال : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_چوکھٹا_سائز_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    چوکھٹا_سائز_override_flag : 1;
    uint32_t    بفر_removal_وقت_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    چوکھٹا_refs_short_signaling : 1;
    uint32_t    allow_بلند_precision_mv : 1;
    uint32_t    is_motion_منوال_switchable : 1;
    uint32_t    use_ref_چوکھٹا_mvs : 1;
    uint32_t    disable_چوکھٹا_انتہا_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_سیٹ : 1;
    uint32_t    skip_منوال_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_ڈیٹا : 1;
    uint32_t    استعمال_کرتا_Lr : 1;
    uint32_t    استعمال_کرتا_Chroma_Lr : 1;
    uint32_t    show_چوکھٹا : 1;
    uint32_t    showable_چوکھٹا : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

قسمتعریف ساخت StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_چوکھٹا_Type                       چوکھٹا_type;
    uint32_t                                   چوکھٹا_presentation_وقت;
    uint32_t                                   current_چوکھٹا_id;
    uint8_t                                    ترتیب_hint;
    uint8_t                                    primary_ref_چوکھٹا;
    uint8_t                                    refresh_چوکھٹا_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_چوڑائی_minus_1;
    uint16_t                                   render_اونچائی_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_منوال                          Tx_منوال;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ترتیب_hint[STD_VIDEO_AV1_عدد_REF_چوکھٹے];
    int8_t                                     ref_چوکھٹا_idx[STD_VIDEO_AV1_REFS_فی_چوکھٹا];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_چوکھٹا_id_minus_1[STD_VIDEO_AV1_REFS_فی_چوکھٹا];
    ثابت StdVideoAV1TileInfo*                 pTileInfo;
    ثابت StdVideoAV1Quantization*             pQuantization;
    ثابت StdVideoAV1Segmentation*             pSegmentation;
    ثابت StdVideoAV1LoopFilter*               pLoopFilter;
    ثابت StdVideoAV1CDEF*                     pCDEF;
    ثابت StdVideoAV1LoopRestoration*          pLoopRestoration;
    ثابت StdVideoAV1GlobalMotion*             pGlobalMotion;
    ثابت Std_Video_Encode_AV1_Extension_سرخی*    p_Extension_سرخی;
    ثابت uint32_t*                            p_بفر_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

قسمتعریف ساخت StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_چوکھٹا_انتہا_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

قسمتعریف ساخت StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_چوکھٹا_Id;
    Std_Video_AV1_چوکھٹا_Type                       چوکھٹا_type;
    uint8_t                                    ترتیب_Hint;
    uint8_t                                    reserved1[3];
    ثابت Std_Video_Encode_AV1_Extension_سرخی*    p_Extension_سرخی;
} StdVideoEncodeAV1ReferenceInfo;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
