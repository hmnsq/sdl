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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#அந்தர்பாவ "../SDL_egl_c.h"

// SDL internals
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#ifdef SDL_உள்ளீடு_LINUXEV
#அந்தர்பாவ "../../core/linux/SDL_evdev.h"
#அல்லதெனில் defined SDL_உள்ளீடு_WSCONS
#அந்தர்பாவ "../../core/openbsd/SDL_wscons.h"
#endif

// KMS/DRM declarations
#அந்தர்பாவ "SDL_kmsdrmdyn.h"
#அந்தர்பாவ "SDL_kmsdrmevents.h"
#அந்தர்பாவ "SDL_kmsdrmmouse.h"
#அந்தர்பாவ "SDL_kmsdrmvideo.h"
#அந்தர்பாவ "SDL_kmsdrmopengles.h"
#அந்தர்பாவ "SDL_kmsdrmvulkan.h"
#அந்தர்பாவ <dirent.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <poll.h>
#அந்தர்பாவ <sys/param.h>
#அந்தர்பாவ <sys/stat.h>
#அந்தர்பாவ <sys/utsname.h>

#ifdef SDL_PLATFORM_OPENBSD
நிலையான bool moderndri = false;
#இல்லையெனில்
நிலையான bool moderndri = true;
#endif

நிலையான எழுத்து kmsdrm_dri_path[16];
நிலையான முழு kmsdrm_dri_pathsize = 0;
நிலையான எழுத்து kmsdrm_dri_devname[8];
நிலையான முழு kmsdrm_dri_devnamesize = 0;
நிலையான எழுத்து kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#ifndef DRM_FORMAT_MOD_VENDOR_NONE
#define DRM_FORMAT_MOD_VENDOR_NONE 0
#endif
#ifndef DRM_FORMAT_MOD_LINEAR
#define DRM_FORMAT_MOD_LINEAR fourcc_mod_code(NONE, 0)
#endif

நிலையான முழு get_driindex(வெறுமை)
{
    முழு available = -ENOENT;
    எழுத்து device[அளவு(kmsdrm_dri_cardpath)];
    முழு drm_fd;
    முழு i;
    முழு devindex = -1;
    DIR *folder;
    மாறிலி எழுத்து *hint;
    கட்டமைப்பு dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_INDEX);
    எனில் (hint && *hint) {
        எழுத்து *endptr = வெற்று;
        மாறிலி முழு idx = (முழு)SDL_strtol(hint, &endptr, 10);
        எனில் ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            திரும்பு idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_path, அளவு(device));
    folder = opendir(device);
    எனில் (!folder) {
        SDL_SetError("Failed to open directory '%s'", device);
        திரும்பு -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                அளவு(device) - kmsdrm_dri_pathsize);
    போது((res = readdir(folder)) != வெற்று && available < 0) {
        எனில் (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        அளவு(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            எனில் (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                எனில் (SDL_KMSDRM_LoadSymbols()) {
                    drmModeRes *resources = KMSDRM_drmModeGetResources(drm_fd);
                    எனில் (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->மொத்தம்_connectors,
                                     resources->மொத்தம்_encoders,
                                     resources->மொத்தம்_crtcs);

                        எனில் (resources->மொத்தம்_connectors > 0 &&
                            resources->மொத்தம்_encoders > 0 &&
                            resources->மொத்தம்_crtcs > 0) {
                            available = -ENOENT;
                            க்கு (i = 0; i < resources->மொத்தம்_connectors && available < 0; i++) {
                                drmModeConnector *conn =
                                    KMSDRM_drmModeGetConnector(
                                        drm_fd, resources->connectors[i]);

                                எனில் (!conn) {
                                    தொடர்;
                                }

                                எனில் (conn->connection == DRM_MODE_CONNECTED &&
                                    conn->மொத்தம்_modes) {
                                    bool access_denied = false;
                                    எனில் (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drmSetMaster(drm_fd);
                                        எனில் (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    எனில் (!access_denied) {
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
            } இல்லையெனில் {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    திரும்பு available;
}

நிலையான வெறுமை CalculateRefreshRate(drmModeModeInfo *mode, முழு *numerator, முழு *denominator)
{
    *numerator = mode->clock * 1000;
    *denominator = mode->htotal * mode->vtotal;

    எனில் (mode->flags & DRM_MODE_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    எனில் (mode->flags & DRM_MODE_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    எனில் (mode->vscan > 1) {
        *denominator *= mode->vscan;
    }
}


முழு add_connector_property(drmModeAtomicReq *req, KMSDRM_connector *conn, மாறிலி எழுத்து *name, uint64_t மதிப்பு)
{
    unsigned முழு i;
    முழு prop_id = 0;

    க்கு (i = 0 ; i < conn->props->மொத்தம்_props ; i++) {
        எனில் (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            நிறுத்து;
        }
    }

    எனில் (prop_id < 0) {
        SDL_SetError("no connector property: %s", name);
        திரும்பு -EINVAL;
    }

    திரும்பு KMSDRM_drmModeAtomicAddProperty(req, conn->connector->connector_id, prop_id, மதிப்பு);
}

முழு add_crtc_property(drmModeAtomicReq *req, KMSDRM_crtc *c, மாறிலி எழுத்து *name, uint64_t மதிப்பு)
{
    unsigned முழு i;
    முழு prop_id = -1;

    க்கு (i = 0 ; i < c->props->மொத்தம்_props ; i++) {
        எனில் (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            நிறுத்து;
        }
    }

    எனில் (prop_id < 0) {
        SDL_SetError("no crtc property: %s", name);
        திரும்பு -EINVAL;
    }

    திரும்பு KMSDRM_drmModeAtomicAddProperty(req, c->crtc->crtc_id, prop_id, மதிப்பு);
}

முழு add_plane_property(drmModeAtomicReq *req, KMSDRM_plane *p, மாறிலி எழுத்து *name, uint64_t மதிப்பு)
{
    unsigned முழு i;
    முழு prop_id = -1;

    க்கு (i = 0 ; i < p->props->மொத்தம்_props ; i++) {
        எனில் (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            நிறுத்து;
        }
    }

    எனில் (prop_id < 0) {
        SDL_SetError("no plane property: %s", name);
        திரும்பு -EINVAL;
    }

    திரும்பு KMSDRM_drmModeAtomicAddProperty(req, p->plane->plane_id, prop_id, மதிப்பு);
}

#ifdef DEBUG_KMSDRM
நிலையான வெறுமை print_plane_info(SDL_VideoDevice *_this, drmModePlanePtr plane)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd,
        plane->plane_id, DRM_MODE_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    க்கு (முழு i = 0; i < props->மொத்தம்_props; i++) {
        drmModePropertyPtr p = KMSDRM_drmModeGetProperty(viddata->drm_fd, props->props[i]);
        எனில் ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_மதிப்புகள்[i];
        }

        KMSDRM_drmModeFreeProperty(p);
    }

    எழுத்து *plane_type = "unknown";
    தேர்வு (type) {
        நிலை DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            நிறுத்து;

        நிலை DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            நிறுத்து;

        நிலை DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            நிறுத்து;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drmModeRes *resources = KMSDRM_drmModeGetResources(viddata->drm_fd);
    எனில் (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        க்கு (முழு i = 0; i < resources->மொத்தம்_crtcs; i++) {
            எனில் (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                நிறுத்து;
            }
        }
        SDL_Log("%s\n\n", (மாறிலி எழுத்து *)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ""));
        SDL_CloseIO(io);
    }
}

நிலையான வெறுமை get_planes_info(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);

    drmModePlaneResPtr plane_resources = KMSDRM_drmModeGetPlaneResources(viddata->drm_fd);
    எனில் (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        திரும்பு;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->மொத்தம்_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    க்கு (uint32_t i = 0; (i < plane_resources->மொத்தம்_planes); i++) {
        மாறிலி uint32_t plane_id = plane_resources->planes[i];

        drmModePlanePtr plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);
        எனில் (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            தொடர்;
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
நிலையான முழு get_plane_id(SDL_VideoDevice *_this, unsigned முழு crtc_id, uint32_t plane_type)
{
    drmModeRes *resources = வெற்று;
    drmModePlaneResPtr plane_resources = வெற்று;
    uint32_t i, j;
    unsigned முழு crtc_index = 0;
    முழு ret = -EINVAL;
    முழு found = 0;

    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);

    resources = KMSDRM_drmModeGetResources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    க்கு (i = 0; i < resources->மொத்தம்_crtcs; i++) {
        எனில் (resources->crtcs[i] == crtc_id) {
            crtc_index = i;
            நிறுத்து;
        }
    }

    plane_resources = KMSDRM_drmModeGetPlaneResources(viddata->drm_fd);
    எனில் (!plane_resources) {
        திரும்பு SDL_SetError("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    க்கு (i = 0; (i < plane_resources->மொத்தம்_planes) && !found; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drmModePlanePtr plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);
        எனில் (!plane) {
            தொடர்;
        }

        /* See if the current CRTC is available for this plane. */
        எனில் (plane->possible_crtcs & (1 << crtc_index)) {

            drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(
                viddata->drm_fd, plane_id, DRM_MODE_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            க்கு (j = 0; j < props->மொத்தம்_props; j++) {

                drmModePropertyPtr p = KMSDRM_drmModeGetProperty(viddata->drm_fd,
                    props->props[j]);

                எனில் ((SDL_strcmp(p->name, "type") == 0) && (props->prop_மதிப்புகள்[j] == plane_type)) {
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

    திரும்பு ret;
}

/* Setup a plane and it's props. */
bool setup_plane(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    bool ret = true;

    *_plane = SDL_calloc(1, அளவு(**_plane));
    எனில் (!(*_plane)) {
        ret = false;
        செல் cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    எனில் (!plane_id) {
        ret = SDL_SetError("Invalid Plane ID");
        செல் cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drmModeGetPlane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    எனில் ((*_plane)->plane) {
        unsigned முழு i;
        (*_plane)->props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_MODE_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->மொத்தம்_props, அளவு(*(*_plane)->props_info));

        எனில் ( !((*_plane)->props_info) ) {
            ret = false;
            செல் cleanup;
        }

        க்கு (i = 0; i < (*_plane)->props->மொத்தம்_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    எனில் (!ret) {
        எனில் (*_plane) {
            SDL_free(*_plane);
            *_plane = வெற்று;
        }
    }
    திரும்பு ret;
}

/* Free a plane and it's props. */
வெறுமை free_plane(KMSDRM_plane **_plane)
{
    எனில் (*_plane) {
        எனில் ((*_plane)->plane) {
            KMSDRM_drmModeFreePlane((*_plane)->plane);
            (*_plane)->plane = வெற்று;
        }
        எனில் ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = வெற்று;
        }
        SDL_free(*_plane);
        *_plane = வெற்று;
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
வெறுமை
drm_atomic_set_plane_props(SDL_DisplayData *dispdata, கட்டமைப்பு KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    எனில் (!dispdata->atomic_req) {
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

முழு drm_atomic_commit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata, bool blocking, bool allow_modeset)
{
    SDL_VideoData *viddata = ((SDL_VideoData *)_this->internal);
    uint32_t atomic_flags = 0;
    முழு ret;

    எனில் (!blocking) {
        atomic_flags |= DRM_MODE_ATOMIC_NONBLOCK;
    }

    எனில் (allow_modeset) {
        atomic_flags |= DRM_MODE_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drmModeAtomicCommit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, வெற்று);

    எனில் (ret) {
        SDL_SetError("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#எனில் 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#endif
        செல் out;
    }

    எனில் (dispdata->kms_in_fence_fd != -1) {
        close(dispdata->kms_in_fence_fd);
        dispdata->kms_in_fence_fd = -1;
    }

out:
    KMSDRM_drmModeAtomicFree(dispdata->atomic_req);
    dispdata->atomic_req = வெற்று;

    திரும்பு ret;
}

வெறுமை
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    எனில் (dispdata->kms_fence) {
       EGLint status;

        செய் {
            status = _this->egl_data->eglClientWaitSyncKHR(_this->egl_data->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } போது (status != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_data->eglDestroySyncKHR(_this->egl_data->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = வெற்று;
    }
}

நிலையான bool KMSDRM_Available(வெறுமை)
{
#ifdef SDL_PLATFORM_OPENBSD
    கட்டமைப்பு utsname nameofsystem;
    இரட்டை releaseversion;
#endif
    முழு ret = -ENOENT;

#ifdef SDL_PLATFORM_OPENBSD
    எனில் (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        எனில் (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#endif

    எனில் (moderndri) {
        SDL_strlcpy(kmsdrm_dri_path, "/dev/dri/", அளவு(kmsdrm_dri_path));
        SDL_strlcpy(kmsdrm_dri_devname, "card", அளவு(kmsdrm_dri_devname));
    } இல்லையெனில் {
        SDL_strlcpy(kmsdrm_dri_path, "/dev/", அளவு(kmsdrm_dri_path));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", அளவு(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_path);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (வெறுமை)SDL_snprintf(kmsdrm_dri_cardpath, அளவு(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_path, kmsdrm_dri_devname);

    ret = get_driindex();
    எனில் (ret >= 0) {
        திரும்பு true;
    }

    திரும்பு false;
}

நிலையான வெறுமை KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    எனில் (device->internal) {
        SDL_free(device->internal);
        device->internal = வெற்று;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

நிலையான SDL_VideoDevice *KMSDRM_CreateDevice(வெறுமை)
{
    SDL_VideoDevice *device;
    SDL_VideoData *viddata;
    முழு devindex;

    எனில் (!KMSDRM_Available()) {
        திரும்பு வெற்று;
    }

    devindex = get_driindex();
    எனில் (devindex < 0) {
        SDL_SetError("devindex (%d) must not be negative.", devindex);
        திரும்பு வெற்று;
    }

    எனில் (!SDL_KMSDRM_LoadSymbols()) {
        திரும்பு வெற்று;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
    }

    viddata = (SDL_VideoData *)SDL_calloc(1, அளவு(SDL_VideoData));
    எனில் (!viddata) {
        செல் cleanup;
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
    device->விடுவி = KMSDRM_DeleteDevice;

    திரும்பு device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    திரும்பு வெற்று;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    வெற்று, // no ShowMessageBox implementation
    false
};

நிலையான வெறுமை KMSDRM_FBDestroyCallback(கட்டமைப்பு gbm_bo *bo, வெறுமை *data)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)data;

    எனில் (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drmModeRmFB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, கட்டமைப்பு gbm_bo *bo)
{
    SDL_VideoData *viddata = _this->internal;
    unsigned w, h;
    முழு rc = -1;
    முழு இலக்கம்_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_data(bo);

    எனில் (fb_info) {
        திரும்பு fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, அளவு(KMSDRM_FBInfo));

    எனில் (!fb_info) {
        திரும்பு வெற்று;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_width(bo);
    h = KMSDRM_gbm_bo_get_height(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    எனில் (KMSDRM_drmModeAddFB2WithModifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_மொத்தம் &&
        KMSDRM_gbm_bo_get_offset &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        இலக்கம்_planes = KMSDRM_gbm_bo_get_plane_மொத்தம்(bo);
        க்கு (முழு i = 0; i < இலக்கம்_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_offset(bo, i);
            modifiers[i] = modifiers[0];
        }

        எனில் (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_MODE_FB_MODIFIERS;
        }

        rc = KMSDRM_drmModeAddFB2WithModifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    எனில் (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drmModeAddFB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    எனில் (rc < 0) {
        SDL_free(fb_info);
        திரும்பு வெற்று;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (வெறுமை *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_set_user_data(bo, fb_info, KMSDRM_FBDestroyCallback);

    திரும்பு fb_info;
}

நிலையான வெறுமை KMSDRM_FlipHandler(முழு fd, unsigned முழு frame, unsigned முழு sec, unsigned முழு usec, வெறுமை *data)
{
    *((bool *)data) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_WindowData *windata)
{

    SDL_VideoData *viddata = _this->internal;
    drmEventContext ev = { 0 };
    கட்டமைப்பு pollfd pfd = { 0 };
    முழு ret;

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
    போது (windata->waiting_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        எனில் (ret < 0) {
            எனில் (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                தொடர்;
            } இல்லையெனில் {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                திரும்பு false;
            }
        }

        எனில் (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            திரும்பு false;
        }

        எனில் (pfd.revents & POLLIN) {
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

    திரும்பு true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
நிலையான drmModeModeInfo *KMSDRM_GetClosestDisplayMode(SDL_VideoDisplay *display, முழு width, முழு height)
{

    SDL_DisplayData *dispdata = display->internal;
    drmModeConnector *conn = dispdata->connector.connector;

    SDL_DisplayMode closest;
    drmModeModeInfo *drm_mode;

    எனில் (SDL_GetClosestFullscreenDisplayMode(display->id, width, height, 0.0f, false, &closest)) {
        மாறிலி SDL_DisplayModeData *modedata = closest.internal;
        drm_mode = &conn->modes[modedata->mode_index];
        திரும்பு drm_mode;
    } இல்லையெனில் {
        திரும்பு வெற்று;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

நிலையான bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;

    எனில் (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drmSetClientCap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drmSetClientCap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    எனில் (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        திரும்பு true;
    }

    திரும்பு KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
நிலையான வெறுமை KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayID *displays;
    SDL_DisplayData *dispdata;
    முழு i;

    displays = SDL_GetDisplays(வெற்று);
    எனில் (displays) {
        // Iterate on the SDL Display list.
        க்கு (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_GetDisplayDriverData(displays[i]);

            // Free connector
            எனில் (dispdata && dispdata->connector.connector) {
                KMSDRM_drmModeFreeConnector(dispdata->connector.connector);
                dispdata->connector.connector = வெற்று;
            }

            // Free CRTC
            எனில் (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drmModeFreeCrtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = வெற்று;
            }
        }
        SDL_free(displays);
    }

    எனில் (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

நிலையான bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool found = false;
    uint64_t prop_மதிப்பு = 0;

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, output_id, DRM_MODE_OBJECT_CONNECTOR);
    எனில் (props) {
        க்கு (uint32_t i = 0; !found && i < props->மொத்தம்_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            எனில் (prop) {
                எனில் (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_மதிப்பு = props->prop_மதிப்புகள்[i];
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    எனில் (found) {
        திரும்பு prop_மதிப்பு ? true : false;
    }
    திரும்பு false;
}

நிலையான bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool found = false;
    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC);
    எனில் (props) {
        க்கு (uint32_t i = 0; !found && i < props->மொத்தம்_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            எனில் (prop) {
                எனில் (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    திரும்பு found;
}

நிலையான வெறுமை KMSDRM_CrtcSetVrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    எனில் (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        திரும்பு;
    }

    KMSDRM_drmModeObjectSetProperty(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC, vrr_prop_id, enabled);
}

நிலையான bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool found = false;
    uint64_t prop_மதிப்பு = 0;

    எனில் (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        திரும்பு false;
    }

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CRTC);
    எனில் (props) {
        க்கு (uint32_t i = 0; !found && i < props->மொத்தம்_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            எனில் (prop) {
                எனில் (prop->prop_id == vrr_prop_id) {
                    prop_மதிப்பு = props->prop_மதிப்புகள்[i];
                    found = true;
                }
                KMSDRM_drmModeFreeProperty(prop);
            }
        }
        KMSDRM_drmModeFreeObjectProperties(props);
    }
    எனில் (found) {
        திரும்பு prop_மதிப்பு ? true : false;
    }
    திரும்பு false;
}

நிலையான முழு KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool found = false;
    முழு orientation = 0;

    drmModeObjectPropertiesPtr props = KMSDRM_drmModeObjectGetProperties(drm_fd, crtc_id, DRM_MODE_OBJECT_CONNECTOR);
    எனில் (props) {
        க்கு (uint32_t i = 0; !found && i < props->மொத்தம்_props; ++i) {
            drmModePropertyPtr prop = KMSDRM_drmModeGetProperty(drm_fd, props->props[i]);
            எனில் (prop) {
                எனில் (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_MODE_PROP_ENUM)) {
                    எனில் (prop->மொத்தம்_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        எனில் (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } இல்லையெனில் எனில் (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } இல்லையெனில் எனில் (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
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
    திரும்பு orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
நிலையான வெறுமை KMSDRM_AddDisplay(SDL_VideoDevice *_this, drmModeConnector *conn, drmModeRes *resources)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *dispdata = வெற்று;
    SDL_VideoDisplay display = { 0 };
    SDL_DisplayModeData *modedata = வெற்று;
    drmModeEncoder *encoder = வெற்று;
    drmModeCrtc *crtc = வெற்று;
    மாறிலி எழுத்து *connector_type = வெற்று;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    எழுத்து name_fmt[64];
    முழு orientation;
    முழு mode_index;
    முழு i, j;
    முழு ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_DisplayData *)SDL_calloc(1, அளவு(SDL_DisplayData));
    எனில் (!dispdata) {
        ret = -1;
        செல் cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = வெற்று;
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
    க்கு (i = 0; i < resources->மொத்தம்_encoders; i++) {
        encoder = KMSDRM_drmModeGetEncoder(viddata->drm_fd, resources->encoders[i]);

        எனில் (!encoder) {
            தொடர்;
        }

        எனில் (encoder->encoder_id == conn->encoder_id) {
            நிறுத்து;
        }

        KMSDRM_drmModeFreeEncoder(encoder);
        encoder = வெற்று;
    }

    எனில் (!encoder) {
        // No encoder was connected, find the first supported one
        க்கு (i = 0; i < resources->மொத்தம்_encoders; i++) {
            encoder = KMSDRM_drmModeGetEncoder(viddata->drm_fd,
                                               resources->encoders[i]);

            எனில் (!encoder) {
                தொடர்;
            }

            க்கு (j = 0; j < conn->மொத்தம்_encoders; j++) {
                எனில் (conn->encoders[j] == encoder->encoder_id) {
                    நிறுத்து;
                }
            }

            எனில் (j != conn->மொத்தம்_encoders) {
                நிறுத்து;
            }

            KMSDRM_drmModeFreeEncoder(encoder);
            encoder = வெற்று;
        }
    }

    எனில் (!encoder) {
        ret = SDL_SetError("No connected encoder found for connector.");
        செல் cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drmModeGetCrtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    எனில் (!crtc) {
        க்கு (i = 0; i < resources->மொத்தம்_crtcs; i++) {
            எனில் (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drmModeGetCrtc(viddata->drm_fd, encoder->crtc_id);
                நிறுத்து;
            }
        }
    }

    எனில் (!crtc) {
        ret = SDL_SetError("No CRTC found for connector.");
        செல் cleanup;
    }

    // Find the index of the mode attached to this CRTC
    mode_index = -1;

    க்கு (i = 0; i < conn->மொத்தம்_modes; i++) {
        drmModeModeInfo *mode = &conn->modes[i];

        எனில் (!SDL_memcmp(mode, &crtc->mode, அளவு(crtc->mode))) {
            mode_index = i;
            நிறுத்து;
        }
    }

    எனில் (mode_index == -1) {
        முழு current_area, largest_area = 0;

        // Find the preferred mode or the highest resolution mode
        க்கு (i = 0; i < conn->மொத்தம்_modes; i++) {
            drmModeModeInfo *mode = &conn->modes[i];

            எனில் (mode->type & DRM_MODE_TYPE_PREFERRED) {
                mode_index = i;
                நிறுத்து;
            }

            current_area = mode->hdisplay * mode->vdisplay;
            எனில் (current_area > largest_area) {
                mode_index = i;
                largest_area = current_area;
            }
        }
        எனில் (mode_index != -1) {
            crtc->mode = conn->modes[mode_index];
        }
    }

    எனில் (mode_index == -1) {
        ret = SDL_SetError("Failed to find index of mode attached to the CRTC.");
        செல் cleanup;
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

    எனில் (dispdata->mode.hdisplay == 0 || dispdata->mode.vdisplay == 0) {
        ret = SDL_SetError("Couldn't get a valid connector videomode.");
        செல் cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    எனில் (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_CrtcSetVrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    எனில் (KMSDRM_drmModeGetConnectorTypeName) {
        connector_type = KMSDRM_drmModeGetConnectorTypeName(conn->connector_type);
        எனில் (connector_type == வெற்று) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, அளவு(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd, crtc->crtc_id, DRM_MODE_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->மொத்தம்_props, அளவு(*dispdata->crtc.props_info));
    எனில் (!dispdata->crtc.props_info) {
        ret = false;
        செல் cleanup;
    }

    க்கு (i = 0; i < dispdata->crtc.props->மொத்தம்_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drmModeObjectGetProperties(viddata->drm_fd, conn->connector_id, DRM_MODE_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->மொத்தம்_props, அளவு(*dispdata->connector.props_info));
    எனில் (!dispdata->connector.props_info) {
        ret = false;
        செல் cleanup;
    }

    க்கு (i = 0; i < dispdata->connector.props->மொத்தம்_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drmModeGetProperty(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, அளவு(SDL_DisplayModeData));

    எனில் (!modedata) {
        ret = -1;
        செல் cleanup;
    }

    modedata->mode_index = mode_index;

    display.internal = dispdata;
    display.desktop_mode.w = dispdata->mode.hdisplay;
    display.desktop_mode.h = dispdata->mode.vdisplay;
    CalculateRefreshRate(&dispdata->mode, &display.desktop_mode.refresh_rate_numerator, &display.desktop_mode.refresh_rate_denominator);
    display.desktop_mode.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_mode.internal = modedata;
    எனில் (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_AddVideoDisplay(&display, false);
    எனில் (!display_id) {
        ret = -1;
        செல் cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_Set_எண்_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_எண், orientation);

#ifdef DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#endif

cleanup:
    எனில் (encoder) {
        KMSDRM_drmModeFreeEncoder(encoder);
    }
    எனில் (ret) {
        // Error (complete) cleanup
        எனில் (dispdata) {
            எனில் (dispdata->connector.connector) {
                KMSDRM_drmModeFreeConnector(dispdata->connector.connector);
            }
            எனில் (dispdata->crtc.crtc) {
                KMSDRM_drmModeFreeCrtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

நிலையான வெறுமை KMSDRM_SortDisplays(SDL_VideoDevice *_this)
{
    மாறிலி எழுத்து *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    எனில் (name_hint) {
        எழுத்து *saveptr;
        எழுத்து *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(அளவு(SDL_VideoDisplay *) * _this->இலக்கம்_displays);

        எனில் (str && sorted_list) {
            முழு sorted_index = 0;

            // Sort the requested displays to the front of the list.
            மாறிலி எழுத்து *token = SDL_strtok_r(str, ",", &saveptr);
            போது (token) {
                க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    எனில் (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_index++] = d;
                        _this->displays[i] = வெற்று;
                        நிறுத்து;
                    }
                }

                token = SDL_strtok_r(வெற்று, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
                எனில் (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, அளவு(SDL_VideoDisplay *) * _this->இலக்கம்_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

நிலையான bool set_client_atomic_caps(முழு fd)
{
    எனில் (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        திரும்பு false;  // emergency escape hatch.
    } இல்லையெனில் எனில் (KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        திரும்பு false;  // no atomic modesetting support.
    } இல்லையெனில் எனில் (KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        திரும்பு false;  // no universal planes support.
    }
    திரும்பு true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
நிலையான bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;
    drmModeRes *resources = வெற்று;
    uint64_t async_pageflip = 0;
    முழு i;
    bool result = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (வெறுமை)SDL_snprintf(viddata->devpath, அளவு(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    எனில் (viddata->drm_fd < 0) {
        result = SDL_SetError("Could not open %s", viddata->devpath);
        செல் cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = set_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drmModeGetResources(viddata->drm_fd);
    எனில் (!resources) {
        result = SDL_SetError("drmModeGetResources(%d) failed", viddata->drm_fd);
        செல் cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    க்கு (i = 0; i < resources->மொத்தம்_connectors; i++) {
        drmModeConnector *conn = KMSDRM_drmModeGetConnector(viddata->drm_fd, resources->connectors[i]);
        எனில் (!conn) {
            தொடர்;
        }

        எனில் (conn->connection == DRM_MODE_CONNECTED && conn->மொத்தம்_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_AddDisplay(_this, conn, resources);
        } இல்லையெனில் {
            // If it's not, free it now.
            KMSDRM_drmModeFreeConnector(conn);
        }
    }

    // Have we added any SDL displays?
    எனில் (SDL_GetPrimaryDisplay() == 0) {
        result = SDL_SetError("No connected displays found.");
        செல் cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_SortDisplays(_this);

    // Determine if video hardware supports async pageflips.
    எனில் (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_PAGE_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    எனில் (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    எனில் (resources) {
        KMSDRM_drmModeFreeResources(resources);
    }
    எனில் (!result) {
        எனில் (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    திரும்பு result;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
நிலையான bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = _this->internal;
    bool result = true;

    // Reopen the FD if we weren't able to drop master on the original one
    எனில் (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        எனில் (viddata->drm_fd < 0) {
            திரும்பு SDL_SetError("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = set_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drmSetMaster(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    எனில் (!viddata->gbm_dev) {
        result = SDL_SetError("Couldn't create gbm device.");
    } இல்லையெனில் {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        result = setup_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        எனில் (!result) {
            SDL_SetError("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    திரும்பு result;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
நிலையான வெறுமை KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_DisplayData *dispdata)
{
    SDL_VideoData *viddata = _this->internal;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    எனில் (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = வெற்று;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    எனில் (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

நிலையான வெறுமை KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *windata = window->internal;
    SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
    முழு ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    எனில் (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#எனில் 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
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
        எனில் (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_SetError("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        எனில் (ret && (dispdata->crtc->mode_valid == 0)) {
            ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->buffer_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_mode);
        }
#endif

#எனில் 1
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

        எனில் (drm_atomic_commit(_this, dispdata, true, false)) {
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
    எனில் (ret && (dispdata->crtc.crtc->mode_valid == 0)) {
        ret = KMSDRM_drmModeSetCrtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->buffer_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_mode);
    }

    எனில் (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    எனில் (windata->bo) {
        எனில் (windata->bo != windata->next_bo) {
            KMSDRM_gbm_surface_release_buffer(windata->gs, windata->bo);
        }
        windata->bo = வெற்று;
    }

    எனில் (windata->next_bo) {
        KMSDRM_gbm_surface_release_buffer(windata->gs, windata->next_bo);
        windata->next_bo = வெற்று;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    எனில் (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    எனில் (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = வெற்று;
    }
}

நிலையான வெறுமை KMSDRM_GetModeToSet(SDL_Window *window, drmModeModeInfo *out_mode)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    SDL_DisplayData *dispdata = display->internal;

    எனில் (window->fullscreen_exclusive) {
        *out_mode = dispdata->fullscreen_mode;
    } இல்லையெனில் {
        drmModeModeInfo *mode = KMSDRM_GetClosestDisplayMode(display, window->windowed.w, window->windowed.h);
        எனில் (mode) {
            *out_mode = *mode;
        } இல்லையெனில் {
            *out_mode = dispdata->original_mode;
        }
    }
}

நிலையான வெறுமை KMSDRM_DirtySurfaces(SDL_Window *window)
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
    நிலையான மாறிலி கட்டமைப்பு { uint32_t fmt; மாறிலி எழுத்து *name; முழு r; முழு g; முழு b; முழு a; } gbm_formats[] = {
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
    எனில் (windata->gs) {
        KMSDRM_DestroySurfaces(_this, window);
    }

    bool tried_setting_format = false;
    மாறிலி uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    க்கு (முழு i = 0; i < SDL_arraysize(gbm_formats); i++) {
        மாறிலி uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        எனில் (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            தொடர்;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_GetModeToSet(window, &dispdata->mode);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->mode.hdisplay, dispdata->mode.vdisplay, surface_fmt, surface_flags);
        எனில் (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->mode.hdisplay, dispdata->mode.vdisplay, surface_fmt, 0);
        }
        எனில் (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_SetError("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            தொடர்;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_SetRequiredVisualId(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)windata->gs);
        எனில் (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = வெற்று;
            தொடர்;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        result = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        எனில் (!result) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            தொடர்;
        }

        _this->gl_config.red_size = gbm_formats[i].r;
        _this->gl_config.green_size = gbm_formats[i].g;
        _this->gl_config.blue_size = gbm_formats[i].b;
        _this->gl_config.alpha_size = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        result = true;

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, dispdata->mode.hdisplay, dispdata->mode.vdisplay);

        நிறுத்து;
    }

    SDL_assert(result || (windata->gs == வெற்று));

    எனில் (!result) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        எனில் (!tried_setting_format) {   // make sure there's an error string set.
            SDL_SetError("Could not find any supported GBM surface format.");
        }
    }

    திரும்பு result;
}

#ifdef SDL_உள்ளீடு_LINUXEV
நிலையான வெறுமை KMSDRM_ReleaseVT(வெறுமை *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_VideoData *viddata = _this->internal;
    முழு i;

    க்கு (i = 0; i < viddata->இலக்கம்_windows; i++) {
        SDL_Window *window = viddata->windows[i];
        எனில் (!(window->flags & SDL_WINDOW_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, window);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

நிலையான வெறுமை KMSDRM_AcquireVT(வெறுமை *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_VideoData *viddata = _this->internal;
    முழு i;

    KMSDRM_drmSetMaster(viddata->drm_fd);
    க்கு (i = 0; i < viddata->இலக்கம்_windows; i++) {
        SDL_Window *window = viddata->windows[i];
        எனில் (!(window->flags & SDL_WINDOW_VULKAN)) {
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
    எனில் (!KMSDRM_InitDisplays(_this)) {
        result = SDL_SetError("error getting KMSDRM displays information");
    }

#ifdef SDL_உள்ளீடு_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_SetVTSwitchCallbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#அல்லதெனில் defined(SDL_உள்ளீடு_WSCONS)
    SDL_WSCONS_Init();
#endif

    viddata->video_init = true;

    திரும்பு result;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
வெறுமை KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *viddata = _this->internal;

    KMSDRM_DeinitDisplays(_this);

#ifdef SDL_உள்ளீடு_LINUXEV
    SDL_EVDEV_SetVTSwitchCallbacks(வெற்று, வெற்று, வெற்று, வெற்று);
    SDL_EVDEV_Quit();
#அல்லதெனில் defined(SDL_உள்ளீடு_WSCONS)
    SDL_WSCONS_Quit();
#endif

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = வெற்று;
    viddata->max_windows = 0;
    viddata->இலக்கம்_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *dispdata = display->internal;
    drmModeConnector *conn = dispdata->connector.connector;
    SDL_DisplayMode mode;
    முழு i;

    க்கு (i = 0; i < conn->மொத்தம்_modes; i++) {
        SDL_DisplayModeData *modedata = SDL_calloc(1, அளவு(SDL_DisplayModeData));

        எனில் (modedata) {
            modedata->mode_index = i;
        }

        SDL_zero(mode);
        mode.w = conn->modes[i].hdisplay;
        mode.h = conn->modes[i].vdisplay;
        CalculateRefreshRate(&conn->modes[i], &mode.refresh_rate_numerator, &mode.refresh_rate_denominator);
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        mode.internal = modedata;

        எனில் (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(modedata);
        }
    }
    திரும்பு true;
}

bool KMSDRM_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *dispdata = display->internal;
    SDL_DisplayModeData *modedata = mode->internal;
    drmModeConnector *conn = dispdata->connector.connector;
    முழு i;

    // Don't do anything if we are in Vulkan mode.
    எனில் (viddata->vulkan_mode) {
        திரும்பு true;
    }

    எனில் (!modedata) {
        திரும்பு SDL_SetError("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_mode = conn->modes[modedata->mode_index];

    க்கு (i = 0; i < viddata->இலக்கம்_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    திரும்பு true;
}

வெறுமை KMSDRM_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windata = window->internal;
    SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
    SDL_VideoData *viddata;
    bool is_vulkan = window->flags & SDL_WINDOW_VULKAN; // Is this a VK window?
    unsigned முழு i, j;

    எனில் (!windata) {
        திரும்பு;
    }

    // restore vrr state
    KMSDRM_CrtcSetVrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    எனில் (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_GetVideoDisplayForWindow(window));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, window);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        எனில் (viddata->இலக்கம்_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            எனில் (_this->egl_data) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } இல்லையெனில் {

        // If we were in Vulkan mode, get out of it.
        எனில் (viddata->vulkan_mode) {
            viddata->vulkan_mode = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    க்கு (i = 0; i < viddata->இலக்கம்_windows; i++) {
        எனில் (viddata->windows[i] == window) {
            viddata->இலக்கம்_windows--;

            க்கு (j = i; j < viddata->இலக்கம்_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            நிறுத்து;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(window->internal);
    window->internal = வெற்று;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *windata = வெற்று;
    SDL_VideoData *viddata = _this->internal;
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    SDL_DisplayData *dispdata = display->internal;
    bool is_vulkan = window->flags & SDL_WINDOW_VULKAN; // Is this a VK window?
    bool vulkan_mode = viddata->vulkan_mode;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drmModeModeInfo *mode;
    bool result = true;

    // Allocate window internal data
    windata = (SDL_WindowData *)SDL_calloc(1, அளவு(SDL_WindowData));
    எனில் (!windata) {
        திரும்பு false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    window->internal = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_buffer = false;
    எனில் (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_BUFFER, false)) {
        windata->double_buffer = true;
    }

    எனில் (!is_vulkan && !vulkan_mode) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        window->flags |= SDL_WINDOW_OPENGL;

        எனில் (!(viddata->gbm_init)) {

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
            எனில் (!KMSDRM_GBMInit(_this, dispdata)) {
                திரும்பு SDL_SetError("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        எனில் (!_this->egl_data) {
            egl_display = (NativeDisplayType)_this->internal->gbm_dev;
            எனில் (!SDL_EGL_LoadLibrary(_this, வெற்று, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_version = 2;
                _this->gl_config.minor_version = 0;
                எனில் (!SDL_EGL_LoadLibrary(_this, வெற்று, egl_display)) {
                    திரும்பு SDL_SetError("Can't load EGL/GL library on window creation.");
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

        எனில் (mode) {
            dispdata->fullscreen_mode = *mode;
        } இல்லையெனில் {
            dispdata->fullscreen_mode = dispdata->original_mode;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        எனில் (!KMSDRM_CreateSurfaces(_this, window)) {
            திரும்பு false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    எனில் (viddata->இலக்கம்_windows >= viddata->max_windows) {
        unsigned முழு new_max_windows = viddata->max_windows + 1;
        SDL_Window **new_windows = (SDL_Window **)SDL_realloc(viddata->windows,
                                                              new_max_windows * அளவு(SDL_Window *));
        எனில் (!new_windows) {
            திரும்பு false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->இலக்கம்_windows++] = window;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_mode = is_vulkan;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_KMSDRM_DEVICE_INDEX_எண், viddata->devindex);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_KMSDRM_DRM_FD_எண், viddata->drm_fd);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_KMSDRM_GBM_DEVICE_POINTER, viddata->gbm_dev);

    எனில் ((window->flags & SDL_WINDOW_NOT_FOCUSABLE) == 0) {
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
    திரும்பு result;
}

வெறுமை KMSDRM_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool KMSDRM_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    திரும்பு SDL_Unsupported();
}
வெறுமை KMSDRM_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    எனில் (!viddata->vulkan_mode) {
        KMSDRM_DirtySurfaces(window);
    }
}
SDL_FullscreenResult KMSDRM_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_VideoData *viddata = _this->internal;
    எனில் (!viddata->vulkan_mode) {
        KMSDRM_DirtySurfaces(window);
    }
    திரும்பு SDL_FULLSCREEN_SUCCEEDED;
}
வெறுமை KMSDRM_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை KMSDRM_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை KMSDRM_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை KMSDRM_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை KMSDRM_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை KMSDRM_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool KMSDRM_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    திரும்பு true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
