#अगर_अघोषित __eglplatform_h_
#घोषणा __eglplatform_h_

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

#समावेश <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#अगर_अघोषित EGLAPI
#घोषणा EGLAPI KHRONOS_APICALL
#पूर्ण_अगर

#अगर_अघोषित EGLAPIENTRY
#घोषणा EGLAPIENTRY  KHRONOS_APIENTRY
#पूर्ण_अगर
#घोषणा EGLAPIENTRYP EGLAPIENTRY*

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

#अगर defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

प्रकार व्योम *EGLNativeDisplayType;
प्रकार व्योम *EGLNativePixmapType;
प्रकार व्योम *EGLNativeWindowType;

#या_अगर defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#अगर_अघोषित WIN32_LEAN_AND_MEAN
#घोषणा WIN32_LEAN_AND_MEAN 1
#पूर्ण_अगर
#समावेश <windows.h>

प्रकार HDC     EGLNativeDisplayType;
प्रकार HBITMAP EGLNativePixmapType;
प्रकार HWND    EGLNativeWindowType;

#या_अगर defined(__QNX__)

प्रकार khronos_uintptr_t      EGLNativeDisplayType;
प्रकार काष्ठा _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
प्रकार काष्ठा _screen_window* EGLNativeWindowType;  /* screen_window_t */

#या_अगर defined(__EMSCRIPTEN__)

प्रकार पूर्णांक EGLNativeDisplayType;
प्रकार पूर्णांक EGLNativePixmapType;
प्रकार पूर्णांक EGLNativeWindowType;

#या_अगर defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

प्रकार पूर्णांक   EGLNativeDisplayType;
प्रकार व्योम *EGLNativePixmapType;
प्रकार व्योम *EGLNativeWindowType;

#या_अगर defined(WL_EGL_PLATFORM)

प्रकार काष्ठा wl_display     *EGLNativeDisplayType;
प्रकार काष्ठा wl_egl_pixmap  *EGLNativePixmapType;
प्रकार काष्ठा wl_egl_window  *EGLNativeWindowType;

#या_अगर defined(__GBM__)

प्रकार काष्ठा gbm_device  *EGLNativeDisplayType;
प्रकार काष्ठा gbm_bo      *EGLNativePixmapType;
प्रकार व्योम               *EGLNativeWindowType;

#या_अगर defined(__ANDROID__) || defined(ANDROID)

काष्ठा ANativeWindow;
काष्ठा egl_native_pixmap_t;

प्रकार व्योम*                           EGLNativeDisplayType;
प्रकार काष्ठा egl_native_pixmap_t*     EGLNativePixmapType;
प्रकार काष्ठा ANativeWindow*           EGLNativeWindowType;

#या_अगर defined(USE_OZONE)

प्रकार intptr_t EGLNativeDisplayType;
प्रकार intptr_t EGLNativePixmapType;
प्रकार intptr_t EGLNativeWindowType;

#या_अगर defined(USE_X11)

/* X11 (tentative)  */
#समावेश <X11/Xlib.h>
#समावेश <X11/Xutil.h>

प्रकार Display *EGLNativeDisplayType;
प्रकार Pixmap   EGLNativePixmapType;
प्रकार Window   EGLNativeWindowType;

#या_अगर defined(__unix__)

प्रकार व्योम             *EGLNativeDisplayType;
प्रकार khronos_uintptr_t EGLNativePixmapType;
प्रकार khronos_uintptr_t EGLNativeWindowType;

#या_अगर defined(__APPLE__)

प्रकार पूर्णांक   EGLNativeDisplayType;
प्रकार व्योम *EGLNativePixmapType;
प्रकार व्योम *EGLNativeWindowType;

#या_अगर defined(__HAIKU__)

#समावेश <kernel/image.h>

प्रकार व्योम              *EGLNativeDisplayType;
प्रकार khronos_uintptr_t  EGLNativePixmapType;
प्रकार khronos_uintptr_t  EGLNativeWindowType;

#या_अगर defined(__Fuchsia__)

प्रकार व्योम              *EGLNativeDisplayType;
प्रकार khronos_uintptr_t  EGLNativePixmapType;
प्रकार khronos_uintptr_t  EGLNativeWindowType;

#अन्यथा
#त्रुटि "Platform not recognized"
#पूर्ण_अगर

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
प्रकार EGLNativeDisplayType NativeDisplayType;
प्रकार EGLNativePixmapType  NativePixmapType;
प्रकार EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
प्रकार khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#अगर defined(__cplusplus)
#घोषणा EGL_CAST(type, मूल्य) (static_cast<type>(मूल्य))
#अन्यथा
#घोषणा EGL_CAST(type, मूल्य) ((type) (मूल्य))
#पूर्ण_अगर

#पूर्ण_अगर /* __eglplatform_h */
