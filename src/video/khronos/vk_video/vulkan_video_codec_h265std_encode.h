#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h265std_encode 1

#అన్తర్భావ "vulkan_video_codec_h265std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H265_బరువు_పట్టిక_Flags {
    uint16_t    luma_బరువు_l0_flag;
    uint16_t    chroma_బరువు_l0_flag;
    uint16_t    luma_బరువు_l1_flag;
    uint16_t    chroma_బరువు_l1_flag;
} Std_Video_Encode_H265_బరువు_పట్టిక_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H265_బరువు_పట్టిక {
    Std_Video_Encode_H265_బరువు_పట్టిక_Flags    flags;
    uint8_t                               luma_log2_బరువు_denom;
    int8_t                                delta_chroma_log2_బరువు_denom;
    int8_t                                delta_luma_బరువు_l0[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    int8_t                                luma_స్థానభ్రంశం_l0[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    int8_t                                delta_chroma_బరువు_l0[STD_VIDEO_H265_MAX_అంకె_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_స్థానభ్రంశం_l0[STD_VIDEO_H265_MAX_అంకె_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_బరువు_l1[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    int8_t                                luma_స్థానభ్రంశం_l1[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    int8_t                                delta_chroma_బరువు_l1[STD_VIDEO_H265_MAX_అంకె_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_స్థానభ్రంశం_l1[STD_VIDEO_H265_MAX_అంకె_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_బరువు_పట్టిక;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H265_ముక్క_Segment_శీర్షిక_Flags {
    uint32_t    మొదటి_ముక్క_segment_లోపల_pic_flag : 1;
    uint32_t    dependent_ముక్క_segment_flag : 1;
    uint32_t    ముక్క_sao_luma_flag : 1;
    uint32_t    ముక్క_sao_chroma_flag : 1;
    uint32_t    అంకె_ref_idx_చురుకైన_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_స్థానభ్రంశం_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ముక్క_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ముక్క_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ముక్క_Segment_శీర్షిక_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H265_ముక్క_Segment_శీర్షిక {
    Std_Video_Encode_H265_ముక్క_Segment_శీర్షిక_Flags    flags;
    Std_Video_H265_ముక్క_Type                        ముక్క_type;
    uint32_t                                     ముక్క_segment_చిరునామా;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_అంకె_విలీనం_Cand;
    int8_t                                       ముక్క_cb_qp_స్థానభ్రంశం;
    int8_t                                       ముక్క_cr_qp_స్థానభ్రంశం;
    int8_t                                       ముక్క_beta_స్థానభ్రంశం_div2;
    int8_t                                       ముక్క_tc_స్థానభ్రంశం_div2;
    int8_t                                       ముక్క_act_y_qp_స్థానభ్రంశం;
    int8_t                                       ముక్క_act_cb_qp_స్థానభ్రంశం;
    int8_t                                       ముక్క_act_cr_qp_స్థానభ్రంశం;
    int8_t                                       ముక్క_qp_delta;
    uint16_t                                     reserved1;
    స్థిరరాశి Std_Video_Encode_H265_బరువు_పట్టిక*         p_బరువు_పట్టిక;
} Std_Video_Encode_H265_ముక్క_Segment_శీర్షిక;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      అంకె_ref_idx_l0_చురుకైన_minus1;
    uint8_t                                      అంకె_ref_idx_l1_చురుకైన_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    uint8_t                                      list_నమోదు_l0[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
    uint8_t                                      list_నమోదు_l1[STD_VIDEO_H265_MAX_అంకె_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    వాడిన_for_long_పదం_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_యొక్క_పూర్వ_pics_flag : 1;
    uint32_t    short_పదం_ref_pic_సమితి_sps_flag : 1;
    uint32_t    ముక్క_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H265_Long_పదం_Ref_Pics {
    uint8_t     అంకె_long_పదం_sps;
    uint8_t     అంకె_long_పదం_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_పదం_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_పదం_PICS];
    uint16_t    వాడిన_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_చక్రం_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_పదం_Ref_Pics;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_సమితి_id;
    uint8_t                                        pps_seq_parameter_సమితి_id;
    uint8_t                                        pps_pic_parameter_సమితి_id;
    uint8_t                                        short_పదం_ref_pic_సమితి_idx;
    int32_t                                        Pic_క్రమం_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    స్థిరరాశి StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    స్థిరరాశి Std_Video_H265_Short_పదం_Ref_Pic_సమితి*          p_Short_పదం_Ref_Pic_సమితి;
    స్థిరరాశి Std_Video_Encode_H265_Long_పదం_Ref_Pics*       p_Long_పదం_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    వాడిన_for_long_పదం_reference : 1;
    uint32_t    వాడని_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_క్రమం_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
