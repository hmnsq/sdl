#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_av1std_encode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_av1std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     ਬਫਰ_delay_ਲੰਮਾਈ_minus_1;
    uint8_t     ਬਫਰ_removal_ਸਮਾਂ_ਲੰਮਾਈ_minus_1;
    uint8_t     ਚੌਖਟਾ_presentation_ਸਮਾਂ_ਲੰਮਾਈ_minus_1;
    uint8_t     reserved1;
    uint32_t    ਅੰਕ_units_ਵਿੱਚ_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_AV1_Extension_ਸਿਰਲੇਖ {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_ਸਿਰਲੇਖ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_AV1_Operating_ਬਿੰਦੂ_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    ਨੀਵਾਂ_delay_ਬਹੁਲਕ_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_ਬਿੰਦੂ_Info_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_AV1_Operating_ਬਿੰਦੂ_Info {
    Std_Video_Encode_AV1_Operating_ਬਿੰਦੂ_Info_Flags    flags;
    uint16_t                                    operating_ਬਿੰਦੂ_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_ਬਫਰ_delay;
    uint32_t                                    encoder_ਬਫਰ_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_ਬਿੰਦੂ_Info;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_ਬਹੁਲਕ : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_ਚੌਖਟਾ_ਮਾਪ_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    ਚੌਖਟਾ_ਮਾਪ_override_flag : 1;
    uint32_t    ਬਫਰ_removal_ਸਮਾਂ_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    ਚੌਖਟਾ_refs_short_signaling : 1;
    uint32_t    allow_ਉੱਚਾ_precision_mv : 1;
    uint32_t    is_motion_ਬਹੁਲਕ_switchable : 1;
    uint32_t    use_ref_ਚੌਖਟਾ_mvs : 1;
    uint32_t    disable_ਚੌਖਟਾ_ਸਿਰਾ_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_ਸੈੱਟ : 1;
    uint32_t    skip_ਬਹੁਲਕ_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_ਅੰਕੜੇ : 1;
    uint32_t    ਵਰਤਦਾ_Lr : 1;
    uint32_t    ਵਰਤਦਾ_Chroma_Lr : 1;
    uint32_t    show_ਚੌਖਟਾ : 1;
    uint32_t    showable_ਚੌਖਟਾ : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_ਚੌਖਟਾ_Type                       ਚੌਖਟਾ_type;
    uint32_t                                   ਚੌਖਟਾ_presentation_ਸਮਾਂ;
    uint32_t                                   current_ਚੌਖਟਾ_id;
    uint8_t                                    ਕ੍ਰਮ_hint;
    uint8_t                                    primary_ref_ਚੌਖਟਾ;
    uint8_t                                    refresh_ਚੌਖਟਾ_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_ਚੌੜਾਈ_minus_1;
    uint16_t                                   render_ਉਚਾਈ_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_ਬਹੁਲਕ                          Tx_ਬਹੁਲਕ;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ਕ੍ਰਮ_hint[STD_VIDEO_AV1_ਅੰਕ_REF_ਚੌਖਟੇ];
    int8_t                                     ref_ਚੌਖਟਾ_idx[STD_VIDEO_AV1_REFS_ਪ੍ਰਤੀ_ਚੌਖਟਾ];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_ਚੌਖਟਾ_id_minus_1[STD_VIDEO_AV1_REFS_ਪ੍ਰਤੀ_ਚੌਖਟਾ];
    ਅਚਲ StdVideoAV1TileInfo*                 pTileInfo;
    ਅਚਲ StdVideoAV1Quantization*             pQuantization;
    ਅਚਲ StdVideoAV1Segmentation*             pSegmentation;
    ਅਚਲ StdVideoAV1LoopFilter*               pLoopFilter;
    ਅਚਲ StdVideoAV1CDEF*                     pCDEF;
    ਅਚਲ StdVideoAV1LoopRestoration*          pLoopRestoration;
    ਅਚਲ StdVideoAV1GlobalMotion*             pGlobalMotion;
    ਅਚਲ Std_Video_Encode_AV1_Extension_ਸਿਰਲੇਖ*    p_Extension_ਸਿਰਲੇਖ;
    ਅਚਲ uint32_t*                            p_ਬਫਰ_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_ਚੌਖਟਾ_ਸਿਰਾ_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_ਚੌਖਟਾ_Id;
    Std_Video_AV1_ਚੌਖਟਾ_Type                       ਚੌਖਟਾ_type;
    uint8_t                                    ਕ੍ਰਮ_Hint;
    uint8_t                                    reserved1[3];
    ਅਚਲ Std_Video_Encode_AV1_Extension_ਸਿਰਲੇਖ*    p_Extension_ਸਿਰਲੇਖ;
} StdVideoEncodeAV1ReferenceInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
