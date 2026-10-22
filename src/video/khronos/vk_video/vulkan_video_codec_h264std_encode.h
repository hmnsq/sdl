#ifndef VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#define VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
خارجي "C" {
#endif



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codec_h264std_encode 1

#ضمن "vulkan_video_codec_h264std.h"

#define VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#define VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_VERSION_1_0_0
#define VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

تعريفنوع بنية StdVideoEncodeH264WeightTableFlags {
    uint32_t    luma_weight_l0_flag;
    uint32_t    chroma_weight_l0_flag;
    uint32_t    luma_weight_l1_flag;
    uint32_t    chroma_weight_l1_flag;
} StdVideoEncodeH264WeightTableFlags;

تعريفنوع بنية StdVideoEncodeH264WeightTable {
    StdVideoEncodeH264WeightTableFlags    flags;
    uint8_t                               luma_log2_weight_denom;
    uint8_t                               chroma_log2_weight_denom;
    int8_t                                luma_weight_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_offset_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_weight_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_offset_l0[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_weight_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                luma_offset_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    int8_t                                chroma_weight_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_offset_l1[STD_VIDEO_H264_MAX_عدد_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} StdVideoEncodeH264WeightTable;

تعريفنوع بنية StdVideoEncodeH264SliceHeaderFlags {
    uint32_t    direct_spatial_mv_pred_flag : 1;
    uint32_t    عدد_ref_idx_active_override_flag : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264SliceHeaderFlags;

تعريفنوع بنية StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_of_prior_pics_flag : 1;
    uint32_t    long_term_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_mode_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    used_for_long_term_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

تعريفنوع بنية StdVideoEncodeH264RefListModEntry {
    StdVideoH264ModificationOfPicNumsIdc    modification_of_pic_nums_idc;
    uint16_t                                abs_diff_pic_عدد_minus1;
    uint16_t                                long_term_pic_عدد;
} StdVideoEncodeH264RefListModEntry;

تعريفنوع بنية StdVideoEncodeH264RefPicMarkingEntry {
    StdVideoH264MemMgmtControlOp    memory_management_control_operation;
    uint16_t                        difference_of_pic_nums_minus1;
    uint16_t                        long_term_pic_عدد;
    uint16_t                        long_term_frame_idx;
    uint16_t                        max_long_term_frame_idx_plus1;
} StdVideoEncodeH264RefPicMarkingEntry;

تعريفنوع بنية StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        عدد_ref_idx_l0_active_minus1;
    uint8_t                                        عدد_ref_idx_l1_active_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_عدد_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_گنتی;
    uint8_t                                        ref_List1_Mod_Op_گنتی;
    uint8_t                                        ref_Pic_Marking_Op_گنتی;
    uint8_t                                        reserved1[7];
    ثابت StdVideoEncodeH264RefListModEntry*       pRefList0ModOperations;
    ثابت StdVideoEncodeH264RefListModEntry*       pRefList1ModOperations;
    ثابت StdVideoEncodeH264RefPicMarkingEntry*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

تعريفنوع بنية StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_set_id;
    uint8_t                                        pic_parameter_set_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       frame_عدد;
    int32_t                                        PicOrderCnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ثابت StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

تعريفنوع بنية StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                Frame_عدد;
    int32_t                                 PicOrderCnt;
    uint16_t                                long_term_pic_عدد;
    uint16_t                                long_term_frame_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

تعريفنوع بنية StdVideoEncodeH264SliceHeader {
    StdVideoEncodeH264SliceHeaderFlags        flags;
    uint32_t                                  first_mb_in_slice;
    StdVideoH264SliceType                     slice_type;
    int8_t                                    slice_alpha_c0_offset_div2;
    int8_t                                    slice_beta_offset_div2;
    int8_t                                    slice_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ثابت StdVideoEncodeH264WeightTable*      pWeightTable;
} StdVideoEncodeH264SliceHeader;


#ifdef __cplusplus
}
#endif

#endif
