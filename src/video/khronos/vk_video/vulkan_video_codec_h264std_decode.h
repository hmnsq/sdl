#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

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



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vulkan_video_codec_h264std_decode 1

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_video_codec_h264std.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_ਸੰਸਕਰਣ_1_0_0 VK_MAKE_VIDEO_STD_ਸੰਸਕਰਣ(1, 0, 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_ਸੰਸਕਰਣ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_ਸੰਸਕਰਣ_1_0_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_LIST_ਮਾਪ 2U

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Std_Video_Decode_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ {
    STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_ਸਿਖਰ = 0,
    STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH264PictureInfoFlags {
    uint32_t    ਖੇਤਰ_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_ਖੇਤਰ_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_ਖੇਤਰ_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_ਸੈੱਟ_id;
    uint8_t                               pic_parameter_ਸੈੱਟ_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              ਚੌਖਟਾ_ਅੰਕ;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ਕ੍ਰਮ_Cnt[STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_LIST_ਮਾਪ];
} StdVideoDecodeH264PictureInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    ਸਿਖਰ_ਖੇਤਰ_flag : 1;
    uint32_t    bottom_ਖੇਤਰ_flag : 1;
    uint32_t    ਵਰਤਿਆ_for_long_ਪਦ_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                ਚੌਖਟਾ_ਅੰਕ_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ਕ੍ਰਮ_Cnt[STD_VIDEO_DECODE_H264_ਖੇਤਰ_ਕ੍ਰਮ_ਗਿਣਤੀ_LIST_ਮਾਪ];
} StdVideoDecodeH264ReferenceInfo;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
