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

#जइ defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

प्रकारनिर्देश शून्य *EGLNativeDisplayType;
प्रकारनिर्देश शून्य *EGLNativePixmapType;
प्रकारनिर्देश शून्य *EGLNativeWindowType;

#नोचेद्यदि defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#अन्तर्भाव <windows.h>

प्रकारनिर्देश HDC     EGLNativeDisplayType;
प्रकारनिर्देश HBITMAP EGLNativePixmapType;
प्रकारनिर्देश HWND    EGLNativeWindowType;

#नोचेद्यदि defined(__QNX__)

प्रकारनिर्देश khronos_uintptr_t      EGLNativeDisplayType;
प्रकारनिर्देश संरचना _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
प्रकारनिर्देश संरचना _screen_window* EGLNativeWindowType;  /* screen_window_t */

#नोचेद्यदि defined(__EMSCRIPTEN__)

प्रकारनिर्देश पूर्णाङ्क EGLNativeDisplayType;
प्रकारनिर्देश पूर्णाङ्क EGLNativePixmapType;
प्रकारनिर्देश पूर्णाङ्क EGLNativeWindowType;

#नोचेद्यदि defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

प्रकारनिर्देश पूर्णाङ्क   EGLNativeDisplayType;
प्रकारनिर्देश शून्य *EGLNativePixmapType;
प्रकारनिर्देश शून्य *EGLNativeWindowType;

#नोचेद्यदि defined(WL_EGL_PLATFORM)

प्रकारनिर्देश संरचना wl_display     *EGLNativeDisplayType;
प्रकारनिर्देश संरचना wl_egl_pixmap  *EGLNativePixmapType;
प्रकारनिर्देश संरचना wl_egl_window  *EGLNativeWindowType;

#नोचेद्यदि defined(__GBM__)

प्रकारनिर्देश संरचना gbm_device  *EGLNativeDisplayType;
प्रकारनिर्देश संरचना gbm_bo      *EGLNativePixmapType;
प्रकारनिर्देश शून्य               *EGLNativeWindowType;

#नोचेद्यदि defined(__ANDROID__) || defined(ANDROID)

संरचना ANativeWindow;
संरचना egl_native_pixmap_t;

प्रकारनिर्देश शून्य*                           EGLNativeDisplayType;
प्रकारनिर्देश संरचना egl_native_pixmap_t*     EGLNativePixmapType;
प्रकारनिर्देश संरचना ANativeWindow*           EGLNativeWindowType;

#नोचेद्यदि defined(USE_OZONE)

प्रकारनिर्देश intptr_t EGLNativeDisplayType;
प्रकारनिर्देश intptr_t EGLNativePixmapType;
प्रकारनिर्देश intptr_t EGLNativeWindowType;

#नोचेद्यदि defined(USE_X11)

/* X11 (tentative)  */
#अन्तर्भाव <X11/Xlib.h>
#अन्तर्भाव <X11/Xutil.h>

प्रकारनिर्देश Display *EGLNativeDisplayType;
प्रकारनिर्देश Pixmap   EGLNativePixmapType;
प्रकारनिर्देश Window   EGLNativeWindowType;

#नोचेद्यदि defined(__unix__)

प्रकारनिर्देश शून्य             *EGLNativeDisplayType;
प्रकारनिर्देश khronos_uintptr_t EGLNativePixmapType;
प्रकारनिर्देश khronos_uintptr_t EGLNativeWindowType;

#नोचेद्यदि defined(__APPLE__)

प्रकारनिर्देश पूर्णाङ्क   EGLNativeDisplayType;
प्रकारनिर्देश शून्य *EGLNativePixmapType;
प्रकारनिर्देश शून्य *EGLNativeWindowType;

#नोचेद्यदि defined(__HAIKU__)

#अन्तर्भाव <kernel/image.h>

प्रकारनिर्देश शून्य              *EGLNativeDisplayType;
प्रकारनिर्देश khronos_uintptr_t  EGLNativePixmapType;
प्रकारनिर्देश khronos_uintptr_t  EGLNativeWindowType;

#नोचेद्यदि defined(__Fuchsia__)

प्रकारनिर्देश शून्य              *EGLNativeDisplayType;
प्रकारनिर्देश khronos_uintptr_t  EGLNativePixmapType;
प्रकारनिर्देश khronos_uintptr_t  EGLNativeWindowType;

#अण्णहा
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
प्रकारनिर्देश EGLNativeDisplayType NativeDisplayType;
प्रकारनिर्देश EGLNativePixmapType  NativePixmapType;
प्रकारनिर्देश EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
प्रकारनिर्देश khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#जइ defined(__cplusplus)
#define EGL_CAST(type, मानम्) (static_cast<type>(मानम्))
#अण्णहा
#define EGL_CAST(type, मानम्) ((type) (मानम्))
#endif

#endif /* __eglplatform_h */
