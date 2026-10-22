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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "SDL_x11pen.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xinput2.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_pen_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
ସ୍ଥିର bool xinput2_initialized;
ସ୍ଥିର bool xinput2_grabbed_touch_raised;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା xinput2_active_touch_ଗଣନା;
#ଯଦି defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ସ୍ଥିର bool xinput2_scrolling_supported;
ସ୍ଥିର bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ସ୍ଥିର bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା xinput2_opcode;

ସ୍ଥିର Atom xinput2_rel_x_atom;
ସ୍ଥିର Atom xinput2_rel_y_atom;
ସ୍ଥିର Atom xinput2_abs_x_atom;
ସ୍ଥିର Atom xinput2_abs_y_atom;

// Pointer button remapping table
ସ୍ଥିର unsigned ଅକ୍ଷର *xinput2_pointer_button_map;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସଂଖ୍ୟା_2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା scroll_type;
    ଦ୍ୱିଗୁଣ prev_ମୂଲ୍ୟ;
    ଦ୍ୱିଗୁଣ increment;
    bool prev_ମୂଲ୍ୟ_valid;
} SDL_XInput2ScrollInfo;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା scroll_info_ଗଣନା;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସଂଖ୍ୟା_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ଦ୍ୱିଗୁଣ minval[2];
    ଦ୍ୱିଗୁଣ maxval[2];
    ଦ୍ୱିଗୁଣ prev_coords[2];
} SDL_XInput2RelativeDevice;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_XInput2DeviceInfo
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    ସଂରଚନା SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

ସ୍ଥିର SDL_XInput2DeviceInfo *xinput2_device_info;

ସ୍ଥିର ଶୂନ୍ୟ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ଅଚଳ XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ଦ୍ୱିଗୁଣ processed_coords[2] = { 0.0, 0.0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟଗୁଡ଼ିକ_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ଅଚଳ bool use_raw_vals = mouse->ନିବେଶ_Transform || !mouse->enable_relative_system_scale;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        ଯଦି (!XIMaskIsSet(rawev->valuators.mask, i)) {
            ଜାରି;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < 2; ++j) {
            ଯଦି (rel_dev->ସଂଖ୍ୟା_2[j] == i) {
                ଅଚଳ ଦ୍ୱିଗୁଣ current_val = use_raw_vals ? rawev->raw_ମୂଲ୍ୟଗୁଡ଼ିକ[ମୂଲ୍ୟଗୁଡ଼ିକ_i] : rawev->valuators.ମୂଲ୍ୟଗୁଡ଼ିକ[ମୂଲ୍ୟଗୁଡ଼ିକ_i];

                ଯଦି (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ଅନ୍ୟଥା {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ଯଦି (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                ଭାଙ୍ଗ;
            }
        }

        ++ମୂଲ୍ୟଗୁଡ଼ିକ_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ଯଦି (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ଦଶମିକ)processed_coords[0], (ଦଶମିକ)processed_coords[1]);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା query_xinput2_version(Display *display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା major, ପୂର୍ଣ୍ଣସଂଖ୍ୟା minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    ଫେରନ୍ତୁ (major * 1000) + minor;
}

ସ୍ଥିର bool xinput2_version_atleast(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା version, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା wantmajor, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା wantminor)
{
    ଫେରନ୍ତୁ version >= ((wantmajor * 1000) + wantminor);
}

ସ୍ଥିର SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ଅଚଳ SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    ଫେରନ୍ତୁ windowdata ? windowdata->window : ଖାଲି;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ସ୍ଥିର ଶୂନ୍ୟ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ଅଚଳ XIDeviceEvent *xev)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟଗୁଡ଼ିକ_i = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < xev->valuators.mask_len * 8; ++j) {
        ଯଦି (!XIMaskIsSet(xev->valuators.mask, j)) {
            ଜାରି;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < scroll_dev->scroll_info_ଗଣନା; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ଯଦି (info->ସଂଖ୍ୟା_2 == j) {
                ଅଚଳ ଦ୍ୱିଗୁଣ current_val = xev->valuators.ମୂଲ୍ୟଗୁଡ଼ିକ[ମୂଲ୍ୟଗୁଡ଼ିକ_i];
                ଅଚଳ ଦ୍ୱିଗୁଣ delta = (info->prev_ମୂଲ୍ୟ - current_val) / info->increment;
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
                ଯଦି (info->prev_ମୂଲ୍ୟ_valid && SDL_fabs(delta) < (ଦ୍ୱିଗୁଣ)SDL_MAX_SINT32 * 0.95) {
                    ଅଚଳ ଦ୍ୱିଗୁଣ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ଅଚଳ ଦ୍ୱିଗୁଣ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (ଦଶମିକ)-x, (ଦଶମିକ)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_ମୂଲ୍ୟ = current_val;
                info->prev_ମୂଲ୍ୟ_valid = true;
            }
        }

        ++ମୂଲ୍ୟଗୁଡ଼ିକ_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ସ୍ଥିର ଶୂନ୍ୟ xinput2_normalize_touch_coordinates(SDL_Window *window, ଦ୍ୱିଗୁଣ in_x, ଦ୍ୱିଗୁଣ in_y, ଦଶମିକ *out_x, ଦଶମିକ *out_y)
{
    ଯଦି (window) {
        ଯଦି (window->w == 1) {
            *out_x = 0.5f;
        } ଅନ୍ୟଥା {
            *out_x = (ଦଶମିକ)in_x / (window->w - 1);
        }
        ଯଦି (window->h == 1) {
            *out_y = 0.5f;
        } ଅନ୍ୟଥା {
            *out_y = (ଦଶମିକ)in_y / (window->h - 1);
        }
    } ଅନ୍ୟଥା {
        // couldn't find the window...
        *out_x = (ଦଶମିକ)in_x;
        *out_y = (ଦଶମିକ)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା version = 0;
    XIEventMask eventmask;
    unsigned ଅକ୍ଷର mask[5] = { 0, 0, 0, 0, 0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ଯଦି (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        ଫେରନ୍ତୁ false;
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
    ଯଦି (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        ଫେରନ୍ତୁ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    ଯଦି (!xinput2_version_atleast(version, 2, 0)) {
        ଫେରନ୍ତୁ false; // X server does not support the version we want at all.
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
    eventmask.mask_len = ଆକାର(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ଯଦି (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ଯଦି (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_ମୂଳ_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = ଆକାର(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_ଚାବି_Press);
    XISetMask(mask, XI_ଚାବି_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_ମୂଳ_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ false;
#endif
}

ଶୂନ୍ୟ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ପାଇଁ (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = ଖାଲି; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = ଖାଲି;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = ଖାଲି;
    xinput2_pointer_button_map_size = 0;
#endif
}

ଶୂନ୍ୟ X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ଯଦି (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = ଖାଲି;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, ଖାଲି, 0);
        ଯଦି (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, ଆକାର(unsigned ଅକ୍ଷର));
            ଯଦି (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } ଅନ୍ୟଥା {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ସ୍ଥିର ଶୂନ୍ୟ xinput2_remove_device_info(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_id)
{
    ପାଇଁ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ଖାଲି; devinfo; devinfo = devinfo->next) {
        ଯଦି (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ଖାଲି));
            ଯଦି (!prev) {
                xinput2_device_info = devinfo->next;
            } ଅନ୍ୟଥା {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            ଫେରନ୍ତୁ;
        }
        prev = devinfo;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ xinput2_reset_device_valuators(ଶୂନ୍ୟ)
{
    ପାଇଁ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < devinfo->scroll.scroll_info_ଗଣନା; ++i) {
            devinfo->scroll.scroll_info[i].prev_ମୂଲ୍ୟ_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_classes)
{
    ଯଦି (!devinfo) {
        ଫେରନ୍ତୁ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା allocated_scroll_info_ଗଣନା = devinfo->scroll.scroll_info_ଗଣନା;
    devinfo->scroll.scroll_info_ଗଣନା = 0;
#endif

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_classes; ++i) {
        ଯଦି (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ଅଚଳ XIValuatorClassInfo *v = (ଅଚଳ XIValuatorClassInfo *)classes[i];
            ଯଦି (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.ସଂଖ୍ୟା_2[0] = v->ସଂଖ୍ୟା_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ଯଦି (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ଅନ୍ୟଥା ଯଦି (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ଅନ୍ୟଥା ଯଦି (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.ସଂଖ୍ୟା_2[1] = v->ସଂଖ୍ୟା_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ଯଦି (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ଅନ୍ୟଥା ଯଦି (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ଅନ୍ୟଥା ଯଦି (classes[i]->type == XIScrollClass) {
            ଅଚଳ XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ଯଦି (devinfo->scroll.scroll_info_ଗଣନା == allocated_scroll_info_ଗଣନା) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_ଗଣନା + 2) * ଆକାର(SDL_XInput2ScrollInfo));
                ଯଦି (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_ଗଣନା = 0;
                    devinfo->scroll.scroll_info_ଗଣନା = 0;
                    ଜାରି;
                }

                allocated_scroll_info_ଗଣନା += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_ଗଣନା];
            ++devinfo->scroll.scroll_info_ଗଣନା;

            SDL_zerop(scroll_info);
            scroll_info->ସଂଖ୍ୟା_2 = s->ସଂଖ୍ୟା_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ସ୍ଥିର SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_id)
{
    ପାଇଁ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ଖାଲି; devinfo; devinfo = devinfo->next) {
        ଯଦି (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ଖାଲି));
            ଯଦି (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            ଫେରନ୍ତୁ devinfo;
        }
        prev = devinfo;
    }

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ଯଦି (devinfo) {
        ଫେରନ୍ତୁ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, ଆକାର(SDL_XInput2DeviceInfo));
    ଯଦି (!devinfo) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ଯଦି (!xidevinfo) {
        SDL_free(devinfo);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->ଅଙ୍କ_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    ଫେରନ୍ତୁ devinfo;
}
#endif

ଶୂନ୍ୟ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    ଯଦି (cookie->extension != xinput2_opcode) {
        ଫେରନ୍ତୁ;
    }

    ବାଛ (cookie->evtype) {
    ସ୍ଥିତି XI_HierarchyChanged:
    {
        ଅଚଳ XIHierarchyEvent *hierev = (ଅଚଳ XIHierarchyEvent *)cookie->data;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < hierev->ଅଙ୍କ_info; ++i) {
            // pen stuff...
            ଯଦି ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ଅନ୍ୟଥା ଯଦି ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ଯଦି (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } ଭାଙ୍ଗ;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    ସ୍ଥିତି XI_DeviceChanged:
    {
        ଅଚଳ XIDeviceChangedEvent *dcev = (ଅଚଳ XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ଯଦି (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->ଅଙ୍କ_classes);
        }
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_PropertyEvent:
    {
        ଅଚଳ XIPropertyEvent *proev = (ଅଚଳ XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        ଯଦି (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : ଖାଲି, proev->deviceid);
        }
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_RawMotion:
    {
        ଅଚଳ XIRawEvent *rawev = (ଅଚଳ XIRawEvent *)cookie->data;
        ଅଚଳ bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != ଖାଲି;

        videodata->global_mouse_changed = true;
        ଯଦି (is_pen) {
            ଭାଙ୍ଗ; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ଯଦି (!devinfo) {
            ଭାଙ୍ଗ; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_ଚାବି_Press:
    ସ୍ଥିତି XI_ଚାବି_Release:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        ଯଦି (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ଭାଙ୍ଗ;
        }

        ଯଦି (cookie->evtype == XI_ଚାବି_Press) {
            xevent.type = ଚାବି_Press;
        } ଅନ୍ୟଥା {
            xevent.type = ଚାବି_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.ମୂଳ = xev->ମୂଳ;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)xev->event_x;
        xevent.xkey.y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)xev->event_y;
        xevent.xkey.x_ମୂଳ = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)xev->ମୂଳ_x;
        xevent.xkey.y_ମୂଳ = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)xev->ମୂଳ_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_ଚାବି_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ଅନ୍ୟଥା
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_ଚାବି_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_RawButtonPress:
    ସ୍ଥିତି XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ସ୍ଥିତି XI_RawTouchBegin:
    ସ୍ଥିତି XI_RawTouchUpdate:
    ସ୍ଥିତି XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_ButtonPress:
    ସ୍ଥିତି XI_ButtonRelease:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା button = xev->detail;
        ଅଚଳ bool down = (cookie->evtype == XI_ButtonPress);
#ଯଦି defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ଅନ୍ୟଥା
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        ଯଦି (pen) {
            ଯଦି (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ଭାଙ୍ଗ;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            ଯଦି (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } ଅନ୍ୟଥା {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } ଅନ୍ୟଥା ଯଦି (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା x_ticks = 0, y_ticks = 0;

            ଯଦି (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ଯଦି (SDL_GetMouseFocus() != windowdata->window) {
                    ଭାଙ୍ଗ;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ଯଦି (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ଯଦି (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ଭାଙ୍ଗ;
            }

            ଯଦି (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ଦଶମିକ)xev->event_x, (ଦଶମିକ)xev->event_y, xev->time, xev->serial);
            } ଅନ୍ୟଥା {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ଭାଙ୍ଗ;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    ସ୍ଥିତି XI_Motion:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
#ଯଦି defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#ଅନ୍ୟଥା
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        ଯଦି (pen) {
            ଯଦି (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ଭାଙ୍ଗ;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (ଦଶମିକ) xev->event_x, (ଦଶମିକ) xev->event_y);

            ଦଶମିକ axes[SDL_PEN_AXIS_ଗଣନା];
            X11_PenAxesFromValuators(pen, xev->valuators.ମୂଲ୍ୟଗୁଡ଼ିକ, xev->valuators.mask, xev->valuators.mask_len, axes);

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_arraysize(axes); i++) {
                ଯଦି (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ଅନ୍ୟଥା ଯଦି (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ଯଦି (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ଯଦି (devinfo) {
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
            ଯଦି (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_ଗଣନା && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ଯଦି (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (ଦଶମିକ)xev->event_x, (ଦଶମିକ)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (ଦଶମିକ)xev->event_x, (ଦଶମିକ)xev->event_y);
                }
            }
        }
    } ଭାଙ୍ଗ;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ସ୍ଥିତି XI_TouchBegin:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
        ଦଶମିକ x, y;
        ++xinput2_active_touch_ଗଣନା;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_TouchEnd:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
        ଦଶମିକ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        ଯଦି (!--xinput2_active_touch_ଗଣନା && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } ଭାଙ୍ଗ;

    ସ୍ଥିତି XI_TouchUpdate:
    {
        ଅଚଳ XIDeviceEvent *xev = (ଅଚଳ XIDeviceEvent *)cookie->data;
        ଦଶମିକ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } ଭାଙ୍ଗ;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ସ୍ଥିତି XI_GesturePinchBegin:
    ସ୍ଥିତି XI_GesturePinchUpdate:
    ସ୍ଥିତି XI_GesturePinchEnd:
    {
        ଅଚଳ XIGesturePinchEvent *xev = (ଅଚଳ XIGesturePinchEvent *)cookie->data;
        ଦଶମିକ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        ଯଦି (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ଅନ୍ୟଥା ଯଦି (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (ଦଶମିକ)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ଅନ୍ୟଥା {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ଭାଙ୍ଗ;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ଶୂନ୍ୟ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_ଗଣନା = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ଅଚଳ bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_ଗଣନା || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    ଫେରନ୍ତୁ ret;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ଶୂନ୍ୟ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#ଯଦି defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned ଅକ୍ଷର mask[5] = { 0, 0, 0, 0, 0 };

    ଯଦି (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        ଫେରନ୍ତୁ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = ଆକାର(mask);
    eventmask.mask = mask;

    ଯଦି (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    ଯଦି (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ଯଦି (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(ଶୂନ୍ୟ)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ଫେରନ୍ତୁ xinput2_initialized;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ଅଚଳ SDL_VideoData *data = _this->internal;

    ଯଦି (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned ଅକ୍ଷର mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = ଆକାର(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_ଚାବି_Press);
        XISetMask(mask, XI_ଚାବି_Release);
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

        ଯଦି (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ନିବେଶ, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    ଯଦି (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned ଅକ୍ଷର mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    ଯଦି (!xinput2_multitouch_supported) {
        ଫେରନ୍ତୁ;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = ଆକାର(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

ଶୂନ୍ୟ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    ଯଦି (!xinput2_multitouch_supported) {
        ଫେରନ୍ତୁ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

ସ୍ଥିର ଶୂନ୍ୟ AddDeviceID(Uint32 deviceID, Uint32 **list, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_ଗଣନା = (*ଗଣନା_2 + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ଗଣନା * ଆକାର(*new_list));
    ଯଦି (!new_list) {
        // Oh well, we'll drop this one
        ଫେରନ୍ତୁ;
    }
    new_list[new_ଗଣନା - 1] = deviceID;

    *ଗଣନା_2 = new_ଗଣନା;
    *list = new_list;
}

ସ୍ଥିର bool HasDeviceID(Uint32 deviceID, ଅଚଳ Uint32 *list, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଗଣନା_2; ++i) {
        ଯଦି (deviceID == list[i]) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ସ୍ଥିର ଶୂନ୍ୟ AddDeviceID64(Uint64 deviceID, Uint64 **list, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_ଗଣନା = (*ଗଣନା_2 + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_ଗଣନା * ଆକାର(*new_list));
    ଯଦି (!new_list) {
        // Oh well, we'll drop this one
        ଫେରନ୍ତୁ;
    }
    new_list[new_ଗଣନା - 1] = deviceID;

    *ଗଣନା_2 = new_ଗଣନା;
    *list = new_list;
}
#endif

ସ୍ଥିର bool HasDeviceID64(Uint64 deviceID, ଅଚଳ Uint64 *list, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଗଣନା_2; ++i) {
        ଯଦି (deviceID == list[i]) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

ଶୂନ୍ୟ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ndevices;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_keyboard_ଗଣନା = 0;
    SDL_KeyboardID *old_keyboards = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_keyboard_ଗଣନା = 0;
    SDL_KeyboardID *new_keyboards = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_mouse_ଗଣନା = 0;
    SDL_MouseID *old_mice = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_mouse_ଗଣନା = 0;
    SDL_MouseID *new_mice = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_touch_ଗଣନା = 0;
    Uint64 *old_touch_devices = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_touch_ଗଣନା = 0;
    Uint64 *new_touch_devices = ଖାଲି;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ଗଣନା);
    old_mice = SDL_GetMice(&old_mouse_ଗଣନା);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_ଗଣନା);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        ବାଛ (dev->use) {
        ସ୍ଥିତି XIMasterKeyboard:
        ସ୍ଥିତି XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_ଗଣନା);
                ଯଦି (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ଗଣନା)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        ସ୍ଥିତି XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_ଗଣନା);
                ଯଦି (!HasDeviceID(mouseID, old_mice, old_mouse_ଗଣନା)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ଯଦି (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->ଅଙ୍କ_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < dev->ଅଙ୍କ_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ଯଦି (class->type != XITouchClass) {
                ଜାରି;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_ଗଣନା);
            ଯଦି (!HasDeviceID64(touchID, old_touch_devices, old_touch_ଗଣନା)) {
                ଯଦି (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } ଅନ୍ୟଥା { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = old_keyboard_ଗଣନା; i--;) {
        ଯଦି (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ଗଣନା)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = old_mouse_ଗଣନା; i--;) {
        ଯଦି (!HasDeviceID(old_mice[i], new_mice, new_mouse_ଗଣନା)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = old_touch_ଗଣନା; i--;) {
        ଯଦି (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_ଗଣନା)) {
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
