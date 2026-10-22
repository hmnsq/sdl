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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_evdev.h"
#ਜਾਂਜੇ defined SDL_ਨਿਵੇਸ਼_WSCONS
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openbsd/SDL_wscons.h"
#ਜੇ_ਅੰਤ

// KMS/DRM declarations
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmdyn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmvulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <dirent.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <poll.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/stat.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/utsname.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OPENBSD
ਸਥਿਰ bool moderndri = false;
#ਨਹੀਂਤਾਂ
ਸਥਿਰ bool moderndri = true;
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਅੱਖਰ kmsdrm_dri_ਰਸਤਾ[16];
ਸਥਿਰ ਪੂਰਨ kmsdrm_dri_pathsize = 0;
ਸਥਿਰ ਅੱਖਰ kmsdrm_dri_devname[8];
ਸਥਿਰ ਪੂਰਨ kmsdrm_dri_devnamesize = 0;
ਸਥਿਰ ਅੱਖਰ kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_FORMAT_MOD_VENDOR_NONE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_FORMAT_MOD_VENDOR_NONE 0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DRM_FORMAT_MOD_ਰੇਖਿਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DRM_FORMAT_MOD_ਰੇਖਿਕ fourcc_mod_ਕੋਡ(NONE, 0)
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ get_driindex(ਖਾਲੀ)
{
    ਪੂਰਨ ਉਪਲਬਧ = -ENOENT;
    ਅੱਖਰ device[ਆਕਾਰ(kmsdrm_dri_cardpath)];
    ਪੂਰਨ drm_fd;
    ਪੂਰਨ i;
    ਪੂਰਨ devindex = -1;
    DIR *folder;
    ਅਚਲ ਅੱਖਰ *hint;
    ਬਣਤਰ dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_ਸੂਚਕਾਂਕ);
    ਜੇ (hint && *hint) {
        ਅੱਖਰ *endptr = ਨਿਰਾ;
        ਅਚਲ ਪੂਰਨ idx = (ਪੂਰਨ)SDL_strtol(hint, &endptr, 10);
        ਜੇ ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            ਵਾਪਸ idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_ਰਸਤਾ, ਆਕਾਰ(device));
    folder = opendir(device);
    ਜੇ (!folder) {
        SDL_ਸੈੱਟ_Error("Failed to open directory '%s'", device);
        ਵਾਪਸ -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                ਆਕਾਰ(device) - kmsdrm_dri_pathsize);
    ਜਦੋਂ((res = readdir(folder)) != ਨਿਰਾ && ਉਪਲਬਧ < 0) {
        ਜੇ (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        ਆਕਾਰ(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            ਜੇ (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                ਜੇ (SDL_KMSDRM_ਲੱਦੋ_Symbols()) {
                    drm_ਬਹੁਲਕ_Res *resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Resources(drm_fd);
                    ਜੇ (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->ਗਿਣਤੀ_connectors,
                                     resources->ਗਿਣਤੀ_encoders,
                                     resources->ਗਿਣਤੀ_crtcs);

                        ਜੇ (resources->ਗਿਣਤੀ_connectors > 0 &&
                            resources->ਗਿਣਤੀ_encoders > 0 &&
                            resources->ਗਿਣਤੀ_crtcs > 0) {
                            ਉਪਲਬਧ = -ENOENT;
                            ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_connectors && ਉਪਲਬਧ < 0; i++) {
                                drm_ਬਹੁਲਕ_Connector *conn =
                                    KMSDRM_drm_ਬਹੁਲਕ_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                ਜੇ (!conn) {
                                    ਜਾਰੀ;
                                }

                                ਜੇ (conn->connection == DRM_ਬਹੁਲਕ_CONNECTED &&
                                    conn->ਗਿਣਤੀ_modes) {
                                    bool access_denied = false;
                                    ਜੇ (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_ਸੈੱਟ_Master(drm_fd);
                                        ਜੇ (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    ਜੇ (!access_denied) {
                                        ਉਪਲਬਧ = devindex;
                                    }
                                }

                                KMSDRM_drm_ਬਹੁਲਕ_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_ਬਹੁਲਕ_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } ਨਹੀਂਤਾਂ {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    ਵਾਪਸ ਉਪਲਬਧ;
}

ਸਥਿਰ ਖਾਲੀ Calculate_Refresh_ਦਰ(drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਹੁਲਕ, ਪੂਰਨ *numerator, ਪੂਰਨ *denominator)
{
    *numerator = ਬਹੁਲਕ->clock * 1000;
    *denominator = ਬਹੁਲਕ->htotal * ਬਹੁਲਕ->vtotal;

    ਜੇ (ਬਹੁਲਕ->flags & DRM_ਬਹੁਲਕ_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    ਜੇ (ਬਹੁਲਕ->flags & DRM_ਬਹੁਲਕ_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    ਜੇ (ਬਹੁਲਕ->vscan > 1) {
        *denominator *= ਬਹੁਲਕ->vscan;
    }
}


ਪੂਰਨ ਜੋੜੋ_connector_property(drm_ਬਹੁਲਕ_Atomic_Req *req, KMSDRM_connector *conn, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
    ਪੂਰਨ prop_id = 0;

    ਲਈ (i = 0 ; i < conn->props->ਗਿਣਤੀ_props ; i++) {
        ਜੇ (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            ਰੋਕੋ;
        }
    }

    ਜੇ (prop_id < 0) {
        SDL_ਸੈੱਟ_Error("no connector property: %s", name);
        ਵਾਪਸ -EINVAL;
    }

    ਵਾਪਸ KMSDRM_drm_ਬਹੁਲਕ_Atomic_ਜੋੜੋ_Property(req, conn->connector->connector_id, prop_id, ਮੁੱਲ);
}

ਪੂਰਨ ਜੋੜੋ_crtc_property(drm_ਬਹੁਲਕ_Atomic_Req *req, KMSDRM_crtc *c, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
    ਪੂਰਨ prop_id = -1;

    ਲਈ (i = 0 ; i < c->props->ਗਿਣਤੀ_props ; i++) {
        ਜੇ (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            ਰੋਕੋ;
        }
    }

    ਜੇ (prop_id < 0) {
        SDL_ਸੈੱਟ_Error("no crtc property: %s", name);
        ਵਾਪਸ -EINVAL;
    }

    ਵਾਪਸ KMSDRM_drm_ਬਹੁਲਕ_Atomic_ਜੋੜੋ_Property(req, c->crtc->crtc_id, prop_id, ਮੁੱਲ);
}

ਪੂਰਨ ਜੋੜੋ_plane_property(drm_ਬਹੁਲਕ_Atomic_Req *req, KMSDRM_plane *p, ਅਚਲ ਅੱਖਰ *name, uint64_t ਮੁੱਲ)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
    ਪੂਰਨ prop_id = -1;

    ਲਈ (i = 0 ; i < p->props->ਗਿਣਤੀ_props ; i++) {
        ਜੇ (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            ਰੋਕੋ;
        }
    }

    ਜੇ (prop_id < 0) {
        SDL_ਸੈੱਟ_Error("no plane property: %s", name);
        ਵਾਪਸ -EINVAL;
    }

    ਵਾਪਸ KMSDRM_drm_ਬਹੁਲਕ_Atomic_ਜੋੜੋ_Property(req, p->plane->plane_id, prop_id, ਮੁੱਲ);
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_KMSDRM
ਸਥਿਰ ਖਾਲੀ print_plane_info(SDL_VideoDevice *_this, drm_ਬਹੁਲਕ_Plane_Ptr plane)
{
    SDL_Video_ਅੰਕੜੇ *viddata = ((SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ);
    drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_ਬਹੁਲਕ_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < props->ਗਿਣਤੀ_props; i++) {
        drm_ਬਹੁਲਕ_Property_Ptr p = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(viddata->drm_fd, props->props[i]);
        ਜੇ ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_ਮੁੱਲਾਂ[i];
        }

        KMSDRM_drm_ਬਹੁਲਕ_Free_Property(p);
    }

    ਅੱਖਰ *plane_type = "unknown";
    ਚੋਣ (type) {
        ਹਾਲਤ DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            ਰੋਕੋ;

        ਹਾਲਤ DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            ਰੋਕੋ;

        ਹਾਲਤ DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            ਰੋਕੋ;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_ਬਹੁਲਕ_Res *resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Resources(viddata->drm_fd);
    ਜੇ (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        ਲਈ (ਪੂਰਨ i = 0; i < resources->ਗਿਣਤੀ_crtcs; i++) {
            ਜੇ (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                ਰੋਕੋ;
            }
        }
        SDL_Log("%s\n\n", (ਅਚਲ ਅੱਖਰ *)SDL_Get_ਸੂਚਕ_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_ਸਮ੍ਰਿਤੀ_ਸੂਚਕ, ""));
        SDL_CloseIO(io);
    }
}

ਸਥਿਰ ਖਾਲੀ get_planes_info(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata)
{
    SDL_Video_ਅੰਕੜੇ *viddata = ((SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ);

    drm_ਬਹੁਲਕ_Plane_Res_Ptr plane_resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Plane_Resources(viddata->drm_fd);
    ਜੇ (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        ਵਾਪਸ;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->ਗਿਣਤੀ_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    ਲਈ (uint32_t i = 0; (i < plane_resources->ਗਿਣਤੀ_planes); i++) {
        ਅਚਲ uint32_t plane_id = plane_resources->planes[i];

        drm_ਬਹੁਲਕ_Plane_Ptr plane = KMSDRM_drm_ਬਹੁਲਕ_Get_Plane(viddata->drm_fd, plane_id);
        ਜੇ (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            ਜਾਰੀ;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_ਬਹੁਲਕ_Free_Plane(plane);
    }

    KMSDRM_drm_ਬਹੁਲਕ_Free_Plane_Resources(plane_resources);
}
#ਜੇ_ਅੰਤ

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
ਸਥਿਰ ਪੂਰਨ get_plane_id(SDL_VideoDevice *_this, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ crtc_id, uint32_t plane_type)
{
    drm_ਬਹੁਲਕ_Res *resources = ਨਿਰਾ;
    drm_ਬਹੁਲਕ_Plane_Res_Ptr plane_resources = ਨਿਰਾ;
    uint32_t i, j;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ crtc_ਸੂਚਕਾਂਕ = 0;
    ਪੂਰਨ ret = -EINVAL;
    ਪੂਰਨ ਮਿਲਿਆ = 0;

    SDL_Video_ਅੰਕੜੇ *viddata = ((SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ);

    resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_crtcs; i++) {
        ਜੇ (resources->crtcs[i] == crtc_id) {
            crtc_ਸੂਚਕਾਂਕ = i;
            ਰੋਕੋ;
        }
    }

    plane_resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Plane_Resources(viddata->drm_fd);
    ਜੇ (!plane_resources) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    ਲਈ (i = 0; (i < plane_resources->ਗਿਣਤੀ_planes) && !ਮਿਲਿਆ; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_ਬਹੁਲਕ_Plane_Ptr plane = KMSDRM_drm_ਬਹੁਲਕ_Get_Plane(viddata->drm_fd, plane_id);
        ਜੇ (!plane) {
            ਜਾਰੀ;
        }

        /* See if the current CRTC is available for this plane. */
        ਜੇ (plane->possible_crtcs & (1 << crtc_ਸੂਚਕਾਂਕ)) {

            drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_ਬਹੁਲਕ_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            ਲਈ (j = 0; j < props->ਗਿਣਤੀ_props; j++) {

                drm_ਬਹੁਲਕ_Property_Ptr p = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(viddata->drm_fd,
                    props->props[j]);

                ਜੇ ((SDL_strcmp(p->name, "type") == 0) && (props->prop_ਮੁੱਲਾਂ[j] == plane_type)) {
                    /* found our plane, use that: */
                    ਮਿਲਿਆ = 1;
                }

                KMSDRM_drm_ਬਹੁਲਕ_Free_Property(p);
            }

            KMSDRM_drm_ਬਹੁਲਕ_Free_Object_Properties(props);
        }

        KMSDRM_drm_ਬਹੁਲਕ_Free_Plane(plane);
    }

    KMSDRM_drm_ਬਹੁਲਕ_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_ਬਹੁਲਕ_Free_Resources(resources);

    ਵਾਪਸ ret;
}

/* Setup a plane and it's props. */
bool ਤਿਆਰੀ_plane(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_ਅੰਕੜੇ *viddata = ((SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ);
    bool ret = true;

    *_plane = SDL_calloc(1, ਆਕਾਰ(**_plane));
    ਜੇ (!(*_plane)) {
        ret = false;
        ਜਾਓ cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    ਜੇ (!plane_id) {
        ret = SDL_ਸੈੱਟ_Error("Invalid Plane ID");
        ਜਾਓ cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_ਬਹੁਲਕ_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    ਜੇ ((*_plane)->plane) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
        (*_plane)->props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_ਬਹੁਲਕ_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->ਗਿਣਤੀ_props, ਆਕਾਰ(*(*_plane)->props_info));

        ਜੇ ( !((*_plane)->props_info) ) {
            ret = false;
            ਜਾਓ cleanup;
        }

        ਲਈ (i = 0; i < (*_plane)->props->ਗਿਣਤੀ_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    ਜੇ (!ret) {
        ਜੇ (*_plane) {
            SDL_free(*_plane);
            *_plane = ਨਿਰਾ;
        }
    }
    ਵਾਪਸ ret;
}

/* Free a plane and it's props. */
ਖਾਲੀ free_plane(KMSDRM_plane **_plane)
{
    ਜੇ (*_plane) {
        ਜੇ ((*_plane)->plane) {
            KMSDRM_drm_ਬਹੁਲਕ_Free_Plane((*_plane)->plane);
            (*_plane)->plane = ਨਿਰਾ;
        }
        ਜੇ ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = ਨਿਰਾ;
        }
        SDL_free(*_plane);
        *_plane = ਨਿਰਾ;
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
ਖਾਲੀ
drm_atomic_ਸੈੱਟ_plane_props(SDL_Display_ਅੰਕੜੇ *dispdata, ਬਣਤਰ KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    ਜੇ (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_ਬਹੁਲਕ_Atomic_Alloc();
    }

    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    ਜੋੜੋ_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

ਪੂਰਨ drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_ਅੰਕੜੇ *viddata = ((SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ);
    uint32_t atomic_flags = 0;
    ਪੂਰਨ ret;

    ਜੇ (!blocking) {
        atomic_flags |= DRM_ਬਹੁਲਕ_ATOMIC_NONBLOCK;
    }

    ਜੇ (allow_modeset) {
        atomic_flags |= DRM_ਬਹੁਲਕ_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_ਬਹੁਲਕ_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, ਨਿਰਾ);

    ਜੇ (ret) {
        SDL_ਸੈੱਟ_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#ਜੇ 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#ਜੇ_ਅੰਤ
        ਜਾਓ ਬਾਹਰਲਾ;
    }

    ਜੇ (dispdata->kms_ਵਿੱਚ_fence_fd != -1) {
        close(dispdata->kms_ਵਿੱਚ_fence_fd);
        dispdata->kms_ਵਿੱਚ_fence_fd = -1;
    }

ਬਾਹਰਲਾ:
    KMSDRM_drm_ਬਹੁਲਕ_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = ਨਿਰਾ;

    ਵਾਪਸ ret;
}

ਖਾਲੀ
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    ਜੇ (dispdata->kms_fence) {
       EGLint ਸਥਿਤੀ;

        ਕਰੋ {
            ਸਥਿਤੀ = _this->egl_ਅੰਕੜੇ->eglClientWaitSyncKHR(_this->egl_ਅੰਕੜੇ->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } ਜਦੋਂ (ਸਥਿਤੀ != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_ਅੰਕੜੇ->eglDestroySyncKHR(_this->egl_ਅੰਕੜੇ->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = ਨਿਰਾ;
    }
}

ਸਥਿਰ bool KMSDRM_ਉਪਲਬਧ(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OPENBSD
    ਬਣਤਰ utsname nameofsystem;
    ਦੁੱਗਣਾ releaseversion;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ret = -ENOENT;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_OPENBSD
    ਜੇ (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        ਜੇ (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (moderndri) {
        SDL_strlcpy(kmsdrm_dri_ਰਸਤਾ, "/dev/dri/", ਆਕਾਰ(kmsdrm_dri_ਰਸਤਾ));
        SDL_strlcpy(kmsdrm_dri_devname, "card", ਆਕਾਰ(kmsdrm_dri_devname));
    } ਨਹੀਂਤਾਂ {
        SDL_strlcpy(kmsdrm_dri_ਰਸਤਾ, "/dev/", ਆਕਾਰ(kmsdrm_dri_ਰਸਤਾ));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", ਆਕਾਰ(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_ਰਸਤਾ);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (ਖਾਲੀ)SDL_snprintf(kmsdrm_dri_cardpath, ਆਕਾਰ(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_ਰਸਤਾ, kmsdrm_dri_devname);

    ret = get_driindex();
    ਜੇ (ret >= 0) {
        ਵਾਪਸ true;
    }

    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    ਜੇ (device->ਅੰਦਰੂਨੀ) {
        SDL_free(device->ਅੰਦਰੂਨੀ);
        device->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

ਸਥਿਰ SDL_VideoDevice *KMSDRM_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *viddata;
    ਪੂਰਨ devindex;

    ਜੇ (!KMSDRM_ਉਪਲਬਧ()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    devindex = get_driindex();
    ਜੇ (devindex < 0) {
        SDL_ਸੈੱਟ_Error("devindex (%d) must not be negative.", devindex);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!SDL_KMSDRM_ਲੱਦੋ_Symbols()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    viddata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!viddata) {
        ਜਾਓ cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->ਅੰਦਰੂਨੀ = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = KMSDRM_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->CreateSDLWindow = KMSDRM_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->Show_ਖਿੜਕੀ = KMSDRM_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = KMSDRM_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = KMSDRM_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = KMSDRM_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = KMSDRM_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = KMSDRM_Restore_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = KMSDRM_Destroy_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Focusable = KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Focusable;

    device->GL_ਲੱਦੋ_Library = KMSDRM_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = KMSDRM_GLES_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = KMSDRM_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = KMSDRM_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = KMSDRM_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_ਸੈੱਟ_Default_Profile_Config = KMSDRM_GLES_ਸੈੱਟ_Default_Profile_Config;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = KMSDRM_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#ਜੇ_ਅੰਤ

    device->PumpEvents = KMSDRM_PumpEvents;
    device->ਮੁਕਤ = KMSDRM_DeleteDevice;

    ਵਾਪਸ device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    ਵਾਪਸ ਨਿਰਾ;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

ਸਥਿਰ ਖਾਲੀ KMSDRM_FBDestroyCallback(ਬਣਤਰ gbm_bo *bo, ਖਾਲੀ *ਅੰਕੜੇ)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)ਅੰਕੜੇ;

    ਜੇ (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_ਬਹੁਲਕ_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ਬਣਤਰ gbm_bo *bo)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ w, h;
    ਪੂਰਨ rc = -1;
    ਪੂਰਨ ਅੰਕ_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_ਅੰਕੜੇ(bo);

    ਜੇ (fb_info) {
        ਵਾਪਸ fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, ਆਕਾਰ(KMSDRM_FBInfo));

    ਜੇ (!fb_info) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_ਚੌੜਾਈ(bo);
    h = KMSDRM_gbm_bo_get_ਉਚਾਈ(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    ਜੇ (KMSDRM_drm_ਬਹੁਲਕ_ਜੋੜੋ_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_ਗਿਣਤੀ &&
        KMSDRM_gbm_bo_get_ਵਿੱਥ &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        ਅੰਕ_planes = KMSDRM_gbm_bo_get_plane_ਗਿਣਤੀ(bo);
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_ਵਿੱਥ(bo, i);
            modifiers[i] = modifiers[0];
        }

        ਜੇ (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_ਬਹੁਲਕ_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_ਬਹੁਲਕ_ਜੋੜੋ_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    ਜੇ (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_ਬਹੁਲਕ_ਜੋੜੋ_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    ਜੇ (rc < 0) {
        SDL_free(fb_info);
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (ਖਾਲੀ *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_ਸੈੱਟ_user_ਅੰਕੜੇ(bo, fb_info, KMSDRM_FBDestroyCallback);

    ਵਾਪਸ fb_info;
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_FlipHandler(ਪੂਰਨ fd, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਚੌਖਟਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sec, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ usec, ਖਾਲੀ *ਅੰਕੜੇ)
{
    *((bool *)ਅੰਕੜੇ) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata)
{

    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    drmEventContext ev = { 0 };
    ਬਣਤਰ pollfd pfd = { 0 };
    ਪੂਰਨ ret;

    ev.ਸੰਸਕਰਣ = DRM_EVENT_CONTEXT_ਸੰਸਕਰਣ;
    ev.ਪੰਨਾ_flip_handler = KMSDRM_FlipHandler;

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
    ਜਦੋਂ (windata->ਉਡੀਕ_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        ਜੇ (ret < 0) {
            ਜੇ (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                ਜਾਰੀ;
            } ਨਹੀਂਤਾਂ {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                ਵਾਪਸ false;
            }
        }

        ਜੇ (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            ਵਾਪਸ false;
        }

        ਜੇ (pfd.revents & POLLIN) {
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

    ਵਾਪਸ true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
ਸਥਿਰ drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *KMSDRM_Get_Closest_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{

    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    drm_ਬਹੁਲਕ_Connector *conn = dispdata->connector.connector;

    SDL_Display_ਬਹੁਲਕ closest;
    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *drm_ਬਹੁਲਕ;

    ਜੇ (SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(display->id, ਚੌੜਾਈ, ਉਚਾਈ, 0.0f, false, &closest)) {
        ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = closest.ਅੰਦਰੂਨੀ;
        drm_ਬਹੁਲਕ = &conn->modes[modedata->ਬਹੁਲਕ_ਸੂਚਕਾਂਕ];
        ਵਾਪਸ drm_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ ਨਿਰਾ;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

ਸਥਿਰ bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_ਸੈੱਟ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_ਸੈੱਟ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    ਜੇ (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        ਵਾਪਸ true;
    }

    ਵਾਪਸ KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
ਸਥਿਰ ਖਾਲੀ KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_DisplayID *displays;
    SDL_Display_ਅੰਕੜੇ *dispdata;
    ਪੂਰਨ i;

    displays = SDL_GetDisplays(ਨਿਰਾ);
    ਜੇ (displays) {
        // Iterate on the SDL Display list.
        ਲਈ (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_ਅੰਕੜੇ(displays[i]);

            // Free connector
            ਜੇ (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_ਬਹੁਲਕ_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = ਨਿਰਾ;
            }

            // Free CRTC
            ਜੇ (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_ਬਹੁਲਕ_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = ਨਿਰਾ;
            }
        }
        SDL_free(displays);
    }

    ਜੇ (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

ਸਥਿਰ bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool ਮਿਲਿਆ = false;
    uint64_t prop_ਮੁੱਲ = 0;

    drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(drm_fd, output_id, DRM_ਬਹੁਲਕ_OBJECT_CONNECTOR);
    ਜੇ (props) {
        ਲਈ (uint32_t i = 0; !ਮਿਲਿਆ && i < props->ਗਿਣਤੀ_props; ++i) {
            drm_ਬਹੁਲਕ_Property_Ptr prop = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(drm_fd, props->props[i]);
            ਜੇ (prop) {
                ਜੇ (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_ਮੁੱਲ = props->prop_ਮੁੱਲਾਂ[i];
                    ਮਿਲਿਆ = true;
                }
                KMSDRM_drm_ਬਹੁਲਕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ਬਹੁਲਕ_Free_Object_Properties(props);
    }
    ਜੇ (ਮਿਲਿਆ) {
        ਵਾਪਸ prop_ਮੁੱਲ ? true : false;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool ਮਿਲਿਆ = false;
    drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ਬਹੁਲਕ_OBJECT_CRTC);
    ਜੇ (props) {
        ਲਈ (uint32_t i = 0; !ਮਿਲਿਆ && i < props->ਗਿਣਤੀ_props; ++i) {
            drm_ਬਹੁਲਕ_Property_Ptr prop = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(drm_fd, props->props[i]);
            ਜੇ (prop) {
                ਜੇ (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    ਮਿਲਿਆ = true;
                }
                KMSDRM_drm_ਬਹੁਲਕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ਬਹੁਲਕ_Free_Object_Properties(props);
    }
    ਵਾਪਸ ਮਿਲਿਆ;
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_Crtc_ਸੈੱਟ_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    ਜੇ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ਵਾਪਸ;
    }

    KMSDRM_drm_ਬਹੁਲਕ_Object_ਸੈੱਟ_Property(drm_fd, crtc_id, DRM_ਬਹੁਲਕ_OBJECT_CRTC, vrr_prop_id, enabled);
}

ਸਥਿਰ bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool ਮਿਲਿਆ = false;
    uint64_t prop_ਮੁੱਲ = 0;

    ਜੇ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ਵਾਪਸ false;
    }

    drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ਬਹੁਲਕ_OBJECT_CRTC);
    ਜੇ (props) {
        ਲਈ (uint32_t i = 0; !ਮਿਲਿਆ && i < props->ਗਿਣਤੀ_props; ++i) {
            drm_ਬਹੁਲਕ_Property_Ptr prop = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(drm_fd, props->props[i]);
            ਜੇ (prop) {
                ਜੇ (prop->prop_id == vrr_prop_id) {
                    prop_ਮੁੱਲ = props->prop_ਮੁੱਲਾਂ[i];
                    ਮਿਲਿਆ = true;
                }
                KMSDRM_drm_ਬਹੁਲਕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ਬਹੁਲਕ_Free_Object_Properties(props);
    }
    ਜੇ (ਮਿਲਿਆ) {
        ਵਾਪਸ prop_ਮੁੱਲ ? true : false;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਪੂਰਨ KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool ਮਿਲਿਆ = false;
    ਪੂਰਨ orientation = 0;

    drm_ਬਹੁਲਕ_Object_Properties_Ptr props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(drm_fd, crtc_id, DRM_ਬਹੁਲਕ_OBJECT_CONNECTOR);
    ਜੇ (props) {
        ਲਈ (uint32_t i = 0; !ਮਿਲਿਆ && i < props->ਗਿਣਤੀ_props; ++i) {
            drm_ਬਹੁਲਕ_Property_Ptr prop = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(drm_fd, props->props[i]);
            ਜੇ (prop) {
                ਜੇ (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_ਬਹੁਲਕ_PROP_ENUM)) {
                    ਜੇ (prop->ਗਿਣਤੀ_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        ਜੇ (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    ਮਿਲਿਆ = true;
                }
                KMSDRM_drm_ਬਹੁਲਕ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ਬਹੁਲਕ_Free_Object_Properties(props);
    }
    ਵਾਪਸ orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
ਸਥਿਰ ਖਾਲੀ KMSDRM_ਜੋੜੋ_Display(SDL_VideoDevice *_this, drm_ਬਹੁਲਕ_Connector *conn, drm_ਬਹੁਲਕ_Res *resources)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *dispdata = ਨਿਰਾ;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = ਨਿਰਾ;
    drm_ਬਹੁਲਕ_Encoder *encoder = ਨਿਰਾ;
    drm_ਬਹੁਲਕ_Crtc *crtc = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *connector_type = ਨਿਰਾ;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    ਅੱਖਰ name_fmt[64];
    ਪੂਰਨ orientation;
    ਪੂਰਨ ਬਹੁਲਕ_ਸੂਚਕਾਂਕ;
    ਪੂਰਨ i, j;
    ਪੂਰਨ ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ));
    ਜੇ (!dispdata) {
        ret = -1;
        ਜਾਓ cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = ਨਿਰਾ;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_ਵਿੱਚ_fence_fd = -1;
    dispdata->kms_ਬਾਹਰਲਾ_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_encoders; i++) {
        encoder = KMSDRM_drm_ਬਹੁਲਕ_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        ਜੇ (!encoder) {
            ਜਾਰੀ;
        }

        ਜੇ (encoder->encoder_id == conn->encoder_id) {
            ਰੋਕੋ;
        }

        KMSDRM_drm_ਬਹੁਲਕ_Free_Encoder(encoder);
        encoder = ਨਿਰਾ;
    }

    ਜੇ (!encoder) {
        // No encoder was connected, find the first supported one
        ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_encoders; i++) {
            encoder = KMSDRM_drm_ਬਹੁਲਕ_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            ਜੇ (!encoder) {
                ਜਾਰੀ;
            }

            ਲਈ (j = 0; j < conn->ਗਿਣਤੀ_encoders; j++) {
                ਜੇ (conn->encoders[j] == encoder->encoder_id) {
                    ਰੋਕੋ;
                }
            }

            ਜੇ (j != conn->ਗਿਣਤੀ_encoders) {
                ਰੋਕੋ;
            }

            KMSDRM_drm_ਬਹੁਲਕ_Free_Encoder(encoder);
            encoder = ਨਿਰਾ;
        }
    }

    ਜੇ (!encoder) {
        ret = SDL_ਸੈੱਟ_Error("No connected encoder found for connector.");
        ਜਾਓ cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_ਬਹੁਲਕ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    ਜੇ (!crtc) {
        ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_crtcs; i++) {
            ਜੇ (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_ਬਹੁਲਕ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (!crtc) {
        ret = SDL_ਸੈੱਟ_Error("No CRTC found for connector.");
        ਜਾਓ cleanup;
    }

    // Find the index of the mode attached to this CRTC
    ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = -1;

    ਲਈ (i = 0; i < conn->ਗਿਣਤੀ_modes; i++) {
        drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਹੁਲਕ = &conn->modes[i];

        ਜੇ (!SDL_memcmp(ਬਹੁਲਕ, &crtc->ਬਹੁਲਕ, ਆਕਾਰ(crtc->ਬਹੁਲਕ))) {
            ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = i;
            ਰੋਕੋ;
        }
    }

    ਜੇ (ਬਹੁਲਕ_ਸੂਚਕਾਂਕ == -1) {
        ਪੂਰਨ current_area, ਸਭ_ਤੋਂ_ਵੱਡਾ_area = 0;

        // Find the preferred mode or the highest resolution mode
        ਲਈ (i = 0; i < conn->ਗਿਣਤੀ_modes; i++) {
            drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਹੁਲਕ = &conn->modes[i];

            ਜੇ (ਬਹੁਲਕ->type & DRM_ਬਹੁਲਕ_TYPE_PREFERRED) {
                ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = i;
                ਰੋਕੋ;
            }

            current_area = ਬਹੁਲਕ->hdisplay * ਬਹੁਲਕ->vdisplay;
            ਜੇ (current_area > ਸਭ_ਤੋਂ_ਵੱਡਾ_area) {
                ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = i;
                ਸਭ_ਤੋਂ_ਵੱਡਾ_area = current_area;
            }
        }
        ਜੇ (ਬਹੁਲਕ_ਸੂਚਕਾਂਕ != -1) {
            crtc->ਬਹੁਲਕ = conn->modes[ਬਹੁਲਕ_ਸੂਚਕਾਂਕ];
        }
    }

    ਜੇ (ਬਹੁਲਕ_ਸੂਚਕਾਂਕ == -1) {
        ret = SDL_ਸੈੱਟ_Error("Failed to find index of mode attached to the CRTC.");
        ਜਾਓ cleanup;
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
    dispdata->ਬਹੁਲਕ = crtc->ਬਹੁਲਕ;
    dispdata->original_ਬਹੁਲਕ = crtc->ਬਹੁਲਕ;
    dispdata->fullscreen_ਬਹੁਲਕ = crtc->ਬਹੁਲਕ;

    ਜੇ (dispdata->ਬਹੁਲਕ.hdisplay == 0 || dispdata->ਬਹੁਲਕ.vdisplay == 0) {
        ret = SDL_ਸੈੱਟ_Error("Couldn't get a valid connector videomode.");
        ਜਾਓ cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    ਜੇ (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_ਸੈੱਟ_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    ਜੇ (KMSDRM_drm_ਬਹੁਲਕ_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_ਬਹੁਲਕ_Get_Connector_Type_Name(conn->connector_type);
        ਜੇ (connector_type == ਨਿਰਾ) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_ਬਹੁਲਕ_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->ਗਿਣਤੀ_props, ਆਕਾਰ(*dispdata->crtc.props_info));
    ਜੇ (!dispdata->crtc.props_info) {
        ret = false;
        ਜਾਓ cleanup;
    }

    ਲਈ (i = 0; i < dispdata->crtc.props->ਗਿਣਤੀ_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_ਬਹੁਲਕ_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_ਬਹੁਲਕ_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->ਗਿਣਤੀ_props, ਆਕਾਰ(*dispdata->connector.props_info));
    ਜੇ (!dispdata->connector.props_info) {
        ret = false;
        ਜਾਓ cleanup;
    }

    ਲਈ (i = 0; i < dispdata->connector.props->ਗਿਣਤੀ_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_ਬਹੁਲਕ_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));

    ਜੇ (!modedata) {
        ret = -1;
        ਜਾਓ cleanup;
    }

    modedata->ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = ਬਹੁਲਕ_ਸੂਚਕਾਂਕ;

    display.ਅੰਦਰੂਨੀ = dispdata;
    display.desktop_ਬਹੁਲਕ.w = dispdata->ਬਹੁਲਕ.hdisplay;
    display.desktop_ਬਹੁਲਕ.h = dispdata->ਬਹੁਲਕ.vdisplay;
    Calculate_Refresh_ਦਰ(&dispdata->ਬਹੁਲਕ, &display.desktop_ਬਹੁਲਕ.refresh_ਦਰ_numerator, &display.desktop_ਬਹੁਲਕ.refresh_ਦਰ_denominator);
    display.desktop_ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;
    ਜੇ (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_ਜੋੜੋ_Video_Display(&display, false);
    ਜੇ (!display_id) {
        ret = -1;
        ਜਾਓ cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_ਸੰਖਿਆ, orientation);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#ਜੇ_ਅੰਤ

cleanup:
    ਜੇ (encoder) {
        KMSDRM_drm_ਬਹੁਲਕ_Free_Encoder(encoder);
    }
    ਜੇ (ret) {
        // Error (complete) cleanup
        ਜੇ (dispdata) {
            ਜੇ (dispdata->connector.connector) {
                KMSDRM_drm_ਬਹੁਲਕ_Free_Connector(dispdata->connector.connector);
            }
            ਜੇ (dispdata->crtc.crtc) {
                KMSDRM_drm_ਬਹੁਲਕ_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

ਸਥਿਰ ਖਾਲੀ KMSDRM_ਛਾਂਟੋ_Displays(SDL_VideoDevice *_this)
{
    ਅਚਲ ਅੱਖਰ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ਤਰਜੀਹ);

    ਜੇ (name_hint) {
        ਅੱਖਰ *saveptr;
        ਅੱਖਰ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ਆਕਾਰ(SDL_VideoDisplay *) * _this->ਅੰਕ_displays);

        ਜੇ (str && sorted_list) {
            ਪੂਰਨ sorted_ਸੂਚਕਾਂਕ = 0;

            // Sort the requested displays to the front of the list.
            ਅਚਲ ਅੱਖਰ *token = SDL_strtok_r(str, ",", &saveptr);
            ਜਦੋਂ (token) {
                ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ਜੇ (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_ਸੂਚਕਾਂਕ++] = d;
                        _this->displays[i] = ਨਿਰਾ;
                        ਰੋਕੋ;
                    }
                }

                token = SDL_strtok_r(ਨਿਰਾ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
                ਜੇ (_this->displays[i]) {
                    sorted_list[sorted_ਸੂਚਕਾਂਕ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ਆਕਾਰ(SDL_VideoDisplay *) * _this->ਅੰਕ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ਸਥਿਰ bool ਸੈੱਟ_client_atomic_caps(ਪੂਰਨ fd)
{
    ਜੇ (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        ਵਾਪਸ false;  // emergency escape hatch.
    } ਨਹੀਂਤਾਂ ਜੇ (KMSDRM_drm_ਸੈੱਟ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        ਵਾਪਸ false;  // no atomic modesetting support.
    } ਨਹੀਂਤਾਂ ਜੇ (KMSDRM_drm_ਸੈੱਟ_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_ਸੈੱਟ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        ਵਾਪਸ false;  // no universal planes support.
    }
    ਵਾਪਸ true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
ਸਥਿਰ bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    drm_ਬਹੁਲਕ_Res *resources = ਨਿਰਾ;
    uint64_t async_pageflip = 0;
    ਪੂਰਨ i;
    bool ਨਤੀਜਾ = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (ਖਾਲੀ)SDL_snprintf(viddata->devpath, ਆਕਾਰ(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    ਜੇ (viddata->drm_fd < 0) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Could not open %s", viddata->devpath);
        ਜਾਓ cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = ਸੈੱਟ_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_ਬਹੁਲਕ_Get_Resources(viddata->drm_fd);
    ਜੇ (!resources) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        ਜਾਓ cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    ਲਈ (i = 0; i < resources->ਗਿਣਤੀ_connectors; i++) {
        drm_ਬਹੁਲਕ_Connector *conn = KMSDRM_drm_ਬਹੁਲਕ_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        ਜੇ (!conn) {
            ਜਾਰੀ;
        }

        ਜੇ (conn->connection == DRM_ਬਹੁਲਕ_CONNECTED && conn->ਗਿਣਤੀ_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_ਜੋੜੋ_Display(_this, conn, resources);
        } ਨਹੀਂਤਾਂ {
            // If it's not, free it now.
            KMSDRM_drm_ਬਹੁਲਕ_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    ਜੇ (SDL_GetPrimaryDisplay() == 0) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("No connected displays found.");
        ਜਾਓ cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_ਛਾਂਟੋ_Displays(_this);

    // Determine if video hardware supports async pageflips.
    ਜੇ (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_ਪੰਨਾ_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    ਜੇ (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    ਜੇ (resources) {
        KMSDRM_drm_ਬਹੁਲਕ_Free_Resources(resources);
    }
    ਜੇ (!ਨਤੀਜਾ) {
        ਜੇ (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
ਸਥਿਰ bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    bool ਨਤੀਜਾ = true;

    // Reopen the FD if we weren't able to drop master on the original one
    ਜੇ (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        ਜੇ (viddata->drm_fd < 0) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = ਸੈੱਟ_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_ਸੈੱਟ_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    ਜੇ (!viddata->gbm_dev) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Couldn't create gbm device.");
    } ਨਹੀਂਤਾਂ {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        ਨਤੀਜਾ = ਤਿਆਰੀ_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_ਸੈੱਟ_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    ਵਾਪਸ ਨਤੀਜਾ;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
ਸਥਿਰ ਖਾਲੀ KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_ਅੰਕੜੇ *dispdata)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    ਜੇ (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = ਨਿਰਾ;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    ਜੇ (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *dispdata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਪੂਰਨ ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    ਜੇ (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#ਜੇ 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        ਜੋੜੋ_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        ਜੋੜੋ_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        ਜੋੜੋ_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_ਪੰਨਾ_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_ਸੈੱਟ_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->ਬਫਰ_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_ਬਹੁਲਕ);

        /* Issue atomic commit that is blocking and allows modesetting. */
        ਜੇ (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_ਸੈੱਟ_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        ਜੇ (ret && (dispdata->crtc->ਬਹੁਲਕ_valid == 0)) {
            ret = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->ਬਫਰ_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_ਬਹੁਲਕ);
        }
#ਜੇ_ਅੰਤ

#ਜੇ 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->ਬਫਰ_id;
        plane_info.src_w = dispdata->original_ਬਹੁਲਕ.hdisplay;
        plane_info.src_h = dispdata->original_ਬਹੁਲਕ.vdisplay;
        plane_info.crtc_w = dispdata->original_ਬਹੁਲਕ.hdisplay;
        plane_info.crtc_h = dispdata->original_ਬਹੁਲਕ.vdisplay;

        drm_atomic_ਸੈੱਟ_plane_props(dispdata, &plane_info);

        ਜੇ (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_ਸੈੱਟ_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#ਜੇ_ਅੰਤ

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->ਬਫਰ_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_ਬਹੁਲਕ);

    // If we failed to set the original mode, try to set the connector preferred mode.
    ਜੇ (ret && (dispdata->crtc.crtc->ਬਹੁਲਕ_valid == 0)) {
        ret = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->ਬਫਰ_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_ਬਹੁਲਕ);
    }

    ਜੇ (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    ਜੇ (windata->bo) {
        ਜੇ (windata->bo != windata->ਅਗਲਾ_bo) {
            KMSDRM_gbm_surface_release_ਬਫਰ(windata->gs, windata->bo);
        }
        windata->bo = ਨਿਰਾ;
    }

    ਜੇ (windata->ਅਗਲਾ_bo) {
        KMSDRM_gbm_surface_release_ਬਫਰ(windata->gs, windata->ਅਗਲਾ_bo);
        windata->ਅਗਲਾ_bo = ਨਿਰਾ;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    ਜੇ (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    ਜੇ (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_Get_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਸੈੱਟ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਾਹਰਲਾ_ਬਹੁਲਕ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;

    ਜੇ (ਖਿੜਕੀ->fullscreen_exclusive) {
        *ਬਾਹਰਲਾ_ਬਹੁਲਕ = dispdata->fullscreen_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {
        drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਹੁਲਕ = KMSDRM_Get_Closest_Display_ਬਹੁਲਕ(display, ਖਿੜਕੀ->windowed.w, ਖਿੜਕੀ->windowed.h);
        ਜੇ (ਬਹੁਲਕ) {
            *ਬਾਹਰਲਾ_ਬਹੁਲਕ = *ਬਹੁਲਕ;
        } ਨਹੀਂਤਾਂ {
            *ਬਾਹਰਲਾ_ਬਹੁਲਕ = dispdata->original_ਬਹੁਲਕ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_DirtySurfaces(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info ਬਹੁਲਕ;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਸੈੱਟ(ਖਿੜਕੀ, &ਬਹੁਲਕ);
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਬਹੁਲਕ.hdisplay, ਬਹੁਲਕ.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਸਥਿਰ ਅਚਲ ਬਣਤਰ { uint32_t fmt; ਅਚਲ ਅੱਖਰ *name; ਪੂਰਨ r; ਪੂਰਨ g; ਪੂਰਨ b; ਪੂਰਨ a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ FMT
    };

    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    EGLContext egl_context;
    bool ਨਤੀਜਾ = false;

    // If the current window already has surfaces, destroy them before creating other.
    ਜੇ (windata->gs) {
        KMSDRM_DestroySurfaces(_this, ਖਿੜਕੀ);
    }

    bool tried_setting_format = false;
    ਅਚਲ uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ਅਚਲ uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        ਜੇ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            ਜਾਰੀ;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_ਸੈੱਟ(ਖਿੜਕੀ, &dispdata->ਬਹੁਲਕ);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ਬਹੁਲਕ.hdisplay, dispdata->ਬਹੁਲਕ.vdisplay, surface_fmt, surface_flags);
        ਜੇ (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ਬਹੁਲਕ.hdisplay, dispdata->ਬਹੁਲਕ.vdisplay, surface_fmt, 0);
        }
        ਜੇ (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_ਸੈੱਟ_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            ਜਾਰੀ;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_ਸੈੱਟ_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)windata->gs);
        ਜੇ (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = ਨਿਰਾ;
            ਜਾਰੀ;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        ਨਤੀਜਾ = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        ਜੇ (!ਨਤੀਜਾ) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            ਜਾਰੀ;
        }

        _this->gl_config.red_ਮਾਪ = gbm_formats[i].r;
        _this->gl_config.green_ਮਾਪ = gbm_formats[i].g;
        _this->gl_config.blue_ਮਾਪ = gbm_formats[i].b;
        _this->gl_config.alpha_ਮਾਪ = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        ਨਤੀਜਾ = true;

        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, dispdata->ਬਹੁਲਕ.hdisplay, dispdata->ਬਹੁਲਕ.vdisplay);

        ਰੋਕੋ;
    }

    SDL_assert(ਨਤੀਜਾ || (windata->gs == ਨਿਰਾ));

    ਜੇ (!ਨਤੀਜਾ) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        ਜੇ (!tried_setting_format) {   // make sure there's an error string set.
            SDL_ਸੈੱਟ_Error("Could not find any supported GBM surface format.");
        }
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
ਸਥਿਰ ਖਾਲੀ KMSDRM_ReleaseVT(ਖਾਲੀ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < viddata->ਅੰਕ_windows; i++) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = viddata->windows[i];
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, ਖਿੜਕੀ);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

ਸਥਿਰ ਖਾਲੀ KMSDRM_AcquireVT(ਖਾਲੀ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ i;

    KMSDRM_drm_ਸੈੱਟ_Master(viddata->drm_fd);
    ਲਈ (i = 0; i < viddata->ਅੰਕ_windows; i++) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = viddata->windows[i];
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, ਖਿੜਕੀ);
        }
    }
}
#ਜੇ_ਅੰਤ // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool ਨਤੀਜਾ = true;

    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    ਜੇ (!KMSDRM_InitDisplays(_this)) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("error getting KMSDRM displays information");
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_ਸੈੱਟ_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#ਜਾਂਜੇ defined(SDL_ਨਿਵੇਸ਼_WSCONS)
    SDL_WSCONS_Init();
#ਜੇ_ਅੰਤ

    viddata->video_init = true;

    ਵਾਪਸ ਨਤੀਜਾ;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
ਖਾਲੀ KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;

    KMSDRM_DeinitDisplays(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    SDL_EVDEV_ਸੈੱਟ_VTSwitch_Callbacks(ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
    SDL_EVDEV_Quit();
#ਜਾਂਜੇ defined(SDL_ਨਿਵੇਸ਼_WSCONS)
    SDL_WSCONS_Quit();
#ਜੇ_ਅੰਤ

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = ਨਿਰਾ;
    viddata->max_windows = 0;
    viddata->ਅੰਕ_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    drm_ਬਹੁਲਕ_Connector *conn = dispdata->connector.connector;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < conn->ਗਿਣਤੀ_modes; i++) {
        SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));

        ਜੇ (modedata) {
            modedata->ਬਹੁਲਕ_ਸੂਚਕਾਂਕ = i;
        }

        SDL_zero(ਬਹੁਲਕ);
        ਬਹੁਲਕ.w = conn->modes[i].hdisplay;
        ਬਹੁਲਕ.h = conn->modes[i].vdisplay;
        Calculate_Refresh_ਦਰ(&conn->modes[i], &ਬਹੁਲਕ.refresh_ਦਰ_numerator, &ਬਹੁਲਕ.refresh_ਦਰ_denominator);
        ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ARGB8888;
        ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;

        ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ)) {
            SDL_free(modedata);
        }
    }
    ਵਾਪਸ true;
}

bool KMSDRM_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    drm_ਬਹੁਲਕ_Connector *conn = dispdata->connector.connector;
    ਪੂਰਨ i;

    // Don't do anything if we are in Vulkan mode.
    ਜੇ (viddata->vulkan_ਬਹੁਲਕ) {
        ਵਾਪਸ true;
    }

    ਜੇ (!modedata) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_ਬਹੁਲਕ = conn->modes[modedata->ਬਹੁਲਕ_ਸੂਚਕਾਂਕ];

    ਲਈ (i = 0; i < viddata->ਅੰਕ_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ KMSDRM_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *dispdata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_Video_ਅੰਕੜੇ *viddata;
    bool is_vulkan = ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN; // Is this a VK window?
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i, j;

    ਜੇ (!windata) {
        ਵਾਪਸ;
    }

    // restore vrr state
    KMSDRM_Crtc_ਸੈੱਟ_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    ਜੇ (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, ਖਿੜਕੀ);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        ਜੇ (viddata->ਅੰਕ_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            ਜੇ (_this->egl_ਅੰਕੜੇ) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } ਨਹੀਂਤਾਂ {

        // If we were in Vulkan mode, get out of it.
        ਜੇ (viddata->vulkan_ਬਹੁਲਕ) {
            viddata->vulkan_ਬਹੁਲਕ = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    ਲਈ (i = 0; i < viddata->ਅੰਕ_windows; i++) {
        ਜੇ (viddata->windows[i] == ਖਿੜਕੀ) {
            viddata->ਅੰਕ_windows--;

            ਲਈ (j = i; j < viddata->ਅੰਕ_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            ਰੋਕੋ;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਨਿਰਾ;
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    bool is_vulkan = ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN; // Is this a VK window?
    bool vulkan_ਬਹੁਲਕ = viddata->vulkan_ਬਹੁਲਕ;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_ਬਹੁਲਕ_ਬਹੁਲਕ_Info *ਬਹੁਲਕ;
    bool ਨਤੀਜਾ = true;

    // Allocate window internal data
    windata = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!windata) {
        ਵਾਪਸ false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_ਬਫਰ = false;
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ਬਫਰ, false)) {
        windata->double_ਬਫਰ = true;
    }

    ਜੇ (!is_vulkan && !vulkan_ਬਹੁਲਕ) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_OPENGL;

        ਜੇ (!(viddata->gbm_init)) {

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
            ਜੇ (!KMSDRM_GBMInit(_this, dispdata)) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        ਜੇ (!_this->egl_ਅੰਕੜੇ) {
            egl_display = (NativeDisplayType)_this->ਅੰਦਰੂਨੀ->gbm_dev;
            ਜੇ (!SDL_EGL_ਲੱਦੋ_Library(_this, ਨਿਰਾ, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_ਸੰਸਕਰਣ = 2;
                _this->gl_config.minor_ਸੰਸਕਰਣ = 0;
                ਜੇ (!SDL_EGL_ਲੱਦੋ_Library(_this, ਨਿਰਾ, egl_display)) {
                    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't load EGL/GL library on window creation.");
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
        ਬਹੁਲਕ = KMSDRM_Get_Closest_Display_ਬਹੁਲਕ(display, ਖਿੜਕੀ->windowed.w, ਖਿੜਕੀ->windowed.h);

        ਜੇ (ਬਹੁਲਕ) {
            dispdata->fullscreen_ਬਹੁਲਕ = *ਬਹੁਲਕ;
        } ਨਹੀਂਤਾਂ {
            dispdata->fullscreen_ਬਹੁਲਕ = dispdata->original_ਬਹੁਲਕ;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        ਜੇ (!KMSDRM_CreateSurfaces(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    ਜੇ (viddata->ਅੰਕ_windows >= viddata->max_windows) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ new_max_windows = viddata->max_windows + 1;
        SDL_ਖਿੜਕੀ **new_windows = (SDL_ਖਿੜਕੀ **)SDL_realloc(viddata->windows,
                                                              new_max_windows * ਆਕਾਰ(SDL_ਖਿੜਕੀ *));
        ਜੇ (!new_windows) {
            ਵਾਪਸ false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->ਅੰਕ_windows++] = ਖਿੜਕੀ;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_ਬਹੁਲਕ = is_vulkan;

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_KMSDRM_DEVICE_ਸੂਚਕਾਂਕ_ਸੰਖਿਆ, viddata->devindex);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_KMSDRM_DRM_FD_ਸੰਖਿਆ, viddata->drm_fd);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_KMSDRM_GBM_DEVICE_ਸੂਚਕ, viddata->gbm_dev);

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ), &display_bounds);
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
bool KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ SDL_Unsupported();
}
ਖਾਲੀ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!viddata->vulkan_ਬਹੁਲਕ) {
        KMSDRM_DirtySurfaces(ਖਿੜਕੀ);
    }
}
SDL_Fullscreen_ਨਤੀਜਾ KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!viddata->vulkan_ਬਹੁਲਕ) {
        KMSDRM_DirtySurfaces(ਖਿੜਕੀ);
    }
    ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
}
ਖਾਲੀ KMSDRM_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ KMSDRM_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ KMSDRM_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ KMSDRM_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ KMSDRM_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ KMSDRM_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
bool KMSDRM_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable)
{
    ਵਾਪਸ true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_KMSDRM
