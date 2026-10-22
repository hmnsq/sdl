#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H265STD_H_
#परिभाषय VULKAN_VIDEO_CODEC_H265STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// vulkan_video_codec_h265std is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h265std 1

#अन्तर्भाव "vulkan_video_codecs_common.h"

#परिभाषय STD_VIDEO_H265_CPB_CNT_LIST_आकार  32U
#परिभाषय STD_VIDEO_H265_SUBLAYERS_LIST_आकार 7U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_4_X4_अङ्कः_LISTS 6U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_4_X4_अङ्कः_ELEMENTS 16U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_8_X8_अङ्कः_LISTS 6U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_8_X8_अङ्कः_ELEMENTS 64U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_16_X16_अङ्कः_LISTS 6U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_16_X16_अङ्कः_ELEMENTS 64U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_32_X32_अङ्कः_LISTS 2U
#परिभाषय STD_VIDEO_H265_SCALING_LIST_32_X32_अङ्कः_ELEMENTS 64U
#परिभाषय STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_LIST_आकार 6U
#परिभाषय STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_TILE_स्तम्भसङ्ख्या_LIST_आकार 19U
#परिभाषय STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_TILE_पङ्क्तिकाः_LIST_आकार 21U
#परिभाषय STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_आकार 3U
#परिभाषय STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_आकार 128U
#परिभाषय STD_VIDEO_H265_MAX_अङ्कः_LIST_REF   15U
#परिभाषय STD_VIDEO_H265_MAX_CHROMA_PLANES  2U
#परिभाषय STD_VIDEO_H265_MAX_SHORT_पदांशः_REF_PIC_SETS 64U
#परिभाषय STD_VIDEO_H265_MAX_DPB_आकार       16U
#परिभाषय STD_VIDEO_H265_MAX_LONG_पदांशः_REF_PICS_SPS 32U
#परिभाषय STD_VIDEO_H265_MAX_LONG_पदांशः_PICS 16U
#परिभाषय STD_VIDEO_H265_MAX_DELTA_POC      48U
#परिभाषय STD_VIDEO_H265_NO_REFERENCE_PICTURE 0xFFU

प्रकारनिर्देश गणना StdVideoH265ChromaFormatIdc {
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ChromaFormatIdc;

प्रकारनिर्देश गणना StdVideoH265ProfileIdc {
    STD_VIDEO_H265_PROFILE_IDC_MAIN = 1,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_10 = 2,
    STD_VIDEO_H265_PROFILE_IDC_MAIN_STILL_PICTURE = 3,
    STD_VIDEO_H265_PROFILE_IDC_FORMAT_RANGE_EXTENSIONS = 4,
    STD_VIDEO_H265_PROFILE_IDC_SCC_EXTENSIONS = 9,
    STD_VIDEO_H265_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265ProfileIdc;

प्रकारनिर्देश गणना StdVideoH265LevelIdc {
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

प्रकारनिर्देश गणना Std_Video_H265_खण्डिका_Type {
    STD_VIDEO_H265_खण्डिका_TYPE_B = 0,
    STD_VIDEO_H265_खण्डिका_TYPE_P = 1,
    STD_VIDEO_H265_खण्डिका_TYPE_I = 2,
    STD_VIDEO_H265_खण्डिका_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_खण्डिका_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_खण्डिका_Type;

प्रकारनिर्देश गणना StdVideoH265PictureType {
    STD_VIDEO_H265_PICTURE_TYPE_P = 0,
    STD_VIDEO_H265_PICTURE_TYPE_B = 1,
    STD_VIDEO_H265_PICTURE_TYPE_I = 2,
    STD_VIDEO_H265_PICTURE_TYPE_IDR = 3,
    STD_VIDEO_H265_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH265PictureType;

प्रकारनिर्देश गणना Std_Video_H265_Aspect_अनुपातः_Idc {
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_वर्गफलम् = 1,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_12_11 = 2,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_10_11 = 3,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_16_11 = 4,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_40_33 = 5,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_24_11 = 6,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_20_11 = 7,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_32_11 = 8,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_80_33 = 9,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_18_11 = 10,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_15_11 = 11,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_64_33 = 12,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_160_99 = 13,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_4_3 = 14,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_3_2 = 15,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_2_1 = 16,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H265_ASPECT_अनुपातः_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H265_Aspect_अनुपातः_Idc;

प्रकारनिर्देश संरचना StdVideoH265DecPicBufMgr {
    uint32_t    max_latency_increase_plus1[STD_VIDEO_H265_SUBLAYERS_LIST_आकार];
    uint8_t     max_dec_pic_buffering_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_आकार];
    uint8_t     max_अङ्कः_reorder_pics[STD_VIDEO_H265_SUBLAYERS_LIST_आकार];
} StdVideoH265DecPicBufMgr;

प्रकारनिर्देश संरचना StdVideoH265SubLayerHrdParameters {
    uint32_t    bit_दरः_मानम्_minus1[STD_VIDEO_H265_CPB_CNT_LIST_आकार];
    uint32_t    cpb_आकार_मानम्_minus1[STD_VIDEO_H265_CPB_CNT_LIST_आकार];
    uint32_t    cpb_आकार_du_मानम्_minus1[STD_VIDEO_H265_CPB_CNT_LIST_आकार];
    uint32_t    bit_दरः_du_मानम्_minus1[STD_VIDEO_H265_CPB_CNT_LIST_आकार];
    uint32_t    cbr_flag;
} StdVideoH265SubLayerHrdParameters;

प्रकारनिर्देश संरचना StdVideoH265HrdFlags {
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
    uint32_t    sub_pic_hrd_params_present_flag : 1;
    uint32_t    sub_pic_cpb_params_अन्तर्_pic_timing_sei_flag : 1;
    uint32_t    fixed_pic_दरः_general_flag : 8;
    uint32_t    fixed_pic_दरः_within_cvs_flag : 8;
    uint32_t    नीचः_delay_hrd_flag : 8;
} StdVideoH265HrdFlags;

प्रकारनिर्देश संरचना StdVideoH265HrdParameters {
    StdVideoH265HrdFlags                        flags;
    uint8_t                                     tick_भाजकः_minus2;
    uint8_t                                     du_cpb_removal_delay_increment_दीर्घता_minus1;
    uint8_t                                     dpb_output_delay_du_दीर्घता_minus1;
    uint8_t                                     bit_दरः_scale;
    uint8_t                                     cpb_आकार_scale;
    uint8_t                                     cpb_आकार_du_scale;
    uint8_t                                     initial_cpb_removal_delay_दीर्घता_minus1;
    uint8_t                                     au_cpb_removal_delay_दीर्घता_minus1;
    uint8_t                                     dpb_output_delay_दीर्घता_minus1;
    uint8_t                                     cpb_cnt_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_आकार];
    uint16_t                                    elemental_duration_अन्तर्_tc_minus1[STD_VIDEO_H265_SUBLAYERS_LIST_आकार];
    uint16_t                                    reserved[3];
    ध्रुव StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersNal;
    ध्रुव StdVideoH265SubLayerHrdParameters*    pSubLayerHrdParametersVcl;
} StdVideoH265HrdParameters;

प्रकारनिर्देश संरचना StdVideoH265VpsFlags {
    uint32_t    vps_temporal_id_nesting_flag : 1;
    uint32_t    vps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    vps_timing_info_present_flag : 1;
    uint32_t    vps_poc_proportional_गन्तव्यम्_timing_flag : 1;
} StdVideoH265VpsFlags;

प्रकारनिर्देश संरचना StdVideoH265ProfileTierLevelFlags {
    uint32_t    general_tier_flag : 1;
    uint32_t    general_progressive_source_flag : 1;
    uint32_t    general_interlaced_source_flag : 1;
    uint32_t    general_non_packed_constraint_flag : 1;
    uint32_t    general_frame_only_constraint_flag : 1;
} StdVideoH265ProfileTierLevelFlags;

प्रकारनिर्देश संरचना StdVideoH265ProfileTierLevel {
    StdVideoH265ProfileTierLevelFlags    flags;
    StdVideoH265ProfileIdc               general_profile_idc;
    StdVideoH265LevelIdc                 general_level_idc;
} StdVideoH265ProfileTierLevel;

प्रकारनिर्देश संरचना Std_Video_H265_Video_Parameter_समुच्चयः {
    StdVideoH265VpsFlags                   flags;
    uint8_t                                vps_video_parameter_समुच्चयः_id;
    uint8_t                                vps_max_sub_layers_minus1;
    uint8_t                                reserved1;
    uint8_t                                reserved2;
    uint32_t                               vps_अङ्कः_units_अन्तर्_tick;
    uint32_t                               vps_time_scale;
    uint32_t                               vps_अङ्कः_ticks_poc_diff_one_minus1;
    uint32_t                               reserved3;
    ध्रुव StdVideoH265DecPicBufMgr*        pDecPicBufMgr;
    ध्रुव StdVideoH265HrdParameters*       pHrdParameters;
    ध्रुव StdVideoH265ProfileTierLevel*    pProfileTierLevel;
} Std_Video_H265_Video_Parameter_समुच्चयः;

प्रकारनिर्देश संरचना StdVideoH265ScalingLists {
    uint8_t    ScalingList4x4[STD_VIDEO_H265_SCALING_LIST_4_X4_अङ्कः_LISTS][STD_VIDEO_H265_SCALING_LIST_4_X4_अङ्कः_ELEMENTS];
    uint8_t    ScalingList8x8[STD_VIDEO_H265_SCALING_LIST_8_X8_अङ्कः_LISTS][STD_VIDEO_H265_SCALING_LIST_8_X8_अङ्कः_ELEMENTS];
    uint8_t    ScalingList16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_अङ्कः_LISTS][STD_VIDEO_H265_SCALING_LIST_16_X16_अङ्कः_ELEMENTS];
    uint8_t    ScalingList32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_अङ्कः_LISTS][STD_VIDEO_H265_SCALING_LIST_32_X32_अङ्कः_ELEMENTS];
    uint8_t    ScalingListDCCoef16x16[STD_VIDEO_H265_SCALING_LIST_16_X16_अङ्कः_LISTS];
    uint8_t    ScalingListDCCoef32x32[STD_VIDEO_H265_SCALING_LIST_32_X32_अङ्कः_LISTS];
} StdVideoH265ScalingLists;

प्रकारनिर्देश संरचना StdVideoH265SpsVuiFlags {
    uint32_t    aspect_अनुपातः_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_पूर्णम्_range_flag : 1;
    uint32_t    रङ्गः_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    neutral_chroma_indication_flag : 1;
    uint32_t    क्षेत्रम्_seq_flag : 1;
    uint32_t    frame_क्षेत्रम्_info_present_flag : 1;
    uint32_t    default_display_गवाक्षः_flag : 1;
    uint32_t    vui_timing_info_present_flag : 1;
    uint32_t    vui_poc_proportional_गन्तव्यम्_timing_flag : 1;
    uint32_t    vui_hrd_parameters_present_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    tiles_fixed_structure_flag : 1;
    uint32_t    motion_vectors_over_pic_boundaries_flag : 1;
    uint32_t    restricted_ref_pic_lists_flag : 1;
} StdVideoH265SpsVuiFlags;

प्रकारनिर्देश संरचना Std_Video_H265_Sequence_Parameter_समुच्चयः_Vui {
    StdVideoH265SpsVuiFlags             flags;
    Std_Video_H265_Aspect_अनुपातः_Idc          aspect_अनुपातः_idc;
    uint16_t                            sar_विस्तारः;
    uint16_t                            sar_height;
    uint8_t                             video_format;
    uint8_t                             रङ्गः_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             matrix_coeffs;
    uint8_t                             chroma_sample_loc_type_शिखरम्_क्षेत्रम्;
    uint8_t                             chroma_sample_loc_type_bottom_क्षेत्रम्;
    uint8_t                             reserved1;
    uint8_t                             reserved2;
    uint16_t                            def_disp_win_वामः_विस्थापनम्;
    uint16_t                            def_disp_win_दक्षिणः_विस्थापनम्;
    uint16_t                            def_disp_win_शिखरम्_विस्थापनम्;
    uint16_t                            def_disp_win_bottom_विस्थापनम्;
    uint32_t                            vui_अङ्कः_units_अन्तर्_tick;
    uint32_t                            vui_time_scale;
    uint32_t                            vui_अङ्कः_ticks_poc_diff_one_minus1;
    uint16_t                            min_spatial_segmentation_idc;
    uint16_t                            reserved3;
    uint8_t                             max_अष्टकानि_प्रत्येकम्_pic_denom;
    uint8_t                             max_द्वयङ्काः_प्रत्येकम्_min_cu_denom;
    uint8_t                             log2_max_mv_दीर्घता_horizontal;
    uint8_t                             log2_max_mv_दीर्घता_vertical;
    ध्रुव StdVideoH265HrdParameters*    pHrdParameters;
} Std_Video_H265_Sequence_Parameter_समुच्चयः_Vui;

प्रकारनिर्देश संरचना StdVideoH265PredictorPaletteEntries {
    uint16_t    PredictorPaletteEntries[STD_VIDEO_H265_PREDICTOR_PALETTE_COMPONENTS_LIST_आकार][STD_VIDEO_H265_PREDICTOR_PALETTE_COMP_ENTRIES_LIST_आकार];
} StdVideoH265PredictorPaletteEntries;

प्रकारनिर्देश संरचना StdVideoH265SpsFlags {
    uint32_t    sps_temporal_id_nesting_flag : 1;
    uint32_t    separate_रङ्गः_plane_flag : 1;
    uint32_t    conformance_गवाक्षः_flag : 1;
    uint32_t    sps_sub_layer_ordering_info_present_flag : 1;
    uint32_t    scaling_list_enabled_flag : 1;
    uint32_t    sps_scaling_list_दत्त_present_flag : 1;
    uint32_t    amp_enabled_flag : 1;
    uint32_t    sample_adaptive_विस्थापनम्_enabled_flag : 1;
    uint32_t    pcm_enabled_flag : 1;
    uint32_t    pcm_loop_filter_disabled_flag : 1;
    uint32_t    long_पदांशः_ref_pics_present_flag : 1;
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
    uint32_t    उच्चः_precision_offsets_enabled_flag : 1;
    uint32_t    persistent_rice_adaptation_enabled_flag : 1;
    uint32_t    cabac_bypass_alignment_enabled_flag : 1;
    uint32_t    sps_scc_extension_flag : 1;
    uint32_t    sps_curr_pic_ref_enabled_flag : 1;
    uint32_t    palette_बहुलकम्_enabled_flag : 1;
    uint32_t    sps_palette_predictor_initializers_present_flag : 1;
    uint32_t    intra_boundary_filtering_disabled_flag : 1;
} StdVideoH265SpsFlags;

प्रकारनिर्देश संरचना Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः_Flags {
    uint32_t    inter_ref_pic_समुच्चयः_prediction_flag : 1;
    uint32_t    delta_rps_sign : 1;
} Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः_Flags;

प्रकारनिर्देश संरचना Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः {
    Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः_Flags    flags;
    uint32_t                               delta_idx_minus1;
    uint16_t                               use_delta_flag;
    uint16_t                               abs_delta_rps_minus1;
    uint16_t                               प्रयुक्तम्_by_curr_pic_flag;
    uint16_t                               प्रयुक्तम्_by_curr_pic_s0_flag;
    uint16_t                               प्रयुक्तम्_by_curr_pic_s1_flag;
    uint16_t                               reserved1;
    uint8_t                                reserved2;
    uint8_t                                reserved3;
    uint8_t                                अङ्कः_negative_pics;
    uint8_t                                अङ्कः_धनात्मकम्_pics;
    uint16_t                               delta_poc_s0_minus1[STD_VIDEO_H265_MAX_DPB_आकार];
    uint16_t                               delta_poc_s1_minus1[STD_VIDEO_H265_MAX_DPB_आकार];
} Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः;

प्रकारनिर्देश संरचना Std_Video_H265_Long_पदांशः_Ref_Pics_Sps {
    uint32_t    प्रयुक्तम्_by_curr_pic_lt_sps_flag;
    uint32_t    lt_ref_pic_poc_lsb_sps[STD_VIDEO_H265_MAX_LONG_पदांशः_REF_PICS_SPS];
} Std_Video_H265_Long_पदांशः_Ref_Pics_Sps;

प्रकारनिर्देश संरचना Std_Video_H265_Sequence_Parameter_समुच्चयः {
    StdVideoH265SpsFlags                          flags;
    StdVideoH265ChromaFormatIdc                   chroma_format_idc;
    uint32_t                                      pic_विस्तारः_अन्तर्_luma_samples;
    uint32_t                                      pic_height_अन्तर्_luma_samples;
    uint8_t                                       sps_video_parameter_समुच्चयः_id;
    uint8_t                                       sps_max_sub_layers_minus1;
    uint8_t                                       sps_seq_parameter_समुच्चयः_id;
    uint8_t                                       bit_गभीरता_luma_minus8;
    uint8_t                                       bit_गभीरता_chroma_minus8;
    uint8_t                                       log2_max_pic_क्रमः_cnt_lsb_minus4;
    uint8_t                                       log2_min_luma_coding_खण्डम्_आकार_minus3;
    uint8_t                                       log2_diff_max_min_luma_coding_खण्डम्_आकार;
    uint8_t                                       log2_min_luma_transform_खण्डम्_आकार_minus2;
    uint8_t                                       log2_diff_max_min_luma_transform_खण्डम्_आकार;
    uint8_t                                       max_transform_hierarchy_गभीरता_inter;
    uint8_t                                       max_transform_hierarchy_गभीरता_intra;
    uint8_t                                       अङ्कः_short_पदांशः_ref_pic_sets;
    uint8_t                                       अङ्कः_long_पदांशः_ref_pics_sps;
    uint8_t                                       pcm_sample_bit_गभीरता_luma_minus1;
    uint8_t                                       pcm_sample_bit_गभीरता_chroma_minus1;
    uint8_t                                       log2_min_pcm_luma_coding_खण्डम्_आकार_minus3;
    uint8_t                                       log2_diff_max_min_pcm_luma_coding_खण्डम्_आकार;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint8_t                                       palette_max_आकार;
    uint8_t                                       delta_palette_max_predictor_आकार;
    uint8_t                                       motion_सदिशम्_resolution_control_idc;
    uint8_t                                       sps_अङ्कः_palette_predictor_initializers_minus1;
    uint32_t                                      conf_win_वामः_विस्थापनम्;
    uint32_t                                      conf_win_दक्षिणः_विस्थापनम्;
    uint32_t                                      conf_win_शिखरम्_विस्थापनम्;
    uint32_t                                      conf_win_bottom_विस्थापनम्;
    ध्रुव StdVideoH265ProfileTierLevel*           pProfileTierLevel;
    ध्रुव StdVideoH265DecPicBufMgr*               pDecPicBufMgr;
    ध्रुव StdVideoH265ScalingLists*               pScalingLists;
    ध्रुव Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः*         p_Short_पदांशः_Ref_Pic_समुच्चयः;
    ध्रुव Std_Video_H265_Long_पदांशः_Ref_Pics_Sps*         p_Long_पदांशः_Ref_Pics_Sps;
    ध्रुव Std_Video_H265_Sequence_Parameter_समुच्चयः_Vui*    p_Sequence_Parameter_समुच्चयः_Vui;
    ध्रुव StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Sequence_Parameter_समुच्चयः;

प्रकारनिर्देश संरचना StdVideoH265PpsFlags {
    uint32_t    dependent_खण्डिका_segments_enabled_flag : 1;
    uint32_t    output_flag_present_flag : 1;
    uint32_t    sign_दत्त_hiding_enabled_flag : 1;
    uint32_t    cabac_init_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    transform_skip_enabled_flag : 1;
    uint32_t    cu_qp_delta_enabled_flag : 1;
    uint32_t    pps_खण्डिका_chroma_qp_offsets_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    weighted_bipred_flag : 1;
    uint32_t    transquant_bypass_enabled_flag : 1;
    uint32_t    tiles_enabled_flag : 1;
    uint32_t    entropy_coding_sync_enabled_flag : 1;
    uint32_t    एकरूपम्_spacing_flag : 1;
    uint32_t    loop_filter_across_tiles_enabled_flag : 1;
    uint32_t    pps_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    deblocking_filter_override_enabled_flag : 1;
    uint32_t    pps_deblocking_filter_disabled_flag : 1;
    uint32_t    pps_scaling_list_दत्त_present_flag : 1;
    uint32_t    lists_modification_present_flag : 1;
    uint32_t    खण्डिका_segment_शीर्षकम्_extension_present_flag : 1;
    uint32_t    pps_extension_present_flag : 1;
    uint32_t    cross_component_prediction_enabled_flag : 1;
    uint32_t    chroma_qp_विस्थापनम्_list_enabled_flag : 1;
    uint32_t    pps_curr_pic_ref_enabled_flag : 1;
    uint32_t    residual_adaptive_रङ्गः_transform_enabled_flag : 1;
    uint32_t    pps_खण्डिका_act_qp_offsets_present_flag : 1;
    uint32_t    pps_palette_predictor_initializers_present_flag : 1;
    uint32_t    monochrome_palette_flag : 1;
    uint32_t    pps_range_extension_flag : 1;
} StdVideoH265PpsFlags;

प्रकारनिर्देश संरचना Std_Video_H265_Picture_Parameter_समुच्चयः {
    StdVideoH265PpsFlags                          flags;
    uint8_t                                       pps_pic_parameter_समुच्चयः_id;
    uint8_t                                       pps_seq_parameter_समुच्चयः_id;
    uint8_t                                       sps_video_parameter_समुच्चयः_id;
    uint8_t                                       अङ्कः_extra_खण्डिका_शीर्षकम्_द्वयङ्काः;
    uint8_t                                       अङ्कः_ref_idx_l0_default_सक्रिय_minus1;
    uint8_t                                       अङ्कः_ref_idx_l1_default_सक्रिय_minus1;
    int8_t                                        init_qp_minus26;
    uint8_t                                       diff_cu_qp_delta_गभीरता;
    int8_t                                        pps_cb_qp_विस्थापनम्;
    int8_t                                        pps_cr_qp_विस्थापनम्;
    int8_t                                        pps_beta_विस्थापनम्_div2;
    int8_t                                        pps_tc_विस्थापनम्_div2;
    uint8_t                                       log2_parallel_merge_level_minus2;
    uint8_t                                       log2_max_transform_skip_खण्डम्_आकार_minus2;
    uint8_t                                       diff_cu_chroma_qp_विस्थापनम्_गभीरता;
    uint8_t                                       chroma_qp_विस्थापनम्_list_len_minus1;
    int8_t                                        cb_qp_विस्थापनम्_list[STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_LIST_आकार];
    int8_t                                        cr_qp_विस्थापनम्_list[STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_LIST_आकार];
    uint8_t                                       log2_sao_विस्थापनम्_scale_luma;
    uint8_t                                       log2_sao_विस्थापनम्_scale_chroma;
    int8_t                                        pps_act_y_qp_विस्थापनम्_plus5;
    int8_t                                        pps_act_cb_qp_विस्थापनम्_plus5;
    int8_t                                        pps_act_cr_qp_विस्थापनम्_plus3;
    uint8_t                                       pps_अङ्कः_palette_predictor_initializers;
    uint8_t                                       luma_bit_गभीरता_प्रविष्टिः_minus8;
    uint8_t                                       chroma_bit_गभीरता_प्रविष्टिः_minus8;
    uint8_t                                       अङ्कः_tile_columns_minus1;
    uint8_t                                       अङ्कः_tile_पङ्क्तिकाः_minus1;
    uint8_t                                       reserved1;
    uint8_t                                       reserved2;
    uint16_t                                      column_विस्तारः_minus1[STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_TILE_स्तम्भसङ्ख्या_LIST_आकार];
    uint16_t                                      row_height_minus1[STD_VIDEO_H265_CHROMA_QP_विस्थापनम्_TILE_पङ्क्तिकाः_LIST_आकार];
    uint32_t                                      reserved3;
    ध्रुव StdVideoH265ScalingLists*               pScalingLists;
    ध्रुव StdVideoH265PredictorPaletteEntries*    pPredictorPaletteEntries;
} Std_Video_H265_Picture_Parameter_समुच्चयः;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
