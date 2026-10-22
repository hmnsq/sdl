#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_AV1STD_ENCODE_H_ 1

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



// vulkan_video_codec_av1std_encode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_av1std_encode 1

#अन्तर्भाव "vulkan_video_codec_av1std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_av1_encode"

प्रकारनिर्देश संरचना StdVideoEncodeAV1DecoderModelInfo {
    uint8_t     बफर_delay_दीर्घता_minus_1;
    uint8_t     बफर_removal_time_दीर्घता_minus_1;
    uint8_t     frame_presentation_time_दीर्घता_minus_1;
    uint8_t     reserved1;
    uint32_t    अङ्कः_units_अन्तर्_decoding_tick;
} StdVideoEncodeAV1DecoderModelInfo;

प्रकारनिर्देश संरचना Std_Video_Encode_AV1_Extension_शीर्षकम् {
    uint8_t    temporal_id;
    uint8_t    spatial_id;
} Std_Video_Encode_AV1_Extension_शीर्षकम्;

प्रकारनिर्देश संरचना StdVideoEncodeAV1OperatingPointInfoFlags {
    uint32_t    decoder_model_present_for_this_op : 1;
    uint32_t    नीचः_delay_बहुलकम्_flag : 1;
    uint32_t    initial_display_delay_present_for_this_op : 1;
    uint32_t    reserved : 29;
} StdVideoEncodeAV1OperatingPointInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeAV1OperatingPointInfo {
    StdVideoEncodeAV1OperatingPointInfoFlags    flags;
    uint16_t                                    operating_point_idc;
    uint8_t                                     seq_level_idx;
    uint8_t                                     seq_tier;
    uint32_t                                    decoder_बफर_delay;
    uint32_t                                    encoder_बफर_delay;
    uint8_t                                     initial_display_delay_minus_1;
} StdVideoEncodeAV1OperatingPointInfo;

प्रकारनिर्देश संरचना StdVideoEncodeAV1PictureInfoFlags {
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
    uint32_t    show_frame : 1;
    uint32_t    showable_frame : 1;
    uint32_t    reserved : 3;
} StdVideoEncodeAV1PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeAV1PictureInfo {
    StdVideoEncodeAV1PictureInfoFlags          flags;
    StdVideoAV1FrameType                       frame_type;
    uint32_t                                   frame_presentation_time;
    uint32_t                                   current_frame_id;
    uint8_t                                    क्रमः_hint;
    uint8_t                                    primary_ref_frame;
    uint8_t                                    refresh_frame_flags;
    uint8_t                                    coded_denom;
    uint16_t                                   render_विस्तारः_minus_1;
    uint16_t                                   render_height_minus_1;
    StdVideoAV1InterpolationFilter             interpolation_filter;
    Std_Video_AV1_Tx_बहुलकम्                          Tx_बहुलकम्;
    uint8_t                                    delta_q_res;
    uint8_t                                    delta_lf_res;
    uint8_t                                    ref_क्रमः_hint[STD_VIDEO_AV1_अङ्कः_REF_चौकटाः];
    int8_t                                     ref_frame_idx[STD_VIDEO_AV1_REFS_प्रत्येकम्_FRAME];
    uint8_t                                    reserved1[3];
    uint32_t                                   delta_frame_id_minus_1[STD_VIDEO_AV1_REFS_प्रत्येकम्_FRAME];
    ध्रुव StdVideoAV1TileInfo*                 pTileInfo;
    ध्रुव StdVideoAV1Quantization*             pQuantization;
    ध्रुव StdVideoAV1Segmentation*             pSegmentation;
    ध्रुव StdVideoAV1LoopFilter*               pLoopFilter;
    ध्रुव StdVideoAV1CDEF*                     pCDEF;
    ध्रुव StdVideoAV1LoopRestoration*          pLoopRestoration;
    ध्रुव StdVideoAV1GlobalMotion*             pGlobalMotion;
    ध्रुव Std_Video_Encode_AV1_Extension_शीर्षकम्*    p_Extension_शीर्षकम्;
    ध्रुव uint32_t*                            p_बफर_Removal_Times;
} StdVideoEncodeAV1PictureInfo;

प्रकारनिर्देश संरचना StdVideoEncodeAV1ReferenceInfoFlags {
    uint32_t    disable_frame_अन्तः_update_cdf : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeAV1ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeAV1ReferenceInfo {
    StdVideoEncodeAV1ReferenceInfoFlags        flags;
    uint32_t                                   RefFrameId;
    StdVideoAV1FrameType                       frame_type;
    uint8_t                                    क्रमः_Hint;
    uint8_t                                    reserved1[3];
    ध्रुव Std_Video_Encode_AV1_Extension_शीर्षकम्*    p_Extension_शीर्षकम्;
} StdVideoEncodeAV1ReferenceInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
