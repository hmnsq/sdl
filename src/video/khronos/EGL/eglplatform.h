#اگر_تعریف_نشده __eglplatform_h_
#تعریف_کن __eglplatform_h_

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

#ضمن <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#اگر_تعریف_نشده EGLAPI
#تعریف_کن EGLAPI KHRONOS_APICALL
#پایان_اگر

#اگر_تعریف_نشده EGLAPIENTRY
#تعریف_کن EGLAPIENTRY  KHRONOS_APIENTRY
#پایان_اگر
#تعریف_کن EGLAPIENTRYP EGLAPIENTRY*

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

#إذا defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

تعريفنوع فراغ *EGLNativeDisplayType;
تعريفنوع فراغ *EGLNativePixmapType;
تعريفنوع فراغ *EGLNative_پنجره_Type;

#وإلاإذا defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#اگر_تعریف_نشده WIN32_LEAN_AND_میانگین
#تعریف_کن WIN32_LEAN_AND_میانگین 1
#پایان_اگر
#ضمن <windows.h>

تعريفنوع HDC     EGLNativeDisplayType;
تعريفنوع HBITMAP EGLNativePixmapType;
تعريفنوع HWND    EGLNative_پنجره_Type;

#وإلاإذا defined(__QNX__)

تعريفنوع khronos_uintptr_t      EGLNativeDisplayType;
تعريفنوع بنية _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
تعريفنوع بنية screen_پنجره* EGLNative_پنجره_Type;  /* screen_window_t */

#وإلاإذا defined(__EMSCRIPTEN__)

تعريفنوع صحيح EGLNativeDisplayType;
تعريفنوع صحيح EGLNativePixmapType;
تعريفنوع صحيح EGLNative_پنجره_Type;

#وإلاإذا defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

تعريفنوع صحيح   EGLNativeDisplayType;
تعريفنوع فراغ *EGLNativePixmapType;
تعريفنوع فراغ *EGLNative_پنجره_Type;

#وإلاإذا defined(WL_EGL_PLATFORM)

تعريفنوع بنية wl_display     *EGLNativeDisplayType;
تعريفنوع بنية wl_egl_pixmap  *EGLNativePixmapType;
تعريفنوع بنية wl_egl_پنجره  *EGLNative_پنجره_Type;

#وإلاإذا defined(__GBM__)

تعريفنوع بنية gbm_device  *EGLNativeDisplayType;
تعريفنوع بنية gbm_bo      *EGLNativePixmapType;
تعريفنوع فراغ               *EGLNative_پنجره_Type;

#وإلاإذا defined(__ANDROID__) || defined(ANDROID)

بنية ANative_پنجره;
بنية egl_native_pixmap_t;

تعريفنوع فراغ*                           EGLNativeDisplayType;
تعريفنوع بنية egl_native_pixmap_t*     EGLNativePixmapType;
تعريفنوع بنية ANative_پنجره*           EGLNative_پنجره_Type;

#وإلاإذا defined(USE_OZONE)

تعريفنوع intptr_t EGLNativeDisplayType;
تعريفنوع intptr_t EGLNativePixmapType;
تعريفنوع intptr_t EGLNative_پنجره_Type;

#وإلاإذا defined(USE_X11)

/* X11 (tentative)  */
#ضمن <X11/Xlib.h>
#ضمن <X11/Xutil.h>

تعريفنوع Display *EGLNativeDisplayType;
تعريفنوع Pixmap   EGLNativePixmapType;
تعريفنوع پنجره_2   EGLNative_پنجره_Type;

#وإلاإذا defined(__unix__)

تعريفنوع فراغ             *EGLNativeDisplayType;
تعريفنوع khronos_uintptr_t EGLNativePixmapType;
تعريفنوع khronos_uintptr_t EGLNative_پنجره_Type;

#وإلاإذا defined(__APPLE__)

تعريفنوع صحيح   EGLNativeDisplayType;
تعريفنوع فراغ *EGLNativePixmapType;
تعريفنوع فراغ *EGLNative_پنجره_Type;

#وإلاإذا defined(__HAIKU__)

#ضمن <kernel/image.h>

تعريفنوع فراغ              *EGLNativeDisplayType;
تعريفنوع khronos_uintptr_t  EGLNativePixmapType;
تعريفنوع khronos_uintptr_t  EGLNative_پنجره_Type;

#وإلاإذا defined(__Fuchsia__)

تعريفنوع فراغ              *EGLNativeDisplayType;
تعريفنوع khronos_uintptr_t  EGLNativePixmapType;
تعريفنوع khronos_uintptr_t  EGLNative_پنجره_Type;

#وإلا
#خطا "Platform not recognized"
#پایان_اگر

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
تعريفنوع EGLNativeDisplayType NativeDisplayType;
تعريفنوع EGLNativePixmapType  NativePixmapType;
تعريفنوع EGLNative_پنجره_Type  Native_پنجره_Type;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
تعريفنوع khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#إذا defined(__cplusplus)
#تعریف_کن EGL_CAST(type, مقدار) (static_cast<type>(مقدار))
#وإلا
#تعریف_کن EGL_CAST(type, مقدار) ((type) (مقدار))
#پایان_اگر

#پایان_اگر /* __eglplatform_h */
