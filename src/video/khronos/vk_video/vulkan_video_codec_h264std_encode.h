#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

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



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_h264std_encode 1

#ضمن "vulkan_video_codec_h264std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

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
    int8_t                                luma_وزن_l0[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    int8_t                                luma_وٿي_l0[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    int8_t                                chroma_وزن_l0[STD_VIDEO_H264_MAX_انگ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_وٿي_l0[STD_VIDEO_H264_MAX_انگ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_وزن_l1[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    int8_t                                luma_وٿي_l1[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    int8_t                                chroma_وزن_l1[STD_VIDEO_H264_MAX_انگ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_وٿي_l1[STD_VIDEO_H264_MAX_انگ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_وزن_جدول;

تعريفنوع بنية Std_Video_Encode_H264_ٽڪرو_سرو_Flags {
    uint32_t    سڌو_spatial_mv_pred_flag : 1;
    uint32_t    انگ_ref_idx_سرگرم_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_ٽڪرو_سرو_Flags;

تعريفنوع بنية StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_جو_اڳواٽ_pics_flag : 1;
    uint32_t    long_رڪن_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_گهڻائي_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    استعمال_ٿيل_for_long_رڪن_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

تعريفنوع بنية Std_Video_Encode_H264_Ref_List_Mod_داخلا {
    Std_Video_H264_Modification_جو_Pic_Nums_Idc    modification_جو_pic_nums_idc;
    uint16_t                                abs_diff_pic_انگ_minus1;
    uint16_t                                long_رڪن_pic_انگ;
} Std_Video_Encode_H264_Ref_List_Mod_داخلا;

تعريفنوع بنية Std_Video_Encode_H264_Ref_Pic_Marking_داخلا {
    StdVideoH264MemMgmtControlOp    يادگيري_management_control_operation;
    uint16_t                        difference_جو_pic_nums_minus1;
    uint16_t                        long_رڪن_pic_انگ;
    uint16_t                        long_رڪن_چوکٺو_idx;
    uint16_t                        max_long_رڪن_چوکٺو_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_داخلا;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        انگ_ref_idx_l0_سرگرم_minus1;
    uint8_t                                        انگ_ref_idx_l1_سرگرم_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_انگ_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_ڳڻپ;
    uint8_t                                        ref_List1_Mod_Op_ڳڻپ;
    uint8_t                                        ref_Pic_Marking_Op_ڳڻپ;
    uint8_t                                        reserved1[7];
    ثابت Std_Video_Encode_H264_Ref_List_Mod_داخلا*       pRefList0ModOperations;
    ثابت Std_Video_Encode_H264_Ref_List_Mod_داخلا*       pRefList1ModOperations;
    ثابت Std_Video_Encode_H264_Ref_Pic_Marking_داخلا*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_سيٽ_id;
    uint8_t                                        pic_parameter_سيٽ_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       چوکٺو_انگ;
    int32_t                                        Pic_ترتيب_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ثابت StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                چوکٺو_انگ_2;
    int32_t                                 Pic_ترتيب_Cnt;
    uint16_t                                long_رڪن_pic_انگ;
    uint16_t                                long_رڪن_چوکٺو_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

تعريفنوع بنية Std_Video_Encode_H264_ٽڪرو_سرو {
    Std_Video_Encode_H264_ٽڪرو_سرو_Flags        flags;
    uint32_t                                  پهريون_mb_اندريون_ٽڪرو;
    Std_Video_H264_ٽڪرو_Type                     ٽڪرو_type;
    int8_t                                    ٽڪرو_alpha_c0_وٿي_div2;
    int8_t                                    ٽڪرو_beta_وٿي_div2;
    int8_t                                    ٽڪرو_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ثابت Std_Video_Encode_H264_وزن_جدول*      p_وزن_جدول;
} Std_Video_Encode_H264_ٽڪرو_سرو;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
