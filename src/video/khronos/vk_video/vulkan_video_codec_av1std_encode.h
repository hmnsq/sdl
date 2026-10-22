#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_av1std_encode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_av1std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     ಬಫರ್_delay_ಉದ್ದಳತೆ_minus_1;
    uint8_t     ಬಫರ್_removal_ಸಮಯ_ಉದ್ದಳತೆ_minus_1;
    uint8_t     ಚೌಕಟ್ಟು_presentation_ಸಮಯ_ಉದ್ದಳತೆ_minus_1;
    uint8_t     reserved1;
    uint32_t    ಅಂಕೆ_units_ಒಳ_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_AV1_Extension_ಶೀರ್ಷಿಕೆ {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_ಶೀರ್ಷಿಕೆ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_AV1_Operating_ಬಿಂದು_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    ಕೆಳಗಿನ_delay_ಬಹುಲಕ_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_ಬಿಂದು_Info_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_AV1_Operating_ಬಿಂದು_Info {
    Std_Video_Encode_AV1_Operating_ಬಿಂದು_Info_Flags    flags;
    uint16_t                                    operating_ಬಿಂದು_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_ಬಫರ್_delay;
    uint32_t                                    encoder_ಬಫರ್_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_ಬಿಂದು_Info;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_ಬಹುಲಕ : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_ಚೌಕಟ್ಟು_ಗಾತ್ರ_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    ಚೌಕಟ್ಟು_ಗಾತ್ರ_override_flag : 1;
    uint32_t    ಬಫರ್_removal_ಸಮಯ_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    ಚೌಕಟ್ಟು_refs_short_signaling : 1;
    uint32_t    allow_ಮೇಲಿನ_precision_mv : 1;
    uint32_t    is_motion_ಬಹುಲಕ_switchable : 1;
    uint32_t    use_ref_ಚೌಕಟ್ಟು_mvs : 1;
    uint32_t    disable_ಚೌಕಟ್ಟು_ಕೊನೆ_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_ಗಣ : 1;
    uint32_t    skip_ಬಹುಲಕ_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_ದತ್ತಾಂಶ : 1;
    uint32_t    ಬಳಸುತ್ತದೆ_Lr : 1;
    uint32_t    ಬಳಸುತ್ತದೆ_Chroma_Lr : 1;
    uint32_t    show_ಚೌಕಟ್ಟು : 1;
    uint32_t    showable_ಚೌಕಟ್ಟು : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_ಚೌಕಟ್ಟು_Type                       ಚೌಕಟ್ಟು_type;
    uint32_t                                   ಚೌಕಟ್ಟು_presentation_ಸಮಯ;
    uint32_t                                   current_ಚೌಕಟ್ಟು_id;
    uint8_t                                    ಕ್ರಮ_hint;
    uint8_t                                    primary_ref_ಚೌಕಟ್ಟು;
    uint8_t                                    refresh_ಚೌಕಟ್ಟು_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_ಅಗಲ_minus_1;
    uint16_t                                   render_ಎತ್ತರ_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_ಬಹುಲಕ                          Tx_ಬಹುಲಕ;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_ಕ್ರಮ_hint[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು];
    int8_t                                     ref_ಚೌಕಟ್ಟು_idx[STD_VIDEO_AV1_REFS_ಪ್ರತಿ_ಚೌಕಟ್ಟು];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_ಚೌಕಟ್ಟು_id_minus_1[STD_VIDEO_AV1_REFS_ಪ್ರತಿ_ಚೌಕಟ್ಟು];
    ಸ್ಥಿರಾಂಕ StdVideoAV1TileInfo*                 pTileInfo;
    ಸ್ಥಿರಾಂಕ StdVideoAV1Quantization*             pQuantization;
    ಸ್ಥಿರಾಂಕ StdVideoAV1Segmentation*             pSegmentation;
    ಸ್ಥಿರಾಂಕ StdVideoAV1LoopFilter*               pLoopFilter;
    ಸ್ಥಿರಾಂಕ StdVideoAV1CDEF*                     pCDEF;
    ಸ್ಥಿರಾಂಕ StdVideoAV1LoopRestoration*          pLoopRestoration;
    ಸ್ಥಿರಾಂಕ StdVideoAV1GlobalMotion*             pGlobalMotion;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_AV1_Extension_ಶೀರ್ಷಿಕೆ*    p_Extension_ಶೀರ್ಷಿಕೆ;
    ಸ್ಥಿರಾಂಕ uint32_t*                            p_ಬಫರ್_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_ಚೌಕಟ್ಟು_ಕೊನೆ_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_ಚೌಕಟ್ಟು_Id;
    Std_Video_AV1_ಚೌಕಟ್ಟು_Type                       ಚೌಕಟ್ಟು_type;
    uint8_t                                    ಕ್ರಮ_Hint;
    uint8_t                                    reserved1[3];
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_AV1_Extension_ಶೀರ್ಷಿಕೆ*    p_Extension_ಶೀರ್ಷಿಕೆ;
} StdVideoEncodeAV1ReferenceInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
