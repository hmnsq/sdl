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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11pen.h"
#include "SDL_x11video.h"
#include "SDL_x11xinput2.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_pen_c.h"
#include "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
static bool xinput2_initialized;
static bool xinput2_grabbed_touch_raised;
static puur_naa_nka xinput2_active_touch_count;
#ᱡᱩᱫᱤ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
static bool xinput2_scrolling_supported;
static bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
static bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
static puur_naa_nka xinput2_opcode;

static Atom xinput2_rel_x_atom;
static Atom xinput2_rel_y_atom;
static Atom xinput2_abs_x_atom;
static Atom xinput2_abs_y_atom;

// Pointer button remapping table
static unsigned var_na *xinput2_pointer_button_map;
static puur_naa_nka xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
typedef sa_nracanaa
{
    puur_naa_nka number;
    puur_naa_nka scroll_type;
    dviguu_na prev_value;
    dviguu_na increment;
    bool prev_value_valid;
} SDL_XInput2ScrollInfo;

typedef sa_nracanaa
{
    puur_naa_nka scroll_info_count;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

typedef sa_nracanaa
{
    puur_naa_nka number[2];
    bool relative[2];
    bool prev_coord_valid[2];
    dviguu_na minval[2];
    dviguu_na maxval[2];
    dviguu_na prev_coords[2];
} SDL_XInput2RelativeDevice;

typedef sa_nracanaa SDL_XInput2DeviceInfo
{
    puur_naa_nka device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    sa_nracanaa SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

static SDL_XInput2DeviceInfo *xinput2_device_info;

static void parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, const XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    dviguu_na processed_coords[2] = { 0.0, 0.0 };
    puur_naa_nka values_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    const bool use_raw_vals = mouse->InputTransform || !mouse->enable_relative_system_scale;

    for (puur_naa_nka i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        ᱡᱩᱫᱤ (!XIMaskIsSet(rawev->valuators.mask, i)) {
            continue;
        }

        for (puur_naa_nka j = 0; j < 2; ++j) {
            ᱡᱩᱫᱤ (rel_dev->number[j] == i) {
                const dviguu_na current_val = use_raw_vals ? rawev->raw_values[values_i] : rawev->valuators.values[values_i];

                ᱡᱩᱫᱤ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ᱵᱟᱝ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ᱡᱩᱫᱤ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                bha_nga;
            }
        }

        ++values_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ᱡᱩᱫᱤ (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (float)processed_coords[0], (float)processed_coords[1]);
    }
}

static puur_naa_nka query_xinput2_version(Display *display, puur_naa_nka major, puur_naa_nka minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    ᱨᱩᱣᱟᱹᱲ (major * 1000) + minor;
}

static bool xinput2_version_atleast(const puur_naa_nka version, const puur_naa_nka wantmajor, const puur_naa_nka wantminor)
{
    ᱨᱩᱣᱟᱹᱲ version >= ((wantmajor * 1000) + wantminor);
}

static SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    const SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    ᱨᱩᱣᱟᱹᱲ windowdata ? windowdata->window : NULL;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
static void xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, const XIDeviceEvent *xev)
{
    puur_naa_nka values_i = 0;
    for (puur_naa_nka j = 0; j < xev->valuators.mask_len * 8; ++j) {
        ᱡᱩᱫᱤ (!XIMaskIsSet(xev->valuators.mask, j)) {
            continue;
        }

        for (puur_naa_nka k = 0; k < scroll_dev->scroll_info_count; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ᱡᱩᱫᱤ (info->number == j) {
                const dviguu_na current_val = xev->valuators.values[values_i];
                const dviguu_na delta = (info->prev_value - current_val) / info->increment;
                /* Ignore very large jumps that can happen as a result of overflowing
                 * the maximum range, as the driver will reset the position to zero
                 * at "something that's close to 2^32".
                 *
                 * The first scroll event is meaningless by itself and must be discarded,
                 * as it is only useful for establishing a baseline for future deltas.
                 * This is a known deficiency of the XInput2 scroll protocol, and,
                 * unfortunately, there is nothing we can do about it.
                 *
                 * http://who-t.blogspot.com/2012/06/xi-21-protocol-design-issues.html
                 */
                ᱡᱩᱫᱤ (info->prev_value_valid && SDL_fabs(delta) < (dviguu_na)SDL_MAX_SINT32 * 0.95) {
                    const dviguu_na x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    const dviguu_na y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (float)-x, (float)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_value = current_val;
                info->prev_value_valid = true;
            }
        }

        ++values_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
static void xinput2_normalize_touch_coordinates(SDL_Window *window, dviguu_na in_x, dviguu_na in_y, float *out_x, float *out_y)
{
    ᱡᱩᱫᱤ (window) {
        ᱡᱩᱫᱤ (window->w == 1) {
            *out_x = 0.5f;
        } ᱵᱟᱝ {
            *out_x = (float)in_x / (window->w - 1);
        }
        ᱡᱩᱫᱤ (window->h == 1) {
            *out_y = 0.5f;
        } ᱵᱟᱝ {
            *out_y = (float)in_y / (window->h - 1);
        }
    } ᱵᱟᱝ {
        // couldn't find the window...
        *out_x = (float)in_x;
        *out_y = (float)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    puur_naa_nka version = 0;
    XIEventMask eventmask;
    unsigned var_na mask[5] = { 0, 0, 0, 0, 0 };
    puur_naa_nka event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ᱡᱩᱫᱤ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        ᱨᱩᱣᱟᱹᱲ false;
    }

    /*
     * Initialize XInput 2
     * According to http://who-t.blogspot.com/2009/05/xi2-recipes-part-1.html its better
     * to inform Xserver what version of Xinput we support.The server will store the version we support.
     * "As XI2 progresses it becomes important that you use this call as the server may treat the client
     * differently depending on the supported version".
     *
     * FIXME:event and err are not needed but if not passed X11_XQueryExtension returns SegmentationFault
     */
    ᱡᱩᱫᱤ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        ᱨᱩᱣᱟᱹᱲ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    ᱡᱩᱫᱤ (!xinput2_version_atleast(version, 2, 0)) {
        ᱨᱩᱣᱟᱹᱲ false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_version_atleast(version, 2, 1);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_version_atleast(version, 2, 2);
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_version_atleast(version, 2, 4);
#endif

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(data->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(data->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(data->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(data->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = parimaa_na(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ᱡᱩᱫᱤ (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ᱡᱩᱫᱤ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, DefaultRootWindow(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = parimaa_na(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_KeyPress);
    XISetMask(mask, XI_KeyRelease);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, DefaultRootWindow(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    ᱨᱩᱣᱟᱹᱲ true;
#ᱵᱟᱝ
    ᱨᱩᱣᱟᱹᱲ false;
#endif
}

void X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    for (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = NULL; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = NULL;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = NULL;
    xinput2_pointer_button_map_size = 0;
#endif
}

void X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ᱡᱩᱫᱤ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = NULL;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, NULL, 0);
        ᱡᱩᱫᱤ (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, parimaa_na(unsigned var_na));
            ᱡᱩᱫᱤ (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } ᱵᱟᱝ {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
static void xinput2_remove_device_info(const puur_naa_nka device_id)
{
    for (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = NULL; devinfo; devinfo = devinfo->next) {
        ᱡᱩᱫᱤ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == NULL));
            ᱡᱩᱫᱤ (!prev) {
                xinput2_device_info = devinfo->next;
            } ᱵᱟᱝ {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            ᱨᱩᱣᱟᱹᱲ;
        }
        prev = devinfo;
    }
}

static void xinput2_reset_device_valuators(void)
{
    for (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        for (puur_naa_nka i = 0; i < devinfo->scroll.scroll_info_count; ++i) {
            devinfo->scroll.scroll_info[i].prev_value_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

static void xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, puur_naa_nka num_classes)
{
    ᱡᱩᱫᱤ (!devinfo) {
        ᱨᱩᱣᱟᱹᱲ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    puur_naa_nka rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    puur_naa_nka allocated_scroll_info_count = devinfo->scroll.scroll_info_count;
    devinfo->scroll.scroll_info_count = 0;
#endif

    for (puur_naa_nka i = 0; i < num_classes; ++i) {
        ᱡᱩᱫᱤ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            const XIValuatorClassInfo *v = (const XIValuatorClassInfo *)classes[i];
            ᱡᱩᱫᱤ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.number[0] = v->number;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ᱡᱩᱫᱤ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ᱵᱟᱝ ᱡᱩᱫᱤ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ᱵᱟᱝ ᱡᱩᱫᱤ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.number[1] = v->number;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ᱡᱩᱫᱤ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ᱵᱟᱝ ᱡᱩᱫᱤ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ᱵᱟᱝ ᱡᱩᱫᱤ (classes[i]->type == XIScrollClass) {
            const XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ᱡᱩᱫᱤ (devinfo->scroll.scroll_info_count == allocated_scroll_info_count) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_count + 2) * parimaa_na(SDL_XInput2ScrollInfo));
                ᱡᱩᱫᱤ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_count = 0;
                    devinfo->scroll.scroll_info_count = 0;
                    continue;
                }

                allocated_scroll_info_count += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_count];
            ++devinfo->scroll.scroll_info_count;

            SDL_zerop(scroll_info);
            scroll_info->number = s->number;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

static SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(const puur_naa_nka device_id)
{
    for (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = NULL; devinfo; devinfo = devinfo->next) {
        ᱡᱩᱫᱤ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == NULL));
            ᱡᱩᱫᱤ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            ᱨᱩᱣᱟᱹᱲ devinfo;
        }
        prev = devinfo;
    }

    ᱨᱩᱣᱟᱹᱲ NULL;
}

static SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, const puur_naa_nka device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ᱡᱩᱫᱤ (devinfo) {
        ᱨᱩᱣᱟᱹᱲ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, parimaa_na(SDL_XInput2DeviceInfo));
    ᱡᱩᱫᱤ (!devinfo) {
        ᱨᱩᱣᱟᱹᱲ NULL;
    }

    puur_naa_nka i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ᱡᱩᱫᱤ (!xidevinfo) {
        SDL_free(devinfo);
        ᱨᱩᱣᱟᱹᱲ NULL;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->num_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    ᱨᱩᱣᱟᱹᱲ devinfo;
}
#endif

void X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    ᱡᱩᱫᱤ (cookie->extension != xinput2_opcode) {
        ᱨᱩᱣᱟᱹᱲ;
    }

    switch (cookie->evtype) {
    pak_sa XI_HierarchyChanged:
    {
        const XIHierarchyEvent *hierev = (const XIHierarchyEvent *)cookie->data;
        for (puur_naa_nka i = 0; i < hierev->num_info; ++i) {
            // pen stuff...
            ᱡᱩᱫᱤ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ᱵᱟᱝ ᱡᱩᱫᱤ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ᱡᱩᱫᱤ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } bha_nga;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    pak_sa XI_DeviceChanged:
    {
        const XIDeviceChangedEvent *dcev = (const XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ᱡᱩᱫᱤ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->num_classes);
        }
    } bha_nga;

    pak_sa XI_PropertyEvent:
    {
        const XIPropertyEvent *proev = (const XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        ᱡᱩᱫᱤ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : NULL, proev->deviceid);
        }
    } bha_nga;

    pak_sa XI_RawMotion:
    {
        const XIRawEvent *rawev = (const XIRawEvent *)cookie->data;
        const bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != NULL;

        videodata->global_mouse_changed = true;
        ᱡᱩᱫᱤ (is_pen) {
            bha_nga; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ᱡᱩᱫᱤ (!devinfo) {
            bha_nga; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } bha_nga;

    pak_sa XI_KeyPress:
    pak_sa XI_KeyRelease:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        ᱡᱩᱫᱤ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            bha_nga;
        }

        ᱡᱩᱫᱤ (cookie->evtype == XI_KeyPress) {
            xevent.type = KeyPress;
        } ᱵᱟᱝ {
            xevent.type = KeyRelease;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.root = xev->root;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (puur_naa_nka)xev->event_x;
        xevent.xkey.y = (puur_naa_nka)xev->event_y;
        xevent.xkey.x_root = (puur_naa_nka)xev->root_x;
        xevent.xkey.y_root = (puur_naa_nka)xev->root_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_HandleKeyEvent(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ᱵᱟᱝ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_key_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } bha_nga;

    pak_sa XI_RawButtonPress:
    pak_sa XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    pak_sa XI_RawTouchBegin:
    pak_sa XI_RawTouchUpdate:
    pak_sa XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } bha_nga;

    pak_sa XI_ButtonPress:
    pak_sa XI_ButtonRelease:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        puur_naa_nka button = xev->detail;
        const bool down = (cookie->evtype == XI_ButtonPress);
#ᱡᱩᱫᱤ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ᱵᱟᱝ
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        ᱡᱩᱫᱤ (pen) {
            ᱡᱩᱫᱤ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                bha_nga;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            ᱡᱩᱫᱤ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } ᱵᱟᱝ {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } ᱵᱟᱝ ᱡᱩᱫᱤ (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            puur_naa_nka x_ticks = 0, y_ticks = 0;

            ᱡᱩᱫᱤ (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ᱡᱩᱫᱤ (SDL_GetMouseFocus() != windowdata->window) {
                    bha_nga;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ᱡᱩᱫᱤ (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ᱡᱩᱫᱤ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                bha_nga;
            }

            ᱡᱩᱫᱤ (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (float)xev->event_x, (float)xev->event_y, xev->time, xev->serial);
            } ᱵᱟᱝ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } bha_nga;

    pak_sa XI_Enter:
    {
        xinput2_reset_device_valuators();
    } bha_nga;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    pak_sa XI_Motion:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
#ᱡᱩᱫᱤ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ᱵᱟᱝ
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        ᱡᱩᱫᱤ (pen) {
            ᱡᱩᱫᱤ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                bha_nga;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (float) xev->event_x, (float) xev->event_y);

            float axes[SDL_PEN_AXIS_COUNT];
            X11_PenAxesFromValuators(pen, xev->valuators.values, xev->valuators.mask, xev->valuators.mask_len, axes);

            for (puur_naa_nka i = 0; i < SDL_arraysize(axes); i++) {
                ᱡᱩᱫᱤ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ᱵᱟᱝ ᱡᱩᱫᱤ (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ᱡᱩᱫᱤ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ᱡᱩᱫᱤ (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#endif

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            ᱡᱩᱫᱤ (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_count && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ᱡᱩᱫᱤ (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (float)xev->event_x, (float)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (float)xev->event_x, (float)xev->event_y);
                }
            }
        }
    } bha_nga;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    pak_sa XI_TouchBegin:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
        float x, y;
        ++xinput2_active_touch_count;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } bha_nga;

    pak_sa XI_TouchEnd:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
        float x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        ᱡᱩᱫᱤ (!--xinput2_active_touch_count && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } bha_nga;

    pak_sa XI_TouchUpdate:
    {
        const XIDeviceEvent *xev = (const XIDeviceEvent *)cookie->data;
        float x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } bha_nga;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    pak_sa XI_GesturePinchBegin:
    pak_sa XI_GesturePinchUpdate:
    pak_sa XI_GesturePinchEnd:
    {
        const XIGesturePinchEvent *xev = (const XIGesturePinchEvent *)cookie->data;
        float x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        ᱡᱩᱫᱤ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ᱵᱟᱝ ᱡᱩᱫᱤ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (float)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ᱵᱟᱝ {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } bha_nga;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

void X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_count = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    const bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_count || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    ᱨᱩᱣᱟᱹᱲ ret;
#ᱵᱟᱝ
    ᱨᱩᱣᱟᱹᱲ false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

void X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#ᱡᱩᱫᱤ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned var_na mask[5] = { 0, 0, 0, 0, 0 };

    ᱡᱩᱫᱤ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        ᱨᱩᱣᱟᱹᱲ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = parimaa_na(mask);
    eventmask.mask = mask;

    ᱡᱩᱫᱤ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    ᱡᱩᱫᱤ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ᱡᱩᱫᱤ (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(void)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ᱨᱩᱣᱟᱹᱲ xinput2_initialized;
#ᱵᱟᱝ
    ᱨᱩᱣᱟᱹᱲ false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    const SDL_VideoData *data = _this->internal;

    ᱡᱩᱫᱤ (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned var_na mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = parimaa_na(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_KeyPress);
        XISetMask(mask, XI_KeyRelease);
        windowdata->xinput2_keyboard_enabled = true;
#endif

        XISetMask(mask, XI_ButtonPress);
        XISetMask(mask, XI_ButtonRelease);
        XISetMask(mask, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISetMask(mask, XI_Enter);
        XISetMask(mask, XI_Leave);

        // Hotplugging:
        XISetMask(mask, XI_DeviceChanged);
        XISetMask(mask, XI_HierarchyChanged);
        XISetMask(mask, XI_PropertyEvent); // E.g., when swapping tablet pens

        ᱡᱩᱫᱤ (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    ᱡᱩᱫᱤ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        ᱨᱩᱣᱟᱹᱲ true;
    }
    ᱨᱩᱣᱟᱹᱲ false;
}

void X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned var_na mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    ᱡᱩᱫᱤ (!xinput2_multitouch_supported) {
        ᱨᱩᱣᱟᱹᱲ;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = parimaa_na(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

void X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    ᱡᱩᱫᱤ (!xinput2_multitouch_supported) {
        ᱨᱩᱣᱟᱹᱲ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

static void AddDeviceID(Uint32 deviceID, Uint32 **list, puur_naa_nka *count)
{
    puur_naa_nka new_count = (*count + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_count * parimaa_na(*new_list));
    ᱡᱩᱫᱤ (!new_list) {
        // Oh well, we'll drop this one
        ᱨᱩᱣᱟᱹᱲ;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}

static bool HasDeviceID(Uint32 deviceID, const Uint32 *list, puur_naa_nka count)
{
    for (puur_naa_nka i = 0; i < count; ++i) {
        ᱡᱩᱫᱤ (deviceID == list[i]) {
            ᱨᱩᱣᱟᱹᱲ true;
        }
    }
    ᱨᱩᱣᱟᱹᱲ false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
static void AddDeviceID64(Uint64 deviceID, Uint64 **list, puur_naa_nka *count)
{
    puur_naa_nka new_count = (*count + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_count * parimaa_na(*new_list));
    ᱡᱩᱫᱤ (!new_list) {
        // Oh well, we'll drop this one
        ᱨᱩᱣᱟᱹᱲ;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}
#endif

static bool HasDeviceID64(Uint64 deviceID, const Uint64 *list, puur_naa_nka count)
{
    for (puur_naa_nka i = 0; i < count; ++i) {
        ᱡᱩᱫᱤ (deviceID == list[i]) {
            ᱨᱩᱣᱟᱹᱲ true;
        }
    }
    ᱨᱩᱣᱟᱹᱲ false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

void X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    puur_naa_nka ndevices;
    puur_naa_nka old_keyboard_count = 0;
    SDL_KeyboardID *old_keyboards = NULL;
    puur_naa_nka new_keyboard_count = 0;
    SDL_KeyboardID *new_keyboards = NULL;
    puur_naa_nka old_mouse_count = 0;
    SDL_MouseID *old_mice = NULL;
    puur_naa_nka new_mouse_count = 0;
    SDL_MouseID *new_mice = NULL;
    puur_naa_nka old_touch_count = 0;
    Uint64 *old_touch_devices = NULL;
    puur_naa_nka new_touch_count = 0;
    Uint64 *new_touch_devices = NULL;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_count);
    old_mice = SDL_GetMice(&old_mouse_count);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_count);

    for (puur_naa_nka i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        switch (dev->use) {
        pak_sa XIMasterKeyboard:
        pak_sa XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_count);
                ᱡᱩᱫᱤ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_count)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            bha_nga;
        pak_sa XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        pak_sa XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_count);
                ᱡᱩᱫᱤ (!HasDeviceID(mouseID, old_mice, old_mouse_count)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            bha_nga;
        default:
            bha_nga;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ᱡᱩᱫᱤ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->num_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        for (puur_naa_nka j = 0; j < dev->num_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ᱡᱩᱫᱤ (class->type != XITouchClass) {
                continue;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_count);
            ᱡᱩᱫᱤ (!HasDeviceID64(touchID, old_touch_devices, old_touch_count)) {
                ᱡᱩᱫᱤ (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } ᱵᱟᱝ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    for (puur_naa_nka i = old_keyboard_count; i--;) {
        ᱡᱩᱫᱤ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_count)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    for (puur_naa_nka i = old_mouse_count; i--;) {
        ᱡᱩᱫᱤ (!HasDeviceID(old_mice[i], new_mice, new_mouse_count)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    for (puur_naa_nka i = old_touch_count; i--;) {
        ᱡᱩᱫᱤ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_count)) {
            SDL_DelTouch(old_touch_devices[i]);
        }
    }

    SDL_free(old_keyboards);
    SDL_free(new_keyboards);
    SDL_free(old_mice);
    SDL_free(new_mice);
    SDL_free(old_touch_devices);
    SDL_free(new_touch_devices);

    X11_XIFreeDeviceInfo(info);

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#endif // SDL_VIDEO_DRIVER_X11
