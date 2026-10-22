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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_kmsdrmvideo_h
#నిర్వచించు SDL_kmsdrmvideo_h

#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <xf86drm.h>
#అన్తర్భావ <xf86drmMode.h>
#అన్తర్భావ <gbm.h>
#అన్తర్భావ <EGL/egl.h>
#అన్తర్భావ <EGL/eglext.h>

#నిర్వచితం_కాకపోతే DRM_FORMAT_MOD_INVALID
#నిర్వచించు DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_బహుళకం_FB_MODIFIERS
#నిర్వచించు DRM_బహుళకం_FB_MODIFIERS	2
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_బహుళకం_పుట_FLIP_ASYNC
#నిర్వచించు DRM_బహుళకం_పుట_FLIP_ASYNC    2
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_బహుళకం_OBJECT_CONNECTOR
#నిర్వచించు DRM_బహుళకం_OBJECT_CONNECTOR   0xc0c0c0c0
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_బహుళకం_OBJECT_CRTC
#నిర్వచించు DRM_బహుళకం_OBJECT_CRTC        0xcccccccc
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_CAP_ASYNC_పుట_FLIP
#నిర్వచించు DRM_CAP_ASYNC_పుట_FLIP 7
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_CAP_CURSOR_వెడల్పు
#నిర్వచించు DRM_CAP_CURSOR_వెడల్పు    8
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే DRM_CAP_CURSOR_ఎత్తు
#నిర్వచించు DRM_CAP_CURSOR_ఎత్తు   9
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GBM_FORMAT_ARGB8888
#నిర్వచించు GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#నిర్వచించు GBM_BO_USE_CURSOR   (1 << 1)
#నిర్వచించు GBM_BO_USE_WRITE    (1 << 3)
#నిర్వచించు GBM_BO_USE_రేఖీయ   (1 << 4)
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం KMSDRM_plane
{
    drm_బహుళకం_Plane *plane;
    drm_బహుళకం_Object_Properties *props;
    drm_బహుళకం_Property_Res **props_info;
} KMSDRM_plane;
 
రకనిర్వచనం నిర్మాణం KMSDRM_crtc
{
    drm_బహుళకం_Crtc *crtc;
    drm_బహుళకం_Object_Properties *props;
    drm_బహుళకం_Property_Res **props_info;
} KMSDRM_crtc;

రకనిర్వచనం నిర్మాణం KMSDRM_connector
{
    drm_బహుళకం_Connector *connector;
    drm_బహుళకం_Object_Properties *props;
    drm_బహుళకం_Property_Res **props_info;
} KMSDRM_connector;

నిర్మాణం SDL_Video_దత్తాంశం
{
    పూర్ణాంకం devindex;     // device index that was passed on creation
    పూర్ణాంకం drm_fd;       // DRM file desc
    అక్షరం devpath[32]; // DRM dev path.

    నిర్మాణం gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_బహుళకం;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_కిటికీ **windows;
    పూర్ణాంకం max_windows;
    పూర్ణాంకం అంకె_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
    పూర్ణాంకం బహుళకం_సూచీ;
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drm_బహుళకం_బహుళకం_Info బహుళకం;
    drm_బహుళకం_బహుళకం_Info original_బహుళకం;
    drm_బహుళకం_బహుళకం_Info fullscreen_బహుళకం;

    drm_బహుళకం_Crtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    నిర్మాణం gbm_bo *cursor_bo;
    పూర్ణాంకం cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_బహుళకం_Atomic_Req *atomic_req;

    పూర్ణాంకం kms_లోపల_fence_fd;
    పూర్ణాంకం kms_బహిర్గతం_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_Video_దత్తాంశం *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    నిర్మాణం gbm_surface *gs;
    నిర్మాణం gbm_bo *bo;
    నిర్మాణం gbm_bo *తదుపరి_bo;

    bool నిరీక్షణ_for_flip;
    bool double_బఫరు;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*మార్పిడి_కిటికీ)(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
};

రకనిర్వచనం నిర్మాణం KMSDRM_FBInfo
{
    పూర్ణాంకం drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

రకనిర్వచనం నిర్మాణం KMSDRM_PlaneInfo
{
    నిర్మాణం KMSDRM_plane *plane;
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
బాహ్య bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, నిర్మాణం gbm_bo *bo);
బాహ్య KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, నిర్మాణం gbm_bo *bo, పూర్ణాంకం w, పూర్ణాంకం h);
బాహ్య bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
శూన్య drm_atomic_సమితి_plane_props(SDL_Display_దత్తాంశం *dispdata, నిర్మాణం KMSDRM_PlaneInfo *info);
శూన్య drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata);
పూర్ణాంకం drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata, bool blocking, bool allow_modeset);
పూర్ణాంకం కూడు_plane_property(drm_బహుళకం_Atomic_Req *req, నిర్మాణం KMSDRM_plane *plane, స్థిరరాశి అక్షరం *name, uint64_t విలువ);
పూర్ణాంకం కూడు_crtc_property(drm_బహుళకం_Atomic_Req *req, నిర్మాణం KMSDRM_crtc *crtc, స్థిరరాశి అక్షరం *name, uint64_t విలువ);
పూర్ణాంకం కూడు_connector_property(drm_బహుళకం_Atomic_Req *req, నిర్మాణం KMSDRM_connector *connector, స్థిరరాశి అక్షరం *name, uint64_t విలువ);
bool అమరిక_plane(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata, నిర్మాణం KMSDRM_plane **plane, uint32_t plane_type);
శూన్య free_plane(నిర్మాణం KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
బాహ్య bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
బాహ్య శూన్య KMSDRM_VideoQuit(SDL_VideoDevice *_this);
బాహ్య bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
బాహ్య bool KMSDRM_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య bool KMSDRM_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య KMSDRM_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool KMSDRM_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_Fullscreen_ఫలితం KMSDRM_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య KMSDRM_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య KMSDRM_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool KMSDRM_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);

#అయితే_ముగింపు // SDL_kmsdrmvideo_h
