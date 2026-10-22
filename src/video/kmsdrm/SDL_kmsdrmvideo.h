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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_kmsdrmvideo_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_kmsdrmvideo_h

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xf86drm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xf86drmMode.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <gbm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/eglext.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_FORMAT_MOD_INVALID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_ਬਹੁਲਕ_FB_MODIFIERS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_ਬਹੁਲਕ_FB_MODIFIERS	2
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_ਬਹੁਲਕ_ਪੰਨਾ_FLIP_ASYNC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_ਬਹੁਲਕ_ਪੰਨਾ_FLIP_ASYNC    2
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_ਬਹੁਲਕ_OBJECT_CONNECTOR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_ਬਹੁਲਕ_OBJECT_CONNECTOR   0xc0c0c0c0
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_ਬਹੁਲਕ_OBJECT_CRTC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_ਬਹੁਲਕ_OBJECT_CRTC        0xcccccccc
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_CAP_ASYNC_ਪੰਨਾ_FLIP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_CAP_ASYNC_ਪੰਨਾ_FLIP 7
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_CAP_CURSOR_ਚੌੜਾਈ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_CAP_CURSOR_ਚੌੜਾਈ    8
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_CAP_CURSOR_ਉਚਾਈ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_CAP_CURSOR_ਉਚਾਈ   9
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GBM_FORMAT_ARGB8888
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GBM_BO_USE_CURSOR   (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GBM_BO_USE_WRITE    (1 << 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GBM_BO_USE_ਰੇਖਿਕ   (1 << 4)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KMSDRM_plane
{
    drm_ਬਹੁਲਕ_Plane *plane;
    drm_ਬਹੁਲਕ_Object_Properties *props;
    drm_ਬਹੁਲਕ_Property_Res **props_info;
} KMSDRM_plane;
 
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KMSDRM_crtc
{
    drm_ਬਹੁਲਕ_Crtc *crtc;
    drm_ਬਹੁਲਕ_Object_Properties *props;
    drm_ਬਹੁਲਕ_Property_Res **props_info;
} KMSDRM_crtc;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KMSDRM_connector
{
    drm_ਬਹੁਲਕ_Connector *connector;
    drm_ਬਹੁਲਕ_Object_Properties *props;
    drm_ਬਹੁਲਕ_Property_Res **props_info;
} KMSDRM_connector;

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    ਪੂਰਨ devindex;     // device index that was passed on creation
    ਪੂਰਨ drm_fd;       // DRM file desc
    ਅੱਖਰ devpath[32]; // DRM dev path.

    ਬਣਤਰ gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_ਬਹੁਲਕ;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_ਖਿੜਕੀ **windows;
    ਪੂਰਨ max_windows;
    ਪੂਰਨ ਅੰਕ_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
    ਪੂਰਨ ਬਹੁਲਕ_ਸੂਚਕਾਂਕ;
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info ਬਹੁਲਕ;
    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info original_ਬਹੁਲਕ;
    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info fullscreen_ਬਹੁਲਕ;

    drm_ਬਹੁਲਕ_Crtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    ਬਣਤਰ gbm_bo *cursor_bo;
    ਪੂਰਨ cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_ਬਹੁਲਕ_Atomic_Req *atomic_req;

    ਪੂਰਨ kms_ਵਿੱਚ_fence_fd;
    ਪੂਰਨ kms_ਬਾਹਰਲਾ_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    SDL_Video_ਅੰਕੜੇ *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    ਬਣਤਰ gbm_surface *gs;
    ਬਣਤਰ gbm_bo *bo;
    ਬਣਤਰ gbm_bo *ਅਗਲਾ_bo;

    bool ਉਡੀਕ_for_flip;
    bool double_ਬਫਰ;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ)(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KMSDRM_FBInfo
{
    ਪੂਰਨ drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KMSDRM_PlaneInfo
{
    ਬਣਤਰ KMSDRM_plane *plane;
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
ਬਾਹਰੀ bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ਬਣਤਰ gbm_bo *bo);
ਬਾਹਰੀ KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, ਬਣਤਰ gbm_bo *bo, ਪੂਰਨ w, ਪੂਰਨ h);
ਬਾਹਰੀ bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
ਖਾਲੀ drm_atomic_ਸੈੱਟ_plane_props(SDL_Display_ਅੰਕੜੇ *dispdata, ਬਣਤਰ KMSDRM_PlaneInfo *info);
ਖਾਲੀ drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata);
ਪੂਰਨ drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata, bool blocking, bool allow_modeset);
ਪੂਰਨ ਜੋੜੋ_plane_property(drm_ਬਹੁਲਕ_Atomic_Req *req, ਬਣਤਰ KMSDRM_plane *plane, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ);
ਪੂਰਨ ਜੋੜੋ_crtc_property(drm_ਬਹੁਲਕ_Atomic_Req *req, ਬਣਤਰ KMSDRM_crtc *crtc, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ);
ਪੂਰਨ ਜੋੜੋ_connector_property(drm_ਬਹੁਲਕ_Atomic_Req *req, ਬਣਤਰ KMSDRM_connector *connector, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ);
bool ਤਿਆਰੀ_plane(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata, ਬਣਤਰ KMSDRM_plane **plane, uint32_t plane_type);
ਖਾਲੀ free_plane(ਬਣਤਰ KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ਬਾਹਰੀ bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_VideoQuit(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਬਾਹਰੀ bool KMSDRM_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ bool KMSDRM_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ KMSDRM_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);

#ਜੇ_ਅੰਤ // SDL_kmsdrmvideo_h
