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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_scancode_tables_c.h"
#அந்தர்பாவ "../../events/SDL_keysym_to_keycode_c.h"
#அந்தர்பாவ "../../core/linux/SDL_system_theme.h"
#அந்தர்பாவ "../SDL_sysvideo.h"

#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"
#அந்தர்பாவ "SDL_waylandwindow.h"
#அந்தர்பாவ "SDL_waylandmouse.h"
#அந்தர்பாவ "SDL_waylandclipboard.h"
#அந்தர்பாவ "SDL_waylandkeyboard.h"

#அந்தர்பாவ "pointer-constraints-unstable-v1-client-protocol.h"
#அந்தர்பாவ "relative-pointer-unstable-v1-client-protocol.h"
#அந்தர்பாவ "xdg-shell-client-protocol.h"
#அந்தர்பாவ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#அந்தர்பாவ "text-input-unstable-v3-client-protocol.h"
#அந்தர்பாவ "tablet-v2-client-protocol.h"
#அந்தர்பாவ "primary-selection-unstable-v1-client-protocol.h"
#அந்தர்பாவ "input-timestamps-unstable-v1-client-protocol.h"
#அந்தர்பாவ "pointer-gestures-unstable-v1-client-protocol.h"
#அந்தர்பாவ "cursor-shape-v1-client-protocol.h"
#அந்தர்பாவ "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#அந்தர்பாவ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_உள்ளீடு_LINUXEV
#அந்தர்பாவ <linux/input.h>
#இல்லையெனில்
#define BTN_இடது    (0x110)
#define BTN_வலது   (0x111)
#define BTN_நடு  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#அந்தர்பாவ "../../events/SDL_keysym_to_scancode_c.h"
#அந்தர்பாவ "../../events/imKStoUCS.h"
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <xkbcommon/xkbcommon-compose.h>
#அந்தர்பாவ <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_கீழ்  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_உயர்வு (WAYLAND_TIMER_ROLLOVER_INTERVAL_கீழ் * 15U)

// Scoped function declarations
நிலையான வெறுமை Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

வகைவரை கட்டமைப்பு
{
    Uint32 சாவி;
    SDL_Scancode scancode;
} Wayland_Reserved_சாவி;

வகைவரை கட்டமைப்பு
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    கட்டமைப்பு wl_surface *surface;

    கட்டமைப்பு wl_list link;
} SDL_WaylandTouchPoint;

நிலையான வெறுமை Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, கட்டமைப்பு wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(அளவு(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_செருகு(&seat->touch.points, &tp->link);
}

நிலையான வெறுமை Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    எனில் (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        எனில் (window_data) {
            மாறிலி தசம x = (தசம)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            மாறிலி தசம y = (தசம)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_மொத்தம்;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            எனில் (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_மொத்தம் &&
                !window_data->pointer_focus_மொத்தம் && !window_data->active_touch_மொத்தம்) {
                SDL_SetMouseFocus(வெற்று);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

நிலையான வெறுமை Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, கட்டமைப்பு wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        எனில் (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            எனில் (surface) {
                *surface = tp->surface;
            }
            நிறுத்து;
        }
    }
}

நிலையான வெறுமை Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, கட்டமைப்பு wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        எனில் (tp->id == id) {
            எனில் (fx) {
                *fx = tp->fx;
            }
            எனில் (fy) {
                *fy = tp->fy;
            }
            எனில் (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            நிறுத்து;
        }
    }
}

நிலையான வெறுமை Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (முழு)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (முழு)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (முழு)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (முழு)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

நிலையான Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    நிலையான Uint64 timestamp_offset = 0;
    மாறிலி Uint64 now = SDL_GetTicksNS();

    எனில் (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    எனில் (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    திரும்பு nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
நிலையான Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    நிலையான Uint64 timestamp_offset = 0;
    நிலையான Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    எனில் (wl_timestamp_ms >= last) {
        எனில் (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_கீழ் && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_உயர்வு) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } இல்லையெனில் {
            last = wl_timestamp_ms;
        }
    } இல்லையெனில் {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        எனில் (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_கீழ் && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_உயர்வு) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    திரும்பு timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

நிலையான Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    மாறிலி Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    திரும்பு Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

நிலையான Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    மாறிலி Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    திரும்பு Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    மாறிலி Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    திரும்பு Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

நிலையான வெறுமை உள்ளீடு_timestamp_listener(வெறுமை *data, கட்டமைப்பு zwp_உள்ளீடு_timestamps_v1 *zwp_உள்ளீடு_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

நிலையான மாறிலி கட்டமைப்பு zwp_உள்ளீடு_timestamps_v1_listener timestamp_listener = {
    உள்ளீடு_timestamp_listener
};

நிலையான வெறுமை Wayland_Seat_Register_உள்ளீடு_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    எனில் (seat->display->உள்ளீடு_timestamps_manager) {
        எனில் (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_உள்ளீடு_timestamps_manager_v1_get_keyboard_timestamps(seat->display->உள்ளீடு_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_உள்ளீடு_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        எனில் (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_உள்ளீடு_timestamps_manager_v1_get_pointer_timestamps(seat->display->உள்ளீடு_timestamps_manager, seat->pointer.wl_pointer);
            zwp_உள்ளீடு_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        எனில் (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_உள்ளீடு_timestamps_manager_v1_get_touch_timestamps(seat->display->உள்ளீடு_timestamps_manager, seat->touch.wl_touch);
            zwp_உள்ளீடு_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

வெறுமை Wayland_Display_Init_உள்ளீடு_Timestamp_Manager(SDL_VideoData *display)
{
    எனில் (display->உள்ளீடு_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_உள்ளீடு_Timestamp_Listeners(seat);
        }
    }
}

நிலையான வெறுமை handle_pinch_begin(வெறுமை *data, கட்டமைப்பு zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, கட்டமைப்பு wl_surface *surface, uint32_t fingers)
{
    எனில் (!surface) {
        திரும்பு;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    எனில் (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        மாறிலி Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

நிலையான வெறுமை handle_pinch_update(வெறுமை *data, கட்டமைப்பு zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    எனில் (seat->pointer.gesture_focus) {
        மாறிலி Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        மாறிலி தசம s = (தசம)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

நிலையான வெறுமை handle_pinch_end(வெறுமை *data, கட்டமைப்பு zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    எனில் (seat->pointer.gesture_focus) {
        மாறிலி Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = வெற்று;
    }
}

நிலையான மாறிலி கட்டமைப்பு zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

நிலையான வெறுமை Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    எனில் (seat->display->zwp_pointer_gestures) {
        எனில் (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

வெறுமை Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

நிலையான வெறுமை Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    எனில் (seat->display->cursor_shape_manager) {
        எனில் (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            எனில் (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

வெறுமை Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

நிலையான வெறுமை Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    மாறிலி bool send_event = !seat->display->initializing;

    எனில் (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.இலக்கம்_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
நிலையான வெறுமை keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    போது (elapsed >= repeat_info->next_repeat_ns) {
        எனில் (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            மாறிலி Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_சாவி_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->சாவி, repeat_info->scancode, true);
        }
        எனில் (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

நிலையான வெறுமை keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t சாவி, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, மாறிலி எழுத்து *text)
{
    எனில் (!repeat_info->repeat_rate) {
        திரும்பு;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->சாவி = சாவி;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    எனில் (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } இல்லையெனில் {
        repeat_info->text[0] = '\0';
    }
}

நிலையான வெறுமை sync_done_handler(வெறுமை *data, கட்டமைப்பு wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

நிலையான கட்டமைப்பு wl_callback_listener sync_listener = {
    sync_done_handler
};

வெறுமை Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    கட்டமைப்பு wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, வெற்று);
    WAYLAND_wl_display_flush(d->display);
}

முழு Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    மாறிலி முழு display_fd = WAYLAND_wl_display_get_fd(d->display);
    முழு ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    எனில் (!d->text_உள்ளீடு_manager && keyboard_focus && SDL_Text_உள்ளீடு_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        எனில் (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        எனில் (seat->keyboard.repeat.சாவி) {
            மாறிலி Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            மாறிலி Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            எனில் (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    எனில் (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        எனில் (timeoutNS > 0) {
            மாறிலி Uint64 now = SDL_GetTicksNS();
            மாறிலி Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        எனில் (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            எனில் (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        எனில் (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            திரும்பு errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        எனில் (timeoutNS > 0) {
            மாறிலி Uint64 now = SDL_GetTicksNS();
            மாறிலி Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        எனில் (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            எனில் (ret == 0) {
                திரும்பு poll_alarm_set ? 1 : 0;
            } இல்லையெனில் {
                // Pump events on an interrupt or broken pipe to handle the error.
                திரும்பு errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        எனில் (ret == -1) {
            திரும்பு ret;
        }
    }

    // Signal to the caller that there might be an event available.
    திரும்பு 1;
}

வெறுமை Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    மாறிலி முழு display_fd = WAYLAND_wl_display_get_fd(d->display);
    முழு ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    எனில் (!d->text_உள்ளீடு_manager && keyboard_focus && SDL_Text_உள்ளீடு_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    எனில் (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    எனில் (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        எனில் (ret < 0) {
            செல் connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    எனில் (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        எனில் (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            எனில் (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        எனில் (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            செல் connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        எனில் (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            எனில் (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } இல்லையெனில் {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } இல்லையெனில் {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    எனில் (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            எனில் (seat->keyboard.repeat.சாவி) {
                Wayland_SeatSetKeymap(seat);

                மாறிலி Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    எனில் (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

நிலையான வெறுமை pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : வெற்று;

    எனில் (window_data) {
        இரட்டை sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        இரட்டை sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        எனில் (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (இரட்டை)window_data->mask.offset_x;
            sy += (இரட்டை)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        எனில் (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (தசம)sx, (தசம)sy);
        } இல்லையெனில் {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (தசம)sx, (தசம)sy);
        }

        seat->pointer.last_motion.x = (முழு)SDL_floor(sx);
        seat->pointer.last_motion.y = (முழு)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        எனில் (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        எனில் (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            தேர்வு (rc) {
            நிலை SDL_HITTEST_RESIZE_TOPLEFT:
                எனில் ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_இடது)) {
                    rc = SDL_HITTEST_NORMAL;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி) {
                    rc = SDL_HITTEST_RESIZE_இடது;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_இடது) {
                    rc = SDL_HITTEST_RESIZE_உச்சி;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_உச்சி:
                எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி) {
                    rc = SDL_HITTEST_NORMAL;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_TOPRIGHT:
                எனில் ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_வலது)) {
                    rc = SDL_HITTEST_NORMAL;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி) {
                    rc = SDL_HITTEST_RESIZE_வலது;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_வலது) {
                    rc = SDL_HITTEST_RESIZE_உச்சி;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_வலது:
                எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_வலது) {
                    rc = SDL_HITTEST_NORMAL;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                எனில் ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_வலது)) {
                    rc = SDL_HITTEST_NORMAL;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_வலது;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_வலது) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_BOTTOM:
                எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT:
                எனில் ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_இடது)) {
                    rc = SDL_HITTEST_NORMAL;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_இடது;
                } இல்லையெனில் எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_இடது) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                நிறுத்து;
            நிலை SDL_HITTEST_RESIZE_இடது:
                எனில் (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_இடது) {
                    rc = SDL_HITTEST_NORMAL;
                }
                நிறுத்து;
            இயல்பு:
                நிறுத்து;
            }

            எனில் (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

நிலையான வெறுமை pointer_handle_motion(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    மாறிலி Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        எனில் (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } இல்லையெனில் {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

நிலையான வெறுமை pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    எனில் (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        திரும்பு;
    }

    எனில் (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        திரும்பு;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_மொத்தம்;
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

நிலையான வெறுமை pointer_handle_enter(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                 uint32_t serial, கட்டமைப்பு wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    எனில் (!surface) {
        // Enter event for a destroyed surface.
        திரும்பு;
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

    எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

நிலையான வெறுமை pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    எனில் (window) {
        எனில் (seat->pointer.focus) {
            எனில் (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = வெற்று;
                seat->pointer.focus_surface = வெற்று;
                க்கு (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    எனில் (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                மாறிலி bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                எனில் (!--window->pointer_focus_மொத்தம் && had_focus && !window->active_touch_மொத்தம்) {
                    SDL_SetMouseFocus(வெற்று);
                }

                எனில் (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } இல்லையெனில் எனில் (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

நிலையான வெறுமை pointer_handle_leave(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                 uint32_t serial, கட்டமைப்பு wl_surface *surface)
{
    எனில் (!surface) {
        // Leave event for a destroyed surface.
        திரும்பு;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

நிலையான bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    எனில் (seat->pointer.locked_pointer) {
        திரும்பு false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    எனில் (window->hit_test) {
        நிலையான மாறிலி uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_உச்சி_இடது, XDG_TOPLEVEL_RESIZE_EDGE_உச்சி,
            XDG_TOPLEVEL_RESIZE_EDGE_உச்சி_வலது, XDG_TOPLEVEL_RESIZE_EDGE_வலது,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_வலது, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_இடது, XDG_TOPLEVEL_RESIZE_EDGE_இடது
        };

#ifdef HAVE_LIBDECOR_H
        நிலையான மாறிலி uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_உச்சி_இடது, LIBDECOR_RESIZE_EDGE_உச்சி,
            LIBDECOR_RESIZE_EDGE_உச்சி_வலது, LIBDECOR_RESIZE_EDGE_வலது,
            LIBDECOR_RESIZE_EDGE_BOTTOM_வலது, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_இடது, LIBDECOR_RESIZE_EDGE_இடது
        };
#endif

        தேர்வு (window_data->hit_test_result) {
        நிலை SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            எனில் (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                எனில் (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } இல்லையெனில்
#endif
                எனில் (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                எனில் (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            திரும்பு true;

        நிலை SDL_HITTEST_RESIZE_TOPLEFT:
        நிலை SDL_HITTEST_RESIZE_உச்சி:
        நிலை SDL_HITTEST_RESIZE_TOPRIGHT:
        நிலை SDL_HITTEST_RESIZE_வலது:
        நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        நிலை SDL_HITTEST_RESIZE_BOTTOM:
        நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT:
        நிலை SDL_HITTEST_RESIZE_இடது:
#ifdef HAVE_LIBDECOR_H
            எனில் (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                எனில் (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } இல்லையெனில்
#endif
                எனில் (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                எனில் (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            திரும்பு true;

        இயல்பு:
            திரும்பு false;
        }
    }

    திரும்பு false;
}

நிலையான வெறுமை pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    எனில் (window) {
        bool ignore_click = false;

        எனில் (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            எனில் (sdl_button == SDL_BUTTON_இடது && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                திரும்பு; // don't pass this event on to app.
            }
        } இல்லையெனில் {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        எனில் (window->last_focus_event_time_ns) {
            எனில் (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        எனில் (!seat->pointer.relative_pointer) {
            எனில் (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } இல்லையெனில் {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                எனில் (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        எனில் (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

நிலையான வெறுமை pointer_handle_button(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    தேர்வு (button) {
    நிலை BTN_இடது:
        sdl_button = SDL_BUTTON_இடது;
        நிறுத்து;
    நிலை BTN_நடு:
        sdl_button = SDL_BUTTON_நடு;
        நிறுத்து;
    நிலை BTN_வலது:
        sdl_button = SDL_BUTTON_வலது;
        நிறுத்து;
    இயல்பு:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        நிறுத்து;
    }

    எனில் (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    எனில் (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        எனில் (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } இல்லையெனில் {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } இல்லையெனில் {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

நிலையான வெறுமை pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t மதிப்பு)
{
    SDL_WindowData *window = seat->pointer.focus;
    மாறிலி எண்ணிக்கை wl_pointer_axis a = axis;

    எனில் (seat->pointer.focus) {
        தசம x, y;

        தேர்வு (a) {
        நிலை WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (தசம)wl_fixed_to_double(மதிப்பு);
            நிறுத்து;
        நிலை WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (தசம)wl_fixed_to_double(மதிப்பு);
            y = 0;
            நிறுத்து;
        இயல்பு:
            திரும்பு;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

நிலையான வெறுமை pointer_handle_axis_common(SDL_WaylandSeat *seat, எண்ணிக்கை SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t மதிப்பு)
{
    மாறிலி எண்ணிக்கை wl_pointer_axis a = axis;

    எனில் (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        தேர்வு (a) {
        நிலை WL_POINTER_AXIS_VERTICAL_SCROLL:
            தேர்வு (type) {
            நிலை SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                எனில் (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (தசம)wl_fixed_to_double(மதிப்பு);
                நிறுத்து;
            நிலை SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                எனில் (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (தசம)wl_fixed_to_double(மதிப்பு);
                }
                நிறுத்து;
            நிலை SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                எனில் (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (தசம)wl_fixed_to_double(மதிப்பு);
                }
                நிறுத்து;
            }
            நிறுத்து;
        நிலை WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            தேர்வு (type) {
            நிலை SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                எனில் (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (தசம)wl_fixed_to_double(மதிப்பு);
                நிறுத்து;
            நிலை SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                எனில் (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (தசம)wl_fixed_to_double(மதிப்பு);
                }
                நிறுத்து;
            நிலை SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                எனில் (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (தசம)wl_fixed_to_double(மதிப்பு);
                }
                நிறுத்து;
            }
            நிறுத்து;
        }
    }
}

நிலையான வெறுமை pointer_handle_axis(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t மதிப்பு)
{
    SDL_WaylandSeat *seat = data;
    மாறிலி Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    எனில் (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, மதிப்பு);
    } இல்லையெனில் {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, மதிப்பு);
    }
}

நிலையான வெறுமை pointer_handle_axis_relative_direction(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    தேர்வு (axis_relative_direction) {
    நிலை WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        நிறுத்து;
    நிலை WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        நிறுத்து;
    }
}

நிலையான வெறுமை pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    எனில் (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        இரட்டை dx;
        இரட்டை dy;
        எனில் (mouse->உள்ளீடு_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } இல்லையெனில் {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (தசம)dx, (தசம)dy);
    }
}

நிலையான வெறுமை pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    தசம x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    தேர்வு (seat->pointer.pending_frame.axis.x_axis_type) {
    நிலை SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        நிறுத்து;
    நிலை SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        நிறுத்து;
    நிலை SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        நிறுத்து;
    இயல்பு:
        x = 0.0f;
        நிறுத்து;
    }

    தேர்வு (seat->pointer.pending_frame.axis.y_axis_type) {
    நிலை SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        நிறுத்து;
    நிலை SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        நிறுத்து;
    நிலை SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        நிறுத்து;
    இயல்பு:
        y = 0.0f;
        நிறுத்து;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

நிலையான வெறுமை pointer_handle_frame(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    எனில் (seat->pointer.pending_frame.enter_surface) {
        எனில் (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            எனில் (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = வெற்று;
                seat->pointer.pending_frame.leave_surface = வெற்று;
            } இல்லையெனில் {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = வெற்று;
            }
        }

        எனில் (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    எனில் (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    எனில் (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    க்கு (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        மாறிலி Uint32 mask = SDL_BUTTON_MASK(i);
        எனில் (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        எனில் (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    எனில் (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    எனில் (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

நிலையான வெறுமை pointer_handle_axis_source(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

நிலையான வெறுமை pointer_handle_axis_stop(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

நிலையான வெறுமை pointer_handle_axis_discrete(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

நிலையான வெறுமை pointer_handle_axis_value120(வெறுமை *data, கட்டமைப்பு wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

நிலையான வெறுமை pointer_handle_warp(வெறுமை *data, கட்டமைப்பு wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

நிலையான மாறிலி கட்டமைப்பு wl_pointer_listener pointer_listener = {
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

நிலையான வெறுமை relative_pointer_handle_relative_motion(வெறுமை *data,
                                                    கட்டமைப்பு zwp_relative_pointer_v1 *pointer,
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

    எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } இல்லையெனில் {
        pointer_dispatch_relative_motion(seat);
    }
}

நிலையான மாறிலி கட்டமைப்பு zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

நிலையான வெறுமை locked_pointer_locked(வெறுமை *data, கட்டமைப்பு zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

நிலையான வெறுமை locked_pointer_unlocked(வெறுமை *data, கட்டமைப்பு zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

நிலையான மாறிலி கட்டமைப்பு zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

நிலையான வெறுமை confined_pointer_confined(வெறுமை *data, கட்டமைப்பு zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

நிலையான வெறுமை confined_pointer_unconfined(வெறுமை *data, கட்டமைப்பு zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

நிலையான மாறிலி கட்டமைப்பு zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

நிலையான வெறுமை touch_handler_down(வெறுமை *data, கட்டமைப்பு wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, கட்டமைப்பு wl_surface *surface,
                               முழு id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    எனில் (!surface) {
        திரும்பு;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    எனில் (window_data && window_data->surface == surface) {
        தசம x, y;

        எனில் (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } இல்லையெனில் {
            x = (தசம)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        எனில் (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } இல்லையெனில் {
            y = (தசம)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_மொத்தம்;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

நிலையான வெறுமை touch_handler_up(வெறுமை *data, கட்டமைப்பு wl_touch *touch, uint32_t serial, uint32_t timestamp, முழு id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    கட்டமைப்பு wl_surface *surface = வெற்று;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    எனில் (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        எனில் (window_data && window_data->surface == surface) {
            மாறிலி தசம x = (தசம)wl_fixed_to_double(fx) / window_data->current.logical_width;
            மாறிலி தசம y = (தசம)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_மொத்தம்;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            எனில் (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_மொத்தம் &&
                !window_data->pointer_focus_மொத்தம் && !window_data->active_touch_மொத்தம்) {
                SDL_SetMouseFocus(வெற்று);
            }
        }
    }
}

நிலையான வெறுமை touch_handler_motion(வெறுமை *data, கட்டமைப்பு wl_touch *touch, uint32_t timestamp, முழு id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    கட்டமைப்பு wl_surface *surface = வெற்று;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    எனில் (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        எனில் (window_data && window_data->surface == surface) {
            மாறிலி தசம x = (தசம)wl_fixed_to_double(fx) / window_data->current.logical_width;
            மாறிலி தசம y = (தசம)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

நிலையான வெறுமை touch_handler_frame(வெறுமை *data, கட்டமைப்பு wl_touch *touch)
{
}

நிலையான வெறுமை touch_handler_cancel(வெறுமை *data, கட்டமைப்பு wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

நிலையான வெறுமை touch_handler_shape(வெறுமை *data, கட்டமைப்பு wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

நிலையான வெறுமை touch_handler_orientation(வெறுமை *data, கட்டமைப்பு wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

நிலையான மாறிலி கட்டமைப்பு wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#எனில் !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
நிலையான size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t சாவி, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    எனில் (!masks_out || !masks_size) {
        திரும்பு 0;
    }

    // Level 0 is always unmodified, so early out.
    எனில் (level == 0) {
        *masks_out = 0;
        திரும்பு 1;
    }

    size_t mask_idx = 0;
    மாறிலி xkb_mod_mask_t keymod_masks[] = {
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
    மாறிலி xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    மாறிலி xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    க்கு (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        எனில் (WAYLAND_xkb_state_சாவி_get_level(seat->keyboard.xkb.state, சாவி, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            எனில் (++mask_idx == masks_size) {
                நிறுத்து;
            }
        }
    }

    திரும்பு mask_idx;
}
#endif

நிலையான வெறுமை Wayland_KeymapIterator(கட்டமைப்பு xkb_keymap *keymap, xkb_keycode_t சாவி, வெறுமை *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    மாறிலி xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    மாறிலி xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    எனில் (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, சாவி - 8);
    }

    க்கு (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.இலக்கம்_layouts; ++layout) {
        மாறிலி xkb_level_index_t இலக்கம்_levels = WAYLAND_xkb_keymap_இலக்கம்_levels_for_சாவி(seat->keyboard.xkb.keymap, சாவி, layout);
        க்கு (xkb_level_index_t level = 0; level < இலக்கம்_levels; ++level) {
            எனில் (WAYLAND_xkb_keymap_சாவி_get_syms_by_level(seat->keyboard.xkb.keymap, சாவி, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                எனில் (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_சாவி_Sym(syms[0], சாவி);
                    எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
                        தொடர்;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#எனில் SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                மாறிலி size_t இலக்கம்_masks = WAYLAND_xkb_keymap_சாவி_get_mods_for_level(seat->keyboard.xkb.keymap, சாவி, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#இல்லையெனில்
                மாறிலி size_t இலக்கம்_masks = xkb_legacy_get_mods_for_level(seat, சாவி, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                க்கு (size_t mask = 0; mask < இலக்கம்_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    எனில் ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        தொடர்;
                    }

                    மாறிலி SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_சாவி_Code_From_சாவி_Sym(syms[0], சாவி, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    எனில் (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        எனில் (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_சாவி *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, அளவு(Wayland_Reserved_சாவி));
                        எனில் (res) {
                            res->scancode = scancode;
                            res->சாவி = சாவி - 8;
                        }
                    }

                    எனில் (!keycode) {
                        தேர்வு (scancode) {
                        நிலை SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            நிறுத்து;
                        நிலை SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            நிறுத்து;
                        நிலை SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            நிறுத்து;
                        நிலை SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            நிறுத்து;
                        இயல்பு:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            நிறுத்து;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

நிலையான வெறுமை keyboard_handle_keymap(வெறுமை *data, கட்டமைப்பு wl_keyboard *keyboard,
                                   uint32_t format, முழு fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    எழுத்து *map_str;

    எனில் (!data) {
        close(fd);
        திரும்பு;
    }

    எனில் (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        திரும்பு;
    }

    map_str = mmap(வெற்று, size, PROT_READ, MAP_PRIVATE, fd, 0);
    எனில் (map_str == MAP_FAILED) {
        close(fd);
        திரும்பு;
    }

    எனில் (seat->keyboard.xkb.keymap != வெற்று) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = வெற்று;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    எனில் (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        திரும்பு;
    }

    // Clear the old layouts.
    க்கு (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.இலக்கம்_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = வெற்று;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.இலக்கம்_layouts = 0;

#எனில் SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.இலக்கம்_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_இலக்கம்);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#இல்லையெனில்
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.இலக்கம்_mask = 1 << GET_MOD_INDEX(இலக்கம்_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    எனில் (seat->keyboard.xkb.state != வெற்று) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = வெற்று;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    எனில் (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = வெற்று;
        திரும்பு;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == வெற்று;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.இலக்கம்_layouts = WAYLAND_xkb_keymap_இலக்கம்_layouts(seat->keyboard.xkb.keymap);
    எனில் (seat->keyboard.xkb.இலக்கம்_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.இலக்கம்_layouts, அளவு(SDL_Keymap *));
        எனில் (!seat->keyboard.sdl_keymap) {
            திரும்பு;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        க்கு (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.இலக்கம்_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            எனில் (!seat->keyboard.sdl_keymap[i]) {
                க்கு (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = வெற்று;
                திரும்பு;
            }
        }

        WAYLAND_xkb_keymap_சாவி_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.இலக்கம்_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    மாறிலி எழுத்து *locale = SDL_getenv("LC_ALL");
    எனில் (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        எனில் (!locale) {
            locale = SDL_getenv("LANG");
            எனில் (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    எனில் (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        எனில் (seat->keyboard.xkb.compose_table != வெற்று) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = வெற்று;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        எனில் (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            எனில் (seat->keyboard.xkb.compose_state != வெற்று) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = வெற்று;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            எனில் (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = வெற்று;
            }
        }
    } இல்லையெனில் எனில் (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
நிலையான SDL_Scancode Wayland_Get_Scancode_For_சாவி(SDL_WaylandSeat *seat, Uint32 சாவி, மாறிலி xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    எனில் (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, சாவி);

        // No table entry? Check the reserved list.
        எனில் (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_சாவி *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                எனில் (i->சாவி == சாவி) {
                    திரும்பு i->scancode;
                }
            }
        }
    } இல்லையெனில் {
        மாறிலி xkb_keysym_t *keysym;
        எனில் (WAYLAND_xkb_state_சாவி_get_syms(seat->keyboard.xkb.state, சாவி + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_சாவி_Sym(keysym[0], சாவி + 8);
            எனில் (syms) {
                *syms = keysym;
            }
        }
    }

    திரும்பு scancode;
}

நிலையான வெறுமை Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool சாவி_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    எனில் (!சாவி_pressed) {
        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } இல்லையெனில் {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } இல்லையெனில் {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } இல்லையெனில் {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } இல்லையெனில் {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } இல்லையெனில் {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        எனில் (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            எனில் (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } இல்லையெனில் {
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
    மாறிலி xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        எனில் (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } இல்லையெனில் எனில் (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        எனில் (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } இல்லையெனில் எனில் (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        எனில் (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } இல்லையெனில் எனில் (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        எனில் (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } இல்லையெனில் எனில் (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    எனில் (xkb_locked_modifiers & seat->keyboard.xkb.இலக்கம்_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_இலக்கம்;
    } இல்லையெனில் {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_இலக்கம்;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

நிலையான வெறுமை Wayland_Handle_Modifier_சாவிகள்(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    மாறிலி SDL_Keycode keycode = SDL_Get_சாவி_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    தேர்வு (keycode) {
    நிலை SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        நிறுத்து;
    நிலை SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        நிறுத்து;
    நிலை SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        நிறுத்து;
    நிலை SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        நிறுத்து;
    நிலை SDLK_LALT:
        mod = SDL_KMOD_LALT;
        நிறுத்து;
    நிலை SDLK_RALT:
        mod = SDL_KMOD_RALT;
        நிறுத்து;
    நிலை SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        நிறுத்து;
    நிலை SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        நிறுத்து;
    நிலை SDLK_MODE:
        mod = SDL_KMOD_MODE;
        நிறுத்து;
    நிலை SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        நிறுத்து;
    இயல்பு:
        திரும்பு;
    }

    எனில் (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } இல்லையெனில் {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

நிலையான வெறுமை keyboard_handle_enter(வெறுமை *data, கட்டமைப்பு wl_keyboard *keyboard,
                                  uint32_t serial, கட்டமைப்பு wl_surface *surface,
                                  கட்டமைப்பு wl_array *சாவிகள்)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *சாவி;

    எனில் (!surface) {
        // Enter event for a destroyed surface.
        திரும்பு;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    எனில் (!window) {
        // Not a surface owned by SDL.
        திரும்பு;
    }

    ++window->keyboard_focus_மொத்தம்;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_உள்ளீடு(seat);

#ifdef SDL_USE_IME
    எனில் (!seat->text_உள்ளீடு.zwp_text_உள்ளீடு) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (சாவி, சாவிகள்) {
        மாறிலி SDL_Scancode scancode = Wayland_Get_Scancode_For_சாவி(seat, *சாவி, வெற்று);
        எனில் (scancode != SDL_SCANCODE_UNKNOWN) {
            மாறிலி SDL_Keycode keycode = SDL_Get_சாவி_From_Scancode(scancode, SDL_KMOD_NONE, false);

            தேர்வு (keycode) {
            நிலை SDLK_LSHIFT:
            நிலை SDLK_RSHIFT:
            நிலை SDLK_LCTRL:
            நிலை SDLK_RCTRL:
            நிலை SDLK_LALT:
            நிலை SDLK_RALT:
            நிலை SDLK_LGUI:
            நிலை SDLK_RGUI:
            நிலை SDLK_MODE:
            நிலை SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_சாவிகள்(seat, scancode, true);
                SDL_Send_Keyboard_சாவி_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *சாவி, scancode, true);
                நிறுத்து;
            இயல்பு:
                நிறுத்து;
            }
        }
    }
}

நிலையான வெறுமை keyboard_handle_leave(வெறுமை *data, கட்டமைப்பு wl_keyboard *keyboard,
                                  uint32_t serial, கட்டமைப்பு wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    எனில் (!surface) {
        // Leave event for a destroyed surface.
        திரும்பு;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    எனில் (!window) {
        // Not a surface owned by SDL.
        திரும்பு;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.சாவி = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    போது (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    மாறிலி bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = வெற்று;
    --window->keyboard_focus_மொத்தம்;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    எனில் (!window->keyboard_focus_மொத்தம் && had_focus) {
        SDL_SetKeyboardFocus(வெற்று);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_உள்ளீடு(seat);

#ifdef SDL_USE_IME
    எனில் (!seat->text_உள்ளீடு.zwp_text_உள்ளீடு && !window->keyboard_focus_மொத்தம்) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    எனில் (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_மொத்தம் && !window->active_touch_மொத்தம்) {
        SDL_SetMouseFocus(வெற்று);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, வெற்று);
}

நிலையான bool keyboard_உள்ளீடு_get_text(எழுத்து text[8], மாறிலி SDL_WaylandSeat *seat, uint32_t சாவி, bool down, bool *handled_by_ime)
{
    மாறிலி xkb_keysym_t *syms;
    xkb_keysym_t sym;

    எனில் (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        திரும்பு false;
    }

    // TODO: Can this happen?
    எனில் (WAYLAND_xkb_state_சாவி_get_syms(seat->keyboard.xkb.state, சாவி + 8, &syms) != 1) {
        திரும்பு false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    எனில் (SDL_IME_Process_சாவி_Event(sym, சாவி + 8, down)) {
        எனில் (handled_by_ime) {
            *handled_by_ime = true;
        }
        திரும்பு true;
    }
#endif

    எனில் (!down) {
        திரும்பு false;
    }

    எனில் (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        தேர்வு (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        நிலை XKB_COMPOSE_COMPOSING:
            எனில் (handled_by_ime) {
                *handled_by_ime = true;
            }
            திரும்பு true;
        நிலை XKB_COMPOSE_CANCELLED:
        இயல்பு:
            sym = XKB_சாவி_No_குறியீடு;
            நிறுத்து;
        நிலை XKB_COMPOSE_NOTHING:
            நிறுத்து;
        நிலை XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            நிறுத்து;
        }
    }

    திரும்பு WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

நிலையான வெறுமை keyboard_handle_சாவி(வெறுமை *data, கட்டமைப்பு wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t சாவி,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    எண்ணிக்கை wl_keyboard_சாவி_state state = state_w;
    எழுத்து text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    மாறிலி Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    எனில் (state == WL_KEYBOARD_சாவி_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        எனில் (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_சாவி_repeats(seat->keyboard.xkb.keymap, சாவி + 8)) {
            திரும்பு;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_சாவி_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    எனில் (state == WL_KEYBOARD_சாவி_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        எனில் (keyboard_focus && SDL_Text_உள்ளீடு_Active(keyboard_focus)) {
            has_text = keyboard_உள்ளீடு_get_text(text, seat, சாவி, true, &handled_by_ime);
        }
    } இல்லையெனில் {
        எனில் (சாவி == seat->keyboard.repeat.சாவி) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            மாறிலி Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.சாவி = 0;
        }
        keyboard_உள்ளீடு_get_text(text, seat, சாவி, false, &handled_by_ime);
    }

    மாறிலி xkb_keysym_t *syms = வெற்று;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_சாவி(seat, சாவி, &syms);
    Wayland_Handle_Modifier_சாவிகள்(seat, scancode, state == WL_KEYBOARD_சாவி_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    எனில் (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        மாறிலி SDL_Keycode keycode = (SDL_Keycode)SDL_சாவி_Sym_To_Ucs4(syms[0]);
        எனில் (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            எனில் (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_சாவி_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, சாவி, scancode, state == WL_KEYBOARD_சாவி_STATE_PRESSED);

    எனில் (state == WL_KEYBOARD_சாவி_STATE_PRESSED) {
        எனில் (handled_by_ime) {
            has_text = false;
        }
        எனில் (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        எனில் (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_சாவி_repeats(seat->keyboard.xkb.keymap, சாவி + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, சாவி, time, timestamp_ns, scancode, has_text ? text : வெற்று);
        }
    }
}

நிலையான வெறுமை keyboard_handle_modifiers(வெறுமை *data, கட்டமைப்பு wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    மாறிலி uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    எனில் (!seat->keyboard.xkb.state) {
        திரும்பு;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    எனில் (seat->keyboard.repeat.சாவி) {
        எழுத்து text[8];

        எனில் (keyboard_உள்ளீடு_get_text(text, seat, seat->keyboard.repeat.சாவி, true, வெற்று)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    எனில் (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        எனில் (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

நிலையான வெறுமை keyboard_handle_repeat_info(வெறுமை *data, கட்டமைப்பு wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    எனில் (!rate) {
        seat->keyboard.repeat.சாவி = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_சாவி,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

நிலையான வெறுமை Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    எனில் (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    எனில் (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = வெற்று;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    எனில் (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    எனில் (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    எனில் (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    எனில் (seat->pointer.timestamps) {
        zwp_உள்ளீடு_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    எனில் (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    எனில் (seat->pointer.wl_pointer) {
        எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } இல்லையெனில் {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

நிலையான வெறுமை Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    எனில் (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    எனில் (seat->keyboard.sdl_keymap) {
        எனில் (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.இலக்கம்_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        க்கு (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.இலக்கம்_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = வெற்று;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    எனில் (seat->keyboard.சாவி_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.சாவி_inhibitor);
    }

    எனில் (seat->keyboard.timestamps) {
        zwp_உள்ளீடு_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    எனில் (seat->keyboard.wl_keyboard) {
        எனில் (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } இல்லையெனில் {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    எனில் (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    எனில் (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    எனில் (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    எனில் (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

நிலையான வெறுமை Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    எனில் (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    எனில் (seat->touch.timestamps) {
        zwp_உள்ளீடு_timestamps_v1_destroy(seat->touch.timestamps);
    }

    எனில் (seat->touch.wl_touch) {
        எனில் (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } இல்லையெனில் {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

நிலையான வெறுமை seat_handle_capabilities(வெறுமை *data, கட்டமைப்பு wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    எழுத்து name_fmt[256];

    எனில் ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        எனில் (seat->name) {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } இல்லையெனில் {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } இல்லையெனில் எனில் (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    எனில் ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        எனில் (seat->name) {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } இல்லையெனில் {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } இல்லையெனில் எனில் (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    எனில் ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        எனில் (seat->name) {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } இல்லையெனில் {
            SDL_snprintf(name_fmt, அளவு(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } இல்லையெனில் எனில் (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_உள்ளீடு_Timestamp_Listeners(seat);
}

நிலையான வெறுமை seat_handle_name(வெறுமை *data, கட்டமைப்பு wl_seat *wl_seat, மாறிலி எழுத்து *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    எனில் (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

நிலையான வெறுமை data_offer_handle_offer(வெறுமை *data, கட்டமைப்பு wl_data_offer *wl_data_offer,
                                    மாறிலி எழுத்து *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

நிலையான வெறுமை data_offer_handle_source_actions(வெறுமை *data, கட்டமைப்பு wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

நிலையான வெறுமை data_offer_handle_actions(வெறுமை *data, கட்டமைப்பு wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

நிலையான மாறிலி கட்டமைப்பு wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

நிலையான வெறுமை primary_selection_offer_handle_offer(வெறுமை *data, கட்டமைப்பு zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 மாறிலி எழுத்து *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

நிலையான மாறிலி கட்டமைப்பு zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

நிலையான வெறுமை data_device_handle_data_offer(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device,
                                          கட்டமைப்பு wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, அளவு(*data_offer));
    எனில் (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id) : -1));
    }
}

நிலையான வெறுமை data_device_handle_enter(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device,
                                     uint32_t serial, கட்டமைப்பு wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, கட்டமைப்பு wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : வெற்று;
    data_device->has_mime_file = false;
    data_device->text_mime_type = வெற்று;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    எனில் (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    எனில் (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        எனில் (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        எனில் (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        எனில் (!data_device->has_mime_file) {
            size_t mime_மொத்தம் = 0;
            மாறிலி எழுத்து *மாறிலி *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_மொத்தம்);
            க்கு (size_t i = 0; i < mime_மொத்தம்; ++i) {
                எனில் (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    நிறுத்து;
                }
            }
        }

        எனில் (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            எனில் (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            இரட்டை dx = wl_fixed_to_double(x);
            இரட்டை dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            எனில் (surface == window->mask.surface) {
                dx += (இரட்டை)window->mask.offset_x;
                dy += (இரட்டை)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (தசம)dx, (தசம)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } இல்லையெனில் {
            // Decline the offer.
            wl_data_offer_accept(id, serial, வெற்று);
            எனில் (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } இல்லையெனில் {
        data_device->dnd_window = வெற்று;
        data_device->dnd_surface = வெற்று;

        // Decline the offer.
        எனில் (id) {
            wl_data_offer_accept(id, serial, வெற்று);
            எனில் (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

நிலையான வெறுமை data_device_handle_leave(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    எனில் (data_device->drag_offer) {
        எனில் (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } இல்லையெனில் {
            SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = வெற்று;
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = வெற்று;
}

நிலையான வெறுமை data_device_handle_motion(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    எனில் (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        இரட்டை dx = wl_fixed_to_double(x);
        இரட்டை dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        எனில் (data_device->dnd_surface == window_data->mask.surface) {
            dx += (இரட்டை)window_data->mask.offset_x;
            dy += (இரட்டை)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (தசம)dx, (தசம)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

நிலையான வெறுமை drop_cleanup_handler(வெறுமை *data, கட்டமைப்பு wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

நிலையான மாறிலி கட்டமைப்பு wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

நிலையான வெறுமை drop_dispatch_handler(வெறுமை *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    எனில் (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        எனில் (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            வெறுமை *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            எனில் (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                எனில் (dbus) {
                    முழு path_மொத்தம் = 0;
                    எழுத்து **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_மொத்தம்);
                    // If dropped files contain a directory the list is empty
                    எனில் (paths && path_மொத்தம் > 0) {
                        க்கு (முழு i = 0; i < path_மொத்தம்; i++) {
                            SDL_SendDropFile(drop->dnd_window, வெற்று, paths[i]);
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
        எனில் (!drop_handled) {
            எனில் (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                வெறுமை *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                எனில் (buffer) {
                    எழுத்து *saveptr = வெற்று;
                    எழுத்து *token = SDL_strtok_r((எழுத்து *)buffer, "\r\n", &saveptr);
                    போது (token) {
                        எனில் (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, வெற்று, token);
                        }
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } இல்லையெனில் எனில் (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                வெறுமை *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                எனில் (buffer) {
                    எழுத்து *saveptr = வெற்று;
                    எழுத்து *token = SDL_strtok_r((எழுத்து *)buffer, "\r\n", &saveptr);
                    போது (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(வெற்று, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        எனில் (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = வெற்று;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

நிலையான வெறுமை data_device_handle_drop(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    எனில் (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, அளவு(Wayland_DropData));
        எனில் (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_செருகு(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } இல்லையெனில் {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } இல்லையெனில் {
        SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = வெற்று;
}

நிலையான வெறுமை data_device_handle_selection(வெறுமை *data, கட்டமைப்பு wl_data_device *wl_data_device,
                                         கட்டமைப்பு wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = வெற்று;

    எனில் (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

நிலையான மாறிலி கட்டமைப்பு wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

நிலையான வெறுமை primary_selection_device_handle_offer(வெறுமை *data, கட்டமைப்பு zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  கட்டமைப்பு zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, அளவு(*primary_selection_offer));
    எனில் (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id) : -1));
}

நிலையான வெறுமை primary_selection_device_handle_selection(வெறுமை *data, கட்டமைப்பு zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      கட்டமைப்பு zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = வெற்று;

    எனில் (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    எனில் (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((கட்டமைப்பு wl_proxy *)id) : -1));
}

நிலையான மாறிலி கட்டமைப்பு zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

நிலையான வெறுமை text_உள்ளீடு_enter(வெறுமை *data,
                             கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                             கட்டமைப்பு wl_surface *surface)
{
    // No-op
}

நிலையான வெறுமை text_உள்ளீடு_leave(வெறுமை *data,
                             கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                             கட்டமைப்பு wl_surface *surface)
{
    // No-op
}

நிலையான வெறுமை text_உள்ளீடு_preedit_string(வெறுமை *data,
                                      கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                                      மாறிலி எழுத்து *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_உள்ளீடு.has_preedit = true;
    எனில் (text) {
        முழு cursor_begin_utf8 = cursor_begin >= 0 ? (முழு)SDL_utf8strnlen(text, cursor_begin) : -1;
        முழு cursor_end_utf8 = cursor_end >= 0 ? (முழு)SDL_utf8strnlen(text, cursor_end) : -1;
        முழு cursor_size_utf8;
        எனில் (cursor_end_utf8 >= 0) {
            எனில் (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } இல்லையெனில் {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } இல்லையெனில் {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } இல்லையெனில் {
        SDL_SendEditingText("", 0, 0);
    }
}

நிலையான வெறுமை text_உள்ளீடு_commit_string(வெறுமை *data,
                                     கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                                     மாறிலி எழுத்து *text)
{
    SDL_SendKeyboardText(text);
}

நிலையான வெறுமை text_உள்ளீடு_delete_surrounding_text(வெறுமை *data,
                                               கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

நிலையான வெறுமை text_உள்ளீடு_done(வெறுமை *data,
                            கட்டமைப்பு zwp_text_உள்ளீடு_v3 *zwp_text_உள்ளீடு_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    எனில் (!seat->text_உள்ளீடு.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_உள்ளீடு.has_preedit = false;
}

நிலையான மாறிலி கட்டமைப்பு zwp_text_உள்ளீடு_v3_listener text_உள்ளீடு_listener = {
    text_உள்ளீடு_enter,
    text_உள்ளீடு_leave,
    text_உள்ளீடு_preedit_string,
    text_உள்ளீடு_commit_string,
    text_உள்ளீடு_delete_surrounding_text,
    text_உள்ளீடு_done
};

நிலையான வெறுமை Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    எனில் (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        எனில் (dbus) {
            மாறிலி எழுத்து *id = dbus->bus_get_unique_name(dbus->session_conn);
            எனில் (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    எனில் (!data_device->id_str)
#endif
    {
        எழுத்து id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, அளவு(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

நிலையான வெறுமை Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    எனில் (!seat->display->data_device_manager) {
        திரும்பு;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, அளவு(*data_device));
    எனில் (!data_device) {
        திரும்பு;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    எனில் (!data_device->data_device) {
        SDL_free(data_device);
        திரும்பு;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

வெறுமை Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

நிலையான வெறுமை Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    எனில் (!seat->display->primary_selection_device_manager) {
        திரும்பு;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, அளவு(*primary_selection_device));
    எனில் (!primary_selection_device) {
        திரும்பு;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    எனில் (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } இல்லையெனில் {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

வெறுமை Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

நிலையான வெறுமை Wayland_Seat_Create_Text_உள்ளீடு(SDL_WaylandSeat *seat)
{
    எனில் (seat->display->text_உள்ளீடு_manager) {
        seat->text_உள்ளீடு.zwp_text_உள்ளீடு = zwp_text_உள்ளீடு_manager_v3_get_text_உள்ளீடு(seat->display->text_உள்ளீடு_manager, seat->wl_seat);

        எனில் (seat->text_உள்ளீடு.zwp_text_உள்ளீடு) {
            zwp_text_உள்ளீடு_v3_set_user_data(seat->text_உள்ளீடு.zwp_text_உள்ளீடு, seat);
            zwp_text_உள்ளீடு_v3_add_listener(seat->text_உள்ளீடு.zwp_text_உள்ளீடு,
                                           &text_உள்ளீடு_listener, seat);
        }
    }
}

வெறுமை Wayland_Display_Init_Text_உள்ளீடு_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_உள்ளீடு(seat);
    }
}

// Pen/Tablet support...
நிலையான வெறுமை tablet_tool_handle_type(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    தேர்வு (type) {
        #define CASE(typ) நிலை ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; திரும்பு
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        இயல்பு: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

நிலையான வெறுமை tablet_tool_handle_hardware_serial(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

நிலையான வெறுமை tablet_tool_handle_hardware_id_wacom(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

நிலையான வெறுமை tablet_tool_handle_capability(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    தேர்வு (capability) {
        #define CASE(wltyp,sdltyp) நிலை ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; திரும்பு
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        இயல்பு: நிறுத்து;  // unsupported here.
    }
}

நிலையான வெறுமை tablet_tool_handle_done(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    எனில் (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : வெற்று;
        sdltool->instance_id = SDL_AddPenDevice(0, வெற்று, window, &sdltool->info, sdltool, false);
    }
}

நிலையான வெறுமை tablet_tool_handle_removed(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    எனில் (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : வெற்று;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

நிலையான வெறுமை tablet_tool_handle_proximity_in(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t serial, கட்டமைப்பு zwp_tablet_v2 *tablet, கட்டமைப்பு wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : வெற்று;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : வெற்று;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

நிலையான வெறுமை tablet_tool_handle_proximity_out(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

நிலையான வெறுமை tablet_tool_handle_down(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

நிலையான வெறுமை tablet_tool_handle_up(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

நிலையான வெறுமை tablet_tool_handle_motion(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    எனில் (windowdata) {
        sdltool->frame.x = (தசம)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (தசம)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

நிலையான வெறுமை tablet_tool_handle_pressure(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((தசம) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    எனில் (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

நிலையான வெறுமை tablet_tool_handle_distance(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((தசம) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    எனில் (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

நிலையான வெறுமை tablet_tool_handle_tilt(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (தசம)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (தசம)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

நிலையான வெறுமை tablet_tool_handle_button(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    முழு sdlbutton;

    தேர்வு (button) {
    நிலை BTN_STYLUS:
        sdlbutton = 1;
        நிறுத்து;
    நிலை BTN_STYLUS2:
        sdlbutton = 2;
        நிறுத்து;
    நிலை BTN_STYLUS3:
        sdlbutton = 3;
        நிறுத்து;
    இயல்பு:
        திரும்பு;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

நிலையான வெறுமை tablet_tool_handle_rotation(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    மாறிலி தசம rotation = (தசம)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

நிலையான வெறுமை tablet_tool_handle_slider(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

நிலையான வெறுமை tablet_tool_handle_wheel(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

நிலையான வெறுமை tablet_tool_handle_frame(வெறுமை *data, கட்டமைப்பு zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    மாறிலி SDL_PenID instance_id = sdltool->instance_id;
    எனில் (!instance_id) {
        திரும்பு;  // Not a pen we report on.
    }

    மாறிலி Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : வெற்று;
    மாறிலி bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    எனில் (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    எனில் (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        எனில் (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } இல்லையெனில் {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } இல்லையெனில் {
        எனில் (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        எனில் (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    க்கு (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_மொத்தம்; i++) {
        எனில் (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    க்கு (முழு i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        மாறிலி முழு state = sdltool->frame.buttons[i];
        எனில் (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    எனில் (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = வெற்று;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

நிலையான மாறிலி கட்டமைப்பு zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


நிலையான வெறுமை tablet_seat_handle_tablet_added(வெறுமை *data, கட்டமைப்பு zwp_tablet_seat_v2 *zwp_tablet_seat_v2, கட்டமைப்பு zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

நிலையான வெறுமை tablet_seat_handle_tool_added(வெறுமை *data, கட்டமைப்பு zwp_tablet_seat_v2 *zwp_tablet_seat_v2, கட்டமைப்பு zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, அளவு(*sdltool));

    எனில் (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.இலக்கம்_buttons = -1;

        எனில் (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_செருகு(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

நிலையான வெறுமை tablet_seat_handle_pad_added(வெறுமை *data, கட்டமைப்பு zwp_tablet_seat_v2 *zwp_tablet_seat_v2, கட்டமைப்பு zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

நிலையான மாறிலி கட்டமைப்பு zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

நிலையான வெறுமை Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

வெறுமை Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

நிலையான வெறுமை Wayland_remove_all_pens_callback(SDL_PenID instance_id, வெறுமை *handle, வெறுமை *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

நிலையான வெறுமை Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    எனில் (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } இல்லையெனில் {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, வெற்று);
    }

    எனில் (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = வெற்று;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

வெறுமை Wayland_DisplayCreateSeat(SDL_VideoData *display, கட்டமைப்பு wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, அளவு(SDL_WaylandSeat));
    எனில் (!seat) {
        திரும்பு;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_செருகு(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_உள்ளீடு(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    எனில் (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

வெறுமை Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        எனில் (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        எனில் (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = வெற்று;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            எனில் (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            எனில் (tool->focus == window) {
                tool->focus = வெற்று;
                Wayland_TabletToolUpdateCursor(tool);
                எனில் (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            எனில் (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                எனில் (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

வெறுமை Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    எனில் (!seat) {
        திரும்பு;
    }

    SDL_free(seat->name);

    எனில் (seat->data_device) {
        எனில் (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        எனில் (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        எனில் (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            எனில் (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        எனில் (seat->data_device->data_device) {
            எனில் (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } இல்லையெனில் {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    எனில் (seat->primary_selection_device) {
        எனில் (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        எனில் (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        எனில் (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    எனில் (seat->text_உள்ளீடு.zwp_text_உள்ளீடு) {
        zwp_text_உள்ளீடு_v3_destroy(seat->text_உள்ளீடு.zwp_text_உள்ளீடு);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    எனில் (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } இல்லையெனில் {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

நிலையான வெறுமை Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    எனில் (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        எனில் (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            எனில் (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                எனில் (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } இல்லையெனில் {
                    relative_focus = seat->pointer.focus->keyboard_focus_மொத்தம் != 0;
                }
            } இல்லையெனில் {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        எனில் (relative_focus) {
            எனில் (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } இல்லையெனில் எனில் (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = வெற்று;
        }
    }
}

நிலையான வெறுமை Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    எனில் (display->சாவி_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        எனில் (seat->keyboard.சாவி_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.சாவி_inhibitor);
            seat->keyboard.சாவி_inhibitor = வெற்று;
        }

        எனில் (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            எனில் (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                எனில் (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.சாவி_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->சாவி_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

வெறுமை Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    எனில் (display->pointer_constraints) {
        எனில் (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = வெற்று;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        எனில் (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            எனில் (seat->pointer.relative_pointer) {
                எனில் (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    எனில் (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = வெற்று;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, வெற்று,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                திரும்பு;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            எனில் (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = வெற்று;
            }

            SDL_WindowData *w = seat->pointer.focus;
            எனில் (!w) {
                திரும்பு;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            எனில் (!(window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                திரும்பு;
            }

            கட்டமைப்பு wl_region *confine_rect = வெற்று;
            எனில் (!SDL_RectEmpty(&window->mouse_rect)) {
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
                எனில் (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    முழு closest_x = seat->pointer.last_motion.x;
                    முழு closest_y = seat->pointer.last_motion.y;

                    எனில் (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } இல்லையெனில் எனில் (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    எனில் (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } இல்லையெனில் எனில் (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            எனில் (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                எனில் (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } இல்லையெனில் {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                வெற்று,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                எனில் (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

வெறுமை Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        எனில் (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

வெறுமை Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        எனில் (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

வெறுமை Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    எனில் (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
