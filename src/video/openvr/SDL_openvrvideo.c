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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENVR

#اگر 0
#تعریف_کرو DEBUG_OPENVR
#اگر_ختم

#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../SDL_egl_c.h"
#شامل "SDL_openvrvideo.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#شامل <SDL3/SDL_opengl.h>
#ورنہ
// Currently only EGL, not OpenGL, is supported on other platforms
#شامل <SDL3/SDL_opengles2.h>
#شامل <SDL3/SDL_opengles2_gl2.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#شامل "../windows/SDL_windowsopengl.h"
#شامل "../windows/SDL_windowsvulkan.h"

#تعریف_کرو DEFAULT_OPENGL "OPENGL32.DLL"

ساکن bool OPENVR_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ);
ساکن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

ساخت SDL_GLContextState
{
    HGLRC hglrc;
};
#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS



#اگر_تعریف_شدہ SDL_PLATFORM_WINDOWS
#تعریف_کرو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#ورنہ
#تعریف_کرو SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#اگر_ختم

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#تعریف_کرو MARKER_ID 0
#تعریف_کرو MARKER_STR "vr-marker,frame_end,type,application"

#تعریف_منسوخ EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_ڈیٹا * global_openvr_driver;

ساکن خالی InitializeMouseFunctions(خالی);

ساخت SDL_Cursor_ڈیٹا
{
    غیرعلامتی texture_id_handle;
    صحیح hot_x, hot_y;
    صحیح w, h;
};

// GL Extensions for functions we will be using.
ساکن خالی (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ساکن خالی (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ساکن خالی (APIENTRY *ov_glBindFramebuffer)(GLenum ہدف, GLuint framebuffer);
ساکن خالی (APIENTRY *ov_glBindRenderbuffer)(GLenum ہدف, GLuint renderbuffer);
ساکن خالی (APIENTRY *ov_glRenderbufferStorage)(GLenum ہدف, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
ساکن خالی (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum ہدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ساکن خالی (APIENTRY *ov_glFramebufferTexture2D)(GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ساکن GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_حالت)(GLuint framebuffer, GLenum ہدف);
ساکن GLenum (APIENTRY *ov_glGetError)(خالی);
ساکن خالی (APIENTRY *ov_glFlush)(خالی);
ساکن خالی (APIENTRY *ov_gl_اختتام)(خالی);
ساکن خالی (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ساکن خالی (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ساکن خالی (APIENTRY *ov_glTexParameterf)(GLenum ہدف, GLenum pname, GLfloat param);
ساکن خالی (APIENTRY *ov_glTexParameteri)(GLenum ہدف, GLenum pname, GLenum param);
ساکن خالی (APIENTRY *ov_glTexImage2D)(GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLenum format, GLenum type, ثابت خالی *ڈیٹا);
ساکن خالی (APIENTRY *ov_glBindTexture)(GLenum ہدف, GLuint texture);
ساکن خالی (APIENTRY *ov_glDrawBuffers)(GLsizei n, ثابت GLenum *bufs);
ساکن خالی (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * ڈیٹا);
ساکن ثابت GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint اشاریہ);
ساکن خالی (APIENTRY *ov_glClear)(GLbitfield نقاب);
ساکن خالی (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ساکن خالی (APIENTRY *ov_gl_Color_نقاب)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ساکن خالی (APIENTRY *ov_gl_Debug_پیغام_داخل_کرو)(GLenum ماخذ, GLenum type, GLuint id, GLenum severity, GLsizei لمبائی, ثابت حرف *پیغام);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
ساکن PROC (*ov_wgl_Get_Proc_پتہ)(LPCSTR);
ساکن HGLRC (*ov_wglCreateContext)(HDC);
ساکن BOOL (*ov_wglDeleteContext)(HGLRC);
ساکن BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#اگر_ختم


#تعریف_کرو OPENVR_DEFAULT_چوڑائی 1920
#تعریف_کرو OPENVR_DEFAULT_اونچائی 1080

#تعریف_کرو OPENVR_تیاری_Proc(proc) { proc = (خالی *)SDL_GL_Get_Proc_پتہ((#proc)+3); اگر (!proc) { failed_extension = (#proc)+3; } }

ساکن bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    اگر (!ov_glGetError) {
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
        OPENVR_تیاری_Proc(ov_gl_اختتام);
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
        OPENVR_تیاری_Proc(ov_gl_Debug_پیغام_داخل_کرو);
        اگر (failed_extension) {
            واپس SDL_سیٹ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    واپس true;
}

ساکن bool OPENVR_سیٹ_Overlay_Error(EVROverlayError e)
{
    انتخاب (e) {
#تعریف_کرو CASE(X) حالت EVROverlayError_VROverlayError_##X: واپس SDL_سیٹ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_حد_بندی_Exceeded);
    CASE(WrongVisibilityType);
    CASE(کلید_Too_Long);
    CASE(NameTooLong);
    CASE(کلید_اندر_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_مقصد_بھرو_File);
    CASE(Keyboard_Already_اندر_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_نقاب_Primitives);
    CASE(Bad_نقاب_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_تالا_استعداد_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_برآمد);
#تعریف_منسوخ CASE
    طےشدہ:
        واپس SDL_سیٹ_Error("Unknown VROverlayError %d", e);
    }
}

ساکن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

ساکن bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    ثابت حرف * hint_چوڑائی = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ثابت حرف * hint_اونچائی = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ثابت حرف * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    صحیح چوڑائی = hint_چوڑائی ? SDL_atoi(hint_چوڑائی) : 0;
    صحیح اونچائی = hint_اونچائی ? SDL_atoi(hint_اونچائی) : 0;
    صحیح fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_منوال.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_منوال.w = OPENVR_DEFAULT_چوڑائی;
    display.desktop_منوال.h = OPENVR_DEFAULT_اونچائی;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    اگر (اونچائی > 0 && چوڑائی > 0) {
        display.desktop_منوال.w = چوڑائی;
        display.desktop_منوال.h = اونچائی;
    }
    اگر (fps) {
        display.desktop_منوال.refresh_شرح = fps;
    } ورنہ {
        display.desktop_منوال.refresh_شرح = ڈیٹا->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_اشاریہ_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (حرف *)"OpenVRDisplay";
    SDL_جوڑو_Video_Display(&display, false);

    واپس true;
}

ساکن خالی OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ساکن خالی OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;

#اگر_تعریف_شدہ SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#اگر_ختم

    اگر (ڈیٹا) {
        اگر (ڈیٹا->openVRLIB) {
            SDL_UnloadObject(ڈیٹا->openVRLIB);
        }
    }
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    صحیح w = surf->w;
    صحیح h = surf->h;
    صحیح pitch = surf->pitch;
    صحیح x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    برائے(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        برائے(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    واپس pxd;
}

ساکن bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    اگر (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_چوڑائی;
        videodata->targh = OPENVR_DEFAULT_اونچائی;
    }

    اگر (videodata->targh != videodata->آخری_targh
     || videodata->targw != videodata->آخری_targw) {

        ساخت HmdVector2_t ms;
        صحیح حالت_2;

        اگر (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_گہرائی_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_گہرائی_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_قریب_ترین);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_قریب_ترین);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        حالت_2 = ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER);
        اگر (حالت_2 != GL_FRAMEBUFFER_COMPLETE) {
            واپس SDL_سیٹ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (اعشاری)videodata->targw;
        ms.v[1] = (اعشاری)videodata->targh;
        videodata->oOverlay->سیٹ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->آخری_targh = videodata->targh;
        videodata->آخری_targw = videodata->targw;
    }
    واپس true;
}

ساکن bool OPENVR_VirtualControllerRumble(خالی *userdata, Uint16 کم_frequency_rumble, Uint16 بلند_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)userdata;

    ثابت اعشاری k_flIntensity = 320.f; // Maximum frequency
    اعشاری fl_بایاں_Frequency = (اعشاری)کم_frequency_rumble * k_flIntensity / 65535.f;
    اعشاری fl_دایاں_Frequency = (اعشاری)بلند_frequency_rumble * k_flIntensity / 65535.f;
    اعشاری flDurationSeconds = 2.f;
    اعشاری flAmplitude = 1.f;

    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[0], 0, flDurationSeconds, fl_بایاں_Frequency, flAmplitude, 0);
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[1], 0, flDurationSeconds, fl_دایاں_Frequency, flAmplitude, 0);

    واپس true;
}

ساکن bool OPENVR_VirtualControllerRumbleTriggers(خالی *userdata, Uint16 بایاں_rumble, Uint16 دایاں_rumble)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)userdata;
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[0], 0, 0.1f, بایاں_rumble, 1.0, 0);
    videodata->o_داخلہ->TriggerHapticVibrationAction(videodata->داخلہ_action_handles_haptics[1], 0, 0.1f, دایاں_rumble, 1.0, 0);
    واپس true;
}

ساکن خالی OPENVR_VirtualControllerUpdate(خالی *userdata)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    داخلہ_Digital_Action_ڈیٹا_t digital_داخلہ_action;
    داخلہ_Analog_Action_ڈیٹا_t analog_داخلہ_action;
    EVRInputError e;
#اگر_تعریف_شدہ DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#اگر_ختم
    VRActive_Action_سیٹ_t action_سیٹ = { 0 };
    action_سیٹ.ul_Action_سیٹ = videodata->داخلہ_action_سیٹ;
    e = videodata->o_داخلہ->UpdateActionState(&action_سیٹ, حجم(action_سیٹ), 1);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#اگر_ختم
        واپس;
    }

    برائے (صحیح d = 0; d < videodata->داخلہ_action_handles_buttons_گنتی; d++)
    {
        اگر (videodata->داخلہ_action_handles_buttons[d] == k_ulInvalidActionHandle)
            جاری;
        e = videodata->o_داخلہ->Get_Digital_Action_ڈیٹا(videodata->داخلہ_action_handles_buttons[d], &digital_داخلہ_action, حجم(digital_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
        اگر (e)
        {
#اگر_تعریف_شدہ DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#اگر_ختم
            واپس;
        }
        SDL_سیٹ_Joystick_Virtual_Button(joystick, d, digital_داخلہ_action.bState);
#اگر_تعریف_شدہ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#اگر_ختم
    }

    // Left Stick
    e = videodata->o_داخلہ->Get_Analog_Action_ڈیٹا(videodata->داخلہ_action_handles_axes[0], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#اگر_ختم
        واپس;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_داخلہ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_داخلہ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_داخلہ->Get_Analog_Action_ڈیٹا(videodata->داخلہ_action_handles_axes[1], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#اگر_ختم
        واپس;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_داخلہ_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_داخلہ_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_داخلہ->Get_Analog_Action_ڈیٹا(videodata->داخلہ_action_handles_axes[2], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#اگر_ختم
        واپس;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_بایاں_TRIGGER, (Sint16)((analog_داخلہ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_داخلہ->Get_Analog_Action_ڈیٹا(videodata->داخلہ_action_handles_axes[3], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#اگر_ختم
        واپس;
    }
    SDL_سیٹ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_دایاں_TRIGGER, (Sint16)((analog_داخلہ_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#اگر 0
    برائے (a = 0; a < videodata->داخلہ_action_handles_axes_گنتی; a++)
    {
        اعشاری xval = 0.0f;
        e = videodata->o_داخلہ->Get_Analog_Action_ڈیٹا(videodata->داخلہ_action_handles_axes[a], &analog_داخلہ_action, حجم(analog_داخلہ_action), k_ul_Invalid_داخلہ_قدر_Handle);
        اگر (e) جاؤ updatefail;
        xval = analog_داخلہ_action.x;
        اگر (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        اگر (a == SDL_GAMEPAD_AXIS_بایاں_TRIGGER || a == SDL_GAMEPAD_AXIS_دایاں_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_سیٹ_Joystick_Virtual_Axis(joystick, a, xval);
#اگر_تعریف_شدہ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#اگر_ختم
    }
#اگر_ختم
#اگر_تعریف_شدہ DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#اگر_ختم
    واپس;
}

ساکن bool OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_ڈیٹا * videodata)
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

    اگر ((e = videodata->o_داخلہ->Get_Action_سیٹ_Handle("/actions/virtualgamepad", &videodata->داخلہ_action_سیٹ)) != EVRInputError_VRInputError_None)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#اگر_ختم
        واپس SDL_سیٹ_Error("Failed to get action set handle");
    }

    videodata->داخلہ_action_handles_buttons_گنتی = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->داخلہ_action_handles_buttons = SDL_malloc(videodata->داخلہ_action_handles_buttons_گنتی * حجم(VRActionHandle_t));

    برائے (صحیح i = 0; i < videodata->داخلہ_action_handles_buttons_گنتی; i++)
    {
        e = videodata->o_داخلہ->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->داخلہ_action_handles_buttons[i]);
        اگر (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            واپس SDL_سیٹ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->داخلہ_action_handles_axes_گنتی = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->داخلہ_action_handles_axes = SDL_malloc(videodata->داخلہ_action_handles_axes_گنتی * حجم(VRActionHandle_t));

    برائے (صحیح i = 0; i < videodata->داخلہ_action_handles_axes_گنتی; i++)
    {
        e = videodata->o_داخلہ->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->داخلہ_action_handles_axes[i]);
        اگر (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            واپس SDL_سیٹ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_داخلہ->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->داخلہ_action_handles_haptics[0]);
    e |= videodata->o_داخلہ->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->داخلہ_action_handles_haptics[1]);
    اگر (e)
    {
#اگر_تعریف_شدہ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#اگر_ختم
        واپس SDL_سیٹ_Error("ERROR: Failed to get haptics action");
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

    اگر (!virtual_id) {
        واپس SDL_سیٹ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    اگر (!videodata->virtual_joystick) {
        واپس SDL_سیٹ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#اگر_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->داخلہ_action_handles_buttons_گنتی, videodata->داخلہ_action_handles_axes_گنتی);
#اگر_ختم

    واپس true;
}

ساکن bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    // Wait til here, to make sure we have our context setup correctly.
    اگر (!OPENVR_InitExtensions(_this)) {
        واپس false;
    }

    // Generate the overlay.
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        حرف * cursorname = 0;
        اگر (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        اگر (!videodata->sOverlayName) {
            واپس false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        اگر (!cursorname) {
            واپس false;
        }

        EVROverlayError نتیجہ = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            کھڑکی->title, &videodata->overlayID, &videodata->thumbID);
        اگر (نتیجہ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            واپس SDL_سیٹ_Error("Could not create dashboard overlay (%d)", نتیجہ );
        }
        نتیجہ = videodata->oOverlay->CreateOverlay(cursorname, کھڑکی->title, &videodata->cursorID);
        اگر (نتیجہ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            واپس SDL_سیٹ_Error("Could not create cursor overlay (%d)", نتیجہ );
        }
        SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
        SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_OPENVR_OVERLAY_ID_نمبر, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ثابت حرف *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        اگر (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } ورنہ {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#اگر 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#اگر_ختم
        }

        برائے (صحیح i = 0; i < حجم(overlay_flags) * 8; ++i) {
            اگر (overlay_flags & (1 << i)) {
                videodata->oOverlay->سیٹ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        اعشاری f_چوڑائی = hint ? (اعشاری)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->سیٹ_Overlay_چوڑائی_اندر_Meters(videodata->overlayID, f_چوڑائی);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        اعشاری f_Cursor_چوڑائی = hint ? (اعشاری)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->سیٹ_Overlay_چوڑائی_اندر_Meters(videodata->cursorID, f_Cursor_چوڑائی * 0.5f);
    }
    {
        ثابت حرف * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        اگر (hint) {
            حرف * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->سیٹ_Overlay_From_File(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            اگر (err == EVROverlayError_VROverlayError_None) {
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

    اگر (!OPENVR_CheckRenderbuffer(_this)) {
        واپس false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->سیٹ_Overlay_Name(videodata->overlayID, کھڑکی->title);

    videodata->bDidCreateOverlay = true;
    videodata->کھڑکی = کھڑکی;

    واپس true;
}


ساکن bool OPENVR_تیاری_چوکھٹا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ساکن ثابت GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_بفر_rendering = true;

#اگر_تعریف_شدہ DEBUG_OPENVR
    {
        صحیح error = ov_glGetError();
        اگر (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
    }
#اگر_ختم

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    اگر (!(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_نقاب(false, false, false, true);
        ov_glClear(GL_COLOR_بفر_ثنائی_ہندسہ);
        ov_gl_Color_نقاب(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    واپس true;
}

ساکن bool OPENVR_Release_چوکھٹا(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    اگر (!ov_glGetError) {
        واپس true;
    }

    اگر (!videodata->is_بفر_rendering) {
        واپس true;
    }

#اگر_تعریف_شدہ DEBUG_OPENVR
    {
        صحیح error = ov_glGetError();
        اگر (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_حالت(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#اگر_ختم

    videodata->is_بفر_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    اگر (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->آخری_targh &&
        videodata->targw == videodata->آخری_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ساخت Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (خالی *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->سیٹ_Overlay_Texture(videodata->overlayID, &tex);
    }

    اگر (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    اگر (videodata->renderdoc_debugmarker_چوکھٹا_انتہا) {
        ov_gl_Debug_پیغام_داخل_کرو(GL_DEBUG_ماخذ_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    واپس OPENVR_CheckRenderbuffer(_this);
}

ساکن خالی OPENVR_HandleResize(SDL_VideoDevice *_this, صحیح w, صحیح h)
{
    SDL_Video_ڈیٹا *ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ڈیٹا->targw = w;
    ڈیٹا->targh = h;
}

ساکن bool OPENVR_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    واپس true;
}


#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
ساکن LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam)
{
    انتخاب (پیغام_2) {
    حالت WM_DESTROY:
        واپس 0;
    }
    واپس Def_کھڑکی_Proc(hwnd, پیغام_2, wParam, lParam);
}

ساکن bool OPENVR_GL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    اگر (راستہ == تہی) {
        راستہ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    اگر (راستہ == تہی) {
        راستہ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_بھرو_Object(راستہ);
    اگر (!_this->gl_config.dll_handle) {
        واپس false;
    }
    SDL_strlcpy(_this->gl_config.driver_راستہ, راستہ,
                 SDL_arraysize(_this->gl_config.driver_راستہ));

    // Allocate OpenGL memory
    _this->gl_ڈیٹا = (ساخت SDL_GLDriver_ڈیٹا *)SDL_calloc(1, حجم(ساخت SDL_GLDriver_ڈیٹا));
    اگر (!_this->gl_ڈیٹا) {
        واپس false;
    }
    _this->gl_config.driver_loaded = true;

    واپس true;
}

ساکن SDL_Function_اشارہ_گر OPENVR_GL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر نتیجہ = تہی;
    اگر (ov_wgl_Get_Proc_پتہ) {
        نتیجہ = (SDL_Function_اشارہ_گر)ov_wgl_Get_Proc_پتہ(proc);
        اگر (نتیجہ) {
            واپس نتیجہ;
        }
    }

    واپس SDL_بھرو_Function(_this->gl_config.dll_handle, proc);
}

ساکن خالی OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ساکن SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    GLint عدد_Extensions;
    صحیح i;
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(تہی);
        wnd.hIcon = بھرو_Icon(تہی, IDI_APPLICATION);
        wnd.hCursor = بھرو_Cursor(تہی, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = تہی;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        رجسٹر_Class_A(&wnd);
        hwnd = Create_کھڑکی_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, تہی, تہی, GetModuleHandle(تہی), تہی);

        پیغام_3 پیغام_2;
        جب (Peek_پیغام(&پیغام_2, تہی, 0, 0, PM_REMOVE)) {
            Translate_پیغام(&پیغام_2);
            Dispatch_پیغام(&پیغام_2);
        }

        videodata->hdc = GetDC(hwnd);

        ساکن  PIXELFORMATDESCRIPTOR pfd =
        {
            حجم(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_مقصد_کھڑکی |
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
        اگر (!سیٹ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_سیٹ_Error( "Could not set pixel format" );
            واپس تہی;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        اگر (!opengl) {
            SDL_سیٹ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            واپس تہی;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_پتہ(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_پتہ(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_پتہ = (PROC(*)(LPCSTR))Get_Proc_پتہ(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_پتہ(opengl, "wglDeleteContext");
        اگر (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_سیٹ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            واپس تہی;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        اگر (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_سیٹ_Error("Could not make current OpenGL context.");
            واپس تہی;
        }
    }

    i = OPENVR_InitExtensions(_this);
    اگر (i == 0) {
        واپس تہی;
    }

    videodata->renderdoc_debugmarker_چوکھٹا_انتہا = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    برائے (i = 0; i < عدد_Extensions; i++) {
        ثابت حرف *ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        اگر (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#اگر_تعریف_شدہ DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#اگر_ختم
            videodata->renderdoc_debugmarker_چوکھٹا_انتہا = true;
        }
    }

    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            واپس تہی;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکھٹا(_this, کھڑکی);

    SDL_GLContext نتیجہ = SDL_malloc(حجم(ساخت SDL_GLContextState));
    اگر (!نتیجہ) {
        واپس تہی;
    }
    نتیجہ->hglrc = videodata->hglrc;
    واپس نتیجہ;
}

ساکن bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *wnd, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    واپس true;
}

ساکن bool OPENVR_GL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    videodata->تبادلہ_interval = interval;
    واپس true;
}

ساکن bool OPENVR_GL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *تبادلہ_Interval)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (تبادلہ_Interval)
        *تبادلہ_Interval = videodata->تبادلہ_interval;
    ورنہ
        واپس SDL_سیٹ_Error("OPENVR: null passed in for GetSwapInterval");
    واپس true;
}

ساکن bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ov_wglMakeCurrent(videodata->hdc, تہی);
    ov_wglDeleteContext(videodata->hglrc);
    واپس true;
}


#ورنہ

ساکن EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_نسخہ, 2,
    EGL_NONE
};

ساکن bool SDL_EGL_Init_اندرونی(SDL_Video_ڈیٹا * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=تہی;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#اگر_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#اگر_ختم

    اگر (vd->eglDpy == 0) {
        واپس SDL_سیٹ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    اگر (!b) {
        واپس SDL_سیٹ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#اگر_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#اگر_ختم

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#اگر_تعریف_شدہ DEBUG_OPENVR
    {
        صحیح err = eglGetError();
        اگر (err != EGL_SUCCESS) {
            واپس SDL_سیٹ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#اگر_ختم

    اگر (!vd->eglCtx) {
        واپس SDL_سیٹ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    واپس true;
}

// Linux, EGL, etc.
ساکن bool OVR_EGL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ)
{
    واپس SDL_EGL_بھرو_Library(_this, راستہ, EGL_DEFAULT_DISPLAY);
}

ساکن SDL_Function_اشارہ_گر OVR_EGL_Get_Proc_پتہ(SDL_VideoDevice *_this, ثابت حرف *proc)
{
    واپس SDL_EGL_Get_Proc_پتہ(proc);
}
ساکن خالی OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ساکن SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    GLint عدد_Extensions;
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (!videodata->eglCtx) {
        اگر (!SDL_EGL_Init_اندرونی(videodata)) {
            واپس تہی;
        }
    }

    اگر (!OPENVR_InitExtensions(_this)) {
        واپس تہی;
    }

    videodata->renderdoc_debugmarker_چوکھٹا_انتہا = false;

    ov_glGetIntegerv(GL_عدد_EXTENSIONS, &عدد_Extensions);
    برائے(صحیح i = 0; i < عدد_Extensions; i++) {
        ثابت حرف * ccc = (ثابت حرف *)ov_glGetStringi(GL_EXTENSIONS, i);
        اگر (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#اگر_تعریف_شدہ DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#اگر_ختم
           videodata->renderdoc_debugmarker_چوکھٹا_انتہا = true;
        }
    }

    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            واپس تہی;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_تیاری_چوکھٹا(_this, کھڑکی);

    واپس videodata->eglCtx;
}

ساکن bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی * wnd, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    واپس true;
}

ساکن bool OVR_EGL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    videodata->تبادلہ_interval = interval;
    واپس true;
}

ساکن bool OVR_EGL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح * تبادلہ_Interval)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (تبادلہ_Interval)
        *تبادلہ_Interval = videodata->تبادلہ_interval;
    ورنہ
        واپس SDL_سیٹ_Error("OPENVR: null passed in for GetSwapInterval");
    واپس true;
}

ساکن bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    واپس true;
}

#اگر_ختم

ساکن bool OPENVR_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    // Allocate window internal data
    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (ڈیٹا == تہی) {
        واپس SDL_برآمد_کا_حافظہ();
    }

    کھڑکی->max_w = 4096;
    کھڑکی->max_h = 4096;
    کھڑکی->min_w = 1;
    کھڑکی->min_h = 1;

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = ڈیٹا;
    واپس true;
}


ساکن خالی OPENVR_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    ڈیٹا = کھڑکی->اندرونی_2;
    SDL_free(ڈیٹا);
    کھڑکی->اندرونی_2 = تہی;
}

ساکن خالی OPENVR_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا * ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (ڈیٹا->bDidCreateOverlay) {
        ڈیٹا->oOverlay->سیٹ_Overlay_Name(ڈیٹا->overlayID, کھڑکی->title);
    }
}

ساکن خالی OPENVR_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    اگر (کھڑکی->pending.w != کھڑکی->w) {
        کھڑکی->w = کھڑکی->pending.w;
    }

    اگر (کھڑکی->pending.h != کھڑکی->h) {
        کھڑکی->h = کھڑکی->pending.h;
    }

    اگر (ڈیٹا->targh != کھڑکی->h || ڈیٹا->targw != کھڑکی->w) {
        OPENVR_HandleResize(_this, کھڑکی->w, کھڑکی->h);
    }

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->w, کھڑکی->h);
}

ساکن خالی OPENVR_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    SDL_Video_ڈیٹا *ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    *w = ڈیٹا->targw;
    *h = ڈیٹا->targh;
}

ساکن خالی OPENVR_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (ڈیٹا->targh != کھڑکی->h || ڈیٹا->targw != کھڑکی->w) {
        OPENVR_HandleResize(_this, کھڑکی->w, کھڑکی->h);
    }

    ڈیٹا->oOverlay->ShowDashboard(ڈیٹا->sOverlayName);

    کھڑکی->flags |= (SDL_کھڑکی_داخلہ_FOCUS | SDL_کھڑکی_MOUSE_FOCUS);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
}

ساکن خالی OPENVR_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس;
}

ساکن bool OPENVR_GL_تبادلہ_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    اگر (!videodata->bDidCreateOverlay) {
        اگر (!OPENVR_InitializeOverlay(_this, کھڑکی)) {
            واپس false;
        }
    }

    اگر (!OPENVR_Release_چوکھٹا(_this)) {
        واپس false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    اگر (videodata->تبادلہ_interval != 0) {
        videodata->oOverlay->Wait_چوکھٹا_Sync(100);
    }

    اگر (!OPENVR_تیاری_چوکھٹا(_this, کھڑکی)) {
        واپس false;
    }

    واپس true;
}

ساکن Uint8 OPENVR_MapMouseButton(صحیح btn)
{
    اگر (btn == EVRMouse_Button_VRMouse_Button_دایاں) {
        واپس SDL_BUTTON_دایاں;
    } ورنہ اگر (btn == EVRMouse_Button_VRMouse_Button_درمیان) {
        واپس SDL_BUTTON_درمیان;
    } ورنہ {
        واپس SDL_BUTTON_بایاں;
    }
}

ساکن خالی OPENVR_HandleMouse(اعشاری x, اعشاری y, صحیح btn, صحیح evt)
{
    اگر (evt == 2) {
        SDL_SendMouseMotion(0, تہی, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } ورنہ {
        ثابت Uint8 button = OPENVR_MapMouseButton(btn);
        ثابت bool نیچے_کو = (evt != 0);
        SDL_SendMouseButton(0, تہی, SDL_GLOBAL_MOUSE_ID, button, نیچے_کو);
    }
}


ساکن bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    واپس true;
}

ساکن خالی OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        واپس;
    }
    EGamepad_متن_داخلہ_منوال داخلہ_منوال;
    انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        داخلہ_منوال = EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_Password;
        توڑو;
    طےشدہ:
        داخلہ_منوال = EGamepad_متن_داخلہ_منوال_k_EGamepad_متن_داخلہ_منوال_معمول;
        توڑو;
    }
    EGamepad_متن_داخلہ_سطر_منوال سطر_منوال;
    اگر (SDL_Get_متن_داخلہ_Multiline(props)) {
        سطر_منوال = EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_مضرب_سطریں;
    } ورنہ {
        سطر_منوال = EGamepad_متن_داخلہ_سطر_منوال_k_EGamepad_متن_داخلہ_سطر_منوال_Single_سطر;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           داخلہ_منوال, سطر_منوال,
           EKeyboard_Flags_Keyboard_Flag_اقل, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ساکن خالی OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ساکن SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor *نتیجہ = SDL_calloc(1, حجم(SDL_Cursor));
    اگر (!نتیجہ) {
        واپس تہی;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_ڈیٹا *ovrc = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*ovrc));
    اگر (!ovrc) {
        SDL_free(نتیجہ);
        واپس تہی;
    }
    نتیجہ->اندرونی_2 = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    واپس نتیجہ;
}

ساکن bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ڈیٹا * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    اگر (!cursor) {
        global_openvr_driver->oOverlay->سیٹ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->سیٹ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        اگر (e != EVROverlayError_VROverlayError_None) {
            واپس OPENVR_سیٹ_Overlay_Error(e);
        }
        واپس true;
    }

    global_openvr_driver->oOverlay->سیٹ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->اندرونی_2;

    اگر (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        واپس true;
    }

    hotspot.v[0] = (اعشاری)ovrc->hot_x / (اعشاری)ovrc->w;
    hotspot.v[1] = (اعشاری)ovrc->hot_y / (اعشاری)ovrc->h;

    texture.handle = (خالی *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    اگر (e != EVROverlayError_VROverlayError_None) {
        واپس OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    اگر (e != EVROverlayError_VROverlayError_None) {
        واپس OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    اگر (e != EVROverlayError_VROverlayError_None) {
        واپس OPENVR_سیٹ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    اگر (e != EVROverlayError_VROverlayError_None) {
        واپس OPENVR_سیٹ_Overlay_Error(e);
    }

    واپس true;
}

ساکن خالی OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ovrc = cursor->اندرونی_2;
        اگر (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ساکن bool OPENVR_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_Surface * icon)
{
    اگر (!global_openvr_driver) {
        واپس SDL_سیٹ_Error("OpenVR Overlay not initialized");
    }

    غیرعلامتی texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    اگر (videodata->bIconOverridden) {
        واپس SDL_سیٹ_Error("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (خالی *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->سیٹ_Overlay_Texture(videodata->thumbID, &texture);
    اگر (e != EVROverlayError_VROverlayError_None) {
        واپس OPENVR_سیٹ_Overlay_Error(e);
    }
    واپس true;
}

ساکن bool OPENVR_Show_پیغام_Box(SDL_VideoDevice *_this,ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonid)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    حرف خالی_خانے = 0;
    حرف * پیغام = SDL_strdup(messageboxdata->پیغام?messageboxdata->پیغام:"");
    حرف * title = SDL_strdup(messageboxdata->پیغام?messageboxdata->پیغام:"");
    حرف * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_پیغام_Overlay(پیغام, title, ok, &خالی_خانے, &خالی_خانے, &خالی_خانے);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(پیغام);
    واپس true;
}

ساکن خالی InitializeMouseFunctions(خالی)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ساکن خالی OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)_this->اندرونی_2;
    ساخت VREvent_t nEvent;
    اگر (videodata->overlayID) {
        جب (videodata->oOverlay->Poll_اگلا_Overlay_Event(videodata->overlayID, &nEvent, حجم(nEvent))) {
            انتخاب (nEvent.eventType) {
            حالت EVREventType_VREvent_ButtonPress:
            حالت EVREventType_VREvent_ButtonUnpress:
                توڑو;
            حالت EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.ڈیٹا.mouse.x, videodata->targh - nEvent.ڈیٹا.mouse.y, nEvent.ڈیٹا.mouse.button, 2);
                توڑو;
            حالت EVREvent_Type_VREvent_Mouse_Button_نیچے_کو:
                OPENVR_HandleMouse(nEvent.ڈیٹا.mouse.x, videodata->targh - nEvent.ڈیٹا.mouse.y, nEvent.ڈیٹا.mouse.button, 1);
                توڑو;
            حالت EVREvent_Type_VREvent_Mouse_Button_اوپر:
                OPENVR_HandleMouse(nEvent.ڈیٹا.mouse.x, videodata->targh - nEvent.ڈیٹا.mouse.y, nEvent.ڈیٹا.mouse.button, 0);
                توڑو;
            حالت EVREventType_VREvent_ScrollSmooth:
            حالت EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, تہی, SDL_GLOBAL_MOUSE_ID, -nEvent.ڈیٹا.scroll.xdelta, nEvent.ڈیٹا.scroll.ydelta, SDL_MOUSEWHEEL_معمول);
                توڑو;
            حالت EVREvent_Type_VREvent_Keyboard_Char_داخلہ:
                SDL_Send_Keyboard_Unicode_کلید(SDL_GetTicksNS(), nEvent.ڈیٹا.keyboard.c_New_داخلہ[0]);
                توڑو;
            حالت EVREventType_VREvent_OverlayShown:
                SDL_سیٹ_Keyboard_Focus(videodata->کھڑکی);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
                توڑو;
            حالت EVREventType_VREvent_OverlayHidden:
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
                SDL_Send_کھڑکی_Event(videodata->کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
                SDL_سیٹ_Keyboard_Focus(تہی);
                توڑو;
            حالت EVREventType_VREvent_OverlayClosed:
            حالت EVREventType_VREvent_Quit:
                SDL_SendQuit();
                توڑو;
            }
        }
    }
}


ساکن SDL_VideoDevice *OPENVR_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;
    ثابت حرف *hint;

#اگر_تعریف_شدہ SDL_PLATFORM_WINDOWS
    SDL_رجسٹر_App(تہی, 0, تہی);
#اگر_ختم

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (device) {
        ڈیٹا = (ساخت SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    } ورنہ {
        ڈیٹا = تہی;
    }
    اگر (!ڈیٹا) {
#اگر_تعریف_شدہ SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#اگر_ختم
        SDL_free(device);
        واپس تہی;
    }
    device->اندرونی_2 = ڈیٹا;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    اگر (hint) {
        ڈیٹا->openVRLIB = SDL_بھرو_Object(hint);
    }
    اگر (!ڈیٹا->openVRLIB) {
        ڈیٹا->openVRLIB = SDL_بھرو_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    اگر (!ڈیٹا->openVRLIB) {
        SDL_سیٹ_Error("Could not open OpenVR API Library");
        جاؤ error;
    }

    ڈیٹا->FN_VR_Init_اندرونی = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_بھرو_Function(ڈیٹا->openVRLIB, "VR_InitInternal");
    ڈیٹا->FN_VR_GetVRInitErrorAsEnglishDescription = (ثابت حرف *(*)(EVRInitError error))SDL_بھرو_Function(ڈیٹا->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    ڈیٹا->FN_VR_GetGenericInterface = (intptr_t (*)(ثابت حرف *pch_Interface_نسخہ, EVRInitError * peError))SDL_بھرو_Function(ڈیٹا->openVRLIB, "VR_GetGenericInterface");
    اگر (!ڈیٹا->FN_VR_Init_اندرونی || !ڈیٹا->FN_VR_GetVRInitErrorAsEnglishDescription || !ڈیٹا->FN_VR_GetGenericInterface) {
        جاؤ error;
    }

    حرف fnname[128];
    EVRInitError e;
    ڈیٹا->vrtoken = ڈیٹا->FN_VR_Init_اندرونی(&e, EVRApplicationType_VRApplication_Overlay);
    اگر (!ڈیٹا->vrtoken) {
        ثابت حرف *err = "Can't get english description";
        اگر (ڈیٹا->FN_VR_GetVRInitErrorAsEnglishDescription != تہی)
            err = ڈیٹا->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_سیٹ_Error("Could not generate OpenVR Context (%s)", err);
        جاؤ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_نسخہ);
    ڈیٹا->oSystem = (ساخت VR_IVRSystem_Fn_جدول *)ڈیٹا->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_نسخہ);
    ڈیٹا->oOverlay = (ساخت VR_IVROverlay_Fn_جدول *)ڈیٹا->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_نسخہ);
    ڈیٹا->o_داخلہ = (ساخت VR_IVRInput_Fn_جدول *)ڈیٹا->FN_VR_GetGenericInterface(fnname, &e);

    اگر (!ڈیٹا->oOverlay || !ڈیٹا->oSystem || !ڈیٹا->o_داخلہ) {
        SDL_سیٹ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_نسخہ, IVROverlay_نسخہ, IVRInput_نسخہ);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    حرف *loadpath = 0;
    EVRInputError err;

    اگر (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } ورنہ {
        ثابت حرف *basepath = SDL_Get_بنیاد_راستہ();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    اگر (!loadpath) {
        جاؤ error;
    }

    err = ڈیٹا->o_داخلہ->سیٹ_Action_Manifest_راستہ(loadpath);
#اگر_تعریف_شدہ DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#اگر_ختم
    SDL_free(loadpath);
    اگر (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        اگر (hint) {
            جاؤ error;
        }
    } ورنہ {
        اگر(!OPENVR_تیاری_Joystick_Based_On_Loaded_Action_Manifest(ڈیٹا)) {
            جاؤ error;
        }
    }

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->آزاد = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->سیٹ_Display_منوال = OPENVR_سیٹ_Display_منوال;
    device->CreateSDLWindow = OPENVR_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = OPENVR_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_سائز = OPENVR_سیٹ_کھڑکی_سائز;
    device->Get_کھڑکی_سائز_اندر_Pixels = OPENVR_Get_کھڑکی_سائز_اندر_Pixels;
    device->Show_کھڑکی = OPENVR_Show_کھڑکی;
    device->Hide_کھڑکی = OPENVR_Hide_کھڑکی;
    device->Destroy_کھڑکی = OPENVR_Destroy_کھڑکی;
    device->Show_پیغام_Box = OPENVR_Show_پیغام_Box;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_WGL
    device->GL_بھرو_Library = OPENVR_GL_بھرو_Library;
    device->GL_Get_Proc_پتہ = OPENVR_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = OPENVR_GL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = OPENVR_GL_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = OPENVR_GL_تبادلہ_کھڑکی;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#ورنہ
#غلطی Needs مزید work مقصد support EGL
#اگر_ختم
#ورنہ
    device->GL_بھرو_Library = OVR_EGL_بھرو_Library;
    device->GL_Get_Proc_پتہ = OVR_EGL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = OVR_EGL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = OVR_EGL_Get_تبادلہ_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_تبادلہ_کھڑکی = OPENVR_GL_تبادلہ_کھڑکی;
#اگر_ختم

#اگر defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_بھرو_Library = WIN_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#ورنہ
    device->Vulkan_بھرو_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#اگر_ختم

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->سیٹ_کھڑکی_Icon = OPENVR_سیٹ_کھڑکی_Icon;

    واپس device;

error:
    OPENVR_Destroy(device);
    واپس تہی;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, تہی, false
};

#اگر_ختم // SDL_VIDEO_DRIVER_OPENVR

