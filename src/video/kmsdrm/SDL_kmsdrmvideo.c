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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"

// SDL internals
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#ಅಥವಾಆದರೆ defined SDL_ಒಳಹರಿವು_WSCONS
#ಅನ್ತರ್ಭಾವ "../../core/openbsd/SDL_wscons.h"
#ಆದರೆ_ಅಂತ್ಯ

// KMS/DRM declarations
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvulkan.h"
#ಅನ್ತರ್ಭಾವ <dirent.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <poll.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <sys/stat.h>
#ಅನ್ತರ್ಭಾವ <sys/utsname.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OPENBSD
ಸ್ಥಿರ bool moderndri = false;
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ bool moderndri = true;
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಅಕ್ಷರ kmsdrm_dri_ಮಾರ್ಗ[16];
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ kmsdrm_dri_pathsize = 0;
ಸ್ಥಿರ ಅಕ್ಷರ kmsdrm_dri_devname[8];
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ kmsdrm_dri_devnamesize = 0;
ಸ್ಥಿರ ಅಕ್ಷರ kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_FORMAT_MOD_VENDOR_NONE
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_FORMAT_MOD_VENDOR_NONE 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DRM_FORMAT_MOD_ರೇಖೀಯ
#ವ್ಯಾಖ್ಯಾನಿಸು DRM_FORMAT_MOD_ರೇಖೀಯ fourcc_mod_ಸಂಕೇತ(NONE, 0)
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_driindex(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ ಲಭ್ಯ = -ENOENT;
    ಅಕ್ಷರ device[ಗಾತ್ರ(kmsdrm_dri_cardpath)];
    ಪೂರ್ಣಾಂಕ drm_fd;
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ devindex = -1;
    DIR *folder;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;
    ರಚನೆ dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_ಸೂಚ್ಯಂಕ);
    ಆದರೆ (hint && *hint) {
        ಅಕ್ಷರ *endptr = ಖಾಲಿ;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ idx = (ಪೂರ್ಣಾಂಕ)SDL_strtol(hint, &endptr, 10);
        ಆದರೆ ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            ಹಿಂತಿರುಗಿ idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_ಮಾರ್ಗ, ಗಾತ್ರ(device));
    folder = opendir(device);
    ಆದರೆ (!folder) {
        SDL_ಗಣ_Error("Failed to open directory '%s'", device);
        ಹಿಂತಿರುಗಿ -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                ಗಾತ್ರ(device) - kmsdrm_dri_pathsize);
    ಆಗ((res = readdir(folder)) != ಖಾಲಿ && ಲಭ್ಯ < 0) {
        ಆದರೆ (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        ಗಾತ್ರ(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            ಆದರೆ (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                ಆದರೆ (SDL_KMSDRM_ತುಂಬು_Symbols()) {
                    drm_ಬಹುಲಕ_Res *resources = KMSDRM_drm_ಬಹುಲಕ_Get_Resources(drm_fd);
                    ಆದರೆ (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->ಎಣಿಕೆ_connectors,
                                     resources->ಎಣಿಕೆ_encoders,
                                     resources->ಎಣಿಕೆ_crtcs);

                        ಆದರೆ (resources->ಎಣಿಕೆ_connectors > 0 &&
                            resources->ಎಣಿಕೆ_encoders > 0 &&
                            resources->ಎಣಿಕೆ_crtcs > 0) {
                            ಲಭ್ಯ = -ENOENT;
                            ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_connectors && ಲಭ್ಯ < 0; i++) {
                                drm_ಬಹುಲಕ_Connector *conn =
                                    KMSDRM_drm_ಬಹುಲಕ_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                ಆದರೆ (!conn) {
                                    ಮುಂದುವರಿ;
                                }

                                ಆದರೆ (conn->connection == DRM_ಬಹುಲಕ_CONNECTED &&
                                    conn->ಎಣಿಕೆ_modes) {
                                    bool access_denied = false;
                                    ಆದರೆ (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_ಗಣ_Master(drm_fd);
                                        ಆದರೆ (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    ಆದರೆ (!access_denied) {
                                        ಲಭ್ಯ = devindex;
                                    }
                                }

                                KMSDRM_drm_ಬಹುಲಕ_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_ಬಹುಲಕ_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    ಹಿಂತಿರುಗಿ ಲಭ್ಯ;
}

ಸ್ಥಿರ ಶೂನ್ಯ Calculate_Refresh_ದರ(drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಬಹುಲಕ, ಪೂರ್ಣಾಂಕ *numerator, ಪೂರ್ಣಾಂಕ *denominator)
{
    *numerator = ಬಹುಲಕ->clock * 1000;
    *denominator = ಬಹುಲಕ->htotal * ಬಹುಲಕ->vtotal;

    ಆದರೆ (ಬಹುಲಕ->flags & DRM_ಬಹುಲಕ_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    ಆದರೆ (ಬಹುಲಕ->flags & DRM_ಬಹುಲಕ_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    ಆದರೆ (ಬಹುಲಕ->vscan > 1) {
        *denominator *= ಬಹುಲಕ->vscan;
    }
}


ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_connector_property(drm_ಬಹುಲಕ_Atomic_Req *req, KMSDRM_connector *conn, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ)
{
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ prop_id = 0;

    ಗಾಗಿ (i = 0 ; i < conn->props->ಎಣಿಕೆ_props ; i++) {
        ಆದರೆ (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (prop_id < 0) {
        SDL_ಗಣ_Error("no connector property: %s", name);
        ಹಿಂತಿರುಗಿ -EINVAL;
    }

    ಹಿಂತಿರುಗಿ KMSDRM_drm_ಬಹುಲಕ_Atomic_ಕೂಡಿಸು_Property(req, conn->connector->connector_id, prop_id, ಮೌಲ್ಯ);
}

ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_crtc_property(drm_ಬಹುಲಕ_Atomic_Req *req, KMSDRM_crtc *c, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ)
{
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ prop_id = -1;

    ಗಾಗಿ (i = 0 ; i < c->props->ಎಣಿಕೆ_props ; i++) {
        ಆದರೆ (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (prop_id < 0) {
        SDL_ಗಣ_Error("no crtc property: %s", name);
        ಹಿಂತಿರುಗಿ -EINVAL;
    }

    ಹಿಂತಿರುಗಿ KMSDRM_drm_ಬಹುಲಕ_Atomic_ಕೂಡಿಸು_Property(req, c->crtc->crtc_id, prop_id, ಮೌಲ್ಯ);
}

ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_plane_property(drm_ಬಹುಲಕ_Atomic_Req *req, KMSDRM_plane *p, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, uint64_t ಮೌಲ್ಯ)
{
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ prop_id = -1;

    ಗಾಗಿ (i = 0 ; i < p->props->ಎಣಿಕೆ_props ; i++) {
        ಆದರೆ (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (prop_id < 0) {
        SDL_ಗಣ_Error("no plane property: %s", name);
        ಹಿಂತಿರುಗಿ -EINVAL;
    }

    ಹಿಂತಿರುಗಿ KMSDRM_drm_ಬಹುಲಕ_Atomic_ಕೂಡಿಸು_Property(req, p->plane->plane_id, prop_id, ಮೌಲ್ಯ);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_KMSDRM
ಸ್ಥಿರ ಶೂನ್ಯ print_plane_info(SDL_VideoDevice *_this, drm_ಬಹುಲಕ_Plane_Ptr plane)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = ((SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ);
    drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_ಬಹುಲಕ_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < props->ಎಣಿಕೆ_props; i++) {
        drm_ಬಹುಲಕ_Property_Ptr p = KMSDRM_drm_ಬಹುಲಕ_Get_Property(viddata->drm_fd, props->props[i]);
        ಆದರೆ ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_ಮೌಲ್ಯಗಳು[i];
        }

        KMSDRM_drm_ಬಹುಲಕ_Free_Property(p);
    }

    ಅಕ್ಷರ *plane_type = "unknown";
    ಆಯ್ಕೆ (type) {
        ಸ್ಥಿತಿ DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            ನಿಲ್ಲಿಸು;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_ಬಹುಲಕ_Res *resources = KMSDRM_drm_ಬಹುಲಕ_Get_Resources(viddata->drm_fd);
    ಆದರೆ (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < resources->ಎಣಿಕೆ_crtcs; i++) {
            ಆದರೆ (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                ನಿಲ್ಲಿಸು;
            }
        }
        SDL_Log("%s\n\n", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)SDL_Get_ಸೂಚಕ_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_ಸ್ಮರಣೆ_ಸೂಚಕ, ""));
        SDL_CloseIO(io);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ get_planes_info(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = ((SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ);

    drm_ಬಹುಲಕ_Plane_Res_Ptr plane_resources = KMSDRM_drm_ಬಹುಲಕ_Get_Plane_Resources(viddata->drm_fd);
    ಆದರೆ (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->ಎಣಿಕೆ_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    ಗಾಗಿ (uint32_t i = 0; (i < plane_resources->ಎಣಿಕೆ_planes); i++) {
        ಸ್ಥಿರಾಂಕ uint32_t plane_id = plane_resources->planes[i];

        drm_ಬಹುಲಕ_Plane_Ptr plane = KMSDRM_drm_ಬಹುಲಕ_Get_Plane(viddata->drm_fd, plane_id);
        ಆದರೆ (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            ಮುಂದುವರಿ;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_ಬಹುಲಕ_Free_Plane(plane);
    }

    KMSDRM_drm_ಬಹುಲಕ_Free_Plane_Resources(plane_resources);
}
#ಆದರೆ_ಅಂತ್ಯ

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_plane_id(SDL_VideoDevice *_this, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ crtc_id, uint32_t plane_type)
{
    drm_ಬಹುಲಕ_Res *resources = ಖಾಲಿ;
    drm_ಬಹುಲಕ_Plane_Res_Ptr plane_resources = ಖಾಲಿ;
    uint32_t i, j;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ crtc_ಸೂಚ್ಯಂಕ = 0;
    ಪೂರ್ಣಾಂಕ ret = -EINVAL;
    ಪೂರ್ಣಾಂಕ ಸಿಕ್ಕಿತು = 0;

    SDL_Video_ದತ್ತಾಂಶ *viddata = ((SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ);

    resources = KMSDRM_drm_ಬಹುಲಕ_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_crtcs; i++) {
        ಆದರೆ (resources->crtcs[i] == crtc_id) {
            crtc_ಸೂಚ್ಯಂಕ = i;
            ನಿಲ್ಲಿಸು;
        }
    }

    plane_resources = KMSDRM_drm_ಬಹುಲಕ_Get_Plane_Resources(viddata->drm_fd);
    ಆದರೆ (!plane_resources) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    ಗಾಗಿ (i = 0; (i < plane_resources->ಎಣಿಕೆ_planes) && !ಸಿಕ್ಕಿತು; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_ಬಹುಲಕ_Plane_Ptr plane = KMSDRM_drm_ಬಹುಲಕ_Get_Plane(viddata->drm_fd, plane_id);
        ಆದರೆ (!plane) {
            ಮುಂದುವರಿ;
        }

        /* See if the current CRTC is available for this plane. */
        ಆದರೆ (plane->possible_crtcs & (1 << crtc_ಸೂಚ್ಯಂಕ)) {

            drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_ಬಹುಲಕ_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            ಗಾಗಿ (j = 0; j < props->ಎಣಿಕೆ_props; j++) {

                drm_ಬಹುಲಕ_Property_Ptr p = KMSDRM_drm_ಬಹುಲಕ_Get_Property(viddata->drm_fd,
                    props->props[j]);

                ಆದರೆ ((SDL_strcmp(p->name, "type") == 0) && (props->prop_ಮೌಲ್ಯಗಳು[j] == plane_type)) {
                    /* found our plane, use that: */
                    ಸಿಕ್ಕಿತು = 1;
                }

                KMSDRM_drm_ಬಹುಲಕ_Free_Property(p);
            }

            KMSDRM_drm_ಬಹುಲಕ_Free_Object_Properties(props);
        }

        KMSDRM_drm_ಬಹುಲಕ_Free_Plane(plane);
    }

    KMSDRM_drm_ಬಹುಲಕ_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_ಬಹುಲಕ_Free_Resources(resources);

    ಹಿಂತಿರುಗಿ ret;
}

/* Setup a plane and it's props. */
bool ಸಿದ್ಧತೆ_plane(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_ದತ್ತಾಂಶ *viddata = ((SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ);
    bool ret = true;

    *_plane = SDL_calloc(1, ಗಾತ್ರ(**_plane));
    ಆದರೆ (!(*_plane)) {
        ret = false;
        ಹೋಗು cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    ಆದರೆ (!plane_id) {
        ret = SDL_ಗಣ_Error("Invalid Plane ID");
        ಹೋಗು cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_ಬಹುಲಕ_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    ಆದರೆ ((*_plane)->plane) {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
        (*_plane)->props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_ಬಹುಲಕ_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->ಎಣಿಕೆ_props, ಗಾತ್ರ(*(*_plane)->props_info));

        ಆದರೆ ( !((*_plane)->props_info) ) {
            ret = false;
            ಹೋಗು cleanup;
        }

        ಗಾಗಿ (i = 0; i < (*_plane)->props->ಎಣಿಕೆ_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_ಬಹುಲಕ_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    ಆದರೆ (!ret) {
        ಆದರೆ (*_plane) {
            SDL_free(*_plane);
            *_plane = ಖಾಲಿ;
        }
    }
    ಹಿಂತಿರುಗಿ ret;
}

/* Free a plane and it's props. */
ಶೂನ್ಯ free_plane(KMSDRM_plane **_plane)
{
    ಆದರೆ (*_plane) {
        ಆದರೆ ((*_plane)->plane) {
            KMSDRM_drm_ಬಹುಲಕ_Free_Plane((*_plane)->plane);
            (*_plane)->plane = ಖಾಲಿ;
        }
        ಆದರೆ ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = ಖಾಲಿ;
        }
        SDL_free(*_plane);
        *_plane = ಖಾಲಿ;
    }
}

/**********************************************************************************/
/* The most important ATOMIC fn of the backend.                                   */
/* A PLANE reads a BUFFER, and a CRTC reads a PLANE and sends it's contents       */
/*   over to a CONNECTOR->ENCODER system (several CONNECTORS can be connected     */
/*   to the same PLANE).                                                          */
/*   Think of a plane as a "frame" surrounding a picture, where the "picture"     */
/*   is the buffer, and we move the "frame" from  a picture to another,           */
/*   and the one that has the "frame" is the one sent over to the screen          */
/*   via the CONNECTOR->ENCODER system.                                           */
/*   Think of a PLANE as being "in the middle", it's the CENTRAL part             */
/*   between the CRTC and the BUFFER that is shown on screen.                     */
/*   What we do here is connect a PLANE to a CRTC and a BUFFER.                   */
/*   -ALWAYS set the CRTC_ID and FB_ID attribs of a plane at the same time,       */
/*   meaning IN THE SAME atomic request.                                          */
/*   -And NEVER destroy a GBM surface whose buffers are being read by a plane:    */
/*   first, move the plane away from those buffers and ONLY THEN destroy the      */
/*   buffers and/or the GBM surface containing them.                              */
/**********************************************************************************/
ಶೂನ್ಯ
drm_atomic_ಗಣ_plane_props(SDL_Display_ದತ್ತಾಂಶ *dispdata, ರಚನೆ KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    ಆದರೆ (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_ಬಹುಲಕ_Atomic_Alloc();
    }

    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    ಕೂಡಿಸು_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

ಪೂರ್ಣಾಂಕ drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = ((SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ);
    uint32_t atomic_flags = 0;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!blocking) {
        atomic_flags |= DRM_ಬಹುಲಕ_ATOMIC_NONBLOCK;
    }

    ಆದರೆ (allow_modeset) {
        atomic_flags |= DRM_ಬಹುಲಕ_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_ಬಹುಲಕ_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, ಖಾಲಿ);

    ಆದರೆ (ret) {
        SDL_ಗಣ_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#ಆದರೆ 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#ಆದರೆ_ಅಂತ್ಯ
        ಹೋಗು ಹೊರಹೋಗು;
    }

    ಆದರೆ (dispdata->kms_ಒಳ_fence_fd != -1) {
        close(dispdata->kms_ಒಳ_fence_fd);
        dispdata->kms_ಒಳ_fence_fd = -1;
    }

ಹೊರಹೋಗು:
    KMSDRM_drm_ಬಹುಲಕ_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    ಆದರೆ (dispdata->kms_fence) {
       EGLint ಸ್ಥಿತಿ_2;

        ಮಾಡು {
            ಸ್ಥಿತಿ_2 = _this->egl_ದತ್ತಾಂಶ->eglClientWaitSyncKHR(_this->egl_ದತ್ತಾಂಶ->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } ಆಗ (ಸ್ಥಿತಿ_2 != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_ದತ್ತಾಂಶ->eglDestroySyncKHR(_this->egl_ದತ್ತಾಂಶ->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ bool KMSDRM_ಲಭ್ಯ(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OPENBSD
    ರಚನೆ utsname nameofsystem;
    ದ್ವಿಗುಣ releaseversion;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ret = -ENOENT;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_OPENBSD
    ಆದರೆ (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        ಆದರೆ (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (moderndri) {
        SDL_strlcpy(kmsdrm_dri_ಮಾರ್ಗ, "/dev/dri/", ಗಾತ್ರ(kmsdrm_dri_ಮಾರ್ಗ));
        SDL_strlcpy(kmsdrm_dri_devname, "card", ಗಾತ್ರ(kmsdrm_dri_devname));
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_strlcpy(kmsdrm_dri_ಮಾರ್ಗ, "/dev/", ಗಾತ್ರ(kmsdrm_dri_ಮಾರ್ಗ));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", ಗಾತ್ರ(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_ಮಾರ್ಗ);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (ಶೂನ್ಯ)SDL_snprintf(kmsdrm_dri_cardpath, ಗಾತ್ರ(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_ಮಾರ್ಗ, kmsdrm_dri_devname);

    ret = get_driindex();
    ಆದರೆ (ret >= 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    ಆದರೆ (device->ಆಂತರಿಕ) {
        SDL_free(device->ಆಂತರಿಕ);
        device->ಆಂತರಿಕ = ಖಾಲಿ;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

ಸ್ಥಿರ SDL_VideoDevice *KMSDRM_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *viddata;
    ಪೂರ್ಣಾಂಕ devindex;

    ಆದರೆ (!KMSDRM_ಲಭ್ಯ()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    devindex = get_driindex();
    ಆದರೆ (devindex < 0) {
        SDL_ಗಣ_Error("devindex (%d) must not be negative.", devindex);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_KMSDRM_ತುಂಬು_Symbols()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    viddata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!viddata) {
        ಹೋಗು cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->ಆಂತರಿಕ = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = KMSDRM_ಗಣ_Display_ಬಹುಲಕ;
    device->CreateSDLWindow = KMSDRM_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = KMSDRM_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = KMSDRM_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = KMSDRM_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = KMSDRM_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->Show_ಕಿಟಕಿ = KMSDRM_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = KMSDRM_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = KMSDRM_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = KMSDRM_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = KMSDRM_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = KMSDRM_Restore_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = KMSDRM_Destroy_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Focusable = KMSDRM_ಗಣ_ಕಿಟಕಿ_Focusable;

    device->GL_ತುಂಬು_Library = KMSDRM_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = KMSDRM_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = KMSDRM_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = KMSDRM_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = KMSDRM_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_ಗಣ_Default_Profile_Config = KMSDRM_GLES_ಗಣ_Default_Profile_Config;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = KMSDRM_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#ಆದರೆ_ಅಂತ್ಯ

    device->PumpEvents = KMSDRM_PumpEvents;
    device->ಬಿಡುಗಡೆ = KMSDRM_DeleteDevice;

    ಹಿಂತಿರುಗಿ device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_FBDestroyCallback(ರಚನೆ gbm_bo *bo, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)ದತ್ತಾಂಶ;

    ಆದರೆ (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_ಬಹುಲಕ_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ರಚನೆ gbm_bo *bo)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    ಚಿಹ್ನೆರಹಿತ w, h;
    ಪೂರ್ಣಾಂಕ rc = -1;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_ದತ್ತಾಂಶ(bo);

    ಆದರೆ (fb_info) {
        ಹಿಂತಿರುಗಿ fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, ಗಾತ್ರ(KMSDRM_FBInfo));

    ಆದರೆ (!fb_info) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_ಅಗಲ(bo);
    h = KMSDRM_gbm_bo_get_ಎತ್ತರ(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    ಆದರೆ (KMSDRM_drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_ಎಣಿಕೆ &&
        KMSDRM_gbm_bo_get_ಸ್ಥಾನಾಂತರ &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        ಅಂಕೆ_planes = KMSDRM_gbm_bo_get_plane_ಎಣಿಕೆ(bo);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_ಸ್ಥಾನಾಂತರ(bo, i);
            modifiers[i] = modifiers[0];
        }

        ಆದರೆ (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_ಬಹುಲಕ_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    ಆದರೆ (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_ಬಹುಲಕ_ಕೂಡಿಸು_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    ಆದರೆ (rc < 0) {
        SDL_free(fb_info);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (ಶೂನ್ಯ *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_ಗಣ_user_ದತ್ತಾಂಶ(bo, fb_info, KMSDRM_FBDestroyCallback);

    ಹಿಂತಿರುಗಿ fb_info;
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_FlipHandler(ಪೂರ್ಣಾಂಕ fd, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sec, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ usec, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    *((bool *)ದತ್ತಾಂಶ) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata)
{

    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    drmEventContext ev = { 0 };
    ರಚನೆ pollfd pfd = { 0 };
    ಪೂರ್ಣಾಂಕ ret;

    ev.ಆವೃತ್ತಿ = DRM_EVENT_CONTEXT_ಆವೃತ್ತಿ;
    ev.ಪುಟ_flip_handler = KMSDRM_FlipHandler;

    pfd.fd = viddata->drm_fd;
    pfd.events = POLLIN;

    /* Stay on the while loop until we get the desired event.
       We need the while the loop because we could be in a situation where:
       -We get and event on the FD in time, thus not on exiting on return number 1.
       -The event is not an error, thus not exiting on return number 2.
       -The event is of POLLIN type, but even then, if the event is not a pageflip,
        drmHandleEvent() won't unset wait_for_pageflip, so we have to iterate
        and go polling again.

        If it wasn't for the while loop, we could erroneously exit the function
        without the pageflip event to arrive!

      For example, vblank events hit the FD and they are POLLIN events too (POLLIN
      means "there's data to read on the FD"), but they are not the pageflip event
      we are waiting for, so the drmEventHandle() doesn't run the flip handler, and
      since waiting_for_flip is set on the pageflip handle, it's not set and we stay
      on the loop, until we get the event for the pageflip, which is fine.
    */
    ಆಗ (windata->ಕಾಯುವಿಕೆ_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        ಆದರೆ (ret < 0) {
            ಆದರೆ (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                ಮುಂದುವರಿ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                ಹಿಂತಿರುಗಿ false;
            }
        }

        ಆದರೆ (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (pfd.revents & POLLIN) {
            /* There is data to read on the FD!
               Is the event a pageflip? We know it is a pageflip if it matches the
               event we are passing in &ev. If it does, drmHandleEvent() will unset
               windata->waiting_for_flip and we will get out of the "while" loop.
               If it's not, we keep iterating on the loop. */
            KMSDRM_drmHandleEvent(viddata->drm_fd, &ev);
        }

        /* If we got to this point in the loop, we may iterate or exit the loop:
           -A legit (non-error) event arrived, and it was a POLLING event, and it was consumed
            by drmHandleEvent().
              -If it was a PAGEFLIP event, waiting_for_flip will be unset by drmHandleEvent()
               and we will exit the loop.
              -If it wasn't a PAGEFLIP, drmHandleEvent() won't unset waiting_for_flip, so we
               iterare back to polling.
           -A legit (non-error) event arrived, but it's not a POLLIN event, so it hasn't to be
            consumed by drmHandleEvent(), so waiting_for_flip isn't set and we iterate back
            to polling. */
    }

    ಹಿಂತಿರುಗಿ true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
ಸ್ಥಿರ drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *KMSDRM_Get_Closest_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{

    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    drm_ಬಹುಲಕ_Connector *conn = dispdata->connector.connector;

    SDL_Display_ಬಹುಲಕ closest;
    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *drm_ಬಹುಲಕ;

    ಆದರೆ (SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(display->id, ಅಗಲ, ಎತ್ತರ, 0.0f, false, &closest)) {
        ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = closest.ಆಂತರಿಕ;
        drm_ಬಹುಲಕ = &conn->modes[modedata->ಬಹುಲಕ_ಸೂಚ್ಯಂಕ];
        ಹಿಂತಿರುಗಿ drm_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

ಸ್ಥಿರ bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;

    ಆದರೆ (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_ಗಣ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_ಗಣ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    ಆದರೆ (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_DisplayID *displays;
    SDL_Display_ದತ್ತಾಂಶ *dispdata;
    ಪೂರ್ಣಾಂಕ i;

    displays = SDL_GetDisplays(ಖಾಲಿ);
    ಆದರೆ (displays) {
        // Iterate on the SDL Display list.
        ಗಾಗಿ (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(displays[i]);

            // Free connector
            ಆದರೆ (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_ಬಹುಲಕ_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = ಖಾಲಿ;
            }

            // Free CRTC
            ಆದರೆ (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_ಬಹುಲಕ_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = ಖಾಲಿ;
            }
        }
        SDL_free(displays);
    }

    ಆದರೆ (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

ಸ್ಥಿರ bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool ಸಿಕ್ಕಿತು = false;
    uint64_t prop_ಮೌಲ್ಯ = 0;

    drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(drm_fd, output_id, DRM_ಬಹುಲಕ_OBJECT_CONNECTOR);
    ಆದರೆ (props) {
        ಗಾಗಿ (uint32_t i = 0; !ಸಿಕ್ಕಿತು && i < props->ಎಣಿಕೆ_props; ++i) {
            drm_ಬಹುಲಕ_Property_Ptr prop = KMSDRM_drm_ಬಹುಲಕ_Get_Property(drm_fd, props->props[i]);
            ಆದರೆ (prop) {
                ಆದರೆ (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_ಮೌಲ್ಯ = props->prop_ಮೌಲ್ಯಗಳು[i];
                    ಸಿಕ್ಕಿತು = true;
                }
                KMSDRM_drm_ಬಹುಲಕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ಬಹುಲಕ_Free_Object_Properties(props);
    }
    ಆದರೆ (ಸಿಕ್ಕಿತು) {
        ಹಿಂತಿರುಗಿ prop_ಮೌಲ್ಯ ? true : false;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool ಸಿಕ್ಕಿತು = false;
    drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ಬಹುಲಕ_OBJECT_CRTC);
    ಆದರೆ (props) {
        ಗಾಗಿ (uint32_t i = 0; !ಸಿಕ್ಕಿತು && i < props->ಎಣಿಕೆ_props; ++i) {
            drm_ಬಹುಲಕ_Property_Ptr prop = KMSDRM_drm_ಬಹುಲಕ_Get_Property(drm_fd, props->props[i]);
            ಆದರೆ (prop) {
                ಆದರೆ (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    ಸಿಕ್ಕಿತು = true;
                }
                KMSDRM_drm_ಬಹುಲಕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ಬಹುಲಕ_Free_Object_Properties(props);
    }
    ಹಿಂತಿರುಗಿ ಸಿಕ್ಕಿತು;
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_Crtc_ಗಣ_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    ಆದರೆ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ಹಿಂತಿರುಗಿ;
    }

    KMSDRM_drm_ಬಹುಲಕ_Object_ಗಣ_Property(drm_fd, crtc_id, DRM_ಬಹುಲಕ_OBJECT_CRTC, vrr_prop_id, enabled);
}

ಸ್ಥಿರ bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool ಸಿಕ್ಕಿತು = false;
    uint64_t prop_ಮೌಲ್ಯ = 0;

    ಆದರೆ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ಹಿಂತಿರುಗಿ false;
    }

    drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ಬಹುಲಕ_OBJECT_CRTC);
    ಆದರೆ (props) {
        ಗಾಗಿ (uint32_t i = 0; !ಸಿಕ್ಕಿತು && i < props->ಎಣಿಕೆ_props; ++i) {
            drm_ಬಹುಲಕ_Property_Ptr prop = KMSDRM_drm_ಬಹುಲಕ_Get_Property(drm_fd, props->props[i]);
            ಆದರೆ (prop) {
                ಆದರೆ (prop->prop_id == vrr_prop_id) {
                    prop_ಮೌಲ್ಯ = props->prop_ಮೌಲ್ಯಗಳು[i];
                    ಸಿಕ್ಕಿತು = true;
                }
                KMSDRM_drm_ಬಹುಲಕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ಬಹುಲಕ_Free_Object_Properties(props);
    }
    ಆದರೆ (ಸಿಕ್ಕಿತು) {
        ಹಿಂತಿರುಗಿ prop_ಮೌಲ್ಯ ? true : false;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool ಸಿಕ್ಕಿತು = false;
    ಪೂರ್ಣಾಂಕ orientation = 0;

    drm_ಬಹುಲಕ_Object_Properties_Ptr props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ಬಹುಲಕ_OBJECT_CONNECTOR);
    ಆದರೆ (props) {
        ಗಾಗಿ (uint32_t i = 0; !ಸಿಕ್ಕಿತು && i < props->ಎಣಿಕೆ_props; ++i) {
            drm_ಬಹುಲಕ_Property_Ptr prop = KMSDRM_drm_ಬಹುಲಕ_Get_Property(drm_fd, props->props[i]);
            ಆದರೆ (prop) {
                ಆದರೆ (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_ಬಹುಲಕ_PROP_ENUM)) {
                    ಆದರೆ (prop->ಎಣಿಕೆ_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        ಆದರೆ (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    ಸಿಕ್ಕಿತು = true;
                }
                KMSDRM_drm_ಬಹುಲಕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ಬಹುಲಕ_Free_Object_Properties(props);
    }
    ಹಿಂತಿರುಗಿ orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_ಕೂಡಿಸು_Display(SDL_VideoDevice *_this, drm_ಬಹುಲಕ_Connector *conn, drm_ಬಹುಲಕ_Res *resources)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = ಖಾಲಿ;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = ಖಾಲಿ;
    drm_ಬಹುಲಕ_Encoder *encoder = ಖಾಲಿ;
    drm_ಬಹುಲಕ_Crtc *crtc = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *connector_type = ಖಾಲಿ;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    ಅಕ್ಷರ name_fmt[64];
    ಪೂರ್ಣಾಂಕ orientation;
    ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_ಸೂಚ್ಯಂಕ;
    ಪೂರ್ಣಾಂಕ i, j;
    ಪೂರ್ಣಾಂಕ ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ));
    ಆದರೆ (!dispdata) {
        ret = -1;
        ಹೋಗು cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = ಖಾಲಿ;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_ಒಳ_fence_fd = -1;
    dispdata->kms_ಹೊರಹೋಗು_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_encoders; i++) {
        encoder = KMSDRM_drm_ಬಹುಲಕ_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        ಆದರೆ (!encoder) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (encoder->encoder_id == conn->encoder_id) {
            ನಿಲ್ಲಿಸು;
        }

        KMSDRM_drm_ಬಹುಲಕ_Free_Encoder(encoder);
        encoder = ಖಾಲಿ;
    }

    ಆದರೆ (!encoder) {
        // No encoder was connected, find the first supported one
        ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_encoders; i++) {
            encoder = KMSDRM_drm_ಬಹುಲಕ_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            ಆದರೆ (!encoder) {
                ಮುಂದುವರಿ;
            }

            ಗಾಗಿ (j = 0; j < conn->ಎಣಿಕೆ_encoders; j++) {
                ಆದರೆ (conn->encoders[j] == encoder->encoder_id) {
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ (j != conn->ಎಣಿಕೆ_encoders) {
                ನಿಲ್ಲಿಸು;
            }

            KMSDRM_drm_ಬಹುಲಕ_Free_Encoder(encoder);
            encoder = ಖಾಲಿ;
        }
    }

    ಆದರೆ (!encoder) {
        ret = SDL_ಗಣ_Error("No connected encoder found for connector.");
        ಹೋಗು cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_ಬಹುಲಕ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    ಆದರೆ (!crtc) {
        ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_crtcs; i++) {
            ಆದರೆ (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_ಬಹುಲಕ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (!crtc) {
        ret = SDL_ಗಣ_Error("No CRTC found for connector.");
        ಹೋಗು cleanup;
    }

    // Find the index of the mode attached to this CRTC
    ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = -1;

    ಗಾಗಿ (i = 0; i < conn->ಎಣಿಕೆ_modes; i++) {
        drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಬಹುಲಕ = &conn->modes[i];

        ಆದರೆ (!SDL_memcmp(ಬಹುಲಕ, &crtc->ಬಹುಲಕ, ಗಾತ್ರ(crtc->ಬಹುಲಕ))) {
            ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = i;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (ಬಹುಲಕ_ಸೂಚ್ಯಂಕ == -1) {
        ಪೂರ್ಣಾಂಕ current_area, ಅತಿದೊಡ್ಡ_area = 0;

        // Find the preferred mode or the highest resolution mode
        ಗಾಗಿ (i = 0; i < conn->ಎಣಿಕೆ_modes; i++) {
            drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಬಹುಲಕ = &conn->modes[i];

            ಆದರೆ (ಬಹುಲಕ->type & DRM_ಬಹುಲಕ_TYPE_PREFERRED) {
                ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = i;
                ನಿಲ್ಲಿಸು;
            }

            current_area = ಬಹುಲಕ->hdisplay * ಬಹುಲಕ->vdisplay;
            ಆದರೆ (current_area > ಅತಿದೊಡ್ಡ_area) {
                ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = i;
                ಅತಿದೊಡ್ಡ_area = current_area;
            }
        }
        ಆದರೆ (ಬಹುಲಕ_ಸೂಚ್ಯಂಕ != -1) {
            crtc->ಬಹುಲಕ = conn->modes[ಬಹುಲಕ_ಸೂಚ್ಯಂಕ];
        }
    }

    ಆದರೆ (ಬಹುಲಕ_ಸೂಚ್ಯಂಕ == -1) {
        ret = SDL_ಗಣ_Error("Failed to find index of mode attached to the CRTC.");
        ಹೋಗು cleanup;
    }

    /*********************************************/
    // Create an SDL Display for this connector.
    /*********************************************/

    /*********************************************/
    // Part 1: setup the SDL_Display internal.
    /*********************************************/

    /* Get the mode currently setup for this display,
       which is the mode currently setup on the CRTC
       we found for the active connector. */
    dispdata->ಬಹುಲಕ = crtc->ಬಹುಲಕ;
    dispdata->original_ಬಹುಲಕ = crtc->ಬಹುಲಕ;
    dispdata->fullscreen_ಬಹುಲಕ = crtc->ಬಹುಲಕ;

    ಆದರೆ (dispdata->ಬಹುಲಕ.hdisplay == 0 || dispdata->ಬಹುಲಕ.vdisplay == 0) {
        ret = SDL_ಗಣ_Error("Couldn't get a valid connector videomode.");
        ಹೋಗು cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    ಆದರೆ (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_ಗಣ_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    ಆದರೆ (KMSDRM_drm_ಬಹುಲಕ_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_ಬಹುಲಕ_Get_Connector_Type_Name(conn->connector_type);
        ಆದರೆ (connector_type == ಖಾಲಿ) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_ಬಹುಲಕ_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->ಎಣಿಕೆ_props, ಗಾತ್ರ(*dispdata->crtc.props_info));
    ಆದರೆ (!dispdata->crtc.props_info) {
        ret = false;
        ಹೋಗು cleanup;
    }

    ಗಾಗಿ (i = 0; i < dispdata->crtc.props->ಎಣಿಕೆ_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_ಬಹುಲಕ_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_ಬಹುಲಕ_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_ಬಹುಲಕ_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->ಎಣಿಕೆ_props, ಗಾತ್ರ(*dispdata->connector.props_info));
    ಆದರೆ (!dispdata->connector.props_info) {
        ret = false;
        ಹೋಗು cleanup;
    }

    ಗಾಗಿ (i = 0; i < dispdata->connector.props->ಎಣಿಕೆ_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_ಬಹುಲಕ_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));

    ಆದರೆ (!modedata) {
        ret = -1;
        ಹೋಗು cleanup;
    }

    modedata->ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = ಬಹುಲಕ_ಸೂಚ್ಯಂಕ;

    display.ಆಂತರಿಕ = dispdata;
    display.desktop_ಬಹುಲಕ.w = dispdata->ಬಹುಲಕ.hdisplay;
    display.desktop_ಬಹುಲಕ.h = dispdata->ಬಹುಲಕ.vdisplay;
    Calculate_Refresh_ದರ(&dispdata->ಬಹುಲಕ, &display.desktop_ಬಹುಲಕ.refresh_ದರ_numerator, &display.desktop_ಬಹುಲಕ.refresh_ದರ_denominator);
    display.desktop_ಬಹುಲಕ.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_ಬಹುಲಕ.ಆಂತರಿಕ = modedata;
    ಆದರೆ (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_ಕೂಡಿಸು_Video_Display(&display, false);
    ಆದರೆ (!display_id) {
        ret = -1;
        ಹೋಗು cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_ಸಂಖ್ಯೆ, orientation);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#ಆದರೆ_ಅಂತ್ಯ

cleanup:
    ಆದರೆ (encoder) {
        KMSDRM_drm_ಬಹುಲಕ_Free_Encoder(encoder);
    }
    ಆದರೆ (ret) {
        // Error (complete) cleanup
        ಆದರೆ (dispdata) {
            ಆದರೆ (dispdata->connector.connector) {
                KMSDRM_drm_ಬಹುಲಕ_Free_Connector(dispdata->connector.connector);
            }
            ಆದರೆ (dispdata->crtc.crtc) {
                KMSDRM_drm_ಬಹುಲಕ_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_ವಿಂಗಡಿಸು_Displays(SDL_VideoDevice *_this)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ಆದ್ಯತೆ);

    ಆದರೆ (name_hint) {
        ಅಕ್ಷರ *saveptr;
        ಅಕ್ಷರ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ಗಾತ್ರ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);

        ಆದರೆ (str && sorted_list) {
            ಪೂರ್ಣಾಂಕ sorted_ಸೂಚ್ಯಂಕ = 0;

            // Sort the requested displays to the front of the list.
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token = SDL_strtok_r(str, ",", &saveptr);
            ಆಗ (token) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ಆದರೆ (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = d;
                        _this->displays[i] = ಖಾಲಿ;
                        ನಿಲ್ಲಿಸು;
                    }
                }

                token = SDL_strtok_r(ಖಾಲಿ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                ಆದರೆ (_this->displays[i]) {
                    sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ಗಾತ್ರ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ಸ್ಥಿರ bool ಗಣ_client_atomic_caps(ಪೂರ್ಣಾಂಕ fd)
{
    ಆದರೆ (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        ಹಿಂತಿರುಗಿ false;  // emergency escape hatch.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (KMSDRM_drm_ಗಣ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        ಹಿಂತಿರುಗಿ false;  // no atomic modesetting support.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (KMSDRM_drm_ಗಣ_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_ಗಣ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        ಹಿಂತಿರುಗಿ false;  // no universal planes support.
    }
    ಹಿಂತಿರುಗಿ true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
ಸ್ಥಿರ bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    drm_ಬಹುಲಕ_Res *resources = ಖಾಲಿ;
    uint64_t async_pageflip = 0;
    ಪೂರ್ಣಾಂಕ i;
    bool ಫಲಿತಾಂಶ = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (ಶೂನ್ಯ)SDL_snprintf(viddata->devpath, ಗಾತ್ರ(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    ಆದರೆ (viddata->drm_fd < 0) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Could not open %s", viddata->devpath);
        ಹೋಗು cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = ಗಣ_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_ಬಹುಲಕ_Get_Resources(viddata->drm_fd);
    ಆದರೆ (!resources) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        ಹೋಗು cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    ಗಾಗಿ (i = 0; i < resources->ಎಣಿಕೆ_connectors; i++) {
        drm_ಬಹುಲಕ_Connector *conn = KMSDRM_drm_ಬಹುಲಕ_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        ಆದರೆ (!conn) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (conn->connection == DRM_ಬಹುಲಕ_CONNECTED && conn->ಎಣಿಕೆ_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_ಕೂಡಿಸು_Display(_this, conn, resources);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // If it's not, free it now.
            KMSDRM_drm_ಬಹುಲಕ_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    ಆದರೆ (SDL_GetPrimaryDisplay() == 0) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("No connected displays found.");
        ಹೋಗು cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_ವಿಂಗಡಿಸು_Displays(_this);

    // Determine if video hardware supports async pageflips.
    ಆದರೆ (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_ಪುಟ_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    ಆದರೆ (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    ಆದರೆ (resources) {
        KMSDRM_drm_ಬಹುಲಕ_Free_Resources(resources);
    }
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಆದರೆ (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
ಸ್ಥಿರ bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    bool ಫಲಿತಾಂಶ = true;

    // Reopen the FD if we weren't able to drop master on the original one
    ಆದರೆ (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        ಆದರೆ (viddata->drm_fd < 0) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = ಗಣ_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_ಗಣ_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    ಆದರೆ (!viddata->gbm_dev) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Couldn't create gbm device.");
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        ಫಲಿತಾಂಶ = ಸಿದ್ಧತೆ_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_ಗಣ_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_ದತ್ತಾಂಶ *dispdata)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    ಆದರೆ (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = ಖಾಲಿ;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    ಆದರೆ (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಪೂರ್ಣಾಂಕ ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    ಆದರೆ (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#ಆದರೆ 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        ಕೂಡಿಸು_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        ಕೂಡಿಸು_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_ಪುಟ_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_ಗಣ_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->ಬಫರ್_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_ಬಹುಲಕ);

        /* Issue atomic commit that is blocking and allows modesetting. */
        ಆದರೆ (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_ಗಣ_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        ಆದರೆ (ret && (dispdata->crtc->ಬಹುಲಕ_valid == 0)) {
            ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->ಬಫರ್_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_ಬಹುಲಕ);
        }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->ಬಫರ್_id;
        plane_info.src_w = dispdata->original_ಬಹುಲಕ.hdisplay;
        plane_info.src_h = dispdata->original_ಬಹುಲಕ.vdisplay;
        plane_info.crtc_w = dispdata->original_ಬಹುಲಕ.hdisplay;
        plane_info.crtc_h = dispdata->original_ಬಹುಲಕ.vdisplay;

        drm_atomic_ಗಣ_plane_props(dispdata, &plane_info);

        ಆದರೆ (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_ಗಣ_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->ಬಫರ್_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_ಬಹುಲಕ);

    // If we failed to set the original mode, try to set the connector preferred mode.
    ಆದರೆ (ret && (dispdata->crtc.crtc->ಬಹುಲಕ_valid == 0)) {
        ret = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->ಬಫರ್_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_ಬಹುಲಕ);
    }

    ಆದರೆ (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    ಆದರೆ (windata->bo) {
        ಆದರೆ (windata->bo != windata->ಮುಂದಿನ_bo) {
            KMSDRM_gbm_surface_release_ಬಫರ್(windata->gs, windata->bo);
        }
        windata->bo = ಖಾಲಿ;
    }

    ಆದರೆ (windata->ಮುಂದಿನ_bo) {
        KMSDRM_gbm_surface_release_ಬಫರ್(windata->gs, windata->ಮುಂದಿನ_bo);
        windata->ಮುಂದಿನ_bo = ಖಾಲಿ;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    ಆದರೆ (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    ಆದರೆ (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_Get_ಬಹುಲಕ_ಗಮ್ಯ_ಗಣ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಹೊರಹೋಗು_ಬಹುಲಕ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;

    ಆದರೆ (ಕಿಟಕಿ->fullscreen_exclusive) {
        *ಹೊರಹೋಗು_ಬಹುಲಕ = dispdata->fullscreen_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಬಹುಲಕ = KMSDRM_Get_Closest_Display_ಬಹುಲಕ(display, ಕಿಟಕಿ->windowed.w, ಕಿಟಕಿ->windowed.h);
        ಆದರೆ (ಬಹುಲಕ) {
            *ಹೊರಹೋಗು_ಬಹುಲಕ = *ಬಹುಲಕ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *ಹೊರಹೋಗು_ಬಹುಲಕ = dispdata->original_ಬಹುಲಕ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_DirtySurfaces(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info ಬಹುಲಕ;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_ಬಹುಲಕ_ಗಮ್ಯ_ಗಣ(ಕಿಟಕಿ, &ಬಹುಲಕ);
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಬಹುಲಕ.hdisplay, ಬಹುಲಕ.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ { uint32_t fmt; ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name; ಪೂರ್ಣಾಂಕ r; ಪೂರ್ಣಾಂಕ g; ಪೂರ್ಣಾಂಕ b; ಪೂರ್ಣಾಂಕ a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #ವ್ಯಾಖ್ಯಾನಿಸು FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
        FMT(ARGB8888, 8, 8, 8, 8),
        FMT(ABGR8888, 8, 8, 8, 8),
        FMT(BGRA8888, 8, 8, 8, 8),
        FMT(RGBA8888, 8, 8, 8, 8),
        FMT(BGRX8888, 8, 8, 8, 0),
        FMT(RGBX8888, 8, 8, 8, 0),
        FMT(XRGB8888, 8, 8, 8, 0),
        FMT(XBGR8888, 8, 8, 8, 0),
        FMT(RGBA1010102, 10, 10, 10, 2),
        FMT(BGRA1010102, 10, 10, 10, 2),
        FMT(ARGB2101010, 10, 10, 10, 2),
        FMT(ABGR2101010, 10, 10, 10, 2),
        FMT(XRGB2101010, 10, 10, 10, 0),
        FMT(XBGR2101010, 10, 10, 10, 0),
        FMT(RGBX1010102, 10, 10, 10, 0),
        FMT(BGRX1010102, 10, 10, 10, 0),
        FMT(ARGB1555, 5, 5, 5, 1),
        FMT(ABGR1555, 5, 5, 5, 1),
        FMT(RGBA5551, 5, 5, 5, 1),
        FMT(BGRA5551, 5, 5, 5, 1),
        FMT(XRGB1555, 5, 5, 5, 0),
        FMT(XBGR1555, 5, 5, 5, 0),
        FMT(RGBX5551, 5, 5, 5, 0),
        FMT(BGRX5551, 5, 5, 5, 0),
        FMT(RGB565, 5, 6, 5, 0),
        FMT(BGR565, 5, 6, 5, 0)
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು FMT
    };

    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    EGLContext egl_context;
    bool ಫಲಿತಾಂಶ = false;

    // If the current window already has surfaces, destroy them before creating other.
    ಆದರೆ (windata->gs) {
        KMSDRM_DestroySurfaces(_this, ಕಿಟಕಿ);
    }

    bool tried_setting_format = false;
    ಸ್ಥಿರಾಂಕ uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ಸ್ಥಿರಾಂಕ uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        ಆದರೆ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            ಮುಂದುವರಿ;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_ಬಹುಲಕ_ಗಮ್ಯ_ಗಣ(ಕಿಟಕಿ, &dispdata->ಬಹುಲಕ);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ಬಹುಲಕ.hdisplay, dispdata->ಬಹುಲಕ.vdisplay, surface_fmt, surface_flags);
        ಆದರೆ (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ಬಹುಲಕ.hdisplay, dispdata->ಬಹುಲಕ.vdisplay, surface_fmt, 0);
        }
        ಆದರೆ (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_ಗಣ_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            ಮುಂದುವರಿ;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_ಗಣ_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)windata->gs);
        ಆದರೆ (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = ಖಾಲಿ;
            ಮುಂದುವರಿ;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        ಫಲಿತಾಂಶ = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            ಮುಂದುವರಿ;
        }

        _this->gl_config.red_ಗಾತ್ರ = gbm_formats[i].r;
        _this->gl_config.green_ಗಾತ್ರ = gbm_formats[i].g;
        _this->gl_config.blue_ಗಾತ್ರ = gbm_formats[i].b;
        _this->gl_config.alpha_ಗಾತ್ರ = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        ಫಲಿತಾಂಶ = true;

        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, dispdata->ಬಹುಲಕ.hdisplay, dispdata->ಬಹುಲಕ.vdisplay);

        ನಿಲ್ಲಿಸು;
    }

    SDL_assert(ಫಲಿತಾಂಶ || (windata->gs == ಖಾಲಿ));

    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        ಆದರೆ (!tried_setting_format) {   // make sure there's an error string set.
            SDL_ಗಣ_Error("Could not find any supported GBM surface format.");
        }
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_ReleaseVT(ಶೂನ್ಯ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < viddata->ಅಂಕೆ_windows; i++) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = viddata->windows[i];
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, ಕಿಟಕಿ);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_AcquireVT(ಶೂನ್ಯ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ i;

    KMSDRM_drm_ಗಣ_Master(viddata->drm_fd);
    ಗಾಗಿ (i = 0; i < viddata->ಅಂಕೆ_windows; i++) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = viddata->windows[i];
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, ಕಿಟಕಿ);
        }
    }
}
#ಆದರೆ_ಅಂತ್ಯ // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool ಫಲಿತಾಂಶ = true;

    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    ಆದರೆ (!KMSDRM_InitDisplays(_this)) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("error getting KMSDRM displays information");
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_ಗಣ_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#ಅಥವಾಆದರೆ defined(SDL_ಒಳಹರಿವು_WSCONS)
    SDL_WSCONS_Init();
#ಆದರೆ_ಅಂತ್ಯ

    viddata->video_init = true;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
ಶೂನ್ಯ KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;

    KMSDRM_DeinitDisplays(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_ಗಣ_VTSwitch_Callbacks(ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);
    SDL_EVDEV_Quit();
#ಅಥವಾಆದರೆ defined(SDL_ಒಳಹರಿವು_WSCONS)
    SDL_WSCONS_Quit();
#ಆದರೆ_ಅಂತ್ಯ

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = ಖಾಲಿ;
    viddata->max_windows = 0;
    viddata->ಅಂಕೆ_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    drm_ಬಹುಲಕ_Connector *conn = dispdata->connector.connector;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < conn->ಎಣಿಕೆ_modes; i++) {
        SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));

        ಆದರೆ (modedata) {
            modedata->ಬಹುಲಕ_ಸೂಚ್ಯಂಕ = i;
        }

        SDL_zero(ಬಹುಲಕ);
        ಬಹುಲಕ.w = conn->modes[i].hdisplay;
        ಬಹುಲಕ.h = conn->modes[i].vdisplay;
        Calculate_Refresh_ದರ(&conn->modes[i], &ಬಹುಲಕ.refresh_ದರ_numerator, &ಬಹುಲಕ.refresh_ದರ_denominator);
        ಬಹುಲಕ.format = SDL_PIXELFORMAT_ARGB8888;
        ಬಹುಲಕ.ಆಂತರಿಕ = modedata;

        ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ)) {
            SDL_free(modedata);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool KMSDRM_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = ಬಹುಲಕ->ಆಂತರಿಕ;
    drm_ಬಹುಲಕ_Connector *conn = dispdata->connector.connector;
    ಪೂರ್ಣಾಂಕ i;

    // Don't do anything if we are in Vulkan mode.
    ಆದರೆ (viddata->vulkan_ಬಹುಲಕ) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!modedata) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_ಬಹುಲಕ = conn->modes[modedata->ಬಹುಲಕ_ಸೂಚ್ಯಂಕ];

    ಗಾಗಿ (i = 0; i < viddata->ಅಂಕೆ_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ KMSDRM_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_Video_ದತ್ತಾಂಶ *viddata;
    bool is_vulkan = ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN; // Is this a VK window?
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i, j;

    ಆದರೆ (!windata) {
        ಹಿಂತಿರುಗಿ;
    }

    // restore vrr state
    KMSDRM_Crtc_ಗಣ_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    ಆದರೆ (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, ಕಿಟಕಿ);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        ಆದರೆ (viddata->ಅಂಕೆ_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            ಆದರೆ (_this->egl_ದತ್ತಾಂಶ) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } ಇಲ್ಲದಿದ್ದರೆ {

        // If we were in Vulkan mode, get out of it.
        ಆದರೆ (viddata->vulkan_ಬಹುಲಕ) {
            viddata->vulkan_ಬಹುಲಕ = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    ಗಾಗಿ (i = 0; i < viddata->ಅಂಕೆ_windows; i++) {
        ಆದರೆ (viddata->windows[i] == ಕಿಟಕಿ) {
            viddata->ಅಂಕೆ_windows--;

            ಗಾಗಿ (j = i; j < viddata->ಅಂಕೆ_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            ನಿಲ್ಲಿಸು;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಖಾಲಿ;
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    bool is_vulkan = ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN; // Is this a VK window?
    bool vulkan_ಬಹುಲಕ = viddata->vulkan_ಬಹುಲಕ;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_ಬಹುಲಕ_ಬಹುಲಕ_Info *ಬಹುಲಕ;
    bool ಫಲಿತಾಂಶ = true;

    // Allocate window internal data
    windata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!windata) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    ಕಿಟಕಿ->ಆಂತರಿಕ = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_ಬಫರ್ = false;
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ಬಫರ್, false)) {
        windata->double_ಬಫರ್ = true;
    }

    ಆದರೆ (!is_vulkan && !vulkan_ಬಹುಲಕ) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_OPENGL;

        ಆದರೆ (!(viddata->gbm_init)) {

            /* After SDL_CreateWindow, most SDL programs will do SDL_CreateRenderer(),
               which will in turn call GL_CreateRenderer() or GLES2_CreateRenderer().
               In order for the GL_CreateRenderer() or GLES2_CreateRenderer() call to
               succeed without an unnecessary window re-creation, we must:
               -Mark the window as being OPENGL
               -Load the GL library (which can't be done until the GBM device has been
                created, so we have to do it here instead of doing it on VideoInit())
                and mark it as loaded by setting gl_config.driver_loaded to 1.
               So if you ever see KMSDRM_CreateWindow() to be called two times in tests,
               don't be shy to debug GL_CreateRenderer() or GLES2_CreateRenderer()
               to find out why!
             */

            /* Reopen FD, create gbm dev, setup display plane, etc,.
               but only when we come here for the first time,
               and only if it's not a VK window. */
            ಆದರೆ (!KMSDRM_GBMInit(_this, dispdata)) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
            egl_display = (NativeDisplayType)_this->ಆಂತರಿಕ->gbm_dev;
            ಆದರೆ (!SDL_EGL_ತುಂಬು_Library(_this, ಖಾಲಿ, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_ಆವೃತ್ತಿ = 2;
                _this->gl_config.minor_ಆವೃತ್ತಿ = 0;
                ಆದರೆ (!SDL_EGL_ತುಂಬು_Library(_this, ಖಾಲಿ, egl_display)) {
                    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Can't load EGL/GL library on window creation.");
                }
            }

            _this->gl_config.driver_loaded = 1;
        }

        /* Create the cursor BO for the display of this window,
           now that we know this is not a VK window. */
        KMSDRM_CreateCursorBO(display);

        /* Create and set the default cursor for the display
           of this window, now that we know this is not a VK window. */
        KMSDRM_InitMouse(_this, display);

        /* The FULLSCREEN flags are cut out from window->flags at this point,
           so we can't know if a window is fullscreen or not, hence all windows
           are considered "windowed" at this point of their life.
           If a window is fullscreen, SDL internals will call
           KMSDRM_SetWindowFullscreen() to reconfigure it if necessary. */
        ಬಹುಲಕ = KMSDRM_Get_Closest_Display_ಬಹುಲಕ(display, ಕಿಟಕಿ->windowed.w, ಕಿಟಕಿ->windowed.h);

        ಆದರೆ (ಬಹುಲಕ) {
            dispdata->fullscreen_ಬಹುಲಕ = *ಬಹುಲಕ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dispdata->fullscreen_ಬಹುಲಕ = dispdata->original_ಬಹುಲಕ;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        ಆದರೆ (!KMSDRM_CreateSurfaces(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    ಆದರೆ (viddata->ಅಂಕೆ_windows >= viddata->max_windows) {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ new_max_windows = viddata->max_windows + 1;
        SDL_ಕಿಟಕಿ **new_windows = (SDL_ಕಿಟಕಿ **)SDL_realloc(viddata->windows,
                                                              new_max_windows * ಗಾತ್ರ(SDL_ಕಿಟಕಿ *));
        ಆದರೆ (!new_windows) {
            ಹಿಂತಿರುಗಿ false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->ಅಂಕೆ_windows++] = ಕಿಟಕಿ;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_ಬಹುಲಕ = is_vulkan;

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_KMSDRM_DEVICE_ಸೂಚ್ಯಂಕ_ಸಂಖ್ಯೆ, viddata->devindex);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_KMSDRM_DRM_FD_ಸಂಖ್ಯೆ, viddata->drm_fd);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_KMSDRM_GBM_DEVICE_ಸೂಚಕ, viddata->gbm_dev);

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ), &display_bounds);
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ KMSDRM_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool KMSDRM_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}
ಶೂನ್ಯ KMSDRM_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    ಆದರೆ (!viddata->vulkan_ಬಹುಲಕ) {
        KMSDRM_DirtySurfaces(ಕಿಟಕಿ);
    }
}
SDL_Fullscreen_ಫಲಿತಾಂಶ KMSDRM_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    ಆದರೆ (!viddata->vulkan_ಬಹುಲಕ) {
        KMSDRM_DirtySurfaces(ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
}
ಶೂನ್ಯ KMSDRM_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ KMSDRM_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ KMSDRM_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ KMSDRM_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ KMSDRM_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ KMSDRM_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool KMSDRM_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable)
{
    ಹಿಂತಿರುಗಿ true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM
