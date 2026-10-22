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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
ساكن bool xinput2_initialized;
ساكن bool xinput2_grabbed_touch_raised;
ساكن صحيح xinput2_active_touch_count;
#𐡄𐡍 defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ساكن bool xinput2_scrolling_supported;
ساكن bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ساكن bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ساكن صحيح xinput2_opcode;

ساكن Atom xinput2_rel_x_atom;
ساكن Atom xinput2_rel_y_atom;
ساكن Atom xinput2_abs_x_atom;
ساكن Atom xinput2_abs_y_atom;

// Pointer button remapping table
ساكن unsigned حرف *xinput2_pointer_button_map;
ساكن صحيح xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
تعريفنوع بنية
{
    صحيح number;
    صحيح scroll_type;
    مزدوج prev_value;
    مزدوج increment;
    bool prev_value_valid;
} SDL_XInput2ScrollInfo;

تعريفنوع بنية
{
    صحيح scroll_info_count;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

تعريفنوع بنية
{
    صحيح number[2];
    bool relative[2];
    bool prev_coord_valid[2];
    مزدوج minval[2];
    مزدوج maxval[2];
    مزدوج prev_coords[2];
} SDL_XInput2RelativeDevice;

تعريفنوع بنية SDL_XInput2DeviceInfo
{
    صحيح device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    بنية SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

ساكن SDL_XInput2DeviceInfo *xinput2_device_info;

ساكن فراغ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    مزدوج processed_coords[2] = { 0.0, 0.0 };
    صحيح values_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->InputTransform || !mouse->enable_relative_system_scale;

    لكل (صحيح i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        𐡄𐡍 (!XIMaskIsSet(rawev->valuators.mask, i)) {
            استمر;
        }

        لكل (صحيح j = 0; j < 2; ++j) {
            𐡄𐡍 (rel_dev->number[j] == i) {
                ثابت مزدوج current_val = use_raw_vals ? rawev->raw_values[values_i] : rawev->valuators.values[values_i];

                𐡄𐡍 (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } وإلا {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    𐡄𐡍 (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                اكسر;
            }
        }

        ++values_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    𐡄𐡍 (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (عائم)processed_coords[0], (عائم)processed_coords[1]);
    }
}

ساكن صحيح query_xinput2_version(Display *display, صحيح major, صحيح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xinput2_version_atleast(ثابت صحيح version, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع version >= ((wantmajor * 1000) + wantminor);
}

ساكن SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ثابت SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    أرجع windowdata ? windowdata->window : عدم;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ساكن فراغ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحيح values_i = 0;
    لكل (صحيح j = 0; j < xev->valuators.mask_len * 8; ++j) {
        𐡄𐡍 (!XIMaskIsSet(xev->valuators.mask, j)) {
            استمر;
        }

        لكل (صحيح k = 0; k < scroll_dev->scroll_info_count; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            𐡄𐡍 (info->number == j) {
                ثابت مزدوج current_val = xev->valuators.values[values_i];
                ثابت مزدوج delta = (info->prev_value - current_val) / info->increment;
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
                𐡄𐡍 (info->prev_value_valid && SDL_fabs(delta) < (مزدوج)SDL_MAX_SINT32 * 0.95) {
                    ثابت مزدوج x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت مزدوج y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (عائم)-x, (عائم)y, SDL_MOUSEWHEEL_NORMAL);
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
ساكن فراغ xinput2_normalize_touch_coordinates(SDL_Window *window, مزدوج in_x, مزدوج in_y, عائم *out_x, عائم *out_y)
{
    𐡄𐡍 (window) {
        𐡄𐡍 (window->w == 1) {
            *out_x = 0.5f;
        } وإلا {
            *out_x = (عائم)in_x / (window->w - 1);
        }
        𐡄𐡍 (window->h == 1) {
            *out_y = 0.5f;
        } وإلا {
            *out_y = (عائم)in_y / (window->h - 1);
        }
    } وإلا {
        // couldn't find the window...
        *out_x = (عائم)in_x;
        *out_y = (عائم)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    صحيح version = 0;
    XIEventMask eventmask;
    unsigned حرف mask[5] = { 0, 0, 0, 0, 0 };
    صحيح event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    𐡄𐡍 (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        أرجع false;
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
    𐡄𐡍 (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        أرجع false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    𐡄𐡍 (!xinput2_version_atleast(version, 2, 0)) {
        أرجع false; // X server does not support the version we want at all.
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
    eventmask.mask_len = حجم(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    𐡄𐡍 (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    𐡄𐡍 (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, DefaultRootWindow(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = حجم(mask);
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

    أرجع true;
#وإلا
    أرجع false;
#endif
}

فراغ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    لكل (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = عدم; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = عدم;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = عدم;
    xinput2_pointer_button_map_size = 0;
#endif
}

فراغ X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    𐡄𐡍 (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = عدم;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, عدم, 0);
        𐡄𐡍 (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, حجم(unsigned حرف));
            𐡄𐡍 (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } وإلا {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ساكن فراغ xinput2_remove_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->next) {
        𐡄𐡍 (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            𐡄𐡍 (!prev) {
                xinput2_device_info = devinfo->next;
            } وإلا {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            أرجع;
        }
        prev = devinfo;
    }
}

ساكن فراغ xinput2_reset_device_valuators(فراغ)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        لكل (صحيح i = 0; i < devinfo->scroll.scroll_info_count; ++i) {
            devinfo->scroll.scroll_info[i].prev_value_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ساكن فراغ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, صحيح num_classes)
{
    𐡄𐡍 (!devinfo) {
        أرجع;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    صحيح rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحيح allocated_scroll_info_count = devinfo->scroll.scroll_info_count;
    devinfo->scroll.scroll_info_count = 0;
#endif

    لكل (صحيح i = 0; i < num_classes; ++i) {
        𐡄𐡍 (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            𐡄𐡍 (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.number[0] = v->number;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                𐡄𐡍 (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } وإلا 𐡄𐡍 (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } وإلا 𐡄𐡍 (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.number[1] = v->number;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                𐡄𐡍 (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } وإلا 𐡄𐡍 (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        وإلا 𐡄𐡍 (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            𐡄𐡍 (devinfo->scroll.scroll_info_count == allocated_scroll_info_count) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_count + 2) * حجم(SDL_XInput2ScrollInfo));
                𐡄𐡍 (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_count = 0;
                    devinfo->scroll.scroll_info_count = 0;
                    استمر;
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

ساكن SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->next) {
        𐡄𐡍 (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            𐡄𐡍 (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            أرجع devinfo;
        }
        prev = devinfo;
    }

    أرجع عدم;
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ثابت صحيح device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    𐡄𐡍 (devinfo) {
        أرجع devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, حجم(SDL_XInput2DeviceInfo));
    𐡄𐡍 (!devinfo) {
        أرجع عدم;
    }

    صحيح i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    𐡄𐡍 (!xidevinfo) {
        SDL_free(devinfo);
        أرجع عدم;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->num_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    أرجع devinfo;
}
#endif

فراغ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    𐡄𐡍 (cookie->extension != xinput2_opcode) {
        أرجع;
    }

    بدل (cookie->evtype) {
    حالة XI_HierarchyChanged:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->data;
        لكل (صحيح i = 0; i < hierev->num_info; ++i) {
            // pen stuff...
            𐡄𐡍 ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } وإلا 𐡄𐡍 ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            𐡄𐡍 (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } اكسر;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالة XI_DeviceChanged:
    {
        ثابت XIDeviceChangedEvent *dcev = (ثابت XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        𐡄𐡍 (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->num_classes);
        }
    } اكسر;

    حالة XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        𐡄𐡍 (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : عدم, proev->deviceid);
        }
    } اكسر;

    حالة XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->data;
        ثابت bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != عدم;

        videodata->global_mouse_changed = true;
        𐡄𐡍 (is_pen) {
            اكسر; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        𐡄𐡍 (!devinfo) {
            اكسر; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } اكسر;

    حالة XI_KeyPress:
    حالة XI_KeyRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        𐡄𐡍 (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            اكسر;
        }

        𐡄𐡍 (cookie->evtype == XI_KeyPress) {
            xevent.type = KeyPress;
        } وإلا {
            xevent.type = KeyRelease;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.root = xev->root;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (صحيح)xev->event_x;
        xevent.xkey.y = (صحيح)xev->event_y;
        xevent.xkey.x_root = (صحيح)xev->root_x;
        xevent.xkey.y_root = (صحيح)xev->root_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_HandleKeyEvent(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#وإلا
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_key_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } اكسر;

    حالة XI_RawButtonPress:
    حالة XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_RawTouchBegin:
    حالة XI_RawTouchUpdate:
    حالة XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } اكسر;

    حالة XI_ButtonPress:
    حالة XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        صحيح button = xev->detail;
        ثابت bool down = (cookie->evtype == XI_ButtonPress);
#𐡄𐡍 defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        𐡄𐡍 (pen) {
            𐡄𐡍 (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            𐡄𐡍 (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } وإلا {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } وإلا 𐡄𐡍 (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            صحيح x_ticks = 0, y_ticks = 0;

            𐡄𐡍 (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                𐡄𐡍 (SDL_GetMouseFocus() != windowdata->window) {
                    اكسر;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                𐡄𐡍 (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            𐡄𐡍 (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                اكسر;
            }

            𐡄𐡍 (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (عائم)xev->event_x, (عائم)xev->event_y, xev->time, xev->serial);
            } وإلا {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } اكسر;

    حالة XI_Enter:
    {
        xinput2_reset_device_valuators();
    } اكسر;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    حالة XI_Motion:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
#𐡄𐡍 defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        𐡄𐡍 (pen) {
            𐡄𐡍 (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (عائم) xev->event_x, (عائم) xev->event_y);

            عائم axes[SDL_PEN_AXIS_COUNT];
            X11_PenAxesFromValuators(pen, xev->valuators.values, xev->valuators.mask, xev->valuators.mask_len, axes);

            لكل (صحيح i = 0; i < SDL_arraysize(axes); i++) {
                𐡄𐡍 (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } وإلا 𐡄𐡍 (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            𐡄𐡍 (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                𐡄𐡍 (devinfo) {
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
            𐡄𐡍 (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_count && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                𐡄𐡍 (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (عائم)xev->event_x, (عائم)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (عائم)xev->event_x, (عائم)xev->event_y);
                }
            }
        }
    } اكسر;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        عائم x, y;
        ++xinput2_active_touch_count;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } اكسر;

    حالة XI_TouchEnd:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        عائم x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        𐡄𐡍 (!--xinput2_active_touch_count && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } اكسر;

    حالة XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->data;
        عائم x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } اكسر;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالة XI_GesturePinchBegin:
    حالة XI_GesturePinchUpdate:
    حالة XI_GesturePinchEnd:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->data;
        عائم x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        𐡄𐡍 (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا 𐡄𐡍 (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (عائم)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } اكسر;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
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
    ثابت bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_count || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    أرجع ret;
#وإلا
    أرجع false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#𐡄𐡍 defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned حرف mask[5] = { 0, 0, 0, 0, 0 };

    𐡄𐡍 (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        أرجع;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = حجم(mask);
    eventmask.mask = mask;

    𐡄𐡍 (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    𐡄𐡍 (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    𐡄𐡍 (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(فراغ)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    أرجع xinput2_initialized;
#وإلا
    أرجع false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_VideoData *data = _this->internal;

    𐡄𐡍 (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned حرف mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = حجم(mask);
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

        𐡄𐡍 (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    𐡄𐡍 (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        أرجع true;
    }
    أرجع false;
}

فراغ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned حرف mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    𐡄𐡍 (!xinput2_multitouch_supported) {
        أرجع;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = حجم(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

فراغ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    𐡄𐡍 (!xinput2_multitouch_supported) {
        أرجع;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

ساكن فراغ AddDeviceID(Uint32 deviceID, Uint32 **list, صحيح *count)
{
    صحيح new_count = (*count + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_count * حجم(*new_list));
    𐡄𐡍 (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح count)
{
    لكل (صحيح i = 0; i < count; ++i) {
        𐡄𐡍 (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ AddDeviceID64(Uint64 deviceID, Uint64 **list, صحيح *count)
{
    صحيح new_count = (*count + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_count * حجم(*new_list));
    𐡄𐡍 (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_count - 1] = deviceID;

    *count = new_count;
    *list = new_list;
}
#endif

ساكن bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحيح count)
{
    لكل (صحيح i = 0; i < count; ++i) {
        𐡄𐡍 (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

فراغ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    صحيح ndevices;
    صحيح old_keyboard_count = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_count = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_count = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_count = 0;
    SDL_MouseID *new_mice = عدم;
    صحيح old_touch_count = 0;
    Uint64 *old_touch_devices = عدم;
    صحيح new_touch_count = 0;
    Uint64 *new_touch_devices = عدم;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_count);
    old_mice = SDL_GetMice(&old_mouse_count);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_count);

    لكل (صحيح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        بدل (dev->use) {
        حالة XIMasterKeyboard:
        حالة XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_count);
                𐡄𐡍 (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_count)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            اكسر;
        حالة XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالة XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_count);
                𐡄𐡍 (!HasDeviceID(mouseID, old_mice, old_mouse_count)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        𐡄𐡍 (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->num_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        لكل (صحيح j = 0; j < dev->num_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            𐡄𐡍 (class->type != XITouchClass) {
                استمر;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_count);
            𐡄𐡍 (!HasDeviceID64(touchID, old_touch_devices, old_touch_count)) {
                𐡄𐡍 (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } وإلا { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    لكل (صحيح i = old_keyboard_count; i--;) {
        𐡄𐡍 (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_count)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_count; i--;) {
        𐡄𐡍 (!HasDeviceID(old_mice[i], new_mice, new_mouse_count)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    لكل (صحيح i = old_touch_count; i--;) {
        𐡄𐡍 (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_count)) {
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
