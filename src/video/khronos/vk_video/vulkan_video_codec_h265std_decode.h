#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

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



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h265std_decode 1

#अन्तर्भाव "vulkan_video_codec_h265std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#परिभाषय STD_VIDEO_DECODE_H265_REF_PIC_समुच्चयः_LIST_आकार 8U

प्रकारनिर्देश संरचना StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_पदांशः_ref_pic_समुच्चयः_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_समुच्चयः_id;
    uint8_t                               pps_seq_parameter_समुच्चयः_id;
    uint8_t                               pps_pic_parameter_समुच्चयः_id;
    uint8_t                               अङ्कः_Delta_Pocs_सम्बन्धि_Ref_Rps_Idx;
    int32_t                               Pic_क्रमः_Cnt_Val;
    uint16_t                              अङ्कः_द्वयङ्काः_For_STRef_Pic_समुच्चयः_अन्तर्_खण्डिका;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_समुच्चयः_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_समुच्चयः_LIST_आकार];
    uint8_t                               Ref_Pic_समुच्चयः_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_समुच्चयः_LIST_आकार];
    uint8_t                               Ref_Pic_समुच्चयः_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_समुच्चयः_LIST_आकार];
} StdVideoDecodeH265PictureInfo;

प्रकारनिर्देश संरचना StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    प्रयुक्तम्_for_long_पदांशः_reference : 1;
    uint32_t    अप्रयुक्तम्_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_क्रमः_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
