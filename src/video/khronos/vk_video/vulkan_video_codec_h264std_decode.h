#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H264STD_DECODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H264STD_DECODE_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// vulkan_video_codec_h264std_decode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h264std_decode 1

#అన్తర్భావ "vulkan_video_codec_h264std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h264_decode"
#నిర్వచించు STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_LIST_కొలత 2U

రకనిర్వచనం గణన Std_Video_Decode_H264_క్షేత్రం_క్రమం_లెక్క {
    STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_శిఖరం = 0,
    STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_BOTTOM = 1,
    STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_INVALID = 0x7FFFFFFF,
    STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_MAX_ENUM = 0x7FFFFFFF
} Std_Video_Decode_H264_క్షేత్రం_క్రమం_లెక్క;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH264PictureInfoFlags {
    uint32_t    క్షేత్రం_pic_flag : 1;
    uint32_t    is_intra : 1;
    uint32_t    IdrPicFlag : 1;
    uint32_t    bottom_క్షేత్రం_flag : 1;
    uint32_t    is_reference : 1;
    uint32_t    complementary_క్షేత్రం_pair : 1;
} StdVideoDecodeH264PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH264PictureInfo {
    StdVideoDecodeH264PictureInfoFlags    flags;
    uint8_t                               seq_parameter_సమితి_id;
    uint8_t                               pic_parameter_సమితి_id;
    uint8_t                               reserved1;
    uint8_t                               reserved2;
    uint16_t                              చట్రం_అంకె;
    uint16_t                              idr_pic_id;
    int32_t                               Pic_క్రమం_Cnt[STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_LIST_కొలత];
} StdVideoDecodeH264PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH264ReferenceInfoFlags {
    uint32_t    శిఖరం_క్షేత్రం_flag : 1;
    uint32_t    bottom_క్షేత్రం_flag : 1;
    uint32_t    వాడిన_for_long_పదం_reference : 1;
    uint32_t    is_non_existing : 1;
} StdVideoDecodeH264ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH264ReferenceInfo {
    StdVideoDecodeH264ReferenceInfoFlags    flags;
    uint16_t                                చట్రం_అంకె_2;
    uint16_t                                reserved;
    int32_t                                 Pic_క్రమం_Cnt[STD_VIDEO_DECODE_H264_క్షేత్రం_క్రమం_లెక్క_LIST_కొలత];
} StdVideoDecodeH264ReferenceInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
