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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#অন্তর্ভাৱ "../SDL_egl_c.h"

// SDL internals
#অন্তর্ভাৱ "../../events/SDL_events_c.h"
#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"

#ifdef SDL_প্ৰবেশ_LINUXEV
#অন্তর্ভাৱ "../../core/linux/SDL_evdev.h"
#নোচেদ্যদি defined SDL_প্ৰবেশ_WSCONS
#অন্তর্ভাৱ "../../core/openbsd/SDL_wscons.h"
#endif

// KMS/DRM declarations
#অন্তর্ভাৱ "SDL_kmsdrmdyn.h"
#অন্তর্ভাৱ "SDL_kmsdrmevents.h"
#অন্তর্ভাৱ "SDL_kmsdrmmouse.h"
#অন্তর্ভাৱ "SDL_kmsdrmvideo.h"
#অন্তর্ভাৱ "SDL_kmsdrmopengles.h"
#অন্তর্ভাৱ "SDL_kmsdrmvulkan.h"
#অন্তর্ভাৱ <dirent.h>
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <poll.h>
#অন্তর্ভাৱ <sys/param.h>
#অন্তর্ভাৱ <sys/stat.h>
#অন্তর্ভাৱ <sys/utsname.h>

#ifdef SDL_PLATFORM_OPENBSD
স্থির bool moderndri = false;
#অন্যথা
স্থির bool moderndri = true;
#endif

স্থির ৱর্ণ kmsdrm_dri_path[16];
স্থির পূর্ণাঙ্ক kmsdrm_dri_pathsize = 0;
স্থির ৱর্ণ kmsdrm_dri_devname[8];
স্থির পূর্ণাঙ্ক kmsdrm_dri_devnamesize = 0;
স্থির ৱর্ণ kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#ifndef DRM_FORMAT_MOD_VENDOR_NONE
#define DRM_FORMAT_MOD_VENDOR_NONE 0
#endif
#ifndef DRM_FORMAT_MOD_LINEAR
#define DRM_FORMAT_MOD_LINEAR fourcc_mod_code(NONE, 0)
#endif

স্থির পূর্ণাঙ্ক get_driindex(শূন্য)
{
    পূর্ণাঙ্ক available = -ENOENT;
    ৱর্ণ device[পরিমাণ(kmsdrm_dri_cardpath)];
    পূর্ণাঙ্ক drm_fd;
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক devindex = -1;
    DIR *folder;
    ধ্রুৱ ৱর্ণ *hint;
    সংরচনা dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_INDEX);
    যদি (hint && *hint) {
        ৱর্ণ *endptr = রিক্ত;
        ধ্রুৱ পূর্ণাঙ্ক idx = (পূর্ণাঙ্ক)SDL_strtol(hint, &endptr, 10);
        যদি ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            ঘূৰাই idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_path, পরিমাণ(device));
    folder = opendir(device);
    যদি (!folder) {
        SDL_SetError("Failed to open directory '%s'", device);
        ঘূৰাই -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                পরিমাণ(device) - kmsdrm_dri_pathsize);
    যেতিয়ালৈ((res = readdir(folder)) != রিক্ত && available < 0) {
        যদি (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        পরিমাণ(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            যদি (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                যদি (SDL_KMSDRM_LoadSymbols()) {
                    drmModeRes *resources = KMSDRM_drmModeGetResources(drm_fd);
                    যদি (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->গুনতি_connectors,
                                     resources->গুনতি_encoders,
                                     resources->গুনতি_crtcs);

                        যদি (resources->গুনতি_connectors > 0 &&
                            resources->গুনতি_encoders > 0 &&
                            resources->গুনতি_crtcs > 0) {
                            available = -ENOENT;
                            বাবে (i = 0; i < resources->গুনতি_connectors && available < 0; i++) {
                                drmModeConnector *conn =
                                    KMSDRM_drmModeGetConnector(
                                        drm_fd, resources->connectors[i]);

                                যদি (!conn) {
                                    অনুৱর্ত;
                                }

                                যদি (conn->connection == DRM_MODE_CONNECTED &&
                                    conn->গুনতি_modes) {
                                    bool access_denied = false;
                                    যদি (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drmSetMaster(drm_fd);
                                        যদি (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    যদি (!access_denied) {
                                        available = devindex;
                                    }
                                }

                                KMSDRM_drmModeFreeConnector(conn);
                            }
                        }
                        KMSDRM_drmModeFreeResources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } অন্যথা {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    ঘূৰাই available;
}

স্থির শূন্য CalculateRefreshRate(drmModeModeInfo *mode, পূর্ণাঙ্ক *numerator, পূর্ণাঙ্ক *denominator)
{
    *numerator = mode->clock * 1000;
    *denominator = mode->htotal * mode->vtotal;

    যদি (mode->flags & DRM_MODE_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    যদি (mode->flags & DRM_MODE_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    যদি (mode->vscan > 1) {
        *denominator *= mode->vscan;
    }
}


পূর্ণাঙ্ক add_connector_property(drmModeAtomicReq *req, KMSDRM_connector *conn, ধ্রুৱ ৱর্ণ *name, uint64_t মান)
{
    unsigned পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক prop_id = 0;

    বাবে (i = 0 ; i < conn->props->গুনতি_props ; i++) {
        যদি (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            ভঙ্গ;
        }
    }

    যদি (prop_id < 0) {
        SDL_SetError("no connector property: %s", name);
        ঘূৰাই -EINVAL;
    }

    ঘূৰাই KMSDRM_drmModeAtomicAddProperty(req, conn->connector->connector_id, prop_id, মান);
}

পূর্ণাঙ্ক add_crtc_property(drmModeAtomicReq *req, KMSDRM_crtc *c, ধ্রুৱ ৱর্ণ *name, uint64_t মান)
{
    unsigned পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক prop_id = -1;

    বাবে (i = 0 ; i < c->props->গুনতি_props ; i++) {
        যদি (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            ভঙ্গ;
        }
    }

    যদি (prop_id < 0) {
        SDL_SetError("no crtc property: %s", name);
        ঘূৰাই -EINVAL;
    }

    ঘূৰাই KMSDRM_drmModeAtomicAddProperty(req, c->crtc->crtc_id, prop_id, মান);
}

পূর্ণাঙ্ক add_plane_property(drmModeAtomicReq *req, KMSDRM_plane *p, ধ্রুৱ ৱর্ণ *name, uint64_t মান)
{
    unsigned পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক prop_id = -1;

    বাবে (i = 0 ; i < p->props->গুনতি_props ; i++) {
        যদি (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            ভঙ্গ;
        }
    }

    যদি (prop_id < 0) {
        SDL_SetError("no plane property: %s", name);
        ঘূৰাই -EINVAL;
    }

    ঘূৰাই KMSDRM_drmModeAtomicAddProperty(req, p->plane->plane_id, prop_id, মান);
}

#ifdef DEBUG_KMSDRM
স্থির শূন্য print_plane_info(SDL_VideoDevice *_this, drmModePlanePtr plane)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd,
        plane->plane_id, DRM_MODE_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    বাবে (পূর্ণাঙ্ক i = 0; i < props->গুনতি_props; i++) {
        drmModePropertyPtr p = KMSDRM_drmModeGetProperty(viddata->drm_fd, props->props[i]);
        যদি ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_মানসমূহ[i];
        }

        KMSDRM_drmModeFreeProperty(p);
    }

    ৱর্ণ *plane_type = "unknown";
    ৱিকল্প (type) {
        পক্ষ DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            ভঙ্গ;

        পক্ষ DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            ভঙ্গ;

        পক্ষ DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            ভঙ্গ;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drmModeRes *resources = KMSDRM_drmModeGetResources(viddata->drm_fd);
    যদি (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        বাবে (পূর্ণাঙ্ক i = 0; i < resources->গুনতি_crtcs; i++) {
            যদি (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                ভঙ্গ;
            }
        }
        SDL_Log("%s\n\n", (ধ্রুৱ ৱর্ণ *)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ""));
        SDL_CloseIO(io);
    }
}

স্থির শূন্য get_planes_info(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);

    drmModePlaneResPtr plane_resources = KMSDRM_drmModeGetPlaneResources(viddata->drm_fd);
    যদি (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        ঘূৰাই;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->গুনতি_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    বাবে (uint32_t i = 0; (i < plane_resources->গুনতি_planes); i++) {
        ধ্রুৱ uint32_t plane_id = plane_resources->planes[i];

        drmModePlanePtr plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);
        যদি (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            অনুৱর্ত;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drmModeFreePlane(plane);
    }

    KMSDRM_drmModeFreePlaneResources(plane_resources);
}
#endif

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
স্থির পূর্ণাঙ্ক get_plane_id(SDL_VideoDevice *_this, unsigned পূর্ণাঙ্ক crtc_id, uint32_t plane_type)
{
    drmModeRes *resources = রিক্ত;
    drmModePlaneResPtr plane_resources = রিক্ত;
    uint32_t i, j;
    unsigned পূর্ণাঙ্ক crtc_index = 0;
    পূর্ণাঙ্ক ret = -EINVAL;
    পূর্ণাঙ্ক found = 0;

    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);

    resources = KMSDRM_drmModeGetResources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    বাবে (i = 0; i < resources->গুনতি_crtcs; i++) {
        যদি (resources->crtcs[i] == crtc_id) {
            crtc_index = i;
            ভঙ্গ;
        }
    }

    plane_resources = KMSDRM_drmModeGetPlaneResources(viddata->drm_fd);
    যদি (!plane_resources) {
        ঘূৰাই SDL_SetError("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    বাবে (i = 0; (i < plane_resources->গুনতি_planes) && !found; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drmModePlanePtr plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);
        যদি (!plane) {
            অনুৱর্ত;
        }

        /* See if the current CRTC is available for this plane. */
        যদি (plane->possible_crtcs & (1 << crtc_index)) {

            drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(
                viddata->drm_fd, plane_id, DRM_MODE_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            বাবে (j = 0; j < props->গুনতি_props; j++) {

                drmModePropertyPtr p = KMSDRM_drmModeGetProperty(viddata->drm_fd,
                    props->props[j]);

                যদি ((SDL_strcmp(p->name, "type") == 0) && (props->prop_মানসমূহ[j] == plane_type)) {
                    /* found our plane, use that: */
                    found = 1;
                }

                KMSDRM_drmModeFreeProperty(p);
            }

            KMSDRM_drmModeFreeObjectProperties(props);
        }

        KMSDRM_drmModeFreePlane(plane);
    }

    KMSDRM_drmModeFreePlaneResources(plane_resources);
    KMSDRM_drmModeFreeResources(resources);

    ঘূৰাই ret;
}

/* Setup a plane and it's props. */
bool setup_plane(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    bool ret = true;

    *_plane = SDL_calloc(1, পরিমাণ(**_plane));
    যদি (!(*_plane)) {
        ret = false;
        গচ্ছ cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    যদি (!plane_id) {
        ret = SDL_SetError("Invalid Plane ID");
        গচ্ছ cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    যদি ((*_plane)->plane) {
        unsigned পূর্ণাঙ্ক i;
        (*_plane)->props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_MODE_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->গুনতি_props, পরিমাণ(*(*_plane)->props_info));

        যদি ( !((*_plane)->props_info) ) {
            ret = false;
            গচ্ছ cleanup;
        }

        বাবে (i = 0; i < (*_plane)->props->গুনতি_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    যদি (!ret) {
        যদি (*_plane) {
            SDL_free(*_plane);
            *_plane = রিক্ত;
        }
    }
    ঘূৰাই ret;
}

/* Free a plane and it's props. */
শূন্য free_plane(KMSDRM_plane **_plane)
{
    যদি (*_plane) {
        যদি ((*_plane)->plane) {
            KMSDRM_drmModeFreePlane((*_plane)->plane);
            (*_plane)->plane = রিক্ত;
        }
        যদি ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = রিক্ত;
        }
        SDL_free(*_plane);
        *_plane = রিক্ত;
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
শূন্য
drm_atomic_set_plane_props(SDL_DisplayData *dispdata, সংরচনা KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    যদি (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drmModeAtomicAlloc();
    }

    add_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    add_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    add_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    add_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    add_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    add_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    add_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    add_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    add_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    add_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

পূর্ণাঙ্ক drm_atomic_commit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, bool blocking, bool allow_modeset)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    uint32_t atomic_flags = 0;
    পূর্ণাঙ্ক ret;

    যদি (!blocking) {
        atomic_flags |= DRM_MODE_ATOMIC_NONBLOCK;
    }

    যদি (allow_modeset) {
        atomic_flags |= DRM_MODE_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drmModeAtomicCommit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, রিক্ত);

    যদি (ret) {
        SDL_SetError("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#যদি 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#endif
        গচ্ছ out;
    }

    যদি (dispdata->kms_in_fence_fd != -1) {
        close(dispdata->kms_in_fence_fd);
        dispdata->kms_in_fence_fd = -1;
    }

out:
    KMSDRM_drmModeAtomicFree(dispdata->atomic_req);
    dispdata->atomic_req = রিক্ত;

    ঘূৰাই ret;
}

শূন্য
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    যদি (dispdata->kms_fence) {
       EGLint status;

        কৰা {
            status = _this->egl_data->eglClientWaitSyncKHR(_this->egl_data->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } যেতিয়ালৈ (status != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_data->eglDestroySyncKHR(_this->egl_data->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = রিক্ত;
    }
}

স্থির bool KMSDRM_Available(শূন্য)
{
#ifdef SDL_PLATFORM_OPENBSD
    সংরচনা utsname nameofsystem;
    দ্ৱিগুণ releaseversion;
#endif
    পূর্ণাঙ্ক ret = -ENOENT;

#ifdef SDL_PLATFORM_OPENBSD
    যদি (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        যদি (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#endif

    যদি (moderndri) {
        SDL_strlcpy(kmsdrm_dri_path, "/dev/dri/", পরিমাণ(kmsdrm_dri_path));
        SDL_strlcpy(kmsdrm_dri_devname, "card", পরিমাণ(kmsdrm_dri_devname));
    } অন্যথা {
        SDL_strlcpy(kmsdrm_dri_path, "/dev/", পরিমাণ(kmsdrm_dri_path));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", পরিমাণ(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_path);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (শূন্য)SDL_snprintf(kmsdrm_dri_cardpath, পরিমাণ(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_path, kmsdrm_dri_devname);

    ret = get_driindex();
    যদি (ret >= 0) {
        ঘূৰাই true;
    }

    ঘূৰাই false;
}

স্থির শূন্য KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    যদি (device->internal) {
        SDL_free(device->internal);
        device->internal = রিক্ত;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

স্থির SDL_VideoDevice *KMSDRM_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_VideoData *viddata;
    পূর্ণাঙ্ক devindex;

    যদি (!KMSDRM_Available()) {
        ঘূৰাই রিক্ত;
    }

    devindex = get_driindex();
    যদি (devindex < 0) {
        SDL_SetError("devindex (%d) must not be negative.", devindex);
        ঘূৰাই রিক্ত;
    }

    যদি (!SDL_KMSDRM_LoadSymbols()) {
        ঘূৰাই রিক্ত;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, পরিমাণ(SDL_VideoDevice));
    যদি (!device) {
        ঘূৰাই রিক্ত;
    }

    viddata = (SDL_VideoData *)SDL_calloc(1, পরিমাণ(SDL_VideoData));
    যদি (!viddata) {
        গচ্ছ cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->internal = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->SetDisplayMode = KMSDRM_SetDisplayMode;
    device->CreateSDLWindow = KMSDRM_CreateWindow;
    device->SetWindowTitle = KMSDRM_SetWindowTitle;
    device->SetWindowPosition = KMSDRM_SetWindowPosition;
    device->SetWindowSize = KMSDRM_SetWindowSize;
    device->SetWindowFullscreen = KMSDRM_SetWindowFullscreen;
    device->ShowWindow = KMSDRM_ShowWindow;
    device->HideWindow = KMSDRM_HideWindow;
    device->RaiseWindow = KMSDRM_RaiseWindow;
    device->MaximizeWindow = KMSDRM_MaximizeWindow;
    device->MinimizeWindow = KMSDRM_MinimizeWindow;
    device->RestoreWindow = KMSDRM_RestoreWindow;
    device->DestroyWindow = KMSDRM_DestroyWindow;
    device->SetWindowFocusable = KMSDRM_SetWindowFocusable;

    device->GL_LoadLibrary = KMSDRM_GLES_LoadLibrary;
    device->GL_GetProcAddress = KMSDRM_GLES_GetProcAddress;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_SetSwapInterval = KMSDRM_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = KMSDRM_GLES_GetSwapInterval;
    device->GL_SwapWindow = KMSDRM_GLES_SwapWindow;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_SetDefaultProfileConfig = KMSDRM_GLES_SetDefaultProfileConfig;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = KMSDRM_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#endif

    device->PumpEvents = KMSDRM_PumpEvents;
    device->মুক্ত = KMSDRM_DeleteDevice;

    ঘূৰাই device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    ঘূৰাই রিক্ত;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    রিক্ত, // no ShowMessageBox implementation
    false
};

স্থির শূন্য KMSDRM_FBDestroyCallback(সংরচনা gbm_bo *bo, শূন্য *data)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)data;

    যদি (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drmModeRmFB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, সংরচনা gbm_bo *bo)
{
    SDL_VideoData *viddata = _this->internal;
    unsigned w, h;
    পূর্ণাঙ্ক rc = -1;
    পূর্ণাঙ্ক অঙ্ক_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_data(bo);

    যদি (fb_info) {
        ঘূৰাই fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, পরিমাণ(KMSDRM_FBInfo));

    যদি (!fb_info) {
        ঘূৰাই রিক্ত;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_width(bo);
    h = KMSDRM_gbm_bo_get_height(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    যদি (KMSDRM_drmModeAddFB2WithModifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_গুনতি &&
        KMSDRM_gbm_bo_get_offset &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        অঙ্ক_planes = KMSDRM_gbm_bo_get_plane_গুনতি(bo);
        বাবে (পূর্ণাঙ্ক i = 0; i < অঙ্ক_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_offset(bo, i);
            modifiers[i] = modifiers[0];
        }

        যদি (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_MODE_FB_MODIFIERS;
        }

        rc = KMSDRM_drmModeAddFB2WithModifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    যদি (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drmModeAddFB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    যদি (rc < 0) {
        SDL_free(fb_info);
        ঘূৰাই রিক্ত;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (শূন্য *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_set_user_data(bo, fb_info, KMSDRM_FBDestroyCallback);

    ঘূৰাই fb_info;
}

স্থির শূন্য KMSDRM_FlipHandler(পূর্ণাঙ্ক fd, unsigned পূর্ণাঙ্ক frame, unsigned পূর্ণাঙ্ক sec, unsigned পূর্ণাঙ্ক usec, শূন্য *data)
{
    *((bool *)data) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_WindowData *windata)
{

    SDL_VideoData *viddata = _this->internal;
    drmEventContext ev = { 0 };
    সংরচনা pollfd pfd = { 0 };
    পূর্ণাঙ্ক ret;

    ev.version = DRM_EVENT_CONTEXT_VERSION;
    ev.page_flip_handler = KMSDRM_FlipHandler;

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
    যেতিয়ালৈ (windata->waiting_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        যদি (ret < 0) {
            যদি (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                অনুৱর্ত;
            } অন্যথা {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                ঘূৰাই false;
            }
        }

        যদি (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            ঘূৰাই false;
        }

        যদি (pfd.revents & POLLIN) {
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

    ঘূৰাই true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
স্থির drmModeModeInfo *KMSDRM_GetClosestDisplayMode(SDL_VideoDisplay *display, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{

    SDL_DisplayData *dispdata = display->internal;
    drmModeConnector *conn = dispdata->connector.connector;

    SDL_DisplayMode closest;
    drmModeModeInfo *drm_mode;

    যদি (SDL_GetClosestFullscreenDisplayMode(display->id, width, height, 0.0f, false, &closest)) {
        ধ্রুৱ SDL_DisplayModeData *modedata = closest.internal;
        drm_mode = &conn->modes[modedata->mode_index];
        ঘূৰাই drm_mode;
    } অন্যথা {
        ঘূৰাই রিক্ত;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

স্থির bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;

    যদি (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drmSetClientCap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drmSetClientCap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    যদি (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        ঘূৰাই true;
    }

    ঘূৰাই KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
স্থির শূন্য KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayID *displays;
    SDL_DisplayData *dispdata;
    পূর্ণাঙ্ক i;

    displays = SDL_GetDisplays(রিক্ত);
    যদি (displays) {
        // Iterate on the SDL Display list.
        বাবে (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_GetDisplayDriverData(displays[i]);

            // Free connector
            যদি (dispdata && dispdata->connector.connector) {
                KMSDRM_drmModeFreeConnector(dispdata->connector.connector);
                dispdata->connector.connector = রিক্ত;
            }

            // Free CRTC
            যদি (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drmModeFreeCrtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = রিক্ত;
            }
        }
        SDL_free(displays);
    }

    যদি (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

স্থির bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool found = false;
    uint64_t prop_মান = 0;

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, output_id, DRM_MODE_OBJECT_CONNECTOR);
    যদি (props) {
        বাবে (uint32_t i = 0; !found && i < props->গুনতি_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            যদি (prop) {
                যদি (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_মান = props->prop_মানসমূহ[i];
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    যদি (found) {
        ঘূৰাই prop_মান ? true : false;
    }
    ঘূৰাই false;
}

স্থির bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool found = false;
    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC);
    যদি (props) {
        বাবে (uint32_t i = 0; !found && i < props->গুনতি_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            যদি (prop) {
                যদি (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    ঘূৰাই found;
}

স্থির শূন্য KMSDRM_CrtcSetVrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    যদি (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ঘূৰাই;
    }

    KMSDRM_drmModeObjectSetProperty(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC, vrr_prop_id, enabled);
}

স্থির bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool found = false;
    uint64_t prop_মান = 0;

    যদি (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        ঘূৰাই false;
    }

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC);
    যদি (props) {
        বাবে (uint32_t i = 0; !found && i < props->গুনতি_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            যদি (prop) {
                যদি (prop->prop_id == vrr_prop_id) {
                    prop_মান = props->prop_মানসমূহ[i];
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    যদি (found) {
        ঘূৰাই prop_মান ? true : false;
    }
    ঘূৰাই false;
}

স্থির পূর্ণাঙ্ক KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool found = false;
    পূর্ণাঙ্ক orientation = 0;

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CONNECTOR);
    যদি (props) {
        বাবে (uint32_t i = 0; !found && i < props->গুনতি_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            যদি (prop) {
                যদি (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_MODE_PROP_ENUM)) {
                    যদি (prop->গুনতি_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        যদি (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } অন্যথা যদি (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } অন্যথা যদি (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    ঘূৰাই orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
স্থির শূন্য KMSDRM_AddDisplay(SDL_VideoDevice *_this, drmModeConnector *conn, drmModeRes *resources)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *dispdata = রিক্ত;
    SDL_VideoDisplay display = { 0 };
    SDL_DisplayModeData *modedata = রিক্ত;
    drmModeEncoder *encoder = রিক্ত;
    drmModeCrtc *crtc = রিক্ত;
    ধ্রুৱ ৱর্ণ *connector_type = রিক্ত;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    ৱর্ণ name_fmt[64];
    পূর্ণাঙ্ক orientation;
    পূর্ণাঙ্ক mode_index;
    পূর্ণাঙ্ক i, j;
    পূর্ণাঙ্ক ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_DisplayData *)SDL_calloc(1, পরিমাণ(SDL_DisplayData));
    যদি (!dispdata) {
        ret = -1;
        গচ্ছ cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = রিক্ত;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_in_fence_fd = -1;
    dispdata->kms_out_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    বাবে (i = 0; i < resources->গুনতি_encoders; i++) {
        encoder = KMSDRM_drmModeGetEncoder(viddata->drm_fd, resources->encoders[i]);

        যদি (!encoder) {
            অনুৱর্ত;
        }

        যদি (encoder->encoder_id == conn->encoder_id) {
            ভঙ্গ;
        }

        KMSDRM_drmModeFreeEncoder(encoder);
        encoder = রিক্ত;
    }

    যদি (!encoder) {
        // No encoder was connected, find the first supported one
        বাবে (i = 0; i < resources->গুনতি_encoders; i++) {
            encoder = KMSDRM_drmModeGetEncoder(viddata->drm_fd,
                                               resources->encoders[i]);

            যদি (!encoder) {
                অনুৱর্ত;
            }

            বাবে (j = 0; j < conn->গুনতি_encoders; j++) {
                যদি (conn->encoders[j] == encoder->encoder_id) {
                    ভঙ্গ;
                }
            }

            যদি (j != conn->গুনতি_encoders) {
                ভঙ্গ;
            }

            KMSDRM_drmModeFreeEncoder(encoder);
            encoder = রিক্ত;
        }
    }

    যদি (!encoder) {
        ret = SDL_SetError("No connected encoder found for connector.");
        গচ্ছ cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drmModeGetCrtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    যদি (!crtc) {
        বাবে (i = 0; i < resources->গুনতি_crtcs; i++) {
            যদি (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drmModeGetCrtc(viddata->drm_fd, encoder->crtc_id);
                ভঙ্গ;
            }
        }
    }

    যদি (!crtc) {
        ret = SDL_SetError("No CRTC found for connector.");
        গচ্ছ cleanup;
    }

    // Find the index of the mode attached to this CRTC
    mode_index = -1;

    বাবে (i = 0; i < conn->গুনতি_modes; i++) {
        drmModeModeInfo *mode = &conn->modes[i];

        যদি (!SDL_memcmp(mode, &crtc->mode, পরিমাণ(crtc->mode))) {
            mode_index = i;
            ভঙ্গ;
        }
    }

    যদি (mode_index == -1) {
        পূর্ণাঙ্ক current_area, largest_area = 0;

        // Find the preferred mode or the highest resolution mode
        বাবে (i = 0; i < conn->গুনতি_modes; i++) {
            drmModeModeInfo *mode = &conn->modes[i];

            যদি (mode->type & DRM_MODE_TYPE_PREFERRED) {
                mode_index = i;
                ভঙ্গ;
            }

            current_area = mode->hdisplay * mode->vdisplay;
            যদি (current_area > largest_area) {
                mode_index = i;
                largest_area = current_area;
            }
        }
        যদি (mode_index != -1) {
            crtc->mode = conn->modes[mode_index];
        }
    }

    যদি (mode_index == -1) {
        ret = SDL_SetError("Failed to find index of mode attached to the CRTC.");
        গচ্ছ cleanup;
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
    dispdata->mode = crtc->mode;
    dispdata->original_mode = crtc->mode;
    dispdata->fullscreen_mode = crtc->mode;

    যদি (dispdata->mode.hdisplay == 0 || dispdata->mode.vdisplay == 0) {
        ret = SDL_SetError("Couldn't get a valid connector videomode.");
        গচ্ছ cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    যদি (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_CrtcSetVrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    যদি (KMSDRM_drmModeGetConnectorTypeName) {
        connector_type = KMSDRM_drmModeGetConnectorTypeName(conn->connector_type);
        যদি (connector_type == রিক্ত) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd, crtc->crtc_id, DRM_MODE_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->গুনতি_props, পরিমাণ(*dispdata->crtc.props_info));
    যদি (!dispdata->crtc.props_info) {
        ret = false;
        গচ্ছ cleanup;
    }

    বাবে (i = 0; i < dispdata->crtc.props->গুনতি_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd, conn->connector_id, DRM_MODE_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->গুনতি_props, পরিমাণ(*dispdata->connector.props_info));
    যদি (!dispdata->connector.props_info) {
        ret = false;
        গচ্ছ cleanup;
    }

    বাবে (i = 0; i < dispdata->connector.props->গুনতি_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));

    যদি (!modedata) {
        ret = -1;
        গচ্ছ cleanup;
    }

    modedata->mode_index = mode_index;

    display.internal = dispdata;
    display.desktop_mode.w = dispdata->mode.hdisplay;
    display.desktop_mode.h = dispdata->mode.vdisplay;
    CalculateRefreshRate(&dispdata->mode, &display.desktop_mode.refresh_rate_numerator, &display.desktop_mode.refresh_rate_denominator);
    display.desktop_mode.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_mode.internal = modedata;
    যদি (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_AddVideoDisplay(&display, false);
    যদি (!display_id) {
        ret = -1;
        গচ্ছ cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_Set_সংখ্যা_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_সংখ্যা, orientation);

#ifdef DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#endif

cleanup:
    যদি (encoder) {
        KMSDRM_drmModeFreeEncoder(encoder);
    }
    যদি (ret) {
        // Error (complete) cleanup
        যদি (dispdata) {
            যদি (dispdata->connector.connector) {
                KMSDRM_drmModeFreeConnector(dispdata->connector.connector);
            }
            যদি (dispdata->crtc.crtc) {
                KMSDRM_drmModeFreeCrtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

স্থির শূন্য KMSDRM_SortDisplays(SDL_VideoDevice *_this)
{
    ধ্রুৱ ৱর্ণ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    যদি (name_hint) {
        ৱর্ণ *saveptr;
        ৱর্ণ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(পরিমাণ(SDL_VideoDisplay *) * _this->অঙ্ক_displays);

        যদি (str && sorted_list) {
            পূর্ণাঙ্ক sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ধ্রুৱ ৱর্ণ *token = SDL_strtok_r(str, ",", &saveptr);
            যেতিয়ালৈ (token) {
                বাবে (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    যদি (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_index++] = d;
                        _this->displays[i] = রিক্ত;
                        ভঙ্গ;
                    }
                }

                token = SDL_strtok_r(রিক্ত, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            বাবে (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
                যদি (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, পরিমাণ(SDL_VideoDisplay *) * _this->অঙ্ক_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

স্থির bool set_client_atomic_caps(পূর্ণাঙ্ক fd)
{
    যদি (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        ঘূৰাই false;  // emergency escape hatch.
    } অন্যথা যদি (KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        ঘূৰাই false;  // no atomic modesetting support.
    } অন্যথা যদি (KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        ঘূৰাই false;  // no universal planes support.
    }
    ঘূৰাই true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
স্থির bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;
    drmModeRes *resources = রিক্ত;
    uint64_t async_pageflip = 0;
    পূর্ণাঙ্ক i;
    bool result = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (শূন্য)SDL_snprintf(viddata->devpath, পরিমাণ(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    যদি (viddata->drm_fd < 0) {
        result = SDL_SetError("Could not open %s", viddata->devpath);
        গচ্ছ cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = set_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drmModeGetResources(viddata->drm_fd);
    যদি (!resources) {
        result = SDL_SetError("drmModeGetResources(%d) failed", viddata->drm_fd);
        গচ্ছ cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    বাবে (i = 0; i < resources->গুনতি_connectors; i++) {
        drmModeConnector *conn = KMSDRM_drmModeGetConnector(viddata->drm_fd, resources->connectors[i]);
        যদি (!conn) {
            অনুৱর্ত;
        }

        যদি (conn->connection == DRM_MODE_CONNECTED && conn->গুনতি_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_AddDisplay(_this, conn, resources);
        } অন্যথা {
            // If it's not, free it now.
            KMSDRM_drmModeFreeConnector(conn);
        }
    }

    // Have we added any SDL displays?
    যদি (SDL_GetPrimaryDisplay() == 0) {
        result = SDL_SetError("No connected displays found.");
        গচ্ছ cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_SortDisplays(_this);

    // Determine if video hardware supports async pageflips.
    যদি (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_PAGE_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    যদি (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    যদি (resources) {
        KMSDRM_drmModeFreeResources(resources);
    }
    যদি (!result) {
        যদি (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    ঘূৰাই result;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
স্থির bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = _this->internal;
    bool result = true;

    // Reopen the FD if we weren't able to drop master on the original one
    যদি (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        যদি (viddata->drm_fd < 0) {
            ঘূৰাই SDL_SetError("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = set_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drmSetMaster(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    যদি (!viddata->gbm_dev) {
        result = SDL_SetError("Couldn't create gbm device.");
    } অন্যথা {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        result = setup_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        যদি (!result) {
            SDL_SetError("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    ঘূৰাই result;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
স্থির শূন্য KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = _this->internal;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    যদি (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = রিক্ত;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    যদি (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

স্থির শূন্য KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *windata = window->internal;
    SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
    পূর্ণাঙ্ক ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    যদি (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#যদি 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        add_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        add_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        add_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_WaitPageFlip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_set_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->buffer_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_mode);

        /* Issue atomic commit that is blocking and allows modesetting. */
        যদি (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_SetError("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        যদি (ret && (dispdata->crtc->mode_valid == 0)) {
            ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->buffer_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_mode);
        }
#endif

#যদি 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->buffer_id;
        plane_info.src_w = dispdata->original_mode.hdisplay;
        plane_info.src_h = dispdata->original_mode.vdisplay;
        plane_info.crtc_w = dispdata->original_mode.hdisplay;
        plane_info.crtc_h = dispdata->original_mode.vdisplay;

        drm_atomic_set_plane_props(dispdata, &plane_info);

        যদি (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_SetError("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#endif

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->buffer_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_mode);

    // If we failed to set the original mode, try to set the connector preferred mode.
    যদি (ret && (dispdata->crtc.crtc->mode_valid == 0)) {
        ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->buffer_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_mode);
    }

    যদি (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    যদি (windata->bo) {
        যদি (windata->bo != windata->next_bo) {
            KMSDRM_gbm_surface_release_buffer(windata->gs, windata->bo);
        }
        windata->bo = রিক্ত;
    }

    যদি (windata->next_bo) {
        KMSDRM_gbm_surface_release_buffer(windata->gs, windata->next_bo);
        windata->next_bo = রিক্ত;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    যদি (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    যদি (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = রিক্ত;
    }
}

স্থির শূন্য KMSDRM_GetModeToSet(SDL_Window *window, drmModeModeInfo *out_mode)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    SDL_DisplayData *dispdata = display->internal;

    যদি (window->fullscreen_exclusive) {
        *out_mode = dispdata->fullscreen_mode;
    } অন্যথা {
        drmModeModeInfo *mode = KMSDRM_GetClosestDisplayMode(display, window->windowed.w, window->windowed.h);
        যদি (mode) {
            *out_mode = *mode;
        } অন্যথা {
            *out_mode = dispdata->original_mode;
        }
    }
}

স্থির শূন্য KMSDRM_DirtySurfaces(SDL_Window *window)
{
    SDL_WindowData *windata = window->internal;
    drmModeModeInfo mode;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_GetModeToSet(window, &mode);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode.hdisplay, mode.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_Window *window)
{
    স্থির ধ্রুৱ সংরচনা { uint32_t fmt; ধ্রুৱ ৱর্ণ *name; পূর্ণাঙ্ক r; পূর্ণাঙ্ক g; পূর্ণাঙ্ক b; পূর্ণাঙ্ক a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #define FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #undef FMT
    };

    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *windata = window->internal;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    SDL_DisplayData *dispdata = display->internal;
    EGLContext egl_context;
    bool result = false;

    // If the current window already has surfaces, destroy them before creating other.
    যদি (windata->gs) {
        KMSDRM_DestroySurfaces(_this, window);
    }

    bool tried_setting_format = false;
    ধ্রুৱ uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    বাবে (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ধ্রুৱ uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        যদি (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            অনুৱর্ত;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_GetModeToSet(window, &dispdata->mode);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->mode.hdisplay, dispdata->mode.vdisplay, surface_fmt, surface_flags);
        যদি (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->mode.hdisplay, dispdata->mode.vdisplay, surface_fmt, 0);
        }
        যদি (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_SetError("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            অনুৱর্ত;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_SetRequiredVisualId(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)windata->gs);
        যদি (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = রিক্ত;
            অনুৱর্ত;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        result = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        যদি (!result) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            অনুৱর্ত;
        }

        _this->gl_config.red_size = gbm_formats[i].r;
        _this->gl_config.green_size = gbm_formats[i].g;
        _this->gl_config.blue_size = gbm_formats[i].b;
        _this->gl_config.alpha_size = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        result = true;

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, dispdata->mode.hdisplay, dispdata->mode.vdisplay);

        ভঙ্গ;
    }

    SDL_assert(result || (windata->gs == রিক্ত));

    যদি (!result) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        যদি (!tried_setting_format) {   // make sure there's an error string set.
            SDL_SetError("Could not find any supported GBM surface format.");
        }
    }

    ঘূৰাই result;
}

#ifdef SDL_প্ৰবেশ_LINUXEV
স্থির শূন্য KMSDRM_ReleaseVT(শূন্য *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_VideoData *viddata = _this->internal;
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < viddata->অঙ্ক_windows; i++) {
        SDL_Window *window = viddata->windows[i];
        যদি (!(window->flags & SDL_WINDOW_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, window);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

স্থির শূন্য KMSDRM_AcquireVT(শূন্য *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_VideoData *viddata = _this->internal;
    পূর্ণাঙ্ক i;

    KMSDRM_drmSetMaster(viddata->drm_fd);
    বাবে (i = 0; i < viddata->অঙ্ক_windows; i++) {
        SDL_Window *window = viddata->windows[i];
        যদি (!(window->flags & SDL_WINDOW_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, window);
        }
    }
}
#endif // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool result = true;

    SDL_VideoData *viddata = _this->internal;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    যদি (!KMSDRM_InitDisplays(_this)) {
        result = SDL_SetError("error getting KMSDRM displays information");
    }

#ifdef SDL_প্ৰবেশ_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_SetVTSwitchCallbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#নোচেদ্যদি defined(SDL_প্ৰবেশ_WSCONS)
    SDL_WSCONS_Init();
#endif

    viddata->video_init = true;

    ঘূৰাই result;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
শূন্য KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;

    KMSDRM_DeinitDisplays(_this);

#ifdef SDL_প্ৰবেশ_LINUXEV
    SDL_EVDEV_SetVTSwitchCallbacks(রিক্ত, রিক্ত, রিক্ত, রিক্ত);
    SDL_EVDEV_Quit();
#নোচেদ্যদি defined(SDL_প্ৰবেশ_WSCONS)
    SDL_WSCONS_Quit();
#endif

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = রিক্ত;
    viddata->max_windows = 0;
    viddata->অঙ্ক_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *dispdata = display->internal;
    drmModeConnector *conn = dispdata->connector.connector;
    SDL_DisplayMode mode;
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < conn->গুনতি_modes; i++) {
        SDL_DisplayModeData *modedata = SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));

        যদি (modedata) {
            modedata->mode_index = i;
        }

        SDL_zero(mode);
        mode.w = conn->modes[i].hdisplay;
        mode.h = conn->modes[i].vdisplay;
        CalculateRefreshRate(&conn->modes[i], &mode.refresh_rate_numerator, &mode.refresh_rate_denominator);
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        mode.internal = modedata;

        যদি (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(modedata);
        }
    }
    ঘূৰাই true;
}

bool KMSDRM_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *dispdata = display->internal;
    SDL_DisplayModeData *modedata = mode->internal;
    drmModeConnector *conn = dispdata->connector.connector;
    পূর্ণাঙ্ক i;

    // Don't do anything if we are in Vulkan mode.
    যদি (viddata->vulkan_mode) {
        ঘূৰাই true;
    }

    যদি (!modedata) {
        ঘূৰাই SDL_SetError("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_mode = conn->modes[modedata->mode_index];

    বাবে (i = 0; i < viddata->অঙ্ক_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    ঘূৰাই true;
}

শূন্য KMSDRM_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windata = window->internal;
    SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
    SDL_VideoData *viddata;
    bool is_vulkan = window->flags & SDL_WINDOW_VULKAN; // Is this a VK window?
    unsigned পূর্ণাঙ্ক i, j;

    যদি (!windata) {
        ঘূৰাই;
    }

    // restore vrr state
    KMSDRM_CrtcSetVrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    যদি (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_GetVideoDisplayForWindow(window));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, window);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        যদি (viddata->অঙ্ক_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            যদি (_this->egl_data) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } অন্যথা {

        // If we were in Vulkan mode, get out of it.
        যদি (viddata->vulkan_mode) {
            viddata->vulkan_mode = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    বাবে (i = 0; i < viddata->অঙ্ক_windows; i++) {
        যদি (viddata->windows[i] == window) {
            viddata->অঙ্ক_windows--;

            বাবে (j = i; j < viddata->অঙ্ক_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            ভঙ্গ;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(window->internal);
    window->internal = রিক্ত;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *windata = রিক্ত;
    SDL_VideoData *viddata = _this->internal;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    SDL_DisplayData *dispdata = display->internal;
    bool is_vulkan = window->flags & SDL_WINDOW_VULKAN; // Is this a VK window?
    bool vulkan_mode = viddata->vulkan_mode;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drmModeModeInfo *mode;
    bool result = true;

    // Allocate window internal data
    windata = (SDL_WindowData *)SDL_calloc(1, পরিমাণ(SDL_WindowData));
    যদি (!windata) {
        ঘূৰাই false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    window->internal = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_buffer = false;
    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_BUFFER, false)) {
        windata->double_buffer = true;
    }

    যদি (!is_vulkan && !vulkan_mode) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        window->flags |= SDL_WINDOW_OPENGL;

        যদি (!(viddata->gbm_init)) {

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
            যদি (!KMSDRM_GBMInit(_this, dispdata)) {
                ঘূৰাই SDL_SetError("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        যদি (!_this->egl_data) {
            egl_display = (NativeDisplayType)_this->internal->gbm_dev;
            যদি (!SDL_EGL_LoadLibrary(_this, রিক্ত, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_version = 2;
                _this->gl_config.minor_version = 0;
                যদি (!SDL_EGL_LoadLibrary(_this, রিক্ত, egl_display)) {
                    ঘূৰাই SDL_SetError("Can't load EGL/GL library on window creation.");
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
        mode = KMSDRM_GetClosestDisplayMode(display, window->windowed.w, window->windowed.h);

        যদি (mode) {
            dispdata->fullscreen_mode = *mode;
        } অন্যথা {
            dispdata->fullscreen_mode = dispdata->original_mode;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        যদি (!KMSDRM_CreateSurfaces(_this, window)) {
            ঘূৰাই false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    যদি (viddata->অঙ্ক_windows >= viddata->max_windows) {
        unsigned পূর্ণাঙ্ক new_max_windows = viddata->max_windows + 1;
        SDL_Window **new_windows = (SDL_Window **)SDL_realloc(viddata->windows,
                                                              new_max_windows * পরিমাণ(SDL_Window *));
        যদি (!new_windows) {
            ঘূৰাই false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->অঙ্ক_windows++] = window;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_mode = is_vulkan;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_KMSDRM_DEVICE_INDEX_সংখ্যা, viddata->devindex);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_KMSDRM_DRM_FD_সংখ্যা, viddata->drm_fd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_KMSDRM_GBM_DEVICE_POINTER, viddata->gbm_dev);

    যদি ((window->flags & SDL_WINDOW_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_GetDisplayForWindow(window), &display_bounds);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    ঘূৰাই result;
}

শূন্য KMSDRM_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool KMSDRM_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ঘূৰাই SDL_Unsupported();
}
শূন্য KMSDRM_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    যদি (!viddata->vulkan_mode) {
        KMSDRM_DirtySurfaces(window);
    }
}
SDL_FullscreenResult KMSDRM_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_VideoData *viddata = _this->internal;
    যদি (!viddata->vulkan_mode) {
        KMSDRM_DirtySurfaces(window);
    }
    ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
}
শূন্য KMSDRM_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য KMSDRM_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য KMSDRM_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য KMSDRM_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য KMSDRM_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য KMSDRM_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool KMSDRM_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    ঘূৰাই true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
