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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ "../../core/unix/SDL_poll.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_scancode_tables_c.h"
#અન્તર્ભાવ "../../events/SDL_keysym_to_keycode_c.h"
#અન્તર્ભાવ "../../core/linux/SDL_system_theme.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandevents_c.h"
#અન્તર્ભાવ "SDL_waylandwindow.h"
#અન્તર્ભાવ "SDL_waylandmouse.h"
#અન્તર્ભાવ "SDL_waylandclipboard.h"
#અન્તર્ભાવ "SDL_waylandkeyboard.h"

#અન્તર્ભાવ "pointer-constraints-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "relative-pointer-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "xdg-shell-client-protocol.h"
#અન્તર્ભાવ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "text-input-unstable-v3-client-protocol.h"
#અન્તર્ભાવ "tablet-v2-client-protocol.h"
#અન્તર્ભાવ "primary-selection-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "input-timestamps-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "pointer-gestures-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "cursor-shape-v1-client-protocol.h"
#અન્તર્ભાવ "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#અન્તર્ભાવ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_આગત_LINUXEV
#અન્તર્ભાવ <linux/input.h>
#નહીંતર
#define BTN_ડાબું    (0x110)
#define BTN_જમણું   (0x111)
#define BTN_મધ્ય  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#અન્તર્ભાવ "../../events/SDL_keysym_to_scancode_c.h"
#અન્તર્ભાવ "../../events/imKStoUCS.h"
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <sys/mman.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <xkbcommon/xkbcommon-compose.h>
#અન્તર્ભાવ <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_નીચલું  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ઉપલું (WAYLAND_TIMER_ROLLOVER_INTERVAL_નીચલું * 15U)

// Scoped function declarations
સ્થિર શૂન્ય Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

પ્રકારવ્યાખ્યા સંરચના
{
    Uint32 ચાવી;
    SDL_Scancode scancode;
} Wayland_Reserved_ચાવી;

પ્રકારવ્યાખ્યા સંરચના
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    સંરચના wl_surface *surface;

    સંરચના wl_list link;
} SDL_WaylandTouchPoint;

સ્થિર શૂન્ય Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, સંરચના wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(કદ(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ઉમેરો(&seat->touch.points, &tp->link);
}

સ્થિર શૂન્ય Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    જો (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        જો (window_data) {
            અચલ દશાંશ x = (દશાંશ)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            અચલ દશાંશ y = (દશાંશ)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_ગણતરી;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            જો (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ગણતરી &&
                !window_data->pointer_focus_ગણતરી && !window_data->active_touch_ગણતરી) {
                SDL_SetMouseFocus(ખાલી);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

સ્થિર શૂન્ય Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, સંરચના wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        જો (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            જો (surface) {
                *surface = tp->surface;
            }
            તોડો;
        }
    }
}

સ્થિર શૂન્ય Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, સંરચના wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        જો (tp->id == id) {
            જો (fx) {
                *fx = tp->fx;
            }
            જો (fy) {
                *fy = tp->fy;
            }
            જો (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            તોડો;
        }
    }
}

સ્થિર શૂન્ય Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (પૂર્ણાંક)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (પૂર્ણાંક)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (પૂર્ણાંક)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (પૂર્ણાંક)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

સ્થિર Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    સ્થિર Uint64 timestamp_offset = 0;
    અચલ Uint64 now = SDL_GetTicksNS();

    જો (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    જો (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    પાછા nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
સ્થિર Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    સ્થિર Uint64 timestamp_offset = 0;
    સ્થિર Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    જો (wl_timestamp_ms >= last) {
        જો (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_નીચલું && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ઉપલું) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } નહીંતર {
            last = wl_timestamp_ms;
        }
    } નહીંતર {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        જો (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_નીચલું && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_ઉપલું) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    પાછા timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

સ્થિર Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    અચલ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    પાછા Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

સ્થિર Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    અચલ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    પાછા Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    અચલ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    પાછા Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

સ્થિર શૂન્ય આગત_timestamp_listener(શૂન્ય *data, સંરચના zwp_આગત_timestamps_v1 *zwp_આગત_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

સ્થિર અચલ સંરચના zwp_આગત_timestamps_v1_listener timestamp_listener = {
    આગત_timestamp_listener
};

સ્થિર શૂન્ય Wayland_Seat_Register_આગત_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    જો (seat->display->આગત_timestamps_manager) {
        જો (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_આગત_timestamps_manager_v1_get_keyboard_timestamps(seat->display->આગત_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_આગત_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        જો (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_આગત_timestamps_manager_v1_get_pointer_timestamps(seat->display->આગત_timestamps_manager, seat->pointer.wl_pointer);
            zwp_આગત_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        જો (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_આગત_timestamps_manager_v1_get_touch_timestamps(seat->display->આગત_timestamps_manager, seat->touch.wl_touch);
            zwp_આગત_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

શૂન્ય Wayland_Display_Init_આગત_Timestamp_Manager(SDL_VideoData *display)
{
    જો (display->આગત_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_આગત_Timestamp_Listeners(seat);
        }
    }
}

સ્થિર શૂન્ય handle_pinch_begin(શૂન્ય *data, સંરચના zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, સંરચના wl_surface *surface, uint32_t fingers)
{
    જો (!surface) {
        પાછા;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    જો (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        અચલ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

સ્થિર શૂન્ય handle_pinch_update(શૂન્ય *data, સંરચના zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    જો (seat->pointer.gesture_focus) {
        અચલ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        અચલ દશાંશ s = (દશાંશ)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

સ્થિર શૂન્ય handle_pinch_end(શૂન્ય *data, સંરચના zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    જો (seat->pointer.gesture_focus) {
        અચલ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = ખાલી;
    }
}

સ્થિર અચલ સંરચના zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

સ્થિર શૂન્ય Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    જો (seat->display->zwp_pointer_gestures) {
        જો (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

શૂન્ય Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

સ્થિર શૂન્ય Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    જો (seat->display->cursor_shape_manager) {
        જો (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            જો (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

શૂન્ય Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

સ્થિર શૂન્ય Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    અચલ bool send_event = !seat->display->initializing;

    જો (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.અંક_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
સ્થિર શૂન્ય keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    જ્યારે (elapsed >= repeat_info->next_repeat_ns) {
        જો (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            અચલ Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->ચાવી, repeat_info->scancode, true);
        }
        જો (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

સ્થિર શૂન્ય keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ચાવી, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, અચલ અક્ષર *text)
{
    જો (!repeat_info->repeat_rate) {
        પાછા;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ચાવી = ચાવી;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    જો (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } નહીંતર {
        repeat_info->text[0] = '\0';
    }
}

સ્થિર શૂન્ય sync_done_handler(શૂન્ય *data, સંરચના wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

સ્થિર સંરચના wl_callback_listener sync_listener = {
    sync_done_handler
};

શૂન્ય Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    સંરચના wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, ખાલી);
    WAYLAND_wl_display_flush(d->display);
}

પૂર્ણાંક Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    અચલ પૂર્ણાંક display_fd = WAYLAND_wl_display_get_fd(d->display);
    પૂર્ણાંક ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    જો (!d->text_આગત_manager && keyboard_focus && SDL_Text_આગત_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        જો (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        જો (seat->keyboard.repeat.ચાવી) {
            અચલ Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            અચલ Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            જો (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    જો (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        જો (timeoutNS > 0) {
            અચલ Uint64 now = SDL_GetTicksNS();
            અચલ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        જો (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            જો (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        જો (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            પાછા errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        જો (timeoutNS > 0) {
            અચલ Uint64 now = SDL_GetTicksNS();
            અચલ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        જો (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            જો (ret == 0) {
                પાછા poll_alarm_set ? 1 : 0;
            } નહીંતર {
                // Pump events on an interrupt or broken pipe to handle the error.
                પાછા errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        જો (ret == -1) {
            પાછા ret;
        }
    }

    // Signal to the caller that there might be an event available.
    પાછા 1;
}

શૂન્ય Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    અચલ પૂર્ણાંક display_fd = WAYLAND_wl_display_get_fd(d->display);
    પૂર્ણાંક ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    જો (!d->text_આગત_manager && keyboard_focus && SDL_Text_આગત_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    જો (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    જો (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        જો (ret < 0) {
            જાઓ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    જો (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        જો (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            જો (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        જો (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            જાઓ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        જો (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            જો (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } નહીંતર {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } નહીંતર {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    જો (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            જો (seat->keyboard.repeat.ચાવી) {
                Wayland_SeatSetKeymap(seat);

                અચલ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    જો (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

સ્થિર શૂન્ય pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : ખાલી;

    જો (window_data) {
        દ્વિગુણ sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        દ્વિગુણ sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        જો (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (દ્વિગુણ)window_data->mask.offset_x;
            sy += (દ્વિગુણ)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        જો (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (દશાંશ)sx, (દશાંશ)sy);
        } નહીંતર {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (દશાંશ)sx, (દશાંશ)sy);
        }

        seat->pointer.last_motion.x = (પૂર્ણાંક)SDL_floor(sx);
        seat->pointer.last_motion.y = (પૂર્ણાંક)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        જો (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        જો (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            પસંદગી (rc) {
            સ્થિતિ SDL_HITTEST_RESIZE_TOPLEFT:
                જો ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું)) {
                    rc = SDL_HITTEST_NORMAL;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ) {
                    rc = SDL_HITTEST_RESIZE_ડાબું;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું) {
                    rc = SDL_HITTEST_RESIZE_ટોચ;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_ટોચ:
                જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_TOPRIGHT:
                જો ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_જમણું)) {
                    rc = SDL_HITTEST_NORMAL;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ) {
                    rc = SDL_HITTEST_RESIZE_જમણું;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_જમણું) {
                    rc = SDL_HITTEST_RESIZE_ટોચ;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_જમણું:
                જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_જમણું) {
                    rc = SDL_HITTEST_NORMAL;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                જો ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_જમણું)) {
                    rc = SDL_HITTEST_NORMAL;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_જમણું;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_જમણું) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_BOTTOM:
                જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                જો ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું)) {
                    rc = SDL_HITTEST_NORMAL;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ડાબું;
                } નહીંતર જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                તોડો;
            સ્થિતિ SDL_HITTEST_RESIZE_ડાબું:
                જો (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું) {
                    rc = SDL_HITTEST_NORMAL;
                }
                તોડો;
            મૂળભૂત:
                તોડો;
            }

            જો (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

સ્થિર શૂન્ય pointer_handle_motion(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    અચલ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    જો (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        જો (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } નહીંતર {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

સ્થિર શૂન્ય pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    જો (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        પાછા;
    }

    જો (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        પાછા;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_ગણતરી;
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

સ્થિર શૂન્ય pointer_handle_enter(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                 uint32_t serial, સંરચના wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    જો (!surface) {
        // Enter event for a destroyed surface.
        પાછા;
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

    જો (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

સ્થિર શૂન્ય pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    જો (window) {
        જો (seat->pointer.focus) {
            જો (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = ખાલી;
                seat->pointer.focus_surface = ખાલી;
                માટે (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    જો (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                અચલ bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                જો (!--window->pointer_focus_ગણતરી && had_focus && !window->active_touch_ગણતરી) {
                    SDL_SetMouseFocus(ખાલી);
                }

                જો (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } નહીંતર જો (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

સ્થિર શૂન્ય pointer_handle_leave(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                 uint32_t serial, સંરચના wl_surface *surface)
{
    જો (!surface) {
        // Leave event for a destroyed surface.
        પાછા;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    જો (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

સ્થિર bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    જો (seat->pointer.locked_pointer) {
        પાછા false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    જો (window->hit_test) {
        સ્થિર અચલ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_ટોચ_ડાબું, XDG_TOPLEVEL_RESIZE_EDGE_ટોચ,
            XDG_TOPLEVEL_RESIZE_EDGE_ટોચ_જમણું, XDG_TOPLEVEL_RESIZE_EDGE_જમણું,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_જમણું, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ડાબું, XDG_TOPLEVEL_RESIZE_EDGE_ડાબું
        };

#ifdef HAVE_LIBDECOR_H
        સ્થિર અચલ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_ટોચ_ડાબું, LIBDECOR_RESIZE_EDGE_ટોચ,
            LIBDECOR_RESIZE_EDGE_ટોચ_જમણું, LIBDECOR_RESIZE_EDGE_જમણું,
            LIBDECOR_RESIZE_EDGE_BOTTOM_જમણું, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ડાબું, LIBDECOR_RESIZE_EDGE_ડાબું
        };
#endif

        પસંદગી (window_data->hit_test_result) {
        સ્થિતિ SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            જો (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                જો (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } નહીંતર
#endif
                જો (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                જો (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            પાછા true;

        સ્થિતિ SDL_HITTEST_RESIZE_TOPLEFT:
        સ્થિતિ SDL_HITTEST_RESIZE_ટોચ:
        સ્થિતિ SDL_HITTEST_RESIZE_TOPRIGHT:
        સ્થિતિ SDL_HITTEST_RESIZE_જમણું:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOM:
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        સ્થિતિ SDL_HITTEST_RESIZE_ડાબું:
#ifdef HAVE_LIBDECOR_H
            જો (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                જો (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } નહીંતર
#endif
                જો (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                જો (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            પાછા true;

        મૂળભૂત:
            પાછા false;
        }
    }

    પાછા false;
}

સ્થિર શૂન્ય pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    જો (window) {
        bool ignore_click = false;

        જો (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            જો (sdl_button == SDL_BUTTON_ડાબું && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                પાછા; // don't pass this event on to app.
            }
        } નહીંતર {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        જો (window->last_focus_event_time_ns) {
            જો (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        જો (!seat->pointer.relative_pointer) {
            જો (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } નહીંતર {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                જો (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        જો (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

સ્થિર શૂન્ય pointer_handle_button(શૂન્ય *data, સંરચના wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    પસંદગી (button) {
    સ્થિતિ BTN_ડાબું:
        sdl_button = SDL_BUTTON_ડાબું;
        તોડો;
    સ્થિતિ BTN_મધ્ય:
        sdl_button = SDL_BUTTON_મધ્ય;
        તોડો;
    સ્થિતિ BTN_જમણું:
        sdl_button = SDL_BUTTON_જમણું;
        તોડો;
    મૂળભૂત:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        તોડો;
    }

    જો (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    જો (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        જો (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } નહીંતર {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } નહીંતર {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

સ્થિર શૂન્ય pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t કિંમત)
{
    SDL_WindowData *window = seat->pointer.focus;
    અચલ ગણના wl_pointer_axis a = axis;

    જો (seat->pointer.focus) {
        દશાંશ x, y;

        પસંદગી (a) {
        સ્થિતિ WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (દશાંશ)wl_fixed_to_double(કિંમત);
            તોડો;
        સ્થિતિ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (દશાંશ)wl_fixed_to_double(કિંમત);
            y = 0;
            તોડો;
        મૂળભૂત:
            પાછા;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

સ્થિર શૂન્ય pointer_handle_axis_common(SDL_WaylandSeat *seat, ગણના SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t કિંમત)
{
    અચલ ગણના wl_pointer_axis a = axis;

    જો (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        પસંદગી (a) {
        સ્થિતિ WL_POINTER_AXIS_VERTICAL_SCROLL:
            પસંદગી (type) {
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                જો (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (દશાંશ)wl_fixed_to_double(કિંમત);
                તોડો;
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                જો (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (દશાંશ)wl_fixed_to_double(કિંમત);
                }
                તોડો;
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                જો (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (દશાંશ)wl_fixed_to_double(કિંમત);
                }
                તોડો;
            }
            તોડો;
        સ્થિતિ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            પસંદગી (type) {
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                જો (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (દશાંશ)wl_fixed_to_double(કિંમત);
                તોડો;
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                જો (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (દશાંશ)wl_fixed_to_double(કિંમત);
                }
                તોડો;
            સ્થિતિ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                જો (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (દશાંશ)wl_fixed_to_double(કિંમત);
                }
                તોડો;
            }
            તોડો;
        }
    }
}

સ્થિર શૂન્ય pointer_handle_axis(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t કિંમત)
{
    SDL_WaylandSeat *seat = data;
    અચલ Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    જો (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, કિંમત);
    } નહીંતર {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, કિંમત);
    }
}

સ્થિર શૂન્ય pointer_handle_axis_relative_direction(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    પસંદગી (axis_relative_direction) {
    સ્થિતિ WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        તોડો;
    સ્થિતિ WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        તોડો;
    }
}

સ્થિર શૂન્ય pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    જો (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        દ્વિગુણ dx;
        દ્વિગુણ dy;
        જો (mouse->આગત_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } નહીંતર {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (દશાંશ)dx, (દશાંશ)dy);
    }
}

સ્થિર શૂન્ય pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    દશાંશ x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    પસંદગી (seat->pointer.pending_frame.axis.x_axis_type) {
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        તોડો;
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        તોડો;
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        તોડો;
    મૂળભૂત:
        x = 0.0f;
        તોડો;
    }

    પસંદગી (seat->pointer.pending_frame.axis.y_axis_type) {
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        તોડો;
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        તોડો;
    સ્થિતિ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        તોડો;
    મૂળભૂત:
        y = 0.0f;
        તોડો;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

સ્થિર શૂન્ય pointer_handle_frame(શૂન્ય *data, સંરચના wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    જો (seat->pointer.pending_frame.enter_surface) {
        જો (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            જો (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = ખાલી;
                seat->pointer.pending_frame.leave_surface = ખાલી;
            } નહીંતર {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = ખાલી;
            }
        }

        જો (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    જો (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    જો (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    માટે (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        અચલ Uint32 mask = SDL_BUTTON_MASK(i);
        જો (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        જો (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    જો (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    જો (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

સ્થિર શૂન્ય pointer_handle_axis_source(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

સ્થિર શૂન્ય pointer_handle_axis_stop(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

સ્થિર શૂન્ય pointer_handle_axis_discrete(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

સ્થિર શૂન્ય pointer_handle_axis_value120(શૂન્ય *data, સંરચના wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

સ્થિર શૂન્ય pointer_handle_warp(શૂન્ય *data, સંરચના wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

સ્થિર અચલ સંરચના wl_pointer_listener pointer_listener = {
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

સ્થિર શૂન્ય relative_pointer_handle_relative_motion(શૂન્ય *data,
                                                    સંરચના zwp_relative_pointer_v1 *pointer,
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

    જો (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } નહીંતર {
        pointer_dispatch_relative_motion(seat);
    }
}

સ્થિર અચલ સંરચના zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

સ્થિર શૂન્ય locked_pointer_locked(શૂન્ય *data, સંરચના zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

સ્થિર શૂન્ય locked_pointer_unlocked(શૂન્ય *data, સંરચના zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

સ્થિર અચલ સંરચના zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

સ્થિર શૂન્ય confined_pointer_confined(શૂન્ય *data, સંરચના zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

સ્થિર શૂન્ય confined_pointer_unconfined(શૂન્ય *data, સંરચના zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

સ્થિર અચલ સંરચના zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

સ્થિર શૂન્ય touch_handler_down(શૂન્ય *data, સંરચના wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, સંરચના wl_surface *surface,
                               પૂર્ણાંક id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    જો (!surface) {
        પાછા;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    જો (window_data && window_data->surface == surface) {
        દશાંશ x, y;

        જો (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } નહીંતર {
            x = (દશાંશ)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        જો (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } નહીંતર {
            y = (દશાંશ)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_ગણતરી;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

સ્થિર શૂન્ય touch_handler_up(શૂન્ય *data, સંરચના wl_touch *touch, uint32_t serial, uint32_t timestamp, પૂર્ણાંક id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    સંરચના wl_surface *surface = ખાલી;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    જો (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        જો (window_data && window_data->surface == surface) {
            અચલ દશાંશ x = (દશાંશ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            અચલ દશાંશ y = (દશાંશ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_ગણતરી;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            જો (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ગણતરી &&
                !window_data->pointer_focus_ગણતરી && !window_data->active_touch_ગણતરી) {
                SDL_SetMouseFocus(ખાલી);
            }
        }
    }
}

સ્થિર શૂન્ય touch_handler_motion(શૂન્ય *data, સંરચના wl_touch *touch, uint32_t timestamp, પૂર્ણાંક id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    સંરચના wl_surface *surface = ખાલી;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    જો (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        જો (window_data && window_data->surface == surface) {
            અચલ દશાંશ x = (દશાંશ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            અચલ દશાંશ y = (દશાંશ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

સ્થિર શૂન્ય touch_handler_frame(શૂન્ય *data, સંરચના wl_touch *touch)
{
}

સ્થિર શૂન્ય touch_handler_cancel(શૂન્ય *data, સંરચના wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

સ્થિર શૂન્ય touch_handler_shape(શૂન્ય *data, સંરચના wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

સ્થિર શૂન્ય touch_handler_orientation(શૂન્ય *data, સંરચના wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

સ્થિર અચલ સંરચના wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#જો !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
સ્થિર size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ચાવી, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    જો (!masks_out || !masks_size) {
        પાછા 0;
    }

    // Level 0 is always unmodified, so early out.
    જો (level == 0) {
        *masks_out = 0;
        પાછા 1;
    }

    size_t mask_idx = 0;
    અચલ xkb_mod_mask_t keymod_masks[] = {
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
    અચલ xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    અચલ xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    માટે (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        જો (WAYLAND_xkb_state_ચાવી_get_level(seat->keyboard.xkb.state, ચાવી, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            જો (++mask_idx == masks_size) {
                તોડો;
            }
        }
    }

    પાછા mask_idx;
}
#endif

સ્થિર શૂન્ય Wayland_KeymapIterator(સંરચના xkb_keymap *keymap, xkb_keycode_t ચાવી, શૂન્ય *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    અચલ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    અચલ xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    જો (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ચાવી - 8);
    }

    માટે (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.અંક_layouts; ++layout) {
        અચલ xkb_level_index_t અંક_levels = WAYLAND_xkb_keymap_અંક_levels_for_ચાવી(seat->keyboard.xkb.keymap, ચાવી, layout);
        માટે (xkb_level_index_t level = 0; level < અંક_levels; ++level) {
            જો (WAYLAND_xkb_keymap_ચાવી_get_syms_by_level(seat->keyboard.xkb.keymap, ચાવી, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                જો (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ચાવી_Sym(syms[0], ચાવી);
                    જો (scancode == SDL_SCANCODE_UNKNOWN) {
                        ચાલુ;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#જો SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                અચલ size_t અંક_masks = WAYLAND_xkb_keymap_ચાવી_get_mods_for_level(seat->keyboard.xkb.keymap, ચાવી, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#નહીંતર
                અચલ size_t અંક_masks = xkb_legacy_get_mods_for_level(seat, ચાવી, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                માટે (size_t mask = 0; mask < અંક_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    જો ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        ચાલુ;
                    }

                    અચલ SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ચાવી_Code_From_ચાવી_Sym(syms[0], ચાવી, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    જો (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        જો (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ચાવી *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, કદ(Wayland_Reserved_ચાવી));
                        જો (res) {
                            res->scancode = scancode;
                            res->ચાવી = ચાવી - 8;
                        }
                    }

                    જો (!keycode) {
                        પસંદગી (scancode) {
                        સ્થિતિ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            તોડો;
                        સ્થિતિ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            તોડો;
                        સ્થિતિ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            તોડો;
                        સ્થિતિ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            તોડો;
                        મૂળભૂત:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            તોડો;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

સ્થિર શૂન્ય keyboard_handle_keymap(શૂન્ય *data, સંરચના wl_keyboard *keyboard,
                                   uint32_t format, પૂર્ણાંક fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    અક્ષર *map_str;

    જો (!data) {
        close(fd);
        પાછા;
    }

    જો (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        પાછા;
    }

    map_str = mmap(ખાલી, size, PROT_READ, MAP_PRIVATE, fd, 0);
    જો (map_str == MAP_FAILED) {
        close(fd);
        પાછા;
    }

    જો (seat->keyboard.xkb.keymap != ખાલી) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ખાલી;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    જો (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        પાછા;
    }

    // Clear the old layouts.
    માટે (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.અંક_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ખાલી;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.અંક_layouts = 0;

#જો SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.અંક_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_અંક);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#નહીંતર
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.અંક_mask = 1 << GET_MOD_INDEX(અંક_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    જો (seat->keyboard.xkb.state != ખાલી) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ખાલી;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    જો (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ખાલી;
        પાછા;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ખાલી;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.અંક_layouts = WAYLAND_xkb_keymap_અંક_layouts(seat->keyboard.xkb.keymap);
    જો (seat->keyboard.xkb.અંક_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.અંક_layouts, કદ(SDL_Keymap *));
        જો (!seat->keyboard.sdl_keymap) {
            પાછા;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        માટે (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.અંક_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            જો (!seat->keyboard.sdl_keymap[i]) {
                માટે (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ખાલી;
                પાછા;
            }
        }

        WAYLAND_xkb_keymap_ચાવી_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.અંક_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    અચલ અક્ષર *locale = SDL_getenv("LC_ALL");
    જો (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        જો (!locale) {
            locale = SDL_getenv("LANG");
            જો (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    જો (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        જો (seat->keyboard.xkb.compose_table != ખાલી) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = ખાલી;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        જો (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            જો (seat->keyboard.xkb.compose_state != ખાલી) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ખાલી;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            જો (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = ખાલી;
            }
        }
    } નહીંતર જો (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
સ્થિર SDL_Scancode Wayland_Get_Scancode_For_ચાવી(SDL_WaylandSeat *seat, Uint32 ચાવી, અચલ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    જો (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ચાવી);

        // No table entry? Check the reserved list.
        જો (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ચાવી *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                જો (i->ચાવી == ચાવી) {
                    પાછા i->scancode;
                }
            }
        }
    } નહીંતર {
        અચલ xkb_keysym_t *keysym;
        જો (WAYLAND_xkb_state_ચાવી_get_syms(seat->keyboard.xkb.state, ચાવી + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ચાવી_Sym(keysym[0], ચાવી + 8);
            જો (syms) {
                *syms = keysym;
            }
        }
    }

    પાછા scancode;
}

સ્થિર શૂન્ય Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ચાવી_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    જો (!ચાવી_pressed) {
        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } નહીંતર {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } નહીંતર {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } નહીંતર {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } નહીંતર {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } નહીંતર {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        જો (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            જો (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } નહીંતર {
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
    અચલ xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    જો (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        જો (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } નહીંતર જો (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        જો (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } નહીંતર જો (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        જો (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } નહીંતર જો (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        જો (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } નહીંતર જો (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    જો (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    જો (xkb_locked_modifiers & seat->keyboard.xkb.અંક_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_અંક;
    } નહીંતર {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_અંક;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

સ્થિર શૂન્ય Wayland_Handle_Modifier_ચાવીઓ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    અચલ SDL_Keycode keycode = SDL_Get_ચાવી_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    પસંદગી (keycode) {
    સ્થિતિ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        તોડો;
    સ્થિતિ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        તોડો;
    સ્થિતિ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        તોડો;
    સ્થિતિ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        તોડો;
    સ્થિતિ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        તોડો;
    સ્થિતિ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        તોડો;
    સ્થિતિ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        તોડો;
    સ્થિતિ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        તોડો;
    સ્થિતિ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        તોડો;
    સ્થિતિ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        તોડો;
    મૂળભૂત:
        પાછા;
    }

    જો (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } નહીંતર {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

સ્થિર શૂન્ય keyboard_handle_enter(શૂન્ય *data, સંરચના wl_keyboard *keyboard,
                                  uint32_t serial, સંરચના wl_surface *surface,
                                  સંરચના wl_array *ચાવીઓ)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *ચાવી;

    જો (!surface) {
        // Enter event for a destroyed surface.
        પાછા;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    જો (!window) {
        // Not a surface owned by SDL.
        પાછા;
    }

    ++window->keyboard_focus_ગણતરી;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_આગત(seat);

#ifdef SDL_USE_IME
    જો (!seat->text_આગત.zwp_text_આગત) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (ચાવી, ચાવીઓ) {
        અચલ SDL_Scancode scancode = Wayland_Get_Scancode_For_ચાવી(seat, *ચાવી, ખાલી);
        જો (scancode != SDL_SCANCODE_UNKNOWN) {
            અચલ SDL_Keycode keycode = SDL_Get_ચાવી_From_Scancode(scancode, SDL_KMOD_NONE, false);

            પસંદગી (keycode) {
            સ્થિતિ SDLK_LSHIFT:
            સ્થિતિ SDLK_RSHIFT:
            સ્થિતિ SDLK_LCTRL:
            સ્થિતિ SDLK_RCTRL:
            સ્થિતિ SDLK_LALT:
            સ્થિતિ SDLK_RALT:
            સ્થિતિ SDLK_LGUI:
            સ્થિતિ SDLK_RGUI:
            સ્થિતિ SDLK_MODE:
            સ્થિતિ SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_ચાવીઓ(seat, scancode, true);
                SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ચાવી, scancode, true);
                તોડો;
            મૂળભૂત:
                તોડો;
            }
        }
    }
}

સ્થિર શૂન્ય keyboard_handle_leave(શૂન્ય *data, સંરચના wl_keyboard *keyboard,
                                  uint32_t serial, સંરચના wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    જો (!surface) {
        // Leave event for a destroyed surface.
        પાછા;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    જો (!window) {
        // Not a surface owned by SDL.
        પાછા;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ચાવી = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    જ્યારે (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    અચલ bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ખાલી;
    --window->keyboard_focus_ગણતરી;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    જો (!window->keyboard_focus_ગણતરી && had_focus) {
        SDL_SetKeyboardFocus(ખાલી);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_આગત(seat);

#ifdef SDL_USE_IME
    જો (!seat->text_આગત.zwp_text_આગત && !window->keyboard_focus_ગણતરી) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    જો (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_ગણતરી && !window->active_touch_ગણતરી) {
        SDL_SetMouseFocus(ખાલી);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, ખાલી);
}

સ્થિર bool keyboard_આગત_get_text(અક્ષર text[8], અચલ SDL_WaylandSeat *seat, uint32_t ચાવી, bool down, bool *handled_by_ime)
{
    અચલ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    જો (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        પાછા false;
    }

    // TODO: Can this happen?
    જો (WAYLAND_xkb_state_ચાવી_get_syms(seat->keyboard.xkb.state, ચાવી + 8, &syms) != 1) {
        પાછા false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    જો (SDL_IME_Process_ચાવી_Event(sym, ચાવી + 8, down)) {
        જો (handled_by_ime) {
            *handled_by_ime = true;
        }
        પાછા true;
    }
#endif

    જો (!down) {
        પાછા false;
    }

    જો (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        પસંદગી (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        સ્થિતિ XKB_COMPOSE_COMPOSING:
            જો (handled_by_ime) {
                *handled_by_ime = true;
            }
            પાછા true;
        સ્થિતિ XKB_COMPOSE_CANCELLED:
        મૂળભૂત:
            sym = XKB_ચાવી_No_પ્રતીક;
            તોડો;
        સ્થિતિ XKB_COMPOSE_NOTHING:
            તોડો;
        સ્થિતિ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            તોડો;
        }
    }

    પાછા WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

સ્થિર શૂન્ય keyboard_handle_ચાવી(શૂન્ય *data, સંરચના wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t ચાવી,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    ગણના wl_keyboard_ચાવી_state state = state_w;
    અક્ષર text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    અચલ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    જો (state == WL_KEYBOARD_ચાવી_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        જો (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ચાવી_repeats(seat->keyboard.xkb.keymap, ચાવી + 8)) {
            પાછા;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ચાવી_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    જો (state == WL_KEYBOARD_ચાવી_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        જો (keyboard_focus && SDL_Text_આગત_Active(keyboard_focus)) {
            has_text = keyboard_આગત_get_text(text, seat, ચાવી, true, &handled_by_ime);
        }
    } નહીંતર {
        જો (ચાવી == seat->keyboard.repeat.ચાવી) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            અચલ Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ચાવી = 0;
        }
        keyboard_આગત_get_text(text, seat, ચાવી, false, &handled_by_ime);
    }

    અચલ xkb_keysym_t *syms = ખાલી;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ચાવી(seat, ચાવી, &syms);
    Wayland_Handle_Modifier_ચાવીઓ(seat, scancode, state == WL_KEYBOARD_ચાવી_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    જો (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        અચલ SDL_Keycode keycode = (SDL_Keycode)SDL_ચાવી_Sym_To_Ucs4(syms[0]);
        જો (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            જો (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ચાવી_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ચાવી, scancode, state == WL_KEYBOARD_ચાવી_STATE_PRESSED);

    જો (state == WL_KEYBOARD_ચાવી_STATE_PRESSED) {
        જો (handled_by_ime) {
            has_text = false;
        }
        જો (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        જો (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ચાવી_repeats(seat->keyboard.xkb.keymap, ચાવી + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, ચાવી, time, timestamp_ns, scancode, has_text ? text : ખાલી);
        }
    }
}

સ્થિર શૂન્ય keyboard_handle_modifiers(શૂન્ય *data, સંરચના wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    અચલ uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    જો (!seat->keyboard.xkb.state) {
        પાછા;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    જો (seat->keyboard.repeat.ચાવી) {
        અક્ષર text[8];

        જો (keyboard_આગત_get_text(text, seat, seat->keyboard.repeat.ચાવી, true, ખાલી)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    જો (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        જો (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

સ્થિર શૂન્ય keyboard_handle_repeat_info(શૂન્ય *data, સંરચના wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    જો (!rate) {
        seat->keyboard.repeat.ચાવી = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

સ્થિર અચલ સંરચના wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ચાવી,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

સ્થિર શૂન્ય Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    જો (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    જો (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = ખાલી;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    જો (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    જો (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    જો (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    જો (seat->pointer.timestamps) {
        zwp_આગત_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    જો (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    જો (seat->pointer.wl_pointer) {
        જો (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } નહીંતર {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

સ્થિર શૂન્ય Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    જો (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    જો (seat->keyboard.sdl_keymap) {
        જો (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.અંક_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        માટે (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.અંક_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ખાલી;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    જો (seat->keyboard.ચાવી_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ચાવી_inhibitor);
    }

    જો (seat->keyboard.timestamps) {
        zwp_આગત_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    જો (seat->keyboard.wl_keyboard) {
        જો (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } નહીંતર {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    જો (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    જો (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    જો (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    જો (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

સ્થિર શૂન્ય Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    જો (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    જો (seat->touch.timestamps) {
        zwp_આગત_timestamps_v1_destroy(seat->touch.timestamps);
    }

    જો (seat->touch.wl_touch) {
        જો (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } નહીંતર {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

સ્થિર શૂન્ય seat_handle_capabilities(શૂન્ય *data, સંરચના wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    અક્ષર name_fmt[256];

    જો ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        જો (seat->name) {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } નહીંતર {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } નહીંતર જો (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    જો ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        જો (seat->name) {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } નહીંતર {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } નહીંતર જો (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    જો ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        જો (seat->name) {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } નહીંતર {
            SDL_snprintf(name_fmt, કદ(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } નહીંતર જો (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_આગત_Timestamp_Listeners(seat);
}

સ્થિર શૂન્ય seat_handle_name(શૂન્ય *data, સંરચના wl_seat *wl_seat, અચલ અક્ષર *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    જો (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

સ્થિર અચલ સંરચના wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

સ્થિર શૂન્ય data_offer_handle_offer(શૂન્ય *data, સંરચના wl_data_offer *wl_data_offer,
                                    અચલ અક્ષર *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

સ્થિર શૂન્ય data_offer_handle_source_actions(શૂન્ય *data, સંરચના wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

સ્થિર શૂન્ય data_offer_handle_actions(શૂન્ય *data, સંરચના wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

સ્થિર અચલ સંરચના wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

સ્થિર શૂન્ય primary_selection_offer_handle_offer(શૂન્ય *data, સંરચના zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 અચલ અક્ષર *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

સ્થિર અચલ સંરચના zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

સ્થિર શૂન્ય data_device_handle_data_offer(શૂન્ય *data, સંરચના wl_data_device *wl_data_device,
                                          સંરચના wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, કદ(*data_offer));
    જો (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id) : -1));
    }
}

સ્થિર શૂન્ય data_device_handle_enter(શૂન્ય *data, સંરચના wl_data_device *wl_data_device,
                                     uint32_t serial, સંરચના wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, સંરચના wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ખાલી;
    data_device->has_mime_file = false;
    data_device->text_mime_type = ખાલી;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    જો (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    જો (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        જો (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        જો (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        જો (!data_device->has_mime_file) {
            size_t mime_ગણતરી = 0;
            અચલ અક્ષર *અચલ *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_ગણતરી);
            માટે (size_t i = 0; i < mime_ગણતરી; ++i) {
                જો (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    તોડો;
                }
            }
        }

        જો (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            જો (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            દ્વિગુણ dx = wl_fixed_to_double(x);
            દ્વિગુણ dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            જો (surface == window->mask.surface) {
                dx += (દ્વિગુણ)window->mask.offset_x;
                dy += (દ્વિગુણ)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (દશાંશ)dx, (દશાંશ)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } નહીંતર {
            // Decline the offer.
            wl_data_offer_accept(id, serial, ખાલી);
            જો (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } નહીંતર {
        data_device->dnd_window = ખાલી;
        data_device->dnd_surface = ખાલી;

        // Decline the offer.
        જો (id) {
            wl_data_offer_accept(id, serial, ખાલી);
            જો (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

સ્થિર શૂન્ય data_device_handle_leave(શૂન્ય *data, સંરચના wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    જો (data_device->drag_offer) {
        જો (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } નહીંતર {
            SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = ખાલી;
    } નહીંતર {
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = ખાલી;
}

સ્થિર શૂન્ય data_device_handle_motion(શૂન્ય *data, સંરચના wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    જો (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        દ્વિગુણ dx = wl_fixed_to_double(x);
        દ્વિગુણ dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        જો (data_device->dnd_surface == window_data->mask.surface) {
            dx += (દ્વિગુણ)window_data->mask.offset_x;
            dy += (દ્વિગુણ)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (દશાંશ)dx, (દશાંશ)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } નહીંતર {
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

સ્થિર શૂન્ય drop_cleanup_handler(શૂન્ય *data, સંરચના wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

સ્થિર અચલ સંરચના wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

સ્થિર શૂન્ય drop_dispatch_handler(શૂન્ય *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    જો (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        જો (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            શૂન્ય *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            જો (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                જો (dbus) {
                    પૂર્ણાંક path_ગણતરી = 0;
                    અક્ષર **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_ગણતરી);
                    // If dropped files contain a directory the list is empty
                    જો (paths && path_ગણતરી > 0) {
                        માટે (પૂર્ણાંક i = 0; i < path_ગણતરી; i++) {
                            SDL_SendDropFile(drop->dnd_window, ખાલી, paths[i]);
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
        જો (!drop_handled) {
            જો (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                શૂન્ય *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                જો (buffer) {
                    અક્ષર *saveptr = ખાલી;
                    અક્ષર *token = SDL_strtok_r((અક્ષર *)buffer, "\r\n", &saveptr);
                    જ્યારે (token) {
                        જો (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, ખાલી, token);
                        }
                        token = SDL_strtok_r(ખાલી, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } નહીંતર જો (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                શૂન્ય *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                જો (buffer) {
                    અક્ષર *saveptr = ખાલી;
                    અક્ષર *token = SDL_strtok_r((અક્ષર *)buffer, "\r\n", &saveptr);
                    જ્યારે (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(ખાલી, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        જો (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = ખાલી;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

સ્થિર શૂન્ય data_device_handle_drop(શૂન્ય *data, સંરચના wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    જો (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, કદ(Wayland_DropData));
        જો (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_ઉમેરો(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } નહીંતર {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } નહીંતર {
        SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = ખાલી;
}

સ્થિર શૂન્ય data_device_handle_selection(શૂન્ય *data, સંરચના wl_data_device *wl_data_device,
                                         સંરચના wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = ખાલી;

    જો (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

સ્થિર અચલ સંરચના wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

સ્થિર શૂન્ય primary_selection_device_handle_offer(શૂન્ય *data, સંરચના zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  સંરચના zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, કદ(*primary_selection_offer));
    જો (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id) : -1));
}

સ્થિર શૂન્ય primary_selection_device_handle_selection(શૂન્ય *data, સંરચના zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      સંરચના zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = ખાલી;

    જો (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    જો (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((સંરચના wl_proxy *)id) : -1));
}

સ્થિર અચલ સંરચના zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

સ્થિર શૂન્ય text_આગત_enter(શૂન્ય *data,
                             સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                             સંરચના wl_surface *surface)
{
    // No-op
}

સ્થિર શૂન્ય text_આગત_leave(શૂન્ય *data,
                             સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                             સંરચના wl_surface *surface)
{
    // No-op
}

સ્થિર શૂન્ય text_આગત_preedit_string(શૂન્ય *data,
                                      સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                                      અચલ અક્ષર *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_આગત.has_preedit = true;
    જો (text) {
        પૂર્ણાંક cursor_begin_utf8 = cursor_begin >= 0 ? (પૂર્ણાંક)SDL_utf8strnlen(text, cursor_begin) : -1;
        પૂર્ણાંક cursor_end_utf8 = cursor_end >= 0 ? (પૂર્ણાંક)SDL_utf8strnlen(text, cursor_end) : -1;
        પૂર્ણાંક cursor_size_utf8;
        જો (cursor_end_utf8 >= 0) {
            જો (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } નહીંતર {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } નહીંતર {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } નહીંતર {
        SDL_SendEditingText("", 0, 0);
    }
}

સ્થિર શૂન્ય text_આગત_commit_string(શૂન્ય *data,
                                     સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                                     અચલ અક્ષર *text)
{
    SDL_SendKeyboardText(text);
}

સ્થિર શૂન્ય text_આગત_delete_surrounding_text(શૂન્ય *data,
                                               સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

સ્થિર શૂન્ય text_આગત_done(શૂન્ય *data,
                            સંરચના zwp_text_આગત_v3 *zwp_text_આગત_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    જો (!seat->text_આગત.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_આગત.has_preedit = false;
}

સ્થિર અચલ સંરચના zwp_text_આગત_v3_listener text_આગત_listener = {
    text_આગત_enter,
    text_આગત_leave,
    text_આગત_preedit_string,
    text_આગત_commit_string,
    text_આગત_delete_surrounding_text,
    text_આગત_done
};

સ્થિર શૂન્ય Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    જો (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        જો (dbus) {
            અચલ અક્ષર *id = dbus->bus_get_unique_name(dbus->session_conn);
            જો (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    જો (!data_device->id_str)
#endif
    {
        અક્ષર id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, કદ(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

સ્થિર શૂન્ય Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    જો (!seat->display->data_device_manager) {
        પાછા;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, કદ(*data_device));
    જો (!data_device) {
        પાછા;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    જો (!data_device->data_device) {
        SDL_free(data_device);
        પાછા;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

શૂન્ય Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

સ્થિર શૂન્ય Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    જો (!seat->display->primary_selection_device_manager) {
        પાછા;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, કદ(*primary_selection_device));
    જો (!primary_selection_device) {
        પાછા;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    જો (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } નહીંતર {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

શૂન્ય Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

સ્થિર શૂન્ય Wayland_Seat_Create_Text_આગત(SDL_WaylandSeat *seat)
{
    જો (seat->display->text_આગત_manager) {
        seat->text_આગત.zwp_text_આગત = zwp_text_આગત_manager_v3_get_text_આગત(seat->display->text_આગત_manager, seat->wl_seat);

        જો (seat->text_આગત.zwp_text_આગત) {
            zwp_text_આગત_v3_set_user_data(seat->text_આગત.zwp_text_આગત, seat);
            zwp_text_આગત_v3_add_listener(seat->text_આગત.zwp_text_આગત,
                                           &text_આગત_listener, seat);
        }
    }
}

શૂન્ય Wayland_Display_Init_Text_આગત_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_આગત(seat);
    }
}

// Pen/Tablet support...
સ્થિર શૂન્ય tablet_tool_handle_type(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    પસંદગી (type) {
        #define CASE(typ) સ્થિતિ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; પાછા
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        મૂળભૂત: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

સ્થિર શૂન્ય tablet_tool_handle_hardware_serial(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

સ્થિર શૂન્ય tablet_tool_handle_hardware_id_wacom(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

સ્થિર શૂન્ય tablet_tool_handle_capability(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    પસંદગી (capability) {
        #define CASE(wltyp,sdltyp) સ્થિતિ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; પાછા
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        મૂળભૂત: તોડો;  // unsupported here.
    }
}

સ્થિર શૂન્ય tablet_tool_handle_done(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    જો (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ખાલી;
        sdltool->instance_id = SDL_AddPenDevice(0, ખાલી, window, &sdltool->info, sdltool, false);
    }
}

સ્થિર શૂન્ય tablet_tool_handle_removed(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    જો (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ખાલી;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

સ્થિર શૂન્ય tablet_tool_handle_proximity_in(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t serial, સંરચના zwp_tablet_v2 *tablet, સંરચના wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ખાલી;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ખાલી;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

સ્થિર શૂન્ય tablet_tool_handle_proximity_out(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

સ્થિર શૂન્ય tablet_tool_handle_down(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

સ્થિર શૂન્ય tablet_tool_handle_up(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

સ્થિર શૂન્ય tablet_tool_handle_motion(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    જો (windowdata) {
        sdltool->frame.x = (દશાંશ)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (દશાંશ)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

સ્થિર શૂન્ય tablet_tool_handle_pressure(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((દશાંશ) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    જો (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

સ્થિર શૂન્ય tablet_tool_handle_distance(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((દશાંશ) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    જો (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

સ્થિર શૂન્ય tablet_tool_handle_tilt(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (દશાંશ)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (દશાંશ)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

સ્થિર શૂન્ય tablet_tool_handle_button(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    પૂર્ણાંક sdlbutton;

    પસંદગી (button) {
    સ્થિતિ BTN_STYLUS:
        sdlbutton = 1;
        તોડો;
    સ્થિતિ BTN_STYLUS2:
        sdlbutton = 2;
        તોડો;
    સ્થિતિ BTN_STYLUS3:
        sdlbutton = 3;
        તોડો;
    મૂળભૂત:
        પાછા;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

સ્થિર શૂન્ય tablet_tool_handle_rotation(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    અચલ દશાંશ rotation = (દશાંશ)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

સ્થિર શૂન્ય tablet_tool_handle_slider(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

સ્થિર શૂન્ય tablet_tool_handle_wheel(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

સ્થિર શૂન્ય tablet_tool_handle_frame(શૂન્ય *data, સંરચના zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    અચલ SDL_PenID instance_id = sdltool->instance_id;
    જો (!instance_id) {
        પાછા;  // Not a pen we report on.
    }

    અચલ Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ખાલી;
    અચલ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    જો (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    જો (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        જો (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } નહીંતર {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } નહીંતર {
        જો (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        જો (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    માટે (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ગણતરી; i++) {
        જો (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    માટે (પૂર્ણાંક i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        અચલ પૂર્ણાંક state = sdltool->frame.buttons[i];
        જો (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    જો (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = ખાલી;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

સ્થિર અચલ સંરચના zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


સ્થિર શૂન્ય tablet_seat_handle_tablet_added(શૂન્ય *data, સંરચના zwp_tablet_seat_v2 *zwp_tablet_seat_v2, સંરચના zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

સ્થિર શૂન્ય tablet_seat_handle_tool_added(શૂન્ય *data, સંરચના zwp_tablet_seat_v2 *zwp_tablet_seat_v2, સંરચના zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, કદ(*sdltool));

    જો (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.અંક_buttons = -1;

        જો (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ઉમેરો(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

સ્થિર શૂન્ય tablet_seat_handle_pad_added(શૂન્ય *data, સંરચના zwp_tablet_seat_v2 *zwp_tablet_seat_v2, સંરચના zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

સ્થિર અચલ સંરચના zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

સ્થિર શૂન્ય Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

શૂન્ય Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

સ્થિર શૂન્ય Wayland_remove_all_pens_callback(SDL_PenID instance_id, શૂન્ય *handle, શૂન્ય *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

સ્થિર શૂન્ય Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    જો (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } નહીંતર {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ખાલી);
    }

    જો (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ખાલી;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

શૂન્ય Wayland_DisplayCreateSeat(SDL_VideoData *display, સંરચના wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, કદ(SDL_WaylandSeat));
    જો (!seat) {
        પાછા;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ઉમેરો(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_આગત(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    જો (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

શૂન્ય Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        જો (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        જો (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = ખાલી;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            જો (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            જો (tool->focus == window) {
                tool->focus = ખાલી;
                Wayland_TabletToolUpdateCursor(tool);
                જો (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            જો (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                જો (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

શૂન્ય Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    જો (!seat) {
        પાછા;
    }

    SDL_free(seat->name);

    જો (seat->data_device) {
        જો (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        જો (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        જો (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            જો (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        જો (seat->data_device->data_device) {
            જો (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } નહીંતર {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    જો (seat->primary_selection_device) {
        જો (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        જો (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        જો (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    જો (seat->text_આગત.zwp_text_આગત) {
        zwp_text_આગત_v3_destroy(seat->text_આગત.zwp_text_આગત);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    જો (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } નહીંતર {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

સ્થિર શૂન્ય Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    જો (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        જો (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            જો (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                જો (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } નહીંતર {
                    relative_focus = seat->pointer.focus->keyboard_focus_ગણતરી != 0;
                }
            } નહીંતર {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        જો (relative_focus) {
            જો (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } નહીંતર જો (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = ખાલી;
        }
    }
}

સ્થિર શૂન્ય Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    જો (display->ચાવી_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        જો (seat->keyboard.ચાવી_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ચાવી_inhibitor);
            seat->keyboard.ચાવી_inhibitor = ખાલી;
        }

        જો (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            જો (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                જો (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.ચાવી_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ચાવી_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

શૂન્ય Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    જો (display->pointer_constraints) {
        જો (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = ખાલી;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        જો (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            જો (seat->pointer.relative_pointer) {
                જો (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    જો (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = ખાલી;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, ખાલી,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                પાછા;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            જો (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ખાલી;
            }

            SDL_WindowData *w = seat->pointer.focus;
            જો (!w) {
                પાછા;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            જો (!(window->flags & SDL_WINDOW_આગત_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                પાછા;
            }

            સંરચના wl_region *confine_rect = ખાલી;
            જો (!SDL_RectEmpty(&window->mouse_rect)) {
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
                જો (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    પૂર્ણાંક closest_x = seat->pointer.last_motion.x;
                    પૂર્ણાંક closest_y = seat->pointer.last_motion.y;

                    જો (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } નહીંતર જો (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    જો (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } નહીંતર જો (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            જો (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                જો (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } નહીંતર {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                ખાલી,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                જો (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

શૂન્ય Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        જો (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

શૂન્ય Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        જો (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

શૂન્ય Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    જો (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
