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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"
#ಅನ್ತರ್ಭಾವ <errno.h>

#ವ್ಯಾಖ್ಯಾನಿಸು VOID2U64(x) ((uint64_t)(size_t)(x))

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_PLATFORM_GBM_KHR
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_GBM_KHR 0x31D7
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_SYNC_NATIVE_FENCE_ANDROID
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_SYNC_NATIVE_FENCE_FD_ANDROID
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NO_NATIVE_FENCE_FD_ANDROID
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
#ಆದರೆ_ಅಂತ್ಯ


// EGL implementation of SDL OpenGL support

ಶೂನ್ಯ KMSDRM_GLES_ಗಣ_Default_Profile_Config(SDL_VideoDevice *_this)
{
    /* if SDL was _also_ built with the Raspberry Pi driver (so we're
       definitely a Pi device) or with the ROCKCHIP video driver
       (it's a ROCKCHIP device),  default to GLES2. */
#ಆದರೆ defined(SDL_VIDEO_DRIVER_RPI) || defined(SDL_VIDEO_DRIVER_ROCKCHIP)
    _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
    _this->gl_config.major_ಆವೃತ್ತಿ = 2;
    _this->gl_config.minor_ಆವೃತ್ತಿ = 0;
#ಆದರೆ_ಅಂತ್ಯ

    _this->gl_config.egl_platform = EGL_PLATFORM_GBM_KHR;
}

bool KMSDRM_GLES_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    /* Just pretend you do this here, but don't do it until KMSDRM_CreateWindow(),
       where we do the same library load we would normally do here.
       because this gets called by SDL_CreateWindow() before KMSDR_CreateWindow(),
       so gbm dev isn't yet created when this is called, AND we can't alter the
       call order in SDL_CreateWindow(). */
#ಆದರೆ 0
    NativeDisplayType display = (NativeDisplayType)_this->ಆಂತರಿಕ->gbm_dev;
    ಹಿಂತಿರುಗಿ SDL_EGL_ತುಂಬು_Library(_this, ಮಾರ್ಗ, display);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ KMSDRM_GLES_UnloadLibrary(SDL_VideoDevice *_this)
{
    /* As with KMSDRM_GLES_LoadLibrary(), we define our own "dummy" unloading function
       so we manually unload the library whenever we want. */
}

SDL_EGL_CreateContext_impl(KMSDRM)

bool KMSDRM_GLES_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("EGL not initialized");
    }

    ಆದರೆ (interval == 0 || interval == 1) {
        _this->egl_ದತ್ತಾಂಶ->egl_swapinterval = interval;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Only swap intervals of 0 or 1 are supported");
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ EGLSyncKHR create_fence(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ fd)
{
    EGLint attrib_list[] = {
        EGL_SYNC_NATIVE_FENCE_FD_ANDROID, fd,
        EGL_NONE,
    };

    EGLSyncKHR fence = _this->egl_ದತ್ತಾಂಶ->eglCreateSyncKHR(_this->egl_ದತ್ತಾಂಶ->egl_display, EGL_SYNC_NATIVE_FENCE_ANDROID, attrib_list);

    SDL_assert(fence);
    ಹಿಂತಿರುಗಿ fence;
}

/***********************************************************************************/
/* Comments about buffer access protection mechanism (=fences) are the ones boxed. */
/* Also, DON'T remove the asserts: if a fence-related call fails, it's better that */
/* program exits immediately, or we could leave KMS waiting for a failed/missing   */
/* fence forever.                                                                  */
/***********************************************************************************/
ಸ್ಥಿರ bool KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Fenced(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ((SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *) ಕಿಟಕಿ->ಆಂತರಿಕ);
    SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    KMSDRM_FBInfo *fb;
    KMSDRM_PlaneInfo info;
    ಸ್ಥಿರಾಂಕ bool modesetting = windata->egl_surface_dirty;

    ಆದರೆ (modesetting) {
        KMSDRM_CreateSurfaces(_this, ಕಿಟಕಿ);
    }

    SDL_zero(info);

    /******************************************************************/
    /* Create the GPU-side FENCE OBJECT. It will be inserted into the */
    /* GL CMDSTREAM exactly at the end of the gl commands that form a */
    /* frame.(KMS will have to wait on it before doing a pageflip.)   */
    /******************************************************************/
    dispdata->gpu_fence = create_fence(_this, EGL_NO_NATIVE_FENCE_FD_ANDROID);
    SDL_assert(dispdata->gpu_fence);

    /******************************************************************/
    /* eglSwapBuffers flushes the fence down the GL CMDSTREAM, so we  */
    /* know for sure it's there now.                                  */
    /* Also it marks, at EGL level, the buffer that we want to become */
    /* the new front buffer. (Remember that won't really happen until */
    /* we request a pageflip at the KMS level and it completes.       */
    /******************************************************************/
    ಆದರೆ (! _this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, windata->egl_surface)) {
        ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("Failed to swap EGL buffers", "eglSwapBuffers");
    }

    /******************************************************************/
    /* EXPORT the GPU-side FENCE OBJECT to the fence INPUT FD, so we  */
    /* can pass it into the kernel. Atomic ioctl will pass the        */
    /* in-fence fd into the kernel, thus telling KMS that it has to   */
    /* wait for GPU to finish rendering the frame (remember where we  */
    /* put the fence in the GL CMDSTREAM) before doing the changes    */
    /* requested in the atomic ioct (the pageflip in this case).      */
    /* (We export the GPU-side FENCE OBJECT to the fence INPUT FD now,*/
    /* not sooner, because now we are sure that the GPU-side fence is */
    /* in the CMDSTREAM to be lifted when the CMDSTREAM to this point */
    /* is completed).                                                 */
    /******************************************************************/
    dispdata->kms_ಒಳ_fence_fd = _this->egl_ದತ್ತಾಂಶ->eglDupNativeFenceFDANDROID (_this->egl_ದತ್ತಾಂಶ->egl_display, dispdata->gpu_fence);

    _this->egl_ದತ್ತಾಂಶ->eglDestroySyncKHR(_this->egl_ದತ್ತಾಂಶ->egl_display, dispdata->gpu_fence);
    SDL_assert(dispdata->kms_ಒಳ_fence_fd != -1);

    /* Lock the buffer that is marked by eglSwapBuffers() to become the
       next front buffer (so it can not be chosen by EGL as back buffer
       to draw on), and get a handle to it to request the pageflip on it.
       REMEMBER that gbm_surface_lock_front_buffer() ALWAYS has to be
       called after eglSwapBuffers(). */
    windata->ಮುಂದಿನ_bo = KMSDRM_gbm_surface_ಬೀಗ_front_ಬಫರ್(windata->gs);
    ಆದರೆ (!windata->ಮುಂದಿನ_bo) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to lock frontbuffer");
    }
    fb = KMSDRM_FBFromBO(_this, windata->ಮುಂದಿನ_bo);
    ಆದರೆ (!fb) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to get a new framebuffer from BO");
    }

    ಆದರೆ (!windata->bo) {
        /* On the first swap, immediately present the new front buffer. Before
           drmModePageFlip can be used the CRTC has to be configured to use
           the current connector and mode with drmModeSetCrtc */
        SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd,
                                    dispdata->crtc.crtc->crtc_id, fb->fb_id, 0, 0,
                                    &dispdata->connector.connector->connector_id, 1, &dispdata->ಬಹುಲಕ);

        ಆದರೆ (ret) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not set videomode on CRTC.");
        }
    }

    /* Add the pageflip to the request list. */
    info.plane = dispdata->display_plane;
    info.crtc_id = dispdata->crtc.crtc->crtc_id;
    info.fb_id = fb->fb_id;
    info.src_w = ಕಿಟಕಿ->w;  // !!! FIXME: was windata->src_w in the original atomic patch
    info.src_h = ಕಿಟಕಿ->h;  // !!! FIXME: was windata->src_h in the original atomic patch
    info.crtc_w = dispdata->ಬಹುಲಕ.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch
    info.crtc_h = dispdata->ಬಹುಲಕ.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch
    info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch

    drm_atomic_ಗಣ_plane_props(dispdata, &info);

    /*****************************************************************/
    /* Tell the display (KMS) that it will have to wait on the fence */
    /* for the GPU-side FENCE.                                       */
    /*                                                               */
    /* Since KMS is a kernel thing, we have to pass an FD into       */
    /* the kernel, and get another FD out of the kernel.             */
    /*                                                               */
    /* 1) To pass the GPU-side fence into the kernel, we set the     */
    /* INPUT FD as the IN_FENCE_FD prop of the PRIMARY PLANE.        */
    /* This FD tells KMS (the kernel) to wait for the GPU-side fence.*/
    /*                                                               */
    /* 2) To get the KMS-side fence out of the kernel, we set the    */
    /* OUTPUT FD as the OUT_FEWNCE_FD prop of the CRTC.              */
    /* This FD will be later imported as a FENCE OBJECT which will be*/
    /* used to tell the GPU to wait for KMS to complete the changes  */
    /* requested in atomic_commit (the pageflip in this case).       */
    /*****************************************************************/
    ಆದರೆ (dispdata->kms_ಒಳ_fence_fd != -1)
    {
        ಕೂಡಿಸು_plane_property(dispdata->atomic_req, dispdata->display_plane,
            "IN_FENCE_FD", dispdata->kms_ಒಳ_fence_fd);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, &dispdata->crtc,
            "OUT_FENCE_PTR", VOID2U64(&dispdata->kms_ಹೊರಹೋಗು_fence_fd));
    }
 
    /* Do we have a pending modesetting? If so, set the necessary
       props so it's included in the incoming atomic commit. */
    ಆದರೆ (modesetting) {
        uint32_t blob_id;
        SDL_Video_ದತ್ತಾಂಶ *viddata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

        ಕೂಡಿಸು_connector_property(dispdata->atomic_req, &dispdata->connector, "CRTC_ID", dispdata->crtc.crtc->crtc_id);
        KMSDRM_drm_ಬಹುಲಕ_Create_Property_Blob(viddata->drm_fd, &dispdata->ಬಹುಲಕ, ಗಾತ್ರ(dispdata->ಬಹುಲಕ), &blob_id);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, &dispdata->crtc, "MODE_ID", blob_id);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, &dispdata->crtc, "active", 1);
    }

    /*****************************************************************/
    /* Issue a non-blocking atomic commit: for triple buffering,     */
    /* this must not block so the game can start building another    */
    /* frame, even if the just-requested pageflip hasnt't completed. */
    /*****************************************************************/
    ಆದರೆ (drm_atomic_commit(_this, dispdata, false, modesetting)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to issue atomic commit on pageflip");
    }

    /* Release the previous front buffer so EGL can chose it as back buffer
       and render on it again. */
    ಆದರೆ (windata->bo) {
        KMSDRM_gbm_surface_release_ಬಫರ್(windata->gs, windata->bo);
    }
    /* Take note of the buffer about to become front buffer, so next
       time we come here we can free it like we just did with the previous
       front buffer. */
    windata->bo = windata->ಮುಂದಿನ_bo;

    /****************************************************************/
    /* Import the KMS-side FENCE OUTPUT FD from the kernel to the   */
    /* KMS-side FENCE OBJECT so we can use use it to fence the GPU. */
    /****************************************************************/
    dispdata->kms_fence = create_fence(_this, dispdata->kms_ಹೊರಹೋಗು_fence_fd);
    SDL_assert(dispdata->kms_fence);

    /****************************************************************/
    /* "Delete" the fence OUTPUT FD, because we already have the    */
    /* KMS FENCE OBJECT, the fence itself is away from us, on the   */
    /* kernel side.                                                 */
    /****************************************************************/
    dispdata->kms_ಹೊರಹೋಗು_fence_fd = -1;

    /*****************************************************************/
    /* Tell the GPU to wait on the fence for the KMS-side FENCE,     */
    /* which means waiting until the requested pageflip is completed.*/
    /*****************************************************************/
    _this->egl_ದತ್ತಾಂಶ->eglWaitSyncKHR(_this->egl_ದತ್ತಾಂಶ->egl_display, dispdata->kms_fence, 0);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Double_Buffered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ((SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *) ಕಿಟಕಿ->ಆಂತರಿಕ);
    SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    KMSDRM_FBInfo *fb;
    KMSDRM_PlaneInfo info;
    ಸ್ಥಿರಾಂಕ bool modesetting = windata->egl_surface_dirty;

    ಆದರೆ (modesetting) {
        KMSDRM_CreateSurfaces(_this, ಕಿಟಕಿ);
    }

    SDL_zero(info);

    /**********************************************************************************/
    /* In double-buffer mode, atomic_commit will always be synchronous/blocking (ie:  */
    /* won't return until the requested changes are really done).                     */
    /* Also, there's no need to fence KMS or the GPU, because we won't be entering    */
    /* game loop again (hence not building or executing a new cmdstring) until        */
    /* pageflip is done, so we don't need to protect the KMS/GPU access to the buffer.*/
    /**********************************************************************************/

    /* Mark, at EGL level, the buffer that we want to become the new front buffer.
       It won't really happen until we request a pageflip at the KMS level and it
       completes. */
    ಆದರೆ (! _this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display, windata->egl_surface)) {
        ಹಿಂತಿರುಗಿ SDL_EGL_ಗಣ_Error("Failed to swap EGL buffers", "eglSwapBuffers");
    }
    /* Lock the buffer that is marked by eglSwapBuffers() to become the next front buffer
       (so it can not be chosen by EGL as back buffer to draw on), and get a handle to it,
       to request the pageflip on it. */
    windata->ಮುಂದಿನ_bo = KMSDRM_gbm_surface_ಬೀಗ_front_ಬಫರ್(windata->gs);
    ಆದರೆ (!windata->ಮುಂದಿನ_bo) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to lock frontbuffer");
     }
    fb = KMSDRM_FBFromBO(_this, windata->ಮುಂದಿನ_bo);
    ಆದರೆ (!fb) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to get a new framebuffer BO");
    }

    ಆದರೆ (!windata->bo) {
        /* On the first swap, immediately present the new front buffer. Before
           drmModePageFlip can be used the CRTC has to be configured to use
           the current connector and mode with drmModeSetCrtc */
        SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd,
                                    dispdata->crtc.crtc->crtc_id, fb->fb_id, 0, 0,
                                    &dispdata->connector.connector->connector_id, 1, &dispdata->ಬಹುಲಕ);

        ಆದರೆ (ret) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not set videomode on CRTC.");
        }
    }

    /* Add the pageflip to the request list. */
    info.plane = dispdata->display_plane;
    info.crtc_id = dispdata->crtc.crtc->crtc_id;
    info.fb_id = fb->fb_id;
    info.src_w = ಕಿಟಕಿ->w;  // !!! FIXME: was windata->src_w in the original atomic patch
    info.src_h = ಕಿಟಕಿ->h;  // !!! FIXME: was windata->src_h in the original atomic patch
    info.crtc_w = dispdata->ಬಹುಲಕ.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch
    info.crtc_h = dispdata->ಬಹುಲಕ.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch
    info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch

    drm_atomic_ಗಣ_plane_props(dispdata, &info);

    /* Do we have a pending modesetting? If so, set the necessary
       props so it's included in the incoming atomic commit. */
    ಆದರೆ (modesetting) {
        uint32_t blob_id;

        SDL_Video_ದತ್ತಾಂಶ *viddata = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

        ಕೂಡಿಸು_connector_property(dispdata->atomic_req, &dispdata->connector, "CRTC_ID", dispdata->crtc.crtc->crtc_id);
        KMSDRM_drm_ಬಹುಲಕ_Create_Property_Blob(viddata->drm_fd, &dispdata->ಬಹುಲಕ, ಗಾತ್ರ(dispdata->ಬಹುಲಕ), &blob_id);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, &dispdata->crtc, "MODE_ID", blob_id);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, &dispdata->crtc, "active", 1);
    }
 
    /* Issue the one and only atomic commit where all changes will be requested!
       Blocking for double buffering: won't return until completed. */
    ಆದರೆ (drm_atomic_commit(_this, dispdata, true, modesetting)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to issue atomic commit on pageflip");
    }

    /* Release last front buffer so EGL can chose it as back buffer and render on it again. */
    ಆದರೆ (windata->bo) {
        KMSDRM_gbm_surface_release_ಬಫರ್(windata->gs, windata->bo);
    }

    /* Take note of current front buffer, so we can free it next time we come here. */
    windata->bo = windata->ಮುಂದಿನ_bo;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Legacy(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    KMSDRM_FBInfo *fb_info;
    ಪೂರ್ಣಾಂಕ ret = 0;

    /* Always wait for the previous issued flip before issuing a new one,
       even if you do async flips. */
    uint32_t flip_flags = DRM_ಬಹುಲಕ_ಪುಟ_FLIP_EVENT;

    // Skip the swap if we've switched away to another VT
    ಆದರೆ (windata->egl_surface == EGL_NO_SURFACE) {
        // Wait a bit, throttling to ~100 FPS
        SDL_Delay(10);
        ಹಿಂತಿರುಗಿ true;
    }

    // Recreate the GBM / EGL surfaces if the display mode has changed
    ಆದರೆ (windata->egl_surface_dirty) {
        KMSDRM_CreateSurfaces(_this, ಕಿಟಕಿ);
    }

    /* Wait for confirmation that the next front buffer has been flipped, at which
       point the previous front buffer can be released */
    ಆದರೆ (!KMSDRM_WaitPageflip(_this, windata)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Wait for previous pageflip failed");
    }

    // Release the previous front buffer
    ಆದರೆ (windata->bo) {
        KMSDRM_gbm_surface_release_ಬಫರ್(windata->gs, windata->bo);
    }

    windata->bo = windata->ಮುಂದಿನ_bo;

    /* Mark a buffer to become the next front buffer.
       This won't happen until pageflip completes. */
    ಆದರೆ (!(_this->egl_ದತ್ತಾಂಶ->egl_ಅದಲುಬದಲು_Buffers(_this->egl_ದತ್ತಾಂಶ->egl_display,
                                          windata->egl_surface))) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("eglSwapBuffers failed");
    }

    /* From the GBM surface, get the next BO to become the next front buffer,
       and lock it so it can't be allocated as a back buffer (to prevent EGL
       from drawing into it!) */
    windata->ಮುಂದಿನ_bo = KMSDRM_gbm_surface_ಬೀಗ_front_ಬಫರ್(windata->gs);
    ಆದರೆ (!windata->ಮುಂದಿನ_bo) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not lock front buffer on GBM surface");
    }

    // Get an actual usable fb for the next front buffer.
    fb_info = KMSDRM_FBFromBO(_this, windata->ಮುಂದಿನ_bo);
    ಆದರೆ (!fb_info) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not get a framebuffer");
    }

    ಆದರೆ (!windata->bo) {
        /* On the first swap, immediately present the new front buffer. Before
           drmModePageFlip can be used the CRTC has to be configured to use
           the current connector and mode with drmModeSetCrtc */
        ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd,
                                    dispdata->crtc.crtc->crtc_id, fb_info->fb_id, 0, 0,
                                    &dispdata->connector.connector->connector_id, 1, &dispdata->ಬಹುಲಕ);

        ಆದರೆ (ret) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not set videomode on CRTC.");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* On subsequent swaps, queue the new front buffer to be flipped during
           the next vertical blank

           Remember: drmModePageFlip() never blocks, it just issues the flip,
           which will be done during the next vblank, or immediately if
           we pass the DRM_MODE_PAGE_FLIP_ASYNC flag.
           Since calling drmModePageFlip() will return EBUSY if we call it
           without having completed the last issued flip, we must pass the
           DRM_MODE_PAGE_FLIP_ASYNC if we don't block on EGL (egl_swapinterval = 0).
           That makes it flip immediately, without waiting for the next vblank
           to do so, so even if we don't block on EGL, the flip will have completed
           when we get here again. */
        ಆದರೆ (_this->egl_ದತ್ತಾಂಶ->egl_swapinterval == 0 && viddata->async_pageflip_support) {
            flip_flags |= DRM_ಬಹುಲಕ_ಪುಟ_FLIP_ASYNC;
        }

        ret = KMSDRM_drm_ಬಹುಲಕ_ಪುಟ_Flip(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                     fb_info->fb_id, flip_flags, &windata->ಕಾಯುವಿಕೆ_for_flip);

        // some drivers apparently claim they can do async page flip but can't (or have intermittent problems),
        // so in this specific case just retry without the async flag. If it still fails after that, oh well.
        ಆದರೆ ((ret == -EINVAL) && (flip_flags & DRM_ಬಹುಲಕ_ಪುಟ_FLIP_ASYNC)) {
            flip_flags &= ~DRM_ಬಹುಲಕ_ಪುಟ_FLIP_ASYNC;
            ret = KMSDRM_drm_ಬಹುಲಕ_ಪುಟ_Flip(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, fb_info->fb_id, flip_flags, &windata->ಕಾಯುವಿಕೆ_for_flip);
        }

        ಆದರೆ (ret == 0) {
            windata->ಕಾಯುವಿಕೆ_for_flip = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not queue pageflip: %d", ret);
        }

        /* Wait immediately for vsync (as if we only had two buffers).
           Even if we are already doing a WaitPageflip at the beginning of this
           function, this is NOT redundant because here we wait immediately
           after submitting the image to the screen, reducing lag, and if
           we have waited here, there won't be a pending pageflip so the
           WaitPageflip at the beginning of this function will be a no-op.
           Just leave it here and don't worry.
           Run your SDL program with "SDL_VIDEO_DOUBLE_BUFFER=1 <program_name>"
           to enable this. */
        ಆದರೆ (windata->double_ಬಫರ್) {
            ಆದರೆ (!KMSDRM_WaitPageflip(_this, windata)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Immediate wait for previous pageflip failed");
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *) ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (windata->ಅದಲುಬದಲು_ಕಿಟಕಿ == ಖಾಲಿ) {
        SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
        ಆದರೆ (viddata->is_atomic) {
            // We want the fenced version by default, but it needs extensions.
            ಆದರೆ ( (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ಬಫರ್, false)) || (!SDL_EGL_HasExtension(_this, SDL_EGL_DISPLAY_EXTENSION, "EGL_ANDROID_native_fence_sync")) ) {
                windata->ಅದಲುಬದಲು_ಕಿಟಕಿ = KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Double_Buffered;
            } ಇಲ್ಲದಿದ್ದರೆ {
                windata->ಅದಲುಬದಲು_ಕಿಟಕಿ = KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Fenced;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            windata->ಅದಲುಬದಲು_ಕಿಟಕಿ = KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ_Legacy;
        }
    }
    ಹಿಂತಿರುಗಿ windata->ಅದಲುಬದಲು_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
}

SDL_EGL_MakeCurrent_impl(KMSDRM)

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM
