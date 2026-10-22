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

#నిర్వచితం_కాకపోతే SDL_KMSDRM_MODULE
#నిర్వచించు SDL_KMSDRM_MODULE(modname)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_KMSDRM_SYM
#నిర్వచించు SDL_KMSDRM_SYM(rc,fn,params)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_KMSDRM_SYM_CONST
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_KMSDRM_SYM_OPT
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc,fn,params)
#అయితే_ముగింపు


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Resources,(drm_బహుళకం_Res_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_FB,(drm_బహుళకం_FBPtr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Crtc,(drm_బహుళకం_Crtc_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Connector,(drm_బహుళకం_Connector_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Encoder,(drm_బహుళకం_Encoder_Ptr ptr))
SDL_KMSDRM_SYM(పూర్ణాంకం,drmGetCap,(పూర్ణాంకం fd, uint64_t capability, uint64_t *విలువ))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_సమితి_Master,(పూర్ణాంకం fd))
SDL_KMSDRM_SYM(పూర్ణాంకం,drmDropMaster,(పూర్ణాంకం fd))
SDL_KMSDRM_SYM(పూర్ణాంకం,drmAuthMagic,(పూర్ణాంకం fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drm_బహుళకం_Res_Ptr,drm_బహుళకం_Get_Resources,(పూర్ణాంకం fd))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_కూడు_FB,(పూర్ణాంకం fd, uint32_t వెడల్పు, uint32_t ఎత్తు, uint8_t లోతు_2,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(పూర్ణాంకం,drm_బహుళకం_కూడు_FB2,(పూర్ణాంకం fd, uint32_t వెడల్పు, uint32_t ఎత్తు,
                         uint32_t pixel_format, స్థిరరాశి uint32_t bo_handles[4],
                         స్థిరరాశి uint32_t pitches[4], స్థిరరాశి uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(పూర్ణాంకం,drm_బహుళకం_కూడు_FB2_With_Modifiers,(పూర్ణాంకం fd, uint32_t వెడల్పు,
                         uint32_t ఎత్తు, uint32_t pixel_format, స్థిరరాశి uint32_t bo_handles[4],
                         స్థిరరాశి uint32_t pitches[4], స్థిరరాశి uint32_t offsets[4],
                         స్థిరరాశి uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(స్థిరరాశి అక్షరం *,drm_బహుళకం_Get_Connector_Type_Name,(uint32_t connector_type))

SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Rm_FB,(పూర్ణాంకం fd, uint32_t బఫరు_Id))
SDL_KMSDRM_SYM(drm_బహుళకం_FBPtr,drm_బహుళకం_Get_FB,(పూర్ణాంకం fd, uint32_t buf))
SDL_KMSDRM_SYM(drm_బహుళకం_Crtc_Ptr,drm_బహుళకం_Get_Crtc,(పూర్ణాంకం fd, uint32_t crtcId))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_సమితి_Crtc,(పూర్ణాంకం fd, uint32_t crtcId, uint32_t బఫరు_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, పూర్ణాంకం లెక్క,
                                   drm_బహుళకం_బహుళకం_Info_Ptr బహుళకం))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_సమితి_Cursor,(పూర్ణాంకం fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t వెడల్పు, uint32_t ఎత్తు))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_సమితి_Cursor2,(పూర్ణాంకం fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t వెడల్పు, uint32_t ఎత్తు,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Move_Cursor,(పూర్ణాంకం fd, uint32_t crtcId, పూర్ణాంకం x, పూర్ణాంకం y))
SDL_KMSDRM_SYM(drm_బహుళకం_Encoder_Ptr,drm_బహుళకం_Get_Encoder,(పూర్ణాంకం fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drm_బహుళకం_Connector_Ptr,drm_బహుళకం_Get_Connector,(పూర్ణాంకం fd, uint32_t connector_id))
SDL_KMSDRM_SYM(పూర్ణాంకం,drmHandleEvent,(పూర్ణాంకం fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_పుట_Flip,(పూర్ణాంకం fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, శూన్య *user_దత్తాంశం_2))

// Planes stuff.
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_సమితి_Client_Cap,(పూర్ణాంకం fd, uint64_t capability, uint64_t విలువ))
SDL_KMSDRM_SYM(drm_బహుళకం_Plane_Res_Ptr,drm_బహుళకం_Get_Plane_Resources,(పూర్ణాంకం fd))
SDL_KMSDRM_SYM(drm_బహుళకం_Plane_Ptr,drm_బహుళకం_Get_Plane,(పూర్ణాంకం fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drm_బహుళకం_Object_Properties_Ptr,drm_బహుళకం_Object_Get_Properties,(పూర్ణాంకం fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Object_సమితి_Property,(పూర్ణాంకం fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t విలువ))
SDL_KMSDRM_SYM(drm_బహుళకం_Property_Ptr,drm_బహుళకం_Get_Property,(పూర్ణాంకం fd, uint32_t propertyId))

SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Property,(drm_బహుళకం_Property_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Object_Properties,(drm_బహుళకం_Object_Properties_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Plane,(drm_బహుళకం_Plane_Ptr ptr))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Free_Plane_Resources,(drm_బహుళకం_Plane_Res_Ptr ptr))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_సమితి_Plane,(పూర్ణాంకం fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(పూర్ణాంకం,gbm_device_is_format_supported,(నిర్మాణం gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(శూన్య,gbm_device_destroy,(నిర్మాణం gbm_device *gbm))
SDL_KMSDRM_SYM(నిర్మాణం gbm_device *,gbm_create_device,(పూర్ణాంకం fd))
SDL_KMSDRM_SYM(గుర్తులేని పూర్ణాంకం,gbm_bo_get_వెడల్పు,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(గుర్తులేని పూర్ణాంకం,gbm_bo_get_ఎత్తు,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(సంఘం gbm_bo_handle,gbm_bo_get_handle,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(పూర్ణాంకం,gbm_bo_write,(నిర్మాణం gbm_bo *bo, స్థిరరాశి శూన్య *buf, size_t లెక్క))
SDL_KMSDRM_SYM(నిర్మాణం gbm_device *,gbm_bo_get_device,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(శూన్య,gbm_bo_సమితి_user_దత్తాంశం,(నిర్మాణం gbm_bo *bo, శూన్య *దత్తాంశం,
                                          శూన్య (*destroy_user_దత్తాంశం)(నిర్మాణం gbm_bo *, శూన్య *)))
SDL_KMSDRM_SYM(శూన్య *,gbm_bo_get_user_దత్తాంశం,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(శూన్య,gbm_bo_destroy,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM(నిర్మాణం gbm_bo *,gbm_bo_create,(నిర్మాణం gbm_device *gbm,
                                              uint32_t వెడల్పు, uint32_t ఎత్తు,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(నిర్మాణం gbm_surface *,gbm_surface_create,(నిర్మాణం gbm_device *gbm,
                                                        uint32_t వెడల్పు, uint32_t ఎత్తు,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(శూన్య,gbm_surface_destroy,(నిర్మాణం gbm_surface *surf))
SDL_KMSDRM_SYM(నిర్మాణం gbm_bo *,gbm_surface_తాళం_front_బఫరు,(నిర్మాణం gbm_surface *surf))
SDL_KMSDRM_SYM(శూన్య,gbm_surface_release_బఫరు,(నిర్మాణం gbm_surface *surf, నిర్మాణం gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(పూర్ణాంకం,gbm_bo_get_plane_లెక్క,(నిర్మాణం gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_స్థానభ్రంశం,(నిర్మాణం gbm_bo *bo, పూర్ణాంకం plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(నిర్మాణం gbm_bo *bo, పూర్ణాంకం plane))
SDL_KMSDRM_SYM_OPT(సంఘం gbm_bo_handle,gbm_bo_get_handle_for_plane,(నిర్మాణం gbm_bo *bo, పూర్ణాంకం plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(పూర్ణాంకం,drmIoctl,(పూర్ణాంకం fd, గుర్తులేని దీర్ఘ request, శూన్య *arg))
SDL_KMSDRM_SYM(drm_బహుళకం_Atomic_Req_Ptr,drm_బహుళకం_Atomic_Alloc,(శూన్య))
SDL_KMSDRM_SYM(శూన్య,drm_బహుళకం_Atomic_Free,(drm_బహుళకం_Atomic_Req_Ptr req))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Atomic_Commit,(పూర్ణాంకం fd,drm_బహుళకం_Atomic_Req_Ptr req,uint32_t flags,శూన్య *user_దత్తాంశం_2))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Atomic_కూడు_Property,(drm_బహుళకం_Atomic_Req_Ptr req,uint32_t object_id,uint32_t property_id,uint64_t విలువ))
SDL_KMSDRM_SYM(పూర్ణాంకం,drm_బహుళకం_Create_Property_Blob,(పూర్ణాంకం fd,స్థిరరాశి శూన్య *దత్తాంశం,size_t కొలత,uint32_t *id))


#నిర్వచనం_రద్దు SDL_KMSDRM_MODULE
#నిర్వచనం_రద్దు SDL_KMSDRM_SYM
#నిర్వచనం_రద్దు SDL_KMSDRM_SYM_CONST
#నిర్వచనం_రద్దు SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
