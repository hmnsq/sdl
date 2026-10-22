#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

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



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h264std_encode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_h264std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ_Flags {
    uint32_t    luma_ਭਾਰ_l0_flag;
    uint32_t    chroma_ਭਾਰ_l0_flag;
    uint32_t    luma_ਭਾਰ_l1_flag;
    uint32_t    chroma_ਭਾਰ_l1_flag;
} Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ {
    Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ_Flags    flags;
    uint8_t                               luma_log2_ਭਾਰ_denom;
    uint8_t                               chroma_log2_ਭਾਰ_denom;
    int8_t                                luma_ਭਾਰ_l0[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    int8_t                                luma_ਵਿੱਥ_l0[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    int8_t                                chroma_ਭਾਰ_l0[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_ਵਿੱਥ_l0[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_ਭਾਰ_l1[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    int8_t                                luma_ਵਿੱਥ_l1[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    int8_t                                chroma_ਭਾਰ_l1[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_ਵਿੱਥ_l1[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_ਟੁਕੜਾ_ਸਿਰਲੇਖ_Flags {
    uint32_t    ਸਿੱਧਾ_spatial_mv_pred_flag : 1;
    uint32_t    ਅੰਕ_ref_idx_ਸਰਗਰਮ_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_ਟੁਕੜਾ_ਸਿਰਲੇਖ_Flags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_ਦਾ_ਪੂਰਵ_pics_flag : 1;
    uint32_t    long_ਪਦ_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_ਬਹੁਲਕ_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    ਵਰਤਿਆ_for_long_ਪਦ_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_Ref_List_Mod_ਇੰਦਰਾਜ {
    Std_Video_H264_Modification_ਦਾ_Pic_Nums_Idc    modification_ਦਾ_pic_nums_idc;
    uint16_t                                abs_diff_pic_ਅੰਕ_minus1;
    uint16_t                                long_ਪਦ_pic_ਅੰਕ;
} Std_Video_Encode_H264_Ref_List_Mod_ਇੰਦਰਾਜ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_Ref_Pic_Marking_ਇੰਦਰਾਜ {
    StdVideoH264MemMgmtControlOp    ਸਮ੍ਰਿਤੀ_management_control_operation;
    uint16_t                        difference_ਦਾ_pic_nums_minus1;
    uint16_t                        long_ਪਦ_pic_ਅੰਕ;
    uint16_t                        long_ਪਦ_ਚੌਖਟਾ_idx;
    uint16_t                        max_long_ਪਦ_ਚੌਖਟਾ_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_ਇੰਦਰਾਜ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        ਅੰਕ_ref_idx_l0_ਸਰਗਰਮ_minus1;
    uint8_t                                        ਅੰਕ_ref_idx_l1_ਸਰਗਰਮ_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_ਅੰਕ_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_ਗਿਣਤੀ;
    uint8_t                                        ref_List1_Mod_Op_ਗਿਣਤੀ;
    uint8_t                                        ref_Pic_Marking_Op_ਗਿਣਤੀ;
    uint8_t                                        reserved1[7];
    ਅਚਲ Std_Video_Encode_H264_Ref_List_Mod_ਇੰਦਰਾਜ*       pRefList0ModOperations;
    ਅਚਲ Std_Video_Encode_H264_Ref_List_Mod_ਇੰਦਰਾਜ*       pRefList1ModOperations;
    ਅਚਲ Std_Video_Encode_H264_Ref_Pic_Marking_ਇੰਦਰਾਜ*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_ਸੈੱਟ_id;
    uint8_t                                        pic_parameter_ਸੈੱਟ_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       ਚੌਖਟਾ_ਅੰਕ;
    int32_t                                        Pic_ਕ੍ਰਮ_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ਅਚਲ StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                ਚੌਖਟਾ_ਅੰਕ_2;
    int32_t                                 Pic_ਕ੍ਰਮ_Cnt;
    uint16_t                                long_ਪਦ_pic_ਅੰਕ;
    uint16_t                                long_ਪਦ_ਚੌਖਟਾ_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Std_Video_Encode_H264_ਟੁਕੜਾ_ਸਿਰਲੇਖ {
    Std_Video_Encode_H264_ਟੁਕੜਾ_ਸਿਰਲੇਖ_Flags        flags;
    uint32_t                                  ਪਹਿਲਾ_mb_ਵਿੱਚ_ਟੁਕੜਾ;
    Std_Video_H264_ਟੁਕੜਾ_Type                     ਟੁਕੜਾ_type;
    int8_t                                    ਟੁਕੜਾ_alpha_c0_ਵਿੱਥ_div2;
    int8_t                                    ਟੁਕੜਾ_beta_ਵਿੱਥ_div2;
    int8_t                                    ਟੁਕੜਾ_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ਅਚਲ Std_Video_Encode_H264_ਭਾਰ_ਸਾਰਣੀ*      p_ਭਾਰ_ਸਾਰਣੀ;
} Std_Video_Encode_H264_ਟੁਕੜਾ_ਸਿਰਲੇਖ;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
