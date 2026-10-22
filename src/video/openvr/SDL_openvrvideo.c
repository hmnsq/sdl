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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#إذا 0
#define DEBUG_OPENVR
#endif

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ضمن <SDL3/SDL_opengl.h>
#وإلا
// Currently only EGL, not OpenGL, is supported on other platforms
#ضمن <SDL3/SDL_opengles2.h>
#ضمن <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#ضمن "../windows/SDL_windowsopengl.h"
#ضمن "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

ساكن bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path);
ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

بنية SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وإلا
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

ساكن فراغ InitializeMouseFunctions(فراغ);

بنية SDL_CursorData
{
    unsigned texture_id_handle;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

// GL Extensions for functions we will be using.
ساكن فراغ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساكن فراغ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساكن فراغ (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
ساكن فراغ (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
ساكن فراغ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساكن GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
ساكن GLenum (APIENTRY *ov_glGetError)(فراغ);
ساكن فراغ (APIENTRY *ov_glFlush)(فراغ);
ساكن فراغ (APIENTRY *ov_glFinish)(فراغ);
ساكن فراغ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
ساكن فراغ (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
ساكن فراغ (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ثابت فراغ *data);
ساكن فراغ (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
ساكن فراغ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساكن فراغ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
ساكن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
ساكن فراغ (APIENTRY *ov_glClear)(GLbitfield mask);
ساكن فراغ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساكن فراغ (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساكن فراغ (APIENTRY *ov_gl_Debug_Message_قىستۇرۇش)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ثابت حرف *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
ساكن PROC (*ov_wglGetProcAddress)(LPCSTR);
ساكن HGLRC (*ov_wglCreateContext)(HDC);
ساكن BOOL (*ov_wglDeleteContext)(HGLRC);
ساكن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (فراغ *)SDL_GL_GetProcAddress((#proc)+3); إذا (!proc) { failed_extension = (#proc)+3; } }

ساكن bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    إذا (!ov_glGetError) {
        ثابت حرف * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_قىستۇرۇش);
        إذا (failed_extension) {
            أرجع SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    أرجع true;
}

ساكن bool OPENVR_SetOverlayError(EVROverlayError e)
{
    بدل (e) {
#define CASE(X) حالة EVROverlayError_VROverlayError_##X: أرجع SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(ئاچقۇچ_Too_Long);
    CASE(NameTooLong);
    CASE(ئاچقۇچ_In_Use);
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
    افتراضي:
        أرجع SDL_SetError("Unknown VROverlayError %d", e);
    }
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

ساكن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ثابت حرف * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحيح width = hintWidth ? SDL_atoi(hintWidth) : 0;
    صحيح height = hintHeight ? SDL_atoi(hintHeight) : 0;
    صحيح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    إذا (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    إذا (fps) {
        display.desktop_mode.refresh_rate = fps;
    } وإلا {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    أرجع true;
}

ساكن فراغ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساكن فراغ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    إذا (data) {
        إذا (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

ساكن uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    صحيح w = surf->w;
    صحيح h = surf->h;
    صحيح pitch = surf->pitch;
    صحيح x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    لكل(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        لكل(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    أرجع pxd;
}

ساكن bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    إذا (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    إذا (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        بنية HmdVector2_t ms;
        صحيح status;

        إذا (videodata->fbo <= 0) {
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
        إذا (status != GL_FRAMEBUFFER_COMPLETE) {
            أرجع SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (عائم)videodata->targw;
        ms.v[1] = (عائم)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumble(فراغ *userdata, Uint16 تۆۋەن_frequency_rumble, Uint16 يۇقىرى_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    ثابت عائم k_flIntensity = 320.f; // Maximum frequency
    عائم fl_سول_Frequency = (عائم)تۆۋەن_frequency_rumble * k_flIntensity / 65535.f;
    عائم fl_ئوڭ_Frequency = (عائم)يۇقىرى_frequency_rumble * k_flIntensity / 65535.f;
    عائم flDurationSeconds = 2.f;
    عائم flAmplitude = 1.f;

    videodata->o_كىرگۈزۈش->TriggerHapticVibrationAction(videodata->كىرگۈزۈش_action_handles_haptics[0], 0, flDurationSeconds, fl_سول_Frequency, flAmplitude, 0);
    videodata->o_كىرگۈزۈش->TriggerHapticVibrationAction(videodata->كىرگۈزۈش_action_handles_haptics[1], 0, flDurationSeconds, fl_ئوڭ_Frequency, flAmplitude, 0);

    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumbleTriggers(فراغ *userdata, Uint16 سول_rumble, Uint16 ئوڭ_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_كىرگۈزۈش->TriggerHapticVibrationAction(videodata->كىرگۈزۈش_action_handles_haptics[0], 0, 0.1f, سول_rumble, 1.0, 0);
    videodata->o_كىرگۈزۈش->TriggerHapticVibrationAction(videodata->كىرگۈزۈش_action_handles_haptics[1], 0, 0.1f, ئوڭ_rumble, 1.0, 0);
    أرجع true;
}

ساكن فراغ OPENVR_VirtualControllerUpdate(فراغ *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    كىرگۈزۈش_Digital_Action_Data_t digital_كىرگۈزۈش_action;
    كىرگۈزۈش_Analog_Action_Data_t analog_كىرگۈزۈش_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->كىرگۈزۈش_action_set;
    e = videodata->o_كىرگۈزۈش->UpdateActionState(&actionSet, حجم(actionSet), 1);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        أرجع;
    }

    لكل (صحيح d = 0; d < videodata->كىرگۈزۈش_action_handles_buttons_سانى; d++)
    {
        إذا (videodata->كىرگۈزۈش_action_handles_buttons[d] == k_ulInvalidActionHandle)
            استمر;
        e = videodata->o_كىرگۈزۈش->GetDigitalActionData(videodata->كىرگۈزۈش_action_handles_buttons[d], &digital_كىرگۈزۈش_action, حجم(digital_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
        إذا (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            أرجع;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_كىرگۈزۈش_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_كىرگۈزۈش->GetAnalogActionData(videodata->كىرگۈزۈش_action_handles_axes[0], &analog_كىرگۈزۈش_action, حجم(analog_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        أرجع;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_كىرگۈزۈش_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_كىرگۈزۈش_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_كىرگۈزۈش->GetAnalogActionData(videodata->كىرگۈزۈش_action_handles_axes[1], &analog_كىرگۈزۈش_action, حجم(analog_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        أرجع;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_كىرگۈزۈش_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_كىرگۈزۈش_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_كىرگۈزۈش->GetAnalogActionData(videodata->كىرگۈزۈش_action_handles_axes[2], &analog_كىرگۈزۈش_action, حجم(analog_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        أرجع;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_سول_TRIGGER, (Sint16)((analog_كىرگۈزۈش_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_كىرگۈزۈش->GetAnalogActionData(videodata->كىرگۈزۈش_action_handles_axes[3], &analog_كىرگۈزۈش_action, حجم(analog_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        أرجع;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_ئوڭ_TRIGGER, (Sint16)((analog_كىرگۈزۈش_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#إذا 0
    لكل (a = 0; a < videodata->كىرگۈزۈش_action_handles_axes_سانى; a++)
    {
        عائم xval = 0.0f;
        e = videodata->o_كىرگۈزۈش->GetAnalogActionData(videodata->كىرگۈزۈش_action_handles_axes[a], &analog_كىرگۈزۈش_action, حجم(analog_كىرگۈزۈش_action), k_ul_Invalid_كىرگۈزۈش_قىممەت_Handle);
        إذا (e) اذهب updatefail;
        xval = analog_كىرگۈزۈش_action.x;
        إذا (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        إذا (a == SDL_GAMEPAD_AXIS_سول_TRIGGER || a == SDL_GAMEPAD_AXIS_ئوڭ_TRIGGER)
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
    أرجع;
}

ساكن bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    حرف * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_سانى] = {
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
    حرف * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    إذا ((e = videodata->o_كىرگۈزۈش->GetActionSetHandle("/actions/virtualgamepad", &videodata->كىرگۈزۈش_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        أرجع SDL_SetError("Failed to get action set handle");
    }

    videodata->كىرگۈزۈش_action_handles_buttons_سانى = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->كىرگۈزۈش_action_handles_buttons = SDL_malloc(videodata->كىرگۈزۈش_action_handles_buttons_سانى * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->كىرگۈزۈش_action_handles_buttons_سانى; i++)
    {
        e = videodata->o_كىرگۈزۈش->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->كىرگۈزۈش_action_handles_buttons[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            أرجع SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->كىرگۈزۈش_action_handles_axes_سانى = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->كىرگۈزۈش_action_handles_axes = SDL_malloc(videodata->كىرگۈزۈش_action_handles_axes_سانى * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->كىرگۈزۈش_action_handles_axes_سانى; i++)
    {
        e = videodata->o_كىرگۈزۈش->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->كىرگۈزۈش_action_handles_axes[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            أرجع SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_كىرگۈزۈش->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->كىرگۈزۈش_action_handles_haptics[0]);
    e |= videodata->o_كىرگۈزۈش->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->كىرگۈزۈش_action_handles_haptics[1]);
    إذا (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        أرجع SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_سانى;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_سانى;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    إذا (!virtual_id) {
        أرجع SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    إذا (!videodata->virtual_joystick) {
        أرجع SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->كىرگۈزۈش_action_handles_buttons_سانى, videodata->كىرگۈزۈش_action_handles_axes_سانى);
#endif

    أرجع true;
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع false;
    }

    // Generate the overlay.
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        حرف * cursorname = 0;
        إذا (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        إذا (!videodata->sOverlayName) {
            أرجع false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        إذا (!cursorname) {
            أرجع false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        إذا (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        إذا (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_سان_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_سان, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ثابت حرف *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        إذا (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } وإلا {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#إذا 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        لكل (صحيح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            إذا (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        عائم fWidth = hint ? (عائم)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        عائم fCursorWidth = hint ? (عائم)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        إذا (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            إذا (err == EVROverlayError_VROverlayError_None) {
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

    إذا (!OPENVR_CheckRenderbuffer(_this)) {
        أرجع false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    أرجع true;
}


ساكن bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ساكن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    إذا (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    أرجع true;
}

ساكن bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    إذا (!ov_glGetError) {
        أرجع true;
    }

    إذا (!videodata->is_buffer_rendering) {
        أرجع true;
    }

#ifdef DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    إذا (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        بنية Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (فراغ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    إذا (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    إذا (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_قىستۇرۇش(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    أرجع OPENVR_CheckRenderbuffer(_this);
}

ساكن فراغ OPENVR_HandleResize(SDL_VideoDevice *_this, صحيح w, صحيح h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

ساكن bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    أرجع true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
ساكن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT ئۇچۇر, WPARAM wParam, LPARAM lParam)
{
    بدل (ئۇچۇر) {
    حالة WM_DESTROY:
        أرجع 0;
    }
    أرجع DefWindowProc(hwnd, ئۇچۇر, wParam, lParam);
}

ساكن bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path)
{
    إذا (path == عدم) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    إذا (path == عدم) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (بنية SDL_GLDriverData *)SDL_calloc(1, حجم(بنية SDL_GLDriverData));
    إذا (!_this->gl_data) {
        أرجع false;
    }
    _this->gl_config.driver_loaded = true;

    أرجع true;
}

ساكن SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_FunctionPointer result = عدم;
    إذا (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        إذا (result) {
            أرجع result;
        }
    }

    أرجع SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

ساكن فراغ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint رەقەم_Extensions;
    صحيح i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(عدم);
        wnd.hIcon = LoadIcon(عدم, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(عدم, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = عدم;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, عدم, عدم, GetModuleHandle(عدم), عدم);

        ئۇچۇر_2 ئۇچۇر;
        طالما (PeekMessage(&ئۇچۇر, عدم, 0, 0, PM_REMOVE)) {
            TranslateMessage(&ئۇچۇر);
            DispatchMessage(&ئۇچۇر);
        }

        videodata->hdc = GetDC(hwnd);

        ساكن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
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
        إذا (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            أرجع عدم;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        إذا (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            أرجع عدم;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        إذا (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            أرجع عدم;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        إذا (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            أرجع عدم;
        }
    }

    i = OPENVR_InitExtensions(_this);
    إذا (i == 0) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_رەقەم_EXTENSIONS, &رەقەم_Extensions);
    لكل (i = 0; i < رەقەم_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, window)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(حجم(بنية SDL_GLContextState));
    إذا (!result) {
        أرجع عدم;
    }
    result->hglrc = videodata->hglrc;
    أرجع result;
}

ساكن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    أرجع true;
}

ساكن bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    أرجع true;
}

ساكن bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, صحيح *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (swapInterval)
        *swapInterval = videodata->swap_interval;
    وإلا
        أرجع SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, عدم);
    ov_wglDeleteContext(videodata->hglrc);
    أرجع true;
}


#وإلا

ساكن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

ساكن bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=عدم;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    إذا (vd->eglDpy == 0) {
        أرجع SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    إذا (!b) {
        أرجع SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        صحيح err = eglGetError();
        إذا (err != EGL_SUCCESS) {
            أرجع SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    إذا (!vd->eglCtx) {
        أرجع SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    أرجع true;
}

// Linux, EGL, etc.
ساكن bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path)
{
    أرجع SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

ساكن SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_GetProcAddress(proc);
}
ساكن فراغ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساكن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint رەقەم_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (!videodata->eglCtx) {
        إذا (!SDL_EGL_InitInternal(videodata)) {
            أرجع عدم;
        }
    }

    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_رەقەم_EXTENSIONS, &رەقەم_Extensions);
    لكل(صحيح i = 0; i < رەقەم_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, window)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    أرجع videodata->eglCtx;
}

ساكن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    أرجع true;
}

ساكن bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    أرجع true;
}

ساكن bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, صحيح * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (swapInterval)
        *swapInterval = videodata->swap_interval;
    وإلا
        أرجع SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    أرجع true;
}

#endif

ساكن bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, حجم(SDL_WindowData));
    إذا (data == عدم) {
        أرجع SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    أرجع true;
}


ساكن فراغ OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = عدم;
}

ساكن فراغ OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    إذا (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

ساكن فراغ OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    إذا (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    إذا (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    إذا (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

ساكن فراغ OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحيح *w, صحيح *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

ساكن فراغ OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    إذا (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_كىرگۈزۈش_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

ساكن فراغ OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    أرجع;
}

ساكن bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, window)) {
            أرجع false;
        }
    }

    إذا (!OPENVR_ReleaseFrame(_this)) {
        أرجع false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    إذا (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    إذا (!OPENVR_SetupFrame(_this, window)) {
        أرجع false;
    }

    أرجع true;
}

ساكن Uint8 OPENVR_MapMouseButton(صحيح btn)
{
    إذا (btn == EVRMouse_Button_VRMouse_Button_ئوڭ) {
        أرجع SDL_BUTTON_ئوڭ;
    } وإلا إذا (btn == EVRMouse_Button_VRMouse_Button_ئوتتۇرا) {
        أرجع SDL_BUTTON_ئوتتۇرا;
    } وإلا {
        أرجع SDL_BUTTON_سول;
    }
}

ساكن فراغ OPENVR_HandleMouse(عائم x, عائم y, صحيح btn, صحيح evt)
{
    إذا (evt == 2) {
        SDL_SendMouseMotion(0, عدم, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وإلا {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool down = (evt != 0);
        SDL_SendMouseButton(0, عدم, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


ساكن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

ساكن فراغ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        أرجع;
    }
    EGamepad_Text_كىرگۈزۈش_Mode كىرگۈزۈش_mode;
    بدل (SDL_Get_Text_كىرگۈزۈش_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    حالة SDL_TEXTINPUT_TYPE_سان_PASSWORD_HIDDEN:
        كىرگۈزۈش_mode = EGamepad_Text_كىرگۈزۈش_Mode_k_EGamepad_Text_كىرگۈزۈش_Mode_Password;
        اكسر;
    افتراضي:
        كىرگۈزۈش_mode = EGamepad_Text_كىرگۈزۈش_Mode_k_EGamepad_Text_كىرگۈزۈش_Mode_Normal;
        اكسر;
    }
    EGamepad_Text_كىرگۈزۈش_قۇر_Mode قۇر_mode;
    إذا (SDL_Get_Text_كىرگۈزۈش_Multiline(props)) {
        قۇر_mode = EGamepad_Text_كىرگۈزۈش_قۇر_Mode_k_EGamepad_Text_كىرگۈزۈش_قۇر_Mode_Multiple_قۇرلار;
    } وإلا {
        قۇر_mode = EGamepad_Text_كىرگۈزۈش_قۇر_Mode_k_EGamepad_Text_كىرگۈزۈش_قۇر_Mode_Single_قۇر;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           كىرگۈزۈش_mode, قۇر_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساكن فراغ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساكن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (!result) {
        أرجع عدم;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, حجم(*ovrc));
    إذا (!ovrc) {
        SDL_free(result);
        أرجع عدم;
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

    أرجع result;
}

ساكن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    إذا (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        إذا (e != EVROverlayError_VROverlayError_None) {
            أرجع OPENVR_SetOverlayError(e);
        }
        أرجع true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    إذا (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        أرجع true;
    }

    hotspot.v[0] = (عائم)ovrc->hot_x / (عائم)ovrc->w;
    hotspot.v[1] = (عائم)ovrc->hot_y / (عائم)ovrc->h;

    texture.handle = (فراغ *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_SetOverlayError(e);
    }

    أرجع true;
}

ساكن فراغ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    إذا (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        إذا (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساكن bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    إذا (!global_openvr_driver) {
        أرجع SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    إذا (videodata->bIconOverridden) {
        أرجع SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (فراغ *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_SetOverlayError(e);
    }
    أرجع true;
}

ساكن bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    حرف empty = 0;
    حرف * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    حرف * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    أرجع true;
}

ساكن فراغ InitializeMouseFunctions(فراغ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ساكن فراغ OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    بنية VREvent_t nEvent;
    إذا (videodata->overlayID) {
        طالما (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, حجم(nEvent))) {
            بدل (nEvent.eventType) {
            حالة EVREventType_VREvent_ButtonPress:
            حالة EVREventType_VREvent_ButtonUnpress:
                اكسر;
            حالة EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                اكسر;
            حالة EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                اكسر;
            حالة EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                اكسر;
            حالة EVREventType_VREvent_ScrollSmooth:
            حالة EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, عدم, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                اكسر;
            حالة EVREvent_Type_VREvent_Keyboard_Char_كىرگۈزۈش:
                SDL_Send_Keyboard_Unicode_ئاچقۇچ(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_كىرگۈزۈش[0]);
                اكسر;
            حالة EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                اكسر;
            حالة EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(عدم);
                اكسر;
            حالة EVREventType_VREvent_OverlayClosed:
            حالة EVREventType_VREvent_Quit:
                SDL_SendQuit();
                اكسر;
            }
        }
    }
}


ساكن SDL_VideoDevice *OPENVR_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ثابت حرف *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(عدم, 0, عدم);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        data = (بنية SDL_VideoData *)SDL_calloc(1, حجم(SDL_VideoData));
    } وإلا {
        data = عدم;
    }
    إذا (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        أرجع عدم;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    إذا (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    إذا (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    إذا (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        اذهب error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    إذا (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        اذهب error;
    }

    حرف fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    إذا (!data->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        إذا (data->FN_VR_GetVRInitErrorAsEnglishDescription != عدم)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        اذهب error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (بنية VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (بنية VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_كىرگۈزۈش = (بنية VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    إذا (!data->oOverlay || !data->oSystem || !data->o_كىرگۈزۈش) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    إذا (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وإلا {
        ثابت حرف *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    إذا (!loadpath) {
        اذهب error;
    }

    err = data->o_كىرگۈزۈش->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    إذا (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        إذا (hint) {
            اذهب error;
        }
    } وإلا {
        إذا(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            اذهب error;
        }
    }

    // Setup amount of available displays
    device->رەقەم_displays = 0;

    // Set device free function
    device->حرر = OPENVR_Destroy;

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
#وإلا
#error Needs more work to support EGL
#endif
#وإلا
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

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وإلا
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

    أرجع device;

error:
    OPENVR_Destroy(device);
    أرجع عدم;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, عدم, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

