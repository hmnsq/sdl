#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_H264STD_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_h264std 1

#ضمن "vulkan_video_codecs_common.h"

#وصف_ڪريو STD_VIDEO_H264_CPB_CNT_LIST_سائيز  32U
#وصف_ڪريو STD_VIDEO_H264_SCALING_LIST_4_X4_انگ_LISTS 6U
#وصف_ڪريو STD_VIDEO_H264_SCALING_LIST_4_X4_انگ_ELEMENTS 16U
#وصف_ڪريو STD_VIDEO_H264_SCALING_LIST_8_X8_انگ_LISTS 6U
#وصف_ڪريو STD_VIDEO_H264_SCALING_LIST_8_X8_انگ_ELEMENTS 64U
#وصف_ڪريو STD_VIDEO_H264_MAX_انگ_LIST_REF   32U
#وصف_ڪريو STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#وصف_ڪريو STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

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
    STD_VIDEO_H264_PROFILE_IDC_مٿاهون = 100,
    STD_VIDEO_H264_PROFILE_IDC_مٿاهون_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_مٿاهون_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_مٿاهون_444_PREDICTIVE = 244,
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

تعريفنوع تعداد Std_Video_H264_Aspect_تناسب_Idc {
    STD_VIDEO_H264_ASPECT_تناسب_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_تناسب_IDC_چورس = 1,
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

تعريفنوع تعداد StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

تعريفنوع تعداد Std_Video_H264_Modification_جو_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_SHORT_رڪن_ڪٽيو = 0,
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_SHORT_رڪن_جوڙيو = 1,
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_LONG_رڪن = 2,
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_پڇاڙي = 3,
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_جو_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_جو_Pic_Nums_Idc;

تعريفنوع تعداد StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_پڇاڙي = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_رڪن = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_رڪن = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_رڪن = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_سيٽ_MAX_LONG_رڪن_اشاريو = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_رڪن = 6,
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

تعريفنوع تعداد Std_Video_H264_ٽڪرو_Type {
    STD_VIDEO_H264_ٽڪرو_TYPE_P = 0,
    STD_VIDEO_H264_ٽڪرو_TYPE_B = 1,
    STD_VIDEO_H264_ٽڪرو_TYPE_I = 2,
    STD_VIDEO_H264_ٽڪرو_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ٽڪرو_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_ٽڪرو_Type;

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
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_اڳياڙي = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_پڇاڙي_جو_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_پڇاڙي_جو_وهڪرو = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

تعريفنوع بنية StdVideoH264SpsVuiFlags {
    uint32_t    aspect_تناسب_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ڀريل_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_چوکٺو_شرح_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

تعريفنوع بنية StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     ٻٽو_انگ_شرح_scale;
    uint8_t     cpb_سائيز_scale;
    uint8_t     reserved1;
    uint32_t    ٻٽو_انگ_شرح_قدر_minus1[STD_VIDEO_H264_CPB_CNT_LIST_سائيز];
    uint32_t    cpb_سائيز_قدر_minus1[STD_VIDEO_H264_CPB_CNT_LIST_سائيز];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_سائيز];
    uint32_t    initial_cpb_removal_delay_ڊيگهائي_minus1;
    uint32_t    cpb_removal_delay_ڊيگهائي_minus1;
    uint32_t    dpb_output_delay_ڊيگهائي_minus1;
    uint32_t    وقت_وٿي_ڊيگهائي;
} StdVideoH264HrdParameters;

تعريفنوع بنية Std_Video_H264_Sequence_Parameter_سيٽ_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_تناسب_Idc          aspect_تناسب_idc;
    uint16_t                            sar_ويڪر;
    uint16_t                            sar_اوچائي;
    uint8_t                             video_format;
    uint8_t                             رنگ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ميٽرڪس_coefficients;
    uint32_t                            انگ_units_اندريون_tick;
    uint32_t                            وقت_scale;
    uint8_t                             max_انگ_reorder_چوکٺا;
    uint8_t                             max_dec_چوکٺو_buffering;
    uint8_t                             chroma_sample_loc_type_چوٽي_ميدان;
    uint8_t                             chroma_sample_loc_type_bottom_ميدان;
    uint32_t                            reserved1;
    ثابت StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_سيٽ_Vui;

تعريفنوع بنية StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    سڌو_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_چوکٺو_ميدان_flag : 1;
    uint32_t    چوکٺو_mbs_only_flag : 1;
    uint32_t    delta_pic_ترتيب_always_zero_flag : 1;
    uint32_t    separate_رنگ_plane_flag : 1;
    uint32_t    gaps_اندريون_چوکٺو_انگ_قدر_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    چوکٺو_cropping_flag : 1;
    uint32_t    seq_scaling_ميٽرڪس_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

تعريفنوع بنية StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_نقاب;
    uint16_t    use_default_scaling_ميٽرڪس_نقاب;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_انگ_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_انگ_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_انگ_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_انگ_ELEMENTS];
} StdVideoH264ScalingLists;

تعريفنوع بنية Std_Video_H264_Sequence_Parameter_سيٽ {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_سيٽ_id;
    uint8_t                                       ٻٽو_انگ_اونهائي_luma_minus8;
    uint8_t                                       ٻٽو_انگ_اونهائي_chroma_minus8;
    uint8_t                                       log2_max_چوکٺو_انگ_minus4;
    StdVideoH264PocType                           pic_ترتيب_cnt_type;
    int32_t                                       وٿي_for_non_ref_pic;
    int32_t                                       وٿي_for_چوٽي_منزل_bottom_ميدان;
    uint8_t                                       log2_max_pic_ترتيب_cnt_lsb_minus4;
    uint8_t                                       انگ_ref_چوکٺا_اندريون_pic_ترتيب_cnt_چڪر;
    uint8_t                                       max_انگ_ref_چوکٺا;
    uint8_t                                       reserved1;
    uint32_t                                      pic_ويڪر_اندريون_mbs_minus1;
    uint32_t                                      pic_اوچائي_اندريون_map_units_minus1;
    uint32_t                                      چوکٺو_crop_کاٻو_وٿي;
    uint32_t                                      چوکٺو_crop_ساڄو_وٿي;
    uint32_t                                      چوکٺو_crop_چوٽي_وٿي;
    uint32_t                                      چوکٺو_crop_bottom_وٿي;
    uint32_t                                      reserved2;
    ثابت int32_t*                                p_وٿي_For_Ref_چوکٺو;
    ثابت StdVideoH264ScalingLists*               pScalingLists;
    ثابت Std_Video_H264_Sequence_Parameter_سيٽ_Vui*    p_Sequence_Parameter_سيٽ_Vui;
} Std_Video_H264_Sequence_Parameter_سيٽ;

تعريفنوع بنية StdVideoH264PpsFlags {
    uint32_t    transform_8x8_گهڻائي_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_ميدان_pic_ترتيب_اندريون_چوکٺو_present_flag : 1;
    uint32_t    entropy_coding_گهڻائي_flag : 1;
    uint32_t    pic_scaling_ميٽرڪس_present_flag : 1;
} StdVideoH264PpsFlags;

تعريفنوع بنية Std_Video_H264_Picture_Parameter_سيٽ {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_سيٽ_id;
    uint8_t                            pic_parameter_سيٽ_id;
    uint8_t                            انگ_ref_idx_l0_default_سرگرم_minus1;
    uint8_t                            انگ_ref_idx_l1_default_سرگرم_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_اشاريو_وٿي;
    int8_t                             ٻيو_chroma_qp_اشاريو_وٿي;
    ثابت StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_سيٽ;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
