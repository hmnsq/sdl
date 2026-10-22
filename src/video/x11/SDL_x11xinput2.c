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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11pen.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_pen_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_AXIS 16

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
ਸਥਿਰ bool xinput2_initialized;
ਸਥਿਰ bool xinput2_grabbed_touch_raised;
ਸਥਿਰ ਪੂਰਨ xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ;
#ਜੇ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ਸਥਿਰ bool xinput2_scrolling_supported;
ਸਥਿਰ bool xinput2_multitouch_supported;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ਸਥਿਰ bool xinput2_gesture_supported;
#ਜੇ_ਅੰਤ

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ਸਥਿਰ ਪੂਰਨ xinput2_opcode;

ਸਥਿਰ Atom xinput2_rel_x_atom;
ਸਥਿਰ Atom xinput2_rel_y_atom;
ਸਥਿਰ Atom xinput2_abs_x_atom;
ਸਥਿਰ Atom xinput2_abs_y_atom;

// Pointer button remapping table
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *xinput2_ਸੂਚਕ_button_map;
ਸਥਿਰ ਪੂਰਨ xinput2_ਸੂਚਕ_button_map_ਮਾਪ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ ਸੰਖਿਆ_2;
    ਪੂਰਨ scroll_type;
    ਦੁੱਗਣਾ prev_ਮੁੱਲ;
    ਦੁੱਗਣਾ increment;
    bool prev_ਮੁੱਲ_valid;
} SDL_XInput2ScrollInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ scroll_info_ਗਿਣਤੀ;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ ਸੰਖਿਆ_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ਦੁੱਗਣਾ minval[2];
    ਦੁੱਗਣਾ maxval[2];
    ਦੁੱਗਣਾ prev_coords[2];
} SDL_XInput2RelativeDevice;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_XInput2DeviceInfo
{
    ਪੂਰਨ device_id;
    SDL_XInput2RelativeDevice relative;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#ਜੇ_ਅੰਤ
    ਬਣਤਰ SDL_XInput2DeviceInfo *ਅਗਲਾ;
} SDL_XInput2DeviceInfo;

ਸਥਿਰ SDL_XInput2DeviceInfo *xinput2_device_info;

ਸਥਿਰ ਖਾਲੀ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ਅਚਲ XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ਦੁੱਗਣਾ processed_coords[2] = { 0.0, 0.0 };
    ਪੂਰਨ ਮੁੱਲਾਂ_i = 0, ਮਿਲਿਆ = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ਅਚਲ bool use_raw_vals = mouse->ਨਿਵੇਸ਼_Transform || !mouse->enable_relative_system_scale;

    ਲਈ (ਪੂਰਨ i = 0; i < rawev->valuators.ਨਕਾਬ_len * 8 && ਮਿਲਿਆ < 2; ++i) {
        ਜੇ (!XIMask_Is_ਸੈੱਟ(rawev->valuators.ਨਕਾਬ, i)) {
            ਜਾਰੀ;
        }

        ਲਈ (ਪੂਰਨ j = 0; j < 2; ++j) {
            ਜੇ (rel_dev->ਸੰਖਿਆ_2[j] == i) {
                ਅਚਲ ਦੁੱਗਣਾ current_val = use_raw_vals ? rawev->raw_ਮੁੱਲਾਂ[ਮੁੱਲਾਂ_i] : rawev->valuators.ਮੁੱਲਾਂ[ਮੁੱਲਾਂ_i];

                ਜੇ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ਨਹੀਂਤਾਂ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ਜੇ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++ਮਿਲਿਆ;

                ਰੋਕੋ;
            }
        }

        ++ਮੁੱਲਾਂ_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ਜੇ (mouse->relative_ਬਹੁਲਕ && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->ਸਮਾਂ, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ਦਸ਼ਮਲਵ)processed_coords[0], (ਦਸ਼ਮਲਵ)processed_coords[1]);
    }
}

ਸਥਿਰ ਪੂਰਨ query_xinput2_ਸੰਸਕਰਣ(Display *display, ਪੂਰਨ major, ਪੂਰਨ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_ਸੰਸਕਰਣ(display, &major, &minor);
    ਵਾਪਸ (major * 1000) + minor;
}

ਸਥਿਰ bool xinput2_ਸੰਸਕਰਣ_atleast(ਅਚਲ ਪੂਰਨ ਸੰਸਕਰਣ, ਅਚਲ ਪੂਰਨ wantmajor, ਅਚਲ ਪੂਰਨ wantminor)
{
    ਵਾਪਸ ਸੰਸਕਰਣ >= ((wantmajor * 1000) + wantminor);
}

ਸਥਿਰ SDL_ਖਿੜਕੀ *xinput2_get_sdlwindow(SDL_Video_ਅੰਕੜੇ *videodata, ਖਿੜਕੀ_2 ਖਿੜਕੀ)
{
    ਅਚਲ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = X11_ਲੱਭੋ_ਖਿੜਕੀ(videodata, ਖਿੜਕੀ);
    ਵਾਪਸ windowdata ? windowdata->ਖਿੜਕੀ : ਨਿਰਾ;
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ਸਥਿਰ ਖਾਲੀ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ਅਚਲ XIDeviceEvent *xev)
{
    ਪੂਰਨ ਮੁੱਲਾਂ_i = 0;
    ਲਈ (ਪੂਰਨ j = 0; j < xev->valuators.ਨਕਾਬ_len * 8; ++j) {
        ਜੇ (!XIMask_Is_ਸੈੱਟ(xev->valuators.ਨਕਾਬ, j)) {
            ਜਾਰੀ;
        }

        ਲਈ (ਪੂਰਨ k = 0; k < scroll_dev->scroll_info_ਗਿਣਤੀ; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ਜੇ (info->ਸੰਖਿਆ_2 == j) {
                ਅਚਲ ਦੁੱਗਣਾ current_val = xev->valuators.ਮੁੱਲਾਂ[ਮੁੱਲਾਂ_i];
                ਅਚਲ ਦੁੱਗਣਾ delta = (info->prev_ਮੁੱਲ - current_val) / info->increment;
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
                ਜੇ (info->prev_ਮੁੱਲ_valid && SDL_fabs(delta) < (ਦੁੱਗਣਾ)SDL_MAX_SINT32 * 0.95) {
                    ਅਚਲ ਦੁੱਗਣਾ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ਅਚਲ ਦੁੱਗਣਾ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->ਸਮਾਂ, mouse->focus, (SDL_MouseID)xev->sourceid, (ਦਸ਼ਮਲਵ)-x, (ਦਸ਼ਮਲਵ)y, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
                }
                info->prev_ਮੁੱਲ = current_val;
                info->prev_ਮੁੱਲ_valid = true;
            }
        }

        ++ਮੁੱਲਾਂ_i;
    }
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ਸਥਿਰ ਖਾਲੀ xinput2_normalize_touch_coordinates(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦੁੱਗਣਾ ਵਿੱਚ_x, ਦੁੱਗਣਾ ਵਿੱਚ_y, ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_x, ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_y)
{
    ਜੇ (ਖਿੜਕੀ) {
        ਜੇ (ਖਿੜਕੀ->w == 1) {
            *ਬਾਹਰਲਾ_x = 0.5f;
        } ਨਹੀਂਤਾਂ {
            *ਬਾਹਰਲਾ_x = (ਦਸ਼ਮਲਵ)ਵਿੱਚ_x / (ਖਿੜਕੀ->w - 1);
        }
        ਜੇ (ਖਿੜਕੀ->h == 1) {
            *ਬਾਹਰਲਾ_y = 0.5f;
        } ਨਹੀਂਤਾਂ {
            *ਬਾਹਰਲਾ_y = (ਦਸ਼ਮਲਵ)ਵਿੱਚ_y / (ਖਿੜਕੀ->h - 1);
        }
    } ਨਹੀਂਤਾਂ {
        // couldn't find the window...
        *ਬਾਹਰਲਾ_x = (ਦਸ਼ਮਲਵ)ਵਿੱਚ_x;
        *ਬਾਹਰਲਾ_y = (ਦਸ਼ਮਲਵ)ਵਿੱਚ_y;
    }
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਪੂਰਨ ਸੰਸਕਰਣ = 0;
    XIEvent_ਨਕਾਬ eventmask;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਕਾਬ[5] = { 0, 0, 0, 0, 0 };
    ਪੂਰਨ event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ਜੇ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        ਵਾਪਸ false;
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
    ਜੇ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(ਅੰਕੜੇ->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        ਵਾਪਸ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    ਸੰਸਕਰਣ = query_xinput2_ਸੰਸਕਰਣ(ਅੰਕੜੇ->display, 2, 4);
    ਜੇ (!xinput2_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 2, 0)) {
        ਵਾਪਸ false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 2, 1);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 2, 2);
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_ਸੰਸਕਰਣ_atleast(ਸੰਸਕਰਣ, 2, 4);
#ਜੇ_ਅੰਤ

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(ਅੰਕੜੇ->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(ਅੰਕੜੇ->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(ਅੰਕੜੇ->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(ਅੰਕੜੇ->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(ਨਕਾਬ);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ਨਕਾਬ_len = ਆਕਾਰ(ਨਕਾਬ);
    eventmask.ਨਕਾਬ = ਨਕਾਬ;

    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_RawMotion);
    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_RawButtonPress);
    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_RawButtonRelease);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ਜੇ (xinput2_scrolling_supported) {
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Motion);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ਜੇ (xinput2_multitouch_supported) {
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_RawTouchBegin);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_RawTouchUpdate);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Raw_Touch_ਸਿਰਾ);
    }
#ਜੇ_ਅੰਤ

    X11_XISelectEvents(ਅੰਕੜੇ->display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(ਅੰਕੜੇ->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(ਨਕਾਬ);
    eventmask.deviceid = XIAllDevices;
    eventmask.ਨਕਾਬ_len = ਆਕਾਰ(ਨਕਾਬ);
    eventmask.ਨਕਾਬ = ਨਕਾਬ;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ਕੁੰਜੀ_Press);
    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ਕੁੰਜੀ_Release);
#ਜੇ_ਅੰਤ

    XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Hierarchy_ਬਦਲਿਆ);
    X11_XISelectEvents(ਅੰਕੜੇ->display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(ਅੰਕੜੇ->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_ਸੂਚਕ_Mapping(_this);

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    ਲਈ (SDL_XInput2DeviceInfo *i = xinput2_device_info, *ਅਗਲਾ = ਨਿਰਾ; i; i = ਅਗਲਾ) {
        ਅਗਲਾ = i->ਅਗਲਾ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#ਜੇ_ਅੰਤ
        SDL_free(i);
    }
    xinput2_device_info = ਨਿਰਾ;

    SDL_free(xinput2_ਸੂਚਕ_button_map);
    xinput2_ਸੂਚਕ_button_map = ਨਿਰਾ;
    xinput2_ਸੂਚਕ_button_map_ਮਾਪ = 0;
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ X11_Xinput2_Update_ਸੂਚਕ_Mapping(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    ਜੇ (X11_Xinput2IsInitialized()) {
        SDL_Video_ਅੰਕੜੇ *vid = _this->ਅੰਦਰੂਨੀ;

        SDL_free(xinput2_ਸੂਚਕ_button_map);
        xinput2_ਸੂਚਕ_button_map = ਨਿਰਾ;
        xinput2_ਸੂਚਕ_button_map_ਮਾਪ = 0;

        xinput2_ਸੂਚਕ_button_map_ਮਾਪ = X11_XGet_ਸੂਚਕ_Mapping(vid->display, ਨਿਰਾ, 0);
        ਜੇ (xinput2_ਸੂਚਕ_button_map_ਮਾਪ) {
            xinput2_ਸੂਚਕ_button_map = SDL_calloc(xinput2_ਸੂਚਕ_button_map_ਮਾਪ, ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ));
            ਜੇ (xinput2_ਸੂਚਕ_button_map) {
                xinput2_ਸੂਚਕ_button_map_ਮਾਪ = X11_XGet_ਸੂਚਕ_Mapping(vid->display, xinput2_ਸੂਚਕ_button_map, xinput2_ਸੂਚਕ_button_map_ਮਾਪ);
            } ਨਹੀਂਤਾਂ {
                xinput2_ਸੂਚਕ_button_map_ਮਾਪ = 0;
            }
        }
    }
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ਸਥਿਰ ਖਾਲੀ xinput2_remove_device_info(ਅਚਲ ਪੂਰਨ device_id)
{
    ਲਈ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ਨਿਰਾ; devinfo; devinfo = devinfo->ਅਗਲਾ) {
        ਜੇ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ਨਿਰਾ));
            ਜੇ (!prev) {
                xinput2_device_info = devinfo->ਅਗਲਾ;
            } ਨਹੀਂਤਾਂ {
                prev->ਅਗਲਾ = devinfo->ਅਗਲਾ;
            }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#ਜੇ_ਅੰਤ
            SDL_free(devinfo);
            ਵਾਪਸ;
        }
        prev = devinfo;
    }
}

ਸਥਿਰ ਖਾਲੀ xinput2_reset_device_valuators(ਖਾਲੀ)
{
    ਲਈ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->ਅਗਲਾ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ਲਈ (ਪੂਰਨ i = 0; i < devinfo->scroll.scroll_info_ਗਿਣਤੀ; ++i) {
            devinfo->scroll.scroll_info[i].prev_ਮੁੱਲ_valid = false;
        }
#ਜੇ_ਅੰਤ
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ਸਥਿਰ ਖਾਲੀ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, ਪੂਰਨ ਅੰਕ_classes)
{
    ਜੇ (!devinfo) {
        ਵਾਪਸ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    ਪੂਰਨ rel_axis_ਸੂਚਕਾਂਕ = 0;

    SDL_zero(devinfo->relative);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    ਪੂਰਨ allocated_scroll_info_ਗਿਣਤੀ = devinfo->scroll.scroll_info_ਗਿਣਤੀ;
    devinfo->scroll.scroll_info_ਗਿਣਤੀ = 0;
#ਜੇ_ਅੰਤ

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_classes; ++i) {
        ਜੇ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ਅਚਲ XIValuatorClassInfo *v = (ਅਚਲ XIValuatorClassInfo *)classes[i];
            ਜੇ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_ਸੂਚਕਾਂਕ == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.ਸੰਖਿਆ_2[0] = v->ਸੰਖਿਆ_2;
                devinfo->relative.relative[0] = (v->ਬਹੁਲਕ == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ਜੇ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ਨਹੀਂਤਾਂ ਜੇ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ਨਹੀਂਤਾਂ ਜੇ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_ਸੂਚਕਾਂਕ == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.ਸੰਖਿਆ_2[1] = v->ਸੰਖਿਆ_2;
                devinfo->relative.relative[1] = (v->ਬਹੁਲਕ == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ਜੇ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ਨਹੀਂਤਾਂ ਜੇ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_ਸੂਚਕਾਂਕ;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ਨਹੀਂਤਾਂ ਜੇ (classes[i]->type == XIScrollClass) {
            ਅਚਲ XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ਜੇ (devinfo->scroll.scroll_info_ਗਿਣਤੀ == allocated_scroll_info_ਗਿਣਤੀ) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_ਗਿਣਤੀ + 2) * ਆਕਾਰ(SDL_XInput2ScrollInfo));
                ਜੇ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_ਗਿਣਤੀ = 0;
                    devinfo->scroll.scroll_info_ਗਿਣਤੀ = 0;
                    ਜਾਰੀ;
                }

                allocated_scroll_info_ਗਿਣਤੀ += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_ਗਿਣਤੀ];
            ++devinfo->scroll.scroll_info_ਗਿਣਤੀ;

            SDL_zerop(scroll_info);
            scroll_info->ਸੰਖਿਆ_2 = s->ਸੰਖਿਆ_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ਸਥਿਰ SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ਅਚਲ ਪੂਰਨ device_id)
{
    ਲਈ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ਨਿਰਾ; devinfo; devinfo = devinfo->ਅਗਲਾ) {
        ਜੇ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ਨਿਰਾ));
            ਜੇ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->ਅਗਲਾ = devinfo->ਅਗਲਾ;
                devinfo->ਅਗਲਾ = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            ਵਾਪਸ devinfo;
        }
        prev = devinfo;
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_ਅੰਕੜੇ *videodata, ਅਚਲ ਪੂਰਨ device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ਜੇ (devinfo) {
        ਵਾਪਸ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, ਆਕਾਰ(SDL_XInput2DeviceInfo));
    ਜੇ (!devinfo) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਪੂਰਨ i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ਜੇ (!xidevinfo) {
        SDL_free(devinfo);
        ਵਾਪਸ ਨਿਰਾ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->ਅੰਕ_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->ਅਗਲਾ = xinput2_device_info;
    xinput2_device_info = devinfo;

    ਵਾਪਸ devinfo;
}
#ਜੇ_ਅੰਤ

ਖਾਲੀ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (cookie->extension != xinput2_opcode) {
        ਵਾਪਸ;
    }

    ਚੋਣ (cookie->evtype) {
    ਹਾਲਤ XI_Hierarchy_ਬਦਲਿਆ:
    {
        ਅਚਲ XIHierarchyEvent *hierev = (ਅਚਲ XIHierarchyEvent *)cookie->ਅੰਕੜੇ;
        ਲਈ (ਪੂਰਨ i = 0; i < hierev->ਅੰਕ_info; ++i) {
            // pen stuff...
            ਜੇ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ਨਹੀਂਤਾਂ ਜੇ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_ਜੋੜੋ_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ਜੇ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_ਬਦਲਿਆ = true;
    } ਰੋਕੋ;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    ਹਾਲਤ XI_Device_ਬਦਲਿਆ:
    {
        ਅਚਲ XIDevice_ਬਦਲਿਆ_Event *dcev = (ਅਚਲ XIDevice_ਬਦਲਿਆ_Event *)cookie->ਅੰਕੜੇ;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ਜੇ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->ਅੰਕ_classes);
        }
    } ਰੋਕੋ;

    ਹਾਲਤ XI_PropertyEvent:
    {
        ਅਚਲ XIPropertyEvent *proev = (ਅਚਲ XIPropertyEvent *)cookie->ਅੰਕੜੇ;
        // Handle pen proximity enter/leave
        ਜੇ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = X11_ਲੱਭੋ_ਖਿੜਕੀ(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->ਖਿੜਕੀ : ਨਿਰਾ, proev->deviceid);
        }
    } ਰੋਕੋ;

    ਹਾਲਤ XI_RawMotion:
    {
        ਅਚਲ XIRawEvent *rawev = (ਅਚਲ XIRawEvent *)cookie->ਅੰਕੜੇ;
        ਅਚਲ bool is_pen = X11_ਲੱਭੋ_Pen_By_Device_ID(rawev->sourceid) != ਨਿਰਾ;

        videodata->global_mouse_ਬਦਲਿਆ = true;
        ਜੇ (is_pen) {
            ਰੋਕੋ; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ਜੇ (!devinfo) {
            ਰੋਕੋ; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ਰੋਕੋ;

    ਹਾਲਤ XI_ਕੁੰਜੀ_Press:
    ਹਾਲਤ XI_ਕੁੰਜੀ_Release:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_XINPUT2_KEYBOARD
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = X11_ਲੱਭੋ_ਖਿੜਕੀ(videodata, xev->event);
        XEvent xevent;

        ਜੇ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ਰੋਕੋ;
        }

        ਜੇ (cookie->evtype == XI_ਕੁੰਜੀ_Press) {
            xevent.type = ਕੁੰਜੀ_Press;
        } ਨਹੀਂਤਾਂ {
            xevent.type = ਕੁੰਜੀ_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.ਖਿੜਕੀ = xev->event;
        xevent.xkey.ਜੜ੍ਹ = xev->ਜੜ੍ਹ;
        xevent.xkey.subwindow = xev->ਬੱਚਾ;
        xevent.xkey.ਸਮਾਂ = xev->ਸਮਾਂ;
        xevent.xkey.x = (ਪੂਰਨ)xev->event_x;
        xevent.xkey.y = (ਪੂਰਨ)xev->event_y;
        xevent.xkey.x_ਜੜ੍ਹ = (ਪੂਰਨ)xev->ਜੜ੍ਹ_x;
        xevent.xkey.y_ਜੜ੍ਹ = (ਪੂਰਨ)xev->ਜੜ੍ਹ_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_ਕੁੰਜੀ_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ਨਹੀਂਤਾਂ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_ਆਖਰੀ_ਕੁੰਜੀ_serial = xev->serial;
        videodata->xinput_ਆਖਰੀ_keyboard_device = xev->sourceid;
#ਜੇ_ਅੰਤ
    } ਰੋਕੋ;

    ਹਾਲਤ XI_RawButtonPress:
    ਹਾਲਤ XI_RawButtonRelease:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ਹਾਲਤ XI_RawTouchBegin:
    ਹਾਲਤ XI_RawTouchUpdate:
    ਹਾਲਤ XI_Raw_Touch_ਸਿਰਾ:
#ਜੇ_ਅੰਤ
    {
        videodata->global_mouse_ਬਦਲਿਆ = true;
    } ਰੋਕੋ;

    ਹਾਲਤ XI_ButtonPress:
    ਹਾਲਤ XI_ButtonRelease:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
        X11_PenHandle *pen = X11_ਲੱਭੋ_Pen_By_Device_ID(xev->sourceid);
        ਪੂਰਨ button = xev->detail;
        ਅਚਲ bool ਥੱਲੇ = (cookie->evtype == XI_ButtonPress);
#ਜੇ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool ਸੂਚਕ_emulated = (xev->flags & XIPointerEmulated) != 0;
#ਨਹੀਂਤਾਂ
        bool ਸੂਚਕ_emulated = false;
#ਜੇ_ਅੰਤ

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_ਆਖਰੀ_button_serial = xev->serial;

        ਜੇ (pen) {
            ਜੇ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ਰੋਕੋ;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
            ਜੇ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, ਖਿੜਕੀ, pen->is_eraser, ਥੱਲੇ);
            } ਨਹੀਂਤਾਂ {
                SDL_SendPenButton(0, pen->pen, ਖਿੜਕੀ, button - 1, ਥੱਲੇ);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (!ਸੂਚਕ_emulated) {
            // Otherwise assume a regular mouse
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = X11_ਲੱਭੋ_ਖਿੜਕੀ(videodata, xev->event);
            ਪੂਰਨ x_ticks = 0, y_ticks = 0;

            ਜੇ (xev->deviceid != videodata->xinput_master_ਸੂਚਕ_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ਜੇ (SDL_GetMouseFocus() != windowdata->ਖਿੜਕੀ) {
                    ਰੋਕੋ;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ਜੇ (button <= xinput2_ਸੂਚਕ_button_map_ਮਾਪ) {
                    button = xinput2_ਸੂਚਕ_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ਜੇ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ਰੋਕੋ;
            }

            ਜੇ (ਥੱਲੇ) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ਦਸ਼ਮਲਵ)xev->event_x, (ਦਸ਼ਮਲਵ)xev->event_y, xev->ਸਮਾਂ, xev->serial);
            } ਨਹੀਂਤਾਂ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->ਸਮਾਂ);
            }
        }
    } ਰੋਕੋ;

    ਹਾਲਤ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ਰੋਕੋ;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    ਹਾਲਤ XI_Motion:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
#ਜੇ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool ਸੂਚਕ_emulated = (xev->flags & XIPointerEmulated) != 0;
#ਨਹੀਂਤਾਂ
        bool ਸੂਚਕ_emulated = false;
#ਜੇ_ਅੰਤ

        videodata->global_mouse_ਬਦਲਿਆ = true;

        X11_PenHandle *pen = X11_ਲੱਭੋ_Pen_By_Device_ID(xev->sourceid);

        ਜੇ (pen) {
            ਜੇ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ਰੋਕੋ;
            }

            SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ) xev->event_x, (ਦਸ਼ਮਲਵ) xev->event_y);

            ਦਸ਼ਮਲਵ axes[SDL_PEN_AXIS_ਗਿਣਤੀ];
            X11_PenAxesFromValuators(pen, xev->valuators.ਮੁੱਲਾਂ, xev->valuators.ਨਕਾਬ, xev->valuators.ਨਕਾਬ_len, axes);

            ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(axes); i++) {
                ਜੇ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, ਖਿੜਕੀ, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ਨਹੀਂਤਾਂ ਜੇ (!ਸੂਚਕ_emulated) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ਜੇ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ਜੇ (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#ਜੇ_ਅੰਤ

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
            ਜੇ (ਖਿੜਕੀ && (xev->deviceid == videodata->xinput_master_ਸੂਚਕ_device || (xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ਜੇ (!mouse->relative_ਬਹੁਲਕ) {
                        X11_Process_ਪ੍ਰਾਪਤੀ_Test(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ, (ਦਸ਼ਮਲਵ)xev->event_x, (ਦਸ਼ਮਲਵ)xev->event_y, false);
                        SDL_SendMouseMotion(0, ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, (ਦਸ਼ਮਲਵ)xev->event_x, (ਦਸ਼ਮਲਵ)xev->event_y);
                }
            }
        }
    } ਰੋਕੋ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ਹਾਲਤ XI_TouchBegin:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
        ਦਸ਼ਮਲਵ x, y;
        ++xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ;
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ਖਿੜਕੀ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, ਖਿੜਕੀ, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, 1.0);
    } ਰੋਕੋ;

    ਹਾਲਤ XI_Touch_ਸਿਰਾ:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
        ਦਸ਼ਮਲਵ x, y;
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
        ਜੇ (!--xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ && ਖਿੜਕੀ && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(ਖਿੜਕੀ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, ਖਿੜਕੀ, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, 1.0);
    } ਰੋਕੋ;

    ਹਾਲਤ XI_TouchUpdate:
    {
        ਅਚਲ XIDeviceEvent *xev = (ਅਚਲ XIDeviceEvent *)cookie->ਅੰਕੜੇ;
        ਦਸ਼ਮਲਵ x, y;
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ਖਿੜਕੀ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, ਖਿੜਕੀ, x, y, 1.0);
    } ਰੋਕੋ;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ਹਾਲਤ XI_GesturePinchBegin:
    ਹਾਲਤ XI_GesturePinchUpdate:
    ਹਾਲਤ XI_Gesture_Pinch_ਸਿਰਾ:
    {
        ਅਚਲ XIGesturePinchEvent *xev = (ਅਚਲ XIGesturePinchEvent *)cookie->ਅੰਕੜੇ;
        ਦਸ਼ਮਲਵ x, y;
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ਖਿੜਕੀ, xev->event_x, xev->event_y, &x, &y);

        ਜੇ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, ਖਿੜਕੀ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ਨਹੀਂਤਾਂ ਜੇ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ਨਹੀਂਤਾਂ {
            SDL_SendPinch(SDL_EVENT_PINCH_ਸਿਰਾ, 0, ਖਿੜਕੀ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ਰੋਕੋ;

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ਖਾਲੀ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ = 0;
#ਜੇ_ਅੰਤ
}

bool X11_Xinput2_Handles_Motion_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ਅਚਲ bool ret = ਖਿੜਕੀ_ਅੰਕੜੇ_2->xinput2_mouse_enabled &&
                     (!ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_grabbed || xinput2_ਸਰਗਰਮ_touch_ਗਿਣਤੀ || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    ਵਾਪਸ ret;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ਖਾਲੀ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    XIEvent_ਨਕਾਬ eventmask;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਕਾਬ[5] = { 0, 0, 0, 0, 0 };

    ਜੇ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        ਵਾਪਸ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ਨਕਾਬ_len = ਆਕਾਰ(ਨਕਾਬ);
    eventmask.ਨਕਾਬ = ਨਕਾਬ;

    ਜੇ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Enter);
    }

    ਜੇ (xinput2_multitouch_supported) {
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_TouchBegin);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_TouchUpdate);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Touch_ਸਿਰਾ);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Motion);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ਜੇ (xinput2_gesture_supported) {
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_GesturePinchBegin);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_GesturePinchUpdate);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Gesture_Pinch_ਸਿਰਾ);
    }
#ਜੇ_ਅੰਤ

    X11_XISelectEvents(ਅੰਕੜੇ->display, ਖਿੜਕੀ_ਅੰਕੜੇ_2->xwindow, &eventmask, 1);
#ਜੇ_ਅੰਤ
}

bool X11_Xinput2IsInitialized(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    ਵਾਪਸ xinput2_initialized;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (X11_Xinput2IsInitialized()) {
        XIEvent_ਨਕਾਬ eventmask;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਕਾਬ[4] = { 0, 0, 0, 0 };

        eventmask.ਨਕਾਬ_len = ਆਕਾਰ(ਨਕਾਬ);
        eventmask.ਨਕਾਬ = ਨਕਾਬ;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_XINPUT2_KEYBOARD
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ਕੁੰਜੀ_Press);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ਕੁੰਜੀ_Release);
        windowdata->xinput2_keyboard_enabled = true;
#ਜੇ_ਅੰਤ

        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ButtonPress);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_ButtonRelease);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Enter);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Leave);

        // Hotplugging:
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Device_ਬਦਲਿਆ);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_Hierarchy_ਬਦਲਿਆ);
        XISet_ਨਕਾਬ(ਨਕਾਬ, XI_PropertyEvent); // E.g., when swapping tablet pens

        ਜੇ (X11_XISelectEvents(ਅੰਕੜੇ->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਖਾਲੀ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਨਕਾਬ[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_ਨਕਾਬ eventmask;

    ਜੇ (!xinput2_multitouch_supported) {
        ਵਾਪਸ;
    }

    mods.modifiers = XIAnyModifier;
    mods.ਸਥਿਤੀ = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.ਨਕਾਬ_len = ਆਕਾਰ(ਨਕਾਬ);
    eventmask.ਨਕਾਬ = ਨਕਾਬ;

    XISet_ਨਕਾਬ(eventmask.ਨਕਾਬ, XI_TouchBegin);
    XISet_ਨਕਾਬ(eventmask.ਨਕਾਬ, XI_TouchUpdate);
    XISet_ਨਕਾਬ(eventmask.ਨਕਾਬ, XI_Touch_ਸਿਰਾ);
    XISet_ਨਕਾਬ(eventmask.ਨਕਾਬ, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, ਅੰਕੜੇ->xwindow, True, &eventmask, 1, &mods);
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;

    XIGrabModifiers mods;

    ਜੇ (!xinput2_multitouch_supported) {
        ਵਾਪਸ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.ਸਥਿਤੀ = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, ਅੰਕੜੇ->xwindow, 1, &mods);
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2

ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Device_ID(Uint32 deviceID, Uint32 **list, ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਪੂਰਨ new_ਗਿਣਤੀ = (*ਗਿਣਤੀ_2 + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ਗਿਣਤੀ * ਆਕਾਰ(*new_list));
    ਜੇ (!new_list) {
        // Oh well, we'll drop this one
        ਵਾਪਸ;
    }
    new_list[new_ਗਿਣਤੀ - 1] = deviceID;

    *ਗਿਣਤੀ_2 = new_ਗਿਣਤੀ;
    *list = new_list;
}

ਸਥਿਰ bool HasDeviceID(Uint32 deviceID, ਅਚਲ Uint32 *list, ਪੂਰਨ ਗਿਣਤੀ_2)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; ++i) {
        ਜੇ (deviceID == list[i]) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Device_ID64(Uint64 deviceID, Uint64 **list, ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਪੂਰਨ new_ਗਿਣਤੀ = (*ਗਿਣਤੀ_2 + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_ਗਿਣਤੀ * ਆਕਾਰ(*new_list));
    ਜੇ (!new_list) {
        // Oh well, we'll drop this one
        ਵਾਪਸ;
    }
    new_list[new_ਗਿਣਤੀ - 1] = deviceID;

    *ਗਿਣਤੀ_2 = new_ਗਿਣਤੀ;
    *list = new_list;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool HasDeviceID64(Uint64 deviceID, ਅਚਲ Uint64 *list, ਪੂਰਨ ਗਿਣਤੀ_2)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; ++i) {
        ਜੇ (deviceID == list[i]) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2

ਖਾਲੀ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    XIDeviceInfo *info;
    ਪੂਰਨ ndevices;
    ਪੂਰਨ old_keyboard_ਗਿਣਤੀ = 0;
    SDL_KeyboardID *old_keyboards = ਨਿਰਾ;
    ਪੂਰਨ new_keyboard_ਗਿਣਤੀ = 0;
    SDL_KeyboardID *new_keyboards = ਨਿਰਾ;
    ਪੂਰਨ old_mouse_ਗਿਣਤੀ = 0;
    SDL_MouseID *old_mice = ਨਿਰਾ;
    ਪੂਰਨ new_mouse_ਗਿਣਤੀ = 0;
    SDL_MouseID *new_mice = ਨਿਰਾ;
    ਪੂਰਨ old_touch_ਗਿਣਤੀ = 0;
    Uint64 *old_touch_devices = ਨਿਰਾ;
    ਪੂਰਨ new_touch_ਗਿਣਤੀ = 0;
    Uint64 *new_touch_devices = ਨਿਰਾ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(ਅੰਕੜੇ->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ਗਿਣਤੀ);
    old_mice = SDL_GetMice(&old_mouse_ਗਿਣਤੀ);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_ਗਿਣਤੀ);

    ਲਈ (ਪੂਰਨ i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        ਚੋਣ (dev->use) {
        ਹਾਲਤ XIMasterKeyboard:
        ਹਾਲਤ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                ਜੋੜੋ_Device_ID(keyboardID, &new_keyboards, &new_keyboard_ਗਿਣਤੀ);
                ਜੇ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ਗਿਣਤੀ)) {
                    SDL_ਜੋੜੋ_Keyboard(keyboardID, dev->name);
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ XIMaster_ਸੂਚਕ:
            ਅੰਕੜੇ->xinput_master_ਸੂਚਕ_device = dev->deviceid;
            SDL_FALLTHROUGH;
        ਹਾਲਤ XISlave_ਸੂਚਕ:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                ਜੋੜੋ_Device_ID(mouseID, &new_mice, &new_mouse_ਗਿਣਤੀ);
                ਜੇ (!HasDeviceID(mouseID, old_mice, old_mouse_ਗਿਣਤੀ)) {
                    SDL_ਜੋੜੋ_Mouse(mouseID, dev->name);
                }
            }
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ਜੇ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->ਅੰਕ_classes);
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        ਲਈ (ਪੂਰਨ j = 0; j < dev->ਅੰਕ_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ਜੇ (class->type != XITouchClass) {
                ਜਾਰੀ;
            }

            touchID = (Uint64)t->sourceid;
            ਜੋੜੋ_Device_ID64(touchID, &new_touch_devices, &new_touch_ਗਿਣਤੀ);
            ਜੇ (!HasDeviceID64(touchID, old_touch_devices, old_touch_ਗਿਣਤੀ)) {
                ਜੇ (t->ਬਹੁਲਕ == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_ਅਸਿੱਧਾ_RELATIVE;
                } ਨਹੀਂਤਾਂ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_ਸਿੱਧਾ;
                }
                SDL_ਜੋੜੋ_Touch(touchID, touchType, dev->name);
            }
        }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    ਲਈ (ਪੂਰਨ i = old_keyboard_ਗਿਣਤੀ; i--;) {
        ਜੇ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ਗਿਣਤੀ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ਲਈ (ਪੂਰਨ i = old_mouse_ਗਿਣਤੀ; i--;) {
        ਜੇ (!HasDeviceID(old_mice[i], new_mice, new_mouse_ਗਿਣਤੀ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    ਲਈ (ਪੂਰਨ i = old_touch_ਗਿਣਤੀ; i--;) {
        ਜੇ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_ਗਿਣਤੀ)) {
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

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
