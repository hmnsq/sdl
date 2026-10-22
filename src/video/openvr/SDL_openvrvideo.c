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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#যদি 0
#define DEBUG_OPENVR
#endif

#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_pixels_c.h"
#অন্তর্ভাব "../SDL_egl_c.h"
#অন্তর্ভাব "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#অন্তর্ভাব <SDL3/SDL_opengl.h>
#অন্যথা
// Currently only EGL, not OpenGL, is supported on other platforms
#অন্তর্ভাব <SDL3/SDL_opengles2.h>
#অন্তর্ভাব <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#অন্তর্ভাব "../windows/SDL_windowsopengl.h"
#অন্তর্ভাব "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

স্থির bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path);
স্থির SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

কাঠামো SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#অন্যথা
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
SDL_Video_তথ্য * global_openvr_driver;

স্থির শূন্য InitializeMouseFunctions(শূন্য);

কাঠামো SDL_Cursor_তথ্য
{
    unsigned texture_id_handle;
    পূর্ণসংখ্যা hot_x, hot_y;
    পূর্ণসংখ্যা w, h;
};

// GL Extensions for functions we will be using.
স্থির শূন্য (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
স্থির শূন্য (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
স্থির শূন্য (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
স্থির শূন্য (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
স্থির শূন্য (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
স্থির শূন্য (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
স্থির শূন্য (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
স্থির GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
স্থির GLenum (APIENTRY *ov_glGetError)(শূন্য);
স্থির শূন্য (APIENTRY *ov_glFlush)(শূন্য);
স্থির শূন্য (APIENTRY *ov_glFinish)(শূন্য);
স্থির শূন্য (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
স্থির শূন্য (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
স্থির শূন্য (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
স্থির শূন্য (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
স্থির শূন্য (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ধ্রুবক শূন্য *তথ্য);
স্থির শূন্য (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
স্থির শূন্য (APIENTRY *ov_glDrawBuffers)(GLsizei n, ধ্রুবক GLenum *bufs);
স্থির শূন্য (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * তথ্য);
স্থির ধ্রুবক GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint সূচক);
স্থির শূন্য (APIENTRY *ov_glClear)(GLbitfield mask);
স্থির শূন্য (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
স্থির শূন্য (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
স্থির শূন্য (APIENTRY *ov_gl_Debug_Message_ঢোকাও)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei দৈর্ঘ্য, ধ্রুবক অক্ষর *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
স্থির PROC (*ov_wglGetProcAddress)(LPCSTR);
স্থির HGLRC (*ov_wglCreateContext)(HDC);
স্থির BOOL (*ov_wglDeleteContext)(HGLRC);
স্থির BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (শূন্য *)SDL_GL_GetProcAddress((#proc)+3); যদি (!proc) { failed_extension = (#proc)+3; } }

স্থির bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    যদি (!ov_glGetError) {
        ধ্রুবক অক্ষর * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_ঢোকাও);
        যদি (failed_extension) {
            ফেরত SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    ফেরত true;
}

স্থির bool OPENVR_SetOverlayError(EVROverlayError e)
{
    নির্বাচন (e) {
#define CASE(X) ক্ষেত্র EVROverlayError_VROverlayError_##X: ফেরত SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(চাবি_Too_Long);
    CASE(NameTooLong);
    CASE(চাবি_In_Use);
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
    পূর্বনির্ধারিত:
        ফেরত SDL_SetError("Unknown VROverlayError %d", e);
    }
}

স্থির bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

স্থির bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = (SDL_Video_তথ্য *)_this->internal;

    ধ্রুবক অক্ষর * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ধ্রুবক অক্ষর * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ধ্রুবক অক্ষর * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    পূর্ণসংখ্যা width = hintWidth ? SDL_atoi(hintWidth) : 0;
    পূর্ণসংখ্যা height = hintHeight ? SDL_atoi(hintHeight) : 0;
    পূর্ণসংখ্যা fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    যদি (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    যদি (fps) {
        display.desktop_mode.refresh_rate = fps;
    } অন্যথা {
        display.desktop_mode.refresh_rate = তথ্য->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_সূচক_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (অক্ষর *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    ফেরত true;
}

স্থির শূন্য OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

স্থির শূন্য OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_তথ্য *তথ্য = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    যদি (তথ্য) {
        যদি (তথ্য->openVRLIB) {
            SDL_UnloadObject(তথ্য->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    পূর্ণসংখ্যা w = surf->w;
    পূর্ণসংখ্যা h = surf->h;
    পূর্ণসংখ্যা pitch = surf->pitch;
    পূর্ণসংখ্যা x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    জন্য(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        জন্য(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    ফেরত pxd;
}

স্থির bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;

    যদি (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    যদি (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        কাঠামো HmdVector2_t ms;
        পূর্ণসংখ্যা status;

        যদি (videodata->fbo <= 0) {
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
        যদি (status != GL_FRAMEBUFFER_COMPLETE) {
            ফেরত SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (দশমিক)videodata->targw;
        ms.v[1] = (দশমিক)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    ফেরত true;
}

স্থির bool OPENVR_VirtualControllerRumble(শূন্য *userdata, Uint16 নিচের_frequency_rumble, Uint16 উপরের_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)userdata;

    ধ্রুবক দশমিক k_flIntensity = 320.f; // Maximum frequency
    দশমিক fl_বাম_Frequency = (দশমিক)নিচের_frequency_rumble * k_flIntensity / 65535.f;
    দশমিক fl_ডান_Frequency = (দশমিক)উপরের_frequency_rumble * k_flIntensity / 65535.f;
    দশমিক flDurationSeconds = 2.f;
    দশমিক flAmplitude = 1.f;

    videodata->o_প্রবেশ->TriggerHapticVibrationAction(videodata->প্রবেশ_action_handles_haptics[0], 0, flDurationSeconds, fl_বাম_Frequency, flAmplitude, 0);
    videodata->o_প্রবেশ->TriggerHapticVibrationAction(videodata->প্রবেশ_action_handles_haptics[1], 0, flDurationSeconds, fl_ডান_Frequency, flAmplitude, 0);

    ফেরত true;
}

স্থির bool OPENVR_VirtualControllerRumbleTriggers(শূন্য *userdata, Uint16 বাম_rumble, Uint16 ডান_rumble)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)userdata;
    videodata->o_প্রবেশ->TriggerHapticVibrationAction(videodata->প্রবেশ_action_handles_haptics[0], 0, 0.1f, বাম_rumble, 1.0, 0);
    videodata->o_প্রবেশ->TriggerHapticVibrationAction(videodata->প্রবেশ_action_handles_haptics[1], 0, 0.1f, ডান_rumble, 1.0, 0);
    ফেরত true;
}

স্থির শূন্য OPENVR_VirtualControllerUpdate(শূন্য *userdata)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    প্রবেশ_Digital_Action_তথ্য_t digital_প্রবেশ_action;
    প্রবেশ_Analog_Action_তথ্য_t analog_প্রবেশ_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->প্রবেশ_action_set;
    e = videodata->o_প্রবেশ->UpdateActionState(&actionSet, আকার(actionSet), 1);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        ফেরত;
    }

    জন্য (পূর্ণসংখ্যা d = 0; d < videodata->প্রবেশ_action_handles_buttons_গুনতি; d++)
    {
        যদি (videodata->প্রবেশ_action_handles_buttons[d] == k_ulInvalidActionHandle)
            চালু;
        e = videodata->o_প্রবেশ->Get_Digital_Action_তথ্য(videodata->প্রবেশ_action_handles_buttons[d], &digital_প্রবেশ_action, আকার(digital_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
        যদি (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            ফেরত;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_প্রবেশ_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_প্রবেশ->Get_Analog_Action_তথ্য(videodata->প্রবেশ_action_handles_axes[0], &analog_প্রবেশ_action, আকার(analog_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        ফেরত;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_প্রবেশ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_প্রবেশ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_প্রবেশ->Get_Analog_Action_তথ্য(videodata->প্রবেশ_action_handles_axes[1], &analog_প্রবেশ_action, আকার(analog_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        ফেরত;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_প্রবেশ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_প্রবেশ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_প্রবেশ->Get_Analog_Action_তথ্য(videodata->প্রবেশ_action_handles_axes[2], &analog_প্রবেশ_action, আকার(analog_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        ফেরত;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_বাম_TRIGGER, (Sint16)((analog_প্রবেশ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_প্রবেশ->Get_Analog_Action_তথ্য(videodata->প্রবেশ_action_handles_axes[3], &analog_প্রবেশ_action, আকার(analog_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        ফেরত;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ডান_TRIGGER, (Sint16)((analog_প্রবেশ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#যদি 0
    জন্য (a = 0; a < videodata->প্রবেশ_action_handles_axes_গুনতি; a++)
    {
        দশমিক xval = 0.0f;
        e = videodata->o_প্রবেশ->Get_Analog_Action_তথ্য(videodata->প্রবেশ_action_handles_axes[a], &analog_প্রবেশ_action, আকার(analog_প্রবেশ_action), k_ul_Invalid_প্রবেশ_মান_Handle);
        যদি (e) যাও updatefail;
        xval = analog_প্রবেশ_action.x;
        যদি (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        যদি (a == SDL_GAMEPAD_AXIS_বাম_TRIGGER || a == SDL_GAMEPAD_AXIS_ডান_TRIGGER)
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
    ফেরত;
}

স্থির bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_Video_তথ্য * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    অক্ষর * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_গুনতি] = {
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
    অক্ষর * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    যদি ((e = videodata->o_প্রবেশ->GetActionSetHandle("/actions/virtualgamepad", &videodata->প্রবেশ_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        ফেরত SDL_SetError("Failed to get action set handle");
    }

    videodata->প্রবেশ_action_handles_buttons_গুনতি = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->প্রবেশ_action_handles_buttons = SDL_malloc(videodata->প্রবেশ_action_handles_buttons_গুনতি * আকার(VRActionHandle_t));

    জন্য (পূর্ণসংখ্যা i = 0; i < videodata->প্রবেশ_action_handles_buttons_গুনতি; i++)
    {
        e = videodata->o_প্রবেশ->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->প্রবেশ_action_handles_buttons[i]);
        যদি (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            ফেরত SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->প্রবেশ_action_handles_axes_গুনতি = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->প্রবেশ_action_handles_axes = SDL_malloc(videodata->প্রবেশ_action_handles_axes_গুনতি * আকার(VRActionHandle_t));

    জন্য (পূর্ণসংখ্যা i = 0; i < videodata->প্রবেশ_action_handles_axes_গুনতি; i++)
    {
        e = videodata->o_প্রবেশ->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->প্রবেশ_action_handles_axes[i]);
        যদি (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            ফেরত SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_প্রবেশ->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->প্রবেশ_action_handles_haptics[0]);
    e |= videodata->o_প্রবেশ->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->প্রবেশ_action_handles_haptics[1]);
    যদি (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        ফেরত SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_গুনতি;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_গুনতি;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    যদি (!virtual_id) {
        ফেরত SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    যদি (!videodata->virtual_joystick) {
        ফেরত SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->প্রবেশ_action_handles_buttons_গুনতি, videodata->প্রবেশ_action_handles_axes_গুনতি);
#endif

    ফেরত true;
}

স্থির bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    যদি (!OPENVR_InitExtensions(_this)) {
        ফেরত false;
    }

    // Generate the overlay.
    {
        ধ্রুবক অক্ষর * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        অক্ষর * cursorname = 0;
        যদি (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        যদি (!videodata->sOverlayName) {
            ফেরত false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        যদি (!cursorname) {
            ফেরত false;
        }

        EVROverlayError ফলাফল = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        যদি (ফলাফল != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ফেরত SDL_SetError("Could not create dashboard overlay (%d)", ফলাফল );
        }
        ফলাফল = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        যদি (ফলাফল != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ফেরত SDL_SetError("Could not create cursor overlay (%d)", ফলাফল );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_সংখ্যা, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ধ্রুবক অক্ষর *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        যদি (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } অন্যথা {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#যদি 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        জন্য (পূর্ণসংখ্যা i = 0; i < আকার(overlay_flags) * 8; ++i) {
            যদি (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ধ্রুবক অক্ষর * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        দশমিক fWidth = hint ? (দশমিক)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ধ্রুবক অক্ষর * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        দশমিক fCursorWidth = hint ? (দশমিক)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ধ্রুবক অক্ষর * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        যদি (hint) {
            অক্ষর * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            যদি (err == EVROverlayError_VROverlayError_None) {
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

    যদি (!OPENVR_CheckRenderbuffer(_this)) {
        ফেরত false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    ফেরত true;
}


স্থির bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    স্থির ধ্রুবক GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_বাফার_rendering = true;

#ifdef DEBUG_OPENVR
    {
        পূর্ণসংখ্যা error = ov_glGetError();
        যদি (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    যদি (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_বাফার_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    ফেরত true;
}

স্থির bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    যদি (!ov_glGetError) {
        ফেরত true;
    }

    যদি (!videodata->is_বাফার_rendering) {
        ফেরত true;
    }

#ifdef DEBUG_OPENVR
    {
        পূর্ণসংখ্যা error = ov_glGetError();
        যদি (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_বাফার_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    যদি (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        কাঠামো Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (শূন্য *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    যদি (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    যদি (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_ঢোকাও(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    ফেরত OPENVR_CheckRenderbuffer(_this);
}

স্থির শূন্য OPENVR_HandleResize(SDL_VideoDevice *_this, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h)
{
    SDL_Video_তথ্য *তথ্য = (SDL_Video_তথ্য *)_this->internal;
    তথ্য->targw = w;
    তথ্য->targh = h;
}

স্থির bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ফেরত true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
স্থির LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM lParam)
{
    নির্বাচন (বার্তা) {
    ক্ষেত্র WM_DESTROY:
        ফেরত 0;
    }
    ফেরত DefWindowProc(hwnd, বার্তা, wParam, lParam);
}

স্থির bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    যদি (path == ফাঁকা) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    যদি (path == ফাঁকা) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    যদি (!_this->gl_config.dll_handle) {
        ফেরত false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_তথ্য = (কাঠামো SDL_GLDriver_তথ্য *)SDL_calloc(1, আকার(কাঠামো SDL_GLDriver_তথ্য));
    যদি (!_this->gl_তথ্য) {
        ফেরত false;
    }
    _this->gl_config.driver_loaded = true;

    ফেরত true;
}

স্থির SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    SDL_FunctionPointer ফলাফল = ফাঁকা;
    যদি (ov_wglGetProcAddress) {
        ফলাফল = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        যদি (ফলাফল) {
            ফেরত ফলাফল;
        }
    }

    ফেরত SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

স্থির শূন্য OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

স্থির SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint অঙ্ক_Extensions;
    পূর্ণসংখ্যা i;
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ফাঁকা);
        wnd.hIcon = LoadIcon(ফাঁকা, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(ফাঁকা, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ফাঁকা;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ফাঁকা, ফাঁকা, GetModuleHandle(ফাঁকা), ফাঁকা);

        বার্তা_2 বার্তা;
        যখন (PeekMessage(&বার্তা, ফাঁকা, 0, 0, PM_REMOVE)) {
            TranslateMessage(&বার্তা);
            DispatchMessage(&বার্তা);
        }

        videodata->hdc = GetDC(hwnd);

        স্থির  PIXELFORMATDESCRIPTOR pfd =
        {
            আকার(PIXELFORMATDESCRIPTOR),
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
        যদি (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            ফেরত ফাঁকা;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        যদি (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            ফেরত ফাঁকা;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        যদি (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            ফেরত ফাঁকা;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        যদি (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            ফেরত ফাঁকা;
        }
    }

    i = OPENVR_InitExtensions(_this);
    যদি (i == 0) {
        ফেরত ফাঁকা;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_অঙ্ক_EXTENSIONS, &অঙ্ক_Extensions);
    জন্য (i = 0; i < অঙ্ক_Extensions; i++) {
        ধ্রুবক অক্ষর *ccc = (ধ্রুবক অক্ষর *)ov_glGetStringi(GL_EXTENSIONS, i);
        যদি (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    যদি (!videodata->bDidCreateOverlay) {
        যদি (!OPENVR_InitializeOverlay(_this, window)) {
            ফেরত ফাঁকা;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext ফলাফল = SDL_malloc(আকার(কাঠামো SDL_GLContextState));
    যদি (!ফলাফল) {
        ফেরত ফাঁকা;
    }
    ফলাফল->hglrc = videodata->hglrc;
    ফেরত ফলাফল;
}

স্থির bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    ফেরত true;
}

স্থির bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    videodata->swap_interval = interval;
    ফেরত true;
}

স্থির bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা *swapInterval)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (swapInterval)
        *swapInterval = videodata->swap_interval;
    অন্যথা
        ফেরত SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ফেরত true;
}

স্থির bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, ফাঁকা);
    ov_wglDeleteContext(videodata->hglrc);
    ফেরত true;
}


#অন্যথা

স্থির EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

স্থির bool SDL_EGL_InitInternal(SDL_Video_তথ্য * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ফাঁকা;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    যদি (vd->eglDpy == 0) {
        ফেরত SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    যদি (!b) {
        ফেরত SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        পূর্ণসংখ্যা err = eglGetError();
        যদি (err != EGL_SUCCESS) {
            ফেরত SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    যদি (!vd->eglCtx) {
        ফেরত SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    ফেরত true;
}

// Linux, EGL, etc.
স্থির bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *path)
{
    ফেরত SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

স্থির SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ধ্রুবক অক্ষর *proc)
{
    ফেরত SDL_EGL_GetProcAddress(proc);
}
স্থির শূন্য OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
স্থির SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint অঙ্ক_Extensions;
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (!videodata->eglCtx) {
        যদি (!SDL_EGL_InitInternal(videodata)) {
            ফেরত ফাঁকা;
        }
    }

    যদি (!OPENVR_InitExtensions(_this)) {
        ফেরত ফাঁকা;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_অঙ্ক_EXTENSIONS, &অঙ্ক_Extensions);
    জন্য(পূর্ণসংখ্যা i = 0; i < অঙ্ক_Extensions; i++) {
        ধ্রুবক অক্ষর * ccc = (ধ্রুবক অক্ষর *)ov_glGetStringi(GL_EXTENSIONS, i);
        যদি (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    যদি (!videodata->bDidCreateOverlay) {
        যদি (!OPENVR_InitializeOverlay(_this, window)) {
            ফেরত ফাঁকা;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    ফেরত videodata->eglCtx;
}

স্থির bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    ফেরত true;
}

স্থির bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা interval)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    videodata->swap_interval = interval;
    ফেরত true;
}

স্থির bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণসংখ্যা * swapInterval)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (swapInterval)
        *swapInterval = videodata->swap_interval;
    অন্যথা
        ফেরত SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    ফেরত true;
}

স্থির bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    ফেরত true;
}

#endif

স্থির bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_তথ্য *তথ্য;

    // Allocate window internal data
    তথ্য = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(SDL_Window_তথ্য));
    যদি (তথ্য == ফাঁকা) {
        ফেরত SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = তথ্য;
    ফেরত true;
}


স্থির শূন্য OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য;

    তথ্য = window->internal;
    SDL_free(তথ্য);
    window->internal = ফাঁকা;
}

স্থির শূন্য OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য * তথ্য = (SDL_Video_তথ্য *)_this->internal;
    যদি (তথ্য->bDidCreateOverlay) {
        তথ্য->oOverlay->SetOverlayName(তথ্য->overlayID, window->title);
    }
}

স্থির শূন্য OPENVR_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *তথ্য = (SDL_Video_তথ্য *)_this->internal;

    যদি (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    যদি (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    যদি (তথ্য->targh != window->h || তথ্য->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

স্থির শূন্য OPENVR_Get_Window_আকার_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *w, পূর্ণসংখ্যা *h)
{
    SDL_Video_তথ্য *তথ্য = (SDL_Video_তথ্য *)_this->internal;
    *w = তথ্য->targw;
    *h = তথ্য->targh;
}

স্থির শূন্য OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *তথ্য = (SDL_Video_তথ্য *)_this->internal;
    যদি (তথ্য->targh != window->h || তথ্য->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    তথ্য->oOverlay->ShowDashboard(তথ্য->sOverlayName);

    window->flags |= (SDL_WINDOW_প্রবেশ_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

স্থির শূন্য OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    ফেরত;
}

স্থির bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    যদি (!videodata->bDidCreateOverlay) {
        যদি (!OPENVR_InitializeOverlay(_this, window)) {
            ফেরত false;
        }
    }

    যদি (!OPENVR_ReleaseFrame(_this)) {
        ফেরত false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    যদি (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    যদি (!OPENVR_SetupFrame(_this, window)) {
        ফেরত false;
    }

    ফেরত true;
}

স্থির Uint8 OPENVR_MapMouseButton(পূর্ণসংখ্যা btn)
{
    যদি (btn == EVRMouse_Button_VRMouse_Button_ডান) {
        ফেরত SDL_BUTTON_ডান;
    } অন্যথা যদি (btn == EVRMouse_Button_VRMouse_Button_মধ্য) {
        ফেরত SDL_BUTTON_মধ্য;
    } অন্যথা {
        ফেরত SDL_BUTTON_বাম;
    }
}

স্থির শূন্য OPENVR_HandleMouse(দশমিক x, দশমিক y, পূর্ণসংখ্যা btn, পূর্ণসংখ্যা evt)
{
    যদি (evt == 2) {
        SDL_SendMouseMotion(0, ফাঁকা, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } অন্যথা {
        ধ্রুবক Uint8 button = OPENVR_MapMouseButton(btn);
        ধ্রুবক bool down = (evt != 0);
        SDL_SendMouseButton(0, ফাঁকা, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


স্থির bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ফেরত true;
}

স্থির শূন্য OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        ফেরত;
    }
    EGamepad_Text_প্রবেশ_Mode প্রবেশ_mode;
    নির্বাচন (SDL_Get_Text_প্রবেশ_Type(props)) {
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        প্রবেশ_mode = EGamepad_Text_প্রবেশ_Mode_k_EGamepad_Text_প্রবেশ_Mode_Password;
        বিরতি;
    পূর্বনির্ধারিত:
        প্রবেশ_mode = EGamepad_Text_প্রবেশ_Mode_k_EGamepad_Text_প্রবেশ_Mode_Normal;
        বিরতি;
    }
    EGamepad_Text_প্রবেশ_সারি_Mode সারি_mode;
    যদি (SDL_Get_Text_প্রবেশ_Multiline(props)) {
        সারি_mode = EGamepad_Text_প্রবেশ_সারি_Mode_k_EGamepad_Text_প্রবেশ_সারি_Mode_Multiple_সারিগুলি;
    } অন্যথা {
        সারি_mode = EGamepad_Text_প্রবেশ_সারি_Mode_k_EGamepad_Text_প্রবেশ_সারি_Mode_Single_সারি;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           প্রবেশ_mode, সারি_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

স্থির শূন্য OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

স্থির SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    SDL_Cursor *ফলাফল = SDL_calloc(1, আকার(SDL_Cursor));
    যদি (!ফলাফল) {
        ফেরত ফাঁকা;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_তথ্য *ovrc = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*ovrc));
    যদি (!ovrc) {
        SDL_free(ফলাফল);
        ফেরত ফাঁকা;
    }
    ফলাফল->internal = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    ফেরত ফলাফল;
}

স্থির bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_তথ্য * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    যদি (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        যদি (e != EVROverlayError_VROverlayError_None) {
            ফেরত OPENVR_SetOverlayError(e);
        }
        ফেরত true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    যদি (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        ফেরত true;
    }

    hotspot.v[0] = (দশমিক)ovrc->hot_x / (দশমিক)ovrc->w;
    hotspot.v[1] = (দশমিক)ovrc->hot_y / (দশমিক)ovrc->h;

    texture.handle = (শূন্য *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    যদি (e != EVROverlayError_VROverlayError_None) {
        ফেরত OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    যদি (e != EVROverlayError_VROverlayError_None) {
        ফেরত OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    যদি (e != EVROverlayError_VROverlayError_None) {
        ফেরত OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    যদি (e != EVROverlayError_VROverlayError_None) {
        ফেরত OPENVR_SetOverlayError(e);
    }

    ফেরত true;
}

স্থির শূন্য OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    যদি (cursor) {
        SDL_Cursor_তথ্য *ovrc = cursor->internal;
        যদি (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


স্থির bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    যদি (!global_openvr_driver) {
        ফেরত SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    যদি (videodata->bIconOverridden) {
        ফেরত SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (শূন্য *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    যদি (e != EVROverlayError_VROverlayError_None) {
        ফেরত OPENVR_SetOverlayError(e);
    }
    ফেরত true;
}

স্থির bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonid)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    অক্ষর empty = 0;
    অক্ষর * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    অক্ষর * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    অক্ষর * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    ফেরত true;
}

স্থির শূন্য InitializeMouseFunctions(শূন্য)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

স্থির শূন্য OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = (SDL_Video_তথ্য *)_this->internal;
    কাঠামো VREvent_t nEvent;
    যদি (videodata->overlayID) {
        যখন (videodata->oOverlay->Poll_পরবর্তী_Overlay_Event(videodata->overlayID, &nEvent, আকার(nEvent))) {
            নির্বাচন (nEvent.eventType) {
            ক্ষেত্র EVREventType_VREvent_ButtonPress:
            ক্ষেত্র EVREventType_VREvent_ButtonUnpress:
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.তথ্য.mouse.x, videodata->targh - nEvent.তথ্য.mouse.y, nEvent.তথ্য.mouse.button, 2);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.তথ্য.mouse.x, videodata->targh - nEvent.তথ্য.mouse.y, nEvent.তথ্য.mouse.button, 1);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.তথ্য.mouse.x, videodata->targh - nEvent.তথ্য.mouse.y, nEvent.তথ্য.mouse.button, 0);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_ScrollSmooth:
            ক্ষেত্র EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ফাঁকা, SDL_GLOBAL_MOUSE_ID, -nEvent.তথ্য.scroll.xdelta, nEvent.তথ্য.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                বিরতি;
            ক্ষেত্র EVREvent_Type_VREvent_Keyboard_Char_প্রবেশ:
                SDL_Send_Keyboard_Unicode_চাবি(SDL_GetTicksNS(), nEvent.তথ্য.keyboard.c_New_প্রবেশ[0]);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(ফাঁকা);
                বিরতি;
            ক্ষেত্র EVREventType_VREvent_OverlayClosed:
            ক্ষেত্র EVREventType_VREvent_Quit:
                SDL_SendQuit();
                বিরতি;
            }
        }
    }
}


স্থির SDL_VideoDevice *OPENVR_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *তথ্য;
    ধ্রুবক অক্ষর *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(ফাঁকা, 0, ফাঁকা);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (device) {
        তথ্য = (কাঠামো SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    } অন্যথা {
        তথ্য = ফাঁকা;
    }
    যদি (!তথ্য) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        ফেরত ফাঁকা;
    }
    device->internal = তথ্য;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    যদি (hint) {
        তথ্য->openVRLIB = SDL_LoadObject(hint);
    }
    যদি (!তথ্য->openVRLIB) {
        তথ্য->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    যদি (!তথ্য->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        যাও error;
    }

    তথ্য->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(তথ্য->openVRLIB, "VR_InitInternal");
    তথ্য->FN_VR_GetVRInitErrorAsEnglishDescription = (ধ্রুবক অক্ষর *(*)(EVRInitError error))SDL_LoadFunction(তথ্য->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    তথ্য->FN_VR_GetGenericInterface = (intptr_t (*)(ধ্রুবক অক্ষর *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(তথ্য->openVRLIB, "VR_GetGenericInterface");
    যদি (!তথ্য->FN_VR_InitInternal || !তথ্য->FN_VR_GetVRInitErrorAsEnglishDescription || !তথ্য->FN_VR_GetGenericInterface) {
        যাও error;
    }

    অক্ষর fnname[128];
    EVRInitError e;
    তথ্য->vrtoken = তথ্য->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    যদি (!তথ্য->vrtoken) {
        ধ্রুবক অক্ষর *err = "Can't get english description";
        যদি (তথ্য->FN_VR_GetVRInitErrorAsEnglishDescription != ফাঁকা)
            err = তথ্য->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        যাও error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    তথ্য->oSystem = (কাঠামো VR_IVRSystem_FnTable *)তথ্য->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    তথ্য->oOverlay = (কাঠামো VR_IVROverlay_FnTable *)তথ্য->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    তথ্য->o_প্রবেশ = (কাঠামো VR_IVRInput_FnTable *)তথ্য->FN_VR_GetGenericInterface(fnname, &e);

    যদি (!তথ্য->oOverlay || !তথ্য->oSystem || !তথ্য->o_প্রবেশ) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    অক্ষর *loadpath = 0;
    EVRInputError err;

    যদি (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } অন্যথা {
        ধ্রুবক অক্ষর *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    যদি (!loadpath) {
        যাও error;
    }

    err = তথ্য->o_প্রবেশ->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    যদি (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        যদি (hint) {
            যাও error;
        }
    } অন্যথা {
        যদি(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(তথ্য)) {
            যাও error;
        }
    }

    // Setup amount of available displays
    device->অঙ্ক_displays = 0;

    // Set device free function
    device->মুক্ত = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->SetDisplayMode = OPENVR_SetDisplayMode;
    device->CreateSDLWindow = OPENVR_CreateWindow;
    device->SetWindowTitle = OPENVR_SetWindowTitle;
    device->Set_Window_আকার = OPENVR_Set_Window_আকার;
    device->Get_Window_আকার_In_Pixels = OPENVR_Get_Window_আকার_In_Pixels;
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
#অন্যথা
#error Needs more work to support EGL
#endif
#অন্যথা
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

#যদি defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#অন্যথা
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

    ফেরত device;

error:
    OPENVR_Destroy(device);
    ফেরত ফাঁকা;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ফাঁকা, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

