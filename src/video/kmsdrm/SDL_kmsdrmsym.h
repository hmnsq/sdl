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
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmGetCap,(പൂർണ്ണസംഖ്യ fd, uint64_t capability, uint64_t *മൂല്യം))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmSetMaster,(പൂർണ്ണസംഖ്യ fd))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmDropMaster,(പൂർണ്ണസംഖ്യ fd))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmAuthMagic,(പൂർണ്ണസംഖ്യ fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(പൂർണ്ണസംഖ്യ fd))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeAddFB,(പൂർണ്ണസംഖ്യ fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(പൂർണ്ണസംഖ്യ,drmModeAddFB2,(പൂർണ്ണസംഖ്യ fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, സ്ഥിരം uint32_t bo_handles[4],
                         സ്ഥിരം uint32_t pitches[4], സ്ഥിരം uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(പൂർണ്ണസംഖ്യ,drmModeAddFB2WithModifiers,(പൂർണ്ണസംഖ്യ fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, സ്ഥിരം uint32_t bo_handles[4],
                         സ്ഥിരം uint32_t pitches[4], സ്ഥിരം uint32_t offsets[4],
                         സ്ഥിരം uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(സ്ഥിരം അക്ഷരം *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeRmFB,(പൂർണ്ണസംഖ്യ fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(പൂർണ്ണസംഖ്യ fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(പൂർണ്ണസംഖ്യ fd, uint32_t crtcId))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeSetCrtc,(പൂർണ്ണസംഖ്യ fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, പൂർണ്ണസംഖ്യ എണ്ണം,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeSetCursor,(പൂർണ്ണസംഖ്യ fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeSetCursor2,(പൂർണ്ണസംഖ്യ fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeMoveCursor,(പൂർണ്ണസംഖ്യ fd, uint32_t crtcId, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(പൂർണ്ണസംഖ്യ fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(പൂർണ്ണസംഖ്യ fd, uint32_t connector_id))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmHandleEvent,(പൂർണ്ണസംഖ്യ fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModePageFlip,(പൂർണ്ണസംഖ്യ fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, ശൂന്യം *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmSetClientCap,(പൂർണ്ണസംഖ്യ fd, uint64_t capability, uint64_t മൂല്യം))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(പൂർണ്ണസംഖ്യ fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(പൂർണ്ണസംഖ്യ fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(പൂർണ്ണസംഖ്യ fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeObjectSetProperty,(പൂർണ്ണസംഖ്യ fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t മൂല്യം))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(പൂർണ്ണസംഖ്യ fd, uint32_t propertyId))

SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeSetPlane,(പൂർണ്ണസംഖ്യ fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,gbm_device_is_format_supported,(ഘടന gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ശൂന്യം,gbm_device_destroy,(ഘടന gbm_device *gbm))
SDL_KMSDRM_SYM(ഘടന gbm_device *,gbm_create_device,(പൂർണ്ണസംഖ്യ fd))
SDL_KMSDRM_SYM(unsigned പൂർണ്ണസംഖ്യ,gbm_bo_get_width,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned പൂർണ്ണസംഖ്യ,gbm_bo_get_height,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(സംഘം gbm_bo_handle,gbm_bo_get_handle,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,gbm_bo_write,(ഘടന gbm_bo *bo, സ്ഥിരം ശൂന്യം *buf, size_t എണ്ണം))
SDL_KMSDRM_SYM(ഘടന gbm_device *,gbm_bo_get_device,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(ശൂന്യം,gbm_bo_set_user_data,(ഘടന gbm_bo *bo, ശൂന്യം *data,
                                          ശൂന്യം (*destroy_user_data)(ഘടന gbm_bo *, ശൂന്യം *)))
SDL_KMSDRM_SYM(ശൂന്യം *,gbm_bo_get_user_data,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(ശൂന്യം,gbm_bo_destroy,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM(ഘടന gbm_bo *,gbm_bo_create,(ഘടന gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ഘടന gbm_surface *,gbm_surface_create,(ഘടന gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(ശൂന്യം,gbm_surface_destroy,(ഘടന gbm_surface *surf))
SDL_KMSDRM_SYM(ഘടന gbm_bo *,gbm_surface_lock_front_buffer,(ഘടന gbm_surface *surf))
SDL_KMSDRM_SYM(ശൂന്യം,gbm_surface_release_buffer,(ഘടന gbm_surface *surf, ഘടന gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(പൂർണ്ണസംഖ്യ,gbm_bo_get_plane_എണ്ണം,(ഘടന gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(ഘടന gbm_bo *bo, പൂർണ്ണസംഖ്യ plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(ഘടന gbm_bo *bo, പൂർണ്ണസംഖ്യ plane))
SDL_KMSDRM_SYM_OPT(സംഘം gbm_bo_handle,gbm_bo_get_handle_for_plane,(ഘടന gbm_bo *bo, പൂർണ്ണസംഖ്യ plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmIoctl,(പൂർണ്ണസംഖ്യ fd, unsigned long request, ശൂന്യം *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(ശൂന്യം))
SDL_KMSDRM_SYM(ശൂന്യം,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeAtomicCommit,(പൂർണ്ണസംഖ്യ fd,drmModeAtomicReqPtr req,uint32_t flags,ശൂന്യം *user_data))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t മൂല്യം))
SDL_KMSDRM_SYM(പൂർണ്ണസംഖ്യ,drmModeCreatePropertyBlob,(പൂർണ്ണസംഖ്യ fd,സ്ഥിരം ശൂന്യം *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
