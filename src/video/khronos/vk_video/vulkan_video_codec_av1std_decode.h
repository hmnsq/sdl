#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_av1std_decode 1

#ضمن "vulkan_video_codec_av1std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

تعريفنوع بنية StdVideoDecodeAV1PictureInfoFlags {
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
    uint32_t    reference_select : 1;
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
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    Std_Video_AV1_چوکاټ_Type                 چوکاټ_type;
    uint32_t                             current_چوکاټ_id;
    uint8_t                              ترتیب_Hint;
    uint8_t                              primary_ref_چوکاټ;
    uint8_t                              refresh_چوکاټ_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_ډېرپېښ                    Tx_ډېرپېښ;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_ډېرپېښ_چوکاټ[STD_VIDEO_AV1_SKIP_ډېرپېښ_چوکاټونه];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              ترتیب_Hints[STD_VIDEO_AV1_عدد_REF_چوکاټونه];
    uint32_t                             expected_چوکاټ_Id[STD_VIDEO_AV1_عدد_REF_چوکاټونه];
    ثابت StdVideoAV1TileInfo*           pTileInfo;
    ثابت StdVideoAV1Quantization*       pQuantization;
    ثابت StdVideoAV1Segmentation*       pSegmentation;
    ثابت StdVideoAV1LoopFilter*         pLoopFilter;
    ثابت StdVideoAV1CDEF*               pCDEF;
    ثابت StdVideoAV1LoopRestoration*    pLoopRestoration;
    ثابت StdVideoAV1GlobalMotion*       pGlobalMotion;
    ثابت StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

تعريفنوع بنية StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_چوکاټ_پای_ټکی_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                چوکاټ_type;
    uint8_t                                Ref_چوکاټ_Sign_Bias;
    uint8_t                                ترتیب_Hint;
    uint8_t                                Saved_ترتیب_Hints[STD_VIDEO_AV1_عدد_REF_چوکاټونه];
} StdVideoDecodeAV1ReferenceInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
