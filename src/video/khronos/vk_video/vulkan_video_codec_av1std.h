#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_AV1STD_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_AV1STD_H_ 1

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



// vulkan_video_codec_av1std is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_av1std 1

#అన్తర్భావ "vulkan_video_codecs_common.h"

#నిర్వచించు STD_VIDEO_AV1_అంకె_REF_చట్రాలు      8U
#నిర్వచించు STD_VIDEO_AV1_REFS_చొప్పున_చట్రం      7U
#నిర్వచించు STD_VIDEO_AV1_మొత్తం_REFS_చొప్పున_చట్రం 8U
#నిర్వచించు STD_VIDEO_AV1_MAX_TILE_నిలువుల_సంఖ్య       64U
#నిర్వచించు STD_VIDEO_AV1_MAX_TILE_అడ్డువరుసలు       64U
#నిర్వచించు STD_VIDEO_AV1_MAX_SEGMENTS        8U
#నిర్వచించు STD_VIDEO_AV1_SEG_LVL_MAX         8U
#నిర్వచించు STD_VIDEO_AV1_PRIMARY_REF_NONE    7U
#నిర్వచించు STD_VIDEO_AV1_SELECT_INTEGER_MV   2U
#నిర్వచించు STD_VIDEO_AV1_SELECT_SCREEN_CONTENT_TOOLS 2U
#నిర్వచించు STD_VIDEO_AV1_SKIP_బహుళకం_చట్రాలు    2U
#నిర్వచించు STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS 4U
#నిర్వచించు STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS 2U
#నిర్వచించు STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS 8U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_PLANES      3U
#నిర్వచించు STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS 6U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_Y_POINTS    14U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_CB_POINTS   10U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_CR_POINTS   10U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_POS_LUMA    24U
#నిర్వచించు STD_VIDEO_AV1_MAX_అంకె_POS_CHROMA  25U

రకనిర్వచనం గణన StdVideoAV1Profile {
    STD_VIDEO_AV1_PROFILE_MAIN = 0,
    STD_VIDEO_AV1_PROFILE_ఎగువ = 1,
    STD_VIDEO_AV1_PROFILE_PROFESSIONAL = 2,
    STD_VIDEO_AV1_PROFILE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_PROFILE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Profile;

రకనిర్వచనం గణన StdVideoAV1Level {
    STD_VIDEO_AV1_LEVEL_2_0 = 0,
    STD_VIDEO_AV1_LEVEL_2_1 = 1,
    STD_VIDEO_AV1_LEVEL_2_2 = 2,
    STD_VIDEO_AV1_LEVEL_2_3 = 3,
    STD_VIDEO_AV1_LEVEL_3_0 = 4,
    STD_VIDEO_AV1_LEVEL_3_1 = 5,
    STD_VIDEO_AV1_LEVEL_3_2 = 6,
    STD_VIDEO_AV1_LEVEL_3_3 = 7,
    STD_VIDEO_AV1_LEVEL_4_0 = 8,
    STD_VIDEO_AV1_LEVEL_4_1 = 9,
    STD_VIDEO_AV1_LEVEL_4_2 = 10,
    STD_VIDEO_AV1_LEVEL_4_3 = 11,
    STD_VIDEO_AV1_LEVEL_5_0 = 12,
    STD_VIDEO_AV1_LEVEL_5_1 = 13,
    STD_VIDEO_AV1_LEVEL_5_2 = 14,
    STD_VIDEO_AV1_LEVEL_5_3 = 15,
    STD_VIDEO_AV1_LEVEL_6_0 = 16,
    STD_VIDEO_AV1_LEVEL_6_1 = 17,
    STD_VIDEO_AV1_LEVEL_6_2 = 18,
    STD_VIDEO_AV1_LEVEL_6_3 = 19,
    STD_VIDEO_AV1_LEVEL_7_0 = 20,
    STD_VIDEO_AV1_LEVEL_7_1 = 21,
    STD_VIDEO_AV1_LEVEL_7_2 = 22,
    STD_VIDEO_AV1_LEVEL_7_3 = 23,
    STD_VIDEO_AV1_LEVEL_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_LEVEL_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Level;

రకనిర్వచనం గణన Std_Video_AV1_చట్రం_Type {
    STD_VIDEO_AV1_చట్రం_TYPE_కీలకం = 0,
    STD_VIDEO_AV1_చట్రం_TYPE_INTER = 1,
    STD_VIDEO_AV1_చట్రం_TYPE_INTRA_ONLY = 2,
    STD_VIDEO_AV1_చట్రం_TYPE_SWITCH = 3,
    STD_VIDEO_AV1_చట్రం_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_చట్రం_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_చట్రం_Type;

రకనిర్వచనం గణన StdVideoAV1ReferenceName {
    STD_VIDEO_AV1_REFERENCE_NAME_INTRA_చట్రం = 0,
    STD_VIDEO_AV1_REFERENCE_NAME_చివరి_చట్రం = 1,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST2_చట్రం = 2,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST3_చట్రం = 3,
    STD_VIDEO_AV1_REFERENCE_NAME_GOLDEN_చట్రం = 4,
    STD_VIDEO_AV1_REFERENCE_NAME_BWDREF_చట్రం = 5,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF2_చట్రం = 6,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF_చట్రం = 7,
    STD_VIDEO_AV1_REFERENCE_NAME_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_REFERENCE_NAME_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ReferenceName;

రకనిర్వచనం గణన StdVideoAV1InterpolationFilter {
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP = 0,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SMOOTH = 1,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SHARP = 2,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_BILINEAR = 3,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_SWITCHABLE = 4,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1InterpolationFilter;

రకనిర్వచనం గణన Std_Video_AV1_Tx_బహుళకం {
    STD_VIDEO_AV1_TX_బహుళకం_ONLY_4_X4 = 0,
    STD_VIDEO_AV1_TX_బహుళకం_అతిపెద్ద = 1,
    STD_VIDEO_AV1_TX_బహుళకం_SELECT = 2,
    STD_VIDEO_AV1_TX_బహుళకం_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TX_బహుళకం_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_Tx_బహుళకం;

రకనిర్వచనం గణన Std_Video_AV1_చట్రం_Restoration_Type {
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_NONE = 0,
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_WIENER = 1,
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_SGRPROJ = 2,
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_SWITCHABLE = 3,
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_చట్రం_RESTORATION_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_చట్రం_Restoration_Type;

రకనిర్వచనం గణన StdVideoAV1ColorPrimaries {
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_709 = 1,
    STD_VIDEO_AV1_COLOR_PRIMARIES_UNSPECIFIED = 2,
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_470_M = 4,
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_470_B_G = 5,
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_601 = 6,
    STD_VIDEO_AV1_COLOR_PRIMARIES_SMPTE_240 = 7,
    STD_VIDEO_AV1_COLOR_PRIMARIES_GENERIC_FILM = 8,
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_2020 = 9,
    STD_VIDEO_AV1_COLOR_PRIMARIES_XYZ = 10,
    STD_VIDEO_AV1_COLOR_PRIMARIES_SMPTE_431 = 11,
    STD_VIDEO_AV1_COLOR_PRIMARIES_SMPTE_432 = 12,
    STD_VIDEO_AV1_COLOR_PRIMARIES_EBU_3213 = 22,
    STD_VIDEO_AV1_COLOR_PRIMARIES_INVALID = 0x7FFFFFFF,
  // STD_VIDEO_AV1_COLOR_PRIMARIES_BT_UNSPECIFIED is a legacy alias
    STD_VIDEO_AV1_COLOR_PRIMARIES_BT_UNSPECIFIED = STD_VIDEO_AV1_COLOR_PRIMARIES_UNSPECIFIED,
    STD_VIDEO_AV1_COLOR_PRIMARIES_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ColorPrimaries;

రకనిర్వచనం గణన StdVideoAV1TransferCharacteristics {
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_0 = 0,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_709 = 1,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_3 = 3,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_M = 4,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_B_G = 5,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_601 = 6,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_240 = 7,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_రేఖీయ = 8,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100 = 9,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100_SQRT10 = 10,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_IEC_61966 = 11,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_1361 = 12,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SRGB = 13,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_10_బిట్టు = 14,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_12_బిట్టు = 15,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_2084 = 16,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_428 = 17,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_HLG = 18,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1TransferCharacteristics;

రకనిర్వచనం గణన Std_Video_AV1_మాతృక_Coefficients {
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_తటస్థం = 0,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_BT_709 = 1,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_RESERVED_3 = 3,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_FCC = 4,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_BT_470_B_G = 5,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_BT_601 = 6,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_SMPTE_240 = 7,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_SMPTE_YCGCO = 8,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_BT_2020_NCL = 9,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_BT_2020_CL = 10,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_SMPTE_2085 = 11,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_CHROMAT_NCL = 12,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_CHROMAT_CL = 13,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_ICTCP = 14,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_మాతృక_COEFFICIENTS_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_మాతృక_Coefficients;

రకనిర్వచనం గణన StdVideoAV1ChromaSamplePosition {
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_UNKNOWN = 0,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_VERTICAL = 1,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_COLOCATED = 2,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_RESERVED = 3,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ChromaSamplePosition;

రకనిర్వచనం నిర్మాణం StdVideoAV1ColorConfigFlags {
    uint32_t    mono_chrome : 1;
    uint32_t    color_range : 1;
    uint32_t    separate_uv_delta_q : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    reserved : 28;
} StdVideoAV1ColorConfigFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1ColorConfig {
    StdVideoAV1ColorConfigFlags           flags;
    uint8_t                               బిట్టు_లోతు;
    uint8_t                               subsampling_x;
    uint8_t                               subsampling_y;
    uint8_t                               reserved1;
    StdVideoAV1ColorPrimaries             color_primaries;
    StdVideoAV1TransferCharacteristics    transfer_characteristics;
    Std_Video_AV1_మాతృక_Coefficients         మాతృక_coefficients;
    StdVideoAV1ChromaSamplePosition       chroma_sample_position;
} StdVideoAV1ColorConfig;

రకనిర్వచనం నిర్మాణం StdVideoAV1TimingInfoFlags {
    uint32_t    equal_picture_interval : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TimingInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1TimingInfo {
    StdVideoAV1TimingInfoFlags    flags;
    uint32_t                      అంకె_units_లోపల_display_tick;
    uint32_t                      సమయం_scale;
    uint32_t                      అంకె_ticks_చొప్పున_picture_minus_1;
} StdVideoAV1TimingInfo;

రకనిర్వచనం నిర్మాణం StdVideoAV1LoopFilterFlags {
    uint32_t    loop_filter_delta_enabled : 1;
    uint32_t    loop_filter_delta_update : 1;
    uint32_t    reserved : 30;
} StdVideoAV1LoopFilterFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1LoopFilter {
    StdVideoAV1LoopFilterFlags    flags;
    uint8_t                       loop_filter_level[STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS];
    uint8_t                       loop_filter_sharpness;
    uint8_t                       update_ref_delta;
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_AV1_మొత్తం_REFS_చొప్పున_చట్రం];
    uint8_t                       update_బహుళకం_delta;
    int8_t                        loop_filter_బహుళకం_deltas[STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS];
} StdVideoAV1LoopFilter;

రకనిర్వచనం నిర్మాణం StdVideoAV1QuantizationFlags {
    uint32_t    using_qmatrix : 1;
    uint32_t    diff_uv_delta : 1;
    uint32_t    reserved : 30;
} StdVideoAV1QuantizationFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1Quantization {
    StdVideoAV1QuantizationFlags    flags;
    uint8_t                         పునాది_q_idx;
    int8_t                          DeltaQYDc;
    int8_t                          DeltaQUDc;
    int8_t                          DeltaQUAc;
    int8_t                          DeltaQVDc;
    int8_t                          DeltaQVAc;
    uint8_t                         qm_y;
    uint8_t                         qm_u;
    uint8_t                         qm_v;
} StdVideoAV1Quantization;

రకనిర్వచనం నిర్మాణం StdVideoAV1Segmentation {
    uint8_t    FeatureEnabled[STD_VIDEO_AV1_MAX_SEGMENTS];
    int16_t    Feature_దత్తాంశం[STD_VIDEO_AV1_MAX_SEGMENTS][STD_VIDEO_AV1_SEG_LVL_MAX];
} StdVideoAV1Segmentation;

రకనిర్వచనం నిర్మాణం StdVideoAV1TileInfoFlags {
    uint32_t    ఏకరీతి_tile_spacing_flag : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TileInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1TileInfo {
    StdVideoAV1TileInfoFlags    flags;
    uint8_t                     Tile_నిలువుల_సంఖ్య;
    uint8_t                     Tile_అడ్డువరుసలు;
    uint16_t                    context_update_tile_id;
    uint8_t                     tile_కొలత_బైట్లు_minus_1;
    uint8_t                     reserved1[7];
    స్థిరరాశి uint16_t*             p_Mi_నిలువు_Starts;
    స్థిరరాశి uint16_t*             p_Mi_అడ్డువరుస_Starts;
    స్థిరరాశి uint16_t*             p_వెడల్పు_లోపల_Sbs_Minus1;
    స్థిరరాశి uint16_t*             p_ఎత్తు_లోపల_Sbs_Minus1;
} StdVideoAV1TileInfo;

రకనిర్వచనం నిర్మాణం StdVideoAV1CDEF {
    uint8_t    cdef_damping_minus_3;
    uint8_t    cdef_బిట్లు;
    uint8_t    cdef_y_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_y_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
} StdVideoAV1CDEF;

రకనిర్వచనం నిర్మాణం StdVideoAV1LoopRestoration {
    Std_Video_AV1_చట్రం_Restoration_Type    చట్రం_Restoration_Type[STD_VIDEO_AV1_MAX_అంకె_PLANES];
    uint16_t                           Loop_Restoration_కొలత[STD_VIDEO_AV1_MAX_అంకె_PLANES];
} StdVideoAV1LoopRestoration;

రకనిర్వచనం నిర్మాణం StdVideoAV1GlobalMotion {
    uint8_t    GmType[STD_VIDEO_AV1_అంకె_REF_చట్రాలు];
    int32_t    gm_params[STD_VIDEO_AV1_అంకె_REF_చట్రాలు][STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS];
} StdVideoAV1GlobalMotion;

రకనిర్వచనం నిర్మాణం StdVideoAV1FilmGrainFlags {
    uint32_t    chroma_scaling_from_luma : 1;
    uint32_t    overlap_flag : 1;
    uint32_t    clip_గమ్యం_restricted_range : 1;
    uint32_t    update_grain : 1;
    uint32_t    reserved : 28;
} StdVideoAV1FilmGrainFlags;

రకనిర్వచనం నిర్మాణం StdVideoAV1FilmGrain {
    StdVideoAV1FilmGrainFlags    flags;
    uint8_t                      grain_scaling_minus_8;
    uint8_t                      ar_coeff_lag;
    uint8_t                      ar_coeff_జరుపు_minus_6;
    uint8_t                      grain_scale_జరుపు;
    uint16_t                     grain_విత్తనం;
    uint8_t                      film_grain_params_ref_idx;
    uint8_t                      అంకె_y_points;
    uint8_t                      బిందువు_y_విలువ[STD_VIDEO_AV1_MAX_అంకె_Y_POINTS];
    uint8_t                      బిందువు_y_scaling[STD_VIDEO_AV1_MAX_అంకె_Y_POINTS];
    uint8_t                      అంకె_cb_points;
    uint8_t                      బిందువు_cb_విలువ[STD_VIDEO_AV1_MAX_అంకె_CB_POINTS];
    uint8_t                      బిందువు_cb_scaling[STD_VIDEO_AV1_MAX_అంకె_CB_POINTS];
    uint8_t                      అంకె_cr_points;
    uint8_t                      బిందువు_cr_విలువ[STD_VIDEO_AV1_MAX_అంకె_CR_POINTS];
    uint8_t                      బిందువు_cr_scaling[STD_VIDEO_AV1_MAX_అంకె_CR_POINTS];
    int8_t                       ar_coeffs_y_plus_128[STD_VIDEO_AV1_MAX_అంకె_POS_LUMA];
    int8_t                       ar_coeffs_cb_plus_128[STD_VIDEO_AV1_MAX_అంకె_POS_CHROMA];
    int8_t                       ar_coeffs_cr_plus_128[STD_VIDEO_AV1_MAX_అంకె_POS_CHROMA];
    uint8_t                      cb_mult;
    uint8_t                      cb_luma_mult;
    uint16_t                     cb_స్థానభ్రంశం;
    uint8_t                      cr_mult;
    uint8_t                      cr_luma_mult;
    uint16_t                     cr_స్థానభ్రంశం;
} StdVideoAV1FilmGrain;

రకనిర్వచనం నిర్మాణం Std_Video_AV1_Sequence_శీర్షిక_Flags {
    uint32_t    still_picture : 1;
    uint32_t    reduced_still_picture_శీర్షిక : 1;
    uint32_t    use_128x128_superblock : 1;
    uint32_t    enable_filter_intra : 1;
    uint32_t    enable_intra_అంచు_filter : 1;
    uint32_t    enable_interintra_compound : 1;
    uint32_t    enable_masked_compound : 1;
    uint32_t    enable_warped_motion : 1;
    uint32_t    enable_dual_filter : 1;
    uint32_t    enable_క్రమం_hint : 1;
    uint32_t    enable_jnt_comp : 1;
    uint32_t    enable_ref_చట్రం_mvs : 1;
    uint32_t    చట్రం_id_numbers_present_flag : 1;
    uint32_t    enable_superres : 1;
    uint32_t    enable_cdef : 1;
    uint32_t    enable_restoration : 1;
    uint32_t    film_grain_params_present : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    initial_display_delay_present_flag : 1;
    uint32_t    reserved : 13;
} Std_Video_AV1_Sequence_శీర్షిక_Flags;

రకనిర్వచనం నిర్మాణం Std_Video_AV1_Sequence_శీర్షిక {
    Std_Video_AV1_Sequence_శీర్షిక_Flags    flags;
    StdVideoAV1Profile                seq_profile;
    uint8_t                           చట్రం_వెడల్పు_బిట్లు_minus_1;
    uint8_t                           చట్రం_ఎత్తు_బిట్లు_minus_1;
    uint16_t                          max_చట్రం_వెడల్పు_minus_1;
    uint16_t                          max_చట్రం_ఎత్తు_minus_1;
    uint8_t                           delta_చట్రం_id_నిడివి_minus_2;
    uint8_t                           additional_చట్రం_id_నిడివి_minus_1;
    uint8_t                           క్రమం_hint_బిట్లు_minus_1;
    uint8_t                           seq_force_integer_mv;
    uint8_t                           seq_force_screen_content_tools;
    uint8_t                           reserved1[5];
    స్థిరరాశి StdVideoAV1ColorConfig*     pColorConfig;
    స్థిరరాశి StdVideoAV1TimingInfo*      pTimingInfo;
} Std_Video_AV1_Sequence_శీర్షిక;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
