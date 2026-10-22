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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM

/* Include this first, as some system headers may pull in EGL headers that
 * define EGL types as native types for other enabled platforms, which can
 * result in type-mismatch warnings when building with LTO.
 */
#شامل "../SDL_egl_c.h"

// SDL internals
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
#شامل "../../core/linux/SDL_evdev.h"
#وگرنہ_اگر defined SDL_داخلہ_WSCONS
#شامل "../../core/openbsd/SDL_wscons.h"
#اگر_ختم

// KMS/DRM declarations
#شامل "SDL_kmsdrmdyn.h"
#شامل "SDL_kmsdrmevents.h"
#شامل "SDL_kmsdrmmouse.h"
#شامل "SDL_kmsdrmvideo.h"
#شامل "SDL_kmsdrmopengles.h"
#شامل "SDL_kmsdrmvulkan.h"
#شامل <dirent.h>
#شامل <errno.h>
#شامل <poll.h>
#شامل <sys/param.h>
#شامل <sys/stat.h>
#شامل <sys/utsname.h>

#اگر_تعریف_شدہ SDL_PLATFORM_OPENBSD
ساکن bool moderndri = false;
#ورنہ
ساکن bool moderndri = true;
#اگر_ختم

ساکن حرف kmsdrm_dri_راستہ[16];
ساکن صحیح kmsdrm_dri_pathsize = 0;
ساکن حرف kmsdrm_dri_devname[8];
ساکن صحیح kmsdrm_dri_devnamesize = 0;
ساکن حرف kmsdrm_dri_cardpath[32];

/* for older KMSDRM headers... */
#اگر_غیر_تعریف_شدہ DRM_FORMAT_MOD_VENDOR_NONE
#تعریف_کرو DRM_FORMAT_MOD_VENDOR_NONE 0
#اگر_ختم
#اگر_غیر_تعریف_شدہ DRM_FORMAT_MOD_خطی
#تعریف_کرو DRM_FORMAT_MOD_خطی fourcc_mod_رمز(NONE, 0)
#اگر_ختم

ساکن صحیح get_driindex(خالی)
{
    صحیح دستیاب = -ENOENT;
    حرف device[حجم(kmsdrm_dri_cardpath)];
    صحیح drm_fd;
    صحیح i;
    صحیح devindex = -1;
    DIR *folder;
    ثابت حرف *hint;
    ساخت dirent *res;

    hint = SDL_GetHint(SDL_HINT_KMSDRM_DEVICE_اشاریہ);
    اگر (hint && *hint) {
        حرف *endptr = تہی;
        ثابت صحیح idx = (صحیح)SDL_strtol(hint, &endptr, 10);
        اگر ((*endptr == '\0') && (idx >= 0)) { /* *endptr==0 means "whole string was a valid number" */
            واپس idx;                        // we'll take the user's request here.
        }
    }

    SDL_strlcpy(device, kmsdrm_dri_راستہ, حجم(device));
    folder = opendir(device);
    اگر (!folder) {
        SDL_سیٹ_Error("Failed to open directory '%s'", device);
        واپس -ENOENT;
    }

    SDL_strlcpy(device + kmsdrm_dri_pathsize, kmsdrm_dri_devname,
                حجم(device) - kmsdrm_dri_pathsize);
    جب((res = readdir(folder)) != تہی && دستیاب < 0) {
        اگر (SDL_memcmp(res->d_name, kmsdrm_dri_devname,
                       kmsdrm_dri_devnamesize) == 0) {
            SDL_strlcpy(device + kmsdrm_dri_pathsize + kmsdrm_dri_devnamesize,
                        res->d_name + kmsdrm_dri_devnamesize,
                        حجم(device) - kmsdrm_dri_pathsize -
                            kmsdrm_dri_devnamesize);

            drm_fd = open(device, O_RDWR | O_CLOEXEC);
            اگر (drm_fd >= 0) {
                devindex = SDL_atoi(device + kmsdrm_dri_pathsize +
                                    kmsdrm_dri_devnamesize);
                اگر (SDL_KMSDRM_بھرو_Symbols()) {
                    drm_منوال_Res *resources = KMSDRM_drm_منوال_Get_Resources(drm_fd);
                    اگر (resources) {
                        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                                     "%s%d connector, encoder and CRTC counts are: %d %d %d",
                                     kmsdrm_dri_cardpath, devindex,
                                     resources->گنتی_connectors,
                                     resources->گنتی_encoders,
                                     resources->گنتی_crtcs);

                        اگر (resources->گنتی_connectors > 0 &&
                            resources->گنتی_encoders > 0 &&
                            resources->گنتی_crtcs > 0) {
                            دستیاب = -ENOENT;
                            برائے (i = 0; i < resources->گنتی_connectors && دستیاب < 0; i++) {
                                drm_منوال_Connector *conn =
                                    KMSDRM_drm_منوال_Get_Connector(
                                        drm_fd, resources->connectors[i]);

                                اگر (!conn) {
                                    جاری;
                                }

                                اگر (conn->connection == DRM_منوال_CONNECTED &&
                                    conn->گنتی_modes) {
                                    bool access_denied = false;
                                    اگر (SDL_GetHintBoolean(
                                            SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER,
                                            true)) {
                                        /* Skip this device if we can't obtain
                                         * DRM master */
                                        KMSDRM_drm_سیٹ_Master(drm_fd);
                                        اگر (KMSDRM_drmAuthMagic(drm_fd, 0) == -EACCES) {
                                            access_denied = true;
                                        }
                                    }

                                    اگر (!access_denied) {
                                        دستیاب = devindex;
                                    }
                                }

                                KMSDRM_drm_منوال_Free_Connector(conn);
                            }
                        }
                        KMSDRM_drm_منوال_Free_Resources(resources);
                    }
                    SDL_KMSDRM_UnloadSymbols();
                }
                close(drm_fd);
            } ورنہ {
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                             "Failed to open KMSDRM device %s, errno: %d", device, errno);
            }
        }
    }

    closedir(folder);

    واپس دستیاب;
}

ساکن خالی Calculate_Refresh_شرح(drm_منوال_منوال_Info *منوال, صحیح *numerator, صحیح *denominator)
{
    *numerator = منوال->clock * 1000;
    *denominator = منوال->htotal * منوال->vtotal;

    اگر (منوال->flags & DRM_منوال_FLAG_INTERLACE) {
        *numerator *= 2;
    }

    اگر (منوال->flags & DRM_منوال_FLAG_DBLSCAN) {
        *denominator *= 2;
    }

    اگر (منوال->vscan > 1) {
        *denominator *= منوال->vscan;
    }
}


صحیح جوڑو_connector_property(drm_منوال_Atomic_Req *req, KMSDRM_connector *conn, ثابت حرف *name, uint64_t قدر)
{
    غیرعلامتی صحیح i;
    صحیح prop_id = 0;

    برائے (i = 0 ; i < conn->props->گنتی_props ; i++) {
        اگر (SDL_strcmp(conn->props_info[i]->name, name) == 0) {
            prop_id = conn->props_info[i]->prop_id;
            توڑو;
        }
    }

    اگر (prop_id < 0) {
        SDL_سیٹ_Error("no connector property: %s", name);
        واپس -EINVAL;
    }

    واپس KMSDRM_drm_منوال_Atomic_جوڑو_Property(req, conn->connector->connector_id, prop_id, قدر);
}

صحیح جوڑو_crtc_property(drm_منوال_Atomic_Req *req, KMSDRM_crtc *c, ثابت حرف *name, uint64_t قدر)
{
    غیرعلامتی صحیح i;
    صحیح prop_id = -1;

    برائے (i = 0 ; i < c->props->گنتی_props ; i++) {
        اگر (SDL_strcmp(c->props_info[i]->name, name) == 0) {
            prop_id = c->props_info[i]->prop_id;
            توڑو;
        }
    }

    اگر (prop_id < 0) {
        SDL_سیٹ_Error("no crtc property: %s", name);
        واپس -EINVAL;
    }

    واپس KMSDRM_drm_منوال_Atomic_جوڑو_Property(req, c->crtc->crtc_id, prop_id, قدر);
}

صحیح جوڑو_plane_property(drm_منوال_Atomic_Req *req, KMSDRM_plane *p, ثابت حرف *name, uint64_t قدر)
{
    غیرعلامتی صحیح i;
    صحیح prop_id = -1;

    برائے (i = 0 ; i < p->props->گنتی_props ; i++) {
        اگر (SDL_strcmp(p->props_info[i]->name, name) == 0) {
            prop_id = p->props_info[i]->prop_id;
            توڑو;
        }
    }

    اگر (prop_id < 0) {
        SDL_سیٹ_Error("no plane property: %s", name);
        واپس -EINVAL;
    }

    واپس KMSDRM_drm_منوال_Atomic_جوڑو_Property(req, p->plane->plane_id, prop_id, قدر);
}

#اگر_تعریف_شدہ DEBUG_KMSDRM
ساکن خالی print_plane_info(SDL_VideoDevice *_this, drm_منوال_Plane_Ptr plane)
{
    SDL_Video_ڈیٹا *viddata = ((SDL_Video_ڈیٹا *)_this->اندرونی_2);
    drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(viddata->drm_fd,
        plane->plane_id, DRM_منوال_OBJECT_PLANE);

    /* Search the plane props for the plane type. */
    uint32_t type = 0;
    برائے (صحیح i = 0; i < props->گنتی_props; i++) {
        drm_منوال_Property_Ptr p = KMSDRM_drm_منوال_Get_Property(viddata->drm_fd, props->props[i]);
        اگر ((SDL_strcmp(p->name, "type") == 0)) {
            type = props->prop_اقدار[i];
        }

        KMSDRM_drm_منوال_Free_Property(p);
    }

    حرف *plane_type = "unknown";
    انتخاب (type) {
        حالت DRM_PLANE_TYPE_OVERLAY:
            plane_type = "overlay";
            توڑو;

        حالت DRM_PLANE_TYPE_PRIMARY:
            plane_type = "primary";
            توڑو;

        حالت DRM_PLANE_TYPE_CURSOR:
            plane_type = "cursor";
            توڑو;
    }


    /* Remember that to present a plane on screen, it has to be
       connected to a CRTC so the CRTC scans it,
       scales it, etc... and presents it on screen. */

    /* Now we look for the CRTCs supported by the plane. */
    drm_منوال_Res *resources = KMSDRM_drm_منوال_Get_Resources(viddata->drm_fd);
    اگر (resources) {
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        SDL_IOprintf(io, "--PLANE ID: %d\nPLANE TYPE: %s\nCRTC READING THIS PLANE: %d\nCRTCS SUPPORTED BY THIS PLANE: ",  plane->plane_id, plane_type, plane->crtc_id);
        برائے (صحیح i = 0; i < resources->گنتی_crtcs; i++) {
            اگر (plane->possible_crtcs & (1 << i)) {
                uint32_t crtc_id = resources->crtcs[i];
                SDL_IOprintf(io, " %d", crtc_id);
                توڑو;
            }
        }
        SDL_Log("%s\n\n", (ثابت حرف *)SDL_Get_اشارہ_گر_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_حافظہ_اشارہ_گر, ""));
        SDL_CloseIO(io);
    }
}

ساکن خالی get_planes_info(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata)
{
    SDL_Video_ڈیٹا *viddata = ((SDL_Video_ڈیٹا *)_this->اندرونی_2);

    drm_منوال_Plane_Res_Ptr plane_resources = KMSDRM_drm_منوال_Get_Plane_Resources(viddata->drm_fd);
    اگر (!plane_resources) {
        SDL_Log("drmModeGetPlaneResources failed: %s", strerror(errno));
        واپس;
    }

    SDL_Log("--Number of planes found: %d--", plane_resources->گنتی_planes);
    SDL_Log("--Usable CRTC that we have chosen: %d--", dispdata->crtc.crtc->crtc_id);

    /* Iterate on all the available planes. */
    برائے (uint32_t i = 0; (i < plane_resources->گنتی_planes); i++) {
        ثابت uint32_t plane_id = plane_resources->planes[i];

        drm_منوال_Plane_Ptr plane = KMSDRM_drm_منوال_Get_Plane(viddata->drm_fd, plane_id);
        اگر (!plane) {
            SDL_Log("drmModeGetPlane(%u) failed: %s", plane_id, strerror(errno));
            جاری;
        }

        /* Print plane info. */
        print_plane_info(_this, plane);
        KMSDRM_drm_منوال_Free_Plane(plane);
    }

    KMSDRM_drm_منوال_Free_Plane_Resources(plane_resources);
}
#اگر_ختم

/* Get the plane_id of a plane that is of the specified plane type (primary,
   overlay, cursor...) and can use specified CRTC. */
ساکن صحیح get_plane_id(SDL_VideoDevice *_this, غیرعلامتی صحیح crtc_id, uint32_t plane_type)
{
    drm_منوال_Res *resources = تہی;
    drm_منوال_Plane_Res_Ptr plane_resources = تہی;
    uint32_t i, j;
    غیرعلامتی صحیح crtc_اشاریہ = 0;
    صحیح ret = -EINVAL;
    صحیح ملا = 0;

    SDL_Video_ڈیٹا *viddata = ((SDL_Video_ڈیٹا *)_this->اندرونی_2);

    resources = KMSDRM_drm_منوال_Get_Resources(viddata->drm_fd);

    /* Get the crtc_index for the current CRTC.
       It's needed to find out if a plane supports the CRTC. */
    برائے (i = 0; i < resources->گنتی_crtcs; i++) {
        اگر (resources->crtcs[i] == crtc_id) {
            crtc_اشاریہ = i;
            توڑو;
        }
    }

    plane_resources = KMSDRM_drm_منوال_Get_Plane_Resources(viddata->drm_fd);
    اگر (!plane_resources) {
        واپس SDL_سیٹ_Error("drmModeGetPlaneResources failed.");
    }

    /* Iterate on all the available planes. */
    برائے (i = 0; (i < plane_resources->گنتی_planes) && !ملا; i++) {

        uint32_t plane_id = plane_resources->planes[i];

        drm_منوال_Plane_Ptr plane = KMSDRM_drm_منوال_Get_Plane(viddata->drm_fd, plane_id);
        اگر (!plane) {
            جاری;
        }

        /* See if the current CRTC is available for this plane. */
        اگر (plane->possible_crtcs & (1 << crtc_اشاریہ)) {

            drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(
                viddata->drm_fd, plane_id, DRM_منوال_OBJECT_PLANE);
            ret = plane_id;

            /* Iterate on the plane props to find the type of the plane,
               to see if it's of the type we want. */
            برائے (j = 0; j < props->گنتی_props; j++) {

                drm_منوال_Property_Ptr p = KMSDRM_drm_منوال_Get_Property(viddata->drm_fd,
                    props->props[j]);

                اگر ((SDL_strcmp(p->name, "type") == 0) && (props->prop_اقدار[j] == plane_type)) {
                    /* found our plane, use that: */
                    ملا = 1;
                }

                KMSDRM_drm_منوال_Free_Property(p);
            }

            KMSDRM_drm_منوال_Free_Object_Properties(props);
        }

        KMSDRM_drm_منوال_Free_Plane(plane);
    }

    KMSDRM_drm_منوال_Free_Plane_Resources(plane_resources);
    KMSDRM_drm_منوال_Free_Resources(resources);

    واپس ret;
}

/* Setup a plane and it's props. */
bool تیاری_plane(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata, KMSDRM_plane **_plane, uint32_t plane_type)
{
    uint32_t plane_id;
    SDL_Video_ڈیٹا *viddata = ((SDL_Video_ڈیٹا *)_this->اندرونی_2);
    bool ret = true;

    *_plane = SDL_calloc(1, حجم(**_plane));
    اگر (!(*_plane)) {
        ret = false;
        جاؤ cleanup;
    }

    /* Get plane ID for a given CRTC and plane type. */
    plane_id = get_plane_id(_this, dispdata->crtc.crtc->crtc_id, plane_type);

    اگر (!plane_id) {
        ret = SDL_سیٹ_Error("Invalid Plane ID");
        جاؤ cleanup;
    }

    /* Get the DRM plane itself. */
    (*_plane)->plane = KMSDRM_drm_منوال_Get_Plane(viddata->drm_fd, plane_id);

    /* Get the DRM plane properties. */
    اگر ((*_plane)->plane) {
        غیرعلامتی صحیح i;
        (*_plane)->props = KMSDRM_drm_منوال_Object_Get_Properties(viddata->drm_fd,
        (*_plane)->plane->plane_id, DRM_منوال_OBJECT_PLANE);
        (*_plane)->props_info = SDL_calloc((*_plane)->props->گنتی_props, حجم(*(*_plane)->props_info));

        اگر ( !((*_plane)->props_info) ) {
            ret = false;
            جاؤ cleanup;
        }

        برائے (i = 0; i < (*_plane)->props->گنتی_props; i++) {
            (*_plane)->props_info[i] = KMSDRM_drm_منوال_Get_Property(viddata->drm_fd, (*_plane)->props->props[i]);
        }
    }

cleanup:
    اگر (!ret) {
        اگر (*_plane) {
            SDL_free(*_plane);
            *_plane = تہی;
        }
    }
    واپس ret;
}

/* Free a plane and it's props. */
خالی free_plane(KMSDRM_plane **_plane)
{
    اگر (*_plane) {
        اگر ((*_plane)->plane) {
            KMSDRM_drm_منوال_Free_Plane((*_plane)->plane);
            (*_plane)->plane = تہی;
        }
        اگر ((*_plane)->props_info) {
            SDL_free((*_plane)->props_info);
            (*_plane)->props_info = تہی;
        }
        SDL_free(*_plane);
        *_plane = تہی;
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
خالی
drm_atomic_سیٹ_plane_props(SDL_Display_ڈیٹا *dispdata, ساخت KMSDRM_PlaneInfo *info)
{
    /* Do we have a set of changes already in the making? If not, allocate a new one. */
    اگر (!dispdata->atomic_req) {
        dispdata->atomic_req = KMSDRM_drm_منوال_Atomic_Alloc();
    }

    جوڑو_plane_property(dispdata->atomic_req, info->plane, "FB_ID", info->fb_id);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "CRTC_ID", info->crtc_id);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "SRC_W", info->src_w << 16);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "SRC_H", info->src_h << 16);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "SRC_X", info->src_x);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "SRC_Y", info->src_y);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "CRTC_W", info->crtc_w);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "CRTC_H", info->crtc_h);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "CRTC_X", info->crtc_x);
    جوڑو_plane_property(dispdata->atomic_req, info->plane, "CRTC_Y", info->crtc_y);
}

صحیح drm_atomic_commit(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata, bool blocking, bool allow_modeset)
{
    SDL_Video_ڈیٹا *viddata = ((SDL_Video_ڈیٹا *)_this->اندرونی_2);
    uint32_t atomic_flags = 0;
    صحیح ret;

    اگر (!blocking) {
        atomic_flags |= DRM_منوال_ATOMIC_NONBLOCK;
    }

    اگر (allow_modeset) {
        atomic_flags |= DRM_منوال_ATOMIC_ALLOW_MODESET;
    }

    /* Never issue a new atomic commit if previous has not yet completed,
       or it will error. */
    drm_atomic_waitpending(_this, dispdata);

    ret = KMSDRM_drm_منوال_Atomic_Commit(viddata->drm_fd, dispdata->atomic_req,
              atomic_flags, تہی);

    اگر (ret) {
        SDL_سیٹ_Error("Atomic commit failed, returned %d.", ret);
        /* Uncomment this for fast-debugging */
#اگر 0
        SDL_Log("ATOMIC COMMIT FAILED: %s.", strerror(errno));
#اگر_ختم
        جاؤ برآمد;
    }

    اگر (dispdata->kms_اندر_fence_fd != -1) {
        close(dispdata->kms_اندر_fence_fd);
        dispdata->kms_اندر_fence_fd = -1;
    }

برآمد:
    KMSDRM_drm_منوال_Atomic_Free(dispdata->atomic_req);
    dispdata->atomic_req = تہی;

    واپس ret;
}

خالی
drm_atomic_waitpending(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata)
{
    /* Will return immediately if we have already destroyed the fence, because we NULL-ify it just after.
       Also, will return immediately in double-buffer mode, because kms_fence will alsawys be NULL. */
    اگر (dispdata->kms_fence) {
       EGLint حالت_2;

        کرو {
            حالت_2 = _this->egl_ڈیٹا->eglClientWaitSyncKHR(_this->egl_ڈیٹا->egl_display,
                dispdata->kms_fence, 0, EGL_FOREVER_KHR);
        } جب (حالت_2 != EGL_CONDITION_SATISFIED_KHR);

        _this->egl_ڈیٹا->eglDestroySyncKHR(_this->egl_ڈیٹا->egl_display, dispdata->kms_fence);
            dispdata->kms_fence = تہی;
    }
}

ساکن bool KMSDRM_دستیاب(خالی)
{
#اگر_تعریف_شدہ SDL_PLATFORM_OPENBSD
    ساخت utsname nameofsystem;
    دوہرا releaseversion;
#اگر_ختم
    صحیح ret = -ENOENT;

#اگر_تعریف_شدہ SDL_PLATFORM_OPENBSD
    اگر (!(uname(&nameofsystem) < 0)) {
        releaseversion = SDL_atof(nameofsystem.release);
        اگر (releaseversion >= 6.9) {
            moderndri = true;
        }
    }
#اگر_ختم

    اگر (moderndri) {
        SDL_strlcpy(kmsdrm_dri_راستہ, "/dev/dri/", حجم(kmsdrm_dri_راستہ));
        SDL_strlcpy(kmsdrm_dri_devname, "card", حجم(kmsdrm_dri_devname));
    } ورنہ {
        SDL_strlcpy(kmsdrm_dri_راستہ, "/dev/", حجم(kmsdrm_dri_راستہ));
        SDL_strlcpy(kmsdrm_dri_devname, "drm", حجم(kmsdrm_dri_devname));
    }

    kmsdrm_dri_pathsize = SDL_strlen(kmsdrm_dri_راستہ);
    kmsdrm_dri_devnamesize = SDL_strlen(kmsdrm_dri_devname);
    (خالی)SDL_snprintf(kmsdrm_dri_cardpath, حجم(kmsdrm_dri_cardpath), "%s%s",
                       kmsdrm_dri_راستہ, kmsdrm_dri_devname);

    ret = get_driindex();
    اگر (ret >= 0) {
        واپس true;
    }

    واپس false;
}

ساکن خالی KMSDRM_DeleteDevice(SDL_VideoDevice *device)
{
    اگر (device->اندرونی_2) {
        SDL_free(device->اندرونی_2);
        device->اندرونی_2 = تہی;
    }

    SDL_free(device);

    SDL_KMSDRM_UnloadSymbols();
}

ساکن SDL_VideoDevice *KMSDRM_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *viddata;
    صحیح devindex;

    اگر (!KMSDRM_دستیاب()) {
        واپس تہی;
    }

    devindex = get_driindex();
    اگر (devindex < 0) {
        SDL_سیٹ_Error("devindex (%d) must not be negative.", devindex);
        واپس تہی;
    }

    اگر (!SDL_KMSDRM_بھرو_Symbols()) {
        واپس تہی;
    }

    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    viddata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!viddata) {
        جاؤ cleanup;
    }
    viddata->devindex = devindex;
    viddata->drm_fd = -1;

    device->اندرونی_2 = viddata;

    // Setup all functions which we can handle
    device->VideoInit = KMSDRM_VideoInit;
    device->VideoQuit = KMSDRM_VideoQuit;
    device->GetDisplayModes = KMSDRM_GetDisplayModes;
    device->سیٹ_Display_منوال = KMSDRM_سیٹ_Display_منوال;
    device->CreateSDLWindow = KMSDRM_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = KMSDRM_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = KMSDRM_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = KMSDRM_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Fullscreen = KMSDRM_سیٹ_کھڑکی_Fullscreen;
    device->Show_کھڑکی = KMSDRM_Show_کھڑکی;
    device->Hide_کھڑکی = KMSDRM_Hide_کھڑکی;
    device->Raise_کھڑکی = KMSDRM_Raise_کھڑکی;
    device->Maximize_کھڑکی = KMSDRM_Maximize_کھڑکی;
    device->Minimize_کھڑکی = KMSDRM_Minimize_کھڑکی;
    device->Restore_کھڑکی = KMSDRM_Restore_کھڑکی;
    device->Destroy_کھڑکی = KMSDRM_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_Focusable = KMSDRM_سیٹ_کھڑکی_Focusable;

    device->GL_بھرو_Library = KMSDRM_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = KMSDRM_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = KMSDRM_GLES_UnloadLibrary;
    device->GL_CreateContext = KMSDRM_GLES_CreateContext;
    device->GL_MakeCurrent = KMSDRM_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = KMSDRM_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = KMSDRM_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = KMSDRM_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = KMSDRM_GLES_DestroyContext;
    device->GL_سیٹ_Default_Profile_Config = KMSDRM_GLES_سیٹ_Default_Profile_Config;

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = KMSDRM_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = KMSDRM_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = KMSDRM_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = KMSDRM_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = KMSDRM_Vulkan_DestroySurface;
#اگر_ختم

    device->PumpEvents = KMSDRM_PumpEvents;
    device->آزاد = KMSDRM_DeleteDevice;

    واپس device;

cleanup:
    SDL_free(device);

    SDL_free(viddata);
    واپس تہی;
}

VideoBootStrap KMSDRM_bootstrap = {
    "kmsdrm",
    "KMS/DRM Video Driver",
    KMSDRM_CreateDevice,
    تہی, // no ShowMessageBox implementation
    false
};

ساکن خالی KMSDRM_FBDestroyCallback(ساخت gbm_bo *bo, خالی *ڈیٹا)
{
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)ڈیٹا;

    اگر (fb_info && fb_info->drm_fd >= 0 && fb_info->fb_id != 0) {
        KMSDRM_drm_منوال_Rm_FB(fb_info->drm_fd, fb_info->fb_id);
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Delete DRM FB %u", fb_info->fb_id);
    }

    SDL_free(fb_info);
}

KMSDRM_FBInfo *KMSDRM_FBFromBO(SDL_VideoDevice *_this, ساخت gbm_bo *bo)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    غیرعلامتی w, h;
    صحیح rc = -1;
    صحیح عدد_planes = 0;
    uint32_t format, strides[4] = { 0 }, handles[4] = { 0 }, offsets[4] = { 0 }, flags = 0;
    uint64_t modifiers[4] = { 0 };

    // Check for an existing framebuffer
    KMSDRM_FBInfo *fb_info = (KMSDRM_FBInfo *)KMSDRM_gbm_bo_get_user_ڈیٹا(bo);

    اگر (fb_info) {
        واپس fb_info;
    }

    /* Create a structure that contains enough info to remove the framebuffer
       when the backing buffer is destroyed */
    fb_info = (KMSDRM_FBInfo *)SDL_calloc(1, حجم(KMSDRM_FBInfo));

    اگر (!fb_info) {
        واپس تہی;
    }

    fb_info->drm_fd = viddata->drm_fd;

    /* Create framebuffer object for the buffer using the modifiers requested by GBM.
       Use of the modifiers is necessary on some platforms. */
    w = KMSDRM_gbm_bo_get_چوڑائی(bo);
    h = KMSDRM_gbm_bo_get_اونچائی(bo);
    format = KMSDRM_gbm_bo_get_format(bo);

    اگر (KMSDRM_drm_منوال_جوڑو_FB2_With_Modifiers &&
        KMSDRM_gbm_bo_get_modifier &&
        KMSDRM_gbm_bo_get_plane_گنتی &&
        KMSDRM_gbm_bo_get_انحراف &&
        KMSDRM_gbm_bo_get_stride_for_plane &&
        KMSDRM_gbm_bo_get_handle_for_plane) {

        modifiers[0] = KMSDRM_gbm_bo_get_modifier(bo);
        عدد_planes = KMSDRM_gbm_bo_get_plane_گنتی(bo);
        برائے (صحیح i = 0; i < عدد_planes; i++) {
            strides[i] = KMSDRM_gbm_bo_get_stride_for_plane(bo, i);
            handles[i] = KMSDRM_gbm_bo_get_handle_for_plane(bo, i).u32;
            offsets[i] = KMSDRM_gbm_bo_get_انحراف(bo, i);
            modifiers[i] = modifiers[0];
        }

        اگر (modifiers[0] && modifiers[0] != DRM_FORMAT_MOD_INVALID) {
            flags = DRM_منوال_FB_MODIFIERS;
        }

        rc = KMSDRM_drm_منوال_جوڑو_FB2_With_Modifiers(viddata->drm_fd, w, h, format, handles, strides, offsets, modifiers, &fb_info->fb_id, flags);
    }

    اگر (rc < 0) {
        strides[0] = KMSDRM_gbm_bo_get_stride(bo);
        handles[0] = KMSDRM_gbm_bo_get_handle(bo).u32;
        rc = KMSDRM_drm_منوال_جوڑو_FB(viddata->drm_fd, w, h, 24, 32, strides[0], handles[0], &fb_info->fb_id);
    }

    اگر (rc < 0) {
        SDL_free(fb_info);
        واپس تہی;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "New DRM FB (%u): %ux%u, from BO %p",
                 fb_info->fb_id, w, h, (خالی *)bo);

    // Associate our DRM framebuffer with this buffer object
    KMSDRM_gbm_bo_سیٹ_user_ڈیٹا(bo, fb_info, KMSDRM_FBDestroyCallback);

    واپس fb_info;
}

ساکن خالی KMSDRM_FlipHandler(صحیح fd, غیرعلامتی صحیح چوکھٹا, غیرعلامتی صحیح sec, غیرعلامتی صحیح usec, خالی *ڈیٹا)
{
    *((bool *)ڈیٹا) = false;
}

bool KMSDRM_WaitPageflip(SDL_VideoDevice *_this, SDL_کھڑکی_ڈیٹا *windata)
{

    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    drmEventContext ev = { 0 };
    ساخت pollfd pfd = { 0 };
    صحیح ret;

    ev.نسخہ = DRM_EVENT_CONTEXT_نسخہ;
    ev.صفحہ_flip_handler = KMSDRM_FlipHandler;

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
    جب (windata->انتظار_for_flip) {

        pfd.revents = 0;

        /* poll() waits for events arriving on the FD, and returns < 0 if timeout passes
           with no events or a signal occurred before any requested event (-EINTR).
           We wait forever (timeout = -1), but even if we DO get an event, we have yet
           to see if it's of the required type, then if it's a pageflip, etc */
        ret = poll(&pfd, 1, -1);

        اگر (ret < 0) {
            اگر (errno == EINTR) {
                /* poll() returning < 0 and setting errno = EINTR means there was a signal before
                   any requested event, so we immediately poll again. */
                جاری;
            } ورنہ {
                // There was another error. Don't pull again or we could get into a busy loop.
                SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll error");
                واپس false;
            }
        }

        اگر (pfd.revents & (POLLHUP | POLLERR)) {
            // An event arrived on the FD in time, but it's an error.
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "DRM poll hup or error");
            واپس false;
        }

        اگر (pfd.revents & POLLIN) {
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

    واپس true;
}

/* Given w, h and refresh rate, returns the closest DRM video mode
   available on the DRM connector of the display.
   We use the SDL mode list (which we filled in KMSDRM_GetDisplayModes)
   because it's ordered, while the list on the connector is mostly random.*/
ساکن drm_منوال_منوال_Info *KMSDRM_Get_Closest_Display_منوال(SDL_VideoDisplay *display, صحیح چوڑائی, صحیح اونچائی)
{

    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;
    drm_منوال_Connector *conn = dispdata->connector.connector;

    SDL_Display_منوال closest;
    drm_منوال_منوال_Info *drm_منوال;

    اگر (SDL_Get_Closest_Fullscreen_Display_منوال(display->id, چوڑائی, اونچائی, 0.0f, false, &closest)) {
        ثابت SDL_Display_منوال_ڈیٹا *modedata = closest.اندرونی_2;
        drm_منوال = &conn->modes[modedata->منوال_اشاریہ];
        واپس drm_منوال;
    } ورنہ {
        واپس تہی;
    }
}

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/* _this is a SDL_VideoDevice *                                              */
/*****************************************************************************/

ساکن bool KMSDRM_DropMaster(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;

    اگر (viddata->is_atomic) {  // turn off atomic support until we are in control again.
        KMSDRM_drm_سیٹ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_ATOMIC, 0);
        KMSDRM_drm_سیٹ_Client_Cap(viddata->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 0);
    }

    /* Check if we have DRM master to begin with */
    اگر (KMSDRM_drmAuthMagic(viddata->drm_fd, 0) == -EACCES) {
        /* Nope, nothing to do then */
        واپس true;
    }

    واپس KMSDRM_drmDropMaster(viddata->drm_fd) == 0;
}

// Deinitializes the internal of the SDL Displays in the SDL display list.
ساکن خالی KMSDRM_DeinitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_DisplayID *displays;
    SDL_Display_ڈیٹا *dispdata;
    صحیح i;

    displays = SDL_GetDisplays(تہی);
    اگر (displays) {
        // Iterate on the SDL Display list.
        برائے (i = 0; displays[i]; ++i) {

            // Get the internal for this display
            dispdata = SDL_Get_Display_Driver_ڈیٹا(displays[i]);

            // Free connector
            اگر (dispdata && dispdata->connector.connector) {
                KMSDRM_drm_منوال_Free_Connector(dispdata->connector.connector);
                dispdata->connector.connector = تہی;
            }

            // Free CRTC
            اگر (dispdata && dispdata->crtc.crtc) {
                KMSDRM_drm_منوال_Free_Crtc(dispdata->crtc.crtc);
                dispdata->crtc.crtc = تہی;
            }
        }
        SDL_free(displays);
    }

    اگر (viddata->drm_fd >= 0) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }
}

ساکن bool KMSDRM_ConnectorCheckVrrCapable(uint32_t drm_fd, uint32_t output_id)
{
    bool ملا = false;
    uint64_t prop_قدر = 0;

    drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(drm_fd, output_id, DRM_منوال_OBJECT_CONNECTOR);
    اگر (props) {
        برائے (uint32_t i = 0; !ملا && i < props->گنتی_props; ++i) {
            drm_منوال_Property_Ptr prop = KMSDRM_drm_منوال_Get_Property(drm_fd, props->props[i]);
            اگر (prop) {
                اگر (SDL_strcasecmp(prop->name, "VRR_CAPABLE") == 0) {
                    prop_قدر = props->prop_اقدار[i];
                    ملا = true;
                }
                KMSDRM_drm_منوال_Free_Property(prop);
            }
        }
        KMSDRM_drm_منوال_Free_Object_Properties(props);
    }
    اگر (ملا) {
        واپس prop_قدر ? true : false;
    }
    واپس false;
}

ساکن bool KMSDRM_VrrPropId(uint32_t drm_fd, uint32_t crtc_id, uint32_t *vrr_prop_id)
{
    bool ملا = false;
    drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(drm_fd, crtc_id, DRM_منوال_OBJECT_CRTC);
    اگر (props) {
        برائے (uint32_t i = 0; !ملا && i < props->گنتی_props; ++i) {
            drm_منوال_Property_Ptr prop = KMSDRM_drm_منوال_Get_Property(drm_fd, props->props[i]);
            اگر (prop) {
                اگر (SDL_strcmp(prop->name, "VRR_ENABLED") == 0) {
                    *vrr_prop_id = prop->prop_id;
                    ملا = true;
                }
                KMSDRM_drm_منوال_Free_Property(prop);
            }
        }
        KMSDRM_drm_منوال_Free_Object_Properties(props);
    }
    واپس ملا;
}

ساکن خالی KMSDRM_Crtc_سیٹ_Vrr(uint32_t drm_fd, uint32_t crtc_id, bool enabled)
{
    uint32_t vrr_prop_id;
    اگر (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        واپس;
    }

    KMSDRM_drm_منوال_Object_سیٹ_Property(drm_fd, crtc_id, DRM_منوال_OBJECT_CRTC, vrr_prop_id, enabled);
}

ساکن bool KMSDRM_CrtcGetVrr(uint32_t drm_fd, uint32_t crtc_id)
{
    uint32_t vrr_prop_id = 0;
    bool ملا = false;
    uint64_t prop_قدر = 0;

    اگر (!KMSDRM_VrrPropId(drm_fd, crtc_id, &vrr_prop_id)) {
        واپس false;
    }

    drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(drm_fd, crtc_id, DRM_منوال_OBJECT_CRTC);
    اگر (props) {
        برائے (uint32_t i = 0; !ملا && i < props->گنتی_props; ++i) {
            drm_منوال_Property_Ptr prop = KMSDRM_drm_منوال_Get_Property(drm_fd, props->props[i]);
            اگر (prop) {
                اگر (prop->prop_id == vrr_prop_id) {
                    prop_قدر = props->prop_اقدار[i];
                    ملا = true;
                }
                KMSDRM_drm_منوال_Free_Property(prop);
            }
        }
        KMSDRM_drm_منوال_Free_Object_Properties(props);
    }
    اگر (ملا) {
        واپس prop_قدر ? true : false;
    }
    واپس false;
}

ساکن صحیح KMSDRM_CrtcGetOrientation(uint32_t drm_fd, uint32_t crtc_id)
{
    bool ملا = false;
    صحیح orientation = 0;

    drm_منوال_Object_Properties_Ptr props = KMSDRM_drm_منوال_Object_Get_Properties(drm_fd, crtc_id, DRM_منوال_OBJECT_CONNECTOR);
    اگر (props) {
        برائے (uint32_t i = 0; !ملا && i < props->گنتی_props; ++i) {
            drm_منوال_Property_Ptr prop = KMSDRM_drm_منوال_Get_Property(drm_fd, props->props[i]);
            اگر (prop) {
                اگر (SDL_strcasecmp(prop->name, "panel orientation") == 0 && (prop->flags & DRM_منوال_PROP_ENUM)) {
                    اگر (prop->گنتی_enums) {
                        // "Normal" is the default of no rotation (0 degrees)
                        اگر (SDL_strcmp(prop->enums[0].name, "Left Side Up") == 0) {
                            orientation = 90;
                        } ورنہ اگر (SDL_strcmp(prop->enums[0].name, "Upside Down") == 0) {
                            orientation = 180;
                        } ورنہ اگر (SDL_strcmp(prop->enums[0].name, "Right Side Up") == 0) {
                            orientation = 270;
                        }
                    }
                    ملا = true;
                }
                KMSDRM_drm_منوال_Free_Property(prop);
            }
        }
        KMSDRM_drm_منوال_Free_Object_Properties(props);
    }
    واپس orientation;
}

/* Gets a DRM connector, builds an SDL_Display with it, and adds it to the
   list of SDL Displays in _this->displays[]  */
ساکن خالی KMSDRM_جوڑو_Display(SDL_VideoDevice *_this, drm_منوال_Connector *conn, drm_منوال_Res *resources)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_Display_ڈیٹا *dispdata = تہی;
    SDL_VideoDisplay display = { 0 };
    SDL_Display_منوال_ڈیٹا *modedata = تہی;
    drm_منوال_Encoder *encoder = تہی;
    drm_منوال_Crtc *crtc = تہی;
    ثابت حرف *connector_type = تہی;
    SDL_DisplayID display_id;
    SDL_PropertiesID display_properties;
    حرف name_fmt[64];
    صحیح orientation;
    صحیح منوال_اشاریہ;
    صحیح i, j;
    صحیح ret = 0;

    // Reserve memory for the new display's internal.
    dispdata = (SDL_Display_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_ڈیٹا));
    اگر (!dispdata) {
        ret = -1;
        جاؤ cleanup;
    }

    /* Initialize some of the members of the new display's internal
       to sane values. */
    dispdata->cursor_bo = تہی;
    dispdata->cursor_bo_drm_fd = -1;
    dispdata->kms_اندر_fence_fd = -1;
    dispdata->kms_برآمد_fence_fd = -1;

    /* Since we create and show the default cursor on KMSDRM_InitMouse(),
       and we call KMSDRM_InitMouse() when we create a window, we have to know
       if the display used by the window already has a default cursor or not.
       If we don't, new default cursors would stack up on mouse->cursors and SDL
       would have to hide and delete them at quit, not to mention the memory leak... */
    dispdata->default_cursor_init = false;

    // Try to find the connector's current encoder
    برائے (i = 0; i < resources->گنتی_encoders; i++) {
        encoder = KMSDRM_drm_منوال_Get_Encoder(viddata->drm_fd, resources->encoders[i]);

        اگر (!encoder) {
            جاری;
        }

        اگر (encoder->encoder_id == conn->encoder_id) {
            توڑو;
        }

        KMSDRM_drm_منوال_Free_Encoder(encoder);
        encoder = تہی;
    }

    اگر (!encoder) {
        // No encoder was connected, find the first supported one
        برائے (i = 0; i < resources->گنتی_encoders; i++) {
            encoder = KMSDRM_drm_منوال_Get_Encoder(viddata->drm_fd,
                                               resources->encoders[i]);

            اگر (!encoder) {
                جاری;
            }

            برائے (j = 0; j < conn->گنتی_encoders; j++) {
                اگر (conn->encoders[j] == encoder->encoder_id) {
                    توڑو;
                }
            }

            اگر (j != conn->گنتی_encoders) {
                توڑو;
            }

            KMSDRM_drm_منوال_Free_Encoder(encoder);
            encoder = تہی;
        }
    }

    اگر (!encoder) {
        ret = SDL_سیٹ_Error("No connected encoder found for connector.");
        جاؤ cleanup;
    }

    // Try to find a CRTC connected to this encoder
    crtc = KMSDRM_drm_منوال_Get_Crtc(viddata->drm_fd, encoder->crtc_id);

    /* If no CRTC was connected to the encoder, find the first CRTC
       that is supported by the encoder, and use that. */
    اگر (!crtc) {
        برائے (i = 0; i < resources->گنتی_crtcs; i++) {
            اگر (encoder->possible_crtcs & (1 << i)) {
                encoder->crtc_id = resources->crtcs[i];
                crtc = KMSDRM_drm_منوال_Get_Crtc(viddata->drm_fd, encoder->crtc_id);
                توڑو;
            }
        }
    }

    اگر (!crtc) {
        ret = SDL_سیٹ_Error("No CRTC found for connector.");
        جاؤ cleanup;
    }

    // Find the index of the mode attached to this CRTC
    منوال_اشاریہ = -1;

    برائے (i = 0; i < conn->گنتی_modes; i++) {
        drm_منوال_منوال_Info *منوال = &conn->modes[i];

        اگر (!SDL_memcmp(منوال, &crtc->منوال, حجم(crtc->منوال))) {
            منوال_اشاریہ = i;
            توڑو;
        }
    }

    اگر (منوال_اشاریہ == -1) {
        صحیح current_area, سب_سے_بڑا_area = 0;

        // Find the preferred mode or the highest resolution mode
        برائے (i = 0; i < conn->گنتی_modes; i++) {
            drm_منوال_منوال_Info *منوال = &conn->modes[i];

            اگر (منوال->type & DRM_منوال_TYPE_PREFERRED) {
                منوال_اشاریہ = i;
                توڑو;
            }

            current_area = منوال->hdisplay * منوال->vdisplay;
            اگر (current_area > سب_سے_بڑا_area) {
                منوال_اشاریہ = i;
                سب_سے_بڑا_area = current_area;
            }
        }
        اگر (منوال_اشاریہ != -1) {
            crtc->منوال = conn->modes[منوال_اشاریہ];
        }
    }

    اگر (منوال_اشاریہ == -1) {
        ret = SDL_سیٹ_Error("Failed to find index of mode attached to the CRTC.");
        جاؤ cleanup;
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
    dispdata->منوال = crtc->منوال;
    dispdata->original_منوال = crtc->منوال;
    dispdata->fullscreen_منوال = crtc->منوال;

    اگر (dispdata->منوال.hdisplay == 0 || dispdata->منوال.vdisplay == 0) {
        ret = SDL_سیٹ_Error("Couldn't get a valid connector videomode.");
        جاؤ cleanup;
    }

    // Store the connector and crtc for this display.
    dispdata->connector.connector = conn;
    dispdata->crtc.crtc = crtc;

    // save previous vrr state
    dispdata->saved_vrr = KMSDRM_CrtcGetVrr(viddata->drm_fd, crtc->crtc_id);
    // try to enable vrr
    اگر (KMSDRM_ConnectorCheckVrrCapable(viddata->drm_fd, conn->connector_id)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Enabling VRR");
        KMSDRM_Crtc_سیٹ_Vrr(viddata->drm_fd, crtc->crtc_id, true);
    }

    // Set the name by the connector type, if possible
    اگر (KMSDRM_drm_منوال_Get_Connector_Type_Name) {
        connector_type = KMSDRM_drm_منوال_Get_Connector_Type_Name(conn->connector_type);
        اگر (connector_type == تہی) {
            connector_type = "Unknown";
        }
        SDL_snprintf(name_fmt, حجم(name_fmt), "%s-%u", connector_type, conn->connector_type_id);
    }

    dispdata->crtc.props = KMSDRM_drm_منوال_Object_Get_Properties(viddata->drm_fd, crtc->crtc_id, DRM_منوال_OBJECT_CRTC);
    dispdata->crtc.props_info = SDL_calloc(dispdata->crtc.props->گنتی_props, حجم(*dispdata->crtc.props_info));
    اگر (!dispdata->crtc.props_info) {
        ret = false;
        جاؤ cleanup;
    }

    برائے (i = 0; i < dispdata->crtc.props->گنتی_props; i++) {
        dispdata->crtc.props_info[i] = KMSDRM_drm_منوال_Get_Property(viddata->drm_fd, dispdata->crtc.props->props[i]);
    }

    /* Get connector properties */
    dispdata->connector.props = KMSDRM_drm_منوال_Object_Get_Properties(viddata->drm_fd, conn->connector_id, DRM_منوال_OBJECT_CONNECTOR);
    dispdata->connector.props_info = SDL_calloc(dispdata->connector.props->گنتی_props, حجم(*dispdata->connector.props_info));
    اگر (!dispdata->connector.props_info) {
        ret = false;
        جاؤ cleanup;
    }

    برائے (i = 0; i < dispdata->connector.props->گنتی_props; i++) {
        dispdata->connector.props_info[i] = KMSDRM_drm_منوال_Get_Property(viddata->drm_fd,
        dispdata->connector.props->props[i]);
    }

    /*****************************************/
    // Part 2: setup the SDL_Display itself.
    /*****************************************/

    /* Setup the display.
       There's no problem with it being still incomplete. */
    modedata = SDL_calloc(1, حجم(SDL_Display_منوال_ڈیٹا));

    اگر (!modedata) {
        ret = -1;
        جاؤ cleanup;
    }

    modedata->منوال_اشاریہ = منوال_اشاریہ;

    display.اندرونی_2 = dispdata;
    display.desktop_منوال.w = dispdata->منوال.hdisplay;
    display.desktop_منوال.h = dispdata->منوال.vdisplay;
    Calculate_Refresh_شرح(&dispdata->منوال, &display.desktop_منوال.refresh_شرح_numerator, &display.desktop_منوال.refresh_شرح_denominator);
    display.desktop_منوال.format = SDL_PIXELFORMAT_ARGB8888;
    display.desktop_منوال.اندرونی_2 = modedata;
    اگر (connector_type) {
        display.name = name_fmt;
    }

    // Add the display to the list of SDL displays.
    display_id = SDL_جوڑو_Video_Display(&display, false);
    اگر (!display_id) {
        ret = -1;
        جاؤ cleanup;
    }

    orientation = KMSDRM_CrtcGetOrientation(viddata->drm_fd, crtc->crtc_id);
    display_properties = SDL_GetDisplayProperties(display_id);
    SDL_سیٹ_نمبر_Property(display_properties, SDL_PROP_DISPLAY_KMSDRM_PANEL_ORIENTATION_نمبر, orientation);

#اگر_تعریف_شدہ DEBUG_KMSDRM  // Use this if you ever need to see info on all available planes.
    get_planes_info(_this, dispdata);
#اگر_ختم

cleanup:
    اگر (encoder) {
        KMSDRM_drm_منوال_Free_Encoder(encoder);
    }
    اگر (ret) {
        // Error (complete) cleanup
        اگر (dispdata) {
            اگر (dispdata->connector.connector) {
                KMSDRM_drm_منوال_Free_Connector(dispdata->connector.connector);
            }
            اگر (dispdata->crtc.crtc) {
                KMSDRM_drm_منوال_Free_Crtc(dispdata->crtc.crtc);
            }
            SDL_free(dispdata->connector.props_info);
            SDL_free(dispdata->crtc.props_info);
            SDL_free(dispdata->display_plane);
            SDL_free(dispdata);
        }
    }
} // NOLINT(clang-analyzer-unix.Malloc): If no error `dispdata` is saved in the display

ساکن خالی KMSDRM_ترتیب_دو_Displays(SDL_VideoDevice *_this)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ترجیح);

    اگر (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(حجم(SDL_VideoDisplay *) * _this->عدد_displays);

        اگر (str && sorted_list) {
            صحیح sorted_اشاریہ = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            جب (token) {
                برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    اگر (d && SDL_strcmp(token, d->name) == 0) {
                        sorted_list[sorted_اشاریہ++] = d;
                        _this->displays[i] = تہی;
                        توڑو;
                    }
                }

                token = SDL_strtok_r(تہی, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
                اگر (_this->displays[i]) {
                    sorted_list[sorted_اشاریہ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, حجم(SDL_VideoDisplay *) * _this->عدد_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساکن bool سیٹ_client_atomic_caps(صحیح fd)
{
    اگر (!SDL_GetHintBoolean(SDL_HINT_KMSDRM_ATOMIC, true)) {
        واپس false;  // emergency escape hatch.
    } ورنہ اگر (KMSDRM_drm_سیٹ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 1)) {
        واپس false;  // no atomic modesetting support.
    } ورنہ اگر (KMSDRM_drm_سیٹ_Client_Cap(fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1)) {
        KMSDRM_drm_سیٹ_Client_Cap(fd, DRM_CLIENT_CAP_ATOMIC, 0);  // turn this back off again.
        واپس false;  // no universal planes support.
    }
    واپس true;
}

/* Initializes the list of SDL displays: we build a new display for each
   connecter connector we find.
   This is to be called early, in VideoInit(), because it gets us
   the videomode information, which SDL needs immediately after VideoInit(). */
ساکن bool KMSDRM_InitDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    drm_منوال_Res *resources = تہی;
    uint64_t async_pageflip = 0;
    صحیح i;
    bool نتیجہ = true;

    // Open /dev/dri/cardNN (/dev/drmN if on OpenBSD version less than 6.9)
    (خالی)SDL_snprintf(viddata->devpath, حجم(viddata->devpath), "%s%d",
                       kmsdrm_dri_cardpath, viddata->devindex);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opening device %s", viddata->devpath);
    viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);

    اگر (viddata->drm_fd < 0) {
        نتیجہ = SDL_سیٹ_Error("Could not open %s", viddata->devpath);
        جاؤ cleanup;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Opened DRM FD (%d)", viddata->drm_fd);

    // Set ATOMIC & UNIVERSAL PLANES compatibility
    viddata->is_atomic = سیٹ_client_atomic_caps(viddata->drm_fd);

    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "DRM FD (%d) %s atomic", viddata->drm_fd, viddata->is_atomic ? "SUPPORTS" : "DOES NOT SUPPORT");

    // Get all of the available connectors / devices / crtcs
    resources = KMSDRM_drm_منوال_Get_Resources(viddata->drm_fd);
    اگر (!resources) {
        نتیجہ = SDL_سیٹ_Error("drmModeGetResources(%d) failed", viddata->drm_fd);
        جاؤ cleanup;
    }

    /* Iterate on the available connectors. For every connected connector,
       we create an SDL_Display and add it to the list of SDL Displays. */
    برائے (i = 0; i < resources->گنتی_connectors; i++) {
        drm_منوال_Connector *conn = KMSDRM_drm_منوال_Get_Connector(viddata->drm_fd, resources->connectors[i]);
        اگر (!conn) {
            جاری;
        }

        اگر (conn->connection == DRM_منوال_CONNECTED && conn->گنتی_modes) {
            /* If it's a connected connector with available videomodes, try to add
               an SDL Display representing it. KMSDRM_AddDisplay() is purposely void,
               so if it fails (no encoder for connector, no valid video mode for
               connector etc...) we can keep looking for connected connectors. */
            KMSDRM_جوڑو_Display(_this, conn, resources);
        } ورنہ {
            // If it's not, free it now.
            KMSDRM_drm_منوال_Free_Connector(conn);
        }
    }

    // Have we added any SDL displays?
    اگر (SDL_GetPrimaryDisplay() == 0) {
        نتیجہ = SDL_سیٹ_Error("No connected displays found.");
        جاؤ cleanup;
    }

    // Sort the displays, if necessary
    KMSDRM_ترتیب_دو_Displays(_this);

    // Determine if video hardware supports async pageflips.
    اگر (KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_ASYNC_صفحہ_FLIP, &async_pageflip) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not determine async page flip capability.");
    }
    viddata->async_pageflip_support = async_pageflip ? true : false;

    /***********************************/
    // Block for Vulkan compatibility.
    /***********************************/

    /* Vulkan requires DRM master on its own FD to work, so try to drop master
       on our FD. This will only work without root on kernels v5.8 and later.
       If it doesn't work, just close the FD and we'll reopen it later. */
    اگر (!KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

cleanup:
    اگر (resources) {
        KMSDRM_drm_منوال_Free_Resources(resources);
    }
    اگر (!نتیجہ) {
        اگر (viddata->drm_fd >= 0) {
            close(viddata->drm_fd);
            viddata->drm_fd = -1;
        }
    }
    واپس نتیجہ;
}

/* Init the Vulkan-INCOMPATIBLE stuff:
   Reopen FD, create gbm dev, create dumb buffer and setup display plane.
   This is to be called late, in WindowCreate(), and ONLY if this is not
   a Vulkan window.
   We are doing this so late to allow Vulkan to work if we build a VK window.
   These things are incompatible with Vulkan, which accesses the same resources
   internally so they must be free when trying to build a Vulkan surface.
*/
ساکن bool KMSDRM_GBMInit(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    bool نتیجہ = true;

    // Reopen the FD if we weren't able to drop master on the original one
    اگر (viddata->drm_fd < 0) {
        viddata->drm_fd = open(viddata->devpath, O_RDWR | O_CLOEXEC);
        اگر (viddata->drm_fd < 0) {
            واپس SDL_سیٹ_Error("Could not reopen %s", viddata->devpath);
        }
    }

    viddata->is_atomic = سیٹ_client_atomic_caps(viddata->drm_fd);

    // Set the FD as current DRM master.
    KMSDRM_drm_سیٹ_Master(viddata->drm_fd);

    // Create the GBM device.
    viddata->gbm_dev = KMSDRM_gbm_create_device(viddata->drm_fd);
    اگر (!viddata->gbm_dev) {
        نتیجہ = SDL_سیٹ_Error("Couldn't create gbm device.");
    } ورنہ {
        // Setup the display plane. ONLY do this after dispdata has the right
        // crtc and connector, because these are used in this function.
        نتیجہ = تیاری_plane(_this, dispdata, &dispdata->display_plane, DRM_PLANE_TYPE_PRIMARY);
        اگر (!نتیجہ) {
            SDL_سیٹ_Error("can't find suitable display plane.");
        }
    }

    viddata->gbm_init = true;

    واپس نتیجہ;
}

// Deinit the Vulkan-incompatible KMSDRM stuff.
ساکن خالی KMSDRM_GBMDeinit(SDL_VideoDevice *_this, SDL_Display_ڈیٹا *dispdata)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;

    // Free display plane
    free_plane(&dispdata->display_plane);

    // Free cursor plane (if still not freed)
    free_plane(&dispdata->cursor_plane);

    /* Destroy GBM device. GBM surface is destroyed by DestroySurfaces(),
       already called when we get here. */
    اگر (viddata->gbm_dev) {
        KMSDRM_gbm_device_destroy(viddata->gbm_dev);
        viddata->gbm_dev = تہی;
    }

    /* Finally drop DRM master if possible, otherwise close DRM FD.
       May be reopened on next non-vulkan window creation. */
    اگر (viddata->drm_fd >= 0 && !KMSDRM_DropMaster(_this)) {
        close(viddata->drm_fd);
        viddata->drm_fd = -1;
    }

    viddata->gbm_init = false;
}

ساکن خالی KMSDRM_DestroySurfaces(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *windata = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *dispdata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    صحیح ret;

    /**********************************************/
    // Wait for last issued pageflip to complete.
    /**********************************************/
    // KMSDRM_WaitPageflip(_this, windata);

    اگر (viddata->is_atomic) {

    /* TODO : Continue investigating why this doesn't work. We should do this instead
       of making the display plane point to the TTY console, which isn't there
       after creating and destroying a Vulkan window. */

#اگر 0  // (note that this code has bitrotted a little, in addition to TODO comment above.)
        /* Disconnect the connector from the CRTC (remember: several connectors
           can read a CRTC), deactivate the CRTC, and set the PRIMARY PLANE props
           CRTC_ID and FB_ID to 0. Then we can destroy the GBM buffers and surface. */
        جوڑو_connector_property(dispdata->atomic_req, dispdata->connector , "CRTC_ID", 0);
        جوڑو_crtc_property(dispdata->atomic_req, dispdata->crtc , "MODE_ID", 0);
        جوڑو_crtc_property(dispdata->atomic_req, dispdata->crtc , "active", 0);
        /**********************************************/
        /* Wait for last issued pageflip to complete. */
        /**********************************************/
        KMSDRM_Wait_صفحہ_Flip(_this, windata, -1);

        plane_info.plane = dispdata->display_plane;
        plane_info.crtc_id = 0;
        plane_info.fb_id = 0;
        /************************************************************************/
        /* Restore the original CRTC configuration: configure the crtc with the */
        /* original video mode and make it point to the original TTY buffer.    */
        /************************************************************************/

        drm_atomic_سیٹ_plane_props(dispdata, &plane_info);
        ret = KMSDRM_drm_منوال_سیٹ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                &dispdata->original_منوال);

        /* Issue atomic commit that is blocking and allows modesetting. */
        اگر (drm_atomic_commit(_this, dispdata, true, true)) {
            SDL_سیٹ_Error("Failed to issue atomic commit on surfaces destruction.");
        /* If we failed to set the original mode, try to set the connector preferred mode. */
        اگر (ret && (dispdata->crtc->منوال_valid == 0)) {
            ret = KMSDRM_drm_منوال_سیٹ_Crtc(viddata->drm_fd, dispdata->crtc->crtc_id,
                    dispdata->crtc->بفر_id, 0, 0, &dispdata->connector->connector_id, 1,
                    &dispdata->original_منوال);
        }
#اگر_ختم

#اگر 1
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
        plane_info.src_w = dispdata->original_منوال.hdisplay;
        plane_info.src_h = dispdata->original_منوال.vdisplay;
        plane_info.crtc_w = dispdata->original_منوال.hdisplay;
        plane_info.crtc_h = dispdata->original_منوال.vdisplay;

        drm_atomic_سیٹ_plane_props(dispdata, &plane_info);

        اگر (drm_atomic_commit(_this, dispdata, true, false)) {
            SDL_سیٹ_Error("Failed to issue atomic commit on surfaces destruction.");
        }
    }
#اگر_ختم

    /************************************************************************/
    // Restore the original CRTC configuration: configure the crtc with the
    // original video mode and make it point to the original TTY buffer.
    /************************************************************************/

    ret = KMSDRM_drm_منوال_سیٹ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                &dispdata->original_منوال);

    // If we failed to set the original mode, try to set the connector preferred mode.
    اگر (ret && (dispdata->crtc.crtc->منوال_valid == 0)) {
        ret = KMSDRM_drm_منوال_سیٹ_Crtc(viddata->drm_fd, dispdata->crtc.crtc->crtc_id,
                                    dispdata->crtc.crtc->بفر_id, 0, 0, &dispdata->connector.connector->connector_id, 1,
                                    &dispdata->original_منوال);
    }

    اگر (ret) {
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Could not restore CRTC");
    }

    /***************************/
    // Destroy the GBM buffers
    /***************************/

    اگر (windata->bo) {
        اگر (windata->bo != windata->اگلا_bo) {
            KMSDRM_gbm_surface_release_بفر(windata->gs, windata->bo);
        }
        windata->bo = تہی;
    }

    اگر (windata->اگلا_bo) {
        KMSDRM_gbm_surface_release_بفر(windata->gs, windata->اگلا_bo);
        windata->اگلا_bo = تہی;
    }

    /***************************/
    // Destroy the EGL surface
    /***************************/

    SDL_EGL_MakeCurrent(_this, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    اگر (windata->egl_surface != EGL_NO_SURFACE) {
        SDL_EGL_DestroySurface(_this, windata->egl_surface);
        windata->egl_surface = EGL_NO_SURFACE;
    }

    /***************************/
    // Destroy the GBM surface
    /***************************/

    اگر (windata->gs) {
        KMSDRM_gbm_surface_destroy(windata->gs);
        windata->gs = تہی;
    }
}

ساکن خالی KMSDRM_Get_منوال_مقصد_سیٹ(SDL_کھڑکی *کھڑکی, drm_منوال_منوال_Info *برآمد_منوال)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;

    اگر (کھڑکی->fullscreen_exclusive) {
        *برآمد_منوال = dispdata->fullscreen_منوال;
    } ورنہ {
        drm_منوال_منوال_Info *منوال = KMSDRM_Get_Closest_Display_منوال(display, کھڑکی->windowed.w, کھڑکی->windowed.h);
        اگر (منوال) {
            *برآمد_منوال = *منوال;
        } ورنہ {
            *برآمد_منوال = dispdata->original_منوال;
        }
    }
}

ساکن خالی KMSDRM_DirtySurfaces(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *windata = کھڑکی->اندرونی_2;
    drm_منوال_منوال_Info منوال;

    /* Can't recreate EGL surfaces right now, need to wait until SwapWindow
       so the correct thread-local surface and context state are available */
    windata->egl_surface_dirty = true;

    /* The app may be waiting for the resize event after calling SetWindowSize
       or SetWindowFullscreen, send a fake event for now since the actual
       recreation is deferred */
    KMSDRM_Get_منوال_مقصد_سیٹ(کھڑکی, &منوال);
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, منوال.hdisplay, منوال.vdisplay);
}

/* This determines the size of the fb, which comes from the GBM surface
   that we create here. */
bool KMSDRM_CreateSurfaces(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    ساکن ثابت ساخت { uint32_t fmt; ثابت حرف *name; صحیح r; صحیح g; صحیح b; صحیح a; } gbm_formats[] = {
        // !!! FIXME: I have no idea if this is a good preferred order for this list.
        #تعریف_کرو FMT(name, r, g, b, a) { GBM_FORMAT_##name, #name, r, g, b, a }
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
        #تعریف_منسوخ FMT
    };

    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *windata = کھڑکی->اندرونی_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;
    EGLContext egl_context;
    bool نتیجہ = false;

    // If the current window already has surfaces, destroy them before creating other.
    اگر (windata->gs) {
        KMSDRM_DestroySurfaces(_this, کھڑکی);
    }

    bool tried_setting_format = false;
    ثابت uint32_t surface_flags = GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING;
    برائے (صحیح i = 0; i < SDL_arraysize(gbm_formats); i++) {
        ثابت uint32_t surface_fmt = gbm_formats[i].fmt;

        SDL_Log("KMSDRM: Trying format GBM_FORMAT_%s", gbm_formats[i].name);

        اگر (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev, surface_fmt, surface_flags)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: GBM_FORMAT_%s is not supported.", gbm_formats[i].name);
            جاری;  // try the next one.
        }

        tried_setting_format = true;

        /* The KMSDRM backend doesn't always set the mode the higher-level code in
           SDL_video.c expects. Hulk-smash the display's current_mode to keep the
           mode that's set in sync with what SDL_video.c thinks is set

           FIXME: How do we do that now? Can we get a better idea at the higher level?
         */
        KMSDRM_Get_منوال_مقصد_سیٹ(کھڑکی, &dispdata->منوال);

        windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->منوال.hdisplay, dispdata->منوال.vdisplay, surface_fmt, surface_flags);
        اگر (!windata->gs && errno == ENOSYS) {
            // Try again without the scanout flags, needed on NVIDIA drivers
            windata->gs = KMSDRM_gbm_surface_create(viddata->gbm_dev, dispdata->منوال.hdisplay, dispdata->منوال.vdisplay, surface_fmt, 0);
        }
        اگر (!windata->gs) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: gbm_surface_create(GBM_FORMAT_%s) failed.", gbm_formats[i].name);
            SDL_سیٹ_Error("Could not create %s GBM surface: %s", gbm_formats[i].name, strerror(errno));  // set error in case this was the last supposedly-supported format.
            جاری;   // try the next one.
        }

        /* We can't get the EGL context yet because SDL_CreateRenderer has not been called,
           but we need an EGL surface NOW, or GL won't be able to render into any surface
           and we won't see the first frame. */
        SDL_EGL_سیٹ_Required_Visual_Id(_this, surface_fmt);
        windata->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)windata->gs);
        اگر (windata->egl_surface == EGL_NO_SURFACE) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_CreateSurface(GBM_FORMAT_%s) failed: %s", gbm_formats[i].name, SDL_GetError());
            KMSDRM_gbm_surface_destroy(windata->gs);
            windata->gs = تہی;
            جاری;  // try the next one.
        }

        /* Current context passing to EGL is now done here. If something fails,
           go back to delayed SDL_EGL_MakeCurrent() call in SwapWindow. */
        egl_context = (EGLContext)SDL_GL_GetCurrentContext();
        نتیجہ = SDL_EGL_MakeCurrent(_this, windata->egl_surface, egl_context);
        اگر (!نتیجہ) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: SDL_EGL_MakeCurrent with GBM_FORMAT_%s failed: %s", gbm_formats[i].name, SDL_GetError());
            جاری;
        }

        _this->gl_config.red_سائز = gbm_formats[i].r;
        _this->gl_config.green_سائز = gbm_formats[i].g;
        _this->gl_config.blue_سائز = gbm_formats[i].b;
        _this->gl_config.alpha_سائز = gbm_formats[i].a;

        windata->egl_surface_dirty = false;

        نتیجہ = true;

        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, dispdata->منوال.hdisplay, dispdata->منوال.vdisplay);

        توڑو;
    }

    SDL_assert(نتیجہ || (windata->gs == تہی));

    اگر (!نتیجہ) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "KMSDRM: Failed to create surfaces in _any_ format!");
        اگر (!tried_setting_format) {   // make sure there's an error string set.
            SDL_سیٹ_Error("Could not find any supported GBM surface format.");
        }
    }

    واپس نتیجہ;
}

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
ساکن خالی KMSDRM_ReleaseVT(خالی *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    صحیح i;

    برائے (i = 0; i < viddata->عدد_windows; i++) {
        SDL_کھڑکی *کھڑکی = viddata->windows[i];
        اگر (!(کھڑکی->flags & SDL_کھڑکی_VULKAN)) {
            KMSDRM_DestroySurfaces(_this, کھڑکی);
        }
    }
    KMSDRM_drmDropMaster(viddata->drm_fd);
}

ساکن خالی KMSDRM_AcquireVT(خالی *userdata)
{
    SDL_VideoDevice *_this = (SDL_VideoDevice *)userdata;
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    صحیح i;

    KMSDRM_drm_سیٹ_Master(viddata->drm_fd);
    برائے (i = 0; i < viddata->عدد_windows; i++) {
        SDL_کھڑکی *کھڑکی = viddata->windows[i];
        اگر (!(کھڑکی->flags & SDL_کھڑکی_VULKAN)) {
            KMSDRM_CreateSurfaces(_this, کھڑکی);
        }
    }
}
#اگر_ختم // defined SDL_INPUT_LINUXEV

bool KMSDRM_VideoInit(SDL_VideoDevice *_this)
{
    bool نتیجہ = true;

    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "KMSDRM_VideoInit()");

    viddata->video_init = false;
    viddata->gbm_init = false;

    /* Get KMSDRM resources info and store what we need. Getting and storing
       this info isn't a problem for VK compatibility.
       For VK-incompatible initializations we have KMSDRM_GBMInit(), which is
       called on window creation, and only when we know it's not a VK window. */
    اگر (!KMSDRM_InitDisplays(_this)) {
        نتیجہ = SDL_سیٹ_Error("error getting KMSDRM displays information");
    }

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Init();
    SDL_EVDEV_سیٹ_VTSwitch_Callbacks(KMSDRM_ReleaseVT, _this, KMSDRM_AcquireVT, _this);
#وگرنہ_اگر defined(SDL_داخلہ_WSCONS)
    SDL_WSCONS_Init();
#اگر_ختم

    viddata->video_init = true;

    واپس نتیجہ;
}

/* The internal pointers, like dispdata, viddata, windata, etc...
   are freed by SDL internals, so not our job. */
خالی KMSDRM_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;

    KMSDRM_DeinitDisplays(_this);

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_سیٹ_VTSwitch_Callbacks(تہی, تہی, تہی, تہی);
    SDL_EVDEV_Quit();
#وگرنہ_اگر defined(SDL_داخلہ_WSCONS)
    SDL_WSCONS_Quit();
#اگر_ختم

    // Clear out the window list
    SDL_free(viddata->windows);
    viddata->windows = تہی;
    viddata->max_windows = 0;
    viddata->عدد_windows = 0;
    viddata->video_init = false;
}

// Read modes from the connector modes, and store them in display->display_modes.
bool KMSDRM_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;
    drm_منوال_Connector *conn = dispdata->connector.connector;
    SDL_Display_منوال منوال;
    صحیح i;

    برائے (i = 0; i < conn->گنتی_modes; i++) {
        SDL_Display_منوال_ڈیٹا *modedata = SDL_calloc(1, حجم(SDL_Display_منوال_ڈیٹا));

        اگر (modedata) {
            modedata->منوال_اشاریہ = i;
        }

        SDL_zero(منوال);
        منوال.w = conn->modes[i].hdisplay;
        منوال.h = conn->modes[i].vdisplay;
        Calculate_Refresh_شرح(&conn->modes[i], &منوال.refresh_شرح_numerator, &منوال.refresh_شرح_denominator);
        منوال.format = SDL_PIXELFORMAT_ARGB8888;
        منوال.اندرونی_2 = modedata;

        اگر (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
            SDL_free(modedata);
        }
    }
    واپس true;
}

bool KMSDRM_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    /* Set the dispdata->mode to the new mode and leave actual modesetting
       pending to be done on SwapWindow() via drmModeSetCrtc() */

    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;
    SDL_Display_منوال_ڈیٹا *modedata = منوال->اندرونی_2;
    drm_منوال_Connector *conn = dispdata->connector.connector;
    صحیح i;

    // Don't do anything if we are in Vulkan mode.
    اگر (viddata->vulkan_منوال) {
        واپس true;
    }

    اگر (!modedata) {
        واپس SDL_سیٹ_Error("Mode doesn't have an associated index");
    }

    /* Take note of the new mode to be set, and leave the CRTC modeset pending
       so it's done in SwapWindow. */
    dispdata->fullscreen_منوال = conn->modes[modedata->منوال_اشاریہ];

    برائے (i = 0; i < viddata->عدد_windows; i++) {
        KMSDRM_DirtySurfaces(viddata->windows[i]);
    }

    واپس true;
}

خالی KMSDRM_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *windata = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *dispdata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    SDL_Video_ڈیٹا *viddata;
    bool is_vulkan = کھڑکی->flags & SDL_کھڑکی_VULKAN; // Is this a VK window?
    غیرعلامتی صحیح i, j;

    اگر (!windata) {
        واپس;
    }

    // restore vrr state
    KMSDRM_Crtc_سیٹ_Vrr(windata->viddata->drm_fd, dispdata->crtc.crtc->crtc_id, dispdata->saved_vrr);

    viddata = windata->viddata;

    اگر (!is_vulkan && viddata->gbm_init) {

        // Destroy cursor GBM BO of the display of this window.
        KMSDRM_DestroyCursorBO(_this, SDL_Get_Video_Display_For_کھڑکی(کھڑکی));

        // Destroy GBM surface and buffers.
        KMSDRM_DestroySurfaces(_this, کھڑکی);

        /* Unload library and deinit GBM, but only if this is the last window.
           Note that this is the right comparison because num_windows could be 1
           if there is a complete window, or 0 if we got here from SDL_CreateWindow()
           because KMSDRM_CreateWindow() returned an error so the window wasn't
           added to the windows list. */
        اگر (viddata->عدد_windows <= 1) {

            // Unload EGL/GL library and free egl_data.
            اگر (_this->egl_ڈیٹا) {
                SDL_EGL_UnloadLibrary(_this);
                _this->gl_config.driver_loaded = 0;
            }

            // Free display plane, and destroy GBM device.
            KMSDRM_GBMDeinit(_this, dispdata);
        }

    } ورنہ {

        // If we were in Vulkan mode, get out of it.
        اگر (viddata->vulkan_منوال) {
            viddata->vulkan_منوال = false;
        }
    }

    /********************************************/
    // Remove from the internal SDL window list
    /********************************************/

    برائے (i = 0; i < viddata->عدد_windows; i++) {
        اگر (viddata->windows[i] == کھڑکی) {
            viddata->عدد_windows--;

            برائے (j = i; j < viddata->عدد_windows; j++) {
                viddata->windows[j] = viddata->windows[j + 1];
            }

            توڑو;
        }
    }

    /*********************************************************************/
    // Free the window internal. Bye bye, surface and buffer pointers!
    /*********************************************************************/
    SDL_free(کھڑکی->اندرونی_2);
    کھڑکی->اندرونی_2 = تہی;
}

/**********************************************************************/
// We simply IGNORE if it's a fullscreen window, window->flags don't
// reflect it: if it's fullscreen, KMSDRM_SetWindowFullscreen() will
// be called by SDL later, and we can manage it there.
/**********************************************************************/
bool KMSDRM_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *windata = تہی;
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    SDL_Display_ڈیٹا *dispdata = display->اندرونی_2;
    bool is_vulkan = کھڑکی->flags & SDL_کھڑکی_VULKAN; // Is this a VK window?
    bool vulkan_منوال = viddata->vulkan_منوال;            // Do we have any Vulkan windows?
    NativeDisplayType egl_display;
    drm_منوال_منوال_Info *منوال;
    bool نتیجہ = true;

    // Allocate window internal data
    windata = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!windata) {
        واپس false;
    }

    // Setup driver data for this window
    windata->viddata = viddata;
    کھڑکی->اندرونی_2 = windata;

    // Do we want a double buffering scheme to get low video lag?
    windata->double_بفر = false;
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        windata->double_بفر = true;
    }

    اگر (!is_vulkan && !vulkan_منوال) { // NON-Vulkan block.

        /* Maybe you didn't ask for an OPENGL window, but that's what you will get.
           See following comments on why. */
        کھڑکی->flags |= SDL_کھڑکی_OPENGL;

        اگر (!(viddata->gbm_init)) {

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
            اگر (!KMSDRM_GBMInit(_this, dispdata)) {
                واپس SDL_سیٹ_Error("Can't init GBM on window creation.");
            }
        }

        /* Manually load the GL library. KMSDRM_EGL_LoadLibrary() has already
           been called by SDL_CreateWindow() but we don't do anything there,
           our KMSDRM_EGL_LoadLibrary() is a dummy precisely to be able to load it here.
           If we let SDL_CreateWindow() load the lib, it would be loaded
           before we call KMSDRM_GBMInit(), causing all GLES programs to fail. */
        اگر (!_this->egl_ڈیٹا) {
            egl_display = (NativeDisplayType)_this->اندرونی_2->gbm_dev;
            اگر (!SDL_EGL_بھرو_Library(_this, تہی, egl_display)) {
                // Try again with OpenGL ES 2.0
                _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
                _this->gl_config.major_نسخہ = 2;
                _this->gl_config.minor_نسخہ = 0;
                اگر (!SDL_EGL_بھرو_Library(_this, تہی, egl_display)) {
                    واپس SDL_سیٹ_Error("Can't load EGL/GL library on window creation.");
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
        منوال = KMSDRM_Get_Closest_Display_منوال(display, کھڑکی->windowed.w, کھڑکی->windowed.h);

        اگر (منوال) {
            dispdata->fullscreen_منوال = *منوال;
        } ورنہ {
            dispdata->fullscreen_منوال = dispdata->original_منوال;
        }

        /* Create the window surfaces with the size we have just chosen.
           Needs the window driverdata in place. */
        اگر (!KMSDRM_CreateSurfaces(_this, کھڑکی)) {
            واپس false;
        }
    } // NON-Vulkan block ends.

    /* Add window to the internal list of tracked windows. Note, while it may
       seem odd to support multiple fullscreen windows, some apps create an
       extra window as a dummy surface when working with multiple contexts */
    اگر (viddata->عدد_windows >= viddata->max_windows) {
        غیرعلامتی صحیح new_max_windows = viddata->max_windows + 1;
        SDL_کھڑکی **new_windows = (SDL_کھڑکی **)SDL_realloc(viddata->windows,
                                                              new_max_windows * حجم(SDL_کھڑکی *));
        اگر (!new_windows) {
            واپس false;
        }
        viddata->windows = new_windows;
        viddata->max_windows = new_max_windows;

    }

    viddata->windows[viddata->عدد_windows++] = کھڑکی;

    // If we have just created a Vulkan window, establish that we are in Vulkan mode now.
    viddata->vulkan_منوال = is_vulkan;

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_KMSDRM_DEVICE_اشاریہ_نمبر, viddata->devindex);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_KMSDRM_DRM_FD_نمبر, viddata->drm_fd);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_KMSDRM_GBM_DEVICE_اشارہ_گر, viddata->gbm_dev);

    اگر ((کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE) == 0) {
        /* Focus on the newly created window.
           SDL_SetMouseFocus() also takes care of calling KMSDRM_ShowCursor() if necessary. */
        SDL_سیٹ_Mouse_Focus(کھڑکی);
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }

    // Tell the app that the window has moved to top-left.
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(SDL_Get_Display_For_کھڑکی(کھڑکی), &display_bounds);
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, display_bounds.x, display_bounds.y);

    /* Allocated windata will be freed in KMSDRM_DestroyWindow,
       and KMSDRM_DestroyWindow() will be called by SDL_CreateWindow()
       if we return error on any of the previous returns of the function. */
    واپس نتیجہ;
}

خالی KMSDRM_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool KMSDRM_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس SDL_Unsupported();
}
خالی KMSDRM_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    اگر (!viddata->vulkan_منوال) {
        KMSDRM_DirtySurfaces(کھڑکی);
    }
}
SDL_Fullscreen_نتیجہ KMSDRM_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    اگر (!viddata->vulkan_منوال) {
        KMSDRM_DirtySurfaces(کھڑکی);
    }
    واپس SDL_FULLSCREEN_SUCCEEDED;
}
خالی KMSDRM_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی KMSDRM_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی KMSDRM_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی KMSDRM_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی KMSDRM_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی KMSDRM_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool KMSDRM_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    واپس true;  // this just has to exist or SDL_SetWindowFocusable() will refuse to change the window flag.
}

#اگر_ختم // SDL_VIDEO_DRIVER_KMSDRM
