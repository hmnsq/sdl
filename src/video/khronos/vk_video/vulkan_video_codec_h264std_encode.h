#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h264std_encode 1

#شامل "vulkan_video_codec_h264std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

قسمتعریف ساخت Std_Video_Encode_H264_وزن_جدول_Flags {
    uint32_t    luma_وزن_l0_flag;
    uint32_t    chroma_وزن_l0_flag;
    uint32_t    luma_وزن_l1_flag;
    uint32_t    chroma_وزن_l1_flag;
} Std_Video_Encode_H264_وزن_جدول_Flags;

قسمتعریف ساخت Std_Video_Encode_H264_وزن_جدول {
    Std_Video_Encode_H264_وزن_جدول_Flags    flags;
    uint8_t                               luma_log2_وزن_denom;
    uint8_t                               chroma_log2_وزن_denom;
    int8_t                                luma_وزن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_انحراف_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_وزن_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_انحراف_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_وزن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_انحراف_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_وزن_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_انحراف_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_وزن_جدول;

قسمتعریف ساخت Std_Video_Encode_H264_قاش_سرخی_Flags {
    uint32_t    براہ_راست_spatial_mv_pred_flag : 1;
    uint32_t    عدد_ref_idx_فعال_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_قاش_سرخی_Flags;

قسمتعریف ساخت StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_کا_پیشگی_pics_flag : 1;
    uint32_t    long_رکن_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_منوال_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

قسمتعریف ساخت StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    مستعمل_for_long_رکن_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

قسمتعریف ساخت StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

قسمتعریف ساخت Std_Video_Encode_H264_Ref_List_Mod_اندراج {
    Std_Video_H264_Modification_کا_Pic_Nums_Idc    modification_کا_pic_nums_idc;
    uint16_t                                abs_diff_pic_عدد_minus1;
    uint16_t                                long_رکن_pic_عدد;
} Std_Video_Encode_H264_Ref_List_Mod_اندراج;

قسمتعریف ساخت Std_Video_Encode_H264_Ref_Pic_Marking_اندراج {
    StdVideoH264MemMgmtControlOp    حافظہ_management_control_operation;
    uint16_t                        difference_کا_pic_nums_minus1;
    uint16_t                        long_رکن_pic_عدد;
    uint16_t                        long_رکن_چوکھٹا_idx;
    uint16_t                        max_long_رکن_چوکھٹا_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_اندراج;

قسمتعریف ساخت StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        عدد_ref_idx_l0_فعال_minus1;
    uint8_t                                        عدد_ref_idx_l1_فعال_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_گنتی;
    uint8_t                                        ref_List1_Mod_Op_گنتی;
    uint8_t                                        ref_Pic_Marking_Op_گنتی;
    uint8_t                                        reserved1[7];
    ثابت Std_Video_Encode_H264_Ref_List_Mod_اندراج*       pRefList0ModOperations;
    ثابت Std_Video_Encode_H264_Ref_List_Mod_اندراج*       pRefList1ModOperations;
    ثابت Std_Video_Encode_H264_Ref_Pic_Marking_اندراج*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

قسمتعریف ساخت StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_سیٹ_id;
    uint8_t                                        pic_parameter_سیٹ_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       چوکھٹا_عدد;
    int32_t                                        Pic_ترتیب_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ثابت StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

قسمتعریف ساخت StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                چوکھٹا_عدد_2;
    int32_t                                 Pic_ترتیب_Cnt;
    uint16_t                                long_رکن_pic_عدد;
    uint16_t                                long_رکن_چوکھٹا_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

قسمتعریف ساخت Std_Video_Encode_H264_قاش_سرخی {
    Std_Video_Encode_H264_قاش_سرخی_Flags        flags;
    uint32_t                                  پہلا_mb_اندر_قاش;
    Std_Video_H264_قاش_Type                     قاش_type;
    int8_t                                    قاش_alpha_c0_انحراف_div2;
    int8_t                                    قاش_beta_انحراف_div2;
    int8_t                                    قاش_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ثابت Std_Video_Encode_H264_وزن_جدول*      p_وزن_جدول;
} Std_Video_Encode_H264_قاش_سرخی;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
