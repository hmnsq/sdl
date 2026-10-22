#ifndef __eglplatform_h_
#define __eglplatform_h_

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

#شامل <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

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

#اگر defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

تعریفنوع تهی *EGLNativeDisplayType;
تعریفنوع تهی *EGLNativePixmapType;
تعریفنوع تهی *EGLNativeWindowType;

#وگرنهاگر defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#شامل <windows.h>

تعریفنوع HDC     EGLNativeDisplayType;
تعریفنوع HBITMAP EGLNativePixmapType;
تعریفنوع HWND    EGLNativeWindowType;

#وگرنهاگر defined(__QNX__)

تعریفنوع khronos_uintptr_t      EGLNativeDisplayType;
تعریفنوع ساختار _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
تعریفنوع ساختار _screen_window* EGLNativeWindowType;  /* screen_window_t */

#وگرنهاگر defined(__EMSCRIPTEN__)

تعریفنوع صحیح EGLNativeDisplayType;
تعریفنوع صحیح EGLNativePixmapType;
تعریفنوع صحیح EGLNativeWindowType;

#وگرنهاگر defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

تعریفنوع صحیح   EGLNativeDisplayType;
تعریفنوع تهی *EGLNativePixmapType;
تعریفنوع تهی *EGLNativeWindowType;

#وگرنهاگر defined(WL_EGL_PLATFORM)

تعریفنوع ساختار wl_display     *EGLNativeDisplayType;
تعریفنوع ساختار wl_egl_pixmap  *EGLNativePixmapType;
تعریفنوع ساختار wl_egl_window  *EGLNativeWindowType;

#وگرنهاگر defined(__GBM__)

تعریفنوع ساختار gbm_device  *EGLNativeDisplayType;
تعریفنوع ساختار gbm_bo      *EGLNativePixmapType;
تعریفنوع تهی               *EGLNativeWindowType;

#وگرنهاگر defined(__ANDROID__) || defined(ANDROID)

ساختار ANativeWindow;
ساختار egl_native_pixmap_t;

تعریفنوع تهی*                           EGLNativeDisplayType;
تعریفنوع ساختار egl_native_pixmap_t*     EGLNativePixmapType;
تعریفنوع ساختار ANativeWindow*           EGLNativeWindowType;

#وگرنهاگر defined(USE_OZONE)

تعریفنوع intptr_t EGLNativeDisplayType;
تعریفنوع intptr_t EGLNativePixmapType;
تعریفنوع intptr_t EGLNativeWindowType;

#وگرنهاگر defined(USE_X11)

/* X11 (tentative)  */
#شامل <X11/Xlib.h>
#شامل <X11/Xutil.h>

تعریفنوع Display *EGLNativeDisplayType;
تعریفنوع Pixmap   EGLNativePixmapType;
تعریفنوع Window   EGLNativeWindowType;

#وگرنهاگر defined(__unix__)

تعریفنوع تهی             *EGLNativeDisplayType;
تعریفنوع khronos_uintptr_t EGLNativePixmapType;
تعریفنوع khronos_uintptr_t EGLNativeWindowType;

#وگرنهاگر defined(__APPLE__)

تعریفنوع صحیح   EGLNativeDisplayType;
تعریفنوع تهی *EGLNativePixmapType;
تعریفنوع تهی *EGLNativeWindowType;

#وگرنهاگر defined(__HAIKU__)

#شامل <kernel/image.h>

تعریفنوع تهی              *EGLNativeDisplayType;
تعریفنوع khronos_uintptr_t  EGLNativePixmapType;
تعریفنوع khronos_uintptr_t  EGLNativeWindowType;

#وگرنهاگر defined(__Fuchsia__)

تعریفنوع تهی              *EGLNativeDisplayType;
تعریفنوع khronos_uintptr_t  EGLNativePixmapType;
تعریفنوع khronos_uintptr_t  EGLNativeWindowType;

#وگرنه
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
تعریفنوع EGLNativeDisplayType NativeDisplayType;
تعریفنوع EGLNativePixmapType  NativePixmapType;
تعریفنوع EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
تعریفنوع khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#اگر defined(__cplusplus)
#define EGL_CAST(type, مقدار) (static_cast<type>(مقدار))
#وگرنه
#define EGL_CAST(type, مقدار) ((type) (مقدار))
#endif

#endif /* __eglplatform_h */
