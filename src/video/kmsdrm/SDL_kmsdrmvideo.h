/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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

// Atomic KMSDRM backend originally written by Manuel Alfayate Corchete <redwindwanderer@gmail.com>

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_kmsdrmvideo_h
#تعریف_کرو SDL_kmsdrmvideo_h

#شامل "../SDL_sysvideo.h"

#شامل <fcntl.h>
#شامل <unistd.h>
#شامل <xf86drm.h>
#شامل <xf86drmMode.h>
#شامل <gbm.h>
#شامل <EGL/egl.h>
#شامل <EGL/eglext.h>

#اگر_غیر_تعریف_شدہ DRM_FORMAT_MOD_INVALID
#تعریف_کرو DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_منوال_FB_MODIFIERS
#تعریف_کرو DRM_منوال_FB_MODIFIERS	2
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_منوال_صفحہ_FLIP_ASYNC
#تعریف_کرو DRM_منوال_صفحہ_FLIP_ASYNC    2
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_منوال_OBJECT_CONNECTOR
#تعریف_کرو DRM_منوال_OBJECT_CONNECTOR   0xc0c0c0c0
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_منوال_OBJECT_CRTC
#تعریف_کرو DRM_منوال_OBJECT_CRTC        0xcccccccc
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_CAP_ASYNC_صفحہ_FLIP
#تعریف_کرو DRM_CAP_ASYNC_صفحہ_FLIP 7
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_CAP_CURSOR_چوڑائی
#تعریف_کرو DRM_CAP_CURSOR_چوڑائی    8
#اگر_ختم

#اگر_غیر_تعریف_شدہ DRM_CAP_CURSOR_اونچائی
#تعریف_کرو DRM_CAP_CURSOR_اونچائی   9
#اگر_ختم

#اگر_غیر_تعریف_شدہ GBM_FORMAT_ARGB8888
#تعریف_کرو GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#تعریف_کرو GBM_BO_USE_CURSOR   (1 << 1)
#تعریف_کرو GBM_BO_USE_WRITE    (1 << 3)
#تعریف_کرو GBM_BO_USE_خطی   (1 << 4)
#اگر_ختم

قسمتعریف ساخت KMSDRM_plane
{
    drm_منوال_Plane *plane;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_plane;
 
قسمتعریف ساخت KMSDRM_crtc
{
    drm_منوال_Crtc *crtc;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_crtc;

قسمتعریف ساخت KMSDRM_connector
{
    drm_منوال_Connector *connector;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_connector;

ساخت SDL_Video_ڈیٹا
{
    صحیح devindex;     // device index that was passed on creation
    صحیح drm_fd;       // DRM file desc
    حرف devpath[32]; // DRM dev path.

    ساخت gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_منوال;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_کھڑکی **windows;
    صحیح max_windows;
    صحیح عدد_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

ساخت SDL_Display_منوال_ڈیٹا
{
    صحیح منوال_اشاریہ;
};

ساخت SDL_Display_ڈیٹا
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drm_منوال_منوال_Info منوال;
    drm_منوال_منوال_Info original_منوال;
    drm_منوال_منوال_Info fullscreen_منوال;

    drm_منوال_Crtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    ساخت gbm_bo *cursor_bo;
    صحیح cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_منوال_Atomic_Req *atomic_req;

    صحیح kms_اندر_fence_fd;
    صحیح kms_برآمد_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

ساخت SDL_کھڑکی_ڈیٹا
{
    SDL_Video_ڈیٹا *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    ساخت gbm_surface *gs;
    ساخت gbm_bo *bo;
    ساخت gbm_bo *اگلا_bo;

    bool انتظار_for_flip;
    bool double_بفر;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*تبادلہ_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
};

قسمتعریف ساخت KMSDRM_FBInfo
{
    صحیح drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

قسمتعریف ساخت KMSDRM_PlaneInfo
{
    ساخت KMSDRM_plane *plane;
    uint32_t fb_id;
    uint32_t crtc_id;
    int32_t src_x;
    int32_t src_y;
    int32_t src_w;
    int32_t src_h;
    int32_t crtc_x;
    int32_t crtc_y;
    int32_t crtc_w;
    int32_t crtc_h;
} KMSDRM_PlaneInfo;

// Helper functions
خارجی bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ساخت gbm_bo *bo);
خارجی KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, ساخت gbm_bo *bo, صحیح w, صحیح h);
خارجی bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
خالی drm_atomic_سیٹ_plane_props(SDL_Display_ڈیٹا *dispdata, ساخت KMSDRM_PlaneInfo *info);
خالی drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata);
صحیح drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata, bool blocking, bool allow_modeset);
صحیح جوڑو_plane_property(drm_منوال_Atomic_Req *req, ساخت KMSDRM_plane *plane, ثابت حرف *name, uint64_t قدر);
صحیح جوڑو_crtc_property(drm_منوال_Atomic_Req *req, ساخت KMSDRM_crtc *crtc, ثابت حرف *name, uint64_t قدر);
صحیح جوڑو_connector_property(drm_منوال_Atomic_Req *req, ساخت KMSDRM_connector *connector, ثابت حرف *name, uint64_t قدر);
bool تیاری_plane(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata, ساخت KMSDRM_plane **plane, uint32_t plane_type);
خالی free_plane(ساخت KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجی bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
خارجی خالی KMSDRM_VideoQuit(SDL_VideoDevice *_this);
خارجی bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجی bool KMSDRM_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجی bool KMSDRM_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی KMSDRM_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool KMSDRM_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_Fullscreen_نتیجہ KMSDRM_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجی خالی KMSDRM_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی KMSDRM_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool KMSDRM_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);

#اگر_ختم // SDL_kmsdrmvideo_h
