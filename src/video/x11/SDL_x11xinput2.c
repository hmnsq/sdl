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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11pen.h"
#شامل "SDL_x11video.h"
#شامل "SDL_x11xinput2.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_pen_c.h"
#شامل "../../events/SDL_touch_c.h"

#تعریف_کرو MAX_AXIS 16

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
ساکن bool xinput2_initialized;
ساکن bool xinput2_grabbed_touch_raised;
ساکن صحیح xinput2_فعال_touch_گنتی;
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ساکن bool xinput2_scrolling_supported;
ساکن bool xinput2_multitouch_supported;
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ساکن bool xinput2_gesture_supported;
#اگر_ختم

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ساکن صحیح xinput2_opcode;

ساکن Atom xinput2_rel_x_atom;
ساکن Atom xinput2_rel_y_atom;
ساکن Atom xinput2_abs_x_atom;
ساکن Atom xinput2_abs_y_atom;

// Pointer button remapping table
ساکن غیرعلامتی حرف *xinput2_اشارہ_گر_button_map;
ساکن صحیح xinput2_اشارہ_گر_button_map_سائز;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
قسمتعریف ساخت
{
    صحیح نمبر_2;
    صحیح scroll_type;
    دوہرا پچھلا_قدر;
    دوہرا increment;
    bool پچھلا_قدر_valid;
} SDL_XInput2ScrollInfo;

قسمتعریف ساخت
{
    صحیح scroll_info_گنتی;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#اگر_ختم

قسمتعریف ساخت
{
    صحیح نمبر_2[2];
    bool relative[2];
    bool پچھلا_coord_valid[2];
    دوہرا minval[2];
    دوہرا maxval[2];
    دوہرا پچھلا_coords[2];
} SDL_XInput2RelativeDevice;

قسمتعریف ساخت SDL_XInput2DeviceInfo
{
    صحیح device_id;
    SDL_XInput2RelativeDevice relative;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#اگر_ختم
    ساخت SDL_XInput2DeviceInfo *اگلا;
} SDL_XInput2DeviceInfo;

ساکن SDL_XInput2DeviceInfo *xinput2_device_info;

ساکن خالی parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ثابت XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    دوہرا processed_coords[2] = { 0.0, 0.0 };
    صحیح اقدار_i = 0, ملا = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ثابت bool use_raw_vals = mouse->داخلہ_Transform || !mouse->enable_relative_system_scale;

    برائے (صحیح i = 0; i < rawev->valuators.نقاب_len * 8 && ملا < 2; ++i) {
        اگر (!XIMask_Is_سیٹ(rawev->valuators.نقاب, i)) {
            جاری;
        }

        برائے (صحیح j = 0; j < 2; ++j) {
            اگر (rel_dev->نمبر_2[j] == i) {
                ثابت دوہرا current_val = use_raw_vals ? rawev->raw_اقدار[اقدار_i] : rawev->valuators.اقدار[اقدار_i];

                اگر (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ورنہ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    اگر (rel_dev->پچھلا_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->پچھلا_coords[j]; // convert absolute to relative
                    }
                    rel_dev->پچھلا_coords[j] = current_val;
                    rel_dev->پچھلا_coord_valid[j] = true;
                }
                ++ملا;

                توڑو;
            }
        }

        ++اقدار_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    اگر (mouse->relative_منوال && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->وقت, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (اعشاری)processed_coords[0], (اعشاری)processed_coords[1]);
    }
}

ساکن صحیح query_xinput2_نسخہ(Display *display, صحیح major, صحیح minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_نسخہ(display, &major, &minor);
    واپس (major * 1000) + minor;
}

ساکن bool xinput2_نسخہ_atleast(ثابت صحیح نسخہ, ثابت صحیح wantmajor, ثابت صحیح wantminor)
{
    واپس نسخہ >= ((wantmajor * 1000) + wantminor);
}

ساکن SDL_کھڑکی *xinput2_get_sdlwindow(SDL_Video_ڈیٹا *videodata, کھڑکی_2 کھڑکی)
{
    ثابت SDL_کھڑکی_ڈیٹا *windowdata = X11_ڈھونڈو_کھڑکی(videodata, کھڑکی);
    واپس windowdata ? windowdata->کھڑکی : تہی;
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ساکن خالی xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ثابت XIDeviceEvent *xev)
{
    صحیح اقدار_i = 0;
    برائے (صحیح j = 0; j < xev->valuators.نقاب_len * 8; ++j) {
        اگر (!XIMask_Is_سیٹ(xev->valuators.نقاب, j)) {
            جاری;
        }

        برائے (صحیح k = 0; k < scroll_dev->scroll_info_گنتی; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            اگر (info->نمبر_2 == j) {
                ثابت دوہرا current_val = xev->valuators.اقدار[اقدار_i];
                ثابت دوہرا delta = (info->پچھلا_قدر - current_val) / info->increment;
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
                اگر (info->پچھلا_قدر_valid && SDL_fabs(delta) < (دوہرا)SDL_MAX_SINT32 * 0.95) {
                    ثابت دوہرا x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ثابت دوہرا y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->وقت, mouse->focus, (SDL_MouseID)xev->sourceid, (اعشاری)-x, (اعشاری)y, SDL_MOUSEWHEEL_معمول);
                }
                info->پچھلا_قدر = current_val;
                info->پچھلا_قدر_valid = true;
            }
        }

        ++اقدار_i;
    }
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساکن خالی xinput2_normalize_touch_coordinates(SDL_کھڑکی *کھڑکی, دوہرا اندر_x, دوہرا اندر_y, اعشاری *برآمد_x, اعشاری *برآمد_y)
{
    اگر (کھڑکی) {
        اگر (کھڑکی->w == 1) {
            *برآمد_x = 0.5f;
        } ورنہ {
            *برآمد_x = (اعشاری)اندر_x / (کھڑکی->w - 1);
        }
        اگر (کھڑکی->h == 1) {
            *برآمد_y = 0.5f;
        } ورنہ {
            *برآمد_y = (اعشاری)اندر_y / (کھڑکی->h - 1);
        }
    } ورنہ {
        // couldn't find the window...
        *برآمد_x = (اعشاری)اندر_x;
        *برآمد_y = (اعشاری)اندر_y;
    }
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    صحیح نسخہ = 0;
    XIEvent_نقاب eventmask;
    غیرعلامتی حرف نقاب[5] = { 0, 0, 0, 0, 0 };
    صحیح event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    اگر (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        واپس false;
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
    اگر (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(ڈیٹا->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        واپس false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    نسخہ = query_xinput2_نسخہ(ڈیٹا->display, 2, 4);
    اگر (!xinput2_نسخہ_atleast(نسخہ, 2, 0)) {
        واپس false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_نسخہ_atleast(نسخہ, 2, 1);
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_نسخہ_atleast(نسخہ, 2, 2);
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_نسخہ_atleast(نسخہ, 2, 4);
#اگر_ختم

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(ڈیٹا->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(ڈیٹا->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(ڈیٹا->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(ڈیٹا->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(نقاب);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    XISet_نقاب(نقاب, XI_RawMotion);
    XISet_نقاب(نقاب, XI_RawButtonPress);
    XISet_نقاب(نقاب, XI_RawButtonRelease);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    اگر (xinput2_scrolling_supported) {
        XISet_نقاب(نقاب, XI_Motion);
    }
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    اگر (xinput2_multitouch_supported) {
        XISet_نقاب(نقاب, XI_RawTouchBegin);
        XISet_نقاب(نقاب, XI_RawTouchUpdate);
        XISet_نقاب(نقاب, XI_Raw_Touch_انتہا);
    }
#اگر_ختم

    X11_XISelectEvents(ڈیٹا->display, Default_جڑ_کھڑکی(ڈیٹا->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(نقاب);
    eventmask.deviceid = XIAllDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

#اگر_غیر_تعریف_شدہ USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_نقاب(نقاب, XI_کلید_Press);
    XISet_نقاب(نقاب, XI_کلید_Release);
#اگر_ختم

    XISet_نقاب(نقاب, XI_Hierarchy_بدلا);
    X11_XISelectEvents(ڈیٹا->display, Default_جڑ_کھڑکی(ڈیٹا->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_اشارہ_گر_Mapping(_this);

    واپس true;
#ورنہ
    واپس false;
#اگر_ختم
}

خالی X11_QuitXinput2(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    برائے (SDL_XInput2DeviceInfo *i = xinput2_device_info, *اگلا = تہی; i; i = اگلا) {
        اگلا = i->اگلا;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#اگر_ختم
        SDL_free(i);
    }
    xinput2_device_info = تہی;

    SDL_free(xinput2_اشارہ_گر_button_map);
    xinput2_اشارہ_گر_button_map = تہی;
    xinput2_اشارہ_گر_button_map_سائز = 0;
#اگر_ختم
}

خالی X11_Xinput2_Update_اشارہ_گر_Mapping(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    اگر (X11_Xinput2IsInitialized()) {
        SDL_Video_ڈیٹا *vid = _this->اندرونی_2;

        SDL_free(xinput2_اشارہ_گر_button_map);
        xinput2_اشارہ_گر_button_map = تہی;
        xinput2_اشارہ_گر_button_map_سائز = 0;

        xinput2_اشارہ_گر_button_map_سائز = X11_XGet_اشارہ_گر_Mapping(vid->display, تہی, 0);
        اگر (xinput2_اشارہ_گر_button_map_سائز) {
            xinput2_اشارہ_گر_button_map = SDL_calloc(xinput2_اشارہ_گر_button_map_سائز, حجم(غیرعلامتی حرف));
            اگر (xinput2_اشارہ_گر_button_map) {
                xinput2_اشارہ_گر_button_map_سائز = X11_XGet_اشارہ_گر_Mapping(vid->display, xinput2_اشارہ_گر_button_map, xinput2_اشارہ_گر_button_map_سائز);
            } ورنہ {
                xinput2_اشارہ_گر_button_map_سائز = 0;
            }
        }
    }
#اگر_ختم
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ساکن خالی xinput2_remove_device_info(ثابت صحیح device_id)
{
    برائے (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *پچھلا = تہی; devinfo; devinfo = devinfo->اگلا) {
        اگر (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (پچھلا == تہی));
            اگر (!پچھلا) {
                xinput2_device_info = devinfo->اگلا;
            } ورنہ {
                پچھلا->اگلا = devinfo->اگلا;
            }
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#اگر_ختم
            SDL_free(devinfo);
            واپس;
        }
        پچھلا = devinfo;
    }
}

ساکن خالی xinput2_reset_device_valuators(خالی)
{
    برائے (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->اگلا) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        برائے (صحیح i = 0; i < devinfo->scroll.scroll_info_گنتی; ++i) {
            devinfo->scroll.scroll_info[i].پچھلا_قدر_valid = false;
        }
#اگر_ختم
        devinfo->relative.پچھلا_coord_valid[0] = false;
        devinfo->relative.پچھلا_coord_valid[1] = false;
    }
}

ساکن خالی xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, صحیح عدد_classes)
{
    اگر (!devinfo) {
        واپس;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    صحیح rel_axis_اشاریہ = 0;

    SDL_zero(devinfo->relative);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    صحیح allocated_scroll_info_گنتی = devinfo->scroll.scroll_info_گنتی;
    devinfo->scroll.scroll_info_گنتی = 0;
#اگر_ختم

    برائے (صحیح i = 0; i < عدد_classes; ++i) {
        اگر (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ثابت XIValuatorClassInfo *v = (ثابت XIValuatorClassInfo *)classes[i];
            اگر (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_اشاریہ == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.نمبر_2[0] = v->نمبر_2;
                devinfo->relative.relative[0] = (v->منوال == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                اگر (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ورنہ اگر (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ورنہ اگر (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_اشاریہ == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.نمبر_2[1] = v->نمبر_2;
                devinfo->relative.relative[1] = (v->منوال == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                اگر (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ورنہ اگر (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_اشاریہ;
        }
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ورنہ اگر (classes[i]->type == XIScrollClass) {
            ثابت XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            اگر (devinfo->scroll.scroll_info_گنتی == allocated_scroll_info_گنتی) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_گنتی + 2) * حجم(SDL_XInput2ScrollInfo));
                اگر (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_گنتی = 0;
                    devinfo->scroll.scroll_info_گنتی = 0;
                    جاری;
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
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ساکن SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ثابت صحیح device_id)
{
    برائے (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *پچھلا = تہی; devinfo; devinfo = devinfo->اگلا) {
        اگر (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (پچھلا == تہی));
            اگر (پچھلا) { // move this to the front of the list, assuming we'll get more from this one.
                پچھلا->اگلا = devinfo->اگلا;
                devinfo->اگلا = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            واپس devinfo;
        }
        پچھلا = devinfo;
    }

    واپس تہی;
}

ساکن SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_ڈیٹا *videodata, ثابت صحیح device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    اگر (devinfo) {
        واپس devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, حجم(SDL_XInput2DeviceInfo));
    اگر (!devinfo) {
        واپس تہی;
    }

    صحیح i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    اگر (!xidevinfo) {
        SDL_free(devinfo);
        واپس تہی;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->عدد_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->اگلا = xinput2_device_info;
    xinput2_device_info = devinfo;

    واپس devinfo;
}
#اگر_ختم

خالی X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    اگر (cookie->extension != xinput2_opcode) {
        واپس;
    }

    انتخاب (cookie->evtype) {
    حالت XI_Hierarchy_بدلا:
    {
        ثابت XIHierarchyEvent *hierev = (ثابت XIHierarchyEvent *)cookie->ڈیٹا;
        برائے (صحیح i = 0; i < hierev->عدد_info; ++i) {
            // pen stuff...
            اگر ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ورنہ اگر ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_جوڑو_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            اگر (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_بدلا = true;
    } توڑو;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    حالت XI_Device_بدلا:
    {
        ثابت XIDevice_بدلا_Event *dcev = (ثابت XIDevice_بدلا_Event *)cookie->ڈیٹا;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        اگر (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->عدد_classes);
        }
    } توڑو;

    حالت XI_PropertyEvent:
    {
        ثابت XIPropertyEvent *proev = (ثابت XIPropertyEvent *)cookie->ڈیٹا;
        // Handle pen proximity enter/leave
        اگر (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
            SDL_کھڑکی_ڈیٹا *windowdata = X11_ڈھونڈو_کھڑکی(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->کھڑکی : تہی, proev->deviceid);
        }
    } توڑو;

    حالت XI_RawMotion:
    {
        ثابت XIRawEvent *rawev = (ثابت XIRawEvent *)cookie->ڈیٹا;
        ثابت bool is_pen = X11_ڈھونڈو_Pen_By_Device_ID(rawev->sourceid) != تہی;

        videodata->global_mouse_بدلا = true;
        اگر (is_pen) {
            توڑو; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        اگر (!devinfo) {
            توڑو; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } توڑو;

    حالت XI_کلید_Press:
    حالت XI_کلید_Release:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;

#اگر_تعریف_شدہ USE_XINPUT2_KEYBOARD
        SDL_کھڑکی_ڈیٹا *windowdata = X11_ڈھونڈو_کھڑکی(videodata, xev->event);
        XEvent xevent;

        اگر (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            توڑو;
        }

        اگر (cookie->evtype == XI_کلید_Press) {
            xevent.type = کلید_Press;
        } ورنہ {
            xevent.type = کلید_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.کھڑکی = xev->event;
        xevent.xkey.جڑ = xev->جڑ;
        xevent.xkey.subwindow = xev->بچہ;
        xevent.xkey.وقت = xev->وقت;
        xevent.xkey.x = (صحیح)xev->event_x;
        xevent.xkey.y = (صحیح)xev->event_y;
        xevent.xkey.x_جڑ = (صحیح)xev->جڑ_x;
        xevent.xkey.y_جڑ = (صحیح)xev->جڑ_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_کلید_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ورنہ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_آخری_کلید_serial = xev->serial;
        videodata->xinput_آخری_keyboard_device = xev->sourceid;
#اگر_ختم
    } توڑو;

    حالت XI_RawButtonPress:
    حالت XI_RawButtonRelease:
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالت XI_RawTouchBegin:
    حالت XI_RawTouchUpdate:
    حالت XI_Raw_Touch_انتہا:
#اگر_ختم
    {
        videodata->global_mouse_بدلا = true;
    } توڑو;

    حالت XI_ButtonPress:
    حالت XI_ButtonRelease:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
        X11_PenHandle *pen = X11_ڈھونڈو_Pen_By_Device_ID(xev->sourceid);
        صحیح button = xev->detail;
        ثابت bool نیچے_کو = (cookie->evtype == XI_ButtonPress);
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشارہ_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#ورنہ
        bool اشارہ_گر_emulated = false;
#اگر_ختم

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_آخری_button_serial = xev->serial;

        اگر (pen) {
            اگر (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                توڑو;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            اگر (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, کھڑکی, pen->is_eraser, نیچے_کو);
            } ورنہ {
                SDL_SendPenButton(0, pen->pen, کھڑکی, button - 1, نیچے_کو);
            }
        } ورنہ اگر (!اشارہ_گر_emulated) {
            // Otherwise assume a regular mouse
            SDL_کھڑکی_ڈیٹا *windowdata = X11_ڈھونڈو_کھڑکی(videodata, xev->event);
            صحیح x_ticks = 0, y_ticks = 0;

            اگر (xev->deviceid != videodata->xinput_master_اشارہ_گر_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                اگر (SDL_GetMouseFocus() != windowdata->کھڑکی) {
                    توڑو;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                اگر (button <= xinput2_اشارہ_گر_button_map_سائز) {
                    button = xinput2_اشارہ_گر_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            اگر (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                توڑو;
            }

            اگر (نیچے_کو) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (اعشاری)xev->event_x, (اعشاری)xev->event_y, xev->وقت, xev->serial);
            } ورنہ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->وقت);
            }
        }
    } توڑو;

    حالت XI_Enter:
    {
        xinput2_reset_device_valuators();
    } توڑو;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    حالت XI_Motion:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool اشارہ_گر_emulated = (xev->flags & XIPointerEmulated) != 0;
#ورنہ
        bool اشارہ_گر_emulated = false;
#اگر_ختم

        videodata->global_mouse_بدلا = true;

        X11_PenHandle *pen = X11_ڈھونڈو_Pen_By_Device_ID(xev->sourceid);

        اگر (pen) {
            اگر (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                توڑو;
            }

            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, کھڑکی, (اعشاری) xev->event_x, (اعشاری) xev->event_y);

            اعشاری axes[SDL_PEN_AXIS_گنتی];
            X11_PenAxesFromValuators(pen, xev->valuators.اقدار, xev->valuators.نقاب, xev->valuators.نقاب_len, axes);

            برائے (صحیح i = 0; i < SDL_arraysize(axes); i++) {
                اگر (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, کھڑکی, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ورنہ اگر (!اشارہ_گر_emulated) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            اگر (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                اگر (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#اگر_ختم

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
            اگر (کھڑکی && (xev->deviceid == videodata->xinput_master_اشارہ_گر_device || (xinput2_فعال_touch_گنتی && کھڑکی->اندرونی_2->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                اگر (!mouse->relative_منوال) {
                        X11_Process_کامیابی_Test(_this, کھڑکی->اندرونی_2, (اعشاری)xev->event_x, (اعشاری)xev->event_y, false);
                        SDL_SendMouseMotion(0, کھڑکی, SDL_GLOBAL_MOUSE_ID, false, (اعشاری)xev->event_x, (اعشاری)xev->event_y);
                }
            }
        }
    } توڑو;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    حالت XI_TouchBegin:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
        اعشاری x, y;
        ++xinput2_فعال_touch_گنتی;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کھڑکی, SDL_EVENT_FINGER_نیچے_کو, x, y, 1.0);
    } توڑو;

    حالت XI_Touch_انتہا:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
        اعشاری x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        اگر (!--xinput2_فعال_touch_گنتی && کھڑکی && کھڑکی->اندرونی_2->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, کھڑکی, SDL_EVENT_FINGER_اوپر, x, y, 1.0);
    } توڑو;

    حالت XI_TouchUpdate:
    {
        ثابت XIDeviceEvent *xev = (ثابت XIDeviceEvent *)cookie->ڈیٹا;
        اعشاری x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, کھڑکی, x, y, 1.0);
    } توڑو;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    حالت XI_GesturePinchBegin:
    حالت XI_GesturePinchUpdate:
    حالت XI_Gesture_Pinch_انتہا:
    {
        ثابت XIGesturePinchEvent *xev = (ثابت XIGesturePinchEvent *)cookie->ڈیٹا;
        اعشاری x, y;
        SDL_کھڑکی *کھڑکی = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(کھڑکی, xev->event_x, xev->event_y, &x, &y);

        اگر (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, کھڑکی, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ورنہ اگر (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, کھڑکی, (اعشاری)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ورنہ {
            SDL_SendPinch(SDL_EVENT_PINCH_انتہا, 0, کھڑکی, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } توڑو;

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2
}

خالی X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_فعال_touch_گنتی = 0;
#اگر_ختم
}

bool X11_Xinput2_Handles_Motion_For_کھڑکی(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ثابت bool ret = کھڑکی_ڈیٹا_2->xinput2_mouse_enabled &&
                     (!کھڑکی_ڈیٹا_2->mouse_grabbed || xinput2_فعال_touch_گنتی || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    واپس ret;
#ورنہ
    واپس false;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2
}

خالی X11_Xinput2Select(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;
    XIEvent_نقاب eventmask;
    غیرعلامتی حرف نقاب[5] = { 0, 0, 0, 0, 0 };

    اگر (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        واپس;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    اگر (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_نقاب(نقاب, XI_Enter);
    }

    اگر (xinput2_multitouch_supported) {
        XISet_نقاب(نقاب, XI_TouchBegin);
        XISet_نقاب(نقاب, XI_TouchUpdate);
        XISet_نقاب(نقاب, XI_Touch_انتہا);
        XISet_نقاب(نقاب, XI_Motion);
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    اگر (xinput2_gesture_supported) {
        XISet_نقاب(نقاب, XI_GesturePinchBegin);
        XISet_نقاب(نقاب, XI_GesturePinchUpdate);
        XISet_نقاب(نقاب, XI_Gesture_Pinch_انتہا);
    }
#اگر_ختم

    X11_XISelectEvents(ڈیٹا->display, کھڑکی_ڈیٹا_2->xwindow, &eventmask, 1);
#اگر_ختم
}

bool X11_Xinput2IsInitialized(خالی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    واپس xinput2_initialized;
#ورنہ
    واپس false;
#اگر_ختم
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *windowdata = کھڑکی->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    ثابت SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (X11_Xinput2IsInitialized()) {
        XIEvent_نقاب eventmask;
        غیرعلامتی حرف نقاب[4] = { 0, 0, 0, 0 };

        eventmask.نقاب_len = حجم(نقاب);
        eventmask.نقاب = نقاب;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#اگر_تعریف_شدہ USE_XINPUT2_KEYBOARD
        XISet_نقاب(نقاب, XI_کلید_Press);
        XISet_نقاب(نقاب, XI_کلید_Release);
        windowdata->xinput2_keyboard_enabled = true;
#اگر_ختم

        XISet_نقاب(نقاب, XI_ButtonPress);
        XISet_نقاب(نقاب, XI_ButtonRelease);
        XISet_نقاب(نقاب, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_نقاب(نقاب, XI_Enter);
        XISet_نقاب(نقاب, XI_Leave);

        // Hotplugging:
        XISet_نقاب(نقاب, XI_Device_بدلا);
        XISet_نقاب(نقاب, XI_Hierarchy_بدلا);
        XISet_نقاب(نقاب, XI_PropertyEvent); // E.g., when swapping tablet pens

        اگر (X11_XISelectEvents(ڈیٹا->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_داخلہ, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#اگر_ختم

    اگر (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        واپس true;
    }
    واپس false;
}

خالی X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;

    غیرعلامتی حرف نقاب[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_نقاب eventmask;

    اگر (!xinput2_multitouch_supported) {
        واپس;
    }

    mods.modifiers = XIAnyModifier;
    mods.حالت_2 = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.نقاب_len = حجم(نقاب);
    eventmask.نقاب = نقاب;

    XISet_نقاب(eventmask.نقاب, XI_TouchBegin);
    XISet_نقاب(eventmask.نقاب, XI_TouchUpdate);
    XISet_نقاب(eventmask.نقاب, XI_Touch_انتہا);
    XISet_نقاب(eventmask.نقاب, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, ڈیٹا->xwindow, True, &eventmask, 1, &mods);
#اگر_ختم
}

خالی X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;

    XIGrabModifiers mods;

    اگر (!xinput2_multitouch_supported) {
        واپس;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.حالت_2 = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, ڈیٹا->xwindow, 1, &mods);
#اگر_ختم
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2

ساکن خالی جوڑو_Device_ID(Uint32 deviceID, Uint32 **list, صحیح *گنتی)
{
    صحیح new_گنتی = (*گنتی + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        واپس;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}

ساکن bool HasDeviceID(Uint32 deviceID, ثابت Uint32 *list, صحیح گنتی)
{
    برائے (صحیح i = 0; i < گنتی; ++i) {
        اگر (deviceID == list[i]) {
            واپس true;
        }
    }
    واپس false;
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ساکن خالی جوڑو_Device_ID64(Uint64 deviceID, Uint64 **list, صحیح *گنتی)
{
    صحیح new_گنتی = (*گنتی + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_گنتی * حجم(*new_list));
    اگر (!new_list) {
        // Oh well, we'll drop this one
        واپس;
    }
    new_list[new_گنتی - 1] = deviceID;

    *گنتی = new_گنتی;
    *list = new_list;
}
#اگر_ختم

ساکن bool HasDeviceID64(Uint64 deviceID, ثابت Uint64 *list, صحیح گنتی)
{
    برائے (صحیح i = 0; i < گنتی; ++i) {
        اگر (deviceID == list[i]) {
            واپس true;
        }
    }
    واپس false;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2

خالی X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    XIDeviceInfo *info;
    صحیح ndevices;
    صحیح old_keyboard_گنتی = 0;
    SDL_KeyboardID *old_keyboards = تہی;
    صحیح new_keyboard_گنتی = 0;
    SDL_KeyboardID *new_keyboards = تہی;
    صحیح old_mouse_گنتی = 0;
    SDL_MouseID *old_mice = تہی;
    صحیح new_mouse_گنتی = 0;
    SDL_MouseID *new_mice = تہی;
    صحیح old_touch_گنتی = 0;
    Uint64 *old_touch_devices = تہی;
    صحیح new_touch_گنتی = 0;
    Uint64 *new_touch_devices = تہی;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(ڈیٹا->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_گنتی);
    old_mice = SDL_GetMice(&old_mouse_گنتی);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_گنتی);

    برائے (صحیح i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        انتخاب (dev->use) {
        حالت XIMasterKeyboard:
        حالت XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                جوڑو_Device_ID(keyboardID, &new_keyboards, &new_keyboard_گنتی);
                اگر (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_گنتی)) {
                    SDL_جوڑو_Keyboard(keyboardID, dev->name);
                }
            }
            توڑو;
        حالت XIMaster_اشارہ_گر:
            ڈیٹا->xinput_master_اشارہ_گر_device = dev->deviceid;
            SDL_FALLTHROUGH;
        حالت XISlave_اشارہ_گر:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                جوڑو_Device_ID(mouseID, &new_mice, &new_mouse_گنتی);
                اگر (!HasDeviceID(mouseID, old_mice, old_mouse_گنتی)) {
                    SDL_جوڑو_Mouse(mouseID, dev->name);
                }
            }
            توڑو;
        طےشدہ:
            توڑو;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        اگر (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->عدد_classes);
        }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        برائے (صحیح j = 0; j < dev->عدد_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            اگر (class->type != XITouchClass) {
                جاری;
            }

            touchID = (Uint64)t->sourceid;
            جوڑو_Device_ID64(touchID, &new_touch_devices, &new_touch_گنتی);
            اگر (!HasDeviceID64(touchID, old_touch_devices, old_touch_گنتی)) {
                اگر (t->منوال == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_بالواسطہ_RELATIVE;
                } ورنہ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_براہ_راست;
                }
                SDL_جوڑو_Touch(touchID, touchType, dev->name);
            }
        }
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    برائے (صحیح i = old_keyboard_گنتی; i--;) {
        اگر (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_گنتی)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    برائے (صحیح i = old_mouse_گنتی; i--;) {
        اگر (!HasDeviceID(old_mice[i], new_mice, new_mouse_گنتی)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    برائے (صحیح i = old_touch_گنتی; i--;) {
        اگر (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_گنتی)) {
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

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
