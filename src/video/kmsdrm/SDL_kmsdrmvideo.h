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

#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_kmsdrmvideo_h
#define SDL_kmsdrmvideo_h

#অন্তর্ভাৱ "../SDL_sysvideo.h"

#অন্তর্ভাৱ <fcntl.h>
#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <xf86drm.h>
#অন্তর্ভাৱ <xf86drmMode.h>
#অন্তর্ভাৱ <gbm.h>
#অন্তর্ভাৱ <EGL/egl.h>
#অন্তর্ভাৱ <EGL/eglext.h>

#ifndef DRM_FORMAT_MOD_INVALID
#define DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#endif

#ifndef DRM_MODE_FB_MODIFIERS
#define DRM_MODE_FB_MODIFIERS	2
#endif

#ifndef DRM_MODE_PAGE_FLIP_ASYNC
#define DRM_MODE_PAGE_FLIP_ASYNC    2
#endif

#ifndef DRM_MODE_OBJECT_CONNECTOR
#define DRM_MODE_OBJECT_CONNECTOR   0xc0c0c0c0
#endif

#ifndef DRM_MODE_OBJECT_CRTC
#define DRM_MODE_OBJECT_CRTC        0xcccccccc
#endif

#ifndef DRM_CAP_ASYNC_PAGE_FLIP
#define DRM_CAP_ASYNC_PAGE_FLIP 7
#endif

#ifndef DRM_CAP_CURSOR_WIDTH
#define DRM_CAP_CURSOR_WIDTH    8
#endif

#ifndef DRM_CAP_CURSOR_HEIGHT
#define DRM_CAP_CURSOR_HEIGHT   9
#endif

#ifndef GBM_FORMAT_ARGB8888
#define GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#define GBM_BO_USE_CURSOR   (1 << 1)
#define GBM_BO_USE_WRITE    (1 << 3)
#define GBM_BO_USE_LINEAR   (1 << 4)
#endif

প্রকারনির্দেশ সংরচনা KMSDRM_plane
{
    drmModePlane *plane;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_plane;
 
প্রকারনির্দেশ সংরচনা KMSDRM_crtc
{
    drmModeCrtc *crtc;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_crtc;

প্রকারনির্দেশ সংরচনা KMSDRM_connector
{
    drmModeConnector *connector;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_connector;

সংরচনা SDL_VideoData
{
    পূর্ণাঙ্ক devindex;     // device index that was passed on creation
    পূর্ণাঙ্ক drm_fd;       // DRM file desc
    ৱর্ণ devpath[32]; // DRM dev path.

    সংরচনা gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_mode;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_Window **windows;
    পূর্ণাঙ্ক max_windows;
    পূর্ণাঙ্ক অঙ্ক_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

সংরচনা SDL_DisplayModeData
{
    পূর্ণাঙ্ক mode_index;
};

সংরচনা SDL_DisplayData
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drmModeModeInfo mode;
    drmModeModeInfo original_mode;
    drmModeModeInfo fullscreen_mode;

    drmModeCrtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    সংরচনা gbm_bo *cursor_bo;
    পূর্ণাঙ্ক cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drmModeAtomicReq *atomic_req;

    পূর্ণাঙ্ক kms_in_fence_fd;
    পূর্ণাঙ্ক kms_out_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

সংরচনা SDL_WindowData
{
    SDL_VideoData *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    সংরচনা gbm_surface *gs;
    সংরচনা gbm_bo *bo;
    সংরচনা gbm_bo *next_bo;

    bool waiting_for_flip;
    bool double_buffer;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*swap_window)(SDL_VideoDevice *_this, SDL_Window *window);
};

প্রকারনির্দেশ সংরচনা KMSDRM_FBInfo
{
    পূর্ণাঙ্ক drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

প্রকারনির্দেশ সংরচনা KMSDRM_PlaneInfo
{
    সংরচনা KMSDRM_plane *plane;
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
বাহ্য bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, সংরচনা gbm_bo *bo);
বাহ্য KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, সংরচনা gbm_bo *bo, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h);
বাহ্য bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_WindowData *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
শূন্য drm_atomic_set_plane_props(SDL_DisplayData *dispdata, সংরচনা KMSDRM_PlaneInfo *info);
শূন্য drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_DisplayData *dispdata);
পূর্ণাঙ্ক drm_atomic_commit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, bool blocking, bool allow_modeset);
পূর্ণাঙ্ক add_plane_property(drmModeAtomicReq *req, সংরচনা KMSDRM_plane *plane, ধ্রুৱ ৱর্ণ *name, uint64_t মান);
পূর্ণাঙ্ক add_crtc_property(drmModeAtomicReq *req, সংরচনা KMSDRM_crtc *crtc, ধ্রুৱ ৱর্ণ *name, uint64_t মান);
পূর্ণাঙ্ক add_connector_property(drmModeAtomicReq *req, সংরচনা KMSDRM_connector *connector, ধ্রুৱ ৱর্ণ *name, uint64_t মান);
bool setup_plane(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, সংরচনা KMSDRM_plane **plane, uint32_t plane_type);
শূন্য free_plane(সংরচনা KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
বাহ্য bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
বাহ্য শূন্য KMSDRM_VideoQuit(SDL_VideoDevice *_this);
বাহ্য bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্য bool KMSDRM_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্য bool KMSDRM_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্য শূন্য KMSDRM_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool KMSDRM_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য SDL_FullscreenResult KMSDRM_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
বাহ্য শূন্য KMSDRM_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য KMSDRM_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool KMSDRM_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);

#endif // SDL_kmsdrmvideo_h
