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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_scancode_tables_c.h"
#अन्तर्भाव "../../events/SDL_keysym_to_keycode_c.h"
#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylandwindow.h"
#अन्तर्भाव "SDL_waylandmouse.h"
#अन्तर्भाव "SDL_waylandclipboard.h"
#अन्तर्भाव "SDL_waylandkeyboard.h"

#अन्तर्भाव "pointer-constraints-unstable-v1-client-protocol.h"
#अन्तर्भाव "relative-pointer-unstable-v1-client-protocol.h"
#अन्तर्भाव "xdg-shell-client-protocol.h"
#अन्तर्भाव "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#अन्तर्भाव "text-input-unstable-v3-client-protocol.h"
#अन्तर्भाव "tablet-v2-client-protocol.h"
#अन्तर्भाव "primary-selection-unstable-v1-client-protocol.h"
#अन्तर्भाव "input-timestamps-unstable-v1-client-protocol.h"
#अन्तर्भाव "pointer-gestures-unstable-v1-client-protocol.h"
#अन्तर्भाव "cursor-shape-v1-client-protocol.h"
#अन्तर्भाव "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_निवेश_LINUXEV
#अन्तर्भाव <linux/input.h>
#अन्यथा
#define BTN_बायाँ    (0x110)
#define BTN_दायाँ   (0x111)
#define BTN_मध्य  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#अन्तर्भाव "../../events/SDL_keysym_to_scancode_c.h"
#अन्तर्भाव "../../events/imKStoUCS.h"
#अन्तर्भाव <errno.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <xkbcommon/xkbcommon-compose.h>
#अन्तर्भाव <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी (WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला * 15U)

// Scoped function declarations
स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

प्रकारनिर्देश संरचना
{
    Uint32 कुंजी;
    SDL_Scancode scancode;
} Wayland_Reserved_कुंजी;

प्रकारनिर्देश संरचना
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    संरचना wl_surface *surface;

    संरचना wl_list link;
} SDL_WaylandTouchPoint;

स्थिर शून्य Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, संरचना wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(परिमाण(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_जोड़ो(&seat->touch.points, &tp->link);
}

स्थिर शून्य Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    यदि (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        यदि (window_data) {
            ध्रुव भिन्न x = (भिन्न)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ध्रुव भिन्न y = (भिन्न)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_गिनती;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            यदि (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_गिनती &&
                !window_data->pointer_focus_गिनती && !window_data->active_touch_गिनती) {
                SDL_SetMouseFocus(रिक्त);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

स्थिर शून्य Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, संरचना wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        यदि (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            यदि (surface) {
                *surface = tp->surface;
            }
            भङ्ग;
        }
    }
}

स्थिर शून्य Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, संरचना wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        यदि (tp->id == id) {
            यदि (fx) {
                *fx = tp->fx;
            }
            यदि (fy) {
                *fy = tp->fy;
            }
            यदि (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            भङ्ग;
        }
    }
}

स्थिर शून्य Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (पूर्णाङ्क)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (पूर्णाङ्क)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (पूर्णाङ्क)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (पूर्णाङ्क)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

स्थिर Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    स्थिर Uint64 timestamp_offset = 0;
    ध्रुव Uint64 now = SDL_GetTicksNS();

    यदि (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    यदि (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    प्रत्यागम nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
स्थिर Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 timestamp_offset = 0;
    स्थिर Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    यदि (wl_timestamp_ms >= last) {
        यदि (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } अन्यथा {
            last = wl_timestamp_ms;
        }
    } अन्यथा {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        यदि (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    प्रत्यागम timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

स्थिर Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ध्रुव Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    प्रत्यागम Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ध्रुव Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    प्रत्यागम Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ध्रुव Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    प्रत्यागम Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर शून्य निवेश_timestamp_listener(शून्य *data, संरचना zwp_निवेश_timestamps_v1 *zwp_निवेश_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

स्थिर ध्रुव संरचना zwp_निवेश_timestamps_v1_listener timestamp_listener = {
    निवेश_timestamp_listener
};

स्थिर शून्य Wayland_Seat_Register_निवेश_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    यदि (seat->display->निवेश_timestamps_manager) {
        यदि (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_निवेश_timestamps_manager_v1_get_keyboard_timestamps(seat->display->निवेश_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_निवेश_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        यदि (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_निवेश_timestamps_manager_v1_get_pointer_timestamps(seat->display->निवेश_timestamps_manager, seat->pointer.wl_pointer);
            zwp_निवेश_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        यदि (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_निवेश_timestamps_manager_v1_get_touch_timestamps(seat->display->निवेश_timestamps_manager, seat->touch.wl_touch);
            zwp_निवेश_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

शून्य Wayland_Display_Init_निवेश_Timestamp_Manager(SDL_VideoData *display)
{
    यदि (display->निवेश_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_निवेश_Timestamp_Listeners(seat);
        }
    }
}

स्थिर शून्य handle_pinch_begin(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, संरचना wl_surface *surface, uint32_t fingers)
{
    यदि (!surface) {
        प्रत्यागम;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    यदि (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_update(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    यदि (seat->pointer.gesture_focus) {
        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ध्रुव भिन्न s = (भिन्न)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_end(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    यदि (seat->pointer.gesture_focus) {
        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = रिक्त;
    }
}

स्थिर ध्रुव संरचना zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

स्थिर शून्य Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    यदि (seat->display->zwp_pointer_gestures) {
        यदि (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

शून्य Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

स्थिर शून्य Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    यदि (seat->display->cursor_shape_manager) {
        यदि (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            यदि (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

शून्य Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

स्थिर शून्य Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ध्रुव bool send_event = !seat->display->initializing;

    यदि (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
स्थिर शून्य keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    यावत् (elapsed >= repeat_info->next_repeat_ns) {
        यदि (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ध्रुव Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->कुंजी, repeat_info->scancode, true);
        }
        यदि (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

स्थिर शून्य keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t कुंजी, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ध्रुव वर्ण *text)
{
    यदि (!repeat_info->repeat_rate) {
        प्रत्यागम;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->कुंजी = कुंजी;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    यदि (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } अन्यथा {
        repeat_info->text[0] = '\0';
    }
}

स्थिर शून्य sync_done_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener sync_listener = {
    sync_done_handler
};

शून्य Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    संरचना wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, रिक्त);
    WAYLAND_wl_display_flush(d->display);
}

पूर्णाङ्क Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ध्रुव पूर्णाङ्क display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णाङ्क ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    यदि (!d->text_निवेश_manager && keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        यदि (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        यदि (seat->keyboard.repeat.कुंजी) {
            ध्रुव Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ध्रुव Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            यदि (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    यदि (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        यदि (timeoutNS > 0) {
            ध्रुव Uint64 now = SDL_GetTicksNS();
            ध्रुव Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        यदि (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            यदि (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        यदि (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            प्रत्यागम errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        यदि (timeoutNS > 0) {
            ध्रुव Uint64 now = SDL_GetTicksNS();
            ध्रुव Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        यदि (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            यदि (ret == 0) {
                प्रत्यागम poll_alarm_set ? 1 : 0;
            } अन्यथा {
                // Pump events on an interrupt or broken pipe to handle the error.
                प्रत्यागम errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        यदि (ret == -1) {
            प्रत्यागम ret;
        }
    }

    // Signal to the caller that there might be an event available.
    प्रत्यागम 1;
}

शून्य Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ध्रुव पूर्णाङ्क display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णाङ्क ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    यदि (!d->text_निवेश_manager && keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    यदि (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    यदि (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        यदि (ret < 0) {
            गच्छ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    यदि (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        यदि (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            यदि (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        यदि (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            गच्छ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        यदि (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            यदि (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } अन्यथा {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } अन्यथा {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    यदि (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            यदि (seat->keyboard.repeat.कुंजी) {
                Wayland_SeatSetKeymap(seat);

                ध्रुव Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    यदि (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

स्थिर शून्य pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : रिक्त;

    यदि (window_data) {
        द्विगुण sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        द्विगुण sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        यदि (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (द्विगुण)window_data->mask.offset_x;
            sy += (द्विगुण)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        यदि (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (भिन्न)sx, (भिन्न)sy);
        } अन्यथा {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (भिन्न)sx, (भिन्न)sy);
        }

        seat->pointer.last_motion.x = (पूर्णाङ्क)SDL_floor(sx);
        seat->pointer.last_motion.y = (पूर्णाङ्क)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        यदि (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        यदि (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            विकल्प (rc) {
            पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
                यदि ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_बायाँ;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_शीर्ष:
                यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_NORMAL;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
                यदि ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_दायाँ;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_दायाँ:
                यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                यदि ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_दायाँ;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOM:
                यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
                यदि ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_बायाँ;
                } अन्यथा यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_बायाँ:
                यदि (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }

            यदि (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

स्थिर शून्य pointer_handle_motion(शून्य *data, संरचना wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    यदि (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        यदि (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } अन्यथा {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

स्थिर शून्य pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    यदि (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        प्रत्यागम;
    }

    यदि (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        प्रत्यागम;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_गिनती;
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

स्थिर शून्य pointer_handle_enter(शून्य *data, संरचना wl_pointer *pointer,
                                 uint32_t serial, संरचना wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    यदि (!surface) {
        // Enter event for a destroyed surface.
        प्रत्यागम;
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

    यदि (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

स्थिर शून्य pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    यदि (window) {
        यदि (seat->pointer.focus) {
            यदि (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = रिक्त;
                seat->pointer.focus_surface = रिक्त;
                प्रति (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    यदि (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ध्रुव bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                यदि (!--window->pointer_focus_गिनती && had_focus && !window->active_touch_गिनती) {
                    SDL_SetMouseFocus(रिक्त);
                }

                यदि (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } अन्यथा यदि (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

स्थिर शून्य pointer_handle_leave(शून्य *data, संरचना wl_pointer *pointer,
                                 uint32_t serial, संरचना wl_surface *surface)
{
    यदि (!surface) {
        // Leave event for a destroyed surface.
        प्रत्यागम;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    यदि (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

स्थिर bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    यदि (seat->pointer.locked_pointer) {
        प्रत्यागम false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    यदि (window->hit_test) {
        स्थिर ध्रुव uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_बायाँ, XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष,
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_दायाँ, XDG_TOPLEVEL_RESIZE_EDGE_दायाँ,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_दायाँ, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_बायाँ, XDG_TOPLEVEL_RESIZE_EDGE_बायाँ
        };

#ifdef HAVE_LIBDECOR_H
        स्थिर ध्रुव uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_शीर्ष_बायाँ, LIBDECOR_RESIZE_EDGE_शीर्ष,
            LIBDECOR_RESIZE_EDGE_शीर्ष_दायाँ, LIBDECOR_RESIZE_EDGE_दायाँ,
            LIBDECOR_RESIZE_EDGE_BOTTOM_दायाँ, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_बायाँ, LIBDECOR_RESIZE_EDGE_बायाँ
        };
#endif

        विकल्प (window_data->hit_test_result) {
        पक्ष SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            यदि (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                यदि (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } अन्यथा
#endif
                यदि (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                यदि (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            प्रत्यागम true;

        पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
        पक्ष SDL_HITTEST_RESIZE_शीर्ष:
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
        पक्ष SDL_HITTEST_RESIZE_दायाँ:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        पक्ष SDL_HITTEST_RESIZE_BOTTOM:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
        पक्ष SDL_HITTEST_RESIZE_बायाँ:
#ifdef HAVE_LIBDECOR_H
            यदि (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                यदि (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } अन्यथा
#endif
                यदि (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                यदि (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            प्रत्यागम true;

        स्वभाव:
            प्रत्यागम false;
        }
    }

    प्रत्यागम false;
}

स्थिर शून्य pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    यदि (window) {
        bool ignore_click = false;

        यदि (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            यदि (sdl_button == SDL_BUTTON_बायाँ && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                प्रत्यागम; // don't pass this event on to app.
            }
        } अन्यथा {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        यदि (window->last_focus_event_time_ns) {
            यदि (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        यदि (!seat->pointer.relative_pointer) {
            यदि (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } अन्यथा {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                यदि (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        यदि (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

स्थिर शून्य pointer_handle_button(शून्य *data, संरचना wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    विकल्प (button) {
    पक्ष BTN_बायाँ:
        sdl_button = SDL_BUTTON_बायाँ;
        भङ्ग;
    पक्ष BTN_मध्य:
        sdl_button = SDL_BUTTON_मध्य;
        भङ्ग;
    पक्ष BTN_दायाँ:
        sdl_button = SDL_BUTTON_दायाँ;
        भङ्ग;
    स्वभाव:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        भङ्ग;
    }

    यदि (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    यदि (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        यदि (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } अन्यथा {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } अन्यथा {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

स्थिर शून्य pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t मूल्य)
{
    SDL_WindowData *window = seat->pointer.focus;
    ध्रुव गणना wl_pointer_axis a = axis;

    यदि (seat->pointer.focus) {
        भिन्न x, y;

        विकल्प (a) {
        पक्ष WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (भिन्न)wl_fixed_to_double(मूल्य);
            भङ्ग;
        पक्ष WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (भिन्न)wl_fixed_to_double(मूल्य);
            y = 0;
            भङ्ग;
        स्वभाव:
            प्रत्यागम;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

स्थिर शून्य pointer_handle_axis_common(SDL_WaylandSeat *seat, गणना SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t मूल्य)
{
    ध्रुव गणना wl_pointer_axis a = axis;

    यदि (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        विकल्प (a) {
        पक्ष WL_POINTER_AXIS_VERTICAL_SCROLL:
            विकल्प (type) {
            पक्ष SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                यदि (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (भिन्न)wl_fixed_to_double(मूल्य);
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                यदि (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (भिन्न)wl_fixed_to_double(मूल्य);
                }
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                यदि (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (भिन्न)wl_fixed_to_double(मूल्य);
                }
                भङ्ग;
            }
            भङ्ग;
        पक्ष WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            विकल्प (type) {
            पक्ष SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                यदि (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (भिन्न)wl_fixed_to_double(मूल्य);
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                यदि (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (भिन्न)wl_fixed_to_double(मूल्य);
                }
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                यदि (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (भिन्न)wl_fixed_to_double(मूल्य);
                }
                भङ्ग;
            }
            भङ्ग;
        }
    }
}

स्थिर शून्य pointer_handle_axis(शून्य *data, संरचना wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t मूल्य)
{
    SDL_WaylandSeat *seat = data;
    ध्रुव Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    यदि (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, मूल्य);
    } अन्यथा {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, मूल्य);
    }
}

स्थिर शून्य pointer_handle_axis_relative_direction(शून्य *data, संरचना wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    विकल्प (axis_relative_direction) {
    पक्ष WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        भङ्ग;
    पक्ष WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        भङ्ग;
    }
}

स्थिर शून्य pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    यदि (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        द्विगुण dx;
        द्विगुण dy;
        यदि (mouse->निवेश_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } अन्यथा {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (भिन्न)dx, (भिन्न)dy);
    }
}

स्थिर शून्य pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    भिन्न x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    विकल्प (seat->pointer.pending_frame.axis.x_axis_type) {
    पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        भङ्ग;
    पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        भङ्ग;
    पक्ष SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        भङ्ग;
    स्वभाव:
        x = 0.0f;
        भङ्ग;
    }

    विकल्प (seat->pointer.pending_frame.axis.y_axis_type) {
    पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        भङ्ग;
    पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        भङ्ग;
    पक्ष SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        भङ्ग;
    स्वभाव:
        y = 0.0f;
        भङ्ग;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

स्थिर शून्य pointer_handle_frame(शून्य *data, संरचना wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    यदि (seat->pointer.pending_frame.enter_surface) {
        यदि (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            यदि (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = रिक्त;
                seat->pointer.pending_frame.leave_surface = रिक्त;
            } अन्यथा {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = रिक्त;
            }
        }

        यदि (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    यदि (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    यदि (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    प्रति (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ध्रुव Uint32 mask = SDL_BUTTON_MASK(i);
        यदि (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        यदि (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    यदि (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    यदि (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

स्थिर शून्य pointer_handle_axis_source(शून्य *data, संरचना wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

स्थिर शून्य pointer_handle_axis_stop(शून्य *data, संरचना wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

स्थिर शून्य pointer_handle_axis_discrete(शून्य *data, संरचना wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

स्थिर शून्य pointer_handle_axis_value120(शून्य *data, संरचना wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

स्थिर शून्य pointer_handle_warp(शून्य *data, संरचना wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

स्थिर ध्रुव संरचना wl_pointer_listener pointer_listener = {
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

स्थिर शून्य relative_pointer_handle_relative_motion(शून्य *data,
                                                    संरचना zwp_relative_pointer_v1 *pointer,
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

    यदि (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } अन्यथा {
        pointer_dispatch_relative_motion(seat);
    }
}

स्थिर ध्रुव संरचना zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

स्थिर शून्य locked_pointer_locked(शून्य *data, संरचना zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

स्थिर शून्य locked_pointer_unlocked(शून्य *data, संरचना zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

स्थिर ध्रुव संरचना zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

स्थिर शून्य confined_pointer_confined(शून्य *data, संरचना zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

स्थिर शून्य confined_pointer_unconfined(शून्य *data, संरचना zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

स्थिर ध्रुव संरचना zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

स्थिर शून्य touch_handler_down(शून्य *data, संरचना wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, संरचना wl_surface *surface,
                               पूर्णाङ्क id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    यदि (!surface) {
        प्रत्यागम;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    यदि (window_data && window_data->surface == surface) {
        भिन्न x, y;

        यदि (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } अन्यथा {
            x = (भिन्न)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        यदि (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } अन्यथा {
            y = (भिन्न)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_गिनती;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

स्थिर शून्य touch_handler_up(शून्य *data, संरचना wl_touch *touch, uint32_t serial, uint32_t timestamp, पूर्णाङ्क id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    यदि (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        यदि (window_data && window_data->surface == surface) {
            ध्रुव भिन्न x = (भिन्न)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ध्रुव भिन्न y = (भिन्न)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_गिनती;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            यदि (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_गिनती &&
                !window_data->pointer_focus_गिनती && !window_data->active_touch_गिनती) {
                SDL_SetMouseFocus(रिक्त);
            }
        }
    }
}

स्थिर शून्य touch_handler_motion(शून्य *data, संरचना wl_touch *touch, uint32_t timestamp, पूर्णाङ्क id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    यदि (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        यदि (window_data && window_data->surface == surface) {
            ध्रुव भिन्न x = (भिन्न)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ध्रुव भिन्न y = (भिन्न)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

स्थिर शून्य touch_handler_frame(शून्य *data, संरचना wl_touch *touch)
{
}

स्थिर शून्य touch_handler_cancel(शून्य *data, संरचना wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

स्थिर शून्य touch_handler_shape(शून्य *data, संरचना wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

स्थिर शून्य touch_handler_orientation(शून्य *data, संरचना wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

स्थिर ध्रुव संरचना wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#यदि !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
स्थिर size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t कुंजी, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    यदि (!masks_out || !masks_size) {
        प्रत्यागम 0;
    }

    // Level 0 is always unmodified, so early out.
    यदि (level == 0) {
        *masks_out = 0;
        प्रत्यागम 1;
    }

    size_t mask_idx = 0;
    ध्रुव xkb_mod_mask_t keymod_masks[] = {
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
    ध्रुव xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    ध्रुव xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    प्रति (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        यदि (WAYLAND_xkb_state_कुंजी_get_level(seat->keyboard.xkb.state, कुंजी, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            यदि (++mask_idx == masks_size) {
                भङ्ग;
            }
        }
    }

    प्रत्यागम mask_idx;
}
#endif

स्थिर शून्य Wayland_KeymapIterator(संरचना xkb_keymap *keymap, xkb_keycode_t कुंजी, शून्य *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ध्रुव xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ध्रुव xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    यदि (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, कुंजी - 8);
    }

    प्रति (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.अंक_layouts; ++layout) {
        ध्रुव xkb_level_index_t अंक_levels = WAYLAND_xkb_keymap_अंक_levels_for_कुंजी(seat->keyboard.xkb.keymap, कुंजी, layout);
        प्रति (xkb_level_index_t level = 0; level < अंक_levels; ++level) {
            यदि (WAYLAND_xkb_keymap_कुंजी_get_syms_by_level(seat->keyboard.xkb.keymap, कुंजी, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                यदि (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_कुंजी_Sym(syms[0], कुंजी);
                    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                        अनुवर्त;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#यदि SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ध्रुव size_t अंक_masks = WAYLAND_xkb_keymap_कुंजी_get_mods_for_level(seat->keyboard.xkb.keymap, कुंजी, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#अन्यथा
                ध्रुव size_t अंक_masks = xkb_legacy_get_mods_for_level(seat, कुंजी, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                प्रति (size_t mask = 0; mask < अंक_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    यदि ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        अनुवर्त;
                    }

                    ध्रुव SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_कुंजी_Code_From_कुंजी_Sym(syms[0], कुंजी, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    यदि (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        यदि (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_कुंजी *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, परिमाण(Wayland_Reserved_कुंजी));
                        यदि (res) {
                            res->scancode = scancode;
                            res->कुंजी = कुंजी - 8;
                        }
                    }

                    यदि (!keycode) {
                        विकल्प (scancode) {
                        पक्ष SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            भङ्ग;
                        पक्ष SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            भङ्ग;
                        पक्ष SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            भङ्ग;
                        पक्ष SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            भङ्ग;
                        स्वभाव:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            भङ्ग;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

स्थिर शून्य keyboard_handle_keymap(शून्य *data, संरचना wl_keyboard *keyboard,
                                   uint32_t format, पूर्णाङ्क fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    वर्ण *map_str;

    यदि (!data) {
        close(fd);
        प्रत्यागम;
    }

    यदि (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        प्रत्यागम;
    }

    map_str = mmap(रिक्त, size, PROT_READ, MAP_PRIVATE, fd, 0);
    यदि (map_str == MAP_FAILED) {
        close(fd);
        प्रत्यागम;
    }

    यदि (seat->keyboard.xkb.keymap != रिक्त) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = रिक्त;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    यदि (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        प्रत्यागम;
    }

    // Clear the old layouts.
    प्रति (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = रिक्त;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.अंक_layouts = 0;

#यदि SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.अंक_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_अंक);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#अन्यथा
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.अंक_mask = 1 << GET_MOD_INDEX(अंक_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    यदि (seat->keyboard.xkb.state != रिक्त) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = रिक्त;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    यदि (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = रिक्त;
        प्रत्यागम;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == रिक्त;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.अंक_layouts = WAYLAND_xkb_keymap_अंक_layouts(seat->keyboard.xkb.keymap);
    यदि (seat->keyboard.xkb.अंक_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.अंक_layouts, परिमाण(SDL_Keymap *));
        यदि (!seat->keyboard.sdl_keymap) {
            प्रत्यागम;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        प्रति (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            यदि (!seat->keyboard.sdl_keymap[i]) {
                प्रति (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = रिक्त;
                प्रत्यागम;
            }
        }

        WAYLAND_xkb_keymap_कुंजी_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ध्रुव वर्ण *locale = SDL_getenv("LC_ALL");
    यदि (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        यदि (!locale) {
            locale = SDL_getenv("LANG");
            यदि (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    यदि (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        यदि (seat->keyboard.xkb.compose_table != रिक्त) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = रिक्त;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        यदि (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            यदि (seat->keyboard.xkb.compose_state != रिक्त) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = रिक्त;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            यदि (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = रिक्त;
            }
        }
    } अन्यथा यदि (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
स्थिर SDL_Scancode Wayland_Get_Scancode_For_कुंजी(SDL_WaylandSeat *seat, Uint32 कुंजी, ध्रुव xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    यदि (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, कुंजी);

        // No table entry? Check the reserved list.
        यदि (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_कुंजी *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                यदि (i->कुंजी == कुंजी) {
                    प्रत्यागम i->scancode;
                }
            }
        }
    } अन्यथा {
        ध्रुव xkb_keysym_t *keysym;
        यदि (WAYLAND_xkb_state_कुंजी_get_syms(seat->keyboard.xkb.state, कुंजी + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_कुंजी_Sym(keysym[0], कुंजी + 8);
            यदि (syms) {
                *syms = keysym;
            }
        }
    }

    प्रत्यागम scancode;
}

स्थिर शून्य Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool कुंजी_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    यदि (!कुंजी_pressed) {
        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } अन्यथा {
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
    ध्रुव xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    यदि (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.अंक_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_अंक;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_अंक;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

स्थिर शून्य Wayland_Handle_Modifier_कुंजियाँ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ध्रुव SDL_Keycode keycode = SDL_Get_कुंजी_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    विकल्प (keycode) {
    पक्ष SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        भङ्ग;
    पक्ष SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        भङ्ग;
    पक्ष SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        भङ्ग;
    पक्ष SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        भङ्ग;
    पक्ष SDLK_LALT:
        mod = SDL_KMOD_LALT;
        भङ्ग;
    पक्ष SDLK_RALT:
        mod = SDL_KMOD_RALT;
        भङ्ग;
    पक्ष SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        भङ्ग;
    पक्ष SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        भङ्ग;
    पक्ष SDLK_MODE:
        mod = SDL_KMOD_MODE;
        भङ्ग;
    पक्ष SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        भङ्ग;
    स्वभाव:
        प्रत्यागम;
    }

    यदि (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } अन्यथा {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

स्थिर शून्य keyboard_handle_enter(शून्य *data, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface,
                                  संरचना wl_array *कुंजियाँ)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *कुंजी;

    यदि (!surface) {
        // Enter event for a destroyed surface.
        प्रत्यागम;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    यदि (!window) {
        // Not a surface owned by SDL.
        प्रत्यागम;
    }

    ++window->keyboard_focus_गिनती;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_निवेश(seat);

#ifdef SDL_USE_IME
    यदि (!seat->text_निवेश.zwp_text_निवेश) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (कुंजी, कुंजियाँ) {
        ध्रुव SDL_Scancode scancode = Wayland_Get_Scancode_For_कुंजी(seat, *कुंजी, रिक्त);
        यदि (scancode != SDL_SCANCODE_UNKNOWN) {
            ध्रुव SDL_Keycode keycode = SDL_Get_कुंजी_From_Scancode(scancode, SDL_KMOD_NONE, false);

            विकल्प (keycode) {
            पक्ष SDLK_LSHIFT:
            पक्ष SDLK_RSHIFT:
            पक्ष SDLK_LCTRL:
            पक्ष SDLK_RCTRL:
            पक्ष SDLK_LALT:
            पक्ष SDLK_RALT:
            पक्ष SDLK_LGUI:
            पक्ष SDLK_RGUI:
            पक्ष SDLK_MODE:
            पक्ष SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_कुंजियाँ(seat, scancode, true);
                SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *कुंजी, scancode, true);
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }
        }
    }
}

स्थिर शून्य keyboard_handle_leave(शून्य *data, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    यदि (!surface) {
        // Leave event for a destroyed surface.
        प्रत्यागम;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    यदि (!window) {
        // Not a surface owned by SDL.
        प्रत्यागम;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.कुंजी = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    यावत् (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ध्रुव bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = रिक्त;
    --window->keyboard_focus_गिनती;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    यदि (!window->keyboard_focus_गिनती && had_focus) {
        SDL_SetKeyboardFocus(रिक्त);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_निवेश(seat);

#ifdef SDL_USE_IME
    यदि (!seat->text_निवेश.zwp_text_निवेश && !window->keyboard_focus_गिनती) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    यदि (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_गिनती && !window->active_touch_गिनती) {
        SDL_SetMouseFocus(रिक्त);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, रिक्त);
}

स्थिर bool keyboard_निवेश_get_text(वर्ण text[8], ध्रुव SDL_WaylandSeat *seat, uint32_t कुंजी, bool down, bool *handled_by_ime)
{
    ध्रुव xkb_keysym_t *syms;
    xkb_keysym_t sym;

    यदि (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        प्रत्यागम false;
    }

    // TODO: Can this happen?
    यदि (WAYLAND_xkb_state_कुंजी_get_syms(seat->keyboard.xkb.state, कुंजी + 8, &syms) != 1) {
        प्रत्यागम false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    यदि (SDL_IME_Process_कुंजी_Event(sym, कुंजी + 8, down)) {
        यदि (handled_by_ime) {
            *handled_by_ime = true;
        }
        प्रत्यागम true;
    }
#endif

    यदि (!down) {
        प्रत्यागम false;
    }

    यदि (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        विकल्प (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        पक्ष XKB_COMPOSE_COMPOSING:
            यदि (handled_by_ime) {
                *handled_by_ime = true;
            }
            प्रत्यागम true;
        पक्ष XKB_COMPOSE_CANCELLED:
        स्वभाव:
            sym = XKB_कुंजी_No_प्रतीक;
            भङ्ग;
        पक्ष XKB_COMPOSE_NOTHING:
            भङ्ग;
        पक्ष XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            भङ्ग;
        }
    }

    प्रत्यागम WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

स्थिर शून्य keyboard_handle_कुंजी(शून्य *data, संरचना wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t कुंजी,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    गणना wl_keyboard_कुंजी_state state = state_w;
    वर्ण text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ध्रुव Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    यदि (state == WL_KEYBOARD_कुंजी_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        यदि (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_कुंजी_repeats(seat->keyboard.xkb.keymap, कुंजी + 8)) {
            प्रत्यागम;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_कुंजी_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    यदि (state == WL_KEYBOARD_कुंजी_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        यदि (keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
            has_text = keyboard_निवेश_get_text(text, seat, कुंजी, true, &handled_by_ime);
        }
    } अन्यथा {
        यदि (कुंजी == seat->keyboard.repeat.कुंजी) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ध्रुव Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.कुंजी = 0;
        }
        keyboard_निवेश_get_text(text, seat, कुंजी, false, &handled_by_ime);
    }

    ध्रुव xkb_keysym_t *syms = रिक्त;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_कुंजी(seat, कुंजी, &syms);
    Wayland_Handle_Modifier_कुंजियाँ(seat, scancode, state == WL_KEYBOARD_कुंजी_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    यदि (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ध्रुव SDL_Keycode keycode = (SDL_Keycode)SDL_कुंजी_Sym_To_Ucs4(syms[0]);
        यदि (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            यदि (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, कुंजी, scancode, state == WL_KEYBOARD_कुंजी_STATE_PRESSED);

    यदि (state == WL_KEYBOARD_कुंजी_STATE_PRESSED) {
        यदि (handled_by_ime) {
            has_text = false;
        }
        यदि (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        यदि (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_कुंजी_repeats(seat->keyboard.xkb.keymap, कुंजी + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, कुंजी, time, timestamp_ns, scancode, has_text ? text : रिक्त);
        }
    }
}

स्थिर शून्य keyboard_handle_modifiers(शून्य *data, संरचना wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    ध्रुव uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    यदि (!seat->keyboard.xkb.state) {
        प्रत्यागम;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    यदि (seat->keyboard.repeat.कुंजी) {
        वर्ण text[8];

        यदि (keyboard_निवेश_get_text(text, seat, seat->keyboard.repeat.कुंजी, true, रिक्त)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    यदि (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        यदि (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

स्थिर शून्य keyboard_handle_repeat_info(शून्य *data, संरचना wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    यदि (!rate) {
        seat->keyboard.repeat.कुंजी = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

स्थिर ध्रुव संरचना wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_कुंजी,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

स्थिर शून्य Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    यदि (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    यदि (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = रिक्त;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    यदि (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    यदि (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    यदि (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    यदि (seat->pointer.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    यदि (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    यदि (seat->pointer.wl_pointer) {
        यदि (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } अन्यथा {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

स्थिर शून्य Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    यदि (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    यदि (seat->keyboard.sdl_keymap) {
        यदि (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        प्रति (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = रिक्त;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    यदि (seat->keyboard.कुंजी_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुंजी_inhibitor);
    }

    यदि (seat->keyboard.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    यदि (seat->keyboard.wl_keyboard) {
        यदि (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } अन्यथा {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    यदि (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    यदि (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    यदि (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    यदि (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

स्थिर शून्य Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    यदि (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    यदि (seat->touch.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->touch.timestamps);
    }

    यदि (seat->touch.wl_touch) {
        यदि (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } अन्यथा {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

स्थिर शून्य seat_handle_capabilities(शून्य *data, संरचना wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    वर्ण name_fmt[256];

    यदि ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    यदि ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    यदि ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_निवेश_Timestamp_Listeners(seat);
}

स्थिर शून्य seat_handle_name(शून्य *data, संरचना wl_seat *wl_seat, ध्रुव वर्ण *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    यदि (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

स्थिर ध्रुव संरचना wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

स्थिर शून्य data_offer_handle_offer(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                    ध्रुव वर्ण *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

स्थिर शून्य data_offer_handle_source_actions(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

स्थिर शून्य data_offer_handle_actions(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

स्थिर ध्रुव संरचना wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

स्थिर शून्य primary_selection_offer_handle_offer(शून्य *data, संरचना zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ध्रुव वर्ण *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

स्थिर ध्रुव संरचना zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

स्थिर शून्य data_device_handle_data_offer(शून्य *data, संरचना wl_data_device *wl_data_device,
                                          संरचना wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, परिमाण(*data_offer));
    यदि (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
    }
}

स्थिर शून्य data_device_handle_enter(शून्य *data, संरचना wl_data_device *wl_data_device,
                                     uint32_t serial, संरचना wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, संरचना wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : रिक्त;
    data_device->has_mime_file = false;
    data_device->text_mime_type = रिक्त;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    यदि (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    यदि (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        यदि (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        यदि (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        यदि (!data_device->has_mime_file) {
            size_t mime_गिनती = 0;
            ध्रुव वर्ण *ध्रुव *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_गिनती);
            प्रति (size_t i = 0; i < mime_गिनती; ++i) {
                यदि (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    भङ्ग;
                }
            }
        }

        यदि (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            यदि (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            द्विगुण dx = wl_fixed_to_double(x);
            द्विगुण dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            यदि (surface == window->mask.surface) {
                dx += (द्विगुण)window->mask.offset_x;
                dy += (द्विगुण)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (भिन्न)dx, (भिन्न)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } अन्यथा {
            // Decline the offer.
            wl_data_offer_accept(id, serial, रिक्त);
            यदि (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } अन्यथा {
        data_device->dnd_window = रिक्त;
        data_device->dnd_surface = रिक्त;

        // Decline the offer.
        यदि (id) {
            wl_data_offer_accept(id, serial, रिक्त);
            यदि (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

स्थिर शून्य data_device_handle_leave(शून्य *data, संरचना wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    यदि (data_device->drag_offer) {
        यदि (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } अन्यथा {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = रिक्त;
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = रिक्त;
}

स्थिर शून्य data_device_handle_motion(शून्य *data, संरचना wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    यदि (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        द्विगुण dx = wl_fixed_to_double(x);
        द्विगुण dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        यदि (data_device->dnd_surface == window_data->mask.surface) {
            dx += (द्विगुण)window_data->mask.offset_x;
            dy += (द्विगुण)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (भिन्न)dx, (भिन्न)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

स्थिर शून्य drop_cleanup_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

स्थिर ध्रुव संरचना wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

स्थिर शून्य drop_dispatch_handler(शून्य *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    यदि (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        यदि (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            शून्य *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            यदि (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                यदि (dbus) {
                    पूर्णाङ्क path_गिनती = 0;
                    वर्ण **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_गिनती);
                    // If dropped files contain a directory the list is empty
                    यदि (paths && path_गिनती > 0) {
                        प्रति (पूर्णाङ्क i = 0; i < path_गिनती; i++) {
                            SDL_SendDropFile(drop->dnd_window, रिक्त, paths[i]);
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
        यदि (!drop_handled) {
            यदि (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                शून्य *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                यदि (buffer) {
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r((वर्ण *)buffer, "\r\n", &saveptr);
                    यावत् (token) {
                        यदि (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, रिक्त, token);
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } अन्यथा यदि (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                शून्य *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                यदि (buffer) {
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r((वर्ण *)buffer, "\r\n", &saveptr);
                    यावत् (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        यदि (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = रिक्त;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

स्थिर शून्य data_device_handle_drop(शून्य *data, संरचना wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    यदि (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, परिमाण(Wayland_DropData));
        यदि (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_जोड़ो(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } अन्यथा {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = रिक्त;
}

स्थिर शून्य data_device_handle_selection(शून्य *data, संरचना wl_data_device *wl_data_device,
                                         संरचना wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = रिक्त;

    यदि (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

स्थिर ध्रुव संरचना wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

स्थिर शून्य primary_selection_device_handle_offer(शून्य *data, संरचना zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  संरचना zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, परिमाण(*primary_selection_offer));
    यदि (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर शून्य primary_selection_device_handle_selection(शून्य *data, संरचना zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      संरचना zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = रिक्त;

    यदि (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    यदि (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर ध्रुव संरचना zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

स्थिर शून्य text_निवेश_enter(शून्य *data,
                             संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_निवेश_leave(शून्य *data,
                             संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_निवेश_preedit_string(शून्य *data,
                                      संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                      ध्रुव वर्ण *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_निवेश.has_preedit = true;
    यदि (text) {
        पूर्णाङ्क cursor_begin_utf8 = cursor_begin >= 0 ? (पूर्णाङ्क)SDL_utf8strnlen(text, cursor_begin) : -1;
        पूर्णाङ्क cursor_end_utf8 = cursor_end >= 0 ? (पूर्णाङ्क)SDL_utf8strnlen(text, cursor_end) : -1;
        पूर्णाङ्क cursor_size_utf8;
        यदि (cursor_end_utf8 >= 0) {
            यदि (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } अन्यथा {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } अन्यथा {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } अन्यथा {
        SDL_SendEditingText("", 0, 0);
    }
}

स्थिर शून्य text_निवेश_commit_string(शून्य *data,
                                     संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                     ध्रुव वर्ण *text)
{
    SDL_SendKeyboardText(text);
}

स्थिर शून्य text_निवेश_delete_surrounding_text(शून्य *data,
                                               संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

स्थिर शून्य text_निवेश_done(शून्य *data,
                            संरचना zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    यदि (!seat->text_निवेश.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_निवेश.has_preedit = false;
}

स्थिर ध्रुव संरचना zwp_text_निवेश_v3_listener text_निवेश_listener = {
    text_निवेश_enter,
    text_निवेश_leave,
    text_निवेश_preedit_string,
    text_निवेश_commit_string,
    text_निवेश_delete_surrounding_text,
    text_निवेश_done
};

स्थिर शून्य Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    यदि (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        यदि (dbus) {
            ध्रुव वर्ण *id = dbus->bus_get_unique_name(dbus->session_conn);
            यदि (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    यदि (!data_device->id_str)
#endif
    {
        वर्ण id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, परिमाण(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

स्थिर शून्य Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    यदि (!seat->display->data_device_manager) {
        प्रत्यागम;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, परिमाण(*data_device));
    यदि (!data_device) {
        प्रत्यागम;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    यदि (!data_device->data_device) {
        SDL_free(data_device);
        प्रत्यागम;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

शून्य Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

स्थिर शून्य Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    यदि (!seat->display->primary_selection_device_manager) {
        प्रत्यागम;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, परिमाण(*primary_selection_device));
    यदि (!primary_selection_device) {
        प्रत्यागम;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    यदि (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } अन्यथा {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

शून्य Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

स्थिर शून्य Wayland_Seat_Create_Text_निवेश(SDL_WaylandSeat *seat)
{
    यदि (seat->display->text_निवेश_manager) {
        seat->text_निवेश.zwp_text_निवेश = zwp_text_निवेश_manager_v3_get_text_निवेश(seat->display->text_निवेश_manager, seat->wl_seat);

        यदि (seat->text_निवेश.zwp_text_निवेश) {
            zwp_text_निवेश_v3_set_user_data(seat->text_निवेश.zwp_text_निवेश, seat);
            zwp_text_निवेश_v3_add_listener(seat->text_निवेश.zwp_text_निवेश,
                                           &text_निवेश_listener, seat);
        }
    }
}

शून्य Wayland_Display_Init_Text_निवेश_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_निवेश(seat);
    }
}

// Pen/Tablet support...
स्थिर शून्य tablet_tool_handle_type(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    विकल्प (type) {
        #define CASE(typ) पक्ष ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; प्रत्यागम
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        स्वभाव: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

स्थिर शून्य tablet_tool_handle_hardware_serial(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

स्थिर शून्य tablet_tool_handle_hardware_id_wacom(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

स्थिर शून्य tablet_tool_handle_capability(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    विकल्प (capability) {
        #define CASE(wltyp,sdltyp) पक्ष ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; प्रत्यागम
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        स्वभाव: भङ्ग;  // unsupported here.
    }
}

स्थिर शून्य tablet_tool_handle_done(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    यदि (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
        sdltool->instance_id = SDL_AddPenDevice(0, रिक्त, window, &sdltool->info, sdltool, false);
    }
}

स्थिर शून्य tablet_tool_handle_removed(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    यदि (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

स्थिर शून्य tablet_tool_handle_proximity_in(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial, संरचना zwp_tablet_v2 *tablet, संरचना wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : रिक्त;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : रिक्त;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

स्थिर शून्य tablet_tool_handle_proximity_out(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

स्थिर शून्य tablet_tool_handle_down(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

स्थिर शून्य tablet_tool_handle_up(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

स्थिर शून्य tablet_tool_handle_motion(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    यदि (windowdata) {
        sdltool->frame.x = (भिन्न)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (भिन्न)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

स्थिर शून्य tablet_tool_handle_pressure(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((भिन्न) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    यदि (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

स्थिर शून्य tablet_tool_handle_distance(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((भिन्न) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    यदि (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

स्थिर शून्य tablet_tool_handle_tilt(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (भिन्न)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (भिन्न)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

स्थिर शून्य tablet_tool_handle_button(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    पूर्णाङ्क sdlbutton;

    विकल्प (button) {
    पक्ष BTN_STYLUS:
        sdlbutton = 1;
        भङ्ग;
    पक्ष BTN_STYLUS2:
        sdlbutton = 2;
        भङ्ग;
    पक्ष BTN_STYLUS3:
        sdlbutton = 3;
        भङ्ग;
    स्वभाव:
        प्रत्यागम;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

स्थिर शून्य tablet_tool_handle_rotation(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ध्रुव भिन्न rotation = (भिन्न)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

स्थिर शून्य tablet_tool_handle_slider(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

स्थिर शून्य tablet_tool_handle_wheel(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

स्थिर शून्य tablet_tool_handle_frame(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ध्रुव SDL_PenID instance_id = sdltool->instance_id;
    यदि (!instance_id) {
        प्रत्यागम;  // Not a pen we report on.
    }

    ध्रुव Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
    ध्रुव bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    यदि (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    यदि (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        यदि (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } अन्यथा {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } अन्यथा {
        यदि (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        यदि (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    प्रति (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_गिनती; i++) {
        यदि (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ध्रुव पूर्णाङ्क state = sdltool->frame.buttons[i];
        यदि (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    यदि (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = रिक्त;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

स्थिर ध्रुव संरचना zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


स्थिर शून्य tablet_seat_handle_tablet_added(शून्य *data, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

स्थिर शून्य tablet_seat_handle_tool_added(शून्य *data, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, परिमाण(*sdltool));

    यदि (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.अंक_buttons = -1;

        यदि (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_जोड़ो(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

स्थिर शून्य tablet_seat_handle_pad_added(शून्य *data, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

स्थिर ध्रुव संरचना zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

स्थिर शून्य Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

शून्य Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

स्थिर शून्य Wayland_remove_all_pens_callback(SDL_PenID instance_id, शून्य *handle, शून्य *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

स्थिर शून्य Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    यदि (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } अन्यथा {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, रिक्त);
    }

    यदि (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = रिक्त;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

शून्य Wayland_DisplayCreateSeat(SDL_VideoData *display, संरचना wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, परिमाण(SDL_WaylandSeat));
    यदि (!seat) {
        प्रत्यागम;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_जोड़ो(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_निवेश(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    यदि (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

शून्य Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        यदि (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        यदि (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = रिक्त;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            यदि (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            यदि (tool->focus == window) {
                tool->focus = रिक्त;
                Wayland_TabletToolUpdateCursor(tool);
                यदि (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            यदि (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                यदि (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

शून्य Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    यदि (!seat) {
        प्रत्यागम;
    }

    SDL_free(seat->name);

    यदि (seat->data_device) {
        यदि (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        यदि (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        यदि (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            यदि (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        यदि (seat->data_device->data_device) {
            यदि (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } अन्यथा {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    यदि (seat->primary_selection_device) {
        यदि (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        यदि (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        यदि (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    यदि (seat->text_निवेश.zwp_text_निवेश) {
        zwp_text_निवेश_v3_destroy(seat->text_निवेश.zwp_text_निवेश);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    यदि (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } अन्यथा {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

स्थिर शून्य Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    यदि (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        यदि (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            यदि (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                यदि (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } अन्यथा {
                    relative_focus = seat->pointer.focus->keyboard_focus_गिनती != 0;
                }
            } अन्यथा {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        यदि (relative_focus) {
            यदि (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } अन्यथा यदि (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = रिक्त;
        }
    }
}

स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    यदि (display->कुंजी_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        यदि (seat->keyboard.कुंजी_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुंजी_inhibitor);
            seat->keyboard.कुंजी_inhibitor = रिक्त;
        }

        यदि (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            यदि (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                यदि (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.कुंजी_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->कुंजी_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

शून्य Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    यदि (display->pointer_constraints) {
        यदि (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = रिक्त;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        यदि (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            यदि (seat->pointer.relative_pointer) {
                यदि (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    यदि (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = रिक्त;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, रिक्त,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                प्रत्यागम;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            यदि (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = रिक्त;
            }

            SDL_WindowData *w = seat->pointer.focus;
            यदि (!w) {
                प्रत्यागम;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            यदि (!(window->flags & SDL_WINDOW_निवेश_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                प्रत्यागम;
            }

            संरचना wl_region *confine_rect = रिक्त;
            यदि (!SDL_RectEmpty(&window->mouse_rect)) {
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
                यदि (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    पूर्णाङ्क closest_x = seat->pointer.last_motion.x;
                    पूर्णाङ्क closest_y = seat->pointer.last_motion.y;

                    यदि (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } अन्यथा यदि (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    यदि (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } अन्यथा यदि (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            यदि (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                यदि (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } अन्यथा {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                रिक्त,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                यदि (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

शून्य Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        यदि (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

शून्य Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        यदि (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

शून्य Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    यदि (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
