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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#అన్తర్భావ "../SDL_egl_c.h"

// SDL internals
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ "../../core/linux/SDL_evdev.h"
#లేదావేళ defined SDL_ఆదానం_WSCONS
#అన్తర్భావ "../../core/openbsd/SDL_wscons.h"
#అయితే_ముగింపు

// KMS/DRM declarations
#అన్తర్భావ "SDL_kmsdrmdyn.h"
#అన్తర్భావ "SDL_kmsdrmevents.h"
#అన్తర్భావ "SDL_kmsdrmmouse.h"
#అన్తర్భావ "SDL_kmsdrmvideo.h"
#అన్తర్భావ "SDL_kmsdrmopengles.h"
#అన్తర్భావ "SDL_kmsdrmvulkan.h"
#అన్తర్భావ <dirent.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <poll.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <sys/stat.h>
#అన్తర్భావ <sys/utsname.h>

#నిర్వచితమైతే SDL_PLATFORM_OPENBSD
స్థిర bool moderndri = false;
#లేకపోతే
స్థిర bool moderndri = true;
#అయితే_ముగింపు

స్థిర అక్షరం kmsdrm_dri_మార్గం[16];
స్థిర పూర్ణాంకం kmsdrm_dri_pathsize = 0;
స్థిర అక్షరం kmsdrm_dri_devname[8];
స్థిర పూర్ణాంకం kmsdrm_dri_devnamesize = 0;
స్థిర అక్షరం kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#నిర్వచితం_కాకపోతే DRM_FORMAT_MOD_VENDOR_NONE
#నిర్వచించు DRM_FORMAT_MOD_VENDOR_NONE 0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే DRM_FORMAT_MOD_రేఖీయ
#నిర్వచించు DRM_FORMAT_MOD_రేఖీయ fourcc_mod_సంకేతం(NONE, 0)
#అయితే_ముగింపు

స్థిర పూర్ణాంకం get_driindex(శూన్య)
{
    పూర్ణాంకం అందుబాటు = -ENOENT;
    అక్షరం device[పరిమాణం(kmsdrm_dri_cardpath)];
    పూర్ణాంకం drm_fd;
    పూర్ణాంకం i;
    పూర్ణాంకం devindex = -1;
    DIR *folder;
    స్థిరరాశి అక్షరం *hint;
    నిర్మాణం dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_సూచీ);
    ఒకవేళ (hint && *hint) {
        అక్షరం *endptr = ఖాళీ;
        స్థిరరాశి పూర్ణాంకం idx = (పూర్ణాంకం)SDL_strtol(hint, &endptr, 10);
        ఒకవేళ ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            తిరిగి idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_మార్గం, పరిమాణం(device));
    folder = opendir(device);
    ఒకవేళ (!folder) {
        SDL_సమితి_Error("Failed to open directory '%s'", device);
        తిరిగి -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                పరిమాణం(device) - kmsdrm_dri_pathsize);
    అయితే((res = readdir(folder)) != ఖాళీ && అందుబాటు < 0) {
        ఒకవేళ (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        పరిమాణం(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            ఒకవేళ (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                ఒకవేళ (SDL_KMSDRM_ఎక్కించు_Symbols()) {
                    drm_బహుళకం_Res *resources = KMSDRM_drm_బహుళకం_Get_Resources(drm_fd);
                    ఒకవేళ (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->లెక్క_connectors,
                                     resources->లెక్క_encoders,
                                     resources->లెక్క_crtcs);

                        ఒకవేళ (resources->లెక్క_connectors > 0 &&
                            resources->లెక్క_encoders > 0 &&
                            resources->లెక్క_crtcs > 0) {
                            అందుబాటు = -ENOENT;
                            కొరకు (i = 0; i < resources->లెక్క_connectors && అందుబాటు < 0; i++) {
                                drm_బహుళకం_Connector *conn =
                                    KMSDRM_drm_బహుళకం_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                ఒకవేళ (!conn) {
                                    కొనసాగు;
                                }

                                ఒకవేళ (conn->connection == DRM_బహుళకం_CONNECTED &&
                                    conn->లెక్క_modes) {
                                    bool access_denied = false;
                                    ఒకవేళ (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_సమితి_Master(drm_fd);
                                        ఒకవేళ (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    ఒకవేళ (!access_denied) {
                                        అందుబాటు = devindex;
                                    }
                                }

                                KMSDRM_drm_బహుళకం_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_బహుళకం_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } లేకపోతే {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    తిరిగి అందుబాటు;
}

స్థిర శూన్య Calculate_Refresh_రేటు(drm_బహుళకం_బహుళకం_Info *బహుళకం, పూర్ణాంకం *numerator, పూర్ణాంకం *denominator)
{
    *numerator = బహుళకం->clock * 1000;
    *denominator = బహుళకం->htotal * బహుళకం->vtotal;

    ఒకవేళ (బహుళకం->flags & DRM_బహుళకం_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    ఒకవేళ (బహుళకం->flags & DRM_బహుళకం_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    ఒకవేళ (బహుళకం->vscan > 1) {
        *denominator *= బహుళకం->vscan;
    }
}


పూర్ణాంకం కూడు_connector_property(drm_బహుళకం_Atomic_Req *req, KMSDRM_connector *conn, స్థిరరాశి అక్షరం *name, uint64_t విలువ)
{
    గుర్తులేని పూర్ణాంకం i;
    పూర్ణాంకం prop_id = 0;

    కొరకు (i = 0 ; i < conn->props->లెక్క_props ; i++) {
        ఒకవేళ (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            ఆపు;
        }
    }

    ఒకవేళ (prop_id < 0) {
        SDL_సమితి_Error("no connector property: %s", name);
        తిరిగి -EINVAL;
    }

    తిరిగి KMSDRM_drm_బహుళకం_Atomic_కూడు_Property(req, conn->connector->connector_id, prop_id, విలువ);
}

పూర్ణాంకం కూడు_crtc_property(drm_బహుళకం_Atomic_Req *req, KMSDRM_crtc *c, స్థిరరాశి అక్షరం *name, uint64_t విలువ)
{
    గుర్తులేని పూర్ణాంకం i;
    పూర్ణాంకం prop_id = -1;

    కొరకు (i = 0 ; i < c->props->లెక్క_props ; i++) {
        ఒకవేళ (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            ఆపు;
        }
    }

    ఒకవేళ (prop_id < 0) {
        SDL_సమితి_Error("no crtc property: %s", name);
        తిరిగి -EINVAL;
    }

    తిరిగి KMSDRM_drm_బహుళకం_Atomic_కూడు_Property(req, c->crtc->crtc_id, prop_id, విలువ);
}

పూర్ణాంకం కూడు_plane_property(drm_బహుళకం_Atomic_Req *req, KMSDRM_plane *p, స్థిరరాశి అక్షరం *name, uint64_t విలువ)
{
    గుర్తులేని పూర్ణాంకం i;
    పూర్ణాంకం prop_id = -1;

    కొరకు (i = 0 ; i < p->props->లెక్క_props ; i++) {
        ఒకవేళ (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            ఆపు;
        }
    }

    ఒకవేళ (prop_id < 0) {
        SDL_సమితి_Error("no plane property: %s", name);
        తిరిగి -EINVAL;
    }

    తిరిగి KMSDRM_drm_బహుళకం_Atomic_కూడు_Property(req, p->plane->plane_id, prop_id, విలువ);
}

#నిర్వచితమైతే DEBUG_KMSDRM
స్థిర శూన్య print_plane_info(SDL_VideoDevice *_this, drm_బహుళకం_Plane_Ptr plane)
{
    SDL_Video_దత్తాంశం *viddata = ((SDL_Video_దత్తాంశం *)_this->అంతర్గత);
    drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_బహుళకం_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    కొరకు (పూర్ణాంకం i = 0; i < props->లెక్క_props; i++) {
        drm_బహుళకం_Property_Ptr p = KMSDRM_drm_బహుళకం_Get_Property(viddata->drm_fd, props->props[i]);
        ఒకవేళ ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_విలువలు[i];
        }

        KMSDRM_drm_బహుళకం_Free_Property(p);
    }

    అక్షరం *plane_type = "unknown";
    ఎంపిక (type) {
        స్థితి DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            ఆపు;

        స్థితి DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            ఆపు;

        స్థితి DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            ఆపు;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_బహుళకం_Res *resources = KMSDRM_drm_బహుళకం_Get_Resources(viddata->drm_fd);
    ఒకవేళ (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        కొరకు (పూర్ణాంకం i = 0; i < resources->లెక్క_crtcs; i++) {
            ఒకవేళ (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                ఆపు;
            }
        }
        SDL_Log("%s\n\n", (స్థిరరాశి అక్షరం *)SDL_Get_సూచిక_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_జ్ఞాపకం_సూచిక, ""));
        SDL_CloseIO(io);
    }
}

స్థిర శూన్య get_planes_info(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata)
{
    SDL_Video_దత్తాంశం *viddata = ((SDL_Video_దత్తాంశం *)_this->అంతర్గత);

    drm_బహుళకం_Plane_Res_Ptr plane_resources = KMSDRM_drm_బహుళకం_Get_Plane_Resources(viddata->drm_fd);
    ఒకవేళ (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        తిరిగి;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->లెక్క_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    కొరకు (uint32_t i = 0; (i < plane_resources->లెక్క_planes); i++) {
        స్థిరరాశి uint32_t plane_id = plane_resources->planes[i];

        drm_బహుళకం_Plane_Ptr plane = KMSDRM_drm_బహుళకం_Get_Plane(viddata->drm_fd, plane_id);
        ఒకవేళ (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            కొనసాగు;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_బహుళకం_Free_Plane(plane);
    }

    KMSDRM_drm_బహుళకం_Free_Plane_Resources(plane_resources);
}
#అయితే_ముగింపు

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
స్థిర పూర్ణాంకం get_plane_id(SDL_VideoDevice *_this, గుర్తులేని పూర్ణాంకం crtc_id, uint32_t plane_type)
{
    drm_బహుళకం_Res *resources = ఖాళీ;
    drm_బహుళకం_Plane_Res_Ptr plane_resources = ఖాళీ;
    uint32_t i, j;
    గుర్తులేని పూర్ణాంకం crtc_సూచీ = 0;
    పూర్ణాంకం ret = -EINVAL;
    పూర్ణాంకం దొరికింది = 0;

    SDL_Video_దత్తాంశం *viddata = ((SDL_Video_దత్తాంశం *)_this->అంతర్గత);

    resources = KMSDRM_drm_బహుళకం_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    కొరకు (i = 0; i < resources->లెక్క_crtcs; i++) {
        ఒకవేళ (resources->crtcs[i] == crtc_id) {
            crtc_సూచీ = i;
            ఆపు;
        }
    }

    plane_resources = KMSDRM_drm_బహుళకం_Get_Plane_Resources(viddata->drm_fd);
    ఒకవేళ (!plane_resources) {
        తిరిగి SDL_సమితి_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    కొరకు (i = 0; (i < plane_resources->లెక్క_planes) && !దొరికింది; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_బహుళకం_Plane_Ptr plane = KMSDRM_drm_బహుళకం_Get_Plane(viddata->drm_fd, plane_id);
        ఒకవేళ (!plane) {
            కొనసాగు;
        }

        /* See if the current CRTC is available for this plane. */
        ఒకవేళ (plane->possible_crtcs & (1 << crtc_సూచీ)) {

            drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_బహుళకం_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            కొరకు (j = 0; j < props->లెక్క_props; j++) {

                drm_బహుళకం_Property_Ptr p = KMSDRM_drm_బహుళకం_Get_Property(viddata->drm_fd,
                    props->props[j]);

                ఒకవేళ ((SDL_strcmp(p->name, "type") == 0) && (props->prop_విలువలు[j] == plane_type)) {
                    /* found our plane, use that: */
                    దొరికింది = 1;
                }

                KMSDRM_drm_బహుళకం_Free_Property(p);
            }

            KMSDRM_drm_బహుళకం_Free_Object_Properties(props);
        }

        KMSDRM_drm_బహుళకం_Free_Plane(plane);
    }

    KMSDRM_drm_బహుళకం_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_బహుళకం_Free_Resources(resources);

    తిరిగి ret;
}

/* Setup a plane and it's props. */
bool అమరిక_plane(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_దత్తాంశం *viddata = ((SDL_Video_దత్తాంశం *)_this->అంతర్గత);
    bool ret = true;

    *_plane = SDL_calloc(1, పరిమాణం(**_plane));
    ఒకవేళ (!(*_plane)) {
        ret = false;
        వెళ్ళు cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    ఒకవేళ (!plane_id) {
        ret = SDL_సమితి_Error("Invalid Plane ID");
        వెళ్ళు cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_బహుళకం_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    ఒకవేళ ((*_plane)->plane) {
        గుర్తులేని పూర్ణాంకం i;
        (*_plane)->props = KMSDRM_drm_బహుళకం_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_బహుళకం_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->లెక్క_props, పరిమాణం(*(*_plane)->props_info));

        ఒకవేళ ( !((*_plane)->props_info) ) {
            ret = false;
            వెళ్ళు cleanup;
        }

        కొరకు (i = 0; i < (*_plane)->props->లెక్క_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_బహుళకం_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    ఒకవేళ (!ret) {
        ఒకవేళ (*_plane) {
            SDL_free(*_plane);
            *_plane = ఖాళీ;
        }
    }
    తిరిగి ret;
}

/* Free a plane and it's props. */
శూన్య free_plane(KMSDRM_plane **_plane)
{
    ఒకవేళ (*_plane) {
        ఒకవేళ ((*_plane)->plane) {
            KMSDRM_drm_బహుళకం_Free_Plane((*_plane)->plane);
            (*_plane)->plane = ఖాళీ;
        }
        ఒకవేళ ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = ఖాళీ;
        }
        SDL_free(*_plane);
        *_plane = ఖాళీ;
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
శూన్య
drm_atomic_సమితి_plane_props(SDL_Display_దత్తాంశం *dispdata, నిర్మాణం KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    ఒకవేళ (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_బహుళకం_Atomic_Alloc();
    }

    కూడు_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    కూడు_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

పూర్ణాంకం drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_దత్తాంశం *viddata = ((SDL_Video_దత్తాంశం *)_this->అంతర్గత);
    uint32_t atomic_flags = 0;
    పూర్ణాంకం ret;

    ఒకవేళ (!blocking) {
        atomic_flags |= DRM_బహుళకం_ATOMIC_NONBLOCK;
    }

    ఒకవేళ (allow_modeset) {
        atomic_flags |= DRM_బహుళకం_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_బహుళకం_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, ఖాళీ);

    ఒకవేళ (ret) {
        SDL_సమితి_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#ఒకవేళ 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#అయితే_ముగింపు
        వెళ్ళు బహిర్గతం;
    }

    ఒకవేళ (dispdata->kms_లోపల_fence_fd != -1) {
        close(dispdata->kms_లోపల_fence_fd);
        dispdata->kms_లోపల_fence_fd = -1;
    }

బహిర్గతం:
    KMSDRM_drm_బహుళకం_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = ఖాళీ;

    తిరిగి ret;
}

శూన్య
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    ఒకవేళ (dispdata->kms_fence) {
       EGLint స్థితి_2;

        చేయి {
            స్థితి_2 = _this->egl_దత్తాంశం->eglClientWaitSyncKHR(_this->egl_దత్తాంశం->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } అయితే (స్థితి_2 != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_దత్తాంశం->eglDestroySyncKHR(_this->egl_దత్తాంశం->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = ఖాళీ;
    }
}

స్థిర bool KMSDRM_అందుబాటు(శూన్య)
{
#నిర్వచితమైతే SDL_PLATFORM_OPENBSD
    నిర్మాణం utsname nameofsystem;
    ద్విగుణ releaseversion;
#అయితే_ముగింపు
    పూర్ణాంకం ret = -ENOENT;

#నిర్వచితమైతే SDL_PLATFORM_OPENBSD
    ఒకవేళ (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        ఒకవేళ (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (moderndri) {
        SDL_strlcpy(kmsdrm_dri_మార్గం, "/dev/dri/", పరిమాణం(kmsdrm_dri_మార్గం));
        SDL_strlcpy(kmsdrm_dri_devname, "card", పరిమాణం(kmsdrm_dri_devname));
    } లేకపోతే {
        SDL_strlcpy(kmsdrm_dri_మార్గం, "/dev/", పరిమాణం(kmsdrm_dri_మార్గం));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", పరిమాణం(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_మార్గం);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (శూన్య)SDL_snprintf(kmsdrm_dri_cardpath, పరిమాణం(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_మార్గం, kmsdrm_dri_devname);

    ret = get_driindex();
    ఒకవేళ (ret >= 0) {
        తిరిగి true;
    }

    తిరిగి false;
}

స్థిర శూన్య KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    ఒకవేళ (device->అంతర్గత) {
        SDL_free(device->అంతర్గత);
        device->అంతర్గత = ఖాళీ;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

స్థిర SDL_VideoDevice *KMSDRM_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *viddata;
    పూర్ణాంకం devindex;

    ఒకవేళ (!KMSDRM_అందుబాటు()) {
        తిరిగి ఖాళీ;
    }

    devindex = get_driindex();
    ఒకవేళ (devindex < 0) {
        SDL_సమితి_Error("devindex (%d) must not be negative.", devindex);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!SDL_KMSDRM_ఎక్కించు_Symbols()) {
        తిరిగి ఖాళీ;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    viddata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!viddata) {
        వెళ్ళు cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->అంతర్గత = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->సమితి_Display_బహుళకం = KMSDRM_సమితి_Display_బహుళకం;
    device->CreateSDLWindow = KMSDRM_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = KMSDRM_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = KMSDRM_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = KMSDRM_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Fullscreen = KMSDRM_సమితి_కిటికీ_Fullscreen;
    device->Show_కిటికీ = KMSDRM_Show_కిటికీ;
    device->Hide_కిటికీ = KMSDRM_Hide_కిటికీ;
    device->Raise_కిటికీ = KMSDRM_Raise_కిటికీ;
    device->Maximize_కిటికీ = KMSDRM_Maximize_కిటికీ;
    device->Minimize_కిటికీ = KMSDRM_Minimize_కిటికీ;
    device->Restore_కిటికీ = KMSDRM_Restore_కిటికీ;
    device->Destroy_కిటికీ = KMSDRM_Destroy_కిటికీ;
    device->సమితి_కిటికీ_Focusable = KMSDRM_సమితి_కిటికీ_Focusable;

    device->GL_ఎక్కించు_Library = KMSDRM_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = KMSDRM_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = KMSDRM_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = KMSDRM_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = KMSDRM_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_సమితి_Default_Profile_Config = KMSDRM_GLES_సమితి_Default_Profile_Config;

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = KMSDRM_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#అయితే_ముగింపు

    device->PumpEvents = KMSDRM_PumpEvents;
    device->విడుదల = KMSDRM_DeleteDevice;

    తిరిగి device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    తిరిగి ఖాళీ;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

స్థిర శూన్య KMSDRM_FBDestroyCallback(నిర్మాణం gbm_bo *bo, శూన్య *దత్తాంశం)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)దత్తాంశం;

    ఒకవేళ (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_బహుళకం_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, నిర్మాణం gbm_bo *bo)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    గుర్తులేని w, h;
    పూర్ణాంకం rc = -1;
    పూర్ణాంకం అంకె_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_దత్తాంశం(bo);

    ఒకవేళ (fb_info) {
        తిరిగి fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, పరిమాణం(KMSDRM_FBInfo));

    ఒకవేళ (!fb_info) {
        తిరిగి ఖాళీ;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_వెడల్పు(bo);
    h = KMSDRM_gbm_bo_get_ఎత్తు(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    ఒకవేళ (KMSDRM_drm_బహుళకం_కూడు_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_లెక్క &&
        KMSDRM_gbm_bo_get_స్థానభ్రంశం &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        అంకె_planes = KMSDRM_gbm_bo_get_plane_లెక్క(bo);
        కొరకు (పూర్ణాంకం i = 0; i < అంకె_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_స్థానభ్రంశం(bo, i);
            modifiers[i] = modifiers[0];
        }

        ఒకవేళ (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_బహుళకం_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_బహుళకం_కూడు_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    ఒకవేళ (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_బహుళకం_కూడు_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    ఒకవేళ (rc < 0) {
        SDL_free(fb_info);
        తిరిగి ఖాళీ;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (శూన్య *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_సమితి_user_దత్తాంశం(bo, fb_info, KMSDRM_FBDestroyCallback);

    తిరిగి fb_info;
}

స్థిర శూన్య KMSDRM_FlipHandler(పూర్ణాంకం fd, గుర్తులేని పూర్ణాంకం చట్రం, గుర్తులేని పూర్ణాంకం sec, గుర్తులేని పూర్ణాంకం usec, శూన్య *దత్తాంశం)
{
    *((bool *)దత్తాంశం) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windata)
{

    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    drmEventContext ev = { 0 };
    నిర్మాణం pollfd pfd = { 0 };
    పూర్ణాంకం ret;

    ev.సంస్కరణ = DRM_EVENT_CONTEXT_సంస్కరణ;
    ev.పుట_flip_handler = KMSDRM_FlipHandler;

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
    అయితే (windata->నిరీక్షణ_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        ఒకవేళ (ret < 0) {
            ఒకవేళ (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                కొనసాగు;
            } లేకపోతే {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                తిరిగి false;
            }
        }

        ఒకవేళ (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            తిరిగి false;
        }

        ఒకవేళ (pfd.revents & POLLIN) {
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

    తిరిగి true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
స్థిర drm_బహుళకం_బహుళకం_Info *KMSDRM_Get_Closest_Display_బహుళకం(SDL_VideoDisplay *display, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{

    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    drm_బహుళకం_Connector *conn = dispdata->connector.connector;

    SDL_Display_బహుళకం closest;
    drm_బహుళకం_బహుళకం_Info *drm_బహుళకం;

    ఒకవేళ (SDL_Get_Closest_Fullscreen_Display_బహుళకం(display->id, వెడల్పు, ఎత్తు, 0.0f, false, &closest)) {
        స్థిరరాశి SDL_Display_బహుళకం_దత్తాంశం *modedata = closest.అంతర్గత;
        drm_బహుళకం = &conn->modes[modedata->బహుళకం_సూచీ];
        తిరిగి drm_బహుళకం;
    } లేకపోతే {
        తిరిగి ఖాళీ;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

స్థిర bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;

    ఒకవేళ (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_సమితి_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_సమితి_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    ఒకవేళ (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        తిరిగి true;
    }

    తిరిగి KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
స్థిర శూన్య KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_DisplayID *displays;
    SDL_Display_దత్తాంశం *dispdata;
    పూర్ణాంకం i;

    displays = SDL_GetDisplays(ఖాళీ);
    ఒకవేళ (displays) {
        // Iterate on the SDL Display list.
        కొరకు (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_దత్తాంశం(displays[i]);

            // Free connector
            ఒకవేళ (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_బహుళకం_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = ఖాళీ;
            }

            // Free CRTC
            ఒకవేళ (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_బహుళకం_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = ఖాళీ;
            }
        }
        SDL_free(displays);
    }

    ఒకవేళ (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

స్థిర bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool దొరికింది = false;
    uint64_t prop_విలువ = 0;

    drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(drm_fd, output_id, DRM_బహుళకం_OBJECT_CONNECTOR);
    ఒకవేళ (props) {
        కొరకు (uint32_t i = 0; !దొరికింది && i < props->లెక్క_props; ++i) {
            drm_బహుళకం_Property_Ptr prop = KMSDRM_drm_బహుళకం_Get_Property(drm_fd, props->props[i]);
            ఒకవేళ (prop) {
                ఒకవేళ (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_విలువ = props->prop_విలువలు[i];
                    దొరికింది = true;
                }
                KMSDRM_drm_బహుళకం_Free_Property(prop);
            }
        }
        KMSDRM_drm_బహుళకం_Free_Object_Properties(props);
    }
    ఒకవేళ (దొరికింది) {
        తిరిగి prop_విలువ ? true : false;
    }
    తిరిగి false;
}

స్థిర bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool దొరికింది = false;
    drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(drm_fd, crtc_id, DRM_బహుళకం_OBJECT_CRTC);
    ఒకవేళ (props) {
        కొరకు (uint32_t i = 0; !దొరికింది && i < props->లెక్క_props; ++i) {
            drm_బహుళకం_Property_Ptr prop = KMSDRM_drm_బహుళకం_Get_Property(drm_fd, props->props[i]);
            ఒకవేళ (prop) {
                ఒకవేళ (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    దొరికింది = true;
                }
                KMSDRM_drm_బహుళకం_Free_Property(prop);
            }
        }
        KMSDRM_drm_బహుళకం_Free_Object_Properties(props);
    }
    తిరిగి దొరికింది;
}

స్థిర శూన్య KMSDRM_Crtc_సమితి_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    ఒకవేళ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        తిరిగి;
    }

    KMSDRM_drm_బహుళకం_Object_సమితి_Property(drm_fd, crtc_id, DRM_బహుళకం_OBJECT_CRTC, vrr_prop_id, enabled);
}

స్థిర bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool దొరికింది = false;
    uint64_t prop_విలువ = 0;

    ఒకవేళ (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        తిరిగి false;
    }

    drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(drm_fd, crtc_id, DRM_బహుళకం_OBJECT_CRTC);
    ఒకవేళ (props) {
        కొరకు (uint32_t i = 0; !దొరికింది && i < props->లెక్క_props; ++i) {
            drm_బహుళకం_Property_Ptr prop = KMSDRM_drm_బహుళకం_Get_Property(drm_fd, props->props[i]);
            ఒకవేళ (prop) {
                ఒకవేళ (prop->prop_id == vrr_prop_id) {
                    prop_విలువ = props->prop_విలువలు[i];
                    దొరికింది = true;
                }
                KMSDRM_drm_బహుళకం_Free_Property(prop);
            }
        }
        KMSDRM_drm_బహుళకం_Free_Object_Properties(props);
    }
    ఒకవేళ (దొరికింది) {
        తిరిగి prop_విలువ ? true : false;
    }
    తిరిగి false;
}

స్థిర పూర్ణాంకం KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool దొరికింది = false;
    పూర్ణాంకం orientation = 0;

    drm_బహుళకం_Object_Properties_Ptr props = KMSDRM_drm_బహుళకం_Object_Get_Properties(drm_fd, crtc_id, DRM_బహుళకం_OBJECT_CONNECTOR);
    ఒకవేళ (props) {
        కొరకు (uint32_t i = 0; !దొరికింది && i < props->లెక్క_props; ++i) {
            drm_బహుళకం_Property_Ptr prop = KMSDRM_drm_బహుళకం_Get_Property(drm_fd, props->props[i]);
            ఒకవేళ (prop) {
                ఒకవేళ (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_బహుళకం_PROP_ENUM)) {
                    ఒకవేళ (prop->లెక్క_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        ఒకవేళ (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } లేకపోతే ఒకవేళ (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } లేకపోతే ఒకవేళ (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    దొరికింది = true;
                }
                KMSDRM_drm_బహుళకం_Free_Property(prop);
            }
        }
        KMSDRM_drm_బహుళకం_Free_Object_Properties(props);
    }
    తిరిగి orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
స్థిర శూన్య KMSDRM_కూడు_Display(SDL_VideoDevice *_this, drm_బహుళకం_Connector *conn, drm_బహుళకం_Res *resources)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *dispdata = ఖాళీ;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_బహుళకం_దత్తాంశం *modedata = ఖాళీ;
    drm_బహుళకం_Encoder *encoder = ఖాళీ;
    drm_బహుళకం_Crtc *crtc = ఖాళీ;
    స్థిరరాశి అక్షరం *connector_type = ఖాళీ;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    అక్షరం name_fmt[64];
    పూర్ణాంకం orientation;
    పూర్ణాంకం బహుళకం_సూచీ;
    పూర్ణాంకం i, j;
    పూర్ణాంకం ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_దత్తాంశం));
    ఒకవేళ (!dispdata) {
        ret = -1;
        వెళ్ళు cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = ఖాళీ;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_లోపల_fence_fd = -1;
    dispdata->kms_బహిర్గతం_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    కొరకు (i = 0; i < resources->లెక్క_encoders; i++) {
        encoder = KMSDRM_drm_బహుళకం_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        ఒకవేళ (!encoder) {
            కొనసాగు;
        }

        ఒకవేళ (encoder->encoder_id == conn->encoder_id) {
            ఆపు;
        }

        KMSDRM_drm_బహుళకం_Free_Encoder(encoder);
        encoder = ఖాళీ;
    }

    ఒకవేళ (!encoder) {
        // No encoder was connected, find the first supported one
        కొరకు (i = 0; i < resources->లెక్క_encoders; i++) {
            encoder = KMSDRM_drm_బహుళకం_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            ఒకవేళ (!encoder) {
                కొనసాగు;
            }

            కొరకు (j = 0; j < conn->లెక్క_encoders; j++) {
                ఒకవేళ (conn->encoders[j] == encoder->encoder_id) {
                    ఆపు;
                }
            }

            ఒకవేళ (j != conn->లెక్క_encoders) {
                ఆపు;
            }

            KMSDRM_drm_బహుళకం_Free_Encoder(encoder);
            encoder = ఖాళీ;
        }
    }

    ఒకవేళ (!encoder) {
        ret = SDL_సమితి_Error("No connected encoder found for connector.");
        వెళ్ళు cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_బహుళకం_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    ఒకవేళ (!crtc) {
        కొరకు (i = 0; i < resources->లెక్క_crtcs; i++) {
            ఒకవేళ (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_బహుళకం_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                ఆపు;
            }
        }
    }

    ఒకవేళ (!crtc) {
        ret = SDL_సమితి_Error("No CRTC found for connector.");
        వెళ్ళు cleanup;
    }

    // Find the index of the mode attached to this CRTC
    బహుళకం_సూచీ = -1;

    కొరకు (i = 0; i < conn->లెక్క_modes; i++) {
        drm_బహుళకం_బహుళకం_Info *బహుళకం = &conn->modes[i];

        ఒకవేళ (!SDL_memcmp(బహుళకం, &crtc->బహుళకం, పరిమాణం(crtc->బహుళకం))) {
            బహుళకం_సూచీ = i;
            ఆపు;
        }
    }

    ఒకవేళ (బహుళకం_సూచీ == -1) {
        పూర్ణాంకం current_area, అతిపెద్ద_area = 0;

        // Find the preferred mode or the highest resolution mode
        కొరకు (i = 0; i < conn->లెక్క_modes; i++) {
            drm_బహుళకం_బహుళకం_Info *బహుళకం = &conn->modes[i];

            ఒకవేళ (బహుళకం->type & DRM_బహుళకం_TYPE_PREFERRED) {
                బహుళకం_సూచీ = i;
                ఆపు;
            }

            current_area = బహుళకం->hdisplay * బహుళకం->vdisplay;
            ఒకవేళ (current_area > అతిపెద్ద_area) {
                బహుళకం_సూచీ = i;
                అతిపెద్ద_area = current_area;
            }
        }
        ఒకవేళ (బహుళకం_సూచీ != -1) {
            crtc->బహుళకం = conn->modes[బహుళకం_సూచీ];
        }
    }

    ఒకవేళ (బహుళకం_సూచీ == -1) {
        ret = SDL_సమితి_Error("Failed to find index of mode attached to the CRTC.");
        వెళ్ళు cleanup;
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
    dispdata->బహుళకం = crtc->బహుళకం;
    dispdata->original_బహుళకం = crtc->బహుళకం;
    dispdata->fullscreen_బహుళకం = crtc->బహుళకం;

    ఒకవేళ (dispdata->బహుళకం.hdisplay == 0 || dispdata->బహుళకం.vdisplay == 0) {
        ret = SDL_సమితి_Error("Couldn't get a valid connector videomode.");
        వెళ్ళు cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    ఒకవేళ (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_సమితి_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    ఒకవేళ (KMSDRM_drm_బహుళకం_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_బహుళకం_Get_Connector_Type_Name(conn->connector_type);
        ఒకవేళ (connector_type == ఖాళీ) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_బహుళకం_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_బహుళకం_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->లెక్క_props, పరిమాణం(*dispdata->crtc.props_info));
    ఒకవేళ (!dispdata->crtc.props_info) {
        ret = false;
        వెళ్ళు cleanup;
    }

    కొరకు (i = 0; i < dispdata->crtc.props->లెక్క_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_బహుళకం_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_బహుళకం_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_బహుళకం_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->లెక్క_props, పరిమాణం(*dispdata->connector.props_info));
    ఒకవేళ (!dispdata->connector.props_info) {
        ret = false;
        వెళ్ళు cleanup;
    }

    కొరకు (i = 0; i < dispdata->connector.props->లెక్క_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_బహుళకం_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));

    ఒకవేళ (!modedata) {
        ret = -1;
        వెళ్ళు cleanup;
    }

    modedata->బహుళకం_సూచీ = బహుళకం_సూచీ;

    display.అంతర్గత = dispdata;
    display.desktop_బహుళకం.w = dispdata->బహుళకం.hdisplay;
    display.desktop_బహుళకం.h = dispdata->బహుళకం.vdisplay;
    Calculate_Refresh_రేటు(&dispdata->బహుళకం, &display.desktop_బహుళకం.refresh_రేటు_numerator, &display.desktop_బహుళకం.refresh_రేటు_denominator);
    display.desktop_బహుళకం.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_బహుళకం.అంతర్గత = modedata;
    ఒకవేళ (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_కూడు_Video_Display(&display, false);
    ఒకవేళ (!display_id) {
        ret = -1;
        వెళ్ళు cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_సమితి_సంఖ్య_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_సంఖ్య, orientation);

#నిర్వచితమైతే DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#అయితే_ముగింపు

cleanup:
    ఒకవేళ (encoder) {
        KMSDRM_drm_బహుళకం_Free_Encoder(encoder);
    }
    ఒకవేళ (ret) {
        // Error (complete) cleanup
        ఒకవేళ (dispdata) {
            ఒకవేళ (dispdata->connector.connector) {
                KMSDRM_drm_బహుళకం_Free_Connector(dispdata->connector.connector);
            }
            ఒకవేళ (dispdata->crtc.crtc) {
                KMSDRM_drm_బహుళకం_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

స్థిర శూన్య KMSDRM_క్రమీకరించు_Displays(SDL_VideoDevice *_this)
{
    స్థిరరాశి అక్షరం *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ప్రాధాన్యత);

    ఒకవేళ (name_hint) {
        అక్షరం *saveptr;
        అక్షరం *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(పరిమాణం(SDL_VideoDisplay *) * _this->అంకె_displays);

        ఒకవేళ (str && sorted_list) {
            పూర్ణాంకం sorted_సూచీ = 0;

            // Sort the requested displays to the front of the list.
            స్థిరరాశి అక్షరం *token = SDL_strtok_r(str, ",", &saveptr);
            అయితే (token) {
                కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ఒకవేళ (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_సూచీ++] = d;
                        _this->displays[i] = ఖాళీ;
                        ఆపు;
                    }
                }

                token = SDL_strtok_r(ఖాళీ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
                ఒకవేళ (_this->displays[i]) {
                    sorted_list[sorted_సూచీ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, పరిమాణం(SDL_VideoDisplay *) * _this->అంకె_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

స్థిర bool సమితి_client_atomic_caps(పూర్ణాంకం fd)
{
    ఒకవేళ (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        తిరిగి false;  // emergency escape hatch.
    } లేకపోతే ఒకవేళ (KMSDRM_drm_సమితి_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        తిరిగి false;  // no atomic modesetting support.
    } లేకపోతే ఒకవేళ (KMSDRM_drm_సమితి_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_సమితి_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        తిరిగి false;  // no universal planes support.
    }
    తిరిగి true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
స్థిర bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    drm_బహుళకం_Res *resources = ఖాళీ;
    uint64_t async_pageflip = 0;
    పూర్ణాంకం i;
    bool ఫలితం = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (శూన్య)SDL_snprintf(viddata->devpath, పరిమాణం(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    ఒకవేళ (viddata->drm_fd < 0) {
        ఫలితం = SDL_సమితి_Error("Could not open %s", viddata->devpath);
        వెళ్ళు cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = సమితి_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_బహుళకం_Get_Resources(viddata->drm_fd);
    ఒకవేళ (!resources) {
        ఫలితం = SDL_సమితి_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        వెళ్ళు cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    కొరకు (i = 0; i < resources->లెక్క_connectors; i++) {
        drm_బహుళకం_Connector *conn = KMSDRM_drm_బహుళకం_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        ఒకవేళ (!conn) {
            కొనసాగు;
        }

        ఒకవేళ (conn->connection == DRM_బహుళకం_CONNECTED && conn->లెక్క_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_కూడు_Display(_this, conn, resources);
        } లేకపోతే {
            // If it's not, free it now.
            KMSDRM_drm_బహుళకం_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    ఒకవేళ (SDL_GetPrimaryDisplay() == 0) {
        ఫలితం = SDL_సమితి_Error("No connected displays found.");
        వెళ్ళు cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_క్రమీకరించు_Displays(_this);

    // Determine if video hardware supports async pageflips.
    ఒకవేళ (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_పుట_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    ఒకవేళ (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    ఒకవేళ (resources) {
        KMSDRM_drm_బహుళకం_Free_Resources(resources);
    }
    ఒకవేళ (!ఫలితం) {
        ఒకవేళ (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    తిరిగి ఫలితం;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
స్థిర bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    bool ఫలితం = true;

    // Reopen the FD if we weren't able to drop master on the original one
    ఒకవేళ (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        ఒకవేళ (viddata->drm_fd < 0) {
            తిరిగి SDL_సమితి_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = సమితి_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_సమితి_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    ఒకవేళ (!viddata->gbm_dev) {
        ఫలితం = SDL_సమితి_Error("Couldn't create gbm device.");
    } లేకపోతే {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        ఫలితం = అమరిక_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        ఒకవేళ (!ఫలితం) {
            SDL_సమితి_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    తిరిగి ఫలితం;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
స్థిర శూన్య KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_దత్తాంశం *dispdata)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    ఒకవేళ (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = ఖాళీ;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    ఒకవేళ (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

స్థిర శూన్య KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *windata = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *dispdata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    పూర్ణాంకం ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    ఒకవేళ (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#ఒకవేళ 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        కూడు_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        కూడు_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        కూడు_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_పుట_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_సమితి_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_బహుళకం_సమితి_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->బఫరు_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_బహుళకం);

        /* Issue atomic commit that is blocking and allows modesetting. */
        ఒకవేళ (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_సమితి_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        ఒకవేళ (ret && (dispdata->crtc->బహుళకం_valid == 0)) {
            ret = KMSDRM_drm_బహుళకం_సమితి_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->బఫరు_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_బహుళకం);
        }
#అయితే_ముగింపు

#ఒకవేళ 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->బఫరు_id;
        plane_info.src_w = dispdata->original_బహుళకం.hdisplay;
        plane_info.src_h = dispdata->original_బహుళకం.vdisplay;
        plane_info.crtc_w = dispdata->original_బహుళకం.hdisplay;
        plane_info.crtc_h = dispdata->original_బహుళకం.vdisplay;

        drm_atomic_సమితి_plane_props(dispdata, &plane_info);

        ఒకవేళ (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_సమితి_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#అయితే_ముగింపు

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_బహుళకం_సమితి_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->బఫరు_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_బహుళకం);

    // If we failed to set the original mode, try to set the connector preferred mode.
    ఒకవేళ (ret && (dispdata->crtc.crtc->బహుళకం_valid == 0)) {
        ret = KMSDRM_drm_బహుళకం_సమితి_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->బఫరు_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_బహుళకం);
    }

    ఒకవేళ (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    ఒకవేళ (windata->bo) {
        ఒకవేళ (windata->bo != windata->తదుపరి_bo) {
            KMSDRM_gbm_surface_release_బఫరు(windata->gs, windata->bo);
        }
        windata->bo = ఖాళీ;
    }

    ఒకవేళ (windata->తదుపరి_bo) {
        KMSDRM_gbm_surface_release_బఫరు(windata->gs, windata->తదుపరి_bo);
        windata->తదుపరి_bo = ఖాళీ;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    ఒకవేళ (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    ఒకవేళ (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = ఖాళీ;
    }
}

స్థిర శూన్య KMSDRM_Get_బహుళకం_గమ్యం_సమితి(SDL_కిటికీ *కిటికీ, drm_బహుళకం_బహుళకం_Info *బహిర్గతం_బహుళకం)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;

    ఒకవేళ (కిటికీ->fullscreen_exclusive) {
        *బహిర్గతం_బహుళకం = dispdata->fullscreen_బహుళకం;
    } లేకపోతే {
        drm_బహుళకం_బహుళకం_Info *బహుళకం = KMSDRM_Get_Closest_Display_బహుళకం(display, కిటికీ->windowed.w, కిటికీ->windowed.h);
        ఒకవేళ (బహుళకం) {
            *బహిర్గతం_బహుళకం = *బహుళకం;
        } లేకపోతే {
            *బహిర్గతం_బహుళకం = dispdata->original_బహుళకం;
        }
    }
}

స్థిర శూన్య KMSDRM_DirtySurfaces(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *windata = కిటికీ->అంతర్గత;
    drm_బహుళకం_బహుళకం_Info బహుళకం;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_బహుళకం_గమ్యం_సమితి(కిటికీ, &బహుళకం);
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, బహుళకం.hdisplay, బహుళకం.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    స్థిర స్థిరరాశి నిర్మాణం { uint32_t fmt; స్థిరరాశి అక్షరం *name; పూర్ణాంకం r; పూర్ణాంకం g; పూర్ణాంకం b; పూర్ణాంకం a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #నిర్వచించు FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #నిర్వచనం_రద్దు FMT
    };

    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *windata = కిటికీ->అంతర్గత;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    EGLContext egl_context;
    bool ఫలితం = false;

    // If the current window already has surfaces, destroy them before creating other.
    ఒకవేళ (windata->gs) {
        KMSDRM_DestroySurfaces(_this, కిటికీ);
    }

    bool tried_setting_format = false;
    స్థిరరాశి uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(gbm_formats); i++) {
        స్థిరరాశి uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        ఒకవేళ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            కొనసాగు;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_బహుళకం_గమ్యం_సమితి(కిటికీ, &dispdata->బహుళకం);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->బహుళకం.hdisplay, dispdata->బహుళకం.vdisplay, surface_fmt, surface_flags);
        ఒకవేళ (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->బహుళకం.hdisplay, dispdata->బహుళకం.vdisplay, surface_fmt, 0);
        }
        ఒకవేళ (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_సమితి_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            కొనసాగు;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_సమితి_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)windata->gs);
        ఒకవేళ (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = ఖాళీ;
            కొనసాగు;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        ఫలితం = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        ఒకవేళ (!ఫలితం) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            కొనసాగు;
        }

        _this->gl_config.red_కొలత = gbm_formats[i].r;
        _this->gl_config.green_కొలత = gbm_formats[i].g;
        _this->gl_config.blue_కొలత = gbm_formats[i].b;
        _this->gl_config.alpha_కొలత = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        ఫలితం = true;

        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, dispdata->బహుళకం.hdisplay, dispdata->బహుళకం.vdisplay);

        ఆపు;
    }

    SDL_assert(ఫలితం || (windata->gs == ఖాళీ));

    ఒకవేళ (!ఫలితం) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        ఒకవేళ (!tried_setting_format) {   // make sure there's an error string set.
            SDL_సమితి_Error("Could not find any supported GBM surface format.");
        }
    }

    తిరిగి ఫలితం;
}

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
స్థిర శూన్య KMSDRM_ReleaseVT(శూన్య *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < viddata->అంకె_windows; i++) {
        SDL_కిటికీ *కిటికీ = viddata->windows[i];
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, కిటికీ);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

స్థిర శూన్య KMSDRM_AcquireVT(శూన్య *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    పూర్ణాంకం i;

    KMSDRM_drm_సమితి_Master(viddata->drm_fd);
    కొరకు (i = 0; i < viddata->అంకె_windows; i++) {
        SDL_కిటికీ *కిటికీ = viddata->windows[i];
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, కిటికీ);
        }
    }
}
#అయితే_ముగింపు // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool ఫలితం = true;

    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    ఒకవేళ (!KMSDRM_InitDisplays(_this)) {
        ఫలితం = SDL_సమితి_Error("error getting KMSDRM displays information");
    }

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_సమితి_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#లేదావేళ defined(SDL_ఆదానం_WSCONS)
    SDL_WSCONS_Init();
#అయితే_ముగింపు

    viddata->video_init = true;

    తిరిగి ఫలితం;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
శూన్య KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;

    KMSDRM_DeinitDisplays(_this);

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_సమితి_VTSwitch_Callbacks(ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
    SDL_EVDEV_Quit();
#లేదావేళ defined(SDL_ఆదానం_WSCONS)
    SDL_WSCONS_Quit();
#అయితే_ముగింపు

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = ఖాళీ;
    viddata->max_windows = 0;
    viddata->అంకె_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    drm_బహుళకం_Connector *conn = dispdata->connector.connector;
    SDL_Display_బహుళకం బహుళకం;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < conn->లెక్క_modes; i++) {
        SDL_Display_బహుళకం_దత్తాంశం *modedata = SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));

        ఒకవేళ (modedata) {
            modedata->బహుళకం_సూచీ = i;
        }

        SDL_zero(బహుళకం);
        బహుళకం.w = conn->modes[i].hdisplay;
        బహుళకం.h = conn->modes[i].vdisplay;
        Calculate_Refresh_రేటు(&conn->modes[i], &బహుళకం.refresh_రేటు_numerator, &బహుళకం.refresh_రేటు_denominator);
        బహుళకం.format = SDL_PIXELFORMAT_ARGB8888;
        బహుళకం.అంతర్గత = modedata;

        ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం)) {
            SDL_free(modedata);
        }
    }
    తిరిగి true;
}

bool KMSDRM_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    SDL_Display_బహుళకం_దత్తాంశం *modedata = బహుళకం->అంతర్గత;
    drm_బహుళకం_Connector *conn = dispdata->connector.connector;
    పూర్ణాంకం i;

    // Don't do anything if we are in Vulkan mode.
    ఒకవేళ (viddata->vulkan_బహుళకం) {
        తిరిగి true;
    }

    ఒకవేళ (!modedata) {
        తిరిగి SDL_సమితి_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_బహుళకం = conn->modes[modedata->బహుళకం_సూచీ];

    కొరకు (i = 0; i < viddata->అంకె_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    తిరిగి true;
}

శూన్య KMSDRM_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *windata = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *dispdata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    SDL_Video_దత్తాంశం *viddata;
    bool is_vulkan = కిటికీ->flags & SDL_కిటికీ_VULKAN; // Is this a VK window?
    గుర్తులేని పూర్ణాంకం i, j;

    ఒకవేళ (!windata) {
        తిరిగి;
    }

    // restore vrr state
    KMSDRM_Crtc_సమితి_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    ఒకవేళ (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_కిటికీ(కిటికీ));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, కిటికీ);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        ఒకవేళ (viddata->అంకె_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            ఒకవేళ (_this->egl_దత్తాంశం) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } లేకపోతే {

        // If we were in Vulkan mode, get out of it.
        ఒకవేళ (viddata->vulkan_బహుళకం) {
            viddata->vulkan_బహుళకం = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    కొరకు (i = 0; i < viddata->అంకె_windows; i++) {
        ఒకవేళ (viddata->windows[i] == కిటికీ) {
            viddata->అంకె_windows--;

            కొరకు (j = i; j < viddata->అంకె_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            ఆపు;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(కిటికీ->అంతర్గత);
    కిటికీ->అంతర్గత = ఖాళీ;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *windata = ఖాళీ;
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    bool is_vulkan = కిటికీ->flags & SDL_కిటికీ_VULKAN; // Is this a VK window?
    bool vulkan_బహుళకం = viddata->vulkan_బహుళకం;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_బహుళకం_బహుళకం_Info *బహుళకం;
    bool ఫలితం = true;

    // Allocate window internal data
    windata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!windata) {
        తిరిగి false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    కిటికీ->అంతర్గత = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_బఫరు = false;
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_బఫరు, false)) {
        windata->double_బఫరు = true;
    }

    ఒకవేళ (!is_vulkan && !vulkan_బహుళకం) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        కిటికీ->flags |= SDL_కిటికీ_OPENGL;

        ఒకవేళ (!(viddata->gbm_init)) {

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
            ఒకవేళ (!KMSDRM_GBMInit(_this, dispdata)) {
                తిరిగి SDL_సమితి_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        ఒకవేళ (!_this->egl_దత్తాంశం) {
            egl_display = (NativeDisplayType)_this->అంతర్గత->gbm_dev;
            ఒకవేళ (!SDL_EGL_ఎక్కించు_Library(_this, ఖాళీ, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_సంస్కరణ = 2;
                _this->gl_config.minor_సంస్కరణ = 0;
                ఒకవేళ (!SDL_EGL_ఎక్కించు_Library(_this, ఖాళీ, egl_display)) {
                    తిరిగి SDL_సమితి_Error("Can't load EGL/GL library on window creation.");
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
        బహుళకం = KMSDRM_Get_Closest_Display_బహుళకం(display, కిటికీ->windowed.w, కిటికీ->windowed.h);

        ఒకవేళ (బహుళకం) {
            dispdata->fullscreen_బహుళకం = *బహుళకం;
        } లేకపోతే {
            dispdata->fullscreen_బహుళకం = dispdata->original_బహుళకం;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        ఒకవేళ (!KMSDRM_CreateSurfaces(_this, కిటికీ)) {
            తిరిగి false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    ఒకవేళ (viddata->అంకె_windows >= viddata->max_windows) {
        గుర్తులేని పూర్ణాంకం new_max_windows = viddata->max_windows + 1;
        SDL_కిటికీ **new_windows = (SDL_కిటికీ **)SDL_realloc(viddata->windows,
                                                              new_max_windows * పరిమాణం(SDL_కిటికీ *));
        ఒకవేళ (!new_windows) {
            తిరిగి false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->అంకె_windows++] = కిటికీ;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_బహుళకం = is_vulkan;

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_KMSDRM_DEVICE_సూచీ_సంఖ్య, viddata->devindex);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_KMSDRM_DRM_FD_సంఖ్య, viddata->drm_fd);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_KMSDRM_GBM_DEVICE_సూచిక, viddata->gbm_dev);

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_సమితి_Mouse_Focus(కిటికీ);
        SDL_సమితి_Keyboard_Focus(కిటికీ);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_కిటికీ(కిటికీ), &display_bounds);
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    తిరిగి ఫలితం;
}

శూన్య KMSDRM_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool KMSDRM_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_Unsupported();
}
శూన్య KMSDRM_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    ఒకవేళ (!viddata->vulkan_బహుళకం) {
        KMSDRM_DirtySurfaces(కిటికీ);
    }
}
SDL_Fullscreen_ఫలితం KMSDRM_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    ఒకవేళ (!viddata->vulkan_బహుళకం) {
        KMSDRM_DirtySurfaces(కిటికీ);
    }
    తిరిగి SDL_FULLSCREEN_SUCCEEDED;
}
శూన్య KMSDRM_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య KMSDRM_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య KMSDRM_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య KMSDRM_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య KMSDRM_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య KMSDRM_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool KMSDRM_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable)
{
    తిరిగి true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_KMSDRM
