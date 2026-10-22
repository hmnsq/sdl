#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_av1std_decode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_av1std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeAV1PictureInfoFlags {
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
    uint32_t    reference_select : 1;
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
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    Std_Video_AV1_ਚੌਖਟਾ_Type                 ਚੌਖਟਾ_type;
    uint32_t                             current_ਚੌਖਟਾ_id;
    uint8_t                              ਕ੍ਰਮ_Hint;
    uint8_t                              primary_ref_ਚੌਖਟਾ;
    uint8_t                              refresh_ਚੌਖਟਾ_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_ਬਹੁਲਕ                    Tx_ਬਹੁਲਕ;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_ਬਹੁਲਕ_ਚੌਖਟਾ[STD_VIDEO_AV1_SKIP_ਬਹੁਲਕ_ਚੌਖਟੇ];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              ਕ੍ਰਮ_Hints[STD_VIDEO_AV1_ਅੰਕ_REF_ਚੌਖਟੇ];
    uint32_t                             expected_ਚੌਖਟਾ_Id[STD_VIDEO_AV1_ਅੰਕ_REF_ਚੌਖਟੇ];
    ਅਚਲ StdVideoAV1TileInfo*           pTileInfo;
    ਅਚਲ StdVideoAV1Quantization*       pQuantization;
    ਅਚਲ StdVideoAV1Segmentation*       pSegmentation;
    ਅਚਲ StdVideoAV1LoopFilter*         pLoopFilter;
    ਅਚਲ StdVideoAV1CDEF*               pCDEF;
    ਅਚਲ StdVideoAV1LoopRestoration*    pLoopRestoration;
    ਅਚਲ StdVideoAV1GlobalMotion*       pGlobalMotion;
    ਅਚਲ StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_ਚੌਖਟਾ_ਸਿਰਾ_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                ਚੌਖਟਾ_type;
    uint8_t                                Ref_ਚੌਖਟਾ_Sign_Bias;
    uint8_t                                ਕ੍ਰਮ_Hint;
    uint8_t                                Saved_ਕ੍ਰਮ_Hints[STD_VIDEO_AV1_ਅੰਕ_REF_ਚੌਖਟੇ];
} StdVideoDecodeAV1ReferenceInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
