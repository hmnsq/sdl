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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENVR

#எனில் 0
#define DEBUG_OPENVR
#endif

#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_pixels_c.h"
#அந்தர்பாவ "../SDL_egl_c.h"
#அந்தர்பாவ "SDL_openvrvideo.h"

#ifdef SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#அந்தர்பாவ <SDL3/SDL_opengl.h>
#இல்லையெனில்
// Currently only EGL, not OpenGL, is supported on other platforms
#அந்தர்பாவ <SDL3/SDL_opengles2.h>
#அந்தர்பாவ <SDL3/SDL_opengles2_gl2.h>
#endif

#ifdef SDL_VIDEO_DRIVER_WINDOWS
#அந்தர்பாவ "../windows/SDL_windowsopengl.h"
#அந்தர்பாவ "../windows/SDL_windowsvulkan.h"

#define DEFAULT_OPENGL "OPENGL32.DLL"

நிலையான bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
நிலையான SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);

கட்டமைப்பு SDL_GLContextState
{
    HGLRC hglrc;
};
#endif // SDL_VIDEO_DRIVER_WINDOWS



#ifdef SDL_PLATFORM_WINDOWS
#define SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#இல்லையெனில்
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

நிலையான வெறுமை InitializeMouseFunctions(வெறுமை);

கட்டமைப்பு SDL_CursorData
{
    unsigned texture_id_handle;
    முழு hot_x, hot_y;
    முழு w, h;
};

// GL Extensions for functions we will be using.
நிலையான வெறுமை (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
நிலையான வெறுமை (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
நிலையான வெறுமை (APIENTRY *ov_glBindFramebuffer)(GLenum target, GLuint framebuffer);
நிலையான வெறுமை (APIENTRY *ov_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
நிலையான வெறுமை (APIENTRY *ov_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
நிலையான வெறுமை (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
நிலையான வெறுமை (APIENTRY *ov_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
நிலையான GLenum (APIENTRY *ov_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
நிலையான GLenum (APIENTRY *ov_glGetError)(வெறுமை);
நிலையான வெறுமை (APIENTRY *ov_glFlush)(வெறுமை);
நிலையான வெறுமை (APIENTRY *ov_glFinish)(வெறுமை);
நிலையான வெறுமை (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
நிலையான வெறுமை (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
நிலையான வெறுமை (APIENTRY *ov_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
நிலையான வெறுமை (APIENTRY *ov_glTexParameteri)(GLenum target, GLenum pname, GLenum param);
நிலையான வெறுமை (APIENTRY *ov_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, மாறிலி வெறுமை *data);
நிலையான வெறுமை (APIENTRY *ov_glBindTexture)(GLenum target, GLuint texture);
நிலையான வெறுமை (APIENTRY *ov_glDrawBuffers)(GLsizei n, மாறிலி GLenum *bufs);
நிலையான வெறுமை (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * data);
நிலையான மாறிலி GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint index);
நிலையான வெறுமை (APIENTRY *ov_glClear)(GLbitfield mask);
நிலையான வெறுமை (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
நிலையான வெறுமை (APIENTRY *ov_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
நிலையான வெறுமை (APIENTRY *ov_gl_Debug_Message_செருகு)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, மாறிலி எழுத்து *message);

#ifdef SDL_VIDEO_DRIVER_WINDOWS
நிலையான PROC (*ov_wglGetProcAddress)(LPCSTR);
நிலையான HGLRC (*ov_wglCreateContext)(HDC);
நிலையான BOOL (*ov_wglDeleteContext)(HGLRC);
நிலையான BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#endif


#define OPENVR_DEFAULT_WIDTH 1920
#define OPENVR_DEFAULT_HEIGHT 1080

#define OPENVR_SetupProc(proc) { proc = (வெறுமை *)SDL_GL_GetProcAddress((#proc)+3); எனில் (!proc) { failed_extension = (#proc)+3; } }

நிலையான bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    எனில் (!ov_glGetError) {
        மாறிலி எழுத்து * failed_extension = 0;
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
        OPENVR_SetupProc(ov_gl_Debug_Message_செருகு);
        எனில் (failed_extension) {
            திரும்பு SDL_SetError("Error loading GL extension for %s", failed_extension);
        }
    }
    திரும்பு true;
}

நிலையான bool OPENVR_SetOverlayError(EVROverlayError e)
{
    தேர்வு (e) {
#define CASE(X) நிலை EVROverlayError_VROverlayError_##X: திரும்பு SDL_SetError("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(OverlayLimitExceeded);
    CASE(WrongVisibilityType);
    CASE(சாவி_Too_Long);
    CASE(NameTooLong);
    CASE(சாவி_In_Use);
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
    இயல்பு:
        திரும்பு SDL_SetError("Unknown VROverlayError %d", e);
    }
}

நிலையான bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window);

நிலையான bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    மாறிலி எழுத்து * hintWidth = SDL_GetHint("SDL_DEFAULT_WIDTH");
    மாறிலி எழுத்து * hintHeight = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    மாறிலி எழுத்து * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    முழு width = hintWidth ? SDL_atoi(hintWidth) : 0;
    முழு height = hintHeight ? SDL_atoi(hintHeight) : 0;
    முழு fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_mode.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_mode.w = OPENVR_DEFAULT_WIDTH;
    display.desktop_mode.h = OPENVR_DEFAULT_HEIGHT;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    எனில் (height > 0 && width > 0) {
        display.desktop_mode.w = width;
        display.desktop_mode.h = height;
    }
    எனில் (fps) {
        display.desktop_mode.refresh_rate = fps;
    } இல்லையெனில் {
        display.desktop_mode.refresh_rate = data->oSystem->GetFloatTrackedDeviceProperty(k_unTrackedDeviceIndex_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (எழுத்து *)"OpenVRDisplay";
    SDL_AddVideoDisplay(&display, false);

    திரும்பு true;
}

நிலையான வெறுமை OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

நிலையான வெறுமை OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#endif

    எனில் (data) {
        எனில் (data->openVRLIB) {
            SDL_UnloadObject(data->openVRLIB);
        }
    }
    SDL_free(device->internal);
    SDL_free(device);
}

நிலையான uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    முழு w = surf->w;
    முழு h = surf->h;
    முழு pitch = surf->pitch;
    முழு x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    க்கு(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        க்கு(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    திரும்பு pxd;
}

நிலையான bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    எனில் (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_WIDTH;
        videodata->targh = OPENVR_DEFAULT_HEIGHT;
    }

    எனில் (videodata->targh != videodata->last_targh
     || videodata->targw != videodata->last_targw) {

        கட்டமைப்பு HmdVector2_t ms;
        முழு status;

        எனில் (videodata->fbo <= 0) {
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
        எனில் (status != GL_FRAMEBUFFER_COMPLETE) {
            திரும்பு SDL_SetError("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (தசம)videodata->targw;
        ms.v[1] = (தசம)videodata->targh;
        videodata->oOverlay->SetOverlayMouseScale(videodata->overlayID, &ms);

        videodata->last_targh = videodata->targh;
        videodata->last_targw = videodata->targw;
    }
    திரும்பு true;
}

நிலையான bool OPENVR_VirtualControllerRumble(வெறுமை *userdata, Uint16 கீழ்_frequency_rumble, Uint16 உயர்வு_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;

    மாறிலி தசம k_flIntensity = 320.f; // Maximum frequency
    தசம fl_இடது_Frequency = (தசம)கீழ்_frequency_rumble * k_flIntensity / 65535.f;
    தசம fl_வலது_Frequency = (தசம)உயர்வு_frequency_rumble * k_flIntensity / 65535.f;
    தசம flDurationSeconds = 2.f;
    தசம flAmplitude = 1.f;

    videodata->o_உள்ளீடு->TriggerHapticVibrationAction(videodata->உள்ளீடு_action_handles_haptics[0], 0, flDurationSeconds, fl_இடது_Frequency, flAmplitude, 0);
    videodata->o_உள்ளீடு->TriggerHapticVibrationAction(videodata->உள்ளீடு_action_handles_haptics[1], 0, flDurationSeconds, fl_வலது_Frequency, flAmplitude, 0);

    திரும்பு true;
}

நிலையான bool OPENVR_VirtualControllerRumbleTriggers(வெறுமை *userdata, Uint16 இடது_rumble, Uint16 வலது_rumble)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    videodata->o_உள்ளீடு->TriggerHapticVibrationAction(videodata->உள்ளீடு_action_handles_haptics[0], 0, 0.1f, இடது_rumble, 1.0, 0);
    videodata->o_உள்ளீடு->TriggerHapticVibrationAction(videodata->உள்ளீடு_action_handles_haptics[1], 0, 0.1f, வலது_rumble, 1.0, 0);
    திரும்பு true;
}

நிலையான வெறுமை OPENVR_VirtualControllerUpdate(வெறுமை *userdata)
{
    SDL_VideoData *videodata = (SDL_VideoData *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    உள்ளீடு_Digital_Action_Data_t digital_உள்ளீடு_action;
    உள்ளீடு_Analog_Action_Data_t analog_உள்ளீடு_action;
    EVRInputError e;
#ifdef DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#endif
    VRActiveActionSet_t actionSet = { 0 };
    actionSet.ulActionSet = videodata->உள்ளீடு_action_set;
    e = videodata->o_உள்ளீடு->UpdateActionState(&actionSet, அளவு(actionSet), 1);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#endif
        திரும்பு;
    }

    க்கு (முழு d = 0; d < videodata->உள்ளீடு_action_handles_buttons_மொத்தம்; d++)
    {
        எனில் (videodata->உள்ளீடு_action_handles_buttons[d] == k_ulInvalidActionHandle)
            தொடர்;
        e = videodata->o_உள்ளீடு->GetDigitalActionData(videodata->உள்ளீடு_action_handles_buttons[d], &digital_உள்ளீடு_action, அளவு(digital_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
        எனில் (e)
        {
#ifdef DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#endif
            திரும்பு;
        }
        SDL_SetJoystickVirtualButton(joystick, d, digital_உள்ளீடு_action.bState);
#ifdef DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#endif
    }

    // Left Stick
    e = videodata->o_உள்ளீடு->GetAnalogActionData(videodata->உள்ளீடு_action_handles_axes[0], &analog_உள்ளீடு_action, அளவு(analog_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#endif
        திரும்பு;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_உள்ளீடு_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_உள்ளீடு_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_உள்ளீடு->GetAnalogActionData(videodata->உள்ளீடு_action_handles_axes[1], &analog_உள்ளீடு_action, அளவு(analog_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#endif
        திரும்பு;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_உள்ளீடு_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_உள்ளீடு_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_உள்ளீடு->GetAnalogActionData(videodata->உள்ளீடு_action_handles_axes[2], &analog_உள்ளீடு_action, அளவு(analog_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#endif
        திரும்பு;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_இடது_TRIGGER, (Sint16)((analog_உள்ளீடு_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_உள்ளீடு->GetAnalogActionData(videodata->உள்ளீடு_action_handles_axes[3], &analog_உள்ளீடு_action, அளவு(analog_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#endif
        திரும்பு;
    }
    SDL_SetJoystickVirtualAxis(joystick, SDL_GAMEPAD_AXIS_வலது_TRIGGER, (Sint16)((analog_உள்ளீடு_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#எனில் 0
    க்கு (a = 0; a < videodata->உள்ளீடு_action_handles_axes_மொத்தம்; a++)
    {
        தசம xval = 0.0f;
        e = videodata->o_உள்ளீடு->GetAnalogActionData(videodata->உள்ளீடு_action_handles_axes[a], &analog_உள்ளீடு_action, அளவு(analog_உள்ளீடு_action), k_ul_Invalid_உள்ளீடு_மதிப்பு_Handle);
        எனில் (e) செல் updatefail;
        xval = analog_உள்ளீடு_action.x;
        எனில் (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        எனில் (a == SDL_GAMEPAD_AXIS_இடது_TRIGGER || a == SDL_GAMEPAD_AXIS_வலது_TRIGGER)
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
    திரும்பு;
}

நிலையான bool OPENVR_SetupJoystickBasedOnLoadedActionManifest(SDL_VideoData * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    எழுத்து * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_மொத்தம்] = {
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
    எழுத்து * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    எனில் ((e = videodata->o_உள்ளீடு->GetActionSetHandle("/actions/virtualgamepad", &videodata->உள்ளீடு_action_set)) != EVRInputError_VRInputError_None)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#endif
        திரும்பு SDL_SetError("Failed to get action set handle");
    }

    videodata->உள்ளீடு_action_handles_buttons_மொத்தம் = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->உள்ளீடு_action_handles_buttons = SDL_malloc(videodata->உள்ளீடு_action_handles_buttons_மொத்தம் * அளவு(VRActionHandle_t));

    க்கு (முழு i = 0; i < videodata->உள்ளீடு_action_handles_buttons_மொத்தம்; i++)
    {
        e = videodata->o_உள்ளீடு->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->உள்ளீடு_action_handles_buttons[i]);
        எனில் (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            திரும்பு SDL_SetError("ERROR: Failed to get button action");
        }
    }

    videodata->உள்ளீடு_action_handles_axes_மொத்தம் = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->உள்ளீடு_action_handles_axes = SDL_malloc(videodata->உள்ளீடு_action_handles_axes_மொத்தம் * அளவு(VRActionHandle_t));

    க்கு (முழு i = 0; i < videodata->உள்ளீடு_action_handles_axes_மொத்தம்; i++)
    {
        e = videodata->o_உள்ளீடு->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->உள்ளீடு_action_handles_axes[i]);
        எனில் (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            திரும்பு SDL_SetError("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_உள்ளீடு->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->உள்ளீடு_action_handles_haptics[0]);
    e |= videodata->o_உள்ளீடு->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->உள்ளீடு_action_handles_haptics[1]);
    எனில் (e)
    {
#ifdef DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#endif
        திரும்பு SDL_SetError("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_மொத்தம்;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_மொத்தம்;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    எனில் (!virtual_id) {
        திரும்பு SDL_SetError("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    எனில் (!videodata->virtual_joystick) {
        திரும்பு SDL_SetError("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ifdef DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->உள்ளீடு_action_handles_buttons_மொத்தம், videodata->உள்ளீடு_action_handles_axes_மொத்தம்);
#endif

    திரும்பு true;
}

நிலையான bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // Wait til here, to make sure we have our context setup correctly.
    எனில் (!OPENVR_InitExtensions(_this)) {
        திரும்பு false;
    }

    // Generate the overlay.
    {
        மாறிலி எழுத்து * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        எழுத்து * cursorname = 0;
        எனில் (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        எனில் (!videodata->sOverlayName) {
            திரும்பு false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        எனில் (!cursorname) {
            திரும்பு false;
        }

        EVROverlayError result = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            window->title, &videodata->overlayID, &videodata->thumbID);
        எனில் (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            திரும்பு SDL_SetError("Could not create dashboard overlay (%d)", result );
        }
        result = videodata->oOverlay->CreateOverlay(cursorname, window->title, &videodata->cursorID);
        எனில் (result != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            திரும்பு SDL_SetError("Could not create cursor overlay (%d)", result );
        }
        SDL_PropertiesID props = SDL_GetWindowProperties(window);
        SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_OPENVR_OVERLAY_ID_எண், videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        மாறிலி எழுத்து *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        எனில் (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } இல்லையெனில் {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#எனில் 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#endif
        }

        க்கு (முழு i = 0; i < அளவு(overlay_flags) * 8; ++i) {
            எனில் (overlay_flags & (1 << i)) {
                videodata->oOverlay->SetOverlayFlag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        மாறிலி எழுத்து * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        தசம fWidth = hint ? (தசம)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->overlayID, fWidth);
    }
    {
        மாறிலி எழுத்து * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        தசம fCursorWidth = hint ? (தசம)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->SetOverlayWidthInMeters(videodata->cursorID, fCursorWidth * 0.5f);
    }
    {
        மாறிலி எழுத்து * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        எனில் (hint) {
            எழுத்து * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->SetOverlayFromFile(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            எனில் (err == EVROverlayError_VROverlayError_None) {
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

    எனில் (!OPENVR_CheckRenderbuffer(_this)) {
        திரும்பு false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->SetOverlayName(videodata->overlayID, window->title);

    videodata->bDidCreateOverlay = true;
    videodata->window = window;

    திரும்பு true;
}


நிலையான bool OPENVR_SetupFrame(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    நிலையான மாறிலி GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_buffer_rendering = true;

#ifdef DEBUG_OPENVR
    {
        முழு error = ov_glGetError();
        எனில் (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
    }
#endif

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    எனில் (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_glColorMask(false, false, false, true);
        ov_glClear(GL_COLOR_BUFFER_BIT);
        ov_glColorMask(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    திரும்பு true;
}

நிலையான bool OPENVR_ReleaseFrame(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    எனில் (!ov_glGetError) {
        திரும்பு true;
    }

    எனில் (!videodata->is_buffer_rendering) {
        திரும்பு true;
    }

#ifdef DEBUG_OPENVR
    {
        முழு error = ov_glGetError();
        எனில் (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_glCheckNamedFramebufferStatus(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#endif

    videodata->is_buffer_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    எனில் (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->last_targh &&
        videodata->targw == videodata->last_targw) {
        // Only submit frames to OpenVR if the texture exists.
        கட்டமைப்பு Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (வெறுமை *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->SetOverlayTexture(videodata->overlayID, &tex);
    }

    எனில் (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    எனில் (videodata->renderdoc_debugmarker_frame_end) {
        ov_gl_Debug_Message_செருகு(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    திரும்பு OPENVR_CheckRenderbuffer(_this);
}

நிலையான வெறுமை OPENVR_HandleResize(SDL_VideoDevice *_this, முழு w, முழு h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    data->targw = w;
    data->targh = h;
}

நிலையான bool OPENVR_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    திரும்பு true;
}


#ifdef SDL_VIDEO_DRIVER_WINDOWS
நிலையான LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT செய்தி, WPARAM wParam, LPARAM lParam)
{
    தேர்வு (செய்தி) {
    நிலை WM_DESTROY:
        திரும்பு 0;
    }
    திரும்பு DefWindowProc(hwnd, செய்தி, wParam, lParam);
}

நிலையான bool OPENVR_GL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    எனில் (path == வெற்று) {
        path = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    எனில் (path == வெற்று) {
        path = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_LoadObject(path);
    எனில் (!_this->gl_config.dll_handle) {
        திரும்பு false;
    }
    SDL_strlcpy(_this->gl_config.driver_path, path,
                 SDL_arraysize(_this->gl_config.driver_path));

    // Allocate OpenGL memory
    _this->gl_data = (கட்டமைப்பு SDL_GLDriverData *)SDL_calloc(1, அளவு(கட்டமைப்பு SDL_GLDriverData));
    எனில் (!_this->gl_data) {
        திரும்பு false;
    }
    _this->gl_config.driver_loaded = true;

    திரும்பு true;
}

நிலையான SDL_FunctionPointer OPENVR_GL_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc)
{
    SDL_FunctionPointer result = வெற்று;
    எனில் (ov_wglGetProcAddress) {
        result = (SDL_FunctionPointer)ov_wglGetProcAddress(proc);
        எனில் (result) {
            திரும்பு result;
        }
    }

    திரும்பு SDL_LoadFunction(_this->gl_config.dll_handle, proc);
}

நிலையான வெறுமை OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

நிலையான SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)
{
    GLint இலக்கம்_Extensions;
    முழு i;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(வெற்று);
        wnd.hIcon = LoadIcon(வெற்று, IDI_APPLICATION);
        wnd.hCursor = LoadCursor(வெற்று, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = வெற்று;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        RegisterClassA(&wnd);
        hwnd = CreateWindowA("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, வெற்று, வெற்று, GetModuleHandle(வெற்று), வெற்று);

        செய்தி_2 செய்தி;
        போது (PeekMessage(&செய்தி, வெற்று, 0, 0, PM_REMOVE)) {
            TranslateMessage(&செய்தி);
            DispatchMessage(&செய்தி);
        }

        videodata->hdc = GetDC(hwnd);

        நிலையான  PIXELFORMATDESCRIPTOR pfd =
        {
            அளவு(PIXELFORMATDESCRIPTOR),
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
        எனில் (!SetPixelFormat(videodata->hdc, PixelFormat, &pfd)) {
            SDL_SetError( "Could not set pixel format" );
            திரும்பு வெற்று;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        எனில் (!opengl) {
            SDL_SetError("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            திரும்பு வெற்று;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))GetProcAddress(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))GetProcAddress(opengl, "wglCreateContext");
        ov_wglGetProcAddress = (PROC(*)(LPCSTR))GetProcAddress(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))GetProcAddress(opengl, "wglDeleteContext");
        எனில் (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_SetError("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            திரும்பு வெற்று;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        எனில் (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_SetError("Could not make current OpenGL context.");
            திரும்பு வெற்று;
        }
    }

    i = OPENVR_InitExtensions(_this);
    எனில் (i == 0) {
        திரும்பு வெற்று;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_இலக்கம்_EXTENSIONS, &இலக்கம்_Extensions);
    க்கு (i = 0; i < இலக்கம்_Extensions; i++) {
        மாறிலி எழுத்து *ccc = (மாறிலி எழுத்து *)ov_glGetStringi(GL_EXTENSIONS, i);
        எனில் (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#endif
            videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    எனில் (!videodata->bDidCreateOverlay) {
        எனில் (!OPENVR_InitializeOverlay(_this, window)) {
            திரும்பு வெற்று;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    SDL_GLContext result = SDL_malloc(அளவு(கட்டமைப்பு SDL_GLContextState));
    எனில் (!result) {
        திரும்பு வெற்று;
    }
    result->hglrc = videodata->hglrc;
    திரும்பு result;
}

நிலையான bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    திரும்பு true;
}

நிலையான bool OPENVR_GL_SetSwapInterval(SDL_VideoDevice *_this, முழு interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    திரும்பு true;
}

நிலையான bool OPENVR_GL_GetSwapInterval(SDL_VideoDevice *_this, முழு *swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (swapInterval)
        *swapInterval = videodata->swap_interval;
    இல்லையெனில்
        திரும்பு SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    திரும்பு true;
}

நிலையான bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    ov_wglMakeCurrent(videodata->hdc, வெற்று);
    ov_wglDeleteContext(videodata->hglrc);
    திரும்பு true;
}


#இல்லையெனில்

நிலையான EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

நிலையான bool SDL_EGL_InitInternal(SDL_VideoData * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=வெற்று;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#endif

    எனில் (vd->eglDpy == 0) {
        திரும்பு SDL_SetError("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    எனில் (!b) {
        திரும்பு SDL_SetError("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ifdef DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#endif

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ifdef DEBUG_OPENVR
    {
        முழு err = eglGetError();
        எனில் (err != EGL_SUCCESS) {
            திரும்பு SDL_SetError("EGL Error after eglCreateContext %d", err);
        }
    }
#endif

    எனில் (!vd->eglCtx) {
        திரும்பு SDL_SetError("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    திரும்பு true;
}

// Linux, EGL, etc.
நிலையான bool OVR_EGL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path)
{
    திரும்பு SDL_EGL_LoadLibrary(_this, path, EGL_DEFAULT_DISPLAY);
}

நிலையான SDL_FunctionPointer OVR_EGL_GetProcAddress(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc)
{
    திரும்பு SDL_EGL_GetProcAddress(proc);
}
நிலையான வெறுமை OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
நிலையான SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_Window * window)
{
    GLint இலக்கம்_Extensions;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (!videodata->eglCtx) {
        எனில் (!SDL_EGL_InitInternal(videodata)) {
            திரும்பு வெற்று;
        }
    }

    எனில் (!OPENVR_InitExtensions(_this)) {
        திரும்பு வெற்று;
    }

    videodata->renderdoc_debugmarker_frame_end = false;

    ov_glGetIntegerv(GL_இலக்கம்_EXTENSIONS, &இலக்கம்_Extensions);
    க்கு(முழு i = 0; i < இலக்கம்_Extensions; i++) {
        மாறிலி எழுத்து * ccc = (மாறிலி எழுத்து *)ov_glGetStringi(GL_EXTENSIONS, i);
        எனில் (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ifdef DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#endif
           videodata->renderdoc_debugmarker_frame_end = true;
        }
    }

    எனில் (!videodata->bDidCreateOverlay) {
        எனில் (!OPENVR_InitializeOverlay(_this, window)) {
            திரும்பு வெற்று;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_SetupFrame(_this, window);

    திரும்பு videodata->eglCtx;
}

நிலையான bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window * wnd, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    திரும்பு true;
}

நிலையான bool OVR_EGL_SetSwapInterval(SDL_VideoDevice *_this, முழு interval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->swap_interval = interval;
    திரும்பு true;
}

நிலையான bool OVR_EGL_GetSwapInterval(SDL_VideoDevice *_this, முழு * swapInterval)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (swapInterval)
        *swapInterval = videodata->swap_interval;
    இல்லையெனில்
        திரும்பு SDL_SetError("OPENVR: null passed in for GetSwapInterval");
    திரும்பு true;
}

நிலையான bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    திரும்பு true;
}

#endif

நிலையான bool OPENVR_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, அளவு(SDL_WindowData));
    எனில் (data == வெற்று) {
        திரும்பு SDL_OutOfMemory();
    }

    window->max_w = 4096;
    window->max_h = 4096;
    window->min_w = 1;
    window->min_h = 1;

    // Setup driver data for this window
    window->internal = data;
    திரும்பு true;
}


நிலையான வெறுமை OPENVR_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);
    window->internal = வெற்று;
}

நிலையான வெறுமை OPENVR_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData * data = (SDL_VideoData *)_this->internal;
    எனில் (data->bDidCreateOverlay) {
        data->oOverlay->SetOverlayName(data->overlayID, window->title);
    }
}

நிலையான வெறுமை OPENVR_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;

    எனில் (window->pending.w != window->w) {
        window->w = window->pending.w;
    }

    எனில் (window->pending.h != window->h) {
        window->h = window->pending.h;
    }

    எனில் (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->w, window->h);
}

நிலையான வெறுமை OPENVR_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, முழு *w, முழு *h)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    *w = data->targw;
    *h = data->targh;
}

நிலையான வெறுமை OPENVR_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->internal;
    எனில் (data->targh != window->h || data->targw != window->w) {
        OPENVR_HandleResize(_this, window->w, window->h);
    }

    data->oOverlay->ShowDashboard(data->sOverlayName);

    window->flags |= (SDL_WINDOW_உள்ளீடு_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    SDL_SetKeyboardFocus(window);
}

நிலையான வெறுமை OPENVR_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    திரும்பு;
}

நிலையான bool OPENVR_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    எனில் (!videodata->bDidCreateOverlay) {
        எனில் (!OPENVR_InitializeOverlay(_this, window)) {
            திரும்பு false;
        }
    }

    எனில் (!OPENVR_ReleaseFrame(_this)) {
        திரும்பு false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    எனில் (videodata->swap_interval != 0) {
        videodata->oOverlay->WaitFrameSync(100);
    }

    எனில் (!OPENVR_SetupFrame(_this, window)) {
        திரும்பு false;
    }

    திரும்பு true;
}

நிலையான Uint8 OPENVR_MapMouseButton(முழு btn)
{
    எனில் (btn == EVRMouse_Button_VRMouse_Button_வலது) {
        திரும்பு SDL_BUTTON_வலது;
    } இல்லையெனில் எனில் (btn == EVRMouse_Button_VRMouse_Button_நடு) {
        திரும்பு SDL_BUTTON_நடு;
    } இல்லையெனில் {
        திரும்பு SDL_BUTTON_இடது;
    }
}

நிலையான வெறுமை OPENVR_HandleMouse(தசம x, தசம y, முழு btn, முழு evt)
{
    எனில் (evt == 2) {
        SDL_SendMouseMotion(0, வெற்று, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } இல்லையெனில் {
        மாறிலி Uint8 button = OPENVR_MapMouseButton(btn);
        மாறிலி bool down = (evt != 0);
        SDL_SendMouseButton(0, வெற்று, SDL_GLOBAL_MOUSE_ID, button, down);
    }
}


நிலையான bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    திரும்பு true;
}

நிலையான வெறுமை OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        திரும்பு;
    }
    EGamepad_Text_உள்ளீடு_Mode உள்ளீடு_mode;
    தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
    நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
    நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_HIDDEN:
        உள்ளீடு_mode = EGamepad_Text_உள்ளீடு_Mode_k_EGamepad_Text_உள்ளீடு_Mode_Password;
        நிறுத்து;
    இயல்பு:
        உள்ளீடு_mode = EGamepad_Text_உள்ளீடு_Mode_k_EGamepad_Text_உள்ளீடு_Mode_Normal;
        நிறுத்து;
    }
    EGamepad_Text_உள்ளீடு_வரி_Mode வரி_mode;
    எனில் (SDL_Get_Text_உள்ளீடு_Multiline(props)) {
        வரி_mode = EGamepad_Text_உள்ளீடு_வரி_Mode_k_EGamepad_Text_உள்ளீடு_வரி_Mode_Multiple_வரிகள்;
    } இல்லையெனில் {
        வரி_mode = EGamepad_Text_உள்ளீடு_வரி_Mode_k_EGamepad_Text_உள்ளீடு_வரி_Mode_Single_வரி;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           உள்ளீடு_mode, வரி_mode,
           EKeyboardFlags_KeyboardFlag_Minimal, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

நிலையான வெறுமை OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

நிலையான SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, முழு hot_x, முழு hot_y)
{
    SDL_Cursor *result = SDL_calloc(1, அளவு(SDL_Cursor));
    எனில் (!result) {
        திரும்பு வெற்று;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_CursorData *ovrc = (SDL_CursorData *)SDL_calloc(1, அளவு(*ovrc));
    எனில் (!ovrc) {
        SDL_free(result);
        திரும்பு வெற்று;
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

    திரும்பு result;
}

நிலையான bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_CursorData * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    எனில் (!cursor) {
        global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        எனில் (e != EVROverlayError_VROverlayError_None) {
            திரும்பு OPENVR_SetOverlayError(e);
        }
        திரும்பு true;
    }

    global_openvr_driver->oOverlay->SetOverlayFlag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->internal;

    எனில் (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        திரும்பு true;
    }

    hotspot.v[0] = (தசம)ovrc->hot_x / (தசம)ovrc->w;
    hotspot.v[1] = (தசம)ovrc->hot_y / (தசம)ovrc->h;

    texture.handle = (வெறுமை *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->SetOverlayTextureBounds(global_openvr_driver->cursorID, &tb);
    எனில் (e != EVROverlayError_VROverlayError_None) {
        திரும்பு OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTransformCursor(global_openvr_driver->cursorID, &hotspot);
    எனில் (e != EVROverlayError_VROverlayError_None) {
        திரும்பு OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayTexture(global_openvr_driver->cursorID, &texture);
    எனில் (e != EVROverlayError_VROverlayError_None) {
        திரும்பு OPENVR_SetOverlayError(e);
    }

    e = global_openvr_driver->oOverlay->SetOverlayCursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    எனில் (e != EVROverlayError_VROverlayError_None) {
        திரும்பு OPENVR_SetOverlayError(e);
    }

    திரும்பு true;
}

நிலையான வெறுமை OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    எனில் (cursor) {
        SDL_CursorData *ovrc = cursor->internal;
        எனில் (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


நிலையான bool OPENVR_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window * window, SDL_Surface * icon)
{
    எனில் (!global_openvr_driver) {
        திரும்பு SDL_SetError("OpenVR Overlay not initialized");
    }

    unsigned texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எனில் (videodata->bIconOverridden) {
        திரும்பு SDL_SetError("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (வெறுமை *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->SetOverlayTexture(videodata->thumbID, &texture);
    எனில் (e != EVROverlayError_VROverlayError_None) {
        திரும்பு OPENVR_SetOverlayError(e);
    }
    திரும்பு true;
}

நிலையான bool OPENVR_ShowMessageBox(SDL_VideoDevice *_this,மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonid)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    எழுத்து empty = 0;
    எழுத்து * message = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    எழுத்து * title = SDL_strdup(messageboxdata->message?messageboxdata->message:"");
    எழுத்து * ok = SDL_strdup("Ok");
    videodata->oOverlay->ShowMessageOverlay(message, title, ok, &empty, &empty, &empty);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(message);
    திரும்பு true;
}

நிலையான வெறுமை InitializeMouseFunctions(வெறுமை)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

நிலையான வெறுமை OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = (SDL_VideoData *)_this->internal;
    கட்டமைப்பு VREvent_t nEvent;
    எனில் (videodata->overlayID) {
        போது (videodata->oOverlay->PollNextOverlayEvent(videodata->overlayID, &nEvent, அளவு(nEvent))) {
            தேர்வு (nEvent.eventType) {
            நிலை EVREventType_VREvent_ButtonPress:
            நிலை EVREventType_VREvent_ButtonUnpress:
                நிறுத்து;
            நிலை EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 2);
                நிறுத்து;
            நிலை EVREventType_VREvent_MouseButtonDown:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 1);
                நிறுத்து;
            நிலை EVREventType_VREvent_MouseButtonUp:
                OPENVR_HandleMouse(nEvent.data.mouse.x, videodata->targh - nEvent.data.mouse.y, nEvent.data.mouse.button, 0);
                நிறுத்து;
            நிலை EVREventType_VREvent_ScrollSmooth:
            நிலை EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, வெற்று, SDL_GLOBAL_MOUSE_ID, -nEvent.data.scroll.xdelta, nEvent.data.scroll.ydelta, SDL_MOUSEWHEEL_NORMAL);
                நிறுத்து;
            நிலை EVREvent_Type_VREvent_Keyboard_Char_உள்ளீடு:
                SDL_Send_Keyboard_Unicode_சாவி(SDL_GetTicksNS(), nEvent.data.keyboard.c_New_உள்ளீடு[0]);
                நிறுத்து;
            நிலை EVREventType_VREvent_OverlayShown:
                SDL_SetKeyboardFocus(videodata->window);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
                நிறுத்து;
            நிலை EVREventType_VREvent_OverlayHidden:
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
                SDL_SendWindowEvent(videodata->window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
                SDL_SetKeyboardFocus(வெற்று);
                நிறுத்து;
            நிலை EVREventType_VREvent_OverlayClosed:
            நிலை EVREventType_VREvent_Quit:
                SDL_SendQuit();
                நிறுத்து;
            }
        }
    }
}


நிலையான SDL_VideoDevice *OPENVR_CreateDevice(வெறுமை)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    மாறிலி எழுத்து *hint;

#ifdef SDL_PLATFORM_WINDOWS
    SDL_RegisterApp(வெற்று, 0, வெற்று);
#endif

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (device) {
        data = (கட்டமைப்பு SDL_VideoData *)SDL_calloc(1, அளவு(SDL_VideoData));
    } இல்லையெனில் {
        data = வெற்று;
    }
    எனில் (!data) {
#ifdef SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#endif
        SDL_free(device);
        திரும்பு வெற்று;
    }
    device->internal = data;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    எனில் (hint) {
        data->openVRLIB = SDL_LoadObject(hint);
    }
    எனில் (!data->openVRLIB) {
        data->openVRLIB = SDL_LoadObject(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    எனில் (!data->openVRLIB) {
        SDL_SetError("Could not open OpenVR API Library");
        செல் error;
    }

    data->FN_VR_InitInternal = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_LoadFunction(data->openVRLIB, "VR_InitInternal");
    data->FN_VR_GetVRInitErrorAsEnglishDescription = (மாறிலி எழுத்து *(*)(EVRInitError error))SDL_LoadFunction(data->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    data->FN_VR_GetGenericInterface = (intptr_t (*)(மாறிலி எழுத்து *pchInterfaceVersion, EVRInitError * peError))SDL_LoadFunction(data->openVRLIB, "VR_GetGenericInterface");
    எனில் (!data->FN_VR_InitInternal || !data->FN_VR_GetVRInitErrorAsEnglishDescription || !data->FN_VR_GetGenericInterface) {
        செல் error;
    }

    எழுத்து fnname[128];
    EVRInitError e;
    data->vrtoken = data->FN_VR_InitInternal(&e, EVRApplicationType_VRApplication_Overlay);
    எனில் (!data->vrtoken) {
        மாறிலி எழுத்து *err = "Can't get english description";
        எனில் (data->FN_VR_GetVRInitErrorAsEnglishDescription != வெற்று)
            err = data->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_SetError("Could not generate OpenVR Context (%s)", err);
        செல் error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_Version);
    data->oSystem = (கட்டமைப்பு VR_IVRSystem_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_Version);
    data->oOverlay = (கட்டமைப்பு VR_IVROverlay_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_Version);
    data->o_உள்ளீடு = (கட்டமைப்பு VR_IVRInput_FnTable *)data->FN_VR_GetGenericInterface(fnname, &e);

    எனில் (!data->oOverlay || !data->oSystem || !data->o_உள்ளீடு) {
        SDL_SetError("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_Version, IVROverlay_Version, IVRInput_Version);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    எழுத்து *loadpath = 0;
    EVRInputError err;

    எனில் (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } இல்லையெனில் {
        மாறிலி எழுத்து *basepath = SDL_GetBasePath();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    எனில் (!loadpath) {
        செல் error;
    }

    err = data->o_உள்ளீடு->SetActionManifestPath(loadpath);
#ifdef DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#endif
    SDL_free(loadpath);
    எனில் (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        எனில் (hint) {
            செல் error;
        }
    } இல்லையெனில் {
        எனில்(!OPENVR_SetupJoystickBasedOnLoadedActionManifest(data)) {
            செல் error;
        }
    }

    // Setup amount of available displays
    device->இலக்கம்_displays = 0;

    // Set device free function
    device->விடுவி = OPENVR_Destroy;

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
#இல்லையெனில்
#error Needs more work to support EGL
#endif
#இல்லையெனில்
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

#எனில் defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_LoadLibrary = WIN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#இல்லையெனில்
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

    திரும்பு device;

error:
    OPENVR_Destroy(device);
    திரும்பு வெற்று;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, வெற்று, false
};

#endif // SDL_VIDEO_DRIVER_OPENVR

