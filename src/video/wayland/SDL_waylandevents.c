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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাৱ "../../core/unix/SDL_poll.h"
#অন্তর্ভাৱ "../../events/SDL_events_c.h"
#অন্তর্ভাৱ "../../events/SDL_scancode_tables_c.h"
#অন্তর্ভাৱ "../../events/SDL_keysym_to_keycode_c.h"
#অন্তর্ভাৱ "../../core/linux/SDL_system_theme.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"

#অন্তর্ভাৱ "SDL_waylandvideo.h"
#অন্তর্ভাৱ "SDL_waylandevents_c.h"
#অন্তর্ভাৱ "SDL_waylandwindow.h"
#অন্তর্ভাৱ "SDL_waylandmouse.h"
#অন্তর্ভাৱ "SDL_waylandclipboard.h"
#অন্তর্ভাৱ "SDL_waylandkeyboard.h"

#অন্তর্ভাৱ "pointer-constraints-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "relative-pointer-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "xdg-shell-client-protocol.h"
#অন্তর্ভাৱ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "text-input-unstable-v3-client-protocol.h"
#অন্তর্ভাৱ "tablet-v2-client-protocol.h"
#অন্তর্ভাৱ "primary-selection-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "input-timestamps-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "pointer-gestures-unstable-v1-client-protocol.h"
#অন্তর্ভাৱ "cursor-shape-v1-client-protocol.h"
#অন্তর্ভাৱ "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#অন্তর্ভাৱ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_প্ৰবেশ_LINUXEV
#অন্তর্ভাৱ <linux/input.h>
#অন্যথা
#define BTN_বাম    (0x110)
#define BTN_ডান   (0x111)
#define BTN_মধ্য  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#অন্তর্ভাৱ "../../events/SDL_keysym_to_scancode_c.h"
#অন্তর্ভাৱ "../../events/imKStoUCS.h"
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <sys/mman.h>
#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <xkbcommon/xkbcommon-compose.h>
#অন্তর্ভাৱ <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_নিচেৰ  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_উপৰেৰ (WAYLAND_TIMER_ROLLOVER_INTERVAL_নিচেৰ * 15U)

// Scoped function declarations
স্থির শূন্য Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

প্রকারনির্দেশ সংরচনা
{
    Uint32 চাবি;
    SDL_Scancode scancode;
} Wayland_Reserved_চাবি;

প্রকারনির্দেশ সংরচনা
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    সংরচনা wl_surface *surface;

    সংরচনা wl_list link;
} SDL_WaylandTouchPoint;

স্থির শূন্য Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, সংরচনা wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(পরিমাণ(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ঢোকাও(&seat->touch.points, &tp->link);
}

স্থির শূন্য Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    যদি (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        যদি (window_data) {
            ধ্রুৱ ভিন্ন x = (ভিন্ন)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ধ্রুৱ ভিন্ন y = (ভিন্ন)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_গুনতি;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            যদি (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_গুনতি &&
                !window_data->pointer_focus_গুনতি && !window_data->active_touch_গুনতি) {
                SDL_SetMouseFocus(রিক্ত);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

স্থির শূন্য Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, সংরচনা wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        যদি (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            যদি (surface) {
                *surface = tp->surface;
            }
            ভঙ্গ;
        }
    }
}

স্থির শূন্য Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, সংরচনা wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        যদি (tp->id == id) {
            যদি (fx) {
                *fx = tp->fx;
            }
            যদি (fy) {
                *fy = tp->fy;
            }
            যদি (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ভঙ্গ;
        }
    }
}

স্থির শূন্য Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (পূর্ণাঙ্ক)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (পূর্ণাঙ্ক)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (পূর্ণাঙ্ক)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (পূর্ণাঙ্ক)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

স্থির Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    স্থির Uint64 timestamp_offset = 0;
    ধ্রুৱ Uint64 now = SDL_GetTicksNS();

    যদি (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    যদি (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ঘূৰাই nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
স্থির Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    স্থির Uint64 timestamp_offset = 0;
    স্থির Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    যদি (wl_timestamp_ms >= last) {
        যদি (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_নিচেৰ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_উপৰেৰ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } অন্যথা {
            last = wl_timestamp_ms;
        }
    } অন্যথা {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        যদি (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_নিচেৰ && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_উপৰেৰ) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    ঘূৰাই timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

স্থির Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ধ্রুৱ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ঘূৰাই Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

স্থির Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ধ্রুৱ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ঘূৰাই Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ধ্রুৱ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ঘূৰাই Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

স্থির শূন্য প্ৰবেশ_timestamp_listener(শূন্য *data, সংরচনা zwp_প্ৰবেশ_timestamps_v1 *zwp_প্ৰবেশ_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

স্থির ধ্রুৱ সংরচনা zwp_প্ৰবেশ_timestamps_v1_listener timestamp_listener = {
    প্ৰবেশ_timestamp_listener
};

স্থির শূন্য Wayland_Seat_Register_প্ৰবেশ_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    যদি (seat->display->প্ৰবেশ_timestamps_manager) {
        যদি (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_প্ৰবেশ_timestamps_manager_v1_get_keyboard_timestamps(seat->display->প্ৰবেশ_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_প্ৰবেশ_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        যদি (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_প্ৰবেশ_timestamps_manager_v1_get_pointer_timestamps(seat->display->প্ৰবেশ_timestamps_manager, seat->pointer.wl_pointer);
            zwp_প্ৰবেশ_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        যদি (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_প্ৰবেশ_timestamps_manager_v1_get_touch_timestamps(seat->display->প্ৰবেশ_timestamps_manager, seat->touch.wl_touch);
            zwp_প্ৰবেশ_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

শূন্য Wayland_Display_Init_প্ৰবেশ_Timestamp_Manager(SDL_VideoData *display)
{
    যদি (display->প্ৰবেশ_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_প্ৰবেশ_Timestamp_Listeners(seat);
        }
    }
}

স্থির শূন্য handle_pinch_begin(শূন্য *data, সংরচনা zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, সংরচনা wl_surface *surface, uint32_t fingers)
{
    যদি (!surface) {
        ঘূৰাই;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    যদি (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ধ্রুৱ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

স্থির শূন্য handle_pinch_update(শূন্য *data, সংরচনা zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    যদি (seat->pointer.gesture_focus) {
        ধ্রুৱ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ধ্রুৱ ভিন্ন s = (ভিন্ন)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

স্থির শূন্য handle_pinch_end(শূন্য *data, সংরচনা zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    যদি (seat->pointer.gesture_focus) {
        ধ্রুৱ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = রিক্ত;
    }
}

স্থির ধ্রুৱ সংরচনা zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

স্থির শূন্য Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    যদি (seat->display->zwp_pointer_gestures) {
        যদি (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

শূন্য Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

স্থির শূন্য Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    যদি (seat->display->cursor_shape_manager) {
        যদি (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            যদি (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

শূন্য Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

স্থির শূন্য Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ধ্রুৱ bool send_event = !seat->display->initializing;

    যদি (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.অঙ্ক_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
স্থির শূন্য keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    যেতিয়ালৈ (elapsed >= repeat_info->next_repeat_ns) {
        যদি (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ধ্রুৱ Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_চাবি_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->চাবি, repeat_info->scancode, true);
        }
        যদি (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

স্থির শূন্য keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t চাবি, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ধ্রুৱ ৱর্ণ *text)
{
    যদি (!repeat_info->repeat_rate) {
        ঘূৰাই;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->চাবি = চাবি;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    যদি (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } অন্যথা {
        repeat_info->text[0] = '\0';
    }
}

স্থির শূন্য sync_done_handler(শূন্য *data, সংরচনা wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

স্থির সংরচনা wl_callback_listener sync_listener = {
    sync_done_handler
};

শূন্য Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    সংরচনা wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, রিক্ত);
    WAYLAND_wl_display_flush(d->display);
}

পূর্ণাঙ্ক Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ধ্রুৱ পূর্ণাঙ্ক display_fd = WAYLAND_wl_display_get_fd(d->display);
    পূর্ণাঙ্ক ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    যদি (!d->text_প্ৰবেশ_manager && keyboard_focus && SDL_Text_প্ৰবেশ_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        যদি (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        যদি (seat->keyboard.repeat.চাবি) {
            ধ্রুৱ Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ধ্রুৱ Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            যদি (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    যদি (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        যদি (timeoutNS > 0) {
            ধ্রুৱ Uint64 now = SDL_GetTicksNS();
            ধ্রুৱ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        যদি (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            যদি (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        যদি (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ঘূৰাই errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        যদি (timeoutNS > 0) {
            ধ্রুৱ Uint64 now = SDL_GetTicksNS();
            ধ্রুৱ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        যদি (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            যদি (ret == 0) {
                ঘূৰাই poll_alarm_set ? 1 : 0;
            } অন্যথা {
                // Pump events on an interrupt or broken pipe to handle the error.
                ঘূৰাই errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        যদি (ret == -1) {
            ঘূৰাই ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ঘূৰাই 1;
}

শূন্য Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ধ্রুৱ পূর্ণাঙ্ক display_fd = WAYLAND_wl_display_get_fd(d->display);
    পূর্ণাঙ্ক ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    যদি (!d->text_প্ৰবেশ_manager && keyboard_focus && SDL_Text_প্ৰবেশ_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    যদি (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    যদি (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        যদি (ret < 0) {
            গচ্ছ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    যদি (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        যদি (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            যদি (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        যদি (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            গচ্ছ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        যদি (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            যদি (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } অন্যথা {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } অন্যথা {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    যদি (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            যদি (seat->keyboard.repeat.চাবি) {
                Wayland_SeatSetKeymap(seat);

                ধ্রুৱ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    যদি (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

স্থির শূন্য pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : রিক্ত;

    যদি (window_data) {
        দ্ৱিগুণ sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        দ্ৱিগুণ sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        যদি (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (দ্ৱিগুণ)window_data->mask.offset_x;
            sy += (দ্ৱিগুণ)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        যদি (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (ভিন্ন)sx, (ভিন্ন)sy);
        } অন্যথা {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (ভিন্ন)sx, (ভিন্ন)sy);
        }

        seat->pointer.last_motion.x = (পূর্ণাঙ্ক)SDL_floor(sx);
        seat->pointer.last_motion.y = (পূর্ণাঙ্ক)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        যদি (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        যদি (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ৱিকল্প (rc) {
            পক্ষ SDL_HITTEST_RESIZE_TOPLEFT:
                যদি ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_শীৰ্ষ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_বাম)) {
                    rc = SDL_HITTEST_NORMAL;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_শীৰ্ষ) {
                    rc = SDL_HITTEST_RESIZE_বাম;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_বাম) {
                    rc = SDL_HITTEST_RESIZE_শীৰ্ষ;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_শীৰ্ষ:
                যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_শীৰ্ষ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_TOPRIGHT:
                যদি ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_শীৰ্ষ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ডান)) {
                    rc = SDL_HITTEST_NORMAL;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_শীৰ্ষ) {
                    rc = SDL_HITTEST_RESIZE_ডান;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ডান) {
                    rc = SDL_HITTEST_RESIZE_শীৰ্ষ;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_ডান:
                যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ডান) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                যদি ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ডান)) {
                    rc = SDL_HITTEST_NORMAL;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ডান;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ডান) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_BOTTOM:
                যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                যদি ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_বাম)) {
                    rc = SDL_HITTEST_NORMAL;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_বাম;
                } অন্যথা যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_বাম) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ভঙ্গ;
            পক্ষ SDL_HITTEST_RESIZE_বাম:
                যদি (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_বাম) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ভঙ্গ;
            স্ৱভাৱ:
                ভঙ্গ;
            }

            যদি (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

স্থির শূন্য pointer_handle_motion(শূন্য *data, সংরচনা wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ধ্রুৱ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    যদি (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        যদি (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } অন্যথা {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

স্থির শূন্য pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    যদি (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ঘূৰাই;
    }

    যদি (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        ঘূৰাই;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_গুনতি;
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

স্থির শূন্য pointer_handle_enter(শূন্য *data, সংরচনা wl_pointer *pointer,
                                 uint32_t serial, সংরচনা wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    যদি (!surface) {
        // Enter event for a destroyed surface.
        ঘূৰাই;
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

    যদি (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

স্থির শূন্য pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    যদি (window) {
        যদি (seat->pointer.focus) {
            যদি (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = রিক্ত;
                seat->pointer.focus_surface = রিক্ত;
                বাবে (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    যদি (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ধ্রুৱ bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                যদি (!--window->pointer_focus_গুনতি && had_focus && !window->active_touch_গুনতি) {
                    SDL_SetMouseFocus(রিক্ত);
                }

                যদি (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } অন্যথা যদি (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

স্থির শূন্য pointer_handle_leave(শূন্য *data, সংরচনা wl_pointer *pointer,
                                 uint32_t serial, সংরচনা wl_surface *surface)
{
    যদি (!surface) {
        // Leave event for a destroyed surface.
        ঘূৰাই;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    যদি (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

স্থির bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    যদি (seat->pointer.locked_pointer) {
        ঘূৰাই false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    যদি (window->hit_test) {
        স্থির ধ্রুৱ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_শীৰ্ষ_বাম, XDG_TOPLEVEL_RESIZE_EDGE_শীৰ্ষ,
            XDG_TOPLEVEL_RESIZE_EDGE_শীৰ্ষ_ডান, XDG_TOPLEVEL_RESIZE_EDGE_ডান,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ডান, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_বাম, XDG_TOPLEVEL_RESIZE_EDGE_বাম
        };

#ifdef HAVE_LIBDECOR_H
        স্থির ধ্রুৱ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_শীৰ্ষ_বাম, LIBDECOR_RESIZE_EDGE_শীৰ্ষ,
            LIBDECOR_RESIZE_EDGE_শীৰ্ষ_ডান, LIBDECOR_RESIZE_EDGE_ডান,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ডান, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_বাম, LIBDECOR_RESIZE_EDGE_বাম
        };
#endif

        ৱিকল্প (window_data->hit_test_result) {
        পক্ষ SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            যদি (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                যদি (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } অন্যথা
#endif
                যদি (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                যদি (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ঘূৰাই true;

        পক্ষ SDL_HITTEST_RESIZE_TOPLEFT:
        পক্ষ SDL_HITTEST_RESIZE_শীৰ্ষ:
        পক্ষ SDL_HITTEST_RESIZE_TOPRIGHT:
        পক্ষ SDL_HITTEST_RESIZE_ডান:
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        পক্ষ SDL_HITTEST_RESIZE_BOTTOM:
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        পক্ষ SDL_HITTEST_RESIZE_বাম:
#ifdef HAVE_LIBDECOR_H
            যদি (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                যদি (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } অন্যথা
#endif
                যদি (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                যদি (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ঘূৰাই true;

        স্ৱভাৱ:
            ঘূৰাই false;
        }
    }

    ঘূৰাই false;
}

স্থির শূন্য pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    যদি (window) {
        bool ignore_click = false;

        যদি (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            যদি (sdl_button == SDL_BUTTON_বাম && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                ঘূৰাই; // don't pass this event on to app.
            }
        } অন্যথা {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        যদি (window->last_focus_event_time_ns) {
            যদি (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        যদি (!seat->pointer.relative_pointer) {
            যদি (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } অন্যথা {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                যদি (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        যদি (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

স্থির শূন্য pointer_handle_button(শূন্য *data, সংরচনা wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    ৱিকল্প (button) {
    পক্ষ BTN_বাম:
        sdl_button = SDL_BUTTON_বাম;
        ভঙ্গ;
    পক্ষ BTN_মধ্য:
        sdl_button = SDL_BUTTON_মধ্য;
        ভঙ্গ;
    পক্ষ BTN_ডান:
        sdl_button = SDL_BUTTON_ডান;
        ভঙ্গ;
    স্ৱভাৱ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ভঙ্গ;
    }

    যদি (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    যদি (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        যদি (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } অন্যথা {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } অন্যথা {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

স্থির শূন্য pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t মান)
{
    SDL_WindowData *window = seat->pointer.focus;
    ধ্রুৱ গণনা wl_pointer_axis a = axis;

    যদি (seat->pointer.focus) {
        ভিন্ন x, y;

        ৱিকল্প (a) {
        পক্ষ WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ভিন্ন)wl_fixed_to_double(মান);
            ভঙ্গ;
        পক্ষ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (ভিন্ন)wl_fixed_to_double(মান);
            y = 0;
            ভঙ্গ;
        স্ৱভাৱ:
            ঘূৰাই;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

স্থির শূন্য pointer_handle_axis_common(SDL_WaylandSeat *seat, গণনা SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t মান)
{
    ধ্রুৱ গণনা wl_pointer_axis a = axis;

    যদি (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        ৱিকল্প (a) {
        পক্ষ WL_POINTER_AXIS_VERTICAL_SCROLL:
            ৱিকল্প (type) {
            পক্ষ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                যদি (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (ভিন্ন)wl_fixed_to_double(মান);
                ভঙ্গ;
            পক্ষ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                যদি (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (ভিন্ন)wl_fixed_to_double(মান);
                }
                ভঙ্গ;
            পক্ষ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                যদি (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (ভিন্ন)wl_fixed_to_double(মান);
                }
                ভঙ্গ;
            }
            ভঙ্গ;
        পক্ষ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            ৱিকল্প (type) {
            পক্ষ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                যদি (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (ভিন্ন)wl_fixed_to_double(মান);
                ভঙ্গ;
            পক্ষ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                যদি (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (ভিন্ন)wl_fixed_to_double(মান);
                }
                ভঙ্গ;
            পক্ষ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                যদি (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (ভিন্ন)wl_fixed_to_double(মান);
                }
                ভঙ্গ;
            }
            ভঙ্গ;
        }
    }
}

স্থির শূন্য pointer_handle_axis(শূন্য *data, সংরচনা wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t মান)
{
    SDL_WaylandSeat *seat = data;
    ধ্রুৱ Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    যদি (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, মান);
    } অন্যথা {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, মান);
    }
}

স্থির শূন্য pointer_handle_axis_relative_direction(শূন্য *data, সংরচনা wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    ৱিকল্প (axis_relative_direction) {
    পক্ষ WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        ভঙ্গ;
    পক্ষ WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ভঙ্গ;
    }
}

স্থির শূন্য pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    যদি (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        দ্ৱিগুণ dx;
        দ্ৱিগুণ dy;
        যদি (mouse->প্ৰবেশ_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } অন্যথা {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (ভিন্ন)dx, (ভিন্ন)dy);
    }
}

স্থির শূন্য pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    ভিন্ন x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    ৱিকল্প (seat->pointer.pending_frame.axis.x_axis_type) {
    পক্ষ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ভঙ্গ;
    পক্ষ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        ভঙ্গ;
    পক্ষ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        ভঙ্গ;
    স্ৱভাৱ:
        x = 0.0f;
        ভঙ্গ;
    }

    ৱিকল্প (seat->pointer.pending_frame.axis.y_axis_type) {
    পক্ষ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ভঙ্গ;
    পক্ষ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        ভঙ্গ;
    পক্ষ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        ভঙ্গ;
    স্ৱভাৱ:
        y = 0.0f;
        ভঙ্গ;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

স্থির শূন্য pointer_handle_frame(শূন্য *data, সংরচনা wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    যদি (seat->pointer.pending_frame.enter_surface) {
        যদি (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            যদি (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = রিক্ত;
                seat->pointer.pending_frame.leave_surface = রিক্ত;
            } অন্যথা {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = রিক্ত;
            }
        }

        যদি (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    যদি (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    যদি (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    বাবে (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ধ্রুৱ Uint32 mask = SDL_BUTTON_MASK(i);
        যদি (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        যদি (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    যদি (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    যদি (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

স্থির শূন্য pointer_handle_axis_source(শূন্য *data, সংরচনা wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

স্থির শূন্য pointer_handle_axis_stop(শূন্য *data, সংরচনা wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

স্থির শূন্য pointer_handle_axis_discrete(শূন্য *data, সংরচনা wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

স্থির শূন্য pointer_handle_axis_value120(শূন্য *data, সংরচনা wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

স্থির শূন্য pointer_handle_warp(শূন্য *data, সংরচনা wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

স্থির ধ্রুৱ সংরচনা wl_pointer_listener pointer_listener = {
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

স্থির শূন্য relative_pointer_handle_relative_motion(শূন্য *data,
                                                    সংরচনা zwp_relative_pointer_v1 *pointer,
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

    যদি (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } অন্যথা {
        pointer_dispatch_relative_motion(seat);
    }
}

স্থির ধ্রুৱ সংরচনা zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

স্থির শূন্য locked_pointer_locked(শূন্য *data, সংরচনা zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

স্থির শূন্য locked_pointer_unlocked(শূন্য *data, সংরচনা zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

স্থির ধ্রুৱ সংরচনা zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

স্থির শূন্য confined_pointer_confined(শূন্য *data, সংরচনা zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

স্থির শূন্য confined_pointer_unconfined(শূন্য *data, সংরচনা zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

স্থির ধ্রুৱ সংরচনা zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

স্থির শূন্য touch_handler_down(শূন্য *data, সংরচনা wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, সংরচনা wl_surface *surface,
                               পূর্ণাঙ্ক id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    যদি (!surface) {
        ঘূৰাই;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    যদি (window_data && window_data->surface == surface) {
        ভিন্ন x, y;

        যদি (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } অন্যথা {
            x = (ভিন্ন)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        যদি (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } অন্যথা {
            y = (ভিন্ন)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_গুনতি;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

স্থির শূন্য touch_handler_up(শূন্য *data, সংরচনা wl_touch *touch, uint32_t serial, uint32_t timestamp, পূর্ণাঙ্ক id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    সংরচনা wl_surface *surface = রিক্ত;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    যদি (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        যদি (window_data && window_data->surface == surface) {
            ধ্রুৱ ভিন্ন x = (ভিন্ন)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ধ্রুৱ ভিন্ন y = (ভিন্ন)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_গুনতি;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            যদি (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_গুনতি &&
                !window_data->pointer_focus_গুনতি && !window_data->active_touch_গুনতি) {
                SDL_SetMouseFocus(রিক্ত);
            }
        }
    }
}

স্থির শূন্য touch_handler_motion(শূন্য *data, সংরচনা wl_touch *touch, uint32_t timestamp, পূর্ণাঙ্ক id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    সংরচনা wl_surface *surface = রিক্ত;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    যদি (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        যদি (window_data && window_data->surface == surface) {
            ধ্রুৱ ভিন্ন x = (ভিন্ন)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ধ্রুৱ ভিন্ন y = (ভিন্ন)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

স্থির শূন্য touch_handler_frame(শূন্য *data, সংরচনা wl_touch *touch)
{
}

স্থির শূন্য touch_handler_cancel(শূন্য *data, সংরচনা wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

স্থির শূন্য touch_handler_shape(শূন্য *data, সংরচনা wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

স্থির শূন্য touch_handler_orientation(শূন্য *data, সংরচনা wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

স্থির ধ্রুৱ সংরচনা wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#যদি !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
স্থির size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t চাবি, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    যদি (!masks_out || !masks_size) {
        ঘূৰাই 0;
    }

    // Level 0 is always unmodified, so early out.
    যদি (level == 0) {
        *masks_out = 0;
        ঘূৰাই 1;
    }

    size_t mask_idx = 0;
    ধ্রুৱ xkb_mod_mask_t keymod_masks[] = {
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
    ধ্রুৱ xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    ধ্রুৱ xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    বাবে (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        যদি (WAYLAND_xkb_state_চাবি_get_level(seat->keyboard.xkb.state, চাবি, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            যদি (++mask_idx == masks_size) {
                ভঙ্গ;
            }
        }
    }

    ঘূৰাই mask_idx;
}
#endif

স্থির শূন্য Wayland_KeymapIterator(সংরচনা xkb_keymap *keymap, xkb_keycode_t চাবি, শূন্য *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ধ্রুৱ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ধ্রুৱ xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    যদি (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, চাবি - 8);
    }

    বাবে (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.অঙ্ক_layouts; ++layout) {
        ধ্রুৱ xkb_level_index_t অঙ্ক_levels = WAYLAND_xkb_keymap_অঙ্ক_levels_for_চাবি(seat->keyboard.xkb.keymap, চাবি, layout);
        বাবে (xkb_level_index_t level = 0; level < অঙ্ক_levels; ++level) {
            যদি (WAYLAND_xkb_keymap_চাবি_get_syms_by_level(seat->keyboard.xkb.keymap, চাবি, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                যদি (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_চাবি_Sym(syms[0], চাবি);
                    যদি (scancode == SDL_SCANCODE_UNKNOWN) {
                        অনুৱর্ত;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ধ্রুৱ size_t অঙ্ক_masks = WAYLAND_xkb_keymap_চাবি_get_mods_for_level(seat->keyboard.xkb.keymap, চাবি, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#অন্যথা
                ধ্রুৱ size_t অঙ্ক_masks = xkb_legacy_get_mods_for_level(seat, চাবি, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                বাবে (size_t mask = 0; mask < অঙ্ক_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    যদি ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        অনুৱর্ত;
                    }

                    ধ্রুৱ SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_চাবি_Code_From_চাবি_Sym(syms[0], চাবি, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    যদি (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        যদি (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_চাবি *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, পরিমাণ(Wayland_Reserved_চাবি));
                        যদি (res) {
                            res->scancode = scancode;
                            res->চাবি = চাবি - 8;
                        }
                    }

                    যদি (!keycode) {
                        ৱিকল্প (scancode) {
                        পক্ষ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ভঙ্গ;
                        পক্ষ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ভঙ্গ;
                        পক্ষ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ভঙ্গ;
                        পক্ষ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ভঙ্গ;
                        স্ৱভাৱ:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            ভঙ্গ;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

স্থির শূন্য keyboard_handle_keymap(শূন্য *data, সংরচনা wl_keyboard *keyboard,
                                   uint32_t format, পূর্ণাঙ্ক fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    ৱর্ণ *map_str;

    যদি (!data) {
        close(fd);
        ঘূৰাই;
    }

    যদি (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ঘূৰাই;
    }

    map_str = mmap(রিক্ত, size, PROT_READ, MAP_PRIVATE, fd, 0);
    যদি (map_str == MAP_FAILED) {
        close(fd);
        ঘূৰাই;
    }

    যদি (seat->keyboard.xkb.keymap != রিক্ত) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = রিক্ত;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    যদি (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        ঘূৰাই;
    }

    // Clear the old layouts.
    বাবে (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.অঙ্ক_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = রিক্ত;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.অঙ্ক_layouts = 0;

#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.অঙ্ক_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_অঙ্ক);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#অন্যথা
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.অঙ্ক_mask = 1 << GET_MOD_INDEX(অঙ্ক_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    যদি (seat->keyboard.xkb.state != রিক্ত) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = রিক্ত;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    যদি (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = রিক্ত;
        ঘূৰাই;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == রিক্ত;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.অঙ্ক_layouts = WAYLAND_xkb_keymap_অঙ্ক_layouts(seat->keyboard.xkb.keymap);
    যদি (seat->keyboard.xkb.অঙ্ক_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.অঙ্ক_layouts, পরিমাণ(SDL_Keymap *));
        যদি (!seat->keyboard.sdl_keymap) {
            ঘূৰাই;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        বাবে (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.অঙ্ক_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            যদি (!seat->keyboard.sdl_keymap[i]) {
                বাবে (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = রিক্ত;
                ঘূৰাই;
            }
        }

        WAYLAND_xkb_keymap_চাবি_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.অঙ্ক_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ধ্রুৱ ৱর্ণ *locale = SDL_getenv("LC_ALL");
    যদি (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        যদি (!locale) {
            locale = SDL_getenv("LANG");
            যদি (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    যদি (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        যদি (seat->keyboard.xkb.compose_table != রিক্ত) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = রিক্ত;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        যদি (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            যদি (seat->keyboard.xkb.compose_state != রিক্ত) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = রিক্ত;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            যদি (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = রিক্ত;
            }
        }
    } অন্যথা যদি (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
স্থির SDL_Scancode Wayland_Get_Scancode_For_চাবি(SDL_WaylandSeat *seat, Uint32 চাবি, ধ্রুৱ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    যদি (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, চাবি);

        // No table entry? Check the reserved list.
        যদি (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_চাবি *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                যদি (i->চাবি == চাবি) {
                    ঘূৰাই i->scancode;
                }
            }
        }
    } অন্যথা {
        ধ্রুৱ xkb_keysym_t *keysym;
        যদি (WAYLAND_xkb_state_চাবি_get_syms(seat->keyboard.xkb.state, চাবি + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_চাবি_Sym(keysym[0], চাবি + 8);
            যদি (syms) {
                *syms = keysym;
            }
        }
    }

    ঘূৰাই scancode;
}

স্থির শূন্য Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool চাবি_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    যদি (!চাবি_pressed) {
        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } অন্যথা {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } অন্যথা {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } অন্যথা {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } অন্যথা {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } অন্যথা {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        যদি (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            যদি (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } অন্যথা {
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
    ধ্রুৱ xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        যদি (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } অন্যথা যদি (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        যদি (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } অন্যথা যদি (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        যদি (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } অন্যথা যদি (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        যদি (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } অন্যথা যদি (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    যদি (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    যদি (xkb_locked_modifiers & seat->keyboard.xkb.অঙ্ক_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_অঙ্ক;
    } অন্যথা {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_অঙ্ক;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

স্থির শূন্য Wayland_Handle_Modifier_চাবিগুলি(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ধ্রুৱ SDL_Keycode keycode = SDL_Get_চাবি_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ৱিকল্প (keycode) {
    পক্ষ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ভঙ্গ;
    পক্ষ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ভঙ্গ;
    পক্ষ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ভঙ্গ;
    পক্ষ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ভঙ্গ;
    পক্ষ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ভঙ্গ;
    পক্ষ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ভঙ্গ;
    পক্ষ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ভঙ্গ;
    পক্ষ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ভঙ্গ;
    পক্ষ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        ভঙ্গ;
    পক্ষ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        ভঙ্গ;
    স্ৱভাৱ:
        ঘূৰাই;
    }

    যদি (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } অন্যথা {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

স্থির শূন্য keyboard_handle_enter(শূন্য *data, সংরচনা wl_keyboard *keyboard,
                                  uint32_t serial, সংরচনা wl_surface *surface,
                                  সংরচনা wl_array *চাবিগুলি)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *চাবি;

    যদি (!surface) {
        // Enter event for a destroyed surface.
        ঘূৰাই;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    যদি (!window) {
        // Not a surface owned by SDL.
        ঘূৰাই;
    }

    ++window->keyboard_focus_গুনতি;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_প্ৰবেশ(seat);

#ifdef SDL_USE_IME
    যদি (!seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (চাবি, চাবিগুলি) {
        ধ্রুৱ SDL_Scancode scancode = Wayland_Get_Scancode_For_চাবি(seat, *চাবি, রিক্ত);
        যদি (scancode != SDL_SCANCODE_UNKNOWN) {
            ধ্রুৱ SDL_Keycode keycode = SDL_Get_চাবি_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ৱিকল্প (keycode) {
            পক্ষ SDLK_LSHIFT:
            পক্ষ SDLK_RSHIFT:
            পক্ষ SDLK_LCTRL:
            পক্ষ SDLK_RCTRL:
            পক্ষ SDLK_LALT:
            পক্ষ SDLK_RALT:
            পক্ষ SDLK_LGUI:
            পক্ষ SDLK_RGUI:
            পক্ষ SDLK_MODE:
            পক্ষ SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_চাবিগুলি(seat, scancode, true);
                SDL_Send_Keyboard_চাবি_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *চাবি, scancode, true);
                ভঙ্গ;
            স্ৱভাৱ:
                ভঙ্গ;
            }
        }
    }
}

স্থির শূন্য keyboard_handle_leave(শূন্য *data, সংরচনা wl_keyboard *keyboard,
                                  uint32_t serial, সংরচনা wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    যদি (!surface) {
        // Leave event for a destroyed surface.
        ঘূৰাই;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    যদি (!window) {
        // Not a surface owned by SDL.
        ঘূৰাই;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.চাবি = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    যেতিয়ালৈ (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ধ্রুৱ bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = রিক্ত;
    --window->keyboard_focus_গুনতি;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    যদি (!window->keyboard_focus_গুনতি && had_focus) {
        SDL_SetKeyboardFocus(রিক্ত);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_প্ৰবেশ(seat);

#ifdef SDL_USE_IME
    যদি (!seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ && !window->keyboard_focus_গুনতি) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    যদি (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_গুনতি && !window->active_touch_গুনতি) {
        SDL_SetMouseFocus(রিক্ত);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, রিক্ত);
}

স্থির bool keyboard_প্ৰবেশ_get_text(ৱর্ণ text[8], ধ্রুৱ SDL_WaylandSeat *seat, uint32_t চাবি, bool down, bool *handled_by_ime)
{
    ধ্রুৱ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    যদি (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ঘূৰাই false;
    }

    // TODO: Can this happen?
    যদি (WAYLAND_xkb_state_চাবি_get_syms(seat->keyboard.xkb.state, চাবি + 8, &syms) != 1) {
        ঘূৰাই false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    যদি (SDL_IME_Process_চাবি_Event(sym, চাবি + 8, down)) {
        যদি (handled_by_ime) {
            *handled_by_ime = true;
        }
        ঘূৰাই true;
    }
#endif

    যদি (!down) {
        ঘূৰাই false;
    }

    যদি (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ৱিকল্প (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        পক্ষ XKB_COMPOSE_COMPOSING:
            যদি (handled_by_ime) {
                *handled_by_ime = true;
            }
            ঘূৰাই true;
        পক্ষ XKB_COMPOSE_CANCELLED:
        স্ৱভাৱ:
            sym = XKB_চাবি_No_প্ৰতীক;
            ভঙ্গ;
        পক্ষ XKB_COMPOSE_NOTHING:
            ভঙ্গ;
        পক্ষ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ভঙ্গ;
        }
    }

    ঘূৰাই WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

স্থির শূন্য keyboard_handle_চাবি(শূন্য *data, সংরচনা wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t চাবি,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    গণনা wl_keyboard_চাবি_state state = state_w;
    ৱর্ণ text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ধ্রুৱ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    যদি (state == WL_KEYBOARD_চাবি_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        যদি (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_চাবি_repeats(seat->keyboard.xkb.keymap, চাবি + 8)) {
            ঘূৰাই;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_চাবি_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    যদি (state == WL_KEYBOARD_চাবি_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        যদি (keyboard_focus && SDL_Text_প্ৰবেশ_Active(keyboard_focus)) {
            has_text = keyboard_প্ৰবেশ_get_text(text, seat, চাবি, true, &handled_by_ime);
        }
    } অন্যথা {
        যদি (চাবি == seat->keyboard.repeat.চাবি) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ধ্রুৱ Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.চাবি = 0;
        }
        keyboard_প্ৰবেশ_get_text(text, seat, চাবি, false, &handled_by_ime);
    }

    ধ্রুৱ xkb_keysym_t *syms = রিক্ত;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_চাবি(seat, চাবি, &syms);
    Wayland_Handle_Modifier_চাবিগুলি(seat, scancode, state == WL_KEYBOARD_চাবি_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    যদি (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ধ্রুৱ SDL_Keycode keycode = (SDL_Keycode)SDL_চাবি_Sym_To_Ucs4(syms[0]);
        যদি (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            যদি (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_চাবি_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, চাবি, scancode, state == WL_KEYBOARD_চাবি_STATE_PRESSED);

    যদি (state == WL_KEYBOARD_চাবি_STATE_PRESSED) {
        যদি (handled_by_ime) {
            has_text = false;
        }
        যদি (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        যদি (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_চাবি_repeats(seat->keyboard.xkb.keymap, চাবি + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, চাবি, time, timestamp_ns, scancode, has_text ? text : রিক্ত);
        }
    }
}

স্থির শূন্য keyboard_handle_modifiers(শূন্য *data, সংরচনা wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    ধ্রুৱ uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    যদি (!seat->keyboard.xkb.state) {
        ঘূৰাই;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    যদি (seat->keyboard.repeat.চাবি) {
        ৱর্ণ text[8];

        যদি (keyboard_প্ৰবেশ_get_text(text, seat, seat->keyboard.repeat.চাবি, true, রিক্ত)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    যদি (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        যদি (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

স্থির শূন্য keyboard_handle_repeat_info(শূন্য *data, সংরচনা wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    যদি (!rate) {
        seat->keyboard.repeat.চাবি = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

স্থির ধ্রুৱ সংরচনা wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_চাবি,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

স্থির শূন্য Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    যদি (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    যদি (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = রিক্ত;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    যদি (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    যদি (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    যদি (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    যদি (seat->pointer.timestamps) {
        zwp_প্ৰবেশ_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    যদি (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    যদি (seat->pointer.wl_pointer) {
        যদি (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } অন্যথা {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

স্থির শূন্য Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    যদি (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    যদি (seat->keyboard.sdl_keymap) {
        যদি (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.অঙ্ক_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        বাবে (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.অঙ্ক_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = রিক্ত;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    যদি (seat->keyboard.চাবি_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.চাবি_inhibitor);
    }

    যদি (seat->keyboard.timestamps) {
        zwp_প্ৰবেশ_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    যদি (seat->keyboard.wl_keyboard) {
        যদি (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } অন্যথা {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    যদি (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    যদি (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    যদি (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    যদি (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

স্থির শূন্য Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    যদি (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    যদি (seat->touch.timestamps) {
        zwp_প্ৰবেশ_timestamps_v1_destroy(seat->touch.timestamps);
    }

    যদি (seat->touch.wl_touch) {
        যদি (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } অন্যথা {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

স্থির শূন্য seat_handle_capabilities(শূন্য *data, সংরচনা wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ৱর্ণ name_fmt[256];

    যদি ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        যদি (seat->name) {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } অন্যথা {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } অন্যথা যদি (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    যদি ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        যদি (seat->name) {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } অন্যথা {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } অন্যথা যদি (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    যদি ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        যদি (seat->name) {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } অন্যথা {
            SDL_snprintf(name_fmt, পরিমাণ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } অন্যথা যদি (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_প্ৰবেশ_Timestamp_Listeners(seat);
}

স্থির শূন্য seat_handle_name(শূন্য *data, সংরচনা wl_seat *wl_seat, ধ্রুৱ ৱর্ণ *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    যদি (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

স্থির ধ্রুৱ সংরচনা wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

স্থির শূন্য data_offer_handle_offer(শূন্য *data, সংরচনা wl_data_offer *wl_data_offer,
                                    ধ্রুৱ ৱর্ণ *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

স্থির শূন্য data_offer_handle_source_actions(শূন্য *data, সংরচনা wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

স্থির শূন্য data_offer_handle_actions(শূন্য *data, সংরচনা wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

স্থির ধ্রুৱ সংরচনা wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

স্থির শূন্য primary_selection_offer_handle_offer(শূন্য *data, সংরচনা zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ধ্রুৱ ৱর্ণ *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

স্থির ধ্রুৱ সংরচনা zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

স্থির শূন্য data_device_handle_data_offer(শূন্য *data, সংরচনা wl_data_device *wl_data_device,
                                          সংরচনা wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, পরিমাণ(*data_offer));
    যদি (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id) : -1));
    }
}

স্থির শূন্য data_device_handle_enter(শূন্য *data, সংরচনা wl_data_device *wl_data_device,
                                     uint32_t serial, সংরচনা wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, সংরচনা wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : রিক্ত;
    data_device->has_mime_file = false;
    data_device->text_mime_type = রিক্ত;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    যদি (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    যদি (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        যদি (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        যদি (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        যদি (!data_device->has_mime_file) {
            size_t mime_গুনতি = 0;
            ধ্রুৱ ৱর্ণ *ধ্রুৱ *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_গুনতি);
            বাবে (size_t i = 0; i < mime_গুনতি; ++i) {
                যদি (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    ভঙ্গ;
                }
            }
        }

        যদি (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            যদি (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            দ্ৱিগুণ dx = wl_fixed_to_double(x);
            দ্ৱিগুণ dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            যদি (surface == window->mask.surface) {
                dx += (দ্ৱিগুণ)window->mask.offset_x;
                dy += (দ্ৱিগুণ)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (ভিন্ন)dx, (ভিন্ন)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } অন্যথা {
            // Decline the offer.
            wl_data_offer_accept(id, serial, রিক্ত);
            যদি (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } অন্যথা {
        data_device->dnd_window = রিক্ত;
        data_device->dnd_surface = রিক্ত;

        // Decline the offer.
        যদি (id) {
            wl_data_offer_accept(id, serial, রিক্ত);
            যদি (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

স্থির শূন্য data_device_handle_leave(শূন্য *data, সংরচনা wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    যদি (data_device->drag_offer) {
        যদি (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } অন্যথা {
            SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = রিক্ত;
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = রিক্ত;
}

স্থির শূন্য data_device_handle_motion(শূন্য *data, সংরচনা wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    যদি (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        দ্ৱিগুণ dx = wl_fixed_to_double(x);
        দ্ৱিগুণ dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        যদি (data_device->dnd_surface == window_data->mask.surface) {
            dx += (দ্ৱিগুণ)window_data->mask.offset_x;
            dy += (দ্ৱিগুণ)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (ভিন্ন)dx, (ভিন্ন)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

স্থির শূন্য drop_cleanup_handler(শূন্য *data, সংরচনা wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

স্থির ধ্রুৱ সংরচনা wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

স্থির শূন্য drop_dispatch_handler(শূন্য *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    যদি (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        যদি (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            শূন্য *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            যদি (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                যদি (dbus) {
                    পূর্ণাঙ্ক path_গুনতি = 0;
                    ৱর্ণ **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_গুনতি);
                    // If dropped files contain a directory the list is empty
                    যদি (paths && path_গুনতি > 0) {
                        বাবে (পূর্ণাঙ্ক i = 0; i < path_গুনতি; i++) {
                            SDL_SendDropFile(drop->dnd_window, রিক্ত, paths[i]);
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
        যদি (!drop_handled) {
            যদি (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                শূন্য *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                যদি (buffer) {
                    ৱর্ণ *saveptr = রিক্ত;
                    ৱর্ণ *token = SDL_strtok_r((ৱর্ণ *)buffer, "\r\n", &saveptr);
                    যেতিয়ালৈ (token) {
                        যদি (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, রিক্ত, token);
                        }
                        token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } অন্যথা যদি (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                শূন্য *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                যদি (buffer) {
                    ৱর্ণ *saveptr = রিক্ত;
                    ৱর্ণ *token = SDL_strtok_r((ৱর্ণ *)buffer, "\r\n", &saveptr);
                    যেতিয়ালৈ (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(রিক্ত, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        যদি (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = রিক্ত;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

স্থির শূন্য data_device_handle_drop(শূন্য *data, সংরচনা wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    যদি (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, পরিমাণ(Wayland_DropData));
        যদি (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_ঢোকাও(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } অন্যথা {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } অন্যথা {
        SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = রিক্ত;
}

স্থির শূন্য data_device_handle_selection(শূন্য *data, সংরচনা wl_data_device *wl_data_device,
                                         সংরচনা wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = রিক্ত;

    যদি (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

স্থির ধ্রুৱ সংরচনা wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

স্থির শূন্য primary_selection_device_handle_offer(শূন্য *data, সংরচনা zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  সংরচনা zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, পরিমাণ(*primary_selection_offer));
    যদি (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id) : -1));
}

স্থির শূন্য primary_selection_device_handle_selection(শূন্য *data, সংরচনা zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      সংরচনা zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = রিক্ত;

    যদি (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    যদি (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_প্ৰবেশ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((সংরচনা wl_proxy *)id) : -1));
}

স্থির ধ্রুৱ সংরচনা zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

স্থির শূন্য text_প্ৰবেশ_enter(শূন্য *data,
                             সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                             সংরচনা wl_surface *surface)
{
    // No-op
}

স্থির শূন্য text_প্ৰবেশ_leave(শূন্য *data,
                             সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                             সংরচনা wl_surface *surface)
{
    // No-op
}

স্থির শূন্য text_প্ৰবেশ_preedit_string(শূন্য *data,
                                      সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                                      ধ্রুৱ ৱর্ণ *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_প্ৰবেশ.has_preedit = true;
    যদি (text) {
        পূর্ণাঙ্ক cursor_begin_utf8 = cursor_begin >= 0 ? (পূর্ণাঙ্ক)SDL_utf8strnlen(text, cursor_begin) : -1;
        পূর্ণাঙ্ক cursor_end_utf8 = cursor_end >= 0 ? (পূর্ণাঙ্ক)SDL_utf8strnlen(text, cursor_end) : -1;
        পূর্ণাঙ্ক cursor_size_utf8;
        যদি (cursor_end_utf8 >= 0) {
            যদি (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } অন্যথা {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } অন্যথা {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } অন্যথা {
        SDL_SendEditingText("", 0, 0);
    }
}

স্থির শূন্য text_প্ৰবেশ_commit_string(শূন্য *data,
                                     সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                                     ধ্রুৱ ৱর্ণ *text)
{
    SDL_SendKeyboardText(text);
}

স্থির শূন্য text_প্ৰবেশ_delete_surrounding_text(শূন্য *data,
                                               সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

স্থির শূন্য text_প্ৰবেশ_done(শূন্য *data,
                            সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    যদি (!seat->text_প্ৰবেশ.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_প্ৰবেশ.has_preedit = false;
}

স্থির ধ্রুৱ সংরচনা zwp_text_প্ৰবেশ_v3_listener text_প্ৰবেশ_listener = {
    text_প্ৰবেশ_enter,
    text_প্ৰবেশ_leave,
    text_প্ৰবেশ_preedit_string,
    text_প্ৰবেশ_commit_string,
    text_প্ৰবেশ_delete_surrounding_text,
    text_প্ৰবেশ_done
};

স্থির শূন্য Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    যদি (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        যদি (dbus) {
            ধ্রুৱ ৱর্ণ *id = dbus->bus_get_unique_name(dbus->session_conn);
            যদি (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    যদি (!data_device->id_str)
#endif
    {
        ৱর্ণ id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, পরিমাণ(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

স্থির শূন্য Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    যদি (!seat->display->data_device_manager) {
        ঘূৰাই;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, পরিমাণ(*data_device));
    যদি (!data_device) {
        ঘূৰাই;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    যদি (!data_device->data_device) {
        SDL_free(data_device);
        ঘূৰাই;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

শূন্য Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

স্থির শূন্য Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    যদি (!seat->display->primary_selection_device_manager) {
        ঘূৰাই;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, পরিমাণ(*primary_selection_device));
    যদি (!primary_selection_device) {
        ঘূৰাই;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    যদি (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } অন্যথা {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

শূন্য Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

স্থির শূন্য Wayland_Seat_Create_Text_প্ৰবেশ(SDL_WaylandSeat *seat)
{
    যদি (seat->display->text_প্ৰবেশ_manager) {
        seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ = zwp_text_প্ৰবেশ_manager_v3_get_text_প্ৰবেশ(seat->display->text_প্ৰবেশ_manager, seat->wl_seat);

        যদি (seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ) {
            zwp_text_প্ৰবেশ_v3_set_user_data(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ, seat);
            zwp_text_প্ৰবেশ_v3_add_listener(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ,
                                           &text_প্ৰবেশ_listener, seat);
        }
    }
}

শূন্য Wayland_Display_Init_Text_প্ৰবেশ_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_প্ৰবেশ(seat);
    }
}

// Pen/Tablet support...
স্থির শূন্য tablet_tool_handle_type(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ৱিকল্প (type) {
        #define CASE(typ) পক্ষ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ঘূৰাই
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        স্ৱভাৱ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

স্থির শূন্য tablet_tool_handle_hardware_serial(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

স্থির শূন্য tablet_tool_handle_hardware_id_wacom(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

স্থির শূন্য tablet_tool_handle_capability(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ৱিকল্প (capability) {
        #define CASE(wltyp,sdltyp) পক্ষ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ঘূৰাই
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        স্ৱভাৱ: ভঙ্গ;  // unsupported here.
    }
}

স্থির শূন্য tablet_tool_handle_done(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    যদি (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : রিক্ত;
        sdltool->instance_id = SDL_AddPenDevice(0, রিক্ত, window, &sdltool->info, sdltool, false);
    }
}

স্থির শূন্য tablet_tool_handle_removed(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    যদি (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : রিক্ত;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

স্থির শূন্য tablet_tool_handle_proximity_in(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t serial, সংরচনা zwp_tablet_v2 *tablet, সংরচনা wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : রিক্ত;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : রিক্ত;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

স্থির শূন্য tablet_tool_handle_proximity_out(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

স্থির শূন্য tablet_tool_handle_down(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

স্থির শূন্য tablet_tool_handle_up(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

স্থির শূন্য tablet_tool_handle_motion(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    যদি (windowdata) {
        sdltool->frame.x = (ভিন্ন)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (ভিন্ন)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

স্থির শূন্য tablet_tool_handle_pressure(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((ভিন্ন) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    যদি (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

স্থির শূন্য tablet_tool_handle_distance(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((ভিন্ন) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    যদি (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

স্থির শূন্য tablet_tool_handle_tilt(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (ভিন্ন)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (ভিন্ন)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

স্থির শূন্য tablet_tool_handle_button(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    পূর্ণাঙ্ক sdlbutton;

    ৱিকল্প (button) {
    পক্ষ BTN_STYLUS:
        sdlbutton = 1;
        ভঙ্গ;
    পক্ষ BTN_STYLUS2:
        sdlbutton = 2;
        ভঙ্গ;
    পক্ষ BTN_STYLUS3:
        sdlbutton = 3;
        ভঙ্গ;
    স্ৱভাৱ:
        ঘূৰাই;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

স্থির শূন্য tablet_tool_handle_rotation(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ধ্রুৱ ভিন্ন rotation = (ভিন্ন)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

স্থির শূন্য tablet_tool_handle_slider(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

স্থির শূন্য tablet_tool_handle_wheel(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

স্থির শূন্য tablet_tool_handle_frame(শূন্য *data, সংরচনা zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ধ্রুৱ SDL_PenID instance_id = sdltool->instance_id;
    যদি (!instance_id) {
        ঘূৰাই;  // Not a pen we report on.
    }

    ধ্রুৱ Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : রিক্ত;
    ধ্রুৱ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    যদি (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    যদি (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        যদি (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } অন্যথা {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } অন্যথা {
        যদি (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        যদি (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    বাবে (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_গুনতি; i++) {
        যদি (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    বাবে (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ধ্রুৱ পূর্ণাঙ্ক state = sdltool->frame.buttons[i];
        যদি (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    যদি (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = রিক্ত;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

স্থির ধ্রুৱ সংরচনা zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


স্থির শূন্য tablet_seat_handle_tablet_added(শূন্য *data, সংরচনা zwp_tablet_seat_v2 *zwp_tablet_seat_v2, সংরচনা zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

স্থির শূন্য tablet_seat_handle_tool_added(শূন্য *data, সংরচনা zwp_tablet_seat_v2 *zwp_tablet_seat_v2, সংরচনা zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, পরিমাণ(*sdltool));

    যদি (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.অঙ্ক_buttons = -1;

        যদি (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ঢোকাও(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

স্থির শূন্য tablet_seat_handle_pad_added(শূন্য *data, সংরচনা zwp_tablet_seat_v2 *zwp_tablet_seat_v2, সংরচনা zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

স্থির ধ্রুৱ সংরচনা zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

স্থির শূন্য Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

শূন্য Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

স্থির শূন্য Wayland_remove_all_pens_callback(SDL_PenID instance_id, শূন্য *handle, শূন্য *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

স্থির শূন্য Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    যদি (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } অন্যথা {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, রিক্ত);
    }

    যদি (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = রিক্ত;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

শূন্য Wayland_DisplayCreateSeat(SDL_VideoData *display, সংরচনা wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, পরিমাণ(SDL_WaylandSeat));
    যদি (!seat) {
        ঘূৰাই;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ঢোকাও(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_প্ৰবেশ(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    যদি (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

শূন্য Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        যদি (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        যদি (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = রিক্ত;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            যদি (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            যদি (tool->focus == window) {
                tool->focus = রিক্ত;
                Wayland_TabletToolUpdateCursor(tool);
                যদি (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            যদি (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                যদি (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

শূন্য Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    যদি (!seat) {
        ঘূৰাই;
    }

    SDL_free(seat->name);

    যদি (seat->data_device) {
        যদি (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        যদি (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        যদি (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            যদি (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        যদি (seat->data_device->data_device) {
            যদি (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } অন্যথা {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    যদি (seat->primary_selection_device) {
        যদি (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        যদি (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        যদি (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    যদি (seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ) {
        zwp_text_প্ৰবেশ_v3_destroy(seat->text_প্ৰবেশ.zwp_text_প্ৰবেশ);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    যদি (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } অন্যথা {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

স্থির শূন্য Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    যদি (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        যদি (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            যদি (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                যদি (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } অন্যথা {
                    relative_focus = seat->pointer.focus->keyboard_focus_গুনতি != 0;
                }
            } অন্যথা {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        যদি (relative_focus) {
            যদি (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } অন্যথা যদি (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = রিক্ত;
        }
    }
}

স্থির শূন্য Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    যদি (display->চাবি_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        যদি (seat->keyboard.চাবি_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.চাবি_inhibitor);
            seat->keyboard.চাবি_inhibitor = রিক্ত;
        }

        যদি (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            যদি (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                যদি (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.চাবি_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->চাবি_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

শূন্য Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    যদি (display->pointer_constraints) {
        যদি (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = রিক্ত;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        যদি (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            যদি (seat->pointer.relative_pointer) {
                যদি (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    যদি (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = রিক্ত;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, রিক্ত,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ঘূৰাই;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            যদি (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = রিক্ত;
            }

            SDL_WindowData *w = seat->pointer.focus;
            যদি (!w) {
                ঘূৰাই;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            যদি (!(window->flags & SDL_WINDOW_প্ৰবেশ_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                ঘূৰাই;
            }

            সংরচনা wl_region *confine_rect = রিক্ত;
            যদি (!SDL_RectEmpty(&window->mouse_rect)) {
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
                যদি (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    পূর্ণাঙ্ক closest_x = seat->pointer.last_motion.x;
                    পূর্ণাঙ্ক closest_y = seat->pointer.last_motion.y;

                    যদি (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } অন্যথা যদি (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    যদি (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } অন্যথা যদি (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            যদি (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                যদি (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } অন্যথা {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                রিক্ত,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                যদি (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

শূন্য Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        যদি (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

শূন্য Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        যদি (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

শূন্য Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    যদি (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
