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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS)
#अन्तर्भाव "../core/windows/SDL_windows.h"
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
#अन्तर्भाव <android/native_window.h>
#अन्तर्भाव "../video/android/SDL_androidvideo.h"
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_QNX
#अन्तर्भाव <screen/screen.h>
#अन्तर्भाव "../video/qnx/SDL_qnx.h"
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RPI
#अन्तर्भाव <unistd.h>
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR_OGL
#अन्तर्भाव <GLES2/gl2.h>
#यदि_अन्तः

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_egl_c.h"
#अन्तर्भाव "../SDL_hints_c.h"

#यदि_परिभाषितम् EGL_KHR_create_context
// EGL_OPENGL_ES3_BIT_KHR was added in version 13 of the extension.
#यदि_अपरिभाषितम् EGL_OPENGL_ES3_BIT_KHR
#परिभाषय EGL_OPENGL_ES3_BIT_KHR 0x00000040
#यदि_अन्तः
#यदि_अन्तः // EGL_KHR_create_context

#यदि_अपरिभाषितम् EGL_EXT_pixel_format_float
#परिभाषय EGL_EXT_pixel_format_float
#परिभाषय EGL_COLOR_COMPONENT_TYPE_EXT       0x3339
#परिभाषय EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#परिभाषय EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#यदि_अन्तः // EGL_EXT_pixel_format_float

#यदि_अपरिभाषितम् EGL_EXT_platform_device
#परिभाषय EGL_EXT_platform_device 1
#परिभाषय EGL_PLATFORM_DEVICE_EXT 0x313F
#यदि_अन्तः // EGL_EXT_platform_device

#यदि_अपरिभाषितम् EGL_EXT_present_opaque
#परिभाषय EGL_EXT_present_opaque 1
#परिभाषय EGL_PRESENT_OPAQUE_EXT 0x31DF
#यदि_अन्तः // EGL_EXT_present_opaque

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RPI
// Raspbian places the OpenGL ES/EGL binaries in a non standard path
#परिभाषय DEFAULT_EGL        (vc4 ? "libEGL.so.1" : "libbrcmEGL.so")
#परिभाषय ALT_EGL            "libEGL.so"
#परिभाषय DEFAULT_OGL_ES2    (vc4 ? "libGLESv2.so.2" : "libbrcmGLESv2.so")
#परिभाषय ALT_OGL_ES2        "libGLESv2.so"
// The GLESv2 library also contains GLESv1 exports when using the dispmanx implementation
#परिभाषय DEFAULT_OGL_ES_PVR (vc4 ? "libGLES_CM.so.1" : "libbrcmGLESv2.so")
#परिभाषय DEFAULT_OGL_ES     (vc4 ? "libGLESv1_CM.so.1" : "libbrcmGLESv2.so")
#परिभाषय ALT_OGL_ES         "libGLESv2.so"

#नोचेद्यदि defined(SDL_VIDEO_DRIVER_ANDROID) || defined(SDL_VIDEO_DRIVER_VIVANTE)
// Android
#परिभाषय DEFAULT_EGL        "libEGL.so"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.so"
#परिभाषय DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#परिभाषय DEFAULT_OGL_ES     "libGLESv1_CM.so"

#नोचेद्यदि defined(SDL_VIDEO_DRIVER_OPENHARMONY)
#परिभाषय DEFAULT_EGL        "libEGL.so"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv3.so"

#नोचेद्यदि defined(SDL_VIDEO_DRIVER_WINDOWS)
// EGL AND OpenGL ES support via ANGLE
#परिभाषय DEFAULT_EGL        "libEGL.dll"
#परिभाषय DEFAULT_OGL        "opengl32.dll"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.dll"
#परिभाषय DEFAULT_OGL_ES_PVR "libGLES_CM.dll"
#परिभाषय DEFAULT_OGL_ES     "libGLESv1_CM.dll"

#नोचेद्यदि defined(SDL_VIDEO_DRIVER_COCOA)
// EGL AND OpenGL ES support via ANGLE
#परिभाषय DEFAULT_EGL        "libEGL.dylib"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.dylib"
#परिभाषय DEFAULT_OGL_ES_PVR "libGLES_CM.dylib"   //???
#परिभाषय DEFAULT_OGL_ES     "libGLESv1_CM.dylib" //???

#नोचेद्यदि defined(SDL_PLATFORM_OPENBSD)
// OpenBSD
#परिभाषय DEFAULT_OGL        "libGL.so"
#परिभाषय DEFAULT_EGL        "libEGL.so"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.so"
#परिभाषय DEFAULT_OGL_ES_PVR "libGLES_CM.so"
#परिभाषय DEFAULT_OGL_ES     "libGLESv1_CM.so"

#नोचेद्यदि defined(SDL_VIDEO_DRIVER_QNX)
// QNX
#परिभाषय DEFAULT_EGL        "libEGL.so.1"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.so.1"

#अन्यथा
// Desktop Linux/Unix-like
#परिभाषय DEFAULT_OGL        "libGL.so.1"
#परिभाषय DEFAULT_EGL        "libEGL.so.1"
#परिभाषय ALT_OGL            "libOpenGL.so.0"
#परिभाषय DEFAULT_OGL_ES2    "libGLESv2.so.2"
#परिभाषय DEFAULT_OGL_ES_PVR "libGLES_CM.so.1"
#परिभाषय DEFAULT_OGL_ES     "libGLESv1_CM.so.1"

SDL_ELF_NOTE_DLOPEN(
    "egl-opengl",
    "Support for OpenGL",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_OGL, ALT_OGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-egl",
    "Support for EGL",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_EGL
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es2",
    "Support for EGL ES2",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_OGL_ES2
)
SDL_ELF_NOTE_DLOPEN(
    "egl-es-pvr",
    "Support for EGL ES PVR",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_OGL_ES_PVR
)
SDL_ELF_NOTE_DLOPEN(
    "egl-ogl-es",
    "Support for OpenGL ES",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    DEFAULT_OGL_ES
)
#यदि_अन्तः // SDL_VIDEO_DRIVER_RPI

#यदि defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_VITA_PVR_OGL)
#अन्तर्भाव <SDL3/SDL_opengl.h>
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
प्रकारनिर्देश शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint * params);
#यदि_अन्तः

#यदि defined(SDL_VIDEO_STATIC_ANGLE) || defined(SDL_VIDEO_DRIVER_VITA)
#परिभाषय आरोपय_FUNC(TYPE, NAME) \
    _this->egl_दत्त->NAME = NAME;
#अन्यथा
#परिभाषय आरोपय_FUNC(TYPE, NAME)                                                               \
    _this->egl_दत्त->NAME = (TYPE)SDL_आरोपय_Function(_this->egl_दत्त->egl_dll_handle, #NAME); \
    यदि (!_this->egl_दत्त->NAME) {                                                     \
        प्रत्यागम SDL_समुच्चयः_Error("Could not retrieve EGL function " #NAME);                \
    }
#यदि_अन्तः

// it is allowed to not have some of the EGL extensions on start - attempts to use them will fail later.
#परिभाषय आरोपय_FUNC_EGLEXT(TYPE, NAME) \
    _this->egl_दत्त->NAME = (TYPE)_this->egl_दत्त->egl_Get_Proc_स्थानाङ्कः(#NAME);

स्थिर ध्रुव वर्ण *SDL_EGL_GetErrorName(EGLint egl_Error_संहिता)
{
#परिभाषय SDL_EGL_ERROR_TRANSLATE(e) \
    पक्ष e:                        \
        प्रत्यागम #e
    विकल्प (egl_Error_संहिता) {
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
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_मेलनम्);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_PARAMETER);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_PIXMAP);
        SDL_EGL_ERROR_TRANSLATE(EGL_BAD_NATIVE_गवाक्षः);
        SDL_EGL_ERROR_TRANSLATE(EGL_CONTEXT_नष्टम्);
    }
    प्रत्यागम "";
}

bool SDL_EGL_समुच्चयः_Error_Ex(ध्रुव वर्ण *सन्देशः, ध्रुव वर्ण *eglFunctionName, EGLint egl_Error_संहिता)
{
    ध्रुव वर्ण *errorText = SDL_EGL_GetErrorName(egl_Error_संहिता);
    वर्ण altErrorText[32];
    यदि (errorText[0] == '\0') {
        // An unknown-to-SDL error code was reported.  Report its hexadecimal value, instead of its name.
        (शून्य)SDL_snprintf(altErrorText, SDL_arraysize(altErrorText), "0x%x", (अचिह्नित पूर्णाङ्क)egl_Error_संहिता);
        errorText = altErrorText;
    }
    प्रत्यागम SDL_समुच्चयः_Error("%s (call to %s failed, reporting an error of %s)", सन्देशः, eglFunctionName, errorText);
}

// EGL implementation of SDL OpenGL ES support

bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ध्रुव वर्ण *ext)
{
    size_t ext_len;
    ध्रुव वर्ण *ext_override;
    ध्रुव वर्ण *egl_extstr;
    ध्रुव वर्ण *ext_start;

    // Invalid extensions can be rejected early
    यदि (!ext || *ext == 0 || SDL_strchr(ext, ' ') != रिक्त) {
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid EGL extension");
        प्रत्यागम false;
    }

    /* Extensions can be masked with a hint or environment variable.
     * Unlike the OpenGL override, this will use the set bits of an integer
     * to disable the extension.
     *  Bit   Action
     *  0     If set, the display extension is masked and not present to SDL.
     *  1     If set, the client extension is masked and not present to SDL.
     */
    ext_override = SDL_GetHint(ext);
    यदि (ext_override) {
        पूर्णाङ्क disable_ext = SDL_atoi(ext_override);
        यदि (disable_ext & 0x01 && type == SDL_EGL_DISPLAY_EXTENSION) {
            प्रत्यागम false;
        } अन्यथा यदि (disable_ext & 0x02 && type == SDL_EGL_CLIENT_EXTENSION) {
            प्रत्यागम false;
        }
    }

    ext_len = SDL_strlen(ext);
    विकल्प (type) {
    पक्ष SDL_EGL_DISPLAY_EXTENSION:
        egl_extstr = _this->egl_दत्त->eglQueryString(_this->egl_दत्त->egl_display, EGL_EXTENSIONS);
        भङ्ग;
    पक्ष SDL_EGL_CLIENT_EXTENSION:
        /* EGL_EXT_client_extensions modifies eglQueryString to return client extensions
         * if EGL_NO_DISPLAY is passed. Implementations without it are required to return NULL.
         * This behavior is included in EGL 1.5.
         */
        egl_extstr = _this->egl_दत्त->eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        भङ्ग;
    स्वभाव:
        // SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "SDL_EGL_HasExtension: Invalid extension type");
        प्रत्यागम false;
    }

    यदि (egl_extstr) {
        ext_start = egl_extstr;

        यावत् (*ext_start) {
            ext_start = SDL_strstr(ext_start, ext);
            यदि (!ext_start) {
                प्रत्यागम false;
            }
            // Check if the match is not just a substring of one of the extensions
            यदि (ext_start == egl_extstr || *(ext_start - 1) == ' ') {
                यदि (ext_start[ext_len] == ' ' || ext_start[ext_len] == 0) {
                    प्रत्यागम true;
                }
            }
            // If the search stopped in the middle of an extension, skip to the end of it
            ext_start += ext_len;
            यावत् (*ext_start != ' ' && *ext_start != 0) {
                ext_start++;
            }
        }
    }

    प्रत्यागम false;
}

SDL_FunctionPointer SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer परिणाम = रिक्त;
    यदि (_this->egl_दत्त) {
        ध्रुव Uint32 eglver = (((Uint32)_this->egl_दत्त->egl_संस्करणम्_major) << 16) | ((Uint32)_this->egl_दत्त->egl_संस्करणम्_minor);
        ध्रुव bool is_egl_15_or_later = eglver >= ((((Uint32)1) << 16) | 5);

        // EGL 1.5 can use eglGetProcAddress() for any symbol. 1.4 and earlier can't use it for core entry points.
        यदि (!परिणाम && is_egl_15_or_later && _this->egl_दत्त->egl_Get_Proc_स्थानाङ्कः) {
            परिणाम = _this->egl_दत्त->egl_Get_Proc_स्थानाङ्कः(proc);
        }

#यदि !defined(SDL_VIDEO_DRIVER_VITA)
        // Try SDL_LoadFunction() first for EGL <= 1.4, or as a fallback for >= 1.5.
        यदि (!परिणाम) {
            परिणाम = SDL_आरोपय_Function(_this->egl_दत्त->opengl_dll_handle, proc);
        }
#यदि_अन्तः

        // Try eglGetProcAddress if we're on <= 1.4 and still searching...
        यदि (!परिणाम && !is_egl_15_or_later && _this->egl_दत्त->egl_Get_Proc_स्थानाङ्कः) {
            परिणाम = _this->egl_दत्त->egl_Get_Proc_स्थानाङ्कः(proc);
        }
    }
    प्रत्यागम परिणाम;
}

शून्य SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    यदि (_this->egl_दत्त) {
        यदि (_this->egl_दत्त->egl_display) {
            _this->egl_दत्त->eglTerminate(_this->egl_दत्त->egl_display);
            _this->egl_दत्त->egl_display = रिक्त;
        }

        यदि (_this->egl_दत्त->egl_dll_handle) {
            SDL_UnloadObject(_this->egl_दत्त->egl_dll_handle);
            _this->egl_दत्त->egl_dll_handle = रिक्त;
        }
        यदि (_this->egl_दत्त->opengl_dll_handle) {
            SDL_UnloadObject(_this->egl_दत्त->opengl_dll_handle);
            _this->egl_दत्त->opengl_dll_handle = रिक्त;
        }

        SDL_free(_this->egl_दत्त);
        _this->egl_दत्त = रिक्त;
    }
}

स्थिर bool SDL_EGL_आरोपय_Library_आन्तरिकम्(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_मार्गः)
{
    SDL_SharedObject *egl_dll_handle = रिक्त;
#यदि !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    SDL_SharedObject *opengl_dll_handle = रिक्त;
#यदि_अन्तः
    ध्रुव वर्ण *मार्गः = रिक्त;
#यदि defined(SDL_VIDEO_DRIVER_WINDOWS)
    ध्रुव वर्ण *d3dcompiler;
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RPI
    bool vc4 = (0 == access("/sys/module/vc4/", F_OK));
#यदि_अन्तः

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS)
    d3dcompiler = SDL_GetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER);
    यदि (d3dcompiler) {
        यदि (SDL_strcasecmp(d3dcompiler, "none") != 0) {
            यदि (SDL_आरोपय_Object(d3dcompiler) == रिक्त) {
                SDL_ClearError();
            }
        }
    } अन्यथा {
        यदि (WIN_IsWindowsVistaOrGreater()) {
            // Try the newer d3d compilers first
            ध्रुव वर्ण *d3dcompiler_list[] = {
                "d3dcompiler_47.dll",
                "d3dcompiler_46.dll",
            };
            पूर्णाङ्क i;

            प्रति (i = 0; i < SDL_arraysize(d3dcompiler_list); ++i) {
                यदि (SDL_आरोपय_Object(d3dcompiler_list[i]) != रिक्त) {
                    भङ्ग;
                }
                SDL_ClearError();
            }
        } अन्यथा {
            यदि (SDL_आरोपय_Object("d3dcompiler_43.dll") == रिक्त) {
                SDL_ClearError();
            }
        }
    }
#यदि_अन्तः

#यदि !defined(SDL_VIDEO_STATIC_ANGLE) && !defined(SDL_VIDEO_DRIVER_VITA)
    /* A funny thing, loading EGL.so first does not work on the Raspberry, so we load libGL* first */
    मार्गः = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    यदि (मार्गः) {
        opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
    }

    यदि (!opengl_dll_handle) {
        यदि (_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) {
            यदि (_this->gl_config.major_संस्करणम् > 1) {
#यदि_परिभाषितम् DEFAULT_OGL_ES2
                यदि (!opengl_dll_handle) {
                    मार्गः = DEFAULT_OGL_ES2;
                    opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
                }
#यदि_अन्तः
#यदि_परिभाषितम् ALT_OGL_ES2
                यदि (!opengl_dll_handle && !vc4) {
                    मार्गः = ALT_OGL_ES2;
                    opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
                }
#यदि_अन्तः
            } अन्यथा {
#यदि_परिभाषितम् DEFAULT_OGL_ES
                यदि (!opengl_dll_handle) {
                    मार्गः = DEFAULT_OGL_ES;
                    opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
                }
#यदि_अन्तः
#यदि_परिभाषितम् DEFAULT_OGL_ES_PVR
                यदि (!opengl_dll_handle) {
                    मार्गः = DEFAULT_OGL_ES_PVR;
                    opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
                }
#यदि_अन्तः
#यदि_परिभाषितम् ALT_OGL_ES
                यदि (!opengl_dll_handle && !vc4) {
                    मार्गः = ALT_OGL_ES;
                    opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
                }
#यदि_अन्तः
            }
        } अन्यथा {
#यदि_परिभाषितम् DEFAULT_OGL
            यदि (!opengl_dll_handle) {
                मार्गः = DEFAULT_OGL;
                opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
            }
#यदि_अन्तः
#यदि_परिभाषितम् ALT_OGL
            यदि (!opengl_dll_handle) {
                मार्गः = ALT_OGL;
                opengl_dll_handle = SDL_आरोपय_Object(मार्गः);
            }
#यदि_अन्तः
        }
    }
    _this->egl_दत्त->opengl_dll_handle = opengl_dll_handle;

    यदि (!opengl_dll_handle) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not initialize OpenGL / GLES library");
    }

    /* Loading libGL* in the previous step took care of loading libEGL.so, but we future proof by double checking */
    यदि (egl_मार्गः) {
        egl_dll_handle = SDL_आरोपय_Object(egl_मार्गः);
    }
    // Try loading a EGL symbol, if it does not work try the default library paths
    यदि (!egl_dll_handle || SDL_आरोपय_Function(egl_dll_handle, "eglChooseConfig") == रिक्त) {
        यदि (egl_dll_handle) {
            SDL_UnloadObject(egl_dll_handle);
        }
        मार्गः = SDL_GetHint(SDL_HINT_EGL_LIBRARY);
        यदि (!मार्गः) {
            मार्गः = DEFAULT_EGL;
        }
        egl_dll_handle = SDL_आरोपय_Object(मार्गः);

#यदि_परिभाषितम् ALT_EGL
        यदि (!egl_dll_handle && !vc4) {
            मार्गः = ALT_EGL;
            egl_dll_handle = SDL_आरोपय_Object(मार्गः);
        }
#यदि_अन्तः

        यदि (!egl_dll_handle || SDL_आरोपय_Function(egl_dll_handle, "eglChooseConfig") == रिक्त) {
            यदि (egl_dll_handle) {
                SDL_UnloadObject(egl_dll_handle);
            }
            प्रत्यागम SDL_समुच्चयः_Error("Could not load EGL library");
        }
        SDL_ClearError();
    }
#यदि_अन्तः

    _this->egl_दत्त->egl_dll_handle = egl_dll_handle;

    // Load new function pointers
    आरोपय_FUNC(PFNEGLGETDISPLAYPROC, eglGetDisplay);
    आरोपय_FUNC(PFNEGLINITIALIZEPROC, eglInitialize);
    आरोपय_FUNC(PFNEGLTERMINATEPROC, eglTerminate);
    आरोपय_FUNC(PFNEGLGETPROCADDRESSPROC, egl_Get_Proc_स्थानाङ्कः);
    आरोपय_FUNC(PFNEGLCHOOSECONFIGPROC, egl_वृणु_Config);
    आरोपय_FUNC(PFNEGLCREATECONTEXTPROC, eglCreateContext);
    आरोपय_FUNC(PFNEGLDESTROYCONTEXTPROC, eglDestroyContext);
    आरोपय_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface);
    आरोपय_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, egl_Create_गवाक्षः_Surface);
    आरोपय_FUNC(PFNEGLDESTROYSURFACEPROC, eglDestroySurface);
    आरोपय_FUNC(PFNEGLMAKECURRENTPROC, eglMakeCurrent);
    आरोपय_FUNC(PFNEGLSWAPBUFFERSPROC, eglSwapBuffers);
    आरोपय_FUNC(PFNEGLSWAPINTERVALPROC, eglSwapInterval);
    आरोपय_FUNC(PFNEGLQUERYSTRINGPROC, eglQueryString);
    आरोपय_FUNC(PFNEGLGETCONFIGATTRIBPROC, eglGetConfigAttrib);
    आरोपय_FUNC(PFNEGLWAITNATIVEPROC, eglWaitNative);
    आरोपय_FUNC(PFNEGLWAITGLPROC, eglWaitGL);
    आरोपय_FUNC(PFNEGLBINDAPIPROC, eglBindAPI);
    आरोपय_FUNC(PFNEGLGETERRORPROC, eglGetError);
    आरोपय_FUNC_EGLEXT(PFNEGLQUERYDEVICESEXTPROC, eglQueryDevicesEXT);
    आरोपय_FUNC_EGLEXT(PFNEGLGETPLATFORMDISPLAYEXTPROC, eglGetPlatformDisplayEXT);
    // Atomic functions
    आरोपय_FUNC_EGLEXT(PFNEGLCREATESYNCKHRPROC, eglCreateSyncKHR);
    आरोपय_FUNC_EGLEXT(PFNEGLDESTROYSYNCKHRPROC, eglDestroySyncKHR);
    आरोपय_FUNC_EGLEXT(PFNEGLDUPNATIVEFENCEFDANDROIDPROC, eglDupNativeFenceFDANDROID);
    आरोपय_FUNC_EGLEXT(PFNEGLWAITSYNCKHRPROC, eglWaitSyncKHR);
    आरोपय_FUNC_EGLEXT(PFNEGLCLIENTWAITSYNCKHRPROC, eglClientWaitSyncKHR);
    // Atomic functions end

    यदि (मार्गः) {
        SDL_strlcpy(_this->gl_config.driver_मार्गः, मार्गः, परिमाण(_this->gl_config.driver_मार्गः) - 1);
    } अन्यथा {
        *_this->gl_config.driver_मार्गः = '\0';
    }

    प्रत्यागम true;
}

bool SDL_EGL_आरोपय_Library_Only(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_मार्गः)
{
    यदि (_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL context already created");
    }

    _this->egl_दत्त = (संरचना SDL_EGL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_EGL_Video_दत्त));
    यदि (!_this->egl_दत्त) {
        प्रत्यागम false;
    }

    यदि (!SDL_EGL_आरोपय_Library_आन्तरिकम्(_this, egl_मार्गः)) {
        SDL_free(_this->egl_दत्त);
        _this->egl_दत्त = रिक्त;
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

स्थिर शून्य SDL_EGL_Get_संस्करणम्(SDL_VideoDevice *_this)
{
    यदि (_this->egl_दत्त->eglQueryString) {
        ध्रुव वर्ण *egl_संस्करणम् = _this->egl_दत्त->eglQueryString(_this->egl_दत्त->egl_display, EGL_संस्करणम्);
        यदि (egl_संस्करणम्) {
            पूर्णाङ्क major = 0, minor = 0;
            यदि (SDL_sscanf(egl_संस्करणम्, "%d.%d", &major, &minor) == 2) {
                _this->egl_दत्त->egl_संस्करणम्_major = major;
                _this->egl_दत्त->egl_संस्करणम्_minor = minor;
            } अन्यथा {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Could not parse EGL version string: %s", egl_संस्करणम्);
            }
        }
    }
}

bool SDL_EGL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *egl_मार्गः, NativeDisplayType native_display)
{
    यदि (!SDL_EGL_आरोपय_Library_Only(_this, egl_मार्गः)) {
        प्रत्यागम false;
    }

    _this->egl_दत्त->egl_display = EGL_NO_DISPLAY;

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_VITA
    EGLenum platform = _this->gl_config.egl_platform;
    यदि (platform) {
        /* EGL 1.5 allows querying for client version with EGL_NO_DISPLAY
         * --
         * Khronos doc: "EGL_BAD_DISPLAY is generated if display is not an EGL display connection, unless display is EGL_NO_DISPLAY and name is EGL_EXTENSIONS."
         * Therefore SDL_EGL_GetVersion() shouldn't work with uninitialized display.
         * - it actually doesn't work on Android that has 1.5 egl client
         * - it works on desktop X11 (using SDL_VIDEO_FORCE_EGL=1) */
        SDL_EGL_Get_संस्करणम्(_this);

        यदि (_this->egl_दत्त->egl_संस्करणम्_major == 1 && _this->egl_दत्त->egl_संस्करणम्_minor == 5) {
            आरोपय_FUNC(PFNEGLGETPLATFORMDISPLAYPROC, eglGetPlatformDisplay);
        }

        यदि (_this->egl_दत्त->eglGetPlatformDisplay) {
            EGLAttrib *attribs = रिक्त;
            यदि (_this->egl_platformattrib_callback) {
                attribs = _this->egl_platformattrib_callback(_this->egl_attrib_callback_userdata);
                यदि (!attribs) {
                    _this->gl_config.driver_loaded = 0;
                    *_this->gl_config.driver_मार्गः = '\0';
                    प्रत्यागम SDL_समुच्चयः_Error("EGL platform attribute callback returned NULL pointer");
                }
            }
            _this->egl_दत्त->egl_display = _this->egl_दत्त->eglGetPlatformDisplay(platform, (शून्य *)(uintptr_t)native_display, attribs);
            SDL_free(attribs);
        } अन्यथा {
            यदि (SDL_EGL_HasExtension(_this, SDL_EGL_CLIENT_EXTENSION, "EGL_EXT_platform_base")) {
                _this->egl_दत्त->eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्(_this, "eglGetPlatformDisplayEXT");
                यदि (_this->egl_दत्त->eglGetPlatformDisplayEXT) {
                    _this->egl_दत्त->egl_display = _this->egl_दत्त->eglGetPlatformDisplayEXT(platform, (शून्य *)(uintptr_t)native_display, रिक्त);
                }
            }
        }
    }
#यदि_अन्तः
    // Try the implementation-specific eglGetDisplay even if eglGetPlatformDisplay fails
    यदि ((_this->egl_दत्त->egl_display == EGL_NO_DISPLAY) &&
        (_this->egl_दत्त->eglGetDisplay) &&
        SDL_GetHintBoolean(SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK, true)) {
        _this->egl_दत्त->egl_display = _this->egl_दत्त->eglGetDisplay(native_display);
    }
    यदि (_this->egl_दत्त->egl_display == EGL_NO_DISPLAY) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_मार्गः = '\0';
        प्रत्यागम SDL_समुच्चयः_Error("Could not get EGL display");
    }

    यदि (_this->egl_दत्त->eglInitialize(_this->egl_दत्त->egl_display, रिक्त, रिक्त) != EGL_TRUE) {
        _this->gl_config.driver_loaded = 0;
        *_this->gl_config.driver_मार्गः = '\0';
        प्रत्यागम SDL_समुच्चयः_Error("Could not initialize EGL");
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_संस्करणम्(_this);

    _this->egl_दत्त->is_offscreen = false;

    प्रत्यागम true;
}

/**
   On multi GPU machines EGL device 0 is not always the first valid GPU.
   Container environments can restrict access to some GPUs that are still listed in the EGL
   device list. If the requested device is a restricted GPU and cannot be used
   (eglInitialize() will fail) then attempt to automatically and silently select the next
   valid available GPU for EGL to use.
*/

bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, पूर्णाङ्क device)
{
    शून्य *egl_devices[SDL_EGL_MAX_DEVICES];
    EGLint अङ्कः_egl_devices = 0;
    ध्रुव वर्ण *egl_device_hint;

    यदि (_this->gl_config.driver_loaded <= 0) {
        प्रत्यागम SDL_समुच्चयः_Error("SDL_EGL_LoadLibraryOnly() has not been called or has failed.");
    }

    // Check for all extensions that are optional until used and fail if any is missing
    यदि (!_this->egl_दत्त->eglQueryDevicesEXT) {
        प्रत्यागम SDL_समुच्चयः_Error("eglQueryDevicesEXT is missing (EXT_device_enumeration not supported by the drivers?)");
    }

    यदि (!_this->egl_दत्त->eglGetPlatformDisplayEXT) {
        प्रत्यागम SDL_समुच्चयः_Error("eglGetPlatformDisplayEXT is missing (EXT_platform_base not supported by the drivers?)");
    }

    यदि (_this->egl_दत्त->eglQueryDevicesEXT(SDL_EGL_MAX_DEVICES, egl_devices, &अङ्कः_egl_devices) != EGL_TRUE) {
        प्रत्यागम SDL_समुच्चयः_Error("eglQueryDevicesEXT() failed");
    }

    egl_device_hint = SDL_GetHint("SDL_HINT_EGL_DEVICE");
    यदि (egl_device_hint) {
        device = SDL_atoi(egl_device_hint);

        यदि (device >= अङ्कः_egl_devices) {
            प्रत्यागम SDL_समुच्चयः_Error("Invalid EGL device is requested.");
        }

        _this->egl_दत्त->egl_display = _this->egl_दत्त->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[device], रिक्त);

        यदि (_this->egl_दत्त->egl_display == EGL_NO_DISPLAY) {
            प्रत्यागम SDL_समुच्चयः_Error("eglGetPlatformDisplayEXT() failed.");
        }

        यदि (_this->egl_दत्त->eglInitialize(_this->egl_दत्त->egl_display, रिक्त, रिक्त) != EGL_TRUE) {
            प्रत्यागम SDL_समुच्चयः_Error("Could not initialize EGL");
        }
    } अन्यथा {
        पूर्णाङ्क i;
        bool प्राप्तम् = false;
        EGLDisplay attempted_egl_display;

        // If no hint is provided lets look for the first device/display that will allow us to eglInit
        प्रति (i = 0; i < अङ्कः_egl_devices; i++) {
            attempted_egl_display = _this->egl_दत्त->eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, egl_devices[i], रिक्त);

            यदि (attempted_egl_display == EGL_NO_DISPLAY) {
                अनुवर्त;
            }

            यदि (_this->egl_दत्त->eglInitialize(attempted_egl_display, रिक्त, रिक्त) != EGL_TRUE) {
                _this->egl_दत्त->eglTerminate(attempted_egl_display);
                अनुवर्त;
            }

            // We did not fail, we'll pick this one!
            _this->egl_दत्त->egl_display = attempted_egl_display;
            प्राप्तम् = true;

            भङ्ग;
        }

        यदि (!प्राप्तम्) {
            प्रत्यागम SDL_समुच्चयः_Error("Could not find a valid EGL device to initialize");
        }
    }

    // Get the EGL version with a valid egl_display, for EGL <= 1.4
    SDL_EGL_Get_संस्करणम्(_this);

    _this->egl_दत्त->is_offscreen = true;

    प्रत्यागम true;
}

शून्य SDL_EGL_समुच्चयः_Required_Visual_Id(SDL_VideoDevice *_this, पूर्णाङ्क visual_id)
{
    _this->egl_दत्त->egl_required_visual_id = visual_id;
}

#यदि_परिभाषितम् DUMP_EGL_CONFIG

#परिभाषय ATTRIBUTE(_attr) \
    {                    \
        _attr, #_attr    \
    }

प्रकारनिर्देश संरचना
{
    EGLint attribute;
    वर्ण ध्रुव *name;
} Attribute;

स्थिर Attribute all_गुणाः[] = {
    ATTRIBUTE(EGL_बफर_आकार),
    ATTRIBUTE(EGL_ALPHA_आकार),
    ATTRIBUTE(EGL_BLUE_आकार),
    ATTRIBUTE(EGL_GREEN_आकार),
    ATTRIBUTE(EGL_RED_आकार),
    ATTRIBUTE(EGL_गभीरता_आकार),
    ATTRIBUTE(EGL_STENCIL_आकार),
    ATTRIBUTE(EGL_CONFIG_CAVEAT),
    ATTRIBUTE(EGL_CONFIG_ID),
    ATTRIBUTE(EGL_LEVEL),
    ATTRIBUTE(EGL_MAX_PBUFFER_HEIGHT),
    ATTRIBUTE(EGL_MAX_PBUFFER_विस्तारः),
    ATTRIBUTE(EGL_MAX_PBUFFER_PIXELS),
    ATTRIBUTE(EGL_NATIVE_RENDERABLE),
    ATTRIBUTE(EGL_NATIVE_VISUAL_ID),
    ATTRIBUTE(EGL_NATIVE_VISUAL_TYPE),
    ATTRIBUTE(EGL_SAMPLES),
    ATTRIBUTE(EGL_SAMPLE_BUFFERS),
    ATTRIBUTE(EGL_SURFACE_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_TYPE),
    ATTRIBUTE(EGL_TRANSPARENT_BLUE_मानम्),
    ATTRIBUTE(EGL_TRANSPARENT_GREEN_मानम्),
    ATTRIBUTE(EGL_TRANSPARENT_RED_मानम्),
    ATTRIBUTE(EGL_BIND_गन्तव्यम्_TEXTURE_RGB),
    ATTRIBUTE(EGL_BIND_गन्तव्यम्_TEXTURE_RGBA),
    ATTRIBUTE(EGL_MIN_SWAP_INTERVAL),
    ATTRIBUTE(EGL_MAX_SWAP_INTERVAL),
    ATTRIBUTE(EGL_LUMINANCE_आकार),
    ATTRIBUTE(EGL_ALPHA_आवरणम्_आकार),
    ATTRIBUTE(EGL_COLOR_बफर_TYPE),
    ATTRIBUTE(EGL_RENDERABLE_TYPE),
    ATTRIBUTE(EGL_मेलनम्_NATIVE_PIXMAP),
    ATTRIBUTE(EGL_CONFORMANT),
};

स्थिर शून्य dumpconfig(SDL_VideoDevice *_this, EGLConfig config)
{
    पूर्णाङ्क attr;
    प्रति (attr = 0; attr < SDL_arraysize(all_गुणाः); attr++) {
        EGLint मानम्;
        _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, config, all_गुणाः[attr].attribute, &मानम्);
        SDL_Log("\t%-32s: %10d (0x%08x)", all_गुणाः[attr].name, मानम्, मानम्);
    }
}

#यदि_अन्तः // DUMP_EGL_CONFIG

स्थिर bool SDL_EGL_वैयक्तिकम्_वृणु_Config(SDL_VideoDevice *_this, bool समुच्चयः_config_caveat_none)
{
    // 64 seems nice.
    EGLint attribs[64];
    EGLint प्राप्तम्_configs = 0, मानम्;
    // 128 seems even nicer here
    EGLConfig configs[128];
    bool has_matching_format = false;
    पूर्णाङ्क i, j, best_bitdiff = -1, best_truecolor_bitdiff = -1;
    पूर्णाङ्क truecolor_config_idx = -1;

    // Get a valid EGL configuration
    i = 0;
    attribs[i++] = EGL_RED_आकार;
    attribs[i++] = _this->gl_config.red_आकार;
    attribs[i++] = EGL_GREEN_आकार;
    attribs[i++] = _this->gl_config.green_आकार;
    attribs[i++] = EGL_BLUE_आकार;
    attribs[i++] = _this->gl_config.blue_आकार;

    यदि (समुच्चयः_config_caveat_none) {
        attribs[i++] = EGL_CONFIG_CAVEAT;
        attribs[i++] = EGL_NONE;
    }

    यदि (_this->gl_config.alpha_आकार) {
        attribs[i++] = EGL_ALPHA_आकार;
        attribs[i++] = _this->gl_config.alpha_आकार;
    }

    यदि (_this->gl_config.बफर_आकार) {
        attribs[i++] = EGL_बफर_आकार;
        attribs[i++] = _this->gl_config.बफर_आकार;
    }

    यदि (_this->gl_config.गभीरता_आकार) {
        attribs[i++] = EGL_गभीरता_आकार;
        attribs[i++] = _this->gl_config.गभीरता_आकार;
    }

    यदि (_this->gl_config.stencil_आकार) {
        attribs[i++] = EGL_STENCIL_आकार;
        attribs[i++] = _this->gl_config.stencil_आकार;
    }

    यदि (_this->gl_config.multisamplebuffers) {
        attribs[i++] = EGL_SAMPLE_BUFFERS;
        attribs[i++] = _this->gl_config.multisamplebuffers;
    }

    यदि (_this->gl_config.multisamplesamples) {
        attribs[i++] = EGL_SAMPLES;
        attribs[i++] = _this->gl_config.multisamplesamples;
    }

    यदि (_this->gl_config.floatbuffers) {
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_EXT;
        attribs[i++] = EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT;
    }

    यदि (_this->egl_दत्त->is_offscreen) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = EGL_PBUFFER_BIT;
    }

    attribs[i++] = EGL_RENDERABLE_TYPE;
    यदि (_this->gl_config.profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES) {
#यदि_परिभाषितम् EGL_KHR_create_context
        यदि (_this->gl_config.major_संस्करणम् >= 3 &&
            SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[i++] = EGL_OPENGL_ES3_BIT_KHR;
        } अन्यथा
#यदि_अन्तः
            यदि (_this->gl_config.major_संस्करणम् >= 2) {
            attribs[i++] = EGL_OPENGL_ES2_BIT;
        } अन्यथा {
            attribs[i++] = EGL_OPENGL_ES_BIT;
        }
        _this->egl_दत्त->eglBindAPI(EGL_OPENGL_ES_API);
    } अन्यथा {
        attribs[i++] = EGL_OPENGL_BIT;
        _this->egl_दत्त->eglBindAPI(EGL_OPENGL_API);
    }

    यदि (_this->egl_दत्त->egl_surfacetype) {
        attribs[i++] = EGL_SURFACE_TYPE;
        attribs[i++] = _this->egl_दत्त->egl_surfacetype;
    }

    attribs[i++] = EGL_NONE;

    SDL_assert(i < SDL_arraysize(attribs));

    यदि (_this->egl_दत्त->egl_वृणु_Config(_this->egl_दत्त->egl_display,
                                         attribs,
                                         configs, SDL_arraysize(configs),
                                         &प्राप्तम्_configs) == EGL_FALSE ||
        प्राप्तम्_configs == 0) {
        प्रत्यागम false;
    }

    // first ensure that a found config has a matching format, or the function will fall through.
    यदि (_this->egl_दत्त->egl_required_visual_id) {
        प्रति (i = 0; i < प्राप्तम्_configs; i++) {
            EGLint format;
            _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            यदि (_this->egl_दत्त->egl_required_visual_id == format) {
                has_matching_format = true;
                भङ्ग;
            }
        }
    }

    // eglChooseConfig returns a number of configurations that match or exceed the requested attribs.
    // From those, we select the one that matches our requirements more closely via a makeshift algorithm

    प्रति (i = 0; i < प्राप्तम्_configs; i++) {
        bool is_truecolor = false;
        पूर्णाङ्क bitdiff = 0;

        यदि (has_matching_format && _this->egl_दत्त->egl_required_visual_id) {
            EGLint format;
            _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display,
                                                configs[i],
                                                EGL_NATIVE_VISUAL_ID, &format);
            यदि (_this->egl_दत्त->egl_required_visual_id != format) {
                अनुवर्त;
            }
        }

        _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, configs[i], EGL_RED_आकार, &मानम्);
        यदि (मानम् == 8) {
            _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, configs[i], EGL_GREEN_आकार, &मानम्);
            यदि (मानम् == 8) {
                _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, configs[i], EGL_BLUE_आकार, &मानम्);
                यदि (मानम् == 8) {
                    is_truecolor = true;
                }
            }
        }

        प्रति (j = 0; j < SDL_arraysize(attribs) - 1; j += 2) {
            यदि (attribs[j] == EGL_NONE) {
                भङ्ग;
            }

            यदि (attribs[j + 1] != EGL_DONT_CARE && (attribs[j] == EGL_RED_आकार ||
                                                    attribs[j] == EGL_GREEN_आकार ||
                                                    attribs[j] == EGL_BLUE_आकार ||
                                                    attribs[j] == EGL_ALPHA_आकार ||
                                                    attribs[j] == EGL_गभीरता_आकार ||
                                                    attribs[j] == EGL_STENCIL_आकार)) {
                _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display, configs[i], attribs[j], &मानम्);
                bitdiff += मानम् - attribs[j + 1]; // value is always >= attrib
            }
        }

        यदि ((bitdiff < best_bitdiff) || (best_bitdiff == -1)) {
            _this->egl_दत्त->egl_config = configs[i];
            best_bitdiff = bitdiff;
        }

        यदि (is_truecolor && ((bitdiff < best_truecolor_bitdiff) || (best_truecolor_bitdiff == -1))) {
            truecolor_config_idx = i;
            best_truecolor_bitdiff = bitdiff;
        }
    }

#परिभाषय FAVOR_TRUECOLOR 1
#यदि FAVOR_TRUECOLOR
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
    यदि (((_this->gl_config.red_आकार + _this->gl_config.blue_आकार + _this->gl_config.green_आकार) <= 16)) {
        यदि (truecolor_config_idx != -1) {
            _this->egl_दत्त->egl_config = configs[truecolor_config_idx];
        }
    }
#यदि_अन्तः

#यदि_परिभाषितम् DUMP_EGL_CONFIG
    dumpconfig(_this, _this->egl_दत्त->egl_config);
#यदि_अन्तः

    प्रत्यागम true;
}

bool SDL_EGL_वृणु_Config(SDL_VideoDevice *_this)
{
    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    // Try with EGL_CONFIG_CAVEAT set to EGL_NONE, to avoid any EGL_SLOW_CONFIG or EGL_NON_CONFORMANT_CONFIG
    यदि (SDL_EGL_वैयक्तिकम्_वृणु_Config(_this, true)) {
        प्रत्यागम true;
    }

    // Fallback with all configs
    यदि (SDL_EGL_वैयक्तिकम्_वृणु_Config(_this, false)) {
        SDL_Log("SDL_EGL_ChooseConfig: found a slow EGL config");
        प्रत्यागम true;
    }

    प्रत्यागम SDL_EGL_समुच्चयः_Error("Couldn't find matching EGL config", "eglChooseConfig");
}

SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    // max 16 key+value pairs plus terminator.
    EGLint attribs[33];
    पूर्णाङ्क attr = 0;

    EGLContext egl_context, share_context = EGL_NO_CONTEXT;
    EGLint profile_आवरणम् = _this->gl_config.profile_आवरणम्;
    EGLint major_संस्करणम् = _this->gl_config.major_संस्करणम्;
    EGLint minor_संस्करणम् = _this->gl_config.minor_संस्करणम्;
    bool profile_es = (profile_आवरणम् == SDL_GL_CONTEXT_PROFILE_ES);

    यदि (!_this->egl_दत्त) {
        SDL_समुच्चयः_Error("EGL not initialized");
        प्रत्यागम रिक्त;
    }

    यदि (_this->gl_config.share_with_current_context) {
        share_context = (EGLContext)SDL_GL_GetCurrentContext();
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
    यदि (_this->gl_config.flags & SDL_GL_CONTEXT_DEBUG_FLAG) {
        /* If SDL_GL_CONTEXT_DEBUG_FLAG is set but EGL_KHR_debug unsupported, unset.
         * This is required because some Android devices like to complain about it
         * by "silently" failing, logging a hint which could be easily overlooked:
         * E/libEGL  (26984): validate_display:255 error 3008 (EGL_BAD_DISPLAY)
         * The following explicitly checks for EGL_KHR_debug before EGL 1.5
         */
        पूर्णाङ्क egl_संस्करणम्_major = _this->egl_दत्त->egl_संस्करणम्_major;
        पूर्णाङ्क egl_संस्करणम्_minor = _this->egl_दत्त->egl_संस्करणम्_minor;
        यदि (((egl_संस्करणम्_major < 1) || (egl_संस्करणम्_major == 1 && egl_संस्करणम्_minor < 5)) &&
            !SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_debug")) {
            // SDL profile bits match EGL profile bits.
            _this->gl_config.flags &= ~SDL_GL_CONTEXT_DEBUG_FLAG;
        }
    }
#यदि_अन्तः

    // Set the context version and other attributes.
    यदि ((major_संस्करणम् < 3 || (minor_संस्करणम् == 0 && profile_es)) &&
        _this->gl_config.flags == 0 &&
        (profile_आवरणम् == 0 || profile_es)) {
        /* Create a context without using EGL_KHR_create_context attribs.
         * When creating a GLES context without EGL_KHR_create_context we can
         * only specify the major version. When creating a desktop GL context
         * we can't specify any version, so we only try in that case when the
         * version is less than 3.0 (matches SDL's GLX/WGL behavior.)
         */
        यदि (profile_es) {
            attribs[attr++] = EGL_CONTEXT_CLIENT_संस्करणम्;
            attribs[attr++] = SDL_max(major_संस्करणम्, 1);
        }
    } अन्यथा {
#यदि_परिभाषितम् EGL_KHR_create_context
        /* The Major/minor version, context profiles, and context flags can
         * only be specified when this extension is available.
         */
        यदि (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context")) {
            attribs[attr++] = EGL_CONTEXT_MAJOR_संस्करणम्_KHR;
            attribs[attr++] = major_संस्करणम्;
            attribs[attr++] = EGL_CONTEXT_MINOR_संस्करणम्_KHR;
            attribs[attr++] = minor_संस्करणम्;

            // SDL profile bits match EGL profile bits.
            यदि (profile_आवरणम् != 0 && profile_आवरणम् != SDL_GL_CONTEXT_PROFILE_ES) {
                attribs[attr++] = EGL_CONTEXT_OPENGL_PROFILE_आवरणम्_KHR;
                attribs[attr++] = profile_आवरणम्;
            }

            // SDL flags match EGL flags.
            यदि (_this->gl_config.flags != 0) {
                attribs[attr++] = EGL_CONTEXT_FLAGS_KHR;
                attribs[attr++] = _this->gl_config.flags;
            }
        } अन्यथा
#यदि_अन्तः // EGL_KHR_create_context
        {
            SDL_समुच्चयः_Error("Could not create EGL context (context attributes are not supported)");
            प्रत्यागम रिक्त;
        }
    }

#यदि_परिभाषितम् EGL_KHR_create_context_no_error
    यदि (_this->gl_config.no_error) {
        यदि (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_create_context_no_error")) {
            attribs[attr++] = EGL_CONTEXT_OPENGL_NO_ERROR_KHR;
            attribs[attr++] = _this->gl_config.no_error;
        }
    }
#यदि_अन्तः

    यदि (_this->egl_contextattrib_callback) {
        ध्रुव पूर्णाङ्क maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_contextattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_दत्त->egl_display, _this->egl_दत्त->egl_config);
        यदि (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_मार्गः = '\0';
            SDL_समुच्चयः_Error("EGL context attribute callback returned NULL pointer");
            प्रत्यागम रिक्त;
        }

        प्रति (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            यदि (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_मार्गः = '\0';
                SDL_समुच्चयः_Error("EGL context attribute callback returned too many attributes");
                प्रत्यागम रिक्त;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    // Bind the API
    यदि (profile_es) {
        _this->egl_दत्त->apitype = EGL_OPENGL_ES_API;
    } अन्यथा {
        _this->egl_दत्त->apitype = EGL_OPENGL_API;
    }
    यदि (!_this->egl_दत्त->eglBindAPI(_this->egl_दत्त->apitype)) {
        SDL_समुच्चयः_Error("Could not bind EGL API");
        प्रत्यागम रिक्त;
    }

    egl_context = _this->egl_दत्त->eglCreateContext(_this->egl_दत्त->egl_display,
                                                    _this->egl_दत्त->egl_config,
                                                    share_context, attribs);

    यदि (egl_context == EGL_NO_CONTEXT) {
        SDL_EGL_समुच्चयः_Error("Could not create EGL context", "eglCreateContext");
        प्रत्यागम रिक्त;
    }

    // The default swap interval is 1, according to the spec, but SDL3's policy is to default vsync to off by default.
    _this->egl_दत्त->egl_swapinterval = 0;

    यदि (!SDL_EGL_MakeCurrent(_this, egl_surface, (SDL_GLContext)egl_context)) {
        // Delete the context
        SDL_EGL_DestroyContext(_this, (SDL_GLContext)egl_context);
        प्रत्यागम रिक्त;
    }

    /* Check whether making contexts current without a surface is supported.
     * First condition: EGL must support it. That's the case for EGL 1.5
     * or later, or if the EGL_KHR_surfaceless_context extension is present. */
    यदि ((_this->egl_दत्त->egl_संस्करणम्_major > 1) ||
        ((_this->egl_दत्त->egl_संस्करणम्_major == 1) && (_this->egl_दत्त->egl_संस्करणम्_minor >= 5)) ||
        SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_surfaceless_context")) {
        // Secondary condition: The client API must support it.
        यदि (profile_es) {
            /* On OpenGL ES, the GL_OES_surfaceless_context extension must be
             * present. */
            यदि (SDL_GL_ExtensionSupported("GL_OES_surfaceless_context")) {
                _this->gl_allow_no_surface = true;
            }
#यदि defined(SDL_VIDEO_OPENGL) && !defined(SDL_VIDEO_DRIVER_VITA)
        } अन्यथा {
            // Desktop OpenGL supports it by default from version 3.0 on.
             PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetIntegerv");
            यदि (glGetIntegervFunc) {
                GLint v = 0;
                glGetIntegervFunc(GL_MAJOR_संस्करणम्, &v);
                यदि (v >= 3) {
                    _this->gl_allow_no_surface = true;
                }
            }
#यदि_अन्तः
        }
    }

    SDL_EGL_समुच्चयः_Swap_Interval(_this, 0);  // EGL tends to default to vsync=1. To make this consistent with the rest of SDL, we force it off at startup. Apps can explicitly enable it afterwards.

    प्रत्यागम (SDL_GLContext)egl_context;
}

bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    यदि (!_this->egl_दत्त->eglMakeCurrent) {
        यदि (!egl_surface && !context) {
            // Can't do the nothing there is to do? Probably trying to cleanup a failed startup, just return.
            प्रत्यागम true;
        } अन्यथा {
            प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized"); // something clearly went wrong somewhere.
        }
    }

    // Make sure current thread has a valid API bound to it.
    यदि (_this->egl_दत्त->eglBindAPI) {
        _this->egl_दत्त->eglBindAPI(_this->egl_दत्त->apitype);
    }

    /* The android emulator crashes badly if you try to eglMakeCurrent
     * with a valid context and invalid surface, so we have to check for both here.
     */
    यदि (!egl_context || (!egl_surface && !_this->gl_allow_no_surface)) {
        _this->egl_दत्त->eglMakeCurrent(_this->egl_दत्त->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    } अन्यथा {
        यदि (!_this->egl_दत्त->eglMakeCurrent(_this->egl_दत्त->egl_display,
                                             egl_surface, egl_surface, egl_context)) {
            प्रत्यागम SDL_EGL_समुच्चयः_Error("Unable to make EGL context current", "eglMakeCurrent");
        }
    }

    प्रत्यागम true;
}

bool SDL_EGL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    EGLBoolean स्थितिः;

    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published:
     * https://github.com/KhronosGroup/EGL-Registry/pull/113
     */
    यदि (interval < 0) {
        प्रत्यागम SDL_समुच्चयः_Error("Late swap tearing currently unsupported");
    }

    स्थितिः = _this->egl_दत्त->eglSwapInterval(_this->egl_दत्त->egl_display, interval);
    यदि (स्थितिः == EGL_TRUE) {
        _this->egl_दत्त->egl_swapinterval = interval;
        प्रत्यागम true;
    }

    प्रत्यागम SDL_EGL_समुच्चयः_Error("Unable to set the EGL swap interval", "eglSwapInterval");
}

bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval)
{
    यदि (!_this->egl_दत्त) {
        प्रत्यागम SDL_समुच्चयः_Error("EGL not initialized");
    }

    *interval = _this->egl_दत्त->egl_swapinterval;
    प्रत्यागम true;
}

bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    यदि (!_this->egl_दत्त->eglSwapBuffers(_this->egl_दत्त->egl_display, egl_surface)) {
        प्रत्यागम SDL_EGL_समुच्चयः_Error("unable to show color buffer in an OS-native window", "eglSwapBuffers");
    }
    प्रत्यागम true;
}

bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    EGLContext egl_context = (EGLContext)context;

    // Clean up GLES and EGL
    यदि (!_this->egl_दत्त) {
        प्रत्यागम true;
    }

    यदि (egl_context != रिक्त && egl_context != EGL_NO_CONTEXT) {
        _this->egl_दत्त->eglDestroyContext(_this->egl_दत्त->egl_display, egl_context);
    }
    प्रत्यागम true;
}

EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, Native_गवाक्षः_Type nw)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
    EGLint format_wanted;
    EGLint format_got;
#यदि_अन्तः
    // max 16 key+value pairs, plus terminator.
    EGLint attribs[33];
    पूर्णाङ्क attr = 0;

    EGLSurface surface;

    यदि (!SDL_EGL_वृणु_Config(_this)) {
        प्रत्यागम EGL_NO_SURFACE;
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
    /* On Android, EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry(). */
    _this->egl_दत्त->eglGetConfigAttrib(_this->egl_दत्त->egl_display,
                                        _this->egl_दत्त->egl_config,
                                        EGL_NATIVE_VISUAL_ID, &format_wanted);

    // Format based on selected egl config.
    ANative_गवाक्षः_समुच्चयः_Buffers_Geometry(nw, 0, 0, format_wanted);
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_QNX
    // Wayland is also a supported platform on QNX, so we need to be specific.
    यदि (SDL_strcmp(_this->name, "qnx") == 0) {
        पूर्णाङ्क format = QNX_वृणु_Format(_this, _this->egl_दत्त->egl_config);

        यदि (screen_समुच्चयः_गवाक्षः_property_iv(nw, SCREEN_PROPERTY_FORMAT, &format) < 0) {
            प्रत्यागम EGL_NO_SURFACE;
        }
    }
#यदि_अन्तः

#यदि_परिभाषितम् EGL_KHR_gl_colorspace
    यदि (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_KHR_gl_colorspace")) {
        ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
        यदि (srgbhint && *srgbhint) {
            यदि (SDL_strcmp(srgbhint, "skip") == 0) {
                // don't set an attribute at all.
            } अन्यथा {
                attribs[attr++] = EGL_GL_COLORSPACE_KHR;
                attribs[attr++] = SDL_GetStringBoolean(srgbhint, false) ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_रैखिकम्_KHR;
            }
        } अन्यथा यदि (_this->gl_config.framebuffer_srgb_capable >= 0) {  // default behavior without the hint.
            attribs[attr++] = EGL_GL_COLORSPACE_KHR;
            attribs[attr++] = _this->gl_config.framebuffer_srgb_capable ? EGL_GL_COLORSPACE_SRGB_KHR : EGL_GL_COLORSPACE_रैखिकम्_KHR;
        }
    }
#यदि_अन्तः

    पूर्णाङ्क opaque_ext_idx = -1;

#यदि_परिभाषितम् EGL_EXT_present_opaque
    यदि (SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_EXT_present_opaque")) {
        opaque_ext_idx = attr;
        bool allow_transparent = false;
        यदि (गवाक्षः && (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT)) {
            allow_transparent = true;
        }
        attribs[attr++] = EGL_PRESENT_OPAQUE_EXT;
        attribs[attr++] = allow_transparent ? EGL_FALSE : EGL_TRUE;
    }
#यदि_अन्तः

    यदि (_this->egl_surfaceattrib_callback) {
        ध्रुव पूर्णाङ्क maxAttribs = SDL_arraysize(attribs);
        EGLint *userAttribs, *userAttribP;
        userAttribs = _this->egl_surfaceattrib_callback(_this->egl_attrib_callback_userdata, _this->egl_दत्त->egl_display, _this->egl_दत्त->egl_config);
        यदि (!userAttribs) {
            _this->gl_config.driver_loaded = 0;
            *_this->gl_config.driver_मार्गः = '\0';
            SDL_समुच्चयः_Error("EGL surface attribute callback returned NULL pointer");
            प्रत्यागम EGL_NO_SURFACE;
        }

        प्रति (userAttribP = userAttribs; *userAttribP != EGL_NONE;) {
            यदि (attr + 3 >= maxAttribs) {
                _this->gl_config.driver_loaded = 0;
                *_this->gl_config.driver_मार्गः = '\0';
                SDL_समुच्चयः_Error("EGL surface attribute callback returned too many attributes");
                प्रत्यागम EGL_NO_SURFACE;
            }
            attribs[attr++] = *userAttribP++;
            attribs[attr++] = *userAttribP++;
        }
        SDL_free(userAttribs);
    }

    attribs[attr++] = EGL_NONE;

    surface = _this->egl_दत्त->egl_Create_गवाक्षः_Surface(_this->egl_दत्त->egl_display, _this->egl_दत्त->egl_config, nw, &attribs[0]);
    यदि (surface == EGL_NO_SURFACE) {
        // we had a report of Nvidia drivers that report EGL_BAD_ATTRIBUTE if you try to
        //  use EGL_PRESENT_OPAQUE_EXT, even when EGL_EXT_present_opaque is reported as available.
        //  If we used it, try a second time without this attribute.
        यदि ((_this->egl_दत्त->eglGetError() == EGL_BAD_ATTRIBUTE) && (opaque_ext_idx >= 0)) {
            SDL_memmove(&attribs[opaque_ext_idx], &attribs[opaque_ext_idx + 2], परिमाण (attribs[0]) * ((attr - opaque_ext_idx) - 2));
            surface = _this->egl_दत्त->egl_Create_गवाक्षः_Surface(_this->egl_दत्त->egl_display, _this->egl_दत्त->egl_config, nw, &attribs[0]);
        }
    }

    यदि (surface == EGL_NO_SURFACE) {
        SDL_EGL_समुच्चयः_Error("unable to create an EGL window surface", "eglCreateWindowSurface");
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
    format_got = ANative_गवाक्षः_get_Format(nw);
    Android_समुच्चयः_Format(format_wanted, format_got);
#यदि_अन्तः

    प्रत्यागम surface;
}

EGLSurface
SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, पूर्णाङ्क विस्तारः, पूर्णाङ्क height)
{
    EGLint गुणाः[] = {
        EGL_विस्तारः, 0,
        EGL_HEIGHT, 0,
        EGL_NONE
    };
    गुणाः[1] = विस्तारः;
    गुणाः[3] = height;

    यदि (!SDL_EGL_वृणु_Config(_this)) {
        प्रत्यागम EGL_NO_SURFACE;
    }

    प्रत्यागम _this->egl_दत्त->eglCreatePbufferSurface(
        _this->egl_दत्त->egl_display,
        _this->egl_दत्त->egl_config,
        गुणाः);
}

शून्य SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface)
{
    यदि (!_this->egl_दत्त) {
        प्रत्यागम;
    }

    यदि (egl_surface != EGL_NO_SURFACE) {
        _this->egl_दत्त->eglDestroySurface(_this->egl_दत्त->egl_display, egl_surface);
    }
}

#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL
