#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h265std_decode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_h265std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_DECODE_H265_REF_PIC_ਸੈੱਟ_LIST_ਮਾਪ 8U

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_ਪਦ_ref_pic_ਸੈੱਟ_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_ਸੈੱਟ_id;
    uint8_t                               pps_seq_parameter_ਸੈੱਟ_id;
    uint8_t                               pps_pic_parameter_ਸੈੱਟ_id;
    uint8_t                               ਅੰਕ_Delta_Pocs_ਦਾ_Ref_Rps_Idx;
    int32_t                               Pic_ਕ੍ਰਮ_Cnt_Val;
    uint16_t                              ਅੰਕ_ਬਿੱਟ_For_STRef_Pic_ਸੈੱਟ_ਵਿੱਚ_ਟੁਕੜਾ;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_ਸੈੱਟ_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_ਸੈੱਟ_LIST_ਮਾਪ];
    uint8_t                               Ref_Pic_ਸੈੱਟ_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_ਸੈੱਟ_LIST_ਮਾਪ];
    uint8_t                               Ref_Pic_ਸੈੱਟ_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_ਸੈੱਟ_LIST_ਮਾਪ];
} StdVideoDecodeH265PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    ਵਰਤਿਆ_for_long_ਪਦ_reference : 1;
    uint32_t    ਅਣਵਰਤਿਆ_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ਕ੍ਰਮ_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
