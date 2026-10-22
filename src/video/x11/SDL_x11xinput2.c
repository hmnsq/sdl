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

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11pen.h"
#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11xinput2.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_pen_c.h"
#அந்தர்பாவ "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
நிலையான bool xinput2_initialized;
நிலையான bool xinput2_grabbed_touch_raised;
நிலையான முழு xinput2_active_touch_மொத்தம்;
#எனில் defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
நிலையான bool xinput2_scrolling_supported;
நிலையான bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
நிலையான bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
நிலையான முழு xinput2_opcode;

நிலையான Atom xinput2_rel_x_atom;
நிலையான Atom xinput2_rel_y_atom;
நிலையான Atom xinput2_abs_x_atom;
நிலையான Atom xinput2_abs_y_atom;

// Pointer button remapping table
நிலையான unsigned எழுத்து *xinput2_pointer_button_map;
நிலையான முழு xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
வகைவரை கட்டமைப்பு
{
    முழு எண்_2;
    முழு scroll_type;
    இரட்டை prev_மதிப்பு;
    இரட்டை increment;
    bool prev_மதிப்பு_valid;
} SDL_XInput2ScrollInfo;

வகைவரை கட்டமைப்பு
{
    முழு scroll_info_மொத்தம்;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

வகைவரை கட்டமைப்பு
{
    முழு எண்_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    இரட்டை minval[2];
    இரட்டை maxval[2];
    இரட்டை prev_coords[2];
} SDL_XInput2RelativeDevice;

வகைவரை கட்டமைப்பு SDL_XInput2DeviceInfo
{
    முழு device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    கட்டமைப்பு SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

நிலையான SDL_XInput2DeviceInfo *xinput2_device_info;

நிலையான வெறுமை parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, மாறிலி XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    இரட்டை processed_coords[2] = { 0.0, 0.0 };
    முழு மதிப்புகள்_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    மாறிலி bool use_raw_vals = mouse->உள்ளீடு_Transform || !mouse->enable_relative_system_scale;

    க்கு (முழு i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        எனில் (!XIMaskIsSet(rawev->valuators.mask, i)) {
            தொடர்;
        }

        க்கு (முழு j = 0; j < 2; ++j) {
            எனில் (rel_dev->எண்_2[j] == i) {
                மாறிலி இரட்டை current_val = use_raw_vals ? rawev->raw_மதிப்புகள்[மதிப்புகள்_i] : rawev->valuators.மதிப்புகள்[மதிப்புகள்_i];

                எனில் (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } இல்லையெனில் {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    எனில் (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                நிறுத்து;
            }
        }

        ++மதிப்புகள்_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    எனில் (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (தசம)processed_coords[0], (தசம)processed_coords[1]);
    }
}

நிலையான முழு query_xinput2_version(Display *display, முழு major, முழு minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    திரும்பு (major * 1000) + minor;
}

நிலையான bool xinput2_version_atleast(மாறிலி முழு version, மாறிலி முழு wantmajor, மாறிலி முழு wantminor)
{
    திரும்பு version >= ((wantmajor * 1000) + wantminor);
}

நிலையான SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    மாறிலி SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    திரும்பு windowdata ? windowdata->window : வெற்று;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
நிலையான வெறுமை xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, மாறிலி XIDeviceEvent *xev)
{
    முழு மதிப்புகள்_i = 0;
    க்கு (முழு j = 0; j < xev->valuators.mask_len * 8; ++j) {
        எனில் (!XIMaskIsSet(xev->valuators.mask, j)) {
            தொடர்;
        }

        க்கு (முழு k = 0; k < scroll_dev->scroll_info_மொத்தம்; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            எனில் (info->எண்_2 == j) {
                மாறிலி இரட்டை current_val = xev->valuators.மதிப்புகள்[மதிப்புகள்_i];
                மாறிலி இரட்டை delta = (info->prev_மதிப்பு - current_val) / info->increment;
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
                எனில் (info->prev_மதிப்பு_valid && SDL_fabs(delta) < (இரட்டை)SDL_MAX_SINT32 * 0.95) {
                    மாறிலி இரட்டை x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    மாறிலி இரட்டை y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (தசம)-x, (தசம)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_மதிப்பு = current_val;
                info->prev_மதிப்பு_valid = true;
            }
        }

        ++மதிப்புகள்_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
நிலையான வெறுமை xinput2_normalize_touch_coordinates(SDL_Window *window, இரட்டை in_x, இரட்டை in_y, தசம *out_x, தசம *out_y)
{
    எனில் (window) {
        எனில் (window->w == 1) {
            *out_x = 0.5f;
        } இல்லையெனில் {
            *out_x = (தசம)in_x / (window->w - 1);
        }
        எனில் (window->h == 1) {
            *out_y = 0.5f;
        } இல்லையெனில் {
            *out_y = (தசம)in_y / (window->h - 1);
        }
    } இல்லையெனில் {
        // couldn't find the window...
        *out_x = (தசம)in_x;
        *out_y = (தசம)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    முழு version = 0;
    XIEventMask eventmask;
    unsigned எழுத்து mask[5] = { 0, 0, 0, 0, 0 };
    முழு event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    எனில் (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        திரும்பு false;
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
    எனில் (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        திரும்பு false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    எனில் (!xinput2_version_atleast(version, 2, 0)) {
        திரும்பு false; // X server does not support the version we want at all.
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
    eventmask.mask_len = அளவு(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    எனில் (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    எனில் (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_வேர்_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = அளவு(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_சாவி_Press);
    XISetMask(mask, XI_சாவி_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_வேர்_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    திரும்பு true;
#இல்லையெனில்
    திரும்பு false;
#endif
}

வெறுமை X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    க்கு (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = வெற்று; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = வெற்று;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = வெற்று;
    xinput2_pointer_button_map_size = 0;
#endif
}

வெறுமை X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    எனில் (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = வெற்று;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, வெற்று, 0);
        எனில் (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, அளவு(unsigned எழுத்து));
            எனில் (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } இல்லையெனில் {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
நிலையான வெறுமை xinput2_remove_device_info(மாறிலி முழு device_id)
{
    க்கு (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = வெற்று; devinfo; devinfo = devinfo->next) {
        எனில் (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == வெற்று));
            எனில் (!prev) {
                xinput2_device_info = devinfo->next;
            } இல்லையெனில் {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            திரும்பு;
        }
        prev = devinfo;
    }
}

நிலையான வெறுமை xinput2_reset_device_valuators(வெறுமை)
{
    க்கு (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        க்கு (முழு i = 0; i < devinfo->scroll.scroll_info_மொத்தம்; ++i) {
            devinfo->scroll.scroll_info[i].prev_மதிப்பு_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

நிலையான வெறுமை xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, முழு இலக்கம்_classes)
{
    எனில் (!devinfo) {
        திரும்பு;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    முழு rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    முழு allocated_scroll_info_மொத்தம் = devinfo->scroll.scroll_info_மொத்தம்;
    devinfo->scroll.scroll_info_மொத்தம் = 0;
#endif

    க்கு (முழு i = 0; i < இலக்கம்_classes; ++i) {
        எனில் (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            மாறிலி XIValuatorClassInfo *v = (மாறிலி XIValuatorClassInfo *)classes[i];
            எனில் (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.எண்_2[0] = v->எண்_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                எனில் (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } இல்லையெனில் எனில் (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } இல்லையெனில் எனில் (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.எண்_2[1] = v->எண்_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                எனில் (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } இல்லையெனில் எனில் (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        இல்லையெனில் எனில் (classes[i]->type == XIScrollClass) {
            மாறிலி XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            எனில் (devinfo->scroll.scroll_info_மொத்தம் == allocated_scroll_info_மொத்தம்) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_மொத்தம் + 2) * அளவு(SDL_XInput2ScrollInfo));
                எனில் (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_மொத்தம் = 0;
                    devinfo->scroll.scroll_info_மொத்தம் = 0;
                    தொடர்;
                }

                allocated_scroll_info_மொத்தம் += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_மொத்தம்];
            ++devinfo->scroll.scroll_info_மொத்தம்;

            SDL_zerop(scroll_info);
            scroll_info->எண்_2 = s->எண்_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

நிலையான SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(மாறிலி முழு device_id)
{
    க்கு (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = வெற்று; devinfo; devinfo = devinfo->next) {
        எனில் (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == வெற்று));
            எனில் (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            திரும்பு devinfo;
        }
        prev = devinfo;
    }

    திரும்பு வெற்று;
}

நிலையான SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, மாறிலி முழு device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    எனில் (devinfo) {
        திரும்பு devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, அளவு(SDL_XInput2DeviceInfo));
    எனில் (!devinfo) {
        திரும்பு வெற்று;
    }

    முழு i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    எனில் (!xidevinfo) {
        SDL_free(devinfo);
        திரும்பு வெற்று;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->இலக்கம்_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    திரும்பு devinfo;
}
#endif

வெறுமை X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    எனில் (cookie->extension != xinput2_opcode) {
        திரும்பு;
    }

    தேர்வு (cookie->evtype) {
    நிலை XI_HierarchyChanged:
    {
        மாறிலி XIHierarchyEvent *hierev = (மாறிலி XIHierarchyEvent *)cookie->data;
        க்கு (முழு i = 0; i < hierev->இலக்கம்_info; ++i) {
            // pen stuff...
            எனில் ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } இல்லையெனில் எனில் ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            எனில் (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } நிறுத்து;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    நிலை XI_DeviceChanged:
    {
        மாறிலி XIDeviceChangedEvent *dcev = (மாறிலி XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        எனில் (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->இலக்கம்_classes);
        }
    } நிறுத்து;

    நிலை XI_PropertyEvent:
    {
        மாறிலி XIPropertyEvent *proev = (மாறிலி XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        எனில் (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : வெற்று, proev->deviceid);
        }
    } நிறுத்து;

    நிலை XI_RawMotion:
    {
        மாறிலி XIRawEvent *rawev = (மாறிலி XIRawEvent *)cookie->data;
        மாறிலி bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != வெற்று;

        videodata->global_mouse_changed = true;
        எனில் (is_pen) {
            நிறுத்து; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        எனில் (!devinfo) {
            நிறுத்து; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } நிறுத்து;

    நிலை XI_சாவி_Press:
    நிலை XI_சாவி_Release:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        எனில் (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            நிறுத்து;
        }

        எனில் (cookie->evtype == XI_சாவி_Press) {
            xevent.type = சாவி_Press;
        } இல்லையெனில் {
            xevent.type = சாவி_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.வேர் = xev->வேர்;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (முழு)xev->event_x;
        xevent.xkey.y = (முழு)xev->event_y;
        xevent.xkey.x_வேர் = (முழு)xev->வேர்_x;
        xevent.xkey.y_வேர் = (முழு)xev->வேர்_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_சாவி_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#இல்லையெனில்
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_சாவி_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } நிறுத்து;

    நிலை XI_RawButtonPress:
    நிலை XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    நிலை XI_RawTouchBegin:
    நிலை XI_RawTouchUpdate:
    நிலை XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } நிறுத்து;

    நிலை XI_ButtonPress:
    நிலை XI_ButtonRelease:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        முழு button = xev->detail;
        மாறிலி bool down = (cookie->evtype == XI_ButtonPress);
#எனில் defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#இல்லையெனில்
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        எனில் (pen) {
            எனில் (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                நிறுத்து;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            எனில் (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } இல்லையெனில் {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } இல்லையெனில் எனில் (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            முழு x_ticks = 0, y_ticks = 0;

            எனில் (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                எனில் (SDL_GetMouseFocus() != windowdata->window) {
                    நிறுத்து;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                எனில் (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            எனில் (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                நிறுத்து;
            }

            எனில் (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (தசம)xev->event_x, (தசம)xev->event_y, xev->time, xev->serial);
            } இல்லையெனில் {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } நிறுத்து;

    நிலை XI_Enter:
    {
        xinput2_reset_device_valuators();
    } நிறுத்து;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    நிலை XI_Motion:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
#எனில் defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#இல்லையெனில்
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        எனில் (pen) {
            எனில் (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                நிறுத்து;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (தசம) xev->event_x, (தசம) xev->event_y);

            தசம axes[SDL_PEN_AXIS_மொத்தம்];
            X11_PenAxesFromValuators(pen, xev->valuators.மதிப்புகள், xev->valuators.mask, xev->valuators.mask_len, axes);

            க்கு (முழு i = 0; i < SDL_arraysize(axes); i++) {
                எனில் (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } இல்லையெனில் எனில் (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            எனில் (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                எனில் (devinfo) {
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
            எனில் (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_மொத்தம் && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                எனில் (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (தசம)xev->event_x, (தசம)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (தசம)xev->event_x, (தசம)xev->event_y);
                }
            }
        }
    } நிறுத்து;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    நிலை XI_TouchBegin:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
        தசம x, y;
        ++xinput2_active_touch_மொத்தம்;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } நிறுத்து;

    நிலை XI_TouchEnd:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
        தசம x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        எனில் (!--xinput2_active_touch_மொத்தம் && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } நிறுத்து;

    நிலை XI_TouchUpdate:
    {
        மாறிலி XIDeviceEvent *xev = (மாறிலி XIDeviceEvent *)cookie->data;
        தசம x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } நிறுத்து;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    நிலை XI_GesturePinchBegin:
    நிலை XI_GesturePinchUpdate:
    நிலை XI_GesturePinchEnd:
    {
        மாறிலி XIGesturePinchEvent *xev = (மாறிலி XIGesturePinchEvent *)cookie->data;
        தசம x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        எனில் (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } இல்லையெனில் எனில் (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (தசம)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } இல்லையெனில் {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } நிறுத்து;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

வெறுமை X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_மொத்தம் = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    மாறிலி bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_மொத்தம் || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    திரும்பு ret;
#இல்லையெனில்
    திரும்பு false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

வெறுமை X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#எனில் defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned எழுத்து mask[5] = { 0, 0, 0, 0, 0 };

    எனில் (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        திரும்பு;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = அளவு(mask);
    eventmask.mask = mask;

    எனில் (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    எனில் (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    எனில் (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(வெறுமை)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    திரும்பு xinput2_initialized;
#இல்லையெனில்
    திரும்பு false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    மாறிலி SDL_VideoData *data = _this->internal;

    எனில் (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned எழுத்து mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = அளவு(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_சாவி_Press);
        XISetMask(mask, XI_சாவி_Release);
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

        எனில் (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_உள்ளீடு, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    எனில் (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        திரும்பு true;
    }
    திரும்பு false;
}

வெறுமை X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned எழுத்து mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    எனில் (!xinput2_multitouch_supported) {
        திரும்பு;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = அளவு(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

வெறுமை X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    எனில் (!xinput2_multitouch_supported) {
        திரும்பு;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

நிலையான வெறுமை AddDeviceID(Uint32 deviceID, Uint32 **list, முழு *மொத்தம்)
{
    முழு new_மொத்தம் = (*மொத்தம் + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_மொத்தம் * அளவு(*new_list));
    எனில் (!new_list) {
        // Oh well, we'll drop this one
        திரும்பு;
    }
    new_list[new_மொத்தம் - 1] = deviceID;

    *மொத்தம் = new_மொத்தம்;
    *list = new_list;
}

நிலையான bool HasDeviceID(Uint32 deviceID, மாறிலி Uint32 *list, முழு மொத்தம்)
{
    க்கு (முழு i = 0; i < மொத்தம்; ++i) {
        எனில் (deviceID == list[i]) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
நிலையான வெறுமை AddDeviceID64(Uint64 deviceID, Uint64 **list, முழு *மொத்தம்)
{
    முழு new_மொத்தம் = (*மொத்தம் + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_மொத்தம் * அளவு(*new_list));
    எனில் (!new_list) {
        // Oh well, we'll drop this one
        திரும்பு;
    }
    new_list[new_மொத்தம் - 1] = deviceID;

    *மொத்தம் = new_மொத்தம்;
    *list = new_list;
}
#endif

நிலையான bool HasDeviceID64(Uint64 deviceID, மாறிலி Uint64 *list, முழு மொத்தம்)
{
    க்கு (முழு i = 0; i < மொத்தம்; ++i) {
        எனில் (deviceID == list[i]) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

வெறுமை X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    முழு ndevices;
    முழு old_keyboard_மொத்தம் = 0;
    SDL_KeyboardID *old_keyboards = வெற்று;
    முழு new_keyboard_மொத்தம் = 0;
    SDL_KeyboardID *new_keyboards = வெற்று;
    முழு old_mouse_மொத்தம் = 0;
    SDL_MouseID *old_mice = வெற்று;
    முழு new_mouse_மொத்தம் = 0;
    SDL_MouseID *new_mice = வெற்று;
    முழு old_touch_மொத்தம் = 0;
    Uint64 *old_touch_devices = வெற்று;
    முழு new_touch_மொத்தம் = 0;
    Uint64 *new_touch_devices = வெற்று;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_மொத்தம்);
    old_mice = SDL_GetMice(&old_mouse_மொத்தம்);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_மொத்தம்);

    க்கு (முழு i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        தேர்வு (dev->use) {
        நிலை XIMasterKeyboard:
        நிலை XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_மொத்தம்);
                எனில் (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_மொத்தம்)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            நிறுத்து;
        நிலை XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        நிலை XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_மொத்தம்);
                எனில் (!HasDeviceID(mouseID, old_mice, old_mouse_மொத்தம்)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        எனில் (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->இலக்கம்_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        க்கு (முழு j = 0; j < dev->இலக்கம்_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            எனில் (class->type != XITouchClass) {
                தொடர்;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_மொத்தம்);
            எனில் (!HasDeviceID64(touchID, old_touch_devices, old_touch_மொத்தம்)) {
                எனில் (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } இல்லையெனில் { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    க்கு (முழு i = old_keyboard_மொத்தம்; i--;) {
        எனில் (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_மொத்தம்)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    க்கு (முழு i = old_mouse_மொத்தம்; i--;) {
        எனில் (!HasDeviceID(old_mice[i], new_mice, new_mouse_மொத்தம்)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    க்கு (முழு i = old_touch_மொத்தம்; i--;) {
        எனில் (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_மொத்தம்)) {
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
