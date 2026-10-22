#اگر_تعریف_نشده __gl2platform_h_
#تعریف_کن __gl2platform_h_

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

#ضمن <KHR/khrplatform.h>

#اگر_تعریف_نشده GL_APICALL
#تعریف_کن GL_APICALL  KHRONOS_APICALL
#پایان_اگر

#اگر_تعریف_نشده GL_APIENTRY
#تعریف_کن GL_APIENTRY KHRONOS_APIENTRY
#پایان_اگر

#پایان_اگر /* __gl2platform_h_ */
