#جے_بنا_تعریف VULKAN_VIDEO_CODEC_VP9STD_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_VP9STD_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// vulkan_video_codec_vp9std is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_vp9std 1

#ضمن "vulkan_video_codecs_common.h"

#تعریف_کرو STD_VIDEO_VP9_عدد_REF_چوکھٹے      8U
#تعریف_کرو STD_VIDEO_VP9_REFS_فی_چوکھٹا      3U
#تعریف_کرو STD_VIDEO_VP9_MAX_REF_چوکھٹے      4U
#تعریف_کرو STD_VIDEO_VP9_LOOP_FILTER_ADJUSTMENTS 2U
#تعریف_کرو STD_VIDEO_VP9_MAX_SEGMENTS        8U
#تعریف_کرو STD_VIDEO_VP9_SEG_LVL_MAX         4U
#تعریف_کرو STD_VIDEO_VP9_MAX_SEGMENTATION_درخت_PROBS 7U
#تعریف_کرو STD_VIDEO_VP9_MAX_SEGMENTATION_PRED_PROB 3U

تعريفنوع تعداد StdVideoVP9Profile {
    STD_VIDEO_VP9_PROFILE_0 = 0,
    STD_VIDEO_VP9_PROFILE_1 = 1,
    STD_VIDEO_VP9_PROFILE_2 = 2,
    STD_VIDEO_VP9_PROFILE_3 = 3,
    STD_VIDEO_VP9_PROFILE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_PROFILE_MAX_ENUM = 0x7FFFFFFF
} StdVideoVP9Profile;

تعريفنوع تعداد StdVideoVP9Level {
    STD_VIDEO_VP9_LEVEL_1_0 = 0,
    STD_VIDEO_VP9_LEVEL_1_1 = 1,
    STD_VIDEO_VP9_LEVEL_2_0 = 2,
    STD_VIDEO_VP9_LEVEL_2_1 = 3,
    STD_VIDEO_VP9_LEVEL_3_0 = 4,
    STD_VIDEO_VP9_LEVEL_3_1 = 5,
    STD_VIDEO_VP9_LEVEL_4_0 = 6,
    STD_VIDEO_VP9_LEVEL_4_1 = 7,
    STD_VIDEO_VP9_LEVEL_5_0 = 8,
    STD_VIDEO_VP9_LEVEL_5_1 = 9,
    STD_VIDEO_VP9_LEVEL_5_2 = 10,
    STD_VIDEO_VP9_LEVEL_6_0 = 11,
    STD_VIDEO_VP9_LEVEL_6_1 = 12,
    STD_VIDEO_VP9_LEVEL_6_2 = 13,
    STD_VIDEO_VP9_LEVEL_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_LEVEL_MAX_ENUM = 0x7FFFFFFF
} StdVideoVP9Level;

تعريفنوع تعداد Std_Video_VP9_چوکھٹا_Type {
    STD_VIDEO_VP9_چوکھٹا_TYPE_کلید = 0,
    STD_VIDEO_VP9_چوکھٹا_TYPE_NON_کلید = 1,
    STD_VIDEO_VP9_چوکھٹا_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_چوکھٹا_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_VP9_چوکھٹا_Type;

تعريفنوع تعداد StdVideoVP9ReferenceName {
    STD_VIDEO_VP9_REFERENCE_NAME_INTRA_چوکھٹا = 0,
    STD_VIDEO_VP9_REFERENCE_NAME_آخری_چوکھٹا = 1,
    STD_VIDEO_VP9_REFERENCE_NAME_GOLDEN_چوکھٹا = 2,
    STD_VIDEO_VP9_REFERENCE_NAME_ALTREF_چوکھٹا = 3,
    STD_VIDEO_VP9_REFERENCE_NAME_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_REFERENCE_NAME_MAX_ENUM = 0x7FFFFFFF
} StdVideoVP9ReferenceName;

تعريفنوع تعداد StdVideoVP9InterpolationFilter {
    STD_VIDEO_VP9_INTERPOLATION_FILTER_EIGHTTAP = 0,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_EIGHTTAP_SMOOTH = 1,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_EIGHTTAP_SHARP = 2,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_BILINEAR = 3,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_SWITCHABLE = 4,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_INTERPOLATION_FILTER_MAX_ENUM = 0x7FFFFFFF
} StdVideoVP9InterpolationFilter;

تعريفنوع تعداد StdVideoVP9ColorSpace {
    STD_VIDEO_VP9_COLOR_SPACE_UNKNOWN = 0,
    STD_VIDEO_VP9_COLOR_SPACE_BT_601 = 1,
    STD_VIDEO_VP9_COLOR_SPACE_BT_709 = 2,
    STD_VIDEO_VP9_COLOR_SPACE_SMPTE_170 = 3,
    STD_VIDEO_VP9_COLOR_SPACE_SMPTE_240 = 4,
    STD_VIDEO_VP9_COLOR_SPACE_BT_2020 = 5,
    STD_VIDEO_VP9_COLOR_SPACE_RESERVED = 6,
    STD_VIDEO_VP9_COLOR_SPACE_RGB = 7,
    STD_VIDEO_VP9_COLOR_SPACE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_VP9_COLOR_SPACE_MAX_ENUM = 0x7FFFFFFF
} StdVideoVP9ColorSpace;

تعريفنوع بنية StdVideoVP9ColorConfigFlags {
    uint32_t    color_range : 1;
    uint32_t    reserved : 31;
} StdVideoVP9ColorConfigFlags;

تعريفنوع بنية StdVideoVP9ColorConfig {
    StdVideoVP9ColorConfigFlags    flags;
    uint8_t                        ثنائی_ہندسہ_ڈونگھائی;
    uint8_t                        subsampling_x;
    uint8_t                        subsampling_y;
    uint8_t                        reserved1;
    StdVideoVP9ColorSpace          color_space;
} StdVideoVP9ColorConfig;

تعريفنوع بنية StdVideoVP9LoopFilterFlags {
    uint32_t    loop_filter_delta_enabled : 1;
    uint32_t    loop_filter_delta_update : 1;
    uint32_t    reserved : 30;
} StdVideoVP9LoopFilterFlags;

تعريفنوع بنية StdVideoVP9LoopFilter {
    StdVideoVP9LoopFilterFlags    flags;
    uint8_t                       loop_filter_level;
    uint8_t                       loop_filter_sharpness;
    uint8_t                       update_ref_delta;
    int8_t                        loop_filter_ref_deltas[STD_VIDEO_VP9_MAX_REF_چوکھٹے];
    uint8_t                       update_منوال_delta;
    int8_t                        loop_filter_منوال_deltas[STD_VIDEO_VP9_LOOP_FILTER_ADJUSTMENTS];
} StdVideoVP9LoopFilter;

تعريفنوع بنية StdVideoVP9SegmentationFlags {
    uint32_t    segmentation_update_map : 1;
    uint32_t    segmentation_temporal_update : 1;
    uint32_t    segmentation_update_انکڑے : 1;
    uint32_t    segmentation_abs_or_delta_update : 1;
    uint32_t    reserved : 28;
} StdVideoVP9SegmentationFlags;

تعريفنوع بنية StdVideoVP9Segmentation {
    StdVideoVP9SegmentationFlags    flags;
    uint8_t                         segmentation_درخت_probs[STD_VIDEO_VP9_MAX_SEGMENTATION_درخت_PROBS];
    uint8_t                         segmentation_pred_prob[STD_VIDEO_VP9_MAX_SEGMENTATION_PRED_PROB];
    uint8_t                         FeatureEnabled[STD_VIDEO_VP9_MAX_SEGMENTS];
    int16_t                         Feature_انکڑے[STD_VIDEO_VP9_MAX_SEGMENTS][STD_VIDEO_VP9_SEG_LVL_MAX];
} StdVideoVP9Segmentation;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
