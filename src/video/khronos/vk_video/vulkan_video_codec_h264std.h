#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H264STD_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h264std 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codecs_common.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_CPB_CNT_LIST_ਮਾਪ  32U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_SCALING_LIST_4_X4_ਅੰਕ_LISTS 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_SCALING_LIST_4_X4_ਅੰਕ_ELEMENTS 16U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_SCALING_LIST_8_X8_ਅੰਕ_LISTS 6U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_SCALING_LIST_8_X8_ਅੰਕ_ELEMENTS 64U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF   32U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_ਉੱਚਾ = 100,
    STD_VIDEO_H264_PROFILE_IDC_ਉੱਚਾ_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_ਉੱਚਾ_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_ਉੱਚਾ_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264LevelIdc {
    STD_VIDEO_H264_LEVEL_IDC_1_0 = 0,
    STD_VIDEO_H264_LEVEL_IDC_1_1 = 1,
    STD_VIDEO_H264_LEVEL_IDC_1_2 = 2,
    STD_VIDEO_H264_LEVEL_IDC_1_3 = 3,
    STD_VIDEO_H264_LEVEL_IDC_2_0 = 4,
    STD_VIDEO_H264_LEVEL_IDC_2_1 = 5,
    STD_VIDEO_H264_LEVEL_IDC_2_2 = 6,
    STD_VIDEO_H264_LEVEL_IDC_3_0 = 7,
    STD_VIDEO_H264_LEVEL_IDC_3_1 = 8,
    STD_VIDEO_H264_LEVEL_IDC_3_2 = 9,
    STD_VIDEO_H264_LEVEL_IDC_4_0 = 10,
    STD_VIDEO_H264_LEVEL_IDC_4_1 = 11,
    STD_VIDEO_H264_LEVEL_IDC_4_2 = 12,
    STD_VIDEO_H264_LEVEL_IDC_5_0 = 13,
    STD_VIDEO_H264_LEVEL_IDC_5_1 = 14,
    STD_VIDEO_H264_LEVEL_IDC_5_2 = 15,
    STD_VIDEO_H264_LEVEL_IDC_6_0 = 16,
    STD_VIDEO_H264_LEVEL_IDC_6_1 = 17,
    STD_VIDEO_H264_LEVEL_IDC_6_2 = 18,
    STD_VIDEO_H264_LEVEL_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_LEVEL_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264LevelIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_H264_Aspect_ਅਨੁਪਾਤ_Idc {
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_ਵਰਗਫਲ = 1,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_ਅਨੁਪਾਤ_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_ਅਨੁਪਾਤ_Idc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_H264_Modification_ਦਾ_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_SHORT_ਪਦ_ਘਟਾਓ = 0,
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_SHORT_ਪਦ_ਜੋੜੋ = 1,
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_LONG_ਪਦ = 2,
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_ਸਿਰਾ = 3,
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_ਦਾ_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_ਦਾ_Pic_Nums_Idc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_ਸਿਰਾ = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_ਪਦ = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_ਪਦ = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_ਪਦ = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_ਸੈੱਟ_MAX_LONG_ਪਦ_ਸੂਚਕਾਂਕ = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_ਪਦ = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_H264_ਟੁਕੜਾ_Type {
    STD_VIDEO_H264_ਟੁਕੜਾ_TYPE_P = 0,
    STD_VIDEO_H264_ਟੁਕੜਾ_TYPE_B = 1,
    STD_VIDEO_H264_ਟੁਕੜਾ_TYPE_I = 2,
    STD_VIDEO_H264_ਟੁਕੜਾ_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ਟੁਕੜਾ_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_ਟੁਕੜਾ_Type;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ਅਗੇਤਰ = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ਸਿਰਾ_ਦਾ_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_ਸਿਰਾ_ਦਾ_ਧਾਰਾ = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH264SpsVuiFlags {
    uint32_t    aspect_ਅਨੁਪਾਤ_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_ਭਰਿਆ_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_ਚੌਖਟਾ_ਦਰ_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਰ_scale;
    uint8_t     cpb_ਮਾਪ_scale;
    uint8_t     reserved1;
    uint32_t    ਦੋਆਧਾਰੀ_ਅੰਕ_ਦਰ_ਮੁੱਲ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    cpb_ਮਾਪ_ਮੁੱਲ_minus1[STD_VIDEO_H264_CPB_CNT_LIST_ਮਾਪ];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_ਮਾਪ];
    uint32_t    initial_cpb_removal_delay_ਲੰਮਾਈ_minus1;
    uint32_t    cpb_removal_delay_ਲੰਮਾਈ_minus1;
    uint32_t    dpb_output_delay_ਲੰਮਾਈ_minus1;
    uint32_t    ਸਮਾਂ_ਵਿੱਥ_ਲੰਮਾਈ;
} StdVideoH264HrdParameters;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H264_Sequence_Parameter_ਸੈੱਟ_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_ਅਨੁਪਾਤ_Idc          aspect_ਅਨੁਪਾਤ_idc;
    uint16_t                            sar_ਚੌੜਾਈ;
    uint16_t                            sar_ਉਚਾਈ;
    uint8_t                             video_format;
    uint8_t                             ਰੰਗ_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             ਮੈਟ੍ਰਿਕਸ_coefficients;
    uint32_t                            ਅੰਕ_units_ਵਿੱਚ_tick;
    uint32_t                            ਸਮਾਂ_scale;
    uint8_t                             max_ਅੰਕ_reorder_ਚੌਖਟੇ;
    uint8_t                             max_dec_ਚੌਖਟਾ_buffering;
    uint8_t                             chroma_sample_loc_type_ਸਿਖਰ_ਖੇਤਰ;
    uint8_t                             chroma_sample_loc_type_bottom_ਖੇਤਰ;
    uint32_t                            reserved1;
    ਅਚਲ StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_ਸੈੱਟ_Vui;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    ਸਿੱਧਾ_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_ਚੌਖਟਾ_ਖੇਤਰ_flag : 1;
    uint32_t    ਚੌਖਟਾ_mbs_only_flag : 1;
    uint32_t    delta_pic_ਕ੍ਰਮ_always_zero_flag : 1;
    uint32_t    separate_ਰੰਗ_plane_flag : 1;
    uint32_t    gaps_ਵਿੱਚ_ਚੌਖਟਾ_ਅੰਕ_ਮੁੱਲ_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    ਚੌਖਟਾ_cropping_flag : 1;
    uint32_t    seq_scaling_ਮੈਟ੍ਰਿਕਸ_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_ਨਕਾਬ;
    uint16_t    use_default_scaling_ਮੈਟ੍ਰਿਕਸ_ਨਕਾਬ;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_ਅੰਕ_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_ਅੰਕ_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_ਅੰਕ_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_ਅੰਕ_ELEMENTS];
} StdVideoH264ScalingLists;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H264_Sequence_Parameter_ਸੈੱਟ {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_ਸੈੱਟ_id;
    uint8_t                                       ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma_minus8;
    uint8_t                                       ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma_minus8;
    uint8_t                                       log2_max_ਚੌਖਟਾ_ਅੰਕ_minus4;
    StdVideoH264PocType                           pic_ਕ੍ਰਮ_cnt_type;
    int32_t                                       ਵਿੱਥ_for_non_ref_pic;
    int32_t                                       ਵਿੱਥ_for_ਸਿਖਰ_ਮੰਜ਼ਿਲ_bottom_ਖੇਤਰ;
    uint8_t                                       log2_max_pic_ਕ੍ਰਮ_cnt_lsb_minus4;
    uint8_t                                       ਅੰਕ_ref_ਚੌਖਟੇ_ਵਿੱਚ_pic_ਕ੍ਰਮ_cnt_ਚੱਕਰ;
    uint8_t                                       max_ਅੰਕ_ref_ਚੌਖਟੇ;
    uint8_t                                       reserved1;
    uint32_t                                      pic_ਚੌੜਾਈ_ਵਿੱਚ_mbs_minus1;
    uint32_t                                      pic_ਉਚਾਈ_ਵਿੱਚ_map_units_minus1;
    uint32_t                                      ਚੌਖਟਾ_crop_ਖੱਬਾ_ਵਿੱਥ;
    uint32_t                                      ਚੌਖਟਾ_crop_ਸੱਜਾ_ਵਿੱਥ;
    uint32_t                                      ਚੌਖਟਾ_crop_ਸਿਖਰ_ਵਿੱਥ;
    uint32_t                                      ਚੌਖਟਾ_crop_bottom_ਵਿੱਥ;
    uint32_t                                      reserved2;
    ਅਚਲ int32_t*                                p_ਵਿੱਥ_For_Ref_ਚੌਖਟਾ;
    ਅਚਲ StdVideoH264ScalingLists*               pScalingLists;
    ਅਚਲ Std_Video_H264_Sequence_Parameter_ਸੈੱਟ_Vui*    p_Sequence_Parameter_ਸੈੱਟ_Vui;
} Std_Video_H264_Sequence_Parameter_ਸੈੱਟ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoH264PpsFlags {
    uint32_t    transform_8x8_ਬਹੁਲਕ_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_ਖੇਤਰ_pic_ਕ੍ਰਮ_ਵਿੱਚ_ਚੌਖਟਾ_present_flag : 1;
    uint32_t    entropy_coding_ਬਹੁਲਕ_flag : 1;
    uint32_t    pic_scaling_ਮੈਟ੍ਰਿਕਸ_present_flag : 1;
} StdVideoH264PpsFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_H264_Picture_Parameter_ਸੈੱਟ {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_ਸੈੱਟ_id;
    uint8_t                            pic_parameter_ਸੈੱਟ_id;
    uint8_t                            ਅੰਕ_ref_idx_l0_default_ਸਰਗਰਮ_minus1;
    uint8_t                            ਅੰਕ_ref_idx_l1_default_ਸਰਗਰਮ_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_ਸੂਚਕਾਂਕ_ਵਿੱਥ;
    int8_t                             ਦੂਜਾ_chroma_qp_ਸੂਚਕਾਂਕ_ਵਿੱਥ;
    ਅਚਲ StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_ਸੈੱਟ;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
