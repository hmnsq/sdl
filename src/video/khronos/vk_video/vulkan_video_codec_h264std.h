#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_H264STD_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H264STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h264std 1

#شامل "vulkan_video_codecs_common.h"

#تعریف_کرو STD_VIDEO_H264_CPB_CNT_LIST_سائز  32U
#تعریف_کرو STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_LISTS 6U
#تعریف_کرو STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_ELEMENTS 16U
#تعریف_کرو STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_LISTS 6U
#تعریف_کرو STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_ELEMENTS 64U
#تعریف_کرو STD_VIDEO_H264_MAX_عدد_LIST_REF   32U
#تعریف_کرو STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#تعریف_کرو STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

قسمتعریف شمار StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

قسمتعریف شمار StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_بلند = 100,
    STD_VIDEO_H264_PROFILE_IDC_بلند_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_بلند_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_بلند_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

قسمتعریف شمار StdVideoH264LevelIdc {
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

قسمتعریف شمار StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

قسمتعریف شمار Std_Video_H264_Aspect_تناسب_Idc {
    STD_VIDEO_H264_ASPECT_تناسب_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_مربع = 1,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_تناسب_Idc;

قسمتعریف شمار StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

قسمتعریف شمار Std_Video_H264_Modification_کا_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_SHORT_رکن_تفریق = 0,
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_SHORT_رکن_جوڑو = 1,
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_LONG_رکن = 2,
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_انتہا = 3,
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_کا_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_کا_Pic_Nums_Idc;

قسمتعریف شمار StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_انتہا = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_رکن = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_رکن = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_رکن = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_سیٹ_MAX_LONG_رکن_اشاریہ = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_رکن = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

قسمتعریف شمار StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

قسمتعریف شمار StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

قسمتعریف شمار Std_Video_H264_قاش_Type {
    STD_VIDEO_H264_قاش_TYPE_P = 0,
    STD_VIDEO_H264_قاش_TYPE_B = 1,
    STD_VIDEO_H264_قاش_TYPE_I = 2,
    STD_VIDEO_H264_قاش_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_قاش_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_قاش_Type;

قسمتعریف شمار StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

قسمتعریف شمار StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_سابقہ = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_انتہا_کا_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_انتہا_کا_دھارا = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

قسمتعریف ساخت StdVideoH264SpsVuiFlags {
    uint32_t    aspect_تناسب_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_بھرا_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_چوکھٹا_شرح_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

قسمتعریف ساخت StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     ثنائی_ہندسہ_شرح_scale;
    uint8_t     cpb_سائز_scale;
    uint8_t     reserved1;
    uint32_t    ثنائی_ہندسہ_شرح_قدر_minus1[STD_VIDEO_H264_CPB_CNT_LIST_سائز];
    uint32_t    cpb_سائز_قدر_minus1[STD_VIDEO_H264_CPB_CNT_LIST_سائز];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_سائز];
    uint32_t    initial_cpb_removal_delay_لمبائی_minus1;
    uint32_t    cpb_removal_delay_لمبائی_minus1;
    uint32_t    dpb_output_delay_لمبائی_minus1;
    uint32_t    وقت_انحراف_لمبائی;
} StdVideoH264HrdParameters;

قسمتعریف ساخت Std_Video_H264_Sequence_Parameter_سیٹ_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_تناسب_Idc          aspect_تناسب_idc;
    uint16_t                            sar_چوڑائی;
    uint16_t                            sar_اونچائی;
    uint8_t                             video_format;
    uint8_t                             رنگ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             میٹرکس_coefficients;
    uint32_t                            عدد_units_اندر_tick;
    uint32_t                            وقت_scale;
    uint8_t                             max_عدد_reorder_چوکھٹے;
    uint8_t                             max_dec_چوکھٹا_buffering;
    uint8_t                             chroma_sample_loc_type_چوٹی_میدان;
    uint8_t                             chroma_sample_loc_type_bottom_میدان;
    uint32_t                            reserved1;
    ثابت StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_سیٹ_Vui;

قسمتعریف ساخت StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    براہ_راست_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_چوکھٹا_میدان_flag : 1;
    uint32_t    چوکھٹا_mbs_only_flag : 1;
    uint32_t    delta_pic_ترتیب_always_zero_flag : 1;
    uint32_t    separate_رنگ_plane_flag : 1;
    uint32_t    gaps_اندر_چوکھٹا_عدد_قدر_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    چوکھٹا_cropping_flag : 1;
    uint32_t    seq_scaling_میٹرکس_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

قسمتعریف ساخت StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_نقاب;
    uint16_t    use_default_scaling_میٹرکس_نقاب;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_عدد_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_عدد_ELEMENTS];
} StdVideoH264ScalingLists;

قسمتعریف ساخت Std_Video_H264_Sequence_Parameter_سیٹ {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_سیٹ_id;
    uint8_t                                       ثنائی_ہندسہ_گہرائی_luma_minus8;
    uint8_t                                       ثنائی_ہندسہ_گہرائی_chroma_minus8;
    uint8_t                                       log2_max_چوکھٹا_عدد_minus4;
    StdVideoH264PocType                           pic_ترتیب_cnt_type;
    int32_t                                       انحراف_for_non_ref_pic;
    int32_t                                       انحراف_for_چوٹی_مقصد_bottom_میدان;
    uint8_t                                       log2_max_pic_ترتیب_cnt_lsb_minus4;
    uint8_t                                       عدد_ref_چوکھٹے_اندر_pic_ترتیب_cnt_چکر;
    uint8_t                                       max_عدد_ref_چوکھٹے;
    uint8_t                                       reserved1;
    uint32_t                                      pic_چوڑائی_اندر_mbs_minus1;
    uint32_t                                      pic_اونچائی_اندر_map_units_minus1;
    uint32_t                                      چوکھٹا_crop_بایاں_انحراف;
    uint32_t                                      چوکھٹا_crop_دایاں_انحراف;
    uint32_t                                      چوکھٹا_crop_چوٹی_انحراف;
    uint32_t                                      چوکھٹا_crop_bottom_انحراف;
    uint32_t                                      reserved2;
    ثابت int32_t*                                p_انحراف_For_Ref_چوکھٹا;
    ثابت StdVideoH264ScalingLists*               pScalingLists;
    ثابت Std_Video_H264_Sequence_Parameter_سیٹ_Vui*    p_Sequence_Parameter_سیٹ_Vui;
} Std_Video_H264_Sequence_Parameter_سیٹ;

قسمتعریف ساخت StdVideoH264PpsFlags {
    uint32_t    transform_8x8_منوال_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_میدان_pic_ترتیب_اندر_چوکھٹا_present_flag : 1;
    uint32_t    entropy_coding_منوال_flag : 1;
    uint32_t    pic_scaling_میٹرکس_present_flag : 1;
} StdVideoH264PpsFlags;

قسمتعریف ساخت Std_Video_H264_Picture_Parameter_سیٹ {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_سیٹ_id;
    uint8_t                            pic_parameter_سیٹ_id;
    uint8_t                            عدد_ref_idx_l0_default_فعال_minus1;
    uint8_t                            عدد_ref_idx_l1_default_فعال_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_اشاریہ_انحراف;
    int8_t                             دوسرا_chroma_qp_اشاریہ_انحراف;
    ثابت StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_سیٹ;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
