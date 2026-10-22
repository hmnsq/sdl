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

#ଅନ୍ତର୍ଭାଵ <KHR/khrplatform.h>

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

#ଯଦି defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativeWindowType;

#ନଚେତଯଦି defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ଅନ୍ତର୍ଭାଵ <windows.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା HDC     EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା HBITMAP EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା HWND    EGLNativeWindowType;

#ନଚେତଯଦି defined(__QNX__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t      EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _screen_window* EGLNativeWindowType;  /* screen_window_t */

#ନଚେତଯଦି defined(__EMSCRIPTEN__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା EGLNativeWindowType;

#ନଚେତଯଦି defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା   EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativeWindowType;

#ନଚେତଯଦି defined(WL_EGL_PLATFORM)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା wl_display     *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା wl_egl_pixmap  *EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା wl_egl_window  *EGLNativeWindowType;

#ନଚେତଯଦି defined(__GBM__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା gbm_device  *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା gbm_bo      *EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ               *EGLNativeWindowType;

#ନଚେତଯଦି defined(__ANDROID__) || defined(ANDROID)

ସଂରଚନା ANativeWindow;
ସଂରଚନା egl_native_pixmap_t;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ*                           EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା egl_native_pixmap_t*     EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ANativeWindow*           EGLNativeWindowType;

#ନଚେତଯଦି defined(USE_OZONE)

ପ୍ରକାରବ୍ୟାଖ୍ୟା intptr_t EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା intptr_t EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା intptr_t EGLNativeWindowType;

#ନଚେତଯଦି defined(USE_X11)

/* X11 (tentative)  */
#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>
#ଅନ୍ତର୍ଭାଵ <X11/Xutil.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା Display *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା Pixmap   EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା Window   EGLNativeWindowType;

#ନଚେତଯଦି defined(__unix__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ             *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t EGLNativeWindowType;

#ନଚେତଯଦି defined(__APPLE__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା   EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLNativeWindowType;

#ନଚେତଯଦି defined(__HAIKU__)

#ଅନ୍ତର୍ଭାଵ <kernel/image.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ              *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t  EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t  EGLNativeWindowType;

#ନଚେତଯଦି defined(__Fuchsia__)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ              *EGLNativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t  EGLNativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uintptr_t  EGLNativeWindowType;

#ଅନ୍ୟଥା
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLNativeDisplayType NativeDisplayType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLNativePixmapType  NativePixmapType;
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#ଯଦି defined(__cplusplus)
#define EGL_CAST(type, ମୂଲ୍ୟ) (static_cast<type>(ମୂଲ୍ୟ))
#ଅନ୍ୟଥା
#define EGL_CAST(type, ମୂଲ୍ୟ) ((type) (ମୂଲ୍ୟ))
#endif

#endif /* __eglplatform_h */
