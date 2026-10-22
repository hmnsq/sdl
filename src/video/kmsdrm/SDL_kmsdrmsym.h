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

#که_نه_تعریف_شوی SDL_KMSDRM_MODULE
#تعریف_کړه SDL_KMSDRM_MODULE(modname)
#د_که_پای

#که_نه_تعریف_شوی SDL_KMSDRM_SYM
#تعریف_کړه SDL_KMSDRM_SYM(rc,fn,params)
#د_که_پای

#که_نه_تعریف_شوی SDL_KMSDRM_SYM_CONST
#تعریف_کړه SDL_KMSDRM_SYM_CONST(type, name)
#د_که_پای

#که_نه_تعریف_شوی SDL_KMSDRM_SYM_OPT
#تعریف_کړه SDL_KMSDRM_SYM_OPT(rc,fn,params)
#د_که_پای


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Resources,(drm_ډېرپېښ_Res_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_FB,(drm_ډېرپېښ_FBPtr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Crtc,(drm_ډېرپېښ_Crtc_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Connector,(drm_ډېرپېښ_Connector_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Encoder,(drm_ډېرپېښ_Encoder_Ptr ptr))
SDL_KMSDRM_SYM(صحيح,drmGetCap,(صحيح fd, uint64_t capability, uint64_t *ارزښت))
SDL_KMSDRM_SYM(صحيح,drm_سېټ_Master,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drmDropMaster,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drmAuthMagic,(صحيح fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Res_Ptr,drm_ډېرپېښ_Get_Resources,(صحيح fd))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_جمع_کړه_FB,(صحيح fd, uint32_t پلنوالی, uint32_t لوړوالی, uint8_t ژوروالی_2,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(صحيح,drm_ډېرپېښ_جمع_کړه_FB2,(صحيح fd, uint32_t پلنوالی, uint32_t لوړوالی,
                         uint32_t pixel_format, ثابت uint32_t bo_handles[4],
                         ثابت uint32_t pitches[4], ثابت uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(صحيح,drm_ډېرپېښ_جمع_کړه_FB2_With_Modifiers,(صحيح fd, uint32_t پلنوالی,
                         uint32_t لوړوالی, uint32_t pixel_format, ثابت uint32_t bo_handles[4],
                         ثابت uint32_t pitches[4], ثابت uint32_t offsets[4],
                         ثابت uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ثابت حرف *,drm_ډېرپېښ_Get_Connector_Type_Name,(uint32_t connector_type))

SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Rm_FB,(صحيح fd, uint32_t بفر_Id))
SDL_KMSDRM_SYM(drm_ډېرپېښ_FBPtr,drm_ډېرپېښ_Get_FB,(صحيح fd, uint32_t buf))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Crtc_Ptr,drm_ډېرپېښ_Get_Crtc,(صحيح fd, uint32_t crtcId))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_سېټ_Crtc,(صحيح fd, uint32_t crtcId, uint32_t بفر_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, صحيح شمېر,
                                   drm_ډېرپېښ_ډېرپېښ_Info_Ptr ډېرپېښ))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_سېټ_Cursor,(صحيح fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t پلنوالی, uint32_t لوړوالی))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_سېټ_Cursor2,(صحيح fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t پلنوالی, uint32_t لوړوالی,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Move_Cursor,(صحيح fd, uint32_t crtcId, صحيح x, صحيح y))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Encoder_Ptr,drm_ډېرپېښ_Get_Encoder,(صحيح fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Connector_Ptr,drm_ډېرپېښ_Get_Connector,(صحيح fd, uint32_t connector_id))
SDL_KMSDRM_SYM(صحيح,drmHandleEvent,(صحيح fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_پاڼه_Flip,(صحيح fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, فراغ *user_معلومات_2))

// Planes stuff.
SDL_KMSDRM_SYM(صحيح,drm_سېټ_Client_Cap,(صحيح fd, uint64_t capability, uint64_t ارزښت))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Plane_Res_Ptr,drm_ډېرپېښ_Get_Plane_Resources,(صحيح fd))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Plane_Ptr,drm_ډېرپېښ_Get_Plane,(صحيح fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Object_Properties_Ptr,drm_ډېرپېښ_Object_Get_Properties,(صحيح fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Object_سېټ_Property,(صحيح fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t ارزښت))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Property_Ptr,drm_ډېرپېښ_Get_Property,(صحيح fd, uint32_t propertyId))

SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Property,(drm_ډېرپېښ_Property_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Object_Properties,(drm_ډېرپېښ_Object_Properties_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Plane,(drm_ډېرپېښ_Plane_Ptr ptr))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Free_Plane_Resources,(drm_ډېرپېښ_Plane_Res_Ptr ptr))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_سېټ_Plane,(صحيح fd, uint32_t plane_id, uint32_t crtc_id,
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
SDL_KMSDRM_SYM(بینښه صحيح,gbm_bo_get_پلنوالی,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(بینښه صحيح,gbm_bo_get_لوړوالی,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(اتحاد gbm_bo_handle,gbm_bo_get_handle,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(صحيح,gbm_bo_write,(بنية gbm_bo *bo, ثابت فراغ *buf, size_t شمېر))
SDL_KMSDRM_SYM(بنية gbm_device *,gbm_bo_get_device,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(فراغ,gbm_bo_سېټ_user_معلومات,(بنية gbm_bo *bo, فراغ *معلومات,
                                          فراغ (*destroy_user_معلومات)(بنية gbm_bo *, فراغ *)))
SDL_KMSDRM_SYM(فراغ *,gbm_bo_get_user_معلومات,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(فراغ,gbm_bo_destroy,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM(بنية gbm_bo *,gbm_bo_create,(بنية gbm_device *gbm,
                                              uint32_t پلنوالی, uint32_t لوړوالی,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(بنية gbm_surface *,gbm_surface_create,(بنية gbm_device *gbm,
                                                        uint32_t پلنوالی, uint32_t لوړوالی,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(فراغ,gbm_surface_destroy,(بنية gbm_surface *surf))
SDL_KMSDRM_SYM(بنية gbm_bo *,gbm_surface_قلف_front_بفر,(بنية gbm_surface *surf))
SDL_KMSDRM_SYM(فراغ,gbm_surface_release_بفر,(بنية gbm_surface *surf, بنية gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(صحيح,gbm_bo_get_plane_شمېر,(بنية gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_دننه_واټن,(بنية gbm_bo *bo, صحيح plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(بنية gbm_bo *bo, صحيح plane))
SDL_KMSDRM_SYM_OPT(اتحاد gbm_bo_handle,gbm_bo_get_handle_for_plane,(بنية gbm_bo *bo, صحيح plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(صحيح,drmIoctl,(صحيح fd, بینښه اوږد request, فراغ *arg))
SDL_KMSDRM_SYM(drm_ډېرپېښ_Atomic_Req_Ptr,drm_ډېرپېښ_Atomic_Alloc,(فراغ))
SDL_KMSDRM_SYM(فراغ,drm_ډېرپېښ_Atomic_Free,(drm_ډېرپېښ_Atomic_Req_Ptr req))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Atomic_Commit,(صحيح fd,drm_ډېرپېښ_Atomic_Req_Ptr req,uint32_t flags,فراغ *user_معلومات_2))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Atomic_جمع_کړه_Property,(drm_ډېرپېښ_Atomic_Req_Ptr req,uint32_t object_id,uint32_t property_id,uint64_t ارزښت))
SDL_KMSDRM_SYM(صحيح,drm_ډېرپېښ_Create_Property_Blob,(صحيح fd,ثابت فراغ *معلومات,size_t اندازه,uint32_t *id))


#تعریف_لغوه SDL_KMSDRM_MODULE
#تعریف_لغوه SDL_KMSDRM_SYM
#تعریف_لغوه SDL_KMSDRM_SYM_CONST
#تعریف_لغوه SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
