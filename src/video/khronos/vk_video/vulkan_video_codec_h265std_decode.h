#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

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



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು vulkan_video_codec_h265std_decode 1

#ಅನ್ತರ್ಭಾವ "vulkan_video_codec_h265std.h"

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_ಆವೃತ್ತಿ_1_0_0 VK_MAKE_VIDEO_STD_ಆವೃತ್ತಿ(1, 0, 0)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_ಆವೃತ್ತಿ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_ಆವೃತ್ತಿ_1_0_0
#ವ್ಯಾಖ್ಯಾನಿಸು VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#ವ್ಯಾಖ್ಯಾನಿಸು STD_VIDEO_DECODE_H265_REF_PIC_ಗಣ_LIST_ಗಾತ್ರ 8U

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_ಪದ_ref_pic_ಗಣ_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_ಗಣ_id;
    uint8_t                               pps_seq_parameter_ಗಣ_id;
    uint8_t                               pps_pic_parameter_ಗಣ_id;
    uint8_t                               ಅಂಕೆ_Delta_Pocs_ದ_Ref_Rps_Idx;
    int32_t                               Pic_ಕ್ರಮ_Cnt_Val;
    uint16_t                              ಅಂಕೆ_ಬಿಟ್ಟುಗಳು_For_STRef_Pic_ಗಣ_ಒಳ_ತುಂಡು;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_ಗಣ_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_ಗಣ_LIST_ಗಾತ್ರ];
    uint8_t                               Ref_Pic_ಗಣ_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_ಗಣ_LIST_ಗಾತ್ರ];
    uint8_t                               Ref_Pic_ಗಣ_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_ಗಣ_LIST_ಗಾತ್ರ];
} StdVideoDecodeH265PictureInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    ಬಳಸಿದ_for_long_ಪದ_reference : 1;
    uint32_t    ಬಳಸದ_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_ಕ್ರಮ_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
