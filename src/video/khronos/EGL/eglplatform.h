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

#અન્તર્ભાવ <KHR/khrplatform.h>

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

#જો defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

પ્રકારવ્યાખ્યા શૂન્ય *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativePixmapType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativeWindowType;

#અથવાજો defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#અન્તર્ભાવ <windows.h>

પ્રકારવ્યાખ્યા HDC     EGLNativeDisplayType;
પ્રકારવ્યાખ્યા HBITMAP EGLNativePixmapType;
પ્રકારવ્યાખ્યા HWND    EGLNativeWindowType;

#અથવાજો defined(__QNX__)

પ્રકારવ્યાખ્યા khronos_uintptr_t      EGLNativeDisplayType;
પ્રકારવ્યાખ્યા સંરચના _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
પ્રકારવ્યાખ્યા સંરચના _screen_window* EGLNativeWindowType;  /* screen_window_t */

#અથવાજો defined(__EMSCRIPTEN__)

પ્રકારવ્યાખ્યા પૂર્ણાંક EGLNativeDisplayType;
પ્રકારવ્યાખ્યા પૂર્ણાંક EGLNativePixmapType;
પ્રકારવ્યાખ્યા પૂર્ણાંક EGLNativeWindowType;

#અથવાજો defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

પ્રકારવ્યાખ્યા પૂર્ણાંક   EGLNativeDisplayType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativePixmapType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativeWindowType;

#અથવાજો defined(WL_EGL_PLATFORM)

પ્રકારવ્યાખ્યા સંરચના wl_display     *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા સંરચના wl_egl_pixmap  *EGLNativePixmapType;
પ્રકારવ્યાખ્યા સંરચના wl_egl_window  *EGLNativeWindowType;

#અથવાજો defined(__GBM__)

પ્રકારવ્યાખ્યા સંરચના gbm_device  *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા સંરચના gbm_bo      *EGLNativePixmapType;
પ્રકારવ્યાખ્યા શૂન્ય               *EGLNativeWindowType;

#અથવાજો defined(__ANDROID__) || defined(ANDROID)

સંરચના ANativeWindow;
સંરચના egl_native_pixmap_t;

પ્રકારવ્યાખ્યા શૂન્ય*                           EGLNativeDisplayType;
પ્રકારવ્યાખ્યા સંરચના egl_native_pixmap_t*     EGLNativePixmapType;
પ્રકારવ્યાખ્યા સંરચના ANativeWindow*           EGLNativeWindowType;

#અથવાજો defined(USE_OZONE)

પ્રકારવ્યાખ્યા intptr_t EGLNativeDisplayType;
પ્રકારવ્યાખ્યા intptr_t EGLNativePixmapType;
પ્રકારવ્યાખ્યા intptr_t EGLNativeWindowType;

#અથવાજો defined(USE_X11)

/* X11 (tentative)  */
#અન્તર્ભાવ <X11/Xlib.h>
#અન્તર્ભાવ <X11/Xutil.h>

પ્રકારવ્યાખ્યા Display *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા Pixmap   EGLNativePixmapType;
પ્રકારવ્યાખ્યા Window   EGLNativeWindowType;

#અથવાજો defined(__unix__)

પ્રકારવ્યાખ્યા શૂન્ય             *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા khronos_uintptr_t EGLNativePixmapType;
પ્રકારવ્યાખ્યા khronos_uintptr_t EGLNativeWindowType;

#અથવાજો defined(__APPLE__)

પ્રકારવ્યાખ્યા પૂર્ણાંક   EGLNativeDisplayType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativePixmapType;
પ્રકારવ્યાખ્યા શૂન્ય *EGLNativeWindowType;

#અથવાજો defined(__HAIKU__)

#અન્તર્ભાવ <kernel/image.h>

પ્રકારવ્યાખ્યા શૂન્ય              *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા khronos_uintptr_t  EGLNativePixmapType;
પ્રકારવ્યાખ્યા khronos_uintptr_t  EGLNativeWindowType;

#અથવાજો defined(__Fuchsia__)

પ્રકારવ્યાખ્યા શૂન્ય              *EGLNativeDisplayType;
પ્રકારવ્યાખ્યા khronos_uintptr_t  EGLNativePixmapType;
પ્રકારવ્યાખ્યા khronos_uintptr_t  EGLNativeWindowType;

#નહીંતર
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
પ્રકારવ્યાખ્યા EGLNativeDisplayType NativeDisplayType;
પ્રકારવ્યાખ્યા EGLNativePixmapType  NativePixmapType;
પ્રકારવ્યાખ્યા EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
પ્રકારવ્યાખ્યા khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#જો defined(__cplusplus)
#define EGL_CAST(type, કિંમત) (static_cast<type>(કિંમત))
#નહીંતર
#define EGL_CAST(type, કિંમત) ((type) (કિંમત))
#endif

#endif /* __eglplatform_h */
