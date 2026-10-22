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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_kmsdrmvideo_h
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_kmsdrmvideo_h

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <xf86drm.h>
#ಅನ್ತರ್ಭಾವ <xf86drmMode.h>
#ಅನ್ತರ್ಭಾವ <gbm.h>
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ <EGL/eglext.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_FORMAT_MOD_INVALID
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_ಬಹುಲಕ_FB_MODIFIERS
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_ಬಹುಲಕ_FB_MODIFIERS	2
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_ಬಹುಲಕ_ಪುಟ_FLIP_ASYNC
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_ಬಹುಲಕ_ಪುಟ_FLIP_ASYNC    2
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_ಬಹುಲಕ_OBJECT_CONNECTOR
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_ಬಹುಲಕ_OBJECT_CONNECTOR   0xc0c0c0c0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_ಬಹುಲಕ_OBJECT_CRTC
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_ಬಹುಲಕ_OBJECT_CRTC        0xcccccccc
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_CAP_ASYNC_ಪುಟ_FLIP
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_CAP_ASYNC_ಪುಟ_FLIP 7
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_CAP_CURSOR_ಅಗಲ
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_CAP_CURSOR_ಅಗಲ    8
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_CAP_CURSOR_ಎತ್ತರ
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_CAP_CURSOR_ಎತ್ತರ   9
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GBM_FORMAT_ARGB8888
#ವ್ಯಾಖ್ಯಾನಿಸು GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#ವ್ಯಾಖ್ಯಾನಿಸು GBM_BO_USE_CURSOR   (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು GBM_BO_USE_WRITE    (1 << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು GBM_BO_USE_ರೇಖೀಯ   (1 << 4)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KMSDRM_plane
{
    drm_ಬಹುಲಕ_Plane *plane;
    drm_ಬಹುಲಕ_Object_Properties *props;
    drm_ಬಹುಲಕ_Property_Res **props_info;
} KMSDRM_plane;
 
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KMSDRM_crtc
{
    drm_ಬಹುಲಕ_Crtc *crtc;
    drm_ಬಹುಲಕ_Object_Properties *props;
    drm_ಬಹುಲಕ_Property_Res **props_info;
} KMSDRM_crtc;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KMSDRM_connector
{
    drm_ಬಹುಲಕ_Connector *connector;
    drm_ಬಹುಲಕ_Object_Properties *props;
    drm_ಬಹುಲಕ_Property_Res **props_info;
} KMSDRM_connector;

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ devindex;     // device index that was passed on creation
    ಪೂರ್ಣಾಂಕ drm_fd;       // DRM file desc
    ಅಕ್ಷರ devpath[32]; // DRM dev path.

    ರಚನೆ gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_ಬಹುಲಕ;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_ಕಿಟಕಿ **windows;
    ಪೂರ್ಣಾಂಕ max_windows;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_ಸೂಚ್ಯಂಕ;
};

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info ಬಹುಲಕ;
    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info original_ಬಹುಲಕ;
    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info fullscreen_ಬಹುಲಕ;

    drm_ಬಹುಲಕ_Crtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    ರಚನೆ gbm_bo *cursor_bo;
    ಪೂರ್ಣಾಂಕ cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_ಬಹುಲಕ_Atomic_Req *atomic_req;

    ಪೂರ್ಣಾಂಕ kms_ಒಳ_fence_fd;
    ಪೂರ್ಣಾಂಕ kms_ಹೊರಹೋಗು_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_Video_ದತ್ತಾಂಶ *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    ರಚನೆ gbm_surface *gs;
    ರಚನೆ gbm_bo *bo;
    ರಚನೆ gbm_bo *ಮುಂದಿನ_bo;

    bool ಕಾಯುವಿಕೆ_for_flip;
    bool double_ಬಫರ್;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*ಅದಲುಬದಲು_ಕಿಟಕಿ)(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KMSDRM_FBInfo
{
    ಪೂರ್ಣಾಂಕ drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KMSDRM_PlaneInfo
{
    ರಚನೆ KMSDRM_plane *plane;
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
ಬಾಹ್ಯ bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ರಚನೆ gbm_bo *bo);
ಬಾಹ್ಯ KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, ರಚನೆ gbm_bo *bo, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h);
ಬಾಹ್ಯ bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
ಶೂನ್ಯ drm_atomic_ಗಣ_plane_props(SDL_Display_ದತ್ತಾಂಶ *dispdata, ರಚನೆ KMSDRM_PlaneInfo *info);
ಶೂನ್ಯ drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata);
ಪೂರ್ಣಾಂಕ drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata, bool blocking, bool allow_modeset);
ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_plane_property(drm_ಬಹುಲಕ_Atomic_Req *req, ರಚನೆ KMSDRM_plane *plane, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_crtc_property(drm_ಬಹುಲಕ_Atomic_Req *req, ರಚನೆ KMSDRM_crtc *crtc, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_connector_property(drm_ಬಹುಲಕ_Atomic_Req *req, ರಚನೆ KMSDRM_connector *connector, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ);
bool ಸಿದ್ಧತೆ_plane(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata, ರಚನೆ KMSDRM_plane **plane, uint32_t plane_type);
ಶೂನ್ಯ free_plane(ರಚನೆ KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
ಬಾಹ್ಯ bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_VideoQuit(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಬಾಹ್ಯ bool KMSDRM_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ bool KMSDRM_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool KMSDRM_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ KMSDRM_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ KMSDRM_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool KMSDRM_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);

#ಆದರೆ_ಅಂತ್ಯ // SDL_kmsdrmvideo_h
