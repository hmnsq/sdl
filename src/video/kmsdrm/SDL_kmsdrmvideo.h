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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_kmsdrmvideo_h
#define SDL_kmsdrmvideo_h

#অন্তর্ভাব "../SDL_sysvideo.h"

#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <xf86drm.h>
#অন্তর্ভাব <xf86drmMode.h>
#অন্তর্ভাব <gbm.h>
#অন্তর্ভাব <EGL/egl.h>
#অন্তর্ভাব <EGL/eglext.h>

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

প্রকারলেখ কাঠামো KMSDRM_plane
{
    drmModePlane *plane;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_plane;
 
প্রকারলেখ কাঠামো KMSDRM_crtc
{
    drmModeCrtc *crtc;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_crtc;

প্রকারলেখ কাঠামো KMSDRM_connector
{
    drmModeConnector *connector;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_connector;

কাঠামো SDL_Video_তথ্য
{
    পূর্ণসংখ্যা devindex;     // device index that was passed on creation
    পূর্ণসংখ্যা drm_fd;       // DRM file desc
    অক্ষর devpath[32]; // DRM dev path.

    কাঠামো gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_mode;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_Window **windows;
    পূর্ণসংখ্যা max_windows;
    পূর্ণসংখ্যা অঙ্ক_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

কাঠামো SDL_Display_Mode_তথ্য
{
    পূর্ণসংখ্যা mode_সূচক;
};

কাঠামো SDL_Display_তথ্য
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
    কাঠামো gbm_bo *cursor_bo;
    পূর্ণসংখ্যা cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drmModeAtomicReq *atomic_req;

    পূর্ণসংখ্যা kms_in_fence_fd;
    পূর্ণসংখ্যা kms_out_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

কাঠামো SDL_Window_তথ্য
{
    SDL_Video_তথ্য *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    কাঠামো gbm_surface *gs;
    কাঠামো gbm_bo *bo;
    কাঠামো gbm_bo *পরবর্তী_bo;

    bool waiting_for_flip;
    bool double_বাফার;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*swap_window)(SDL_VideoDevice *_this, SDL_Window *window);
};

প্রকারলেখ কাঠামো KMSDRM_FBInfo
{
    পূর্ণসংখ্যা drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

প্রকারলেখ কাঠামো KMSDRM_PlaneInfo
{
    কাঠামো KMSDRM_plane *plane;
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
বাহ্যিক bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, কাঠামো gbm_bo *bo);
বাহ্যিক KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, কাঠামো gbm_bo *bo, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h);
বাহ্যিক bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_Window_তথ্য *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
শূন্য drm_atomic_set_plane_props(SDL_Display_তথ্য *dispdata, কাঠামো KMSDRM_PlaneInfo *info);
শূন্য drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_তথ্য *dispdata);
পূর্ণসংখ্যা drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_তথ্য *dispdata, bool blocking, bool allow_modeset);
পূর্ণসংখ্যা add_plane_property(drmModeAtomicReq *req, কাঠামো KMSDRM_plane *plane, ধ্রুবক অক্ষর *name, uint64_t মান);
পূর্ণসংখ্যা add_crtc_property(drmModeAtomicReq *req, কাঠামো KMSDRM_crtc *crtc, ধ্রুবক অক্ষর *name, uint64_t মান);
পূর্ণসংখ্যা add_connector_property(drmModeAtomicReq *req, কাঠামো KMSDRM_connector *connector, ধ্রুবক অক্ষর *name, uint64_t মান);
bool setup_plane(SDL_VideoDevice *_this, SDL_Display_তথ্য *dispdata, কাঠামো KMSDRM_plane **plane, uint32_t plane_type);
শূন্য free_plane(কাঠামো KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
বাহ্যিক bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
বাহ্যিক শূন্য KMSDRM_VideoQuit(SDL_VideoDevice *_this);
বাহ্যিক bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
বাহ্যিক bool KMSDRM_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
বাহ্যিক bool KMSDRM_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্যিক শূন্য KMSDRM_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool KMSDRM_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক SDL_Fullscreen_ফলাফল KMSDRM_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
বাহ্যিক শূন্য KMSDRM_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য KMSDRM_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool KMSDRM_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);

#endif // SDL_kmsdrmvideo_h
