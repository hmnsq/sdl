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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_scancode_tables_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_keycode_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandkeyboard.h"

#ಅನ್ತರ್ಭಾವ "pointer-constraints-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "relative-pointer-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-shell-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "text-input-unstable-v3-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "tablet-v2-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "primary-selection-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "input-timestamps-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-gestures-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "cursor-shape-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "viewporter-client-protocol.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
#ಅನ್ತರ್ಭಾವ <libdecor.h>
#ಆದರೆ_ಅಂತ್ಯ

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ <linux/input.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_ಎಡ    (0x110)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_ಬಲ   (0x111)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_ಮಧ್ಯ  (0x112)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_SIDE    (0x113)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_EXTRA   (0x114)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_STYLUS  (0x14b)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_STYLUS2 (0x14c)
#ವ್ಯಾಖ್ಯಾನಿಸು BTN_STYLUS3 (0x149)
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_scancode_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/imKStoUCS.h"
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <xkbcommon/xkbcommon-compose.h>
#ಅನ್ತರ್ಭಾವ <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_WHEEL_AXIS_UNIT 10

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XKB_MOD_NAME_MOD3
#ವ್ಯಾಖ್ಯಾನಿಸು XKB_MOD_NAME_MOD3 "Mod3"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XKB_MOD_NAME_MOD5
#ವ್ಯಾಖ್ಯಾನಿಸು XKB_MOD_NAME_MOD5 "Mod5"
#ಆದರೆ_ಅಂತ್ಯ

// Keyboard and mouse names to match XWayland
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_DEFAULT_ಸೂಚಕ_NAME "Virtual core pointer"
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_ಗಮ್ಯ_NS(10)

// Timer rollover detection thresholds
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ  (SDL_MAX_UINT32 / 16U)
#ವ್ಯಾಖ್ಯಾನಿಸು WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ (WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ * 15U)

// Scoped function declarations
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    Uint32 ಕೀಲಿ;
    SDL_Scancode scancode;
} Wayland_Reserved_ಕೀಲಿ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ರಚನೆ wl_surface *surface;

    ರಚನೆ wl_list link;
} SDL_Wayland_Touch_ಬಿಂದು;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_ಕೂಡಿಸು_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ರಚನೆ wl_surface *surface)
{
    SDL_Wayland_Touch_ಬಿಂದು *tp = SDL_malloc(ಗಾತ್ರ(SDL_Wayland_Touch_ಬಿಂದು));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ಸೇರಿಸು(&seat->touch.points, &tp->link);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_ಬಿಂದು *tp)
{
    ಆದರೆ (tp->surface) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(tp->surface);

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2) {
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(tp->fx) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಅಗಲ);
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(tp->fy) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಎತ್ತರ);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ಆದರೆ (SDL_GetMouseFocus() == ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow && !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->keyboard_focus_ಎಣಿಕೆ &&
                !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_focus_ಎಣಿಕೆ && !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ) {
                SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ರಚನೆ wl_surface **surface)
{
    SDL_Wayland_Touch_ಬಿಂದು *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ಆದರೆ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ಆದರೆ (surface) {
                *surface = tp->surface;
            }
            ನಿಲ್ಲಿಸು;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ರಚನೆ wl_surface **surface)
{
    SDL_Wayland_Touch_ಬಿಂದು *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ಆದರೆ (tp->id == id) {
            ಆದರೆ (fx) {
                *fx = tp->fx;
            }
            ಆದರೆ (fy) {
                *fy = tp->fy;
            }
            ಆದರೆ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ನಿಲ್ಲಿಸು;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_GetScaledMouseRect(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Rect *scaled_rect)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;

    scaled_rect->x = (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->mouse_rect.x / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.x);
    scaled_rect->y = (ಪೂರ್ಣಾಂಕ)SDL_floor(ಕಿಟಕಿ->mouse_rect.y / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.y);
    scaled_rect->w = (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->mouse_rect.w / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.x);
    scaled_rect->h = (ಪೂರ್ಣಾಂಕ)SDL_ceil(ಕಿಟಕಿ->mouse_rect.h / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.y);
}

ಸ್ಥಿರ Uint64 Wayland_Adjust_Event_Timestamp_ತಳ(Uint64 nsTimestamp)
{
    ಸ್ಥಿರ Uint64 timestamp_ಸ್ಥಾನಾಂತರ = 0;
    ಸ್ಥಿರಾಂಕ Uint64 now = SDL_GetTicksNS();

    ಆದರೆ (!timestamp_ಸ್ಥಾನಾಂತರ) {
        timestamp_ಸ್ಥಾನಾಂತರ = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (nsTimestamp > now) {
        timestamp_ಸ್ಥಾನಾಂತರ -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ಹಿಂತಿರುಗಿ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ಸ್ಥಿರ Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ಸ್ಥಿರ Uint64 timestamp_ಸ್ಥಾನಾಂತರ = 0;
    ಸ್ಥಿರ Uint32 ಕೊನೆಯ = 0;
    Uint64 timestamp = SDL_MS_ಗಮ್ಯ_NS(wl_timestamp_ms) + timestamp_ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (wl_timestamp_ms >= ಕೊನೆಯ) {
        ಆದರೆ (timestamp_ಸ್ಥಾನಾಂತರ && ಕೊನೆಯ < WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_ಗಮ್ಯ_NS(SDL_UINT64_C(0x100000000));
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕೊನೆಯ = wl_timestamp_ms;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ಆದರೆ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ && ಕೊನೆಯ > WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ) {
            timestamp_ಸ್ಥಾನಾಂತರ += SDL_MS_ಗಮ್ಯ_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_ಗಮ್ಯ_NS(SDL_UINT64_C(0x100000000));
            ಕೊನೆಯ = wl_timestamp_ms;
        }
    }

    ಹಿಂತಿರುಗಿ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ಸ್ಥಿರ Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಸ್ಥಿರಾಂಕ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಹಿಂತಿರುಗಿ Wayland_Adjust_Event_Timestamp_ತಳ(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ಸ್ಥಿರ Uint64 Wayland_Get_ಸೂಚಕ_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಸ್ಥಿರಾಂಕ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಹಿಂತಿರುಗಿ Wayland_Adjust_Event_Timestamp_ತಳ(seat->ಸೂಚಕ_2.timestamps ? seat->ಸೂಚಕ_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಸ್ಥಿರಾಂಕ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಹಿಂತಿರುಗಿ Wayland_Adjust_Event_Timestamp_ತಳ(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಒಳಹರಿವು_timestamp_listener(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_v1 *zwp_ಒಳಹರಿವು_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)ದತ್ತಾಂಶ) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_ಪ್ರತಿ_ಎರಡನೇ) + tv_nsec;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_v1_listener timestamp_listener = {
    ಒಳಹರಿವು_timestamp_listener
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_ರಿಜಿಸ್ಟರ್_ಒಳಹರಿವು_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->display->ಒಳಹರಿವು_timestamps_manager) {
        ಆದರೆ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ಒಳಹರಿವು_timestamps_v1_ಕೂಡಿಸು_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ && !seat->ಸೂಚಕ_2.timestamps) {
            seat->ಸೂಚಕ_2.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_ಸೂಚಕ_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
            zwp_ಒಳಹರಿವು_timestamps_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.timestamps, &timestamp_listener, &seat->ಸೂಚಕ_2.highres_timestamp_ns);
        }

        ಆದರೆ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_touch_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->touch.wl_touch);
            zwp_ಒಳಹರಿವು_timestamps_v1_ಕೂಡಿಸು_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Init_ಒಳಹರಿವು_Timestamp_Manager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    ಆದರೆ (display->ಒಳಹರಿವು_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_ರಿಜಿಸ್ಟರ್_ಒಳಹರಿವು_Timestamp_Listeners(seat);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_begin(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_ಸೂಚಕ_gesture_pinch_v1 *zwp_ಸೂಚಕ_gesture_pinch_v1, uint32_t serial, uint32_t ಸಮಯ, ರಚನೆ wl_surface *surface, uint32_t fingers)
{
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);
    ಆದರೆ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
        seat->ಸೂಚಕ_2.gesture_focus = wind;

        ಸ್ಥಿರಾಂಕ Uint64 timestamp = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_update(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_ಸೂಚಕ_gesture_pinch_v1 *zwp_ಸೂಚಕ_gesture_pinch_v1, uint32_t ಸಮಯ,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;

    ಆದರೆ (seat->ಸೂಚಕ_2.gesture_focus) {
        ಸ್ಥಿರಾಂಕ Uint64 timestamp = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ s = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->ಸೂಚಕ_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_ಕೊನೆ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_ಸೂಚಕ_gesture_pinch_v1 *zwp_ಸೂಚಕ_gesture_pinch_v1, uint32_t serial, uint32_t ಸಮಯ, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;

    ಆದರೆ (seat->ಸೂಚಕ_2.gesture_focus) {
        ಸ್ಥಿರಾಂಕ Uint64 timestamp = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);
        SDL_SendPinch(SDL_EVENT_PINCH_ಕೊನೆ, timestamp, seat->ಸೂಚಕ_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->ಸೂಚಕ_2.gesture_focus = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_ಸೂಚಕ_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_ಕೊನೆ
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Create_ಸೂಚಕ_Gestures(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->display->zwp_ಸೂಚಕ_gestures) {
        ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ && !seat->ಸೂಚಕ_2.gesture_pinch) {
            seat->ಸೂಚಕ_2.gesture_pinch = zwp_ಸೂಚಕ_gestures_v1_get_pinch_gesture(seat->display->zwp_ಸೂಚಕ_gestures, seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
            zwp_ಸೂಚಕ_gesture_pinch_v1_ಗಣ_user_ದತ್ತಾಂಶ(seat->ಸೂಚಕ_2.gesture_pinch, seat);
            zwp_ಸೂಚಕ_gesture_pinch_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Init_ಸೂಚಕ_Gesture_Manager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_ಸೂಚಕ_Gestures(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->display->cursor_shape_manager) {
        ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ && !seat->ಸೂಚಕ_2.cursor_state.cursor_shape) {
            seat->ಸೂಚಕ_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_ಸೂಚಕ(seat->display->cursor_shape_manager, seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ಆದರೆ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayInitCursorShapeManager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_ಗಣ_Keymap(SDL_WaylandSeat *seat)
{
    ಸ್ಥಿರಾಂಕ bool send_event = !seat->display->initializing;

    ಆದರೆ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_ಗಣ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_ಗಣ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ಸ್ಥಿರ ಶೂನ್ಯ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ಆಗ (elapsed >= repeat_info->ಮುಂದಿನ_repeat_ns) {
        ಆದರೆ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ಸ್ಥಿರಾಂಕ Uint64 timestamp = repeat_info->ತಳ_ಸಮಯ_ns + repeat_info->ಮುಂದಿನ_repeat_ns;
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_ತಳ(timestamp), repeat_info->keyboard_id, repeat_info->ಕೀಲಿ, repeat_info->scancode, true);
        }
        ಆದರೆ (repeat_info->ಪಠ್ಯ[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_ಪಠ್ಯ(repeat_info->ಪಠ್ಯ);
        }
        repeat_info->ಮುಂದಿನ_repeat_ns += SDL_NS_ಪ್ರತಿ_ಎರಡನೇ / (Uint64)repeat_info->repeat_ದರ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_repeat_ಗಣ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ಕೀಲಿ, Uint32 wl_press_ಸಮಯ_ms,
                                Uint64 ತಳ_ಸಮಯ_ns, uint32_t scancode, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    ಆದರೆ (!repeat_info->repeat_ದರ) {
        ಹಿಂತಿರುಗಿ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ಕೀಲಿ = ಕೀಲಿ;
    repeat_info->wl_press_ಸಮಯ_ms = wl_press_ಸಮಯ_ms;
    repeat_info->ತಳ_ಸಮಯ_ns = ತಳ_ಸಮಯ_ns;
    repeat_info->sdl_press_ಸಮಯ_ns = SDL_GetTicksNS();
    repeat_info->ಮುಂದಿನ_repeat_ns = SDL_MS_ಗಮ್ಯ_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ಆದರೆ (ಪಠ್ಯ) {
        SDL_strlcpy(repeat_info->ಪಠ್ಯ, ಪಠ್ಯ, SDL_arraysize(repeat_info->ಪಠ್ಯ));
    } ಇಲ್ಲದಿದ್ದರೆ {
        repeat_info->ಪಠ್ಯ[0] = '\0';
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ sync_ಮುಗಿದ_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ಸ್ಥಿರ ರಚನೆ wl_callback_listener sync_listener = {
    sync_ಮುಗಿದ_handler
};

ಶೂನ್ಯ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *d = _this->ಆಂತರಿಕ;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ರಚನೆ wl_callback *cb = wl_display_sync(d->display);
    wl_callback_ಕೂಡಿಸು_listener(cb, &sync_listener, ಖಾಲಿ);
    WAYLAND_wl_display_flush(d->display);
}

ಪೂರ್ಣಾಂಕ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ದತ್ತಾಂಶ *d = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;
    Uint64 ಆರಂಭ = SDL_GetTicksNS();
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ಪೂರ್ಣಾಂಕ ret;
    bool poll_alarm_ಗಣ = false;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    SDL_ಕಿಟಕಿ *keyboard_focus = SDL_GetKeyboardFocus();
    ಆದರೆ (!d->ಪಠ್ಯ_ಒಳಹರಿವು_manager && keyboard_focus && SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ಆದರೆ (timeoutNS < 0 || SDL_MS_ಗಮ್ಯ_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_ಗಮ್ಯ_NS(200);
            poll_alarm_ಗಣ = true;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ಆದರೆ (seat->keyboard.repeat.ಕೀಲಿ) {
            ಸ್ಥಿರಾಂಕ Uint64 elapsed = ಆರಂಭ - seat->keyboard.repeat.sdl_press_ಸಮಯ_ns;
            ಸ್ಥಿರಾಂಕ Uint64 ಮುಂದಿನ_repeat_wait_ಸಮಯ = (seat->keyboard.repeat.ಮುಂದಿನ_repeat_ns - elapsed) + 1;
            ಆದರೆ (timeoutNS < 0 || ಮುಂದಿನ_repeat_wait_ಸಮಯ <= timeoutNS) {
                timeoutNS = ಮುಂದಿನ_repeat_wait_ಸಮಯ;
                poll_alarm_ಗಣ = true;
            }
        }
    }

    ಆದರೆ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ಆದರೆ (timeoutNS > 0) {
            ಸ್ಥಿರಾಂಕ Uint64 now = SDL_GetTicksNS();
            ಸ್ಥಿರಾಂಕ Uint64 elapsed = now - ಆರಂಭ;
            ಆರಂಭ = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ಆದರೆ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ಆದರೆ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ಆದರೆ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ಹಿಂತಿರುಗಿ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ಆದರೆ (timeoutNS > 0) {
            ಸ್ಥಿರಾಂಕ Uint64 now = SDL_GetTicksNS();
            ಸ್ಥಿರಾಂಕ Uint64 elapsed = now - ಆರಂಭ;
            ಆರಂಭ = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ಆದರೆ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ಆದರೆ (ret == 0) {
                ಹಿಂತಿರುಗಿ poll_alarm_ಗಣ ? 1 : 0;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Pump events on an interrupt or broken pipe to handle the error.
                ಹಿಂತಿರುಗಿ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ಆದರೆ (ret == -1) {
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ಹಿಂತಿರುಗಿ 1;
}

ಶೂನ್ಯ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *d = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ಪೂರ್ಣಾಂಕ ret = 0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    SDL_ಕಿಟಕಿ *keyboard_focus = SDL_GetKeyboardFocus();
    ಆದರೆ (!d->ಪಠ್ಯ_ಒಳಹರಿವು_manager && keyboard_focus && SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ಆದರೆ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ಆದರೆ (ret < 0) {
            ಹೋಗು connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ಆದರೆ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ಆದರೆ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_ಗಮ್ಯ_NS(4));
            ಆದರೆ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ಆದರೆ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            ಹೋಗು connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ಆದರೆ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ಆದರೆ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ಇಲ್ಲದಿದ್ದರೆ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ಆದರೆ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ಆದರೆ (seat->keyboard.repeat.ಕೀಲಿ) {
                Wayland_Seat_ಗಣ_Keymap(seat);

                ಸ್ಥಿರಾಂಕ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_ಸಮಯ_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ಆದರೆ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = seat->ಸೂಚಕ_2.focus;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 ? ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow : ಖಾಲಿ;

    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2) {
        ದ್ವಿಗುಣ sx = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sx);
        ದ್ವಿಗುಣ sy = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sy);

        ಆದರೆ (seat->ಸೂಚಕ_2.focus_surface == ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.surface) {
            sx += (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x;
            sy += (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y;
        }

        sx *= ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.x;
        sy *= ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.y;
        ಆದರೆ (!warp) {
            SDL_SendMouseMotion(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, false, (ದಶಮಾಂಶ)sx, (ದಶಮಾಂಶ)sy);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_SendMouseWarp(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, (ದಶಮಾಂಶ)sx, (ದಶಮಾಂಶ)sy);
        }

        seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion.x = (ಪೂರ್ಣಾಂಕ)SDL_floor(sx);
        seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion.y = (ಪೂರ್ಣಾಂಕ)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ಆದರೆ (!SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->mouse_rect) && !seat->ಸೂಚಕ_2.is_confined) {
            Wayland_Seat_Update_ಸೂಚಕ_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE) && ಕಿಟಕಿ->ದೊರಕಿತು_test) {
            SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ rc = ಕಿಟಕಿ->ದೊರಕಿತು_test(ಕಿಟಕಿ, &seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion, ಕಿಟಕಿ->ದೊರಕಿತು_test_ದತ್ತಾಂಶ);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ಆಯ್ಕೆ (rc) {
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT:
                ಆದರೆ ((ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) &&
                    (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ)) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_RESIZE_ಎಡ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_RESIZE_ತುದಿ;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ:
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT:
                ಆದರೆ ((ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) &&
                    (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ)) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_RESIZE_ಬಲ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_RESIZE_ತುದಿ;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ:
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ಆದರೆ ((ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ)) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ಬಲ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM:
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ಆದರೆ ((ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ)) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ಎಡ;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ:
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_ಸಾಮಾನ್ಯ;
                }
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (rc != ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ) {
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ = rc;
                Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_motion(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                  uint32_t ಸಮಯ, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ Uint64 timestamp = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);

    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sx = sx;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sy = sy;

    ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) >= WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ಆದರೆ (!seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_relative || seat->ಸೂಚಕ_2.timestamps) {
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = timestamp;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = timestamp;
        ಸೂಚಕ_dispatch_absolute_motion(seat, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface);
    ಆದರೆ (!ಕಿಟಕಿ) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ಕಿಟಕಿ->surface != seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_ಗಣ_Default_Cursor(seat);
        ಹಿಂತಿರುಗಿ;
    }

    seat->ಸೂಚಕ_2.focus = ಕಿಟಕಿ;
    seat->ಸೂಚಕ_2.focus_surface = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface;
    ++ಕಿಟಕಿ->ಸೂಚಕ_focus_ಎಣಿಕೆ;
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ->sdlwindow);

    // Send the initial position.
    ಸೂಚಕ_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_ಸೂಚಕ_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_enter(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                 uint32_t serial, ರಚನೆ wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ಆದರೆ (!surface) {
        // Enter event for a destroyed surface.
        ಹಿಂತಿರುಗಿ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface = surface;
    seat->ಸೂಚಕ_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sx = sx_w;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sy = sy_w;

    ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) < WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = 0;
        ಸೂಚಕ_dispatch_enter(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_leave(SDL_WaylandSeat *seat, bool update_ಸೂಚಕ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface);

    ಆದರೆ (ಕಿಟಕಿ) {
        ಆದರೆ (seat->ಸೂಚಕ_2.focus) {
            ಆದರೆ (seat->ಸೂಚಕ_2.focus->surface == seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface) {
                // Clear the capture flag and raise all buttons
                ಕಿಟಕಿ->sdlwindow->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_CAPTURE;

                seat->ಸೂಚಕ_2.focus = ಖಾಲಿ;
                seat->ಸೂಚಕ_2.focus_surface = ಖಾಲಿ;
                ಗಾಗಿ (Uint8 i = 1; seat->ಸೂಚಕ_2.buttons_pressed; ++i) {
                    ಆದರೆ (seat->ಸೂಚಕ_2.buttons_pressed & SDL_BUTTON_ಮುಖವಾಡ(i)) {
                        SDL_SendMouseButton(0, ಕಿಟಕಿ->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, i, false);
                        seat->ಸೂಚಕ_2.buttons_pressed &= ~SDL_BUTTON_ಮುಖವಾಡ(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_ಕಿಟಕಿ *mouse_focus = SDL_GetMouseFocus();
                ಸ್ಥಿರಾಂಕ bool had_focus = mouse_focus && ಕಿಟಕಿ->sdlwindow == mouse_focus;
                ಆದರೆ (!--ಕಿಟಕಿ->ಸೂಚಕ_focus_ಎಣಿಕೆ && had_focus && !ಕಿಟಕಿ->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ) {
                    SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
                }

                ಆದರೆ (update_ಸೂಚಕ) {
                    Wayland_Seat_Update_ಸೂಚಕ_Grab(seat);
                    Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (update_ಸೂಚಕ) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_leave(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                 uint32_t serial, ರಚನೆ wl_surface *surface)
{
    ಆದರೆ (!surface) {
        // Leave event for a destroyed surface.
        ಹಿಂತಿರುಗಿ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = surface;
    ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) < WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        ಸೂಚಕ_dispatch_leave(seat, true);
    }
}

ಸ್ಥಿರ bool Wayland_Process_ದೊರಕಿತು_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ಆದರೆ (seat->ಸೂಚಕ_2.locked_ಸೂಚಕ) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = seat->ಸೂಚಕ_2.focus;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow;

    ಆದರೆ (ಕಿಟಕಿ->ದೊರಕಿತು_test) {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_ಅಂಚು_ತುದಿ_ಎಡ, XDG_TOPLEVEL_RESIZE_ಅಂಚು_ತುದಿ,
            XDG_TOPLEVEL_RESIZE_ಅಂಚು_ತುದಿ_ಬಲ, XDG_TOPLEVEL_RESIZE_ಅಂಚು_ಬಲ,
            XDG_TOPLEVEL_RESIZE_ಅಂಚು_BOTTOM_ಬಲ, XDG_TOPLEVEL_RESIZE_ಅಂಚು_BOTTOM,
            XDG_TOPLEVEL_RESIZE_ಅಂಚು_BOTTOM_ಎಡ, XDG_TOPLEVEL_RESIZE_ಅಂಚು_ಎಡ
        };

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_ಅಂಚು_ತುದಿ_ಎಡ, LIBDECOR_RESIZE_ಅಂಚು_ತುದಿ,
            LIBDECOR_RESIZE_ಅಂಚು_ತುದಿ_ಬಲ, LIBDECOR_RESIZE_ಅಂಚು_ಬಲ,
            LIBDECOR_RESIZE_ಅಂಚು_BOTTOM_ಬಲ, LIBDECOR_RESIZE_ಅಂಚು_BOTTOM,
            LIBDECOR_RESIZE_ಅಂಚು_BOTTOM_ಎಡ, LIBDECOR_RESIZE_ಅಂಚು_ಎಡ
        };
#ಆದರೆ_ಅಂತ್ಯ

        ಆಯ್ಕೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ) {
        ಸ್ಥಿತಿ SDL_HITTEST_DRAGGABLE:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
            ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
                    libdecor_ಚೌಕಟ್ಟು_move(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.libdecor.ಚೌಕಟ್ಟು,
                                        seat->wl_seat,
                                        serial);
                }
            } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ಹಿಂತಿರುಗಿ true;

        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
            ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
                    libdecor_ಚೌಕಟ್ಟು_resize(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.libdecor.ಚೌಕಟ್ಟು,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ಹಿಂತಿರುಗಿ true;

        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool ಕೆಳಕ್ಕೆ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = seat->ಸೂಚಕ_2.focus;

    ಆದರೆ (ಕಿಟಕಿ) {
        bool ignore_click = false;

        ಆದರೆ (ಕೆಳಕ್ಕೆ) {
            seat->ಸೂಚಕ_2.buttons_pressed |= SDL_BUTTON_ಮುಖವಾಡ(sdl_button);

            ಆದರೆ (sdl_button == SDL_BUTTON_ಎಡ && Wayland_Process_ದೊರಕಿತು_Test(seat, seat->ಕೊನೆಯ_implicit_grab_serial)) {
                ಹಿಂತಿರುಗಿ; // don't pass this event on to app.
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->ಸೂಚಕ_2.buttons_pressed &= ~SDL_BUTTON_ಮುಖವಾಡ(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ಆದರೆ (ಕಿಟಕಿ->ಕೊನೆಯ_focus_event_ಸಮಯ_ns) {
            ಆದರೆ (ಕೆಳಕ್ಕೆ && (SDL_GetTicksNS() - ಕಿಟಕಿ->ಕೊನೆಯ_focus_event_ಸಮಯ_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            ಕಿಟಕಿ->ಕೊನೆಯ_focus_event_ಸಮಯ_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        ಆದರೆ (!seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
            ಆದರೆ (seat->ಸೂಚಕ_2.buttons_pressed != 0) {
                ಕಿಟಕಿ->sdlwindow->flags |= SDL_ಕಿಟಕಿ_MOUSE_CAPTURE;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ->sdlwindow->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ಆದರೆ (seat->ಸೂಚಕ_2.focus_surface != ಕಿಟಕಿ->surface) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = ಕಿಟಕಿ->surface;
                }
            }
        }

        ಆದರೆ (!ignore_click) {
            SDL_SendMouseButton(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns, ಕಿಟಕಿ->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, sdl_button, ಕೆಳಕ್ಕೆ);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_button(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2, uint32_t serial,
                                  uint32_t ಸಮಯ, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    Uint8 sdl_button;

    ಆಯ್ಕೆ (button) {
    ಸ್ಥಿತಿ BTN_ಎಡ:
        sdl_button = SDL_BUTTON_ಎಡ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ BTN_ಮಧ್ಯ:
        sdl_button = SDL_BUTTON_ಮಧ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ BTN_ಬಲ:
        sdl_button = SDL_BUTTON_ಬಲ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);

    ಆದರೆ (wl_seat_get_ಆವೃತ್ತಿ(seat->wl_seat) >= WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        ಆದರೆ (state_w) {
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_pressed |= SDL_BUTTON_ಮುಖವಾಡ(sdl_button);
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_released |= SDL_BUTTON_ಮುಖವಾಡ(sdl_button);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸೂಚಕ_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = seat->ಸೂಚಕ_2.focus;
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ wl_ಸೂಚಕ_axis a = axis;

    ಆದರೆ (seat->ಸೂಚಕ_2.focus) {
        ದಶಮಾಂಶ x, y;

        ಆಯ್ಕೆ (a) {
        ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_HORIZONTAL_SCROLL:
            x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
            y = 0;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, ಕಿಟಕಿ->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, x, y, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_common(SDL_WaylandSeat *seat, ಎಣಿಕೆ SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ wl_ಸೂಚಕ_axis a = axis;

    ಆದರೆ (seat->ಸೂಚಕ_2.focus) {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_axis = true;

        ಆಯ್ಕೆ (a) {
        ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_VERTICAL_SCROLL:
            ಆಯ್ಕೆ (type) {
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y = 0.0f;
                }
                seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y += 0 - (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y = 0 - (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y = 0 - (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                }
                ನಿಲ್ಲಿಸು;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_HORIZONTAL_SCROLL:
            ಆಯ್ಕೆ (type) {
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x = 0.0f;
                }
                seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x += (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(ಮೌಲ್ಯ);
                }
                ನಿಲ್ಲಿಸು;
            }
            ನಿಲ್ಲಿಸು;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                uint32_t ಸಮಯ, uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ Uint64 nsTimestamp = Wayland_Get_ಸೂಚಕ_Timestamp(seat, ಸಮಯ);

    ಆದರೆ (wl_seat_get_ಆವೃತ್ತಿ(seat->wl_seat) >= WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = nsTimestamp;
        ಸೂಚಕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, ಮೌಲ್ಯ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸೂಚಕ_handle_axis_common_v1(seat, nsTimestamp, axis, ಮೌಲ್ಯ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_relative_direction(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;

    ಆಯ್ಕೆ (axis_relative_direction) {
    ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.direction = SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ WL_ಸೂಚಕ_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = seat->ಸೂಚಕ_2.focus;

    ಆದರೆ (ಕಿಟಕಿ) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ದ್ವಿಗುಣ dx;
        ದ್ವಿಗುಣ dy;
        ಆದರೆ (mouse->ಒಳಹರಿವು_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dx_unaccel);
            dy = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dy_unaccel);
        } ಇಲ್ಲದಿದ್ದರೆ {
            dx = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dx) * ಕಿಟಕಿ->ಸೂಚಕ_scale.x;
            dy = wl_fixed_ಗಮ್ಯ_double(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dy) * ಕಿಟಕಿ->ಸೂಚಕ_scale.y;
        }

        SDL_SendMouseMotion(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns, ಕಿಟಕಿ->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, true, (ದಶಮಾಂಶ)dx, (ದಶಮಾಂಶ)dy);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_dispatch_axis(SDL_WaylandSeat *seat)
{
    ದಶಮಾಂಶ x, y;
    SDL_MouseWheelDirection direction = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.direction;

    ಆಯ್ಕೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x_axis_type) {
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.x / 120.0f;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        x = 0.0f;
        ನಿಲ್ಲಿಸು;
    }

    ಆಯ್ಕೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y_axis_type) {
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis.y / 120.0f;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        y = 0.0f;
        ನಿಲ್ಲಿಸು;
    }

    SDL_SendMouseWheel(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns,
                       seat->ಸೂಚಕ_2.focus->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, x, y, direction);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_ಚೌಕಟ್ಟು(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;

    ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface) {
        ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = seat->ಸೂಚಕ_2.focus;
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *new_focus = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface);

            ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 && (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE) && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->ಸೂಚಕ_2.focus_surface = seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface;
                seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface = ಖಾಲಿ;
                seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = ಖಾಲಿ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Leaving the previous surface before entering a new surface.
                ಸೂಚಕ_dispatch_leave(seat, false);
                seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = ಖಾಲಿ;
            }
        }

        ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.enter_surface) {
            ಸೂಚಕ_dispatch_enter(seat);
        }
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_absolute) {
        ಸೂಚಕ_dispatch_absolute_motion(seat, seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_warp);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_relative) {
        ಸೂಚಕ_dispatch_relative_motion(seat);
    }

    ಗಾಗಿ (Uint8 i = 1; seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_pressed || seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_released; ++i) {
        ಸ್ಥಿರಾಂಕ Uint32 ಮುಖವಾಡ = SDL_BUTTON_ಮುಖವಾಡ(i);
        ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_pressed & ಮುಖವಾಡ) {
            ಸೂಚಕ_dispatch_button(seat, i, true);
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_pressed &= ~ಮುಖವಾಡ;
        }
        ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_released & ಮುಖವಾಡ) {
            ಸೂಚಕ_dispatch_button(seat, i, false);
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.buttons_released &= ~ಮುಖವಾಡ;
        }
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_axis) {
        ಸೂಚಕ_dispatch_axis(seat);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface) {
        ಸೂಚಕ_dispatch_leave(seat, true);
    }

    SDL_zero(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_ಮೂಲ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                       uint32_t axis_ಮೂಲ)
{
    // unimplemented
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_stop(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                     uint32_t ಸಮಯ, uint32_t axis)
{
    // unimplemented
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_discrete(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಸೂಚಕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_axis_value120(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *ಸೂಚಕ_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಸೂಚಕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸೂಚಕ_handle_warp(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಸೂಚಕ *wl_ಸೂಚಕ, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;

    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_absolute = true;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_warp = true;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sx = surface_x;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.absolute.sy = surface_y;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_ಸೂಚಕ_listener ಸೂಚಕ_listener = {
    ಸೂಚಕ_handle_enter,
    ಸೂಚಕ_handle_leave,
    ಸೂಚಕ_handle_motion,
    ಸೂಚಕ_handle_button,
    ಸೂಚಕ_handle_axis,
    ಸೂಚಕ_handle_ಚೌಕಟ್ಟು,                   // Version 5
    ಸೂಚಕ_handle_axis_ಮೂಲ,             // Version 5
    ಸೂಚಕ_handle_axis_stop,               // Version 5
    ಸೂಚಕ_handle_axis_discrete,           // Version 5
    ಸೂಚಕ_handle_axis_value120,           // Version 8
    ಸೂಚಕ_handle_axis_relative_direction, // Version 9
    ಸೂಚಕ_handle_warp                     // Version 11
};

ಸ್ಥಿರ ಶೂನ್ಯ relative_ಸೂಚಕ_handle_relative_motion(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                    ರಚನೆ zwp_relative_ಸೂಚಕ_v1 *ಸೂಚಕ_2,
                                                    uint32_t ಸಮಯ_hi,
                                                    uint32_t ಸಮಯ_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;

    // Relative pointer event times are in microsecond granularity.
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dx = dx;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dy = dy;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dx_unaccel = dx_unaccel;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.relative.dy_unaccel = dy_unaccel;
    seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.timestamp_ns = Wayland_Adjust_Event_Timestamp_ತಳ(SDL_US_ಗಮ್ಯ_NS(((Uint64)ಸಮಯ_hi << 32) | (Uint64)ಸಮಯ_lo));

    ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) >= WL_ಸೂಚಕ_ಚೌಕಟ್ಟು_SINCE_ಆವೃತ್ತಿ) {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.have_relative = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸೂಚಕ_dispatch_relative_motion(seat);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_relative_ಸೂಚಕ_v1_listener relative_ಸೂಚಕ_listener = {
    relative_ಸೂಚಕ_handle_relative_motion,
};

ಸ್ಥಿರ ಶೂನ್ಯ locked_ಸೂಚಕ_locked(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_locked_ಸೂಚಕ_v1 *locked_ಸೂಚಕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.is_confined = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ locked_ಸೂಚಕ_unlocked(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_locked_ಸೂಚಕ_v1 *locked_ಸೂಚಕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.is_confined = false;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_locked_ಸೂಚಕ_v1_listener locked_ಸೂಚಕ_listener = {
    locked_ಸೂಚಕ_locked,
    locked_ಸೂಚಕ_unlocked,
};

ಸ್ಥಿರ ಶೂನ್ಯ confined_ಸೂಚಕ_confined(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_confined_ಸೂಚಕ_v1 *confined_ಸೂಚಕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.is_confined = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ confined_ಸೂಚಕ_unconfined(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_confined_ಸೂಚಕ_v1 *confined_ಸೂಚಕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಸೂಚಕ_2.is_confined = false;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_confined_ಸೂಚಕ_v1_listener confined_ಸೂಚಕ_listener = {
    confined_ಸೂಚಕ_confined,
    confined_ಸೂಚಕ_unconfined,
};

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_ಕೆಳಕ್ಕೆ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ರಚನೆ wl_surface *surface,
                               ಪೂರ್ಣಾಂಕ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;

    // Check that this surface is valid.
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_Seat_ಕೂಡಿಸು_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);

    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->surface == surface) {
        ದಶಮಾಂಶ x, y;

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಅಗಲ <= 1) {
            x = 0.5f;
        } ಇಲ್ಲದಿದ್ದರೆ {
            x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fx) / (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಅಗಲ - 1);
        }
        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಎತ್ತರ <= 1) {
            y = 0.5f;
        } ಇಲ್ಲದಿದ್ದರೆ {
            y = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fy) / (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಎತ್ತರ - 1);
        }

        ++ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;
        SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, 1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_ಮೇಲೆ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *touch, uint32_t serial, uint32_t timestamp, ಪೂರ್ಣಾಂಕ id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    wl_fixed_t fx = 0, fy = 0;
    ರಚನೆ wl_surface *surface = ಖಾಲಿ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ಆದರೆ (surface) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->surface == surface) {
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fx) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಅಗಲ;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fy) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಎತ್ತರ;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, 0.0f);

            --ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ಆದರೆ (SDL_GetMouseFocus() == ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow && !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->keyboard_focus_ಎಣಿಕೆ &&
                !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_focus_ಎಣಿಕೆ && !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ) {
                SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_motion(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *touch, uint32_t timestamp, ಪೂರ್ಣಾಂಕ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    ರಚನೆ wl_surface *surface = ಖಾಲಿ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ಆದರೆ (surface) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->surface == surface) {
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ x = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fx) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಅಗಲ;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ y = (ದಶಮಾಂಶ)wl_fixed_ಗಮ್ಯ_double(fy) / ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->current.logical_ಎತ್ತರ;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_ಚೌಕಟ್ಟು(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *touch)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_cancel(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    SDL_Wayland_Touch_ಬಿಂದು *tp, *ತಾತ್ಕಾಲಿಕ;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_ಸುರಕ್ಷಿತ (tp, ತಾತ್ಕಾಲಿಕ, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_shape(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_orientation(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_touch_listener touch_listener = {
    touch_handler_ಕೆಳಕ್ಕೆ,
    touch_handler_ಮೇಲೆ,
    touch_handler_motion,
    touch_handler_ಚೌಕಟ್ಟು,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ಆದರೆ !SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(1, 0, 0)
ಸ್ಥಿರ size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ಕೀಲಿ, xkb_layout_ಸೂಚ್ಯಂಕ_t layout, xkb_level_ಸೂಚ್ಯಂಕ_t level, xkb_mod_ಮುಖವಾಡ_t *masks_ಹೊರಹೋಗು, size_t masks_ಗಾತ್ರ)
{
    ಆದರೆ (!masks_ಹೊರಹೋಗು || !masks_ಗಾತ್ರ) {
        ಹಿಂತಿರುಗಿ 0;
    }

    // Level 0 is always unmodified, so early out.
    ಆದರೆ (level == 0) {
        *masks_ಹೊರಹೋಗು = 0;
        ಹಿಂತಿರುಗಿ 1;
    }

    size_t ಮುಖವಾಡ_idx = 0;
    ಸ್ಥಿರಾಂಕ xkb_mod_ಮುಖವಾಡ_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ,
        seat->keyboard.xkb.caps_ಮುಖವಾಡ_2,
        seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ | seat->keyboard.xkb.caps_ಮುಖವಾಡ_2,
        seat->keyboard.xkb.level3_ಮುಖವಾಡ,
        seat->keyboard.xkb.level3_ಮುಖವಾಡ | seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ,
        seat->keyboard.xkb.level3_ಮುಖವಾಡ | seat->keyboard.xkb.caps_ಮುಖವಾಡ_2,
        seat->keyboard.xkb.level3_ಮುಖವಾಡ | seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ | seat->keyboard.xkb.caps_ಮುಖವಾಡ_2,
        seat->keyboard.xkb.level5_ಮುಖವಾಡ,
        seat->keyboard.xkb.level5_ಮುಖವಾಡ | seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ,
        seat->keyboard.xkb.level5_ಮುಖವಾಡ | seat->keyboard.xkb.caps_ಮುಖವಾಡ_2,
        seat->keyboard.xkb.level5_ಮುಖವಾಡ | seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ | seat->keyboard.xkb.caps_ಮುಖವಾಡ_2
    };
    ಸ್ಥಿರಾಂಕ xkb_mod_ಮುಖವಾಡ_t pressed_mod_ಮುಖವಾಡ = seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ | seat->keyboard.xkb.level3_ಮುಖವಾಡ | seat->keyboard.xkb.level5_ಮುಖವಾಡ;
    ಸ್ಥಿರಾಂಕ xkb_mod_ಮುಖವಾಡ_t locked_mod_ಮುಖವಾಡ = seat->keyboard.xkb.caps_ಮುಖವಾಡ_2;

    ಗಾಗಿ (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_ಮುಖವಾಡ(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_ಮುಖವಾಡ, 0, keymod_masks[i] & locked_mod_ಮುಖವಾಡ, 0, 0, layout);
        ಆದರೆ (WAYLAND_xkb_state_ಕೀಲಿ_get_level(seat->keyboard.xkb.state, ಕೀಲಿ, layout) == level) {
            masks_ಹೊರಹೋಗು[ಮುಖವಾಡ_idx] = keymod_masks[i];

            ಆದರೆ (++ಮುಖವಾಡ_idx == masks_ಗಾತ್ರ) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ_idx;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_KeymapIterator(ರಚನೆ xkb_keymap *keymap, xkb_keycode_t ಕೀಲಿ, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ಸ್ಥಿರಾಂಕ xkb_mod_ಮುಖವಾಡ_t xkb_valid_mod_ಮುಖವಾಡ = seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ |
                                              seat->keyboard.xkb.alt_ಮುಖವಾಡ |
                                              seat->keyboard.xkb.level3_ಮುಖವಾಡ |
                                              seat->keyboard.xkb.level5_ಮುಖವಾಡ |
                                              seat->keyboard.xkb.caps_ಮುಖವಾಡ_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ಆದರೆ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_ಕೋಷ್ಟಕ(SDL_SCANCODE_ಕೋಷ್ಟಕ_LINUX, ಕೀಲಿ - 8);
    }

    ಗಾಗಿ (xkb_layout_ಸೂಚ್ಯಂಕ_t layout = 0; layout < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++layout) {
        ಸ್ಥಿರಾಂಕ xkb_level_ಸೂಚ್ಯಂಕ_t ಅಂಕೆ_ಮಟ್ಟಗಳು = WAYLAND_xkb_keymap_ಅಂಕೆ_ಮಟ್ಟಗಳು_for_ಕೀಲಿ(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout);
        ಗಾಗಿ (xkb_level_ಸೂಚ್ಯಂಕ_t level = 0; level < ಅಂಕೆ_ಮಟ್ಟಗಳು; ++level) {
            ಆದರೆ (WAYLAND_xkb_keymap_ಕೀಲಿ_get_syms_by_level(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ಕೀಲಿ_Sym(syms[0], ಕೀಲಿ);
                    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
                        ಮುಂದುವರಿ;
                    }
                }

                xkb_mod_ಮುಖವಾಡ_t xkb_mod_masks[16];
#ಆದರೆ SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(1, 0, 0)
                ಸ್ಥಿರಾಂಕ size_t ಅಂಕೆ_masks = WAYLAND_xkb_keymap_ಕೀಲಿ_get_mods_for_level(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ಇಲ್ಲದಿದ್ದರೆ
                ಸ್ಥಿರಾಂಕ size_t ಅಂಕೆ_masks = xkb_legacy_get_mods_for_level(seat, ಕೀಲಿ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ಆದರೆ_ಅಂತ್ಯ
                ಗಾಗಿ (size_t ಮುಖವಾಡ = 0; ಮುಖವಾಡ < ಅಂಕೆ_masks; ++ಮುಖವಾಡ) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ಆದರೆ ((xkb_mod_masks[ಮುಖವಾಡ] | xkb_valid_mod_ಮುಖವಾಡ) != xkb_valid_mod_ಮುಖವಾಡ) {
                        ಮುಂದುವರಿ;
                    }

                    ಸ್ಥಿರಾಂಕ SDL_Keymod sdl_mod = (xkb_mod_masks[ಮುಖವಾಡ] & seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ ? SDL_KMOD_ಸರಿಸು : 0) |
                                               (xkb_mod_masks[ಮುಖವಾಡ] & seat->keyboard.xkb.alt_ಮುಖವಾಡ ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[ಮುಖವಾಡ] & seat->keyboard.xkb.level3_ಮುಖವಾಡ ? SDL_KMOD_ಬಹುಲಕ : 0) |
                                               (xkb_mod_masks[ಮುಖವಾಡ] & seat->keyboard.xkb.level5_ಮುಖವಾಡ ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[ಮುಖವಾಡ] & seat->keyboard.xkb.caps_ಮುಖವಾಡ_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_ಸಂಕೇತ_From_ಕೀಲಿ_Sym(syms[0], ಕೀಲಿ, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ಆದರೆ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_ಮುಂದಿನ_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        ಆದರೆ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_ಗಣ_Keymap_ನಮೂದು(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ಕೀಲಿ *res = WAYLAND_wl_array_ಕೂಡಿಸು(&seat->keyboard.reserved_scancodes, ಗಾತ್ರ(Wayland_Reserved_ಕೀಲಿ));
                        ಆದರೆ (res) {
                            res->scancode = scancode;
                            res->ಕೀಲಿ = ಕೀಲಿ - 8;
                        }
                    }

                    ಆದರೆ (!keycode) {
                        ಆಯ್ಕೆ (scancode) {
                        ಸ್ಥಿತಿ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ನಿಲ್ಲಿಸು;
                        ಸ್ಥಿತಿ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ನಿಲ್ಲಿಸು;
                        ಸ್ಥಿತಿ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ನಿಲ್ಲಿಸು;
                        ಸ್ಥಿತಿ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ನಿಲ್ಲಿಸು;
                        ಪೂರ್ವನಿಯೋಜಿತ:
                            keycode = SDL_SCANCODE_ಗಮ್ಯ_KEYCODE(scancode);
                            ನಿಲ್ಲಿಸು;
                        }
                    }

                    SDL_ಗಣ_Keymap_ನಮೂದು(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_keymap(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *keyboard,
                                   uint32_t format, ಪೂರ್ಣಾಂಕ fd, uint32_t ಗಾತ್ರ_2)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಅಕ್ಷರ *map_str;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        close(fd);
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ಹಿಂತಿರುಗಿ;
    }

    map_str = mmap(ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ, MAP_PRIVATE, fd, 0);
    ಆದರೆ (map_str == MAP_FAILED) {
        close(fd);
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (seat->keyboard.xkb.keymap != ಖಾಲಿ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ಖಾಲಿ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_ಪಠ್ಯ_V1,
                                                                   0);
    munmap(map_str, ಗಾತ್ರ_2);
    close(fd);

    ಆದರೆ (!seat->keyboard.xkb.keymap) {
        SDL_ಗಣ_Error("failed to compile keymap");
        ಹಿಂತಿರುಗಿ;
    }

    // Clear the old layouts.
    ಗಾಗಿ (xkb_layout_ಸೂಚ್ಯಂಕ_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ಖಾಲಿ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.ಅಂಕೆ_layouts = 0;

#ಆದರೆ SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(1, 10, 0)
    seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_ಸರಿಸು);
    seat->keyboard.xkb.ctrl_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.ಅಂಕೆ_ಮುಖವಾಡ = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ಅಂಕೆ);
    seat->keyboard.xkb.caps_ಮುಖವಾಡ_2 = WAYLAND_xkb_keymap_mod_get_ಮುಖವಾಡ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GET_MOD_ಸೂಚ್ಯಂಕ(mod) \
    WAYLAND_xkb_keymap_mod_get_ಸೂಚ್ಯಂಕ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(ಸರಿಸು_2);
    seat->keyboard.xkb.ctrl_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(CTRL);
    seat->keyboard.xkb.alt_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(ALT);
    seat->keyboard.xkb.gui_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(MOD5);
    seat->keyboard.xkb.level5_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(MOD3);
    seat->keyboard.xkb.ಅಂಕೆ_ಮುಖವಾಡ = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(ಅಂಕೆ_2);
    seat->keyboard.xkb.caps_ಮುಖವಾಡ_2 = 1 << GET_MOD_ಸೂಚ್ಯಂಕ(CAPS);
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು GET_MOD_ಸೂಚ್ಯಂಕ
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (seat->keyboard.xkb.state != ಖಾಲಿ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ಖಾಲಿ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ಆದರೆ (!seat->keyboard.xkb.state) {
        SDL_ಗಣ_Error("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ಖಾಲಿ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.ಅಂಕೆ_layouts = WAYLAND_xkb_keymap_ಅಂಕೆ_layouts(seat->keyboard.xkb.keymap);
    ಆದರೆ (seat->keyboard.xkb.ಅಂಕೆ_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.ಅಂಕೆ_layouts, ಗಾತ್ರ(SDL_Keymap *));
        ಆದರೆ (!seat->keyboard.sdl_keymap) {
            ಹಿಂತಿರುಗಿ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        ಗಾಗಿ (xkb_layout_ಸೂಚ್ಯಂಕ_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ಆದರೆ (!seat->keyboard.sdl_keymap[i]) {
                ಗಾಗಿ (xkb_layout_ಸೂಚ್ಯಂಕ_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ಖಾಲಿ;
                ಹಿಂತಿರುಗಿ;
            }
        }

        WAYLAND_xkb_keymap_ಕೀಲಿ_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_ಮುಖವಾಡ(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_ಗಣ_Keymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *locale = SDL_getenv("LC_ALL");
    ಆದರೆ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ಆದರೆ (!locale) {
            locale = SDL_getenv("LANG");
            ಆದರೆ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ಆದರೆ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ಆದರೆ (seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ != ಖಾಲಿ) {
            WAYLAND_xkb_compose_ಕೋಷ್ಟಕ_unref(seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ);
            seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ = ಖಾಲಿ;
        }
        seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ = WAYLAND_xkb_compose_ಕೋಷ್ಟಕ_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ಆದರೆ (seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ) {
            // Set up XKB compose state
            ಆದರೆ (seat->keyboard.xkb.compose_state != ಖಾಲಿ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ಖಾಲಿ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ಆದರೆ (!seat->keyboard.xkb.compose_state) {
                SDL_ಗಣ_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_ಕೋಷ್ಟಕ_unref(seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ);
                seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ = ಖಾಲಿ;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ಸ್ಥಿರ SDL_Scancode Wayland_Get_Scancode_For_ಕೀಲಿ(SDL_WaylandSeat *seat, Uint32 ಕೀಲಿ, ಸ್ಥಿರಾಂಕ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ಆದರೆ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_ಕೋಷ್ಟಕ(SDL_SCANCODE_ಕೋಷ್ಟಕ_LINUX, ಕೀಲಿ);

        // No table entry? Check the reserved list.
        ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ಕೀಲಿ *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ಆದರೆ (i->ಕೀಲಿ == ಕೀಲಿ) {
                    ಹಿಂತಿರುಗಿ i->scancode;
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ xkb_keysym_t *keysym;
        ಆದರೆ (WAYLAND_xkb_state_ಕೀಲಿ_get_syms(seat->keyboard.xkb.state, ಕೀಲಿ + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ಕೀಲಿ_Sym(keysym[0], ಕೀಲಿ + 8);
            ಆದರೆ (syms) {
                *syms = keysym;
            }
        }
    }

    ಹಿಂತಿರುಗಿ scancode;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ಕೀಲಿ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ಆದರೆ (!ಕೀಲಿ_pressed) {
        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ಸರಿಸು)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ಸರಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ಸರಿಸು;
        }

        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ಬಹುಲಕ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ಬಹುಲಕ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ಬಹುಲಕ;
        }

        ಆದರೆ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_ಮುಖವಾಡ) {
            ಆದರೆ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_LEVEL5;
        }
    }

    /* If a latch or lock was activated by a keypress, the latch/lock will
     * be tied to the specific left/right key that initiated it. Otherwise,
     * the ambiguous left/right combo is used.
     *
     * The modifier will remain active until the latch/lock is released by
     * the system.
     */
    ಸ್ಥಿರಾಂಕ xkb_mod_ಮುಖವಾಡ_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.ಸರಿಸು_ಮುಖವಾಡ) {
        ಆದರೆ (seat->keyboard.pressed_modifiers & SDL_KMOD_ಸರಿಸು) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ಸರಿಸು;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ಸರಿಸು);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ಸರಿಸು)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ಸರಿಸು;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ಸರಿಸು;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_ಮುಖವಾಡ) {
        ಆದರೆ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.alt_ಮುಖವಾಡ) {
        ಆದರೆ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.gui_ಮುಖವಾಡ) {
        ಆದರೆ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.level3_ಮುಖವಾಡ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ಬಹುಲಕ;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.level5_ಮುಖವಾಡ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.caps_ಮುಖವಾಡ_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ಆದರೆ (xkb_locked_modifiers & seat->keyboard.xkb.ಅಂಕೆ_ಮುಖವಾಡ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ಅಂಕೆ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ಅಂಕೆ;
    }

    SDL_ಗಣ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Handle_Modifier_ಕೀಲಿಗಳು(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ಸ್ಥಿರಾಂಕ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ಆಯ್ಕೆ (keycode) {
    ಸ್ಥಿತಿ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_ಬಹುಲಕ:
        mod = SDL_KMOD_ಬಹುಲಕ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDLK_LEVEL5_ಸರಿಸು:
        mod = SDL_KMOD_LEVEL5;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ಇಲ್ಲದಿದ್ದರೆ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_enter(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *keyboard,
                                  uint32_t serial, ರಚನೆ wl_surface *surface,
                                  ರಚನೆ wl_array *ಕೀಲಿಗಳು)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    uint32_t *ಕೀಲಿ;

    ಆದರೆ (!surface) {
        // Enter event for a destroyed surface.
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);
    ಆದರೆ (!ಕಿಟಕಿ) {
        // Not a surface owned by SDL.
        ಹಿಂತಿರುಗಿ;
    }

    ++ಕಿಟಕಿ->keyboard_focus_ಎಣಿಕೆ;
    seat->keyboard.focus = ಕಿಟಕಿ;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ->sdlwindow->keyboard_focus ? ಕಿಟಕಿ->sdlwindow->keyboard_focus : ಕಿಟಕಿ->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_ಸೂಚಕ_Grabs(seat->display, ಕಿಟಕಿ);

    // Update text input and IME focus.
    Wayland_Seat_Update_ಪಠ್ಯ_ಒಳಹರಿವು(seat);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    ಆದರೆ (!seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು) {
        SDL_IME_ಗಣ_Focus(true);
    }
#ಆದರೆ_ಅಂತ್ಯ

    Uint64 timestamp = SDL_GetTicksNS();
    ಕಿಟಕಿ->ಕೊನೆಯ_focus_event_ಸಮಯ_ns = timestamp;

    Wayland_Seat_ಗಣ_Keymap(seat);

    wl_array_for_each (ಕೀಲಿ, ಕೀಲಿಗಳು) {
        ಸ್ಥಿರಾಂಕ SDL_Scancode scancode = Wayland_Get_Scancode_For_ಕೀಲಿ(seat, *ಕೀಲಿ, ಖಾಲಿ);
        ಆದರೆ (scancode != SDL_SCANCODE_UNKNOWN) {
            ಸ್ಥಿರಾಂಕ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ಆಯ್ಕೆ (keycode) {
            ಸ್ಥಿತಿ SDLK_LSHIFT:
            ಸ್ಥಿತಿ SDLK_RSHIFT:
            ಸ್ಥಿತಿ SDLK_LCTRL:
            ಸ್ಥಿತಿ SDLK_RCTRL:
            ಸ್ಥಿತಿ SDLK_LALT:
            ಸ್ಥಿತಿ SDLK_RALT:
            ಸ್ಥಿತಿ SDLK_LGUI:
            ಸ್ಥಿತಿ SDLK_RGUI:
            ಸ್ಥಿತಿ SDLK_ಬಹುಲಕ:
            ಸ್ಥಿತಿ SDLK_LEVEL5_ಸರಿಸು:
                Wayland_Handle_Modifier_ಕೀಲಿಗಳು(seat, scancode, true);
                SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ಕೀಲಿ, scancode, true);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_leave(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *keyboard,
                                  uint32_t serial, ರಚನೆ wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;

    ಆದರೆ (!surface) {
        // Leave event for a destroyed surface.
        ಹಿಂತಿರುಗಿ;
    }

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface);
    ಆದರೆ (!ಕಿಟಕಿ) {
        // Not a surface owned by SDL.
        ಹಿಂತಿರುಗಿ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ಕೀಲಿ = 0;

    SDL_ಕಿಟಕಿ *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ಆಗ (keyboard_focus && SDL_ಕಿಟಕಿ_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->ಪೋಷಕ;
    }

    ಸ್ಥಿರಾಂಕ bool had_focus = keyboard_focus && ಕಿಟಕಿ->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ಖಾಲಿ;
    --ಕಿಟಕಿ->keyboard_focus_ಎಣಿಕೆ;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ಆದರೆ (!ಕಿಟಕಿ->keyboard_focus_ಎಣಿಕೆ && had_focus) {
        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_ಸೂಚಕ_Grabs(seat->display, ಕಿಟಕಿ);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_ಪಠ್ಯ_ಒಳಹರಿವು(seat);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    ಆದರೆ (!seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು && !ಕಿಟಕಿ->keyboard_focus_ಎಣಿಕೆ) {
        SDL_IME_ಗಣ_Focus(false);
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ಆದರೆ (SDL_GetMouseFocus() == ಕಿಟಕಿ->sdlwindow && !ಕಿಟಕಿ->ಸೂಚಕ_focus_ಎಣಿಕೆ && !ಕಿಟಕಿ->ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ) {
        SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_Offer(seat->ದತ್ತಾಂಶ_device, ಖಾಲಿ);
}

ಸ್ಥಿರ bool keyboard_ಒಳಹರಿವು_get_ಪಠ್ಯ(ಅಕ್ಷರ ಪಠ್ಯ[8], ಸ್ಥಿರಾಂಕ SDL_WaylandSeat *seat, uint32_t ಕೀಲಿ, bool ಕೆಳಕ್ಕೆ, bool *handled_by_ime)
{
    ಸ್ಥಿರಾಂಕ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ಆದರೆ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ಹಿಂತಿರುಗಿ false;
    }

    // TODO: Can this happen?
    ಆದರೆ (WAYLAND_xkb_state_ಕೀಲಿ_get_syms(seat->keyboard.xkb.state, ಕೀಲಿ + 8, &syms) != 1) {
        ಹಿಂತಿರುಗಿ false;
    }
    sym = syms[0];

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_IME
    ಆದರೆ (SDL_IME_Process_ಕೀಲಿ_Event(sym, ಕೀಲಿ + 8, ಕೆಳಕ್ಕೆ)) {
        ಆದರೆ (handled_by_ime) {
            *handled_by_ime = true;
        }
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!ಕೆಳಕ್ಕೆ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ಆಯ್ಕೆ (WAYLAND_xkb_compose_state_get_ಸ್ಥಿತಿ(seat->keyboard.xkb.compose_state)) {
        ಸ್ಥಿತಿ XKB_COMPOSE_COMPOSING:
            ಆದರೆ (handled_by_ime) {
                *handled_by_ime = true;
            }
            ಹಿಂತಿರುಗಿ true;
        ಸ್ಥಿತಿ XKB_COMPOSE_CANCELLED:
        ಪೂರ್ವನಿಯೋಜಿತ:
            sym = XKB_ಕೀಲಿ_No_ಚಿಹ್ನೆ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XKB_COMPOSE_NOTHING:
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ನಿಲ್ಲಿಸು;
        }
    }

    ಹಿಂತಿರುಗಿ WAYLAND_xkb_keysym_ಗಮ್ಯ_utf8(sym, ಪಠ್ಯ, 8) > 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_ಕೀಲಿ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *keyboard,
                                uint32_t serial, uint32_t ಸಮಯ, uint32_t ಕೀಲಿ,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಎಣಿಕೆ wl_keyboard_ಕೀಲಿ_state state = state_w;
    ಅಕ್ಷರ ಪಠ್ಯ[8];
    bool has_ಪಠ್ಯ = false;
    bool handled_by_ime = false;
    ಸ್ಥಿರಾಂಕ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, ಸಮಯ);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ಆದರೆ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ಆದರೆ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ಕೀಲಿ_repeats(seat->keyboard.xkb.keymap, ಕೀಲಿ + 8)) {
            ಹಿಂತಿರುಗಿ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED;
    }

    Wayland_Seat_ಗಣ_Keymap(seat);

    ಆದರೆ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED) {
        SDL_ಕಿಟಕಿ *keyboard_focus = SDL_GetKeyboardFocus();
        ಆದರೆ (keyboard_focus && SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(keyboard_focus)) {
            has_ಪಠ್ಯ = keyboard_ಒಳಹರಿವು_get_ಪಠ್ಯ(ಪಠ್ಯ, seat, ಕೀಲಿ, true, &handled_by_ime);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಕೀಲಿ == seat->keyboard.repeat.ಕೀಲಿ) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ಸ್ಥಿರಾಂಕ Uint64 elapsed = SDL_MS_ಗಮ್ಯ_NS(ಸಮಯ - seat->keyboard.repeat.wl_press_ಸಮಯ_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ಕೀಲಿ = 0;
        }
        keyboard_ಒಳಹರಿವು_get_ಪಠ್ಯ(ಪಠ್ಯ, seat, ಕೀಲಿ, false, &handled_by_ime);
    }

    ಸ್ಥಿರಾಂಕ xkb_keysym_t *syms = ಖಾಲಿ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ಕೀಲಿ(seat, ಕೀಲಿ, &syms);
    Wayland_Handle_Modifier_ಕೀಲಿಗಳು(seat, scancode, state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ಸ್ಥಿರಾಂಕ SDL_Keycode keycode = (SDL_Keycode)SDL_ಕೀಲಿ_Sym_ಗಮ್ಯ_Ucs4(syms[0]);
        ಆದರೆ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_ಮುಖವಾಡ) {
                scancode = SDL_Get_Keymap_ಮುಂದಿನ_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_ಗಣ_Keymap_ನಮೂದು(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ಕೀಲಿ, scancode, state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED);

    ಆದರೆ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED) {
        ಆದರೆ (handled_by_ime) {
            has_ಪಠ್ಯ = false;
        }
        ಆದರೆ (has_ಪಠ್ಯ && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_ಪಠ್ಯ(ಪಠ್ಯ);
        }
        ಆದರೆ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ಕೀಲಿ_repeats(seat->keyboard.xkb.keymap, ಕೀಲಿ + 8)) {
            keyboard_repeat_ಗಣ(&seat->keyboard.repeat, seat->keyboard.sdl_id, ಕೀಲಿ, ಸಮಯ, timestamp_ns, scancode, has_ಪಠ್ಯ ? ಪಠ್ಯ : ಖಾಲಿ);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_modifiers(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t ಗುಂಪು)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ uint32_t ಹಿಂದಿನ_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = ಗುಂಪು;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ಆದರೆ (!seat->keyboard.xkb.state) {
        ಹಿಂತಿರುಗಿ;
    }

    WAYLAND_xkb_state_update_ಮುಖವಾಡ(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, ಗುಂಪು);

    // If a key is repeating, update the text to apply the modifier.
    ಆದರೆ (seat->keyboard.repeat.ಕೀಲಿ) {
        ಅಕ್ಷರ ಪಠ್ಯ[8];

        ಆದರೆ (keyboard_ಒಳಹರಿವು_get_ಪಠ್ಯ(ಪಠ್ಯ, seat, seat->keyboard.repeat.ಕೀಲಿ, true, ಖಾಲಿ)) {
            SDL_strlcpy(seat->keyboard.repeat.ಪಠ್ಯ, ಪಠ್ಯ, SDL_arraysize(seat->keyboard.repeat.ಪಠ್ಯ));
        }
    }

    ಆದರೆ (ಗುಂಪು != ಹಿಂದಿನ_layout) {
        Wayland_Seat_ಗಣ_Keymap(seat);

        ಆದರೆ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_repeat_info(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_keyboard *wl_keyboard,
                                        int32_t ದರ, int32_t delay)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ;
    seat->keyboard.repeat.repeat_ದರ = ದರ;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ಆದರೆ (!ದರ) {
        seat->keyboard.repeat.ಕೀಲಿ = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ಕೀಲಿ,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Destroy_ಸೂಚಕ(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->ಸೂಚಕ_2.cursor_state);

    // End any active gestures.
    ಆದರೆ (seat->ಸೂಚಕ_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_ಕೊನೆ, 0, seat->ಸೂಚಕ_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ಆದರೆ (seat->ಸೂಚಕ_2.focus) {
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = seat->ಸೂಚಕ_2.focus->surface;
        ಸೂಚಕ_dispatch_leave(seat, false);
        seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = ಖಾಲಿ;
    }

    SDL_RemoveMouse(seat->ಸೂಚಕ_2.sdl_id);

    ಆದರೆ (seat->ಸೂಚಕ_2.confined_ಸೂಚಕ) {
        zwp_confined_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.confined_ಸೂಚಕ);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.locked_ಸೂಚಕ) {
        zwp_locked_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.locked_ಸೂಚಕ);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
        zwp_relative_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.relative_ಸೂಚಕ);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->ಸೂಚಕ_2.timestamps);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.gesture_pinch) {
        zwp_ಸೂಚಕ_gesture_pinch_v1_destroy(seat->ಸೂಚಕ_2.gesture_pinch);
    }

    ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
        ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) >= WL_ಸೂಚಕ_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            wl_ಸೂಚಕ_release(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_ಸೂಚಕ_destroy(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
        }
    }

    SDL_zero(seat->ಸೂಚಕ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ಆದರೆ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ಆದರೆ (seat->keyboard.sdl_keymap) {
        ಆದರೆ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_ಗಣ_Mod_State(SDL_KMOD_NONE);
        }
        ಗಾಗಿ (xkb_layout_ಸೂಚ್ಯಂಕ_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ಖಾಲಿ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ಆದರೆ (seat->keyboard.ಕೀಲಿ_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ಕೀಲಿ_inhibitor);
    }

    ಆದರೆ (seat->keyboard.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ಆದರೆ (seat->keyboard.wl_keyboard) {
        ಆದರೆ (wl_keyboard_get_ಆವೃತ್ತಿ(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ಆದರೆ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ಆದರೆ (seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ) {
        WAYLAND_xkb_compose_ಕೋಷ್ಟಕ_unref(seat->keyboard.xkb.compose_ಕೋಷ್ಟಕ);
    }

    ಆದರೆ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ಆದರೆ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ಆದರೆ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ಆದರೆ (seat->touch.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ಆದರೆ (seat->touch.wl_touch) {
        ಆದರೆ (wl_touch_get_ಆವೃತ್ತಿ(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            wl_touch_release(seat->touch.wl_touch);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ಸ್ಥಿರ ಶೂನ್ಯ seat_handle_capabilities(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    ಅಕ್ಷರ name_fmt[256];

    ಆದರೆ ((capabilities & WL_SEAT_CAPABILITY_ಸೂಚಕ) && !seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
        seat->ಸೂಚಕ_2.wl_ಸೂಚಕ = wl_seat_get_ಸೂಚಕ(wl_seat);
        SDL_zero(seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_ಸೂಚಕ_ಗಣ_user_ದತ್ತಾಂಶ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ, seat);
        wl_ಸೂಚಕ_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ, &ಸೂಚಕ_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_ಸೂಚಕ_Gestures(seat);

        seat->ಸೂಚಕ_2.sdl_id = SDL_Get_ಮುಂದಿನ_Object_ID();

        ಆದರೆ (seat->name) {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_ಸೂಚಕ_NAME, seat->name);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_ಸೂಚಕ_NAME, seat->ಸೂಚಕ_2.sdl_id);
        }

        SDL_ಕೂಡಿಸು_Mouse(seat->ಸೂಚಕ_2.sdl_id, name_fmt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(capabilities & WL_SEAT_CAPABILITY_ಸೂಚಕ) && seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
        Wayland_Seat_Destroy_ಸೂಚಕ(seat);
    }

    ಆದರೆ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_ಗಣ_user_ದತ್ತಾಂಶ(seat->touch.wl_touch, seat);
        wl_touch_ಕೂಡಿಸು_listener(seat->touch.wl_touch, &touch_listener, seat);

        ಆದರೆ (seat->name) {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_ಕೂಡಿಸು_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_ನೇರ, name_fmt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ಆದರೆ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_ಗಣ_user_ದತ್ತಾಂಶ(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_ಕೂಡಿಸು_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_ಮುಂದಿನ_Object_ID();

        ಆದರೆ (seat->name) {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_snprintf(name_fmt, ಗಾತ್ರ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_ಕೂಡಿಸು_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_ರಿಜಿಸ್ಟರ್_ಒಳಹರಿವು_Timestamp_Listeners(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ seat_handle_name(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_seat *wl_seat, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;

    ಆದರೆ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_offer_handle_offer(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_offer *wl_ದತ್ತಾಂಶ_offer,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer = ದತ್ತಾಂಶ;
    Wayland_ದತ್ತಾಂಶ_Offer_ಕೂಡಿಸು_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_ದತ್ತಾಂಶ_offer ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)wl_ದತ್ತಾಂಶ_offer) : -1),
                 mime_type);
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_offer_handle_ಮೂಲ_actions(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_offer *wl_ದತ್ತಾಂಶ_offer,
                                             uint32_t ಮೂಲ_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_ದತ್ತಾಂಶ_offer ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)wl_ದತ್ತಾಂಶ_offer) : -1),
                 ಮೂಲ_actions);
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_offer_handle_actions(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_offer *wl_ದತ್ತಾಂಶ_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_ದತ್ತಾಂಶ_offer ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)wl_ದತ್ತಾಂಶ_offer) : -1),
                 dnd_action);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_ದತ್ತಾಂಶ_offer_listener ದತ್ತಾಂಶ_offer_listener = {
    ದತ್ತಾಂಶ_offer_handle_offer,
    ದತ್ತಾಂಶ_offer_handle_ಮೂಲ_actions, // Version 3
    ದತ್ತಾಂಶ_offer_handle_actions,        // Version 3
};

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_offer_handle_offer(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = ದತ್ತಾಂಶ;
    Wayland_Primary_Selection_Offer_ಕೂಡಿಸು_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_ದತ್ತಾಂಶ_offer(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device,
                                          ರಚನೆ wl_ದತ್ತಾಂಶ_offer *id)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *ದತ್ತಾಂಶ_offer = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ_offer));
    ಆದರೆ (ದತ್ತಾಂಶ_offer) {
        SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = (SDL_Wayland_ದತ್ತಾಂಶ_Device *)ದತ್ತಾಂಶ;
        ದತ್ತಾಂಶ_offer->offer = id;
        ದತ್ತಾಂಶ_offer->ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ_device;
        ದತ್ತಾಂಶ_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(ದತ್ತಾಂಶ_offer->mimes));
        wl_ದತ್ತಾಂಶ_offer_ಗಣ_user_ದತ್ತಾಂಶ(id, ದತ್ತಾಂಶ_offer);
        wl_ದತ್ತಾಂಶ_offer_ಕೂಡಿಸು_listener(id, &ದತ್ತಾಂಶ_offer_listener, ದತ್ತಾಂಶ_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id) : -1));
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_enter(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device,
                                     uint32_t serial, ರಚನೆ wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ರಚನೆ wl_ದತ್ತಾಂಶ_offer *id)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = surface ? Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface) : ಖಾಲಿ;
    ದತ್ತಾಂಶ_device->has_mime_file = false;
    ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type = ಖಾಲಿ;

    ದತ್ತಾಂಶ_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ಆದರೆ (id) {
        ದತ್ತಾಂಶ_device->drag_offer = wl_ದತ್ತಾಂಶ_offer_get_user_ದತ್ತಾಂಶ(id);
    }

    ಆದರೆ (ದತ್ತಾಂಶ_device->drag_offer && ಕಿಟಕಿ && ಕಿಟಕಿ->ಸ್ವೀಕರಿಸು_drag_and_drop) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
        ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(ದತ್ತಾಂಶ_device->drag_offer, FILE_PORTAL_MIME)) {
            ದತ್ತಾಂಶ_device->has_mime_file = true;
            wl_ದತ್ತಾಂಶ_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(ದತ್ತಾಂಶ_device->drag_offer, FILE_MIME)) {
            ದತ್ತಾಂಶ_device->has_mime_file = true;
            wl_ದತ್ತಾಂಶ_offer_accept(id, serial, FILE_MIME);
        }

        ಆದರೆ (!ದತ್ತಾಂಶ_device->has_mime_file) {
            size_t mime_ಎಣಿಕೆ = 0;
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *ಪಠ್ಯ_mime_types = Wayland_Get_ಪಠ್ಯ_Mime_Types(SDL_GetVideoDevice(), &mime_ಎಣಿಕೆ);
            ಗಾಗಿ (size_t i = 0; i < mime_ಎಣಿಕೆ; ++i) {
                ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(ದತ್ತಾಂಶ_device->drag_offer, ಪಠ್ಯ_mime_types[i])) {
                    ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type = ಪಠ್ಯ_mime_types[i];
                    wl_ದತ್ತಾಂಶ_offer_accept(id, serial, ಪಠ್ಯ_mime_types[i]);
                    ನಿಲ್ಲಿಸು;
                }
            }
        }

        ಆದರೆ (ದತ್ತಾಂಶ_device->has_mime_file || ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type) {
            // SDL only supports "copy" style drag and drop
            ಆದರೆ (wl_ದತ್ತಾಂಶ_offer_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ_device->drag_offer->offer) >= WL_ದತ್ತಾಂಶ_OFFER_ಗಣ_ACTIONS_SINCE_ಆವೃತ್ತಿ) {
                wl_ದತ್ತಾಂಶ_offer_ಗಣ_actions(ದತ್ತಾಂಶ_device->drag_offer->offer, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_COPY, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ = ಕಿಟಕಿ->sdlwindow;
            ದತ್ತಾಂಶ_device->dnd_surface = surface;
            ದ್ವಿಗುಣ dx = wl_fixed_ಗಮ್ಯ_double(x);
            ದ್ವಿಗುಣ dy = wl_fixed_ಗಮ್ಯ_double(y);

            // If over the mask, adjust the offset.
            ಆದರೆ (surface == ಕಿಟಕಿ->ಮುಖವಾಡ.surface) {
                dx += (ದ್ವಿಗುಣ)ಕಿಟಕಿ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x;
                dy += (ದ್ವಿಗುಣ)ಕಿಟಕಿ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y;
            }

            dx *= ಕಿಟಕಿ->ಸೂಚಕ_scale.x;
            dy *= ಕಿಟಕಿ->ಸೂಚಕ_scale.y;

            SDL_SendDropPosition(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ, (ದಶಮಾಂಶ)dx, (ದಶಮಾಂಶ)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id),
                         wl_fixed_ಗಮ್ಯ_int(x), wl_fixed_ಗಮ್ಯ_int(y), SDL_Get_ಕಿಟಕಿ_ID(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ), serial);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Decline the offer.
            wl_ದತ್ತಾಂಶ_offer_accept(id, serial, ಖಾಲಿ);
            ಆದರೆ (wl_ದತ್ತಾಂಶ_offer_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ_device->drag_offer->offer) >= WL_ದತ್ತಾಂಶ_OFFER_ಗಣ_ACTIONS_SINCE_ಆವೃತ್ತಿ) {
                wl_ದತ್ತಾಂಶ_offer_ಗಣ_actions(ದತ್ತಾಂಶ_device->drag_offer->offer, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_NONE, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id), wl_fixed_ಗಮ್ಯ_int(x), wl_fixed_ಗಮ್ಯ_int(y), serial);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ = ಖಾಲಿ;
        ದತ್ತಾಂಶ_device->dnd_surface = ಖಾಲಿ;

        // Decline the offer.
        ಆದರೆ (id) {
            wl_ದತ್ತಾಂಶ_offer_accept(id, serial, ಖಾಲಿ);
            ಆದರೆ (wl_ದತ್ತಾಂಶ_offer_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ_device->drag_offer->offer) >= WL_ದತ್ತಾಂಶ_OFFER_ಗಣ_ACTIONS_SINCE_ಆವೃತ್ತಿ) {
                wl_ದತ್ತಾಂಶ_offer_ಗಣ_actions(ದತ್ತಾಂಶ_device->drag_offer->offer, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_NONE, WL_ದತ್ತಾಂಶ_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id) : -1,
                     wl_fixed_ಗಮ್ಯ_int(x), wl_fixed_ಗಮ್ಯ_int(y), serial);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_leave(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ;

    ಆದರೆ (ದತ್ತಾಂಶ_device->drag_offer) {
        ಆದರೆ (ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ) {
            SDL_SendDropComplete(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ_device->drag_offer->offer),
                         SDL_Get_ಕಿಟಕಿ_ID(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ), ದತ್ತಾಂಶ_device->drag_serial);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ_device->drag_offer->offer),
                         ದತ್ತಾಂಶ_device->drag_serial);
        }
        Wayland_ದತ್ತಾಂಶ_Offer_Destroy(ದತ್ತಾಂಶ_device->drag_offer);
        ದತ್ತಾಂಶ_device->drag_offer = ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    ದತ್ತಾಂಶ_device->has_mime_file = false;
    ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_motion(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device,
                                      uint32_t ಸಮಯ, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ;

    ಆದರೆ (ದತ್ತಾಂಶ_device->drag_offer && ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ && (ದತ್ತಾಂಶ_device->has_mime_file || ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ->ಆಂತರಿಕ;
        ದ್ವಿಗುಣ dx = wl_fixed_ಗಮ್ಯ_double(x);
        ದ್ವಿಗುಣ dy = wl_fixed_ಗಮ್ಯ_double(y);

        // If over the mask, adjust the offset.
        ಆದರೆ (ದತ್ತಾಂಶ_device->dnd_surface == ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.surface) {
            dx += (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x;
            dy += (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y;
        }

        dx *= ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.x;
        dy *= ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಸೂಚಕ_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ, (ದಶಮಾಂಶ)dx, (ದಶಮಾಂಶ)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ_device->drag_offer->offer),
                     wl_fixed_ಗಮ್ಯ_int(x), wl_fixed_ಗಮ್ಯ_int(y),
                     SDL_Get_ಕಿಟಕಿ_ID(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ), ದತ್ತಾಂಶ_device->drag_serial);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_ಗಮ್ಯ_int(x), wl_fixed_ಗಮ್ಯ_int(y), -1);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ drop_cleanup_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    Wayland_Drop_ದತ್ತಾಂಶ *drop = (Wayland_Drop_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ drop_dispatch_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    Wayland_Drop_ದತ್ತಾಂಶ *drop = (Wayland_Drop_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer = drop->offer;
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = offer->ದತ್ತಾಂಶ_device;

    ಆದರೆ (drop->dnd_ಕಿಟಕಿ) {
        size_t ಉದ್ದಳತೆ;
        bool drop_handled = false;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
        ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            ಶೂನ್ಯ *ಬಫರ್_2 = Wayland_ದತ್ತಾಂಶ_Offer_Receive(offer, FILE_PORTAL_MIME, &ಉದ್ದಳತೆ);
            ಆದರೆ (ಬಫರ್_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ಆದರೆ (dbus) {
                    ಪೂರ್ಣಾಂಕ ಮಾರ್ಗ_ಎಣಿಕೆ = 0;
                    ಅಕ್ಷರ **paths = SDL_DBus_DocumentsPortalRetrieveFiles(ಬಫರ್_2, &ಮಾರ್ಗ_ಎಣಿಕೆ);
                    // If dropped files contain a directory the list is empty
                    ಆದರೆ (paths && ಮಾರ್ಗ_ಎಣಿಕೆ > 0) {
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಮಾರ್ಗ_ಎಣಿಕೆ; i++) {
                            SDL_SendDropFile(drop->dnd_ಕಿಟಕಿ, ಖಾಲಿ, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(ಬಫರ್_2);
            }
        }
#ಆದರೆ_ಅಂತ್ಯ
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        ಆದರೆ (!drop_handled) {
            ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(offer, FILE_MIME)) {
                ಶೂನ್ಯ *ಬಫರ್_2 = Wayland_ದತ್ತಾಂಶ_Offer_Receive(offer, FILE_MIME, &ಉದ್ದಳತೆ);
                ಆದರೆ (ಬಫರ್_2) {
                    ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                    ಅಕ್ಷರ *token = SDL_strtok_r((ಅಕ್ಷರ *)ಬಫರ್_2, "\r\n", &saveptr);
                    ಆಗ (token) {
                        ಆದರೆ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_ಕಿಟಕಿ, ಖಾಲಿ, token);
                        }
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    SDL_free(ಬಫರ್_2);
                    drop_handled = true;
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(offer, drop->ಪಠ್ಯ_mime_type)) {
                ಶೂನ್ಯ *ಬಫರ್_2 = Wayland_ದತ್ತಾಂಶ_Offer_Receive(offer, drop->ಪಠ್ಯ_mime_type, &ಉದ್ದಳತೆ);
                ಆದರೆ (ಬಫರ್_2) {
                    ಅಕ್ಷರ *saveptr = ಖಾಲಿ;
                    ಅಕ್ಷರ *token = SDL_strtok_r((ಅಕ್ಷರ *)ಬಫರ್_2, "\r\n", &saveptr);
                    ಆಗ (token) {
                        SDL_Send_Drop_ಪಠ್ಯ(drop->dnd_ಕಿಟಕಿ, token);
                        token = SDL_strtok_r(ಖಾಲಿ, "\r\n", &saveptr);
                    }
                    SDL_free(ಬಫರ್_2);
                    drop_handled = true;
                }
            }
        }

        ಆದರೆ (drop_handled && wl_ದತ್ತಾಂಶ_offer_get_ಆವೃತ್ತಿ(offer->offer) >= WL_ದತ್ತಾಂಶ_OFFER_ಮುಕ್ತಾಯ_SINCE_ಆವೃತ್ತಿ) {
            wl_ದತ್ತಾಂಶ_offer_ಮುಕ್ತಾಯ(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_ಕಿಟಕಿ);
    }

    Wayland_ದತ್ತಾಂಶ_Offer_Destroy(drop->offer);
    drop->offer = ಖಾಲಿ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(ದತ್ತಾಂಶ_device->seat->display->display);
    wl_callback_ಕೂಡಿಸು_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_drop(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ;

    ಆದರೆ (ದತ್ತಾಂಶ_device->drag_offer && ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ &&
        (ದತ್ತಾಂಶ_device->has_mime_file || ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ_device->drag_offer->offer),
                     SDL_Get_ಕಿಟಕಿ_ID(ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ), ದತ್ತಾಂಶ_device->drag_serial);

        Wayland_ಕೆಲಸ_Thread_Context *ctx = ದತ್ತಾಂಶ_device->seat->display->ಕೆಲಸ_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_ದತ್ತಾಂಶ *drop = SDL_calloc(1, ಗಾತ್ರ(Wayland_Drop_ದತ್ತಾಂಶ));
        ಆದರೆ (drop) {
            drop->offer = ದತ್ತಾಂಶ_device->drag_offer;
            drop->dnd_ಕಿಟಕಿ = ದತ್ತಾಂಶ_device->dnd_ಕಿಟಕಿ;
            drop->ಪಠ್ಯ_mime_type = ದತ್ತಾಂಶ_device->ಪಠ್ಯ_mime_type;

            WAYLAND_wl_list_ಸೇರಿಸು(&ದತ್ತಾಂಶ_device->pending_drops, &drop->link);
            Wayland_ಕೆಲಸ_Thread_ಕೂಡಿಸು_ಕೆಲಸ(ctx, drop_dispatch_handler, drop, &drop->id);
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_ದತ್ತಾಂಶ_Offer_Destroy(ದತ್ತಾಂಶ_device->drag_offer);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_ದತ್ತಾಂಶ_Offer_Destroy(ದತ್ತಾಂಶ_device->drag_offer);
    }

    ದತ್ತಾಂಶ_device->drag_offer = ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_device_handle_selection(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_device *wl_ದತ್ತಾಂಶ_device,
                                         ರಚನೆ wl_ದತ್ತಾಂಶ_offer *id)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ;
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer = ಖಾಲಿ;

    ಆದರೆ (id) {
        offer = wl_ದತ್ತಾಂಶ_offer_get_user_ದತ್ತಾಂಶ(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id) : -1));

    Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_Offer(ದತ್ತಾಂಶ_device, offer);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_ದತ್ತಾಂಶ_device_listener ದತ್ತಾಂಶ_device_listener = {
    ದತ್ತಾಂಶ_device_handle_ದತ್ತಾಂಶ_offer,
    ದತ್ತಾಂಶ_device_handle_enter,
    ದತ್ತಾಂಶ_device_handle_leave,
    ದತ್ತಾಂಶ_device_handle_motion,
    ದತ್ತಾಂಶ_device_handle_drop,
    ದತ್ತಾಂಶ_device_handle_selection
};

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_device_handle_offer(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ರಚನೆ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, ಗಾತ್ರ(*primary_selection_offer));
    ಆದರೆ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)ದತ್ತಾಂಶ;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_ಗಣ_user_ದತ್ತಾಂಶ(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_ಕೂಡಿಸು_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id) : -1));
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_device_handle_selection(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ರಚನೆ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = ದತ್ತಾಂಶ;
    SDL_WaylandPrimarySelectionOffer *offer = ಖಾಲಿ;

    ಆದರೆ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_ದತ್ತಾಂಶ(id);
    }

    ಆದರೆ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ರಚನೆ wl_proxy *)id) : -1));
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_enter(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                             ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                             ರಚನೆ wl_surface *surface)
{
    // No-op
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_leave(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                             ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                             ರಚನೆ wl_surface *surface)
{
    // No-op
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_preedit_string(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                      ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ,
                                      int32_t cursor_begin,
                                      int32_t cursor_ಕೊನೆ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    seat->ಪಠ್ಯ_ಒಳಹರಿವು.has_preedit = true;
    ಆದರೆ (ಪಠ್ಯ) {
        ಪೂರ್ಣಾಂಕ cursor_begin_utf8 = cursor_begin >= 0 ? (ಪೂರ್ಣಾಂಕ)SDL_utf8strnlen(ಪಠ್ಯ, cursor_begin) : -1;
        ಪೂರ್ಣಾಂಕ cursor_ಕೊನೆ_utf8 = cursor_ಕೊನೆ >= 0 ? (ಪೂರ್ಣಾಂಕ)SDL_utf8strnlen(ಪಠ್ಯ, cursor_ಕೊನೆ) : -1;
        ಪೂರ್ಣಾಂಕ cursor_ಗಾತ್ರ_utf8;
        ಆದರೆ (cursor_ಕೊನೆ_utf8 >= 0) {
            ಆದರೆ (cursor_begin_utf8 >= 0) {
                cursor_ಗಾತ್ರ_utf8 = cursor_ಕೊನೆ_utf8 - cursor_begin_utf8;
            } ಇಲ್ಲದಿದ್ದರೆ {
                cursor_ಗಾತ್ರ_utf8 = cursor_ಕೊನೆ_utf8;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            cursor_ಗಾತ್ರ_utf8 = -1;
        }
        SDL_Send_Editing_ಪಠ್ಯ(ಪಠ್ಯ, cursor_begin_utf8, cursor_ಗಾತ್ರ_utf8);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Send_Editing_ಪಠ್ಯ("", 0, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_commit_string(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                     ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                                     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_Send_Keyboard_ಪಠ್ಯ(ಪಠ್ಯ);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_delete_surrounding_ಪಠ್ಯ(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                               ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                                               uint32_t before_ಉದ್ದಳತೆ,
                                               uint32_t after_ಉದ್ದಳತೆ)
{
    // FIXME: Do we care about this event?
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪಠ್ಯ_ಒಳಹರಿವು_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                            ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    ಆದರೆ (!seat->ಪಠ್ಯ_ಒಳಹರಿವು.has_preedit) {
        SDL_Send_Editing_ಪಠ್ಯ("", 0, 0);
    }
    seat->ಪಠ್ಯ_ಒಳಹರಿವು.has_preedit = false;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_listener ಪಠ್ಯ_ಒಳಹರಿವು_listener = {
    ಪಠ್ಯ_ಒಳಹರಿವು_enter,
    ಪಠ್ಯ_ಒಳಹರಿವು_leave,
    ಪಠ್ಯ_ಒಳಹರಿವು_preedit_string,
    ಪಠ್ಯ_ಒಳಹರಿವು_commit_string,
    ಪಠ್ಯ_ಒಳಹರಿವು_delete_surrounding_ಪಠ್ಯ,
    ಪಠ್ಯ_ಒಳಹರಿವು_ಮುಗಿದ
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_ID(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device)
{
    ಆದರೆ (!ದತ್ತಾಂಶ_device->id_str)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ಆದರೆ (dbus) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id = dbus->bus_get_unique_name(dbus->session_conn);
            ಆದರೆ (id) {
                ದತ್ತಾಂಶ_device->id_str = SDL_strdup(id);
            }
        }
    }
    ಆದರೆ (!ದತ್ತಾಂಶ_device->id_str)
#ಆದರೆ_ಅಂತ್ಯ
    {
        ಅಕ್ಷರ id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, ಗಾತ್ರ(id), "%" SDL_PRIu64, pid);
        ದತ್ತಾಂಶ_device->id_str = SDL_strdup(id);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Create_ದತ್ತಾಂಶ_Device(SDL_WaylandSeat *seat)
{
    ಆದರೆ (!seat->display->ದತ್ತಾಂಶ_device_manager) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ_device));
    ಆದರೆ (!ದತ್ತಾಂಶ_device) {
        ಹಿಂತಿರುಗಿ;
    }

    ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device = wl_ದತ್ತಾಂಶ_device_manager_get_ದತ್ತಾಂಶ_device(
        seat->display->ದತ್ತಾಂಶ_device_manager, seat->wl_seat);
    ದತ್ತಾಂಶ_device->seat = seat;

    ಆದರೆ (!ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device) {
        SDL_free(ದತ್ತಾಂಶ_device);
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_ID(ದತ್ತಾಂಶ_device);
    WAYLAND_wl_list_init(&ದತ್ತಾಂಶ_device->pending_drops);
    wl_ದತ್ತಾಂಶ_device_ಗಣ_user_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device, ದತ್ತಾಂಶ_device);
    wl_ದತ್ತಾಂಶ_device_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device, &ದತ್ತಾಂಶ_device_listener, ದತ್ತಾಂಶ_device);
    seat->ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ_device;
}

ಶೂನ್ಯ Wayland_Display_Init_ದತ್ತಾಂಶ_Device_Manager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_ದತ್ತಾಂಶ_Device(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ಆದರೆ (!seat->display->primary_selection_device_manager) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, ಗಾತ್ರ(*primary_selection_device));
    ಆದರೆ (!primary_selection_device) {
        ಹಿಂತಿರುಗಿ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ಆದರೆ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ಇಲ್ಲದಿದ್ದರೆ {
        zwp_primary_selection_device_v1_ಗಣ_user_ದತ್ತಾಂಶ(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_ಕೂಡಿಸು_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

ಶೂನ್ಯ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Create_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->display->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು = zwp_ಪಠ್ಯ_ಒಳಹರಿವು_manager_v3_get_ಪಠ್ಯ_ಒಳಹರಿವು(seat->display->ಪಠ್ಯ_ಒಳಹರಿವು_manager, seat->wl_seat);

        ಆದರೆ (seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು) {
            zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_ಗಣ_user_ದತ್ತಾಂಶ(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು, seat);
            zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_ಕೂಡಿಸು_listener(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು,
                                           &ಪಠ್ಯ_ಒಳಹರಿವು_listener, seat);
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Init_ಪಠ್ಯ_ಒಳಹರಿವು_Manager(SDL_Video_ದತ್ತಾಂಶ *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_ಪಠ್ಯ_ಒಳಹರಿವು(seat);
    }
}

// Pen/Tablet support...
ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_type(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಆಯ್ಕೆ (type) {
        #ವ್ಯಾಖ್ಯಾನಿಸು CASE(typ) ಸ್ಥಿತಿ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ಹಿಂತಿರುಗಿ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CASE
        ಪೂರ್ವನಿಯೋಜಿತ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_hardware_serial(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_hardware_id_wacom(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->info.wacom_id = id_lo;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_capability(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಆಯ್ಕೆ (capability) {
        #ವ್ಯಾಖ್ಯಾನಿಸು CASE(wltyp,sdltyp) ಸ್ಥಿತಿ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ಹಿಂತಿರುಗಿ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(ದೂರ_2, SDL_PEN_CAPABILITY_ದೂರ);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CASE
        ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;  // unsupported here.
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಆದರೆ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = sdltool->focus ? sdltool->focus->sdlwindow : ಖಾಲಿ;
        sdltool->instance_id = SDL_ಕೂಡಿಸು_Pen_Device(0, ಖಾಲಿ, ಕಿಟಕಿ, &sdltool->info, sdltool, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_removed(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಆದರೆ (sdltool->instance_id) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = sdltool->focus ? sdltool->focus->sdlwindow : ಖಾಲಿ;
        SDL_RemovePenDevice(0, ಕಿಟಕಿ, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_proximity_ಒಳ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t serial, ರಚನೆ zwp_tablet_v2 *tablet, ರಚನೆ wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = surface ? Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(surface) : ಖಾಲಿ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ಖಾಲಿ;
    sdltool->proximity_serial = serial;
    sdltool->ಚೌಕಟ್ಟು.have_proximity = true;
    sdltool->ಚೌಕಟ್ಟು.ಒಳ_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_proximity_ಹೊರಹೋಗು(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.have_proximity = true;
    sdltool->ಚೌಕಟ್ಟು.ಒಳ_proximity = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_ಕೆಳಕ್ಕೆ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.tool_state = WAYLAND_TABLET_TOOL_STATE_ಕೆಳಕ್ಕೆ;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_ಮೇಲೆ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.tool_state = WAYLAND_TABLET_TOOL_STATE_ಮೇಲೆ;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_motion(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = sdltool->focus;
    ಆದರೆ (windowdata) {
        sdltool->ಚೌಕಟ್ಟು.x = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(sx_w) * windowdata->ಸೂಚಕ_scale.x);
        sdltool->ಚೌಕಟ್ಟು.y = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(sy_w) * windowdata->ಸೂಚಕ_scale.y);
        sdltool->ಚೌಕಟ್ಟು.have_motion = true;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_pressure(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_PRESSURE] = ((ದಶಮಾಂಶ) pressure) / 65535.0f;
    sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_PRESSURE);
    ಆದರೆ (pressure) {
        sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_ದೂರ] = 0.0f;
        sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_ದೂರ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_ದೂರ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t ದೂರ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_ದೂರ] = ((ದಶಮಾಂಶ) ದೂರ) / 65535.0f;
    sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_ದೂರ);
    ಆದರೆ (ದೂರ) {
        sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_tilt(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_XTILT] = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(xtilt));
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_YTILT] = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(ytilt));
    sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_button(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ sdlbutton;

    ಆಯ್ಕೆ (button) {
    ಸ್ಥಿತಿ BTN_STYLUS:
        sdlbutton = 1;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ BTN_STYLUS2:
        sdlbutton = 2;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ BTN_STYLUS3:
        sdlbutton = 3;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->ಚೌಕಟ್ಟು.buttons)));
    sdltool->ಚೌಕಟ್ಟು.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_ಕೆಳಕ್ಕೆ : WAYLAND_TABLET_TOOL_BUTTON_ಮೇಲೆ;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_rotation(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ rotation = (ದಶಮಾಂಶ)(wl_fixed_ಗಮ್ಯ_double(degrees));
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_slider(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    sdltool->ಚೌಕಟ್ಟು.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_wheel(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_ಚೌಕಟ್ಟು(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_tool_v2 *tool, uint32_t ಸಮಯ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ SDL_PenID instance_id = sdltool->instance_id;
    ಆದರೆ (!instance_id) {
        ಹಿಂತಿರುಗಿ;  // Not a pen we report on.
    }

    ಸ್ಥಿರಾಂಕ Uint64 timestamp = Wayland_Adjust_Event_Timestamp_ತಳ(Wayland_EventTimestampMSToNS(ಸಮಯ));
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = sdltool->focus ? sdltool->focus->sdlwindow : ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.have_proximity && sdltool->ಚೌಕಟ್ಟು.ಒಳ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, ಕಿಟಕಿ, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.have_motion && sdltool->ಚೌಕಟ್ಟು.tool_state) {
        ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.tool_state == WAYLAND_TABLET_TOOL_STATE_ಕೆಳಕ್ಕೆ) {
            SDL_SendPenMotion(timestamp, instance_id, ಕಿಟಕಿ, sdltool->ಚೌಕಟ್ಟು.x, sdltool->ಚೌಕಟ್ಟು.y);
            SDL_SendPenTouch(timestamp, instance_id, ಕಿಟಕಿ, is_eraser, true);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_SendPenTouch(timestamp, instance_id, ಕಿಟಕಿ, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, ಕಿಟಕಿ, sdltool->ಚೌಕಟ್ಟು.x, sdltool->ಚೌಕಟ್ಟು.y);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, ಕಿಟಕಿ, is_eraser, sdltool->ಚೌಕಟ್ಟು.tool_state == WAYLAND_TABLET_TOOL_STATE_ಕೆಳಕ್ಕೆ);
        }

        ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, ಕಿಟಕಿ, sdltool->ಚೌಕಟ್ಟು.x, sdltool->ಚೌಕಟ್ಟು.y);
        }
    }

    ಗಾಗಿ (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ಎಣಿಕೆ; i++) {
        ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.axes_ಗಣ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, ಕಿಟಕಿ, i, sdltool->ಚೌಕಟ್ಟು.axes[i]);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(sdltool->ಚೌಕಟ್ಟು.buttons); i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ state = sdltool->ಚೌಕಟ್ಟು.buttons[i];
        ಆದರೆ (state) {
            SDL_SendPenButton(timestamp, instance_id, ಕಿಟಕಿ, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_ಕೆಳಕ್ಕೆ);
        }
    }

    ಆದರೆ (sdltool->ಚೌಕಟ್ಟು.have_proximity && !sdltool->ಚೌಕಟ್ಟು.ಒಳ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, ಕಿಟಕಿ, false, false);
        sdltool->focus = ಖಾಲಿ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->ಚೌಕಟ್ಟು);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_ಮುಗಿದ,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_ಒಳ,
    tablet_tool_handle_proximity_ಹೊರಹೋಗು,
    tablet_tool_handle_ಕೆಳಕ್ಕೆ,
    tablet_tool_handle_ಮೇಲೆ,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_ದೂರ,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_ಚೌಕಟ್ಟು
};


ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_tablet_added(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ರಚನೆ zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_tool_added(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ರಚನೆ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ದತ್ತಾಂಶ;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, ಗಾತ್ರ(*sdltool));

    ಆದರೆ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.ಅಂಕೆ_buttons = -1;

        ಆದರೆ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ಸೇರಿಸು(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_ಕೂಡಿಸು_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_pad_added(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ರಚನೆ zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_ಕೂಡಿಸು_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

ಶೂನ್ಯ Wayland_DisplayInitTabletManager(SDL_Video_ದತ್ತಾಂಶ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_remove_all_pens_callback(SDL_PenID instance_id, ಶೂನ್ಯ *handle, ಶೂನ್ಯ *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_ಕೆಳಕ್ಕೆ)
{
    ಆದರೆ (!shutting_ಕೆಳಕ್ಕೆ) {
        SDL_WaylandPenTool *tool, *ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ (tool, ತಾತ್ಕಾಲಿಕ, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ಖಾಲಿ);
    }

    ಆದರೆ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ಖಾಲಿ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

ಶೂನ್ಯ Wayland_DisplayCreateSeat(SDL_Video_ದತ್ತಾಂಶ *display, ರಚನೆ wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, ಗಾತ್ರ(SDL_WaylandSeat));
    ಆದರೆ (!seat) {
        ಹಿಂತಿರುಗಿ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ಸೇರಿಸು(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_ದತ್ತಾಂಶ_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_ಪಠ್ಯ_ಒಳಹರಿವು(seat);

    wl_seat_ಗಣ_user_ದತ್ತಾಂಶ(seat->wl_seat, seat);
    wl_seat_ಕೂಡಿಸು_listener(seat->wl_seat, &seat_listener, seat);

    ಆದರೆ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ಶೂನ್ಯ Wayland_Display_Remove_ಕಿಟಕಿ_References_From_Seats(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ಆದರೆ (seat->keyboard.focus == ಕಿಟಕಿ) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, ಕಿಟಕಿ->surface);
        }

        ಆದರೆ (seat->ಸೂಚಕ_2.focus == ಕಿಟಕಿ) {
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = seat->ಸೂಚಕ_2.focus->surface;
            ಸೂಚಕ_dispatch_leave(seat, true);
            seat->ಸೂಚಕ_2.pending_ಚೌಕಟ್ಟು.leave_surface = ಖಾಲಿ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_ಬಿಂದು *tp, *ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ (tp, ತಾತ್ಕಾಲಿಕ, &seat->touch.points, link) {
            ಆದರೆ (tp->surface == ಕಿಟಕಿ->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಆದರೆ (tool->focus == ಕಿಟಕಿ) {
                tool->focus = ಖಾಲಿ;
                Wayland_TabletToolUpdateCursor(tool);
                ಆದರೆ (tool->instance_id) {
                    SDL_RemovePenDevice(0, ಕಿಟಕಿ->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_ದತ್ತಾಂಶ *drop, *drop_ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ (drop, drop_ತಾತ್ಕಾಲಿಕ, &seat->ದತ್ತಾಂಶ_device->pending_drops, link) {
            ಆದರೆ (drop->dnd_ಕಿಟಕಿ == ಕಿಟಕಿ->sdlwindow) {
                Wayland_ಕೆಲಸ_Thread_Cancel_ಕೆಲಸ(display->ಕೆಲಸ_thread_context, drop->id);

                ಆದರೆ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_ದತ್ತಾಂಶ_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

ಶೂನ್ಯ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ಕೆಳಕ್ಕೆ)
{
    ಆದರೆ (!seat) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_free(seat->name);

    ಆದರೆ (seat->ದತ್ತಾಂಶ_device) {
        ಆದರೆ (seat->ದತ್ತಾಂಶ_device->selection_offer) {
            Wayland_ದತ್ತಾಂಶ_Offer_Destroy(seat->ದತ್ತಾಂಶ_device->selection_offer);
        }
        ಆದರೆ (seat->ದತ್ತಾಂಶ_device->selection_ಮೂಲ) {
            Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(seat->ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
        }
        ಆದರೆ (seat->ದತ್ತಾಂಶ_device->drag_offer) {
            Wayland_ದತ್ತಾಂಶ_Offer_Destroy(seat->ದತ್ತಾಂಶ_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_ದತ್ತಾಂಶ *drop, *drop_ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ (drop, drop_ತಾತ್ಕಾಲಿಕ, &seat->ದತ್ತಾಂಶ_device->pending_drops, link) {
            Wayland_ಕೆಲಸ_Thread_Cancel_ಕೆಲಸ(seat->display->ಕೆಲಸ_thread_context, drop->id);

            ಆದರೆ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_ದತ್ತಾಂಶ_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ಆದರೆ (seat->ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device) {
            ಆದರೆ (wl_ದತ್ತಾಂಶ_device_get_ಆವೃತ್ತಿ(seat->ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device) >= WL_ದತ್ತಾಂಶ_DEVICE_RELEASE_SINCE_ಆವೃತ್ತಿ) {
                wl_ದತ್ತಾಂಶ_device_release(seat->ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device);
            } ಇಲ್ಲದಿದ್ದರೆ {
                wl_ದತ್ತಾಂಶ_device_destroy(seat->ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device);
            }
        }
        SDL_free(seat->ದತ್ತಾಂಶ_device->id_str);
        SDL_free(seat->ದತ್ತಾಂಶ_device);
    }

    ಆದರೆ (seat->primary_selection_device) {
        ಆದರೆ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ಆದರೆ (seat->primary_selection_device->selection_ಮೂಲ) {
            Wayland_Primary_Selection_ಮೂಲ_Destroy(seat->primary_selection_device->selection_ಮೂಲ);
        }
        ಆದರೆ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ಆದರೆ (seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು) {
        zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3_destroy(seat->ಪಠ್ಯ_ಒಳಹರಿವು.zwp_ಪಠ್ಯ_ಒಳಹರಿವು);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_ಸೂಚಕ(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_ಕೆಳಕ್ಕೆ);

    ಆದರೆ (wl_seat_get_ಆವೃತ್ತಿ(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_ಆವೃತ್ತಿ) {
        wl_seat_release(seat->wl_seat);
    } ಇಲ್ಲದಿದ್ದರೆ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Update_Relative_ಸೂಚಕ(SDL_WaylandSeat *seat)
{
    ಆದರೆ (seat->display->relative_ಸೂಚಕ_manager) {
        bool relative_focus = false;

        ಆದರೆ (seat->ಸೂಚಕ_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ಆದರೆ (seat->ಸೂಚಕ_2.focus->sdlwindow->flags & SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ) {
                ಆದರೆ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->ಸೂಚಕ_2.focus;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    relative_focus = seat->ಸೂಚಕ_2.focus->keyboard_focus_ಎಣಿಕೆ != 0;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                relative_focus = SDL_GetMouse()->warp_emulation_ಸಕ್ರಿಯ;
            }
        }

        ಆದರೆ (relative_focus) {
            ಆದರೆ (!seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
                seat->ಸೂಚಕ_2.relative_ಸೂಚಕ = zwp_relative_ಸೂಚಕ_manager_v1_get_relative_ಸೂಚಕ(seat->display->relative_ಸೂಚಕ_manager, seat->ಸೂಚಕ_2.wl_ಸೂಚಕ);
                zwp_relative_ಸೂಚಕ_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.relative_ಸೂಚಕ, &relative_ಸೂಚಕ_listener, seat);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
            zwp_relative_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.relative_ಸೂಚಕ);
            seat->ಸೂಚಕ_2.relative_ಸೂಚಕ = ಖಾಲಿ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_ದತ್ತಾಂಶ *display = seat->display;

    ಆದರೆ (display->ಕೀಲಿ_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ಆದರೆ (seat->keyboard.ಕೀಲಿ_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ಕೀಲಿ_inhibitor);
            seat->keyboard.ಕೀಲಿ_inhibitor = ಖಾಲಿ;
        }

        ಆದರೆ (seat->keyboard.wl_keyboard) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *w = seat->keyboard.focus;
            ಆದರೆ (w) {
                SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED) {
                    seat->keyboard.ಕೀಲಿ_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ಕೀಲಿ_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

ಶೂನ್ಯ Wayland_Seat_Update_ಸೂಚಕ_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_ದತ್ತಾಂಶ *display = seat->display;
    Wayland_Seat_Update_Relative_ಸೂಚಕ(seat);

    ಆದರೆ (display->ಸೂಚಕ_constraints) {
        ಆದರೆ (seat->ಸೂಚಕ_2.locked_ಸೂಚಕ && !seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
            zwp_locked_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.locked_ಸೂಚಕ);
            seat->ಸೂಚಕ_2.locked_ಸೂಚಕ = ಖಾಲಿ;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
        }

        ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ಆದರೆ (seat->ಸೂಚಕ_2.relative_ಸೂಚಕ) {
                ಆದರೆ (!seat->ಸೂಚಕ_2.locked_ಸೂಚಕ) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ಆದರೆ (seat->ಸೂಚಕ_2.confined_ಸೂಚಕ) {
                        zwp_confined_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.confined_ಸೂಚಕ);
                        seat->ಸೂಚಕ_2.confined_ಸೂಚಕ = ಖಾಲಿ;
                    }

                    seat->ಸೂಚಕ_2.locked_ಸೂಚಕ = zwp_ಸೂಚಕ_constraints_v1_ಬೀಗ_ಸೂಚಕ(display->ಸೂಚಕ_constraints,
                                                                                           seat->ಸೂಚಕ_2.focus->surface,
                                                                                           seat->ಸೂಚಕ_2.wl_ಸೂಚಕ, ಖಾಲಿ,
                                                                                           ZWP_ಸೂಚಕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_ಸೂಚಕ_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.locked_ಸೂಚಕ, &locked_ಸೂಚಕ_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ಹಿಂತಿರುಗಿ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ಆದರೆ (seat->ಸೂಚಕ_2.confined_ಸೂಚಕ) {
                zwp_confined_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.confined_ಸೂಚಕ);
                seat->ಸೂಚಕ_2.confined_ಸೂಚಕ = ಖಾಲಿ;
            }

            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *w = seat->ಸೂಚಕ_2.focus;
            ಆದರೆ (!w) {
                ಹಿಂತಿರುಗಿ;
            }

            SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) ||
                (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED) && SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->mouse_rect))) {
                ಹಿಂತಿರುಗಿ;
            }

            ರಚನೆ wl_region *confine_rect = ಖಾಲಿ;
            ಆದರೆ (!SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(ಕಿಟಕಿ, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_ಕೂಡಿಸು(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                ಆದರೆ (!SDL_ಬಿಂದು_ಒಳ_Rect(&seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    ಪೂರ್ಣಾಂಕ closest_x = seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion.x;
                    ಪೂರ್ಣಾಂಕ closest_y = seat->ಸೂಚಕ_2.ಕೊನೆಯ_motion.y;

                    ಆದರೆ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ಆದರೆ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ಆದರೆ (confine_rect || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED)) {
                ಆದರೆ (ಕಿಟಕಿ->mouse_rect.w != 1 && ಕಿಟಕಿ->mouse_rect.h != 1) {
                    seat->ಸೂಚಕ_2.confined_ಸೂಚಕ =
                        zwp_ಸೂಚಕ_constraints_v1_confine_ಸೂಚಕ(display->ಸೂಚಕ_constraints,
                                                                   w->surface,
                                                                   seat->ಸೂಚಕ_2.wl_ಸೂಚಕ,
                                                                   confine_rect,
                                                                   ZWP_ಸೂಚಕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_ಸೂಚಕ_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.confined_ಸೂಚಕ,
                                                         &confined_ಸೂಚಕ_listener,
                                                         seat);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->ಸೂಚಕ_2.locked_ಸೂಚಕ =
                        zwp_ಸೂಚಕ_constraints_v1_ಬೀಗ_ಸೂಚಕ(display->ಸೂಚಕ_constraints,
                                                                w->surface,
                                                                seat->ಸೂಚಕ_2.wl_ಸೂಚಕ,
                                                                ಖಾಲಿ,
                                                                ZWP_ಸೂಚಕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_ಸೂಚಕ_v1_ಕೂಡಿಸು_listener(seat->ಸೂಚಕ_2.locked_ಸೂಚಕ,
                                                       &locked_ಸೂಚಕ_listener,
                                                       seat);
                }
                ಆದರೆ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Update_ಸೂಚಕ_Grabs(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ಆದರೆ (!ಕಿಟಕಿ || seat->ಸೂಚಕ_2.focus == ಕಿಟಕಿ) {
            Wayland_Seat_Update_ಸೂಚಕ_Grab(seat);
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ಆದರೆ (!ಕಿಟಕಿ || seat->keyboard.focus == ಕಿಟಕಿ) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

ಶೂನ್ಯ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ಆದರೆ (serial > seat->ಕೊನೆಯ_implicit_grab_serial) {
        seat->ಕೊನೆಯ_implicit_grab_serial = serial;
        seat->display->ಕೊನೆಯ_implicit_grab_seat = seat;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
