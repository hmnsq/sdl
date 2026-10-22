#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_h265std_encode 1

#ضمن "vulkan_video_codec_h265std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

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
    int8_t                                delta_luma_وزن_l0[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    int8_t                                luma_وٿي_l0[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    int8_t                                delta_chroma_وزن_l0[STD_VIDEO_H265_MAX_انگ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_وٿي_l0[STD_VIDEO_H265_MAX_انگ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_وزن_l1[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    int8_t                                luma_وٿي_l1[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    int8_t                                delta_chroma_وزن_l1[STD_VIDEO_H265_MAX_انگ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_وٿي_l1[STD_VIDEO_H265_MAX_انگ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_وزن_جدول;

تعريفنوع بنية Std_Video_Encode_H265_ٽڪرو_Segment_سرو_Flags {
    uint32_t    پهريون_ٽڪرو_segment_اندريون_pic_flag : 1;
    uint32_t    dependent_ٽڪرو_segment_flag : 1;
    uint32_t    ٽڪرو_sao_luma_flag : 1;
    uint32_t    ٽڪرو_sao_chroma_flag : 1;
    uint32_t    انگ_ref_idx_سرگرم_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_وٿي_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ٽڪرو_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ٽڪرو_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ٽڪرو_Segment_سرو_Flags;

تعريفنوع بنية Std_Video_Encode_H265_ٽڪرو_Segment_سرو {
    Std_Video_Encode_H265_ٽڪرو_Segment_سرو_Flags    flags;
    Std_Video_H265_ٽڪرو_Type                        ٽڪرو_type;
    uint32_t                                     ٽڪرو_segment_پتو;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_انگ_ملايو_Cand;
    int8_t                                       ٽڪرو_cb_qp_وٿي;
    int8_t                                       ٽڪرو_cr_qp_وٿي;
    int8_t                                       ٽڪرو_beta_وٿي_div2;
    int8_t                                       ٽڪرو_tc_وٿي_div2;
    int8_t                                       ٽڪرو_act_y_qp_وٿي;
    int8_t                                       ٽڪرو_act_cb_qp_وٿي;
    int8_t                                       ٽڪرو_act_cr_qp_وٿي;
    int8_t                                       ٽڪرو_qp_delta;
    uint16_t                                     reserved1;
    ثابت Std_Video_Encode_H265_وزن_جدول*         p_وزن_جدول;
} Std_Video_Encode_H265_ٽڪرو_Segment_سرو;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      انگ_ref_idx_l0_سرگرم_minus1;
    uint8_t                                      انگ_ref_idx_l1_سرگرم_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    uint8_t                                      list_داخلا_l0[STD_VIDEO_H265_MAX_انگ_LIST_REF];
    uint8_t                                      list_داخلا_l1[STD_VIDEO_H265_MAX_انگ_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    استعمال_ٿيل_for_long_رڪن_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_جو_اڳواٽ_pics_flag : 1;
    uint32_t    short_رڪن_ref_pic_سيٽ_sps_flag : 1;
    uint32_t    ٽڪرو_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

تعريفنوع بنية Std_Video_Encode_H265_Long_رڪن_Ref_Pics {
    uint8_t     انگ_long_رڪن_sps;
    uint8_t     انگ_long_رڪن_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_رڪن_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_رڪن_PICS];
    uint16_t    استعمال_ٿيل_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_چڪر_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_رڪن_Ref_Pics;

تعريفنوع بنية StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_سيٽ_id;
    uint8_t                                        pps_seq_parameter_سيٽ_id;
    uint8_t                                        pps_pic_parameter_سيٽ_id;
    uint8_t                                        short_رڪن_ref_pic_سيٽ_idx;
    int32_t                                        Pic_ترتيب_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ثابت StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ثابت Std_Video_H265_Short_رڪن_Ref_Pic_سيٽ*          p_Short_رڪن_Ref_Pic_سيٽ;
    ثابت Std_Video_Encode_H265_Long_رڪن_Ref_Pics*       p_Long_رڪن_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    استعمال_ٿيل_for_long_رڪن_reference : 1;
    uint32_t    اڻ_استعمال_ٿيل_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ترتيب_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
