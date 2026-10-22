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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../events/SDL_touch_c.h"

#تعریف_کړه MAX_AXIS 16

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
ساكن bool xinput2_initialized;
ساكن bool xinput2_grabbed_touch_raised;
ساكن صحيح xinput2_فعال_touch_شمېر;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ساكن bool xinput2_scrolling_supported;
ساكن bool xinput2_multitouch_supported;
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ساكن bool xinput2_gesture_supported;
#د_که_پای

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
ساكن بینښه حرف *xinput2_اشاره_ګر_button_map;
ساكن صحيح xinput2_اشاره_ګر_button_map_اندازه;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
تعريفنوع بنية
{
    صحيح شمېره_2;
    صحيح scroll_type;
    مزدوج prev_ارزښت;
    مزدوج increment;
    bool prev_ارزښت_valid;
} SDL_XInput2ScrollInfo;

تعريفنوع بنية
{
    صحيح scroll_info_شمېر;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#د_که_پای

تعريفنوع بنية
{
    صحيح شمېره_2[2];
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
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#د_که_پای
    بنية SDL_XInput2DeviceInfo *بل;
} SDL_XInput2DeviceInfo;

ساكن SDL_XInput2DeviceInfo *xinput2_device_info;

ساكن فراغ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    مزدوج processed_coords[2] = { 0.0, 0.0 };
    صحيح ارزښتونه_i = 0, وموندل = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->ننوت_Transform || !mouse->enable_relative_system_scale;

    لكل (صحيح i = 0; i < rawev->valuators.ماسک_len * 8 && وموندل < 2; ++i) {
        إذا (!XIMask_Is_سېټ(rawev->valuators.ماسک, i)) {
            استمر;
        }

        لكل (صحيح j = 0; j < 2; ++j) {
            إذا (rel_dev->شمېره_2[j] == i) {
                ثابت مزدوج current_val = use_raw_vals ? rawev->raw_ارزښتونه[ارزښتونه_i] : rawev->valuators.ارزښتونه[ارزښتونه_i];

                إذا (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } وإلا {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    إذا (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++وموندل;

                اكسر;
            }
        }

        ++ارزښتونه_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    إذا (mouse->relative_ډېرپېښ && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->وخت, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (عائم)processed_coords[0], (عائم)processed_coords[1]);
    }
}

ساكن صحيح query_xinput2_نسخه(Display *display, صحيح major, صحيح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_نسخه(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xinput2_نسخه_atleast(ثابت صحيح نسخه, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع نسخه >= ((wantmajor * 1000) + wantminor);
}

ساكن SDL_کړکۍ *xinput2_get_sdlwindow(SDL_Video_معلومات *videodata, کړکۍ_2 کړکۍ)
{
    ثابت SDL_کړکۍ_معلومات *windowdata = X11_پیدا_کړه_کړکۍ(videodata, کړکۍ);
    أرجع windowdata ? windowdata->کړکۍ : عدم;
}
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ساكن فراغ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحيح ارزښتونه_i = 0;
    لكل (صحيح j = 0; j < xev->valuators.ماسک_len * 8; ++j) {
        إذا (!XIMask_Is_سېټ(xev->valuators.ماسک, j)) {
            استمر;
        }

        لكل (صحيح k = 0; k < scroll_dev->scroll_info_شمېر; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            إذا (info->شمېره_2 == j) {
                ثابت مزدوج current_val = xev->valuators.ارزښتونه[ارزښتونه_i];
                ثابت مزدوج delta = (info->prev_ارزښت - current_val) / info->increment;
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
                إذا (info->prev_ارزښت_valid && SDL_fabs(delta) < (مزدوج)SDL_MAX_SINT32 * 0.95) {
                    ثابت مزدوج x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت مزدوج y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->وخت, mouse->focus, (SDL_MouseID)xev->sourceid, (عائم)-x, (عائم)y, SDL_MOUSEWHEEL_نورمال);
                }
                info->prev_ارزښت = current_val;
                info->prev_ارزښت_valid = true;
            }
        }

        ++ارزښتونه_i;
    }
}
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ xinput2_normalize_touch_coordinates(SDL_کړکۍ *کړکۍ, مزدوج دننه_x, مزدوج دننه_y, عائم *بهر_x, عائم *بهر_y)
{
    إذا (کړکۍ) {
        إذا (کړکۍ->w == 1) {
            *بهر_x = 0.5f;
        } وإلا {
            *بهر_x = (عائم)دننه_x / (کړکۍ->w - 1);
        }
        إذا (کړکۍ->h == 1) {
            *بهر_y = 0.5f;
        } وإلا {
            *بهر_y = (عائم)دننه_y / (کړکۍ->h - 1);
        }
    } وإلا {
        // couldn't find the window...
        *بهر_x = (عائم)دننه_x;
        *بهر_y = (عائم)دننه_y;
    }
}
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_معلومات *معلومات = _this->دننی;

    صحيح نسخه = 0;
    XIEvent_ماسک eventmask;
    بینښه حرف ماسک[5] = { 0, 0, 0, 0, 0 };
    صحيح event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    إذا (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
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
    إذا (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(معلومات->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        أرجع false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    نسخه = query_xinput2_نسخه(معلومات->display, 2, 4);
    إذا (!xinput2_نسخه_atleast(نسخه, 2, 0)) {
        أرجع false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_نسخه_atleast(نسخه, 2, 1);
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_نسخه_atleast(نسخه, 2, 2);
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_نسخه_atleast(نسخه, 2, 4);
#د_که_پای

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(معلومات->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(معلومات->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(معلومات->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(معلومات->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(ماسک);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

    XISet_ماسک(ماسک, XI_RawMotion);
    XISet_ماسک(ماسک, XI_RawButtonPress);
    XISet_ماسک(ماسک, XI_RawButtonRelease);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    إذا (xinput2_scrolling_supported) {
        XISet_ماسک(ماسک, XI_Motion);
    }
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    إذا (xinput2_multitouch_supported) {
        XISet_ماسک(ماسک, XI_RawTouchBegin);
        XISet_ماسک(ماسک, XI_RawTouchUpdate);
        XISet_ماسک(ماسک, XI_Raw_Touch_پای_ټکی);
    }
#د_که_پای

    X11_XISelectEvents(معلومات->display, Default_ریښه_کړکۍ(معلومات->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(ماسک);
    eventmask.deviceid = XIAllDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

#که_نه_تعریف_شوی USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_ماسک(ماسک, XI_کلی_Press);
    XISet_ماسک(ماسک, XI_کلی_Release);
#د_که_پای

    XISet_ماسک(ماسک, XI_Hierarchy_بدل_شوی);
    X11_XISelectEvents(معلومات->display, Default_ریښه_کړکۍ(معلومات->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_اشاره_ګر_Mapping(_this);

    أرجع true;
#وإلا
    أرجع false;
#د_که_پای
}

فراغ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    لكل (SDL_XInput2DeviceInfo *i = xinput2_device_info, *بل = عدم; i; i = بل) {
        بل = i->بل;
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#د_که_پای
        SDL_free(i);
    }
    xinput2_device_info = عدم;

    SDL_free(xinput2_اشاره_ګر_button_map);
    xinput2_اشاره_ګر_button_map = عدم;
    xinput2_اشاره_ګر_button_map_اندازه = 0;
#د_که_پای
}

فراغ X11_Xinput2_Update_اشاره_ګر_Mapping(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    إذا (X11_Xinput2IsInitialized()) {
        SDL_Video_معلومات *vid = _this->دننی;

        SDL_free(xinput2_اشاره_ګر_button_map);
        xinput2_اشاره_ګر_button_map = عدم;
        xinput2_اشاره_ګر_button_map_اندازه = 0;

        xinput2_اشاره_ګر_button_map_اندازه = X11_XGet_اشاره_ګر_Mapping(vid->display, عدم, 0);
        إذا (xinput2_اشاره_ګر_button_map_اندازه) {
            xinput2_اشاره_ګر_button_map = SDL_calloc(xinput2_اشاره_ګر_button_map_اندازه, حجم(بینښه حرف));
            إذا (xinput2_اشاره_ګر_button_map) {
                xinput2_اشاره_ګر_button_map_اندازه = X11_XGet_اشاره_ګر_Mapping(vid->display, xinput2_اشاره_ګر_button_map, xinput2_اشاره_ګر_button_map_اندازه);
            } وإلا {
                xinput2_اشاره_ګر_button_map_اندازه = 0;
            }
        }
    }
#د_که_پای
}

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ساكن فراغ xinput2_remove_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->بل) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (!prev) {
                xinput2_device_info = devinfo->بل;
            } وإلا {
                prev->بل = devinfo->بل;
            }
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#د_که_پای
            SDL_free(devinfo);
            أرجع;
        }
        prev = devinfo;
    }
}

ساكن فراغ xinput2_reset_device_valuators(فراغ)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->بل) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        لكل (صحيح i = 0; i < devinfo->scroll.scroll_info_شمېر; ++i) {
            devinfo->scroll.scroll_info[i].prev_ارزښت_valid = false;
        }
#د_که_پای
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ساكن فراغ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, صحيح عدد_classes)
{
    إذا (!devinfo) {
        أرجع;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    صحيح rel_axis_شاخص = 0;

    SDL_zero(devinfo->relative);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحيح allocated_scroll_info_شمېر = devinfo->scroll.scroll_info_شمېر;
    devinfo->scroll.scroll_info_شمېر = 0;
#د_که_پای

    لكل (صحيح i = 0; i < عدد_classes; ++i) {
        إذا (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            إذا (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_شاخص == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.شمېره_2[0] = v->شمېره_2;
                devinfo->relative.relative[0] = (v->ډېرپېښ == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                إذا (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } وإلا إذا (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } وإلا إذا (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_شاخص == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.شمېره_2[1] = v->شمېره_2;
                devinfo->relative.relative[1] = (v->ډېرپېښ == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                إذا (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } وإلا إذا (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_شاخص;
        }
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        وإلا إذا (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            إذا (devinfo->scroll.scroll_info_شمېر == allocated_scroll_info_شمېر) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_شمېر + 2) * حجم(SDL_XInput2ScrollInfo));
                إذا (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_شمېر = 0;
                    devinfo->scroll.scroll_info_شمېر = 0;
                    استمر;
                }

                allocated_scroll_info_شمېر += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_شمېر];
            ++devinfo->scroll.scroll_info_شمېر;

            SDL_zerop(scroll_info);
            scroll_info->شمېره_2 = s->شمېره_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->بل) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->بل = devinfo->بل;
                devinfo->بل = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            أرجع devinfo;
        }
        prev = devinfo;
    }

    أرجع عدم;
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_معلومات *videodata, ثابت صحيح device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    إذا (devinfo) {
        أرجع devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, حجم(SDL_XInput2DeviceInfo));
    إذا (!devinfo) {
        أرجع عدم;
    }

    صحيح i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    إذا (!xidevinfo) {
        SDL_free(devinfo);
        أرجع عدم;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->عدد_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->بل = xinput2_device_info;
    xinput2_device_info = devinfo;

    أرجع devinfo;
}
#د_که_پای

فراغ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_معلومات *videodata = _this->دننی;

    إذا (cookie->extension != xinput2_opcode) {
        أرجع;
    }

    بدل (cookie->evtype) {
    حالة XI_Hierarchy_بدل_شوی:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->معلومات;
        لكل (صحيح i = 0; i < hierev->عدد_info; ++i) {
            // pen stuff...
            إذا ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } وإلا إذا ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_جمع_کړه_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            إذا (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_بدل_شوی = true;
    } اكسر;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالة XI_Device_بدل_شوی:
    {
        ثابت XIDevice_بدل_شوی_Event *dcev = (ثابت XIDevice_بدل_شوی_Event *)cookie->معلومات;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        إذا (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->عدد_classes);
        }
    } اكسر;

    حالة XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->معلومات;
        // Handle pen proximity enter/leave
        إذا (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
            SDL_کړکۍ_معلومات *windowdata = X11_پیدا_کړه_کړکۍ(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->کړکۍ : عدم, proev->deviceid);
        }
    } اكسر;

    حالة XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->معلومات;
        ثابت bool is_pen = X11_پیدا_کړه_Pen_By_Device_ID(rawev->sourceid) != عدم;

        videodata->global_mouse_بدل_شوی = true;
        إذا (is_pen) {
            اكسر; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        إذا (!devinfo) {
            اكسر; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } اكسر;

    حالة XI_کلی_Press:
    حالة XI_کلی_Release:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;

#که_تعریف_شوی USE_XINPUT2_KEYBOARD
        SDL_کړکۍ_معلومات *windowdata = X11_پیدا_کړه_کړکۍ(videodata, xev->event);
        XEvent xevent;

        إذا (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            اكسر;
        }

        إذا (cookie->evtype == XI_کلی_Press) {
            xevent.type = کلی_Press;
        } وإلا {
            xevent.type = کلی_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.کړکۍ = xev->event;
        xevent.xkey.ریښه = xev->ریښه;
        xevent.xkey.subwindow = xev->ماشوم;
        xevent.xkey.وخت = xev->وخت;
        xevent.xkey.x = (صحيح)xev->event_x;
        xevent.xkey.y = (صحيح)xev->event_y;
        xevent.xkey.x_ریښه = (صحيح)xev->ریښه_x;
        xevent.xkey.y_ریښه = (صحيح)xev->ریښه_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_کلی_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#وإلا
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_وروستی_کلی_serial = xev->serial;
        videodata->xinput_وروستی_keyboard_device = xev->sourceid;
#د_که_پای
    } اكسر;

    حالة XI_RawButtonPress:
    حالة XI_RawButtonRelease:
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_RawTouchBegin:
    حالة XI_RawTouchUpdate:
    حالة XI_Raw_Touch_پای_ټکی:
#د_که_پای
    {
        videodata->global_mouse_بدل_شوی = true;
    } اكسر;

    حالة XI_ButtonPress:
    حالة XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
        X11_PenHandle *pen = X11_پیدا_کړه_Pen_By_Device_ID(xev->sourceid);
        صحيح button = xev->detail;
        ثابت bool ښکته = (cookie->evtype == XI_ButtonPress);
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشاره_ګر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشاره_ګر_emulated = false;
#د_که_پای

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_وروستی_button_serial = xev->serial;

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, کړکۍ, pen->is_eraser, ښکته);
            } وإلا {
                SDL_SendPenButton(0, pen->pen, کړکۍ, button - 1, ښکته);
            }
        } وإلا إذا (!اشاره_ګر_emulated) {
            // Otherwise assume a regular mouse
            SDL_کړکۍ_معلومات *windowdata = X11_پیدا_کړه_کړکۍ(videodata, xev->event);
            صحيح x_ticks = 0, y_ticks = 0;

            إذا (xev->deviceid != videodata->xinput_master_اشاره_ګر_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                إذا (SDL_GetMouseFocus() != windowdata->کړکۍ) {
                    اكسر;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                إذا (button <= xinput2_اشاره_ګر_button_map_اندازه) {
                    button = xinput2_اشاره_ګر_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            إذا (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                اكسر;
            }

            إذا (ښکته) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (عائم)xev->event_x, (عائم)xev->event_y, xev->وخت, xev->serial);
            } وإلا {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->وخت);
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
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشاره_ګر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشاره_ګر_emulated = false;
#د_که_پای

        videodata->global_mouse_بدل_شوی = true;

        X11_PenHandle *pen = X11_پیدا_کړه_Pen_By_Device_ID(xev->sourceid);

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }

            SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, کړکۍ, (عائم) xev->event_x, (عائم) xev->event_y);

            عائم axes[SDL_PEN_AXIS_شمېر];
            X11_PenAxesFromValuators(pen, xev->valuators.ارزښتونه, xev->valuators.ماسک, xev->valuators.ماسک_len, axes);

            لكل (صحيح i = 0; i < SDL_arraysize(axes); i++) {
                إذا (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, کړکۍ, (SDL_PenAxis) i, axes[i]);
                }
            }
        } وإلا إذا (!اشاره_ګر_emulated) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            إذا (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                إذا (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#د_که_پای

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (کړکۍ && (xev->deviceid == videodata->xinput_master_اشاره_ګر_device || (xinput2_فعال_touch_شمېر && کړکۍ->دننی->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                إذا (!mouse->relative_ډېرپېښ) {
                        X11_Process_موندنه_Test(_this, کړکۍ->دننی, (عائم)xev->event_x, (عائم)xev->event_y, false);
                        SDL_SendMouseMotion(0, کړکۍ, SDL_GLOBAL_MOUSE_ID, false, (عائم)xev->event_x, (عائم)xev->event_y);
                }
            }
        }
    } اكسر;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
        عائم x, y;
        ++xinput2_فعال_touch_شمېر;
        SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کړکۍ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کړکۍ, SDL_EVENT_FINGER_ښکته, x, y, 1.0);
    } اكسر;

    حالة XI_Touch_پای_ټکی:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
        عائم x, y;
        SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
        إذا (!--xinput2_فعال_touch_شمېر && کړکۍ && کړکۍ->دننی->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(کړکۍ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کړکۍ, SDL_EVENT_FINGER_پورته, x, y, 1.0);
    } اكسر;

    حالة XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->معلومات;
        عائم x, y;
        SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کړکۍ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, کړکۍ, x, y, 1.0);
    } اكسر;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالة XI_GesturePinchBegin:
    حالة XI_GesturePinchUpdate:
    حالة XI_Gesture_Pinch_پای_ټکی:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->معلومات;
        عائم x, y;
        SDL_کړکۍ *کړکۍ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کړکۍ, xev->event_x, xev->event_y, &x, &y);

        إذا (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, کړکۍ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا إذا (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, کړکۍ, (عائم)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا {
            SDL_SendPinch(SDL_EVENT_PINCH_پای_ټکی, 0, کړکۍ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } اكسر;

#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_فعال_touch_شمېر = 0;
#د_که_پای
}

bool X11_Xinput2_Handles_Motion_For_کړکۍ(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ثابت bool ret = کړکۍ_معلومات_2->xinput2_mouse_enabled &&
                     (!کړکۍ_معلومات_2->mouse_grabbed || xinput2_فعال_touch_شمېر || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    أرجع ret;
#وإلا
    أرجع false;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_معلومات *معلومات = _this->دننی;
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = کړکۍ->دننی;
    XIEvent_ماسک eventmask;
    بینښه حرف ماسک[5] = { 0, 0, 0, 0, 0 };

    إذا (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        أرجع;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

    إذا (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_ماسک(ماسک, XI_Enter);
    }

    إذا (xinput2_multitouch_supported) {
        XISet_ماسک(ماسک, XI_TouchBegin);
        XISet_ماسک(ماسک, XI_TouchUpdate);
        XISet_ماسک(ماسک, XI_Touch_پای_ټکی);
        XISet_ماسک(ماسک, XI_Motion);
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    إذا (xinput2_gesture_supported) {
        XISet_ماسک(ماسک, XI_GesturePinchBegin);
        XISet_ماسک(ماسک, XI_GesturePinchUpdate);
        XISet_ماسک(ماسک, XI_Gesture_Pinch_پای_ټکی);
    }
#د_که_پای

    X11_XISelectEvents(معلومات->display, کړکۍ_معلومات_2->xwindow, &eventmask, 1);
#د_که_پای
}

bool X11_Xinput2IsInitialized(فراغ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    أرجع xinput2_initialized;
#وإلا
    أرجع false;
#د_که_پای
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *windowdata = کړکۍ->دننی;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (X11_Xinput2IsInitialized()) {
        XIEvent_ماسک eventmask;
        بینښه حرف ماسک[4] = { 0, 0, 0, 0 };

        eventmask.ماسک_len = حجم(ماسک);
        eventmask.ماسک = ماسک;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#که_تعریف_شوی USE_XINPUT2_KEYBOARD
        XISet_ماسک(ماسک, XI_کلی_Press);
        XISet_ماسک(ماسک, XI_کلی_Release);
        windowdata->xinput2_keyboard_enabled = true;
#د_که_پای

        XISet_ماسک(ماسک, XI_ButtonPress);
        XISet_ماسک(ماسک, XI_ButtonRelease);
        XISet_ماسک(ماسک, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_ماسک(ماسک, XI_Enter);
        XISet_ماسک(ماسک, XI_Leave);

        // Hotplugging:
        XISet_ماسک(ماسک, XI_Device_بدل_شوی);
        XISet_ماسک(ماسک, XI_Hierarchy_بدل_شوی);
        XISet_ماسک(ماسک, XI_PropertyEvent); // E.g., when swapping tablet pens

        إذا (X11_XISelectEvents(معلومات->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ننوت, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#د_که_پای

    إذا (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        أرجع true;
    }
    أرجع false;
}

فراغ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;

    بینښه حرف ماسک[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_ماسک eventmask;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    mods.modifiers = XIAnyModifier;
    mods.حالت = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

    XISet_ماسک(eventmask.ماسک, XI_TouchBegin);
    XISet_ماسک(eventmask.ماسک, XI_TouchUpdate);
    XISet_ماسک(eventmask.ماسک, XI_Touch_پای_ټکی);
    XISet_ماسک(eventmask.ماسک, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, معلومات->xwindow, True, &eventmask, 1, &mods);
#د_که_پای
}

فراغ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;

    XIGrabModifiers mods;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.حالت = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, معلومات->xwindow, 1, &mods);
#د_که_پای
}

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2

ساكن فراغ جمع_کړه_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *شمېر)
{
    صحيح new_شمېر = (*شمېر + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمېر * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمېر - 1] = deviceID;

    *شمېر = new_شمېر;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح شمېر)
{
    لكل (صحيح i = 0; i < شمېر; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ جمع_کړه_Device_ID64(Uint64 deviceID, Uint64 **list, صحيح *شمېر)
{
    صحيح new_شمېر = (*شمېر + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_شمېر * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمېر - 1] = deviceID;

    *شمېر = new_شمېر;
    *list = new_list;
}
#د_که_پای

ساكن bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحيح شمېر)
{
    لكل (صحيح i = 0; i < شمېر; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2

فراغ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_معلومات *معلومات = _this->دننی;
    XIDeviceInfo *info;
    صحيح ndevices;
    صحيح old_keyboard_شمېر = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_شمېر = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_شمېر = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_شمېر = 0;
    SDL_MouseID *new_mice = عدم;
    صحيح old_touch_شمېر = 0;
    Uint64 *old_touch_devices = عدم;
    صحيح new_touch_شمېر = 0;
    Uint64 *new_touch_devices = عدم;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(معلومات->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمېر);
    old_mice = SDL_GetMice(&old_mouse_شمېر);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_شمېر);

    لكل (صحيح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        بدل (dev->use) {
        حالة XIMasterKeyboard:
        حالة XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                جمع_کړه_Device_ID(keyboardID, &new_keyboards, &new_keyboard_شمېر);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمېر)) {
                    SDL_جمع_کړه_Keyboard(keyboardID, dev->name);
                }
            }
            اكسر;
        حالة XIMaster_اشاره_ګر:
            معلومات->xinput_master_اشاره_ګر_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالة XISlave_اشاره_ګر:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                جمع_کړه_Device_ID(mouseID, &new_mice, &new_mouse_شمېر);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_شمېر)) {
                    SDL_جمع_کړه_Mouse(mouseID, dev->name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        إذا (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->عدد_classes);
        }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        لكل (صحيح j = 0; j < dev->عدد_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            إذا (class->type != XITouchClass) {
                استمر;
            }

            touchID = (Uint64)t->sourceid;
            جمع_کړه_Device_ID64(touchID, &new_touch_devices, &new_touch_شمېر);
            إذا (!HasDeviceID64(touchID, old_touch_devices, old_touch_شمېر)) {
                إذا (t->ډېرپېښ == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_غیرمستقیم_RELATIVE;
                } وإلا { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_مستقیم;
                }
                SDL_جمع_کړه_Touch(touchID, touchType, dev->name);
            }
        }
#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    لكل (صحيح i = old_keyboard_شمېر; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمېر)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_شمېر; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمېر)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    لكل (صحيح i = old_touch_شمېر; i--;) {
        إذا (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_شمېر)) {
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

#د_که_پای // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
