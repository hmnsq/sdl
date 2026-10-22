/*
 *  Simple DirectMedia Layer
 *  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS)
#ಅನ್ತರ್ಭಾವ "../core/windows/SDL_windows.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
#ಅನ್ತರ್ಭಾವ <android/native_window.h>
#ಅನ್ತರ್ಭಾವ "../video/android/SDL_androidvideo.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_QNX
#ಅನ್ತರ್ಭಾವ <screen/screen.h>
#ಅನ್ತರ್ಭಾವ "../video/qnx/SDL_qnx.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR_OGL
#ಅನ್ತರ್ಭಾವ <GLES2/gl2.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_hints_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_OPENGL_ES3_ಬಿಟ್_KHR
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENGL_ES3_ಬಿಟ್_KHR 0x00000040
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // EGL_KHR_create_context

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_pixel_format_float
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_pixel_format_float
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#ಆದರೆ_ಅಂತ್ಯ // EGL_EXT_pixel_format_float

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_device
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_device 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_DEVICE_EXT 0x313F
#ಆದರೆ_ಅಂತ್ಯ // EGL_EXT_platform_device

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_present_opaque
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_present_opaque 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PRESENT_OPAQUE_EXT 0x31DF
#ಆದರೆ_ಅಂತ್ಯ // EGL_EXT_present_opaque

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#ವ್ಯಾಖ್ಯಾನಿಸು ALT_EGL            "libEGL.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#ವ್ಯಾಖ್ಯಾನಿಸು ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#ವ್ಯಾಖ್ಯಾನಿಸು ALT_OGL_ES         "libGLESv2.so"

#ಅಥವಾಆದರೆ defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     "libGLESv1_CM.so"

#ಅಥವಾಆದರೆ defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv3.so"

#ಅಥವಾಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.dll"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL        "opengl32.dll"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.dll"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#ಅಥವಾಆದರೆ defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.dylib"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.dylib"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL        "libGL.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     "libGLESv1_CM.so"

#ಅಥವಾಆದರೆ defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.so.1"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.so.1"

#ಇಲ್ಲದಿದ್ದರೆ
// Desktop Linux/Unix-like
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL        "libGL.so.1"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_EGL        "libEGL.so.1"
#ವ್ಯಾಖ್ಯಾನಿಸು ALT_OGL            "libOpenGL.so.0"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES2    "libGLESv2.so.2"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    DEFAULT_OGL_ES
)
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RPI

#ಆದರೆ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_FUNC(TYPE, NAME) \
    _this->egl_ದತ್ತಾಂಶ->NAME = NAME;
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_FUNC(TYPE, NAME)                                                               \
    _this->egl_ದತ್ತಾಂಶ->NAME = (TYPE)SDL_ತುಂಬು_Function(_this->egl_ದತ್ತಾಂಶ->egl_dll_handle, #NAME); \
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->NAME) {                                                     \
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not retrieve EGL function " #NAME);                \
    }
#ಆದರೆ_ಅಂತ್ಯ

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_ದತ್ತಾಂಶ->NAME = (TYPE)_this->egl_ದತ್ತಾಂಶ->egl_Get_Proc_ವಿಳಾಸ(#NAME);

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_EGL_GetErrorName(EGLint egl_Error_ಸಂಕೇತ)
{
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_ERROR_TRANSLATE(e) \
    ಸ್ಥಿತಿ e:                        \
        ಹಿಂತಿರುಗಿ #e
    ಆಯ್ಕೆ (egl_Error_ಸಂಕೇತ) {
        SDL_EGL_ERROR_TRANSLATE(EGL_SUCCESS);
        SDL_EGL_ERROR_TRANSLATE(EGL_NOT_INITIALIZED);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_ACCESS);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_ALLOC);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_ATTRIBUTE);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_CONTEXT);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_CONFIG);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_CURRENT_SURFACE);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_DISPLAY);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_SURFACE);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_ಹೊಂದಿಕೆ);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_ಕಿಟಕಿ);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_ಕಳೆದುಹೋದ);
    }
    ಹಿಂತಿರುಗಿ "";
}

bool SDL_EGL_ಗಣ_Error_Ex(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *eglFunctionName, EGLint egl_Error_ಸಂಕೇತ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *error_ಪಠ್ಯ = SDL_EGL_GetErrorName(egl_Error_ಸಂಕೇತ);
    ಅಕ್ಷರ alt_Error_ಪಠ್ಯ[32];
    ಆದರೆ (error_ಪಠ್ಯ[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (ಶೂನ್ಯ)SDL_snprintf(alt_Error_ಪಠ್ಯ, SDL_arraysize(alt_Error_ಪಠ್ಯ), "0x%x", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)egl_Error_ಸಂಕೇತ);
        error_ಪಠ್ಯ = alt_Error_ಪಠ್ಯ;
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("%s (call to %s failed, reporting an error of %s)", ಸಂದೇಶ, eglFunctionName, error_ಪಠ್ಯ);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ext)
{
    size_t ext_len;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ext_override;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_extstr;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ext_ಆರಂಭ;

    // Invalid extensions can be rejected early
    ಆದರೆ (!ext || *ext == 0 || SDL_strchr(ext, ' ') != ಖಾಲಿ) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        ಹಿಂತಿರುಗಿ false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    ಆದರೆ (ext_override) {
        ಪೂರ್ಣಾಂಕ disable_ext = SDL_atoi(ext_override);
        ಆದರೆ (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            ಹಿಂತಿರುಗಿ false;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ext_len = SDL_strlen(ext);
    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_ದತ್ತಾಂಶ->eglQueryString(_this->egl_ದತ್ತಾಂಶ->egl_display, EGL_EXTENSIONS);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_ದತ್ತಾಂಶ->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (egl_extstr) {
        ext_ಆರಂಭ = egl_extstr;

        ಆಗ (*ext_ಆರಂಭ) {
            ext_ಆರಂಭ = SDL_strstr(ext_ಆರಂಭ, ext);
            ಆದರೆ (!ext_ಆರಂಭ) {
                ಹಿಂತಿರುಗಿ false;
            }
            // Check if the match is not just a substring of one of the extensions
            ಆದರೆ (ext_ಆರಂಭ == egl_extstr || *(ext_ಆರಂಭ - 1) == ' ') {
                ಆದರೆ (ext_ಆರಂಭ[ext_len] == ' ' || ext_ಆರಂಭ[ext_len] == 0) {
                    ಹಿಂತಿರುಗಿ true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_ಆರಂಭ += ext_len;
            ಆಗ (*ext_ಆರಂಭ != ' ' && *ext_ಆರಂಭ != 0) {
                ext_ಆರಂಭ++;
            }
        }
    }

    ಹಿಂತಿರುಗಿ false;
}

SDL_Function_ಸೂಚಕ SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    SDL_Function_ಸೂಚಕ ಫಲಿತಾಂಶ = ಖಾಲಿ;
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ) {
        ಸ್ಥಿರಾಂಕ Uint32 eglver = (((Uint32)_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major) << 16) | ((Uint32)_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_minor);
        ಸ್ಥಿರಾಂಕ bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        ಆದರೆ (!ಫಲಿತಾಂಶ && is_egl_15_or_later && _this->egl_ದತ್ತಾಂಶ->egl_Get_Proc_ವಿಳಾಸ) {
            ಫಲಿತಾಂಶ = _this->egl_ದತ್ತಾಂಶ->egl_Get_Proc_ವಿಳಾಸ(proc);
        }

#ಆದರೆ !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            ಫಲಿತಾಂಶ = SDL_ತುಂಬು_Function(_this->egl_ದತ್ತಾಂಶ->opengl_dll_handle, proc);
        }
#ಆದರೆ_ಅಂತ್ಯ

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        ಆದರೆ (!ಫಲಿತಾಂಶ && !is_egl_15_or_later && _this->egl_ದತ್ತಾಂಶ->egl_Get_Proc_ವಿಳಾಸ) {
            ಫಲಿತಾಂಶ = _this->egl_ದತ್ತಾಂಶ->egl_Get_Proc_ವಿಳಾಸ(proc);
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ) {
        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_display) {
            _this->egl_ದತ್ತಾಂಶ->eglTerminate(_this->egl_ದತ್ತಾಂಶ->egl_display);
            _this->egl_ದತ್ತಾಂಶ->egl_display = ಖಾಲಿ;
        }

        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_ದತ್ತಾಂಶ->egl_dll_handle);
            _this->egl_ದತ್ತಾಂಶ->egl_dll_handle = ಖಾಲಿ;
        }
        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_ದತ್ತಾಂಶ->opengl_dll_handle);
            _this->egl_ದತ್ತಾಂಶ->opengl_dll_handle = ಖಾಲಿ;
        }

        SDL_free(_this->egl_ದತ್ತಾಂಶ);
        _this->egl_ದತ್ತಾಂಶ = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ bool SDL_EGL_ತುಂಬು_Library_ಆಂತರಿಕ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಮಾರ್ಗ)
{
    SDL_SharedObject *egl_dll_handle = ಖಾಲಿ;
#ಆದರೆ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ = ಖಾಲಿ;
#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS)
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *d3dcompiler;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    ಆದರೆ (d3dcompiler) {
        ಆದರೆ (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            ಆದರೆ (SDL_ತುಂಬು_Object(d3dcompiler) == ಖಾಲಿ) {
                SDL_ClearError();
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            ಪೂರ್ಣಾಂಕ i;

            ಗಾಗಿ (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                ಆದರೆ (SDL_ತುಂಬು_Object(d3dcompiler_list[i]) != ಖಾಲಿ) {
                    ನಿಲ್ಲಿಸು;
                }
                SDL_ClearError();
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (SDL_ತುಂಬು_Object("d3dcompiler_43.dll") == ಖಾಲಿ) {
                SDL_ClearError();
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    ಆದರೆ (ಮಾರ್ಗ) {
        opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
    }

    ಆದರೆ (!opengl_dll_handle) {
        ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) {
            ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ > 1) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEFAULT_OGL_ES2
                ಆದರೆ (!opengl_dll_handle) {
                    ಮಾರ್ಗ = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
                }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ALT_OGL_ES2
                ಆದರೆ (!opengl_dll_handle && !vc4) {
                    ಮಾರ್ಗ = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
                }
#ಆದರೆ_ಅಂತ್ಯ
            } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEFAULT_OGL_ES
                ಆದರೆ (!opengl_dll_handle) {
                    ಮಾರ್ಗ = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
                }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEFAULT_OGL_ES_PVR
                ಆದರೆ (!opengl_dll_handle) {
                    ಮಾರ್ಗ = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
                }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ALT_OGL_ES
                ಆದರೆ (!opengl_dll_handle && !vc4) {
                    ಮಾರ್ಗ = ALT_OGL_ES;
                    opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
                }
#ಆದರೆ_ಅಂತ್ಯ
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEFAULT_OGL
            ಆದರೆ (!opengl_dll_handle) {
                ಮಾರ್ಗ = DEFAULT_OGL;
                opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
            }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ALT_OGL
            ಆದರೆ (!opengl_dll_handle) {
                ಮಾರ್ಗ = ALT_OGL;
                opengl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
            }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
    _this->egl_ದತ್ತಾಂಶ->opengl_dll_handle = opengl_dll_handle;

    ಆದರೆ (!opengl_dll_handle) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    ಆದರೆ (egl_ಮಾರ್ಗ) {
        egl_dll_handle = SDL_ತುಂಬು_Object(egl_ಮಾರ್ಗ);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    ಆದರೆ (!egl_dll_handle || SDL_ತುಂಬು_Function(egl_dll_handle, "eglChooseConfig") == ಖಾಲಿ) {
        ಆದರೆ (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        ಆದರೆ (!ಮಾರ್ಗ) {
            ಮಾರ್ಗ = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ALT_EGL
        ಆದರೆ (!egl_dll_handle && !vc4) {
            ಮಾರ್ಗ = ALT_EGL;
            egl_dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
        }
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (!egl_dll_handle || SDL_ತುಂಬು_Function(egl_dll_handle, "eglChooseConfig") == ಖಾಲಿ) {
            ಆದರೆ (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#ಆದರೆ_ಅಂತ್ಯ

    _this->egl_ದತ್ತಾಂಶ->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    ತುಂಬು_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    ತುಂಬು_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    ತುಂಬು_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    ತುಂಬು_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_ವಿಳಾಸ);
    ತುಂಬು_FUNC(PFNEGLCHOOSECONFIGPROC, egl_ಆರಿಸು_Config);
    ತುಂಬು_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    ತುಂಬು_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    ತುಂಬು_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    ತುಂಬು_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_ಕಿಟಕಿ_Surface);
    ತುಂಬು_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    ತುಂಬು_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    ತುಂಬು_FUNC(PFNEGLSWAPBUFFERSPROC, egl_ಅದಲುಬದಲು_Buffers);
    ತುಂಬು_FUNC(PFNEGLSWAPINTERVALPROC, egl_ಅದಲುಬದಲು_Interval);
    ತುಂಬು_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    ತುಂಬು_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    ತುಂಬು_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    ತುಂಬು_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    ತುಂಬು_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    ತುಂಬು_FUNC(PFNEGLGETERRORPROC, eglGetError);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    ತುಂಬು_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    ತುಂಬು_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    ಆದರೆ (ಮಾರ್ಗ) {
        SDL_strlcpy(_this->gl_config.driver_ಮಾರ್ಗ, ಮಾರ್ಗ, ಗಾತ್ರ(_this->gl_config.driver_ಮಾರ್ಗ) - 1);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_EGL_ತುಂಬು_Library_Only(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಮಾರ್ಗ)
{
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL context already created");
    }

    _this->egl_ದತ್ತಾಂಶ = (ರಚನೆ SDL_EGL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_EGL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!SDL_EGL_ತುಂಬು_Library_ಆಂತರಿಕ(_this, egl_ಮಾರ್ಗ)) {
        SDL_free(_this->egl_ದತ್ತಾಂಶ);
        _this->egl_ದತ್ತಾಂಶ = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_EGL_Get_ಆವೃತ್ತಿ(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglQueryString) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಆವೃತ್ತಿ = _this->egl_ದತ್ತಾಂಶ->eglQueryString(_this->egl_ದತ್ತಾಂಶ->egl_display, EGL_ಆವೃತ್ತಿ);
        ಆದರೆ (egl_ಆವೃತ್ತಿ) {
            ಪೂರ್ಣಾಂಕ major = 0, minor = 0;
            ಆದರೆ (SDL_sscanf(egl_ಆವೃತ್ತಿ, "%d.%d", &major, &minor) == 2) {
                _this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major = major;
                _this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_minor = minor;
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_ಆವೃತ್ತಿ);
            }
        }
    }
}

bool SDL_EGL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_ಮಾರ್ಗ, NativeDisplayType native_display)
{
    ಆದರೆ (!SDL_EGL_ತುಂಬು_Library_Only(_this, egl_ಮಾರ್ಗ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    _this->egl_ದತ್ತಾಂಶ->egl_display = EGL_NO_DISPLAY;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    ಆದರೆ (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_ಆವೃತ್ತಿ(_this);

        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major == 1 && _this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_minor == 5) {
            ತುಂಬು_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplay) {
            EGLAttrib *attribs = ಖಾಲಿ;
            ಆದರೆ (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                ಆದರೆ (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
                    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_ದತ್ತಾಂಶ->egl_display = _this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplay(platform, (ಶೂನ್ಯ *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ(_this, "eglGetPlatformDisplayEXT");
                ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT) {
                    _this->egl_ದತ್ತಾಂಶ->egl_display = _this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT(platform, (ಶೂನ್ಯ *)(uintptr_t)native_display, ಖಾಲಿ);
                }
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    ಆದರೆ ((_this->egl_ದತ್ತಾಂಶ->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_ದತ್ತಾಂಶ->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_ದತ್ತಾಂಶ->egl_display = _this->egl_ದತ್ತಾಂಶ->eglGetDisplay(native_display);
    }
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not get EGL display");
    }

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglInitialize(_this->egl_ದತ್ತಾಂಶ->egl_display, ಖಾಲಿ, ಖಾಲಿ) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_ಆವೃತ್ತಿ(_this);

    _this->egl_ದತ್ತಾಂಶ->is_offscreen = false;

    ಹಿಂತಿರುಗಿ true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ device)
{
    ಶೂನ್ಯ *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint ಅಂಕೆ_egl_devices = 0;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *egl_device_hint;

    ಆದರೆ (_this->gl_config.driver_loaded <= 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->eglQueryDevicesEXT) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &ಅಂಕೆ_egl_devices) != EGL_TRUE) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    ಆದರೆ (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        ಆದರೆ (device >= ಅಂಕೆ_egl_devices) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid EGL device is requested.");
        }

        _this->egl_ದತ್ತಾಂಶ->egl_display = _this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], ಖಾಲಿ);

        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_display == EGL_NO_DISPLAY) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglGetPlatformDisplayEXT() failed.");
        }

        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglInitialize(_this->egl_ದತ್ತಾಂಶ->egl_display, ಖಾಲಿ, ಖಾಲಿ) != EGL_TRUE) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not initialize EGL");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ i;
        bool ಸಿಕ್ಕಿತು = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_egl_devices; i++) {
            attempted_egl_display = _this->egl_ದತ್ತಾಂಶ->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], ಖಾಲಿ);

            ಆದರೆ (attempted_egl_display == EGL_NO_DISPLAY) {
                ಮುಂದುವರಿ;
            }

            ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglInitialize(attempted_egl_display, ಖಾಲಿ, ಖಾಲಿ) != EGL_TRUE) {
                _this->egl_ದತ್ತಾಂಶ->eglTerminate(attempted_egl_display);
                ಮುಂದುವರಿ;
            }

            // We did not fail, we'll pick this one!
            _this->egl_ದತ್ತಾಂಶ->egl_display = attempted_egl_display;
            ಸಿಕ್ಕಿತು = true;

            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!ಸಿಕ್ಕಿತು) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_ಆವೃತ್ತಿ(_this);

    _this->egl_ದತ್ತಾಂಶ->is_offscreen = true;

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_EGL_ಗಣ_Required_Visual_Id(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ visual_id)
{
    _this->egl_ದತ್ತಾಂಶ->egl_required_visual_id = visual_id;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DUMP_EGL_CONFIG

#ವ್ಯಾಖ್ಯಾನಿಸು ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    EGLint attribute;
    ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ *name;
} Attribute;

ಸ್ಥಿರ Attribute all_ಗುಣಲಕ್ಷಣಗಳು[] = {
    ATTRIBUTE(EGL_ಬಫರ್_ಗಾತ್ರ),
    ATTRIBUTE(EGL_ALPHA_ಗಾತ್ರ),
    ATTRIBUTE(EGL_BLUE_ಗಾತ್ರ),
    ATTRIBUTE(EGL_GREEN_ಗಾತ್ರ),
    ATTRIBUTE(EGL_RED_ಗಾತ್ರ),
    ATTRIBUTE(EGL_ಆಳ_ಗಾತ್ರ),
    ATTRIBUTE(EGL_STENCIL_ಗಾತ್ರ),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_ಎತ್ತರ),
    ATTRIBUTE(EGL_MAX_PBUFFER_ಅಗಲ),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_ಮೌಲ್ಯ),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_ಮೌಲ್ಯ),
    ATTRIBUTE(EGL_TRANSPARENT_RED_ಮೌಲ್ಯ),
    ATTRIBUTE(EGL_BIND_ಗಮ್ಯ_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_ಗಮ್ಯ_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_ಅದಲುಬದಲು_INTERVAL),
    ATTRIBUTE(EGL_MAX_ಅದಲುಬದಲು_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_ಗಾತ್ರ),
    ATTRIBUTE(EGL_ALPHA_ಮುಖವಾಡ_ಗಾತ್ರ),
    ATTRIBUTE(EGL_COLOR_ಬಫರ್_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_ಹೊಂದಿಕೆ_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

ಸ್ಥಿರ ಶೂನ್ಯ dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    ಪೂರ್ಣಾಂಕ attr;
    ಗಾಗಿ (attr = 0; attr < SDL_arraysize(all_ಗುಣಲಕ್ಷಣಗಳು); attr++) {
        EGLint ಮೌಲ್ಯ;
        _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, config, all_ಗುಣಲಕ್ಷಣಗಳು[attr].attribute, &ಮೌಲ್ಯ);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_ಗುಣಲಕ್ಷಣಗಳು[attr].name, ಮೌಲ್ಯ, ಮೌಲ್ಯ);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // DUMP_EGL_CONFIG

ಸ್ಥಿರ bool SDL_EGL_ಖಾಸಗಿ_ಆರಿಸು_Config(SDL_VideoDevice *_this, bool ಗಣ_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint ಸಿಕ್ಕಿತು_configs = 0, ಮೌಲ್ಯ;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    ಪೂರ್ಣಾಂಕ i, j, ಉತ್ತಮ_bitdiff = -1, ಉತ್ತಮ_truecolor_bitdiff = -1;
    ಪೂರ್ಣಾಂಕ truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.red_ಗಾತ್ರ;
    attribs[i++] = EGL_GREEN_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.green_ಗಾತ್ರ;
    attribs[i++] = EGL_BLUE_ಗಾತ್ರ;
    attribs[i++] = _this->gl_config.blue_ಗಾತ್ರ;

    ಆದರೆ (ಗಣ_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ) {
        attribs[i++] = EGL_ALPHA_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.alpha_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.ಬಫರ್_ಗಾತ್ರ) {
        attribs[i++] = EGL_ಬಫರ್_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.ಬಫರ್_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.ಆಳ_ಗಾತ್ರ) {
        attribs[i++] = EGL_ಆಳ_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.ಆಳ_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.stencil_ಗಾತ್ರ) {
        attribs[i++] = EGL_STENCIL_ಗಾತ್ರ;
        attribs[i++] = _this->gl_config.stencil_ಗಾತ್ರ;
    }

    ಆದರೆ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ಆದರೆ (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ಆದರೆ (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_ಬಿಟ್;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_create_context
        ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_ಬಿಟ್_KHR;
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (_this->gl_config.major_ಆವೃತ್ತಿ >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_ಬಿಟ್;
        } ಇಲ್ಲದಿದ್ದರೆ {
            attribs[i++] = EGL_OPENGL_ES_ಬಿಟ್;
        }
        _this->egl_ದತ್ತಾಂಶ->eglBindAPI(EGL_OPENGL_ES_API);
    } ಇಲ್ಲದಿದ್ದರೆ {
        attribs[i++] = EGL_OPENGL_ಬಿಟ್;
        _this->egl_ದತ್ತಾಂಶ->eglBindAPI(EGL_OPENGL_API);
    }

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_ದತ್ತಾಂಶ->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_ಆರಿಸು_Config(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &ಸಿಕ್ಕಿತು_configs) == EGL_FALSE ||
        ಸಿಕ್ಕಿತು_configs == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_required_visual_id) {
        ಗಾಗಿ (i = 0; i < ಸಿಕ್ಕಿತು_configs; i++) {
            EGLint format;
            _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_required_visual_id == format) {
                has_matching_format = true;
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    ಗಾಗಿ (i = 0; i < ಸಿಕ್ಕಿತು_configs; i++) {
        bool is_truecolor = false;
        ಪೂರ್ಣಾಂಕ bitdiff = 0;

        ಆದರೆ (has_matching_format && _this->egl_ದತ್ತಾಂಶ->egl_required_visual_id) {
            EGLint format;
            _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_required_visual_id != format) {
                ಮುಂದುವರಿ;
            }
        }

        _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, configs[i], EGL_RED_ಗಾತ್ರ, &ಮೌಲ್ಯ);
        ಆದರೆ (ಮೌಲ್ಯ == 8) {
            _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, configs[i], EGL_GREEN_ಗಾತ್ರ, &ಮೌಲ್ಯ);
            ಆದರೆ (ಮೌಲ್ಯ == 8) {
                _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, configs[i], EGL_BLUE_ಗಾತ್ರ, &ಮೌಲ್ಯ);
                ಆದರೆ (ಮೌಲ್ಯ == 8) {
                    is_truecolor = true;
                }
            }
        }

        ಗಾಗಿ (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            ಆದರೆ (attribs[j] == EGL_NONE) {
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_ಗಾತ್ರ ||
                                                    attribs[j] == EGL_GREEN_ಗಾತ್ರ ||
                                                    attribs[j] == EGL_BLUE_ಗಾತ್ರ ||
                                                    attribs[j] == EGL_ALPHA_ಗಾತ್ರ ||
                                                    attribs[j] == EGL_ಆಳ_ಗಾತ್ರ ||
                                                    attribs[j] == EGL_STENCIL_ಗಾತ್ರ)) {
                _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display, configs[i], attribs[j], &ಮೌಲ್ಯ);
                bitdiff += ಮೌಲ್ಯ - attribs[j + 1]; // value is always >= attrib
            }
        }

        ಆದರೆ ((bitdiff < ಉತ್ತಮ_bitdiff) || (ಉತ್ತಮ_bitdiff == -1)) {
            _this->egl_ದತ್ತಾಂಶ->egl_config = configs[i];
            ಉತ್ತಮ_bitdiff = bitdiff;
        }

        ಆದರೆ (is_truecolor && ((bitdiff < ಉತ್ತಮ_truecolor_bitdiff) || (ಉತ್ತಮ_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            ಉತ್ತಮ_truecolor_bitdiff = bitdiff;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿಸು FAVOR_TRUECOLOR 1
#ಆದರೆ FAVOR_TRUECOLOR
    /* Some apps request a low color depth, either because they _assume_
       they'll get a larger one but don't want to fail if only smaller ones
       are available, or they just never called SDL_GL_SetAttribute at all and
       got a tiny default. For these cases, a game that would otherwise run
       at 24-bit color might get dithered down to something smaller, which is
       worth avoiding. If the app requested <= 16 bit color and an exact 24-bit
       match is available, favor that. Otherwise, we look for the closest
       match. Note that while the API promises what you request _or better_,
       it's feasible this can be disastrous for performance for custom software
       on small hardware that all expected to actually get 16-bit color. In this
       case, turn off FAVOR_TRUECOLOR (and maybe send a patch to make this more
       flexible). */
    ಆದರೆ (((_this->gl_config.red_ಗಾತ್ರ + _this->gl_config.blue_ಗಾತ್ರ + _this->gl_config.green_ಗಾತ್ರ) <= 16)) {
        ಆದರೆ (truecolor_config_idx != -1) {
            _this->egl_ದತ್ತಾಂಶ->egl_config = configs[truecolor_config_idx];
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_ದತ್ತಾಂಶ->egl_config);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_EGL_ಆರಿಸು_Config(SDL_VideoDevice *_this)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    ಆದರೆ (SDL_EGL_ಖಾಸಗಿ_ಆರಿಸು_Config(_this, true)) {
        ಹಿಂತಿರುಗಿ true;
    }

    // Fallback with all configs
    ಆದರೆ (SDL_EGL_ಖಾಸಗಿ_ಆರಿಸು_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    ಪೂರ್ಣಾಂಕ attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_ಮುಖವಾಡ = _this->gl_config.profile_ಮುಖವಾಡ;
    EGLint major_ಆವೃತ್ತಿ = _this->gl_config.major_ಆವೃತ್ತಿ;
    EGLint minor_ಆವೃತ್ತಿ = _this->gl_config.minor_ಆವೃತ್ತಿ;
    bool profile_es = (profile_ಮುಖವಾಡ == SDL_GL_CONTEXT_PROFILE_ES);

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        SDL_ಗಣ_Error("EGL not initialized");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
    ಆದರೆ (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        ಪೂರ್ಣಾಂಕ egl_ಆವೃತ್ತಿ_major = _this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major;
        ಪೂರ್ಣಾಂಕ egl_ಆವೃತ್ತಿ_minor = _this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_minor;
        ಆದರೆ (((egl_ಆವೃತ್ತಿ_major < 1) || (egl_ಆವೃತ್ತಿ_major == 1 && egl_ಆವೃತ್ತಿ_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Set the context version and other attributes.
    ಆದರೆ ((major_ಆವೃತ್ತಿ < 3 || (minor_ಆವೃತ್ತಿ == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_ಮುಖವಾಡ == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        ಆದರೆ (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_ಆವೃತ್ತಿ;
            attribs[attr++] = SDL_max(major_ಆವೃತ್ತಿ, 1);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        ಆದರೆ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_ಆವೃತ್ತಿ_KHR;
            attribs[attr++] = major_ಆವೃತ್ತಿ;
            attribs[attr++] = EGL_CONTEXT_MINOR_ಆವೃತ್ತಿ_KHR;
            attribs[attr++] = minor_ಆವೃತ್ತಿ;

            // SDL profile bits match EGL profile bits.
            ಆದರೆ (profile_ಮುಖವಾಡ != 0 && profile_ಮುಖವಾಡ != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_ಮುಖವಾಡ_KHR;
                attribs[attr++] = profile_ಮುಖವಾಡ;
            }

            // SDL flags match EGL flags.
            ಆದರೆ (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ // EGL_KHR_create_context
        {
            SDL_ಗಣ_Error("Could not create EGL context (context attributes are not supported)");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_create_context_no_error
    ಆದರೆ (_this->gl_config.no_error) {
        ಆದರೆ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (_this->egl_contextattrib_callback) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ದತ್ತಾಂಶ->egl_display, _this->egl_ದತ್ತಾಂಶ->egl_config);
        ಆದರೆ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
            SDL_ಗಣ_Error("EGL context attribute callback returned NULL pointer");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಗಾಗಿ (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ಆದರೆ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
                SDL_ಗಣ_Error("EGL context attribute callback returned too many attributes");
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    ಆದರೆ (profile_es) {
        _this->egl_ದತ್ತಾಂಶ->apitype = EGL_OPENGL_ES_API;
    } ಇಲ್ಲದಿದ್ದರೆ {
        _this->egl_ದತ್ತಾಂಶ->apitype = EGL_OPENGL_API;
    }
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->eglBindAPI(_this->egl_ದತ್ತಾಂಶ->apitype)) {
        SDL_ಗಣ_Error("Could not bind EGL API");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    egl_context = _this->egl_ದತ್ತಾಂಶ->eglCreateContext(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                                    _this->egl_ದತ್ತಾಂಶ->egl_config,
                                                    share_context, attribs);

    ಆದರೆ (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_ಗಣ_Error("Could not create EGL context", "eglCreateContext");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_ದತ್ತಾಂಶ->egl_swapinterval = 0;

    ಆದರೆ (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    ಆದರೆ ((_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major > 1) ||
        ((_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_major == 1) && (_this->egl_ದತ್ತಾಂಶ->egl_ಆವೃತ್ತಿ_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        ಆದರೆ (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            ಆದರೆ (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#ಆದರೆ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetIntegerv");
            ಆದರೆ (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_ಆವೃತ್ತಿ, &v);
                ಆದರೆ (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }

    SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    ಹಿಂತಿರುಗಿ (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->eglMakeCurrent) {
        ಆದರೆ (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            ಹಿಂತಿರುಗಿ true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->eglBindAPI) {
        _this->egl_ದತ್ತಾಂಶ->eglBindAPI(_this->egl_ದತ್ತಾಂಶ->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    ಆದರೆ (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_ದತ್ತಾಂಶ->eglMakeCurrent(_this->egl_ದತ್ತಾಂಶ->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->eglMakeCurrent(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    EGLBoolean ಸ್ಥಿತಿ_2;

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    ಆದರೆ (interval < 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Late swap tearing currently unsupported");
    }

    ಸ್ಥಿತಿ_2 = _this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Interval(_this->egl_ದತ್ತಾಂಶ->egl_display, interval);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == EGL_TRUE) {
        _this->egl_ದತ್ತಾಂಶ->egl_swapinterval = interval;
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    *interval = _this->egl_ದತ್ತಾಂಶ->egl_swapinterval;
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_EGL_ಅದಲುಬದಲು_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, egl_surface)) {
        ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (egl_context != ಖಾಲಿ && egl_context != EGL_NO_CONTEXT) {
        _this->egl_ದತ್ತಾಂಶ->eglDestroyContext(_this->egl_ದತ್ತಾಂಶ->egl_display, egl_context);
    }
    ಹಿಂತಿರುಗಿ true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, Native_ಕಿಟಕಿ_Type nw)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#ಆದರೆ_ಅಂತ್ಯ
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    ಪೂರ್ಣಾಂಕ attr = 0;

    EGLSurface surface;

    ಆದರೆ (!SDL_EGL_ಆರಿಸು_Config(_this)) {
        ಹಿಂತಿರುಗಿ EGL_NO_SURFACE;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_ದತ್ತಾಂಶ->eglGetConfigAttrib(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                        _this->egl_ದತ್ತಾಂಶ->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_ಕಿಟಕಿ_ಗಣ_Buffers_Geometry(nw, 0, 0, format_wanted);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    ಆದರೆ (SDL_strcmp(_this->name, "qnx") == 0) {
        ಪೂರ್ಣಾಂಕ format = QNX_ಆರಿಸು_Format(_this, _this->egl_ದತ್ತಾಂಶ->egl_config);

        ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            ಹಿಂತಿರುಗಿ EGL_NO_SURFACE;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_gl_colorspace
    ಆದರೆ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ಆದರೆ (srgbhint && *srgbhint) {
            ಆದರೆ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ಇಲ್ಲದಿದ್ದರೆ {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_ರೇಖೀಯ_KHR;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_ರೇಖೀಯ_KHR;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಪೂರ್ಣಾಂಕ opaque_ext_idx = -1;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EXT_present_opaque
    ಆದರೆ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        ಆದರೆ (ಕಿಟಕಿ && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (_this->egl_surfaceattrib_callback) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ದತ್ತಾಂಶ->egl_display, _this->egl_ದತ್ತಾಂಶ->egl_config);
        ಆದರೆ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
            SDL_ಗಣ_Error("EGL surface attribute callback returned NULL pointer");
            ಹಿಂತಿರುಗಿ EGL_NO_SURFACE;
        }

        ಗಾಗಿ (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ಆದರೆ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_ಮಾರ್ಗ = '\0';
                SDL_ಗಣ_Error("EGL surface attribute callback returned too many attributes");
                ಹಿಂತಿರುಗಿ EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_ದತ್ತಾಂಶ->egl_Create_ಕಿಟಕಿ_Surface(_this->egl_ದತ್ತಾಂಶ->egl_display, _this->egl_ದತ್ತಾಂಶ->egl_config, nw, &attribs[0]);
    ಆದರೆ (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        ಆದರೆ ((_this->egl_ದತ್ತಾಂಶ->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], ಗಾತ್ರ (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_ದತ್ತಾಂಶ->egl_Create_ಕಿಟಕಿ_Surface(_this->egl_ದತ್ತಾಂಶ->egl_display, _this->egl_ದತ್ತಾಂಶ->egl_config, nw, &attribs[0]);
        }
    }

    ಆದರೆ (surface == EGL_NO_SURFACE) {
        SDL_EGL_ಗಣ_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_ಕಿಟಕಿ_get_Format(nw);
    Android_ಗಣ_Format(format_wanted, format_got);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    EGLint ಗುಣಲಕ್ಷಣಗಳು[] = {
        EGL_ಅಗಲ, 0,
        EGL_ಎತ್ತರ, 0,
        EGL_NONE
    };
    ಗುಣಲಕ್ಷಣಗಳು[1] = ಅಗಲ;
    ಗುಣಲಕ್ಷಣಗಳು[3] = ಎತ್ತರ;

    ಆದರೆ (!SDL_EGL_ಆರಿಸು_Config(_this)) {
        ಹಿಂತಿರುಗಿ EGL_NO_SURFACE;
    }

    ಹಿಂತಿರುಗಿ _this->egl_ದತ್ತಾಂಶ->eglCreatePbufferSurface(
        _this->egl_ದತ್ತಾಂಶ->egl_display,
        _this->egl_ದತ್ತಾಂಶ->egl_config,
        ಗುಣಲಕ್ಷಣಗಳು);
}

ಶೂನ್ಯ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (egl_surface != EGL_NO_SURFACE) {
        _this->egl_ದತ್ತಾಂಶ->eglDestroySurface(_this->egl_ದತ್ತಾಂಶ->egl_display, egl_surface);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL
