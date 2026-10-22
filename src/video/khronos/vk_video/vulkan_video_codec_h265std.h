#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_H265STD_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H265STD_H_ 1

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



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h265std 1

#شامل "vulkan_video_codecs_common.h"

#تعریف_کرو STD_VIDEO_H265_CPB_CNT_LIST_سائز  32U
#تعریف_کرو STD_VIDEO_H265_SUBLAYERS_LIST_سائز 7U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_4_X4_عدد_LISTS 6U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_4_X4_عدد_ELEMENTS 16U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_8_X8_عدد_LISTS 6U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_8_X8_عدد_ELEMENTS 64U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_16_X16_عدد_LISTS 6U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_16_X16_عدد_ELEMENTS 64U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_32_X32_عدد_LISTS 2U
#تعریف_کرو STD_VIDEO_H265_SCALING_LIST_32_X32_عدد_ELEMENTS 64U
#تعریف_کرو STD_VIDEO_H265_CHROMA_QP_انحراف_LIST_سائز 6U
#تعریف_کرو STD_VIDEO_H265_CHROMA_QP_انحراف_TILE_ستون_تعداد_LIST_سائز 19U
#تعریف_کرو STD_VIDEO_H265_CHROMA_QP_انحراف_TILE_صفیں_LIST_سائز 21U
#تعریف_کرو STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_سائز 3U
#تعریف_کرو STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_سائز 128U
#تعریف_کرو STD_VIDEO_H265_MAX_عدد_LIST_REF   15U
#تعریف_کرو STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#تعریف_کرو STD_VIDEO_H265_MAX_SHORT_رکن_REF_PIC_SETS 64U
#تعریف_کرو STD_VIDEO_H265_MAX_DPB_سائز       16U
#تعریف_کرو STD_VIDEO_H265_MAX_LONG_رکن_REF_PICS_SPS 32U
#تعریف_کرو STD_VIDEO_H265_MAX_LONG_رکن_PICS 16U
#تعریف_کرو STD_VIDEO_H265_MAX_DELTA_POC      48U
#تعریف_کرو STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

قسمتعریف شمار StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

قسمتعریف شمار StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

قسمتعریف شمار StdVideoH265LevelIdc {
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

قسمتعریف شمار Std_Video_H265_قاش_Type {
    STD_VIDEO_H265_قاش_TYPE_B = 0,
    STD_VIDEO_H265_قاش_TYPE_P = 1,
    STD_VIDEO_H265_قاش_TYPE_I = 2,
    STD_VIDEO_H265_قاش_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_قاش_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_قاش_Type;

قسمتعریف شمار StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

قسمتعریف شمار Std_Video_H265_Aspect_تناسب_Idc {
    STD_VIDEO_H265_ASPECT_تناسب_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_مربع = 1,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_تناسب_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_تناسب_Idc;

قسمتعریف ساخت StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_سائز];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_سائز];
    uint8_t     max_عدد_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_سائز];
} StdVideoH265DecPicBufMgr;

قسمتعریف ساخت StdVideoH265SubLayerHrdParameters {
    uint32_t    ثنائی_ہندسہ_شرح_قدر_minus1[STD_VIDEO_H265_CPB_CNT_LIST_سائز];
    uint32_t    cpb_سائز_قدر_minus1[STD_VIDEO_H265_CPB_CNT_LIST_سائز];
    uint32_t    cpb_سائز_du_قدر_minus1[STD_VIDEO_H265_CPB_CNT_LIST_سائز];
    uint32_t    ثنائی_ہندسہ_شرح_du_قدر_minus1[STD_VIDEO_H265_CPB_CNT_LIST_سائز];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

قسمتعریف ساخت StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_اندر_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_شرح_general_flag : 8;
    uint32_t    fixed_pic_شرح_within_cvs_flag : 8;
    uint32_t    کم_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

قسمتعریف ساخت StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_مقسوم_علیہ_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_لمبائی_minus1;
    uint8_t                                     dpb_output_delay_du_لمبائی_minus1;
    uint8_t                                     ثنائی_ہندسہ_شرح_scale;
    uint8_t                                     cpb_سائز_scale;
    uint8_t                                     cpb_سائز_du_scale;
    uint8_t                                     initial_cpb_removal_delay_لمبائی_minus1;
    uint8_t                                     au_cpb_removal_delay_لمبائی_minus1;
    uint8_t                                     dpb_output_delay_لمبائی_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_سائز];
    uint16_t                                    elemental_duration_اندر_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_سائز];
    uint16_t                                    reserved[3];
    ثابت StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    ثابت StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

قسمتعریف ساخت StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_مقصد_timing_flag : 1;
} StdVideoH265VpsFlags;

قسمتعریف ساخت StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_ماخذ_flag : 1;
    uint32_t    general_interlaced_ماخذ_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_چوکھٹا_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

قسمتعریف ساخت StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

قسمتعریف ساخت Std_Video_H265_Video_Parameter_سیٹ {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_سیٹ_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_عدد_units_اندر_tick;
    uint32_t                               vps_وقت_scale;
    uint32_t                               vps_عدد_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    ثابت StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    ثابت StdVideoH265HrdParameters*       pHrdParameters;
    ثابت StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_سیٹ;

قسمتعریف ساخت StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_عدد_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_عدد_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_عدد_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_عدد_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_عدد_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_عدد_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_عدد_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_عدد_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_عدد_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_عدد_LISTS];
} StdVideoH265ScalingLists;

قسمتعریف ساخت StdVideoH265SpsVuiFlags {
    uint32_t    aspect_تناسب_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_بھرا_range_flag : 1;
    uint32_t    رنگ_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    میدان_seq_flag : 1;
    uint32_t    چوکھٹا_میدان_info_present_flag : 1;
    uint32_t    default_display_کھڑکی_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_مقصد_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

قسمتعریف ساخت Std_Video_H265_Sequence_Parameter_سیٹ_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_تناسب_Idc          aspect_تناسب_idc;
    uint16_t                            sar_چوڑائی;
    uint16_t                            sar_اونچائی;
    uint8_t                             video_format;
    uint8_t                             رنگ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             میٹرکس_coeffs;
    uint8_t                             chroma_sample_loc_type_چوٹی_میدان;
    uint8_t                             chroma_sample_loc_type_bottom_میدان;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_بایاں_انحراف;
    uint16_t                            def_disp_win_دایاں_انحراف;
    uint16_t                            def_disp_win_چوٹی_انحراف;
    uint16_t                            def_disp_win_bottom_انحراف;
    uint32_t                            vui_عدد_units_اندر_tick;
    uint32_t                            vui_وقت_scale;
    uint32_t                            vui_عدد_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_بائٹیں_فی_pic_denom;
    uint8_t                             max_بٹ_فی_min_cu_denom;
    uint8_t                             log2_max_mv_لمبائی_horizontal;
    uint8_t                             log2_max_mv_لمبائی_vertical;
    ثابت StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_سیٹ_Vui;

قسمتعریف ساخت StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_سائز][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_سائز];
} StdVideoH265PredictorPaletteEntries;

قسمتعریف ساخت StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_رنگ_plane_flag : 1;
    uint32_t    conformance_کھڑکی_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_ڈیٹا_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_انحراف_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_رکن_ref_pics_present_flag : 1;
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
    uint32_t    بلند_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_منوال_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

قسمتعریف ساخت Std_Video_H265_Short_رکن_Ref_Pic_سیٹ_Flags {
    uint32_t    inter_ref_pic_سیٹ_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_رکن_Ref_Pic_سیٹ_Flags;

قسمتعریف ساخت Std_Video_H265_Short_رکن_Ref_Pic_سیٹ {
    Std_Video_H265_Short_رکن_Ref_Pic_سیٹ_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               مستعمل_by_curr_pic_flag;
    uint16_t                               مستعمل_by_curr_pic_s0_flag;
    uint16_t                               مستعمل_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                عدد_negative_pics;
    uint8_t                                عدد_مثبت_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_سائز];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_سائز];
} Std_Video_H265_Short_رکن_Ref_Pic_سیٹ;

قسمتعریف ساخت Std_Video_H265_Long_رکن_Ref_Pics_Sps {
    uint32_t    مستعمل_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_رکن_REF_PICS_SPS];
} Std_Video_H265_Long_رکن_Ref_Pics_Sps;

قسمتعریف ساخت Std_Video_H265_Sequence_Parameter_سیٹ {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_چوڑائی_اندر_luma_samples;
    uint32_t                                      pic_اونچائی_اندر_luma_samples;
    uint8_t                                       sps_video_parameter_سیٹ_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_سیٹ_id;
    uint8_t                                       ثنائی_ہندسہ_گہرائی_luma_minus8;
    uint8_t                                       ثنائی_ہندسہ_گہرائی_chroma_minus8;
    uint8_t                                       log2_max_pic_ترتیب_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_بلاک_سائز_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_بلاک_سائز;
    uint8_t                                       log2_min_luma_transform_بلاک_سائز_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_بلاک_سائز;
    uint8_t                                       max_transform_hierarchy_گہرائی_inter;
    uint8_t                                       max_transform_hierarchy_گہرائی_intra;
    uint8_t                                       عدد_short_رکن_ref_pic_sets;
    uint8_t                                       عدد_long_رکن_ref_pics_sps;
    uint8_t                                       pcm_sample_ثنائی_ہندسہ_گہرائی_luma_minus1;
    uint8_t                                       pcm_sample_ثنائی_ہندسہ_گہرائی_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_بلاک_سائز_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_بلاک_سائز;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_سائز;
    uint8_t                                       delta_palette_max_predictor_سائز;
    uint8_t                                       motion_سمتیہ_resolution_control_idc;
    uint8_t                                       sps_عدد_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_بایاں_انحراف;
    uint32_t                                      conf_win_دایاں_انحراف;
    uint32_t                                      conf_win_چوٹی_انحراف;
    uint32_t                                      conf_win_bottom_انحراف;
    ثابت StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    ثابت StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    ثابت StdVideoH265ScalingLists*               pScalingLists;
    ثابت Std_Video_H265_Short_رکن_Ref_Pic_سیٹ*         p_Short_رکن_Ref_Pic_سیٹ;
    ثابت Std_Video_H265_Long_رکن_Ref_Pics_Sps*         p_Long_رکن_Ref_Pics_Sps;
    ثابت Std_Video_H265_Sequence_Parameter_سیٹ_Vui*    p_Sequence_Parameter_سیٹ_Vui;
    ثابت StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_سیٹ;

قسمتعریف ساخت StdVideoH265PpsFlags {
    uint32_t    dependent_قاش_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_ڈیٹا_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_قاش_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    یکساں_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_ڈیٹا_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    قاش_segment_سرخی_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_انحراف_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_رنگ_transform_enabled_flag : 1;
    uint32_t    pps_قاش_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

قسمتعریف ساخت Std_Video_H265_Picture_Parameter_سیٹ {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_سیٹ_id;
    uint8_t                                       pps_seq_parameter_سیٹ_id;
    uint8_t                                       sps_video_parameter_سیٹ_id;
    uint8_t                                       عدد_extra_قاش_سرخی_بٹ;
    uint8_t                                       عدد_ref_idx_l0_default_فعال_minus1;
    uint8_t                                       عدد_ref_idx_l1_default_فعال_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_گہرائی;
    int8_t                                        pps_cb_qp_انحراف;
    int8_t                                        pps_cr_qp_انحراف;
    int8_t                                        pps_beta_انحراف_div2;
    int8_t                                        pps_tc_انحراف_div2;
    uint8_t                                       log2_parallel_ملاؤ_level_minus2;
    uint8_t                                       log2_max_transform_skip_بلاک_سائز_minus2;
    uint8_t                                       diff_cu_chroma_qp_انحراف_گہرائی;
    uint8_t                                       chroma_qp_انحراف_list_len_minus1;
    int8_t                                        cb_qp_انحراف_list[STD_VIDEO_H265_CHROMA_QP_انحراف_LIST_سائز];
    int8_t                                        cr_qp_انحراف_list[STD_VIDEO_H265_CHROMA_QP_انحراف_LIST_سائز];
    uint8_t                                       log2_sao_انحراف_scale_luma;
    uint8_t                                       log2_sao_انحراف_scale_chroma;
    int8_t                                        pps_act_y_qp_انحراف_plus5;
    int8_t                                        pps_act_cb_qp_انحراف_plus5;
    int8_t                                        pps_act_cr_qp_انحراف_plus3;
    uint8_t                                       pps_عدد_palette_predictor_initializers;
    uint8_t                                       luma_ثنائی_ہندسہ_گہرائی_اندراج_minus8;
    uint8_t                                       chroma_ثنائی_ہندسہ_گہرائی_اندراج_minus8;
    uint8_t                                       عدد_tile_columns_minus1;
    uint8_t                                       عدد_tile_صفیں_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      عمود_چوڑائی_minus1[STD_VIDEO_H265_CHROMA_QP_انحراف_TILE_ستون_تعداد_LIST_سائز];
    uint16_t                                      صف_اونچائی_minus1[STD_VIDEO_H265_CHROMA_QP_انحراف_TILE_صفیں_LIST_سائز];
    uint32_t                                      reserved3;
    ثابت StdVideoH265ScalingLists*               pScalingLists;
    ثابت StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_سیٹ;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
