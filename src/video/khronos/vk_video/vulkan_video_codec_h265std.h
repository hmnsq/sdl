#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_H265STD_H_
#تعریف_کن VULKAN_VIDEO_CODEC_H265STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_h265std 1

#ضمن "vulkan_video_codecs_common.h"

#تعریف_کن STD_VIDEO_H265_CPB_CNT_LIST_اندازه  32U
#تعریف_کن STD_VIDEO_H265_SUBLAYERS_LIST_اندازه 7U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_4_X4_رقم_LISTS 6U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_4_X4_رقم_ELEMENTS 16U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_8_X8_رقم_LISTS 6U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_8_X8_رقم_ELEMENTS 64U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_16_X16_رقم_LISTS 6U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_16_X16_رقم_ELEMENTS 64U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_32_X32_رقم_LISTS 2U
#تعریف_کن STD_VIDEO_H265_SCALING_LIST_32_X32_رقم_ELEMENTS 64U
#تعریف_کن STD_VIDEO_H265_CHROMA_QP_جابه_جایی_LIST_اندازه 6U
#تعریف_کن STD_VIDEO_H265_CHROMA_QP_جابه_جایی_TILE_تعداد_ستون_LIST_اندازه 19U
#تعریف_کن STD_VIDEO_H265_CHROMA_QP_جابه_جایی_TILE_ردیفها_LIST_اندازه 21U
#تعریف_کن STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_اندازه 3U
#تعریف_کن STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_اندازه 128U
#تعریف_کن STD_VIDEO_H265_MAX_رقم_LIST_REF   15U
#تعریف_کن STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#تعریف_کن STD_VIDEO_H265_MAX_SHORT_جمله_REF_PIC_SETS 64U
#تعریف_کن STD_VIDEO_H265_MAX_DPB_اندازه       16U
#تعریف_کن STD_VIDEO_H265_MAX_LONG_جمله_REF_PICS_SPS 32U
#تعریف_کن STD_VIDEO_H265_MAX_LONG_جمله_PICS 16U
#تعریف_کن STD_VIDEO_H265_MAX_DELTA_POC      48U
#تعریف_کن STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

تعريفنوع تعداد StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

تعريفنوع تعداد StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

تعريفنوع تعداد StdVideoH265LevelIdc {
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

تعريفنوع تعداد Std_Video_H265_برش_Type {
    STD_VIDEO_H265_برش_TYPE_B = 0,
    STD_VIDEO_H265_برش_TYPE_P = 1,
    STD_VIDEO_H265_برش_TYPE_I = 2,
    STD_VIDEO_H265_برش_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_برش_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_برش_Type;

تعريفنوع تعداد StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

تعريفنوع تعداد Std_Video_H265_Aspect_نسبت_Idc {
    STD_VIDEO_H265_ASPECT_نسبت_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_مربع = 1,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_نسبت_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_نسبت_Idc;

تعريفنوع بنية StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_اندازه];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_اندازه];
    uint8_t     max_رقم_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_اندازه];
} StdVideoH265DecPicBufMgr;

تعريفنوع بنية StdVideoH265SubLayerHrdParameters {
    uint32_t    بیت_نرخ_مقدار_minus1[STD_VIDEO_H265_CPB_CNT_LIST_اندازه];
    uint32_t    cpb_اندازه_مقدار_minus1[STD_VIDEO_H265_CPB_CNT_LIST_اندازه];
    uint32_t    cpb_اندازه_du_مقدار_minus1[STD_VIDEO_H265_CPB_CNT_LIST_اندازه];
    uint32_t    بیت_نرخ_du_مقدار_minus1[STD_VIDEO_H265_CPB_CNT_LIST_اندازه];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

تعريفنوع بنية StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_درون_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_نرخ_general_flag : 8;
    uint32_t    fixed_pic_نرخ_within_cvs_flag : 8;
    uint32_t    کم_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

تعريفنوع بنية StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_مقسوم_علیه_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_درازی_minus1;
    uint8_t                                     dpb_output_delay_du_درازی_minus1;
    uint8_t                                     بیت_نرخ_scale;
    uint8_t                                     cpb_اندازه_scale;
    uint8_t                                     cpb_اندازه_du_scale;
    uint8_t                                     initial_cpb_removal_delay_درازی_minus1;
    uint8_t                                     au_cpb_removal_delay_درازی_minus1;
    uint8_t                                     dpb_output_delay_درازی_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_اندازه];
    uint16_t                                    elemental_duration_درون_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_اندازه];
    uint16_t                                    reserved[3];
    ثابت StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    ثابت StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

تعريفنوع بنية StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_مقصد_timing_flag : 1;
} StdVideoH265VpsFlags;

تعريفنوع بنية StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_منبع_flag : 1;
    uint32_t    general_interlaced_منبع_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_قاب_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

تعريفنوع بنية StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

تعريفنوع بنية Std_Video_H265_Video_Parameter_مجموعه {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_مجموعه_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_رقم_units_درون_tick;
    uint32_t                               vps_زمان_scale;
    uint32_t                               vps_رقم_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    ثابت StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    ثابت StdVideoH265HrdParameters*       pHrdParameters;
    ثابت StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_مجموعه;

تعريفنوع بنية StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_رقم_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_رقم_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_رقم_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_رقم_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_رقم_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_رقم_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_رقم_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_رقم_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_رقم_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_رقم_LISTS];
} StdVideoH265ScalingLists;

تعريفنوع بنية StdVideoH265SpsVuiFlags {
    uint32_t    aspect_نسبت_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_پر_range_flag : 1;
    uint32_t    رنگ_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    فیلد_seq_flag : 1;
    uint32_t    قاب_فیلد_info_present_flag : 1;
    uint32_t    default_display_پنجره_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_مقصد_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

تعريفنوع بنية Std_Video_H265_Sequence_Parameter_مجموعه_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_نسبت_Idc          aspect_نسبت_idc;
    uint16_t                            sar_عرض;
    uint16_t                            sar_ارتفاع;
    uint8_t                             video_format;
    uint8_t                             رنگ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ماتریس_coeffs;
    uint8_t                             chroma_sample_loc_type_بالاترین_فیلد;
    uint8_t                             chroma_sample_loc_type_bottom_فیلد;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_چپ_جابه_جایی;
    uint16_t                            def_disp_win_راست_جابه_جایی;
    uint16_t                            def_disp_win_بالاترین_جابه_جایی;
    uint16_t                            def_disp_win_bottom_جابه_جایی;
    uint32_t                            vui_رقم_units_درون_tick;
    uint32_t                            vui_زمان_scale;
    uint32_t                            vui_رقم_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_بایتها_در_هر_pic_denom;
    uint8_t                             max_بیتها_در_هر_min_cu_denom;
    uint8_t                             log2_max_mv_درازی_horizontal;
    uint8_t                             log2_max_mv_درازی_vertical;
    ثابت StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_مجموعه_Vui;

تعريفنوع بنية StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_اندازه][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_اندازه];
} StdVideoH265PredictorPaletteEntries;

تعريفنوع بنية StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_رنگ_plane_flag : 1;
    uint32_t    conformance_پنجره_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_داده_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_جابه_جایی_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_جمله_ref_pics_present_flag : 1;
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
    uint32_t    بالا_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_نما_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

تعريفنوع بنية Std_Video_H265_Short_جمله_Ref_Pic_مجموعه_Flags {
    uint32_t    inter_ref_pic_مجموعه_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_جمله_Ref_Pic_مجموعه_Flags;

تعريفنوع بنية Std_Video_H265_Short_جمله_Ref_Pic_مجموعه {
    Std_Video_H265_Short_جمله_Ref_Pic_مجموعه_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               استفاده_شده_by_curr_pic_flag;
    uint16_t                               استفاده_شده_by_curr_pic_s0_flag;
    uint16_t                               استفاده_شده_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                رقم_negative_pics;
    uint8_t                                رقم_مثبت_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_اندازه];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_اندازه];
} Std_Video_H265_Short_جمله_Ref_Pic_مجموعه;

تعريفنوع بنية Std_Video_H265_Long_جمله_Ref_Pics_Sps {
    uint32_t    استفاده_شده_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_جمله_REF_PICS_SPS];
} Std_Video_H265_Long_جمله_Ref_Pics_Sps;

تعريفنوع بنية Std_Video_H265_Sequence_Parameter_مجموعه {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_عرض_درون_luma_samples;
    uint32_t                                      pic_ارتفاع_درون_luma_samples;
    uint8_t                                       sps_video_parameter_مجموعه_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_مجموعه_id;
    uint8_t                                       بیت_عمق_luma_minus8;
    uint8_t                                       بیت_عمق_chroma_minus8;
    uint8_t                                       log2_max_pic_ترتیب_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_بلوک_اندازه_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_بلوک_اندازه;
    uint8_t                                       log2_min_luma_transform_بلوک_اندازه_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_بلوک_اندازه;
    uint8_t                                       max_transform_hierarchy_عمق_inter;
    uint8_t                                       max_transform_hierarchy_عمق_intra;
    uint8_t                                       رقم_short_جمله_ref_pic_sets;
    uint8_t                                       رقم_long_جمله_ref_pics_sps;
    uint8_t                                       pcm_sample_بیت_عمق_luma_minus1;
    uint8_t                                       pcm_sample_بیت_عمق_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_بلوک_اندازه_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_بلوک_اندازه;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_اندازه;
    uint8_t                                       delta_palette_max_predictor_اندازه;
    uint8_t                                       motion_وکتور_resolution_control_idc;
    uint8_t                                       sps_رقم_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_چپ_جابه_جایی;
    uint32_t                                      conf_win_راست_جابه_جایی;
    uint32_t                                      conf_win_بالاترین_جابه_جایی;
    uint32_t                                      conf_win_bottom_جابه_جایی;
    ثابت StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    ثابت StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    ثابت StdVideoH265ScalingLists*               pScalingLists;
    ثابت Std_Video_H265_Short_جمله_Ref_Pic_مجموعه*         p_Short_جمله_Ref_Pic_مجموعه;
    ثابت Std_Video_H265_Long_جمله_Ref_Pics_Sps*         p_Long_جمله_Ref_Pics_Sps;
    ثابت Std_Video_H265_Sequence_Parameter_مجموعه_Vui*    p_Sequence_Parameter_مجموعه_Vui;
    ثابت StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_مجموعه;

تعريفنوع بنية StdVideoH265PpsFlags {
    uint32_t    dependent_برش_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_داده_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_برش_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    یکنواخت_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_داده_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    برش_segment_سرآیند_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_جابه_جایی_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_رنگ_transform_enabled_flag : 1;
    uint32_t    pps_برش_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

تعريفنوع بنية Std_Video_H265_Picture_Parameter_مجموعه {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_مجموعه_id;
    uint8_t                                       pps_seq_parameter_مجموعه_id;
    uint8_t                                       sps_video_parameter_مجموعه_id;
    uint8_t                                       رقم_extra_برش_سرآیند_بیتها;
    uint8_t                                       رقم_ref_idx_l0_default_فعال_minus1;
    uint8_t                                       رقم_ref_idx_l1_default_فعال_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_عمق;
    int8_t                                        pps_cb_qp_جابه_جایی;
    int8_t                                        pps_cr_qp_جابه_جایی;
    int8_t                                        pps_beta_جابه_جایی_div2;
    int8_t                                        pps_tc_جابه_جایی_div2;
    uint8_t                                       log2_parallel_ادغام_level_minus2;
    uint8_t                                       log2_max_transform_skip_بلوک_اندازه_minus2;
    uint8_t                                       diff_cu_chroma_qp_جابه_جایی_عمق;
    uint8_t                                       chroma_qp_جابه_جایی_list_len_minus1;
    int8_t                                        cb_qp_جابه_جایی_list[STD_VIDEO_H265_CHROMA_QP_جابه_جایی_LIST_اندازه];
    int8_t                                        cr_qp_جابه_جایی_list[STD_VIDEO_H265_CHROMA_QP_جابه_جایی_LIST_اندازه];
    uint8_t                                       log2_sao_جابه_جایی_scale_luma;
    uint8_t                                       log2_sao_جابه_جایی_scale_chroma;
    int8_t                                        pps_act_y_qp_جابه_جایی_plus5;
    int8_t                                        pps_act_cb_qp_جابه_جایی_plus5;
    int8_t                                        pps_act_cr_qp_جابه_جایی_plus3;
    uint8_t                                       pps_رقم_palette_predictor_initializers;
    uint8_t                                       luma_بیت_عمق_مدخل_minus8;
    uint8_t                                       chroma_بیت_عمق_مدخل_minus8;
    uint8_t                                       رقم_tile_columns_minus1;
    uint8_t                                       رقم_tile_ردیفها_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      ستونی_عرض_minus1[STD_VIDEO_H265_CHROMA_QP_جابه_جایی_TILE_تعداد_ستون_LIST_اندازه];
    uint16_t                                      ردیف_ارتفاع_minus1[STD_VIDEO_H265_CHROMA_QP_جابه_جایی_TILE_ردیفها_LIST_اندازه];
    uint32_t                                      reserved3;
    ثابت StdVideoH265ScalingLists*               pScalingLists;
    ثابت StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_مجموعه;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
