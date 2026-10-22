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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENVR

#ಆದರೆ 0
#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_OPENVR
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_openvrvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
// Currently only OpenGL, not EGL, is supported on Windows
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಇಲ್ಲದಿದ್ದರೆ
// Currently only EGL, not OpenGL, is supported on other platforms
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2.h>
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2_gl2.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
#ಅನ್ತರ್ಭಾವ "../windows/SDL_windowsopengl.h"
#ಅನ್ತರ್ಭಾವ "../windows/SDL_windowsvulkan.h"

#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_OPENGL "OPENGL32.DLL"

ಸ್ಥಿರ bool OPENVR_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಸ್ಥಿರ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ರಚನೆ SDL_GLContextState
{
    HGLRC hglrc;
};
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS



#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_WINDOWS
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.dll"
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_OPENVR_DRIVER_DYNAMIC "openvr_api.so"
#ಆದರೆ_ಅಂತ್ಯ

SDL_ELF_NOTE_DLOPEN(
    "video-openvr",
    "Support for OpenVR video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_OPENVR_DRIVER_DYNAMIC
)

#ವ್ಯಾಖ್ಯಾನಿಸು MARKER_ID 0
#ವ್ಯಾಖ್ಯಾನಿಸು MARKER_STR "vr-marker,frame_end,type,application"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು EXTERN_C

// For access to functions that don't get the video data context.
SDL_Video_ದತ್ತಾಂಶ * global_openvr_driver;

ಸ್ಥಿರ ಶೂನ್ಯ InitializeMouseFunctions(ಶೂನ್ಯ);

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    ಚಿಹ್ನೆರಹಿತ texture_id_handle;
    ಪೂರ್ಣಾಂಕ hot_x, hot_y;
    ಪೂರ್ಣಾಂಕ w, h;
};

// GL Extensions for functions we will be using.
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindFramebuffer)(GLenum ಗುರಿ, GLuint framebuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindRenderbuffer)(GLenum ಗುರಿ, GLuint renderbuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glRenderbufferStorage)(GLenum ಗುರಿ, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFramebufferRenderbuffer)(GLenum ಗುರಿ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFramebufferTexture2D)(GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ಸ್ಥಿರ GLenum (APIENTRY *ov_gl_Check_Named_Framebuffer_ಸ್ಥಿತಿ)(GLuint framebuffer, GLenum ಗುರಿ);
ಸ್ಥಿರ GLenum (APIENTRY *ov_glGetError)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glFlush)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_gl_ಮುಕ್ತಾಯ)(ಶೂನ್ಯ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGenTextures)(GLsizei n, GLuint *textures);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glDeleteTextures)(GLsizei n, GLuint *textures);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexParameterf)(GLenum ಗುರಿ, GLenum pname, GLfloat param);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexParameteri)(GLenum ಗುರಿ, GLenum pname, GLenum param);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glTexImage2D)(GLenum ಗುರಿ, GLint level, GLint internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLint border, GLenum format, GLenum type, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glBindTexture)(GLenum ಗುರಿ, GLuint texture);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glDrawBuffers)(GLsizei n, ಸ್ಥಿರಾಂಕ GLenum *bufs);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glGetIntegerv)(GLenum pname, GLint * ದತ್ತಾಂಶ);
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ GLubyte *(APIENTRY *ov_glGetStringi)(GLenum name, GLuint ಸೂಚ್ಯಂಕ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glClear)(GLbitfield ಮುಖವಾಡ);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_gl_Color_ಮುಖವಾಡ)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ಸ್ಥಿರ ಶೂನ್ಯ (APIENTRY *ov_gl_Debug_ಸಂದೇಶ_ಸೇರಿಸು)(GLenum ಮೂಲ, GLenum type, GLuint id, GLenum severity, GLsizei ಉದ್ದಳತೆ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
ಸ್ಥಿರ PROC (*ov_wgl_Get_Proc_ವಿಳಾಸ)(LPCSTR);
ಸ್ಥಿರ HGLRC (*ov_wglCreateContext)(HDC);
ಸ್ಥಿರ BOOL (*ov_wglDeleteContext)(HGLRC);
ಸ್ಥಿರ BOOL (*ov_wglMakeCurrent)(HDC, HGLRC);
//static HGLRC (*ov_wglGetCurrentContext)(void);
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿಸು OPENVR_DEFAULT_ಅಗಲ 1920
#ವ್ಯಾಖ್ಯಾನಿಸು OPENVR_DEFAULT_ಎತ್ತರ 1080

#ವ್ಯಾಖ್ಯಾನಿಸು OPENVR_ಸಿದ್ಧತೆ_Proc(proc) { proc = (ಶೂನ್ಯ *)SDL_GL_Get_Proc_ವಿಳಾಸ((#proc)+3); ಆದರೆ (!proc) { failed_extension = (#proc)+3; } }

ಸ್ಥಿರ bool OPENVR_InitExtensions(SDL_VideoDevice *_this)
{
    ಆದರೆ (!ov_glGetError) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * failed_extension = 0;
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGenFramebuffers);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGenRenderbuffers);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glBindFramebuffer);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glBindRenderbuffer);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glRenderbufferStorage);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glFramebufferRenderbuffer);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glFramebufferTexture2D);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_gl_Check_Named_Framebuffer_ಸ್ಥಿತಿ);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGetError);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glFlush);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_gl_ಮುಕ್ತಾಯ);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGenTextures);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glDeleteTextures);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glTexParameterf);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glTexParameteri);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glTexImage2D);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glBindTexture);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glDrawBuffers);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glClear);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glClearColor);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_gl_Color_ಮುಖವಾಡ);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGetStringi);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_glGetIntegerv);
        OPENVR_ಸಿದ್ಧತೆ_Proc(ov_gl_Debug_ಸಂದೇಶ_ಸೇರಿಸು);
        ಆದರೆ (failed_extension) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Error loading GL extension for %s", failed_extension);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_ಗಣ_Overlay_Error(EVROverlayError e)
{
    ಆಯ್ಕೆ (e) {
#ವ್ಯಾಖ್ಯಾನಿಸು CASE(X) ಸ್ಥಿತಿ EVROverlayError_VROverlayError_##X: ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("VROverlayError %s", #X)
    CASE(UnknownOverlay);
    CASE(InvalidHandle);
    CASE(PermissionDenied);
    CASE(Overlay_ಎಲ್ಲೆ_Exceeded);
    CASE(WrongVisibilityType);
    CASE(ಕೀಲಿ_Too_Long);
    CASE(NameTooLong);
    CASE(ಕೀಲಿ_ಒಳ_Use);
    CASE(WrongTransformType);
    CASE(InvalidTrackedDevice);
    CASE(InvalidParameter);
    CASE(ThumbnailCantBeDestroyed);
    CASE(ArrayTooSmall);
    CASE(RequestFailed);
    CASE(InvalidTexture);
    CASE(Unable_ಗಮ್ಯ_ತುಂಬು_File);
    CASE(Keyboard_Already_ಒಳ_Use);
    CASE(NoNeighbor);
    CASE(Too_Many_ಮುಖವಾಡ_Primitives);
    CASE(Bad_ಮುಖವಾಡ_Primitive);
    CASE(TextureAlreadyLocked);
    CASE(Texture_ಬೀಗ_ಸಾಮರ್ಥ್ಯ_Reached);
    CASE(TextureNotLocked);
    CASE(Timed_ಹೊರಹೋಗು);
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CASE
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown VROverlayError %d", e);
    }
}

ಸ್ಥಿರ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ಸ್ಥಿರ bool OPENVR_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint_ಅಗಲ = SDL_GetHint("SDL_DEFAULT_WIDTH");
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint_ಎತ್ತರ = SDL_GetHint("SDL_DEFAULT_HEIGHT");
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hintFPS = SDL_GetHint("SDL_DEFAULT_FPS");
    ಪೂರ್ಣಾಂಕ ಅಗಲ = hint_ಅಗಲ ? SDL_atoi(hint_ಅಗಲ) : 0;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = hint_ಎತ್ತರ ? SDL_atoi(hint_ಎತ್ತರ) : 0;
    ಪೂರ್ಣಾಂಕ fps = hintFPS ? SDL_atoi(hintFPS) : 0;

    SDL_VideoDisplay display;
    SDL_zero(display);
    display.desktop_ಬಹುಲಕ.format = SDL_PIXELFORMAT_RGBA32;
    display.desktop_ಬಹುಲಕ.w = OPENVR_DEFAULT_ಅಗಲ;
    display.desktop_ಬಹುಲಕ.h = OPENVR_DEFAULT_ಎತ್ತರ;
    display.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.current_orientation = SDL_ORIENTATION_LANDSCAPE;
    display.content_scale = 1.0f;
    ಆದರೆ (ಎತ್ತರ > 0 && ಅಗಲ > 0) {
        display.desktop_ಬಹುಲಕ.w = ಅಗಲ;
        display.desktop_ಬಹುಲಕ.h = ಎತ್ತರ;
    }
    ಆದರೆ (fps) {
        display.desktop_ಬಹುಲಕ.refresh_ದರ = fps;
    } ಇಲ್ಲದಿದ್ದರೆ {
        display.desktop_ಬಹುಲಕ.refresh_ದರ = ದತ್ತಾಂಶ->oSystem->GetFloatTrackedDeviceProperty(k_un_Tracked_Device_ಸೂಚ್ಯಂಕ_Hmd, ETrackedDeviceProperty_Prop_DisplayFrequency_Float, 0);
    }
    display.name = (ಅಕ್ಷರ *)"OpenVRDisplay";
    SDL_ಕೂಡಿಸು_Video_Display(&display, false);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->bDidCreateOverlay && videodata->overlayID != 0) {
        videodata->oOverlay->DestroyOverlay(videodata->overlayID);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_WINDOWS
    SDL_UnregisterApp();
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ) {
        ಆದರೆ (ದತ್ತಾಂಶ->openVRLIB) {
            SDL_UnloadObject(ದತ್ತಾಂಶ->openVRLIB);
        }
    }
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ uint32_t *ImageSDLToOpenVRGL(SDL_Surface * surf, bool bFlipY)
{
    ಪೂರ್ಣಾಂಕ w = surf->w;
    ಪೂರ್ಣಾಂಕ h = surf->h;
    ಪೂರ್ಣಾಂಕ pitch = surf->pitch;
    ಪೂರ್ಣಾಂಕ x, y;
    uint32_t * pxd = SDL_malloc(4 * surf->w * surf->h);
    ಗಾಗಿ(y = 0; y < h; y++) {
        uint32_t * iline = (uint32_t *)&(((uint8_t *)surf->pixels)[y * pitch]);
        uint32_t * oline = &pxd[(bFlipY?(h-y-1):y)*w];
        ಗಾಗಿ(x = 0; x < w; x++)
        {
            uint32_t pr = iline[x];
            oline[x] = (pr & 0xff00ff00) | ((pr & 0xff) << 16) | ((pr & 0xff0000)>>16);
        }
    }
    ಹಿಂತಿರುಗಿ pxd;
}

ಸ್ಥಿರ bool OPENVR_CheckRenderbuffer(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    ಆದರೆ (videodata->targw == 0 || videodata->targh == 0) {
        videodata->targw = OPENVR_DEFAULT_ಅಗಲ;
        videodata->targh = OPENVR_DEFAULT_ಎತ್ತರ;
    }

    ಆದರೆ (videodata->targh != videodata->ಕೊನೆಯ_targh
     || videodata->targw != videodata->ಕೊನೆಯ_targw) {

        ರಚನೆ HmdVector2_t ms;
        ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;

        ಆದರೆ (videodata->fbo <= 0) {
            ov_glGenFramebuffers(1, &videodata->fbo);
            ov_glGenRenderbuffers(1, &videodata->rbo);
            ov_glGenTextures(1, &videodata->overlaytexture);
        }

        // Generate the OpenGL Backing buffers/etc.
        ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
        ov_glBindRenderbuffer(GL_RENDERBUFFER, videodata->rbo);
        ov_glRenderbufferStorage(GL_RENDERBUFFER, GL_ಆಳ_COMPONENT, videodata->targw, videodata->targh);
        ov_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_ಆಳ_ATTACHMENT, GL_RENDERBUFFER, videodata->rbo);
        ov_glBindTexture(GL_TEXTURE_2D, videodata->overlaytexture);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_ಹತ್ತಿರದ);
        ov_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_ಹತ್ತಿರದ);
        ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videodata->targw, videodata->targh, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        ov_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, videodata->overlaytexture, 0);
        ಸ್ಥಿತಿ_2 = ov_gl_Check_Named_Framebuffer_ಸ್ಥಿತಿ(videodata->fbo, GL_FRAMEBUFFER);
        ಆದರೆ (ಸ್ಥಿತಿ_2 != GL_FRAMEBUFFER_COMPLETE) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OPENVR: Can't generate overlay buffer");
        }
        ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ms.v[0] = (ದಶಮಾಂಶ)videodata->targw;
        ms.v[1] = (ದಶಮಾಂಶ)videodata->targh;
        videodata->oOverlay->ಗಣ_Overlay_Mouse_Scale(videodata->overlayID, &ms);

        videodata->ಕೊನೆಯ_targh = videodata->targh;
        videodata->ಕೊನೆಯ_targw = videodata->targw;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_VirtualControllerRumble(ಶೂನ್ಯ *userdata, Uint16 ಕೆಳಗಿನ_frequency_rumble, Uint16 ಮೇಲಿನ_frequency_rumble)
{
    // On XBOX Controllers Low/High maps to Left/Right
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)userdata;

    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ k_flIntensity = 320.f; // Maximum frequency
    ದಶಮಾಂಶ fl_ಎಡ_Frequency = (ದಶಮಾಂಶ)ಕೆಳಗಿನ_frequency_rumble * k_flIntensity / 65535.f;
    ದಶಮಾಂಶ fl_ಬಲ_Frequency = (ದಶಮಾಂಶ)ಮೇಲಿನ_frequency_rumble * k_flIntensity / 65535.f;
    ದಶಮಾಂಶ flDurationSeconds = 2.f;
    ದಶಮಾಂಶ flAmplitude = 1.f;

    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[0], 0, flDurationSeconds, fl_ಎಡ_Frequency, flAmplitude, 0);
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[1], 0, flDurationSeconds, fl_ಬಲ_Frequency, flAmplitude, 0);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_VirtualControllerRumbleTriggers(ಶೂನ್ಯ *userdata, Uint16 ಎಡ_rumble, Uint16 ಬಲ_rumble)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)userdata;
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[0], 0, 0.1f, ಎಡ_rumble, 1.0, 0);
    videodata->o_ಒಳಹರಿವು->TriggerHapticVibrationAction(videodata->ಒಳಹರಿವು_action_handles_haptics[1], 0, 0.1f, ಬಲ_rumble, 1.0, 0);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_VirtualControllerUpdate(ಶೂನ್ಯ *userdata)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)userdata;
    SDL_Joystick * joystick = videodata->virtual_joystick;
    ಒಳಹರಿವು_Digital_Action_ದತ್ತಾಂಶ_t digital_ಒಳಹರಿವು_action;
    ಒಳಹರಿವು_Analog_Action_ದತ್ತಾಂಶ_t analog_ಒಳಹರಿವು_action;
    EVRInputError e;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    //char cts[10240];
    //char * ctsx = cts;
#ಆದರೆ_ಅಂತ್ಯ
    VRActive_Action_ಗಣ_t action_ಗಣ = { 0 };
    action_ಗಣ.ul_Action_ಗಣ = videodata->ಒಳಹರಿವು_action_ಗಣ;
    e = videodata->o_ಒಳಹರಿವು->UpdateActionState(&action_ಗಣ, ಗಾತ್ರ(action_ಗಣ), 1);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to update action state");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ d = 0; d < videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ; d++)
    {
        ಆದರೆ (videodata->ಒಳಹರಿವು_action_handles_buttons[d] == k_ulInvalidActionHandle)
            ಮುಂದುವರಿ;
        e = videodata->o_ಒಳಹರಿವು->Get_Digital_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_buttons[d], &digital_ಒಳಹರಿವು_action, ಗಾತ್ರ(digital_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
        ಆದರೆ (e)
        {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
            SDL_Log("ERROR: Failed to get digital action data: %d", d);
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ;
        }
        SDL_ಗಣ_Joystick_Virtual_Button(joystick, d, digital_ಒಳಹರಿವು_action.bState);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"%d", digital_input_action.bState);
#ಆದರೆ_ಅಂತ್ಯ
    }

    // Left Stick
    e = videodata->o_ಒಳಹರಿವು->Get_Analog_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_axes[0], &analog_ಒಳಹರಿವು_action, ಗಾತ್ರ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left stick");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTX, (Sint16)(analog_ಒಳಹರಿವು_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_LEFTY, (Sint16)(-analog_ಒಳಹರಿವು_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Right Stick
    e = videodata->o_ಒಳಹರಿವು->Get_Analog_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_axes[1], &analog_ಒಳಹರಿವು_action, ಗಾತ್ರ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right stick");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTX, (Sint16)(analog_ಒಳಹರಿವು_action.x * SDL_JOYSTICK_AXIS_MAX));
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_RIGHTY, (Sint16)(-analog_ಒಳಹರಿವು_action.y * SDL_JOYSTICK_AXIS_MAX));

    // Left Trigger
    e = videodata->o_ಒಳಹರಿವು->Get_Analog_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_axes[2], &analog_ಒಳಹರಿವು_action, ಗಾತ್ರ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: left trigger");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ಎಡ_TRIGGER, (Sint16)((analog_ಒಳಹರಿವು_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

    // Right Trigger
    e = videodata->o_ಒಳಹರಿವು->Get_Analog_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_axes[3], &analog_ಒಳಹರಿವು_action, ಗಾತ್ರ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get analog action data: right trigger");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }
    SDL_ಗಣ_Joystick_Virtual_Axis(joystick, SDL_GAMEPAD_AXIS_ಬಲ_TRIGGER, (Sint16)((analog_ಒಳಹರಿವು_action.x * 2.0f - 1.0f) * SDL_JOYSTICK_AXIS_MAX));

#ಆದರೆ 0
    ಗಾಗಿ (a = 0; a < videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ; a++)
    {
        ದಶಮಾಂಶ xval = 0.0f;
        e = videodata->o_ಒಳಹರಿವು->Get_Analog_Action_ದತ್ತಾಂಶ(videodata->ಒಳಹರಿವು_action_handles_axes[a], &analog_ಒಳಹರಿವು_action, ಗಾತ್ರ(analog_ಒಳಹರಿವು_action), k_ul_Invalid_ಒಳಹರಿವು_ಮೌಲ್ಯ_Handle);
        ಆದರೆ (e) ಹೋಗು updatefail;
        xval = analog_ಒಳಹರಿವು_action.x;
        ಆದರೆ (a == SDL_CONTROLLER_AXIS_LEFTY || a == SDL_CONTROLLER_AXIS_RIGHTY)
          xval *= -1.0f;
        ಆದರೆ (a == SDL_GAMEPAD_AXIS_ಎಡ_TRIGGER || a == SDL_GAMEPAD_AXIS_ಬಲ_TRIGGER)
          xval = xval * 2.0f - 1.0f;
        //SDL_SetJoystickVirtualAxis(joystick, a, analog_input_action.x * 32767);
        xval *= SDL_JOYSTICK_AXIS_MAX;
        SDL_ಗಣ_Joystick_Virtual_Axis(joystick, a, xval);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        //ctsx+=sprintf(ctsx,"[%f]", analog_input_action.x);
#ಆದರೆ_ಅಂತ್ಯ
    }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    //SDL_Log("Debug Input States: %s", cts);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ bool OPENVR_ಸಿದ್ಧತೆ_Joystick_Based_On_Loaded_Action_Manifest(SDL_Video_ದತ್ತಾಂಶ * videodata)
{
    SDL_VirtualJoystickDesc desc;
    SDL_JoystickID virtual_id;

    EVRInputError e = 0;

    ಅಕ್ಷರ * k_pchBooleanActionPaths[SDL_GAMEPAD_BUTTON_ಎಣಿಕೆ] = {
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
    ಅಕ್ಷರ * k_pchAnalogActionPaths[4] = {
        "/actions/virtualgamepad/in/stick_left",
        "/actions/virtualgamepad/in/stick_right",
        "/actions/virtualgamepad/in/trigger_left",
        "/actions/virtualgamepad/in/trigger_right",
    };

    ಆದರೆ ((e = videodata->o_ಒಳಹರಿವು->Get_Action_ಗಣ_Handle("/actions/virtualgamepad", &videodata->ಒಳಹರಿವು_action_ಗಣ)) != EVRInputError_VRInputError_None)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get action set handle: %d", e);
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to get action set handle");
    }

    videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ = SDL_arraysize(k_pchBooleanActionPaths);
    videodata->ಒಳಹರಿವು_action_handles_buttons = SDL_malloc(videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ * ಗಾತ್ರ(VRActionHandle_t));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ; i++)
    {
        e = videodata->o_ಒಳಹರಿವು->GetActionHandle(k_pchBooleanActionPaths[i], &videodata->ಒಳಹರಿವು_action_handles_buttons[i]);
        ಆದರೆ (e)
        {
            SDL_Log("ERROR: Failed to get button action %d ('%s')", i, k_pchBooleanActionPaths[i]);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ERROR: Failed to get button action");
        }
    }

    videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ = SDL_arraysize(k_pchAnalogActionPaths);
    videodata->ಒಳಹರಿವು_action_handles_axes = SDL_malloc(videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ * ಗಾತ್ರ(VRActionHandle_t));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ; i++)
    {
        e = videodata->o_ಒಳಹರಿವು->GetActionHandle(k_pchAnalogActionPaths[i], &videodata->ಒಳಹರಿವು_action_handles_axes[i]);
        ಆದರೆ (e)
        {
            SDL_Log("ERROR: Failed to get analog action %d ('%s')", i, k_pchAnalogActionPaths[i]);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ERROR: Failed to get analog action");
        }
    }

    e  = videodata->o_ಒಳಹರಿವು->GetActionHandle("/actions/virtualgamepad/out/haptic_left", &videodata->ಒಳಹರಿವು_action_handles_haptics[0]);
    e |= videodata->o_ಒಳಹರಿವು->GetActionHandle("/actions/virtualgamepad/out/haptic_right", &videodata->ಒಳಹರಿವು_action_handles_haptics[1]);
    ಆದರೆ (e)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
        SDL_Log("ERROR: Failed to get haptics action");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("ERROR: Failed to get haptics action");
    }

    // Create a virtual joystick.
    SDL_INIT_INTERFACE(&desc);
    desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = SDL_GAMEPAD_AXIS_ಎಣಿಕೆ;
    desc.nbuttons = SDL_GAMEPAD_BUTTON_ಎಣಿಕೆ;
    desc.Rumble = OPENVR_VirtualControllerRumble;
    desc.RumbleTriggers = OPENVR_VirtualControllerRumbleTriggers;
    desc.Update = OPENVR_VirtualControllerUpdate;
    desc.userdata = videodata;
    virtual_id = SDL_AttachVirtualJoystick(&desc);

    ಆದರೆ (!virtual_id) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OPENVR: Couldn't attach virtual joystick device: %s", SDL_GetError());
    }

    videodata->virtual_joystick = SDL_OpenJoystick(virtual_id);
    ಆದರೆ (!videodata->virtual_joystick) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OPENVR: Couldn't open virtual joystick device: %s", SDL_GetError());
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    SDL_Log("Loaded virtual joystick with %d buttons and %d axes", videodata->ಒಳಹರಿವು_action_handles_buttons_ಎಣಿಕೆ, videodata->ಒಳಹರಿವು_action_handles_axes_ಎಣಿಕೆ);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_InitializeOverlay(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    // Wait til here, to make sure we have our context setup correctly.
    ಆದರೆ (!OPENVR_InitExtensions(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Generate the overlay.
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_NAME");
        ಅಕ್ಷರ * cursorname = 0;
        ಆದರೆ (!hint) {
            hint = "sdl";
        }

        SDL_asprintf(&videodata->sOverlayName, "%s-overlay",hint);
        ಆದರೆ (!videodata->sOverlayName) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_asprintf(&cursorname, "%s-cursor",hint);
        ಆದರೆ (!cursorname) {
            ಹಿಂತಿರುಗಿ false;
        }

        EVROverlayError ಫಲಿತಾಂಶ = videodata->oOverlay->CreateDashboardOverlay(videodata->sOverlayName,
            ಕಿಟಕಿ->title, &videodata->overlayID, &videodata->thumbID);
        ಆದರೆ (ಫಲಿತಾಂಶ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create dashboard overlay (%d)", ಫಲಿತಾಂಶ );
        }
        ಫಲಿತಾಂಶ = videodata->oOverlay->CreateOverlay(cursorname, ಕಿಟಕಿ->title, &videodata->cursorID);
        ಆದರೆ (ಫಲಿತಾಂಶ != EVROverlayError_VROverlayError_None) {
            SDL_free(cursorname);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create cursor overlay (%d)", ಫಲಿತಾಂಶ );
        }
        SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
        SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_OPENVR_OVERLAY_ID_ಸಂಖ್ಯೆ, videodata->overlayID);
        SDL_free(cursorname);
        videodata->bHasShownOverlay = false;
    }
    {
        Uint32 overlay_flags = 0;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint("SDL_OPENVR_OVERLAY_FLAGS");
        ಆದರೆ (hint && *hint) {
            overlay_flags = SDL_atoi(hint);
        } ಇಲ್ಲದಿದ್ದರೆ {
            overlay_flags |= (1 << 17); //vr::VROverlayFlags_SendVRSmoothScrollEvents
            overlay_flags |= (1 << 23); //vr::VROverlayFlags_EnableControlBar
            overlay_flags |= (1 << 24); //vr::VROverlayFlags_EnableControlBarKeyboard
            overlay_flags |= (1 << 25); //vr::VROverlayFlags_EnableControlBarClose
#ಆದರೆ 0
            /* OpenVR overlays assume unpremultiplied alpha by default, set this flag to tag the source buffer as premultiplied.
             * Note that (as of 2025) OpenVR overlay composition is higher quality when premultiplied buffers are provided,
             * as texture samplers that blend energy (such as bilinear) do not yield sensical results when operating on natively
             * unpremultiplied textures. It is thus preferable to hand openvr natively premultiplied buffers when accurate
             * sampling / composition is required. */
            overlay_flags |= (1 << 21);    // vr::VROverlayFlags_IsPremultiplied
#ಆದರೆ_ಅಂತ್ಯ
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಗಾತ್ರ(overlay_flags) * 8; ++i) {
            ಆದರೆ (overlay_flags & (1 << i)) {
                videodata->oOverlay->ಗಣ_Overlay_Flag(videodata->overlayID, (VROverlayFlags)(1 << i), true);
            }
        }
    }
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint = SDL_GetHint("SDL_OPENVR_OVERLAY_PANEL_WIDTH");
        ದಶಮಾಂಶ f_ಅಗಲ = hint ? (ದಶಮಾಂಶ)SDL_atof(hint) : 1.0f;
        videodata->oOverlay->ಗಣ_Overlay_ಅಗಲ_ಒಳ_Meters(videodata->overlayID, f_ಅಗಲ);
    }
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint = SDL_GetHint("SDL_OPENVR_CURSOR_WIDTH");
        // Default is what SteamVR Does
        ದಶಮಾಂಶ f_Cursor_ಅಗಲ = hint ? (ದಶಮಾಂಶ)SDL_atof(hint) : 0.06f;
        videodata->oOverlay->ಗಣ_Overlay_ಅಗಲ_ಒಳ_Meters(videodata->cursorID, f_Cursor_ಅಗಲ * 0.5f);
    }
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * hint = SDL_GetHint("SDL_OPENVR_WINDOW_ICON_FILE");
        videodata->bIconOverridden = false;
        ಆದರೆ (hint) {
            ಅಕ್ಷರ * tmpcopy = SDL_strdup(hint);
            EVROverlayError err = videodata->oOverlay->ಗಣ_Overlay_From_File(videodata->thumbID, tmpcopy);
            SDL_free(tmpcopy);
            ಆದರೆ (err == EVROverlayError_VROverlayError_None) {
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
        videodata->oOverlay->ಗಣ_Overlay_Texture_Bounds(videodata->overlayID, &bounds);
    }

    ಆದರೆ (!OPENVR_CheckRenderbuffer(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    global_openvr_driver = videodata;
    InitializeMouseFunctions();

    // Actually show the overlay.
    videodata->oOverlay->ಗಣ_Overlay_Name(videodata->overlayID, ಕಿಟಕಿ->title);

    videodata->bDidCreateOverlay = true;
    videodata->ಕಿಟಕಿ = ಕಿಟಕಿ;

    ಹಿಂತಿರುಗಿ true;
}


ಸ್ಥಿರ bool OPENVR_ಸಿದ್ಧತೆ_ಚೌಕಟ್ಟು(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ GLenum buffers[8] = { GL_COLOR_ATTACHMENT0_EXT };

    videodata->is_ಬಫರ್_rendering = true;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಂಕ error = ov_glGetError();
        ಆದರೆ (error)
            SDL_Log("Found GL Error before beginning frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_ಸ್ಥಿತಿ(videodata->fbo, GL_FRAMEBUFFER));
    }
#ಆದರೆ_ಅಂತ್ಯ

    ov_glBindFramebuffer(GL_FRAMEBUFFER, videodata->fbo);
    ov_glDrawBuffers(1, buffers);

    // Set the alpha channel for non-transparent windows
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT)) {
        ov_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ov_gl_Color_ಮುಖವಾಡ(false, false, false, true);
        ov_glClear(GL_COLOR_ಬಫರ್_ಬಿಟ್);
        ov_gl_Color_ಮುಖವಾಡ(true, true, true, true);
    }

    ov_glBindTexture( GL_TEXTURE_2D, videodata->saved_texture_state );

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_Release_ಚೌಕಟ್ಟು(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ov_glGetIntegerv(GL_TEXTURE_BINDING_2D, &videodata->saved_texture_state);

    ಆದರೆ (!ov_glGetError) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!videodata->is_ಬಫರ್_rendering) {
        ಹಿಂತಿರುಗಿ true;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಂಕ error = ov_glGetError();
        ಆದರೆ (error) {
            SDL_Log("Found GL Error before release frame: %d / (Framebuffer:%d)", error, ov_gl_Check_Named_Framebuffer_ಸ್ಥಿತಿ(videodata->fbo, GL_FRAMEBUFFER));
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    videodata->is_ಬಫರ್_rendering = false;

    ov_glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ಆದರೆ (videodata->overlaytexture != 0 &&
        videodata->targh == videodata->ಕೊನೆಯ_targh &&
        videodata->targw == videodata->ಕೊನೆಯ_targw) {
        // Only submit frames to OpenVR if the texture exists.
        ರಚನೆ Texture_t tex;

        // Setup a Texture_t object to send in the texture.
        tex.eColorSpace = EColorSpace_ColorSpace_Auto;
        tex.eType = ETextureType_TextureType_OpenGL;
        tex.handle = (ಶೂನ್ಯ *)(intptr_t)videodata->overlaytexture;

        // Send texture into OpenVR as the overlay.
        videodata->oOverlay->ಗಣ_Overlay_Texture(videodata->overlayID, &tex);
    }

    ಆದರೆ (!videodata->bHasShownOverlay && videodata->bDidCreateOverlay) {
        videodata->oOverlay->ShowDashboard(videodata->sOverlayName);
        videodata->bHasShownOverlay = true;
    }

    ಆದರೆ (videodata->renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ) {
        ov_gl_Debug_ಸಂದೇಶ_ಸೇರಿಸು(GL_DEBUG_ಮೂಲ_APPLICATION,
            GL_DEBUG_TYPE_MARKER, MARKER_ID, GL_DEBUG_SEVERITY_NOTIFICATION, -1,
            MARKER_STR);
    }

    ಹಿಂತಿರುಗಿ OPENVR_CheckRenderbuffer(_this);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HandleResize(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ದತ್ತಾಂಶ->targw = w;
    ದತ್ತಾಂಶ->targh = h;
}

ಸ್ಥಿರ bool OPENVR_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    ಹಿಂತಿರುಗಿ true;
}


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
ಸ್ಥಿರ LRESULT CALLBACK OpenVRVideoWndProc(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM lParam)
{
    ಆಯ್ಕೆ (ಸಂದೇಶ_2) {
    ಸ್ಥಿತಿ WM_DESTROY:
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ Def_ಕಿಟಕಿ_Proc(hwnd, ಸಂದೇಶ_2, wParam, lParam);
}

ಸ್ಥಿರ bool OPENVR_GL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = SDL_GetHint(SDL_HINT_OPENGL_LIBRARY);
    }

    ಆದರೆ (ಮಾರ್ಗ == ಖಾಲಿ) {
        ಮಾರ್ಗ = DEFAULT_OPENGL;
    }
    _this->gl_config.dll_handle = SDL_ತುಂಬು_Object(ಮಾರ್ಗ);
    ಆದರೆ (!_this->gl_config.dll_handle) {
        ಹಿಂತಿರುಗಿ false;
    }
    SDL_strlcpy(_this->gl_config.driver_ಮಾರ್ಗ, ಮಾರ್ಗ,
                 SDL_arraysize(_this->gl_config.driver_ಮಾರ್ಗ));

    // Allocate OpenGL memory
    _this->gl_ದತ್ತಾಂಶ = (ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(ರಚನೆ SDL_GLDriver_ದತ್ತಾಂಶ));
    ಆದರೆ (!_this->gl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }
    _this->gl_config.driver_loaded = true;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ SDL_Function_ಸೂಚಕ OPENVR_GL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    SDL_Function_ಸೂಚಕ ಫಲಿತಾಂಶ = ಖಾಲಿ;
    ಆದರೆ (ov_wgl_Get_Proc_ವಿಳಾಸ) {
        ಫಲಿತಾಂಶ = (SDL_Function_ಸೂಚಕ)ov_wgl_Get_Proc_ವಿಳಾಸ(proc);
        ಆದರೆ (ಫಲಿತಾಂಶ) {
            ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_Function(_this->gl_config.dll_handle, proc);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_GL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_GL_UnloadLibrary();
}

ಸ್ಥಿರ SDL_GLContext OPENVR_GL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    GLint ಅಂಕೆ_Extensions;
    ಪೂರ್ಣಾಂಕ i;
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (!videodata->hglrc) {
        // Create a surfaceless EGL Context
        HWND hwnd;

        WNDCLASSA wnd;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wnd.lpfnWndProc = OpenVRVideoWndProc;
        wnd.cbClsExtra = 0;
        wnd.cbWndExtra = 0;
        wnd.hInstance = GetModuleHandle(ಖಾಲಿ);
        wnd.hIcon = ತುಂಬು_Icon(ಖಾಲಿ, IDI_APPLICATION);
        wnd.hCursor = ತುಂಬು_Cursor(ಖಾಲಿ, IDC_ARROW);
        wnd.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wnd.lpszMenuName = ಖಾಲಿ;
        wnd.lpszClassName = "SDL_openvrvideo_classname";
        ರಿಜಿಸ್ಟರ್_Class_A(&wnd);
        hwnd = Create_ಕಿಟಕಿ_A("SDL_openvrvideo_classname", "SDL_openvrvideo_windowname", (WS_OVERLAPPEDWINDOW), 0, 0,
                              100, 100, ಖಾಲಿ, ಖಾಲಿ, GetModuleHandle(ಖಾಲಿ), ಖಾಲಿ);

        ಸಂದೇಶ_3 ಸಂದೇಶ_2;
        ಆಗ (Peek_ಸಂದೇಶ(&ಸಂದೇಶ_2, ಖಾಲಿ, 0, 0, PM_REMOVE)) {
            Translate_ಸಂದೇಶ(&ಸಂದೇಶ_2);
            Dispatch_ಸಂದೇಶ(&ಸಂದೇಶ_2);
        }

        videodata->hdc = GetDC(hwnd);

        ಸ್ಥಿರ  PIXELFORMATDESCRIPTOR pfd =
        {
            ಗಾತ್ರ(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_ಗಮ್ಯ_ಕಿಟಕಿ |
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
        GLuint PixelFormat = ಆರಿಸು_Pixel_Format(videodata->hdc, &pfd);
        ಆದರೆ (!ಗಣ_Pixel_Format(videodata->hdc, PixelFormat, &pfd)) {
            SDL_ಗಣ_Error( "Could not set pixel format" );
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        HMODULE opengl = GetModuleHandleA(DEFAULT_OPENGL);
        ಆದರೆ (!opengl) {
            SDL_ಗಣ_Error("Could not open OpenGL Library %s", DEFAULT_OPENGL);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ov_wglMakeCurrent = (BOOL(*)(HDC, HGLRC))Get_Proc_ವಿಳಾಸ(opengl, "wglMakeCurrent");
        ov_wglCreateContext = (HGLRC(*)(HDC))Get_Proc_ವಿಳಾಸ(opengl, "wglCreateContext");
        ov_wgl_Get_Proc_ವಿಳಾಸ = (PROC(*)(LPCSTR))Get_Proc_ವಿಳಾಸ(opengl, "wglGetProcAddress");
        ov_wglDeleteContext = (BOOL(*)(HGLRC))Get_Proc_ವಿಳಾಸ(opengl, "wglDeleteContext");
        ಆದರೆ (!ov_wglMakeCurrent || !ov_wglCreateContext) {
            SDL_ಗಣ_Error("Cannot get wgl context procs(%p, %p)", ov_wglMakeCurrent, ov_wglCreateContext);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        videodata->hglrc = ov_wglCreateContext(videodata->hdc);
        ಆದರೆ (!videodata->hglrc || !ov_wglMakeCurrent(videodata->hdc, videodata->hglrc)) {
            SDL_ಗಣ_Error("Could not make current OpenGL context.");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    i = OPENVR_InitExtensions(_this);
    ಆದರೆ (i == 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    videodata->renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ = false;

    ov_glGetIntegerv(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_Extensions);
    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_Extensions; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ccc = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ಆದರೆ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
            SDL_Log("Found renderdoc debug extension.");
#ಆದರೆ_ಅಂತ್ಯ
            videodata->renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ = true;
        }
    }

    ಆದರೆ (!videodata->bDidCreateOverlay) {
        ಆದರೆ (!OPENVR_InitializeOverlay(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_ಸಿದ್ಧತೆ_ಚೌಕಟ್ಟು(_this, ಕಿಟಕಿ);

    SDL_GLContext ಫಲಿತಾಂಶ = SDL_malloc(ಗಾತ್ರ(ರಚನೆ SDL_GLContextState));
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಫಲಿತಾಂಶ->hglrc = videodata->hglrc;
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ bool OPENVR_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *wnd, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ov_wglMakeCurrent(videodata->hdc, videodata->hglrc);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_GL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    videodata->ಅದಲುಬದಲು_interval = interval;
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_GL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *ಅದಲುಬದಲು_Interval)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (ಅದಲುಬದಲು_Interval)
        *ಅದಲುಬದಲು_Interval = videodata->ಅದಲುಬದಲು_interval;
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OPENVR: null passed in for GetSwapInterval");
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ov_wglMakeCurrent(videodata->hdc, ಖಾಲಿ);
    ov_wglDeleteContext(videodata->hglrc);
    ಹಿಂತಿರುಗಿ true;
}


#ಇಲ್ಲದಿದ್ದರೆ

ಸ್ಥಿರ EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_ಆವೃತ್ತಿ, 2,
    EGL_NONE
};

ಸ್ಥಿರ bool SDL_EGL_Init_ಆಂತರಿಕ(SDL_Video_ದತ್ತಾಂಶ * vd)
{
    // Create a surfaceless EGL Context
    EGLint major, minor;
    EGLConfig eglCfg=ಖಾಲಿ;
    EGLBoolean b;

    vd->eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    SDL_Log("EGL Display: %p", vd->eglDpy);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (vd->eglDpy == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No EGL Display");
    }

    b = eglInitialize(vd->eglDpy, &major, &minor);
    ಆದರೆ (!b) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglInitialize failed");
    }

    eglBindAPI(EGL_OPENGL_API);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    SDL_Log("EGL Major Minor: %d %d = %d", major, minor, b);
#ಆದರೆ_ಅಂತ್ಯ

    vd->eglCtx = eglCreateContext(vd->eglDpy, eglCfg, EGL_NO_CONTEXT, context_attribs);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    {
        ಪೂರ್ಣಾಂಕ err = eglGetError();
        ಆದರೆ (err != EGL_SUCCESS) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL Error after eglCreateContext %d", err);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!vd->eglCtx) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No EGL context available");
    }

    eglMakeCurrent(vd->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, vd->eglCtx);

    ಹಿಂತಿರುಗಿ true;
}

// Linux, EGL, etc.
ಸ್ಥಿರ bool OVR_EGL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, EGL_DEFAULT_DISPLAY);
}

ಸ್ಥಿರ SDL_Function_ಸೂಚಕ OVR_EGL_Get_Proc_ವಿಳಾಸ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    ಹಿಂತಿರುಗಿ SDL_EGL_Get_Proc_ವಿಳಾಸ(proc);
}
ಸ್ಥಿರ ಶೂನ್ಯ OVR_EGL_UnloadLibrary(SDL_VideoDevice *_this)
{
    SDL_EGL_UnloadLibrary(_this);
}
ಸ್ಥಿರ SDL_GLContext OVR_EGL_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    GLint ಅಂಕೆ_Extensions;
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (!videodata->eglCtx) {
        ಆದರೆ (!SDL_EGL_Init_ಆಂತರಿಕ(videodata)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ (!OPENVR_InitExtensions(_this)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    videodata->renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ = false;

    ov_glGetIntegerv(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_Extensions);
    ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_Extensions; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ccc = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ov_glGetStringi(GL_EXTENSIONS, i);
        ಆದರೆ (SDL_strcmp(ccc, "GL_KHR_debug") == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
           SDL_Log("Found renderdoc debug extension.");
#ಆದರೆ_ಅಂತ್ಯ
           videodata->renderdoc_debugmarker_ಚೌಕಟ್ಟು_ಕೊನೆ = true;
        }
    }

    ಆದರೆ (!videodata->bDidCreateOverlay) {
        ಆದರೆ (!OPENVR_InitializeOverlay(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    OPENVR_CheckRenderbuffer(_this);

    OPENVR_ಸಿದ್ಧತೆ_ಚೌಕಟ್ಟು(_this, ಕಿಟಕಿ);

    ಹಿಂತಿರುಗಿ videodata->eglCtx;
}

ಸ್ಥಿರ bool OVR_EGL_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * wnd, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    eglMakeCurrent(videodata->eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, videodata->eglCtx);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OVR_EGL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    videodata->ಅದಲುಬದಲು_interval = interval;
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OVR_EGL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ * ಅದಲುಬದಲು_Interval)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (ಅದಲುಬದಲು_Interval)
        *ಅದಲುಬದಲು_Interval = videodata->ಅದಲುಬದಲು_interval;
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OPENVR: null passed in for GetSwapInterval");
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OVR_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->eglDpy) {
        eglTerminate(videodata->eglDpy);
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool OPENVR_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Allocate window internal data
    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (ದತ್ತಾಂಶ == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
    }

    ಕಿಟಕಿ->max_w = 4096;
    ಕಿಟಕಿ->max_h = 4096;
    ಕಿಟಕಿ->min_w = 1;
    ಕಿಟಕಿ->min_h = 1;

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ಹಿಂತಿರುಗಿ true;
}


ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_free(ದತ್ತಾಂಶ);
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ * ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->bDidCreateOverlay) {
        ದತ್ತಾಂಶ->oOverlay->ಗಣ_Overlay_Name(ದತ್ತಾಂಶ->overlayID, ಕಿಟಕಿ->title);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    ಆದರೆ (ಕಿಟಕಿ->pending.w != ಕಿಟಕಿ->w) {
        ಕಿಟಕಿ->w = ಕಿಟಕಿ->pending.w;
    }

    ಆದರೆ (ಕಿಟಕಿ->pending.h != ಕಿಟಕಿ->h) {
        ಕಿಟಕಿ->h = ಕಿಟಕಿ->pending.h;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->targh != ಕಿಟಕಿ->h || ದತ್ತಾಂಶ->targw != ಕಿಟಕಿ->w) {
        OPENVR_HandleResize(_this, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
    }

    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    *w = ದತ್ತಾಂಶ->targw;
    *h = ದತ್ತಾಂಶ->targh;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->targh != ಕಿಟಕಿ->h || ದತ್ತಾಂಶ->targw != ಕಿಟಕಿ->w) {
        OPENVR_HandleResize(_this, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
    }

    ದತ್ತಾಂಶ->oOverlay->ShowDashboard(ದತ್ತಾಂಶ->sOverlayName);

    ಕಿಟಕಿ->flags |= (SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS | SDL_ಕಿಟಕಿ_MOUSE_FOCUS);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ bool OPENVR_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    // This is a little weird.   On Windows, we don't necessarily call the normal
    // context creation function, and we might get here without having our buffers
    // initialized.
    ಆದರೆ (!videodata->bDidCreateOverlay) {
        ಆದರೆ (!OPENVR_InitializeOverlay(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಆದರೆ (!OPENVR_Release_ಚೌಕಟ್ಟು(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // If swap_interval is nonzero (i.e. -1 or 1) we want to wait for vsync on the compositor.
    ಆದರೆ (videodata->ಅದಲುಬದಲು_interval != 0) {
        videodata->oOverlay->Wait_ಚೌಕಟ್ಟು_Sync(100);
    }

    ಆದರೆ (!OPENVR_ಸಿದ್ಧತೆ_ಚೌಕಟ್ಟು(_this, ಕಿಟಕಿ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ Uint8 OPENVR_MapMouseButton(ಪೂರ್ಣಾಂಕ btn)
{
    ಆದರೆ (btn == EVRMouse_Button_VRMouse_Button_ಬಲ) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಬಲ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (btn == EVRMouse_Button_VRMouse_Button_ಮಧ್ಯ) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಮಧ್ಯ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಎಡ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HandleMouse(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, ಪೂರ್ಣಾಂಕ btn, ಪೂರ್ಣಾಂಕ evt)
{
    ಆದರೆ (evt == 2) {
        SDL_SendMouseMotion(0, ಖಾಲಿ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ Uint8 button = OPENVR_MapMouseButton(btn);
        ಸ್ಥಿರಾಂಕ bool ಕೆಳಕ್ಕೆ = (evt != 0);
        SDL_SendMouseButton(0, ಖಾಲಿ, SDL_GLOBAL_MOUSE_ID, button, ಕೆಳಕ್ಕೆ);
    }
}


ಸ್ಥಿರ bool OPENVR_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (!videodata ||
        videodata->oOverlay == 0 ||
        videodata->overlayID == 0) {
        ಹಿಂತಿರುಗಿ;
    }
    EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ ಒಳಹರಿವು_ಬಹುಲಕ;
    ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_HIDDEN:
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        ಒಳಹರಿವು_ಬಹುಲಕ = EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_Password;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಒಳಹರಿವು_ಬಹುಲಕ = EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಬಹುಲಕ_ಸಾಮಾನ್ಯ;
        ನಿಲ್ಲಿಸು;
    }
    EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ ಸಾಲು_ಬಹುಲಕ;
    ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(props)) {
        ಸಾಲು_ಬಹುಲಕ = EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_ಅಪವರ್ತ್ಯ_ಸಾಲುಗಳು;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸಾಲು_ಬಹುಲಕ = EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_k_EGamepad_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಾಲು_ಬಹುಲಕ_Single_ಸಾಲು;
    }
    videodata->oOverlay->ShowKeyboardForOverlay(videodata->overlayID,
           ಒಳಹರಿವು_ಬಹುಲಕ, ಸಾಲು_ಬಹುಲಕ,
           EKeyboard_Flags_Keyboard_Flag_ಕನಿಷ್ಠತಮ, "Virtual Keyboard", 128, "", 0);
    SDL_SendScreenKeyboardShown();
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    videodata->oOverlay->HideKeyboard();
    SDL_SendScreenKeyboardHidden();
}

ಸ್ಥಿರ SDL_Cursor *OPENVR_CreateCursor(SDL_Surface * surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Cursor *ಫಲಿತಾಂಶ = SDL_calloc(1, ಗಾತ್ರ(SDL_Cursor));
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    uint32_t * pixels = ImageSDLToOpenVRGL(surface, false);
    SDL_Cursor_ದತ್ತಾಂಶ *ovrc = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ovrc));
    ಆದರೆ (!ovrc) {
        SDL_free(ಫಲಿತಾಂಶ);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಫಲಿತಾಂಶ->ಆಂತರಿಕ = ovrc;

    ov_glGenTextures(1, &ovrc->texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, ovrc->texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    ovrc->hot_x = hot_x;
    ovrc->hot_y = hot_y;
    ovrc->w = surface->w;
    ovrc->h = surface->h;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ bool OPENVR_ShowCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ * ovrc;
    EVROverlayError e;
    Texture_t texture;
    HmdVector2_t hotspot;
    VRTextureBounds_t tb;

    ಆದರೆ (!cursor) {
        global_openvr_driver->oOverlay->ಗಣ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, true);
        e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Cursor(global_openvr_driver->overlayID, k_ulOverlayHandleInvalid);
        ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
            ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
        }
        ಹಿಂತಿರುಗಿ true;
    }

    global_openvr_driver->oOverlay->ಗಣ_Overlay_Flag(global_openvr_driver->overlayID, VROverlayFlags_HideLaserIntersection, false);

    ovrc = cursor->ಆಂತರಿಕ;

    ಆದರೆ (!ovrc) {
        // Sometimes at boot there is a race condition where this is not ready.
        ಹಿಂತಿರುಗಿ true;
    }

    hotspot.v[0] = (ದಶಮಾಂಶ)ovrc->hot_x / (ದಶಮಾಂಶ)ovrc->w;
    hotspot.v[1] = (ದಶಮಾಂಶ)ovrc->hot_y / (ದಶಮಾಂಶ)ovrc->h;

    texture.handle = (ಶೂನ್ಯ *)(intptr_t)(ovrc->texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    tb.uMin = 0;
    tb.uMax = 1;
    tb.vMin = 1;
    tb.vMax = 0;

    e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Texture_Bounds(global_openvr_driver->cursorID, &tb);
    ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
        ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Transform_Cursor(global_openvr_driver->cursorID, &hotspot);
    ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
        ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Texture(global_openvr_driver->cursorID, &texture);
    ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
        ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
    }

    e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Cursor(global_openvr_driver->overlayID, global_openvr_driver->cursorID);
    ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
        ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_FreeCursor(SDL_Cursor * cursor)
{
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ovrc = cursor->ಆಂತರಿಕ;
        ಆದರೆ (ovrc) {
            ov_glDeleteTextures(1, &ovrc->texture_id_handle);
            SDL_free(ovrc);
        }
        SDL_free(cursor);
    }
}


ಸ್ಥಿರ bool OPENVR_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_Surface * icon)
{
    ಆದರೆ (!global_openvr_driver) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenVR Overlay not initialized");
    }

    ಚಿಹ್ನೆರಹಿತ texture_id_handle;
    EVROverlayError e;
    Texture_t texture;
    uint32_t * pixels;
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಆದರೆ (videodata->bIconOverridden) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenVR Icon is overridden.");
    }

    pixels = ImageSDLToOpenVRGL(icon, true);

    ov_glGenTextures(1, &texture_id_handle);
    ov_glBindTexture(GL_TEXTURE_2D, texture_id_handle);
    ov_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, icon->w, icon->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    SDL_free(pixels);
    ov_glBindTexture(GL_TEXTURE_2D, 0);

    texture.handle = (ಶೂನ್ಯ *)(intptr_t)(texture_id_handle);
    texture.eType = ETextureType_TextureType_OpenGL;
    texture.eColorSpace = EColorSpace_ColorSpace_Auto;

    e = global_openvr_driver->oOverlay->ಗಣ_Overlay_Texture(videodata->thumbID, &texture);
    ಆದರೆ (e != EVROverlayError_VROverlayError_None) {
        ಹಿಂತಿರುಗಿ OPENVR_ಗಣ_Overlay_Error(e);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OPENVR_Show_ಸಂದೇಶ_Box(SDL_VideoDevice *_this,ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonid)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ಅಕ್ಷರ ಖಾಲಿಗಳು = 0;
    ಅಕ್ಷರ * ಸಂದೇಶ = SDL_strdup(messageboxdata->ಸಂದೇಶ?messageboxdata->ಸಂದೇಶ:"");
    ಅಕ್ಷರ * title = SDL_strdup(messageboxdata->ಸಂದೇಶ?messageboxdata->ಸಂದೇಶ:"");
    ಅಕ್ಷರ * ok = SDL_strdup("Ok");
    videodata->oOverlay->Show_ಸಂದೇಶ_Overlay(ಸಂದೇಶ, title, ok, &ಖಾಲಿಗಳು, &ಖಾಲಿಗಳು, &ಖಾಲಿಗಳು);
    SDL_free(ok);
    SDL_free(title);
    SDL_free(ಸಂದೇಶ);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ InitializeMouseFunctions(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->CreateCursor = OPENVR_CreateCursor;
    mouse->ShowCursor = OPENVR_ShowCursor;
    mouse->FreeCursor = OPENVR_FreeCursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENVR_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;
    ರಚನೆ VREvent_t nEvent;
    ಆದರೆ (videodata->overlayID) {
        ಆಗ (videodata->oOverlay->Poll_ಮುಂದಿನ_Overlay_Event(videodata->overlayID, &nEvent, ಗಾತ್ರ(nEvent))) {
            ಆಯ್ಕೆ (nEvent.eventType) {
            ಸ್ಥಿತಿ EVREventType_VREvent_ButtonPress:
            ಸ್ಥಿತಿ EVREventType_VREvent_ButtonUnpress:
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREventType_VREvent_MouseMove:
                OPENVR_HandleMouse(nEvent.ದತ್ತಾಂಶ.mouse.x, videodata->targh - nEvent.ದತ್ತಾಂಶ.mouse.y, nEvent.ದತ್ತಾಂಶ.mouse.button, 2);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREvent_Type_VREvent_Mouse_Button_ಕೆಳಕ್ಕೆ:
                OPENVR_HandleMouse(nEvent.ದತ್ತಾಂಶ.mouse.x, videodata->targh - nEvent.ದತ್ತಾಂಶ.mouse.y, nEvent.ದತ್ತಾಂಶ.mouse.button, 1);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREvent_Type_VREvent_Mouse_Button_ಮೇಲೆ:
                OPENVR_HandleMouse(nEvent.ದತ್ತಾಂಶ.mouse.x, videodata->targh - nEvent.ದತ್ತಾಂಶ.mouse.y, nEvent.ದತ್ತಾಂಶ.mouse.button, 0);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREventType_VREvent_ScrollSmooth:
            ಸ್ಥಿತಿ EVREventType_VREvent_ScrollDiscrete:
                SDL_SendMouseWheel(0, ಖಾಲಿ, SDL_GLOBAL_MOUSE_ID, -nEvent.ದತ್ತಾಂಶ.scroll.xdelta, nEvent.ದತ್ತಾಂಶ.scroll.ydelta, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREvent_Type_VREvent_Keyboard_Char_ಒಳಹರಿವು:
                SDL_Send_Keyboard_Unicode_ಕೀಲಿ(SDL_GetTicksNS(), nEvent.ದತ್ತಾಂಶ.keyboard.c_New_ಒಳಹರಿವು[0]);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREventType_VREvent_OverlayShown:
                SDL_ಗಣ_Keyboard_Focus(videodata->ಕಿಟಕಿ);
                SDL_Send_ಕಿಟಕಿ_Event(videodata->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
                SDL_Send_ಕಿಟಕಿ_Event(videodata->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREventType_VREvent_OverlayHidden:
                SDL_Send_ಕಿಟಕಿ_Event(videodata->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HIDDEN, 0, 0);
                SDL_Send_ಕಿಟಕಿ_Event(videodata->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
                SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ EVREventType_VREvent_OverlayClosed:
            ಸ್ಥಿತಿ EVREventType_VREvent_Quit:
                SDL_SendQuit();
                ನಿಲ್ಲಿಸು;
            }
        }
    }
}


ಸ್ಥಿರ SDL_VideoDevice *OPENVR_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_WINDOWS
    SDL_ರಿಜಿಸ್ಟರ್_App(ಖಾಲಿ, 0, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (device) {
        ದತ್ತಾಂಶ = (ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ = ಖಾಲಿ;
    }
    ಆದರೆ (!ದತ್ತಾಂಶ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_WINDOWS
        SDL_UnregisterApp();
#ಆದರೆ_ಅಂತ್ಯ
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    hint = SDL_GetHint(SDL_HINT_OPENVR_LIBRARY);
    ಆದರೆ (hint) {
        ದತ್ತಾಂಶ->openVRLIB = SDL_ತುಂಬು_Object(hint);
    }
    ಆದರೆ (!ದತ್ತಾಂಶ->openVRLIB) {
        ದತ್ತಾಂಶ->openVRLIB = SDL_ತುಂಬು_Object(SDL_OPENVR_DRIVER_DYNAMIC);
    }
    ಆದರೆ (!ದತ್ತಾಂಶ->openVRLIB) {
        SDL_ಗಣ_Error("Could not open OpenVR API Library");
        ಹೋಗು error;
    }

    ದತ್ತಾಂಶ->FN_VR_Init_ಆಂತರಿಕ = (intptr_t(*)(EVRInitError * peError, EVRApplicationType eType))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->openVRLIB, "VR_InitInternal");
    ದತ್ತಾಂಶ->FN_VR_GetVRInitErrorAsEnglishDescription = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(*)(EVRInitError error))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->openVRLIB, "VR_GetVRInitErrorAsEnglishDescription");
    ದತ್ತಾಂಶ->FN_VR_GetGenericInterface = (intptr_t (*)(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pch_Interface_ಆವೃತ್ತಿ, EVRInitError * peError))SDL_ತುಂಬು_Function(ದತ್ತಾಂಶ->openVRLIB, "VR_GetGenericInterface");
    ಆದರೆ (!ದತ್ತಾಂಶ->FN_VR_Init_ಆಂತರಿಕ || !ದತ್ತಾಂಶ->FN_VR_GetVRInitErrorAsEnglishDescription || !ದತ್ತಾಂಶ->FN_VR_GetGenericInterface) {
        ಹೋಗು error;
    }

    ಅಕ್ಷರ fnname[128];
    EVRInitError e;
    ದತ್ತಾಂಶ->vrtoken = ದತ್ತಾಂಶ->FN_VR_Init_ಆಂತರಿಕ(&e, EVRApplicationType_VRApplication_Overlay);
    ಆದರೆ (!ದತ್ತಾಂಶ->vrtoken) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *err = "Can't get english description";
        ಆದರೆ (ದತ್ತಾಂಶ->FN_VR_GetVRInitErrorAsEnglishDescription != ಖಾಲಿ)
            err = ದತ್ತಾಂಶ->FN_VR_GetVRInitErrorAsEnglishDescription(e);
        SDL_ಗಣ_Error("Could not generate OpenVR Context (%s)", err);
        ಹೋಗು error;
    }

    SDL_snprintf(fnname, 127, "FnTable:%s", IVRSystem_ಆವೃತ್ತಿ);
    ದತ್ತಾಂಶ->oSystem = (ರಚನೆ VR_IVRSystem_Fn_ಕೋಷ್ಟಕ *)ದತ್ತಾಂಶ->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVROverlay_ಆವೃತ್ತಿ);
    ದತ್ತಾಂಶ->oOverlay = (ರಚನೆ VR_IVROverlay_Fn_ಕೋಷ್ಟಕ *)ದತ್ತಾಂಶ->FN_VR_GetGenericInterface(fnname, &e);
    SDL_snprintf(fnname, 127, "FnTable:%s", IVRInput_ಆವೃತ್ತಿ);
    ದತ್ತಾಂಶ->o_ಒಳಹರಿವು = (ರಚನೆ VR_IVRInput_Fn_ಕೋಷ್ಟಕ *)ದತ್ತಾಂಶ->FN_VR_GetGenericInterface(fnname, &e);

    ಆದರೆ (!ದತ್ತಾಂಶ->oOverlay || !ದತ್ತಾಂಶ->oSystem || !ದತ್ತಾಂಶ->o_ಒಳಹರಿವು) {
        SDL_ಗಣ_Error("Could not get interfaces for the OpenVR System (%s), Overlay (%s) and Input (%s) versions", IVRSystem_ಆವೃತ್ತಿ, IVROverlay_ಆವೃತ್ತಿ, IVRInput_ಆವೃತ್ತಿ);
    }

    hint = SDL_GetHint("SDL_OPENVR_INPUT_PROFILE");
    ಅಕ್ಷರ *loadpath = 0;
    EVRInputError err;

    ಆದರೆ (hint) {
        SDL_asprintf(&loadpath, "%s", hint);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *basepath = SDL_Get_ತಳ_ಮಾರ್ಗ();
        SDL_asprintf(&loadpath, "%ssdloverlay_actions.json", basepath);
    }
    ಆದರೆ (!loadpath) {
        ಹೋಗು error;
    }

    err = ದತ್ತಾಂಶ->o_ಒಳಹರಿವು->ಗಣ_Action_Manifest_ಮಾರ್ಗ(loadpath);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_OPENVR
    SDL_Log("Loaded action manifest at %s (%d)", loadpath, err);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_free(loadpath);
    ಆದರೆ (err != EVRInputError_VRInputError_None) {
        // I know we don't normally log, but this _really_ should be percolated
        // up as far as we can.
        SDL_Log("Could not load action manifest path");
        // If we didn't have a hint, this is a soft fail.
        // If we did have the hint, then it's a hard fail.
        ಆದರೆ (hint) {
            ಹೋಗು error;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ(!OPENVR_ಸಿದ್ಧತೆ_Joystick_Based_On_Loaded_Action_Manifest(ದತ್ತಾಂಶ)) {
            ಹೋಗು error;
        }
    }

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಬಿಡುಗಡೆ = OPENVR_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;
    device->ಗಣ_Display_ಬಹುಲಕ = OPENVR_ಗಣ_Display_ಬಹುಲಕ;
    device->CreateSDLWindow = OPENVR_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = OPENVR_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = OPENVR_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels = OPENVR_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels;
    device->Show_ಕಿಟಕಿ = OPENVR_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = OPENVR_Hide_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = OPENVR_Destroy_ಕಿಟಕಿ;
    device->Show_ಸಂದೇಶ_Box = OPENVR_Show_ಸಂದೇಶ_Box;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_WGL
    device->GL_ತುಂಬು_Library = OPENVR_GL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = OPENVR_GL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = OPENVR_GL_UnloadLibrary;
    device->GL_CreateContext = OPENVR_GL_CreateContext;
    device->GL_MakeCurrent = OPENVR_GL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = OPENVR_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = OPENVR_GL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = OPENVR_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = OPENVR_GL_DestroyContext;
#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ Needs ಇನ್ನಷ್ಟು work ಗಮ್ಯ support EGL
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
    device->GL_ತುಂಬು_Library = OVR_EGL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = OVR_EGL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = OVR_EGL_UnloadLibrary;
    device->GL_CreateContext = OVR_EGL_CreateContext;
    device->GL_MakeCurrent = OVR_EGL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = OVR_EGL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = OVR_EGL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_DestroyContext = OVR_EGL_DestroyContext;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = OPENVR_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_VIDEO_VULKAN) && defined(SDL_VIDEO_DRIVER_WINDOWS)
    device->Vulkan_ತುಂಬು_Library = WIN_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = WIN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = WIN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = WIN_Vulkan_CreateSurface;
#ಇಲ್ಲದಿದ್ದರೆ
    device->Vulkan_ತುಂಬು_Library = 0;
    device->Vulkan_UnloadLibrary = 0;
    device->Vulkan_GetInstanceExtensions = 0;
    device->Vulkan_CreateSurface = 0;
#ಆದರೆ_ಅಂತ್ಯ

    device->PumpEvents = OPENVR_PumpEvents;
    device->VideoInit = OPENVR_VideoInit;
    device->VideoQuit = OPENVR_VideoQuit;

    device->HasScreenKeyboardSupport = OPENVR_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENVR_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENVR_HideScreenKeyboard;
    device->ಗಣ_ಕಿಟಕಿ_Icon = OPENVR_ಗಣ_ಕಿಟಕಿ_Icon;

    ಹಿಂತಿರುಗಿ device;

error:
    OPENVR_Destroy(device);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

VideoBootStrap OPENVR_bootstrap = {
    "openvr", "SDL OpenVR video driver", OPENVR_CreateDevice, ಖಾಲಿ, false
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENVR

