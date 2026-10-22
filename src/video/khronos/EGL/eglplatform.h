#నిర్వచితం_కాకపోతే __eglplatform_h_
#నిర్వచించు __eglplatform_h_

/*
** Copyright 2007-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
*/

/* Platform-specific types and definitions for egl.h
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by filing an issue or pull request on the public Khronos EGL Registry, at
 * https://www.github.com/KhronosGroup/EGL-Registry/
 */

#అన్తర్భావ <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#నిర్వచితం_కాకపోతే EGLAPI
#నిర్వచించు EGLAPI KHRONOS_APICALL
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే EGLAPIENTRY
#నిర్వచించు EGLAPIENTRY  KHRONOS_APIENTRY
#అయితే_ముగింపు
#నిర్వచించు EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 *
 * Khronos STRONGLY RECOMMENDS that you use the default definitions
 * provided below, since these changes affect both binary and source
 * portability of applications using EGL running on different EGL
 * implementations.
 */

#ఒకవేళ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

రకనిర్వచనం శూన్య *EGLNativeDisplayType;
రకనిర్వచనం శూన్య *EGLNativePixmapType;
రకనిర్వచనం శూన్య *EGLNative_కిటికీ_Type;

#లేదావేళ defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#నిర్వచితం_కాకపోతే WIN32_LEAN_AND_సగటు
#నిర్వచించు WIN32_LEAN_AND_సగటు 1
#అయితే_ముగింపు
#అన్తర్భావ <windows.h>

రకనిర్వచనం HDC     EGLNativeDisplayType;
రకనిర్వచనం HBITMAP EGLNativePixmapType;
రకనిర్వచనం HWND    EGLNative_కిటికీ_Type;

#లేదావేళ defined(__QNX__)

రకనిర్వచనం khronos_uintptr_t      EGLNativeDisplayType;
రకనిర్వచనం నిర్మాణం _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
రకనిర్వచనం నిర్మాణం screen_కిటికీ* EGLNative_కిటికీ_Type;  /* screen_window_t */

#లేదావేళ defined(__EMSCRIPTEN__)

రకనిర్వచనం పూర్ణాంకం EGLNativeDisplayType;
రకనిర్వచనం పూర్ణాంకం EGLNativePixmapType;
రకనిర్వచనం పూర్ణాంకం EGLNative_కిటికీ_Type;

#లేదావేళ defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

రకనిర్వచనం పూర్ణాంకం   EGLNativeDisplayType;
రకనిర్వచనం శూన్య *EGLNativePixmapType;
రకనిర్వచనం శూన్య *EGLNative_కిటికీ_Type;

#లేదావేళ defined(WL_EGL_PLATFORM)

రకనిర్వచనం నిర్మాణం wl_display     *EGLNativeDisplayType;
రకనిర్వచనం నిర్మాణం wl_egl_pixmap  *EGLNativePixmapType;
రకనిర్వచనం నిర్మాణం wl_egl_కిటికీ  *EGLNative_కిటికీ_Type;

#లేదావేళ defined(__GBM__)

రకనిర్వచనం నిర్మాణం gbm_device  *EGLNativeDisplayType;
రకనిర్వచనం నిర్మాణం gbm_bo      *EGLNativePixmapType;
రకనిర్వచనం శూన్య               *EGLNative_కిటికీ_Type;

#లేదావేళ defined(__ANDROID__) || defined(ANDROID)

నిర్మాణం ANative_కిటికీ;
నిర్మాణం egl_native_pixmap_t;

రకనిర్వచనం శూన్య*                           EGLNativeDisplayType;
రకనిర్వచనం నిర్మాణం egl_native_pixmap_t*     EGLNativePixmapType;
రకనిర్వచనం నిర్మాణం ANative_కిటికీ*           EGLNative_కిటికీ_Type;

#లేదావేళ defined(USE_OZONE)

రకనిర్వచనం intptr_t EGLNativeDisplayType;
రకనిర్వచనం intptr_t EGLNativePixmapType;
రకనిర్వచనం intptr_t EGLNative_కిటికీ_Type;

#లేదావేళ defined(USE_X11)

/* X11 (tentative)  */
#అన్తర్భావ <X11/Xlib.h>
#అన్తర్భావ <X11/Xutil.h>

రకనిర్వచనం Display *EGLNativeDisplayType;
రకనిర్వచనం Pixmap   EGLNativePixmapType;
రకనిర్వచనం కిటికీ_2   EGLNative_కిటికీ_Type;

#లేదావేళ defined(__unix__)

రకనిర్వచనం శూన్య             *EGLNativeDisplayType;
రకనిర్వచనం khronos_uintptr_t EGLNativePixmapType;
రకనిర్వచనం khronos_uintptr_t EGLNative_కిటికీ_Type;

#లేదావేళ defined(__APPLE__)

రకనిర్వచనం పూర్ణాంకం   EGLNativeDisplayType;
రకనిర్వచనం శూన్య *EGLNativePixmapType;
రకనిర్వచనం శూన్య *EGLNative_కిటికీ_Type;

#లేదావేళ defined(__HAIKU__)

#అన్తర్భావ <kernel/image.h>

రకనిర్వచనం శూన్య              *EGLNativeDisplayType;
రకనిర్వచనం khronos_uintptr_t  EGLNativePixmapType;
రకనిర్వచనం khronos_uintptr_t  EGLNative_కిటికీ_Type;

#లేదావేళ defined(__Fuchsia__)

రకనిర్వచనం శూన్య              *EGLNativeDisplayType;
రకనిర్వచనం khronos_uintptr_t  EGLNativePixmapType;
రకనిర్వచనం khronos_uintptr_t  EGLNative_కిటికీ_Type;

#లేకపోతే
#దోషం "Platform not recognized"
#అయితే_ముగింపు

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
రకనిర్వచనం EGLNativeDisplayType NativeDisplayType;
రకనిర్వచనం EGLNativePixmapType  NativePixmapType;
రకనిర్వచనం EGLNative_కిటికీ_Type  Native_కిటికీ_Type;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
రకనిర్వచనం khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#ఒకవేళ defined(__cplusplus)
#నిర్వచించు EGL_CAST(type, విలువ) (static_cast<type>(విలువ))
#లేకపోతే
#నిర్వచించు EGL_CAST(type, విలువ) ((type) (విలువ))
#అయితే_ముగింపు

#అయితే_ముగింపు /* __eglplatform_h */
