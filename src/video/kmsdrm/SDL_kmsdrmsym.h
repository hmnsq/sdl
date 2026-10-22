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
SDL_KMSDRM_SYM(শূন্য,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmGetCap,(পূর্ণসংখ্যা fd, uint64_t capability, uint64_t *মান))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmSetMaster,(পূর্ণসংখ্যা fd))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmDropMaster,(পূর্ণসংখ্যা fd))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmAuthMagic,(পূর্ণসংখ্যা fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(পূর্ণসংখ্যা fd))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeAddFB,(পূর্ণসংখ্যা fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(পূর্ণসংখ্যা,drmModeAddFB2,(পূর্ণসংখ্যা fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, ধ্রুবক uint32_t bo_handles[4],
                         ধ্রুবক uint32_t pitches[4], ধ্রুবক uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(পূর্ণসংখ্যা,drmModeAddFB2WithModifiers,(পূর্ণসংখ্যা fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, ধ্রুবক uint32_t bo_handles[4],
                         ধ্রুবক uint32_t pitches[4], ধ্রুবক uint32_t offsets[4],
                         ধ্রুবক uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ধ্রুবক অক্ষর *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeRmFB,(পূর্ণসংখ্যা fd, uint32_t বাফার_Id))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(পূর্ণসংখ্যা fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(পূর্ণসংখ্যা fd, uint32_t crtcId))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeSetCrtc,(পূর্ণসংখ্যা fd, uint32_t crtcId, uint32_t বাফার_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, পূর্ণসংখ্যা গুনতি,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeSetCursor,(পূর্ণসংখ্যা fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeSetCursor2,(পূর্ণসংখ্যা fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeMoveCursor,(পূর্ণসংখ্যা fd, uint32_t crtcId, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(পূর্ণসংখ্যা fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(পূর্ণসংখ্যা fd, uint32_t connector_id))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmHandleEvent,(পূর্ণসংখ্যা fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModePageFlip,(পূর্ণসংখ্যা fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, শূন্য *user_তথ্য_2))

// Planes stuff.
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmSetClientCap,(পূর্ণসংখ্যা fd, uint64_t capability, uint64_t মান))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(পূর্ণসংখ্যা fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(পূর্ণসংখ্যা fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(পূর্ণসংখ্যা fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeObjectSetProperty,(পূর্ণসংখ্যা fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t মান))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(পূর্ণসংখ্যা fd, uint32_t propertyId))

SDL_KMSDRM_SYM(শূন্য,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeSetPlane,(পূর্ণসংখ্যা fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,gbm_device_is_format_supported,(কাঠামো gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(শূন্য,gbm_device_destroy,(কাঠামো gbm_device *gbm))
SDL_KMSDRM_SYM(কাঠামো gbm_device *,gbm_create_device,(পূর্ণসংখ্যা fd))
SDL_KMSDRM_SYM(unsigned পূর্ণসংখ্যা,gbm_bo_get_width,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned পূর্ণসংখ্যা,gbm_bo_get_height,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(সংঘ gbm_bo_handle,gbm_bo_get_handle,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,gbm_bo_write,(কাঠামো gbm_bo *bo, ধ্রুবক শূন্য *buf, size_t গুনতি))
SDL_KMSDRM_SYM(কাঠামো gbm_device *,gbm_bo_get_device,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(শূন্য,gbm_bo_set_user_তথ্য,(কাঠামো gbm_bo *bo, শূন্য *তথ্য,
                                          শূন্য (*destroy_user_তথ্য)(কাঠামো gbm_bo *, শূন্য *)))
SDL_KMSDRM_SYM(শূন্য *,gbm_bo_get_user_তথ্য,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(শূন্য,gbm_bo_destroy,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM(কাঠামো gbm_bo *,gbm_bo_create,(কাঠামো gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(কাঠামো gbm_surface *,gbm_surface_create,(কাঠামো gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(শূন্য,gbm_surface_destroy,(কাঠামো gbm_surface *surf))
SDL_KMSDRM_SYM(কাঠামো gbm_bo *,gbm_surface_lock_front_বাফার,(কাঠামো gbm_surface *surf))
SDL_KMSDRM_SYM(শূন্য,gbm_surface_release_বাফার,(কাঠামো gbm_surface *surf, কাঠামো gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(পূর্ণসংখ্যা,gbm_bo_get_plane_গুনতি,(কাঠামো gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(কাঠামো gbm_bo *bo, পূর্ণসংখ্যা plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(কাঠামো gbm_bo *bo, পূর্ণসংখ্যা plane))
SDL_KMSDRM_SYM_OPT(সংঘ gbm_bo_handle,gbm_bo_get_handle_for_plane,(কাঠামো gbm_bo *bo, পূর্ণসংখ্যা plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmIoctl,(পূর্ণসংখ্যা fd, unsigned long request, শূন্য *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(শূন্য))
SDL_KMSDRM_SYM(শূন্য,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeAtomicCommit,(পূর্ণসংখ্যা fd,drmModeAtomicReqPtr req,uint32_t flags,শূন্য *user_তথ্য_2))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t মান))
SDL_KMSDRM_SYM(পূর্ণসংখ্যা,drmModeCreatePropertyBlob,(পূর্ণসংখ্যা fd,ধ্রুবক শূন্য *তথ্য,size_t আকার_2,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
