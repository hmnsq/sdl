#ifndef VULKAN_VIDEO_CODECS_COMMON_H_
#define VULKAN_VIDEO_CODECS_COMMON_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
ബാഹ്യ "C" {
#endif



// vulkan_video_codecs_common is a preprocessor guard. Do not pass it to API calls.
#define vulkan_video_codecs_common 1

#എങ്കിൽ !defined(VK_NO_STDINT_H)
    #അന്തര്ഭാവ <stdint.h>
#endif

#define VK_MAKE_VIDEO_STD_VERSION(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#ifdef __cplusplus
}
#endif

#endif
