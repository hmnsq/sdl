#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

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



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_av1std_decode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_av1std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeAV1PictureInfoFlags {
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
    uint32_t    reference_select : 1;
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
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    Std_Video_AV1_ಚೌಕಟ್ಟು_Type                 ಚೌಕಟ್ಟು_type;
    uint32_t                             current_ಚೌಕಟ್ಟು_id;
    uint8_t                              ಕ್ರಮ_Hint;
    uint8_t                              primary_ref_ಚೌಕಟ್ಟು;
    uint8_t                              refresh_ಚೌಕಟ್ಟು_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_ಬಹುಲಕ                    Tx_ಬಹುಲಕ;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_ಬಹುಲಕ_ಚೌಕಟ್ಟು[STD_VIDEO_AV1_SKIP_ಬಹುಲಕ_ಚೌಕಟ್ಟುಗಳು];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              ಕ್ರಮ_Hints[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು];
    uint32_t                             expected_ಚೌಕಟ್ಟು_Id[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು];
    ಸ್ಥಿರಾಂಕ StdVideoAV1TileInfo*           pTileInfo;
    ಸ್ಥಿರಾಂಕ StdVideoAV1Quantization*       pQuantization;
    ಸ್ಥಿರಾಂಕ StdVideoAV1Segmentation*       pSegmentation;
    ಸ್ಥಿರಾಂಕ StdVideoAV1LoopFilter*         pLoopFilter;
    ಸ್ಥಿರಾಂಕ StdVideoAV1CDEF*               pCDEF;
    ಸ್ಥಿರಾಂಕ StdVideoAV1LoopRestoration*    pLoopRestoration;
    ಸ್ಥಿರಾಂಕ StdVideoAV1GlobalMotion*       pGlobalMotion;
    ಸ್ಥಿರಾಂಕ StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_ಚೌಕಟ್ಟು_ಕೊನೆ_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                ಚೌಕಟ್ಟು_type;
    uint8_t                                Ref_ಚೌಕಟ್ಟು_Sign_Bias;
    uint8_t                                ಕ್ರಮ_Hint;
    uint8_t                                Saved_ಕ್ರಮ_Hints[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು];
} StdVideoDecodeAV1ReferenceInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
