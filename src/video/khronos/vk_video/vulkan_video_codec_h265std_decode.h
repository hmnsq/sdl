#جے_بنا_تعریف VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#تعریف_کرو VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codec_h265std_decode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخہ_1_0_0 VK_MAKE_VIDEO_STD_نسخہ(1, 0, 0)

#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_نسخہ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخہ_1_0_0
#تعریف_کرو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#تعریف_کرو STD_VIDEO_DECODE_H265_REF_PIC_سیٹ_LIST_ناپ 8U

تعريفنوع بنية StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_رکن_ref_pic_سیٹ_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_سیٹ_id;
    uint8_t                               pps_seq_parameter_سیٹ_id;
    uint8_t                               pps_pic_parameter_سیٹ_id;
    uint8_t                               عدد_Delta_Pocs_دا_Ref_Rps_Idx;
    int32_t                               Pic_ترتیب_Cnt_Val;
    uint16_t                              عدد_بٹ_For_STRef_Pic_سیٹ_وچ_ٹکڑا;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_سیٹ_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_سیٹ_LIST_ناپ];
    uint8_t                               Ref_Pic_سیٹ_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_سیٹ_LIST_ناپ];
    uint8_t                               Ref_Pic_سیٹ_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_سیٹ_LIST_ناپ];
} StdVideoDecodeH265PictureInfo;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    ورتیا_for_long_رکن_reference : 1;
    uint32_t    بن_ورتیا_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ترتیب_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
