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
#ifdef SDL_आदान_LINUXEV
#अन्तर्भाव <linux/input.h>
#अन्यथा
#define BTN_डावा    (0x110)
#define BTN_उजवा   (0x111)
#define BTN_मधला  (0x112)
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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_खालचा  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_वरचा (WAYLAND_TIMER_ROLLOVER_INTERVAL_खालचा * 15U)

// Scoped function declarations
स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

प्रकारव्याख्या संरचना
{
    Uint32 किल्ली;
    SDL_Scancode scancode;
} Wayland_Reserved_किल्ली;

प्रकारव्याख्या संरचना
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    संरचना wl_surface *surface;

    संरचना wl_list link;
} SDL_WaylandTouchPoint;

स्थिर शून्य Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, संरचना wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(आकार(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_घाला(&seat->touch.points, &tp->link);
}

स्थिर शून्य Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    जर (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        जर (window_data) {
            स्थिरांक दशांश x = (दशांश)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            स्थिरांक दशांश y = (दशांश)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_मोजणी;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            जर (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_मोजणी &&
                !window_data->pointer_focus_मोजणी && !window_data->active_touch_मोजणी) {
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
        जर (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            जर (surface) {
                *surface = tp->surface;
            }
            थांबा;
        }
    }
}

स्थिर शून्य Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, संरचना wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        जर (tp->id == id) {
            जर (fx) {
                *fx = tp->fx;
            }
            जर (fy) {
                *fy = tp->fy;
            }
            जर (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            थांबा;
        }
    }
}

स्थिर शून्य Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (पूर्णांक)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (पूर्णांक)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (पूर्णांक)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (पूर्णांक)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

स्थिर Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    स्थिर Uint64 timestamp_offset = 0;
    स्थिरांक Uint64 now = SDL_GetTicksNS();

    जर (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    जर (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    परत nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
स्थिर Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 timestamp_offset = 0;
    स्थिर Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    जर (wl_timestamp_ms >= last) {
        जर (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_खालचा && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_वरचा) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } अन्यथा {
            last = wl_timestamp_ms;
        }
    } अन्यथा {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        जर (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_खालचा && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_वरचा) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    परत timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

स्थिर Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिरांक Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    परत Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिरांक Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    परत Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिरांक Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    परत Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर शून्य आदान_timestamp_listener(शून्य *data, संरचना zwp_आदान_timestamps_v1 *zwp_आदान_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

स्थिर स्थिरांक संरचना zwp_आदान_timestamps_v1_listener timestamp_listener = {
    आदान_timestamp_listener
};

स्थिर शून्य Wayland_Seat_Register_आदान_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    जर (seat->display->आदान_timestamps_manager) {
        जर (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_आदान_timestamps_manager_v1_get_keyboard_timestamps(seat->display->आदान_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_आदान_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        जर (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_आदान_timestamps_manager_v1_get_pointer_timestamps(seat->display->आदान_timestamps_manager, seat->pointer.wl_pointer);
            zwp_आदान_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        जर (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_आदान_timestamps_manager_v1_get_touch_timestamps(seat->display->आदान_timestamps_manager, seat->touch.wl_touch);
            zwp_आदान_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

शून्य Wayland_Display_Init_आदान_Timestamp_Manager(SDL_VideoData *display)
{
    जर (display->आदान_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_आदान_Timestamp_Listeners(seat);
        }
    }
}

स्थिर शून्य handle_pinch_begin(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t समय, संरचना wl_surface *surface, uint32_t fingers)
{
    जर (!surface) {
        परत;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    जर (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        स्थिरांक Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_update(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t समय,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    जर (seat->pointer.gesture_focus) {
        स्थिरांक Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        स्थिरांक दशांश s = (दशांश)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_end(शून्य *data, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t समय, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    जर (seat->pointer.gesture_focus) {
        स्थिरांक Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = रिक्त;
    }
}

स्थिर स्थिरांक संरचना zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

स्थिर शून्य Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    जर (seat->display->zwp_pointer_gestures) {
        जर (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
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
    जर (seat->display->cursor_shape_manager) {
        जर (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            जर (!tool->cursor_state.cursor_shape) {
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
    स्थिरांक bool send_event = !seat->display->initializing;

    जर (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
स्थिर शून्य keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    पर्यंत (elapsed >= repeat_info->next_repeat_ns) {
        जर (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            स्थिरांक Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_किल्ली_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->किल्ली, repeat_info->scancode, true);
        }
        जर (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

स्थिर शून्य keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t किल्ली, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, स्थिरांक अक्षर *text)
{
    जर (!repeat_info->repeat_rate) {
        परत;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->किल्ली = किल्ली;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    जर (text) {
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

पूर्णांक Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    स्थिरांक पूर्णांक display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णांक ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    जर (!d->text_आदान_manager && keyboard_focus && SDL_Text_आदान_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        जर (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        जर (seat->keyboard.repeat.किल्ली) {
            स्थिरांक Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            स्थिरांक Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            जर (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    जर (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        जर (timeoutNS > 0) {
            स्थिरांक Uint64 now = SDL_GetTicksNS();
            स्थिरांक Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        जर (ret == -1 && त्रुटि_सं == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            जर (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        जर (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            परत त्रुटि_सं == EINTR || त्रुटि_सं == EPIPE ? 1 : ret;
        }

        जर (timeoutNS > 0) {
            स्थिरांक Uint64 now = SDL_GetTicksNS();
            स्थिरांक Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        जर (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            जर (ret == 0) {
                परत poll_alarm_set ? 1 : 0;
            } अन्यथा {
                // Pump events on an interrupt or broken pipe to handle the error.
                परत त्रुटि_सं == EINTR || त्रुटि_सं == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        जर (ret == -1) {
            परत ret;
        }
    }

    // Signal to the caller that there might be an event available.
    परत 1;
}

शून्य Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    स्थिरांक पूर्णांक display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णांक ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    जर (!d->text_आदान_manager && keyboard_focus && SDL_Text_आदान_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    जर (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    जर (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        जर (ret < 0) {
            जा connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    जर (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        जर (ret == -1 && त्रुटि_सं == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            जर (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        जर (ret < 0 && त्रुटि_सं == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            जा connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        जर (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            जर (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } अन्यथा {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } अन्यथा {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    जर (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            जर (seat->keyboard.repeat.किल्ली) {
                Wayland_SeatSetKeymap(seat);

                स्थिरांक Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    जर (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

स्थिर शून्य pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : रिक्त;

    जर (window_data) {
        द्विगुण sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        द्विगुण sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        जर (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (द्विगुण)window_data->mask.offset_x;
            sy += (द्विगुण)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        जर (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (दशांश)sx, (दशांश)sy);
        } अन्यथा {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (दशांश)sx, (दशांश)sy);
        }

        seat->pointer.last_motion.x = (पूर्णांक)SDL_floor(sx);
        seat->pointer.last_motion.y = (पूर्णांक)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        जर (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        जर (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            निवड (rc) {
            स्थिती SDL_HITTEST_RESIZE_TOPLEFT:
                जर ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_डावा)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_डावा;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_डावा) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_शीर्ष:
                जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_NORMAL;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_TOPRIGHT:
                जर ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_उजवा)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_उजवा;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_उजवा) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_उजवा:
                जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_उजवा) {
                    rc = SDL_HITTEST_NORMAL;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                जर ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_उजवा)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_उजवा;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_उजवा) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_BOTTOM:
                जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_BOTTOMLEFT:
                जर ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_डावा)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_डावा;
                } अन्यथा जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_डावा) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                थांबा;
            स्थिती SDL_HITTEST_RESIZE_डावा:
                जर (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_डावा) {
                    rc = SDL_HITTEST_NORMAL;
                }
                थांबा;
            पूर्वनिर्धारित:
                थांबा;
            }

            जर (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

स्थिर शून्य pointer_handle_motion(शून्य *data, संरचना wl_pointer *pointer,
                                  uint32_t समय, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    स्थिरांक Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    जर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        जर (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
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
    जर (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        परत;
    }

    जर (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        परत;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_मोजणी;
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
    जर (!surface) {
        // Enter event for a destroyed surface.
        परत;
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

    जर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

स्थिर शून्य pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    जर (window) {
        जर (seat->pointer.focus) {
            जर (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = रिक्त;
                seat->pointer.focus_surface = रिक्त;
                साठी (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    जर (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                स्थिरांक bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                जर (!--window->pointer_focus_मोजणी && had_focus && !window->active_touch_मोजणी) {
                    SDL_SetMouseFocus(रिक्त);
                }

                जर (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } अन्यथा जर (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

स्थिर शून्य pointer_handle_leave(शून्य *data, संरचना wl_pointer *pointer,
                                 uint32_t serial, संरचना wl_surface *surface)
{
    जर (!surface) {
        // Leave event for a destroyed surface.
        परत;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    जर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

स्थिर bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    जर (seat->pointer.locked_pointer) {
        परत false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    जर (window->hit_test) {
        स्थिर स्थिरांक uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_डावा, XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष,
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_उजवा, XDG_TOPLEVEL_RESIZE_EDGE_उजवा,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_उजवा, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_डावा, XDG_TOPLEVEL_RESIZE_EDGE_डावा
        };

#ifdef HAVE_LIBDECOR_H
        स्थिर स्थिरांक uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_शीर्ष_डावा, LIBDECOR_RESIZE_EDGE_शीर्ष,
            LIBDECOR_RESIZE_EDGE_शीर्ष_उजवा, LIBDECOR_RESIZE_EDGE_उजवा,
            LIBDECOR_RESIZE_EDGE_BOTTOM_उजवा, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_डावा, LIBDECOR_RESIZE_EDGE_डावा
        };
#endif

        निवड (window_data->hit_test_result) {
        स्थिती SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            जर (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                जर (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } अन्यथा
#endif
                जर (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                जर (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            परत true;

        स्थिती SDL_HITTEST_RESIZE_TOPLEFT:
        स्थिती SDL_HITTEST_RESIZE_शीर्ष:
        स्थिती SDL_HITTEST_RESIZE_TOPRIGHT:
        स्थिती SDL_HITTEST_RESIZE_उजवा:
        स्थिती SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        स्थिती SDL_HITTEST_RESIZE_BOTTOM:
        स्थिती SDL_HITTEST_RESIZE_BOTTOMLEFT:
        स्थिती SDL_HITTEST_RESIZE_डावा:
#ifdef HAVE_LIBDECOR_H
            जर (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                जर (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } अन्यथा
#endif
                जर (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                जर (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            परत true;

        पूर्वनिर्धारित:
            परत false;
        }
    }

    परत false;
}

स्थिर शून्य pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    जर (window) {
        bool ignore_click = false;

        जर (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            जर (sdl_button == SDL_BUTTON_डावा && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                परत; // don't pass this event on to app.
            }
        } अन्यथा {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        जर (window->last_focus_event_time_ns) {
            जर (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        जर (!seat->pointer.relative_pointer) {
            जर (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } अन्यथा {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                जर (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        जर (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

स्थिर शून्य pointer_handle_button(शून्य *data, संरचना wl_pointer *pointer, uint32_t serial,
                                  uint32_t समय, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    निवड (button) {
    स्थिती BTN_डावा:
        sdl_button = SDL_BUTTON_डावा;
        थांबा;
    स्थिती BTN_मधला:
        sdl_button = SDL_BUTTON_मधला;
        थांबा;
    स्थिती BTN_उजवा:
        sdl_button = SDL_BUTTON_उजवा;
        थांबा;
    पूर्वनिर्धारित:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        थांबा;
    }

    जर (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, समय);

    जर (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        जर (state_w) {
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
    स्थिरांक गणना wl_pointer_axis a = axis;

    जर (seat->pointer.focus) {
        दशांश x, y;

        निवड (a) {
        स्थिती WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (दशांश)wl_fixed_to_double(मूल्य);
            थांबा;
        स्थिती WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (दशांश)wl_fixed_to_double(मूल्य);
            y = 0;
            थांबा;
        पूर्वनिर्धारित:
            परत;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

स्थिर शून्य pointer_handle_axis_common(SDL_WaylandSeat *seat, गणना SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t मूल्य)
{
    स्थिरांक गणना wl_pointer_axis a = axis;

    जर (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        निवड (a) {
        स्थिती WL_POINTER_AXIS_VERTICAL_SCROLL:
            निवड (type) {
            स्थिती SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                जर (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (दशांश)wl_fixed_to_double(मूल्य);
                थांबा;
            स्थिती SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                जर (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (दशांश)wl_fixed_to_double(मूल्य);
                }
                थांबा;
            स्थिती SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                जर (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (दशांश)wl_fixed_to_double(मूल्य);
                }
                थांबा;
            }
            थांबा;
        स्थिती WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            निवड (type) {
            स्थिती SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                जर (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (दशांश)wl_fixed_to_double(मूल्य);
                थांबा;
            स्थिती SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                जर (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (दशांश)wl_fixed_to_double(मूल्य);
                }
                थांबा;
            स्थिती SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                जर (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (दशांश)wl_fixed_to_double(मूल्य);
                }
                थांबा;
            }
            थांबा;
        }
    }
}

स्थिर शून्य pointer_handle_axis(शून्य *data, संरचना wl_pointer *pointer,
                                uint32_t समय, uint32_t axis, wl_fixed_t मूल्य)
{
    SDL_WaylandSeat *seat = data;
    स्थिरांक Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, समय);

    जर (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
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

    निवड (axis_relative_direction) {
    स्थिती WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        थांबा;
    स्थिती WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        थांबा;
    }
}

स्थिर शून्य pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    जर (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        द्विगुण dx;
        द्विगुण dy;
        जर (mouse->आदान_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } अन्यथा {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (दशांश)dx, (दशांश)dy);
    }
}

स्थिर शून्य pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    दशांश x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    निवड (seat->pointer.pending_frame.axis.x_axis_type) {
    स्थिती SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        थांबा;
    स्थिती SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        थांबा;
    स्थिती SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        थांबा;
    पूर्वनिर्धारित:
        x = 0.0f;
        थांबा;
    }

    निवड (seat->pointer.pending_frame.axis.y_axis_type) {
    स्थिती SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        थांबा;
    स्थिती SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        थांबा;
    स्थिती SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        थांबा;
    पूर्वनिर्धारित:
        y = 0.0f;
        थांबा;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

स्थिर शून्य pointer_handle_frame(शून्य *data, संरचना wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    जर (seat->pointer.pending_frame.enter_surface) {
        जर (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            जर (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
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

        जर (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    जर (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    जर (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    साठी (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        स्थिरांक Uint32 mask = SDL_BUTTON_MASK(i);
        जर (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        जर (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    जर (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    जर (seat->pointer.pending_frame.leave_surface) {
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
                                     uint32_t समय, uint32_t axis)
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

स्थिर स्थिरांक संरचना wl_pointer_listener pointer_listener = {
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

    जर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } अन्यथा {
        pointer_dispatch_relative_motion(seat);
    }
}

स्थिर स्थिरांक संरचना zwp_relative_pointer_v1_listener relative_pointer_listener = {
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

स्थिर स्थिरांक संरचना zwp_locked_pointer_v1_listener locked_pointer_listener = {
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

स्थिर स्थिरांक संरचना zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

स्थिर शून्य touch_handler_down(शून्य *data, संरचना wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, संरचना wl_surface *surface,
                               पूर्णांक id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    जर (!surface) {
        परत;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    जर (window_data && window_data->surface == surface) {
        दशांश x, y;

        जर (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } अन्यथा {
            x = (दशांश)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        जर (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } अन्यथा {
            y = (दशांश)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_मोजणी;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

स्थिर शून्य touch_handler_up(शून्य *data, संरचना wl_touch *touch, uint32_t serial, uint32_t timestamp, पूर्णांक id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    जर (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        जर (window_data && window_data->surface == surface) {
            स्थिरांक दशांश x = (दशांश)wl_fixed_to_double(fx) / window_data->current.logical_width;
            स्थिरांक दशांश y = (दशांश)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_मोजणी;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            जर (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_मोजणी &&
                !window_data->pointer_focus_मोजणी && !window_data->active_touch_मोजणी) {
                SDL_SetMouseFocus(रिक्त);
            }
        }
    }
}

स्थिर शून्य touch_handler_motion(शून्य *data, संरचना wl_touch *touch, uint32_t timestamp, पूर्णांक id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    जर (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        जर (window_data && window_data->surface == surface) {
            स्थिरांक दशांश x = (दशांश)wl_fixed_to_double(fx) / window_data->current.logical_width;
            स्थिरांक दशांश y = (दशांश)wl_fixed_to_double(fy) / window_data->current.logical_height;

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

स्थिर स्थिरांक संरचना wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#जर !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
स्थिर माप_प्रकार xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t किल्ली, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, माप_प्रकार masks_size)
{
    जर (!masks_out || !masks_size) {
        परत 0;
    }

    // Level 0 is always unmodified, so early out.
    जर (level == 0) {
        *masks_out = 0;
        परत 1;
    }

    माप_प्रकार mask_idx = 0;
    स्थिरांक xkb_mod_mask_t keymod_masks[] = {
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
    स्थिरांक xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    स्थिरांक xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    साठी (माप_प्रकार i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        जर (WAYLAND_xkb_state_किल्ली_get_level(seat->keyboard.xkb.state, किल्ली, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            जर (++mask_idx == masks_size) {
                थांबा;
            }
        }
    }

    परत mask_idx;
}
#endif

स्थिर शून्य Wayland_KeymapIterator(संरचना xkb_keymap *keymap, xkb_keycode_t किल्ली, शून्य *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    स्थिरांक xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    स्थिरांक xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    जर (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, किल्ली - 8);
    }

    साठी (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.अंक_layouts; ++layout) {
        स्थिरांक xkb_level_index_t अंक_levels = WAYLAND_xkb_keymap_अंक_levels_for_किल्ली(seat->keyboard.xkb.keymap, किल्ली, layout);
        साठी (xkb_level_index_t level = 0; level < अंक_levels; ++level) {
            जर (WAYLAND_xkb_keymap_किल्ली_get_syms_by_level(seat->keyboard.xkb.keymap, किल्ली, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                जर (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_किल्ली_Sym(syms[0], किल्ली);
                    जर (scancode == SDL_SCANCODE_UNKNOWN) {
                        सुरूठेवा;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#जर SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                स्थिरांक माप_प्रकार अंक_masks = WAYLAND_xkb_keymap_किल्ली_get_mods_for_level(seat->keyboard.xkb.keymap, किल्ली, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#अन्यथा
                स्थिरांक माप_प्रकार अंक_masks = xkb_legacy_get_mods_for_level(seat, किल्ली, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                साठी (माप_प्रकार mask = 0; mask < अंक_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    जर ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        सुरूठेवा;
                    }

                    स्थिरांक SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_किल्ली_Code_From_किल्ली_Sym(syms[0], किल्ली, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    जर (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        जर (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_किल्ली *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, आकार(Wayland_Reserved_किल्ली));
                        जर (res) {
                            res->scancode = scancode;
                            res->किल्ली = किल्ली - 8;
                        }
                    }

                    जर (!keycode) {
                        निवड (scancode) {
                        स्थिती SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            थांबा;
                        स्थिती SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            थांबा;
                        स्थिती SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            थांबा;
                        स्थिती SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            थांबा;
                        पूर्वनिर्धारित:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            थांबा;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

स्थिर शून्य keyboard_handle_keymap(शून्य *data, संरचना wl_keyboard *keyboard,
                                   uint32_t format, पूर्णांक fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    अक्षर *map_str;

    जर (!data) {
        बंद(fd);
        परत;
    }

    जर (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        बंद(fd);
        परत;
    }

    map_str = mmap(रिक्त, size, PROT_READ, MAP_PRIVATE, fd, 0);
    जर (map_str == MAP_FAILED) {
        बंद(fd);
        परत;
    }

    जर (seat->keyboard.xkb.keymap != रिक्त) {
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
    बंद(fd);

    जर (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        परत;
    }

    // Clear the old layouts.
    साठी (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = रिक्त;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.अंक_layouts = 0;

#जर SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
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

    जर (seat->keyboard.xkb.state != रिक्त) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = रिक्त;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    जर (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = रिक्त;
        परत;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == रिक्त;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.अंक_layouts = WAYLAND_xkb_keymap_अंक_layouts(seat->keyboard.xkb.keymap);
    जर (seat->keyboard.xkb.अंक_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.अंक_layouts, आकार(SDL_Keymap *));
        जर (!seat->keyboard.sdl_keymap) {
            परत;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        साठी (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            जर (!seat->keyboard.sdl_keymap[i]) {
                साठी (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = रिक्त;
                परत;
            }
        }

        WAYLAND_xkb_keymap_किल्ली_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

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
    स्थिरांक अक्षर *locale = SDL_getenv("LC_ALL");
    जर (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        जर (!locale) {
            locale = SDL_getenv("LANG");
            जर (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    जर (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        जर (seat->keyboard.xkb.compose_table != रिक्त) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = रिक्त;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        जर (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            जर (seat->keyboard.xkb.compose_state != रिक्त) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = रिक्त;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            जर (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = रिक्त;
            }
        }
    } अन्यथा जर (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
स्थिर SDL_Scancode Wayland_Get_Scancode_For_किल्ली(SDL_WaylandSeat *seat, Uint32 किल्ली, स्थिरांक xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    जर (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, किल्ली);

        // No table entry? Check the reserved list.
        जर (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_किल्ली *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                जर (i->किल्ली == किल्ली) {
                    परत i->scancode;
                }
            }
        }
    } अन्यथा {
        स्थिरांक xkb_keysym_t *keysym;
        जर (WAYLAND_xkb_state_किल्ली_get_syms(seat->keyboard.xkb.state, किल्ली + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_किल्ली_Sym(keysym[0], किल्ली + 8);
            जर (syms) {
                *syms = keysym;
            }
        }
    }

    परत scancode;
}

स्थिर शून्य Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool किल्ली_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    जर (!किल्ली_pressed) {
        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        जर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            जर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
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
    स्थिरांक xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    जर (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        जर (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } अन्यथा जर (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        जर (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } अन्यथा जर (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        जर (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } अन्यथा जर (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        जर (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } अन्यथा जर (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    जर (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    जर (xkb_locked_modifiers & seat->keyboard.xkb.अंक_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_अंक;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_अंक;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

स्थिर शून्य Wayland_Handle_Modifier_किल्ल्या(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    स्थिरांक SDL_Keycode keycode = SDL_Get_किल्ली_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    निवड (keycode) {
    स्थिती SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        थांबा;
    स्थिती SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        थांबा;
    स्थिती SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        थांबा;
    स्थिती SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        थांबा;
    स्थिती SDLK_LALT:
        mod = SDL_KMOD_LALT;
        थांबा;
    स्थिती SDLK_RALT:
        mod = SDL_KMOD_RALT;
        थांबा;
    स्थिती SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        थांबा;
    स्थिती SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        थांबा;
    स्थिती SDLK_MODE:
        mod = SDL_KMOD_MODE;
        थांबा;
    स्थिती SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        थांबा;
    पूर्वनिर्धारित:
        परत;
    }

    जर (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } अन्यथा {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

स्थिर शून्य keyboard_handle_enter(शून्य *data, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface,
                                  संरचना wl_array *किल्ल्या)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *किल्ली;

    जर (!surface) {
        // Enter event for a destroyed surface.
        परत;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    जर (!window) {
        // Not a surface owned by SDL.
        परत;
    }

    ++window->keyboard_focus_मोजणी;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_आदान(seat);

#ifdef SDL_USE_IME
    जर (!seat->text_आदान.zwp_text_आदान) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (किल्ली, किल्ल्या) {
        स्थिरांक SDL_Scancode scancode = Wayland_Get_Scancode_For_किल्ली(seat, *किल्ली, रिक्त);
        जर (scancode != SDL_SCANCODE_UNKNOWN) {
            स्थिरांक SDL_Keycode keycode = SDL_Get_किल्ली_From_Scancode(scancode, SDL_KMOD_NONE, false);

            निवड (keycode) {
            स्थिती SDLK_LSHIFT:
            स्थिती SDLK_RSHIFT:
            स्थिती SDLK_LCTRL:
            स्थिती SDLK_RCTRL:
            स्थिती SDLK_LALT:
            स्थिती SDLK_RALT:
            स्थिती SDLK_LGUI:
            स्थिती SDLK_RGUI:
            स्थिती SDLK_MODE:
            स्थिती SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_किल्ल्या(seat, scancode, true);
                SDL_Send_Keyboard_किल्ली_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *किल्ली, scancode, true);
                थांबा;
            पूर्वनिर्धारित:
                थांबा;
            }
        }
    }
}

स्थिर शून्य keyboard_handle_leave(शून्य *data, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    जर (!surface) {
        // Leave event for a destroyed surface.
        परत;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    जर (!window) {
        // Not a surface owned by SDL.
        परत;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.किल्ली = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    पर्यंत (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    स्थिरांक bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = रिक्त;
    --window->keyboard_focus_मोजणी;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    जर (!window->keyboard_focus_मोजणी && had_focus) {
        SDL_SetKeyboardFocus(रिक्त);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_आदान(seat);

#ifdef SDL_USE_IME
    जर (!seat->text_आदान.zwp_text_आदान && !window->keyboard_focus_मोजणी) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    जर (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_मोजणी && !window->active_touch_मोजणी) {
        SDL_SetMouseFocus(रिक्त);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, रिक्त);
}

स्थिर bool keyboard_आदान_get_text(अक्षर text[8], स्थिरांक SDL_WaylandSeat *seat, uint32_t किल्ली, bool down, bool *handled_by_ime)
{
    स्थिरांक xkb_keysym_t *syms;
    xkb_keysym_t sym;

    जर (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        परत false;
    }

    // TODO: Can this happen?
    जर (WAYLAND_xkb_state_किल्ली_get_syms(seat->keyboard.xkb.state, किल्ली + 8, &syms) != 1) {
        परत false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    जर (SDL_IME_Process_किल्ली_Event(sym, किल्ली + 8, down)) {
        जर (handled_by_ime) {
            *handled_by_ime = true;
        }
        परत true;
    }
#endif

    जर (!down) {
        परत false;
    }

    जर (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        निवड (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        स्थिती XKB_COMPOSE_COMPOSING:
            जर (handled_by_ime) {
                *handled_by_ime = true;
            }
            परत true;
        स्थिती XKB_COMPOSE_CANCELLED:
        पूर्वनिर्धारित:
            sym = XKB_किल्ली_No_चिन्ह;
            थांबा;
        स्थिती XKB_COMPOSE_NOTHING:
            थांबा;
        स्थिती XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            थांबा;
        }
    }

    परत WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

स्थिर शून्य keyboard_handle_किल्ली(शून्य *data, संरचना wl_keyboard *keyboard,
                                uint32_t serial, uint32_t समय, uint32_t किल्ली,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    गणना wl_keyboard_किल्ली_state state = state_w;
    अक्षर text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    स्थिरांक Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, समय);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    जर (state == WL_KEYBOARD_किल्ली_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        जर (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_किल्ली_repeats(seat->keyboard.xkb.keymap, किल्ली + 8)) {
            परत;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_किल्ली_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    जर (state == WL_KEYBOARD_किल्ली_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        जर (keyboard_focus && SDL_Text_आदान_Active(keyboard_focus)) {
            has_text = keyboard_आदान_get_text(text, seat, किल्ली, true, &handled_by_ime);
        }
    } अन्यथा {
        जर (किल्ली == seat->keyboard.repeat.किल्ली) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            स्थिरांक Uint64 elapsed = SDL_MS_TO_NS(समय - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.किल्ली = 0;
        }
        keyboard_आदान_get_text(text, seat, किल्ली, false, &handled_by_ime);
    }

    स्थिरांक xkb_keysym_t *syms = रिक्त;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_किल्ली(seat, किल्ली, &syms);
    Wayland_Handle_Modifier_किल्ल्या(seat, scancode, state == WL_KEYBOARD_किल्ली_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    जर (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        स्थिरांक SDL_Keycode keycode = (SDL_Keycode)SDL_किल्ली_Sym_To_Ucs4(syms[0]);
        जर (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            जर (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_किल्ली_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, किल्ली, scancode, state == WL_KEYBOARD_किल्ली_STATE_PRESSED);

    जर (state == WL_KEYBOARD_किल्ली_STATE_PRESSED) {
        जर (handled_by_ime) {
            has_text = false;
        }
        जर (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        जर (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_किल्ली_repeats(seat->keyboard.xkb.keymap, किल्ली + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, किल्ली, समय, timestamp_ns, scancode, has_text ? text : रिक्त);
        }
    }
}

स्थिर शून्य keyboard_handle_modifiers(शून्य *data, संरचना wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    स्थिरांक uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    जर (!seat->keyboard.xkb.state) {
        परत;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    जर (seat->keyboard.repeat.किल्ली) {
        अक्षर text[8];

        जर (keyboard_आदान_get_text(text, seat, seat->keyboard.repeat.किल्ली, true, रिक्त)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    जर (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        जर (seat->keyboard.xkb.compose_state) {
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

    जर (!rate) {
        seat->keyboard.repeat.किल्ली = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

स्थिर स्थिरांक संरचना wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_किल्ली,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

स्थिर शून्य Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    जर (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    जर (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = रिक्त;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    जर (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    जर (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    जर (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    जर (seat->pointer.timestamps) {
        zwp_आदान_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    जर (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    जर (seat->pointer.wl_pointer) {
        जर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
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
    जर (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    जर (seat->keyboard.sdl_keymap) {
        जर (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        साठी (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = रिक्त;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    जर (seat->keyboard.किल्ली_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.किल्ली_inhibitor);
    }

    जर (seat->keyboard.timestamps) {
        zwp_आदान_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    जर (seat->keyboard.wl_keyboard) {
        जर (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } अन्यथा {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    जर (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    जर (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    जर (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    जर (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

स्थिर शून्य Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    जर (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    जर (seat->touch.timestamps) {
        zwp_आदान_timestamps_v1_destroy(seat->touch.timestamps);
    }

    जर (seat->touch.wl_touch) {
        जर (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
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
    अक्षर name_fmt[256];

    जर ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        जर (seat->name) {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } अन्यथा जर (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    जर ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        जर (seat->name) {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } अन्यथा जर (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    जर ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        जर (seat->name) {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, आकार(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } अन्यथा जर (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_आदान_Timestamp_Listeners(seat);
}

स्थिर शून्य seat_handle_name(शून्य *data, संरचना wl_seat *wl_seat, स्थिरांक अक्षर *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    जर (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

स्थिर स्थिरांक संरचना wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

स्थिर शून्य data_offer_handle_offer(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                    स्थिरांक अक्षर *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

स्थिर शून्य data_offer_handle_source_actions(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

स्थिर शून्य data_offer_handle_actions(शून्य *data, संरचना wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

स्थिर स्थिरांक संरचना wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

स्थिर शून्य primary_selection_offer_handle_offer(शून्य *data, संरचना zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 स्थिरांक अक्षर *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

स्थिर स्थिरांक संरचना zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

स्थिर शून्य data_device_handle_data_offer(शून्य *data, संरचना wl_data_device *wl_data_device,
                                          संरचना wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, आकार(*data_offer));
    जर (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
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
    जर (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    जर (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        जर (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        जर (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        जर (!data_device->has_mime_file) {
            माप_प्रकार mime_मोजणी = 0;
            स्थिरांक अक्षर *स्थिरांक *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_मोजणी);
            साठी (माप_प्रकार i = 0; i < mime_मोजणी; ++i) {
                जर (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    थांबा;
                }
            }
        }

        जर (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            जर (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            द्विगुण dx = wl_fixed_to_double(x);
            द्विगुण dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            जर (surface == window->mask.surface) {
                dx += (द्विगुण)window->mask.offset_x;
                dy += (द्विगुण)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (दशांश)dx, (दशांश)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } अन्यथा {
            // Decline the offer.
            wl_data_offer_accept(id, serial, रिक्त);
            जर (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } अन्यथा {
        data_device->dnd_window = रिक्त;
        data_device->dnd_surface = रिक्त;

        // Decline the offer.
        जर (id) {
            wl_data_offer_accept(id, serial, रिक्त);
            जर (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

स्थिर शून्य data_device_handle_leave(शून्य *data, संरचना wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    जर (data_device->drag_offer) {
        जर (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } अन्यथा {
            SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = रिक्त;
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = रिक्त;
}

स्थिर शून्य data_device_handle_motion(शून्य *data, संरचना wl_data_device *wl_data_device,
                                      uint32_t समय, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    जर (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        द्विगुण dx = wl_fixed_to_double(x);
        द्विगुण dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        जर (data_device->dnd_surface == window_data->mask.surface) {
            dx += (द्विगुण)window_data->mask.offset_x;
            dy += (द्विगुण)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (दशांश)dx, (दशांश)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
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

स्थिर स्थिरांक संरचना wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

स्थिर शून्य drop_dispatch_handler(शून्य *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    जर (drop->dnd_window) {
        माप_प्रकार length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        जर (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            शून्य *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            जर (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                जर (dbus) {
                    पूर्णांक path_मोजणी = 0;
                    अक्षर **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_मोजणी);
                    // If dropped files contain a directory the list is empty
                    जर (paths && path_मोजणी > 0) {
                        साठी (पूर्णांक i = 0; i < path_मोजणी; i++) {
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
        जर (!drop_handled) {
            जर (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                शून्य *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                जर (buffer) {
                    अक्षर *saveptr = रिक्त;
                    अक्षर *token = SDL_strtok_r((अक्षर *)buffer, "\r\n", &saveptr);
                    पर्यंत (token) {
                        जर (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, रिक्त, token);
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } अन्यथा जर (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                शून्य *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                जर (buffer) {
                    अक्षर *saveptr = रिक्त;
                    अक्षर *token = SDL_strtok_r((अक्षर *)buffer, "\r\n", &saveptr);
                    पर्यंत (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        जर (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
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

    जर (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, आकार(Wayland_DropData));
        जर (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_घाला(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } अन्यथा {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
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

    जर (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

स्थिर स्थिरांक संरचना wl_data_device_listener data_device_listener = {
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
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, आकार(*primary_selection_offer));
    जर (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर शून्य primary_selection_device_handle_selection(शून्य *data, संरचना zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      संरचना zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = रिक्त;

    जर (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    जर (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर स्थिरांक संरचना zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

स्थिर शून्य text_आदान_enter(शून्य *data,
                             संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_आदान_leave(शून्य *data,
                             संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_आदान_preedit_string(शून्य *data,
                                      संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                                      स्थिरांक अक्षर *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_आदान.has_preedit = true;
    जर (text) {
        पूर्णांक cursor_begin_utf8 = cursor_begin >= 0 ? (पूर्णांक)SDL_utf8strnlen(text, cursor_begin) : -1;
        पूर्णांक cursor_end_utf8 = cursor_end >= 0 ? (पूर्णांक)SDL_utf8strnlen(text, cursor_end) : -1;
        पूर्णांक cursor_size_utf8;
        जर (cursor_end_utf8 >= 0) {
            जर (cursor_begin_utf8 >= 0) {
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

स्थिर शून्य text_आदान_commit_string(शून्य *data,
                                     संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                                     स्थिरांक अक्षर *text)
{
    SDL_SendKeyboardText(text);
}

स्थिर शून्य text_आदान_delete_surrounding_text(शून्य *data,
                                               संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

स्थिर शून्य text_आदान_done(शून्य *data,
                            संरचना zwp_text_आदान_v3 *zwp_text_आदान_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    जर (!seat->text_आदान.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_आदान.has_preedit = false;
}

स्थिर स्थिरांक संरचना zwp_text_आदान_v3_listener text_आदान_listener = {
    text_आदान_enter,
    text_आदान_leave,
    text_आदान_preedit_string,
    text_आदान_commit_string,
    text_आदान_delete_surrounding_text,
    text_आदान_done
};

स्थिर शून्य Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    जर (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        जर (dbus) {
            स्थिरांक अक्षर *id = dbus->bus_get_unique_name(dbus->session_conn);
            जर (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    जर (!data_device->id_str)
#endif
    {
        अक्षर id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, आकार(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

स्थिर शून्य Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    जर (!seat->display->data_device_manager) {
        परत;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, आकार(*data_device));
    जर (!data_device) {
        परत;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    जर (!data_device->data_device) {
        SDL_free(data_device);
        परत;
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
    जर (!seat->display->primary_selection_device_manager) {
        परत;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, आकार(*primary_selection_device));
    जर (!primary_selection_device) {
        परत;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    जर (!primary_selection_device->primary_selection_device) {
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

स्थिर शून्य Wayland_Seat_Create_Text_आदान(SDL_WaylandSeat *seat)
{
    जर (seat->display->text_आदान_manager) {
        seat->text_आदान.zwp_text_आदान = zwp_text_आदान_manager_v3_get_text_आदान(seat->display->text_आदान_manager, seat->wl_seat);

        जर (seat->text_आदान.zwp_text_आदान) {
            zwp_text_आदान_v3_set_user_data(seat->text_आदान.zwp_text_आदान, seat);
            zwp_text_आदान_v3_add_listener(seat->text_आदान.zwp_text_आदान,
                                           &text_आदान_listener, seat);
        }
    }
}

शून्य Wayland_Display_Init_Text_आदान_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_आदान(seat);
    }
}

// Pen/Tablet support...
स्थिर शून्य tablet_tool_handle_type(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    निवड (type) {
        #define CASE(typ) स्थिती ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; परत
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        पूर्वनिर्धारित: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
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
    निवड (capability) {
        #define CASE(wltyp,sdltyp) स्थिती ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; परत
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        पूर्वनिर्धारित: थांबा;  // unsupported here.
    }
}

स्थिर शून्य tablet_tool_handle_done(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    जर (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
        sdltool->instance_id = SDL_AddPenDevice(0, रिक्त, window, &sdltool->info, sdltool, false);
    }
}

स्थिर शून्य tablet_tool_handle_removed(शून्य *data, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    जर (sdltool->instance_id) {
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
    जर (windowdata) {
        sdltool->frame.x = (दशांश)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (दशांश)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

स्थिर शून्य tablet_tool_handle_pressure(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((दशांश) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    जर (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

स्थिर शून्य tablet_tool_handle_distance(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((दशांश) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    जर (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

स्थिर शून्य tablet_tool_handle_tilt(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (दशांश)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (दशांश)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

स्थिर शून्य tablet_tool_handle_button(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    पूर्णांक sdlbutton;

    निवड (button) {
    स्थिती BTN_STYLUS:
        sdlbutton = 1;
        थांबा;
    स्थिती BTN_STYLUS2:
        sdlbutton = 2;
        थांबा;
    स्थिती BTN_STYLUS3:
        sdlbutton = 3;
        थांबा;
    पूर्वनिर्धारित:
        परत;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

स्थिर शून्य tablet_tool_handle_rotation(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    स्थिरांक दशांश rotation = (दशांश)(wl_fixed_to_double(degrees));
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

स्थिर शून्य tablet_tool_handle_frame(शून्य *data, संरचना zwp_tablet_tool_v2 *tool, uint32_t समय)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    स्थिरांक SDL_PenID instance_id = sdltool->instance_id;
    जर (!instance_id) {
        परत;  // Not a pen we report on.
    }

    स्थिरांक Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(समय));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
    स्थिरांक bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    जर (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    जर (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        जर (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } अन्यथा {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } अन्यथा {
        जर (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        जर (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    साठी (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_मोजणी; i++) {
        जर (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    साठी (पूर्णांक i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        स्थिरांक पूर्णांक state = sdltool->frame.buttons[i];
        जर (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    जर (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = रिक्त;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

स्थिर स्थिरांक संरचना zwp_tablet_tool_v2_listener tablet_tool_listener = {
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
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, आकार(*sdltool));

    जर (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.अंक_buttons = -1;

        जर (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_घाला(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

स्थिर शून्य tablet_seat_handle_pad_added(शून्य *data, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

स्थिर स्थिरांक संरचना zwp_tablet_seat_v2_listener tablet_seat_listener = {
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
    जर (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } अन्यथा {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, रिक्त);
    }

    जर (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = रिक्त;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

शून्य Wayland_DisplayCreateSeat(SDL_VideoData *display, संरचना wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, आकार(SDL_WaylandSeat));
    जर (!seat) {
        परत;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_घाला(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_आदान(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    जर (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

शून्य Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        जर (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        जर (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = रिक्त;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            जर (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            जर (tool->focus == window) {
                tool->focus = रिक्त;
                Wayland_TabletToolUpdateCursor(tool);
                जर (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            जर (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                जर (drop->cleanup_callback) {
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
    जर (!seat) {
        परत;
    }

    SDL_free(seat->name);

    जर (seat->data_device) {
        जर (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        जर (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        जर (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            जर (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        जर (seat->data_device->data_device) {
            जर (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } अन्यथा {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    जर (seat->primary_selection_device) {
        जर (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        जर (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        जर (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    जर (seat->text_आदान.zwp_text_आदान) {
        zwp_text_आदान_v3_destroy(seat->text_आदान.zwp_text_आदान);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    जर (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } अन्यथा {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

स्थिर शून्य Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    जर (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        जर (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            जर (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                जर (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } अन्यथा {
                    relative_focus = seat->pointer.focus->keyboard_focus_मोजणी != 0;
                }
            } अन्यथा {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        जर (relative_focus) {
            जर (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } अन्यथा जर (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = रिक्त;
        }
    }
}

स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    जर (display->किल्ली_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        जर (seat->keyboard.किल्ली_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.किल्ली_inhibitor);
            seat->keyboard.किल्ली_inhibitor = रिक्त;
        }

        जर (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            जर (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                जर (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.किल्ली_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->किल्ली_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

शून्य Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    जर (display->pointer_constraints) {
        जर (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = रिक्त;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        जर (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            जर (seat->pointer.relative_pointer) {
                जर (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    जर (seat->pointer.confined_pointer) {
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
                परत;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            जर (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = रिक्त;
            }

            SDL_WindowData *w = seat->pointer.focus;
            जर (!w) {
                परत;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            जर (!(window->flags & SDL_WINDOW_आदान_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                परत;
            }

            संरचना wl_region *confine_rect = रिक्त;
            जर (!SDL_RectEmpty(&window->mouse_rect)) {
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
                जर (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    पूर्णांक closest_x = seat->pointer.last_motion.x;
                    पूर्णांक closest_y = seat->pointer.last_motion.y;

                    जर (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } अन्यथा जर (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    जर (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } अन्यथा जर (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            जर (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                जर (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
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
                जर (confine_rect) {
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
        जर (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

शून्य Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        जर (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

शून्य Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    जर (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
