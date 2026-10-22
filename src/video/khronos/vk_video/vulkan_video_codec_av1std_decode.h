#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_av1std_decode 1

#ضمن "vulkan_video_codec_av1std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

تعريفنوع بنية StdVideoDecodeAV1PictureInfoFlags {
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
    uint32_t    reference_select : 1;
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
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    Std_Video_AV1_چوکٺو_Type                 چوکٺو_type;
    uint32_t                             current_چوکٺو_id;
    uint8_t                              ترتيب_Hint;
    uint8_t                              primary_ref_چوکٺو;
    uint8_t                              refresh_چوکٺو_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_گهڻائي                    Tx_گهڻائي;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_گهڻائي_چوکٺو[STD_VIDEO_AV1_SKIP_گهڻائي_چوکٺا];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              ترتيب_Hints[STD_VIDEO_AV1_انگ_REF_چوکٺا];
    uint32_t                             expected_چوکٺو_Id[STD_VIDEO_AV1_انگ_REF_چوکٺا];
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
    uint32_t    disable_چوکٺو_پڇاڙي_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                چوکٺو_type;
    uint8_t                                Ref_چوکٺو_Sign_Bias;
    uint8_t                                ترتيب_Hint;
    uint8_t                                Saved_ترتيب_Hints[STD_VIDEO_AV1_انگ_REF_چوکٺا];
} StdVideoDecodeAV1ReferenceInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
