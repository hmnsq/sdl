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

#अगर_अघोषित SDL_KMSDRM_MODULE
#घोषणा SDL_KMSDRM_MODULE(modname)
#पूर्ण_अगर

#अगर_अघोषित SDL_KMSDRM_SYM
#घोषणा SDL_KMSDRM_SYM(rc,fn,params)
#पूर्ण_अगर

#अगर_अघोषित SDL_KMSDRM_SYM_CONST
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)
#पूर्ण_अगर

#अगर_अघोषित SDL_KMSDRM_SYM_OPT
#घोषणा SDL_KMSDRM_SYM_OPT(rc,fn,params)
#पूर्ण_अगर


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(व्योम,drmModeFreeResources,(drmModeResPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreeFB,(drmModeFBPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreeCrtc,(drmModeCrtcPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreeConnector,(drmModeConnectorPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreeEncoder,(drmModeEncoderPtr ptr))
SDL_KMSDRM_SYM(पूर्णांक,drmGetCap,(पूर्णांक fd, uint64_t capability, uint64_t *मूल्य))
SDL_KMSDRM_SYM(पूर्णांक,drmSetMaster,(पूर्णांक fd))
SDL_KMSDRM_SYM(पूर्णांक,drmDropMaster,(पूर्णांक fd))
SDL_KMSDRM_SYM(पूर्णांक,drmAuthMagic,(पूर्णांक fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drmModeResPtr,drmModeGetResources,(पूर्णांक fd))
SDL_KMSDRM_SYM(पूर्णांक,drmModeAddFB,(पूर्णांक fd, uint32_t width, uint32_t height, uint8_t depth,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(पूर्णांक,drmModeAddFB2,(पूर्णांक fd, uint32_t width, uint32_t height,
                         uint32_t pixel_format, स्थिर uint32_t bo_handles[4],
                         स्थिर uint32_t pitches[4], स्थिर uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(पूर्णांक,drmModeAddFB2WithModifiers,(पूर्णांक fd, uint32_t width,
                         uint32_t height, uint32_t pixel_format, स्थिर uint32_t bo_handles[4],
                         स्थिर uint32_t pitches[4], स्थिर uint32_t offsets[4],
                         स्थिर uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(स्थिर अक्षर *,drmModeGetConnectorTypeName,(uint32_t connector_type))

SDL_KMSDRM_SYM(पूर्णांक,drmModeRmFB,(पूर्णांक fd, uint32_t बफर_Id))
SDL_KMSDRM_SYM(drmModeFBPtr,drmModeGetFB,(पूर्णांक fd, uint32_t buf))
SDL_KMSDRM_SYM(drmModeCrtcPtr,drmModeGetCrtc,(पूर्णांक fd, uint32_t crtcId))
SDL_KMSDRM_SYM(पूर्णांक,drmModeSetCrtc,(पूर्णांक fd, uint32_t crtcId, uint32_t बफर_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, पूर्णांक गिनती,
                                   drmModeModeInfoPtr mode))
SDL_KMSDRM_SYM(पूर्णांक,drmModeSetCursor,(पूर्णांक fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t width, uint32_t height))
SDL_KMSDRM_SYM(पूर्णांक,drmModeSetCursor2,(पूर्णांक fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t width, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(पूर्णांक,drmModeMoveCursor,(पूर्णांक fd, uint32_t crtcId, पूर्णांक x, पूर्णांक y))
SDL_KMSDRM_SYM(drmModeEncoderPtr,drmModeGetEncoder,(पूर्णांक fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drmModeConnectorPtr,drmModeGetConnector,(पूर्णांक fd, uint32_t connector_id))
SDL_KMSDRM_SYM(पूर्णांक,drmHandleEvent,(पूर्णांक fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(पूर्णांक,drmModePageFlip,(पूर्णांक fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, व्योम *user_तथ्य_2))

// Planes stuff.
SDL_KMSDRM_SYM(पूर्णांक,drmSetClientCap,(पूर्णांक fd, uint64_t capability, uint64_t मूल्य))
SDL_KMSDRM_SYM(drmModePlaneResPtr,drmModeGetPlaneResources,(पूर्णांक fd))
SDL_KMSDRM_SYM(drmModePlanePtr,drmModeGetPlane,(पूर्णांक fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drmModeObjectPropertiesPtr,drmModeObjectGetProperties,(पूर्णांक fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(पूर्णांक,drmModeObjectSetProperty,(पूर्णांक fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t मूल्य))
SDL_KMSDRM_SYM(drmModePropertyPtr,drmModeGetProperty,(पूर्णांक fd, uint32_t propertyId))

SDL_KMSDRM_SYM(व्योम,drmModeFreeProperty,(drmModePropertyPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreeObjectProperties,(drmModeObjectPropertiesPtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreePlane,(drmModePlanePtr ptr))
SDL_KMSDRM_SYM(व्योम,drmModeFreePlaneResources,(drmModePlaneResPtr ptr))
SDL_KMSDRM_SYM(पूर्णांक,drmModeSetPlane,(पूर्णांक fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(पूर्णांक,gbm_device_is_format_supported,(काष्ठा gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(व्योम,gbm_device_destroy,(काष्ठा gbm_device *gbm))
SDL_KMSDRM_SYM(काष्ठा gbm_device *,gbm_create_device,(पूर्णांक fd))
SDL_KMSDRM_SYM(अचिन्हित पूर्णांक,gbm_bo_get_width,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(अचिन्हित पूर्णांक,gbm_bo_get_height,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(जोड़ gbm_bo_handle,gbm_bo_get_handle,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(पूर्णांक,gbm_bo_write,(काष्ठा gbm_bo *bo, स्थिर व्योम *buf, माप_प्रकार गिनती))
SDL_KMSDRM_SYM(काष्ठा gbm_device *,gbm_bo_get_device,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(व्योम,gbm_bo_set_user_तथ्य,(काष्ठा gbm_bo *bo, व्योम *तथ्य,
                                          व्योम (*destroy_user_तथ्य)(काष्ठा gbm_bo *, व्योम *)))
SDL_KMSDRM_SYM(व्योम *,gbm_bo_get_user_तथ्य,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(व्योम,gbm_bo_destroy,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM(काष्ठा gbm_bo *,gbm_bo_create,(काष्ठा gbm_device *gbm,
                                              uint32_t width, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(काष्ठा gbm_surface *,gbm_surface_create,(काष्ठा gbm_device *gbm,
                                                        uint32_t width, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(व्योम,gbm_surface_destroy,(काष्ठा gbm_surface *surf))
SDL_KMSDRM_SYM(काष्ठा gbm_bo *,gbm_surface_lock_front_बफर,(काष्ठा gbm_surface *surf))
SDL_KMSDRM_SYM(व्योम,gbm_surface_release_बफर,(काष्ठा gbm_surface *surf, काष्ठा gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(पूर्णांक,gbm_bo_get_plane_गिनती,(काष्ठा gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_offset,(काष्ठा gbm_bo *bo, पूर्णांक plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(काष्ठा gbm_bo *bo, पूर्णांक plane))
SDL_KMSDRM_SYM_OPT(जोड़ gbm_bo_handle,gbm_bo_get_handle_for_plane,(काष्ठा gbm_bo *bo, पूर्णांक plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(पूर्णांक,drmIoctl,(पूर्णांक fd, अचिन्हित दीर्घ request, व्योम *arg))
SDL_KMSDRM_SYM(drmModeAtomicReqPtr,drmModeAtomicAlloc,(व्योम))
SDL_KMSDRM_SYM(व्योम,drmModeAtomicFree,(drmModeAtomicReqPtr req))
SDL_KMSDRM_SYM(पूर्णांक,drmModeAtomicCommit,(पूर्णांक fd,drmModeAtomicReqPtr req,uint32_t flags,व्योम *user_तथ्य_2))
SDL_KMSDRM_SYM(पूर्णांक,drmModeAtomicAddProperty,(drmModeAtomicReqPtr req,uint32_t object_id,uint32_t property_id,uint64_t मूल्य))
SDL_KMSDRM_SYM(पूर्णांक,drmModeCreatePropertyBlob,(पूर्णांक fd,स्थिर व्योम *तथ्य,माप_प्रकार आकार,uint32_t *id))


#अघोषित SDL_KMSDRM_MODULE
#अघोषित SDL_KMSDRM_SYM
#अघोषित SDL_KMSDRM_SYM_CONST
#अघोषित SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
