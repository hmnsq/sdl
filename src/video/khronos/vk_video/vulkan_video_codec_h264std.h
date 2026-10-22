#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H264STD_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h264std 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codecs_common.h"

#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_CPB_CNT_LIST_ಗಾತ್ರ  32U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_SCALING_LIST_4_X4_ಅಂಕೆ_LISTS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_SCALING_LIST_4_X4_ಅಂಕೆ_ELEMENTS 16U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_SCALING_LIST_8_X8_ಅಂಕೆ_LISTS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_SCALING_LIST_8_X8_ಅಂಕೆ_ELEMENTS 64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF   32U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_ಮೇಲಿನ = 100,
    STD_VIDEO_H264_PROFILE_IDC_ಮೇಲಿನ_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_ಮೇಲಿನ_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_ಮೇಲಿನ_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264LevelIdc {
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_H264_Aspect_ಅನುಪಾತ_Idc {
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_ವರ್ಗಫಲ = 1,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_ಅನುಪಾತ_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_ಅನುಪಾತ_Idc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_H264_Modification_ದ_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_SHORT_ಪದ_ಕಳೆ = 0,
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_SHORT_ಪದ_ಕೂಡಿಸು = 1,
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_LONG_ಪದ = 2,
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_ಕೊನೆ = 3,
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_ದ_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_ದ_Pic_Nums_Idc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_ಕೊನೆ = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_ಪದ = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_ಪದ = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_ಪದ = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_ಗಣ_MAX_LONG_ಪದ_ಸೂಚ್ಯಂಕ = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_ಪದ = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_H264_ತುಂಡು_Type {
    STD_VIDEO_H264_ತುಂಡು_TYPE_P = 0,
    STD_VIDEO_H264_ತುಂಡು_TYPE_B = 1,
    STD_VIDEO_H264_ತುಂಡು_TYPE_I = 2,
    STD_VIDEO_H264_ತುಂಡು_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ತುಂಡು_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_ತುಂಡು_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ಪೂರ್ವಪ್ರತ್ಯಯ = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ಕೊನೆ_ದ_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ಕೊನೆ_ದ_ಹರಿವು = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH264SpsVuiFlags {
    uint32_t    aspect_ಅನುಪಾತ_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ತುಂಬಿದ_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_ಚೌಕಟ್ಟು_ದರ_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     ಬಿಟ್_ದರ_scale;
    uint8_t     cpb_ಗಾತ್ರ_scale;
    uint8_t     reserved1;
    uint32_t    ಬಿಟ್_ದರ_ಮೌಲ್ಯ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    cpb_ಗಾತ್ರ_ಮೌಲ್ಯ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_ಗಾತ್ರ];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    initial_cpb_removal_delay_ಉದ್ದಳತೆ_minus1;
    uint32_t    cpb_removal_delay_ಉದ್ದಳತೆ_minus1;
    uint32_t    dpb_output_delay_ಉದ್ದಳತೆ_minus1;
    uint32_t    ಸಮಯ_ಸ್ಥಾನಾಂತರ_ಉದ್ದಳತೆ;
} StdVideoH264HrdParameters;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H264_Sequence_Parameter_ಗಣ_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_ಅನುಪಾತ_Idc          aspect_ಅನುಪಾತ_idc;
    uint16_t                            sar_ಅಗಲ;
    uint16_t                            sar_ಎತ್ತರ;
    uint8_t                             video_format;
    uint8_t                             ಬಣ್ಣ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ಮಾತೃಕೆ_coefficients;
    uint32_t                            ಅಂಕೆ_units_ಒಳ_tick;
    uint32_t                            ಸಮಯ_scale;
    uint8_t                             max_ಅಂಕೆ_reorder_ಚೌಕಟ್ಟುಗಳು;
    uint8_t                             max_dec_ಚೌಕಟ್ಟು_buffering;
    uint8_t                             chroma_sample_loc_type_ತುದಿ_ಕ್ಷೇತ್ರ;
    uint8_t                             chroma_sample_loc_type_bottom_ಕ್ಷೇತ್ರ;
    uint32_t                            reserved1;
    ಸ್ಥಿರಾಂಕ StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_ಗಣ_Vui;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    ನೇರ_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_ಚೌಕಟ್ಟು_ಕ್ಷೇತ್ರ_flag : 1;
    uint32_t    ಚೌಕಟ್ಟು_mbs_only_flag : 1;
    uint32_t    delta_pic_ಕ್ರಮ_always_zero_flag : 1;
    uint32_t    separate_ಬಣ್ಣ_plane_flag : 1;
    uint32_t    gaps_ಒಳ_ಚೌಕಟ್ಟು_ಅಂಕೆ_ಮೌಲ್ಯ_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    ಚೌಕಟ್ಟು_cropping_flag : 1;
    uint32_t    seq_scaling_ಮಾತೃಕೆ_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_ಮುಖವಾಡ;
    uint16_t    use_default_scaling_ಮಾತೃಕೆ_ಮುಖವಾಡ;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_ಅಂಕೆ_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_ಅಂಕೆ_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_ಅಂಕೆ_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_ಅಂಕೆ_ELEMENTS];
} StdVideoH264ScalingLists;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H264_Sequence_Parameter_ಗಣ {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_ಗಣ_id;
    uint8_t                                       ಬಿಟ್_ಆಳ_luma_minus8;
    uint8_t                                       ಬಿಟ್_ಆಳ_chroma_minus8;
    uint8_t                                       log2_max_ಚೌಕಟ್ಟು_ಅಂಕೆ_minus4;
    StdVideoH264PocType                           pic_ಕ್ರಮ_cnt_type;
    int32_t                                       ಸ್ಥಾನಾಂತರ_for_non_ref_pic;
    int32_t                                       ಸ್ಥಾನಾಂತರ_for_ತುದಿ_ಗಮ್ಯ_bottom_ಕ್ಷೇತ್ರ;
    uint8_t                                       log2_max_pic_ಕ್ರಮ_cnt_lsb_minus4;
    uint8_t                                       ಅಂಕೆ_ref_ಚೌಕಟ್ಟುಗಳು_ಒಳ_pic_ಕ್ರಮ_cnt_ಚಕ್ರ;
    uint8_t                                       max_ಅಂಕೆ_ref_ಚೌಕಟ್ಟುಗಳು;
    uint8_t                                       reserved1;
    uint32_t                                      pic_ಅಗಲ_ಒಳ_mbs_minus1;
    uint32_t                                      pic_ಎತ್ತರ_ಒಳ_map_units_minus1;
    uint32_t                                      ಚೌಕಟ್ಟು_crop_ಎಡ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      ಚೌಕಟ್ಟು_crop_ಬಲ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      ಚೌಕಟ್ಟು_crop_ತುದಿ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      ಚೌಕಟ್ಟು_crop_bottom_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      reserved2;
    ಸ್ಥಿರಾಂಕ int32_t*                                p_ಸ್ಥಾನಾಂತರ_For_Ref_ಚೌಕಟ್ಟು;
    ಸ್ಥಿರಾಂಕ StdVideoH264ScalingLists*               pScalingLists;
    ಸ್ಥಿರಾಂಕ Std_Video_H264_Sequence_Parameter_ಗಣ_Vui*    p_Sequence_Parameter_ಗಣ_Vui;
} Std_Video_H264_Sequence_Parameter_ಗಣ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH264PpsFlags {
    uint32_t    transform_8x8_ಬಹುಲಕ_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_ಕ್ಷೇತ್ರ_pic_ಕ್ರಮ_ಒಳ_ಚೌಕಟ್ಟು_present_flag : 1;
    uint32_t    entropy_coding_ಬಹುಲಕ_flag : 1;
    uint32_t    pic_scaling_ಮಾತೃಕೆ_present_flag : 1;
} StdVideoH264PpsFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H264_Picture_Parameter_ಗಣ {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_ಗಣ_id;
    uint8_t                            pic_parameter_ಗಣ_id;
    uint8_t                            ಅಂಕೆ_ref_idx_l0_default_ಸಕ್ರಿಯ_minus1;
    uint8_t                            ಅಂಕೆ_ref_idx_l1_default_ಸಕ್ರಿಯ_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ;
    int8_t                             ಎರಡನೇ_chroma_qp_ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ;
    ಸ್ಥಿರಾಂಕ StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_ಗಣ;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
