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

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11pen.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
ಸ್ಥಿರ bool xinput2_initialized;
ಸ್ಥಿರ bool xinput2_grabbed_touch_raised;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ xinput2_active_touch_ಎಣಿಕೆ;
#ಯದಿ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ಸ್ಥಿರ bool xinput2_scrolling_supported;
ಸ್ಥಿರ bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ಸ್ಥಿರ bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ xinput2_opcode;

ಸ್ಥಿರ Atom xinput2_rel_x_atom;
ಸ್ಥಿರ Atom xinput2_rel_y_atom;
ಸ್ಥಿರ Atom xinput2_abs_x_atom;
ಸ್ಥಿರ Atom xinput2_abs_y_atom;

// Pointer button remapping table
ಸ್ಥಿರ unsigned ವರ್ಣ *xinput2_pointer_button_map;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ ಸಂಖ್ಯೆ_2;
    ಪೂರ್ಣಾಙ್ಕ scroll_type;
    ದ್ವಿಗುಣ prev_ಮೌಲ್ಯ;
    ದ್ವಿಗುಣ increment;
    bool prev_ಮೌಲ್ಯ_valid;
} SDL_XInput2ScrollInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ scroll_info_ಎಣಿಕೆ;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ ಸಂಖ್ಯೆ_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ದ್ವಿಗುಣ minval[2];
    ದ್ವಿಗುಣ maxval[2];
    ದ್ವಿಗುಣ prev_coords[2];
} SDL_XInput2RelativeDevice;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_XInput2DeviceInfo
{
    ಪೂರ್ಣಾಙ್ಕ device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    ಸಂರಚನಾ SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_device_info;

ಸ್ಥಿರ ಶೂನ್ಯ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ಧ್ರುವ XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ದ್ವಿಗುಣ processed_coords[2] = { 0.0, 0.0 };
    ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯಗಳು_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ಧ್ರುವ bool use_raw_vals = mouse->ಒಳಹರಿವು_Transform || !mouse->enable_relative_system_scale;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        ಯದಿ (!XIMaskIsSet(rawev->valuators.mask, i)) {
            ಅನುವರ್ತ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < 2; ++j) {
            ಯದಿ (rel_dev->ಸಂಖ್ಯೆ_2[j] == i) {
                ಧ್ರುವ ದ್ವಿಗುಣ current_val = use_raw_vals ? rawev->raw_ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i] : rawev->valuators.ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i];

                ಯದಿ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ಅನ್ಯಥಾ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ಯದಿ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                ಭಙ್ಗ;
            }
        }

        ++ಮೌಲ್ಯಗಳು_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ಯದಿ (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ಭಿನ್ನ)processed_coords[0], (ಭಿನ್ನ)processed_coords[1]);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ query_xinput2_version(Display *display, ಪೂರ್ಣಾಙ್ಕ major, ಪೂರ್ಣಾಙ್ಕ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    ಪ್ರತ್ಯಾಗಮ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xinput2_version_atleast(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ version, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantmajor, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ wantminor)
{
    ಪ್ರತ್ಯಾಗಮ version >= ((wantmajor * 1000) + wantminor);
}

ಸ್ಥಿರ SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ಧ್ರುವ SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    ಪ್ರತ್ಯಾಗಮ windowdata ? windowdata->window : ರಿಕ್ತ;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ಧ್ರುವ XIDeviceEvent *xev)
{
    ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯಗಳು_i = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < xev->valuators.mask_len * 8; ++j) {
        ಯದಿ (!XIMaskIsSet(xev->valuators.mask, j)) {
            ಅನುವರ್ತ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ k = 0; k < scroll_dev->scroll_info_ಎಣಿಕೆ; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ಯದಿ (info->ಸಂಖ್ಯೆ_2 == j) {
                ಧ್ರುವ ದ್ವಿಗುಣ current_val = xev->valuators.ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i];
                ಧ್ರುವ ದ್ವಿಗುಣ delta = (info->prev_ಮೌಲ್ಯ - current_val) / info->increment;
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
                ಯದಿ (info->prev_ಮೌಲ್ಯ_valid && SDL_fabs(delta) < (ದ್ವಿಗುಣ)SDL_MAX_SINT32 * 0.95) {
                    ಧ್ರುವ ದ್ವಿಗುಣ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ಧ್ರುವ ದ್ವಿಗುಣ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (ಭಿನ್ನ)-x, (ಭಿನ್ನ)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_ಮೌಲ್ಯ = current_val;
                info->prev_ಮೌಲ್ಯ_valid = true;
            }
        }

        ++ಮೌಲ್ಯಗಳು_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_normalize_touch_coordinates(SDL_Window *window, ದ್ವಿಗುಣ in_x, ದ್ವಿಗುಣ in_y, ಭಿನ್ನ *out_x, ಭಿನ್ನ *out_y)
{
    ಯದಿ (window) {
        ಯದಿ (window->w == 1) {
            *out_x = 0.5f;
        } ಅನ್ಯಥಾ {
            *out_x = (ಭಿನ್ನ)in_x / (window->w - 1);
        }
        ಯದಿ (window->h == 1) {
            *out_y = 0.5f;
        } ಅನ್ಯಥಾ {
            *out_y = (ಭಿನ್ನ)in_y / (window->h - 1);
        }
    } ಅನ್ಯಥಾ {
        // couldn't find the window...
        *out_x = (ಭಿನ್ನ)in_x;
        *out_y = (ಭಿನ್ನ)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    ಪೂರ್ಣಾಙ್ಕ version = 0;
    XIEventMask eventmask;
    unsigned ವರ್ಣ mask[5] = { 0, 0, 0, 0, 0 };
    ಪೂರ್ಣಾಙ್ಕ event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ಯದಿ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        ಪ್ರತ್ಯಾಗಮ false;
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
    ಯದಿ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        ಪ್ರತ್ಯಾಗಮ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    ಯದಿ (!xinput2_version_atleast(version, 2, 0)) {
        ಪ್ರತ್ಯಾಗಮ false; // X server does not support the version we want at all.
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
    eventmask.mask_len = ಪರಿಮಾಣ(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ಯದಿ (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ಯದಿ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_ಬೇರು_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = ಪರಿಮಾಣ(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_ಕೀಲಿ_Press);
    XISetMask(mask, XI_ಕೀಲಿ_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_ಬೇರು_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ false;
#endif
}

ಶೂನ್ಯ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ಪ್ರತಿ (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = ರಿಕ್ತ; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = ರಿಕ್ತ;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = ರಿಕ್ತ;
    xinput2_pointer_button_map_size = 0;
#endif
}

ಶೂನ್ಯ X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ಯದಿ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = ರಿಕ್ತ;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, ರಿಕ್ತ, 0);
        ಯದಿ (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, ಪರಿಮಾಣ(unsigned ವರ್ಣ));
            ಯದಿ (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } ಅನ್ಯಥಾ {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_remove_device_info(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ device_id)
{
    ಪ್ರತಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ರಿಕ್ತ; devinfo; devinfo = devinfo->next) {
        ಯದಿ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ರಿಕ್ತ));
            ಯದಿ (!prev) {
                xinput2_device_info = devinfo->next;
            } ಅನ್ಯಥಾ {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            ಪ್ರತ್ಯಾಗಮ;
        }
        prev = devinfo;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ xinput2_reset_device_valuators(ಶೂನ್ಯ)
{
    ಪ್ರತಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < devinfo->scroll.scroll_info_ಎಣಿಕೆ; ++i) {
            devinfo->scroll.scroll_info[i].prev_ಮೌಲ್ಯ_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_classes)
{
    ಯದಿ (!devinfo) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    ಪೂರ್ಣಾಙ್ಕ rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    ಪೂರ್ಣಾಙ್ಕ allocated_scroll_info_ಎಣಿಕೆ = devinfo->scroll.scroll_info_ಎಣಿಕೆ;
    devinfo->scroll.scroll_info_ಎಣಿಕೆ = 0;
#endif

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_classes; ++i) {
        ಯದಿ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ಧ್ರುವ XIValuatorClassInfo *v = (ಧ್ರುವ XIValuatorClassInfo *)classes[i];
            ಯದಿ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.ಸಂಖ್ಯೆ_2[0] = v->ಸಂಖ್ಯೆ_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ಯದಿ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ಅನ್ಯಥಾ ಯದಿ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ಅನ್ಯಥಾ ಯದಿ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.ಸಂಖ್ಯೆ_2[1] = v->ಸಂಖ್ಯೆ_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ಯದಿ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ಅನ್ಯಥಾ ಯದಿ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ಅನ್ಯಥಾ ಯದಿ (classes[i]->type == XIScrollClass) {
            ಧ್ರುವ XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ಯದಿ (devinfo->scroll.scroll_info_ಎಣಿಕೆ == allocated_scroll_info_ಎಣಿಕೆ) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_ಎಣಿಕೆ + 2) * ಪರಿಮಾಣ(SDL_XInput2ScrollInfo));
                ಯದಿ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_ಎಣಿಕೆ = 0;
                    devinfo->scroll.scroll_info_ಎಣಿಕೆ = 0;
                    ಅನುವರ್ತ;
                }

                allocated_scroll_info_ಎಣಿಕೆ += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_ಎಣಿಕೆ];
            ++devinfo->scroll.scroll_info_ಎಣಿಕೆ;

            SDL_zerop(scroll_info);
            scroll_info->ಸಂಖ್ಯೆ_2 = s->ಸಂಖ್ಯೆ_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ device_id)
{
    ಪ್ರತಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ರಿಕ್ತ; devinfo; devinfo = devinfo->next) {
        ಯದಿ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ರಿಕ್ತ));
            ಯದಿ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            ಪ್ರತ್ಯಾಗಮ devinfo;
        }
        prev = devinfo;
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ಯದಿ (devinfo) {
        ಪ್ರತ್ಯಾಗಮ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_XInput2DeviceInfo));
    ಯದಿ (!devinfo) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪೂರ್ಣಾಙ್ಕ i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ಯದಿ (!xidevinfo) {
        SDL_free(devinfo);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->ಅಂಕೆ_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    ಪ್ರತ್ಯಾಗಮ devinfo;
}
#endif

ಶೂನ್ಯ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    ಯದಿ (cookie->extension != xinput2_opcode) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ವಿಕಲ್ಪ (cookie->evtype) {
    ಪಕ್ಷ XI_HierarchyChanged:
    {
        ಧ್ರುವ XIHierarchyEvent *hierev = (ಧ್ರುವ XIHierarchyEvent *)cookie->data;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < hierev->ಅಂಕೆ_info; ++i) {
            // pen stuff...
            ಯದಿ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ಅನ್ಯಥಾ ಯದಿ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ಯದಿ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } ಭಙ್ಗ;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    ಪಕ್ಷ XI_DeviceChanged:
    {
        ಧ್ರುವ XIDeviceChangedEvent *dcev = (ಧ್ರುವ XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ಯದಿ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->ಅಂಕೆ_classes);
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_PropertyEvent:
    {
        ಧ್ರುವ XIPropertyEvent *proev = (ಧ್ರುವ XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        ಯದಿ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : ರಿಕ್ತ, proev->deviceid);
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_RawMotion:
    {
        ಧ್ರುವ XIRawEvent *rawev = (ಧ್ರುವ XIRawEvent *)cookie->data;
        ಧ್ರುವ bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != ರಿಕ್ತ;

        videodata->global_mouse_changed = true;
        ಯದಿ (is_pen) {
            ಭಙ್ಗ; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ಯದಿ (!devinfo) {
            ಭಙ್ಗ; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_ಕೀಲಿ_Press:
    ಪಕ್ಷ XI_ಕೀಲಿ_Release:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        ಯದಿ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ಭಙ್ಗ;
        }

        ಯದಿ (cookie->evtype == XI_ಕೀಲಿ_Press) {
            xevent.type = ಕೀಲಿ_Press;
        } ಅನ್ಯಥಾ {
            xevent.type = ಕೀಲಿ_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.ಬೇರು = xev->ಬೇರು;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (ಪೂರ್ಣಾಙ್ಕ)xev->event_x;
        xevent.xkey.y = (ಪೂರ್ಣಾಙ್ಕ)xev->event_y;
        xevent.xkey.x_ಬೇರು = (ಪೂರ್ಣಾಙ್ಕ)xev->ಬೇರು_x;
        xevent.xkey.y_ಬೇರು = (ಪೂರ್ಣಾಙ್ಕ)xev->ಬೇರು_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_ಕೀಲಿ_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ಅನ್ಯಥಾ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_ಕೀಲಿ_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_RawButtonPress:
    ಪಕ್ಷ XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ಪಕ್ಷ XI_RawTouchBegin:
    ಪಕ್ಷ XI_RawTouchUpdate:
    ಪಕ್ಷ XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_ButtonPress:
    ಪಕ್ಷ XI_ButtonRelease:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        ಪೂರ್ಣಾಙ್ಕ button = xev->detail;
        ಧ್ರುವ bool down = (cookie->evtype == XI_ButtonPress);
#ಯದಿ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ಅನ್ಯಥಾ
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        ಯದಿ (pen) {
            ಯದಿ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ಭಙ್ಗ;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            ಯದಿ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } ಅನ್ಯಥಾ {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } ಅನ್ಯಥಾ ಯದಿ (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            ಪೂರ್ಣಾಙ್ಕ x_ticks = 0, y_ticks = 0;

            ಯದಿ (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ಯದಿ (SDL_GetMouseFocus() != windowdata->window) {
                    ಭಙ್ಗ;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ಯದಿ (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ಯದಿ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ಭಙ್ಗ;
            }

            ಯದಿ (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ಭಿನ್ನ)xev->event_x, (ಭಿನ್ನ)xev->event_y, xev->time, xev->serial);
            } ಅನ್ಯಥಾ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ಭಙ್ಗ;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    ಪಕ್ಷ XI_Motion:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
#ಯದಿ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ಅನ್ಯಥಾ
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        ಯದಿ (pen) {
            ಯದಿ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ಭಙ್ಗ;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (ಭಿನ್ನ) xev->event_x, (ಭಿನ್ನ) xev->event_y);

            ಭಿನ್ನ axes[SDL_PEN_AXIS_ಎಣಿಕೆ];
            X11_PenAxesFromValuators(pen, xev->valuators.ಮೌಲ್ಯಗಳು, xev->valuators.mask, xev->valuators.mask_len, axes);

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_arraysize(axes); i++) {
                ಯದಿ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ಅನ್ಯಥಾ ಯದಿ (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ಯದಿ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ಯದಿ (devinfo) {
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
            ಯದಿ (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_ಎಣಿಕೆ && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ಯದಿ (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (ಭಿನ್ನ)xev->event_x, (ಭಿನ್ನ)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (ಭಿನ್ನ)xev->event_x, (ಭಿನ್ನ)xev->event_y);
                }
            }
        }
    } ಭಙ್ಗ;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ಪಕ್ಷ XI_TouchBegin:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
        ಭಿನ್ನ x, y;
        ++xinput2_active_touch_ಎಣಿಕೆ;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_TouchEnd:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
        ಭಿನ್ನ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        ಯದಿ (!--xinput2_active_touch_ಎಣಿಕೆ && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } ಭಙ್ಗ;

    ಪಕ್ಷ XI_TouchUpdate:
    {
        ಧ್ರುವ XIDeviceEvent *xev = (ಧ್ರುವ XIDeviceEvent *)cookie->data;
        ಭಿನ್ನ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } ಭಙ್ಗ;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ಪಕ್ಷ XI_GesturePinchBegin:
    ಪಕ್ಷ XI_GesturePinchUpdate:
    ಪಕ್ಷ XI_GesturePinchEnd:
    {
        ಧ್ರುವ XIGesturePinchEvent *xev = (ಧ್ರುವ XIGesturePinchEvent *)cookie->data;
        ಭಿನ್ನ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        ಯದಿ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ಅನ್ಯಥಾ ಯದಿ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (ಭಿನ್ನ)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ಅನ್ಯಥಾ {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ಭಙ್ಗ;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ಶೂನ್ಯ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_ಎಣಿಕೆ = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ಧ್ರುವ bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_ಎಣಿಕೆ || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    ಪ್ರತ್ಯಾಗಮ ret;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ಶೂನ್ಯ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#ಯದಿ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned ವರ್ಣ mask[5] = { 0, 0, 0, 0, 0 };

    ಯದಿ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = ಪರಿಮಾಣ(mask);
    eventmask.mask = mask;

    ಯದಿ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    ಯದಿ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ಯದಿ (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(ಶೂನ್ಯ)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ಪ್ರತ್ಯಾಗಮ xinput2_initialized;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ಧ್ರುವ SDL_VideoData *data = _this->internal;

    ಯದಿ (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned ವರ್ಣ mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = ಪರಿಮಾಣ(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_ಕೀಲಿ_Press);
        XISetMask(mask, XI_ಕೀಲಿ_Release);
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

        ಯದಿ (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    ಯದಿ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned ವರ್ಣ mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    ಯದಿ (!xinput2_multitouch_supported) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = ಪರಿಮಾಣ(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

ಶೂನ್ಯ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    ಯದಿ (!xinput2_multitouch_supported) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

ಸ್ಥಿರ ಶೂನ್ಯ AddDeviceID(Uint32 deviceID, Uint32 **list, ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಪೂರ್ಣಾಙ್ಕ new_ಎಣಿಕೆ = (*ಎಣಿಕೆ + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ಎಣಿಕೆ * ಪರಿಮಾಣ(*new_list));
    ಯದಿ (!new_list) {
        // Oh well, we'll drop this one
        ಪ್ರತ್ಯಾಗಮ;
    }
    new_list[new_ಎಣಿಕೆ - 1] = deviceID;

    *ಎಣಿಕೆ = new_ಎಣಿಕೆ;
    *list = new_list;
}

ಸ್ಥಿರ bool HasDeviceID(Uint32 deviceID, ಧ್ರುವ Uint32 *list, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಎಣಿಕೆ; ++i) {
        ಯದಿ (deviceID == list[i]) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ಸ್ಥಿರ ಶೂನ್ಯ AddDeviceID64(Uint64 deviceID, Uint64 **list, ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಪೂರ್ಣಾಙ್ಕ new_ಎಣಿಕೆ = (*ಎಣಿಕೆ + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_ಎಣಿಕೆ * ಪರಿಮಾಣ(*new_list));
    ಯದಿ (!new_list) {
        // Oh well, we'll drop this one
        ಪ್ರತ್ಯಾಗಮ;
    }
    new_list[new_ಎಣಿಕೆ - 1] = deviceID;

    *ಎಣಿಕೆ = new_ಎಣಿಕೆ;
    *list = new_list;
}
#endif

ಸ್ಥಿರ bool HasDeviceID64(Uint64 deviceID, ಧ್ರುವ Uint64 *list, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಎಣಿಕೆ; ++i) {
        ಯದಿ (deviceID == list[i]) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

ಶೂನ್ಯ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    ಪೂರ್ಣಾಙ್ಕ ndevices;
    ಪೂರ್ಣಾಙ್ಕ old_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *old_keyboards = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ new_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *new_keyboards = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ old_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *old_mice = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ new_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *new_mice = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ old_touch_ಎಣಿಕೆ = 0;
    Uint64 *old_touch_devices = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ new_touch_ಎಣಿಕೆ = 0;
    Uint64 *new_touch_devices = ರಿಕ್ತ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ಎಣಿಕೆ);
    old_mice = SDL_GetMice(&old_mouse_ಎಣಿಕೆ);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_ಎಣಿಕೆ);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        ವಿಕಲ್ಪ (dev->use) {
        ಪಕ್ಷ XIMasterKeyboard:
        ಪಕ್ಷ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_ಎಣಿಕೆ);
                ಯದಿ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ಎಣಿಕೆ)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        ಪಕ್ಷ XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_ಎಣಿಕೆ);
                ಯದಿ (!HasDeviceID(mouseID, old_mice, old_mouse_ಎಣಿಕೆ)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ಯದಿ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->ಅಂಕೆ_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < dev->ಅಂಕೆ_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ಯದಿ (class->type != XITouchClass) {
                ಅನುವರ್ತ;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_ಎಣಿಕೆ);
            ಯದಿ (!HasDeviceID64(touchID, old_touch_devices, old_touch_ಎಣಿಕೆ)) {
                ಯದಿ (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } ಅನ್ಯಥಾ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = old_keyboard_ಎಣಿಕೆ; i--;) {
        ಯದಿ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ಎಣಿಕೆ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = old_mouse_ಎಣಿಕೆ; i--;) {
        ಯದಿ (!HasDeviceID(old_mice[i], new_mice, new_mouse_ಎಣಿಕೆ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = old_touch_ಎಣಿಕೆ; i--;) {
        ಯದಿ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_ಎಣಿಕೆ)) {
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
