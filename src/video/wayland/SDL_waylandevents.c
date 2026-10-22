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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_scancode_tables_c.h"
#شامل "../../events/SDL_keysym_to_keycode_c.h"
#شامل "../../core/linux/SDL_system_theme.h"
#شامل "../SDL_sysvideo.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylandmouse.h"
#شامل "SDL_waylandclipboard.h"
#شامل "SDL_waylandkeyboard.h"

#شامل "pointer-constraints-unstable-v1-client-protocol.h"
#شامل "relative-pointer-unstable-v1-client-protocol.h"
#شامل "xdg-shell-client-protocol.h"
#شامل "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#شامل "text-input-unstable-v3-client-protocol.h"
#شامل "tablet-v2-client-protocol.h"
#شامل "primary-selection-unstable-v1-client-protocol.h"
#شامل "input-timestamps-unstable-v1-client-protocol.h"
#شامل "pointer-gestures-unstable-v1-client-protocol.h"
#شامل "cursor-shape-v1-client-protocol.h"
#شامل "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#شامل <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_درون_داد_LINUXEV
#شامل <linux/input.h>
#وگرنه
#define BTN_چپ    (0x110)
#define BTN_راست   (0x111)
#define BTN_میانه  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#شامل "../../events/SDL_keysym_to_scancode_c.h"
#شامل "../../events/imKStoUCS.h"
#شامل <errno.h>
#شامل <sys/mman.h>
#شامل <unistd.h>
#شامل <xkbcommon/xkbcommon-compose.h>
#شامل <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_کم  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا (WAYLAND_TIMER_ROLLOVER_INTERVAL_کم * 15U)

// Scoped function declarations
ایستا تهی Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

تعریفنوع ساختار
{
    Uint32 کلید;
    SDL_Scancode scancode;
} Wayland_Reserved_کلید;

تعریفنوع ساختار
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ساختار wl_surface *surface;

    ساختار wl_list link;
} SDL_WaylandTouchPoint;

ایستا تهی Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ساختار wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(اندازه(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_درج(&seat->touch.points, &tp->link);
}

ایستا تهی Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    اگر (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        اگر (window_data) {
            ثابت اعشاری x = (اعشاری)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ثابت اعشاری y = (اعشاری)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_شمار;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            اگر (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_شمار &&
                !window_data->pointer_focus_شمار && !window_data->active_touch_شمار) {
                SDL_SetMouseFocus(پوچ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ایستا تهی Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ساختار wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        اگر (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            اگر (surface) {
                *surface = tp->surface;
            }
            بشکن;
        }
    }
}

ایستا تهی Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ساختار wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        اگر (tp->id == id) {
            اگر (fx) {
                *fx = tp->fx;
            }
            اگر (fy) {
                *fy = tp->fy;
            }
            اگر (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            بشکن;
        }
    }
}

ایستا تهی Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (صحیح)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (صحیح)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (صحیح)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (صحیح)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

ایستا Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    ایستا Uint64 timestamp_offset = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    اگر (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    اگر (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    بازگشت nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ایستا Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ایستا Uint64 timestamp_offset = 0;
    ایستا Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    اگر (wl_timestamp_ms >= last) {
        اگر (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } وگرنه {
            last = wl_timestamp_ms;
        }
    } وگرنه {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        اگر (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    بازگشت timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ایستا Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    بازگشت Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ایستا Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    بازگشت Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    بازگشت Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ایستا تهی درون_داد_timestamp_listener(تهی *data, ساختار zwp_درون_داد_timestamps_v1 *zwp_درون_داد_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

ایستا ثابت ساختار zwp_درون_داد_timestamps_v1_listener timestamp_listener = {
    درون_داد_timestamp_listener
};

ایستا تهی Wayland_Seat_Register_درون_داد_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    اگر (seat->display->درون_داد_timestamps_manager) {
        اگر (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_درون_داد_timestamps_manager_v1_get_keyboard_timestamps(seat->display->درون_داد_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_درون_داد_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        اگر (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_درون_داد_timestamps_manager_v1_get_pointer_timestamps(seat->display->درون_داد_timestamps_manager, seat->pointer.wl_pointer);
            zwp_درون_داد_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        اگر (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_درون_داد_timestamps_manager_v1_get_touch_timestamps(seat->display->درون_داد_timestamps_manager, seat->touch.wl_touch);
            zwp_درون_داد_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

تهی Wayland_Display_Init_درون_داد_Timestamp_Manager(SDL_VideoData *display)
{
    اگر (display->درون_داد_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_درون_داد_Timestamp_Listeners(seat);
        }
    }
}

ایستا تهی handle_pinch_begin(تهی *data, ساختار zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, ساختار wl_surface *surface, uint32_t fingers)
{
    اگر (!surface) {
        بازگشت;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    اگر (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ایستا تهی handle_pinch_update(تهی *data, ساختار zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    اگر (seat->pointer.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ثابت اعشاری s = (اعشاری)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ایستا تهی handle_pinch_end(تهی *data, ساختار zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    اگر (seat->pointer.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = پوچ;
    }
}

ایستا ثابت ساختار zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

ایستا تهی Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    اگر (seat->display->zwp_pointer_gestures) {
        اگر (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

تهی Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

ایستا تهی Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    اگر (seat->display->cursor_shape_manager) {
        اگر (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            اگر (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

تهی Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ایستا تهی Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    اگر (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ایستا تهی keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    وقتی (elapsed >= repeat_info->next_repeat_ns) {
        اگر (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->کلید, repeat_info->scancode, true);
        }
        اگر (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

ایستا تهی keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کلید, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ثابت نویسه *text)
{
    اگر (!repeat_info->repeat_rate) {
        بازگشت;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کلید = کلید;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    اگر (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } وگرنه {
        repeat_info->text[0] = '\0';
    }
}

ایستا تهی sync_done_handler(تهی *data, ساختار wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ایستا ساختار wl_callback_listener sync_listener = {
    sync_done_handler
};

تهی Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ساختار wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, پوچ);
    WAYLAND_wl_display_flush(d->display);
}

صحیح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحیح ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    اگر (!d->text_درون_داد_manager && keyboard_focus && SDL_Text_درون_داد_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        اگر (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        اگر (seat->keyboard.repeat.کلید) {
            ثابت Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ثابت Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            اگر (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    اگر (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        اگر (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        اگر (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            اگر (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        اگر (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            بازگشت errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        اگر (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        اگر (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            اگر (ret == 0) {
                بازگشت poll_alarm_set ? 1 : 0;
            } وگرنه {
                // Pump events on an interrupt or broken pipe to handle the error.
                بازگشت errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        اگر (ret == -1) {
            بازگشت ret;
        }
    }

    // Signal to the caller that there might be an event available.
    بازگشت 1;
}

تهی Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحیح ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    اگر (!d->text_درون_داد_manager && keyboard_focus && SDL_Text_درون_داد_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    اگر (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    اگر (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        اگر (ret < 0) {
            برو connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    اگر (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        اگر (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            اگر (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        اگر (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            برو connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        اگر (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            اگر (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } وگرنه {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } وگرنه {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    اگر (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            اگر (seat->keyboard.repeat.کلید) {
                Wayland_SeatSetKeymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    اگر (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ایستا تهی pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : پوچ;

    اگر (window_data) {
        دوگانه sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        دوگانه sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        اگر (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (دوگانه)window_data->mask.offset_x;
            sy += (دوگانه)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        اگر (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (اعشاری)sx, (اعشاری)sy);
        } وگرنه {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (اعشاری)sx, (اعشاری)sy);
        }

        seat->pointer.last_motion.x = (صحیح)SDL_floor(sx);
        seat->pointer.last_motion.y = (صحیح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        اگر (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        اگر (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            انتخاب (rc) {
            حالت SDL_HITTEST_RESIZE_TOPLEFT:
                اگر ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ)) {
                    rc = SDL_HITTEST_NORMAL;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_RESIZE_چپ;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_RESIZE_بالاترین;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_بالاترین:
                اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_NORMAL;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_TOPRIGHT:
                اگر ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست)) {
                    rc = SDL_HITTEST_NORMAL;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_RESIZE_راست;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_RESIZE_بالاترین;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_راست:
                اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_NORMAL;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                اگر ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست)) {
                    rc = SDL_HITTEST_NORMAL;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_راست;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_BOTTOM:
                اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
                اگر ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ)) {
                    rc = SDL_HITTEST_NORMAL;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_چپ;
                } وگرنه اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                بشکن;
            حالت SDL_HITTEST_RESIZE_چپ:
                اگر (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                بشکن;
            پیشفرض:
                بشکن;
            }

            اگر (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

ایستا تهی pointer_handle_motion(تهی *data, ساختار wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    اگر (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        اگر (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } وگرنه {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

ایستا تهی pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    اگر (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        بازگشت;
    }

    اگر (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        بازگشت;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_شمار;
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

ایستا تهی pointer_handle_enter(تهی *data, ساختار wl_pointer *pointer,
                                 uint32_t serial, ساختار wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    اگر (!surface) {
        // Enter event for a destroyed surface.
        بازگشت;
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

    اگر (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

ایستا تهی pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    اگر (window) {
        اگر (seat->pointer.focus) {
            اگر (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = پوچ;
                seat->pointer.focus_surface = پوچ;
                برای (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    اگر (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                اگر (!--window->pointer_focus_شمار && had_focus && !window->active_touch_شمار) {
                    SDL_SetMouseFocus(پوچ);
                }

                اگر (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } وگرنه اگر (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ایستا تهی pointer_handle_leave(تهی *data, ساختار wl_pointer *pointer,
                                 uint32_t serial, ساختار wl_surface *surface)
{
    اگر (!surface) {
        // Leave event for a destroyed surface.
        بازگشت;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    اگر (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

ایستا bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    اگر (seat->pointer.locked_pointer) {
        بازگشت false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    اگر (window->hit_test) {
        ایستا ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_بالاترین_چپ, XDG_TOPLEVEL_RESIZE_EDGE_بالاترین,
            XDG_TOPLEVEL_RESIZE_EDGE_بالاترین_راست, XDG_TOPLEVEL_RESIZE_EDGE_راست,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_راست, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_چپ, XDG_TOPLEVEL_RESIZE_EDGE_چپ
        };

#ifdef HAVE_LIBDECOR_H
        ایستا ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_بالاترین_چپ, LIBDECOR_RESIZE_EDGE_بالاترین,
            LIBDECOR_RESIZE_EDGE_بالاترین_راست, LIBDECOR_RESIZE_EDGE_راست,
            LIBDECOR_RESIZE_EDGE_BOTTOM_راست, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_چپ, LIBDECOR_RESIZE_EDGE_چپ
        };
#endif

        انتخاب (window_data->hit_test_result) {
        حالت SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            اگر (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                اگر (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } وگرنه
#endif
                اگر (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                اگر (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            بازگشت true;

        حالت SDL_HITTEST_RESIZE_TOPLEFT:
        حالت SDL_HITTEST_RESIZE_بالاترین:
        حالت SDL_HITTEST_RESIZE_TOPRIGHT:
        حالت SDL_HITTEST_RESIZE_راست:
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالت SDL_HITTEST_RESIZE_BOTTOM:
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالت SDL_HITTEST_RESIZE_چپ:
#ifdef HAVE_LIBDECOR_H
            اگر (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                اگر (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وگرنه
#endif
                اگر (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                اگر (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            بازگشت true;

        پیشفرض:
            بازگشت false;
        }
    }

    بازگشت false;
}

ایستا تهی pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    اگر (window) {
        bool ignore_click = false;

        اگر (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            اگر (sdl_button == SDL_BUTTON_چپ && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                بازگشت; // don't pass this event on to app.
            }
        } وگرنه {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        اگر (window->last_focus_event_time_ns) {
            اگر (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        اگر (!seat->pointer.relative_pointer) {
            اگر (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } وگرنه {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                اگر (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        اگر (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

ایستا تهی pointer_handle_button(تهی *data, ساختار wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    انتخاب (button) {
    حالت BTN_چپ:
        sdl_button = SDL_BUTTON_چپ;
        بشکن;
    حالت BTN_میانه:
        sdl_button = SDL_BUTTON_میانه;
        بشکن;
    حالت BTN_راست:
        sdl_button = SDL_BUTTON_راست;
        بشکن;
    پیشفرض:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        بشکن;
    }

    اگر (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    اگر (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        اگر (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } وگرنه {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } وگرنه {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ایستا تهی pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t مقدار)
{
    SDL_WindowData *window = seat->pointer.focus;
    ثابت شمارش wl_pointer_axis a = axis;

    اگر (seat->pointer.focus) {
        اعشاری x, y;

        انتخاب (a) {
        حالت WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (اعشاری)wl_fixed_to_double(مقدار);
            بشکن;
        حالت WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (اعشاری)wl_fixed_to_double(مقدار);
            y = 0;
            بشکن;
        پیشفرض:
            بازگشت;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

ایستا تهی pointer_handle_axis_common(SDL_WaylandSeat *seat, شمارش SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t مقدار)
{
    ثابت شمارش wl_pointer_axis a = axis;

    اگر (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        انتخاب (a) {
        حالت WL_POINTER_AXIS_VERTICAL_SCROLL:
            انتخاب (type) {
            حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                اگر (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (اعشاری)wl_fixed_to_double(مقدار);
                بشکن;
            حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                اگر (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (اعشاری)wl_fixed_to_double(مقدار);
                }
                بشکن;
            حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                اگر (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (اعشاری)wl_fixed_to_double(مقدار);
                }
                بشکن;
            }
            بشکن;
        حالت WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            انتخاب (type) {
            حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                اگر (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (اعشاری)wl_fixed_to_double(مقدار);
                بشکن;
            حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                اگر (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (اعشاری)wl_fixed_to_double(مقدار);
                }
                بشکن;
            حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                اگر (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (اعشاری)wl_fixed_to_double(مقدار);
                }
                بشکن;
            }
            بشکن;
        }
    }
}

ایستا تهی pointer_handle_axis(تهی *data, ساختار wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t مقدار)
{
    SDL_WaylandSeat *seat = data;
    ثابت Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    اگر (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, مقدار);
    } وگرنه {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, مقدار);
    }
}

ایستا تهی pointer_handle_axis_relative_direction(تهی *data, ساختار wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    انتخاب (axis_relative_direction) {
    حالت WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        بشکن;
    حالت WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        بشکن;
    }
}

ایستا تهی pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    اگر (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        دوگانه dx;
        دوگانه dy;
        اگر (mouse->درون_داد_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } وگرنه {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (اعشاری)dx, (اعشاری)dy);
    }
}

ایستا تهی pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    اعشاری x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    انتخاب (seat->pointer.pending_frame.axis.x_axis_type) {
    حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        بشکن;
    حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        بشکن;
    حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        بشکن;
    پیشفرض:
        x = 0.0f;
        بشکن;
    }

    انتخاب (seat->pointer.pending_frame.axis.y_axis_type) {
    حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        بشکن;
    حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        بشکن;
    حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        بشکن;
    پیشفرض:
        y = 0.0f;
        بشکن;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

ایستا تهی pointer_handle_frame(تهی *data, ساختار wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    اگر (seat->pointer.pending_frame.enter_surface) {
        اگر (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            اگر (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = پوچ;
                seat->pointer.pending_frame.leave_surface = پوچ;
            } وگرنه {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = پوچ;
            }
        }

        اگر (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    اگر (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    اگر (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    برای (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ثابت Uint32 mask = SDL_BUTTON_MASK(i);
        اگر (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        اگر (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    اگر (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    اگر (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

ایستا تهی pointer_handle_axis_source(تهی *data, ساختار wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

ایستا تهی pointer_handle_axis_stop(تهی *data, ساختار wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

ایستا تهی pointer_handle_axis_discrete(تهی *data, ساختار wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ایستا تهی pointer_handle_axis_value120(تهی *data, ساختار wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ایستا تهی pointer_handle_warp(تهی *data, ساختار wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

ایستا ثابت ساختار wl_pointer_listener pointer_listener = {
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

ایستا تهی relative_pointer_handle_relative_motion(تهی *data,
                                                    ساختار zwp_relative_pointer_v1 *pointer,
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

    اگر (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } وگرنه {
        pointer_dispatch_relative_motion(seat);
    }
}

ایستا ثابت ساختار zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

ایستا تهی locked_pointer_locked(تهی *data, ساختار zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ایستا تهی locked_pointer_unlocked(تهی *data, ساختار zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ایستا ثابت ساختار zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

ایستا تهی confined_pointer_confined(تهی *data, ساختار zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ایستا تهی confined_pointer_unconfined(تهی *data, ساختار zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ایستا ثابت ساختار zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

ایستا تهی touch_handler_down(تهی *data, ساختار wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ساختار wl_surface *surface,
                               صحیح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    اگر (!surface) {
        بازگشت;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    اگر (window_data && window_data->surface == surface) {
        اعشاری x, y;

        اگر (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } وگرنه {
            x = (اعشاری)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        اگر (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } وگرنه {
            y = (اعشاری)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_شمار;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

ایستا تهی touch_handler_up(تهی *data, ساختار wl_touch *touch, uint32_t serial, uint32_t timestamp, صحیح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    ساختار wl_surface *surface = پوچ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    اگر (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        اگر (window_data && window_data->surface == surface) {
            ثابت اعشاری x = (اعشاری)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ثابت اعشاری y = (اعشاری)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_شمار;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            اگر (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_شمار &&
                !window_data->pointer_focus_شمار && !window_data->active_touch_شمار) {
                SDL_SetMouseFocus(پوچ);
            }
        }
    }
}

ایستا تهی touch_handler_motion(تهی *data, ساختار wl_touch *touch, uint32_t timestamp, صحیح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ساختار wl_surface *surface = پوچ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    اگر (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        اگر (window_data && window_data->surface == surface) {
            ثابت اعشاری x = (اعشاری)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ثابت اعشاری y = (اعشاری)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

ایستا تهی touch_handler_frame(تهی *data, ساختار wl_touch *touch)
{
}

ایستا تهی touch_handler_cancel(تهی *data, ساختار wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ایستا تهی touch_handler_shape(تهی *data, ساختار wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ایستا تهی touch_handler_orientation(تهی *data, ساختار wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ایستا ثابت ساختار wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#اگر !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
ایستا size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کلید, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    اگر (!masks_out || !masks_size) {
        بازگشت 0;
    }

    // Level 0 is always unmodified, so early out.
    اگر (level == 0) {
        *masks_out = 0;
        بازگشت 1;
    }

    size_t mask_idx = 0;
    ثابت xkb_mod_mask_t keymod_masks[] = {
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
    ثابت xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    ثابت xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    برای (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        اگر (WAYLAND_xkb_state_کلید_get_level(seat->keyboard.xkb.state, کلید, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            اگر (++mask_idx == masks_size) {
                بشکن;
            }
        }
    }

    بازگشت mask_idx;
}
#endif

ایستا تهی Wayland_KeymapIterator(ساختار xkb_keymap *keymap, xkb_keycode_t کلید, تهی *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    اگر (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, کلید - 8);
    }

    برای (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.رقم_layouts; ++layout) {
        ثابت xkb_level_index_t رقم_levels = WAYLAND_xkb_keymap_رقم_levels_for_کلید(seat->keyboard.xkb.keymap, کلید, layout);
        برای (xkb_level_index_t level = 0; level < رقم_levels; ++level) {
            اگر (WAYLAND_xkb_keymap_کلید_get_syms_by_level(seat->keyboard.xkb.keymap, کلید, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                اگر (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_کلید_Sym(syms[0], کلید);
                    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                        ادامه;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#اگر SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ثابت size_t رقم_masks = WAYLAND_xkb_keymap_کلید_get_mods_for_level(seat->keyboard.xkb.keymap, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وگرنه
                ثابت size_t رقم_masks = xkb_legacy_get_mods_for_level(seat, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                برای (size_t mask = 0; mask < رقم_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    اگر ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        ادامه;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کلید_Code_From_کلید_Sym(syms[0], کلید, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    اگر (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        اگر (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کلید *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, اندازه(Wayland_Reserved_کلید));
                        اگر (res) {
                            res->scancode = scancode;
                            res->کلید = کلید - 8;
                        }
                    }

                    اگر (!keycode) {
                        انتخاب (scancode) {
                        حالت SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            بشکن;
                        حالت SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            بشکن;
                        حالت SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            بشکن;
                        حالت SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            بشکن;
                        پیشفرض:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            بشکن;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ایستا تهی keyboard_handle_keymap(تهی *data, ساختار wl_keyboard *keyboard,
                                   uint32_t format, صحیح fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    نویسه *map_str;

    اگر (!data) {
        close(fd);
        بازگشت;
    }

    اگر (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        بازگشت;
    }

    map_str = mmap(پوچ, size, PROT_READ, MAP_PRIVATE, fd, 0);
    اگر (map_str == MAP_FAILED) {
        close(fd);
        بازگشت;
    }

    اگر (seat->keyboard.xkb.keymap != پوچ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = پوچ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    اگر (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        بازگشت;
    }

    // Clear the old layouts.
    برای (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = پوچ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.رقم_layouts = 0;

#اگر SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.رقم_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_رقم);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وگرنه
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.رقم_mask = 1 << GET_MOD_INDEX(رقم_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    اگر (seat->keyboard.xkb.state != پوچ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = پوچ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    اگر (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = پوچ;
        بازگشت;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == پوچ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.رقم_layouts = WAYLAND_xkb_keymap_رقم_layouts(seat->keyboard.xkb.keymap);
    اگر (seat->keyboard.xkb.رقم_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.رقم_layouts, اندازه(SDL_Keymap *));
        اگر (!seat->keyboard.sdl_keymap) {
            بازگشت;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        برای (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            اگر (!seat->keyboard.sdl_keymap[i]) {
                برای (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = پوچ;
                بازگشت;
            }
        }

        WAYLAND_xkb_keymap_کلید_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ثابت نویسه *locale = SDL_getenv("LC_ALL");
    اگر (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        اگر (!locale) {
            locale = SDL_getenv("LANG");
            اگر (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    اگر (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        اگر (seat->keyboard.xkb.compose_table != پوچ) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = پوچ;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        اگر (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            اگر (seat->keyboard.xkb.compose_state != پوچ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = پوچ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            اگر (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = پوچ;
            }
        }
    } وگرنه اگر (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ایستا SDL_Scancode Wayland_Get_Scancode_For_کلید(SDL_WaylandSeat *seat, Uint32 کلید, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    اگر (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, کلید);

        // No table entry? Check the reserved list.
        اگر (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_کلید *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                اگر (i->کلید == کلید) {
                    بازگشت i->scancode;
                }
            }
        }
    } وگرنه {
        ثابت xkb_keysym_t *keysym;
        اگر (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_کلید_Sym(keysym[0], کلید + 8);
            اگر (syms) {
                *syms = keysym;
            }
        }
    }

    بازگشت scancode;
}

ایستا تهی Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    اگر (!کلید_pressed) {
        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } وگرنه {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وگرنه {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وگرنه {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وگرنه {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } وگرنه {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } وگرنه {
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
    ثابت xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } وگرنه اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } وگرنه اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } وگرنه اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } وگرنه اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    اگر (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.رقم_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_رقم;
    } وگرنه {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_رقم;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ایستا تهی Wayland_Handle_Modifier_کلیدها(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    انتخاب (keycode) {
    حالت SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        بشکن;
    حالت SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        بشکن;
    حالت SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        بشکن;
    حالت SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        بشکن;
    حالت SDLK_LALT:
        mod = SDL_KMOD_LALT;
        بشکن;
    حالت SDLK_RALT:
        mod = SDL_KMOD_RALT;
        بشکن;
    حالت SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        بشکن;
    حالت SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        بشکن;
    حالت SDLK_MODE:
        mod = SDL_KMOD_MODE;
        بشکن;
    حالت SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        بشکن;
    پیشفرض:
        بازگشت;
    }

    اگر (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } وگرنه {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ایستا تهی keyboard_handle_enter(تهی *data, ساختار wl_keyboard *keyboard,
                                  uint32_t serial, ساختار wl_surface *surface,
                                  ساختار wl_array *کلیدها)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *کلید;

    اگر (!surface) {
        // Enter event for a destroyed surface.
        بازگشت;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    اگر (!window) {
        // Not a surface owned by SDL.
        بازگشت;
    }

    ++window->keyboard_focus_شمار;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_درون_داد(seat);

#ifdef SDL_USE_IME
    اگر (!seat->text_درون_داد.zwp_text_درون_داد) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (کلید, کلیدها) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, *کلید, پوچ);
        اگر (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false);

            انتخاب (keycode) {
            حالت SDLK_LSHIFT:
            حالت SDLK_RSHIFT:
            حالت SDLK_LCTRL:
            حالت SDLK_RCTRL:
            حالت SDLK_LALT:
            حالت SDLK_RALT:
            حالت SDLK_LGUI:
            حالت SDLK_RGUI:
            حالت SDLK_MODE:
            حالت SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_کلیدها(seat, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کلید, scancode, true);
                بشکن;
            پیشفرض:
                بشکن;
            }
        }
    }
}

ایستا تهی keyboard_handle_leave(تهی *data, ساختار wl_keyboard *keyboard,
                                  uint32_t serial, ساختار wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    اگر (!surface) {
        // Leave event for a destroyed surface.
        بازگشت;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    اگر (!window) {
        // Not a surface owned by SDL.
        بازگشت;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کلید = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    وقتی (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ثابت bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = پوچ;
    --window->keyboard_focus_شمار;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    اگر (!window->keyboard_focus_شمار && had_focus) {
        SDL_SetKeyboardFocus(پوچ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_درون_داد(seat);

#ifdef SDL_USE_IME
    اگر (!seat->text_درون_داد.zwp_text_درون_داد && !window->keyboard_focus_شمار) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    اگر (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_شمار && !window->active_touch_شمار) {
        SDL_SetMouseFocus(پوچ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, پوچ);
}

ایستا bool keyboard_درون_داد_get_text(نویسه text[8], ثابت SDL_WaylandSeat *seat, uint32_t کلید, bool down, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    اگر (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        بازگشت false;
    }

    // TODO: Can this happen?
    اگر (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &syms) != 1) {
        بازگشت false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    اگر (SDL_IME_Process_کلید_Event(sym, کلید + 8, down)) {
        اگر (handled_by_ime) {
            *handled_by_ime = true;
        }
        بازگشت true;
    }
#endif

    اگر (!down) {
        بازگشت false;
    }

    اگر (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        انتخاب (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        حالت XKB_COMPOSE_COMPOSING:
            اگر (handled_by_ime) {
                *handled_by_ime = true;
            }
            بازگشت true;
        حالت XKB_COMPOSE_CANCELLED:
        پیشفرض:
            sym = XKB_کلید_No_نماد;
            بشکن;
        حالت XKB_COMPOSE_NOTHING:
            بشکن;
        حالت XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            بشکن;
        }
    }

    بازگشت WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

ایستا تهی keyboard_handle_کلید(تهی *data, ساختار wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t کلید,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    شمارش wl_keyboard_کلید_state state = state_w;
    نویسه text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    اگر (state == WL_KEYBOARD_کلید_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        اگر (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            بازگشت;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کلید_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    اگر (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        اگر (keyboard_focus && SDL_Text_درون_داد_Active(keyboard_focus)) {
            has_text = keyboard_درون_داد_get_text(text, seat, کلید, true, &handled_by_ime);
        }
    } وگرنه {
        اگر (کلید == seat->keyboard.repeat.کلید) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کلید = 0;
        }
        keyboard_درون_داد_get_text(text, seat, کلید, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = پوچ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, کلید, &syms);
    Wayland_Handle_Modifier_کلیدها(seat, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    اگر (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کلید_Sym_To_Ucs4(syms[0]);
        اگر (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            اگر (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, کلید, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    اگر (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        اگر (handled_by_ime) {
            has_text = false;
        }
        اگر (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        اگر (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, کلید, time, timestamp_ns, scancode, has_text ? text : پوچ);
        }
    }
}

ایستا تهی keyboard_handle_modifiers(تهی *data, ساختار wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    ثابت uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    اگر (!seat->keyboard.xkb.state) {
        بازگشت;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    اگر (seat->keyboard.repeat.کلید) {
        نویسه text[8];

        اگر (keyboard_درون_داد_get_text(text, seat, seat->keyboard.repeat.کلید, true, پوچ)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    اگر (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        اگر (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ایستا تهی keyboard_handle_repeat_info(تهی *data, ساختار wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    اگر (!rate) {
        seat->keyboard.repeat.کلید = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ایستا ثابت ساختار wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_کلید,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ایستا تهی Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    اگر (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    اگر (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = پوچ;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    اگر (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    اگر (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    اگر (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    اگر (seat->pointer.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    اگر (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    اگر (seat->pointer.wl_pointer) {
        اگر (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } وگرنه {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

ایستا تهی Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    اگر (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    اگر (seat->keyboard.sdl_keymap) {
        اگر (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        برای (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = پوچ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    اگر (seat->keyboard.کلید_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
    }

    اگر (seat->keyboard.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    اگر (seat->keyboard.wl_keyboard) {
        اگر (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } وگرنه {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    اگر (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    اگر (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    اگر (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    اگر (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ایستا تهی Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    اگر (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    اگر (seat->touch.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->touch.timestamps);
    }

    اگر (seat->touch.wl_touch) {
        اگر (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } وگرنه {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ایستا تهی seat_handle_capabilities(تهی *data, ساختار wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    نویسه name_fmt[256];

    اگر ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        اگر (seat->name) {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } وگرنه {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } وگرنه اگر (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    اگر ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        اگر (seat->name) {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وگرنه {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } وگرنه اگر (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    اگر ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        اگر (seat->name) {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وگرنه {
            SDL_snprintf(name_fmt, اندازه(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } وگرنه اگر (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_درون_داد_Timestamp_Listeners(seat);
}

ایستا تهی seat_handle_name(تهی *data, ساختار wl_seat *wl_seat, ثابت نویسه *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    اگر (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ایستا ثابت ساختار wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ایستا تهی data_offer_handle_offer(تهی *data, ساختار wl_data_offer *wl_data_offer,
                                    ثابت نویسه *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

ایستا تهی data_offer_handle_source_actions(تهی *data, ساختار wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

ایستا تهی data_offer_handle_actions(تهی *data, ساختار wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

ایستا ثابت ساختار wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

ایستا تهی primary_selection_offer_handle_offer(تهی *data, ساختار zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت نویسه *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ایستا ثابت ساختار zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ایستا تهی data_device_handle_data_offer(تهی *data, ساختار wl_data_device *wl_data_device,
                                          ساختار wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, اندازه(*data_offer));
    اگر (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id) : -1));
    }
}

ایستا تهی data_device_handle_enter(تهی *data, ساختار wl_data_device *wl_data_device,
                                     uint32_t serial, ساختار wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ساختار wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : پوچ;
    data_device->has_mime_file = false;
    data_device->text_mime_type = پوچ;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    اگر (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    اگر (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        اگر (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        اگر (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        اگر (!data_device->has_mime_file) {
            size_t mime_شمار = 0;
            ثابت نویسه *ثابت *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_شمار);
            برای (size_t i = 0; i < mime_شمار; ++i) {
                اگر (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    بشکن;
                }
            }
        }

        اگر (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            اگر (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            دوگانه dx = wl_fixed_to_double(x);
            دوگانه dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            اگر (surface == window->mask.surface) {
                dx += (دوگانه)window->mask.offset_x;
                dy += (دوگانه)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (اعشاری)dx, (اعشاری)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } وگرنه {
            // Decline the offer.
            wl_data_offer_accept(id, serial, پوچ);
            اگر (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } وگرنه {
        data_device->dnd_window = پوچ;
        data_device->dnd_surface = پوچ;

        // Decline the offer.
        اگر (id) {
            wl_data_offer_accept(id, serial, پوچ);
            اگر (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

ایستا تهی data_device_handle_leave(تهی *data, ساختار wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    اگر (data_device->drag_offer) {
        اگر (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } وگرنه {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = پوچ;
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = پوچ;
}

ایستا تهی data_device_handle_motion(تهی *data, ساختار wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    اگر (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        دوگانه dx = wl_fixed_to_double(x);
        دوگانه dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        اگر (data_device->dnd_surface == window_data->mask.surface) {
            dx += (دوگانه)window_data->mask.offset_x;
            dy += (دوگانه)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (اعشاری)dx, (اعشاری)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

ایستا تهی drop_cleanup_handler(تهی *data, ساختار wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ایستا ثابت ساختار wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ایستا تهی drop_dispatch_handler(تهی *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    اگر (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        اگر (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            تهی *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            اگر (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                اگر (dbus) {
                    صحیح path_شمار = 0;
                    نویسه **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_شمار);
                    // If dropped files contain a directory the list is empty
                    اگر (paths && path_شمار > 0) {
                        برای (صحیح i = 0; i < path_شمار; i++) {
                            SDL_SendDropFile(drop->dnd_window, پوچ, paths[i]);
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
        اگر (!drop_handled) {
            اگر (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                تهی *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                اگر (buffer) {
                    نویسه *saveptr = پوچ;
                    نویسه *token = SDL_strtok_r((نویسه *)buffer, "\r\n", &saveptr);
                    وقتی (token) {
                        اگر (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, پوچ, token);
                        }
                        token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } وگرنه اگر (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                تهی *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                اگر (buffer) {
                    نویسه *saveptr = پوچ;
                    نویسه *token = SDL_strtok_r((نویسه *)buffer, "\r\n", &saveptr);
                    وقتی (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(پوچ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        اگر (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = پوچ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ایستا تهی data_device_handle_drop(تهی *data, ساختار wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    اگر (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, اندازه(Wayland_DropData));
        اگر (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_درج(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } وگرنه {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } وگرنه {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = پوچ;
}

ایستا تهی data_device_handle_selection(تهی *data, ساختار wl_data_device *wl_data_device,
                                         ساختار wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = پوچ;

    اگر (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

ایستا ثابت ساختار wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

ایستا تهی primary_selection_device_handle_offer(تهی *data, ساختار zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ساختار zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, اندازه(*primary_selection_offer));
    اگر (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id) : -1));
}

ایستا تهی primary_selection_device_handle_selection(تهی *data, ساختار zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ساختار zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = پوچ;

    اگر (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    اگر (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساختار wl_proxy *)id) : -1));
}

ایستا ثابت ساختار zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ایستا تهی text_درون_داد_enter(تهی *data,
                             ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                             ساختار wl_surface *surface)
{
    // No-op
}

ایستا تهی text_درون_داد_leave(تهی *data,
                             ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                             ساختار wl_surface *surface)
{
    // No-op
}

ایستا تهی text_درون_داد_preedit_string(تهی *data,
                                      ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                                      ثابت نویسه *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_درون_داد.has_preedit = true;
    اگر (text) {
        صحیح cursor_begin_utf8 = cursor_begin >= 0 ? (صحیح)SDL_utf8strnlen(text, cursor_begin) : -1;
        صحیح cursor_end_utf8 = cursor_end >= 0 ? (صحیح)SDL_utf8strnlen(text, cursor_end) : -1;
        صحیح cursor_size_utf8;
        اگر (cursor_end_utf8 >= 0) {
            اگر (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } وگرنه {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } وگرنه {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } وگرنه {
        SDL_SendEditingText("", 0, 0);
    }
}

ایستا تهی text_درون_داد_commit_string(تهی *data,
                                     ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                                     ثابت نویسه *text)
{
    SDL_SendKeyboardText(text);
}

ایستا تهی text_درون_داد_delete_surrounding_text(تهی *data,
                                               ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

ایستا تهی text_درون_داد_done(تهی *data,
                            ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    اگر (!seat->text_درون_داد.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_درون_داد.has_preedit = false;
}

ایستا ثابت ساختار zwp_text_درون_داد_v3_listener text_درون_داد_listener = {
    text_درون_داد_enter,
    text_درون_داد_leave,
    text_درون_داد_preedit_string,
    text_درون_داد_commit_string,
    text_درون_داد_delete_surrounding_text,
    text_درون_داد_done
};

ایستا تهی Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    اگر (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        اگر (dbus) {
            ثابت نویسه *id = dbus->bus_get_unique_name(dbus->session_conn);
            اگر (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    اگر (!data_device->id_str)
#endif
    {
        نویسه id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, اندازه(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

ایستا تهی Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    اگر (!seat->display->data_device_manager) {
        بازگشت;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, اندازه(*data_device));
    اگر (!data_device) {
        بازگشت;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    اگر (!data_device->data_device) {
        SDL_free(data_device);
        بازگشت;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

تهی Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

ایستا تهی Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    اگر (!seat->display->primary_selection_device_manager) {
        بازگشت;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, اندازه(*primary_selection_device));
    اگر (!primary_selection_device) {
        بازگشت;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    اگر (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } وگرنه {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

تهی Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ایستا تهی Wayland_Seat_Create_Text_درون_داد(SDL_WaylandSeat *seat)
{
    اگر (seat->display->text_درون_داد_manager) {
        seat->text_درون_داد.zwp_text_درون_داد = zwp_text_درون_داد_manager_v3_get_text_درون_داد(seat->display->text_درون_داد_manager, seat->wl_seat);

        اگر (seat->text_درون_داد.zwp_text_درون_داد) {
            zwp_text_درون_داد_v3_set_user_data(seat->text_درون_داد.zwp_text_درون_داد, seat);
            zwp_text_درون_داد_v3_add_listener(seat->text_درون_داد.zwp_text_درون_داد,
                                           &text_درون_داد_listener, seat);
        }
    }
}

تهی Wayland_Display_Init_Text_درون_داد_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_درون_داد(seat);
    }
}

// Pen/Tablet support...
ایستا تهی tablet_tool_handle_type(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    انتخاب (type) {
        #define CASE(typ) حالت ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; بازگشت
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        پیشفرض: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ایستا تهی tablet_tool_handle_hardware_serial(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ایستا تهی tablet_tool_handle_hardware_id_wacom(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

ایستا تهی tablet_tool_handle_capability(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    انتخاب (capability) {
        #define CASE(wltyp,sdltyp) حالت ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; بازگشت
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        پیشفرض: بشکن;  // unsupported here.
    }
}

ایستا تهی tablet_tool_handle_done(تهی *data, ساختار zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    اگر (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : پوچ;
        sdltool->instance_id = SDL_AddPenDevice(0, پوچ, window, &sdltool->info, sdltool, false);
    }
}

ایستا تهی tablet_tool_handle_removed(تهی *data, ساختار zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    اگر (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : پوچ;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ایستا تهی tablet_tool_handle_proximity_in(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t serial, ساختار zwp_tablet_v2 *tablet, ساختار wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : پوچ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : پوچ;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ایستا تهی tablet_tool_handle_proximity_out(تهی *data, ساختار zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

ایستا تهی tablet_tool_handle_down(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

ایستا تهی tablet_tool_handle_up(تهی *data, ساختار zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

ایستا تهی tablet_tool_handle_motion(تهی *data, ساختار zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    اگر (windowdata) {
        sdltool->frame.x = (اعشاری)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (اعشاری)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

ایستا تهی tablet_tool_handle_pressure(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((اعشاری) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    اگر (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

ایستا تهی tablet_tool_handle_distance(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((اعشاری) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    اگر (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ایستا تهی tablet_tool_handle_tilt(تهی *data, ساختار zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (اعشاری)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (اعشاری)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ایستا تهی tablet_tool_handle_button(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    صحیح sdlbutton;

    انتخاب (button) {
    حالت BTN_STYLUS:
        sdlbutton = 1;
        بشکن;
    حالت BTN_STYLUS2:
        sdlbutton = 2;
        بشکن;
    حالت BTN_STYLUS3:
        sdlbutton = 3;
        بشکن;
    پیشفرض:
        بازگشت;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

ایستا تهی tablet_tool_handle_rotation(تهی *data, ساختار zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ثابت اعشاری rotation = (اعشاری)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

ایستا تهی tablet_tool_handle_slider(تهی *data, ساختار zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

ایستا تهی tablet_tool_handle_wheel(تهی *data, ساختار zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ایستا تهی tablet_tool_handle_frame(تهی *data, ساختار zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    اگر (!instance_id) {
        بازگشت;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : پوچ;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    اگر (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    اگر (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        اگر (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } وگرنه {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } وگرنه {
        اگر (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        اگر (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    برای (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_شمار; i++) {
        اگر (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    برای (صحیح i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ثابت صحیح state = sdltool->frame.buttons[i];
        اگر (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    اگر (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = پوچ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

ایستا ثابت ساختار zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


ایستا تهی tablet_seat_handle_tablet_added(تهی *data, ساختار zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساختار zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ایستا تهی tablet_seat_handle_tool_added(تهی *data, ساختار zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساختار zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, اندازه(*sdltool));

    اگر (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.رقم_buttons = -1;

        اگر (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_درج(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ایستا تهی tablet_seat_handle_pad_added(تهی *data, ساختار zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساختار zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ایستا ثابت ساختار zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ایستا تهی Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

تهی Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ایستا تهی Wayland_remove_all_pens_callback(SDL_PenID instance_id, تهی *handle, تهی *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ایستا تهی Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    اگر (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } وگرنه {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, پوچ);
    }

    اگر (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = پوچ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

تهی Wayland_DisplayCreateSeat(SDL_VideoData *display, ساختار wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, اندازه(SDL_WaylandSeat));
    اگر (!seat) {
        بازگشت;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_درج(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_درون_داد(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    اگر (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

تهی Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        اگر (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        اگر (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = پوچ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            اگر (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->focus == window) {
                tool->focus = پوچ;
                Wayland_TabletToolUpdateCursor(tool);
                اگر (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            اگر (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                اگر (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

تهی Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    اگر (!seat) {
        بازگشت;
    }

    SDL_free(seat->name);

    اگر (seat->data_device) {
        اگر (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        اگر (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        اگر (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            اگر (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        اگر (seat->data_device->data_device) {
            اگر (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } وگرنه {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    اگر (seat->primary_selection_device) {
        اگر (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        اگر (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        اگر (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    اگر (seat->text_درون_داد.zwp_text_درون_داد) {
        zwp_text_درون_داد_v3_destroy(seat->text_درون_داد.zwp_text_درون_داد);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    اگر (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } وگرنه {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ایستا تهی Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    اگر (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        اگر (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            اگر (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                اگر (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } وگرنه {
                    relative_focus = seat->pointer.focus->keyboard_focus_شمار != 0;
                }
            } وگرنه {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        اگر (relative_focus) {
            اگر (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } وگرنه اگر (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = پوچ;
        }
    }
}

ایستا تهی Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    اگر (display->کلید_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        اگر (seat->keyboard.کلید_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
            seat->keyboard.کلید_inhibitor = پوچ;
        }

        اگر (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            اگر (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                اگر (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.کلید_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کلید_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

تهی Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    اگر (display->pointer_constraints) {
        اگر (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = پوچ;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        اگر (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            اگر (seat->pointer.relative_pointer) {
                اگر (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    اگر (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = پوچ;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, پوچ,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                بازگشت;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            اگر (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = پوچ;
            }

            SDL_WindowData *w = seat->pointer.focus;
            اگر (!w) {
                بازگشت;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            اگر (!(window->flags & SDL_WINDOW_درون_داد_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                بازگشت;
            }

            ساختار wl_region *confine_rect = پوچ;
            اگر (!SDL_RectEmpty(&window->mouse_rect)) {
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
                اگر (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحیح closest_x = seat->pointer.last_motion.x;
                    صحیح closest_y = seat->pointer.last_motion.y;

                    اگر (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } وگرنه اگر (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    اگر (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } وگرنه اگر (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            اگر (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                اگر (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } وگرنه {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                پوچ,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                اگر (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

تهی Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        اگر (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

تهی Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        اگر (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

تهی Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    اگر (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
