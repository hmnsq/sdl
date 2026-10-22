#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H264STD_H_
#परिभाषय VULKAN_VIDEO_CODEC_H264STD_H_ 1

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



// vulkan_video_codec_h264std is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h264std 1

#अन्तर्भाव "vulkan_video_codecs_common.h"

#परिभाषय STD_VIDEO_H264_CPB_CNT_LIST_आकार  32U
#परिभाषय STD_VIDEO_H264_SCALING_LIST_4_X4_अङ्कः_LISTS 6U
#परिभाषय STD_VIDEO_H264_SCALING_LIST_4_X4_अङ्कः_ELEMENTS 16U
#परिभाषय STD_VIDEO_H264_SCALING_LIST_8_X8_अङ्कः_LISTS 6U
#परिभाषय STD_VIDEO_H264_SCALING_LIST_8_X8_अङ्कः_ELEMENTS 64U
#परिभाषय STD_VIDEO_H264_MAX_अङ्कः_LIST_REF   32U
#परिभाषय STD_VIDEO_H264_MAX_CHROMA_PLANES  2U
#परिभाषय STD_VIDEO_H264_NO_REFERENCE_PICTURE 0xFFU

प्रकारनिर्देश गणना StdVideoH264ChromaFormatIdc {
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MONOCHROME = 0,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_420 = 1,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_422 = 2,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_444 = 3,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CHROMA_FORMAT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ChromaFormatIdc;

प्रकारनिर्देश गणना StdVideoH264ProfileIdc {
    STD_VIDEO_H264_PROFILE_IDC_BASELINE = 66,
    STD_VIDEO_H264_PROFILE_IDC_MAIN = 77,
    STD_VIDEO_H264_PROFILE_IDC_उच्चः = 100,
    STD_VIDEO_H264_PROFILE_IDC_उच्चः_10 = 110,
    STD_VIDEO_H264_PROFILE_IDC_उच्चः_422 = 122,
    STD_VIDEO_H264_PROFILE_IDC_उच्चः_444_PREDICTIVE = 244,
    STD_VIDEO_H264_PROFILE_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PROFILE_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264ProfileIdc;

प्रकारनिर्देश गणना StdVideoH264LevelIdc {
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

प्रकारनिर्देश गणना StdVideoH264PocType {
    STD_VIDEO_H264_POC_TYPE_0 = 0,
    STD_VIDEO_H264_POC_TYPE_1 = 1,
    STD_VIDEO_H264_POC_TYPE_2 = 2,
    STD_VIDEO_H264_POC_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_POC_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PocType;

प्रकारनिर्देश गणना Std_Video_H264_Aspect_अनुपातः_Idc {
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_UNSPECIFIED = 0,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_वर्गफलम् = 1,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_12_11 = 2,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_10_11 = 3,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_16_11 = 4,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_40_33 = 5,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_24_11 = 6,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_20_11 = 7,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_32_11 = 8,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_80_33 = 9,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_18_11 = 10,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_15_11 = 11,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_64_33 = 12,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_160_99 = 13,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_4_3 = 14,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_3_2 = 15,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_2_1 = 16,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_EXTENDED_SAR = 255,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_ASPECT_अनुपातः_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Aspect_अनुपातः_Idc;

प्रकारनिर्देश गणना StdVideoH264WeightedBipredIdc {
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT = 0,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_EXPLICIT = 1,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_IMPLICIT = 2,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264WeightedBipredIdc;

प्रकारनिर्देश गणना Std_Video_H264_Modification_सम्बन्धि_Pic_Nums_Idc {
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_SHORT_पदांशः_व्यवकलय = 0,
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_SHORT_पदांशः_सङ्कलय = 1,
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_LONG_पदांशः = 2,
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_अन्तः = 3,
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MODIFICATION_सम्बन्धि_PIC_NUMS_IDC_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_Modification_सम्बन्धि_Pic_Nums_Idc;

प्रकारनिर्देश गणना StdVideoH264MemMgmtControlOp {
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_अन्तः = 0,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_SHORT_पदांशः = 1,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_LONG_पदांशः = 2,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_LONG_पदांशः = 3,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_समुच्चयः_MAX_LONG_पदांशः_सूचकांक = 4,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_UNMARK_ALL = 5,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MARK_CURRENT_AS_LONG_पदांशः = 6,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_MEM_MGMT_CONTROL_OP_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264MemMgmtControlOp;

प्रकारनिर्देश गणना StdVideoH264CabacInitIdc {
    STD_VIDEO_H264_CABAC_INIT_IDC_0 = 0,
    STD_VIDEO_H264_CABAC_INIT_IDC_1 = 1,
    STD_VIDEO_H264_CABAC_INIT_IDC_2 = 2,
    STD_VIDEO_H264_CABAC_INIT_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_CABAC_INIT_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264CabacInitIdc;

प्रकारनिर्देश गणना StdVideoH264DisableDeblockingFilterIdc {
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_DISABLED = 0,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_ENABLED = 1,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_PARTIAL = 2,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_DISABLE_DEBLOCKING_FILTER_IDC_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264DisableDeblockingFilterIdc;

प्रकारनिर्देश गणना Std_Video_H264_खण्डिका_Type {
    STD_VIDEO_H264_खण्डिका_TYPE_P = 0,
    STD_VIDEO_H264_खण्डिका_TYPE_B = 1,
    STD_VIDEO_H264_खण्डिका_TYPE_I = 2,
    STD_VIDEO_H264_खण्डिका_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_खण्डिका_TYPE_MAX_ENUM = 0x7FFFFFFF
} Std_Video_H264_खण्डिका_Type;

प्रकारनिर्देश गणना StdVideoH264PictureType {
    STD_VIDEO_H264_PICTURE_TYPE_P = 0,
    STD_VIDEO_H264_PICTURE_TYPE_B = 1,
    STD_VIDEO_H264_PICTURE_TYPE_I = 2,
    STD_VIDEO_H264_PICTURE_TYPE_IDR = 5,
    STD_VIDEO_H264_PICTURE_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_PICTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264PictureType;

प्रकारनिर्देश गणना StdVideoH264NonVclNaluType {
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_SPS = 0,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PPS = 1,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_AUD = 2,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_उपसर्गः = 3,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_अन्तः_सम्बन्धि_SEQUENCE = 4,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_अन्तः_सम्बन्धि_प्रवाहः = 5,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_PRECODED = 6,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_INVALID = 0x7FFFFFFF,
    STD_VIDEO_H264_NON_VCL_NALU_TYPE_MAX_ENUM = 0x7FFFFFFF
} StdVideoH264NonVclNaluType;

प्रकारनिर्देश संरचना StdVideoH264SpsVuiFlags {
    uint32_t    aspect_अनुपातः_info_present_flag : 1;
    uint32_t    overscan_info_present_flag : 1;
    uint32_t    overscan_appropriate_flag : 1;
    uint32_t    video_signal_type_present_flag : 1;
    uint32_t    video_पूर्णम्_range_flag : 1;
    uint32_t    color_description_present_flag : 1;
    uint32_t    chroma_loc_info_present_flag : 1;
    uint32_t    timing_info_present_flag : 1;
    uint32_t    fixed_frame_दरः_flag : 1;
    uint32_t    bitstream_restriction_flag : 1;
    uint32_t    nal_hrd_parameters_present_flag : 1;
    uint32_t    vcl_hrd_parameters_present_flag : 1;
} StdVideoH264SpsVuiFlags;

प्रकारनिर्देश संरचना StdVideoH264HrdParameters {
    uint8_t     cpb_cnt_minus1;
    uint8_t     bit_दरः_scale;
    uint8_t     cpb_आकार_scale;
    uint8_t     reserved1;
    uint32_t    bit_दरः_मानम्_minus1[STD_VIDEO_H264_CPB_CNT_LIST_आकार];
    uint32_t    cpb_आकार_मानम्_minus1[STD_VIDEO_H264_CPB_CNT_LIST_आकार];
    uint8_t     cbr_flag[STD_VIDEO_H264_CPB_CNT_LIST_आकार];
    uint32_t    initial_cpb_removal_delay_दीर्घता_minus1;
    uint32_t    cpb_removal_delay_दीर्घता_minus1;
    uint32_t    dpb_output_delay_दीर्घता_minus1;
    uint32_t    time_विस्थापनम्_दीर्घता;
} StdVideoH264HrdParameters;

प्रकारनिर्देश संरचना Std_Video_H264_Sequence_Parameter_समुच्चयः_Vui {
    StdVideoH264SpsVuiFlags             flags;
    Std_Video_H264_Aspect_अनुपातः_Idc          aspect_अनुपातः_idc;
    uint16_t                            sar_विस्तारः;
    uint16_t                            sar_height;
    uint8_t                             video_format;
    uint8_t                             रङ्गः_primaries;
    uint8_t                             transfer_characteristics;
    uint8_t                             matrix_coefficients;
    uint32_t                            अङ्कः_units_अन्तर्_tick;
    uint32_t                            time_scale;
    uint8_t                             max_अङ्कः_reorder_चौकटाः;
    uint8_t                             max_dec_frame_buffering;
    uint8_t                             chroma_sample_loc_type_शिखरम्_क्षेत्रम्;
    uint8_t                             chroma_sample_loc_type_bottom_क्षेत्रम्;
    uint32_t                            reserved1;
    ध्रुव StdVideoH264HrdParameters*    pHrdParameters;
} Std_Video_H264_Sequence_Parameter_समुच्चयः_Vui;

प्रकारनिर्देश संरचना StdVideoH264SpsFlags {
    uint32_t    constraint_set0_flag : 1;
    uint32_t    constraint_set1_flag : 1;
    uint32_t    constraint_set2_flag : 1;
    uint32_t    constraint_set3_flag : 1;
    uint32_t    constraint_set4_flag : 1;
    uint32_t    constraint_set5_flag : 1;
    uint32_t    प्रत्यक्षम्_8x8_inference_flag : 1;
    uint32_t    mb_adaptive_frame_क्षेत्रम्_flag : 1;
    uint32_t    frame_mbs_only_flag : 1;
    uint32_t    delta_pic_क्रमः_always_zero_flag : 1;
    uint32_t    separate_रङ्गः_plane_flag : 1;
    uint32_t    gaps_अन्तर्_frame_अङ्कः_मानम्_allowed_flag : 1;
    uint32_t    qpprime_y_zero_transform_bypass_flag : 1;
    uint32_t    frame_cropping_flag : 1;
    uint32_t    seq_scaling_matrix_present_flag : 1;
    uint32_t    vui_parameters_present_flag : 1;
} StdVideoH264SpsFlags;

प्रकारनिर्देश संरचना StdVideoH264ScalingLists {
    uint16_t    scaling_list_present_आवरणम्;
    uint16_t    use_default_scaling_matrix_आवरणम्;
    uint8_t     ScalingList4x4[STD_VIDEO_H264_SCALING_LIST_4_X4_अङ्कः_LISTS][STD_VIDEO_H264_SCALING_LIST_4_X4_अङ्कः_ELEMENTS];
    uint8_t     ScalingList8x8[STD_VIDEO_H264_SCALING_LIST_8_X8_अङ्कः_LISTS][STD_VIDEO_H264_SCALING_LIST_8_X8_अङ्कः_ELEMENTS];
} StdVideoH264ScalingLists;

प्रकारनिर्देश संरचना Std_Video_H264_Sequence_Parameter_समुच्चयः {
    StdVideoH264SpsFlags                          flags;
    StdVideoH264ProfileIdc                        profile_idc;
    StdVideoH264LevelIdc                          level_idc;
    StdVideoH264ChromaFormatIdc                   chroma_format_idc;
    uint8_t                                       seq_parameter_समुच्चयः_id;
    uint8_t                                       bit_गभीरता_luma_minus8;
    uint8_t                                       bit_गभीरता_chroma_minus8;
    uint8_t                                       log2_max_frame_अङ्कः_minus4;
    StdVideoH264PocType                           pic_क्रमः_cnt_type;
    int32_t                                       विस्थापनम्_for_non_ref_pic;
    int32_t                                       विस्थापनम्_for_शिखरम्_गन्तव्यम्_bottom_क्षेत्रम्;
    uint8_t                                       log2_max_pic_क्रमः_cnt_lsb_minus4;
    uint8_t                                       अङ्कः_ref_चौकटाः_अन्तर्_pic_क्रमः_cnt_आवृत्तिः;
    uint8_t                                       max_अङ्कः_ref_चौकटाः;
    uint8_t                                       reserved1;
    uint32_t                                      pic_विस्तारः_अन्तर्_mbs_minus1;
    uint32_t                                      pic_height_अन्तर्_map_units_minus1;
    uint32_t                                      frame_crop_वामः_विस्थापनम्;
    uint32_t                                      frame_crop_दक्षिणः_विस्थापनम्;
    uint32_t                                      frame_crop_शिखरम्_विस्थापनम्;
    uint32_t                                      frame_crop_bottom_विस्थापनम्;
    uint32_t                                      reserved2;
    ध्रुव int32_t*                                p_विस्थापनम्_For_Ref_Frame;
    ध्रुव StdVideoH264ScalingLists*               pScalingLists;
    ध्रुव Std_Video_H264_Sequence_Parameter_समुच्चयः_Vui*    p_Sequence_Parameter_समुच्चयः_Vui;
} Std_Video_H264_Sequence_Parameter_समुच्चयः;

प्रकारनिर्देश संरचना StdVideoH264PpsFlags {
    uint32_t    transform_8x8_बहुलकम्_flag : 1;
    uint32_t    redundant_pic_cnt_present_flag : 1;
    uint32_t    constrained_intra_pred_flag : 1;
    uint32_t    deblocking_filter_control_present_flag : 1;
    uint32_t    weighted_pred_flag : 1;
    uint32_t    bottom_क्षेत्रम्_pic_क्रमः_अन्तर्_frame_present_flag : 1;
    uint32_t    entropy_coding_बहुलकम्_flag : 1;
    uint32_t    pic_scaling_matrix_present_flag : 1;
} StdVideoH264PpsFlags;

प्रकारनिर्देश संरचना Std_Video_H264_Picture_Parameter_समुच्चयः {
    StdVideoH264PpsFlags               flags;
    uint8_t                            seq_parameter_समुच्चयः_id;
    uint8_t                            pic_parameter_समुच्चयः_id;
    uint8_t                            अङ्कः_ref_idx_l0_default_सक्रिय_minus1;
    uint8_t                            अङ्कः_ref_idx_l1_default_सक्रिय_minus1;
    StdVideoH264WeightedBipredIdc      weighted_bipred_idc;
    int8_t                             pic_init_qp_minus26;
    int8_t                             pic_init_qs_minus26;
    int8_t                             chroma_qp_सूचकांक_विस्थापनम्;
    int8_t                             second_chroma_qp_सूचकांक_विस्थापनम्;
    ध्रुव StdVideoH264ScalingLists*    pScalingLists;
} Std_Video_H264_Picture_Parameter_समुच्चयः;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
