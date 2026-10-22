#که_نه_تعریف_شوی VULKAN_VIDEO_CODECS_COMMON_H_
#تعریف_کړه VULKAN_VIDEO_CODECS_COMMON_H_ 1

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



// vulkan_video_codecs_common is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه vulkan_video_codecs_common 1

#إذا !defined(VK_NO_STDINT_H)
    #ضمن <stdint.h>
#د_که_پای

#تعریف_کړه VK_MAKE_VIDEO_STD_نسخه(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
