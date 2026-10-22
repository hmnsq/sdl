#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

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



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h264std_encode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_h264std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ_Flags {
    uint32_t    luma_ತೂಕ_l0_flag;
    uint32_t    chroma_ತೂಕ_l0_flag;
    uint32_t    luma_ತೂಕ_l1_flag;
    uint32_t    chroma_ತೂಕ_l1_flag;
} Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ {
    Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ_Flags    flags;
    uint8_t                               luma_log2_ತೂಕ_denom;
    uint8_t                               chroma_log2_ತೂಕ_denom;
    int8_t                                luma_ತೂಕ_l0[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                luma_ಸ್ಥಾನಾಂತರ_l0[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                chroma_ತೂಕ_l0[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_ಸ್ಥಾನಾಂತರ_l0[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_ತೂಕ_l1[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                luma_ಸ್ಥಾನಾಂತರ_l1[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    int8_t                                chroma_ತೂಕ_l1[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_ಸ್ಥಾನಾಂತರ_l1[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_ತುಂಡು_ಶೀರ್ಷಿಕೆ_Flags {
    uint32_t    ನೇರ_spatial_mv_pred_flag : 1;
    uint32_t    ಅಂಕೆ_ref_idx_ಸಕ್ರಿಯ_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_ತುಂಡು_ಶೀರ್ಷಿಕೆ_Flags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_ದ_ಪೂರ್ವ_pics_flag : 1;
    uint32_t    long_ಪದ_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_ಬಹುಲಕ_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    ಬಳಸಿದ_for_long_ಪದ_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_Ref_List_Mod_ನಮೂದು {
    Std_Video_H264_Modification_ದ_Pic_Nums_Idc    modification_ದ_pic_nums_idc;
    uint16_t                                abs_diff_pic_ಅಂಕೆ_minus1;
    uint16_t                                long_ಪದ_pic_ಅಂಕೆ;
} Std_Video_Encode_H264_Ref_List_Mod_ನಮೂದು;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_Ref_Pic_Marking_ನಮೂದು {
    StdVideoH264MemMgmtControlOp    ಸ್ಮರಣೆ_management_control_operation;
    uint16_t                        difference_ದ_pic_nums_minus1;
    uint16_t                        long_ಪದ_pic_ಅಂಕೆ;
    uint16_t                        long_ಪದ_ಚೌಕಟ್ಟು_idx;
    uint16_t                        max_long_ಪದ_ಚೌಕಟ್ಟು_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_ನಮೂದು;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        ಅಂಕೆ_ref_idx_l0_ಸಕ್ರಿಯ_minus1;
    uint8_t                                        ಅಂಕೆ_ref_idx_l1_ಸಕ್ರಿಯ_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_ಅಂಕೆ_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_ಎಣಿಕೆ;
    uint8_t                                        ref_List1_Mod_Op_ಎಣಿಕೆ;
    uint8_t                                        ref_Pic_Marking_Op_ಎಣಿಕೆ;
    uint8_t                                        reserved1[7];
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H264_Ref_List_Mod_ನಮೂದು*       pRefList0ModOperations;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H264_Ref_List_Mod_ನಮೂದು*       pRefList1ModOperations;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H264_Ref_Pic_Marking_ನಮೂದು*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_ಗಣ_id;
    uint8_t                                        pic_parameter_ಗಣ_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       ಚೌಕಟ್ಟು_ಅಂಕೆ;
    int32_t                                        Pic_ಕ್ರಮ_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ಸ್ಥಿರಾಂಕ StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                ಚೌಕಟ್ಟು_ಅಂಕೆ_2;
    int32_t                                 Pic_ಕ್ರಮ_Cnt;
    uint16_t                                long_ಪದ_pic_ಅಂಕೆ;
    uint16_t                                long_ಪದ_ಚೌಕಟ್ಟು_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Std_Video_Encode_H264_ತುಂಡು_ಶೀರ್ಷಿಕೆ {
    Std_Video_Encode_H264_ತುಂಡು_ಶೀರ್ಷಿಕೆ_Flags        flags;
    uint32_t                                  ಮೊದಲ_mb_ಒಳ_ತುಂಡು;
    Std_Video_H264_ತುಂಡು_Type                     ತುಂಡು_type;
    int8_t                                    ತುಂಡು_alpha_c0_ಸ್ಥಾನಾಂತರ_div2;
    int8_t                                    ತುಂಡು_beta_ಸ್ಥಾನಾಂತರ_div2;
    int8_t                                    ತುಂಡು_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ಸ್ಥಿರಾಂಕ Std_Video_Encode_H264_ತೂಕ_ಕೋಷ್ಟಕ*      p_ತೂಕ_ಕೋಷ್ಟಕ;
} Std_Video_Encode_H264_ತುಂಡು_ಶೀರ್ಷಿಕೆ;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
