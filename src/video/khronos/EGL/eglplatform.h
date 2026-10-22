#اگر_غیر_تعریف_شدہ __eglplatform_h_
#تعریف_کرو __eglplatform_h_

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

#اگر_غیر_تعریف_شدہ EGLAPI
#تعریف_کرو EGLAPI KHRONOS_APICALL
#اگر_ختم

#اگر_غیر_تعریف_شدہ EGLAPIENTRY
#تعریف_کرو EGLAPIENTRY  KHRONOS_APIENTRY
#اگر_ختم
#تعریف_کرو EGLAPIENTRYP EGLAPIENTRY*

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

قسمتعریف خالی *EGLNativeDisplayType;
قسمتعریف خالی *EGLNativePixmapType;
قسمتعریف خالی *EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#اگر_غیر_تعریف_شدہ WIN32_LEAN_AND_اوسط
#تعریف_کرو WIN32_LEAN_AND_اوسط 1
#اگر_ختم
#شامل <windows.h>

قسمتعریف HDC     EGLNativeDisplayType;
قسمتعریف HBITMAP EGLNativePixmapType;
قسمتعریف HWND    EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__QNX__)

قسمتعریف khronos_uintptr_t      EGLNativeDisplayType;
قسمتعریف ساخت _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
قسمتعریف ساخت screen_کھڑکی* EGLNative_کھڑکی_Type;  /* screen_window_t */

#وگرنہ_اگر defined(__EMSCRIPTEN__)

قسمتعریف صحیح EGLNativeDisplayType;
قسمتعریف صحیح EGLNativePixmapType;
قسمتعریف صحیح EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

قسمتعریف صحیح   EGLNativeDisplayType;
قسمتعریف خالی *EGLNativePixmapType;
قسمتعریف خالی *EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(WL_EGL_PLATFORM)

قسمتعریف ساخت wl_display     *EGLNativeDisplayType;
قسمتعریف ساخت wl_egl_pixmap  *EGLNativePixmapType;
قسمتعریف ساخت wl_egl_کھڑکی  *EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__GBM__)

قسمتعریف ساخت gbm_device  *EGLNativeDisplayType;
قسمتعریف ساخت gbm_bo      *EGLNativePixmapType;
قسمتعریف خالی               *EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__ANDROID__) || defined(ANDROID)

ساخت ANative_کھڑکی;
ساخت egl_native_pixmap_t;

قسمتعریف خالی*                           EGLNativeDisplayType;
قسمتعریف ساخت egl_native_pixmap_t*     EGLNativePixmapType;
قسمتعریف ساخت ANative_کھڑکی*           EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(USE_OZONE)

قسمتعریف intptr_t EGLNativeDisplayType;
قسمتعریف intptr_t EGLNativePixmapType;
قسمتعریف intptr_t EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(USE_X11)

/* X11 (tentative)  */
#شامل <X11/Xlib.h>
#شامل <X11/Xutil.h>

قسمتعریف Display *EGLNativeDisplayType;
قسمتعریف Pixmap   EGLNativePixmapType;
قسمتعریف کھڑکی_2   EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__unix__)

قسمتعریف خالی             *EGLNativeDisplayType;
قسمتعریف khronos_uintptr_t EGLNativePixmapType;
قسمتعریف khronos_uintptr_t EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__APPLE__)

قسمتعریف صحیح   EGLNativeDisplayType;
قسمتعریف خالی *EGLNativePixmapType;
قسمتعریف خالی *EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__HAIKU__)

#شامل <kernel/image.h>

قسمتعریف خالی              *EGLNativeDisplayType;
قسمتعریف khronos_uintptr_t  EGLNativePixmapType;
قسمتعریف khronos_uintptr_t  EGLNative_کھڑکی_Type;

#وگرنہ_اگر defined(__Fuchsia__)

قسمتعریف خالی              *EGLNativeDisplayType;
قسمتعریف khronos_uintptr_t  EGLNativePixmapType;
قسمتعریف khronos_uintptr_t  EGLNative_کھڑکی_Type;

#ورنہ
#غلطی "Platform not recognized"
#اگر_ختم

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
قسمتعریف EGLNativeDisplayType NativeDisplayType;
قسمتعریف EGLNativePixmapType  NativePixmapType;
قسمتعریف EGLNative_کھڑکی_Type  Native_کھڑکی_Type;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
قسمتعریف khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#اگر defined(__cplusplus)
#تعریف_کرو EGL_CAST(type, قدر) (static_cast<type>(قدر))
#ورنہ
#تعریف_کرو EGL_CAST(type, قدر) ((type) (قدر))
#اگر_ختم

#اگر_ختم /* __eglplatform_h */
