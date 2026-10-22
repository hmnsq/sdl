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
SDL_KMSDRM_SYM(शून्य,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmGetCap,(पूर्णाङ्क fd, uint64_t capability, uint64_t *मानम्))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmSetMaster,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmDropMaster,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmAuthMagic,(पूर्णाङ्क fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeAddFB,(पूर्णाङ्क fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,drmModeAddFB2,(पूर्णाङ्क fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, ध्रुव uint32_t bo_handles[4],
                         ध्रुव uint32_t pitches[4], ध्रुव uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,drmModeAddFB2WithModifiers,(पूर्णाङ्क fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, ध्रुव uint32_t bo_handles[4],
                         ध्रुव uint32_t pitches[4], ध्रुव uint32_t offsets[4],
                         ध्रुव uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ध्रुव वर्ण *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeRmFB,(पूर्णाङ्क fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(पूर्णाङ्क fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(पूर्णाङ्क fd, uint32_t crtcId))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeSetCrtc,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, पूर्णाङ्क गणनम्,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeSetCursor,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeSetCursor2,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeMoveCursor,(पूर्णाङ्क fd, uint32_t crtcId, पूर्णाङ्क x, पूर्णाङ्क y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(पूर्णाङ्क fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(पूर्णाङ्क fd, uint32_t connector_id))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmHandleEvent,(पूर्णाङ्क fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModePageFlip,(पूर्णाङ्क fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, शून्य *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(पूर्णाङ्क,drmSetClientCap,(पूर्णाङ्क fd, uint64_t capability, uint64_t मानम्))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(पूर्णाङ्क fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(पूर्णाङ्क fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeObjectSetProperty,(पूर्णाङ्क fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t मानम्))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(पूर्णाङ्क fd, uint32_t propertyId))

SDL_KMSDRM_SYM(शून्य,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(शून्य,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeSetPlane,(पूर्णाङ्क fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(पूर्णाङ्क,gbm_device_is_format_supported,(संरचना gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(शून्य,gbm_device_destroy,(संरचना gbm_device *gbm))
SDL_KMSDRM_SYM(संरचना gbm_device *,gbm_create_device,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(unsigned पूर्णाङ्क,gbm_bo_get_width,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned पूर्णाङ्क,gbm_bo_get_height,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(सङ्घ gbm_bo_handle,gbm_bo_get_handle,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(पूर्णाङ्क,gbm_bo_write,(संरचना gbm_bo *bo, ध्रुव शून्य *buf, size_t गणनम्))
SDL_KMSDRM_SYM(संरचना gbm_device *,gbm_bo_get_device,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(शून्य,gbm_bo_set_user_data,(संरचना gbm_bo *bo, शून्य *data,
                                          शून्य (*destroy_user_data)(संरचना gbm_bo *, शून्य *)))
SDL_KMSDRM_SYM(शून्य *,gbm_bo_get_user_data,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(शून्य,gbm_bo_destroy,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(संरचना gbm_bo *,gbm_bo_create,(संरचना gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(संरचना gbm_surface *,gbm_surface_create,(संरचना gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(शून्य,gbm_surface_destroy,(संरचना gbm_surface *surf))
SDL_KMSDRM_SYM(संरचना gbm_bo *,gbm_surface_lock_front_buffer,(संरचना gbm_surface *surf))
SDL_KMSDRM_SYM(शून्य,gbm_surface_release_buffer,(संरचना gbm_surface *surf, संरचना gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,gbm_bo_get_plane_गणनम्,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(संरचना gbm_bo *bo, पूर्णाङ्क plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(संरचना gbm_bo *bo, पूर्णाङ्क plane))
SDL_KMSDRM_SYM_OPT(सङ्घ gbm_bo_handle,gbm_bo_get_handle_for_plane,(संरचना gbm_bo *bo, पूर्णाङ्क plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(पूर्णाङ्क,drmIoctl,(पूर्णाङ्क fd, unsigned long request, शून्य *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(शून्य))
SDL_KMSDRM_SYM(शून्य,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeAtomicCommit,(पूर्णाङ्क fd,drmModeAtomicReqPtr req,uint32_t flags,शून्य *user_data))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t मानम्))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmModeCreatePropertyBlob,(पूर्णाङ्क fd,ध्रुव शून्य *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
