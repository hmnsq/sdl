#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_av1std_decode 1

#అన్తర్భావ "vulkan_video_codec_av1std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

రకనిర్వచనం నిర్మాణం StdVideoDecodeAV1PictureInfoFlags {
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
    uint32_t    reference_select : 1;
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
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    Std_Video_AV1_చట్రం_Type                 చట్రం_type;
    uint32_t                             current_చట్రం_id;
    uint8_t                              క్రమం_Hint;
    uint8_t                              primary_ref_చట్రం;
    uint8_t                              refresh_చట్రం_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_బహుళకం                    Tx_బహుళకం;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_బహుళకం_చట్రం[STD_VIDEO_AV1_SKIP_బహుళకం_చట్రాలు];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              క్రమం_Hints[STD_VIDEO_AV1_అంకె_REF_చట్రాలు];
    uint32_t                             expected_చట్రం_Id[STD_VIDEO_AV1_అంకె_REF_చట్రాలు];
    స్థిరరాశి StdVideoAV1TileInfo*           pTileInfo;
    స్థిరరాశి StdVideoAV1Quantization*       pQuantization;
    స్థిరరాశి StdVideoAV1Segmentation*       pSegmentation;
    స్థిరరాశి StdVideoAV1LoopFilter*         pLoopFilter;
    స్థిరరాశి StdVideoAV1CDEF*               pCDEF;
    స్థిరరాశి StdVideoAV1LoopRestoration*    pLoopRestoration;
    స్థిరరాశి StdVideoAV1GlobalMotion*       pGlobalMotion;
    స్థిరరాశి StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_చట్రం_చివర_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                చట్రం_type;
    uint8_t                                Ref_చట్రం_Sign_Bias;
    uint8_t                                క్రమం_Hint;
    uint8_t                                Saved_క్రమం_Hints[STD_VIDEO_AV1_అంకె_REF_చట్రాలు];
} StdVideoDecodeAV1ReferenceInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
