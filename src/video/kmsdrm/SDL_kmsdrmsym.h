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
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmGetCap,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint64_t capability, uint64_t *ମୂଲ୍ୟ))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmSetMaster,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmDropMaster,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmAuthMagic,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeAddFB,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeAddFB2,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, ଅଚଳ uint32_t bo_handles[4],
                         ଅଚଳ uint32_t pitches[4], ଅଚଳ uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeAddFB2WithModifiers,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, ଅଚଳ uint32_t bo_handles[4],
                         ଅଚଳ uint32_t pitches[4], ଅଚଳ uint32_t offsets[4],
                         ଅଚଳ uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ଅଚଳ ଅକ୍ଷର *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeRmFB,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtcId))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeSetCrtc,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeSetCursor,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeSetCursor2,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeMoveCursor,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtcId, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t connector_id))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmHandleEvent,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModePageFlip,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, ଶୂନ୍ୟ *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmSetClientCap,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint64_t capability, uint64_t ମୂଲ୍ୟ))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeObjectSetProperty,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t ମୂଲ୍ୟ))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t propertyId))

SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeSetPlane,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,gbm_device_is_format_supported,(ସଂରଚନା gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,gbm_device_destroy,(ସଂରଚନା gbm_device *gbm))
SDL_KMSDRM_SYM(ସଂରଚନା gbm_device *,gbm_create_device,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd))
SDL_KMSDRM_SYM(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା,gbm_bo_get_width,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା,gbm_bo_get_height,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(ସଂଘ gbm_bo_handle,gbm_bo_get_handle,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,gbm_bo_write,(ସଂରଚନା gbm_bo *bo, ଅଚଳ ଶୂନ୍ୟ *buf, size_t ଗଣନା_2))
SDL_KMSDRM_SYM(ସଂରଚନା gbm_device *,gbm_bo_get_device,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,gbm_bo_set_user_data,(ସଂରଚନା gbm_bo *bo, ଶୂନ୍ୟ *data,
                                          ଶୂନ୍ୟ (*destroy_user_data)(ସଂରଚନା gbm_bo *, ଶୂନ୍ୟ *)))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ *,gbm_bo_get_user_data,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,gbm_bo_destroy,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM(ସଂରଚନା gbm_bo *,gbm_bo_create,(ସଂରଚନା gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ସଂରଚନା gbm_surface *,gbm_surface_create,(ସଂରଚନା gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,gbm_surface_destroy,(ସଂରଚନା gbm_surface *surf))
SDL_KMSDRM_SYM(ସଂରଚନା gbm_bo *,gbm_surface_lock_front_buffer,(ସଂରଚନା gbm_surface *surf))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,gbm_surface_release_buffer,(ସଂରଚନା gbm_surface *surf, ସଂରଚନା gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,gbm_bo_get_plane_ଗଣନା,(ସଂରଚନା gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(ସଂରଚନା gbm_bo *bo, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(ସଂରଚନା gbm_bo *bo, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane))
SDL_KMSDRM_SYM_OPT(ସଂଘ gbm_bo_handle,gbm_bo_get_handle_for_plane,(ସଂରଚନା gbm_bo *bo, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmIoctl,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, unsigned long request, ଶୂନ୍ୟ *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(ଶୂନ୍ୟ))
SDL_KMSDRM_SYM(ଶୂନ୍ୟ,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeAtomicCommit,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd,drmModeAtomicReqPtr req,uint32_t flags,ଶୂନ୍ୟ *user_data))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t ମୂଲ୍ୟ))
SDL_KMSDRM_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,drmModeCreatePropertyBlob,(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd,ଅଚଳ ଶୂନ୍ୟ *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
