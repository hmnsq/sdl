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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#ಯದಿ 0
#define DEBUG_OPENVR
#endif

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಅನ್ಯಥಾ
// Currently only EGL, not OpenGL, is supported on other platforms
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2.h>
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ಅನ್ತರ್ಭಾವ "../windows/SDL_windowsopengl.h"
#ಅನ್ತರ್ಭಾವ "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

ಸ್ಥಿರ bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಸ್ಥಿರ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ಸಂರಚನಾ SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#ಅನ್ಯಥಾ
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

ಸ್ಥಿರ ಶೂನ್ಯ InitializeMouseFunctions(ಶೂನ್ಯ);

ಸಂರಚನಾ SDL_CursorData
{
    unsigned texture_id_handle;
    ಪೂರ್ಣಾಙ್ಕ hot_x, hot_y;
    ಪೂರ್ಣಾಙ್ಕ w, h;
};

// GL Extensions for functions we will be using.
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ಸ್ಥಿರ GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
ಸ್ಥಿರ GLenum (APIENTRY *ov_glGetError)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFlush)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFinish)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ಧ್ರುವ ಶೂನ್ಯ *data);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ಧ್ರುವ GLenum *bufs);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
ಸ್ಥಿರ ಧ್ರುವ GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glClear)(GLbitfield mask);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_gl_Debug_Message_ಸೇರಿಸು)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ಧ್ರುವ ವರ್ಣ *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
ಸ್ಥಿರ PROC (*ov_wglGetProcAddress)(LPCSTR);
ಸ್ಥಿರ HGLRC (*ov_wglCreateContext)(HDC);
ಸ್ಥಿರ BOOL (*ov_wglDeleteContext)(HGLRC);
ಸ್ಥಿರ BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (ಶೂನ್ಯ *)SDL_GL_GetProcAddress((#proc)+3); ಯದಿ (!proc) { failed_extension = (#proc)+3; } }

ಸ್ಥಿರ bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    ಯದಿ (!ov_glGetError) {
        ಧ್ರುವ ವರ್ಣ * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_ಸೇರಿಸು);
        ಯದಿ (failed_extension) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_SetOverlayError(EVROverlayError e)
{
    ವಿಕಲ್ಪ (e) {
#define CASE(X) ಪಕ್ಷ EVROverlayError_VROverlayError_##X: ಪ್ರತ್ಯಾಗಮ SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(ಕೀಲಿ_Too_Long);
    CASE(NameTooLong);
    CASE(ಕೀಲಿ_In_Use);
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
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unknown VROverlayError %d", e);
    }
}

ಸ್ಥಿರ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

ಸ್ಥಿರ bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ಧ್ರುವ ವರ್ಣ * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ಧ್ರುವ ವರ್ಣ * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ಧ್ರುವ ವರ್ಣ * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    ಪೂರ್ಣಾಙ್ಕ width = hintWidth ? SDL_atoi(hintWidth) : 0;
    ಪೂರ್ಣಾಙ್ಕ height = hintHeight ? SDL_atoi(hintHeight) : 0;
    ಪೂರ್ಣಾಙ್ಕ fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    ಯದಿ (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    ಯದಿ (fps) {
        display.desktop_mode.refresh_rate = fps;
    } ಅನ್ಯಥಾ {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (ವರ್ಣ *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    ಯದಿ (data) {
        ಯದಿ (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    ಪೂರ್ಣಾಙ್ಕ w = surf->w;
    ಪೂರ್ಣಾಙ್ಕ h = surf->h;
    ಪೂರ್ಣಾಙ್ಕ pitch = surf->pitch;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    ಪ್ರತಿ(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        ಪ್ರತಿ(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    ಪ್ರತ್ಯಾಗಮ pxd;
}

ಸ್ಥಿರ bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    ಯದಿ (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    ಯದಿ (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        ಸಂರಚನಾ HmdVector2_t ms;
        ಪೂರ್ಣಾಙ್ಕ status;

        ಯದಿ (videodata->fbo <= 0) {
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
        ಯದಿ (status != GL_FRAMEBUFFER_COMPLETE) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (ಭಿನ್ನ)videodata->targw;
        ms.v[1] = (ಭಿನ್ನ)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_VirtualControllerRumble(ಶೂನ್ಯ *userdata, Uint16 ಕೆಳಗಿನ_frequency_rumble, Uint16 ಮೇಲಿನ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    ಧ್ರುವ ಭಿನ್ನ k_flIntensity = 320.f; // Maximum frequency
    ಭಿನ್ನ fl_ಎಡ_Frequency = (ಭಿನ್ನ)ಕೆಳಗಿನ_frequency_rumble * k_flIntensity / 65535.f;
    ಭಿನ್ನ fl_ಬಲ_Frequency = (ಭಿನ್ನ)ಮೇಲಿನ_frequency_rumble * k_flIntensity / 65535.f;
    ಭಿನ್ನ flDurationSeconds = 2.f;
    ಭಿನ್ನ flAmplitude = 1.f;

    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[0], 0, flDurationSeconds, fl_ಎಡ_Frequency, flAmplitude, 0);
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[1], 0, flDurationSeconds, fl_ಬಲ_Frequency, flAmplitude, 0);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_VirtualControllerRumbleTriggers(ಶೂನ್ಯ *userdata, Uint16 ಎಡ_rumble, Uint16 ಬಲ_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[0], 0, 0.1f, ಎಡ_rumble, 1.0, 0);
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[1], 0, 0.1f, ಬಲ_rumble, 1.0, 0);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_VirtualControllerUpdate(ಶೂನ್ಯ *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ಒಳಹರಿವು_Digital_Action_Data_t digital_ಒಳಹರಿವು_action;
    ಒಳಹರಿವು_Analog_Action_Data_t analog_ಒಳಹರಿವು_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->ಒಳಹರಿವು_action_set;
    e = videodata->o_ಒಳಹರಿವು->UpdateActionState(&actionSet, ಪರಿಮಾಣ(actionSet), 1);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ d = 0; d < videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ; d++)
    {
        ಯದಿ (videodata->ಒಳಹರಿವು_action_handles_buttons[d] == k_ulInvalidActionHandle)
            ಅನುವರ್ತ;
        e = videodata->o_ಒಳಹರಿವು->GetDigitalActionData(videodata->ಒಳಹರಿವು_action_handles_buttons[d], &digital_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(digital_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
        ಯದಿ (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            ಪ್ರತ್ಯಾಗಮ;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_ಒಳಹರಿವು_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_ಒಳಹರಿವು->GetAnalogActionData(videodata->ಒಳಹರಿವು_action_handles_axes[0], &analog_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        ಪ್ರತ್ಯಾಗಮ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ಒಳಹರಿವು_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ಒಳಹರಿವು_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ಒಳಹರಿವು->GetAnalogActionData(videodata->ಒಳಹರಿವು_action_handles_axes[1], &analog_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        ಪ್ರತ್ಯಾಗಮ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ಒಳಹರಿವು_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ಒಳಹರಿವು_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ಒಳಹರಿವು->GetAnalogActionData(videodata->ಒಳಹರಿವು_action_handles_axes[2], &analog_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        ಪ್ರತ್ಯಾಗಮ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ಎಡ_TRIGGER, (Sint16)((analog_ಒಳಹರಿವು_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ಒಳಹರಿವು->GetAnalogActionData(videodata->ಒಳಹರಿವು_action_handles_axes[3], &analog_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        ಪ್ರತ್ಯಾಗಮ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ಬಲ_TRIGGER, (Sint16)((analog_ಒಳಹರಿವು_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#ಯದಿ 0
    ಪ್ರತಿ (a = 0; a < videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ; a++)
    {
        ಭಿನ್ನ xval = 0.0f;
        e = videodata->o_ಒಳಹರಿವು->GetAnalogActionData(videodata->ಒಳಹರಿವು_action_handles_axes[a], &analog_ಒಳಹರಿವು_action, ಪರಿಮಾಣ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
        ಯದಿ (e) ಗಚ್ಛ updatefail;
        xval = analog_ಒಳಹರಿವು_action.x;
        ಯದಿ (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        ಯದಿ (a == SDL_GAMEPAD_AXIS_ಎಡ_TRIGGER || a == SDL_GAMEPAD_AXIS_ಬಲ_TRIGGER)
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
    ಪ್ರತ್ಯಾಗಮ;
}

ಸ್ಥಿರ bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    ವರ್ಣ * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_ಎಣಿಕೆ] = {
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
    ವರ್ಣ * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    ಯದಿ ((e = videodata->o_ಒಳಹರಿವು->GetActionSetHandle("/actions/virtualgamepad", &videodata->ಒಳಹರಿವು_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Failed to get action set handle");
    }

    videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ಒಳಹರಿವು_action_handles_buttons = SDL_malloc(videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ * ಪರಿಮಾಣ(VRActionHandle_t));

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ; i++)
    {
        e = videodata->o_ಒಳಹರಿವು->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ಒಳಹರಿವು_action_handles_buttons[i]);
        ಯದಿ (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ಒಳಹರಿವು_action_handles_axes = SDL_malloc(videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ * ಪರಿಮಾಣ(VRActionHandle_t));

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ; i++)
    {
        e = videodata->o_ಒಳಹರಿವು->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ಒಳಹರಿವು_action_handles_axes[i]);
        ಯದಿ (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ಒಳಹರಿವು->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ಒಳಹರಿವು_action_handles_haptics[0]);
    e |= videodata->o_ಒಳಹರಿವು->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ಒಳಹರಿವು_action_handles_haptics[1]);
    ಯದಿ (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_ಎಣಿಕೆ;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_ಎಣಿಕೆ;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    ಯದಿ (!virtual_id) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    ಯದಿ (!videodata->virtual_joystick) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ, videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ);
#endif

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    ಯದಿ (!OPENVR_InitExtensions(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Generate the overlay.
    {
        ಧ್ರುವ ವರ್ಣ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        ವರ್ಣ * cursorname = 0;
        ಯದಿ (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        ಯದಿ (!videodata->sOverlayName) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        ಯದಿ (!cursorname) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        ಯದಿ (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        ಯದಿ (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_ಸಂಖ್ಯೆ, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        ಯದಿ (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } ಅನ್ಯಥಾ {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#ಯದಿ 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಪರಿಮಾಣ(overlay_flags) * 8; ++i) {
            ಯದಿ (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ಧ್ರುವ ವರ್ಣ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        ಭಿನ್ನ fWidth = hint ? (ಭಿನ್ನ)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ಧ್ರುವ ವರ್ಣ * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        ಭಿನ್ನ fCursorWidth = hint ? (ಭಿನ್ನ)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ಧ್ರುವ ವರ್ಣ * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        ಯದಿ (hint) {
            ವರ್ಣ * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            ಯದಿ (err == EVROverlayError_VROverlayError_None) {
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

    ಯದಿ (!OPENVR_CheckRenderbuffer(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    ಪ್ರತ್ಯಾಗಮ true;
}


ಸ್ಥಿರ bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಸ್ಥಿರ ಧ್ರುವ GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಙ್ಕ error = ov_glGetError();
        ಯದಿ (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    ಯದಿ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    ಯದಿ (!ov_glGetError) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!videodata->is_buffer_rendering) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

#ifdef DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಙ್ಕ error = ov_glGetError();
        ಯದಿ (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ಯದಿ (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ಸಂರಚನಾ Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (ಶೂನ್ಯ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    ಯದಿ (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    ಯದಿ (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_ಸೇರಿಸು(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    ಪ್ರತ್ಯಾಗಮ OPENVR_CheckRenderbuffer(_this);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HandleResize(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

ಸ್ಥಿರ bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ಪ್ರತ್ಯಾಗಮ true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
ಸ್ಥಿರ LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT ಸಂದೇಶ, WPARAM wParam, LPARAM lParam)
{
    ವಿಕಲ್ಪ (ಸಂದೇಶ) {
    ಪಕ್ಷ WM_DESTROY:
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ DefWindowProc(hwnd, ಸಂದೇಶ, wParam, lParam);
}

ಸ್ಥಿರ bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    ಯದಿ (path == ರಿಕ್ತ) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    ಯದಿ (path == ರಿಕ್ತ) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    ಯದಿ (!_this->gl_config.dll_handle) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (ಸಂರಚನಾ SDL_GLDriverData *)SDL_calloc(1, ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_GLDriverData));
    ಯದಿ (!_this->gl_data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    _this->gl_config.driver_loaded = true;

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc)
{
    SDL_FunctionPointer result = ರಿಕ್ತ;
    ಯದಿ (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        ಯದಿ (result) {
            ಪ್ರತ್ಯಾಗಮ result;
        }
    }

    ಪ್ರತ್ಯಾಗಮ SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ಸ್ಥಿರ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint ಅಂಕೆ_Extensions;
    ಪೂರ್ಣಾಙ್ಕ i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ರಿಕ್ತ);
        wnd.hIcon = LoadIcon(ರಿಕ್ತ, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(ರಿಕ್ತ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ರಿಕ್ತ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ರಿಕ್ತ, ರಿಕ್ತ, GetModuleHandle(ರಿಕ್ತ), ರಿಕ್ತ);

        ಸಂದೇಶ_2 ಸಂದೇಶ;
        ಯಾವತ್ (PeekMessage(&ಸಂದೇಶ, ರಿಕ್ತ, 0, 0, PM_REMOVE)) {
            TranslateMessage(&ಸಂದೇಶ);
            DispatchMessage(&ಸಂದೇಶ);
        }

        videodata->hdc = GetDC(hwnd);

        ಸ್ಥಿರ  PIXELFORMATDESCRIPTOR pfd =
        {
            ಪರಿಮಾಣ(PIXELFORMATDESCRIPTOR),
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
        ಯದಿ (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        ಯದಿ (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        ಯದಿ (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        ಯದಿ (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    ಯದಿ (i == 0) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_Extensions);
    ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_Extensions; i++) {
        ಧ್ರುವ ವರ್ಣ *ccc = (ಧ್ರುವ ವರ್ಣ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ಯದಿ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    ಯದಿ (!videodata->bDidCreateOverlay) {
        ಯದಿ (!OPENVR_InitializeOverlay(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_GLContextState));
    ಯದಿ (!result) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    result->hglrc = videodata->hglrc;
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (swapInterval)
        *swapInterval = videodata->swap_interval;
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, ರಿಕ್ತ);
    ov_wglDeleteContext(videodata->hglrc);
    ಪ್ರತ್ಯಾಗಮ true;
}


#ಅನ್ಯಥಾ

ಸ್ಥಿರ EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

ಸ್ಥಿರ bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ರಿಕ್ತ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    ಯದಿ (vd->eglDpy == 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    ಯದಿ (!b) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಙ್ಕ err = eglGetError();
        ಯದಿ (err != EGL_SUCCESS) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    ಯದಿ (!vd->eglCtx) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    ಪ್ರತ್ಯಾಗಮ true;
}

// Linux, EGL, etc.
ಸ್ಥಿರ bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path)
{
    ಪ್ರತ್ಯಾಗಮ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

ಸ್ಥಿರ SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc)
{
    ಪ್ರತ್ಯಾಗಮ SDL_EGL_GetProcAddress(proc);
}
ಸ್ಥಿರ ಶೂನ್ಯ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ಸ್ಥಿರ SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint ಅಂಕೆ_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (!videodata->eglCtx) {
        ಯದಿ (!SDL_EGL_InitInternal(videodata)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಯದಿ (!OPENVR_InitExtensions(_this)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_Extensions);
    ಪ್ರತಿ(ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_Extensions; i++) {
        ಧ್ರುವ ವರ್ಣ * ccc = (ಧ್ರುವ ವರ್ಣ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ಯದಿ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    ಯದಿ (!videodata->bDidCreateOverlay) {
        ಯದಿ (!OPENVR_InitializeOverlay(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    ಪ್ರತ್ಯಾಗಮ videodata->eglCtx;
}

ಸ್ಥಿರ bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (swapInterval)
        *swapInterval = videodata->swap_interval;
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#endif

ಸ್ಥಿರ bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_WindowData));
    ಯದಿ (data == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    ಪ್ರತ್ಯಾಗಮ true;
}


ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    ಯದಿ (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ಯದಿ (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    ಯದಿ (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    ಯದಿ (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    ಯದಿ (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_ಒಳಹರಿವು_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ;
}

ಸ್ಥಿರ bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    ಯದಿ (!videodata->bDidCreateOverlay) {
        ಯದಿ (!OPENVR_InitializeOverlay(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಯದಿ (!OPENVR_ReleaseFrame(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    ಯದಿ (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    ಯದಿ (!OPENVR_SetupFrame(_this, window)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ Uint8 OPENVR_MapMouseButton(ಪೂರ್ಣಾಙ್ಕ btn)
{
    ಯದಿ (btn == EVRMouse_Button_VRMouse_Button_ಬಲ) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಬಲ;
    } ಅನ್ಯಥಾ ಯದಿ (btn == EVRMouse_Button_VRMouse_Button_ಮಧ್ಯ) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಮಧ್ಯ;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಎಡ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HandleMouse(ಭಿನ್ನ x, ಭಿನ್ನ y, ಪೂರ್ಣಾಙ್ಕ btn, ಪೂರ್ಣಾಙ್ಕ evt)
{
    ಯದಿ (evt == 2) {
        SDL_SendMouseMotion(0, ರಿಕ್ತ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ Uint8 button = OPENVR_MapMouseButton(btn);
        ಧ್ರುವ bool down = (evt != 0);
        SDL_SendMouseButton(0, ರಿಕ್ತ, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


ಸ್ಥಿರ bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    EGamepad_Text_ಒಳಹರಿವು_Mode ಒಳಹರಿವು_mode;
    ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        ಒಳಹರಿವು_mode = EGamepad_Text_ಒಳಹರಿವು_Mode_k_EGamepad_Text_ಒಳಹರಿವು_Mode_Password;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಒಳಹರಿವು_mode = EGamepad_Text_ಒಳಹರಿವು_Mode_k_EGamepad_Text_ಒಳಹರಿವು_Mode_Normal;
        ಭಙ್ಗ;
    }
    EGamepad_Text_ಒಳಹರಿವು_ಸಾಲು_Mode ಸಾಲು_mode;
    ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Multiline(props)) {
        ಸಾಲು_mode = EGamepad_Text_ಒಳಹರಿವು_ಸಾಲು_Mode_k_EGamepad_Text_ಒಳಹರಿವು_ಸಾಲು_Mode_Multiple_ಸಾಲುಗಳು;
    } ಅನ್ಯಥಾ {
        ಸಾಲು_mode = EGamepad_Text_ಒಳಹರಿವು_ಸಾಲು_Mode_k_EGamepad_Text_ಒಳಹರಿವು_ಸಾಲು_Mode_Single_ಸಾಲು;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ಒಳಹರಿವು_mode, ಸಾಲು_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ಸ್ಥಿರ SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, ಪರಿಮಾಣ(SDL_Cursor));
    ಯದಿ (!result) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*ovrc));
    ಯದಿ (!ovrc) {
        SDL_free(result);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
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

    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    ಯದಿ (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        ಯದಿ (e != EVROverlayError_VROverlayError_None) {
            ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    ಯದಿ (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        ಪ್ರತ್ಯಾಗಮ true;
    }

    hotspot.v[0] = (ಭಿನ್ನ)ovrc->hot_x / (ಭಿನ್ನ)ovrc->w;
    hotspot.v[1] = (ಭಿನ್ನ)ovrc->hot_y / (ಭಿನ್ನ)ovrc->h;

    texture.handle = (ಶೂನ್ಯ *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    ಯದಿ (e != EVROverlayError_VROverlayError_None) {
        ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    ಯದಿ (e != EVROverlayError_VROverlayError_None) {
        ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    ಯದಿ (e != EVROverlayError_VROverlayError_None) {
        ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    ಯದಿ (e != EVROverlayError_VROverlayError_None) {
        ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    ಯದಿ (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        ಯದಿ (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ಸ್ಥಿರ bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    ಯದಿ (!global_openvr_driver) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಯದಿ (videodata->bIconOverridden) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (ಶೂನ್ಯ *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    ಯದಿ (e != EVROverlayError_VROverlayError_None) {
        ಪ್ರತ್ಯಾಗಮ OPENVR_SetOverlayError(e);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ವರ್ಣ empty = 0;
    ವರ್ಣ * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    ವರ್ಣ * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    ವರ್ಣ * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ InitializeMouseFunctions(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ಸಂರಚನಾ VREvent_t nEvent;
    ಯದಿ (videodata->overlayID) {
        ಯಾವತ್ (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, ಪರಿಮಾಣ(nEvent))) {
            ವಿಕಲ್ಪ (nEvent.eventType) {
            ಪಕ್ಷ EVREventType_VREvent_ButtonPress:
            ಪಕ್ಷ EVREventType_VREvent_ButtonUnpress:
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_ScrollSmooth:
            ಪಕ್ಷ EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ರಿಕ್ತ, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREvent_Type_VREvent_Keyboard_Char_ಒಳಹರಿವು:
                SDL_Send_Keyboard_Unicode_ಕೀಲಿ(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_ಒಳಹರಿವು[0]);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(ರಿಕ್ತ);
                ಭಙ್ಗ;
            ಪಕ್ಷ EVREventType_VREvent_OverlayClosed:
            ಪಕ್ಷ EVREventType_VREvent_Quit:
                SDL_SendQuit();
                ಭಙ್ಗ;
            }
        }
    }
}


ಸ್ಥಿರ SDL_VideoDevice *OPENVR_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ಧ್ರುವ ವರ್ಣ *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(ರಿಕ್ತ, 0, ರಿಕ್ತ);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (device) {
        data = (ಸಂರಚನಾ SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    } ಅನ್ಯಥಾ {
        data = ರಿಕ್ತ;
    }
    ಯದಿ (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    ಯದಿ (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    ಯದಿ (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    ಯದಿ (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        ಗಚ್ಛ error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (ಧ್ರುವ ವರ್ಣ *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(ಧ್ರುವ ವರ್ಣ *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    ಯದಿ (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        ಗಚ್ಛ error;
    }

    ವರ್ಣ fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    ಯದಿ (!data->vrtoken) {
        ಧ್ರುವ ವರ್ಣ *err = "Can't get english description";
        ಯದಿ (data->FN_VR_GetVRInitErrorAsEnglishDescription != ರಿಕ್ತ)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        ಗಚ್ಛ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (ಸಂರಚನಾ VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (ಸಂರಚನಾ VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_ಒಳಹರಿವು = (ಸಂರಚನಾ VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    ಯದಿ (!data->oOverlay || !data->oSystem || !data->o_ಒಳಹರಿವು) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    ವರ್ಣ *loadpath = 0;
    EVRInputError err;

    ಯದಿ (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ ವರ್ಣ *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    ಯದಿ (!loadpath) {
        ಗಚ್ಛ error;
    }

    err = data->o_ಒಳಹರಿವು->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    ಯದಿ (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        ಯದಿ (hint) {
            ಗಚ್ಛ error;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            ಗಚ್ಛ error;
        }
    }

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಮುಕ್ತ = OPENVR_Destroy;

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
#ಅನ್ಯಥಾ
#error Needs more work to support EGL
#endif
#ಅನ್ಯಥಾ
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

#ಯದಿ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#ಅನ್ಯಥಾ
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

    ಪ್ರತ್ಯಾಗಮ device;

error:
    OPENVR_Destroy(device);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ರಿಕ್ತ, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

