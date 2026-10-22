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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

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

#ifdef HAVE_LIBDECOR_H
#ಅನ್ತರ್ಭಾವ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ <linux/input.h>
#ಅನ್ಯಥಾ
#define BTN_ಎಡ    (0x110)
#define BTN_ಬಲ   (0x111)
#define BTN_ಮಧ್ಯ  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keysym_to_scancode_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/imKStoUCS.h"
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <xkbcommon/xkbcommon-compose.h>
#ಅನ್ತರ್ಭಾವ <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#define WAYLAND_WHEEL_AXIS_UNIT 10

#ifndef XKB_MOD_NAME_MOD3
#define XKB_MOD_NAME_MOD3 "Mod3"
#endif

#ifndef XKB_MOD_NAME_MOD5
#define XKB_MOD_NAME_MOD5 "Mod5"
#endif

// Keyboard and mouse names to match XWayland
#define WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#define WAYLAND_DEFAULT_POINTER_NAME "Virtual core pointer"
#define WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#define WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_TO_NS(10)

// Timer rollover detection thresholds
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ (WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ * 15U)

// Scoped function declarations
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    Uint32 ಕೀಲಿ;
    SDL_Scancode scancode;
} Wayland_Reserved_ಕೀಲಿ;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ಸಂರಚನಾ wl_surface *surface;

    ಸಂರಚನಾ wl_list link;
} SDL_WaylandTouchPoint;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ಸಂರಚನಾ wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(ಪರಿಮಾಣ(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ಸೇರಿಸು(&seat->touch.points, &tp->link);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    ಯದಿ (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        ಯದಿ (window_data) {
            ಧ್ರುವ ಭಿನ್ನ x = (ಭಿನ್ನ)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ಧ್ರುವ ಭಿನ್ನ y = (ಭಿನ್ನ)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_ಎಣಿಕೆ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ಯದಿ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ಎಣಿಕೆ &&
                !window_data->pointer_focus_ಎಣಿಕೆ && !window_data->active_touch_ಎಣಿಕೆ) {
                SDL_SetMouseFocus(ರಿಕ್ತ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ಸಂರಚನಾ wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ಯದಿ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ಯದಿ (surface) {
                *surface = tp->surface;
            }
            ಭಙ್ಗ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ಸಂರಚನಾ wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ಯದಿ (tp->id == id) {
            ಯದಿ (fx) {
                *fx = tp->fx;
            }
            ಯದಿ (fy) {
                *fy = tp->fy;
            }
            ಯದಿ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ಭಙ್ಗ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

ಸ್ಥಿರ Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    ಸ್ಥಿರ Uint64 timestamp_offset = 0;
    ಧ್ರುವ Uint64 now = SDL_GetTicksNS();

    ಯದಿ (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    ಯದಿ (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ಪ್ರತ್ಯಾಗಮ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ಸ್ಥಿರ Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ಸ್ಥಿರ Uint64 timestamp_offset = 0;
    ಸ್ಥಿರ Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    ಯದಿ (wl_timestamp_ms >= last) {
        ಯದಿ (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } ಅನ್ಯಥಾ {
            last = wl_timestamp_ms;
        }
    } ಅನ್ಯಥಾ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ಯದಿ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_ಕೆಳಗಿನ && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_ಮೇಲಿನ) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    ಪ್ರತ್ಯಾಗಮ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ಸ್ಥಿರ Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಧ್ರುವ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಪ್ರತ್ಯಾಗಮ Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ಸ್ಥಿರ Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಧ್ರುವ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಪ್ರತ್ಯಾಗಮ Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ಧ್ರುವ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ಪ್ರತ್ಯಾಗಮ Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಒಳಹರಿವು_timestamp_listener(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_v1 *zwp_ಒಳಹರಿವು_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_v1_listener timestamp_listener = {
    ಒಳಹರಿವು_timestamp_listener
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Register_ಒಳಹರಿವು_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->display->ಒಳಹರಿವು_timestamps_manager) {
        ಯದಿ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ಒಳಹರಿವು_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ಯದಿ (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_pointer_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->pointer.wl_pointer);
            zwp_ಒಳಹರಿವು_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        ಯದಿ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ಒಳಹರಿವು_timestamps_manager_v1_get_touch_timestamps(seat->display->ಒಳಹರಿವು_timestamps_manager, seat->touch.wl_touch);
            zwp_ಒಳಹರಿವು_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Init_ಒಳಹರಿವು_Timestamp_Manager(SDL_VideoData *display)
{
    ಯದಿ (display->ಒಳಹರಿವು_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_ಒಳಹರಿವು_Timestamp_Listeners(seat);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_begin(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, ಸಂರಚನಾ wl_surface *surface, uint32_t fingers)
{
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    ಯದಿ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ಧ್ರುವ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_update(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ಯದಿ (seat->pointer.gesture_focus) {
        ಧ್ರುವ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ಧ್ರುವ ಭಿನ್ನ s = (ಭಿನ್ನ)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_pinch_end(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ಯದಿ (seat->pointer.gesture_focus) {
        ಧ್ರುವ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->display->zwp_pointer_gestures) {
        ಯದಿ (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->display->cursor_shape_manager) {
        ಯದಿ (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ಯದಿ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ಧ್ರುವ bool send_event = !seat->display->initializing;

    ಯದಿ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ಸ್ಥಿರ ಶೂನ್ಯ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ಯಾವತ್ (elapsed >= repeat_info->next_repeat_ns) {
        ಯದಿ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ಧ್ರುವ Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->ಕೀಲಿ, repeat_info->scancode, true);
        }
        ಯದಿ (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ಕೀಲಿ, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ಧ್ರುವ ವರ್ಣ *text)
{
    ಯದಿ (!repeat_info->repeat_rate) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ಕೀಲಿ = ಕೀಲಿ;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ಯದಿ (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } ಅನ್ಯಥಾ {
        repeat_info->text[0] = '\0';
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ sync_done_handler(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ಸ್ಥಿರ ಸಂರಚನಾ wl_callback_listener sync_listener = {
    sync_done_handler
};

ಶೂನ್ಯ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ಸಂರಚನಾ wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, ರಿಕ್ತ);
    WAYLAND_wl_display_flush(d->display);
}

ಪೂರ್ಣಾಙ್ಕ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ಪೂರ್ಣಾಙ್ಕ ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ಯದಿ (!d->text_ಒಳಹರಿವು_manager && keyboard_focus && SDL_Text_ಒಳಹರಿವು_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ಯದಿ (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ಯದಿ (seat->keyboard.repeat.ಕೀಲಿ) {
            ಧ್ರುವ Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ಧ್ರುವ Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            ಯದಿ (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    ಯದಿ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ಯದಿ (timeoutNS > 0) {
            ಧ್ರುವ Uint64 now = SDL_GetTicksNS();
            ಧ್ರುವ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ಯದಿ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ಯದಿ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ಯದಿ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ಪ್ರತ್ಯಾಗಮ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ಯದಿ (timeoutNS > 0) {
            ಧ್ರುವ Uint64 now = SDL_GetTicksNS();
            ಧ್ರುವ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ಯದಿ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ಯದಿ (ret == 0) {
                ಪ್ರತ್ಯಾಗಮ poll_alarm_set ? 1 : 0;
            } ಅನ್ಯಥಾ {
                // Pump events on an interrupt or broken pipe to handle the error.
                ಪ್ರತ್ಯಾಗಮ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ಯದಿ (ret == -1) {
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ಪ್ರತ್ಯಾಗಮ 1;
}

ಶೂನ್ಯ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ display_fd = WAYLAND_wl_display_get_fd(d->display);
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ಯದಿ (!d->text_ಒಳಹರಿವು_manager && keyboard_focus && SDL_Text_ಒಳಹರಿವು_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    ಯದಿ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ಯದಿ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ಯದಿ (ret < 0) {
            ಗಚ್ಛ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ಯದಿ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ಯದಿ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            ಯದಿ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ಯದಿ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            ಗಚ್ಛ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ಯದಿ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ಯದಿ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ಅನ್ಯಥಾ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ಅನ್ಯಥಾ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ಯದಿ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ಯದಿ (seat->keyboard.repeat.ಕೀಲಿ) {
                Wayland_SeatSetKeymap(seat);

                ಧ್ರುವ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ಯದಿ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : ರಿಕ್ತ;

    ಯದಿ (window_data) {
        ದ್ವಿಗುಣ sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        ದ್ವಿಗುಣ sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        ಯದಿ (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (ದ್ವಿಗುಣ)window_data->mask.offset_x;
            sy += (ದ್ವಿಗುಣ)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        ಯದಿ (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (ಭಿನ್ನ)sx, (ಭಿನ್ನ)sy);
        } ಅನ್ಯಥಾ {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (ಭಿನ್ನ)sx, (ಭಿನ್ನ)sy);
        }

        seat->pointer.last_motion.x = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(sx);
        seat->pointer.last_motion.y = (ಪೂರ್ಣಾಙ್ಕ)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ಯದಿ (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ಯದಿ (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ವಿಕಲ್ಪ (rc) {
            ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPLEFT:
                ಯದಿ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_RESIZE_ಎಡ;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_RESIZE_ತುದಿ;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_ತುದಿ:
                ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPRIGHT:
                ಯದಿ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ) {
                    rc = SDL_HITTEST_RESIZE_ಬಲ;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_RESIZE_ತುದಿ;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_ಬಲ:
                ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ಯದಿ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ಬಲ;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOM:
                ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ಯದಿ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ಎಡ;
                } ಅನ್ಯಥಾ ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_HITTEST_RESIZE_ಎಡ:
                ಯದಿ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ಭಙ್ಗ;
            ಸ್ವಭಾವ:
                ಭಙ್ಗ;
            }

            ಯದಿ (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_motion(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ಧ್ರುವ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ಯದಿ (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } ಅನ್ಯಥಾ {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    ಯದಿ (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        ಪ್ರತ್ಯಾಗಮ;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_ಎಣಿಕೆ;
    SDL_SetMouseFocus(window->sdlwindow);

    // Send the initial position.
    pointer_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_SeatUpdatePointerGrab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_SeatUpdatePointerCursor(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_enter(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                 uint32_t serial, ಸಂರಚನಾ wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ಯದಿ (!surface) {
        // Enter event for a destroyed surface.
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.enter_surface = surface;
    seat->pointer.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->pointer.pending_frame.absolute.sx = sx_w;
    seat->pointer.pending_frame.absolute.sy = sy_w;

    ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    ಯದಿ (window) {
        ಯದಿ (seat->pointer.focus) {
            ಯದಿ (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = ರಿಕ್ತ;
                seat->pointer.focus_surface = ರಿಕ್ತ;
                ಪ್ರತಿ (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    ಯದಿ (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ಧ್ರುವ bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                ಯದಿ (!--window->pointer_focus_ಎಣಿಕೆ && had_focus && !window->active_touch_ಎಣಿಕೆ) {
                    SDL_SetMouseFocus(ರಿಕ್ತ);
                }

                ಯದಿ (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } ಅನ್ಯಥಾ ಯದಿ (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_leave(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                 uint32_t serial, ಸಂರಚನಾ wl_surface *surface)
{
    ಯದಿ (!surface) {
        // Leave event for a destroyed surface.
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

ಸ್ಥಿರ bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ಯದಿ (seat->pointer.locked_pointer) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    ಯದಿ (window->hit_test) {
        ಸ್ಥಿರ ಧ್ರುವ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_ತುದಿ_ಎಡ, XDG_TOPLEVEL_RESIZE_EDGE_ತುದಿ,
            XDG_TOPLEVEL_RESIZE_EDGE_ತುದಿ_ಬಲ, XDG_TOPLEVEL_RESIZE_EDGE_ಬಲ,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ಬಲ, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ಎಡ, XDG_TOPLEVEL_RESIZE_EDGE_ಎಡ
        };

#ifdef HAVE_LIBDECOR_H
        ಸ್ಥಿರ ಧ್ರುವ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_ತುದಿ_ಎಡ, LIBDECOR_RESIZE_EDGE_ತುದಿ,
            LIBDECOR_RESIZE_EDGE_ತುದಿ_ಬಲ, LIBDECOR_RESIZE_EDGE_ಬಲ,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ಬಲ, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ಎಡ, LIBDECOR_RESIZE_EDGE_ಎಡ
        };
#endif

        ವಿಕಲ್ಪ (window_data->hit_test_result) {
        ಪಕ್ಷ SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            ಯದಿ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ಯದಿ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } ಅನ್ಯಥಾ
#endif
                ಯದಿ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ಯದಿ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ಪ್ರತ್ಯಾಗಮ true;

        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPLEFT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ತುದಿ:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPRIGHT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಬಲ:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOM:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಎಡ:
#ifdef HAVE_LIBDECOR_H
            ಯದಿ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ಯದಿ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ಅನ್ಯಥಾ
#endif
                ಯದಿ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ಯದಿ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ಪ್ರತ್ಯಾಗಮ true;

        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    ಯದಿ (window) {
        bool ignore_click = false;

        ಯದಿ (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            ಯದಿ (sdl_button == SDL_BUTTON_ಎಡ && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                ಪ್ರತ್ಯಾಗಮ; // don't pass this event on to app.
            }
        } ಅನ್ಯಥಾ {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ಯದಿ (window->last_focus_event_time_ns) {
            ಯದಿ (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            window->last_focus_event_time_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        ಯದಿ (!seat->pointer.relative_pointer) {
            ಯದಿ (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } ಅನ್ಯಥಾ {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ಯದಿ (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        ಯದಿ (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_button(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    ವಿಕಲ್ಪ (button) {
    ಪಕ್ಷ BTN_ಎಡ:
        sdl_button = SDL_BUTTON_ಎಡ;
        ಭಙ್ಗ;
    ಪಕ್ಷ BTN_ಮಧ್ಯ:
        sdl_button = SDL_BUTTON_ಮಧ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ BTN_ಬಲ:
        sdl_button = SDL_BUTTON_ಬಲ;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ಭಙ್ಗ;
    }

    ಯದಿ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    ಯದಿ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        ಯದಿ (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } ಅನ್ಯಥಾ {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } ಅನ್ಯಥಾ {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    SDL_WindowData *window = seat->pointer.focus;
    ಧ್ರುವ ಗಣನಾ wl_pointer_axis a = axis;

    ಯದಿ (seat->pointer.focus) {
        ಭಿನ್ನ x, y;

        ವಿಕಲ್ಪ (a) {
        ಪಕ್ಷ WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
            ಭಙ್ಗ;
        ಪಕ್ಷ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
            y = 0;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_common(SDL_WaylandSeat *seat, ಗಣನಾ SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    ಧ್ರುವ ಗಣನಾ wl_pointer_axis a = axis;

    ಯದಿ (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        ವಿಕಲ್ಪ (a) {
        ಪಕ್ಷ WL_POINTER_AXIS_VERTICAL_SCROLL:
            ವಿಕಲ್ಪ (type) {
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ಯದಿ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ಯದಿ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ಯದಿ (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                }
                ಭಙ್ಗ;
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            ವಿಕಲ್ಪ (type) {
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ಯದಿ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ಯದಿ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ಯದಿ (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (ಭಿನ್ನ)wl_fixed_to_double(ಮೌಲ್ಯ);
                }
                ಭಙ್ಗ;
            }
            ಭಙ್ಗ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t ಮೌಲ್ಯ)
{
    SDL_WaylandSeat *seat = data;
    ಧ್ರುವ Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    ಯದಿ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, ಮೌಲ್ಯ);
    } ಅನ್ಯಥಾ {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, ಮೌಲ್ಯ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_relative_direction(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    ವಿಕಲ್ಪ (axis_relative_direction) {
    ಪಕ್ಷ WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        ಭಙ್ಗ;
    ಪಕ್ಷ WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    ಯದಿ (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ದ್ವಿಗುಣ dx;
        ದ್ವಿಗುಣ dy;
        ಯದಿ (mouse->ಒಳಹರಿವು_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } ಅನ್ಯಥಾ {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (ಭಿನ್ನ)dx, (ಭಿನ್ನ)dy);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    ಭಿನ್ನ x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    ವಿಕಲ್ಪ (seat->pointer.pending_frame.axis.x_axis_type) {
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        x = 0.0f;
        ಭಙ್ಗ;
    }

    ವಿಕಲ್ಪ (seat->pointer.pending_frame.axis.y_axis_type) {
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        y = 0.0f;
        ಭಙ್ಗ;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_frame(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    ಯದಿ (seat->pointer.pending_frame.enter_surface) {
        ಯದಿ (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            ಯದಿ (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = ರಿಕ್ತ;
                seat->pointer.pending_frame.leave_surface = ರಿಕ್ತ;
            } ಅನ್ಯಥಾ {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = ರಿಕ್ತ;
            }
        }

        ಯದಿ (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    ಯದಿ (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    ಯದಿ (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    ಪ್ರತಿ (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ಧ್ರುವ Uint32 mask = SDL_BUTTON_MASK(i);
        ಯದಿ (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        ಯದಿ (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    ಯದಿ (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    ಯದಿ (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_source(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_stop(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_discrete(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_axis_value120(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ಸ್ಥಿರ ಶೂನ್ಯ pointer_handle_warp(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_pointer_listener pointer_listener = {
    pointer_handle_enter,
    pointer_handle_leave,
    pointer_handle_motion,
    pointer_handle_button,
    pointer_handle_axis,
    pointer_handle_frame,                   // Version 5
    pointer_handle_axis_source,             // Version 5
    pointer_handle_axis_stop,               // Version 5
    pointer_handle_axis_discrete,           // Version 5
    pointer_handle_axis_value120,           // Version 8
    pointer_handle_axis_relative_direction, // Version 9
    pointer_handle_warp                     // Version 11
};

ಸ್ಥಿರ ಶೂನ್ಯ relative_pointer_handle_relative_motion(ಶೂನ್ಯ *data,
                                                    ಸಂರಚನಾ zwp_relative_pointer_v1 *pointer,
                                                    uint32_t time_hi,
                                                    uint32_t time_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = data;

    // Relative pointer event times are in microsecond granularity.
    seat->pointer.pending_frame.relative.dx = dx;
    seat->pointer.pending_frame.relative.dy = dy;
    seat->pointer.pending_frame.relative.dx_unaccel = dx_unaccel;
    seat->pointer.pending_frame.relative.dy_unaccel = dy_unaccel;
    seat->pointer.pending_frame.timestamp_ns = Wayland_AdjustEventTimestampBase(SDL_US_TO_NS(((Uint64)time_hi << 32) | (Uint64)time_lo));

    ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } ಅನ್ಯಥಾ {
        pointer_dispatch_relative_motion(seat);
    }
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

ಸ್ಥಿರ ಶೂನ್ಯ locked_pointer_locked(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ locked_pointer_unlocked(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

ಸ್ಥಿರ ಶೂನ್ಯ confined_pointer_confined(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ confined_pointer_unconfined(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_down(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ಸಂರಚನಾ wl_surface *surface,
                               ಪೂರ್ಣಾಙ್ಕ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    ಯದಿ (window_data && window_data->surface == surface) {
        ಭಿನ್ನ x, y;

        ಯದಿ (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } ಅನ್ಯಥಾ {
            x = (ಭಿನ್ನ)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        ಯದಿ (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } ಅನ್ಯಥಾ {
            y = (ಭಿನ್ನ)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_ಎಣಿಕೆ;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_up(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *touch, uint32_t serial, uint32_t timestamp, ಪೂರ್ಣಾಙ್ಕ id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    ಸಂರಚನಾ wl_surface *surface = ರಿಕ್ತ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ಯದಿ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ಯದಿ (window_data && window_data->surface == surface) {
            ಧ್ರುವ ಭಿನ್ನ x = (ಭಿನ್ನ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ಧ್ರುವ ಭಿನ್ನ y = (ಭಿನ್ನ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_ಎಣಿಕೆ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ಯದಿ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ಎಣಿಕೆ &&
                !window_data->pointer_focus_ಎಣಿಕೆ && !window_data->active_touch_ಎಣಿಕೆ) {
                SDL_SetMouseFocus(ರಿಕ್ತ);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_motion(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *touch, uint32_t timestamp, ಪೂರ್ಣಾಙ್ಕ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ಸಂರಚನಾ wl_surface *surface = ರಿಕ್ತ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ಯದಿ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ಯದಿ (window_data && window_data->surface == surface) {
            ಧ್ರುವ ಭಿನ್ನ x = (ಭಿನ್ನ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ಧ್ರುವ ಭಿನ್ನ y = (ಭಿನ್ನ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_frame(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *touch)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_cancel(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_shape(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ touch_handler_orientation(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ಯದಿ !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
ಸ್ಥಿರ size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ಕೀಲಿ, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    ಯದಿ (!masks_out || !masks_size) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    // Level 0 is always unmodified, so early out.
    ಯದಿ (level == 0) {
        *masks_out = 0;
        ಪ್ರತ್ಯಾಗಮ 1;
    }

    size_t mask_idx = 0;
    ಧ್ರುವ xkb_mod_mask_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.shift_mask,
        seat->keyboard.xkb.caps_mask,
        seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.caps_mask,
        seat->keyboard.xkb.level3_mask,
        seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.shift_mask,
        seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.caps_mask,
        seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.caps_mask,
        seat->keyboard.xkb.level5_mask,
        seat->keyboard.xkb.level5_mask | seat->keyboard.xkb.shift_mask,
        seat->keyboard.xkb.level5_mask | seat->keyboard.xkb.caps_mask,
        seat->keyboard.xkb.level5_mask | seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.caps_mask
    };
    ಧ್ರುವ xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    ಧ್ರುವ xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    ಪ್ರತಿ (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        ಯದಿ (WAYLAND_xkb_state_ಕೀಲಿ_get_level(seat->keyboard.xkb.state, ಕೀಲಿ, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            ಯದಿ (++mask_idx == masks_size) {
                ಭಙ್ಗ;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ mask_idx;
}
#endif

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_KeymapIterator(ಸಂರಚನಾ xkb_keymap *keymap, xkb_keycode_t ಕೀಲಿ, ಶೂನ್ಯ *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ಧ್ರುವ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ಧ್ರುವ xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ಯದಿ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ಕೀಲಿ - 8);
    }

    ಪ್ರತಿ (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++layout) {
        ಧ್ರುವ xkb_level_index_t ಅಂಕೆ_levels = WAYLAND_xkb_keymap_ಅಂಕೆ_levels_for_ಕೀಲಿ(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout);
        ಪ್ರತಿ (xkb_level_index_t level = 0; level < ಅಂಕೆ_levels; ++level) {
            ಯದಿ (WAYLAND_xkb_keymap_ಕೀಲಿ_get_syms_by_level(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ಕೀಲಿ_Sym(syms[0], ಕೀಲಿ);
                    ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
                        ಅನುವರ್ತ;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#ಯದಿ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ಧ್ರುವ size_t ಅಂಕೆ_masks = WAYLAND_xkb_keymap_ಕೀಲಿ_get_mods_for_level(seat->keyboard.xkb.keymap, ಕೀಲಿ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ಅನ್ಯಥಾ
                ಧ್ರುವ size_t ಅಂಕೆ_masks = xkb_legacy_get_mods_for_level(seat, ಕೀಲಿ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                ಪ್ರತಿ (size_t mask = 0; mask < ಅಂಕೆ_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ಯದಿ ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        ಅನುವರ್ತ;
                    }

                    ಧ್ರುವ SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_Code_From_ಕೀಲಿ_Sym(syms[0], ಕೀಲಿ, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ಯದಿ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        ಯದಿ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ಕೀಲಿ *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, ಪರಿಮಾಣ(Wayland_Reserved_ಕೀಲಿ));
                        ಯದಿ (res) {
                            res->scancode = scancode;
                            res->ಕೀಲಿ = ಕೀಲಿ - 8;
                        }
                    }

                    ಯದಿ (!keycode) {
                        ವಿಕಲ್ಪ (scancode) {
                        ಪಕ್ಷ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ಭಙ್ಗ;
                        ಪಕ್ಷ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ಭಙ್ಗ;
                        ಪಕ್ಷ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ಭಙ್ಗ;
                        ಪಕ್ಷ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ಭಙ್ಗ;
                        ಸ್ವಭಾವ:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            ಭಙ್ಗ;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_keymap(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *keyboard,
                                   uint32_t format, ಪೂರ್ಣಾಙ್ಕ fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    ವರ್ಣ *map_str;

    ಯದಿ (!data) {
        close(fd);
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ಪ್ರತ್ಯಾಗಮ;
    }

    map_str = mmap(ರಿಕ್ತ, size, PROT_READ, MAP_PRIVATE, fd, 0);
    ಯದಿ (map_str == MAP_FAILED) {
        close(fd);
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (seat->keyboard.xkb.keymap != ರಿಕ್ತ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ರಿಕ್ತ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    ಯದಿ (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Clear the old layouts.
    ಪ್ರತಿ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ರಿಕ್ತ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.ಅಂಕೆ_layouts = 0;

#ಯದಿ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.ಅಂಕೆ_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ಅಂಕೆ);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ಅನ್ಯಥಾ
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.ಅಂಕೆ_mask = 1 << GET_MOD_INDEX(ಅಂಕೆ_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    ಯದಿ (seat->keyboard.xkb.state != ರಿಕ್ತ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ರಿಕ್ತ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ಯದಿ (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ರಿಕ್ತ;
        ಪ್ರತ್ಯಾಗಮ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ರಿಕ್ತ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.ಅಂಕೆ_layouts = WAYLAND_xkb_keymap_ಅಂಕೆ_layouts(seat->keyboard.xkb.keymap);
    ಯದಿ (seat->keyboard.xkb.ಅಂಕೆ_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.ಅಂಕೆ_layouts, ಪರಿಮಾಣ(SDL_Keymap *));
        ಯದಿ (!seat->keyboard.sdl_keymap) {
            ಪ್ರತ್ಯಾಗಮ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        ಪ್ರತಿ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ಯದಿ (!seat->keyboard.sdl_keymap[i]) {
                ಪ್ರತಿ (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ರಿಕ್ತ;
                ಪ್ರತ್ಯಾಗಮ;
            }
        }

        WAYLAND_xkb_keymap_ಕೀಲಿ_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ಧ್ರುವ ವರ್ಣ *locale = SDL_getenv("LC_ALL");
    ಯದಿ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ಯದಿ (!locale) {
            locale = SDL_getenv("LANG");
            ಯದಿ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ಯದಿ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ಯದಿ (seat->keyboard.xkb.compose_table != ರಿಕ್ತ) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = ರಿಕ್ತ;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ಯದಿ (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            ಯದಿ (seat->keyboard.xkb.compose_state != ರಿಕ್ತ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ರಿಕ್ತ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ಯದಿ (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = ರಿಕ್ತ;
            }
        }
    } ಅನ್ಯಥಾ ಯದಿ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ಸ್ಥಿರ SDL_Scancode Wayland_Get_Scancode_For_ಕೀಲಿ(SDL_WaylandSeat *seat, Uint32 ಕೀಲಿ, ಧ್ರುವ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ಯದಿ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ಕೀಲಿ);

        // No table entry? Check the reserved list.
        ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ಕೀಲಿ *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ಯದಿ (i->ಕೀಲಿ == ಕೀಲಿ) {
                    ಪ್ರತ್ಯಾಗಮ i->scancode;
                }
            }
        }
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ xkb_keysym_t *keysym;
        ಯದಿ (WAYLAND_xkb_state_ಕೀಲಿ_get_syms(seat->keyboard.xkb.state, ಕೀಲಿ + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ಕೀಲಿ_Sym(keysym[0], ಕೀಲಿ + 8);
            ಯದಿ (syms) {
                *syms = keysym;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ scancode;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ಕೀಲಿ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ಯದಿ (!ಕೀಲಿ_pressed) {
        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } ಅನ್ಯಥಾ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ಅನ್ಯಥಾ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ಅನ್ಯಥಾ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ಅನ್ಯಥಾ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } ಅನ್ಯಥಾ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        ಯದಿ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            ಯದಿ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ಅನ್ಯಥಾ {
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
    ಧ್ರುವ xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        ಯದಿ (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } ಅನ್ಯಥಾ ಯದಿ (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        ಯದಿ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ಅನ್ಯಥಾ ಯದಿ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        ಯದಿ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ಅನ್ಯಥಾ ಯದಿ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        ಯದಿ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ಅನ್ಯಥಾ ಯದಿ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ಯದಿ (xkb_locked_modifiers & seat->keyboard.xkb.ಅಂಕೆ_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ಅಂಕೆ;
    } ಅನ್ಯಥಾ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ಅಂಕೆ;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Handle_Modifier_ಕೀಲಿಗಳು(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ಧ್ರುವ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ವಿಕಲ್ಪ (keycode) {
    ಪಕ್ಷ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ಅನ್ಯಥಾ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_enter(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *keyboard,
                                  uint32_t serial, ಸಂರಚನಾ wl_surface *surface,
                                  ಸಂರಚನಾ wl_array *ಕೀಲಿಗಳು)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *ಕೀಲಿ;

    ಯದಿ (!surface) {
        // Enter event for a destroyed surface.
        ಪ್ರತ್ಯಾಗಮ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ಯದಿ (!window) {
        // Not a surface owned by SDL.
        ಪ್ರತ್ಯಾಗಮ;
    }

    ++window->keyboard_focus_ಎಣಿಕೆ;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ಒಳಹರಿವು(seat);

#ifdef SDL_USE_IME
    ಯದಿ (!seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (ಕೀಲಿ, ಕೀಲಿಗಳು) {
        ಧ್ರುವ SDL_Scancode scancode = Wayland_Get_Scancode_For_ಕೀಲಿ(seat, *ಕೀಲಿ, ರಿಕ್ತ);
        ಯದಿ (scancode != SDL_SCANCODE_UNKNOWN) {
            ಧ್ರುವ SDL_Keycode keycode = SDL_Get_ಕೀಲಿ_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ವಿಕಲ್ಪ (keycode) {
            ಪಕ್ಷ SDLK_LSHIFT:
            ಪಕ್ಷ SDLK_RSHIFT:
            ಪಕ್ಷ SDLK_LCTRL:
            ಪಕ್ಷ SDLK_RCTRL:
            ಪಕ್ಷ SDLK_LALT:
            ಪಕ್ಷ SDLK_RALT:
            ಪಕ್ಷ SDLK_LGUI:
            ಪಕ್ಷ SDLK_RGUI:
            ಪಕ್ಷ SDLK_MODE:
            ಪಕ್ಷ SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_ಕೀಲಿಗಳು(seat, scancode, true);
                SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ಕೀಲಿ, scancode, true);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ:
                ಭಙ್ಗ;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_leave(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *keyboard,
                                  uint32_t serial, ಸಂರಚನಾ wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ಯದಿ (!surface) {
        // Leave event for a destroyed surface.
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ಯದಿ (!window) {
        // Not a surface owned by SDL.
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ಕೀಲಿ = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ಯಾವತ್ (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ಧ್ರುವ bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ರಿಕ್ತ;
    --window->keyboard_focus_ಎಣಿಕೆ;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ಯದಿ (!window->keyboard_focus_ಎಣಿಕೆ && had_focus) {
        SDL_SetKeyboardFocus(ರಿಕ್ತ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ಒಳಹರಿವು(seat);

#ifdef SDL_USE_IME
    ಯದಿ (!seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು && !window->keyboard_focus_ಎಣಿಕೆ) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ಯದಿ (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_ಎಣಿಕೆ && !window->active_touch_ಎಣಿಕೆ) {
        SDL_SetMouseFocus(ರಿಕ್ತ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, ರಿಕ್ತ);
}

ಸ್ಥಿರ bool keyboard_ಒಳಹರಿವು_get_text(ವರ್ಣ text[8], ಧ್ರುವ SDL_WaylandSeat *seat, uint32_t ಕೀಲಿ, bool down, bool *handled_by_ime)
{
    ಧ್ರುವ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ಯದಿ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // TODO: Can this happen?
    ಯದಿ (WAYLAND_xkb_state_ಕೀಲಿ_get_syms(seat->keyboard.xkb.state, ಕೀಲಿ + 8, &syms) != 1) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    ಯದಿ (SDL_IME_Process_ಕೀಲಿ_Event(sym, ಕೀಲಿ + 8, down)) {
        ಯದಿ (handled_by_ime) {
            *handled_by_ime = true;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }
#endif

    ಯದಿ (!down) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ವಿಕಲ್ಪ (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        ಪಕ್ಷ XKB_COMPOSE_COMPOSING:
            ಯದಿ (handled_by_ime) {
                *handled_by_ime = true;
            }
            ಪ್ರತ್ಯಾಗಮ true;
        ಪಕ್ಷ XKB_COMPOSE_CANCELLED:
        ಸ್ವಭಾವ:
            sym = XKB_ಕೀಲಿ_No_ಚಿಹ್ನೆ;
            ಭಙ್ಗ;
        ಪಕ್ಷ XKB_COMPOSE_NOTHING:
            ಭಙ್ಗ;
        ಪಕ್ಷ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ಭಙ್ಗ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_ಕೀಲಿ(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t ಕೀಲಿ,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    ಗಣನಾ wl_keyboard_ಕೀಲಿ_state state = state_w;
    ವರ್ಣ text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ಧ್ರುವ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ಯದಿ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ಯದಿ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ಕೀಲಿ_repeats(seat->keyboard.xkb.keymap, ಕೀಲಿ + 8)) {
            ಪ್ರತ್ಯಾಗಮ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    ಯದಿ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        ಯದಿ (keyboard_focus && SDL_Text_ಒಳಹರಿವು_Active(keyboard_focus)) {
            has_text = keyboard_ಒಳಹರಿವು_get_text(text, seat, ಕೀಲಿ, true, &handled_by_ime);
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (ಕೀಲಿ == seat->keyboard.repeat.ಕೀಲಿ) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ಧ್ರುವ Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ಕೀಲಿ = 0;
        }
        keyboard_ಒಳಹರಿವು_get_text(text, seat, ಕೀಲಿ, false, &handled_by_ime);
    }

    ಧ್ರುವ xkb_keysym_t *syms = ರಿಕ್ತ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ಕೀಲಿ(seat, ಕೀಲಿ, &syms);
    Wayland_Handle_Modifier_ಕೀಲಿಗಳು(seat, scancode, state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ಧ್ರುವ SDL_Keycode keycode = (SDL_Keycode)SDL_ಕೀಲಿ_Sym_To_Ucs4(syms[0]);
        ಯದಿ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ಯದಿ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ಕೀಲಿ_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ಕೀಲಿ, scancode, state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED);

    ಯದಿ (state == WL_KEYBOARD_ಕೀಲಿ_STATE_PRESSED) {
        ಯದಿ (handled_by_ime) {
            has_text = false;
        }
        ಯದಿ (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        ಯದಿ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ಕೀಲಿ_repeats(seat->keyboard.xkb.keymap, ಕೀಲಿ + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, ಕೀಲಿ, time, timestamp_ns, scancode, has_text ? text : ರಿಕ್ತ);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_modifiers(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    ಧ್ರುವ uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ಯದಿ (!seat->keyboard.xkb.state) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    ಯದಿ (seat->keyboard.repeat.ಕೀಲಿ) {
        ವರ್ಣ text[8];

        ಯದಿ (keyboard_ಒಳಹರಿವು_get_text(text, seat, seat->keyboard.repeat.ಕೀಲಿ, true, ರಿಕ್ತ)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    ಯದಿ (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        ಯದಿ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ keyboard_handle_repeat_info(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ಯದಿ (!rate) {
        seat->keyboard.repeat.ಕೀಲಿ = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ಕೀಲಿ,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    ಯದಿ (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ಯದಿ (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = ರಿಕ್ತ;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    ಯದಿ (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    ಯದಿ (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    ಯದಿ (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    ಯದಿ (seat->pointer.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    ಯದಿ (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    ಯದಿ (seat->pointer.wl_pointer) {
        ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } ಅನ್ಯಥಾ {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ಯದಿ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ಯದಿ (seat->keyboard.sdl_keymap) {
        ಯದಿ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ಅಂಕೆ_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        ಪ್ರತಿ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ಅಂಕೆ_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ರಿಕ್ತ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ಯದಿ (seat->keyboard.ಕೀಲಿ_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ಕೀಲಿ_inhibitor);
    }

    ಯದಿ (seat->keyboard.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ಯದಿ (seat->keyboard.wl_keyboard) {
        ಯದಿ (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ಅನ್ಯಥಾ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ಯದಿ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ಯದಿ (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    ಯದಿ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ಯದಿ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ಯದಿ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ಯದಿ (seat->touch.timestamps) {
        zwp_ಒಳಹರಿವು_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ಯದಿ (seat->touch.wl_touch) {
        ಯದಿ (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } ಅನ್ಯಥಾ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ಸ್ಥಿರ ಶೂನ್ಯ seat_handle_capabilities(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ವರ್ಣ name_fmt[256];

    ಯದಿ ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        ಯದಿ (seat->name) {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } ಅನ್ಯಥಾ {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } ಅನ್ಯಥಾ ಯದಿ (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    ಯದಿ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        ಯದಿ (seat->name) {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ಅನ್ಯಥಾ {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } ಅನ್ಯಥಾ ಯದಿ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ಯದಿ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        ಯದಿ (seat->name) {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ಅನ್ಯಥಾ {
            SDL_snprintf(name_fmt, ಪರಿಮಾಣ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } ಅನ್ಯಥಾ ಯದಿ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_ಒಳಹರಿವು_Timestamp_Listeners(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ seat_handle_name(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_seat *wl_seat, ಧ್ರುವ ವರ್ಣ *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ಯದಿ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ಸ್ಥಿರ ಶೂನ್ಯ data_offer_handle_offer(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_offer *wl_data_offer,
                                    ಧ್ರುವ ವರ್ಣ *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

ಸ್ಥಿರ ಶೂನ್ಯ data_offer_handle_source_actions(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

ಸ್ಥಿರ ಶೂನ್ಯ data_offer_handle_actions(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_offer_handle_offer(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ಧ್ರುವ ವರ್ಣ *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_data_offer(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device,
                                          ಸಂರಚನಾ wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, ಪರಿಮಾಣ(*data_offer));
    ಯದಿ (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id) : -1));
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_enter(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device,
                                     uint32_t serial, ಸಂರಚನಾ wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ಸಂರಚನಾ wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ರಿಕ್ತ;
    data_device->has_mime_file = false;
    data_device->text_mime_type = ರಿಕ್ತ;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ಯದಿ (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    ಯದಿ (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        ಯದಿ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        ಯದಿ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        ಯದಿ (!data_device->has_mime_file) {
            size_t mime_ಎಣಿಕೆ = 0;
            ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_ಎಣಿಕೆ);
            ಪ್ರತಿ (size_t i = 0; i < mime_ಎಣಿಕೆ; ++i) {
                ಯದಿ (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    ಭಙ್ಗ;
                }
            }
        }

        ಯದಿ (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            ಯದಿ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            ದ್ವಿಗುಣ dx = wl_fixed_to_double(x);
            ದ್ವಿಗುಣ dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            ಯದಿ (surface == window->mask.surface) {
                dx += (ದ್ವಿಗುಣ)window->mask.offset_x;
                dy += (ದ್ವಿಗುಣ)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (ಭಿನ್ನ)dx, (ಭಿನ್ನ)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } ಅನ್ಯಥಾ {
            // Decline the offer.
            wl_data_offer_accept(id, serial, ರಿಕ್ತ);
            ಯದಿ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } ಅನ್ಯಥಾ {
        data_device->dnd_window = ರಿಕ್ತ;
        data_device->dnd_surface = ರಿಕ್ತ;

        // Decline the offer.
        ಯದಿ (id) {
            wl_data_offer_accept(id, serial, ರಿಕ್ತ);
            ಯದಿ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_leave(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ಯದಿ (data_device->drag_offer) {
        ಯದಿ (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } ಅನ್ಯಥಾ {
            SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = ರಿಕ್ತ;
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_motion(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    ಯದಿ (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        ದ್ವಿಗುಣ dx = wl_fixed_to_double(x);
        ದ್ವಿಗುಣ dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        ಯದಿ (data_device->dnd_surface == window_data->mask.surface) {
            dx += (ದ್ವಿಗುಣ)window_data->mask.offset_x;
            dy += (ದ್ವಿಗುಣ)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (ಭಿನ್ನ)dx, (ಭಿನ್ನ)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ drop_cleanup_handler(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ drop_dispatch_handler(ಶೂನ್ಯ *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    ಯದಿ (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        ಯದಿ (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            ಶೂನ್ಯ *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            ಯದಿ (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ಯದಿ (dbus) {
                    ಪೂರ್ಣಾಙ್ಕ path_ಎಣಿಕೆ = 0;
                    ವರ್ಣ **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_ಎಣಿಕೆ);
                    // If dropped files contain a directory the list is empty
                    ಯದಿ (paths && path_ಎಣಿಕೆ > 0) {
                        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < path_ಎಣಿಕೆ; i++) {
                            SDL_SendDropFile(drop->dnd_window, ರಿಕ್ತ, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(buffer);
            }
        }
#endif
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        ಯದಿ (!drop_handled) {
            ಯದಿ (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                ಶೂನ್ಯ *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                ಯದಿ (buffer) {
                    ವರ್ಣ *saveptr = ರಿಕ್ತ;
                    ವರ್ಣ *token = SDL_strtok_r((ವರ್ಣ *)buffer, "\r\n", &saveptr);
                    ಯಾವತ್ (token) {
                        ಯದಿ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, ರಿಕ್ತ, token);
                        }
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } ಅನ್ಯಥಾ ಯದಿ (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                ಶೂನ್ಯ *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                ಯದಿ (buffer) {
                    ವರ್ಣ *saveptr = ರಿಕ್ತ;
                    ವರ್ಣ *token = SDL_strtok_r((ವರ್ಣ *)buffer, "\r\n", &saveptr);
                    ಯಾವತ್ (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(ರಿಕ್ತ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        ಯದಿ (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = ರಿಕ್ತ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_drop(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ಯದಿ (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_DropData));
        ಯದಿ (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_ಸೇರಿಸು(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } ಅನ್ಯಥಾ {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } ಅನ್ಯಥಾ {
        SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ data_device_handle_selection(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_device *wl_data_device,
                                         ಸಂರಚನಾ wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = ರಿಕ್ತ;

    ಯದಿ (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_device_handle_offer(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ಸಂರಚನಾ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, ಪರಿಮಾಣ(*primary_selection_offer));
    ಯದಿ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id) : -1));
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_device_handle_selection(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ಸಂರಚನಾ zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = ರಿಕ್ತ;

    ಯದಿ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    ಯದಿ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ಸಂರಚನಾ wl_proxy *)id) : -1));
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_enter(ಶೂನ್ಯ *data,
                             ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                             ಸಂರಚನಾ wl_surface *surface)
{
    // No-op
}

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_leave(ಶೂನ್ಯ *data,
                             ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                             ಸಂರಚನಾ wl_surface *surface)
{
    // No-op
}

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_preedit_string(ಶೂನ್ಯ *data,
                                      ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                                      ಧ್ರುವ ವರ್ಣ *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_ಒಳಹರಿವು.has_preedit = true;
    ಯದಿ (text) {
        ಪೂರ್ಣಾಙ್ಕ cursor_begin_utf8 = cursor_begin >= 0 ? (ಪೂರ್ಣಾಙ್ಕ)SDL_utf8strnlen(text, cursor_begin) : -1;
        ಪೂರ್ಣಾಙ್ಕ cursor_end_utf8 = cursor_end >= 0 ? (ಪೂರ್ಣಾಙ್ಕ)SDL_utf8strnlen(text, cursor_end) : -1;
        ಪೂರ್ಣಾಙ್ಕ cursor_size_utf8;
        ಯದಿ (cursor_end_utf8 >= 0) {
            ಯದಿ (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } ಅನ್ಯಥಾ {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } ಅನ್ಯಥಾ {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } ಅನ್ಯಥಾ {
        SDL_SendEditingText("", 0, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_commit_string(ಶೂನ್ಯ *data,
                                     ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                                     ಧ್ರುವ ವರ್ಣ *text)
{
    SDL_SendKeyboardText(text);
}

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_delete_surrounding_text(ಶೂನ್ಯ *data,
                                               ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

ಸ್ಥಿರ ಶೂನ್ಯ text_ಒಳಹರಿವು_done(ಶೂನ್ಯ *data,
                            ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ಯದಿ (!seat->text_ಒಳಹರಿವು.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_ಒಳಹರಿವು.has_preedit = false;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3_listener text_ಒಳಹರಿವು_listener = {
    text_ಒಳಹರಿವು_enter,
    text_ಒಳಹರಿವು_leave,
    text_ಒಳಹರಿವು_preedit_string,
    text_ಒಳಹರಿವು_commit_string,
    text_ಒಳಹರಿವು_delete_surrounding_text,
    text_ಒಳಹರಿವು_done
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    ಯದಿ (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ಯದಿ (dbus) {
            ಧ್ರುವ ವರ್ಣ *id = dbus->bus_get_unique_name(dbus->session_conn);
            ಯದಿ (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    ಯದಿ (!data_device->id_str)
#endif
    {
        ವರ್ಣ id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, ಪರಿಮಾಣ(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    ಯದಿ (!seat->display->data_device_manager) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, ಪರಿಮಾಣ(*data_device));
    ಯದಿ (!data_device) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    ಯದಿ (!data_device->data_device) {
        SDL_free(data_device);
        ಪ್ರತ್ಯಾಗಮ;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

ಶೂನ್ಯ Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ಯದಿ (!seat->display->primary_selection_device_manager) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, ಪರಿಮಾಣ(*primary_selection_device));
    ಯದಿ (!primary_selection_device) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ಯದಿ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ಅನ್ಯಥಾ {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

ಶೂನ್ಯ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Seat_Create_Text_ಒಳಹರಿವು(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->display->text_ಒಳಹರಿವು_manager) {
        seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು = zwp_text_ಒಳಹರಿವು_manager_v3_get_text_ಒಳಹರಿವು(seat->display->text_ಒಳಹರಿವು_manager, seat->wl_seat);

        ಯದಿ (seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು) {
            zwp_text_ಒಳಹರಿವು_v3_set_user_data(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು, seat);
            zwp_text_ಒಳಹರಿವು_v3_add_listener(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು,
                                           &text_ಒಳಹರಿವು_listener, seat);
        }
    }
}

ಶೂನ್ಯ Wayland_Display_Init_Text_ಒಳಹರಿವು_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_ಒಳಹರಿವು(seat);
    }
}

// Pen/Tablet support...
ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_type(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ವಿಕಲ್ಪ (type) {
        #define CASE(typ) ಪಕ್ಷ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ಪ್ರತ್ಯಾಗಮ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        ಸ್ವಭಾವ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_hardware_serial(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_hardware_id_wacom(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_capability(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ವಿಕಲ್ಪ (capability) {
        #define CASE(wltyp,sdltyp) ಪಕ್ಷ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ಪ್ರತ್ಯಾಗಮ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        ಸ್ವಭಾವ: ಭಙ್ಗ;  // unsupported here.
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_done(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ಯದಿ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ರಿಕ್ತ;
        sdltool->instance_id = SDL_AddPenDevice(0, ರಿಕ್ತ, window, &sdltool->info, sdltool, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_removed(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ಯದಿ (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ರಿಕ್ತ;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_proximity_in(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t serial, ಸಂರಚನಾ zwp_tablet_v2 *tablet, ಸಂರಚನಾ wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ರಿಕ್ತ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ರಿಕ್ತ;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_proximity_out(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_down(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_up(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_motion(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    ಯದಿ (windowdata) {
        sdltool->frame.x = (ಭಿನ್ನ)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (ಭಿನ್ನ)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_pressure(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((ಭಿನ್ನ) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    ಯದಿ (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_distance(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((ಭಿನ್ನ) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    ಯದಿ (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_tilt(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (ಭಿನ್ನ)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (ಭಿನ್ನ)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_button(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ಪೂರ್ಣಾಙ್ಕ sdlbutton;

    ವಿಕಲ್ಪ (button) {
    ಪಕ್ಷ BTN_STYLUS:
        sdlbutton = 1;
        ಭಙ್ಗ;
    ಪಕ್ಷ BTN_STYLUS2:
        sdlbutton = 2;
        ಭಙ್ಗ;
    ಪಕ್ಷ BTN_STYLUS3:
        sdlbutton = 3;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_rotation(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ಧ್ರುವ ಭಿನ್ನ rotation = (ಭಿನ್ನ)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_slider(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_wheel(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_tool_handle_frame(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ಧ್ರುವ SDL_PenID instance_id = sdltool->instance_id;
    ಯದಿ (!instance_id) {
        ಪ್ರತ್ಯಾಗಮ;  // Not a pen we report on.
    }

    ಧ್ರುವ Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ರಿಕ್ತ;
    ಧ್ರುವ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ಯದಿ (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ಯದಿ (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        ಯದಿ (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } ಅನ್ಯಥಾ {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        ಯದಿ (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    ಪ್ರತಿ (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ಎಣಿಕೆ; i++) {
        ಯದಿ (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ state = sdltool->frame.buttons[i];
        ಯದಿ (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    ಯದಿ (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = ರಿಕ್ತ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_done,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_in,
    tablet_tool_handle_proximity_out,
    tablet_tool_handle_down,
    tablet_tool_handle_up,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_distance,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_frame
};


ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_tablet_added(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ಸಂರಚನಾ zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_tool_added(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ಸಂರಚನಾ zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, ಪರಿಮಾಣ(*sdltool));

    ಯದಿ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.ಅಂಕೆ_buttons = -1;

        ಯದಿ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ಸೇರಿಸು(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ tablet_seat_handle_pad_added(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ಸಂರಚನಾ zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

ಶೂನ್ಯ Wayland_DisplayInitTabletManager(SDL_VideoData *display)
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

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    ಯದಿ (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ಅನ್ಯಥಾ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ರಿಕ್ತ);
    }

    ಯದಿ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ರಿಕ್ತ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

ಶೂನ್ಯ Wayland_DisplayCreateSeat(SDL_VideoData *display, ಸಂರಚನಾ wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, ಪರಿಮಾಣ(SDL_WaylandSeat));
    ಯದಿ (!seat) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ಸೇರಿಸು(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_ಒಳಹರಿವು(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    ಯದಿ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ಶೂನ್ಯ Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ಯದಿ (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        ಯದಿ (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = ರಿಕ್ತ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            ಯದಿ (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಯದಿ (tool->focus == window) {
                tool->focus = ರಿಕ್ತ;
                Wayland_TabletToolUpdateCursor(tool);
                ಯದಿ (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            ಯದಿ (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                ಯದಿ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

ಶೂನ್ಯ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    ಯದಿ (!seat) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_free(seat->name);

    ಯದಿ (seat->data_device) {
        ಯದಿ (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        ಯದಿ (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        ಯದಿ (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            ಯದಿ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ಯದಿ (seat->data_device->data_device) {
            ಯದಿ (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } ಅನ್ಯಥಾ {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    ಯದಿ (seat->primary_selection_device) {
        ಯದಿ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ಯದಿ (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        ಯದಿ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ಯದಿ (seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು) {
        zwp_text_ಒಳಹರಿವು_v3_destroy(seat->text_ಒಳಹರಿವು.zwp_text_ಒಳಹರಿವು);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    ಯದಿ (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } ಅನ್ಯಥಾ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    ಯದಿ (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        ಯದಿ (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ಯದಿ (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                ಯದಿ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } ಅನ್ಯಥಾ {
                    relative_focus = seat->pointer.focus->keyboard_focus_ಎಣಿಕೆ != 0;
                }
            } ಅನ್ಯಥಾ {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        ಯದಿ (relative_focus) {
            ಯದಿ (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } ಅನ್ಯಥಾ ಯದಿ (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = ರಿಕ್ತ;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    ಯದಿ (display->ಕೀಲಿ_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ಯದಿ (seat->keyboard.ಕೀಲಿ_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ಕೀಲಿ_inhibitor);
            seat->keyboard.ಕೀಲಿ_inhibitor = ರಿಕ್ತ;
        }

        ಯದಿ (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            ಯದಿ (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ಯದಿ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.ಕೀಲಿ_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ಕೀಲಿ_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

ಶೂನ್ಯ Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    ಯದಿ (display->pointer_constraints) {
        ಯದಿ (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = ರಿಕ್ತ;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        ಯದಿ (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ಯದಿ (seat->pointer.relative_pointer) {
                ಯದಿ (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ಯದಿ (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = ರಿಕ್ತ;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, ರಿಕ್ತ,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ಪ್ರತ್ಯಾಗಮ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ಯದಿ (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ರಿಕ್ತ;
            }

            SDL_WindowData *w = seat->pointer.focus;
            ಯದಿ (!w) {
                ಪ್ರತ್ಯಾಗಮ;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ಯದಿ (!(window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                ಪ್ರತ್ಯಾಗಮ;
            }

            ಸಂರಚನಾ wl_region *confine_rect = ರಿಕ್ತ;
            ಯದಿ (!SDL_RectEmpty(&window->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(window, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_add(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                ಯದಿ (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    ಪೂರ್ಣಾಙ್ಕ closest_x = seat->pointer.last_motion.x;
                    ಪೂರ್ಣಾಙ್ಕ closest_y = seat->pointer.last_motion.y;

                    ಯದಿ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ಅನ್ಯಥಾ ಯದಿ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ಯದಿ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ಅನ್ಯಥಾ ಯದಿ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ಯದಿ (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                ಯದಿ (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } ಅನ್ಯಥಾ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                ರಿಕ್ತ,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                ಯದಿ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ಯದಿ (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

ಶೂನ್ಯ Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ಯದಿ (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

ಶೂನ್ಯ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ಯದಿ (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
