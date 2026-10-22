#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h265std_encode 1

#अन्तर्भाव "vulkan_video_codec_h265std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

प्रकारनिर्देश संरचना Std_Video_Encode_H265_Weight_सारणी_Flags {
    uint16_t    luma_weight_l0_flag;
    uint16_t    chroma_weight_l0_flag;
    uint16_t    luma_weight_l1_flag;
    uint16_t    chroma_weight_l1_flag;
} Std_Video_Encode_H265_Weight_सारणी_Flags;

प्रकारनिर्देश संरचना Std_Video_Encode_H265_Weight_सारणी {
    Std_Video_Encode_H265_Weight_सारणी_Flags    flags;
    uint8_t                               luma_log2_weight_denom;
    int8_t                                delta_chroma_log2_weight_denom;
    int8_t                                delta_luma_weight_l0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    int8_t                                luma_विस्थापनम्_l0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    int8_t                                delta_chroma_weight_l0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_विस्थापनम्_l0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_weight_l1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    int8_t                                luma_विस्थापनम्_l1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    int8_t                                delta_chroma_weight_l1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_विस्थापनम्_l1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_Weight_सारणी;

प्रकारनिर्देश संरचना Std_Video_Encode_H265_खण्डिका_Segment_शीर्षकम्_Flags {
    uint32_t    first_खण्डिका_segment_अन्तर्_pic_flag : 1;
    uint32_t    dependent_खण्डिका_segment_flag : 1;
    uint32_t    खण्डिका_sao_luma_flag : 1;
    uint32_t    खण्डिका_sao_chroma_flag : 1;
    uint32_t    अङ्कः_ref_idx_सक्रिय_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_विस्थापनम्_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    खण्डिका_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    खण्डिका_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_खण्डिका_Segment_शीर्षकम्_Flags;

प्रकारनिर्देश संरचना Std_Video_Encode_H265_खण्डिका_Segment_शीर्षकम् {
    Std_Video_Encode_H265_खण्डिका_Segment_शीर्षकम्_Flags    flags;
    Std_Video_H265_खण्डिका_Type                        खण्डिका_type;
    uint32_t                                     खण्डिका_segment_स्थानाङ्कः;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_अङ्कः_Merge_Cand;
    int8_t                                       खण्डिका_cb_qp_विस्थापनम्;
    int8_t                                       खण्डिका_cr_qp_विस्थापनम्;
    int8_t                                       खण्डिका_beta_विस्थापनम्_div2;
    int8_t                                       खण्डिका_tc_विस्थापनम्_div2;
    int8_t                                       खण्डिका_act_y_qp_विस्थापनम्;
    int8_t                                       खण्डिका_act_cb_qp_विस्थापनम्;
    int8_t                                       खण्डिका_act_cr_qp_विस्थापनम्;
    int8_t                                       खण्डिका_qp_delta;
    uint16_t                                     reserved1;
    ध्रुव Std_Video_Encode_H265_Weight_सारणी*         p_Weight_सारणी;
} Std_Video_Encode_H265_खण्डिका_Segment_शीर्षकम्;

प्रकारनिर्देश संरचना StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      अङ्कः_ref_idx_l0_सक्रिय_minus1;
    uint8_t                                      अङ्कः_ref_idx_l1_सक्रिय_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    uint8_t                                      list_प्रविष्टिः_l0[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
    uint8_t                                      list_प्रविष्टिः_l1[STD_VIDEO_H265_MAX_अङ्कः_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

प्रकारनिर्देश संरचना StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    प्रयुक्तम्_for_long_पदांशः_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_सम्बन्धि_प्राक्_pics_flag : 1;
    uint32_t    short_पदांशः_ref_pic_समुच्चयः_sps_flag : 1;
    uint32_t    खण्डिका_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

प्रकारनिर्देश संरचना Std_Video_Encode_H265_Long_पदांशः_Ref_Pics {
    uint8_t     अङ्कः_long_पदांशः_sps;
    uint8_t     अङ्कः_long_पदांशः_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_पदांशः_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_पदांशः_PICS];
    uint16_t    प्रयुक्तम्_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_आवृत्तिः_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_पदांशः_Ref_Pics;

प्रकारनिर्देश संरचना StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_समुच्चयः_id;
    uint8_t                                        pps_seq_parameter_समुच्चयः_id;
    uint8_t                                        pps_pic_parameter_समुच्चयः_id;
    uint8_t                                        short_पदांशः_ref_pic_समुच्चयः_idx;
    int32_t                                        Pic_क्रमः_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ध्रुव StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ध्रुव Std_Video_H265_Short_पदांशः_Ref_Pic_समुच्चयः*          p_Short_पदांशः_Ref_Pic_समुच्चयः;
    ध्रुव Std_Video_Encode_H265_Long_पदांशः_Ref_Pics*       p_Long_पदांशः_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

प्रकारनिर्देश संरचना StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    प्रयुक्तम्_for_long_पदांशः_reference : 1;
    uint32_t    अप्रयुक्तम्_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_क्रमः_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
