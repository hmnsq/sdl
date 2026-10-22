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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_kmsdrmvideo_h
#घोषणा SDL_kmsdrmvideo_h

#समावेश "../SDL_sysvideo.h"

#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <xf86drm.h>
#समावेश <xf86drmMode.h>
#समावेश <gbm.h>
#समावेश <EGL/egl.h>
#समावेश <EGL/eglext.h>

#अगर_अघोषित DRM_FORMAT_MOD_INVALID
#घोषणा DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#पूर्ण_अगर

#अगर_अघोषित DRM_MODE_FB_MODIFIERS
#घोषणा DRM_MODE_FB_MODIFIERS	2
#पूर्ण_अगर

#अगर_अघोषित DRM_MODE_PAGE_FLIP_ASYNC
#घोषणा DRM_MODE_PAGE_FLIP_ASYNC    2
#पूर्ण_अगर

#अगर_अघोषित DRM_MODE_OBJECT_CONNECTOR
#घोषणा DRM_MODE_OBJECT_CONNECTOR   0xc0c0c0c0
#पूर्ण_अगर

#अगर_अघोषित DRM_MODE_OBJECT_CRTC
#घोषणा DRM_MODE_OBJECT_CRTC        0xcccccccc
#पूर्ण_अगर

#अगर_अघोषित DRM_CAP_ASYNC_PAGE_FLIP
#घोषणा DRM_CAP_ASYNC_PAGE_FLIP 7
#पूर्ण_अगर

#अगर_अघोषित DRM_CAP_CURSOR_WIDTH
#घोषणा DRM_CAP_CURSOR_WIDTH    8
#पूर्ण_अगर

#अगर_अघोषित DRM_CAP_CURSOR_HEIGHT
#घोषणा DRM_CAP_CURSOR_HEIGHT   9
#पूर्ण_अगर

#अगर_अघोषित GBM_FORMAT_ARGB8888
#घोषणा GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#घोषणा GBM_BO_USE_CURSOR   (1 << 1)
#घोषणा GBM_BO_USE_WRITE    (1 << 3)
#घोषणा GBM_BO_USE_LINEAR   (1 << 4)
#पूर्ण_अगर

प्रकार काष्ठा KMSDRM_plane
{
    drmModePlane *plane;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_plane;
 
प्रकार काष्ठा KMSDRM_crtc
{
    drmModeCrtc *crtc;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_crtc;

प्रकार काष्ठा KMSDRM_connector
{
    drmModeConnector *connector;
    drmModeObjectProperties *props;
    drmModePropertyRes **props_info;
} KMSDRM_connector;

काष्ठा SDL_Video_तथ्य
{
    पूर्णांक devindex;     // device index that was passed on creation
    पूर्णांक drm_fd;       // DRM file desc
    अक्षर devpath[32]; // DRM dev path.

    काष्ठा gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_mode;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_Window **windows;
    पूर्णांक max_windows;
    पूर्णांक अंक_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

काष्ठा SDL_Display_Mode_तथ्य
{
    पूर्णांक mode_सूचकांक;
};

काष्ठा SDL_Display_तथ्य
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
    काष्ठा gbm_bo *cursor_bo;
    पूर्णांक cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drmModeAtomicReq *atomic_req;

    पूर्णांक kms_in_fence_fd;
    पूर्णांक kms_out_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

काष्ठा SDL_Window_तथ्य
{
    SDL_Video_तथ्य *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    काष्ठा gbm_surface *gs;
    काष्ठा gbm_bo *bo;
    काष्ठा gbm_bo *अग्र_bo;

    bool waiting_for_flip;
    bool double_बफर;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*swap_window)(SDL_VideoDevice *_this, SDL_Window *window);
};

प्रकार काष्ठा KMSDRM_FBInfo
{
    पूर्णांक drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

प्रकार काष्ठा KMSDRM_PlaneInfo
{
    काष्ठा KMSDRM_plane *plane;
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
बाह्य bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, काष्ठा gbm_bo *bo);
बाह्य KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, काष्ठा gbm_bo *bo, पूर्णांक w, पूर्णांक h);
बाह्य bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_Window_तथ्य *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
व्योम drm_atomic_set_plane_props(SDL_Display_तथ्य *dispdata, काष्ठा KMSDRM_PlaneInfo *info);
व्योम drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_तथ्य *dispdata);
पूर्णांक drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_तथ्य *dispdata, bool blocking, bool allow_modeset);
पूर्णांक add_plane_property(drmModeAtomicReq *req, काष्ठा KMSDRM_plane *plane, स्थिर अक्षर *name, uint64_t मूल्य);
पूर्णांक add_crtc_property(drmModeAtomicReq *req, काष्ठा KMSDRM_crtc *crtc, स्थिर अक्षर *name, uint64_t मूल्य);
पूर्णांक add_connector_property(drmModeAtomicReq *req, काष्ठा KMSDRM_connector *connector, स्थिर अक्षर *name, uint64_t मूल्य);
bool setup_plane(SDL_VideoDevice *_this, SDL_Display_तथ्य *dispdata, काष्ठा KMSDRM_plane **plane, uint32_t plane_type);
व्योम free_plane(काष्ठा KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
बाह्य व्योम KMSDRM_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool KMSDRM_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
बाह्य bool KMSDRM_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य व्योम KMSDRM_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool KMSDRM_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_Fullscreen_परिणाम KMSDRM_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
बाह्य व्योम KMSDRM_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम KMSDRM_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool KMSDRM_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);

#पूर्ण_अगर // SDL_kmsdrmvideo_h
