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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ "../../core/unix/SDL_poll.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_scancode_tables_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keysym_to_keycode_c.h"
#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_system_theme.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandwindow.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandmouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandclipboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandkeyboard.h"

#ଅନ୍ତର୍ଭାଵ "pointer-constraints-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "relative-pointer-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "xdg-shell-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "text-input-unstable-v3-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "tablet-v2-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "primary-selection-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "input-timestamps-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "pointer-gestures-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "cursor-shape-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#ଅନ୍ତର୍ଭାଵ <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_ନିବେଶ_LINUXEV
#ଅନ୍ତର୍ଭାଵ <linux/input.h>
#ଅନ୍ୟଥା
#define BTN_ବାମ    (0x110)
#define BTN_ଡାହାଣ   (0x111)
#define BTN_ମଧ୍ୟ  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keysym_to_scancode_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/imKStoUCS.h"
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <xkbcommon/xkbcommon-compose.h>
#ଅନ୍ତର୍ଭାଵ <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ତଳ  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_ଉପର (WAYLAND_TIMER_ROLLOVER_INTERVAL_ତଳ * 15U)

// Scoped function declarations
ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    Uint32 ଚାବି;
    SDL_Scancode scancode;
} Wayland_Reserved_ଚାବି;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ସଂରଚନା wl_surface *surface;

    ସଂରଚନା wl_list link;
} SDL_WaylandTouchPoint;

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ସଂରଚନା wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(ଆକାର(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ଭର୍ତ୍ତି(&seat->touch.points, &tp->link);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    ଯଦି (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        ଯଦି (window_data) {
            ଅଚଳ ଦଶମିକ x = (ଦଶମିକ)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            ଅଚଳ ଦଶମିକ y = (ଦଶମିକ)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_ଗଣନା;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ଯଦି (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ଗଣନା &&
                !window_data->pointer_focus_ଗଣନା && !window_data->active_touch_ଗଣନା) {
                SDL_SetMouseFocus(ଖାଲି);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ସଂରଚନା wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ଯଦି (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ଯଦି (surface) {
                *surface = tp->surface;
            }
            ଭାଙ୍ଗ;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ସଂରଚନା wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ଯଦି (tp->id == id) {
            ଯଦି (fx) {
                *fx = tp->fx;
            }
            ଯଦି (fy) {
                *fy = tp->fy;
            }
            ଯଦି (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ଭାଙ୍ଗ;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

ସ୍ଥିର Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    ସ୍ଥିର Uint64 timestamp_offset = 0;
    ଅଚଳ Uint64 now = SDL_GetTicksNS();

    ଯଦି (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    ଯଦି (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ଫେରନ୍ତୁ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ସ୍ଥିର Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ସ୍ଥିର Uint64 timestamp_offset = 0;
    ସ୍ଥିର Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    ଯଦି (wl_timestamp_ms >= last) {
        ଯଦି (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_ତଳ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ଉପର) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } ଅନ୍ୟଥା {
            last = wl_timestamp_ms;
        }
    } ଅନ୍ୟଥା {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ଯଦି (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_ତଳ && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_ଉପର) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    ଫେରନ୍ତୁ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ସ୍ଥିର Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ଅଚଳ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ଫେରନ୍ତୁ Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ସ୍ଥିର Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ଅଚଳ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ଫେରନ୍ତୁ Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ଅଚଳ Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ଫେରନ୍ତୁ Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ସ୍ଥିର ଶୂନ୍ୟ ନିବେଶ_timestamp_listener(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_ନିବେଶ_timestamps_v1 *zwp_ନିବେଶ_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_ନିବେଶ_timestamps_v1_listener timestamp_listener = {
    ନିବେଶ_timestamp_listener
};

ସ୍ଥିର ଶୂନ୍ୟ Wayland_Seat_Register_ନିବେଶ_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    ଯଦି (seat->display->ନିବେଶ_timestamps_manager) {
        ଯଦି (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ନିବେଶ_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ନିବେଶ_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ନିବେଶ_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ଯଦି (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_ନିବେଶ_timestamps_manager_v1_get_pointer_timestamps(seat->display->ନିବେଶ_timestamps_manager, seat->pointer.wl_pointer);
            zwp_ନିବେଶ_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        ଯଦି (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ନିବେଶ_timestamps_manager_v1_get_touch_timestamps(seat->display->ନିବେଶ_timestamps_manager, seat->touch.wl_touch);
            zwp_ନିବେଶ_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

ଶୂନ୍ୟ Wayland_Display_Init_ନିବେଶ_Timestamp_Manager(SDL_VideoData *display)
{
    ଯଦି (display->ନିବେଶ_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_ନିବେଶ_Timestamp_Listeners(seat);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ handle_pinch_begin(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, ସଂରଚନା wl_surface *surface, uint32_t fingers)
{
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    ଯଦି (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        ଅଚଳ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ handle_pinch_update(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ଯଦି (seat->pointer.gesture_focus) {
        ଅଚଳ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ଅଚଳ ଦଶମିକ s = (ଦଶମିକ)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ handle_pinch_end(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ଯଦି (seat->pointer.gesture_focus) {
        ଅଚଳ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = ଖାଲି;
    }
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    ଯଦି (seat->display->zwp_pointer_gestures) {
        ଯଦି (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

ଶୂନ୍ୟ Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ଯଦି (seat->display->cursor_shape_manager) {
        ଯଦି (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ଯଦି (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

ଶୂନ୍ୟ Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    ଅଚଳ bool send_event = !seat->display->initializing;

    ଯଦି (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ଅଙ୍କ_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ସ୍ଥିର ଶୂନ୍ୟ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ଯେତେବେଳେ (elapsed >= repeat_info->next_repeat_ns) {
        ଯଦି (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ଅଚଳ Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_Send_Keyboard_ଚାବି_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->ଚାବି, repeat_info->scancode, true);
        }
        ଯଦି (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ଚାବି, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, ଅଚଳ ଅକ୍ଷର *text)
{
    ଯଦି (!repeat_info->repeat_rate) {
        ଫେରନ୍ତୁ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ଚାବି = ଚାବି;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ଯଦି (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } ଅନ୍ୟଥା {
        repeat_info->text[0] = '\0';
    }
}

ସ୍ଥିର ଶୂନ୍ୟ sync_done_handler(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ସ୍ଥିର ସଂରଚନା wl_callback_listener sync_listener = {
    sync_done_handler
};

ଶୂନ୍ୟ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ସଂରଚନା wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, ଖାଲି);
    WAYLAND_wl_display_flush(d->display);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_fd = WAYLAND_wl_display_get_fd(d->display);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ଯଦି (!d->text_ନିବେଶ_manager && keyboard_focus && SDL_Text_ନିବେଶ_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ଯଦି (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ଯଦି (seat->keyboard.repeat.ଚାବି) {
            ଅଚଳ Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ଅଚଳ Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            ଯଦି (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    ଯଦି (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ଯଦି (timeoutNS > 0) {
            ଅଚଳ Uint64 now = SDL_GetTicksNS();
            ଅଚଳ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ଯଦି (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ଯଦି (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ଯଦି (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ଫେରନ୍ତୁ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ଯଦି (timeoutNS > 0) {
            ଅଚଳ Uint64 now = SDL_GetTicksNS();
            ଅଚଳ Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ଯଦି (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ଯଦି (ret == 0) {
                ଫେରନ୍ତୁ poll_alarm_set ? 1 : 0;
            } ଅନ୍ୟଥା {
                // Pump events on an interrupt or broken pipe to handle the error.
                ଫେରନ୍ତୁ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ଯଦି (ret == -1) {
            ଫେରନ୍ତୁ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ଫେରନ୍ତୁ 1;
}

ଶୂନ୍ୟ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_fd = WAYLAND_wl_display_get_fd(d->display);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ଯଦି (!d->text_ନିବେଶ_manager && keyboard_focus && SDL_Text_ନିବେଶ_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    ଯଦି (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ଯଦି (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ଯଦି (ret < 0) {
            ଯାଅ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ଯଦି (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ଯଦି (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            ଯଦି (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ଯଦି (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            ଯାଅ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ଯଦି (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ଯଦି (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ଅନ୍ୟଥା {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ଅନ୍ୟଥା {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ଯଦି (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ଯଦି (seat->keyboard.repeat.ଚାବି) {
                Wayland_SeatSetKeymap(seat);

                ଅଚଳ Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ଯଦି (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : ଖାଲି;

    ଯଦି (window_data) {
        ଦ୍ୱିଗୁଣ sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        ଦ୍ୱିଗୁଣ sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        ଯଦି (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (ଦ୍ୱିଗୁଣ)window_data->mask.offset_x;
            sy += (ଦ୍ୱିଗୁଣ)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        ଯଦି (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (ଦଶମିକ)sx, (ଦଶମିକ)sy);
        } ଅନ୍ୟଥା {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (ଦଶମିକ)sx, (ଦଶମିକ)sy);
        }

        seat->pointer.last_motion.x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_floor(sx);
        seat->pointer.last_motion.y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ଯଦି (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ଯଦି (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ବାଛ (rc) {
            ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPLEFT:
                ଯଦି ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ) {
                    rc = SDL_HITTEST_RESIZE_ବାମ;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ) {
                    rc = SDL_HITTEST_RESIZE_ଶୀର୍ଷ;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_ଶୀର୍ଷ:
                ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPRIGHT:
                ଯଦି ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ) {
                    rc = SDL_HITTEST_RESIZE_ଡାହାଣ;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ) {
                    rc = SDL_HITTEST_RESIZE_ଶୀର୍ଷ;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_ଡାହାଣ:
                ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ଯଦି ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ଡାହାଣ;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOM:
                ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ଯଦି ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ)) {
                    rc = SDL_HITTEST_NORMAL;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ବାମ;
                } ଅନ୍ୟଥା ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_HITTEST_RESIZE_ବାମ:
                ଯଦି (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                ଭାଙ୍ଗ;
            }

            ଯଦି (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_motion(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ଅଚଳ Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ଯଦି (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } ଅନ୍ୟଥା {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    ଯଦି (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ଫେରନ୍ତୁ;
    }

    ଯଦି (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        ଫେରନ୍ତୁ;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_ଗଣନା;
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

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_enter(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                 uint32_t serial, ସଂରଚନା wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ଯଦି (!surface) {
        // Enter event for a destroyed surface.
        ଫେରନ୍ତୁ;
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

    ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    ଯଦି (window) {
        ଯଦି (seat->pointer.focus) {
            ଯଦି (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = ଖାଲି;
                seat->pointer.focus_surface = ଖାଲି;
                ପାଇଁ (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    ଯଦି (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                ଅଚଳ bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                ଯଦି (!--window->pointer_focus_ଗଣନା && had_focus && !window->active_touch_ଗଣନା) {
                    SDL_SetMouseFocus(ଖାଲି);
                }

                ଯଦି (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } ଅନ୍ୟଥା ଯଦି (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_leave(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                 uint32_t serial, ସଂରଚନା wl_surface *surface)
{
    ଯଦି (!surface) {
        // Leave event for a destroyed surface.
        ଫେରନ୍ତୁ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

ସ୍ଥିର bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ଯଦି (seat->pointer.locked_pointer) {
        ଫେରନ୍ତୁ false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    ଯଦି (window->hit_test) {
        ସ୍ଥିର ଅଚଳ uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_ଶୀର୍ଷ_ବାମ, XDG_TOPLEVEL_RESIZE_EDGE_ଶୀର୍ଷ,
            XDG_TOPLEVEL_RESIZE_EDGE_ଶୀର୍ଷ_ଡାହାଣ, XDG_TOPLEVEL_RESIZE_EDGE_ଡାହାଣ,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ଡାହାଣ, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_ବାମ, XDG_TOPLEVEL_RESIZE_EDGE_ବାମ
        };

#ifdef HAVE_LIBDECOR_H
        ସ୍ଥିର ଅଚଳ uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_ଶୀର୍ଷ_ବାମ, LIBDECOR_RESIZE_EDGE_ଶୀର୍ଷ,
            LIBDECOR_RESIZE_EDGE_ଶୀର୍ଷ_ଡାହାଣ, LIBDECOR_RESIZE_EDGE_ଡାହାଣ,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ଡାହାଣ, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_ବାମ, LIBDECOR_RESIZE_EDGE_ବାମ
        };
#endif

        ବାଛ (window_data->hit_test_result) {
        ସ୍ଥିତି SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            ଯଦି (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ଯଦି (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } ଅନ୍ୟଥା
#endif
                ଯଦି (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ଯଦି (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ଫେରନ୍ତୁ true;

        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPLEFT:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଶୀର୍ଷ:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPRIGHT:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଡାହାଣ:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOM:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMLEFT:
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ବାମ:
#ifdef HAVE_LIBDECOR_H
            ଯଦି (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ଯଦି (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ଅନ୍ୟଥା
#endif
                ଯଦି (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ଯଦି (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ଫେରନ୍ତୁ true;

        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ false;
        }
    }

    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    ଯଦି (window) {
        bool ignore_click = false;

        ଯଦି (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            ଯଦି (sdl_button == SDL_BUTTON_ବାମ && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                ଫେରନ୍ତୁ; // don't pass this event on to app.
            }
        } ଅନ୍ୟଥା {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ଯଦି (window->last_focus_event_time_ns) {
            ଯଦି (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        ଯଦି (!seat->pointer.relative_pointer) {
            ଯଦି (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } ଅନ୍ୟଥା {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ଯଦି (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        ଯଦି (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_button(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    ବାଛ (button) {
    ସ୍ଥିତି BTN_ବାମ:
        sdl_button = SDL_BUTTON_ବାମ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି BTN_ମଧ୍ୟ:
        sdl_button = SDL_BUTTON_ମଧ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି BTN_ଡାହାଣ:
        sdl_button = SDL_BUTTON_ଡାହାଣ;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ଭାଙ୍ଗ;
    }

    ଯଦି (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    ଯଦି (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        ଯଦି (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } ଅନ୍ୟଥା {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } ଅନ୍ୟଥା {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t ମୂଲ୍ୟ)
{
    SDL_WindowData *window = seat->pointer.focus;
    ଅଚଳ ଗଣନା wl_pointer_axis a = axis;

    ଯଦି (seat->pointer.focus) {
        ଦଶମିକ x, y;

        ବାଛ (a) {
        ସ୍ଥିତି WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
            y = 0;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_common(SDL_WaylandSeat *seat, ଗଣନା SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t ମୂଲ୍ୟ)
{
    ଅଚଳ ଗଣନା wl_pointer_axis a = axis;

    ଯଦି (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        ବାଛ (a) {
        ସ୍ଥିତି WL_POINTER_AXIS_VERTICAL_SCROLL:
            ବାଛ (type) {
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ଯଦି (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ଯଦି (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ଯଦି (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                }
                ଭାଙ୍ଗ;
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            ବାଛ (type) {
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ଯଦି (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ଯଦି (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ଯଦି (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (ଦଶମିକ)wl_fixed_to_double(ମୂଲ୍ୟ);
                }
                ଭାଙ୍ଗ;
            }
            ଭାଙ୍ଗ;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t ମୂଲ୍ୟ)
{
    SDL_WaylandSeat *seat = data;
    ଅଚଳ Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    ଯଦି (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, ମୂଲ୍ୟ);
    } ଅନ୍ୟଥା {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, ମୂଲ୍ୟ);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_relative_direction(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    ବାଛ (axis_relative_direction) {
    ସ୍ଥିତି WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    ଯଦି (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ଦ୍ୱିଗୁଣ dx;
        ଦ୍ୱିଗୁଣ dy;
        ଯଦି (mouse->ନିବେଶ_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } ଅନ୍ୟଥା {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (ଦଶମିକ)dx, (ଦଶମିକ)dy);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    ଦଶମିକ x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    ବାଛ (seat->pointer.pending_frame.axis.x_axis_type) {
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        x = 0.0f;
        ଭାଙ୍ଗ;
    }

    ବାଛ (seat->pointer.pending_frame.axis.y_axis_type) {
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        y = 0.0f;
        ଭାଙ୍ଗ;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_frame(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    ଯଦି (seat->pointer.pending_frame.enter_surface) {
        ଯଦି (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            ଯଦି (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = ଖାଲି;
                seat->pointer.pending_frame.leave_surface = ଖାଲି;
            } ଅନ୍ୟଥା {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = ଖାଲି;
            }
        }

        ଯଦି (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    ଯଦି (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    ଯଦି (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    ପାଇଁ (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        ଅଚଳ Uint32 mask = SDL_BUTTON_MASK(i);
        ଯଦି (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        ଯଦି (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    ଯଦି (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    ଯଦି (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_source(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_stop(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_discrete(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_axis_value120(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ସ୍ଥିର ଶୂନ୍ୟ pointer_handle_warp(ଶୂନ୍ୟ *data, ସଂରଚନା wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_pointer_listener pointer_listener = {
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

ସ୍ଥିର ଶୂନ୍ୟ relative_pointer_handle_relative_motion(ଶୂନ୍ୟ *data,
                                                    ସଂରଚନା zwp_relative_pointer_v1 *pointer,
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

    ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } ଅନ୍ୟଥା {
        pointer_dispatch_relative_motion(seat);
    }
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

ସ୍ଥିର ଶୂନ୍ୟ locked_pointer_locked(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ସ୍ଥିର ଶୂନ୍ୟ locked_pointer_unlocked(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

ସ୍ଥିର ଶୂନ୍ୟ confined_pointer_confined(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

ସ୍ଥିର ଶୂନ୍ୟ confined_pointer_unconfined(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_down(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ସଂରଚନା wl_surface *surface,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    ଯଦି (window_data && window_data->surface == surface) {
        ଦଶମିକ x, y;

        ଯଦି (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } ଅନ୍ୟଥା {
            x = (ଦଶମିକ)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        ଯଦି (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } ଅନ୍ୟଥା {
            y = (ଦଶମିକ)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_ଗଣନା;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_up(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *touch, uint32_t serial, uint32_t timestamp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    ସଂରଚନା wl_surface *surface = ଖାଲି;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ଯଦି (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ଯଦି (window_data && window_data->surface == surface) {
            ଅଚଳ ଦଶମିକ x = (ଦଶମିକ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ଅଚଳ ଦଶମିକ y = (ଦଶମିକ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_ଗଣନା;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ଯଦି (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_ଗଣନା &&
                !window_data->pointer_focus_ଗଣନା && !window_data->active_touch_ଗଣନା) {
                SDL_SetMouseFocus(ଖାଲି);
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_motion(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *touch, uint32_t timestamp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ସଂରଚନା wl_surface *surface = ଖାଲି;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ଯଦି (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ଯଦି (window_data && window_data->surface == surface) {
            ଅଚଳ ଦଶମିକ x = (ଦଶମିକ)wl_fixed_to_double(fx) / window_data->current.logical_width;
            ଅଚଳ ଦଶମିକ y = (ଦଶମିକ)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_frame(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *touch)
{
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_cancel(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_shape(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ସ୍ଥିର ଶୂନ୍ୟ touch_handler_orientation(ଶୂନ୍ୟ *data, ସଂରଚନା wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ଯଦି !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
ସ୍ଥିର size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ଚାବି, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    ଯଦି (!masks_out || !masks_size) {
        ଫେରନ୍ତୁ 0;
    }

    // Level 0 is always unmodified, so early out.
    ଯଦି (level == 0) {
        *masks_out = 0;
        ଫେରନ୍ତୁ 1;
    }

    size_t mask_idx = 0;
    ଅଚଳ xkb_mod_mask_t keymod_masks[] = {
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
    ଅଚଳ xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    ଅଚଳ xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    ପାଇଁ (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        ଯଦି (WAYLAND_xkb_state_ଚାବି_get_level(seat->keyboard.xkb.state, ଚାବି, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            ଯଦି (++mask_idx == masks_size) {
                ଭାଙ୍ଗ;
            }
        }
    }

    ଫେରନ୍ତୁ mask_idx;
}
#endif

ସ୍ଥିର ଶୂନ୍ୟ Wayland_KeymapIterator(ସଂରଚନା xkb_keymap *keymap, xkb_keycode_t ଚାବି, ଶୂନ୍ୟ *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ଅଚଳ xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ଅଚଳ xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ଯଦି (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ଚାବି - 8);
    }

    ପାଇଁ (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.ଅଙ୍କ_layouts; ++layout) {
        ଅଚଳ xkb_level_index_t ଅଙ୍କ_levels = WAYLAND_xkb_keymap_ଅଙ୍କ_levels_for_ଚାବି(seat->keyboard.xkb.keymap, ଚାବି, layout);
        ପାଇଁ (xkb_level_index_t level = 0; level < ଅଙ୍କ_levels; ++level) {
            ଯଦି (WAYLAND_xkb_keymap_ଚାବି_get_syms_by_level(seat->keyboard.xkb.keymap, ଚାବି, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ଯଦି (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ଚାବି_Sym(syms[0], ଚାବି);
                    ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
                        ଜାରି;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#ଯଦି SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                ଅଚଳ size_t ଅଙ୍କ_masks = WAYLAND_xkb_keymap_ଚାବି_get_mods_for_level(seat->keyboard.xkb.keymap, ଚାବି, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ଅନ୍ୟଥା
                ଅଚଳ size_t ଅଙ୍କ_masks = xkb_legacy_get_mods_for_level(seat, ଚାବି, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                ପାଇଁ (size_t mask = 0; mask < ଅଙ୍କ_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ଯଦି ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        ଜାରି;
                    }

                    ଅଚଳ SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ଚାବି_Code_From_ଚାବି_Sym(syms[0], ଚାବି, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ଯଦି (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        ଯଦି (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ଚାବି *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, ଆକାର(Wayland_Reserved_ଚାବି));
                        ଯଦି (res) {
                            res->scancode = scancode;
                            res->ଚାବି = ଚାବି - 8;
                        }
                    }

                    ଯଦି (!keycode) {
                        ବାଛ (scancode) {
                        ସ୍ଥିତି SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ଭାଙ୍ଗ;
                        ସ୍ଥିତି SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ଭାଙ୍ଗ;
                        ସ୍ଥିତି SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ଭାଙ୍ଗ;
                        ସ୍ଥିତି SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ଭାଙ୍ଗ;
                        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            ଭାଙ୍ଗ;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_keymap(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *keyboard,
                                   uint32_t format, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    ଅକ୍ଷର *map_str;

    ଯଦି (!data) {
        close(fd);
        ଫେରନ୍ତୁ;
    }

    ଯଦି (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ଫେରନ୍ତୁ;
    }

    map_str = mmap(ଖାଲି, size, PROT_READ, MAP_PRIVATE, fd, 0);
    ଯଦି (map_str == MAP_FAILED) {
        close(fd);
        ଫେରନ୍ତୁ;
    }

    ଯଦି (seat->keyboard.xkb.keymap != ଖାଲି) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ଖାଲି;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    ଯଦି (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        ଫେରନ୍ତୁ;
    }

    // Clear the old layouts.
    ପାଇଁ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ଅଙ୍କ_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ଖାଲି;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.ଅଙ୍କ_layouts = 0;

#ଯଦି SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.ଅଙ୍କ_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ଅଙ୍କ);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ଅନ୍ୟଥା
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.ଅଙ୍କ_mask = 1 << GET_MOD_INDEX(ଅଙ୍କ_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    ଯଦି (seat->keyboard.xkb.state != ଖାଲି) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ଖାଲି;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ଯଦି (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ଖାଲି;
        ଫେରନ୍ତୁ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ଖାଲି;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.ଅଙ୍କ_layouts = WAYLAND_xkb_keymap_ଅଙ୍କ_layouts(seat->keyboard.xkb.keymap);
    ଯଦି (seat->keyboard.xkb.ଅଙ୍କ_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.ଅଙ୍କ_layouts, ଆକାର(SDL_Keymap *));
        ଯଦି (!seat->keyboard.sdl_keymap) {
            ଫେରନ୍ତୁ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        ପାଇଁ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ଅଙ୍କ_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ଯଦି (!seat->keyboard.sdl_keymap[i]) {
                ପାଇଁ (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ଖାଲି;
                ଫେରନ୍ତୁ;
            }
        }

        WAYLAND_xkb_keymap_ଚାବି_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ଅଙ୍କ_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ଅଚଳ ଅକ୍ଷର *locale = SDL_getenv("LC_ALL");
    ଯଦି (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ଯଦି (!locale) {
            locale = SDL_getenv("LANG");
            ଯଦି (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ଯଦି (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ଯଦି (seat->keyboard.xkb.compose_table != ଖାଲି) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = ଖାଲି;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ଯଦି (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            ଯଦି (seat->keyboard.xkb.compose_state != ଖାଲି) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ଖାଲି;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ଯଦି (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = ଖାଲି;
            }
        }
    } ଅନ୍ୟଥା ଯଦି (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ସ୍ଥିର SDL_Scancode Wayland_Get_Scancode_For_ଚାବି(SDL_WaylandSeat *seat, Uint32 ଚାବି, ଅଚଳ xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ଯଦି (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, ଚାବି);

        // No table entry? Check the reserved list.
        ଯଦି (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ଚାବି *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ଯଦି (i->ଚାବି == ଚାବି) {
                    ଫେରନ୍ତୁ i->scancode;
                }
            }
        }
    } ଅନ୍ୟଥା {
        ଅଚଳ xkb_keysym_t *keysym;
        ଯଦି (WAYLAND_xkb_state_ଚାବି_get_syms(seat->keyboard.xkb.state, ଚାବି + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ଚାବି_Sym(keysym[0], ଚାବି + 8);
            ଯଦି (syms) {
                *syms = keysym;
            }
        }
    }

    ଫେରନ୍ତୁ scancode;
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ଚାବି_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ଯଦି (!ଚାବି_pressed) {
        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } ଅନ୍ୟଥା {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ଅନ୍ୟଥା {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ଅନ୍ୟଥା {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ଅନ୍ୟଥା {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } ଅନ୍ୟଥା {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        ଯଦି (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            ଯଦି (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ଅନ୍ୟଥା {
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
    ଅଚଳ xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        ଯଦି (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } ଅନ୍ୟଥା ଯଦି (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        ଯଦି (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ଅନ୍ୟଥା ଯଦି (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        ଯଦି (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ଅନ୍ୟଥା ଯଦି (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        ଯଦି (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ଅନ୍ୟଥା ଯଦି (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ଯଦି (xkb_locked_modifiers & seat->keyboard.xkb.ଅଙ୍କ_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_ଅଙ୍କ;
    } ଅନ୍ୟଥା {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ଅଙ୍କ;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_Handle_Modifier_ଚାବିଗୁଡ଼ିକ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ଅଚଳ SDL_Keycode keycode = SDL_Get_ଚାବି_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ବାଛ (keycode) {
    ସ୍ଥିତି SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_MODE:
        mod = SDL_KMOD_MODE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ;
    }

    ଯଦି (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ଅନ୍ୟଥା {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_enter(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *keyboard,
                                  uint32_t serial, ସଂରଚନା wl_surface *surface,
                                  ସଂରଚନା wl_array *ଚାବିଗୁଡ଼ିକ)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *ଚାବି;

    ଯଦି (!surface) {
        // Enter event for a destroyed surface.
        ଫେରନ୍ତୁ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ଯଦି (!window) {
        // Not a surface owned by SDL.
        ଫେରନ୍ତୁ;
    }

    ++window->keyboard_focus_ଗଣନା;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ନିବେଶ(seat);

#ifdef SDL_USE_IME
    ଯଦି (!seat->text_ନିବେଶ.zwp_text_ନିବେଶ) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (ଚାବି, ଚାବିଗୁଡ଼ିକ) {
        ଅଚଳ SDL_Scancode scancode = Wayland_Get_Scancode_For_ଚାବି(seat, *ଚାବି, ଖାଲି);
        ଯଦି (scancode != SDL_SCANCODE_UNKNOWN) {
            ଅଚଳ SDL_Keycode keycode = SDL_Get_ଚାବି_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ବାଛ (keycode) {
            ସ୍ଥିତି SDLK_LSHIFT:
            ସ୍ଥିତି SDLK_RSHIFT:
            ସ୍ଥିତି SDLK_LCTRL:
            ସ୍ଥିତି SDLK_RCTRL:
            ସ୍ଥିତି SDLK_LALT:
            ସ୍ଥିତି SDLK_RALT:
            ସ୍ଥିତି SDLK_LGUI:
            ସ୍ଥିତି SDLK_RGUI:
            ସ୍ଥିତି SDLK_MODE:
            ସ୍ଥିତି SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_ଚାବିଗୁଡ଼ିକ(seat, scancode, true);
                SDL_Send_Keyboard_ଚାବି_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ଚାବି, scancode, true);
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                ଭାଙ୍ଗ;
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_leave(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *keyboard,
                                  uint32_t serial, ସଂରଚନା wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ଯଦି (!surface) {
        // Leave event for a destroyed surface.
        ଫେରନ୍ତୁ;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ଯଦି (!window) {
        // Not a surface owned by SDL.
        ଫେରନ୍ତୁ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ଚାବି = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ଯେତେବେଳେ (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ଅଚଳ bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ଖାଲି;
    --window->keyboard_focus_ଗଣନା;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ଯଦି (!window->keyboard_focus_ଗଣନା && had_focus) {
        SDL_SetKeyboardFocus(ଖାଲି);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_ନିବେଶ(seat);

#ifdef SDL_USE_IME
    ଯଦି (!seat->text_ନିବେଶ.zwp_text_ନିବେଶ && !window->keyboard_focus_ଗଣନା) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ଯଦି (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_ଗଣନା && !window->active_touch_ଗଣନା) {
        SDL_SetMouseFocus(ଖାଲି);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, ଖାଲି);
}

ସ୍ଥିର bool keyboard_ନିବେଶ_get_text(ଅକ୍ଷର text[8], ଅଚଳ SDL_WaylandSeat *seat, uint32_t ଚାବି, bool down, bool *handled_by_ime)
{
    ଅଚଳ xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ଯଦି (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ଫେରନ୍ତୁ false;
    }

    // TODO: Can this happen?
    ଯଦି (WAYLAND_xkb_state_ଚାବି_get_syms(seat->keyboard.xkb.state, ଚାବି + 8, &syms) != 1) {
        ଫେରନ୍ତୁ false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    ଯଦି (SDL_IME_Process_ଚାବି_Event(sym, ଚାବି + 8, down)) {
        ଯଦି (handled_by_ime) {
            *handled_by_ime = true;
        }
        ଫେରନ୍ତୁ true;
    }
#endif

    ଯଦି (!down) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ବାଛ (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        ସ୍ଥିତି XKB_COMPOSE_COMPOSING:
            ଯଦି (handled_by_ime) {
                *handled_by_ime = true;
            }
            ଫେରନ୍ତୁ true;
        ସ୍ଥିତି XKB_COMPOSE_CANCELLED:
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            sym = XKB_ଚାବି_No_ପ୍ରତୀକ;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି XKB_COMPOSE_NOTHING:
            ଭାଙ୍ଗ;
        ସ୍ଥିତି XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ଭାଙ୍ଗ;
        }
    }

    ଫେରନ୍ତୁ WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_ଚାବି(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t ଚାବି,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    ଗଣନା wl_keyboard_ଚାବି_state state = state_w;
    ଅକ୍ଷର text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ଅଚଳ Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ଯଦି (state == WL_KEYBOARD_ଚାବି_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ଯଦି (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ଚାବି_repeats(seat->keyboard.xkb.keymap, ଚାବି + 8)) {
            ଫେରନ୍ତୁ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ଚାବି_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    ଯଦି (state == WL_KEYBOARD_ଚାବି_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        ଯଦି (keyboard_focus && SDL_Text_ନିବେଶ_Active(keyboard_focus)) {
            has_text = keyboard_ନିବେଶ_get_text(text, seat, ଚାବି, true, &handled_by_ime);
        }
    } ଅନ୍ୟଥା {
        ଯଦି (ଚାବି == seat->keyboard.repeat.ଚାବି) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ଅଚଳ Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ଚାବି = 0;
        }
        keyboard_ନିବେଶ_get_text(text, seat, ଚାବି, false, &handled_by_ime);
    }

    ଅଚଳ xkb_keysym_t *syms = ଖାଲି;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ଚାବି(seat, ଚାବି, &syms);
    Wayland_Handle_Modifier_ଚାବିଗୁଡ଼ିକ(seat, scancode, state == WL_KEYBOARD_ଚାବି_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ଯଦି (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ଅଚଳ SDL_Keycode keycode = (SDL_Keycode)SDL_ଚାବି_Sym_To_Ucs4(syms[0]);
        ଯଦି (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ଯଦି (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ଚାବି_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ଚାବି, scancode, state == WL_KEYBOARD_ଚାବି_STATE_PRESSED);

    ଯଦି (state == WL_KEYBOARD_ଚାବି_STATE_PRESSED) {
        ଯଦି (handled_by_ime) {
            has_text = false;
        }
        ଯଦି (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        ଯଦି (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ଚାବି_repeats(seat->keyboard.xkb.keymap, ଚାବି + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, ଚାବି, time, timestamp_ns, scancode, has_text ? text : ଖାଲି);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_modifiers(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    ଅଚଳ uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ଯଦି (!seat->keyboard.xkb.state) {
        ଫେରନ୍ତୁ;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    ଯଦି (seat->keyboard.repeat.ଚାବି) {
        ଅକ୍ଷର text[8];

        ଯଦି (keyboard_ନିବେଶ_get_text(text, seat, seat->keyboard.repeat.ଚାବି, true, ଖାଲି)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    ଯଦି (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        ଯଦି (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ keyboard_handle_repeat_info(ଶୂନ୍ୟ *data, ସଂରଚନା wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ଯଦି (!rate) {
        seat->keyboard.repeat.ଚାବି = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ଚାବି,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    ଯଦି (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ଯଦି (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = ଖାଲି;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    ଯଦି (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    ଯଦି (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    ଯଦି (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    ଯଦି (seat->pointer.timestamps) {
        zwp_ନିବେଶ_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    ଯଦି (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    ଯଦି (seat->pointer.wl_pointer) {
        ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } ଅନ୍ୟଥା {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ଯଦି (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ଯଦି (seat->keyboard.sdl_keymap) {
        ଯଦି (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.ଅଙ୍କ_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        ପାଇଁ (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.ଅଙ୍କ_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ଖାଲି;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ଯଦି (seat->keyboard.ଚାବି_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ଚାବି_inhibitor);
    }

    ଯଦି (seat->keyboard.timestamps) {
        zwp_ନିବେଶ_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ଯଦି (seat->keyboard.wl_keyboard) {
        ଯଦି (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ଅନ୍ୟଥା {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ଯଦି (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ଯଦି (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    ଯଦି (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ଯଦି (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ଯଦି (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ଯଦି (seat->touch.timestamps) {
        zwp_ନିବେଶ_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ଯଦି (seat->touch.wl_touch) {
        ଯଦି (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } ଅନ୍ୟଥା {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ସ୍ଥିର ଶୂନ୍ୟ seat_handle_capabilities(ଶୂନ୍ୟ *data, ସଂରଚନା wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ଅକ୍ଷର name_fmt[256];

    ଯଦି ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        ଯଦି (seat->name) {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } ଅନ୍ୟଥା {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } ଅନ୍ୟଥା ଯଦି (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    ଯଦି ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        ଯଦି (seat->name) {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ଅନ୍ୟଥା {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } ଅନ୍ୟଥା ଯଦି (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ଯଦି ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        ଯଦି (seat->name) {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ଅନ୍ୟଥା {
            SDL_snprintf(name_fmt, ଆକାର(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } ଅନ୍ୟଥା ଯଦି (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_ନିବେଶ_Timestamp_Listeners(seat);
}

ସ୍ଥିର ଶୂନ୍ୟ seat_handle_name(ଶୂନ୍ୟ *data, ସଂରଚନା wl_seat *wl_seat, ଅଚଳ ଅକ୍ଷର *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ଯଦି (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ସ୍ଥିର ଶୂନ୍ୟ data_offer_handle_offer(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_offer *wl_data_offer,
                                    ଅଚଳ ଅକ୍ଷର *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

ସ୍ଥିର ଶୂନ୍ୟ data_offer_handle_source_actions(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

ସ୍ଥିର ଶୂନ୍ୟ data_offer_handle_actions(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

ସ୍ଥିର ଶୂନ୍ୟ primary_selection_offer_handle_offer(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ଅଚଳ ଅକ୍ଷର *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_data_offer(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device,
                                          ସଂରଚନା wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, ଆକାର(*data_offer));
    ଯଦି (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id) : -1));
    }
}

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_enter(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device,
                                     uint32_t serial, ସଂରଚନା wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ସଂରଚନା wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ଖାଲି;
    data_device->has_mime_file = false;
    data_device->text_mime_type = ଖାଲି;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ଯଦି (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    ଯଦି (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        ଯଦି (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        ଯଦି (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        ଯଦି (!data_device->has_mime_file) {
            size_t mime_ଗଣନା = 0;
            ଅଚଳ ଅକ୍ଷର *ଅଚଳ *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_ଗଣନା);
            ପାଇଁ (size_t i = 0; i < mime_ଗଣନା; ++i) {
                ଯଦି (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    ଭାଙ୍ଗ;
                }
            }
        }

        ଯଦି (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            ଯଦି (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            ଦ୍ୱିଗୁଣ dx = wl_fixed_to_double(x);
            ଦ୍ୱିଗୁଣ dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            ଯଦି (surface == window->mask.surface) {
                dx += (ଦ୍ୱିଗୁଣ)window->mask.offset_x;
                dy += (ଦ୍ୱିଗୁଣ)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (ଦଶମିକ)dx, (ଦଶମିକ)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } ଅନ୍ୟଥା {
            // Decline the offer.
            wl_data_offer_accept(id, serial, ଖାଲି);
            ଯଦି (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } ଅନ୍ୟଥା {
        data_device->dnd_window = ଖାଲି;
        data_device->dnd_surface = ଖାଲି;

        // Decline the offer.
        ଯଦି (id) {
            wl_data_offer_accept(id, serial, ଖାଲି);
            ଯଦି (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_leave(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ଯଦି (data_device->drag_offer) {
        ଯଦି (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } ଅନ୍ୟଥା {
            SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = ଖାଲି;
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_motion(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    ଯଦି (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        ଦ୍ୱିଗୁଣ dx = wl_fixed_to_double(x);
        ଦ୍ୱିଗୁଣ dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        ଯଦି (data_device->dnd_surface == window_data->mask.surface) {
            dx += (ଦ୍ୱିଗୁଣ)window_data->mask.offset_x;
            dy += (ଦ୍ୱିଗୁଣ)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (ଦଶମିକ)dx, (ଦଶମିକ)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ drop_cleanup_handler(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ସ୍ଥିର ଶୂନ୍ୟ drop_dispatch_handler(ଶୂନ୍ୟ *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    ଯଦି (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        ଯଦି (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            ଶୂନ୍ୟ *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            ଯଦି (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ଯଦି (dbus) {
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା path_ଗଣନା = 0;
                    ଅକ୍ଷର **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_ଗଣନା);
                    // If dropped files contain a directory the list is empty
                    ଯଦି (paths && path_ଗଣନା > 0) {
                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < path_ଗଣନା; i++) {
                            SDL_SendDropFile(drop->dnd_window, ଖାଲି, paths[i]);
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
        ଯଦି (!drop_handled) {
            ଯଦି (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                ଶୂନ୍ୟ *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                ଯଦି (buffer) {
                    ଅକ୍ଷର *saveptr = ଖାଲି;
                    ଅକ୍ଷର *token = SDL_strtok_r((ଅକ୍ଷର *)buffer, "\r\n", &saveptr);
                    ଯେତେବେଳେ (token) {
                        ଯଦି (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, ଖାଲି, token);
                        }
                        token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } ଅନ୍ୟଥା ଯଦି (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                ଶୂନ୍ୟ *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                ଯଦି (buffer) {
                    ଅକ୍ଷର *saveptr = ଖାଲି;
                    ଅକ୍ଷର *token = SDL_strtok_r((ଅକ୍ଷର *)buffer, "\r\n", &saveptr);
                    ଯେତେବେଳେ (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(ଖାଲି, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        ଯଦି (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = ଖାଲି;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_drop(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ଯଦି (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, ଆକାର(Wayland_DropData));
        ଯଦି (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_ଭର୍ତ୍ତି(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } ଅନ୍ୟଥା {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } ଅନ୍ୟଥା {
        SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ data_device_handle_selection(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_device *wl_data_device,
                                         ସଂରଚନା wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = ଖାଲି;

    ଯଦି (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

ସ୍ଥିର ଶୂନ୍ୟ primary_selection_device_handle_offer(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ସଂରଚନା zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, ଆକାର(*primary_selection_offer));
    ଯଦି (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id) : -1));
}

ସ୍ଥିର ଶୂନ୍ୟ primary_selection_device_handle_selection(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ସଂରଚନା zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = ଖାଲି;

    ଯଦି (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    ଯଦି (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ସଂରଚନା wl_proxy *)id) : -1));
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_enter(ଶୂନ୍ୟ *data,
                             ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                             ସଂରଚନା wl_surface *surface)
{
    // No-op
}

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_leave(ଶୂନ୍ୟ *data,
                             ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                             ସଂରଚନା wl_surface *surface)
{
    // No-op
}

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_preedit_string(ଶୂନ୍ୟ *data,
                                      ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                                      ଅଚଳ ଅକ୍ଷର *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_ନିବେଶ.has_preedit = true;
    ଯଦି (text) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା cursor_begin_utf8 = cursor_begin >= 0 ? (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_utf8strnlen(text, cursor_begin) : -1;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା cursor_end_utf8 = cursor_end >= 0 ? (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_utf8strnlen(text, cursor_end) : -1;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା cursor_size_utf8;
        ଯଦି (cursor_end_utf8 >= 0) {
            ଯଦି (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } ଅନ୍ୟଥା {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } ଅନ୍ୟଥା {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } ଅନ୍ୟଥା {
        SDL_SendEditingText("", 0, 0);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_commit_string(ଶୂନ୍ୟ *data,
                                     ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                                     ଅଚଳ ଅକ୍ଷର *text)
{
    SDL_SendKeyboardText(text);
}

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_delete_surrounding_text(ଶୂନ୍ୟ *data,
                                               ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

ସ୍ଥିର ଶୂନ୍ୟ text_ନିବେଶ_done(ଶୂନ୍ୟ *data,
                            ସଂରଚନା zwp_text_ନିବେଶ_v3 *zwp_text_ନିବେଶ_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ଯଦି (!seat->text_ନିବେଶ.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_ନିବେଶ.has_preedit = false;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_text_ନିବେଶ_v3_listener text_ନିବେଶ_listener = {
    text_ନିବେଶ_enter,
    text_ନିବେଶ_leave,
    text_ନିବେଶ_preedit_string,
    text_ନିବେଶ_commit_string,
    text_ନିବେଶ_delete_surrounding_text,
    text_ନିବେଶ_done
};

ସ୍ଥିର ଶୂନ୍ୟ Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    ଯଦି (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ଯଦି (dbus) {
            ଅଚଳ ଅକ୍ଷର *id = dbus->bus_get_unique_name(dbus->session_conn);
            ଯଦି (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    ଯଦି (!data_device->id_str)
#endif
    {
        ଅକ୍ଷର id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, ଆକାର(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    ଯଦି (!seat->display->data_device_manager) {
        ଫେରନ୍ତୁ;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, ଆକାର(*data_device));
    ଯଦି (!data_device) {
        ଫେରନ୍ତୁ;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    ଯଦି (!data_device->data_device) {
        SDL_free(data_device);
        ଫେରନ୍ତୁ;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

ଶୂନ୍ୟ Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ଯଦି (!seat->display->primary_selection_device_manager) {
        ଫେରନ୍ତୁ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, ଆକାର(*primary_selection_device));
    ଯଦି (!primary_selection_device) {
        ଫେରନ୍ତୁ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ଯଦି (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ଅନ୍ୟଥା {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

ଶୂନ୍ୟ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_Seat_Create_Text_ନିବେଶ(SDL_WaylandSeat *seat)
{
    ଯଦି (seat->display->text_ନିବେଶ_manager) {
        seat->text_ନିବେଶ.zwp_text_ନିବେଶ = zwp_text_ନିବେଶ_manager_v3_get_text_ନିବେଶ(seat->display->text_ନିବେଶ_manager, seat->wl_seat);

        ଯଦି (seat->text_ନିବେଶ.zwp_text_ନିବେଶ) {
            zwp_text_ନିବେଶ_v3_set_user_data(seat->text_ନିବେଶ.zwp_text_ନିବେଶ, seat);
            zwp_text_ନିବେଶ_v3_add_listener(seat->text_ନିବେଶ.zwp_text_ନିବେଶ,
                                           &text_ନିବେଶ_listener, seat);
        }
    }
}

ଶୂନ୍ୟ Wayland_Display_Init_Text_ନିବେଶ_Manager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_ନିବେଶ(seat);
    }
}

// Pen/Tablet support...
ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_type(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ବାଛ (type) {
        #define CASE(typ) ସ୍ଥିତି ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ଫେରନ୍ତୁ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_hardware_serial(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_hardware_id_wacom(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_capability(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ବାଛ (capability) {
        #define CASE(wltyp,sdltyp) ସ୍ଥିତି ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ଫେରନ୍ତୁ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଭାଙ୍ଗ;  // unsupported here.
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_done(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ଯଦି (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ଖାଲି;
        sdltool->instance_id = SDL_AddPenDevice(0, ଖାଲି, window, &sdltool->info, sdltool, false);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_removed(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ଯଦି (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ଖାଲି;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_proximity_in(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t serial, ସଂରଚନା zwp_tablet_v2 *tablet, ସଂରଚନା wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : ଖାଲି;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ଖାଲି;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_proximity_out(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_down(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_up(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_motion(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    ଯଦି (windowdata) {
        sdltool->frame.x = (ଦଶମିକ)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (ଦଶମିକ)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_pressure(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((ଦଶମିକ) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    ଯଦି (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_distance(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((ଦଶମିକ) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    ଯଦି (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_tilt(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (ଦଶମିକ)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (ଦଶମିକ)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_button(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sdlbutton;

    ବାଛ (button) {
    ସ୍ଥିତି BTN_STYLUS:
        sdlbutton = 1;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି BTN_STYLUS2:
        sdlbutton = 2;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି BTN_STYLUS3:
        sdlbutton = 3;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_rotation(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ଅଚଳ ଦଶମିକ rotation = (ଦଶମିକ)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_slider(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_wheel(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_tool_handle_frame(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ଅଚଳ SDL_PenID instance_id = sdltool->instance_id;
    ଯଦି (!instance_id) {
        ଫେରନ୍ତୁ;  // Not a pen we report on.
    }

    ଅଚଳ Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : ଖାଲି;
    ଅଚଳ bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ଯଦି (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ଯଦି (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        ଯଦି (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } ଅନ୍ୟଥା {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } ଅନ୍ୟଥା {
        ଯଦି (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        ଯଦି (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    ପାଇଁ (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ଗଣନା; i++) {
        ଯଦି (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା state = sdltool->frame.buttons[i];
        ଯଦି (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    ଯଦି (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = ଖାଲି;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


ସ୍ଥିର ଶୂନ୍ୟ tablet_seat_handle_tablet_added(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ସଂରଚନା zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_seat_handle_tool_added(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ସଂରଚନା zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, ଆକାର(*sdltool));

    ଯଦି (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.ଅଙ୍କ_buttons = -1;

        ଯଦି (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ଭର୍ତ୍ତି(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ tablet_seat_handle_pad_added(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ସଂରଚନା zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

ଶୂନ୍ୟ Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_remove_all_pens_callback(SDL_PenID instance_id, ଶୂନ୍ୟ *handle, ଶୂନ୍ୟ *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    ଯଦି (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ଅନ୍ୟଥା {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ଖାଲି);
    }

    ଯଦି (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ଖାଲି;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

ଶୂନ୍ୟ Wayland_DisplayCreateSeat(SDL_VideoData *display, ସଂରଚନା wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, ଆକାର(SDL_WaylandSeat));
    ଯଦି (!seat) {
        ଫେରନ୍ତୁ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ଭର୍ତ୍ତି(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_ନିବେଶ(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    ଯଦି (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ଶୂନ୍ୟ Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ଯଦି (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        ଯଦି (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = ଖାଲି;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            ଯଦି (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ଯଦି (tool->focus == window) {
                tool->focus = ଖାଲି;
                Wayland_TabletToolUpdateCursor(tool);
                ଯଦି (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            ଯଦି (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                ଯଦି (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

ଶୂନ୍ୟ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    ଯଦି (!seat) {
        ଫେରନ୍ତୁ;
    }

    SDL_free(seat->name);

    ଯଦି (seat->data_device) {
        ଯଦି (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        ଯଦି (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        ଯଦି (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            ଯଦି (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ଯଦି (seat->data_device->data_device) {
            ଯଦି (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } ଅନ୍ୟଥା {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    ଯଦି (seat->primary_selection_device) {
        ଯଦି (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ଯଦି (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        ଯଦି (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ଯଦି (seat->text_ନିବେଶ.zwp_text_ନିବେଶ) {
        zwp_text_ନିବେଶ_v3_destroy(seat->text_ନିବେଶ.zwp_text_ନିବେଶ);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    ଯଦି (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } ଅନ୍ୟଥା {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    ଯଦି (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        ଯଦି (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ଯଦି (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                ଯଦି (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } ଅନ୍ୟଥା {
                    relative_focus = seat->pointer.focus->keyboard_focus_ଗଣନା != 0;
                }
            } ଅନ୍ୟଥା {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        ଯଦି (relative_focus) {
            ଯଦି (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } ଅନ୍ୟଥା ଯଦି (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = ଖାଲି;
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    ଯଦି (display->ଚାବି_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ଯଦି (seat->keyboard.ଚାବି_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ଚାବି_inhibitor);
            seat->keyboard.ଚାବି_inhibitor = ଖାଲି;
        }

        ଯଦି (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            ଯଦି (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ଯଦି (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.ଚାବି_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ଚାବି_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

ଶୂନ୍ୟ Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    ଯଦି (display->pointer_constraints) {
        ଯଦି (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = ଖାଲି;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        ଯଦି (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ଯଦି (seat->pointer.relative_pointer) {
                ଯଦି (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ଯଦି (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = ଖାଲି;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, ଖାଲି,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ଫେରନ୍ତୁ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ଯଦି (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ଖାଲି;
            }

            SDL_WindowData *w = seat->pointer.focus;
            ଯଦି (!w) {
                ଫେରନ୍ତୁ;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ଯଦି (!(window->flags & SDL_WINDOW_ନିବେଶ_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                ଫେରନ୍ତୁ;
            }

            ସଂରଚନା wl_region *confine_rect = ଖାଲି;
            ଯଦି (!SDL_RectEmpty(&window->mouse_rect)) {
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
                ଯଦି (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା closest_x = seat->pointer.last_motion.x;
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା closest_y = seat->pointer.last_motion.y;

                    ଯଦି (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ଅନ୍ୟଥା ଯଦି (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ଯଦି (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ଅନ୍ୟଥା ଯଦି (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ଯଦି (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                ଯଦି (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } ଅନ୍ୟଥା {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                ଖାଲି,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                ଯଦି (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

ଶୂନ୍ୟ Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ଯଦି (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

ଶୂନ୍ୟ Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ଯଦି (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

ଶୂନ୍ୟ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ଯଦି (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
