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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_KMSDRM_MODULE
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_MODULE(modname)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_KMSDRM_SYM
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM(rc,fn,params)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_KMSDRM_SYM_CONST
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_CONST(type, name)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_KMSDRM_SYM_OPT
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_KMSDRM_SYM_OPT(rc,fn,params)
#ಆದರೆ_ಅಂತ್ಯ


SDL_KMSDRM_MODULE(LIBDRM)
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Resources,(drm_ಬಹುಲಕ_Res_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_FB,(drm_ಬಹುಲಕ_FBPtr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Crtc,(drm_ಬಹುಲಕ_Crtc_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Connector,(drm_ಬಹುಲಕ_Connector_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Encoder,(drm_ಬಹುಲಕ_Encoder_Ptr ptr))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drmGetCap,(ಪೂರ್ಣಾಂಕ fd, uint64_t capability, uint64_t *ಮೌಲ್ಯ))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಗಣ_Master,(ಪೂರ್ಣಾಂಕ fd))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drmDropMaster,(ಪೂರ್ಣಾಂಕ fd))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drmAuthMagic,(ಪೂರ್ಣಾಂಕ fd, drm_magic_t magic))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Res_Ptr,drm_ಬಹುಲಕ_Get_Resources,(ಪೂರ್ಣಾಂಕ fd))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB,(ಪೂರ್ಣಾಂಕ fd, uint32_t ಅಗಲ, uint32_t ಎತ್ತರ, uint8_t ಆಳ_2,
                         uint8_t bpp, uint32_t pitch, uint32_t bo_handle,
                         uint32_t *buf_id))

SDL_KMSDRM_SYM_OPT(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB2,(ಪೂರ್ಣಾಂಕ fd, uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
                         uint32_t pixel_format, ಸ್ಥಿರಾಂಕ uint32_t bo_handles[4],
                         ಸ್ಥಿರಾಂಕ uint32_t pitches[4], ಸ್ಥಿರಾಂಕ uint32_t offsets[4],
                         uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB2_With_Modifiers,(ಪೂರ್ಣಾಂಕ fd, uint32_t ಅಗಲ,
                         uint32_t ಎತ್ತರ, uint32_t pixel_format, ಸ್ಥಿರಾಂಕ uint32_t bo_handles[4],
                         ಸ್ಥಿರಾಂಕ uint32_t pitches[4], ಸ್ಥಿರಾಂಕ uint32_t offsets[4],
                         ಸ್ಥಿರಾಂಕ uint64_t modifier[4], uint32_t *buf_id, uint32_t flags))

SDL_KMSDRM_SYM_OPT(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *,drm_ಬಹುಲಕ_Get_Connector_Type_Name,(uint32_t connector_type))

SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Rm_FB,(ಪೂರ್ಣಾಂಕ fd, uint32_t ಬಫರ್_Id))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_FBPtr,drm_ಬಹುಲಕ_Get_FB,(ಪೂರ್ಣಾಂಕ fd, uint32_t buf))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Crtc_Ptr,drm_ಬಹುಲಕ_Get_Crtc,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtcId))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಗಣ_Crtc,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtcId, uint32_t ಬಫರ್_Id,
                                   uint32_t x, uint32_t y, uint32_t *connectors, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2,
                                   drm_ಬಹುಲಕ_ಬಹುಲಕ_Info_Ptr ಬಹುಲಕ))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಗಣ_Cursor,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtcId, uint32_t bo_handle,
                                     uint32_t ಅಗಲ, uint32_t ಎತ್ತರ))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಗಣ_Cursor2,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtcId, uint32_t bo_handle,
                                      uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
                                      int32_t hot_x, int32_t hot_y))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Move_Cursor,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtcId, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Encoder_Ptr,drm_ಬಹುಲಕ_Get_Encoder,(ಪೂರ್ಣಾಂಕ fd, uint32_t encoder_id))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Connector_Ptr,drm_ಬಹುಲಕ_Get_Connector,(ಪೂರ್ಣಾಂಕ fd, uint32_t connector_id))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drmHandleEvent,(ಪೂರ್ಣಾಂಕ fd,drmEventContextPtr evctx))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಪುಟ_Flip,(ಪೂರ್ಣಾಂಕ fd, uint32_t crtc_id, uint32_t fb_id,
                                    uint32_t flags, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2))

// Planes stuff.
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಗಣ_Client_Cap,(ಪೂರ್ಣಾಂಕ fd, uint64_t capability, uint64_t ಮೌಲ್ಯ))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Plane_Res_Ptr,drm_ಬಹುಲಕ_Get_Plane_Resources,(ಪೂರ್ಣಾಂಕ fd))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Plane_Ptr,drm_ಬಹುಲಕ_Get_Plane,(ಪೂರ್ಣಾಂಕ fd, uint32_t plane_id))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Object_Properties_Ptr,drm_ಬಹುಲಕ_Object_Get_Properties,(ಪೂರ್ಣಾಂಕ fd,uint32_t object_id,uint32_t object_type))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Object_ಗಣ_Property,(ಪೂರ್ಣಾಂಕ fd, uint32_t object_id,
                                             uint32_t object_type, uint32_t property_id,
                                             uint64_t ಮೌಲ್ಯ))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Property_Ptr,drm_ಬಹುಲಕ_Get_Property,(ಪೂರ್ಣಾಂಕ fd, uint32_t propertyId))

SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Property,(drm_ಬಹುಲಕ_Property_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Object_Properties,(drm_ಬಹುಲಕ_Object_Properties_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Plane,(drm_ಬಹುಲಕ_Plane_Ptr ptr))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Free_Plane_Resources,(drm_ಬಹುಲಕ_Plane_Res_Ptr ptr))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_ಗಣ_Plane,(ಪೂರ್ಣಾಂಕ fd, uint32_t plane_id, uint32_t crtc_id,
                                    uint32_t fb_id, uint32_t flags,
                                    int32_t crtc_x, int32_t crtc_y,
                                    uint32_t crtc_w, uint32_t crtc_h,
                                    uint32_t src_x, uint32_t src_y,
                                    uint32_t src_w, uint32_t src_h))
// Planes stuff ends.

SDL_KMSDRM_MODULE(GBM)
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,gbm_device_is_format_supported,(ರಚನೆ gbm_device *gbm,
                                                   uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,gbm_device_destroy,(ರಚನೆ gbm_device *gbm))
SDL_KMSDRM_SYM(ರಚನೆ gbm_device *,gbm_create_device,(ಪೂರ್ಣಾಂಕ fd))
SDL_KMSDRM_SYM(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ,gbm_bo_get_ಅಗಲ,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ,gbm_bo_get_ಎತ್ತರ,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_stride,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(uint32_t,gbm_bo_get_format,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ಒಕ್ಕೂಟ gbm_bo_handle,gbm_bo_get_handle,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,gbm_bo_write,(ರಚನೆ gbm_bo *bo, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *buf, size_t ಎಣಿಕೆ_2))
SDL_KMSDRM_SYM(ರಚನೆ gbm_device *,gbm_bo_get_device,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,gbm_bo_ಗಣ_user_ದತ್ತಾಂಶ,(ರಚನೆ gbm_bo *bo, ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                          ಶೂನ್ಯ (*destroy_user_ದತ್ತಾಂಶ)(ರಚನೆ gbm_bo *, ಶೂನ್ಯ *)))
SDL_KMSDRM_SYM(ಶೂನ್ಯ *,gbm_bo_get_user_ದತ್ತಾಂಶ,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,gbm_bo_destroy,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM(ರಚನೆ gbm_bo *,gbm_bo_create,(ರಚನೆ gbm_device *gbm,
                                              uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
                                              uint32_t format, uint32_t usage))
SDL_KMSDRM_SYM(ರಚನೆ gbm_surface *,gbm_surface_create,(ರಚನೆ gbm_device *gbm,
                                                        uint32_t ಅಗಲ, uint32_t ಎತ್ತರ,
                                                        uint32_t format, uint32_t flags))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,gbm_surface_destroy,(ರಚನೆ gbm_surface *surf))
SDL_KMSDRM_SYM(ರಚನೆ gbm_bo *,gbm_surface_ಬೀಗ_front_ಬಫರ್,(ರಚನೆ gbm_surface *surf))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,gbm_surface_release_ಬಫರ್,(ರಚನೆ gbm_surface *surf, ರಚನೆ gbm_bo *bo))

SDL_KMSDRM_SYM_OPT(uint64_t,gbm_bo_get_modifier,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(ಪೂರ್ಣಾಂಕ,gbm_bo_get_plane_ಎಣಿಕೆ,(ರಚನೆ gbm_bo *bo))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_ಸ್ಥಾನಾಂತರ,(ರಚನೆ gbm_bo *bo, ಪೂರ್ಣಾಂಕ plane))
SDL_KMSDRM_SYM_OPT(uint32_t,gbm_bo_get_stride_for_plane,(ರಚನೆ gbm_bo *bo, ಪೂರ್ಣಾಂಕ plane))
SDL_KMSDRM_SYM_OPT(ಒಕ್ಕೂಟ gbm_bo_handle,gbm_bo_get_handle_for_plane,(ರಚನೆ gbm_bo *bo, ಪೂರ್ಣಾಂಕ plane))


SDL_KMSDRM_MODULE(ATOMIC)
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drmIoctl,(ಪೂರ್ಣಾಂಕ fd, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ request, ಶೂನ್ಯ *arg))
SDL_KMSDRM_SYM(drm_ಬಹುಲಕ_Atomic_Req_Ptr,drm_ಬಹುಲಕ_Atomic_Alloc,(ಶೂನ್ಯ))
SDL_KMSDRM_SYM(ಶೂನ್ಯ,drm_ಬಹುಲಕ_Atomic_Free,(drm_ಬಹುಲಕ_Atomic_Req_Ptr req))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Atomic_Commit,(ಪೂರ್ಣಾಂಕ fd,drm_ಬಹುಲಕ_Atomic_Req_Ptr req,uint32_t flags,ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Atomic_ಕೂಡಿಸು_Property,(drm_ಬಹುಲಕ_Atomic_Req_Ptr req,uint32_t object_id,uint32_t property_id,uint64_t ಮೌಲ್ಯ))
SDL_KMSDRM_SYM(ಪೂರ್ಣಾಂಕ,drm_ಬಹುಲಕ_Create_Property_Blob,(ಪೂರ್ಣಾಂಕ fd,ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ,size_t ಗಾತ್ರ_2,uint32_t *id))


#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_KMSDRM_MODULE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_KMSDRM_SYM
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_KMSDRM_SYM_CONST
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_KMSDRM_SYM_OPT

/* *INDENT-ON* */ // clang-format on
