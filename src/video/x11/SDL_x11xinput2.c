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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "SDL_x11pen.h"
#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11xinput2.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_pen_c.h"
#અન્તર્ભાવ "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
સ્થિર bool xinput2_initialized;
સ્થિર bool xinput2_grabbed_touch_raised;
સ્થિર પૂર્ણાંક xinput2_active_touch_ગણતરી;
#જો defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
સ્થિર bool xinput2_scrolling_supported;
સ્થિર bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
સ્થિર bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
સ્થિર પૂર્ણાંક xinput2_opcode;

સ્થિર Atom xinput2_rel_x_atom;
સ્થિર Atom xinput2_rel_y_atom;
સ્થિર Atom xinput2_abs_x_atom;
સ્થિર Atom xinput2_abs_y_atom;

// Pointer button remapping table
સ્થિર unsigned અક્ષર *xinput2_pointer_button_map;
સ્થિર પૂર્ણાંક xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક સંખ્યા_2;
    પૂર્ણાંક scroll_type;
    દ્વિગુણ prev_કિંમત;
    દ્વિગુણ increment;
    bool prev_કિંમત_valid;
} SDL_XInput2ScrollInfo;

પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક scroll_info_ગણતરી;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક સંખ્યા_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    દ્વિગુણ minval[2];
    દ્વિગુણ maxval[2];
    દ્વિગુણ prev_coords[2];
} SDL_XInput2RelativeDevice;

પ્રકારવ્યાખ્યા સંરચના SDL_XInput2DeviceInfo
{
    પૂર્ણાંક device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    સંરચના SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

સ્થિર SDL_XInput2DeviceInfo *xinput2_device_info;

સ્થિર શૂન્ય parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, અચલ XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    દ્વિગુણ processed_coords[2] = { 0.0, 0.0 };
    પૂર્ણાંક કિંમતો_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    અચલ bool use_raw_vals = mouse->આગત_Transform || !mouse->enable_relative_system_scale;

    માટે (પૂર્ણાંક i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        જો (!XIMaskIsSet(rawev->valuators.mask, i)) {
            ચાલુ;
        }

        માટે (પૂર્ણાંક j = 0; j < 2; ++j) {
            જો (rel_dev->સંખ્યા_2[j] == i) {
                અચલ દ્વિગુણ current_val = use_raw_vals ? rawev->raw_કિંમતો[કિંમતો_i] : rawev->valuators.કિંમતો[કિંમતો_i];

                જો (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } નહીંતર {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    જો (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                તોડો;
            }
        }

        ++કિંમતો_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    જો (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (દશાંશ)processed_coords[0], (દશાંશ)processed_coords[1]);
    }
}

સ્થિર પૂર્ણાંક query_xinput2_version(Display *display, પૂર્ણાંક major, પૂર્ણાંક minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    પાછા (major * 1000) + minor;
}

સ્થિર bool xinput2_version_atleast(અચલ પૂર્ણાંક version, અચલ પૂર્ણાંક wantmajor, અચલ પૂર્ણાંક wantminor)
{
    પાછા version >= ((wantmajor * 1000) + wantminor);
}

સ્થિર SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    અચલ SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    પાછા windowdata ? windowdata->window : ખાલી;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
સ્થિર શૂન્ય xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, અચલ XIDeviceEvent *xev)
{
    પૂર્ણાંક કિંમતો_i = 0;
    માટે (પૂર્ણાંક j = 0; j < xev->valuators.mask_len * 8; ++j) {
        જો (!XIMaskIsSet(xev->valuators.mask, j)) {
            ચાલુ;
        }

        માટે (પૂર્ણાંક k = 0; k < scroll_dev->scroll_info_ગણતરી; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            જો (info->સંખ્યા_2 == j) {
                અચલ દ્વિગુણ current_val = xev->valuators.કિંમતો[કિંમતો_i];
                અચલ દ્વિગુણ delta = (info->prev_કિંમત - current_val) / info->increment;
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
                જો (info->prev_કિંમત_valid && SDL_fabs(delta) < (દ્વિગુણ)SDL_MAX_SINT32 * 0.95) {
                    અચલ દ્વિગુણ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    અચલ દ્વિગુણ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (દશાંશ)-x, (દશાંશ)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_કિંમત = current_val;
                info->prev_કિંમત_valid = true;
            }
        }

        ++કિંમતો_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
સ્થિર શૂન્ય xinput2_normalize_touch_coordinates(SDL_Window *window, દ્વિગુણ in_x, દ્વિગુણ in_y, દશાંશ *out_x, દશાંશ *out_y)
{
    જો (window) {
        જો (window->w == 1) {
            *out_x = 0.5f;
        } નહીંતર {
            *out_x = (દશાંશ)in_x / (window->w - 1);
        }
        જો (window->h == 1) {
            *out_y = 0.5f;
        } નહીંતર {
            *out_y = (દશાંશ)in_y / (window->h - 1);
        }
    } નહીંતર {
        // couldn't find the window...
        *out_x = (દશાંશ)in_x;
        *out_y = (દશાંશ)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    પૂર્ણાંક version = 0;
    XIEventMask eventmask;
    unsigned અક્ષર mask[5] = { 0, 0, 0, 0, 0 };
    પૂર્ણાંક event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    જો (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        પાછા false;
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
    જો (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        પાછા false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    જો (!xinput2_version_atleast(version, 2, 0)) {
        પાછા false; // X server does not support the version we want at all.
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
    eventmask.mask_len = કદ(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    જો (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    જો (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_મૂળ_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = કદ(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_ચાવી_Press);
    XISetMask(mask, XI_ચાવી_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_મૂળ_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    પાછા true;
#નહીંતર
    પાછા false;
#endif
}

શૂન્ય X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    માટે (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = ખાલી; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = ખાલી;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = ખાલી;
    xinput2_pointer_button_map_size = 0;
#endif
}

શૂન્ય X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    જો (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = ખાલી;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, ખાલી, 0);
        જો (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, કદ(unsigned અક્ષર));
            જો (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } નહીંતર {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
સ્થિર શૂન્ય xinput2_remove_device_info(અચલ પૂર્ણાંક device_id)
{
    માટે (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ખાલી; devinfo; devinfo = devinfo->next) {
        જો (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ખાલી));
            જો (!prev) {
                xinput2_device_info = devinfo->next;
            } નહીંતર {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            પાછા;
        }
        prev = devinfo;
    }
}

સ્થિર શૂન્ય xinput2_reset_device_valuators(શૂન્ય)
{
    માટે (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        માટે (પૂર્ણાંક i = 0; i < devinfo->scroll.scroll_info_ગણતરી; ++i) {
            devinfo->scroll.scroll_info[i].prev_કિંમત_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

સ્થિર શૂન્ય xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, પૂર્ણાંક અંક_classes)
{
    જો (!devinfo) {
        પાછા;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    પૂર્ણાંક rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    પૂર્ણાંક allocated_scroll_info_ગણતરી = devinfo->scroll.scroll_info_ગણતરી;
    devinfo->scroll.scroll_info_ગણતરી = 0;
#endif

    માટે (પૂર્ણાંક i = 0; i < અંક_classes; ++i) {
        જો (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            અચલ XIValuatorClassInfo *v = (અચલ XIValuatorClassInfo *)classes[i];
            જો (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.સંખ્યા_2[0] = v->સંખ્યા_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                જો (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } નહીંતર જો (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } નહીંતર જો (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.સંખ્યા_2[1] = v->સંખ્યા_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                જો (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } નહીંતર જો (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        નહીંતર જો (classes[i]->type == XIScrollClass) {
            અચલ XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            જો (devinfo->scroll.scroll_info_ગણતરી == allocated_scroll_info_ગણતરી) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_ગણતરી + 2) * કદ(SDL_XInput2ScrollInfo));
                જો (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_ગણતરી = 0;
                    devinfo->scroll.scroll_info_ગણતરી = 0;
                    ચાલુ;
                }

                allocated_scroll_info_ગણતરી += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_ગણતરી];
            ++devinfo->scroll.scroll_info_ગણતરી;

            SDL_zerop(scroll_info);
            scroll_info->સંખ્યા_2 = s->સંખ્યા_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

સ્થિર SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(અચલ પૂર્ણાંક device_id)
{
    માટે (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ખાલી; devinfo; devinfo = devinfo->next) {
        જો (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ખાલી));
            જો (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            પાછા devinfo;
        }
        prev = devinfo;
    }

    પાછા ખાલી;
}

સ્થિર SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, અચલ પૂર્ણાંક device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    જો (devinfo) {
        પાછા devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, કદ(SDL_XInput2DeviceInfo));
    જો (!devinfo) {
        પાછા ખાલી;
    }

    પૂર્ણાંક i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    જો (!xidevinfo) {
        SDL_free(devinfo);
        પાછા ખાલી;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->અંક_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    પાછા devinfo;
}
#endif

શૂન્ય X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    જો (cookie->extension != xinput2_opcode) {
        પાછા;
    }

    પસંદગી (cookie->evtype) {
    સ્થિતિ XI_HierarchyChanged:
    {
        અચલ XIHierarchyEvent *hierev = (અચલ XIHierarchyEvent *)cookie->data;
        માટે (પૂર્ણાંક i = 0; i < hierev->અંક_info; ++i) {
            // pen stuff...
            જો ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } નહીંતર જો ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            જો (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } તોડો;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    સ્થિતિ XI_DeviceChanged:
    {
        અચલ XIDeviceChangedEvent *dcev = (અચલ XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        જો (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->અંક_classes);
        }
    } તોડો;

    સ્થિતિ XI_PropertyEvent:
    {
        અચલ XIPropertyEvent *proev = (અચલ XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        જો (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : ખાલી, proev->deviceid);
        }
    } તોડો;

    સ્થિતિ XI_RawMotion:
    {
        અચલ XIRawEvent *rawev = (અચલ XIRawEvent *)cookie->data;
        અચલ bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != ખાલી;

        videodata->global_mouse_changed = true;
        જો (is_pen) {
            તોડો; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        જો (!devinfo) {
            તોડો; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } તોડો;

    સ્થિતિ XI_ચાવી_Press:
    સ્થિતિ XI_ચાવી_Release:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        જો (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            તોડો;
        }

        જો (cookie->evtype == XI_ચાવી_Press) {
            xevent.type = ચાવી_Press;
        } નહીંતર {
            xevent.type = ચાવી_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.મૂળ = xev->મૂળ;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (પૂર્ણાંક)xev->event_x;
        xevent.xkey.y = (પૂર્ણાંક)xev->event_y;
        xevent.xkey.x_મૂળ = (પૂર્ણાંક)xev->મૂળ_x;
        xevent.xkey.y_મૂળ = (પૂર્ણાંક)xev->મૂળ_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_ચાવી_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#નહીંતર
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_ચાવી_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } તોડો;

    સ્થિતિ XI_RawButtonPress:
    સ્થિતિ XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    સ્થિતિ XI_RawTouchBegin:
    સ્થિતિ XI_RawTouchUpdate:
    સ્થિતિ XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } તોડો;

    સ્થિતિ XI_ButtonPress:
    સ્થિતિ XI_ButtonRelease:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        પૂર્ણાંક button = xev->detail;
        અચલ bool down = (cookie->evtype == XI_ButtonPress);
#જો defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#નહીંતર
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        જો (pen) {
            જો (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                તોડો;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            જો (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } નહીંતર {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } નહીંતર જો (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            પૂર્ણાંક x_ticks = 0, y_ticks = 0;

            જો (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                જો (SDL_GetMouseFocus() != windowdata->window) {
                    તોડો;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                જો (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            જો (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                તોડો;
            }

            જો (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (દશાંશ)xev->event_x, (દશાંશ)xev->event_y, xev->time, xev->serial);
            } નહીંતર {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } તોડો;

    સ્થિતિ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } તોડો;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    સ્થિતિ XI_Motion:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
#જો defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#નહીંતર
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        જો (pen) {
            જો (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                તોડો;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (દશાંશ) xev->event_x, (દશાંશ) xev->event_y);

            દશાંશ axes[SDL_PEN_AXIS_ગણતરી];
            X11_PenAxesFromValuators(pen, xev->valuators.કિંમતો, xev->valuators.mask, xev->valuators.mask_len, axes);

            માટે (પૂર્ણાંક i = 0; i < SDL_arraysize(axes); i++) {
                જો (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } નહીંતર જો (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            જો (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                જો (devinfo) {
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
            જો (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_ગણતરી && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                જો (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (દશાંશ)xev->event_x, (દશાંશ)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (દશાંશ)xev->event_x, (દશાંશ)xev->event_y);
                }
            }
        }
    } તોડો;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    સ્થિતિ XI_TouchBegin:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
        દશાંશ x, y;
        ++xinput2_active_touch_ગણતરી;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } તોડો;

    સ્થિતિ XI_TouchEnd:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
        દશાંશ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        જો (!--xinput2_active_touch_ગણતરી && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } તોડો;

    સ્થિતિ XI_TouchUpdate:
    {
        અચલ XIDeviceEvent *xev = (અચલ XIDeviceEvent *)cookie->data;
        દશાંશ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } તોડો;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    સ્થિતિ XI_GesturePinchBegin:
    સ્થિતિ XI_GesturePinchUpdate:
    સ્થિતિ XI_GesturePinchEnd:
    {
        અચલ XIGesturePinchEvent *xev = (અચલ XIGesturePinchEvent *)cookie->data;
        દશાંશ x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        જો (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } નહીંતર જો (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (દશાંશ)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } નહીંતર {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } તોડો;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

શૂન્ય X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_ગણતરી = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    અચલ bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_ગણતરી || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    પાછા ret;
#નહીંતર
    પાછા false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

શૂન્ય X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#જો defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned અક્ષર mask[5] = { 0, 0, 0, 0, 0 };

    જો (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        પાછા;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = કદ(mask);
    eventmask.mask = mask;

    જો (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    જો (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    જો (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(શૂન્ય)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    પાછા xinput2_initialized;
#નહીંતર
    પાછા false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    અચલ SDL_VideoData *data = _this->internal;

    જો (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned અક્ષર mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = કદ(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_ચાવી_Press);
        XISetMask(mask, XI_ચાવી_Release);
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

        જો (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_આગત, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    જો (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        પાછા true;
    }
    પાછા false;
}

શૂન્ય X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned અક્ષર mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    જો (!xinput2_multitouch_supported) {
        પાછા;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = કદ(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

શૂન્ય X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    જો (!xinput2_multitouch_supported) {
        પાછા;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

સ્થિર શૂન્ય AddDeviceID(Uint32 deviceID, Uint32 **list, પૂર્ણાંક *ગણતરી)
{
    પૂર્ણાંક new_ગણતરી = (*ગણતરી + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ગણતરી * કદ(*new_list));
    જો (!new_list) {
        // Oh well, we'll drop this one
        પાછા;
    }
    new_list[new_ગણતરી - 1] = deviceID;

    *ગણતરી = new_ગણતરી;
    *list = new_list;
}

સ્થિર bool HasDeviceID(Uint32 deviceID, અચલ Uint32 *list, પૂર્ણાંક ગણતરી)
{
    માટે (પૂર્ણાંક i = 0; i < ગણતરી; ++i) {
        જો (deviceID == list[i]) {
            પાછા true;
        }
    }
    પાછા false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
સ્થિર શૂન્ય AddDeviceID64(Uint64 deviceID, Uint64 **list, પૂર્ણાંક *ગણતરી)
{
    પૂર્ણાંક new_ગણતરી = (*ગણતરી + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_ગણતરી * કદ(*new_list));
    જો (!new_list) {
        // Oh well, we'll drop this one
        પાછા;
    }
    new_list[new_ગણતરી - 1] = deviceID;

    *ગણતરી = new_ગણતરી;
    *list = new_list;
}
#endif

સ્થિર bool HasDeviceID64(Uint64 deviceID, અચલ Uint64 *list, પૂર્ણાંક ગણતરી)
{
    માટે (પૂર્ણાંક i = 0; i < ગણતરી; ++i) {
        જો (deviceID == list[i]) {
            પાછા true;
        }
    }
    પાછા false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

શૂન્ય X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    પૂર્ણાંક ndevices;
    પૂર્ણાંક old_keyboard_ગણતરી = 0;
    SDL_KeyboardID *old_keyboards = ખાલી;
    પૂર્ણાંક new_keyboard_ગણતરી = 0;
    SDL_KeyboardID *new_keyboards = ખાલી;
    પૂર્ણાંક old_mouse_ગણતરી = 0;
    SDL_MouseID *old_mice = ખાલી;
    પૂર્ણાંક new_mouse_ગણતરી = 0;
    SDL_MouseID *new_mice = ખાલી;
    પૂર્ણાંક old_touch_ગણતરી = 0;
    Uint64 *old_touch_devices = ખાલી;
    પૂર્ણાંક new_touch_ગણતરી = 0;
    Uint64 *new_touch_devices = ખાલી;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ગણતરી);
    old_mice = SDL_GetMice(&old_mouse_ગણતરી);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_ગણતરી);

    માટે (પૂર્ણાંક i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        પસંદગી (dev->use) {
        સ્થિતિ XIMasterKeyboard:
        સ્થિતિ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_ગણતરી);
                જો (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ગણતરી)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            તોડો;
        સ્થિતિ XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        સ્થિતિ XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_ગણતરી);
                જો (!HasDeviceID(mouseID, old_mice, old_mouse_ગણતરી)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            તોડો;
        મૂળભૂત:
            તોડો;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        જો (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->અંક_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        માટે (પૂર્ણાંક j = 0; j < dev->અંક_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            જો (class->type != XITouchClass) {
                ચાલુ;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_ગણતરી);
            જો (!HasDeviceID64(touchID, old_touch_devices, old_touch_ગણતરી)) {
                જો (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } નહીંતર { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    માટે (પૂર્ણાંક i = old_keyboard_ગણતરી; i--;) {
        જો (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ગણતરી)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    માટે (પૂર્ણાંક i = old_mouse_ગણતરી; i--;) {
        જો (!HasDeviceID(old_mice[i], new_mice, new_mouse_ગણતરી)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    માટે (પૂર્ણાંક i = old_touch_ગણતરી; i--;) {
        જો (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_ગણતરી)) {
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
