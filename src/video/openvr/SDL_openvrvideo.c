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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENVR

#ਜੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_OPENVR
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openvrvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>
#ਨਹੀਂਤਾਂ
// Currently only EGL, not OpenGL, is supported on other platforms
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengles2.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengles2_gl2.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
#ਅਨ੍ਤਰ੍ਭਾਵ "../windows/SDL_windowsopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../windows/SDL_windowsvulkan.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_OPENGL "OPENGL32.DLL"

ਸਥਿਰ bool OPENVR_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਸਥਿਰ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

ਬਣਤਰ SDL_GLContextState
{
    HGLRC hglrc;
};
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS



#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_WINDOWS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#ਜੇ_ਅੰਤ

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MARKER_ID 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MARKER_STR "vr-marker,frame_end,type,application"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_ਅੰਕੜੇ * global_openvr_driver;

ਸਥਿਰ ਖਾਲੀ InitializeMouseFunctions(ਖਾਲੀ);

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ texture_id_handle;
    ਪੂਰਨ hot_x, hot_y;
    ਪੂਰਨ w, h;
};

// GL Extensions for functions we will be using.
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glBindFramebuffer)(GLenum ਨਿਸ਼ਾਨਾ, GLuint framebuffer);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glBindRenderbuffer)(GLenum ਨਿਸ਼ਾਨਾ, GLuint renderbuffer);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glRenderbufferStorage)(GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glFramebufferTexture2D)(GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ਸਥਿਰ GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_ਸਥਿਤੀ)(GLuint framebuffer, GLenum ਨਿਸ਼ਾਨਾ);
ਸਥਿਰ GLenum (APIENTRY *ov_glGetError)(ਖਾਲੀ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glFlush)(ਖਾਲੀ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_gl_ਅੰਤ)(ਖਾਲੀ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glTexParameterf)(GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfloat param);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glTexParameteri)(GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLenum param);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glTexImage2D)(GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glBindTexture)(GLenum ਨਿਸ਼ਾਨਾ, GLuint texture);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ਅਚਲ GLenum *bufs);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * ਅੰਕੜੇ);
ਸਥਿਰ ਅਚਲ GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint ਸੂਚਕਾਂਕ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glClear)(GLbitfield ਨਕਾਬ);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_gl_Color_ਨਕਾਬ)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ਸਥਿਰ ਖਾਲੀ (APIENTRY *ov_gl_Debug_ਸੁਨੇਹਾ_ਪਾਓ)(GLenum ਸਰੋਤ, GLenum type, GLuint id, GLenum severity, GLsizei ਲੰਮਾਈ, ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
ਸਥਿਰ PROC (*ov_wgl_Get_Proc_ਪਤਾ)(LPCSTR);
ਸਥਿਰ HGLRC (*ov_wglCreateContext)(HDC);
ਸਥਿਰ BOOL (*ov_wglDeleteContext)(HGLRC);
ਸਥਿਰ BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#ਜੇ_ਅੰਤ


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENVR_DEFAULT_ਚੌੜਾਈ 1920
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENVR_DEFAULT_ਉਚਾਈ 1080

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENVR_ਤਿਆਰੀ_Proc(proc) { proc = (ਖਾਲੀ *)SDL_GL_Get_Proc_ਪਤਾ((#proc)+3); ਜੇ (!proc) { failed_extension = (#proc)+3; } }

ਸਥਿਰ bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    ਜੇ (!ov_glGetError) {
        ਅਚਲ ਅੱਖਰ * failed_extension = 0;
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGenFramebuffers);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGenRenderbuffers);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glBindFramebuffer);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glBindRenderbuffer);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glRenderbufferStorage);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glFramebufferTexture2D);
        OPENVR_ਤਿਆਰੀ_Proc(ov_gl_Check_Named_Framebuffer_ਸਥਿਤੀ);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGetError);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glFlush);
        OPENVR_ਤਿਆਰੀ_Proc(ov_gl_ਅੰਤ);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGenTextures);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glDeleteTextures);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glTexParameterf);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glTexParameteri);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glTexImage2D);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glBindTexture);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glDrawBuffers);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glClear);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glClearColor);
        OPENVR_ਤਿਆਰੀ_Proc(ov_gl_Color_ਨਕਾਬ);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGetStringi);
        OPENVR_ਤਿਆਰੀ_Proc(ov_glGetIntegerv);
        OPENVR_ਤਿਆਰੀ_Proc(ov_gl_Debug_ਸੁਨੇਹਾ_ਪਾਓ);
        ਜੇ (failed_extension) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_ਸੈੱਟ_Overlay_Error(EVROverlayError e)
{
    ਚੋਣ (e) {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CASE(X) ਹਾਲਤ EVROverlayError_VROverlayError_##X: ਵਾਪਸ SDL_ਸੈੱਟ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_ਹੱਦਬੰਦੀ_Exceeded);
    CASE(WrongVisibilityType);
    CASE(ਕੁੰਜੀ_Too_Long);
    CASE(NameTooLong);
    CASE(ਕੁੰਜੀ_ਵਿੱਚ_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_ਮੰਜ਼ਿਲ_ਲੱਦੋ_File);
    CASE(Keyboard_Already_ਵਿੱਚ_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_ਨਕਾਬ_Primitives);
    CASE(Bad_ਨਕਾਬ_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_ਤਾਲਾ_ਸਮਰੱਥਾ_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_ਬਾਹਰਲਾ);
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CASE
    ਮੂਲ:
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unknown VROverlayError %d", e);
    }
}

ਸਥਿਰ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

ਸਥਿਰ bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    ਅਚਲ ਅੱਖਰ * hint_ਚੌੜਾਈ = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ਅਚਲ ਅੱਖਰ * hint_ਉਚਾਈ = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ਅਚਲ ਅੱਖਰ * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    ਪੂਰਨ ਚੌੜਾਈ = hint_ਚੌੜਾਈ ? SDL_atoi(hint_ਚੌੜਾਈ) : 0;
    ਪੂਰਨ ਉਚਾਈ = hint_ਉਚਾਈ ? SDL_atoi(hint_ਉਚਾਈ) : 0;
    ਪੂਰਨ fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_ਬਹੁਲਕ.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_ਬਹੁਲਕ.w = OPENVR_DEFAULT_ਚੌੜਾਈ;
    display.desktop_ਬਹੁਲਕ.h = OPENVR_DEFAULT_ਉਚਾਈ;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    ਜੇ (ਉਚਾਈ > 0 && ਚੌੜਾਈ > 0) {
        display.desktop_ਬਹੁਲਕ.w = ਚੌੜਾਈ;
        display.desktop_ਬਹੁਲਕ.h = ਉਚਾਈ;
    }
    ਜੇ (fps) {
        display.desktop_ਬਹੁਲਕ.refresh_ਦਰ = fps;
    } ਨਹੀਂਤਾਂ {
        display.desktop_ਬਹੁਲਕ.refresh_ਦਰ = ਅੰਕੜੇ->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_ਸੂਚਕਾਂਕ_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (ਅੱਖਰ *)"OpenVRDisplay";
    SDL_ਜੋੜੋ_Video_Display(&display, false);

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ਸਥਿਰ ਖਾਲੀ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ) {
        ਜੇ (ਅੰਕੜੇ->openVRLIB) {
            SDL_UnloadObject(ਅੰਕੜੇ->openVRLIB);
        }
    }
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    ਪੂਰਨ w = surf->w;
    ਪੂਰਨ h = surf->h;
    ਪੂਰਨ pitch = surf->pitch;
    ਪੂਰਨ x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    ਲਈ(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        ਲਈ(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    ਵਾਪਸ pxd;
}

ਸਥਿਰ bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    ਜੇ (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_ਚੌੜਾਈ;
        videodata->targh = OPENVR_DEFAULT_ਉਚਾਈ;
    }

    ਜੇ (videodata->targh != videodata->ਆਖਰੀ_targh
     || videodata->targw != videodata->ਆਖਰੀ_targw) {

        ਬਣਤਰ HmdVector2_t ms;
        ਪੂਰਨ ਸਥਿਤੀ;

        ਜੇ (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_ਡੂੰਘਾਈ_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_ਡੂੰਘਾਈ_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_ਸਭ_ਤੋਂ_ਨੇੜੇ);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_ਸਭ_ਤੋਂ_ਨੇੜੇ);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        ਸਥਿਤੀ = ov_gl_Check_Named_Framebuffer_ਸਥਿਤੀ(videodata->fbo, GL_FRAMEBUFFER);
        ਜੇ (ਸਥਿਤੀ != GL_FRAMEBUFFER_COMPLETE) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (ਦਸ਼ਮਲਵ)videodata->targw;
        ms.v[1] = (ਦਸ਼ਮਲਵ)videodata->targh;
        videodata->oOverlay->ਸੈੱਟ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->ਆਖਰੀ_targh = videodata->targh;
        videodata->ਆਖਰੀ_targw = videodata->targw;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_VirtualControllerRumble(ਖਾਲੀ *userdata, Uint16 ਨੀਵਾਂ_frequency_rumble, Uint16 ਉੱਚਾ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)userdata;

    ਅਚਲ ਦਸ਼ਮਲਵ k_flIntensity = 320.f; // Maximum frequency
    ਦਸ਼ਮਲਵ fl_ਖੱਬਾ_Frequency = (ਦਸ਼ਮਲਵ)ਨੀਵਾਂ_frequency_rumble * k_flIntensity / 65535.f;
    ਦਸ਼ਮਲਵ fl_ਸੱਜਾ_Frequency = (ਦਸ਼ਮਲਵ)ਉੱਚਾ_frequency_rumble * k_flIntensity / 65535.f;
    ਦਸ਼ਮਲਵ flDurationSeconds = 2.f;
    ਦਸ਼ਮਲਵ flAmplitude = 1.f;

    videodata->o_ਨਿਵੇਸ਼->TriggerHapticVibrationAction(videodata->ਨਿਵੇਸ਼_action_handles_haptics[0], 0, flDurationSeconds, fl_ਖੱਬਾ_Frequency, flAmplitude, 0);
    videodata->o_ਨਿਵੇਸ਼->TriggerHapticVibrationAction(videodata->ਨਿਵੇਸ਼_action_handles_haptics[1], 0, flDurationSeconds, fl_ਸੱਜਾ_Frequency, flAmplitude, 0);

    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_VirtualControllerRumbleTriggers(ਖਾਲੀ *userdata, Uint16 ਖੱਬਾ_rumble, Uint16 ਸੱਜਾ_rumble)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)userdata;
    videodata->o_ਨਿਵੇਸ਼->TriggerHapticVibrationAction(videodata->ਨਿਵੇਸ਼_action_handles_haptics[0], 0, 0.1f, ਖੱਬਾ_rumble, 1.0, 0);
    videodata->o_ਨਿਵੇਸ਼->TriggerHapticVibrationAction(videodata->ਨਿਵੇਸ਼_action_handles_haptics[1], 0, 0.1f, ਸੱਜਾ_rumble, 1.0, 0);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_VirtualControllerUpdate(ਖਾਲੀ *userdata)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ਨਿਵੇਸ਼_Digital_Action_ਅੰਕੜੇ_t digital_ਨਿਵੇਸ਼_action;
    ਨਿਵੇਸ਼_Analog_Action_ਅੰਕੜੇ_t analog_ਨਿਵੇਸ਼_action;
    EVRInputError e;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#ਜੇ_ਅੰਤ
    VRActive_Action_ਸੈੱਟ_t action_ਸੈੱਟ = { 0 };
    action_ਸੈੱਟ.ul_Action_ਸੈੱਟ = videodata->ਨਿਵੇਸ਼_action_ਸੈੱਟ;
    e = videodata->o_ਨਿਵੇਸ਼->UpdateActionState(&action_ਸੈੱਟ, ਆਕਾਰ(action_ਸੈੱਟ), 1);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }

    ਲਈ (ਪੂਰਨ d = 0; d < videodata->ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ; d++)
    {
        ਜੇ (videodata->ਨਿਵੇਸ਼_action_handles_buttons[d] == k_ulInvalidActionHandle)
            ਜਾਰੀ;
        e = videodata->o_ਨਿਵੇਸ਼->Get_Digital_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_buttons[d], &digital_ਨਿਵੇਸ਼_action, ਆਕਾਰ(digital_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
        ਜੇ (e)
        {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#ਜੇ_ਅੰਤ
            ਵਾਪਸ;
        }
        SDL_ਸੈੱਟ_Joystick_Virtual_Button(joystick, d, digital_ਨਿਵੇਸ਼_action.bState);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#ਜੇ_ਅੰਤ
    }

    // Left Stick
    e = videodata->o_ਨਿਵੇਸ਼->Get_Analog_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_axes[0], &analog_ਨਿਵੇਸ਼_action, ਆਕਾਰ(analog_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ਨਿਵੇਸ਼_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ਨਿਵੇਸ਼_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ਨਿਵੇਸ਼->Get_Analog_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_axes[1], &analog_ਨਿਵੇਸ਼_action, ਆਕਾਰ(analog_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ਨਿਵੇਸ਼_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ਨਿਵੇਸ਼_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ਨਿਵੇਸ਼->Get_Analog_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_axes[2], &analog_ਨਿਵੇਸ਼_action, ਆਕਾਰ(analog_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ਖੱਬਾ_TRIGGER, (Sint16)((analog_ਨਿਵੇਸ਼_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ਨਿਵੇਸ਼->Get_Analog_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_axes[3], &analog_ਨਿਵੇਸ਼_action, ਆਕਾਰ(analog_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }
    SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ਸੱਜਾ_TRIGGER, (Sint16)((analog_ਨਿਵੇਸ਼_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#ਜੇ 0
    ਲਈ (a = 0; a < videodata->ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ; a++)
    {
        ਦਸ਼ਮਲਵ xval = 0.0f;
        e = videodata->o_ਨਿਵੇਸ਼->Get_Analog_Action_ਅੰਕੜੇ(videodata->ਨਿਵੇਸ਼_action_handles_axes[a], &analog_ਨਿਵੇਸ਼_action, ਆਕਾਰ(analog_ਨਿਵੇਸ਼_action), k_ul_Invalid_ਨਿਵੇਸ਼_ਮੁੱਲ_Handle);
        ਜੇ (e) ਜਾਓ updatefail;
        xval = analog_ਨਿਵੇਸ਼_action.x;
        ਜੇ (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        ਜੇ (a == SDL_GAMEPAD_AXIS_ਖੱਬਾ_TRIGGER || a == SDL_GAMEPAD_AXIS_ਸੱਜਾ_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_ਸੈੱਟ_Joystick_Virtual_Axis(joystick, a, xval);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#ਜੇ_ਅੰਤ
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ;
}

ਸਥਿਰ bool OPENVR_ਤਿਆਰੀ_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_ਅੰਕੜੇ * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    ਅੱਖਰ * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_ਗਿਣਤੀ] = {
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
    ਅੱਖਰ * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    ਜੇ ((e = videodata->o_ਨਿਵੇਸ਼->Get_Action_ਸੈੱਟ_Handle("/actions/virtualgamepad", &videodata->ਨਿਵੇਸ਼_action_ਸੈੱਟ)) != EVRInputError_VRInputError_None)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#ਜੇ_ਅੰਤ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to get action set handle");
    }

    videodata->ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ਨਿਵੇਸ਼_action_handles_buttons = SDL_malloc(videodata->ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ * ਆਕਾਰ(VRActionHandle_t));

    ਲਈ (ਪੂਰਨ i = 0; i < videodata->ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ; i++)
    {
        e = videodata->o_ਨਿਵੇਸ਼->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ਨਿਵੇਸ਼_action_handles_buttons[i]);
        ਜੇ (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ਨਿਵੇਸ਼_action_handles_axes = SDL_malloc(videodata->ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ * ਆਕਾਰ(VRActionHandle_t));

    ਲਈ (ਪੂਰਨ i = 0; i < videodata->ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ; i++)
    {
        e = videodata->o_ਨਿਵੇਸ਼->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ਨਿਵੇਸ਼_action_handles_axes[i]);
        ਜੇ (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ਨਿਵੇਸ਼->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ਨਿਵੇਸ਼_action_handles_haptics[0]);
    e |= videodata->o_ਨਿਵੇਸ਼->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ਨਿਵੇਸ਼_action_handles_haptics[1]);
    ਜੇ (e)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_ਗਿਣਤੀ;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_ਗਿਣਤੀ;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    ਜੇ (!virtual_id) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    ਜੇ (!videodata->virtual_joystick) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ਨਿਵੇਸ਼_action_handles_buttons_ਗਿਣਤੀ, videodata->ਨਿਵੇਸ਼_action_handles_axes_ਗਿਣਤੀ);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    // Wait til here, to make sure we have our context setup correctly.
    ਜੇ (!OPENVR_InitExtensions(_this)) {
        ਵਾਪਸ false;
    }

    // Generate the overlay.
    {
        ਅਚਲ ਅੱਖਰ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        ਅੱਖਰ * cursorname = 0;
        ਜੇ (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        ਜੇ (!videodata->sOverlayName) {
            ਵਾਪਸ false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        ਜੇ (!cursorname) {
            ਵਾਪਸ false;
        }

        EVROverlayError ਨਤੀਜਾ = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            ਖਿੜਕੀ->title, &videodata->overlayID, &videodata->thumbID);
        ਜੇ (ਨਤੀਜਾ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create dashboard overlay (%d)", ਨਤੀਜਾ );
        }
        ਨਤੀਜਾ = videodata->oOverlay->CreateOverlay(cursorname, ਖਿੜਕੀ->title, &videodata->cursorID);
        ਜੇ (ਨਤੀਜਾ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create cursor overlay (%d)", ਨਤੀਜਾ );
        }
        SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
        SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_OPENVR_OVERLAY_ID_ਸੰਖਿਆ, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        ਜੇ (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } ਨਹੀਂਤਾਂ {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#ਜੇ 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#ਜੇ_ਅੰਤ
        }

        ਲਈ (ਪੂਰਨ i = 0; i < ਆਕਾਰ(overlay_flags) * 8; ++i) {
            ਜੇ (overlay_flags & (1 << i)) {
                videodata->oOverlay->ਸੈੱਟ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ਅਚਲ ਅੱਖਰ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        ਦਸ਼ਮਲਵ f_ਚੌੜਾਈ = hint ? (ਦਸ਼ਮਲਵ)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->ਸੈੱਟ_Overlay_ਚੌੜਾਈ_ਵਿੱਚ_Meters(videodata->overlayID, f_ਚੌੜਾਈ);
    }
    {
        ਅਚਲ ਅੱਖਰ * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        ਦਸ਼ਮਲਵ f_Cursor_ਚੌੜਾਈ = hint ? (ਦਸ਼ਮਲਵ)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->ਸੈੱਟ_Overlay_ਚੌੜਾਈ_ਵਿੱਚ_Meters(videodata->cursorID, f_Cursor_ਚੌੜਾਈ * 0.5f);
    }
    {
        ਅਚਲ ਅੱਖਰ * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        ਜੇ (hint) {
            ਅੱਖਰ * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->ਸੈੱਟ_Overlay_From_File(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            ਜੇ (err == EVROverlayError_VROverlayError_None) {
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
        videodata->oOverlay->ਸੈੱਟ_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    ਜੇ (!OPENVR_CheckRenderbuffer(_this)) {
        ਵਾਪਸ false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->ਸੈੱਟ_Overlay_Name(videodata->overlayID, ਖਿੜਕੀ->title);

    videodata->bDidCreateOverlay = true;
    videodata->ਖਿੜਕੀ = ਖਿੜਕੀ;

    ਵਾਪਸ true;
}


ਸਥਿਰ bool OPENVR_ਤਿਆਰੀ_ਚੌਖਟਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਸਥਿਰ ਅਚਲ GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_ਬਫਰ_rendering = true;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    {
        ਪੂਰਨ error = ov_glGetError();
        ਜੇ (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_ਸਥਿਤੀ(videodata->fbo, GL_FRAMEBUFFER));
    }
#ਜੇ_ਅੰਤ

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_ਨਕਾਬ(false, false, false, true);
        ov_glClear(GL_COLOR_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ);
        ov_gl_Color_ਨਕਾਬ(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_Release_ਚੌਖਟਾ(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    ਜੇ (!ov_glGetError) {
        ਵਾਪਸ true;
    }

    ਜੇ (!videodata->is_ਬਫਰ_rendering) {
        ਵਾਪਸ true;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    {
        ਪੂਰਨ error = ov_glGetError();
        ਜੇ (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_ਸਥਿਤੀ(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#ਜੇ_ਅੰਤ

    videodata->is_ਬਫਰ_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ਜੇ (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->ਆਖਰੀ_targh &&
        videodata->targw == videodata->ਆਖਰੀ_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ਬਣਤਰ Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (ਖਾਲੀ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->ਸੈੱਟ_Overlay_Texture(videodata->overlayID, &tex);
    }

    ਜੇ (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    ਜੇ (videodata->renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ) {
        ov_gl_Debug_ਸੁਨੇਹਾ_ਪਾਓ(GL_DEBUG_ਸਰੋਤ_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    ਵਾਪਸ OPENVR_CheckRenderbuffer(_this);
}

ਸਥਿਰ ਖਾਲੀ OPENVR_HandleResize(SDL_VideoDevice *_this, ਪੂਰਨ w, ਪੂਰਨ h)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਅੰਕੜੇ->targw = w;
    ਅੰਕੜੇ->targh = h;
}

ਸਥਿਰ bool OPENVR_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    ਵਾਪਸ true;
}


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
ਸਥਿਰ LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM lParam)
{
    ਚੋਣ (ਸੁਨੇਹਾ_2) {
    ਹਾਲਤ WM_DESTROY:
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ Def_ਖਿੜਕੀ_Proc(hwnd, ਸੁਨੇਹਾ_2, wParam, lParam);
}

ਸਥਿਰ bool OPENVR_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    ਜੇ (ਰਸਤਾ == ਨਿਰਾ) {
        ਰਸਤਾ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ਲੱਦੋ_Object(ਰਸਤਾ);
    ਜੇ (!_this->gl_config.dll_handle) {
        ਵਾਪਸ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ਰਸਤਾ, ਰਸਤਾ,
                 SDL_arraysize(_this->gl_config.driver_ਰਸਤਾ));

    // Allocate OpenGL memory
    _this->gl_ਅੰਕੜੇ = (ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ));
    ਜੇ (!_this->gl_ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    _this->gl_config.driver_loaded = true;

    ਵਾਪਸ true;
}

ਸਥਿਰ SDL_Function_ਸੂਚਕ OPENVR_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    SDL_Function_ਸੂਚਕ ਨਤੀਜਾ = ਨਿਰਾ;
    ਜੇ (ov_wgl_Get_Proc_ਪਤਾ) {
        ਨਤੀਜਾ = (SDL_Function_ਸੂਚਕ)ov_wgl_Get_Proc_ਪਤਾ(proc);
        ਜੇ (ਨਤੀਜਾ) {
            ਵਾਪਸ ਨਤੀਜਾ;
        }
    }

    ਵਾਪਸ SDL_ਲੱਦੋ_Function(_this->gl_config.dll_handle, proc);
}

ਸਥਿਰ ਖਾਲੀ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ਸਥਿਰ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    GLint ਅੰਕ_Extensions;
    ਪੂਰਨ i;
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ਨਿਰਾ);
        wnd.hIcon = ਲੱਦੋ_Icon(ਨਿਰਾ, IDI_APPLICATION);
        wnd.hCursor = ਲੱਦੋ_Cursor(ਨਿਰਾ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ਨਿਰਾ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        ਰਜਿਸਟਰ_Class_A(&wnd);
        hwnd = Create_ਖਿੜਕੀ_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ਨਿਰਾ, ਨਿਰਾ, GetModuleHandle(ਨਿਰਾ), ਨਿਰਾ);

        ਸੁਨੇਹਾ_3 ਸੁਨੇਹਾ_2;
        ਜਦੋਂ (Peek_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2, ਨਿਰਾ, 0, 0, PM_REMOVE)) {
            Translate_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
            Dispatch_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
        }

        videodata->hdc = GetDC(hwnd);

        ਸਥਿਰ  PIXELFORMATDESCRIPTOR pfd =
        {
            ਆਕਾਰ(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ |
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
        GLuint PixelFormat = ਚੁਣੋ_Pixel_Format(videodata->hdc, &pfd);
        ਜੇ (!ਸੈੱਟ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_ਸੈੱਟ_Error( "Could not set pixel format" );
            ਵਾਪਸ ਨਿਰਾ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        ਜੇ (!opengl) {
            SDL_ਸੈੱਟ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            ਵਾਪਸ ਨਿਰਾ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_ਪਤਾ(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_ਪਤਾ(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_ਪਤਾ = (PROC(*)(LPCSTR))Get_Proc_ਪਤਾ(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_ਪਤਾ(opengl, "wglDeleteContext");
        ਜੇ (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_ਸੈੱਟ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            ਵਾਪਸ ਨਿਰਾ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        ਜੇ (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_ਸੈੱਟ_Error("Could not make current OpenGL context.");
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    ਜੇ (i == 0) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    videodata->renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ = false;

    ov_glGetIntegerv(GL_ਅੰਕ_EXTENSIONS, &ਅੰਕ_Extensions);
    ਲਈ (i = 0; i < ਅੰਕ_Extensions; i++) {
        ਅਚਲ ਅੱਖਰ *ccc = (ਅਚਲ ਅੱਖਰ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ਜੇ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#ਜੇ_ਅੰਤ
            videodata->renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ = true;
        }
    }

    ਜੇ (!videodata->bDidCreateOverlay) {
        ਜੇ (!OPENVR_InitializeOverlay(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_ਤਿਆਰੀ_ਚੌਖਟਾ(_this, ਖਿੜਕੀ);

    SDL_GLContext ਨਤੀਜਾ = SDL_malloc(ਆਕਾਰ(ਬਣਤਰ SDL_GLContextState));
    ਜੇ (!ਨਤੀਜਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਨਤੀਜਾ->hglrc = videodata->hglrc;
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *wnd, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    videodata->ਅਦਲਾ_ਬਦਲੀ_interval = interval;
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *ਅਦਲਾ_ਬਦਲੀ_Interval)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅਦਲਾ_ਬਦਲੀ_Interval)
        *ਅਦਲਾ_ਬਦਲੀ_Interval = videodata->ਅਦਲਾ_ਬਦਲੀ_interval;
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OPENVR: null passed in for GetSwapInterval");
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ov_wglMakeCurrent(videodata->hdc, ਨਿਰਾ);
    ov_wglDeleteContext(videodata->hglrc);
    ਵਾਪਸ true;
}


#ਨਹੀਂਤਾਂ

ਸਥਿਰ EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_ਸੰਸਕਰਣ, 2,
    EGL_NONE
};

ਸਥਿਰ bool SDL_EGL_Init_ਅੰਦਰੂਨੀ(SDL_Video_ਅੰਕੜੇ * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ਨਿਰਾ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#ਜੇ_ਅੰਤ

    ਜੇ (vd->eglDpy == 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    ਜੇ (!b) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#ਜੇ_ਅੰਤ

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    {
        ਪੂਰਨ err = eglGetError();
        ਜੇ (err != EGL_SUCCESS) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!vd->eglCtx) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    ਵਾਪਸ true;
}

// Linux, EGL, etc.
ਸਥਿਰ bool OVR_EGL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਵਾਪਸ SDL_EGL_ਲੱਦੋ_Library(_this, ਰਸਤਾ, EGL_DEFAULT_DISPLAY);
}

ਸਥਿਰ SDL_Function_ਸੂਚਕ OVR_EGL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc)
{
    ਵਾਪਸ SDL_EGL_Get_Proc_ਪਤਾ(proc);
}
ਸਥਿਰ ਖਾਲੀ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ਸਥਿਰ SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    GLint ਅੰਕ_Extensions;
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (!videodata->eglCtx) {
        ਜੇ (!SDL_EGL_Init_ਅੰਦਰੂਨੀ(videodata)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ (!OPENVR_InitExtensions(_this)) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    videodata->renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ = false;

    ov_glGetIntegerv(GL_ਅੰਕ_EXTENSIONS, &ਅੰਕ_Extensions);
    ਲਈ(ਪੂਰਨ i = 0; i < ਅੰਕ_Extensions; i++) {
        ਅਚਲ ਅੱਖਰ * ccc = (ਅਚਲ ਅੱਖਰ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ਜੇ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#ਜੇ_ਅੰਤ
           videodata->renderdoc_debugmarker_ਚੌਖਟਾ_ਸਿਰਾ = true;
        }
    }

    ਜੇ (!videodata->bDidCreateOverlay) {
        ਜੇ (!OPENVR_InitializeOverlay(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_ਤਿਆਰੀ_ਚੌਖਟਾ(_this, ਖਿੜਕੀ);

    ਵਾਪਸ videodata->eglCtx;
}

ਸਥਿਰ bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * wnd, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OVR_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    videodata->ਅਦਲਾ_ਬਦਲੀ_interval = interval;
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OVR_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ * ਅਦਲਾ_ਬਦਲੀ_Interval)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅਦਲਾ_ਬਦਲੀ_Interval)
        *ਅਦਲਾ_ਬਦਲੀ_Interval = videodata->ਅਦਲਾ_ਬਦਲੀ_interval;
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OPENVR: null passed in for GetSwapInterval");
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ bool OPENVR_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Allocate window internal data
    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (ਅੰਕੜੇ == ਨਿਰਾ) {
        ਵਾਪਸ SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
    }

    ਖਿੜਕੀ->max_w = 4096;
    ਖਿੜਕੀ->max_h = 4096;
    ਖਿੜਕੀ->min_w = 1;
    ਖਿੜਕੀ->min_h = 1;

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਵਾਪਸ true;
}


ਸਥਿਰ ਖਾਲੀ OPENVR_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_free(ਅੰਕੜੇ);
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ * ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->bDidCreateOverlay) {
        ਅੰਕੜੇ->oOverlay->ਸੈੱਟ_Overlay_Name(ਅੰਕੜੇ->overlayID, ਖਿੜਕੀ->title);
    }
}

ਸਥਿਰ ਖਾਲੀ OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਖਿੜਕੀ->pending.w != ਖਿੜਕੀ->w) {
        ਖਿੜਕੀ->w = ਖਿੜਕੀ->pending.w;
    }

    ਜੇ (ਖਿੜਕੀ->pending.h != ਖਿੜਕੀ->h) {
        ਖਿੜਕੀ->h = ਖਿੜਕੀ->pending.h;
    }

    ਜੇ (ਅੰਕੜੇ->targh != ਖਿੜਕੀ->h || ਅੰਕੜੇ->targw != ਖਿੜਕੀ->w) {
        OPENVR_HandleResize(_this, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
    }

    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
}

ਸਥਿਰ ਖਾਲੀ OPENVR_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    *w = ਅੰਕੜੇ->targw;
    *h = ਅੰਕੜੇ->targh;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->targh != ਖਿੜਕੀ->h || ਅੰਕੜੇ->targw != ਖਿੜਕੀ->w) {
        OPENVR_HandleResize(_this, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
    }

    ਅੰਕੜੇ->oOverlay->ShowDashboard(ਅੰਕੜੇ->sOverlayName);

    ਖਿੜਕੀ->flags |= (SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS | SDL_ਖਿੜਕੀ_MOUSE_FOCUS);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
}

ਸਥਿਰ ਖਾਲੀ OPENVR_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ;
}

ਸਥਿਰ bool OPENVR_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    ਜੇ (!videodata->bDidCreateOverlay) {
        ਜੇ (!OPENVR_InitializeOverlay(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    }

    ਜੇ (!OPENVR_Release_ਚੌਖਟਾ(_this)) {
        ਵਾਪਸ false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    ਜੇ (videodata->ਅਦਲਾ_ਬਦਲੀ_interval != 0) {
        videodata->oOverlay->Wait_ਚੌਖਟਾ_Sync(100);
    }

    ਜੇ (!OPENVR_ਤਿਆਰੀ_ਚੌਖਟਾ(_this, ਖਿੜਕੀ)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ Uint8 OPENVR_MapMouseButton(ਪੂਰਨ btn)
{
    ਜੇ (btn == EVRMouse_Button_VRMouse_Button_ਸੱਜਾ) {
        ਵਾਪਸ SDL_BUTTON_ਸੱਜਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (btn == EVRMouse_Button_VRMouse_Button_ਵਿਚਕਾਰ) {
        ਵਾਪਸ SDL_BUTTON_ਵਿਚਕਾਰ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_BUTTON_ਖੱਬਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ OPENVR_HandleMouse(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, ਪੂਰਨ btn, ਪੂਰਨ evt)
{
    ਜੇ (evt == 2) {
        SDL_SendMouseMotion(0, ਨਿਰਾ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ Uint8 button = OPENVR_MapMouseButton(btn);
        ਅਚਲ bool ਥੱਲੇ = (evt != 0);
        SDL_SendMouseButton(0, ਨਿਰਾ, SDL_GLOBAL_MOUSE_ID, button, ਥੱਲੇ);
    }
}


ਸਥਿਰ bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        ਵਾਪਸ;
    }
    EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ ਨਿਵੇਸ਼_ਬਹੁਲਕ;
    ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_HIDDEN:
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
        ਨਿਵੇਸ਼_ਬਹੁਲਕ = EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_Password;
        ਰੋਕੋ;
    ਮੂਲ:
        ਨਿਵੇਸ਼_ਬਹੁਲਕ = EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਬਹੁਲਕ_ਸਾਧਾਰਨ;
        ਰੋਕੋ;
    }
    EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ ਸਤਰ_ਬਹੁਲਕ;
    ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(props)) {
        ਸਤਰ_ਬਹੁਲਕ = EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_ਗੁਣਜ_ਸਤਰਾਂ;
    } ਨਹੀਂਤਾਂ {
        ਸਤਰ_ਬਹੁਲਕ = EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_k_EGamepad_ਪਾਠ_ਨਿਵੇਸ਼_ਸਤਰ_ਬਹੁਲਕ_Single_ਸਤਰ;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ਨਿਵੇਸ਼_ਬਹੁਲਕ, ਸਤਰ_ਬਹੁਲਕ,
           EKeyboard_Flags_Keyboard_Flag_ਨਿਊਨਤਮ, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ਸਥਿਰ ਖਾਲੀ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ਸਥਿਰ SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor *ਨਤੀਜਾ = SDL_calloc(1, ਆਕਾਰ(SDL_Cursor));
    ਜੇ (!ਨਤੀਜਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_ਅੰਕੜੇ *ovrc = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ovrc));
    ਜੇ (!ovrc) {
        SDL_free(ਨਤੀਜਾ);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਨਤੀਜਾ->ਅੰਦਰੂਨੀ = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ਅੰਕੜੇ * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    ਜੇ (!cursor) {
        global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        ਜੇ (e != EVROverlayError_VROverlayError_None) {
            ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
        }
        ਵਾਪਸ true;
    }

    global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->ਅੰਦਰੂਨੀ;

    ਜੇ (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        ਵਾਪਸ true;
    }

    hotspot.v[0] = (ਦਸ਼ਮਲਵ)ovrc->hot_x / (ਦਸ਼ਮਲਵ)ovrc->w;
    hotspot.v[1] = (ਦਸ਼ਮਲਵ)ovrc->hot_y / (ਦਸ਼ਮਲਵ)ovrc->h;

    texture.handle = (ਖਾਲੀ *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    ਜੇ (e != EVROverlayError_VROverlayError_None) {
        ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    ਜੇ (e != EVROverlayError_VROverlayError_None) {
        ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    ਜੇ (e != EVROverlayError_VROverlayError_None) {
        ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    ਜੇ (e != EVROverlayError_VROverlayError_None) {
        ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ovrc = cursor->ਅੰਦਰੂਨੀ;
        ਜੇ (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ਸਥਿਰ bool OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_Surface * icon)
{
    ਜੇ (!global_openvr_driver) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenVR Overlay not initialized");
    }

    ਬਿਨਾਨਿਸ਼ਾਨੀ texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਜੇ (videodata->bIconOverridden) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (ਖਾਲੀ *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->ਸੈੱਟ_Overlay_Texture(videodata->thumbID, &texture);
    ਜੇ (e != EVROverlayError_VROverlayError_None) {
        ਵਾਪਸ OPENVR_ਸੈੱਟ_Overlay_Error(e);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OPENVR_Show_ਸੁਨੇਹਾ_Box(SDL_VideoDevice *_this,ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonid)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਅੱਖਰ ਖਾਲੀ_ਥਾਵਾਂ = 0;
    ਅੱਖਰ * ਸੁਨੇਹਾ = SDL_strdup(messageboxdata->ਸੁਨੇਹਾ?messageboxdata->ਸੁਨੇਹਾ:"");
    ਅੱਖਰ * title = SDL_strdup(messageboxdata->ਸੁਨੇਹਾ?messageboxdata->ਸੁਨੇਹਾ:"");
    ਅੱਖਰ * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_ਸੁਨੇਹਾ_Overlay(ਸੁਨੇਹਾ, title, ok, &ਖਾਲੀ_ਥਾਵਾਂ, &ਖਾਲੀ_ਥਾਵਾਂ, &ਖਾਲੀ_ਥਾਵਾਂ);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(ਸੁਨੇਹਾ);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ InitializeMouseFunctions(ਖਾਲੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ਸਥਿਰ ਖਾਲੀ OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;
    ਬਣਤਰ VREvent_t nEvent;
    ਜੇ (videodata->overlayID) {
        ਜਦੋਂ (videodata->oOverlay->Poll_ਅਗਲਾ_Overlay_Event(videodata->overlayID, &nEvent, ਆਕਾਰ(nEvent))) {
            ਚੋਣ (nEvent.eventType) {
            ਹਾਲਤ EVREventType_VREvent_ButtonPress:
            ਹਾਲਤ EVREventType_VREvent_ButtonUnpress:
                ਰੋਕੋ;
            ਹਾਲਤ EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.ਅੰਕੜੇ.mouse.x, videodata->targh - nEvent.ਅੰਕੜੇ.mouse.y, nEvent.ਅੰਕੜੇ.mouse.button, 2);
                ਰੋਕੋ;
            ਹਾਲਤ EVREvent_Type_VREvent_Mouse_Button_ਥੱਲੇ:
                OPENVR_HandleMouse(nEvent.ਅੰਕੜੇ.mouse.x, videodata->targh - nEvent.ਅੰਕੜੇ.mouse.y, nEvent.ਅੰਕੜੇ.mouse.button, 1);
                ਰੋਕੋ;
            ਹਾਲਤ EVREvent_Type_VREvent_Mouse_Button_ਉੱਪਰ:
                OPENVR_HandleMouse(nEvent.ਅੰਕੜੇ.mouse.x, videodata->targh - nEvent.ਅੰਕੜੇ.mouse.y, nEvent.ਅੰਕੜੇ.mouse.button, 0);
                ਰੋਕੋ;
            ਹਾਲਤ EVREventType_VREvent_ScrollSmooth:
            ਹਾਲਤ EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ਨਿਰਾ, SDL_GLOBAL_MOUSE_ID, -nEvent.ਅੰਕੜੇ.scroll.xdelta, nEvent.ਅੰਕੜੇ.scroll.ydelta, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
                ਰੋਕੋ;
            ਹਾਲਤ EVREvent_Type_VREvent_Keyboard_Char_ਨਿਵੇਸ਼:
                SDL_Send_Keyboard_Unicode_ਕੁੰਜੀ(SDL_GetTicksNS(), nEvent.ਅੰਕੜੇ.keyboard.c_New_ਨਿਵੇਸ਼[0]);
                ਰੋਕੋ;
            ਹਾਲਤ EVREventType_VREvent_OverlayShown:
                SDL_ਸੈੱਟ_Keyboard_Focus(videodata->ਖਿੜਕੀ);
                SDL_Send_ਖਿੜਕੀ_Event(videodata->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
                SDL_Send_ਖਿੜਕੀ_Event(videodata->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
                ਰੋਕੋ;
            ਹਾਲਤ EVREventType_VREvent_OverlayHidden:
                SDL_Send_ਖਿੜਕੀ_Event(videodata->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HIDDEN, 0, 0);
                SDL_Send_ਖਿੜਕੀ_Event(videodata->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
                SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
                ਰੋਕੋ;
            ਹਾਲਤ EVREventType_VREvent_OverlayClosed:
            ਹਾਲਤ EVREventType_VREvent_Quit:
                SDL_SendQuit();
                ਰੋਕੋ;
            }
        }
    }
}


ਸਥਿਰ SDL_VideoDevice *OPENVR_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਅਚਲ ਅੱਖਰ *hint;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_WINDOWS
    SDL_ਰਜਿਸਟਰ_App(ਨਿਰਾ, 0, ਨਿਰਾ);
#ਜੇ_ਅੰਤ

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (device) {
        ਅੰਕੜੇ = (ਬਣਤਰ SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ = ਨਿਰਾ;
    }
    ਜੇ (!ਅੰਕੜੇ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#ਜੇ_ਅੰਤ
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }
    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    ਜੇ (hint) {
        ਅੰਕੜੇ->openVRLIB = SDL_ਲੱਦੋ_Object(hint);
    }
    ਜੇ (!ਅੰਕੜੇ->openVRLIB) {
        ਅੰਕੜੇ->openVRLIB = SDL_ਲੱਦੋ_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    ਜੇ (!ਅੰਕੜੇ->openVRLIB) {
        SDL_ਸੈੱਟ_Error("Could not open OpenVR API Library");
        ਜਾਓ error;
    }

    ਅੰਕੜੇ->FN_VR_Init_ਅੰਦਰੂਨੀ = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->openVRLIB, "VR_InitInternal");
    ਅੰਕੜੇ->FN_VR_GetVRInitErrorAsEnglishDescription = (ਅਚਲ ਅੱਖਰ *(*)(EVRInitError error))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    ਅੰਕੜੇ->FN_VR_GetGenericInterface = (intptr_t (*)(ਅਚਲ ਅੱਖਰ *pch_Interface_ਸੰਸਕਰਣ, EVRInitError * peError))SDL_ਲੱਦੋ_Function(ਅੰਕੜੇ->openVRLIB, "VR_GetGenericInterface");
    ਜੇ (!ਅੰਕੜੇ->FN_VR_Init_ਅੰਦਰੂਨੀ || !ਅੰਕੜੇ->FN_VR_GetVRInitErrorAsEnglishDescription || !ਅੰਕੜੇ->FN_VR_GetGenericInterface) {
        ਜਾਓ error;
    }

    ਅੱਖਰ fnname[128];
    EVRInitError e;
    ਅੰਕੜੇ->vrtoken = ਅੰਕੜੇ->FN_VR_Init_ਅੰਦਰੂਨੀ(&e, EVRApplicationType_VRApplication_Overlay);
    ਜੇ (!ਅੰਕੜੇ->vrtoken) {
        ਅਚਲ ਅੱਖਰ *err = "Can't get english description";
        ਜੇ (ਅੰਕੜੇ->FN_VR_GetVRInitErrorAsEnglishDescription != ਨਿਰਾ)
            err = ਅੰਕੜੇ->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_ਸੈੱਟ_Error("Could not generate OpenVR Context (%s)", err);
        ਜਾਓ error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_ਸੰਸਕਰਣ);
    ਅੰਕੜੇ->oSystem = (ਬਣਤਰ VR_IVRSystem_Fn_ਸਾਰਣੀ *)ਅੰਕੜੇ->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_ਸੰਸਕਰਣ);
    ਅੰਕੜੇ->oOverlay = (ਬਣਤਰ VR_IVROverlay_Fn_ਸਾਰਣੀ *)ਅੰਕੜੇ->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_ਸੰਸਕਰਣ);
    ਅੰਕੜੇ->o_ਨਿਵੇਸ਼ = (ਬਣਤਰ VR_IVRInput_Fn_ਸਾਰਣੀ *)ਅੰਕੜੇ->FN_VR_GetGenericInterface(fnname, &e);

    ਜੇ (!ਅੰਕੜੇ->oOverlay || !ਅੰਕੜੇ->oSystem || !ਅੰਕੜੇ->o_ਨਿਵੇਸ਼) {
        SDL_ਸੈੱਟ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_ਸੰਸਕਰਣ, IVROverlay_ਸੰਸਕਰਣ, IVRInput_ਸੰਸਕਰਣ);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    ਅੱਖਰ *loadpath = 0;
    EVRInputError err;

    ਜੇ (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਅੱਖਰ *basepath = SDL_Get_ਅਧਾਰ_ਰਸਤਾ();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    ਜੇ (!loadpath) {
        ਜਾਓ error;
    }

    err = ਅੰਕੜੇ->o_ਨਿਵੇਸ਼->ਸੈੱਟ_Action_Manifest_ਰਸਤਾ(loadpath);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#ਜੇ_ਅੰਤ
    SDL_free(loadpath);
    ਜੇ (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        ਜੇ (hint) {
            ਜਾਓ error;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ(!OPENVR_ਤਿਆਰੀ_Joystick_Based_On_Loaded_Action_Manifest(ਅੰਕੜੇ)) {
            ਜਾਓ error;
        }
    }

    // Setup amount of available displays
    device->ਅੰਕ_displays = 0;

    // Set device free function
    device->ਮੁਕਤ = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = OPENVR_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->CreateSDLWindow = OPENVR_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels = OPENVR_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels;
    device->Show_ਖਿੜਕੀ = OPENVR_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = OPENVR_Hide_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = OPENVR_Destroy_ਖਿੜਕੀ;
    device->Show_ਸੁਨੇਹਾ_Box = OPENVR_Show_ਸੁਨੇਹਾ_Box;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_WGL
    device->GL_ਲੱਦੋ_Library = OPENVR_GL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = OPENVR_GL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = OPENVR_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = OPENVR_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = OPENVR_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#ਨਹੀਂਤਾਂ
#ਗਲਤੀ Needs ਹੋਰ work ਮੰਜ਼ਿਲ support EGL
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
    device->GL_ਲੱਦੋ_Library = OVR_EGL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = OVR_EGL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = OVR_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = OVR_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = OPENVR_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_ਲੱਦੋ_Library = WIN_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#ਨਹੀਂਤਾਂ
    device->Vulkan_ਲੱਦੋ_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#ਜੇ_ਅੰਤ

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Icon = OPENVR_ਸੈੱਟ_ਖਿੜਕੀ_Icon;

    ਵਾਪਸ device;

error:
    OPENVR_Destroy(device);
    ਵਾਪਸ ਨਿਰਾ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ਨਿਰਾ, false
};

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENVR

