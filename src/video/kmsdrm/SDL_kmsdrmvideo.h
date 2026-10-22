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

#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_kmsdrmvideo_h
#تعریف_کرو SDL_kmsdrmvideo_h

#ضمن "../SDL_sysvideo.h"

#ضمن <fcntl.h>
#ضمن <unistd.h>
#ضمن <xf86drm.h>
#ضمن <xf86drmMode.h>
#ضمن <gbm.h>
#ضمن <EGL/egl.h>
#ضمن <EGL/eglext.h>

#جے_بنا_تعریف DRM_FORMAT_MOD_INVALID
#تعریف_کرو DRM_FORMAT_MOD_INVALID 0x00ffffffffffffffULL
#جے_انت

#جے_بنا_تعریف DRM_منوال_FB_MODIFIERS
#تعریف_کرو DRM_منوال_FB_MODIFIERS	2
#جے_انت

#جے_بنا_تعریف DRM_منوال_ورقہ_FLIP_ASYNC
#تعریف_کرو DRM_منوال_ورقہ_FLIP_ASYNC    2
#جے_انت

#جے_بنا_تعریف DRM_منوال_OBJECT_CONNECTOR
#تعریف_کرو DRM_منوال_OBJECT_CONNECTOR   0xc0c0c0c0
#جے_انت

#جے_بنا_تعریف DRM_منوال_OBJECT_CRTC
#تعریف_کرو DRM_منوال_OBJECT_CRTC        0xcccccccc
#جے_انت

#جے_بنا_تعریف DRM_CAP_ASYNC_ورقہ_FLIP
#تعریف_کرو DRM_CAP_ASYNC_ورقہ_FLIP 7
#جے_انت

#جے_بنا_تعریف DRM_CAP_CURSOR_چوڑائی
#تعریف_کرو DRM_CAP_CURSOR_چوڑائی    8
#جے_انت

#جے_بنا_تعریف DRM_CAP_CURSOR_اچائی
#تعریف_کرو DRM_CAP_CURSOR_اچائی   9
#جے_انت

#جے_بنا_تعریف GBM_FORMAT_ARGB8888
#تعریف_کرو GBM_FORMAT_ARGB8888  ((uint32_t)('A') | ((uint32_t)('R') << 8) | ((uint32_t)('2') << 16) | ((uint32_t)('4') << 24))
#تعریف_کرو GBM_BO_USE_CURSOR   (1 << 1)
#تعریف_کرو GBM_BO_USE_WRITE    (1 << 3)
#تعریف_کرو GBM_BO_USE_خطی   (1 << 4)
#جے_انت

تعريفنوع بنية KMSDRM_plane
{
    drm_منوال_Plane *plane;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_plane;
 
تعريفنوع بنية KMSDRM_crtc
{
    drm_منوال_Crtc *crtc;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_crtc;

تعريفنوع بنية KMSDRM_connector
{
    drm_منوال_Connector *connector;
    drm_منوال_Object_Properties *props;
    drm_منوال_Property_Res **props_info;
} KMSDRM_connector;

بنية SDL_Video_انکڑے
{
    صحيح devindex;     // device index that was passed on creation
    صحيح drm_fd;       // DRM file desc
    حرف devpath[32]; // DRM dev path.

    بنية gbm_device *gbm_dev;

    bool video_init;             // Has VideoInit succeeded?
    bool vulkan_منوال;            // Are we in Vulkan mode? One VK window is enough to be.
    bool async_pageflip_support; // Does the hardware support async. pageflips?

    SDL_کھڑکی **windows;
    صحيح max_windows;
    صحيح عدد_windows;

    /* Even if we have several displays, we only have to
       open 1 FD and create 1 gbm device. */
    bool gbm_init;

    bool is_atomic;  // true if atomic interfaces are supported.
};

بنية SDL_Display_منوال_انکڑے
{
    صحيح منوال_اشاریہ;
};

بنية SDL_Display_انکڑے
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
    بنية gbm_bo *cursor_bo;
    صحيح cursor_bo_drm_fd;
    uint64_t cursor_w, cursor_h;

    /* Central atomic request list, used for the prop
       changeset related to pageflip in SwapWindow. */
    drm_منوال_Atomic_Req *atomic_req;

    صحيح kms_وچ_fence_fd;
    صحيح kms_باہرلا_fence_fd;
    EGLSyncKHR kms_fence;
    EGLSyncKHR gpu_fence;

    bool default_cursor_init;
};

بنية SDL_کھڑکی_انکڑے
{
    SDL_Video_انکڑے *viddata;
    /* SDL internals expect EGL surface to be here, and in KMSDRM the GBM surface is
       what supports the EGL surface on the driver side, so all these surfaces and buffers
       are expected to be here, in the struct pointed by SDL_Window internal pointer:
       this one. So don't try to move these to dispdata!  */
    بنية gbm_surface *gs;
    بنية gbm_bo *bo;
    بنية gbm_bo *اگلا_bo;

    bool اڈیک_for_flip;
    bool double_بفر;

    EGLSurface egl_surface;
    bool egl_surface_dirty;

    /* This dictates what approach we'll use for SwapBuffers. */
    bool (*وٹاندرا_کھڑکی)(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
};

تعريفنوع بنية KMSDRM_FBInfo
{
    صحيح drm_fd;     // DRM file desc
    uint32_t fb_id; // DRM framebuffer ID
} KMSDRM_FBInfo;

تعريفنوع بنية KMSDRM_PlaneInfo
{
    بنية KMSDRM_plane *plane;
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
خارجي bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, بنية gbm_bo *bo);
خارجي KMSDRM_FBInfo *KMSDRM_FBFromBO2(SDL_VideoDevice *_this, بنية gbm_bo *bo, صحيح w, صحيح h);
خارجي bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_کھڑکی_انکڑے *windata);

// Atomic functions that are used from SDL_kmsdrmopengles.c and SDL_kmsdrmmouse.c
فراغ drm_atomic_سیٹ_plane_props(SDL_Display_انکڑے *dispdata, بنية KMSDRM_PlaneInfo *info);
فراغ drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_انکڑے *dispdata);
صحيح drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_انکڑے *dispdata, bool blocking, bool allow_modeset);
صحيح جوڑو_plane_property(drm_منوال_Atomic_Req *req, بنية KMSDRM_plane *plane, ثابت حرف *name, uint64_t قدر);
صحيح جوڑو_crtc_property(drm_منوال_Atomic_Req *req, بنية KMSDRM_crtc *crtc, ثابت حرف *name, uint64_t قدر);
صحيح جوڑو_connector_property(drm_منوال_Atomic_Req *req, بنية KMSDRM_connector *connector, ثابت حرف *name, uint64_t قدر);
bool تیاری_plane(SDL_VideoDevice *_this, SDL_Display_انکڑے *dispdata, بنية KMSDRM_plane **plane, uint32_t plane_type);
فراغ free_plane(بنية KMSDRM_plane **plane);

/****************************************************************************/
// SDL_VideoDevice functions declaration
/****************************************************************************/

// Display and window functions
خارجي bool KMSDRM_VideoInit(SDL_VideoDevice *_this);
خارجي فراغ KMSDRM_VideoQuit(SDL_VideoDevice *_this);
خارجي bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
خارجي bool KMSDRM_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
خارجي bool KMSDRM_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ KMSDRM_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool KMSDRM_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_Fullscreen_نتیجہ KMSDRM_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ KMSDRM_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ KMSDRM_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool KMSDRM_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);

#جے_انت // SDL_kmsdrmvideo_h
