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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_pen_c.h"
#ضمن "../../events/SDL_touch_c.h"

#تعریف_کرو MAX_AXIS 16

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
ساكن bool xinput2_initialized;
ساكن bool xinput2_grabbed_touch_raised;
ساكن صحيح xinput2_سرگرم_touch_گنتی;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ساكن bool xinput2_scrolling_supported;
ساكن bool xinput2_multitouch_supported;
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ساكن bool xinput2_gesture_supported;
#جے_انت

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
ساكن بنانشانی حرف *xinput2_اشارہ_گر_button_map;
ساكن صحيح xinput2_اشارہ_گر_button_map_ناپ;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
تعريفنوع بنية
{
    صحيح نمبر_2;
    صحيح scroll_type;
    مزدوج prev_قدر;
    مزدوج increment;
    bool prev_قدر_valid;
} SDL_XInput2ScrollInfo;

تعريفنوع بنية
{
    صحيح scroll_info_گنتی;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#جے_انت

تعريفنوع بنية
{
    صحيح نمبر_2[2];
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
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#جے_انت
    بنية SDL_XInput2DeviceInfo *اگلا;
} SDL_XInput2DeviceInfo;

ساكن SDL_XInput2DeviceInfo *xinput2_device_info;

ساكن فراغ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    مزدوج processed_coords[2] = { 0.0, 0.0 };
    صحيح اقدار_i = 0, لبھیا = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->داخلہ_Transform || !mouse->enable_relative_system_scale;

    لكل (صحيح i = 0; i < rawev->valuators.نقاب_len * 8 && لبھیا < 2; ++i) {
        إذا (!XIMask_Is_سیٹ(rawev->valuators.نقاب, i)) {
            استمر;
        }

        لكل (صحيح j = 0; j < 2; ++j) {
            إذا (rel_dev->نمبر_2[j] == i) {
                ثابت مزدوج current_val = use_raw_vals ? rawev->raw_اقدار[اقدار_i] : rawev->valuators.اقدار[اقدار_i];

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
                ++لبھیا;

                اكسر;
            }
        }

        ++اقدار_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    إذا (mouse->relative_منوال && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->ویلا, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (عائم)processed_coords[0], (عائم)processed_coords[1]);
    }
}

ساكن صحيح query_xinput2_نسخہ(Display *display, صحيح major, صحيح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_نسخہ(display, &major, &minor);
    أرجع (major * 1000) + minor;
}

ساكن bool xinput2_نسخہ_atleast(ثابت صحيح نسخہ, ثابت صحيح wantmajor, ثابت صحيح wantminor)
{
    أرجع نسخہ >= ((wantmajor * 1000) + wantminor);
}

ساكن SDL_کھڑکی *xinput2_get_sdlwindow(SDL_Video_انکڑے *videodata, کھڑکی_2 کھڑکی)
{
    ثابت SDL_کھڑکی_انکڑے *windowdata = X11_لبھو_کھڑکی(videodata, کھڑکی);
    أرجع windowdata ? windowdata->کھڑکی : عدم;
}
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ساكن فراغ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحيح اقدار_i = 0;
    لكل (صحيح j = 0; j < xev->valuators.نقاب_len * 8; ++j) {
        إذا (!XIMask_Is_سیٹ(xev->valuators.نقاب, j)) {
            استمر;
        }

        لكل (صحيح k = 0; k < scroll_dev->scroll_info_گنتی; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            إذا (info->نمبر_2 == j) {
                ثابت مزدوج current_val = xev->valuators.اقدار[اقدار_i];
                ثابت مزدوج delta = (info->prev_قدر - current_val) / info->increment;
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
                إذا (info->prev_قدر_valid && SDL_fabs(delta) < (مزدوج)SDL_MAX_SINT32 * 0.95) {
                    ثابت مزدوج x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت مزدوج y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->ویلا, mouse->focus, (SDL_MouseID)xev->sourceid, (عائم)-x, (عائم)y, SDL_MOUSEWHEEL_عام);
                }
                info->prev_قدر = current_val;
                info->prev_قدر_valid = true;
            }
        }

        ++اقدار_i;
    }
}
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ xinput2_normalize_touch_coordinates(SDL_کھڑکی *کھڑکی, مزدوج وچ_x, مزدوج وچ_y, عائم *باہرلا_x, عائم *باہرلا_y)
{
    إذا (کھڑکی) {
        إذا (کھڑکی->w == 1) {
            *باہرلا_x = 0.5f;
        } وإلا {
            *باہرلا_x = (عائم)وچ_x / (کھڑکی->w - 1);
        }
        إذا (کھڑکی->h == 1) {
            *باہرلا_y = 0.5f;
        } وإلا {
            *باہرلا_y = (عائم)وچ_y / (کھڑکی->h - 1);
        }
    } وإلا {
        // couldn't find the window...
        *باہرلا_x = (عائم)وچ_x;
        *باہرلا_y = (عائم)وچ_y;
    }
}
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    صحيح نسخہ = 0;
    XIEvent_نقاب eventmask;
    بنانشانی حرف نقاب[5] = { 0, 0, 0, 0, 0 };
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
        !X11_XQueryExtension(انکڑے->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        أرجع false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    نسخہ = query_xinput2_نسخہ(انکڑے->display, 2, 4);
    إذا (!xinput2_نسخہ_atleast(نسخہ, 2, 0)) {
        أرجع false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_نسخہ_atleast(نسخہ, 2, 1);
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_نسخہ_atleast(نسخہ, 2, 2);
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_نسخہ_atleast(نسخہ, 2, 4);
#جے_انت

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(انکڑے->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(انکڑے->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(انکڑے->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(انکڑے->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(نقاب);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    XISet_نقاب(نقاب, XI_RawMotion);
    XISet_نقاب(نقاب, XI_RawButtonPress);
    XISet_نقاب(نقاب, XI_RawButtonRelease);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    إذا (xinput2_scrolling_supported) {
        XISet_نقاب(نقاب, XI_Motion);
    }
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    إذا (xinput2_multitouch_supported) {
        XISet_نقاب(نقاب, XI_RawTouchBegin);
        XISet_نقاب(نقاب, XI_RawTouchUpdate);
        XISet_نقاب(نقاب, XI_Raw_Touch_سرا);
    }
#جے_انت

    X11_XISelectEvents(انکڑے->display, Default_جڑ_کھڑکی(انکڑے->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(نقاب);
    eventmask.deviceid = XIAllDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

#جے_بنا_تعریف USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_نقاب(نقاب, XI_کلید_Press);
    XISet_نقاب(نقاب, XI_کلید_Release);
#جے_انت

    XISet_نقاب(نقاب, XI_Hierarchy_بدلیا);
    X11_XISelectEvents(انکڑے->display, Default_جڑ_کھڑکی(انکڑے->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_اشارہ_گر_Mapping(_this);

    أرجع true;
#وإلا
    أرجع false;
#جے_انت
}

فراغ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    لكل (SDL_XInput2DeviceInfo *i = xinput2_device_info, *اگلا = عدم; i; i = اگلا) {
        اگلا = i->اگلا;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#جے_انت
        SDL_free(i);
    }
    xinput2_device_info = عدم;

    SDL_free(xinput2_اشارہ_گر_button_map);
    xinput2_اشارہ_گر_button_map = عدم;
    xinput2_اشارہ_گر_button_map_ناپ = 0;
#جے_انت
}

فراغ X11_Xinput2_Update_اشارہ_گر_Mapping(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    إذا (X11_Xinput2IsInitialized()) {
        SDL_Video_انکڑے *vid = _this->اندرونی;

        SDL_free(xinput2_اشارہ_گر_button_map);
        xinput2_اشارہ_گر_button_map = عدم;
        xinput2_اشارہ_گر_button_map_ناپ = 0;

        xinput2_اشارہ_گر_button_map_ناپ = X11_XGet_اشارہ_گر_Mapping(vid->display, عدم, 0);
        إذا (xinput2_اشارہ_گر_button_map_ناپ) {
            xinput2_اشارہ_گر_button_map = SDL_calloc(xinput2_اشارہ_گر_button_map_ناپ, حجم(بنانشانی حرف));
            إذا (xinput2_اشارہ_گر_button_map) {
                xinput2_اشارہ_گر_button_map_ناپ = X11_XGet_اشارہ_گر_Mapping(vid->display, xinput2_اشارہ_گر_button_map, xinput2_اشارہ_گر_button_map_ناپ);
            } وإلا {
                xinput2_اشارہ_گر_button_map_ناپ = 0;
            }
        }
    }
#جے_انت
}

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ساكن فراغ xinput2_remove_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->اگلا) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (!prev) {
                xinput2_device_info = devinfo->اگلا;
            } وإلا {
                prev->اگلا = devinfo->اگلا;
            }
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#جے_انت
            SDL_free(devinfo);
            أرجع;
        }
        prev = devinfo;
    }
}

ساكن فراغ xinput2_reset_device_valuators(فراغ)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->اگلا) {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        لكل (صحيح i = 0; i < devinfo->scroll.scroll_info_گنتی; ++i) {
            devinfo->scroll.scroll_info[i].prev_قدر_valid = false;
        }
#جے_انت
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
    صحيح rel_axis_اشاریہ = 0;

    SDL_zero(devinfo->relative);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحيح allocated_scroll_info_گنتی = devinfo->scroll.scroll_info_گنتی;
    devinfo->scroll.scroll_info_گنتی = 0;
#جے_انت

    لكل (صحيح i = 0; i < عدد_classes; ++i) {
        إذا (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            إذا (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_اشاریہ == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.نمبر_2[0] = v->نمبر_2;
                devinfo->relative.relative[0] = (v->منوال == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                إذا (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } وإلا إذا (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } وإلا إذا (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_اشاریہ == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.نمبر_2[1] = v->نمبر_2;
                devinfo->relative.relative[1] = (v->منوال == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                إذا (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } وإلا إذا (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_اشاریہ;
        }
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        وإلا إذا (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            إذا (devinfo->scroll.scroll_info_گنتی == allocated_scroll_info_گنتی) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_گنتی + 2) * حجم(SDL_XInput2ScrollInfo));
                إذا (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_گنتی = 0;
                    devinfo->scroll.scroll_info_گنتی = 0;
                    استمر;
                }

                allocated_scroll_info_گنتی += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_گنتی];
            ++devinfo->scroll.scroll_info_گنتی;

            SDL_zerop(scroll_info);
            scroll_info->نمبر_2 = s->نمبر_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحيح device_id)
{
    لكل (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = عدم; devinfo; devinfo = devinfo->اگلا) {
        إذا (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == عدم));
            إذا (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->اگلا = devinfo->اگلا;
                devinfo->اگلا = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            أرجع devinfo;
        }
        prev = devinfo;
    }

    أرجع عدم;
}

ساكن SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_انکڑے *videodata, ثابت صحيح device_id)
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
    devinfo->اگلا = xinput2_device_info;
    xinput2_device_info = devinfo;

    أرجع devinfo;
}
#جے_انت

فراغ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    إذا (cookie->extension != xinput2_opcode) {
        أرجع;
    }

    بدل (cookie->evtype) {
    حالة XI_Hierarchy_بدلیا:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->انکڑے;
        لكل (صحيح i = 0; i < hierev->عدد_info; ++i) {
            // pen stuff...
            إذا ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } وإلا إذا ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_جوڑو_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            إذا (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_بدلیا = true;
    } اكسر;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالة XI_Device_بدلیا:
    {
        ثابت XIDevice_بدلیا_Event *dcev = (ثابت XIDevice_بدلیا_Event *)cookie->انکڑے;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        إذا (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->عدد_classes);
        }
    } اكسر;

    حالة XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->انکڑے;
        // Handle pen proximity enter/leave
        إذا (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
            SDL_کھڑکی_انکڑے *windowdata = X11_لبھو_کھڑکی(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->کھڑکی : عدم, proev->deviceid);
        }
    } اكسر;

    حالة XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->انکڑے;
        ثابت bool is_pen = X11_لبھو_Pen_By_Device_ID(rawev->sourceid) != عدم;

        videodata->global_mouse_بدلیا = true;
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
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;

#جے_تعریف_شدہ USE_XINPUT2_KEYBOARD
        SDL_کھڑکی_انکڑے *windowdata = X11_لبھو_کھڑکی(videodata, xev->event);
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
        xevent.xkey.کھڑکی = xev->event;
        xevent.xkey.جڑ = xev->جڑ;
        xevent.xkey.subwindow = xev->بچہ;
        xevent.xkey.ویلا = xev->ویلا;
        xevent.xkey.x = (صحيح)xev->event_x;
        xevent.xkey.y = (صحيح)xev->event_y;
        xevent.xkey.x_جڑ = (صحيح)xev->جڑ_x;
        xevent.xkey.y_جڑ = (صحيح)xev->جڑ_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_کلید_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#وإلا
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_آخری_کلید_serial = xev->serial;
        videodata->xinput_آخری_keyboard_device = xev->sourceid;
#جے_انت
    } اكسر;

    حالة XI_RawButtonPress:
    حالة XI_RawButtonRelease:
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_RawTouchBegin:
    حالة XI_RawTouchUpdate:
    حالة XI_Raw_Touch_سرا:
#جے_انت
    {
        videodata->global_mouse_بدلیا = true;
    } اكسر;

    حالة XI_ButtonPress:
    حالة XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
        X11_PenHandle *pen = X11_لبھو_Pen_By_Device_ID(xev->sourceid);
        صحيح button = xev->detail;
        ثابت bool تھلے = (cookie->evtype == XI_ButtonPress);
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشارہ_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشارہ_گر_emulated = false;
#جے_انت

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_آخری_button_serial = xev->serial;

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, کھڑکی, pen->is_eraser, تھلے);
            } وإلا {
                SDL_SendPenButton(0, pen->pen, کھڑکی, button - 1, تھلے);
            }
        } وإلا إذا (!اشارہ_گر_emulated) {
            // Otherwise assume a regular mouse
            SDL_کھڑکی_انکڑے *windowdata = X11_لبھو_کھڑکی(videodata, xev->event);
            صحيح x_ticks = 0, y_ticks = 0;

            إذا (xev->deviceid != videodata->xinput_master_اشارہ_گر_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                إذا (SDL_GetMouseFocus() != windowdata->کھڑکی) {
                    اكسر;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                إذا (button <= xinput2_اشارہ_گر_button_map_ناپ) {
                    button = xinput2_اشارہ_گر_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            إذا (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                اكسر;
            }

            إذا (تھلے) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (عائم)xev->event_x, (عائم)xev->event_y, xev->ویلا, xev->serial);
            } وإلا {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->ویلا);
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
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشارہ_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#وإلا
        bool اشارہ_گر_emulated = false;
#جے_انت

        videodata->global_mouse_بدلیا = true;

        X11_PenHandle *pen = X11_لبھو_Pen_By_Device_ID(xev->sourceid);

        إذا (pen) {
            إذا (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                اكسر;
            }

            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, کھڑکی, (عائم) xev->event_x, (عائم) xev->event_y);

            عائم axes[SDL_PEN_AXIS_گنتی];
            X11_PenAxesFromValuators(pen, xev->valuators.اقدار, xev->valuators.نقاب, xev->valuators.نقاب_len, axes);

            لكل (صحيح i = 0; i < SDL_arraysize(axes); i++) {
                إذا (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, کھڑکی, (SDL_PenAxis) i, axes[i]);
                }
            }
        } وإلا إذا (!اشارہ_گر_emulated) {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            إذا (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                إذا (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#جے_انت

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            إذا (کھڑکی && (xev->deviceid == videodata->xinput_master_اشارہ_گر_device || (xinput2_سرگرم_touch_گنتی && کھڑکی->اندرونی->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                إذا (!mouse->relative_منوال) {
                        X11_Process_کامیابی_Test(_this, کھڑکی->اندرونی, (عائم)xev->event_x, (عائم)xev->event_y, false);
                        SDL_SendMouseMotion(0, کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (عائم)xev->event_x, (عائم)xev->event_y);
                }
            }
        }
    } اكسر;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالة XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
        عائم x, y;
        ++xinput2_سرگرم_touch_گنتی;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کھڑکی, SDL_EVENT_FINGER_تھلے, x, y, 1.0);
    } اكسر;

    حالة XI_Touch_سرا:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
        عائم x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        إذا (!--xinput2_سرگرم_touch_گنتی && کھڑکی && کھڑکی->اندرونی->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کھڑکی, SDL_EVENT_FINGER_اتے, x, y, 1.0);
    } اكسر;

    حالة XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->انکڑے;
        عائم x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, کھڑکی, x, y, 1.0);
    } اكسر;
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالة XI_GesturePinchBegin:
    حالة XI_GesturePinchUpdate:
    حالة XI_Gesture_Pinch_سرا:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->انکڑے;
        عائم x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);

        إذا (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, کھڑکی, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا إذا (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, کھڑکی, (عائم)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } وإلا {
            SDL_SendPinch(SDL_EVENT_PINCH_سرا, 0, کھڑکی, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } اكسر;

#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_سرگرم_touch_گنتی = 0;
#جے_انت
}

bool X11_Xinput2_Handles_Motion_For_کھڑکی(SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ثابت bool ret = کھڑکی_انکڑے_2->xinput2_mouse_enabled &&
                     (!کھڑکی_انکڑے_2->mouse_grabbed || xinput2_سرگرم_touch_گنتی || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    أرجع ret;
#وإلا
    أرجع false;
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2
}

فراغ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#إذا defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = کھڑکی->اندرونی;
    XIEvent_نقاب eventmask;
    بنانشانی حرف نقاب[5] = { 0, 0, 0, 0, 0 };

    إذا (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        أرجع;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    إذا (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_نقاب(نقاب, XI_Enter);
    }

    إذا (xinput2_multitouch_supported) {
        XISet_نقاب(نقاب, XI_TouchBegin);
        XISet_نقاب(نقاب, XI_TouchUpdate);
        XISet_نقاب(نقاب, XI_Touch_سرا);
        XISet_نقاب(نقاب, XI_Motion);
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    إذا (xinput2_gesture_supported) {
        XISet_نقاب(نقاب, XI_GesturePinchBegin);
        XISet_نقاب(نقاب, XI_GesturePinchUpdate);
        XISet_نقاب(نقاب, XI_Gesture_Pinch_سرا);
    }
#جے_انت

    X11_XISelectEvents(انکڑے->display, کھڑکی_انکڑے_2->xwindow, &eventmask, 1);
#جے_انت
}

bool X11_Xinput2IsInitialized(فراغ)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    أرجع xinput2_initialized;
#وإلا
    أرجع false;
#جے_انت
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *windowdata = کھڑکی->اندرونی;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (X11_Xinput2IsInitialized()) {
        XIEvent_نقاب eventmask;
        بنانشانی حرف نقاب[4] = { 0, 0, 0, 0 };

        eventmask.نقاب_len = حجم(نقاب);
        eventmask.نقاب = نقاب;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#جے_تعریف_شدہ USE_XINPUT2_KEYBOARD
        XISet_نقاب(نقاب, XI_کلید_Press);
        XISet_نقاب(نقاب, XI_کلید_Release);
        windowdata->xinput2_keyboard_enabled = true;
#جے_انت

        XISet_نقاب(نقاب, XI_ButtonPress);
        XISet_نقاب(نقاب, XI_ButtonRelease);
        XISet_نقاب(نقاب, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_نقاب(نقاب, XI_Enter);
        XISet_نقاب(نقاب, XI_Leave);

        // Hotplugging:
        XISet_نقاب(نقاب, XI_Device_بدلیا);
        XISet_نقاب(نقاب, XI_Hierarchy_بدلیا);
        XISet_نقاب(نقاب, XI_PropertyEvent); // E.g., when swapping tablet pens

        إذا (X11_XISelectEvents(انکڑے->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_داخلہ, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#جے_انت

    إذا (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        أرجع true;
    }
    أرجع false;
}

فراغ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;

    بنانشانی حرف نقاب[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_نقاب eventmask;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    mods.modifiers = XIAnyModifier;
    mods.حالت = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    XISet_نقاب(eventmask.نقاب, XI_TouchBegin);
    XISet_نقاب(eventmask.نقاب, XI_TouchUpdate);
    XISet_نقاب(eventmask.نقاب, XI_Touch_سرا);
    XISet_نقاب(eventmask.نقاب, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, انکڑے->xwindow, True, &eventmask, 1, &mods);
#جے_انت
}

فراغ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;

    XIGrabModifiers mods;

    إذا (!xinput2_multitouch_supported) {
        أرجع;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.حالت = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, انکڑے->xwindow, 1, &mods);
#جے_انت
}

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2

ساكن فراغ جوڑو_Device_ID(Uint32 deviceID, Uint32 **list, صحيح *گنتی)
{
    صحيح new_گنتی = (*گنتی + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}

ساكن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحيح گنتی)
{
    لكل (صحيح i = 0; i < گنتی; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساكن فراغ جوڑو_Device_ID64(Uint64 deviceID, Uint64 **list, صحيح *گنتی)
{
    صحيح new_گنتی = (*گنتی + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    إذا (!new_list) {
        // Oh well, we'll drop this one
        أرجع;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}
#جے_انت

ساكن bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحيح گنتی)
{
    لكل (صحيح i = 0; i < گنتی; ++i) {
        إذا (deviceID == list[i]) {
            أرجع true;
        }
    }
    أرجع false;
}

#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2

فراغ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    XIDeviceInfo *info;
    صحيح ndevices;
    صحيح old_keyboard_گنتی = 0;
    SDL_KeyboardID *old_keyboards = عدم;
    صحيح new_keyboard_گنتی = 0;
    SDL_KeyboardID *new_keyboards = عدم;
    صحيح old_mouse_گنتی = 0;
    SDL_MouseID *old_mice = عدم;
    صحيح new_mouse_گنتی = 0;
    SDL_MouseID *new_mice = عدم;
    صحيح old_touch_گنتی = 0;
    Uint64 *old_touch_devices = عدم;
    صحيح new_touch_گنتی = 0;
    Uint64 *new_touch_devices = عدم;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(انکڑے->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_گنتی);
    old_mice = SDL_GetMice(&old_mouse_گنتی);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_گنتی);

    لكل (صحيح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        بدل (dev->use) {
        حالة XIMasterKeyboard:
        حالة XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                جوڑو_Device_ID(keyboardID, &new_keyboards, &new_keyboard_گنتی);
                إذا (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_گنتی)) {
                    SDL_جوڑو_Keyboard(keyboardID, dev->name);
                }
            }
            اكسر;
        حالة XIMaster_اشارہ_گر:
            انکڑے->xinput_master_اشارہ_گر_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالة XISlave_اشارہ_گر:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                جوڑو_Device_ID(mouseID, &new_mice, &new_mouse_گنتی);
                إذا (!HasDeviceID(mouseID, old_mice, old_mouse_گنتی)) {
                    SDL_جوڑو_Mouse(mouseID, dev->name);
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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
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
            جوڑو_Device_ID64(touchID, &new_touch_devices, &new_touch_گنتی);
            إذا (!HasDeviceID64(touchID, old_touch_devices, old_touch_گنتی)) {
                إذا (t->منوال == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_اسدھا_RELATIVE;
                } وإلا { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_سدھا;
                }
                SDL_جوڑو_Touch(touchID, touchType, dev->name);
            }
        }
#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    لكل (صحيح i = old_keyboard_گنتی; i--;) {
        إذا (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_گنتی)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    لكل (صحيح i = old_mouse_گنتی; i--;) {
        إذا (!HasDeviceID(old_mice[i], new_mice, new_mouse_گنتی)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    لكل (صحيح i = old_touch_گنتی; i--;) {
        إذا (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_گنتی)) {
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

#جے_انت // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#جے_انت // SDL_VIDEO_DRIVER_X11
