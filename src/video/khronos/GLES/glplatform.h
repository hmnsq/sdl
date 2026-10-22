#اگر_تعریف_نشده __glplatform_h_
#تعریف_کن __glplatform_h_

/*
** Copyright 2017-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
*/

/* Platform-specific types and definitions for OpenGL ES 1.X  gl.h
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * Please contribute modifications back to Khronos as pull requests on the
 * public github repository:
 *      https://github.com/KhronosGroup/OpenGL-Registry
 */

#ضمن <KHR/khrplatform.h>

#اگر_تعریف_نشده GL_API
#تعریف_کن GL_API      KHRONOS_APICALL
#پایان_اگر

#اگر_تعریف_نشده GL_APIENTRY
#تعریف_کن GL_APIENTRY KHRONOS_APIENTRY
#پایان_اگر

#پایان_اگر /* __glplatform_h_ */
