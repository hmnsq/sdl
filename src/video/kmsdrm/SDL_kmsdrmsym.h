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
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmGetCap,(પૂર્ણાંક fd, uint64_t capability, uint64_t *કિંમત))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmSetMaster,(પૂર્ણાંક fd))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmDropMaster,(પૂર્ણાંક fd))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmAuthMagic,(પૂર્ણાંક fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(પૂર્ણાંક fd))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeAddFB,(પૂર્ણાંક fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(પૂર્ણાંક,drmModeAddFB2,(પૂર્ણાંક fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, અચલ uint32_t bo_handles[4],
                         અચલ uint32_t pitches[4], અચલ uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(પૂર્ણાંક,drmModeAddFB2WithModifiers,(પૂર્ણાંક fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, અચલ uint32_t bo_handles[4],
                         અચલ uint32_t pitches[4], અચલ uint32_t offsets[4],
                         અચલ uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(અચલ અક્ષર *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeRmFB,(પૂર્ણાંક fd, uint32_t bufferId))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(પૂર્ણાંક fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(પૂર્ણાંક fd, uint32_t crtcId))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeSetCrtc,(પૂર્ણાંક fd, uint32_t crtcId, uint32_t bufferId,
                                   uint32_t x, uint32_t y, uint32_t *connectors, પૂર્ણાંક ગણતરી,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeSetCursor,(પૂર્ણાંક fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeSetCursor2,(પૂર્ણાંક fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeMoveCursor,(પૂર્ણાંક fd, uint32_t crtcId, પૂર્ણાંક x, પૂર્ણાંક y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(પૂર્ણાંક fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(પૂર્ણાંક fd, uint32_t connector_id))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmHandleEvent,(પૂર્ણાંક fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModePageFlip,(પૂર્ણાંક fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, શૂન્ય *user_data))

// Planes stuff.
SDL_KMSDRM_SYM(પૂર્ણાંક,drmSetClientCap,(પૂર્ણાંક fd, uint64_t capability, uint64_t કિંમત))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(પૂર્ણાંક fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(પૂર્ણાંક fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(પૂર્ણાંક fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeObjectSetProperty,(પૂર્ણાંક fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t કિંમત))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(પૂર્ણાંક fd, uint32_t propertyId))

SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(શૂન્ય,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeSetPlane,(પૂર્ણાંક fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(પૂર્ણાંક,gbm_device_is_format_supported,(સંરચના gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(શૂન્ય,gbm_device_destroy,(સંરચના gbm_device *gbm))
SDL_KMSDRM_SYM(સંરચના gbm_device *,gbm_create_device,(પૂર્ણાંક fd))
SDL_KMSDRM_SYM(unsigned પૂર્ણાંક,gbm_bo_get_width,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(unsigned પૂર્ણાંક,gbm_bo_get_height,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(સંઘ gbm_bo_handle,gbm_bo_get_handle,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(પૂર્ણાંક,gbm_bo_write,(સંરચના gbm_bo *bo, અચલ શૂન્ય *buf, size_t ગણતરી))
SDL_KMSDRM_SYM(સંરચના gbm_device *,gbm_bo_get_device,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(શૂન્ય,gbm_bo_set_user_data,(સંરચના gbm_bo *bo, શૂન્ય *data,
                                          શૂન્ય (*destroy_user_data)(સંરચના gbm_bo *, શૂન્ય *)))
SDL_KMSDRM_SYM(શૂન્ય *,gbm_bo_get_user_data,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(શૂન્ય,gbm_bo_destroy,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM(સંરચના gbm_bo *,gbm_bo_create,(સંરચના gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(સંરચના gbm_surface *,gbm_surface_create,(સંરચના gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(શૂન્ય,gbm_surface_destroy,(સંરચના gbm_surface *surf))
SDL_KMSDRM_SYM(સંરચના gbm_bo *,gbm_surface_lock_front_buffer,(સંરચના gbm_surface *surf))
SDL_KMSDRM_SYM(શૂન્ય,gbm_surface_release_buffer,(સંરચના gbm_surface *surf, સંરચના gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(પૂર્ણાંક,gbm_bo_get_plane_ગણતરી,(સંરચના gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(સંરચના gbm_bo *bo, પૂર્ણાંક plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(સંરચના gbm_bo *bo, પૂર્ણાંક plane))
SDL_KMSDRM_SYM_OPT(સંઘ gbm_bo_handle,gbm_bo_get_handle_for_plane,(સંરચના gbm_bo *bo, પૂર્ણાંક plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(પૂર્ણાંક,drmIoctl,(પૂર્ણાંક fd, unsigned long request, શૂન્ય *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(શૂન્ય))
SDL_KMSDRM_SYM(શૂન્ય,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeAtomicCommit,(પૂર્ણાંક fd,drmModeAtomicReqPtr req,uint32_t flags,શૂન્ય *user_data))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t કિંમત))
SDL_KMSDRM_SYM(પૂર્ણાંક,drmModeCreatePropertyBlob,(પૂર્ણાંક fd,અચલ શૂન્ય *data,size_t size,uint32_t *id))


#undef SDL_KMSDRM_MODULE
#undef SDL_KMSDRM_SYM
#undef SDL_KMSDRM_SYM_CONST
#undef SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
