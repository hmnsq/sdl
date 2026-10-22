#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H265STD_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H265STD_H_ 1

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



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h265std 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codecs_common.h"

#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_CPB_CNT_LIST_ಗಾತ್ರ  32U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ 7U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_4_X4_ಅಂಕೆ_LISTS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_4_X4_ಅಂಕೆ_ELEMENTS 16U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_8_X8_ಅಂಕೆ_LISTS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_8_X8_ಅಂಕೆ_ELEMENTS 64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_16_X16_ಅಂಕೆ_LISTS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_16_X16_ಅಂಕೆ_ELEMENTS 64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_32_X32_ಅಂಕೆ_LISTS 2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_SCALING_LIST_32_X32_ಅಂಕೆ_ELEMENTS 64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_LIST_ಗಾತ್ರ 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_TILE_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_LIST_ಗಾತ್ರ 19U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_TILE_ಅಡ್ಡಸಾಲುಗಳು_LIST_ಗಾತ್ರ 21U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_ಗಾತ್ರ 3U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_ಗಾತ್ರ 128U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF   15U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_SHORT_ಪದ_REF_PIC_SETS 64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_DPB_ಗಾತ್ರ       16U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_LONG_ಪದ_REF_PICS_SPS 32U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_LONG_ಪದ_PICS 16U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_MAX_DELTA_POC      48U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH265LevelIdc {
    STD_VIDEO_H265_LEVEL_IDC_1_0 = 0,
    STD_VIDEO_H265_LEVEL_IDC_2_0 = 1,
    STD_VIDEO_H265_LEVEL_IDC_2_1 = 2,
    STD_VIDEO_H265_LEVEL_IDC_3_0 = 3,
    STD_VIDEO_H265_LEVEL_IDC_3_1 = 4,
    STD_VIDEO_H265_LEVEL_IDC_4_0 = 5,
    STD_VIDEO_H265_LEVEL_IDC_4_1 = 6,
    STD_VIDEO_H265_LEVEL_IDC_5_0 = 7,
    STD_VIDEO_H265_LEVEL_IDC_5_1 = 8,
    STD_VIDEO_H265_LEVEL_IDC_5_2 = 9,
    STD_VIDEO_H265_LEVEL_IDC_6_0 = 10,
    STD_VIDEO_H265_LEVEL_IDC_6_1 = 11,
    STD_VIDEO_H265_LEVEL_IDC_6_2 = 12,
    STD_VIDEO_H265_LEVEL_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_LEVEL_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265LevelIdc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_H265_ತುಂಡು_Type {
    STD_VIDEO_H265_ತುಂಡು_TYPE_B = 0,
    STD_VIDEO_H265_ತುಂಡು_TYPE_P = 1,
    STD_VIDEO_H265_ತುಂಡು_TYPE_I = 2,
    STD_VIDEO_H265_ತುಂಡು_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ತುಂಡು_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_ತುಂಡು_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_H265_Aspect_ಅನುಪಾತ_Idc {
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_ವರ್ಗಫಲ = 1,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_ಅನುಪಾತ_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_ಅನುಪಾತ_Idc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ];
    uint8_t     max_ಅಂಕೆ_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ];
} StdVideoH265DecPicBufMgr;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265SubLayerHrdParameters {
    uint32_t    ಬಿಟ್_ದರ_ಮೌಲ್ಯ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    cpb_ಗಾತ್ರ_ಮೌಲ್ಯ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    cpb_ಗಾತ್ರ_du_ಮೌಲ್ಯ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    ಬಿಟ್_ದರ_du_ಮೌಲ್ಯ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ಗಾತ್ರ];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_ಒಳ_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_ದರ_general_flag : 8;
    uint32_t    fixed_pic_ದರ_within_cvs_flag : 8;
    uint32_t    ಕೆಳಗಿನ_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_ಭಾಜಕ_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_ಉದ್ದಳತೆ_minus1;
    uint8_t                                     dpb_output_delay_du_ಉದ್ದಳತೆ_minus1;
    uint8_t                                     ಬಿಟ್_ದರ_scale;
    uint8_t                                     cpb_ಗಾತ್ರ_scale;
    uint8_t                                     cpb_ಗಾತ್ರ_du_scale;
    uint8_t                                     initial_cpb_removal_delay_ಉದ್ದಳತೆ_minus1;
    uint8_t                                     au_cpb_removal_delay_ಉದ್ದಳತೆ_minus1;
    uint8_t                                     dpb_output_delay_ಉದ್ದಳತೆ_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ];
    uint16_t                                    elemental_duration_ಒಳ_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ಗಾತ್ರ];
    uint16_t                                    reserved[3];
    ಸ್ಥಿರಾಂಕ StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    ಸ್ಥಿರಾಂಕ StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_ಗಮ್ಯ_timing_flag : 1;
} StdVideoH265VpsFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_ಮೂಲ_flag : 1;
    uint32_t    general_interlaced_ಮೂಲ_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_ಚೌಕಟ್ಟು_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Video_Parameter_ಗಣ {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_ಗಣ_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_ಅಂಕೆ_units_ಒಳ_tick;
    uint32_t                               vps_ಸಮಯ_scale;
    uint32_t                               vps_ಅಂಕೆ_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    ಸ್ಥಿರಾಂಕ StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    ಸ್ಥಿರಾಂಕ StdVideoH265HrdParameters*       pHrdParameters;
    ಸ್ಥಿರಾಂಕ StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_ಗಣ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_ಅಂಕೆ_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_ಅಂಕೆ_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_ಅಂಕೆ_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_ಅಂಕೆ_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_ಅಂಕೆ_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_ಅಂಕೆ_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_ಅಂಕೆ_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_ಅಂಕೆ_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_ಅಂಕೆ_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_ಅಂಕೆ_LISTS];
} StdVideoH265ScalingLists;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265SpsVuiFlags {
    uint32_t    aspect_ಅನುಪಾತ_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ತುಂಬಿದ_range_flag : 1;
    uint32_t    ಬಣ್ಣ_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    ಕ್ಷೇತ್ರ_seq_flag : 1;
    uint32_t    ಚೌಕಟ್ಟು_ಕ್ಷೇತ್ರ_info_present_flag : 1;
    uint32_t    default_display_ಕಿಟಕಿ_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_ಗಮ್ಯ_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Sequence_Parameter_ಗಣ_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_ಅನುಪಾತ_Idc          aspect_ಅನುಪಾತ_idc;
    uint16_t                            sar_ಅಗಲ;
    uint16_t                            sar_ಎತ್ತರ;
    uint8_t                             video_format;
    uint8_t                             ಬಣ್ಣ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ಮಾತೃಕೆ_coeffs;
    uint8_t                             chroma_sample_loc_type_ತುದಿ_ಕ್ಷೇತ್ರ;
    uint8_t                             chroma_sample_loc_type_bottom_ಕ್ಷೇತ್ರ;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_ಎಡ_ಸ್ಥಾನಾಂತರ;
    uint16_t                            def_disp_win_ಬಲ_ಸ್ಥಾನಾಂತರ;
    uint16_t                            def_disp_win_ತುದಿ_ಸ್ಥಾನಾಂತರ;
    uint16_t                            def_disp_win_bottom_ಸ್ಥಾನಾಂತರ;
    uint32_t                            vui_ಅಂಕೆ_units_ಒಳ_tick;
    uint32_t                            vui_ಸಮಯ_scale;
    uint32_t                            vui_ಅಂಕೆ_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_ಬೈಟುಗಳು_ಪ್ರತಿ_pic_denom;
    uint8_t                             max_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_min_cu_denom;
    uint8_t                             log2_max_mv_ಉದ್ದಳತೆ_horizontal;
    uint8_t                             log2_max_mv_ಉದ್ದಳತೆ_vertical;
    ಸ್ಥಿರಾಂಕ StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_ಗಣ_Vui;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_ಗಾತ್ರ][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_ಗಾತ್ರ];
} StdVideoH265PredictorPaletteEntries;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_ಬಣ್ಣ_plane_flag : 1;
    uint32_t    conformance_ಕಿಟಕಿ_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_ದತ್ತಾಂಶ_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_ಸ್ಥಾನಾಂತರ_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_ಪದ_ref_pics_present_flag : 1;
    uint32_t    sps_temporal_mvp_enabled_flag : 1;
    uint32_t    strong_intra_smoothing_enabled_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
    uint32_t    sps_extension_present_flag : 1;
    uint32_t    sps_range_extension_flag : 1;
    uint32_t    transform_skip_rotation_enabled_flag : 1;
    uint32_t    transform_skip_context_enabled_flag : 1;
    uint32_t    implicit_rdpcm_enabled_flag : 1;
    uint32_t    explicit_rdpcm_enabled_flag : 1;
    uint32_t    extended_precision_processing_flag : 1;
    uint32_t    intra_smoothing_disabled_flag : 1;
    uint32_t    ಮೇಲಿನ_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_ಬಹುಲಕ_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ_Flags {
    uint32_t    inter_ref_pic_ಗಣ_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ {
    Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               ಬಳಸಿದ_by_curr_pic_flag;
    uint16_t                               ಬಳಸಿದ_by_curr_pic_s0_flag;
    uint16_t                               ಬಳಸಿದ_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                ಅಂಕೆ_negative_pics;
    uint8_t                                ಅಂಕೆ_ಧನಾತ್ಮಕ_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_ಗಾತ್ರ];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_ಗಾತ್ರ];
} Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Long_ಪದ_Ref_Pics_Sps {
    uint32_t    ಬಳಸಿದ_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_ಪದ_REF_PICS_SPS];
} Std_Video_H265_Long_ಪದ_Ref_Pics_Sps;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Sequence_Parameter_ಗಣ {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_ಅಗಲ_ಒಳ_luma_samples;
    uint32_t                                      pic_ಎತ್ತರ_ಒಳ_luma_samples;
    uint8_t                                       sps_video_parameter_ಗಣ_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_ಗಣ_id;
    uint8_t                                       ಬಿಟ್_ಆಳ_luma_minus8;
    uint8_t                                       ಬಿಟ್_ಆಳ_chroma_minus8;
    uint8_t                                       log2_max_pic_ಕ್ರಮ_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_ಖಂಡ_ಗಾತ್ರ_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_ಖಂಡ_ಗಾತ್ರ;
    uint8_t                                       log2_min_luma_transform_ಖಂಡ_ಗಾತ್ರ_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_ಖಂಡ_ಗಾತ್ರ;
    uint8_t                                       max_transform_hierarchy_ಆಳ_inter;
    uint8_t                                       max_transform_hierarchy_ಆಳ_intra;
    uint8_t                                       ಅಂಕೆ_short_ಪದ_ref_pic_sets;
    uint8_t                                       ಅಂಕೆ_long_ಪದ_ref_pics_sps;
    uint8_t                                       pcm_sample_ಬಿಟ್_ಆಳ_luma_minus1;
    uint8_t                                       pcm_sample_ಬಿಟ್_ಆಳ_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_ಖಂಡ_ಗಾತ್ರ_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_ಖಂಡ_ಗಾತ್ರ;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_ಗಾತ್ರ;
    uint8_t                                       delta_palette_max_predictor_ಗಾತ್ರ;
    uint8_t                                       motion_ಸದಿಶ_resolution_control_idc;
    uint8_t                                       sps_ಅಂಕೆ_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_ಎಡ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      conf_win_ಬಲ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      conf_win_ತುದಿ_ಸ್ಥಾನಾಂತರ;
    uint32_t                                      conf_win_bottom_ಸ್ಥಾನಾಂತರ;
    ಸ್ಥಿರಾಂಕ StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    ಸ್ಥಿರಾಂಕ StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    ಸ್ಥಿರಾಂಕ StdVideoH265ScalingLists*               pScalingLists;
    ಸ್ಥಿರಾಂಕ Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ*         p_Short_ಪದ_Ref_Pic_ಗಣ;
    ಸ್ಥಿರಾಂಕ Std_Video_H265_Long_ಪದ_Ref_Pics_Sps*         p_Long_ಪದ_Ref_Pics_Sps;
    ಸ್ಥಿರಾಂಕ Std_Video_H265_Sequence_Parameter_ಗಣ_Vui*    p_Sequence_Parameter_ಗಣ_Vui;
    ಸ್ಥಿರಾಂಕ StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_ಗಣ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoH265PpsFlags {
    uint32_t    dependent_ತುಂಡು_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_ದತ್ತಾಂಶ_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_ತುಂಡು_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    ಏಕರೂಪ_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_ದತ್ತಾಂಶ_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    ತುಂಡು_segment_ಶೀರ್ಷಿಕೆ_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_ಸ್ಥಾನಾಂತರ_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_ಬಣ್ಣ_transform_enabled_flag : 1;
    uint32_t    pps_ತುಂಡು_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_H265_Picture_Parameter_ಗಣ {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_ಗಣ_id;
    uint8_t                                       pps_seq_parameter_ಗಣ_id;
    uint8_t                                       sps_video_parameter_ಗಣ_id;
    uint8_t                                       ಅಂಕೆ_extra_ತುಂಡು_ಶೀರ್ಷಿಕೆ_ಬಿಟ್ಟುಗಳು;
    uint8_t                                       ಅಂಕೆ_ref_idx_l0_default_ಸಕ್ರಿಯ_minus1;
    uint8_t                                       ಅಂಕೆ_ref_idx_l1_default_ಸಕ್ರಿಯ_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_ಆಳ;
    int8_t                                        pps_cb_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                        pps_cr_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                        pps_beta_ಸ್ಥಾನಾಂತರ_div2;
    int8_t                                        pps_tc_ಸ್ಥಾನಾಂತರ_div2;
    uint8_t                                       log2_parallel_ವಿಲೀನ_level_minus2;
    uint8_t                                       log2_max_transform_skip_ಖಂಡ_ಗಾತ್ರ_minus2;
    uint8_t                                       diff_cu_chroma_qp_ಸ್ಥಾನಾಂತರ_ಆಳ;
    uint8_t                                       chroma_qp_ಸ್ಥಾನಾಂತರ_list_len_minus1;
    int8_t                                        cb_qp_ಸ್ಥಾನಾಂತರ_list[STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_LIST_ಗಾತ್ರ];
    int8_t                                        cr_qp_ಸ್ಥಾನಾಂತರ_list[STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_LIST_ಗಾತ್ರ];
    uint8_t                                       log2_sao_ಸ್ಥಾನಾಂತರ_scale_luma;
    uint8_t                                       log2_sao_ಸ್ಥಾನಾಂತರ_scale_chroma;
    int8_t                                        pps_act_y_qp_ಸ್ಥಾನಾಂತರ_plus5;
    int8_t                                        pps_act_cb_qp_ಸ್ಥಾನಾಂತರ_plus5;
    int8_t                                        pps_act_cr_qp_ಸ್ಥಾನಾಂತರ_plus3;
    uint8_t                                       pps_ಅಂಕೆ_palette_predictor_initializers;
    uint8_t                                       luma_ಬಿಟ್_ಆಳ_ನಮೂದು_minus8;
    uint8_t                                       chroma_ಬಿಟ್_ಆಳ_ನಮೂದು_minus8;
    uint8_t                                       ಅಂಕೆ_tile_columns_minus1;
    uint8_t                                       ಅಂಕೆ_tile_ಅಡ್ಡಸಾಲುಗಳು_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      ಸ್ತಂಭ_ಅಗಲ_minus1[STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_TILE_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_LIST_ಗಾತ್ರ];
    uint16_t                                      ಅಡ್ಡಸಾಲು_ಎತ್ತರ_minus1[STD_VIDEO_H265_CHROMA_QP_ಸ್ಥಾನಾಂತರ_TILE_ಅಡ್ಡಸಾಲುಗಳು_LIST_ಗಾತ್ರ];
    uint32_t                                      reserved3;
    ಸ್ಥಿರಾಂಕ StdVideoH265ScalingLists*               pScalingLists;
    ಸ್ಥಿರಾಂಕ StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_ಗಣ;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
