/*
  Simple DirectMedia Layer
  Copyright (C) 2022 Charles Lohr <charlesl@valvesoftware.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#എങ്കിൽ 0
#define DEBUG_OPENVR
#endif

#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../SDL_egl_c.h"
#അന്തര്ഭാവ "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#അന്തര്ഭാവ <SDL3/SDL_opengl.h>
#അല്ലെങ്കിൽ
// Currently only EGL, not OpenGL, is supported on other platforms
#അന്തര്ഭാവ <SDL3/SDL_opengles2.h>
#അന്തര്ഭാവ <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#അന്തര്ഭാവ "../windows/SDL_windowsopengl.h"
#അന്തര്ഭാവ "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

സ്ഥിതം bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
സ്ഥിതം SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ഘടന SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#അല്ലെങ്കിൽ
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#endif

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#define MARKER_ID 0
#define MARKER_STR "vr-marker,frame_end,type,application"

#undef EXTERN_C

// For access to functions that don't get the video data context.
SDL_VideoData * global_openvr_driver;

സ്ഥിതം ശൂന്യം InitializeMouseFunctions(ശൂന്യം);

ഘടന SDL_CursorData
{
    unsigned texture_id_handle;
    പൂർണ്ണസംഖ്യ hot_x, hot_y;
    പൂർണ്ണസംഖ്യ w, h;
};

// GL Extensions for functions we will be using.
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
സ്ഥിതം GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
സ്ഥിതം GLenum (APIENTRY *ov_glGetError)(ശൂന്യം);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glFlush)(ശൂന്യം);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glFinish)(ശൂന്യം);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, സ്ഥിരം ശൂന്യം *data);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glDrawBuffers)(GLsizei n, സ്ഥിരം GLenum *bufs);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
സ്ഥിതം സ്ഥിരം GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glClear)(GLbitfield mask);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
സ്ഥിതം ശൂന്യം (APIENTRY *ov_gl_Debug_Message_തിരുകുക)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, സ്ഥിരം അക്ഷരം *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
സ്ഥിതം PROC (*ov_wglGetProcAddress)(LPCSTR);
സ്ഥിതം HGLRC (*ov_wglCreateContext)(HDC);
സ്ഥിതം BOOL (*ov_wglDeleteContext)(HGLRC);
സ്ഥിതം BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (ശൂന്യം *)SDL_GL_GetProcAddress((#proc)+3); എങ്കിൽ (!proc) { failed_extension = (#proc)+3; } }

സ്ഥിതം bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!ov_glGetError) {
        സ്ഥിരം അക്ഷരം * failed_extension = 0;
        OPENVR_SetupProc(ov_glGenFramebuffers);
        OPENVR_SetupProc(ov_glGenRenderbuffers);
        OPENVR_SetupProc(ov_glBindFramebuffer);
        OPENVR_SetupProc(ov_glBindRenderbuffer);
        OPENVR_SetupProc(ov_glRenderbufferStorage);
        OPENVR_SetupProc(ov_glFramebufferRenderbuffer);
        OPENVR_SetupProc(ov_glFramebufferTexture2D);
        OPENVR_SetupProc(ov_glCheckNamedFramebufferStatus);
        OPENVR_SetupProc(ov_glGetError);
        OPENVR_SetupProc(ov_glFlush);
        OPENVR_SetupProc(ov_glFinish);
        OPENVR_SetupProc(ov_glGenTextures);
        OPENVR_SetupProc(ov_glDeleteTextures);
        OPENVR_SetupProc(ov_glTexParameterf);
        OPENVR_SetupProc(ov_glTexParameteri);
        OPENVR_SetupProc(ov_glTexImage2D);
        OPENVR_SetupProc(ov_glBindTexture);
        OPENVR_SetupProc(ov_glDrawBuffers);
        OPENVR_SetupProc(ov_glClear);
        OPENVR_SetupProc(ov_glClearColor);
        OPENVR_SetupProc(ov_glColorMask);
        OPENVR_SetupProc(ov_glGetStringi);
        OPENVR_SetupProc(ov_glGetIntegerv);
        OPENVR_SetupProc(ov_gl_Debug_Message_തിരുകുക);
        എങ്കിൽ (failed_extension) {
            തിരികെ SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_SetOverlayError(EVROverlayError e)
{
    തിരഞ്ഞെടുപ്പ് (e) {
#define CASE(X) അവസ്ഥ EVROverlayError_VROverlayError_##X: തിരികെ SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(താക്കോൽ_Too_Long);
    CASE(NameTooLong);
    CASE(താക്കോൽ_In_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(UnableToLoadFile);
    CASE(KeyboardAlreadyInUse);
    CASE(NoNeighbor);
    CASE(TooManyMaskPrimitives);
    CASE(BadMaskPrimitive);
    CASE(TextureAlreadyLocked);
    CASE(TextureLockCapacityReached);
    CASE(TextureNotLocked);
    CASE(TimedOut);
#undef CASE
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_SetError("Unknown VROverlayError %d", e);
    }
}

സ്ഥിതം bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

സ്ഥിതം bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    സ്ഥിരം അക്ഷരം * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    സ്ഥിരം അക്ഷരം * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    സ്ഥിരം അക്ഷരം * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    പൂർണ്ണസംഖ്യ width = hintWidth ? SDL_atoi(hintWidth) : 0;
    പൂർണ്ണസംഖ്യ height = hintHeight ? SDL_atoi(hintHeight) : 0;
    പൂർണ്ണസംഖ്യ fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    എങ്കിൽ (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    എങ്കിൽ (fps) {
        display.desktop_mode.refresh_rate = fps;
    } അല്ലെങ്കിൽ {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (അക്ഷരം *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

സ്ഥിതം ശൂന്യം OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    എങ്കിൽ (data) {
        എങ്കിൽ (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    പൂർണ്ണസംഖ്യ w = surf->w;
    പൂർണ്ണസംഖ്യ h = surf->h;
    പൂർണ്ണസംഖ്യ pitch = surf->pitch;
    പൂർണ്ണസംഖ്യ x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    വേണ്ടി(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        വേണ്ടി(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    തിരികെ pxd;
}

സ്ഥിതം bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    എങ്കിൽ (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    എങ്കിൽ (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        ഘടന HmdVector2_t ms;
        പൂർണ്ണസംഖ്യ status;

        എങ്കിൽ (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        status = ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER);
        എങ്കിൽ (status != GL_FRAMEBUFFER_COMPLETE) {
            തിരികെ SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (ദശാംശം)videodata->targw;
        ms.v[1] = (ദശാംശം)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_VirtualControllerRumble(ശൂന്യം *userdata, Uint16 താഴെയുള്ള_frequency_rumble, Uint16 മുകളിലെ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    സ്ഥിരം ദശാംശം k_flIntensity = 320.f; // Maximum frequency
    ദശാംശം fl_ഇടത്_Frequency = (ദശാംശം)താഴെയുള്ള_frequency_rumble * k_flIntensity / 65535.f;
    ദശാംശം fl_വലത്_Frequency = (ദശാംശം)മുകളിലെ_frequency_rumble * k_flIntensity / 65535.f;
    ദശാംശം flDurationSeconds = 2.f;
    ദശാംശം flAmplitude = 1.f;

    videodata->o_നിവേശം->TriggerHapticVibrationAction(videodata->നിവേശം_action_handles_haptics[0], 0, flDurationSeconds, fl_ഇടത്_Frequency, flAmplitude, 0);
    videodata->o_നിവേശം->TriggerHapticVibrationAction(videodata->നിവേശം_action_handles_haptics[1], 0, flDurationSeconds, fl_വലത്_Frequency, flAmplitude, 0);

    തിരികെ true;
}

സ്ഥിതം bool OPENVR_VirtualControllerRumbleTriggers(ശൂന്യം *userdata, Uint16 ഇടത്_rumble, Uint16 വലത്_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_നിവേശം->TriggerHapticVibrationAction(videodata->നിവേശം_action_handles_haptics[0], 0, 0.1f, ഇടത്_rumble, 1.0, 0);
    videodata->o_നിവേശം->TriggerHapticVibrationAction(videodata->നിവേശം_action_handles_haptics[1], 0, 0.1f, വലത്_rumble, 1.0, 0);
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം OPENVR_VirtualControllerUpdate(ശൂന്യം *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    നിവേശം_Digital_Action_Data_t digital_നിവേശം_action;
    നിവേശം_Analog_Action_Data_t analog_നിവേശം_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->നിവേശം_action_set;
    e = videodata->o_നിവേശം->UpdateActionState(&actionSet, വലുപ്പം(actionSet), 1);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        തിരികെ;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ d = 0; d < videodata->നിവേശം_action_handles_buttons_എണ്ണം; d++)
    {
        എങ്കിൽ (videodata->നിവേശം_action_handles_buttons[d] == k_ulInvalidActionHandle)
            തുടരുക;
        e = videodata->o_നിവേശം->GetDigitalActionData(videodata->നിവേശം_action_handles_buttons[d], &digital_നിവേശം_action, വലുപ്പം(digital_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
        എങ്കിൽ (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            തിരികെ;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_നിവേശം_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_നിവേശം->GetAnalogActionData(videodata->നിവേശം_action_handles_axes[0], &analog_നിവേശം_action, വലുപ്പം(analog_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        തിരികെ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_നിവേശം_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_നിവേശം_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_നിവേശം->GetAnalogActionData(videodata->നിവേശം_action_handles_axes[1], &analog_നിവേശം_action, വലുപ്പം(analog_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        തിരികെ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_നിവേശം_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_നിവേശം_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_നിവേശം->GetAnalogActionData(videodata->നിവേശം_action_handles_axes[2], &analog_നിവേശം_action, വലുപ്പം(analog_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        തിരികെ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ഇടത്_TRIGGER, (Sint16)((analog_നിവേശം_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_നിവേശം->GetAnalogActionData(videodata->നിവേശം_action_handles_axes[3], &analog_നിവേശം_action, വലുപ്പം(analog_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        തിരികെ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_വലത്_TRIGGER, (Sint16)((analog_നിവേശം_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#എങ്കിൽ 0
    വേണ്ടി (a = 0; a < videodata->നിവേശം_action_handles_axes_എണ്ണം; a++)
    {
        ദശാംശം xval = 0.0f;
        e = videodata->o_നിവേശം->GetAnalogActionData(videodata->നിവേശം_action_handles_axes[a], &analog_നിവേശം_action, വലുപ്പം(analog_നിവേശം_action), k_ul_Invalid_നിവേശം_മൂല്യം_Handle);
        എങ്കിൽ (e) പോകുക updatefail;
        xval = analog_നിവേശം_action.x;
        എങ്കിൽ (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        എങ്കിൽ (a == SDL_GAMEPAD_AXIS_ഇടത്_TRIGGER || a == SDL_GAMEPAD_AXIS_വലത്_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_SetJoystickVirtualAxis(joystick, a, xval);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#endif
    }
#endif
#ifdef DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#endif
    തിരികെ;
}

സ്ഥിതം bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    അക്ഷരം * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_എണ്ണം] = {
        "/actions/virtualgamepad/in/a",
        "/actions/virtualgamepad/in/b",
        "/actions/virtualgamepad/in/x",
        "/actions/virtualgamepad/in/y",
        "/actions/virtualgamepad/in/back",
        "/actions/virtualgamepad/in/guide",
        "/actions/virtualgamepad/in/start",
        "/actions/virtualgamepad/in/stick_click_left",
        "/actions/virtualgamepad/in/stick_click_right",
        "/actions/virtualgamepad/in/shoulder_left",
        "/actions/virtualgamepad/in/shoulder_right",
        "/actions/virtualgamepad/in/dpad_up",
        "/actions/virtualgamepad/in/dpad_down",
        "/actions/virtualgamepad/in/dpad_left",
        "/actions/virtualgamepad/in/dpad_right",
        "/actions/virtualgamepad/in/misc_1",
        "/actions/virtualgamepad/in/paddle_1",
        "/actions/virtualgamepad/in/paddle_2",
        "/actions/virtualgamepad/in/paddle_3",
        "/actions/virtualgamepad/in/paddle_4",
        "/actions/virtualgamepad/in/touchpad_click",
        "/actions/virtualgamepad/in/misc_2",
        "/actions/virtualgamepad/in/misc_3",
        "/actions/virtualgamepad/in/misc_4",
        "/actions/virtualgamepad/in/misc_5",
        "/actions/virtualgamepad/in/misc_6",
    };
    അക്ഷരം * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    എങ്കിൽ ((e = videodata->o_നിവേശം->GetActionSetHandle("/actions/virtualgamepad", &videodata->നിവേശം_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        തിരികെ SDL_SetError("Failed to get action set handle");
    }

    videodata->നിവേശം_action_handles_buttons_എണ്ണം = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->നിവേശം_action_handles_buttons = SDL_malloc(videodata->നിവേശം_action_handles_buttons_എണ്ണം * വലുപ്പം(VRActionHandle_t));

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->നിവേശം_action_handles_buttons_എണ്ണം; i++)
    {
        e = videodata->o_നിവേശം->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->നിവേശം_action_handles_buttons[i]);
        എങ്കിൽ (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            തിരികെ SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->നിവേശം_action_handles_axes_എണ്ണം = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->നിവേശം_action_handles_axes = SDL_malloc(videodata->നിവേശം_action_handles_axes_എണ്ണം * വലുപ്പം(VRActionHandle_t));

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < videodata->നിവേശം_action_handles_axes_എണ്ണം; i++)
    {
        e = videodata->o_നിവേശം->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->നിവേശം_action_handles_axes[i]);
        എങ്കിൽ (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            തിരികെ SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_നിവേശം->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->നിവേശം_action_handles_haptics[0]);
    e |= videodata->o_നിവേശം->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->നിവേശം_action_handles_haptics[1]);
    എങ്കിൽ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        തിരികെ SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_എണ്ണം;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_എണ്ണം;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    എങ്കിൽ (!virtual_id) {
        തിരികെ SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    എങ്കിൽ (!videodata->virtual_joystick) {
        തിരികെ SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->നിവേശം_action_handles_buttons_എണ്ണം, videodata->നിവേശം_action_handles_axes_എണ്ണം);
#endif

    തിരികെ true;
}

സ്ഥിതം bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    എങ്കിൽ (!OPENVR_InitExtensions(_this)) {
        തിരികെ false;
    }

    // Generate the overlay.
    {
        സ്ഥിരം അക്ഷരം * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        അക്ഷരം * cursorname = 0;
        എങ്കിൽ (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        എങ്കിൽ (!videodata->sOverlayName) {
            തിരികെ false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        എങ്കിൽ (!cursorname) {
            തിരികെ false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        എങ്കിൽ (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            തിരികെ SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        എങ്കിൽ (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            തിരികെ SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_സംഖ്യ, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        സ്ഥിരം അക്ഷരം *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        എങ്കിൽ (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } അല്ലെങ്കിൽ {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#എങ്കിൽ 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < വലുപ്പം(overlay_flags) * 8; ++i) {
            എങ്കിൽ (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        സ്ഥിരം അക്ഷരം * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        ദശാംശം fWidth = hint ? (ദശാംശം)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        സ്ഥിരം അക്ഷരം * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        ദശാംശം fCursorWidth = hint ? (ദശാംശം)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        സ്ഥിരം അക്ഷരം * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        എങ്കിൽ (hint) {
            അക്ഷരം * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            എങ്കിൽ (err == EVROverlayError_VROverlayError_None) {
                videodata->bIconOverridden = SDL_GetHintBoolean("SDL_OPENVR_WINDOW_ICON_OVERRIDE", false);
            }
        }
    }
    {
        VRTextureBounds_t bounds;
        bounds.uMin = 0;
        bounds.uMax = 1;
        bounds.vMin = 0;
        bounds.vMax = 1;
        videodata->oOverlay->SetOverlayTextureBounds(videodata->overlayID, &bounds);
    }

    എങ്കിൽ (!OPENVR_CheckRenderbuffer(_this)) {
        തിരികെ false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    തിരികെ true;
}


സ്ഥിതം bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    സ്ഥിതം സ്ഥിരം GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        പൂർണ്ണസംഖ്യ error = ov_glGetError();
        എങ്കിൽ (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    എങ്കിൽ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    തിരികെ true;
}

സ്ഥിതം bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    എങ്കിൽ (!ov_glGetError) {
        തിരികെ true;
    }

    എങ്കിൽ (!videodata->is_buffer_rendering) {
        തിരികെ true;
    }

#ifdef DEBUG_OPENVR
    {
        പൂർണ്ണസംഖ്യ error = ov_glGetError();
        എങ്കിൽ (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    എങ്കിൽ (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ഘടന Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (ശൂന്യം *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    എങ്കിൽ (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    എങ്കിൽ (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_തിരുകുക(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    തിരികെ OPENVR_CheckRenderbuffer(_this);
}

സ്ഥിതം ശൂന്യം OPENVR_HandleResize(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

സ്ഥിതം bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    തിരികെ true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
സ്ഥിതം LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT സന്ദേശം, WPARAM wParam, LPARAM lParam)
{
    തിരഞ്ഞെടുപ്പ് (സന്ദേശം) {
    അവസ്ഥ WM_DESTROY:
        തിരികെ 0;
    }
    തിരികെ DefWindowProc(hwnd, സന്ദേശം, wParam, lParam);
}

സ്ഥിതം bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    എങ്കിൽ (path == ശൂന്യ) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    എങ്കിൽ (path == ശൂന്യ) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    എങ്കിൽ (!_this->gl_config.dll_handle) {
        തിരികെ false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (ഘടന SDL_GLDriverData *)SDL_calloc(1, വലുപ്പം(ഘടന SDL_GLDriverData));
    എങ്കിൽ (!_this->gl_data) {
        തിരികെ false;
    }
    _this->gl_config.driver_loaded = true;

    തിരികെ true;
}

സ്ഥിതം SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    SDL_FunctionPointer result = ശൂന്യ;
    എങ്കിൽ (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        എങ്കിൽ (result) {
            തിരികെ result;
        }
    }

    തിരികെ SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

സ്ഥിതം ശൂന്യം OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

സ്ഥിതം SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint അക്കം_Extensions;
    പൂർണ്ണസംഖ്യ i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ശൂന്യ);
        wnd.hIcon = LoadIcon(ശൂന്യ, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(ശൂന്യ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ശൂന്യ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ശൂന്യ, ശൂന്യ, GetModuleHandle(ശൂന്യ), ശൂന്യ);

        സന്ദേശം_2 സന്ദേശം;
        ആകുമ്പോൾ (PeekMessage(&സന്ദേശം, ശൂന്യ, 0, 0, PM_REMOVE)) {
            TranslateMessage(&സന്ദേശം);
            DispatchMessage(&സന്ദേശം);
        }

        videodata->hdc = GetDC(hwnd);

        സ്ഥിതം  PIXELFORMATDESCRIPTOR pfd =
        {
            വലുപ്പം(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL |
            PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            24,
            8, 0, 8, 8, 8, 16,
            8,
            24,
            32,
            8, 8, 8, 8,
            16,
            0,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };
        GLuint PixelFormat = ChoosePixelFormat(videodata->hdc, &pfd);
        എങ്കിൽ (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            തിരികെ ശൂന്യ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        എങ്കിൽ (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            തിരികെ ശൂന്യ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        എങ്കിൽ (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            തിരികെ ശൂന്യ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        എങ്കിൽ (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            തിരികെ ശൂന്യ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    എങ്കിൽ (i == 0) {
        തിരികെ ശൂന്യ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_അക്കം_EXTENSIONS, &അക്കം_Extensions);
    വേണ്ടി (i = 0; i < അക്കം_Extensions; i++) {
        സ്ഥിരം അക്ഷരം *ccc = (സ്ഥിരം അക്ഷരം *)ov_glGetStringi(GL_EXTENSIONS, i);
        എങ്കിൽ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    എങ്കിൽ (!videodata->bDidCreateOverlay) {
        എങ്കിൽ (!OPENVR_InitializeOverlay(_this, window)) {
            തിരികെ ശൂന്യ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(വലുപ്പം(ഘടന SDL_GLContextState));
    എങ്കിൽ (!result) {
        തിരികെ ശൂന്യ;
    }
    result->hglrc = videodata->hglrc;
    തിരികെ result;
}

സ്ഥിതം bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (swapInterval)
        *swapInterval = videodata->swap_interval;
    അല്ലെങ്കിൽ
        തിരികെ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, ശൂന്യ);
    ov_wglDeleteContext(videodata->hglrc);
    തിരികെ true;
}


#അല്ലെങ്കിൽ

സ്ഥിതം EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

സ്ഥിതം bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ശൂന്യ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    എങ്കിൽ (vd->eglDpy == 0) {
        തിരികെ SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    എങ്കിൽ (!b) {
        തിരികെ SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        പൂർണ്ണസംഖ്യ err = eglGetError();
        എങ്കിൽ (err != EGL_SUCCESS) {
            തിരികെ SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    എങ്കിൽ (!vd->eglCtx) {
        തിരികെ SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    തിരികെ true;
}

// Linux, EGL, etc.
സ്ഥിതം bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path)
{
    തിരികെ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

സ്ഥിതം SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc)
{
    തിരികെ SDL_EGL_GetProcAddress(proc);
}
സ്ഥിതം ശൂന്യം OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
സ്ഥിതം SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint അക്കം_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (!videodata->eglCtx) {
        എങ്കിൽ (!SDL_EGL_InitInternal(videodata)) {
            തിരികെ ശൂന്യ;
        }
    }

    എങ്കിൽ (!OPENVR_InitExtensions(_this)) {
        തിരികെ ശൂന്യ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_അക്കം_EXTENSIONS, &അക്കം_Extensions);
    വേണ്ടി(പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_Extensions; i++) {
        സ്ഥിരം അക്ഷരം * ccc = (സ്ഥിരം അക്ഷരം *)ov_glGetStringi(GL_EXTENSIONS, i);
        എങ്കിൽ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    എങ്കിൽ (!videodata->bDidCreateOverlay) {
        എങ്കിൽ (!OPENVR_InitializeOverlay(_this, window)) {
            തിരികെ ശൂന്യ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    തിരികെ videodata->eglCtx;
}

സ്ഥിതം bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    തിരികെ true;
}

സ്ഥിതം bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    തിരികെ true;
}

സ്ഥിതം bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (swapInterval)
        *swapInterval = videodata->swap_interval;
    അല്ലെങ്കിൽ
        തിരികെ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    തിരികെ true;
}

സ്ഥിതം bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    തിരികെ true;
}

#endif

സ്ഥിതം bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(SDL_WindowData));
    എങ്കിൽ (data == ശൂന്യ) {
        തിരികെ SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    തിരികെ true;
}


സ്ഥിതം ശൂന്യം OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = ശൂന്യ;
}

സ്ഥിതം ശൂന്യം OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

സ്ഥിതം ശൂന്യം OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    എങ്കിൽ (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    എങ്കിൽ (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    എങ്കിൽ (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

സ്ഥിതം ശൂന്യം OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

സ്ഥിതം ശൂന്യം OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_നിവേശം_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

സ്ഥിതം ശൂന്യം OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    തിരികെ;
}

സ്ഥിതം bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    എങ്കിൽ (!videodata->bDidCreateOverlay) {
        എങ്കിൽ (!OPENVR_InitializeOverlay(_this, window)) {
            തിരികെ false;
        }
    }

    എങ്കിൽ (!OPENVR_ReleaseFrame(_this)) {
        തിരികെ false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    എങ്കിൽ (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    എങ്കിൽ (!OPENVR_SetupFrame(_this, window)) {
        തിരികെ false;
    }

    തിരികെ true;
}

സ്ഥിതം Uint8 OPENVR_MapMouseButton(പൂർണ്ണസംഖ്യ btn)
{
    എങ്കിൽ (btn == EVRMouse_Button_VRMouse_Button_വലത്) {
        തിരികെ SDL_BUTTON_വലത്;
    } അല്ലെങ്കിൽ എങ്കിൽ (btn == EVRMouse_Button_VRMouse_Button_നടുവ്) {
        തിരികെ SDL_BUTTON_നടുവ്;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_BUTTON_ഇടത്;
    }
}

സ്ഥിതം ശൂന്യം OPENVR_HandleMouse(ദശാംശം x, ദശാംശം y, പൂർണ്ണസംഖ്യ btn, പൂർണ്ണസംഖ്യ evt)
{
    എങ്കിൽ (evt == 2) {
        SDL_SendMouseMotion(0, ശൂന്യ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം Uint8 button = OPENVR_MapMouseButton(btn);
        സ്ഥിരം bool down = (evt != 0);
        SDL_SendMouseButton(0, ശൂന്യ, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


സ്ഥിതം bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        തിരികെ;
    }
    EGamepad_Text_നിവേശം_Mode നിവേശം_mode;
    തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_HIDDEN:
        നിവേശം_mode = EGamepad_Text_നിവേശം_Mode_k_EGamepad_Text_നിവേശം_Mode_Password;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിവേശം_mode = EGamepad_Text_നിവേശം_Mode_k_EGamepad_Text_നിവേശം_Mode_Normal;
        നിർത്തുക;
    }
    EGamepad_Text_നിവേശം_വരി_Mode വരി_mode;
    എങ്കിൽ (SDL_Get_Text_നിവേശം_Multiline(props)) {
        വരി_mode = EGamepad_Text_നിവേശം_വരി_Mode_k_EGamepad_Text_നിവേശം_വരി_Mode_Multiple_വരികൾ;
    } അല്ലെങ്കിൽ {
        വരി_mode = EGamepad_Text_നിവേശം_വരി_Mode_k_EGamepad_Text_നിവേശം_വരി_Mode_Single_വരി;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           നിവേശം_mode, വരി_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

സ്ഥിതം ശൂന്യം OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

സ്ഥിതം SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, വലുപ്പം(SDL_Cursor));
    എങ്കിൽ (!result) {
        തിരികെ ശൂന്യ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*ovrc));
    എങ്കിൽ (!ovrc) {
        SDL_free(result);
        തിരികെ ശൂന്യ;
    }
    result->internal = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    തിരികെ result;
}

സ്ഥിതം bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    എങ്കിൽ (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
            തിരികെ OPENVR_SetOverlayError(e);
        }
        തിരികെ true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    എങ്കിൽ (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        തിരികെ true;
    }

    hotspot.v[0] = (ദശാംശം)ovrc->hot_x / (ദശാംശം)ovrc->w;
    hotspot.v[1] = (ദശാംശം)ovrc->hot_y / (ദശാംശം)ovrc->h;

    texture.handle = (ശൂന്യം *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
        തിരികെ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
        തിരികെ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
        തിരികെ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
        തിരികെ OPENVR_SetOverlayError(e);
    }

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    എങ്കിൽ (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        എങ്കിൽ (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


സ്ഥിതം bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    എങ്കിൽ (!global_openvr_driver) {
        തിരികെ SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    എങ്കിൽ (videodata->bIconOverridden) {
        തിരികെ SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (ശൂന്യം *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    എങ്കിൽ (e != EVROverlayError_VROverlayError_None) {
        തിരികെ OPENVR_SetOverlayError(e);
    }
    തിരികെ true;
}

സ്ഥിതം bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    അക്ഷരം empty = 0;
    അക്ഷരം * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    അക്ഷരം * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    അക്ഷരം * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം InitializeMouseFunctions(ശൂന്യം)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

സ്ഥിതം ശൂന്യം OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ഘടന VREvent_t nEvent;
    എങ്കിൽ (videodata->overlayID) {
        ആകുമ്പോൾ (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, വലുപ്പം(nEvent))) {
            തിരഞ്ഞെടുപ്പ് (nEvent.eventType) {
            അവസ്ഥ EVREventType_VREvent_ButtonPress:
            അവസ്ഥ EVREventType_VREvent_ButtonUnpress:
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_ScrollSmooth:
            അവസ്ഥ EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ശൂന്യ, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                നിർത്തുക;
            അവസ്ഥ EVREvent_Type_VREvent_Keyboard_Char_നിവേശം:
                SDL_Send_Keyboard_Unicode_താക്കോൽ(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_നിവേശം[0]);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(ശൂന്യ);
                നിർത്തുക;
            അവസ്ഥ EVREventType_VREvent_OverlayClosed:
            അവസ്ഥ EVREventType_VREvent_Quit:
                SDL_SendQuit();
                നിർത്തുക;
            }
        }
    }
}


സ്ഥിതം SDL_VideoDevice *OPENVR_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    സ്ഥിരം അക്ഷരം *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(ശൂന്യ, 0, ശൂന്യ);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (device) {
        data = (ഘടന SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    } അല്ലെങ്കിൽ {
        data = ശൂന്യ;
    }
    എങ്കിൽ (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        തിരികെ ശൂന്യ;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    എങ്കിൽ (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    എങ്കിൽ (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    എങ്കിൽ (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        പോകുക error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (സ്ഥിരം അക്ഷരം *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(സ്ഥിരം അക്ഷരം *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    എങ്കിൽ (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        പോകുക error;
    }

    അക്ഷരം fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    എങ്കിൽ (!data->vrtoken) {
        സ്ഥിരം അക്ഷരം *err = "Can't get english description";
        എങ്കിൽ (data->FN_VR_GetVRInitErrorAsEnglishDescription != ശൂന്യ)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        പോകുക error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (ഘടന VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (ഘടന VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_നിവേശം = (ഘടന VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    എങ്കിൽ (!data->oOverlay || !data->oSystem || !data->o_നിവേശം) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    അക്ഷരം *loadpath = 0;
    EVRInputError err;

    എങ്കിൽ (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം അക്ഷരം *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    എങ്കിൽ (!loadpath) {
        പോകുക error;
    }

    err = data->o_നിവേശം->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    എങ്കിൽ (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        എങ്കിൽ (hint) {
            പോകുക error;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            പോകുക error;
        }
    }

    // Setup amount of available displays
    device->അക്കം_displays = 0;

    // Set device free function
    device->സ്വതന്ത്രം = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->SetDisplayMode = OPENVR_SetDisplayMode;
    device->CreateSDLWindow = OPENVR_CreateWindow;
    device->SetWindowTitle = OPENVR_SetWindowTitle;
    device->SetWindowSize = OPENVR_SetWindowSize;
    device->GetWindowSizeInPixels = OPENVR_GetWindowSizeInPixels;
    device->ShowWindow = OPENVR_ShowWindow;
    device->HideWindow = OPENVR_HideWindow;
    device->DestroyWindow = OPENVR_DestroyWindow;
    device->ShowMessageBox = OPENVR_ShowMessageBox;

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ifdef SDL_VIDEO_OPENGL_WGL
    device->GL_LoadLibrary = OPENVR_GL_LoadLibrary;
    device->GL_GetProcAddress = OPENVR_GL_GetProcAddress;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_SetSwapInterval = OPENVR_GL_SetSwapInterval;
    device->GL_GetSwapInterval = OPENVR_GL_GetSwapInterval;
    device->GL_SwapWindow = OPENVR_GL_SwapWindow;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#അല്ലെങ്കിൽ
#error Needs more work to support EGL
#endif
#അല്ലെങ്കിൽ
    device->GL_LoadLibrary = OVR_EGL_LoadLibrary;
    device->GL_GetProcAddress = OVR_EGL_GetProcAddress;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_SetSwapInterval = OVR_EGL_SetSwapInterval;
    device->GL_GetSwapInterval = OVR_EGL_GetSwapInterval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_SwapWindow = OPENVR_GL_SwapWindow;
#endif

#എങ്കിൽ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#അല്ലെങ്കിൽ
    device->Vulkan_LoadLibrary = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#endif

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->SetWindowIcon = OPENVR_SetWindowIcon;

    തിരികെ device;

error:
    OPENVR_Destroy(device);
    തിരികെ ശൂന്യ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ശൂന്യ, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

