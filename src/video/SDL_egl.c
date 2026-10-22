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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS)
#అన్తర్భావ "../core/windows/SDL_windows.h"
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
#అన్తర్భావ <android/native_window.h>
#అన్తర్భావ "../video/android/SDL_androidvideo.h"
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_QNX
#అన్తర్భావ <screen/screen.h>
#అన్తర్భావ "../video/qnx/SDL_qnx.h"
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_VITA_PVR_OGL
#అన్తర్భావ <GLES2/gl2.h>
#అయితే_ముగింపు

#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "SDL_egl_c.h"
#అన్తర్భావ "../SDL_hints_c.h"

#నిర్వచితమైతే EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#నిర్వచితం_కాకపోతే EGL_OPENGL_ES3_బిట్టు_KHR
#నిర్వచించు EGL_OPENGL_ES3_బిట్టు_KHR 0x00000040
#అయితే_ముగింపు
#అయితే_ముగింపు // EGL_KHR_create_context

#నిర్వచితం_కాకపోతే EGL_EXT_pixel_format_float
#నిర్వచించు EGL_EXT_pixel_format_float
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#అయితే_ముగింపు // EGL_EXT_pixel_format_float

#నిర్వచితం_కాకపోతే EGL_EXT_platform_device
#నిర్వచించు EGL_EXT_platform_device 1
#నిర్వచించు EGL_PLATFORM_DEVICE_EXT 0x313F
#అయితే_ముగింపు // EGL_EXT_platform_device

#నిర్వచితం_కాకపోతే EGL_EXT_present_opaque
#నిర్వచించు EGL_EXT_present_opaque 1
#నిర్వచించు EGL_PRESENT_OPAQUE_EXT 0x31DF
#అయితే_ముగింపు // EGL_EXT_present_opaque

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#నిర్వచించు DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#నిర్వచించు ALT_EGL            "libEGL.so"
#నిర్వచించు DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#నిర్వచించు ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#నిర్వచించు DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#నిర్వచించు DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#నిర్వచించు ALT_OGL_ES         "libGLESv2.so"

#లేదావేళ defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#నిర్వచించు DEFAULT_EGL        "libEGL.so"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.so"
#నిర్వచించు DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#నిర్వచించు DEFAULT_OGL_ES     "libGLESv1_CM.so"

#లేదావేళ defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#నిర్వచించు DEFAULT_EGL        "libEGL.so"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv3.so"

#లేదావేళ defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#నిర్వచించు DEFAULT_EGL        "libEGL.dll"
#నిర్వచించు DEFAULT_OGL        "opengl32.dll"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.dll"
#నిర్వచించు DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#నిర్వచించు DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#లేదావేళ defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#నిర్వచించు DEFAULT_EGL        "libEGL.dylib"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.dylib"
#నిర్వచించు DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#నిర్వచించు DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#లేదావేళ defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#నిర్వచించు DEFAULT_OGL        "libGL.so"
#నిర్వచించు DEFAULT_EGL        "libEGL.so"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.so"
#నిర్వచించు DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#నిర్వచించు DEFAULT_OGL_ES     "libGLESv1_CM.so"

#లేదావేళ defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#నిర్వచించు DEFAULT_EGL        "libEGL.so.1"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.so.1"

#లేకపోతే
// Desktop Linux/Unix-like
#నిర్వచించు DEFAULT_OGL        "libGL.so.1"
#నిర్వచించు DEFAULT_EGL        "libEGL.so.1"
#నిర్వచించు ALT_OGL            "libOpenGL.so.0"
#నిర్వచించు DEFAULT_OGL_ES2    "libGLESv2.so.2"
#నిర్వచించు DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#నిర్వచించు DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    DEFAULT_OGL_ES
)
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RPI

#ఒకవేళ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#అన్తర్భావ <SDL3/SDL_opengl.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_OPENGL
రకనిర్వచనం శూన్య (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#నిర్వచించు ఎక్కించు_FUNC(TYPE, NAME) \
    _this->egl_దత్తాంశం->NAME = NAME;
#లేకపోతే
#నిర్వచించు ఎక్కించు_FUNC(TYPE, NAME)                                                               \
    _this->egl_దత్తాంశం->NAME = (TYPE)SDL_ఎక్కించు_Function(_this->egl_దత్తాంశం->egl_dll_handle, #NAME); \
    ఒకవేళ (!_this->egl_దత్తాంశం->NAME) {                                                     \
        తిరిగి SDL_సమితి_Error("Could not retrieve EGL function " #NAME);                \
    }
#అయితే_ముగింపు

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#నిర్వచించు ఎక్కించు_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_దత్తాంశం->NAME = (TYPE)_this->egl_దత్తాంశం->egl_Get_Proc_చిరునామా(#NAME);

స్థిర స్థిరరాశి అక్షరం *SDL_EGL_GetErrorName(EGLint egl_Error_సంకేతం)
{
#నిర్వచించు SDL_EGL_ERROR_TRANSLATE(e) \
    స్థితి e:                        \
        తిరిగి #e
    ఎంపిక (egl_Error_సంకేతం) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_సరిపోలిక);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_కిటికీ);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_కోల్పోయిన);
    }
    తిరిగి "";
}

bool SDL_EGL_సమితి_Error_Ex(స్థిరరాశి అక్షరం *సందేశం, స్థిరరాశి అక్షరం *eglFunctionName, EGLint egl_Error_సంకేతం)
{
    స్థిరరాశి అక్షరం *error_పాఠ్యం = SDL_EGL_GetErrorName(egl_Error_సంకేతం);
    అక్షరం alt_Error_పాఠ్యం[32];
    ఒకవేళ (error_పాఠ్యం[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (శూన్య)SDL_snprintf(alt_Error_పాఠ్యం, SDL_arraysize(alt_Error_పాఠ్యం), "0x%x", (గుర్తులేని పూర్ణాంకం)egl_Error_సంకేతం);
        error_పాఠ్యం = alt_Error_పాఠ్యం;
    }
    తిరిగి SDL_సమితి_Error("%s (call to %s failed, reporting an error of %s)", సందేశం, eglFunctionName, error_పాఠ్యం);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, స్థిరరాశి అక్షరం *ext)
{
    size_t ext_len;
    స్థిరరాశి అక్షరం *ext_override;
    స్థిరరాశి అక్షరం *egl_extstr;
    స్థిరరాశి అక్షరం *ext_ప్రారంభం;

    // Invalid extensions can be rejected early
    ఒకవేళ (!ext || *ext == 0 || SDL_strchr(ext, ' ') != ఖాళీ) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        తిరిగి false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    ఒకవేళ (ext_override) {
        పూర్ణాంకం disable_ext = SDL_atoi(ext_override);
        ఒకవేళ (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            తిరిగి false;
        } లేకపోతే ఒకవేళ (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            తిరిగి false;
        }
    }

    ext_len = SDL_strlen(ext);
    ఎంపిక (type) {
    స్థితి SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_దత్తాంశం->eglQueryString(_this->egl_దత్తాంశం->egl_display, EGL_EXTENSIONS);
        ఆపు;
    స్థితి SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_దత్తాంశం->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        ఆపు;
    అప్రమేయ:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        తిరిగి false;
    }

    ఒకవేళ (egl_extstr) {
        ext_ప్రారంభం = egl_extstr;

        అయితే (*ext_ప్రారంభం) {
            ext_ప్రారంభం = SDL_strstr(ext_ప్రారంభం, ext);
            ఒకవేళ (!ext_ప్రారంభం) {
                తిరిగి false;
            }
            // Check if the match is not just a substring of one of the extensions
            ఒకవేళ (ext_ప్రారంభం == egl_extstr || *(ext_ప్రారంభం - 1) == ' ') {
                ఒకవేళ (ext_ప్రారంభం[ext_len] == ' ' || ext_ప్రారంభం[ext_len] == 0) {
                    తిరిగి true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_ప్రారంభం += ext_len;
            అయితే (*ext_ప్రారంభం != ' ' && *ext_ప్రారంభం != 0) {
                ext_ప్రారంభం++;
            }
        }
    }

    తిరిగి false;
}

SDL_Function_సూచిక SDL_EGL_Get_Proc_చిరునామా_అంతర్గత(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    SDL_Function_సూచిక ఫలితం = ఖాళీ;
    ఒకవేళ (_this->egl_దత్తాంశం) {
        స్థిరరాశి Uint32 eglver = (((Uint32)_this->egl_దత్తాంశం->egl_సంస్కరణ_major) << 16) | ((Uint32)_this->egl_దత్తాంశం->egl_సంస్కరణ_minor);
        స్థిరరాశి bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        ఒకవేళ (!ఫలితం && is_egl_15_or_later && _this->egl_దత్తాంశం->egl_Get_Proc_చిరునామా) {
            ఫలితం = _this->egl_దత్తాంశం->egl_Get_Proc_చిరునామా(proc);
        }

#ఒకవేళ !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        ఒకవేళ (!ఫలితం) {
            ఫలితం = SDL_ఎక్కించు_Function(_this->egl_దత్తాంశం->opengl_dll_handle, proc);
        }
#అయితే_ముగింపు

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        ఒకవేళ (!ఫలితం && !is_egl_15_or_later && _this->egl_దత్తాంశం->egl_Get_Proc_చిరునామా) {
            ఫలితం = _this->egl_దత్తాంశం->egl_Get_Proc_చిరునామా(proc);
        }
    }
    తిరిగి ఫలితం;
}

శూన్య SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->egl_దత్తాంశం) {
        ఒకవేళ (_this->egl_దత్తాంశం->egl_display) {
            _this->egl_దత్తాంశం->eglTerminate(_this->egl_దత్తాంశం->egl_display);
            _this->egl_దత్తాంశం->egl_display = ఖాళీ;
        }

        ఒకవేళ (_this->egl_దత్తాంశం->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_దత్తాంశం->egl_dll_handle);
            _this->egl_దత్తాంశం->egl_dll_handle = ఖాళీ;
        }
        ఒకవేళ (_this->egl_దత్తాంశం->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_దత్తాంశం->opengl_dll_handle);
            _this->egl_దత్తాంశం->opengl_dll_handle = ఖాళీ;
        }

        SDL_free(_this->egl_దత్తాంశం);
        _this->egl_దత్తాంశం = ఖాళీ;
    }
}

స్థిర bool SDL_EGL_ఎక్కించు_Library_అంతర్గత(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *egl_మార్గం)
{
    SDL_SharedObject *egl_dll_handle = ఖాళీ;
#ఒకవేళ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = ఖాళీ;
#అయితే_ముగింపు
    స్థిరరాశి అక్షరం *మార్గం = ఖాళీ;
#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS)
    స్థిరరాశి అక్షరం *d3dcompiler;
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    ఒకవేళ (d3dcompiler) {
        ఒకవేళ (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            ఒకవేళ (SDL_ఎక్కించు_Object(d3dcompiler) == ఖాళీ) {
                SDL_ClearError();
            }
        }
    } లేకపోతే {
        ఒకవేళ (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            స్థిరరాశి అక్షరం *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            పూర్ణాంకం i;

            కొరకు (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                ఒకవేళ (SDL_ఎక్కించు_Object(d3dcompiler_list[i]) != ఖాళీ) {
                    ఆపు;
                }
                SDL_ClearError();
            }
        } లేకపోతే {
            ఒకవేళ (SDL_ఎక్కించు_Object("d3dcompiler_43.dll") == ఖాళీ) {
                SDL_ClearError();
            }
        }
    }
#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    మార్గం = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    ఒకవేళ (మార్గం) {
        opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
    }

    ఒకవేళ (!opengl_dll_handle) {
        ఒకవేళ (_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) {
            ఒకవేళ (_this->gl_config.major_సంస్కరణ > 1) {
#నిర్వచితమైతే DEFAULT_OGL_ES2
                ఒకవేళ (!opengl_dll_handle) {
                    మార్గం = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
                }
#అయితే_ముగింపు
#నిర్వచితమైతే ALT_OGL_ES2
                ఒకవేళ (!opengl_dll_handle && !vc4) {
                    మార్గం = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
                }
#అయితే_ముగింపు
            } లేకపోతే {
#నిర్వచితమైతే DEFAULT_OGL_ES
                ఒకవేళ (!opengl_dll_handle) {
                    మార్గం = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
                }
#అయితే_ముగింపు
#నిర్వచితమైతే DEFAULT_OGL_ES_PVR
                ఒకవేళ (!opengl_dll_handle) {
                    మార్గం = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
                }
#అయితే_ముగింపు
#నిర్వచితమైతే ALT_OGL_ES
                ఒకవేళ (!opengl_dll_handle && !vc4) {
                    మార్గం = ALT_OGL_ES;
                    opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
                }
#అయితే_ముగింపు
            }
        } లేకపోతే {
#నిర్వచితమైతే DEFAULT_OGL
            ఒకవేళ (!opengl_dll_handle) {
                మార్గం = DEFAULT_OGL;
                opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
            }
#అయితే_ముగింపు
#నిర్వచితమైతే ALT_OGL
            ఒకవేళ (!opengl_dll_handle) {
                మార్గం = ALT_OGL;
                opengl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
            }
#అయితే_ముగింపు
        }
    }
    _this->egl_దత్తాంశం->opengl_dll_handle = opengl_dll_handle;

    ఒకవేళ (!opengl_dll_handle) {
        తిరిగి SDL_సమితి_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    ఒకవేళ (egl_మార్గం) {
        egl_dll_handle = SDL_ఎక్కించు_Object(egl_మార్గం);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    ఒకవేళ (!egl_dll_handle || SDL_ఎక్కించు_Function(egl_dll_handle, "eglChooseConfig") == ఖాళీ) {
        ఒకవేళ (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        మార్గం = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        ఒకవేళ (!మార్గం) {
            మార్గం = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);

#నిర్వచితమైతే ALT_EGL
        ఒకవేళ (!egl_dll_handle && !vc4) {
            మార్గం = ALT_EGL;
            egl_dll_handle = SDL_ఎక్కించు_Object(మార్గం);
        }
#అయితే_ముగింపు

        ఒకవేళ (!egl_dll_handle || SDL_ఎక్కించు_Function(egl_dll_handle, "eglChooseConfig") == ఖాళీ) {
            ఒకవేళ (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            తిరిగి SDL_సమితి_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#అయితే_ముగింపు

    _this->egl_దత్తాంశం->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    ఎక్కించు_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    ఎక్కించు_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    ఎక్కించు_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    ఎక్కించు_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_చిరునామా);
    ఎక్కించు_FUNC(PFNEGLCHOOSECONFIGPROC, egl_ఎంచుకో_Config);
    ఎక్కించు_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    ఎక్కించు_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    ఎక్కించు_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    ఎక్కించు_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_కిటికీ_Surface);
    ఎక్కించు_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    ఎక్కించు_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    ఎక్కించు_FUNC(PFNEGLSWAPBUFFERSPROC, egl_మార్పిడి_Buffers);
    ఎక్కించు_FUNC(PFNEGLSWAPINTERVALPROC, egl_మార్పిడి_Interval);
    ఎక్కించు_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    ఎక్కించు_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    ఎక్కించు_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    ఎక్కించు_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    ఎక్కించు_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    ఎక్కించు_FUNC(PFNEGLGETERRORPROC, eglGetError);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    ఎక్కించు_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    ఎక్కించు_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    ఒకవేళ (మార్గం) {
        SDL_strlcpy(_this->gl_config.driver_మార్గం, మార్గం, పరిమాణం(_this->gl_config.driver_మార్గం) - 1);
    } లేకపోతే {
        *_this->gl_config.driver_మార్గం = '\0';
    }

    తిరిగి true;
}

bool SDL_EGL_ఎక్కించు_Library_Only(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *egl_మార్గం)
{
    ఒకవేళ (_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL context already created");
    }

    _this->egl_దత్తాంశం = (నిర్మాణం SDL_EGL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_EGL_Video_దత్తాంశం));
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి false;
    }

    ఒకవేళ (!SDL_EGL_ఎక్కించు_Library_అంతర్గత(_this, egl_మార్గం)) {
        SDL_free(_this->egl_దత్తాంశం);
        _this->egl_దత్తాంశం = ఖాళీ;
        తిరిగి false;
    }
    తిరిగి true;
}

స్థిర శూన్య SDL_EGL_Get_సంస్కరణ(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->egl_దత్తాంశం->eglQueryString) {
        స్థిరరాశి అక్షరం *egl_సంస్కరణ = _this->egl_దత్తాంశం->eglQueryString(_this->egl_దత్తాంశం->egl_display, EGL_సంస్కరణ);
        ఒకవేళ (egl_సంస్కరణ) {
            పూర్ణాంకం major = 0, minor = 0;
            ఒకవేళ (SDL_sscanf(egl_సంస్కరణ, "%d.%d", &major, &minor) == 2) {
                _this->egl_దత్తాంశం->egl_సంస్కరణ_major = major;
                _this->egl_దత్తాంశం->egl_సంస్కరణ_minor = minor;
            } లేకపోతే {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_సంస్కరణ);
            }
        }
    }
}

bool SDL_EGL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *egl_మార్గం, NativeDisplayType native_display)
{
    ఒకవేళ (!SDL_EGL_ఎక్కించు_Library_Only(_this, egl_మార్గం)) {
        తిరిగి false;
    }

    _this->egl_దత్తాంశం->egl_display = EGL_NO_DISPLAY;

#నిర్వచితం_కాకపోతే SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    ఒకవేళ (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_సంస్కరణ(_this);

        ఒకవేళ (_this->egl_దత్తాంశం->egl_సంస్కరణ_major == 1 && _this->egl_దత్తాంశం->egl_సంస్కరణ_minor == 5) {
            ఎక్కించు_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        ఒకవేళ (_this->egl_దత్తాంశం->eglGetPlatformDisplay) {
            EGLAttrib *attribs = ఖాళీ;
            ఒకవేళ (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                ఒకవేళ (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_మార్గం = '\0';
                    తిరిగి SDL_సమితి_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_దత్తాంశం->egl_display = _this->egl_దత్తాంశం->eglGetPlatformDisplay(platform, (శూన్య *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } లేకపోతే {
            ఒకవేళ (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_దత్తాంశం->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_చిరునామా_అంతర్గత(_this, "eglGetPlatformDisplayEXT");
                ఒకవేళ (_this->egl_దత్తాంశం->eglGetPlatformDisplayEXT) {
                    _this->egl_దత్తాంశం->egl_display = _this->egl_దత్తాంశం->eglGetPlatformDisplayEXT(platform, (శూన్య *)(uintptr_t)native_display, ఖాళీ);
                }
            }
        }
    }
#అయితే_ముగింపు
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    ఒకవేళ ((_this->egl_దత్తాంశం->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_దత్తాంశం->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_దత్తాంశం->egl_display = _this->egl_దత్తాంశం->eglGetDisplay(native_display);
    }
    ఒకవేళ (_this->egl_దత్తాంశం->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_మార్గం = '\0';
        తిరిగి SDL_సమితి_Error("Could not get EGL display");
    }

    ఒకవేళ (_this->egl_దత్తాంశం->eglInitialize(_this->egl_దత్తాంశం->egl_display, ఖాళీ, ఖాళీ) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_మార్గం = '\0';
        తిరిగి SDL_సమితి_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_సంస్కరణ(_this);

    _this->egl_దత్తాంశం->is_offscreen = false;

    తిరిగి true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, పూర్ణాంకం device)
{
    శూన్య *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint అంకె_egl_devices = 0;
    స్థిరరాశి అక్షరం *egl_device_hint;

    ఒకవేళ (_this->gl_config.driver_loaded <= 0) {
        తిరిగి SDL_సమితి_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    ఒకవేళ (!_this->egl_దత్తాంశం->eglQueryDevicesEXT) {
        తిరిగి SDL_సమితి_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    ఒకవేళ (!_this->egl_దత్తాంశం->eglGetPlatformDisplayEXT) {
        తిరిగి SDL_సమితి_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    ఒకవేళ (_this->egl_దత్తాంశం->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &అంకె_egl_devices) != EGL_TRUE) {
        తిరిగి SDL_సమితి_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    ఒకవేళ (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        ఒకవేళ (device >= అంకె_egl_devices) {
            తిరిగి SDL_సమితి_Error("Invalid EGL device is requested.");
        }

        _this->egl_దత్తాంశం->egl_display = _this->egl_దత్తాంశం->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], ఖాళీ);

        ఒకవేళ (_this->egl_దత్తాంశం->egl_display == EGL_NO_DISPLAY) {
            తిరిగి SDL_సమితి_Error("eglGetPlatformDisplayEXT() failed.");
        }

        ఒకవేళ (_this->egl_దత్తాంశం->eglInitialize(_this->egl_దత్తాంశం->egl_display, ఖాళీ, ఖాళీ) != EGL_TRUE) {
            తిరిగి SDL_సమితి_Error("Could not initialize EGL");
        }
    } లేకపోతే {
        పూర్ణాంకం i;
        bool దొరికింది = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        కొరకు (i = 0; i < అంకె_egl_devices; i++) {
            attempted_egl_display = _this->egl_దత్తాంశం->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], ఖాళీ);

            ఒకవేళ (attempted_egl_display == EGL_NO_DISPLAY) {
                కొనసాగు;
            }

            ఒకవేళ (_this->egl_దత్తాంశం->eglInitialize(attempted_egl_display, ఖాళీ, ఖాళీ) != EGL_TRUE) {
                _this->egl_దత్తాంశం->eglTerminate(attempted_egl_display);
                కొనసాగు;
            }

            // We did not fail, we'll pick this one!
            _this->egl_దత్తాంశం->egl_display = attempted_egl_display;
            దొరికింది = true;

            ఆపు;
        }

        ఒకవేళ (!దొరికింది) {
            తిరిగి SDL_సమితి_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_సంస్కరణ(_this);

    _this->egl_దత్తాంశం->is_offscreen = true;

    తిరిగి true;
}

శూన్య SDL_EGL_సమితి_Required_Visual_Id(SDL_VideoDevice *_this, పూర్ణాంకం visual_id)
{
    _this->egl_దత్తాంశం->egl_required_visual_id = visual_id;
}

#నిర్వచితమైతే DUMP_EGL_CONFIG

#నిర్వచించు ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

రకనిర్వచనం నిర్మాణం
{
    EGLint attribute;
    అక్షరం స్థిరరాశి *name;
} Attribute;

స్థిర Attribute all_లక్షణాలు[] = {
    ATTRIBUTE(EGL_బఫరు_కొలత),
    ATTRIBUTE(EGL_ALPHA_కొలత),
    ATTRIBUTE(EGL_BLUE_కొలత),
    ATTRIBUTE(EGL_GREEN_కొలత),
    ATTRIBUTE(EGL_RED_కొలత),
    ATTRIBUTE(EGL_లోతు_కొలత),
    ATTRIBUTE(EGL_STENCIL_కొలత),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_ఎత్తు),
    ATTRIBUTE(EGL_MAX_PBUFFER_వెడల్పు),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_విలువ),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_విలువ),
    ATTRIBUTE(EGL_TRANSPARENT_RED_విలువ),
    ATTRIBUTE(EGL_BIND_గమ్యం_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_గమ్యం_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_మార్పిడి_INTERVAL),
    ATTRIBUTE(EGL_MAX_మార్పిడి_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_కొలత),
    ATTRIBUTE(EGL_ALPHA_ముసుగు_కొలత),
    ATTRIBUTE(EGL_COLOR_బఫరు_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_సరిపోలిక_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

స్థిర శూన్య dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    పూర్ణాంకం attr;
    కొరకు (attr = 0; attr < SDL_arraysize(all_లక్షణాలు); attr++) {
        EGLint విలువ;
        _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, config, all_లక్షణాలు[attr].attribute, &విలువ);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_లక్షణాలు[attr].name, విలువ, విలువ);
    }
}

#అయితే_ముగింపు // DUMP_EGL_CONFIG

స్థిర bool SDL_EGL_వ్యక్తిగత_ఎంచుకో_Config(SDL_VideoDevice *_this, bool సమితి_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint దొరికింది_configs = 0, విలువ;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    పూర్ణాంకం i, j, ఉత్తమ_bitdiff = -1, ఉత్తమ_truecolor_bitdiff = -1;
    పూర్ణాంకం truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_కొలత;
    attribs[i++] = _this->gl_config.red_కొలత;
    attribs[i++] = EGL_GREEN_కొలత;
    attribs[i++] = _this->gl_config.green_కొలత;
    attribs[i++] = EGL_BLUE_కొలత;
    attribs[i++] = _this->gl_config.blue_కొలత;

    ఒకవేళ (సమితి_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    ఒకవేళ (_this->gl_config.alpha_కొలత) {
        attribs[i++] = EGL_ALPHA_కొలత;
        attribs[i++] = _this->gl_config.alpha_కొలత;
    }

    ఒకవేళ (_this->gl_config.బఫరు_కొలత) {
        attribs[i++] = EGL_బఫరు_కొలత;
        attribs[i++] = _this->gl_config.బఫరు_కొలత;
    }

    ఒకవేళ (_this->gl_config.లోతు_కొలత) {
        attribs[i++] = EGL_లోతు_కొలత;
        attribs[i++] = _this->gl_config.లోతు_కొలత;
    }

    ఒకవేళ (_this->gl_config.stencil_కొలత) {
        attribs[i++] = EGL_STENCIL_కొలత;
        attribs[i++] = _this->gl_config.stencil_కొలత;
    }

    ఒకవేళ (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    ఒకవేళ (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    ఒకవేళ (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    ఒకవేళ (_this->egl_దత్తాంశం->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_బిట్టు;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    ఒకవేళ (_this->gl_config.profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES) {
#నిర్వచితమైతే EGL_KHR_create_context
        ఒకవేళ (_this->gl_config.major_సంస్కరణ >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_బిట్టు_KHR;
        } లేకపోతే
#అయితే_ముగింపు
            ఒకవేళ (_this->gl_config.major_సంస్కరణ >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_బిట్టు;
        } లేకపోతే {
            attribs[i++] = EGL_OPENGL_ES_బిట్టు;
        }
        _this->egl_దత్తాంశం->eglBindAPI(EGL_OPENGL_ES_API);
    } లేకపోతే {
        attribs[i++] = EGL_OPENGL_బిట్టు;
        _this->egl_దత్తాంశం->eglBindAPI(EGL_OPENGL_API);
    }

    ఒకవేళ (_this->egl_దత్తాంశం->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_దత్తాంశం->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    ఒకవేళ (_this->egl_దత్తాంశం->egl_ఎంచుకో_Config(_this->egl_దత్తాంశం->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &దొరికింది_configs) == EGL_FALSE ||
        దొరికింది_configs == 0) {
        తిరిగి false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    ఒకవేళ (_this->egl_దత్తాంశం->egl_required_visual_id) {
        కొరకు (i = 0; i < దొరికింది_configs; i++) {
            EGLint format;
            _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ఒకవేళ (_this->egl_దత్తాంశం->egl_required_visual_id == format) {
                has_matching_format = true;
                ఆపు;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    కొరకు (i = 0; i < దొరికింది_configs; i++) {
        bool is_truecolor = false;
        పూర్ణాంకం bitdiff = 0;

        ఒకవేళ (has_matching_format && _this->egl_దత్తాంశం->egl_required_visual_id) {
            EGLint format;
            _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            ఒకవేళ (_this->egl_దత్తాంశం->egl_required_visual_id != format) {
                కొనసాగు;
            }
        }

        _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, configs[i], EGL_RED_కొలత, &విలువ);
        ఒకవేళ (విలువ == 8) {
            _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, configs[i], EGL_GREEN_కొలత, &విలువ);
            ఒకవేళ (విలువ == 8) {
                _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, configs[i], EGL_BLUE_కొలత, &విలువ);
                ఒకవేళ (విలువ == 8) {
                    is_truecolor = true;
                }
            }
        }

        కొరకు (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            ఒకవేళ (attribs[j] == EGL_NONE) {
                ఆపు;
            }

            ఒకవేళ (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_కొలత ||
                                                    attribs[j] == EGL_GREEN_కొలత ||
                                                    attribs[j] == EGL_BLUE_కొలత ||
                                                    attribs[j] == EGL_ALPHA_కొలత ||
                                                    attribs[j] == EGL_లోతు_కొలత ||
                                                    attribs[j] == EGL_STENCIL_కొలత)) {
                _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display, configs[i], attribs[j], &విలువ);
                bitdiff += విలువ - attribs[j + 1]; // value is always >= attrib
            }
        }

        ఒకవేళ ((bitdiff < ఉత్తమ_bitdiff) || (ఉత్తమ_bitdiff == -1)) {
            _this->egl_దత్తాంశం->egl_config = configs[i];
            ఉత్తమ_bitdiff = bitdiff;
        }

        ఒకవేళ (is_truecolor && ((bitdiff < ఉత్తమ_truecolor_bitdiff) || (ఉత్తమ_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            ఉత్తమ_truecolor_bitdiff = bitdiff;
        }
    }

#నిర్వచించు FAVOR_TRUECOLOR 1
#ఒకవేళ FAVOR_TRUECOLOR
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
    ఒకవేళ (((_this->gl_config.red_కొలత + _this->gl_config.blue_కొలత + _this->gl_config.green_కొలత) <= 16)) {
        ఒకవేళ (truecolor_config_idx != -1) {
            _this->egl_దత్తాంశం->egl_config = configs[truecolor_config_idx];
        }
    }
#అయితే_ముగింపు

#నిర్వచితమైతే DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_దత్తాంశం->egl_config);
#అయితే_ముగింపు

    తిరిగి true;
}

bool SDL_EGL_ఎంచుకో_Config(SDL_VideoDevice *_this)
{
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    ఒకవేళ (SDL_EGL_వ్యక్తిగత_ఎంచుకో_Config(_this, true)) {
        తిరిగి true;
    }

    // Fallback with all configs
    ఒకవేళ (SDL_EGL_వ్యక్తిగత_ఎంచుకో_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        తిరిగి true;
    }

    తిరిగి SDL_EGL_సమితి_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    పూర్ణాంకం attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_ముసుగు = _this->gl_config.profile_ముసుగు;
    EGLint major_సంస్కరణ = _this->gl_config.major_సంస్కరణ;
    EGLint minor_సంస్కరణ = _this->gl_config.minor_సంస్కరణ;
    bool profile_es = (profile_ముసుగు == SDL_GL_CONTEXT_PROFILE_ES);

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        SDL_సమితి_Error("EGL not initialized");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
    ఒకవేళ (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        పూర్ణాంకం egl_సంస్కరణ_major = _this->egl_దత్తాంశం->egl_సంస్కరణ_major;
        పూర్ణాంకం egl_సంస్కరణ_minor = _this->egl_దత్తాంశం->egl_సంస్కరణ_minor;
        ఒకవేళ (((egl_సంస్కరణ_major < 1) || (egl_సంస్కరణ_major == 1 && egl_సంస్కరణ_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#అయితే_ముగింపు

    // Set the context version and other attributes.
    ఒకవేళ ((major_సంస్కరణ < 3 || (minor_సంస్కరణ == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_ముసుగు == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        ఒకవేళ (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_సంస్కరణ;
            attribs[attr++] = SDL_max(major_సంస్కరణ, 1);
        }
    } లేకపోతే {
#నిర్వచితమైతే EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        ఒకవేళ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_సంస్కరణ_KHR;
            attribs[attr++] = major_సంస్కరణ;
            attribs[attr++] = EGL_CONTEXT_MINOR_సంస్కరణ_KHR;
            attribs[attr++] = minor_సంస్కరణ;

            // SDL profile bits match EGL profile bits.
            ఒకవేళ (profile_ముసుగు != 0 && profile_ముసుగు != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_ముసుగు_KHR;
                attribs[attr++] = profile_ముసుగు;
            }

            // SDL flags match EGL flags.
            ఒకవేళ (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } లేకపోతే
#అయితే_ముగింపు // EGL_KHR_create_context
        {
            SDL_సమితి_Error("Could not create EGL context (context attributes are not supported)");
            తిరిగి ఖాళీ;
        }
    }

#నిర్వచితమైతే EGL_KHR_create_context_no_error
    ఒకవేళ (_this->gl_config.no_error) {
        ఒకవేళ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (_this->egl_contextattrib_callback) {
        స్థిరరాశి పూర్ణాంకం maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_దత్తాంశం->egl_display, _this->egl_దత్తాంశం->egl_config);
        ఒకవేళ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_మార్గం = '\0';
            SDL_సమితి_Error("EGL context attribute callback returned NULL pointer");
            తిరిగి ఖాళీ;
        }

        కొరకు (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ఒకవేళ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_మార్గం = '\0';
                SDL_సమితి_Error("EGL context attribute callback returned too many attributes");
                తిరిగి ఖాళీ;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    ఒకవేళ (profile_es) {
        _this->egl_దత్తాంశం->apitype = EGL_OPENGL_ES_API;
    } లేకపోతే {
        _this->egl_దత్తాంశం->apitype = EGL_OPENGL_API;
    }
    ఒకవేళ (!_this->egl_దత్తాంశం->eglBindAPI(_this->egl_దత్తాంశం->apitype)) {
        SDL_సమితి_Error("Could not bind EGL API");
        తిరిగి ఖాళీ;
    }

    egl_context = _this->egl_దత్తాంశం->eglCreateContext(_this->egl_దత్తాంశం->egl_display,
                                                    _this->egl_దత్తాంశం->egl_config,
                                                    share_context, attribs);

    ఒకవేళ (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_సమితి_Error("Could not create EGL context", "eglCreateContext");
        తిరిగి ఖాళీ;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_దత్తాంశం->egl_swapinterval = 0;

    ఒకవేళ (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        తిరిగి ఖాళీ;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    ఒకవేళ ((_this->egl_దత్తాంశం->egl_సంస్కరణ_major > 1) ||
        ((_this->egl_దత్తాంశం->egl_సంస్కరణ_major == 1) && (_this->egl_దత్తాంశం->egl_సంస్కరణ_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        ఒకవేళ (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            ఒకవేళ (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#ఒకవేళ defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } లేకపోతే {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_చిరునామా("glGetIntegerv");
            ఒకవేళ (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_సంస్కరణ, &v);
                ఒకవేళ (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#అయితే_ముగింపు
        }
    }

    SDL_EGL_సమితి_మార్పిడి_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    తిరిగి (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    ఒకవేళ (!_this->egl_దత్తాంశం->eglMakeCurrent) {
        ఒకవేళ (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            తిరిగి true;
        } లేకపోతే {
            తిరిగి SDL_సమితి_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    ఒకవేళ (_this->egl_దత్తాంశం->eglBindAPI) {
        _this->egl_దత్తాంశం->eglBindAPI(_this->egl_దత్తాంశం->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    ఒకవేళ (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_దత్తాంశం->eglMakeCurrent(_this->egl_దత్తాంశం->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } లేకపోతే {
        ఒకవేళ (!_this->egl_దత్తాంశం->eglMakeCurrent(_this->egl_దత్తాంశం->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            తిరిగి SDL_EGL_సమితి_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    తిరిగి true;
}

bool SDL_EGL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    EGLBoolean స్థితి_2;

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    ఒకవేళ (interval < 0) {
        తిరిగి SDL_సమితి_Error("Late swap tearing currently unsupported");
    }

    స్థితి_2 = _this->egl_దత్తాంశం->egl_మార్పిడి_Interval(_this->egl_దత్తాంశం->egl_display, interval);
    ఒకవేళ (స్థితి_2 == EGL_TRUE) {
        _this->egl_దత్తాంశం->egl_swapinterval = interval;
        తిరిగి true;
    }

    తిరిగి SDL_EGL_సమితి_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval)
{
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి SDL_సమితి_Error("EGL not initialized");
    }

    *interval = _this->egl_దత్తాంశం->egl_swapinterval;
    తిరిగి true;
}

bool SDL_EGL_మార్పిడి_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ఒకవేళ (!_this->egl_దత్తాంశం->egl_మార్పిడి_Buffers(_this->egl_దత్తాంశం->egl_display, egl_surface)) {
        తిరిగి SDL_EGL_సమితి_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    తిరిగి true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి true;
    }

    ఒకవేళ (egl_context != ఖాళీ && egl_context != EGL_NO_CONTEXT) {
        _this->egl_దత్తాంశం->eglDestroyContext(_this->egl_దత్తాంశం->egl_display, egl_context);
    }
    తిరిగి true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, Native_కిటికీ_Type nw)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#అయితే_ముగింపు
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    పూర్ణాంకం attr = 0;

    EGLSurface surface;

    ఒకవేళ (!SDL_EGL_ఎంచుకో_Config(_this)) {
        తిరిగి EGL_NO_SURFACE;
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_దత్తాంశం->eglGetConfigAttrib(_this->egl_దత్తాంశం->egl_display,
                                        _this->egl_దత్తాంశం->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_కిటికీ_సమితి_Buffers_Geometry(nw, 0, 0, format_wanted);
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    ఒకవేళ (SDL_strcmp(_this->name, "qnx") == 0) {
        పూర్ణాంకం format = QNX_ఎంచుకో_Format(_this, _this->egl_దత్తాంశం->egl_config);

        ఒకవేళ (screen_సమితి_కిటికీ_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            తిరిగి EGL_NO_SURFACE;
        }
    }
#అయితే_ముగింపు

#నిర్వచితమైతే EGL_KHR_gl_colorspace
    ఒకవేళ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        స్థిరరాశి అక్షరం *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        ఒకవేళ (srgbhint && *srgbhint) {
            ఒకవేళ (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } లేకపోతే {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_రేఖీయ_KHR;
            }
        } లేకపోతే ఒకవేళ (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_రేఖీయ_KHR;
        }
    }
#అయితే_ముగింపు

    పూర్ణాంకం opaque_ext_idx = -1;

#నిర్వచితమైతే EGL_EXT_present_opaque
    ఒకవేళ (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        ఒకవేళ (కిటికీ && (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#అయితే_ముగింపు

    ఒకవేళ (_this->egl_surfaceattrib_callback) {
        స్థిరరాశి పూర్ణాంకం maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_దత్తాంశం->egl_display, _this->egl_దత్తాంశం->egl_config);
        ఒకవేళ (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_మార్గం = '\0';
            SDL_సమితి_Error("EGL surface attribute callback returned NULL pointer");
            తిరిగి EGL_NO_SURFACE;
        }

        కొరకు (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            ఒకవేళ (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_మార్గం = '\0';
                SDL_సమితి_Error("EGL surface attribute callback returned too many attributes");
                తిరిగి EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_దత్తాంశం->egl_Create_కిటికీ_Surface(_this->egl_దత్తాంశం->egl_display, _this->egl_దత్తాంశం->egl_config, nw, &attribs[0]);
    ఒకవేళ (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        ఒకవేళ ((_this->egl_దత్తాంశం->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], పరిమాణం (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_దత్తాంశం->egl_Create_కిటికీ_Surface(_this->egl_దత్తాంశం->egl_display, _this->egl_దత్తాంశం->egl_config, nw, &attribs[0]);
        }
    }

    ఒకవేళ (surface == EGL_NO_SURFACE) {
        SDL_EGL_సమితి_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_కిటికీ_get_Format(nw);
    Android_సమితి_Format(format_wanted, format_got);
#అయితే_ముగింపు

    తిరిగి surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    EGLint లక్షణాలు[] = {
        EGL_వెడల్పు, 0,
        EGL_ఎత్తు, 0,
        EGL_NONE
    };
    లక్షణాలు[1] = వెడల్పు;
    లక్షణాలు[3] = ఎత్తు;

    ఒకవేళ (!SDL_EGL_ఎంచుకో_Config(_this)) {
        తిరిగి EGL_NO_SURFACE;
    }

    తిరిగి _this->egl_దత్తాంశం->eglCreatePbufferSurface(
        _this->egl_దత్తాంశం->egl_display,
        _this->egl_దత్తాంశం->egl_config,
        లక్షణాలు);
}

శూన్య SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        తిరిగి;
    }

    ఒకవేళ (egl_surface != EGL_NO_SURFACE) {
        _this->egl_దత్తాంశం->eglDestroySurface(_this->egl_దత్తాంశం->egl_display, egl_surface);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_EGL
