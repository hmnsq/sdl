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

/* *INDENT-OFF* */ // clang-format off

#ifndef SDL_KMSDRM_MODULE
#define SDL_KMSDRM_MODULE(modname)
#endif

#ifndef SDL_KMSDRM_SYM
#define SDL_KMSDRM_SYM(rc,fn,params)
#endif

#ifndef SDL_KMSDRM_SYM_CONST
#define SDL_KMSDRM_SYM_CONST(type, name)
#endif

#ifndef SDL_KMSDRM_SYM_OPT
#define SDL_KMSDRM_SYM_OPT(rc,fn,params)
#endif


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(void,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(ចំនួនគត់,drmGetCap,(ចំនួនគត់ fd, uint64_t capability, uint64_t *value))
SDL_KMSDRM_SYM(ចំនួនគត់,drmSetMaster,(ចំនួនគត់ fd))
SDL_KMSDRM_SYM(ចំនួនគត់,drmDropMaster,(ចំនួនគត់ fd))
SDL_KMSDRM_SYM(ចំនួនគត់,drmAuthMagic,(ចំនួនគត់ fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(ចំនួនគត់ fd))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeAddFB,(ចំនួនគត់ fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(ចំនួនគត់,drmModeAddFB2,(ចំនួនគត់ fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, const uint32_t bo_handles[4],
                         const uint32_t pitches[4], const uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ចំនួនគត់,drmModeAddFB2WithModifiers,(ចំនួនគត់ fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, const uint32_t bo_handles[4],
                         const uint32_t pitches[4], const uint32_t offsets[4],
                         const uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(const var_na *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(ចំនួនគត់,drmModeRmFB,(ចំនួនគត់ fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(ចំនួនគត់ fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(ចំនួនគត់ fd, uint32_t crtcId))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeSetCrtc,(ចំនួនគត់ fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, ចំនួនគត់ count,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeSetCursor,(ចំនួនគត់ fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeSetCursor2,(ចំនួនគត់ fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeMoveCursor,(ចំនួនគត់ fd, uint32_t crtcId, ចំនួនគត់ x, ចំនួនគត់ y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(ចំនួនគត់ fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(ចំនួនគត់ fd, uint32_t connector_id))
SDL_KMSDRM_SYM(ចំនួនគត់,drmHandleEvent,(ចំនួនគត់ fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModePageFlip,(ចំនួនគត់ fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, void *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(ចំនួនគត់,drmSetClientCap,(ចំនួនគត់ fd, uint64_t capability, uint64_t value))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(ចំនួនគត់ fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(ចំនួនគត់ fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(ចំនួនគត់ fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeObjectSetProperty,(ចំនួនគត់ fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t value))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(ចំនួនគត់ fd, uint32_t propertyId))

SDL_KMSDRM_SYM(void,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(void,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeSetPlane,(ចំនួនគត់ fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(ចំនួនគត់,gbm_device_is_format_supported,(sa_nracanaa gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(void,gbm_device_destroy,(sa_nracanaa gbm_device *gbm))
SDL_KMSDRM_SYM(sa_nracanaa gbm_device *,gbm_create_device,(ចំនួនគត់ fd))
SDL_KMSDRM_SYM(unsigned ចំនួនគត់,gbm_bo_get_width,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned ចំនួនគត់,gbm_bo_get_height,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(sa_ngha gbm_bo_handle,gbm_bo_get_handle,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(ចំនួនគត់,gbm_bo_write,(sa_nracanaa gbm_bo *bo, const void *buf, size_t count))
SDL_KMSDRM_SYM(sa_nracanaa gbm_device *,gbm_bo_get_device,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(void,gbm_bo_set_user_data,(sa_nracanaa gbm_bo *bo, void *data,
                                          void (*destroy_user_data)(sa_nracanaa gbm_bo *, void *)))
SDL_KMSDRM_SYM(void *,gbm_bo_get_user_data,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(void,gbm_bo_destroy,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM(sa_nracanaa gbm_bo *,gbm_bo_create,(sa_nracanaa gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(sa_nracanaa gbm_surface *,gbm_surface_create,(sa_nracanaa gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(void,gbm_surface_destroy,(sa_nracanaa gbm_surface *surf))
SDL_KMSDRM_SYM(sa_nracanaa gbm_bo *,gbm_surface_lock_front_buffer,(sa_nracanaa gbm_surface *surf))
SDL_KMSDRM_SYM(void,gbm_surface_release_buffer,(sa_nracanaa gbm_surface *surf, sa_nracanaa gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(ចំនួនគត់,gbm_bo_get_plane_count,(sa_nracanaa gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(sa_nracanaa gbm_bo *bo, ចំនួនគត់ plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(sa_nracanaa gbm_bo *bo, ចំនួនគត់ plane))
SDL_KMSDRM_SYM_OPT(sa_ngha gbm_bo_handle,gbm_bo_get_handle_for_plane,(sa_nracanaa gbm_bo *bo, ចំនួនគត់ plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(ចំនួនគត់,drmIoctl,(ចំនួនគត់ fd, unsigned long request, void *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(void))
SDL_KMSDRM_SYM(void,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeAtomicCommit,(ចំនួនគត់ fd,drmModeAtomicReqPtr req,uint32_t flags,void *user_data))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t value))
SDL_KMSDRM_SYM(ចំនួនគត់,drmModeCreatePropertyBlob,(ចំនួនគត់ fd,const void *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
