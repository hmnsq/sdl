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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#ଯଦି 0
#define DEBUG_OPENVR
#endif

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengl.h>
#ଅନ୍ୟଥା
// Currently only EGL, not OpenGL, is supported on other platforms
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengles2.h>
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ଅନ୍ତର୍ଭାଵ "../windows/SDL_windowsopengl.h"
#ଅନ୍ତର୍ଭାଵ "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

ସ୍ଥିର bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ସ୍ଥିର SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ସଂରଚନା SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#ଅନ୍ୟଥା
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

ସ୍ଥିର ଶୂନ୍ୟ InitializeMouseFunctions(ଶୂନ୍ୟ);

ସଂରଚନା SDL_CursorData
{
    unsigned texture_id_handle;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, hot_y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
};

// GL Extensions for functions we will be using.
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ସ୍ଥିର GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
ସ୍ଥିର GLenum (APIENTRY *ov_glGetError)(ଶୂନ୍ୟ);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glFlush)(ଶୂନ୍ୟ);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glFinish)(ଶୂନ୍ୟ);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *data);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ଅଚଳ GLenum *bufs);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
ସ୍ଥିର ଅଚଳ GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glClear)(GLbitfield mask);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ସ୍ଥିର ଶୂନ୍ୟ (APIENTRY *ov_gl_Debug_Message_ଭର୍ତ୍ତି)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ଅଚଳ ଅକ୍ଷର *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
ସ୍ଥିର PROC (*ov_wglGetProcAddress)(LPCSTR);
ସ୍ଥିର HGLRC (*ov_wglCreateContext)(HDC);
ସ୍ଥିର BOOL (*ov_wglDeleteContext)(HGLRC);
ସ୍ଥିର BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (ଶୂନ୍ୟ *)SDL_GL_GetProcAddress((#proc)+3); ଯଦି (!proc) { failed_extension = (#proc)+3; } }

ସ୍ଥିର bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    ଯଦି (!ov_glGetError) {
        ଅଚଳ ଅକ୍ଷର * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_ଭର୍ତ୍ତି);
        ଯଦି (failed_extension) {
            ଫେରନ୍ତୁ SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_SetOverlayError(EVROverlayError e)
{
    ବାଛ (e) {
#define CASE(X) ସ୍ଥିତି EVROverlayError_VROverlayError_##X: ଫେରନ୍ତୁ SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(ଚାବି_Too_Long);
    CASE(NameTooLong);
    CASE(ଚାବି_In_Use);
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
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SetError("Unknown VROverlayError %d", e);
    }
}

ସ୍ଥିର bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

ସ୍ଥିର bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ଅଚଳ ଅକ୍ଷର * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ଅଚଳ ଅକ୍ଷର * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ଅଚଳ ଅକ୍ଷର * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width = hintWidth ? SDL_atoi(hintWidth) : 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = hintHeight ? SDL_atoi(hintHeight) : 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    ଯଦି (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    ଯଦି (fps) {
        display.desktop_mode.refresh_rate = fps;
    } ଅନ୍ୟଥା {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (ଅକ୍ଷର *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    ଯଦି (data) {
        ଯଦି (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = surf->w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = surf->h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch = surf->pitch;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    ପାଇଁ(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        ପାଇଁ(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    ଫେରନ୍ତୁ pxd;
}

ସ୍ଥିର bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    ଯଦି (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    ଯଦି (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        ସଂରଚନା HmdVector2_t ms;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା status;

        ଯଦି (videodata->fbo <= 0) {
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
        ଯଦି (status != GL_FRAMEBUFFER_COMPLETE) {
            ଫେରନ୍ତୁ SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (ଦଶମିକ)videodata->targw;
        ms.v[1] = (ଦଶମିକ)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_VirtualControllerRumble(ଶୂନ୍ୟ *userdata, Uint16 ତଳ_frequency_rumble, Uint16 ଉପର_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    ଅଚଳ ଦଶମିକ k_flIntensity = 320.f; // Maximum frequency
    ଦଶମିକ fl_ବାମ_Frequency = (ଦଶମିକ)ତଳ_frequency_rumble * k_flIntensity / 65535.f;
    ଦଶମିକ fl_ଡାହାଣ_Frequency = (ଦଶମିକ)ଉପର_frequency_rumble * k_flIntensity / 65535.f;
    ଦଶମିକ flDurationSeconds = 2.f;
    ଦଶମିକ flAmplitude = 1.f;

    videodata->o_ନିବେଶ->TriggerHapticVibrationAction(videodata->ନିବେଶ_action_handles_haptics[0], 0, flDurationSeconds, fl_ବାମ_Frequency, flAmplitude, 0);
    videodata->o_ନିବେଶ->TriggerHapticVibrationAction(videodata->ନିବେଶ_action_handles_haptics[1], 0, flDurationSeconds, fl_ଡାହାଣ_Frequency, flAmplitude, 0);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_VirtualControllerRumbleTriggers(ଶୂନ୍ୟ *userdata, Uint16 ବାମ_rumble, Uint16 ଡାହାଣ_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_ନିବେଶ->TriggerHapticVibrationAction(videodata->ନିବେଶ_action_handles_haptics[0], 0, 0.1f, ବାମ_rumble, 1.0, 0);
    videodata->o_ନିବେଶ->TriggerHapticVibrationAction(videodata->ନିବେଶ_action_handles_haptics[1], 0, 0.1f, ଡାହାଣ_rumble, 1.0, 0);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_VirtualControllerUpdate(ଶୂନ୍ୟ *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ନିବେଶ_Digital_Action_Data_t digital_ନିବେଶ_action;
    ନିବେଶ_Analog_Action_Data_t analog_ନିବେଶ_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->ନିବେଶ_action_set;
    e = videodata->o_ନିବେଶ->UpdateActionState(&actionSet, ଆକାର(actionSet), 1);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        ଫେରନ୍ତୁ;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା d = 0; d < videodata->ନିବେଶ_action_handles_buttons_ଗଣନା; d++)
    {
        ଯଦି (videodata->ନିବେଶ_action_handles_buttons[d] == k_ulInvalidActionHandle)
            ଜାରି;
        e = videodata->o_ନିବେଶ->GetDigitalActionData(videodata->ନିବେଶ_action_handles_buttons[d], &digital_ନିବେଶ_action, ଆକାର(digital_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
        ଯଦି (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            ଫେରନ୍ତୁ;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_ନିବେଶ_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_ନିବେଶ->GetAnalogActionData(videodata->ନିବେଶ_action_handles_axes[0], &analog_ନିବେଶ_action, ଆକାର(analog_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        ଫେରନ୍ତୁ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ନିବେଶ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ନିବେଶ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ନିବେଶ->GetAnalogActionData(videodata->ନିବେଶ_action_handles_axes[1], &analog_ନିବେଶ_action, ଆକାର(analog_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        ଫେରନ୍ତୁ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ନିବେଶ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ନିବେଶ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ନିବେଶ->GetAnalogActionData(videodata->ନିବେଶ_action_handles_axes[2], &analog_ନିବେଶ_action, ଆକାର(analog_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        ଫେରନ୍ତୁ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ବାମ_TRIGGER, (Sint16)((analog_ନିବେଶ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ନିବେଶ->GetAnalogActionData(videodata->ନିବେଶ_action_handles_axes[3], &analog_ନିବେଶ_action, ଆକାର(analog_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        ଫେରନ୍ତୁ;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ଡାହାଣ_TRIGGER, (Sint16)((analog_ନିବେଶ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#ଯଦି 0
    ପାଇଁ (a = 0; a < videodata->ନିବେଶ_action_handles_axes_ଗଣନା; a++)
    {
        ଦଶମିକ xval = 0.0f;
        e = videodata->o_ନିବେଶ->GetAnalogActionData(videodata->ନିବେଶ_action_handles_axes[a], &analog_ନିବେଶ_action, ଆକାର(analog_ନିବେଶ_action), k_ul_Invalid_ନିବେଶ_ମୂଲ୍ୟ_Handle);
        ଯଦି (e) ଯାଅ updatefail;
        xval = analog_ନିବେଶ_action.x;
        ଯଦି (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        ଯଦି (a == SDL_GAMEPAD_AXIS_ବାମ_TRIGGER || a == SDL_GAMEPAD_AXIS_ଡାହାଣ_TRIGGER)
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
    ଫେରନ୍ତୁ;
}

ସ୍ଥିର bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    ଅକ୍ଷର * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_ଗଣନା] = {
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
    ଅକ୍ଷର * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    ଯଦି ((e = videodata->o_ନିବେଶ->GetActionSetHandle("/actions/virtualgamepad", &videodata->ନିବେଶ_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        ଫେରନ୍ତୁ SDL_SetError("Failed to get action set handle");
    }

    videodata->ନିବେଶ_action_handles_buttons_ଗଣନା = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ନିବେଶ_action_handles_buttons = SDL_malloc(videodata->ନିବେଶ_action_handles_buttons_ଗଣନା * ଆକାର(VRActionHandle_t));

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < videodata->ନିବେଶ_action_handles_buttons_ଗଣନା; i++)
    {
        e = videodata->o_ନିବେଶ->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ନିବେଶ_action_handles_buttons[i]);
        ଯଦି (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            ଫେରନ୍ତୁ SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->ନିବେଶ_action_handles_axes_ଗଣନା = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ନିବେଶ_action_handles_axes = SDL_malloc(videodata->ନିବେଶ_action_handles_axes_ଗଣନା * ଆକାର(VRActionHandle_t));

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < videodata->ନିବେଶ_action_handles_axes_ଗଣନା; i++)
    {
        e = videodata->o_ନିବେଶ->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ନିବେଶ_action_handles_axes[i]);
        ଯଦି (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            ଫେରନ୍ତୁ SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ନିବେଶ->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ନିବେଶ_action_handles_haptics[0]);
    e |= videodata->o_ନିବେଶ->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ନିବେଶ_action_handles_haptics[1]);
    ଯଦି (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        ଫେରନ୍ତୁ SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_ଗଣନା;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_ଗଣନା;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    ଯଦି (!virtual_id) {
        ଫେରନ୍ତୁ SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    ଯଦି (!videodata->virtual_joystick) {
        ଫେରନ୍ତୁ SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ନିବେଶ_action_handles_buttons_ଗଣନା, videodata->ନିବେଶ_action_handles_axes_ଗଣନା);
#endif

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    ଯଦି (!OPENVR_InitExtensions(_this)) {
        ଫେରନ୍ତୁ false;
    }

    // Generate the overlay.
    {
        ଅଚଳ ଅକ୍ଷର * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        ଅକ୍ଷର * cursorname = 0;
        ଯଦି (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        ଯଦି (!videodata->sOverlayName) {
            ଫେରନ୍ତୁ false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        ଯଦି (!cursorname) {
            ଫେରନ୍ତୁ false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        ଯଦି (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ଫେରନ୍ତୁ SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        ଯଦି (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ଫେରନ୍ତୁ SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_ସଂଖ୍ୟା, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        ଯଦି (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } ଅନ୍ୟଥା {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#ଯଦି 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଆକାର(overlay_flags) * 8; ++i) {
            ଯଦି (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ଅଚଳ ଅକ୍ଷର * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        ଦଶମିକ fWidth = hint ? (ଦଶମିକ)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ଅଚଳ ଅକ୍ଷର * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        ଦଶମିକ fCursorWidth = hint ? (ଦଶମିକ)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ଅଚଳ ଅକ୍ଷର * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        ଯଦି (hint) {
            ଅକ୍ଷର * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            ଯଦି (err == EVROverlayError_VROverlayError_None) {
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

    ଯଦି (!OPENVR_CheckRenderbuffer(_this)) {
        ଫେରନ୍ତୁ false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    ଫେରନ୍ତୁ true;
}


ସ୍ଥିର bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ସ୍ଥିର ଅଚଳ GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା error = ov_glGetError();
        ଯଦି (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    ଯଦି (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    ଯଦି (!ov_glGetError) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (!videodata->is_buffer_rendering) {
        ଫେରନ୍ତୁ true;
    }

#ifdef DEBUG_OPENVR
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା error = ov_glGetError();
        ଯଦି (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ଯଦି (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ସଂରଚନା Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (ଶୂନ୍ୟ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    ଯଦି (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    ଯଦି (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_ଭର୍ତ୍ତି(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    ଫେରନ୍ତୁ OPENVR_CheckRenderbuffer(_this);
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_HandleResize(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

ସ୍ଥିର bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ଫେରନ୍ତୁ true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
ସ୍ଥିର LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT ସନ୍ଦେଶ, WPARAM wParam, LPARAM lParam)
{
    ବାଛ (ସନ୍ଦେଶ) {
    ସ୍ଥିତି WM_DESTROY:
        ଫେରନ୍ତୁ 0;
    }
    ଫେରନ୍ତୁ DefWindowProc(hwnd, ସନ୍ଦେଶ, wParam, lParam);
}

ସ୍ଥିର bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path)
{
    ଯଦି (path == ଖାଲି) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    ଯଦି (path == ଖାଲି) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    ଯଦି (!_this->gl_config.dll_handle) {
        ଫେରନ୍ତୁ false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (ସଂରଚନା SDL_GLDriverData *)SDL_calloc(1, ଆକାର(ସଂରଚନା SDL_GLDriverData));
    ଯଦି (!_this->gl_data) {
        ଫେରନ୍ତୁ false;
    }
    _this->gl_config.driver_loaded = true;

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc)
{
    SDL_FunctionPointer result = ଖାଲି;
    ଯଦି (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        ଯଦି (result) {
            ଫେରନ୍ତୁ result;
        }
    }

    ଫେରନ୍ତୁ SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ସ୍ଥିର SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint ଅଙ୍କ_Extensions;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ଖାଲି);
        wnd.hIcon = LoadIcon(ଖାଲି, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(ଖାଲି, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ଖାଲି;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ଖାଲି, ଖାଲି, GetModuleHandle(ଖାଲି), ଖାଲି);

        ସନ୍ଦେଶ_2 ସନ୍ଦେଶ;
        ଯେତେବେଳେ (PeekMessage(&ସନ୍ଦେଶ, ଖାଲି, 0, 0, PM_REMOVE)) {
            TranslateMessage(&ସନ୍ଦେଶ);
            DispatchMessage(&ସନ୍ଦେଶ);
        }

        videodata->hdc = GetDC(hwnd);

        ସ୍ଥିର  PIXELFORMATDESCRIPTOR pfd =
        {
            ଆକାର(PIXELFORMATDESCRIPTOR),
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
        ଯଦି (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            ଫେରନ୍ତୁ ଖାଲି;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        ଯଦି (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        ଯଦି (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        ଯଦି (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    i = OPENVR_InitExtensions(_this);
    ଯଦି (i == 0) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_ଅଙ୍କ_EXTENSIONS, &ଅଙ୍କ_Extensions);
    ପାଇଁ (i = 0; i < ଅଙ୍କ_Extensions; i++) {
        ଅଚଳ ଅକ୍ଷର *ccc = (ଅଚଳ ଅକ୍ଷର *)ov_glGetStringi(GL_EXTENSIONS, i);
        ଯଦି (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    ଯଦି (!videodata->bDidCreateOverlay) {
        ଯଦି (!OPENVR_InitializeOverlay(_this, window)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(ଆକାର(ସଂରଚନା SDL_GLContextState));
    ଯଦି (!result) {
        ଫେରନ୍ତୁ ଖାଲି;
    }
    result->hglrc = videodata->hglrc;
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (swapInterval)
        *swapInterval = videodata->swap_interval;
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, ଖାଲି);
    ov_wglDeleteContext(videodata->hglrc);
    ଫେରନ୍ତୁ true;
}


#ଅନ୍ୟଥା

ସ୍ଥିର EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

ସ୍ଥିର bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ଖାଲି;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    ଯଦି (vd->eglDpy == 0) {
        ଫେରନ୍ତୁ SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    ଯଦି (!b) {
        ଫେରନ୍ତୁ SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = eglGetError();
        ଯଦି (err != EGL_SUCCESS) {
            ଫେରନ୍ତୁ SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    ଯଦି (!vd->eglCtx) {
        ଫେରନ୍ତୁ SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    ଫେରନ୍ତୁ true;
}

// Linux, EGL, etc.
ସ୍ଥିର bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path)
{
    ଫେରନ୍ତୁ SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

ସ୍ଥିର SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc)
{
    ଫେରନ୍ତୁ SDL_EGL_GetProcAddress(proc);
}
ସ୍ଥିର ଶୂନ୍ୟ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ସ୍ଥିର SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint ଅଙ୍କ_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (!videodata->eglCtx) {
        ଯଦି (!SDL_EGL_InitInternal(videodata)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    ଯଦି (!OPENVR_InitExtensions(_this)) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_ଅଙ୍କ_EXTENSIONS, &ଅଙ୍କ_Extensions);
    ପାଇଁ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_Extensions; i++) {
        ଅଚଳ ଅକ୍ଷର * ccc = (ଅଚଳ ଅକ୍ଷର *)ov_glGetStringi(GL_EXTENSIONS, i);
        ଯଦି (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    ଯଦି (!videodata->bDidCreateOverlay) {
        ଯଦି (!OPENVR_InitializeOverlay(_this, window)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    ଫେରନ୍ତୁ videodata->eglCtx;
}

ସ୍ଥିର bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (swapInterval)
        *swapInterval = videodata->swap_interval;
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    ଫେରନ୍ତୁ true;
}

#endif

ସ୍ଥିର bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, ଆକାର(SDL_WindowData));
    ଯଦି (data == ଖାଲି) {
        ଫେରନ୍ତୁ SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    ଫେରନ୍ତୁ true;
}


ସ୍ଥିର ଶୂନ୍ୟ OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    ଯଦି (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ଯଦି (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    ଯଦି (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    ଯଦି (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    ଯଦି (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_ନିବେଶ_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଫେରନ୍ତୁ;
}

ସ୍ଥିର bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    ଯଦି (!videodata->bDidCreateOverlay) {
        ଯଦି (!OPENVR_InitializeOverlay(_this, window)) {
            ଫେରନ୍ତୁ false;
        }
    }

    ଯଦି (!OPENVR_ReleaseFrame(_this)) {
        ଫେରନ୍ତୁ false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    ଯଦି (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    ଯଦି (!OPENVR_SetupFrame(_this, window)) {
        ଫେରନ୍ତୁ false;
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର Uint8 OPENVR_MapMouseButton(ପୂର୍ଣ୍ଣସଂଖ୍ୟା btn)
{
    ଯଦି (btn == EVRMouse_Button_VRMouse_Button_ଡାହାଣ) {
        ଫେରନ୍ତୁ SDL_BUTTON_ଡାହାଣ;
    } ଅନ୍ୟଥା ଯଦି (btn == EVRMouse_Button_VRMouse_Button_ମଧ୍ୟ) {
        ଫେରନ୍ତୁ SDL_BUTTON_ମଧ୍ୟ;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_BUTTON_ବାମ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_HandleMouse(ଦଶମିକ x, ଦଶମିକ y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା btn, ପୂର୍ଣ୍ଣସଂଖ୍ୟା evt)
{
    ଯଦି (evt == 2) {
        SDL_SendMouseMotion(0, ଖାଲି, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } ଅନ୍ୟଥା {
        ଅଚଳ Uint8 button = OPENVR_MapMouseButton(btn);
        ଅଚଳ bool down = (evt != 0);
        SDL_SendMouseButton(0, ଖାଲି, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


ସ୍ଥିର bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        ଫେରନ୍ତୁ;
    }
    EGamepad_Text_ନିବେଶ_Mode ନିବେଶ_mode;
    ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_HIDDEN:
        ନିବେଶ_mode = EGamepad_Text_ନିବେଶ_Mode_k_EGamepad_Text_ନିବେଶ_Mode_Password;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ନିବେଶ_mode = EGamepad_Text_ନିବେଶ_Mode_k_EGamepad_Text_ନିବେଶ_Mode_Normal;
        ଭାଙ୍ଗ;
    }
    EGamepad_Text_ନିବେଶ_ଧାଡ଼ି_Mode ଧାଡ଼ି_mode;
    ଯଦି (SDL_Get_Text_ନିବେଶ_Multiline(props)) {
        ଧାଡ଼ି_mode = EGamepad_Text_ନିବେଶ_ଧାଡ଼ି_Mode_k_EGamepad_Text_ନିବେଶ_ଧାଡ଼ି_Mode_Multiple_ଧାଡ଼ିଗୁଡ଼ିକ;
    } ଅନ୍ୟଥା {
        ଧାଡ଼ି_mode = EGamepad_Text_ନିବେଶ_ଧାଡ଼ି_Mode_k_EGamepad_Text_ନିବେଶ_ଧାଡ଼ି_Mode_Single_ଧାଡ଼ି;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ନିବେଶ_mode, ଧାଡ଼ି_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ସ୍ଥିର SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, ଆକାର(SDL_Cursor));
    ଯଦି (!result) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*ovrc));
    ଯଦି (!ovrc) {
        SDL_free(result);
        ଫେରନ୍ତୁ ଖାଲି;
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

    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    ଯଦି (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        ଯଦି (e != EVROverlayError_VROverlayError_None) {
            ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
        }
        ଫେରନ୍ତୁ true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    ଯଦି (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        ଫେରନ୍ତୁ true;
    }

    hotspot.v[0] = (ଦଶମିକ)ovrc->hot_x / (ଦଶମିକ)ovrc->w;
    hotspot.v[1] = (ଦଶମିକ)ovrc->hot_y / (ଦଶମିକ)ovrc->h;

    texture.handle = (ଶୂନ୍ୟ *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    ଯଦି (e != EVROverlayError_VROverlayError_None) {
        ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    ଯଦି (e != EVROverlayError_VROverlayError_None) {
        ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    ଯଦି (e != EVROverlayError_VROverlayError_None) {
        ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    ଯଦି (e != EVROverlayError_VROverlayError_None) {
        ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    ଯଦି (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        ଯଦି (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ସ୍ଥିର bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    ଯଦି (!global_openvr_driver) {
        ଫେରନ୍ତୁ SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଯଦି (videodata->bIconOverridden) {
        ଫେରନ୍ତୁ SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (ଶୂନ୍ୟ *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    ଯଦି (e != EVROverlayError_VROverlayError_None) {
        ଫେରନ୍ତୁ OPENVR_SetOverlayError(e);
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ଅକ୍ଷର empty = 0;
    ଅକ୍ଷର * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    ଅକ୍ଷର * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    ଅକ୍ଷର * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ InitializeMouseFunctions(ଶୂନ୍ୟ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ସ୍ଥିର ଶୂନ୍ୟ OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ସଂରଚନା VREvent_t nEvent;
    ଯଦି (videodata->overlayID) {
        ଯେତେବେଳେ (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, ଆକାର(nEvent))) {
            ବାଛ (nEvent.eventType) {
            ସ୍ଥିତି EVREventType_VREvent_ButtonPress:
            ସ୍ଥିତି EVREventType_VREvent_ButtonUnpress:
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_ScrollSmooth:
            ସ୍ଥିତି EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ଖାଲି, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREvent_Type_VREvent_Keyboard_Char_ନିବେଶ:
                SDL_Send_Keyboard_Unicode_ଚାବି(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_ନିବେଶ[0]);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(ଖାଲି);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି EVREventType_VREvent_OverlayClosed:
            ସ୍ଥିତି EVREventType_VREvent_Quit:
                SDL_SendQuit();
                ଭାଙ୍ଗ;
            }
        }
    }
}


ସ୍ଥିର SDL_VideoDevice *OPENVR_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ଅଚଳ ଅକ୍ଷର *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(ଖାଲି, 0, ଖାଲି);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (device) {
        data = (ସଂରଚନା SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    } ଅନ୍ୟଥା {
        data = ଖାଲି;
    }
    ଯଦି (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    ଯଦି (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    ଯଦି (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    ଯଦି (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        ଯାଅ error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (ଅଚଳ ଅକ୍ଷର *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(ଅଚଳ ଅକ୍ଷର *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    ଯଦି (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        ଯାଅ error;
    }

    ଅକ୍ଷର fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    ଯଦି (!data->vrtoken) {
        ଅଚଳ ଅକ୍ଷର *err = "Can't get english description";
        ଯଦି (data->FN_VR_GetVRInitErrorAsEnglishDescription != ଖାଲି)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        ଯାଅ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (ସଂରଚନା VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (ସଂରଚନା VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_ନିବେଶ = (ସଂରଚନା VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    ଯଦି (!data->oOverlay || !data->oSystem || !data->o_ନିବେଶ) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    ଅକ୍ଷର *loadpath = 0;
    EVRInputError err;

    ଯଦି (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } ଅନ୍ୟଥା {
        ଅଚଳ ଅକ୍ଷର *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    ଯଦି (!loadpath) {
        ଯାଅ error;
    }

    err = data->o_ନିବେଶ->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    ଯଦି (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        ଯଦି (hint) {
            ଯାଅ error;
        }
    } ଅନ୍ୟଥା {
        ଯଦି(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            ଯାଅ error;
        }
    }

    // Setup amount of available displays
    device->ଅଙ୍କ_displays = 0;

    // Set device free function
    device->ମୁକ୍ତ = OPENVR_Destroy;

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
#ଅନ୍ୟଥା
#error Needs more work to support EGL
#endif
#ଅନ୍ୟଥା
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

#ଯଦି defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#ଅନ୍ୟଥା
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

    ଫେରନ୍ତୁ device;

error:
    OPENVR_Destroy(device);
    ଫେରନ୍ତୁ ଖାଲି;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ଖାଲି, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

