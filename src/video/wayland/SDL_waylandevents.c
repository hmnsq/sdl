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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"
#ضمن "../../core/linux/SDL_system_theme.h"
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "SDL_waylandmouse.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "SDL_waylandkeyboard.h"

#ضمن "pointer-constraints-unstable-v1-client-protocol.h"
#ضمن "relative-pointer-unstable-v1-client-protocol.h"
#ضمن "xdg-shell-client-protocol.h"
#ضمن "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ضمن "text-input-unstable-v3-client-protocol.h"
#ضمن "tablet-v2-client-protocol.h"
#ضمن "primary-selection-unstable-v1-client-protocol.h"
#ضمن "input-timestamps-unstable-v1-client-protocol.h"
#ضمن "pointer-gestures-unstable-v1-client-protocol.h"
#ضمن "cursor-shape-v1-client-protocol.h"
#ضمن "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_ماسوقن_LINUXEV
#ضمن <linux/input.h>
#وإلا
#define BTN_کيري    (0x110)
#define BTN_کانن   (0x111)
#define BTN_تڠه  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/imKStoUCS.h"
#ضمن <errno.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>
#ضمن <xkbcommon/xkbcommon-compose.h>
#ضمن <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_رنده  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_تيڠݢي (WAYLAND_TIMER_ROLLOVER_INTERVAL_رنده * 15U)

// Scoped function declarations
ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

تعريفنوع بنية
{
    Uint32 کونچي;
    SDL_Scancode scancode;
} Wayland_Reserved_کونچي;

تعريفنوع بنية
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    بنية wl_surface *surface;

    بنية wl_list link;
} SDL_WaylandTouchPoint;

ساكن فراغ Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(حجم(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_سيسيڤ(&seat->touch.points, &tp->link);
}

ساكن فراغ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    إذا (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        إذا (window_data) {
            ثابت عائم x = (عائم)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ثابت عائم y = (عائم)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_کيراءن;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_کيراءن &&
                !window_data->pointer_focus_کيراءن && !window_data->active_touch_کيراءن) {
                SDL_SetMouseFocus(عدم);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساكن فراغ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        إذا (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            إذا (surface) {
                *surface = tp->surface;
            }
            اكسر;
        }
    }
}

ساكن فراغ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, بنية wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        إذا (tp->id == id) {
            إذا (fx) {
                *fx = tp->fx;
            }
            إذا (fy) {
                *fy = tp->fy;
            }
            إذا (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            اكسر;
        }
    }
}

ساكن فراغ Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (صحيح)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (صحيح)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (صحيح)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (صحيح)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

ساكن Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    ساكن Uint64 timestamp_offset = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    إذا (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    إذا (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    أرجع nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساكن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساكن Uint64 timestamp_offset = 0;
    ساكن Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    إذا (wl_timestamp_ms >= last) {
        إذا (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_رنده && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_تيڠݢي) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } وإلا {
            last = wl_timestamp_ms;
        }
    } وإلا {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        إذا (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_رنده && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_تيڠݢي) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    أرجع timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ساكن Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن فراغ ماسوقن_timestamp_listener(فراغ *data, بنية zwp_ماسوقن_timestamps_v1 *zwp_ماسوقن_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

ساكن ثابت بنية zwp_ماسوقن_timestamps_v1_listener timestamp_listener = {
    ماسوقن_timestamp_listener
};

ساكن فراغ Wayland_Seat_Register_ماسوقن_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    إذا (seat->display->ماسوقن_timestamps_manager) {
        إذا (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ماسوقن_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ماسوقن_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ماسوقن_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        إذا (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_ماسوقن_timestamps_manager_v1_get_pointer_timestamps(seat->display->ماسوقن_timestamps_manager, seat->pointer.wl_pointer);
            zwp_ماسوقن_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        إذا (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ماسوقن_timestamps_manager_v1_get_touch_timestamps(seat->display->ماسوقن_timestamps_manager, seat->touch.wl_touch);
            zwp_ماسوقن_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

فراغ Wayland_Display_Init_ماسوقن_Timestamp_Manager(SDL_VideoData *display)
{
    إذا (display->ماسوقن_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_ماسوقن_Timestamp_Listeners(seat);
        }
    }
}

ساكن فراغ handle_pinch_begin(فراغ *data, بنية zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, بنية wl_surface *surface, uint32_t fingers)
{
    إذا (!surface) {
        أرجع;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    إذا (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_update(فراغ *data, بنية zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    إذا (seat->pointer.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ثابت عائم s = (عائم)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_end(فراغ *data, بنية zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    إذا (seat->pointer.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = عدم;
    }
}

ساكن ثابت بنية zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

ساكن فراغ Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    إذا (seat->display->zwp_pointer_gestures) {
        إذا (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

فراغ Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

ساكن فراغ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    إذا (seat->display->cursor_shape_manager) {
        إذا (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            إذا (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

فراغ Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ساكن فراغ Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    إذا (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.اڠک_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساكن فراغ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    طالما (elapsed >= repeat_info->next_repeat_ns) {
        إذا (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_کونچي_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->کونچي, repeat_info->scancode, true);
        }
        إذا (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

ساكن فراغ keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کونچي, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ثابت حرف *text)
{
    إذا (!repeat_info->repeat_rate) {
        أرجع;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کونچي = کونچي;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    إذا (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } وإلا {
        repeat_info->text[0] = '\0';
    }
}

ساكن فراغ sync_done_handler(فراغ *data, بنية wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener sync_listener = {
    sync_done_handler
};

فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    بنية wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, عدم);
    WAYLAND_wl_display_flush(d->display);
}

صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->text_ماسوقن_manager && keyboard_focus && SDL_Text_ماسوقن_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        إذا (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->keyboard.repeat.کونچي) {
            ثابت Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ثابت Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            إذا (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    إذا (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        إذا (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            إذا (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        إذا (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            أرجع errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        إذا (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            إذا (ret == 0) {
                أرجع poll_alarm_set ? 1 : 0;
            } وإلا {
                // Pump events on an interrupt or broken pipe to handle the error.
                أرجع errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        إذا (ret == -1) {
            أرجع ret;
        }
    }

    // Signal to the caller that there might be an event available.
    أرجع 1;
}

فراغ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->text_ماسوقن_manager && keyboard_focus && SDL_Text_ماسوقن_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    إذا (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    إذا (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        إذا (ret < 0) {
            اذهب connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    إذا (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        إذا (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            إذا (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        إذا (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            اذهب connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        إذا (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            إذا (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } وإلا {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } وإلا {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    إذا (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (seat->keyboard.repeat.کونچي) {
                Wayland_SeatSetKeymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    إذا (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساكن فراغ pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : عدم;

    إذا (window_data) {
        مزدوج sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        مزدوج sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        إذا (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (مزدوج)window_data->mask.offset_x;
            sy += (مزدوج)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        إذا (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (عائم)sx, (عائم)sy);
        } وإلا {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (عائم)sx, (عائم)sy);
        }

        seat->pointer.last_motion.x = (صحيح)SDL_floor(sx);
        seat->pointer.last_motion.y = (صحيح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        إذا (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        إذا (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            بدل (rc) {
            حالة SDL_HITTEST_RESIZE_TOPLEFT:
                إذا ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_اتس) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کيري)) {
                    rc = SDL_HITTEST_NORMAL;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_اتس) {
                    rc = SDL_HITTEST_RESIZE_کيري;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کيري) {
                    rc = SDL_HITTEST_RESIZE_اتس;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_اتس:
                إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_اتس) {
                    rc = SDL_HITTEST_NORMAL;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                إذا ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_اتس) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کانن)) {
                    rc = SDL_HITTEST_NORMAL;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_اتس) {
                    rc = SDL_HITTEST_RESIZE_کانن;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کانن) {
                    rc = SDL_HITTEST_RESIZE_اتس;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_کانن:
                إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کانن) {
                    rc = SDL_HITTEST_NORMAL;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                إذا ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کانن)) {
                    rc = SDL_HITTEST_NORMAL;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_کانن;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کانن) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOM:
                إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                إذا ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کيري)) {
                    rc = SDL_HITTEST_NORMAL;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_کيري;
                } وإلا إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کيري) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_کيري:
                إذا (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کيري) {
                    rc = SDL_HITTEST_NORMAL;
                }
                اكسر;
            افتراضي:
                اكسر;
            }

            إذا (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

ساكن فراغ pointer_handle_motion(فراغ *data, بنية wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ثابت Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    إذا (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        إذا (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } وإلا {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

ساكن فراغ pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    إذا (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        أرجع;
    }

    إذا (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        أرجع;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_کيراءن;
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

ساكن فراغ pointer_handle_enter(فراغ *data, بنية wl_pointer *pointer,
                                 uint32_t serial, بنية wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
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

    إذا (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

ساكن فراغ pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    إذا (window) {
        إذا (seat->pointer.focus) {
            إذا (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = عدم;
                seat->pointer.focus_surface = عدم;
                لكل (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    إذا (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                إذا (!--window->pointer_focus_کيراءن && had_focus && !window->active_touch_کيراءن) {
                    SDL_SetMouseFocus(عدم);
                }

                إذا (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } وإلا إذا (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساكن فراغ pointer_handle_leave(فراغ *data, بنية wl_pointer *pointer,
                                 uint32_t serial, بنية wl_surface *surface)
{
    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    إذا (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

ساكن bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    إذا (seat->pointer.locked_pointer) {
        أرجع false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    إذا (window->hit_test) {
        ساكن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_اتس_کيري, XDG_TOPLEVEL_RESIZE_EDGE_اتس,
            XDG_TOPLEVEL_RESIZE_EDGE_اتس_کانن, XDG_TOPLEVEL_RESIZE_EDGE_کانن,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_کانن, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_کيري, XDG_TOPLEVEL_RESIZE_EDGE_کيري
        };

#ifdef HAVE_LIBDECOR_H
        ساكن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_اتس_کيري, LIBDECOR_RESIZE_EDGE_اتس,
            LIBDECOR_RESIZE_EDGE_اتس_کانن, LIBDECOR_RESIZE_EDGE_کانن,
            LIBDECOR_RESIZE_EDGE_BOTTOM_کانن, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_کيري, LIBDECOR_RESIZE_EDGE_کيري
        };
#endif

        بدل (window_data->hit_test_result) {
        حالة SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            إذا (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } وإلا
#endif
                إذا (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_اتس:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_کانن:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_کيري:
#ifdef HAVE_LIBDECOR_H
            إذا (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وإلا
#endif
                إذا (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    إذا (window) {
        bool ignore_click = false;

        إذا (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            إذا (sdl_button == SDL_BUTTON_کيري && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                أرجع; // don't pass this event on to app.
            }
        } وإلا {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        إذا (window->last_focus_event_time_ns) {
            إذا (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        إذا (!seat->pointer.relative_pointer) {
            إذا (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } وإلا {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                إذا (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        إذا (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

ساكن فراغ pointer_handle_button(فراغ *data, بنية wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    بدل (button) {
    حالة BTN_کيري:
        sdl_button = SDL_BUTTON_کيري;
        اكسر;
    حالة BTN_تڠه:
        sdl_button = SDL_BUTTON_تڠه;
        اكسر;
    حالة BTN_کانن:
        sdl_button = SDL_BUTTON_کانن;
        اكسر;
    افتراضي:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        اكسر;
    }

    إذا (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    إذا (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        إذا (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } وإلا {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } وإلا {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساكن فراغ pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t نيلاي)
{
    SDL_WindowData *window = seat->pointer.focus;
    ثابت تعداد wl_pointer_axis a = axis;

    إذا (seat->pointer.focus) {
        عائم x, y;

        بدل (a) {
        حالة WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (عائم)wl_fixed_to_double(نيلاي);
            اكسر;
        حالة WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (عائم)wl_fixed_to_double(نيلاي);
            y = 0;
            اكسر;
        افتراضي:
            أرجع;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

ساكن فراغ pointer_handle_axis_common(SDL_WaylandSeat *seat, تعداد SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t نيلاي)
{
    ثابت تعداد wl_pointer_axis a = axis;

    إذا (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        بدل (a) {
        حالة WL_POINTER_AXIS_VERTICAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (عائم)wl_fixed_to_double(نيلاي);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (عائم)wl_fixed_to_double(نيلاي);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (عائم)wl_fixed_to_double(نيلاي);
                }
                اكسر;
            }
            اكسر;
        حالة WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (عائم)wl_fixed_to_double(نيلاي);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (عائم)wl_fixed_to_double(نيلاي);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (عائم)wl_fixed_to_double(نيلاي);
                }
                اكسر;
            }
            اكسر;
        }
    }
}

ساكن فراغ pointer_handle_axis(فراغ *data, بنية wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t نيلاي)
{
    SDL_WaylandSeat *seat = data;
    ثابت Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    إذا (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, نيلاي);
    } وإلا {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, نيلاي);
    }
}

ساكن فراغ pointer_handle_axis_relative_direction(فراغ *data, بنية wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    بدل (axis_relative_direction) {
    حالة WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        اكسر;
    حالة WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        اكسر;
    }
}

ساكن فراغ pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    إذا (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        مزدوج dx;
        مزدوج dy;
        إذا (mouse->ماسوقن_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } وإلا {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (عائم)dx, (عائم)dy);
    }
}

ساكن فراغ pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    عائم x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    بدل (seat->pointer.pending_frame.axis.x_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        اكسر;
    افتراضي:
        x = 0.0f;
        اكسر;
    }

    بدل (seat->pointer.pending_frame.axis.y_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        اكسر;
    افتراضي:
        y = 0.0f;
        اكسر;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

ساكن فراغ pointer_handle_frame(فراغ *data, بنية wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    إذا (seat->pointer.pending_frame.enter_surface) {
        إذا (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            إذا (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = عدم;
                seat->pointer.pending_frame.leave_surface = عدم;
            } وإلا {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = عدم;
            }
        }

        إذا (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    إذا (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    إذا (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    لكل (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ثابت Uint32 mask = SDL_BUTTON_MASK(i);
        إذا (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        إذا (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    إذا (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    إذا (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

ساكن فراغ pointer_handle_axis_source(فراغ *data, بنية wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

ساكن فراغ pointer_handle_axis_stop(فراغ *data, بنية wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

ساكن فراغ pointer_handle_axis_discrete(فراغ *data, بنية wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساكن فراغ pointer_handle_axis_value120(فراغ *data, بنية wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساكن فراغ pointer_handle_warp(فراغ *data, بنية wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

ساكن ثابت بنية wl_pointer_listener pointer_listener = {
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

ساكن فراغ relative_pointer_handle_relative_motion(فراغ *data,
                                                    بنية zwp_relative_pointer_v1 *pointer,
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

    إذا (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } وإلا {
        pointer_dispatch_relative_motion(seat);
    }
}

ساكن ثابت بنية zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

ساكن فراغ locked_pointer_locked(فراغ *data, بنية zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ساكن فراغ locked_pointer_unlocked(فراغ *data, بنية zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ساكن ثابت بنية zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

ساكن فراغ confined_pointer_confined(فراغ *data, بنية zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ساكن فراغ confined_pointer_unconfined(فراغ *data, بنية zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ساكن ثابت بنية zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

ساكن فراغ touch_handler_down(فراغ *data, بنية wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, بنية wl_surface *surface,
                               صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    إذا (!surface) {
        أرجع;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    إذا (window_data && window_data->surface == surface) {
        عائم x, y;

        إذا (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } وإلا {
            x = (عائم)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        إذا (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } وإلا {
            y = (عائم)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_کيراءن;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

ساكن فراغ touch_handler_up(فراغ *data, بنية wl_touch *touch, uint32_t serial, uint32_t timestamp, صحيح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    بنية wl_surface *surface = عدم;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    إذا (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        إذا (window_data && window_data->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ثابت عائم y = (عائم)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_کيراءن;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_کيراءن &&
                !window_data->pointer_focus_کيراءن && !window_data->active_touch_کيراءن) {
                SDL_SetMouseFocus(عدم);
            }
        }
    }
}

ساكن فراغ touch_handler_motion(فراغ *data, بنية wl_touch *touch, uint32_t timestamp, صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    بنية wl_surface *surface = عدم;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    إذا (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        إذا (window_data && window_data->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ثابت عائم y = (عائم)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

ساكن فراغ touch_handler_frame(فراغ *data, بنية wl_touch *touch)
{
}

ساكن فراغ touch_handler_cancel(فراغ *data, بنية wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ساكن فراغ touch_handler_shape(فراغ *data, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ساكن فراغ touch_handler_orientation(فراغ *data, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ساكن ثابت بنية wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#إذا !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
ساكن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کونچي, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    إذا (!masks_out || !masks_size) {
        أرجع 0;
    }

    // Level 0 is always unmodified, so early out.
    إذا (level == 0) {
        *masks_out = 0;
        أرجع 1;
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

    لكل (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        إذا (WAYLAND_xkb_state_کونچي_get_level(seat->keyboard.xkb.state, کونچي, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            إذا (++mask_idx == masks_size) {
                اكسر;
            }
        }
    }

    أرجع mask_idx;
}
#endif

ساكن فراغ Wayland_KeymapIterator(بنية xkb_keymap *keymap, xkb_keycode_t کونچي, فراغ *data)
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
    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, کونچي - 8);
    }

    لكل (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.اڠک_layouts; ++layout) {
        ثابت xkb_level_index_t اڠک_levels = WAYLAND_xkb_keymap_اڠک_levels_for_کونچي(seat->keyboard.xkb.keymap, کونچي, layout);
        لكل (xkb_level_index_t level = 0; level < اڠک_levels; ++level) {
            إذا (WAYLAND_xkb_keymap_کونچي_get_syms_by_level(seat->keyboard.xkb.keymap, کونچي, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                إذا (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_کونچي_Sym(syms[0], کونچي);
                    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                        استمر;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#إذا SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ثابت size_t اڠک_masks = WAYLAND_xkb_keymap_کونچي_get_mods_for_level(seat->keyboard.xkb.keymap, کونچي, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وإلا
                ثابت size_t اڠک_masks = xkb_legacy_get_mods_for_level(seat, کونچي, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                لكل (size_t mask = 0; mask < اڠک_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    إذا ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        استمر;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کونچي_Code_From_کونچي_Sym(syms[0], کونچي, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    إذا (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        إذا (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کونچي *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_کونچي));
                        إذا (res) {
                            res->scancode = scancode;
                            res->کونچي = کونچي - 8;
                        }
                    }

                    إذا (!keycode) {
                        بدل (scancode) {
                        حالة SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            اكسر;
                        حالة SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            اكسر;
                        حالة SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            اكسر;
                        حالة SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            اكسر;
                        افتراضي:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            اكسر;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساكن فراغ keyboard_handle_keymap(فراغ *data, بنية wl_keyboard *keyboard,
                                   uint32_t format, صحيح fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    حرف *map_str;

    إذا (!data) {
        close(fd);
        أرجع;
    }

    إذا (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        أرجع;
    }

    map_str = mmap(عدم, size, PROT_READ, MAP_PRIVATE, fd, 0);
    إذا (map_str == MAP_FAILED) {
        close(fd);
        أرجع;
    }

    إذا (seat->keyboard.xkb.keymap != عدم) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = عدم;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    إذا (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        أرجع;
    }

    // Clear the old layouts.
    لكل (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.اڠک_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = عدم;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.اڠک_layouts = 0;

#إذا SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.اڠک_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_اڠک);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وإلا
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.اڠک_mask = 1 << GET_MOD_INDEX(اڠک_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    إذا (seat->keyboard.xkb.state != عدم) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = عدم;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    إذا (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = عدم;
        أرجع;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == عدم;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.اڠک_layouts = WAYLAND_xkb_keymap_اڠک_layouts(seat->keyboard.xkb.keymap);
    إذا (seat->keyboard.xkb.اڠک_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.اڠک_layouts, حجم(SDL_Keymap *));
        إذا (!seat->keyboard.sdl_keymap) {
            أرجع;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        لكل (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.اڠک_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            إذا (!seat->keyboard.sdl_keymap[i]) {
                لكل (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = عدم;
                أرجع;
            }
        }

        WAYLAND_xkb_keymap_کونچي_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.اڠک_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ثابت حرف *locale = SDL_getenv("LC_ALL");
    إذا (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        إذا (!locale) {
            locale = SDL_getenv("LANG");
            إذا (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    إذا (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        إذا (seat->keyboard.xkb.compose_table != عدم) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = عدم;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        إذا (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            إذا (seat->keyboard.xkb.compose_state != عدم) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = عدم;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            إذا (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = عدم;
            }
        }
    } وإلا إذا (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ساكن SDL_Scancode Wayland_Get_Scancode_For_کونچي(SDL_WaylandSeat *seat, Uint32 کونچي, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, کونچي);

        // No table entry? Check the reserved list.
        إذا (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_کونچي *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                إذا (i->کونچي == کونچي) {
                    أرجع i->scancode;
                }
            }
        }
    } وإلا {
        ثابت xkb_keysym_t *keysym;
        إذا (WAYLAND_xkb_state_کونچي_get_syms(seat->keyboard.xkb.state, کونچي + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_کونچي_Sym(keysym[0], کونچي + 8);
            إذا (syms) {
                *syms = keysym;
            }
        }
    }

    أرجع scancode;
}

ساكن فراغ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool کونچي_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    إذا (!کونچي_pressed) {
        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } وإلا {
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

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    إذا (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.اڠک_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_اڠک;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_اڠک;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساكن فراغ Wayland_Handle_Modifier_کونچي_سموا(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کونچي_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    بدل (keycode) {
    حالة SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        اكسر;
    حالة SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        اكسر;
    حالة SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        اكسر;
    حالة SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        اكسر;
    حالة SDLK_LALT:
        mod = SDL_KMOD_LALT;
        اكسر;
    حالة SDLK_RALT:
        mod = SDL_KMOD_RALT;
        اكسر;
    حالة SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        اكسر;
    حالة SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        اكسر;
    حالة SDLK_MODE:
        mod = SDL_KMOD_MODE;
        اكسر;
    حالة SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        اكسر;
    افتراضي:
        أرجع;
    }

    إذا (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } وإلا {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ساكن فراغ keyboard_handle_enter(فراغ *data, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface,
                                  بنية wl_array *کونچي_سموا)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *کونچي;

    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    إذا (!window) {
        // Not a surface owned by SDL.
        أرجع;
    }

    ++window->keyboard_focus_کيراءن;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ماسوقن(seat);

#ifdef SDL_USE_IME
    إذا (!seat->text_ماسوقن.zwp_text_ماسوقن) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (کونچي, کونچي_سموا) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_کونچي(seat, *کونچي, عدم);
        إذا (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_کونچي_From_Scancode(scancode, SDL_KMOD_NONE, false);

            بدل (keycode) {
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_MODE:
            حالة SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_کونچي_سموا(seat, scancode, true);
                SDL_Send_Keyboard_کونچي_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کونچي, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        }
    }
}

ساكن فراغ keyboard_handle_leave(فراغ *data, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    إذا (!window) {
        // Not a surface owned by SDL.
        أرجع;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کونچي = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    طالما (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ثابت bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = عدم;
    --window->keyboard_focus_کيراءن;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    إذا (!window->keyboard_focus_کيراءن && had_focus) {
        SDL_SetKeyboardFocus(عدم);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ماسوقن(seat);

#ifdef SDL_USE_IME
    إذا (!seat->text_ماسوقن.zwp_text_ماسوقن && !window->keyboard_focus_کيراءن) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    إذا (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_کيراءن && !window->active_touch_کيراءن) {
        SDL_SetMouseFocus(عدم);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, عدم);
}

ساكن bool keyboard_ماسوقن_get_text(حرف text[8], ثابت SDL_WaylandSeat *seat, uint32_t کونچي, bool down, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    إذا (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        أرجع false;
    }

    // TODO: Can this happen?
    إذا (WAYLAND_xkb_state_کونچي_get_syms(seat->keyboard.xkb.state, کونچي + 8, &syms) != 1) {
        أرجع false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    إذا (SDL_IME_Process_کونچي_Event(sym, کونچي + 8, down)) {
        إذا (handled_by_ime) {
            *handled_by_ime = true;
        }
        أرجع true;
    }
#endif

    إذا (!down) {
        أرجع false;
    }

    إذا (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        بدل (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        حالة XKB_COMPOSE_COMPOSING:
            إذا (handled_by_ime) {
                *handled_by_ime = true;
            }
            أرجع true;
        حالة XKB_COMPOSE_CANCELLED:
        افتراضي:
            sym = XKB_کونچي_No_سيمبول;
            اكسر;
        حالة XKB_COMPOSE_NOTHING:
            اكسر;
        حالة XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            اكسر;
        }
    }

    أرجع WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

ساكن فراغ keyboard_handle_کونچي(فراغ *data, بنية wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t کونچي,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    تعداد wl_keyboard_کونچي_state state = state_w;
    حرف text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    إذا (state == WL_KEYBOARD_کونچي_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        إذا (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کونچي_repeats(seat->keyboard.xkb.keymap, کونچي + 8)) {
            أرجع;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کونچي_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    إذا (state == WL_KEYBOARD_کونچي_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        إذا (keyboard_focus && SDL_Text_ماسوقن_Active(keyboard_focus)) {
            has_text = keyboard_ماسوقن_get_text(text, seat, کونچي, true, &handled_by_ime);
        }
    } وإلا {
        إذا (کونچي == seat->keyboard.repeat.کونچي) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کونچي = 0;
        }
        keyboard_ماسوقن_get_text(text, seat, کونچي, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = عدم;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کونچي(seat, کونچي, &syms);
    Wayland_Handle_Modifier_کونچي_سموا(seat, scancode, state == WL_KEYBOARD_کونچي_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    إذا (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کونچي_Sym_To_Ucs4(syms[0]);
        إذا (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_کونچي_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, کونچي, scancode, state == WL_KEYBOARD_کونچي_STATE_PRESSED);

    إذا (state == WL_KEYBOARD_کونچي_STATE_PRESSED) {
        إذا (handled_by_ime) {
            has_text = false;
        }
        إذا (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        إذا (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_کونچي_repeats(seat->keyboard.xkb.keymap, کونچي + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, کونچي, time, timestamp_ns, scancode, has_text ? text : عدم);
        }
    }
}

ساكن فراغ keyboard_handle_modifiers(فراغ *data, بنية wl_keyboard *keyboard,
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
    إذا (!seat->keyboard.xkb.state) {
        أرجع;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    إذا (seat->keyboard.repeat.کونچي) {
        حرف text[8];

        إذا (keyboard_ماسوقن_get_text(text, seat, seat->keyboard.repeat.کونچي, true, عدم)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    إذا (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        إذا (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ساكن فراغ keyboard_handle_repeat_info(فراغ *data, بنية wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    إذا (!rate) {
        seat->keyboard.repeat.کونچي = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ساكن ثابت بنية wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_کونچي,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ساكن فراغ Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    إذا (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    إذا (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = عدم;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    إذا (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    إذا (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    إذا (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    إذا (seat->pointer.timestamps) {
        zwp_ماسوقن_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    إذا (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    إذا (seat->pointer.wl_pointer) {
        إذا (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } وإلا {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

ساكن فراغ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    إذا (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    إذا (seat->keyboard.sdl_keymap) {
        إذا (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.اڠک_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        لكل (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.اڠک_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = عدم;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    إذا (seat->keyboard.کونچي_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کونچي_inhibitor);
    }

    إذا (seat->keyboard.timestamps) {
        zwp_ماسوقن_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    إذا (seat->keyboard.wl_keyboard) {
        إذا (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } وإلا {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    إذا (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    إذا (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    إذا (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    إذا (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ساكن فراغ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    إذا (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    إذا (seat->touch.timestamps) {
        zwp_ماسوقن_timestamps_v1_destroy(seat->touch.timestamps);
    }

    إذا (seat->touch.wl_touch) {
        إذا (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } وإلا {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ساكن فراغ seat_handle_capabilities(فراغ *data, بنية wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    حرف name_fmt[256];

    إذا ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_ماسوقن_Timestamp_Listeners(seat);
}

ساكن فراغ seat_handle_name(فراغ *data, بنية wl_seat *wl_seat, ثابت حرف *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    إذا (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ساكن ثابت بنية wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ساكن فراغ data_offer_handle_offer(فراغ *data, بنية wl_data_offer *wl_data_offer,
                                    ثابت حرف *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

ساكن فراغ data_offer_handle_source_actions(فراغ *data, بنية wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

ساكن فراغ data_offer_handle_actions(فراغ *data, بنية wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

ساكن ثابت بنية wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

ساكن فراغ primary_selection_offer_handle_offer(فراغ *data, بنية zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ساكن ثابت بنية zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ساكن فراغ data_device_handle_data_offer(فراغ *data, بنية wl_data_device *wl_data_device,
                                          بنية wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, حجم(*data_offer));
    إذا (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
    }
}

ساكن فراغ data_device_handle_enter(فراغ *data, بنية wl_data_device *wl_data_device,
                                     uint32_t serial, بنية wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, بنية wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : عدم;
    data_device->has_mime_file = false;
    data_device->text_mime_type = عدم;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    إذا (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    إذا (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        إذا (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        إذا (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        إذا (!data_device->has_mime_file) {
            size_t mime_کيراءن = 0;
            ثابت حرف *ثابت *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_کيراءن);
            لكل (size_t i = 0; i < mime_کيراءن; ++i) {
                إذا (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    اكسر;
                }
            }
        }

        إذا (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            إذا (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            مزدوج dx = wl_fixed_to_double(x);
            مزدوج dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            إذا (surface == window->mask.surface) {
                dx += (مزدوج)window->mask.offset_x;
                dy += (مزدوج)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (عائم)dx, (عائم)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } وإلا {
            // Decline the offer.
            wl_data_offer_accept(id, serial, عدم);
            إذا (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } وإلا {
        data_device->dnd_window = عدم;
        data_device->dnd_surface = عدم;

        // Decline the offer.
        إذا (id) {
            wl_data_offer_accept(id, serial, عدم);
            إذا (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

ساكن فراغ data_device_handle_leave(فراغ *data, بنية wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    إذا (data_device->drag_offer) {
        إذا (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } وإلا {
            SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = عدم;
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = عدم;
}

ساكن فراغ data_device_handle_motion(فراغ *data, بنية wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    إذا (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        مزدوج dx = wl_fixed_to_double(x);
        مزدوج dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        إذا (data_device->dnd_surface == window_data->mask.surface) {
            dx += (مزدوج)window_data->mask.offset_x;
            dy += (مزدوج)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (عائم)dx, (عائم)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

ساكن فراغ drop_cleanup_handler(فراغ *data, بنية wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ساكن ثابت بنية wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ساكن فراغ drop_dispatch_handler(فراغ *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    إذا (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        إذا (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            فراغ *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            إذا (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                إذا (dbus) {
                    صحيح path_کيراءن = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_کيراءن);
                    // If dropped files contain a directory the list is empty
                    إذا (paths && path_کيراءن > 0) {
                        لكل (صحيح i = 0; i < path_کيراءن; i++) {
                            SDL_SendDropFile(drop->dnd_window, عدم, paths[i]);
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
        إذا (!drop_handled) {
            إذا (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                فراغ *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                إذا (buffer) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)buffer, "\r\n", &saveptr);
                    طالما (token) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } وإلا إذا (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                فراغ *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                إذا (buffer) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)buffer, "\r\n", &saveptr);
                    طالما (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        إذا (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = عدم;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساكن فراغ data_device_handle_drop(فراغ *data, بنية wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    إذا (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, حجم(Wayland_DropData));
        إذا (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_سيسيڤ(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } وإلا {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = عدم;
}

ساكن فراغ data_device_handle_selection(فراغ *data, بنية wl_data_device *wl_data_device,
                                         بنية wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = عدم;

    إذا (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

ساكن ثابت بنية wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

ساكن فراغ primary_selection_device_handle_offer(فراغ *data, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, حجم(*primary_selection_offer));
    إذا (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن فراغ primary_selection_device_handle_selection(فراغ *data, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = عدم;

    إذا (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    إذا (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ماسوقن,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن ثابت بنية zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساكن فراغ text_ماسوقن_enter(فراغ *data,
                             بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ text_ماسوقن_leave(فراغ *data,
                             بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ text_ماسوقن_preedit_string(فراغ *data,
                                      بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                                      ثابت حرف *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_ماسوقن.has_preedit = true;
    إذا (text) {
        صحيح cursor_begin_utf8 = cursor_begin >= 0 ? (صحيح)SDL_utf8strnlen(text, cursor_begin) : -1;
        صحيح cursor_end_utf8 = cursor_end >= 0 ? (صحيح)SDL_utf8strnlen(text, cursor_end) : -1;
        صحيح cursor_size_utf8;
        إذا (cursor_end_utf8 >= 0) {
            إذا (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } وإلا {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } وإلا {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } وإلا {
        SDL_SendEditingText("", 0, 0);
    }
}

ساكن فراغ text_ماسوقن_commit_string(فراغ *data,
                                     بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                                     ثابت حرف *text)
{
    SDL_SendKeyboardText(text);
}

ساكن فراغ text_ماسوقن_delete_surrounding_text(فراغ *data,
                                               بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

ساكن فراغ text_ماسوقن_done(فراغ *data,
                            بنية zwp_text_ماسوقن_v3 *zwp_text_ماسوقن_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    إذا (!seat->text_ماسوقن.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_ماسوقن.has_preedit = false;
}

ساكن ثابت بنية zwp_text_ماسوقن_v3_listener text_ماسوقن_listener = {
    text_ماسوقن_enter,
    text_ماسوقن_leave,
    text_ماسوقن_preedit_string,
    text_ماسوقن_commit_string,
    text_ماسوقن_delete_surrounding_text,
    text_ماسوقن_done
};

ساكن فراغ Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    إذا (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        إذا (dbus) {
            ثابت حرف *id = dbus->bus_get_unique_name(dbus->session_conn);
            إذا (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    إذا (!data_device->id_str)
#endif
    {
        حرف id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, حجم(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

ساكن فراغ Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->data_device_manager) {
        أرجع;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, حجم(*data_device));
    إذا (!data_device) {
        أرجع;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    إذا (!data_device->data_device) {
        SDL_free(data_device);
        أرجع;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

فراغ Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

ساكن فراغ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->primary_selection_device_manager) {
        أرجع;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, حجم(*primary_selection_device));
    إذا (!primary_selection_device) {
        أرجع;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    إذا (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } وإلا {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ساكن فراغ Wayland_Seat_Create_Text_ماسوقن(SDL_WaylandSeat *seat)
{
    إذا (seat->display->text_ماسوقن_manager) {
        seat->text_ماسوقن.zwp_text_ماسوقن = zwp_text_ماسوقن_manager_v3_get_text_ماسوقن(seat->display->text_ماسوقن_manager, seat->wl_seat);

        إذا (seat->text_ماسوقن.zwp_text_ماسوقن) {
            zwp_text_ماسوقن_v3_set_user_data(seat->text_ماسوقن.zwp_text_ماسوقن, seat);
            zwp_text_ماسوقن_v3_add_listener(seat->text_ماسوقن.zwp_text_ماسوقن,
                                           &text_ماسوقن_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_Text_ماسوقن_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_ماسوقن(seat);
    }
}

// Pen/Tablet support...
ساكن فراغ tablet_tool_handle_type(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    بدل (type) {
        #define CASE(typ) حالة ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; أرجع
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        افتراضي: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ساكن فراغ tablet_tool_handle_hardware_serial(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ساكن فراغ tablet_tool_handle_hardware_id_wacom(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

ساكن فراغ tablet_tool_handle_capability(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    بدل (capability) {
        #define CASE(wltyp,sdltyp) حالة ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; أرجع
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        افتراضي: اكسر;  // unsupported here.
    }
}

ساكن فراغ tablet_tool_handle_done(فراغ *data, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    إذا (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        sdltool->instance_id = SDL_AddPenDevice(0, عدم, window, &sdltool->info, sdltool, false);
    }
}

ساكن فراغ tablet_tool_handle_removed(فراغ *data, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    إذا (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساكن فراغ tablet_tool_handle_proximity_in(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, بنية zwp_tablet_v2 *tablet, بنية wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : عدم;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : عدم;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساكن فراغ tablet_tool_handle_proximity_out(فراغ *data, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

ساكن فراغ tablet_tool_handle_down(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

ساكن فراغ tablet_tool_handle_up(فراغ *data, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

ساكن فراغ tablet_tool_handle_motion(فراغ *data, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    إذا (windowdata) {
        sdltool->frame.x = (عائم)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (عائم)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

ساكن فراغ tablet_tool_handle_pressure(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((عائم) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    إذا (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

ساكن فراغ tablet_tool_handle_distance(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((عائم) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    إذا (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساكن فراغ tablet_tool_handle_tilt(فراغ *data, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (عائم)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (عائم)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ساكن فراغ tablet_tool_handle_button(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    صحيح sdlbutton;

    بدل (button) {
    حالة BTN_STYLUS:
        sdlbutton = 1;
        اكسر;
    حالة BTN_STYLUS2:
        sdlbutton = 2;
        اكسر;
    حالة BTN_STYLUS3:
        sdlbutton = 3;
        اكسر;
    افتراضي:
        أرجع;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

ساكن فراغ tablet_tool_handle_rotation(فراغ *data, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ثابت عائم rotation = (عائم)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساكن فراغ tablet_tool_handle_slider(فراغ *data, بنية zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساكن فراغ tablet_tool_handle_wheel(فراغ *data, بنية zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساكن فراغ tablet_tool_handle_frame(فراغ *data, بنية zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    إذا (!instance_id) {
        أرجع;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    إذا (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    إذا (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        إذا (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } وإلا {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } وإلا {
        إذا (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        إذا (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    لكل (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_کيراءن; i++) {
        إذا (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    لكل (صحيح i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ثابت صحيح state = sdltool->frame.buttons[i];
        إذا (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    إذا (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = عدم;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

ساكن ثابت بنية zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


ساكن فراغ tablet_seat_handle_tablet_added(فراغ *data, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ساكن فراغ tablet_seat_handle_tool_added(فراغ *data, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, حجم(*sdltool));

    إذا (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.اڠک_buttons = -1;

        إذا (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_سيسيڤ(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ساكن فراغ tablet_seat_handle_pad_added(فراغ *data, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ساكن ثابت بنية zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ساكن فراغ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

فراغ Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ساكن فراغ Wayland_remove_all_pens_callback(SDL_PenID instance_id, فراغ *handle, فراغ *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ساكن فراغ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    إذا (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } وإلا {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, عدم);
    }

    إذا (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = عدم;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

فراغ Wayland_DisplayCreateSeat(SDL_VideoData *display, بنية wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, حجم(SDL_WaylandSeat));
    إذا (!seat) {
        أرجع;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_سيسيڤ(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_ماسوقن(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    إذا (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

فراغ Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        إذا (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        إذا (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = عدم;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            إذا (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == window) {
                tool->focus = عدم;
                Wayland_TabletToolUpdateCursor(tool);
                إذا (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            إذا (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                إذا (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    إذا (!seat) {
        أرجع;
    }

    SDL_free(seat->name);

    إذا (seat->data_device) {
        إذا (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        إذا (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        إذا (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            إذا (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        إذا (seat->data_device->data_device) {
            إذا (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } وإلا {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    إذا (seat->primary_selection_device) {
        إذا (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        إذا (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        إذا (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    إذا (seat->text_ماسوقن.zwp_text_ماسوقن) {
        zwp_text_ماسوقن_v3_destroy(seat->text_ماسوقن.zwp_text_ماسوقن);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    إذا (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } وإلا {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساكن فراغ Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    إذا (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        إذا (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            إذا (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                إذا (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } وإلا {
                    relative_focus = seat->pointer.focus->keyboard_focus_کيراءن != 0;
                }
            } وإلا {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        إذا (relative_focus) {
            إذا (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } وإلا إذا (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = عدم;
        }
    }
}

ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    إذا (display->کونچي_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        إذا (seat->keyboard.کونچي_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کونچي_inhibitor);
            seat->keyboard.کونچي_inhibitor = عدم;
        }

        إذا (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            إذا (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                إذا (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.کونچي_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کونچي_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

فراغ Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    إذا (display->pointer_constraints) {
        إذا (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = عدم;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        إذا (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            إذا (seat->pointer.relative_pointer) {
                إذا (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    إذا (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = عدم;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, عدم,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                أرجع;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            إذا (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = عدم;
            }

            SDL_WindowData *w = seat->pointer.focus;
            إذا (!w) {
                أرجع;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            إذا (!(window->flags & SDL_WINDOW_ماسوقن_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                أرجع;
            }

            بنية wl_region *confine_rect = عدم;
            إذا (!SDL_RectEmpty(&window->mouse_rect)) {
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
                إذا (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحيح closest_x = seat->pointer.last_motion.x;
                    صحيح closest_y = seat->pointer.last_motion.y;

                    إذا (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } وإلا إذا (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    إذا (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } وإلا إذا (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            إذا (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                إذا (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } وإلا {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                عدم,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                إذا (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

فراغ Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    إذا (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
