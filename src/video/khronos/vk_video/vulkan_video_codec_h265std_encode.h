#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H265STD_ENCODE_H_ 1

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



// vulkan_video_codec_h265std_encode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h265std_encode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_h265std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_encode"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ_Flags {
    uint16_t    luma_ತೂಕ_l0_flag;
    uint16_t    chroma_ತೂಕ_l0_flag;
    uint16_t    luma_ತೂಕ_l1_flag;
    uint16_t    chroma_ತೂಕ_l1_flag;
} Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ {
    Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ_Flags    flags;
    uint8_t                               luma_log2_ತೂಕ_denom;
    int8_t                                delta_chroma_log2_ತೂಕ_denom;
    int8_t                                delta_luma_ತೂಕ_l0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                luma_ಸ್ಥಾನಾಂತರ_l0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                delta_chroma_ತೂಕ_l0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_ಸ್ಥಾನಾಂತರ_l0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_luma_ತೂಕ_l1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                luma_ಸ್ಥಾನಾಂತರ_l1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                delta_chroma_ತೂಕ_l1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
    int8_t                                delta_chroma_ಸ್ಥಾನಾಂತರ_l1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H265_MAX_CHROMA_PLANES];
} Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H265_ತುಂಡು_Segment_ಶೀರ್ಷಿಕೆ_Flags {
    uint32_t    ಮೊದಲ_ತುಂಡು_segment_ಒಳ_pic_flag : 1;
    uint32_t    dependent_ತುಂಡು_segment_flag : 1;
    uint32_t    ತುಂಡು_sao_luma_flag : 1;
    uint32_t    ತುಂಡು_sao_chroma_flag : 1;
    uint32_t    ಅಂಕೆ_ref_idx_ಸಕ್ರಿಯ_override_flag : 1;
    uint32_t    mvd_l1_zero_flag : 1;
    uint32_t    cabac_init_flag : 1;
    uint32_t    cu_chroma_qp_ಸ್ಥಾನಾಂತರ_enabled_flag : 1;
    uint32_t    deblocking_filter_override_flag : 1;
    uint32_t    ತುಂಡು_deblocking_filter_disabled_flag : 1;
    uint32_t    collocated_from_l0_flag : 1;
    uint32_t    ತುಂಡು_loop_filter_across_slices_enabled_flag : 1;
    uint32_t    reserved : 20;
} Std_Video_Encode_H265_ತುಂಡು_Segment_ಶೀರ್ಷಿಕೆ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H265_ತುಂಡು_Segment_ಶೀರ್ಷಿಕೆ {
    Std_Video_Encode_H265_ತುಂಡು_Segment_ಶೀರ್ಷಿಕೆ_Flags    flags;
    Std_Video_H265_ತುಂಡು_Type                        ತುಂಡು_type;
    uint32_t                                     ತುಂಡು_segment_ವಿಳಾಸ;
    uint8_t                                      collocated_ref_idx;
    uint8_t                                      Max_ಅಂಕೆ_ವಿಲೀನ_Cand;
    int8_t                                       ತುಂಡು_cb_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                       ತುಂಡು_cr_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                       ತುಂಡು_beta_ಸ್ಥಾನಾಂತರ_div2;
    int8_t                                       ತುಂಡು_tc_ಸ್ಥಾನಾಂತರ_div2;
    int8_t                                       ತುಂಡು_act_y_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                       ತುಂಡು_act_cb_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                       ತುಂಡು_act_cr_qp_ಸ್ಥಾನಾಂತರ;
    int8_t                                       ತುಂಡು_qp_delta;
    uint16_t                                     reserved1;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H265_ತೂಕ_ಕೋಷ್ಟಕ*         p_ತೂಕ_ಕೋಷ್ಟಕ;
} Std_Video_Encode_H265_ತುಂಡು_Segment_ಶೀರ್ಷಿಕೆ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceListsInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265ReferenceListsInfo {
    StdVideoEncodeH265ReferenceListsInfoFlags    flags;
    uint8_t                                      ಅಂಕೆ_ref_idx_l0_ಸಕ್ರಿಯ_minus1;
    uint8_t                                      ಅಂಕೆ_ref_idx_l1_ಸಕ್ರಿಯ_minus1;
    uint8_t                                      RefPicList0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    uint8_t                                      RefPicList1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    uint8_t                                      list_ನಮೂದು_l0[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
    uint8_t                                      list_ನಮೂದು_l1[STD_VIDEO_H265_MAX_ಅಂಕೆ_LIST_REF];
} StdVideoEncodeH265ReferenceListsInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265PictureInfoFlags {
    uint32_t    is_reference : 1;
    uint32_t    IrapPicFlag : 1;
    uint32_t    ಬಳಸಿದ_for_long_ಪದ_reference : 1;
    uint32_t    discardable_flag : 1;
    uint32_t    cross_layer_bla_flag : 1;
    uint32_t    pic_output_flag : 1;
    uint32_t    no_output_ದ_ಪೂರ್ವ_pics_flag : 1;
    uint32_t    short_ಪದ_ref_pic_ಗಣ_sps_flag : 1;
    uint32_t    ತುಂಡು_temporal_mvp_enabled_flag : 1;
    uint32_t    reserved : 23;
} StdVideoEncodeH265PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H265_Long_ಪದ_Ref_Pics {
    uint8_t     ಅಂಕೆ_long_ಪದ_sps;
    uint8_t     ಅಂಕೆ_long_ಪದ_pics;
    uint8_t     lt_idx_sps[STD_VIDEO_H265_MAX_LONG_ಪದ_REF_PICS_SPS];
    uint8_t     poc_lsb_lt[STD_VIDEO_H265_MAX_LONG_ಪದ_PICS];
    uint16_t    ಬಳಸಿದ_by_curr_pic_lt_flag;
    uint8_t     delta_poc_msb_present_flag[STD_VIDEO_H265_MAX_DELTA_POC];
    uint8_t     delta_poc_msb_ಚಕ್ರ_lt[STD_VIDEO_H265_MAX_DELTA_POC];
} Std_Video_Encode_H265_Long_ಪದ_Ref_Pics;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265PictureInfo {
    StdVideoEncodeH265PictureInfoFlags             flags;
    StdVideoH265PictureType                        pic_type;
    uint8_t                                        sps_video_parameter_ಗಣ_id;
    uint8_t                                        pps_seq_parameter_ಗಣ_id;
    uint8_t                                        pps_pic_parameter_ಗಣ_id;
    uint8_t                                        short_ಪದ_ref_pic_ಗಣ_idx;
    int32_t                                        Pic_ಕ್ರಮ_Cnt_Val;
    uint8_t                                        TemporalId;
    uint8_t                                        reserved1[7];
    ಸ್ಥಿರಾಂಕ StdVideoEncodeH265ReferenceListsInfo*    pRefLists;
    ಸ್ಥಿರಾಂಕ Std_Video_H265_Short_ಪದ_Ref_Pic_ಗಣ*          p_Short_ಪದ_Ref_Pic_ಗಣ;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H265_Long_ಪದ_Ref_Pics*       p_Long_ಪದ_Ref_Pics;
} StdVideoEncodeH265PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265ReferenceInfoFlags {
    uint32_t    ಬಳಸಿದ_for_long_ಪದ_reference : 1;
    uint32_t    ಬಳಸದ_for_reference : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH265ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH265ReferenceInfo {
    StdVideoEncodeH265ReferenceInfoFlags    flags;
    StdVideoH265PictureType                 pic_type;
    int32_t                                 Pic_ಕ್ರಮ_Cnt_Val;
    uint8_t                                 TemporalId;
} StdVideoEncodeH265ReferenceInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
