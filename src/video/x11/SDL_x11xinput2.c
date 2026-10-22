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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11pen.h"
#समावेश "SDL_x11video.h"
#समावेश "SDL_x11xinput2.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_pen_c.h"
#समावेश "../../events/SDL_touch_c.h"

#घोषणा MAX_AXIS 16

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
अटल bool xinput2_initialized;
अटल bool xinput2_grabbed_touch_raised;
अटल पूर्णांक xinput2_active_touch_गिनती;
#अगर defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
अटल bool xinput2_scrolling_supported;
अटल bool xinput2_multitouch_supported;
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
अटल bool xinput2_gesture_supported;
#पूर्ण_अगर

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
अटल पूर्णांक xinput2_opcode;

अटल Atom xinput2_rel_x_atom;
अटल Atom xinput2_rel_y_atom;
अटल Atom xinput2_abs_x_atom;
अटल Atom xinput2_abs_y_atom;

// Pointer button remapping table
अटल अचिन्हित अक्षर *xinput2_pointer_button_map;
अटल पूर्णांक xinput2_pointer_button_map_आकार;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
प्रकार काष्ठा
{
    पूर्णांक संख्या_2;
    पूर्णांक scroll_type;
    द्विगुन पूर्व_मूल्य;
    द्विगुन increment;
    bool पूर्व_मूल्य_valid;
} SDL_XInput2ScrollInfo;

प्रकार काष्ठा
{
    पूर्णांक scroll_info_गिनती;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#पूर्ण_अगर

प्रकार काष्ठा
{
    पूर्णांक संख्या_2[2];
    bool relative[2];
    bool पूर्व_coord_valid[2];
    द्विगुन minval[2];
    द्विगुन maxval[2];
    द्विगुन पूर्व_coords[2];
} SDL_XInput2RelativeDevice;

प्रकार काष्ठा SDL_XInput2DeviceInfo
{
    पूर्णांक device_id;
    SDL_XInput2RelativeDevice relative;
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#पूर्ण_अगर
    काष्ठा SDL_XInput2DeviceInfo *अग्र;
} SDL_XInput2DeviceInfo;

अटल SDL_XInput2DeviceInfo *xinput2_device_info;

अटल व्योम parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, स्थिर XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    द्विगुन processed_coords[2] = { 0.0, 0.0 };
    पूर्णांक मूल्यावली_i = 0, found = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    स्थिर bool use_raw_vals = mouse->निवेश_Transform || !mouse->enable_relative_system_scale;

    क्रम (पूर्णांक i = 0; i < rawev->valuators.mask_len * 8 && found < 2; ++i) {
        अगर (!XIMaskIsSet(rawev->valuators.mask, i)) {
            जारी;
        }

        क्रम (पूर्णांक j = 0; j < 2; ++j) {
            अगर (rel_dev->संख्या_2[j] == i) {
                स्थिर द्विगुन current_val = use_raw_vals ? rawev->raw_मूल्यावली[मूल्यावली_i] : rawev->valuators.मूल्यावली[मूल्यावली_i];

                अगर (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } अन्यथा {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    अगर (rel_dev->पूर्व_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->पूर्व_coords[j]; // convert absolute to relative
                    }
                    rel_dev->पूर्व_coords[j] = current_val;
                    rel_dev->पूर्व_coord_valid[j] = true;
                }
                ++found;

                अवरोध;
            }
        }

        ++मूल्यावली_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    अगर (mouse->relative_mode && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->समय, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (भग्न)processed_coords[0], (भग्न)processed_coords[1]);
    }
}

अटल पूर्णांक query_xinput2_version(Display *display, पूर्णांक major, पूर्णांक minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQueryVersion(display, &major, &minor);
    वापस (major * 1000) + minor;
}

अटल bool xinput2_version_atleast(स्थिर पूर्णांक version, स्थिर पूर्णांक wantmajor, स्थिर पूर्णांक wantminor)
{
    वापस version >= ((wantmajor * 1000) + wantminor);
}

अटल SDL_Window *xinput2_get_sdlwindow(SDL_Video_तथ्य *videodata, Window window)
{
    स्थिर SDL_Window_तथ्य *windowdata = X11_FindWindow(videodata, window);
    वापस windowdata ? windowdata->window : शून्य;
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
अटल व्योम xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, स्थिर XIDeviceEvent *xev)
{
    पूर्णांक मूल्यावली_i = 0;
    क्रम (पूर्णांक j = 0; j < xev->valuators.mask_len * 8; ++j) {
        अगर (!XIMaskIsSet(xev->valuators.mask, j)) {
            जारी;
        }

        क्रम (पूर्णांक k = 0; k < scroll_dev->scroll_info_गिनती; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            अगर (info->संख्या_2 == j) {
                स्थिर द्विगुन current_val = xev->valuators.मूल्यावली[मूल्यावली_i];
                स्थिर द्विगुन delta = (info->पूर्व_मूल्य - current_val) / info->increment;
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
                अगर (info->पूर्व_मूल्य_valid && SDL_fabs(delta) < (द्विगुन)SDL_MAX_SINT32 * 0.95) {
                    स्थिर द्विगुन x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    स्थिर द्विगुन y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->समय, mouse->focus, (SDL_MouseID)xev->sourceid, (भग्न)-x, (भग्न)y, SDL_MOUSEWHEEL_NORMAL);
                }
                info->पूर्व_मूल्य = current_val;
                info->पूर्व_मूल्य_valid = true;
            }
        }

        ++मूल्यावली_i;
    }
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
अटल व्योम xinput2_normalize_touch_coordinates(SDL_Window *window, द्विगुन in_x, द्विगुन in_y, भग्न *out_x, भग्न *out_y)
{
    अगर (window) {
        अगर (window->w == 1) {
            *out_x = 0.5f;
        } अन्यथा {
            *out_x = (भग्न)in_x / (window->w - 1);
        }
        अगर (window->h == 1) {
            *out_y = 0.5f;
        } अन्यथा {
            *out_y = (भग्न)in_y / (window->h - 1);
        }
    } अन्यथा {
        // couldn't find the window...
        *out_x = (भग्न)in_x;
        *out_y = (भग्न)in_y;
    }
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_तथ्य *तथ्य = _this->internal;

    पूर्णांक version = 0;
    XIEventMask eventmask;
    अचिन्हित अक्षर mask[5] = { 0, 0, 0, 0, 0 };
    पूर्णांक event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    अगर (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        वापस false;
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
    अगर (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(तथ्य->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        वापस false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    version = query_xinput2_version(तथ्य->display, 2, 4);
    अगर (!xinput2_version_atleast(version, 2, 0)) {
        वापस false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_version_atleast(version, 2, 1);
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_version_atleast(version, 2, 2);
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_version_atleast(version, 2, 4);
#पूर्ण_अगर

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(तथ्य->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(तथ्य->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(तथ्य->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(तथ्य->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = माप(mask);
    eventmask.mask = mask;

    XISetMask(mask, XI_RawMotion);
    XISetMask(mask, XI_RawButtonPress);
    XISetMask(mask, XI_RawButtonRelease);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    अगर (xinput2_scrolling_supported) {
        XISetMask(mask, XI_Motion);
    }
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    अगर (xinput2_multitouch_supported) {
        XISetMask(mask, XI_RawTouchBegin);
        XISetMask(mask, XI_RawTouchUpdate);
        XISetMask(mask, XI_RawTouchEnd);
    }
#पूर्ण_अगर

    X11_XISelectEvents(तथ्य->display, Default_मूल_Window(तथ्य->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(mask);
    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = माप(mask);
    eventmask.mask = mask;

#अगर_अघोषित USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISetMask(mask, XI_कुंजी_Press);
    XISetMask(mask, XI_कुंजी_Release);
#पूर्ण_अगर

    XISetMask(mask, XI_HierarchyChanged);
    X11_XISelectEvents(तथ्य->display, Default_मूल_Window(तथ्य->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2UpdatePointerMapping(_this);

    वापस true;
#अन्यथा
    वापस false;
#पूर्ण_अगर
}

व्योम X11_QuitXinput2(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    क्रम (SDL_XInput2DeviceInfo *i = xinput2_device_info, *अग्र = शून्य; i; i = अग्र) {
        अग्र = i->अग्र;
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#पूर्ण_अगर
        SDL_free(i);
    }
    xinput2_device_info = शून्य;

    SDL_free(xinput2_pointer_button_map);
    xinput2_pointer_button_map = शून्य;
    xinput2_pointer_button_map_आकार = 0;
#पूर्ण_अगर
}

व्योम X11_Xinput2UpdatePointerMapping(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    अगर (X11_Xinput2IsInitialized()) {
        SDL_Video_तथ्य *vid = _this->internal;

        SDL_free(xinput2_pointer_button_map);
        xinput2_pointer_button_map = शून्य;
        xinput2_pointer_button_map_आकार = 0;

        xinput2_pointer_button_map_आकार = X11_XGetPointerMapping(vid->display, शून्य, 0);
        अगर (xinput2_pointer_button_map_आकार) {
            xinput2_pointer_button_map = SDL_calloc(xinput2_pointer_button_map_आकार, माप(अचिन्हित अक्षर));
            अगर (xinput2_pointer_button_map) {
                xinput2_pointer_button_map_आकार = X11_XGetPointerMapping(vid->display, xinput2_pointer_button_map, xinput2_pointer_button_map_आकार);
            } अन्यथा {
                xinput2_pointer_button_map_आकार = 0;
            }
        }
    }
#पूर्ण_अगर
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
अटल व्योम xinput2_remove_device_info(स्थिर पूर्णांक device_id)
{
    क्रम (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *पूर्व = शून्य; devinfo; devinfo = devinfo->अग्र) {
        अगर (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (पूर्व == शून्य));
            अगर (!पूर्व) {
                xinput2_device_info = devinfo->अग्र;
            } अन्यथा {
                पूर्व->अग्र = devinfo->अग्र;
            }
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#पूर्ण_अगर
            SDL_free(devinfo);
            वापस;
        }
        पूर्व = devinfo;
    }
}

अटल व्योम xinput2_reset_device_valuators(व्योम)
{
    क्रम (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->अग्र) {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        क्रम (पूर्णांक i = 0; i < devinfo->scroll.scroll_info_गिनती; ++i) {
            devinfo->scroll.scroll_info[i].पूर्व_मूल्य_valid = false;
        }
#पूर्ण_अगर
        devinfo->relative.पूर्व_coord_valid[0] = false;
        devinfo->relative.पूर्व_coord_valid[1] = false;
    }
}

अटल व्योम xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, पूर्णांक अंक_classes)
{
    अगर (!devinfo) {
        वापस;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    पूर्णांक rel_axis_सूचकांक = 0;

    SDL_zero(devinfo->relative);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    पूर्णांक allocated_scroll_info_गिनती = devinfo->scroll.scroll_info_गिनती;
    devinfo->scroll.scroll_info_गिनती = 0;
#पूर्ण_अगर

    क्रम (पूर्णांक i = 0; i < अंक_classes; ++i) {
        अगर (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            स्थिर XIValuatorClassInfo *v = (स्थिर XIValuatorClassInfo *)classes[i];
            अगर (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_सूचकांक == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.संख्या_2[0] = v->संख्या_2;
                devinfo->relative.relative[0] = (v->mode == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                अगर (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } अन्यथा अगर (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } अन्यथा अगर (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_सूचकांक == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.संख्या_2[1] = v->संख्या_2;
                devinfo->relative.relative[1] = (v->mode == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                अगर (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } अन्यथा अगर (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_सूचकांक;
        }
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        अन्यथा अगर (classes[i]->type == XIScrollClass) {
            स्थिर XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            अगर (devinfo->scroll.scroll_info_गिनती == allocated_scroll_info_गिनती) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_गिनती + 2) * माप(SDL_XInput2ScrollInfo));
                अगर (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_गिनती = 0;
                    devinfo->scroll.scroll_info_गिनती = 0;
                    जारी;
                }

                allocated_scroll_info_गिनती += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_गिनती];
            ++devinfo->scroll.scroll_info_गिनती;

            SDL_zerop(scroll_info);
            scroll_info->संख्या_2 = s->संख्या_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

अटल SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(स्थिर पूर्णांक device_id)
{
    क्रम (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *पूर्व = शून्य; devinfo; devinfo = devinfo->अग्र) {
        अगर (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (पूर्व == शून्य));
            अगर (पूर्व) { // move this to the front of the list, assuming we'll get more from this one.
                पूर्व->अग्र = devinfo->अग्र;
                devinfo->अग्र = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            वापस devinfo;
        }
        पूर्व = devinfo;
    }

    वापस शून्य;
}

अटल SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_तथ्य *videodata, स्थिर पूर्णांक device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    अगर (devinfo) {
        वापस devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, माप(SDL_XInput2DeviceInfo));
    अगर (!devinfo) {
        वापस शून्य;
    }

    पूर्णांक i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    अगर (!xidevinfo) {
        SDL_free(devinfo);
        वापस शून्य;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->अंक_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->अग्र = xinput2_device_info;
    xinput2_device_info = devinfo;

    वापस devinfo;
}
#पूर्ण_अगर

व्योम X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_तथ्य *videodata = _this->internal;

    अगर (cookie->extension != xinput2_opcode) {
        वापस;
    }

    चयन (cookie->evtype) {
    हाल XI_HierarchyChanged:
    {
        स्थिर XIHierarchyEvent *hierev = (स्थिर XIHierarchyEvent *)cookie->तथ्य;
        क्रम (पूर्णांक i = 0; i < hierev->अंक_info; ++i) {
            // pen stuff...
            अगर ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } अन्यथा अगर ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_MaybeAddPenByDeviceID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            अगर (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_changed = true;
    } अवरोध;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    हाल XI_DeviceChanged:
    {
        स्थिर XIDeviceChangedEvent *dcev = (स्थिर XIDeviceChangedEvent *)cookie->तथ्य;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        अगर (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->अंक_classes);
        }
    } अवरोध;

    हाल XI_PropertyEvent:
    {
        स्थिर XIPropertyEvent *proev = (स्थिर XIPropertyEvent *)cookie->तथ्य;
        // Handle pen proximity enter/leave
        अगर (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
            SDL_Window_तथ्य *windowdata = X11_FindWindow(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->window : शून्य, proev->deviceid);
        }
    } अवरोध;

    हाल XI_RawMotion:
    {
        स्थिर XIRawEvent *rawev = (स्थिर XIRawEvent *)cookie->तथ्य;
        स्थिर bool is_pen = X11_FindPenByDeviceID(rawev->sourceid) != शून्य;

        videodata->global_mouse_changed = true;
        अगर (is_pen) {
            अवरोध; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        अगर (!devinfo) {
            अवरोध; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } अवरोध;

    हाल XI_कुंजी_Press:
    हाल XI_कुंजी_Release:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;

#अगर_घोषित USE_XINPUT2_KEYBOARD
        SDL_Window_तथ्य *windowdata = X11_FindWindow(videodata, xev->event);
        XEvent xevent;

        अगर (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            अवरोध;
        }

        अगर (cookie->evtype == XI_कुंजी_Press) {
            xevent.type = कुंजी_Press;
        } अन्यथा {
            xevent.type = कुंजी_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.window = xev->event;
        xevent.xkey.मूल = xev->मूल;
        xevent.xkey.subwindow = xev->child;
        xevent.xkey.समय = xev->समय;
        xevent.xkey.x = (पूर्णांक)xev->event_x;
        xevent.xkey.y = (पूर्णांक)xev->event_y;
        xevent.xkey.x_मूल = (पूर्णांक)xev->मूल_x;
        xevent.xkey.y_मूल = (पूर्णांक)xev->मूल_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_कुंजी_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#अन्यथा
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_last_कुंजी_serial = xev->serial;
        videodata->xinput_last_keyboard_device = xev->sourceid;
#पूर्ण_अगर
    } अवरोध;

    हाल XI_RawButtonPress:
    हाल XI_RawButtonRelease:
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    हाल XI_RawTouchBegin:
    हाल XI_RawTouchUpdate:
    हाल XI_RawTouchEnd:
#पूर्ण_अगर
    {
        videodata->global_mouse_changed = true;
    } अवरोध;

    हाल XI_ButtonPress:
    हाल XI_ButtonRelease:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);
        पूर्णांक button = xev->detail;
        स्थिर bool down = (cookie->evtype == XI_ButtonPress);
#अगर defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अन्यथा
        bool pointer_emulated = false;
#पूर्ण_अगर

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_last_button_serial = xev->serial;

        अगर (pen) {
            अगर (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                अवरोध;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            अगर (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, window, pen->is_eraser, down);
            } अन्यथा {
                SDL_SendPenButton(0, pen->pen, window, button - 1, down);
            }
        } अन्यथा अगर (!pointer_emulated) {
            // Otherwise assume a regular mouse
            SDL_Window_तथ्य *windowdata = X11_FindWindow(videodata, xev->event);
            पूर्णांक x_ticks = 0, y_ticks = 0;

            अगर (xev->deviceid != videodata->xinput_master_pointer_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                अगर (SDL_GetMouseFocus() != windowdata->window) {
                    अवरोध;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                अगर (button <= xinput2_pointer_button_map_आकार) {
                    button = xinput2_pointer_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            अगर (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                अवरोध;
            }

            अगर (down) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (भग्न)xev->event_x, (भग्न)xev->event_y, xev->समय, xev->serial);
            } अन्यथा {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->समय);
            }
        }
    } अवरोध;

    हाल XI_Enter:
    {
        xinput2_reset_device_valuators();
    } अवरोध;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    हाल XI_Motion:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
#अगर defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool pointer_emulated = (xev->flags & XIPointerEmulated) != 0;
#अन्यथा
        bool pointer_emulated = false;
#पूर्ण_अगर

        videodata->global_mouse_changed = true;

        X11_PenHandle *pen = X11_FindPenByDeviceID(xev->sourceid);

        अगर (pen) {
            अगर (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                अवरोध;
            }

            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, window, (भग्न) xev->event_x, (भग्न) xev->event_y);

            भग्न axes[SDL_PEN_AXIS_गिनती];
            X11_PenAxesFromValuators(pen, xev->valuators.मूल्यावली, xev->valuators.mask, xev->valuators.mask_len, axes);

            क्रम (पूर्णांक i = 0; i < SDL_arraysize(axes); i++) {
                अगर (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, window, (SDL_PenAxis) i, axes[i]);
                }
            }
        } अन्यथा अगर (!pointer_emulated) {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            अगर (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                अगर (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#पूर्ण_अगर

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
            अगर (window && (xev->deviceid == videodata->xinput_master_pointer_device || (xinput2_active_touch_गिनती && window->internal->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                अगर (!mouse->relative_mode) {
                        X11_ProcessHitTest(_this, window->internal, (भग्न)xev->event_x, (भग्न)xev->event_y, false);
                        SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, (भग्न)xev->event_x, (भग्न)xev->event_y);
                }
            }
        }
    } अवरोध;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    हाल XI_TouchBegin:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
        भग्न x, y;
        ++xinput2_active_touch_गिनती;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_DOWN, x, y, 1.0);
    } अवरोध;

    हाल XI_TouchEnd:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
        भग्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        अगर (!--xinput2_active_touch_गिनती && window && window->internal->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, window, SDL_EVENT_FINGER_UP, x, y, 1.0);
    } अवरोध;

    हाल XI_TouchUpdate:
    {
        स्थिर XIDeviceEvent *xev = (स्थिर XIDeviceEvent *)cookie->तथ्य;
        भग्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, window, x, y, 1.0);
    } अवरोध;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    हाल XI_GesturePinchBegin:
    हाल XI_GesturePinchUpdate:
    हाल XI_GesturePinchEnd:
    {
        स्थिर XIGesturePinchEvent *xev = (स्थिर XIGesturePinchEvent *)cookie->तथ्य;
        भग्न x, y;
        SDL_Window *window = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(window, xev->event_x, xev->event_y, &x, &y);

        अगर (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } अन्यथा अगर (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, window, (भग्न)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } अन्यथा {
            SDL_SendPinch(SDL_EVENT_PINCH_END, 0, window, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } अवरोध;

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2
}

व्योम X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_active_touch_गिनती = 0;
#पूर्ण_अगर
}

bool X11_Xinput2HandlesMotionForWindow(SDL_Window_तथ्य *window_तथ्य_2)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    स्थिर bool ret = window_तथ्य_2->xinput2_mouse_enabled &&
                     (!window_तथ्य_2->mouse_grabbed || xinput2_active_touch_गिनती || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    वापस ret;
#अन्यथा
    वापस false;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2
}

व्योम X11_Xinput2Select(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_Window_तथ्य *window_तथ्य_2 = window->internal;
    XIEventMask eventmask;
    अचिन्हित अक्षर mask[5] = { 0, 0, 0, 0, 0 };

    अगर (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        वापस;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = माप(mask);
    eventmask.mask = mask;

    अगर (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISetMask(mask, XI_Enter);
    }

    अगर (xinput2_multitouch_supported) {
        XISetMask(mask, XI_TouchBegin);
        XISetMask(mask, XI_TouchUpdate);
        XISetMask(mask, XI_TouchEnd);
        XISetMask(mask, XI_Motion);
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    अगर (xinput2_gesture_supported) {
        XISetMask(mask, XI_GesturePinchBegin);
        XISetMask(mask, XI_GesturePinchUpdate);
        XISetMask(mask, XI_GesturePinchEnd);
    }
#पूर्ण_अगर

    X11_XISelectEvents(तथ्य->display, window_तथ्य_2->xwindow, &eventmask, 1);
#पूर्ण_अगर
}

bool X11_Xinput2IsInitialized(व्योम)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    वापस xinput2_initialized;
#अन्यथा
    वापस false;
#पूर्ण_अगर
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *windowdata = window->internal;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    स्थिर SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (X11_Xinput2IsInitialized()) {
        XIEventMask eventmask;
        अचिन्हित अक्षर mask[4] = { 0, 0, 0, 0 };

        eventmask.mask_len = माप(mask);
        eventmask.mask = mask;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#अगर_घोषित USE_XINPUT2_KEYBOARD
        XISetMask(mask, XI_कुंजी_Press);
        XISetMask(mask, XI_कुंजी_Release);
        windowdata->xinput2_keyboard_enabled = true;
#पूर्ण_अगर

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

        अगर (X11_XISelectEvents(तथ्य->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_निवेश, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#पूर्ण_अगर

    अगर (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        वापस true;
    }
    वापस false;
}

व्योम X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;

    अचिन्हित अक्षर mask[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEventMask eventmask;

    अगर (!xinput2_multitouch_supported) {
        वापस;
    }

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.mask_len = माप(mask);
    eventmask.mask = mask;

    XISetMask(eventmask.mask, XI_TouchBegin);
    XISetMask(eventmask.mask, XI_TouchUpdate);
    XISetMask(eventmask.mask, XI_TouchEnd);
    XISetMask(eventmask.mask, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, तथ्य->xwindow, True, &eventmask, 1, &mods);
#पूर्ण_अगर
}

व्योम X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;

    XIGrabModifiers mods;

    अगर (!xinput2_multitouch_supported) {
        वापस;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.status = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, तथ्य->xwindow, 1, &mods);
#पूर्ण_अगर
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2

अटल व्योम AddDeviceID(Uint32 deviceID, Uint32 **list, पूर्णांक *गिनती)
{
    पूर्णांक new_गिनती = (*गिनती + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_गिनती * माप(*new_list));
    अगर (!new_list) {
        // Oh well, we'll drop this one
        वापस;
    }
    new_list[new_गिनती - 1] = deviceID;

    *गिनती = new_गिनती;
    *list = new_list;
}

अटल bool HasDeviceID(Uint32 deviceID, स्थिर Uint32 *list, पूर्णांक गिनती)
{
    क्रम (पूर्णांक i = 0; i < गिनती; ++i) {
        अगर (deviceID == list[i]) {
            वापस true;
        }
    }
    वापस false;
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
अटल व्योम AddDeviceID64(Uint64 deviceID, Uint64 **list, पूर्णांक *गिनती)
{
    पूर्णांक new_गिनती = (*गिनती + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_गिनती * माप(*new_list));
    अगर (!new_list) {
        // Oh well, we'll drop this one
        वापस;
    }
    new_list[new_गिनती - 1] = deviceID;

    *गिनती = new_गिनती;
    *list = new_list;
}
#पूर्ण_अगर

अटल bool HasDeviceID64(Uint64 deviceID, स्थिर Uint64 *list, पूर्णांक गिनती)
{
    क्रम (पूर्णांक i = 0; i < गिनती; ++i) {
        अगर (deviceID == list[i]) {
            वापस true;
        }
    }
    वापस false;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2

व्योम X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_तथ्य *तथ्य = _this->internal;
    XIDeviceInfo *info;
    पूर्णांक ndevices;
    पूर्णांक old_keyboard_गिनती = 0;
    SDL_KeyboardID *old_keyboards = शून्य;
    पूर्णांक new_keyboard_गिनती = 0;
    SDL_KeyboardID *new_keyboards = शून्य;
    पूर्णांक old_mouse_गिनती = 0;
    SDL_MouseID *old_mice = शून्य;
    पूर्णांक new_mouse_गिनती = 0;
    SDL_MouseID *new_mice = शून्य;
    पूर्णांक old_touch_गिनती = 0;
    Uint64 *old_touch_devices = शून्य;
    पूर्णांक new_touch_गिनती = 0;
    Uint64 *new_touch_devices = शून्य;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(तथ्य->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_गिनती);
    old_mice = SDL_GetMice(&old_mouse_गिनती);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_गिनती);

    क्रम (पूर्णांक i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        चयन (dev->use) {
        हाल XIMasterKeyboard:
        हाल XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                AddDeviceID(keyboardID, &new_keyboards, &new_keyboard_गिनती);
                अगर (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_गिनती)) {
                    SDL_AddKeyboard(keyboardID, dev->name);
                }
            }
            अवरोध;
        हाल XIMasterPointer:
            तथ्य->xinput_master_pointer_device = dev->deviceid;
            SDL_FALLTHROUGH;
        हाल XISlavePointer:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                AddDeviceID(mouseID, &new_mice, &new_mouse_गिनती);
                अगर (!HasDeviceID(mouseID, old_mice, old_mouse_गिनती)) {
                    SDL_AddMouse(mouseID, dev->name);
                }
            }
            अवरोध;
        शेष:
            अवरोध;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        अगर (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->अंक_classes);
        }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        क्रम (पूर्णांक j = 0; j < dev->अंक_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            अगर (class->type != XITouchClass) {
                जारी;
            }

            touchID = (Uint64)t->sourceid;
            AddDeviceID64(touchID, &new_touch_devices, &new_touch_गिनती);
            अगर (!HasDeviceID64(touchID, old_touch_devices, old_touch_गिनती)) {
                अगर (t->mode == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE;
                } अन्यथा { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_DIRECT;
                }
                SDL_AddTouch(touchID, touchType, dev->name);
            }
        }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    क्रम (पूर्णांक i = old_keyboard_गिनती; i--;) {
        अगर (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_गिनती)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    क्रम (पूर्णांक i = old_mouse_गिनती; i--;) {
        अगर (!HasDeviceID(old_mice[i], new_mice, new_mouse_गिनती)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    क्रम (पूर्णांक i = old_touch_गिनती; i--;) {
        अगर (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_गिनती)) {
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

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
