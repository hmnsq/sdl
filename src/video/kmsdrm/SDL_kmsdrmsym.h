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

#यदि_अपरिभाषितम् SDL_KMSDRM_MODULE
#परिभाषय SDL_KMSDRM_MODULE(modname)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_KMSDRM_SYM
#परिभाषय SDL_KMSDRM_SYM(rc,fn,params)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_KMSDRM_SYM_CONST
#परिभाषय SDL_KMSDRM_SYM_CONST(type, name)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_KMSDRM_SYM_OPT
#परिभाषय SDL_KMSDRM_SYM_OPT(rc,fn,params)
#यदि_अन्तः


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Resources,(drm_बहुलकम्_Res_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_FB,(drm_बहुलकम्_FBPtr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Crtc,(drm_बहुलकम्_Crtc_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Connector,(drm_बहुलकम्_Connector_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Encoder,(drm_बहुलकम्_Encoder_Ptr ptr))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmGetCap,(पूर्णाङ्क fd, uint64_t capability, uint64_t *मानम्))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_समुच्चयः_Master,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmDropMaster,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmAuthMagic,(पूर्णाङ्क fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drm_बहुलकम्_Res_Ptr,drm_बहुलकम्_Get_Resources,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_सङ्कलय_FB,(पूर्णाङ्क fd, uint32_t विस्तारः, uint32_t height, uint8_t गभीरता_2,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,drm_बहुलकम्_सङ्कलय_FB2,(पूर्णाङ्क fd, uint32_t विस्तारः, uint32_t height,
                         uint32_t pixel_format, ध्रुव uint32_t bo_handles[4],
                         ध्रुव uint32_t pitches[4], ध्रुव uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,drm_बहुलकम्_सङ्कलय_FB2_With_Modifiers,(पूर्णाङ्क fd, uint32_t विस्तारः,
                         uint32_t height, uint32_t pixel_format, ध्रुव uint32_t bo_handles[4],
                         ध्रुव uint32_t pitches[4], ध्रुव uint32_t offsets[4],
                         ध्रुव uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ध्रुव वर्ण *,drm_बहुलकम्_Get_Connector_Type_Name,(uint32_t connector_type))

SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Rm_FB,(पूर्णाङ्क fd, uint32_t बफर_Id))
SDL_KMSDRM_SYM(drm_बहुलकम्_FBPtr,drm_बहुलकम्_Get_FB,(पूर्णाङ्क fd, uint32_t buf))
SDL_KMSDRM_SYM(drm_बहुलकम्_Crtc_Ptr,drm_बहुलकम्_Get_Crtc,(पूर्णाङ्क fd, uint32_t crtcId))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_समुच्चयः_Crtc,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t बफर_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, पूर्णाङ्क गणनम्,
                                   drm_बहुलकम्_बहुलकम्_Info_Ptr बहुलकम्))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_समुच्चयः_Cursor,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t विस्तारः, uint32_t height))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_समुच्चयः_Cursor2,(पूर्णाङ्क fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t विस्तारः, uint32_t height,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Move_Cursor,(पूर्णाङ्क fd, uint32_t crtcId, पूर्णाङ्क x, पूर्णाङ्क y))
SDL_KMSDRM_SYM(drm_बहुलकम्_Encoder_Ptr,drm_बहुलकम्_Get_Encoder,(पूर्णाङ्क fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drm_बहुलकम्_Connector_Ptr,drm_बहुलकम्_Get_Connector,(पूर्णाङ्क fd, uint32_t connector_id))
SDL_KMSDRM_SYM(पूर्णाङ्क,drmHandleEvent,(पूर्णाङ्क fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Page_Flip,(पूर्णाङ्क fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, शून्य *user_दत्त_2))

// Planes stuff.
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_समुच्चयः_Client_Cap,(पूर्णाङ्क fd, uint64_t capability, uint64_t मानम्))
SDL_KMSDRM_SYM(drm_बहुलकम्_Plane_Res_Ptr,drm_बहुलकम्_Get_Plane_Resources,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(drm_बहुलकम्_Plane_Ptr,drm_बहुलकम्_Get_Plane,(पूर्णाङ्क fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drm_बहुलकम्_Object_Properties_Ptr,drm_बहुलकम्_Object_Get_Properties,(पूर्णाङ्क fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Object_समुच्चयः_Property,(पूर्णाङ्क fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t मानम्))
SDL_KMSDRM_SYM(drm_बहुलकम्_Property_Ptr,drm_बहुलकम्_Get_Property,(पूर्णाङ्क fd, uint32_t propertyId))

SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Property,(drm_बहुलकम्_Property_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Object_Properties,(drm_बहुलकम्_Object_Properties_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Plane,(drm_बहुलकम्_Plane_Ptr ptr))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Free_Plane_Resources,(drm_बहुलकम्_Plane_Res_Ptr ptr))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_समुच्चयः_Plane,(पूर्णाङ्क fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(पूर्णाङ्क,gbm_device_is_format_supported,(संरचना gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(शून्य,gbm_device_destroy,(संरचना gbm_device *gbm))
SDL_KMSDRM_SYM(संरचना gbm_device *,gbm_create_device,(पूर्णाङ्क fd))
SDL_KMSDRM_SYM(अचिह्नित पूर्णाङ्क,gbm_bo_get_विस्तारः,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(अचिह्नित पूर्णाङ्क,gbm_bo_get_height,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(सङ्घ gbm_bo_handle,gbm_bo_get_handle,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(पूर्णाङ्क,gbm_bo_write,(संरचना gbm_bo *bo, ध्रुव शून्य *buf, size_t गणनम्))
SDL_KMSDRM_SYM(संरचना gbm_device *,gbm_bo_get_device,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(शून्य,gbm_bo_समुच्चयः_user_दत्त,(संरचना gbm_bo *bo, शून्य *दत्त,
                                          शून्य (*destroy_user_दत्त)(संरचना gbm_bo *, शून्य *)))
SDL_KMSDRM_SYM(शून्य *,gbm_bo_get_user_दत्त,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(शून्य,gbm_bo_destroy,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM(संरचना gbm_bo *,gbm_bo_create,(संरचना gbm_device *gbm,
                                              uint32_t विस्तारः, uint32_t height,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(संरचना gbm_surface *,gbm_surface_create,(संरचना gbm_device *gbm,
                                                        uint32_t विस्तारः, uint32_t height,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(शून्य,gbm_surface_destroy,(संरचना gbm_surface *surf))
SDL_KMSDRM_SYM(संरचना gbm_bo *,gbm_surface_तालकम्_front_बफर,(संरचना gbm_surface *surf))
SDL_KMSDRM_SYM(शून्य,gbm_surface_release_बफर,(संरचना gbm_surface *surf, संरचना gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(पूर्णाङ्क,gbm_bo_get_plane_गणनम्,(संरचना gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_विस्थापनम्,(संरचना gbm_bo *bo, पूर्णाङ्क plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(संरचना gbm_bo *bo, पूर्णाङ्क plane))
SDL_KMSDRM_SYM_OPT(सङ्घ gbm_bo_handle,gbm_bo_get_handle_for_plane,(संरचना gbm_bo *bo, पूर्णाङ्क plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(पूर्णाङ्क,drmIoctl,(पूर्णाङ्क fd, अचिह्नित दीर्घ request, शून्य *arg))
SDL_KMSDRM_SYM(drm_बहुलकम्_Atomic_Req_Ptr,drm_बहुलकम्_Atomic_Alloc,(शून्य))
SDL_KMSDRM_SYM(शून्य,drm_बहुलकम्_Atomic_Free,(drm_बहुलकम्_Atomic_Req_Ptr req))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Atomic_Commit,(पूर्णाङ्क fd,drm_बहुलकम्_Atomic_Req_Ptr req,uint32_t flags,शून्य *user_दत्त_2))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Atomic_सङ्कलय_Property,(drm_बहुलकम्_Atomic_Req_Ptr req,uint32_t object_id,uint32_t property_id,uint64_t मानम्))
SDL_KMSDRM_SYM(पूर्णाङ्क,drm_बहुलकम्_Create_Property_Blob,(पूर्णाङ्क fd,ध्रुव शून्य *दत्त,size_t आकार,uint32_t *id))


#अपरिभाषय SDL_KMSDRM_MODULE
#अपरिभाषय SDL_KMSDRM_SYM
#अपरिभाषय SDL_KMSDRM_SYM_CONST
#अपरिभाषय SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
