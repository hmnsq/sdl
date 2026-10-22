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

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11pen.h"
#شامل "SDL_x11video.h"
#شامل "SDL_x11xinput2.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_pen_c.h"
#شامل "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
ایستا bool xinput2_initialized;
ایستا bool xinput2_grabbed_touch_raised;
ایستا صحیح xinput2_active_touch_شمار;
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ایستا bool xinput2_scrolling_supported;
ایستا bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ایستا bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ایستا صحیح xinput2_opcode;

ایستا Atom xinput2_rel_x_atom;
ایستا Atom xinput2_rel_y_atom;
ایستا Atom xinput2_abs_x_atom;
ایستا Atom xinput2_abs_y_atom;

// Pointer button remapping table
ایستا unsigned نویسه *xinput2_pointer_button_map;
ایستا صحیح xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
تعریفنوع ساختار
{
    صحیح عدد_2;
    صحیح scroll_type;
    دوگانه prev_مقدار;
    دوگانه increment;
    bool prev_مقدار_valid;
} SDL_XInput2ScrollInfo;

تعریفنوع ساختار
{
    صحیح scroll_info_شمار;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

تعریفنوع ساختار
{
    صحیح عدد_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    دوگانه minval[2];
    دوگانه maxval[2];
    دوگانه prev_coords[2];
} SDL_XInput2RelativeDevice;

تعریفنوع ساختار SDL_XInput2DeviceInfo
{
    صحیح device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    ساختار SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

ایستا SDL_XInput2DeviceInfo *xinput2_device_info;

ایستا تهی parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    دوگانه processed_coords[2] = { 0.0, 0.0 };
    صحیح مقادیر_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->درون_داد_Transform || !mouse->enable_relative_system_scale;

    برای (صحیح i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        اگر (!XIMaskIsSet(rawev->valuators.mask, i)) {
            ادامه;
        }

        برای (صحیح j = 0; j < 2; ++j) {
            اگر (rel_dev->عدد_2[j] == i) {
                ثابت دوگانه current_val = use_raw_vals ? rawev->raw_مقادیر[مقادیر_i] : rawev->valuators.مقادیر[مقادیر_i];

                اگر (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } وگرنه {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    اگر (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                بشکن;
            }
        }

        ++مقادیر_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    اگر (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (اعشاری)processed_coords[0], (اعشاری)processed_coords[1]);
    }
}

ایستا صحیح query_xinput2_version(Display *display, صحیح major, صحیح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    بازگشت (major * 1000) + minor;
}

ایستا bool xinput2_version_atleast(ثابت صحیح version, ثابت صحیح wantmajor, ثابت صحیح wantminor)
{
    بازگشت version >= ((wantmajor * 1000) + wantminor);
}

ایستا SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ثابت SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    بازگشت windowdata ? windowdata->window : پوچ;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ایستا تهی xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحیح مقادیر_i = 0;
    برای (صحیح j = 0; j < xev->valuators.mask_len * 8; ++j) {
        اگر (!XIMaskIsSet(xev->valuators.mask, j)) {
            ادامه;
        }

        برای (صحیح k = 0; k < scroll_dev->scroll_info_شمار; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            اگر (info->عدد_2 == j) {
                ثابت دوگانه current_val = xev->valuators.مقادیر[مقادیر_i];
                ثابت دوگانه delta = (info->prev_مقدار - current_val) / info->increment;
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
                اگر (info->prev_مقدار_valid && SDL_fabs(delta) < (دوگانه)SDL_MAX_SINT32 * 0.95) {
                    ثابت دوگانه x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت دوگانه y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (اعشاری)-x, (اعشاری)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_مقدار = current_val;
                info->prev_مقدار_valid = true;
            }
        }

        ++مقادیر_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ایستا تهی xinput2_normalize_touch_coordinates(SDL_Window *window, دوگانه in_x, دوگانه in_y, اعشاری *out_x, اعشاری *out_y)
{
    اگر (window) {
        اگر (window->w == 1) {
            *out_x = 0.5f;
        } وگرنه {
            *out_x = (اعشاری)in_x / (window->w - 1);
        }
        اگر (window->h == 1) {
            *out_y = 0.5f;
        } وگرنه {
            *out_y = (اعشاری)in_y / (window->h - 1);
        }
    } وگرنه {
        // couldn't find the window...
        *out_x = (اعشاری)in_x;
        *out_y = (اعشاری)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    صحیح version = 0;
    XIEventMask eventmask;
    unsigned نویسه mask[5] = { 0, 0, 0, 0, 0 };
    صحیح event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    اگر (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        بازگشت false;
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
    اگر (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        بازگشت false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    اگر (!xinput2_version_atleast(version, 2, 0)) {
        بازگشت false; // X server does not support the version we want at all.
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
    eventmask.mask_len = اندازه(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    اگر (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    اگر (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_ریشه_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = اندازه(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_کلید_Press);
    XISetMask(mask, XI_کلید_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_ریشه_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    بازگشت true;
#وگرنه
    بازگشت false;
#endif
}

تهی X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    برای (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = پوچ; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = پوچ;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = پوچ;
    xinput2_pointer_button_map_size = 0;
#endif
}

تهی X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    اگر (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = پوچ;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, پوچ, 0);
        اگر (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, اندازه(unsigned نویسه));
            اگر (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } وگرنه {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ایستا تهی xinput2_remove_device_info(ثابت صحیح device_id)
{
    برای (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = پوچ; devinfo; devinfo = devinfo->next) {
        اگر (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == پوچ));
            اگر (!prev) {
                xinput2_device_info = devinfo->next;
            } وگرنه {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            بازگشت;
        }
        prev = devinfo;
    }
}

ایستا تهی xinput2_reset_device_valuators(تهی)
{
    برای (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        برای (صحیح i = 0; i < devinfo->scroll.scroll_info_شمار; ++i) {
            devinfo->scroll.scroll_info[i].prev_مقدار_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ایستا تهی xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, صحیح رقم_classes)
{
    اگر (!devinfo) {
        بازگشت;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    صحیح rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحیح allocated_scroll_info_شمار = devinfo->scroll.scroll_info_شمار;
    devinfo->scroll.scroll_info_شمار = 0;
#endif

    برای (صحیح i = 0; i < رقم_classes; ++i) {
        اگر (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            اگر (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.عدد_2[0] = v->عدد_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                اگر (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } وگرنه اگر (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } وگرنه اگر (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.عدد_2[1] = v->عدد_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                اگر (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } وگرنه اگر (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        وگرنه اگر (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            اگر (devinfo->scroll.scroll_info_شمار == allocated_scroll_info_شمار) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_شمار + 2) * اندازه(SDL_XInput2ScrollInfo));
                اگر (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_شمار = 0;
                    devinfo->scroll.scroll_info_شمار = 0;
                    ادامه;
                }

                allocated_scroll_info_شمار += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_شمار];
            ++devinfo->scroll.scroll_info_شمار;

            SDL_zerop(scroll_info);
            scroll_info->عدد_2 = s->عدد_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ایستا SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحیح device_id)
{
    برای (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = پوچ; devinfo; devinfo = devinfo->next) {
        اگر (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == پوچ));
            اگر (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            بازگشت devinfo;
        }
        prev = devinfo;
    }

    بازگشت پوچ;
}

ایستا SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ثابت صحیح device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    اگر (devinfo) {
        بازگشت devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, اندازه(SDL_XInput2DeviceInfo));
    اگر (!devinfo) {
        بازگشت پوچ;
    }

    صحیح i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    اگر (!xidevinfo) {
        SDL_free(devinfo);
        بازگشت پوچ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->رقم_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    بازگشت devinfo;
}
#endif

تهی X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    اگر (cookie->extension != xinput2_opcode) {
        بازگشت;
    }

    انتخاب (cookie->evtype) {
    حالت XI_HierarchyChanged:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->data;
        برای (صحیح i = 0; i < hierev->رقم_info; ++i) {
            // pen stuff...
            اگر ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } وگرنه اگر ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            اگر (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } بشکن;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالت XI_DeviceChanged:
    {
        ثابت XIDeviceChangedEvent *dcev = (ثابت XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        اگر (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->رقم_classes);
        }
    } بشکن;

    حالت XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        اگر (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : پوچ, proev->deviceid);
        }
    } بشکن;

    حالت XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->data;
        ثابت bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != پوچ;

        videodata->global_mouse_changed = true;
        اگر (is_pen) {
            بشکن; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        اگر (!devinfo) {
            بشکن; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } بشکن;

    حالت XI_کلید_Press:
    حالت XI_کلید_Release:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        اگر (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            بشکن;
        }

        اگر (cookie->evtype == XI_کلید_Press) {
            xevent.type = کلید_Press;
        } وگرنه {
            xevent.type = کلید_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.ریشه = xev->ریشه;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (صحیح)xev->event_x;
        xevent.xkey.y = (صحیح)xev->event_y;
        xevent.xkey.x_ریشه = (صحیح)xev->ریشه_x;
        xevent.xkey.y_ریشه = (صحیح)xev->ریشه_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_کلید_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#وگرنه
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_کلید_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } بشکن;

    حالت XI_RawButtonPress:
    حالت XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالت XI_RawTouchBegin:
    حالت XI_RawTouchUpdate:
    حالت XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } بشکن;

    حالت XI_ButtonPress:
    حالت XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        صحیح button = xev->detail;
        ثابت bool down = (cookie->evtype == XI_ButtonPress);
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#وگرنه
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        اگر (pen) {
            اگر (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                بشکن;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            اگر (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } وگرنه {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } وگرنه اگر (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            صحیح x_ticks = 0, y_ticks = 0;

            اگر (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                اگر (SDL_GetMouseFocus() != windowdata->window) {
                    بشکن;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                اگر (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            اگر (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                بشکن;
            }

            اگر (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (اعشاری)xev->event_x, (اعشاری)xev->event_y, xev->time, xev->serial);
            } وگرنه {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } بشکن;

    حالت XI_Enter:
    {
        xinput2_reset_device_valuators();
    } بشکن;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    حالت XI_Motion:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#وگرنه
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        اگر (pen) {
            اگر (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                بشکن;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (اعشاری) xev->event_x, (اعشاری) xev->event_y);

            اعشاری axes[SDL_PEN_AXIS_شمار];
            X11_PenAxesFromValuators(pen, xev->valuators.مقادیر, xev->valuators.mask, xev->valuators.mask_len, axes);

            برای (صحیح i = 0; i < SDL_arraysize(axes); i++) {
                اگر (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } وگرنه اگر (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            اگر (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                اگر (devinfo) {
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
            اگر (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_شمار && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                اگر (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (اعشاری)xev->event_x, (اعشاری)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)xev->event_x, (اعشاری)xev->event_y);
                }
            }
        }
    } بشکن;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالت XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        اعشاری x, y;
        ++xinput2_active_touch_شمار;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } بشکن;

    حالت XI_TouchEnd:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        اعشاری x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        اگر (!--xinput2_active_touch_شمار && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } بشکن;

    حالت XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        اعشاری x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } بشکن;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالت XI_GesturePinchBegin:
    حالت XI_GesturePinchUpdate:
    حالت XI_GesturePinchEnd:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->data;
        اعشاری x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        اگر (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } وگرنه اگر (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (اعشاری)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } وگرنه {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } بشکن;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

تهی X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_شمار = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ثابت bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_شمار || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    بازگشت ret;
#وگرنه
    بازگشت false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

تهی X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned نویسه mask[5] = { 0, 0, 0, 0, 0 };

    اگر (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        بازگشت;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = اندازه(mask);
    eventmask.mask = mask;

    اگر (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    اگر (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    اگر (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(تهی)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    بازگشت xinput2_initialized;
#وگرنه
    بازگشت false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_VideoData *data = _this->internal;

    اگر (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned نویسه mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = اندازه(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_کلید_Press);
        XISetMask(mask, XI_کلید_Release);
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

        اگر (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_درون_داد, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    اگر (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        بازگشت true;
    }
    بازگشت false;
}

تهی X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned نویسه mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    اگر (!xinput2_multitouch_supported) {
        بازگشت;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = اندازه(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

تهی X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    اگر (!xinput2_multitouch_supported) {
        بازگشت;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

ایستا تهی AddDeviceID(Uint32 deviceID, Uint32 **list, صحیح *شمار)
{
    صحیح new_شمار = (*شمار + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمار * اندازه(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        بازگشت;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}

ایستا bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحیح شمار)
{
    برای (صحیح i = 0; i < شمار; ++i) {
        اگر (deviceID == list[i]) {
            بازگشت true;
        }
    }
    بازگشت false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ایستا تهی AddDeviceID64(Uint64 deviceID, Uint64 **list, صحیح *شمار)
{
    صحیح new_شمار = (*شمار + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_شمار * اندازه(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        بازگشت;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}
#endif

ایستا bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحیح شمار)
{
    برای (صحیح i = 0; i < شمار; ++i) {
        اگر (deviceID == list[i]) {
            بازگشت true;
        }
    }
    بازگشت false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

تهی X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    صحیح ndevices;
    صحیح old_keyboard_شمار = 0;
    SDL_KeyboardID *old_keyboards = پوچ;
    صحیح new_keyboard_شمار = 0;
    SDL_KeyboardID *new_keyboards = پوچ;
    صحیح old_mouse_شمار = 0;
    SDL_MouseID *old_mice = پوچ;
    صحیح new_mouse_شمار = 0;
    SDL_MouseID *new_mice = پوچ;
    صحیح old_touch_شمار = 0;
    Uint64 *old_touch_devices = پوچ;
    صحیح new_touch_شمار = 0;
    Uint64 *new_touch_devices = پوچ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمار);
    old_mice = SDL_GetMice(&old_mouse_شمار);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_شمار);

    برای (صحیح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        انتخاب (dev->use) {
        حالت XIMasterKeyboard:
        حالت XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_شمار);
                اگر (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمار)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            بشکن;
        حالت XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالت XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_شمار);
                اگر (!HasDeviceID(mouseID, old_mice, old_mouse_شمار)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            بشکن;
        پیشفرض:
            بشکن;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        اگر (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->رقم_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        برای (صحیح j = 0; j < dev->رقم_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            اگر (class->type != XITouchClass) {
                ادامه;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_شمار);
            اگر (!HasDeviceID64(touchID, old_touch_devices, old_touch_شمار)) {
                اگر (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } وگرنه { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    برای (صحیح i = old_keyboard_شمار; i--;) {
        اگر (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمار)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    برای (صحیح i = old_mouse_شمار; i--;) {
        اگر (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمار)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    برای (صحیح i = old_touch_شمار; i--;) {
        اگر (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_شمار)) {
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
