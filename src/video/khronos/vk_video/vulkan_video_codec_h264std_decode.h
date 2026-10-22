#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

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



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h264std_decode 1

#شامل "vulkan_video_codec_h264std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#تعریف_کرو STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_LIST_سائز 2U

قسمتعریف شمار Std_Video_Decode_H264_میدان_ترتیب_گنتی {
    STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_چوٹی = 0,
    STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_میدان_ترتیب_گنتی;

قسمتعریف ساخت StdVideoDecodeH264PictureInfoFlags {
    uint32_t    میدان_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_میدان_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_میدان_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

قسمتعریف ساخت StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_سیٹ_id;
    uint8_t                               pic_parameter_سیٹ_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              چوکھٹا_عدد;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_LIST_سائز];
} StdVideoDecodeH264PictureInfo;

قسمتعریف ساخت StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    چوٹی_میدان_flag : 1;
    uint32_t    bottom_میدان_flag : 1;
    uint32_t    مستعمل_for_long_رکن_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

قسمتعریف ساخت StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                چوکھٹا_عدد_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ترتیب_Cnt[STD_VIDEO_DECODE_H264_میدان_ترتیب_گنتی_LIST_سائز];
} StdVideoDecodeH264ReferenceInfo;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
