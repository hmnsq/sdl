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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#ضمن "../SDL_egl_c.h"

// SDL internals
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#وإلاإذا defined SDL_داخلا_WSCONS
#ضمن "../../core/openbsd/SDL_wscons.h"
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_OPENBSD
ساكن bool moderndri = false;
#وإلا
ساكن bool moderndri = true;
#جيڪڏهن_پورو

ساكن حرف kmsdrm_dri_رستو[16];
ساكن صحيح kmsdrm_dri_pathsize = 0;
ساكن حرف kmsdrm_dri_devname[8];
ساكن صحيح kmsdrm_dri_devnamesize = 0;
ساكن حرف kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#جيڪڏهن_وصف_نه_ٿيل DRM_FORMAT_MOD_VENDOR_NONE
#وصف_ڪريو DRM_FORMAT_MOD_VENDOR_NONE 0
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل DRM_FORMAT_MOD_لڪيري
#وصف_ڪريو DRM_FORMAT_MOD_لڪيري fourcc_mod_ڪوڊ(NONE, 0)
#جيڪڏهن_پورو

ساكن صحيح get_driindex(فراغ)
{
    صحيح موجود = -ENOENT;
    حرف device[حجم(kmsdrm_dri_cardpath)];
    صحيح drm_fd;
    صحيح i;
    صحيح devindex = -1;
    DIR *folder;
    ثابت حرف *hint;
    بنية dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_اشاريو);
    إذا (hint && *hint) {
        حرف *endptr = عدم;
        ثابت صحيح idx = (صحيح)SDL_strtol(hint, &endptr, 10);
        إذا ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            أرجع idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_رستو, حجم(device));
    folder = opendir(device);
    إذا (!folder) {
        SDL_سيٽ_Error("Failed to open directory '%s'", device);
        أرجع -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                حجم(device) - kmsdrm_dri_pathsize);
    طالما((res = readdir(folder)) != عدم && موجود < 0) {
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
                إذا (SDL_KMSDRM_ڀريو_Symbols()) {
                    drm_گهڻائي_Res *resources = KMSDRM_drm_گهڻائي_Get_Resources(drm_fd);
                    إذا (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->ڳڻپ_connectors,
                                     resources->ڳڻپ_encoders,
                                     resources->ڳڻپ_crtcs);

                        إذا (resources->ڳڻپ_connectors > 0 &&
                            resources->ڳڻپ_encoders > 0 &&
                            resources->ڳڻپ_crtcs > 0) {
                            موجود = -ENOENT;
                            لكل (i = 0; i < resources->ڳڻپ_connectors && موجود < 0; i++) {
                                drm_گهڻائي_Connector *conn =
                                    KMSDRM_drm_گهڻائي_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                إذا (!conn) {
                                    استمر;
                                }

                                إذا (conn->connection == DRM_گهڻائي_CONNECTED &&
                                    conn->ڳڻپ_modes) {
                                    bool access_denied = false;
                                    إذا (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_سيٽ_Master(drm_fd);
                                        إذا (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    إذا (!access_denied) {
                                        موجود = devindex;
                                    }
                                }

                                KMSDRM_drm_گهڻائي_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_گهڻائي_Free_Resources(resources);
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

    أرجع موجود;
}

ساكن فراغ Calculate_Refresh_شرح(drm_گهڻائي_گهڻائي_Info *گهڻائي, صحيح *numerator, صحيح *denominator)
{
    *numerator = گهڻائي->clock * 1000;
    *denominator = گهڻائي->htotal * گهڻائي->vtotal;

    إذا (گهڻائي->flags & DRM_گهڻائي_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    إذا (گهڻائي->flags & DRM_گهڻائي_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    إذا (گهڻائي->vscan > 1) {
        *denominator *= گهڻائي->vscan;
    }
}


صحيح جوڙيو_connector_property(drm_گهڻائي_Atomic_Req *req, KMSDRM_connector *conn, ثابت حرف *name, uint64_t قدر)
{
    بنانشان صحيح i;
    صحيح prop_id = 0;

    لكل (i = 0 ; i < conn->props->ڳڻپ_props ; i++) {
        إذا (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سيٽ_Error("no connector property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_گهڻائي_Atomic_جوڙيو_Property(req, conn->connector->connector_id, prop_id, قدر);
}

صحيح جوڙيو_crtc_property(drm_گهڻائي_Atomic_Req *req, KMSDRM_crtc *c, ثابت حرف *name, uint64_t قدر)
{
    بنانشان صحيح i;
    صحيح prop_id = -1;

    لكل (i = 0 ; i < c->props->ڳڻپ_props ; i++) {
        إذا (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سيٽ_Error("no crtc property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_گهڻائي_Atomic_جوڙيو_Property(req, c->crtc->crtc_id, prop_id, قدر);
}

صحيح جوڙيو_plane_property(drm_گهڻائي_Atomic_Req *req, KMSDRM_plane *p, ثابت حرف *name, uint64_t قدر)
{
    بنانشان صحيح i;
    صحيح prop_id = -1;

    لكل (i = 0 ; i < p->props->ڳڻپ_props ; i++) {
        إذا (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            اكسر;
        }
    }

    إذا (prop_id < 0) {
        SDL_سيٽ_Error("no plane property: %s", name);
        أرجع -EINVAL;
    }

    أرجع KMSDRM_drm_گهڻائي_Atomic_جوڙيو_Property(req, p->plane->plane_id, prop_id, قدر);
}

#جيڪڏهن_وصف_ٿيل DEBUG_KMSDRM
ساكن فراغ print_plane_info(SDL_VideoDevice *_this, drm_گهڻائي_Plane_Ptr plane)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->اندروني);
    drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_گهڻائي_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    لكل (صحيح i = 0; i < props->ڳڻپ_props; i++) {
        drm_گهڻائي_Property_Ptr p = KMSDRM_drm_گهڻائي_Get_Property(viddata->drm_fd, props->props[i]);
        إذا ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_قدرون[i];
        }

        KMSDRM_drm_گهڻائي_Free_Property(p);
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
    drm_گهڻائي_Res *resources = KMSDRM_drm_گهڻائي_Get_Resources(viddata->drm_fd);
    إذا (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        لكل (صحيح i = 0; i < resources->ڳڻپ_crtcs; i++) {
            إذا (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                اكسر;
            }
        }
        SDL_Log("%s\n\n", (ثابت حرف *)SDL_Get_اشارو_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_يادگيري_اشارو, ""));
        SDL_CloseIO(io);
    }
}

ساكن فراغ get_planes_info(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->اندروني);

    drm_گهڻائي_Plane_Res_Ptr plane_resources = KMSDRM_drm_گهڻائي_Get_Plane_Resources(viddata->drm_fd);
    إذا (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        أرجع;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->ڳڻپ_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    لكل (uint32_t i = 0; (i < plane_resources->ڳڻپ_planes); i++) {
        ثابت uint32_t plane_id = plane_resources->planes[i];

        drm_گهڻائي_Plane_Ptr plane = KMSDRM_drm_گهڻائي_Get_Plane(viddata->drm_fd, plane_id);
        إذا (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            استمر;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_گهڻائي_Free_Plane(plane);
    }

    KMSDRM_drm_گهڻائي_Free_Plane_Resources(plane_resources);
}
#جيڪڏهن_پورو

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
ساكن صحيح get_plane_id(SDL_VideoDevice *_this, بنانشان صحيح crtc_id, uint32_t plane_type)
{
    drm_گهڻائي_Res *resources = عدم;
    drm_گهڻائي_Plane_Res_Ptr plane_resources = عدم;
    uint32_t i, j;
    بنانشان صحيح crtc_اشاريو = 0;
    صحيح ret = -EINVAL;
    صحيح مليو = 0;

    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->اندروني);

    resources = KMSDRM_drm_گهڻائي_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    لكل (i = 0; i < resources->ڳڻپ_crtcs; i++) {
        إذا (resources->crtcs[i] == crtc_id) {
            crtc_اشاريو = i;
            اكسر;
        }
    }

    plane_resources = KMSDRM_drm_گهڻائي_Get_Plane_Resources(viddata->drm_fd);
    إذا (!plane_resources) {
        أرجع SDL_سيٽ_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    لكل (i = 0; (i < plane_resources->ڳڻپ_planes) && !مليو; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_گهڻائي_Plane_Ptr plane = KMSDRM_drm_گهڻائي_Get_Plane(viddata->drm_fd, plane_id);
        إذا (!plane) {
            استمر;
        }

        /* See if the current CRTC is available for this plane. */
        إذا (plane->possible_crtcs & (1 << crtc_اشاريو)) {

            drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_گهڻائي_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            لكل (j = 0; j < props->ڳڻپ_props; j++) {

                drm_گهڻائي_Property_Ptr p = KMSDRM_drm_گهڻائي_Get_Property(viddata->drm_fd,
                    props->props[j]);

                إذا ((SDL_strcmp(p->name, "type") == 0) && (props->prop_قدرون[j] == plane_type)) {
                    /* found our plane, use that: */
                    مليو = 1;
                }

                KMSDRM_drm_گهڻائي_Free_Property(p);
            }

            KMSDRM_drm_گهڻائي_Free_Object_Properties(props);
        }

        KMSDRM_drm_گهڻائي_Free_Plane(plane);
    }

    KMSDRM_drm_گهڻائي_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_گهڻائي_Free_Resources(resources);

    أرجع ret;
}

/* Setup a plane and it's props. */
bool تياري_plane(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->اندروني);
    bool ret = true;

    *_plane = SDL_calloc(1, حجم(**_plane));
    إذا (!(*_plane)) {
        ret = false;
        اذهب cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    إذا (!plane_id) {
        ret = SDL_سيٽ_Error("Invalid Plane ID");
        اذهب cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_گهڻائي_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    إذا ((*_plane)->plane) {
        بنانشان صحيح i;
        (*_plane)->props = KMSDRM_drm_گهڻائي_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_گهڻائي_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->ڳڻپ_props, حجم(*(*_plane)->props_info));

        إذا ( !((*_plane)->props_info) ) {
            ret = false;
            اذهب cleanup;
        }

        لكل (i = 0; i < (*_plane)->props->ڳڻپ_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_گهڻائي_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
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
            KMSDRM_drm_گهڻائي_Free_Plane((*_plane)->plane);
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
drm_atomic_سيٽ_plane_props(SDL_Display_معلومات *dispdata, بنية KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    إذا (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_گهڻائي_Atomic_Alloc();
    }

    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    جوڙيو_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

صحيح drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_معلومات *viddata = ((SDL_Video_معلومات *)_this->اندروني);
    uint32_t atomic_flags = 0;
    صحيح ret;

    إذا (!blocking) {
        atomic_flags |= DRM_گهڻائي_ATOMIC_NONBLOCK;
    }

    إذا (allow_modeset) {
        atomic_flags |= DRM_گهڻائي_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_گهڻائي_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, عدم);

    إذا (ret) {
        SDL_سيٽ_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#إذا 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#جيڪڏهن_پورو
        اذهب ٻاهريون;
    }

    إذا (dispdata->kms_اندريون_fence_fd != -1) {
        close(dispdata->kms_اندريون_fence_fd);
        dispdata->kms_اندريون_fence_fd = -1;
    }

ٻاهريون:
    KMSDRM_drm_گهڻائي_Atomic_Free(dispdata->atomic_req);
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

ساكن bool KMSDRM_موجود(فراغ)
{
#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_OPENBSD
    بنية utsname nameofsystem;
    مزدوج releaseversion;
#جيڪڏهن_پورو
    صحيح ret = -ENOENT;

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_OPENBSD
    إذا (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        إذا (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#جيڪڏهن_پورو

    إذا (moderndri) {
        SDL_strlcpy(kmsdrm_dri_رستو, "/dev/dri/", حجم(kmsdrm_dri_رستو));
        SDL_strlcpy(kmsdrm_dri_devname, "card", حجم(kmsdrm_dri_devname));
    } وإلا {
        SDL_strlcpy(kmsdrm_dri_رستو, "/dev/", حجم(kmsdrm_dri_رستو));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", حجم(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_رستو);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (فراغ)SDL_snprintf(kmsdrm_dri_cardpath, حجم(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_رستو, kmsdrm_dri_devname);

    ret = get_driindex();
    إذا (ret >= 0) {
        أرجع true;
    }

    أرجع false;
}

ساكن فراغ KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    إذا (device->اندروني) {
        SDL_free(device->اندروني);
        device->اندروني = عدم;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

ساكن SDL_VideoDevice *KMSDRM_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *viddata;
    صحيح devindex;

    إذا (!KMSDRM_موجود()) {
        أرجع عدم;
    }

    devindex = get_driindex();
    إذا (devindex < 0) {
        SDL_سيٽ_Error("devindex (%d) must not be negative.", devindex);
        أرجع عدم;
    }

    إذا (!SDL_KMSDRM_ڀريو_Symbols()) {
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

    device->اندروني = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->سيٽ_Display_گهڻائي = KMSDRM_سيٽ_Display_گهڻائي;
    device->CreateSDLWindow = KMSDRM_Create_دري;
    device->سيٽ_دري_Title = KMSDRM_سيٽ_دري_Title;
    device->سيٽ_دري_Position = KMSDRM_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = KMSDRM_سيٽ_دري_سائيز;
    device->سيٽ_دري_Fullscreen = KMSDRM_سيٽ_دري_Fullscreen;
    device->Show_دري = KMSDRM_Show_دري;
    device->Hide_دري = KMSDRM_Hide_دري;
    device->Raise_دري = KMSDRM_Raise_دري;
    device->Maximize_دري = KMSDRM_Maximize_دري;
    device->Minimize_دري = KMSDRM_Minimize_دري;
    device->Restore_دري = KMSDRM_Restore_دري;
    device->Destroy_دري = KMSDRM_Destroy_دري;
    device->سيٽ_دري_Focusable = KMSDRM_سيٽ_دري_Focusable;

    device->GL_ڀريو_Library = KMSDRM_GLES_ڀريو_Library;
    device->GL_Get_Proc_پتو = KMSDRM_GLES_Get_Proc_پتو;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = KMSDRM_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = KMSDRM_GLES_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = KMSDRM_GLES_مٽا_سٽا_دري;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_سيٽ_Default_Profile_Config = KMSDRM_GLES_سيٽ_Default_Profile_Config;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = KMSDRM_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#جيڪڏهن_پورو

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
        KMSDRM_drm_گهڻائي_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, بنية gbm_bo *bo)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    بنانشان w, h;
    صحيح rc = -1;
    صحيح انگ_planes = 0;
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
    w = KMSDRM_gbm_bo_get_ويڪر(bo);
    h = KMSDRM_gbm_bo_get_اوچائي(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    إذا (KMSDRM_drm_گهڻائي_جوڙيو_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_ڳڻپ &&
        KMSDRM_gbm_bo_get_وٿي &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        انگ_planes = KMSDRM_gbm_bo_get_plane_ڳڻپ(bo);
        لكل (صحيح i = 0; i < انگ_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_وٿي(bo, i);
            modifiers[i] = modifiers[0];
        }

        إذا (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_گهڻائي_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_گهڻائي_جوڙيو_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    إذا (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_گهڻائي_جوڙيو_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    إذا (rc < 0) {
        SDL_free(fb_info);
        أرجع عدم;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (فراغ *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_سيٽ_user_معلومات(bo, fb_info, KMSDRM_FBDestroyCallback);

    أرجع fb_info;
}

ساكن فراغ KMSDRM_FlipHandler(صحيح fd, بنانشان صحيح چوکٺو, بنانشان صحيح sec, بنانشان صحيح usec, فراغ *معلومات)
{
    *((bool *)معلومات) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_دري_معلومات *windata)
{

    SDL_Video_معلومات *viddata = _this->اندروني;
    drmEventContext ev = { 0 };
    بنية pollfd pfd = { 0 };
    صحيح ret;

    ev.نسخو = DRM_EVENT_CONTEXT_نسخو;
    ev.صفحو_flip_handler = KMSDRM_FlipHandler;

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
ساكن drm_گهڻائي_گهڻائي_Info *KMSDRM_Get_Closest_Display_گهڻائي(SDL_VideoDisplay *display, صحيح ويڪر, صحيح اوچائي)
{

    SDL_Display_معلومات *dispdata = display->اندروني;
    drm_گهڻائي_Connector *conn = dispdata->connector.connector;

    SDL_Display_گهڻائي closest;
    drm_گهڻائي_گهڻائي_Info *drm_گهڻائي;

    إذا (SDL_Get_Closest_Fullscreen_Display_گهڻائي(display->id, ويڪر, اوچائي, 0.0f, false, &closest)) {
        ثابت SDL_Display_گهڻائي_معلومات *modedata = closest.اندروني;
        drm_گهڻائي = &conn->modes[modedata->گهڻائي_اشاريو];
        أرجع drm_گهڻائي;
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
    SDL_Video_معلومات *viddata = _this->اندروني;

    إذا (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_سيٽ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_سيٽ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
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
    SDL_Video_معلومات *viddata = _this->اندروني;
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
                KMSDRM_drm_گهڻائي_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = عدم;
            }

            // Free CRTC
            إذا (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_گهڻائي_Free_Crtc(dispdata->crtc.crtc);
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
    bool مليو = false;
    uint64_t prop_قدر = 0;

    drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(drm_fd, output_id, DRM_گهڻائي_OBJECT_CONNECTOR);
    إذا (props) {
        لكل (uint32_t i = 0; !مليو && i < props->ڳڻپ_props; ++i) {
            drm_گهڻائي_Property_Ptr prop = KMSDRM_drm_گهڻائي_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_قدر = props->prop_قدرون[i];
                    مليو = true;
                }
                KMSDRM_drm_گهڻائي_Free_Property(prop);
            }
        }
        KMSDRM_drm_گهڻائي_Free_Object_Properties(props);
    }
    إذا (مليو) {
        أرجع prop_قدر ? true : false;
    }
    أرجع false;
}

ساكن bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool مليو = false;
    drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(drm_fd, crtc_id, DRM_گهڻائي_OBJECT_CRTC);
    إذا (props) {
        لكل (uint32_t i = 0; !مليو && i < props->ڳڻپ_props; ++i) {
            drm_گهڻائي_Property_Ptr prop = KMSDRM_drm_گهڻائي_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    مليو = true;
                }
                KMSDRM_drm_گهڻائي_Free_Property(prop);
            }
        }
        KMSDRM_drm_گهڻائي_Free_Object_Properties(props);
    }
    أرجع مليو;
}

ساكن فراغ KMSDRM_Crtc_سيٽ_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    إذا (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        أرجع;
    }

    KMSDRM_drm_گهڻائي_Object_سيٽ_Property(drm_fd, crtc_id, DRM_گهڻائي_OBJECT_CRTC, vrr_prop_id, enabled);
}

ساكن bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool مليو = false;
    uint64_t prop_قدر = 0;

    إذا (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        أرجع false;
    }

    drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(drm_fd, crtc_id, DRM_گهڻائي_OBJECT_CRTC);
    إذا (props) {
        لكل (uint32_t i = 0; !مليو && i < props->ڳڻپ_props; ++i) {
            drm_گهڻائي_Property_Ptr prop = KMSDRM_drm_گهڻائي_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (prop->prop_id == vrr_prop_id) {
                    prop_قدر = props->prop_قدرون[i];
                    مليو = true;
                }
                KMSDRM_drm_گهڻائي_Free_Property(prop);
            }
        }
        KMSDRM_drm_گهڻائي_Free_Object_Properties(props);
    }
    إذا (مليو) {
        أرجع prop_قدر ? true : false;
    }
    أرجع false;
}

ساكن صحيح KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool مليو = false;
    صحيح orientation = 0;

    drm_گهڻائي_Object_Properties_Ptr props = KMSDRM_drm_گهڻائي_Object_Get_Properties(drm_fd, crtc_id, DRM_گهڻائي_OBJECT_CONNECTOR);
    إذا (props) {
        لكل (uint32_t i = 0; !مليو && i < props->ڳڻپ_props; ++i) {
            drm_گهڻائي_Property_Ptr prop = KMSDRM_drm_گهڻائي_Get_Property(drm_fd, props->props[i]);
            إذا (prop) {
                إذا (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_گهڻائي_PROP_ENUM)) {
                    إذا (prop->ڳڻپ_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        إذا (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } وإلا إذا (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } وإلا إذا (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    مليو = true;
                }
                KMSDRM_drm_گهڻائي_Free_Property(prop);
            }
        }
        KMSDRM_drm_گهڻائي_Free_Object_Properties(props);
    }
    أرجع orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
ساكن فراغ KMSDRM_جوڙيو_Display(SDL_VideoDevice *_this, drm_گهڻائي_Connector *conn, drm_گهڻائي_Res *resources)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_Display_معلومات *dispdata = عدم;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_گهڻائي_معلومات *modedata = عدم;
    drm_گهڻائي_Encoder *encoder = عدم;
    drm_گهڻائي_Crtc *crtc = عدم;
    ثابت حرف *connector_type = عدم;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    حرف name_fmt[64];
    صحيح orientation;
    صحيح گهڻائي_اشاريو;
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
    dispdata->kms_اندريون_fence_fd = -1;
    dispdata->kms_ٻاهريون_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    لكل (i = 0; i < resources->ڳڻپ_encoders; i++) {
        encoder = KMSDRM_drm_گهڻائي_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        إذا (!encoder) {
            استمر;
        }

        إذا (encoder->encoder_id == conn->encoder_id) {
            اكسر;
        }

        KMSDRM_drm_گهڻائي_Free_Encoder(encoder);
        encoder = عدم;
    }

    إذا (!encoder) {
        // No encoder was connected, find the first supported one
        لكل (i = 0; i < resources->ڳڻپ_encoders; i++) {
            encoder = KMSDRM_drm_گهڻائي_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            إذا (!encoder) {
                استمر;
            }

            لكل (j = 0; j < conn->ڳڻپ_encoders; j++) {
                إذا (conn->encoders[j] == encoder->encoder_id) {
                    اكسر;
                }
            }

            إذا (j != conn->ڳڻپ_encoders) {
                اكسر;
            }

            KMSDRM_drm_گهڻائي_Free_Encoder(encoder);
            encoder = عدم;
        }
    }

    إذا (!encoder) {
        ret = SDL_سيٽ_Error("No connected encoder found for connector.");
        اذهب cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_گهڻائي_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    إذا (!crtc) {
        لكل (i = 0; i < resources->ڳڻپ_crtcs; i++) {
            إذا (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_گهڻائي_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                اكسر;
            }
        }
    }

    إذا (!crtc) {
        ret = SDL_سيٽ_Error("No CRTC found for connector.");
        اذهب cleanup;
    }

    // Find the index of the mode attached to this CRTC
    گهڻائي_اشاريو = -1;

    لكل (i = 0; i < conn->ڳڻپ_modes; i++) {
        drm_گهڻائي_گهڻائي_Info *گهڻائي = &conn->modes[i];

        إذا (!SDL_memcmp(گهڻائي, &crtc->گهڻائي, حجم(crtc->گهڻائي))) {
            گهڻائي_اشاريو = i;
            اكسر;
        }
    }

    إذا (گهڻائي_اشاريو == -1) {
        صحيح current_area, سڀ_کان_وڏو_area = 0;

        // Find the preferred mode or the highest resolution mode
        لكل (i = 0; i < conn->ڳڻپ_modes; i++) {
            drm_گهڻائي_گهڻائي_Info *گهڻائي = &conn->modes[i];

            إذا (گهڻائي->type & DRM_گهڻائي_TYPE_PREFERRED) {
                گهڻائي_اشاريو = i;
                اكسر;
            }

            current_area = گهڻائي->hdisplay * گهڻائي->vdisplay;
            إذا (current_area > سڀ_کان_وڏو_area) {
                گهڻائي_اشاريو = i;
                سڀ_کان_وڏو_area = current_area;
            }
        }
        إذا (گهڻائي_اشاريو != -1) {
            crtc->گهڻائي = conn->modes[گهڻائي_اشاريو];
        }
    }

    إذا (گهڻائي_اشاريو == -1) {
        ret = SDL_سيٽ_Error("Failed to find index of mode attached to the CRTC.");
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
    dispdata->گهڻائي = crtc->گهڻائي;
    dispdata->original_گهڻائي = crtc->گهڻائي;
    dispdata->fullscreen_گهڻائي = crtc->گهڻائي;

    إذا (dispdata->گهڻائي.hdisplay == 0 || dispdata->گهڻائي.vdisplay == 0) {
        ret = SDL_سيٽ_Error("Couldn't get a valid connector videomode.");
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
        KMSDRM_Crtc_سيٽ_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    إذا (KMSDRM_drm_گهڻائي_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_گهڻائي_Get_Connector_Type_Name(conn->connector_type);
        إذا (connector_type == عدم) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, حجم(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_گهڻائي_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_گهڻائي_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->ڳڻپ_props, حجم(*dispdata->crtc.props_info));
    إذا (!dispdata->crtc.props_info) {
        ret = false;
        اذهب cleanup;
    }

    لكل (i = 0; i < dispdata->crtc.props->ڳڻپ_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_گهڻائي_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_گهڻائي_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_گهڻائي_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->ڳڻپ_props, حجم(*dispdata->connector.props_info));
    إذا (!dispdata->connector.props_info) {
        ret = false;
        اذهب cleanup;
    }

    لكل (i = 0; i < dispdata->connector.props->ڳڻپ_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_گهڻائي_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, حجم(SDL_Display_گهڻائي_معلومات));

    إذا (!modedata) {
        ret = -1;
        اذهب cleanup;
    }

    modedata->گهڻائي_اشاريو = گهڻائي_اشاريو;

    display.اندروني = dispdata;
    display.desktop_گهڻائي.w = dispdata->گهڻائي.hdisplay;
    display.desktop_گهڻائي.h = dispdata->گهڻائي.vdisplay;
    Calculate_Refresh_شرح(&dispdata->گهڻائي, &display.desktop_گهڻائي.refresh_شرح_numerator, &display.desktop_گهڻائي.refresh_شرح_denominator);
    display.desktop_گهڻائي.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_گهڻائي.اندروني = modedata;
    إذا (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_جوڙيو_Video_Display(&display, false);
    إذا (!display_id) {
        ret = -1;
        اذهب cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_سيٽ_عدد_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_عدد, orientation);

#جيڪڏهن_وصف_ٿيل DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#جيڪڏهن_پورو

cleanup:
    إذا (encoder) {
        KMSDRM_drm_گهڻائي_Free_Encoder(encoder);
    }
    إذا (ret) {
        // Error (complete) cleanup
        إذا (dispdata) {
            إذا (dispdata->connector.connector) {
                KMSDRM_drm_گهڻائي_Free_Connector(dispdata->connector.connector);
            }
            إذا (dispdata->crtc.crtc) {
                KMSDRM_drm_گهڻائي_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

ساكن فراغ KMSDRM_ترتيب_ڏيو_Displays(SDL_VideoDevice *_this)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ترجيح);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(حجم(SDL_VideoDisplay *) * _this->انگ_displays);

        إذا (str && sorted_list) {
            صحيح sorted_اشاريو = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    إذا (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_اشاريو++] = d;
                        _this->displays[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
                إذا (_this->displays[i]) {
                    sorted_list[sorted_اشاريو++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, حجم(SDL_VideoDisplay *) * _this->انگ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن bool سيٽ_client_atomic_caps(صحيح fd)
{
    إذا (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        أرجع false;  // emergency escape hatch.
    } وإلا إذا (KMSDRM_drm_سيٽ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        أرجع false;  // no atomic modesetting support.
    } وإلا إذا (KMSDRM_drm_سيٽ_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_سيٽ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
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
    SDL_Video_معلومات *viddata = _this->اندروني;
    drm_گهڻائي_Res *resources = عدم;
    uint64_t async_pageflip = 0;
    صحيح i;
    bool نتيجو = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (فراغ)SDL_snprintf(viddata->devpath, حجم(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    إذا (viddata->drm_fd < 0) {
        نتيجو = SDL_سيٽ_Error("Could not open %s", viddata->devpath);
        اذهب cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = سيٽ_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_گهڻائي_Get_Resources(viddata->drm_fd);
    إذا (!resources) {
        نتيجو = SDL_سيٽ_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        اذهب cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    لكل (i = 0; i < resources->ڳڻپ_connectors; i++) {
        drm_گهڻائي_Connector *conn = KMSDRM_drm_گهڻائي_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        إذا (!conn) {
            استمر;
        }

        إذا (conn->connection == DRM_گهڻائي_CONNECTED && conn->ڳڻپ_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_جوڙيو_Display(_this, conn, resources);
        } وإلا {
            // If it's not, free it now.
            KMSDRM_drm_گهڻائي_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    إذا (SDL_GetPrimaryDisplay() == 0) {
        نتيجو = SDL_سيٽ_Error("No connected displays found.");
        اذهب cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_ترتيب_ڏيو_Displays(_this);

    // Determine if video hardware supports async pageflips.
    إذا (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_صفحو_FLIP, &async_pageflip) != 0) {
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
        KMSDRM_drm_گهڻائي_Free_Resources(resources);
    }
    إذا (!نتيجو) {
        إذا (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    أرجع نتيجو;
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
    SDL_Video_معلومات *viddata = _this->اندروني;
    bool نتيجو = true;

    // Reopen the FD if we weren't able to drop master on the original one
    إذا (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        إذا (viddata->drm_fd < 0) {
            أرجع SDL_سيٽ_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = سيٽ_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_سيٽ_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    إذا (!viddata->gbm_dev) {
        نتيجو = SDL_سيٽ_Error("Couldn't create gbm device.");
    } وإلا {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        نتيجو = تياري_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        إذا (!نتيجو) {
            SDL_سيٽ_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    أرجع نتيجو;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
ساكن فراغ KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_معلومات *dispdata)
{
    SDL_Video_معلومات *viddata = _this->اندروني;

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

ساكن فراغ KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_دري_معلومات *windata = دري->اندروني;
    SDL_Display_معلومات *dispdata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
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
        جوڙيو_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        جوڙيو_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        جوڙيو_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_صفحو_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_سيٽ_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_گهڻائي_سيٽ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_گهڻائي);

        /* Issue atomic commit that is blocking and allows modesetting. */
        إذا (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_سيٽ_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        إذا (ret && (dispdata->crtc->گهڻائي_valid == 0)) {
            ret = KMSDRM_drm_گهڻائي_سيٽ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_گهڻائي);
        }
#جيڪڏهن_پورو

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
        plane_info.src_w = dispdata->original_گهڻائي.hdisplay;
        plane_info.src_h = dispdata->original_گهڻائي.vdisplay;
        plane_info.crtc_w = dispdata->original_گهڻائي.hdisplay;
        plane_info.crtc_h = dispdata->original_گهڻائي.vdisplay;

        drm_atomic_سيٽ_plane_props(dispdata, &plane_info);

        إذا (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_سيٽ_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#جيڪڏهن_پورو

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_گهڻائي_سيٽ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_گهڻائي);

    // If we failed to set the original mode, try to set the connector preferred mode.
    إذا (ret && (dispdata->crtc.crtc->گهڻائي_valid == 0)) {
        ret = KMSDRM_drm_گهڻائي_سيٽ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_گهڻائي);
    }

    إذا (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    إذا (windata->bo) {
        إذا (windata->bo != windata->ايندڙ_bo) {
            KMSDRM_gbm_surface_release_بفر(windata->gs, windata->bo);
        }
        windata->bo = عدم;
    }

    إذا (windata->ايندڙ_bo) {
        KMSDRM_gbm_surface_release_بفر(windata->gs, windata->ايندڙ_bo);
        windata->ايندڙ_bo = عدم;
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

ساكن فراغ KMSDRM_Get_گهڻائي_منزل_سيٽ(SDL_دري *دري, drm_گهڻائي_گهڻائي_Info *ٻاهريون_گهڻائي)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_دري(دري);
    SDL_Display_معلومات *dispdata = display->اندروني;

    إذا (دري->fullscreen_exclusive) {
        *ٻاهريون_گهڻائي = dispdata->fullscreen_گهڻائي;
    } وإلا {
        drm_گهڻائي_گهڻائي_Info *گهڻائي = KMSDRM_Get_Closest_Display_گهڻائي(display, دري->windowed.w, دري->windowed.h);
        إذا (گهڻائي) {
            *ٻاهريون_گهڻائي = *گهڻائي;
        } وإلا {
            *ٻاهريون_گهڻائي = dispdata->original_گهڻائي;
        }
    }
}

ساكن فراغ KMSDRM_DirtySurfaces(SDL_دري *دري)
{
    SDL_دري_معلومات *windata = دري->اندروني;
    drm_گهڻائي_گهڻائي_Info گهڻائي;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_گهڻائي_منزل_سيٽ(دري, &گهڻائي);
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, گهڻائي.hdisplay, گهڻائي.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_دري *دري)
{
    ساكن ثابت بنية { uint32_t fmt; ثابت حرف *name; صحيح r; صحيح g; صحيح b; صحيح a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #وصف_ڪريو FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #وصف_رد FMT
    };

    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_دري_معلومات *windata = دري->اندروني;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_دري(دري);
    SDL_Display_معلومات *dispdata = display->اندروني;
    EGLContext egl_context;
    bool نتيجو = false;

    // If the current window already has surfaces, destroy them before creating other.
    إذا (windata->gs) {
        KMSDRM_DestroySurfaces(_this, دري);
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
        KMSDRM_Get_گهڻائي_منزل_سيٽ(دري, &dispdata->گهڻائي);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->گهڻائي.hdisplay, dispdata->گهڻائي.vdisplay, surface_fmt, surface_flags);
        إذا (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->گهڻائي.hdisplay, dispdata->گهڻائي.vdisplay, surface_fmt, 0);
        }
        إذا (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_سيٽ_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            استمر;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_سيٽ_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)windata->gs);
        إذا (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = عدم;
            استمر;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        نتيجو = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        إذا (!نتيجو) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            استمر;
        }

        _this->gl_config.red_سائيز = gbm_formats[i].r;
        _this->gl_config.green_سائيز = gbm_formats[i].g;
        _this->gl_config.blue_سائيز = gbm_formats[i].b;
        _this->gl_config.alpha_سائيز = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        نتيجو = true;

        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, dispdata->گهڻائي.hdisplay, dispdata->گهڻائي.vdisplay);

        اكسر;
    }

    SDL_assert(نتيجو || (windata->gs == عدم));

    إذا (!نتيجو) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        إذا (!tried_setting_format) {   // make sure there's an error string set.
            SDL_سيٽ_Error("Could not find any supported GBM surface format.");
        }
    }

    أرجع نتيجو;
}

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
ساكن فراغ KMSDRM_ReleaseVT(فراغ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_معلومات *viddata = _this->اندروني;
    صحيح i;

    لكل (i = 0; i < viddata->انگ_windows; i++) {
        SDL_دري *دري = viddata->windows[i];
        إذا (!(دري->flags & SDL_دري_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, دري);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

ساكن فراغ KMSDRM_AcquireVT(فراغ *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_معلومات *viddata = _this->اندروني;
    صحيح i;

    KMSDRM_drm_سيٽ_Master(viddata->drm_fd);
    لكل (i = 0; i < viddata->انگ_windows; i++) {
        SDL_دري *دري = viddata->windows[i];
        إذا (!(دري->flags & SDL_دري_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, دري);
        }
    }
}
#جيڪڏهن_پورو // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool نتيجو = true;

    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    إذا (!KMSDRM_InitDisplays(_this)) {
        نتيجو = SDL_سيٽ_Error("error getting KMSDRM displays information");
    }

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_سيٽ_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#وإلاإذا defined(SDL_داخلا_WSCONS)
    SDL_WSCONS_Init();
#جيڪڏهن_پورو

    viddata->video_init = true;

    أرجع نتيجو;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
فراغ KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *viddata = _this->اندروني;

    KMSDRM_DeinitDisplays(_this);

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    SDL_EVDEV_سيٽ_VTSwitch_Callbacks(عدم, عدم, عدم, عدم);
    SDL_EVDEV_Quit();
#وإلاإذا defined(SDL_داخلا_WSCONS)
    SDL_WSCONS_Quit();
#جيڪڏهن_پورو

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = عدم;
    viddata->max_windows = 0;
    viddata->انگ_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_معلومات *dispdata = display->اندروني;
    drm_گهڻائي_Connector *conn = dispdata->connector.connector;
    SDL_Display_گهڻائي گهڻائي;
    صحيح i;

    لكل (i = 0; i < conn->ڳڻپ_modes; i++) {
        SDL_Display_گهڻائي_معلومات *modedata = SDL_calloc(1, حجم(SDL_Display_گهڻائي_معلومات));

        إذا (modedata) {
            modedata->گهڻائي_اشاريو = i;
        }

        SDL_zero(گهڻائي);
        گهڻائي.w = conn->modes[i].hdisplay;
        گهڻائي.h = conn->modes[i].vdisplay;
        Calculate_Refresh_شرح(&conn->modes[i], &گهڻائي.refresh_شرح_numerator, &گهڻائي.refresh_شرح_denominator);
        گهڻائي.format = SDL_PIXELFORMAT_ARGB8888;
        گهڻائي.اندروني = modedata;

        إذا (!SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي)) {
            SDL_free(modedata);
        }
    }
    أرجع true;
}

bool KMSDRM_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_Display_معلومات *dispdata = display->اندروني;
    SDL_Display_گهڻائي_معلومات *modedata = گهڻائي->اندروني;
    drm_گهڻائي_Connector *conn = dispdata->connector.connector;
    صحيح i;

    // Don't do anything if we are in Vulkan mode.
    إذا (viddata->vulkan_گهڻائي) {
        أرجع true;
    }

    إذا (!modedata) {
        أرجع SDL_سيٽ_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_گهڻائي = conn->modes[modedata->گهڻائي_اشاريو];

    لكل (i = 0; i < viddata->انگ_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    أرجع true;
}

فراغ KMSDRM_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *windata = دري->اندروني;
    SDL_Display_معلومات *dispdata = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    SDL_Video_معلومات *viddata;
    bool is_vulkan = دري->flags & SDL_دري_VULKAN; // Is this a VK window?
    بنانشان صحيح i, j;

    إذا (!windata) {
        أرجع;
    }

    // restore vrr state
    KMSDRM_Crtc_سيٽ_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    إذا (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_دري(دري));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, دري);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        إذا (viddata->انگ_windows <= 1) {

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
        إذا (viddata->vulkan_گهڻائي) {
            viddata->vulkan_گهڻائي = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    لكل (i = 0; i < viddata->انگ_windows; i++) {
        إذا (viddata->windows[i] == دري) {
            viddata->انگ_windows--;

            لكل (j = i; j < viddata->انگ_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            اكسر;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(دري->اندروني);
    دري->اندروني = عدم;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *windata = عدم;
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_دري(دري);
    SDL_Display_معلومات *dispdata = display->اندروني;
    bool is_vulkan = دري->flags & SDL_دري_VULKAN; // Is this a VK window?
    bool vulkan_گهڻائي = viddata->vulkan_گهڻائي;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_گهڻائي_گهڻائي_Info *گهڻائي;
    bool نتيجو = true;

    // Allocate window internal data
    windata = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (!windata) {
        أرجع false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    دري->اندروني = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_بفر = false;
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        windata->double_بفر = true;
    }

    إذا (!is_vulkan && !vulkan_گهڻائي) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        دري->flags |= SDL_دري_OPENGL;

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
                أرجع SDL_سيٽ_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        إذا (!_this->egl_معلومات) {
            egl_display = (NativeDisplayType)_this->اندروني->gbm_dev;
            إذا (!SDL_EGL_ڀريو_Library(_this, عدم, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_نسخو = 2;
                _this->gl_config.minor_نسخو = 0;
                إذا (!SDL_EGL_ڀريو_Library(_this, عدم, egl_display)) {
                    أرجع SDL_سيٽ_Error("Can't load EGL/GL library on window creation.");
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
        گهڻائي = KMSDRM_Get_Closest_Display_گهڻائي(display, دري->windowed.w, دري->windowed.h);

        إذا (گهڻائي) {
            dispdata->fullscreen_گهڻائي = *گهڻائي;
        } وإلا {
            dispdata->fullscreen_گهڻائي = dispdata->original_گهڻائي;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        إذا (!KMSDRM_CreateSurfaces(_this, دري)) {
            أرجع false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    إذا (viddata->انگ_windows >= viddata->max_windows) {
        بنانشان صحيح new_max_windows = viddata->max_windows + 1;
        SDL_دري **new_windows = (SDL_دري **)SDL_realloc(viddata->windows,
                                                              new_max_windows * حجم(SDL_دري *));
        إذا (!new_windows) {
            أرجع false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->انگ_windows++] = دري;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_گهڻائي = is_vulkan;

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_KMSDRM_DEVICE_اشاريو_عدد, viddata->devindex);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_KMSDRM_DRM_FD_عدد, viddata->drm_fd);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_KMSDRM_GBM_DEVICE_اشارو, viddata->gbm_dev);

    إذا ((دري->flags & SDL_دري_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_سيٽ_Mouse_Focus(دري);
        SDL_سيٽ_Keyboard_Focus(دري);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_دري(دري), &display_bounds);
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    أرجع نتيجو;
}

فراغ KMSDRM_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
bool KMSDRM_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    أرجع SDL_Unsupported();
}
فراغ KMSDRM_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    إذا (!viddata->vulkan_گهڻائي) {
        KMSDRM_DirtySurfaces(دري);
    }
}
SDL_Fullscreen_نتيجو KMSDRM_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    إذا (!viddata->vulkan_گهڻائي) {
        KMSDRM_DirtySurfaces(دري);
    }
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}
فراغ KMSDRM_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ KMSDRM_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ KMSDRM_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ KMSDRM_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ KMSDRM_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ KMSDRM_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
bool KMSDRM_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable)
{
    أرجع true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_KMSDRM
