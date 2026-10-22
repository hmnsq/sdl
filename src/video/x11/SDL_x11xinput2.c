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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11pen.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_pen_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

#परिभाषय MAX_AXIS 16

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
स्थिर bool xinput2_initialized;
स्थिर bool xinput2_grabbed_touch_raised;
स्थिर पूर्णाङ्क xinput2_सक्रिय_touch_गणनम्;
#यदि defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
स्थिर bool xinput2_scrolling_supported;
स्थिर bool xinput2_multitouch_supported;
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
स्थिर bool xinput2_gesture_supported;
#यदि_अन्तः

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
स्थिर अचिह्नित वर्ण *xinput2_pointer_button_map;
स्थिर पूर्णाङ्क xinput2_pointer_button_map_आकार;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
प्रकारनिर्देश संरचना
{
    पूर्णाङ्क सङ्ख्या_2;
    पूर्णाङ्क scroll_type;
    द्विगुण पूर्व_मानम्;
    द्विगुण increment;
    bool पूर्व_मानम्_valid;
} SDL_XInput2ScrollInfo;

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क scroll_info_गणनम्;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#यदि_अन्तः

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क सङ्ख्या_2[2];
    bool relative[2];
    bool पूर्व_coord_valid[2];
    द्विगुण minval[2];
    द्विगुण maxval[2];
    द्विगुण पूर्व_coords[2];
} SDL_XInput2RelativeDevice;

प्रकारनिर्देश संरचना SDL_XInput2DeviceInfo
{
    पूर्णाङ्क device_id;
    SDL_XInput2RelativeDevice relative;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#यदि_अन्तः
    संरचना SDL_XInput2DeviceInfo *अग्र;
} SDL_XInput2DeviceInfo;

स्थिर SDL_XInput2DeviceInfo *xinput2_device_info;

स्थिर शून्य parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ध्रुव XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    द्विगुण processed_coords[2] = { 0.0, 0.0 };
    पूर्णाङ्क मानानि_i = 0, प्राप्तम् = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ध्रुव bool use_raw_vals = mouse->निवेशः_Transform || !mouse->enable_relative_system_scale;

    प्रति (पूर्णाङ्क i = 0; i < rawev->valuators.आवरणम्_len * 8 && प्राप्तम् < 2; ++i) {
        यदि (!XIMask_Is_समुच्चयः(rawev->valuators.आवरणम्, i)) {
            अनुवर्त;
        }

        प्रति (पूर्णाङ्क j = 0; j < 2; ++j) {
            यदि (rel_dev->सङ्ख्या_2[j] == i) {
                ध्रुव द्विगुण current_val = use_raw_vals ? rawev->raw_मानानि[मानानि_i] : rawev->valuators.मानानि[मानानि_i];

                यदि (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } अन्यथा {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    यदि (rel_dev->पूर्व_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->पूर्व_coords[j]; // convert absolute to relative
                    }
                    rel_dev->पूर्व_coords[j] = current_val;
                    rel_dev->पूर्व_coord_valid[j] = true;
                }
                ++प्राप्तम्;

                भङ्ग;
            }
        }

        ++मानानि_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    यदि (mouse->relative_बहुलकम् && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->time, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (भिन्न)processed_coords[0], (भिन्न)processed_coords[1]);
    }
}

स्थिर पूर्णाङ्क query_xinput2_संस्करणम्(Display *display, पूर्णाङ्क major, पूर्णाङ्क minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_संस्करणम्(display, &major, &minor);
    प्रत्यागम (major * 1000) + minor;
}

स्थिर bool xinput2_संस्करणम्_atleast(ध्रुव पूर्णाङ्क संस्करणम्, ध्रुव पूर्णाङ्क wantmajor, ध्रुव पूर्णाङ्क wantminor)
{
    प्रत्यागम संस्करणम् >= ((wantmajor * 1000) + wantminor);
}

स्थिर SDL_गवाक्षः *xinput2_get_sdlwindow(SDL_Video_दत्त *videodata, गवाक्षः_2 गवाक्षः)
{
    ध्रुव SDL_गवाक्षः_दत्त *windowdata = X11_Find_गवाक्षः(videodata, गवाक्षः);
    प्रत्यागम windowdata ? windowdata->गवाक्षः : रिक्त;
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
स्थिर शून्य xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ध्रुव XIDeviceEvent *xev)
{
    पूर्णाङ्क मानानि_i = 0;
    प्रति (पूर्णाङ्क j = 0; j < xev->valuators.आवरणम्_len * 8; ++j) {
        यदि (!XIMask_Is_समुच्चयः(xev->valuators.आवरणम्, j)) {
            अनुवर्त;
        }

        प्रति (पूर्णाङ्क k = 0; k < scroll_dev->scroll_info_गणनम्; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            यदि (info->सङ्ख्या_2 == j) {
                ध्रुव द्विगुण current_val = xev->valuators.मानानि[मानानि_i];
                ध्रुव द्विगुण delta = (info->पूर्व_मानम् - current_val) / info->increment;
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
                यदि (info->पूर्व_मानम्_valid && SDL_fabs(delta) < (द्विगुण)SDL_MAX_SINT32 * 0.95) {
                    ध्रुव द्विगुण x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ध्रुव द्विगुण y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->time, mouse->focus, (SDL_MouseID)xev->sourceid, (भिन्न)-x, (भिन्न)y, SDL_MOUSEWHEEL_प्रसामान्यम्);
                }
                info->पूर्व_मानम् = current_val;
                info->पूर्व_मानम्_valid = true;
            }
        }

        ++मानानि_i;
    }
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
स्थिर शून्य xinput2_normalize_touch_coordinates(SDL_गवाक्षः *गवाक्षः, द्विगुण अन्तर्_x, द्विगुण अन्तर्_y, भिन्न *बहिर्गमनम्_x, भिन्न *बहिर्गमनम्_y)
{
    यदि (गवाक्षः) {
        यदि (गवाक्षः->w == 1) {
            *बहिर्गमनम्_x = 0.5f;
        } अन्यथा {
            *बहिर्गमनम्_x = (भिन्न)अन्तर्_x / (गवाक्षः->w - 1);
        }
        यदि (गवाक्षः->h == 1) {
            *बहिर्गमनम्_y = 0.5f;
        } अन्यथा {
            *बहिर्गमनम्_y = (भिन्न)अन्तर्_y / (गवाक्षः->h - 1);
        }
    } अन्यथा {
        // couldn't find the window...
        *बहिर्गमनम्_x = (भिन्न)अन्तर्_x;
        *बहिर्गमनम्_y = (भिन्न)अन्तर्_y;
    }
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    पूर्णाङ्क संस्करणम् = 0;
    XIEvent_आवरणम् eventmask;
    अचिह्नित वर्ण आवरणम्[5] = { 0, 0, 0, 0, 0 };
    पूर्णाङ्क event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    यदि (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        प्रत्यागम false;
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
    यदि (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(दत्त->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        प्रत्यागम false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    संस्करणम् = query_xinput2_संस्करणम्(दत्त->display, 2, 4);
    यदि (!xinput2_संस्करणम्_atleast(संस्करणम्, 2, 0)) {
        प्रत्यागम false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_संस्करणम्_atleast(संस्करणम्, 2, 1);
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_संस्करणम्_atleast(संस्करणम्, 2, 2);
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_संस्करणम्_atleast(संस्करणम्, 2, 4);
#यदि_अन्तः

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(दत्त->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(दत्त->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(दत्त->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(दत्त->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(आवरणम्);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.आवरणम्_len = परिमाण(आवरणम्);
    eventmask.आवरणम् = आवरणम्;

    XISet_आवरणम्(आवरणम्, XI_RawMotion);
    XISet_आवरणम्(आवरणम्, XI_RawButtonPress);
    XISet_आवरणम्(आवरणम्, XI_RawButtonRelease);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    यदि (xinput2_scrolling_supported) {
        XISet_आवरणम्(आवरणम्, XI_Motion);
    }
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    यदि (xinput2_multitouch_supported) {
        XISet_आवरणम्(आवरणम्, XI_RawTouchBegin);
        XISet_आवरणम्(आवरणम्, XI_RawTouchUpdate);
        XISet_आवरणम्(आवरणम्, XI_Raw_Touch_अन्तः);
    }
#यदि_अन्तः

    X11_XISelectEvents(दत्त->display, Default_मूलम्_गवाक्षः(दत्त->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(आवरणम्);
    eventmask.deviceid = XIAllDevices;
    eventmask.आवरणम्_len = परिमाण(आवरणम्);
    eventmask.आवरणम् = आवरणम्;

#यदि_अपरिभाषितम् USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_आवरणम्(आवरणम्, XI_कुञ्चिका_Press);
    XISet_आवरणम्(आवरणम्, XI_कुञ्चिका_Release);
#यदि_अन्तः

    XISet_आवरणम्(आवरणम्, XI_Hierarchy_परिवर्तितम्);
    X11_XISelectEvents(दत्त->display, Default_मूलम्_गवाक्षः(दत्त->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    प्रत्यागम true;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः
}

शून्य X11_QuitXinput2(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    प्रति (SDL_XInput2DeviceInfo *i = xinput2_device_info, *अग्र = रिक्त; i; i = अग्र) {
        अग्र = i->अग्र;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#यदि_अन्तः
        SDL_free(i);
    }
    xinput2_device_info = रिक्त;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = रिक्त;
    xinput2_pointer_button_map_आकार = 0;
#यदि_अन्तः
}

शून्य X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    यदि (X11_Xinput2IsInitialized()) {
        SDL_Video_दत्त *vid = _this->आन्तरिकम्;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = रिक्त;
        xinput2_pointer_button_map_आकार = 0;

        xinput2_pointer_button_map_आकार = X11_XGetPointerMapping(vid->display, रिक्त, 0);
        यदि (xinput2_pointer_button_map_आकार) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_आकार, परिमाण(अचिह्नित वर्ण));
            यदि (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_आकार = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_आकार);
            } अन्यथा {
                xinput2_pointer_button_map_आकार = 0;
            }
        }
    }
#यदि_अन्तः
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
स्थिर शून्य xinput2_remove_device_info(ध्रुव पूर्णाङ्क device_id)
{
    प्रति (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *पूर्व = रिक्त; devinfo; devinfo = devinfo->अग्र) {
        यदि (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (पूर्व == रिक्त));
            यदि (!पूर्व) {
                xinput2_device_info = devinfo->अग्र;
            } अन्यथा {
                पूर्व->अग्र = devinfo->अग्र;
            }
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#यदि_अन्तः
            SDL_free(devinfo);
            प्रत्यागम;
        }
        पूर्व = devinfo;
    }
}

स्थिर शून्य xinput2_reset_device_valuators(शून्य)
{
    प्रति (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->अग्र) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        प्रति (पूर्णाङ्क i = 0; i < devinfo->scroll.scroll_info_गणनम्; ++i) {
            devinfo->scroll.scroll_info[i].पूर्व_मानम्_valid = false;
        }
#यदि_अन्तः
        devinfo->relative.पूर्व_coord_valid[0] = false;
        devinfo->relative.पूर्व_coord_valid[1] = false;
    }
}

स्थिर शून्य xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, पूर्णाङ्क अङ्कः_classes)
{
    यदि (!devinfo) {
        प्रत्यागम;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    पूर्णाङ्क rel_axis_सूचकांक = 0;

    SDL_zero(devinfo->relative);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    पूर्णाङ्क allocated_scroll_info_गणनम् = devinfo->scroll.scroll_info_गणनम्;
    devinfo->scroll.scroll_info_गणनम् = 0;
#यदि_अन्तः

    प्रति (पूर्णाङ्क i = 0; i < अङ्कः_classes; ++i) {
        यदि (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ध्रुव XIValuatorClassInfo *v = (ध्रुव XIValuatorClassInfo *)classes[i];
            यदि (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_सूचकांक == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.सङ्ख्या_2[0] = v->सङ्ख्या_2;
                devinfo->relative.relative[0] = (v->बहुलकम् == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                यदि (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } अन्यथा यदि (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } अन्यथा यदि (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_सूचकांक == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.सङ्ख्या_2[1] = v->सङ्ख्या_2;
                devinfo->relative.relative[1] = (v->बहुलकम् == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                यदि (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } अन्यथा यदि (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_सूचकांक;
        }
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        अन्यथा यदि (classes[i]->type == XIScrollClass) {
            ध्रुव XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            यदि (devinfo->scroll.scroll_info_गणनम् == allocated_scroll_info_गणनम्) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_गणनम् + 2) * परिमाण(SDL_XInput2ScrollInfo));
                यदि (!devinfo->scroll.scroll_info) {
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
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

स्थिर SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ध्रुव पूर्णाङ्क device_id)
{
    प्रति (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *पूर्व = रिक्त; devinfo; devinfo = devinfo->अग्र) {
        यदि (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (पूर्व == रिक्त));
            यदि (पूर्व) { // move this to the front of the list, assuming we'll get more from this one.
                पूर्व->अग्र = devinfo->अग्र;
                devinfo->अग्र = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            प्रत्यागम devinfo;
        }
        पूर्व = devinfo;
    }

    प्रत्यागम रिक्त;
}

स्थिर SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_दत्त *videodata, ध्रुव पूर्णाङ्क device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    यदि (devinfo) {
        प्रत्यागम devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, परिमाण(SDL_XInput2DeviceInfo));
    यदि (!devinfo) {
        प्रत्यागम रिक्त;
    }

    पूर्णाङ्क i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    यदि (!xidevinfo) {
        SDL_free(devinfo);
        प्रत्यागम रिक्त;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->अङ्कः_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->अग्र = xinput2_device_info;
    xinput2_device_info = devinfo;

    प्रत्यागम devinfo;
}
#यदि_अन्तः

शून्य X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    यदि (cookie->extension != xinput2_opcode) {
        प्रत्यागम;
    }

    विकल्प (cookie->evtype) {
    पक्ष XI_Hierarchy_परिवर्तितम्:
    {
        ध्रुव XIHierarchyEvent *hierev = (ध्रुव XIHierarchyEvent *)cookie->दत्त;
        प्रति (पूर्णाङ्क i = 0; i < hierev->अङ्कः_info; ++i) {
            // pen stuff...
            यदि ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } अन्यथा यदि ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_सङ्कलय_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            यदि (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_परिवर्तितम् = true;
    } भङ्ग;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    पक्ष XI_Device_परिवर्तितम्:
    {
        ध्रुव XIDevice_परिवर्तितम्_Event *dcev = (ध्रुव XIDevice_परिवर्तितम्_Event *)cookie->दत्त;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        यदि (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->अङ्कः_classes);
        }
    } भङ्ग;

    पक्ष XI_PropertyEvent:
    {
        ध्रुव XIPropertyEvent *proev = (ध्रुव XIPropertyEvent *)cookie->दत्त;
        // Handle pen proximity enter/leave
        यदि (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
            SDL_गवाक्षः_दत्त *windowdata = X11_Find_गवाक्षः(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->गवाक्षः : रिक्त, proev->deviceid);
        }
    } भङ्ग;

    पक्ष XI_RawMotion:
    {
        ध्रुव XIRawEvent *rawev = (ध्रुव XIRawEvent *)cookie->दत्त;
        ध्रुव bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != रिक्त;

        videodata->global_mouse_परिवर्तितम् = true;
        यदि (is_pen) {
            भङ्ग; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        यदि (!devinfo) {
            भङ्ग; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } भङ्ग;

    पक्ष XI_कुञ्चिका_Press:
    पक्ष XI_कुञ्चिका_Release:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;

#यदि_परिभाषितम् USE_XINPUT2_KEYBOARD
        SDL_गवाक्षः_दत्त *windowdata = X11_Find_गवाक्षः(videodata, xev->event);
        XEvent xevent;

        यदि (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            भङ्ग;
        }

        यदि (cookie->evtype == XI_कुञ्चिका_Press) {
            xevent.type = कुञ्चिका_Press;
        } अन्यथा {
            xevent.type = कुञ्चिका_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.गवाक्षः = xev->event;
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
#अन्यथा
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_चरमः_कुञ्चिका_serial = xev->serial;
        videodata->xinput_चरमः_keyboard_device = xev->sourceid;
#यदि_अन्तः
    } भङ्ग;

    पक्ष XI_RawButtonPress:
    पक्ष XI_RawButtonRelease:
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    पक्ष XI_RawTouchBegin:
    पक्ष XI_RawTouchUpdate:
    पक्ष XI_Raw_Touch_अन्तः:
#यदि_अन्तः
    {
        videodata->global_mouse_परिवर्तितम् = true;
    } भङ्ग;

    पक्ष XI_ButtonPress:
    पक्ष XI_ButtonRelease:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        पूर्णाङ्क button = xev->detail;
        ध्रुव bool अधस्तात् = (cookie->evtype == XI_ButtonPress);
#यदि defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अन्यथा
        bool pointer_emulated = false;
#यदि_अन्तः

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_चरमः_button_serial = xev->serial;

        यदि (pen) {
            यदि (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                भङ्ग;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
            यदि (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, गवाक्षः, pen->is_eraser, अधस्तात्);
            } अन्यथा {
                SDL_SendPenButton(0, pen->pen, गवाक्षः, button - 1, अधस्तात्);
            }
        } अन्यथा यदि (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_गवाक्षः_दत्त *windowdata = X11_Find_गवाक्षः(videodata, xev->event);
            पूर्णाङ्क x_ticks = 0, y_ticks = 0;

            यदि (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                यदि (SDL_GetMouseFocus() != windowdata->गवाक्षः) {
                    भङ्ग;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                यदि (button <= xinput2_pointer_button_map_आकार) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            यदि (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                भङ्ग;
            }

            यदि (अधस्तात्) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (भिन्न)xev->event_x, (भिन्न)xev->event_y, xev->time, xev->serial);
            } अन्यथा {
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
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
#यदि defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अन्यथा
        bool pointer_emulated = false;
#यदि_अन्तः

        videodata->global_mouse_परिवर्तितम् = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        यदि (pen) {
            यदि (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                भङ्ग;
            }

            SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, गवाक्षः, (भिन्न) xev->event_x, (भिन्न) xev->event_y);

            भिन्न axes[SDL_PEN_AXIS_गणनम्];
            X11_PenAxesFromValuators(pen, xev->valuators.मानानि, xev->valuators.आवरणम्, xev->valuators.आवरणम्_len, axes);

            प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(axes); i++) {
                यदि (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, गवाक्षः, (SDL_PenAxis) i, axes[i]);
                }
            }
        } अन्यथा यदि (!pointer_emulated) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            यदि (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                यदि (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#यदि_अन्तः

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
            यदि (गवाक्षः && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_सक्रिय_touch_गणनम् && गवाक्षः->आन्तरिकम्->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                यदि (!mouse->relative_बहुलकम्) {
                        X11_Process_लब्धम्_Test(_this, गवाक्षः->आन्तरिकम्, (भिन्न)xev->event_x, (भिन्न)xev->event_y, false);
                        SDL_SendMouseMotion(0, गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, (भिन्न)xev->event_x, (भिन्न)xev->event_y);
                }
            }
        }
    } भङ्ग;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    पक्ष XI_TouchBegin:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
        भिन्न x, y;
        ++xinput2_सक्रिय_touch_गणनम्;
        SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(गवाक्षः, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, गवाक्षः, SDL_EVENT_FINGER_अधस्तात्, x, y, 1.0);
    } भङ्ग;

    पक्ष XI_Touch_अन्तः:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
        भिन्न x, y;
        SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
        यदि (!--xinput2_सक्रिय_touch_गणनम् && गवाक्षः && गवाक्षः->आन्तरिकम्->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(गवाक्षः, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, गवाक्षः, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, 1.0);
    } भङ्ग;

    पक्ष XI_TouchUpdate:
    {
        ध्रुव XIDeviceEvent *xev = (ध्रुव XIDeviceEvent *)cookie->दत्त;
        भिन्न x, y;
        SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(गवाक्षः, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, गवाक्षः, x, y, 1.0);
    } भङ्ग;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    पक्ष XI_GesturePinchBegin:
    पक्ष XI_GesturePinchUpdate:
    पक्ष XI_Gesture_Pinch_अन्तः:
    {
        ध्रुव XIGesturePinchEvent *xev = (ध्रुव XIGesturePinchEvent *)cookie->दत्त;
        भिन्न x, y;
        SDL_गवाक्षः *गवाक्षः = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(गवाक्षः, xev->event_x, xev->event_y, &x, &y);

        यदि (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, गवाक्षः, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } अन्यथा यदि (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, गवाक्षः, (भिन्न)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } अन्यथा {
            SDL_SendPinch(SDL_EVENT_PINCH_अन्तः, 0, गवाक्षः, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } भङ्ग;

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2
}

शून्य X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_सक्रिय_touch_गणनम् = 0;
#यदि_अन्तः
}

bool X11_Xinput2_Handles_Motion_For_गवाक्षः(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ध्रुव bool ret = गवाक्षः_दत्त_2->xinput2_mouse_enabled &&
                     (!गवाक्षः_दत्त_2->mouse_grabbed || xinput2_सक्रिय_touch_गणनम् || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    प्रत्यागम ret;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2
}

शून्य X11_Xinput2Select(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;
    XIEvent_आवरणम् eventmask;
    अचिह्नित वर्ण आवरणम्[5] = { 0, 0, 0, 0, 0 };

    यदि (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        प्रत्यागम;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.आवरणम्_len = परिमाण(आवरणम्);
    eventmask.आवरणम् = आवरणम्;

    यदि (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_आवरणम्(आवरणम्, XI_Enter);
    }

    यदि (xinput2_multitouch_supported) {
        XISet_आवरणम्(आवरणम्, XI_TouchBegin);
        XISet_आवरणम्(आवरणम्, XI_TouchUpdate);
        XISet_आवरणम्(आवरणम्, XI_Touch_अन्तः);
        XISet_आवरणम्(आवरणम्, XI_Motion);
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    यदि (xinput2_gesture_supported) {
        XISet_आवरणम्(आवरणम्, XI_GesturePinchBegin);
        XISet_आवरणम्(आवरणम्, XI_GesturePinchUpdate);
        XISet_आवरणम्(आवरणम्, XI_Gesture_Pinch_अन्तः);
    }
#यदि_अन्तः

    X11_XISelectEvents(दत्त->display, गवाक्षः_दत्त_2->xwindow, &eventmask, 1);
#यदि_अन्तः
}

bool X11_Xinput2IsInitialized(शून्य)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    प्रत्यागम xinput2_initialized;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    ध्रुव SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (X11_Xinput2IsInitialized()) {
        XIEvent_आवरणम् eventmask;
        अचिह्नित वर्ण आवरणम्[4] = { 0, 0, 0, 0 };

        eventmask.आवरणम्_len = परिमाण(आवरणम्);
        eventmask.आवरणम् = आवरणम्;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#यदि_परिभाषितम् USE_XINPUT2_KEYBOARD
        XISet_आवरणम्(आवरणम्, XI_कुञ्चिका_Press);
        XISet_आवरणम्(आवरणम्, XI_कुञ्चिका_Release);
        windowdata->xinput2_keyboard_enabled = true;
#यदि_अन्तः

        XISet_आवरणम्(आवरणम्, XI_ButtonPress);
        XISet_आवरणम्(आवरणम्, XI_ButtonRelease);
        XISet_आवरणम्(आवरणम्, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_आवरणम्(आवरणम्, XI_Enter);
        XISet_आवरणम्(आवरणम्, XI_Leave);

        // Hotplugging:
        XISet_आवरणम्(आवरणम्, XI_Device_परिवर्तितम्);
        XISet_आवरणम्(आवरणम्, XI_Hierarchy_परिवर्तितम्);
        XISet_आवरणम्(आवरणम्, XI_PropertyEvent); // E.g., when swapping tablet pens

        यदि (X11_XISelectEvents(दत्त->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_निवेशः, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#यदि_अन्तः

    यदि (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

शून्य X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;

    अचिह्नित वर्ण आवरणम्[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_आवरणम् eventmask;

    यदि (!xinput2_multitouch_supported) {
        प्रत्यागम;
    }

    mods.modifiers = XIAnyModifier;
    mods.स्थितिः = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.आवरणम्_len = परिमाण(आवरणम्);
    eventmask.आवरणम् = आवरणम्;

    XISet_आवरणम्(eventmask.आवरणम्, XI_TouchBegin);
    XISet_आवरणम्(eventmask.आवरणम्, XI_TouchUpdate);
    XISet_आवरणम्(eventmask.आवरणम्, XI_Touch_अन्तः);
    XISet_आवरणम्(eventmask.आवरणम्, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, दत्त->xwindow, True, &eventmask, 1, &mods);
#यदि_अन्तः
}

शून्य X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;

    XIGrabModifiers mods;

    यदि (!xinput2_multitouch_supported) {
        प्रत्यागम;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.स्थितिः = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, दत्त->xwindow, 1, &mods);
#यदि_अन्तः
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2

स्थिर शून्य सङ्कलय_Device_ID(Uint32 deviceID, Uint32 **list, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क new_गणनम् = (*गणनम् + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_गणनम् * परिमाण(*new_list));
    यदि (!new_list) {
        // Oh well, we'll drop this one
        प्रत्यागम;
    }
    new_list[new_गणनम् - 1] = deviceID;

    *गणनम् = new_गणनम्;
    *list = new_list;
}

स्थिर bool HasDeviceID(Uint32 deviceID, ध्रुव Uint32 *list, पूर्णाङ्क गणनम्)
{
    प्रति (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        यदि (deviceID == list[i]) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
स्थिर शून्य सङ्कलय_Device_ID64(Uint64 deviceID, Uint64 **list, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क new_गणनम् = (*गणनम् + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_गणनम् * परिमाण(*new_list));
    यदि (!new_list) {
        // Oh well, we'll drop this one
        प्रत्यागम;
    }
    new_list[new_गणनम् - 1] = deviceID;

    *गणनम् = new_गणनम्;
    *list = new_list;
}
#यदि_अन्तः

स्थिर bool HasDeviceID64(Uint64 deviceID, ध्रुव Uint64 *list, पूर्णाङ्क गणनम्)
{
    प्रति (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        यदि (deviceID == list[i]) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2

शून्य X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
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

    info = X11_XIQueryDevice(दत्त->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_गणनम्);
    old_mice = SDL_GetMice(&old_mouse_गणनम्);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_गणनम्);

    प्रति (पूर्णाङ्क i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        विकल्प (dev->use) {
        पक्ष XIMasterKeyboard:
        पक्ष XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                सङ्कलय_Device_ID(keyboardID, &new_keyboards, &new_keyboard_गणनम्);
                यदि (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_गणनम्)) {
                    SDL_सङ्कलय_Keyboard(keyboardID, dev->name);
                }
            }
            भङ्ग;
        पक्ष XIMasterPointer:
            दत्त->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        पक्ष XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                सङ्कलय_Device_ID(mouseID, &new_mice, &new_mouse_गणनम्);
                यदि (!HasDeviceID(mouseID, old_mice, old_mouse_गणनम्)) {
                    SDL_सङ्कलय_Mouse(mouseID, dev->name);
                }
            }
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        यदि (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->अङ्कः_classes);
        }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        प्रति (पूर्णाङ्क j = 0; j < dev->अङ्कः_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            यदि (class->type != XITouchClass) {
                अनुवर्त;
            }

            touchID = (Uint64)t->sourceid;
            सङ्कलय_Device_ID64(touchID, &new_touch_devices, &new_touch_गणनम्);
            यदि (!HasDeviceID64(touchID, old_touch_devices, old_touch_गणनम्)) {
                यदि (t->बहुलकम् == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_परोक्षम्_RELATIVE;
                } अन्यथा { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_प्रत्यक्षम्;
                }
                SDL_सङ्कलय_Touch(touchID, touchType, dev->name);
            }
        }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    प्रति (पूर्णाङ्क i = old_keyboard_गणनम्; i--;) {
        यदि (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_गणनम्)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    प्रति (पूर्णाङ्क i = old_mouse_गणनम्; i--;) {
        यदि (!HasDeviceID(old_mice[i], new_mice, new_mouse_गणनम्)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    प्रति (पूर्णाङ्क i = old_touch_गणनम्; i--;) {
        यदि (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_गणनम्)) {
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

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
