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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENVR

#ఒకవేళ 0
#నిర్వచించు DEBUG_OPENVR
#అయితే_ముగింపు

#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../SDL_egl_c.h"
#అన్తర్భావ "SDL_openvrvideo.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#అన్తర్భావ <SDL3/SDL_opengl.h>
#లేకపోతే
// Currently only EGL, not OpenGL, is supported on other platforms
#అన్తర్భావ <SDL3/SDL_opengles2.h>
#అన్తర్భావ <SDL3/SDL_opengles2_gl2.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
#అన్తర్భావ "../windows/SDL_windowsopengl.h"
#అన్తర్భావ "../windows/SDL_windowsvulkan.h"

#నిర్వచించు DEFAULT_OPENGL "OPENGL32.DLL"

స్థిర bool OPENVR_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
స్థిర SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

నిర్మాణం SDL_GLContextState
{
    HGLRC hglrc;
};
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS



#నిర్వచితమైతే SDL_PLATFORM_WINDOWS
#నిర్వచించు SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#లేకపోతే
#నిర్వచించు SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#అయితే_ముగింపు

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#నిర్వచించు MARKER_ID 0
#నిర్వచించు MARKER_STR "vr-marker,frame_end,type,application"

#నిర్వచనం_రద్దు EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_దత్తాంశం * global_openvr_driver;

స్థిర శూన్య InitializeMouseFunctions(శూన్య);

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    గుర్తులేని texture_id_handle;
    పూర్ణాంకం hot_x, hot_y;
    పూర్ణాంకం w, h;
};

// GL Extensions for functions we will be using.
స్థిర శూన్య (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
స్థిర శూన్య (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
స్థిర శూన్య (APIENTRY *ov_glBindFramebuffer)(GLenum లక్ష్యం, GLuint framebuffer);
స్థిర శూన్య (APIENTRY *ov_glBindRenderbuffer)(GLenum లక్ష్యం, GLuint renderbuffer);
స్థిర శూన్య (APIENTRY *ov_glRenderbufferStorage)(GLenum లక్ష్యం, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
స్థిర శూన్య (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum లక్ష్యం, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
స్థిర శూన్య (APIENTRY *ov_glFramebufferTexture2D)(GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
స్థిర GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_స్థితి)(GLuint framebuffer, GLenum లక్ష్యం);
స్థిర GLenum (APIENTRY *ov_glGetError)(శూన్య);
స్థిర శూన్య (APIENTRY *ov_glFlush)(శూన్య);
స్థిర శూన్య (APIENTRY *ov_gl_ముగింపు)(శూన్య);
స్థిర శూన్య (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
స్థిర శూన్య (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
స్థిర శూన్య (APIENTRY *ov_glTexParameterf)(GLenum లక్ష్యం, GLenum pname, GLfloat param);
స్థిర శూన్య (APIENTRY *ov_glTexParameteri)(GLenum లక్ష్యం, GLenum pname, GLenum param);
స్థిర శూన్య (APIENTRY *ov_glTexImage2D)(GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *దత్తాంశం);
స్థిర శూన్య (APIENTRY *ov_glBindTexture)(GLenum లక్ష్యం, GLuint texture);
స్థిర శూన్య (APIENTRY *ov_glDrawBuffers)(GLsizei n, స్థిరరాశి GLenum *bufs);
స్థిర శూన్య (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * దత్తాంశం);
స్థిర స్థిరరాశి GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint సూచీ);
స్థిర శూన్య (APIENTRY *ov_glClear)(GLbitfield ముసుగు);
స్థిర శూన్య (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
స్థిర శూన్య (APIENTRY *ov_gl_Color_ముసుగు)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
స్థిర శూన్య (APIENTRY *ov_gl_Debug_సందేశం_చొప్పించు)(GLenum ఆధారం, GLenum type, GLuint id, GLenum severity, GLsizei నిడివి, స్థిరరాశి అక్షరం *సందేశం);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
స్థిర PROC (*ov_wgl_Get_Proc_చిరునామా)(LPCSTR);
స్థిర HGLRC (*ov_wglCreateContext)(HDC);
స్థిర BOOL (*ov_wglDeleteContext)(HGLRC);
స్థిర BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#అయితే_ముగింపు


#నిర్వచించు OPENVR_DEFAULT_వెడల్పు 1920
#నిర్వచించు OPENVR_DEFAULT_ఎత్తు 1080

#నిర్వచించు OPENVR_అమరిక_Proc(proc) { proc = (శూన్య *)SDL_GL_Get_Proc_చిరునామా((#proc)+3); ఒకవేళ (!proc) { failed_extension = (#proc)+3; } }

స్థిర bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    ఒకవేళ (!ov_glGetError) {
        స్థిరరాశి అక్షరం * failed_extension = 0;
        OPENVR_అమరిక_Proc(ov_glGenFramebuffers);
        OPENVR_అమరిక_Proc(ov_glGenRenderbuffers);
        OPENVR_అమరిక_Proc(ov_glBindFramebuffer);
        OPENVR_అమరిక_Proc(ov_glBindRenderbuffer);
        OPENVR_అమరిక_Proc(ov_glRenderbufferStorage);
        OPENVR_అమరిక_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_అమరిక_Proc(ov_glFramebufferTexture2D);
        OPENVR_అమరిక_Proc(ov_gl_Check_Named_Framebuffer_స్థితి);
        OPENVR_అమరిక_Proc(ov_glGetError);
        OPENVR_అమరిక_Proc(ov_glFlush);
        OPENVR_అమరిక_Proc(ov_gl_ముగింపు);
        OPENVR_అమరిక_Proc(ov_glGenTextures);
        OPENVR_అమరిక_Proc(ov_glDeleteTextures);
        OPENVR_అమరిక_Proc(ov_glTexParameterf);
        OPENVR_అమరిక_Proc(ov_glTexParameteri);
        OPENVR_అమరిక_Proc(ov_glTexImage2D);
        OPENVR_అమరిక_Proc(ov_glBindTexture);
        OPENVR_అమరిక_Proc(ov_glDrawBuffers);
        OPENVR_అమరిక_Proc(ov_glClear);
        OPENVR_అమరిక_Proc(ov_glClearColor);
        OPENVR_అమరిక_Proc(ov_gl_Color_ముసుగు);
        OPENVR_అమరిక_Proc(ov_glGetStringi);
        OPENVR_అమరిక_Proc(ov_glGetIntegerv);
        OPENVR_అమరిక_Proc(ov_gl_Debug_సందేశం_చొప్పించు);
        ఒకవేళ (failed_extension) {
            తిరిగి SDL_సమితి_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    తిరిగి true;
}

స్థిర bool OPENVR_సమితి_Overlay_Error(EVROverlayError e)
{
    ఎంపిక (e) {
#నిర్వచించు CASE(X) స్థితి EVROverlayError_VROverlayError_##X: తిరిగి SDL_సమితి_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_హద్దు_Exceeded);
    CASE(WrongVisibilityType);
    CASE(కీలకం_Too_Long);
    CASE(NameTooLong);
    CASE(కీలకం_లోపల_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_గమ్యం_ఎక్కించు_File);
    CASE(Keyboard_Already_లోపల_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_ముసుగు_Primitives);
    CASE(Bad_ముసుగు_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_తాళం_సామర్థ్యం_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_బహిర్గతం);
#నిర్వచనం_రద్దు CASE
    అప్రమేయ:
        తిరిగి SDL_సమితి_Error("Unknown VROverlayError %d", e);
    }
}

స్థిర bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

స్థిర bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    స్థిరరాశి అక్షరం * hint_వెడల్పు = SDL_GetHint("SDL_DEFAULT_WIDTH");
    స్థిరరాశి అక్షరం * hint_ఎత్తు = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    స్థిరరాశి అక్షరం * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    పూర్ణాంకం వెడల్పు = hint_వెడల్పు ? SDL_atoi(hint_వెడల్పు) : 0;
    పూర్ణాంకం ఎత్తు = hint_ఎత్తు ? SDL_atoi(hint_ఎత్తు) : 0;
    పూర్ణాంకం fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_బహుళకం.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_బహుళకం.w = OPENVR_DEFAULT_వెడల్పు;
    display.desktop_బహుళకం.h = OPENVR_DEFAULT_ఎత్తు;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    ఒకవేళ (ఎత్తు > 0 && వెడల్పు > 0) {
        display.desktop_బహుళకం.w = వెడల్పు;
        display.desktop_బహుళకం.h = ఎత్తు;
    }
    ఒకవేళ (fps) {
        display.desktop_బహుళకం.refresh_రేటు = fps;
    } లేకపోతే {
        display.desktop_బహుళకం.refresh_రేటు = దత్తాంశం->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_సూచీ_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (అక్షరం *)"OpenVRDisplay";
    SDL_కూడు_Video_Display(&display, false);

    తిరిగి true;
}

స్థిర శూన్య OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

స్థిర శూన్య OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;

#నిర్వచితమైతే SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం) {
        ఒకవేళ (దత్తాంశం->openVRLIB) {
            SDL_UnloadObject(దత్తాంశం->openVRLIB);
        }
    }
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    పూర్ణాంకం w = surf->w;
    పూర్ణాంకం h = surf->h;
    పూర్ణాంకం pitch = surf->pitch;
    పూర్ణాంకం x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    కొరకు(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        కొరకు(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    తిరిగి pxd;
}

స్థిర bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    ఒకవేళ (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_వెడల్పు;
        videodata->targh = OPENVR_DEFAULT_ఎత్తు;
    }

    ఒకవేళ (videodata->targh != videodata->చివరి_targh
     || videodata->targw != videodata->చివరి_targw) {

        నిర్మాణం HmdVector2_t ms;
        పూర్ణాంకం స్థితి_2;

        ఒకవేళ (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_లోతు_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_లోతు_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_సమీప);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_సమీప);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        స్థితి_2 = ov_gl_Check_Named_Framebuffer_స్థితి(videodata->fbo, GL_FRAMEBUFFER);
        ఒకవేళ (స్థితి_2 != GL_FRAMEBUFFER_COMPLETE) {
            తిరిగి SDL_సమితి_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (దశాంశం)videodata->targw;
        ms.v[1] = (దశాంశం)videodata->targh;
        videodata->oOverlay->సమితి_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->చివరి_targh = videodata->targh;
        videodata->చివరి_targw = videodata->targw;
    }
    తిరిగి true;
}

స్థిర bool OPENVR_VirtualControllerRumble(శూన్య *userdata, Uint16 దిగువ_frequency_rumble, Uint16 ఎగువ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)userdata;

    స్థిరరాశి దశాంశం k_flIntensity = 320.f; // Maximum frequency
    దశాంశం fl_ఎడమ_Frequency = (దశాంశం)దిగువ_frequency_rumble * k_flIntensity / 65535.f;
    దశాంశం fl_కుడి_Frequency = (దశాంశం)ఎగువ_frequency_rumble * k_flIntensity / 65535.f;
    దశాంశం flDurationSeconds = 2.f;
    దశాంశం flAmplitude = 1.f;

    videodata->o_ఆదానం->TriggerHapticVibrationAction(videodata->ఆదానం_action_handles_haptics[0], 0, flDurationSeconds, fl_ఎడమ_Frequency, flAmplitude, 0);
    videodata->o_ఆదానం->TriggerHapticVibrationAction(videodata->ఆదానం_action_handles_haptics[1], 0, flDurationSeconds, fl_కుడి_Frequency, flAmplitude, 0);

    తిరిగి true;
}

స్థిర bool OPENVR_VirtualControllerRumbleTriggers(శూన్య *userdata, Uint16 ఎడమ_rumble, Uint16 కుడి_rumble)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)userdata;
    videodata->o_ఆదానం->TriggerHapticVibrationAction(videodata->ఆదానం_action_handles_haptics[0], 0, 0.1f, ఎడమ_rumble, 1.0, 0);
    videodata->o_ఆదానం->TriggerHapticVibrationAction(videodata->ఆదానం_action_handles_haptics[1], 0, 0.1f, కుడి_rumble, 1.0, 0);
    తిరిగి true;
}

స్థిర శూన్య OPENVR_VirtualControllerUpdate(శూన్య *userdata)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ఆదానం_Digital_Action_దత్తాంశం_t digital_ఆదానం_action;
    ఆదానం_Analog_Action_దత్తాంశం_t analog_ఆదానం_action;
    EVRInputError e;
#నిర్వచితమైతే DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#అయితే_ముగింపు
    VRActive_Action_సమితి_t action_సమితి = { 0 };
    action_సమితి.ul_Action_సమితి = videodata->ఆదానం_action_సమితి;
    e = videodata->o_ఆదానం->UpdateActionState(&action_సమితి, పరిమాణం(action_సమితి), 1);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#అయితే_ముగింపు
        తిరిగి;
    }

    కొరకు (పూర్ణాంకం d = 0; d < videodata->ఆదానం_action_handles_buttons_లెక్క; d++)
    {
        ఒకవేళ (videodata->ఆదానం_action_handles_buttons[d] == k_ulInvalidActionHandle)
            కొనసాగు;
        e = videodata->o_ఆదానం->Get_Digital_Action_దత్తాంశం(videodata->ఆదానం_action_handles_buttons[d], &digital_ఆదానం_action, పరిమాణం(digital_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
        ఒకవేళ (e)
        {
#నిర్వచితమైతే DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#అయితే_ముగింపు
            తిరిగి;
        }
        SDL_సమితి_Joystick_Virtual_Button(joystick, d, digital_ఆదానం_action.bState);
#నిర్వచితమైతే DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#అయితే_ముగింపు
    }

    // Left Stick
    e = videodata->o_ఆదానం->Get_Analog_Action_దత్తాంశం(videodata->ఆదానం_action_handles_axes[0], &analog_ఆదానం_action, పరిమాణం(analog_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#అయితే_ముగింపు
        తిరిగి;
    }
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ఆదానం_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ఆదానం_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ఆదానం->Get_Analog_Action_దత్తాంశం(videodata->ఆదానం_action_handles_axes[1], &analog_ఆదానం_action, పరిమాణం(analog_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#అయితే_ముగింపు
        తిరిగి;
    }
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ఆదానం_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ఆదానం_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ఆదానం->Get_Analog_Action_దత్తాంశం(videodata->ఆదానం_action_handles_axes[2], &analog_ఆదానం_action, పరిమాణం(analog_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#అయితే_ముగింపు
        తిరిగి;
    }
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ఎడమ_TRIGGER, (Sint16)((analog_ఆదానం_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ఆదానం->Get_Analog_Action_దత్తాంశం(videodata->ఆదానం_action_handles_axes[3], &analog_ఆదానం_action, పరిమాణం(analog_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#అయితే_ముగింపు
        తిరిగి;
    }
    SDL_సమితి_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_కుడి_TRIGGER, (Sint16)((analog_ఆదానం_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#ఒకవేళ 0
    కొరకు (a = 0; a < videodata->ఆదానం_action_handles_axes_లెక్క; a++)
    {
        దశాంశం xval = 0.0f;
        e = videodata->o_ఆదానం->Get_Analog_Action_దత్తాంశం(videodata->ఆదానం_action_handles_axes[a], &analog_ఆదానం_action, పరిమాణం(analog_ఆదానం_action), k_ul_Invalid_ఆదానం_విలువ_Handle);
        ఒకవేళ (e) వెళ్ళు updatefail;
        xval = analog_ఆదానం_action.x;
        ఒకవేళ (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        ఒకవేళ (a == SDL_GAMEPAD_AXIS_ఎడమ_TRIGGER || a == SDL_GAMEPAD_AXIS_కుడి_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_సమితి_Joystick_Virtual_Axis(joystick, a, xval);
#నిర్వచితమైతే DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#అయితే_ముగింపు
    }
#అయితే_ముగింపు
#నిర్వచితమైతే DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#అయితే_ముగింపు
    తిరిగి;
}

స్థిర bool OPENVR_అమరిక_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_దత్తాంశం * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    అక్షరం * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_లెక్క] = {
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
    అక్షరం * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    ఒకవేళ ((e = videodata->o_ఆదానం->Get_Action_సమితి_Handle("/actions/virtualgamepad", &videodata->ఆదానం_action_సమితి)) != EVRInputError_VRInputError_None)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#అయితే_ముగింపు
        తిరిగి SDL_సమితి_Error("Failed to get action set handle");
    }

    videodata->ఆదానం_action_handles_buttons_లెక్క = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ఆదానం_action_handles_buttons = SDL_malloc(videodata->ఆదానం_action_handles_buttons_లెక్క * పరిమాణం(VRActionHandle_t));

    కొరకు (పూర్ణాంకం i = 0; i < videodata->ఆదానం_action_handles_buttons_లెక్క; i++)
    {
        e = videodata->o_ఆదానం->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ఆదానం_action_handles_buttons[i]);
        ఒకవేళ (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            తిరిగి SDL_సమితి_Error("ERROR: Failed to get button action");
        }
    }

    videodata->ఆదానం_action_handles_axes_లెక్క = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ఆదానం_action_handles_axes = SDL_malloc(videodata->ఆదానం_action_handles_axes_లెక్క * పరిమాణం(VRActionHandle_t));

    కొరకు (పూర్ణాంకం i = 0; i < videodata->ఆదానం_action_handles_axes_లెక్క; i++)
    {
        e = videodata->o_ఆదానం->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ఆదానం_action_handles_axes[i]);
        ఒకవేళ (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            తిరిగి SDL_సమితి_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ఆదానం->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ఆదానం_action_handles_haptics[0]);
    e |= videodata->o_ఆదానం->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ఆదానం_action_handles_haptics[1]);
    ఒకవేళ (e)
    {
#నిర్వచితమైతే DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#అయితే_ముగింపు
        తిరిగి SDL_సమితి_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_లెక్క;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_లెక్క;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    ఒకవేళ (!virtual_id) {
        తిరిగి SDL_సమితి_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    ఒకవేళ (!videodata->virtual_joystick) {
        తిరిగి SDL_సమితి_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#నిర్వచితమైతే DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ఆదానం_action_handles_buttons_లెక్క, videodata->ఆదానం_action_handles_axes_లెక్క);
#అయితే_ముగింపు

    తిరిగి true;
}

స్థిర bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    // Wait til here, to make sure we have our context setup correctly.
    ఒకవేళ (!OPENVR_InitExtensions(_this)) {
        తిరిగి false;
    }

    // Generate the overlay.
    {
        స్థిరరాశి అక్షరం * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        అక్షరం * cursorname = 0;
        ఒకవేళ (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        ఒకవేళ (!videodata->sOverlayName) {
            తిరిగి false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        ఒకవేళ (!cursorname) {
            తిరిగి false;
        }

        EVROverlayError ఫలితం = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            కిటికీ->title, &videodata->overlayID, &videodata->thumbID);
        ఒకవేళ (ఫలితం != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            తిరిగి SDL_సమితి_Error("Could not create dashboard overlay (%d)", ఫలితం );
        }
        ఫలితం = videodata->oOverlay->CreateOverlay(cursorname, కిటికీ->title, &videodata->cursorID);
        ఒకవేళ (ఫలితం != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            తిరిగి SDL_సమితి_Error("Could not create cursor overlay (%d)", ఫలితం );
        }
        SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
        SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_OPENVR_OVERLAY_ID_సంఖ్య, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        స్థిరరాశి అక్షరం *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        ఒకవేళ (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } లేకపోతే {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#ఒకవేళ 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#అయితే_ముగింపు
        }

        కొరకు (పూర్ణాంకం i = 0; i < పరిమాణం(overlay_flags) * 8; ++i) {
            ఒకవేళ (overlay_flags & (1 << i)) {
                videodata->oOverlay->సమితి_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        స్థిరరాశి అక్షరం * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        దశాంశం f_వెడల్పు = hint ? (దశాంశం)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->సమితి_Overlay_వెడల్పు_లోపల_Meters(videodata->overlayID, f_వెడల్పు);
    }
    {
        స్థిరరాశి అక్షరం * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        దశాంశం f_Cursor_వెడల్పు = hint ? (దశాంశం)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->సమితి_Overlay_వెడల్పు_లోపల_Meters(videodata->cursorID, f_Cursor_వెడల్పు * 0.5f);
    }
    {
        స్థిరరాశి అక్షరం * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        ఒకవేళ (hint) {
            అక్షరం * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->సమితి_Overlay_From_File(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            ఒకవేళ (err == EVROverlayError_VROverlayError_None) {
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
        videodata->oOverlay->సమితి_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    ఒకవేళ (!OPENVR_CheckRenderbuffer(_this)) {
        తిరిగి false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->సమితి_Overlay_Name(videodata->overlayID, కిటికీ->title);

    videodata->bDidCreateOverlay = true;
    videodata->కిటికీ = కిటికీ;

    తిరిగి true;
}


స్థిర bool OPENVR_అమరిక_చట్రం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    స్థిర స్థిరరాశి GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_బఫరు_rendering = true;

#నిర్వచితమైతే DEBUG_OPENVR
    {
        పూర్ణాంకం error = ov_glGetError();
        ఒకవేళ (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_స్థితి(videodata->fbo, GL_FRAMEBUFFER));
    }
#అయితే_ముగింపు

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_ముసుగు(false, false, false, true);
        ov_glClear(GL_COLOR_బఫరు_బిట్టు);
        ov_gl_Color_ముసుగు(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    తిరిగి true;
}

స్థిర bool OPENVR_Release_చట్రం(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    ఒకవేళ (!ov_glGetError) {
        తిరిగి true;
    }

    ఒకవేళ (!videodata->is_బఫరు_rendering) {
        తిరిగి true;
    }

#నిర్వచితమైతే DEBUG_OPENVR
    {
        పూర్ణాంకం error = ov_glGetError();
        ఒకవేళ (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_స్థితి(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#అయితే_ముగింపు

    videodata->is_బఫరు_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ఒకవేళ (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->చివరి_targh &&
        videodata->targw == videodata->చివరి_targw) {
        // Only submit frames to OpenVR if the texture exists.
        నిర్మాణం Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (శూన్య *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->సమితి_Overlay_Texture(videodata->overlayID, &tex);
    }

    ఒకవేళ (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    ఒకవేళ (videodata->renderdoc_debugmarker_చట్రం_చివర) {
        ov_gl_Debug_సందేశం_చొప్పించు(GL_DEBUG_ఆధారం_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    తిరిగి OPENVR_CheckRenderbuffer(_this);
}

స్థిర శూన్య OPENVR_HandleResize(SDL_VideoDevice *_this, పూర్ణాంకం w, పూర్ణాంకం h)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    దత్తాంశం->targw = w;
    దత్తాంశం->targh = h;
}

స్థిర bool OPENVR_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    తిరిగి true;
}


#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
స్థిర LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM lParam)
{
    ఎంపిక (సందేశం_2) {
    స్థితి WM_DESTROY:
        తిరిగి 0;
    }
    తిరిగి Def_కిటికీ_Proc(hwnd, సందేశం_2, wParam, lParam);
}

స్థిర bool OPENVR_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    ఒకవేళ (మార్గం == ఖాళీ) {
        మార్గం = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ఎక్కించు_Object(మార్గం);
    ఒకవేళ (!_this->gl_config.dll_handle) {
        తిరిగి false;
    }
    SDL_strlcpy(_this->gl_config.driver_మార్గం, మార్గం,
                 SDL_arraysize(_this->gl_config.driver_మార్గం));

    // Allocate OpenGL memory
    _this->gl_దత్తాంశం = (నిర్మాణం SDL_GLDriver_దత్తాంశం *)SDL_calloc(1, పరిమాణం(నిర్మాణం SDL_GLDriver_దత్తాంశం));
    ఒకవేళ (!_this->gl_దత్తాంశం) {
        తిరిగి false;
    }
    _this->gl_config.driver_loaded = true;

    తిరిగి true;
}

స్థిర SDL_Function_సూచిక OPENVR_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    SDL_Function_సూచిక ఫలితం = ఖాళీ;
    ఒకవేళ (ov_wgl_Get_Proc_చిరునామా) {
        ఫలితం = (SDL_Function_సూచిక)ov_wgl_Get_Proc_చిరునామా(proc);
        ఒకవేళ (ఫలితం) {
            తిరిగి ఫలితం;
        }
    }

    తిరిగి SDL_ఎక్కించు_Function(_this->gl_config.dll_handle, proc);
}

స్థిర శూన్య OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

స్థిర SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    GLint అంకె_Extensions;
    పూర్ణాంకం i;
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ఖాళీ);
        wnd.hIcon = ఎక్కించు_Icon(ఖాళీ, IDI_APPLICATION);
        wnd.hCursor = ఎక్కించు_Cursor(ఖాళీ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ఖాళీ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        రిజిస్టరు_Class_A(&wnd);
        hwnd = Create_కిటికీ_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ఖాళీ, ఖాళీ, GetModuleHandle(ఖాళీ), ఖాళీ);

        సందేశం_3 సందేశం_2;
        అయితే (Peek_సందేశం(&సందేశం_2, ఖాళీ, 0, 0, PM_REMOVE)) {
            Translate_సందేశం(&సందేశం_2);
            Dispatch_సందేశం(&సందేశం_2);
        }

        videodata->hdc = GetDC(hwnd);

        స్థిర  PIXELFORMATDESCRIPTOR pfd =
        {
            పరిమాణం(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_గమ్యం_కిటికీ |
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
        GLuint PixelFormat = ఎంచుకో_Pixel_Format(videodata->hdc, &pfd);
        ఒకవేళ (!సమితి_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_సమితి_Error( "Could not set pixel format" );
            తిరిగి ఖాళీ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        ఒకవేళ (!opengl) {
            SDL_సమితి_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            తిరిగి ఖాళీ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_చిరునామా(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_చిరునామా(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_చిరునామా = (PROC(*)(LPCSTR))Get_Proc_చిరునామా(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_చిరునామా(opengl, "wglDeleteContext");
        ఒకవేళ (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_సమితి_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            తిరిగి ఖాళీ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        ఒకవేళ (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_సమితి_Error("Could not make current OpenGL context.");
            తిరిగి ఖాళీ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    ఒకవేళ (i == 0) {
        తిరిగి ఖాళీ;
    }

    videodata->renderdoc_debugmarker_చట్రం_చివర = false;

    ov_glGetIntegerv(GL_అంకె_EXTENSIONS, &అంకె_Extensions);
    కొరకు (i = 0; i < అంకె_Extensions; i++) {
        స్థిరరాశి అక్షరం *ccc = (స్థిరరాశి అక్షరం *)ov_glGetStringi(GL_EXTENSIONS, i);
        ఒకవేళ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#నిర్వచితమైతే DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#అయితే_ముగింపు
            videodata->renderdoc_debugmarker_చట్రం_చివర = true;
        }
    }

    ఒకవేళ (!videodata->bDidCreateOverlay) {
        ఒకవేళ (!OPENVR_InitializeOverlay(_this, కిటికీ)) {
            తిరిగి ఖాళీ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_అమరిక_చట్రం(_this, కిటికీ);

    SDL_GLContext ఫలితం = SDL_malloc(పరిమాణం(నిర్మాణం SDL_GLContextState));
    ఒకవేళ (!ఫలితం) {
        తిరిగి ఖాళీ;
    }
    ఫలితం->hglrc = videodata->hglrc;
    తిరిగి ఫలితం;
}

స్థిర bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *wnd, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    తిరిగి true;
}

స్థిర bool OPENVR_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    videodata->మార్పిడి_interval = interval;
    తిరిగి true;
}

స్థిర bool OPENVR_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *మార్పిడి_Interval)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (మార్పిడి_Interval)
        *మార్పిడి_Interval = videodata->మార్పిడి_interval;
    లేకపోతే
        తిరిగి SDL_సమితి_Error("OPENVR: null passed in for GetSwapInterval");
    తిరిగి true;
}

స్థిర bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ov_wglMakeCurrent(videodata->hdc, ఖాళీ);
    ov_wglDeleteContext(videodata->hglrc);
    తిరిగి true;
}


#లేకపోతే

స్థిర EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_సంస్కరణ, 2,
    EGL_NONE
};

స్థిర bool SDL_EGL_Init_అంతర్గత(SDL_Video_దత్తాంశం * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ఖాళీ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#నిర్వచితమైతే DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#అయితే_ముగింపు

    ఒకవేళ (vd->eglDpy == 0) {
        తిరిగి SDL_సమితి_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    ఒకవేళ (!b) {
        తిరిగి SDL_సమితి_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#నిర్వచితమైతే DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#అయితే_ముగింపు

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#నిర్వచితమైతే DEBUG_OPENVR
    {
        పూర్ణాంకం err = eglGetError();
        ఒకవేళ (err != EGL_SUCCESS) {
            తిరిగి SDL_సమితి_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (!vd->eglCtx) {
        తిరిగి SDL_సమితి_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    తిరిగి true;
}

// Linux, EGL, etc.
స్థిర bool OVR_EGL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం)
{
    తిరిగి SDL_EGL_ఎక్కించు_Library(_this, మార్గం, EGL_DEFAULT_DISPLAY);
}

స్థిర SDL_Function_సూచిక OVR_EGL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc)
{
    తిరిగి SDL_EGL_Get_Proc_చిరునామా(proc);
}
స్థిర శూన్య OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
స్థిర SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    GLint అంకె_Extensions;
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (!videodata->eglCtx) {
        ఒకవేళ (!SDL_EGL_Init_అంతర్గత(videodata)) {
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ (!OPENVR_InitExtensions(_this)) {
        తిరిగి ఖాళీ;
    }

    videodata->renderdoc_debugmarker_చట్రం_చివర = false;

    ov_glGetIntegerv(GL_అంకె_EXTENSIONS, &అంకె_Extensions);
    కొరకు(పూర్ణాంకం i = 0; i < అంకె_Extensions; i++) {
        స్థిరరాశి అక్షరం * ccc = (స్థిరరాశి అక్షరం *)ov_glGetStringi(GL_EXTENSIONS, i);
        ఒకవేళ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#నిర్వచితమైతే DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#అయితే_ముగింపు
           videodata->renderdoc_debugmarker_చట్రం_చివర = true;
        }
    }

    ఒకవేళ (!videodata->bDidCreateOverlay) {
        ఒకవేళ (!OPENVR_InitializeOverlay(_this, కిటికీ)) {
            తిరిగి ఖాళీ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_అమరిక_చట్రం(_this, కిటికీ);

    తిరిగి videodata->eglCtx;
}

స్థిర bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ * wnd, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    తిరిగి true;
}

స్థిర bool OVR_EGL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    videodata->మార్పిడి_interval = interval;
    తిరిగి true;
}

స్థిర bool OVR_EGL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం * మార్పిడి_Interval)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (మార్పిడి_Interval)
        *మార్పిడి_Interval = videodata->మార్పిడి_interval;
    లేకపోతే
        తిరిగి SDL_సమితి_Error("OPENVR: null passed in for GetSwapInterval");
    తిరిగి true;
}

స్థిర bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    తిరిగి true;
}

#అయితే_ముగింపు

స్థిర bool OPENVR_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    // Allocate window internal data
    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (దత్తాంశం == ఖాళీ) {
        తిరిగి SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
    }

    కిటికీ->max_w = 4096;
    కిటికీ->max_h = 4096;
    కిటికీ->min_w = 1;
    కిటికీ->min_h = 1;

    // Setup driver data for this window
    కిటికీ->అంతర్గత = దత్తాంశం;
    తిరిగి true;
}


స్థిర శూన్య OPENVR_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_free(దత్తాంశం);
    కిటికీ->అంతర్గత = ఖాళీ;
}

స్థిర శూన్య OPENVR_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం * దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (దత్తాంశం->bDidCreateOverlay) {
        దత్తాంశం->oOverlay->సమితి_Overlay_Name(దత్తాంశం->overlayID, కిటికీ->title);
    }
}

స్థిర శూన్య OPENVR_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    ఒకవేళ (కిటికీ->pending.w != కిటికీ->w) {
        కిటికీ->w = కిటికీ->pending.w;
    }

    ఒకవేళ (కిటికీ->pending.h != కిటికీ->h) {
        కిటికీ->h = కిటికీ->pending.h;
    }

    ఒకవేళ (దత్తాంశం->targh != కిటికీ->h || దత్తాంశం->targw != కిటికీ->w) {
        OPENVR_HandleResize(_this, కిటికీ->w, కిటికీ->h);
    }

    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->w, కిటికీ->h);
}

స్థిర శూన్య OPENVR_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    *w = దత్తాంశం->targw;
    *h = దత్తాంశం->targh;
}

స్థిర శూన్య OPENVR_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (దత్తాంశం->targh != కిటికీ->h || దత్తాంశం->targw != కిటికీ->w) {
        OPENVR_HandleResize(_this, కిటికీ->w, కిటికీ->h);
    }

    దత్తాంశం->oOverlay->ShowDashboard(దత్తాంశం->sOverlayName);

    కిటికీ->flags |= (SDL_కిటికీ_ఆదానం_FOCUS | SDL_కిటికీ_MOUSE_FOCUS);
    SDL_సమితి_Keyboard_Focus(కిటికీ);
}

స్థిర శూన్య OPENVR_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి;
}

స్థిర bool OPENVR_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    ఒకవేళ (!videodata->bDidCreateOverlay) {
        ఒకవేళ (!OPENVR_InitializeOverlay(_this, కిటికీ)) {
            తిరిగి false;
        }
    }

    ఒకవేళ (!OPENVR_Release_చట్రం(_this)) {
        తిరిగి false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    ఒకవేళ (videodata->మార్పిడి_interval != 0) {
        videodata->oOverlay->Wait_చట్రం_Sync(100);
    }

    ఒకవేళ (!OPENVR_అమరిక_చట్రం(_this, కిటికీ)) {
        తిరిగి false;
    }

    తిరిగి true;
}

స్థిర Uint8 OPENVR_MapMouseButton(పూర్ణాంకం btn)
{
    ఒకవేళ (btn == EVRMouse_Button_VRMouse_Button_కుడి) {
        తిరిగి SDL_BUTTON_కుడి;
    } లేకపోతే ఒకవేళ (btn == EVRMouse_Button_VRMouse_Button_మధ్య) {
        తిరిగి SDL_BUTTON_మధ్య;
    } లేకపోతే {
        తిరిగి SDL_BUTTON_ఎడమ;
    }
}

స్థిర శూన్య OPENVR_HandleMouse(దశాంశం x, దశాంశం y, పూర్ణాంకం btn, పూర్ణాంకం evt)
{
    ఒకవేళ (evt == 2) {
        SDL_SendMouseMotion(0, ఖాళీ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } లేకపోతే {
        స్థిరరాశి Uint8 button = OPENVR_MapMouseButton(btn);
        స్థిరరాశి bool కిందికి = (evt != 0);
        SDL_SendMouseButton(0, ఖాళీ, SDL_GLOBAL_MOUSE_ID, button, కిందికి);
    }
}


స్థిర bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    తిరిగి true;
}

స్థిర శూన్య OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        తిరిగి;
    }
    EGamepad_పాఠ్యం_ఆదానం_బహుళకం ఆదానం_బహుళకం;
    ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_HIDDEN:
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
        ఆదానం_బహుళకం = EGamepad_పాఠ్యం_ఆదానం_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_బహుళకం_Password;
        ఆపు;
    అప్రమేయ:
        ఆదానం_బహుళకం = EGamepad_పాఠ్యం_ఆదానం_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_బహుళకం_సాధారణ;
        ఆపు;
    }
    EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం పంక్తి_బహుళకం;
    ఒకవేళ (SDL_Get_పాఠ్యం_ఆదానం_Multiline(props)) {
        పంక్తి_బహుళకం = EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_గుణిజం_పంక్తులు;
    } లేకపోతే {
        పంక్తి_బహుళకం = EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_k_EGamepad_పాఠ్యం_ఆదానం_పంక్తి_బహుళకం_Single_పంక్తి;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ఆదానం_బహుళకం, పంక్తి_బహుళకం,
           EKeyboard_Flags_Keyboard_Flag_కనీస, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

స్థిర శూన్య OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

స్థిర SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor *ఫలితం = SDL_calloc(1, పరిమాణం(SDL_Cursor));
    ఒకవేళ (!ఫలితం) {
        తిరిగి ఖాళీ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_దత్తాంశం *ovrc = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*ovrc));
    ఒకవేళ (!ovrc) {
        SDL_free(ఫలితం);
        తిరిగి ఖాళీ;
    }
    ఫలితం->అంతర్గత = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    తిరిగి ఫలితం;
}

స్థిర bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_దత్తాంశం * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    ఒకవేళ (!cursor) {
        global_openvr_driver->oOverlay->సమితి_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->సమితి_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
            తిరిగి OPENVR_సమితి_Overlay_Error(e);
        }
        తిరిగి true;
    }

    global_openvr_driver->oOverlay->సమితి_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->అంతర్గత;

    ఒకవేళ (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        తిరిగి true;
    }

    hotspot.v[0] = (దశాంశం)ovrc->hot_x / (దశాంశం)ovrc->w;
    hotspot.v[1] = (దశాంశం)ovrc->hot_y / (దశాంశం)ovrc->h;

    texture.handle = (శూన్య *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->సమితి_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
        తిరిగి OPENVR_సమితి_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->సమితి_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
        తిరిగి OPENVR_సమితి_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->సమితి_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
        తిరిగి OPENVR_సమితి_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->సమితి_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
        తిరిగి OPENVR_సమితి_Overlay_Error(e);
    }

    తిరిగి true;
}

స్థిర శూన్య OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *ovrc = cursor->అంతర్గత;
        ఒకవేళ (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


స్థిర bool OPENVR_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_Surface * icon)
{
    ఒకవేళ (!global_openvr_driver) {
        తిరిగి SDL_సమితి_Error("OpenVR Overlay not initialized");
    }

    గుర్తులేని texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    ఒకవేళ (videodata->bIconOverridden) {
        తిరిగి SDL_సమితి_Error("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (శూన్య *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->సమితి_Overlay_Texture(videodata->thumbID, &texture);
    ఒకవేళ (e != EVROverlayError_VROverlayError_None) {
        తిరిగి OPENVR_సమితి_Overlay_Error(e);
    }
    తిరిగి true;
}

స్థిర bool OPENVR_Show_సందేశం_Box(SDL_VideoDevice *_this,స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonid)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    అక్షరం ఖాళీలు = 0;
    అక్షరం * సందేశం = SDL_strdup(messageboxdata->సందేశం?messageboxdata->సందేశం:"");
    అక్షరం * title = SDL_strdup(messageboxdata->సందేశం?messageboxdata->సందేశం:"");
    అక్షరం * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_సందేశం_Overlay(సందేశం, title, ok, &ఖాళీలు, &ఖాళీలు, &ఖాళీలు);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(సందేశం);
    తిరిగి true;
}

స్థిర శూన్య InitializeMouseFunctions(శూన్య)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

స్థిర శూన్య OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;
    నిర్మాణం VREvent_t nEvent;
    ఒకవేళ (videodata->overlayID) {
        అయితే (videodata->oOverlay->Poll_తదుపరి_Overlay_Event(videodata->overlayID, &nEvent, పరిమాణం(nEvent))) {
            ఎంపిక (nEvent.eventType) {
            స్థితి EVREventType_VREvent_ButtonPress:
            స్థితి EVREventType_VREvent_ButtonUnpress:
                ఆపు;
            స్థితి EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.దత్తాంశం.mouse.x, videodata->targh - nEvent.దత్తాంశం.mouse.y, nEvent.దత్తాంశం.mouse.button, 2);
                ఆపు;
            స్థితి EVREvent_Type_VREvent_Mouse_Button_కిందికి:
                OPENVR_HandleMouse(nEvent.దత్తాంశం.mouse.x, videodata->targh - nEvent.దత్తాంశం.mouse.y, nEvent.దత్తాంశం.mouse.button, 1);
                ఆపు;
            స్థితి EVREvent_Type_VREvent_Mouse_Button_పైకి:
                OPENVR_HandleMouse(nEvent.దత్తాంశం.mouse.x, videodata->targh - nEvent.దత్తాంశం.mouse.y, nEvent.దత్తాంశం.mouse.button, 0);
                ఆపు;
            స్థితి EVREventType_VREvent_ScrollSmooth:
            స్థితి EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ఖాళీ, SDL_GLOBAL_MOUSE_ID, -nEvent.దత్తాంశం.scroll.xdelta, nEvent.దత్తాంశం.scroll.ydelta, SDL_MOUSEWHEEL_సాధారణ);
                ఆపు;
            స్థితి EVREvent_Type_VREvent_Keyboard_Char_ఆదానం:
                SDL_Send_Keyboard_Unicode_కీలకం(SDL_GetTicksNS(), nEvent.దత్తాంశం.keyboard.c_New_ఆదానం[0]);
                ఆపు;
            స్థితి EVREventType_VREvent_OverlayShown:
                SDL_సమితి_Keyboard_Focus(videodata->కిటికీ);
                SDL_Send_కిటికీ_Event(videodata->కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
                SDL_Send_కిటికీ_Event(videodata->కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
                ఆపు;
            స్థితి EVREventType_VREvent_OverlayHidden:
                SDL_Send_కిటికీ_Event(videodata->కిటికీ, SDL_EVENT_కిటికీ_HIDDEN, 0, 0);
                SDL_Send_కిటికీ_Event(videodata->కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
                SDL_సమితి_Keyboard_Focus(ఖాళీ);
                ఆపు;
            స్థితి EVREventType_VREvent_OverlayClosed:
            స్థితి EVREventType_VREvent_Quit:
                SDL_SendQuit();
                ఆపు;
            }
        }
    }
}


స్థిర SDL_VideoDevice *OPENVR_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;
    స్థిరరాశి అక్షరం *hint;

#నిర్వచితమైతే SDL_PLATFORM_WINDOWS
    SDL_రిజిస్టరు_App(ఖాళీ, 0, ఖాళీ);
#అయితే_ముగింపు

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (device) {
        దత్తాంశం = (నిర్మాణం SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    } లేకపోతే {
        దత్తాంశం = ఖాళీ;
    }
    ఒకవేళ (!దత్తాంశం) {
#నిర్వచితమైతే SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#అయితే_ముగింపు
        SDL_free(device);
        తిరిగి ఖాళీ;
    }
    device->అంతర్గత = దత్తాంశం;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    ఒకవేళ (hint) {
        దత్తాంశం->openVRLIB = SDL_ఎక్కించు_Object(hint);
    }
    ఒకవేళ (!దత్తాంశం->openVRLIB) {
        దత్తాంశం->openVRLIB = SDL_ఎక్కించు_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    ఒకవేళ (!దత్తాంశం->openVRLIB) {
        SDL_సమితి_Error("Could not open OpenVR API Library");
        వెళ్ళు error;
    }

    దత్తాంశం->FN_VR_Init_అంతర్గత = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_ఎక్కించు_Function(దత్తాంశం->openVRLIB, "VR_InitInternal");
    దత్తాంశం->FN_VR_GetVRInitErrorAsEnglishDescription = (స్థిరరాశి అక్షరం *(*)(EVRInitError error))SDL_ఎక్కించు_Function(దత్తాంశం->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    దత్తాంశం->FN_VR_GetGenericInterface = (intptr_t (*)(స్థిరరాశి అక్షరం *pch_Interface_సంస్కరణ, EVRInitError * peError))SDL_ఎక్కించు_Function(దత్తాంశం->openVRLIB, "VR_GetGenericInterface");
    ఒకవేళ (!దత్తాంశం->FN_VR_Init_అంతర్గత || !దత్తాంశం->FN_VR_GetVRInitErrorAsEnglishDescription || !దత్తాంశం->FN_VR_GetGenericInterface) {
        వెళ్ళు error;
    }

    అక్షరం fnname[128];
    EVRInitError e;
    దత్తాంశం->vrtoken = దత్తాంశం->FN_VR_Init_అంతర్గత(&e, EVRApplicationType_VRApplication_Overlay);
    ఒకవేళ (!దత్తాంశం->vrtoken) {
        స్థిరరాశి అక్షరం *err = "Can't get english description";
        ఒకవేళ (దత్తాంశం->FN_VR_GetVRInitErrorAsEnglishDescription != ఖాళీ)
            err = దత్తాంశం->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_సమితి_Error("Could not generate OpenVR Context (%s)", err);
        వెళ్ళు error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_సంస్కరణ);
    దత్తాంశం->oSystem = (నిర్మాణం VR_IVRSystem_Fn_పట్టిక *)దత్తాంశం->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_సంస్కరణ);
    దత్తాంశం->oOverlay = (నిర్మాణం VR_IVROverlay_Fn_పట్టిక *)దత్తాంశం->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_సంస్కరణ);
    దత్తాంశం->o_ఆదానం = (నిర్మాణం VR_IVRInput_Fn_పట్టిక *)దత్తాంశం->FN_VR_GetGenericInterface(fnname, &e);

    ఒకవేళ (!దత్తాంశం->oOverlay || !దత్తాంశం->oSystem || !దత్తాంశం->o_ఆదానం) {
        SDL_సమితి_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_సంస్కరణ, IVROverlay_సంస్కరణ, IVRInput_సంస్కరణ);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    అక్షరం *loadpath = 0;
    EVRInputError err;

    ఒకవేళ (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } లేకపోతే {
        స్థిరరాశి అక్షరం *basepath = SDL_Get_పునాది_మార్గం();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    ఒకవేళ (!loadpath) {
        వెళ్ళు error;
    }

    err = దత్తాంశం->o_ఆదానం->సమితి_Action_Manifest_మార్గం(loadpath);
#నిర్వచితమైతే DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#అయితే_ముగింపు
    SDL_free(loadpath);
    ఒకవేళ (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        ఒకవేళ (hint) {
            వెళ్ళు error;
        }
    } లేకపోతే {
        ఒకవేళ(!OPENVR_అమరిక_Joystick_Based_On_Loaded_Action_Manifest(దత్తాంశం)) {
            వెళ్ళు error;
        }
    }

    // Setup amount of available displays
    device->అంకె_displays = 0;

    // Set device free function
    device->విడుదల = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->సమితి_Display_బహుళకం = OPENVR_సమితి_Display_బహుళకం;
    device->CreateSDLWindow = OPENVR_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = OPENVR_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_కొలత = OPENVR_సమితి_కిటికీ_కొలత;
    device->Get_కిటికీ_కొలత_లోపల_Pixels = OPENVR_Get_కిటికీ_కొలత_లోపల_Pixels;
    device->Show_కిటికీ = OPENVR_Show_కిటికీ;
    device->Hide_కిటికీ = OPENVR_Hide_కిటికీ;
    device->Destroy_కిటికీ = OPENVR_Destroy_కిటికీ;
    device->Show_సందేశం_Box = OPENVR_Show_సందేశం_Box;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
#నిర్వచితమైతే SDL_VIDEO_OPENGL_WGL
    device->GL_ఎక్కించు_Library = OPENVR_GL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = OPENVR_GL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = OPENVR_GL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = OPENVR_GL_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = OPENVR_GL_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#లేకపోతే
#దోషం Needs మరిన్ని work గమ్యం support EGL
#అయితే_ముగింపు
#లేకపోతే
    device->GL_ఎక్కించు_Library = OVR_EGL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = OVR_EGL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = OVR_EGL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = OVR_EGL_Get_మార్పిడి_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_మార్పిడి_కిటికీ = OPENVR_GL_మార్పిడి_కిటికీ;
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_ఎక్కించు_Library = WIN_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#లేకపోతే
    device->Vulkan_ఎక్కించు_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#అయితే_ముగింపు

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->సమితి_కిటికీ_Icon = OPENVR_సమితి_కిటికీ_Icon;

    తిరిగి device;

error:
    OPENVR_Destroy(device);
    తిరిగి ఖాళీ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ఖాళీ, false
};

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENVR

