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
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmGetCap,(পূর্ণাঙ্ক fd, uint64_t capability, uint64_t *মান))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmSetMaster,(পূর্ণাঙ্ক fd))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmDropMaster,(পূর্ণাঙ্ক fd))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmAuthMagic,(পূর্ণাঙ্ক fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(পূর্ণাঙ্ক fd))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeAddFB,(পূর্ণাঙ্ক fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(পূর্ণাঙ্ক,drmModeAddFB2,(পূর্ণাঙ্ক fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, ধ্রুৱ uint32_t bo_handles[4],
                         ধ্রুৱ uint32_t pitches[4], ধ্রুৱ uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(পূর্ণাঙ্ক,drmModeAddFB2WithModifiers,(পূর্ণাঙ্ক fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, ধ্রুৱ uint32_t bo_handles[4],
                         ধ্রুৱ uint32_t pitches[4], ধ্রুৱ uint32_t offsets[4],
                         ধ্রুৱ uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ধ্রুৱ ৱর্ণ *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeRmFB,(পূর্ণাঙ্ক fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(পূর্ণাঙ্ক fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(পূর্ণাঙ্ক fd, uint32_t crtcId))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeSetCrtc,(পূর্ণাঙ্ক fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, পূর্ণাঙ্ক গুনতি,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeSetCursor,(পূর্ণাঙ্ক fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeSetCursor2,(পূর্ণাঙ্ক fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeMoveCursor,(পূর্ণাঙ্ক fd, uint32_t crtcId, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(পূর্ণাঙ্ক fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(পূর্ণাঙ্ক fd, uint32_t connector_id))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmHandleEvent,(পূর্ণাঙ্ক fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModePageFlip,(পূর্ণাঙ্ক fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, শূন্য *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmSetClientCap,(পূর্ণাঙ্ক fd, uint64_t capability, uint64_t মান))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(পূর্ণাঙ্ক fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(পূর্ণাঙ্ক fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(পূর্ণাঙ্ক fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeObjectSetProperty,(পূর্ণাঙ্ক fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t মান))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(পূর্ণাঙ্ক fd, uint32_t propertyId))

SDL_KMSDRM_SYM(শূন্য,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(শূন্য,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeSetPlane,(পূর্ণাঙ্ক fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,gbm_device_is_format_supported,(সংরচনা gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(শূন্য,gbm_device_destroy,(সংরচনা gbm_device *gbm))
SDL_KMSDRM_SYM(সংরচনা gbm_device *,gbm_create_device,(পূর্ণাঙ্ক fd))
SDL_KMSDRM_SYM(unsigned পূর্ণাঙ্ক,gbm_bo_get_width,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned পূর্ণাঙ্ক,gbm_bo_get_height,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(সঙ্ঘ gbm_bo_handle,gbm_bo_get_handle,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,gbm_bo_write,(সংরচনা gbm_bo *bo, ধ্রুৱ শূন্য *buf, size_t গুনতি))
SDL_KMSDRM_SYM(সংরচনা gbm_device *,gbm_bo_get_device,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(শূন্য,gbm_bo_set_user_data,(সংরচনা gbm_bo *bo, শূন্য *data,
                                          শূন্য (*destroy_user_data)(সংরচনা gbm_bo *, শূন্য *)))
SDL_KMSDRM_SYM(শূন্য *,gbm_bo_get_user_data,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(শূন্য,gbm_bo_destroy,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM(সংরচনা gbm_bo *,gbm_bo_create,(সংরচনা gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(সংরচনা gbm_surface *,gbm_surface_create,(সংরচনা gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(শূন্য,gbm_surface_destroy,(সংরচনা gbm_surface *surf))
SDL_KMSDRM_SYM(সংরচনা gbm_bo *,gbm_surface_lock_front_buffer,(সংরচনা gbm_surface *surf))
SDL_KMSDRM_SYM(শূন্য,gbm_surface_release_buffer,(সংরচনা gbm_surface *surf, সংরচনা gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(পূর্ণাঙ্ক,gbm_bo_get_plane_গুনতি,(সংরচনা gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(সংরচনা gbm_bo *bo, পূর্ণাঙ্ক plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(সংরচনা gbm_bo *bo, পূর্ণাঙ্ক plane))
SDL_KMSDRM_SYM_OPT(সঙ্ঘ gbm_bo_handle,gbm_bo_get_handle_for_plane,(সংরচনা gbm_bo *bo, পূর্ণাঙ্ক plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmIoctl,(পূর্ণাঙ্ক fd, unsigned long request, শূন্য *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(শূন্য))
SDL_KMSDRM_SYM(শূন্য,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeAtomicCommit,(পূর্ণাঙ্ক fd,drmModeAtomicReqPtr req,uint32_t flags,শূন্য *user_data))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t মান))
SDL_KMSDRM_SYM(পূর্ণাঙ্ক,drmModeCreatePropertyBlob,(পূর্ণাঙ্ক fd,ধ্রুৱ শূন্য *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
