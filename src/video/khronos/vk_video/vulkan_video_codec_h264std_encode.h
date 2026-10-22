#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_H264STD_ENCODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// vulkan_video_codec_h264std_encode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h264std_encode 1

#अन्तर्भाव "vulkan_video_codec_h264std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_encode"

प्रकारनिर्देश संरचना Std_Video_Encode_H264_Weight_सारणी_Flags {
    uint32_t    luma_weight_l0_flag;
    uint32_t    chroma_weight_l0_flag;
    uint32_t    luma_weight_l1_flag;
    uint32_t    chroma_weight_l1_flag;
} Std_Video_Encode_H264_Weight_सारणी_Flags;

प्रकारनिर्देश संरचना Std_Video_Encode_H264_Weight_सारणी {
    Std_Video_Encode_H264_Weight_सारणी_Flags    flags;
    uint8_t                               luma_log2_weight_denom;
    uint8_t                               chroma_log2_weight_denom;
    int8_t                                luma_weight_l0[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    int8_t                                luma_विस्थापनम्_l0[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    int8_t                                chroma_weight_l0[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_विस्थापनम्_l0[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                luma_weight_l1[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    int8_t                                luma_विस्थापनम्_l1[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    int8_t                                chroma_weight_l1[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
    int8_t                                chroma_विस्थापनम्_l1[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF][STD_VIDEO_H264_MAX_CHROMA_PLANES];
} Std_Video_Encode_H264_Weight_सारणी;

प्रकारनिर्देश संरचना Std_Video_Encode_H264_खण्डिका_शीर्षकम्_Flags {
    uint32_t    प्रत्यक्षम्_spatial_mv_pred_flag : 1;
    uint32_t    अङ्कः_ref_idx_सक्रिय_override_flag : 1;
    uint32_t    reserved : 30;
} Std_Video_Encode_H264_खण्डिका_शीर्षकम्_Flags;

प्रकारनिर्देश संरचना StdVideoEncodeH264PictureInfoFlags {
    uint32_t    IdrPicFlag : 1;
    uint32_t    is_reference : 1;
    uint32_t    no_output_सम्बन्धि_प्राक्_pics_flag : 1;
    uint32_t    long_पदांशः_reference_flag : 1;
    uint32_t    adaptive_ref_pic_marking_बहुलकम्_flag : 1;
    uint32_t    reserved : 27;
} StdVideoEncodeH264PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeH264ReferenceInfoFlags {
    uint32_t    प्रयुक्तम्_for_long_पदांशः_reference : 1;
    uint32_t    reserved : 31;
} StdVideoEncodeH264ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoEncodeH264ReferenceListsInfoFlags {
    uint32_t    ref_pic_list_modification_flag_l0 : 1;
    uint32_t    ref_pic_list_modification_flag_l1 : 1;
    uint32_t    reserved : 30;
} StdVideoEncodeH264ReferenceListsInfoFlags;

प्रकारनिर्देश संरचना Std_Video_Encode_H264_Ref_List_Mod_प्रविष्टिः {
    Std_Video_H264_Modification_सम्बन्धि_Pic_Nums_Idc    modification_सम्बन्धि_pic_nums_idc;
    uint16_t                                abs_diff_pic_अङ्कः_minus1;
    uint16_t                                long_पदांशः_pic_अङ्कः;
} Std_Video_Encode_H264_Ref_List_Mod_प्रविष्टिः;

प्रकारनिर्देश संरचना Std_Video_Encode_H264_Ref_Pic_Marking_प्रविष्टिः {
    StdVideoH264MemMgmtControlOp    स्मृतिः_management_control_operation;
    uint16_t                        difference_सम्बन्धि_pic_nums_minus1;
    uint16_t                        long_पदांशः_pic_अङ्कः;
    uint16_t                        long_पदांशः_frame_idx;
    uint16_t                        max_long_पदांशः_frame_idx_plus1;
} Std_Video_Encode_H264_Ref_Pic_Marking_प्रविष्टिः;

प्रकारनिर्देश संरचना StdVideoEncodeH264ReferenceListsInfo {
    StdVideoEncodeH264ReferenceListsInfoFlags      flags;
    uint8_t                                        अङ्कः_ref_idx_l0_सक्रिय_minus1;
    uint8_t                                        अङ्कः_ref_idx_l1_सक्रिय_minus1;
    uint8_t                                        RefPicList0[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    uint8_t                                        RefPicList1[STD_VIDEO_H264_MAX_अङ्कः_LIST_REF];
    uint8_t                                        ref_List0_Mod_Op_गणनम्;
    uint8_t                                        ref_List1_Mod_Op_गणनम्;
    uint8_t                                        ref_Pic_Marking_Op_गणनम्;
    uint8_t                                        reserved1[7];
    ध्रुव Std_Video_Encode_H264_Ref_List_Mod_प्रविष्टिः*       pRefList0ModOperations;
    ध्रुव Std_Video_Encode_H264_Ref_List_Mod_प्रविष्टिः*       pRefList1ModOperations;
    ध्रुव Std_Video_Encode_H264_Ref_Pic_Marking_प्रविष्टिः*    pRefPicMarkingOperations;
} StdVideoEncodeH264ReferenceListsInfo;

प्रकारनिर्देश संरचना StdVideoEncodeH264PictureInfo {
    StdVideoEncodeH264PictureInfoFlags             flags;
    uint8_t                                        seq_parameter_समुच्चयः_id;
    uint8_t                                        pic_parameter_समुच्चयः_id;
    uint16_t                                       idr_pic_id;
    StdVideoH264PictureType                        primary_pic_type;
    uint32_t                                       frame_अङ्कः;
    int32_t                                        Pic_क्रमः_Cnt;
    uint8_t                                        temporal_id;
    uint8_t                                        reserved1[3];
    ध्रुव StdVideoEncodeH264ReferenceListsInfo*    pRefLists;
} StdVideoEncodeH264PictureInfo;

प्रकारनिर्देश संरचना StdVideoEncodeH264ReferenceInfo {
    StdVideoEncodeH264ReferenceInfoFlags    flags;
    StdVideoH264PictureType                 primary_pic_type;
    uint32_t                                Frame_अङ्कः;
    int32_t                                 Pic_क्रमः_Cnt;
    uint16_t                                long_पदांशः_pic_अङ्कः;
    uint16_t                                long_पदांशः_frame_idx;
    uint8_t                                 temporal_id;
} StdVideoEncodeH264ReferenceInfo;

प्रकारनिर्देश संरचना Std_Video_Encode_H264_खण्डिका_शीर्षकम् {
    Std_Video_Encode_H264_खण्डिका_शीर्षकम्_Flags        flags;
    uint32_t                                  first_mb_अन्तर्_खण्डिका;
    Std_Video_H264_खण्डिका_Type                     खण्डिका_type;
    int8_t                                    खण्डिका_alpha_c0_विस्थापनम्_div2;
    int8_t                                    खण्डिका_beta_विस्थापनम्_div2;
    int8_t                                    खण्डिका_qp_delta;
    uint8_t                                   reserved1;
    StdVideoH264CabacInitIdc                  cabac_init_idc;
    StdVideoH264DisableDeblockingFilterIdc    disable_deblocking_filter_idc;
    ध्रुव Std_Video_Encode_H264_Weight_सारणी*      p_Weight_सारणी;
} Std_Video_Encode_H264_खण्डिका_शीर्षकम्;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
