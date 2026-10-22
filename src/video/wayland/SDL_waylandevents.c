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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "../../core/unix/SDL_poll.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_scancode_tables_c.h"
#समावेश "../../events/SDL_keysym_to_keycode_c.h"
#समावेश "../../core/linux/SDL_system_theme.h"
#समावेश "../SDL_sysvideo.h"

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylandwindow.h"
#समावेश "SDL_waylandmouse.h"
#समावेश "SDL_waylandclipboard.h"
#समावेश "SDL_waylandkeyboard.h"

#समावेश "pointer-constraints-unstable-v1-client-protocol.h"
#समावेश "relative-pointer-unstable-v1-client-protocol.h"
#समावेश "xdg-shell-client-protocol.h"
#समावेश "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#समावेश "text-input-unstable-v3-client-protocol.h"
#समावेश "tablet-v2-client-protocol.h"
#समावेश "primary-selection-unstable-v1-client-protocol.h"
#समावेश "input-timestamps-unstable-v1-client-protocol.h"
#समावेश "pointer-gestures-unstable-v1-client-protocol.h"
#समावेश "cursor-shape-v1-client-protocol.h"
#समावेश "viewporter-client-protocol.h"

#अगर_घोषित HAVE_LIBDECOR_H
#समावेश <libdecor.h>
#पूर्ण_अगर

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#अगर_घोषित SDL_निवेश_LINUXEV
#समावेश <linux/input.h>
#अन्यथा
#घोषणा BTN_बायाँ    (0x110)
#घोषणा BTN_दायाँ   (0x111)
#घोषणा BTN_मध्य  (0x112)
#घोषणा BTN_SIDE    (0x113)
#घोषणा BTN_EXTRA   (0x114)
#घोषणा BTN_STYLUS  (0x14b)
#घोषणा BTN_STYLUS2 (0x14c)
#घोषणा BTN_STYLUS3 (0x149)
#पूर्ण_अगर
#समावेश "../../events/SDL_keysym_to_scancode_c.h"
#समावेश "../../events/imKStoUCS.h"
#समावेश <errno.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <xkbcommon/xkbcommon-compose.h>
#समावेश <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#घोषणा WAYLAND_WHEEL_AXIS_UNIT 10

#अगर_अघोषित XKB_MOD_NAME_MOD3
#घोषणा XKB_MOD_NAME_MOD3 "Mod3"
#पूर्ण_अगर

#अगर_अघोषित XKB_MOD_NAME_MOD5
#घोषणा XKB_MOD_NAME_MOD5 "Mod5"
#पूर्ण_अगर

// Keyboard and mouse names to match XWayland
#घोषणा WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#घोषणा WAYLAND_DEFAULT_POINTER_NAME "Virtual core pointer"
#घोषणा WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#घोषणा WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_TO_NS(10)

// Timer rollover detection thresholds
#घोषणा WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला  (SDL_MAX_UINT32 / 16U)
#घोषणा WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी (WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला * 15U)

// Scoped function declarations
अटल व्योम Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

प्रकार काष्ठा
{
    Uint32 कुंजी;
    SDL_Scancode scancode;
} Wayland_Reserved_कुंजी;

प्रकार काष्ठा
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    काष्ठा wl_surface *surface;

    काष्ठा wl_list link;
} SDL_WaylandTouchPoint;

अटल व्योम Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, काष्ठा wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(माप(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_जोड़ो(&seat->touch.points, &tp->link);
}

अटल व्योम Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    अगर (tp->surface) {
        SDL_Window_तथ्य *window_तथ्य_2 = Wayland_Get_Window_तथ्य_For_Owned_Surface(tp->surface);

        अगर (window_तथ्य_2) {
            स्थिर भग्न x = (भग्न)(wl_fixed_to_double(tp->fx) / window_तथ्य_2->current.logical_width);
            स्थिर भग्न y = (भग्न)(wl_fixed_to_double(tp->fy) / window_तथ्य_2->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_तथ्य_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_तथ्य_2->active_touch_गिनती;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            अगर (SDL_GetMouseFocus() == window_तथ्य_2->sdlwindow && !window_तथ्य_2->keyboard_focus_गिनती &&
                !window_तथ्य_2->pointer_focus_गिनती && !window_तथ्य_2->active_touch_गिनती) {
                SDL_SetMouseFocus(शून्य);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

अटल व्योम Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, काष्ठा wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        अगर (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            अगर (surface) {
                *surface = tp->surface;
            }
            अवरोध;
        }
    }
}

अटल व्योम Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, काष्ठा wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        अगर (tp->id == id) {
            अगर (fx) {
                *fx = tp->fx;
            }
            अगर (fy) {
                *fy = tp->fy;
            }
            अगर (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            अवरोध;
        }
    }
}

अटल व्योम Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_Window_तथ्य *window_तथ्य_2 = window->internal;

    scaled_rect->x = (पूर्णांक)SDL_floor(window->mouse_rect.x / window_तथ्य_2->pointer_scale.x);
    scaled_rect->y = (पूर्णांक)SDL_floor(window->mouse_rect.y / window_तथ्य_2->pointer_scale.y);
    scaled_rect->w = (पूर्णांक)SDL_ceil(window->mouse_rect.w / window_तथ्य_2->pointer_scale.x);
    scaled_rect->h = (पूर्णांक)SDL_ceil(window->mouse_rect.h / window_तथ्य_2->pointer_scale.y);
}

अटल Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    अटल Uint64 timestamp_offset = 0;
    स्थिर Uint64 now = SDL_GetTicksNS();

    अगर (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    अगर (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    वापस nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
अटल Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    अटल Uint64 timestamp_offset = 0;
    अटल Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    अगर (wl_timestamp_ms >= last) {
        अगर (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } अन्यथा {
            last = wl_timestamp_ms;
        }
    } अन्यथा {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        अगर (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_निचला && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_ऊपरी) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    वापस timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

अटल Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    वापस Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

अटल Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    वापस Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    वापस Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

अटल व्योम निवेश_timestamp_listener(व्योम *तथ्य, काष्ठा zwp_निवेश_timestamps_v1 *zwp_निवेश_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)तथ्य) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

अटल स्थिर काष्ठा zwp_निवेश_timestamps_v1_listener timestamp_listener = {
    निवेश_timestamp_listener
};

अटल व्योम Wayland_Seat_Register_निवेश_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    अगर (seat->display->निवेश_timestamps_manager) {
        अगर (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_निवेश_timestamps_manager_v1_get_keyboard_timestamps(seat->display->निवेश_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_निवेश_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        अगर (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_निवेश_timestamps_manager_v1_get_pointer_timestamps(seat->display->निवेश_timestamps_manager, seat->pointer.wl_pointer);
            zwp_निवेश_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        अगर (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_निवेश_timestamps_manager_v1_get_touch_timestamps(seat->display->निवेश_timestamps_manager, seat->touch.wl_touch);
            zwp_निवेश_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

व्योम Wayland_Display_Init_निवेश_Timestamp_Manager(SDL_Video_तथ्य *display)
{
    अगर (display->निवेश_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_Register_निवेश_Timestamp_Listeners(seat);
        }
    }
}

अटल व्योम handle_pinch_begin(व्योम *तथ्य, काष्ठा zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t समय, काष्ठा wl_surface *surface, uint32_t fingers)
{
    अगर (!surface) {
        वापस;
    }

    SDL_Window_तथ्य *wind = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);
    अगर (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
        seat->pointer.gesture_focus = wind;

        स्थिर Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

अटल व्योम handle_pinch_update(व्योम *तथ्य, काष्ठा zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t समय,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;

    अगर (seat->pointer.gesture_focus) {
        स्थिर Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        स्थिर भग्न s = (भग्न)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

अटल व्योम handle_pinch_end(व्योम *तथ्य, काष्ठा zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t समय, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;

    अगर (seat->pointer.gesture_focus) {
        स्थिर Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = शून्य;
    }
}

अटल स्थिर काष्ठा zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

अटल व्योम Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    अगर (seat->display->zwp_pointer_gestures) {
        अगर (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_तथ्य(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

व्योम Wayland_DisplayInitPointerGestureManager(SDL_Video_तथ्य *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

अटल व्योम Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    अगर (seat->display->cursor_shape_manager) {
        अगर (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            अगर (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

व्योम Wayland_DisplayInitCursorShapeManager(SDL_Video_तथ्य *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

अटल व्योम Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    स्थिर bool send_event = !seat->display->initializing;

    अगर (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
अटल व्योम keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    जबतक (elapsed >= repeat_info->अग्र_repeat_ns) {
        अगर (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            स्थिर Uint64 timestamp = repeat_info->base_time_ns + repeat_info->अग्र_repeat_ns;
            SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->कुंजी, repeat_info->scancode, true);
        }
        अगर (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->अग्र_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

अटल व्योम keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t कुंजी, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, स्थिर अक्षर *text)
{
    अगर (!repeat_info->repeat_rate) {
        वापस;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->कुंजी = कुंजी;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->अग्र_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    अगर (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } अन्यथा {
        repeat_info->text[0] = '\0';
    }
}

अटल व्योम sync_done_handler(व्योम *तथ्य, काष्ठा wl_callback *callback, uint32_t callback_तथ्य)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

अटल काष्ठा wl_callback_listener sync_listener = {
    sync_done_handler
};

व्योम Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    काष्ठा wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, शून्य);
    WAYLAND_wl_display_flush(d->display);
}

पूर्णांक Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_तथ्य *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    स्थिर पूर्णांक display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णांक ret;
    bool poll_alarm_set = false;

#अगर_घोषित SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    अगर (!d->text_निवेश_manager && keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        अगर (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#पूर्ण_अगर

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        अगर (seat->keyboard.repeat.कुंजी) {
            स्थिर Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            स्थिर Uint64 अग्र_repeat_wait_time = (seat->keyboard.repeat.अग्र_repeat_ns - elapsed) + 1;
            अगर (timeoutNS < 0 || अग्र_repeat_wait_time <= timeoutNS) {
                timeoutNS = अग्र_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    अगर (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        अगर (timeoutNS > 0) {
            स्थिर Uint64 now = SDL_GetTicksNS();
            स्थिर Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        अगर (ret == -1 && त्रुटि_सं == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            अगर (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        अगर (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            वापस त्रुटि_सं == EINTR || त्रुटि_सं == EPIPE ? 1 : ret;
        }

        अगर (timeoutNS > 0) {
            स्थिर Uint64 now = SDL_GetTicksNS();
            स्थिर Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        अगर (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            अगर (ret == 0) {
                वापस poll_alarm_set ? 1 : 0;
            } अन्यथा {
                // Pump events on an interrupt or broken pipe to handle the error.
                वापस त्रुटि_सं == EINTR || त्रुटि_सं == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        अगर (ret == -1) {
            वापस ret;
        }
    }

    // Signal to the caller that there might be an event available.
    वापस 1;
}

व्योम Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *d = _this->internal;
    SDL_WaylandSeat *seat;
    स्थिर पूर्णांक display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णांक ret = 0;

#अगर_घोषित SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    अगर (!d->text_निवेश_manager && keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#पूर्ण_अगर

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    अगर (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        अगर (ret < 0) {
            जाओ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    अगर (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        अगर (ret == -1 && त्रुटि_सं == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            अगर (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        अगर (ret < 0 && त्रुटि_सं == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            जाओ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        अगर (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            अगर (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } अन्यथा {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } अन्यथा {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    अगर (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            अगर (seat->keyboard.repeat.कुंजी) {
                Wayland_SeatSetKeymap(seat);

                स्थिर Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    अगर (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

अटल व्योम pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_Window_तथ्य *window_तथ्य_2 = seat->pointer.focus;
    SDL_Window *window = window_तथ्य_2 ? window_तथ्य_2->sdlwindow : शून्य;

    अगर (window_तथ्य_2) {
        द्विगुन sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        द्विगुन sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        अगर (seat->pointer.focus_surface == window_तथ्य_2->mask.surface) {
            sx += (द्विगुन)window_तथ्य_2->mask.offset_x;
            sy += (द्विगुन)window_तथ्य_2->mask.offset_y;
        }

        sx *= window_तथ्य_2->pointer_scale.x;
        sy *= window_तथ्य_2->pointer_scale.y;
        अगर (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_तथ्य_2->sdlwindow, seat->pointer.sdl_id, false, (भग्न)sx, (भग्न)sy);
        } अन्यथा {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_तथ्य_2->sdlwindow, seat->pointer.sdl_id, (भग्न)sx, (भग्न)sy);
        }

        seat->pointer.last_motion.x = (पूर्णांक)SDL_floor(sx);
        seat->pointer.last_motion.y = (पूर्णांक)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        अगर (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        अगर (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_Hit_Test_परिणाम rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_तथ्य);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            चयन (rc) {
            हाल SDL_HITTEST_RESIZE_TOPLEFT:
                अगर ((window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_बायाँ;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_शीर्ष:
                अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_NORMAL;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_TOPRIGHT:
                अगर ((window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) &&
                    (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष) {
                    rc = SDL_HITTEST_RESIZE_दायाँ;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_RESIZE_शीर्ष;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_दायाँ:
                अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                अगर ((window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_दायाँ;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_BOTTOM:
                अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_BOTTOMLEFT:
                अगर ((window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ)) {
                    rc = SDL_HITTEST_NORMAL;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_बायाँ;
                } अन्यथा अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                अवरोध;
            हाल SDL_HITTEST_RESIZE_बायाँ:
                अगर (window_तथ्य_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ) {
                    rc = SDL_HITTEST_NORMAL;
                }
                अवरोध;
            शेष:
                अवरोध;
            }

            अगर (rc != window_तथ्य_2->hit_test_परिणाम) {
                window_तथ्य_2->hit_test_परिणाम = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

अटल व्योम pointer_handle_motion(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                  uint32_t समय, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    स्थिर Uint64 timestamp = Wayland_GetPointerTimestamp(seat, समय);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    अगर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        अगर (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } अन्यथा {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

अटल व्योम pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_Window_तथ्य *window = Wayland_Get_Window_तथ्य_For_Owned_Surface(seat->pointer.pending_frame.enter_surface);
    अगर (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        वापस;
    }

    अगर (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        वापस;
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

अटल व्योम pointer_handle_enter(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                 uint32_t serial, काष्ठा wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    अगर (!surface) {
        // Enter event for a destroyed surface.
        वापस;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.pending_frame.enter_surface = surface;
    seat->pointer.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->pointer.pending_frame.absolute.sx = sx_w;
    seat->pointer.pending_frame.absolute.sy = sy_w;

    अगर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

अटल व्योम pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_Window_तथ्य *window = Wayland_Get_Window_तथ्य_For_Owned_Surface(seat->pointer.pending_frame.leave_surface);

    अगर (window) {
        अगर (seat->pointer.focus) {
            अगर (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = शून्य;
                seat->pointer.focus_surface = शून्य;
                क्रम (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    अगर (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                स्थिर bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                अगर (!--window->pointer_focus_गिनती && had_focus && !window->active_touch_गिनती) {
                    SDL_SetMouseFocus(शून्य);
                }

                अगर (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } अन्यथा अगर (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

अटल व्योम pointer_handle_leave(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                 uint32_t serial, काष्ठा wl_surface *surface)
{
    अगर (!surface) {
        // Leave event for a destroyed surface.
        वापस;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.pending_frame.leave_surface = surface;
    अगर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

अटल bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    अगर (seat->pointer.locked_pointer) {
        वापस false;
    }

    SDL_Window_तथ्य *window_तथ्य_2 = seat->pointer.focus;
    SDL_Window *window = window_तथ्य_2->sdlwindow;

    अगर (window->hit_test) {
        अटल स्थिर uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_बायाँ, XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष,
            XDG_TOPLEVEL_RESIZE_EDGE_शीर्ष_दायाँ, XDG_TOPLEVEL_RESIZE_EDGE_दायाँ,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_दायाँ, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_बायाँ, XDG_TOPLEVEL_RESIZE_EDGE_बायाँ
        };

#अगर_घोषित HAVE_LIBDECOR_H
        अटल स्थिर uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_शीर्ष_बायाँ, LIBDECOR_RESIZE_EDGE_शीर्ष,
            LIBDECOR_RESIZE_EDGE_शीर्ष_दायाँ, LIBDECOR_RESIZE_EDGE_दायाँ,
            LIBDECOR_RESIZE_EDGE_BOTTOM_दायाँ, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_बायाँ, LIBDECOR_RESIZE_EDGE_बायाँ
        };
#पूर्ण_अगर

        चयन (window_तथ्य_2->hit_test_परिणाम) {
        हाल SDL_HITTEST_DRAGGABLE:
#अगर_घोषित HAVE_LIBDECOR_H
            अगर (window_तथ्य_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                अगर (window_तथ्य_2->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_तथ्य_2->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } अन्यथा
#पूर्ण_अगर
                अगर (window_तथ्य_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                अगर (window_तथ्य_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_तथ्य_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            वापस true;

        हाल SDL_HITTEST_RESIZE_TOPLEFT:
        हाल SDL_HITTEST_RESIZE_शीर्ष:
        हाल SDL_HITTEST_RESIZE_TOPRIGHT:
        हाल SDL_HITTEST_RESIZE_दायाँ:
        हाल SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        हाल SDL_HITTEST_RESIZE_BOTTOM:
        हाल SDL_HITTEST_RESIZE_BOTTOMLEFT:
        हाल SDL_HITTEST_RESIZE_बायाँ:
#अगर_घोषित HAVE_LIBDECOR_H
            अगर (window_तथ्य_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                अगर (window_तथ्य_2->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_तथ्य_2->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_तथ्य_2->hit_test_परिणाम - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } अन्यथा
#पूर्ण_अगर
                अगर (window_तथ्य_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                अगर (window_तथ्य_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_तथ्य_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_तथ्य_2->hit_test_परिणाम - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            वापस true;

        शेष:
            वापस false;
        }
    }

    वापस false;
}

अटल व्योम pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_Window_तथ्य *window = seat->pointer.focus;

    अगर (window) {
        bool ignore_click = false;

        अगर (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            अगर (sdl_button == SDL_BUTTON_बायाँ && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                वापस; // don't pass this event on to app.
            }
        } अन्यथा {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        अगर (window->last_focus_event_time_ns) {
            अगर (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        अगर (!seat->pointer.relative_pointer) {
            अगर (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } अन्यथा {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                अगर (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        अगर (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

अटल व्योम pointer_handle_button(व्योम *तथ्य, काष्ठा wl_pointer *pointer, uint32_t serial,
                                  uint32_t समय, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = तथ्य;
    Uint8 sdl_button;

    चयन (button) {
    हाल BTN_बायाँ:
        sdl_button = SDL_BUTTON_बायाँ;
        अवरोध;
    हाल BTN_मध्य:
        sdl_button = SDL_BUTTON_मध्य;
        अवरोध;
    हाल BTN_दायाँ:
        sdl_button = SDL_BUTTON_दायाँ;
        अवरोध;
    शेष:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        अवरोध;
    }

    अगर (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, समय);

    अगर (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        अगर (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } अन्यथा {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } अन्यथा {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

अटल व्योम pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t मूल्य)
{
    SDL_Window_तथ्य *window = seat->pointer.focus;
    स्थिर क्रमागत wl_pointer_axis a = axis;

    अगर (seat->pointer.focus) {
        भग्न x, y;

        चयन (a) {
        हाल WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (भग्न)wl_fixed_to_double(मूल्य);
            अवरोध;
        हाल WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (भग्न)wl_fixed_to_double(मूल्य);
            y = 0;
            अवरोध;
        शेष:
            वापस;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

अटल व्योम pointer_handle_axis_common(SDL_WaylandSeat *seat, क्रमागत SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t मूल्य)
{
    स्थिर क्रमागत wl_pointer_axis a = axis;

    अगर (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        चयन (a) {
        हाल WL_POINTER_AXIS_VERTICAL_SCROLL:
            चयन (type) {
            हाल SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                अगर (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (भग्न)wl_fixed_to_double(मूल्य);
                अवरोध;
            हाल SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                अगर (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (भग्न)wl_fixed_to_double(मूल्य);
                }
                अवरोध;
            हाल SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                अगर (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (भग्न)wl_fixed_to_double(मूल्य);
                }
                अवरोध;
            }
            अवरोध;
        हाल WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            चयन (type) {
            हाल SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                अगर (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (भग्न)wl_fixed_to_double(मूल्य);
                अवरोध;
            हाल SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                अगर (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (भग्न)wl_fixed_to_double(मूल्य);
                }
                अवरोध;
            हाल SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                अगर (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (भग्न)wl_fixed_to_double(मूल्य);
                }
                अवरोध;
            }
            अवरोध;
        }
    }
}

अटल व्योम pointer_handle_axis(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                uint32_t समय, uint32_t axis, wl_fixed_t मूल्य)
{
    SDL_WaylandSeat *seat = तथ्य;
    स्थिर Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, समय);

    अगर (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, मूल्य);
    } अन्यथा {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, मूल्य);
    }
}

अटल व्योम pointer_handle_axis_relative_direction(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = तथ्य;

    चयन (axis_relative_direction) {
    हाल WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        अवरोध;
    हाल WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        अवरोध;
    }
}

अटल व्योम pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_Window_तथ्य *window = seat->pointer.focus;

    अगर (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        द्विगुन dx;
        द्विगुन dy;
        अगर (mouse->निवेश_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } अन्यथा {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (भग्न)dx, (भग्न)dy);
    }
}

अटल व्योम pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    भग्न x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    चयन (seat->pointer.pending_frame.axis.x_axis_type) {
    हाल SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        अवरोध;
    हाल SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        अवरोध;
    हाल SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        अवरोध;
    शेष:
        x = 0.0f;
        अवरोध;
    }

    चयन (seat->pointer.pending_frame.axis.y_axis_type) {
    हाल SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        अवरोध;
    हाल SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        अवरोध;
    हाल SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        अवरोध;
    शेष:
        y = 0.0f;
        अवरोध;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

अटल व्योम pointer_handle_frame(व्योम *तथ्य, काष्ठा wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = तथ्य;

    अगर (seat->pointer.pending_frame.enter_surface) {
        अगर (seat->pointer.pending_frame.leave_surface) {
            SDL_Window_तथ्य *window_तथ्य_2 = seat->pointer.focus;
            SDL_Window_तथ्य *new_focus = Wayland_Get_Window_तथ्य_For_Owned_Surface(seat->pointer.pending_frame.enter_surface);

            अगर (window_तथ्य_2 && (window_तथ्य_2->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_तथ्य_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = शून्य;
                seat->pointer.pending_frame.leave_surface = शून्य;
            } अन्यथा {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = शून्य;
            }
        }

        अगर (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    अगर (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    अगर (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    क्रम (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        स्थिर Uint32 mask = SDL_BUTTON_MASK(i);
        अगर (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        अगर (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    अगर (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    अगर (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

अटल व्योम pointer_handle_axis_source(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

अटल व्योम pointer_handle_axis_stop(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                     uint32_t समय, uint32_t axis)
{
    // unimplemented
}

अटल व्योम pointer_handle_axis_discrete(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = तथ्य;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

अटल व्योम pointer_handle_axis_value120(व्योम *तथ्य, काष्ठा wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = तथ्य;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

अटल व्योम pointer_handle_warp(व्योम *तथ्य, काष्ठा wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

अटल स्थिर काष्ठा wl_pointer_listener pointer_listener = {
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

अटल व्योम relative_pointer_handle_relative_motion(व्योम *तथ्य,
                                                    काष्ठा zwp_relative_pointer_v1 *pointer,
                                                    uint32_t time_hi,
                                                    uint32_t time_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = तथ्य;

    // Relative pointer event times are in microsecond granularity.
    seat->pointer.pending_frame.relative.dx = dx;
    seat->pointer.pending_frame.relative.dy = dy;
    seat->pointer.pending_frame.relative.dx_unaccel = dx_unaccel;
    seat->pointer.pending_frame.relative.dy_unaccel = dy_unaccel;
    seat->pointer.pending_frame.timestamp_ns = Wayland_AdjustEventTimestampBase(SDL_US_TO_NS(((Uint64)time_hi << 32) | (Uint64)time_lo));

    अगर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } अन्यथा {
        pointer_dispatch_relative_motion(seat);
    }
}

अटल स्थिर काष्ठा zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

अटल व्योम locked_pointer_locked(व्योम *तथ्य, काष्ठा zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.is_confined = true;
}

अटल व्योम locked_pointer_unlocked(व्योम *तथ्य, काष्ठा zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.is_confined = false;
}

अटल स्थिर काष्ठा zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

अटल व्योम confined_pointer_confined(व्योम *तथ्य, काष्ठा zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.is_confined = true;
}

अटल व्योम confined_pointer_unconfined(व्योम *तथ्य, काष्ठा zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->pointer.is_confined = false;
}

अटल स्थिर काष्ठा zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

अटल व्योम touch_handler_down(व्योम *तथ्य, काष्ठा wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, काष्ठा wl_surface *surface,
                               पूर्णांक id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    SDL_Window_तथ्य *window_तथ्य_2;

    // Check that this surface is valid.
    अगर (!surface) {
        वापस;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_तथ्य_2 = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);

    अगर (window_तथ्य_2 && window_तथ्य_2->surface == surface) {
        भग्न x, y;

        अगर (window_तथ्य_2->current.logical_width <= 1) {
            x = 0.5f;
        } अन्यथा {
            x = (भग्न)wl_fixed_to_double(fx) / (window_तथ्य_2->current.logical_width - 1);
        }
        अगर (window_तथ्य_2->current.logical_height <= 1) {
            y = 0.5f;
        } अन्यथा {
            y = (भग्न)wl_fixed_to_double(fy) / (window_तथ्य_2->current.logical_height - 1);
        }

        ++window_तथ्य_2->active_touch_गिनती;
        SDL_SetMouseFocus(window_तथ्य_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_तथ्य_2->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

अटल व्योम touch_handler_up(व्योम *तथ्य, काष्ठा wl_touch *touch, uint32_t serial, uint32_t timestamp, पूर्णांक id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    wl_fixed_t fx = 0, fy = 0;
    काष्ठा wl_surface *surface = शून्य;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    अगर (surface) {
        SDL_Window_तथ्य *window_तथ्य_2 = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);

        अगर (window_तथ्य_2 && window_तथ्य_2->surface == surface) {
            स्थिर भग्न x = (भग्न)wl_fixed_to_double(fx) / window_तथ्य_2->current.logical_width;
            स्थिर भग्न y = (भग्न)wl_fixed_to_double(fy) / window_तथ्य_2->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_तथ्य_2->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_तथ्य_2->active_touch_गिनती;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            अगर (SDL_GetMouseFocus() == window_तथ्य_2->sdlwindow && !window_तथ्य_2->keyboard_focus_गिनती &&
                !window_तथ्य_2->pointer_focus_गिनती && !window_तथ्य_2->active_touch_गिनती) {
                SDL_SetMouseFocus(शून्य);
            }
        }
    }
}

अटल व्योम touch_handler_motion(व्योम *तथ्य, काष्ठा wl_touch *touch, uint32_t timestamp, पूर्णांक id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    काष्ठा wl_surface *surface = शून्य;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    अगर (surface) {
        SDL_Window_तथ्य *window_तथ्य_2 = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);

        अगर (window_तथ्य_2 && window_तथ्य_2->surface == surface) {
            स्थिर भग्न x = (भग्न)wl_fixed_to_double(fx) / window_तथ्य_2->current.logical_width;
            स्थिर भग्न y = (भग्न)wl_fixed_to_double(fy) / window_तथ्य_2->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_तथ्य_2->sdlwindow, x, y, 1.0f);
        }
    }
}

अटल व्योम touch_handler_frame(व्योम *तथ्य, काष्ठा wl_touch *touch)
{
}

अटल व्योम touch_handler_cancel(व्योम *तथ्य, काष्ठा wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    SDL_WaylandTouchPoint *tp, *अस्थायी;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, अस्थायी, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

अटल व्योम touch_handler_shape(व्योम *तथ्य, काष्ठा wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

अटल व्योम touch_handler_orientation(व्योम *तथ्य, काष्ठा wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

अटल स्थिर काष्ठा wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#अगर !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
अटल माप_प्रकार xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t कुंजी, xkb_layout_सूचकांक_t layout, xkb_level_सूचकांक_t level, xkb_mod_mask_t *masks_out, माप_प्रकार masks_आकार)
{
    अगर (!masks_out || !masks_आकार) {
        वापस 0;
    }

    // Level 0 is always unmodified, so early out.
    अगर (level == 0) {
        *masks_out = 0;
        वापस 1;
    }

    माप_प्रकार mask_idx = 0;
    स्थिर xkb_mod_mask_t keymod_masks[] = {
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
    स्थिर xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    स्थिर xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    क्रम (माप_प्रकार i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        अगर (WAYLAND_xkb_state_कुंजी_get_level(seat->keyboard.xkb.state, कुंजी, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            अगर (++mask_idx == masks_आकार) {
                अवरोध;
            }
        }
    }

    वापस mask_idx;
}
#पूर्ण_अगर

अटल व्योम Wayland_KeymapIterator(काष्ठा xkb_keymap *keymap, xkb_keycode_t कुंजी, व्योम *तथ्य)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    स्थिर xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    स्थिर xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    अगर (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, कुंजी - 8);
    }

    क्रम (xkb_layout_सूचकांक_t layout = 0; layout < seat->keyboard.xkb.अंक_layouts; ++layout) {
        स्थिर xkb_level_सूचकांक_t अंक_levels = WAYLAND_xkb_keymap_अंक_levels_for_कुंजी(seat->keyboard.xkb.keymap, कुंजी, layout);
        क्रम (xkb_level_सूचकांक_t level = 0; level < अंक_levels; ++level) {
            अगर (WAYLAND_xkb_keymap_कुंजी_get_syms_by_level(seat->keyboard.xkb.keymap, कुंजी, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                अगर (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_कुंजी_Sym(syms[0], कुंजी);
                    अगर (scancode == SDL_SCANCODE_UNKNOWN) {
                        जारी;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#अगर SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                स्थिर माप_प्रकार अंक_masks = WAYLAND_xkb_keymap_कुंजी_get_mods_for_level(seat->keyboard.xkb.keymap, कुंजी, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#अन्यथा
                स्थिर माप_प्रकार अंक_masks = xkb_legacy_get_mods_for_level(seat, कुंजी, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#पूर्ण_अगर
                क्रम (माप_प्रकार mask = 0; mask < अंक_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    अगर ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        जारी;
                    }

                    स्थिर SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_कुंजी_Code_From_कुंजी_Sym(syms[0], कुंजी, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    अगर (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_अग्र_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        अगर (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_कुंजी *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, माप(Wayland_Reserved_कुंजी));
                        अगर (res) {
                            res->scancode = scancode;
                            res->कुंजी = कुंजी - 8;
                        }
                    }

                    अगर (!keycode) {
                        चयन (scancode) {
                        हाल SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            अवरोध;
                        हाल SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            अवरोध;
                        हाल SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            अवरोध;
                        हाल SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            अवरोध;
                        शेष:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            अवरोध;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

अटल व्योम keyboard_handle_keymap(व्योम *तथ्य, काष्ठा wl_keyboard *keyboard,
                                   uint32_t format, पूर्णांक fd, uint32_t आकार)
{
    SDL_WaylandSeat *seat = तथ्य;
    अक्षर *map_str;

    अगर (!तथ्य) {
        बंद(fd);
        वापस;
    }

    अगर (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        बंद(fd);
        वापस;
    }

    map_str = mmap(शून्य, आकार, PROT_READ, MAP_PRIVATE, fd, 0);
    अगर (map_str == MAP_FAILED) {
        बंद(fd);
        वापस;
    }

    अगर (seat->keyboard.xkb.keymap != शून्य) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = शून्य;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, आकार);
    बंद(fd);

    अगर (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        वापस;
    }

    // Clear the old layouts.
    क्रम (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = शून्य;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.अंक_layouts = 0;

#अगर SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.अंक_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_अंक);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#अन्यथा
#घोषणा GET_MOD_सूचकांक(mod) \
    WAYLAND_xkb_keymap_mod_get_सूचकांक(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_सूचकांक(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_सूचकांक(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_सूचकांक(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_सूचकांक(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_सूचकांक(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_सूचकांक(MOD3);
    seat->keyboard.xkb.अंक_mask = 1 << GET_MOD_सूचकांक(अंक_2);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_सूचकांक(CAPS);
#अघोषित GET_MOD_सूचकांक
#पूर्ण_अगर

    अगर (seat->keyboard.xkb.state != शून्य) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = शून्य;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    अगर (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = शून्य;
        वापस;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == शून्य;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.अंक_layouts = WAYLAND_xkb_keymap_अंक_layouts(seat->keyboard.xkb.keymap);
    अगर (seat->keyboard.xkb.अंक_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.अंक_layouts, माप(SDL_Keymap *));
        अगर (!seat->keyboard.sdl_keymap) {
            वापस;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        क्रम (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            अगर (!seat->keyboard.sdl_keymap[i]) {
                क्रम (xkb_layout_सूचकांक_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = शून्य;
                वापस;
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
    स्थिर अक्षर *locale = SDL_getenv("LC_ALL");
    अगर (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        अगर (!locale) {
            locale = SDL_getenv("LANG");
            अगर (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    अगर (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        अगर (seat->keyboard.xkb.compose_table != शून्य) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = शून्य;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        अगर (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            अगर (seat->keyboard.xkb.compose_state != शून्य) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = शून्य;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            अगर (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = शून्य;
            }
        }
    } अन्यथा अगर (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
अटल SDL_Scancode Wayland_Get_Scancode_For_कुंजी(SDL_WaylandSeat *seat, Uint32 कुंजी, स्थिर xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    अगर (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, कुंजी);

        // No table entry? Check the reserved list.
        अगर (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_कुंजी *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                अगर (i->कुंजी == कुंजी) {
                    वापस i->scancode;
                }
            }
        }
    } अन्यथा {
        स्थिर xkb_keysym_t *keysym;
        अगर (WAYLAND_xkb_state_कुंजी_get_syms(seat->keyboard.xkb.state, कुंजी + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_कुंजी_Sym(keysym[0], कुंजी + 8);
            अगर (syms) {
                *syms = keysym;
            }
        }
    }

    वापस scancode;
}

अटल व्योम Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool कुंजी_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    अगर (!कुंजी_pressed) {
        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        अगर (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            अगर (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
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
    स्थिर xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        अगर (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } अन्यथा अगर (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        अगर (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } अन्यथा अगर (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        अगर (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } अन्यथा अगर (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        अगर (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } अन्यथा अगर (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    अगर (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    अगर (xkb_locked_modifiers & seat->keyboard.xkb.अंक_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_अंक;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_अंक;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

अटल व्योम Wayland_Handle_Modifier_कुंजियाँ(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    स्थिर SDL_Keycode keycode = SDL_Get_कुंजी_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    चयन (keycode) {
    हाल SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        अवरोध;
    हाल SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        अवरोध;
    हाल SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        अवरोध;
    हाल SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        अवरोध;
    हाल SDLK_LALT:
        mod = SDL_KMOD_LALT;
        अवरोध;
    हाल SDLK_RALT:
        mod = SDL_KMOD_RALT;
        अवरोध;
    हाल SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        अवरोध;
    हाल SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        अवरोध;
    हाल SDLK_MODE:
        mod = SDL_KMOD_MODE;
        अवरोध;
    हाल SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        अवरोध;
    शेष:
        वापस;
    }

    अगर (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } अन्यथा {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

अटल व्योम keyboard_handle_enter(व्योम *तथ्य, काष्ठा wl_keyboard *keyboard,
                                  uint32_t serial, काष्ठा wl_surface *surface,
                                  काष्ठा wl_array *कुंजियाँ)
{
    SDL_WaylandSeat *seat = तथ्य;
    uint32_t *कुंजी;

    अगर (!surface) {
        // Enter event for a destroyed surface.
        वापस;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_Window_तथ्य *window = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);
    अगर (!window) {
        // Not a surface owned by SDL.
        वापस;
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

#अगर_घोषित SDL_USE_IME
    अगर (!seat->text_निवेश.zwp_text_निवेश) {
        SDL_IME_SetFocus(true);
    }
#पूर्ण_अगर

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (कुंजी, कुंजियाँ) {
        स्थिर SDL_Scancode scancode = Wayland_Get_Scancode_For_कुंजी(seat, *कुंजी, शून्य);
        अगर (scancode != SDL_SCANCODE_UNKNOWN) {
            स्थिर SDL_Keycode keycode = SDL_Get_कुंजी_From_Scancode(scancode, SDL_KMOD_NONE, false);

            चयन (keycode) {
            हाल SDLK_LSHIFT:
            हाल SDLK_RSHIFT:
            हाल SDLK_LCTRL:
            हाल SDLK_RCTRL:
            हाल SDLK_LALT:
            हाल SDLK_RALT:
            हाल SDLK_LGUI:
            हाल SDLK_RGUI:
            हाल SDLK_MODE:
            हाल SDLK_LEVEL5_SHIFT:
                Wayland_Handle_Modifier_कुंजियाँ(seat, scancode, true);
                SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *कुंजी, scancode, true);
                अवरोध;
            शेष:
                अवरोध;
            }
        }
    }
}

अटल व्योम keyboard_handle_leave(व्योम *तथ्य, काष्ठा wl_keyboard *keyboard,
                                  uint32_t serial, काष्ठा wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;

    अगर (!surface) {
        // Leave event for a destroyed surface.
        वापस;
    }

    SDL_Window_तथ्य *window = Wayland_Get_Window_तथ्य_For_Owned_Surface(surface);
    अगर (!window) {
        // Not a surface owned by SDL.
        वापस;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.कुंजी = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    जबतक (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    स्थिर bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = शून्य;
    --window->keyboard_focus_गिनती;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    अगर (!window->keyboard_focus_गिनती && had_focus) {
        SDL_SetKeyboardFocus(शून्य);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_निवेश(seat);

#अगर_घोषित SDL_USE_IME
    अगर (!seat->text_निवेश.zwp_text_निवेश && !window->keyboard_focus_गिनती) {
        SDL_IME_SetFocus(false);
    }
#पूर्ण_अगर

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    अगर (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_गिनती && !window->active_touch_गिनती) {
        SDL_SetMouseFocus(शून्य);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_तथ्य_Device_Set_Selection_Offer(seat->तथ्य_device, शून्य);
}

अटल bool keyboard_निवेश_get_text(अक्षर text[8], स्थिर SDL_WaylandSeat *seat, uint32_t कुंजी, bool down, bool *handled_by_ime)
{
    स्थिर xkb_keysym_t *syms;
    xkb_keysym_t sym;

    अगर (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        वापस false;
    }

    // TODO: Can this happen?
    अगर (WAYLAND_xkb_state_कुंजी_get_syms(seat->keyboard.xkb.state, कुंजी + 8, &syms) != 1) {
        वापस false;
    }
    sym = syms[0];

#अगर_घोषित SDL_USE_IME
    अगर (SDL_IME_Process_कुंजी_Event(sym, कुंजी + 8, down)) {
        अगर (handled_by_ime) {
            *handled_by_ime = true;
        }
        वापस true;
    }
#पूर्ण_अगर

    अगर (!down) {
        वापस false;
    }

    अगर (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        चयन (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        हाल XKB_COMPOSE_COMPOSING:
            अगर (handled_by_ime) {
                *handled_by_ime = true;
            }
            वापस true;
        हाल XKB_COMPOSE_CANCELLED:
        शेष:
            sym = XKB_कुंजी_No_प्रतीक;
            अवरोध;
        हाल XKB_COMPOSE_NOTHING:
            अवरोध;
        हाल XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            अवरोध;
        }
    }

    वापस WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

अटल व्योम keyboard_handle_कुंजी(व्योम *तथ्य, काष्ठा wl_keyboard *keyboard,
                                uint32_t serial, uint32_t समय, uint32_t कुंजी,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = तथ्य;
    क्रमागत wl_keyboard_कुंजी_state state = state_w;
    अक्षर text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    स्थिर Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, समय);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    अगर (state == WL_KEYBOARD_कुंजी_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        अगर (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_कुंजी_repeats(seat->keyboard.xkb.keymap, कुंजी + 8)) {
            वापस;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_कुंजी_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    अगर (state == WL_KEYBOARD_कुंजी_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        अगर (keyboard_focus && SDL_Text_निवेश_Active(keyboard_focus)) {
            has_text = keyboard_निवेश_get_text(text, seat, कुंजी, true, &handled_by_ime);
        }
    } अन्यथा {
        अगर (कुंजी == seat->keyboard.repeat.कुंजी) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            स्थिर Uint64 elapsed = SDL_MS_TO_NS(समय - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.कुंजी = 0;
        }
        keyboard_निवेश_get_text(text, seat, कुंजी, false, &handled_by_ime);
    }

    स्थिर xkb_keysym_t *syms = शून्य;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_कुंजी(seat, कुंजी, &syms);
    Wayland_Handle_Modifier_कुंजियाँ(seat, scancode, state == WL_KEYBOARD_कुंजी_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    अगर (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        स्थिर SDL_Keycode keycode = (SDL_Keycode)SDL_कुंजी_Sym_To_Ucs4(syms[0]);
        अगर (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            अगर (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_Get_Keymap_अग्र_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_कुंजी_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, कुंजी, scancode, state == WL_KEYBOARD_कुंजी_STATE_PRESSED);

    अगर (state == WL_KEYBOARD_कुंजी_STATE_PRESSED) {
        अगर (handled_by_ime) {
            has_text = false;
        }
        अगर (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        अगर (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_कुंजी_repeats(seat->keyboard.xkb.keymap, कुंजी + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, कुंजी, समय, timestamp_ns, scancode, has_text ? text : शून्य);
        }
    }
}

अटल व्योम keyboard_handle_modifiers(व्योम *तथ्य, काष्ठा wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = तथ्य;
    स्थिर uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    अगर (!seat->keyboard.xkb.state) {
        वापस;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    अगर (seat->keyboard.repeat.कुंजी) {
        अक्षर text[8];

        अगर (keyboard_निवेश_get_text(text, seat, seat->keyboard.repeat.कुंजी, true, शून्य)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    अगर (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        अगर (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

अटल व्योम keyboard_handle_repeat_info(व्योम *तथ्य, काष्ठा wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = तथ्य;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    अगर (!rate) {
        seat->keyboard.repeat.कुंजी = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

अटल स्थिर काष्ठा wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_कुंजी,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

अटल व्योम Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    अगर (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    अगर (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = शून्य;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    अगर (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    अगर (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    अगर (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    अगर (seat->pointer.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    अगर (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    अगर (seat->pointer.wl_pointer) {
        अगर (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } अन्यथा {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

अटल व्योम Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    अगर (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    अगर (seat->keyboard.sdl_keymap) {
        अगर (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अंक_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        क्रम (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अंक_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = शून्य;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    अगर (seat->keyboard.कुंजी_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुंजी_inhibitor);
    }

    अगर (seat->keyboard.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    अगर (seat->keyboard.wl_keyboard) {
        अगर (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } अन्यथा {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    अगर (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    अगर (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    अगर (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    अगर (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

अटल व्योम Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    अगर (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    अगर (seat->touch.timestamps) {
        zwp_निवेश_timestamps_v1_destroy(seat->touch.timestamps);
    }

    अगर (seat->touch.wl_touch) {
        अगर (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } अन्यथा {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

अटल व्योम seat_handle_capabilities(व्योम *तथ्य, काष्ठा wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    अक्षर name_fmt[256];

    अगर ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_तथ्य(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_Get_अग्र_Object_ID();

        अगर (seat->name) {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } अन्यथा अगर (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    अगर ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_तथ्य(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        अगर (seat->name) {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } अन्यथा अगर (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    अगर ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_तथ्य(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_अग्र_Object_ID();

        अगर (seat->name) {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, माप(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } अन्यथा अगर (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_Register_निवेश_Timestamp_Listeners(seat);
}

अटल व्योम seat_handle_name(व्योम *तथ्य, काष्ठा wl_seat *wl_seat, स्थिर अक्षर *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;

    अगर (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

अटल स्थिर काष्ठा wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

अटल व्योम तथ्य_offer_handle_offer(व्योम *तथ्य, काष्ठा wl_तथ्य_offer *wl_तथ्य_offer,
                                    स्थिर अक्षर *mime_type)
{
    SDL_Wayland_तथ्य_Offer *offer = तथ्य;
    Wayland_तथ्य_Offer_Add_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_तथ्य_offer ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)wl_तथ्य_offer) : -1),
                 mime_type);
}

अटल व्योम तथ्य_offer_handle_source_actions(व्योम *तथ्य, काष्ठा wl_तथ्य_offer *wl_तथ्य_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_तथ्य_offer ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)wl_तथ्य_offer) : -1),
                 source_actions);
}

अटल व्योम तथ्य_offer_handle_actions(व्योम *तथ्य, काष्ठा wl_तथ्य_offer *wl_तथ्य_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_तथ्य_offer ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)wl_तथ्य_offer) : -1),
                 dnd_action);
}

अटल स्थिर काष्ठा wl_तथ्य_offer_listener तथ्य_offer_listener = {
    तथ्य_offer_handle_offer,
    तथ्य_offer_handle_source_actions, // Version 3
    तथ्य_offer_handle_actions,        // Version 3
};

अटल व्योम primary_selection_offer_handle_offer(व्योम *तथ्य, काष्ठा zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 स्थिर अक्षर *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = तथ्य;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

अटल स्थिर काष्ठा zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

अटल व्योम तथ्य_device_handle_तथ्य_offer(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device,
                                          काष्ठा wl_तथ्य_offer *id)
{
    SDL_Wayland_तथ्य_Offer *तथ्य_offer = SDL_calloc(1, माप(*तथ्य_offer));
    अगर (तथ्य_offer) {
        SDL_Wayland_तथ्य_Device *तथ्य_device = (SDL_Wayland_तथ्य_Device *)तथ्य;
        तथ्य_offer->offer = id;
        तथ्य_offer->तथ्य_device = तथ्य_device;
        तथ्य_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(तथ्य_offer->mimes));
        wl_तथ्य_offer_set_user_तथ्य(id, तथ्य_offer);
        wl_तथ्य_offer_add_listener(id, &तथ्य_offer_listener, तथ्य_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id) : -1));
    }
}

अटल व्योम तथ्य_device_handle_enter(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device,
                                     uint32_t serial, काष्ठा wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, काष्ठा wl_तथ्य_offer *id)
{
    SDL_Wayland_तथ्य_Device *तथ्य_device = तथ्य;
    SDL_Window_तथ्य *window = surface ? Wayland_Get_Window_तथ्य_For_Owned_Surface(surface) : शून्य;
    तथ्य_device->has_mime_file = false;
    तथ्य_device->text_mime_type = शून्य;

    तथ्य_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    अगर (id) {
        तथ्य_device->drag_offer = wl_तथ्य_offer_get_user_तथ्य(id);
    }

    अगर (तथ्य_device->drag_offer && window && window->accepts_drag_and_drop) {
#अगर_घोषित SDL_USE_LIBDBUS
        अगर (Wayland_तथ्य_Offer_Has_MIME(तथ्य_device->drag_offer, FILE_PORTAL_MIME)) {
            तथ्य_device->has_mime_file = true;
            wl_तथ्य_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#पूर्ण_अगर
        अगर (Wayland_तथ्य_Offer_Has_MIME(तथ्य_device->drag_offer, FILE_MIME)) {
            तथ्य_device->has_mime_file = true;
            wl_तथ्य_offer_accept(id, serial, FILE_MIME);
        }

        अगर (!तथ्य_device->has_mime_file) {
            माप_प्रकार mime_गिनती = 0;
            स्थिर अक्षर *स्थिर *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_गिनती);
            क्रम (माप_प्रकार i = 0; i < mime_गिनती; ++i) {
                अगर (Wayland_तथ्य_Offer_Has_MIME(तथ्य_device->drag_offer, text_mime_types[i])) {
                    तथ्य_device->text_mime_type = text_mime_types[i];
                    wl_तथ्य_offer_accept(id, serial, text_mime_types[i]);
                    अवरोध;
                }
            }
        }

        अगर (तथ्य_device->has_mime_file || तथ्य_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            अगर (wl_तथ्य_offer_get_version(तथ्य_device->drag_offer->offer) >= WL_तथ्य_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_तथ्य_offer_set_actions(तथ्य_device->drag_offer->offer, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_COPY, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            तथ्य_device->dnd_window = window->sdlwindow;
            तथ्य_device->dnd_surface = surface;
            द्विगुन dx = wl_fixed_to_double(x);
            द्विगुन dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            अगर (surface == window->mask.surface) {
                dx += (द्विगुन)window->mask.offset_x;
                dy += (द्विगुन)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(तथ्य_device->dnd_window, (भग्न)dx, (भग्न)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(तथ्य_device->dnd_window), serial);
        } अन्यथा {
            // Decline the offer.
            wl_तथ्य_offer_accept(id, serial, शून्य);
            अगर (wl_तथ्य_offer_get_version(तथ्य_device->drag_offer->offer) >= WL_तथ्य_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_तथ्य_offer_set_actions(तथ्य_device->drag_offer->offer, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_NONE, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } अन्यथा {
        तथ्य_device->dnd_window = शून्य;
        तथ्य_device->dnd_surface = शून्य;

        // Decline the offer.
        अगर (id) {
            wl_तथ्य_offer_accept(id, serial, शून्य);
            अगर (wl_तथ्य_offer_get_version(तथ्य_device->drag_offer->offer) >= WL_तथ्य_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_तथ्य_offer_set_actions(तथ्य_device->drag_offer->offer, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_NONE, WL_तथ्य_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

अटल व्योम तथ्य_device_handle_leave(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device)
{
    SDL_Wayland_तथ्य_Device *तथ्य_device = तथ्य;

    अगर (तथ्य_device->drag_offer) {
        अगर (तथ्य_device->dnd_window) {
            SDL_SendDropComplete(तथ्य_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)तथ्य_device->drag_offer->offer),
                         SDL_GetWindowID(तथ्य_device->dnd_window), तथ्य_device->drag_serial);
        } अन्यथा {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)तथ्य_device->drag_offer->offer),
                         तथ्य_device->drag_serial);
        }
        Wayland_तथ्य_Offer_Destroy(तथ्य_device->drag_offer);
        तथ्य_device->drag_offer = शून्य;
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    तथ्य_device->has_mime_file = false;
    तथ्य_device->text_mime_type = शून्य;
}

अटल व्योम तथ्य_device_handle_motion(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device,
                                      uint32_t समय, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_तथ्य_Device *तथ्य_device = तथ्य;

    अगर (तथ्य_device->drag_offer && तथ्य_device->dnd_window && (तथ्य_device->has_mime_file || तथ्य_device->text_mime_type)) {
        SDL_Window_तथ्य *window_तथ्य_2 = तथ्य_device->dnd_window->internal;
        द्विगुन dx = wl_fixed_to_double(x);
        द्विगुन dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        अगर (तथ्य_device->dnd_surface == window_तथ्य_2->mask.surface) {
            dx += (द्विगुन)window_तथ्य_2->mask.offset_x;
            dy += (द्विगुन)window_तथ्य_2->mask.offset_y;
        }

        dx *= window_तथ्य_2->pointer_scale.x;
        dy *= window_तथ्य_2->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(तथ्य_device->dnd_window, (भग्न)dx, (भग्न)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)तथ्य_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(तथ्य_device->dnd_window), तथ्य_device->drag_serial);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

अटल व्योम drop_cleanup_handler(व्योम *तथ्य, काष्ठा wl_callback *callback, uint32_t callback_तथ्य)
{
    Wayland_Drop_तथ्य *drop = (Wayland_Drop_तथ्य *)तथ्य;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

अटल स्थिर काष्ठा wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

अटल व्योम drop_dispatch_handler(व्योम *तथ्य)
{
    Wayland_Drop_तथ्य *drop = (Wayland_Drop_तथ्य *)तथ्य;
    SDL_Wayland_तथ्य_Offer *offer = drop->offer;
    SDL_Wayland_तथ्य_Device *तथ्य_device = offer->तथ्य_device;

    अगर (drop->dnd_window) {
        माप_प्रकार लंबाई;
        bool drop_handled = false;

#अगर_घोषित SDL_USE_LIBDBUS
        अगर (Wayland_तथ्य_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            व्योम *बफर_2 = Wayland_तथ्य_Offer_Receive(offer, FILE_PORTAL_MIME, &लंबाई);
            अगर (बफर_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                अगर (dbus) {
                    पूर्णांक path_गिनती = 0;
                    अक्षर **paths = SDL_DBus_DocumentsPortalRetrieveFiles(बफर_2, &path_गिनती);
                    // If dropped files contain a directory the list is empty
                    अगर (paths && path_गिनती > 0) {
                        क्रम (पूर्णांक i = 0; i < path_गिनती; i++) {
                            SDL_SendDropFile(drop->dnd_window, शून्य, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(बफर_2);
            }
        }
#पूर्ण_अगर
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        अगर (!drop_handled) {
            अगर (Wayland_तथ्य_Offer_Has_MIME(offer, FILE_MIME)) {
                व्योम *बफर_2 = Wayland_तथ्य_Offer_Receive(offer, FILE_MIME, &लंबाई);
                अगर (बफर_2) {
                    अक्षर *saveptr = शून्य;
                    अक्षर *token = SDL_strtok_r((अक्षर *)बफर_2, "\r\n", &saveptr);
                    जबतक (token) {
                        अगर (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, शून्य, token);
                        }
                        token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                    }
                    SDL_free(बफर_2);
                    drop_handled = true;
                }
            } अन्यथा अगर (Wayland_तथ्य_Offer_Has_MIME(offer, drop->text_mime_type)) {
                व्योम *बफर_2 = Wayland_तथ्य_Offer_Receive(offer, drop->text_mime_type, &लंबाई);
                अगर (बफर_2) {
                    अक्षर *saveptr = शून्य;
                    अक्षर *token = SDL_strtok_r((अक्षर *)बफर_2, "\r\n", &saveptr);
                    जबतक (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(शून्य, "\r\n", &saveptr);
                    }
                    SDL_free(बफर_2);
                    drop_handled = true;
                }
            }
        }

        अगर (drop_handled && wl_तथ्य_offer_get_version(offer->offer) >= WL_तथ्य_OFFER_FINISH_SINCE_VERSION) {
            wl_तथ्य_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_तथ्य_Offer_Destroy(drop->offer);
    drop->offer = शून्य;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(तथ्य_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

अटल व्योम तथ्य_device_handle_drop(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device)
{
    SDL_Wayland_तथ्य_Device *तथ्य_device = तथ्य;

    अगर (तथ्य_device->drag_offer && तथ्य_device->dnd_window &&
        (तथ्य_device->has_mime_file || तथ्य_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)तथ्य_device->drag_offer->offer),
                     SDL_GetWindowID(तथ्य_device->dnd_window), तथ्य_device->drag_serial);

        Wayland_JobThreadContext *ctx = तथ्य_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_तथ्य *drop = SDL_calloc(1, माप(Wayland_Drop_तथ्य));
        अगर (drop) {
            drop->offer = तथ्य_device->drag_offer;
            drop->dnd_window = तथ्य_device->dnd_window;
            drop->text_mime_type = तथ्य_device->text_mime_type;

            WAYLAND_wl_list_जोड़ो(&तथ्य_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } अन्यथा {
            Wayland_तथ्य_Offer_Destroy(तथ्य_device->drag_offer);
        }
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_तथ्य_Offer_Destroy(तथ्य_device->drag_offer);
    }

    तथ्य_device->drag_offer = शून्य;
}

अटल व्योम तथ्य_device_handle_selection(व्योम *तथ्य, काष्ठा wl_तथ्य_device *wl_तथ्य_device,
                                         काष्ठा wl_तथ्य_offer *id)
{
    SDL_Wayland_तथ्य_Device *तथ्य_device = तथ्य;
    SDL_Wayland_तथ्य_Offer *offer = शून्य;

    अगर (id) {
        offer = wl_तथ्य_offer_get_user_तथ्य(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id) : -1));

    Wayland_तथ्य_Device_Set_Selection_Offer(तथ्य_device, offer);
}

अटल स्थिर काष्ठा wl_तथ्य_device_listener तथ्य_device_listener = {
    तथ्य_device_handle_तथ्य_offer,
    तथ्य_device_handle_enter,
    तथ्य_device_handle_leave,
    तथ्य_device_handle_motion,
    तथ्य_device_handle_drop,
    तथ्य_device_handle_selection
};

अटल व्योम primary_selection_device_handle_offer(व्योम *तथ्य, काष्ठा zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  काष्ठा zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, माप(*primary_selection_offer));
    अगर (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)तथ्य;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_तथ्य(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id) : -1));
}

अटल व्योम primary_selection_device_handle_selection(व्योम *तथ्य, काष्ठा zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      काष्ठा zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = तथ्य;
    SDL_WaylandPrimarySelectionOffer *offer = शून्य;

    अगर (id) {
        offer = zwp_primary_selection_offer_v1_get_user_तथ्य(id);
    }

    अगर (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((काष्ठा wl_proxy *)id) : -1));
}

अटल स्थिर काष्ठा zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

अटल व्योम text_निवेश_enter(व्योम *तथ्य,
                             काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                             काष्ठा wl_surface *surface)
{
    // No-op
}

अटल व्योम text_निवेश_leave(व्योम *तथ्य,
                             काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                             काष्ठा wl_surface *surface)
{
    // No-op
}

अटल व्योम text_निवेश_preedit_string(व्योम *तथ्य,
                                      काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                      स्थिर अक्षर *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    seat->text_निवेश.has_preedit = true;
    अगर (text) {
        पूर्णांक cursor_begin_utf8 = cursor_begin >= 0 ? (पूर्णांक)SDL_utf8strnlen(text, cursor_begin) : -1;
        पूर्णांक cursor_end_utf8 = cursor_end >= 0 ? (पूर्णांक)SDL_utf8strnlen(text, cursor_end) : -1;
        पूर्णांक cursor_आकार_utf8;
        अगर (cursor_end_utf8 >= 0) {
            अगर (cursor_begin_utf8 >= 0) {
                cursor_आकार_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } अन्यथा {
                cursor_आकार_utf8 = cursor_end_utf8;
            }
        } अन्यथा {
            cursor_आकार_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_आकार_utf8);
    } अन्यथा {
        SDL_SendEditingText("", 0, 0);
    }
}

अटल व्योम text_निवेश_commit_string(व्योम *तथ्य,
                                     काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                     स्थिर अक्षर *text)
{
    SDL_SendKeyboardText(text);
}

अटल व्योम text_निवेश_delete_surrounding_text(व्योम *तथ्य,
                                               काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                                               uint32_t before_लंबाई,
                                               uint32_t after_लंबाई)
{
    // FIXME: Do we care about this event?
}

अटल व्योम text_निवेश_done(व्योम *तथ्य,
                            काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    अगर (!seat->text_निवेश.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_निवेश.has_preedit = false;
}

अटल स्थिर काष्ठा zwp_text_निवेश_v3_listener text_निवेश_listener = {
    text_निवेश_enter,
    text_निवेश_leave,
    text_निवेश_preedit_string,
    text_निवेश_commit_string,
    text_निवेश_delete_surrounding_text,
    text_निवेश_done
};

अटल व्योम Wayland_तथ्य_Device_Set_ID(SDL_Wayland_तथ्य_Device *तथ्य_device)
{
    अगर (!तथ्य_device->id_str)
#अगर_घोषित SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        अगर (dbus) {
            स्थिर अक्षर *id = dbus->bus_get_unique_name(dbus->session_conn);
            अगर (id) {
                तथ्य_device->id_str = SDL_strdup(id);
            }
        }
    }
    अगर (!तथ्य_device->id_str)
#पूर्ण_अगर
    {
        अक्षर id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, माप(id), "%" SDL_PRIu64, pid);
        तथ्य_device->id_str = SDL_strdup(id);
    }
}

अटल व्योम Wayland_Seat_Create_तथ्य_Device(SDL_WaylandSeat *seat)
{
    अगर (!seat->display->तथ्य_device_manager) {
        वापस;
    }

    SDL_Wayland_तथ्य_Device *तथ्य_device = SDL_calloc(1, माप(*तथ्य_device));
    अगर (!तथ्य_device) {
        वापस;
    }

    तथ्य_device->तथ्य_device = wl_तथ्य_device_manager_get_तथ्य_device(
        seat->display->तथ्य_device_manager, seat->wl_seat);
    तथ्य_device->seat = seat;

    अगर (!तथ्य_device->तथ्य_device) {
        SDL_free(तथ्य_device);
        वापस;
    }

    Wayland_तथ्य_Device_Set_ID(तथ्य_device);
    WAYLAND_wl_list_init(&तथ्य_device->pending_drops);
    wl_तथ्य_device_set_user_तथ्य(तथ्य_device->तथ्य_device, तथ्य_device);
    wl_तथ्य_device_add_listener(तथ्य_device->तथ्य_device, &तथ्य_device_listener, तथ्य_device);
    seat->तथ्य_device = तथ्य_device;
}

व्योम Wayland_Display_Init_तथ्य_Device_Manager(SDL_Video_तथ्य *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_तथ्य_Device(seat);
    }
}

अटल व्योम Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    अगर (!seat->display->primary_selection_device_manager) {
        वापस;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, माप(*primary_selection_device));
    अगर (!primary_selection_device) {
        वापस;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    अगर (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } अन्यथा {
        zwp_primary_selection_device_v1_set_user_तथ्य(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

व्योम Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_तथ्य *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

अटल व्योम Wayland_Seat_Create_Text_निवेश(SDL_WaylandSeat *seat)
{
    अगर (seat->display->text_निवेश_manager) {
        seat->text_निवेश.zwp_text_निवेश = zwp_text_निवेश_manager_v3_get_text_निवेश(seat->display->text_निवेश_manager, seat->wl_seat);

        अगर (seat->text_निवेश.zwp_text_निवेश) {
            zwp_text_निवेश_v3_set_user_तथ्य(seat->text_निवेश.zwp_text_निवेश, seat);
            zwp_text_निवेश_v3_add_listener(seat->text_निवेश.zwp_text_निवेश,
                                           &text_निवेश_listener, seat);
        }
    }
}

व्योम Wayland_Display_Init_Text_निवेश_Manager(SDL_Video_तथ्य *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_निवेश(seat);
    }
}

// Pen/Tablet support...
अटल व्योम tablet_tool_handle_type(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    चयन (type) {
        #घोषणा CASE(typ) हाल ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; वापस
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #अघोषित CASE
        शेष: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

अटल व्योम tablet_tool_handle_hardware_serial(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

अटल व्योम tablet_tool_handle_hardware_id_wacom(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->info.wacom_id = id_lo;
}

अटल व्योम tablet_tool_handle_capability(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    चयन (capability) {
        #घोषणा CASE(wltyp,sdltyp) हाल ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; वापस
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #अघोषित CASE
        शेष: अवरोध;  // unsupported here.
    }
}

अटल व्योम tablet_tool_handle_done(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    अगर (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : शून्य;
        sdltool->instance_id = SDL_AddPenDevice(0, शून्य, window, &sdltool->info, sdltool, false);
    }
}

अटल व्योम tablet_tool_handle_removed(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    अगर (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : शून्य;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

अटल व्योम tablet_tool_handle_proximity_in(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t serial, काष्ठा zwp_tablet_v2 *tablet, काष्ठा wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    SDL_Window_तथ्य *windowdata = surface ? Wayland_Get_Window_तथ्य_For_Owned_Surface(surface) : शून्य;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : शून्य;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

अटल व्योम tablet_tool_handle_proximity_out(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

अटल व्योम tablet_tool_handle_down(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

अटल व्योम tablet_tool_handle_up(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

अटल व्योम tablet_tool_handle_motion(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    SDL_Window_तथ्य *windowdata = sdltool->focus;
    अगर (windowdata) {
        sdltool->frame.x = (भग्न)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (भग्न)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

अटल व्योम tablet_tool_handle_pressure(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((भग्न) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    अगर (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

अटल व्योम tablet_tool_handle_distance(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((भग्न) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    अगर (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

अटल व्योम tablet_tool_handle_tilt(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (भग्न)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (भग्न)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

अटल व्योम tablet_tool_handle_button(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    पूर्णांक sdlbutton;

    चयन (button) {
    हाल BTN_STYLUS:
        sdlbutton = 1;
        अवरोध;
    हाल BTN_STYLUS2:
        sdlbutton = 2;
        अवरोध;
    हाल BTN_STYLUS3:
        sdlbutton = 3;
        अवरोध;
    शेष:
        वापस;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

अटल व्योम tablet_tool_handle_rotation(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    स्थिर भग्न rotation = (भग्न)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

अटल व्योम tablet_tool_handle_slider(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

अटल व्योम tablet_tool_handle_wheel(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

अटल व्योम tablet_tool_handle_frame(व्योम *तथ्य, काष्ठा zwp_tablet_tool_v2 *tool, uint32_t समय)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) तथ्य;
    स्थिर SDL_PenID instance_id = sdltool->instance_id;
    अगर (!instance_id) {
        वापस;  // Not a pen we report on.
    }

    स्थिर Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(समय));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : शून्य;
    स्थिर bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    अगर (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    अगर (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        अगर (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } अन्यथा {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } अन्यथा {
        अगर (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        अगर (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    क्रम (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_गिनती; i++) {
        अगर (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    क्रम (पूर्णांक i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        स्थिर पूर्णांक state = sdltool->frame.buttons[i];
        अगर (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    अगर (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = शून्य;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

अटल स्थिर काष्ठा zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


अटल व्योम tablet_seat_handle_tablet_added(व्योम *तथ्य, काष्ठा zwp_tablet_seat_v2 *zwp_tablet_seat_v2, काष्ठा zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

अटल व्योम tablet_seat_handle_tool_added(व्योम *तथ्य, काष्ठा zwp_tablet_seat_v2 *zwp_tablet_seat_v2, काष्ठा zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)तथ्य;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, माप(*sdltool));

    अगर (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.अंक_buttons = -1;

        अगर (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_जोड़ो(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

अटल व्योम tablet_seat_handle_pad_added(व्योम *तथ्य, काष्ठा zwp_tablet_seat_v2 *zwp_tablet_seat_v2, काष्ठा zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

अटल स्थिर काष्ठा zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

अटल व्योम Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

व्योम Wayland_DisplayInitTabletManager(SDL_Video_तथ्य *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

अटल व्योम Wayland_remove_all_pens_callback(SDL_PenID instance_id, व्योम *handle, व्योम *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

अटल व्योम Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    अगर (!shutting_down) {
        SDL_WaylandPenTool *tool, *अस्थायी;
        wl_list_for_each_safe (tool, अस्थायी, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } अन्यथा {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, शून्य);
    }

    अगर (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = शून्य;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

व्योम Wayland_DisplayCreateSeat(SDL_Video_तथ्य *display, काष्ठा wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, माप(SDL_WaylandSeat));
    अगर (!seat) {
        वापस;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_जोड़ो(display->seat_list.पूर्व, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_तथ्य_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_निवेश(seat);

    wl_seat_set_user_तथ्य(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    अगर (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

व्योम Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        अगर (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        अगर (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = शून्य;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *अस्थायी;
        wl_list_for_each_safe (tp, अस्थायी, &seat->touch.points, link) {
            अगर (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            अगर (tool->focus == window) {
                tool->focus = शून्य;
                Wayland_TabletToolUpdateCursor(tool);
                अगर (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_तथ्य *drop, *drop_अस्थायी;
        wl_list_for_each_safe (drop, drop_अस्थायी, &seat->तथ्य_device->pending_drops, link) {
            अगर (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                अगर (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_तथ्य_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

व्योम Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    अगर (!seat) {
        वापस;
    }

    SDL_free(seat->name);

    अगर (seat->तथ्य_device) {
        अगर (seat->तथ्य_device->selection_offer) {
            Wayland_तथ्य_Offer_Destroy(seat->तथ्य_device->selection_offer);
        }
        अगर (seat->तथ्य_device->selection_source) {
            Wayland_तथ्य_Source_Destroy(seat->तथ्य_device->selection_source);
        }
        अगर (seat->तथ्य_device->drag_offer) {
            Wayland_तथ्य_Offer_Destroy(seat->तथ्य_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_तथ्य *drop, *drop_अस्थायी;
        wl_list_for_each_safe (drop, drop_अस्थायी, &seat->तथ्य_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            अगर (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_तथ्य_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        अगर (seat->तथ्य_device->तथ्य_device) {
            अगर (wl_तथ्य_device_get_version(seat->तथ्य_device->तथ्य_device) >= WL_तथ्य_DEVICE_RELEASE_SINCE_VERSION) {
                wl_तथ्य_device_release(seat->तथ्य_device->तथ्य_device);
            } अन्यथा {
                wl_तथ्य_device_destroy(seat->तथ्य_device->तथ्य_device);
            }
        }
        SDL_free(seat->तथ्य_device->id_str);
        SDL_free(seat->तथ्य_device);
    }

    अगर (seat->primary_selection_device) {
        अगर (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        अगर (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        अगर (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    अगर (seat->text_निवेश.zwp_text_निवेश) {
        zwp_text_निवेश_v3_destroy(seat->text_निवेश.zwp_text_निवेश);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    अगर (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } अन्यथा {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

अटल व्योम Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    अगर (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        अगर (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            अगर (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                अगर (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } अन्यथा {
                    relative_focus = seat->pointer.focus->keyboard_focus_गिनती != 0;
                }
            } अन्यथा {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        अगर (relative_focus) {
            अगर (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } अन्यथा अगर (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = शून्य;
        }
    }
}

अटल व्योम Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_तथ्य *display = seat->display;

    अगर (display->कुंजी_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        अगर (seat->keyboard.कुंजी_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुंजी_inhibitor);
            seat->keyboard.कुंजी_inhibitor = शून्य;
        }

        अगर (seat->keyboard.wl_keyboard) {
            SDL_Window_तथ्य *w = seat->keyboard.focus;
            अगर (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                अगर (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.कुंजी_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->कुंजी_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

व्योम Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_तथ्य *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    अगर (display->pointer_constraints) {
        अगर (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = शून्य;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        अगर (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            अगर (seat->pointer.relative_pointer) {
                अगर (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    अगर (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = शून्य;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, शून्य,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                वापस;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            अगर (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = शून्य;
            }

            SDL_Window_तथ्य *w = seat->pointer.focus;
            अगर (!w) {
                वापस;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            अगर (!(window->flags & SDL_WINDOW_निवेश_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                वापस;
            }

            काष्ठा wl_region *confine_rect = शून्य;
            अगर (!SDL_RectEmpty(&window->mouse_rect)) {
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
                अगर (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    पूर्णांक closest_x = seat->pointer.last_motion.x;
                    पूर्णांक closest_y = seat->pointer.last_motion.y;

                    अगर (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } अन्यथा अगर (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    अगर (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } अन्यथा अगर (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            अगर (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                अगर (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
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
                                                                शून्य,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                अगर (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

व्योम Wayland_DisplayUpdatePointerGrabs(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        अगर (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

व्योम Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        अगर (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

व्योम Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    अगर (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
