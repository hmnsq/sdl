#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_AV1STD_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_AV1STD_H_ 1

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



// vulkan_video_codec_av1std is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_av1std 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codecs_common.h"

#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು      8U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_REFS_ಪ್ರತಿ_ಚೌಕಟ್ಟು      7U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_ಒಟ್ಟು_REFS_ಪ್ರತಿ_ಚೌಕಟ್ಟು 8U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_TILE_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ       64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_TILE_ಅಡ್ಡಸಾಲುಗಳು       64U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_SEGMENTS        8U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_SEG_LVL_MAX         8U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_PRIMARY_REF_NONE    7U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_SELECT_INTEGER_MV   2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_SELECT_SCREEN_CONTENT_TOOLS 2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_SKIP_ಬಹುಲಕ_ಚೌಕಟ್ಟುಗಳು    2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS 4U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS 2U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS 8U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_PLANES      3U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS 6U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_Y_POINTS    14U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_CB_POINTS   10U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_CR_POINTS   10U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_POS_LUMA    24U
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_AV1_MAX_ಅಂಕೆ_POS_CHROMA  25U

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1Profile {
    STD_VIDEO_AV1_PROFILE_MAIN = 0,
    STD_VIDEO_AV1_PROFILE_ಮೇಲಿನ = 1,
    STD_VIDEO_AV1_PROFILE_PROFESSIONAL = 2,
    STD_VIDEO_AV1_PROFILE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_PROFILE_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1Profile;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1Level {
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_AV1_ಚೌಕಟ್ಟು_Type {
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_ಕೀಲಿ = 0,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_INTER = 1,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_INTRA_ONLY = 2,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_SWITCH = 3,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_ಚೌಕಟ್ಟು_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1ReferenceName {
    STD_VIDEO_AV1_REFERENCE_NAME_INTRA_ಚೌಕಟ್ಟು = 0,
    STD_VIDEO_AV1_REFERENCE_NAME_ಕೊನೆಯ_ಚೌಕಟ್ಟು = 1,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST2_ಚೌಕಟ್ಟು = 2,
    STD_VIDEO_AV1_REFERENCE_NAME_LAST3_ಚೌಕಟ್ಟು = 3,
    STD_VIDEO_AV1_REFERENCE_NAME_GOLDEN_ಚೌಕಟ್ಟು = 4,
    STD_VIDEO_AV1_REFERENCE_NAME_BWDREF_ಚೌಕಟ್ಟು = 5,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF2_ಚೌಕಟ್ಟು = 6,
    STD_VIDEO_AV1_REFERENCE_NAME_ALTREF_ಚೌಕಟ್ಟು = 7,
    STD_VIDEO_AV1_REFERENCE_NAME_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_REFERENCE_NAME_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ReferenceName;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1InterpolationFilter {
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP = 0,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SMOOTH = 1,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_EIGHTTAP_SHARP = 2,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_BILINEAR = 3,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_SWITCHABLE = 4,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_INTERPOLATION_FILTER_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1InterpolationFilter;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_AV1_Tx_ಬಹುಲಕ {
    STD_VIDEO_AV1_TX_ಬಹುಲಕ_ONLY_4_X4 = 0,
    STD_VIDEO_AV1_TX_ಬಹುಲಕ_ಅತಿದೊಡ್ಡ = 1,
    STD_VIDEO_AV1_TX_ಬಹುಲಕ_SELECT = 2,
    STD_VIDEO_AV1_TX_ಬಹುಲಕ_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TX_ಬಹುಲಕ_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_Tx_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_AV1_ಚೌಕಟ್ಟು_Restoration_Type {
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_NONE = 0,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_WIENER = 1,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_SGRPROJ = 2,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_SWITCHABLE = 3,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_ಚೌಕಟ್ಟು_RESTORATION_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_ಚೌಕಟ್ಟು_Restoration_Type;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1ColorPrimaries {
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1TransferCharacteristics {
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_0 = 0,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_709 = 1,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_RESERVED_3 = 3,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_M = 4,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_470_B_G = 5,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_601 = 6,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_240 = 7,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_ರೇಖೀಯ = 8,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100 = 9,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_LOG_100_SQRT10 = 10,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_IEC_61966 = 11,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_1361 = 12,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SRGB = 13,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_10_ಬಿಟ್ = 14,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_BT_2020_12_ಬಿಟ್ = 15,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_2084 = 16,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_SMPTE_428 = 17,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_HLG = 18,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_TRANSFER_CHARACTERISTICS_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1TransferCharacteristics;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_AV1_ಮಾತೃಕೆ_Coefficients {
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_ತಟಸ್ಥ = 0,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_BT_709 = 1,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_UNSPECIFIED = 2,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_RESERVED_3 = 3,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_FCC = 4,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_BT_470_B_G = 5,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_BT_601 = 6,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_SMPTE_240 = 7,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_SMPTE_YCGCO = 8,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_BT_2020_NCL = 9,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_BT_2020_CL = 10,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_SMPTE_2085 = 11,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_CHROMAT_NCL = 12,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_CHROMAT_CL = 13,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_ICTCP = 14,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_ಮಾತೃಕೆ_COEFFICIENTS_MAX_ENUM = 0x7FFFFFFF
} Std_Video_AV1_ಮಾತೃಕೆ_Coefficients;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ StdVideoAV1ChromaSamplePosition {
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_UNKNOWN = 0,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_VERTICAL = 1,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_COLOCATED = 2,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_RESERVED = 3,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_INVALID = 0x7FFFFFFF,
    STD_VIDEO_AV1_CHROMA_SAMPLE_POSITION_MAX_ENUM = 0x7FFFFFFF
} StdVideoAV1ChromaSamplePosition;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1ColorConfigFlags {
    uint32_t    mono_chrome : 1;
    uint32_t    color_range : 1;
    uint32_t    separate_uv_delta_q : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    reserved : 28;
} StdVideoAV1ColorConfigFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1ColorConfig {
    StdVideoAV1ColorConfigFlags           flags;
    uint8_t                               ಬಿಟ್_ಆಳ;
    uint8_t                               subsampling_x;
    uint8_t                               subsampling_y;
    uint8_t                               reserved1;
    StdVideoAV1ColorPrimaries             color_primaries;
    StdVideoAV1TransferCharacteristics    transfer_characteristics;
    Std_Video_AV1_ಮಾತೃಕೆ_Coefficients         ಮಾತೃಕೆ_coefficients;
    StdVideoAV1ChromaSamplePosition       chroma_sample_position;
} StdVideoAV1ColorConfig;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1TimingInfoFlags {
    uint32_t    equal_picture_interval : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TimingInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1TimingInfo {
    StdVideoAV1TimingInfoFlags    flags;
    uint32_t                      ಅಂಕೆ_units_ಒಳ_display_tick;
    uint32_t                      ಸಮಯ_scale;
    uint32_t                      ಅಂಕೆ_ticks_ಪ್ರತಿ_picture_minus_1;
} StdVideoAV1TimingInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1LoopFilterFlags {
    uint32_t    loop_filter_delta_enabled : 1;
    uint32_t    loop_filter_delta_update : 1;
    uint32_t    reserved : 30;
} StdVideoAV1LoopFilterFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1LoopFilter {
    StdVideoAV1LoopFilterFlags    flags;
    uint8_t                       loop_filter_level[STD_VIDEO_AV1_MAX_LOOP_FILTER_STRENGTHS];
    uint8_t                       loop_filter_sharpness;
    uint8_t                       update_ref_delta;
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_AV1_ಒಟ್ಟು_REFS_ಪ್ರತಿ_ಚೌಕಟ್ಟು];
    uint8_t                       update_ಬಹುಲಕ_delta;
    int8_t                        loop_filter_ಬಹುಲಕ_deltas[STD_VIDEO_AV1_LOOP_FILTER_ADJUSTMENTS];
} StdVideoAV1LoopFilter;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1QuantizationFlags {
    uint32_t    using_qmatrix : 1;
    uint32_t    diff_uv_delta : 1;
    uint32_t    reserved : 30;
} StdVideoAV1QuantizationFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1Quantization {
    StdVideoAV1QuantizationFlags    flags;
    uint8_t                         ತಳ_q_idx;
    int8_t                          DeltaQYDc;
    int8_t                          DeltaQUDc;
    int8_t                          DeltaQUAc;
    int8_t                          DeltaQVDc;
    int8_t                          DeltaQVAc;
    uint8_t                         qm_y;
    uint8_t                         qm_u;
    uint8_t                         qm_v;
} StdVideoAV1Quantization;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1Segmentation {
    uint8_t    FeatureEnabled[STD_VIDEO_AV1_MAX_SEGMENTS];
    int16_t    Feature_ದತ್ತಾಂಶ[STD_VIDEO_AV1_MAX_SEGMENTS][STD_VIDEO_AV1_SEG_LVL_MAX];
} StdVideoAV1Segmentation;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1TileInfoFlags {
    uint32_t    ಏಕರೂಪ_tile_spacing_flag : 1;
    uint32_t    reserved : 31;
} StdVideoAV1TileInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1TileInfo {
    StdVideoAV1TileInfoFlags    flags;
    uint8_t                     Tile_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;
    uint8_t                     Tile_ಅಡ್ಡಸಾಲುಗಳು;
    uint16_t                    context_update_tile_id;
    uint8_t                     tile_ಗಾತ್ರ_ಬೈಟುಗಳು_minus_1;
    uint8_t                     reserved1[7];
    ಸ್ಥಿರಾಂಕ uint16_t*             p_Mi_ಲಂಬಸಾಲು_Starts;
    ಸ್ಥಿರಾಂಕ uint16_t*             p_Mi_ಅಡ್ಡಸಾಲು_Starts;
    ಸ್ಥಿರಾಂಕ uint16_t*             p_ಅಗಲ_ಒಳ_Sbs_Minus1;
    ಸ್ಥಿರಾಂಕ uint16_t*             p_ಎತ್ತರ_ಒಳ_Sbs_Minus1;
} StdVideoAV1TileInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1CDEF {
    uint8_t    cdef_damping_minus_3;
    uint8_t    cdef_ಬಿಟ್ಟುಗಳು;
    uint8_t    cdef_y_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_y_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_pri_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
    uint8_t    cdef_uv_sec_strength[STD_VIDEO_AV1_MAX_CDEF_FILTER_STRENGTHS];
} StdVideoAV1CDEF;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1LoopRestoration {
    Std_Video_AV1_ಚೌಕಟ್ಟು_Restoration_Type    ಚೌಕಟ್ಟು_Restoration_Type[STD_VIDEO_AV1_MAX_ಅಂಕೆ_PLANES];
    uint16_t                           Loop_Restoration_ಗಾತ್ರ[STD_VIDEO_AV1_MAX_ಅಂಕೆ_PLANES];
} StdVideoAV1LoopRestoration;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1GlobalMotion {
    uint8_t    GmType[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು];
    int32_t    gm_params[STD_VIDEO_AV1_ಅಂಕೆ_REF_ಚೌಕಟ್ಟುಗಳು][STD_VIDEO_AV1_GLOBAL_MOTION_PARAMS];
} StdVideoAV1GlobalMotion;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1FilmGrainFlags {
    uint32_t    chroma_scaling_from_luma : 1;
    uint32_t    overlap_flag : 1;
    uint32_t    clip_ಗಮ್ಯ_restricted_range : 1;
    uint32_t    update_grain : 1;
    uint32_t    reserved : 28;
} StdVideoAV1FilmGrainFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoAV1FilmGrain {
    StdVideoAV1FilmGrainFlags    flags;
    uint8_t                      grain_scaling_minus_8;
    uint8_t                      ar_coeff_lag;
    uint8_t                      ar_coeff_ಸರಿಸು_minus_6;
    uint8_t                      grain_scale_ಸರಿಸು;
    uint16_t                     grain_ಬೀಜ;
    uint8_t                      film_grain_params_ref_idx;
    uint8_t                      ಅಂಕೆ_y_points;
    uint8_t                      ಬಿಂದು_y_ಮೌಲ್ಯ[STD_VIDEO_AV1_MAX_ಅಂಕೆ_Y_POINTS];
    uint8_t                      ಬಿಂದು_y_scaling[STD_VIDEO_AV1_MAX_ಅಂಕೆ_Y_POINTS];
    uint8_t                      ಅಂಕೆ_cb_points;
    uint8_t                      ಬಿಂದು_cb_ಮೌಲ್ಯ[STD_VIDEO_AV1_MAX_ಅಂಕೆ_CB_POINTS];
    uint8_t                      ಬಿಂದು_cb_scaling[STD_VIDEO_AV1_MAX_ಅಂಕೆ_CB_POINTS];
    uint8_t                      ಅಂಕೆ_cr_points;
    uint8_t                      ಬಿಂದು_cr_ಮೌಲ್ಯ[STD_VIDEO_AV1_MAX_ಅಂಕೆ_CR_POINTS];
    uint8_t                      ಬಿಂದು_cr_scaling[STD_VIDEO_AV1_MAX_ಅಂಕೆ_CR_POINTS];
    int8_t                       ar_coeffs_y_plus_128[STD_VIDEO_AV1_MAX_ಅಂಕೆ_POS_LUMA];
    int8_t                       ar_coeffs_cb_plus_128[STD_VIDEO_AV1_MAX_ಅಂಕೆ_POS_CHROMA];
    int8_t                       ar_coeffs_cr_plus_128[STD_VIDEO_AV1_MAX_ಅಂಕೆ_POS_CHROMA];
    uint8_t                      cb_mult;
    uint8_t                      cb_luma_mult;
    uint16_t                     cb_ಸ್ಥಾನಾಂತರ;
    uint8_t                      cr_mult;
    uint8_t                      cr_luma_mult;
    uint16_t                     cr_ಸ್ಥಾನಾಂತರ;
} StdVideoAV1FilmGrain;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_AV1_Sequence_ಶೀರ್ಷಿಕೆ_Flags {
    uint32_t    still_picture : 1;
    uint32_t    reduced_still_picture_ಶೀರ್ಷಿಕೆ : 1;
    uint32_t    use_128x128_superblock : 1;
    uint32_t    enable_filter_intra : 1;
    uint32_t    enable_intra_ಅಂಚು_filter : 1;
    uint32_t    enable_interintra_compound : 1;
    uint32_t    enable_masked_compound : 1;
    uint32_t    enable_warped_motion : 1;
    uint32_t    enable_dual_filter : 1;
    uint32_t    enable_ಕ್ರಮ_hint : 1;
    uint32_t    enable_jnt_comp : 1;
    uint32_t    enable_ref_ಚೌಕಟ್ಟು_mvs : 1;
    uint32_t    ಚೌಕಟ್ಟು_id_numbers_present_flag : 1;
    uint32_t    enable_superres : 1;
    uint32_t    enable_cdef : 1;
    uint32_t    enable_restoration : 1;
    uint32_t    film_grain_params_present : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    initial_display_delay_present_flag : 1;
    uint32_t    reserved : 13;
} Std_Video_AV1_Sequence_ಶೀರ್ಷಿಕೆ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_AV1_Sequence_ಶೀರ್ಷಿಕೆ {
    Std_Video_AV1_Sequence_ಶೀರ್ಷಿಕೆ_Flags    flags;
    StdVideoAV1Profile                seq_profile;
    uint8_t                           ಚೌಕಟ್ಟು_ಅಗಲ_ಬಿಟ್ಟುಗಳು_minus_1;
    uint8_t                           ಚೌಕಟ್ಟು_ಎತ್ತರ_ಬಿಟ್ಟುಗಳು_minus_1;
    uint16_t                          max_ಚೌಕಟ್ಟು_ಅಗಲ_minus_1;
    uint16_t                          max_ಚೌಕಟ್ಟು_ಎತ್ತರ_minus_1;
    uint8_t                           delta_ಚೌಕಟ್ಟು_id_ಉದ್ದಳತೆ_minus_2;
    uint8_t                           additional_ಚೌಕಟ್ಟು_id_ಉದ್ದಳತೆ_minus_1;
    uint8_t                           ಕ್ರಮ_hint_ಬಿಟ್ಟುಗಳು_minus_1;
    uint8_t                           seq_force_integer_mv;
    uint8_t                           seq_force_screen_content_tools;
    uint8_t                           reserved1[5];
    ಸ್ಥಿರಾಂಕ StdVideoAV1ColorConfig*     pColorConfig;
    ಸ್ಥಿರಾಂಕ StdVideoAV1TimingInfo*      pTimingInfo;
} Std_Video_AV1_Sequence_ಶೀರ್ಷಿಕೆ;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
