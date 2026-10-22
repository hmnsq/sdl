#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_AV1STD_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_AV1STD_H_ 1

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



// vulkan_video_codec_av1std is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_av1std 1

#ضمن "vulkan_video_codecs_common.h"

#وصف_ڪريو STD_VIDEO_AV1_انگ_REF_چوکٺا      8U
#وصف_ڪريو STD_VIDEO_AV1_REFS_في_چوکٺو      7U
#وصف_ڪريو STD_VIDEO_AV1_ڪل_REFS_في_چوکٺو 8U
#وصف_ڪريو STD_VIDEO_AV1_MAX_TILE_کانن_ڳڻپ       64U
#وصف_ڪريو STD_VIDEO_AV1_MAX_TILE_صفون       64U
#وصف_ڪريو STD_VIDEO_AV1_MAX_SEGMENTS        8U
#وصف_ڪريو STD_VIDEO_AV1_SEG_LVL_MAX         8U
#وصف_ڪريو STD_VIDEO_AV1_PRIMARY_REF_NONE    7U
#وصف_ڪريو STD_VIDEO_AV1_SELECT_INTEGER_MV   2U
#وصف_ڪريو STD_VIDEO_AV1_SELECT_SCREEN_CONTENT_TOOLS 2U
#وصف_ڪريو STD_VIDEO_AV1_SKIP_گهڻائي_چوکٺا    2U
#وصف_ڪريو STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS 4U
#وصف_ڪريو STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS 2U
#وصف_ڪريو STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS 8U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_PLANES      3U
#وصف_ڪريو STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS 6U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_Y_POINTS    14U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_CB_POINTS   10U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_CR_POINTS   10U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_POS_LUMA    24U
#وصف_ڪريو STD_VIDEO_AV1_MAX_انگ_POS_CHROMA  25U

تعريفنوع تعداد StdVideoAV1Profile {
    STD_VIDEO_AV1_PROFILE_MAIN = 0,
    STD_VIDEO_AV1_PROFILE_مٿاهون = 1,
    STD_VIDEO_AV1_PROFILE_PROFESSIONAL = 2,
    STD_VIDEO_AV1_PROFILE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_PROFILE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Profile;

تعريفنوع تعداد StdVideoAV1Level {
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

تعريفنوع تعداد Std_Video_AV1_چوکٺو_Type {
    STD_VIDEO_AV1_چوکٺو_TYPE_ڪنجي = 0,
    STD_VIDEO_AV1_چوکٺو_TYPE_INTER = 1,
    STD_VIDEO_AV1_چوکٺو_TYPE_INTRA_ONLY = 2,
    STD_VIDEO_AV1_چوکٺو_TYPE_SWITCH = 3,
    STD_VIDEO_AV1_چوکٺو_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_چوکٺو_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_چوکٺو_Type;

تعريفنوع تعداد StdVideoAV1ReferenceName {
    STD_VIDEO_AV1_REFERENCE_NAME_INTRA_چوکٺو = 0,
    STD_VIDEO_AV1_REFERENCE_NAME_آخري_چوکٺو = 1,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST2_چوکٺو = 2,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST3_چوکٺو = 3,
    STD_VIDEO_AV1_REFERENCE_NAME_GOLDEN_چوکٺو = 4,
    STD_VIDEO_AV1_REFERENCE_NAME_BWDREF_چوکٺو = 5,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF2_چوکٺو = 6,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF_چوکٺو = 7,
    STD_VIDEO_AV1_REFERENCE_NAME_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_REFERENCE_NAME_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ReferenceName;

تعريفنوع تعداد StdVideoAV1InterpolationFilter {
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP = 0,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SMOOTH = 1,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SHARP = 2,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_BILINEAR = 3,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_SWITCHABLE = 4,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1InterpolationFilter;

تعريفنوع تعداد Std_Video_AV1_Tx_گهڻائي {
    STD_VIDEO_AV1_TX_گهڻائي_ONLY_4_X4 = 0,
    STD_VIDEO_AV1_TX_گهڻائي_سڀ_کان_وڏو = 1,
    STD_VIDEO_AV1_TX_گهڻائي_SELECT = 2,
    STD_VIDEO_AV1_TX_گهڻائي_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TX_گهڻائي_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_Tx_گهڻائي;

تعريفنوع تعداد Std_Video_AV1_چوکٺو_Restoration_Type {
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_NONE = 0,
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_WIENER = 1,
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_SGRPROJ = 2,
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_SWITCHABLE = 3,
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_چوکٺو_RESTORATION_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_چوکٺو_Restoration_Type;

تعريفنوع تعداد StdVideoAV1ColorPrimaries {
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

تعريفنوع تعداد StdVideoAV1TransferCharacteristics {
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_0 = 0,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_709 = 1,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_3 = 3,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_M = 4,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_B_G = 5,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_601 = 6,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_240 = 7,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_لڪيري = 8,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100 = 9,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100_SQRT10 = 10,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_IEC_61966 = 11,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_1361 = 12,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SRGB = 13,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_10_ٻٽو_انگ = 14,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_12_ٻٽو_انگ = 15,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_2084 = 16,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_428 = 17,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_HLG = 18,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1TransferCharacteristics;

تعريفنوع تعداد Std_Video_AV1_ميٽرڪس_Coefficients {
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_سڃاڻپ_عنصر = 0,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_BT_709 = 1,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_RESERVED_3 = 3,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_FCC = 4,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_BT_470_B_G = 5,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_BT_601 = 6,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_SMPTE_240 = 7,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_SMPTE_YCGCO = 8,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_BT_2020_NCL = 9,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_BT_2020_CL = 10,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_SMPTE_2085 = 11,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_CHROMAT_NCL = 12,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_CHROMAT_CL = 13,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_ICTCP = 14,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_ميٽرڪس_COEFFICIENTS_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_ميٽرڪس_Coefficients;

تعريفنوع تعداد StdVideoAV1ChromaSamplePosition {
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_UNKNOWN = 0,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_VERTICAL = 1,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_COLOCATED = 2,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_RESERVED = 3,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ChromaSamplePosition;

تعريفنوع بنية StdVideoAV1ColorConfigFlags {
    uint32_t    mono_chrome : 1;
    uint32_t    color_range : 1;
    uint32_t    separate_uv_delta_q : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    reserved : 28;
} StdVideoAV1ColorConfigFlags;

تعريفنوع بنية StdVideoAV1ColorConfig {
    StdVideoAV1ColorConfigFlags           flags;
    uint8_t                               ٻٽو_انگ_اونهائي;
    uint8_t                               subsampling_x;
    uint8_t                               subsampling_y;
    uint8_t                               reserved1;
    StdVideoAV1ColorPrimaries             color_primaries;
    StdVideoAV1TransferCharacteristics    transfer_characteristics;
    Std_Video_AV1_ميٽرڪس_Coefficients         ميٽرڪس_coefficients;
    StdVideoAV1ChromaSamplePosition       chroma_sample_position;
} StdVideoAV1ColorConfig;

تعريفنوع بنية StdVideoAV1TimingInfoFlags {
    uint32_t    equal_picture_interval : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TimingInfoFlags;

تعريفنوع بنية StdVideoAV1TimingInfo {
    StdVideoAV1TimingInfoFlags    flags;
    uint32_t                      انگ_units_اندريون_display_tick;
    uint32_t                      وقت_scale;
    uint32_t                      انگ_ticks_في_picture_minus_1;
} StdVideoAV1TimingInfo;

تعريفنوع بنية StdVideoAV1LoopFilterFlags {
    uint32_t    loop_filter_delta_enabled : 1;
    uint32_t    loop_filter_delta_update : 1;
    uint32_t    reserved : 30;
} StdVideoAV1LoopFilterFlags;

تعريفنوع بنية StdVideoAV1LoopFilter {
    StdVideoAV1LoopFilterFlags    flags;
    uint8_t                       loop_filter_level[STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS];
    uint8_t                       loop_filter_sharpness;
    uint8_t                       update_ref_delta;
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_AV1_ڪل_REFS_في_چوکٺو];
    uint8_t                       update_گهڻائي_delta;
    int8_t                        loop_filter_گهڻائي_deltas[STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS];
} StdVideoAV1LoopFilter;

تعريفنوع بنية StdVideoAV1QuantizationFlags {
    uint32_t    using_qmatrix : 1;
    uint32_t    diff_uv_delta : 1;
    uint32_t    reserved : 30;
} StdVideoAV1QuantizationFlags;

تعريفنوع بنية StdVideoAV1Quantization {
    StdVideoAV1QuantizationFlags    flags;
    uint8_t                         بنياد_q_idx;
    int8_t                          DeltaQYDc;
    int8_t                          DeltaQUDc;
    int8_t                          DeltaQUAc;
    int8_t                          DeltaQVDc;
    int8_t                          DeltaQVAc;
    uint8_t                         qm_y;
    uint8_t                         qm_u;
    uint8_t                         qm_v;
} StdVideoAV1Quantization;

تعريفنوع بنية StdVideoAV1Segmentation {
    uint8_t    FeatureEnabled[STD_VIDEO_AV1_MAX_SEGMENTS];
    int16_t    Feature_معلومات[STD_VIDEO_AV1_MAX_SEGMENTS][STD_VIDEO_AV1_SEG_LVL_MAX];
} StdVideoAV1Segmentation;

تعريفنوع بنية StdVideoAV1TileInfoFlags {
    uint32_t    هڪجهڙو_tile_spacing_flag : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TileInfoFlags;

تعريفنوع بنية StdVideoAV1TileInfo {
    StdVideoAV1TileInfoFlags    flags;
    uint8_t                     Tile_کانن_ڳڻپ;
    uint8_t                     Tile_صفون;
    uint16_t                    context_update_tile_id;
    uint8_t                     tile_سائيز_بائيٽون_minus_1;
    uint8_t                     reserved1[7];
    ثابت uint16_t*             p_Mi_کانو_Starts;
    ثابت uint16_t*             p_Mi_صف_Starts;
    ثابت uint16_t*             p_ويڪر_اندريون_Sbs_Minus1;
    ثابت uint16_t*             p_اوچائي_اندريون_Sbs_Minus1;
} StdVideoAV1TileInfo;

تعريفنوع بنية StdVideoAV1CDEF {
    uint8_t    cdef_damping_minus_3;
    uint8_t    cdef_بٽ;
    uint8_t    cdef_y_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_y_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
} StdVideoAV1CDEF;

تعريفنوع بنية StdVideoAV1LoopRestoration {
    Std_Video_AV1_چوکٺو_Restoration_Type    چوکٺو_Restoration_Type[STD_VIDEO_AV1_MAX_انگ_PLANES];
    uint16_t                           Loop_Restoration_سائيز[STD_VIDEO_AV1_MAX_انگ_PLANES];
} StdVideoAV1LoopRestoration;

تعريفنوع بنية StdVideoAV1GlobalMotion {
    uint8_t    GmType[STD_VIDEO_AV1_انگ_REF_چوکٺا];
    int32_t    gm_params[STD_VIDEO_AV1_انگ_REF_چوکٺا][STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS];
} StdVideoAV1GlobalMotion;

تعريفنوع بنية StdVideoAV1FilmGrainFlags {
    uint32_t    chroma_scaling_from_luma : 1;
    uint32_t    overlap_flag : 1;
    uint32_t    clip_منزل_restricted_range : 1;
    uint32_t    update_grain : 1;
    uint32_t    reserved : 28;
} StdVideoAV1FilmGrainFlags;

تعريفنوع بنية StdVideoAV1FilmGrain {
    StdVideoAV1FilmGrainFlags    flags;
    uint8_t                      grain_scaling_minus_8;
    uint8_t                      ar_coeff_lag;
    uint8_t                      ar_coeff_سرڪايو_minus_6;
    uint8_t                      grain_scale_سرڪايو;
    uint16_t                     grain_ٻج;
    uint8_t                      film_grain_params_ref_idx;
    uint8_t                      انگ_y_points;
    uint8_t                      نقطو_y_قدر[STD_VIDEO_AV1_MAX_انگ_Y_POINTS];
    uint8_t                      نقطو_y_scaling[STD_VIDEO_AV1_MAX_انگ_Y_POINTS];
    uint8_t                      انگ_cb_points;
    uint8_t                      نقطو_cb_قدر[STD_VIDEO_AV1_MAX_انگ_CB_POINTS];
    uint8_t                      نقطو_cb_scaling[STD_VIDEO_AV1_MAX_انگ_CB_POINTS];
    uint8_t                      انگ_cr_points;
    uint8_t                      نقطو_cr_قدر[STD_VIDEO_AV1_MAX_انگ_CR_POINTS];
    uint8_t                      نقطو_cr_scaling[STD_VIDEO_AV1_MAX_انگ_CR_POINTS];
    int8_t                       ar_coeffs_y_plus_128[STD_VIDEO_AV1_MAX_انگ_POS_LUMA];
    int8_t                       ar_coeffs_cb_plus_128[STD_VIDEO_AV1_MAX_انگ_POS_CHROMA];
    int8_t                       ar_coeffs_cr_plus_128[STD_VIDEO_AV1_MAX_انگ_POS_CHROMA];
    uint8_t                      cb_mult;
    uint8_t                      cb_luma_mult;
    uint16_t                     cb_وٿي;
    uint8_t                      cr_mult;
    uint8_t                      cr_luma_mult;
    uint16_t                     cr_وٿي;
} StdVideoAV1FilmGrain;

تعريفنوع بنية Std_Video_AV1_Sequence_سرو_Flags {
    uint32_t    still_picture : 1;
    uint32_t    reduced_still_picture_سرو : 1;
    uint32_t    use_128x128_superblock : 1;
    uint32_t    enable_filter_intra : 1;
    uint32_t    enable_intra_ڪنارو_filter : 1;
    uint32_t    enable_interintra_compound : 1;
    uint32_t    enable_masked_compound : 1;
    uint32_t    enable_warped_motion : 1;
    uint32_t    enable_dual_filter : 1;
    uint32_t    enable_ترتيب_hint : 1;
    uint32_t    enable_jnt_comp : 1;
    uint32_t    enable_ref_چوکٺو_mvs : 1;
    uint32_t    چوکٺو_id_numbers_present_flag : 1;
    uint32_t    enable_superres : 1;
    uint32_t    enable_cdef : 1;
    uint32_t    enable_restoration : 1;
    uint32_t    film_grain_params_present : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    initial_display_delay_present_flag : 1;
    uint32_t    reserved : 13;
} Std_Video_AV1_Sequence_سرو_Flags;

تعريفنوع بنية Std_Video_AV1_Sequence_سرو {
    Std_Video_AV1_Sequence_سرو_Flags    flags;
    StdVideoAV1Profile                seq_profile;
    uint8_t                           چوکٺو_ويڪر_بٽ_minus_1;
    uint8_t                           چوکٺو_اوچائي_بٽ_minus_1;
    uint16_t                          max_چوکٺو_ويڪر_minus_1;
    uint16_t                          max_چوکٺو_اوچائي_minus_1;
    uint8_t                           delta_چوکٺو_id_ڊيگهائي_minus_2;
    uint8_t                           additional_چوکٺو_id_ڊيگهائي_minus_1;
    uint8_t                           ترتيب_hint_بٽ_minus_1;
    uint8_t                           seq_force_integer_mv;
    uint8_t                           seq_force_screen_content_tools;
    uint8_t                           reserved1[5];
    ثابت StdVideoAV1ColorConfig*     pColorConfig;
    ثابت StdVideoAV1TimingInfo*      pTimingInfo;
} Std_Video_AV1_Sequence_سرو;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
