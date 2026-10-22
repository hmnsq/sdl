#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_AV1STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// vulkan_video_codec_av1std_decode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_av1std_decode 1

#अन्तर्भाव "vulkan_video_codec_av1std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_decode"

प्रकारनिर्देश संरचना StdVideoDecodeAV1PictureInfoFlags {
    uint32_t    error_resilient_बहुलकम् : 1;
    uint32_t    disable_cdf_update : 1;
    uint32_t    use_superres : 1;
    uint32_t    render_and_frame_आकार_different : 1;
    uint32_t    allow_screen_content_tools : 1;
    uint32_t    is_filter_switchable : 1;
    uint32_t    force_integer_mv : 1;
    uint32_t    frame_आकार_override_flag : 1;
    uint32_t    बफर_removal_time_present_flag : 1;
    uint32_t    allow_intrabc : 1;
    uint32_t    frame_refs_short_signaling : 1;
    uint32_t    allow_उच्चः_precision_mv : 1;
    uint32_t    is_motion_बहुलकम्_switchable : 1;
    uint32_t    use_ref_frame_mvs : 1;
    uint32_t    disable_frame_अन्तः_update_cdf : 1;
    uint32_t    allow_warped_motion : 1;
    uint32_t    reduced_tx_समुच्चयः : 1;
    uint32_t    reference_select : 1;
    uint32_t    skip_बहुलकम्_present : 1;
    uint32_t    delta_q_present : 1;
    uint32_t    delta_lf_present : 1;
    uint32_t    delta_lf_multi : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_दत्त : 1;
    uint32_t    उपयुङ्क्ते_Lr : 1;
    uint32_t    उपयुङ्क्ते_Chroma_Lr : 1;
    uint32_t    apply_grain : 1;
    uint32_t    reserved : 3;
} StdVideoDecodeAV1PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeAV1PictureInfo {
    StdVideoDecodeAV1PictureInfoFlags    flags;
    StdVideoAV1FrameType                 frame_type;
    uint32_t                             current_frame_id;
    uint8_t                              क्रमः_Hint;
    uint8_t                              primary_ref_frame;
    uint8_t                              refresh_frame_flags;
    uint8_t                              reserved1;
    StdVideoAV1InterpolationFilter       interpolation_filter;
    Std_Video_AV1_Tx_बहुलकम्                    Tx_बहुलकम्;
    uint8_t                              delta_q_res;
    uint8_t                              delta_lf_res;
    uint8_t                              Skip_बहुलकम्_Frame[STD_VIDEO_AV1_SKIP_बहुलकम्_चौकटाः];
    uint8_t                              coded_denom;
    uint8_t                              reserved2[3];
    uint8_t                              क्रमः_Hints[STD_VIDEO_AV1_अङ्कः_REF_चौकटाः];
    uint32_t                             expectedFrameId[STD_VIDEO_AV1_अङ्कः_REF_चौकटाः];
    ध्रुव StdVideoAV1TileInfo*           pTileInfo;
    ध्रुव StdVideoAV1Quantization*       pQuantization;
    ध्रुव StdVideoAV1Segmentation*       pSegmentation;
    ध्रुव StdVideoAV1LoopFilter*         pLoopFilter;
    ध्रुव StdVideoAV1CDEF*               pCDEF;
    ध्रुव StdVideoAV1LoopRestoration*    pLoopRestoration;
    ध्रुव StdVideoAV1GlobalMotion*       pGlobalMotion;
    ध्रुव StdVideoAV1FilmGrain*          pFilmGrain;
} StdVideoDecodeAV1PictureInfo;

प्रकारनिर्देश संरचना StdVideoDecodeAV1ReferenceInfoFlags {
    uint32_t    disable_frame_अन्तः_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoDecodeAV1ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeAV1ReferenceInfo {
    StdVideoDecodeAV1ReferenceInfoFlags    flags;
    uint8_t                                frame_type;
    uint8_t                                RefFrameSignBias;
    uint8_t                                क्रमः_Hint;
    uint8_t                                Saved_क्रमः_Hints[STD_VIDEO_AV1_अङ्कः_REF_चौकटाः];
} StdVideoDecodeAV1ReferenceInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
