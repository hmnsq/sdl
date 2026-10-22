#నిర్వచితం_కాకపోతే VULKAN_VIDEO_CODEC_H265STD_DECODE_H_
#నిర్వచించు VULKAN_VIDEO_CODEC_H265STD_DECODE_H_ 1

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



// vulkan_video_codec_h265std_decode is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు vulkan_video_codec_h265std_decode 1

#అన్తర్భావ "vulkan_video_codec_h265std.h"

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_సంస్కరణ_1_0_0 VK_MAKE_VIDEO_STD_సంస్కరణ(1, 0, 0)

#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_సంస్కరణ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_API_సంస్కరణ_1_0_0
#నిర్వచించు VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_h265_decode"
#నిర్వచించు STD_VIDEO_DECODE_H265_REF_PIC_సమితి_LIST_కొలత 8U

రకనిర్వచనం నిర్మాణం StdVideoDecodeH265PictureInfoFlags {
    uint32_t    IrapPicFlag : 1;
    uint32_t    IdrPicFlag  : 1;
    uint32_t    IsReference : 1;
    uint32_t    short_పదం_ref_pic_సమితి_sps_flag : 1;
} StdVideoDecodeH265PictureInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH265PictureInfo {
    StdVideoDecodeH265PictureInfoFlags    flags;
    uint8_t                               sps_video_parameter_సమితి_id;
    uint8_t                               pps_seq_parameter_సమితి_id;
    uint8_t                               pps_pic_parameter_సమితి_id;
    uint8_t                               అంకె_Delta_Pocs_యొక్క_Ref_Rps_Idx;
    int32_t                               Pic_క్రమం_Cnt_Val;
    uint16_t                              అంకె_బిట్లు_For_STRef_Pic_సమితి_లోపల_ముక్క;
    uint16_t                              reserved;
    uint8_t                               Ref_Pic_సమితి_St_Curr_Before[STD_VIDEO_DECODE_H265_REF_PIC_సమితి_LIST_కొలత];
    uint8_t                               Ref_Pic_సమితి_St_Curr_After[STD_VIDEO_DECODE_H265_REF_PIC_సమితి_LIST_కొలత];
    uint8_t                               Ref_Pic_సమితి_Lt_Curr[STD_VIDEO_DECODE_H265_REF_PIC_సమితి_LIST_కొలత];
} StdVideoDecodeH265PictureInfo;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH265ReferenceInfoFlags {
    uint32_t    వాడిన_for_long_పదం_reference : 1;
    uint32_t    వాడని_for_reference : 1;
} StdVideoDecodeH265ReferenceInfoFlags;

రకనిర్వచనం నిర్మాణం StdVideoDecodeH265ReferenceInfo {
    StdVideoDecodeH265ReferenceInfoFlags    flags;
    int32_t                                 Pic_క్రమం_Cnt_Val;
} StdVideoDecodeH265ReferenceInfo;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
