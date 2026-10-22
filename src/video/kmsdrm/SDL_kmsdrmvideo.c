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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#अन्तर्भाव "../SDL_egl_c.h"

// SDL internals
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#नोचेद्यदि defined SDL_निवेशः_WSCONS
#अन्तर्भाव "../../core/openbsd/SDL_wscons.h"
#यदि_अन्तः

// KMS/DRM declarations
#अन्तर्भाव "SDL_kmsdrmdyn.h"
#अन्तर्भाव "SDL_kmsdrmevents.h"
#अन्तर्भाव "SDL_kmsdrmmouse.h"
#अन्तर्भाव "SDL_kmsdrmvideo.h"
#अन्तर्भाव "SDL_kmsdrmopengles.h"
#अन्तर्भाव "SDL_kmsdrmvulkan.h"
#अन्तर्भाव <dirent.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव <poll.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <sys/stat.h>
#अन्तर्भाव <sys/utsname.h>

#यदि_परिभाषितम् SDL_PLATFORM_OPENBSD
स्थिर bool moderndri = false;
#अन्यथा
स्थिर bool moderndri = true;
#यदि_अन्तः

स्थिर वर्ण kmsdrm_dri_मार्गः[16];
स्थिर पूर्णाङ्क kmsdrm_dri_pathsize = 0;
स्थिर वर्ण kmsdrm_dri_devname[8];
स्थिर पूर्णाङ्क kmsdrm_dri_devnamesize = 0;
स्थिर वर्ण kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#यदि_अपरिभाषितम् DRM_FORMAT_MOD_VENDOR_NONE
#परिभाषय DRM_FORMAT_MOD_VENDOR_NONE 0
#यदि_अन्तः
#यदि_अपरिभाषितम् DRM_FORMAT_MOD_रैखिकम्
#परिभाषय DRM_FORMAT_MOD_रैखिकम् fourcc_mod_संहिता(NONE, 0)
#यदि_अन्तः

स्थिर पूर्णाङ्क get_driindex(शून्य)
{
    पूर्णाङ्क उपलब्धम् = -ENOENT;
    वर्ण device[परिमाण(kmsdrm_dri_cardpath)];
    पूर्णाङ्क drm_fd;
    पूर्णाङ्क i;
    पूर्णाङ्क devindex = -1;
    DIR *folder;
    ध्रुव वर्ण *hint;
    संरचना dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_सूचकांक);
    यदि (hint && *hint) {
        वर्ण *endptr = रिक्त;
        ध्रुव पूर्णाङ्क idx = (पूर्णाङ्क)SDL_strtol(hint, &endptr, 10);
        यदि ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            प्रत्यागम idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_मार्गः, परिमाण(device));
    folder = opendir(device);
    यदि (!folder) {
        SDL_समुच्चयः_Error("Failed to open directory '%s'", device);
        प्रत्यागम -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                परिमाण(device) - kmsdrm_dri_pathsize);
    यावत्((res = readdir(folder)) != रिक्त && उपलब्धम् < 0) {
        यदि (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        परिमाण(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = उद्घाटय(device, O_RDWR | O_CLOEXEC);
            यदि (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                यदि (SDL_KMSDRM_आरोपय_Symbols()) {
                    drm_बहुलकम्_Res *resources = KMSDRM_drm_बहुलकम्_Get_Resources(drm_fd);
                    यदि (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->गणनम्_connectors,
                                     resources->गणनम्_encoders,
                                     resources->गणनम्_crtcs);

                        यदि (resources->गणनम्_connectors > 0 &&
                            resources->गणनम्_encoders > 0 &&
                            resources->गणनम्_crtcs > 0) {
                            उपलब्धम् = -ENOENT;
                            प्रति (i = 0; i < resources->गणनम्_connectors && उपलब्धम् < 0; i++) {
                                drm_बहुलकम्_Connector *conn =
                                    KMSDRM_drm_बहुलकम्_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                यदि (!conn) {
                                    अनुवर्त;
                                }

                                यदि (conn->connection == DRM_बहुलकम्_CONNECTED &&
                                    conn->गणनम्_modes) {
                                    bool access_denied = false;
                                    यदि (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_समुच्चयः_Master(drm_fd);
                                        यदि (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    यदि (!access_denied) {
                                        उपलब्धम् = devindex;
                                    }
                                }

                                KMSDRM_drm_बहुलकम्_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_बहुलकम्_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } अन्यथा {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    प्रत्यागम उपलब्धम्;
}

स्थिर शून्य Calculate_Refresh_दरः(drm_बहुलकम्_बहुलकम्_Info *बहुलकम्, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    *numerator = बहुलकम्->clock * 1000;
    *denominator = बहुलकम्->htotal * बहुलकम्->vtotal;

    यदि (बहुलकम्->flags & DRM_बहुलकम्_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    यदि (बहुलकम्->flags & DRM_बहुलकम्_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    यदि (बहुलकम्->vscan > 1) {
        *denominator *= बहुलकम्->vscan;
    }
}


पूर्णाङ्क सङ्कलय_connector_property(drm_बहुलकम्_Atomic_Req *req, KMSDRM_connector *conn, ध्रुव वर्ण *name, uint64_t मानम्)
{
    अचिह्नित पूर्णाङ्क i;
    पूर्णाङ्क prop_id = 0;

    प्रति (i = 0 ; i < conn->props->गणनम्_props ; i++) {
        यदि (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            भङ्ग;
        }
    }

    यदि (prop_id < 0) {
        SDL_समुच्चयः_Error("no connector property: %s", name);
        प्रत्यागम -EINVAL;
    }

    प्रत्यागम KMSDRM_drm_बहुलकम्_Atomic_सङ्कलय_Property(req, conn->connector->connector_id, prop_id, मानम्);
}

पूर्णाङ्क सङ्कलय_crtc_property(drm_बहुलकम्_Atomic_Req *req, KMSDRM_crtc *c, ध्रुव वर्ण *name, uint64_t मानम्)
{
    अचिह्नित पूर्णाङ्क i;
    पूर्णाङ्क prop_id = -1;

    प्रति (i = 0 ; i < c->props->गणनम्_props ; i++) {
        यदि (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            भङ्ग;
        }
    }

    यदि (prop_id < 0) {
        SDL_समुच्चयः_Error("no crtc property: %s", name);
        प्रत्यागम -EINVAL;
    }

    प्रत्यागम KMSDRM_drm_बहुलकम्_Atomic_सङ्कलय_Property(req, c->crtc->crtc_id, prop_id, मानम्);
}

पूर्णाङ्क सङ्कलय_plane_property(drm_बहुलकम्_Atomic_Req *req, KMSDRM_plane *p, ध्रुव वर्ण *name, uint64_t मानम्)
{
    अचिह्नित पूर्णाङ्क i;
    पूर्णाङ्क prop_id = -1;

    प्रति (i = 0 ; i < p->props->गणनम्_props ; i++) {
        यदि (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            भङ्ग;
        }
    }

    यदि (prop_id < 0) {
        SDL_समुच्चयः_Error("no plane property: %s", name);
        प्रत्यागम -EINVAL;
    }

    प्रत्यागम KMSDRM_drm_बहुलकम्_Atomic_सङ्कलय_Property(req, p->plane->plane_id, prop_id, मानम्);
}

#यदि_परिभाषितम् DEBUG_KMSDRM
स्थिर शून्य print_plane_info(SDL_VideoDevice *_this, drm_बहुलकम्_Plane_Ptr plane)
{
    SDL_Video_दत्त *viddata = ((SDL_Video_दत्त *)_this->आन्तरिकम्);
    drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_बहुलकम्_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    प्रति (पूर्णाङ्क i = 0; i < props->गणनम्_props; i++) {
        drm_बहुलकम्_Property_Ptr p = KMSDRM_drm_बहुलकम्_Get_Property(viddata->drm_fd, props->props[i]);
        यदि ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_मानानि[i];
        }

        KMSDRM_drm_बहुलकम्_Free_Property(p);
    }

    वर्ण *plane_type = "unknown";
    विकल्प (type) {
        पक्ष DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            भङ्ग;

        पक्ष DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            भङ्ग;

        पक्ष DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            भङ्ग;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_बहुलकम्_Res *resources = KMSDRM_drm_बहुलकम्_Get_Resources(viddata->drm_fd);
    यदि (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        प्रति (पूर्णाङ्क i = 0; i < resources->गणनम्_crtcs; i++) {
            यदि (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                भङ्ग;
            }
        }
        SDL_Log("%s\n\n", (ध्रुव वर्ण *)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_स्मृतिः_POINTER, ""));
        SDL_CloseIO(io);
    }
}

स्थिर शून्य get_planes_info(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata)
{
    SDL_Video_दत्त *viddata = ((SDL_Video_दत्त *)_this->आन्तरिकम्);

    drm_बहुलकम्_Plane_Res_Ptr plane_resources = KMSDRM_drm_बहुलकम्_Get_Plane_Resources(viddata->drm_fd);
    यदि (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        प्रत्यागम;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->गणनम्_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    प्रति (uint32_t i = 0; (i < plane_resources->गणनम्_planes); i++) {
        ध्रुव uint32_t plane_id = plane_resources->planes[i];

        drm_बहुलकम्_Plane_Ptr plane = KMSDRM_drm_बहुलकम्_Get_Plane(viddata->drm_fd, plane_id);
        यदि (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            अनुवर्त;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_बहुलकम्_Free_Plane(plane);
    }

    KMSDRM_drm_बहुलकम्_Free_Plane_Resources(plane_resources);
}
#यदि_अन्तः

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
स्थिर पूर्णाङ्क get_plane_id(SDL_VideoDevice *_this, अचिह्नित पूर्णाङ्क crtc_id, uint32_t plane_type)
{
    drm_बहुलकम्_Res *resources = रिक्त;
    drm_बहुलकम्_Plane_Res_Ptr plane_resources = रिक्त;
    uint32_t i, j;
    अचिह्नित पूर्णाङ्क crtc_सूचकांक = 0;
    पूर्णाङ्क ret = -EINVAL;
    पूर्णाङ्क प्राप्तम् = 0;

    SDL_Video_दत्त *viddata = ((SDL_Video_दत्त *)_this->आन्तरिकम्);

    resources = KMSDRM_drm_बहुलकम्_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    प्रति (i = 0; i < resources->गणनम्_crtcs; i++) {
        यदि (resources->crtcs[i] == crtc_id) {
            crtc_सूचकांक = i;
            भङ्ग;
        }
    }

    plane_resources = KMSDRM_drm_बहुलकम्_Get_Plane_Resources(viddata->drm_fd);
    यदि (!plane_resources) {
        प्रत्यागम SDL_समुच्चयः_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    प्रति (i = 0; (i < plane_resources->गणनम्_planes) && !प्राप्तम्; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_बहुलकम्_Plane_Ptr plane = KMSDRM_drm_बहुलकम्_Get_Plane(viddata->drm_fd, plane_id);
        यदि (!plane) {
            अनुवर्त;
        }

        /* See if the current CRTC is available for this plane. */
        यदि (plane->possible_crtcs & (1 << crtc_सूचकांक)) {

            drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_बहुलकम्_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            प्रति (j = 0; j < props->गणनम्_props; j++) {

                drm_बहुलकम्_Property_Ptr p = KMSDRM_drm_बहुलकम्_Get_Property(viddata->drm_fd,
                    props->props[j]);

                यदि ((SDL_strcmp(p->name, "type") == 0) && (props->prop_मानानि[j] == plane_type)) {
                    /* found our plane, use that: */
                    प्राप्तम् = 1;
                }

                KMSDRM_drm_बहुलकम्_Free_Property(p);
            }

            KMSDRM_drm_बहुलकम्_Free_Object_Properties(props);
        }

        KMSDRM_drm_बहुलकम्_Free_Plane(plane);
    }

    KMSDRM_drm_बहुलकम्_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_बहुलकम्_Free_Resources(resources);

    प्रत्यागम ret;
}

/* Setup a plane and it's props. */
bool सज्जता_plane(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_दत्त *viddata = ((SDL_Video_दत्त *)_this->आन्तरिकम्);
    bool ret = true;

    *_plane = SDL_calloc(1, परिमाण(**_plane));
    यदि (!(*_plane)) {
        ret = false;
        गच्छ cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    यदि (!plane_id) {
        ret = SDL_समुच्चयः_Error("Invalid Plane ID");
        गच्छ cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_बहुलकम्_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    यदि ((*_plane)->plane) {
        अचिह्नित पूर्णाङ्क i;
        (*_plane)->props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_बहुलकम्_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->गणनम्_props, परिमाण(*(*_plane)->props_info));

        यदि ( !((*_plane)->props_info) ) {
            ret = false;
            गच्छ cleanup;
        }

        प्रति (i = 0; i < (*_plane)->props->गणनम्_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_बहुलकम्_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    यदि (!ret) {
        यदि (*_plane) {
            SDL_free(*_plane);
            *_plane = रिक्त;
        }
    }
    प्रत्यागम ret;
}

/* Free a plane and it's props. */
शून्य free_plane(KMSDRM_plane **_plane)
{
    यदि (*_plane) {
        यदि ((*_plane)->plane) {
            KMSDRM_drm_बहुलकम्_Free_Plane((*_plane)->plane);
            (*_plane)->plane = रिक्त;
        }
        यदि ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = रिक्त;
        }
        SDL_free(*_plane);
        *_plane = रिक्त;
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
शून्य
drm_atomic_समुच्चयः_plane_props(SDL_Display_दत्त *dispdata, संरचना KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    यदि (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_बहुलकम्_Atomic_Alloc();
    }

    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    सङ्कलय_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

पूर्णाङ्क drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_दत्त *viddata = ((SDL_Video_दत्त *)_this->आन्तरिकम्);
    uint32_t atomic_flags = 0;
    पूर्णाङ्क ret;

    यदि (!blocking) {
        atomic_flags |= DRM_बहुलकम्_ATOMIC_NONBLOCK;
    }

    यदि (allow_modeset) {
        atomic_flags |= DRM_बहुलकम्_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_बहुलकम्_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, रिक्त);

    यदि (ret) {
        SDL_समुच्चयः_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#यदि 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#यदि_अन्तः
        गच्छ बहिर्गमनम्;
    }

    यदि (dispdata->kms_अन्तर्_fence_fd != -1) {
        close(dispdata->kms_अन्तर्_fence_fd);
        dispdata->kms_अन्तर्_fence_fd = -1;
    }

बहिर्गमनम्:
    KMSDRM_drm_बहुलकम्_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = रिक्त;

    प्रत्यागम ret;
}

शून्य
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    यदि (dispdata->kms_fence) {
       EGLint स्थितिः;

        कुरु {
            स्थितिः = _this->egl_दत्त->eglClientWaitSyncKHR(_this->egl_दत्त->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } यावत् (स्थितिः != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_दत्त->eglDestroySyncKHR(_this->egl_दत्त->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = रिक्त;
    }
}

स्थिर bool KMSDRM_उपलब्धम्(शून्य)
{
#यदि_परिभाषितम् SDL_PLATFORM_OPENBSD
    संरचना utsname nameofsystem;
    द्विगुण releaseversion;
#यदि_अन्तः
    पूर्णाङ्क ret = -ENOENT;

#यदि_परिभाषितम् SDL_PLATFORM_OPENBSD
    यदि (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        यदि (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#यदि_अन्तः

    यदि (moderndri) {
        SDL_strlcpy(kmsdrm_dri_मार्गः, "/dev/dri/", परिमाण(kmsdrm_dri_मार्गः));
        SDL_strlcpy(kmsdrm_dri_devname, "card", परिमाण(kmsdrm_dri_devname));
    } अन्यथा {
        SDL_strlcpy(kmsdrm_dri_मार्गः, "/dev/", परिमाण(kmsdrm_dri_मार्गः));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", परिमाण(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_मार्गः);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (शून्य)SDL_snprintf(kmsdrm_dri_cardpath, परिमाण(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_मार्गः, kmsdrm_dri_devname);

    ret = get_driindex();
    यदि (ret >= 0) {
        प्रत्यागम true;
    }

    प्रत्यागम false;
}

स्थिर शून्य KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    यदि (device->आन्तरिकम्) {
        SDL_free(device->आन्तरिकम्);
        device->आन्तरिकम् = रिक्त;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

स्थिर SDL_VideoDevice *KMSDRM_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *viddata;
    पूर्णाङ्क devindex;

    यदि (!KMSDRM_उपलब्धम्()) {
        प्रत्यागम रिक्त;
    }

    devindex = get_driindex();
    यदि (devindex < 0) {
        SDL_समुच्चयः_Error("devindex (%d) must not be negative.", devindex);
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_KMSDRM_आरोपय_Symbols()) {
        प्रत्यागम रिक्त;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    viddata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!viddata) {
        गच्छ cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->आन्तरिकम् = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = KMSDRM_समुच्चयः_Display_बहुलकम्;
    device->CreateSDLWindow = KMSDRM_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = KMSDRM_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = KMSDRM_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = KMSDRM_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Fullscreen = KMSDRM_समुच्चयः_गवाक्षः_Fullscreen;
    device->Show_गवाक्षः = KMSDRM_Show_गवाक्षः;
    device->Hide_गवाक्षः = KMSDRM_Hide_गवाक्षः;
    device->Raise_गवाक्षः = KMSDRM_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = KMSDRM_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = KMSDRM_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = KMSDRM_Restore_गवाक्षः;
    device->Destroy_गवाक्षः = KMSDRM_Destroy_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Focusable = KMSDRM_समुच्चयः_गवाक्षः_Focusable;

    device->GL_आरोपय_Library = KMSDRM_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = KMSDRM_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = KMSDRM_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = KMSDRM_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = KMSDRM_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_समुच्चयः_Default_Profile_Config = KMSDRM_GLES_समुच्चयः_Default_Profile_Config;

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = KMSDRM_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#यदि_अन्तः

    device->PumpEvents = KMSDRM_PumpEvents;
    device->मुक्त = KMSDRM_DeleteDevice;

    प्रत्यागम device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    प्रत्यागम रिक्त;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

स्थिर शून्य KMSDRM_FBDestroyCallback(संरचना gbm_bo *bo, शून्य *दत्त)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)दत्त;

    यदि (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_बहुलकम्_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, संरचना gbm_bo *bo)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    अचिह्नित w, h;
    पूर्णाङ्क rc = -1;
    पूर्णाङ्क अङ्कः_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_दत्त(bo);

    यदि (fb_info) {
        प्रत्यागम fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, परिमाण(KMSDRM_FBInfo));

    यदि (!fb_info) {
        प्रत्यागम रिक्त;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_विस्तारः(bo);
    h = KMSDRM_gbm_bo_get_height(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    यदि (KMSDRM_drm_बहुलकम्_सङ्कलय_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_गणनम् &&
        KMSDRM_gbm_bo_get_विस्थापनम् &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        अङ्कः_planes = KMSDRM_gbm_bo_get_plane_गणनम्(bo);
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_विस्थापनम्(bo, i);
            modifiers[i] = modifiers[0];
        }

        यदि (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_बहुलकम्_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_बहुलकम्_सङ्कलय_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    यदि (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_बहुलकम्_सङ्कलय_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    यदि (rc < 0) {
        SDL_free(fb_info);
        प्रत्यागम रिक्त;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (शून्य *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_समुच्चयः_user_दत्त(bo, fb_info, KMSDRM_FBDestroyCallback);

    प्रत्यागम fb_info;
}

स्थिर शून्य KMSDRM_FlipHandler(पूर्णाङ्क fd, अचिह्नित पूर्णाङ्क frame, अचिह्नित पूर्णाङ्क sec, अचिह्नित पूर्णाङ्क usec, शून्य *दत्त)
{
    *((bool *)दत्त) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_गवाक्षः_दत्त *windata)
{

    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    drmEventContext ev = { 0 };
    संरचना pollfd pfd = { 0 };
    पूर्णाङ्क ret;

    ev.संस्करणम् = DRM_EVENT_CONTEXT_संस्करणम्;
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
    यावत् (windata->प्रतीक्षा_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        यदि (ret < 0) {
            यदि (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                अनुवर्त;
            } अन्यथा {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                प्रत्यागम false;
            }
        }

        यदि (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            प्रत्यागम false;
        }

        यदि (pfd.revents & POLLIN) {
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

    प्रत्यागम true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
स्थिर drm_बहुलकम्_बहुलकम्_Info *KMSDRM_Get_Closest_Display_बहुलकम्(SDL_VideoDisplay *display, पूर्णाङ्क विस्तारः, पूर्णाङ्क height)
{

    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;
    drm_बहुलकम्_Connector *conn = dispdata->connector.connector;

    SDL_Display_बहुलकम् closest;
    drm_बहुलकम्_बहुलकम्_Info *drm_बहुलकम्;

    यदि (SDL_Get_Closest_Fullscreen_Display_बहुलकम्(display->id, विस्तारः, height, 0.0f, false, &closest)) {
        ध्रुव SDL_Display_बहुलकम्_दत्त *modedata = closest.आन्तरिकम्;
        drm_बहुलकम् = &conn->modes[modedata->बहुलकम्_सूचकांक];
        प्रत्यागम drm_बहुलकम्;
    } अन्यथा {
        प्रत्यागम रिक्त;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

स्थिर bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;

    यदि (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_समुच्चयः_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_समुच्चयः_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    यदि (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        प्रत्यागम true;
    }

    प्रत्यागम KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
स्थिर शून्य KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_DisplayID *displays;
    SDL_Display_दत्त *dispdata;
    पूर्णाङ्क i;

    displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        // Iterate on the SDL Display list.
        प्रति (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_दत्त(displays[i]);

            // Free connector
            यदि (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_बहुलकम्_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = रिक्त;
            }

            // Free CRTC
            यदि (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_बहुलकम्_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = रिक्त;
            }
        }
        SDL_free(displays);
    }

    यदि (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

स्थिर bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool प्राप्तम् = false;
    uint64_t prop_मानम् = 0;

    drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(drm_fd, output_id, DRM_बहुलकम्_OBJECT_CONNECTOR);
    यदि (props) {
        प्रति (uint32_t i = 0; !प्राप्तम् && i < props->गणनम्_props; ++i) {
            drm_बहुलकम्_Property_Ptr prop = KMSDRM_drm_बहुलकम्_Get_Property(drm_fd, props->props[i]);
            यदि (prop) {
                यदि (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_मानम् = props->prop_मानानि[i];
                    प्राप्तम् = true;
                }
                KMSDRM_drm_बहुलकम्_Free_Property(prop);
            }
        }
        KMSDRM_drm_बहुलकम्_Free_Object_Properties(props);
    }
    यदि (प्राप्तम्) {
        प्रत्यागम prop_मानम् ? true : false;
    }
    प्रत्यागम false;
}

स्थिर bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool प्राप्तम् = false;
    drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(drm_fd, crtc_id, DRM_बहुलकम्_OBJECT_CRTC);
    यदि (props) {
        प्रति (uint32_t i = 0; !प्राप्तम् && i < props->गणनम्_props; ++i) {
            drm_बहुलकम्_Property_Ptr prop = KMSDRM_drm_बहुलकम्_Get_Property(drm_fd, props->props[i]);
            यदि (prop) {
                यदि (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    प्राप्तम् = true;
                }
                KMSDRM_drm_बहुलकम्_Free_Property(prop);
            }
        }
        KMSDRM_drm_बहुलकम्_Free_Object_Properties(props);
    }
    प्रत्यागम प्राप्तम्;
}

स्थिर शून्य KMSDRM_Crtc_समुच्चयः_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    यदि (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        प्रत्यागम;
    }

    KMSDRM_drm_बहुलकम्_Object_समुच्चयः_Property(drm_fd, crtc_id, DRM_बहुलकम्_OBJECT_CRTC, vrr_prop_id, enabled);
}

स्थिर bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool प्राप्तम् = false;
    uint64_t prop_मानम् = 0;

    यदि (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        प्रत्यागम false;
    }

    drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(drm_fd, crtc_id, DRM_बहुलकम्_OBJECT_CRTC);
    यदि (props) {
        प्रति (uint32_t i = 0; !प्राप्तम् && i < props->गणनम्_props; ++i) {
            drm_बहुलकम्_Property_Ptr prop = KMSDRM_drm_बहुलकम्_Get_Property(drm_fd, props->props[i]);
            यदि (prop) {
                यदि (prop->prop_id == vrr_prop_id) {
                    prop_मानम् = props->prop_मानानि[i];
                    प्राप्तम् = true;
                }
                KMSDRM_drm_बहुलकम्_Free_Property(prop);
            }
        }
        KMSDRM_drm_बहुलकम्_Free_Object_Properties(props);
    }
    यदि (प्राप्तम्) {
        प्रत्यागम prop_मानम् ? true : false;
    }
    प्रत्यागम false;
}

स्थिर पूर्णाङ्क KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool प्राप्तम् = false;
    पूर्णाङ्क orientation = 0;

    drm_बहुलकम्_Object_Properties_Ptr props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(drm_fd, crtc_id, DRM_बहुलकम्_OBJECT_CONNECTOR);
    यदि (props) {
        प्रति (uint32_t i = 0; !प्राप्तम् && i < props->गणनम्_props; ++i) {
            drm_बहुलकम्_Property_Ptr prop = KMSDRM_drm_बहुलकम्_Get_Property(drm_fd, props->props[i]);
            यदि (prop) {
                यदि (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_बहुलकम्_PROP_ENUM)) {
                    यदि (prop->गणनम्_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        यदि (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } अन्यथा यदि (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } अन्यथा यदि (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    प्राप्तम् = true;
                }
                KMSDRM_drm_बहुलकम्_Free_Property(prop);
            }
        }
        KMSDRM_drm_बहुलकम्_Free_Object_Properties(props);
    }
    प्रत्यागम orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
स्थिर शून्य KMSDRM_सङ्कलय_Display(SDL_VideoDevice *_this, drm_बहुलकम्_Connector *conn, drm_बहुलकम्_Res *resources)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_Display_दत्त *dispdata = रिक्त;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_बहुलकम्_दत्त *modedata = रिक्त;
    drm_बहुलकम्_Encoder *encoder = रिक्त;
    drm_बहुलकम्_Crtc *crtc = रिक्त;
    ध्रुव वर्ण *connector_type = रिक्त;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    वर्ण name_fmt[64];
    पूर्णाङ्क orientation;
    पूर्णाङ्क बहुलकम्_सूचकांक;
    पूर्णाङ्क i, j;
    पूर्णाङ्क ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_दत्त));
    यदि (!dispdata) {
        ret = -1;
        गच्छ cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = रिक्त;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_अन्तर्_fence_fd = -1;
    dispdata->kms_बहिर्गमनम्_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    प्रति (i = 0; i < resources->गणनम्_encoders; i++) {
        encoder = KMSDRM_drm_बहुलकम्_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        यदि (!encoder) {
            अनुवर्त;
        }

        यदि (encoder->encoder_id == conn->encoder_id) {
            भङ्ग;
        }

        KMSDRM_drm_बहुलकम्_Free_Encoder(encoder);
        encoder = रिक्त;
    }

    यदि (!encoder) {
        // No encoder was connected, find the first supported one
        प्रति (i = 0; i < resources->गणनम्_encoders; i++) {
            encoder = KMSDRM_drm_बहुलकम्_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            यदि (!encoder) {
                अनुवर्त;
            }

            प्रति (j = 0; j < conn->गणनम्_encoders; j++) {
                यदि (conn->encoders[j] == encoder->encoder_id) {
                    भङ्ग;
                }
            }

            यदि (j != conn->गणनम्_encoders) {
                भङ्ग;
            }

            KMSDRM_drm_बहुलकम्_Free_Encoder(encoder);
            encoder = रिक्त;
        }
    }

    यदि (!encoder) {
        ret = SDL_समुच्चयः_Error("No connected encoder found for connector.");
        गच्छ cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_बहुलकम्_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    यदि (!crtc) {
        प्रति (i = 0; i < resources->गणनम्_crtcs; i++) {
            यदि (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_बहुलकम्_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                भङ्ग;
            }
        }
    }

    यदि (!crtc) {
        ret = SDL_समुच्चयः_Error("No CRTC found for connector.");
        गच्छ cleanup;
    }

    // Find the index of the mode attached to this CRTC
    बहुलकम्_सूचकांक = -1;

    प्रति (i = 0; i < conn->गणनम्_modes; i++) {
        drm_बहुलकम्_बहुलकम्_Info *बहुलकम् = &conn->modes[i];

        यदि (!SDL_memcmp(बहुलकम्, &crtc->बहुलकम्, परिमाण(crtc->बहुलकम्))) {
            बहुलकम्_सूचकांक = i;
            भङ्ग;
        }
    }

    यदि (बहुलकम्_सूचकांक == -1) {
        पूर्णाङ्क current_area, largest_area = 0;

        // Find the preferred mode or the highest resolution mode
        प्रति (i = 0; i < conn->गणनम्_modes; i++) {
            drm_बहुलकम्_बहुलकम्_Info *बहुलकम् = &conn->modes[i];

            यदि (बहुलकम्->type & DRM_बहुलकम्_TYPE_PREFERRED) {
                बहुलकम्_सूचकांक = i;
                भङ्ग;
            }

            current_area = बहुलकम्->hdisplay * बहुलकम्->vdisplay;
            यदि (current_area > largest_area) {
                बहुलकम्_सूचकांक = i;
                largest_area = current_area;
            }
        }
        यदि (बहुलकम्_सूचकांक != -1) {
            crtc->बहुलकम् = conn->modes[बहुलकम्_सूचकांक];
        }
    }

    यदि (बहुलकम्_सूचकांक == -1) {
        ret = SDL_समुच्चयः_Error("Failed to find index of mode attached to the CRTC.");
        गच्छ cleanup;
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
    dispdata->बहुलकम् = crtc->बहुलकम्;
    dispdata->original_बहुलकम् = crtc->बहुलकम्;
    dispdata->fullscreen_बहुलकम् = crtc->बहुलकम्;

    यदि (dispdata->बहुलकम्.hdisplay == 0 || dispdata->बहुलकम्.vdisplay == 0) {
        ret = SDL_समुच्चयः_Error("Couldn't get a valid connector videomode.");
        गच्छ cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    यदि (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_समुच्चयः_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    यदि (KMSDRM_drm_बहुलकम्_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_बहुलकम्_Get_Connector_Type_Name(conn->connector_type);
        यदि (connector_type == रिक्त) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_बहुलकम्_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->गणनम्_props, परिमाण(*dispdata->crtc.props_info));
    यदि (!dispdata->crtc.props_info) {
        ret = false;
        गच्छ cleanup;
    }

    प्रति (i = 0; i < dispdata->crtc.props->गणनम्_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_बहुलकम्_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_बहुलकम्_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_बहुलकम्_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->गणनम्_props, परिमाण(*dispdata->connector.props_info));
    यदि (!dispdata->connector.props_info) {
        ret = false;
        गच्छ cleanup;
    }

    प्रति (i = 0; i < dispdata->connector.props->गणनम्_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_बहुलकम्_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));

    यदि (!modedata) {
        ret = -1;
        गच्छ cleanup;
    }

    modedata->बहुलकम्_सूचकांक = बहुलकम्_सूचकांक;

    display.आन्तरिकम् = dispdata;
    display.desktop_बहुलकम्.w = dispdata->बहुलकम्.hdisplay;
    display.desktop_बहुलकम्.h = dispdata->बहुलकम्.vdisplay;
    Calculate_Refresh_दरः(&dispdata->बहुलकम्, &display.desktop_बहुलकम्.refresh_दरः_numerator, &display.desktop_बहुलकम्.refresh_दरः_denominator);
    display.desktop_बहुलकम्.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_बहुलकम्.आन्तरिकम् = modedata;
    यदि (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_सङ्कलय_Video_Display(&display, false);
    यदि (!display_id) {
        ret = -1;
        गच्छ cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_समुच्चयः_सङ्ख्या_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_सङ्ख्या, orientation);

#यदि_परिभाषितम् DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#यदि_अन्तः

cleanup:
    यदि (encoder) {
        KMSDRM_drm_बहुलकम्_Free_Encoder(encoder);
    }
    यदि (ret) {
        // Error (complete) cleanup
        यदि (dispdata) {
            यदि (dispdata->connector.connector) {
                KMSDRM_drm_बहुलकम्_Free_Connector(dispdata->connector.connector);
            }
            यदि (dispdata->crtc.crtc) {
                KMSDRM_drm_बहुलकम्_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

स्थिर शून्य KMSDRM_क्रमय_Displays(SDL_VideoDevice *_this)
{
    ध्रुव वर्ण *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_प्राथमिकता);

    यदि (name_hint) {
        वर्ण *saveptr;
        वर्ण *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(परिमाण(SDL_VideoDisplay *) * _this->अङ्कः_displays);

        यदि (str && sorted_list) {
            पूर्णाङ्क sorted_सूचकांक = 0;

            // Sort the requested displays to the front of the list.
            ध्रुव वर्ण *token = SDL_strtok_r(str, ",", &saveptr);
            यावत् (token) {
                प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    यदि (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_सूचकांक++] = d;
                        _this->displays[i] = रिक्त;
                        भङ्ग;
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                यदि (_this->displays[i]) {
                    sorted_list[sorted_सूचकांक++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, परिमाण(SDL_VideoDisplay *) * _this->अङ्कः_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

स्थिर bool समुच्चयः_client_atomic_caps(पूर्णाङ्क fd)
{
    यदि (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        प्रत्यागम false;  // emergency escape hatch.
    } अन्यथा यदि (KMSDRM_drm_समुच्चयः_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        प्रत्यागम false;  // no atomic modesetting support.
    } अन्यथा यदि (KMSDRM_drm_समुच्चयः_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_समुच्चयः_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        प्रत्यागम false;  // no universal planes support.
    }
    प्रत्यागम true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
स्थिर bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    drm_बहुलकम्_Res *resources = रिक्त;
    uint64_t async_pageflip = 0;
    पूर्णाङ्क i;
    bool परिणाम = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (शून्य)SDL_snprintf(viddata->devpath, परिमाण(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = उद्घाटय(viddata->devpath, O_RDWR | O_CLOEXEC);

    यदि (viddata->drm_fd < 0) {
        परिणाम = SDL_समुच्चयः_Error("Could not open %s", viddata->devpath);
        गच्छ cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = समुच्चयः_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_बहुलकम्_Get_Resources(viddata->drm_fd);
    यदि (!resources) {
        परिणाम = SDL_समुच्चयः_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        गच्छ cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    प्रति (i = 0; i < resources->गणनम्_connectors; i++) {
        drm_बहुलकम्_Connector *conn = KMSDRM_drm_बहुलकम्_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        यदि (!conn) {
            अनुवर्त;
        }

        यदि (conn->connection == DRM_बहुलकम्_CONNECTED && conn->गणनम्_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_सङ्कलय_Display(_this, conn, resources);
        } अन्यथा {
            // If it's not, free it now.
            KMSDRM_drm_बहुलकम्_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    यदि (SDL_GetPrimaryDisplay() == 0) {
        परिणाम = SDL_समुच्चयः_Error("No connected displays found.");
        गच्छ cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_क्रमय_Displays(_this);

    // Determine if video hardware supports async pageflips.
    यदि (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_PAGE_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    यदि (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    यदि (resources) {
        KMSDRM_drm_बहुलकम्_Free_Resources(resources);
    }
    यदि (!परिणाम) {
        यदि (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    प्रत्यागम परिणाम;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
स्थिर bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    bool परिणाम = true;

    // Reopen the FD if we weren't able to drop master on the original one
    यदि (viddata->drm_fd < 0) {
        viddata->drm_fd = उद्घाटय(viddata->devpath, O_RDWR | O_CLOEXEC);
        यदि (viddata->drm_fd < 0) {
            प्रत्यागम SDL_समुच्चयः_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = समुच्चयः_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_समुच्चयः_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    यदि (!viddata->gbm_dev) {
        परिणाम = SDL_समुच्चयः_Error("Couldn't create gbm device.");
    } अन्यथा {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        परिणाम = सज्जता_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        यदि (!परिणाम) {
            SDL_समुच्चयः_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    प्रत्यागम परिणाम;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
स्थिर शून्य KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_दत्त *dispdata)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    यदि (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = रिक्त;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    यदि (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

स्थिर शून्य KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *windata = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *dispdata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    पूर्णाङ्क ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    यदि (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#यदि 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        सङ्कलय_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        सङ्कलय_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        सङ्कलय_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
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

        drm_atomic_समुच्चयः_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_बहुलकम्_समुच्चयः_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->बफर_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_बहुलकम्);

        /* Issue atomic commit that is blocking and allows modesetting. */
        यदि (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_समुच्चयः_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        यदि (ret && (dispdata->crtc->बहुलकम्_valid == 0)) {
            ret = KMSDRM_drm_बहुलकम्_समुच्चयः_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->बफर_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_बहुलकम्);
        }
#यदि_अन्तः

#यदि 1
        /************************************************************/
        /* Make the display plane point to the original TTY buffer. */
        /* We have to configure it's input and output scaling       */
        /* parameters accordingly.                                  */
        /************************************************************/

        KMSDRM_PlaneInfo plane_info;
        SDL_zero(plane_info);
        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = dispdata->crtc.crtc->crtc_id;
        plane_info.fb_id = dispdata->crtc.crtc->बफर_id;
        plane_info.src_w = dispdata->original_बहुलकम्.hdisplay;
        plane_info.src_h = dispdata->original_बहुलकम्.vdisplay;
        plane_info.crtc_w = dispdata->original_बहुलकम्.hdisplay;
        plane_info.crtc_h = dispdata->original_बहुलकम्.vdisplay;

        drm_atomic_समुच्चयः_plane_props(dispdata, &plane_info);

        यदि (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_समुच्चयः_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#यदि_अन्तः

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_बहुलकम्_समुच्चयः_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->बफर_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_बहुलकम्);

    // If we failed to set the original mode, try to set the connector preferred mode.
    यदि (ret && (dispdata->crtc.crtc->बहुलकम्_valid == 0)) {
        ret = KMSDRM_drm_बहुलकम्_समुच्चयः_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->बफर_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_बहुलकम्);
    }

    यदि (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    यदि (windata->bo) {
        यदि (windata->bo != windata->अग्र_bo) {
            KMSDRM_gbm_surface_release_बफर(windata->gs, windata->bo);
        }
        windata->bo = रिक्त;
    }

    यदि (windata->अग्र_bo) {
        KMSDRM_gbm_surface_release_बफर(windata->gs, windata->अग्र_bo);
        windata->अग्र_bo = रिक्त;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    यदि (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    यदि (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = रिक्त;
    }
}

स्थिर शून्य KMSDRM_Get_बहुलकम्_गन्तव्यम्_समुच्चयः(SDL_गवाक्षः *गवाक्षः, drm_बहुलकम्_बहुलकम्_Info *बहिर्गमनम्_बहुलकम्)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;

    यदि (गवाक्षः->fullscreen_exclusive) {
        *बहिर्गमनम्_बहुलकम् = dispdata->fullscreen_बहुलकम्;
    } अन्यथा {
        drm_बहुलकम्_बहुलकम्_Info *बहुलकम् = KMSDRM_Get_Closest_Display_बहुलकम्(display, गवाक्षः->windowed.w, गवाक्षः->windowed.h);
        यदि (बहुलकम्) {
            *बहिर्गमनम्_बहुलकम् = *बहुलकम्;
        } अन्यथा {
            *बहिर्गमनम्_बहुलकम् = dispdata->original_बहुलकम्;
        }
    }
}

स्थिर शून्य KMSDRM_DirtySurfaces(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *windata = गवाक्षः->आन्तरिकम्;
    drm_बहुलकम्_बहुलकम्_Info बहुलकम्;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_बहुलकम्_गन्तव्यम्_समुच्चयः(गवाक्षः, &बहुलकम्);
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, बहुलकम्.hdisplay, बहुलकम्.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    स्थिर ध्रुव संरचना { uint32_t fmt; ध्रुव वर्ण *name; पूर्णाङ्क r; पूर्णाङ्क g; पूर्णाङ्क b; पूर्णाङ्क a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #परिभाषय FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #अपरिभाषय FMT
    };

    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *windata = गवाक्षः->आन्तरिकम्;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;
    EGLContext egl_context;
    bool परिणाम = false;

    // If the current window already has surfaces, destroy them before creating other.
    यदि (windata->gs) {
        KMSDRM_DestroySurfaces(_this, गवाक्षः);
    }

    bool tried_setting_format = false;
    ध्रुव uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ध्रुव uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        यदि (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            अनुवर्त;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_बहुलकम्_गन्तव्यम्_समुच्चयः(गवाक्षः, &dispdata->बहुलकम्);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->बहुलकम्.hdisplay, dispdata->बहुलकम्.vdisplay, surface_fmt, surface_flags);
        यदि (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->बहुलकम्.hdisplay, dispdata->बहुलकम्.vdisplay, surface_fmt, 0);
        }
        यदि (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_समुच्चयः_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            अनुवर्त;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_समुच्चयः_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)windata->gs);
        यदि (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = रिक्त;
            अनुवर्त;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        परिणाम = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        यदि (!परिणाम) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            अनुवर्त;
        }

        _this->gl_config.red_आकार = gbm_formats[i].r;
        _this->gl_config.green_आकार = gbm_formats[i].g;
        _this->gl_config.blue_आकार = gbm_formats[i].b;
        _this->gl_config.alpha_आकार = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        परिणाम = true;

        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, dispdata->बहुलकम्.hdisplay, dispdata->बहुलकम्.vdisplay);

        भङ्ग;
    }

    SDL_assert(परिणाम || (windata->gs == रिक्त));

    यदि (!परिणाम) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        यदि (!tried_setting_format) {   // make sure there's an error string set.
            SDL_समुच्चयः_Error("Could not find any supported GBM surface format.");
        }
    }

    प्रत्यागम परिणाम;
}

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
स्थिर शून्य KMSDRM_ReleaseVT(शून्य *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    पूर्णाङ्क i;

    प्रति (i = 0; i < viddata->अङ्कः_windows; i++) {
        SDL_गवाक्षः *गवाक्षः = viddata->windows[i];
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, गवाक्षः);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

स्थिर शून्य KMSDRM_AcquireVT(शून्य *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    पूर्णाङ्क i;

    KMSDRM_drm_समुच्चयः_Master(viddata->drm_fd);
    प्रति (i = 0; i < viddata->अङ्कः_windows; i++) {
        SDL_गवाक्षः *गवाक्षः = viddata->windows[i];
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, गवाक्षः);
        }
    }
}
#यदि_अन्तः // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool परिणाम = true;

    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    यदि (!KMSDRM_InitDisplays(_this)) {
        परिणाम = SDL_समुच्चयः_Error("error getting KMSDRM displays information");
    }

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_समुच्चयः_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#नोचेद्यदि defined(SDL_निवेशः_WSCONS)
    SDL_WSCONS_Init();
#यदि_अन्तः

    viddata->video_init = true;

    प्रत्यागम परिणाम;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
शून्य KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;

    KMSDRM_DeinitDisplays(_this);

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    SDL_EVDEV_समुच्चयः_VTSwitch_Callbacks(रिक्त, रिक्त, रिक्त, रिक्त);
    SDL_EVDEV_Quit();
#नोचेद्यदि defined(SDL_निवेशः_WSCONS)
    SDL_WSCONS_Quit();
#यदि_अन्तः

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = रिक्त;
    viddata->max_windows = 0;
    viddata->अङ्कः_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;
    drm_बहुलकम्_Connector *conn = dispdata->connector.connector;
    SDL_Display_बहुलकम् बहुलकम्;
    पूर्णाङ्क i;

    प्रति (i = 0; i < conn->गणनम्_modes; i++) {
        SDL_Display_बहुलकम्_दत्त *modedata = SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));

        यदि (modedata) {
            modedata->बहुलकम्_सूचकांक = i;
        }

        SDL_zero(बहुलकम्);
        बहुलकम्.w = conn->modes[i].hdisplay;
        बहुलकम्.h = conn->modes[i].vdisplay;
        Calculate_Refresh_दरः(&conn->modes[i], &बहुलकम्.refresh_दरः_numerator, &बहुलकम्.refresh_दरः_denominator);
        बहुलकम्.format = SDL_PIXELFORMAT_ARGB8888;
        बहुलकम्.आन्तरिकम् = modedata;

        यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्)) {
            SDL_free(modedata);
        }
    }
    प्रत्यागम true;
}

bool KMSDRM_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;
    SDL_Display_बहुलकम्_दत्त *modedata = बहुलकम्->आन्तरिकम्;
    drm_बहुलकम्_Connector *conn = dispdata->connector.connector;
    पूर्णाङ्क i;

    // Don't do anything if we are in Vulkan mode.
    यदि (viddata->vulkan_बहुलकम्) {
        प्रत्यागम true;
    }

    यदि (!modedata) {
        प्रत्यागम SDL_समुच्चयः_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_बहुलकम् = conn->modes[modedata->बहुलकम्_सूचकांक];

    प्रति (i = 0; i < viddata->अङ्कः_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    प्रत्यागम true;
}

शून्य KMSDRM_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *windata = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *dispdata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    SDL_Video_दत्त *viddata;
    bool is_vulkan = गवाक्षः->flags & SDL_गवाक्षः_VULKAN; // Is this a VK window?
    अचिह्नित पूर्णाङ्क i, j;

    यदि (!windata) {
        प्रत्यागम;
    }

    // restore vrr state
    KMSDRM_Crtc_समुच्चयः_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    यदि (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, गवाक्षः);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        यदि (viddata->अङ्कः_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            यदि (_this->egl_दत्त) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } अन्यथा {

        // If we were in Vulkan mode, get out of it.
        यदि (viddata->vulkan_बहुलकम्) {
            viddata->vulkan_बहुलकम् = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    प्रति (i = 0; i < viddata->अङ्कः_windows; i++) {
        यदि (viddata->windows[i] == गवाक्षः) {
            viddata->अङ्कः_windows--;

            प्रति (j = i; j < viddata->अङ्कः_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            भङ्ग;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(गवाक्षः->आन्तरिकम्);
    गवाक्षः->आन्तरिकम् = रिक्त;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *windata = रिक्त;
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    SDL_Display_दत्त *dispdata = display->आन्तरिकम्;
    bool is_vulkan = गवाक्षः->flags & SDL_गवाक्षः_VULKAN; // Is this a VK window?
    bool vulkan_बहुलकम् = viddata->vulkan_बहुलकम्;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_बहुलकम्_बहुलकम्_Info *बहुलकम्;
    bool परिणाम = true;

    // Allocate window internal data
    windata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!windata) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    गवाक्षः->आन्तरिकम् = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_बफर = false;
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_बफर, false)) {
        windata->double_बफर = true;
    }

    यदि (!is_vulkan && !vulkan_बहुलकम्) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        गवाक्षः->flags |= SDL_गवाक्षः_OPENGL;

        यदि (!(viddata->gbm_init)) {

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
            यदि (!KMSDRM_GBMInit(_this, dispdata)) {
                प्रत्यागम SDL_समुच्चयः_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        यदि (!_this->egl_दत्त) {
            egl_display = (NativeDisplayType)_this->आन्तरिकम्->gbm_dev;
            यदि (!SDL_EGL_आरोपय_Library(_this, रिक्त, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_आवरणम् = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_संस्करणम् = 2;
                _this->gl_config.minor_संस्करणम् = 0;
                यदि (!SDL_EGL_आरोपय_Library(_this, रिक्त, egl_display)) {
                    प्रत्यागम SDL_समुच्चयः_Error("Can't load EGL/GL library on window creation.");
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
        बहुलकम् = KMSDRM_Get_Closest_Display_बहुलकम्(display, गवाक्षः->windowed.w, गवाक्षः->windowed.h);

        यदि (बहुलकम्) {
            dispdata->fullscreen_बहुलकम् = *बहुलकम्;
        } अन्यथा {
            dispdata->fullscreen_बहुलकम् = dispdata->original_बहुलकम्;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        यदि (!KMSDRM_CreateSurfaces(_this, गवाक्षः)) {
            प्रत्यागम false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    यदि (viddata->अङ्कः_windows >= viddata->max_windows) {
        अचिह्नित पूर्णाङ्क new_max_windows = viddata->max_windows + 1;
        SDL_गवाक्षः **new_windows = (SDL_गवाक्षः **)SDL_realloc(viddata->windows,
                                                              new_max_windows * परिमाण(SDL_गवाक्षः *));
        यदि (!new_windows) {
            प्रत्यागम false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->अङ्कः_windows++] = गवाक्षः;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_बहुलकम् = is_vulkan;

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_KMSDRM_DEVICE_सूचकांक_सङ्ख्या, viddata->devindex);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_KMSDRM_DRM_FD_सङ्ख्या, viddata->drm_fd);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_KMSDRM_GBM_DEVICE_POINTER, viddata->gbm_dev);

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_गवाक्षः(गवाक्षः), &display_bounds);
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    प्रत्यागम परिणाम;
}

शून्य KMSDRM_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool KMSDRM_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_Unsupported();
}
शून्य KMSDRM_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    यदि (!viddata->vulkan_बहुलकम्) {
        KMSDRM_DirtySurfaces(गवाक्षः);
    }
}
SDL_Fullscreen_परिणाम KMSDRM_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    यदि (!viddata->vulkan_बहुलकम्) {
        KMSDRM_DirtySurfaces(गवाक्षः);
    }
    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}
शून्य KMSDRM_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य KMSDRM_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य KMSDRM_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य KMSDRM_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य KMSDRM_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य KMSDRM_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool KMSDRM_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable)
{
    प्रत्यागम true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_KMSDRM
