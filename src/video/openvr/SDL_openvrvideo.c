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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENVR

#إذا 0
#تعریف_کن DEBUG_OPENVR
#پایان_اگر

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openvrvideo.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ضمن <SDL3/SDL_opengl.h>
#وإلا
// Currently only EGL, not OpenGL, is supported on other platforms
#ضمن <SDL3/SDL_opengles2.h>
#ضمن <SDL3/SDL_opengles2_gl2.h>
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
#ضمن "../windows/SDL_windowsopengl.h"
#ضمن "../windows/SDL_windowsvulkan.h"

#تعریف_کن DEFAULT_OPENGL "OPENGL32.DLL"

ساكن bool OPENVR_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر);
ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

بنية SDL_GLContextState
{
    HGLRC hglrc;
};
#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS



#اگر_تعریف_شده SDL_PLATFORM_WINDOWS
#تعریف_کن SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وإلا
#تعریف_کن SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#پایان_اگر

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_اولویت_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#تعریف_کن MARKER_ID 0
#تعریف_کن MARKER_STR "vr-marker,frame_end,type,application"

#لغو_تعریف EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_داده * global_openvr_driver;

ساكن فراغ InitializeMouseFunctions(فراغ);

بنية SDL_Cursor_داده
{
    بیعلامت texture_id_handle;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

// GL Extensions for functions we will be using.
ساكن فراغ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساكن فراغ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساكن فراغ (APIENTRY *ov_glBindFramebuffer)(GLenum هدف, GLuint framebuffer);
ساكن فراغ (APIENTRY *ov_glBindRenderbuffer)(GLenum هدف, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glRenderbufferStorage)(GLenum هدف, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
ساكن فراغ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glFramebufferTexture2D)(GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساكن GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_وضعیت)(GLuint framebuffer, GLenum هدف);
ساكن GLenum (APIENTRY *ov_glGetError)(فراغ);
ساكن فراغ (APIENTRY *ov_glFlush)(فراغ);
ساكن فراغ (APIENTRY *ov_gl_پایان)(فراغ);
ساكن فراغ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glTexParameterf)(GLenum هدف, GLenum pname, GLfloat param);
ساكن فراغ (APIENTRY *ov_glTexParameteri)(GLenum هدف, GLenum pname, GLenum param);
ساكن فراغ (APIENTRY *ov_glTexImage2D)(GLenum هدف, GLint level, GLint internalformat, GLsizei عرض, GLsizei ارتفاع, GLint border, GLenum format, GLenum type, ثابت فراغ *داده);
ساكن فراغ (APIENTRY *ov_glBindTexture)(GLenum هدف, GLuint texture);
ساكن فراغ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساكن فراغ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * داده);
ساكن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint شاخص);
ساكن فراغ (APIENTRY *ov_glClear)(GLbitfield ماسک);
ساكن فراغ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساكن فراغ (APIENTRY *ov_gl_Color_ماسک)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساكن فراغ (APIENTRY *ov_gl_Debug_پیام_درج)(GLenum منبع, GLenum type, GLuint id, GLenum severity, GLsizei درازی, ثابت حرف *پیام);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
ساكن PROC (*ov_wgl_Get_Proc_آدرس)(LPCSTR);
ساكن HGLRC (*ov_wglCreateContext)(HDC);
ساكن BOOL (*ov_wglDeleteContext)(HGLRC);
ساكن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#پایان_اگر


#تعریف_کن OPENVR_DEFAULT_عرض 1920
#تعریف_کن OPENVR_DEFAULT_ارتفاع 1080

#تعریف_کن OPENVR_راهاندازی_Proc(proc) { proc = (فراغ *)SDL_GL_Get_Proc_آدرس((#proc)+3); إذا (!proc) { failed_extension = (#proc)+3; } }

ساكن bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    إذا (!ov_glGetError) {
        ثابت حرف * failed_extension = 0;
        OPENVR_راهاندازی_Proc(ov_glGenFramebuffers);
        OPENVR_راهاندازی_Proc(ov_glGenRenderbuffers);
        OPENVR_راهاندازی_Proc(ov_glBindFramebuffer);
        OPENVR_راهاندازی_Proc(ov_glBindRenderbuffer);
        OPENVR_راهاندازی_Proc(ov_glRenderbufferStorage);
        OPENVR_راهاندازی_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_راهاندازی_Proc(ov_glFramebufferTexture2D);
        OPENVR_راهاندازی_Proc(ov_gl_Check_Named_Framebuffer_وضعیت);
        OPENVR_راهاندازی_Proc(ov_glGetError);
        OPENVR_راهاندازی_Proc(ov_glFlush);
        OPENVR_راهاندازی_Proc(ov_gl_پایان);
        OPENVR_راهاندازی_Proc(ov_glGenTextures);
        OPENVR_راهاندازی_Proc(ov_glDeleteTextures);
        OPENVR_راهاندازی_Proc(ov_glTexParameterf);
        OPENVR_راهاندازی_Proc(ov_glTexParameteri);
        OPENVR_راهاندازی_Proc(ov_glTexImage2D);
        OPENVR_راهاندازی_Proc(ov_glBindTexture);
        OPENVR_راهاندازی_Proc(ov_glDrawBuffers);
        OPENVR_راهاندازی_Proc(ov_glClear);
        OPENVR_راهاندازی_Proc(ov_glClearColor);
        OPENVR_راهاندازی_Proc(ov_gl_Color_ماسک);
        OPENVR_راهاندازی_Proc(ov_glGetStringi);
        OPENVR_راهاندازی_Proc(ov_glGetIntegerv);
        OPENVR_راهاندازی_Proc(ov_gl_Debug_پیام_درج);
        إذا (failed_extension) {
            أرجع SDL_مجموعه_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    أرجع true;
}

ساكن bool OPENVR_مجموعه_Overlay_Error(EVROverlayError e)
{
    بدل (e) {
#تعریف_کن CASE(X) حالة EVROverlayError_VROverlayError_##X: أرجع SDL_مجموعه_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_حد_Exceeded);
    CASE(WrongVisibilityType);
    CASE(کلید_Too_Long);
    CASE(NameTooLong);
    CASE(کلید_درون_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_مقصد_بارگیری_File);
    CASE(Keyboard_Already_درون_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_ماسک_Primitives);
    CASE(Bad_ماسک_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_قفل_ظرفیت_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_بیرون);
#لغو_تعریف CASE
    افتراضي:
        أرجع SDL_مجموعه_Error("Unknown VROverlayError %d", e);
    }
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

ساكن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = (SDL_Video_داده *)_this->داخلی;

    ثابت حرف * hint_عرض = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hint_ارتفاع = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحيح عرض = hint_عرض ? SDL_atoi(hint_عرض) : 0;
    صحيح ارتفاع = hint_ارتفاع ? SDL_atoi(hint_ارتفاع) : 0;
    صحيح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_نما.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_نما.w = OPENVR_DEFAULT_عرض;
    display.desktop_نما.h = OPENVR_DEFAULT_ارتفاع;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    إذا (ارتفاع > 0 && عرض > 0) {
        display.desktop_نما.w = عرض;
        display.desktop_نما.h = ارتفاع;
    }
    إذا (fps) {
        display.desktop_نما.refresh_نرخ = fps;
    } وإلا {
        display.desktop_نما.refresh_نرخ = داده->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_شاخص_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_جمع_کن_Video_Display(&display, false);

    أرجع true;
}

ساكن فراغ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساكن فراغ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_داده *داده = device->داخلی;

#اگر_تعریف_شده SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#پایان_اگر

    إذا (داده) {
        إذا (داده->openVRLIB) {
            SDL_UnloadObject(داده->openVRLIB);
        }
    }
    SDL_free(device->داخلی);
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
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;

    إذا (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_عرض;
        videodata->targh = OPENVR_DEFAULT_ارتفاع;
    }

    إذا (videodata->targh != videodata->آخرین_targh
     || videodata->targw != videodata->آخرین_targw) {

        بنية HmdVector2_t ms;
        صحيح وضعیت;

        إذا (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_عمق_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_عمق_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_نزدیکترین);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_نزدیکترین);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        وضعیت = ov_gl_Check_Named_Framebuffer_وضعیت(videodata->fbo, GL_FRAMEBUFFER);
        إذا (وضعیت != GL_FRAMEBUFFER_COMPLETE) {
            أرجع SDL_مجموعه_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (عائم)videodata->targw;
        ms.v[1] = (عائم)videodata->targh;
        videodata->oOverlay->مجموعه_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->آخرین_targh = videodata->targh;
        videodata->آخرین_targw = videodata->targw;
    }
    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumble(فراغ *userdata, Uint16 کم_frequency_rumble, Uint16 بالا_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_داده *videodata = (SDL_Video_داده *)userdata;

    ثابت عائم k_flIntensity = 320.f; // Maximum frequency
    عائم fl_چپ_Frequency = (عائم)کم_frequency_rumble * k_flIntensity / 65535.f;
    عائم fl_راست_Frequency = (عائم)بالا_frequency_rumble * k_flIntensity / 65535.f;
    عائم flDurationSeconds = 2.f;
    عائم flAmplitude = 1.f;

    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[0], 0, flDurationSeconds, fl_چپ_Frequency, flAmplitude, 0);
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[1], 0, flDurationSeconds, fl_راست_Frequency, flAmplitude, 0);

    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumbleTriggers(فراغ *userdata, Uint16 چپ_rumble, Uint16 راست_rumble)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)userdata;
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[0], 0, 0.1f, چپ_rumble, 1.0, 0);
    videodata->o_درون_داد->TriggerHapticVibrationAction(videodata->درون_داد_action_handles_haptics[1], 0, 0.1f, راست_rumble, 1.0, 0);
    أرجع true;
}

ساكن فراغ OPENVR_VirtualControllerUpdate(فراغ *userdata)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    درون_داد_Digital_Action_داده_t digital_درون_داد_action;
    درون_داد_Analog_Action_داده_t analog_درون_داد_action;
    EVRInputError e;
#اگر_تعریف_شده DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#پایان_اگر
    VRActive_Action_مجموعه_t action_مجموعه = { 0 };
    action_مجموعه.ul_Action_مجموعه = videodata->درون_داد_action_مجموعه;
    e = videodata->o_درون_داد->UpdateActionState(&action_مجموعه, حجم(action_مجموعه), 1);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#پایان_اگر
        أرجع;
    }

    لكل (صحيح d = 0; d < videodata->درون_داد_action_handles_buttons_شمار; d++)
    {
        إذا (videodata->درون_داد_action_handles_buttons[d] == k_ulInvalidActionHandle)
            استمر;
        e = videodata->o_درون_داد->Get_Digital_Action_داده(videodata->درون_داد_action_handles_buttons[d], &digital_درون_داد_action, حجم(digital_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
        إذا (e)
        {
#اگر_تعریف_شده DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#پایان_اگر
            أرجع;
        }
        SDL_مجموعه_Joystick_Virtual_Button(joystick, d, digital_درون_داد_action.bState);
#اگر_تعریف_شده DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#پایان_اگر
    }

    // Left Stick
    e = videodata->o_درون_داد->Get_Analog_Action_داده(videodata->درون_داد_action_handles_axes[0], &analog_درون_داد_action, حجم(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#پایان_اگر
        أرجع;
    }
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_درون_داد_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_درون_داد_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_درون_داد->Get_Analog_Action_داده(videodata->درون_داد_action_handles_axes[1], &analog_درون_داد_action, حجم(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#پایان_اگر
        أرجع;
    }
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_درون_داد_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_درون_داد_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_درون_داد->Get_Analog_Action_داده(videodata->درون_داد_action_handles_axes[2], &analog_درون_داد_action, حجم(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#پایان_اگر
        أرجع;
    }
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_چپ_TRIGGER, (Sint16)((analog_درون_داد_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_درون_داد->Get_Analog_Action_داده(videodata->درون_داد_action_handles_axes[3], &analog_درون_داد_action, حجم(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#پایان_اگر
        أرجع;
    }
    SDL_مجموعه_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_راست_TRIGGER, (Sint16)((analog_درون_داد_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#إذا 0
    لكل (a = 0; a < videodata->درون_داد_action_handles_axes_شمار; a++)
    {
        عائم xval = 0.0f;
        e = videodata->o_درون_داد->Get_Analog_Action_داده(videodata->درون_داد_action_handles_axes[a], &analog_درون_داد_action, حجم(analog_درون_داد_action), k_ul_Invalid_درون_داد_مقدار_Handle);
        إذا (e) اذهب updatefail;
        xval = analog_درون_داد_action.x;
        إذا (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        إذا (a == SDL_GAMEPAD_AXIS_چپ_TRIGGER || a == SDL_GAMEPAD_AXIS_راست_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_مجموعه_Joystick_Virtual_Axis(joystick, a, xval);
#اگر_تعریف_شده DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#پایان_اگر
    }
#پایان_اگر
#اگر_تعریف_شده DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#پایان_اگر
    أرجع;
}

ساكن bool OPENVR_راهاندازی_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_داده * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    حرف * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_شمار] = {
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

    إذا ((e = videodata->o_درون_داد->Get_Action_مجموعه_Handle("/actions/virtualgamepad", &videodata->درون_داد_action_مجموعه)) != EVRInputError_VRInputError_None)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#پایان_اگر
        أرجع SDL_مجموعه_Error("Failed to get action set handle");
    }

    videodata->درون_داد_action_handles_buttons_شمار = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->درون_داد_action_handles_buttons = SDL_malloc(videodata->درون_داد_action_handles_buttons_شمار * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->درون_داد_action_handles_buttons_شمار; i++)
    {
        e = videodata->o_درون_داد->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->درون_داد_action_handles_buttons[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            أرجع SDL_مجموعه_Error("ERROR: Failed to get button action");
        }
    }

    videodata->درون_داد_action_handles_axes_شمار = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->درون_داد_action_handles_axes = SDL_malloc(videodata->درون_داد_action_handles_axes_شمار * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->درون_داد_action_handles_axes_شمار; i++)
    {
        e = videodata->o_درون_داد->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->درون_داد_action_handles_axes[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            أرجع SDL_مجموعه_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_درون_داد->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->درون_داد_action_handles_haptics[0]);
    e |= videodata->o_درون_داد->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->درون_داد_action_handles_haptics[1]);
    إذا (e)
    {
#اگر_تعریف_شده DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#پایان_اگر
        أرجع SDL_مجموعه_Error("ERROR: Failed to get haptics action");
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

    إذا (!virtual_id) {
        أرجع SDL_مجموعه_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    إذا (!videodata->virtual_joystick) {
        أرجع SDL_مجموعه_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#اگر_تعریف_شده DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->درون_داد_action_handles_buttons_شمار, videodata->درون_داد_action_handles_axes_شمار);
#پایان_اگر

    أرجع true;
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;

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

        EVROverlayError نتیجه = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            پنجره->title, &videodata->overlayID, &videodata->thumbID);
        إذا (نتیجه != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_مجموعه_Error("Could not create dashboard overlay (%d)", نتیجه );
        }
        نتیجه = videodata->oOverlay->CreateOverlay(cursorname, پنجره->title, &videodata->cursorID);
        إذا (نتیجه != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_مجموعه_Error("Could not create cursor overlay (%d)", نتیجه );
        }
        SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
        SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_OPENVR_OVERLAY_ID_عدد, videodata->overlayID);
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
#پایان_اگر
        }

        لكل (صحيح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            إذا (overlay_flags & (1 << i)) {
                videodata->oOverlay->مجموعه_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        عائم f_عرض = hint ? (عائم)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->مجموعه_Overlay_عرض_درون_Meters(videodata->overlayID, f_عرض);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        عائم f_Cursor_عرض = hint ? (عائم)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->مجموعه_Overlay_عرض_درون_Meters(videodata->cursorID, f_Cursor_عرض * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        إذا (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->مجموعه_Overlay_From_File(videodata->thumbID, tmpcopy);
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
        videodata->oOverlay->مجموعه_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    إذا (!OPENVR_CheckRenderbuffer(_this)) {
        أرجع false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->مجموعه_Overlay_Name(videodata->overlayID, پنجره->title);

    videodata->bDidCreateOverlay = true;
    videodata->پنجره = پنجره;

    أرجع true;
}


ساكن bool OPENVR_راهاندازی_قاب(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    ساكن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_میانگیر_rendering = true;

#اگر_تعریف_شده DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_وضعیت(videodata->fbo, GL_FRAMEBUFFER));
    }
#پایان_اگر

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    إذا (!(پنجره->flags & SDL_پنجره_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_ماسک(false, false, false, true);
        ov_glClear(GL_COLOR_میانگیر_بیت);
        ov_gl_Color_ماسک(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    أرجع true;
}

ساكن bool OPENVR_Release_قاب(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    إذا (!ov_glGetError) {
        أرجع true;
    }

    إذا (!videodata->is_میانگیر_rendering) {
        أرجع true;
    }

#اگر_تعریف_شده DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_وضعیت(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#پایان_اگر

    videodata->is_میانگیر_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    إذا (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->آخرین_targh &&
        videodata->targw == videodata->آخرین_targw) {
        // Only submit frames to OpenVR if the texture exists.
        بنية Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (فراغ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->مجموعه_Overlay_Texture(videodata->overlayID, &tex);
    }

    إذا (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    إذا (videodata->renderdoc_debugmarker_قاب_انتها) {
        ov_gl_Debug_پیام_درج(GL_DEBUG_منبع_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    أرجع OPENVR_CheckRenderbuffer(_this);
}

ساكن فراغ OPENVR_HandleResize(SDL_VideoDevice *_this, صحيح w, صحيح h)
{
    SDL_Video_داده *داده = (SDL_Video_داده *)_this->داخلی;
    داده->targw = w;
    داده->targh = h;
}

ساكن bool OPENVR_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    أرجع true;
}


#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
ساكن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT پیام_2, WPARAM wParam, LPARAM lParam)
{
    بدل (پیام_2) {
    حالة WM_DESTROY:
        أرجع 0;
    }
    أرجع Def_پنجره_Proc(hwnd, پیام_2, wParam, lParam);
}

ساكن bool OPENVR_GL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    إذا (مسیر == عدم) {
        مسیر = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    إذا (مسیر == عدم) {
        مسیر = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_بارگیری_Object(مسیر);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_مسیر, مسیر,
                 SDL_arraysize(_this->gl_config.driver_مسیر));

    // Allocate OpenGL memory
    _this->gl_داده = (بنية SDL_GLDriver_داده *)SDL_calloc(1, حجم(بنية SDL_GLDriver_داده));
    إذا (!_this->gl_داده) {
        أرجع false;
    }
    _this->gl_config.driver_loaded = true;

    أرجع true;
}

ساكن SDL_Function_اشاره_گر OPENVR_GL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشاره_گر نتیجه = عدم;
    إذا (ov_wgl_Get_Proc_آدرس) {
        نتیجه = (SDL_Function_اشاره_گر)ov_wgl_Get_Proc_آدرس(proc);
        إذا (نتیجه) {
            أرجع نتیجه;
        }
    }

    أرجع SDL_بارگیری_Function(_this->gl_config.dll_handle, proc);
}

ساكن فراغ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    GLint رقم_Extensions;
    صحيح i;
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(عدم);
        wnd.hIcon = بارگیری_Icon(عدم, IDI_APPLICATION);
        wnd.hCursor = بارگیری_Cursor(عدم, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = عدم;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        ثبات_Class_A(&wnd);
        hwnd = Create_پنجره_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, عدم, عدم, GetModuleHandle(عدم), عدم);

        پیام_3 پیام_2;
        طالما (Peek_پیام(&پیام_2, عدم, 0, 0, PM_REMOVE)) {
            Translate_پیام(&پیام_2);
            Dispatch_پیام(&پیام_2);
        }

        videodata->hdc = GetDC(hwnd);

        ساكن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_مقصد_پنجره |
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
        GLuint PixelFormat = انتخاب_Pixel_Format(videodata->hdc, &pfd);
        إذا (!مجموعه_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_مجموعه_Error( "Could not set pixel format" );
            أرجع عدم;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        إذا (!opengl) {
            SDL_مجموعه_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            أرجع عدم;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_آدرس(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_آدرس(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_آدرس = (PROC(*)(LPCSTR))Get_Proc_آدرس(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_آدرس(opengl, "wglDeleteContext");
        إذا (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_مجموعه_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            أرجع عدم;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        إذا (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_مجموعه_Error("Could not make current OpenGL context.");
            أرجع عدم;
        }
    }

    i = OPENVR_InitExtensions(_this);
    إذا (i == 0) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_قاب_انتها = false;

    ov_glGetIntegerv(GL_رقم_EXTENSIONS, &رقم_Extensions);
    لكل (i = 0; i < رقم_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#اگر_تعریف_شده DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#پایان_اگر
            videodata->renderdoc_debugmarker_قاب_انتها = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, پنجره)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_راهاندازی_قاب(_this, پنجره);

    SDL_GLContext نتیجه = SDL_malloc(حجم(بنية SDL_GLContextState));
    إذا (!نتیجه) {
        أرجع عدم;
    }
    نتیجه->hglrc = videodata->hglrc;
    أرجع نتیجه;
}

ساكن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره *wnd, SDL_GLContext context)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    أرجع true;
}

ساكن bool OPENVR_GL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    videodata->جابجا_interval = interval;
    أرجع true;
}

ساكن bool OPENVR_GL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح *جابجا_Interval)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (جابجا_Interval)
        *جابجا_Interval = videodata->جابجا_interval;
    وإلا
        أرجع SDL_مجموعه_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    ov_wglMakeCurrent(videodata->hdc, عدم);
    ov_wglDeleteContext(videodata->hglrc);
    أرجع true;
}


#وإلا

ساكن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_نسخه, 2,
    EGL_NONE
};

ساكن bool SDL_EGL_Init_داخلی(SDL_Video_داده * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=عدم;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#اگر_تعریف_شده DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#پایان_اگر

    إذا (vd->eglDpy == 0) {
        أرجع SDL_مجموعه_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    إذا (!b) {
        أرجع SDL_مجموعه_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#اگر_تعریف_شده DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#پایان_اگر

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#اگر_تعریف_شده DEBUG_OPENVR
    {
        صحيح err = eglGetError();
        إذا (err != EGL_SUCCESS) {
            أرجع SDL_مجموعه_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#پایان_اگر

    إذا (!vd->eglCtx) {
        أرجع SDL_مجموعه_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    أرجع true;
}

// Linux, EGL, etc.
ساكن bool OVR_EGL_بارگیری_Library(SDL_VideoDevice *_this, ثابت حرف *مسیر)
{
    أرجع SDL_EGL_بارگیری_Library(_this, مسیر, EGL_DEFAULT_DISPLAY);
}

ساكن SDL_Function_اشاره_گر OVR_EGL_Get_Proc_آدرس(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_آدرس(proc);
}
ساكن فراغ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساكن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    GLint رقم_Extensions;
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (!videodata->eglCtx) {
        إذا (!SDL_EGL_Init_داخلی(videodata)) {
            أرجع عدم;
        }
    }

    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_قاب_انتها = false;

    ov_glGetIntegerv(GL_رقم_EXTENSIONS, &رقم_Extensions);
    لكل(صحيح i = 0; i < رقم_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#اگر_تعریف_شده DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#پایان_اگر
           videodata->renderdoc_debugmarker_قاب_انتها = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, پنجره)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_راهاندازی_قاب(_this, پنجره);

    أرجع videodata->eglCtx;
}

ساكن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_پنجره * wnd, SDL_GLContext context)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    أرجع true;
}

ساكن bool OVR_EGL_مجموعه_جابجا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    videodata->جابجا_interval = interval;
    أرجع true;
}

ساكن bool OVR_EGL_Get_جابجا_Interval(SDL_VideoDevice *_this, صحيح * جابجا_Interval)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (جابجا_Interval)
        *جابجا_Interval = videodata->جابجا_interval;
    وإلا
        أرجع SDL_مجموعه_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    أرجع true;
}

#پایان_اگر

ساكن bool OPENVR_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *داده;

    // Allocate window internal data
    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (داده == عدم) {
        أرجع SDL_بیرون_از_حافظه();
    }

    پنجره->max_w = 4096;
    پنجره->max_h = 4096;
    پنجره->min_w = 1;
    پنجره->min_h = 1;

    // Setup driver data for this window
    پنجره->داخلی = داده;
    أرجع true;
}


ساكن فراغ OPENVR_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده;

    داده = پنجره->داخلی;
    SDL_free(داده);
    پنجره->داخلی = عدم;
}

ساكن فراغ OPENVR_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده * داده = (SDL_Video_داده *)_this->داخلی;
    إذا (داده->bDidCreateOverlay) {
        داده->oOverlay->مجموعه_Overlay_Name(داده->overlayID, پنجره->title);
    }
}

ساكن فراغ OPENVR_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = (SDL_Video_داده *)_this->داخلی;

    إذا (پنجره->pending.w != پنجره->w) {
        پنجره->w = پنجره->pending.w;
    }

    إذا (پنجره->pending.h != پنجره->h) {
        پنجره->h = پنجره->pending.h;
    }

    إذا (داده->targh != پنجره->h || داده->targw != پنجره->w) {
        OPENVR_HandleResize(_this, پنجره->w, پنجره->h);
    }

    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره->w, پنجره->h);
}

ساكن فراغ OPENVR_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    SDL_Video_داده *داده = (SDL_Video_داده *)_this->داخلی;
    *w = داده->targw;
    *h = داده->targh;
}

ساكن فراغ OPENVR_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = (SDL_Video_داده *)_this->داخلی;
    إذا (داده->targh != پنجره->h || داده->targw != پنجره->w) {
        OPENVR_HandleResize(_this, پنجره->w, پنجره->h);
    }

    داده->oOverlay->ShowDashboard(داده->sOverlayName);

    پنجره->flags |= (SDL_پنجره_درون_داد_FOCUS | SDL_پنجره_MOUSE_FOCUS);
    SDL_مجموعه_Keyboard_Focus(پنجره);
}

ساكن فراغ OPENVR_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    أرجع;
}

ساكن bool OPENVR_GL_جابجا_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, پنجره)) {
            أرجع false;
        }
    }

    إذا (!OPENVR_Release_قاب(_this)) {
        أرجع false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    إذا (videodata->جابجا_interval != 0) {
        videodata->oOverlay->Wait_قاب_Sync(100);
    }

    إذا (!OPENVR_راهاندازی_قاب(_this, پنجره)) {
        أرجع false;
    }

    أرجع true;
}

ساكن Uint8 OPENVR_MapMouseButton(صحيح btn)
{
    إذا (btn == EVRMouse_Button_VRMouse_Button_راست) {
        أرجع SDL_BUTTON_راست;
    } وإلا إذا (btn == EVRMouse_Button_VRMouse_Button_میانه) {
        أرجع SDL_BUTTON_میانه;
    } وإلا {
        أرجع SDL_BUTTON_چپ;
    }
}

ساكن فراغ OPENVR_HandleMouse(عائم x, عائم y, صحيح btn, صحيح evt)
{
    إذا (evt == 2) {
        SDL_SendMouseMotion(0, عدم, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وإلا {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool پایین = (evt != 0);
        SDL_SendMouseButton(0, عدم, SDL_GLOBAL_MOUSE_ID, button, پایین);
    }
}


ساكن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

ساكن فراغ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        أرجع;
    }
    EGamepad_متن_درون_داد_نما درون_داد_نما;
    بدل (SDL_Get_متن_درون_داد_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        درون_داد_نما = EGamepad_متن_درون_داد_نما_k_EGamepad_متن_درون_داد_نما_Password;
        اكسر;
    افتراضي:
        درون_داد_نما = EGamepad_متن_درون_داد_نما_k_EGamepad_متن_درون_داد_نما_نرمال;
        اكسر;
    }
    EGamepad_متن_درون_داد_سطر_نما سطر_نما;
    إذا (SDL_Get_متن_درون_داد_Multiline(props)) {
        سطر_نما = EGamepad_متن_درون_داد_سطر_نما_k_EGamepad_متن_درون_داد_سطر_نما_مضرب_سطرها;
    } وإلا {
        سطر_نما = EGamepad_متن_درون_داد_سطر_نما_k_EGamepad_متن_درون_داد_سطر_نما_Single_سطر;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           درون_داد_نما, سطر_نما,
           EKeyboard_Flags_Keyboard_Flag_کمینه, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساكن فراغ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساكن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *نتیجه = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (!نتیجه) {
        أرجع عدم;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_داده *ovrc = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*ovrc));
    إذا (!ovrc) {
        SDL_free(نتیجه);
        أرجع عدم;
    }
    نتیجه->داخلی = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    أرجع نتیجه;
}

ساكن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_داده * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    إذا (!cursor) {
        global_openvr_driver->oOverlay->مجموعه_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->مجموعه_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        إذا (e != EVROverlayError_VROverlayError_None) {
            أرجع OPENVR_مجموعه_Overlay_Error(e);
        }
        أرجع true;
    }

    global_openvr_driver->oOverlay->مجموعه_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->داخلی;

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

    e = global_openvr_driver->oOverlay->مجموعه_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_مجموعه_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->مجموعه_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_مجموعه_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->مجموعه_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_مجموعه_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->مجموعه_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_مجموعه_Overlay_Error(e);
    }

    أرجع true;
}

ساكن فراغ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    إذا (cursor) {
        SDL_Cursor_داده *ovrc = cursor->داخلی;
        إذا (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساكن bool OPENVR_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_Surface * icon)
{
    إذا (!global_openvr_driver) {
        أرجع SDL_مجموعه_Error("OpenVR Overlay not initialized");
    }

    بیعلامت texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    إذا (videodata->bIconOverridden) {
        أرجع SDL_مجموعه_Error("OpenVR Icon is overridden.");
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

    e = global_openvr_driver->oOverlay->مجموعه_Overlay_Texture(videodata->thumbID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_مجموعه_Overlay_Error(e);
    }
    أرجع true;
}

ساكن bool OPENVR_Show_پیام_Box(SDL_VideoDevice *_this,ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonid)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    حرف خالی = 0;
    حرف * پیام = SDL_strdup(messageboxdata->پیام?messageboxdata->پیام:"");
    حرف * title = SDL_strdup(messageboxdata->پیام?messageboxdata->پیام:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_پیام_Overlay(پیام, title, ok, &خالی, &خالی, &خالی);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(پیام);
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
    SDL_Video_داده *videodata = (SDL_Video_داده *)_this->داخلی;
    بنية VREvent_t nEvent;
    إذا (videodata->overlayID) {
        طالما (videodata->oOverlay->Poll_بعدی_Overlay_Event(videodata->overlayID, &nEvent, حجم(nEvent))) {
            بدل (nEvent.eventType) {
            حالة EVREventType_VREvent_ButtonPress:
            حالة EVREventType_VREvent_ButtonUnpress:
                اكسر;
            حالة EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.داده.mouse.x, videodata->targh - nEvent.داده.mouse.y, nEvent.داده.mouse.button, 2);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_پایین:
                OPENVR_HandleMouse(nEvent.داده.mouse.x, videodata->targh - nEvent.داده.mouse.y, nEvent.داده.mouse.button, 1);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_به_بالا:
                OPENVR_HandleMouse(nEvent.داده.mouse.x, videodata->targh - nEvent.داده.mouse.y, nEvent.داده.mouse.button, 0);
                اكسر;
            حالة EVREventType_VREvent_ScrollSmooth:
            حالة EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, عدم, SDL_GLOBAL_MOUSE_ID, -nEvent.داده.scroll.xdelta, nEvent.داده.scroll.ydelta, SDL_MOUSEWHEEL_نرمال);
                اكسر;
            حالة EVREvent_Type_VREvent_Keyboard_Char_درون_داد:
                SDL_Send_Keyboard_Unicode_کلید(SDL_GetTicksNS(), nEvent.داده.keyboard.c_New_درون_داد[0]);
                اكسر;
            حالة EVREventType_VREvent_OverlayShown:
                SDL_مجموعه_Keyboard_Focus(videodata->پنجره);
                SDL_Send_پنجره_Event(videodata->پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
                SDL_Send_پنجره_Event(videodata->پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
                اكسر;
            حالة EVREventType_VREvent_OverlayHidden:
                SDL_Send_پنجره_Event(videodata->پنجره, SDL_EVENT_پنجره_HIDDEN, 0, 0);
                SDL_Send_پنجره_Event(videodata->پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
                SDL_مجموعه_Keyboard_Focus(عدم);
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
    SDL_Video_داده *داده;
    ثابت حرف *hint;

#اگر_تعریف_شده SDL_PLATFORM_WINDOWS
    SDL_ثبات_App(عدم, 0, عدم);
#پایان_اگر

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        داده = (بنية SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    } وإلا {
        داده = عدم;
    }
    إذا (!داده) {
#اگر_تعریف_شده SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#پایان_اگر
        SDL_free(device);
        أرجع عدم;
    }
    device->داخلی = داده;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    إذا (hint) {
        داده->openVRLIB = SDL_بارگیری_Object(hint);
    }
    إذا (!داده->openVRLIB) {
        داده->openVRLIB = SDL_بارگیری_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    إذا (!داده->openVRLIB) {
        SDL_مجموعه_Error("Could not open OpenVR API Library");
        اذهب error;
    }

    داده->FN_VR_Init_داخلی = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_بارگیری_Function(داده->openVRLIB, "VR_InitInternal");
    داده->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_بارگیری_Function(داده->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    داده->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pch_Interface_نسخه, EVRInitError * peError))SDL_بارگیری_Function(داده->openVRLIB, "VR_GetGenericInterface");
    إذا (!داده->FN_VR_Init_داخلی || !داده->FN_VR_GetVRInitErrorAsEnglishDescription || !داده->FN_VR_GetGenericInterface) {
        اذهب error;
    }

    حرف fnname[128];
    EVRInitError e;
    داده->vrtoken = داده->FN_VR_Init_داخلی(&e, EVRApplicationType_VRApplication_Overlay);
    إذا (!داده->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        إذا (داده->FN_VR_GetVRInitErrorAsEnglishDescription != عدم)
            err = داده->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_مجموعه_Error("Could not generate OpenVR Context (%s)", err);
        اذهب error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_نسخه);
    داده->oSystem = (بنية VR_IVRSystem_Fn_جدول *)داده->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_نسخه);
    داده->oOverlay = (بنية VR_IVROverlay_Fn_جدول *)داده->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_نسخه);
    داده->o_درون_داد = (بنية VR_IVRInput_Fn_جدول *)داده->FN_VR_GetGenericInterface(fnname, &e);

    إذا (!داده->oOverlay || !داده->oSystem || !داده->o_درون_داد) {
        SDL_مجموعه_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_نسخه, IVROverlay_نسخه, IVRInput_نسخه);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    إذا (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وإلا {
        ثابت حرف *basepath = SDL_Get_پایه_مسیر();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    إذا (!loadpath) {
        اذهب error;
    }

    err = داده->o_درون_داد->مجموعه_Action_Manifest_مسیر(loadpath);
#اگر_تعریف_شده DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#پایان_اگر
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
        إذا(!OPENVR_راهاندازی_Joystick_Based_On_Loaded_Action_Manifest(داده)) {
            اذهب error;
        }
    }

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->حرر = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->مجموعه_Display_نما = OPENVR_مجموعه_Display_نما;
    device->CreateSDLWindow = OPENVR_Create_پنجره;
    device->مجموعه_پنجره_Title = OPENVR_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_اندازه = OPENVR_مجموعه_پنجره_اندازه;
    device->Get_پنجره_اندازه_درون_Pixels = OPENVR_Get_پنجره_اندازه_درون_Pixels;
    device->Show_پنجره = OPENVR_Show_پنجره;
    device->Hide_پنجره = OPENVR_Hide_پنجره;
    device->Destroy_پنجره = OPENVR_Destroy_پنجره;
    device->Show_پیام_Box = OPENVR_Show_پیام_Box;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
#اگر_تعریف_شده SDL_VIDEO_OPENGL_WGL
    device->GL_بارگیری_Library = OPENVR_GL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = OPENVR_GL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = OPENVR_GL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = OPENVR_GL_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = OPENVR_GL_جابجا_پنجره;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#وإلا
#خطا Needs بیشتر work مقصد support EGL
#پایان_اگر
#وإلا
    device->GL_بارگیری_Library = OVR_EGL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = OVR_EGL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = OVR_EGL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = OVR_EGL_Get_جابجا_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_جابجا_پنجره = OPENVR_GL_جابجا_پنجره;
#پایان_اگر

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_بارگیری_Library = WIN_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وإلا
    device->Vulkan_بارگیری_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#پایان_اگر

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->مجموعه_پنجره_Icon = OPENVR_مجموعه_پنجره_Icon;

    أرجع device;

error:
    OPENVR_Destroy(device);
    أرجع عدم;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, عدم, false
};

#پایان_اگر // SDL_VIDEO_DRIVER_OPENVR

