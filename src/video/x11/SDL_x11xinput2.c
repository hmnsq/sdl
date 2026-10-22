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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "SDL_x11pen.h"
#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11xinput2.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_pen_c.h"
#অন্তর্ভাব "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
স্থির bool xinput2_initialized;
স্থির bool xinput2_grabbed_touch_raised;
স্থির পূর্ণাঙ্ক xinput2_active_touch_গুনতি;
#যদি defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
স্থির bool xinput2_scrolling_supported;
স্থির bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
স্থির bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
স্থির পূর্ণাঙ্ক xinput2_opcode;

স্থির Atom xinput2_rel_x_atom;
স্থির Atom xinput2_rel_y_atom;
স্থির Atom xinput2_abs_x_atom;
স্থির Atom xinput2_abs_y_atom;

// Pointer button remapping table
স্থির unsigned বর্ণ *xinput2_pointer_button_map;
স্থির পূর্ণাঙ্ক xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক সংখ্যা_2;
    পূর্ণাঙ্ক scroll_type;
    দ্বিগুণ prev_মান;
    দ্বিগুণ increment;
    bool prev_মান_valid;
} SDL_XInput2ScrollInfo;

প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক scroll_info_গুনতি;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক সংখ্যা_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    দ্বিগুণ minval[2];
    দ্বিগুণ maxval[2];
    দ্বিগুণ prev_coords[2];
} SDL_XInput2RelativeDevice;

প্রকারনির্দেশ সংরচনা SDL_XInput2DeviceInfo
{
    পূর্ণাঙ্ক device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    সংরচনা SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

স্থির SDL_XInput2DeviceInfo *xinput2_device_info;

স্থির শূন্য parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ধ্রুব XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    দ্বিগুণ processed_coords[2] = { 0.0, 0.0 };
    পূর্ণাঙ্ক মানসমূহ_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ধ্রুব bool use_raw_vals = mouse->প্রবেশ_Transform || !mouse->enable_relative_system_scale;

    প্রতি (পূর্ণাঙ্ক i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        যদি (!XIMaskIsSet(rawev->valuators.mask, i)) {
            অনুবর্ত;
        }

        প্রতি (পূর্ণাঙ্ক j = 0; j < 2; ++j) {
            যদি (rel_dev->সংখ্যা_2[j] == i) {
                ধ্রুব দ্বিগুণ current_val = use_raw_vals ? rawev->raw_মানসমূহ[মানসমূহ_i] : rawev->valuators.মানসমূহ[মানসমূহ_i];

                যদি (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } অন্যথা {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    যদি (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                ভঙ্গ;
            }
        }

        ++মানসমূহ_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    যদি (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ভিন্ন)processed_coords[0], (ভিন্ন)processed_coords[1]);
    }
}

স্থির পূর্ণাঙ্ক query_xinput2_version(Display *display, পূর্ণাঙ্ক major, পূর্ণাঙ্ক minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    প্রত্যাগম (major * 1000) + minor;
}

স্থির bool xinput2_version_atleast(ধ্রুব পূর্ণাঙ্ক version, ধ্রুব পূর্ণাঙ্ক wantmajor, ধ্রুব পূর্ণাঙ্ক wantminor)
{
    প্রত্যাগম version >= ((wantmajor * 1000) + wantminor);
}

স্থির SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ধ্রুব SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    প্রত্যাগম windowdata ? windowdata->window : রিক্ত;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
স্থির শূন্য xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ধ্রুব XIDeviceEvent *xev)
{
    পূর্ণাঙ্ক মানসমূহ_i = 0;
    প্রতি (পূর্ণাঙ্ক j = 0; j < xev->valuators.mask_len * 8; ++j) {
        যদি (!XIMaskIsSet(xev->valuators.mask, j)) {
            অনুবর্ত;
        }

        প্রতি (পূর্ণাঙ্ক k = 0; k < scroll_dev->scroll_info_গুনতি; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            যদি (info->সংখ্যা_2 == j) {
                ধ্রুব দ্বিগুণ current_val = xev->valuators.মানসমূহ[মানসমূহ_i];
                ধ্রুব দ্বিগুণ delta = (info->prev_মান - current_val) / info->increment;
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
                যদি (info->prev_মান_valid && SDL_fabs(delta) < (দ্বিগুণ)SDL_MAX_SINT32 * 0.95) {
                    ধ্রুব দ্বিগুণ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ধ্রুব দ্বিগুণ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (ভিন্ন)-x, (ভিন্ন)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_মান = current_val;
                info->prev_মান_valid = true;
            }
        }

        ++মানসমূহ_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
স্থির শূন্য xinput2_normalize_touch_coordinates(SDL_Window *window, দ্বিগুণ in_x, দ্বিগুণ in_y, ভিন্ন *out_x, ভিন্ন *out_y)
{
    যদি (window) {
        যদি (window->w == 1) {
            *out_x = 0.5f;
        } অন্যথা {
            *out_x = (ভিন্ন)in_x / (window->w - 1);
        }
        যদি (window->h == 1) {
            *out_y = 0.5f;
        } অন্যথা {
            *out_y = (ভিন্ন)in_y / (window->h - 1);
        }
    } অন্যথা {
        // couldn't find the window...
        *out_x = (ভিন্ন)in_x;
        *out_y = (ভিন্ন)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    পূর্ণাঙ্ক version = 0;
    XIEventMask eventmask;
    unsigned বর্ণ mask[5] = { 0, 0, 0, 0, 0 };
    পূর্ণাঙ্ক event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    যদি (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        প্রত্যাগম false;
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
    যদি (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        প্রত্যাগম false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    যদি (!xinput2_version_atleast(version, 2, 0)) {
        প্রত্যাগম false; // X server does not support the version we want at all.
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
    eventmask.mask_len = পরিমাণ(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    যদি (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    যদি (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_মূল_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = পরিমাণ(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_চাবি_Press);
    XISetMask(mask, XI_চাবি_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_মূল_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    প্রত্যাগম true;
#অন্যথা
    প্রত্যাগম false;
#endif
}

শূন্য X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    প্রতি (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = রিক্ত; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = রিক্ত;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = রিক্ত;
    xinput2_pointer_button_map_size = 0;
#endif
}

শূন্য X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    যদি (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = রিক্ত;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, রিক্ত, 0);
        যদি (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, পরিমাণ(unsigned বর্ণ));
            যদি (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } অন্যথা {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
স্থির শূন্য xinput2_remove_device_info(ধ্রুব পূর্ণাঙ্ক device_id)
{
    প্রতি (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = রিক্ত; devinfo; devinfo = devinfo->next) {
        যদি (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == রিক্ত));
            যদি (!prev) {
                xinput2_device_info = devinfo->next;
            } অন্যথা {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            প্রত্যাগম;
        }
        prev = devinfo;
    }
}

স্থির শূন্য xinput2_reset_device_valuators(শূন্য)
{
    প্রতি (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        প্রতি (পূর্ণাঙ্ক i = 0; i < devinfo->scroll.scroll_info_গুনতি; ++i) {
            devinfo->scroll.scroll_info[i].prev_মান_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

স্থির শূন্য xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, পূর্ণাঙ্ক অঙ্ক_classes)
{
    যদি (!devinfo) {
        প্রত্যাগম;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    পূর্ণাঙ্ক rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    পূর্ণাঙ্ক allocated_scroll_info_গুনতি = devinfo->scroll.scroll_info_গুনতি;
    devinfo->scroll.scroll_info_গুনতি = 0;
#endif

    প্রতি (পূর্ণাঙ্ক i = 0; i < অঙ্ক_classes; ++i) {
        যদি (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ধ্রুব XIValuatorClassInfo *v = (ধ্রুব XIValuatorClassInfo *)classes[i];
            যদি (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.সংখ্যা_2[0] = v->সংখ্যা_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                যদি (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } অন্যথা যদি (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } অন্যথা যদি (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.সংখ্যা_2[1] = v->সংখ্যা_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                যদি (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } অন্যথা যদি (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        অন্যথা যদি (classes[i]->type == XIScrollClass) {
            ধ্রুব XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            যদি (devinfo->scroll.scroll_info_গুনতি == allocated_scroll_info_গুনতি) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_গুনতি + 2) * পরিমাণ(SDL_XInput2ScrollInfo));
                যদি (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_গুনতি = 0;
                    devinfo->scroll.scroll_info_গুনতি = 0;
                    অনুবর্ত;
                }

                allocated_scroll_info_গুনতি += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_গুনতি];
            ++devinfo->scroll.scroll_info_গুনতি;

            SDL_zerop(scroll_info);
            scroll_info->সংখ্যা_2 = s->সংখ্যা_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

স্থির SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ধ্রুব পূর্ণাঙ্ক device_id)
{
    প্রতি (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = রিক্ত; devinfo; devinfo = devinfo->next) {
        যদি (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == রিক্ত));
            যদি (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            প্রত্যাগম devinfo;
        }
        prev = devinfo;
    }

    প্রত্যাগম রিক্ত;
}

স্থির SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ধ্রুব পূর্ণাঙ্ক device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    যদি (devinfo) {
        প্রত্যাগম devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, পরিমাণ(SDL_XInput2DeviceInfo));
    যদি (!devinfo) {
        প্রত্যাগম রিক্ত;
    }

    পূর্ণাঙ্ক i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    যদি (!xidevinfo) {
        SDL_free(devinfo);
        প্রত্যাগম রিক্ত;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->অঙ্ক_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    প্রত্যাগম devinfo;
}
#endif

শূন্য X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    যদি (cookie->extension != xinput2_opcode) {
        প্রত্যাগম;
    }

    বিকল্প (cookie->evtype) {
    পক্ষ XI_HierarchyChanged:
    {
        ধ্রুব XIHierarchyEvent *hierev = (ধ্রুব XIHierarchyEvent *)cookie->data;
        প্রতি (পূর্ণাঙ্ক i = 0; i < hierev->অঙ্ক_info; ++i) {
            // pen stuff...
            যদি ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } অন্যথা যদি ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            যদি (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } ভঙ্গ;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    পক্ষ XI_DeviceChanged:
    {
        ধ্রুব XIDeviceChangedEvent *dcev = (ধ্রুব XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        যদি (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->অঙ্ক_classes);
        }
    } ভঙ্গ;

    পক্ষ XI_PropertyEvent:
    {
        ধ্রুব XIPropertyEvent *proev = (ধ্রুব XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        যদি (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : রিক্ত, proev->deviceid);
        }
    } ভঙ্গ;

    পক্ষ XI_RawMotion:
    {
        ধ্রুব XIRawEvent *rawev = (ধ্রুব XIRawEvent *)cookie->data;
        ধ্রুব bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != রিক্ত;

        videodata->global_mouse_changed = true;
        যদি (is_pen) {
            ভঙ্গ; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        যদি (!devinfo) {
            ভঙ্গ; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ভঙ্গ;

    পক্ষ XI_চাবি_Press:
    পক্ষ XI_চাবি_Release:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        যদি (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ভঙ্গ;
        }

        যদি (cookie->evtype == XI_চাবি_Press) {
            xevent.type = চাবি_Press;
        } অন্যথা {
            xevent.type = চাবি_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.মূল = xev->মূল;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (পূর্ণাঙ্ক)xev->event_x;
        xevent.xkey.y = (পূর্ণাঙ্ক)xev->event_y;
        xevent.xkey.x_মূল = (পূর্ণাঙ্ক)xev->মূল_x;
        xevent.xkey.y_মূল = (পূর্ণাঙ্ক)xev->মূল_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_চাবি_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#অন্যথা
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_চাবি_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } ভঙ্গ;

    পক্ষ XI_RawButtonPress:
    পক্ষ XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    পক্ষ XI_RawTouchBegin:
    পক্ষ XI_RawTouchUpdate:
    পক্ষ XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } ভঙ্গ;

    পক্ষ XI_ButtonPress:
    পক্ষ XI_ButtonRelease:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        পূর্ণাঙ্ক button = xev->detail;
        ধ্রুব bool down = (cookie->evtype == XI_ButtonPress);
#যদি defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#অন্যথা
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        যদি (pen) {
            যদি (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ভঙ্গ;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            যদি (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } অন্যথা {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } অন্যথা যদি (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            পূর্ণাঙ্ক x_ticks = 0, y_ticks = 0;

            যদি (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                যদি (SDL_GetMouseFocus() != windowdata->window) {
                    ভঙ্গ;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                যদি (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            যদি (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ভঙ্গ;
            }

            যদি (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ভিন্ন)xev->event_x, (ভিন্ন)xev->event_y, xev->time, xev->serial);
            } অন্যথা {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } ভঙ্গ;

    পক্ষ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ভঙ্গ;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    পক্ষ XI_Motion:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
#যদি defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#অন্যথা
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        যদি (pen) {
            যদি (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ভঙ্গ;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (ভিন্ন) xev->event_x, (ভিন্ন) xev->event_y);

            ভিন্ন axes[SDL_PEN_AXIS_গুনতি];
            X11_PenAxesFromValuators(pen, xev->valuators.মানসমূহ, xev->valuators.mask, xev->valuators.mask_len, axes);

            প্রতি (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(axes); i++) {
                যদি (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } অন্যথা যদি (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            যদি (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                যদি (devinfo) {
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
            যদি (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_গুনতি && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                যদি (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (ভিন্ন)xev->event_x, (ভিন্ন)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (ভিন্ন)xev->event_x, (ভিন্ন)xev->event_y);
                }
            }
        }
    } ভঙ্গ;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    পক্ষ XI_TouchBegin:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
        ভিন্ন x, y;
        ++xinput2_active_touch_গুনতি;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } ভঙ্গ;

    পক্ষ XI_TouchEnd:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
        ভিন্ন x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        যদি (!--xinput2_active_touch_গুনতি && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } ভঙ্গ;

    পক্ষ XI_TouchUpdate:
    {
        ধ্রুব XIDeviceEvent *xev = (ধ্রুব XIDeviceEvent *)cookie->data;
        ভিন্ন x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } ভঙ্গ;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    পক্ষ XI_GesturePinchBegin:
    পক্ষ XI_GesturePinchUpdate:
    পক্ষ XI_GesturePinchEnd:
    {
        ধ্রুব XIGesturePinchEvent *xev = (ধ্রুব XIGesturePinchEvent *)cookie->data;
        ভিন্ন x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        যদি (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } অন্যথা যদি (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (ভিন্ন)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } অন্যথা {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ভঙ্গ;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

শূন্য X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_গুনতি = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ধ্রুব bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_গুনতি || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    প্রত্যাগম ret;
#অন্যথা
    প্রত্যাগম false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

শূন্য X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned বর্ণ mask[5] = { 0, 0, 0, 0, 0 };

    যদি (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        প্রত্যাগম;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = পরিমাণ(mask);
    eventmask.mask = mask;

    যদি (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    যদি (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    যদি (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(শূন্য)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    প্রত্যাগম xinput2_initialized;
#অন্যথা
    প্রত্যাগম false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ধ্রুব SDL_VideoData *data = _this->internal;

    যদি (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned বর্ণ mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = পরিমাণ(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_চাবি_Press);
        XISetMask(mask, XI_চাবি_Release);
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

        যদি (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_প্রবেশ, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    যদি (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

শূন্য X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned বর্ণ mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    যদি (!xinput2_multitouch_supported) {
        প্রত্যাগম;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = পরিমাণ(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

শূন্য X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    যদি (!xinput2_multitouch_supported) {
        প্রত্যাগম;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

স্থির শূন্য AddDeviceID(Uint32 deviceID, Uint32 **list, পূর্ণাঙ্ক *গুনতি)
{
    পূর্ণাঙ্ক new_গুনতি = (*গুনতি + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_গুনতি * পরিমাণ(*new_list));
    যদি (!new_list) {
        // Oh well, we'll drop this one
        প্রত্যাগম;
    }
    new_list[new_গুনতি - 1] = deviceID;

    *গুনতি = new_গুনতি;
    *list = new_list;
}

স্থির bool HasDeviceID(Uint32 deviceID, ধ্রুব Uint32 *list, পূর্ণাঙ্ক গুনতি)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < গুনতি; ++i) {
        যদি (deviceID == list[i]) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
স্থির শূন্য AddDeviceID64(Uint64 deviceID, Uint64 **list, পূর্ণাঙ্ক *গুনতি)
{
    পূর্ণাঙ্ক new_গুনতি = (*গুনতি + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_গুনতি * পরিমাণ(*new_list));
    যদি (!new_list) {
        // Oh well, we'll drop this one
        প্রত্যাগম;
    }
    new_list[new_গুনতি - 1] = deviceID;

    *গুনতি = new_গুনতি;
    *list = new_list;
}
#endif

স্থির bool HasDeviceID64(Uint64 deviceID, ধ্রুব Uint64 *list, পূর্ণাঙ্ক গুনতি)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < গুনতি; ++i) {
        যদি (deviceID == list[i]) {
            প্রত্যাগম true;
        }
    }
    প্রত্যাগম false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

শূন্য X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    পূর্ণাঙ্ক ndevices;
    পূর্ণাঙ্ক old_keyboard_গুনতি = 0;
    SDL_KeyboardID *old_keyboards = রিক্ত;
    পূর্ণাঙ্ক new_keyboard_গুনতি = 0;
    SDL_KeyboardID *new_keyboards = রিক্ত;
    পূর্ণাঙ্ক old_mouse_গুনতি = 0;
    SDL_MouseID *old_mice = রিক্ত;
    পূর্ণাঙ্ক new_mouse_গুনতি = 0;
    SDL_MouseID *new_mice = রিক্ত;
    পূর্ণাঙ্ক old_touch_গুনতি = 0;
    Uint64 *old_touch_devices = রিক্ত;
    পূর্ণাঙ্ক new_touch_গুনতি = 0;
    Uint64 *new_touch_devices = রিক্ত;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_গুনতি);
    old_mice = SDL_GetMice(&old_mouse_গুনতি);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_গুনতি);

    প্রতি (পূর্ণাঙ্ক i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        বিকল্প (dev->use) {
        পক্ষ XIMasterKeyboard:
        পক্ষ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_গুনতি);
                যদি (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_গুনতি)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            ভঙ্গ;
        পক্ষ XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        পক্ষ XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_গুনতি);
                যদি (!HasDeviceID(mouseID, old_mice, old_mouse_গুনতি)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        যদি (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->অঙ্ক_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        প্রতি (পূর্ণাঙ্ক j = 0; j < dev->অঙ্ক_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            যদি (class->type != XITouchClass) {
                অনুবর্ত;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_গুনতি);
            যদি (!HasDeviceID64(touchID, old_touch_devices, old_touch_গুনতি)) {
                যদি (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } অন্যথা { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    প্রতি (পূর্ণাঙ্ক i = old_keyboard_গুনতি; i--;) {
        যদি (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_গুনতি)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    প্রতি (পূর্ণাঙ্ক i = old_mouse_গুনতি; i--;) {
        যদি (!HasDeviceID(old_mice[i], new_mice, new_mouse_গুনতি)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    প্রতি (পূর্ণাঙ্ক i = old_touch_গুনতি; i--;) {
        যদি (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_গুনতি)) {
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
