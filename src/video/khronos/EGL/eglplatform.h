#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __eglplatform_h_
#ವ್ಯಾಖ್ಯಾನಿಸು __eglplatform_h_

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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGLAPI
#ವ್ಯಾಖ್ಯಾನಿಸು EGLAPI KHRONOS_APICALL
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGLAPIENTRY
#ವ್ಯಾಖ್ಯಾನಿಸು EGLAPIENTRY  KHRONOS_APIENTRY
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGLAPIENTRYP EGLAPIENTRY*

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

#ಆದರೆ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIN32_LEAN_AND_ಸರಾಸರಿ
#ವ್ಯಾಖ್ಯಾನಿಸು WIN32_LEAN_AND_ಸರಾಸರಿ 1
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <windows.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HDC     EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HBITMAP EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HWND    EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__QNX__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t      EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ screen_ಕಿಟಕಿ* EGLNative_ಕಿಟಕಿ_Type;  /* screen_window_t */

#ಅಥವಾಆದರೆ defined(__EMSCRIPTEN__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ   EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(WL_EGL_PLATFORM)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ wl_display     *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ wl_egl_pixmap  *EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ wl_egl_ಕಿಟಕಿ  *EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__GBM__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ gbm_device  *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ gbm_bo      *EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ               *EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__ANDROID__) || defined(ANDROID)

ರಚನೆ ANative_ಕಿಟಕಿ;
ರಚನೆ egl_native_pixmap_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ*                           EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ egl_native_pixmap_t*     EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ANative_ಕಿಟಕಿ*           EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(USE_OZONE)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(USE_X11)

/* X11 (tentative)  */
#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>
#ಅನ್ತರ್ಭಾವ <X11/Xutil.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Display *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Pixmap   EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಕಿಟಕಿ_2   EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__unix__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ             *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__APPLE__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ   EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__HAIKU__)

#ಅನ್ತರ್ಭಾವ <kernel/image.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ              *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t  EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t  EGLNative_ಕಿಟಕಿ_Type;

#ಅಥವಾಆದರೆ defined(__Fuchsia__)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ              *EGLNativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t  EGLNativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uintptr_t  EGLNative_ಕಿಟಕಿ_Type;

#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ "Platform not recognized"
#ಆದರೆ_ಅಂತ್ಯ

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLNativeDisplayType NativeDisplayType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLNativePixmapType  NativePixmapType;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLNative_ಕಿಟಕಿ_Type  Native_ಕಿಟಕಿ_Type;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#ಆದರೆ defined(__cplusplus)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CAST(type, ಮೌಲ್ಯ) (static_cast<type>(ಮೌಲ್ಯ))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CAST(type, ಮೌಲ್ಯ) ((type) (ಮೌಲ್ಯ))
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* __eglplatform_h */
