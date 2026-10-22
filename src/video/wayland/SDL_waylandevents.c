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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_scancode_tables_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keysym_to_keycode_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_system_theme.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandkeyboard.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-constraints-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "relative-pointer-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-shell-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "text-input-unstable-v3-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tablet-v2-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "primary-selection-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "input-timestamps-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-gestures-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cursor-shape-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "viewporter-client-protocol.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
#ਅਨ੍ਤਰ੍ਭਾਵ <libdecor.h>
#ਜੇ_ਅੰਤ

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
#ਅਨ੍ਤਰ੍ਭਾਵ <linux/input.h>
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_ਖੱਬਾ    (0x110)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_ਸੱਜਾ   (0x111)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_ਵਿਚਕਾਰ  (0x112)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_SIDE    (0x113)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_EXTRA   (0x114)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_STYLUS  (0x14b)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_STYLUS2 (0x14c)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BTN_STYLUS3 (0x149)
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keysym_to_scancode_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/imKStoUCS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xkbcommon/xkbcommon-compose.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_WHEEL_AXIS_UNIT 10

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XKB_MOD_NAME_MOD3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XKB_MOD_NAME_MOD3 "Mod3"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XKB_MOD_NAME_MOD5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XKB_MOD_NAME_MOD5 "Mod5"
#ਜੇ_ਅੰਤ

// Keyboard and mouse names to match XWayland
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_DEFAULT_ਸੂਚਕ_NAME "Virtual core pointer"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_ਮੰਜ਼ਿਲ_NS(10)

// Timer rollover detection thresholds
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_TIMER_ROLLOVER_INTERVAL_ਨੀਵਾਂ  (SDL_MAX_UINT32 / 16U)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLAND_TIMER_ROLLOVER_INTERVAL_ਉੱਚਾ (WAYLAND_TIMER_ROLLOVER_INTERVAL_ਨੀਵਾਂ * 15U)

// Scoped function declarations
ਸਥਿਰ ਖਾਲੀ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    Uint32 ਕੁੰਜੀ;
    SDL_Scancode scancode;
} Wayland_Reserved_ਕੁੰਜੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ਬਣਤਰ wl_surface *surface;

    ਬਣਤਰ wl_list link;
} SDL_Wayland_Touch_ਬਿੰਦੂ;

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_ਜੋੜੋ_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ਬਣਤਰ wl_surface *surface)
{
    SDL_Wayland_Touch_ਬਿੰਦੂ *tp = SDL_malloc(ਆਕਾਰ(SDL_Wayland_Touch_ਬਿੰਦੂ));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ਪਾਓ(&seat->touch.points, &tp->link);
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_ਬਿੰਦੂ *tp)
{
    ਜੇ (tp->surface) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(tp->surface);

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2) {
            ਅਚਲ ਦਸ਼ਮਲਵ x = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(tp->fx) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਚੌੜਾਈ);
            ਅਚਲ ਦਸ਼ਮਲਵ y = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(tp->fy) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਉਚਾਈ);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸਰਗਰਮ_touch_ਗਿਣਤੀ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ਜੇ (SDL_GetMouseFocus() == ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow && !ਖਿੜਕੀ_ਅੰਕੜੇ_2->keyboard_focus_ਗਿਣਤੀ &&
                !ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_focus_ਗਿਣਤੀ && !ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸਰਗਰਮ_touch_ਗਿਣਤੀ) {
                SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ਬਣਤਰ wl_surface **surface)
{
    SDL_Wayland_Touch_ਬਿੰਦੂ *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ਜੇ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ਜੇ (surface) {
                *surface = tp->surface;
            }
            ਰੋਕੋ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ਬਣਤਰ wl_surface **surface)
{
    SDL_Wayland_Touch_ਬਿੰਦੂ *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ਜੇ (tp->id == id) {
            ਜੇ (fx) {
                *fx = tp->fx;
            }
            ਜੇ (fy) {
                *fy = tp->fy;
            }
            ਜੇ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ਰੋਕੋ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_GetScaledMouseRect(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Rect *scaled_rect)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    scaled_rect->x = (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->mouse_rect.x / ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.x);
    scaled_rect->y = (ਪੂਰਨ)SDL_floor(ਖਿੜਕੀ->mouse_rect.y / ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.y);
    scaled_rect->w = (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->mouse_rect.w / ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.x);
    scaled_rect->h = (ਪੂਰਨ)SDL_ceil(ਖਿੜਕੀ->mouse_rect.h / ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.y);
}

ਸਥਿਰ Uint64 Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(Uint64 nsTimestamp)
{
    ਸਥਿਰ Uint64 timestamp_ਵਿੱਥ = 0;
    ਅਚਲ Uint64 now = SDL_GetTicksNS();

    ਜੇ (!timestamp_ਵਿੱਥ) {
        timestamp_ਵਿੱਥ = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_ਵਿੱਥ;

    ਜੇ (nsTimestamp > now) {
        timestamp_ਵਿੱਥ -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ਵਾਪਸ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ਸਥਿਰ Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ਸਥਿਰ Uint64 timestamp_ਵਿੱਥ = 0;
    ਸਥਿਰ Uint32 ਆਖਰੀ = 0;
    Uint64 timestamp = SDL_MS_ਮੰਜ਼ਿਲ_NS(wl_timestamp_ms) + timestamp_ਵਿੱਥ;

    ਜੇ (wl_timestamp_ms >= ਆਖਰੀ) {
        ਜੇ (timestamp_ਵਿੱਥ && ਆਖਰੀ < WAYLAND_TIMER_ROLLOVER_INTERVAL_ਨੀਵਾਂ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ਉੱਚਾ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_ਮੰਜ਼ਿਲ_NS(SDL_UINT64_C(0x100000000));
        } ਨਹੀਂਤਾਂ {
            ਆਖਰੀ = wl_timestamp_ms;
        }
    } ਨਹੀਂਤਾਂ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ਜੇ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_ਨੀਵਾਂ && ਆਖਰੀ > WAYLAND_TIMER_ROLLOVER_INTERVAL_ਉੱਚਾ) {
            timestamp_ਵਿੱਥ += SDL_MS_ਮੰਜ਼ਿਲ_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_ਮੰਜ਼ਿਲ_NS(SDL_UINT64_C(0x100000000));
            ਆਖਰੀ = wl_timestamp_ms;
        }
    }

    ਵਾਪਸ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ਸਥਿਰ Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ਅਚਲ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ਵਾਪਸ Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ਸਥਿਰ Uint64 Wayland_Get_ਸੂਚਕ_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ਅਚਲ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ਵਾਪਸ Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(seat->ਸੂਚਕ_2.timestamps ? seat->ਸੂਚਕ_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ਅਚਲ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ਵਾਪਸ Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ਸਥਿਰ ਖਾਲੀ ਨਿਵੇਸ਼_timestamp_listener(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_v1 *zwp_ਨਿਵੇਸ਼_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)ਅੰਕੜੇ) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_ਪ੍ਰਤੀ_ਦੂਜਾ) + tv_nsec;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_v1_listener timestamp_listener = {
    ਨਿਵੇਸ਼_timestamp_listener
};

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_ਰਜਿਸਟਰ_ਨਿਵੇਸ਼_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->display->ਨਿਵੇਸ਼_timestamps_manager) {
        ਜੇ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ਨਿਵੇਸ਼_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ਨਿਵੇਸ਼_timestamps_v1_ਜੋੜੋ_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ && !seat->ਸੂਚਕ_2.timestamps) {
            seat->ਸੂਚਕ_2.timestamps = zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_get_ਸੂਚਕ_timestamps(seat->display->ਨਿਵੇਸ਼_timestamps_manager, seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
            zwp_ਨਿਵੇਸ਼_timestamps_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.timestamps, &timestamp_listener, &seat->ਸੂਚਕ_2.highres_timestamp_ns);
        }

        ਜੇ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_get_touch_timestamps(seat->display->ਨਿਵੇਸ਼_timestamps_manager, seat->touch.wl_touch);
            zwp_ਨਿਵੇਸ਼_timestamps_v1_ਜੋੜੋ_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

ਖਾਲੀ Wayland_Display_Init_ਨਿਵੇਸ਼_Timestamp_Manager(SDL_Video_ਅੰਕੜੇ *display)
{
    ਜੇ (display->ਨਿਵੇਸ਼_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_ਰਜਿਸਟਰ_ਨਿਵੇਸ਼_Timestamp_Listeners(seat);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ handle_pinch_begin(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_ਸੂਚਕ_gesture_pinch_v1 *zwp_ਸੂਚਕ_gesture_pinch_v1, uint32_t serial, uint32_t ਸਮਾਂ, ਬਣਤਰ wl_surface *surface, uint32_t fingers)
{
    ਜੇ (!surface) {
        ਵਾਪਸ;
    }

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);
    ਜੇ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
        seat->ਸੂਚਕ_2.gesture_focus = wind;

        ਅਚਲ Uint64 timestamp = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_pinch_update(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_ਸੂਚਕ_gesture_pinch_v1 *zwp_ਸੂਚਕ_gesture_pinch_v1, uint32_t ਸਮਾਂ,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;

    ਜੇ (seat->ਸੂਚਕ_2.gesture_focus) {
        ਅਚਲ Uint64 timestamp = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);
        ਅਚਲ ਦਸ਼ਮਲਵ s = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->ਸੂਚਕ_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_pinch_ਸਿਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_ਸੂਚਕ_gesture_pinch_v1 *zwp_ਸੂਚਕ_gesture_pinch_v1, uint32_t serial, uint32_t ਸਮਾਂ, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;

    ਜੇ (seat->ਸੂਚਕ_2.gesture_focus) {
        ਅਚਲ Uint64 timestamp = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);
        SDL_SendPinch(SDL_EVENT_PINCH_ਸਿਰਾ, timestamp, seat->ਸੂਚਕ_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->ਸੂਚਕ_2.gesture_focus = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_ਸੂਚਕ_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_ਸਿਰਾ
};

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_Create_ਸੂਚਕ_Gestures(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->display->zwp_ਸੂਚਕ_gestures) {
        ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ && !seat->ਸੂਚਕ_2.gesture_pinch) {
            seat->ਸੂਚਕ_2.gesture_pinch = zwp_ਸੂਚਕ_gestures_v1_get_pinch_gesture(seat->display->zwp_ਸੂਚਕ_gestures, seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
            zwp_ਸੂਚਕ_gesture_pinch_v1_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->ਸੂਚਕ_2.gesture_pinch, seat);
            zwp_ਸੂਚਕ_gesture_pinch_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

ਖਾਲੀ Wayland_Display_Init_ਸੂਚਕ_Gesture_Manager(SDL_Video_ਅੰਕੜੇ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_ਸੂਚਕ_Gestures(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->display->cursor_shape_manager) {
        ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ && !seat->ਸੂਚਕ_2.cursor_state.cursor_shape) {
            seat->ਸੂਚਕ_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_ਸੂਚਕ(seat->display->cursor_shape_manager, seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ਜੇ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

ਖਾਲੀ Wayland_DisplayInitCursorShapeManager(SDL_Video_ਅੰਕੜੇ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_ਸੈੱਟ_Keymap(SDL_WaylandSeat *seat)
{
    ਅਚਲ bool send_event = !seat->display->initializing;

    ਜੇ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ਅੰਕ_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_ਸੈੱਟ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_ਸੈੱਟ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ਸਥਿਰ ਖਾਲੀ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ਜਦੋਂ (elapsed >= repeat_info->ਅਗਲਾ_repeat_ns) {
        ਜੇ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ਅਚਲ Uint64 timestamp = repeat_info->ਅਧਾਰ_ਸਮਾਂ_ns + repeat_info->ਅਗਲਾ_repeat_ns;
            SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(timestamp), repeat_info->keyboard_id, repeat_info->ਕੁੰਜੀ, repeat_info->scancode, true);
        }
        ਜੇ (repeat_info->ਪਾਠ[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_ਪਾਠ(repeat_info->ਪਾਠ);
        }
        repeat_info->ਅਗਲਾ_repeat_ns += SDL_NS_ਪ੍ਰਤੀ_ਦੂਜਾ / (Uint64)repeat_info->repeat_ਦਰ;
    }
}

ਸਥਿਰ ਖਾਲੀ keyboard_repeat_ਸੈੱਟ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ਕੁੰਜੀ, Uint32 wl_press_ਸਮਾਂ_ms,
                                Uint64 ਅਧਾਰ_ਸਮਾਂ_ns, uint32_t scancode, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    ਜੇ (!repeat_info->repeat_ਦਰ) {
        ਵਾਪਸ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ਕੁੰਜੀ = ਕੁੰਜੀ;
    repeat_info->wl_press_ਸਮਾਂ_ms = wl_press_ਸਮਾਂ_ms;
    repeat_info->ਅਧਾਰ_ਸਮਾਂ_ns = ਅਧਾਰ_ਸਮਾਂ_ns;
    repeat_info->sdl_press_ਸਮਾਂ_ns = SDL_GetTicksNS();
    repeat_info->ਅਗਲਾ_repeat_ns = SDL_MS_ਮੰਜ਼ਿਲ_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ਜੇ (ਪਾਠ) {
        SDL_strlcpy(repeat_info->ਪਾਠ, ਪਾਠ, SDL_arraysize(repeat_info->ਪਾਠ));
    } ਨਹੀਂਤਾਂ {
        repeat_info->ਪਾਠ[0] = '\0';
    }
}

ਸਥਿਰ ਖਾਲੀ sync_ਪੂਰਾ_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *callback, uint32_t callback_ਅੰਕੜੇ)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ਸਥਿਰ ਬਣਤਰ wl_callback_listener sync_listener = {
    sync_ਪੂਰਾ_handler
};

ਖਾਲੀ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *d = _this->ਅੰਦਰੂਨੀ;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ਬਣਤਰ wl_callback *cb = wl_display_sync(d->display);
    wl_callback_ਜੋੜੋ_listener(cb, &sync_listener, ਨਿਰਾ);
    WAYLAND_wl_display_flush(d->display);
}

ਪੂਰਨ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ਅੰਕੜੇ *d = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;
    Uint64 ਸ਼ੁਰੂ = SDL_GetTicksNS();
    ਅਚਲ ਪੂਰਨ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ਪੂਰਨ ret;
    bool poll_alarm_ਸੈੱਟ = false;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    SDL_ਖਿੜਕੀ *keyboard_focus = SDL_GetKeyboardFocus();
    ਜੇ (!d->ਪਾਠ_ਨਿਵੇਸ਼_manager && keyboard_focus && SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ਜੇ (timeoutNS < 0 || SDL_MS_ਮੰਜ਼ਿਲ_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_ਮੰਜ਼ਿਲ_NS(200);
            poll_alarm_ਸੈੱਟ = true;
        }
    }
#ਜੇ_ਅੰਤ

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ਜੇ (seat->keyboard.repeat.ਕੁੰਜੀ) {
            ਅਚਲ Uint64 elapsed = ਸ਼ੁਰੂ - seat->keyboard.repeat.sdl_press_ਸਮਾਂ_ns;
            ਅਚਲ Uint64 ਅਗਲਾ_repeat_wait_ਸਮਾਂ = (seat->keyboard.repeat.ਅਗਲਾ_repeat_ns - elapsed) + 1;
            ਜੇ (timeoutNS < 0 || ਅਗਲਾ_repeat_wait_ਸਮਾਂ <= timeoutNS) {
                timeoutNS = ਅਗਲਾ_repeat_wait_ਸਮਾਂ;
                poll_alarm_ਸੈੱਟ = true;
            }
        }
    }

    ਜੇ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ਜੇ (timeoutNS > 0) {
            ਅਚਲ Uint64 now = SDL_GetTicksNS();
            ਅਚਲ Uint64 elapsed = now - ਸ਼ੁਰੂ;
            ਸ਼ੁਰੂ = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ਜੇ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ਜੇ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ਜੇ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ਵਾਪਸ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ਜੇ (timeoutNS > 0) {
            ਅਚਲ Uint64 now = SDL_GetTicksNS();
            ਅਚਲ Uint64 elapsed = now - ਸ਼ੁਰੂ;
            ਸ਼ੁਰੂ = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ਜੇ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ਜੇ (ret == 0) {
                ਵਾਪਸ poll_alarm_ਸੈੱਟ ? 1 : 0;
            } ਨਹੀਂਤਾਂ {
                // Pump events on an interrupt or broken pipe to handle the error.
                ਵਾਪਸ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ਜੇ (ret == -1) {
            ਵਾਪਸ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ਵਾਪਸ 1;
}

ਖਾਲੀ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *d = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;
    ਅਚਲ ਪੂਰਨ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ਪੂਰਨ ret = 0;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    SDL_ਖਿੜਕੀ *keyboard_focus = SDL_GetKeyboardFocus();
    ਜੇ (!d->ਪਾਠ_ਨਿਵੇਸ਼_manager && keyboard_focus && SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#ਜੇ_ਅੰਤ

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ਜੇ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ਜੇ (ret < 0) {
            ਜਾਓ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ਜੇ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ਜੇ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_ਮੰਜ਼ਿਲ_NS(4));
            ਜੇ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ਜੇ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            ਜਾਓ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ਜੇ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ਜੇ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ਨਹੀਂਤਾਂ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ਨਹੀਂਤਾਂ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ਜੇ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ਜੇ (seat->keyboard.repeat.ਕੁੰਜੀ) {
                Wayland_Seat_ਸੈੱਟ_Keymap(seat);

                ਅਚਲ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_ਸਮਾਂ_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ਜੇ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = seat->ਸੂਚਕ_2.focus;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਖਿੜਕੀ_ਅੰਕੜੇ_2 ? ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow : ਨਿਰਾ;

    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2) {
        ਦੁੱਗਣਾ sx = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sx);
        ਦੁੱਗਣਾ sy = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sy);

        ਜੇ (seat->ਸੂਚਕ_2.focus_surface == ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.surface) {
            sx += (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.ਵਿੱਥ_x;
            sy += (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.ਵਿੱਥ_y;
        }

        sx *= ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.x;
        sy *= ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.y;
        ਜੇ (!warp) {
            SDL_SendMouseMotion(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns, ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, false, (ਦਸ਼ਮਲਵ)sx, (ਦਸ਼ਮਲਵ)sy);
        } ਨਹੀਂਤਾਂ {
            SDL_SendMouseWarp(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns, ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, (ਦਸ਼ਮਲਵ)sx, (ਦਸ਼ਮਲਵ)sy);
        }

        seat->ਸੂਚਕ_2.ਆਖਰੀ_motion.x = (ਪੂਰਨ)SDL_floor(sx);
        seat->ਸੂਚਕ_2.ਆਖਰੀ_motion.y = (ਪੂਰਨ)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ਜੇ (!SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->mouse_rect) && !seat->ਸੂਚਕ_2.is_confined) {
            Wayland_Seat_Update_ਸੂਚਕ_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE) && ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) {
            SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ rc = ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test(ਖਿੜਕੀ, &seat->ਸੂਚਕ_2.ਆਖਰੀ_motion, ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test_ਅੰਕੜੇ);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ਚੋਣ (rc) {
            ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT:
                ਜੇ ((ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ) &&
                    (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ)) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ) {
                    rc = SDL_HITTEST_RESIZE_ਖੱਬਾ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ) {
                    rc = SDL_HITTEST_RESIZE_ਸਿਖਰ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ:
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT:
                ਜੇ ((ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ) &&
                    (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ)) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ) {
                    rc = SDL_HITTEST_RESIZE_ਸੱਜਾ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ) {
                    rc = SDL_HITTEST_RESIZE_ਸਿਖਰ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ:
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ਜੇ ((ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ)) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ਸੱਜਾ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM:
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ਜੇ ((ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ)) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ਖੱਬਾ;
                } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ:
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ) {
                    rc = SDL_HITTEST_ਸਾਧਾਰਨ;
                }
                ਰੋਕੋ;
            ਮੂਲ:
                ਰੋਕੋ;
            }

            ਜੇ (rc != ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ) {
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ = rc;
                Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_motion(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                  uint32_t ਸਮਾਂ, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    ਅਚਲ Uint64 timestamp = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);

    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sx = sx;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sy = sy;

    ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) >= WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ਜੇ (!seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_relative || seat->ਸੂਚਕ_2.timestamps) {
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = timestamp;
        }
    } ਨਹੀਂਤਾਂ {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = timestamp;
        ਸੂਚਕ_dispatch_absolute_motion(seat, false);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface);
    ਜੇ (!ਖਿੜਕੀ) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ਵਾਪਸ;
    }

    ਜੇ (ਖਿੜਕੀ->surface != seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_ਸੈੱਟ_Default_Cursor(seat);
        ਵਾਪਸ;
    }

    seat->ਸੂਚਕ_2.focus = ਖਿੜਕੀ;
    seat->ਸੂਚਕ_2.focus_surface = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface;
    ++ਖਿੜਕੀ->ਸੂਚਕ_focus_ਗਿਣਤੀ;
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ->sdlwindow);

    // Send the initial position.
    ਸੂਚਕ_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_ਸੂਚਕ_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_enter(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                 uint32_t serial, ਬਣਤਰ wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ਜੇ (!surface) {
        // Enter event for a destroyed surface.
        ਵਾਪਸ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface = surface;
    seat->ਸੂਚਕ_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sx = sx_w;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sy = sy_w;

    ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) < WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = 0;
        ਸੂਚਕ_dispatch_enter(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_leave(SDL_WaylandSeat *seat, bool update_ਸੂਚਕ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface);

    ਜੇ (ਖਿੜਕੀ) {
        ਜੇ (seat->ਸੂਚਕ_2.focus) {
            ਜੇ (seat->ਸੂਚਕ_2.focus->surface == seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface) {
                // Clear the capture flag and raise all buttons
                ਖਿੜਕੀ->sdlwindow->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_CAPTURE;

                seat->ਸੂਚਕ_2.focus = ਨਿਰਾ;
                seat->ਸੂਚਕ_2.focus_surface = ਨਿਰਾ;
                ਲਈ (Uint8 i = 1; seat->ਸੂਚਕ_2.buttons_pressed; ++i) {
                    ਜੇ (seat->ਸੂਚਕ_2.buttons_pressed & SDL_BUTTON_ਨਕਾਬ(i)) {
                        SDL_SendMouseButton(0, ਖਿੜਕੀ->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, i, false);
                        seat->ਸੂਚਕ_2.buttons_pressed &= ~SDL_BUTTON_ਨਕਾਬ(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_ਖਿੜਕੀ *mouse_focus = SDL_GetMouseFocus();
                ਅਚਲ bool had_focus = mouse_focus && ਖਿੜਕੀ->sdlwindow == mouse_focus;
                ਜੇ (!--ਖਿੜਕੀ->ਸੂਚਕ_focus_ਗਿਣਤੀ && had_focus && !ਖਿੜਕੀ->ਸਰਗਰਮ_touch_ਗਿਣਤੀ) {
                    SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
                }

                ਜੇ (update_ਸੂਚਕ) {
                    Wayland_Seat_Update_ਸੂਚਕ_Grab(seat);
                    Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
                }
            }
        } ਨਹੀਂਤਾਂ ਜੇ (update_ਸੂਚਕ) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_leave(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                 uint32_t serial, ਬਣਤਰ wl_surface *surface)
{
    ਜੇ (!surface) {
        // Leave event for a destroyed surface.
        ਵਾਪਸ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = surface;
    ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) < WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        ਸੂਚਕ_dispatch_leave(seat, true);
    }
}

ਸਥਿਰ bool Wayland_Process_ਪ੍ਰਾਪਤੀ_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ਜੇ (seat->ਸੂਚਕ_2.locked_ਸੂਚਕ) {
        ਵਾਪਸ false;
    }

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = seat->ਸੂਚਕ_2.focus;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow;

    ਜੇ (ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) {
        ਸਥਿਰ ਅਚਲ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ_ਖੱਬਾ, XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ,
            XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ_ਸੱਜਾ, XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_ਸੱਜਾ,
            XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_BOTTOM_ਸੱਜਾ, XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_BOTTOM,
            XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_BOTTOM_ਖੱਬਾ, XDG_TOPLEVEL_RESIZE_ਕਿਨਾਰਾ_ਖੱਬਾ
        };

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
        ਸਥਿਰ ਅਚਲ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ_ਖੱਬਾ, LIBDECOR_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ,
            LIBDECOR_RESIZE_ਕਿਨਾਰਾ_ਸਿਖਰ_ਸੱਜਾ, LIBDECOR_RESIZE_ਕਿਨਾਰਾ_ਸੱਜਾ,
            LIBDECOR_RESIZE_ਕਿਨਾਰਾ_BOTTOM_ਸੱਜਾ, LIBDECOR_RESIZE_ਕਿਨਾਰਾ_BOTTOM,
            LIBDECOR_RESIZE_ਕਿਨਾਰਾ_BOTTOM_ਖੱਬਾ, LIBDECOR_RESIZE_ਕਿਨਾਰਾ_ਖੱਬਾ
        };
#ਜੇ_ਅੰਤ

        ਚੋਣ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ) {
        ਹਾਲਤ SDL_HITTEST_DRAGGABLE:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
            ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.libdecor.ਚੌਖਟਾ) {
                    libdecor_ਚੌਖਟਾ_move(ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.libdecor.ਚੌਖਟਾ,
                                        seat->wl_seat,
                                        serial);
                }
            } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ਵਾਪਸ true;

        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ:
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM:
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
            ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.libdecor.ਚੌਖਟਾ) {
                    libdecor_ਚੌਖਟਾ_resize(ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.libdecor.ਚੌਖਟਾ,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(ਖਿੜਕੀ_ਅੰਕੜੇ_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ਵਾਪਸ true;

        ਮੂਲ:
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool ਥੱਲੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = seat->ਸੂਚਕ_2.focus;

    ਜੇ (ਖਿੜਕੀ) {
        bool ignore_click = false;

        ਜੇ (ਥੱਲੇ) {
            seat->ਸੂਚਕ_2.buttons_pressed |= SDL_BUTTON_ਨਕਾਬ(sdl_button);

            ਜੇ (sdl_button == SDL_BUTTON_ਖੱਬਾ && Wayland_Process_ਪ੍ਰਾਪਤੀ_Test(seat, seat->ਆਖਰੀ_implicit_grab_serial)) {
                ਵਾਪਸ; // don't pass this event on to app.
            }
        } ਨਹੀਂਤਾਂ {
            seat->ਸੂਚਕ_2.buttons_pressed &= ~SDL_BUTTON_ਨਕਾਬ(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ਜੇ (ਖਿੜਕੀ->ਆਖਰੀ_focus_event_ਸਮਾਂ_ns) {
            ਜੇ (ਥੱਲੇ && (SDL_GetTicksNS() - ਖਿੜਕੀ->ਆਖਰੀ_focus_event_ਸਮਾਂ_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            ਖਿੜਕੀ->ਆਖਰੀ_focus_event_ਸਮਾਂ_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        ਜੇ (!seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
            ਜੇ (seat->ਸੂਚਕ_2.buttons_pressed != 0) {
                ਖਿੜਕੀ->sdlwindow->flags |= SDL_ਖਿੜਕੀ_MOUSE_CAPTURE;
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ->sdlwindow->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ਜੇ (seat->ਸੂਚਕ_2.focus_surface != ਖਿੜਕੀ->surface) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = ਖਿੜਕੀ->surface;
                }
            }
        }

        ਜੇ (!ignore_click) {
            SDL_SendMouseButton(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns, ਖਿੜਕੀ->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, sdl_button, ਥੱਲੇ);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_button(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2, uint32_t serial,
                                  uint32_t ਸਮਾਂ, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    Uint8 sdl_button;

    ਚੋਣ (button) {
    ਹਾਲਤ BTN_ਖੱਬਾ:
        sdl_button = SDL_BUTTON_ਖੱਬਾ;
        ਰੋਕੋ;
    ਹਾਲਤ BTN_ਵਿਚਕਾਰ:
        sdl_button = SDL_BUTTON_ਵਿਚਕਾਰ;
        ਰੋਕੋ;
    ਹਾਲਤ BTN_ਸੱਜਾ:
        sdl_button = SDL_BUTTON_ਸੱਜਾ;
        ਰੋਕੋ;
    ਮੂਲ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ਰੋਕੋ;
    }

    ਜੇ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);

    ਜੇ (wl_seat_get_ਸੰਸਕਰਣ(seat->wl_seat) >= WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        ਜੇ (state_w) {
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_pressed |= SDL_BUTTON_ਨਕਾਬ(sdl_button);
        } ਨਹੀਂਤਾਂ {
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_released |= SDL_BUTTON_ਨਕਾਬ(sdl_button);
        }
    } ਨਹੀਂਤਾਂ {
        ਸੂਚਕ_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t ਮੁੱਲ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = seat->ਸੂਚਕ_2.focus;
    ਅਚਲ ਗਿਣਤੀ wl_ਸੂਚਕ_axis a = axis;

    ਜੇ (seat->ਸੂਚਕ_2.focus) {
        ਦਸ਼ਮਲਵ x, y;

        ਚੋਣ (a) {
        ਹਾਲਤ WL_ਸੂਚਕ_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
            ਰੋਕੋ;
        ਹਾਲਤ WL_ਸੂਚਕ_AXIS_HORIZONTAL_SCROLL:
            x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
            y = 0;
            ਰੋਕੋ;
        ਮੂਲ:
            ਵਾਪਸ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, ਖਿੜਕੀ->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, x, y, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_common(SDL_WaylandSeat *seat, ਗਿਣਤੀ SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t ਮੁੱਲ)
{
    ਅਚਲ ਗਿਣਤੀ wl_ਸੂਚਕ_axis a = axis;

    ਜੇ (seat->ਸੂਚਕ_2.focus) {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_axis = true;

        ਚੋਣ (a) {
        ਹਾਲਤ WL_ਸੂਚਕ_AXIS_VERTICAL_SCROLL:
            ਚੋਣ (type) {
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y = 0.0f;
                }
                seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y += 0 - (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                ਰੋਕੋ;
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y = 0 - (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y = 0 - (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                }
                ਰੋਕੋ;
            }
            ਰੋਕੋ;
        ਹਾਲਤ WL_ਸੂਚਕ_AXIS_HORIZONTAL_SCROLL:
            ਚੋਣ (type) {
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x = 0.0f;
                }
                seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x += (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                ਰੋਕੋ;
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(ਮੁੱਲ);
                }
                ਰੋਕੋ;
            }
            ਰੋਕੋ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                uint32_t ਸਮਾਂ, uint32_t axis, wl_fixed_t ਮੁੱਲ)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਅਚਲ Uint64 nsTimestamp = Wayland_Get_ਸੂਚਕ_Timestamp(seat, ਸਮਾਂ);

    ਜੇ (wl_seat_get_ਸੰਸਕਰਣ(seat->wl_seat) >= WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = nsTimestamp;
        ਸੂਚਕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, ਮੁੱਲ);
    } ਨਹੀਂਤਾਂ {
        ਸੂਚਕ_handle_axis_common_v1(seat, nsTimestamp, axis, ਮੁੱਲ);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_relative_direction(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;

    ਚੋਣ (axis_relative_direction) {
    ਹਾਲਤ WL_ਸੂਚਕ_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.direction = SDL_MOUSEWHEEL_ਸਾਧਾਰਨ;
        ਰੋਕੋ;
    ਹਾਲਤ WL_ਸੂਚਕ_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = seat->ਸੂਚਕ_2.focus;

    ਜੇ (ਖਿੜਕੀ) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ਦੁੱਗਣਾ dx;
        ਦੁੱਗਣਾ dy;
        ਜੇ (mouse->ਨਿਵੇਸ਼_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dx_unaccel);
            dy = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dy_unaccel);
        } ਨਹੀਂਤਾਂ {
            dx = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dx) * ਖਿੜਕੀ->ਸੂਚਕ_scale.x;
            dy = wl_fixed_ਮੰਜ਼ਿਲ_double(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dy) * ਖਿੜਕੀ->ਸੂਚਕ_scale.y;
        }

        SDL_SendMouseMotion(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns, ਖਿੜਕੀ->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, true, (ਦਸ਼ਮਲਵ)dx, (ਦਸ਼ਮਲਵ)dy);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_dispatch_axis(SDL_WaylandSeat *seat)
{
    ਦਸ਼ਮਲਵ x, y;
    SDL_MouseWheelDirection direction = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.direction;

    ਚੋਣ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x_axis_type) {
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.x / 120.0f;
        ਰੋਕੋ;
    ਮੂਲ:
        x = 0.0f;
        ਰੋਕੋ;
    }

    ਚੋਣ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y_axis_type) {
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis.y / 120.0f;
        ਰੋਕੋ;
    ਮੂਲ:
        y = 0.0f;
        ਰੋਕੋ;
    }

    SDL_SendMouseWheel(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns,
                       seat->ਸੂਚਕ_2.focus->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, x, y, direction);
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_ਚੌਖਟਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;

    ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface) {
        ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = seat->ਸੂਚਕ_2.focus;
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *new_focus = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface);

            ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2 && (ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE) && ਖਿੜਕੀ_ਅੰਕੜੇ_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->ਸੂਚਕ_2.focus_surface = seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface;
                seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface = ਨਿਰਾ;
                seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = ਨਿਰਾ;
            } ਨਹੀਂਤਾਂ {
                // Leaving the previous surface before entering a new surface.
                ਸੂਚਕ_dispatch_leave(seat, false);
                seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = ਨਿਰਾ;
            }
        }

        ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.enter_surface) {
            ਸੂਚਕ_dispatch_enter(seat);
        }
    }

    ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_absolute) {
        ਸੂਚਕ_dispatch_absolute_motion(seat, seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_warp);
    }

    ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_relative) {
        ਸੂਚਕ_dispatch_relative_motion(seat);
    }

    ਲਈ (Uint8 i = 1; seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_pressed || seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_released; ++i) {
        ਅਚਲ Uint32 ਨਕਾਬ = SDL_BUTTON_ਨਕਾਬ(i);
        ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_pressed & ਨਕਾਬ) {
            ਸੂਚਕ_dispatch_button(seat, i, true);
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_pressed &= ~ਨਕਾਬ;
        }
        ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_released & ਨਕਾਬ) {
            ਸੂਚਕ_dispatch_button(seat, i, false);
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.buttons_released &= ~ਨਕਾਬ;
        }
    }

    ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_axis) {
        ਸੂਚਕ_dispatch_axis(seat);
    }

    ਜੇ (seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface) {
        ਸੂਚਕ_dispatch_leave(seat, true);
    }

    SDL_zero(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ);
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_ਸਰੋਤ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                       uint32_t axis_ਸਰੋਤ)
{
    // unimplemented
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_stop(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                     uint32_t ਸਮਾਂ, uint32_t axis)
{
    // unimplemented
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_discrete(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਸੂਚਕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_axis_value120(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *ਸੂਚਕ_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਸੂਚਕ_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ਸਥਿਰ ਖਾਲੀ ਸੂਚਕ_handle_warp(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਸੂਚਕ *wl_ਸੂਚਕ, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;

    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_absolute = true;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_warp = true;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sx = surface_x;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.absolute.sy = surface_y;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_ਸੂਚਕ_listener ਸੂਚਕ_listener = {
    ਸੂਚਕ_handle_enter,
    ਸੂਚਕ_handle_leave,
    ਸੂਚਕ_handle_motion,
    ਸੂਚਕ_handle_button,
    ਸੂਚਕ_handle_axis,
    ਸੂਚਕ_handle_ਚੌਖਟਾ,                   // Version 5
    ਸੂਚਕ_handle_axis_ਸਰੋਤ,             // Version 5
    ਸੂਚਕ_handle_axis_stop,               // Version 5
    ਸੂਚਕ_handle_axis_discrete,           // Version 5
    ਸੂਚਕ_handle_axis_value120,           // Version 8
    ਸੂਚਕ_handle_axis_relative_direction, // Version 9
    ਸੂਚਕ_handle_warp                     // Version 11
};

ਸਥਿਰ ਖਾਲੀ relative_ਸੂਚਕ_handle_relative_motion(ਖਾਲੀ *ਅੰਕੜੇ,
                                                    ਬਣਤਰ zwp_relative_ਸੂਚਕ_v1 *ਸੂਚਕ_2,
                                                    uint32_t ਸਮਾਂ_hi,
                                                    uint32_t ਸਮਾਂ_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;

    // Relative pointer event times are in microsecond granularity.
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dx = dx;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dy = dy;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dx_unaccel = dx_unaccel;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.relative.dy_unaccel = dy_unaccel;
    seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.timestamp_ns = Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(SDL_US_ਮੰਜ਼ਿਲ_NS(((Uint64)ਸਮਾਂ_hi << 32) | (Uint64)ਸਮਾਂ_lo));

    ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) >= WL_ਸੂਚਕ_ਚੌਖਟਾ_SINCE_ਸੰਸਕਰਣ) {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.have_relative = true;
    } ਨਹੀਂਤਾਂ {
        ਸੂਚਕ_dispatch_relative_motion(seat);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_relative_ਸੂਚਕ_v1_listener relative_ਸੂਚਕ_listener = {
    relative_ਸੂਚਕ_handle_relative_motion,
};

ਸਥਿਰ ਖਾਲੀ locked_ਸੂਚਕ_locked(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_locked_ਸੂਚਕ_v1 *locked_ਸੂਚਕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.is_confined = true;
}

ਸਥਿਰ ਖਾਲੀ locked_ਸੂਚਕ_unlocked(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_locked_ਸੂਚਕ_v1 *locked_ਸੂਚਕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.is_confined = false;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_locked_ਸੂਚਕ_v1_listener locked_ਸੂਚਕ_listener = {
    locked_ਸੂਚਕ_locked,
    locked_ਸੂਚਕ_unlocked,
};

ਸਥਿਰ ਖਾਲੀ confined_ਸੂਚਕ_confined(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_confined_ਸੂਚਕ_v1 *confined_ਸੂਚਕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.is_confined = true;
}

ਸਥਿਰ ਖਾਲੀ confined_ਸੂਚਕ_unconfined(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_confined_ਸੂਚਕ_v1 *confined_ਸੂਚਕ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਸੂਚਕ_2.is_confined = false;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_confined_ਸੂਚਕ_v1_listener confined_ਸੂਚਕ_listener = {
    confined_ਸੂਚਕ_confined,
    confined_ਸੂਚਕ_unconfined,
};

ਸਥਿਰ ਖਾਲੀ touch_handler_ਥੱਲੇ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ਬਣਤਰ wl_surface *surface,
                               ਪੂਰਨ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2;

    // Check that this surface is valid.
    ਜੇ (!surface) {
        ਵਾਪਸ;
    }

    Wayland_Seat_ਜੋੜੋ_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    ਖਿੜਕੀ_ਅੰਕੜੇ_2 = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);

    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2 && ਖਿੜਕੀ_ਅੰਕੜੇ_2->surface == surface) {
        ਦਸ਼ਮਲਵ x, y;

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਚੌੜਾਈ <= 1) {
            x = 0.5f;
        } ਨਹੀਂਤਾਂ {
            x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fx) / (ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਚੌੜਾਈ - 1);
        }
        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਉਚਾਈ <= 1) {
            y = 0.5f;
        } ਨਹੀਂਤਾਂ {
            y = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fy) / (ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਉਚਾਈ - 1);
        }

        ++ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸਰਗਰਮ_touch_ਗਿਣਤੀ;
        SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, 1.0f);
    }
}

ਸਥਿਰ ਖਾਲੀ touch_handler_ਉੱਪਰ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *touch, uint32_t serial, uint32_t timestamp, ਪੂਰਨ id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    wl_fixed_t fx = 0, fy = 0;
    ਬਣਤਰ wl_surface *surface = ਨਿਰਾ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ਜੇ (surface) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2 && ਖਿੜਕੀ_ਅੰਕੜੇ_2->surface == surface) {
            ਅਚਲ ਦਸ਼ਮਲਵ x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fx) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਚੌੜਾਈ;
            ਅਚਲ ਦਸ਼ਮਲਵ y = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fy) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਉਚਾਈ;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, 0.0f);

            --ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸਰਗਰਮ_touch_ਗਿਣਤੀ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ਜੇ (SDL_GetMouseFocus() == ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow && !ਖਿੜਕੀ_ਅੰਕੜੇ_2->keyboard_focus_ਗਿਣਤੀ &&
                !ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_focus_ਗਿਣਤੀ && !ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸਰਗਰਮ_touch_ਗਿਣਤੀ) {
                SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ touch_handler_motion(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *touch, uint32_t timestamp, ਪੂਰਨ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    ਬਣਤਰ wl_surface *surface = ਨਿਰਾ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ਜੇ (surface) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2 && ਖਿੜਕੀ_ਅੰਕੜੇ_2->surface == surface) {
            ਅਚਲ ਦਸ਼ਮਲਵ x = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fx) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਚੌੜਾਈ;
            ਅਚਲ ਦਸ਼ਮਲਵ y = (ਦਸ਼ਮਲਵ)wl_fixed_ਮੰਜ਼ਿਲ_double(fy) / ਖਿੜਕੀ_ਅੰਕੜੇ_2->current.logical_ਉਚਾਈ;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ touch_handler_ਚੌਖਟਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *touch)
{
}

ਸਥਿਰ ਖਾਲੀ touch_handler_cancel(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    SDL_Wayland_Touch_ਬਿੰਦੂ *tp, *ਆਰਜ਼ੀ;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_ਸੁਰੱਖਿਅਤ (tp, ਆਰਜ਼ੀ, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ਸਥਿਰ ਖਾਲੀ touch_handler_shape(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ਸਥਿਰ ਖਾਲੀ touch_handler_orientation(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_touch_listener touch_listener = {
    touch_handler_ਥੱਲੇ,
    touch_handler_ਉੱਪਰ,
    touch_handler_motion,
    touch_handler_ਚੌਖਟਾ,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ਜੇ !SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(1, 0, 0)
ਸਥਿਰ size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ਕੁੰਜੀ, xkb_layout_ਸੂਚਕਾਂਕ_t layout, xkb_level_ਸੂਚਕਾਂਕ_t level, xkb_mod_ਨਕਾਬ_t *masks_ਬਾਹਰਲਾ, size_t masks_ਮਾਪ)
{
    ਜੇ (!masks_ਬਾਹਰਲਾ || !masks_ਮਾਪ) {
        ਵਾਪਸ 0;
    }

    // Level 0 is always unmodified, so early out.
    ਜੇ (level == 0) {
        *masks_ਬਾਹਰਲਾ = 0;
        ਵਾਪਸ 1;
    }

    size_t ਨਕਾਬ_idx = 0;
    ਅਚਲ xkb_mod_ਨਕਾਬ_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ,
        seat->keyboard.xkb.caps_ਨਕਾਬ_2,
        seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ | seat->keyboard.xkb.caps_ਨਕਾਬ_2,
        seat->keyboard.xkb.level3_ਨਕਾਬ,
        seat->keyboard.xkb.level3_ਨਕਾਬ | seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ,
        seat->keyboard.xkb.level3_ਨਕਾਬ | seat->keyboard.xkb.caps_ਨਕਾਬ_2,
        seat->keyboard.xkb.level3_ਨਕਾਬ | seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ | seat->keyboard.xkb.caps_ਨਕਾਬ_2,
        seat->keyboard.xkb.level5_ਨਕਾਬ,
        seat->keyboard.xkb.level5_ਨਕਾਬ | seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ,
        seat->keyboard.xkb.level5_ਨਕਾਬ | seat->keyboard.xkb.caps_ਨਕਾਬ_2,
        seat->keyboard.xkb.level5_ਨਕਾਬ | seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ | seat->keyboard.xkb.caps_ਨਕਾਬ_2
    };
    ਅਚਲ xkb_mod_ਨਕਾਬ_t pressed_mod_ਨਕਾਬ = seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ | seat->keyboard.xkb.level3_ਨਕਾਬ | seat->keyboard.xkb.level5_ਨਕਾਬ;
    ਅਚਲ xkb_mod_ਨਕਾਬ_t locked_mod_ਨਕਾਬ = seat->keyboard.xkb.caps_ਨਕਾਬ_2;

    ਲਈ (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_ਨਕਾਬ(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_ਨਕਾਬ, 0, keymod_masks[i] & locked_mod_ਨਕਾਬ, 0, 0, layout);
        ਜੇ (WAYLAND_xkb_state_ਕੁੰਜੀ_get_level(seat->keyboard.xkb.state, ਕੁੰਜੀ, layout) == level) {
            masks_ਬਾਹਰਲਾ[ਨਕਾਬ_idx] = keymod_masks[i];

            ਜੇ (++ਨਕਾਬ_idx == masks_ਮਾਪ) {
                ਰੋਕੋ;
            }
        }
    }

    ਵਾਪਸ ਨਕਾਬ_idx;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ Wayland_KeymapIterator(ਬਣਤਰ xkb_keymap *keymap, xkb_keycode_t ਕੁੰਜੀ, ਖਾਲੀ *ਅੰਕੜੇ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    ਅਚਲ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ਅਚਲ xkb_mod_ਨਕਾਬ_t xkb_valid_mod_ਨਕਾਬ = seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ |
                                              seat->keyboard.xkb.alt_ਨਕਾਬ |
                                              seat->keyboard.xkb.level3_ਨਕਾਬ |
                                              seat->keyboard.xkb.level5_ਨਕਾਬ |
                                              seat->keyboard.xkb.caps_ਨਕਾਬ_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ਜੇ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_ਸਾਰਣੀ(SDL_SCANCODE_ਸਾਰਣੀ_LINUX, ਕੁੰਜੀ - 8);
    }

    ਲਈ (xkb_layout_ਸੂਚਕਾਂਕ_t layout = 0; layout < seat->keyboard.xkb.ਅੰਕ_layouts; ++layout) {
        ਅਚਲ xkb_level_ਸੂਚਕਾਂਕ_t ਅੰਕ_ਪੱਧਰ = WAYLAND_xkb_keymap_ਅੰਕ_ਪੱਧਰ_for_ਕੁੰਜੀ(seat->keyboard.xkb.keymap, ਕੁੰਜੀ, layout);
        ਲਈ (xkb_level_ਸੂਚਕਾਂਕ_t level = 0; level < ਅੰਕ_ਪੱਧਰ; ++level) {
            ਜੇ (WAYLAND_xkb_keymap_ਕੁੰਜੀ_get_syms_by_level(seat->keyboard.xkb.keymap, ਕੁੰਜੀ, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ਜੇ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ਕੁੰਜੀ_Sym(syms[0], ਕੁੰਜੀ);
                    ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
                        ਜਾਰੀ;
                    }
                }

                xkb_mod_ਨਕਾਬ_t xkb_mod_masks[16];
#ਜੇ SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(1, 0, 0)
                ਅਚਲ size_t ਅੰਕ_masks = WAYLAND_xkb_keymap_ਕੁੰਜੀ_get_mods_for_level(seat->keyboard.xkb.keymap, ਕੁੰਜੀ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ਨਹੀਂਤਾਂ
                ਅਚਲ size_t ਅੰਕ_masks = xkb_legacy_get_mods_for_level(seat, ਕੁੰਜੀ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ਜੇ_ਅੰਤ
                ਲਈ (size_t ਨਕਾਬ = 0; ਨਕਾਬ < ਅੰਕ_masks; ++ਨਕਾਬ) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ਜੇ ((xkb_mod_masks[ਨਕਾਬ] | xkb_valid_mod_ਨਕਾਬ) != xkb_valid_mod_ਨਕਾਬ) {
                        ਜਾਰੀ;
                    }

                    ਅਚਲ SDL_Keymod sdl_mod = (xkb_mod_masks[ਨਕਾਬ] & seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ ? SDL_KMOD_ਖਿਸਕਾਓ : 0) |
                                               (xkb_mod_masks[ਨਕਾਬ] & seat->keyboard.xkb.alt_ਨਕਾਬ ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[ਨਕਾਬ] & seat->keyboard.xkb.level3_ਨਕਾਬ ? SDL_KMOD_ਬਹੁਲਕ : 0) |
                                               (xkb_mod_masks[ਨਕਾਬ] & seat->keyboard.xkb.level5_ਨਕਾਬ ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[ਨਕਾਬ] & seat->keyboard.xkb.caps_ਨਕਾਬ_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ਕੁੰਜੀ_ਕੋਡ_From_ਕੁੰਜੀ_Sym(syms[0], ਕੁੰਜੀ, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ਜੇ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_ਅਗਲਾ_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        ਜੇ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ਕੁੰਜੀ *res = WAYLAND_wl_array_ਜੋੜੋ(&seat->keyboard.reserved_scancodes, ਆਕਾਰ(Wayland_Reserved_ਕੁੰਜੀ));
                        ਜੇ (res) {
                            res->scancode = scancode;
                            res->ਕੁੰਜੀ = ਕੁੰਜੀ - 8;
                        }
                    }

                    ਜੇ (!keycode) {
                        ਚੋਣ (scancode) {
                        ਹਾਲਤ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ਰੋਕੋ;
                        ਹਾਲਤ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ਰੋਕੋ;
                        ਹਾਲਤ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ਰੋਕੋ;
                        ਹਾਲਤ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ਰੋਕੋ;
                        ਮੂਲ:
                            keycode = SDL_SCANCODE_ਮੰਜ਼ਿਲ_KEYCODE(scancode);
                            ਰੋਕੋ;
                        }
                    }

                    SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_keymap(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *keyboard,
                                   uint32_t format, ਪੂਰਨ fd, uint32_t ਮਾਪ)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਅੱਖਰ *map_str;

    ਜੇ (!ਅੰਕੜੇ) {
        close(fd);
        ਵਾਪਸ;
    }

    ਜੇ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ਵਾਪਸ;
    }

    map_str = mmap(ਨਿਰਾ, ਮਾਪ, PROT_READ, MAP_PRIVATE, fd, 0);
    ਜੇ (map_str == MAP_FAILED) {
        close(fd);
        ਵਾਪਸ;
    }

    ਜੇ (seat->keyboard.xkb.keymap != ਨਿਰਾ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ਨਿਰਾ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_ਪਾਠ_V1,
                                                                   0);
    munmap(map_str, ਮਾਪ);
    close(fd);

    ਜੇ (!seat->keyboard.xkb.keymap) {
        SDL_ਸੈੱਟ_Error("failed to compile keymap");
        ਵਾਪਸ;
    }

    // Clear the old layouts.
    ਲਈ (xkb_layout_ਸੂਚਕਾਂਕ_t i = 0; i < seat->keyboard.xkb.ਅੰਕ_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ਨਿਰਾ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.ਅੰਕ_layouts = 0;

#ਜੇ SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(1, 10, 0)
    seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_ਖਿਸਕਾਓ);
    seat->keyboard.xkb.ctrl_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.ਅੰਕ_ਨਕਾਬ = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ਅੰਕ);
    seat->keyboard.xkb.caps_ਨਕਾਬ_2 = WAYLAND_xkb_keymap_mod_get_ਨਕਾਬ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_MOD_ਸੂਚਕਾਂਕ(mod) \
    WAYLAND_xkb_keymap_mod_get_ਸੂਚਕਾਂਕ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(ਖਿਸਕਾਓ_2);
    seat->keyboard.xkb.ctrl_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(CTRL);
    seat->keyboard.xkb.alt_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(ALT);
    seat->keyboard.xkb.gui_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(MOD5);
    seat->keyboard.xkb.level5_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(MOD3);
    seat->keyboard.xkb.ਅੰਕ_ਨਕਾਬ = 1 << GET_MOD_ਸੂਚਕਾਂਕ(ਅੰਕ_2);
    seat->keyboard.xkb.caps_ਨਕਾਬ_2 = 1 << GET_MOD_ਸੂਚਕਾਂਕ(CAPS);
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ GET_MOD_ਸੂਚਕਾਂਕ
#ਜੇ_ਅੰਤ

    ਜੇ (seat->keyboard.xkb.state != ਨਿਰਾ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ਨਿਰਾ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ਜੇ (!seat->keyboard.xkb.state) {
        SDL_ਸੈੱਟ_Error("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ਨਿਰਾ;
        ਵਾਪਸ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ਨਿਰਾ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.ਅੰਕ_layouts = WAYLAND_xkb_keymap_ਅੰਕ_layouts(seat->keyboard.xkb.keymap);
    ਜੇ (seat->keyboard.xkb.ਅੰਕ_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.ਅੰਕ_layouts, ਆਕਾਰ(SDL_Keymap *));
        ਜੇ (!seat->keyboard.sdl_keymap) {
            ਵਾਪਸ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        ਲਈ (xkb_layout_ਸੂਚਕਾਂਕ_t i = 0; i < seat->keyboard.xkb.ਅੰਕ_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ਜੇ (!seat->keyboard.sdl_keymap[i]) {
                ਲਈ (xkb_layout_ਸੂਚਕਾਂਕ_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ਨਿਰਾ;
                ਵਾਪਸ;
            }
        }

        WAYLAND_xkb_keymap_ਕੁੰਜੀ_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_ਨਕਾਬ(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ਅੰਕ_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_ਸੈੱਟ_Keymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ਅਚਲ ਅੱਖਰ *locale = SDL_getenv("LC_ALL");
    ਜੇ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ਜੇ (!locale) {
            locale = SDL_getenv("LANG");
            ਜੇ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ਜੇ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ਜੇ (seat->keyboard.xkb.compose_ਸਾਰਣੀ != ਨਿਰਾ) {
            WAYLAND_xkb_compose_ਸਾਰਣੀ_unref(seat->keyboard.xkb.compose_ਸਾਰਣੀ);
            seat->keyboard.xkb.compose_ਸਾਰਣੀ = ਨਿਰਾ;
        }
        seat->keyboard.xkb.compose_ਸਾਰਣੀ = WAYLAND_xkb_compose_ਸਾਰਣੀ_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ਜੇ (seat->keyboard.xkb.compose_ਸਾਰਣੀ) {
            // Set up XKB compose state
            ਜੇ (seat->keyboard.xkb.compose_state != ਨਿਰਾ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ਨਿਰਾ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_ਸਾਰਣੀ,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ਜੇ (!seat->keyboard.xkb.compose_state) {
                SDL_ਸੈੱਟ_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_ਸਾਰਣੀ_unref(seat->keyboard.xkb.compose_ਸਾਰਣੀ);
                seat->keyboard.xkb.compose_ਸਾਰਣੀ = ਨਿਰਾ;
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ਸਥਿਰ SDL_Scancode Wayland_Get_Scancode_For_ਕੁੰਜੀ(SDL_WaylandSeat *seat, Uint32 ਕੁੰਜੀ, ਅਚਲ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ਜੇ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_ਸਾਰਣੀ(SDL_SCANCODE_ਸਾਰਣੀ_LINUX, ਕੁੰਜੀ);

        // No table entry? Check the reserved list.
        ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ਕੁੰਜੀ *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ਜੇ (i->ਕੁੰਜੀ == ਕੁੰਜੀ) {
                    ਵਾਪਸ i->scancode;
                }
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ xkb_keysym_t *keysym;
        ਜੇ (WAYLAND_xkb_state_ਕੁੰਜੀ_get_syms(seat->keyboard.xkb.state, ਕੁੰਜੀ + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ਕੁੰਜੀ_Sym(keysym[0], ਕੁੰਜੀ + 8);
            ਜੇ (syms) {
                *syms = keysym;
            }
        }
    }

    ਵਾਪਸ scancode;
}

ਸਥਿਰ ਖਾਲੀ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ਕੁੰਜੀ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ਜੇ (!ਕੁੰਜੀ_pressed) {
        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ਖਿਸਕਾਓ;
            }
        } ਨਹੀਂਤਾਂ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
        }

        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ਨਹੀਂਤਾਂ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ਨਹੀਂਤਾਂ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ਨਹੀਂਤਾਂ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ਬਹੁਲਕ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ਬਹੁਲਕ;
            }
        } ਨਹੀਂਤਾਂ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ਬਹੁਲਕ;
        }

        ਜੇ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_ਨਕਾਬ) {
            ਜੇ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ਨਹੀਂਤਾਂ {
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
    ਅਚਲ xkb_mod_ਨਕਾਬ_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.ਖਿਸਕਾਓ_ਨਕਾਬ) {
        ਜੇ (seat->keyboard.pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ਖਿਸਕਾਓ);
        } ਨਹੀਂਤਾਂ ਜੇ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ਖਿਸਕਾਓ)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ਖਿਸਕਾਓ;
        }
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ਖਿਸਕਾਓ;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_ਨਕਾਬ) {
        ਜੇ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ਨਹੀਂਤਾਂ ਜੇ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.alt_ਨਕਾਬ) {
        ਜੇ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ਨਹੀਂਤਾਂ ਜੇ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.gui_ਨਕਾਬ) {
        ਜੇ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ਨਹੀਂਤਾਂ ਜੇ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.level3_ਨਕਾਬ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ਬਹੁਲਕ;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.level5_ਨਕਾਬ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.caps_ਨਕਾਬ_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ਜੇ (xkb_locked_modifiers & seat->keyboard.xkb.ਅੰਕ_ਨਕਾਬ) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ਅੰਕ;
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ਅੰਕ;
    }

    SDL_ਸੈੱਟ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ਸਥਿਰ ਖਾਲੀ Wayland_Handle_Modifier_ਕੁੰਜੀਆਂ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ਅਚਲ SDL_Keycode keycode = SDL_Get_ਕੁੰਜੀ_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ਚੋਣ (keycode) {
    ਹਾਲਤ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_ਬਹੁਲਕ:
        mod = SDL_KMOD_ਬਹੁਲਕ;
        ਰੋਕੋ;
    ਹਾਲਤ SDLK_LEVEL5_ਖਿਸਕਾਓ:
        mod = SDL_KMOD_LEVEL5;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ;
    }

    ਜੇ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ਨਹੀਂਤਾਂ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_enter(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *keyboard,
                                  uint32_t serial, ਬਣਤਰ wl_surface *surface,
                                  ਬਣਤਰ wl_array *ਕੁੰਜੀਆਂ)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    uint32_t *ਕੁੰਜੀ;

    ਜੇ (!surface) {
        // Enter event for a destroyed surface.
        ਵਾਪਸ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);
    ਜੇ (!ਖਿੜਕੀ) {
        // Not a surface owned by SDL.
        ਵਾਪਸ;
    }

    ++ਖਿੜਕੀ->keyboard_focus_ਗਿਣਤੀ;
    seat->keyboard.focus = ਖਿੜਕੀ;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ->sdlwindow->keyboard_focus ? ਖਿੜਕੀ->sdlwindow->keyboard_focus : ਖਿੜਕੀ->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_ਸੂਚਕ_Grabs(seat->display, ਖਿੜਕੀ);

    // Update text input and IME focus.
    Wayland_Seat_Update_ਪਾਠ_ਨਿਵੇਸ਼(seat);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    ਜੇ (!seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼) {
        SDL_IME_ਸੈੱਟ_Focus(true);
    }
#ਜੇ_ਅੰਤ

    Uint64 timestamp = SDL_GetTicksNS();
    ਖਿੜਕੀ->ਆਖਰੀ_focus_event_ਸਮਾਂ_ns = timestamp;

    Wayland_Seat_ਸੈੱਟ_Keymap(seat);

    wl_array_for_each (ਕੁੰਜੀ, ਕੁੰਜੀਆਂ) {
        ਅਚਲ SDL_Scancode scancode = Wayland_Get_Scancode_For_ਕੁੰਜੀ(seat, *ਕੁੰਜੀ, ਨਿਰਾ);
        ਜੇ (scancode != SDL_SCANCODE_UNKNOWN) {
            ਅਚਲ SDL_Keycode keycode = SDL_Get_ਕੁੰਜੀ_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ਚੋਣ (keycode) {
            ਹਾਲਤ SDLK_LSHIFT:
            ਹਾਲਤ SDLK_RSHIFT:
            ਹਾਲਤ SDLK_LCTRL:
            ਹਾਲਤ SDLK_RCTRL:
            ਹਾਲਤ SDLK_LALT:
            ਹਾਲਤ SDLK_RALT:
            ਹਾਲਤ SDLK_LGUI:
            ਹਾਲਤ SDLK_RGUI:
            ਹਾਲਤ SDLK_ਬਹੁਲਕ:
            ਹਾਲਤ SDLK_LEVEL5_ਖਿਸਕਾਓ:
                Wayland_Handle_Modifier_ਕੁੰਜੀਆਂ(seat, scancode, true);
                SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ਕੁੰਜੀ, scancode, true);
                ਰੋਕੋ;
            ਮੂਲ:
                ਰੋਕੋ;
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_leave(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *keyboard,
                                  uint32_t serial, ਬਣਤਰ wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;

    ਜੇ (!surface) {
        // Leave event for a destroyed surface.
        ਵਾਪਸ;
    }

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface);
    ਜੇ (!ਖਿੜਕੀ) {
        // Not a surface owned by SDL.
        ਵਾਪਸ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ਕੁੰਜੀ = 0;

    SDL_ਖਿੜਕੀ *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ਜਦੋਂ (keyboard_focus && SDL_ਖਿੜਕੀ_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->ਮਾਪਾ;
    }

    ਅਚਲ bool had_focus = keyboard_focus && ਖਿੜਕੀ->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ਨਿਰਾ;
    --ਖਿੜਕੀ->keyboard_focus_ਗਿਣਤੀ;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ਜੇ (!ਖਿੜਕੀ->keyboard_focus_ਗਿਣਤੀ && had_focus) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_ਸੂਚਕ_Grabs(seat->display, ਖਿੜਕੀ);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_ਪਾਠ_ਨਿਵੇਸ਼(seat);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    ਜੇ (!seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼ && !ਖਿੜਕੀ->keyboard_focus_ਗਿਣਤੀ) {
        SDL_IME_ਸੈੱਟ_Focus(false);
    }
#ਜੇ_ਅੰਤ

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ਜੇ (SDL_GetMouseFocus() == ਖਿੜਕੀ->sdlwindow && !ਖਿੜਕੀ->ਸੂਚਕ_focus_ਗਿਣਤੀ && !ਖਿੜਕੀ->ਸਰਗਰਮ_touch_ਗਿਣਤੀ) {
        SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_Offer(seat->ਅੰਕੜੇ_device, ਨਿਰਾ);
}

ਸਥਿਰ bool keyboard_ਨਿਵੇਸ਼_get_ਪਾਠ(ਅੱਖਰ ਪਾਠ[8], ਅਚਲ SDL_WaylandSeat *seat, uint32_t ਕੁੰਜੀ, bool ਥੱਲੇ, bool *handled_by_ime)
{
    ਅਚਲ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ਜੇ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ਵਾਪਸ false;
    }

    // TODO: Can this happen?
    ਜੇ (WAYLAND_xkb_state_ਕੁੰਜੀ_get_syms(seat->keyboard.xkb.state, ਕੁੰਜੀ + 8, &syms) != 1) {
        ਵਾਪਸ false;
    }
    sym = syms[0];

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_IME
    ਜੇ (SDL_IME_Process_ਕੁੰਜੀ_Event(sym, ਕੁੰਜੀ + 8, ਥੱਲੇ)) {
        ਜੇ (handled_by_ime) {
            *handled_by_ime = true;
        }
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!ਥੱਲੇ) {
        ਵਾਪਸ false;
    }

    ਜੇ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ਚੋਣ (WAYLAND_xkb_compose_state_get_ਸਥਿਤੀ(seat->keyboard.xkb.compose_state)) {
        ਹਾਲਤ XKB_COMPOSE_COMPOSING:
            ਜੇ (handled_by_ime) {
                *handled_by_ime = true;
            }
            ਵਾਪਸ true;
        ਹਾਲਤ XKB_COMPOSE_CANCELLED:
        ਮੂਲ:
            sym = XKB_ਕੁੰਜੀ_No_ਚਿੰਨ੍ਹ;
            ਰੋਕੋ;
        ਹਾਲਤ XKB_COMPOSE_NOTHING:
            ਰੋਕੋ;
        ਹਾਲਤ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ਰੋਕੋ;
        }
    }

    ਵਾਪਸ WAYLAND_xkb_keysym_ਮੰਜ਼ਿਲ_utf8(sym, ਪਾਠ, 8) > 0;
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_ਕੁੰਜੀ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *keyboard,
                                uint32_t serial, uint32_t ਸਮਾਂ, uint32_t ਕੁੰਜੀ,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਗਿਣਤੀ wl_keyboard_ਕੁੰਜੀ_state state = state_w;
    ਅੱਖਰ ਪਾਠ[8];
    bool has_ਪਾਠ = false;
    bool handled_by_ime = false;
    ਅਚਲ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, ਸਮਾਂ);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ਜੇ (state == WL_KEYBOARD_ਕੁੰਜੀ_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ਜੇ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ਕੁੰਜੀ_repeats(seat->keyboard.xkb.keymap, ਕੁੰਜੀ + 8)) {
            ਵਾਪਸ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ਕੁੰਜੀ_STATE_PRESSED;
    }

    Wayland_Seat_ਸੈੱਟ_Keymap(seat);

    ਜੇ (state == WL_KEYBOARD_ਕੁੰਜੀ_STATE_PRESSED) {
        SDL_ਖਿੜਕੀ *keyboard_focus = SDL_GetKeyboardFocus();
        ਜੇ (keyboard_focus && SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(keyboard_focus)) {
            has_ਪਾਠ = keyboard_ਨਿਵੇਸ਼_get_ਪਾਠ(ਪਾਠ, seat, ਕੁੰਜੀ, true, &handled_by_ime);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਕੁੰਜੀ == seat->keyboard.repeat.ਕੁੰਜੀ) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ਅਚਲ Uint64 elapsed = SDL_MS_ਮੰਜ਼ਿਲ_NS(ਸਮਾਂ - seat->keyboard.repeat.wl_press_ਸਮਾਂ_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ਕੁੰਜੀ = 0;
        }
        keyboard_ਨਿਵੇਸ਼_get_ਪਾਠ(ਪਾਠ, seat, ਕੁੰਜੀ, false, &handled_by_ime);
    }

    ਅਚਲ xkb_keysym_t *syms = ਨਿਰਾ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ਕੁੰਜੀ(seat, ਕੁੰਜੀ, &syms);
    Wayland_Handle_Modifier_ਕੁੰਜੀਆਂ(seat, scancode, state == WL_KEYBOARD_ਕੁੰਜੀ_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ਜੇ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ਅਚਲ SDL_Keycode keycode = (SDL_Keycode)SDL_ਕੁੰਜੀ_Sym_ਮੰਜ਼ਿਲ_Ucs4(syms[0]);
        ਜੇ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ਜੇ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_ਨਕਾਬ) {
                scancode = SDL_Get_Keymap_ਅਗਲਾ_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_ਸੈੱਟ_Keymap_ਇੰਦਰਾਜ(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ਕੁੰਜੀ_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ਕੁੰਜੀ, scancode, state == WL_KEYBOARD_ਕੁੰਜੀ_STATE_PRESSED);

    ਜੇ (state == WL_KEYBOARD_ਕੁੰਜੀ_STATE_PRESSED) {
        ਜੇ (handled_by_ime) {
            has_ਪਾਠ = false;
        }
        ਜੇ (has_ਪਾਠ && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_ਪਾਠ(ਪਾਠ);
        }
        ਜੇ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ਕੁੰਜੀ_repeats(seat->keyboard.xkb.keymap, ਕੁੰਜੀ + 8)) {
            keyboard_repeat_ਸੈੱਟ(&seat->keyboard.repeat, seat->keyboard.sdl_id, ਕੁੰਜੀ, ਸਮਾਂ, timestamp_ns, scancode, has_ਪਾਠ ? ਪਾਠ : ਨਿਰਾ);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_modifiers(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t ਸਮੂਹ)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    ਅਚਲ uint32_t ਪਿਛਲਾ_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = ਸਮੂਹ;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ਜੇ (!seat->keyboard.xkb.state) {
        ਵਾਪਸ;
    }

    WAYLAND_xkb_state_update_ਨਕਾਬ(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, ਸਮੂਹ);

    // If a key is repeating, update the text to apply the modifier.
    ਜੇ (seat->keyboard.repeat.ਕੁੰਜੀ) {
        ਅੱਖਰ ਪਾਠ[8];

        ਜੇ (keyboard_ਨਿਵੇਸ਼_get_ਪਾਠ(ਪਾਠ, seat, seat->keyboard.repeat.ਕੁੰਜੀ, true, ਨਿਰਾ)) {
            SDL_strlcpy(seat->keyboard.repeat.ਪਾਠ, ਪਾਠ, SDL_arraysize(seat->keyboard.repeat.ਪਾਠ));
        }
    }

    ਜੇ (ਸਮੂਹ != ਪਿਛਲਾ_layout) {
        Wayland_Seat_ਸੈੱਟ_Keymap(seat);

        ਜੇ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ keyboard_handle_repeat_info(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_keyboard *wl_keyboard,
                                        int32_t ਦਰ, int32_t delay)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ;
    seat->keyboard.repeat.repeat_ਦਰ = ਦਰ;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ਜੇ (!ਦਰ) {
        seat->keyboard.repeat.ਕੁੰਜੀ = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ਕੁੰਜੀ,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_Destroy_ਸੂਚਕ(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->ਸੂਚਕ_2.cursor_state);

    // End any active gestures.
    ਜੇ (seat->ਸੂਚਕ_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_ਸਿਰਾ, 0, seat->ਸੂਚਕ_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ਜੇ (seat->ਸੂਚਕ_2.focus) {
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = seat->ਸੂਚਕ_2.focus->surface;
        ਸੂਚਕ_dispatch_leave(seat, false);
        seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = ਨਿਰਾ;
    }

    SDL_RemoveMouse(seat->ਸੂਚਕ_2.sdl_id);

    ਜੇ (seat->ਸੂਚਕ_2.confined_ਸੂਚਕ) {
        zwp_confined_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.confined_ਸੂਚਕ);
    }

    ਜੇ (seat->ਸੂਚਕ_2.locked_ਸੂਚਕ) {
        zwp_locked_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.locked_ਸੂਚਕ);
    }

    ਜੇ (seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
        zwp_relative_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.relative_ਸੂਚਕ);
    }

    ਜੇ (seat->ਸੂਚਕ_2.timestamps) {
        zwp_ਨਿਵੇਸ਼_timestamps_v1_destroy(seat->ਸੂਚਕ_2.timestamps);
    }

    ਜੇ (seat->ਸੂਚਕ_2.gesture_pinch) {
        zwp_ਸੂਚਕ_gesture_pinch_v1_destroy(seat->ਸੂਚਕ_2.gesture_pinch);
    }

    ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
        ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) >= WL_ਸੂਚਕ_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            wl_ਸੂਚਕ_release(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
        } ਨਹੀਂਤਾਂ {
            wl_ਸੂਚਕ_destroy(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
        }
    }

    SDL_zero(seat->ਸੂਚਕ_2);
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ਜੇ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ਜੇ (seat->keyboard.sdl_keymap) {
        ਜੇ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ਅੰਕ_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_ਸੈੱਟ_Mod_State(SDL_KMOD_NONE);
        }
        ਲਈ (xkb_layout_ਸੂਚਕਾਂਕ_t i = 0; i < seat->keyboard.xkb.ਅੰਕ_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ਨਿਰਾ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ਜੇ (seat->keyboard.ਕੁੰਜੀ_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ਕੁੰਜੀ_inhibitor);
    }

    ਜੇ (seat->keyboard.timestamps) {
        zwp_ਨਿਵੇਸ਼_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ਜੇ (seat->keyboard.wl_keyboard) {
        ਜੇ (wl_keyboard_get_ਸੰਸਕਰਣ(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ਨਹੀਂਤਾਂ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ਜੇ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ਜੇ (seat->keyboard.xkb.compose_ਸਾਰਣੀ) {
        WAYLAND_xkb_compose_ਸਾਰਣੀ_unref(seat->keyboard.xkb.compose_ਸਾਰਣੀ);
    }

    ਜੇ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ਜੇ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ਜੇ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ਜੇ (seat->touch.timestamps) {
        zwp_ਨਿਵੇਸ਼_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ਜੇ (seat->touch.wl_touch) {
        ਜੇ (wl_touch_get_ਸੰਸਕਰਣ(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            wl_touch_release(seat->touch.wl_touch);
        } ਨਹੀਂਤਾਂ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ਸਥਿਰ ਖਾਲੀ seat_handle_capabilities(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    ਅੱਖਰ name_fmt[256];

    ਜੇ ((capabilities & WL_SEAT_CAPABILITY_ਸੂਚਕ) && !seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
        seat->ਸੂਚਕ_2.wl_ਸੂਚਕ = wl_seat_get_ਸੂਚਕ(wl_seat);
        SDL_zero(seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_ਸੂਚਕ_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ, seat);
        wl_ਸੂਚਕ_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ, &ਸੂਚਕ_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_ਸੂਚਕ_Gestures(seat);

        seat->ਸੂਚਕ_2.sdl_id = SDL_Get_ਅਗਲਾ_Object_ID();

        ਜੇ (seat->name) {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_ਸੂਚਕ_NAME, seat->name);
        } ਨਹੀਂਤਾਂ {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_ਸੂਚਕ_NAME, seat->ਸੂਚਕ_2.sdl_id);
        }

        SDL_ਜੋੜੋ_Mouse(seat->ਸੂਚਕ_2.sdl_id, name_fmt);
    } ਨਹੀਂਤਾਂ ਜੇ (!(capabilities & WL_SEAT_CAPABILITY_ਸੂਚਕ) && seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
        Wayland_Seat_Destroy_ਸੂਚਕ(seat);
    }

    ਜੇ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->touch.wl_touch, seat);
        wl_touch_ਜੋੜੋ_listener(seat->touch.wl_touch, &touch_listener, seat);

        ਜੇ (seat->name) {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ਨਹੀਂਤਾਂ {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_ਜੋੜੋ_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, name_fmt);
    } ਨਹੀਂਤਾਂ ਜੇ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ਜੇ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_ਜੋੜੋ_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_ਅਗਲਾ_Object_ID();

        ਜੇ (seat->name) {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ਨਹੀਂਤਾਂ {
            SDL_snprintf(name_fmt, ਆਕਾਰ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_ਜੋੜੋ_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } ਨਹੀਂਤਾਂ ਜੇ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_ਰਜਿਸਟਰ_ਨਿਵੇਸ਼_Timestamp_Listeners(seat);
}

ਸਥਿਰ ਖਾਲੀ seat_handle_name(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_seat *wl_seat, ਅਚਲ ਅੱਖਰ *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;

    ਜੇ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_offer_handle_offer(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_offer *wl_ਅੰਕੜੇ_offer,
                                    ਅਚਲ ਅੱਖਰ *mime_type)
{
    SDL_Wayland_ਅੰਕੜੇ_Offer *offer = ਅੰਕੜੇ;
    Wayland_ਅੰਕੜੇ_Offer_ਜੋੜੋ_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_ਅੰਕੜੇ_offer ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)wl_ਅੰਕੜੇ_offer) : -1),
                 mime_type);
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_offer_handle_ਸਰੋਤ_actions(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_offer *wl_ਅੰਕੜੇ_offer,
                                             uint32_t ਸਰੋਤ_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_ਅੰਕੜੇ_offer ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)wl_ਅੰਕੜੇ_offer) : -1),
                 ਸਰੋਤ_actions);
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_offer_handle_actions(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_offer *wl_ਅੰਕੜੇ_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_ਅੰਕੜੇ_offer ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)wl_ਅੰਕੜੇ_offer) : -1),
                 dnd_action);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_ਅੰਕੜੇ_offer_listener ਅੰਕੜੇ_offer_listener = {
    ਅੰਕੜੇ_offer_handle_offer,
    ਅੰਕੜੇ_offer_handle_ਸਰੋਤ_actions, // Version 3
    ਅੰਕੜੇ_offer_handle_actions,        // Version 3
};

ਸਥਿਰ ਖਾਲੀ primary_selection_offer_handle_offer(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ਅਚਲ ਅੱਖਰ *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = ਅੰਕੜੇ;
    Wayland_Primary_Selection_Offer_ਜੋੜੋ_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_ਅੰਕੜੇ_offer(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device,
                                          ਬਣਤਰ wl_ਅੰਕੜੇ_offer *id)
{
    SDL_Wayland_ਅੰਕੜੇ_Offer *ਅੰਕੜੇ_offer = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ_offer));
    ਜੇ (ਅੰਕੜੇ_offer) {
        SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = (SDL_Wayland_ਅੰਕੜੇ_Device *)ਅੰਕੜੇ;
        ਅੰਕੜੇ_offer->offer = id;
        ਅੰਕੜੇ_offer->ਅੰਕੜੇ_device = ਅੰਕੜੇ_device;
        ਅੰਕੜੇ_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(ਅੰਕੜੇ_offer->mimes));
        wl_ਅੰਕੜੇ_offer_ਸੈੱਟ_user_ਅੰਕੜੇ(id, ਅੰਕੜੇ_offer);
        wl_ਅੰਕੜੇ_offer_ਜੋੜੋ_listener(id, &ਅੰਕੜੇ_offer_listener, ਅੰਕੜੇ_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id) : -1));
    }
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_enter(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device,
                                     uint32_t serial, ਬਣਤਰ wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ਬਣਤਰ wl_ਅੰਕੜੇ_offer *id)
{
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = surface ? Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface) : ਨਿਰਾ;
    ਅੰਕੜੇ_device->has_mime_file = false;
    ਅੰਕੜੇ_device->ਪਾਠ_mime_type = ਨਿਰਾ;

    ਅੰਕੜੇ_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ਜੇ (id) {
        ਅੰਕੜੇ_device->drag_offer = wl_ਅੰਕੜੇ_offer_get_user_ਅੰਕੜੇ(id);
    }

    ਜੇ (ਅੰਕੜੇ_device->drag_offer && ਖਿੜਕੀ && ਖਿੜਕੀ->ਮੰਨਦਾ_drag_and_drop) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
        ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(ਅੰਕੜੇ_device->drag_offer, FILE_PORTAL_MIME)) {
            ਅੰਕੜੇ_device->has_mime_file = true;
            wl_ਅੰਕੜੇ_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#ਜੇ_ਅੰਤ
        ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(ਅੰਕੜੇ_device->drag_offer, FILE_MIME)) {
            ਅੰਕੜੇ_device->has_mime_file = true;
            wl_ਅੰਕੜੇ_offer_accept(id, serial, FILE_MIME);
        }

        ਜੇ (!ਅੰਕੜੇ_device->has_mime_file) {
            size_t mime_ਗਿਣਤੀ = 0;
            ਅਚਲ ਅੱਖਰ *ਅਚਲ *ਪਾਠ_mime_types = Wayland_Get_ਪਾਠ_Mime_Types(SDL_GetVideoDevice(), &mime_ਗਿਣਤੀ);
            ਲਈ (size_t i = 0; i < mime_ਗਿਣਤੀ; ++i) {
                ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(ਅੰਕੜੇ_device->drag_offer, ਪਾਠ_mime_types[i])) {
                    ਅੰਕੜੇ_device->ਪਾਠ_mime_type = ਪਾਠ_mime_types[i];
                    wl_ਅੰਕੜੇ_offer_accept(id, serial, ਪਾਠ_mime_types[i]);
                    ਰੋਕੋ;
                }
            }
        }

        ਜੇ (ਅੰਕੜੇ_device->has_mime_file || ਅੰਕੜੇ_device->ਪਾਠ_mime_type) {
            // SDL only supports "copy" style drag and drop
            ਜੇ (wl_ਅੰਕੜੇ_offer_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ_device->drag_offer->offer) >= WL_ਅੰਕੜੇ_OFFER_ਸੈੱਟ_ACTIONS_SINCE_ਸੰਸਕਰਣ) {
                wl_ਅੰਕੜੇ_offer_ਸੈੱਟ_actions(ਅੰਕੜੇ_device->drag_offer->offer, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_COPY, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ = ਖਿੜਕੀ->sdlwindow;
            ਅੰਕੜੇ_device->dnd_surface = surface;
            ਦੁੱਗਣਾ dx = wl_fixed_ਮੰਜ਼ਿਲ_double(x);
            ਦੁੱਗਣਾ dy = wl_fixed_ਮੰਜ਼ਿਲ_double(y);

            // If over the mask, adjust the offset.
            ਜੇ (surface == ਖਿੜਕੀ->ਨਕਾਬ.surface) {
                dx += (ਦੁੱਗਣਾ)ਖਿੜਕੀ->ਨਕਾਬ.ਵਿੱਥ_x;
                dy += (ਦੁੱਗਣਾ)ਖਿੜਕੀ->ਨਕਾਬ.ਵਿੱਥ_y;
            }

            dx *= ਖਿੜਕੀ->ਸੂਚਕ_scale.x;
            dy *= ਖਿੜਕੀ->ਸੂਚਕ_scale.y;

            SDL_SendDropPosition(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ)dx, (ਦਸ਼ਮਲਵ)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id),
                         wl_fixed_ਮੰਜ਼ਿਲ_int(x), wl_fixed_ਮੰਜ਼ਿਲ_int(y), SDL_Get_ਖਿੜਕੀ_ID(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ), serial);
        } ਨਹੀਂਤਾਂ {
            // Decline the offer.
            wl_ਅੰਕੜੇ_offer_accept(id, serial, ਨਿਰਾ);
            ਜੇ (wl_ਅੰਕੜੇ_offer_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ_device->drag_offer->offer) >= WL_ਅੰਕੜੇ_OFFER_ਸੈੱਟ_ACTIONS_SINCE_ਸੰਸਕਰਣ) {
                wl_ਅੰਕੜੇ_offer_ਸੈੱਟ_actions(ਅੰਕੜੇ_device->drag_offer->offer, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_NONE, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id), wl_fixed_ਮੰਜ਼ਿਲ_int(x), wl_fixed_ਮੰਜ਼ਿਲ_int(y), serial);
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ = ਨਿਰਾ;
        ਅੰਕੜੇ_device->dnd_surface = ਨਿਰਾ;

        // Decline the offer.
        ਜੇ (id) {
            wl_ਅੰਕੜੇ_offer_accept(id, serial, ਨਿਰਾ);
            ਜੇ (wl_ਅੰਕੜੇ_offer_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ_device->drag_offer->offer) >= WL_ਅੰਕੜੇ_OFFER_ਸੈੱਟ_ACTIONS_SINCE_ਸੰਸਕਰਣ) {
                wl_ਅੰਕੜੇ_offer_ਸੈੱਟ_actions(ਅੰਕੜੇ_device->drag_offer->offer, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_NONE, WL_ਅੰਕੜੇ_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id) : -1,
                     wl_fixed_ਮੰਜ਼ਿਲ_int(x), wl_fixed_ਮੰਜ਼ਿਲ_int(y), serial);
    }
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_leave(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device)
{
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਅੰਕੜੇ;

    ਜੇ (ਅੰਕੜੇ_device->drag_offer) {
        ਜੇ (ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ) {
            SDL_SendDropComplete(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ);
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ_device->drag_offer->offer),
                         SDL_Get_ਖਿੜਕੀ_ID(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ), ਅੰਕੜੇ_device->drag_serial);
        } ਨਹੀਂਤਾਂ {
            SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ_device->drag_offer->offer),
                         ਅੰਕੜੇ_device->drag_serial);
        }
        Wayland_ਅੰਕੜੇ_Offer_Destroy(ਅੰਕੜੇ_device->drag_offer);
        ਅੰਕੜੇ_device->drag_offer = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    ਅੰਕੜੇ_device->has_mime_file = false;
    ਅੰਕੜੇ_device->ਪਾਠ_mime_type = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_motion(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device,
                                      uint32_t ਸਮਾਂ, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਅੰਕੜੇ;

    ਜੇ (ਅੰਕੜੇ_device->drag_offer && ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ && (ਅੰਕੜੇ_device->has_mime_file || ਅੰਕੜੇ_device->ਪਾਠ_mime_type)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਦੁੱਗਣਾ dx = wl_fixed_ਮੰਜ਼ਿਲ_double(x);
        ਦੁੱਗਣਾ dy = wl_fixed_ਮੰਜ਼ਿਲ_double(y);

        // If over the mask, adjust the offset.
        ਜੇ (ਅੰਕੜੇ_device->dnd_surface == ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.surface) {
            dx += (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.ਵਿੱਥ_x;
            dy += (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਨਕਾਬ.ਵਿੱਥ_y;
        }

        dx *= ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.x;
        dy *= ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਸੂਚਕ_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ, (ਦਸ਼ਮਲਵ)dx, (ਦਸ਼ਮਲਵ)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ_device->drag_offer->offer),
                     wl_fixed_ਮੰਜ਼ਿਲ_int(x), wl_fixed_ਮੰਜ਼ਿਲ_int(y),
                     SDL_Get_ਖਿੜਕੀ_ID(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ), ਅੰਕੜੇ_device->drag_serial);
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_ਮੰਜ਼ਿਲ_int(x), wl_fixed_ਮੰਜ਼ਿਲ_int(y), -1);
    }
}

ਸਥਿਰ ਖਾਲੀ drop_cleanup_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *callback, uint32_t callback_ਅੰਕੜੇ)
{
    Wayland_Drop_ਅੰਕੜੇ *drop = (Wayland_Drop_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ਸਥਿਰ ਖਾਲੀ drop_dispatch_handler(ਖਾਲੀ *ਅੰਕੜੇ)
{
    Wayland_Drop_ਅੰਕੜੇ *drop = (Wayland_Drop_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_Wayland_ਅੰਕੜੇ_Offer *offer = drop->offer;
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = offer->ਅੰਕੜੇ_device;

    ਜੇ (drop->dnd_ਖਿੜਕੀ) {
        size_t ਲੰਮਾਈ;
        bool drop_handled = false;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
        ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            ਖਾਲੀ *ਬਫਰ_2 = Wayland_ਅੰਕੜੇ_Offer_Receive(offer, FILE_PORTAL_MIME, &ਲੰਮਾਈ);
            ਜੇ (ਬਫਰ_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ਜੇ (dbus) {
                    ਪੂਰਨ ਰਸਤਾ_ਗਿਣਤੀ = 0;
                    ਅੱਖਰ **paths = SDL_DBus_DocumentsPortalRetrieveFiles(ਬਫਰ_2, &ਰਸਤਾ_ਗਿਣਤੀ);
                    // If dropped files contain a directory the list is empty
                    ਜੇ (paths && ਰਸਤਾ_ਗਿਣਤੀ > 0) {
                        ਲਈ (ਪੂਰਨ i = 0; i < ਰਸਤਾ_ਗਿਣਤੀ; i++) {
                            SDL_SendDropFile(drop->dnd_ਖਿੜਕੀ, ਨਿਰਾ, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(ਬਫਰ_2);
            }
        }
#ਜੇ_ਅੰਤ
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        ਜੇ (!drop_handled) {
            ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(offer, FILE_MIME)) {
                ਖਾਲੀ *ਬਫਰ_2 = Wayland_ਅੰਕੜੇ_Offer_Receive(offer, FILE_MIME, &ਲੰਮਾਈ);
                ਜੇ (ਬਫਰ_2) {
                    ਅੱਖਰ *saveptr = ਨਿਰਾ;
                    ਅੱਖਰ *token = SDL_strtok_r((ਅੱਖਰ *)ਬਫਰ_2, "\r\n", &saveptr);
                    ਜਦੋਂ (token) {
                        ਜੇ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_ਖਿੜਕੀ, ਨਿਰਾ, token);
                        }
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    SDL_free(ਬਫਰ_2);
                    drop_handled = true;
                }
            } ਨਹੀਂਤਾਂ ਜੇ (Wayland_ਅੰਕੜੇ_Offer_Has_MIME(offer, drop->ਪਾਠ_mime_type)) {
                ਖਾਲੀ *ਬਫਰ_2 = Wayland_ਅੰਕੜੇ_Offer_Receive(offer, drop->ਪਾਠ_mime_type, &ਲੰਮਾਈ);
                ਜੇ (ਬਫਰ_2) {
                    ਅੱਖਰ *saveptr = ਨਿਰਾ;
                    ਅੱਖਰ *token = SDL_strtok_r((ਅੱਖਰ *)ਬਫਰ_2, "\r\n", &saveptr);
                    ਜਦੋਂ (token) {
                        SDL_Send_Drop_ਪਾਠ(drop->dnd_ਖਿੜਕੀ, token);
                        token = SDL_strtok_r(ਨਿਰਾ, "\r\n", &saveptr);
                    }
                    SDL_free(ਬਫਰ_2);
                    drop_handled = true;
                }
            }
        }

        ਜੇ (drop_handled && wl_ਅੰਕੜੇ_offer_get_ਸੰਸਕਰਣ(offer->offer) >= WL_ਅੰਕੜੇ_OFFER_ਅੰਤ_SINCE_ਸੰਸਕਰਣ) {
            wl_ਅੰਕੜੇ_offer_ਅੰਤ(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_ਖਿੜਕੀ);
    }

    Wayland_ਅੰਕੜੇ_Offer_Destroy(drop->offer);
    drop->offer = ਨਿਰਾ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(ਅੰਕੜੇ_device->seat->display->display);
    wl_callback_ਜੋੜੋ_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_drop(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device)
{
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਅੰਕੜੇ;

    ਜੇ (ਅੰਕੜੇ_device->drag_offer && ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ &&
        (ਅੰਕੜੇ_device->has_mime_file || ਅੰਕੜੇ_device->ਪਾਠ_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ_device->drag_offer->offer),
                     SDL_Get_ਖਿੜਕੀ_ID(ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ), ਅੰਕੜੇ_device->drag_serial);

        Wayland_ਕੰਮ_Thread_Context *ctx = ਅੰਕੜੇ_device->seat->display->ਕੰਮ_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_ਅੰਕੜੇ *drop = SDL_calloc(1, ਆਕਾਰ(Wayland_Drop_ਅੰਕੜੇ));
        ਜੇ (drop) {
            drop->offer = ਅੰਕੜੇ_device->drag_offer;
            drop->dnd_ਖਿੜਕੀ = ਅੰਕੜੇ_device->dnd_ਖਿੜਕੀ;
            drop->ਪਾਠ_mime_type = ਅੰਕੜੇ_device->ਪਾਠ_mime_type;

            WAYLAND_wl_list_ਪਾਓ(&ਅੰਕੜੇ_device->pending_drops, &drop->link);
            Wayland_ਕੰਮ_Thread_ਜੋੜੋ_ਕੰਮ(ctx, drop_dispatch_handler, drop, &drop->id);
        } ਨਹੀਂਤਾਂ {
            Wayland_ਅੰਕੜੇ_Offer_Destroy(ਅੰਕੜੇ_device->drag_offer);
        }
    } ਨਹੀਂਤਾਂ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_ਅੰਕੜੇ_Offer_Destroy(ਅੰਕੜੇ_device->drag_offer);
    }

    ਅੰਕੜੇ_device->drag_offer = ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_device_handle_selection(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_device *wl_ਅੰਕੜੇ_device,
                                         ਬਣਤਰ wl_ਅੰਕੜੇ_offer *id)
{
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਅੰਕੜੇ;
    SDL_Wayland_ਅੰਕੜੇ_Offer *offer = ਨਿਰਾ;

    ਜੇ (id) {
        offer = wl_ਅੰਕੜੇ_offer_get_user_ਅੰਕੜੇ(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id) : -1));

    Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_Offer(ਅੰਕੜੇ_device, offer);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_ਅੰਕੜੇ_device_listener ਅੰਕੜੇ_device_listener = {
    ਅੰਕੜੇ_device_handle_ਅੰਕੜੇ_offer,
    ਅੰਕੜੇ_device_handle_enter,
    ਅੰਕੜੇ_device_handle_leave,
    ਅੰਕੜੇ_device_handle_motion,
    ਅੰਕੜੇ_device_handle_drop,
    ਅੰਕੜੇ_device_handle_selection
};

ਸਥਿਰ ਖਾਲੀ primary_selection_device_handle_offer(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ਬਣਤਰ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, ਆਕਾਰ(*primary_selection_offer));
    ਜੇ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)ਅੰਕੜੇ;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_ਸੈੱਟ_user_ਅੰਕੜੇ(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_ਜੋੜੋ_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id) : -1));
}

ਸਥਿਰ ਖਾਲੀ primary_selection_device_handle_selection(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ਬਣਤਰ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = ਅੰਕੜੇ;
    SDL_WaylandPrimarySelectionOffer *offer = ਨਿਰਾ;

    ਜੇ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_ਅੰਕੜੇ(id);
    }

    ਜੇ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ਬਣਤਰ wl_proxy *)id) : -1));
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_enter(ਖਾਲੀ *ਅੰਕੜੇ,
                             ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                             ਬਣਤਰ wl_surface *surface)
{
    // No-op
}

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_leave(ਖਾਲੀ *ਅੰਕੜੇ,
                             ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                             ਬਣਤਰ wl_surface *surface)
{
    // No-op
}

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_preedit_string(ਖਾਲੀ *ਅੰਕੜੇ,
                                      ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                                      ਅਚਲ ਅੱਖਰ *ਪਾਠ,
                                      int32_t cursor_begin,
                                      int32_t cursor_ਸਿਰਾ)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    seat->ਪਾਠ_ਨਿਵੇਸ਼.has_preedit = true;
    ਜੇ (ਪਾਠ) {
        ਪੂਰਨ cursor_begin_utf8 = cursor_begin >= 0 ? (ਪੂਰਨ)SDL_utf8strnlen(ਪਾਠ, cursor_begin) : -1;
        ਪੂਰਨ cursor_ਸਿਰਾ_utf8 = cursor_ਸਿਰਾ >= 0 ? (ਪੂਰਨ)SDL_utf8strnlen(ਪਾਠ, cursor_ਸਿਰਾ) : -1;
        ਪੂਰਨ cursor_ਮਾਪ_utf8;
        ਜੇ (cursor_ਸਿਰਾ_utf8 >= 0) {
            ਜੇ (cursor_begin_utf8 >= 0) {
                cursor_ਮਾਪ_utf8 = cursor_ਸਿਰਾ_utf8 - cursor_begin_utf8;
            } ਨਹੀਂਤਾਂ {
                cursor_ਮਾਪ_utf8 = cursor_ਸਿਰਾ_utf8;
            }
        } ਨਹੀਂਤਾਂ {
            cursor_ਮਾਪ_utf8 = -1;
        }
        SDL_Send_Editing_ਪਾਠ(ਪਾਠ, cursor_begin_utf8, cursor_ਮਾਪ_utf8);
    } ਨਹੀਂਤਾਂ {
        SDL_Send_Editing_ਪਾਠ("", 0, 0);
    }
}

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_commit_string(ਖਾਲੀ *ਅੰਕੜੇ,
                                     ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                                     ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    SDL_Send_Keyboard_ਪਾਠ(ਪਾਠ);
}

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_delete_surrounding_ਪਾਠ(ਖਾਲੀ *ਅੰਕੜੇ,
                                               ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                                               uint32_t before_ਲੰਮਾਈ,
                                               uint32_t after_ਲੰਮਾਈ)
{
    // FIXME: Do we care about this event?
}

ਸਥਿਰ ਖਾਲੀ ਪਾਠ_ਨਿਵੇਸ਼_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ,
                            ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    ਜੇ (!seat->ਪਾਠ_ਨਿਵੇਸ਼.has_preedit) {
        SDL_Send_Editing_ਪਾਠ("", 0, 0);
    }
    seat->ਪਾਠ_ਨਿਵੇਸ਼.has_preedit = false;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_listener ਪਾਠ_ਨਿਵੇਸ਼_listener = {
    ਪਾਠ_ਨਿਵੇਸ਼_enter,
    ਪਾਠ_ਨਿਵੇਸ਼_leave,
    ਪਾਠ_ਨਿਵੇਸ਼_preedit_string,
    ਪਾਠ_ਨਿਵੇਸ਼_commit_string,
    ਪਾਠ_ਨਿਵੇਸ਼_delete_surrounding_ਪਾਠ,
    ਪਾਠ_ਨਿਵੇਸ਼_ਪੂਰਾ
};

ਸਥਿਰ ਖਾਲੀ Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_ID(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device)
{
    ਜੇ (!ਅੰਕੜੇ_device->id_str)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ਜੇ (dbus) {
            ਅਚਲ ਅੱਖਰ *id = dbus->bus_get_unique_name(dbus->session_conn);
            ਜੇ (id) {
                ਅੰਕੜੇ_device->id_str = SDL_strdup(id);
            }
        }
    }
    ਜੇ (!ਅੰਕੜੇ_device->id_str)
#ਜੇ_ਅੰਤ
    {
        ਅੱਖਰ id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, ਆਕਾਰ(id), "%" SDL_PRIu64, pid);
        ਅੰਕੜੇ_device->id_str = SDL_strdup(id);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_Create_ਅੰਕੜੇ_Device(SDL_WaylandSeat *seat)
{
    ਜੇ (!seat->display->ਅੰਕੜੇ_device_manager) {
        ਵਾਪਸ;
    }

    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ_device));
    ਜੇ (!ਅੰਕੜੇ_device) {
        ਵਾਪਸ;
    }

    ਅੰਕੜੇ_device->ਅੰਕੜੇ_device = wl_ਅੰਕੜੇ_device_manager_get_ਅੰਕੜੇ_device(
        seat->display->ਅੰਕੜੇ_device_manager, seat->wl_seat);
    ਅੰਕੜੇ_device->seat = seat;

    ਜੇ (!ਅੰਕੜੇ_device->ਅੰਕੜੇ_device) {
        SDL_free(ਅੰਕੜੇ_device);
        ਵਾਪਸ;
    }

    Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_ID(ਅੰਕੜੇ_device);
    WAYLAND_wl_list_init(&ਅੰਕੜੇ_device->pending_drops);
    wl_ਅੰਕੜੇ_device_ਸੈੱਟ_user_ਅੰਕੜੇ(ਅੰਕੜੇ_device->ਅੰਕੜੇ_device, ਅੰਕੜੇ_device);
    wl_ਅੰਕੜੇ_device_ਜੋੜੋ_listener(ਅੰਕੜੇ_device->ਅੰਕੜੇ_device, &ਅੰਕੜੇ_device_listener, ਅੰਕੜੇ_device);
    seat->ਅੰਕੜੇ_device = ਅੰਕੜੇ_device;
}

ਖਾਲੀ Wayland_Display_Init_ਅੰਕੜੇ_Device_Manager(SDL_Video_ਅੰਕੜੇ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_ਅੰਕੜੇ_Device(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ਜੇ (!seat->display->primary_selection_device_manager) {
        ਵਾਪਸ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, ਆਕਾਰ(*primary_selection_device));
    ਜੇ (!primary_selection_device) {
        ਵਾਪਸ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ਜੇ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ਨਹੀਂਤਾਂ {
        zwp_primary_selection_device_v1_ਸੈੱਟ_user_ਅੰਕੜੇ(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_ਜੋੜੋ_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

ਖਾਲੀ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ਅੰਕੜੇ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_Create_ਪਾਠ_ਨਿਵੇਸ਼(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->display->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼ = zwp_ਪਾਠ_ਨਿਵੇਸ਼_manager_v3_get_ਪਾਠ_ਨਿਵੇਸ਼(seat->display->ਪਾਠ_ਨਿਵੇਸ਼_manager, seat->wl_seat);

        ਜੇ (seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼) {
            zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼, seat);
            zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_ਜੋੜੋ_listener(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼,
                                           &ਪਾਠ_ਨਿਵੇਸ਼_listener, seat);
        }
    }
}

ਖਾਲੀ Wayland_Display_Init_ਪਾਠ_ਨਿਵੇਸ਼_Manager(SDL_Video_ਅੰਕੜੇ *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_ਪਾਠ_ਨਿਵੇਸ਼(seat);
    }
}

// Pen/Tablet support...
ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_type(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਚੋਣ (type) {
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CASE(typ) ਹਾਲਤ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ਵਾਪਸ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CASE
        ਮੂਲ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_hardware_serial(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_hardware_id_wacom(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->info.wacom_id = id_lo;
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_capability(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਚੋਣ (capability) {
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CASE(wltyp,sdltyp) ਹਾਲਤ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ਵਾਪਸ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(ਦੂਰੀ_2, SDL_PEN_CAPABILITY_ਦੂਰੀ);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CASE
        ਮੂਲ: ਰੋਕੋ;  // unsupported here.
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਜੇ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = sdltool->focus ? sdltool->focus->sdlwindow : ਨਿਰਾ;
        sdltool->instance_id = SDL_ਜੋੜੋ_Pen_Device(0, ਨਿਰਾ, ਖਿੜਕੀ, &sdltool->info, sdltool, false);
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_removed(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਜੇ (sdltool->instance_id) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = sdltool->focus ? sdltool->focus->sdlwindow : ਨਿਰਾ;
        SDL_RemovePenDevice(0, ਖਿੜਕੀ, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_proximity_ਵਿੱਚ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t serial, ਬਣਤਰ zwp_tablet_v2 *tablet, ਬਣਤਰ wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = surface ? Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(surface) : ਨਿਰਾ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ਨਿਰਾ;
    sdltool->proximity_serial = serial;
    sdltool->ਚੌਖਟਾ.have_proximity = true;
    sdltool->ਚੌਖਟਾ.ਵਿੱਚ_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_proximity_ਬਾਹਰਲਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.have_proximity = true;
    sdltool->ਚੌਖਟਾ.ਵਿੱਚ_proximity = false;
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_ਥੱਲੇ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.tool_state = WAYLAND_TABLET_TOOL_STATE_ਥੱਲੇ;
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_ਉੱਪਰ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.tool_state = WAYLAND_TABLET_TOOL_STATE_ਉੱਪਰ;
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_motion(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = sdltool->focus;
    ਜੇ (windowdata) {
        sdltool->ਚੌਖਟਾ.x = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(sx_w) * windowdata->ਸੂਚਕ_scale.x);
        sdltool->ਚੌਖਟਾ.y = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(sy_w) * windowdata->ਸੂਚਕ_scale.y);
        sdltool->ਚੌਖਟਾ.have_motion = true;
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_pressure(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_PRESSURE] = ((ਦਸ਼ਮਲਵ) pressure) / 65535.0f;
    sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_PRESSURE);
    ਜੇ (pressure) {
        sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_ਦੂਰੀ] = 0.0f;
        sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_ਦੂਰੀ);
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_ਦੂਰੀ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t ਦੂਰੀ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_ਦੂਰੀ] = ((ਦਸ਼ਮਲਵ) ਦੂਰੀ) / 65535.0f;
    sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_ਦੂਰੀ);
    ਜੇ (ਦੂਰੀ) {
        sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_tilt(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_XTILT] = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(xtilt));
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_YTILT] = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(ytilt));
    sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_button(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਪੂਰਨ sdlbutton;

    ਚੋਣ (button) {
    ਹਾਲਤ BTN_STYLUS:
        sdlbutton = 1;
        ਰੋਕੋ;
    ਹਾਲਤ BTN_STYLUS2:
        sdlbutton = 2;
        ਰੋਕੋ;
    ਹਾਲਤ BTN_STYLUS3:
        sdlbutton = 3;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->ਚੌਖਟਾ.buttons)));
    sdltool->ਚੌਖਟਾ.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_ਥੱਲੇ : WAYLAND_TABLET_TOOL_BUTTON_ਉੱਪਰ;
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_rotation(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਅਚਲ ਦਸ਼ਮਲਵ rotation = (ਦਸ਼ਮਲਵ)(wl_fixed_ਮੰਜ਼ਿਲ_double(degrees));
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_slider(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    sdltool->ਚੌਖਟਾ.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_wheel(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ਸਥਿਰ ਖਾਲੀ tablet_tool_handle_ਚੌਖਟਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_tool_v2 *tool, uint32_t ਸਮਾਂ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ਅੰਕੜੇ;
    ਅਚਲ SDL_PenID instance_id = sdltool->instance_id;
    ਜੇ (!instance_id) {
        ਵਾਪਸ;  // Not a pen we report on.
    }

    ਅਚਲ Uint64 timestamp = Wayland_Adjust_Event_Timestamp_ਅਧਾਰ(Wayland_EventTimestampMSToNS(ਸਮਾਂ));
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = sdltool->focus ? sdltool->focus->sdlwindow : ਨਿਰਾ;
    ਅਚਲ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ਜੇ (sdltool->ਚੌਖਟਾ.have_proximity && sdltool->ਚੌਖਟਾ.ਵਿੱਚ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, ਖਿੜਕੀ, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ਜੇ (sdltool->ਚੌਖਟਾ.have_motion && sdltool->ਚੌਖਟਾ.tool_state) {
        ਜੇ (sdltool->ਚੌਖਟਾ.tool_state == WAYLAND_TABLET_TOOL_STATE_ਥੱਲੇ) {
            SDL_SendPenMotion(timestamp, instance_id, ਖਿੜਕੀ, sdltool->ਚੌਖਟਾ.x, sdltool->ਚੌਖਟਾ.y);
            SDL_SendPenTouch(timestamp, instance_id, ਖਿੜਕੀ, is_eraser, true);
        } ਨਹੀਂਤਾਂ {
            SDL_SendPenTouch(timestamp, instance_id, ਖਿੜਕੀ, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, ਖਿੜਕੀ, sdltool->ਚੌਖਟਾ.x, sdltool->ਚੌਖਟਾ.y);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (sdltool->ਚੌਖਟਾ.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, ਖਿੜਕੀ, is_eraser, sdltool->ਚੌਖਟਾ.tool_state == WAYLAND_TABLET_TOOL_STATE_ਥੱਲੇ);
        }

        ਜੇ (sdltool->ਚੌਖਟਾ.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, ਖਿੜਕੀ, sdltool->ਚੌਖਟਾ.x, sdltool->ਚੌਖਟਾ.y);
        }
    }

    ਲਈ (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ਗਿਣਤੀ; i++) {
        ਜੇ (sdltool->ਚੌਖਟਾ.axes_ਸੈੱਟ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, ਖਿੜਕੀ, i, sdltool->ਚੌਖਟਾ.axes[i]);
        }
    }

    ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(sdltool->ਚੌਖਟਾ.buttons); i++) {
        ਅਚਲ ਪੂਰਨ state = sdltool->ਚੌਖਟਾ.buttons[i];
        ਜੇ (state) {
            SDL_SendPenButton(timestamp, instance_id, ਖਿੜਕੀ, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_ਥੱਲੇ);
        }
    }

    ਜੇ (sdltool->ਚੌਖਟਾ.have_proximity && !sdltool->ਚੌਖਟਾ.ਵਿੱਚ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, ਖਿੜਕੀ, false, false);
        sdltool->focus = ਨਿਰਾ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->ਚੌਖਟਾ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_ਪੂਰਾ,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_ਵਿੱਚ,
    tablet_tool_handle_proximity_ਬਾਹਰਲਾ,
    tablet_tool_handle_ਥੱਲੇ,
    tablet_tool_handle_ਉੱਪਰ,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_ਦੂਰੀ,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_ਚੌਖਟਾ
};


ਸਥਿਰ ਖਾਲੀ tablet_seat_handle_tablet_added(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ਬਣਤਰ zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ਸਥਿਰ ਖਾਲੀ tablet_seat_handle_tool_added(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ਬਣਤਰ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ਅੰਕੜੇ;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, ਆਕਾਰ(*sdltool));

    ਜੇ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.ਅੰਕ_buttons = -1;

        ਜੇ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ਪਾਓ(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_ਜੋੜੋ_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ਸਥਿਰ ਖਾਲੀ tablet_seat_handle_pad_added(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ਬਣਤਰ zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ਸਥਿਰ ਖਾਲੀ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_ਜੋੜੋ_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

ਖਾਲੀ Wayland_DisplayInitTabletManager(SDL_Video_ਅੰਕੜੇ *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_remove_all_pens_callback(SDL_PenID instance_id, ਖਾਲੀ *handle, ਖਾਲੀ *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_ਥੱਲੇ)
{
    ਜੇ (!shutting_ਥੱਲੇ) {
        SDL_WaylandPenTool *tool, *ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ (tool, ਆਰਜ਼ੀ, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ਨਹੀਂਤਾਂ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ਨਿਰਾ);
    }

    ਜੇ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ਨਿਰਾ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

ਖਾਲੀ Wayland_DisplayCreateSeat(SDL_Video_ਅੰਕੜੇ *display, ਬਣਤਰ wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, ਆਕਾਰ(SDL_WaylandSeat));
    ਜੇ (!seat) {
        ਵਾਪਸ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ਪਾਓ(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_ਅੰਕੜੇ_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_ਪਾਠ_ਨਿਵੇਸ਼(seat);

    wl_seat_ਸੈੱਟ_user_ਅੰਕੜੇ(seat->wl_seat, seat);
    wl_seat_ਜੋੜੋ_listener(seat->wl_seat, &seat_listener, seat);

    ਜੇ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ਖਾਲੀ Wayland_Display_Remove_ਖਿੜਕੀ_References_From_Seats(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ਜੇ (seat->keyboard.focus == ਖਿੜਕੀ) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, ਖਿੜਕੀ->surface);
        }

        ਜੇ (seat->ਸੂਚਕ_2.focus == ਖਿੜਕੀ) {
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = seat->ਸੂਚਕ_2.focus->surface;
            ਸੂਚਕ_dispatch_leave(seat, true);
            seat->ਸੂਚਕ_2.pending_ਚੌਖਟਾ.leave_surface = ਨਿਰਾ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_ਬਿੰਦੂ *tp, *ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ (tp, ਆਰਜ਼ੀ, &seat->touch.points, link) {
            ਜੇ (tp->surface == ਖਿੜਕੀ->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ਜੇ (tool->focus == ਖਿੜਕੀ) {
                tool->focus = ਨਿਰਾ;
                Wayland_TabletToolUpdateCursor(tool);
                ਜੇ (tool->instance_id) {
                    SDL_RemovePenDevice(0, ਖਿੜਕੀ->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_ਅੰਕੜੇ *drop, *drop_ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ (drop, drop_ਆਰਜ਼ੀ, &seat->ਅੰਕੜੇ_device->pending_drops, link) {
            ਜੇ (drop->dnd_ਖਿੜਕੀ == ਖਿੜਕੀ->sdlwindow) {
                Wayland_ਕੰਮ_Thread_Cancel_ਕੰਮ(display->ਕੰਮ_thread_context, drop->id);

                ਜੇ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_ਅੰਕੜੇ_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

ਖਾਲੀ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ਥੱਲੇ)
{
    ਜੇ (!seat) {
        ਵਾਪਸ;
    }

    SDL_free(seat->name);

    ਜੇ (seat->ਅੰਕੜੇ_device) {
        ਜੇ (seat->ਅੰਕੜੇ_device->selection_offer) {
            Wayland_ਅੰਕੜੇ_Offer_Destroy(seat->ਅੰਕੜੇ_device->selection_offer);
        }
        ਜੇ (seat->ਅੰਕੜੇ_device->selection_ਸਰੋਤ) {
            Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(seat->ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
        }
        ਜੇ (seat->ਅੰਕੜੇ_device->drag_offer) {
            Wayland_ਅੰਕੜੇ_Offer_Destroy(seat->ਅੰਕੜੇ_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_ਅੰਕੜੇ *drop, *drop_ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ (drop, drop_ਆਰਜ਼ੀ, &seat->ਅੰਕੜੇ_device->pending_drops, link) {
            Wayland_ਕੰਮ_Thread_Cancel_ਕੰਮ(seat->display->ਕੰਮ_thread_context, drop->id);

            ਜੇ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_ਅੰਕੜੇ_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ਜੇ (seat->ਅੰਕੜੇ_device->ਅੰਕੜੇ_device) {
            ਜੇ (wl_ਅੰਕੜੇ_device_get_ਸੰਸਕਰਣ(seat->ਅੰਕੜੇ_device->ਅੰਕੜੇ_device) >= WL_ਅੰਕੜੇ_DEVICE_RELEASE_SINCE_ਸੰਸਕਰਣ) {
                wl_ਅੰਕੜੇ_device_release(seat->ਅੰਕੜੇ_device->ਅੰਕੜੇ_device);
            } ਨਹੀਂਤਾਂ {
                wl_ਅੰਕੜੇ_device_destroy(seat->ਅੰਕੜੇ_device->ਅੰਕੜੇ_device);
            }
        }
        SDL_free(seat->ਅੰਕੜੇ_device->id_str);
        SDL_free(seat->ਅੰਕੜੇ_device);
    }

    ਜੇ (seat->primary_selection_device) {
        ਜੇ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ਜੇ (seat->primary_selection_device->selection_ਸਰੋਤ) {
            Wayland_Primary_Selection_ਸਰੋਤ_Destroy(seat->primary_selection_device->selection_ਸਰੋਤ);
        }
        ਜੇ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ਜੇ (seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼) {
        zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3_destroy(seat->ਪਾਠ_ਨਿਵੇਸ਼.zwp_ਪਾਠ_ਨਿਵੇਸ਼);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_ਸੂਚਕ(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_ਥੱਲੇ);

    ਜੇ (wl_seat_get_ਸੰਸਕਰਣ(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_ਸੰਸਕਰਣ) {
        wl_seat_release(seat->wl_seat);
    } ਨਹੀਂਤਾਂ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ਸਥਿਰ ਖਾਲੀ Wayland_Seat_Update_Relative_ਸੂਚਕ(SDL_WaylandSeat *seat)
{
    ਜੇ (seat->display->relative_ਸੂਚਕ_manager) {
        bool relative_focus = false;

        ਜੇ (seat->ਸੂਚਕ_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ਜੇ (seat->ਸੂਚਕ_2.focus->sdlwindow->flags & SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ) {
                ਜੇ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->ਸੂਚਕ_2.focus;
                } ਨਹੀਂਤਾਂ {
                    relative_focus = seat->ਸੂਚਕ_2.focus->keyboard_focus_ਗਿਣਤੀ != 0;
                }
            } ਨਹੀਂਤਾਂ {
                relative_focus = SDL_GetMouse()->warp_emulation_ਸਰਗਰਮ;
            }
        }

        ਜੇ (relative_focus) {
            ਜੇ (!seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
                seat->ਸੂਚਕ_2.relative_ਸੂਚਕ = zwp_relative_ਸੂਚਕ_manager_v1_get_relative_ਸੂਚਕ(seat->display->relative_ਸੂਚਕ_manager, seat->ਸੂਚਕ_2.wl_ਸੂਚਕ);
                zwp_relative_ਸੂਚਕ_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.relative_ਸੂਚਕ, &relative_ਸੂਚਕ_listener, seat);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
            zwp_relative_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.relative_ਸੂਚਕ);
            seat->ਸੂਚਕ_2.relative_ਸੂਚਕ = ਨਿਰਾ;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_ਅੰਕੜੇ *display = seat->display;

    ਜੇ (display->ਕੁੰਜੀ_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ਜੇ (seat->keyboard.ਕੁੰਜੀ_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ਕੁੰਜੀ_inhibitor);
            seat->keyboard.ਕੁੰਜੀ_inhibitor = ਨਿਰਾ;
        }

        ਜੇ (seat->keyboard.wl_keyboard) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *w = seat->keyboard.focus;
            ਜੇ (w) {
                SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED) {
                    seat->keyboard.ਕੁੰਜੀ_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ਕੁੰਜੀ_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

ਖਾਲੀ Wayland_Seat_Update_ਸੂਚਕ_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_ਅੰਕੜੇ *display = seat->display;
    Wayland_Seat_Update_Relative_ਸੂਚਕ(seat);

    ਜੇ (display->ਸੂਚਕ_constraints) {
        ਜੇ (seat->ਸੂਚਕ_2.locked_ਸੂਚਕ && !seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
            zwp_locked_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.locked_ਸੂਚਕ);
            seat->ਸੂਚਕ_2.locked_ਸੂਚਕ = ਨਿਰਾ;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
        }

        ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ਜੇ (seat->ਸੂਚਕ_2.relative_ਸੂਚਕ) {
                ਜੇ (!seat->ਸੂਚਕ_2.locked_ਸੂਚਕ) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ਜੇ (seat->ਸੂਚਕ_2.confined_ਸੂਚਕ) {
                        zwp_confined_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.confined_ਸੂਚਕ);
                        seat->ਸੂਚਕ_2.confined_ਸੂਚਕ = ਨਿਰਾ;
                    }

                    seat->ਸੂਚਕ_2.locked_ਸੂਚਕ = zwp_ਸੂਚਕ_constraints_v1_ਤਾਲਾ_ਸੂਚਕ(display->ਸੂਚਕ_constraints,
                                                                                           seat->ਸੂਚਕ_2.focus->surface,
                                                                                           seat->ਸੂਚਕ_2.wl_ਸੂਚਕ, ਨਿਰਾ,
                                                                                           ZWP_ਸੂਚਕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_ਸੂਚਕ_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.locked_ਸੂਚਕ, &locked_ਸੂਚਕ_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ਵਾਪਸ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ਜੇ (seat->ਸੂਚਕ_2.confined_ਸੂਚਕ) {
                zwp_confined_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.confined_ਸੂਚਕ);
                seat->ਸੂਚਕ_2.confined_ਸੂਚਕ = ਨਿਰਾ;
            }

            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *w = seat->ਸੂਚਕ_2.focus;
            ਜੇ (!w) {
                ਵਾਪਸ;
            }

            SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) ||
                (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED) && SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->mouse_rect))) {
                ਵਾਪਸ;
            }

            ਬਣਤਰ wl_region *confine_rect = ਨਿਰਾ;
            ਜੇ (!SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(ਖਿੜਕੀ, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_ਜੋੜੋ(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                ਜੇ (!SDL_ਬਿੰਦੂ_ਵਿੱਚ_Rect(&seat->ਸੂਚਕ_2.ਆਖਰੀ_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    ਪੂਰਨ closest_x = seat->ਸੂਚਕ_2.ਆਖਰੀ_motion.x;
                    ਪੂਰਨ closest_y = seat->ਸੂਚਕ_2.ਆਖਰੀ_motion.y;

                    ਜੇ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ਨਹੀਂਤਾਂ ਜੇ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ਜੇ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ਨਹੀਂਤਾਂ ਜੇ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ਜੇ (confine_rect || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED)) {
                ਜੇ (ਖਿੜਕੀ->mouse_rect.w != 1 && ਖਿੜਕੀ->mouse_rect.h != 1) {
                    seat->ਸੂਚਕ_2.confined_ਸੂਚਕ =
                        zwp_ਸੂਚਕ_constraints_v1_confine_ਸੂਚਕ(display->ਸੂਚਕ_constraints,
                                                                   w->surface,
                                                                   seat->ਸੂਚਕ_2.wl_ਸੂਚਕ,
                                                                   confine_rect,
                                                                   ZWP_ਸੂਚਕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_ਸੂਚਕ_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.confined_ਸੂਚਕ,
                                                         &confined_ਸੂਚਕ_listener,
                                                         seat);
                } ਨਹੀਂਤਾਂ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->ਸੂਚਕ_2.locked_ਸੂਚਕ =
                        zwp_ਸੂਚਕ_constraints_v1_ਤਾਲਾ_ਸੂਚਕ(display->ਸੂਚਕ_constraints,
                                                                w->surface,
                                                                seat->ਸੂਚਕ_2.wl_ਸੂਚਕ,
                                                                ਨਿਰਾ,
                                                                ZWP_ਸੂਚਕ_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_ਸੂਚਕ_v1_ਜੋੜੋ_listener(seat->ਸੂਚਕ_2.locked_ਸੂਚਕ,
                                                       &locked_ਸੂਚਕ_listener,
                                                       seat);
                }
                ਜੇ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

ਖਾਲੀ Wayland_Display_Update_ਸੂਚਕ_Grabs(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ਜੇ (!ਖਿੜਕੀ || seat->ਸੂਚਕ_2.focus == ਖਿੜਕੀ) {
            Wayland_Seat_Update_ਸੂਚਕ_Grab(seat);
        }
    }
}

ਖਾਲੀ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ਜੇ (!ਖਿੜਕੀ || seat->keyboard.focus == ਖਿੜਕੀ) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

ਖਾਲੀ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ਜੇ (serial > seat->ਆਖਰੀ_implicit_grab_serial) {
        seat->ਆਖਰੀ_implicit_grab_serial = serial;
        seat->display->ਆਖਰੀ_implicit_grab_seat = seat;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
