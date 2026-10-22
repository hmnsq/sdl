#که_نه_تعریف_شوی VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#تعریف_کړه VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codec_h265std_decode 1

#ضمن "vulkan_video_codec_h265std.h"

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخه_1_0_0 VK_MAKE_VIDEO_STD_نسخه(1, 0, 0)

#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_نسخه VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخه_1_0_0
#تعریف_کړه VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#تعریف_کړه STD_VIDEO_DECODE_H265_REF_PIC_سېټ_LIST_اندازه 8U

تعريفنوع بنية StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_غړی_ref_pic_سېټ_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_سېټ_id;
    uint8_t                               pps_seq_parameter_سېټ_id;
    uint8_t                               pps_pic_parameter_سېټ_id;
    uint8_t                               عدد_Delta_Pocs_د_Ref_Rps_Idx;
    int32_t                               Pic_ترتیب_Cnt_Val;
    uint16_t                              عدد_بټونه_For_STRef_Pic_سېټ_دننه_ټوټه;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_سېټ_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_سېټ_LIST_اندازه];
    uint8_t                               Ref_Pic_سېټ_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_سېټ_LIST_اندازه];
    uint8_t                               Ref_Pic_سېټ_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_سېټ_LIST_اندازه];
} StdVideoDecodeH265PictureInfo;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    کارول_شوی_for_long_غړی_reference : 1;
    uint32_t    ناکارول_شوی_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ترتیب_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
