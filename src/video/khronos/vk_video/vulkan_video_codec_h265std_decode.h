#جيڪڏهن_وصف_نه_ٿيل VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#وصف_ڪريو VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو vulkan_video_codec_h265std_decode 1

#ضمن "vulkan_video_codec_h265std.h"

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخو_1_0_0 VK_MAKE_VIDEO_STD_نسخو(1, 0, 0)

#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_نسخو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_نسخو_1_0_0
#وصف_ڪريو VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#وصف_ڪريو STD_VIDEO_DECODE_H265_REF_PIC_سيٽ_LIST_سائيز 8U

تعريفنوع بنية StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_رڪن_ref_pic_سيٽ_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

تعريفنوع بنية StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_سيٽ_id;
    uint8_t                               pps_seq_parameter_سيٽ_id;
    uint8_t                               pps_pic_parameter_سيٽ_id;
    uint8_t                               انگ_Delta_Pocs_جو_Ref_Rps_Idx;
    int32_t                               Pic_ترتيب_Cnt_Val;
    uint16_t                              انگ_بٽ_For_STRef_Pic_سيٽ_اندريون_ٽڪرو;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_سيٽ_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_سيٽ_LIST_سائيز];
    uint8_t                               Ref_Pic_سيٽ_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_سيٽ_LIST_سائيز];
    uint8_t                               Ref_Pic_سيٽ_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_سيٽ_LIST_سائيز];
} StdVideoDecodeH265PictureInfo;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    استعمال_ٿيل_for_long_رڪن_reference : 1;
    uint32_t    اڻ_استعمال_ٿيل_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

تعريفنوع بنية StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ترتيب_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
