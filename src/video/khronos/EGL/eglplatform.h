#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __eglplatform_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __eglplatform_h_

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

#ਅਨ੍ਤਰ੍ਭਾਵ <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGLAPI
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLAPI KHRONOS_APICALL
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGLAPIENTRY
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLAPIENTRY  KHRONOS_APIENTRY
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLAPIENTRYP EGLAPIENTRY*

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

#ਜੇ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIN32_LEAN_AND_ਔਸਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WIN32_LEAN_AND_ਔਸਤ 1
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ HDC     EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ HBITMAP EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ HWND    EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__QNX__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t      EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ screen_ਖਿੜਕੀ* EGLNative_ਖਿੜਕੀ_Type;  /* screen_window_t */

#ਜਾਂਜੇ defined(__EMSCRIPTEN__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ   EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(WL_EGL_PLATFORM)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ wl_display     *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ wl_egl_pixmap  *EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ wl_egl_ਖਿੜਕੀ  *EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__GBM__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ gbm_device  *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ gbm_bo      *EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ               *EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__ANDROID__) || defined(ANDROID)

ਬਣਤਰ ANative_ਖਿੜਕੀ;
ਬਣਤਰ egl_native_pixmap_t;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ*                           EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ egl_native_pixmap_t*     EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ANative_ਖਿੜਕੀ*           EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(USE_OZONE)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(USE_X11)

/* X11 (tentative)  */
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xutil.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Display *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Pixmap   EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਿੜਕੀ_2   EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__unix__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ             *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__APPLE__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ   EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__HAIKU__)

#ਅਨ੍ਤਰ੍ਭਾਵ <kernel/image.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ              *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t  EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t  EGLNative_ਖਿੜਕੀ_Type;

#ਜਾਂਜੇ defined(__Fuchsia__)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ              *EGLNativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t  EGLNativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uintptr_t  EGLNative_ਖਿੜਕੀ_Type;

#ਨਹੀਂਤਾਂ
#ਗਲਤੀ "Platform not recognized"
#ਜੇ_ਅੰਤ

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLNativeDisplayType NativeDisplayType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLNativePixmapType  NativePixmapType;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLNative_ਖਿੜਕੀ_Type  Native_ਖਿੜਕੀ_Type;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#ਜੇ defined(__cplusplus)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CAST(type, ਮੁੱਲ) (static_cast<type>(ਮੁੱਲ))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CAST(type, ਮੁੱਲ) ((type) (ਮੁੱਲ))
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* __eglplatform_h */
