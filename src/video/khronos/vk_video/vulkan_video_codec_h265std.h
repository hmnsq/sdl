#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H265STD_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H265STD_H_ 1

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



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h265std 1

#అన్తర్భావ "vulkan_video_codecs_common.h"

#నిర్వచించు STD_VIDEO_H265_CPB_CNT_LIST_కొలత  32U
#నిర్వచించు STD_VIDEO_H265_SUBLAYERS_LIST_కొలత 7U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_4_X4_అంకె_LISTS 6U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_4_X4_అంకె_ELEMENTS 16U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_8_X8_అంకె_LISTS 6U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_8_X8_అంకె_ELEMENTS 64U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_16_X16_అంకె_LISTS 6U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_16_X16_అంకె_ELEMENTS 64U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_32_X32_అంకె_LISTS 2U
#నిర్వచించు STD_VIDEO_H265_SCALING_LIST_32_X32_అంకె_ELEMENTS 64U
#నిర్వచించు STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_LIST_కొలత 6U
#నిర్వచించు STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_TILE_నిలువుల_సంఖ్య_LIST_కొలత 19U
#నిర్వచించు STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_TILE_అడ్డువరుసలు_LIST_కొలత 21U
#నిర్వచించు STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_కొలత 3U
#నిర్వచించు STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_కొలత 128U
#నిర్వచించు STD_VIDEO_H265_MAX_అంకె_LIST_REF   15U
#నిర్వచించు STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#నిర్వచించు STD_VIDEO_H265_MAX_SHORT_పదం_REF_PIC_SETS 64U
#నిర్వచించు STD_VIDEO_H265_MAX_DPB_కొలత       16U
#నిర్వచించు STD_VIDEO_H265_MAX_LONG_పదం_REF_PICS_SPS 32U
#నిర్వచించు STD_VIDEO_H265_MAX_LONG_పదం_PICS 16U
#నిర్వచించు STD_VIDEO_H265_MAX_DELTA_POC      48U
#నిర్వచించు STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

రకనిర్వచనం గణన StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

రకనిర్వచనం గణన StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

రకనిర్వచనం గణన StdVideoH265LevelIdc {
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

రకనిర్వచనం గణన Std_Video_H265_ముక్క_Type {
    STD_VIDEO_H265_ముక్క_TYPE_B = 0,
    STD_VIDEO_H265_ముక్క_TYPE_P = 1,
    STD_VIDEO_H265_ముక్క_TYPE_I = 2,
    STD_VIDEO_H265_ముక్క_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ముక్క_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_ముక్క_Type;

రకనిర్వచనం గణన StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

రకనిర్వచనం గణన Std_Video_H265_Aspect_నిష్పత్తి_Idc {
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_వర్గం = 1,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_నిష్పత్తి_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_నిష్పత్తి_Idc;

రకనిర్వచనం నిర్మాణం StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_కొలత];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_కొలత];
    uint8_t     max_అంకె_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_కొలత];
} StdVideoH265DecPicBufMgr;

రకనిర్వచనం నిర్మాణం StdVideoH265SubLayerHrdParameters {
    uint32_t    బిట్టు_రేటు_విలువ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_కొలత];
    uint32_t    cpb_కొలత_విలువ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_కొలత];
    uint32_t    cpb_కొలత_du_విలువ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_కొలత];
    uint32_t    బిట్టు_రేటు_du_విలువ_minus1[STD_VIDEO_H265_CPB_CNT_LIST_కొలత];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

రకనిర్వచనం నిర్మాణం StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_లోపల_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_రేటు_general_flag : 8;
    uint32_t    fixed_pic_రేటు_within_cvs_flag : 8;
    uint32_t    దిగువ_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

రకనిర్వచనం నిర్మాణం StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_భాజకం_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_నిడివి_minus1;
    uint8_t                                     dpb_output_delay_du_నిడివి_minus1;
    uint8_t                                     బిట్టు_రేటు_scale;
    uint8_t                                     cpb_కొలత_scale;
    uint8_t                                     cpb_కొలత_du_scale;
    uint8_t                                     initial_cpb_removal_delay_నిడివి_minus1;
    uint8_t                                     au_cpb_removal_delay_నిడివి_minus1;
    uint8_t                                     dpb_output_delay_నిడివి_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_కొలత];
    uint16_t                                    elemental_duration_లోపల_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_కొలత];
    uint16_t                                    reserved[3];
    స్థిరరాశి StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    స్థిరరాశి StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

రకనిర్వచనం నిర్మాణం StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_గమ్యం_timing_flag : 1;
} StdVideoH265VpsFlags;

రకనిర్వచనం నిర్మాణం StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_ఆధారం_flag : 1;
    uint32_t    general_interlaced_ఆధారం_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_చట్రం_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

రకనిర్వచనం నిర్మాణం StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Video_Parameter_సమితి {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_సమితి_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_అంకె_units_లోపల_tick;
    uint32_t                               vps_సమయం_scale;
    uint32_t                               vps_అంకె_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    స్థిరరాశి StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    స్థిరరాశి StdVideoH265HrdParameters*       pHrdParameters;
    స్థిరరాశి StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_సమితి;

రకనిర్వచనం నిర్మాణం StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_అంకె_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_అంకె_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_అంకె_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_అంకె_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_అంకె_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_అంకె_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_అంకె_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_అంకె_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_అంకె_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_అంకె_LISTS];
} StdVideoH265ScalingLists;

రకనిర్వచనం నిర్మాణం StdVideoH265SpsVuiFlags {
    uint32_t    aspect_నిష్పత్తి_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_నిండిన_range_flag : 1;
    uint32_t    రంగు_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    క్షేత్రం_seq_flag : 1;
    uint32_t    చట్రం_క్షేత్రం_info_present_flag : 1;
    uint32_t    default_display_కిటికీ_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_గమ్యం_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Sequence_Parameter_సమితి_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_నిష్పత్తి_Idc          aspect_నిష్పత్తి_idc;
    uint16_t                            sar_వెడల్పు;
    uint16_t                            sar_ఎత్తు;
    uint8_t                             video_format;
    uint8_t                             రంగు_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             మాతృక_coeffs;
    uint8_t                             chroma_sample_loc_type_శిఖరం_క్షేత్రం;
    uint8_t                             chroma_sample_loc_type_bottom_క్షేత్రం;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_ఎడమ_స్థానభ్రంశం;
    uint16_t                            def_disp_win_కుడి_స్థానభ్రంశం;
    uint16_t                            def_disp_win_శిఖరం_స్థానభ్రంశం;
    uint16_t                            def_disp_win_bottom_స్థానభ్రంశం;
    uint32_t                            vui_అంకె_units_లోపల_tick;
    uint32_t                            vui_సమయం_scale;
    uint32_t                            vui_అంకె_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_బైట్లు_చొప్పున_pic_denom;
    uint8_t                             max_బిట్లు_చొప్పున_min_cu_denom;
    uint8_t                             log2_max_mv_నిడివి_horizontal;
    uint8_t                             log2_max_mv_నిడివి_vertical;
    స్థిరరాశి StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_సమితి_Vui;

రకనిర్వచనం నిర్మాణం StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_కొలత][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_కొలత];
} StdVideoH265PredictorPaletteEntries;

రకనిర్వచనం నిర్మాణం StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_రంగు_plane_flag : 1;
    uint32_t    conformance_కిటికీ_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_దత్తాంశం_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_స్థానభ్రంశం_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_పదం_ref_pics_present_flag : 1;
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
    uint32_t    ఎగువ_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_బహుళకం_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Short_పదం_Ref_Pic_సమితి_Flags {
    uint32_t    inter_ref_pic_సమితి_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_పదం_Ref_Pic_సమితి_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Short_పదం_Ref_Pic_సమితి {
    Std_Video_H265_Short_పదం_Ref_Pic_సమితి_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               వాడిన_by_curr_pic_flag;
    uint16_t                               వాడిన_by_curr_pic_s0_flag;
    uint16_t                               వాడిన_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                అంకె_negative_pics;
    uint8_t                                అంకె_ధనాత్మక_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_కొలత];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_కొలత];
} Std_Video_H265_Short_పదం_Ref_Pic_సమితి;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Long_పదం_Ref_Pics_Sps {
    uint32_t    వాడిన_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_పదం_REF_PICS_SPS];
} Std_Video_H265_Long_పదం_Ref_Pics_Sps;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Sequence_Parameter_సమితి {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_వెడల్పు_లోపల_luma_samples;
    uint32_t                                      pic_ఎత్తు_లోపల_luma_samples;
    uint8_t                                       sps_video_parameter_సమితి_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_సమితి_id;
    uint8_t                                       బిట్టు_లోతు_luma_minus8;
    uint8_t                                       బిట్టు_లోతు_chroma_minus8;
    uint8_t                                       log2_max_pic_క్రమం_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_ఖండం_కొలత_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_ఖండం_కొలత;
    uint8_t                                       log2_min_luma_transform_ఖండం_కొలత_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_ఖండం_కొలత;
    uint8_t                                       max_transform_hierarchy_లోతు_inter;
    uint8_t                                       max_transform_hierarchy_లోతు_intra;
    uint8_t                                       అంకె_short_పదం_ref_pic_sets;
    uint8_t                                       అంకె_long_పదం_ref_pics_sps;
    uint8_t                                       pcm_sample_బిట్టు_లోతు_luma_minus1;
    uint8_t                                       pcm_sample_బిట్టు_లోతు_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_ఖండం_కొలత_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_ఖండం_కొలత;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_కొలత;
    uint8_t                                       delta_palette_max_predictor_కొలత;
    uint8_t                                       motion_సదిశ_resolution_control_idc;
    uint8_t                                       sps_అంకె_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_ఎడమ_స్థానభ్రంశం;
    uint32_t                                      conf_win_కుడి_స్థానభ్రంశం;
    uint32_t                                      conf_win_శిఖరం_స్థానభ్రంశం;
    uint32_t                                      conf_win_bottom_స్థానభ్రంశం;
    స్థిరరాశి StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    స్థిరరాశి StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    స్థిరరాశి StdVideoH265ScalingLists*               pScalingLists;
    స్థిరరాశి Std_Video_H265_Short_పదం_Ref_Pic_సమితి*         p_Short_పదం_Ref_Pic_సమితి;
    స్థిరరాశి Std_Video_H265_Long_పదం_Ref_Pics_Sps*         p_Long_పదం_Ref_Pics_Sps;
    స్థిరరాశి Std_Video_H265_Sequence_Parameter_సమితి_Vui*    p_Sequence_Parameter_సమితి_Vui;
    స్థిరరాశి StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_సమితి;

రకనిర్వచనం నిర్మాణం StdVideoH265PpsFlags {
    uint32_t    dependent_ముక్క_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_దత్తాంశం_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_ముక్క_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    ఏకరీతి_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_దత్తాంశం_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    ముక్క_segment_శీర్షిక_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_స్థానభ్రంశం_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_రంగు_transform_enabled_flag : 1;
    uint32_t    pps_ముక్క_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

రకనిర్వచనం నిర్మాణం Std_Video_H265_Picture_Parameter_సమితి {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_సమితి_id;
    uint8_t                                       pps_seq_parameter_సమితి_id;
    uint8_t                                       sps_video_parameter_సమితి_id;
    uint8_t                                       అంకె_extra_ముక్క_శీర్షిక_బిట్లు;
    uint8_t                                       అంకె_ref_idx_l0_default_చురుకైన_minus1;
    uint8_t                                       అంకె_ref_idx_l1_default_చురుకైన_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_లోతు;
    int8_t                                        pps_cb_qp_స్థానభ్రంశం;
    int8_t                                        pps_cr_qp_స్థానభ్రంశం;
    int8_t                                        pps_beta_స్థానభ్రంశం_div2;
    int8_t                                        pps_tc_స్థానభ్రంశం_div2;
    uint8_t                                       log2_parallel_విలీనం_level_minus2;
    uint8_t                                       log2_max_transform_skip_ఖండం_కొలత_minus2;
    uint8_t                                       diff_cu_chroma_qp_స్థానభ్రంశం_లోతు;
    uint8_t                                       chroma_qp_స్థానభ్రంశం_list_len_minus1;
    int8_t                                        cb_qp_స్థానభ్రంశం_list[STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_LIST_కొలత];
    int8_t                                        cr_qp_స్థానభ్రంశం_list[STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_LIST_కొలత];
    uint8_t                                       log2_sao_స్థానభ్రంశం_scale_luma;
    uint8_t                                       log2_sao_స్థానభ్రంశం_scale_chroma;
    int8_t                                        pps_act_y_qp_స్థానభ్రంశం_plus5;
    int8_t                                        pps_act_cb_qp_స్థానభ్రంశం_plus5;
    int8_t                                        pps_act_cr_qp_స్థానభ్రంశం_plus3;
    uint8_t                                       pps_అంకె_palette_predictor_initializers;
    uint8_t                                       luma_బిట్టు_లోతు_నమోదు_minus8;
    uint8_t                                       chroma_బిట్టు_లోతు_నమోదు_minus8;
    uint8_t                                       అంకె_tile_columns_minus1;
    uint8_t                                       అంకె_tile_అడ్డువరుసలు_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      స్తంభం_వెడల్పు_minus1[STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_TILE_నిలువుల_సంఖ్య_LIST_కొలత];
    uint16_t                                      అడ్డువరుస_ఎత్తు_minus1[STD_VIDEO_H265_CHROMA_QP_స్థానభ్రంశం_TILE_అడ్డువరుసలు_LIST_కొలత];
    uint32_t                                      reserved3;
    స్థిరరాశి StdVideoH265ScalingLists*               pScalingLists;
    స్థిరరాశి StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_సమితి;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
