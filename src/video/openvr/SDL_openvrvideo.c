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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OPENVR

#अगर 0
#घोषणा DEBUG_OPENVR
#पूर्ण_अगर

#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../SDL_egl_c.h"
#समावेश "SDL_openvrvideo.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#समावेश <SDL3/SDL_opengl.h>
#अन्यथा
// Currently only EGL, not OpenGL, is supported on other platforms
#समावेश <SDL3/SDL_opengles2.h>
#समावेश <SDL3/SDL_opengles2_gl2.h>
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
#समावेश "../windows/SDL_windowsopengl.h"
#समावेश "../windows/SDL_windowsvulkan.h"

#घोषणा DEFAULT_OPENGL "OPENGL32.DLL"

अटल bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
अटल SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

काष्ठा SDL_GLContextState
{
    HGLRC hglrc;
};
#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS



#अगर_घोषित SDL_PLATFORM_WINDOWS
#घोषणा SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#अन्यथा
#घोषणा SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#पूर्ण_अगर

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#घोषणा MARKER_ID 0
#घोषणा MARKER_STR "vr-marker,frame_end,type,application"

#अघोषित EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_तथ्य * global_openvr_driver;

अटल व्योम InitializeMouseFunctions(व्योम);

काष्ठा SDL_Cursor_तथ्य
{
    अचिन्हित texture_id_handle;
    पूर्णांक hot_x, hot_y;
    पूर्णांक w, h;
};

// GL Extensions for functions we will be using.
अटल व्योम (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
अटल व्योम (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
अटल व्योम (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
अटल व्योम (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
अटल व्योम (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
अटल व्योम (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
अटल व्योम (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
अटल GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
अटल GLenum (APIENTRY *ov_glGetError)(व्योम);
अटल व्योम (APIENTRY *ov_glFlush)(व्योम);
अटल व्योम (APIENTRY *ov_glFinish)(व्योम);
अटल व्योम (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
अटल व्योम (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
अटल व्योम (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
अटल व्योम (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
अटल व्योम (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, स्थिर व्योम *तथ्य);
अटल व्योम (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
अटल व्योम (APIENTRY *ov_glDrawBuffers)(GLsizei n, स्थिर GLenum *bufs);
अटल व्योम (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * तथ्य);
अटल स्थिर GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint सूचकांक);
अटल व्योम (APIENTRY *ov_glClear)(GLbitfield mask);
अटल व्योम (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
अटल व्योम (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
अटल व्योम (APIENTRY *ov_gl_Debug_Message_जोड़ो)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei लंबाई, स्थिर अक्षर *message);

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
अटल PROC (*ov_wglGetProcAddress)(LPCSTR);
अटल HGLRC (*ov_wglCreateContext)(HDC);
अटल BOOL (*ov_wglDeleteContext)(HGLRC);
अटल BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#पूर्ण_अगर


#घोषणा OPENVR_DEFAULT_WIDTH 1920
#घोषणा OPENVR_DEFAULT_HEIGHT 1080

#घोषणा OPENVR_SetupProc(proc) { proc = (व्योम *)SDL_GL_GetProcAddress((#proc)+3); अगर (!proc) { failed_extension = (#proc)+3; } }

अटल bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    अगर (!ov_glGetError) {
        स्थिर अक्षर * failed_extension = 0;
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
        अगर (failed_extension) {
            वापस SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    वापस true;
}

अटल bool OPENVR_SetOverlayError(EVROverlayError e)
{
    चयन (e) {
#घोषणा CASE(X) हाल EVROverlayError_VROverlayError_##X: वापस SDL_SetError("VROverlayError %s", #X)
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
#अघोषित CASE
    शेष:
        वापस SDL_SetError("Unknown VROverlayError %d", e);
    }
}

अटल bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

अटल bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = (SDL_Video_तथ्य *)_this->internal;

    स्थिर अक्षर * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    स्थिर अक्षर * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    स्थिर अक्षर * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
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
    अगर (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    अगर (fps) {
        display.desktop_mode.refresh_rate = fps;
    } अन्यथा {
        display.desktop_mode.refresh_rate = तथ्य->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_सूचकांक_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (अक्षर *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    वापस true;
}

अटल व्योम OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

अटल व्योम OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;

#अगर_घोषित SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#पूर्ण_अगर

    अगर (तथ्य) {
        अगर (तथ्य->openVRLIB) {
            SDL_UnloadObject(तथ्य->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

अटल uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    पूर्णांक w = surf->w;
    पूर्णांक h = surf->h;
    पूर्णांक pitch = surf->pitch;
    पूर्णांक x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    क्रम(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        क्रम(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    वापस pxd;
}

अटल bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;

    अगर (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    अगर (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        काष्ठा HmdVector2_t ms;
        पूर्णांक status;

        अगर (videodata->fbo <= 0) {
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
        अगर (status != GL_FRAMEBUFFER_COMPLETE) {
            वापस SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (भग्न)videodata->targw;
        ms.v[1] = (भग्न)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    वापस true;
}

अटल bool OPENVR_VirtualControllerRumble(व्योम *userdata, Uint16 निचला_frequency_rumble, Uint16 ऊपरी_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)userdata;

    स्थिर भग्न k_flIntensity = 320.f; // Maximum frequency
    भग्न fl_बायाँ_Frequency = (भग्न)निचला_frequency_rumble * k_flIntensity / 65535.f;
    भग्न fl_दायाँ_Frequency = (भग्न)ऊपरी_frequency_rumble * k_flIntensity / 65535.f;
    भग्न flDurationSeconds = 2.f;
    भग्न flAmplitude = 1.f;

    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[0], 0, flDurationSeconds, fl_बायाँ_Frequency, flAmplitude, 0);
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[1], 0, flDurationSeconds, fl_दायाँ_Frequency, flAmplitude, 0);

    वापस true;
}

अटल bool OPENVR_VirtualControllerRumbleTriggers(व्योम *userdata, Uint16 बायाँ_rumble, Uint16 दायाँ_rumble)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)userdata;
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[0], 0, 0.1f, बायाँ_rumble, 1.0, 0);
    videodata->o_निवेश->TriggerHapticVibrationAction(videodata->निवेश_action_handles_haptics[1], 0, 0.1f, दायाँ_rumble, 1.0, 0);
    वापस true;
}

अटल व्योम OPENVR_VirtualControllerUpdate(व्योम *userdata)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    निवेश_Digital_Action_तथ्य_t digital_निवेश_action;
    निवेश_Analog_Action_तथ्य_t analog_निवेश_action;
    EVRInputError e;
#अगर_घोषित DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#पूर्ण_अगर
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->निवेश_action_set;
    e = videodata->o_निवेश->UpdateActionState(&actionSet, माप(actionSet), 1);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#पूर्ण_अगर
        वापस;
    }

    क्रम (पूर्णांक d = 0; d < videodata->निवेश_action_handles_buttons_गिनती; d++)
    {
        अगर (videodata->निवेश_action_handles_buttons[d] == k_ulInvalidActionHandle)
            जारी;
        e = videodata->o_निवेश->Get_Digital_Action_तथ्य(videodata->निवेश_action_handles_buttons[d], &digital_निवेश_action, माप(digital_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
        अगर (e)
        {
#अगर_घोषित DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#पूर्ण_अगर
            वापस;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_निवेश_action.bState);
#अगर_घोषित DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#पूर्ण_अगर
    }

    // Left Stick
    e = videodata->o_निवेश->Get_Analog_Action_तथ्य(videodata->निवेश_action_handles_axes[0], &analog_निवेश_action, माप(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#पूर्ण_अगर
        वापस;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_निवेश_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_निवेश_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_निवेश->Get_Analog_Action_तथ्य(videodata->निवेश_action_handles_axes[1], &analog_निवेश_action, माप(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#पूर्ण_अगर
        वापस;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_निवेश_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_निवेश_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_निवेश->Get_Analog_Action_तथ्य(videodata->निवेश_action_handles_axes[2], &analog_निवेश_action, माप(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#पूर्ण_अगर
        वापस;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_बायाँ_TRIGGER, (Sint16)((analog_निवेश_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_निवेश->Get_Analog_Action_तथ्य(videodata->निवेश_action_handles_axes[3], &analog_निवेश_action, माप(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#पूर्ण_अगर
        वापस;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_दायाँ_TRIGGER, (Sint16)((analog_निवेश_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#अगर 0
    क्रम (a = 0; a < videodata->निवेश_action_handles_axes_गिनती; a++)
    {
        भग्न xval = 0.0f;
        e = videodata->o_निवेश->Get_Analog_Action_तथ्य(videodata->निवेश_action_handles_axes[a], &analog_निवेश_action, माप(analog_निवेश_action), k_ul_Invalid_निवेश_मूल्य_Handle);
        अगर (e) जाओ updatefail;
        xval = analog_निवेश_action.x;
        अगर (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        अगर (a == SDL_GAMEPAD_AXIS_बायाँ_TRIGGER || a == SDL_GAMEPAD_AXIS_दायाँ_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_SetJoystickVirtualAxis(joystick, a, xval);
#अगर_घोषित DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#पूर्ण_अगर
    }
#पूर्ण_अगर
#अगर_घोषित DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#पूर्ण_अगर
    वापस;
}

अटल bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_Video_तथ्य * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    अक्षर * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_गिनती] = {
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

    अगर ((e = videodata->o_निवेश->GetActionSetHandle("/actions/virtualgamepad", &videodata->निवेश_action_set)) != EVRInputError_VRInputError_None)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#पूर्ण_अगर
        वापस SDL_SetError("Failed to get action set handle");
    }

    videodata->निवेश_action_handles_buttons_गिनती = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->निवेश_action_handles_buttons = SDL_malloc(videodata->निवेश_action_handles_buttons_गिनती * माप(VRActionHandle_t));

    क्रम (पूर्णांक i = 0; i < videodata->निवेश_action_handles_buttons_गिनती; i++)
    {
        e = videodata->o_निवेश->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->निवेश_action_handles_buttons[i]);
        अगर (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            वापस SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->निवेश_action_handles_axes_गिनती = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->निवेश_action_handles_axes = SDL_malloc(videodata->निवेश_action_handles_axes_गिनती * माप(VRActionHandle_t));

    क्रम (पूर्णांक i = 0; i < videodata->निवेश_action_handles_axes_गिनती; i++)
    {
        e = videodata->o_निवेश->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->निवेश_action_handles_axes[i]);
        अगर (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            वापस SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_निवेश->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->निवेश_action_handles_haptics[0]);
    e |= videodata->o_निवेश->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->निवेश_action_handles_haptics[1]);
    अगर (e)
    {
#अगर_घोषित DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#पूर्ण_अगर
        वापस SDL_SetError("ERROR: Failed to get haptics action");
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

    अगर (!virtual_id) {
        वापस SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    अगर (!videodata->virtual_joystick) {
        वापस SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#अगर_घोषित DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->निवेश_action_handles_buttons_गिनती, videodata->निवेश_action_handles_axes_गिनती);
#पूर्ण_अगर

    वापस true;
}

अटल bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    अगर (!OPENVR_InitExtensions(_this)) {
        वापस false;
    }

    // Generate the overlay.
    {
        स्थिर अक्षर * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        अक्षर * cursorname = 0;
        अगर (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        अगर (!videodata->sOverlayName) {
            वापस false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        अगर (!cursorname) {
            वापस false;
        }

        EVROverlayError परिणाम = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        अगर (परिणाम != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            वापस SDL_SetError("Could not create dashboard overlay (%d)", परिणाम );
        }
        परिणाम = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        अगर (परिणाम != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            वापस SDL_SetError("Could not create cursor overlay (%d)", परिणाम );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_संख्या, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        स्थिर अक्षर *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        अगर (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } अन्यथा {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#अगर 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#पूर्ण_अगर
        }

        क्रम (पूर्णांक i = 0; i < माप(overlay_flags) * 8; ++i) {
            अगर (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        स्थिर अक्षर * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        भग्न fWidth = hint ? (भग्न)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        स्थिर अक्षर * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        भग्न fCursorWidth = hint ? (भग्न)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        स्थिर अक्षर * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        अगर (hint) {
            अक्षर * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            अगर (err == EVROverlayError_VROverlayError_None) {
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

    अगर (!OPENVR_CheckRenderbuffer(_this)) {
        वापस false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    वापस true;
}


अटल bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अटल स्थिर GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_बफर_rendering = true;

#अगर_घोषित DEBUG_OPENVR
    {
        पूर्णांक error = ov_glGetError();
        अगर (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#पूर्ण_अगर

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    अगर (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_बफर_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    वापस true;
}

अटल bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    अगर (!ov_glGetError) {
        वापस true;
    }

    अगर (!videodata->is_बफर_rendering) {
        वापस true;
    }

#अगर_घोषित DEBUG_OPENVR
    {
        पूर्णांक error = ov_glGetError();
        अगर (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#पूर्ण_अगर

    videodata->is_बफर_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    अगर (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        काष्ठा Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (व्योम *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    अगर (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    अगर (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_जोड़ो(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    वापस OPENVR_CheckRenderbuffer(_this);
}

अटल व्योम OPENVR_HandleResize(SDL_VideoDevice *_this, पूर्णांक w, पूर्णांक h)
{
    SDL_Video_तथ्य *तथ्य = (SDL_Video_तथ्य *)_this->internal;
    तथ्य->targw = w;
    तथ्य->targh = h;
}

अटल bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    वापस true;
}


#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
अटल LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam)
{
    चयन (संदेश) {
    हाल WM_DESTROY:
        वापस 0;
    }
    वापस DefWindowProc(hwnd, संदेश, wParam, lParam);
}

अटल bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    अगर (path == शून्य) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    अगर (path == शून्य) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    अगर (!_this->gl_config.dll_handle) {
        वापस false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_तथ्य = (काष्ठा SDL_GLDriver_तथ्य *)SDL_calloc(1, माप(काष्ठा SDL_GLDriver_तथ्य));
    अगर (!_this->gl_तथ्य) {
        वापस false;
    }
    _this->gl_config.driver_loaded = true;

    वापस true;
}

अटल SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    SDL_FunctionPointer परिणाम = शून्य;
    अगर (ov_wglGetProcAddress) {
        परिणाम = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        अगर (परिणाम) {
            वापस परिणाम;
        }
    }

    वापस SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

अटल व्योम OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

अटल SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint अंक_Extensions;
    पूर्णांक i;
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(शून्य);
        wnd.hIcon = LoadIcon(शून्य, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(शून्य, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = शून्य;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, शून्य, शून्य, GetModuleHandle(शून्य), शून्य);

        संदेश_2 संदेश;
        जबतक (PeekMessage(&संदेश, शून्य, 0, 0, PM_REMOVE)) {
            TranslateMessage(&संदेश);
            DispatchMessage(&संदेश);
        }

        videodata->hdc = GetDC(hwnd);

        अटल  PIXELFORMATDESCRIPTOR pfd =
        {
            माप(PIXELFORMATDESCRIPTOR),
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
        अगर (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            वापस शून्य;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        अगर (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            वापस शून्य;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        अगर (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            वापस शून्य;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        अगर (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            वापस शून्य;
        }
    }

    i = OPENVR_InitExtensions(_this);
    अगर (i == 0) {
        वापस शून्य;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    क्रम (i = 0; i < अंक_Extensions; i++) {
        स्थिर अक्षर *ccc = (स्थिर अक्षर *)ov_glGetStringi(GL_EXTENSIONS, i);
        अगर (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#अगर_घोषित DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#पूर्ण_अगर
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    अगर (!videodata->bDidCreateOverlay) {
        अगर (!OPENVR_InitializeOverlay(_this, window)) {
            वापस शून्य;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext परिणाम = SDL_malloc(माप(काष्ठा SDL_GLContextState));
    अगर (!परिणाम) {
        वापस शून्य;
    }
    परिणाम->hglrc = videodata->hglrc;
    वापस परिणाम;
}

अटल bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    वापस true;
}

अटल bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    videodata->swap_interval = interval;
    वापस true;
}

अटल bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *swapInterval)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        वापस SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    वापस true;
}

अटल bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, शून्य);
    ov_wglDeleteContext(videodata->hglrc);
    वापस true;
}


#अन्यथा

अटल EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

अटल bool SDL_EGL_InitInternal(SDL_Video_तथ्य * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=शून्य;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#अगर_घोषित DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#पूर्ण_अगर

    अगर (vd->eglDpy == 0) {
        वापस SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    अगर (!b) {
        वापस SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#अगर_घोषित DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#पूर्ण_अगर

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#अगर_घोषित DEBUG_OPENVR
    {
        पूर्णांक err = eglGetError();
        अगर (err != EGL_SUCCESS) {
            वापस SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#पूर्ण_अगर

    अगर (!vd->eglCtx) {
        वापस SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    वापस true;
}

// Linux, EGL, etc.
अटल bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path)
{
    वापस SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

अटल SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc)
{
    वापस SDL_EGL_GetProcAddress(proc);
}
अटल व्योम OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
अटल SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint अंक_Extensions;
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (!videodata->eglCtx) {
        अगर (!SDL_EGL_InitInternal(videodata)) {
            वापस शून्य;
        }
    }

    अगर (!OPENVR_InitExtensions(_this)) {
        वापस शून्य;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_अंक_EXTENSIONS, &अंक_Extensions);
    क्रम(पूर्णांक i = 0; i < अंक_Extensions; i++) {
        स्थिर अक्षर * ccc = (स्थिर अक्षर *)ov_glGetStringi(GL_EXTENSIONS, i);
        अगर (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#अगर_घोषित DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#पूर्ण_अगर
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    अगर (!videodata->bDidCreateOverlay) {
        अगर (!OPENVR_InitializeOverlay(_this, window)) {
            वापस शून्य;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    वापस videodata->eglCtx;
}

अटल bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    वापस true;
}

अटल bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    videodata->swap_interval = interval;
    वापस true;
}

अटल bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक * swapInterval)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (swapInterval)
        *swapInterval = videodata->swap_interval;
    अन्यथा
        वापस SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    वापस true;
}

अटल bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    वापस true;
}

#पूर्ण_अगर

अटल bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *तथ्य;

    // Allocate window internal data
    तथ्य = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (तथ्य == शून्य) {
        वापस SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = तथ्य;
    वापस true;
}


अटल व्योम OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य;

    तथ्य = window->internal;
    SDL_free(तथ्य);
    window->internal = शून्य;
}

अटल व्योम OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य * तथ्य = (SDL_Video_तथ्य *)_this->internal;
    अगर (तथ्य->bDidCreateOverlay) {
        तथ्य->oOverlay->SetOverlayName(तथ्य->overlayID, window->title);
    }
}

अटल व्योम OPENVR_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *तथ्य = (SDL_Video_तथ्य *)_this->internal;

    अगर (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    अगर (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    अगर (तथ्य->targh != window->h || तथ्य->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

अटल व्योम OPENVR_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    SDL_Video_तथ्य *तथ्य = (SDL_Video_तथ्य *)_this->internal;
    *w = तथ्य->targw;
    *h = तथ्य->targh;
}

अटल व्योम OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *तथ्य = (SDL_Video_तथ्य *)_this->internal;
    अगर (तथ्य->targh != window->h || तथ्य->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    तथ्य->oOverlay->ShowDashboard(तथ्य->sOverlayName);

    window->flags |= (SDL_WINDOW_निवेश_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

अटल व्योम OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    वापस;
}

अटल bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    अगर (!videodata->bDidCreateOverlay) {
        अगर (!OPENVR_InitializeOverlay(_this, window)) {
            वापस false;
        }
    }

    अगर (!OPENVR_ReleaseFrame(_this)) {
        वापस false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    अगर (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    अगर (!OPENVR_SetupFrame(_this, window)) {
        वापस false;
    }

    वापस true;
}

अटल Uint8 OPENVR_MapMouseButton(पूर्णांक btn)
{
    अगर (btn == EVRMouse_Button_VRMouse_Button_दायाँ) {
        वापस SDL_BUTTON_दायाँ;
    } अन्यथा अगर (btn == EVRMouse_Button_VRMouse_Button_मध्य) {
        वापस SDL_BUTTON_मध्य;
    } अन्यथा {
        वापस SDL_BUTTON_बायाँ;
    }
}

अटल व्योम OPENVR_HandleMouse(भग्न x, भग्न y, पूर्णांक btn, पूर्णांक evt)
{
    अगर (evt == 2) {
        SDL_SendMouseMotion(0, शून्य, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } अन्यथा {
        स्थिर Uint8 button = OPENVR_MapMouseButton(btn);
        स्थिर bool down = (evt != 0);
        SDL_SendMouseButton(0, शून्य, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


अटल bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    वापस true;
}

अटल व्योम OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        वापस;
    }
    EGamepad_Text_निवेश_Mode निवेश_mode;
    चयन (SDL_Get_Text_निवेश_Type(props)) {
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        निवेश_mode = EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Password;
        अवरोध;
    शेष:
        निवेश_mode = EGamepad_Text_निवेश_Mode_k_EGamepad_Text_निवेश_Mode_Normal;
        अवरोध;
    }
    EGamepad_Text_निवेश_पंक्ति_Mode पंक्ति_mode;
    अगर (SDL_Get_Text_निवेश_Multiline(props)) {
        पंक्ति_mode = EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Multiple_पंक्तियाँ;
    } अन्यथा {
        पंक्ति_mode = EGamepad_Text_निवेश_पंक्ति_Mode_k_EGamepad_Text_निवेश_पंक्ति_Mode_Single_पंक्ति;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           निवेश_mode, पंक्ति_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

अटल व्योम OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

अटल SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Cursor *परिणाम = SDL_calloc(1, माप(SDL_Cursor));
    अगर (!परिणाम) {
        वापस शून्य;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_तथ्य *ovrc = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*ovrc));
    अगर (!ovrc) {
        SDL_free(परिणाम);
        वापस शून्य;
    }
    परिणाम->internal = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    वापस परिणाम;
}

अटल bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_तथ्य * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    अगर (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        अगर (e != EVROverlayError_VROverlayError_None) {
            वापस OPENVR_SetOverlayError(e);
        }
        वापस true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    अगर (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        वापस true;
    }

    hotspot.v[0] = (भग्न)ovrc->hot_x / (भग्न)ovrc->w;
    hotspot.v[1] = (भग्न)ovrc->hot_y / (भग्न)ovrc->h;

    texture.handle = (व्योम *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    अगर (e != EVROverlayError_VROverlayError_None) {
        वापस OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    अगर (e != EVROverlayError_VROverlayError_None) {
        वापस OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    अगर (e != EVROverlayError_VROverlayError_None) {
        वापस OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    अगर (e != EVROverlayError_VROverlayError_None) {
        वापस OPENVR_SetOverlayError(e);
    }

    वापस true;
}

अटल व्योम OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    अगर (cursor) {
        SDL_Cursor_तथ्य *ovrc = cursor->internal;
        अगर (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


अटल bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    अगर (!global_openvr_driver) {
        वापस SDL_SetError("OpenVR Overlay not initialized");
    }

    अचिन्हित texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अगर (videodata->bIconOverridden) {
        वापस SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (व्योम *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    अगर (e != EVROverlayError_VROverlayError_None) {
        वापस OPENVR_SetOverlayError(e);
    }
    वापस true;
}

अटल bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonid)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    अक्षर empty = 0;
    अक्षर * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    अक्षर * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    अक्षर * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    वापस true;
}

अटल व्योम InitializeMouseFunctions(व्योम)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

अटल व्योम OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)_this->internal;
    काष्ठा VREvent_t nEvent;
    अगर (videodata->overlayID) {
        जबतक (videodata->oOverlay->Poll_अग्र_Overlay_Event(videodata->overlayID, &nEvent, माप(nEvent))) {
            चयन (nEvent.eventType) {
            हाल EVREventType_VREvent_ButtonPress:
            हाल EVREventType_VREvent_ButtonUnpress:
                अवरोध;
            हाल EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.तथ्य.mouse.x, videodata->targh - nEvent.तथ्य.mouse.y, nEvent.तथ्य.mouse.button, 2);
                अवरोध;
            हाल EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.तथ्य.mouse.x, videodata->targh - nEvent.तथ्य.mouse.y, nEvent.तथ्य.mouse.button, 1);
                अवरोध;
            हाल EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.तथ्य.mouse.x, videodata->targh - nEvent.तथ्य.mouse.y, nEvent.तथ्य.mouse.button, 0);
                अवरोध;
            हाल EVREventType_VREvent_ScrollSmooth:
            हाल EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, शून्य, SDL_GLOBAL_MOUSE_ID, -nEvent.तथ्य.scroll.xdelta, nEvent.तथ्य.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                अवरोध;
            हाल EVREvent_Type_VREvent_Keyboard_Char_निवेश:
                SDL_Send_Keyboard_Unicode_कुंजी(SDL_GetTicksNS(), nEvent.तथ्य.keyboard.c_New_निवेश[0]);
                अवरोध;
            हाल EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                अवरोध;
            हाल EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(शून्य);
                अवरोध;
            हाल EVREventType_VREvent_OverlayClosed:
            हाल EVREventType_VREvent_Quit:
                SDL_SendQuit();
                अवरोध;
            }
        }
    }
}


अटल SDL_VideoDevice *OPENVR_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;
    स्थिर अक्षर *hint;

#अगर_घोषित SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(शून्य, 0, शून्य);
#पूर्ण_अगर

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (device) {
        तथ्य = (काष्ठा SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    } अन्यथा {
        तथ्य = शून्य;
    }
    अगर (!तथ्य) {
#अगर_घोषित SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#पूर्ण_अगर
        SDL_free(device);
        वापस शून्य;
    }
    device->internal = तथ्य;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    अगर (hint) {
        तथ्य->openVRLIB = SDL_LoadObject(hint);
    }
    अगर (!तथ्य->openVRLIB) {
        तथ्य->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    अगर (!तथ्य->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        जाओ error;
    }

    तथ्य->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(तथ्य->openVRLIB, "VR_InitInternal");
    तथ्य->FN_VR_GetVRInitErrorAsEnglishDescription = (स्थिर अक्षर *(*)(EVRInitError error))SDL_LoadFunction(तथ्य->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    तथ्य->FN_VR_GetGenericInterface = (intptr_t (*)(स्थिर अक्षर *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(तथ्य->openVRLIB, "VR_GetGenericInterface");
    अगर (!तथ्य->FN_VR_InitInternal || !तथ्य->FN_VR_GetVRInitErrorAsEnglishDescription || !तथ्य->FN_VR_GetGenericInterface) {
        जाओ error;
    }

    अक्षर fnname[128];
    EVRInitError e;
    तथ्य->vrtoken = तथ्य->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    अगर (!तथ्य->vrtoken) {
        स्थिर अक्षर *err = "Can't get english description";
        अगर (तथ्य->FN_VR_GetVRInitErrorAsEnglishDescription != शून्य)
            err = तथ्य->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        जाओ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    तथ्य->oSystem = (काष्ठा VR_IVRSystem_FnTable *)तथ्य->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    तथ्य->oOverlay = (काष्ठा VR_IVROverlay_FnTable *)तथ्य->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    तथ्य->o_निवेश = (काष्ठा VR_IVRInput_FnTable *)तथ्य->FN_VR_GetGenericInterface(fnname, &e);

    अगर (!तथ्य->oOverlay || !तथ्य->oSystem || !तथ्य->o_निवेश) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    अक्षर *loadpath = 0;
    EVRInputError err;

    अगर (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } अन्यथा {
        स्थिर अक्षर *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    अगर (!loadpath) {
        जाओ error;
    }

    err = तथ्य->o_निवेश->SetActionManifestPath(loadpath);
#अगर_घोषित DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#पूर्ण_अगर
    SDL_free(loadpath);
    अगर (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        अगर (hint) {
            जाओ error;
        }
    } अन्यथा {
        अगर(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(तथ्य)) {
            जाओ error;
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
    device->Set_Window_आकार = OPENVR_Set_Window_आकार;
    device->Get_Window_आकार_In_Pixels = OPENVR_Get_Window_आकार_In_Pixels;
    device->ShowWindow = OPENVR_ShowWindow;
    device->HideWindow = OPENVR_HideWindow;
    device->DestroyWindow = OPENVR_DestroyWindow;
    device->ShowMessageBox = OPENVR_ShowMessageBox;

#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
#अगर_घोषित SDL_VIDEO_OPENGL_WGL
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
#त्रुटि Needs more work to support EGL
#पूर्ण_अगर
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
#पूर्ण_अगर

#अगर defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#अन्यथा
    device->Vulkan_LoadLibrary = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#पूर्ण_अगर

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->SetWindowIcon = OPENVR_SetWindowIcon;

    वापस device;

error:
    OPENVR_Destroy(device);
    वापस शून्य;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, शून्य, false
};

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENVR

