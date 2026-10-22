#جے_بنا_تعریف VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h265std_encode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

تعريفنوع بنية Std_Video_Encode_H265_بھار_جدول_Flags {
    uint16_t    luma_بھار_l0_flag;
    uint16_t    chroma_بھار_l0_flag;
    uint16_t    luma_بھار_l1_flag;
    uint16_t    chroma_بھار_l1_flag;
} Std_Video_Encode_H265_بھار_جدول_Flags;

تعريفنوع بنية Std_Video_Encode_H265_بھار_جدول {
    Std_Video_Encode_H265_بھار_جدول_Flags    flags;
    uint8_t                               luma_log2_بھار_denom;
    int8_t                                delta_chroma_log2_بھار_denom;
    int8_t                                delta_luma_بھار_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                luma_وتھ_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                delta_chroma_بھار_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_وتھ_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_بھار_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                luma_وتھ_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                delta_chroma_بھار_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_وتھ_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_بھار_جدول;

تعريفنوع بنية Std_Video_Encode_H265_ٹکڑا_Segment_سرخی_Flags {
    uint32_t    پہلا_ٹکڑا_segment_وچ_pic_flag : 1;
    uint32_t    dependent_ٹکڑا_segment_flag : 1;
    uint32_t    ٹکڑا_sao_luma_flag : 1;
    uint32_t    ٹکڑا_sao_chroma_flag : 1;
    uint32_t    عدد_ref_idx_سرگرم_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_وتھ_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ٹکڑا_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ٹکڑا_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ٹکڑا_Segment_سرخی_Flags;

تعريفنوع بنية Std_Video_Encode_H265_ٹکڑا_Segment_سرخی {
    Std_Video_Encode_H265_ٹکڑا_Segment_سرخی_Flags    flags;
    Std_Video_H265_ٹکڑا_Type                        ٹکڑا_type;
    uint32_t                                     ٹکڑا_segment_پتہ;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_عدد_ملاؤ_Cand;
    int8_t                                       ٹکڑا_cb_qp_وتھ;
    int8_t                                       ٹکڑا_cr_qp_وتھ;
    int8_t                                       ٹکڑا_beta_وتھ_div2;
    int8_t                                       ٹکڑا_tc_وتھ_div2;
    int8_t                                       ٹکڑا_act_y_qp_وتھ;
    int8_t                                       ٹکڑا_act_cb_qp_وتھ;
    int8_t                                       ٹکڑا_act_cr_qp_وتھ;
    int8_t                                       ٹکڑا_qp_delta;
    uint16_t                                     reserved1;
    ثابت Std_Video_Encode_H265_بھار_جدول*         p_بھار_جدول;
} Std_Video_Encode_H265_ٹکڑا_Segment_سرخی;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      عدد_ref_idx_l0_سرگرم_minus1;
    uint8_t                                      عدد_ref_idx_l1_سرگرم_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      list_اندراج_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      list_اندراج_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    ورتیا_for_long_رکن_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_دا_پہلوں_pics_flag : 1;
    uint32_t    short_رکن_ref_pic_سیٹ_sps_flag : 1;
    uint32_t    ٹکڑا_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

تعريفنوع بنية Std_Video_Encode_H265_Long_رکن_Ref_Pics {
    uint8_t     عدد_long_رکن_sps;
    uint8_t     عدد_long_رکن_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_رکن_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_رکن_PICS];
    uint16_t    ورتیا_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_چکر_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_رکن_Ref_Pics;

تعريفنوع بنية StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_سیٹ_id;
    uint8_t                                        pps_seq_parameter_سیٹ_id;
    uint8_t                                        pps_pic_parameter_سیٹ_id;
    uint8_t                                        short_رکن_ref_pic_سیٹ_idx;
    int32_t                                        Pic_ترتیب_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ثابت StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ثابت Std_Video_H265_Short_رکن_Ref_Pic_سیٹ*          p_Short_رکن_Ref_Pic_سیٹ;
    ثابت Std_Video_Encode_H265_Long_رکن_Ref_Pics*       p_Long_رکن_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    ورتیا_for_long_رکن_reference : 1;
    uint32_t    بن_ورتیا_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ترتیب_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
