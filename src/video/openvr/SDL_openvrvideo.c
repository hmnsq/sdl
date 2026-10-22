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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENVR

#إذا 0
#وصف_ڪريو DEBUG_OPENVR
#جيڪڏهن_پورو

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_openvrvideo.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ضمن <SDL3/SDL_opengl.h>
#وإلا
// Currently only EGL, not OpenGL, is supported on other platforms
#ضمن <SDL3/SDL_opengles2.h>
#ضمن <SDL3/SDL_opengles2_gl2.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
#ضمن "../windows/SDL_windowsopengl.h"
#ضمن "../windows/SDL_windowsvulkan.h"

#وصف_ڪريو DEFAULT_OPENGL "OPENGL32.DLL"

ساكن bool OPENVR_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو);
ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري);

بنية SDL_GLContextState
{
    HGLRC hglrc;
};
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS



#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_WINDOWS
#وصف_ڪريو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#وإلا
#وصف_ڪريو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#جيڪڏهن_پورو

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ترجيح_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#وصف_ڪريو MARKER_ID 0
#وصف_ڪريو MARKER_STR "vr-marker,frame_end,type,application"

#وصف_رد EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_معلومات * global_openvr_driver;

ساكن فراغ InitializeMouseFunctions(فراغ);

بنية SDL_Cursor_معلومات
{
    بنانشان texture_id_handle;
    صحيح hot_x, hot_y;
    صحيح w, h;
};

// GL Extensions for functions we will be using.
ساكن فراغ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساكن فراغ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساكن فراغ (APIENTRY *ov_glBindFramebuffer)(GLenum هدف, GLuint framebuffer);
ساكن فراغ (APIENTRY *ov_glBindRenderbuffer)(GLenum هدف, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glRenderbufferStorage)(GLenum هدف, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
ساكن فراغ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساكن فراغ (APIENTRY *ov_glFramebufferTexture2D)(GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساكن GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_حالت)(GLuint framebuffer, GLenum هدف);
ساكن GLenum (APIENTRY *ov_glGetError)(فراغ);
ساكن فراغ (APIENTRY *ov_glFlush)(فراغ);
ساكن فراغ (APIENTRY *ov_gl_پڄاڻي)(فراغ);
ساكن فراغ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساكن فراغ (APIENTRY *ov_glTexParameterf)(GLenum هدف, GLenum pname, GLfloat param);
ساكن فراغ (APIENTRY *ov_glTexParameteri)(GLenum هدف, GLenum pname, GLenum param);
ساكن فراغ (APIENTRY *ov_glTexImage2D)(GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLenum format, GLenum type, ثابت فراغ *معلومات);
ساكن فراغ (APIENTRY *ov_glBindTexture)(GLenum هدف, GLuint texture);
ساكن فراغ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساكن فراغ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * معلومات);
ساكن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint اشاريو);
ساكن فراغ (APIENTRY *ov_glClear)(GLbitfield نقاب);
ساكن فراغ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساكن فراغ (APIENTRY *ov_gl_Color_نقاب)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساكن فراغ (APIENTRY *ov_gl_Debug_پيغام_وجهو)(GLenum ذريعو, GLenum type, GLuint id, GLenum severity, GLsizei ڊيگهائي, ثابت حرف *پيغام);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
ساكن PROC (*ov_wgl_Get_Proc_پتو)(LPCSTR);
ساكن HGLRC (*ov_wglCreateContext)(HDC);
ساكن BOOL (*ov_wglDeleteContext)(HGLRC);
ساكن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#جيڪڏهن_پورو


#وصف_ڪريو OPENVR_DEFAULT_ويڪر 1920
#وصف_ڪريو OPENVR_DEFAULT_اوچائي 1080

#وصف_ڪريو OPENVR_تياري_Proc(proc) { proc = (فراغ *)SDL_GL_Get_Proc_پتو((#proc)+3); إذا (!proc) { failed_extension = (#proc)+3; } }

ساكن bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    إذا (!ov_glGetError) {
        ثابت حرف * failed_extension = 0;
        OPENVR_تياري_Proc(ov_glGenFramebuffers);
        OPENVR_تياري_Proc(ov_glGenRenderbuffers);
        OPENVR_تياري_Proc(ov_glBindFramebuffer);
        OPENVR_تياري_Proc(ov_glBindRenderbuffer);
        OPENVR_تياري_Proc(ov_glRenderbufferStorage);
        OPENVR_تياري_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_تياري_Proc(ov_glFramebufferTexture2D);
        OPENVR_تياري_Proc(ov_gl_Check_Named_Framebuffer_حالت);
        OPENVR_تياري_Proc(ov_glGetError);
        OPENVR_تياري_Proc(ov_glFlush);
        OPENVR_تياري_Proc(ov_gl_پڄاڻي);
        OPENVR_تياري_Proc(ov_glGenTextures);
        OPENVR_تياري_Proc(ov_glDeleteTextures);
        OPENVR_تياري_Proc(ov_glTexParameterf);
        OPENVR_تياري_Proc(ov_glTexParameteri);
        OPENVR_تياري_Proc(ov_glTexImage2D);
        OPENVR_تياري_Proc(ov_glBindTexture);
        OPENVR_تياري_Proc(ov_glDrawBuffers);
        OPENVR_تياري_Proc(ov_glClear);
        OPENVR_تياري_Proc(ov_glClearColor);
        OPENVR_تياري_Proc(ov_gl_Color_نقاب);
        OPENVR_تياري_Proc(ov_glGetStringi);
        OPENVR_تياري_Proc(ov_glGetIntegerv);
        OPENVR_تياري_Proc(ov_gl_Debug_پيغام_وجهو);
        إذا (failed_extension) {
            أرجع SDL_سيٽ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    أرجع true;
}

ساكن bool OPENVR_سيٽ_Overlay_Error(EVROverlayError e)
{
    بدل (e) {
#وصف_ڪريو CASE(X) حالة EVROverlayError_VROverlayError_##X: أرجع SDL_سيٽ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_حد_بندي_Exceeded);
    CASE(WrongVisibilityType);
    CASE(ڪنجي_Too_Long);
    CASE(NameTooLong);
    CASE(ڪنجي_اندريون_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_منزل_ڀريو_File);
    CASE(Keyboard_Already_اندريون_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_نقاب_Primitives);
    CASE(Bad_نقاب_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_تالو_صلاحيت_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_ٻاهريون);
#وصف_رد CASE
    افتراضي:
        أرجع SDL_سيٽ_Error("Unknown VROverlayError %d", e);
    }
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_دري *دري);

ساكن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->اندروني;

    ثابت حرف * hint_ويڪر = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hint_اوچائي = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحيح ويڪر = hint_ويڪر ? SDL_atoi(hint_ويڪر) : 0;
    صحيح اوچائي = hint_اوچائي ? SDL_atoi(hint_اوچائي) : 0;
    صحيح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_گهڻائي.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_گهڻائي.w = OPENVR_DEFAULT_ويڪر;
    display.desktop_گهڻائي.h = OPENVR_DEFAULT_اوچائي;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    إذا (اوچائي > 0 && ويڪر > 0) {
        display.desktop_گهڻائي.w = ويڪر;
        display.desktop_گهڻائي.h = اوچائي;
    }
    إذا (fps) {
        display.desktop_گهڻائي.refresh_شرح = fps;
    } وإلا {
        display.desktop_گهڻائي.refresh_شرح = معلومات->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_اشاريو_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_جوڙيو_Video_Display(&display, false);

    أرجع true;
}

ساكن فراغ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساكن فراغ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#جيڪڏهن_پورو

    إذا (معلومات) {
        إذا (معلومات->openVRLIB) {
            SDL_UnloadObject(معلومات->openVRLIB);
        }
    }
    SDL_free(device->اندروني);
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
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;

    إذا (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_ويڪر;
        videodata->targh = OPENVR_DEFAULT_اوچائي;
    }

    إذا (videodata->targh != videodata->آخري_targh
     || videodata->targw != videodata->آخري_targw) {

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
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_اونهائي_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_اونهائي_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_سڀ_کان_ويجهو);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_سڀ_کان_ويجهو);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        حالت = ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER);
        إذا (حالت != GL_FRAMEBUFFER_COMPLETE) {
            أرجع SDL_سيٽ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (عائم)videodata->targw;
        ms.v[1] = (عائم)videodata->targh;
        videodata->oOverlay->سيٽ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->آخري_targh = videodata->targh;
        videodata->آخري_targw = videodata->targw;
    }
    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumble(فراغ *userdata, Uint16 هيٺيون_frequency_rumble, Uint16 مٿاهون_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;

    ثابت عائم k_flIntensity = 320.f; // Maximum frequency
    عائم fl_کاٻو_Frequency = (عائم)هيٺيون_frequency_rumble * k_flIntensity / 65535.f;
    عائم fl_ساڄو_Frequency = (عائم)مٿاهون_frequency_rumble * k_flIntensity / 65535.f;
    عائم flDurationSeconds = 2.f;
    عائم flAmplitude = 1.f;

    videodata->o_داخلا->TriggerHapticVibrationAction(videodata->داخلا_action_handles_haptics[0], 0, flDurationSeconds, fl_کاٻو_Frequency, flAmplitude, 0);
    videodata->o_داخلا->TriggerHapticVibrationAction(videodata->داخلا_action_handles_haptics[1], 0, flDurationSeconds, fl_ساڄو_Frequency, flAmplitude, 0);

    أرجع true;
}

ساكن bool OPENVR_VirtualControllerRumbleTriggers(فراغ *userdata, Uint16 کاٻو_rumble, Uint16 ساڄو_rumble)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;
    videodata->o_داخلا->TriggerHapticVibrationAction(videodata->داخلا_action_handles_haptics[0], 0, 0.1f, کاٻو_rumble, 1.0, 0);
    videodata->o_داخلا->TriggerHapticVibrationAction(videodata->داخلا_action_handles_haptics[1], 0, 0.1f, ساڄو_rumble, 1.0, 0);
    أرجع true;
}

ساكن فراغ OPENVR_VirtualControllerUpdate(فراغ *userdata)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    داخلا_Digital_Action_معلومات_t digital_داخلا_action;
    داخلا_Analog_Action_معلومات_t analog_داخلا_action;
    EVRInputError e;
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#جيڪڏهن_پورو
    VRActive_Action_سيٽ_t action_سيٽ = { 0 };
    action_سيٽ.ul_Action_سيٽ = videodata->داخلا_action_سيٽ;
    e = videodata->o_داخلا->UpdateActionState(&action_سيٽ, حجم(action_سيٽ), 1);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#جيڪڏهن_پورو
        أرجع;
    }

    لكل (صحيح d = 0; d < videodata->داخلا_action_handles_buttons_ڳڻپ; d++)
    {
        إذا (videodata->داخلا_action_handles_buttons[d] == k_ulInvalidActionHandle)
            استمر;
        e = videodata->o_داخلا->Get_Digital_Action_معلومات(videodata->داخلا_action_handles_buttons[d], &digital_داخلا_action, حجم(digital_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
        إذا (e)
        {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#جيڪڏهن_پورو
            أرجع;
        }
        SDL_سيٽ_Joystick_Virtual_Button(joystick, d, digital_داخلا_action.bState);
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#جيڪڏهن_پورو
    }

    // Left Stick
    e = videodata->o_داخلا->Get_Analog_Action_معلومات(videodata->داخلا_action_handles_axes[0], &analog_داخلا_action, حجم(analog_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#جيڪڏهن_پورو
        أرجع;
    }
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_داخلا_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_داخلا_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_داخلا->Get_Analog_Action_معلومات(videodata->داخلا_action_handles_axes[1], &analog_داخلا_action, حجم(analog_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#جيڪڏهن_پورو
        أرجع;
    }
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_داخلا_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_داخلا_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_داخلا->Get_Analog_Action_معلومات(videodata->داخلا_action_handles_axes[2], &analog_داخلا_action, حجم(analog_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#جيڪڏهن_پورو
        أرجع;
    }
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_کاٻو_TRIGGER, (Sint16)((analog_داخلا_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_داخلا->Get_Analog_Action_معلومات(videodata->داخلا_action_handles_axes[3], &analog_داخلا_action, حجم(analog_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#جيڪڏهن_پورو
        أرجع;
    }
    SDL_سيٽ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ساڄو_TRIGGER, (Sint16)((analog_داخلا_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#إذا 0
    لكل (a = 0; a < videodata->داخلا_action_handles_axes_ڳڻپ; a++)
    {
        عائم xval = 0.0f;
        e = videodata->o_داخلا->Get_Analog_Action_معلومات(videodata->داخلا_action_handles_axes[a], &analog_داخلا_action, حجم(analog_داخلا_action), k_ul_Invalid_داخلا_قدر_Handle);
        إذا (e) اذهب updatefail;
        xval = analog_داخلا_action.x;
        إذا (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        إذا (a == SDL_GAMEPAD_AXIS_کاٻو_TRIGGER || a == SDL_GAMEPAD_AXIS_ساڄو_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_سيٽ_Joystick_Virtual_Axis(joystick, a, xval);
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#جيڪڏهن_پورو
    }
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#جيڪڏهن_پورو
    أرجع;
}

ساكن bool OPENVR_تياري_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_معلومات * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    حرف * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_ڳڻپ] = {
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

    إذا ((e = videodata->o_داخلا->Get_Action_سيٽ_Handle("/actions/virtualgamepad", &videodata->داخلا_action_سيٽ)) != EVRInputError_VRInputError_None)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#جيڪڏهن_پورو
        أرجع SDL_سيٽ_Error("Failed to get action set handle");
    }

    videodata->داخلا_action_handles_buttons_ڳڻپ = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->داخلا_action_handles_buttons = SDL_malloc(videodata->داخلا_action_handles_buttons_ڳڻپ * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->داخلا_action_handles_buttons_ڳڻپ; i++)
    {
        e = videodata->o_داخلا->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->داخلا_action_handles_buttons[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            أرجع SDL_سيٽ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->داخلا_action_handles_axes_ڳڻپ = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->داخلا_action_handles_axes = SDL_malloc(videodata->داخلا_action_handles_axes_ڳڻپ * حجم(VRActionHandle_t));

    لكل (صحيح i = 0; i < videodata->داخلا_action_handles_axes_ڳڻپ; i++)
    {
        e = videodata->o_داخلا->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->داخلا_action_handles_axes[i]);
        إذا (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            أرجع SDL_سيٽ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_داخلا->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->داخلا_action_handles_haptics[0]);
    e |= videodata->o_داخلا->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->داخلا_action_handles_haptics[1]);
    إذا (e)
    {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#جيڪڏهن_پورو
        أرجع SDL_سيٽ_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_ڳڻپ;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_ڳڻپ;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    إذا (!virtual_id) {
        أرجع SDL_سيٽ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    إذا (!videodata->virtual_joystick) {
        أرجع SDL_سيٽ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->داخلا_action_handles_buttons_ڳڻپ, videodata->داخلا_action_handles_axes_ڳڻپ);
#جيڪڏهن_پورو

    أرجع true;
}

ساكن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;

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

        EVROverlayError نتيجو = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            دري->title, &videodata->overlayID, &videodata->thumbID);
        إذا (نتيجو != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سيٽ_Error("Could not create dashboard overlay (%d)", نتيجو );
        }
        نتيجو = videodata->oOverlay->CreateOverlay(cursorname, دري->title, &videodata->cursorID);
        إذا (نتيجو != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            أرجع SDL_سيٽ_Error("Could not create cursor overlay (%d)", نتيجو );
        }
        SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
        SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_OPENVR_OVERLAY_ID_عدد, videodata->overlayID);
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
#جيڪڏهن_پورو
        }

        لكل (صحيح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            إذا (overlay_flags & (1 << i)) {
                videodata->oOverlay->سيٽ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        عائم f_ويڪر = hint ? (عائم)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->سيٽ_Overlay_ويڪر_اندريون_Meters(videodata->overlayID, f_ويڪر);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        عائم f_Cursor_ويڪر = hint ? (عائم)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->سيٽ_Overlay_ويڪر_اندريون_Meters(videodata->cursorID, f_Cursor_ويڪر * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        إذا (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->سيٽ_Overlay_From_File(videodata->thumbID, tmpcopy);
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
        videodata->oOverlay->سيٽ_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    إذا (!OPENVR_CheckRenderbuffer(_this)) {
        أرجع false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->سيٽ_Overlay_Name(videodata->overlayID, دري->title);

    videodata->bDidCreateOverlay = true;
    videodata->دري = دري;

    أرجع true;
}


ساكن bool OPENVR_تياري_چوکٺو(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    ساكن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_بفر_rendering = true;

#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
    }
#جيڪڏهن_پورو

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    إذا (!(دري->flags & SDL_دري_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_نقاب(false, false, false, true);
        ov_glClear(GL_COLOR_بفر_ٻٽو_انگ);
        ov_gl_Color_نقاب(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    أرجع true;
}

ساكن bool OPENVR_Release_چوکٺو(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    إذا (!ov_glGetError) {
        أرجع true;
    }

    إذا (!videodata->is_بفر_rendering) {
        أرجع true;
    }

#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    {
        صحيح error = ov_glGetError();
        إذا (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#جيڪڏهن_پورو

    videodata->is_بفر_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    إذا (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->آخري_targh &&
        videodata->targw == videodata->آخري_targw) {
        // Only submit frames to OpenVR if the texture exists.
        بنية Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (فراغ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->سيٽ_Overlay_Texture(videodata->overlayID, &tex);
    }

    إذا (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    إذا (videodata->renderdoc_debugmarker_چوکٺو_پڇاڙي) {
        ov_gl_Debug_پيغام_وجهو(GL_DEBUG_ذريعو_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    أرجع OPENVR_CheckRenderbuffer(_this);
}

ساكن فراغ OPENVR_HandleResize(SDL_VideoDevice *_this, صحيح w, صحيح h)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->اندروني;
    معلومات->targw = w;
    معلومات->targh = h;
}

ساكن bool OPENVR_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    أرجع true;
}


#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
ساكن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT نياپو, WPARAM wParam, LPARAM lParam)
{
    بدل (نياپو) {
    حالة WM_DESTROY:
        أرجع 0;
    }
    أرجع Def_دري_Proc(hwnd, نياپو, wParam, lParam);
}

ساكن bool OPENVR_GL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    إذا (رستو == عدم) {
        رستو = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    إذا (رستو == عدم) {
        رستو = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ڀريو_Object(رستو);
    إذا (!_this->gl_config.dll_handle) {
        أرجع false;
    }
    SDL_strlcpy(_this->gl_config.driver_رستو, رستو,
                 SDL_arraysize(_this->gl_config.driver_رستو));

    // Allocate OpenGL memory
    _this->gl_معلومات = (بنية SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(بنية SDL_GLDriver_معلومات));
    إذا (!_this->gl_معلومات) {
        أرجع false;
    }
    _this->gl_config.driver_loaded = true;

    أرجع true;
}

ساكن SDL_Function_اشارو OPENVR_GL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارو نتيجو = عدم;
    إذا (ov_wgl_Get_Proc_پتو) {
        نتيجو = (SDL_Function_اشارو)ov_wgl_Get_Proc_پتو(proc);
        إذا (نتيجو) {
            أرجع نتيجو;
        }
    }

    أرجع SDL_ڀريو_Function(_this->gl_config.dll_handle, proc);
}

ساكن فراغ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساكن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_دري *دري)
{
    GLint انگ_Extensions;
    صحيح i;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(عدم);
        wnd.hIcon = ڀريو_Icon(عدم, IDI_APPLICATION);
        wnd.hCursor = ڀريو_Cursor(عدم, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = عدم;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        رجسٽر_Class_A(&wnd);
        hwnd = Create_دري_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, عدم, عدم, GetModuleHandle(عدم), عدم);

        نياپو_2 نياپو;
        طالما (Peek_پيغام(&نياپو, عدم, 0, 0, PM_REMOVE)) {
            Translate_پيغام(&نياپو);
            Dispatch_پيغام(&نياپو);
        }

        videodata->hdc = GetDC(hwnd);

        ساكن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_منزل_دري |
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
        GLuint PixelFormat = چونڊيو_Pixel_Format(videodata->hdc, &pfd);
        إذا (!سيٽ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_سيٽ_Error( "Could not set pixel format" );
            أرجع عدم;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        إذا (!opengl) {
            SDL_سيٽ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            أرجع عدم;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_پتو(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_پتو(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_پتو = (PROC(*)(LPCSTR))Get_Proc_پتو(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_پتو(opengl, "wglDeleteContext");
        إذا (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_سيٽ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            أرجع عدم;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        إذا (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_سيٽ_Error("Could not make current OpenGL context.");
            أرجع عدم;
        }
    }

    i = OPENVR_InitExtensions(_this);
    إذا (i == 0) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکٺو_پڇاڙي = false;

    ov_glGetIntegerv(GL_انگ_EXTENSIONS, &انگ_Extensions);
    لكل (i = 0; i < انگ_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#جيڪڏهن_پورو
            videodata->renderdoc_debugmarker_چوکٺو_پڇاڙي = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, دري)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تياري_چوکٺو(_this, دري);

    SDL_GLContext نتيجو = SDL_malloc(حجم(بنية SDL_GLContextState));
    إذا (!نتيجو) {
        أرجع عدم;
    }
    نتيجو->hglrc = videodata->hglrc;
    أرجع نتيجو;
}

ساكن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري *wnd, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    أرجع true;
}

ساكن bool OPENVR_GL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    videodata->مٽا_سٽا_interval = interval;
    أرجع true;
}

ساكن bool OPENVR_GL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح *مٽا_سٽا_Interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (مٽا_سٽا_Interval)
        *مٽا_سٽا_Interval = videodata->مٽا_سٽا_interval;
    وإلا
        أرجع SDL_سيٽ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    ov_wglMakeCurrent(videodata->hdc, عدم);
    ov_wglDeleteContext(videodata->hglrc);
    أرجع true;
}


#وإلا

ساكن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_نسخو, 2,
    EGL_NONE
};

ساكن bool SDL_EGL_Init_اندروني(SDL_Video_معلومات * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=عدم;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#جيڪڏهن_پورو

    إذا (vd->eglDpy == 0) {
        أرجع SDL_سيٽ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    إذا (!b) {
        أرجع SDL_سيٽ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#جيڪڏهن_پورو

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    {
        صحيح err = eglGetError();
        إذا (err != EGL_SUCCESS) {
            أرجع SDL_سيٽ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#جيڪڏهن_پورو

    إذا (!vd->eglCtx) {
        أرجع SDL_سيٽ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    أرجع true;
}

// Linux, EGL, etc.
ساكن bool OVR_EGL_ڀريو_Library(SDL_VideoDevice *_this, ثابت حرف *رستو)
{
    أرجع SDL_EGL_ڀريو_Library(_this, رستو, EGL_DEFAULT_DISPLAY);
}

ساكن SDL_Function_اشارو OVR_EGL_Get_Proc_پتو(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    أرجع SDL_EGL_Get_Proc_پتو(proc);
}
ساكن فراغ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساكن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_دري * دري)
{
    GLint انگ_Extensions;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (!videodata->eglCtx) {
        إذا (!SDL_EGL_Init_اندروني(videodata)) {
            أرجع عدم;
        }
    }

    إذا (!OPENVR_InitExtensions(_this)) {
        أرجع عدم;
    }

    videodata->renderdoc_debugmarker_چوکٺو_پڇاڙي = false;

    ov_glGetIntegerv(GL_انگ_EXTENSIONS, &انگ_Extensions);
    لكل(صحيح i = 0; i < انگ_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        إذا (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#جيڪڏهن_پورو
           videodata->renderdoc_debugmarker_چوکٺو_پڇاڙي = true;
        }
    }

    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, دري)) {
            أرجع عدم;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تياري_چوکٺو(_this, دري);

    أرجع videodata->eglCtx;
}

ساكن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_دري * wnd, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    أرجع true;
}

ساكن bool OVR_EGL_سيٽ_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    videodata->مٽا_سٽا_interval = interval;
    أرجع true;
}

ساكن bool OVR_EGL_Get_مٽا_سٽا_Interval(SDL_VideoDevice *_this, صحيح * مٽا_سٽا_Interval)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (مٽا_سٽا_Interval)
        *مٽا_سٽا_Interval = videodata->مٽا_سٽا_interval;
    وإلا
        أرجع SDL_سيٽ_Error("OPENVR: null passed in for GetSwapInterval");
    أرجع true;
}

ساكن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    أرجع true;
}

#جيڪڏهن_پورو

ساكن bool OPENVR_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *معلومات;

    // Allocate window internal data
    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (معلومات == عدم) {
        أرجع SDL_ٻاهريون_جو_يادگيري();
    }

    دري->max_w = 4096;
    دري->max_h = 4096;
    دري->min_w = 1;
    دري->min_h = 1;

    // Setup driver data for this window
    دري->اندروني = معلومات;
    أرجع true;
}


ساكن فراغ OPENVR_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات;

    معلومات = دري->اندروني;
    SDL_free(معلومات);
    دري->اندروني = عدم;
}

ساكن فراغ OPENVR_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات * معلومات = (SDL_Video_معلومات *)_this->اندروني;
    إذا (معلومات->bDidCreateOverlay) {
        معلومات->oOverlay->سيٽ_Overlay_Name(معلومات->overlayID, دري->title);
    }
}

ساكن فراغ OPENVR_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->اندروني;

    إذا (دري->pending.w != دري->w) {
        دري->w = دري->pending.w;
    }

    إذا (دري->pending.h != دري->h) {
        دري->h = دري->pending.h;
    }

    إذا (معلومات->targh != دري->h || معلومات->targw != دري->w) {
        OPENVR_HandleResize(_this, دري->w, دري->h);
    }

    SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, دري->w, دري->h);
}

ساكن فراغ OPENVR_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->اندروني;
    *w = معلومات->targw;
    *h = معلومات->targh;
}

ساكن فراغ OPENVR_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = (SDL_Video_معلومات *)_this->اندروني;
    إذا (معلومات->targh != دري->h || معلومات->targw != دري->w) {
        OPENVR_HandleResize(_this, دري->w, دري->h);
    }

    معلومات->oOverlay->ShowDashboard(معلومات->sOverlayName);

    دري->flags |= (SDL_دري_داخلا_FOCUS | SDL_دري_MOUSE_FOCUS);
    SDL_سيٽ_Keyboard_Focus(دري);
}

ساكن فراغ OPENVR_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    أرجع;
}

ساكن bool OPENVR_GL_مٽا_سٽا_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    إذا (!videodata->bDidCreateOverlay) {
        إذا (!OPENVR_InitializeOverlay(_this, دري)) {
            أرجع false;
        }
    }

    إذا (!OPENVR_Release_چوکٺو(_this)) {
        أرجع false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    إذا (videodata->مٽا_سٽا_interval != 0) {
        videodata->oOverlay->Wait_چوکٺو_Sync(100);
    }

    إذا (!OPENVR_تياري_چوکٺو(_this, دري)) {
        أرجع false;
    }

    أرجع true;
}

ساكن Uint8 OPENVR_MapMouseButton(صحيح btn)
{
    إذا (btn == EVRMouse_Button_VRMouse_Button_ساڄو) {
        أرجع SDL_BUTTON_ساڄو;
    } وإلا إذا (btn == EVRMouse_Button_VRMouse_Button_وچ) {
        أرجع SDL_BUTTON_وچ;
    } وإلا {
        أرجع SDL_BUTTON_کاٻو;
    }
}

ساكن فراغ OPENVR_HandleMouse(عائم x, عائم y, صحيح btn, صحيح evt)
{
    إذا (evt == 2) {
        SDL_SendMouseMotion(0, عدم, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } وإلا {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool هيٺ_ڏانهن = (evt != 0);
        SDL_SendMouseButton(0, عدم, SDL_GLOBAL_MOUSE_ID, button, هيٺ_ڏانهن);
    }
}


ساكن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

ساكن فراغ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        أرجع;
    }
    EGamepad_متن_داخلا_گهڻائي داخلا_گهڻائي;
    بدل (SDL_Get_متن_داخلا_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        داخلا_گهڻائي = EGamepad_متن_داخلا_گهڻائي_k_EGamepad_متن_داخلا_گهڻائي_Password;
        اكسر;
    افتراضي:
        داخلا_گهڻائي = EGamepad_متن_داخلا_گهڻائي_k_EGamepad_متن_داخلا_گهڻائي_عام;
        اكسر;
    }
    EGamepad_متن_داخلا_سٽ_گهڻائي سٽ_گهڻائي;
    إذا (SDL_Get_متن_داخلا_Multiline(props)) {
        سٽ_گهڻائي = EGamepad_متن_داخلا_سٽ_گهڻائي_k_EGamepad_متن_داخلا_سٽ_گهڻائي_گڻو_سٽون;
    } وإلا {
        سٽ_گهڻائي = EGamepad_متن_داخلا_سٽ_گهڻائي_k_EGamepad_متن_داخلا_سٽ_گهڻائي_Single_سٽ;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           داخلا_گهڻائي, سٽ_گهڻائي,
           EKeyboard_Flags_Keyboard_Flag_گهٽتر, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساكن فراغ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساكن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *نتيجو = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (!نتيجو) {
        أرجع عدم;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_معلومات *ovrc = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*ovrc));
    إذا (!ovrc) {
        SDL_free(نتيجو);
        أرجع عدم;
    }
    نتيجو->اندروني = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    أرجع نتيجو;
}

ساكن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_معلومات * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    إذا (!cursor) {
        global_openvr_driver->oOverlay->سيٽ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->سيٽ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        إذا (e != EVROverlayError_VROverlayError_None) {
            أرجع OPENVR_سيٽ_Overlay_Error(e);
        }
        أرجع true;
    }

    global_openvr_driver->oOverlay->سيٽ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->اندروني;

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

    e = global_openvr_driver->oOverlay->سيٽ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سيٽ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سيٽ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سيٽ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سيٽ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سيٽ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سيٽ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سيٽ_Overlay_Error(e);
    }

    أرجع true;
}

ساكن فراغ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    إذا (cursor) {
        SDL_Cursor_معلومات *ovrc = cursor->اندروني;
        إذا (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساكن bool OPENVR_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري * دري, SDL_Surface * icon)
{
    إذا (!global_openvr_driver) {
        أرجع SDL_سيٽ_Error("OpenVR Overlay not initialized");
    }

    بنانشان texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    إذا (videodata->bIconOverridden) {
        أرجع SDL_سيٽ_Error("OpenVR Icon is overridden.");
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

    e = global_openvr_driver->oOverlay->سيٽ_Overlay_Texture(videodata->thumbID, &texture);
    إذا (e != EVROverlayError_VROverlayError_None) {
        أرجع OPENVR_سيٽ_Overlay_Error(e);
    }
    أرجع true;
}

ساكن bool OPENVR_Show_پيغام_Box(SDL_VideoDevice *_this,ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonid)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    حرف خالي_جايون = 0;
    حرف * پيغام = SDL_strdup(messageboxdata->پيغام?messageboxdata->پيغام:"");
    حرف * title = SDL_strdup(messageboxdata->پيغام?messageboxdata->پيغام:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_پيغام_Overlay(پيغام, title, ok, &خالي_جايون, &خالي_جايون, &خالي_جايون);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(پيغام);
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
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)_this->اندروني;
    بنية VREvent_t nEvent;
    إذا (videodata->overlayID) {
        طالما (videodata->oOverlay->Poll_ايندڙ_Overlay_Event(videodata->overlayID, &nEvent, حجم(nEvent))) {
            بدل (nEvent.eventType) {
            حالة EVREventType_VREvent_ButtonPress:
            حالة EVREventType_VREvent_ButtonUnpress:
                اكسر;
            حالة EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 2);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_هيٺ_ڏانهن:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 1);
                اكسر;
            حالة EVREvent_Type_VREvent_Mouse_Button_مٿي:
                OPENVR_HandleMouse(nEvent.معلومات.mouse.x, videodata->targh - nEvent.معلومات.mouse.y, nEvent.معلومات.mouse.button, 0);
                اكسر;
            حالة EVREventType_VREvent_ScrollSmooth:
            حالة EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, عدم, SDL_GLOBAL_MOUSE_ID, -nEvent.معلومات.scroll.xdelta, nEvent.معلومات.scroll.ydelta, SDL_MOUSEWHEEL_عام);
                اكسر;
            حالة EVREvent_Type_VREvent_Keyboard_Char_داخلا:
                SDL_Send_Keyboard_Unicode_ڪنجي(SDL_GetTicksNS(), nEvent.معلومات.keyboard.c_New_داخلا[0]);
                اكسر;
            حالة EVREventType_VREvent_OverlayShown:
                SDL_سيٽ_Keyboard_Focus(videodata->دري);
                SDL_Send_دري_Event(videodata->دري, SDL_EVENT_دري_RESTORED, 0, 0);
                SDL_Send_دري_Event(videodata->دري, SDL_EVENT_دري_SHOWN, 0, 0);
                اكسر;
            حالة EVREventType_VREvent_OverlayHidden:
                SDL_Send_دري_Event(videodata->دري, SDL_EVENT_دري_HIDDEN, 0, 0);
                SDL_Send_دري_Event(videodata->دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
                SDL_سيٽ_Keyboard_Focus(عدم);
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

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_WINDOWS
    SDL_رجسٽر_App(عدم, 0, عدم);
#جيڪڏهن_پورو

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (device) {
        معلومات = (بنية SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    } وإلا {
        معلومات = عدم;
    }
    إذا (!معلومات) {
#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#جيڪڏهن_پورو
        SDL_free(device);
        أرجع عدم;
    }
    device->اندروني = معلومات;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    إذا (hint) {
        معلومات->openVRLIB = SDL_ڀريو_Object(hint);
    }
    إذا (!معلومات->openVRLIB) {
        معلومات->openVRLIB = SDL_ڀريو_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    إذا (!معلومات->openVRLIB) {
        SDL_سيٽ_Error("Could not open OpenVR API Library");
        اذهب error;
    }

    معلومات->FN_VR_Init_اندروني = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_ڀريو_Function(معلومات->openVRLIB, "VR_InitInternal");
    معلومات->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_ڀريو_Function(معلومات->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    معلومات->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pch_Interface_نسخو, EVRInitError * peError))SDL_ڀريو_Function(معلومات->openVRLIB, "VR_GetGenericInterface");
    إذا (!معلومات->FN_VR_Init_اندروني || !معلومات->FN_VR_GetVRInitErrorAsEnglishDescription || !معلومات->FN_VR_GetGenericInterface) {
        اذهب error;
    }

    حرف fnname[128];
    EVRInitError e;
    معلومات->vrtoken = معلومات->FN_VR_Init_اندروني(&e, EVRApplicationType_VRApplication_Overlay);
    إذا (!معلومات->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        إذا (معلومات->FN_VR_GetVRInitErrorAsEnglishDescription != عدم)
            err = معلومات->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_سيٽ_Error("Could not generate OpenVR Context (%s)", err);
        اذهب error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_نسخو);
    معلومات->oSystem = (بنية VR_IVRSystem_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_نسخو);
    معلومات->oOverlay = (بنية VR_IVROverlay_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_نسخو);
    معلومات->o_داخلا = (بنية VR_IVRInput_Fn_جدول *)معلومات->FN_VR_GetGenericInterface(fnname, &e);

    إذا (!معلومات->oOverlay || !معلومات->oSystem || !معلومات->o_داخلا) {
        SDL_سيٽ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_نسخو, IVROverlay_نسخو, IVRInput_نسخو);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    إذا (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } وإلا {
        ثابت حرف *basepath = SDL_Get_بنياد_رستو();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    إذا (!loadpath) {
        اذهب error;
    }

    err = معلومات->o_داخلا->سيٽ_Action_Manifest_رستو(loadpath);
#جيڪڏهن_وصف_ٿيل DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#جيڪڏهن_پورو
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
        إذا(!OPENVR_تياري_Joystick_Based_On_Loaded_Action_Manifest(معلومات)) {
            اذهب error;
        }
    }

    // Setup amount of available displays
    device->انگ_displays = 0;

    // Set device free function
    device->حرر = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->سيٽ_Display_گهڻائي = OPENVR_سيٽ_Display_گهڻائي;
    device->CreateSDLWindow = OPENVR_Create_دري;
    device->سيٽ_دري_Title = OPENVR_سيٽ_دري_Title;
    device->سيٽ_دري_سائيز = OPENVR_سيٽ_دري_سائيز;
    device->Get_دري_سائيز_اندريون_Pixels = OPENVR_Get_دري_سائيز_اندريون_Pixels;
    device->Show_دري = OPENVR_Show_دري;
    device->Hide_دري = OPENVR_Hide_دري;
    device->Destroy_دري = OPENVR_Destroy_دري;
    device->Show_پيغام_Box = OPENVR_Show_پيغام_Box;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_WGL
    device->GL_ڀريو_Library = OPENVR_GL_ڀريو_Library;
    device->GL_Get_Proc_پتو = OPENVR_GL_Get_Proc_پتو;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = OPENVR_GL_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = OPENVR_GL_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = OPENVR_GL_مٽا_سٽا_دري;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#وإلا
#غلطي Needs وڌيڪ work منزل support EGL
#جيڪڏهن_پورو
#وإلا
    device->GL_ڀريو_Library = OVR_EGL_ڀريو_Library;
    device->GL_Get_Proc_پتو = OVR_EGL_Get_Proc_پتو;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = OVR_EGL_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = OVR_EGL_Get_مٽا_سٽا_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_مٽا_سٽا_دري = OPENVR_GL_مٽا_سٽا_دري;
#جيڪڏهن_پورو

#إذا defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_ڀريو_Library = WIN_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#وإلا
    device->Vulkan_ڀريو_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#جيڪڏهن_پورو

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->سيٽ_دري_Icon = OPENVR_سيٽ_دري_Icon;

    أرجع device;

error:
    OPENVR_Destroy(device);
    أرجع عدم;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, عدم, false
};

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_OPENVR

