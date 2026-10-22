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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OPENVR

#إذا 0
#تعریف_کرو DEBUG_OPENVR
#جے_انت

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openvrvideo.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ضمن <SDL3/SDL_opengl.h>
#وإلا
// Currently only EGL, not OpenGL, is supported on other platforms
#ضمن <SDL3/SDL_opengles2.h>
#ضمن <SDL3/SDL_opengles2_gl2.h>
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#ضمن "../windows/SDL_windowsopengl.h"
#ضمن "../windows/SDL_windowsvulkan.h"

#تعریف_کرو DEFAULT_OPENGL "OPENGL32.DLL"

ساكن bool OPENVR_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ);
ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

بنية SDL_GLContextState
{
    HGLRC hglrc;
};
#جے_انت // SDL_VIDEO_DRIVER_WINDOWS



#جے_تعریف_شدہ SDL_PLATFORM_WINDOWS
#تعریف_کرو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وإلا
#تعریف_کرو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#جے_انت

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#تعریف_کرو MARKER_ID 0
#تعریف_کرو MARKER_STR "vr-marker,frame_end,type,application"

#تعریف_رد EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_انکڑے * global_openvr_driver;

ساكن فراغ InitializeMouseFunctions(فراغ);

بنية SDL_Cursor_انکڑے
{
    بنانشانی texture_id_handle;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

// GL Extensions for functions we will be using.
ساكن فراغ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساكن فراغ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساكن فراغ (APIENTRY *ov_glBindFramebuffer)(GLenum نشانہ, GLuint framebuffer);
ساكن فراغ (APIENTRY *ov_glBindRenderbuffer)(GLenum نشانہ, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glRenderbufferStorage)(GLenum نشانہ, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
ساكن فراغ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum نشانہ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glFramebufferTexture2D)(GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساكن GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_حالت)(GLuint framebuffer, GLenum نشانہ);
ساكن GLenum (APIENTRY *ov_glGetError)(فراغ);
ساكن فراغ (APIENTRY *ov_glFlush)(فراغ);
ساكن فراغ (APIENTRY *ov_gl_انت)(فراغ);
ساكن فراغ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glTexParameterf)(GLenum نشانہ, GLenum pname, GLfloat param);
ساكن فراغ (APIENTRY *ov_glTexParameteri)(GLenum نشانہ, GLenum pname, GLenum param);
ساكن فراغ (APIENTRY *ov_glTexImage2D)(GLenum نشانہ, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اچائی, GLint border, GLenum format, GLenum type, ثابت فراغ *انکڑے);
ساكن فراغ (APIENTRY *ov_glBindTexture)(GLenum نشانہ, GLuint texture);
ساكن فراغ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساكن فراغ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * انکڑے);
ساكن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint اشاریہ);
ساكن فراغ (APIENTRY *ov_glClear)(GLbitfield نقاب);
ساكن فراغ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساكن فراغ (APIENTRY *ov_gl_Color_نقاب)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساكن فراغ (APIENTRY *ov_gl_Debug_سنیہا_داخل_کرو)(GLenum سروت, GLenum type, GLuint id, GLenum severity, GLsizei لمائی, ثابت حرف *سنیہا);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
ساكن PROC (*ov_wgl_Get_Proc_پتہ)(LPCSTR);
ساكن HGLRC (*ov_wglCreateContext)(HDC);
ساكن BOOL (*ov_wglDeleteContext)(HGLRC);
ساكن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#جے_انت


#تعریف_کرو OPENVR_DEFAULT_چوڑائی 1920
#تعریف_کرو OPENVR_DEFAULT_اچائی 1080

#تعریف_کرو OPENVR_تیاری_Proc(proc) { proc = (فراغ *)SDL_GL_Get_Proc_پتہ((#proc)+3); إذا (!proc) { failed_extension = (#proc)+3; } }

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
        OPENVR_تیاری_Proc(ov_gl_انت);
        OPENVR_تیاری_Proc(ov_glGenTextures);
        OPENVR_تیاری_Proc(ov_glDeleteTextures);
        OPENVR_تیاری_Proc(ov_glTexParameterf);
        OPENVR_تیاری_Proc(ov_glTexParameteri);
        OPENVR_تیاری_Proc(ov_glTexImage2D);
        OPENVR_تیاری_Proc(ov_glBindTexture);
        OPENVR_تیاری_Proc(ov_glDrawBuffers);
        OPENVR_تیاری_Proc(ov_glClear);
        OPENVR_تیاری_Proc(ov_glClearColor);
        OPENVR_تیاری_Proc(ov_gl_Color_نقاب);
        OPENVR_تیاری_Proc(ov_glGetStringi);
        OPENVR_تیاری_Proc(ov_glGetIntegerv);
        OPENVR_تیاری_Proc(ov_gl_Debug_سنیہا_داخل_کرو);
        إذا (failed_extension) {
            أرجع SDL_سیٹ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    أرجع true;
}

ساكن bool OPENVR_سیٹ_Overlay_Error(EVROverlayError e)
{
    بدل (e) {
#تعریف_کرو CASE(X) حالة EVROverlayError_VROverlayError_##X: أرجع SDL_سیٹ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_حد_بندی_Exceeded);
    CASE(WrongVisibilityType);
    CASE(کلید_Too_Long);
    CASE(NameTooLong);
    CASE(کلید_وچ_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_منزل_لدو_File);
    CASE(Keyboard_Already_وچ_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_نقاب_Primitives);
    CASE(Bad_نقاب_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_جندرا_سمرتھا_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_باہرلا);
#تعریف_رد CASE
    افتراضي:
        أرجع SDL_سیٹ_Error("Unknown VROverlayError %d", e);
    }
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

ساكن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;

    ثابت حرف * hint_چوڑائی = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hint_اچائی = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحيح چوڑائی = hint_چوڑائی ? SDL_atoi(hint_چوڑائی) : 0;
    صحيح اچائی = hint_اچائی ? SDL_atoi(hint_اچائی) : 0;
    صحيح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_منوال.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_منوال.w = OPENVR_DEFAULT_چوڑائی;
    display.desktop_منوال.h = OPENVR_DEFAULT_اچائی;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    إذا (اچائی > 0 && چوڑائی > 0) {
        display.desktop_منوال.w = چوڑائی;
        display.desktop_منوال.h = اچائی;
    }
    إذا (fps) {
        display.desktop_منوال.refresh_شرح = fps;
    } وإلا {
        display.desktop_منوال.refresh_شرح = انکڑے->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_اشاریہ_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_جوڑو_Video_Display(&display, false);

    أرجع true;
}

ساكن فراغ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساكن فراغ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_انکڑے *انکڑے = device->اندرونی;

#جے_تعریف_شدہ SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#جے_انت

    إذا (انکڑے) {
        إذا (انکڑے->openVRLIB) {
            SDL_UnloadObject(انکڑے->openVRLIB);
        }
    }
    SDL_free(device->اندرونی);
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
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;

    إذا (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_چوڑائی;
        videodata->targh = OPENVR_DEFAULT_اچائی;
    }

    إذا (videodata->targh != videodata->آخری_targh
     || videodata->targw != videodata->آخری_targw) {

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
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_ڈونگھائی_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_ڈونگھائی_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_سبھ_توں_نیڑے);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_سبھ_توں_نیڑے);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        حالت = ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER);
        إذا (حالت != GL_FRAMEBUFFER_COMPLETE) {
            أرجع SDL_سیٹ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (عائم)videodata->targw;
        ms.v[1] = (عائم)videodata->targh;
        videodata->oOverlay->سیٹ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->آخری_targh = videodata->targh;
        videodata->آخری_targw = videodata->targw;
    }
    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumble(فراغ *userdata, Uint16 کم_frequency_rumble, Uint16 بلند_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)userdata;

    ثابت عائم k_flIntensity = 320.f; // Maximum frequency
    عائم fl_بایاں_Frequency = (عائم)کم_frequency_rumble * k_flIntensity / 65535.f;
    عائم fl_دایاں_Frequency = (عائم)بلند_frequency_rumble * k_flIntensity / 65535.f;
    عائم flDurationSeconds = 2.f;
    عائم flAmplitude = 1.f;

    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[0], 0, flDurationSeconds, fl_بایاں_Frequency, flAmplitude, 0);
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[1], 0, flDurationSeconds, fl_دایاں_Frequency, flAmplitude, 0);

    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumbleTriggers(فراغ *userdata, Uint16 بایاں_rumble, Uint16 دایاں_rumble)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)userdata;
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[0], 0, 0.1f, بایاں_rumble, 1.0, 0);
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[1], 0, 0.1f, دایاں_rumble, 1.0, 0);
    أرجع true;
}

ساكن فراغ OPENVR_VirtualControllerUpdate(فراغ *userdata)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    داخلہ_Digital_Action_انکڑے_t digital_داخلہ_action;
    داخلہ_Analog_Action_انکڑے_t analog_داخلہ_action;
    EVRInputError e;
#جے_تعریف_شدہ DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#جے_انت
    VRActive_Action_سیٹ_t action_سیٹ = { 0 };
    action_سیٹ.ul_Action_سیٹ = videodata->داخلہ_action_سیٹ;
    e = videodata->o_داخلہ->UpdateActionState(&action_سیٹ, حجم(action_سیٹ), 1);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#جے_انت
        أرجع;
    }

    لكل (صحيح d = 0; d < videodata->داخلہ_action_handles_buttons_گنتی; d++)
    {
        إذا (videodata->داخلہ_action_handles_buttons[d] == k_ulInvalidActionHandle)
            استمر;
        e = videodata->o_داخلہ->Get_Digital_Action_انکڑے(videodata->داخلہ_action_handles_buttons[d], &digital_داخلہ_action, حجم(digital_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
        إذا (e)
        {
#جے_تعریف_شدہ DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#جے_انت
            أرجع;
        }
        SDL_سیٹ_Joystick_Virtual_Button(joystick, d, digital_داخلہ_action.bState);
#جے_تعریف_شدہ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#جے_انت
    }

    // Left Stick
    e = videodata->o_داخلہ->Get_Analog_Action_انکڑے(videodata->داخلہ_action_handles_axes[0], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#جے_انت
        أرجع;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_داخلہ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_داخلہ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_داخلہ->Get_Analog_Action_انکڑے(videodata->داخلہ_action_handles_axes[1], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#جے_انت
        أرجع;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_داخلہ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_داخلہ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_داخلہ->Get_Analog_Action_انکڑے(videodata->داخلہ_action_handles_axes[2], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#جے_انت
        أرجع;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_بایاں_TRIGGER, (Sint16)((analog_داخلہ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_داخلہ->Get_Analog_Action_انکڑے(videodata->داخلہ_action_handles_axes[3], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#جے_انت
        أرجع;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_دایاں_TRIGGER, (Sint16)((analog_داخلہ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#إذا 0
    لكل (a = 0; a < videodata->داخلہ_action_handles_axes_گنتی; a++)
    {
        عائم xval = 0.0f;
        e = videodata->o_داخلہ->Get_Analog_Action_انکڑے(videodata->داخلہ_action_handles_axes[a], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
        إذا (e) اذهب updatefail;
        xval = analog_داخلہ_action.x;
        إذا (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        إذا (a == SDL_GAMEPAD_AXIS_بایاں_TRIGGER || a == SDL_GAMEPAD_AXIS_دایاں_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_سیٹ_Joystick_Virtual_Axis(joystick, a, xval);
#جے_تعریف_شدہ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#جے_انت
    }
#جے_انت
#جے_تعریف_شدہ DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#جے_انت
    أرجع;
}

ساكن bool OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_انکڑے * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    حرف * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_گنتی] = {
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

    إذا ((e = videodata->o_داخلہ->Get_Action_سیٹ_Handle("/actions/virtualgamepad", &videodata->داخلہ_action_سیٹ)) != EVRInputError_VRInputError_None)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#جے_انت
        أرجع SDL_سیٹ_Error("Failed to get action set handle");
    }

    videodata->داخلہ_action_handles_buttons_گنتی = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->داخلہ_action_handles_buttons = SDL_malloc(videodata->داخلہ_action_handles_buttons_گنتی * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->داخلہ_action_handles_buttons_گنتی; i++)
    {
        e = videodata->o_داخلہ->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->داخلہ_action_handles_buttons[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            أرجع SDL_سیٹ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->داخلہ_action_handles_axes_گنتی = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->داخلہ_action_handles_axes = SDL_malloc(videodata->داخلہ_action_handles_axes_گنتی * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->داخلہ_action_handles_axes_گنتی; i++)
    {
        e = videodata->o_داخلہ->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->داخلہ_action_handles_axes[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            أرجع SDL_سیٹ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_داخلہ->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->داخلہ_action_handles_haptics[0]);
    e |= videodata->o_داخلہ->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->داخلہ_action_handles_haptics[1]);
    إذا (e)
    {
#جے_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#جے_انت
        أرجع SDL_سیٹ_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_گنتی;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_گنتی;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    إذا (!virtual_id) {
        أرجع SDL_سیٹ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    إذا (!videodata->virtual_joystick) {
        أرجع SDL_سیٹ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#جے_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->داخلہ_action_handles_buttons_گنتی, videodata->داخلہ_action_handles_axes_گنتی);
#جے_انت

    أرجع true;
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;

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

        EVROverlayError نتیجہ = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            کھڑکی->title, &videodata->overlayID, &videodata->thumbID);
        إذا (نتیجہ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سیٹ_Error("Could not create dashboard overlay (%d)", نتیجہ );
        }
        نتیجہ = videodata->oOverlay->CreateOverlay(cursorname, کھڑکی->title, &videodata->cursorID);
        إذا (نتیجہ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سیٹ_Error("Could not create cursor overlay (%d)", نتیجہ );
        }
        SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
        SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_OPENVR_OVERLAY_ID_نمبر, videodata->overlayID);
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
#جے_انت
        }

        لكل (صحيح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            إذا (overlay_flags & (1 << i)) {
                videodata->oOverlay->سیٹ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        عائم f_چوڑائی = hint ? (عائم)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->سیٹ_Overlay_چوڑائی_وچ_Meters(videodata->overlayID, f_چوڑائی);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        عائم f_Cursor_چوڑائی = hint ? (عائم)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->سیٹ_Overlay_چوڑائی_وچ_Meters(videodata->cursorID, f_Cursor_چوڑائی * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        إذا (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->سیٹ_Overlay_From_File(videodata->thumbID, tmpcopy);
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
        videodata->oOverlay->سیٹ_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    إذا (!OPENVR_CheckRenderbuffer(_this)) {
        أرجع false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->سیٹ_Overlay_Name(videodata->overlayID, کھڑکی->title);

    videodata->bDidCreateOverlay = true;
    videodata->کھڑکی = کھڑکی;

    أرجع true;
}


ساكن bool OPENVR_تیاری_چوکھٹا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    ساكن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_بفر_rendering = true;

#جے_تعریف_شدہ DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
    }
#جے_انت

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    إذا (!(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_نقاب(false, false, false, true);
        ov_glClear(GL_COLOR_بفر_ثنائی_ہندسہ);
        ov_gl_Color_نقاب(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    أرجع true;
}

ساكن bool OPENVR_Release_چوکھٹا(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    إذا (!ov_glGetError) {
        أرجع true;
    }

    إذا (!videodata->is_بفر_rendering) {
        أرجع true;
    }

#جے_تعریف_شدہ DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#جے_انت

    videodata->is_بفر_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    إذا (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->آخری_targh &&
        videodata->targw == videodata->آخری_targw) {
        // Only submit frames to OpenVR if the texture exists.
        بنية Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (فراغ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->سیٹ_Overlay_Texture(videodata->overlayID, &tex);
    }

    إذا (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    إذا (videodata->renderdoc_debugmarker_چوکھٹا_سرا) {
        ov_gl_Debug_سنیہا_داخل_کرو(GL_DEBUG_سروت_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    أرجع OPENVR_CheckRenderbuffer(_this);
}

ساكن فراغ OPENVR_HandleResize(SDL_VideoDevice *_this, صحيح w, صحيح h)
{
    SDL_Video_انکڑے *انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;
    انکڑے->targw = w;
    انکڑے->targh = h;
}

ساكن bool OPENVR_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    أرجع true;
}


#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
ساكن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT پیغام, WPARAM wParam, LPARAM lParam)
{
    بدل (پیغام) {
    حالة WM_DESTROY:
        أرجع 0;
    }
    أرجع Def_کھڑکی_Proc(hwnd, پیغام, wParam, lParam);
}

ساكن bool OPENVR_GL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    إذا (رستہ == عدم) {
        رستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    إذا (رستہ == عدم) {
        رستہ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_لدو_Object(رستہ);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_رستہ, رستہ,
                 SDL_arraysize(_this->gl_config.driver_رستہ));

    // Allocate OpenGL memory
    _this->gl_انکڑے = (بنية SDL_GLDriver_انکڑے *)SDL_calloc(1, حجم(بنية SDL_GLDriver_انکڑے));
    إذا (!_this->gl_انکڑے) {
        أرجع false;
    }
    _this->gl_config.driver_loaded = true;

    أرجع true;
}

ساكن SDL_Function_اشارہ_گر OPENVR_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر نتیجہ = عدم;
    إذا (ov_wgl_Get_Proc_پتہ) {
        نتیجہ = (SDL_Function_اشارہ_گر)ov_wgl_Get_Proc_پتہ(proc);
        إذا (نتیجہ) {
            أرجع نتیجہ;
        }
    }

    أرجع SDL_لدو_Function(_this->gl_config.dll_handle, proc);
}

ساكن فراغ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    GLint عدد_Extensions;
    صحيح i;
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(عدم);
        wnd.hIcon = لدو_Icon(عدم, IDI_APPLICATION);
        wnd.hCursor = لدو_Cursor(عدم, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = عدم;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        رجسٹر_Class_A(&wnd);
        hwnd = Create_کھڑکی_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, عدم, عدم, GetModuleHandle(عدم), عدم);

        پیغام_2 پیغام;
        طالما (Peek_سنیہا(&پیغام, عدم, 0, 0, PM_REMOVE)) {
            Translate_سنیہا(&پیغام);
            Dispatch_سنیہا(&پیغام);
        }

        videodata->hdc = GetDC(hwnd);

        ساكن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_منزل_کھڑکی |
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
        GLuint PixelFormat = چنو_Pixel_Format(videodata->hdc, &pfd);
        إذا (!سیٹ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_سیٹ_Error( "Could not set pixel format" );
            أرجع عدم;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        إذا (!opengl) {
            SDL_سیٹ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            أرجع عدم;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_پتہ(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_پتہ(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_پتہ = (PROC(*)(LPCSTR))Get_Proc_پتہ(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_پتہ(opengl, "wglDeleteContext");
        إذا (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_سیٹ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            أرجع عدم;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        إذا (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_سیٹ_Error("Could not make current OpenGL context.");
            أرجع عدم;
        }
    }

    i = OPENVR_InitExtensions(_this);
    إذا (i == 0) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکھٹا_سرا = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    لكل (i = 0; i < عدد_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#جے_تعریف_شدہ DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#جے_انت
            videodata->renderdoc_debugmarker_چوکھٹا_سرا = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکھٹا(_this, کھڑکی);

    SDL_GLContext نتیجہ = SDL_malloc(حجم(بنية SDL_GLContextState));
    إذا (!نتیجہ) {
        أرجع عدم;
    }
    نتیجہ->hglrc = videodata->hglrc;
    أرجع نتیجہ;
}

ساكن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *wnd, SDL_GLContext context)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    أرجع true;
}

ساكن bool OPENVR_GL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    videodata->وٹاندرا_interval = interval;
    أرجع true;
}

ساكن bool OPENVR_GL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *وٹاندرا_Interval)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (وٹاندرا_Interval)
        *وٹاندرا_Interval = videodata->وٹاندرا_interval;
    وإلا
        أرجع SDL_سیٹ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    ov_wglMakeCurrent(videodata->hdc, عدم);
    ov_wglDeleteContext(videodata->hglrc);
    أرجع true;
}


#وإلا

ساكن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_نسخہ, 2,
    EGL_NONE
};

ساكن bool SDL_EGL_Init_اندرونی(SDL_Video_انکڑے * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=عدم;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#جے_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#جے_انت

    إذا (vd->eglDpy == 0) {
        أرجع SDL_سیٹ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    إذا (!b) {
        أرجع SDL_سیٹ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#جے_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#جے_انت

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#جے_تعریف_شدہ DEBUG_OPENVR
    {
        صحيح err = eglGetError();
        إذا (err != EGL_SUCCESS) {
            أرجع SDL_سیٹ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#جے_انت

    إذا (!vd->eglCtx) {
        أرجع SDL_سیٹ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    أرجع true;
}

// Linux, EGL, etc.
ساكن bool OVR_EGL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ)
{
    أرجع SDL_EGL_لدو_Library(_this, رستہ, EGL_DEFAULT_DISPLAY);
}

ساكن SDL_Function_اشارہ_گر OVR_EGL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_پتہ(proc);
}
ساكن فراغ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساكن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    GLint عدد_Extensions;
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (!videodata->eglCtx) {
        إذا (!SDL_EGL_Init_اندرونی(videodata)) {
            أرجع عدم;
        }
    }

    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکھٹا_سرا = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    لكل(صحيح i = 0; i < عدد_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#جے_تعریف_شدہ DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#جے_انت
           videodata->renderdoc_debugmarker_چوکھٹا_سرا = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکھٹا(_this, کھڑکی);

    أرجع videodata->eglCtx;
}

ساكن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی * wnd, SDL_GLContext context)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    أرجع true;
}

ساكن bool OVR_EGL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    videodata->وٹاندرا_interval = interval;
    أرجع true;
}

ساكن bool OVR_EGL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح * وٹاندرا_Interval)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (وٹاندرا_Interval)
        *وٹاندرا_Interval = videodata->وٹاندرا_interval;
    وإلا
        أرجع SDL_سیٹ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    أرجع true;
}

#جے_انت

ساكن bool OPENVR_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *انکڑے;

    // Allocate window internal data
    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (انکڑے == عدم) {
        أرجع SDL_باہرلا_دا_حافظہ();
    }

    کھڑکی->max_w = 4096;
    کھڑکی->max_h = 4096;
    کھڑکی->min_w = 1;
    کھڑکی->min_h = 1;

    // Setup driver data for this window
    کھڑکی->اندرونی = انکڑے;
    أرجع true;
}


ساكن فراغ OPENVR_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے;

    انکڑے = کھڑکی->اندرونی;
    SDL_free(انکڑے);
    کھڑکی->اندرونی = عدم;
}

ساكن فراغ OPENVR_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے * انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (انکڑے->bDidCreateOverlay) {
        انکڑے->oOverlay->سیٹ_Overlay_Name(انکڑے->overlayID, کھڑکی->title);
    }
}

ساكن فراغ OPENVR_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;

    إذا (کھڑکی->pending.w != کھڑکی->w) {
        کھڑکی->w = کھڑکی->pending.w;
    }

    إذا (کھڑکی->pending.h != کھڑکی->h) {
        کھڑکی->h = کھڑکی->pending.h;
    }

    إذا (انکڑے->targh != کھڑکی->h || انکڑے->targw != کھڑکی->w) {
        OPENVR_HandleResize(_this, کھڑکی->w, کھڑکی->h);
    }

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->w, کھڑکی->h);
}

ساكن فراغ OPENVR_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    SDL_Video_انکڑے *انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;
    *w = انکڑے->targw;
    *h = انکڑے->targh;
}

ساكن فراغ OPENVR_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (انکڑے->targh != کھڑکی->h || انکڑے->targw != کھڑکی->w) {
        OPENVR_HandleResize(_this, کھڑکی->w, کھڑکی->h);
    }

    انکڑے->oOverlay->ShowDashboard(انکڑے->sOverlayName);

    کھڑکی->flags |= (SDL_کھڑکی_داخلہ_FOCUS | SDL_کھڑکی_MOUSE_FOCUS);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
}

ساكن فراغ OPENVR_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    أرجع;
}

ساكن bool OPENVR_GL_وٹاندرا_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            أرجع false;
        }
    }

    إذا (!OPENVR_Release_چوکھٹا(_this)) {
        أرجع false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    إذا (videodata->وٹاندرا_interval != 0) {
        videodata->oOverlay->Wait_چوکھٹا_Sync(100);
    }

    إذا (!OPENVR_تیاری_چوکھٹا(_this, کھڑکی)) {
        أرجع false;
    }

    أرجع true;
}

ساكن Uint8 OPENVR_MapMouseButton(صحيح btn)
{
    إذا (btn == EVRMouse_Button_VRMouse_Button_دایاں) {
        أرجع SDL_BUTTON_دایاں;
    } وإلا إذا (btn == EVRMouse_Button_VRMouse_Button_درمیان) {
        أرجع SDL_BUTTON_درمیان;
    } وإلا {
        أرجع SDL_BUTTON_بایاں;
    }
}

ساكن فراغ OPENVR_HandleMouse(عائم x, عائم y, صحيح btn, صحيح evt)
{
    إذا (evt == 2) {
        SDL_SendMouseMotion(0, عدم, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وإلا {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool تھلے = (evt != 0);
        SDL_SendMouseButton(0, عدم, SDL_GLOBAL_MOUSE_ID, button, تھلے);
    }
}


ساكن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

ساكن فراغ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        أرجع;
    }
    EGamepad_متن_داخلہ_منوال داخلہ_منوال;
    بدل (SDL_Get_متن_داخلہ_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        داخلہ_منوال = EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_Password;
        اكسر;
    افتراضي:
        داخلہ_منوال = EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_عام;
        اكسر;
    }
    EGamepad_متن_داخلہ_سطر_منوال سطر_منوال;
    إذا (SDL_Get_متن_داخلہ_Multiline(props)) {
        سطر_منوال = EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_مضرب_سطریں;
    } وإلا {
        سطر_منوال = EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_Single_سطر;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           داخلہ_منوال, سطر_منوال,
           EKeyboard_Flags_Keyboard_Flag_اقل, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساكن فراغ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساكن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *نتیجہ = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (!نتیجہ) {
        أرجع عدم;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_انکڑے *ovrc = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*ovrc));
    إذا (!ovrc) {
        SDL_free(نتیجہ);
        أرجع عدم;
    }
    نتیجہ->اندرونی = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    أرجع نتیجہ;
}

ساكن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_انکڑے * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    إذا (!cursor) {
        global_openvr_driver->oOverlay->سیٹ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->سیٹ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        إذا (e != EVROverlayError_VROverlayError_None) {
            أرجع OPENVR_سیٹ_Overlay_Error(e);
        }
        أرجع true;
    }

    global_openvr_driver->oOverlay->سیٹ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->اندرونی;

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

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سیٹ_Overlay_Error(e);
    }

    أرجع true;
}

ساكن فراغ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    إذا (cursor) {
        SDL_Cursor_انکڑے *ovrc = cursor->اندرونی;
        إذا (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساكن bool OPENVR_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_Surface * icon)
{
    إذا (!global_openvr_driver) {
        أرجع SDL_سیٹ_Error("OpenVR Overlay not initialized");
    }

    بنانشانی texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    إذا (videodata->bIconOverridden) {
        أرجع SDL_سیٹ_Error("OpenVR Icon is overridden.");
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

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture(videodata->thumbID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سیٹ_Overlay_Error(e);
    }
    أرجع true;
}

ساكن bool OPENVR_Show_سنیہا_Box(SDL_VideoDevice *_this,ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonid)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    حرف خالی_تھاواں = 0;
    حرف * سنیہا = SDL_strdup(messageboxdata->سنیہا?messageboxdata->سنیہا:"");
    حرف * title = SDL_strdup(messageboxdata->سنیہا?messageboxdata->سنیہا:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_سنیہا_Overlay(سنیہا, title, ok, &خالی_تھاواں, &خالی_تھاواں, &خالی_تھاواں);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(سنیہا);
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
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)_this->اندرونی;
    بنية VREvent_t nEvent;
    إذا (videodata->overlayID) {
        طالما (videodata->oOverlay->Poll_اگلا_Overlay_Event(videodata->overlayID, &nEvent, حجم(nEvent))) {
            بدل (nEvent.eventType) {
            حالة EVREventType_VREvent_ButtonPress:
            حالة EVREventType_VREvent_ButtonUnpress:
                اكسر;
            حالة EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.انکڑے.mouse.x, videodata->targh - nEvent.انکڑے.mouse.y, nEvent.انکڑے.mouse.button, 2);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_تھلے:
                OPENVR_HandleMouse(nEvent.انکڑے.mouse.x, videodata->targh - nEvent.انکڑے.mouse.y, nEvent.انکڑے.mouse.button, 1);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_اتے:
                OPENVR_HandleMouse(nEvent.انکڑے.mouse.x, videodata->targh - nEvent.انکڑے.mouse.y, nEvent.انکڑے.mouse.button, 0);
                اكسر;
            حالة EVREventType_VREvent_ScrollSmooth:
            حالة EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, عدم, SDL_GLOBAL_MOUSE_ID, -nEvent.انکڑے.scroll.xdelta, nEvent.انکڑے.scroll.ydelta, SDL_MOUSEWHEEL_عام);
                اكسر;
            حالة EVREvent_Type_VREvent_Keyboard_Char_داخلہ:
                SDL_Send_Keyboard_Unicode_کلید(SDL_GetTicksNS(), nEvent.انکڑے.keyboard.c_New_داخلہ[0]);
                اكسر;
            حالة EVREventType_VREvent_OverlayShown:
                SDL_سیٹ_Keyboard_Focus(videodata->کھڑکی);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
                اكسر;
            حالة EVREventType_VREvent_OverlayHidden:
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                SDL_سیٹ_Keyboard_Focus(عدم);
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
    SDL_Video_انکڑے *انکڑے;
    ثابت حرف *hint;

#جے_تعریف_شدہ SDL_PLATFORM_WINDOWS
    SDL_رجسٹر_App(عدم, 0, عدم);
#جے_انت

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        انکڑے = (بنية SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    } وإلا {
        انکڑے = عدم;
    }
    إذا (!انکڑے) {
#جے_تعریف_شدہ SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#جے_انت
        SDL_free(device);
        أرجع عدم;
    }
    device->اندرونی = انکڑے;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    إذا (hint) {
        انکڑے->openVRLIB = SDL_لدو_Object(hint);
    }
    إذا (!انکڑے->openVRLIB) {
        انکڑے->openVRLIB = SDL_لدو_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    إذا (!انکڑے->openVRLIB) {
        SDL_سیٹ_Error("Could not open OpenVR API Library");
        اذهب error;
    }

    انکڑے->FN_VR_Init_اندرونی = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_لدو_Function(انکڑے->openVRLIB, "VR_InitInternal");
    انکڑے->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_لدو_Function(انکڑے->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    انکڑے->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pch_Interface_نسخہ, EVRInitError * peError))SDL_لدو_Function(انکڑے->openVRLIB, "VR_GetGenericInterface");
    إذا (!انکڑے->FN_VR_Init_اندرونی || !انکڑے->FN_VR_GetVRInitErrorAsEnglishDescription || !انکڑے->FN_VR_GetGenericInterface) {
        اذهب error;
    }

    حرف fnname[128];
    EVRInitError e;
    انکڑے->vrtoken = انکڑے->FN_VR_Init_اندرونی(&e, EVRApplicationType_VRApplication_Overlay);
    إذا (!انکڑے->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        إذا (انکڑے->FN_VR_GetVRInitErrorAsEnglishDescription != عدم)
            err = انکڑے->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_سیٹ_Error("Could not generate OpenVR Context (%s)", err);
        اذهب error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_نسخہ);
    انکڑے->oSystem = (بنية VR_IVRSystem_Fn_جدول *)انکڑے->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_نسخہ);
    انکڑے->oOverlay = (بنية VR_IVROverlay_Fn_جدول *)انکڑے->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_نسخہ);
    انکڑے->o_داخلہ = (بنية VR_IVRInput_Fn_جدول *)انکڑے->FN_VR_GetGenericInterface(fnname, &e);

    إذا (!انکڑے->oOverlay || !انکڑے->oSystem || !انکڑے->o_داخلہ) {
        SDL_سیٹ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_نسخہ, IVROverlay_نسخہ, IVRInput_نسخہ);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    إذا (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وإلا {
        ثابت حرف *basepath = SDL_Get_ادھار_رستہ();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    إذا (!loadpath) {
        اذهب error;
    }

    err = انکڑے->o_داخلہ->سیٹ_Action_Manifest_رستہ(loadpath);
#جے_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#جے_انت
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
        إذا(!OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(انکڑے)) {
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
    device->سیٹ_Display_منوال = OPENVR_سیٹ_Display_منوال;
    device->CreateSDLWindow = OPENVR_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = OPENVR_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_ناپ = OPENVR_سیٹ_کھڑکی_ناپ;
    device->Get_کھڑکی_ناپ_وچ_Pixels = OPENVR_Get_کھڑکی_ناپ_وچ_Pixels;
    device->Show_کھڑکی = OPENVR_Show_کھڑکی;
    device->Hide_کھڑکی = OPENVR_Hide_کھڑکی;
    device->Destroy_کھڑکی = OPENVR_Destroy_کھڑکی;
    device->Show_سنیہا_Box = OPENVR_Show_سنیہا_Box;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    device->GL_لدو_Library = OPENVR_GL_لدو_Library;
    device->GL_Get_Proc_پتہ = OPENVR_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = OPENVR_GL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = OPENVR_GL_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = OPENVR_GL_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#وإلا
#غلطی Needs ہور work منزل support EGL
#جے_انت
#وإلا
    device->GL_لدو_Library = OVR_EGL_لدو_Library;
    device->GL_Get_Proc_پتہ = OVR_EGL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = OVR_EGL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = OVR_EGL_Get_وٹاندرا_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_وٹاندرا_کھڑکی = OPENVR_GL_وٹاندرا_کھڑکی;
#جے_انت

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_لدو_Library = WIN_Vulkan_لدو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وإلا
    device->Vulkan_لدو_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#جے_انت

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->سیٹ_کھڑکی_Icon = OPENVR_سیٹ_کھڑکی_Icon;

    أرجع device;

error:
    OPENVR_Destroy(device);
    أرجع عدم;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, عدم, false
};

#جے_انت // SDL_VIDEO_DRIVER_OPENVR

