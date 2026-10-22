#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_H264STD_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_h264std 1

#ضمن "vulkan_video_codecs_common.h"

#تعریف_کړه STD_VIDEO_H264_CPB_CNT_LIST_اندازه  32U
#تعریف_کړه STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_LISTS 6U
#تعریف_کړه STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_ELEMENTS 16U
#تعریف_کړه STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_LISTS 6U
#تعریف_کړه STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_ELEMENTS 64U
#تعریف_کړه STD_VIDEO_H264_MAX_عدد_LIST_REF   32U
#تعریف_کړه STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#تعریف_کړه STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

تعريفنوع تعداد StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

تعريفنوع تعداد StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_لوړ = 100,
    STD_VIDEO_H264_PROFILE_IDC_لوړ_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_لوړ_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_لوړ_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

تعريفنوع تعداد StdVideoH264LevelIdc {
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

تعريفنوع تعداد StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

تعريفنوع تعداد Std_Video_H264_Aspect_نسبت_Idc {
    STD_VIDEO_H264_ASPECT_نسبت_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_مربع = 1,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_نسبت_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_نسبت_Idc;

تعريفنوع تعداد StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

تعريفنوع تعداد Std_Video_H264_Modification_د_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_SHORT_غړی_کمول = 0,
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_SHORT_غړی_جمع_کړه = 1,
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_LONG_غړی = 2,
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_پای_ټکی = 3,
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_د_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_د_Pic_Nums_Idc;

تعريفنوع تعداد StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_پای_ټکی = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_غړی = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_غړی = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_غړی = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_سېټ_MAX_LONG_غړی_شاخص = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_غړی = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

تعريفنوع تعداد StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

تعريفنوع تعداد StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

تعريفنوع تعداد Std_Video_H264_ټوټه_Type {
    STD_VIDEO_H264_ټوټه_TYPE_P = 0,
    STD_VIDEO_H264_ټوټه_TYPE_B = 1,
    STD_VIDEO_H264_ټوټه_TYPE_I = 2,
    STD_VIDEO_H264_ټوټه_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ټوټه_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_ټوټه_Type;

تعريفنوع تعداد StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

تعريفنوع تعداد StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_مختاړی = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_پای_ټکی_د_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_پای_ټکی_د_بهیر = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

تعريفنوع بنية StdVideoH264SpsVuiFlags {
    uint32_t    aspect_نسبت_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ډک_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_چوکاټ_شرح_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

تعريفنوع بنية StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     بټ_شرح_scale;
    uint8_t     cpb_اندازه_scale;
    uint8_t     reserved1;
    uint32_t    بټ_شرح_ارزښت_minus1[STD_VIDEO_H264_CPB_CNT_LIST_اندازه];
    uint32_t    cpb_اندازه_ارزښت_minus1[STD_VIDEO_H264_CPB_CNT_LIST_اندازه];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_اندازه];
    uint32_t    initial_cpb_removal_delay_اوږدتیا_minus1;
    uint32_t    cpb_removal_delay_اوږدتیا_minus1;
    uint32_t    dpb_output_delay_اوږدتیا_minus1;
    uint32_t    وخت_دننه_واټن_اوږدتیا;
} StdVideoH264HrdParameters;

تعريفنوع بنية Std_Video_H264_Sequence_Parameter_سېټ_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_نسبت_Idc          aspect_نسبت_idc;
    uint16_t                            sar_پلنوالی;
    uint16_t                            sar_لوړوالی;
    uint8_t                             video_format;
    uint8_t                             رنګ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ماتریکس_coefficients;
    uint32_t                            عدد_units_دننه_tick;
    uint32_t                            وخت_scale;
    uint8_t                             max_عدد_reorder_چوکاټونه;
    uint8_t                             max_dec_چوکاټ_buffering;
    uint8_t                             chroma_sample_loc_type_سر_ډګر;
    uint8_t                             chroma_sample_loc_type_bottom_ډګر;
    uint32_t                            reserved1;
    ثابت StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_سېټ_Vui;

تعريفنوع بنية StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    مستقیم_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_چوکاټ_ډګر_flag : 1;
    uint32_t    چوکاټ_mbs_only_flag : 1;
    uint32_t    delta_pic_ترتیب_always_zero_flag : 1;
    uint32_t    separate_رنګ_plane_flag : 1;
    uint32_t    gaps_دننه_چوکاټ_عدد_ارزښت_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    چوکاټ_cropping_flag : 1;
    uint32_t    seq_scaling_ماتریکس_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

تعريفنوع بنية StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_ماسک;
    uint16_t    use_default_scaling_ماتریکس_ماسک;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_ELEMENTS];
} StdVideoH264ScalingLists;

تعريفنوع بنية Std_Video_H264_Sequence_Parameter_سېټ {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_سېټ_id;
    uint8_t                                       بټ_ژوروالی_luma_minus8;
    uint8_t                                       بټ_ژوروالی_chroma_minus8;
    uint8_t                                       log2_max_چوکاټ_عدد_minus4;
    StdVideoH264PocType                           pic_ترتیب_cnt_type;
    int32_t                                       دننه_واټن_for_non_ref_pic;
    int32_t                                       دننه_واټن_for_سر_منزل_bottom_ډګر;
    uint8_t                                       log2_max_pic_ترتیب_cnt_lsb_minus4;
    uint8_t                                       عدد_ref_چوکاټونه_دننه_pic_ترتیب_cnt_دوره;
    uint8_t                                       max_عدد_ref_چوکاټونه;
    uint8_t                                       reserved1;
    uint32_t                                      pic_پلنوالی_دننه_mbs_minus1;
    uint32_t                                      pic_لوړوالی_دننه_map_units_minus1;
    uint32_t                                      چوکاټ_crop_کیڼ_دننه_واټن;
    uint32_t                                      چوکاټ_crop_ښی_دننه_واټن;
    uint32_t                                      چوکاټ_crop_سر_دننه_واټن;
    uint32_t                                      چوکاټ_crop_bottom_دننه_واټن;
    uint32_t                                      reserved2;
    ثابت int32_t*                                p_دننه_واټن_For_Ref_چوکاټ;
    ثابت StdVideoH264ScalingLists*               pScalingLists;
    ثابت Std_Video_H264_Sequence_Parameter_سېټ_Vui*    p_Sequence_Parameter_سېټ_Vui;
} Std_Video_H264_Sequence_Parameter_سېټ;

تعريفنوع بنية StdVideoH264PpsFlags {
    uint32_t    transform_8x8_ډېرپېښ_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_ډګر_pic_ترتیب_دننه_چوکاټ_present_flag : 1;
    uint32_t    entropy_coding_ډېرپېښ_flag : 1;
    uint32_t    pic_scaling_ماتریکس_present_flag : 1;
} StdVideoH264PpsFlags;

تعريفنوع بنية Std_Video_H264_Picture_Parameter_سېټ {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_سېټ_id;
    uint8_t                            pic_parameter_سېټ_id;
    uint8_t                            عدد_ref_idx_l0_default_فعال_minus1;
    uint8_t                            عدد_ref_idx_l1_default_فعال_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_شاخص_دننه_واټن;
    int8_t                             دوهم_chroma_qp_شاخص_دننه_واټن;
    ثابت StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_سېټ;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
