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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ "../../core/unix/SDL_poll.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_scancode_tables_c.h"
#അന്തര്ഭാവ "../../events/SDL_keysym_to_keycode_c.h"
#അന്തര്ഭാവ "../../core/linux/SDL_system_theme.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"

#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "SDL_waylandevents_c.h"
#അന്തര്ഭാവ "SDL_waylandwindow.h"
#അന്തര്ഭാവ "SDL_waylandmouse.h"
#അന്തര്ഭാവ "SDL_waylandclipboard.h"
#അന്തര്ഭാവ "SDL_waylandkeyboard.h"

#അന്തര്ഭാവ "pointer-constraints-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "relative-pointer-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "xdg-shell-client-protocol.h"
#അന്തര്ഭാവ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "text-input-unstable-v3-client-protocol.h"
#അന്തര്ഭാവ "tablet-v2-client-protocol.h"
#അന്തര്ഭാവ "primary-selection-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "input-timestamps-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "pointer-gestures-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "cursor-shape-v1-client-protocol.h"
#അന്തര്ഭാവ "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#അന്തര്ഭാവ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_നിവേശം_LINUXEV
#അന്തര്ഭാവ <linux/input.h>
#അല്ലെങ്കിൽ
#define BTN_ഇടത്    (0x110)
#define BTN_വലത്   (0x111)
#define BTN_നടുവ്  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#അന്തര്ഭാവ "../../events/SDL_keysym_to_scancode_c.h"
#അന്തര്ഭാവ "../../events/imKStoUCS.h"
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <sys/mman.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <xkbcommon/xkbcommon-compose.h>
#അന്തര്ഭാവ <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_താഴെയുള്ള  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_മുകളിലെ (WAYLAND_TIMER_ROLLOVER_INTERVAL_താഴെയുള്ള * 15U)

// Scoped function declarations
സ്ഥിതം ശൂന്യം Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

തരനിർവചനം ഘടന
{
    Uint32 താക്കോൽ;
    SDL_Scancode scancode;
} Wayland_Reserved_താക്കോൽ;

തരനിർവചനം ഘടന
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ഘടന wl_surface *surface;

    ഘടന wl_list link;
} SDL_WaylandTouchPoint;

സ്ഥിതം ശൂന്യം Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ഘടന wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(വലുപ്പം(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_തിരുകുക(&seat->touch.points, &tp->link);
}

സ്ഥിതം ശൂന്യം Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    എങ്കിൽ (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        എങ്കിൽ (window_data) {
            സ്ഥിരം ദശാംശം x = (ദശാംശം)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            സ്ഥിരം ദശാംശം y = (ദശാംശം)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_എണ്ണം;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            എങ്കിൽ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_എണ്ണം &&
                !window_data->pointer_focus_എണ്ണം && !window_data->active_touch_എണ്ണം) {
                SDL_SetMouseFocus(ശൂന്യ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

സ്ഥിതം ശൂന്യം Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ഘടന wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        എങ്കിൽ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            എങ്കിൽ (surface) {
                *surface = tp->surface;
            }
            നിർത്തുക;
        }
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ഘടന wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        എങ്കിൽ (tp->id == id) {
            എങ്കിൽ (fx) {
                *fx = tp->fx;
            }
            എങ്കിൽ (fy) {
                *fy = tp->fy;
            }
            എങ്കിൽ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            നിർത്തുക;
        }
    }
}

സ്ഥിതം ശൂന്യം Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (പൂർണ്ണസംഖ്യ)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (പൂർണ്ണസംഖ്യ)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (പൂർണ്ണസംഖ്യ)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (പൂർണ്ണസംഖ്യ)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

സ്ഥിതം Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    സ്ഥിതം Uint64 timestamp_offset = 0;
    സ്ഥിരം Uint64 now = SDL_GetTicksNS();

    എങ്കിൽ (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    എങ്കിൽ (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    തിരികെ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
സ്ഥിതം Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    സ്ഥിതം Uint64 timestamp_offset = 0;
    സ്ഥിതം Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    എങ്കിൽ (wl_timestamp_ms >= last) {
        എങ്കിൽ (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_താഴെയുള്ള && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_മുകളിലെ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } അല്ലെങ്കിൽ {
            last = wl_timestamp_ms;
        }
    } അല്ലെങ്കിൽ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        എങ്കിൽ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_താഴെയുള്ള && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_മുകളിലെ) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    തിരികെ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

സ്ഥിതം Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    സ്ഥിരം Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    തിരികെ Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

സ്ഥിതം Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    സ്ഥിരം Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    തിരികെ Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    സ്ഥിരം Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    തിരികെ Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

സ്ഥിതം ശൂന്യം നിവേശം_timestamp_listener(ശൂന്യം *data, ഘടന zwp_നിവേശം_timestamps_v1 *zwp_നിവേശം_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_നിവേശം_timestamps_v1_listener timestamp_listener = {
    നിവേശം_timestamp_listener
};

സ്ഥിതം ശൂന്യം Wayland_Seat_Register_നിവേശം_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->display->നിവേശം_timestamps_manager) {
        എങ്കിൽ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_നിവേശം_timestamps_manager_v1_get_keyboard_timestamps(seat->display->നിവേശം_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_നിവേശം_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        എങ്കിൽ (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_നിവേശം_timestamps_manager_v1_get_pointer_timestamps(seat->display->നിവേശം_timestamps_manager, seat->pointer.wl_pointer);
            zwp_നിവേശം_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        എങ്കിൽ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_നിവേശം_timestamps_manager_v1_get_touch_timestamps(seat->display->നിവേശം_timestamps_manager, seat->touch.wl_touch);
            zwp_നിവേശം_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

ശൂന്യം Wayland_Display_Init_നിവേശം_Timestamp_Manager(SDL_VideoData *display)
{
    എങ്കിൽ (display->നിവേശം_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_നിവേശം_Timestamp_Listeners(seat);
        }
    }
}

സ്ഥിതം ശൂന്യം handle_pinch_begin(ശൂന്യം *data, ഘടന zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, ഘടന wl_surface *surface, uint32_t fingers)
{
    എങ്കിൽ (!surface) {
        തിരികെ;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    എങ്കിൽ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        സ്ഥിരം Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

സ്ഥിതം ശൂന്യം handle_pinch_update(ശൂന്യം *data, ഘടന zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    എങ്കിൽ (seat->pointer.gesture_focus) {
        സ്ഥിരം Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        സ്ഥിരം ദശാംശം s = (ദശാംശം)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

സ്ഥിതം ശൂന്യം handle_pinch_end(ശൂന്യം *data, ഘടന zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    എങ്കിൽ (seat->pointer.gesture_focus) {
        സ്ഥിരം Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = ശൂന്യ;
    }
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

സ്ഥിതം ശൂന്യം Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->display->zwp_pointer_gestures) {
        എങ്കിൽ (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

ശൂന്യം Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->display->cursor_shape_manager) {
        എങ്കിൽ (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            എങ്കിൽ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

ശൂന്യം Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    സ്ഥിരം bool send_event = !seat->display->initializing;

    എങ്കിൽ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.അക്കം_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
സ്ഥിതം ശൂന്യം keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ആകുമ്പോൾ (elapsed >= repeat_info->next_repeat_ns) {
        എങ്കിൽ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            സ്ഥിരം Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->താക്കോൽ, repeat_info->scancode, true);
        }
        എങ്കിൽ (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

സ്ഥിതം ശൂന്യം keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t താക്കോൽ, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, സ്ഥിരം അക്ഷരം *text)
{
    എങ്കിൽ (!repeat_info->repeat_rate) {
        തിരികെ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->താക്കോൽ = താക്കോൽ;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    എങ്കിൽ (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } അല്ലെങ്കിൽ {
        repeat_info->text[0] = '\0';
    }
}

സ്ഥിതം ശൂന്യം sync_done_handler(ശൂന്യം *data, ഘടന wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

സ്ഥിതം ഘടന wl_callback_listener sync_listener = {
    sync_done_handler
};

ശൂന്യം Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ഘടന wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, ശൂന്യ);
    WAYLAND_wl_display_flush(d->display);
}

പൂർണ്ണസംഖ്യ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    സ്ഥിരം പൂർണ്ണസംഖ്യ display_fd = WAYLAND_wl_display_get_fd(d->display);
    പൂർണ്ണസംഖ്യ ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    എങ്കിൽ (!d->text_നിവേശം_manager && keyboard_focus && SDL_Text_നിവേശം_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        എങ്കിൽ (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        എങ്കിൽ (seat->keyboard.repeat.താക്കോൽ) {
            സ്ഥിരം Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            സ്ഥിരം Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            എങ്കിൽ (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    എങ്കിൽ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        എങ്കിൽ (timeoutNS > 0) {
            സ്ഥിരം Uint64 now = SDL_GetTicksNS();
            സ്ഥിരം Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        എങ്കിൽ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            എങ്കിൽ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        എങ്കിൽ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            തിരികെ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        എങ്കിൽ (timeoutNS > 0) {
            സ്ഥിരം Uint64 now = SDL_GetTicksNS();
            സ്ഥിരം Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        എങ്കിൽ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            എങ്കിൽ (ret == 0) {
                തിരികെ poll_alarm_set ? 1 : 0;
            } അല്ലെങ്കിൽ {
                // Pump events on an interrupt or broken pipe to handle the error.
                തിരികെ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        എങ്കിൽ (ret == -1) {
            തിരികെ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    തിരികെ 1;
}

ശൂന്യം Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    സ്ഥിരം പൂർണ്ണസംഖ്യ display_fd = WAYLAND_wl_display_get_fd(d->display);
    പൂർണ്ണസംഖ്യ ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    എങ്കിൽ (!d->text_നിവേശം_manager && keyboard_focus && SDL_Text_നിവേശം_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    എങ്കിൽ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    എങ്കിൽ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        എങ്കിൽ (ret < 0) {
            പോകുക connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    എങ്കിൽ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        എങ്കിൽ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            എങ്കിൽ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        എങ്കിൽ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            പോകുക connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        എങ്കിൽ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            എങ്കിൽ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } അല്ലെങ്കിൽ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } അല്ലെങ്കിൽ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    എങ്കിൽ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            എങ്കിൽ (seat->keyboard.repeat.താക്കോൽ) {
                Wayland_SeatSetKeymap(seat);

                സ്ഥിരം Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    എങ്കിൽ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

സ്ഥിതം ശൂന്യം pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : ശൂന്യ;

    എങ്കിൽ (window_data) {
        ഇരട്ട sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        ഇരട്ട sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        എങ്കിൽ (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (ഇരട്ട)window_data->mask.offset_x;
            sy += (ഇരട്ട)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        എങ്കിൽ (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (ദശാംശം)sx, (ദശാംശം)sy);
        } അല്ലെങ്കിൽ {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (ദശാംശം)sx, (ദശാംശം)sy);
        }

        seat->pointer.last_motion.x = (പൂർണ്ണസംഖ്യ)SDL_floor(sx);
        seat->pointer.last_motion.y = (പൂർണ്ണസംഖ്യ)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        എങ്കിൽ (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        എങ്കിൽ (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            തിരഞ്ഞെടുപ്പ് (rc) {
            അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT:
                എങ്കിൽ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത്)) {
                    rc = SDL_HITTEST_NORMAL;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ) {
                    rc = SDL_HITTEST_RESIZE_ഇടത്;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത്) {
                    rc = SDL_HITTEST_RESIZE_മുകൾ;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ:
                എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT:
                എങ്കിൽ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_വലത്)) {
                    rc = SDL_HITTEST_NORMAL;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ) {
                    rc = SDL_HITTEST_RESIZE_വലത്;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_വലത്) {
                    rc = SDL_HITTEST_RESIZE_മുകൾ;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_വലത്:
                എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_വലത്) {
                    rc = SDL_HITTEST_NORMAL;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                എങ്കിൽ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_വലത്)) {
                    rc = SDL_HITTEST_NORMAL;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_വലത്;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_വലത്) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM:
                എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT:
                എങ്കിൽ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത്)) {
                    rc = SDL_HITTEST_NORMAL;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ഇടത്;
                } അല്ലെങ്കിൽ എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത്) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്:
                എങ്കിൽ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത്) {
                    rc = SDL_HITTEST_NORMAL;
                }
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
            }

            എങ്കിൽ (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_motion(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    സ്ഥിരം Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        എങ്കിൽ (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } അല്ലെങ്കിൽ {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

സ്ഥിതം ശൂന്യം pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    എങ്കിൽ (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        തിരികെ;
    }

    എങ്കിൽ (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        തിരികെ;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_എണ്ണം;
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

സ്ഥിതം ശൂന്യം pointer_handle_enter(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                 uint32_t serial, ഘടന wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    എങ്കിൽ (!surface) {
        // Enter event for a destroyed surface.
        തിരികെ;
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

    എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

സ്ഥിതം ശൂന്യം pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    എങ്കിൽ (window) {
        എങ്കിൽ (seat->pointer.focus) {
            എങ്കിൽ (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = ശൂന്യ;
                seat->pointer.focus_surface = ശൂന്യ;
                വേണ്ടി (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    എങ്കിൽ (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                സ്ഥിരം bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                എങ്കിൽ (!--window->pointer_focus_എണ്ണം && had_focus && !window->active_touch_എണ്ണം) {
                    SDL_SetMouseFocus(ശൂന്യ);
                }

                എങ്കിൽ (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_leave(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                 uint32_t serial, ഘടന wl_surface *surface)
{
    എങ്കിൽ (!surface) {
        // Leave event for a destroyed surface.
        തിരികെ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

സ്ഥിതം bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    എങ്കിൽ (seat->pointer.locked_pointer) {
        തിരികെ false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    എങ്കിൽ (window->hit_test) {
        സ്ഥിതം സ്ഥിരം uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_മുകൾ_ഇടത്, XDG_TOPLEVEL_RESIZE_EDGE_മുകൾ,
            XDG_TOPLEVEL_RESIZE_EDGE_മുകൾ_വലത്, XDG_TOPLEVEL_RESIZE_EDGE_വലത്,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_വലത്, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ഇടത്, XDG_TOPLEVEL_RESIZE_EDGE_ഇടത്
        };

#ifdef HAVE_LIBDECOR_H
        സ്ഥിതം സ്ഥിരം uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_മുകൾ_ഇടത്, LIBDECOR_RESIZE_EDGE_മുകൾ,
            LIBDECOR_RESIZE_EDGE_മുകൾ_വലത്, LIBDECOR_RESIZE_EDGE_വലത്,
            LIBDECOR_RESIZE_EDGE_BOTTOM_വലത്, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ഇടത്, LIBDECOR_RESIZE_EDGE_ഇടത്
        };
#endif

        തിരഞ്ഞെടുപ്പ് (window_data->hit_test_result) {
        അവസ്ഥ SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            എങ്കിൽ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                എങ്കിൽ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } അല്ലെങ്കിൽ
#endif
                എങ്കിൽ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                എങ്കിൽ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            തിരികെ true;

        അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT:
        അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ:
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT:
        അവസ്ഥ SDL_HITTEST_RESIZE_വലത്:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM:
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT:
        അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്:
#ifdef HAVE_LIBDECOR_H
            എങ്കിൽ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                എങ്കിൽ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } അല്ലെങ്കിൽ
#endif
                എങ്കിൽ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                എങ്കിൽ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            തിരികെ true;

        സ്ഥിരസ്ഥിതി:
            തിരികെ false;
        }
    }

    തിരികെ false;
}

സ്ഥിതം ശൂന്യം pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    എങ്കിൽ (window) {
        bool ignore_click = false;

        എങ്കിൽ (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            എങ്കിൽ (sdl_button == SDL_BUTTON_ഇടത് && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                തിരികെ; // don't pass this event on to app.
            }
        } അല്ലെങ്കിൽ {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        എങ്കിൽ (window->last_focus_event_time_ns) {
            എങ്കിൽ (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        എങ്കിൽ (!seat->pointer.relative_pointer) {
            എങ്കിൽ (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } അല്ലെങ്കിൽ {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                എങ്കിൽ (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        എങ്കിൽ (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_button(ശൂന്യം *data, ഘടന wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    തിരഞ്ഞെടുപ്പ് (button) {
    അവസ്ഥ BTN_ഇടത്:
        sdl_button = SDL_BUTTON_ഇടത്;
        നിർത്തുക;
    അവസ്ഥ BTN_നടുവ്:
        sdl_button = SDL_BUTTON_നടുവ്;
        നിർത്തുക;
    അവസ്ഥ BTN_വലത്:
        sdl_button = SDL_BUTTON_വലത്;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        നിർത്തുക;
    }

    എങ്കിൽ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    എങ്കിൽ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        എങ്കിൽ (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } അല്ലെങ്കിൽ {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } അല്ലെങ്കിൽ {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t മൂല്യം)
{
    SDL_WindowData *window = seat->pointer.focus;
    സ്ഥിരം എണ്ണൽ wl_pointer_axis a = axis;

    എങ്കിൽ (seat->pointer.focus) {
        ദശാംശം x, y;

        തിരഞ്ഞെടുപ്പ് (a) {
        അവസ്ഥ WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ദശാംശം)wl_fixed_to_double(മൂല്യം);
            നിർത്തുക;
        അവസ്ഥ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (ദശാംശം)wl_fixed_to_double(മൂല്യം);
            y = 0;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            തിരികെ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_common(SDL_WaylandSeat *seat, എണ്ണൽ SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t മൂല്യം)
{
    സ്ഥിരം എണ്ണൽ wl_pointer_axis a = axis;

    എങ്കിൽ (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        തിരഞ്ഞെടുപ്പ് (a) {
        അവസ്ഥ WL_POINTER_AXIS_VERTICAL_SCROLL:
            തിരഞ്ഞെടുപ്പ് (type) {
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                എങ്കിൽ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                നിർത്തുക;
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                എങ്കിൽ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                }
                നിർത്തുക;
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                എങ്കിൽ (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                }
                നിർത്തുക;
            }
            നിർത്തുക;
        അവസ്ഥ WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            തിരഞ്ഞെടുപ്പ് (type) {
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                എങ്കിൽ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                നിർത്തുക;
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                എങ്കിൽ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                }
                നിർത്തുക;
            അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                എങ്കിൽ (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (ദശാംശം)wl_fixed_to_double(മൂല്യം);
                }
                നിർത്തുക;
            }
            നിർത്തുക;
        }
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_axis(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t മൂല്യം)
{
    SDL_WaylandSeat *seat = data;
    സ്ഥിരം Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    എങ്കിൽ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, മൂല്യം);
    } അല്ലെങ്കിൽ {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, മൂല്യം);
    }
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_relative_direction(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    തിരഞ്ഞെടുപ്പ് (axis_relative_direction) {
    അവസ്ഥ WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        നിർത്തുക;
    അവസ്ഥ WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        നിർത്തുക;
    }
}

സ്ഥിതം ശൂന്യം pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    എങ്കിൽ (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ഇരട്ട dx;
        ഇരട്ട dy;
        എങ്കിൽ (mouse->നിവേശം_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } അല്ലെങ്കിൽ {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (ദശാംശം)dx, (ദശാംശം)dy);
    }
}

സ്ഥിതം ശൂന്യം pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    ദശാംശം x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    തിരഞ്ഞെടുപ്പ് (seat->pointer.pending_frame.axis.x_axis_type) {
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        നിർത്തുക;
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        നിർത്തുക;
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        x = 0.0f;
        നിർത്തുക;
    }

    തിരഞ്ഞെടുപ്പ് (seat->pointer.pending_frame.axis.y_axis_type) {
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        നിർത്തുക;
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        നിർത്തുക;
    അവസ്ഥ SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        y = 0.0f;
        നിർത്തുക;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

സ്ഥിതം ശൂന്യം pointer_handle_frame(ശൂന്യം *data, ഘടന wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    എങ്കിൽ (seat->pointer.pending_frame.enter_surface) {
        എങ്കിൽ (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            എങ്കിൽ (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = ശൂന്യ;
                seat->pointer.pending_frame.leave_surface = ശൂന്യ;
            } അല്ലെങ്കിൽ {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = ശൂന്യ;
            }
        }

        എങ്കിൽ (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    എങ്കിൽ (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    എങ്കിൽ (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    വേണ്ടി (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        സ്ഥിരം Uint32 mask = SDL_BUTTON_MASK(i);
        എങ്കിൽ (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        എങ്കിൽ (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    എങ്കിൽ (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    എങ്കിൽ (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_source(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_stop(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_discrete(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

സ്ഥിതം ശൂന്യം pointer_handle_axis_value120(ശൂന്യം *data, ഘടന wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

സ്ഥിതം ശൂന്യം pointer_handle_warp(ശൂന്യം *data, ഘടന wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

സ്ഥിതം സ്ഥിരം ഘടന wl_pointer_listener pointer_listener = {
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

സ്ഥിതം ശൂന്യം relative_pointer_handle_relative_motion(ശൂന്യം *data,
                                                    ഘടന zwp_relative_pointer_v1 *pointer,
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

    എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } അല്ലെങ്കിൽ {
        pointer_dispatch_relative_motion(seat);
    }
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

സ്ഥിതം ശൂന്യം locked_pointer_locked(ശൂന്യം *data, ഘടന zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

സ്ഥിതം ശൂന്യം locked_pointer_unlocked(ശൂന്യം *data, ഘടന zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

സ്ഥിതം ശൂന്യം confined_pointer_confined(ശൂന്യം *data, ഘടന zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

സ്ഥിതം ശൂന്യം confined_pointer_unconfined(ശൂന്യം *data, ഘടന zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

സ്ഥിതം ശൂന്യം touch_handler_down(ശൂന്യം *data, ഘടന wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ഘടന wl_surface *surface,
                               പൂർണ്ണസംഖ്യ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    എങ്കിൽ (!surface) {
        തിരികെ;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    എങ്കിൽ (window_data && window_data->surface == surface) {
        ദശാംശം x, y;

        എങ്കിൽ (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } അല്ലെങ്കിൽ {
            x = (ദശാംശം)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        എങ്കിൽ (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } അല്ലെങ്കിൽ {
            y = (ദശാംശം)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_എണ്ണം;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

സ്ഥിതം ശൂന്യം touch_handler_up(ശൂന്യം *data, ഘടന wl_touch *touch, uint32_t serial, uint32_t timestamp, പൂർണ്ണസംഖ്യ id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    ഘടന wl_surface *surface = ശൂന്യ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    എങ്കിൽ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        എങ്കിൽ (window_data && window_data->surface == surface) {
            സ്ഥിരം ദശാംശം x = (ദശാംശം)wl_fixed_to_double(fx) / window_data->current.logical_width;
            സ്ഥിരം ദശാംശം y = (ദശാംശം)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_എണ്ണം;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            എങ്കിൽ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_എണ്ണം &&
                !window_data->pointer_focus_എണ്ണം && !window_data->active_touch_എണ്ണം) {
                SDL_SetMouseFocus(ശൂന്യ);
            }
        }
    }
}

സ്ഥിതം ശൂന്യം touch_handler_motion(ശൂന്യം *data, ഘടന wl_touch *touch, uint32_t timestamp, പൂർണ്ണസംഖ്യ id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ഘടന wl_surface *surface = ശൂന്യ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    എങ്കിൽ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        എങ്കിൽ (window_data && window_data->surface == surface) {
            സ്ഥിരം ദശാംശം x = (ദശാംശം)wl_fixed_to_double(fx) / window_data->current.logical_width;
            സ്ഥിരം ദശാംശം y = (ദശാംശം)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

സ്ഥിതം ശൂന്യം touch_handler_frame(ശൂന്യം *data, ഘടന wl_touch *touch)
{
}

സ്ഥിതം ശൂന്യം touch_handler_cancel(ശൂന്യം *data, ഘടന wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

സ്ഥിതം ശൂന്യം touch_handler_shape(ശൂന്യം *data, ഘടന wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

സ്ഥിതം ശൂന്യം touch_handler_orientation(ശൂന്യം *data, ഘടന wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

സ്ഥിതം സ്ഥിരം ഘടന wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#എങ്കിൽ !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
സ്ഥിതം size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t താക്കോൽ, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    എങ്കിൽ (!masks_out || !masks_size) {
        തിരികെ 0;
    }

    // Level 0 is always unmodified, so early out.
    എങ്കിൽ (level == 0) {
        *masks_out = 0;
        തിരികെ 1;
    }

    size_t mask_idx = 0;
    സ്ഥിരം xkb_mod_mask_t keymod_masks[] = {
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
    സ്ഥിരം xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    സ്ഥിരം xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    വേണ്ടി (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        എങ്കിൽ (WAYLAND_xkb_state_താക്കോൽ_get_level(seat->keyboard.xkb.state, താക്കോൽ, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            എങ്കിൽ (++mask_idx == masks_size) {
                നിർത്തുക;
            }
        }
    }

    തിരികെ mask_idx;
}
#endif

സ്ഥിതം ശൂന്യം Wayland_KeymapIterator(ഘടന xkb_keymap *keymap, xkb_keycode_t താക്കോൽ, ശൂന്യം *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    സ്ഥിരം xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    സ്ഥിരം xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    എങ്കിൽ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, താക്കോൽ - 8);
    }

    വേണ്ടി (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.അക്കം_layouts; ++layout) {
        സ്ഥിരം xkb_level_index_t അക്കം_levels = WAYLAND_xkb_keymap_അക്കം_levels_for_താക്കോൽ(seat->keyboard.xkb.keymap, താക്കോൽ, layout);
        വേണ്ടി (xkb_level_index_t level = 0; level < അക്കം_levels; ++level) {
            എങ്കിൽ (WAYLAND_xkb_keymap_താക്കോൽ_get_syms_by_level(seat->keyboard.xkb.keymap, താക്കോൽ, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_താക്കോൽ_Sym(syms[0], താക്കോൽ);
                    എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
                        തുടരുക;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#എങ്കിൽ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                സ്ഥിരം size_t അക്കം_masks = WAYLAND_xkb_keymap_താക്കോൽ_get_mods_for_level(seat->keyboard.xkb.keymap, താക്കോൽ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#അല്ലെങ്കിൽ
                സ്ഥിരം size_t അക്കം_masks = xkb_legacy_get_mods_for_level(seat, താക്കോൽ, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                വേണ്ടി (size_t mask = 0; mask < അക്കം_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    എങ്കിൽ ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        തുടരുക;
                    }

                    സ്ഥിരം SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_താക്കോൽ_Code_From_താക്കോൽ_Sym(syms[0], താക്കോൽ, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    എങ്കിൽ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        എങ്കിൽ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_താക്കോൽ *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, വലുപ്പം(Wayland_Reserved_താക്കോൽ));
                        എങ്കിൽ (res) {
                            res->scancode = scancode;
                            res->താക്കോൽ = താക്കോൽ - 8;
                        }
                    }

                    എങ്കിൽ (!keycode) {
                        തിരഞ്ഞെടുപ്പ് (scancode) {
                        അവസ്ഥ SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            നിർത്തുക;
                        അവസ്ഥ SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            നിർത്തുക;
                        അവസ്ഥ SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            നിർത്തുക;
                        അവസ്ഥ SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            നിർത്തുക;
                        സ്ഥിരസ്ഥിതി:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            നിർത്തുക;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

സ്ഥിതം ശൂന്യം keyboard_handle_keymap(ശൂന്യം *data, ഘടന wl_keyboard *keyboard,
                                   uint32_t format, പൂർണ്ണസംഖ്യ fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    അക്ഷരം *map_str;

    എങ്കിൽ (!data) {
        close(fd);
        തിരികെ;
    }

    എങ്കിൽ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        തിരികെ;
    }

    map_str = mmap(ശൂന്യ, size, PROT_READ, MAP_PRIVATE, fd, 0);
    എങ്കിൽ (map_str == MAP_FAILED) {
        close(fd);
        തിരികെ;
    }

    എങ്കിൽ (seat->keyboard.xkb.keymap != ശൂന്യ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ശൂന്യ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    എങ്കിൽ (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        തിരികെ;
    }

    // Clear the old layouts.
    വേണ്ടി (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.അക്കം_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ശൂന്യ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.അക്കം_layouts = 0;

#എങ്കിൽ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.അക്കം_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_അക്കം);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#അല്ലെങ്കിൽ
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.അക്കം_mask = 1 << GET_MOD_INDEX(അക്കം_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    എങ്കിൽ (seat->keyboard.xkb.state != ശൂന്യ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ശൂന്യ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    എങ്കിൽ (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ശൂന്യ;
        തിരികെ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ശൂന്യ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.അക്കം_layouts = WAYLAND_xkb_keymap_അക്കം_layouts(seat->keyboard.xkb.keymap);
    എങ്കിൽ (seat->keyboard.xkb.അക്കം_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.അക്കം_layouts, വലുപ്പം(SDL_Keymap *));
        എങ്കിൽ (!seat->keyboard.sdl_keymap) {
            തിരികെ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        വേണ്ടി (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.അക്കം_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            എങ്കിൽ (!seat->keyboard.sdl_keymap[i]) {
                വേണ്ടി (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ശൂന്യ;
                തിരികെ;
            }
        }

        WAYLAND_xkb_keymap_താക്കോൽ_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.അക്കം_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    സ്ഥിരം അക്ഷരം *locale = SDL_getenv("LC_ALL");
    എങ്കിൽ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        എങ്കിൽ (!locale) {
            locale = SDL_getenv("LANG");
            എങ്കിൽ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    എങ്കിൽ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        എങ്കിൽ (seat->keyboard.xkb.compose_table != ശൂന്യ) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = ശൂന്യ;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        എങ്കിൽ (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            എങ്കിൽ (seat->keyboard.xkb.compose_state != ശൂന്യ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ശൂന്യ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            എങ്കിൽ (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = ശൂന്യ;
            }
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
സ്ഥിതം SDL_Scancode Wayland_Get_Scancode_For_താക്കോൽ(SDL_WaylandSeat *seat, Uint32 താക്കോൽ, സ്ഥിരം xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    എങ്കിൽ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, താക്കോൽ);

        // No table entry? Check the reserved list.
        എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_താക്കോൽ *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                എങ്കിൽ (i->താക്കോൽ == താക്കോൽ) {
                    തിരികെ i->scancode;
                }
            }
        }
    } അല്ലെങ്കിൽ {
        സ്ഥിരം xkb_keysym_t *keysym;
        എങ്കിൽ (WAYLAND_xkb_state_താക്കോൽ_get_syms(seat->keyboard.xkb.state, താക്കോൽ + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_താക്കോൽ_Sym(keysym[0], താക്കോൽ + 8);
            എങ്കിൽ (syms) {
                *syms = keysym;
            }
        }
    }

    തിരികെ scancode;
}

സ്ഥിതം ശൂന്യം Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool താക്കോൽ_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    എങ്കിൽ (!താക്കോൽ_pressed) {
        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } അല്ലെങ്കിൽ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } അല്ലെങ്കിൽ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } അല്ലെങ്കിൽ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } അല്ലെങ്കിൽ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } അല്ലെങ്കിൽ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        എങ്കിൽ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            എങ്കിൽ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } അല്ലെങ്കിൽ {
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
    സ്ഥിരം xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        എങ്കിൽ (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        എങ്കിൽ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        എങ്കിൽ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        എങ്കിൽ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } അല്ലെങ്കിൽ എങ്കിൽ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    എങ്കിൽ (xkb_locked_modifiers & seat->keyboard.xkb.അക്കം_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_അക്കം;
    } അല്ലെങ്കിൽ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_അക്കം;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

സ്ഥിതം ശൂന്യം Wayland_Handle_Modifier_താക്കോലുകൾ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    സ്ഥിരം SDL_Keycode keycode = SDL_Get_താക്കോൽ_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    തിരഞ്ഞെടുപ്പ് (keycode) {
    അവസ്ഥ SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        നിർത്തുക;
    അവസ്ഥ SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        നിർത്തുക;
    അവസ്ഥ SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        നിർത്തുക;
    അവസ്ഥ SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        നിർത്തുക;
    അവസ്ഥ SDLK_LALT:
        mod = SDL_KMOD_LALT;
        നിർത്തുക;
    അവസ്ഥ SDLK_RALT:
        mod = SDL_KMOD_RALT;
        നിർത്തുക;
    അവസ്ഥ SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        നിർത്തുക;
    അവസ്ഥ SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        നിർത്തുക;
    അവസ്ഥ SDLK_MODE:
        mod = SDL_KMOD_MODE;
        നിർത്തുക;
    അവസ്ഥ SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ;
    }

    എങ്കിൽ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } അല്ലെങ്കിൽ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

സ്ഥിതം ശൂന്യം keyboard_handle_enter(ശൂന്യം *data, ഘടന wl_keyboard *keyboard,
                                  uint32_t serial, ഘടന wl_surface *surface,
                                  ഘടന wl_array *താക്കോലുകൾ)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *താക്കോൽ;

    എങ്കിൽ (!surface) {
        // Enter event for a destroyed surface.
        തിരികെ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    എങ്കിൽ (!window) {
        // Not a surface owned by SDL.
        തിരികെ;
    }

    ++window->keyboard_focus_എണ്ണം;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_നിവേശം(seat);

#ifdef SDL_USE_IME
    എങ്കിൽ (!seat->text_നിവേശം.zwp_text_നിവേശം) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (താക്കോൽ, താക്കോലുകൾ) {
        സ്ഥിരം SDL_Scancode scancode = Wayland_Get_Scancode_For_താക്കോൽ(seat, *താക്കോൽ, ശൂന്യ);
        എങ്കിൽ (scancode != SDL_SCANCODE_UNKNOWN) {
            സ്ഥിരം SDL_Keycode keycode = SDL_Get_താക്കോൽ_From_Scancode(scancode, SDL_KMOD_NONE, false);

            തിരഞ്ഞെടുപ്പ് (keycode) {
            അവസ്ഥ SDLK_LSHIFT:
            അവസ്ഥ SDLK_RSHIFT:
            അവസ്ഥ SDLK_LCTRL:
            അവസ്ഥ SDLK_RCTRL:
            അവസ്ഥ SDLK_LALT:
            അവസ്ഥ SDLK_RALT:
            അവസ്ഥ SDLK_LGUI:
            അവസ്ഥ SDLK_RGUI:
            അവസ്ഥ SDLK_MODE:
            അവസ്ഥ SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_താക്കോലുകൾ(seat, scancode, true);
                SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *താക്കോൽ, scancode, true);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
            }
        }
    }
}

സ്ഥിതം ശൂന്യം keyboard_handle_leave(ശൂന്യം *data, ഘടന wl_keyboard *keyboard,
                                  uint32_t serial, ഘടന wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    എങ്കിൽ (!surface) {
        // Leave event for a destroyed surface.
        തിരികെ;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    എങ്കിൽ (!window) {
        // Not a surface owned by SDL.
        തിരികെ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.താക്കോൽ = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ആകുമ്പോൾ (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    സ്ഥിരം bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ശൂന്യ;
    --window->keyboard_focus_എണ്ണം;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    എങ്കിൽ (!window->keyboard_focus_എണ്ണം && had_focus) {
        SDL_SetKeyboardFocus(ശൂന്യ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_നിവേശം(seat);

#ifdef SDL_USE_IME
    എങ്കിൽ (!seat->text_നിവേശം.zwp_text_നിവേശം && !window->keyboard_focus_എണ്ണം) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    എങ്കിൽ (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_എണ്ണം && !window->active_touch_എണ്ണം) {
        SDL_SetMouseFocus(ശൂന്യ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, ശൂന്യ);
}

സ്ഥിതം bool keyboard_നിവേശം_get_text(അക്ഷരം text[8], സ്ഥിരം SDL_WaylandSeat *seat, uint32_t താക്കോൽ, bool down, bool *handled_by_ime)
{
    സ്ഥിരം xkb_keysym_t *syms;
    xkb_keysym_t sym;

    എങ്കിൽ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        തിരികെ false;
    }

    // TODO: Can this happen?
    എങ്കിൽ (WAYLAND_xkb_state_താക്കോൽ_get_syms(seat->keyboard.xkb.state, താക്കോൽ + 8, &syms) != 1) {
        തിരികെ false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    എങ്കിൽ (SDL_IME_Process_താക്കോൽ_Event(sym, താക്കോൽ + 8, down)) {
        എങ്കിൽ (handled_by_ime) {
            *handled_by_ime = true;
        }
        തിരികെ true;
    }
#endif

    എങ്കിൽ (!down) {
        തിരികെ false;
    }

    എങ്കിൽ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        തിരഞ്ഞെടുപ്പ് (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        അവസ്ഥ XKB_COMPOSE_COMPOSING:
            എങ്കിൽ (handled_by_ime) {
                *handled_by_ime = true;
            }
            തിരികെ true;
        അവസ്ഥ XKB_COMPOSE_CANCELLED:
        സ്ഥിരസ്ഥിതി:
            sym = XKB_താക്കോൽ_No_ചിഹ്നം;
            നിർത്തുക;
        അവസ്ഥ XKB_COMPOSE_NOTHING:
            നിർത്തുക;
        അവസ്ഥ XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            നിർത്തുക;
        }
    }

    തിരികെ WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

സ്ഥിതം ശൂന്യം keyboard_handle_താക്കോൽ(ശൂന്യം *data, ഘടന wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t താക്കോൽ,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    എണ്ണൽ wl_keyboard_താക്കോൽ_state state = state_w;
    അക്ഷരം text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    സ്ഥിരം Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    എങ്കിൽ (state == WL_KEYBOARD_താക്കോൽ_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        എങ്കിൽ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_താക്കോൽ_repeats(seat->keyboard.xkb.keymap, താക്കോൽ + 8)) {
            തിരികെ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_താക്കോൽ_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    എങ്കിൽ (state == WL_KEYBOARD_താക്കോൽ_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        എങ്കിൽ (keyboard_focus && SDL_Text_നിവേശം_Active(keyboard_focus)) {
            has_text = keyboard_നിവേശം_get_text(text, seat, താക്കോൽ, true, &handled_by_ime);
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (താക്കോൽ == seat->keyboard.repeat.താക്കോൽ) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            സ്ഥിരം Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.താക്കോൽ = 0;
        }
        keyboard_നിവേശം_get_text(text, seat, താക്കോൽ, false, &handled_by_ime);
    }

    സ്ഥിരം xkb_keysym_t *syms = ശൂന്യ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_താക്കോൽ(seat, താക്കോൽ, &syms);
    Wayland_Handle_Modifier_താക്കോലുകൾ(seat, scancode, state == WL_KEYBOARD_താക്കോൽ_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        സ്ഥിരം SDL_Keycode keycode = (SDL_Keycode)SDL_താക്കോൽ_Sym_To_Ucs4(syms[0]);
        എങ്കിൽ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            എങ്കിൽ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_താക്കോൽ_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, താക്കോൽ, scancode, state == WL_KEYBOARD_താക്കോൽ_STATE_PRESSED);

    എങ്കിൽ (state == WL_KEYBOARD_താക്കോൽ_STATE_PRESSED) {
        എങ്കിൽ (handled_by_ime) {
            has_text = false;
        }
        എങ്കിൽ (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        എങ്കിൽ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_താക്കോൽ_repeats(seat->keyboard.xkb.keymap, താക്കോൽ + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, താക്കോൽ, time, timestamp_ns, scancode, has_text ? text : ശൂന്യ);
        }
    }
}

സ്ഥിതം ശൂന്യം keyboard_handle_modifiers(ശൂന്യം *data, ഘടന wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    സ്ഥിരം uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    എങ്കിൽ (!seat->keyboard.xkb.state) {
        തിരികെ;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    എങ്കിൽ (seat->keyboard.repeat.താക്കോൽ) {
        അക്ഷരം text[8];

        എങ്കിൽ (keyboard_നിവേശം_get_text(text, seat, seat->keyboard.repeat.താക്കോൽ, true, ശൂന്യ)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    എങ്കിൽ (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        എങ്കിൽ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

സ്ഥിതം ശൂന്യം keyboard_handle_repeat_info(ശൂന്യം *data, ഘടന wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    എങ്കിൽ (!rate) {
        seat->keyboard.repeat.താക്കോൽ = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

സ്ഥിതം സ്ഥിരം ഘടന wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_താക്കോൽ,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

സ്ഥിതം ശൂന്യം Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    എങ്കിൽ (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    എങ്കിൽ (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = ശൂന്യ;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    എങ്കിൽ (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    എങ്കിൽ (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    എങ്കിൽ (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    എങ്കിൽ (seat->pointer.timestamps) {
        zwp_നിവേശം_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    എങ്കിൽ (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    എങ്കിൽ (seat->pointer.wl_pointer) {
        എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } അല്ലെങ്കിൽ {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

സ്ഥിതം ശൂന്യം Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    എങ്കിൽ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    എങ്കിൽ (seat->keyboard.sdl_keymap) {
        എങ്കിൽ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.അക്കം_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        വേണ്ടി (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.അക്കം_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ശൂന്യ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    എങ്കിൽ (seat->keyboard.താക്കോൽ_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.താക്കോൽ_inhibitor);
    }

    എങ്കിൽ (seat->keyboard.timestamps) {
        zwp_നിവേശം_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    എങ്കിൽ (seat->keyboard.wl_keyboard) {
        എങ്കിൽ (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } അല്ലെങ്കിൽ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    എങ്കിൽ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    എങ്കിൽ (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    എങ്കിൽ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    എങ്കിൽ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

സ്ഥിതം ശൂന്യം Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    എങ്കിൽ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    എങ്കിൽ (seat->touch.timestamps) {
        zwp_നിവേശം_timestamps_v1_destroy(seat->touch.timestamps);
    }

    എങ്കിൽ (seat->touch.wl_touch) {
        എങ്കിൽ (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } അല്ലെങ്കിൽ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

സ്ഥിതം ശൂന്യം seat_handle_capabilities(ശൂന്യം *data, ഘടന wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    അക്ഷരം name_fmt[256];

    എങ്കിൽ ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        എങ്കിൽ (seat->name) {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } അല്ലെങ്കിൽ {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } അല്ലെങ്കിൽ എങ്കിൽ (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    എങ്കിൽ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        എങ്കിൽ (seat->name) {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } അല്ലെങ്കിൽ {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } അല്ലെങ്കിൽ എങ്കിൽ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    എങ്കിൽ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        എങ്കിൽ (seat->name) {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } അല്ലെങ്കിൽ {
            SDL_snprintf(name_fmt, വലുപ്പം(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } അല്ലെങ്കിൽ എങ്കിൽ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_നിവേശം_Timestamp_Listeners(seat);
}

സ്ഥിതം ശൂന്യം seat_handle_name(ശൂന്യം *data, ഘടന wl_seat *wl_seat, സ്ഥിരം അക്ഷരം *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    എങ്കിൽ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

സ്ഥിതം സ്ഥിരം ഘടന wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

സ്ഥിതം ശൂന്യം data_offer_handle_offer(ശൂന്യം *data, ഘടന wl_data_offer *wl_data_offer,
                                    സ്ഥിരം അക്ഷരം *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

സ്ഥിതം ശൂന്യം data_offer_handle_source_actions(ശൂന്യം *data, ഘടന wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

സ്ഥിതം ശൂന്യം data_offer_handle_actions(ശൂന്യം *data, ഘടന wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

സ്ഥിതം സ്ഥിരം ഘടന wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

സ്ഥിതം ശൂന്യം primary_selection_offer_handle_offer(ശൂന്യം *data, ഘടന zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 സ്ഥിരം അക്ഷരം *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

സ്ഥിതം ശൂന്യം data_device_handle_data_offer(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device,
                                          ഘടന wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, വലുപ്പം(*data_offer));
    എങ്കിൽ (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id) : -1));
    }
}

സ്ഥിതം ശൂന്യം data_device_handle_enter(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device,
                                     uint32_t serial, ഘടന wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ഘടന wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ശൂന്യ;
    data_device->has_mime_file = false;
    data_device->text_mime_type = ശൂന്യ;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    എങ്കിൽ (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    എങ്കിൽ (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        എങ്കിൽ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        എങ്കിൽ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        എങ്കിൽ (!data_device->has_mime_file) {
            size_t mime_എണ്ണം = 0;
            സ്ഥിരം അക്ഷരം *സ്ഥിരം *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_എണ്ണം);
            വേണ്ടി (size_t i = 0; i < mime_എണ്ണം; ++i) {
                എങ്കിൽ (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    നിർത്തുക;
                }
            }
        }

        എങ്കിൽ (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            എങ്കിൽ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            ഇരട്ട dx = wl_fixed_to_double(x);
            ഇരട്ട dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            എങ്കിൽ (surface == window->mask.surface) {
                dx += (ഇരട്ട)window->mask.offset_x;
                dy += (ഇരട്ട)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (ദശാംശം)dx, (ദശാംശം)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } അല്ലെങ്കിൽ {
            // Decline the offer.
            wl_data_offer_accept(id, serial, ശൂന്യ);
            എങ്കിൽ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } അല്ലെങ്കിൽ {
        data_device->dnd_window = ശൂന്യ;
        data_device->dnd_surface = ശൂന്യ;

        // Decline the offer.
        എങ്കിൽ (id) {
            wl_data_offer_accept(id, serial, ശൂന്യ);
            എങ്കിൽ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

സ്ഥിതം ശൂന്യം data_device_handle_leave(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    എങ്കിൽ (data_device->drag_offer) {
        എങ്കിൽ (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } അല്ലെങ്കിൽ {
            SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = ശൂന്യ;
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = ശൂന്യ;
}

സ്ഥിതം ശൂന്യം data_device_handle_motion(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    എങ്കിൽ (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        ഇരട്ട dx = wl_fixed_to_double(x);
        ഇരട്ട dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        എങ്കിൽ (data_device->dnd_surface == window_data->mask.surface) {
            dx += (ഇരട്ട)window_data->mask.offset_x;
            dy += (ഇരട്ട)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (ദശാംശം)dx, (ദശാംശം)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

സ്ഥിതം ശൂന്യം drop_cleanup_handler(ശൂന്യം *data, ഘടന wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

സ്ഥിതം സ്ഥിരം ഘടന wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

സ്ഥിതം ശൂന്യം drop_dispatch_handler(ശൂന്യം *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    എങ്കിൽ (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        എങ്കിൽ (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            ശൂന്യം *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            എങ്കിൽ (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                എങ്കിൽ (dbus) {
                    പൂർണ്ണസംഖ്യ path_എണ്ണം = 0;
                    അക്ഷരം **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_എണ്ണം);
                    // If dropped files contain a directory the list is empty
                    എങ്കിൽ (paths && path_എണ്ണം > 0) {
                        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < path_എണ്ണം; i++) {
                            SDL_SendDropFile(drop->dnd_window, ശൂന്യ, paths[i]);
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
        എങ്കിൽ (!drop_handled) {
            എങ്കിൽ (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                ശൂന്യം *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                എങ്കിൽ (buffer) {
                    അക്ഷരം *saveptr = ശൂന്യ;
                    അക്ഷരം *token = SDL_strtok_r((അക്ഷരം *)buffer, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token) {
                        എങ്കിൽ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, ശൂന്യ, token);
                        }
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                ശൂന്യം *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                എങ്കിൽ (buffer) {
                    അക്ഷരം *saveptr = ശൂന്യ;
                    അക്ഷരം *token = SDL_strtok_r((അക്ഷരം *)buffer, "\r\n", &saveptr);
                    ആകുമ്പോൾ (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(ശൂന്യ, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        എങ്കിൽ (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = ശൂന്യ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

സ്ഥിതം ശൂന്യം data_device_handle_drop(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    എങ്കിൽ (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, വലുപ്പം(Wayland_DropData));
        എങ്കിൽ (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_തിരുകുക(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } അല്ലെങ്കിൽ {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } അല്ലെങ്കിൽ {
        SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = ശൂന്യ;
}

സ്ഥിതം ശൂന്യം data_device_handle_selection(ശൂന്യം *data, ഘടന wl_data_device *wl_data_device,
                                         ഘടന wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = ശൂന്യ;

    എങ്കിൽ (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

സ്ഥിതം സ്ഥിരം ഘടന wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

സ്ഥിതം ശൂന്യം primary_selection_device_handle_offer(ശൂന്യം *data, ഘടന zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ഘടന zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, വലുപ്പം(*primary_selection_offer));
    എങ്കിൽ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id) : -1));
}

സ്ഥിതം ശൂന്യം primary_selection_device_handle_selection(ശൂന്യം *data, ഘടന zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ഘടന zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = ശൂന്യ;

    എങ്കിൽ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    എങ്കിൽ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ഘടന wl_proxy *)id) : -1));
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

സ്ഥിതം ശൂന്യം text_നിവേശം_enter(ശൂന്യം *data,
                             ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                             ഘടന wl_surface *surface)
{
    // No-op
}

സ്ഥിതം ശൂന്യം text_നിവേശം_leave(ശൂന്യം *data,
                             ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                             ഘടന wl_surface *surface)
{
    // No-op
}

സ്ഥിതം ശൂന്യം text_നിവേശം_preedit_string(ശൂന്യം *data,
                                      ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                                      സ്ഥിരം അക്ഷരം *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_നിവേശം.has_preedit = true;
    എങ്കിൽ (text) {
        പൂർണ്ണസംഖ്യ cursor_begin_utf8 = cursor_begin >= 0 ? (പൂർണ്ണസംഖ്യ)SDL_utf8strnlen(text, cursor_begin) : -1;
        പൂർണ്ണസംഖ്യ cursor_end_utf8 = cursor_end >= 0 ? (പൂർണ്ണസംഖ്യ)SDL_utf8strnlen(text, cursor_end) : -1;
        പൂർണ്ണസംഖ്യ cursor_size_utf8;
        എങ്കിൽ (cursor_end_utf8 >= 0) {
            എങ്കിൽ (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } അല്ലെങ്കിൽ {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } അല്ലെങ്കിൽ {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } അല്ലെങ്കിൽ {
        SDL_SendEditingText("", 0, 0);
    }
}

സ്ഥിതം ശൂന്യം text_നിവേശം_commit_string(ശൂന്യം *data,
                                     ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                                     സ്ഥിരം അക്ഷരം *text)
{
    SDL_SendKeyboardText(text);
}

സ്ഥിതം ശൂന്യം text_നിവേശം_delete_surrounding_text(ശൂന്യം *data,
                                               ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

സ്ഥിതം ശൂന്യം text_നിവേശം_done(ശൂന്യം *data,
                            ഘടന zwp_text_നിവേശം_v3 *zwp_text_നിവേശം_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    എങ്കിൽ (!seat->text_നിവേശം.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_നിവേശം.has_preedit = false;
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_text_നിവേശം_v3_listener text_നിവേശം_listener = {
    text_നിവേശം_enter,
    text_നിവേശം_leave,
    text_നിവേശം_preedit_string,
    text_നിവേശം_commit_string,
    text_നിവേശം_delete_surrounding_text,
    text_നിവേശം_done
};

സ്ഥിതം ശൂന്യം Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    എങ്കിൽ (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        എങ്കിൽ (dbus) {
            സ്ഥിരം അക്ഷരം *id = dbus->bus_get_unique_name(dbus->session_conn);
            എങ്കിൽ (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    എങ്കിൽ (!data_device->id_str)
#endif
    {
        അക്ഷരം id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, വലുപ്പം(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (!seat->display->data_device_manager) {
        തിരികെ;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, വലുപ്പം(*data_device));
    എങ്കിൽ (!data_device) {
        തിരികെ;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    എങ്കിൽ (!data_device->data_device) {
        SDL_free(data_device);
        തിരികെ;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

ശൂന്യം Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (!seat->display->primary_selection_device_manager) {
        തിരികെ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, വലുപ്പം(*primary_selection_device));
    എങ്കിൽ (!primary_selection_device) {
        തിരികെ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    എങ്കിൽ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } അല്ലെങ്കിൽ {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

ശൂന്യം Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

സ്ഥിതം ശൂന്യം Wayland_Seat_Create_Text_നിവേശം(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->display->text_നിവേശം_manager) {
        seat->text_നിവേശം.zwp_text_നിവേശം = zwp_text_നിവേശം_manager_v3_get_text_നിവേശം(seat->display->text_നിവേശം_manager, seat->wl_seat);

        എങ്കിൽ (seat->text_നിവേശം.zwp_text_നിവേശം) {
            zwp_text_നിവേശം_v3_set_user_data(seat->text_നിവേശം.zwp_text_നിവേശം, seat);
            zwp_text_നിവേശം_v3_add_listener(seat->text_നിവേശം.zwp_text_നിവേശം,
                                           &text_നിവേശം_listener, seat);
        }
    }
}

ശൂന്യം Wayland_Display_Init_Text_നിവേശം_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_നിവേശം(seat);
    }
}

// Pen/Tablet support...
സ്ഥിതം ശൂന്യം tablet_tool_handle_type(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    തിരഞ്ഞെടുപ്പ് (type) {
        #define CASE(typ) അവസ്ഥ ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; തിരികെ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        സ്ഥിരസ്ഥിതി: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_hardware_serial(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_hardware_id_wacom(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_capability(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    തിരഞ്ഞെടുപ്പ് (capability) {
        #define CASE(wltyp,sdltyp) അവസ്ഥ ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; തിരികെ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        സ്ഥിരസ്ഥിതി: നിർത്തുക;  // unsupported here.
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_done(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    എങ്കിൽ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ശൂന്യ;
        sdltool->instance_id = SDL_AddPenDevice(0, ശൂന്യ, window, &sdltool->info, sdltool, false);
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_removed(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    എങ്കിൽ (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ശൂന്യ;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_proximity_in(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t serial, ഘടന zwp_tablet_v2 *tablet, ഘടന wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ശൂന്യ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ശൂന്യ;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_proximity_out(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_down(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_up(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_motion(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    എങ്കിൽ (windowdata) {
        sdltool->frame.x = (ദശാംശം)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (ദശാംശം)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_pressure(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((ദശാംശം) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    എങ്കിൽ (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_distance(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((ദശാംശം) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    എങ്കിൽ (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_tilt(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (ദശാംശം)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (ദശാംശം)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_button(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    പൂർണ്ണസംഖ്യ sdlbutton;

    തിരഞ്ഞെടുപ്പ് (button) {
    അവസ്ഥ BTN_STYLUS:
        sdlbutton = 1;
        നിർത്തുക;
    അവസ്ഥ BTN_STYLUS2:
        sdlbutton = 2;
        നിർത്തുക;
    അവസ്ഥ BTN_STYLUS3:
        sdlbutton = 3;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_rotation(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    സ്ഥിരം ദശാംശം rotation = (ദശാംശം)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_slider(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_wheel(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

സ്ഥിതം ശൂന്യം tablet_tool_handle_frame(ശൂന്യം *data, ഘടന zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    സ്ഥിരം SDL_PenID instance_id = sdltool->instance_id;
    എങ്കിൽ (!instance_id) {
        തിരികെ;  // Not a pen we report on.
    }

    സ്ഥിരം Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ശൂന്യ;
    സ്ഥിരം bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    എങ്കിൽ (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    എങ്കിൽ (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        എങ്കിൽ (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } അല്ലെങ്കിൽ {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        എങ്കിൽ (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    വേണ്ടി (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_എണ്ണം; i++) {
        എങ്കിൽ (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ state = sdltool->frame.buttons[i];
        എങ്കിൽ (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    എങ്കിൽ (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = ശൂന്യ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


സ്ഥിതം ശൂന്യം tablet_seat_handle_tablet_added(ശൂന്യം *data, ഘടന zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ഘടന zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

സ്ഥിതം ശൂന്യം tablet_seat_handle_tool_added(ശൂന്യം *data, ഘടന zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ഘടന zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, വലുപ്പം(*sdltool));

    എങ്കിൽ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.അക്കം_buttons = -1;

        എങ്കിൽ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_തിരുകുക(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

സ്ഥിതം ശൂന്യം tablet_seat_handle_pad_added(ശൂന്യം *data, ഘടന zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ഘടന zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

സ്ഥിതം ശൂന്യം Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

ശൂന്യം Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

സ്ഥിതം ശൂന്യം Wayland_remove_all_pens_callback(SDL_PenID instance_id, ശൂന്യം *handle, ശൂന്യം *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

സ്ഥിതം ശൂന്യം Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    എങ്കിൽ (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } അല്ലെങ്കിൽ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ശൂന്യ);
    }

    എങ്കിൽ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ശൂന്യ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

ശൂന്യം Wayland_DisplayCreateSeat(SDL_VideoData *display, ഘടന wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, വലുപ്പം(SDL_WaylandSeat));
    എങ്കിൽ (!seat) {
        തിരികെ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_തിരുകുക(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_നിവേശം(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    എങ്കിൽ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ശൂന്യം Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        എങ്കിൽ (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        എങ്കിൽ (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = ശൂന്യ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            എങ്കിൽ (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            എങ്കിൽ (tool->focus == window) {
                tool->focus = ശൂന്യ;
                Wayland_TabletToolUpdateCursor(tool);
                എങ്കിൽ (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            എങ്കിൽ (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                എങ്കിൽ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

ശൂന്യം Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    എങ്കിൽ (!seat) {
        തിരികെ;
    }

    SDL_free(seat->name);

    എങ്കിൽ (seat->data_device) {
        എങ്കിൽ (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        എങ്കിൽ (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        എങ്കിൽ (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            എങ്കിൽ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        എങ്കിൽ (seat->data_device->data_device) {
            എങ്കിൽ (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } അല്ലെങ്കിൽ {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    എങ്കിൽ (seat->primary_selection_device) {
        എങ്കിൽ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        എങ്കിൽ (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        എങ്കിൽ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    എങ്കിൽ (seat->text_നിവേശം.zwp_text_നിവേശം) {
        zwp_text_നിവേശം_v3_destroy(seat->text_നിവേശം.zwp_text_നിവേശം);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    എങ്കിൽ (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } അല്ലെങ്കിൽ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

സ്ഥിതം ശൂന്യം Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    എങ്കിൽ (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        എങ്കിൽ (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            എങ്കിൽ (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                എങ്കിൽ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } അല്ലെങ്കിൽ {
                    relative_focus = seat->pointer.focus->keyboard_focus_എണ്ണം != 0;
                }
            } അല്ലെങ്കിൽ {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        എങ്കിൽ (relative_focus) {
            എങ്കിൽ (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = ശൂന്യ;
        }
    }
}

സ്ഥിതം ശൂന്യം Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    എങ്കിൽ (display->താക്കോൽ_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        എങ്കിൽ (seat->keyboard.താക്കോൽ_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.താക്കോൽ_inhibitor);
            seat->keyboard.താക്കോൽ_inhibitor = ശൂന്യ;
        }

        എങ്കിൽ (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            എങ്കിൽ (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                എങ്കിൽ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.താക്കോൽ_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->താക്കോൽ_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

ശൂന്യം Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    എങ്കിൽ (display->pointer_constraints) {
        എങ്കിൽ (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = ശൂന്യ;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        എങ്കിൽ (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            എങ്കിൽ (seat->pointer.relative_pointer) {
                എങ്കിൽ (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    എങ്കിൽ (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = ശൂന്യ;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, ശൂന്യ,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                തിരികെ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            എങ്കിൽ (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ശൂന്യ;
            }

            SDL_WindowData *w = seat->pointer.focus;
            എങ്കിൽ (!w) {
                തിരികെ;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            എങ്കിൽ (!(window->flags & SDL_WINDOW_നിവേശം_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                തിരികെ;
            }

            ഘടന wl_region *confine_rect = ശൂന്യ;
            എങ്കിൽ (!SDL_RectEmpty(&window->mouse_rect)) {
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
                എങ്കിൽ (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    പൂർണ്ണസംഖ്യ closest_x = seat->pointer.last_motion.x;
                    പൂർണ്ണസംഖ്യ closest_y = seat->pointer.last_motion.y;

                    എങ്കിൽ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } അല്ലെങ്കിൽ എങ്കിൽ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    എങ്കിൽ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } അല്ലെങ്കിൽ എങ്കിൽ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            എങ്കിൽ (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                എങ്കിൽ (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } അല്ലെങ്കിൽ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                ശൂന്യ,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                എങ്കിൽ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

ശൂന്യം Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        എങ്കിൽ (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

ശൂന്യം Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        എങ്കിൽ (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

ശൂന്യം Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    എങ്കിൽ (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
