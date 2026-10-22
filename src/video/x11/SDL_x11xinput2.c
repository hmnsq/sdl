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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11pen.h"
#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11xinput2.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_pen_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
സ്ഥിതം bool xinput2_initialized;
സ്ഥിതം bool xinput2_grabbed_touch_raised;
സ്ഥിതം പൂർണ്ണസംഖ്യ xinput2_active_touch_എണ്ണം;
#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
സ്ഥിതം bool xinput2_scrolling_supported;
സ്ഥിതം bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
സ്ഥിതം bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
സ്ഥിതം പൂർണ്ണസംഖ്യ xinput2_opcode;

സ്ഥിതം Atom xinput2_rel_x_atom;
സ്ഥിതം Atom xinput2_rel_y_atom;
സ്ഥിതം Atom xinput2_abs_x_atom;
സ്ഥിതം Atom xinput2_abs_y_atom;

// Pointer button remapping table
സ്ഥിതം unsigned അക്ഷരം *xinput2_pointer_button_map;
സ്ഥിതം പൂർണ്ണസംഖ്യ xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ സംഖ്യ_2;
    പൂർണ്ണസംഖ്യ scroll_type;
    ഇരട്ട prev_മൂല്യം;
    ഇരട്ട increment;
    bool prev_മൂല്യം_valid;
} SDL_XInput2ScrollInfo;

തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ scroll_info_എണ്ണം;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ സംഖ്യ_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ഇരട്ട minval[2];
    ഇരട്ട maxval[2];
    ഇരട്ട prev_coords[2];
} SDL_XInput2RelativeDevice;

തരനിർവചനം ഘടന SDL_XInput2DeviceInfo
{
    പൂർണ്ണസംഖ്യ device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    ഘടന SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

സ്ഥിതം SDL_XInput2DeviceInfo *xinput2_device_info;

സ്ഥിതം ശൂന്യം parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, സ്ഥിരം XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ഇരട്ട processed_coords[2] = { 0.0, 0.0 };
    പൂർണ്ണസംഖ്യ മൂല്യങ്ങൾ_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    സ്ഥിരം bool use_raw_vals = mouse->നിവേശം_Transform || !mouse->enable_relative_system_scale;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        എങ്കിൽ (!XIMaskIsSet(rawev->valuators.mask, i)) {
            തുടരുക;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < 2; ++j) {
            എങ്കിൽ (rel_dev->സംഖ്യ_2[j] == i) {
                സ്ഥിരം ഇരട്ട current_val = use_raw_vals ? rawev->raw_മൂല്യങ്ങൾ[മൂല്യങ്ങൾ_i] : rawev->valuators.മൂല്യങ്ങൾ[മൂല്യങ്ങൾ_i];

                എങ്കിൽ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } അല്ലെങ്കിൽ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    എങ്കിൽ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                നിർത്തുക;
            }
        }

        ++മൂല്യങ്ങൾ_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    എങ്കിൽ (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ദശാംശം)processed_coords[0], (ദശാംശം)processed_coords[1]);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ query_xinput2_version(Display *display, പൂർണ്ണസംഖ്യ major, പൂർണ്ണസംഖ്യ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    തിരികെ (major * 1000) + minor;
}

സ്ഥിതം bool xinput2_version_atleast(സ്ഥിരം പൂർണ്ണസംഖ്യ version, സ്ഥിരം പൂർണ്ണസംഖ്യ wantmajor, സ്ഥിരം പൂർണ്ണസംഖ്യ wantminor)
{
    തിരികെ version >= ((wantmajor * 1000) + wantminor);
}

സ്ഥിതം SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    സ്ഥിരം SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    തിരികെ windowdata ? windowdata->window : ശൂന്യ;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
സ്ഥിതം ശൂന്യം xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, സ്ഥിരം XIDeviceEvent *xev)
{
    പൂർണ്ണസംഖ്യ മൂല്യങ്ങൾ_i = 0;
    വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < xev->valuators.mask_len * 8; ++j) {
        എങ്കിൽ (!XIMaskIsSet(xev->valuators.mask, j)) {
            തുടരുക;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ k = 0; k < scroll_dev->scroll_info_എണ്ണം; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            എങ്കിൽ (info->സംഖ്യ_2 == j) {
                സ്ഥിരം ഇരട്ട current_val = xev->valuators.മൂല്യങ്ങൾ[മൂല്യങ്ങൾ_i];
                സ്ഥിരം ഇരട്ട delta = (info->prev_മൂല്യം - current_val) / info->increment;
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
                എങ്കിൽ (info->prev_മൂല്യം_valid && SDL_fabs(delta) < (ഇരട്ട)SDL_MAX_SINT32 * 0.95) {
                    സ്ഥിരം ഇരട്ട x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    സ്ഥിരം ഇരട്ട y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (ദശാംശം)-x, (ദശാംശം)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_മൂല്യം = current_val;
                info->prev_മൂല്യം_valid = true;
            }
        }

        ++മൂല്യങ്ങൾ_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
സ്ഥിതം ശൂന്യം xinput2_normalize_touch_coordinates(SDL_Window *window, ഇരട്ട in_x, ഇരട്ട in_y, ദശാംശം *out_x, ദശാംശം *out_y)
{
    എങ്കിൽ (window) {
        എങ്കിൽ (window->w == 1) {
            *out_x = 0.5f;
        } അല്ലെങ്കിൽ {
            *out_x = (ദശാംശം)in_x / (window->w - 1);
        }
        എങ്കിൽ (window->h == 1) {
            *out_y = 0.5f;
        } അല്ലെങ്കിൽ {
            *out_y = (ദശാംശം)in_y / (window->h - 1);
        }
    } അല്ലെങ്കിൽ {
        // couldn't find the window...
        *out_x = (ദശാംശം)in_x;
        *out_y = (ദശാംശം)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    പൂർണ്ണസംഖ്യ version = 0;
    XIEventMask eventmask;
    unsigned അക്ഷരം mask[5] = { 0, 0, 0, 0, 0 };
    പൂർണ്ണസംഖ്യ event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    എങ്കിൽ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        തിരികെ false;
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
    എങ്കിൽ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        തിരികെ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    എങ്കിൽ (!xinput2_version_atleast(version, 2, 0)) {
        തിരികെ false; // X server does not support the version we want at all.
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
    eventmask.mask_len = വലുപ്പം(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    എങ്കിൽ (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    എങ്കിൽ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_വേര്_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = വലുപ്പം(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_താക്കോൽ_Press);
    XISetMask(mask, XI_താക്കോൽ_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_വേര്_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    തിരികെ true;
#അല്ലെങ്കിൽ
    തിരികെ false;
#endif
}

ശൂന്യം X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    വേണ്ടി (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = ശൂന്യ; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = ശൂന്യ;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = ശൂന്യ;
    xinput2_pointer_button_map_size = 0;
#endif
}

ശൂന്യം X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    എങ്കിൽ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = ശൂന്യ;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, ശൂന്യ, 0);
        എങ്കിൽ (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, വലുപ്പം(unsigned അക്ഷരം));
            എങ്കിൽ (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } അല്ലെങ്കിൽ {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
സ്ഥിതം ശൂന്യം xinput2_remove_device_info(സ്ഥിരം പൂർണ്ണസംഖ്യ device_id)
{
    വേണ്ടി (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ശൂന്യ; devinfo; devinfo = devinfo->next) {
        എങ്കിൽ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ശൂന്യ));
            എങ്കിൽ (!prev) {
                xinput2_device_info = devinfo->next;
            } അല്ലെങ്കിൽ {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            തിരികെ;
        }
        prev = devinfo;
    }
}

സ്ഥിതം ശൂന്യം xinput2_reset_device_valuators(ശൂന്യം)
{
    വേണ്ടി (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < devinfo->scroll.scroll_info_എണ്ണം; ++i) {
            devinfo->scroll.scroll_info[i].prev_മൂല്യം_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

സ്ഥിതം ശൂന്യം xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, പൂർണ്ണസംഖ്യ അക്കം_classes)
{
    എങ്കിൽ (!devinfo) {
        തിരികെ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    പൂർണ്ണസംഖ്യ rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    പൂർണ്ണസംഖ്യ allocated_scroll_info_എണ്ണം = devinfo->scroll.scroll_info_എണ്ണം;
    devinfo->scroll.scroll_info_എണ്ണം = 0;
#endif

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_classes; ++i) {
        എങ്കിൽ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            സ്ഥിരം XIValuatorClassInfo *v = (സ്ഥിരം XIValuatorClassInfo *)classes[i];
            എങ്കിൽ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.സംഖ്യ_2[0] = v->സംഖ്യ_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                എങ്കിൽ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } അല്ലെങ്കിൽ എങ്കിൽ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.സംഖ്യ_2[1] = v->സംഖ്യ_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                എങ്കിൽ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } അല്ലെങ്കിൽ എങ്കിൽ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        അല്ലെങ്കിൽ എങ്കിൽ (classes[i]->type == XIScrollClass) {
            സ്ഥിരം XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            എങ്കിൽ (devinfo->scroll.scroll_info_എണ്ണം == allocated_scroll_info_എണ്ണം) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_എണ്ണം + 2) * വലുപ്പം(SDL_XInput2ScrollInfo));
                എങ്കിൽ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_എണ്ണം = 0;
                    devinfo->scroll.scroll_info_എണ്ണം = 0;
                    തുടരുക;
                }

                allocated_scroll_info_എണ്ണം += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_എണ്ണം];
            ++devinfo->scroll.scroll_info_എണ്ണം;

            SDL_zerop(scroll_info);
            scroll_info->സംഖ്യ_2 = s->സംഖ്യ_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

സ്ഥിതം SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(സ്ഥിരം പൂർണ്ണസംഖ്യ device_id)
{
    വേണ്ടി (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ശൂന്യ; devinfo; devinfo = devinfo->next) {
        എങ്കിൽ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ശൂന്യ));
            എങ്കിൽ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            തിരികെ devinfo;
        }
        prev = devinfo;
    }

    തിരികെ ശൂന്യ;
}

സ്ഥിതം SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, സ്ഥിരം പൂർണ്ണസംഖ്യ device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    എങ്കിൽ (devinfo) {
        തിരികെ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, വലുപ്പം(SDL_XInput2DeviceInfo));
    എങ്കിൽ (!devinfo) {
        തിരികെ ശൂന്യ;
    }

    പൂർണ്ണസംഖ്യ i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    എങ്കിൽ (!xidevinfo) {
        SDL_free(devinfo);
        തിരികെ ശൂന്യ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->അക്കം_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    തിരികെ devinfo;
}
#endif

ശൂന്യം X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    എങ്കിൽ (cookie->extension != xinput2_opcode) {
        തിരികെ;
    }

    തിരഞ്ഞെടുപ്പ് (cookie->evtype) {
    അവസ്ഥ XI_HierarchyChanged:
    {
        സ്ഥിരം XIHierarchyEvent *hierev = (സ്ഥിരം XIHierarchyEvent *)cookie->data;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < hierev->അക്കം_info; ++i) {
            // pen stuff...
            എങ്കിൽ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } അല്ലെങ്കിൽ എങ്കിൽ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            എങ്കിൽ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } നിർത്തുക;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    അവസ്ഥ XI_DeviceChanged:
    {
        സ്ഥിരം XIDeviceChangedEvent *dcev = (സ്ഥിരം XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        എങ്കിൽ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->അക്കം_classes);
        }
    } നിർത്തുക;

    അവസ്ഥ XI_PropertyEvent:
    {
        സ്ഥിരം XIPropertyEvent *proev = (സ്ഥിരം XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        എങ്കിൽ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : ശൂന്യ, proev->deviceid);
        }
    } നിർത്തുക;

    അവസ്ഥ XI_RawMotion:
    {
        സ്ഥിരം XIRawEvent *rawev = (സ്ഥിരം XIRawEvent *)cookie->data;
        സ്ഥിരം bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != ശൂന്യ;

        videodata->global_mouse_changed = true;
        എങ്കിൽ (is_pen) {
            നിർത്തുക; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        എങ്കിൽ (!devinfo) {
            നിർത്തുക; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } നിർത്തുക;

    അവസ്ഥ XI_താക്കോൽ_Press:
    അവസ്ഥ XI_താക്കോൽ_Release:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        എങ്കിൽ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            നിർത്തുക;
        }

        എങ്കിൽ (cookie->evtype == XI_താക്കോൽ_Press) {
            xevent.type = താക്കോൽ_Press;
        } അല്ലെങ്കിൽ {
            xevent.type = താക്കോൽ_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.വേര് = xev->വേര്;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (പൂർണ്ണസംഖ്യ)xev->event_x;
        xevent.xkey.y = (പൂർണ്ണസംഖ്യ)xev->event_y;
        xevent.xkey.x_വേര് = (പൂർണ്ണസംഖ്യ)xev->വേര്_x;
        xevent.xkey.y_വേര് = (പൂർണ്ണസംഖ്യ)xev->വേര്_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_താക്കോൽ_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#അല്ലെങ്കിൽ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_താക്കോൽ_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } നിർത്തുക;

    അവസ്ഥ XI_RawButtonPress:
    അവസ്ഥ XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    അവസ്ഥ XI_RawTouchBegin:
    അവസ്ഥ XI_RawTouchUpdate:
    അവസ്ഥ XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } നിർത്തുക;

    അവസ്ഥ XI_ButtonPress:
    അവസ്ഥ XI_ButtonRelease:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        പൂർണ്ണസംഖ്യ button = xev->detail;
        സ്ഥിരം bool down = (cookie->evtype == XI_ButtonPress);
#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#അല്ലെങ്കിൽ
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        എങ്കിൽ (pen) {
            എങ്കിൽ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                നിർത്തുക;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            എങ്കിൽ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } അല്ലെങ്കിൽ {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            പൂർണ്ണസംഖ്യ x_ticks = 0, y_ticks = 0;

            എങ്കിൽ (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                എങ്കിൽ (SDL_GetMouseFocus() != windowdata->window) {
                    നിർത്തുക;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                എങ്കിൽ (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            എങ്കിൽ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                നിർത്തുക;
            }

            എങ്കിൽ (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ദശാംശം)xev->event_x, (ദശാംശം)xev->event_y, xev->time, xev->serial);
            } അല്ലെങ്കിൽ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } നിർത്തുക;

    അവസ്ഥ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } നിർത്തുക;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    അവസ്ഥ XI_Motion:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#അല്ലെങ്കിൽ
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        എങ്കിൽ (pen) {
            എങ്കിൽ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                നിർത്തുക;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (ദശാംശം) xev->event_x, (ദശാംശം) xev->event_y);

            ദശാംശം axes[SDL_PEN_AXIS_എണ്ണം];
            X11_PenAxesFromValuators(pen, xev->valuators.മൂല്യങ്ങൾ, xev->valuators.mask, xev->valuators.mask_len, axes);

            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(axes); i++) {
                എങ്കിൽ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            എങ്കിൽ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                എങ്കിൽ (devinfo) {
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
            എങ്കിൽ (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_എണ്ണം && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                എങ്കിൽ (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (ദശാംശം)xev->event_x, (ദശാംശം)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (ദശാംശം)xev->event_x, (ദശാംശം)xev->event_y);
                }
            }
        }
    } നിർത്തുക;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    അവസ്ഥ XI_TouchBegin:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
        ദശാംശം x, y;
        ++xinput2_active_touch_എണ്ണം;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } നിർത്തുക;

    അവസ്ഥ XI_TouchEnd:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
        ദശാംശം x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        എങ്കിൽ (!--xinput2_active_touch_എണ്ണം && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } നിർത്തുക;

    അവസ്ഥ XI_TouchUpdate:
    {
        സ്ഥിരം XIDeviceEvent *xev = (സ്ഥിരം XIDeviceEvent *)cookie->data;
        ദശാംശം x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } നിർത്തുക;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    അവസ്ഥ XI_GesturePinchBegin:
    അവസ്ഥ XI_GesturePinchUpdate:
    അവസ്ഥ XI_GesturePinchEnd:
    {
        സ്ഥിരം XIGesturePinchEvent *xev = (സ്ഥിരം XIGesturePinchEvent *)cookie->data;
        ദശാംശം x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        എങ്കിൽ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } അല്ലെങ്കിൽ എങ്കിൽ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (ദശാംശം)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } അല്ലെങ്കിൽ {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } നിർത്തുക;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ശൂന്യം X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_എണ്ണം = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    സ്ഥിരം bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_എണ്ണം || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    തിരികെ ret;
#അല്ലെങ്കിൽ
    തിരികെ false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ശൂന്യം X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned അക്ഷരം mask[5] = { 0, 0, 0, 0, 0 };

    എങ്കിൽ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        തിരികെ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = വലുപ്പം(mask);
    eventmask.mask = mask;

    എങ്കിൽ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    എങ്കിൽ (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    എങ്കിൽ (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(ശൂന്യം)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    തിരികെ xinput2_initialized;
#അല്ലെങ്കിൽ
    തിരികെ false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    സ്ഥിരം SDL_VideoData *data = _this->internal;

    എങ്കിൽ (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned അക്ഷരം mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = വലുപ്പം(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_താക്കോൽ_Press);
        XISetMask(mask, XI_താക്കോൽ_Release);
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

        എങ്കിൽ (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_നിവേശം, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    എങ്കിൽ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        തിരികെ true;
    }
    തിരികെ false;
}

ശൂന്യം X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned അക്ഷരം mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    എങ്കിൽ (!xinput2_multitouch_supported) {
        തിരികെ;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = വലുപ്പം(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

ശൂന്യം X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    എങ്കിൽ (!xinput2_multitouch_supported) {
        തിരികെ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

സ്ഥിതം ശൂന്യം AddDeviceID(Uint32 deviceID, Uint32 **list, പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    പൂർണ്ണസംഖ്യ new_എണ്ണം = (*എണ്ണം + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_എണ്ണം * വലുപ്പം(*new_list));
    എങ്കിൽ (!new_list) {
        // Oh well, we'll drop this one
        തിരികെ;
    }
    new_list[new_എണ്ണം - 1] = deviceID;

    *എണ്ണം = new_എണ്ണം;
    *list = new_list;
}

സ്ഥിതം bool HasDeviceID(Uint32 deviceID, സ്ഥിരം Uint32 *list, പൂർണ്ണസംഖ്യ എണ്ണം)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം; ++i) {
        എങ്കിൽ (deviceID == list[i]) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
സ്ഥിതം ശൂന്യം AddDeviceID64(Uint64 deviceID, Uint64 **list, പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    പൂർണ്ണസംഖ്യ new_എണ്ണം = (*എണ്ണം + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_എണ്ണം * വലുപ്പം(*new_list));
    എങ്കിൽ (!new_list) {
        // Oh well, we'll drop this one
        തിരികെ;
    }
    new_list[new_എണ്ണം - 1] = deviceID;

    *എണ്ണം = new_എണ്ണം;
    *list = new_list;
}
#endif

സ്ഥിതം bool HasDeviceID64(Uint64 deviceID, സ്ഥിരം Uint64 *list, പൂർണ്ണസംഖ്യ എണ്ണം)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം; ++i) {
        എങ്കിൽ (deviceID == list[i]) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

ശൂന്യം X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    പൂർണ്ണസംഖ്യ ndevices;
    പൂർണ്ണസംഖ്യ old_keyboard_എണ്ണം = 0;
    SDL_KeyboardID *old_keyboards = ശൂന്യ;
    പൂർണ്ണസംഖ്യ new_keyboard_എണ്ണം = 0;
    SDL_KeyboardID *new_keyboards = ശൂന്യ;
    പൂർണ്ണസംഖ്യ old_mouse_എണ്ണം = 0;
    SDL_MouseID *old_mice = ശൂന്യ;
    പൂർണ്ണസംഖ്യ new_mouse_എണ്ണം = 0;
    SDL_MouseID *new_mice = ശൂന്യ;
    പൂർണ്ണസംഖ്യ old_touch_എണ്ണം = 0;
    Uint64 *old_touch_devices = ശൂന്യ;
    പൂർണ്ണസംഖ്യ new_touch_എണ്ണം = 0;
    Uint64 *new_touch_devices = ശൂന്യ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_എണ്ണം);
    old_mice = SDL_GetMice(&old_mouse_എണ്ണം);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_എണ്ണം);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        തിരഞ്ഞെടുപ്പ് (dev->use) {
        അവസ്ഥ XIMasterKeyboard:
        അവസ്ഥ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_എണ്ണം);
                എങ്കിൽ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_എണ്ണം)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            നിർത്തുക;
        അവസ്ഥ XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        അവസ്ഥ XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_എണ്ണം);
                എങ്കിൽ (!HasDeviceID(mouseID, old_mice, old_mouse_എണ്ണം)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        എങ്കിൽ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->അക്കം_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < dev->അക്കം_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            എങ്കിൽ (class->type != XITouchClass) {
                തുടരുക;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_എണ്ണം);
            എങ്കിൽ (!HasDeviceID64(touchID, old_touch_devices, old_touch_എണ്ണം)) {
                എങ്കിൽ (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } അല്ലെങ്കിൽ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = old_keyboard_എണ്ണം; i--;) {
        എങ്കിൽ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_എണ്ണം)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = old_mouse_എണ്ണം; i--;) {
        എങ്കിൽ (!HasDeviceID(old_mice[i], new_mice, new_mouse_എണ്ണം)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = old_touch_എണ്ണം; i--;) {
        എങ്കിൽ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_എണ്ണം)) {
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
