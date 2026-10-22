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

#که_تعریف_شوی SDL_VIDEO_DRIVER_OPENVR

#إذا 0
#تعریف_کړه DEBUG_OPENVR
#د_که_پای

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openvrvideo.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ضمن <SDL3/SDL_opengl.h>
#وإلا
// Currently only EGL, not OpenGL, is supported on other platforms
#ضمن <SDL3/SDL_opengles2.h>
#ضمن <SDL3/SDL_opengles2_gl2.h>
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
#ضمن "../windows/SDL_windowsopengl.h"
#ضمن "../windows/SDL_windowsvulkan.h"

#تعریف_کړه DEFAULT_OPENGL "OPENGL32.DLL"

ساكن bool OPENVR_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار);
ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

بنية SDL_GLContextState
{
    HGLRC hglrc;
};
#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS



#که_تعریف_شوی SDL_PLATFORM_WINDOWS
#تعریف_کړه SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وإلا
#تعریف_کړه SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#د_که_پای

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#تعریف_کړه MARKER_ID 0
#تعریف_کړه MARKER_STR "vr-marker,frame_end,type,application"

#تعریف_لغوه EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_معلومات * global_openvr_driver;

ساكن فراغ InitializeMouseFunctions(فراغ);

بنية SDL_Cursor_معلومات
{
    بینښه texture_id_handle;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

// GL Extensions for functions we will be using.
ساكن فراغ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساكن فراغ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساكن فراغ (APIENTRY *ov_glBindFramebuffer)(GLenum موخه, GLuint framebuffer);
ساكن فراغ (APIENTRY *ov_glBindRenderbuffer)(GLenum موخه, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glRenderbufferStorage)(GLenum موخه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
ساكن فراغ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum موخه, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glFramebufferTexture2D)(GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساكن GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_حالت)(GLuint framebuffer, GLenum موخه);
ساكن GLenum (APIENTRY *ov_glGetError)(فراغ);
ساكن فراغ (APIENTRY *ov_glFlush)(فراغ);
ساكن فراغ (APIENTRY *ov_gl_پای)(فراغ);
ساكن فراغ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glTexParameterf)(GLenum موخه, GLenum pname, GLfloat param);
ساكن فراغ (APIENTRY *ov_glTexParameteri)(GLenum موخه, GLenum pname, GLenum param);
ساكن فراغ (APIENTRY *ov_glTexImage2D)(GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLenum format, GLenum type, ثابت فراغ *معلومات);
ساكن فراغ (APIENTRY *ov_glBindTexture)(GLenum موخه, GLuint texture);
ساكن فراغ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساكن فراغ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * معلومات);
ساكن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint شاخص);
ساكن فراغ (APIENTRY *ov_glClear)(GLbitfield ماسک);
ساكن فراغ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساكن فراغ (APIENTRY *ov_gl_Color_ماسک)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساكن فراغ (APIENTRY *ov_gl_Debug_پیغام_ورننباسه)(GLenum سرچینه, GLenum type, GLuint id, GLenum severity, GLsizei اوږدتیا, ثابت حرف *پیغام);

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
ساكن PROC (*ov_wgl_Get_Proc_پته)(LPCSTR);
ساكن HGLRC (*ov_wglCreateContext)(HDC);
ساكن BOOL (*ov_wglDeleteContext)(HGLRC);
ساكن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#د_که_پای


#تعریف_کړه OPENVR_DEFAULT_پلنوالی 1920
#تعریف_کړه OPENVR_DEFAULT_لوړوالی 1080

#تعریف_کړه OPENVR_تیاری_Proc(proc) { proc = (فراغ *)SDL_GL_Get_Proc_پته((#proc)+3); إذا (!proc) { failed_extension = (#proc)+3; } }

ساكن bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    إذا (!ov_glGetError) {
        ثابت حرف * failed_extension = 0;
        OPENVR_تیاری_Proc(ov_glGenFramebuffers);
        OPENVR_تیاری_Proc(ov_glGenRenderbuffers);
        OPENVR_تیاری_Proc(ov_glBindFramebuffer);
        OPENVR_تیاری_Proc(ov_glBindRenderbuffer);
        OPENVR_تیاری_Proc(ov_glRenderbufferStorage);
        OPENVR_تیاری_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_تیاری_Proc(ov_glFramebufferTexture2D);
        OPENVR_تیاری_Proc(ov_gl_Check_Named_Framebuffer_حالت);
        OPENVR_تیاری_Proc(ov_glGetError);
        OPENVR_تیاری_Proc(ov_glFlush);
        OPENVR_تیاری_Proc(ov_gl_پای);
        OPENVR_تیاری_Proc(ov_glGenTextures);
        OPENVR_تیاری_Proc(ov_glDeleteTextures);
        OPENVR_تیاری_Proc(ov_glTexParameterf);
        OPENVR_تیاری_Proc(ov_glTexParameteri);
        OPENVR_تیاری_Proc(ov_glTexImage2D);
        OPENVR_تیاری_Proc(ov_glBindTexture);
        OPENVR_تیاری_Proc(ov_glDrawBuffers);
        OPENVR_تیاری_Proc(ov_glClear);
        OPENVR_تیاری_Proc(ov_glClearColor);
        OPENVR_تیاری_Proc(ov_gl_Color_ماسک);
        OPENVR_تیاری_Proc(ov_glGetStringi);
        OPENVR_تیاری_Proc(ov_glGetIntegerv);
        OPENVR_تیاری_Proc(ov_gl_Debug_پیغام_ورننباسه);
        إذا (failed_extension) {
            أرجع SDL_سېټ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    أرجع true;
}

ساكن bool OPENVR_سېټ_Overlay_Error(EVROverlayError e)
{
    بدل (e) {
#تعریف_کړه CASE(X) حالة EVROverlayError_VROverlayError_##X: أرجع SDL_سېټ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_حد_Exceeded);
    CASE(WrongVisibilityType);
    CASE(کلی_Too_Long);
    CASE(NameTooLong);
    CASE(کلی_دننه_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_منزل_بارول_File);
    CASE(Keyboard_Already_دننه_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_ماسک_Primitives);
    CASE(Bad_ماسک_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_قلف_ظرفیت_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_بهر);
#تعریف_لغوه CASE
    افتراضي:
        أرجع SDL_سېټ_Error("Unknown VROverlayError %d", e);
    }
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);

ساكن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->دننی;

    ثابت حرف * hint_پلنوالی = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hint_لوړوالی = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحيح پلنوالی = hint_پلنوالی ? SDL_atoi(hint_پلنوالی) : 0;
    صحيح لوړوالی = hint_لوړوالی ? SDL_atoi(hint_لوړوالی) : 0;
    صحيح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_ډېرپېښ.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_ډېرپېښ.w = OPENVR_DEFAULT_پلنوالی;
    display.desktop_ډېرپېښ.h = OPENVR_DEFAULT_لوړوالی;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    إذا (لوړوالی > 0 && پلنوالی > 0) {
        display.desktop_ډېرپېښ.w = پلنوالی;
        display.desktop_ډېرپېښ.h = لوړوالی;
    }
    إذا (fps) {
        display.desktop_ډېرپېښ.refresh_شرح = fps;
    } وإلا {
        display.desktop_ډېرپېښ.refresh_شرح = معلومات->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_شاخص_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_جمع_کړه_Video_Display(&display, false);

    أرجع true;
}

ساكن فراغ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساكن فراغ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;

#که_تعریف_شوی SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#د_که_پای

    إذا (معلومات) {
        إذا (معلومات->openVRLIB) {
            SDL_UnloadObject(معلومات->openVRLIB);
        }
    }
    SDL_free(device->دننی);
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
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;

    إذا (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_پلنوالی;
        videodata->targh = OPENVR_DEFAULT_لوړوالی;
    }

    إذا (videodata->targh != videodata->وروستی_targh
     || videodata->targw != videodata->وروستی_targw) {

        بنية HmdVector2_t ms;
        صحيح حالت;

        إذا (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_ژوروالی_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_ژوروالی_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_تر_ټولو_نږدې);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_تر_ټولو_نږدې);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        حالت = ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER);
        إذا (حالت != GL_FRAMEBUFFER_COMPLETE) {
            أرجع SDL_سېټ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (عائم)videodata->targw;
        ms.v[1] = (عائم)videodata->targh;
        videodata->oOverlay->سېټ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->وروستی_targh = videodata->targh;
        videodata->وروستی_targw = videodata->targw;
    }
    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumble(فراغ *userdata, Uint16 ټیټ_frequency_rumble, Uint16 لوړ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;

    ثابت عائم k_flIntensity = 320.f; // Maximum frequency
    عائم fl_کیڼ_Frequency = (عائم)ټیټ_frequency_rumble * k_flIntensity / 65535.f;
    عائم fl_ښی_Frequency = (عائم)لوړ_frequency_rumble * k_flIntensity / 65535.f;
    عائم flDurationSeconds = 2.f;
    عائم flAmplitude = 1.f;

    videodata->o_ننوت->TriggerHapticVibrationAction(videodata->ننوت_action_handles_haptics[0], 0, flDurationSeconds, fl_کیڼ_Frequency, flAmplitude, 0);
    videodata->o_ننوت->TriggerHapticVibrationAction(videodata->ننوت_action_handles_haptics[1], 0, flDurationSeconds, fl_ښی_Frequency, flAmplitude, 0);

    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumbleTriggers(فراغ *userdata, Uint16 کیڼ_rumble, Uint16 ښی_rumble)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;
    videodata->o_ننوت->TriggerHapticVibrationAction(videodata->ننوت_action_handles_haptics[0], 0, 0.1f, کیڼ_rumble, 1.0, 0);
    videodata->o_ننوت->TriggerHapticVibrationAction(videodata->ننوت_action_handles_haptics[1], 0, 0.1f, ښی_rumble, 1.0, 0);
    أرجع true;
}

ساكن فراغ OPENVR_VirtualControllerUpdate(فراغ *userdata)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ننوت_Digital_Action_معلومات_t digital_ننوت_action;
    ننوت_Analog_Action_معلومات_t analog_ننوت_action;
    EVRInputError e;
#که_تعریف_شوی DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#د_که_پای
    VRActive_Action_سېټ_t action_سېټ = { 0 };
    action_سېټ.ul_Action_سېټ = videodata->ننوت_action_سېټ;
    e = videodata->o_ننوت->UpdateActionState(&action_سېټ, حجم(action_سېټ), 1);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#د_که_پای
        أرجع;
    }

    لكل (صحيح d = 0; d < videodata->ننوت_action_handles_buttons_شمېر; d++)
    {
        إذا (videodata->ننوت_action_handles_buttons[d] == k_ulInvalidActionHandle)
            استمر;
        e = videodata->o_ننوت->Get_Digital_Action_معلومات(videodata->ننوت_action_handles_buttons[d], &digital_ننوت_action, حجم(digital_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
        إذا (e)
        {
#که_تعریف_شوی DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#د_که_پای
            أرجع;
        }
        SDL_سېټ_Joystick_Virtual_Button(joystick, d, digital_ننوت_action.bState);
#که_تعریف_شوی DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#د_که_پای
    }

    // Left Stick
    e = videodata->o_ننوت->Get_Analog_Action_معلومات(videodata->ننوت_action_handles_axes[0], &analog_ننوت_action, حجم(analog_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#د_که_پای
        أرجع;
    }
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ننوت_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ننوت_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ننوت->Get_Analog_Action_معلومات(videodata->ننوت_action_handles_axes[1], &analog_ننوت_action, حجم(analog_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#د_که_پای
        أرجع;
    }
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ننوت_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ننوت_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ننوت->Get_Analog_Action_معلومات(videodata->ننوت_action_handles_axes[2], &analog_ننوت_action, حجم(analog_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#د_که_پای
        أرجع;
    }
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_کیڼ_TRIGGER, (Sint16)((analog_ننوت_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ننوت->Get_Analog_Action_معلومات(videodata->ننوت_action_handles_axes[3], &analog_ننوت_action, حجم(analog_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#د_که_پای
        أرجع;
    }
    SDL_سېټ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ښی_TRIGGER, (Sint16)((analog_ننوت_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#إذا 0
    لكل (a = 0; a < videodata->ننوت_action_handles_axes_شمېر; a++)
    {
        عائم xval = 0.0f;
        e = videodata->o_ننوت->Get_Analog_Action_معلومات(videodata->ننوت_action_handles_axes[a], &analog_ننوت_action, حجم(analog_ننوت_action), k_ul_Invalid_ننوت_ارزښت_Handle);
        إذا (e) اذهب updatefail;
        xval = analog_ننوت_action.x;
        إذا (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        إذا (a == SDL_GAMEPAD_AXIS_کیڼ_TRIGGER || a == SDL_GAMEPAD_AXIS_ښی_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_سېټ_Joystick_Virtual_Axis(joystick, a, xval);
#که_تعریف_شوی DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#د_که_پای
    }
#د_که_پای
#که_تعریف_شوی DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#د_که_پای
    أرجع;
}

ساكن bool OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_معلومات * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    حرف * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_شمېر] = {
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

    إذا ((e = videodata->o_ننوت->Get_Action_سېټ_Handle("/actions/virtualgamepad", &videodata->ننوت_action_سېټ)) != EVRInputError_VRInputError_None)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#د_که_پای
        أرجع SDL_سېټ_Error("Failed to get action set handle");
    }

    videodata->ننوت_action_handles_buttons_شمېر = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ننوت_action_handles_buttons = SDL_malloc(videodata->ننوت_action_handles_buttons_شمېر * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->ننوت_action_handles_buttons_شمېر; i++)
    {
        e = videodata->o_ننوت->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ننوت_action_handles_buttons[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            أرجع SDL_سېټ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->ننوت_action_handles_axes_شمېر = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ننوت_action_handles_axes = SDL_malloc(videodata->ننوت_action_handles_axes_شمېر * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->ننوت_action_handles_axes_شمېر; i++)
    {
        e = videodata->o_ننوت->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ننوت_action_handles_axes[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            أرجع SDL_سېټ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ننوت->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ننوت_action_handles_haptics[0]);
    e |= videodata->o_ننوت->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ننوت_action_handles_haptics[1]);
    إذا (e)
    {
#که_تعریف_شوی DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#د_که_پای
        أرجع SDL_سېټ_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_شمېر;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_شمېر;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    إذا (!virtual_id) {
        أرجع SDL_سېټ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    إذا (!videodata->virtual_joystick) {
        أرجع SDL_سېټ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#که_تعریف_شوی DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ننوت_action_handles_buttons_شمېر, videodata->ننوت_action_handles_axes_شمېر);
#د_که_پای

    أرجع true;
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;

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

        EVROverlayError پایله = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            کړکۍ->title, &videodata->overlayID, &videodata->thumbID);
        إذا (پایله != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سېټ_Error("Could not create dashboard overlay (%d)", پایله );
        }
        پایله = videodata->oOverlay->CreateOverlay(cursorname, کړکۍ->title, &videodata->cursorID);
        إذا (پایله != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سېټ_Error("Could not create cursor overlay (%d)", پایله );
        }
        SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
        SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_OPENVR_OVERLAY_ID_شمېره, videodata->overlayID);
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
#د_که_پای
        }

        لكل (صحيح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            إذا (overlay_flags & (1 << i)) {
                videodata->oOverlay->سېټ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        عائم f_پلنوالی = hint ? (عائم)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->سېټ_Overlay_پلنوالی_دننه_Meters(videodata->overlayID, f_پلنوالی);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        عائم f_Cursor_پلنوالی = hint ? (عائم)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->سېټ_Overlay_پلنوالی_دننه_Meters(videodata->cursorID, f_Cursor_پلنوالی * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        إذا (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->سېټ_Overlay_From_File(videodata->thumbID, tmpcopy);
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
        videodata->oOverlay->سېټ_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    إذا (!OPENVR_CheckRenderbuffer(_this)) {
        أرجع false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->سېټ_Overlay_Name(videodata->overlayID, کړکۍ->title);

    videodata->bDidCreateOverlay = true;
    videodata->کړکۍ = کړکۍ;

    أرجع true;
}


ساكن bool OPENVR_تیاری_چوکاټ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    ساكن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_بفر_rendering = true;

#که_تعریف_شوی DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
    }
#د_که_پای

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    إذا (!(کړکۍ->flags & SDL_کړکۍ_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_ماسک(false, false, false, true);
        ov_glClear(GL_COLOR_بفر_بټ);
        ov_gl_Color_ماسک(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    أرجع true;
}

ساكن bool OPENVR_Release_چوکاټ(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    إذا (!ov_glGetError) {
        أرجع true;
    }

    إذا (!videodata->is_بفر_rendering) {
        أرجع true;
    }

#که_تعریف_شوی DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#د_که_پای

    videodata->is_بفر_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    إذا (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->وروستی_targh &&
        videodata->targw == videodata->وروستی_targw) {
        // Only submit frames to OpenVR if the texture exists.
        بنية Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (فراغ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->سېټ_Overlay_Texture(videodata->overlayID, &tex);
    }

    إذا (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    إذا (videodata->renderdoc_debugmarker_چوکاټ_پای_ټکی) {
        ov_gl_Debug_پیغام_ورننباسه(GL_DEBUG_سرچینه_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    أرجع OPENVR_CheckRenderbuffer(_this);
}

ساكن فراغ OPENVR_HandleResize(SDL_VideoDevice *_this, صحيح w, صحيح h)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->دننی;
    معلومات->targw = w;
    معلومات->targh = h;
}

ساكن bool OPENVR_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    أرجع true;
}


#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
ساكن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam)
{
    بدل (پیغام_2) {
    حالة WM_DESTROY:
        أرجع 0;
    }
    أرجع Def_کړکۍ_Proc(hwnd, پیغام_2, wParam, lParam);
}

ساكن bool OPENVR_GL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    إذا (لار == عدم) {
        لار = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    إذا (لار == عدم) {
        لار = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_بارول_Object(لار);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_لار, لار,
                 SDL_arraysize(_this->gl_config.driver_لار));

    // Allocate OpenGL memory
    _this->gl_معلومات = (بنية SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(بنية SDL_GLDriver_معلومات));
    إذا (!_this->gl_معلومات) {
        أرجع false;
    }
    _this->gl_config.driver_loaded = true;

    أرجع true;
}

ساكن SDL_Function_اشاره_ګر OPENVR_GL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشاره_ګر پایله = عدم;
    إذا (ov_wgl_Get_Proc_پته) {
        پایله = (SDL_Function_اشاره_ګر)ov_wgl_Get_Proc_پته(proc);
        إذا (پایله) {
            أرجع پایله;
        }
    }

    أرجع SDL_بارول_Function(_this->gl_config.dll_handle, proc);
}

ساكن فراغ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    GLint عدد_Extensions;
    صحيح i;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(عدم);
        wnd.hIcon = بارول_Icon(عدم, IDI_APPLICATION);
        wnd.hCursor = بارول_Cursor(عدم, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = عدم;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        ثبتوونکی_Class_A(&wnd);
        hwnd = Create_کړکۍ_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, عدم, عدم, GetModuleHandle(عدم), عدم);

        پیغام_3 پیغام_2;
        طالما (Peek_پیغام(&پیغام_2, عدم, 0, 0, PM_REMOVE)) {
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
        }

        videodata->hdc = GetDC(hwnd);

        ساكن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_منزل_کړکۍ |
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
        GLuint PixelFormat = ټاکنه_Pixel_Format(videodata->hdc, &pfd);
        إذا (!سېټ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_سېټ_Error( "Could not set pixel format" );
            أرجع عدم;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        إذا (!opengl) {
            SDL_سېټ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            أرجع عدم;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_پته(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_پته(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_پته = (PROC(*)(LPCSTR))Get_Proc_پته(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_پته(opengl, "wglDeleteContext");
        إذا (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_سېټ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            أرجع عدم;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        إذا (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_سېټ_Error("Could not make current OpenGL context.");
            أرجع عدم;
        }
    }

    i = OPENVR_InitExtensions(_this);
    إذا (i == 0) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکاټ_پای_ټکی = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    لكل (i = 0; i < عدد_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#که_تعریف_شوی DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#د_که_پای
            videodata->renderdoc_debugmarker_چوکاټ_پای_ټکی = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کړکۍ)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکاټ(_this, کړکۍ);

    SDL_GLContext پایله = SDL_malloc(حجم(بنية SDL_GLContextState));
    إذا (!پایله) {
        أرجع عدم;
    }
    پایله->hglrc = videodata->hglrc;
    أرجع پایله;
}

ساكن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ *wnd, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    أرجع true;
}

ساكن bool OPENVR_GL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    videodata->بدلون_interval = interval;
    أرجع true;
}

ساكن bool OPENVR_GL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح *بدلون_Interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (بدلون_Interval)
        *بدلون_Interval = videodata->بدلون_interval;
    وإلا
        أرجع SDL_سېټ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    ov_wglMakeCurrent(videodata->hdc, عدم);
    ov_wglDeleteContext(videodata->hglrc);
    أرجع true;
}


#وإلا

ساكن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_نسخه, 2,
    EGL_NONE
};

ساكن bool SDL_EGL_Init_دننی(SDL_Video_معلومات * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=عدم;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#که_تعریف_شوی DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#د_که_پای

    إذا (vd->eglDpy == 0) {
        أرجع SDL_سېټ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    إذا (!b) {
        أرجع SDL_سېټ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#که_تعریف_شوی DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#د_که_پای

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#که_تعریف_شوی DEBUG_OPENVR
    {
        صحيح err = eglGetError();
        إذا (err != EGL_SUCCESS) {
            أرجع SDL_سېټ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#د_که_پای

    إذا (!vd->eglCtx) {
        أرجع SDL_سېټ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    أرجع true;
}

// Linux, EGL, etc.
ساكن bool OVR_EGL_بارول_Library(SDL_VideoDevice *_this, ثابت حرف *لار)
{
    أرجع SDL_EGL_بارول_Library(_this, لار, EGL_DEFAULT_DISPLAY);
}

ساكن SDL_Function_اشاره_ګر OVR_EGL_Get_Proc_پته(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_پته(proc);
}
ساكن فراغ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساكن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    GLint عدد_Extensions;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (!videodata->eglCtx) {
        إذا (!SDL_EGL_Init_دننی(videodata)) {
            أرجع عدم;
        }
    }

    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکاټ_پای_ټکی = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    لكل(صحيح i = 0; i < عدد_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#که_تعریف_شوی DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#د_که_پای
           videodata->renderdoc_debugmarker_چوکاټ_پای_ټکی = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کړکۍ)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکاټ(_this, کړکۍ);

    أرجع videodata->eglCtx;
}

ساكن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_کړکۍ * wnd, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    أرجع true;
}

ساكن bool OVR_EGL_سېټ_بدلون_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    videodata->بدلون_interval = interval;
    أرجع true;
}

ساكن bool OVR_EGL_Get_بدلون_Interval(SDL_VideoDevice *_this, صحيح * بدلون_Interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (بدلون_Interval)
        *بدلون_Interval = videodata->بدلون_interval;
    وإلا
        أرجع SDL_سېټ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    أرجع true;
}

#د_که_پای

ساكن bool OPENVR_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *معلومات;

    // Allocate window internal data
    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (معلومات == عدم) {
        أرجع SDL_بهر_د_حافظه();
    }

    کړکۍ->max_w = 4096;
    کړکۍ->max_h = 4096;
    کړکۍ->min_w = 1;
    کړکۍ->min_h = 1;

    // Setup driver data for this window
    کړکۍ->دننی = معلومات;
    أرجع true;
}


ساكن فراغ OPENVR_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات;

    معلومات = کړکۍ->دننی;
    SDL_free(معلومات);
    کړکۍ->دننی = عدم;
}

ساكن فراغ OPENVR_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات * معلومات = (SDL_Video_معلومات *)_this->دننی;
    إذا (معلومات->bDidCreateOverlay) {
        معلومات->oOverlay->سېټ_Overlay_Name(معلومات->overlayID, کړکۍ->title);
    }
}

ساكن فراغ OPENVR_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->دننی;

    إذا (کړکۍ->pending.w != کړکۍ->w) {
        کړکۍ->w = کړکۍ->pending.w;
    }

    إذا (کړکۍ->pending.h != کړکۍ->h) {
        کړکۍ->h = کړکۍ->pending.h;
    }

    إذا (معلومات->targh != کړکۍ->h || معلومات->targw != کړکۍ->w) {
        OPENVR_HandleResize(_this, کړکۍ->w, کړکۍ->h);
    }

    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->w, کړکۍ->h);
}

ساكن فراغ OPENVR_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->دننی;
    *w = معلومات->targw;
    *h = معلومات->targh;
}

ساكن فراغ OPENVR_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->دننی;
    إذا (معلومات->targh != کړکۍ->h || معلومات->targw != کړکۍ->w) {
        OPENVR_HandleResize(_this, کړکۍ->w, کړکۍ->h);
    }

    معلومات->oOverlay->ShowDashboard(معلومات->sOverlayName);

    کړکۍ->flags |= (SDL_کړکۍ_ننوت_FOCUS | SDL_کړکۍ_MOUSE_FOCUS);
    SDL_سېټ_Keyboard_Focus(کړکۍ);
}

ساكن فراغ OPENVR_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    أرجع;
}

ساكن bool OPENVR_GL_بدلون_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کړکۍ)) {
            أرجع false;
        }
    }

    إذا (!OPENVR_Release_چوکاټ(_this)) {
        أرجع false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    إذا (videodata->بدلون_interval != 0) {
        videodata->oOverlay->Wait_چوکاټ_Sync(100);
    }

    إذا (!OPENVR_تیاری_چوکاټ(_this, کړکۍ)) {
        أرجع false;
    }

    أرجع true;
}

ساكن Uint8 OPENVR_MapMouseButton(صحيح btn)
{
    إذا (btn == EVRMouse_Button_VRMouse_Button_ښی) {
        أرجع SDL_BUTTON_ښی;
    } وإلا إذا (btn == EVRMouse_Button_VRMouse_Button_منځ) {
        أرجع SDL_BUTTON_منځ;
    } وإلا {
        أرجع SDL_BUTTON_کیڼ;
    }
}

ساكن فراغ OPENVR_HandleMouse(عائم x, عائم y, صحيح btn, صحيح evt)
{
    إذا (evt == 2) {
        SDL_SendMouseMotion(0, عدم, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وإلا {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool ښکته = (evt != 0);
        SDL_SendMouseButton(0, عدم, SDL_GLOBAL_MOUSE_ID, button, ښکته);
    }
}


ساكن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

ساكن فراغ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        أرجع;
    }
    EGamepad_متن_ننوت_ډېرپېښ ننوت_ډېرپېښ;
    بدل (SDL_Get_متن_ننوت_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
    حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_HIDDEN:
        ننوت_ډېرپېښ = EGamepad_متن_ننوت_ډېرپېښ_k_EGamepad_متن_ننوت_ډېرپېښ_Password;
        اكسر;
    افتراضي:
        ننوت_ډېرپېښ = EGamepad_متن_ننوت_ډېرپېښ_k_EGamepad_متن_ننوت_ډېرپېښ_نورمال;
        اكسر;
    }
    EGamepad_متن_ننوت_کرښه_ډېرپېښ کرښه_ډېرپېښ;
    إذا (SDL_Get_متن_ننوت_Multiline(props)) {
        کرښه_ډېرپېښ = EGamepad_متن_ننوت_کرښه_ډېرپېښ_k_EGamepad_متن_ننوت_کرښه_ډېرپېښ_مضرب_کرښې;
    } وإلا {
        کرښه_ډېرپېښ = EGamepad_متن_ننوت_کرښه_ډېرپېښ_k_EGamepad_متن_ننوت_کرښه_ډېرپېښ_Single_کرښه;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ننوت_ډېرپېښ, کرښه_ډېرپېښ,
           EKeyboard_Flags_Keyboard_Flag_اصغري, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساكن فراغ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساكن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *پایله = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (!پایله) {
        أرجع عدم;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_معلومات *ovrc = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*ovrc));
    إذا (!ovrc) {
        SDL_free(پایله);
        أرجع عدم;
    }
    پایله->دننی = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    أرجع پایله;
}

ساكن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_معلومات * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    إذا (!cursor) {
        global_openvr_driver->oOverlay->سېټ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->سېټ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        إذا (e != EVROverlayError_VROverlayError_None) {
            أرجع OPENVR_سېټ_Overlay_Error(e);
        }
        أرجع true;
    }

    global_openvr_driver->oOverlay->سېټ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->دننی;

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

    e = global_openvr_driver->oOverlay->سېټ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سېټ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سېټ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سېټ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سېټ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سېټ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سېټ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سېټ_Overlay_Error(e);
    }

    أرجع true;
}

ساكن فراغ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    إذا (cursor) {
        SDL_Cursor_معلومات *ovrc = cursor->دننی;
        إذا (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساكن bool OPENVR_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, SDL_Surface * icon)
{
    إذا (!global_openvr_driver) {
        أرجع SDL_سېټ_Error("OpenVR Overlay not initialized");
    }

    بینښه texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    إذا (videodata->bIconOverridden) {
        أرجع SDL_سېټ_Error("OpenVR Icon is overridden.");
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

    e = global_openvr_driver->oOverlay->سېټ_Overlay_Texture(videodata->thumbID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سېټ_Overlay_Error(e);
    }
    أرجع true;
}

ساكن bool OPENVR_Show_پیغام_Box(SDL_VideoDevice *_this,ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonid)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    حرف تشه = 0;
    حرف * پیغام = SDL_strdup(messageboxdata->پیغام?messageboxdata->پیغام:"");
    حرف * title = SDL_strdup(messageboxdata->پیغام?messageboxdata->پیغام:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_پیغام_Overlay(پیغام, title, ok, &تشه, &تشه, &تشه);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(پیغام);
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
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->دننی;
    بنية VREvent_t nEvent;
    إذا (videodata->overlayID) {
        طالما (videodata->oOverlay->Poll_بل_Overlay_Event(videodata->overlayID, &nEvent, حجم(nEvent))) {
            بدل (nEvent.eventType) {
            حالة EVREventType_VREvent_ButtonPress:
            حالة EVREventType_VREvent_ButtonUnpress:
                اكسر;
            حالة EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 2);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_ښکته:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 1);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_پورته:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 0);
                اكسر;
            حالة EVREventType_VREvent_ScrollSmooth:
            حالة EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, عدم, SDL_GLOBAL_MOUSE_ID, -nEvent.معلومات.scroll.xdelta, nEvent.معلومات.scroll.ydelta, SDL_MOUSEWHEEL_نورمال);
                اكسر;
            حالة EVREvent_Type_VREvent_Keyboard_Char_ننوت:
                SDL_Send_Keyboard_Unicode_کلی(SDL_GetTicksNS(), nEvent.معلومات.keyboard.c_New_ننوت[0]);
                اكسر;
            حالة EVREventType_VREvent_OverlayShown:
                SDL_سېټ_Keyboard_Focus(videodata->کړکۍ);
                SDL_Send_کړکۍ_Event(videodata->کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
                SDL_Send_کړکۍ_Event(videodata->کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
                اكسر;
            حالة EVREventType_VREvent_OverlayHidden:
                SDL_Send_کړکۍ_Event(videodata->کړکۍ, SDL_EVENT_کړکۍ_HIDDEN, 0, 0);
                SDL_Send_کړکۍ_Event(videodata->کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
                SDL_سېټ_Keyboard_Focus(عدم);
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
    SDL_Video_معلومات *معلومات;
    ثابت حرف *hint;

#که_تعریف_شوی SDL_PLATFORM_WINDOWS
    SDL_ثبتوونکی_App(عدم, 0, عدم);
#د_که_پای

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        معلومات = (بنية SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    } وإلا {
        معلومات = عدم;
    }
    إذا (!معلومات) {
#که_تعریف_شوی SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#د_که_پای
        SDL_free(device);
        أرجع عدم;
    }
    device->دننی = معلومات;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    إذا (hint) {
        معلومات->openVRLIB = SDL_بارول_Object(hint);
    }
    إذا (!معلومات->openVRLIB) {
        معلومات->openVRLIB = SDL_بارول_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    إذا (!معلومات->openVRLIB) {
        SDL_سېټ_Error("Could not open OpenVR API Library");
        اذهب error;
    }

    معلومات->FN_VR_Init_دننی = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_بارول_Function(معلومات->openVRLIB, "VR_InitInternal");
    معلومات->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_بارول_Function(معلومات->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    معلومات->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pch_Interface_نسخه, EVRInitError * peError))SDL_بارول_Function(معلومات->openVRLIB, "VR_GetGenericInterface");
    إذا (!معلومات->FN_VR_Init_دننی || !معلومات->FN_VR_GetVRInitErrorAsEnglishDescription || !معلومات->FN_VR_GetGenericInterface) {
        اذهب error;
    }

    حرف fnname[128];
    EVRInitError e;
    معلومات->vrtoken = معلومات->FN_VR_Init_دننی(&e, EVRApplicationType_VRApplication_Overlay);
    إذا (!معلومات->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        إذا (معلومات->FN_VR_GetVRInitErrorAsEnglishDescription != عدم)
            err = معلومات->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_سېټ_Error("Could not generate OpenVR Context (%s)", err);
        اذهب error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_نسخه);
    معلومات->oSystem = (بنية VR_IVRSystem_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_نسخه);
    معلومات->oOverlay = (بنية VR_IVROverlay_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_نسخه);
    معلومات->o_ننوت = (بنية VR_IVRInput_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);

    إذا (!معلومات->oOverlay || !معلومات->oSystem || !معلومات->o_ننوت) {
        SDL_سېټ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_نسخه, IVROverlay_نسخه, IVRInput_نسخه);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    إذا (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وإلا {
        ثابت حرف *basepath = SDL_Get_بنسټ_لار();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    إذا (!loadpath) {
        اذهب error;
    }

    err = معلومات->o_ننوت->سېټ_Action_Manifest_لار(loadpath);
#که_تعریف_شوی DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#د_که_پای
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
        إذا(!OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(معلومات)) {
            اذهب error;
        }
    }

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->سېټ_Display_ډېرپېښ = OPENVR_سېټ_Display_ډېرپېښ;
    device->CreateSDLWindow = OPENVR_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = OPENVR_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_اندازه = OPENVR_سېټ_کړکۍ_اندازه;
    device->Get_کړکۍ_اندازه_دننه_Pixels = OPENVR_Get_کړکۍ_اندازه_دننه_Pixels;
    device->Show_کړکۍ = OPENVR_Show_کړکۍ;
    device->Hide_کړکۍ = OPENVR_Hide_کړکۍ;
    device->Destroy_کړکۍ = OPENVR_Destroy_کړکۍ;
    device->Show_پیغام_Box = OPENVR_Show_پیغام_Box;

#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
#که_تعریف_شوی SDL_VIDEO_OPENGL_WGL
    device->GL_بارول_Library = OPENVR_GL_بارول_Library;
    device->GL_Get_Proc_پته = OPENVR_GL_Get_Proc_پته;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = OPENVR_GL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = OPENVR_GL_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = OPENVR_GL_بدلون_کړکۍ;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#وإلا
#تېروتنه Needs نور work منزل support EGL
#د_که_پای
#وإلا
    device->GL_بارول_Library = OVR_EGL_بارول_Library;
    device->GL_Get_Proc_پته = OVR_EGL_Get_Proc_پته;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = OVR_EGL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = OVR_EGL_Get_بدلون_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_بدلون_کړکۍ = OPENVR_GL_بدلون_کړکۍ;
#د_که_پای

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_بارول_Library = WIN_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وإلا
    device->Vulkan_بارول_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#د_که_پای

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->سېټ_کړکۍ_Icon = OPENVR_سېټ_کړکۍ_Icon;

    أرجع device;

error:
    OPENVR_Destroy(device);
    أرجع عدم;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, عدم, false
};

#د_که_پای // SDL_VIDEO_DRIVER_OPENVR

