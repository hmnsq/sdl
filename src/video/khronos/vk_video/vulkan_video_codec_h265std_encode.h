#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#تعریف_کن VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_h265std_encode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخه_1_0_0
#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

تعريفنوع بنية Std_Video_Encode_H265_وزن_جدول_Flags {
    uint16_t    luma_وزن_l0_flag;
    uint16_t    chroma_وزن_l0_flag;
    uint16_t    luma_وزن_l1_flag;
    uint16_t    chroma_وزن_l1_flag;
} Std_Video_Encode_H265_وزن_جدول_Flags;

تعريفنوع بنية Std_Video_Encode_H265_وزن_جدول {
    Std_Video_Encode_H265_وزن_جدول_Flags    flags;
    uint8_t                               luma_log2_وزن_denom;
    int8_t                                delta_chroma_log2_وزن_denom;
    int8_t                                delta_luma_وزن_l0[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    int8_t                                luma_جابه_جایی_l0[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    int8_t                                delta_chroma_وزن_l0[STD_VIDEO_H265_MAX_رقم_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_جابه_جایی_l0[STD_VIDEO_H265_MAX_رقم_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_وزن_l1[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    int8_t                                luma_جابه_جایی_l1[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    int8_t                                delta_chroma_وزن_l1[STD_VIDEO_H265_MAX_رقم_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_جابه_جایی_l1[STD_VIDEO_H265_MAX_رقم_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_وزن_جدول;

تعريفنوع بنية Std_Video_Encode_H265_برش_Segment_سرآیند_Flags {
    uint32_t    اولی_برش_segment_درون_pic_flag : 1;
    uint32_t    dependent_برش_segment_flag : 1;
    uint32_t    برش_sao_luma_flag : 1;
    uint32_t    برش_sao_chroma_flag : 1;
    uint32_t    رقم_ref_idx_فعال_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_جابه_جایی_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    برش_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    برش_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_برش_Segment_سرآیند_Flags;

تعريفنوع بنية Std_Video_Encode_H265_برش_Segment_سرآیند {
    Std_Video_Encode_H265_برش_Segment_سرآیند_Flags    flags;
    Std_Video_H265_برش_Type                        برش_type;
    uint32_t                                     برش_segment_آدرس;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_رقم_ادغام_Cand;
    int8_t                                       برش_cb_qp_جابه_جایی;
    int8_t                                       برش_cr_qp_جابه_جایی;
    int8_t                                       برش_beta_جابه_جایی_div2;
    int8_t                                       برش_tc_جابه_جایی_div2;
    int8_t                                       برش_act_y_qp_جابه_جایی;
    int8_t                                       برش_act_cb_qp_جابه_جایی;
    int8_t                                       برش_act_cr_qp_جابه_جایی;
    int8_t                                       برش_qp_delta;
    uint16_t                                     reserved1;
    ثابت Std_Video_Encode_H265_وزن_جدول*         p_وزن_جدول;
} Std_Video_Encode_H265_برش_Segment_سرآیند;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      رقم_ref_idx_l0_فعال_minus1;
    uint8_t                                      رقم_ref_idx_l1_فعال_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    uint8_t                                      list_مدخل_l0[STD_VIDEO_H265_MAX_رقم_LIST_REF];
    uint8_t                                      list_مدخل_l1[STD_VIDEO_H265_MAX_رقم_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    استفاده_شده_for_long_جمله_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_از_پیشین_pics_flag : 1;
    uint32_t    short_جمله_ref_pic_مجموعه_sps_flag : 1;
    uint32_t    برش_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

تعريفنوع بنية Std_Video_Encode_H265_Long_جمله_Ref_Pics {
    uint8_t     رقم_long_جمله_sps;
    uint8_t     رقم_long_جمله_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_جمله_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_جمله_PICS];
    uint16_t    استفاده_شده_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_چرخه_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_جمله_Ref_Pics;

تعريفنوع بنية StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_مجموعه_id;
    uint8_t                                        pps_seq_parameter_مجموعه_id;
    uint8_t                                        pps_pic_parameter_مجموعه_id;
    uint8_t                                        short_جمله_ref_pic_مجموعه_idx;
    int32_t                                        Pic_ترتیب_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ثابت StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ثابت Std_Video_H265_Short_جمله_Ref_Pic_مجموعه*          p_Short_جمله_Ref_Pic_مجموعه;
    ثابت Std_Video_Encode_H265_Long_جمله_Ref_Pics*       p_Long_جمله_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    استفاده_شده_for_long_جمله_reference : 1;
    uint32_t    استفادهنشده_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ترتیب_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
