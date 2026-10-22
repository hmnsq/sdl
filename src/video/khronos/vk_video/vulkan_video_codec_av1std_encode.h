#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_av1std_encode 1

#అన్తర్భావ "vulkan_video_codec_av1std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

రకనిర్వచనం నిర్మాణం StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     బఫరు_delay_నిడివి_minus_1;
    uint8_t     బఫరు_removal_సమయం_నిడివి_minus_1;
    uint8_t     చట్రం_presentation_సమయం_నిడివి_minus_1;
    uint8_t     reserved1;
    uint32_t    అంకె_units_లోపల_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_AV1_Extension_శీర్షిక {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_శీర్షిక;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_AV1_Operating_బిందువు_Info_Flags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    దిగువ_delay_బహుళకం_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} Std_Video_Encode_AV1_Operating_బిందువు_Info_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_AV1_Operating_బిందువు_Info {
    Std_Video_Encode_AV1_Operating_బిందువు_Info_Flags    flags;
    uint16_t                                    operating_బిందువు_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_బఫరు_delay;
    uint32_t                                    encoder_బఫరు_delay;
    uint8_t                                     initial_display_delay_minus_1;
} Std_Video_Encode_AV1_Operating_బిందువు_Info;

రకనిర్వచనం నిర్మాణం StdVideoEncodeAV1PictureInfoFlags {
    uint32_t    error_resilient_బహుళకం : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_చట్రం_కొలత_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    చట్రం_కొలత_override_flag : 1;
    uint32_t    బఫరు_removal_సమయం_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    చట్రం_refs_short_signaling : 1;
    uint32_t    allow_ఎగువ_precision_mv : 1;
    uint32_t    is_motion_బహుళకం_switchable : 1;
    uint32_t    use_ref_చట్రం_mvs : 1;
    uint32_t    disable_చట్రం_చివర_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_సమితి : 1;
    uint32_t    skip_బహుళకం_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_దత్తాంశం : 1;
    uint32_t    ఉపయోగిస్తుంది_Lr : 1;
    uint32_t    ఉపయోగిస్తుంది_Chroma_Lr : 1;
    uint32_t    show_చట్రం : 1;
    uint32_t    showable_చట్రం : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    Std_Video_AV1_చట్రం_Type                       చట్రం_type;
    uint32_t                                   చట్రం_presentation_సమయం;
    uint32_t                                   current_చట్రం_id;
    uint8_t                                    క్రమం_hint;
    uint8_t                                    primary_ref_చట్రం;
    uint8_t                                    refresh_చట్రం_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_వెడల్పు_minus_1;
    uint16_t                                   render_ఎత్తు_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_బహుళకం                          Tx_బహుళకం;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_క్రమం_hint[STD_VIDEO_AV1_అంకె_REF_చట్రాలు];
    int8_t                                     ref_చట్రం_idx[STD_VIDEO_AV1_REFS_చొప్పున_చట్రం];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_చట్రం_id_minus_1[STD_VIDEO_AV1_REFS_చొప్పున_చట్రం];
    స్థిరరాశి StdVideoAV1TileInfo*                 pTileInfo;
    స్థిరరాశి StdVideoAV1Quantization*             pQuantization;
    స్థిరరాశి StdVideoAV1Segmentation*             pSegmentation;
    స్థిరరాశి StdVideoAV1LoopFilter*               pLoopFilter;
    స్థిరరాశి StdVideoAV1CDEF*                     pCDEF;
    స్థిరరాశి StdVideoAV1LoopRestoration*          pLoopRestoration;
    స్థిరరాశి StdVideoAV1GlobalMotion*             pGlobalMotion;
    స్థిరరాశి Std_Video_Encode_AV1_Extension_శీర్షిక*    p_Extension_శీర్షిక;
    స్థిరరాశి uint32_t*                            p_బఫరు_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_చట్రం_చివర_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   Ref_చట్రం_Id;
    Std_Video_AV1_చట్రం_Type                       చట్రం_type;
    uint8_t                                    క్రమం_Hint;
    uint8_t                                    reserved1[3];
    స్థిరరాశి Std_Video_Encode_AV1_Extension_శీర్షిక*    p_Extension_శీర్షిక;
} StdVideoEncodeAV1ReferenceInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
