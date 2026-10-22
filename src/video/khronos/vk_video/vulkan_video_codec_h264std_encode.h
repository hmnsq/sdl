#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

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



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h264std_encode 1

#అన్తర్భావ "vulkan_video_codec_h264std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_బరువు_పట్టిక_Flags {
    uint32_t    luma_బరువు_l0_flag;
    uint32_t    chroma_బరువు_l0_flag;
    uint32_t    luma_బరువు_l1_flag;
    uint32_t    chroma_బరువు_l1_flag;
} Std_Video_Encode_H264_బరువు_పట్టిక_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_బరువు_పట్టిక {
    Std_Video_Encode_H264_బరువు_పట్టిక_Flags    flags;
    uint8_t                               luma_log2_బరువు_denom;
    uint8_t                               chroma_log2_బరువు_denom;
    int8_t                                luma_బరువు_l0[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    int8_t                                luma_స్థానభ్రంశం_l0[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    int8_t                                chroma_బరువు_l0[STD_VIDEO_H264_MAX_అంకె_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_స్థానభ్రంశం_l0[STD_VIDEO_H264_MAX_అంకె_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_బరువు_l1[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    int8_t                                luma_స్థానభ్రంశం_l1[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    int8_t                                chroma_బరువు_l1[STD_VIDEO_H264_MAX_అంకె_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_స్థానభ్రంశం_l1[STD_VIDEO_H264_MAX_అంకె_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_బరువు_పట్టిక;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_ముక్క_శీర్షిక_Flags {
    uint32_t    ప్రత్యక్ష_spatial_mv_pred_flag : 1;
    uint32_t    అంకె_ref_idx_చురుకైన_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_ముక్క_శీర్షిక_Flags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_యొక్క_పూర్వ_pics_flag : 1;
    uint32_t    long_పదం_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_బహుళకం_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    వాడిన_for_long_పదం_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_Ref_List_Mod_నమోదు {
    Std_Video_H264_Modification_యొక్క_Pic_Nums_Idc    modification_యొక్క_pic_nums_idc;
    uint16_t                                abs_diff_pic_అంకె_minus1;
    uint16_t                                long_పదం_pic_అంకె;
} Std_Video_Encode_H264_Ref_List_Mod_నమోదు;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_Ref_Pic_Marking_నమోదు {
    StdVideoH264MemMgmtControlOp    జ్ఞాపకం_management_control_operation;
    uint16_t                        difference_యొక్క_pic_nums_minus1;
    uint16_t                        long_పదం_pic_అంకె;
    uint16_t                        long_పదం_చట్రం_idx;
    uint16_t                        max_long_పదం_చట్రం_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_నమోదు;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        అంకె_ref_idx_l0_చురుకైన_minus1;
    uint8_t                                        అంకె_ref_idx_l1_చురుకైన_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_అంకె_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_లెక్క;
    uint8_t                                        ref_List1_Mod_Op_లెక్క;
    uint8_t                                        ref_Pic_Marking_Op_లెక్క;
    uint8_t                                        reserved1[7];
    స్థిరరాశి Std_Video_Encode_H264_Ref_List_Mod_నమోదు*       pRefList0ModOperations;
    స్థిరరాశి Std_Video_Encode_H264_Ref_List_Mod_నమోదు*       pRefList1ModOperations;
    స్థిరరాశి Std_Video_Encode_H264_Ref_Pic_Marking_నమోదు*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_సమితి_id;
    uint8_t                                        pic_parameter_సమితి_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       చట్రం_అంకె;
    int32_t                                        Pic_క్రమం_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    స్థిరరాశి StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                చట్రం_అంకె_2;
    int32_t                                 Pic_క్రమం_Cnt;
    uint16_t                                long_పదం_pic_అంకె;
    uint16_t                                long_పదం_చట్రం_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

రకనిర్వచనం నిర్మాణం Std_Video_Encode_H264_ముక్క_శీర్షిక {
    Std_Video_Encode_H264_ముక్క_శీర్షిక_Flags        flags;
    uint32_t                                  మొదటి_mb_లోపల_ముక్క;
    Std_Video_H264_ముక్క_Type                     ముక్క_type;
    int8_t                                    ముక్క_alpha_c0_స్థానభ్రంశం_div2;
    int8_t                                    ముక్క_beta_స్థానభ్రంశం_div2;
    int8_t                                    ముక్క_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    స్థిరరాశి Std_Video_Encode_H264_బరువు_పట్టిక*      p_బరువు_పట్టిక;
} Std_Video_Encode_H264_ముక్క_శీర్షిక;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
