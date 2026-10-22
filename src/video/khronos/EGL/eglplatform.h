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

#अन्तर्भाव <KHR/khrplatform.h>

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

#जर defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

प्रकारव्याख्या शून्य *EGLNativeDisplayType;
प्रकारव्याख्या शून्य *EGLNativePixmapType;
प्रकारव्याख्या शून्य *EGLNativeWindowType;

#किंवाजर defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#अन्तर्भाव <windows.h>

प्रकारव्याख्या HDC     EGLNativeDisplayType;
प्रकारव्याख्या HBITMAP EGLNativePixmapType;
प्रकारव्याख्या HWND    EGLNativeWindowType;

#किंवाजर defined(__QNX__)

प्रकारव्याख्या khronos_uintptr_t      EGLNativeDisplayType;
प्रकारव्याख्या संरचना _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
प्रकारव्याख्या संरचना _screen_window* EGLNativeWindowType;  /* screen_window_t */

#किंवाजर defined(__EMSCRIPTEN__)

प्रकारव्याख्या पूर्णांक EGLNativeDisplayType;
प्रकारव्याख्या पूर्णांक EGLNativePixmapType;
प्रकारव्याख्या पूर्णांक EGLNativeWindowType;

#किंवाजर defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

प्रकारव्याख्या पूर्णांक   EGLNativeDisplayType;
प्रकारव्याख्या शून्य *EGLNativePixmapType;
प्रकारव्याख्या शून्य *EGLNativeWindowType;

#किंवाजर defined(WL_EGL_PLATFORM)

प्रकारव्याख्या संरचना wl_display     *EGLNativeDisplayType;
प्रकारव्याख्या संरचना wl_egl_pixmap  *EGLNativePixmapType;
प्रकारव्याख्या संरचना wl_egl_window  *EGLNativeWindowType;

#किंवाजर defined(__GBM__)

प्रकारव्याख्या संरचना gbm_device  *EGLNativeDisplayType;
प्रकारव्याख्या संरचना gbm_bo      *EGLNativePixmapType;
प्रकारव्याख्या शून्य               *EGLNativeWindowType;

#किंवाजर defined(__ANDROID__) || defined(ANDROID)

संरचना ANativeWindow;
संरचना egl_native_pixmap_t;

प्रकारव्याख्या शून्य*                           EGLNativeDisplayType;
प्रकारव्याख्या संरचना egl_native_pixmap_t*     EGLNativePixmapType;
प्रकारव्याख्या संरचना ANativeWindow*           EGLNativeWindowType;

#किंवाजर defined(USE_OZONE)

प्रकारव्याख्या intptr_t EGLNativeDisplayType;
प्रकारव्याख्या intptr_t EGLNativePixmapType;
प्रकारव्याख्या intptr_t EGLNativeWindowType;

#किंवाजर defined(USE_X11)

/* X11 (tentative)  */
#अन्तर्भाव <X11/Xlib.h>
#अन्तर्भाव <X11/Xutil.h>

प्रकारव्याख्या Display *EGLNativeDisplayType;
प्रकारव्याख्या Pixmap   EGLNativePixmapType;
प्रकारव्याख्या Window   EGLNativeWindowType;

#किंवाजर defined(__unix__)

प्रकारव्याख्या शून्य             *EGLNativeDisplayType;
प्रकारव्याख्या khronos_uintptr_t EGLNativePixmapType;
प्रकारव्याख्या khronos_uintptr_t EGLNativeWindowType;

#किंवाजर defined(__APPLE__)

प्रकारव्याख्या पूर्णांक   EGLNativeDisplayType;
प्रकारव्याख्या शून्य *EGLNativePixmapType;
प्रकारव्याख्या शून्य *EGLNativeWindowType;

#किंवाजर defined(__HAIKU__)

#अन्तर्भाव <kernel/image.h>

प्रकारव्याख्या शून्य              *EGLNativeDisplayType;
प्रकारव्याख्या khronos_uintptr_t  EGLNativePixmapType;
प्रकारव्याख्या khronos_uintptr_t  EGLNativeWindowType;

#किंवाजर defined(__Fuchsia__)

प्रकारव्याख्या शून्य              *EGLNativeDisplayType;
प्रकारव्याख्या khronos_uintptr_t  EGLNativePixmapType;
प्रकारव्याख्या khronos_uintptr_t  EGLNativeWindowType;

#अन्यथा
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
प्रकारव्याख्या EGLNativeDisplayType NativeDisplayType;
प्रकारव्याख्या EGLNativePixmapType  NativePixmapType;
प्रकारव्याख्या EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
प्रकारव्याख्या khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#जर defined(__cplusplus)
#define EGL_CAST(type, मूल्य) (static_cast<type>(मूल्य))
#अन्यथा
#define EGL_CAST(type, मूल्य) ((type) (मूल्य))
#endif

#endif /* __eglplatform_h */
