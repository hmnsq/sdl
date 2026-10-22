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

#यदि 0
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

स्थिर bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *path);
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
    unsigned texture_id_handle;
    पूर्णाङ्क hot_x, hot_y;
    पूर्णाङ्क w, h;
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
स्थिर शून्य (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *data);
स्थिर शून्य (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
स्थिर शून्य (APIENTRY *ov_glDrawBuffers)(GLsizei n, ध्रुव GLenum *bufs);
स्थिर शून्य (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
स्थिर ध्रुव GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
स्थिर शून्य (APIENTRY *ov_glClear)(GLbitfield mask);
स्थिर शून्य (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
स्थिर शून्य (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
स्थिर शून्य (APIENTRY *ov_gl_Debug_Message_जोड़ो)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ध्रुव वर्ण *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
स्थिर PROC (*ov_wglGetProcAddress)(LPCSTR);
स्थिर HGLRC (*ov_wglCreateContext)(HDC);
स्थिर BOOL (*ov_wglDeleteContext)(HGLRC);
स्थिर BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (शून्य *)SDL_GL_GetProcAddress((#proc)+3); यदि (!proc) { failed_extension = (#proc)+3; } }

स्थिर bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    यदि (!ov_glGetError) {
        ध्रुव वर्ण * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_जोड़ो);
        यदि (failed_extension) {
            प्रत्यागम SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    प्रत्यागम true;
}

स्थिर bool OPENVR_SetOverlayError(EVROverlayError e)
{
    विकल्प (e) {
#define CASE(X) पक्ष EVROverlayError_VROverlayError_##X: प्रत्यागम SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(कुंजी_Too_Long);
    CASE(NameTooLong);
    CASE(कुंजी_In_Use);
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
    स्वभाव:
        प्रत्यागम SDL_SetError("Unknown VROverlayError %d", e);
    }
}

स्थिर bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

स्थिर bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    ध्रुव वर्ण * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ध्रुव वर्ण * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ध्रुव वर्ण * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    पूर्णाङ्क width = hintWidth ? SDL_atoi(hintWidth) : 0;
    पूर्णाङ्क height = hintHeight ? SDL_atoi(hintHeight) : 0;
    पूर्णाङ्क fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    यदि (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    यदि (fps) {
        display.desktop_mode.refresh_rate = fps;
    } अन्यथा {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (वर्ण *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    प्रत्यागम true;
}

स्थिर शून्य OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

स्थिर शून्य OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    यदि (data) {
        यदि (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    पूर्णाङ्क w = surf->w;
    पूर्णाङ्क h = surf->h;
    पूर्णाङ्क pitch = surf->pitch;
    पूर्णाङ्क x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    प्रति(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        प्रति(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    प्रत्यागम pxd;
}

स्थिर bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    यदि (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    यदि (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        संरचना HmdVector2_t ms;
        पूर्णाङ्क status;

        यदि (videodata->fbo <= 0) {
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
        यदि (status != GL_FRAMEBUFFER_COMPLETE) {
            प्रत्यागम SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (भिन्न)videodata->targw;
        ms.v[1] = (भिन्न)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    प्रत्यागम true;
}

स्थिर bool OPENVR_VirtualControllerRumble(शून्य *userdata, Uint16 निचला_frequency_rumble, Uint16 ऊपरी_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    ध्रुव भिन्न k_flIntensity = 320.f; // Maximum frequency
    भिन्न fl_बायाँ_Frequency = (भिन्न)निचला_frequency_rumble * k_flIntensity / 65535.f;
    भिन्न fl_दायाँ_Frequency = (भिन्न)ऊपरी_frequency_rumble * k_flIntensity / 65535.f;
    भिन्न flDurationSeconds = 2.f;
    भिन्न flAmplitude = 1.f;

    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[0], 0, flDurationSeconds, fl_बायाँ_Frequency, flAmplitude, 0);
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[1], 0, flDurationSeconds, fl_दायाँ_Frequency, flAmplitude, 0);

    प्रत्यागम true;
}

स्थिर bool OPENVR_VirtualControllerRumbleTriggers(शून्य *userdata, Uint16 बायाँ_rumble, Uint16 दायाँ_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[0], 0, 0.1f, बायाँ_rumble, 1.0, 0);
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[1], 0, 0.1f, दायाँ_rumble, 1.0, 0);
    प्रत्यागम true;
}

स्थिर शून्य OPENVR_VirtualControllerUpdate(शून्य *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    निवेश_Digital_Action_Data_t digital_निवेश_action;
    निवेश_Analog_Action_Data_t analog_निवेश_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->निवेश_action_set;
    e = videodata->o_निवेश->UpdateActionState(&actionSet, परिमाण(actionSet), 1);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        प्रत्यागम;
    }

    प्रति (पूर्णाङ्क d = 0; d < videodata->निवेश_action_handles_buttons_गिनती; d++)
    {
        यदि (videodata->निवेश_action_handles_buttons[d] == k_ulInvalidActionHandle)
            अनुवर्त;
        e = videodata->o_निवेश->GetDigitalActionData(videodata->निवेश_action_handles_buttons[d], &digital_निवेश_action, परिमाण(digital_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
        यदि (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            प्रत्यागम;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_निवेश_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_निवेश->GetAnalogActionData(videodata->निवेश_action_handles_axes[0], &analog_निवेश_action, परिमाण(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        प्रत्यागम;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_निवेश_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_निवेश_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_निवेश->GetAnalogActionData(videodata->निवेश_action_handles_axes[1], &analog_निवेश_action, परिमाण(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        प्रत्यागम;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_निवेश_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_निवेश_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_निवेश->GetAnalogActionData(videodata->निवेश_action_handles_axes[2], &analog_निवेश_action, परिमाण(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        प्रत्यागम;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_बायाँ_TRIGGER, (Sint16)((analog_निवेश_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_निवेश->GetAnalogActionData(videodata->निवेश_action_handles_axes[3], &analog_निवेश_action, परिमाण(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        प्रत्यागम;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_दायाँ_TRIGGER, (Sint16)((analog_निवेश_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#यदि 0
    प्रति (a = 0; a < videodata->निवेश_action_handles_axes_गिनती; a++)
    {
        भिन्न xval = 0.0f;
        e = videodata->o_निवेश->GetAnalogActionData(videodata->निवेश_action_handles_axes[a], &analog_निवेश_action, परिमाण(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
        यदि (e) गच्छ updatefail;
        xval = analog_निवेश_action.x;
        यदि (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        यदि (a == SDL_GAMEPAD_AXIS_बायाँ_TRIGGER || a == SDL_GAMEPAD_AXIS_दायाँ_TRIGGER)
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
    प्रत्यागम;
}

स्थिर bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    वर्ण * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_गिनती] = {
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
    वर्ण * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    यदि ((e = videodata->o_निवेश->GetActionSetHandle("/actions/virtualgamepad", &videodata->निवेश_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        प्रत्यागम SDL_SetError("Failed to get action set handle");
    }

    videodata->निवेश_action_handles_buttons_गिनती = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->निवेश_action_handles_buttons = SDL_malloc(videodata->निवेश_action_handles_buttons_गिनती * परिमाण(VRActionHandle_t));

    प्रति (पूर्णाङ्क i = 0; i < videodata->निवेश_action_handles_buttons_गिनती; i++)
    {
        e = videodata->o_निवेश->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->निवेश_action_handles_buttons[i]);
        यदि (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            प्रत्यागम SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->निवेश_action_handles_axes_गिनती = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->निवेश_action_handles_axes = SDL_malloc(videodata->निवेश_action_handles_axes_गिनती * परिमाण(VRActionHandle_t));

    प्रति (पूर्णाङ्क i = 0; i < videodata->निवेश_action_handles_axes_गिनती; i++)
    {
        e = videodata->o_निवेश->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->निवेश_action_handles_axes[i]);
        यदि (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            प्रत्यागम SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_निवेश->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->निवेश_action_handles_haptics[0]);
    e |= videodata->o_निवेश->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->निवेश_action_handles_haptics[1]);
    यदि (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        प्रत्यागम SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_गिनती;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_गिनती;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    यदि (!virtual_id) {
        प्रत्यागम SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    यदि (!videodata->virtual_joystick) {
        प्रत्यागम SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->निवेश_action_handles_buttons_गिनती, videodata->निवेश_action_handles_axes_गिनती);
#endif

    प्रत्यागम true;
}

स्थिर bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    यदि (!OPENVR_InitExtensions(_this)) {
        प्रत्यागम false;
    }

    // Generate the overlay.
    {
        ध्रुव वर्ण * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        वर्ण * cursorname = 0;
        यदि (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        यदि (!videodata->sOverlayName) {
            प्रत्यागम false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        यदि (!cursorname) {
            प्रत्यागम false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        यदि (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            प्रत्यागम SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        यदि (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            प्रत्यागम SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_संख्या, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ध्रुव वर्ण *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        यदि (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } अन्यथा {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#यदि 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        प्रति (पूर्णाङ्क i = 0; i < परिमाण(overlay_flags) * 8; ++i) {
            यदि (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ध्रुव वर्ण * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        भिन्न fWidth = hint ? (भिन्न)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        ध्रुव वर्ण * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        भिन्न fCursorWidth = hint ? (भिन्न)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        ध्रुव वर्ण * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        यदि (hint) {
            वर्ण * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            यदि (err == EVROverlayError_VROverlayError_None) {
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

    यदि (!OPENVR_CheckRenderbuffer(_this)) {
        प्रत्यागम false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    प्रत्यागम true;
}


स्थिर bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    स्थिर ध्रुव GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        पूर्णाङ्क error = ov_glGetError();
        यदि (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    यदि (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    प्रत्यागम true;
}

स्थिर bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    यदि (!ov_glGetError) {
        प्रत्यागम true;
    }

    यदि (!videodata->is_buffer_rendering) {
        प्रत्यागम true;
    }

#ifdef DEBUG_OPENVR
    {
        पूर्णाङ्क error = ov_glGetError();
        यदि (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    यदि (videodata->overlaytexture != 0 &&
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

    यदि (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    यदि (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_जोड़ो(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    प्रत्यागम OPENVR_CheckRenderbuffer(_this);
}

स्थिर शून्य OPENVR_HandleResize(SDL_VideoDevice *_this, पूर्णाङ्क w, पूर्णाङ्क h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

स्थिर bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    प्रत्यागम true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
स्थिर LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam)
{
    विकल्प (संदेश) {
    पक्ष WM_DESTROY:
        प्रत्यागम 0;
    }
    प्रत्यागम DefWindowProc(hwnd, संदेश, wParam, lParam);
}

स्थिर bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *path)
{
    यदि (path == रिक्त) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    यदि (path == रिक्त) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    यदि (!_this->gl_config.dll_handle) {
        प्रत्यागम false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (संरचना SDL_GLDriverData *)SDL_calloc(1, परिमाण(संरचना SDL_GLDriverData));
    यदि (!_this->gl_data) {
        प्रत्यागम false;
    }
    _this->gl_config.driver_loaded = true;

    प्रत्यागम true;
}

स्थिर SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer result = रिक्त;
    यदि (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        यदि (result) {
            प्रत्यागम result;
        }
    }

    प्रत्यागम SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

स्थिर शून्य OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

स्थिर SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint अंक_Extensions;
    पूर्णाङ्क i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (!videodata->hglrc) {
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
        यावत् (PeekMessage(&संदेश, रिक्त, 0, 0, PM_REMOVE)) {
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
        }

        videodata->hdc = GetDC(hwnd);

        स्थिर  PIXELFORMATDESCRIPTOR pfd =
        {
            परिमाण(PIXELFORMATDESCRIPTOR),
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
        यदि (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            प्रत्यागम रिक्त;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        यदि (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            प्रत्यागम रिक्त;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        यदि (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            प्रत्यागम रिक्त;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        यदि (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            प्रत्यागम रिक्त;
        }
    }

    i = OPENVR_InitExtensions(_this);
    यदि (i == 0) {
        प्रत्यागम रिक्त;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    प्रति (i = 0; i < अंक_Extensions; i++) {
        ध्रुव वर्ण *ccc = (ध्रुव वर्ण *)ov_glGetStringi(GL_EXTENSIONS, i);
        यदि (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    यदि (!videodata->bDidCreateOverlay) {
        यदि (!OPENVR_InitializeOverlay(_this, window)) {
            प्रत्यागम रिक्त;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(परिमाण(संरचना SDL_GLContextState));
    यदि (!result) {
        प्रत्यागम रिक्त;
    }
    result->hglrc = videodata->hglrc;
    प्रत्यागम result;
}

स्थिर bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    प्रत्यागम true;
}

स्थिर bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    प्रत्यागम true;
}

स्थिर bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        प्रत्यागम SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    प्रत्यागम true;
}

स्थिर bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, रिक्त);
    ov_wglDeleteContext(videodata->hglrc);
    प्रत्यागम true;
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

    यदि (vd->eglDpy == 0) {
        प्रत्यागम SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    यदि (!b) {
        प्रत्यागम SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        पूर्णाङ्क err = eglGetError();
        यदि (err != EGL_SUCCESS) {
            प्रत्यागम SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    यदि (!vd->eglCtx) {
        प्रत्यागम SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    प्रत्यागम true;
}

// Linux, EGL, etc.
स्थिर bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, ध्रुव वर्ण *path)
{
    प्रत्यागम SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

स्थिर SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, ध्रुव वर्ण *proc)
{
    प्रत्यागम SDL_EGL_GetProcAddress(proc);
}
स्थिर शून्य OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
स्थिर SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint अंक_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (!videodata->eglCtx) {
        यदि (!SDL_EGL_InitInternal(videodata)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (!OPENVR_InitExtensions(_this)) {
        प्रत्यागम रिक्त;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    प्रति(पूर्णाङ्क i = 0; i < अंक_Extensions; i++) {
        ध्रुव वर्ण * ccc = (ध्रुव वर्ण *)ov_glGetStringi(GL_EXTENSIONS, i);
        यदि (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    यदि (!videodata->bDidCreateOverlay) {
        यदि (!OPENVR_InitializeOverlay(_this, window)) {
            प्रत्यागम रिक्त;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    प्रत्यागम videodata->eglCtx;
}

स्थिर bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    प्रत्यागम true;
}

स्थिर bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    प्रत्यागम true;
}

स्थिर bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        प्रत्यागम SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    प्रत्यागम true;
}

स्थिर bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    प्रत्यागम true;
}

#endif

स्थिर bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, परिमाण(SDL_WindowData));
    यदि (data == रिक्त) {
        प्रत्यागम SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    प्रत्यागम true;
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
    यदि (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

स्थिर शून्य OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    यदि (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    यदि (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    यदि (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

स्थिर शून्य OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

स्थिर शून्य OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    यदि (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_निवेश_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

स्थिर शून्य OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    प्रत्यागम;
}

स्थिर bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    यदि (!videodata->bDidCreateOverlay) {
        यदि (!OPENVR_InitializeOverlay(_this, window)) {
            प्रत्यागम false;
        }
    }

    यदि (!OPENVR_ReleaseFrame(_this)) {
        प्रत्यागम false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    यदि (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    यदि (!OPENVR_SetupFrame(_this, window)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

स्थिर Uint8 OPENVR_MapMouseButton(पूर्णाङ्क btn)
{
    यदि (btn == EVRMouse_Button_VRMouse_Button_दायाँ) {
        प्रत्यागम SDL_BUTTON_दायाँ;
    } अन्यथा यदि (btn == EVRMouse_Button_VRMouse_Button_मध्य) {
        प्रत्यागम SDL_BUTTON_मध्य;
    } अन्यथा {
        प्रत्यागम SDL_BUTTON_बायाँ;
    }
}

स्थिर शून्य OPENVR_HandleMouse(भिन्न x, भिन्न y, पूर्णाङ्क btn, पूर्णाङ्क evt)
{
    यदि (evt == 2) {
        SDL_SendMouseMotion(0, रिक्त, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } अन्यथा {
        ध्रुव Uint8 button = OPENVR_MapMouseButton(btn);
        ध्रुव bool down = (evt != 0);
        SDL_SendMouseButton(0, रिक्त, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


स्थिर bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    प्रत्यागम true;
}

स्थिर शून्य OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        प्रत्यागम;
    }
    EGamepad_Text_निवेश_Mode निवेश_mode;
    विकल्प (SDL_Get_Text_निवेश_Type(props)) {
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    पक्ष SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        निवेश_mode = EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Password;
        भङ्ग;
    स्वभाव:
        निवेश_mode = EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Normal;
        भङ्ग;
    }
    EGamepad_Text_निवेश_पंक्ति_Mode पंक्ति_mode;
    यदि (SDL_Get_Text_निवेश_Multiline(props)) {
        पंक्ति_mode = EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Multiple_पंक्तियाँ;
    } अन्यथा {
        पंक्ति_mode = EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Single_पंक्ति;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           निवेश_mode, पंक्ति_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

स्थिर शून्य OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

स्थिर SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, परिमाण(SDL_Cursor));
    यदि (!result) {
        प्रत्यागम रिक्त;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, परिमाण(*ovrc));
    यदि (!ovrc) {
        SDL_free(result);
        प्रत्यागम रिक्त;
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

    प्रत्यागम result;
}

स्थिर bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    यदि (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        यदि (e != EVROverlayError_VROverlayError_None) {
            प्रत्यागम OPENVR_SetOverlayError(e);
        }
        प्रत्यागम true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    यदि (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        प्रत्यागम true;
    }

    hotspot.v[0] = (भिन्न)ovrc->hot_x / (भिन्न)ovrc->w;
    hotspot.v[1] = (भिन्न)ovrc->hot_y / (भिन्न)ovrc->h;

    texture.handle = (शून्य *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    यदि (e != EVROverlayError_VROverlayError_None) {
        प्रत्यागम OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    यदि (e != EVROverlayError_VROverlayError_None) {
        प्रत्यागम OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    यदि (e != EVROverlayError_VROverlayError_None) {
        प्रत्यागम OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    यदि (e != EVROverlayError_VROverlayError_None) {
        प्रत्यागम OPENVR_SetOverlayError(e);
    }

    प्रत्यागम true;
}

स्थिर शून्य OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    यदि (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        यदि (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


स्थिर bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    यदि (!global_openvr_driver) {
        प्रत्यागम SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    यदि (videodata->bIconOverridden) {
        प्रत्यागम SDL_SetError("OpenVR Icon is overridden.");
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
    यदि (e != EVROverlayError_VROverlayError_None) {
        प्रत्यागम OPENVR_SetOverlayError(e);
    }
    प्रत्यागम true;
}

स्थिर bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    वर्ण empty = 0;
    वर्ण * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    वर्ण * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    वर्ण * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    प्रत्यागम true;
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
    यदि (videodata->overlayID) {
        यावत् (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, परिमाण(nEvent))) {
            विकल्प (nEvent.eventType) {
            पक्ष EVREventType_VREvent_ButtonPress:
            पक्ष EVREventType_VREvent_ButtonUnpress:
                भङ्ग;
            पक्ष EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                भङ्ग;
            पक्ष EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                भङ्ग;
            पक्ष EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                भङ्ग;
            पक्ष EVREventType_VREvent_ScrollSmooth:
            पक्ष EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, रिक्त, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                भङ्ग;
            पक्ष EVREvent_Type_VREvent_Keyboard_Char_निवेश:
                SDL_Send_Keyboard_Unicode_कुंजी(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_निवेश[0]);
                भङ्ग;
            पक्ष EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                भङ्ग;
            पक्ष EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(रिक्त);
                भङ्ग;
            पक्ष EVREventType_VREvent_OverlayClosed:
            पक्ष EVREventType_VREvent_Quit:
                SDL_SendQuit();
                भङ्ग;
            }
        }
    }
}


स्थिर SDL_VideoDevice *OPENVR_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ध्रुव वर्ण *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(रिक्त, 0, रिक्त);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (device) {
        data = (संरचना SDL_VideoData *)SDL_calloc(1, परिमाण(SDL_VideoData));
    } अन्यथा {
        data = रिक्त;
    }
    यदि (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        प्रत्यागम रिक्त;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    यदि (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    यदि (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    यदि (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        गच्छ error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (ध्रुव वर्ण *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(ध्रुव वर्ण *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    यदि (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        गच्छ error;
    }

    वर्ण fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    यदि (!data->vrtoken) {
        ध्रुव वर्ण *err = "Can't get english description";
        यदि (data->FN_VR_GetVRInitErrorAsEnglishDescription != रिक्त)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        गच्छ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (संरचना VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (संरचना VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_निवेश = (संरचना VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    यदि (!data->oOverlay || !data->oSystem || !data->o_निवेश) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    वर्ण *loadpath = 0;
    EVRInputError err;

    यदि (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } अन्यथा {
        ध्रुव वर्ण *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    यदि (!loadpath) {
        गच्छ error;
    }

    err = data->o_निवेश->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    यदि (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        यदि (hint) {
            गच्छ error;
        }
    } अन्यथा {
        यदि(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            गच्छ error;
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

#यदि defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
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

    प्रत्यागम device;

error:
    OPENVR_Destroy(device);
    प्रत्यागम रिक्त;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, रिक्त, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

