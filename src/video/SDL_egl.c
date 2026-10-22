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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS)
#شامل "../core/windows/SDL_windows.h"
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
#شامل <android/native_window.h>
#شامل "../video/android/SDL_androidvideo.h"
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
#شامل <screen/screen.h>
#شامل "../video/qnx/SDL_qnx.h"
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
#شامل <unistd.h>
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
#شامل <GLES2/gl2.h>
#اگر_ختم

#شامل "SDL_sysvideo.h"
#شامل "SDL_egl_c.h"
#شامل "../SDL_hints_c.h"

#اگر_تعریف_شدہ EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#اگر_غیر_تعریف_شدہ EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR
#تعریف_کرو EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR 0x00000040
#اگر_ختم
#اگر_ختم // EGL_KHR_create_context

#اگر_غیر_تعریف_شدہ EGL_EXT_pixel_format_float
#تعریف_کرو EGL_EXT_pixel_format_float
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#اگر_ختم // EGL_EXT_pixel_format_float

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_device
#تعریف_کرو EGL_EXT_platform_device 1
#تعریف_کرو EGL_PLATFORM_DEVICE_EXT 0x313F
#اگر_ختم // EGL_EXT_platform_device

#اگر_غیر_تعریف_شدہ EGL_EXT_present_opaque
#تعریف_کرو EGL_EXT_present_opaque 1
#تعریف_کرو EGL_PRESENT_OPAQUE_EXT 0x31DF
#اگر_ختم // EGL_EXT_present_opaque

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#تعریف_کرو DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#تعریف_کرو ALT_EGL            "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#تعریف_کرو ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#تعریف_کرو DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#تعریف_کرو DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#تعریف_کرو ALT_OGL_ES         "libGLESv2.so"

#وگرنہ_اگر defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.so"

#وگرنہ_اگر defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv3.so"

#وگرنہ_اگر defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#تعریف_کرو DEFAULT_EGL        "libEGL.dll"
#تعریف_کرو DEFAULT_OGL        "opengl32.dll"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.dll"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#وگرنہ_اگر defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#تعریف_کرو DEFAULT_EGL        "libEGL.dylib"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.dylib"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#وگرنہ_اگر defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#تعریف_کرو DEFAULT_OGL        "libGL.so"
#تعریف_کرو DEFAULT_EGL        "libEGL.so"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so"
#تعریف_کرو DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#تعریف_کرو DEFAULT_OGL_ES     "libGLESv1_CM.so"

#وگرنہ_اگر defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#تعریف_کرو DEFAULT_EGL        "libEGL.so.1"
#تعریف_کرو DEFAULT_OGL_ES2    "libGLESv2.so.1"

#ورنہ
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
#اگر_ختم // SDL_VIDEO_DRIVER_RPI

#اگر defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#شامل <SDL3/SDL_opengl.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
قسمتعریف خالی (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#اگر_ختم

#اگر defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#تعریف_کرو بھرو_FUNC(TYPE, NAME) \
    _this->egl_ڈیٹا->NAME = NAME;
#ورنہ
#تعریف_کرو بھرو_FUNC(TYPE, NAME)                                                               \
    _this->egl_ڈیٹا->NAME = (TYPE)SDL_بھرو_Function(_this->egl_ڈیٹا->egl_dll_handle, #NAME); \
    اگر (!_this->egl_ڈیٹا->NAME) {                                                     \
        واپس SDL_سیٹ_Error("Could not retrieve EGL function " #NAME);                \
    }
#اگر_ختم

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#تعریف_کرو بھرو_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_ڈیٹا->NAME = (TYPE)_this->egl_ڈیٹا->egl_Get_Proc_پتہ(#NAME);

ساکن ثابت حرف *SDL_EGL_GetErrorName(EGLint egl_Error_رمز)
{
#تعریف_کرو SDL_EGL_ERROR_TRANSLATE(e) \
    حالت e:                        \
        واپس #e
    انتخاب (egl_Error_رمز) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_مطابقت);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_کھڑکی);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_گمشدہ);
    }
    واپس "";
}

bool SDL_EGL_سیٹ_Error_Ex(ثابت حرف *پیغام, ثابت حرف *eglFunctionName, EGLint egl_Error_رمز)
{
    ثابت حرف *error_متن = SDL_EGL_GetErrorName(egl_Error_رمز);
    حرف alt_Error_متن[32];
    اگر (error_متن[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (خالی)SDL_snprintf(alt_Error_متن, SDL_arraysize(alt_Error_متن), "0x%x", (غیرعلامتی صحیح)egl_Error_رمز);
        error_متن = alt_Error_متن;
    }
    واپس SDL_سیٹ_Error("%s (call to %s failed, reporting an error of %s)", پیغام, eglFunctionName, error_متن);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ثابت حرف *ext)
{
    size_t ext_len;
    ثابت حرف *ext_override;
    ثابت حرف *egl_extstr;
    ثابت حرف *ext_آغاز;

    // Invalid extensions can be rejected early
    اگر (!ext || *ext == 0 || SDL_strchr(ext, ' ') != تہی) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        واپس false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    اگر (ext_override) {
        صحیح disable_ext = SDL_atoi(ext_override);
        اگر (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            واپس false;
        } ورنہ اگر (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            واپس false;
        }
    }

    ext_len = SDL_strlen(ext);
    انتخاب (type) {
    حالت SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_ڈیٹا->eglQueryString(_this->egl_ڈیٹا->egl_display, EGL_EXTENSIONS);
        توڑو;
    حالت SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_ڈیٹا->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        توڑو;
    طےشدہ:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        واپس false;
    }

    اگر (egl_extstr) {
        ext_آغاز = egl_extstr;

        جب (*ext_آغاز) {
            ext_آغاز = SDL_strstr(ext_آغاز, ext);
            اگر (!ext_آغاز) {
                واپس false;
            }
            // Check if the match is not just a substring of one of the extensions
            اگر (ext_آغاز == egl_extstr || *(ext_آغاز - 1) == ' ') {
                اگر (ext_آغاز[ext_len] == ' ' || ext_آغاز[ext_len] == 0) {
                    واپس true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_آغاز += ext_len;
            جب (*ext_آغاز != ' ' && *ext_آغاز != 0) {
                ext_آغاز++;
            }
        }
    }

    واپس false;
}

SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ_اندرونی(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر نتیجہ = تہی;
    اگر (_this->egl_ڈیٹا) {
        ثابت Uint32 eglver = (((Uint32)_this->egl_ڈیٹا->egl_نسخہ_major) << 16) | ((Uint32)_this->egl_ڈیٹا->egl_نسخہ_minor);
        ثابت bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        اگر (!نتیجہ && is_egl_15_or_later && _this->egl_ڈیٹا->egl_Get_Proc_پتہ) {
            نتیجہ = _this->egl_ڈیٹا->egl_Get_Proc_پتہ(proc);
        }

#اگر !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        اگر (!نتیجہ) {
            نتیجہ = SDL_بھرو_Function(_this->egl_ڈیٹا->opengl_dll_handle, proc);
        }
#اگر_ختم

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        اگر (!نتیجہ && !is_egl_15_or_later && _this->egl_ڈیٹا->egl_Get_Proc_پتہ) {
            نتیجہ = _this->egl_ڈیٹا->egl_Get_Proc_پتہ(proc);
        }
    }
    واپس نتیجہ;
}

خالی SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    اگر (_this->egl_ڈیٹا) {
        اگر (_this->egl_ڈیٹا->egl_display) {
            _this->egl_ڈیٹا->eglTerminate(_this->egl_ڈیٹا->egl_display);
            _this->egl_ڈیٹا->egl_display = تہی;
        }

        اگر (_this->egl_ڈیٹا->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_ڈیٹا->egl_dll_handle);
            _this->egl_ڈیٹا->egl_dll_handle = تہی;
        }
        اگر (_this->egl_ڈیٹا->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_ڈیٹا->opengl_dll_handle);
            _this->egl_ڈیٹا->opengl_dll_handle = تہی;
        }

        SDL_free(_this->egl_ڈیٹا);
        _this->egl_ڈیٹا = تہی;
    }
}

ساکن bool SDL_EGL_بھرو_Library_اندرونی(SDL_VideoDevice *_this, ثابت حرف *egl_راستہ)
{
    SDL_SharedObject *egl_dll_handle = تہی;
#اگر !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = تہی;
#اگر_ختم
    ثابت حرف *راستہ = تہی;
#اگر defined(SDL_VIDEO_DRIVER_WINDOWS)
    ثابت حرف *d3dcompiler;
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#اگر_ختم

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    اگر (d3dcompiler) {
        اگر (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            اگر (SDL_بھرو_Object(d3dcompiler) == تہی) {
                SDL_ClearError();
            }
        }
    } ورنہ {
        اگر (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ثابت حرف *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            صحیح i;

            برائے (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                اگر (SDL_بھرو_Object(d3dcompiler_list[i]) != تہی) {
                    توڑو;
                }
                SDL_ClearError();
            }
        } ورنہ {
            اگر (SDL_بھرو_Object("d3dcompiler_43.dll") == تہی) {
                SDL_ClearError();
            }
        }
    }
#اگر_ختم

#اگر !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    راستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    اگر (راستہ) {
        opengl_dll_handle = SDL_بھرو_Object(راستہ);
    }

    اگر (!opengl_dll_handle) {
        اگر (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) {
            اگر (_this->gl_config.major_نسخہ > 1) {
#اگر_تعریف_شدہ DEFAULT_OGL_ES2
                اگر (!opengl_dll_handle) {
                    راستہ = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_بھرو_Object(راستہ);
                }
#اگر_ختم
#اگر_تعریف_شدہ ALT_OGL_ES2
                اگر (!opengl_dll_handle && !vc4) {
                    راستہ = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_بھرو_Object(راستہ);
                }
#اگر_ختم
            } ورنہ {
#اگر_تعریف_شدہ DEFAULT_OGL_ES
                اگر (!opengl_dll_handle) {
                    راستہ = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_بھرو_Object(راستہ);
                }
#اگر_ختم
#اگر_تعریف_شدہ DEFAULT_OGL_ES_PVR
                اگر (!opengl_dll_handle) {
                    راستہ = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_بھرو_Object(راستہ);
                }
#اگر_ختم
#اگر_تعریف_شدہ ALT_OGL_ES
                اگر (!opengl_dll_handle && !vc4) {
                    راستہ = ALT_OGL_ES;
                    opengl_dll_handle = SDL_بھرو_Object(راستہ);
                }
#اگر_ختم
            }
        } ورنہ {
#اگر_تعریف_شدہ DEFAULT_OGL
            اگر (!opengl_dll_handle) {
                راستہ = DEFAULT_OGL;
                opengl_dll_handle = SDL_بھرو_Object(راستہ);
            }
#اگر_ختم
#اگر_تعریف_شدہ ALT_OGL
            اگر (!opengl_dll_handle) {
                راستہ = ALT_OGL;
                opengl_dll_handle = SDL_بھرو_Object(راستہ);
            }
#اگر_ختم
        }
    }
    _this->egl_ڈیٹا->opengl_dll_handle = opengl_dll_handle;

    اگر (!opengl_dll_handle) {
        واپس SDL_سیٹ_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    اگر (egl_راستہ) {
        egl_dll_handle = SDL_بھرو_Object(egl_راستہ);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    اگر (!egl_dll_handle || SDL_بھرو_Function(egl_dll_handle, "eglChooseConfig") == تہی) {
        اگر (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        راستہ = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        اگر (!راستہ) {
            راستہ = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_بھرو_Object(راستہ);

#اگر_تعریف_شدہ ALT_EGL
        اگر (!egl_dll_handle && !vc4) {
            راستہ = ALT_EGL;
            egl_dll_handle = SDL_بھرو_Object(راستہ);
        }
#اگر_ختم

        اگر (!egl_dll_handle || SDL_بھرو_Function(egl_dll_handle, "eglChooseConfig") == تہی) {
            اگر (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            واپس SDL_سیٹ_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#اگر_ختم

    _this->egl_ڈیٹا->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    بھرو_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    بھرو_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    بھرو_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    بھرو_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_پتہ);
    بھرو_FUNC(PFNEGLCHOOSECONFIGPROC, egl_انتخاب_Config);
    بھرو_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    بھرو_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    بھرو_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    بھرو_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_کھڑکی_Surface);
    بھرو_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    بھرو_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    بھرو_FUNC(PFNEGLSWAPBUFFERSPROC, egl_تبادلہ_Buffers);
    بھرو_FUNC(PFNEGLSWAPINTERVALPROC, egl_تبادلہ_Interval);
    بھرو_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    بھرو_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    بھرو_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    بھرو_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    بھرو_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    بھرو_FUNC(PFNEGLGETERRORPROC, eglGetError);
    بھرو_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    بھرو_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    بھرو_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    بھرو_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    بھرو_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    بھرو_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    بھرو_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    اگر (راستہ) {
        SDL_strlcpy(_this->gl_config.driver_راستہ, راستہ, حجم(_this->gl_config.driver_راستہ) - 1);
    } ورنہ {
        *_this->gl_config.driver_راستہ = '\0';
    }

    واپس true;
}

bool SDL_EGL_بھرو_Library_Only(SDL_VideoDevice *_this, ثابت حرف *egl_راستہ)
{
    اگر (_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL context already created");
    }

    _this->egl_ڈیٹا = (ساخت SDL_EGL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_EGL_Video_ڈیٹا));
    اگر (!_this->egl_ڈیٹا) {
        واپس false;
    }

    اگر (!SDL_EGL_بھرو_Library_اندرونی(_this, egl_راستہ)) {
        SDL_free(_this->egl_ڈیٹا);
        _this->egl_ڈیٹا = تہی;
        واپس false;
    }
    واپس true;
}

ساکن خالی SDL_EGL_Get_نسخہ(SDL_VideoDevice *_this)
{
    اگر (_this->egl_ڈیٹا->eglQueryString) {
        ثابت حرف *egl_نسخہ = _this->egl_ڈیٹا->eglQueryString(_this->egl_ڈیٹا->egl_display, EGL_نسخہ);
        اگر (egl_نسخہ) {
            صحیح major = 0, minor = 0;
            اگر (SDL_sscanf(egl_نسخہ, "%d.%d", &major, &minor) == 2) {
                _this->egl_ڈیٹا->egl_نسخہ_major = major;
                _this->egl_ڈیٹا->egl_نسخہ_minor = minor;
            } ورنہ {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_نسخہ);
            }
        }
    }
}

bool SDL_EGL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *egl_راستہ, NativeDisplayType native_display)
{
    اگر (!SDL_EGL_بھرو_Library_Only(_this, egl_راستہ)) {
        واپس false;
    }

    _this->egl_ڈیٹا->egl_display = EGL_NO_DISPLAY;

#اگر_غیر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    اگر (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_نسخہ(_this);

        اگر (_this->egl_ڈیٹا->egl_نسخہ_major == 1 && _this->egl_ڈیٹا->egl_نسخہ_minor == 5) {
            بھرو_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        اگر (_this->egl_ڈیٹا->eglGetPlatformDisplay) {
            EGLAttrib *attribs = تہی;
            اگر (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                اگر (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_راستہ = '\0';
                    واپس SDL_سیٹ_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_ڈیٹا->egl_display = _this->egl_ڈیٹا->eglGetPlatformDisplay(platform, (خالی *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } ورنہ {
            اگر (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_ڈیٹا->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_پتہ_اندرونی(_this, "eglGetPlatformDisplayEXT");
                اگر (_this->egl_ڈیٹا->eglGetPlatformDisplayEXT) {
                    _this->egl_ڈیٹا->egl_display = _this->egl_ڈیٹا->eglGetPlatformDisplayEXT(platform, (خالی *)(uintptr_t)native_display, تہی);
                }
            }
        }
    }
#اگر_ختم
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    اگر ((_this->egl_ڈیٹا->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_ڈیٹا->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_ڈیٹا->egl_display = _this->egl_ڈیٹا->eglGetDisplay(native_display);
    }
    اگر (_this->egl_ڈیٹا->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_راستہ = '\0';
        واپس SDL_سیٹ_Error("Could not get EGL display");
    }

    اگر (_this->egl_ڈیٹا->eglInitialize(_this->egl_ڈیٹا->egl_display, تہی, تہی) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_راستہ = '\0';
        واپس SDL_سیٹ_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_نسخہ(_this);

    _this->egl_ڈیٹا->is_offscreen = false;

    واپس true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, صحیح device)
{
    خالی *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint عدد_egl_devices = 0;
    ثابت حرف *egl_device_hint;

    اگر (_this->gl_config.driver_loaded <= 0) {
        واپس SDL_سیٹ_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    اگر (!_this->egl_ڈیٹا->eglQueryDevicesEXT) {
        واپس SDL_سیٹ_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    اگر (!_this->egl_ڈیٹا->eglGetPlatformDisplayEXT) {
        واپس SDL_سیٹ_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    اگر (_this->egl_ڈیٹا->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &عدد_egl_devices) != EGL_TRUE) {
        واپس SDL_سیٹ_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    اگر (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        اگر (device >= عدد_egl_devices) {
            واپس SDL_سیٹ_Error("Invalid EGL device is requested.");
        }

        _this->egl_ڈیٹا->egl_display = _this->egl_ڈیٹا->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], تہی);

        اگر (_this->egl_ڈیٹا->egl_display == EGL_NO_DISPLAY) {
            واپس SDL_سیٹ_Error("eglGetPlatformDisplayEXT() failed.");
        }

        اگر (_this->egl_ڈیٹا->eglInitialize(_this->egl_ڈیٹا->egl_display, تہی, تہی) != EGL_TRUE) {
            واپس SDL_سیٹ_Error("Could not initialize EGL");
        }
    } ورنہ {
        صحیح i;
        bool ملا = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        برائے (i = 0; i < عدد_egl_devices; i++) {
            attempted_egl_display = _this->egl_ڈیٹا->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], تہی);

            اگر (attempted_egl_display == EGL_NO_DISPLAY) {
                جاری;
            }

            اگر (_this->egl_ڈیٹا->eglInitialize(attempted_egl_display, تہی, تہی) != EGL_TRUE) {
                _this->egl_ڈیٹا->eglTerminate(attempted_egl_display);
                جاری;
            }

            // We did not fail, we'll pick this one!
            _this->egl_ڈیٹا->egl_display = attempted_egl_display;
            ملا = true;

            توڑو;
        }

        اگر (!ملا) {
            واپس SDL_سیٹ_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_نسخہ(_this);

    _this->egl_ڈیٹا->is_offscreen = true;

    واپس true;
}

خالی SDL_EGL_سیٹ_Required_Visual_Id(SDL_VideoDevice *_this, صحیح visual_id)
{
    _this->egl_ڈیٹا->egl_required_visual_id = visual_id;
}

#اگر_تعریف_شدہ DUMP_EGL_CONFIG

#تعریف_کرو ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

قسمتعریف ساخت
{
    EGLint attribute;
    حرف ثابت *name;
} Attribute;

ساکن Attribute all_اوصاف[] = {
    ATTRIBUTE(EGL_بفر_سائز),
    ATTRIBUTE(EGL_ALPHA_سائز),
    ATTRIBUTE(EGL_BLUE_سائز),
    ATTRIBUTE(EGL_GREEN_سائز),
    ATTRIBUTE(EGL_RED_سائز),
    ATTRIBUTE(EGL_گہرائی_سائز),
    ATTRIBUTE(EGL_STENCIL_سائز),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_اونچائی),
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
    ATTRIBUTE(EGL_BIND_مقصد_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_مقصد_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_تبادلہ_INTERVAL),
    ATTRIBUTE(EGL_MAX_تبادلہ_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_سائز),
    ATTRIBUTE(EGL_ALPHA_نقاب_سائز),
    ATTRIBUTE(EGL_COLOR_بفر_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_مطابقت_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

ساکن خالی dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    صحیح attr;
    برائے (attr = 0; attr < SDL_arraysize(all_اوصاف); attr++) {
        EGLint قدر;
        _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, config, all_اوصاف[attr].attribute, &قدر);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_اوصاف[attr].name, قدر, قدر);
    }
}

#اگر_ختم // DUMP_EGL_CONFIG

ساکن bool SDL_EGL_نجی_انتخاب_Config(SDL_VideoDevice *_this, bool سیٹ_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint ملا_configs = 0, قدر;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    صحیح i, j, بہترین_bitdiff = -1, بہترین_truecolor_bitdiff = -1;
    صحیح truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_سائز;
    attribs[i++] = _this->gl_config.red_سائز;
    attribs[i++] = EGL_GREEN_سائز;
    attribs[i++] = _this->gl_config.green_سائز;
    attribs[i++] = EGL_BLUE_سائز;
    attribs[i++] = _this->gl_config.blue_سائز;

    اگر (سیٹ_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    اگر (_this->gl_config.alpha_سائز) {
        attribs[i++] = EGL_ALPHA_سائز;
        attribs[i++] = _this->gl_config.alpha_سائز;
    }

    اگر (_this->gl_config.بفر_سائز) {
        attribs[i++] = EGL_بفر_سائز;
        attribs[i++] = _this->gl_config.بفر_سائز;
    }

    اگر (_this->gl_config.گہرائی_سائز) {
        attribs[i++] = EGL_گہرائی_سائز;
        attribs[i++] = _this->gl_config.گہرائی_سائز;
    }

    اگر (_this->gl_config.stencil_سائز) {
        attribs[i++] = EGL_STENCIL_سائز;
        attribs[i++] = _this->gl_config.stencil_سائز;
    }

    اگر (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    اگر (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    اگر (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    اگر (_this->egl_ڈیٹا->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_ثنائی_ہندسہ;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    اگر (_this->gl_config.profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES) {
#اگر_تعریف_شدہ EGL_KHR_create_context
        اگر (_this->gl_config.major_نسخہ >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR;
        } ورنہ
#اگر_ختم
            اگر (_this->gl_config.major_نسخہ >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_ثنائی_ہندسہ;
        } ورنہ {
            attribs[i++] = EGL_OPENGL_ES_ثنائی_ہندسہ;
        }
        _this->egl_ڈیٹا->eglBindAPI(EGL_OPENGL_ES_API);
    } ورنہ {
        attribs[i++] = EGL_OPENGL_ثنائی_ہندسہ;
        _this->egl_ڈیٹا->eglBindAPI(EGL_OPENGL_API);
    }

    اگر (_this->egl_ڈیٹا->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_ڈیٹا->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    اگر (_this->egl_ڈیٹا->egl_انتخاب_Config(_this->egl_ڈیٹا->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &ملا_configs) == EGL_FALSE ||
        ملا_configs == 0) {
        واپس false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    اگر (_this->egl_ڈیٹا->egl_required_visual_id) {
        برائے (i = 0; i < ملا_configs; i++) {
            EGLint format;
            _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            اگر (_this->egl_ڈیٹا->egl_required_visual_id == format) {
                has_matching_format = true;
                توڑو;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    برائے (i = 0; i < ملا_configs; i++) {
        bool is_truecolor = false;
        صحیح bitdiff = 0;

        اگر (has_matching_format && _this->egl_ڈیٹا->egl_required_visual_id) {
            EGLint format;
            _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            اگر (_this->egl_ڈیٹا->egl_required_visual_id != format) {
                جاری;
            }
        }

        _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, configs[i], EGL_RED_سائز, &قدر);
        اگر (قدر == 8) {
            _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, configs[i], EGL_GREEN_سائز, &قدر);
            اگر (قدر == 8) {
                _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, configs[i], EGL_BLUE_سائز, &قدر);
                اگر (قدر == 8) {
                    is_truecolor = true;
                }
            }
        }

        برائے (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            اگر (attribs[j] == EGL_NONE) {
                توڑو;
            }

            اگر (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_سائز ||
                                                    attribs[j] == EGL_GREEN_سائز ||
                                                    attribs[j] == EGL_BLUE_سائز ||
                                                    attribs[j] == EGL_ALPHA_سائز ||
                                                    attribs[j] == EGL_گہرائی_سائز ||
                                                    attribs[j] == EGL_STENCIL_سائز)) {
                _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display, configs[i], attribs[j], &قدر);
                bitdiff += قدر - attribs[j + 1]; // value is always >= attrib
            }
        }

        اگر ((bitdiff < بہترین_bitdiff) || (بہترین_bitdiff == -1)) {
            _this->egl_ڈیٹا->egl_config = configs[i];
            بہترین_bitdiff = bitdiff;
        }

        اگر (is_truecolor && ((bitdiff < بہترین_truecolor_bitdiff) || (بہترین_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            بہترین_truecolor_bitdiff = bitdiff;
        }
    }

#تعریف_کرو FAVOR_TRUECOLOR 1
#اگر FAVOR_TRUECOLOR
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
    اگر (((_this->gl_config.red_سائز + _this->gl_config.blue_سائز + _this->gl_config.green_سائز) <= 16)) {
        اگر (truecolor_config_idx != -1) {
            _this->egl_ڈیٹا->egl_config = configs[truecolor_config_idx];
        }
    }
#اگر_ختم

#اگر_تعریف_شدہ DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_ڈیٹا->egl_config);
#اگر_ختم

    واپس true;
}

bool SDL_EGL_انتخاب_Config(SDL_VideoDevice *_this)
{
    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    اگر (SDL_EGL_نجی_انتخاب_Config(_this, true)) {
        واپس true;
    }

    // Fallback with all configs
    اگر (SDL_EGL_نجی_انتخاب_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        واپس true;
    }

    واپس SDL_EGL_سیٹ_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    صحیح attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_نقاب = _this->gl_config.profile_نقاب;
    EGLint major_نسخہ = _this->gl_config.major_نسخہ;
    EGLint minor_نسخہ = _this->gl_config.minor_نسخہ;
    bool profile_es = (profile_نقاب == SDL_GL_CONTEXT_PROFILE_ES);

    اگر (!_this->egl_ڈیٹا) {
        SDL_سیٹ_Error("EGL not initialized");
        واپس تہی;
    }

    اگر (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    اگر (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        صحیح egl_نسخہ_major = _this->egl_ڈیٹا->egl_نسخہ_major;
        صحیح egl_نسخہ_minor = _this->egl_ڈیٹا->egl_نسخہ_minor;
        اگر (((egl_نسخہ_major < 1) || (egl_نسخہ_major == 1 && egl_نسخہ_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#اگر_ختم

    // Set the context version and other attributes.
    اگر ((major_نسخہ < 3 || (minor_نسخہ == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_نقاب == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        اگر (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_نسخہ;
            attribs[attr++] = SDL_max(major_نسخہ, 1);
        }
    } ورنہ {
#اگر_تعریف_شدہ EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        اگر (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_نسخہ_KHR;
            attribs[attr++] = major_نسخہ;
            attribs[attr++] = EGL_CONTEXT_MINOR_نسخہ_KHR;
            attribs[attr++] = minor_نسخہ;

            // SDL profile bits match EGL profile bits.
            اگر (profile_نقاب != 0 && profile_نقاب != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_نقاب_KHR;
                attribs[attr++] = profile_نقاب;
            }

            // SDL flags match EGL flags.
            اگر (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } ورنہ
#اگر_ختم // EGL_KHR_create_context
        {
            SDL_سیٹ_Error("Could not create EGL context (context attributes are not supported)");
            واپس تہی;
        }
    }

#اگر_تعریف_شدہ EGL_KHR_create_context_no_error
    اگر (_this->gl_config.no_error) {
        اگر (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#اگر_ختم

    اگر (_this->egl_contextattrib_callback) {
        ثابت صحیح maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ڈیٹا->egl_display, _this->egl_ڈیٹا->egl_config);
        اگر (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_راستہ = '\0';
            SDL_سیٹ_Error("EGL context attribute callback returned NULL pointer");
            واپس تہی;
        }

        برائے (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            اگر (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_راستہ = '\0';
                SDL_سیٹ_Error("EGL context attribute callback returned too many attributes");
                واپس تہی;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    اگر (profile_es) {
        _this->egl_ڈیٹا->apitype = EGL_OPENGL_ES_API;
    } ورنہ {
        _this->egl_ڈیٹا->apitype = EGL_OPENGL_API;
    }
    اگر (!_this->egl_ڈیٹا->eglBindAPI(_this->egl_ڈیٹا->apitype)) {
        SDL_سیٹ_Error("Could not bind EGL API");
        واپس تہی;
    }

    egl_context = _this->egl_ڈیٹا->eglCreateContext(_this->egl_ڈیٹا->egl_display,
                                                    _this->egl_ڈیٹا->egl_config,
                                                    share_context, attribs);

    اگر (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_سیٹ_Error("Could not create EGL context", "eglCreateContext");
        واپس تہی;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_ڈیٹا->egl_swapinterval = 0;

    اگر (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        واپس تہی;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    اگر ((_this->egl_ڈیٹا->egl_نسخہ_major > 1) ||
        ((_this->egl_ڈیٹا->egl_نسخہ_major == 1) && (_this->egl_ڈیٹا->egl_نسخہ_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        اگر (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            اگر (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#اگر defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } ورنہ {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
            اگر (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_نسخہ, &v);
                اگر (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#اگر_ختم
        }
    }

    SDL_EGL_سیٹ_تبادلہ_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    واپس (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    اگر (!_this->egl_ڈیٹا->eglMakeCurrent) {
        اگر (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            واپس true;
        } ورنہ {
            واپس SDL_سیٹ_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    اگر (_this->egl_ڈیٹا->eglBindAPI) {
        _this->egl_ڈیٹا->eglBindAPI(_this->egl_ڈیٹا->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    اگر (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_ڈیٹا->eglMakeCurrent(_this->egl_ڈیٹا->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } ورنہ {
        اگر (!_this->egl_ڈیٹا->eglMakeCurrent(_this->egl_ڈیٹا->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            واپس SDL_EGL_سیٹ_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    واپس true;
}

bool SDL_EGL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    EGLBoolean حالت_2;

    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    اگر (interval < 0) {
        واپس SDL_سیٹ_Error("Late swap tearing currently unsupported");
    }

    حالت_2 = _this->egl_ڈیٹا->egl_تبادلہ_Interval(_this->egl_ڈیٹا->egl_display, interval);
    اگر (حالت_2 == EGL_TRUE) {
        _this->egl_ڈیٹا->egl_swapinterval = interval;
        واپس true;
    }

    واپس SDL_EGL_سیٹ_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval)
{
    اگر (!_this->egl_ڈیٹا) {
        واپس SDL_سیٹ_Error("EGL not initialized");
    }

    *interval = _this->egl_ڈیٹا->egl_swapinterval;
    واپس true;
}

bool SDL_EGL_تبادلہ_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    اگر (!_this->egl_ڈیٹا->egl_تبادلہ_Buffers(_this->egl_ڈیٹا->egl_display, egl_surface)) {
        واپس SDL_EGL_سیٹ_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    واپس true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    اگر (!_this->egl_ڈیٹا) {
        واپس true;
    }

    اگر (egl_context != تہی && egl_context != EGL_NO_CONTEXT) {
        _this->egl_ڈیٹا->eglDestroyContext(_this->egl_ڈیٹا->egl_display, egl_context);
    }
    واپس true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Native_کھڑکی_Type nw)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#اگر_ختم
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    صحیح attr = 0;

    EGLSurface surface;

    اگر (!SDL_EGL_انتخاب_Config(_this)) {
        واپس EGL_NO_SURFACE;
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_ڈیٹا->eglGetConfigAttrib(_this->egl_ڈیٹا->egl_display,
                                        _this->egl_ڈیٹا->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_کھڑکی_سیٹ_Buffers_Geometry(nw, 0, 0, format_wanted);
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    اگر (SDL_strcmp(_this->name, "qnx") == 0) {
        صحیح format = QNX_انتخاب_Format(_this, _this->egl_ڈیٹا->egl_config);

        اگر (screen_سیٹ_کھڑکی_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            واپس EGL_NO_SURFACE;
        }
    }
#اگر_ختم

#اگر_تعریف_شدہ EGL_KHR_gl_colorspace
    اگر (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        اگر (srgbhint && *srgbhint) {
            اگر (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } ورنہ {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_خطی_KHR;
            }
        } ورنہ اگر (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_خطی_KHR;
        }
    }
#اگر_ختم

    صحیح opaque_ext_idx = -1;

#اگر_تعریف_شدہ EGL_EXT_present_opaque
    اگر (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        اگر (کھڑکی && (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#اگر_ختم

    اگر (_this->egl_surfaceattrib_callback) {
        ثابت صحیح maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_ڈیٹا->egl_display, _this->egl_ڈیٹا->egl_config);
        اگر (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_راستہ = '\0';
            SDL_سیٹ_Error("EGL surface attribute callback returned NULL pointer");
            واپس EGL_NO_SURFACE;
        }

        برائے (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            اگر (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_راستہ = '\0';
                SDL_سیٹ_Error("EGL surface attribute callback returned too many attributes");
                واپس EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_ڈیٹا->egl_Create_کھڑکی_Surface(_this->egl_ڈیٹا->egl_display, _this->egl_ڈیٹا->egl_config, nw, &attribs[0]);
    اگر (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        اگر ((_this->egl_ڈیٹا->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], حجم (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_ڈیٹا->egl_Create_کھڑکی_Surface(_this->egl_ڈیٹا->egl_display, _this->egl_ڈیٹا->egl_config, nw, &attribs[0]);
        }
    }

    اگر (surface == EGL_NO_SURFACE) {
        SDL_EGL_سیٹ_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_کھڑکی_get_Format(nw);
    Android_سیٹ_Format(format_wanted, format_got);
#اگر_ختم

    واپس surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, صحیح چوڑائی, صحیح اونچائی)
{
    EGLint اوصاف[] = {
        EGL_چوڑائی, 0,
        EGL_اونچائی, 0,
        EGL_NONE
    };
    اوصاف[1] = چوڑائی;
    اوصاف[3] = اونچائی;

    اگر (!SDL_EGL_انتخاب_Config(_this)) {
        واپس EGL_NO_SURFACE;
    }

    واپس _this->egl_ڈیٹا->eglCreatePbufferSurface(
        _this->egl_ڈیٹا->egl_display,
        _this->egl_ڈیٹا->egl_config,
        اوصاف);
}

خالی SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    اگر (!_this->egl_ڈیٹا) {
        واپس;
    }

    اگر (egl_surface != EGL_NO_SURFACE) {
        _this->egl_ڈیٹا->eglDestroySurface(_this->egl_ڈیٹا->egl_display, egl_surface);
    }
}

#اگر_ختم // SDL_VIDEO_OPENGL_EGL
