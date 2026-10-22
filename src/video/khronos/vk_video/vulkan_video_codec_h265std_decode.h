#اگر_تعریف_نشده VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#تعریف_کن VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codec_h265std_decode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخه_1_0_0
#تعریف_کن VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#تعریف_کن STD_VIDEO_DECODE_H265_REF_PIC_مجموعه_LIST_اندازه 8U

تعريفنوع بنية StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_جمله_ref_pic_مجموعه_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_مجموعه_id;
    uint8_t                               pps_seq_parameter_مجموعه_id;
    uint8_t                               pps_pic_parameter_مجموعه_id;
    uint8_t                               رقم_Delta_Pocs_از_Ref_Rps_Idx;
    int32_t                               Pic_ترتیب_Cnt_Val;
    uint16_t                              رقم_بیتها_For_STRef_Pic_مجموعه_درون_برش;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_مجموعه_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_مجموعه_LIST_اندازه];
    uint8_t                               Ref_Pic_مجموعه_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_مجموعه_LIST_اندازه];
    uint8_t                               Ref_Pic_مجموعه_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_مجموعه_LIST_اندازه];
} StdVideoDecodeH265PictureInfo;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    استفاده_شده_for_long_جمله_reference : 1;
    uint32_t    استفادهنشده_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ترتیب_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
