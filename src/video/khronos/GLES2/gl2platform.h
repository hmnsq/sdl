#اگر_غیر_تعریف_شدہ __gl2platform_h_
#تعریف_کرو __gl2platform_h_

/*
** Copyright 2017-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
*/

/* Platform-specific types and definitions for OpenGL ES 2.X  gl2.h
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * Please contribute modifications back to Khronos as pull requests on the
 * public github repository:
 *      https://github.com/KhronosGroup/OpenGL-Registry
 */

#شامل <KHR/khrplatform.h>

#اگر_غیر_تعریف_شدہ GL_APICALL
#تعریف_کرو GL_APICALL  KHRONOS_APICALL
#اگر_ختم

#اگر_غیر_تعریف_شدہ GL_APIENTRY
#تعریف_کرو GL_APIENTRY KHRONOS_APIENTRY
#اگر_ختم

#اگر_ختم /* __gl2platform_h_ */
