#اگر_غیر_تعریف_شدہ VULKAN_VIDEO_CODECS_COMMON_H_
#تعریف_کرو VULKAN_VIDEO_CODECS_COMMON_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// vulkan_video_codecs_common is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو vulkan_video_codecs_common 1

#اگر !defined(VK_NO_STDINT_H)
    #شامل <stdint.h>
#اگر_ختم

#تعریف_کرو VK_MAKE_VIDEO_STD_نسخہ(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
