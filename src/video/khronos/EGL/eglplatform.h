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

#അന്തര്ഭാവ <KHR/khrplatform.h>

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

#എങ്കിൽ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

തരനിർവചനം ശൂന്യം *EGLNativeDisplayType;
തരനിർവചനം ശൂന്യം *EGLNativePixmapType;
തരനിർവചനം ശൂന്യം *EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#അന്തര്ഭാവ <windows.h>

തരനിർവചനം HDC     EGLNativeDisplayType;
തരനിർവചനം HBITMAP EGLNativePixmapType;
തരനിർവചനം HWND    EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__QNX__)

തരനിർവചനം khronos_uintptr_t      EGLNativeDisplayType;
തരനിർവചനം ഘടന _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
തരനിർവചനം ഘടന _screen_window* EGLNativeWindowType;  /* screen_window_t */

#അല്ലെങ്കിലെങ്കിൽ defined(__EMSCRIPTEN__)

തരനിർവചനം പൂർണ്ണസംഖ്യ EGLNativeDisplayType;
തരനിർവചനം പൂർണ്ണസംഖ്യ EGLNativePixmapType;
തരനിർവചനം പൂർണ്ണസംഖ്യ EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

തരനിർവചനം പൂർണ്ണസംഖ്യ   EGLNativeDisplayType;
തരനിർവചനം ശൂന്യം *EGLNativePixmapType;
തരനിർവചനം ശൂന്യം *EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(WL_EGL_PLATFORM)

തരനിർവചനം ഘടന wl_display     *EGLNativeDisplayType;
തരനിർവചനം ഘടന wl_egl_pixmap  *EGLNativePixmapType;
തരനിർവചനം ഘടന wl_egl_window  *EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__GBM__)

തരനിർവചനം ഘടന gbm_device  *EGLNativeDisplayType;
തരനിർവചനം ഘടന gbm_bo      *EGLNativePixmapType;
തരനിർവചനം ശൂന്യം               *EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__ANDROID__) || defined(ANDROID)

ഘടന ANativeWindow;
ഘടന egl_native_pixmap_t;

തരനിർവചനം ശൂന്യം*                           EGLNativeDisplayType;
തരനിർവചനം ഘടന egl_native_pixmap_t*     EGLNativePixmapType;
തരനിർവചനം ഘടന ANativeWindow*           EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(USE_OZONE)

തരനിർവചനം intptr_t EGLNativeDisplayType;
തരനിർവചനം intptr_t EGLNativePixmapType;
തരനിർവചനം intptr_t EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(USE_X11)

/* X11 (tentative)  */
#അന്തര്ഭാവ <X11/Xlib.h>
#അന്തര്ഭാവ <X11/Xutil.h>

തരനിർവചനം Display *EGLNativeDisplayType;
തരനിർവചനം Pixmap   EGLNativePixmapType;
തരനിർവചനം Window   EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__unix__)

തരനിർവചനം ശൂന്യം             *EGLNativeDisplayType;
തരനിർവചനം khronos_uintptr_t EGLNativePixmapType;
തരനിർവചനം khronos_uintptr_t EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__APPLE__)

തരനിർവചനം പൂർണ്ണസംഖ്യ   EGLNativeDisplayType;
തരനിർവചനം ശൂന്യം *EGLNativePixmapType;
തരനിർവചനം ശൂന്യം *EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__HAIKU__)

#അന്തര്ഭാവ <kernel/image.h>

തരനിർവചനം ശൂന്യം              *EGLNativeDisplayType;
തരനിർവചനം khronos_uintptr_t  EGLNativePixmapType;
തരനിർവചനം khronos_uintptr_t  EGLNativeWindowType;

#അല്ലെങ്കിലെങ്കിൽ defined(__Fuchsia__)

തരനിർവചനം ശൂന്യം              *EGLNativeDisplayType;
തരനിർവചനം khronos_uintptr_t  EGLNativePixmapType;
തരനിർവചനം khronos_uintptr_t  EGLNativeWindowType;

#അല്ലെങ്കിൽ
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
തരനിർവചനം EGLNativeDisplayType NativeDisplayType;
തരനിർവചനം EGLNativePixmapType  NativePixmapType;
തരനിർവചനം EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
തരനിർവചനം khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#എങ്കിൽ defined(__cplusplus)
#define EGL_CAST(type, മൂല്യം) (static_cast<type>(മൂല്യം))
#അല്ലെങ്കിൽ
#define EGL_CAST(type, മൂല്യം) ((type) (മൂല്യം))
#endif

#endif /* __eglplatform_h */
