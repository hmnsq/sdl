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

#ಅನ್ತರ್ಭಾವ <KHR/khrplatform.h>

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

#ಯದಿ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ಅನ್ತರ್ಭಾವ <windows.h>

ಪ್ರಕಾರನಿರ್ದೇಶ HDC     EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ HBITMAP EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ HWND    EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__QNX__)

ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t      EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _screen_window* EGLNativeWindowType;  /* screen_window_t */

#ನೋಚೇದ್ಯದಿ defined(__EMSCRIPTEN__)

ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ   EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(WL_EGL_PLATFORM)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ wl_display     *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ wl_egl_pixmap  *EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ wl_egl_window  *EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__GBM__)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ gbm_device  *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ gbm_bo      *EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ               *EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__ANDROID__) || defined(ANDROID)

ಸಂರಚನಾ ANativeWindow;
ಸಂರಚನಾ egl_native_pixmap_t;

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ*                           EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ egl_native_pixmap_t*     EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ANativeWindow*           EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(USE_OZONE)

ಪ್ರಕಾರನಿರ್ದೇಶ intptr_t EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ intptr_t EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ intptr_t EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(USE_X11)

/* X11 (tentative)  */
#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ <X11/Xutil.h>

ಪ್ರಕಾರನಿರ್ದೇಶ Display *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ Pixmap   EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ Window   EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__unix__)

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ             *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__APPLE__)

ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ   EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__HAIKU__)

#ಅನ್ತರ್ಭಾವ <kernel/image.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ              *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t  EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t  EGLNativeWindowType;

#ನೋಚೇದ್ಯದಿ defined(__Fuchsia__)

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ              *EGLNativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t  EGLNativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_uintptr_t  EGLNativeWindowType;

#ಅನ್ಯಥಾ
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
ಪ್ರಕಾರನಿರ್ದೇಶ EGLNativeDisplayType NativeDisplayType;
ಪ್ರಕಾರನಿರ್ದೇಶ EGLNativePixmapType  NativePixmapType;
ಪ್ರಕಾರನಿರ್ದೇಶ EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
ಪ್ರಕಾರನಿರ್ದೇಶ khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#ಯದಿ defined(__cplusplus)
#define EGL_CAST(type, ಮೌಲ್ಯ) (static_cast<type>(ಮೌಲ್ಯ))
#ಅನ್ಯಥಾ
#define EGL_CAST(type, ಮೌಲ್ಯ) ((type) (ಮೌಲ್ಯ))
#endif

#endif /* __eglplatform_h */
