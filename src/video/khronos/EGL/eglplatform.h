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

#অন্তর্ভাব <KHR/khrplatform.h>

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

#যদি defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

প্রকারলেখ শূন্য *EGLNativeDisplayType;
প্রকারলেখ শূন্য *EGLNativePixmapType;
প্রকারলেখ শূন্য *EGLNativeWindowType;

#নতুবা_যদি defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#অন্তর্ভাব <windows.h>

প্রকারলেখ HDC     EGLNativeDisplayType;
প্রকারলেখ HBITMAP EGLNativePixmapType;
প্রকারলেখ HWND    EGLNativeWindowType;

#নতুবা_যদি defined(__QNX__)

প্রকারলেখ khronos_uintptr_t      EGLNativeDisplayType;
প্রকারলেখ কাঠামো _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
প্রকারলেখ কাঠামো _screen_window* EGLNativeWindowType;  /* screen_window_t */

#নতুবা_যদি defined(__EMSCRIPTEN__)

প্রকারলেখ পূর্ণসংখ্যা EGLNativeDisplayType;
প্রকারলেখ পূর্ণসংখ্যা EGLNativePixmapType;
প্রকারলেখ পূর্ণসংখ্যা EGLNativeWindowType;

#নতুবা_যদি defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

প্রকারলেখ পূর্ণসংখ্যা   EGLNativeDisplayType;
প্রকারলেখ শূন্য *EGLNativePixmapType;
প্রকারলেখ শূন্য *EGLNativeWindowType;

#নতুবা_যদি defined(WL_EGL_PLATFORM)

প্রকারলেখ কাঠামো wl_display     *EGLNativeDisplayType;
প্রকারলেখ কাঠামো wl_egl_pixmap  *EGLNativePixmapType;
প্রকারলেখ কাঠামো wl_egl_window  *EGLNativeWindowType;

#নতুবা_যদি defined(__GBM__)

প্রকারলেখ কাঠামো gbm_device  *EGLNativeDisplayType;
প্রকারলেখ কাঠামো gbm_bo      *EGLNativePixmapType;
প্রকারলেখ শূন্য               *EGLNativeWindowType;

#নতুবা_যদি defined(__ANDROID__) || defined(ANDROID)

কাঠামো ANativeWindow;
কাঠামো egl_native_pixmap_t;

প্রকারলেখ শূন্য*                           EGLNativeDisplayType;
প্রকারলেখ কাঠামো egl_native_pixmap_t*     EGLNativePixmapType;
প্রকারলেখ কাঠামো ANativeWindow*           EGLNativeWindowType;

#নতুবা_যদি defined(USE_OZONE)

প্রকারলেখ intptr_t EGLNativeDisplayType;
প্রকারলেখ intptr_t EGLNativePixmapType;
প্রকারলেখ intptr_t EGLNativeWindowType;

#নতুবা_যদি defined(USE_X11)

/* X11 (tentative)  */
#অন্তর্ভাব <X11/Xlib.h>
#অন্তর্ভাব <X11/Xutil.h>

প্রকারলেখ Display *EGLNativeDisplayType;
প্রকারলেখ Pixmap   EGLNativePixmapType;
প্রকারলেখ Window   EGLNativeWindowType;

#নতুবা_যদি defined(__unix__)

প্রকারলেখ শূন্য             *EGLNativeDisplayType;
প্রকারলেখ khronos_uintptr_t EGLNativePixmapType;
প্রকারলেখ khronos_uintptr_t EGLNativeWindowType;

#নতুবা_যদি defined(__APPLE__)

প্রকারলেখ পূর্ণসংখ্যা   EGLNativeDisplayType;
প্রকারলেখ শূন্য *EGLNativePixmapType;
প্রকারলেখ শূন্য *EGLNativeWindowType;

#নতুবা_যদি defined(__HAIKU__)

#অন্তর্ভাব <kernel/image.h>

প্রকারলেখ শূন্য              *EGLNativeDisplayType;
প্রকারলেখ khronos_uintptr_t  EGLNativePixmapType;
প্রকারলেখ khronos_uintptr_t  EGLNativeWindowType;

#নতুবা_যদি defined(__Fuchsia__)

প্রকারলেখ শূন্য              *EGLNativeDisplayType;
প্রকারলেখ khronos_uintptr_t  EGLNativePixmapType;
প্রকারলেখ khronos_uintptr_t  EGLNativeWindowType;

#অন্যথা
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
প্রকারলেখ EGLNativeDisplayType NativeDisplayType;
প্রকারলেখ EGLNativePixmapType  NativePixmapType;
প্রকারলেখ EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
প্রকারলেখ khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#যদি defined(__cplusplus)
#define EGL_CAST(type, মান) (static_cast<type>(মান))
#অন্যথা
#define EGL_CAST(type, মান) ((type) (মান))
#endif

#endif /* __eglplatform_h */
