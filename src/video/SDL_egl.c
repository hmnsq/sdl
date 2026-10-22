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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS)
#ਅਨ੍ਤਰ੍ਭਾਵ "../core/windows/SDL_windows.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
#ਅਨ੍ਤਰ੍ਭਾਵ <android/native_window.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "../video/android/SDL_androidvideo.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_QNX
#ਅਨ੍ਤਰ੍ਭਾਵ <screen/screen.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "../video/qnx/SDL_qnx.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RPI
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR_OGL
#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_hints_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_OPENGL_ES3_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES3_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x00000040
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // EGL_KHR_create_context

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_pixel_format_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_pixel_format_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#ਜੇ_ਅੰਤ // EGL_EXT_pixel_format_float

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_device
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_device 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_DEVICE_EXT 0x313F
#ਜੇ_ਅੰਤ // EGL_EXT_platform_device

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_present_opaque
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_present_opaque 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PRESENT_OPAQUE_EXT 0x31DF
#ਜੇ_ਅੰਤ // EGL_EXT_present_opaque

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALT_EGL            "libEGL.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALT_OGL_ES         "libGLESv2.so"

#ਜਾਂਜੇ defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     "libGLESv1_CM.so"

#ਜਾਂਜੇ defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv3.so"

#ਜਾਂਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.dll"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL        "opengl32.dll"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.dll"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#ਜਾਂਜੇ defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.dylib"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.dylib"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#ਜਾਂਜੇ defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL        "libGL.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     "libGLESv1_CM.so"

#ਜਾਂਜੇ defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.so.1"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.so.1"

#ਨਹੀਂਤਾਂ
// Desktop Linux/Unix-like
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL        "libGL.so.1"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_EGL        "libEGL.so.1"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALT_OGL            "libOpenGL.so.0"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES2    "libGLESv2.so.2"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    DEFAULT_OGL_ES
)
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RPI

#ਜੇ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_FUNC(TYPE, NAME) \
    _this->egl_ਅੰਕੜੇ->NAME = NAME;
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_FUNC(TYPE, NAME)                                                               \
    _this->egl_ਅੰਕੜੇ->NAME = (TYPE)SDL_ਲੱਦੋ_Function(_this->egl_ਅੰਕੜੇ->egl_dll_handle, #NAME); \
    ਜੇ (!_this->egl_ਅੰਕੜੇ->NAME) {                                                     \
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not retrieve EGL function " #NAME);                \
    }
#ਜੇ_ਅੰਤ

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_ਅੰਕੜੇ->NAME = (TYPE)_this->egl_ਅੰਕੜੇ->egl_Get_Proc_ਪਤਾ(#NAME);

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *SDL_EGL_GetErrorName(EGLint egl_Error_ਕੋਡ)
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_ERROR_TRANSLATE(e) \
    ਹਾਲਤ e:                        \
        ਵਾਪਸ #e
    ਚੋਣ (egl_Error_ਕੋਡ) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_ਮੇਲ);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_ਖਿੜਕੀ);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_ਗੁਆਚਾ);
    }
    ਵਾਪਸ "";
}

bool SDL_EGL_ਸੈੱਟ_Error_Ex(ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ਅਚਲ ਅੱਖਰ *eglFunctionName, EGLint egl_Error_ਕੋਡ)
{
    ਅਚਲ ਅੱਖਰ *error_ਪਾਠ = SDL_EGL_GetErrorName(egl_Error_ਕੋਡ);
    ਅੱਖਰ alt_Error_ਪਾਠ[32];
    ਜੇ (error_ਪਾਠ[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (ਖਾਲੀ)SDL_snprintf(alt_Error_ਪਾਠ, SDL_arraysize(alt_Error_ਪਾਠ), "0x%x", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)egl_Error_ਕੋਡ);
        error_ਪਾਠ = alt_Error_ਪਾਠ;
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("%s (call to %s failed, reporting an error of %s)", ਸੁਨੇਹਾ, eglFunctionName, error_ਪਾਠ);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ਅਚਲ ਅੱਖਰ *ext)
{
    size_t ext_len;
    ਅਚਲ ਅੱਖਰ *ext_override;
    ਅਚਲ ਅੱਖਰ *egl_extstr;
    ਅਚਲ ਅੱਖਰ *ext_ਸ਼ੁਰੂ;

    // Invalid extensions can be rejected early
    ਜੇ (!ext || *ext == 0 || SDL_strchr(ext, ' ') != ਨਿਰਾ) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        ਵਾਪਸ false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    ਜੇ (ext_override) {
        ਪੂਰਨ disable_ext = SDL_atoi(ext_override);
        ਜੇ (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            ਵਾਪਸ false;
        } ਨਹੀਂਤਾਂ ਜੇ (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            ਵਾਪਸ false;
        }
    }

    ext_len = SDL_strlen(ext);
    ਚੋਣ (type) {
    ਹਾਲਤ SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_ਅੰਕੜੇ->eglQueryString(_this->egl_ਅੰਕੜੇ->egl_display, EGL_EXTENSIONS);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_ਅੰਕੜੇ->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        ਰੋਕੋ;
    ਮੂਲ:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        ਵਾਪਸ false;
    }

    ਜੇ (egl_extstr) {
        ext_ਸ਼ੁਰੂ = egl_extstr;

        ਜਦੋਂ (*ext_ਸ਼ੁਰੂ) {
            ext_ਸ਼ੁਰੂ = SDL_strstr(ext_ਸ਼ੁਰੂ, ext);
            ਜੇ (!ext_ਸ਼ੁਰੂ) {
                ਵਾਪਸ false;
            }
            // Check if the match is not just a substring of one of the extensions
            ਜੇ (ext_ਸ਼ੁਰੂ == egl_extstr || *(ext_ਸ਼ੁਰੂ - 1) == ' ') {
                ਜੇ (ext_ਸ਼ੁਰੂ[ext_len] == ' ' || ext_ਸ਼ੁਰੂ[ext_len] == 0) {
                    ਵਾਪਸ true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_ਸ਼ੁਰੂ += ext_len;
            ਜਦੋਂ (*ext_ਸ਼ੁਰੂ != ' ' && *ext_ਸ਼ੁਰੂ != 0) {
                ext_ਸ਼ੁਰੂ++;
            }
        }
    }

    ਵਾਪਸ false;
}

SDL_Function_ਸੂਚਕ SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    SDL_Function_ਸੂਚਕ ਨਤੀਜਾ = ਨਿਰਾ;
    ਜੇ (_this->egl_ਅੰਕੜੇ) {
        ਅਚਲ Uint32 eglver = (((Uint32)_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major) << 16) | ((Uint32)_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_minor);
        ਅਚਲ bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        ਜੇ (!ਨਤੀਜਾ && is_egl_15_or_later && _this->egl_ਅੰਕੜੇ->egl_Get_Proc_ਪਤਾ) {
            ਨਤੀਜਾ = _this->egl_ਅੰਕੜੇ->egl_Get_Proc_ਪਤਾ(proc);
        }

#ਜੇ !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        ਜੇ (!ਨਤੀਜਾ) {
            ਨਤੀਜਾ = SDL_ਲੱਦੋ_Function(_this->egl_ਅੰਕੜੇ->opengl_dll_handle, proc);
        }
#ਜੇ_ਅੰਤ

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        ਜੇ (!ਨਤੀਜਾ && !is_egl_15_or_later && _this->egl_ਅੰਕੜੇ->egl_Get_Proc_ਪਤਾ) {
            ਨਤੀਜਾ = _this->egl_ਅੰਕੜੇ->egl_Get_Proc_ਪਤਾ(proc);
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    ਜੇ (_this->egl_ਅੰਕੜੇ) {
        ਜੇ (_this->egl_ਅੰਕੜੇ->egl_display) {
            _this->egl_ਅੰਕੜੇ->eglTerminate(_this->egl_ਅੰਕੜੇ->egl_display);
            _this->egl_ਅੰਕੜੇ->egl_display = ਨਿਰਾ;
        }

        ਜੇ (_this->egl_ਅੰਕੜੇ->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_ਅੰਕੜੇ->egl_dll_handle);
            _this->egl_ਅੰਕੜੇ->egl_dll_handle = ਨਿਰਾ;
        }
        ਜੇ (_this->egl_ਅੰਕੜੇ->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_ਅੰਕੜੇ->opengl_dll_handle);
            _this->egl_ਅੰਕੜੇ->opengl_dll_handle = ਨਿਰਾ;
        }

        SDL_free(_this->egl_ਅੰਕੜੇ);
        _this->egl_ਅੰਕੜੇ = ਨਿਰਾ;
    }
}

ਸਥਿਰ bool SDL_EGL_ਲੱਦੋ_Library_ਅੰਦਰੂਨੀ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *egl_ਰਸਤਾ)
{
    SDL_SharedObject *egl_dll_handle = ਨਿਰਾ;
#ਜੇ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = ਨਿਰਾ;
#ਜੇ_ਅੰਤ
    ਅਚਲ ਅੱਖਰ *ਰਸਤਾ = ਨਿਰਾ;
#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS)
    ਅਚਲ ਅੱਖਰ *d3dcompiler;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    ਜੇ (d3dcompiler) {
        ਜੇ (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            ਜੇ (SDL_ਲੱਦੋ_Object(d3dcompiler) == ਨਿਰਾ) {
                SDL_ClearError();
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ਅਚਲ ਅੱਖਰ *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            ਪੂਰਨ i;

            ਲਈ (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                ਜੇ (SDL_ਲੱਦੋ_Object(d3dcompiler_list[i]) != ਨਿਰਾ) {
                    ਰੋਕੋ;
                }
                SDL_ClearError();
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (SDL_ਲੱਦੋ_Object("d3dcompiler_43.dll") == ਨਿਰਾ) {
                SDL_ClearError();
            }
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    ਰਸਤਾ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    ਜੇ (ਰਸਤਾ) {
        opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    }

    ਜੇ (!opengl_dll_handle) {
        ਜੇ (_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) {
            ਜੇ (_this->gl_config.major_ਸੰਸਕਰਣ > 1) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEFAULT_OGL_ES2
                ਜੇ (!opengl_dll_handle) {
                    ਰਸਤਾ = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
                }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ALT_OGL_ES2
                ਜੇ (!opengl_dll_handle && !vc4) {
                    ਰਸਤਾ = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
                }
#ਜੇ_ਅੰਤ
            } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEFAULT_OGL_ES
                ਜੇ (!opengl_dll_handle) {
                    ਰਸਤਾ = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
                }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEFAULT_OGL_ES_PVR
                ਜੇ (!opengl_dll_handle) {
                    ਰਸਤਾ = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
                }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ALT_OGL_ES
                ਜੇ (!opengl_dll_handle && !vc4) {
                    ਰਸਤਾ = ALT_OGL_ES;
                    opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
                }
#ਜੇ_ਅੰਤ
            }
        } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEFAULT_OGL
            ਜੇ (!opengl_dll_handle) {
                ਰਸਤਾ = DEFAULT_OGL;
                opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
            }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ALT_OGL
            ਜੇ (!opengl_dll_handle) {
                ਰਸਤਾ = ALT_OGL;
                opengl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
            }
#ਜੇ_ਅੰਤ
        }
    }
    _this->egl_ਅੰਕੜੇ->opengl_dll_handle = opengl_dll_handle;

    ਜੇ (!opengl_dll_handle) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    ਜੇ (egl_ਰਸਤਾ) {
        egl_dll_handle = SDL_ਲੱਦੋ_Object(egl_ਰਸਤਾ);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    ਜੇ (!egl_dll_handle || SDL_ਲੱਦੋ_Function(egl_dll_handle, "eglChooseConfig") == ਨਿਰਾ) {
        ਜੇ (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        ਜੇ (!ਰਸਤਾ) {
            ਰਸਤਾ = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ALT_EGL
        ਜੇ (!egl_dll_handle && !vc4) {
            ਰਸਤਾ = ALT_EGL;
            egl_dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
        }
#ਜੇ_ਅੰਤ

        ਜੇ (!egl_dll_handle || SDL_ਲੱਦੋ_Function(egl_dll_handle, "eglChooseConfig") == ਨਿਰਾ) {
            ਜੇ (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#ਜੇ_ਅੰਤ

    _this->egl_ਅੰਕੜੇ->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    ਲੱਦੋ_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    ਲੱਦੋ_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    ਲੱਦੋ_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    ਲੱਦੋ_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_ਪਤਾ);
    ਲੱਦੋ_FUNC(PFNEGLCHOOSECONFIGPROC, egl_ਚੁਣੋ_Config);
    ਲੱਦੋ_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    ਲੱਦੋ_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    ਲੱਦੋ_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    ਲੱਦੋ_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_ਖਿੜਕੀ_Surface);
    ਲੱਦੋ_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    ਲੱਦੋ_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    ਲੱਦੋ_FUNC(PFNEGLSWAPBUFFERSPROC, egl_ਅਦਲਾ_ਬਦਲੀ_Buffers);
    ਲੱਦੋ_FUNC(PFNEGLSWAPINTERVALPROC, egl_ਅਦਲਾ_ਬਦਲੀ_Interval);
    ਲੱਦੋ_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    ਲੱਦੋ_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    ਲੱਦੋ_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    ਲੱਦੋ_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    ਲੱਦੋ_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    ਲੱਦੋ_FUNC(PFNEGLGETERRORPROC, eglGetError);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    ਲੱਦੋ_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    ਜੇ (ਰਸਤਾ) {
        SDL_strlcpy(_this->gl_config.driver_ਰਸਤਾ, ਰਸਤਾ, ਆਕਾਰ(_this->gl_config.driver_ਰਸਤਾ) - 1);
    } ਨਹੀਂਤਾਂ {
        *_this->gl_config.driver_ਰਸਤਾ = '\0';
    }

    ਵਾਪਸ true;
}

bool SDL_EGL_ਲੱਦੋ_Library_Only(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *egl_ਰਸਤਾ)
{
    ਜੇ (_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL context already created");
    }

    _this->egl_ਅੰਕੜੇ = (ਬਣਤਰ SDL_EGL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_EGL_Video_ਅੰਕੜੇ));
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    ਜੇ (!SDL_EGL_ਲੱਦੋ_Library_ਅੰਦਰੂਨੀ(_this, egl_ਰਸਤਾ)) {
        SDL_free(_this->egl_ਅੰਕੜੇ);
        _this->egl_ਅੰਕੜੇ = ਨਿਰਾ;
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ SDL_EGL_Get_ਸੰਸਕਰਣ(SDL_VideoDevice *_this)
{
    ਜੇ (_this->egl_ਅੰਕੜੇ->eglQueryString) {
        ਅਚਲ ਅੱਖਰ *egl_ਸੰਸਕਰਣ = _this->egl_ਅੰਕੜੇ->eglQueryString(_this->egl_ਅੰਕੜੇ->egl_display, EGL_ਸੰਸਕਰਣ);
        ਜੇ (egl_ਸੰਸਕਰਣ) {
            ਪੂਰਨ major = 0, minor = 0;
            ਜੇ (SDL_sscanf(egl_ਸੰਸਕਰਣ, "%d.%d", &major, &minor) == 2) {
                _this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major = major;
                _this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_minor = minor;
            } ਨਹੀਂਤਾਂ {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_ਸੰਸਕਰਣ);
            }
        }
    }
}

bool SDL_EGL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *egl_ਰਸਤਾ, NativeDisplayType native_display)
{
    ਜੇ (!SDL_EGL_ਲੱਦੋ_Library_Only(_this, egl_ਰਸਤਾ)) {
        ਵਾਪਸ false;
    }

    _this->egl_ਅੰਕੜੇ->egl_display = EGL_NO_DISPLAY;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    ਜੇ (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_ਸੰਸਕਰਣ(_this);

        ਜੇ (_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major == 1 && _this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_minor == 5) {
            ਲੱਦੋ_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        ਜੇ (_this->egl_ਅੰਕੜੇ->eglGetPlatformDisplay) {
            EGLAttrib *attribs = ਨਿਰਾ;
            ਜੇ (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                ਜੇ (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_ਰਸਤਾ = '\0';
                    ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_ਅੰਕੜੇ->egl_display = _this->egl_ਅੰਕੜੇ->eglGetPlatformDisplay(platform, (ਖਾਲੀ *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ(_this, "eglGetPlatformDisplayEXT");
                ਜੇ (_this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT) {
                    _this->egl_ਅੰਕੜੇ->egl_display = _this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT(platform, (ਖਾਲੀ *)(uintptr_t)native_display, ਨਿਰਾ);
                }
            }
        }
    }
#ਜੇ_ਅੰਤ
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    ਜੇ ((_this->egl_ਅੰਕੜੇ->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_ਅੰਕੜੇ->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_ਅੰਕੜੇ->egl_display = _this->egl_ਅੰਕੜੇ->eglGetDisplay(native_display);
    }
    ਜੇ (_this->egl_ਅੰਕੜੇ->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_ਰਸਤਾ = '\0';
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not get EGL display");
    }

    ਜੇ (_this->egl_ਅੰਕੜੇ->eglInitialize(_this->egl_ਅੰਕੜੇ->egl_display, ਨਿਰਾ, ਨਿਰਾ) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_ਰਸਤਾ = '\0';
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_ਸੰਸਕਰਣ(_this);

    _this->egl_ਅੰਕੜੇ->is_offscreen = false;

    ਵਾਪਸ true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ਪੂਰਨ device)
{
    ਖਾਲੀ *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint ਅੰਕ_egl_devices = 0;
    ਅਚਲ ਅੱਖਰ *egl_device_hint;

    ਜੇ (_this->gl_config.driver_loaded <= 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    ਜੇ (!_this->egl_ਅੰਕੜੇ->eglQueryDevicesEXT) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    ਜੇ (!_this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    ਜੇ (_this->egl_ਅੰਕੜੇ->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &ਅੰਕ_egl_devices) != EGL_TRUE) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    ਜੇ (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        ਜੇ (device >= ਅੰਕ_egl_devices) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid EGL device is requested.");
        }

        _this->egl_ਅੰਕੜੇ->egl_display = _this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], ਨਿਰਾ);

        ਜੇ (_this->egl_ਅੰਕੜੇ->egl_display == EGL_NO_DISPLAY) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglGetPlatformDisplayEXT() failed.");
        }

        ਜੇ (_this->egl_ਅੰਕੜੇ->eglInitialize(_this->egl_ਅੰਕੜੇ->egl_display, ਨਿਰਾ, ਨਿਰਾ) != EGL_TRUE) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not initialize EGL");
        }
    } ਨਹੀਂਤਾਂ {
        ਪੂਰਨ i;
        bool ਮਿਲਿਆ = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        ਲਈ (i = 0; i < ਅੰਕ_egl_devices; i++) {
            attempted_egl_display = _this->egl_ਅੰਕੜੇ->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], ਨਿਰਾ);

            ਜੇ (attempted_egl_display == EGL_NO_DISPLAY) {
                ਜਾਰੀ;
            }

            ਜੇ (_this->egl_ਅੰਕੜੇ->eglInitialize(attempted_egl_display, ਨਿਰਾ, ਨਿਰਾ) != EGL_TRUE) {
                _this->egl_ਅੰਕੜੇ->eglTerminate(attempted_egl_display);
                ਜਾਰੀ;
            }

            // We did not fail, we'll pick this one!
            _this->egl_ਅੰਕੜੇ->egl_display = attempted_egl_display;
            ਮਿਲਿਆ = true;

            ਰੋਕੋ;
        }

        ਜੇ (!ਮਿਲਿਆ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_ਸੰਸਕਰਣ(_this);

    _this->egl_ਅੰਕੜੇ->is_offscreen = true;

    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_EGL_ਸੈੱਟ_Required_Visual_Id(SDL_VideoDevice *_this, ਪੂਰਨ visual_id)
{
    _this->egl_ਅੰਕੜੇ->egl_required_visual_id = visual_id;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DUMP_EGL_CONFIG

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    EGLint attribute;
    ਅੱਖਰ ਅਚਲ *name;
} Attribute;

ਸਥਿਰ Attribute all_ਗੁਣ[] = {
    ATTRIBUTE(EGL_ਬਫਰ_ਮਾਪ),
    ATTRIBUTE(EGL_ALPHA_ਮਾਪ),
    ATTRIBUTE(EGL_BLUE_ਮਾਪ),
    ATTRIBUTE(EGL_GREEN_ਮਾਪ),
    ATTRIBUTE(EGL_RED_ਮਾਪ),
    ATTRIBUTE(EGL_ਡੂੰਘਾਈ_ਮਾਪ),
    ATTRIBUTE(EGL_STENCIL_ਮਾਪ),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_ਉਚਾਈ),
    ATTRIBUTE(EGL_MAX_PBUFFER_ਚੌੜਾਈ),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_ਮੁੱਲ),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_ਮੁੱਲ),
    ATTRIBUTE(EGL_TRANSPARENT_RED_ਮੁੱਲ),
    ATTRIBUTE(EGL_BIND_ਮੰਜ਼ਿਲ_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_ਮੰਜ਼ਿਲ_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_ਅਦਲਾ_ਬਦਲੀ_INTERVAL),
    ATTRIBUTE(EGL_MAX_ਅਦਲਾ_ਬਦਲੀ_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_ਮਾਪ),
    ATTRIBUTE(EGL_ALPHA_ਨਕਾਬ_ਮਾਪ),
    ATTRIBUTE(EGL_COLOR_ਬਫਰ_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_ਮੇਲ_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

ਸਥਿਰ ਖਾਲੀ dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    ਪੂਰਨ attr;
    ਲਈ (attr = 0; attr < SDL_arraysize(all_ਗੁਣ); attr++) {
        EGLint ਮੁੱਲ;
        _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, config, all_ਗੁਣ[attr].attribute, &ਮੁੱਲ);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_ਗੁਣ[attr].name, ਮੁੱਲ, ਮੁੱਲ);
    }
}

#ਜੇ_ਅੰਤ // DUMP_EGL_CONFIG

ਸਥਿਰ bool SDL_EGL_ਨਿੱਜੀ_ਚੁਣੋ_Config(SDL_VideoDevice *_this, bool ਸੈੱਟ_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint ਮਿਲਿਆ_configs = 0, ਮੁੱਲ;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    ਪੂਰਨ i, j, ਉੱਤਮ_bitdiff = -1, ਉੱਤਮ_truecolor_bitdiff = -1;
    ਪੂਰਨ truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_ਮਾਪ;
    attribs[i++] = _this->gl_config.red_ਮਾਪ;
    attribs[i++] = EGL_GREEN_ਮਾਪ;
    attribs[i++] = _this->gl_config.green_ਮਾਪ;
    attribs[i++] = EGL_BLUE_ਮਾਪ;
    attribs[i++] = _this->gl_config.blue_ਮਾਪ;

    ਜੇ (ਸੈੱਟ_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    ਜੇ (_this->gl_config.alpha_ਮਾਪ) {
        attribs[i++] = EGL_ALPHA_ਮਾਪ;
        attribs[i++] = _this->gl_config.alpha_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.ਬਫਰ_ਮਾਪ) {
        attribs[i++] = EGL_ਬਫਰ_ਮਾਪ;
        attribs[i++] = _this->gl_config.ਬਫਰ_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ) {
        attribs[i++] = EGL_ਡੂੰਘਾਈ_ਮਾਪ;
        attribs[i++] = _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.stencil_ਮਾਪ) {
        attribs[i++] = EGL_STENCIL_ਮਾਪ;
        attribs[i++] = _this->gl_config.stencil_ਮਾਪ;
    }

    ਜੇ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ਜੇ (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ਜੇ (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    ਜੇ (_this->egl_ਅੰਕੜੇ->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    ਜੇ (_this->gl_config.profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context
        ਜੇ (_this->gl_config.major_ਸੰਸਕਰਣ >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
            ਜੇ (_this->gl_config.major_ਸੰਸਕਰਣ >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_ਦੋਆਧਾਰੀ_ਅੰਕ;
        } ਨਹੀਂਤਾਂ {
            attribs[i++] = EGL_OPENGL_ES_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
        _this->egl_ਅੰਕੜੇ->eglBindAPI(EGL_OPENGL_ES_API);
    } ਨਹੀਂਤਾਂ {
        attribs[i++] = EGL_OPENGL_ਦੋਆਧਾਰੀ_ਅੰਕ;
        _this->egl_ਅੰਕੜੇ->eglBindAPI(EGL_OPENGL_API);
    }

    ਜੇ (_this->egl_ਅੰਕੜੇ->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_ਅੰਕੜੇ->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    ਜੇ (_this->egl_ਅੰਕੜੇ->egl_ਚੁਣੋ_Config(_this->egl_ਅੰਕੜੇ->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &ਮਿਲਿਆ_configs) == EGL_FALSE ||
        ਮਿਲਿਆ_configs == 0) {
        ਵਾਪਸ false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    ਜੇ (_this->egl_ਅੰਕੜੇ->egl_required_visual_id) {
        ਲਈ (i = 0; i < ਮਿਲਿਆ_configs; i++) {
            EGLint format;
            _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ਜੇ (_this->egl_ਅੰਕੜੇ->egl_required_visual_id == format) {
                has_matching_format = true;
                ਰੋਕੋ;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    ਲਈ (i = 0; i < ਮਿਲਿਆ_configs; i++) {
        bool is_truecolor = false;
        ਪੂਰਨ bitdiff = 0;

        ਜੇ (has_matching_format && _this->egl_ਅੰਕੜੇ->egl_required_visual_id) {
            EGLint format;
            _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ਜੇ (_this->egl_ਅੰਕੜੇ->egl_required_visual_id != format) {
                ਜਾਰੀ;
            }
        }

        _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, configs[i], EGL_RED_ਮਾਪ, &ਮੁੱਲ);
        ਜੇ (ਮੁੱਲ == 8) {
            _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, configs[i], EGL_GREEN_ਮਾਪ, &ਮੁੱਲ);
            ਜੇ (ਮੁੱਲ == 8) {
                _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, configs[i], EGL_BLUE_ਮਾਪ, &ਮੁੱਲ);
                ਜੇ (ਮੁੱਲ == 8) {
                    is_truecolor = true;
                }
            }
        }

        ਲਈ (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            ਜੇ (attribs[j] == EGL_NONE) {
                ਰੋਕੋ;
            }

            ਜੇ (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_ਮਾਪ ||
                                                    attribs[j] == EGL_GREEN_ਮਾਪ ||
                                                    attribs[j] == EGL_BLUE_ਮਾਪ ||
                                                    attribs[j] == EGL_ALPHA_ਮਾਪ ||
                                                    attribs[j] == EGL_ਡੂੰਘਾਈ_ਮਾਪ ||
                                                    attribs[j] == EGL_STENCIL_ਮਾਪ)) {
                _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display, configs[i], attribs[j], &ਮੁੱਲ);
                bitdiff += ਮੁੱਲ - attribs[j + 1]; // value is always >= attrib
            }
        }

        ਜੇ ((bitdiff < ਉੱਤਮ_bitdiff) || (ਉੱਤਮ_bitdiff == -1)) {
            _this->egl_ਅੰਕੜੇ->egl_config = configs[i];
            ਉੱਤਮ_bitdiff = bitdiff;
        }

        ਜੇ (is_truecolor && ((bitdiff < ਉੱਤਮ_truecolor_bitdiff) || (ਉੱਤਮ_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            ਉੱਤਮ_truecolor_bitdiff = bitdiff;
        }
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FAVOR_TRUECOLOR 1
#ਜੇ FAVOR_TRUECOLOR
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
    ਜੇ (((_this->gl_config.red_ਮਾਪ + _this->gl_config.blue_ਮਾਪ + _this->gl_config.green_ਮਾਪ) <= 16)) {
        ਜੇ (truecolor_config_idx != -1) {
            _this->egl_ਅੰਕੜੇ->egl_config = configs[truecolor_config_idx];
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_ਅੰਕੜੇ->egl_config);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

bool SDL_EGL_ਚੁਣੋ_Config(SDL_VideoDevice *_this)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    ਜੇ (SDL_EGL_ਨਿੱਜੀ_ਚੁਣੋ_Config(_this, true)) {
        ਵਾਪਸ true;
    }

    // Fallback with all configs
    ਜੇ (SDL_EGL_ਨਿੱਜੀ_ਚੁਣੋ_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    ਪੂਰਨ attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_ਨਕਾਬ = _this->gl_config.profile_ਨਕਾਬ;
    EGLint major_ਸੰਸਕਰਣ = _this->gl_config.major_ਸੰਸਕਰਣ;
    EGLint minor_ਸੰਸਕਰਣ = _this->gl_config.minor_ਸੰਸਕਰਣ;
    bool profile_es = (profile_ਨਕਾਬ == SDL_GL_CONTEXT_PROFILE_ES);

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        SDL_ਸੈੱਟ_Error("EGL not initialized");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
    ਜੇ (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        ਪੂਰਨ egl_ਸੰਸਕਰਣ_major = _this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major;
        ਪੂਰਨ egl_ਸੰਸਕਰਣ_minor = _this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_minor;
        ਜੇ (((egl_ਸੰਸਕਰਣ_major < 1) || (egl_ਸੰਸਕਰਣ_major == 1 && egl_ਸੰਸਕਰਣ_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#ਜੇ_ਅੰਤ

    // Set the context version and other attributes.
    ਜੇ ((major_ਸੰਸਕਰਣ < 3 || (minor_ਸੰਸਕਰਣ == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_ਨਕਾਬ == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        ਜੇ (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_ਸੰਸਕਰਣ;
            attribs[attr++] = SDL_max(major_ਸੰਸਕਰਣ, 1);
        }
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        ਜੇ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_ਸੰਸਕਰਣ_KHR;
            attribs[attr++] = major_ਸੰਸਕਰਣ;
            attribs[attr++] = EGL_CONTEXT_MINOR_ਸੰਸਕਰਣ_KHR;
            attribs[attr++] = minor_ਸੰਸਕਰਣ;

            // SDL profile bits match EGL profile bits.
            ਜੇ (profile_ਨਕਾਬ != 0 && profile_ਨਕਾਬ != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_ਨਕਾਬ_KHR;
                attribs[attr++] = profile_ਨਕਾਬ;
            }

            // SDL flags match EGL flags.
            ਜੇ (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ // EGL_KHR_create_context
        {
            SDL_ਸੈੱਟ_Error("Could not create EGL context (context attributes are not supported)");
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context_no_error
    ਜੇ (_this->gl_config.no_error) {
        ਜੇ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (_this->egl_contextattrib_callback) {
        ਅਚਲ ਪੂਰਨ maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ਅੰਕੜੇ->egl_display, _this->egl_ਅੰਕੜੇ->egl_config);
        ਜੇ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_ਰਸਤਾ = '\0';
            SDL_ਸੈੱਟ_Error("EGL context attribute callback returned NULL pointer");
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਲਈ (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ਜੇ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_ਰਸਤਾ = '\0';
                SDL_ਸੈੱਟ_Error("EGL context attribute callback returned too many attributes");
                ਵਾਪਸ ਨਿਰਾ;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    ਜੇ (profile_es) {
        _this->egl_ਅੰਕੜੇ->apitype = EGL_OPENGL_ES_API;
    } ਨਹੀਂਤਾਂ {
        _this->egl_ਅੰਕੜੇ->apitype = EGL_OPENGL_API;
    }
    ਜੇ (!_this->egl_ਅੰਕੜੇ->eglBindAPI(_this->egl_ਅੰਕੜੇ->apitype)) {
        SDL_ਸੈੱਟ_Error("Could not bind EGL API");
        ਵਾਪਸ ਨਿਰਾ;
    }

    egl_context = _this->egl_ਅੰਕੜੇ->eglCreateContext(_this->egl_ਅੰਕੜੇ->egl_display,
                                                    _this->egl_ਅੰਕੜੇ->egl_config,
                                                    share_context, attribs);

    ਜੇ (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_ਸੈੱਟ_Error("Could not create EGL context", "eglCreateContext");
        ਵਾਪਸ ਨਿਰਾ;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_ਅੰਕੜੇ->egl_swapinterval = 0;

    ਜੇ (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    ਜੇ ((_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major > 1) ||
        ((_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_major == 1) && (_this->egl_ਅੰਕੜੇ->egl_ਸੰਸਕਰਣ_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        ਜੇ (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            ਜੇ (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#ਜੇ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } ਨਹੀਂਤਾਂ {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetIntegerv");
            ਜੇ (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_ਸੰਸਕਰਣ, &v);
                ਜੇ (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#ਜੇ_ਅੰਤ
        }
    }

    SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    ਵਾਪਸ (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    ਜੇ (!_this->egl_ਅੰਕੜੇ->eglMakeCurrent) {
        ਜੇ (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            ਵਾਪਸ true;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    ਜੇ (_this->egl_ਅੰਕੜੇ->eglBindAPI) {
        _this->egl_ਅੰਕੜੇ->eglBindAPI(_this->egl_ਅੰਕੜੇ->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    ਜੇ (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_ਅੰਕੜੇ->eglMakeCurrent(_this->egl_ਅੰਕੜੇ->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!_this->egl_ਅੰਕੜੇ->eglMakeCurrent(_this->egl_ਅੰਕੜੇ->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    ਵਾਪਸ true;
}

bool SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    EGLBoolean ਸਥਿਤੀ;

    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    ਜੇ (interval < 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Late swap tearing currently unsupported");
    }

    ਸਥਿਤੀ = _this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Interval(_this->egl_ਅੰਕੜੇ->egl_display, interval);
    ਜੇ (ਸਥਿਤੀ == EGL_TRUE) {
        _this->egl_ਅੰਕੜੇ->egl_swapinterval = interval;
        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL not initialized");
    }

    *interval = _this->egl_ਅੰਕੜੇ->egl_swapinterval;
    ਵਾਪਸ true;
}

bool SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ->egl_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this->egl_ਅੰਕੜੇ->egl_display, egl_surface)) {
        ਵਾਪਸ SDL_EGL_ਸੈੱਟ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    ਵਾਪਸ true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ true;
    }

    ਜੇ (egl_context != ਨਿਰਾ && egl_context != EGL_NO_CONTEXT) {
        _this->egl_ਅੰਕੜੇ->eglDestroyContext(_this->egl_ਅੰਕੜੇ->egl_display, egl_context);
    }
    ਵਾਪਸ true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, Native_ਖਿੜਕੀ_Type nw)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#ਜੇ_ਅੰਤ
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    ਪੂਰਨ attr = 0;

    EGLSurface surface;

    ਜੇ (!SDL_EGL_ਚੁਣੋ_Config(_this)) {
        ਵਾਪਸ EGL_NO_SURFACE;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_ਅੰਕੜੇ->eglGetConfigAttrib(_this->egl_ਅੰਕੜੇ->egl_display,
                                        _this->egl_ਅੰਕੜੇ->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_ਖਿੜਕੀ_ਸੈੱਟ_Buffers_Geometry(nw, 0, 0, format_wanted);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    ਜੇ (SDL_strcmp(_this->name, "qnx") == 0) {
        ਪੂਰਨ format = QNX_ਚੁਣੋ_Format(_this, _this->egl_ਅੰਕੜੇ->egl_config);

        ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            ਵਾਪਸ EGL_NO_SURFACE;
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_colorspace
    ਜੇ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ਅਚਲ ਅੱਖਰ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ਜੇ (srgbhint && *srgbhint) {
            ਜੇ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ਨਹੀਂਤਾਂ {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_ਰੇਖਿਕ_KHR;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_ਰੇਖਿਕ_KHR;
        }
    }
#ਜੇ_ਅੰਤ

    ਪੂਰਨ opaque_ext_idx = -1;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EXT_present_opaque
    ਜੇ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        ਜੇ (ਖਿੜਕੀ && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (_this->egl_surfaceattrib_callback) {
        ਅਚਲ ਪੂਰਨ maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ਅੰਕੜੇ->egl_display, _this->egl_ਅੰਕੜੇ->egl_config);
        ਜੇ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_ਰਸਤਾ = '\0';
            SDL_ਸੈੱਟ_Error("EGL surface attribute callback returned NULL pointer");
            ਵਾਪਸ EGL_NO_SURFACE;
        }

        ਲਈ (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ਜੇ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_ਰਸਤਾ = '\0';
                SDL_ਸੈੱਟ_Error("EGL surface attribute callback returned too many attributes");
                ਵਾਪਸ EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_ਅੰਕੜੇ->egl_Create_ਖਿੜਕੀ_Surface(_this->egl_ਅੰਕੜੇ->egl_display, _this->egl_ਅੰਕੜੇ->egl_config, nw, &attribs[0]);
    ਜੇ (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        ਜੇ ((_this->egl_ਅੰਕੜੇ->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], ਆਕਾਰ (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_ਅੰਕੜੇ->egl_Create_ਖਿੜਕੀ_Surface(_this->egl_ਅੰਕੜੇ->egl_display, _this->egl_ਅੰਕੜੇ->egl_config, nw, &attribs[0]);
        }
    }

    ਜੇ (surface == EGL_NO_SURFACE) {
        SDL_EGL_ਸੈੱਟ_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_ਖਿੜਕੀ_get_Format(nw);
    Android_ਸੈੱਟ_Format(format_wanted, format_got);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    EGLint ਗੁਣ[] = {
        EGL_ਚੌੜਾਈ, 0,
        EGL_ਉਚਾਈ, 0,
        EGL_NONE
    };
    ਗੁਣ[1] = ਚੌੜਾਈ;
    ਗੁਣ[3] = ਉਚਾਈ;

    ਜੇ (!SDL_EGL_ਚੁਣੋ_Config(_this)) {
        ਵਾਪਸ EGL_NO_SURFACE;
    }

    ਵਾਪਸ _this->egl_ਅੰਕੜੇ->eglCreatePbufferSurface(
        _this->egl_ਅੰਕੜੇ->egl_display,
        _this->egl_ਅੰਕੜੇ->egl_config,
        ਗੁਣ);
}

ਖਾਲੀ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        ਵਾਪਸ;
    }

    ਜੇ (egl_surface != EGL_NO_SURFACE) {
        _this->egl_ਅੰਕੜੇ->eglDestroySurface(_this->egl_ਅੰਕੜੇ->egl_display, egl_surface);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL
