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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11pen.h"
#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xinput2.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_pen_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"

#నిర్వచించు MAX_AXIS 16

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
స్థిర bool xinput2_initialized;
స్థిర bool xinput2_grabbed_touch_raised;
స్థిర పూర్ణాంకం xinput2_చురుకైన_touch_లెక్క;
#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
స్థిర bool xinput2_scrolling_supported;
స్థిర bool xinput2_multitouch_supported;
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
స్థిర bool xinput2_gesture_supported;
#అయితే_ముగింపు

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
స్థిర పూర్ణాంకం xinput2_opcode;

స్థిర Atom xinput2_rel_x_atom;
స్థిర Atom xinput2_rel_y_atom;
స్థిర Atom xinput2_abs_x_atom;
స్థిర Atom xinput2_abs_y_atom;

// Pointer button remapping table
స్థిర గుర్తులేని అక్షరం *xinput2_సూచిక_button_map;
స్థిర పూర్ణాంకం xinput2_సూచిక_button_map_కొలత;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం సంఖ్య_2;
    పూర్ణాంకం scroll_type;
    ద్విగుణ prev_విలువ;
    ద్విగుణ increment;
    bool prev_విలువ_valid;
} SDL_XInput2ScrollInfo;

రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం scroll_info_లెక్క;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం సంఖ్య_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ద్విగుణ minval[2];
    ద్విగుణ maxval[2];
    ద్విగుణ prev_coords[2];
} SDL_XInput2RelativeDevice;

రకనిర్వచనం నిర్మాణం SDL_XInput2DeviceInfo
{
    పూర్ణాంకం device_id;
    SDL_XInput2RelativeDevice relative;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#అయితే_ముగింపు
    నిర్మాణం SDL_XInput2DeviceInfo *తదుపరి;
} SDL_XInput2DeviceInfo;

స్థిర SDL_XInput2DeviceInfo *xinput2_device_info;

స్థిర శూన్య parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, స్థిరరాశి XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ద్విగుణ processed_coords[2] = { 0.0, 0.0 };
    పూర్ణాంకం విలువలు_i = 0, దొరికింది = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    స్థిరరాశి bool use_raw_vals = mouse->ఆదానం_Transform || !mouse->enable_relative_system_scale;

    కొరకు (పూర్ణాంకం i = 0; i < rawev->valuators.ముసుగు_len * 8 && దొరికింది < 2; ++i) {
        ఒకవేళ (!XIMask_Is_సమితి(rawev->valuators.ముసుగు, i)) {
            కొనసాగు;
        }

        కొరకు (పూర్ణాంకం j = 0; j < 2; ++j) {
            ఒకవేళ (rel_dev->సంఖ్య_2[j] == i) {
                స్థిరరాశి ద్విగుణ current_val = use_raw_vals ? rawev->raw_విలువలు[విలువలు_i] : rawev->valuators.విలువలు[విలువలు_i];

                ఒకవేళ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } లేకపోతే {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ఒకవేళ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++దొరికింది;

                ఆపు;
            }
        }

        ++విలువలు_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ఒకవేళ (mouse->relative_బహుళకం && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->సమయం, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (దశాంశం)processed_coords[0], (దశాంశం)processed_coords[1]);
    }
}

స్థిర పూర్ణాంకం query_xinput2_సంస్కరణ(Display *display, పూర్ణాంకం major, పూర్ణాంకం minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_సంస్కరణ(display, &major, &minor);
    తిరిగి (major * 1000) + minor;
}

స్థిర bool xinput2_సంస్కరణ_atleast(స్థిరరాశి పూర్ణాంకం సంస్కరణ, స్థిరరాశి పూర్ణాంకం wantmajor, స్థిరరాశి పూర్ణాంకం wantminor)
{
    తిరిగి సంస్కరణ >= ((wantmajor * 1000) + wantminor);
}

స్థిర SDL_కిటికీ *xinput2_get_sdlwindow(SDL_Video_దత్తాంశం *videodata, కిటికీ_2 కిటికీ)
{
    స్థిరరాశి SDL_కిటికీ_దత్తాంశం *windowdata = X11_కనుగొను_కిటికీ(videodata, కిటికీ);
    తిరిగి windowdata ? windowdata->కిటికీ : ఖాళీ;
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
స్థిర శూన్య xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, స్థిరరాశి XIDeviceEvent *xev)
{
    పూర్ణాంకం విలువలు_i = 0;
    కొరకు (పూర్ణాంకం j = 0; j < xev->valuators.ముసుగు_len * 8; ++j) {
        ఒకవేళ (!XIMask_Is_సమితి(xev->valuators.ముసుగు, j)) {
            కొనసాగు;
        }

        కొరకు (పూర్ణాంకం k = 0; k < scroll_dev->scroll_info_లెక్క; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ఒకవేళ (info->సంఖ్య_2 == j) {
                స్థిరరాశి ద్విగుణ current_val = xev->valuators.విలువలు[విలువలు_i];
                స్థిరరాశి ద్విగుణ delta = (info->prev_విలువ - current_val) / info->increment;
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
                ఒకవేళ (info->prev_విలువ_valid && SDL_fabs(delta) < (ద్విగుణ)SDL_MAX_SINT32 * 0.95) {
                    స్థిరరాశి ద్విగుణ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    స్థిరరాశి ద్విగుణ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->సమయం, mouse->focus, (SDL_MouseID)xev->sourceid, (దశాంశం)-x, (దశాంశం)y, SDL_MOUSEWHEEL_సాధారణ);
                }
                info->prev_విలువ = current_val;
                info->prev_విలువ_valid = true;
            }
        }

        ++విలువలు_i;
    }
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
స్థిర శూన్య xinput2_normalize_touch_coordinates(SDL_కిటికీ *కిటికీ, ద్విగుణ లోపల_x, ద్విగుణ లోపల_y, దశాంశం *బహిర్గతం_x, దశాంశం *బహిర్గతం_y)
{
    ఒకవేళ (కిటికీ) {
        ఒకవేళ (కిటికీ->w == 1) {
            *బహిర్గతం_x = 0.5f;
        } లేకపోతే {
            *బహిర్గతం_x = (దశాంశం)లోపల_x / (కిటికీ->w - 1);
        }
        ఒకవేళ (కిటికీ->h == 1) {
            *బహిర్గతం_y = 0.5f;
        } లేకపోతే {
            *బహిర్గతం_y = (దశాంశం)లోపల_y / (కిటికీ->h - 1);
        }
    } లేకపోతే {
        // couldn't find the window...
        *బహిర్గతం_x = (దశాంశం)లోపల_x;
        *బహిర్గతం_y = (దశాంశం)లోపల_y;
    }
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    పూర్ణాంకం సంస్కరణ = 0;
    XIEvent_ముసుగు eventmask;
    గుర్తులేని అక్షరం ముసుగు[5] = { 0, 0, 0, 0, 0 };
    పూర్ణాంకం event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ఒకవేళ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        తిరిగి false;
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
    ఒకవేళ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(దత్తాంశం->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        తిరిగి false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    సంస్కరణ = query_xinput2_సంస్కరణ(దత్తాంశం->display, 2, 4);
    ఒకవేళ (!xinput2_సంస్కరణ_atleast(సంస్కరణ, 2, 0)) {
        తిరిగి false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_సంస్కరణ_atleast(సంస్కరణ, 2, 1);
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_సంస్కరణ_atleast(సంస్కరణ, 2, 2);
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_సంస్కరణ_atleast(సంస్కరణ, 2, 4);
#అయితే_ముగింపు

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(దత్తాంశం->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(దత్తాంశం->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(దత్తాంశం->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(దత్తాంశం->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(ముసుగు);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ముసుగు_len = పరిమాణం(ముసుగు);
    eventmask.ముసుగు = ముసుగు;

    XISet_ముసుగు(ముసుగు, XI_RawMotion);
    XISet_ముసుగు(ముసుగు, XI_RawButtonPress);
    XISet_ముసుగు(ముసుగు, XI_RawButtonRelease);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ఒకవేళ (xinput2_scrolling_supported) {
        XISet_ముసుగు(ముసుగు, XI_Motion);
    }
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ఒకవేళ (xinput2_multitouch_supported) {
        XISet_ముసుగు(ముసుగు, XI_RawTouchBegin);
        XISet_ముసుగు(ముసుగు, XI_RawTouchUpdate);
        XISet_ముసుగు(ముసుగు, XI_Raw_Touch_చివర);
    }
#అయితే_ముగింపు

    X11_XISelectEvents(దత్తాంశం->display, Default_మూలం_కిటికీ(దత్తాంశం->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(ముసుగు);
    eventmask.deviceid = XIAllDevices;
    eventmask.ముసుగు_len = పరిమాణం(ముసుగు);
    eventmask.ముసుగు = ముసుగు;

#నిర్వచితం_కాకపోతే USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_ముసుగు(ముసుగు, XI_కీలకం_Press);
    XISet_ముసుగు(ముసుగు, XI_కీలకం_Release);
#అయితే_ముగింపు

    XISet_ముసుగు(ముసుగు, XI_Hierarchy_మారింది);
    X11_XISelectEvents(దత్తాంశం->display, Default_మూలం_కిటికీ(దత్తాంశం->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_సూచిక_Mapping(_this);

    తిరిగి true;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు
}

శూన్య X11_QuitXinput2(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    కొరకు (SDL_XInput2DeviceInfo *i = xinput2_device_info, *తదుపరి = ఖాళీ; i; i = తదుపరి) {
        తదుపరి = i->తదుపరి;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#అయితే_ముగింపు
        SDL_free(i);
    }
    xinput2_device_info = ఖాళీ;

    SDL_free(xinput2_సూచిక_button_map);
    xinput2_సూచిక_button_map = ఖాళీ;
    xinput2_సూచిక_button_map_కొలత = 0;
#అయితే_ముగింపు
}

శూన్య X11_Xinput2_Update_సూచిక_Mapping(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    ఒకవేళ (X11_Xinput2IsInitialized()) {
        SDL_Video_దత్తాంశం *vid = _this->అంతర్గత;

        SDL_free(xinput2_సూచిక_button_map);
        xinput2_సూచిక_button_map = ఖాళీ;
        xinput2_సూచిక_button_map_కొలత = 0;

        xinput2_సూచిక_button_map_కొలత = X11_XGet_సూచిక_Mapping(vid->display, ఖాళీ, 0);
        ఒకవేళ (xinput2_సూచిక_button_map_కొలత) {
            xinput2_సూచిక_button_map = SDL_calloc(xinput2_సూచిక_button_map_కొలత, పరిమాణం(గుర్తులేని అక్షరం));
            ఒకవేళ (xinput2_సూచిక_button_map) {
                xinput2_సూచిక_button_map_కొలత = X11_XGet_సూచిక_Mapping(vid->display, xinput2_సూచిక_button_map, xinput2_సూచిక_button_map_కొలత);
            } లేకపోతే {
                xinput2_సూచిక_button_map_కొలత = 0;
            }
        }
    }
#అయితే_ముగింపు
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
స్థిర శూన్య xinput2_remove_device_info(స్థిరరాశి పూర్ణాంకం device_id)
{
    కొరకు (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ఖాళీ; devinfo; devinfo = devinfo->తదుపరి) {
        ఒకవేళ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ఖాళీ));
            ఒకవేళ (!prev) {
                xinput2_device_info = devinfo->తదుపరి;
            } లేకపోతే {
                prev->తదుపరి = devinfo->తదుపరి;
            }
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#అయితే_ముగింపు
            SDL_free(devinfo);
            తిరిగి;
        }
        prev = devinfo;
    }
}

స్థిర శూన్య xinput2_reset_device_valuators(శూన్య)
{
    కొరకు (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->తదుపరి) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        కొరకు (పూర్ణాంకం i = 0; i < devinfo->scroll.scroll_info_లెక్క; ++i) {
            devinfo->scroll.scroll_info[i].prev_విలువ_valid = false;
        }
#అయితే_ముగింపు
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

స్థిర శూన్య xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, పూర్ణాంకం అంకె_classes)
{
    ఒకవేళ (!devinfo) {
        తిరిగి;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    పూర్ణాంకం rel_axis_సూచీ = 0;

    SDL_zero(devinfo->relative);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    పూర్ణాంకం allocated_scroll_info_లెక్క = devinfo->scroll.scroll_info_లెక్క;
    devinfo->scroll.scroll_info_లెక్క = 0;
#అయితే_ముగింపు

    కొరకు (పూర్ణాంకం i = 0; i < అంకె_classes; ++i) {
        ఒకవేళ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            స్థిరరాశి XIValuatorClassInfo *v = (స్థిరరాశి XIValuatorClassInfo *)classes[i];
            ఒకవేళ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_సూచీ == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.సంఖ్య_2[0] = v->సంఖ్య_2;
                devinfo->relative.relative[0] = (v->బహుళకం == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ఒకవేళ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } లేకపోతే ఒకవేళ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } లేకపోతే ఒకవేళ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_సూచీ == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.సంఖ్య_2[1] = v->సంఖ్య_2;
                devinfo->relative.relative[1] = (v->బహుళకం == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ఒకవేళ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } లేకపోతే ఒకవేళ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_సూచీ;
        }
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        లేకపోతే ఒకవేళ (classes[i]->type == XIScrollClass) {
            స్థిరరాశి XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ఒకవేళ (devinfo->scroll.scroll_info_లెక్క == allocated_scroll_info_లెక్క) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_లెక్క + 2) * పరిమాణం(SDL_XInput2ScrollInfo));
                ఒకవేళ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_లెక్క = 0;
                    devinfo->scroll.scroll_info_లెక్క = 0;
                    కొనసాగు;
                }

                allocated_scroll_info_లెక్క += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_లెక్క];
            ++devinfo->scroll.scroll_info_లెక్క;

            SDL_zerop(scroll_info);
            scroll_info->సంఖ్య_2 = s->సంఖ్య_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

స్థిర SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(స్థిరరాశి పూర్ణాంకం device_id)
{
    కొరకు (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ఖాళీ; devinfo; devinfo = devinfo->తదుపరి) {
        ఒకవేళ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ఖాళీ));
            ఒకవేళ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->తదుపరి = devinfo->తదుపరి;
                devinfo->తదుపరి = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            తిరిగి devinfo;
        }
        prev = devinfo;
    }

    తిరిగి ఖాళీ;
}

స్థిర SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_దత్తాంశం *videodata, స్థిరరాశి పూర్ణాంకం device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ఒకవేళ (devinfo) {
        తిరిగి devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, పరిమాణం(SDL_XInput2DeviceInfo));
    ఒకవేళ (!devinfo) {
        తిరిగి ఖాళీ;
    }

    పూర్ణాంకం i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ఒకవేళ (!xidevinfo) {
        SDL_free(devinfo);
        తిరిగి ఖాళీ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->అంకె_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->తదుపరి = xinput2_device_info;
    xinput2_device_info = devinfo;

    తిరిగి devinfo;
}
#అయితే_ముగింపు

శూన్య X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    ఒకవేళ (cookie->extension != xinput2_opcode) {
        తిరిగి;
    }

    ఎంపిక (cookie->evtype) {
    స్థితి XI_Hierarchy_మారింది:
    {
        స్థిరరాశి XIHierarchyEvent *hierev = (స్థిరరాశి XIHierarchyEvent *)cookie->దత్తాంశం;
        కొరకు (పూర్ణాంకం i = 0; i < hierev->అంకె_info; ++i) {
            // pen stuff...
            ఒకవేళ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } లేకపోతే ఒకవేళ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_కూడు_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ఒకవేళ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_మారింది = true;
    } ఆపు;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    స్థితి XI_Device_మారింది:
    {
        స్థిరరాశి XIDevice_మారింది_Event *dcev = (స్థిరరాశి XIDevice_మారింది_Event *)cookie->దత్తాంశం;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ఒకవేళ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->అంకె_classes);
        }
    } ఆపు;

    స్థితి XI_PropertyEvent:
    {
        స్థిరరాశి XIPropertyEvent *proev = (స్థిరరాశి XIPropertyEvent *)cookie->దత్తాంశం;
        // Handle pen proximity enter/leave
        ఒకవేళ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
            SDL_కిటికీ_దత్తాంశం *windowdata = X11_కనుగొను_కిటికీ(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->కిటికీ : ఖాళీ, proev->deviceid);
        }
    } ఆపు;

    స్థితి XI_RawMotion:
    {
        స్థిరరాశి XIRawEvent *rawev = (స్థిరరాశి XIRawEvent *)cookie->దత్తాంశం;
        స్థిరరాశి bool is_pen = X11_కనుగొను_Pen_By_Device_ID(rawev->sourceid) != ఖాళీ;

        videodata->global_mouse_మారింది = true;
        ఒకవేళ (is_pen) {
            ఆపు; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ఒకవేళ (!devinfo) {
            ఆపు; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ఆపు;

    స్థితి XI_కీలకం_Press:
    స్థితి XI_కీలకం_Release:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;

#నిర్వచితమైతే USE_XINPUT2_KEYBOARD
        SDL_కిటికీ_దత్తాంశం *windowdata = X11_కనుగొను_కిటికీ(videodata, xev->event);
        XEvent xevent;

        ఒకవేళ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ఆపు;
        }

        ఒకవేళ (cookie->evtype == XI_కీలకం_Press) {
            xevent.type = కీలకం_Press;
        } లేకపోతే {
            xevent.type = కీలకం_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.కిటికీ = xev->event;
        xevent.xkey.మూలం = xev->మూలం;
        xevent.xkey.subwindow = xev->బిడ్డ;
        xevent.xkey.సమయం = xev->సమయం;
        xevent.xkey.x = (పూర్ణాంకం)xev->event_x;
        xevent.xkey.y = (పూర్ణాంకం)xev->event_y;
        xevent.xkey.x_మూలం = (పూర్ణాంకం)xev->మూలం_x;
        xevent.xkey.y_మూలం = (పూర్ణాంకం)xev->మూలం_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_కీలకం_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#లేకపోతే
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_చివరి_కీలకం_serial = xev->serial;
        videodata->xinput_చివరి_keyboard_device = xev->sourceid;
#అయితే_ముగింపు
    } ఆపు;

    స్థితి XI_RawButtonPress:
    స్థితి XI_RawButtonRelease:
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    స్థితి XI_RawTouchBegin:
    స్థితి XI_RawTouchUpdate:
    స్థితి XI_Raw_Touch_చివర:
#అయితే_ముగింపు
    {
        videodata->global_mouse_మారింది = true;
    } ఆపు;

    స్థితి XI_ButtonPress:
    స్థితి XI_ButtonRelease:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
        X11_PenHandle *pen = X11_కనుగొను_Pen_By_Device_ID(xev->sourceid);
        పూర్ణాంకం button = xev->detail;
        స్థిరరాశి bool కిందికి = (cookie->evtype == XI_ButtonPress);
#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool సూచిక_emulated = (xev->flags & XIPointerEmulated) != 0;
#లేకపోతే
        bool సూచిక_emulated = false;
#అయితే_ముగింపు

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_చివరి_button_serial = xev->serial;

        ఒకవేళ (pen) {
            ఒకవేళ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ఆపు;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
            ఒకవేళ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, కిటికీ, pen->is_eraser, కిందికి);
            } లేకపోతే {
                SDL_SendPenButton(0, pen->pen, కిటికీ, button - 1, కిందికి);
            }
        } లేకపోతే ఒకవేళ (!సూచిక_emulated) {
            // Otherwise assume a regular mouse
            SDL_కిటికీ_దత్తాంశం *windowdata = X11_కనుగొను_కిటికీ(videodata, xev->event);
            పూర్ణాంకం x_ticks = 0, y_ticks = 0;

            ఒకవేళ (xev->deviceid != videodata->xinput_master_సూచిక_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ఒకవేళ (SDL_GetMouseFocus() != windowdata->కిటికీ) {
                    ఆపు;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ఒకవేళ (button <= xinput2_సూచిక_button_map_కొలత) {
                    button = xinput2_సూచిక_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ఒకవేళ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ఆపు;
            }

            ఒకవేళ (కిందికి) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (దశాంశం)xev->event_x, (దశాంశం)xev->event_y, xev->సమయం, xev->serial);
            } లేకపోతే {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->సమయం);
            }
        }
    } ఆపు;

    స్థితి XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ఆపు;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    స్థితి XI_Motion:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool సూచిక_emulated = (xev->flags & XIPointerEmulated) != 0;
#లేకపోతే
        bool సూచిక_emulated = false;
#అయితే_ముగింపు

        videodata->global_mouse_మారింది = true;

        X11_PenHandle *pen = X11_కనుగొను_Pen_By_Device_ID(xev->sourceid);

        ఒకవేళ (pen) {
            ఒకవేళ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ఆపు;
            }

            SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, కిటికీ, (దశాంశం) xev->event_x, (దశాంశం) xev->event_y);

            దశాంశం axes[SDL_PEN_AXIS_లెక్క];
            X11_PenAxesFromValuators(pen, xev->valuators.విలువలు, xev->valuators.ముసుగు, xev->valuators.ముసుగు_len, axes);

            కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(axes); i++) {
                ఒకవేళ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, కిటికీ, (SDL_PenAxis) i, axes[i]);
                }
            }
        } లేకపోతే ఒకవేళ (!సూచిక_emulated) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ఒకవేళ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ఒకవేళ (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#అయితే_ముగింపు

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
            ఒకవేళ (కిటికీ && (xev->deviceid == videodata->xinput_master_సూచిక_device || (xinput2_చురుకైన_touch_లెక్క && కిటికీ->అంతర్గత->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ఒకవేళ (!mouse->relative_బహుళకం) {
                        X11_Process_తగిలింది_Test(_this, కిటికీ->అంతర్గత, (దశాంశం)xev->event_x, (దశాంశం)xev->event_y, false);
                        SDL_SendMouseMotion(0, కిటికీ, SDL_GLOBAL_MOUSE_ID, false, (దశాంశం)xev->event_x, (దశాంశం)xev->event_y);
                }
            }
        }
    } ఆపు;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    స్థితి XI_TouchBegin:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
        దశాంశం x, y;
        ++xinput2_చురుకైన_touch_లెక్క;
        SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(కిటికీ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, కిటికీ, SDL_EVENT_FINGER_కిందికి, x, y, 1.0);
    } ఆపు;

    స్థితి XI_Touch_చివర:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
        దశాంశం x, y;
        SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
        ఒకవేళ (!--xinput2_చురుకైన_touch_లెక్క && కిటికీ && కిటికీ->అంతర్గత->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(కిటికీ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, కిటికీ, SDL_EVENT_FINGER_పైకి, x, y, 1.0);
    } ఆపు;

    స్థితి XI_TouchUpdate:
    {
        స్థిరరాశి XIDeviceEvent *xev = (స్థిరరాశి XIDeviceEvent *)cookie->దత్తాంశం;
        దశాంశం x, y;
        SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(కిటికీ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, కిటికీ, x, y, 1.0);
    } ఆపు;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    స్థితి XI_GesturePinchBegin:
    స్థితి XI_GesturePinchUpdate:
    స్థితి XI_Gesture_Pinch_చివర:
    {
        స్థిరరాశి XIGesturePinchEvent *xev = (స్థిరరాశి XIGesturePinchEvent *)cookie->దత్తాంశం;
        దశాంశం x, y;
        SDL_కిటికీ *కిటికీ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(కిటికీ, xev->event_x, xev->event_y, &x, &y);

        ఒకవేళ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, కిటికీ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } లేకపోతే ఒకవేళ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, కిటికీ, (దశాంశం)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } లేకపోతే {
            SDL_SendPinch(SDL_EVENT_PINCH_చివర, 0, కిటికీ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ఆపు;

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2
}

శూన్య X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_చురుకైన_touch_లెక్క = 0;
#అయితే_ముగింపు
}

bool X11_Xinput2_Handles_Motion_For_కిటికీ(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    స్థిరరాశి bool ret = కిటికీ_దత్తాంశం_2->xinput2_mouse_enabled &&
                     (!కిటికీ_దత్తాంశం_2->mouse_grabbed || xinput2_చురుకైన_touch_లెక్క || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    తిరిగి ret;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2
}

శూన్య X11_Xinput2Select(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;
    XIEvent_ముసుగు eventmask;
    గుర్తులేని అక్షరం ముసుగు[5] = { 0, 0, 0, 0, 0 };

    ఒకవేళ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        తిరిగి;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ముసుగు_len = పరిమాణం(ముసుగు);
    eventmask.ముసుగు = ముసుగు;

    ఒకవేళ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_ముసుగు(ముసుగు, XI_Enter);
    }

    ఒకవేళ (xinput2_multitouch_supported) {
        XISet_ముసుగు(ముసుగు, XI_TouchBegin);
        XISet_ముసుగు(ముసుగు, XI_TouchUpdate);
        XISet_ముసుగు(ముసుగు, XI_Touch_చివర);
        XISet_ముసుగు(ముసుగు, XI_Motion);
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ఒకవేళ (xinput2_gesture_supported) {
        XISet_ముసుగు(ముసుగు, XI_GesturePinchBegin);
        XISet_ముసుగు(ముసుగు, XI_GesturePinchUpdate);
        XISet_ముసుగు(ముసుగు, XI_Gesture_Pinch_చివర);
    }
#అయితే_ముగింపు

    X11_XISelectEvents(దత్తాంశం->display, కిటికీ_దత్తాంశం_2->xwindow, &eventmask, 1);
#అయితే_ముగింపు
}

bool X11_Xinput2IsInitialized(శూన్య)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    తిరిగి xinput2_initialized;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    స్థిరరాశి SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (X11_Xinput2IsInitialized()) {
        XIEvent_ముసుగు eventmask;
        గుర్తులేని అక్షరం ముసుగు[4] = { 0, 0, 0, 0 };

        eventmask.ముసుగు_len = పరిమాణం(ముసుగు);
        eventmask.ముసుగు = ముసుగు;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#నిర్వచితమైతే USE_XINPUT2_KEYBOARD
        XISet_ముసుగు(ముసుగు, XI_కీలకం_Press);
        XISet_ముసుగు(ముసుగు, XI_కీలకం_Release);
        windowdata->xinput2_keyboard_enabled = true;
#అయితే_ముగింపు

        XISet_ముసుగు(ముసుగు, XI_ButtonPress);
        XISet_ముసుగు(ముసుగు, XI_ButtonRelease);
        XISet_ముసుగు(ముసుగు, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_ముసుగు(ముసుగు, XI_Enter);
        XISet_ముసుగు(ముసుగు, XI_Leave);

        // Hotplugging:
        XISet_ముసుగు(ముసుగు, XI_Device_మారింది);
        XISet_ముసుగు(ముసుగు, XI_Hierarchy_మారింది);
        XISet_ముసుగు(ముసుగు, XI_PropertyEvent); // E.g., when swapping tablet pens

        ఒకవేళ (X11_XISelectEvents(దత్తాంశం->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ఆదానం, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        తిరిగి true;
    }
    తిరిగి false;
}

శూన్య X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;

    గుర్తులేని అక్షరం ముసుగు[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_ముసుగు eventmask;

    ఒకవేళ (!xinput2_multitouch_supported) {
        తిరిగి;
    }

    mods.modifiers = XIAnyModifier;
    mods.స్థితి_2 = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.ముసుగు_len = పరిమాణం(ముసుగు);
    eventmask.ముసుగు = ముసుగు;

    XISet_ముసుగు(eventmask.ముసుగు, XI_TouchBegin);
    XISet_ముసుగు(eventmask.ముసుగు, XI_TouchUpdate);
    XISet_ముసుగు(eventmask.ముసుగు, XI_Touch_చివర);
    XISet_ముసుగు(eventmask.ముసుగు, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, దత్తాంశం->xwindow, True, &eventmask, 1, &mods);
#అయితే_ముగింపు
}

శూన్య X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;

    XIGrabModifiers mods;

    ఒకవేళ (!xinput2_multitouch_supported) {
        తిరిగి;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.స్థితి_2 = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, దత్తాంశం->xwindow, 1, &mods);
#అయితే_ముగింపు
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2

స్థిర శూన్య కూడు_Device_ID(Uint32 deviceID, Uint32 **list, పూర్ణాంకం *లెక్క)
{
    పూర్ణాంకం new_లెక్క = (*లెక్క + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_లెక్క * పరిమాణం(*new_list));
    ఒకవేళ (!new_list) {
        // Oh well, we'll drop this one
        తిరిగి;
    }
    new_list[new_లెక్క - 1] = deviceID;

    *లెక్క = new_లెక్క;
    *list = new_list;
}

స్థిర bool HasDeviceID(Uint32 deviceID, స్థిరరాశి Uint32 *list, పూర్ణాంకం లెక్క)
{
    కొరకు (పూర్ణాంకం i = 0; i < లెక్క; ++i) {
        ఒకవేళ (deviceID == list[i]) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
స్థిర శూన్య కూడు_Device_ID64(Uint64 deviceID, Uint64 **list, పూర్ణాంకం *లెక్క)
{
    పూర్ణాంకం new_లెక్క = (*లెక్క + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_లెక్క * పరిమాణం(*new_list));
    ఒకవేళ (!new_list) {
        // Oh well, we'll drop this one
        తిరిగి;
    }
    new_list[new_లెక్క - 1] = deviceID;

    *లెక్క = new_లెక్క;
    *list = new_list;
}
#అయితే_ముగింపు

స్థిర bool HasDeviceID64(Uint64 deviceID, స్థిరరాశి Uint64 *list, పూర్ణాంకం లెక్క)
{
    కొరకు (పూర్ణాంకం i = 0; i < లెక్క; ++i) {
        ఒకవేళ (deviceID == list[i]) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2

శూన్య X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    XIDeviceInfo *info;
    పూర్ణాంకం ndevices;
    పూర్ణాంకం old_keyboard_లెక్క = 0;
    SDL_KeyboardID *old_keyboards = ఖాళీ;
    పూర్ణాంకం new_keyboard_లెక్క = 0;
    SDL_KeyboardID *new_keyboards = ఖాళీ;
    పూర్ణాంకం old_mouse_లెక్క = 0;
    SDL_MouseID *old_mice = ఖాళీ;
    పూర్ణాంకం new_mouse_లెక్క = 0;
    SDL_MouseID *new_mice = ఖాళీ;
    పూర్ణాంకం old_touch_లెక్క = 0;
    Uint64 *old_touch_devices = ఖాళీ;
    పూర్ణాంకం new_touch_లెక్క = 0;
    Uint64 *new_touch_devices = ఖాళీ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(దత్తాంశం->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_లెక్క);
    old_mice = SDL_GetMice(&old_mouse_లెక్క);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_లెక్క);

    కొరకు (పూర్ణాంకం i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        ఎంపిక (dev->use) {
        స్థితి XIMasterKeyboard:
        స్థితి XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                కూడు_Device_ID(keyboardID, &new_keyboards, &new_keyboard_లెక్క);
                ఒకవేళ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_లెక్క)) {
                    SDL_కూడు_Keyboard(keyboardID, dev->name);
                }
            }
            ఆపు;
        స్థితి XIMaster_సూచిక:
            దత్తాంశం->xinput_master_సూచిక_device = dev->deviceid;
            SDL_FALLTHROUGH;
        స్థితి XISlave_సూచిక:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                కూడు_Device_ID(mouseID, &new_mice, &new_mouse_లెక్క);
                ఒకవేళ (!HasDeviceID(mouseID, old_mice, old_mouse_లెక్క)) {
                    SDL_కూడు_Mouse(mouseID, dev->name);
                }
            }
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ఒకవేళ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->అంకె_classes);
        }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        కొరకు (పూర్ణాంకం j = 0; j < dev->అంకె_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ఒకవేళ (class->type != XITouchClass) {
                కొనసాగు;
            }

            touchID = (Uint64)t->sourceid;
            కూడు_Device_ID64(touchID, &new_touch_devices, &new_touch_లెక్క);
            ఒకవేళ (!HasDeviceID64(touchID, old_touch_devices, old_touch_లెక్క)) {
                ఒకవేళ (t->బహుళకం == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_పరోక్ష_RELATIVE;
                } లేకపోతే { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_ప్రత్యక్ష;
                }
                SDL_కూడు_Touch(touchID, touchType, dev->name);
            }
        }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    కొరకు (పూర్ణాంకం i = old_keyboard_లెక్క; i--;) {
        ఒకవేళ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_లెక్క)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    కొరకు (పూర్ణాంకం i = old_mouse_లెక్క; i--;) {
        ఒకవేళ (!HasDeviceID(old_mice[i], new_mice, new_mouse_లెక్క)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    కొరకు (పూర్ణాంకం i = old_touch_లెక్క; i--;) {
        ఒకవేళ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_లెక్క)) {
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

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
