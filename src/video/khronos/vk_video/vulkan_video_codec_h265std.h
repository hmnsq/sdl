#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H265STD_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H265STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h265std 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codecs_common.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_CPB_CNT_LIST_ਮਾਪ  32U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ 7U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_4_X4_ਅੰਕ_LISTS 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_4_X4_ਅੰਕ_ELEMENTS 16U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_8_X8_ਅੰਕ_LISTS 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_8_X8_ਅੰਕ_ELEMENTS 64U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_16_X16_ਅੰਕ_LISTS 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_16_X16_ਅੰਕ_ELEMENTS 64U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_32_X32_ਅੰਕ_LISTS 2U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_SCALING_LIST_32_X32_ਅੰਕ_ELEMENTS 64U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_LIST_ਮਾਪ 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_TILE_ਖਾਨੇ_ਗਿਣਤੀ_LIST_ਮਾਪ 19U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_TILE_ਪੰਕਤੀਆਂ_LIST_ਮਾਪ 21U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_ਮਾਪ 3U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_ਮਾਪ 128U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF   15U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_SHORT_ਪਦ_REF_PIC_SETS 64U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_DPB_ਮਾਪ       16U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_LONG_ਪਦ_REF_PICS_SPS 32U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_LONG_ਪਦ_PICS 16U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_MAX_DELTA_POC      48U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH265LevelIdc {
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_H265_ਟੁਕੜਾ_Type {
    STD_VIDEO_H265_ਟੁਕੜਾ_TYPE_B = 0,
    STD_VIDEO_H265_ਟੁਕੜਾ_TYPE_P = 1,
    STD_VIDEO_H265_ਟੁਕੜਾ_TYPE_I = 2,
    STD_VIDEO_H265_ਟੁਕੜਾ_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ਟੁਕੜਾ_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_ਟੁਕੜਾ_Type;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_H265_Aspect_ਅਨੁਪਾਤ_Idc {
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_ਵਰਗਫਲ = 1,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_ਅਨੁਪਾਤ_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_ਅਨੁਪਾਤ_Idc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ];
    uint8_t     max_ਅੰਕ_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ];
} StdVideoH265DecPicBufMgr;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265SubLayerHrdParameters {
    uint32_t    ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਰ_ਮੁੱਲ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    cpb_ਮਾਪ_ਮੁੱਲ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    cpb_ਮਾਪ_du_ਮੁੱਲ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਰ_du_ਮੁੱਲ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_ਵਿੱਚ_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_ਦਰ_general_flag : 8;
    uint32_t    fixed_pic_ਦਰ_within_cvs_flag : 8;
    uint32_t    ਨੀਵਾਂ_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_ਭਾਜਕ_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_ਲੰਮਾਈ_minus1;
    uint8_t                                     dpb_output_delay_du_ਲੰਮਾਈ_minus1;
    uint8_t                                     ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਰ_scale;
    uint8_t                                     cpb_ਮਾਪ_scale;
    uint8_t                                     cpb_ਮਾਪ_du_scale;
    uint8_t                                     initial_cpb_removal_delay_ਲੰਮਾਈ_minus1;
    uint8_t                                     au_cpb_removal_delay_ਲੰਮਾਈ_minus1;
    uint8_t                                     dpb_output_delay_ਲੰਮਾਈ_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ];
    uint16_t                                    elemental_duration_ਵਿੱਚ_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_ਮਾਪ];
    uint16_t                                    reserved[3];
    ਅਚਲ StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    ਅਚਲ StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_ਮੰਜ਼ਿਲ_timing_flag : 1;
} StdVideoH265VpsFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_ਸਰੋਤ_flag : 1;
    uint32_t    general_interlaced_ਸਰੋਤ_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_ਚੌਖਟਾ_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Video_Parameter_ਸੈੱਟ {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_ਸੈੱਟ_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_ਅੰਕ_units_ਵਿੱਚ_tick;
    uint32_t                               vps_ਸਮਾਂ_scale;
    uint32_t                               vps_ਅੰਕ_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    ਅਚਲ StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    ਅਚਲ StdVideoH265HrdParameters*       pHrdParameters;
    ਅਚਲ StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_ਸੈੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_ਅੰਕ_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_ਅੰਕ_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_ਅੰਕ_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_ਅੰਕ_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_ਅੰਕ_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_ਅੰਕ_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_ਅੰਕ_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_ਅੰਕ_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_ਅੰਕ_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_ਅੰਕ_LISTS];
} StdVideoH265ScalingLists;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265SpsVuiFlags {
    uint32_t    aspect_ਅਨੁਪਾਤ_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ਭਰਿਆ_range_flag : 1;
    uint32_t    ਰੰਗ_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    ਖੇਤਰ_seq_flag : 1;
    uint32_t    ਚੌਖਟਾ_ਖੇਤਰ_info_present_flag : 1;
    uint32_t    default_display_ਖਿੜਕੀ_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_ਮੰਜ਼ਿਲ_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Sequence_Parameter_ਸੈੱਟ_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_ਅਨੁਪਾਤ_Idc          aspect_ਅਨੁਪਾਤ_idc;
    uint16_t                            sar_ਚੌੜਾਈ;
    uint16_t                            sar_ਉਚਾਈ;
    uint8_t                             video_format;
    uint8_t                             ਰੰਗ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ਮੈਟ੍ਰਿਕਸ_coeffs;
    uint8_t                             chroma_sample_loc_type_ਸਿਖਰ_ਖੇਤਰ;
    uint8_t                             chroma_sample_loc_type_bottom_ਖੇਤਰ;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_ਖੱਬਾ_ਵਿੱਥ;
    uint16_t                            def_disp_win_ਸੱਜਾ_ਵਿੱਥ;
    uint16_t                            def_disp_win_ਸਿਖਰ_ਵਿੱਥ;
    uint16_t                            def_disp_win_bottom_ਵਿੱਥ;
    uint32_t                            vui_ਅੰਕ_units_ਵਿੱਚ_tick;
    uint32_t                            vui_ਸਮਾਂ_scale;
    uint32_t                            vui_ਅੰਕ_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pic_denom;
    uint8_t                             max_ਬਿੱਟ_ਪ੍ਰਤੀ_min_cu_denom;
    uint8_t                             log2_max_mv_ਲੰਮਾਈ_horizontal;
    uint8_t                             log2_max_mv_ਲੰਮਾਈ_vertical;
    ਅਚਲ StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_ਸੈੱਟ_Vui;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_ਮਾਪ][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_ਮਾਪ];
} StdVideoH265PredictorPaletteEntries;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_ਰੰਗ_plane_flag : 1;
    uint32_t    conformance_ਖਿੜਕੀ_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_ਅੰਕੜੇ_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_ਵਿੱਥ_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_ਪਦ_ref_pics_present_flag : 1;
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
    uint32_t    ਉੱਚਾ_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_ਬਹੁਲਕ_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ_Flags {
    uint32_t    inter_ref_pic_ਸੈੱਟ_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ {
    Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               ਵਰਤਿਆ_by_curr_pic_flag;
    uint16_t                               ਵਰਤਿਆ_by_curr_pic_s0_flag;
    uint16_t                               ਵਰਤਿਆ_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                ਅੰਕ_negative_pics;
    uint8_t                                ਅੰਕ_ਸਕਾਰਾਤਮਕ_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_ਮਾਪ];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_ਮਾਪ];
} Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Long_ਪਦ_Ref_Pics_Sps {
    uint32_t    ਵਰਤਿਆ_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_ਪਦ_REF_PICS_SPS];
} Std_Video_H265_Long_ਪਦ_Ref_Pics_Sps;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Sequence_Parameter_ਸੈੱਟ {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_ਚੌੜਾਈ_ਵਿੱਚ_luma_samples;
    uint32_t                                      pic_ਉਚਾਈ_ਵਿੱਚ_luma_samples;
    uint8_t                                       sps_video_parameter_ਸੈੱਟ_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_ਸੈੱਟ_id;
    uint8_t                                       ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma_minus8;
    uint8_t                                       ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma_minus8;
    uint8_t                                       log2_max_pic_ਕ੍ਰਮ_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_ਖੰਡ_ਮਾਪ_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_ਖੰਡ_ਮਾਪ;
    uint8_t                                       log2_min_luma_transform_ਖੰਡ_ਮਾਪ_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_ਖੰਡ_ਮਾਪ;
    uint8_t                                       max_transform_hierarchy_ਡੂੰਘਾਈ_inter;
    uint8_t                                       max_transform_hierarchy_ਡੂੰਘਾਈ_intra;
    uint8_t                                       ਅੰਕ_short_ਪਦ_ref_pic_sets;
    uint8_t                                       ਅੰਕ_long_ਪਦ_ref_pics_sps;
    uint8_t                                       pcm_sample_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma_minus1;
    uint8_t                                       pcm_sample_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_ਖੰਡ_ਮਾਪ_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_ਖੰਡ_ਮਾਪ;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_ਮਾਪ;
    uint8_t                                       delta_palette_max_predictor_ਮਾਪ;
    uint8_t                                       motion_ਸਦਿਸ਼_resolution_control_idc;
    uint8_t                                       sps_ਅੰਕ_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_ਖੱਬਾ_ਵਿੱਥ;
    uint32_t                                      conf_win_ਸੱਜਾ_ਵਿੱਥ;
    uint32_t                                      conf_win_ਸਿਖਰ_ਵਿੱਥ;
    uint32_t                                      conf_win_bottom_ਵਿੱਥ;
    ਅਚਲ StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    ਅਚਲ StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    ਅਚਲ StdVideoH265ScalingLists*               pScalingLists;
    ਅਚਲ Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ*         p_Short_ਪਦ_Ref_Pic_ਸੈੱਟ;
    ਅਚਲ Std_Video_H265_Long_ਪਦ_Ref_Pics_Sps*         p_Long_ਪਦ_Ref_Pics_Sps;
    ਅਚਲ Std_Video_H265_Sequence_Parameter_ਸੈੱਟ_Vui*    p_Sequence_Parameter_ਸੈੱਟ_Vui;
    ਅਚਲ StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_ਸੈੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH265PpsFlags {
    uint32_t    dependent_ਟੁਕੜਾ_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_ਅੰਕੜੇ_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_ਟੁਕੜਾ_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    ਇਕਸਾਰ_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_ਅੰਕੜੇ_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    ਟੁਕੜਾ_segment_ਸਿਰਲੇਖ_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_ਵਿੱਥ_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_ਰੰਗ_transform_enabled_flag : 1;
    uint32_t    pps_ਟੁਕੜਾ_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H265_Picture_Parameter_ਸੈੱਟ {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_ਸੈੱਟ_id;
    uint8_t                                       pps_seq_parameter_ਸੈੱਟ_id;
    uint8_t                                       sps_video_parameter_ਸੈੱਟ_id;
    uint8_t                                       ਅੰਕ_extra_ਟੁਕੜਾ_ਸਿਰਲੇਖ_ਬਿੱਟ;
    uint8_t                                       ਅੰਕ_ref_idx_l0_default_ਸਰਗਰਮ_minus1;
    uint8_t                                       ਅੰਕ_ref_idx_l1_default_ਸਰਗਰਮ_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_ਡੂੰਘਾਈ;
    int8_t                                        pps_cb_qp_ਵਿੱਥ;
    int8_t                                        pps_cr_qp_ਵਿੱਥ;
    int8_t                                        pps_beta_ਵਿੱਥ_div2;
    int8_t                                        pps_tc_ਵਿੱਥ_div2;
    uint8_t                                       log2_parallel_ਮਿਲਾਓ_level_minus2;
    uint8_t                                       log2_max_transform_skip_ਖੰਡ_ਮਾਪ_minus2;
    uint8_t                                       diff_cu_chroma_qp_ਵਿੱਥ_ਡੂੰਘਾਈ;
    uint8_t                                       chroma_qp_ਵਿੱਥ_list_len_minus1;
    int8_t                                        cb_qp_ਵਿੱਥ_list[STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_LIST_ਮਾਪ];
    int8_t                                        cr_qp_ਵਿੱਥ_list[STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_LIST_ਮਾਪ];
    uint8_t                                       log2_sao_ਵਿੱਥ_scale_luma;
    uint8_t                                       log2_sao_ਵਿੱਥ_scale_chroma;
    int8_t                                        pps_act_y_qp_ਵਿੱਥ_plus5;
    int8_t                                        pps_act_cb_qp_ਵਿੱਥ_plus5;
    int8_t                                        pps_act_cr_qp_ਵਿੱਥ_plus3;
    uint8_t                                       pps_ਅੰਕ_palette_predictor_initializers;
    uint8_t                                       luma_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_ਇੰਦਰਾਜ_minus8;
    uint8_t                                       chroma_ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_ਇੰਦਰਾਜ_minus8;
    uint8_t                                       ਅੰਕ_tile_columns_minus1;
    uint8_t                                       ਅੰਕ_tile_ਪੰਕਤੀਆਂ_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      ਕਾਲਮ_ਚੌੜਾਈ_minus1[STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_TILE_ਖਾਨੇ_ਗਿਣਤੀ_LIST_ਮਾਪ];
    uint16_t                                      ਪੰਕਤੀ_ਉਚਾਈ_minus1[STD_VIDEO_H265_CHROMA_QP_ਵਿੱਥ_TILE_ਪੰਕਤੀਆਂ_LIST_ਮਾਪ];
    uint32_t                                      reserved3;
    ਅਚਲ StdVideoH265ScalingLists*               pScalingLists;
    ਅਚਲ StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_ਸੈੱਟ;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
