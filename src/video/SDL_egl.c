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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_OPENGL_EGL

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS)
#অন্তর্ভাব "../core/windows/SDL_windows.h"
#endif
#ifdef SDL_VIDEO_DRIVER_ANDROID
#অন্তর্ভাব <android/native_window.h>
#অন্তর্ভাব "../video/android/SDL_androidvideo.h"
#endif
#ifdef SDL_VIDEO_DRIVER_QNX
#অন্তর্ভাব <screen/screen.h>
#অন্তর্ভাব "../video/qnx/SDL_qnx.h"
#endif
#ifdef SDL_VIDEO_DRIVER_RPI
#অন্তর্ভাব <unistd.h>
#endif
#ifdef SDL_VIDEO_VITA_PVR_OGL
#অন্তর্ভাব <GLES2/gl2.h>
#endif

#অন্তর্ভাব "SDL_sysvideo.h"
#অন্তর্ভাব "SDL_egl_c.h"
#অন্তর্ভাব "../SDL_hints_c.h"

#ifdef EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#ifndef EGL_OPENGL_ES3_BIT_KHR
#define EGL_OPENGL_ES3_BIT_KHR 0x00000040
#endif
#endif // EGL_KHR_create_context

#ifndef EGL_EXT_pixel_format_float
#define EGL_EXT_pixel_format_float
#define EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#define EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#define EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#endif // EGL_EXT_pixel_format_float

#ifndef EGL_EXT_platform_device
#define EGL_EXT_platform_device 1
#define EGL_PLATFORM_DEVICE_EXT 0x313F
#endif // EGL_EXT_platform_device

#ifndef EGL_EXT_present_opaque
#define EGL_EXT_present_opaque 1
#define EGL_PRESENT_OPAQUE_EXT 0x31DF
#endif // EGL_EXT_present_opaque

#ifdef SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#define DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#define ALT_EGL            "libEGL.so"
#define DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#define ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#define DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#define DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#define ALT_OGL_ES         "libGLESv2.so"

#নোচেদ্যদি defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#define DEFAULT_EGL        "libEGL.so"
#define DEFAULT_OGL_ES2    "libGLESv2.so"
#define DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#define DEFAULT_OGL_ES     "libGLESv1_CM.so"

#নোচেদ্যদি defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#define DEFAULT_EGL        "libEGL.so"
#define DEFAULT_OGL_ES2    "libGLESv3.so"

#নোচেদ্যদি defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#define DEFAULT_EGL        "libEGL.dll"
#define DEFAULT_OGL        "opengl32.dll"
#define DEFAULT_OGL_ES2    "libGLESv2.dll"
#define DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#define DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#নোচেদ্যদি defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#define DEFAULT_EGL        "libEGL.dylib"
#define DEFAULT_OGL_ES2    "libGLESv2.dylib"
#define DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#define DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#নোচেদ্যদি defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#define DEFAULT_OGL        "libGL.so"
#define DEFAULT_EGL        "libEGL.so"
#define DEFAULT_OGL_ES2    "libGLESv2.so"
#define DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#define DEFAULT_OGL_ES     "libGLESv1_CM.so"

#নোচেদ্যদি defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#define DEFAULT_EGL        "libEGL.so.1"
#define DEFAULT_OGL_ES2    "libGLESv2.so.1"

#অন্যথা
// Desktop Linux/Unix-like
#define DEFAULT_OGL        "libGL.so.1"
#define DEFAULT_EGL        "libEGL.so.1"
#define ALT_OGL            "libOpenGL.so.0"
#define DEFAULT_OGL_ES2    "libGLESv2.so.2"
#define DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#define DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    DEFAULT_OGL_ES
)
#endif // SDL_VIDEO_DRIVER_RPI

#যদি defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#অন্তর্ভাব <SDL3/SDL_opengl.h>
#endif

#ifdef SDL_VIDEO_OPENGL
প্রকারনির্দেশ শূন্য (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#endif

#যদি defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#define LOAD_FUNC(TYPE, NAME) \
    _this->egl_data->NAME = NAME;
#অন্যথা
#define LOAD_FUNC(TYPE, NAME)                                                               \
    _this->egl_data->NAME = (TYPE)SDL_LoadFunction(_this->egl_data->egl_dll_handle, #NAME); \
    যদি (!_this->egl_data->NAME) {                                                     \
        প্রত্যাগম SDL_SetError("Could not retrieve EGL function " #NAME);                \
    }
#endif

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#define LOAD_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_data->NAME = (TYPE)_this->egl_data->eglGetProcAddress(#NAME);

স্থির ধ্রুব বর্ণ *SDL_EGL_GetErrorName(EGLint eglErrorCode)
{
#define SDL_EGL_ERROR_TRANSLATE(e) \
    পক্ষ e:                        \
        প্রত্যাগম #e
    বিকল্প (eglErrorCode) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_MATCH);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_WINDOW);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_LOST);
    }
    প্রত্যাগম "";
}

bool SDL_EGL_SetErrorEx(ধ্রুব বর্ণ *message, ধ্রুব বর্ণ *eglFunctionName, EGLint eglErrorCode)
{
    ধ্রুব বর্ণ *errorText = SDL_EGL_GetErrorName(eglErrorCode);
    বর্ণ altErrorText[32];
    যদি (errorText[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (শূন্য)SDL_snprintf(altErrorText, SDL_arraysize(altErrorText), "0x%x", (unsigned পূর্ণাঙ্ক)eglErrorCode);
        errorText = altErrorText;
    }
    প্রত্যাগম SDL_SetError("%s (call to %s failed, reporting an error of %s)", message, eglFunctionName, errorText);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ধ্রুব বর্ণ *ext)
{
    size_t ext_len;
    ধ্রুব বর্ণ *ext_override;
    ধ্রুব বর্ণ *egl_extstr;
    ধ্রুব বর্ণ *ext_start;

    // Invalid extensions can be rejected early
    যদি (!ext || *ext == 0 || SDL_strchr(ext, ' ') != রিক্ত) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        প্রত্যাগম false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    যদি (ext_override) {
        পূর্ণাঙ্ক disable_ext = SDL_atoi(ext_override);
        যদি (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            প্রত্যাগম false;
        } অন্যথা যদি (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            প্রত্যাগম false;
        }
    }

    ext_len = SDL_strlen(ext);
    বিকল্প (type) {
    পক্ষ SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_data->eglQueryString(_this->egl_data->egl_display, EGL_EXTENSIONS);
        ভঙ্গ;
    পক্ষ SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_data->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        ভঙ্গ;
    স্বভাব:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        প্রত্যাগম false;
    }

    যদি (egl_extstr) {
        ext_start = egl_extstr;

        যাবত্ (*ext_start) {
            ext_start = SDL_strstr(ext_start, ext);
            যদি (!ext_start) {
                প্রত্যাগম false;
            }
            // Check if the match is not just a substring of one of the extensions
            যদি (ext_start == egl_extstr || *(ext_start - 1) == ' ') {
                যদি (ext_start[ext_len] == ' ' || ext_start[ext_len] == 0) {
                    প্রত্যাগম true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_start += ext_len;
            যাবত্ (*ext_start != ' ' && *ext_start != 0) {
                ext_start++;
            }
        }
    }

    প্রত্যাগম false;
}

SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, ধ্রুব বর্ণ *proc)
{
    SDL_FunctionPointer result = রিক্ত;
    যদি (_this->egl_data) {
        ধ্রুব Uint32 eglver = (((Uint32)_this->egl_data->egl_version_major) << 16) | ((Uint32)_this->egl_data->egl_version_minor);
        ধ্রুব bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        যদি (!result && is_egl_15_or_later && _this->egl_data->eglGetProcAddress) {
            result = _this->egl_data->eglGetProcAddress(proc);
        }

#যদি !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        যদি (!result) {
            result = SDL_LoadFunction(_this->egl_data->opengl_dll_handle, proc);
        }
#endif

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        যদি (!result && !is_egl_15_or_later && _this->egl_data->eglGetProcAddress) {
            result = _this->egl_data->eglGetProcAddress(proc);
        }
    }
    প্রত্যাগম result;
}

শূন্য SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    যদি (_this->egl_data) {
        যদি (_this->egl_data->egl_display) {
            _this->egl_data->eglTerminate(_this->egl_data->egl_display);
            _this->egl_data->egl_display = রিক্ত;
        }

        যদি (_this->egl_data->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_data->egl_dll_handle);
            _this->egl_data->egl_dll_handle = রিক্ত;
        }
        যদি (_this->egl_data->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_data->opengl_dll_handle);
            _this->egl_data->opengl_dll_handle = রিক্ত;
        }

        SDL_free(_this->egl_data);
        _this->egl_data = রিক্ত;
    }
}

স্থির bool SDL_EGL_LoadLibraryInternal(SDL_VideoDevice *_this, ধ্রুব বর্ণ *egl_path)
{
    SDL_SharedObject *egl_dll_handle = রিক্ত;
#যদি !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = রিক্ত;
#endif
    ধ্রুব বর্ণ *path = রিক্ত;
#যদি defined(SDL_VIDEO_DRIVER_WINDOWS)
    ধ্রুব বর্ণ *d3dcompiler;
#endif
#ifdef SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#endif

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    যদি (d3dcompiler) {
        যদি (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            যদি (SDL_LoadObject(d3dcompiler) == রিক্ত) {
                SDL_ClearError();
            }
        }
    } অন্যথা {
        যদি (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ধ্রুব বর্ণ *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            পূর্ণাঙ্ক i;

            প্রতি (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                যদি (SDL_LoadObject(d3dcompiler_list[i]) != রিক্ত) {
                    ভঙ্গ;
                }
                SDL_ClearError();
            }
        } অন্যথা {
            যদি (SDL_LoadObject("d3dcompiler_43.dll") == রিক্ত) {
                SDL_ClearError();
            }
        }
    }
#endif

#যদি !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    যদি (path) {
        opengl_dll_handle = SDL_LoadObject(path);
    }

    যদি (!opengl_dll_handle) {
        যদি (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) {
            যদি (_this->gl_config.major_version > 1) {
#ifdef DEFAULT_OGL_ES2
                যদি (!opengl_dll_handle) {
                    path = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_LoadObject(path);
                }
#endif
#ifdef ALT_OGL_ES2
                যদি (!opengl_dll_handle && !vc4) {
                    path = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_LoadObject(path);
                }
#endif
            } অন্যথা {
#ifdef DEFAULT_OGL_ES
                যদি (!opengl_dll_handle) {
                    path = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_LoadObject(path);
                }
#endif
#ifdef DEFAULT_OGL_ES_PVR
                যদি (!opengl_dll_handle) {
                    path = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_LoadObject(path);
                }
#endif
#ifdef ALT_OGL_ES
                যদি (!opengl_dll_handle && !vc4) {
                    path = ALT_OGL_ES;
                    opengl_dll_handle = SDL_LoadObject(path);
                }
#endif
            }
        } অন্যথা {
#ifdef DEFAULT_OGL
            যদি (!opengl_dll_handle) {
                path = DEFAULT_OGL;
                opengl_dll_handle = SDL_LoadObject(path);
            }
#endif
#ifdef ALT_OGL
            যদি (!opengl_dll_handle) {
                path = ALT_OGL;
                opengl_dll_handle = SDL_LoadObject(path);
            }
#endif
        }
    }
    _this->egl_data->opengl_dll_handle = opengl_dll_handle;

    যদি (!opengl_dll_handle) {
        প্রত্যাগম SDL_SetError("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    যদি (egl_path) {
        egl_dll_handle = SDL_LoadObject(egl_path);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    যদি (!egl_dll_handle || SDL_LoadFunction(egl_dll_handle, "eglChooseConfig") == রিক্ত) {
        যদি (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        path = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        যদি (!path) {
            path = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_LoadObject(path);

#ifdef ALT_EGL
        যদি (!egl_dll_handle && !vc4) {
            path = ALT_EGL;
            egl_dll_handle = SDL_LoadObject(path);
        }
#endif

        যদি (!egl_dll_handle || SDL_LoadFunction(egl_dll_handle, "eglChooseConfig") == রিক্ত) {
            যদি (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            প্রত্যাগম SDL_SetError("Could not load EGL library");
        }
        SDL_ClearError();
    }
#endif

    _this->egl_data->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    LOAD_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    LOAD_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    LOAD_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    LOAD_FUNC(PFNEGLGETPROCADDRESSPROC, eglGetProcAddress);
    LOAD_FUNC(PFNEGLCHOOSECONFIGPROC, eglChooseConfig);
    LOAD_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    LOAD_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    LOAD_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    LOAD_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, eglCreateWindowSurface);
    LOAD_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    LOAD_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    LOAD_FUNC(PFNEGLSWAPBUFFERSPROC, eglSwapBuffers);
    LOAD_FUNC(PFNEGLSWAPINTERVALPROC, eglSwapInterval);
    LOAD_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    LOAD_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    LOAD_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    LOAD_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    LOAD_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    LOAD_FUNC(PFNEGLGETERRORPROC, eglGetError);
    LOAD_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    LOAD_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    LOAD_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    LOAD_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    LOAD_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    LOAD_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    LOAD_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    যদি (path) {
        SDL_strlcpy(_this->gl_config.driver_path, path, পরিমাণ(_this->gl_config.driver_path) - 1);
    } অন্যথা {
        *_this->gl_config.driver_path = '\0';
    }

    প্রত্যাগম true;
}

bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, ধ্রুব বর্ণ *egl_path)
{
    যদি (_this->egl_data) {
        প্রত্যাগম SDL_SetError("EGL context already created");
    }

    _this->egl_data = (সংরচনা SDL_EGL_VideoData *)SDL_calloc(1, পরিমাণ(SDL_EGL_VideoData));
    যদি (!_this->egl_data) {
        প্রত্যাগম false;
    }

    যদি (!SDL_EGL_LoadLibraryInternal(_this, egl_path)) {
        SDL_free(_this->egl_data);
        _this->egl_data = রিক্ত;
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

স্থির শূন্য SDL_EGL_GetVersion(SDL_VideoDevice *_this)
{
    যদি (_this->egl_data->eglQueryString) {
        ধ্রুব বর্ণ *egl_version = _this->egl_data->eglQueryString(_this->egl_data->egl_display, EGL_VERSION);
        যদি (egl_version) {
            পূর্ণাঙ্ক major = 0, minor = 0;
            যদি (SDL_sscanf(egl_version, "%d.%d", &major, &minor) == 2) {
                _this->egl_data->egl_version_major = major;
                _this->egl_data->egl_version_minor = minor;
            } অন্যথা {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_version);
            }
        }
    }
}

bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুব বর্ণ *egl_path, NativeDisplayType native_display)
{
    যদি (!SDL_EGL_LoadLibraryOnly(_this, egl_path)) {
        প্রত্যাগম false;
    }

    _this->egl_data->egl_display = EGL_NO_DISPLAY;

#ifndef SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    যদি (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_GetVersion(_this);

        যদি (_this->egl_data->egl_version_major == 1 && _this->egl_data->egl_version_minor == 5) {
            LOAD_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        যদি (_this->egl_data->eglGetPlatformDisplay) {
            EGLAttrib *attribs = রিক্ত;
            যদি (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                যদি (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_path = '\0';
                    প্রত্যাগম SDL_SetError("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_data->egl_display = _this->egl_data->eglGetPlatformDisplay(platform, (শূন্য *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } অন্যথা {
            যদি (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_data->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_GetProcAddressInternal(_this, "eglGetPlatformDisplayEXT");
                যদি (_this->egl_data->eglGetPlatformDisplayEXT) {
                    _this->egl_data->egl_display = _this->egl_data->eglGetPlatformDisplayEXT(platform, (শূন্য *)(uintptr_t)native_display, রিক্ত);
                }
            }
        }
    }
#endif
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    যদি ((_this->egl_data->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_data->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_data->egl_display = _this->egl_data->eglGetDisplay(native_display);
    }
    যদি (_this->egl_data->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_path = '\0';
        প্রত্যাগম SDL_SetError("Could not get EGL display");
    }

    যদি (_this->egl_data->eglInitialize(_this->egl_data->egl_display, রিক্ত, রিক্ত) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_path = '\0';
        প্রত্যাগম SDL_SetError("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_GetVersion(_this);

    _this->egl_data->is_offscreen = false;

    প্রত্যাগম true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, পূর্ণাঙ্ক device)
{
    শূন্য *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint অঙ্ক_egl_devices = 0;
    ধ্রুব বর্ণ *egl_device_hint;

    যদি (_this->gl_config.driver_loaded <= 0) {
        প্রত্যাগম SDL_SetError("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    যদি (!_this->egl_data->eglQueryDevicesEXT) {
        প্রত্যাগম SDL_SetError("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    যদি (!_this->egl_data->eglGetPlatformDisplayEXT) {
        প্রত্যাগম SDL_SetError("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    যদি (_this->egl_data->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &অঙ্ক_egl_devices) != EGL_TRUE) {
        প্রত্যাগম SDL_SetError("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    যদি (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        যদি (device >= অঙ্ক_egl_devices) {
            প্রত্যাগম SDL_SetError("Invalid EGL device is requested.");
        }

        _this->egl_data->egl_display = _this->egl_data->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], রিক্ত);

        যদি (_this->egl_data->egl_display == EGL_NO_DISPLAY) {
            প্রত্যাগম SDL_SetError("eglGetPlatformDisplayEXT() failed.");
        }

        যদি (_this->egl_data->eglInitialize(_this->egl_data->egl_display, রিক্ত, রিক্ত) != EGL_TRUE) {
            প্রত্যাগম SDL_SetError("Could not initialize EGL");
        }
    } অন্যথা {
        পূর্ণাঙ্ক i;
        bool found = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        প্রতি (i = 0; i < অঙ্ক_egl_devices; i++) {
            attempted_egl_display = _this->egl_data->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], রিক্ত);

            যদি (attempted_egl_display == EGL_NO_DISPLAY) {
                অনুবর্ত;
            }

            যদি (_this->egl_data->eglInitialize(attempted_egl_display, রিক্ত, রিক্ত) != EGL_TRUE) {
                _this->egl_data->eglTerminate(attempted_egl_display);
                অনুবর্ত;
            }

            // We did not fail, we'll pick this one!
            _this->egl_data->egl_display = attempted_egl_display;
            found = true;

            ভঙ্গ;
        }

        যদি (!found) {
            প্রত্যাগম SDL_SetError("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_GetVersion(_this);

    _this->egl_data->is_offscreen = true;

    প্রত্যাগম true;
}

শূন্য SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, পূর্ণাঙ্ক visual_id)
{
    _this->egl_data->egl_required_visual_id = visual_id;
}

#ifdef DUMP_EGL_CONFIG

#define ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

প্রকারনির্দেশ সংরচনা
{
    EGLint attribute;
    বর্ণ ধ্রুব *name;
} Attribute;

স্থির Attribute all_attributes[] = {
    ATTRIBUTE(EGL_BUFFER_SIZE),
    ATTRIBUTE(EGL_ALPHA_SIZE),
    ATTRIBUTE(EGL_BLUE_SIZE),
    ATTRIBUTE(EGL_GREEN_SIZE),
    ATTRIBUTE(EGL_RED_SIZE),
    ATTRIBUTE(EGL_DEPTH_SIZE),
    ATTRIBUTE(EGL_STENCIL_SIZE),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_HEIGHT),
    ATTRIBUTE(EGL_MAX_PBUFFER_WIDTH),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_মান),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_মান),
    ATTRIBUTE(EGL_TRANSPARENT_RED_মান),
    ATTRIBUTE(EGL_BIND_TO_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_TO_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_SWAP_INTERVAL),
    ATTRIBUTE(EGL_MAX_SWAP_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_SIZE),
    ATTRIBUTE(EGL_ALPHA_MASK_SIZE),
    ATTRIBUTE(EGL_COLOR_BUFFER_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_MATCH_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

স্থির শূন্য dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    পূর্ণাঙ্ক attr;
    প্রতি (attr = 0; attr < SDL_arraysize(all_attributes); attr++) {
        EGLint মান;
        _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, config, all_attributes[attr].attribute, &মান);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_attributes[attr].name, মান, মান);
    }
}

#endif // DUMP_EGL_CONFIG

স্থির bool SDL_EGL_PrivateChooseConfig(SDL_VideoDevice *_this, bool set_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint found_configs = 0, মান;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    পূর্ণাঙ্ক i, j, best_bitdiff = -1, best_truecolor_bitdiff = -1;
    পূর্ণাঙ্ক truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_SIZE;
    attribs[i++] = _this->gl_config.red_size;
    attribs[i++] = EGL_GREEN_SIZE;
    attribs[i++] = _this->gl_config.green_size;
    attribs[i++] = EGL_BLUE_SIZE;
    attribs[i++] = _this->gl_config.blue_size;

    যদি (set_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    যদি (_this->gl_config.alpha_size) {
        attribs[i++] = EGL_ALPHA_SIZE;
        attribs[i++] = _this->gl_config.alpha_size;
    }

    যদি (_this->gl_config.buffer_size) {
        attribs[i++] = EGL_BUFFER_SIZE;
        attribs[i++] = _this->gl_config.buffer_size;
    }

    যদি (_this->gl_config.depth_size) {
        attribs[i++] = EGL_DEPTH_SIZE;
        attribs[i++] = _this->gl_config.depth_size;
    }

    যদি (_this->gl_config.stencil_size) {
        attribs[i++] = EGL_STENCIL_SIZE;
        attribs[i++] = _this->gl_config.stencil_size;
    }

    যদি (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    যদি (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    যদি (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    যদি (_this->egl_data->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_BIT;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    যদি (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) {
#ifdef EGL_KHR_create_context
        যদি (_this->gl_config.major_version >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_BIT_KHR;
        } অন্যথা
#endif
            যদি (_this->gl_config.major_version >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_BIT;
        } অন্যথা {
            attribs[i++] = EGL_OPENGL_ES_BIT;
        }
        _this->egl_data->eglBindAPI(EGL_OPENGL_ES_API);
    } অন্যথা {
        attribs[i++] = EGL_OPENGL_BIT;
        _this->egl_data->eglBindAPI(EGL_OPENGL_API);
    }

    যদি (_this->egl_data->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_data->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    যদি (_this->egl_data->eglChooseConfig(_this->egl_data->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &found_configs) == EGL_FALSE ||
        found_configs == 0) {
        প্রত্যাগম false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    যদি (_this->egl_data->egl_required_visual_id) {
        প্রতি (i = 0; i < found_configs; i++) {
            EGLint format;
            _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            যদি (_this->egl_data->egl_required_visual_id == format) {
                has_matching_format = true;
                ভঙ্গ;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    প্রতি (i = 0; i < found_configs; i++) {
        bool is_truecolor = false;
        পূর্ণাঙ্ক bitdiff = 0;

        যদি (has_matching_format && _this->egl_data->egl_required_visual_id) {
            EGLint format;
            _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            যদি (_this->egl_data->egl_required_visual_id != format) {
                অনুবর্ত;
            }
        }

        _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, configs[i], EGL_RED_SIZE, &মান);
        যদি (মান == 8) {
            _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, configs[i], EGL_GREEN_SIZE, &মান);
            যদি (মান == 8) {
                _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, configs[i], EGL_BLUE_SIZE, &মান);
                যদি (মান == 8) {
                    is_truecolor = true;
                }
            }
        }

        প্রতি (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            যদি (attribs[j] == EGL_NONE) {
                ভঙ্গ;
            }

            যদি (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_SIZE ||
                                                    attribs[j] == EGL_GREEN_SIZE ||
                                                    attribs[j] == EGL_BLUE_SIZE ||
                                                    attribs[j] == EGL_ALPHA_SIZE ||
                                                    attribs[j] == EGL_DEPTH_SIZE ||
                                                    attribs[j] == EGL_STENCIL_SIZE)) {
                _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display, configs[i], attribs[j], &মান);
                bitdiff += মান - attribs[j + 1]; // value is always >= attrib
            }
        }

        যদি ((bitdiff < best_bitdiff) || (best_bitdiff == -1)) {
            _this->egl_data->egl_config = configs[i];
            best_bitdiff = bitdiff;
        }

        যদি (is_truecolor && ((bitdiff < best_truecolor_bitdiff) || (best_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            best_truecolor_bitdiff = bitdiff;
        }
    }

#define FAVOR_TRUECOLOR 1
#যদি FAVOR_TRUECOLOR
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
    যদি (((_this->gl_config.red_size + _this->gl_config.blue_size + _this->gl_config.green_size) <= 16)) {
        যদি (truecolor_config_idx != -1) {
            _this->egl_data->egl_config = configs[truecolor_config_idx];
        }
    }
#endif

#ifdef DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_data->egl_config);
#endif

    প্রত্যাগম true;
}

bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this)
{
    যদি (!_this->egl_data) {
        প্রত্যাগম SDL_SetError("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    যদি (SDL_EGL_PrivateChooseConfig(_this, true)) {
        প্রত্যাগম true;
    }

    // Fallback with all configs
    যদি (SDL_EGL_PrivateChooseConfig(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        প্রত্যাগম true;
    }

    প্রত্যাগম SDL_EGL_SetError("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    পূর্ণাঙ্ক attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_mask = _this->gl_config.profile_mask;
    EGLint major_version = _this->gl_config.major_version;
    EGLint minor_version = _this->gl_config.minor_version;
    bool profile_es = (profile_mask == SDL_GL_CONTEXT_PROFILE_ES);

    যদি (!_this->egl_data) {
        SDL_SetError("EGL not initialized");
        প্রত্যাগম রিক্ত;
    }

    যদি (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#ifdef SDL_VIDEO_DRIVER_ANDROID
    যদি (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        পূর্ণাঙ্ক egl_version_major = _this->egl_data->egl_version_major;
        পূর্ণাঙ্ক egl_version_minor = _this->egl_data->egl_version_minor;
        যদি (((egl_version_major < 1) || (egl_version_major == 1 && egl_version_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#endif

    // Set the context version and other attributes.
    যদি ((major_version < 3 || (minor_version == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_mask == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        যদি (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_VERSION;
            attribs[attr++] = SDL_max(major_version, 1);
        }
    } অন্যথা {
#ifdef EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        যদি (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_VERSION_KHR;
            attribs[attr++] = major_version;
            attribs[attr++] = EGL_CONTEXT_MINOR_VERSION_KHR;
            attribs[attr++] = minor_version;

            // SDL profile bits match EGL profile bits.
            যদি (profile_mask != 0 && profile_mask != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR;
                attribs[attr++] = profile_mask;
            }

            // SDL flags match EGL flags.
            যদি (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } অন্যথা
#endif // EGL_KHR_create_context
        {
            SDL_SetError("Could not create EGL context (context attributes are not supported)");
            প্রত্যাগম রিক্ত;
        }
    }

#ifdef EGL_KHR_create_context_no_error
    যদি (_this->gl_config.no_error) {
        যদি (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#endif

    যদি (_this->egl_contextattrib_callback) {
        ধ্রুব পূর্ণাঙ্ক maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_data->egl_display, _this->egl_data->egl_config);
        যদি (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_path = '\0';
            SDL_SetError("EGL context attribute callback returned NULL pointer");
            প্রত্যাগম রিক্ত;
        }

        প্রতি (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            যদি (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_path = '\0';
                SDL_SetError("EGL context attribute callback returned too many attributes");
                প্রত্যাগম রিক্ত;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    যদি (profile_es) {
        _this->egl_data->apitype = EGL_OPENGL_ES_API;
    } অন্যথা {
        _this->egl_data->apitype = EGL_OPENGL_API;
    }
    যদি (!_this->egl_data->eglBindAPI(_this->egl_data->apitype)) {
        SDL_SetError("Could not bind EGL API");
        প্রত্যাগম রিক্ত;
    }

    egl_context = _this->egl_data->eglCreateContext(_this->egl_data->egl_display,
                                                    _this->egl_data->egl_config,
                                                    share_context, attribs);

    যদি (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_SetError("Could not create EGL context", "eglCreateContext");
        প্রত্যাগম রিক্ত;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_data->egl_swapinterval = 0;

    যদি (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        প্রত্যাগম রিক্ত;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    যদি ((_this->egl_data->egl_version_major > 1) ||
        ((_this->egl_data->egl_version_major == 1) && (_this->egl_data->egl_version_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        যদি (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            যদি (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#যদি defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } অন্যথা {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
            যদি (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_VERSION, &v);
                যদি (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#endif
        }
    }

    SDL_EGL_SetSwapInterval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    প্রত্যাগম (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    যদি (!_this->egl_data) {
        প্রত্যাগম SDL_SetError("EGL not initialized");
    }

    যদি (!_this->egl_data->eglMakeCurrent) {
        যদি (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            প্রত্যাগম true;
        } অন্যথা {
            প্রত্যাগম SDL_SetError("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    যদি (_this->egl_data->eglBindAPI) {
        _this->egl_data->eglBindAPI(_this->egl_data->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    যদি (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_data->eglMakeCurrent(_this->egl_data->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } অন্যথা {
        যদি (!_this->egl_data->eglMakeCurrent(_this->egl_data->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            প্রত্যাগম SDL_EGL_SetError("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    প্রত্যাগম true;
}

bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval)
{
    EGLBoolean status;

    যদি (!_this->egl_data) {
        প্রত্যাগম SDL_SetError("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    যদি (interval < 0) {
        প্রত্যাগম SDL_SetError("Late swap tearing currently unsupported");
    }

    status = _this->egl_data->eglSwapInterval(_this->egl_data->egl_display, interval);
    যদি (status == EGL_TRUE) {
        _this->egl_data->egl_swapinterval = interval;
        প্রত্যাগম true;
    }

    প্রত্যাগম SDL_EGL_SetError("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval)
{
    যদি (!_this->egl_data) {
        প্রত্যাগম SDL_SetError("EGL not initialized");
    }

    *interval = _this->egl_data->egl_swapinterval;
    প্রত্যাগম true;
}

bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    যদি (!_this->egl_data->eglSwapBuffers(_this->egl_data->egl_display, egl_surface)) {
        প্রত্যাগম SDL_EGL_SetError("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    প্রত্যাগম true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    যদি (!_this->egl_data) {
        প্রত্যাগম true;
    }

    যদি (egl_context != রিক্ত && egl_context != EGL_NO_CONTEXT) {
        _this->egl_data->eglDestroyContext(_this->egl_data->egl_display, egl_context);
    }
    প্রত্যাগম true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw)
{
#ifdef SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#endif
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    পূর্ণাঙ্ক attr = 0;

    EGLSurface surface;

    যদি (!SDL_EGL_ChooseConfig(_this)) {
        প্রত্যাগম EGL_NO_SURFACE;
    }

#ifdef SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_data->eglGetConfigAttrib(_this->egl_data->egl_display,
                                        _this->egl_data->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANativeWindow_setBuffersGeometry(nw, 0, 0, format_wanted);
#endif

#ifdef SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    যদি (SDL_strcmp(_this->name, "qnx") == 0) {
        পূর্ণাঙ্ক format = QNX_ChooseFormat(_this, _this->egl_data->egl_config);

        যদি (screen_set_window_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            প্রত্যাগম EGL_NO_SURFACE;
        }
    }
#endif

#ifdef EGL_KHR_gl_colorspace
    যদি (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ধ্রুব বর্ণ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        যদি (srgbhint && *srgbhint) {
            যদি (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } অন্যথা {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_LINEAR_KHR;
            }
        } অন্যথা যদি (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_LINEAR_KHR;
        }
    }
#endif

    পূর্ণাঙ্ক opaque_ext_idx = -1;

#ifdef EGL_EXT_present_opaque
    যদি (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        যদি (window && (window->flags & SDL_WINDOW_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#endif

    যদি (_this->egl_surfaceattrib_callback) {
        ধ্রুব পূর্ণাঙ্ক maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_data->egl_display, _this->egl_data->egl_config);
        যদি (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_path = '\0';
            SDL_SetError("EGL surface attribute callback returned NULL pointer");
            প্রত্যাগম EGL_NO_SURFACE;
        }

        প্রতি (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            যদি (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_path = '\0';
                SDL_SetError("EGL surface attribute callback returned too many attributes");
                প্রত্যাগম EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_data->eglCreateWindowSurface(_this->egl_data->egl_display, _this->egl_data->egl_config, nw, &attribs[0]);
    যদি (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        যদি ((_this->egl_data->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], পরিমাণ (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_data->eglCreateWindowSurface(_this->egl_data->egl_display, _this->egl_data->egl_config, nw, &attribs[0]);
        }
    }

    যদি (surface == EGL_NO_SURFACE) {
        SDL_EGL_SetError("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#ifdef SDL_VIDEO_DRIVER_ANDROID
    format_got = ANativeWindow_getFormat(nw);
    Android_SetFormat(format_wanted, format_got);
#endif

    প্রত্যাগম surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{
    EGLint attributes[] = {
        EGL_WIDTH, 0,
        EGL_HEIGHT, 0,
        EGL_NONE
    };
    attributes[1] = width;
    attributes[3] = height;

    যদি (!SDL_EGL_ChooseConfig(_this)) {
        প্রত্যাগম EGL_NO_SURFACE;
    }

    প্রত্যাগম _this->egl_data->eglCreatePbufferSurface(
        _this->egl_data->egl_display,
        _this->egl_data->egl_config,
        attributes);
}

শূন্য SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    যদি (!_this->egl_data) {
        প্রত্যাগম;
    }

    যদি (egl_surface != EGL_NO_SURFACE) {
        _this->egl_data->eglDestroySurface(_this->egl_data->egl_display, egl_surface);
    }
}

#endif // SDL_VIDEO_OPENGL_EGL
