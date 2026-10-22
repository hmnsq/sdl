#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

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



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_h264std_encode 1

#ضمن "vulkan_video_codec_h264std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

تعريفنوع بنية Std_Video_Encode_H264_وزن_جدول_Flags {
    uint32_t    luma_وزن_l0_flag;
    uint32_t    chroma_وزن_l0_flag;
    uint32_t    luma_وزن_l1_flag;
    uint32_t    chroma_وزن_l1_flag;
} Std_Video_Encode_H264_وزن_جدول_Flags;

تعريفنوع بنية Std_Video_Encode_H264_وزن_جدول {
    Std_Video_Encode_H264_وزن_جدول_Flags    flags;
    uint8_t                               luma_log2_وزن_denom;
    uint8_t                               chroma_log2_وزن_denom;
    int8_t                                luma_وزن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_دننه_واټن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_وزن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_دننه_واټن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_وزن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_دننه_واټن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_وزن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_دننه_واټن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_وزن_جدول;

تعريفنوع بنية Std_Video_Encode_H264_ټوټه_سرلیک_Flags {
    uint32_t    مستقیم_spatial_mv_pred_flag : 1;
    uint32_t    عدد_ref_idx_فعال_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_ټوټه_سرلیک_Flags;

تعريفنوع بنية StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_د_مخکینی_pics_flag : 1;
    uint32_t    long_غړی_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_ډېرپېښ_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    کارول_شوی_for_long_غړی_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

تعريفنوع بنية Std_Video_Encode_H264_Ref_List_Mod_ثبت {
    Std_Video_H264_Modification_د_Pic_Nums_Idc    modification_د_pic_nums_idc;
    uint16_t                                abs_diff_pic_عدد_minus1;
    uint16_t                                long_غړی_pic_عدد;
} Std_Video_Encode_H264_Ref_List_Mod_ثبت;

تعريفنوع بنية Std_Video_Encode_H264_Ref_Pic_Marking_ثبت {
    StdVideoH264MemMgmtControlOp    حافظه_management_control_operation;
    uint16_t                        difference_د_pic_nums_minus1;
    uint16_t                        long_غړی_pic_عدد;
    uint16_t                        long_غړی_چوکاټ_idx;
    uint16_t                        max_long_غړی_چوکاټ_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_ثبت;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        عدد_ref_idx_l0_فعال_minus1;
    uint8_t                                        عدد_ref_idx_l1_فعال_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_شمېر;
    uint8_t                                        ref_List1_Mod_Op_شمېر;
    uint8_t                                        ref_Pic_Marking_Op_شمېر;
    uint8_t                                        reserved1[7];
    ثابت Std_Video_Encode_H264_Ref_List_Mod_ثبت*       pRefList0ModOperations;
    ثابت Std_Video_Encode_H264_Ref_List_Mod_ثبت*       pRefList1ModOperations;
    ثابت Std_Video_Encode_H264_Ref_Pic_Marking_ثبت*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_سېټ_id;
    uint8_t                                        pic_parameter_سېټ_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       چوکاټ_عدد;
    int32_t                                        Pic_ترتیب_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ثابت StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                چوکاټ_عدد_2;
    int32_t                                 Pic_ترتیب_Cnt;
    uint16_t                                long_غړی_pic_عدد;
    uint16_t                                long_غړی_چوکاټ_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

تعريفنوع بنية Std_Video_Encode_H264_ټوټه_سرلیک {
    Std_Video_Encode_H264_ټوټه_سرلیک_Flags        flags;
    uint32_t                                  لومړی_mb_دننه_ټوټه;
    Std_Video_H264_ټوټه_Type                     ټوټه_type;
    int8_t                                    ټوټه_alpha_c0_دننه_واټن_div2;
    int8_t                                    ټوټه_beta_دننه_واټن_div2;
    int8_t                                    ټوټه_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ثابت Std_Video_Encode_H264_وزن_جدول*      p_وزن_جدول;
} Std_Video_Encode_H264_ټوټه_سرلیک;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
