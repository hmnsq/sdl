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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_KMSDRM_MODULE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_MODULE(modname)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_KMSDRM_SYM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM(rc,fn,params)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_KMSDRM_SYM_CONST
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_CONST(type, name)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_KMSDRM_SYM_OPT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_KMSDRM_SYM_OPT(rc,fn,params)
#ਜੇ_ਅੰਤ


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Resources,(drm_ਬਹੁਲਕ_Res_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_FB,(drm_ਬਹੁਲਕ_FBPtr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Crtc,(drm_ਬਹੁਲਕ_Crtc_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Connector,(drm_ਬਹੁਲਕ_Connector_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Encoder,(drm_ਬਹੁਲਕ_Encoder_Ptr ptr))
SDL_KMSDRM_SYM(ਪੂਰਨ,drmGetCap,(ਪੂਰਨ fd, uint64_t capability, uint64_t *ਮੁੱਲ))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਸੈੱਟ_Master,(ਪੂਰਨ fd))
SDL_KMSDRM_SYM(ਪੂਰਨ,drmDropMaster,(ਪੂਰਨ fd))
SDL_KMSDRM_SYM(ਪੂਰਨ,drmAuthMagic,(ਪੂਰਨ fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Res_Ptr,drm_ਬਹੁਲਕ_Get_Resources,(ਪੂਰਨ fd))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਜੋੜੋ_FB,(ਪੂਰਨ fd, uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ, uint8_t ਡੂੰਘਾਈ_2,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਜੋੜੋ_FB2,(ਪੂਰਨ fd, uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
                         uint32_t pixel_format, ਅਚਲ uint32_t bo_handles[4],
                         ਅਚਲ uint32_t pitches[4], ਅਚਲ uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਜੋੜੋ_FB2_With_Modifiers,(ਪੂਰਨ fd, uint32_t ਚੌੜਾਈ,
                         uint32_t ਉਚਾਈ, uint32_t pixel_format, ਅਚਲ uint32_t bo_handles[4],
                         ਅਚਲ uint32_t pitches[4], ਅਚਲ uint32_t offsets[4],
                         ਅਚਲ uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ਅਚਲ ਅੱਖਰ *,drm_ਬਹੁਲਕ_Get_Connector_Type_Name,(uint32_t connector_type))

SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Rm_FB,(ਪੂਰਨ fd, uint32_t ਬਫਰ_Id))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_FBPtr,drm_ਬਹੁਲਕ_Get_FB,(ਪੂਰਨ fd, uint32_t buf))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Crtc_Ptr,drm_ਬਹੁਲਕ_Get_Crtc,(ਪੂਰਨ fd, uint32_t crtcId))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਸੈੱਟ_Crtc,(ਪੂਰਨ fd, uint32_t crtcId, uint32_t ਬਫਰ_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, ਪੂਰਨ ਗਿਣਤੀ_2,
                                   drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info_Ptr ਬਹੁਲਕ))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਸੈੱਟ_Cursor,(ਪੂਰਨ fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਸੈੱਟ_Cursor2,(ਪੂਰਨ fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Move_Cursor,(ਪੂਰਨ fd, uint32_t crtcId, ਪੂਰਨ x, ਪੂਰਨ y))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Encoder_Ptr,drm_ਬਹੁਲਕ_Get_Encoder,(ਪੂਰਨ fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Connector_Ptr,drm_ਬਹੁਲਕ_Get_Connector,(ਪੂਰਨ fd, uint32_t connector_id))
SDL_KMSDRM_SYM(ਪੂਰਨ,drmHandleEvent,(ਪੂਰਨ fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਪੰਨਾ_Flip,(ਪੂਰਨ fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, ਖਾਲੀ *user_ਅੰਕੜੇ_2))

// Planes stuff.
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਸੈੱਟ_Client_Cap,(ਪੂਰਨ fd, uint64_t capability, uint64_t ਮੁੱਲ))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Plane_Res_Ptr,drm_ਬਹੁਲਕ_Get_Plane_Resources,(ਪੂਰਨ fd))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Plane_Ptr,drm_ਬਹੁਲਕ_Get_Plane,(ਪੂਰਨ fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Object_Properties_Ptr,drm_ਬਹੁਲਕ_Object_Get_Properties,(ਪੂਰਨ fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Object_ਸੈੱਟ_Property,(ਪੂਰਨ fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t ਮੁੱਲ))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Property_Ptr,drm_ਬਹੁਲਕ_Get_Property,(ਪੂਰਨ fd, uint32_t propertyId))

SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Property,(drm_ਬਹੁਲਕ_Property_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Object_Properties,(drm_ਬਹੁਲਕ_Object_Properties_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Plane,(drm_ਬਹੁਲਕ_Plane_Ptr ptr))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Free_Plane_Resources,(drm_ਬਹੁਲਕ_Plane_Res_Ptr ptr))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_ਸੈੱਟ_Plane,(ਪੂਰਨ fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(ਪੂਰਨ,gbm_device_is_format_supported,(ਬਣਤਰ gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ਖਾਲੀ,gbm_device_destroy,(ਬਣਤਰ gbm_device *gbm))
SDL_KMSDRM_SYM(ਬਣਤਰ gbm_device *,gbm_create_device,(ਪੂਰਨ fd))
SDL_KMSDRM_SYM(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ,gbm_bo_get_ਚੌੜਾਈ,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ,gbm_bo_get_ਉਚਾਈ,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਸੰਘ gbm_bo_handle,gbm_bo_get_handle,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਪੂਰਨ,gbm_bo_write,(ਬਣਤਰ gbm_bo *bo, ਅਚਲ ਖਾਲੀ *buf, size_t ਗਿਣਤੀ_2))
SDL_KMSDRM_SYM(ਬਣਤਰ gbm_device *,gbm_bo_get_device,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਖਾਲੀ,gbm_bo_ਸੈੱਟ_user_ਅੰਕੜੇ,(ਬਣਤਰ gbm_bo *bo, ਖਾਲੀ *ਅੰਕੜੇ,
                                          ਖਾਲੀ (*destroy_user_ਅੰਕੜੇ)(ਬਣਤਰ gbm_bo *, ਖਾਲੀ *)))
SDL_KMSDRM_SYM(ਖਾਲੀ *,gbm_bo_get_user_ਅੰਕੜੇ,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਖਾਲੀ,gbm_bo_destroy,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM(ਬਣਤਰ gbm_bo *,gbm_bo_create,(ਬਣਤਰ gbm_device *gbm,
                                              uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ਬਣਤਰ gbm_surface *,gbm_surface_create,(ਬਣਤਰ gbm_device *gbm,
                                                        uint32_t ਚੌੜਾਈ, uint32_t ਉਚਾਈ,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(ਖਾਲੀ,gbm_surface_destroy,(ਬਣਤਰ gbm_surface *surf))
SDL_KMSDRM_SYM(ਬਣਤਰ gbm_bo *,gbm_surface_ਤਾਲਾ_front_ਬਫਰ,(ਬਣਤਰ gbm_surface *surf))
SDL_KMSDRM_SYM(ਖਾਲੀ,gbm_surface_release_ਬਫਰ,(ਬਣਤਰ gbm_surface *surf, ਬਣਤਰ gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(ਪੂਰਨ,gbm_bo_get_plane_ਗਿਣਤੀ,(ਬਣਤਰ gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_ਵਿੱਥ,(ਬਣਤਰ gbm_bo *bo, ਪੂਰਨ plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(ਬਣਤਰ gbm_bo *bo, ਪੂਰਨ plane))
SDL_KMSDRM_SYM_OPT(ਸੰਘ gbm_bo_handle,gbm_bo_get_handle_for_plane,(ਬਣਤਰ gbm_bo *bo, ਪੂਰਨ plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(ਪੂਰਨ,drmIoctl,(ਪੂਰਨ fd, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ request, ਖਾਲੀ *arg))
SDL_KMSDRM_SYM(drm_ਬਹੁਲਕ_Atomic_Req_Ptr,drm_ਬਹੁਲਕ_Atomic_Alloc,(ਖਾਲੀ))
SDL_KMSDRM_SYM(ਖਾਲੀ,drm_ਬਹੁਲਕ_Atomic_Free,(drm_ਬਹੁਲਕ_Atomic_Req_Ptr req))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Atomic_Commit,(ਪੂਰਨ fd,drm_ਬਹੁਲਕ_Atomic_Req_Ptr req,uint32_t flags,ਖਾਲੀ *user_ਅੰਕੜੇ_2))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Atomic_ਜੋੜੋ_Property,(drm_ਬਹੁਲਕ_Atomic_Req_Ptr req,uint32_t object_id,uint32_t property_id,uint64_t ਮੁੱਲ))
SDL_KMSDRM_SYM(ਪੂਰਨ,drm_ਬਹੁਲਕ_Create_Property_Blob,(ਪੂਰਨ fd,ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ,size_t ਮਾਪ,uint32_t *id))


#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_KMSDRM_MODULE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_KMSDRM_SYM
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_KMSDRM_SYM_CONST
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
