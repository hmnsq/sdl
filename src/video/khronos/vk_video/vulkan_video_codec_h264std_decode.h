#अगर_अघोषित VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#घोषणा VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#घोषणा vulkan_video_codec_h264std_decode 1

#समावेश "vulkan_video_codec_h264std.h"

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#घोषणा VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_VERSION_1_0_0
#घोषणा VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#घोषणा STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_LIST_आकार 2U

प्रकार क्रमागत Std_Video_Decode_H264_Field_Order_गिनती {
    STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_शीर्ष = 0,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_Field_Order_गिनती;

प्रकार काष्ठा StdVideoDecodeH264PictureInfoFlags {
    uint32_t    field_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_field_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_field_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

प्रकार काष्ठा StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_set_id;
    uint8_t                               pic_parameter_set_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              frame_अंक;
    uint16_t                              idr_pic_id;
    int32_t                               PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_LIST_आकार];
} StdVideoDecodeH264PictureInfo;

प्रकार काष्ठा StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    शीर्ष_field_flag : 1;
    uint32_t    bottom_field_flag : 1;
    uint32_t    used_for_long_term_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

प्रकार काष्ठा StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                Frame_अंक;
    uint16_t                                reserved;
    int32_t                                 PicOrderCnt[STD_VIDEO_DECODE_H264_FIELD_ORDER_गिनती_LIST_आकार];
} StdVideoDecodeH264ReferenceInfo;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
