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
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(முழு,drmGetCap,(முழு fd, uint64_t capability, uint64_t *மதிப்பு))
SDL_KMSDRM_SYM(முழு,drmSetMaster,(முழு fd))
SDL_KMSDRM_SYM(முழு,drmDropMaster,(முழு fd))
SDL_KMSDRM_SYM(முழு,drmAuthMagic,(முழு fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(முழு fd))
SDL_KMSDRM_SYM(முழு,drmModeAddFB,(முழு fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(முழு,drmModeAddFB2,(முழு fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, மாறிலி uint32_t bo_handles[4],
                         மாறிலி uint32_t pitches[4], மாறிலி uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(முழு,drmModeAddFB2WithModifiers,(முழு fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, மாறிலி uint32_t bo_handles[4],
                         மாறிலி uint32_t pitches[4], மாறிலி uint32_t offsets[4],
                         மாறிலி uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(மாறிலி எழுத்து *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(முழு,drmModeRmFB,(முழு fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(முழு fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(முழு fd, uint32_t crtcId))
SDL_KMSDRM_SYM(முழு,drmModeSetCrtc,(முழு fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, முழு மொத்தம்,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(முழு,drmModeSetCursor,(முழு fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(முழு,drmModeSetCursor2,(முழு fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(முழு,drmModeMoveCursor,(முழு fd, uint32_t crtcId, முழு x, முழு y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(முழு fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(முழு fd, uint32_t connector_id))
SDL_KMSDRM_SYM(முழு,drmHandleEvent,(முழு fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(முழு,drmModePageFlip,(முழு fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, வெறுமை *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(முழு,drmSetClientCap,(முழு fd, uint64_t capability, uint64_t மதிப்பு))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(முழு fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(முழு fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(முழு fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(முழு,drmModeObjectSetProperty,(முழு fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t மதிப்பு))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(முழு fd, uint32_t propertyId))

SDL_KMSDRM_SYM(வெறுமை,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(வெறுமை,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(முழு,drmModeSetPlane,(முழு fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(முழு,gbm_device_is_format_supported,(கட்டமைப்பு gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(வெறுமை,gbm_device_destroy,(கட்டமைப்பு gbm_device *gbm))
SDL_KMSDRM_SYM(கட்டமைப்பு gbm_device *,gbm_create_device,(முழு fd))
SDL_KMSDRM_SYM(unsigned முழு,gbm_bo_get_width,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned முழு,gbm_bo_get_height,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(ஒன்றிப்பு gbm_bo_handle,gbm_bo_get_handle,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(முழு,gbm_bo_write,(கட்டமைப்பு gbm_bo *bo, மாறிலி வெறுமை *buf, size_t மொத்தம்))
SDL_KMSDRM_SYM(கட்டமைப்பு gbm_device *,gbm_bo_get_device,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(வெறுமை,gbm_bo_set_user_data,(கட்டமைப்பு gbm_bo *bo, வெறுமை *data,
                                          வெறுமை (*destroy_user_data)(கட்டமைப்பு gbm_bo *, வெறுமை *)))
SDL_KMSDRM_SYM(வெறுமை *,gbm_bo_get_user_data,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(வெறுமை,gbm_bo_destroy,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM(கட்டமைப்பு gbm_bo *,gbm_bo_create,(கட்டமைப்பு gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(கட்டமைப்பு gbm_surface *,gbm_surface_create,(கட்டமைப்பு gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(வெறுமை,gbm_surface_destroy,(கட்டமைப்பு gbm_surface *surf))
SDL_KMSDRM_SYM(கட்டமைப்பு gbm_bo *,gbm_surface_lock_front_buffer,(கட்டமைப்பு gbm_surface *surf))
SDL_KMSDRM_SYM(வெறுமை,gbm_surface_release_buffer,(கட்டமைப்பு gbm_surface *surf, கட்டமைப்பு gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(முழு,gbm_bo_get_plane_மொத்தம்,(கட்டமைப்பு gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(கட்டமைப்பு gbm_bo *bo, முழு plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(கட்டமைப்பு gbm_bo *bo, முழு plane))
SDL_KMSDRM_SYM_OPT(ஒன்றிப்பு gbm_bo_handle,gbm_bo_get_handle_for_plane,(கட்டமைப்பு gbm_bo *bo, முழு plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(முழு,drmIoctl,(முழு fd, unsigned long request, வெறுமை *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(வெறுமை))
SDL_KMSDRM_SYM(வெறுமை,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(முழு,drmModeAtomicCommit,(முழு fd,drmModeAtomicReqPtr req,uint32_t flags,வெறுமை *user_data))
SDL_KMSDRM_SYM(முழு,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t மதிப்பு))
SDL_KMSDRM_SYM(முழு,drmModeCreatePropertyBlob,(முழு fd,மாறிலி வெறுமை *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
