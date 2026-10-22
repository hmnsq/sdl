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

#அந்தர்பாவ <KHR/khrplatform.h>

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

#எனில் defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

வகைவரை வெறுமை *EGLNativeDisplayType;
வகைவரை வெறுமை *EGLNativePixmapType;
வகைவரை வெறுமை *EGLNativeWindowType;

#அல்லதெனில் defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#அந்தர்பாவ <windows.h>

வகைவரை HDC     EGLNativeDisplayType;
வகைவரை HBITMAP EGLNativePixmapType;
வகைவரை HWND    EGLNativeWindowType;

#அல்லதெனில் defined(__QNX__)

வகைவரை khronos_uintptr_t      EGLNativeDisplayType;
வகைவரை கட்டமைப்பு _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
வகைவரை கட்டமைப்பு _screen_window* EGLNativeWindowType;  /* screen_window_t */

#அல்லதெனில் defined(__EMSCRIPTEN__)

வகைவரை முழு EGLNativeDisplayType;
வகைவரை முழு EGLNativePixmapType;
வகைவரை முழு EGLNativeWindowType;

#அல்லதெனில் defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

வகைவரை முழு   EGLNativeDisplayType;
வகைவரை வெறுமை *EGLNativePixmapType;
வகைவரை வெறுமை *EGLNativeWindowType;

#அல்லதெனில் defined(WL_EGL_PLATFORM)

வகைவரை கட்டமைப்பு wl_display     *EGLNativeDisplayType;
வகைவரை கட்டமைப்பு wl_egl_pixmap  *EGLNativePixmapType;
வகைவரை கட்டமைப்பு wl_egl_window  *EGLNativeWindowType;

#அல்லதெனில் defined(__GBM__)

வகைவரை கட்டமைப்பு gbm_device  *EGLNativeDisplayType;
வகைவரை கட்டமைப்பு gbm_bo      *EGLNativePixmapType;
வகைவரை வெறுமை               *EGLNativeWindowType;

#அல்லதெனில் defined(__ANDROID__) || defined(ANDROID)

கட்டமைப்பு ANativeWindow;
கட்டமைப்பு egl_native_pixmap_t;

வகைவரை வெறுமை*                           EGLNativeDisplayType;
வகைவரை கட்டமைப்பு egl_native_pixmap_t*     EGLNativePixmapType;
வகைவரை கட்டமைப்பு ANativeWindow*           EGLNativeWindowType;

#அல்லதெனில் defined(USE_OZONE)

வகைவரை intptr_t EGLNativeDisplayType;
வகைவரை intptr_t EGLNativePixmapType;
வகைவரை intptr_t EGLNativeWindowType;

#அல்லதெனில் defined(USE_X11)

/* X11 (tentative)  */
#அந்தர்பாவ <X11/Xlib.h>
#அந்தர்பாவ <X11/Xutil.h>

வகைவரை Display *EGLNativeDisplayType;
வகைவரை Pixmap   EGLNativePixmapType;
வகைவரை Window   EGLNativeWindowType;

#அல்லதெனில் defined(__unix__)

வகைவரை வெறுமை             *EGLNativeDisplayType;
வகைவரை khronos_uintptr_t EGLNativePixmapType;
வகைவரை khronos_uintptr_t EGLNativeWindowType;

#அல்லதெனில் defined(__APPLE__)

வகைவரை முழு   EGLNativeDisplayType;
வகைவரை வெறுமை *EGLNativePixmapType;
வகைவரை வெறுமை *EGLNativeWindowType;

#அல்லதெனில் defined(__HAIKU__)

#அந்தர்பாவ <kernel/image.h>

வகைவரை வெறுமை              *EGLNativeDisplayType;
வகைவரை khronos_uintptr_t  EGLNativePixmapType;
வகைவரை khronos_uintptr_t  EGLNativeWindowType;

#அல்லதெனில் defined(__Fuchsia__)

வகைவரை வெறுமை              *EGLNativeDisplayType;
வகைவரை khronos_uintptr_t  EGLNativePixmapType;
வகைவரை khronos_uintptr_t  EGLNativeWindowType;

#இல்லையெனில்
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
வகைவரை EGLNativeDisplayType NativeDisplayType;
வகைவரை EGLNativePixmapType  NativePixmapType;
வகைவரை EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
வகைவரை khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#எனில் defined(__cplusplus)
#define EGL_CAST(type, மதிப்பு) (static_cast<type>(மதிப்பு))
#இல்லையெனில்
#define EGL_CAST(type, மதிப்பு) ((type) (மதிப்பு))
#endif

#endif /* __eglplatform_h */
