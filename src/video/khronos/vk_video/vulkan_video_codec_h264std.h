#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H264STD_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h264std 1

#అన్తర్భావ "vulkan_video_codecs_common.h"

#నిర్వచించు STD_VIDEO_H264_CPB_CNT_LIST_కొలత  32U
#నిర్వచించు STD_VIDEO_H264_SCALING_LIST_4_X4_అంకె_LISTS 6U
#నిర్వచించు STD_VIDEO_H264_SCALING_LIST_4_X4_అంకె_ELEMENTS 16U
#నిర్వచించు STD_VIDEO_H264_SCALING_LIST_8_X8_అంకె_LISTS 6U
#నిర్వచించు STD_VIDEO_H264_SCALING_LIST_8_X8_అంకె_ELEMENTS 64U
#నిర్వచించు STD_VIDEO_H264_MAX_అంకె_LIST_REF   32U
#నిర్వచించు STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#నిర్వచించు STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

రకనిర్వచనం గణన StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

రకనిర్వచనం గణన StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_ఎగువ = 100,
    STD_VIDEO_H264_PROFILE_IDC_ఎగువ_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_ఎగువ_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_ఎగువ_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

రకనిర్వచనం గణన StdVideoH264LevelIdc {
    STD_VIDEO_H264_LEVEL_IDC_1_0 = 0,
    STD_VIDEO_H264_LEVEL_IDC_1_1 = 1,
    STD_VIDEO_H264_LEVEL_IDC_1_2 = 2,
    STD_VIDEO_H264_LEVEL_IDC_1_3 = 3,
    STD_VIDEO_H264_LEVEL_IDC_2_0 = 4,
    STD_VIDEO_H264_LEVEL_IDC_2_1 = 5,
    STD_VIDEO_H264_LEVEL_IDC_2_2 = 6,
    STD_VIDEO_H264_LEVEL_IDC_3_0 = 7,
    STD_VIDEO_H264_LEVEL_IDC_3_1 = 8,
    STD_VIDEO_H264_LEVEL_IDC_3_2 = 9,
    STD_VIDEO_H264_LEVEL_IDC_4_0 = 10,
    STD_VIDEO_H264_LEVEL_IDC_4_1 = 11,
    STD_VIDEO_H264_LEVEL_IDC_4_2 = 12,
    STD_VIDEO_H264_LEVEL_IDC_5_0 = 13,
    STD_VIDEO_H264_LEVEL_IDC_5_1 = 14,
    STD_VIDEO_H264_LEVEL_IDC_5_2 = 15,
    STD_VIDEO_H264_LEVEL_IDC_6_0 = 16,
    STD_VIDEO_H264_LEVEL_IDC_6_1 = 17,
    STD_VIDEO_H264_LEVEL_IDC_6_2 = 18,
    STD_VIDEO_H264_LEVEL_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_LEVEL_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264LevelIdc;

రకనిర్వచనం గణన StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

రకనిర్వచనం గణన Std_Video_H264_Aspect_నిష్పత్తి_Idc {
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_వర్గం = 1,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_నిష్పత్తి_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_నిష్పత్తి_Idc;

రకనిర్వచనం గణన StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

రకనిర్వచనం గణన Std_Video_H264_Modification_యొక్క_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_SHORT_పదం_వ్యవకలనం = 0,
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_SHORT_పదం_కూడు = 1,
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_LONG_పదం = 2,
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_చివర = 3,
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_యొక్క_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_యొక్క_Pic_Nums_Idc;

రకనిర్వచనం గణన StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_చివర = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_పదం = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_పదం = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_పదం = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_సమితి_MAX_LONG_పదం_సూచీ = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_పదం = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

రకనిర్వచనం గణన StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

రకనిర్వచనం గణన StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

రకనిర్వచనం గణన Std_Video_H264_ముక్క_Type {
    STD_VIDEO_H264_ముక్క_TYPE_P = 0,
    STD_VIDEO_H264_ముక్క_TYPE_B = 1,
    STD_VIDEO_H264_ముక్క_TYPE_I = 2,
    STD_VIDEO_H264_ముక్క_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ముక్క_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_ముక్క_Type;

రకనిర్వచనం గణన StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

రకనిర్వచనం గణన StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ఉపసర్గ = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_చివర_యొక్క_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_చివర_యొక్క_ప్రవాహం = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

రకనిర్వచనం నిర్మాణం StdVideoH264SpsVuiFlags {
    uint32_t    aspect_నిష్పత్తి_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_నిండిన_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_చట్రం_రేటు_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

రకనిర్వచనం నిర్మాణం StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     బిట్టు_రేటు_scale;
    uint8_t     cpb_కొలత_scale;
    uint8_t     reserved1;
    uint32_t    బిట్టు_రేటు_విలువ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_కొలత];
    uint32_t    cpb_కొలత_విలువ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_కొలత];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_కొలత];
    uint32_t    initial_cpb_removal_delay_నిడివి_minus1;
    uint32_t    cpb_removal_delay_నిడివి_minus1;
    uint32_t    dpb_output_delay_నిడివి_minus1;
    uint32_t    సమయం_స్థానభ్రంశం_నిడివి;
} StdVideoH264HrdParameters;

రకనిర్వచనం నిర్మాణం Std_Video_H264_Sequence_Parameter_సమితి_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_నిష్పత్తి_Idc          aspect_నిష్పత్తి_idc;
    uint16_t                            sar_వెడల్పు;
    uint16_t                            sar_ఎత్తు;
    uint8_t                             video_format;
    uint8_t                             రంగు_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             మాతృక_coefficients;
    uint32_t                            అంకె_units_లోపల_tick;
    uint32_t                            సమయం_scale;
    uint8_t                             max_అంకె_reorder_చట్రాలు;
    uint8_t                             max_dec_చట్రం_buffering;
    uint8_t                             chroma_sample_loc_type_శిఖరం_క్షేత్రం;
    uint8_t                             chroma_sample_loc_type_bottom_క్షేత్రం;
    uint32_t                            reserved1;
    స్థిరరాశి StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_సమితి_Vui;

రకనిర్వచనం నిర్మాణం StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    ప్రత్యక్ష_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_చట్రం_క్షేత్రం_flag : 1;
    uint32_t    చట్రం_mbs_only_flag : 1;
    uint32_t    delta_pic_క్రమం_always_zero_flag : 1;
    uint32_t    separate_రంగు_plane_flag : 1;
    uint32_t    gaps_లోపల_చట్రం_అంకె_విలువ_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    చట్రం_cropping_flag : 1;
    uint32_t    seq_scaling_మాతృక_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

రకనిర్వచనం నిర్మాణం StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_ముసుగు;
    uint16_t    use_default_scaling_మాతృక_ముసుగు;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_అంకె_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_అంకె_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_అంకె_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_అంకె_ELEMENTS];
} StdVideoH264ScalingLists;

రకనిర్వచనం నిర్మాణం Std_Video_H264_Sequence_Parameter_సమితి {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_సమితి_id;
    uint8_t                                       బిట్టు_లోతు_luma_minus8;
    uint8_t                                       బిట్టు_లోతు_chroma_minus8;
    uint8_t                                       log2_max_చట్రం_అంకె_minus4;
    StdVideoH264PocType                           pic_క్రమం_cnt_type;
    int32_t                                       స్థానభ్రంశం_for_non_ref_pic;
    int32_t                                       స్థానభ్రంశం_for_శిఖరం_గమ్యం_bottom_క్షేత్రం;
    uint8_t                                       log2_max_pic_క్రమం_cnt_lsb_minus4;
    uint8_t                                       అంకె_ref_చట్రాలు_లోపల_pic_క్రమం_cnt_చక్రం;
    uint8_t                                       max_అంకె_ref_చట్రాలు;
    uint8_t                                       reserved1;
    uint32_t                                      pic_వెడల్పు_లోపల_mbs_minus1;
    uint32_t                                      pic_ఎత్తు_లోపల_map_units_minus1;
    uint32_t                                      చట్రం_crop_ఎడమ_స్థానభ్రంశం;
    uint32_t                                      చట్రం_crop_కుడి_స్థానభ్రంశం;
    uint32_t                                      చట్రం_crop_శిఖరం_స్థానభ్రంశం;
    uint32_t                                      చట్రం_crop_bottom_స్థానభ్రంశం;
    uint32_t                                      reserved2;
    స్థిరరాశి int32_t*                                p_స్థానభ్రంశం_For_Ref_చట్రం;
    స్థిరరాశి StdVideoH264ScalingLists*               pScalingLists;
    స్థిరరాశి Std_Video_H264_Sequence_Parameter_సమితి_Vui*    p_Sequence_Parameter_సమితి_Vui;
} Std_Video_H264_Sequence_Parameter_సమితి;

రకనిర్వచనం నిర్మాణం StdVideoH264PpsFlags {
    uint32_t    transform_8x8_బహుళకం_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_క్షేత్రం_pic_క్రమం_లోపల_చట్రం_present_flag : 1;
    uint32_t    entropy_coding_బహుళకం_flag : 1;
    uint32_t    pic_scaling_మాతృక_present_flag : 1;
} StdVideoH264PpsFlags;

రకనిర్వచనం నిర్మాణం Std_Video_H264_Picture_Parameter_సమితి {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_సమితి_id;
    uint8_t                            pic_parameter_సమితి_id;
    uint8_t                            అంకె_ref_idx_l0_default_చురుకైన_minus1;
    uint8_t                            అంకె_ref_idx_l1_default_చురుకైన_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_సూచీ_స్థానభ్రంశం;
    int8_t                             రెండవ_chroma_qp_సూచీ_స్థానభ్రంశం;
    స్థిరరాశి StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_సమితి;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
