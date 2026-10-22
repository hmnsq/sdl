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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#जर 0
#define DEBUG_OPENVR
#endif

#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../SDL_egl_c.h"
#अन्तर्भाव "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#अन्तर्भाव <SDL3/SDL_opengl.h>
#अन्यथा
// Currently only EGL, not OpenGL, is supported on other platforms
#अन्तर्भाव <SDL3/SDL_opengles2.h>
#अन्तर्भाव <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#अन्तर्भाव "../windows/SDL_windowsopengl.h"
#अन्तर्भाव "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

स्थिर bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path);
स्थिर SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

संरचना SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#अन्यथा
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

स्थिर शून्य InitializeMouseFunctions(शून्य);

संरचना SDL_CursorData
{
    अचिन्हित texture_id_handle;
    पूर्णांक hot_x, hot_y;
    पूर्णांक w, h;
};

// GL Extensions for functions we will be using.
स्थिर शून्य (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
स्थिर शून्य (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
स्थिर शून्य (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
स्थिर शून्य (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
स्थिर शून्य (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
स्थिर शून्य (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
स्थिर शून्य (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
स्थिर GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
स्थिर GLenum (APIENTRY *ov_glGetError)(शून्य);
स्थिर शून्य (APIENTRY *ov_glFlush)(शून्य);
स्थिर शून्य (APIENTRY *ov_glFinish)(शून्य);
स्थिर शून्य (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
स्थिर शून्य (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
स्थिर शून्य (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
स्थिर शून्य (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
स्थिर शून्य (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, स्थिरांक शून्य *data);
स्थिर शून्य (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
स्थिर शून्य (APIENTRY *ov_glDrawBuffers)(GLsizei n, स्थिरांक GLenum *bufs);
स्थिर शून्य (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
स्थिर स्थिरांक GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
स्थिर शून्य (APIENTRY *ov_glClear)(GLbitfield mask);
स्थिर शून्य (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
स्थिर शून्य (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
स्थिर शून्य (APIENTRY *ov_gl_Debug_Message_घाला)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, स्थिरांक अक्षर *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
स्थिर PROC (*ov_wglGetProcAddress)(LPCSTR);
स्थिर HGLRC (*ov_wglCreateContext)(HDC);
स्थिर BOOL (*ov_wglDeleteContext)(HGLRC);
स्थिर BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (शून्य *)SDL_GL_GetProcAddress((#proc)+3); जर (!proc) { failed_extension = (#proc)+3; } }

स्थिर bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    जर (!ov_glGetError) {
        स्थिरांक अक्षर * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_घाला);
        जर (failed_extension) {
            परत SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    परत true;
}

स्थिर bool OPENVR_SetOverlayError(EVROverlayError e)
{
    निवड (e) {
#define CASE(X) स्थिती EVROverlayError_VROverlayError_##X: परत SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(किल्ली_Too_Long);
    CASE(NameTooLong);
    CASE(किल्ली_In_Use);
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
    पूर्वनिर्धारित:
        परत SDL_SetError("Unknown VROverlayError %d", e);
    }
}

स्थिर bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

स्थिर bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    स्थिरांक अक्षर * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    स्थिरांक अक्षर * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    स्थिरांक अक्षर * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    पूर्णांक width = hintWidth ? SDL_atoi(hintWidth) : 0;
    पूर्णांक height = hintHeight ? SDL_atoi(hintHeight) : 0;
    पूर्णांक fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    जर (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    जर (fps) {
        display.desktop_mode.refresh_rate = fps;
    } अन्यथा {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (अक्षर *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    परत true;
}

स्थिर शून्य OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

स्थिर शून्य OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    जर (data) {
        जर (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    पूर्णांक w = surf->w;
    पूर्णांक h = surf->h;
    पूर्णांक pitch = surf->pitch;
    पूर्णांक x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    साठी(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        साठी(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    परत pxd;
}

स्थिर bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    जर (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    जर (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        संरचना HmdVector2_t ms;
        पूर्णांक status;

        जर (videodata->fbo <= 0) {
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
        जर (status != GL_FRAMEBUFFER_COMPLETE) {
            परत SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (दशांश)videodata->targw;
        ms.v[1] = (दशांश)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    परत true;
}

स्थिर bool OPENVR_VirtualControllerRumble(शून्य *userdata, Uint16 खालचा_frequency_rumble, Uint16 वरचा_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    स्थिरांक दशांश k_flIntensity = 320.f; // Maximum frequency
    दशांश fl_डावा_Frequency = (दशांश)खालचा_frequency_rumble * k_flIntensity / 65535.f;
    दशांश fl_उजवा_Frequency = (दशांश)वरचा_frequency_rumble * k_flIntensity / 65535.f;
    दशांश flDurationSeconds = 2.f;
    दशांश flAmplitude = 1.f;

    videodata->o_आदान->TriggerHapticVibrationAction(videodata->आदान_action_handles_haptics[0], 0, flDurationSeconds, fl_डावा_Frequency, flAmplitude, 0);
    videodata->o_आदान->TriggerHapticVibrationAction(videodata->आदान_action_handles_haptics[1], 0, flDurationSeconds, fl_उजवा_Frequency, flAmplitude, 0);

    परत true;
}

स्थिर bool OPENVR_VirtualControllerRumbleTriggers(शून्य *userdata, Uint16 डावा_rumble, Uint16 उजवा_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_आदान->TriggerHapticVibrationAction(videodata->आदान_action_handles_haptics[0], 0, 0.1f, डावा_rumble, 1.0, 0);
    videodata->o_आदान->TriggerHapticVibrationAction(videodata->आदान_action_handles_haptics[1], 0, 0.1f, उजवा_rumble, 1.0, 0);
    परत true;
}

स्थिर शून्य OPENVR_VirtualControllerUpdate(शून्य *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    आदान_Digital_Action_Data_t digital_आदान_action;
    आदान_Analog_Action_Data_t analog_आदान_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->आदान_action_set;
    e = videodata->o_आदान->UpdateActionState(&actionSet, आकार(actionSet), 1);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        परत;
    }

    साठी (पूर्णांक d = 0; d < videodata->आदान_action_handles_buttons_मोजणी; d++)
    {
        जर (videodata->आदान_action_handles_buttons[d] == k_ulInvalidActionHandle)
            सुरूठेवा;
        e = videodata->o_आदान->GetDigitalActionData(videodata->आदान_action_handles_buttons[d], &digital_आदान_action, आकार(digital_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
        जर (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            परत;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_आदान_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_आदान->GetAnalogActionData(videodata->आदान_action_handles_axes[0], &analog_आदान_action, आकार(analog_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        परत;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_आदान_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_आदान_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_आदान->GetAnalogActionData(videodata->आदान_action_handles_axes[1], &analog_आदान_action, आकार(analog_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        परत;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_आदान_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_आदान_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_आदान->GetAnalogActionData(videodata->आदान_action_handles_axes[2], &analog_आदान_action, आकार(analog_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        परत;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_डावा_TRIGGER, (Sint16)((analog_आदान_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_आदान->GetAnalogActionData(videodata->आदान_action_handles_axes[3], &analog_आदान_action, आकार(analog_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        परत;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_उजवा_TRIGGER, (Sint16)((analog_आदान_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#जर 0
    साठी (a = 0; a < videodata->आदान_action_handles_axes_मोजणी; a++)
    {
        दशांश xval = 0.0f;
        e = videodata->o_आदान->GetAnalogActionData(videodata->आदान_action_handles_axes[a], &analog_आदान_action, आकार(analog_आदान_action), k_ul_Invalid_आदान_मूल्य_Handle);
        जर (e) जा updatefail;
        xval = analog_आदान_action.x;
        जर (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        जर (a == SDL_GAMEPAD_AXIS_डावा_TRIGGER || a == SDL_GAMEPAD_AXIS_उजवा_TRIGGER)
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
    परत;
}

स्थिर bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    अक्षर * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_मोजणी] = {
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
    अक्षर * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    जर ((e = videodata->o_आदान->GetActionSetHandle("/actions/virtualgamepad", &videodata->आदान_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        परत SDL_SetError("Failed to get action set handle");
    }

    videodata->आदान_action_handles_buttons_मोजणी = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->आदान_action_handles_buttons = SDL_malloc(videodata->आदान_action_handles_buttons_मोजणी * आकार(VRActionHandle_t));

    साठी (पूर्णांक i = 0; i < videodata->आदान_action_handles_buttons_मोजणी; i++)
    {
        e = videodata->o_आदान->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->आदान_action_handles_buttons[i]);
        जर (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            परत SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->आदान_action_handles_axes_मोजणी = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->आदान_action_handles_axes = SDL_malloc(videodata->आदान_action_handles_axes_मोजणी * आकार(VRActionHandle_t));

    साठी (पूर्णांक i = 0; i < videodata->आदान_action_handles_axes_मोजणी; i++)
    {
        e = videodata->o_आदान->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->आदान_action_handles_axes[i]);
        जर (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            परत SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_आदान->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->आदान_action_handles_haptics[0]);
    e |= videodata->o_आदान->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->आदान_action_handles_haptics[1]);
    जर (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        परत SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_मोजणी;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_मोजणी;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    जर (!virtual_id) {
        परत SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    जर (!videodata->virtual_joystick) {
        परत SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->आदान_action_handles_buttons_मोजणी, videodata->आदान_action_handles_axes_मोजणी);
#endif

    परत true;
}

स्थिर bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    जर (!OPENVR_InitExtensions(_this)) {
        परत false;
    }

    // Generate the overlay.
    {
        स्थिरांक अक्षर * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        अक्षर * cursorname = 0;
        जर (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        जर (!videodata->sOverlayName) {
            परत false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        जर (!cursorname) {
            परत false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        जर (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            परत SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        जर (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            परत SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_संख्या, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        स्थिरांक अक्षर *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        जर (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } अन्यथा {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#जर 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        साठी (पूर्णांक i = 0; i < आकार(overlay_flags) * 8; ++i) {
            जर (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        स्थिरांक अक्षर * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        दशांश fWidth = hint ? (दशांश)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        स्थिरांक अक्षर * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        दशांश fCursorWidth = hint ? (दशांश)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        स्थिरांक अक्षर * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        जर (hint) {
            अक्षर * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            जर (err == EVROverlayError_VROverlayError_None) {
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

    जर (!OPENVR_CheckRenderbuffer(_this)) {
        परत false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    परत true;
}


स्थिर bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    स्थिर स्थिरांक GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        पूर्णांक error = ov_glGetError();
        जर (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    जर (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    परत true;
}

स्थिर bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    जर (!ov_glGetError) {
        परत true;
    }

    जर (!videodata->is_buffer_rendering) {
        परत true;
    }

#ifdef DEBUG_OPENVR
    {
        पूर्णांक error = ov_glGetError();
        जर (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    जर (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        संरचना Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (शून्य *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    जर (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    जर (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_घाला(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    परत OPENVR_CheckRenderbuffer(_this);
}

स्थिर शून्य OPENVR_HandleResize(SDL_VideoDevice *_this, पूर्णांक w, पूर्णांक h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

स्थिर bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    परत true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
स्थिर LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam)
{
    निवड (संदेश) {
    स्थिती WM_DESTROY:
        परत 0;
    }
    परत DefWindowProc(hwnd, संदेश, wParam, lParam);
}

स्थिर bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path)
{
    जर (path == रिक्त) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    जर (path == रिक्त) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    जर (!_this->gl_config.dll_handle) {
        परत false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (संरचना SDL_GLDriverData *)SDL_calloc(1, आकार(संरचना SDL_GLDriverData));
    जर (!_this->gl_data) {
        परत false;
    }
    _this->gl_config.driver_loaded = true;

    परत true;
}

स्थिर SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिरांक अक्षर *proc)
{
    SDL_FunctionPointer result = रिक्त;
    जर (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        जर (result) {
            परत result;
        }
    }

    परत SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

स्थिर शून्य OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

स्थिर SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint अंक_Extensions;
    पूर्णांक i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(रिक्त);
        wnd.hIcon = LoadIcon(रिक्त, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(रिक्त, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = रिक्त;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, रिक्त, रिक्त, GetModuleHandle(रिक्त), रिक्त);

        संदेश_2 संदेश;
        पर्यंत (PeekMessage(&संदेश, रिक्त, 0, 0, PM_REMOVE)) {
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
        }

        videodata->hdc = GetDC(hwnd);

        स्थिर  PIXELFORMATDESCRIPTOR pfd =
        {
            आकार(PIXELFORMATDESCRIPTOR),
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
        जर (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            परत रिक्त;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        जर (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            परत रिक्त;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        जर (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            परत रिक्त;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        जर (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            परत रिक्त;
        }
    }

    i = OPENVR_InitExtensions(_this);
    जर (i == 0) {
        परत रिक्त;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    साठी (i = 0; i < अंक_Extensions; i++) {
        स्थिरांक अक्षर *ccc = (स्थिरांक अक्षर *)ov_glGetStringi(GL_EXTENSIONS, i);
        जर (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    जर (!videodata->bDidCreateOverlay) {
        जर (!OPENVR_InitializeOverlay(_this, window)) {
            परत रिक्त;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(आकार(संरचना SDL_GLContextState));
    जर (!result) {
        परत रिक्त;
    }
    result->hglrc = videodata->hglrc;
    परत result;
}

स्थिर bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    परत true;
}

स्थिर bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    परत true;
}

स्थिर bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        परत SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    परत true;
}

स्थिर bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, रिक्त);
    ov_wglDeleteContext(videodata->hglrc);
    परत true;
}


#अन्यथा

स्थिर EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

स्थिर bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=रिक्त;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    जर (vd->eglDpy == 0) {
        परत SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    जर (!b) {
        परत SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        पूर्णांक err = eglGetError();
        जर (err != EGL_SUCCESS) {
            परत SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    जर (!vd->eglCtx) {
        परत SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    परत true;
}

// Linux, EGL, etc.
स्थिर bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path)
{
    परत SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

स्थिर SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, स्थिरांक अक्षर *proc)
{
    परत SDL_EGL_GetProcAddress(proc);
}
स्थिर शून्य OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
स्थिर SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint अंक_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (!videodata->eglCtx) {
        जर (!SDL_EGL_InitInternal(videodata)) {
            परत रिक्त;
        }
    }

    जर (!OPENVR_InitExtensions(_this)) {
        परत रिक्त;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    साठी(पूर्णांक i = 0; i < अंक_Extensions; i++) {
        स्थिरांक अक्षर * ccc = (स्थिरांक अक्षर *)ov_glGetStringi(GL_EXTENSIONS, i);
        जर (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    जर (!videodata->bDidCreateOverlay) {
        जर (!OPENVR_InitializeOverlay(_this, window)) {
            परत रिक्त;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    परत videodata->eglCtx;
}

स्थिर bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    परत true;
}

स्थिर bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    परत true;
}

स्थिर bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        परत SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    परत true;
}

स्थिर bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    परत true;
}

#endif

स्थिर bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, आकार(SDL_WindowData));
    जर (data == रिक्त) {
        परत SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    परत true;
}


स्थिर शून्य OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = रिक्त;
}

स्थिर शून्य OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    जर (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

स्थिर शून्य OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    जर (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    जर (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    जर (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

स्थिर शून्य OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

स्थिर शून्य OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    जर (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_आदान_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

स्थिर शून्य OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    परत;
}

स्थिर bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    जर (!videodata->bDidCreateOverlay) {
        जर (!OPENVR_InitializeOverlay(_this, window)) {
            परत false;
        }
    }

    जर (!OPENVR_ReleaseFrame(_this)) {
        परत false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    जर (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    जर (!OPENVR_SetupFrame(_this, window)) {
        परत false;
    }

    परत true;
}

स्थिर Uint8 OPENVR_MapMouseButton(पूर्णांक btn)
{
    जर (btn == EVRMouse_Button_VRMouse_Button_उजवा) {
        परत SDL_BUTTON_उजवा;
    } अन्यथा जर (btn == EVRMouse_Button_VRMouse_Button_मधला) {
        परत SDL_BUTTON_मधला;
    } अन्यथा {
        परत SDL_BUTTON_डावा;
    }
}

स्थिर शून्य OPENVR_HandleMouse(दशांश x, दशांश y, पूर्णांक btn, पूर्णांक evt)
{
    जर (evt == 2) {
        SDL_SendMouseMotion(0, रिक्त, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } अन्यथा {
        स्थिरांक Uint8 button = OPENVR_MapMouseButton(btn);
        स्थिरांक bool down = (evt != 0);
        SDL_SendMouseButton(0, रिक्त, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


स्थिर bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    परत true;
}

स्थिर शून्य OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        परत;
    }
    EGamepad_Text_आदान_Mode आदान_mode;
    निवड (SDL_Get_Text_आदान_Type(props)) {
    स्थिती SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    स्थिती SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        आदान_mode = EGamepad_Text_आदान_Mode_k_EGamepad_Text_आदान_Mode_Password;
        थांबा;
    पूर्वनिर्धारित:
        आदान_mode = EGamepad_Text_आदान_Mode_k_EGamepad_Text_आदान_Mode_Normal;
        थांबा;
    }
    EGamepad_Text_आदान_ओळ_Mode ओळ_mode;
    जर (SDL_Get_Text_आदान_Multiline(props)) {
        ओळ_mode = EGamepad_Text_आदान_ओळ_Mode_k_EGamepad_Text_आदान_ओळ_Mode_Multiple_ओळी;
    } अन्यथा {
        ओळ_mode = EGamepad_Text_आदान_ओळ_Mode_k_EGamepad_Text_आदान_ओळ_Mode_Single_ओळ;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           आदान_mode, ओळ_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

स्थिर शून्य OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

स्थिर SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, आकार(SDL_Cursor));
    जर (!result) {
        परत रिक्त;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, आकार(*ovrc));
    जर (!ovrc) {
        SDL_free(result);
        परत रिक्त;
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

    परत result;
}

स्थिर bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    जर (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        जर (e != EVROverlayError_VROverlayError_None) {
            परत OPENVR_SetOverlayError(e);
        }
        परत true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    जर (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        परत true;
    }

    hotspot.v[0] = (दशांश)ovrc->hot_x / (दशांश)ovrc->w;
    hotspot.v[1] = (दशांश)ovrc->hot_y / (दशांश)ovrc->h;

    texture.handle = (शून्य *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    जर (e != EVROverlayError_VROverlayError_None) {
        परत OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    जर (e != EVROverlayError_VROverlayError_None) {
        परत OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    जर (e != EVROverlayError_VROverlayError_None) {
        परत OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    जर (e != EVROverlayError_VROverlayError_None) {
        परत OPENVR_SetOverlayError(e);
    }

    परत true;
}

स्थिर शून्य OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    जर (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        जर (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


स्थिर bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    जर (!global_openvr_driver) {
        परत SDL_SetError("OpenVR Overlay not initialized");
    }

    अचिन्हित texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    जर (videodata->bIconOverridden) {
        परत SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (शून्य *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    जर (e != EVROverlayError_VROverlayError_None) {
        परत OPENVR_SetOverlayError(e);
    }
    परत true;
}

स्थिर bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    अक्षर empty = 0;
    अक्षर * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    अक्षर * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    अक्षर * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    परत true;
}

स्थिर शून्य InitializeMouseFunctions(शून्य)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

स्थिर शून्य OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    संरचना VREvent_t nEvent;
    जर (videodata->overlayID) {
        पर्यंत (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, आकार(nEvent))) {
            निवड (nEvent.eventType) {
            स्थिती EVREventType_VREvent_ButtonPress:
            स्थिती EVREventType_VREvent_ButtonUnpress:
                थांबा;
            स्थिती EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                थांबा;
            स्थिती EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                थांबा;
            स्थिती EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                थांबा;
            स्थिती EVREventType_VREvent_ScrollSmooth:
            स्थिती EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, रिक्त, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                थांबा;
            स्थिती EVREvent_Type_VREvent_Keyboard_Char_आदान:
                SDL_Send_Keyboard_Unicode_किल्ली(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_आदान[0]);
                थांबा;
            स्थिती EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                थांबा;
            स्थिती EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(रिक्त);
                थांबा;
            स्थिती EVREventType_VREvent_OverlayClosed:
            स्थिती EVREventType_VREvent_Quit:
                SDL_SendQuit();
                थांबा;
            }
        }
    }
}


स्थिर SDL_VideoDevice *OPENVR_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    स्थिरांक अक्षर *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(रिक्त, 0, रिक्त);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, आकार(SDL_VideoDevice));
    जर (device) {
        data = (संरचना SDL_VideoData *)SDL_calloc(1, आकार(SDL_VideoData));
    } अन्यथा {
        data = रिक्त;
    }
    जर (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        परत रिक्त;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    जर (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    जर (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    जर (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        जा error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (स्थिरांक अक्षर *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(स्थिरांक अक्षर *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    जर (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        जा error;
    }

    अक्षर fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    जर (!data->vrtoken) {
        स्थिरांक अक्षर *err = "Can't get english description";
        जर (data->FN_VR_GetVRInitErrorAsEnglishDescription != रिक्त)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        जा error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (संरचना VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (संरचना VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_आदान = (संरचना VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    जर (!data->oOverlay || !data->oSystem || !data->o_आदान) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    अक्षर *loadpath = 0;
    EVRInputError err;

    जर (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } अन्यथा {
        स्थिरांक अक्षर *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    जर (!loadpath) {
        जा error;
    }

    err = data->o_आदान->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    जर (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        जर (hint) {
            जा error;
        }
    } अन्यथा {
        जर(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            जा error;
        }
    }

    // Setup amount of available displays
    device->अंक_displays = 0;

    // Set device free function
    device->मुक्त = OPENVR_Destroy;

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
#अन्यथा
#error Needs more work to support EGL
#endif
#अन्यथा
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

#जर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#अन्यथा
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

    परत device;

error:
    OPENVR_Destroy(device);
    परत रिक्त;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, रिक्त, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

