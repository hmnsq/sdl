#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h265std_encode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_h265std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ_Flags {
    uint16_t    luma_ਭਾਰ_l0_flag;
    uint16_t    chroma_ਭਾਰ_l0_flag;
    uint16_t    luma_ਭਾਰ_l1_flag;
    uint16_t    chroma_ਭਾਰ_l1_flag;
} Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ {
    Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ_Flags    flags;
    uint8_t                               luma_log2_ਭਾਰ_denom;
    int8_t                                delta_chroma_log2_ਭਾਰ_denom;
    int8_t                                delta_luma_ਭਾਰ_l0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    int8_t                                luma_ਵਿੱਥ_l0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    int8_t                                delta_chroma_ਭਾਰ_l0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_ਵਿੱਥ_l0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_ਭਾਰ_l1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    int8_t                                luma_ਵਿੱਥ_l1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    int8_t                                delta_chroma_ਭਾਰ_l1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_ਵਿੱਥ_l1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H265_ਟੁਕੜਾ_Segment_ਸਿਰਲੇਖ_Flags {
    uint32_t    ਪਹਿਲਾ_ਟੁਕੜਾ_segment_ਵਿੱਚ_pic_flag : 1;
    uint32_t    dependent_ਟੁਕੜਾ_segment_flag : 1;
    uint32_t    ਟੁਕੜਾ_sao_luma_flag : 1;
    uint32_t    ਟੁਕੜਾ_sao_chroma_flag : 1;
    uint32_t    ਅੰਕ_ref_idx_ਸਰਗਰਮ_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_ਵਿੱਥ_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ਟੁਕੜਾ_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ਟੁਕੜਾ_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ਟੁਕੜਾ_Segment_ਸਿਰਲੇਖ_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H265_ਟੁਕੜਾ_Segment_ਸਿਰਲੇਖ {
    Std_Video_Encode_H265_ਟੁਕੜਾ_Segment_ਸਿਰਲੇਖ_Flags    flags;
    Std_Video_H265_ਟੁਕੜਾ_Type                        ਟੁਕੜਾ_type;
    uint32_t                                     ਟੁਕੜਾ_segment_ਪਤਾ;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_ਅੰਕ_ਮਿਲਾਓ_Cand;
    int8_t                                       ਟੁਕੜਾ_cb_qp_ਵਿੱਥ;
    int8_t                                       ਟੁਕੜਾ_cr_qp_ਵਿੱਥ;
    int8_t                                       ਟੁਕੜਾ_beta_ਵਿੱਥ_div2;
    int8_t                                       ਟੁਕੜਾ_tc_ਵਿੱਥ_div2;
    int8_t                                       ਟੁਕੜਾ_act_y_qp_ਵਿੱਥ;
    int8_t                                       ਟੁਕੜਾ_act_cb_qp_ਵਿੱਥ;
    int8_t                                       ਟੁਕੜਾ_act_cr_qp_ਵਿੱਥ;
    int8_t                                       ਟੁਕੜਾ_qp_delta;
    uint16_t                                     reserved1;
    ਅਚਲ Std_Video_Encode_H265_ਭਾਰ_ਸਾਰਣੀ*         p_ਭਾਰ_ਸਾਰਣੀ;
} Std_Video_Encode_H265_ਟੁਕੜਾ_Segment_ਸਿਰਲੇਖ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      ਅੰਕ_ref_idx_l0_ਸਰਗਰਮ_minus1;
    uint8_t                                      ਅੰਕ_ref_idx_l1_ਸਰਗਰਮ_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    uint8_t                                      list_ਇੰਦਰਾਜ_l0[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
    uint8_t                                      list_ਇੰਦਰਾਜ_l1[STD_VIDEO_H265_MAX_ਅੰਕ_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    ਵਰਤਿਆ_for_long_ਪਦ_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_ਦਾ_ਪੂਰਵ_pics_flag : 1;
    uint32_t    short_ਪਦ_ref_pic_ਸੈੱਟ_sps_flag : 1;
    uint32_t    ਟੁਕੜਾ_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H265_Long_ਪਦ_Ref_Pics {
    uint8_t     ਅੰਕ_long_ਪਦ_sps;
    uint8_t     ਅੰਕ_long_ਪਦ_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_ਪਦ_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_ਪਦ_PICS];
    uint16_t    ਵਰਤਿਆ_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_ਚੱਕਰ_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_ਪਦ_Ref_Pics;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_ਸੈੱਟ_id;
    uint8_t                                        pps_seq_parameter_ਸੈੱਟ_id;
    uint8_t                                        pps_pic_parameter_ਸੈੱਟ_id;
    uint8_t                                        short_ਪਦ_ref_pic_ਸੈੱਟ_idx;
    int32_t                                        Pic_ਕ੍ਰਮ_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ਅਚਲ StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ਅਚਲ Std_Video_H265_Short_ਪਦ_Ref_Pic_ਸੈੱਟ*          p_Short_ਪਦ_Ref_Pic_ਸੈੱਟ;
    ਅਚਲ Std_Video_Encode_H265_Long_ਪਦ_Ref_Pics*       p_Long_ਪਦ_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    ਵਰਤਿਆ_for_long_ਪਦ_reference : 1;
    uint32_t    ਅਣਵਰਤਿਆ_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ਕ੍ਰਮ_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
