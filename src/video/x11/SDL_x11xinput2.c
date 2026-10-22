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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11pen.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_AXIS 16

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
ಸ್ಥಿರ bool xinput2_initialized;
ಸ್ಥಿರ bool xinput2_grabbed_touch_raised;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;
#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
ಸ್ಥಿರ bool xinput2_scrolling_supported;
ಸ್ಥಿರ bool xinput2_multitouch_supported;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
ಸ್ಥಿರ bool xinput2_gesture_supported;
#ಆದರೆ_ಅಂತ್ಯ

/* Opcode returned X11_XQueryExtension
 * It will be used in event processing
 * to know that the event came from
 * this extension */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ xinput2_opcode;

ಸ್ಥಿರ Atom xinput2_rel_x_atom;
ಸ್ಥಿರ Atom xinput2_rel_y_atom;
ಸ್ಥಿರ Atom xinput2_abs_x_atom;
ಸ್ಥಿರ Atom xinput2_abs_y_atom;

// Pointer button remapping table
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *xinput2_ಸೂಚಕ_button_map;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ_2;
    ಪೂರ್ಣಾಂಕ scroll_type;
    ದ್ವಿಗುಣ prev_ಮೌಲ್ಯ;
    ದ್ವಿಗುಣ increment;
    bool prev_ಮೌಲ್ಯ_valid;
} SDL_XInput2ScrollInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ scroll_info_ಎಣಿಕೆ;
    SDL_XInput2ScrollInfo *scroll_info;
} SDL_XInput2ScrollableDevice;
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ_2[2];
    bool relative[2];
    bool prev_coord_valid[2];
    ದ್ವಿಗುಣ minval[2];
    ದ್ವಿಗುಣ maxval[2];
    ದ್ವಿಗುಣ prev_coords[2];
} SDL_XInput2RelativeDevice;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_XInput2DeviceInfo
{
    ಪೂರ್ಣಾಂಕ device_id;
    SDL_XInput2RelativeDevice relative;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    SDL_XInput2ScrollableDevice scroll;
#ಆದರೆ_ಅಂತ್ಯ
    ರಚನೆ SDL_XInput2DeviceInfo *ಮುಂದಿನ;
} SDL_XInput2DeviceInfo;

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_device_info;

ಸ್ಥಿರ ಶೂನ್ಯ parse_relative_valuators(SDL_XInput2RelativeDevice *rel_dev, ಸ್ಥಿರಾಂಕ XIRawEvent *rawev)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    ದ್ವಿಗುಣ processed_coords[2] = { 0.0, 0.0 };
    ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯಗಳು_i = 0, ಸಿಕ್ಕಿತು = 0;

    // Use the raw values if a custom transform function is set, or the relative system scale hint is unset.
    ಸ್ಥಿರಾಂಕ bool use_raw_vals = mouse->ಒಳಹರಿವು_Transform || !mouse->enable_relative_system_scale;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < rawev->valuators.ಮುಖವಾಡ_len * 8 && ಸಿಕ್ಕಿತು < 2; ++i) {
        ಆದರೆ (!XIMask_Is_ಗಣ(rawev->valuators.ಮುಖವಾಡ, i)) {
            ಮುಂದುವರಿ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < 2; ++j) {
            ಆದರೆ (rel_dev->ಸಂಖ್ಯೆ_2[j] == i) {
                ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ current_val = use_raw_vals ? rawev->raw_ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i] : rawev->valuators.ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i];

                ಆದರೆ (rel_dev->relative[j]) {
                    processed_coords[j] = current_val;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    // The first absolute value is meaningless by itself and must be ignored, as it only establishes a baseline for future deltas.
                    ಆದರೆ (rel_dev->prev_coord_valid[j]) {
                        processed_coords[j] = current_val - rel_dev->prev_coords[j]; // convert absolute to relative
                    }
                    rel_dev->prev_coords[j] = current_val;
                    rel_dev->prev_coord_valid[j] = true;
                }
                ++ಸಿಕ್ಕಿತು;

                ನಿಲ್ಲಿಸು;
            }
        }

        ++ಮೌಲ್ಯಗಳು_i;
    }

    // Relative mouse motion is delivered to the window with keyboard focus
    ಆದರೆ (mouse->relative_ಬಹುಲಕ && SDL_GetKeyboardFocus()) {
        SDL_SendMouseMotion(rawev->ಸಮಯ, mouse->focus, (SDL_MouseID)rawev->sourceid, true, (ದಶಮಾಂಶ)processed_coords[0], (ದಶಮಾಂಶ)processed_coords[1]);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ query_xinput2_ಆವೃತ್ತಿ(Display *display, ಪೂರ್ಣಾಂಕ major, ಪೂರ್ಣಾಂಕ minor)
{
    // We don't care if this fails, so long as it sets major/minor on it's way out the door.
    X11_XIQuery_ಆವೃತ್ತಿ(display, &major, &minor);
    ಹಿಂತಿರುಗಿ (major * 1000) + minor;
}

ಸ್ಥಿರ bool xinput2_ಆವೃತ್ತಿ_atleast(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantmajor, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ wantminor)
{
    ಹಿಂತಿರುಗಿ ಆವೃತ್ತಿ >= ((wantmajor * 1000) + wantminor);
}

ಸ್ಥಿರ SDL_ಕಿಟಕಿ *xinput2_get_sdlwindow(SDL_Video_ದತ್ತಾಂಶ *videodata, ಕಿಟಕಿ_2 ಕಿಟಕಿ)
{
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(videodata, ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ windowdata ? windowdata->ಕಿಟಕಿ : ಖಾಲಿ;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_parse_scrollable_valuators(SDL_XInput2ScrollableDevice *scroll_dev, ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev)
{
    ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯಗಳು_i = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < xev->valuators.ಮುಖವಾಡ_len * 8; ++j) {
        ಆದರೆ (!XIMask_Is_ಗಣ(xev->valuators.ಮುಖವಾಡ, j)) {
            ಮುಂದುವರಿ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < scroll_dev->scroll_info_ಎಣಿಕೆ; ++k) {
            SDL_XInput2ScrollInfo *info = &scroll_dev->scroll_info[k];
            ಆದರೆ (info->ಸಂಖ್ಯೆ_2 == j) {
                ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ current_val = xev->valuators.ಮೌಲ್ಯಗಳು[ಮೌಲ್ಯಗಳು_i];
                ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ delta = (info->prev_ಮೌಲ್ಯ - current_val) / info->increment;
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
                ಆದರೆ (info->prev_ಮೌಲ್ಯ_valid && SDL_fabs(delta) < (ದ್ವಿಗುಣ)SDL_MAX_SINT32 * 0.95) {
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ x = info->scroll_type == XIScrollTypeHorizontal ? delta : 0;
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ y = info->scroll_type == XIScrollTypeVertical ? delta : 0;

                    SDL_Mouse *mouse = SDL_GetMouse();
                    SDL_SendMouseWheel(xev->ಸಮಯ, mouse->focus, (SDL_MouseID)xev->sourceid, (ದಶಮಾಂಶ)-x, (ದಶಮಾಂಶ)y, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
                }
                info->prev_ಮೌಲ್ಯ = current_val;
                info->prev_ಮೌಲ್ಯ_valid = true;
            }
        }

        ++ಮೌಲ್ಯಗಳು_i;
    }
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_normalize_touch_coordinates(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದ್ವಿಗುಣ ಒಳ_x, ದ್ವಿಗುಣ ಒಳ_y, ದಶಮಾಂಶ *ಹೊರಹೋಗು_x, ದಶಮಾಂಶ *ಹೊರಹೋಗು_y)
{
    ಆದರೆ (ಕಿಟಕಿ) {
        ಆದರೆ (ಕಿಟಕಿ->w == 1) {
            *ಹೊರಹೋಗು_x = 0.5f;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *ಹೊರಹೋಗು_x = (ದಶಮಾಂಶ)ಒಳ_x / (ಕಿಟಕಿ->w - 1);
        }
        ಆದರೆ (ಕಿಟಕಿ->h == 1) {
            *ಹೊರಹೋಗು_y = 0.5f;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *ಹೊರಹೋಗು_y = (ದಶಮಾಂಶ)ಒಳ_y / (ಕಿಟಕಿ->h - 1);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // couldn't find the window...
        *ಹೊರಹೋಗು_x = (ದಶಮಾಂಶ)ಒಳ_x;
        *ಹೊರಹೋಗು_y = (ದಶಮಾಂಶ)ಒಳ_y;
    }
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

bool X11_InitXinput2(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಪೂರ್ಣಾಂಕ ಆವೃತ್ತಿ = 0;
    XIEvent_ಮುಖವಾಡ eventmask;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಮುಖವಾಡ[5] = { 0, 0, 0, 0, 0 };
    ಪೂರ್ಣಾಂಕ event, err;

    /* XInput2 is required for relative mouse mode, so you probably want to leave this enabled */
    ಆದರೆ (!SDL_GetHintBoolean("SDL_VIDEO_X11_XINPUT2", true)) {
        ಹಿಂತಿರುಗಿ false;
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
    ಆದರೆ (!SDL_X11_HAVE_XINPUT2 ||
        !X11_XQueryExtension(ದತ್ತಾಂಶ->display, "XInputExtension", &xinput2_opcode, &event, &err)) {
        ಹಿಂತಿರುಗಿ false; // X server does not have XInput at all
    }

    // We need at least 2.4 for Gesture, 2.2 for Multitouch, 2.0 otherwise.
    ಆವೃತ್ತಿ = query_xinput2_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->display, 2, 4);
    ಆದರೆ (!xinput2_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 2, 0)) {
        ಹಿಂತಿರುಗಿ false; // X server does not support the version we want at all.
    }

    xinput2_initialized = true;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO // Smooth scrolling needs XInput 2.1
    xinput2_scrolling_supported = xinput2_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 2, 1);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH // Multitouch needs XInput 2.2
    xinput2_multitouch_supported = xinput2_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 2, 2);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE // Gesture needs XInput 2.4
    xinput2_gesture_supported = xinput2_ಆವೃತ್ತಿ_atleast(ಆವೃತ್ತಿ, 2, 4);
#ಆದರೆ_ಅಂತ್ಯ

    // Populate the atoms for finding relative axes
    xinput2_rel_x_atom = X11_XInternAtom(ದತ್ತಾಂಶ->display, "Rel X", False);
    xinput2_rel_y_atom = X11_XInternAtom(ದತ್ತಾಂಶ->display, "Rel Y", False);
    xinput2_abs_x_atom = X11_XInternAtom(ದತ್ತಾಂಶ->display, "Abs X", False);
    xinput2_abs_y_atom = X11_XInternAtom(ದತ್ತಾಂಶ->display, "Abs Y", False);

    // Enable raw motion events for this display
    SDL_zero(eventmask);
    SDL_zeroa(ಮುಖವಾಡ);
    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ಮುಖವಾಡ_len = ಗಾತ್ರ(ಮುಖವಾಡ);
    eventmask.ಮುಖವಾಡ = ಮುಖವಾಡ;

    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_RawMotion);
    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_RawButtonPress);
    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_RawButtonRelease);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    ಆದರೆ (xinput2_scrolling_supported) {
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Motion);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    // Enable raw touch events if supported
    ಆದರೆ (xinput2_multitouch_supported) {
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_RawTouchBegin);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_RawTouchUpdate);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Raw_Touch_ಕೊನೆ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_XISelectEvents(ದತ್ತಾಂಶ->display, Default_ಬೇರು_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display), &eventmask, 1);

    SDL_zero(eventmask);
    SDL_zeroa(ಮುಖವಾಡ);
    eventmask.deviceid = XIAllDevices;
    eventmask.ಮುಖವಾಡ_len = ಗಾತ್ರ(ಮುಖವಾಡ);
    eventmask.ಮುಖವಾಡ = ಮುಖವಾಡ;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_XINPUT2_KEYBOARD
    // If not using the full keyboard handling, register for keypresses to get the event source devices.
    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ಕೀಲಿ_Press);
    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ಕೀಲಿ_Release);
#ಆದರೆ_ಅಂತ್ಯ

    XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Hierarchy_ಬದಲಾಯಿತು);
    X11_XISelectEvents(ದತ್ತಾಂಶ->display, Default_ಬೇರು_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display), &eventmask, 1);

    X11_Xinput2UpdateDevices(_this);
    X11_Xinput2_Update_ಸೂಚಕ_Mapping(_this);

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ X11_QuitXinput2(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    ಗಾಗಿ (SDL_XInput2DeviceInfo *i = xinput2_device_info, *ಮುಂದಿನ = ಖಾಲಿ; i; i = ಮುಂದಿನ) {
        ಮುಂದಿನ = i->ಮುಂದಿನ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        SDL_free(i->scroll.scroll_info);
#ಆದರೆ_ಅಂತ್ಯ
        SDL_free(i);
    }
    xinput2_device_info = ಖಾಲಿ;

    SDL_free(xinput2_ಸೂಚಕ_button_map);
    xinput2_ಸೂಚಕ_button_map = ಖಾಲಿ;
    xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ = 0;
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ X11_Xinput2_Update_ಸೂಚಕ_Mapping(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    ಆದರೆ (X11_Xinput2IsInitialized()) {
        SDL_Video_ದತ್ತಾಂಶ *vid = _this->ಆಂತರಿಕ;

        SDL_free(xinput2_ಸೂಚಕ_button_map);
        xinput2_ಸೂಚಕ_button_map = ಖಾಲಿ;
        xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ = 0;

        xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ = X11_XGet_ಸೂಚಕ_Mapping(vid->display, ಖಾಲಿ, 0);
        ಆದರೆ (xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ) {
            xinput2_ಸೂಚಕ_button_map = SDL_calloc(xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ, ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ));
            ಆದರೆ (xinput2_ಸೂಚಕ_button_map) {
                xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ = X11_XGet_ಸೂಚಕ_Mapping(vid->display, xinput2_ಸೂಚಕ_button_map, xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ = 0;
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
// xi2 device went away? take it out of the list.
ಸ್ಥಿರ ಶೂನ್ಯ xinput2_remove_device_info(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ device_id)
{
    ಗಾಗಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ಖಾಲಿ; devinfo; devinfo = devinfo->ಮುಂದಿನ) {
        ಆದರೆ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ಖಾಲಿ));
            ಆದರೆ (!prev) {
                xinput2_device_info = devinfo->ಮುಂದಿನ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                prev->ಮುಂದಿನ = devinfo->ಮುಂದಿನ;
            }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            SDL_free(devinfo->scroll.scroll_info);
#ಆದರೆ_ಅಂತ್ಯ
            SDL_free(devinfo);
            ಹಿಂತಿರುಗಿ;
        }
        prev = devinfo;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ xinput2_reset_device_valuators(ಶೂನ್ಯ)
{
    ಗಾಗಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info; devinfo; devinfo = devinfo->ಮುಂದಿನ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < devinfo->scroll.scroll_info_ಎಣಿಕೆ; ++i) {
            devinfo->scroll.scroll_info[i].prev_ಮೌಲ್ಯ_valid = false;
        }
#ಆದರೆ_ಅಂತ್ಯ
        devinfo->relative.prev_coord_valid[0] = false;
        devinfo->relative.prev_coord_valid[1] = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ xinput2_update_device_info(SDL_XInput2DeviceInfo *devinfo, XIAnyClassInfo **classes, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_classes)
{
    ಆದರೆ (!devinfo) {
        ಹಿಂತಿರುಗಿ;
    }

    bool have_rel_x = false, have_rel_y = false;
    bool have_abs_x = false, have_abs_y = false;
    ಪೂರ್ಣಾಂಕ rel_axis_ಸೂಚ್ಯಂಕ = 0;

    SDL_zero(devinfo->relative);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    // Don't unnecessarily reallocate the array.
    ಪೂರ್ಣಾಂಕ allocated_scroll_info_ಎಣಿಕೆ = devinfo->scroll.scroll_info_ಎಣಿಕೆ;
    devinfo->scroll.scroll_info_ಎಣಿಕೆ = 0;
#ಆದರೆ_ಅಂತ್ಯ

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_classes; ++i) {
        ಆದರೆ (classes[i]->type == XIValuatorClass) {
            /* Search for relative axes with the following priority:
             *  - Labelled 'Rel X'/'Rel Y'
             *   - Labelled 'Abs X'/'Abs Y'
             *    - The first two axes found
             */
            ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *v = (ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *)classes[i];
            ಆದರೆ (v->label == xinput2_rel_x_atom || (v->label == xinput2_abs_x_atom && !have_rel_x) ||
                (rel_axis_ಸೂಚ್ಯಂಕ == 0 && !have_rel_x && !have_abs_x)) {
                devinfo->relative.ಸಂಖ್ಯೆ_2[0] = v->ಸಂಖ್ಯೆ_2;
                devinfo->relative.relative[0] = (v->ಬಹುಲಕ == XIModeRelative);
                devinfo->relative.minval[0] = v->min;
                devinfo->relative.maxval[0] = v->max;

                ಆದರೆ (v->label == xinput2_rel_x_atom) {
                    have_rel_x = true;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (v->label == xinput2_abs_x_atom) {
                    have_abs_x = true;
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (v->label == xinput2_rel_y_atom || (v->label == xinput2_abs_y_atom && !have_rel_y) ||
                       (rel_axis_ಸೂಚ್ಯಂಕ == 1 && !have_rel_y && !have_abs_y)) {
                devinfo->relative.ಸಂಖ್ಯೆ_2[1] = v->ಸಂಖ್ಯೆ_2;
                devinfo->relative.relative[1] = (v->ಬಹುಲಕ == XIModeRelative);
                devinfo->relative.minval[1] = v->min;
                devinfo->relative.maxval[1] = v->max;

                ಆದರೆ (v->label == xinput2_rel_y_atom) {
                    have_rel_y = true;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (v->label == xinput2_abs_y_atom) {
                    have_abs_y = true;
                }
            }

            ++rel_axis_ಸೂಚ್ಯಂಕ;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (classes[i]->type == XIScrollClass) {
            ಸ್ಥಿರಾಂಕ XIScrollClassInfo *s = (XIScrollClassInfo *)classes[i];

            // Allocate new scroll info entries two at a time, as they typically come in a horizontal/vertical pair.
            ಆದರೆ (devinfo->scroll.scroll_info_ಎಣಿಕೆ == allocated_scroll_info_ಎಣಿಕೆ) {
                devinfo->scroll.scroll_info = SDL_realloc(devinfo->scroll.scroll_info, (allocated_scroll_info_ಎಣಿಕೆ + 2) * ಗಾತ್ರ(SDL_XInput2ScrollInfo));
                ಆದರೆ (!devinfo->scroll.scroll_info) {
                    // No memory, oh well...
                    allocated_scroll_info_ಎಣಿಕೆ = 0;
                    devinfo->scroll.scroll_info_ಎಣಿಕೆ = 0;
                    ಮುಂದುವರಿ;
                }

                allocated_scroll_info_ಎಣಿಕೆ += 2;
            }

            SDL_XInput2ScrollInfo *scroll_info = &devinfo->scroll.scroll_info[devinfo->scroll.scroll_info_ಎಣಿಕೆ];
            ++devinfo->scroll.scroll_info_ಎಣಿಕೆ;

            SDL_zerop(scroll_info);
            scroll_info->ಸಂಖ್ಯೆ_2 = s->ಸಂಖ್ಯೆ_2;
            scroll_info->scroll_type = s->scroll_type;
            scroll_info->increment = s->increment;
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
    }
}

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_get_cached_device_info(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ device_id)
{
    ಗಾಗಿ (SDL_XInput2DeviceInfo *devinfo = xinput2_device_info, *prev = ಖಾಲಿ; devinfo; devinfo = devinfo->ಮುಂದಿನ) {
        ಆದರೆ (devinfo->device_id == device_id) {
            SDL_assert((devinfo == xinput2_device_info) == (prev == ಖಾಲಿ));
            ಆದರೆ (prev) { // move this to the front of the list, assuming we'll get more from this one.
                prev->ಮುಂದಿನ = devinfo->ಮುಂದಿನ;
                devinfo->ಮುಂದಿನ = xinput2_device_info;
                xinput2_device_info = devinfo;
            }
            ಹಿಂತಿರುಗಿ devinfo;
        }
        prev = devinfo;
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ SDL_XInput2DeviceInfo *xinput2_get_device_info(SDL_Video_ದತ್ತಾಂಶ *videodata, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ device_id)
{
    // Cache device info as we see new devices.
    SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(device_id);
    ಆದರೆ (devinfo) {
        ಹಿಂತಿರುಗಿ devinfo;
    }

    // Don't know about this device yet, query and cache it.
    devinfo = (SDL_XInput2DeviceInfo *)SDL_calloc(1, ಗಾತ್ರ(SDL_XInput2DeviceInfo));
    ಆದರೆ (!devinfo) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಪೂರ್ಣಾಂಕ i;
    XIDeviceInfo *xidevinfo = X11_XIQueryDevice(videodata->display, device_id, &i);
    ಆದರೆ (!xidevinfo) {
        SDL_free(devinfo);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    xinput2_update_device_info(devinfo, xidevinfo->classes, xidevinfo->ಅಂಕೆ_classes);
    X11_XIFreeDeviceInfo(xidevinfo);

    devinfo->device_id = device_id;
    devinfo->ಮುಂದಿನ = xinput2_device_info;
    xinput2_device_info = devinfo;

    ಹಿಂತಿರುಗಿ devinfo;
}
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ X11_HandleXinput2Event(SDL_VideoDevice *_this, XGenericEventCookie *cookie)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    ಆದರೆ (cookie->extension != xinput2_opcode) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆಯ್ಕೆ (cookie->evtype) {
    ಸ್ಥಿತಿ XI_Hierarchy_ಬದಲಾಯಿತು:
    {
        ಸ್ಥಿರಾಂಕ XIHierarchyEvent *hierev = (ಸ್ಥಿರಾಂಕ XIHierarchyEvent *)cookie->ದತ್ತಾಂಶ;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < hierev->ಅಂಕೆ_info; ++i) {
            // pen stuff...
            ಆದರೆ ((hierev->info[i].flags & (XISlaveRemoved | XIDeviceDisabled)) != 0) {
                X11_RemovePenByDeviceID(hierev->info[i].deviceid);  // it's okay if this thing isn't actually a pen, it'll handle it.
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((hierev->info[i].flags & (XISlaveAdded | XIDeviceEnabled)) != 0) {
                X11_Maybe_ಕೂಡಿಸು_Pen_By_Device_ID(_this, hierev->info[i].deviceid);  // this will do more checks to make sure this is valid.
            }

            // not pen stuff...
            ಆದರೆ (hierev->info[i].flags & (XIMasterRemoved | XISlaveRemoved)) {
                xinput2_remove_device_info(hierev->info[i].deviceid);
            }
        }
        videodata->xinput_hierarchy_ಬದಲಾಯಿತು = true;
    } ನಿಲ್ಲಿಸು;

    // !!! FIXME: XI_DeviceChanged fires when device valuator mappings need to be updated. Is XI_PropertyEvent needed for anything?
    // case XI_PropertyEvent:
    ಸ್ಥಿತಿ XI_Device_ಬದಲಾಯಿತು:
    {
        ಸ್ಥಿರಾಂಕ XIDevice_ಬದಲಾಯಿತು_Event *dcev = (ಸ್ಥಿರಾಂಕ XIDevice_ಬದಲಾಯಿತು_Event *)cookie->ದತ್ತಾಂಶ;
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dcev->deviceid);
        ಆದರೆ (devinfo) {
            xinput2_update_device_info(devinfo, dcev->classes, dcev->ಅಂಕೆ_classes);
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_PropertyEvent:
    {
        ಸ್ಥಿರಾಂಕ XIPropertyEvent *proev = (ಸ್ಥಿರಾಂಕ XIPropertyEvent *)cookie->ದತ್ತಾಂಶ;
        // Handle pen proximity enter/leave
        ಆದರೆ (proev->what == XIPropertyModified && proev->property == videodata->atoms.pen_atom_wacom_serial_ids) {
            ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(videodata, xev->event);
            X11_NotifyPenProximityChange(_this, windowdata ? windowdata->ಕಿಟಕಿ : ಖಾಲಿ, proev->deviceid);
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_RawMotion:
    {
        ಸ್ಥಿರಾಂಕ XIRawEvent *rawev = (ಸ್ಥಿರಾಂಕ XIRawEvent *)cookie->ದತ್ತಾಂಶ;
        ಸ್ಥಿರಾಂಕ bool is_pen = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(rawev->sourceid) != ಖಾಲಿ;

        videodata->global_mouse_ಬದಲಾಯಿತು = true;
        ಆದರೆ (is_pen) {
            ನಿಲ್ಲಿಸು; // Pens check for XI_Motion instead
        }

        SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, rawev->deviceid);
        ಆದರೆ (!devinfo) {
            ನಿಲ್ಲಿಸು; // oh well.
        }

        parse_relative_valuators(&devinfo->relative, rawev);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_ಕೀಲಿ_Press:
    ಸ್ಥಿತಿ XI_ಕೀಲಿ_Release:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_XINPUT2_KEYBOARD
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(videodata, xev->event);
        XEvent xevent;

        ಆದರೆ (xev->deviceid != xev->sourceid) {
            // Discard events from "Master" devices to avoid duplicates.
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (cookie->evtype == XI_ಕೀಲಿ_Press) {
            xevent.type = ಕೀಲಿ_Press;
        } ಇಲ್ಲದಿದ್ದರೆ {
            xevent.type = ಕೀಲಿ_Release;
        }
        xevent.xkey.serial = xev->serial;
        xevent.xkey.send_event = xev->send_event;
        xevent.xkey.display = xev->display;
        xevent.xkey.ಕಿಟಕಿ = xev->event;
        xevent.xkey.ಬೇರು = xev->ಬೇರು;
        xevent.xkey.subwindow = xev->ಮಗು;
        xevent.xkey.ಸಮಯ = xev->ಸಮಯ;
        xevent.xkey.x = (ಪೂರ್ಣಾಂಕ)xev->event_x;
        xevent.xkey.y = (ಪೂರ್ಣಾಂಕ)xev->event_y;
        xevent.xkey.x_ಬೇರು = (ಪೂರ್ಣಾಂಕ)xev->ಬೇರು_x;
        xevent.xkey.y_ಬೇರು = (ಪೂರ್ಣಾಂಕ)xev->ಬೇರು_y;
        xevent.xkey.state = xev->mods.effective;
        xevent.xkey.keycode = xev->detail;
        xevent.xkey.same_screen = 1;

        X11_Handle_ಕೀಲಿ_Event(_this, windowdata, (SDL_KeyboardID)xev->sourceid, &xevent);
#ಇಲ್ಲದಿದ್ದರೆ
        /* Keys are handled through core X events, however, note the device ID and
         * associated serial, so that the source device ID can be passed through.
         */
        videodata->xinput_ಕೊನೆಯ_ಕೀಲಿ_serial = xev->serial;
        videodata->xinput_ಕೊನೆಯ_keyboard_device = xev->sourceid;
#ಆದರೆ_ಅಂತ್ಯ
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_RawButtonPress:
    ಸ್ಥಿತಿ XI_RawButtonRelease:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ಸ್ಥಿತಿ XI_RawTouchBegin:
    ಸ್ಥಿತಿ XI_RawTouchUpdate:
    ಸ್ಥಿತಿ XI_Raw_Touch_ಕೊನೆ:
#ಆದರೆ_ಅಂತ್ಯ
    {
        videodata->global_mouse_ಬದಲಾಯಿತು = true;
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_ButtonPress:
    ಸ್ಥಿತಿ XI_ButtonRelease:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
        X11_PenHandle *pen = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(xev->sourceid);
        ಪೂರ್ಣಾಂಕ button = xev->detail;
        ಸ್ಥಿರಾಂಕ bool ಕೆಳಕ್ಕೆ = (cookie->evtype == XI_ButtonPress);
#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool ಸೂಚಕ_emulated = (xev->flags & XIPointerEmulated) != 0;
#ಇಲ್ಲದಿದ್ದರೆ
        bool ಸೂಚಕ_emulated = false;
#ಆದರೆ_ಅಂತ್ಯ

        // Store the button serial to filter out redundant core button events.
        videodata->xinput_ಕೊನೆಯ_button_serial = xev->serial;

        ಆದರೆ (pen) {
            ಆದರೆ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ನಿಲ್ಲಿಸು;
            }
            // Only report button event; if there was also pen movement / pressure changes, we expect an XI_Motion event first anyway.
            SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
            ಆದರೆ (button == 1) { // button 1 is the pen tip
                SDL_SendPenTouch(0, pen->pen, ಕಿಟಕಿ, pen->is_eraser, ಕೆಳಕ್ಕೆ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_SendPenButton(0, pen->pen, ಕಿಟಕಿ, button - 1, ಕೆಳಕ್ಕೆ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಸೂಚಕ_emulated) {
            // Otherwise assume a regular mouse
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = X11_ಕಂಡುಹಿಡಿ_ಕಿಟಕಿ(videodata, xev->event);
            ಪೂರ್ಣಾಂಕ x_ticks = 0, y_ticks = 0;

            ಆದರೆ (xev->deviceid != videodata->xinput_master_ಸೂಚಕ_device) {
                /* Ignore slave button events on non-focused windows, as they can arrive before FocusIn events,
                 * or result in focus being incorrectly set while a grab is active.
                 */
                ಆದರೆ (SDL_GetMouseFocus() != windowdata->ಕಿಟಕಿ) {
                    ನಿಲ್ಲಿಸು;
                }

                // Slave pointer devices don't have button remapping applied automatically, so do it manually.
                ಆದರೆ (button <= xinput2_ಸೂಚಕ_button_map_ಗಾತ್ರ) {
                    button = xinput2_ಸೂಚಕ_button_map[button - 1];
                }
            }

            /* Discard wheel events from "Master" devices to avoid duplicates,
             * as coarse wheel events are stateless and can't be deduplicated.
             */
            ಆದರೆ (xev->deviceid != xev->sourceid && X11_IsWheelEvent(button, &x_ticks, &y_ticks)) {
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (ಕೆಳಕ್ಕೆ) {
                X11_HandleButtonPress(_this, windowdata, (SDL_MouseID)xev->sourceid, button,
                                      (ದಶಮಾಂಶ)xev->event_x, (ದಶಮಾಂಶ)xev->event_y, xev->ಸಮಯ, xev->serial);
            } ಇಲ್ಲದಿದ್ದರೆ {
                X11_HandleButtonRelease(_this, windowdata, (SDL_MouseID)xev->sourceid, button, xev->ಸಮಯ);
            }
        }
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_Enter:
    {
        xinput2_reset_device_valuators();
    } ನಿಲ್ಲಿಸು;

    /* Register to receive XI_Motion (which deactivates MotionNotify), so that we can distinguish
       real mouse motions from synthetic ones, for multitouch and pen support. */
    ಸ್ಥಿತಿ XI_Motion:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
        bool ಸೂಚಕ_emulated = (xev->flags & XIPointerEmulated) != 0;
#ಇಲ್ಲದಿದ್ದರೆ
        bool ಸೂಚಕ_emulated = false;
#ಆದರೆ_ಅಂತ್ಯ

        videodata->global_mouse_ಬದಲಾಯಿತು = true;

        X11_PenHandle *pen = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(xev->sourceid);

        ಆದರೆ (pen) {
            ಆದರೆ (xev->deviceid != xev->sourceid) {
                // Discard events from "Master" devices to avoid duplicates.
                ನಿಲ್ಲಿಸು;
            }

            SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
            SDL_SendPenMotion(0, pen->pen, ಕಿಟಕಿ, (ದಶಮಾಂಶ) xev->event_x, (ದಶಮಾಂಶ) xev->event_y);

            ದಶಮಾಂಶ axes[SDL_PEN_AXIS_ಎಣಿಕೆ];
            X11_PenAxesFromValuators(pen, xev->valuators.ಮೌಲ್ಯಗಳು, xev->valuators.ಮುಖವಾಡ, xev->valuators.ಮುಖವಾಡ_len, axes);

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(axes); i++) {
                ಆದರೆ (pen->valuator_for_axis[i] != SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
                    SDL_SendPenAxis(0, pen->pen, ಕಿಟಕಿ, (SDL_PenAxis) i, axes[i]);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಸೂಚಕ_emulated) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO
            ಆದರೆ (xev->deviceid == xev->sourceid) {
                SDL_XInput2DeviceInfo *devinfo = xinput2_get_device_info(videodata, xev->deviceid);
                ಆದರೆ (devinfo) {
                    xinput2_parse_scrollable_valuators(&devinfo->scroll, xev);
                }
            }
#ಆದರೆ_ಅಂತ್ಯ

            /* Use the master device for non-relative motion, as the slave devices can seemingly lag behind,
             * except when the mouse is grabbed and touches are active, as core input events are used for
             * absolute motion while the mouse is grabbed, and core events don't have the XIPointerEmulated
             * flag to filter out pointer events emulated from touch events.
             */
            SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
            ಆದರೆ (ಕಿಟಕಿ && (xev->deviceid == videodata->xinput_master_ಸೂಚಕ_device || (xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ && ಕಿಟಕಿ->ಆಂತರಿಕ->mouse_grabbed))) {
                SDL_Mouse *mouse = SDL_GetMouse();
                ಆದರೆ (!mouse->relative_ಬಹುಲಕ) {
                        X11_Process_ದೊರಕಿತು_Test(_this, ಕಿಟಕಿ->ಆಂತರಿಕ, (ದಶಮಾಂಶ)xev->event_x, (ದಶಮಾಂಶ)xev->event_y, false);
                        SDL_SendMouseMotion(0, ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, (ದಶಮಾಂಶ)xev->event_x, (ದಶಮಾಂಶ)xev->event_y);
                }
            }
        }
    } ನಿಲ್ಲಿಸು;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    ಸ್ಥಿತಿ XI_TouchBegin:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
        ದಶಮಾಂಶ x, y;
        ++xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ಕಿಟಕಿ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, ಕಿಟಕಿ, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, 1.0);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_Touch_ಕೊನೆ:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
        ದಶಮಾಂಶ x, y;
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
        ಆದರೆ (!--xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ && ಕಿಟಕಿ && ಕಿಟಕಿ->ಆಂತರಿಕ->mouse_grabbed) {
            xinput2_grabbed_touch_raised = true;
        }
        xinput2_normalize_touch_coordinates(ಕಿಟಕಿ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouch(0, xev->sourceid, xev->detail, ಕಿಟಕಿ, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, 1.0);
    } ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ XI_TouchUpdate:
    {
        ಸ್ಥಿರಾಂಕ XIDeviceEvent *xev = (ಸ್ಥಿರಾಂಕ XIDeviceEvent *)cookie->ದತ್ತಾಂಶ;
        ದಶಮಾಂಶ x, y;
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ಕಿಟಕಿ, xev->event_x, xev->event_y, &x, &y);
        SDL_SendTouchMotion(0, xev->sourceid, xev->detail, ಕಿಟಕಿ, x, y, 1.0);
    } ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ಸ್ಥಿತಿ XI_GesturePinchBegin:
    ಸ್ಥಿತಿ XI_GesturePinchUpdate:
    ಸ್ಥಿತಿ XI_Gesture_Pinch_ಕೊನೆ:
    {
        ಸ್ಥಿರಾಂಕ XIGesturePinchEvent *xev = (ಸ್ಥಿರಾಂಕ XIGesturePinchEvent *)cookie->ದತ್ತಾಂಶ;
        ದಶಮಾಂಶ x, y;
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = xinput2_get_sdlwindow(videodata, xev->event);
        xinput2_normalize_touch_coordinates(ಕಿಟಕಿ, xev->event_x, xev->event_y, &x, &y);

        ಆದರೆ (cookie->evtype == XI_GesturePinchBegin) {
            SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, 0, ಕಿಟಕಿ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cookie->evtype == XI_GesturePinchUpdate) {
            SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, 0, ಕಿಟಕಿ, (ದಶಮಾಂಶ)xev->scale, -1.0f, -1.0f, -1.0f, -1.0f);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_SendPinch(SDL_EVENT_PINCH_ಕೊನೆ, 0, ಕಿಟಕಿ, 0, -1.0f, -1.0f, -1.0f, -1.0f);
        }
    } ನಿಲ್ಲಿಸು;

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE

    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ಶೂನ್ಯ X11_InitXinput2Multitouch(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    xinput2_grabbed_touch_raised = false;
    xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ = 0;
#ಆದರೆ_ಅಂತ್ಯ
}

bool X11_Xinput2_Handles_Motion_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    /* Send the active flag once more after the touch count is zero, to suppress the
     * emulated motion event when the last touch is raised.
     */
    ಸ್ಥಿರಾಂಕ bool ret = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->xinput2_mouse_enabled &&
                     (!ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_grabbed || xinput2_ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ || xinput2_grabbed_touch_raised);
    xinput2_grabbed_touch_raised = false;

    ಹಿಂತಿರುಗಿ ret;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

ಶೂನ್ಯ X11_Xinput2Select(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_SCROLLINFO) || defined(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH)
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;
    XIEvent_ಮುಖವಾಡ eventmask;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಮುಖವಾಡ[5] = { 0, 0, 0, 0, 0 };

    ಆದರೆ (!xinput2_scrolling_supported && !xinput2_multitouch_supported) {
        ಹಿಂತಿರುಗಿ;
    }

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.ಮುಖವಾಡ_len = ಗಾತ್ರ(ಮುಖವಾಡ);
    eventmask.ಮುಖವಾಡ = ಮುಖವಾಡ;

    ಆದರೆ (xinput2_scrolling_supported) {
        /* Track enter events that inform us that we need to update
         * the previous scroll coordinates since we cannot track
         * them outside our window.
         */
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Enter);
    }

    ಆದರೆ (xinput2_multitouch_supported) {
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_TouchBegin);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_TouchUpdate);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Touch_ಕೊನೆ);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Motion);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_GESTURE
    ಆದರೆ (xinput2_gesture_supported) {
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_GesturePinchBegin);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_GesturePinchUpdate);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Gesture_Pinch_ಕೊನೆ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_XISelectEvents(ದತ್ತಾಂಶ->display, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->xwindow, &eventmask, 1);
#ಆದರೆ_ಅಂತ್ಯ
}

bool X11_Xinput2IsInitialized(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    ಹಿಂತಿರುಗಿ xinput2_initialized;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ
}

bool X11_Xinput2SelectMouseAndKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (X11_Xinput2IsInitialized()) {
        XIEvent_ಮುಖವಾಡ eventmask;
        ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಮುಖವಾಡ[4] = { 0, 0, 0, 0 };

        eventmask.ಮುಖವಾಡ_len = ಗಾತ್ರ(ಮುಖವಾಡ);
        eventmask.ಮುಖವಾಡ = ಮುಖವಾಡ;
        eventmask.deviceid = XIAllDevices;

// This is not enabled by default because these events are only delivered to the window with mouse focus, not keyboard focus
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_XINPUT2_KEYBOARD
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ಕೀಲಿ_Press);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ಕೀಲಿ_Release);
        windowdata->xinput2_keyboard_enabled = true;
#ಆದರೆ_ಅಂತ್ಯ

        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ButtonPress);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_ButtonRelease);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Motion);
        windowdata->xinput2_mouse_enabled = true;

        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Enter);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Leave);

        // Hotplugging:
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Device_ಬದಲಾಯಿತು);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_Hierarchy_ಬದಲಾಯಿತು);
        XISet_ಮುಖವಾಡ(ಮುಖವಾಡ, XI_PropertyEvent); // E.g., when swapping tablet pens

        ಆದರೆ (X11_XISelectEvents(ದತ್ತಾಂಶ->display, windowdata->xwindow, &eventmask, 1) != Success) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "Could not enable XInput2 event handling");
            windowdata->xinput2_keyboard_enabled = false;
            windowdata->xinput2_mouse_enabled = false;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (windowdata->xinput2_keyboard_enabled || windowdata->xinput2_mouse_enabled) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ X11_Xinput2GrabTouch(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಮುಖವಾಡ[4] = { 0, 0, 0, 0 };
    XIGrabModifiers mods;
    XIEvent_ಮುಖವಾಡ eventmask;

    ಆದರೆ (!xinput2_multitouch_supported) {
        ಹಿಂತಿರುಗಿ;
    }

    mods.modifiers = XIAnyModifier;
    mods.ಸ್ಥಿತಿ_2 = 0;

    eventmask.deviceid = XIAllDevices;
    eventmask.ಮುಖವಾಡ_len = ಗಾತ್ರ(ಮುಖವಾಡ);
    eventmask.ಮುಖವಾಡ = ಮುಖವಾಡ;

    XISet_ಮುಖವಾಡ(eventmask.ಮುಖವಾಡ, XI_TouchBegin);
    XISet_ಮುಖವಾಡ(eventmask.ಮುಖವಾಡ, XI_TouchUpdate);
    XISet_ಮುಖವಾಡ(eventmask.ಮುಖವಾಡ, XI_Touch_ಕೊನೆ);
    XISet_ಮುಖವಾಡ(eventmask.ಮುಖವಾಡ, XI_Motion);

    X11_XIGrabTouchBegin(display, XIAllDevices, ದತ್ತಾಂಶ->xwindow, True, &eventmask, 1, &mods);
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ X11_Xinput2UngrabTouch(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;

    XIGrabModifiers mods;

    ಆದರೆ (!xinput2_multitouch_supported) {
        ಹಿಂತಿರುಗಿ;
    }

    xinput2_grabbed_touch_raised = false;

    mods.modifiers = XIAnyModifier;
    mods.ಸ್ಥಿತಿ_2 = 0;

    X11_XIUngrabTouchBegin(display, XIAllDevices, ದತ್ತಾಂಶ->xwindow, 1, &mods);
#ಆದರೆ_ಅಂತ್ಯ
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Device_ID(Uint32 deviceID, Uint32 **list, ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಪೂರ್ಣಾಂಕ new_ಎಣಿಕೆ = (*ಎಣಿಕೆ_2 + 1);
    Uint32 *new_list = (Uint32 *)SDL_realloc(*list, new_ಎಣಿಕೆ * ಗಾತ್ರ(*new_list));
    ಆದರೆ (!new_list) {
        // Oh well, we'll drop this one
        ಹಿಂತಿರುಗಿ;
    }
    new_list[new_ಎಣಿಕೆ - 1] = deviceID;

    *ಎಣಿಕೆ_2 = new_ಎಣಿಕೆ;
    *list = new_list;
}

ಸ್ಥಿರ bool HasDeviceID(Uint32 deviceID, ಸ್ಥಿರಾಂಕ Uint32 *list, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; ++i) {
        ಆದರೆ (deviceID == list[i]) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Device_ID64(Uint64 deviceID, Uint64 **list, ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಪೂರ್ಣಾಂಕ new_ಎಣಿಕೆ = (*ಎಣಿಕೆ_2 + 1);
    Uint64 *new_list = (Uint64 *)SDL_realloc(*list, new_ಎಣಿಕೆ * ಗಾತ್ರ(*new_list));
    ಆದರೆ (!new_list) {
        // Oh well, we'll drop this one
        ಹಿಂತಿರುಗಿ;
    }
    new_list[new_ಎಣಿಕೆ - 1] = deviceID;

    *ಎಣಿಕೆ_2 = new_ಎಣಿಕೆ;
    *list = new_list;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool HasDeviceID64(Uint64 deviceID, ಸ್ಥಿರಾಂಕ Uint64 *list, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; ++i) {
        ಆದರೆ (deviceID == list[i]) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2

ಶೂನ್ಯ X11_Xinput2UpdateDevices(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    XIDeviceInfo *info;
    ಪೂರ್ಣಾಂಕ ndevices;
    ಪೂರ್ಣಾಂಕ old_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *old_keyboards = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ new_keyboard_ಎಣಿಕೆ = 0;
    SDL_KeyboardID *new_keyboards = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ old_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *old_mice = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ new_mouse_ಎಣಿಕೆ = 0;
    SDL_MouseID *new_mice = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ old_touch_ಎಣಿಕೆ = 0;
    Uint64 *old_touch_devices = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ new_touch_ಎಣಿಕೆ = 0;
    Uint64 *new_touch_devices = ಖಾಲಿ;

    SDL_assert(X11_Xinput2IsInitialized());

    info = X11_XIQueryDevice(ದತ್ತಾಂಶ->display, XIAllDevices, &ndevices);

    old_keyboards = SDL_GetKeyboards(&old_keyboard_ಎಣಿಕೆ);
    old_mice = SDL_GetMice(&old_mouse_ಎಣಿಕೆ);
    old_touch_devices = SDL_GetTouchDevices(&old_touch_ಎಣಿಕೆ);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ndevices; i++) {
        XIDeviceInfo *dev = &info[i];

        ಆಯ್ಕೆ (dev->use) {
        ಸ್ಥಿತಿ XIMasterKeyboard:
        ಸ್ಥಿತಿ XISlaveKeyboard:
            {
                SDL_KeyboardID keyboardID = (SDL_KeyboardID)dev->deviceid;
                ಕೂಡಿಸು_Device_ID(keyboardID, &new_keyboards, &new_keyboard_ಎಣಿಕೆ);
                ಆದರೆ (!HasDeviceID(keyboardID, old_keyboards, old_keyboard_ಎಣಿಕೆ)) {
                    SDL_ಕೂಡಿಸು_Keyboard(keyboardID, dev->name);
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XIMaster_ಸೂಚಕ:
            ದತ್ತಾಂಶ->xinput_master_ಸೂಚಕ_device = dev->deviceid;
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ XISlave_ಸೂಚಕ:
            {
                SDL_MouseID mouseID = (SDL_MouseID)dev->deviceid;
                ಕೂಡಿಸು_Device_ID(mouseID, &new_mice, &new_mouse_ಎಣಿಕೆ);
                ಆದರೆ (!HasDeviceID(mouseID, old_mice, old_mouse_ಎಣಿಕೆ)) {
                    SDL_ಕೂಡಿಸು_Mouse(mouseID, dev->name);
                }
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }

        // If a device info entry already exists for this device, update it.
        SDL_XInput2DeviceInfo *devinfo = xinput2_get_cached_device_info(dev->deviceid);
        ಆದರೆ (devinfo) {
            xinput2_update_device_info(devinfo, dev->classes, dev->ಅಂಕೆ_classes);
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < dev->ಅಂಕೆ_classes; j++) {
            Uint64 touchID;
            SDL_TouchDeviceType touchType;
            XIAnyClassInfo *class = dev->classes[j];
            XITouchClassInfo *t = (XITouchClassInfo *)class;

            // Only touch devices
            ಆದರೆ (class->type != XITouchClass) {
                ಮುಂದುವರಿ;
            }

            touchID = (Uint64)t->sourceid;
            ಕೂಡಿಸು_Device_ID64(touchID, &new_touch_devices, &new_touch_ಎಣಿಕೆ);
            ಆದರೆ (!HasDeviceID64(touchID, old_touch_devices, old_touch_ಎಣಿಕೆ)) {
                ಆದರೆ (t->ಬಹುಲಕ == XIDependentTouch) {
                    touchType = SDL_TOUCH_DEVICE_ಪರೋಕ್ಷ_RELATIVE;
                } ಇಲ್ಲದಿದ್ದರೆ { // XIDirectTouch
                    touchType = SDL_TOUCH_DEVICE_ನೇರ;
                }
                SDL_ಕೂಡಿಸು_Touch(touchID, touchType, dev->name);
            }
        }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = old_keyboard_ಎಣಿಕೆ; i--;) {
        ಆದರೆ (!HasDeviceID(old_keyboards[i], new_keyboards, new_keyboard_ಎಣಿಕೆ)) {
            SDL_RemoveKeyboard(old_keyboards[i]);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = old_mouse_ಎಣಿಕೆ; i--;) {
        ಆದರೆ (!HasDeviceID(old_mice[i], new_mice, new_mouse_ಎಣಿಕೆ)) {
            SDL_RemoveMouse(old_mice[i]);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = old_touch_ಎಣಿಕೆ; i--;) {
        ಆದರೆ (!HasDeviceID64(old_touch_devices[i], new_touch_devices, new_touch_ಎಣಿಕೆ)) {
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

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
