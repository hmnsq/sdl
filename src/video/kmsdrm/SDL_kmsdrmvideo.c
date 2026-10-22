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

#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#ضمن "../SDL_egl_c.h"

// SDL internals
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"

#که_تعریف_شوی SDL_ننوت_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#وإلاإذا defined SDL_ننوت_WSCONS
#ضمن "../../core/openbsd/SDL_wscons.h"
#د_که_پای

// KMS/DRM declarations
#ضمن "SDL_kmsdrmdyn.h"
#ضمن "SDL_kmsdrmevents.h"
#ضمن "SDL_kmsdrmmouse.h"
#ضمن "SDL_kmsdrmvideo.h"
#ضمن "SDL_kmsdrmopengles.h"
#ضمن "SDL_kmsdrmvulkan.h"
#ضمن <dirent.h>
#ضمن <errno.h>
#ضمن <poll.h>
#ضمن <sys/param.h>
#ضمن <sys/stat.h>
#ضمن <sys/utsname.h>

#که_تعریف_شوی SDL_PLATFORM_OPENBSD
ساكن bool moderndri = false;
#وإلا
ساكن bool moderndri = true;
#د_که_پای

ساكن حرف kmsdrm_dri_لار[16];
ساكن صحيح kmsdrm_dri_pathsize = 0;
ساكن حرف kmsdrm_dri_devname[8];
ساكن صحيح kmsdrm_dri_devnamesize = 0;
ساكن حرف kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#که_نه_تعریف_شوی DRM_FORMAT_MOD_VENDOR_NONE
#تعریف_کړه DRM_FORMAT_MOD_VENDOR_NONE 0
#د_که_پای
#که_نه_تعریف_شوی DRM_FORMAT_MOD_خطي
#تعریف_کړه DRM_FORMAT_MOD_خطي fourcc_mod_کوډ(NONE, 0)
#د_که_پای

ساكن صحيح get_driindex(فراغ)
{
    صحيح شته = -ENOENT;
    حرف device[حجم(kmsdrm_dri_cardpath)];
    صحيح drm_fd;
    صحيح i;
    صحيح devindex = -1;
    DIR *folder;
    ثابت حرف *hint;
    بنية dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_شاخص);
    إذا (hint && *hint) {
        حرف *endptr = عدم;
        ثابت صحيح idx = (صحيح)SDL_strtol(hint, &endptr, 10);
        إذا ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            أرجع idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_لار, حجم(device));
    folder = opendir(device);
    إذا (!folder) {
        SDL_سېټ_Error("Failed to open directory '%s'", device);
        أرجع -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                حجم(device) - kmsdrm_dri_pathsize);
    طالما((res = readdir(folder)) != عدم && شته < 0) {
        إذا (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        حجم(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            إذا (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                إذا (SDL_KMSDRM_بارول_Symbols()) {
                    drm_ډېرپېښ_Res *resources = KMSDRM_drm_ډېرپېښ_Get_Resources(drm_fd);
                    إذا (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->شمېر_connectors,
                                     resources->شمېر_encoders,
                                     resources->شمېر_crtcs);

                        إذا (resources->شمېر_connectors > 0 &&
                            resources->شمېر_encoders > 0 &&
                            resources->شمېر_crtcs > 0) {
                            شته = -ENOENT;
                            لكل (i = 0; i < resources->شمېر_connectors && شته < 0; i++) {
                                drm_ډېرپېښ_Connector *conn =
                                    KMSDRM_drm_ډېرپېښ_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                إذا (!conn) {
                                    استمر;
                                }

                                إذا (conn->connection == DRM_ډېرپېښ_CONNECTED &&
                                    conn->شمېر_modes) {
                                    bool access_denied = false;
                                    إذا (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_سېټ_Master(drm_fd);
                                        إذا (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    إذا (!access_denied) {
                                        شته = devindex;
                                    }
                                }

                                KMSDRM_drm_ډېرپېښ_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_ډېرپېښ_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } وإلا {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    أرجع شته;
}

ساكن فراغ Calculate_Refresh_شرح(drm_ډېرپېښ_ډېرپېښ_Info *ډېرپېښ, صحيح *numerator, صحيح *denominator)
{
    *numerator = ډېرپېښ->clock * 1000;
    *denominator = ډېرپېښ->htotal * ډېرپېښ->vtotal;

    إذا (ډېرپېښ->flags & DRM_ډېرپېښ_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    إذا (ډېرپېښ->flags & DRM_ډېرپېښ_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    إذا (ډېرپېښ->vscan > 1) {
        *denominator *= ډېرپېښ->vscan;
    }
}


صحيح جمع_کړه_connector_property(drm_ډېرپېښ_Atomic_Req *req, KMSDRM_connector *conn, ثابت حرف *name, uint64_t ارزښت)
{
    بینښه صحيح i;
    صحيح prop_id = 0;

    لكل (i = 0 ; i < conn->props->شمېر_props ; i++) {
        إذا (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سېټ_Error("no connector property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_ډېرپېښ_Atomic_جمع_کړه_Property(req, conn->connector->connector_id, prop_id, ارزښت);
}

صحيح جمع_کړه_crtc_property(drm_ډېرپېښ_Atomic_Req *req, KMSDRM_crtc *c, ثابت حرف *name, uint64_t ارزښت)
{
    بینښه صحيح i;
    صحيح prop_id = -1;

    لكل (i = 0 ; i < c->props->شمېر_props ; i++) {
        إذا (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سېټ_Error("no crtc property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_ډېرپېښ_Atomic_جمع_کړه_Property(req, c->crtc->crtc_id, prop_id, ارزښت);
}

صحيح جمع_کړه_plane_property(drm_ډېرپېښ_Atomic_Req *req, KMSDRM_plane *p, ثابت حرف *name, uint64_t ارزښت)
{
    بینښه صحيح i;
    صحيح prop_id = -1;

    لكل (i = 0 ; i < p->props->شمېر_props ; i++) {
        إذا (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سېټ_Error("no plane property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_ډېرپېښ_Atomic_جمع_کړه_Property(req, p->plane->plane_id, prop_id, ارزښت);
}

#که_تعریف_شوی DEBUG_KMSDRM
ساكن فراغ print_plane_info(SDL_VideoDevice *_this, drm_ډېرپېښ_Plane_Ptr plane)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->دننی);
    drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_ډېرپېښ_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    لكل (صحيح i = 0; i < props->شمېر_props; i++) {
        drm_ډېرپېښ_Property_Ptr p = KMSDRM_drm_ډېرپېښ_Get_Property(viddata->drm_fd, props->props[i]);
        إذا ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_ارزښتونه[i];
        }

        KMSDRM_drm_ډېرپېښ_Free_Property(p);
    }

    حرف *plane_type = "unknown";
    بدل (type) {
        حالة DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            اكسر;

        حالة DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            اكسر;

        حالة DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            اكسر;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_ډېرپېښ_Res *resources = KMSDRM_drm_ډېرپېښ_Get_Resources(viddata->drm_fd);
    إذا (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        لكل (صحيح i = 0; i < resources->شمېر_crtcs; i++) {
            إذا (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                اكسر;
            }
        }
        SDL_Log("%s\n\n", (ثابت حرف *)SDL_Get_اشاره_ګر_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_حافظه_اشاره_ګر, ""));
        SDL_CloseIO(io);
    }
}

ساكن فراغ get_planes_info(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->دننی);

    drm_ډېرپېښ_Plane_Res_Ptr plane_resources = KMSDRM_drm_ډېرپېښ_Get_Plane_Resources(viddata->drm_fd);
    إذا (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        أرجع;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->شمېر_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    لكل (uint32_t i = 0; (i < plane_resources->شمېر_planes); i++) {
        ثابت uint32_t plane_id = plane_resources->planes[i];

        drm_ډېرپېښ_Plane_Ptr plane = KMSDRM_drm_ډېرپېښ_Get_Plane(viddata->drm_fd, plane_id);
        إذا (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            استمر;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_ډېرپېښ_Free_Plane(plane);
    }

    KMSDRM_drm_ډېرپېښ_Free_Plane_Resources(plane_resources);
}
#د_که_پای

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
ساكن صحيح get_plane_id(SDL_VideoDevice *_this, بینښه صحيح crtc_id, uint32_t plane_type)
{
    drm_ډېرپېښ_Res *resources = عدم;
    drm_ډېرپېښ_Plane_Res_Ptr plane_resources = عدم;
    uint32_t i, j;
    بینښه صحيح crtc_شاخص = 0;
    صحيح ret = -EINVAL;
    صحيح وموندل = 0;

    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->دننی);

    resources = KMSDRM_drm_ډېرپېښ_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    لكل (i = 0; i < resources->شمېر_crtcs; i++) {
        إذا (resources->crtcs[i] == crtc_id) {
            crtc_شاخص = i;
            اكسر;
        }
    }

    plane_resources = KMSDRM_drm_ډېرپېښ_Get_Plane_Resources(viddata->drm_fd);
    إذا (!plane_resources) {
        أرجع SDL_سېټ_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    لكل (i = 0; (i < plane_resources->شمېر_planes) && !وموندل; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_ډېرپېښ_Plane_Ptr plane = KMSDRM_drm_ډېرپېښ_Get_Plane(viddata->drm_fd, plane_id);
        إذا (!plane) {
            استمر;
        }

        /* See if the current CRTC is available for this plane. */
        إذا (plane->possible_crtcs & (1 << crtc_شاخص)) {

            drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_ډېرپېښ_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            لكل (j = 0; j < props->شمېر_props; j++) {

                drm_ډېرپېښ_Property_Ptr p = KMSDRM_drm_ډېرپېښ_Get_Property(viddata->drm_fd,
                    props->props[j]);

                إذا ((SDL_strcmp(p->name, "type") == 0) && (props->prop_ارزښتونه[j] == plane_type)) {
                    /* found our plane, use that: */
                    وموندل = 1;
                }

                KMSDRM_drm_ډېرپېښ_Free_Property(p);
            }

            KMSDRM_drm_ډېرپېښ_Free_Object_Properties(props);
        }

        KMSDRM_drm_ډېرپېښ_Free_Plane(plane);
    }

    KMSDRM_drm_ډېرپېښ_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_ډېرپېښ_Free_Resources(resources);

    أرجع ret;
}

/* Setup a plane and it's props. */
bool تیاری_plane(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->دننی);
    bool ret = true;

    *_plane = SDL_calloc(1, حجم(**_plane));
    إذا (!(*_plane)) {
        ret = false;
        اذهب cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    إذا (!plane_id) {
        ret = SDL_سېټ_Error("Invalid Plane ID");
        اذهب cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_ډېرپېښ_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    إذا ((*_plane)->plane) {
        بینښه صحيح i;
        (*_plane)->props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_ډېرپېښ_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->شمېر_props, حجم(*(*_plane)->props_info));

        إذا ( !((*_plane)->props_info) ) {
            ret = false;
            اذهب cleanup;
        }

        لكل (i = 0; i < (*_plane)->props->شمېر_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_ډېرپېښ_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    إذا (!ret) {
        إذا (*_plane) {
            SDL_free(*_plane);
            *_plane = عدم;
        }
    }
    أرجع ret;
}

/* Free a plane and it's props. */
فراغ free_plane(KMSDRM_plane **_plane)
{
    إذا (*_plane) {
        إذا ((*_plane)->plane) {
            KMSDRM_drm_ډېرپېښ_Free_Plane((*_plane)->plane);
            (*_plane)->plane = عدم;
        }
        إذا ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = عدم;
        }
        SDL_free(*_plane);
        *_plane = عدم;
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
فراغ
drm_atomic_سېټ_plane_props(SDL_Display_معلومات *dispdata, بنية KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    إذا (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_ډېرپېښ_Atomic_Alloc();
    }

    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    جمع_کړه_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

صحيح drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->دننی);
    uint32_t atomic_flags = 0;
    صحيح ret;

    إذا (!blocking) {
        atomic_flags |= DRM_ډېرپېښ_ATOMIC_NONBLOCK;
    }

    إذا (allow_modeset) {
        atomic_flags |= DRM_ډېرپېښ_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_ډېرپېښ_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, عدم);

    إذا (ret) {
        SDL_سېټ_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#إذا 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#د_که_پای
        اذهب بهر;
    }

    إذا (dispdata->kms_دننه_fence_fd != -1) {
        close(dispdata->kms_دننه_fence_fd);
        dispdata->kms_دننه_fence_fd = -1;
    }

بهر:
    KMSDRM_drm_ډېرپېښ_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = عدم;

    أرجع ret;
}

فراغ
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    إذا (dispdata->kms_fence) {
       EGLint حالت;

        افعل {
            حالت = _this->egl_معلومات->eglClientWaitSyncKHR(_this->egl_معلومات->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } طالما (حالت != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_معلومات->eglDestroySyncKHR(_this->egl_معلومات->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = عدم;
    }
}

ساكن bool KMSDRM_شته(فراغ)
{
#که_تعریف_شوی SDL_PLATFORM_OPENBSD
    بنية utsname nameofsystem;
    مزدوج releaseversion;
#د_که_پای
    صحيح ret = -ENOENT;

#که_تعریف_شوی SDL_PLATFORM_OPENBSD
    إذا (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        إذا (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#د_که_پای

    إذا (moderndri) {
        SDL_strlcpy(kmsdrm_dri_لار, "/dev/dri/", حجم(kmsdrm_dri_لار));
        SDL_strlcpy(kmsdrm_dri_devname, "card", حجم(kmsdrm_dri_devname));
    } وإلا {
        SDL_strlcpy(kmsdrm_dri_لار, "/dev/", حجم(kmsdrm_dri_لار));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", حجم(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_لار);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (فراغ)SDL_snprintf(kmsdrm_dri_cardpath, حجم(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_لار, kmsdrm_dri_devname);

    ret = get_driindex();
    إذا (ret >= 0) {
        أرجع true;
    }

    أرجع false;
}

ساكن فراغ KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    إذا (device->دننی) {
        SDL_free(device->دننی);
        device->دننی = عدم;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

ساكن SDL_VideoDevice *KMSDRM_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *viddata;
    صحيح devindex;

    إذا (!KMSDRM_شته()) {
        أرجع عدم;
    }

    devindex = get_driindex();
    إذا (devindex < 0) {
        SDL_سېټ_Error("devindex (%d) must not be negative.", devindex);
        أرجع عدم;
    }

    إذا (!SDL_KMSDRM_بارول_Symbols()) {
        أرجع عدم;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    viddata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!viddata) {
        اذهب cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->دننی = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = KMSDRM_سېټ_Display_ډېرپېښ;
    device->CreateSDLWindow = KMSDRM_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = KMSDRM_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Position = KMSDRM_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = KMSDRM_سېټ_کړکۍ_اندازه;
    device->سېټ_کړکۍ_Fullscreen = KMSDRM_سېټ_کړکۍ_Fullscreen;
    device->Show_کړکۍ = KMSDRM_Show_کړکۍ;
    device->Hide_کړکۍ = KMSDRM_Hide_کړکۍ;
    device->Raise_کړکۍ = KMSDRM_Raise_کړکۍ;
    device->Maximize_کړکۍ = KMSDRM_Maximize_کړکۍ;
    device->Minimize_کړکۍ = KMSDRM_Minimize_کړکۍ;
    device->Restore_کړکۍ = KMSDRM_Restore_کړکۍ;
    device->Destroy_کړکۍ = KMSDRM_Destroy_کړکۍ;
    device->سېټ_کړکۍ_Focusable = KMSDRM_سېټ_کړکۍ_Focusable;

    device->GL_بارول_Library = KMSDRM_GLES_بارول_Library;
    device->GL_Get_Proc_پته = KMSDRM_GLES_Get_Proc_پته;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = KMSDRM_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = KMSDRM_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = KMSDRM_GLES_بدلون_کړکۍ;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_سېټ_Default_Profile_Config = KMSDRM_GLES_سېټ_Default_Profile_Config;

#که_تعریف_شوی SDL_VIDEO_VULKAN
    device->Vulkan_بارول_Library = KMSDRM_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#د_که_پای

    device->PumpEvents = KMSDRM_PumpEvents;
    device->حرر = KMSDRM_DeleteDevice;

    أرجع device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    أرجع عدم;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

ساكن فراغ KMSDRM_FBDestroyCallback(بنية gbm_bo *bo, فراغ *معلومات)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)معلومات;

    إذا (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_ډېرپېښ_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, بنية gbm_bo *bo)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    بینښه w, h;
    صحيح rc = -1;
    صحيح عدد_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_معلومات(bo);

    إذا (fb_info) {
        أرجع fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, حجم(KMSDRM_FBInfo));

    إذا (!fb_info) {
        أرجع عدم;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_پلنوالی(bo);
    h = KMSDRM_gbm_bo_get_لوړوالی(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    إذا (KMSDRM_drm_ډېرپېښ_جمع_کړه_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_شمېر &&
        KMSDRM_gbm_bo_get_دننه_واټن &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        عدد_planes = KMSDRM_gbm_bo_get_plane_شمېر(bo);
        لكل (صحيح i = 0; i < عدد_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_دننه_واټن(bo, i);
            modifiers[i] = modifiers[0];
        }

        إذا (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_ډېرپېښ_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_ډېرپېښ_جمع_کړه_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    إذا (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_ډېرپېښ_جمع_کړه_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    إذا (rc < 0) {
        SDL_free(fb_info);
        أرجع عدم;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (فراغ *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_سېټ_user_معلومات(bo, fb_info, KMSDRM_FBDestroyCallback);

    أرجع fb_info;
}

ساكن فراغ KMSDRM_FlipHandler(صحيح fd, بینښه صحيح چوکاټ, بینښه صحيح sec, بینښه صحيح usec, فراغ *معلومات)
{
    *((bool *)معلومات) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_کړکۍ_معلومات *windata)
{

    SDL_Video_معلومات *viddata = _this->دننی;
    drmEventContext ev = { 0 };
    بنية pollfd pfd = { 0 };
    صحيح ret;

    ev.نسخه = DRM_EVENT_CONTEXT_نسخه;
    ev.پاڼه_flip_handler = KMSDRM_FlipHandler;

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
    طالما (windata->انتظار_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        إذا (ret < 0) {
            إذا (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                استمر;
            } وإلا {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                أرجع false;
            }
        }

        إذا (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            أرجع false;
        }

        إذا (pfd.revents & POLLIN) {
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

    أرجع true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
ساكن drm_ډېرپېښ_ډېرپېښ_Info *KMSDRM_Get_Closest_Display_ډېرپېښ(SDL_VideoDisplay *display, صحيح پلنوالی, صحيح لوړوالی)
{

    SDL_Display_معلومات *dispdata = display->دننی;
    drm_ډېرپېښ_Connector *conn = dispdata->connector.connector;

    SDL_Display_ډېرپېښ closest;
    drm_ډېرپېښ_ډېرپېښ_Info *drm_ډېرپېښ;

    إذا (SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(display->id, پلنوالی, لوړوالی, 0.0f, false, &closest)) {
        ثابت SDL_Display_ډېرپېښ_معلومات *modedata = closest.دننی;
        drm_ډېرپېښ = &conn->modes[modedata->ډېرپېښ_شاخص];
        أرجع drm_ډېرپېښ;
    } وإلا {
        أرجع عدم;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

ساكن bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *viddata = _this->دننی;

    إذا (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_سېټ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_سېټ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    إذا (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        أرجع true;
    }

    أرجع KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
ساكن فراغ KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_DisplayID *displays;
    SDL_Display_معلومات *dispdata;
    صحيح i;

    displays = SDL_GetDisplays(عدم);
    إذا (displays) {
        // Iterate on the SDL Display list.
        لكل (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_معلومات(displays[i]);

            // Free connector
            إذا (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_ډېرپېښ_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = عدم;
            }

            // Free CRTC
            إذا (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_ډېرپېښ_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = عدم;
            }
        }
        SDL_free(displays);
    }

    إذا (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

ساكن bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool وموندل = false;
    uint64_t prop_ارزښت = 0;

    drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(drm_fd, output_id, DRM_ډېرپېښ_OBJECT_CONNECTOR);
    إذا (props) {
        لكل (uint32_t i = 0; !وموندل && i < props->شمېر_props; ++i) {
            drm_ډېرپېښ_Property_Ptr prop = KMSDRM_drm_ډېرپېښ_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_ارزښت = props->prop_ارزښتونه[i];
                    وموندل = true;
                }
                KMSDRM_drm_ډېرپېښ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ډېرپېښ_Free_Object_Properties(props);
    }
    إذا (وموندل) {
        أرجع prop_ارزښت ? true : false;
    }
    أرجع false;
}

ساكن bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool وموندل = false;
    drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(drm_fd, crtc_id, DRM_ډېرپېښ_OBJECT_CRTC);
    إذا (props) {
        لكل (uint32_t i = 0; !وموندل && i < props->شمېر_props; ++i) {
            drm_ډېرپېښ_Property_Ptr prop = KMSDRM_drm_ډېرپېښ_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    وموندل = true;
                }
                KMSDRM_drm_ډېرپېښ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ډېرپېښ_Free_Object_Properties(props);
    }
    أرجع وموندل;
}

ساكن فراغ KMSDRM_Crtc_سېټ_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    إذا (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        أرجع;
    }

    KMSDRM_drm_ډېرپېښ_Object_سېټ_Property(drm_fd, crtc_id, DRM_ډېرپېښ_OBJECT_CRTC, vrr_prop_id, enabled);
}

ساكن bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool وموندل = false;
    uint64_t prop_ارزښت = 0;

    إذا (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        أرجع false;
    }

    drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(drm_fd, crtc_id, DRM_ډېرپېښ_OBJECT_CRTC);
    إذا (props) {
        لكل (uint32_t i = 0; !وموندل && i < props->شمېر_props; ++i) {
            drm_ډېرپېښ_Property_Ptr prop = KMSDRM_drm_ډېرپېښ_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (prop->prop_id == vrr_prop_id) {
                    prop_ارزښت = props->prop_ارزښتونه[i];
                    وموندل = true;
                }
                KMSDRM_drm_ډېرپېښ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ډېرپېښ_Free_Object_Properties(props);
    }
    إذا (وموندل) {
        أرجع prop_ارزښت ? true : false;
    }
    أرجع false;
}

ساكن صحيح KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool وموندل = false;
    صحيح orientation = 0;

    drm_ډېرپېښ_Object_Properties_Ptr props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(drm_fd, crtc_id, DRM_ډېرپېښ_OBJECT_CONNECTOR);
    إذا (props) {
        لكل (uint32_t i = 0; !وموندل && i < props->شمېر_props; ++i) {
            drm_ډېرپېښ_Property_Ptr prop = KMSDRM_drm_ډېرپېښ_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_ډېرپېښ_PROP_ENUM)) {
                    إذا (prop->شمېر_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        إذا (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } وإلا إذا (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } وإلا إذا (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    وموندل = true;
                }
                KMSDRM_drm_ډېرپېښ_Free_Property(prop);
            }
        }
        KMSDRM_drm_ډېرپېښ_Free_Object_Properties(props);
    }
    أرجع orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
ساكن فراغ KMSDRM_جمع_کړه_Display(SDL_VideoDevice *_this, drm_ډېرپېښ_Connector *conn, drm_ډېرپېښ_Res *resources)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_Display_معلومات *dispdata = عدم;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_ډېرپېښ_معلومات *modedata = عدم;
    drm_ډېرپېښ_Encoder *encoder = عدم;
    drm_ډېرپېښ_Crtc *crtc = عدم;
    ثابت حرف *connector_type = عدم;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    حرف name_fmt[64];
    صحيح orientation;
    صحيح ډېرپېښ_شاخص;
    صحيح i, j;
    صحيح ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_معلومات *)SDL_calloc(1, حجم(SDL_Display_معلومات));
    إذا (!dispdata) {
        ret = -1;
        اذهب cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = عدم;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_دننه_fence_fd = -1;
    dispdata->kms_بهر_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    لكل (i = 0; i < resources->شمېر_encoders; i++) {
        encoder = KMSDRM_drm_ډېرپېښ_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        إذا (!encoder) {
            استمر;
        }

        إذا (encoder->encoder_id == conn->encoder_id) {
            اكسر;
        }

        KMSDRM_drm_ډېرپېښ_Free_Encoder(encoder);
        encoder = عدم;
    }

    إذا (!encoder) {
        // No encoder was connected, find the first supported one
        لكل (i = 0; i < resources->شمېر_encoders; i++) {
            encoder = KMSDRM_drm_ډېرپېښ_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            إذا (!encoder) {
                استمر;
            }

            لكل (j = 0; j < conn->شمېر_encoders; j++) {
                إذا (conn->encoders[j] == encoder->encoder_id) {
                    اكسر;
                }
            }

            إذا (j != conn->شمېر_encoders) {
                اكسر;
            }

            KMSDRM_drm_ډېرپېښ_Free_Encoder(encoder);
            encoder = عدم;
        }
    }

    إذا (!encoder) {
        ret = SDL_سېټ_Error("No connected encoder found for connector.");
        اذهب cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_ډېرپېښ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    إذا (!crtc) {
        لكل (i = 0; i < resources->شمېر_crtcs; i++) {
            إذا (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_ډېرپېښ_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                اكسر;
            }
        }
    }

    إذا (!crtc) {
        ret = SDL_سېټ_Error("No CRTC found for connector.");
        اذهب cleanup;
    }

    // Find the index of the mode attached to this CRTC
    ډېرپېښ_شاخص = -1;

    لكل (i = 0; i < conn->شمېر_modes; i++) {
        drm_ډېرپېښ_ډېرپېښ_Info *ډېرپېښ = &conn->modes[i];

        إذا (!SDL_memcmp(ډېرپېښ, &crtc->ډېرپېښ, حجم(crtc->ډېرپېښ))) {
            ډېرپېښ_شاخص = i;
            اكسر;
        }
    }

    إذا (ډېرپېښ_شاخص == -1) {
        صحيح current_area, تر_ټولو_لوی_area = 0;

        // Find the preferred mode or the highest resolution mode
        لكل (i = 0; i < conn->شمېر_modes; i++) {
            drm_ډېرپېښ_ډېرپېښ_Info *ډېرپېښ = &conn->modes[i];

            إذا (ډېرپېښ->type & DRM_ډېرپېښ_TYPE_PREFERRED) {
                ډېرپېښ_شاخص = i;
                اكسر;
            }

            current_area = ډېرپېښ->hdisplay * ډېرپېښ->vdisplay;
            إذا (current_area > تر_ټولو_لوی_area) {
                ډېرپېښ_شاخص = i;
                تر_ټولو_لوی_area = current_area;
            }
        }
        إذا (ډېرپېښ_شاخص != -1) {
            crtc->ډېرپېښ = conn->modes[ډېرپېښ_شاخص];
        }
    }

    إذا (ډېرپېښ_شاخص == -1) {
        ret = SDL_سېټ_Error("Failed to find index of mode attached to the CRTC.");
        اذهب cleanup;
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
    dispdata->ډېرپېښ = crtc->ډېرپېښ;
    dispdata->original_ډېرپېښ = crtc->ډېرپېښ;
    dispdata->fullscreen_ډېرپېښ = crtc->ډېرپېښ;

    إذا (dispdata->ډېرپېښ.hdisplay == 0 || dispdata->ډېرپېښ.vdisplay == 0) {
        ret = SDL_سېټ_Error("Couldn't get a valid connector videomode.");
        اذهب cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    إذا (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_سېټ_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    إذا (KMSDRM_drm_ډېرپېښ_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_ډېرپېښ_Get_Connector_Type_Name(conn->connector_type);
        إذا (connector_type == عدم) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, حجم(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_ډېرپېښ_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->شمېر_props, حجم(*dispdata->crtc.props_info));
    إذا (!dispdata->crtc.props_info) {
        ret = false;
        اذهب cleanup;
    }

    لكل (i = 0; i < dispdata->crtc.props->شمېر_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_ډېرپېښ_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_ډېرپېښ_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_ډېرپېښ_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->شمېر_props, حجم(*dispdata->connector.props_info));
    إذا (!dispdata->connector.props_info) {
        ret = false;
        اذهب cleanup;
    }

    لكل (i = 0; i < dispdata->connector.props->شمېر_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_ډېرپېښ_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, حجم(SDL_Display_ډېرپېښ_معلومات));

    إذا (!modedata) {
        ret = -1;
        اذهب cleanup;
    }

    modedata->ډېرپېښ_شاخص = ډېرپېښ_شاخص;

    display.دننی = dispdata;
    display.desktop_ډېرپېښ.w = dispdata->ډېرپېښ.hdisplay;
    display.desktop_ډېرپېښ.h = dispdata->ډېرپېښ.vdisplay;
    Calculate_Refresh_شرح(&dispdata->ډېرپېښ, &display.desktop_ډېرپېښ.refresh_شرح_numerator, &display.desktop_ډېرپېښ.refresh_شرح_denominator);
    display.desktop_ډېرپېښ.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_ډېرپېښ.دننی = modedata;
    إذا (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_جمع_کړه_Video_Display(&display, false);
    إذا (!display_id) {
        ret = -1;
        اذهب cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_سېټ_شمېره_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_شمېره, orientation);

#که_تعریف_شوی DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#د_که_پای

cleanup:
    إذا (encoder) {
        KMSDRM_drm_ډېرپېښ_Free_Encoder(encoder);
    }
    إذا (ret) {
        // Error (complete) cleanup
        إذا (dispdata) {
            إذا (dispdata->connector.connector) {
                KMSDRM_drm_ډېرپېښ_Free_Connector(dispdata->connector.connector);
            }
            إذا (dispdata->crtc.crtc) {
                KMSDRM_drm_ډېرپېښ_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

ساكن فراغ KMSDRM_ترتیبول_Displays(SDL_VideoDevice *_this)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_لومړیتوب);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(حجم(SDL_VideoDisplay *) * _this->عدد_displays);

        إذا (str && sorted_list) {
            صحيح sorted_شاخص = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    إذا (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_شاخص++] = d;
                        _this->displays[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
                إذا (_this->displays[i]) {
                    sorted_list[sorted_شاخص++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, حجم(SDL_VideoDisplay *) * _this->عدد_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن bool سېټ_client_atomic_caps(صحيح fd)
{
    إذا (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        أرجع false;  // emergency escape hatch.
    } وإلا إذا (KMSDRM_drm_سېټ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        أرجع false;  // no atomic modesetting support.
    } وإلا إذا (KMSDRM_drm_سېټ_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_سېټ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        أرجع false;  // no universal planes support.
    }
    أرجع true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
ساكن bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    drm_ډېرپېښ_Res *resources = عدم;
    uint64_t async_pageflip = 0;
    صحيح i;
    bool پایله = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (فراغ)SDL_snprintf(viddata->devpath, حجم(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    إذا (viddata->drm_fd < 0) {
        پایله = SDL_سېټ_Error("Could not open %s", viddata->devpath);
        اذهب cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = سېټ_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_ډېرپېښ_Get_Resources(viddata->drm_fd);
    إذا (!resources) {
        پایله = SDL_سېټ_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        اذهب cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    لكل (i = 0; i < resources->شمېر_connectors; i++) {
        drm_ډېرپېښ_Connector *conn = KMSDRM_drm_ډېرپېښ_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        إذا (!conn) {
            استمر;
        }

        إذا (conn->connection == DRM_ډېرپېښ_CONNECTED && conn->شمېر_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_جمع_کړه_Display(_this, conn, resources);
        } وإلا {
            // If it's not, free it now.
            KMSDRM_drm_ډېرپېښ_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    إذا (SDL_GetPrimaryDisplay() == 0) {
        پایله = SDL_سېټ_Error("No connected displays found.");
        اذهب cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_ترتیبول_Displays(_this);

    // Determine if video hardware supports async pageflips.
    إذا (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_پاڼه_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    إذا (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    إذا (resources) {
        KMSDRM_drm_ډېرپېښ_Free_Resources(resources);
    }
    إذا (!پایله) {
        إذا (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    أرجع پایله;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
ساكن bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    bool پایله = true;

    // Reopen the FD if we weren't able to drop master on the original one
    إذا (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        إذا (viddata->drm_fd < 0) {
            أرجع SDL_سېټ_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = سېټ_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_سېټ_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    إذا (!viddata->gbm_dev) {
        پایله = SDL_سېټ_Error("Couldn't create gbm device.");
    } وإلا {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        پایله = تیاری_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        إذا (!پایله) {
            SDL_سېټ_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    أرجع پایله;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
ساكن فراغ KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    SDL_Video_معلومات *viddata = _this->دننی;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    إذا (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = عدم;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    إذا (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

ساكن فراغ KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_کړکۍ_معلومات *windata = کړکۍ->دننی;
    SDL_Display_معلومات *dispdata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    صحيح ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    إذا (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#إذا 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        جمع_کړه_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        جمع_کړه_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        جمع_کړه_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_پاڼه_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_سېټ_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_ډېرپېښ_سېټ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_ډېرپېښ);

        /* Issue atomic commit that is blocking and allows modesetting. */
        إذا (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_سېټ_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        إذا (ret && (dispdata->crtc->ډېرپېښ_valid == 0)) {
            ret = KMSDRM_drm_ډېرپېښ_سېټ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_ډېرپېښ);
        }
#د_که_پای

#إذا 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->بفر_id;
        plane_info.src_w = dispdata->original_ډېرپېښ.hdisplay;
        plane_info.src_h = dispdata->original_ډېرپېښ.vdisplay;
        plane_info.crtc_w = dispdata->original_ډېرپېښ.hdisplay;
        plane_info.crtc_h = dispdata->original_ډېرپېښ.vdisplay;

        drm_atomic_سېټ_plane_props(dispdata, &plane_info);

        إذا (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_سېټ_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#د_که_پای

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_ډېرپېښ_سېټ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_ډېرپېښ);

    // If we failed to set the original mode, try to set the connector preferred mode.
    إذا (ret && (dispdata->crtc.crtc->ډېرپېښ_valid == 0)) {
        ret = KMSDRM_drm_ډېرپېښ_سېټ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_ډېرپېښ);
    }

    إذا (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    إذا (windata->bo) {
        إذا (windata->bo != windata->بل_bo) {
            KMSDRM_gbm_surface_release_بفر(windata->gs, windata->bo);
        }
        windata->bo = عدم;
    }

    إذا (windata->بل_bo) {
        KMSDRM_gbm_surface_release_بفر(windata->gs, windata->بل_bo);
        windata->بل_bo = عدم;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    إذا (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    إذا (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = عدم;
    }
}

ساكن فراغ KMSDRM_Get_ډېرپېښ_منزل_سېټ(SDL_کړکۍ *کړکۍ, drm_ډېرپېښ_ډېرپېښ_Info *بهر_ډېرپېښ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    SDL_Display_معلومات *dispdata = display->دننی;

    إذا (کړکۍ->fullscreen_exclusive) {
        *بهر_ډېرپېښ = dispdata->fullscreen_ډېرپېښ;
    } وإلا {
        drm_ډېرپېښ_ډېرپېښ_Info *ډېرپېښ = KMSDRM_Get_Closest_Display_ډېرپېښ(display, کړکۍ->windowed.w, کړکۍ->windowed.h);
        إذا (ډېرپېښ) {
            *بهر_ډېرپېښ = *ډېرپېښ;
        } وإلا {
            *بهر_ډېرپېښ = dispdata->original_ډېرپېښ;
        }
    }
}

ساكن فراغ KMSDRM_DirtySurfaces(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *windata = کړکۍ->دننی;
    drm_ډېرپېښ_ډېرپېښ_Info ډېرپېښ;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_ډېرپېښ_منزل_سېټ(کړکۍ, &ډېرپېښ);
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, ډېرپېښ.hdisplay, ډېرپېښ.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    ساكن ثابت بنية { uint32_t fmt; ثابت حرف *name; صحيح r; صحيح g; صحيح b; صحيح a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #تعریف_کړه FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #تعریف_لغوه FMT
    };

    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_کړکۍ_معلومات *windata = کړکۍ->دننی;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    SDL_Display_معلومات *dispdata = display->دننی;
    EGLContext egl_context;
    bool پایله = false;

    // If the current window already has surfaces, destroy them before creating other.
    إذا (windata->gs) {
        KMSDRM_DestroySurfaces(_this, کړکۍ);
    }

    bool tried_setting_format = false;
    ثابت uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    لكل (صحيح i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ثابت uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        إذا (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            استمر;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_ډېرپېښ_منزل_سېټ(کړکۍ, &dispdata->ډېرپېښ);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ډېرپېښ.hdisplay, dispdata->ډېرپېښ.vdisplay, surface_fmt, surface_flags);
        إذا (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->ډېرپېښ.hdisplay, dispdata->ډېرپېښ.vdisplay, surface_fmt, 0);
        }
        إذا (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_سېټ_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            استمر;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_سېټ_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)windata->gs);
        إذا (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = عدم;
            استمر;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        پایله = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        إذا (!پایله) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            استمر;
        }

        _this->gl_config.red_اندازه = gbm_formats[i].r;
        _this->gl_config.green_اندازه = gbm_formats[i].g;
        _this->gl_config.blue_اندازه = gbm_formats[i].b;
        _this->gl_config.alpha_اندازه = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        پایله = true;

        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, dispdata->ډېرپېښ.hdisplay, dispdata->ډېرپېښ.vdisplay);

        اكسر;
    }

    SDL_assert(پایله || (windata->gs == عدم));

    إذا (!پایله) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        إذا (!tried_setting_format) {   // make sure there's an error string set.
            SDL_سېټ_Error("Could not find any supported GBM surface format.");
        }
    }

    أرجع پایله;
}

#که_تعریف_شوی SDL_ننوت_LINUXEV
ساكن فراغ KMSDRM_ReleaseVT(فراغ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_معلومات *viddata = _this->دننی;
    صحيح i;

    لكل (i = 0; i < viddata->عدد_windows; i++) {
        SDL_کړکۍ *کړکۍ = viddata->windows[i];
        إذا (!(کړکۍ->flags & SDL_کړکۍ_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, کړکۍ);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

ساكن فراغ KMSDRM_AcquireVT(فراغ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_معلومات *viddata = _this->دننی;
    صحيح i;

    KMSDRM_drm_سېټ_Master(viddata->drm_fd);
    لكل (i = 0; i < viddata->عدد_windows; i++) {
        SDL_کړکۍ *کړکۍ = viddata->windows[i];
        إذا (!(کړکۍ->flags & SDL_کړکۍ_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, کړکۍ);
        }
    }
}
#د_که_پای // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool پایله = true;

    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    إذا (!KMSDRM_InitDisplays(_this)) {
        پایله = SDL_سېټ_Error("error getting KMSDRM displays information");
    }

#که_تعریف_شوی SDL_ننوت_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_سېټ_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#وإلاإذا defined(SDL_ننوت_WSCONS)
    SDL_WSCONS_Init();
#د_که_پای

    viddata->video_init = true;

    أرجع پایله;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
فراغ KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *viddata = _this->دننی;

    KMSDRM_DeinitDisplays(_this);

#که_تعریف_شوی SDL_ننوت_LINUXEV
    SDL_EVDEV_سېټ_VTSwitch_Callbacks(عدم, عدم, عدم, عدم);
    SDL_EVDEV_Quit();
#وإلاإذا defined(SDL_ننوت_WSCONS)
    SDL_WSCONS_Quit();
#د_که_پای

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = عدم;
    viddata->max_windows = 0;
    viddata->عدد_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_معلومات *dispdata = display->دننی;
    drm_ډېرپېښ_Connector *conn = dispdata->connector.connector;
    SDL_Display_ډېرپېښ ډېرپېښ;
    صحيح i;

    لكل (i = 0; i < conn->شمېر_modes; i++) {
        SDL_Display_ډېرپېښ_معلومات *modedata = SDL_calloc(1, حجم(SDL_Display_ډېرپېښ_معلومات));

        إذا (modedata) {
            modedata->ډېرپېښ_شاخص = i;
        }

        SDL_zero(ډېرپېښ);
        ډېرپېښ.w = conn->modes[i].hdisplay;
        ډېرپېښ.h = conn->modes[i].vdisplay;
        Calculate_Refresh_شرح(&conn->modes[i], &ډېرپېښ.refresh_شرح_numerator, &ډېرپېښ.refresh_شرح_denominator);
        ډېرپېښ.format = SDL_PIXELFORMAT_ARGB8888;
        ډېرپېښ.دننی = modedata;

        إذا (!SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &ډېرپېښ)) {
            SDL_free(modedata);
        }
    }
    أرجع true;
}

bool KMSDRM_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_Display_معلومات *dispdata = display->دننی;
    SDL_Display_ډېرپېښ_معلومات *modedata = ډېرپېښ->دننی;
    drm_ډېرپېښ_Connector *conn = dispdata->connector.connector;
    صحيح i;

    // Don't do anything if we are in Vulkan mode.
    إذا (viddata->vulkan_ډېرپېښ) {
        أرجع true;
    }

    إذا (!modedata) {
        أرجع SDL_سېټ_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_ډېرپېښ = conn->modes[modedata->ډېرپېښ_شاخص];

    لكل (i = 0; i < viddata->عدد_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    أرجع true;
}

فراغ KMSDRM_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *windata = کړکۍ->دننی;
    SDL_Display_معلومات *dispdata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(کړکۍ);
    SDL_Video_معلومات *viddata;
    bool is_vulkan = کړکۍ->flags & SDL_کړکۍ_VULKAN; // Is this a VK window?
    بینښه صحيح i, j;

    إذا (!windata) {
        أرجع;
    }

    // restore vrr state
    KMSDRM_Crtc_سېټ_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    إذا (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_کړکۍ(کړکۍ));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, کړکۍ);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        إذا (viddata->عدد_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            إذا (_this->egl_معلومات) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } وإلا {

        // If we were in Vulkan mode, get out of it.
        إذا (viddata->vulkan_ډېرپېښ) {
            viddata->vulkan_ډېرپېښ = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    لكل (i = 0; i < viddata->عدد_windows; i++) {
        إذا (viddata->windows[i] == کړکۍ) {
            viddata->عدد_windows--;

            لكل (j = i; j < viddata->عدد_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            اكسر;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(کړکۍ->دننی);
    کړکۍ->دننی = عدم;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *windata = عدم;
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    SDL_Display_معلومات *dispdata = display->دننی;
    bool is_vulkan = کړکۍ->flags & SDL_کړکۍ_VULKAN; // Is this a VK window?
    bool vulkan_ډېرپېښ = viddata->vulkan_ډېرپېښ;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_ډېرپېښ_ډېرپېښ_Info *ډېرپېښ;
    bool پایله = true;

    // Allocate window internal data
    windata = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!windata) {
        أرجع false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    کړکۍ->دننی = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_بفر = false;
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        windata->double_بفر = true;
    }

    إذا (!is_vulkan && !vulkan_ډېرپېښ) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        کړکۍ->flags |= SDL_کړکۍ_OPENGL;

        إذا (!(viddata->gbm_init)) {

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
            إذا (!KMSDRM_GBMInit(_this, dispdata)) {
                أرجع SDL_سېټ_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        إذا (!_this->egl_معلومات) {
            egl_display = (NativeDisplayType)_this->دننی->gbm_dev;
            إذا (!SDL_EGL_بارول_Library(_this, عدم, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_نسخه = 2;
                _this->gl_config.minor_نسخه = 0;
                إذا (!SDL_EGL_بارول_Library(_this, عدم, egl_display)) {
                    أرجع SDL_سېټ_Error("Can't load EGL/GL library on window creation.");
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
        ډېرپېښ = KMSDRM_Get_Closest_Display_ډېرپېښ(display, کړکۍ->windowed.w, کړکۍ->windowed.h);

        إذا (ډېرپېښ) {
            dispdata->fullscreen_ډېرپېښ = *ډېرپېښ;
        } وإلا {
            dispdata->fullscreen_ډېرپېښ = dispdata->original_ډېرپېښ;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        إذا (!KMSDRM_CreateSurfaces(_this, کړکۍ)) {
            أرجع false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    إذا (viddata->عدد_windows >= viddata->max_windows) {
        بینښه صحيح new_max_windows = viddata->max_windows + 1;
        SDL_کړکۍ **new_windows = (SDL_کړکۍ **)SDL_realloc(viddata->windows,
                                                              new_max_windows * حجم(SDL_کړکۍ *));
        إذا (!new_windows) {
            أرجع false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->عدد_windows++] = کړکۍ;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_ډېرپېښ = is_vulkan;

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_KMSDRM_DEVICE_شاخص_شمېره, viddata->devindex);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_KMSDRM_DRM_FD_شمېره, viddata->drm_fd);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_KMSDRM_GBM_DEVICE_اشاره_ګر, viddata->gbm_dev);

    إذا ((کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_سېټ_Mouse_Focus(کړکۍ);
        SDL_سېټ_Keyboard_Focus(کړکۍ);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_کړکۍ(کړکۍ), &display_bounds);
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    أرجع پایله;
}

فراغ KMSDRM_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
bool KMSDRM_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    أرجع SDL_Unsupported();
}
فراغ KMSDRM_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    إذا (!viddata->vulkan_ډېرپېښ) {
        KMSDRM_DirtySurfaces(کړکۍ);
    }
}
SDL_Fullscreen_پایله KMSDRM_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    إذا (!viddata->vulkan_ډېرپېښ) {
        KMSDRM_DirtySurfaces(کړکۍ);
    }
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}
فراغ KMSDRM_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ KMSDRM_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ KMSDRM_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ KMSDRM_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ KMSDRM_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ KMSDRM_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
bool KMSDRM_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable)
{
    أرجع true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#د_که_پای // SDL_VIDEO_DRIVER_KMSDRM
