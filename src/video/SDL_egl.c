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
#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS)
#ضمن "../core/windows/SDL_windows.h"
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
#ضمن <android/native_window.h>
#ضمن "../video/android/SDL_androidvideo.h"
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
#ضمن <screen/screen.h>
#ضمن "../video/qnx/SDL_qnx.h"
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
#ضمن <unistd.h>
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
#ضمن <GLES2/gl2.h>
#جے_انت

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_egl_c.h"
#ضمن "../SDL_hints_c.h"

#جے_تعریف_شدہ EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#جے_بنا_تعریف EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR
#تعریف_کرو EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR 0x00000040
#جے_انت
#جے_انت // EGL_KHR_create_context

#جے_بنا_تعریف EGL_EXT_pixel_format_float
#تعریف_کرو EGL_EXT_pixel_format_float
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#جے_انت // EGL_EXT_pixel_format_float

#جے_بنا_تعریف EGL_EXT_platform_device
#تعریف_کرو EGL_EXT_platform_device 1
#تعریف_کرو EGL_PLATFORM_DEVICE_EXT 0x313F
#جے_انت // EGL_EXT_platform_device

#جے_بنا_تعریف EGL_EXT_present_opaque
#تعریف_کرو EGL_EXT_present_opaque 1
#تعریف_کرو EGL_PRESENT_OPAQUE_EXT 0x31DF
#جے_انت // EGL_EXT_present_opaque

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#تعریف_کرو DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#تعریف_کرو ALT_EGL            "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#تعریف_کرو ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#تعریف_کرو DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#تعریف_کرو DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#تعریف_کرو ALT_OGL_ES         "libGLESv2.so"

#وإلاإذا defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.so"

#وإلاإذا defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv3.so"

#وإلاإذا defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#تعریف_کرو DEFAULT_EGL        "libEGL.dll"
#تعریف_کرو DEFAULT_OGL        "opengl32.dll"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.dll"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#وإلاإذا defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#تعریف_کرو DEFAULT_EGL        "libEGL.dylib"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.dylib"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#وإلاإذا defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#تعریف_کرو DEFAULT_OGL        "libGL.so"
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.so"

#وإلاإذا defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#تعریف_کرو DEFAULT_EGL        "libEGL.so.1"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so.1"

#وإلا
// Desktop Linux/Unix-like
#تعریف_کرو DEFAULT_OGL        "libGL.so.1"
#تعریف_کرو DEFAULT_EGL        "libEGL.so.1"
#تعریف_کرو ALT_OGL            "libOpenGL.so.0"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so.2"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    DEFAULT_OGL_ES
)
#جے_انت // SDL_VIDEO_DRIVER_RPI

#إذا defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#ضمن <SDL3/SDL_opengl.h>
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
تعريفنوع فراغ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#جے_انت

#إذا defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#تعریف_کرو لدو_FUNC(TYPE, NAME) \
    _this->egl_انکڑے->NAME = NAME;
#وإلا
#تعریف_کرو لدو_FUNC(TYPE, NAME)                                                               \
    _this->egl_انکڑے->NAME = (TYPE)SDL_لدو_Function(_this->egl_انکڑے->egl_dll_handle, #NAME); \
    إذا (!_this->egl_انکڑے->NAME) {                                                     \
        أرجع SDL_سیٹ_Error("Could not retrieve EGL function " #NAME);                \
    }
#جے_انت

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#تعریف_کرو لدو_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_انکڑے->NAME = (TYPE)_this->egl_انکڑے->egl_Get_Proc_پتہ(#NAME);

ساكن ثابت حرف *SDL_EGL_GetErrorName(EGLint egl_Error_کوڈ)
{
#تعریف_کرو SDL_EGL_ERROR_TRANSLATE(e) \
    حالة e:                        \
        أرجع #e
    بدل (egl_Error_کوڈ) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_میل);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_کھڑکی);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_گواچا);
    }
    أرجع "";
}

bool SDL_EGL_سیٹ_Error_Ex(ثابت حرف *سنیہا, ثابت حرف *eglFunctionName, EGLint egl_Error_کوڈ)
{
    ثابت حرف *error_متن = SDL_EGL_GetErrorName(egl_Error_کوڈ);
    حرف alt_Error_متن[32];
    إذا (error_متن[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (فراغ)SDL_snprintf(alt_Error_متن, SDL_arraysize(alt_Error_متن), "0x%x", (بنانشانی صحيح)egl_Error_کوڈ);
        error_متن = alt_Error_متن;
    }
    أرجع SDL_سیٹ_Error("%s (call to %s failed, reporting an error of %s)", سنیہا, eglFunctionName, error_متن);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ثابت حرف *ext)
{
    size_t ext_len;
    ثابت حرف *ext_override;
    ثابت حرف *egl_extstr;
    ثابت حرف *ext_شروع;

    // Invalid extensions can be rejected early
    إذا (!ext || *ext == 0 || SDL_strchr(ext, ' ') != عدم) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        أرجع false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    إذا (ext_override) {
        صحيح disable_ext = SDL_atoi(ext_override);
        إذا (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            أرجع false;
        } وإلا إذا (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            أرجع false;
        }
    }

    ext_len = SDL_strlen(ext);
    بدل (type) {
    حالة SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_انکڑے->eglQueryString(_this->egl_انکڑے->egl_display, EGL_EXTENSIONS);
        اكسر;
    حالة SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_انکڑے->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        اكسر;
    افتراضي:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        أرجع false;
    }

    إذا (egl_extstr) {
        ext_شروع = egl_extstr;

        طالما (*ext_شروع) {
            ext_شروع = SDL_strstr(ext_شروع, ext);
            إذا (!ext_شروع) {
                أرجع false;
            }
            // Check if the match is not just a substring of one of the extensions
            إذا (ext_شروع == egl_extstr || *(ext_شروع - 1) == ' ') {
                إذا (ext_شروع[ext_len] == ' ' || ext_شروع[ext_len] == 0) {
                    أرجع true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_شروع += ext_len;
            طالما (*ext_شروع != ' ' && *ext_شروع != 0) {
                ext_شروع++;
            }
        }
    }

    أرجع false;
}

SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ_اندرونی(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر نتیجہ = عدم;
    إذا (_this->egl_انکڑے) {
        ثابت Uint32 eglver = (((Uint32)_this->egl_انکڑے->egl_نسخہ_major) << 16) | ((Uint32)_this->egl_انکڑے->egl_نسخہ_minor);
        ثابت bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        إذا (!نتیجہ && is_egl_15_or_later && _this->egl_انکڑے->egl_Get_Proc_پتہ) {
            نتیجہ = _this->egl_انکڑے->egl_Get_Proc_پتہ(proc);
        }

#إذا !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        إذا (!نتیجہ) {
            نتیجہ = SDL_لدو_Function(_this->egl_انکڑے->opengl_dll_handle, proc);
        }
#جے_انت

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        إذا (!نتیجہ && !is_egl_15_or_later && _this->egl_انکڑے->egl_Get_Proc_پتہ) {
            نتیجہ = _this->egl_انکڑے->egl_Get_Proc_پتہ(proc);
        }
    }
    أرجع نتیجہ;
}

فراغ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    إذا (_this->egl_انکڑے) {
        إذا (_this->egl_انکڑے->egl_display) {
            _this->egl_انکڑے->eglTerminate(_this->egl_انکڑے->egl_display);
            _this->egl_انکڑے->egl_display = عدم;
        }

        إذا (_this->egl_انکڑے->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_انکڑے->egl_dll_handle);
            _this->egl_انکڑے->egl_dll_handle = عدم;
        }
        إذا (_this->egl_انکڑے->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_انکڑے->opengl_dll_handle);
            _this->egl_انکڑے->opengl_dll_handle = عدم;
        }

        SDL_free(_this->egl_انکڑے);
        _this->egl_انکڑے = عدم;
    }
}

ساكن bool SDL_EGL_لدو_Library_اندرونی(SDL_VideoDevice *_this, ثابت حرف *egl_رستہ)
{
    SDL_SharedObject *egl_dll_handle = عدم;
#إذا !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = عدم;
#جے_انت
    ثابت حرف *رستہ = عدم;
#إذا defined(SDL_VIDEO_DRIVER_WINDOWS)
    ثابت حرف *d3dcompiler;
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#جے_انت

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    إذا (d3dcompiler) {
        إذا (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            إذا (SDL_لدو_Object(d3dcompiler) == عدم) {
                SDL_ClearError();
            }
        }
    } وإلا {
        إذا (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ثابت حرف *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            صحيح i;

            لكل (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                إذا (SDL_لدو_Object(d3dcompiler_list[i]) != عدم) {
                    اكسر;
                }
                SDL_ClearError();
            }
        } وإلا {
            إذا (SDL_لدو_Object("d3dcompiler_43.dll") == عدم) {
                SDL_ClearError();
            }
        }
    }
#جے_انت

#إذا !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    رستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    إذا (رستہ) {
        opengl_dll_handle = SDL_لدو_Object(رستہ);
    }

    إذا (!opengl_dll_handle) {
        إذا (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) {
            إذا (_this->gl_config.major_نسخہ > 1) {
#جے_تعریف_شدہ DEFAULT_OGL_ES2
                إذا (!opengl_dll_handle) {
                    رستہ = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_لدو_Object(رستہ);
                }
#جے_انت
#جے_تعریف_شدہ ALT_OGL_ES2
                إذا (!opengl_dll_handle && !vc4) {
                    رستہ = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_لدو_Object(رستہ);
                }
#جے_انت
            } وإلا {
#جے_تعریف_شدہ DEFAULT_OGL_ES
                إذا (!opengl_dll_handle) {
                    رستہ = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_لدو_Object(رستہ);
                }
#جے_انت
#جے_تعریف_شدہ DEFAULT_OGL_ES_PVR
                إذا (!opengl_dll_handle) {
                    رستہ = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_لدو_Object(رستہ);
                }
#جے_انت
#جے_تعریف_شدہ ALT_OGL_ES
                إذا (!opengl_dll_handle && !vc4) {
                    رستہ = ALT_OGL_ES;
                    opengl_dll_handle = SDL_لدو_Object(رستہ);
                }
#جے_انت
            }
        } وإلا {
#جے_تعریف_شدہ DEFAULT_OGL
            إذا (!opengl_dll_handle) {
                رستہ = DEFAULT_OGL;
                opengl_dll_handle = SDL_لدو_Object(رستہ);
            }
#جے_انت
#جے_تعریف_شدہ ALT_OGL
            إذا (!opengl_dll_handle) {
                رستہ = ALT_OGL;
                opengl_dll_handle = SDL_لدو_Object(رستہ);
            }
#جے_انت
        }
    }
    _this->egl_انکڑے->opengl_dll_handle = opengl_dll_handle;

    إذا (!opengl_dll_handle) {
        أرجع SDL_سیٹ_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    إذا (egl_رستہ) {
        egl_dll_handle = SDL_لدو_Object(egl_رستہ);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    إذا (!egl_dll_handle || SDL_لدو_Function(egl_dll_handle, "eglChooseConfig") == عدم) {
        إذا (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        رستہ = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        إذا (!رستہ) {
            رستہ = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_لدو_Object(رستہ);

#جے_تعریف_شدہ ALT_EGL
        إذا (!egl_dll_handle && !vc4) {
            رستہ = ALT_EGL;
            egl_dll_handle = SDL_لدو_Object(رستہ);
        }
#جے_انت

        إذا (!egl_dll_handle || SDL_لدو_Function(egl_dll_handle, "eglChooseConfig") == عدم) {
            إذا (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            أرجع SDL_سیٹ_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#جے_انت

    _this->egl_انکڑے->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    لدو_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    لدو_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    لدو_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    لدو_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_پتہ);
    لدو_FUNC(PFNEGLCHOOSECONFIGPROC, egl_چنو_Config);
    لدو_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    لدو_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    لدو_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    لدو_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_کھڑکی_Surface);
    لدو_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    لدو_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    لدو_FUNC(PFNEGLSWAPBUFFERSPROC, egl_وٹاندرا_Buffers);
    لدو_FUNC(PFNEGLSWAPINTERVALPROC, egl_وٹاندرا_Interval);
    لدو_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    لدو_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    لدو_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    لدو_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    لدو_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    لدو_FUNC(PFNEGLGETERRORPROC, eglGetError);
    لدو_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    لدو_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    لدو_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    لدو_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    لدو_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    لدو_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    لدو_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    إذا (رستہ) {
        SDL_strlcpy(_this->gl_config.driver_رستہ, رستہ, حجم(_this->gl_config.driver_رستہ) - 1);
    } وإلا {
        *_this->gl_config.driver_رستہ = '\0';
    }

    أرجع true;
}

bool SDL_EGL_لدو_Library_Only(SDL_VideoDevice *_this, ثابت حرف *egl_رستہ)
{
    إذا (_this->egl_انکڑے) {
        أرجع SDL_سیٹ_Error("EGL context already created");
    }

    _this->egl_انکڑے = (بنية SDL_EGL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_EGL_Video_انکڑے));
    إذا (!_this->egl_انکڑے) {
        أرجع false;
    }

    إذا (!SDL_EGL_لدو_Library_اندرونی(_this, egl_رستہ)) {
        SDL_free(_this->egl_انکڑے);
        _this->egl_انکڑے = عدم;
        أرجع false;
    }
    أرجع true;
}

ساكن فراغ SDL_EGL_Get_نسخہ(SDL_VideoDevice *_this)
{
    إذا (_this->egl_انکڑے->eglQueryString) {
        ثابت حرف *egl_نسخہ = _this->egl_انکڑے->eglQueryString(_this->egl_انکڑے->egl_display, EGL_نسخہ);
        إذا (egl_نسخہ) {
            صحيح major = 0, minor = 0;
            إذا (SDL_sscanf(egl_نسخہ, "%d.%d", &major, &minor) == 2) {
                _this->egl_انکڑے->egl_نسخہ_major = major;
                _this->egl_انکڑے->egl_نسخہ_minor = minor;
            } وإلا {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_نسخہ);
            }
        }
    }
}

bool SDL_EGL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_رستہ, NativeDisplayType native_display)
{
    إذا (!SDL_EGL_لدو_Library_Only(_this, egl_رستہ)) {
        أرجع false;
    }

    _this->egl_انکڑے->egl_display = EGL_NO_DISPLAY;

#جے_بنا_تعریف SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    إذا (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_نسخہ(_this);

        إذا (_this->egl_انکڑے->egl_نسخہ_major == 1 && _this->egl_انکڑے->egl_نسخہ_minor == 5) {
            لدو_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        إذا (_this->egl_انکڑے->eglGetPlatformDisplay) {
            EGLAttrib *attribs = عدم;
            إذا (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                إذا (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_رستہ = '\0';
                    أرجع SDL_سیٹ_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_انکڑے->egl_display = _this->egl_انکڑے->eglGetPlatformDisplay(platform, (فراغ *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } وإلا {
            إذا (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_انکڑے->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_پتہ_اندرونی(_this, "eglGetPlatformDisplayEXT");
                إذا (_this->egl_انکڑے->eglGetPlatformDisplayEXT) {
                    _this->egl_انکڑے->egl_display = _this->egl_انکڑے->eglGetPlatformDisplayEXT(platform, (فراغ *)(uintptr_t)native_display, عدم);
                }
            }
        }
    }
#جے_انت
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    إذا ((_this->egl_انکڑے->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_انکڑے->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_انکڑے->egl_display = _this->egl_انکڑے->eglGetDisplay(native_display);
    }
    إذا (_this->egl_انکڑے->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_رستہ = '\0';
        أرجع SDL_سیٹ_Error("Could not get EGL display");
    }

    إذا (_this->egl_انکڑے->eglInitialize(_this->egl_انکڑے->egl_display, عدم, عدم) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_رستہ = '\0';
        أرجع SDL_سیٹ_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_نسخہ(_this);

    _this->egl_انکڑے->is_offscreen = false;

    أرجع true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, صحيح device)
{
    فراغ *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint عدد_egl_devices = 0;
    ثابت حرف *egl_device_hint;

    إذا (_this->gl_config.driver_loaded <= 0) {
        أرجع SDL_سیٹ_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    إذا (!_this->egl_انکڑے->eglQueryDevicesEXT) {
        أرجع SDL_سیٹ_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    إذا (!_this->egl_انکڑے->eglGetPlatformDisplayEXT) {
        أرجع SDL_سیٹ_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    إذا (_this->egl_انکڑے->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &عدد_egl_devices) != EGL_TRUE) {
        أرجع SDL_سیٹ_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    إذا (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        إذا (device >= عدد_egl_devices) {
            أرجع SDL_سیٹ_Error("Invalid EGL device is requested.");
        }

        _this->egl_انکڑے->egl_display = _this->egl_انکڑے->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], عدم);

        إذا (_this->egl_انکڑے->egl_display == EGL_NO_DISPLAY) {
            أرجع SDL_سیٹ_Error("eglGetPlatformDisplayEXT() failed.");
        }

        إذا (_this->egl_انکڑے->eglInitialize(_this->egl_انکڑے->egl_display, عدم, عدم) != EGL_TRUE) {
            أرجع SDL_سیٹ_Error("Could not initialize EGL");
        }
    } وإلا {
        صحيح i;
        bool لبھیا = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        لكل (i = 0; i < عدد_egl_devices; i++) {
            attempted_egl_display = _this->egl_انکڑے->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], عدم);

            إذا (attempted_egl_display == EGL_NO_DISPLAY) {
                استمر;
            }

            إذا (_this->egl_انکڑے->eglInitialize(attempted_egl_display, عدم, عدم) != EGL_TRUE) {
                _this->egl_انکڑے->eglTerminate(attempted_egl_display);
                استمر;
            }

            // We did not fail, we'll pick this one!
            _this->egl_انکڑے->egl_display = attempted_egl_display;
            لبھیا = true;

            اكسر;
        }

        إذا (!لبھیا) {
            أرجع SDL_سیٹ_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_نسخہ(_this);

    _this->egl_انکڑے->is_offscreen = true;

    أرجع true;
}

فراغ SDL_EGL_سیٹ_Required_Visual_Id(SDL_VideoDevice *_this, صحيح visual_id)
{
    _this->egl_انکڑے->egl_required_visual_id = visual_id;
}

#جے_تعریف_شدہ DUMP_EGL_CONFIG

#تعریف_کرو ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

تعريفنوع بنية
{
    EGLint attribute;
    حرف ثابت *name;
} Attribute;

ساكن Attribute all_گن[] = {
    ATTRIBUTE(EGL_بفر_ناپ),
    ATTRIBUTE(EGL_ALPHA_ناپ),
    ATTRIBUTE(EGL_BLUE_ناپ),
    ATTRIBUTE(EGL_GREEN_ناپ),
    ATTRIBUTE(EGL_RED_ناپ),
    ATTRIBUTE(EGL_ڈونگھائی_ناپ),
    ATTRIBUTE(EGL_STENCIL_ناپ),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_اچائی),
    ATTRIBUTE(EGL_MAX_PBUFFER_چوڑائی),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_قدر),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_قدر),
    ATTRIBUTE(EGL_TRANSPARENT_RED_قدر),
    ATTRIBUTE(EGL_BIND_منزل_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_منزل_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_وٹاندرا_INTERVAL),
    ATTRIBUTE(EGL_MAX_وٹاندرا_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_ناپ),
    ATTRIBUTE(EGL_ALPHA_نقاب_ناپ),
    ATTRIBUTE(EGL_COLOR_بفر_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_میل_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

ساكن فراغ dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    صحيح attr;
    لكل (attr = 0; attr < SDL_arraysize(all_گن); attr++) {
        EGLint قدر;
        _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, config, all_گن[attr].attribute, &قدر);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_گن[attr].name, قدر, قدر);
    }
}

#جے_انت // DUMP_EGL_CONFIG

ساكن bool SDL_EGL_نجی_چنو_Config(SDL_VideoDevice *_this, bool سیٹ_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint لبھیا_configs = 0, قدر;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    صحيح i, j, بہترین_bitdiff = -1, بہترین_truecolor_bitdiff = -1;
    صحيح truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_ناپ;
    attribs[i++] = _this->gl_config.red_ناپ;
    attribs[i++] = EGL_GREEN_ناپ;
    attribs[i++] = _this->gl_config.green_ناپ;
    attribs[i++] = EGL_BLUE_ناپ;
    attribs[i++] = _this->gl_config.blue_ناپ;

    إذا (سیٹ_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    إذا (_this->gl_config.alpha_ناپ) {
        attribs[i++] = EGL_ALPHA_ناپ;
        attribs[i++] = _this->gl_config.alpha_ناپ;
    }

    إذا (_this->gl_config.بفر_ناپ) {
        attribs[i++] = EGL_بفر_ناپ;
        attribs[i++] = _this->gl_config.بفر_ناپ;
    }

    إذا (_this->gl_config.ڈونگھائی_ناپ) {
        attribs[i++] = EGL_ڈونگھائی_ناپ;
        attribs[i++] = _this->gl_config.ڈونگھائی_ناپ;
    }

    إذا (_this->gl_config.stencil_ناپ) {
        attribs[i++] = EGL_STENCIL_ناپ;
        attribs[i++] = _this->gl_config.stencil_ناپ;
    }

    إذا (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    إذا (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    إذا (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    إذا (_this->egl_انکڑے->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_ثنائی_ہندسہ;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    إذا (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) {
#جے_تعریف_شدہ EGL_KHR_create_context
        إذا (_this->gl_config.major_نسخہ >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR;
        } وإلا
#جے_انت
            إذا (_this->gl_config.major_نسخہ >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;
        } وإلا {
            attribs[i++] = EGL_OPENGL_ES_ثنائی_ہندسہ;
        }
        _this->egl_انکڑے->eglBindAPI(EGL_OPENGL_ES_API);
    } وإلا {
        attribs[i++] = EGL_OPENGL_ثنائی_ہندسہ;
        _this->egl_انکڑے->eglBindAPI(EGL_OPENGL_API);
    }

    إذا (_this->egl_انکڑے->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_انکڑے->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    إذا (_this->egl_انکڑے->egl_چنو_Config(_this->egl_انکڑے->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &لبھیا_configs) == EGL_FALSE ||
        لبھیا_configs == 0) {
        أرجع false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    إذا (_this->egl_انکڑے->egl_required_visual_id) {
        لكل (i = 0; i < لبھیا_configs; i++) {
            EGLint format;
            _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            إذا (_this->egl_انکڑے->egl_required_visual_id == format) {
                has_matching_format = true;
                اكسر;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    لكل (i = 0; i < لبھیا_configs; i++) {
        bool is_truecolor = false;
        صحيح bitdiff = 0;

        إذا (has_matching_format && _this->egl_انکڑے->egl_required_visual_id) {
            EGLint format;
            _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            إذا (_this->egl_انکڑے->egl_required_visual_id != format) {
                استمر;
            }
        }

        _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, configs[i], EGL_RED_ناپ, &قدر);
        إذا (قدر == 8) {
            _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, configs[i], EGL_GREEN_ناپ, &قدر);
            إذا (قدر == 8) {
                _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, configs[i], EGL_BLUE_ناپ, &قدر);
                إذا (قدر == 8) {
                    is_truecolor = true;
                }
            }
        }

        لكل (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            إذا (attribs[j] == EGL_NONE) {
                اكسر;
            }

            إذا (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_ناپ ||
                                                    attribs[j] == EGL_GREEN_ناپ ||
                                                    attribs[j] == EGL_BLUE_ناپ ||
                                                    attribs[j] == EGL_ALPHA_ناپ ||
                                                    attribs[j] == EGL_ڈونگھائی_ناپ ||
                                                    attribs[j] == EGL_STENCIL_ناپ)) {
                _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display, configs[i], attribs[j], &قدر);
                bitdiff += قدر - attribs[j + 1]; // value is always >= attrib
            }
        }

        إذا ((bitdiff < بہترین_bitdiff) || (بہترین_bitdiff == -1)) {
            _this->egl_انکڑے->egl_config = configs[i];
            بہترین_bitdiff = bitdiff;
        }

        إذا (is_truecolor && ((bitdiff < بہترین_truecolor_bitdiff) || (بہترین_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            بہترین_truecolor_bitdiff = bitdiff;
        }
    }

#تعریف_کرو FAVOR_TRUECOLOR 1
#إذا FAVOR_TRUECOLOR
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
    إذا (((_this->gl_config.red_ناپ + _this->gl_config.blue_ناپ + _this->gl_config.green_ناپ) <= 16)) {
        إذا (truecolor_config_idx != -1) {
            _this->egl_انکڑے->egl_config = configs[truecolor_config_idx];
        }
    }
#جے_انت

#جے_تعریف_شدہ DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_انکڑے->egl_config);
#جے_انت

    أرجع true;
}

bool SDL_EGL_چنو_Config(SDL_VideoDevice *_this)
{
    إذا (!_this->egl_انکڑے) {
        أرجع SDL_سیٹ_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    إذا (SDL_EGL_نجی_چنو_Config(_this, true)) {
        أرجع true;
    }

    // Fallback with all configs
    إذا (SDL_EGL_نجی_چنو_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        أرجع true;
    }

    أرجع SDL_EGL_سیٹ_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    صحيح attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_نقاب = _this->gl_config.profile_نقاب;
    EGLint major_نسخہ = _this->gl_config.major_نسخہ;
    EGLint minor_نسخہ = _this->gl_config.minor_نسخہ;
    bool profile_es = (profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);

    إذا (!_this->egl_انکڑے) {
        SDL_سیٹ_Error("EGL not initialized");
        أرجع عدم;
    }

    إذا (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    إذا (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        صحيح egl_نسخہ_major = _this->egl_انکڑے->egl_نسخہ_major;
        صحيح egl_نسخہ_minor = _this->egl_انکڑے->egl_نسخہ_minor;
        إذا (((egl_نسخہ_major < 1) || (egl_نسخہ_major == 1 && egl_نسخہ_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#جے_انت

    // Set the context version and other attributes.
    إذا ((major_نسخہ < 3 || (minor_نسخہ == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_نقاب == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        إذا (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_نسخہ;
            attribs[attr++] = SDL_max(major_نسخہ, 1);
        }
    } وإلا {
#جے_تعریف_شدہ EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        إذا (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_نسخہ_KHR;
            attribs[attr++] = major_نسخہ;
            attribs[attr++] = EGL_CONTEXT_MINOR_نسخہ_KHR;
            attribs[attr++] = minor_نسخہ;

            // SDL profile bits match EGL profile bits.
            إذا (profile_نقاب != 0 && profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_نقاب_KHR;
                attribs[attr++] = profile_نقاب;
            }

            // SDL flags match EGL flags.
            إذا (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } وإلا
#جے_انت // EGL_KHR_create_context
        {
            SDL_سیٹ_Error("Could not create EGL context (context attributes are not supported)");
            أرجع عدم;
        }
    }

#جے_تعریف_شدہ EGL_KHR_create_context_no_error
    إذا (_this->gl_config.no_error) {
        إذا (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#جے_انت

    إذا (_this->egl_contextattrib_callback) {
        ثابت صحيح maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_انکڑے->egl_display, _this->egl_انکڑے->egl_config);
        إذا (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_رستہ = '\0';
            SDL_سیٹ_Error("EGL context attribute callback returned NULL pointer");
            أرجع عدم;
        }

        لكل (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            إذا (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_رستہ = '\0';
                SDL_سیٹ_Error("EGL context attribute callback returned too many attributes");
                أرجع عدم;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    إذا (profile_es) {
        _this->egl_انکڑے->apitype = EGL_OPENGL_ES_API;
    } وإلا {
        _this->egl_انکڑے->apitype = EGL_OPENGL_API;
    }
    إذا (!_this->egl_انکڑے->eglBindAPI(_this->egl_انکڑے->apitype)) {
        SDL_سیٹ_Error("Could not bind EGL API");
        أرجع عدم;
    }

    egl_context = _this->egl_انکڑے->eglCreateContext(_this->egl_انکڑے->egl_display,
                                                    _this->egl_انکڑے->egl_config,
                                                    share_context, attribs);

    إذا (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_سیٹ_Error("Could not create EGL context", "eglCreateContext");
        أرجع عدم;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_انکڑے->egl_swapinterval = 0;

    إذا (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        أرجع عدم;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    إذا ((_this->egl_انکڑے->egl_نسخہ_major > 1) ||
        ((_this->egl_انکڑے->egl_نسخہ_major == 1) && (_this->egl_انکڑے->egl_نسخہ_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        إذا (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            إذا (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#إذا defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } وإلا {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
            إذا (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_نسخہ, &v);
                إذا (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#جے_انت
        }
    }

    SDL_EGL_سیٹ_وٹاندرا_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    أرجع (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    إذا (!_this->egl_انکڑے) {
        أرجع SDL_سیٹ_Error("EGL not initialized");
    }

    إذا (!_this->egl_انکڑے->eglMakeCurrent) {
        إذا (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            أرجع true;
        } وإلا {
            أرجع SDL_سیٹ_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    إذا (_this->egl_انکڑے->eglBindAPI) {
        _this->egl_انکڑے->eglBindAPI(_this->egl_انکڑے->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    إذا (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_انکڑے->eglMakeCurrent(_this->egl_انکڑے->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } وإلا {
        إذا (!_this->egl_انکڑے->eglMakeCurrent(_this->egl_انکڑے->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            أرجع SDL_EGL_سیٹ_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    أرجع true;
}

bool SDL_EGL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    EGLBoolean حالت;

    إذا (!_this->egl_انکڑے) {
        أرجع SDL_سیٹ_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    إذا (interval < 0) {
        أرجع SDL_سیٹ_Error("Late swap tearing currently unsupported");
    }

    حالت = _this->egl_انکڑے->egl_وٹاندرا_Interval(_this->egl_انکڑے->egl_display, interval);
    إذا (حالت == EGL_TRUE) {
        _this->egl_انکڑے->egl_swapinterval = interval;
        أرجع true;
    }

    أرجع SDL_EGL_سیٹ_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval)
{
    إذا (!_this->egl_انکڑے) {
        أرجع SDL_سیٹ_Error("EGL not initialized");
    }

    *interval = _this->egl_انکڑے->egl_swapinterval;
    أرجع true;
}

bool SDL_EGL_وٹاندرا_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    إذا (!_this->egl_انکڑے->egl_وٹاندرا_Buffers(_this->egl_انکڑے->egl_display, egl_surface)) {
        أرجع SDL_EGL_سیٹ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    أرجع true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    إذا (!_this->egl_انکڑے) {
        أرجع true;
    }

    إذا (egl_context != عدم && egl_context != EGL_NO_CONTEXT) {
        _this->egl_انکڑے->eglDestroyContext(_this->egl_انکڑے->egl_display, egl_context);
    }
    أرجع true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Native_کھڑکی_Type nw)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#جے_انت
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    صحيح attr = 0;

    EGLSurface surface;

    إذا (!SDL_EGL_چنو_Config(_this)) {
        أرجع EGL_NO_SURFACE;
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_انکڑے->eglGetConfigAttrib(_this->egl_انکڑے->egl_display,
                                        _this->egl_انکڑے->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_کھڑکی_سیٹ_Buffers_Geometry(nw, 0, 0, format_wanted);
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    إذا (SDL_strcmp(_this->name, "qnx") == 0) {
        صحيح format = QNX_چنو_Format(_this, _this->egl_انکڑے->egl_config);

        إذا (screen_سیٹ_کھڑکی_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            أرجع EGL_NO_SURFACE;
        }
    }
#جے_انت

#جے_تعریف_شدہ EGL_KHR_gl_colorspace
    إذا (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        إذا (srgbhint && *srgbhint) {
            إذا (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } وإلا {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_خطی_KHR;
            }
        } وإلا إذا (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_خطی_KHR;
        }
    }
#جے_انت

    صحيح opaque_ext_idx = -1;

#جے_تعریف_شدہ EGL_EXT_present_opaque
    إذا (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        إذا (کھڑکی && (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#جے_انت

    إذا (_this->egl_surfaceattrib_callback) {
        ثابت صحيح maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_انکڑے->egl_display, _this->egl_انکڑے->egl_config);
        إذا (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_رستہ = '\0';
            SDL_سیٹ_Error("EGL surface attribute callback returned NULL pointer");
            أرجع EGL_NO_SURFACE;
        }

        لكل (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            إذا (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_رستہ = '\0';
                SDL_سیٹ_Error("EGL surface attribute callback returned too many attributes");
                أرجع EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_انکڑے->egl_Create_کھڑکی_Surface(_this->egl_انکڑے->egl_display, _this->egl_انکڑے->egl_config, nw, &attribs[0]);
    إذا (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        إذا ((_this->egl_انکڑے->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], حجم (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_انکڑے->egl_Create_کھڑکی_Surface(_this->egl_انکڑے->egl_display, _this->egl_انکڑے->egl_config, nw, &attribs[0]);
        }
    }

    إذا (surface == EGL_NO_SURFACE) {
        SDL_EGL_سیٹ_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_کھڑکی_get_Format(nw);
    Android_سیٹ_Format(format_wanted, format_got);
#جے_انت

    أرجع surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, صحيح چوڑائی, صحيح اچائی)
{
    EGLint گن[] = {
        EGL_چوڑائی, 0,
        EGL_اچائی, 0,
        EGL_NONE
    };
    گن[1] = چوڑائی;
    گن[3] = اچائی;

    إذا (!SDL_EGL_چنو_Config(_this)) {
        أرجع EGL_NO_SURFACE;
    }

    أرجع _this->egl_انکڑے->eglCreatePbufferSurface(
        _this->egl_انکڑے->egl_display,
        _this->egl_انکڑے->egl_config,
        گن);
}

فراغ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    إذا (!_this->egl_انکڑے) {
        أرجع;
    }

    إذا (egl_surface != EGL_NO_SURFACE) {
        _this->egl_انکڑے->eglDestroySurface(_this->egl_انکڑے->egl_display, egl_surface);
    }
}

#جے_انت // SDL_VIDEO_OPENGL_EGL
