#यदि_अपरिभाषितम् VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#परिभाषय VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

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



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#परिभाषय vulkan_video_codec_h264std_decode 1

#अन्तर्भाव "vulkan_video_codec_h264std.h"

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_संस्करणम्_1_0_0 VK_MAKE_VIDEO_STD_संस्करणम्(1, 0, 0)

#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_संस्करणम् VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_संस्करणम्_1_0_0
#परिभाषय VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#परिभाषय STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_LIST_आकार 2U

प्रकारनिर्देश गणना Std_Video_Decode_H264_क्षेत्रम्_क्रमः_गणनम् {
    STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_शिखरम् = 0,
    STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_क्षेत्रम्_क्रमः_गणनम्;

प्रकारनिर्देश संरचना StdVideoDecodeH264PictureInfoFlags {
    uint32_t    क्षेत्रम्_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_क्षेत्रम्_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_क्षेत्रम्_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_समुच्चयः_id;
    uint8_t                               pic_parameter_समुच्चयः_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              frame_अङ्कः;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_क्रमः_Cnt[STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_LIST_आकार];
} StdVideoDecodeH264PictureInfo;

प्रकारनिर्देश संरचना StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    शिखरम्_क्षेत्रम्_flag : 1;
    uint32_t    bottom_क्षेत्रम्_flag : 1;
    uint32_t    प्रयुक्तम्_for_long_पदांशः_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

प्रकारनिर्देश संरचना StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                Frame_अङ्कः;
    uint16_t                                reserved;
    int32_t                                 Pic_क्रमः_Cnt[STD_VIDEO_DECODE_H264_क्षेत्रम्_क्रमः_गणनम्_LIST_आकार];
} StdVideoDecodeH264ReferenceInfo;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
