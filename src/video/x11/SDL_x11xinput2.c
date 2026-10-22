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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11pen.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_pen_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

#define MAX_AXIS 16

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
स्थिर bool xinput2_initialized;
स्थिर bool xinput2_grabbed_touch_raised;
स्थिर पूर्णाङ्क xinput2_active_touch_गणनम्;
#सचे defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
स्थिर bool xinput2_scrolling_supported;
स्थिर bool xinput2_multitouch_supported;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
स्थिर bool xinput2_gesture_supported;
#endif

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
स्थिर पूर्णाङ्क xinput2_opcode;

स्थिर Atom xinput2_rel_x_atom;
स्थिर Atom xinput2_rel_y_atom;
स्थिर Atom xinput2_abs_x_atom;
स्थिर Atom xinput2_abs_y_atom;

// Pointer button remapping table
स्थिर unsigned वर्ण *xinput2_pointer_button_map;
स्थिर पूर्णाङ्क xinput2_pointer_button_map_size;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
प्रकारनिर्देश संरचना
{
    पूर्णाङ्क सङ्ख्या_2;
    पूर्णाङ्क scroll_type;
    द्विगुण prev_मानम्;
    द्विगुण increment;
    bool prev_मानम्_valid;
} SDL_XInput2ScrollInfo;

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क scroll_info_गणनम्;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#endif

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क सङ्ख्या_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    द्विगुण minval[2];
    द्विगुण maxval[2];
    द्विगुण prev_coords[2];
} SDL_XInput2RelativeDevice;

प्रकारनिर्देश संरचना SDL_XInput2DeviceInfo
{
    पूर्णाङ्क device_id;
    SDL_XInput2RelativeDevice relative;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#endif
    संरचना SDL_XInput2DeviceInfo *next;
} SDL_XInput2DeviceInfo;

स्थिर SDL_XInput2DeviceInfo *xinput2_device_info;

स्थिर शून्य parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ध्रुव XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    द्विगुण processed_coords[2] = { 0.0, 0.0 };
    पूर्णाङ्क मानानि_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ध्रुव bool use_raw_vals = mouse->निवेशः_Transform || !mouse->enable_relative_system_scale;

    अत्थाय (पूर्णाङ्क i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        सचे (!XIMaskIsSet(rawev->valuators.mask, i)) {
            अनुवर्त;
        }

        अत्थाय (पूर्णाङ्क j = 0; j < 2; ++j) {
            सचे (rel_dev->सङ्ख्या_2[j] == i) {
                ध्रुव द्विगुण current_val = use_raw_vals ? rawev->raw_मानानि[मानानि_i] : rawev->valuators.मानानि[मानानि_i];

                सचे (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } अञ्ञथा {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    सचे (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++found;

                भङ्ग;
            }
        }

        ++मानानि_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    सचे (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (भिन्न)processed_coords[0], (भिन्न)processed_coords[1]);
    }
}

स्थिर पूर्णाङ्क query_xinput2_version(Display *display, पूर्णाङ्क major, पूर्णाङ्क minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    पटिनिवत्त (major * 1000) + minor;
}

स्थिर bool xinput2_version_atleast(ध्रुव पूर्णाङ्क version, ध्रुव पूर्णाङ्क wantmajor, ध्रुव पूर्णाङ्क wantminor)
{
    पटिनिवत्त version >= ((wantmajor * 1000) + wantminor);
}

स्थिर SDL_Window *xinput2_get_sdlwindow(SDL_VideoData *videodata, Window window)
{
    ध्रुव SDL_WindowData *windowdata = X11_FindWindow(videodata, window);
    पटिनिवत्त windowdata ? windowdata->window : रिक्त;
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
स्थिर शून्य xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ध्रुव XIDeviceEvent *xev)
{
    पूर्णाङ्क मानानि_i = 0;
    अत्थाय (पूर्णाङ्क j = 0; j < xev->valuators.mask_len * 8; ++j) {
        सचे (!XIMaskIsSet(xev->valuators.mask, j)) {
            अनुवर्त;
        }

        अत्थाय (पूर्णाङ्क k = 0; k < scroll_dev->scroll_info_गणनम्; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            सचे (info->सङ्ख्या_2 == j) {
                ध्रुव द्विगुण current_val = xev->valuators.मानानि[मानानि_i];
                ध्रुव द्विगुण delta = (info->prev_मानम् - current_val) / info->increment;
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
                सचे (info->prev_मानम्_valid && SDL_fabs(delta) < (द्विगुण)SDL_MAX_SINT32 * 0.95) {
                    ध्रुव द्विगुण x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ध्रुव द्विगुण y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (भिन्न)-x, (भिन्न)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->prev_मानम् = current_val;
                info->prev_मानम्_valid = true;
            }
        }

        ++मानानि_i;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
स्थिर शून्य xinput2_normalize_touch_coordinates(SDL_Window *window, द्विगुण in_x, द्विगुण in_y, भिन्न *out_x, भिन्न *out_y)
{
    सचे (window) {
        सचे (window->w == 1) {
            *out_x = 0.5f;
        } अञ्ञथा {
            *out_x = (भिन्न)in_x / (window->w - 1);
        }
        सचे (window->h == 1) {
            *out_y = 0.5f;
        } अञ्ञथा {
            *out_y = (भिन्न)in_y / (window->h - 1);
        }
    } अञ्ञथा {
        // couldn't find the window...
        *out_x = (भिन्न)in_x;
        *out_y = (भिन्न)in_y;
    }
}
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;

    पूर्णाङ्क version = 0;
    XIEventMask eventmask;
    unsigned वर्ण mask[5] = { 0, 0, 0, 0, 0 };
    पूर्णाङ्क event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    सचे (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        पटिनिवत्त false;
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
    सचे (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(data->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        पटिनिवत्त false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(data->display, 2, 4);
    सचे (!xinput2_version_atleast(version, 2, 0)) {
        पटिनिवत्त false; // X server does not support the version we want at all.
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
    eventmask.mask_len = परिमाण(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    सचे (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    सचे (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#endif

    X11_XISelectEvents(data->display, Default_मूलम्_Window(data->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = परिमाण(mask);
    eventmask.mask = mask;

#ifndef USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_कुञ्चिका_Press);
    XISetMask(mask, XI_कुञ्चिका_Release);
#endif

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(data->display, Default_मूलम्_Window(data->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    पटिनिवत्त true;
#अञ्ञथा
    पटिनिवत्त false;
#endif
}

शून्य X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    अत्थाय (SDL_XInput2DeviceInfo *i = xinput2_device_info, *next = रिक्त; i; i = next) {
        next = i->next;
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#endif
        SDL_free(i);
    }
    xinput2_device_info = रिक्त;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = रिक्त;
    xinput2_pointer_button_map_size = 0;
#endif
}

शून्य X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    सचे (X11_Xinput2IsInitialized()) {
        SDL_VideoData *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = रिक्त;
        xinput2_pointer_button_map_size = 0;

        xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, रिक्त, 0);
        सचे (xinput2_pointer_button_map_size) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_size, परिमाण(unsigned वर्ण));
            सचे (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_size = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_size);
            } अञ्ञथा {
                xinput2_pointer_button_map_size = 0;
            }
        }
    }
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
स्थिर शून्य xinput2_remove_device_info(ध्रुव पूर्णाङ्क device_id)
{
    अत्थाय (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = रिक्त; devinfo; devinfo = devinfo->next) {
        सचे (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == रिक्त));
            सचे (!prev) {
                xinput2_device_info = devinfo->next;
            } अञ्ञथा {
                prev->next = devinfo->next;
            }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#endif
            SDL_free(devinfo);
            पटिनिवत्त;
        }
        prev = devinfo;
    }
}

स्थिर शून्य xinput2_reset_device_valuators(शून्य)
{
    अत्थाय (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->next) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        अत्थाय (पूर्णाङ्क i = 0; i < devinfo->scroll.scroll_info_गणनम्; ++i) {
            devinfo->scroll.scroll_info[i].prev_मानम्_valid = false;
        }
#endif
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

स्थिर शून्य xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, पूर्णाङ्क अङ्कः_classes)
{
    सचे (!devinfo) {
        पटिनिवत्त;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    पूर्णाङ्क rel_axis_index = 0;

    SDL_zero(devinfo->relative);

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    पूर्णाङ्क allocated_scroll_info_गणनम् = devinfo->scroll.scroll_info_गणनम्;
    devinfo->scroll.scroll_info_गणनम् = 0;
#endif

    अत्थाय (पूर्णाङ्क i = 0; i < अङ्कः_classes; ++i) {
        सचे (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ध्रुव XIValuatorClassInfo *v = (ध्रुव XIValuatorClassInfo *)classes[i];
            सचे (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_index == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.सङ्ख्या_2[0] = v->सङ्ख्या_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                सचे (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } अञ्ञथा सचे (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } अञ्ञथा सचे (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_index == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.सङ्ख्या_2[1] = v->सङ्ख्या_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                सचे (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } अञ्ञथा सचे (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_index;
        }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        अञ्ञथा सचे (classes[i]->type == XIScrollClass) {
            ध्रुव XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            सचे (devinfo->scroll.scroll_info_गणनम् == allocated_scroll_info_गणनम्) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_गणनम् + 2) * परिमाण(SDL_XInput2ScrollInfo));
                सचे (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_गणनम् = 0;
                    devinfo->scroll.scroll_info_गणनम् = 0;
                    अनुवर्त;
                }

                allocated_scroll_info_गणनम् += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_गणनम्];
            ++devinfo->scroll.scroll_info_गणनम्;

            SDL_zerop(scroll_info);
            scroll_info->सङ्ख्या_2 = s->सङ्ख्या_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

स्थिर SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ध्रुव पूर्णाङ्क device_id)
{
    अत्थाय (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = रिक्त; devinfo; devinfo = devinfo->next) {
        सचे (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == रिक्त));
            सचे (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->next = devinfo->next;
                devinfo->next = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            पटिनिवत्त devinfo;
        }
        prev = devinfo;
    }

    पटिनिवत्त रिक्त;
}

स्थिर SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_VideoData *videodata, ध्रुव पूर्णाङ्क device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    सचे (devinfo) {
        पटिनिवत्त devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, परिमाण(SDL_XInput2DeviceInfo));
    सचे (!devinfo) {
        पटिनिवत्त रिक्त;
    }

    पूर्णाङ्क i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    सचे (!xidevinfo) {
        SDL_free(devinfo);
        पटिनिवत्त रिक्त;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->अङ्कः_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->next = xinput2_device_info;
    xinput2_device_info = devinfo;

    पटिनिवत्त devinfo;
}
#endif

शून्य X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *videodata = _this->internal;

    सचे (cookie->extension != xinput2_opcode) {
        पटिनिवत्त;
    }

    विकल्प (cookie->evtype) {
    पक्ष XI_HierarchyChanged:
    {
        ध्रुव XIHierarchyEvent *hierev = (ध्रुव XIHierarchyEvent *)cookie->data;
        अत्थाय (पूर्णाङ्क i = 0; i < hierev->अङ्कः_info; ++i) {
            // pen stuff...
            सचे ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } अञ्ञथा सचे ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            सचे (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } भङ्ग;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    पक्ष XI_DeviceChanged:
    {
        ध्रुव XIDeviceChangedEvent *dcev = (ध्रुव XIDeviceChangedEvent *)cookie->data;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        सचे (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->अङ्कः_classes);
        }
    } भङ्ग;

    पक्ष XI_PropertyEvent:
    {
        ध्रुव XIPropertyEvent *proev = (ध्रुव XIPropertyEvent *)cookie->data;
        // Handle pen proximity enter/leave
        सचे (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : रिक्त, proev->deviceid);
        }
    } भङ्ग;

    पक्ष XI_RawMotion:
    {
        ध्रुव XIRawEvent *rawev = (ध्रुव XIRawEvent *)cookie->data;
        ध्रुव bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != रिक्त;

        videodata->global_mouse_changed = true;
        सचे (is_pen) {
            भङ्ग; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        सचे (!devinfo) {
            भङ्ग; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } भङ्ग;

    पक्ष XI_कुञ्चिका_Press:
    पक्ष XI_कुञ्चिका_Release:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;

#ifdef USE_XINPUT2_KEYBOARD
        SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        सचे (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            भङ्ग;
        }

        सचे (cookie->evtype == XI_कुञ्चिका_Press) {
            xevent.type = कुञ्चिका_Press;
        } अञ्ञथा {
            xevent.type = कुञ्चिका_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.मूलम् = xev->मूलम्;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.time = xev->time;
        xevent.xkey.x = (पूर्णाङ्क)xev->event_x;
        xevent.xkey.y = (पूर्णाङ्क)xev->event_y;
        xevent.xkey.x_मूलम् = (पूर्णाङ्क)xev->मूलम्_x;
        xevent.xkey.y_मूलम् = (पूर्णाङ्क)xev->मूलम्_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_कुञ्चिका_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#अञ्ञथा
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_कुञ्चिका_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#endif
    } भङ्ग;

    पक्ष XI_RawButtonPress:
    पक्ष XI_RawButtonRelease:
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    पक्ष XI_RawTouchBegin:
    पक्ष XI_RawTouchUpdate:
    पक्ष XI_RawTouchEnd:
#endif
    {
        videodata->global_mouse_changed = true;
    } भङ्ग;

    पक्ष XI_ButtonPress:
    पक्ष XI_ButtonRelease:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        पूर्णाङ्क button = xev->detail;
        ध्रुव bool down = (cookie->evtype == XI_ButtonPress);
#सचे defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अञ्ञथा
        bool pointer_emulated = false;
#endif

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        सचे (pen) {
            सचे (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                भङ्ग;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            सचे (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } अञ्ञथा {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } अञ्ञथा सचे (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_WindowData *windowdata = X11_FindWindow(videodata, xev->event);
            पूर्णाङ्क x_ticks = 0, y_ticks = 0;

            सचे (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                सचे (SDL_GetMouseFocus() != windowdata->window) {
                    भङ्ग;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                सचे (button <= xinput2_pointer_button_map_size) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            सचे (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                भङ्ग;
            }

            सचे (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (भिन्न)xev->event_x, (भिन्न)xev->event_y, xev->time, xev->serial);
            } अञ्ञथा {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->time);
            }
        }
    } भङ्ग;

    पक्ष XI_Enter:
    {
        xinput2_reset_device_valuators();
    } भङ्ग;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    पक्ष XI_Motion:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
#सचे defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अञ्ञथा
        bool pointer_emulated = false;
#endif

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        सचे (pen) {
            सचे (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                भङ्ग;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (भिन्न) xev->event_x, (भिन्न) xev->event_y);

            भिन्न axes[SDL_PEN_AXIS_गणनम्];
            X11_PenAxesFromValuators(pen, xev->valuators.मानानि, xev->valuators.mask, xev->valuators.mask_len, axes);

            अत्थाय (पूर्णाङ्क i = 0; i < SDL_arraysize(axes); i++) {
                सचे (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } अञ्ञथा सचे (!pointer_emulated) {
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            सचे (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                सचे (devinfo) {
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
            सचे (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_गणनम् && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                सचे (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (भिन्न)xev->event_x, (भिन्न)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xev->event_x, (भिन्न)xev->event_y);
                }
            }
        }
    } भङ्ग;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    पक्ष XI_TouchBegin:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
        भिन्न x, y;
        ++xinput2_active_touch_गणनम्;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } भङ्ग;

    पक्ष XI_TouchEnd:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
        भिन्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        सचे (!--xinput2_active_touch_गणनम् && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } भङ्ग;

    पक्ष XI_TouchUpdate:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->data;
        भिन्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } भङ्ग;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    पक्ष XI_GesturePinchBegin:
    पक्ष XI_GesturePinchUpdate:
    पक्ष XI_GesturePinchEnd:
    {
        ध्रुव XIGesturePinchEvent *xev = (ध्रुव XIGesturePinchEvent *)cookie->data;
        भिन्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        सचे (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } अञ्ञथा सचे (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (भिन्न)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } अञ्ञथा {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } भङ्ग;

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

शून्य X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_गणनम् = 0;
#endif
}

bool X11_Xinput2HandlesMotionForWindow(SDL_WindowData *window_data)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ध्रुव bool ret = window_data->xinput2_mouse_enabled &&
                     (!window_data->mouse_grabbed || xinput2_active_touch_गणनम् || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    पटिनिवत्त ret;
#अञ्ञथा
    पटिनिवत्त false;
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2
}

शून्य X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#सचे defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *window_data = window->internal;
    XIEventMask eventmask;
    unsigned वर्ण mask[5] = { 0, 0, 0, 0, 0 };

    सचे (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        पटिनिवत्त;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = परिमाण(mask);
    eventmask.mask = mask;

    सचे (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    सचे (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    सचे (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#endif

    X11_XISelectEvents(data->display, window_data->xwindow, &eventmask, 1);
#endif
}

bool X11_Xinput2IsInitialized(शून्य)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    पटिनिवत्त xinput2_initialized;
#अञ्ञथा
    पटिनिवत्त false;
#endif
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *windowdata = window->internal;

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ध्रुव SDL_VideoData *data = _this->internal;

    सचे (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        unsigned वर्ण mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = परिमाण(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ifdef USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_कुञ्चिका_Press);
        XISetMask(mask, XI_कुञ्चिका_Release);
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

        सचे (X11_XISelectEvents(data->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_निवेशः, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#endif

    सचे (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

शून्य X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    unsigned वर्ण mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    सचे (!xinput2_multitouch_supported) {
        पटिनिवत्त;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = परिमाण(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, data->xwindow, True, &eventmask, 1, &mods);
#endif
}

शून्य X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;

    XIGrabModifiers mods;

    सचे (!xinput2_multitouch_supported) {
        पटिनिवत्त;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, data->xwindow, 1, &mods);
#endif
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

स्थिर शून्य AddDeviceID(Uint32 deviceID, Uint32 **list, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क new_गणनम् = (*गणनम् + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_गणनम् * परिमाण(*new_list));
    सचे (!new_list) {
        // Oh well, we'll drop this one
        पटिनिवत्त;
    }
    new_list[new_गणनम् - 1] = deviceID;

    *गणनम् = new_गणनम्;
    *list = new_list;
}

स्थिर bool HasDeviceID(Uint32 deviceID, ध्रुव Uint32 *list, पूर्णाङ्क गणनम्)
{
    अत्थाय (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        सचे (deviceID == list[i]) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
स्थिर शून्य AddDeviceID64(Uint64 deviceID, Uint64 **list, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क new_गणनम् = (*गणनम् + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_गणनम् * परिमाण(*new_list));
    सचे (!new_list) {
        // Oh well, we'll drop this one
        पटिनिवत्त;
    }
    new_list[new_गणनम् - 1] = deviceID;

    *गणनम् = new_गणनम्;
    *list = new_list;
}
#endif

स्थिर bool HasDeviceID64(Uint64 deviceID, ध्रुव Uint64 *list, पूर्णाङ्क गणनम्)
{
    अत्थाय (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        सचे (deviceID == list[i]) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

शून्य X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_VideoData *data = _this->internal;
    XIDeviceInfo *info;
    पूर्णाङ्क ndevices;
    पूर्णाङ्क old_keyboard_गणनम् = 0;
    SDL_KeyboardID *old_keyboards = रिक्त;
    पूर्णाङ्क new_keyboard_गणनम् = 0;
    SDL_KeyboardID *new_keyboards = रिक्त;
    पूर्णाङ्क old_mouse_गणनम् = 0;
    SDL_MouseID *old_mice = रिक्त;
    पूर्णाङ्क new_mouse_गणनम् = 0;
    SDL_MouseID *new_mice = रिक्त;
    पूर्णाङ्क old_touch_गणनम् = 0;
    Uint64 *old_touch_devices = रिक्त;
    पूर्णाङ्क new_touch_गणनम् = 0;
    Uint64 *new_touch_devices = रिक्त;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(data->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_गणनम्);
    old_mice = SDL_GetMice(&old_mouse_गणनम्);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_गणनम्);

    अत्थाय (पूर्णाङ्क i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        विकल्प (dev->use) {
        पक्ष XIMasterKeyboard:
        पक्ष XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_गणनम्);
                सचे (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_गणनम्)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            भङ्ग;
        पक्ष XIMasterPointer:
            data->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        पक्ष XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_गणनम्);
                सचे (!HasDeviceID(mouseID, old_mice, old_mouse_गणनम्)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        सचे (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->अङ्कः_classes);
        }

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        अत्थाय (पूर्णाङ्क j = 0; j < dev->अङ्कः_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            सचे (class->type != XITouchClass) {
                अनुवर्त;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_गणनम्);
            सचे (!HasDeviceID64(touchID, old_touch_devices, old_touch_गणनम्)) {
                सचे (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } अञ्ञथा { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#endif // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    अत्थाय (पूर्णाङ्क i = old_keyboard_गणनम्; i--;) {
        सचे (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_गणनम्)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    अत्थाय (पूर्णाङ्क i = old_mouse_गणनम्; i--;) {
        सचे (!HasDeviceID(old_mice[i], new_mice, new_mouse_गणनम्)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    अत्थाय (पूर्णाङ्क i = old_touch_गणनम्; i--;) {
        सचे (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_गणनम्)) {
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
