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
SDL_KMSDRM_SYM(فراغ,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(صحيح,drmGetCap,(صحيح fd, uint64_t capability, uint64_t *قىممەت))
SDL_KMSDRM_SYM(صحيح,drmSetMaster,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drmDropMaster,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drmAuthMagic,(صحيح fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drmModeAddFB,(صحيح fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(صحيح,drmModeAddFB2,(صحيح fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, ثابت uint32_t bo_handles[4],
                         ثابت uint32_t pitches[4], ثابت uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(صحيح,drmModeAddFB2WithModifiers,(صحيح fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, ثابت uint32_t bo_handles[4],
                         ثابت uint32_t pitches[4], ثابت uint32_t offsets[4],
                         ثابت uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ثابت حرف *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(صحيح,drmModeRmFB,(صحيح fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(صحيح fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(صحيح fd, uint32_t crtcId))
SDL_KMSDRM_SYM(صحيح,drmModeSetCrtc,(صحيح fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, صحيح سانى,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(صحيح,drmModeSetCursor,(صحيح fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(صحيح,drmModeSetCursor2,(صحيح fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(صحيح,drmModeMoveCursor,(صحيح fd, uint32_t crtcId, صحيح x, صحيح y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(صحيح fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(صحيح fd, uint32_t connector_id))
SDL_KMSDRM_SYM(صحيح,drmHandleEvent,(صحيح fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(صحيح,drmModePageFlip,(صحيح fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, فراغ *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(صحيح,drmSetClientCap,(صحيح fd, uint64_t capability, uint64_t قىممەت))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(صحيح fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(صحيح fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(صحيح fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(صحيح,drmModeObjectSetProperty,(صحيح fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t قىممەت))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(صحيح fd, uint32_t propertyId))

SDL_KMSDRM_SYM(فراغ,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(فراغ,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(صحيح,drmModeSetPlane,(صحيح fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(صحيح,gbm_device_is_format_supported,(بنية gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(فراغ,gbm_device_destroy,(بنية gbm_device *gbm))
SDL_KMSDRM_SYM(بنية gbm_device *,gbm_create_device,(صحيح fd))
SDL_KMSDRM_SYM(unsigned صحيح,gbm_bo_get_width,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned صحيح,gbm_bo_get_height,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(اتحاد gbm_bo_handle,gbm_bo_get_handle,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(صحيح,gbm_bo_write,(بنية gbm_bo *bo, ثابت فراغ *buf, size_t سانى))
SDL_KMSDRM_SYM(بنية gbm_device *,gbm_bo_get_device,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(فراغ,gbm_bo_set_user_data,(بنية gbm_bo *bo, فراغ *data,
                                          فراغ (*destroy_user_data)(بنية gbm_bo *, فراغ *)))
SDL_KMSDRM_SYM(فراغ *,gbm_bo_get_user_data,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(فراغ,gbm_bo_destroy,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(بنية gbm_bo *,gbm_bo_create,(بنية gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(بنية gbm_surface *,gbm_surface_create,(بنية gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(فراغ,gbm_surface_destroy,(بنية gbm_surface *surf))
SDL_KMSDRM_SYM(بنية gbm_bo *,gbm_surface_lock_front_buffer,(بنية gbm_surface *surf))
SDL_KMSDRM_SYM(فراغ,gbm_surface_release_buffer,(بنية gbm_surface *surf, بنية gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(صحيح,gbm_bo_get_plane_سانى,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(بنية gbm_bo *bo, صحيح plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(بنية gbm_bo *bo, صحيح plane))
SDL_KMSDRM_SYM_OPT(اتحاد gbm_bo_handle,gbm_bo_get_handle_for_plane,(بنية gbm_bo *bo, صحيح plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(صحيح,drmIoctl,(صحيح fd, unsigned long request, فراغ *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(فراغ))
SDL_KMSDRM_SYM(فراغ,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(صحيح,drmModeAtomicCommit,(صحيح fd,drmModeAtomicReqPtr req,uint32_t flags,فراغ *user_data))
SDL_KMSDRM_SYM(صحيح,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t قىممەت))
SDL_KMSDRM_SYM(صحيح,drmModeCreatePropertyBlob,(صحيح fd,ثابت فراغ *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
