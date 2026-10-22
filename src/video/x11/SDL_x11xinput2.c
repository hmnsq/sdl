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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../events/SDL_touch_c.h"

#تعریف_کن MAX_AXIS 16

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
ساكن bool xinput2_initialized;
ساكن bool xinput2_grabbed_touch_raised;
ساكن صحيح xinput2_فعال_touch_شمار;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ساكن bool xinput2_scrolling_supported;
ساكن bool xinput2_multitouch_supported;
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ساكن bool xinput2_gesture_supported;
#پایان_اگر

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
ساكن بیعلامت حرف *xinput2_اشاره_گر_button_map;
ساكن صحيح xinput2_اشاره_گر_button_map_اندازه;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
تعريفنوع بنية
{
    صحيح عدد_2;
    صحيح scroll_type;
    مزدوج prev_مقدار;
    مزدوج increment;
    bool prev_مقدار_valid;
} SDL_XInput2ScrollInfo;

تعريفنوع بنية
{
    صحيح scroll_info_شمار;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#پایان_اگر

تعريفنوع بنية
{
    صحيح عدد_2[2];
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
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#پایان_اگر
    بنية SDL_XInput2DeviceInfo *بعدی;
} SDL_XInput2DeviceInfo;

ساكن SDL_XInput2DeviceInfo *xinput2_device_info;

ساكن فراغ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    مزدوج processed_coords[2] = { 0.0, 0.0 };
    صحيح مقادیر_i = 0, یافت = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->درون_داد_Transform || !mouse->enable_relative_system_scale;

    لكل (صحيح i = 0; i < rawev->valuators.ماسک_len * 8 && یافت < 2; ++i) {
        إذا (!XIMask_Is_مجموعه(rawev->valuators.ماسک, i)) {
            استمر;
        }

        لكل (صحيح j = 0; j < 2; ++j) {
            إذا (rel_dev->عدد_2[j] == i) {
                ثابت مزدوج current_val = use_raw_vals ? rawev->raw_مقادیر[مقادیر_i] : rawev->valuators.مقادیر[مقادیر_i];

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
                ++یافت;

                اكسر;
            }
        }

        ++مقادیر_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    إذا (mouse->relative_نما && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->زمان, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (عائم)processed_coords[0], (عائم)processed_coords[1]);
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

ساكن SDL_پنجره *xinput2_get_sdlwindow(SDL_Video_داده *videodata, پنجره_2 پنجره)
{
    ثابت SDL_پنجره_داده *windowdata = X11_پیدا_کن_پنجره(videodata, پنجره);
    أرجع windowdata ? windowdata->پنجره : عدم;
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ساكن فراغ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحيح مقادیر_i = 0;
    لكل (صحيح j = 0; j < xev->valuators.ماسک_len * 8; ++j) {
        إذا (!XIMask_Is_مجموعه(xev->valuators.ماسک, j)) {
            استمر;
        }

        لكل (صحيح k = 0; k < scroll_dev->scroll_info_شمار; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            إذا (info->عدد_2 == j) {
                ثابت مزدوج current_val = xev->valuators.مقادیر[مقادیر_i];
                ثابت مزدوج delta = (info->prev_مقدار - current_val) / info->increment;
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
                إذا (info->prev_مقدار_valid && SDL_fabs(delta) < (مزدوج)SDL_MAX_SINT32 * 0.95) {
                    ثابت مزدوج x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت مزدوج y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->زمان, mouse->focus, (SDL_MouseID)xev->sourceid, (عائم)-x, (عائم)y, SDL_MOUSEWHEEL_نرمال);
                }
                info->prev_مقدار = current_val;
                info->prev_مقدار_valid = true;
            }
        }

        ++مقادیر_i;
    }
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ xinput2_normalize_touch_coordinates(SDL_پنجره *پنجره, مزدوج درون_x, مزدوج درون_y, عائم *بیرون_x, عائم *بیرون_y)
{
    إذا (پنجره) {
        إذا (پنجره->w == 1) {
            *بیرون_x = 0.5f;
        } وإلا {
            *بیرون_x = (عائم)درون_x / (پنجره->w - 1);
        }
        إذا (پنجره->h == 1) {
            *بیرون_y = 0.5f;
        } وإلا {
            *بیرون_y = (عائم)درون_y / (پنجره->h - 1);
        }
    } وإلا {
        // couldn't find the window...
        *بیرون_x = (عائم)درون_x;
        *بیرون_y = (عائم)درون_y;
    }
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_داده *داده = _this->داخلی;

    صحيح نسخه = 0;
    XIEvent_ماسک eventmask;
    بیعلامت حرف ماسک[5] = { 0, 0, 0, 0, 0 };
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
        !X11_XQueryExtension(داده->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        أرجع false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    نسخه = query_xinput2_نسخه(داده->display, 2, 4);
    إذا (!xinput2_نسخه_atleast(نسخه, 2, 0)) {
        أرجع false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_نسخه_atleast(نسخه, 2, 1);
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_نسخه_atleast(نسخه, 2, 2);
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_نسخه_atleast(نسخه, 2, 4);
#پایان_اگر

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(داده->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(داده->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(داده->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(داده->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(ماسک);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

    XISet_ماسک(ماسک, XI_RawMotion);
    XISet_ماسک(ماسک, XI_RawButtonPress);
    XISet_ماسک(ماسک, XI_RawButtonRelease);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    إذا (xinput2_scrolling_supported) {
        XISet_ماسک(ماسک, XI_Motion);
    }
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    إذا (xinput2_multitouch_supported) {
        XISet_ماسک(ماسک, XI_RawTouchBegin);
        XISet_ماسک(ماسک, XI_RawTouchUpdate);
        XISet_ماسک(ماسک, XI_Raw_Touch_انتها);
    }
#پایان_اگر

    X11_XISelectEvents(داده->display, Default_ریشه_پنجره(داده->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(ماسک);
    eventmask.deviceid = XIAllDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

#اگر_تعریف_نشده USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_ماسک(ماسک, XI_کلید_Press);
    XISet_ماسک(ماسک, XI_کلید_Release);
#پایان_اگر

    XISet_ماسک(ماسک, XI_Hierarchy_تغییریافته);
    X11_XISelectEvents(داده->display, Default_ریشه_پنجره(داده->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_اشاره_گر_Mapping(_this);

    أرجع true;
#وإلا
    أرجع false;
#پایان_اگر
}

فراغ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    لكل (SDL_XInput2DeviceInfo *i = xinput2_device_info, *بعدی = عدم; i; i = بعدی) {
        بعدی = i->بعدی;
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#پایان_اگر
        SDL_free(i);
    }
    xinput2_device_info = عدم;

    SDL_free(xinput2_اشاره_گر_button_map);
    xinput2_اشاره_گر_button_map = عدم;
    xinput2_اشاره_گر_button_map_اندازه = 0;
#پایان_اگر
}

فراغ X11_Xinput2_Update_اشاره_گر_Mapping(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    إذا (X11_Xinput2IsInitialized()) {
        SDL_Video_داده *vid = _this->داخلی;

        SDL_free(xinput2_اشاره_گر_button_map);
        xinput2_اشاره_گر_button_map = عدم;
        xinput2_اشاره_گر_button_map_اندازه = 0;

        xinput2_اشاره_گر_button_map_اندازه = X11_XGet_اشاره_گر_Mapping(vid->display, عدم, 0);
        إذا (xinput2_اشاره_گر_button_map_اندازه) {
            xinput2_اشاره_گر_button_map = SDL_calloc(xinput2_اشاره_گر_button_map_اندازه, حجم(بیعلامت حرف));
            إذا (xinput2_اشاره_گر_button_map) {
                xinput2_اشاره_گر_button_map_اندازه = X11_XGet_اشاره_گر_Mapping(vid->display, xinput2_اشاره_گر_button_map, xinput2_اشاره_گر_button_map_اندازه);
            } وإلا {
                xinput2_اشاره_گر_button_map_اندازه = 0;
            }
        }
    }
#پایان_اگر
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ساكن فراغ xinput2_remove_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->بعدی) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (!prev) {
                xinput2_device_info = devinfo->بعدی;
            } وإلا {
                prev->بعدی = devinfo->بعدی;
            }
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#پایان_اگر
            SDL_free(devinfo);
            أرجع;
        }
        prev = devinfo;
    }
}

ساكن فراغ xinput2_reset_device_valuators(فراغ)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->بعدی) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        لكل (صحيح i = 0; i < devinfo->scroll.scroll_info_شمار; ++i) {
            devinfo->scroll.scroll_info[i].prev_مقدار_valid = false;
        }
#پایان_اگر
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ساكن فراغ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, صحيح رقم_classes)
{
    إذا (!devinfo) {
        أرجع;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    صحيح rel_axis_شاخص = 0;

    SDL_zero(devinfo->relative);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحيح allocated_scroll_info_شمار = devinfo->scroll.scroll_info_شمار;
    devinfo->scroll.scroll_info_شمار = 0;
#پایان_اگر

    لكل (صحيح i = 0; i < رقم_classes; ++i) {
        إذا (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            إذا (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_شاخص == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.عدد_2[0] = v->عدد_2;
                devinfo->relative.relative[0] = (v->نما == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                إذا (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } وإلا إذا (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } وإلا إذا (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_شاخص == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.عدد_2[1] = v->عدد_2;
                devinfo->relative.relative[1] = (v->نما == XIModeRelative);
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
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        وإلا إذا (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            إذا (devinfo->scroll.scroll_info_شمار == allocated_scroll_info_شمار) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_شمار + 2) * حجم(SDL_XInput2ScrollInfo));
                إذا (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_شمار = 0;
                    devinfo->scroll.scroll_info_شمار = 0;
                    استمر;
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
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->بعدی) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->بعدی = devinfo->بعدی;
                devinfo->بعدی = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            أرجع devinfo;
        }
        prev = devinfo;
    }

    أرجع عدم;
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_داده *videodata, ثابت صحيح device_id)
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

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->رقم_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->بعدی = xinput2_device_info;
    xinput2_device_info = devinfo;

    أرجع devinfo;
}
#پایان_اگر

فراغ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_داده *videodata = _this->داخلی;

    إذا (cookie->extension != xinput2_opcode) {
        أرجع;
    }

    بدل (cookie->evtype) {
    حالة XI_Hierarchy_تغییریافته:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->داده;
        لكل (صحيح i = 0; i < hierev->رقم_info; ++i) {
            // pen stuff...
            إذا ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } وإلا إذا ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_جمع_کن_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            إذا (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_تغییریافته = true;
    } اكسر;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالة XI_Device_تغییریافته:
    {
        ثابت XIDevice_تغییریافته_Event *dcev = (ثابت XIDevice_تغییریافته_Event *)cookie->داده;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        إذا (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->رقم_classes);
        }
    } اكسر;

    حالة XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->داده;
        // Handle pen proximity enter/leave
        إذا (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
            SDL_پنجره_داده *windowdata = X11_پیدا_کن_پنجره(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->پنجره : عدم, proev->deviceid);
        }
    } اكسر;

    حالة XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->داده;
        ثابت bool is_pen = X11_پیدا_کن_Pen_By_Device_ID(rawev->sourceid) != عدم;

        videodata->global_mouse_تغییریافته = true;
        إذا (is_pen) {
            اكسر; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        إذا (!devinfo) {
            اكسر; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } اكسر;

    حالة XI_کلید_Press:
    حالة XI_کلید_Release:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;

#اگر_تعریف_شده USE_XINPUT2_KEYBOARD
        SDL_پنجره_داده *windowdata = X11_پیدا_کن_پنجره(videodata, xev->event);
        XEvent xevent;

        إذا (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            اكسر;
        }

        إذا (cookie->evtype == XI_کلید_Press) {
            xevent.type = کلید_Press;
        } وإلا {
            xevent.type = کلید_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.پنجره = xev->event;
        xevent.xkey.ریشه = xev->ریشه;
        xevent.xkey.subwindow = xev->فرزند;
        xevent.xkey.زمان = xev->زمان;
        xevent.xkey.x = (صحيح)xev->event_x;
        xevent.xkey.y = (صحيح)xev->event_y;
        xevent.xkey.x_ریشه = (صحيح)xev->ریشه_x;
        xevent.xkey.y_ریشه = (صحيح)xev->ریشه_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_کلید_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#وإلا
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_آخرین_کلید_serial = xev->serial;
        videodata->xinput_آخرین_keyboard_device = xev->sourceid;
#پایان_اگر
    } اكسر;

    حالة XI_RawButtonPress:
    حالة XI_RawButtonRelease:
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_RawTouchBegin:
    حالة XI_RawTouchUpdate:
    حالة XI_Raw_Touch_انتها:
#پایان_اگر
    {
        videodata->global_mouse_تغییریافته = true;
    } اكسر;

    حالة XI_ButtonPress:
    حالة XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
        X11_PenHandle *pen = X11_پیدا_کن_Pen_By_Device_ID(xev->sourceid);
        صحيح button = xev->detail;
        ثابت bool پایین = (cookie->evtype == XI_ButtonPress);
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشاره_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشاره_گر_emulated = false;
#پایان_اگر

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_آخرین_button_serial = xev->serial;

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, پنجره, pen->is_eraser, پایین);
            } وإلا {
                SDL_SendPenButton(0, pen->pen, پنجره, button - 1, پایین);
            }
        } وإلا إذا (!اشاره_گر_emulated) {
            // Otherwise assume a regular mouse
            SDL_پنجره_داده *windowdata = X11_پیدا_کن_پنجره(videodata, xev->event);
            صحيح x_ticks = 0, y_ticks = 0;

            إذا (xev->deviceid != videodata->xinput_master_اشاره_گر_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                إذا (SDL_GetMouseFocus() != windowdata->پنجره) {
                    اكسر;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                إذا (button <= xinput2_اشاره_گر_button_map_اندازه) {
                    button = xinput2_اشاره_گر_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            إذا (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                اكسر;
            }

            إذا (پایین) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (عائم)xev->event_x, (عائم)xev->event_y, xev->زمان, xev->serial);
            } وإلا {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->زمان);
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
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشاره_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشاره_گر_emulated = false;
#پایان_اگر

        videodata->global_mouse_تغییریافته = true;

        X11_PenHandle *pen = X11_پیدا_کن_Pen_By_Device_ID(xev->sourceid);

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }

            SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, پنجره, (عائم) xev->event_x, (عائم) xev->event_y);

            عائم axes[SDL_PEN_AXIS_شمار];
            X11_PenAxesFromValuators(pen, xev->valuators.مقادیر, xev->valuators.ماسک, xev->valuators.ماسک_len, axes);

            لكل (صحيح i = 0; i < SDL_arraysize(axes); i++) {
                إذا (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, پنجره, (SDL_PenAxis) i, axes[i]);
                }
            }
        } وإلا إذا (!اشاره_گر_emulated) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            إذا (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                إذا (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#پایان_اگر

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (پنجره && (xev->deviceid == videodata->xinput_master_اشاره_گر_device || (xinput2_فعال_touch_شمار && پنجره->داخلی->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                إذا (!mouse->relative_نما) {
                        X11_Process_اصابت_Test(_this, پنجره->داخلی, (عائم)xev->event_x, (عائم)xev->event_y, false);
                        SDL_SendMouseMotion(0, پنجره, SDL_GLOBAL_MOUSE_ID, false, (عائم)xev->event_x, (عائم)xev->event_y);
                }
            }
        }
    } اكسر;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
        عائم x, y;
        ++xinput2_فعال_touch_شمار;
        SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(پنجره, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, پنجره, SDL_EVENT_FINGER_پایین, x, y, 1.0);
    } اكسر;

    حالة XI_Touch_انتها:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
        عائم x, y;
        SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
        إذا (!--xinput2_فعال_touch_شمار && پنجره && پنجره->داخلی->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(پنجره, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, پنجره, SDL_EVENT_FINGER_به_بالا, x, y, 1.0);
    } اكسر;

    حالة XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->داده;
        عائم x, y;
        SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(پنجره, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, پنجره, x, y, 1.0);
    } اكسر;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالة XI_GesturePinchBegin:
    حالة XI_GesturePinchUpdate:
    حالة XI_Gesture_Pinch_انتها:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->داده;
        عائم x, y;
        SDL_پنجره *پنجره = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(پنجره, xev->event_x, xev->event_y, &x, &y);

        إذا (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, پنجره, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا إذا (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, پنجره, (عائم)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا {
            SDL_SendPinch(SDL_EVENT_PINCH_انتها, 0, پنجره, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } اكسر;

#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_فعال_touch_شمار = 0;
#پایان_اگر
}

bool X11_Xinput2_Handles_Motion_For_پنجره(SDL_پنجره_داده *پنجره_داده_2)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ثابت bool ret = پنجره_داده_2->xinput2_mouse_enabled &&
                     (!پنجره_داده_2->mouse_grabbed || xinput2_فعال_touch_شمار || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    أرجع ret;
#وإلا
    أرجع false;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_داده *داده = _this->داخلی;
    SDL_پنجره_داده *پنجره_داده_2 = پنجره->داخلی;
    XIEvent_ماسک eventmask;
    بیعلامت حرف ماسک[5] = { 0, 0, 0, 0, 0 };

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
        XISet_ماسک(ماسک, XI_Touch_انتها);
        XISet_ماسک(ماسک, XI_Motion);
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    إذا (xinput2_gesture_supported) {
        XISet_ماسک(ماسک, XI_GesturePinchBegin);
        XISet_ماسک(ماسک, XI_GesturePinchUpdate);
        XISet_ماسک(ماسک, XI_Gesture_Pinch_انتها);
    }
#پایان_اگر

    X11_XISelectEvents(داده->display, پنجره_داده_2->xwindow, &eventmask, 1);
#پایان_اگر
}

bool X11_Xinput2IsInitialized(فراغ)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    أرجع xinput2_initialized;
#وإلا
    أرجع false;
#پایان_اگر
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *windowdata = پنجره->داخلی;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_Video_داده *داده = _this->داخلی;

    إذا (X11_Xinput2IsInitialized()) {
        XIEvent_ماسک eventmask;
        بیعلامت حرف ماسک[4] = { 0, 0, 0, 0 };

        eventmask.ماسک_len = حجم(ماسک);
        eventmask.ماسک = ماسک;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#اگر_تعریف_شده USE_XINPUT2_KEYBOARD
        XISet_ماسک(ماسک, XI_کلید_Press);
        XISet_ماسک(ماسک, XI_کلید_Release);
        windowdata->xinput2_keyboard_enabled = true;
#پایان_اگر

        XISet_ماسک(ماسک, XI_ButtonPress);
        XISet_ماسک(ماسک, XI_ButtonRelease);
        XISet_ماسک(ماسک, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_ماسک(ماسک, XI_Enter);
        XISet_ماسک(ماسک, XI_Leave);

        // Hotplugging:
        XISet_ماسک(ماسک, XI_Device_تغییریافته);
        XISet_ماسک(ماسک, XI_Hierarchy_تغییریافته);
        XISet_ماسک(ماسک, XI_PropertyEvent); // E.g., when swapping tablet pens

        إذا (X11_XISelectEvents(داده->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_درون_داد, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#پایان_اگر

    إذا (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        أرجع true;
    }
    أرجع false;
}

فراغ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;

    بیعلامت حرف ماسک[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_ماسک eventmask;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    mods.modifiers = XIAnyModifier;
    mods.وضعیت = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.ماسک_len = حجم(ماسک);
    eventmask.ماسک = ماسک;

    XISet_ماسک(eventmask.ماسک, XI_TouchBegin);
    XISet_ماسک(eventmask.ماسک, XI_TouchUpdate);
    XISet_ماسک(eventmask.ماسک, XI_Touch_انتها);
    XISet_ماسک(eventmask.ماسک, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, داده->xwindow, True, &eventmask, 1, &mods);
#پایان_اگر
}

فراغ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;

    XIGrabModifiers mods;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.وضعیت = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, داده->xwindow, 1, &mods);
#پایان_اگر
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2

ساكن فراغ جمع_کن_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *شمار)
{
    صحيح new_شمار = (*شمار + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_شمار * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح شمار)
{
    لكل (صحيح i = 0; i < شمار; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ جمع_کن_Device_ID64(Uint64 deviceID, Uint64 **list, صحيح *شمار)
{
    صحيح new_شمار = (*شمار + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_شمار * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_شمار - 1] = deviceID;

    *شمار = new_شمار;
    *list = new_list;
}
#پایان_اگر

ساكن bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحيح شمار)
{
    لكل (صحيح i = 0; i < شمار; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2

فراغ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_داده *داده = _this->داخلی;
    XIDeviceInfo *info;
    صحيح ndevices;
    صحيح old_keyboard_شمار = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_شمار = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_شمار = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_شمار = 0;
    SDL_MouseID *new_mice = عدم;
    صحيح old_touch_شمار = 0;
    Uint64 *old_touch_devices = عدم;
    صحيح new_touch_شمار = 0;
    Uint64 *new_touch_devices = عدم;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(داده->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_شمار);
    old_mice = SDL_GetMice(&old_mouse_شمار);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_شمار);

    لكل (صحيح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        بدل (dev->use) {
        حالة XIMasterKeyboard:
        حالة XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                جمع_کن_Device_ID(keyboardID, &new_keyboards, &new_keyboard_شمار);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_شمار)) {
                    SDL_جمع_کن_Keyboard(keyboardID, dev->name);
                }
            }
            اكسر;
        حالة XIMaster_اشاره_گر:
            داده->xinput_master_اشاره_گر_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالة XISlave_اشاره_گر:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                جمع_کن_Device_ID(mouseID, &new_mice, &new_mouse_شمار);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_شمار)) {
                    SDL_جمع_کن_Mouse(mouseID, dev->name);
                }
            }
            اكسر;
        افتراضي:
            اكسر;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        إذا (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->رقم_classes);
        }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        لكل (صحيح j = 0; j < dev->رقم_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            إذا (class->type != XITouchClass) {
                استمر;
            }

            touchID = (Uint64)t->sourceid;
            جمع_کن_Device_ID64(touchID, &new_touch_devices, &new_touch_شمار);
            إذا (!HasDeviceID64(touchID, old_touch_devices, old_touch_شمار)) {
                إذا (t->نما == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_غیرمستقیم_RELATIVE;
                } وإلا { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_مستقیم;
                }
                SDL_جمع_کن_Touch(touchID, touchType, dev->name);
            }
        }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    لكل (صحيح i = old_keyboard_شمار; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_شمار)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_شمار; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_شمار)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    لكل (صحيح i = old_touch_شمار; i--;) {
        إذا (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_شمار)) {
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

#پایان_اگر // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
