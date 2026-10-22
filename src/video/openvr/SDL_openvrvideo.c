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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#اگر 0
#define DEBUG_OPENVR
#endif

#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../SDL_egl_c.h"
#شامل "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#شامل <SDL3/SDL_opengl.h>
#وگرنه
// Currently only EGL, not OpenGL, is supported on other platforms
#شامل <SDL3/SDL_opengles2.h>
#شامل <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#شامل "../windows/SDL_windowsopengl.h"
#شامل "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

ایستا bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path);
ایستا SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

ساختار SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وگرنه
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

ایستا تهی InitializeMouseFunctions(تهی);

ساختار SDL_CursorData
{
    unsigned texture_id_handle;
    صحیح hot_x, hot_y;
    صحیح w, h;
};

// GL Extensions for functions we will be using.
ایستا تهی (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ایستا تهی (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ایستا تهی (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
ایستا تهی (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
ایستا تهی (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
ایستا تهی (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ایستا تهی (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ایستا GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
ایستا GLenum (APIENTRY *ov_glGetError)(تهی);
ایستا تهی (APIENTRY *ov_glFlush)(تهی);
ایستا تهی (APIENTRY *ov_glFinish)(تهی);
ایستا تهی (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ایستا تهی (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ایستا تهی (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
ایستا تهی (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
ایستا تهی (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ثابت تهی *data);
ایستا تهی (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
ایستا تهی (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ایستا تهی (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
ایستا ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
ایستا تهی (APIENTRY *ov_glClear)(GLbitfield mask);
ایستا تهی (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ایستا تهی (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ایستا تهی (APIENTRY *ov_gl_Debug_Message_درج)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ثابت نویسه *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
ایستا PROC (*ov_wglGetProcAddress)(LPCSTR);
ایستا HGLRC (*ov_wglCreateContext)(HDC);
ایستا BOOL (*ov_wglDeleteContext)(HGLRC);
ایستا BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (تهی *)SDL_GL_GetProcAddress((#proc)+3); اگر (!proc) { failed_extension = (#proc)+3; } }

ایستا bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    اگر (!ov_glGetError) {
        ثابت نویسه * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_درج);
        اگر (failed_extension) {
            بازگشت SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    بازگشت true;
}

ایستا bool OPENVR_SetOverlayError(EVROverlayError e)
{
    انتخاب (e) {
#define CASE(X) حالت EVROverlayError_VROverlayError_##X: بازگشت SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(کلید_Too_Long);
    CASE(NameTooLong);
    CASE(کلید_In_Use);
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
    پیشفرض:
        بازگشت SDL_SetError("Unknown VROverlayError %d", e);
    }
}

ایستا bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

ایستا bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ثابت نویسه * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت نویسه * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت نویسه * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحیح width = hintWidth ? SDL_atoi(hintWidth) : 0;
    صحیح height = hintHeight ? SDL_atoi(hintHeight) : 0;
    صحیح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    اگر (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    اگر (fps) {
        display.desktop_mode.refresh_rate = fps;
    } وگرنه {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (نویسه *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    بازگشت true;
}

ایستا تهی OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ایستا تهی OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    اگر (data) {
        اگر (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

ایستا uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    صحیح w = surf->w;
    صحیح h = surf->h;
    صحیح pitch = surf->pitch;
    صحیح x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    برای(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        برای(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    بازگشت pxd;
}

ایستا bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    اگر (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    اگر (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        ساختار HmdVector2_t ms;
        صحیح status;

        اگر (videodata->fbo <= 0) {
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
        اگر (status != GL_FRAMEBUFFER_COMPLETE) {
            بازگشت SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (اعشاری)videodata->targw;
        ms.v[1] = (اعشاری)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    بازگشت true;
}

ایستا bool OPENVR_VirtualControllerRumble(تهی *userdata, Uint16 کم_frequency_rumble, Uint16 بالا_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    ثابت اعشاری k_flIntensity = 320.f; // Maximum frequency
    اعشاری fl_چپ_Frequency = (اعشاری)کم_frequency_rumble * k_flIntensity / 65535.f;
    اعشاری fl_راست_Frequency = (اعشاری)بالا_frequency_rumble * k_flIntensity / 65535.f;
    اعشاری flDurationSeconds = 2.f;
    اعشاری flAmplitude = 1.f;

    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[0], 0, flDurationSeconds, fl_چپ_Frequency, flAmplitude, 0);
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[1], 0, flDurationSeconds, fl_راست_Frequency, flAmplitude, 0);

    بازگشت true;
}

ایستا bool OPENVR_VirtualControllerRumbleTriggers(تهی *userdata, Uint16 چپ_rumble, Uint16 راست_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[0], 0, 0.1f, چپ_rumble, 1.0, 0);
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[1], 0, 0.1f, راست_rumble, 1.0, 0);
    بازگشت true;
}

ایستا تهی OPENVR_VirtualControllerUpdate(تهی *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    درون_داد_Digital_Action_Data_t digital_درون_داد_action;
    درون_داد_Analog_Action_Data_t analog_درون_داد_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->درون_داد_action_set;
    e = videodata->o_درون_داد->UpdateActionState(&actionSet, اندازه(actionSet), 1);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        بازگشت;
    }

    برای (صحیح d = 0; d < videodata->درون_داد_action_handles_buttons_شمار; d++)
    {
        اگر (videodata->درون_داد_action_handles_buttons[d] == k_ulInvalidActionHandle)
            ادامه;
        e = videodata->o_درون_داد->GetDigitalActionData(videodata->درون_داد_action_handles_buttons[d], &digital_درون_داد_action, اندازه(digital_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
        اگر (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            بازگشت;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_درون_داد_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_درون_داد->GetAnalogActionData(videodata->درون_داد_action_handles_axes[0], &analog_درون_داد_action, اندازه(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        بازگشت;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_درون_داد_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_درون_داد_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_درون_داد->GetAnalogActionData(videodata->درون_داد_action_handles_axes[1], &analog_درون_داد_action, اندازه(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        بازگشت;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_درون_داد_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_درون_داد_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_درون_داد->GetAnalogActionData(videodata->درون_داد_action_handles_axes[2], &analog_درون_داد_action, اندازه(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        بازگشت;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_چپ_TRIGGER, (Sint16)((analog_درون_داد_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_درون_داد->GetAnalogActionData(videodata->درون_داد_action_handles_axes[3], &analog_درون_داد_action, اندازه(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        بازگشت;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_راست_TRIGGER, (Sint16)((analog_درون_داد_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#اگر 0
    برای (a = 0; a < videodata->درون_داد_action_handles_axes_شمار; a++)
    {
        اعشاری xval = 0.0f;
        e = videodata->o_درون_داد->GetAnalogActionData(videodata->درون_داد_action_handles_axes[a], &analog_درون_داد_action, اندازه(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
        اگر (e) برو updatefail;
        xval = analog_درون_داد_action.x;
        اگر (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        اگر (a == SDL_GAMEPAD_AXIS_چپ_TRIGGER || a == SDL_GAMEPAD_AXIS_راست_TRIGGER)
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
    بازگشت;
}

ایستا bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    نویسه * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_شمار] = {
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
    نویسه * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    اگر ((e = videodata->o_درون_داد->GetActionSetHandle("/actions/virtualgamepad", &videodata->درون_داد_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        بازگشت SDL_SetError("Failed to get action set handle");
    }

    videodata->درون_داد_action_handles_buttons_شمار = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->درون_داد_action_handles_buttons = SDL_malloc(videodata->درون_داد_action_handles_buttons_شمار * اندازه(VRActionHandle_t));

    برای (صحیح i = 0; i < videodata->درون_داد_action_handles_buttons_شمار; i++)
    {
        e = videodata->o_درون_داد->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->درون_داد_action_handles_buttons[i]);
        اگر (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            بازگشت SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->درون_داد_action_handles_axes_شمار = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->درون_داد_action_handles_axes = SDL_malloc(videodata->درون_داد_action_handles_axes_شمار * اندازه(VRActionHandle_t));

    برای (صحیح i = 0; i < videodata->درون_داد_action_handles_axes_شمار; i++)
    {
        e = videodata->o_درون_داد->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->درون_داد_action_handles_axes[i]);
        اگر (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            بازگشت SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_درون_داد->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->درون_داد_action_handles_haptics[0]);
    e |= videodata->o_درون_داد->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->درون_داد_action_handles_haptics[1]);
    اگر (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        بازگشت SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_شمار;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_شمار;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    اگر (!virtual_id) {
        بازگشت SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    اگر (!videodata->virtual_joystick) {
        بازگشت SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->درون_داد_action_handles_buttons_شمار, videodata->درون_داد_action_handles_axes_شمار);
#endif

    بازگشت true;
}

ایستا bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    اگر (!OPENVR_InitExtensions(_this)) {
        بازگشت false;
    }

    // Generate the overlay.
    {
        ثابت نویسه * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        نویسه * cursorname = 0;
        اگر (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        اگر (!videodata->sOverlayName) {
            بازگشت false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        اگر (!cursorname) {
            بازگشت false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        اگر (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            بازگشت SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        اگر (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            بازگشت SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_عدد, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ثابت نویسه *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        اگر (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } وگرنه {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#اگر 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        برای (صحیح i = 0; i < اندازه(overlay_flags) * 8; ++i) {
            اگر (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت نویسه * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        اعشاری fWidth = hint ? (اعشاری)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ثابت نویسه * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        اعشاری fCursorWidth = hint ? (اعشاری)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ثابت نویسه * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        اگر (hint) {
            نویسه * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            اگر (err == EVROverlayError_VROverlayError_None) {
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

    اگر (!OPENVR_CheckRenderbuffer(_this)) {
        بازگشت false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    بازگشت true;
}


ایستا bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ایستا ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        صحیح error = ov_glGetError();
        اگر (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    اگر (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    بازگشت true;
}

ایستا bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    اگر (!ov_glGetError) {
        بازگشت true;
    }

    اگر (!videodata->is_buffer_rendering) {
        بازگشت true;
    }

#ifdef DEBUG_OPENVR
    {
        صحیح error = ov_glGetError();
        اگر (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    اگر (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ساختار Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (تهی *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    اگر (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    اگر (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_درج(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    بازگشت OPENVR_CheckRenderbuffer(_this);
}

ایستا تهی OPENVR_HandleResize(SDL_VideoDevice *_this, صحیح w, صحیح h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

ایستا bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    بازگشت true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
ایستا LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT پیام, WPARAM wParam, LPARAM lParam)
{
    انتخاب (پیام) {
    حالت WM_DESTROY:
        بازگشت 0;
    }
    بازگشت DefWindowProc(hwnd, پیام, wParam, lParam);
}

ایستا bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    اگر (path == پوچ) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    اگر (path == پوچ) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    اگر (!_this->gl_config.dll_handle) {
        بازگشت false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (ساختار SDL_GLDriverData *)SDL_calloc(1, اندازه(ساختار SDL_GLDriverData));
    اگر (!_this->gl_data) {
        بازگشت false;
    }
    _this->gl_config.driver_loaded = true;

    بازگشت true;
}

ایستا SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ثابت نویسه *proc)
{
    SDL_FunctionPointer result = پوچ;
    اگر (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        اگر (result) {
            بازگشت result;
        }
    }

    بازگشت SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

ایستا تهی OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ایستا SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint رقم_Extensions;
    صحیح i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(پوچ);
        wnd.hIcon = LoadIcon(پوچ, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(پوچ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = پوچ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, پوچ, پوچ, GetModuleHandle(پوچ), پوچ);

        پیام_2 پیام;
        وقتی (PeekMessage(&پیام, پوچ, 0, 0, PM_REMOVE)) {
            TranslateMessage(&پیام);
            DispatchMessage(&پیام);
        }

        videodata->hdc = GetDC(hwnd);

        ایستا  PIXELFORMATDESCRIPTOR pfd =
        {
            اندازه(PIXELFORMATDESCRIPTOR),
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
        اگر (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            بازگشت پوچ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        اگر (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            بازگشت پوچ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        اگر (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            بازگشت پوچ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        اگر (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            بازگشت پوچ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    اگر (i == 0) {
        بازگشت پوچ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_رقم_EXTENSIONS, &رقم_Extensions);
    برای (i = 0; i < رقم_Extensions; i++) {
        ثابت نویسه *ccc = (ثابت نویسه *)ov_glGetStringi(GL_EXTENSIONS, i);
        اگر (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, window)) {
            بازگشت پوچ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(اندازه(ساختار SDL_GLContextState));
    اگر (!result) {
        بازگشت پوچ;
    }
    result->hglrc = videodata->hglrc;
    بازگشت result;
}

ایستا bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    بازگشت true;
}

ایستا bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, صحیح interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    بازگشت true;
}

ایستا bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, صحیح *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (swapInterval)
        *swapInterval = videodata->swap_interval;
    وگرنه
        بازگشت SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    بازگشت true;
}

ایستا bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, پوچ);
    ov_wglDeleteContext(videodata->hglrc);
    بازگشت true;
}


#وگرنه

ایستا EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

ایستا bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=پوچ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    اگر (vd->eglDpy == 0) {
        بازگشت SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    اگر (!b) {
        بازگشت SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        صحیح err = eglGetError();
        اگر (err != EGL_SUCCESS) {
            بازگشت SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    اگر (!vd->eglCtx) {
        بازگشت SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    بازگشت true;
}

// Linux, EGL, etc.
ایستا bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ثابت نویسه *path)
{
    بازگشت SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

ایستا SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ثابت نویسه *proc)
{
    بازگشت SDL_EGL_GetProcAddress(proc);
}
ایستا تهی OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ایستا SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint رقم_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (!videodata->eglCtx) {
        اگر (!SDL_EGL_InitInternal(videodata)) {
            بازگشت پوچ;
        }
    }

    اگر (!OPENVR_InitExtensions(_this)) {
        بازگشت پوچ;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_رقم_EXTENSIONS, &رقم_Extensions);
    برای(صحیح i = 0; i < رقم_Extensions; i++) {
        ثابت نویسه * ccc = (ثابت نویسه *)ov_glGetStringi(GL_EXTENSIONS, i);
        اگر (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, window)) {
            بازگشت پوچ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    بازگشت videodata->eglCtx;
}

ایستا bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    بازگشت true;
}

ایستا bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, صحیح interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    بازگشت true;
}

ایستا bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, صحیح * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (swapInterval)
        *swapInterval = videodata->swap_interval;
    وگرنه
        بازگشت SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    بازگشت true;
}

ایستا bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    بازگشت true;
}

#endif

ایستا bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, اندازه(SDL_WindowData));
    اگر (data == پوچ) {
        بازگشت SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    بازگشت true;
}


ایستا تهی OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = پوچ;
}

ایستا تهی OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    اگر (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

ایستا تهی OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    اگر (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    اگر (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    اگر (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

ایستا تهی OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحیح *w, صحیح *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

ایستا تهی OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    اگر (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_درون_داد_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

ایستا تهی OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    بازگشت;
}

ایستا bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, window)) {
            بازگشت false;
        }
    }

    اگر (!OPENVR_ReleaseFrame(_this)) {
        بازگشت false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    اگر (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    اگر (!OPENVR_SetupFrame(_this, window)) {
        بازگشت false;
    }

    بازگشت true;
}

ایستا Uint8 OPENVR_MapMouseButton(صحیح btn)
{
    اگر (btn == EVRMouse_Button_VRMouse_Button_راست) {
        بازگشت SDL_BUTTON_راست;
    } وگرنه اگر (btn == EVRMouse_Button_VRMouse_Button_میانه) {
        بازگشت SDL_BUTTON_میانه;
    } وگرنه {
        بازگشت SDL_BUTTON_چپ;
    }
}

ایستا تهی OPENVR_HandleMouse(اعشاری x, اعشاری y, صحیح btn, صحیح evt)
{
    اگر (evt == 2) {
        SDL_SendMouseMotion(0, پوچ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وگرنه {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool down = (evt != 0);
        SDL_SendMouseButton(0, پوچ, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


ایستا bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    بازگشت true;
}

ایستا تهی OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        بازگشت;
    }
    EGamepad_Text_درون_داد_Mode درون_داد_mode;
    انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
    حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        درون_داد_mode = EGamepad_Text_درون_داد_Mode_k_EGamepad_Text_درون_داد_Mode_Password;
        بشکن;
    پیشفرض:
        درون_داد_mode = EGamepad_Text_درون_داد_Mode_k_EGamepad_Text_درون_داد_Mode_Normal;
        بشکن;
    }
    EGamepad_Text_درون_داد_سطر_Mode سطر_mode;
    اگر (SDL_Get_Text_درون_داد_Multiline(props)) {
        سطر_mode = EGamepad_Text_درون_داد_سطر_Mode_k_EGamepad_Text_درون_داد_سطر_Mode_Multiple_سطرها;
    } وگرنه {
        سطر_mode = EGamepad_Text_درون_داد_سطر_Mode_k_EGamepad_Text_درون_داد_سطر_Mode_Single_سطر;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           درون_داد_mode, سطر_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ایستا تهی OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ایستا SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, اندازه(SDL_Cursor));
    اگر (!result) {
        بازگشت پوچ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, اندازه(*ovrc));
    اگر (!ovrc) {
        SDL_free(result);
        بازگشت پوچ;
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

    بازگشت result;
}

ایستا bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    اگر (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        اگر (e != EVROverlayError_VROverlayError_None) {
            بازگشت OPENVR_SetOverlayError(e);
        }
        بازگشت true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    اگر (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        بازگشت true;
    }

    hotspot.v[0] = (اعشاری)ovrc->hot_x / (اعشاری)ovrc->w;
    hotspot.v[1] = (اعشاری)ovrc->hot_y / (اعشاری)ovrc->h;

    texture.handle = (تهی *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    اگر (e != EVROverlayError_VROverlayError_None) {
        بازگشت OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    اگر (e != EVROverlayError_VROverlayError_None) {
        بازگشت OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    اگر (e != EVROverlayError_VROverlayError_None) {
        بازگشت OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    اگر (e != EVROverlayError_VROverlayError_None) {
        بازگشت OPENVR_SetOverlayError(e);
    }

    بازگشت true;
}

ایستا تهی OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    اگر (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        اگر (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ایستا bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    اگر (!global_openvr_driver) {
        بازگشت SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    اگر (videodata->bIconOverridden) {
        بازگشت SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (تهی *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    اگر (e != EVROverlayError_VROverlayError_None) {
        بازگشت OPENVR_SetOverlayError(e);
    }
    بازگشت true;
}

ایستا bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    نویسه empty = 0;
    نویسه * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    نویسه * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    نویسه * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    بازگشت true;
}

ایستا تهی InitializeMouseFunctions(تهی)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ایستا تهی OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ساختار VREvent_t nEvent;
    اگر (videodata->overlayID) {
        وقتی (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, اندازه(nEvent))) {
            انتخاب (nEvent.eventType) {
            حالت EVREventType_VREvent_ButtonPress:
            حالت EVREventType_VREvent_ButtonUnpress:
                بشکن;
            حالت EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                بشکن;
            حالت EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                بشکن;
            حالت EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                بشکن;
            حالت EVREventType_VREvent_ScrollSmooth:
            حالت EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, پوچ, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                بشکن;
            حالت EVREvent_Type_VREvent_Keyboard_Char_درون_داد:
                SDL_Send_Keyboard_Unicode_کلید(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_درون_داد[0]);
                بشکن;
            حالت EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                بشکن;
            حالت EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(پوچ);
                بشکن;
            حالت EVREventType_VREvent_OverlayClosed:
            حالت EVREventType_VREvent_Quit:
                SDL_SendQuit();
                بشکن;
            }
        }
    }
}


ایستا SDL_VideoDevice *OPENVR_CreateDevice(تهی)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ثابت نویسه *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(پوچ, 0, پوچ);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, اندازه(SDL_VideoDevice));
    اگر (device) {
        data = (ساختار SDL_VideoData *)SDL_calloc(1, اندازه(SDL_VideoData));
    } وگرنه {
        data = پوچ;
    }
    اگر (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        بازگشت پوچ;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    اگر (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    اگر (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    اگر (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        برو error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت نویسه *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت نویسه *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    اگر (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        برو error;
    }

    نویسه fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    اگر (!data->vrtoken) {
        ثابت نویسه *err = "Can't get english description";
        اگر (data->FN_VR_GetVRInitErrorAsEnglishDescription != پوچ)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        برو error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (ساختار VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (ساختار VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_درون_داد = (ساختار VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    اگر (!data->oOverlay || !data->oSystem || !data->o_درون_داد) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    نویسه *loadpath = 0;
    EVRInputError err;

    اگر (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وگرنه {
        ثابت نویسه *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    اگر (!loadpath) {
        برو error;
    }

    err = data->o_درون_داد->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    اگر (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        اگر (hint) {
            برو error;
        }
    } وگرنه {
        اگر(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            برو error;
        }
    }

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->آزاد = OPENVR_Destroy;

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
#وگرنه
#error Needs more work to support EGL
#endif
#وگرنه
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

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وگرنه
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

    بازگشت device;

error:
    OPENVR_Destroy(device);
    بازگشت پوچ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, پوچ, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

