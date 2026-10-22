#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_AV1STD_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_AV1STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// vulkan_video_codec_av1std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_av1std 1

#ضمن "vulkan_video_codecs_common.h"

#تعریف_کړه STD_VIDEO_AV1_عدد_REF_چوکاټونه      8U
#تعریف_کړه STD_VIDEO_AV1_REFS_فی_چوکاټ      7U
#تعریف_کړه STD_VIDEO_AV1_ټول_REFS_فی_چوکاټ 8U
#تعریف_کړه STD_VIDEO_AV1_MAX_TILE_ستون_شمېر       64U
#تعریف_کړه STD_VIDEO_AV1_MAX_TILE_لیکې       64U
#تعریف_کړه STD_VIDEO_AV1_MAX_SEGMENTS        8U
#تعریف_کړه STD_VIDEO_AV1_SEG_LVL_MAX         8U
#تعریف_کړه STD_VIDEO_AV1_PRIMARY_REF_NONE    7U
#تعریف_کړه STD_VIDEO_AV1_SELECT_INTEGER_MV   2U
#تعریف_کړه STD_VIDEO_AV1_SELECT_SCREEN_CONTENT_TOOLS 2U
#تعریف_کړه STD_VIDEO_AV1_SKIP_ډېرپېښ_چوکاټونه    2U
#تعریف_کړه STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS 4U
#تعریف_کړه STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS 2U
#تعریف_کړه STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS 8U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_PLANES      3U
#تعریف_کړه STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS 6U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_Y_POINTS    14U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_CB_POINTS   10U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_CR_POINTS   10U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_POS_LUMA    24U
#تعریف_کړه STD_VIDEO_AV1_MAX_عدد_POS_CHROMA  25U

تعريفنوع تعداد StdVideoAV1Profile {
    STD_VIDEO_AV1_PROFILE_MAIN = 0,
    STD_VIDEO_AV1_PROFILE_لوړ = 1,
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

تعريفنوع تعداد Std_Video_AV1_چوکاټ_Type {
    STD_VIDEO_AV1_چوکاټ_TYPE_کلی = 0,
    STD_VIDEO_AV1_چوکاټ_TYPE_INTER = 1,
    STD_VIDEO_AV1_چوکاټ_TYPE_INTRA_ONLY = 2,
    STD_VIDEO_AV1_چوکاټ_TYPE_SWITCH = 3,
    STD_VIDEO_AV1_چوکاټ_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_چوکاټ_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_چوکاټ_Type;

تعريفنوع تعداد StdVideoAV1ReferenceName {
    STD_VIDEO_AV1_REFERENCE_NAME_INTRA_چوکاټ = 0,
    STD_VIDEO_AV1_REFERENCE_NAME_وروستی_چوکاټ = 1,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST2_چوکاټ = 2,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST3_چوکاټ = 3,
    STD_VIDEO_AV1_REFERENCE_NAME_GOLDEN_چوکاټ = 4,
    STD_VIDEO_AV1_REFERENCE_NAME_BWDREF_چوکاټ = 5,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF2_چوکاټ = 6,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF_چوکاټ = 7,
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

تعريفنوع تعداد Std_Video_AV1_Tx_ډېرپېښ {
    STD_VIDEO_AV1_TX_ډېرپېښ_ONLY_4_X4 = 0,
    STD_VIDEO_AV1_TX_ډېرپېښ_تر_ټولو_لوی = 1,
    STD_VIDEO_AV1_TX_ډېرپېښ_SELECT = 2,
    STD_VIDEO_AV1_TX_ډېرپېښ_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TX_ډېرپېښ_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_Tx_ډېرپېښ;

تعريفنوع تعداد Std_Video_AV1_چوکاټ_Restoration_Type {
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_NONE = 0,
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_WIENER = 1,
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_SGRPROJ = 2,
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_SWITCHABLE = 3,
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_چوکاټ_RESTORATION_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_چوکاټ_Restoration_Type;

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
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_خطي = 8,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100 = 9,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100_SQRT10 = 10,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_IEC_61966 = 11,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_1361 = 12,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SRGB = 13,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_10_بټ = 14,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_12_بټ = 15,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_2084 = 16,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_428 = 17,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_HLG = 18,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1TransferCharacteristics;

تعريفنوع تعداد Std_Video_AV1_ماتریکس_Coefficients {
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_بې_اغېزه_عنصر = 0,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_BT_709 = 1,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_RESERVED_3 = 3,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_FCC = 4,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_BT_470_B_G = 5,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_BT_601 = 6,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_SMPTE_240 = 7,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_SMPTE_YCGCO = 8,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_BT_2020_NCL = 9,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_BT_2020_CL = 10,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_SMPTE_2085 = 11,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_CHROMAT_NCL = 12,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_CHROMAT_CL = 13,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_ICTCP = 14,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_ماتریکس_COEFFICIENTS_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_ماتریکس_Coefficients;

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
    uint8_t                               بټ_ژوروالی;
    uint8_t                               subsampling_x;
    uint8_t                               subsampling_y;
    uint8_t                               reserved1;
    StdVideoAV1ColorPrimaries             color_primaries;
    StdVideoAV1TransferCharacteristics    transfer_characteristics;
    Std_Video_AV1_ماتریکس_Coefficients         ماتریکس_coefficients;
    StdVideoAV1ChromaSamplePosition       chroma_sample_position;
} StdVideoAV1ColorConfig;

تعريفنوع بنية StdVideoAV1TimingInfoFlags {
    uint32_t    equal_picture_interval : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TimingInfoFlags;

تعريفنوع بنية StdVideoAV1TimingInfo {
    StdVideoAV1TimingInfoFlags    flags;
    uint32_t                      عدد_units_دننه_display_tick;
    uint32_t                      وخت_scale;
    uint32_t                      عدد_ticks_فی_picture_minus_1;
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
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_AV1_ټول_REFS_فی_چوکاټ];
    uint8_t                       update_ډېرپېښ_delta;
    int8_t                        loop_filter_ډېرپېښ_deltas[STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS];
} StdVideoAV1LoopFilter;

تعريفنوع بنية StdVideoAV1QuantizationFlags {
    uint32_t    using_qmatrix : 1;
    uint32_t    diff_uv_delta : 1;
    uint32_t    reserved : 30;
} StdVideoAV1QuantizationFlags;

تعريفنوع بنية StdVideoAV1Quantization {
    StdVideoAV1QuantizationFlags    flags;
    uint8_t                         بنسټ_q_idx;
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
    uint32_t    یوشان_tile_spacing_flag : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TileInfoFlags;

تعريفنوع بنية StdVideoAV1TileInfo {
    StdVideoAV1TileInfoFlags    flags;
    uint8_t                     Tile_ستون_شمېر;
    uint8_t                     Tile_لیکې;
    uint16_t                    context_update_tile_id;
    uint8_t                     tile_اندازه_بایټونه_minus_1;
    uint8_t                     reserved1[7];
    ثابت uint16_t*             p_Mi_ستون_Starts;
    ثابت uint16_t*             p_Mi_لیکه_Starts;
    ثابت uint16_t*             p_پلنوالی_دننه_Sbs_Minus1;
    ثابت uint16_t*             p_لوړوالی_دننه_Sbs_Minus1;
} StdVideoAV1TileInfo;

تعريفنوع بنية StdVideoAV1CDEF {
    uint8_t    cdef_damping_minus_3;
    uint8_t    cdef_بټونه;
    uint8_t    cdef_y_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_y_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
} StdVideoAV1CDEF;

تعريفنوع بنية StdVideoAV1LoopRestoration {
    Std_Video_AV1_چوکاټ_Restoration_Type    چوکاټ_Restoration_Type[STD_VIDEO_AV1_MAX_عدد_PLANES];
    uint16_t                           Loop_Restoration_اندازه[STD_VIDEO_AV1_MAX_عدد_PLANES];
} StdVideoAV1LoopRestoration;

تعريفنوع بنية StdVideoAV1GlobalMotion {
    uint8_t    GmType[STD_VIDEO_AV1_عدد_REF_چوکاټونه];
    int32_t    gm_params[STD_VIDEO_AV1_عدد_REF_چوکاټونه][STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS];
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
    uint8_t                      ar_coeff_ښويدنه_minus_6;
    uint8_t                      grain_scale_ښويدنه;
    uint16_t                     grain_تخم;
    uint8_t                      film_grain_params_ref_idx;
    uint8_t                      عدد_y_points;
    uint8_t                      ټکی_y_ارزښت[STD_VIDEO_AV1_MAX_عدد_Y_POINTS];
    uint8_t                      ټکی_y_scaling[STD_VIDEO_AV1_MAX_عدد_Y_POINTS];
    uint8_t                      عدد_cb_points;
    uint8_t                      ټکی_cb_ارزښت[STD_VIDEO_AV1_MAX_عدد_CB_POINTS];
    uint8_t                      ټکی_cb_scaling[STD_VIDEO_AV1_MAX_عدد_CB_POINTS];
    uint8_t                      عدد_cr_points;
    uint8_t                      ټکی_cr_ارزښت[STD_VIDEO_AV1_MAX_عدد_CR_POINTS];
    uint8_t                      ټکی_cr_scaling[STD_VIDEO_AV1_MAX_عدد_CR_POINTS];
    int8_t                       ar_coeffs_y_plus_128[STD_VIDEO_AV1_MAX_عدد_POS_LUMA];
    int8_t                       ar_coeffs_cb_plus_128[STD_VIDEO_AV1_MAX_عدد_POS_CHROMA];
    int8_t                       ar_coeffs_cr_plus_128[STD_VIDEO_AV1_MAX_عدد_POS_CHROMA];
    uint8_t                      cb_mult;
    uint8_t                      cb_luma_mult;
    uint16_t                     cb_دننه_واټن;
    uint8_t                      cr_mult;
    uint8_t                      cr_luma_mult;
    uint16_t                     cr_دننه_واټن;
} StdVideoAV1FilmGrain;

تعريفنوع بنية Std_Video_AV1_Sequence_سرلیک_Flags {
    uint32_t    still_picture : 1;
    uint32_t    reduced_still_picture_سرلیک : 1;
    uint32_t    use_128x128_superblock : 1;
    uint32_t    enable_filter_intra : 1;
    uint32_t    enable_intra_څنډه_filter : 1;
    uint32_t    enable_interintra_compound : 1;
    uint32_t    enable_masked_compound : 1;
    uint32_t    enable_warped_motion : 1;
    uint32_t    enable_dual_filter : 1;
    uint32_t    enable_ترتیب_hint : 1;
    uint32_t    enable_jnt_comp : 1;
    uint32_t    enable_ref_چوکاټ_mvs : 1;
    uint32_t    چوکاټ_id_numbers_present_flag : 1;
    uint32_t    enable_superres : 1;
    uint32_t    enable_cdef : 1;
    uint32_t    enable_restoration : 1;
    uint32_t    film_grain_params_present : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    initial_display_delay_present_flag : 1;
    uint32_t    reserved : 13;
} Std_Video_AV1_Sequence_سرلیک_Flags;

تعريفنوع بنية Std_Video_AV1_Sequence_سرلیک {
    Std_Video_AV1_Sequence_سرلیک_Flags    flags;
    StdVideoAV1Profile                seq_profile;
    uint8_t                           چوکاټ_پلنوالی_بټونه_minus_1;
    uint8_t                           چوکاټ_لوړوالی_بټونه_minus_1;
    uint16_t                          max_چوکاټ_پلنوالی_minus_1;
    uint16_t                          max_چوکاټ_لوړوالی_minus_1;
    uint8_t                           delta_چوکاټ_id_اوږدتیا_minus_2;
    uint8_t                           additional_چوکاټ_id_اوږدتیا_minus_1;
    uint8_t                           ترتیب_hint_بټونه_minus_1;
    uint8_t                           seq_force_integer_mv;
    uint8_t                           seq_force_screen_content_tools;
    uint8_t                           reserved1[5];
    ثابت StdVideoAV1ColorConfig*     pColorConfig;
    ثابت StdVideoAV1TimingInfo*      pTimingInfo;
} Std_Video_AV1_Sequence_سرلیک;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
