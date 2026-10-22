#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_h265std_encode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

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
    int8_t                                delta_luma_وزن_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                luma_دننه_واټن_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                delta_chroma_وزن_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_دننه_واټن_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_وزن_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                luma_دننه_واټن_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    int8_t                                delta_chroma_وزن_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_دننه_واټن_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_وزن_جدول;

تعريفنوع بنية Std_Video_Encode_H265_ټوټه_Segment_سرلیک_Flags {
    uint32_t    لومړی_ټوټه_segment_دننه_pic_flag : 1;
    uint32_t    dependent_ټوټه_segment_flag : 1;
    uint32_t    ټوټه_sao_luma_flag : 1;
    uint32_t    ټوټه_sao_chroma_flag : 1;
    uint32_t    عدد_ref_idx_فعال_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_دننه_واټن_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ټوټه_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ټوټه_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ټوټه_Segment_سرلیک_Flags;

تعريفنوع بنية Std_Video_Encode_H265_ټوټه_Segment_سرلیک {
    Std_Video_Encode_H265_ټوټه_Segment_سرلیک_Flags    flags;
    Std_Video_H265_ټوټه_Type                        ټوټه_type;
    uint32_t                                     ټوټه_segment_پته;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_عدد_یوځای_Cand;
    int8_t                                       ټوټه_cb_qp_دننه_واټن;
    int8_t                                       ټوټه_cr_qp_دننه_واټن;
    int8_t                                       ټوټه_beta_دننه_واټن_div2;
    int8_t                                       ټوټه_tc_دننه_واټن_div2;
    int8_t                                       ټوټه_act_y_qp_دننه_واټن;
    int8_t                                       ټوټه_act_cb_qp_دننه_واټن;
    int8_t                                       ټوټه_act_cr_qp_دننه_واټن;
    int8_t                                       ټوټه_qp_delta;
    uint16_t                                     reserved1;
    ثابت Std_Video_Encode_H265_وزن_جدول*         p_وزن_جدول;
} Std_Video_Encode_H265_ټوټه_Segment_سرلیک;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      عدد_ref_idx_l0_فعال_minus1;
    uint8_t                                      عدد_ref_idx_l1_فعال_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      list_ثبت_l0[STD_VIDEO_H265_MAX_عدد_LIST_REF];
    uint8_t                                      list_ثبت_l1[STD_VIDEO_H265_MAX_عدد_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    کارول_شوی_for_long_غړی_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_د_مخکینی_pics_flag : 1;
    uint32_t    short_غړی_ref_pic_سېټ_sps_flag : 1;
    uint32_t    ټوټه_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

تعريفنوع بنية Std_Video_Encode_H265_Long_غړی_Ref_Pics {
    uint8_t     عدد_long_غړی_sps;
    uint8_t     عدد_long_غړی_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_غړی_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_غړی_PICS];
    uint16_t    کارول_شوی_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_دوره_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_غړی_Ref_Pics;

تعريفنوع بنية StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_سېټ_id;
    uint8_t                                        pps_seq_parameter_سېټ_id;
    uint8_t                                        pps_pic_parameter_سېټ_id;
    uint8_t                                        short_غړی_ref_pic_سېټ_idx;
    int32_t                                        Pic_ترتیب_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ثابت StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ثابت Std_Video_H265_Short_غړی_Ref_Pic_سېټ*          p_Short_غړی_Ref_Pic_سېټ;
    ثابت Std_Video_Encode_H265_Long_غړی_Ref_Pics*       p_Long_غړی_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    کارول_شوی_for_long_غړی_reference : 1;
    uint32_t    ناکارول_شوی_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ترتیب_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
