#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h264std_decode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_h264std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_LIST_ಗಾತ್ರ 2U

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Std_Video_Decode_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ {
    STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_ತುದಿ = 0,
    STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH264PictureInfoFlags {
    uint32_t    ಕ್ಷೇತ್ರ_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_ಕ್ಷೇತ್ರ_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_ಕ್ಷೇತ್ರ_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_ಗಣ_id;
    uint8_t                               pic_parameter_ಗಣ_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              ಚೌಕಟ್ಟು_ಅಂಕೆ;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_ಕ್ರಮ_Cnt[STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_LIST_ಗಾತ್ರ];
} StdVideoDecodeH264PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    ತುದಿ_ಕ್ಷೇತ್ರ_flag : 1;
    uint32_t    bottom_ಕ್ಷೇತ್ರ_flag : 1;
    uint32_t    ಬಳಸಿದ_for_long_ಪದ_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                ಚೌಕಟ್ಟು_ಅಂಕೆ_2;
    uint16_t                                reserved;
    int32_t                                 Pic_ಕ್ರಮ_Cnt[STD_VIDEO_DECODE_H264_ಕ್ಷೇತ್ರ_ಕ್ರಮ_ಎಣಿಕೆ_LIST_ಗಾತ್ರ];
} StdVideoDecodeH264ReferenceInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
