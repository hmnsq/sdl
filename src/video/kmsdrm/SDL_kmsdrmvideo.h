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

#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_kmsdrmvideo_h
#परिभाषय SDL_kmsdrmvideo_h

#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <xf86drm.h>
#अन्तर्भाव <xf86drmMode.h>
#अन्तर्भाव <gbm.h>
#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव <EGL/eglext.h>

#यदि_अपरिभाषितम् DRM_FORMAT_MOD_INVALID
#परिभाषय DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_बहुलकम्_FB_MODIFIERS
#परिभाषय DRM_बहुलकम्_FB_MODIFIERS	2
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_बहुलकम्_PAGE_FLIP_ASYNC
#परिभाषय DRM_बहुलकम्_PAGE_FLIP_ASYNC    2
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_बहुलकम्_OBJECT_CONNECTOR
#परिभाषय DRM_बहुलकम्_OBJECT_CONNECTOR   0xc0c0c0c0
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_बहुलकम्_OBJECT_CRTC
#परिभाषय DRM_बहुलकम्_OBJECT_CRTC        0xcccccccc
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_CAP_ASYNC_PAGE_FLIP
#परिभाषय DRM_CAP_ASYNC_PAGE_FLIP 7
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_CAP_CURSOR_विस्तारः
#परिभाषय DRM_CAP_CURSOR_विस्तारः    8
#यदि_अन्तः

#यदि_अपरिभाषितम् DRM_CAP_CURSOR_HEIGHT
#परिभाषय DRM_CAP_CURSOR_HEIGHT   9
#यदि_अन्तः

#यदि_अपरिभाषितम् GBM_FORMAT_ARGB8888
#परिभाषय GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#परिभाषय GBM_BO_USE_CURSOR   (1 << 1)
#परिभाषय GBM_BO_USE_WRITE    (1 << 3)
#परिभाषय GBM_BO_USE_रैखिकम्   (1 << 4)
#यदि_अन्तः

प्रकारनिर्देश संरचना KMSDRM_plane
{
    drm_बहुलकम्_Plane *plane;
    drm_बहुलकम्_Object_Properties *props;
    drm_बहुलकम्_Property_Res **props_info;
} KMSDRM_plane;
 
प्रकारनिर्देश संरचना KMSDRM_crtc
{
    drm_बहुलकम्_Crtc *crtc;
    drm_बहुलकम्_Object_Properties *props;
    drm_बहुलकम्_Property_Res **props_info;
} KMSDRM_crtc;

प्रकारनिर्देश संरचना KMSDRM_connector
{
    drm_बहुलकम्_Connector *connector;
    drm_बहुलकम्_Object_Properties *props;
    drm_बहुलकम्_Property_Res **props_info;
} KMSDRM_connector;

संरचना SDL_Video_दत्त
{
    पूर्णाङ्क devindex;     // device index that was passed on creation
    पूर्णाङ्क drm_fd;       // DRM file desc
    वर्ण devpath[32]; // DRM dev path.

    संरचना gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_बहुलकम्;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_गवाक्षः **windows;
    पूर्णाङ्क max_windows;
    पूर्णाङ्क अङ्कः_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

संरचना SDL_Display_बहुलकम्_दत्त
{
    पूर्णाङ्क बहुलकम्_सूचकांक;
};

संरचना SDL_Display_दत्त
{
    KMSDRM_plane *display_plane;
    KMSDRM_plane *cursor_plane;
    KMSDRM_crtc crtc;
    KMSDRM_connector connector;

    drm_बहुलकम्_बहुलकम्_Info बहुलकम्;
    drm_बहुलकम्_बहुलकम्_Info original_बहुलकम्;
    drm_बहुलकम्_बहुलकम्_Info fullscreen_बहुलकम्;

    drm_बहुलकम्_Crtc *saved_crtc; // CRTC to restore on quit
    bool saved_vrr;

    /* DRM & GBM cursor stuff lives here, not in an SDL_Cursor's internal struct,
       because setting/unsetting up these is done on window creation/destruction,
       where we may not have an SDL_Cursor at all (so no SDL_Cursor internal).
       There's only one cursor GBM BO because we only support one cursor. */
    संरचना gbm_bo *cursor_bo;
    पूर्णाङ्क cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_बहुलकम्_Atomic_Req *atomic_req;

    पूर्णाङ्क kms_अन्तर्_fence_fd;
    पूर्णाङ्क kms_बहिर्गमनम्_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

संरचना SDL_गवाक्षः_दत्त
{
    SDL_Video_दत्त *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    संरचना gbm_surface *gs;
    संरचना gbm_bo *bo;
    संरचना gbm_bo *अग्र_bo;

    bool प्रतीक्षा_for_flip;
    bool double_बफर;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*swap_गवाक्षः)(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
};

प्रकारनिर्देश संरचना KMSDRM_FBInfo
{
    पूर्णाङ्क drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

प्रकारनिर्देश संरचना KMSDRM_PlaneInfo
{
    संरचना KMSDRM_plane *plane;
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
बाह्य bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, संरचना gbm_bo *bo);
बाह्य KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, संरचना gbm_bo *bo, पूर्णाङ्क w, पूर्णाङ्क h);
बाह्य bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
शून्य drm_atomic_समुच्चयः_plane_props(SDL_Display_दत्त *dispdata, संरचना KMSDRM_PlaneInfo *info);
शून्य drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata);
पूर्णाङ्क drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata, bool blocking, bool allow_modeset);
पूर्णाङ्क सङ्कलय_plane_property(drm_बहुलकम्_Atomic_Req *req, संरचना KMSDRM_plane *plane, ध्रुव वर्ण *name, uint64_t मानम्);
पूर्णाङ्क सङ्कलय_crtc_property(drm_बहुलकम्_Atomic_Req *req, संरचना KMSDRM_crtc *crtc, ध्रुव वर्ण *name, uint64_t मानम्);
पूर्णाङ्क सङ्कलय_connector_property(drm_बहुलकम्_Atomic_Req *req, संरचना KMSDRM_connector *connector, ध्रुव वर्ण *name, uint64_t मानम्);
bool सज्जता_plane(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata, संरचना KMSDRM_plane **plane, uint32_t plane_type);
शून्य free_plane(संरचना KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
बाह्य bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
बाह्य शून्य KMSDRM_VideoQuit(SDL_VideoDevice *_this);
बाह्य bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
बाह्य bool KMSDRM_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
बाह्य bool KMSDRM_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य KMSDRM_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool KMSDRM_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_Fullscreen_परिणाम KMSDRM_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
बाह्य शून्य KMSDRM_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य KMSDRM_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool KMSDRM_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);

#यदि_अन्तः // SDL_kmsdrmvideo_h
