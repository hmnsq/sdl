#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#تعریف_کن VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_av1std_encode 1

#ضمن "vulkan_video_codec_av1std.h"

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_نسخه_1_0_0
#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

تعريفنوع بنية StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     میانگیر_delay_درازی_minus_1;
    uint8_t     میانگیر_removal_زمان_درازی_minus_1;
    uint8_t     قاب_presentation_زمان_درازی_minus_1;
    uint8_t     reserved1;
    uint32_t    رقم_units_درون_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

تعريفنوع بنية Std_Video_Encode_AV1_Extension_سرآیند {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_سرآیند;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_نقطه_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    کم_delay_نما_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_نقطه_Info_Flags;

تعريفنوع بنية Std_Video_Encode_AV1_Operating_نقطه_Info {
    Std_Video_Encode_AV1_Operating_نقطه_Info_Flags    flags;
    uint16_t                                    operating_نقطه_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_میانگیر_delay;
    uint32_t                                    encoder_میانگیر_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_نقطه_Info;

تعريفنوع بنية StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_نما : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_قاب_اندازه_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    قاب_اندازه_override_flag : 1;
    uint32_t    میانگیر_removal_زمان_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    قاب_refs_short_signaling : 1;
    uint32_t    allow_بالا_precision_mv : 1;
    uint32_t    is_motion_نما_switchable : 1;
    uint32_t    use_ref_قاب_mvs : 1;
    uint32_t    disable_قاب_انتها_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_مجموعه : 1;
    uint32_t    skip_نما_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_داده : 1;
    uint32_t    استفاده_میکند_Lr : 1;
    uint32_t    استفاده_میکند_Chroma_Lr : 1;
    uint32_t    show_قاب : 1;
    uint32_t    showable_قاب : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_قاب_Type                       قاب_type;
    uint32_t                                   قاب_presentation_زمان;
    uint32_t                                   current_قاب_id;
    uint8_t                                    ترتیب_hint;
    uint8_t                                    primary_ref_قاب;
    uint8_t                                    refresh_قاب_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_عرض_minus_1;
    uint16_t                                   render_ارتفاع_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_نما                          Tx_نما;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ترتیب_hint[STD_VIDEO_AV1_رقم_REF_قابها];
    int8_t                                     ref_قاب_idx[STD_VIDEO_AV1_REFS_در_هر_قاب];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_قاب_id_minus_1[STD_VIDEO_AV1_REFS_در_هر_قاب];
    ثابت StdVideoAV1TileInfo*                 pTileInfo;
    ثابت StdVideoAV1Quantization*             pQuantization;
    ثابت StdVideoAV1Segmentation*             pSegmentation;
    ثابت StdVideoAV1LoopFilter*               pLoopFilter;
    ثابت StdVideoAV1CDEF*                     pCDEF;
    ثابت StdVideoAV1LoopRestoration*          pLoopRestoration;
    ثابت StdVideoAV1GlobalMotion*             pGlobalMotion;
    ثابت Std_Video_Encode_AV1_Extension_سرآیند*    p_Extension_سرآیند;
    ثابت uint32_t*                            p_میانگیر_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_قاب_انتها_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_قاب_Id;
    Std_Video_AV1_قاب_Type                       قاب_type;
    uint8_t                                    ترتیب_Hint;
    uint8_t                                    reserved1[3];
    ثابت Std_Video_Encode_AV1_Extension_سرآیند*    p_Extension_سرآیند;
} StdVideoEncodeAV1ReferenceInfo;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
