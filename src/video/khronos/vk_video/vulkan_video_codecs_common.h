#اگر_تعریف_نشده VULKAN_VIDEO_CODECS_COMMON_H_
#تعریف_کن VULKAN_VIDEO_CODECS_COMMON_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// vulkan_video_codecs_common is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن vulkan_video_codecs_common 1

#إذا !defined(VK_NO_STDINT_H)
    #ضمن <stdint.h>
#پایان_اگر

#تعریف_کن VK_MAKE_VIDEO_STD_نسخه(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
