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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

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

#यदि_परिभाषितम् HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#यदि_अन्तः

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
#अन्तर्भाव <linux/input.h>
#अन्यथा
#परिभाषय BTN_वामः    (0x110)
#परिभाषय BTN_दक्षिणः   (0x111)
#परिभाषय BTN_मध्यः  (0x112)
#परिभाषय BTN_SIDE    (0x113)
#परिभाषय BTN_EXTRA   (0x114)
#परिभाषय BTN_STYLUS  (0x14b)
#परिभाषय BTN_STYLUS2 (0x14c)
#परिभाषय BTN_STYLUS3 (0x149)
#यदि_अन्तः
#अन्तर्भाव "../../events/SDL_keysym_to_scancode_c.h"
#अन्तर्भाव "../../events/imKStoUCS.h"
#अन्तर्भाव <errno.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <xkbcommon/xkbcommon-compose.h>
#अन्तर्भाव <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#परिभाषय WAYLAND_WHEEL_AXIS_UNIT 10

#यदि_अपरिभाषितम् XKB_MOD_NAME_MOD3
#परिभाषय XKB_MOD_NAME_MOD3 "Mod3"
#यदि_अन्तः

#यदि_अपरिभाषितम् XKB_MOD_NAME_MOD5
#परिभाषय XKB_MOD_NAME_MOD5 "Mod5"
#यदि_अन्तः

// Keyboard and mouse names to match XWayland
#परिभाषय WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#परिभाषय WAYLAND_DEFAULT_POINTER_NAME "Virtual core pointer"
#परिभाषय WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#परिभाषय WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_गन्तव्यम्_NS(10)

// Timer rollover detection thresholds
#परिभाषय WAYLAND_TIMER_ROLLOVER_INTERVAL_नीचः  (SDL_MAX_UINT32 / 16U)
#परिभाषय WAYLAND_TIMER_ROLLOVER_INTERVAL_उच्चः (WAYLAND_TIMER_ROLLOVER_INTERVAL_नीचः * 15U)

// Scoped function declarations
स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

प्रकारनिर्देश संरचना
{
    Uint32 कुञ्चिका;
    SDL_Scancode scancode;
} Wayland_Reserved_कुञ्चिका;

प्रकारनिर्देश संरचना
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    संरचना wl_surface *surface;

    संरचना wl_list link;
} SDL_WaylandTouchPoint;

स्थिर शून्य Wayland_Seat_सङ्कलय_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, संरचना wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(परिमाण(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_निवेशय(&seat->touch.points, &tp->link);
}

स्थिर शून्य Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    यदि (tp->surface) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(tp->surface);

        यदि (गवाक्षः_दत्त_2) {
            ध्रुव भिन्न x = (भिन्न)(wl_fixed_गन्तव्यम्_double(tp->fx) / गवाक्षः_दत्त_2->current.logical_विस्तारः);
            ध्रुव भिन्न y = (भिन्न)(wl_fixed_गन्तव्यम्_double(tp->fy) / गवाक्षः_दत्त_2->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), गवाक्षः_दत्त_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --गवाक्षः_दत्त_2->सक्रिय_touch_गणनम्;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            यदि (SDL_GetMouseFocus() == गवाक्षः_दत्त_2->sdlwindow && !गवाक्षः_दत्त_2->keyboard_focus_गणनम् &&
                !गवाक्षः_दत्त_2->pointer_focus_गणनम् && !गवाक्षः_दत्त_2->सक्रिय_touch_गणनम्) {
                SDL_समुच्चयः_Mouse_Focus(रिक्त);
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

स्थिर शून्य Wayland_GetScaledMouseRect(SDL_गवाक्षः *गवाक्षः, SDL_Rect *scaled_rect)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = गवाक्षः->आन्तरिकम्;

    scaled_rect->x = (पूर्णाङ्क)SDL_floor(गवाक्षः->mouse_rect.x / गवाक्षः_दत्त_2->pointer_scale.x);
    scaled_rect->y = (पूर्णाङ्क)SDL_floor(गवाक्षः->mouse_rect.y / गवाक्षः_दत्त_2->pointer_scale.y);
    scaled_rect->w = (पूर्णाङ्क)SDL_ceil(गवाक्षः->mouse_rect.w / गवाक्षः_दत्त_2->pointer_scale.x);
    scaled_rect->h = (पूर्णाङ्क)SDL_ceil(गवाक्षः->mouse_rect.h / गवाक्षः_दत्त_2->pointer_scale.y);
}

स्थिर Uint64 Wayland_Adjust_Event_Timestamp_आधारः(Uint64 nsTimestamp)
{
    स्थिर Uint64 timestamp_विस्थापनम् = 0;
    ध्रुव Uint64 now = SDL_GetTicksNS();

    यदि (!timestamp_विस्थापनम्) {
        timestamp_विस्थापनम् = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_विस्थापनम्;

    यदि (nsTimestamp > now) {
        timestamp_विस्थापनम् -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    प्रत्यागम nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
स्थिर Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    स्थिर Uint64 timestamp_विस्थापनम् = 0;
    स्थिर Uint32 चरमः = 0;
    Uint64 timestamp = SDL_MS_गन्तव्यम्_NS(wl_timestamp_ms) + timestamp_विस्थापनम्;

    यदि (wl_timestamp_ms >= चरमः) {
        यदि (timestamp_विस्थापनम् && चरमः < WAYLAND_TIMER_ROLLOVER_INTERVAL_नीचः && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_उच्चः) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_गन्तव्यम्_NS(SDL_UINT64_C(0x100000000));
        } अन्यथा {
            चरमः = wl_timestamp_ms;
        }
    } अन्यथा {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        यदि (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_नीचः && चरमः > WAYLAND_TIMER_ROLLOVER_INTERVAL_उच्चः) {
            timestamp_विस्थापनम् += SDL_MS_गन्तव्यम्_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_गन्तव्यम्_NS(SDL_UINT64_C(0x100000000));
            चरमः = wl_timestamp_ms;
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
    प्रत्यागम Wayland_Adjust_Event_Timestamp_आधारः(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ध्रुव Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    प्रत्यागम Wayland_Adjust_Event_Timestamp_आधारः(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ध्रुव Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    प्रत्यागम Wayland_Adjust_Event_Timestamp_आधारः(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

स्थिर शून्य निवेशः_timestamp_listener(शून्य *दत्त, संरचना zwp_निवेशः_timestamps_v1 *zwp_निवेशः_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)दत्त) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_प्रत्येकम्_SECOND) + tv_nsec;
}

स्थिर ध्रुव संरचना zwp_निवेशः_timestamps_v1_listener timestamp_listener = {
    निवेशः_timestamp_listener
};

स्थिर शून्य Wayland_Seat_पञ्जिकाकोशः_निवेशः_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    यदि (seat->display->निवेशः_timestamps_manager) {
        यदि (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_निवेशः_timestamps_manager_v1_get_keyboard_timestamps(seat->display->निवेशः_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_निवेशः_timestamps_v1_सङ्कलय_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        यदि (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_निवेशः_timestamps_manager_v1_get_pointer_timestamps(seat->display->निवेशः_timestamps_manager, seat->pointer.wl_pointer);
            zwp_निवेशः_timestamps_v1_सङ्कलय_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        यदि (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_निवेशः_timestamps_manager_v1_get_touch_timestamps(seat->display->निवेशः_timestamps_manager, seat->touch.wl_touch);
            zwp_निवेशः_timestamps_v1_सङ्कलय_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

शून्य Wayland_Display_Init_निवेशः_Timestamp_Manager(SDL_Video_दत्त *display)
{
    यदि (display->निवेशः_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_पञ्जिकाकोशः_निवेशः_Timestamp_Listeners(seat);
        }
    }
}

स्थिर शून्य handle_pinch_begin(शून्य *दत्त, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, संरचना wl_surface *surface, uint32_t fingers)
{
    यदि (!surface) {
        प्रत्यागम;
    }

    SDL_गवाक्षः_दत्त *wind = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);
    यदि (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
        seat->pointer.gesture_focus = wind;

        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_update(शून्य *दत्त, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;

    यदि (seat->pointer.gesture_focus) {
        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        ध्रुव भिन्न s = (भिन्न)wl_fixed_गन्तव्यम्_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

स्थिर शून्य handle_pinch_अन्तः(शून्य *दत्त, संरचना zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;

    यदि (seat->pointer.gesture_focus) {
        ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_अन्तः, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = रिक्त;
    }
}

स्थिर ध्रुव संरचना zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_अन्तः
};

स्थिर शून्य Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    यदि (seat->display->zwp_pointer_gestures) {
        यदि (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_समुच्चयः_user_दत्त(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_सङ्कलय_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

शून्य Wayland_DisplayInitPointerGestureManager(SDL_Video_दत्त *display)
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

शून्य Wayland_DisplayInitCursorShapeManager(SDL_Video_दत्त *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

स्थिर शून्य Wayland_Seat_समुच्चयः_Keymap(SDL_WaylandSeat *seat)
{
    ध्रुव bool send_event = !seat->display->initializing;

    यदि (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अङ्कः_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_समुच्चयः_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_समुच्चयः_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
स्थिर शून्य keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    यावत् (elapsed >= repeat_info->अग्र_repeat_ns) {
        यदि (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ध्रुव Uint64 timestamp = repeat_info->आधारः_time_ns + repeat_info->अग्र_repeat_ns;
            SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_आधारः(timestamp), repeat_info->keyboard_id, repeat_info->कुञ्चिका, repeat_info->scancode, true);
        }
        यदि (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->अग्र_repeat_ns += SDL_NS_प्रत्येकम्_SECOND / (Uint64)repeat_info->repeat_दरः;
    }
}

स्थिर शून्य keyboard_repeat_समुच्चयः(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t कुञ्चिका, Uint32 wl_press_time_ms,
                                Uint64 आधारः_time_ns, uint32_t scancode, ध्रुव वर्ण *text)
{
    यदि (!repeat_info->repeat_दरः) {
        प्रत्यागम;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->कुञ्चिका = कुञ्चिका;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->आधारः_time_ns = आधारः_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->अग्र_repeat_ns = SDL_MS_गन्तव्यम्_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    यदि (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } अन्यथा {
        repeat_info->text[0] = '\0';
    }
}

स्थिर शून्य sync_समाप्तम्_handler(शून्य *दत्त, संरचना wl_callback *callback, uint32_t callback_दत्त)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener sync_listener = {
    sync_समाप्तम्_handler
};

शून्य Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *d = _this->आन्तरिकम्;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    संरचना wl_callback *cb = wl_display_sync(d->display);
    wl_callback_सङ्कलय_listener(cb, &sync_listener, रिक्त);
    WAYLAND_wl_display_flush(d->display);
}

पूर्णाङ्क Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_दत्त *d = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    ध्रुव पूर्णाङ्क display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णाङ्क ret;
    bool poll_alarm_समुच्चयः = false;

#यदि_परिभाषितम् SDL_USE_IME
    SDL_गवाक्षः *keyboard_focus = SDL_GetKeyboardFocus();
    यदि (!d->text_निवेशः_manager && keyboard_focus && SDL_Text_निवेशः_सक्रिय(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        यदि (timeoutNS < 0 || SDL_MS_गन्तव्यम्_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_गन्तव्यम्_NS(200);
            poll_alarm_समुच्चयः = true;
        }
    }
#यदि_अन्तः

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        यदि (seat->keyboard.repeat.कुञ्चिका) {
            ध्रुव Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            ध्रुव Uint64 अग्र_repeat_wait_time = (seat->keyboard.repeat.अग्र_repeat_ns - elapsed) + 1;
            यदि (timeoutNS < 0 || अग्र_repeat_wait_time <= timeoutNS) {
                timeoutNS = अग्र_repeat_wait_time;
                poll_alarm_समुच्चयः = true;
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
                प्रत्यागम poll_alarm_समुच्चयः ? 1 : 0;
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
    SDL_Video_दत्त *d = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat;
    ध्रुव पूर्णाङ्क display_fd = WAYLAND_wl_display_get_fd(d->display);
    पूर्णाङ्क ret = 0;

#यदि_परिभाषितम् SDL_USE_IME
    SDL_गवाक्षः *keyboard_focus = SDL_GetKeyboardFocus();
    यदि (!d->text_निवेशः_manager && keyboard_focus && SDL_Text_निवेशः_सक्रिय(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#यदि_अन्तः

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
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_गन्तव्यम्_NS(4));
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
            यदि (seat->keyboard.repeat.कुञ्चिका) {
                Wayland_Seat_समुच्चयः_Keymap(seat);

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
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = seat->pointer.focus;
    SDL_गवाक्षः *गवाक्षः = गवाक्षः_दत्त_2 ? गवाक्षः_दत्त_2->sdlwindow : रिक्त;

    यदि (गवाक्षः_दत्त_2) {
        द्विगुण sx = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.absolute.sx);
        द्विगुण sy = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.absolute.sy);

        यदि (seat->pointer.focus_surface == गवाक्षः_दत्त_2->आवरणम्.surface) {
            sx += (द्विगुण)गवाक्षः_दत्त_2->आवरणम्.विस्थापनम्_x;
            sy += (द्विगुण)गवाक्षः_दत्त_2->आवरणम्.विस्थापनम्_y;
        }

        sx *= गवाक्षः_दत्त_2->pointer_scale.x;
        sy *= गवाक्षः_दत्त_2->pointer_scale.y;
        यदि (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, गवाक्षः_दत्त_2->sdlwindow, seat->pointer.sdl_id, false, (भिन्न)sx, (भिन्न)sy);
        } अन्यथा {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, गवाक्षः_दत्त_2->sdlwindow, seat->pointer.sdl_id, (भिन्न)sx, (भिन्न)sy);
        }

        seat->pointer.चरमः_motion.x = (पूर्णाङ्क)SDL_floor(sx);
        seat->pointer.चरमः_motion.y = (पूर्णाङ्क)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        यदि (!SDL_Rect_रिक्तानि(&गवाक्षः->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE) && गवाक्षः->लब्धम्_test) {
            SDL_लब्धम्_Test_परिणाम rc = गवाक्षः->लब्धम्_test(गवाक्षः, &seat->pointer.चरमः_motion, गवाक्षः->लब्धम्_test_दत्त);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            विकल्प (rc) {
            पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
                यदि ((गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्) &&
                    (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_वामः)) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्) {
                    rc = SDL_HITTEST_RESIZE_वामः;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_वामः) {
                    rc = SDL_HITTEST_RESIZE_शिखरम्;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_शिखरम्:
                यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
                यदि ((गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्) &&
                    (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः)) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्) {
                    rc = SDL_HITTEST_RESIZE_दक्षिणः;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः) {
                    rc = SDL_HITTEST_RESIZE_शिखरम्;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_दक्षिणः:
                यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                यदि ((गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः)) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_दक्षिणः;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOM:
                यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
                यदि ((गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_वामः)) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_वामः;
                } अन्यथा यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_वामः) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                भङ्ग;
            पक्ष SDL_HITTEST_RESIZE_वामः:
                यदि (गवाक्षः_दत्त_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_वामः) {
                    rc = SDL_HITTEST_प्रसामान्यम्;
                }
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }

            यदि (rc != गवाक्षः_दत्त_2->लब्धम्_test_परिणाम) {
                गवाक्षः_दत्त_2->लब्धम्_test_परिणाम = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

स्थिर शून्य pointer_handle_motion(शून्य *दत्त, संरचना wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    ध्रुव Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_संस्करणम्) {
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
    SDL_गवाक्षः_दत्त *गवाक्षः = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(seat->pointer.pending_frame.enter_surface);
    यदि (!गवाक्षः) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        प्रत्यागम;
    }

    यदि (गवाक्षः->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_समुच्चयः_Default_Cursor(seat);
        प्रत्यागम;
    }

    seat->pointer.focus = गवाक्षः;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++गवाक्षः->pointer_focus_गणनम्;
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः->sdlwindow);

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

स्थिर शून्य pointer_handle_enter(शून्य *दत्त, संरचना wl_pointer *pointer,
                                 uint32_t serial, संरचना wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    यदि (!surface) {
        // Enter event for a destroyed surface.
        प्रत्यागम;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.pending_frame.enter_surface = surface;
    seat->pointer.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->pointer.pending_frame.absolute.sx = sx_w;
    seat->pointer.pending_frame.absolute.sy = sy_w;

    यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_संस्करणम्) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

स्थिर शून्य pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(seat->pointer.pending_frame.leave_surface);

    यदि (गवाक्षः) {
        यदि (seat->pointer.focus) {
            यदि (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                गवाक्षः->sdlwindow->flags &= ~SDL_गवाक्षः_MOUSE_CAPTURE;

                seat->pointer.focus = रिक्त;
                seat->pointer.focus_surface = रिक्त;
                प्रति (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    यदि (seat->pointer.buttons_pressed & SDL_BUTTON_आवरणम्(i)) {
                        SDL_SendMouseButton(0, गवाक्षः->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_आवरणम्(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_गवाक्षः *mouse_focus = SDL_GetMouseFocus();
                ध्रुव bool had_focus = mouse_focus && गवाक्षः->sdlwindow == mouse_focus;
                यदि (!--गवाक्षः->pointer_focus_गणनम् && had_focus && !गवाक्षः->सक्रिय_touch_गणनम्) {
                    SDL_समुच्चयः_Mouse_Focus(रिक्त);
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

स्थिर शून्य pointer_handle_leave(शून्य *दत्त, संरचना wl_pointer *pointer,
                                 uint32_t serial, संरचना wl_surface *surface)
{
    यदि (!surface) {
        // Leave event for a destroyed surface.
        प्रत्यागम;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.pending_frame.leave_surface = surface;
    यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_संस्करणम्) {
        pointer_dispatch_leave(seat, true);
    }
}

स्थिर bool Wayland_Process_लब्धम्_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    यदि (seat->pointer.locked_pointer) {
        प्रत्यागम false;
    }

    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = seat->pointer.focus;
    SDL_गवाक्षः *गवाक्षः = गवाक्षः_दत्त_2->sdlwindow;

    यदि (गवाक्षः->लब्धम्_test) {
        स्थिर ध्रुव uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_शिखरम्_वामः, XDG_TOPLEVEL_RESIZE_EDGE_शिखरम्,
            XDG_TOPLEVEL_RESIZE_EDGE_शिखरम्_दक्षिणः, XDG_TOPLEVEL_RESIZE_EDGE_दक्षिणः,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_दक्षिणः, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_वामः, XDG_TOPLEVEL_RESIZE_EDGE_वामः
        };

#यदि_परिभाषितम् HAVE_LIBDECOR_H
        स्थिर ध्रुव uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_शिखरम्_वामः, LIBDECOR_RESIZE_EDGE_शिखरम्,
            LIBDECOR_RESIZE_EDGE_शिखरम्_दक्षिणः, LIBDECOR_RESIZE_EDGE_दक्षिणः,
            LIBDECOR_RESIZE_EDGE_BOTTOM_दक्षिणः, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_वामः, LIBDECOR_RESIZE_EDGE_वामः
        };
#यदि_अन्तः

        विकल्प (गवाक्षः_दत्त_2->लब्धम्_test_परिणाम) {
        पक्ष SDL_HITTEST_DRAGGABLE:
#यदि_परिभाषितम् HAVE_LIBDECOR_H
            यदि (गवाक्षः_दत्त_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                यदि (गवाक्षः_दत्त_2->shell_surface.libdecor.frame) {
                    libdecor_frame_move(गवाक्षः_दत्त_2->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } अन्यथा
#यदि_अन्तः
                यदि (गवाक्षः_दत्त_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                यदि (गवाक्षः_दत्त_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(गवाक्षः_दत्त_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            प्रत्यागम true;

        पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
        पक्ष SDL_HITTEST_RESIZE_शिखरम्:
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
        पक्ष SDL_HITTEST_RESIZE_दक्षिणः:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        पक्ष SDL_HITTEST_RESIZE_BOTTOM:
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
        पक्ष SDL_HITTEST_RESIZE_वामः:
#यदि_परिभाषितम् HAVE_LIBDECOR_H
            यदि (गवाक्षः_दत्त_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                यदि (गवाक्षः_दत्त_2->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(गवाक्षः_दत्त_2->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[गवाक्षः_दत्त_2->लब्धम्_test_परिणाम - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } अन्यथा
#यदि_अन्तः
                यदि (गवाक्षः_दत्त_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                यदि (गवाक्षः_दत्त_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(गवाक्षः_दत्त_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[गवाक्षः_दत्त_2->लब्धम्_test_परिणाम - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            प्रत्यागम true;

        स्वभाव:
            प्रत्यागम false;
        }
    }

    प्रत्यागम false;
}

स्थिर शून्य pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool अधस्तात्)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = seat->pointer.focus;

    यदि (गवाक्षः) {
        bool ignore_click = false;

        यदि (अधस्तात्) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_आवरणम्(sdl_button);

            यदि (sdl_button == SDL_BUTTON_वामः && Wayland_Process_लब्धम्_Test(seat, seat->चरमः_implicit_grab_serial)) {
                प्रत्यागम; // don't pass this event on to app.
            }
        } अन्यथा {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_आवरणम्(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        यदि (गवाक्षः->चरमः_focus_event_time_ns) {
            यदि (अधस्तात् && (SDL_GetTicksNS() - गवाक्षः->चरमः_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            गवाक्षः->चरमः_focus_event_time_ns = 0;
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
                गवाक्षः->sdlwindow->flags |= SDL_गवाक्षः_MOUSE_CAPTURE;
            } अन्यथा {
                गवाक्षः->sdlwindow->flags &= ~SDL_गवाक्षः_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                यदि (seat->pointer.focus_surface != गवाक्षः->surface) {
                    seat->pointer.pending_frame.leave_surface = गवाक्षः->surface;
                }
            }
        }

        यदि (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, गवाक्षः->sdlwindow, seat->pointer.sdl_id, sdl_button, अधस्तात्);
        }
    }
}

स्थिर शून्य pointer_handle_button(शून्य *दत्त, संरचना wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = दत्त;
    Uint8 sdl_button;

    विकल्प (button) {
    पक्ष BTN_वामः:
        sdl_button = SDL_BUTTON_वामः;
        भङ्ग;
    पक्ष BTN_मध्यः:
        sdl_button = SDL_BUTTON_मध्यः;
        भङ्ग;
    पक्ष BTN_दक्षिणः:
        sdl_button = SDL_BUTTON_दक्षिणः;
        भङ्ग;
    स्वभाव:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        भङ्ग;
    }

    यदि (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    यदि (wl_seat_get_संस्करणम्(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_संस्करणम्) {
        यदि (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_आवरणम्(sdl_button);
        } अन्यथा {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_आवरणम्(sdl_button);
        }
    } अन्यथा {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

स्थिर शून्य pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t मानम्)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = seat->pointer.focus;
    ध्रुव गणना wl_pointer_axis a = axis;

    यदि (seat->pointer.focus) {
        भिन्न x, y;

        विकल्प (a) {
        पक्ष WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
            भङ्ग;
        पक्ष WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
            y = 0;
            भङ्ग;
        स्वभाव:
            प्रत्यागम;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, गवाक्षः->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_प्रसामान्यम्);
    }
}

स्थिर शून्य pointer_handle_axis_common(SDL_WaylandSeat *seat, गणना SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t मानम्)
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
                seat->pointer.pending_frame.axis.y += 0 - (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                यदि (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
                }
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                यदि (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
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
                seat->pointer.pending_frame.axis.x += (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                यदि (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
                }
                भङ्ग;
            पक्ष SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                यदि (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (भिन्न)wl_fixed_गन्तव्यम्_double(मानम्);
                }
                भङ्ग;
            }
            भङ्ग;
        }
    }
}

स्थिर शून्य pointer_handle_axis(शून्य *दत्त, संरचना wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t मानम्)
{
    SDL_WaylandSeat *seat = दत्त;
    ध्रुव Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    यदि (wl_seat_get_संस्करणम्(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_संस्करणम्) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, मानम्);
    } अन्यथा {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, मानम्);
    }
}

स्थिर शून्य pointer_handle_axis_relative_direction(शून्य *दत्त, संरचना wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = दत्त;

    विकल्प (axis_relative_direction) {
    पक्ष WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_प्रसामान्यम्;
        भङ्ग;
    पक्ष WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        भङ्ग;
    }
}

स्थिर शून्य pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = seat->pointer.focus;

    यदि (गवाक्षः) {
        SDL_Mouse *mouse = SDL_GetMouse();
        द्विगुण dx;
        द्विगुण dy;
        यदि (mouse->निवेशः_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } अन्यथा {
            dx = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.relative.dx) * गवाक्षः->pointer_scale.x;
            dy = wl_fixed_गन्तव्यम्_double(seat->pointer.pending_frame.relative.dy) * गवाक्षः->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, गवाक्षः->sdlwindow, seat->pointer.sdl_id, true, (भिन्न)dx, (भिन्न)dy);
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

स्थिर शून्य pointer_handle_frame(शून्य *दत्त, संरचना wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = दत्त;

    यदि (seat->pointer.pending_frame.enter_surface) {
        यदि (seat->pointer.pending_frame.leave_surface) {
            SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = seat->pointer.focus;
            SDL_गवाक्षः_दत्त *new_focus = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(seat->pointer.pending_frame.enter_surface);

            यदि (गवाक्षः_दत्त_2 && (गवाक्षः_दत्त_2->sdlwindow->flags & SDL_गवाक्षः_MOUSE_CAPTURE) && गवाक्षः_दत्त_2 == new_focus) {
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
        ध्रुव Uint32 आवरणम् = SDL_BUTTON_आवरणम्(i);
        यदि (seat->pointer.pending_frame.buttons_pressed & आवरणम्) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~आवरणम्;
        }
        यदि (seat->pointer.pending_frame.buttons_released & आवरणम्) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~आवरणम्;
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

स्थिर शून्य pointer_handle_axis_source(शून्य *दत्त, संरचना wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

स्थिर शून्य pointer_handle_axis_stop(शून्य *दत्त, संरचना wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

स्थिर शून्य pointer_handle_axis_discrete(शून्य *दत्त, संरचना wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = दत्त;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

स्थिर शून्य pointer_handle_axis_value120(शून्य *दत्त, संरचना wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = दत्त;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

स्थिर शून्य pointer_handle_warp(शून्य *दत्त, संरचना wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;

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

स्थिर शून्य relative_pointer_handle_relative_motion(शून्य *दत्त,
                                                    संरचना zwp_relative_pointer_v1 *pointer,
                                                    uint32_t time_hi,
                                                    uint32_t time_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = दत्त;

    // Relative pointer event times are in microsecond granularity.
    seat->pointer.pending_frame.relative.dx = dx;
    seat->pointer.pending_frame.relative.dy = dy;
    seat->pointer.pending_frame.relative.dx_unaccel = dx_unaccel;
    seat->pointer.pending_frame.relative.dy_unaccel = dy_unaccel;
    seat->pointer.pending_frame.timestamp_ns = Wayland_Adjust_Event_Timestamp_आधारः(SDL_US_गन्तव्यम्_NS(((Uint64)time_hi << 32) | (Uint64)time_lo));

    यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_संस्करणम्) {
        seat->pointer.pending_frame.have_relative = true;
    } अन्यथा {
        pointer_dispatch_relative_motion(seat);
    }
}

स्थिर ध्रुव संरचना zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

स्थिर शून्य locked_pointer_locked(शून्य *दत्त, संरचना zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.is_confined = true;
}

स्थिर शून्य locked_pointer_unlocked(शून्य *दत्त, संरचना zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.is_confined = false;
}

स्थिर ध्रुव संरचना zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

स्थिर शून्य confined_pointer_confined(शून्य *दत्त, संरचना zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.is_confined = true;
}

स्थिर शून्य confined_pointer_unconfined(शून्य *दत्त, संरचना zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->pointer.is_confined = false;
}

स्थिर ध्रुव संरचना zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

स्थिर शून्य touch_handler_अधस्तात्(शून्य *दत्त, संरचना wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, संरचना wl_surface *surface,
                               पूर्णाङ्क id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2;

    // Check that this surface is valid.
    यदि (!surface) {
        प्रत्यागम;
    }

    Wayland_Seat_सङ्कलय_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    गवाक्षः_दत्त_2 = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);

    यदि (गवाक्षः_दत्त_2 && गवाक्षः_दत्त_2->surface == surface) {
        भिन्न x, y;

        यदि (गवाक्षः_दत्त_2->current.logical_विस्तारः <= 1) {
            x = 0.5f;
        } अन्यथा {
            x = (भिन्न)wl_fixed_गन्तव्यम्_double(fx) / (गवाक्षः_दत्त_2->current.logical_विस्तारः - 1);
        }
        यदि (गवाक्षः_दत्त_2->current.logical_height <= 1) {
            y = 0.5f;
        } अन्यथा {
            y = (भिन्न)wl_fixed_गन्तव्यम्_double(fy) / (गवाक्षः_दत्त_2->current.logical_height - 1);
        }

        ++गवाक्षः_दत्त_2->सक्रिय_touch_गणनम्;
        SDL_समुच्चयः_Mouse_Focus(गवाक्षः_दत्त_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), गवाक्षः_दत्त_2->sdlwindow, SDL_EVENT_FINGER_अधस्तात्, x, y, 1.0f);
    }
}

स्थिर शून्य touch_handler_ऊर्ध्वम्(शून्य *दत्त, संरचना wl_touch *touch, uint32_t serial, uint32_t timestamp, पूर्णाङ्क id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    wl_fixed_t fx = 0, fy = 0;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    यदि (surface) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);

        यदि (गवाक्षः_दत्त_2 && गवाक्षः_दत्त_2->surface == surface) {
            ध्रुव भिन्न x = (भिन्न)wl_fixed_गन्तव्यम्_double(fx) / गवाक्षः_दत्त_2->current.logical_विस्तारः;
            ध्रुव भिन्न y = (भिन्न)wl_fixed_गन्तव्यम्_double(fy) / गवाक्षः_दत्त_2->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), गवाक्षः_दत्त_2->sdlwindow, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, 0.0f);

            --गवाक्षः_दत्त_2->सक्रिय_touch_गणनम्;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            यदि (SDL_GetMouseFocus() == गवाक्षः_दत्त_2->sdlwindow && !गवाक्षः_दत्त_2->keyboard_focus_गणनम् &&
                !गवाक्षः_दत्त_2->pointer_focus_गणनम् && !गवाक्षः_दत्त_2->सक्रिय_touch_गणनम्) {
                SDL_समुच्चयः_Mouse_Focus(रिक्त);
            }
        }
    }
}

स्थिर शून्य touch_handler_motion(शून्य *दत्त, संरचना wl_touch *touch, uint32_t timestamp, पूर्णाङ्क id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    संरचना wl_surface *surface = रिक्त;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    यदि (surface) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);

        यदि (गवाक्षः_दत्त_2 && गवाक्षः_दत्त_2->surface == surface) {
            ध्रुव भिन्न x = (भिन्न)wl_fixed_गन्तव्यम्_double(fx) / गवाक्षः_दत्त_2->current.logical_विस्तारः;
            ध्रुव भिन्न y = (भिन्न)wl_fixed_गन्तव्यम्_double(fy) / गवाक्षः_दत्त_2->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), गवाक्षः_दत्त_2->sdlwindow, x, y, 1.0f);
        }
    }
}

स्थिर शून्य touch_handler_frame(शून्य *दत्त, संरचना wl_touch *touch)
{
}

स्थिर शून्य touch_handler_cancel(शून्य *दत्त, संरचना wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    SDL_WaylandTouchPoint *tp, *अस्थायी;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, अस्थायी, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

स्थिर शून्य touch_handler_shape(शून्य *दत्त, संरचना wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

स्थिर शून्य touch_handler_orientation(शून्य *दत्त, संरचना wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

स्थिर ध्रुव संरचना wl_touch_listener touch_listener = {
    touch_handler_अधस्तात्,
    touch_handler_ऊर्ध्वम्,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#यदि !SDL_XKBCOMMON_CHECK_संस्करणम्(1, 0, 0)
स्थिर size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t कुञ्चिका, xkb_layout_सूचकांक_t layout, xkb_level_सूचकांक_t level, xkb_mod_आवरणम्_t *masks_बहिर्गमनम्, size_t masks_आकार)
{
    यदि (!masks_बहिर्गमनम् || !masks_आकार) {
        प्रत्यागम 0;
    }

    // Level 0 is always unmodified, so early out.
    यदि (level == 0) {
        *masks_बहिर्गमनम् = 0;
        प्रत्यागम 1;
    }

    size_t आवरणम्_idx = 0;
    ध्रुव xkb_mod_आवरणम्_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.सरणम्_आवरणम्,
        seat->keyboard.xkb.caps_आवरणम्_2,
        seat->keyboard.xkb.सरणम्_आवरणम् | seat->keyboard.xkb.caps_आवरणम्_2,
        seat->keyboard.xkb.level3_आवरणम्,
        seat->keyboard.xkb.level3_आवरणम् | seat->keyboard.xkb.सरणम्_आवरणम्,
        seat->keyboard.xkb.level3_आवरणम् | seat->keyboard.xkb.caps_आवरणम्_2,
        seat->keyboard.xkb.level3_आवरणम् | seat->keyboard.xkb.सरणम्_आवरणम् | seat->keyboard.xkb.caps_आवरणम्_2,
        seat->keyboard.xkb.level5_आवरणम्,
        seat->keyboard.xkb.level5_आवरणम् | seat->keyboard.xkb.सरणम्_आवरणम्,
        seat->keyboard.xkb.level5_आवरणम् | seat->keyboard.xkb.caps_आवरणम्_2,
        seat->keyboard.xkb.level5_आवरणम् | seat->keyboard.xkb.सरणम्_आवरणम् | seat->keyboard.xkb.caps_आवरणम्_2
    };
    ध्रुव xkb_mod_आवरणम्_t pressed_mod_आवरणम् = seat->keyboard.xkb.सरणम्_आवरणम् | seat->keyboard.xkb.level3_आवरणम् | seat->keyboard.xkb.level5_आवरणम्;
    ध्रुव xkb_mod_आवरणम्_t locked_mod_आवरणम् = seat->keyboard.xkb.caps_आवरणम्_2;

    प्रति (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_आवरणम्(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_आवरणम्, 0, keymod_masks[i] & locked_mod_आवरणम्, 0, 0, layout);
        यदि (WAYLAND_xkb_state_कुञ्चिका_get_level(seat->keyboard.xkb.state, कुञ्चिका, layout) == level) {
            masks_बहिर्गमनम्[आवरणम्_idx] = keymod_masks[i];

            यदि (++आवरणम्_idx == masks_आकार) {
                भङ्ग;
            }
        }
    }

    प्रत्यागम आवरणम्_idx;
}
#यदि_अन्तः

स्थिर शून्य Wayland_KeymapIterator(संरचना xkb_keymap *keymap, xkb_keycode_t कुञ्चिका, शून्य *दत्त)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    ध्रुव xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ध्रुव xkb_mod_आवरणम्_t xkb_valid_mod_आवरणम् = seat->keyboard.xkb.सरणम्_आवरणम् |
                                              seat->keyboard.xkb.alt_आवरणम् |
                                              seat->keyboard.xkb.level3_आवरणम् |
                                              seat->keyboard.xkb.level5_आवरणम् |
                                              seat->keyboard.xkb.caps_आवरणम्_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    यदि (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_सारणी(SDL_SCANCODE_सारणी_LINUX, कुञ्चिका - 8);
    }

    प्रति (xkb_layout_सूचकांक_t layout = 0; layout < seat->keyboard.xkb.अङ्कः_layouts; ++layout) {
        ध्रुव xkb_level_सूचकांक_t अङ्कः_स्तराः = WAYLAND_xkb_keymap_अङ्कः_स्तराः_for_कुञ्चिका(seat->keyboard.xkb.keymap, कुञ्चिका, layout);
        प्रति (xkb_level_सूचकांक_t level = 0; level < अङ्कः_स्तराः; ++level) {
            यदि (WAYLAND_xkb_keymap_कुञ्चिका_get_syms_by_level(seat->keyboard.xkb.keymap, कुञ्चिका, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                यदि (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_कुञ्चिका_Sym(syms[0], कुञ्चिका);
                    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
                        अनुवर्त;
                    }
                }

                xkb_mod_आवरणम्_t xkb_mod_masks[16];
#यदि SDL_XKBCOMMON_CHECK_संस्करणम्(1, 0, 0)
                ध्रुव size_t अङ्कः_masks = WAYLAND_xkb_keymap_कुञ्चिका_get_mods_for_level(seat->keyboard.xkb.keymap, कुञ्चिका, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#अन्यथा
                ध्रुव size_t अङ्कः_masks = xkb_legacy_get_mods_for_level(seat, कुञ्चिका, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#यदि_अन्तः
                प्रति (size_t आवरणम् = 0; आवरणम् < अङ्कः_masks; ++आवरणम्) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    यदि ((xkb_mod_masks[आवरणम्] | xkb_valid_mod_आवरणम्) != xkb_valid_mod_आवरणम्) {
                        अनुवर्त;
                    }

                    ध्रुव SDL_Keymod sdl_mod = (xkb_mod_masks[आवरणम्] & seat->keyboard.xkb.सरणम्_आवरणम् ? SDL_KMOD_सरणम् : 0) |
                                               (xkb_mod_masks[आवरणम्] & seat->keyboard.xkb.alt_आवरणम् ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[आवरणम्] & seat->keyboard.xkb.level3_आवरणम् ? SDL_KMOD_बहुलकम् : 0) |
                                               (xkb_mod_masks[आवरणम्] & seat->keyboard.xkb.level5_आवरणम् ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[आवरणम्] & seat->keyboard.xkb.caps_आवरणम्_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_कुञ्चिका_संहिता_From_कुञ्चिका_Sym(syms[0], कुञ्चिका, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    यदि (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_अग्र_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        यदि (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_समुच्चयः_Keymap_प्रविष्टिः(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_कुञ्चिका *res = WAYLAND_wl_array_सङ्कलय(&seat->keyboard.reserved_scancodes, परिमाण(Wayland_Reserved_कुञ्चिका));
                        यदि (res) {
                            res->scancode = scancode;
                            res->कुञ्चिका = कुञ्चिका - 8;
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
                            keycode = SDL_SCANCODE_गन्तव्यम्_KEYCODE(scancode);
                            भङ्ग;
                        }
                    }

                    SDL_समुच्चयः_Keymap_प्रविष्टिः(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

स्थिर शून्य keyboard_handle_keymap(शून्य *दत्त, संरचना wl_keyboard *keyboard,
                                   uint32_t format, पूर्णाङ्क fd, uint32_t आकार)
{
    SDL_WaylandSeat *seat = दत्त;
    वर्ण *map_str;

    यदि (!दत्त) {
        close(fd);
        प्रत्यागम;
    }

    यदि (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        प्रत्यागम;
    }

    map_str = mmap(रिक्त, आकार, PROT_READ, MAP_PRIVATE, fd, 0);
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
    munmap(map_str, आकार);
    close(fd);

    यदि (!seat->keyboard.xkb.keymap) {
        SDL_समुच्चयः_Error("failed to compile keymap");
        प्रत्यागम;
    }

    // Clear the old layouts.
    प्रति (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अङ्कः_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = रिक्त;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.अङ्कः_layouts = 0;

#यदि SDL_XKBCOMMON_CHECK_संस्करणम्(1, 10, 0)
    seat->keyboard.xkb.सरणम्_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_MOD_NAME_सरणम्);
    seat->keyboard.xkb.ctrl_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.अङ्कः_आवरणम् = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_अङ्कः);
    seat->keyboard.xkb.caps_आवरणम्_2 = WAYLAND_xkb_keymap_mod_get_आवरणम्(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#अन्यथा
#परिभाषय GET_MOD_सूचकांक(mod) \
    WAYLAND_xkb_keymap_mod_get_सूचकांक(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.सरणम्_आवरणम् = 1 << GET_MOD_सूचकांक(सरणम्_2);
    seat->keyboard.xkb.ctrl_आवरणम् = 1 << GET_MOD_सूचकांक(CTRL);
    seat->keyboard.xkb.alt_आवरणम् = 1 << GET_MOD_सूचकांक(ALT);
    seat->keyboard.xkb.gui_आवरणम् = 1 << GET_MOD_सूचकांक(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_आवरणम् = 1 << GET_MOD_सूचकांक(MOD5);
    seat->keyboard.xkb.level5_आवरणम् = 1 << GET_MOD_सूचकांक(MOD3);
    seat->keyboard.xkb.अङ्कः_आवरणम् = 1 << GET_MOD_सूचकांक(अङ्कः_2);
    seat->keyboard.xkb.caps_आवरणम्_2 = 1 << GET_MOD_सूचकांक(CAPS);
#अपरिभाषय GET_MOD_सूचकांक
#यदि_अन्तः

    यदि (seat->keyboard.xkb.state != रिक्त) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = रिक्त;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    यदि (!seat->keyboard.xkb.state) {
        SDL_समुच्चयः_Error("failed to create XKB state");
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
    seat->keyboard.xkb.अङ्कः_layouts = WAYLAND_xkb_keymap_अङ्कः_layouts(seat->keyboard.xkb.keymap);
    यदि (seat->keyboard.xkb.अङ्कः_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.अङ्कः_layouts, परिमाण(SDL_Keymap *));
        यदि (!seat->keyboard.sdl_keymap) {
            प्रत्यागम;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        प्रति (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अङ्कः_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            यदि (!seat->keyboard.sdl_keymap[i]) {
                प्रति (xkb_layout_सूचकांक_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = रिक्त;
                प्रत्यागम;
            }
        }

        WAYLAND_xkb_keymap_कुञ्चिका_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_आवरणम्(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अङ्कः_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_समुच्चयः_Keymap(seat);
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

        यदि (seat->keyboard.xkb.compose_सारणी != रिक्त) {
            WAYLAND_xkb_compose_सारणी_unref(seat->keyboard.xkb.compose_सारणी);
            seat->keyboard.xkb.compose_सारणी = रिक्त;
        }
        seat->keyboard.xkb.compose_सारणी = WAYLAND_xkb_compose_सारणी_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        यदि (seat->keyboard.xkb.compose_सारणी) {
            // Set up XKB compose state
            यदि (seat->keyboard.xkb.compose_state != रिक्त) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = रिक्त;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_सारणी,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            यदि (!seat->keyboard.xkb.compose_state) {
                SDL_समुच्चयः_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_सारणी_unref(seat->keyboard.xkb.compose_सारणी);
                seat->keyboard.xkb.compose_सारणी = रिक्त;
            }
        }
    } अन्यथा यदि (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
स्थिर SDL_Scancode Wayland_Get_Scancode_For_कुञ्चिका(SDL_WaylandSeat *seat, Uint32 कुञ्चिका, ध्रुव xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    यदि (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_सारणी(SDL_SCANCODE_सारणी_LINUX, कुञ्चिका);

        // No table entry? Check the reserved list.
        यदि (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_कुञ्चिका *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                यदि (i->कुञ्चिका == कुञ्चिका) {
                    प्रत्यागम i->scancode;
                }
            }
        }
    } अन्यथा {
        ध्रुव xkb_keysym_t *keysym;
        यदि (WAYLAND_xkb_state_कुञ्चिका_get_syms(seat->keyboard.xkb.state, कुञ्चिका + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_कुञ्चिका_Sym(keysym[0], कुञ्चिका + 8);
            यदि (syms) {
                *syms = keysym;
            }
        }
    }

    प्रत्यागम scancode;
}

स्थिर शून्य Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool कुञ्चिका_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    यदि (!कुञ्चिका_pressed) {
        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.सरणम्_आवरणम्) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_सरणम्)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_सरणम्;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_सरणम्;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_आवरणम्) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_आवरणम्) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_आवरणम्) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_आवरणम्) {
            यदि (!(seat->keyboard.pressed_modifiers & SDL_KMOD_बहुलकम्)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_बहुलकम्;
            }
        } अन्यथा {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_बहुलकम्;
        }

        यदि (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_आवरणम्) {
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
    ध्रुव xkb_mod_आवरणम्_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.सरणम्_आवरणम्) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_सरणम्) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_सरणम्;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_सरणम्);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_सरणम्)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_सरणम्;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_सरणम्;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_आवरणम्) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.alt_आवरणम्) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.gui_आवरणम्) {
        यदि (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } अन्यथा यदि (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.level3_आवरणम्) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_बहुलकम्;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_बहुलकम्;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.level5_आवरणम्) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    यदि (xkb_locked_modifiers & seat->keyboard.xkb.caps_आवरणम्_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    यदि (xkb_locked_modifiers & seat->keyboard.xkb.अङ्कः_आवरणम्) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_अङ्कः;
    } अन्यथा {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_अङ्कः;
    }

    SDL_समुच्चयः_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

स्थिर शून्य Wayland_Handle_Modifier_कुञ्चिकाः(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ध्रुव SDL_Keycode keycode = SDL_Get_कुञ्चिका_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
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
    पक्ष SDLK_बहुलकम्:
        mod = SDL_KMOD_बहुलकम्;
        भङ्ग;
    पक्ष SDLK_LEVEL5_सरणम्:
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

स्थिर शून्य keyboard_handle_enter(शून्य *दत्त, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface,
                                  संरचना wl_array *कुञ्चिकाः)
{
    SDL_WaylandSeat *seat = दत्त;
    uint32_t *कुञ्चिका;

    यदि (!surface) {
        // Enter event for a destroyed surface.
        प्रत्यागम;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_गवाक्षः_दत्त *गवाक्षः = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);
    यदि (!गवाक्षः) {
        // Not a surface owned by SDL.
        प्रत्यागम;
    }

    ++गवाक्षः->keyboard_focus_गणनम्;
    seat->keyboard.focus = गवाक्षः;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः->sdlwindow->keyboard_focus ? गवाक्षः->sdlwindow->keyboard_focus : गवाक्षः->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, गवाक्षः);

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_निवेशः(seat);

#यदि_परिभाषितम् SDL_USE_IME
    यदि (!seat->text_निवेशः.zwp_text_निवेशः) {
        SDL_IME_समुच्चयः_Focus(true);
    }
#यदि_अन्तः

    Uint64 timestamp = SDL_GetTicksNS();
    गवाक्षः->चरमः_focus_event_time_ns = timestamp;

    Wayland_Seat_समुच्चयः_Keymap(seat);

    wl_array_for_each (कुञ्चिका, कुञ्चिकाः) {
        ध्रुव SDL_Scancode scancode = Wayland_Get_Scancode_For_कुञ्चिका(seat, *कुञ्चिका, रिक्त);
        यदि (scancode != SDL_SCANCODE_UNKNOWN) {
            ध्रुव SDL_Keycode keycode = SDL_Get_कुञ्चिका_From_Scancode(scancode, SDL_KMOD_NONE, false);

            विकल्प (keycode) {
            पक्ष SDLK_LSHIFT:
            पक्ष SDLK_RSHIFT:
            पक्ष SDLK_LCTRL:
            पक्ष SDLK_RCTRL:
            पक्ष SDLK_LALT:
            पक्ष SDLK_RALT:
            पक्ष SDLK_LGUI:
            पक्ष SDLK_RGUI:
            पक्ष SDLK_बहुलकम्:
            पक्ष SDLK_LEVEL5_सरणम्:
                Wayland_Handle_Modifier_कुञ्चिकाः(seat, scancode, true);
                SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *कुञ्चिका, scancode, true);
                भङ्ग;
            स्वभाव:
                भङ्ग;
            }
        }
    }
}

स्थिर शून्य keyboard_handle_leave(शून्य *दत्त, संरचना wl_keyboard *keyboard,
                                  uint32_t serial, संरचना wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;

    यदि (!surface) {
        // Leave event for a destroyed surface.
        प्रत्यागम;
    }

    SDL_गवाक्षः_दत्त *गवाक्षः = Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface);
    यदि (!गवाक्षः) {
        // Not a surface owned by SDL.
        प्रत्यागम;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.कुञ्चिका = 0;

    SDL_गवाक्षः *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    यावत् (keyboard_focus && SDL_गवाक्षः_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    ध्रुव bool had_focus = keyboard_focus && गवाक्षः->sdlwindow == keyboard_focus;
    seat->keyboard.focus = रिक्त;
    --गवाक्षः->keyboard_focus_गणनम्;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    यदि (!गवाक्षः->keyboard_focus_गणनम् && had_focus) {
        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, गवाक्षः);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_Text_निवेशः(seat);

#यदि_परिभाषितम् SDL_USE_IME
    यदि (!seat->text_निवेशः.zwp_text_निवेशः && !गवाक्षः->keyboard_focus_गणनम्) {
        SDL_IME_समुच्चयः_Focus(false);
    }
#यदि_अन्तः

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    यदि (SDL_GetMouseFocus() == गवाक्षः->sdlwindow && !गवाक्षः->pointer_focus_गणनम् && !गवाक्षः->सक्रिय_touch_गणनम्) {
        SDL_समुच्चयः_Mouse_Focus(रिक्त);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_दत्त_Device_समुच्चयः_Selection_Offer(seat->दत्त_device, रिक्त);
}

स्थिर bool keyboard_निवेशः_get_text(वर्ण text[8], ध्रुव SDL_WaylandSeat *seat, uint32_t कुञ्चिका, bool अधस्तात्, bool *handled_by_ime)
{
    ध्रुव xkb_keysym_t *syms;
    xkb_keysym_t sym;

    यदि (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        प्रत्यागम false;
    }

    // TODO: Can this happen?
    यदि (WAYLAND_xkb_state_कुञ्चिका_get_syms(seat->keyboard.xkb.state, कुञ्चिका + 8, &syms) != 1) {
        प्रत्यागम false;
    }
    sym = syms[0];

#यदि_परिभाषितम् SDL_USE_IME
    यदि (SDL_IME_Process_कुञ्चिका_Event(sym, कुञ्चिका + 8, अधस्तात्)) {
        यदि (handled_by_ime) {
            *handled_by_ime = true;
        }
        प्रत्यागम true;
    }
#यदि_अन्तः

    यदि (!अधस्तात्) {
        प्रत्यागम false;
    }

    यदि (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        विकल्प (WAYLAND_xkb_compose_state_get_स्थितिः(seat->keyboard.xkb.compose_state)) {
        पक्ष XKB_COMPOSE_COMPOSING:
            यदि (handled_by_ime) {
                *handled_by_ime = true;
            }
            प्रत्यागम true;
        पक्ष XKB_COMPOSE_CANCELLED:
        स्वभाव:
            sym = XKB_कुञ्चिका_No_चिह्नम्;
            भङ्ग;
        पक्ष XKB_COMPOSE_NOTHING:
            भङ्ग;
        पक्ष XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            भङ्ग;
        }
    }

    प्रत्यागम WAYLAND_xkb_keysym_गन्तव्यम्_utf8(sym, text, 8) > 0;
}

स्थिर शून्य keyboard_handle_कुञ्चिका(शून्य *दत्त, संरचना wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t कुञ्चिका,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = दत्त;
    गणना wl_keyboard_कुञ्चिका_state state = state_w;
    वर्ण text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    ध्रुव Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    यदि (state == WL_KEYBOARD_कुञ्चिका_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        यदि (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_कुञ्चिका_repeats(seat->keyboard.xkb.keymap, कुञ्चिका + 8)) {
            प्रत्यागम;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_कुञ्चिका_STATE_PRESSED;
    }

    Wayland_Seat_समुच्चयः_Keymap(seat);

    यदि (state == WL_KEYBOARD_कुञ्चिका_STATE_PRESSED) {
        SDL_गवाक्षः *keyboard_focus = SDL_GetKeyboardFocus();
        यदि (keyboard_focus && SDL_Text_निवेशः_सक्रिय(keyboard_focus)) {
            has_text = keyboard_निवेशः_get_text(text, seat, कुञ्चिका, true, &handled_by_ime);
        }
    } अन्यथा {
        यदि (कुञ्चिका == seat->keyboard.repeat.कुञ्चिका) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ध्रुव Uint64 elapsed = SDL_MS_गन्तव्यम्_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.कुञ्चिका = 0;
        }
        keyboard_निवेशः_get_text(text, seat, कुञ्चिका, false, &handled_by_ime);
    }

    ध्रुव xkb_keysym_t *syms = रिक्त;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_कुञ्चिका(seat, कुञ्चिका, &syms);
    Wayland_Handle_Modifier_कुञ्चिकाः(seat, scancode, state == WL_KEYBOARD_कुञ्चिका_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    यदि (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ध्रुव SDL_Keycode keycode = (SDL_Keycode)SDL_कुञ्चिका_Sym_गन्तव्यम्_Ucs4(syms[0]);
        यदि (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            यदि (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_आवरणम्) {
                scancode = SDL_Get_Keymap_अग्र_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_समुच्चयः_Keymap_प्रविष्टिः(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_कुञ्चिका_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, कुञ्चिका, scancode, state == WL_KEYBOARD_कुञ्चिका_STATE_PRESSED);

    यदि (state == WL_KEYBOARD_कुञ्चिका_STATE_PRESSED) {
        यदि (handled_by_ime) {
            has_text = false;
        }
        यदि (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        यदि (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_कुञ्चिका_repeats(seat->keyboard.xkb.keymap, कुञ्चिका + 8)) {
            keyboard_repeat_समुच्चयः(&seat->keyboard.repeat, seat->keyboard.sdl_id, कुञ्चिका, time, timestamp_ns, scancode, has_text ? text : रिक्त);
        }
    }
}

स्थिर शून्य keyboard_handle_modifiers(शून्य *दत्त, संरचना wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t गणः)
{
    SDL_WaylandSeat *seat = दत्त;
    ध्रुव uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = गणः;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    यदि (!seat->keyboard.xkb.state) {
        प्रत्यागम;
    }

    WAYLAND_xkb_state_update_आवरणम्(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, गणः);

    // If a key is repeating, update the text to apply the modifier.
    यदि (seat->keyboard.repeat.कुञ्चिका) {
        वर्ण text[8];

        यदि (keyboard_निवेशः_get_text(text, seat, seat->keyboard.repeat.कुञ्चिका, true, रिक्त)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    यदि (गणः != previous_layout) {
        Wayland_Seat_समुच्चयः_Keymap(seat);

        यदि (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

स्थिर शून्य keyboard_handle_repeat_info(शून्य *दत्त, संरचना wl_keyboard *wl_keyboard,
                                        int32_t दरः, int32_t delay)
{
    SDL_WaylandSeat *seat = दत्त;
    seat->keyboard.repeat.repeat_दरः = दरः;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    यदि (!दरः) {
        seat->keyboard.repeat.कुञ्चिका = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

स्थिर ध्रुव संरचना wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_कुञ्चिका,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

स्थिर शून्य Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    यदि (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_अन्तः, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
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
        zwp_निवेशः_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    यदि (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    यदि (seat->pointer.wl_pointer) {
        यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_संस्करणम्) {
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
        यदि (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.अङ्कः_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_समुच्चयः_Mod_State(SDL_KMOD_NONE);
        }
        प्रति (xkb_layout_सूचकांक_t i = 0; i < seat->keyboard.xkb.अङ्कः_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = रिक्त;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    यदि (seat->keyboard.कुञ्चिका_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुञ्चिका_inhibitor);
    }

    यदि (seat->keyboard.timestamps) {
        zwp_निवेशः_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    यदि (seat->keyboard.wl_keyboard) {
        यदि (wl_keyboard_get_संस्करणम्(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_संस्करणम्) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } अन्यथा {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    यदि (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    यदि (seat->keyboard.xkb.compose_सारणी) {
        WAYLAND_xkb_compose_सारणी_unref(seat->keyboard.xkb.compose_सारणी);
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
        zwp_निवेशः_timestamps_v1_destroy(seat->touch.timestamps);
    }

    यदि (seat->touch.wl_touch) {
        यदि (wl_touch_get_संस्करणम्(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_संस्करणम्) {
            wl_touch_release(seat->touch.wl_touch);
        } अन्यथा {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

स्थिर शून्य seat_handle_capabilities(शून्य *दत्त, संरचना wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    वर्ण name_fmt[256];

    यदि ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_समुच्चयः_user_दत्त(seat->pointer.wl_pointer, seat);
        wl_pointer_सङ्कलय_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_Get_अग्र_Object_ID();

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_सङ्कलय_Mouse(seat->pointer.sdl_id, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    यदि ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_समुच्चयः_user_दत्त(seat->touch.wl_touch, seat);
        wl_touch_सङ्कलय_listener(seat->touch.wl_touch, &touch_listener, seat);

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_सङ्कलय_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_प्रत्यक्षम्, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    यदि ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_समुच्चयः_user_दत्त(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_सङ्कलय_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_अग्र_Object_ID();

        यदि (seat->name) {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } अन्यथा {
            SDL_snprintf(name_fmt, परिमाण(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_सङ्कलय_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } अन्यथा यदि (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_पञ्जिकाकोशः_निवेशः_Timestamp_Listeners(seat);
}

स्थिर शून्य seat_handle_name(शून्य *दत्त, संरचना wl_seat *wl_seat, ध्रुव वर्ण *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;

    यदि (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

स्थिर ध्रुव संरचना wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

स्थिर शून्य दत्त_offer_handle_offer(शून्य *दत्त, संरचना wl_दत्त_offer *wl_दत्त_offer,
                                    ध्रुव वर्ण *mime_type)
{
    SDL_Wayland_दत्त_Offer *offer = दत्त;
    Wayland_दत्त_Offer_सङ्कलय_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_दत्त_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_दत्त_offer) : -1),
                 mime_type);
}

स्थिर शून्य दत्त_offer_handle_source_actions(शून्य *दत्त, संरचना wl_दत्त_offer *wl_दत्त_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_दत्त_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_दत्त_offer) : -1),
                 source_actions);
}

स्थिर शून्य दत्त_offer_handle_actions(शून्य *दत्त, संरचना wl_दत्त_offer *wl_दत्त_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_दत्त_offer ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)wl_दत्त_offer) : -1),
                 dnd_action);
}

स्थिर ध्रुव संरचना wl_दत्त_offer_listener दत्त_offer_listener = {
    दत्त_offer_handle_offer,
    दत्त_offer_handle_source_actions, // Version 3
    दत्त_offer_handle_actions,        // Version 3
};

स्थिर शून्य primary_selection_offer_handle_offer(शून्य *दत्त, संरचना zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ध्रुव वर्ण *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = दत्त;
    Wayland_Primary_Selection_Offer_सङ्कलय_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

स्थिर ध्रुव संरचना zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

स्थिर शून्य दत्त_device_handle_दत्त_offer(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device,
                                          संरचना wl_दत्त_offer *id)
{
    SDL_Wayland_दत्त_Offer *दत्त_offer = SDL_calloc(1, परिमाण(*दत्त_offer));
    यदि (दत्त_offer) {
        SDL_Wayland_दत्त_Device *दत्त_device = (SDL_Wayland_दत्त_Device *)दत्त;
        दत्त_offer->offer = id;
        दत्त_offer->दत्त_device = दत्त_device;
        दत्त_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(दत्त_offer->mimes));
        wl_दत्त_offer_समुच्चयः_user_दत्त(id, दत्त_offer);
        wl_दत्त_offer_सङ्कलय_listener(id, &दत्त_offer_listener, दत्त_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
    }
}

स्थिर शून्य दत्त_device_handle_enter(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device,
                                     uint32_t serial, संरचना wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, संरचना wl_दत्त_offer *id)
{
    SDL_Wayland_दत्त_Device *दत्त_device = दत्त;
    SDL_गवाक्षः_दत्त *गवाक्षः = surface ? Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface) : रिक्त;
    दत्त_device->has_mime_file = false;
    दत्त_device->text_mime_type = रिक्त;

    दत्त_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    यदि (id) {
        दत्त_device->drag_offer = wl_दत्त_offer_get_user_दत्त(id);
    }

    यदि (दत्त_device->drag_offer && गवाक्षः && गवाक्षः->accepts_drag_and_drop) {
#यदि_परिभाषितम् SDL_USE_LIBDBUS
        यदि (Wayland_दत्त_Offer_Has_MIME(दत्त_device->drag_offer, FILE_PORTAL_MIME)) {
            दत्त_device->has_mime_file = true;
            wl_दत्त_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#यदि_अन्तः
        यदि (Wayland_दत्त_Offer_Has_MIME(दत्त_device->drag_offer, FILE_MIME)) {
            दत्त_device->has_mime_file = true;
            wl_दत्त_offer_accept(id, serial, FILE_MIME);
        }

        यदि (!दत्त_device->has_mime_file) {
            size_t mime_गणनम् = 0;
            ध्रुव वर्ण *ध्रुव *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_गणनम्);
            प्रति (size_t i = 0; i < mime_गणनम्; ++i) {
                यदि (Wayland_दत्त_Offer_Has_MIME(दत्त_device->drag_offer, text_mime_types[i])) {
                    दत्त_device->text_mime_type = text_mime_types[i];
                    wl_दत्त_offer_accept(id, serial, text_mime_types[i]);
                    भङ्ग;
                }
            }
        }

        यदि (दत्त_device->has_mime_file || दत्त_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            यदि (wl_दत्त_offer_get_संस्करणम्(दत्त_device->drag_offer->offer) >= WL_दत्त_OFFER_समुच्चयः_ACTIONS_SINCE_संस्करणम्) {
                wl_दत्त_offer_समुच्चयः_actions(दत्त_device->drag_offer->offer, WL_दत्त_DEVICE_MANAGER_DND_ACTION_COPY, WL_दत्त_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            दत्त_device->dnd_गवाक्षः = गवाक्षः->sdlwindow;
            दत्त_device->dnd_surface = surface;
            द्विगुण dx = wl_fixed_गन्तव्यम्_double(x);
            द्विगुण dy = wl_fixed_गन्तव्यम्_double(y);

            // If over the mask, adjust the offset.
            यदि (surface == गवाक्षः->आवरणम्.surface) {
                dx += (द्विगुण)गवाक्षः->आवरणम्.विस्थापनम्_x;
                dy += (द्विगुण)गवाक्षः->आवरणम्.विस्थापनम्_y;
            }

            dx *= गवाक्षः->pointer_scale.x;
            dy *= गवाक्षः->pointer_scale.y;

            SDL_SendDropPosition(दत्त_device->dnd_गवाक्षः, (भिन्न)dx, (भिन्न)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id),
                         wl_fixed_गन्तव्यम्_int(x), wl_fixed_गन्तव्यम्_int(y), SDL_Get_गवाक्षः_ID(दत्त_device->dnd_गवाक्षः), serial);
        } अन्यथा {
            // Decline the offer.
            wl_दत्त_offer_accept(id, serial, रिक्त);
            यदि (wl_दत्त_offer_get_संस्करणम्(दत्त_device->drag_offer->offer) >= WL_दत्त_OFFER_समुच्चयः_ACTIONS_SINCE_संस्करणम्) {
                wl_दत्त_offer_समुच्चयः_actions(दत्त_device->drag_offer->offer, WL_दत्त_DEVICE_MANAGER_DND_ACTION_NONE, WL_दत्त_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id), wl_fixed_गन्तव्यम्_int(x), wl_fixed_गन्तव्यम्_int(y), serial);
        }
    } अन्यथा {
        दत्त_device->dnd_गवाक्षः = रिक्त;
        दत्त_device->dnd_surface = रिक्त;

        // Decline the offer.
        यदि (id) {
            wl_दत्त_offer_accept(id, serial, रिक्त);
            यदि (wl_दत्त_offer_get_संस्करणम्(दत्त_device->drag_offer->offer) >= WL_दत्त_OFFER_समुच्चयः_ACTIONS_SINCE_संस्करणम्) {
                wl_दत्त_offer_समुच्चयः_actions(दत्त_device->drag_offer->offer, WL_दत्त_DEVICE_MANAGER_DND_ACTION_NONE, WL_दत्त_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1,
                     wl_fixed_गन्तव्यम्_int(x), wl_fixed_गन्तव्यम्_int(y), serial);
    }
}

स्थिर शून्य दत्त_device_handle_leave(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device)
{
    SDL_Wayland_दत्त_Device *दत्त_device = दत्त;

    यदि (दत्त_device->drag_offer) {
        यदि (दत्त_device->dnd_गवाक्षः) {
            SDL_SendDropComplete(दत्त_device->dnd_गवाक्षः);
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)दत्त_device->drag_offer->offer),
                         SDL_Get_गवाक्षः_ID(दत्त_device->dnd_गवाक्षः), दत्त_device->drag_serial);
        } अन्यथा {
            SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)दत्त_device->drag_offer->offer),
                         दत्त_device->drag_serial);
        }
        Wayland_दत्त_Offer_Destroy(दत्त_device->drag_offer);
        दत्त_device->drag_offer = रिक्त;
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    दत्त_device->has_mime_file = false;
    दत्त_device->text_mime_type = रिक्त;
}

स्थिर शून्य दत्त_device_handle_motion(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_दत्त_Device *दत्त_device = दत्त;

    यदि (दत्त_device->drag_offer && दत्त_device->dnd_गवाक्षः && (दत्त_device->has_mime_file || दत्त_device->text_mime_type)) {
        SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = दत्त_device->dnd_गवाक्षः->आन्तरिकम्;
        द्विगुण dx = wl_fixed_गन्तव्यम्_double(x);
        द्विगुण dy = wl_fixed_गन्तव्यम्_double(y);

        // If over the mask, adjust the offset.
        यदि (दत्त_device->dnd_surface == गवाक्षः_दत्त_2->आवरणम्.surface) {
            dx += (द्विगुण)गवाक्षः_दत्त_2->आवरणम्.विस्थापनम्_x;
            dy += (द्विगुण)गवाक्षः_दत्त_2->आवरणम्.विस्थापनम्_y;
        }

        dx *= गवाक्षः_दत्त_2->pointer_scale.x;
        dy *= गवाक्षः_दत्त_2->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(दत्त_device->dnd_गवाक्षः, (भिन्न)dx, (भिन्न)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)दत्त_device->drag_offer->offer),
                     wl_fixed_गन्तव्यम्_int(x), wl_fixed_गन्तव्यम्_int(y),
                     SDL_Get_गवाक्षः_ID(दत्त_device->dnd_गवाक्षः), दत्त_device->drag_serial);
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_गन्तव्यम्_int(x), wl_fixed_गन्तव्यम्_int(y), -1);
    }
}

स्थिर शून्य drop_cleanup_handler(शून्य *दत्त, संरचना wl_callback *callback, uint32_t callback_दत्त)
{
    Wayland_Drop_दत्त *drop = (Wayland_Drop_दत्त *)दत्त;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

स्थिर ध्रुव संरचना wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

स्थिर शून्य drop_dispatch_handler(शून्य *दत्त)
{
    Wayland_Drop_दत्त *drop = (Wayland_Drop_दत्त *)दत्त;
    SDL_Wayland_दत्त_Offer *offer = drop->offer;
    SDL_Wayland_दत्त_Device *दत्त_device = offer->दत्त_device;

    यदि (drop->dnd_गवाक्षः) {
        size_t दीर्घता;
        bool drop_handled = false;

#यदि_परिभाषितम् SDL_USE_LIBDBUS
        यदि (Wayland_दत्त_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            शून्य *बफर_2 = Wayland_दत्त_Offer_Receive(offer, FILE_PORTAL_MIME, &दीर्घता);
            यदि (बफर_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                यदि (dbus) {
                    पूर्णाङ्क मार्गः_गणनम् = 0;
                    वर्ण **paths = SDL_DBus_DocumentsPortalRetrieveFiles(बफर_2, &मार्गः_गणनम्);
                    // If dropped files contain a directory the list is empty
                    यदि (paths && मार्गः_गणनम् > 0) {
                        प्रति (पूर्णाङ्क i = 0; i < मार्गः_गणनम्; i++) {
                            SDL_SendDropFile(drop->dnd_गवाक्षः, रिक्त, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(बफर_2);
            }
        }
#यदि_अन्तः
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        यदि (!drop_handled) {
            यदि (Wayland_दत्त_Offer_Has_MIME(offer, FILE_MIME)) {
                शून्य *बफर_2 = Wayland_दत्त_Offer_Receive(offer, FILE_MIME, &दीर्घता);
                यदि (बफर_2) {
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r((वर्ण *)बफर_2, "\r\n", &saveptr);
                    यावत् (token) {
                        यदि (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_गवाक्षः, रिक्त, token);
                        }
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(बफर_2);
                    drop_handled = true;
                }
            } अन्यथा यदि (Wayland_दत्त_Offer_Has_MIME(offer, drop->text_mime_type)) {
                शून्य *बफर_2 = Wayland_दत्त_Offer_Receive(offer, drop->text_mime_type, &दीर्घता);
                यदि (बफर_2) {
                    वर्ण *saveptr = रिक्त;
                    वर्ण *token = SDL_strtok_r((वर्ण *)बफर_2, "\r\n", &saveptr);
                    यावत् (token) {
                        SDL_SendDropText(drop->dnd_गवाक्षः, token);
                        token = SDL_strtok_r(रिक्त, "\r\n", &saveptr);
                    }
                    SDL_free(बफर_2);
                    drop_handled = true;
                }
            }
        }

        यदि (drop_handled && wl_दत्त_offer_get_संस्करणम्(offer->offer) >= WL_दत्त_OFFER_FINISH_SINCE_संस्करणम्) {
            wl_दत्त_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_गवाक्षः);
    }

    Wayland_दत्त_Offer_Destroy(drop->offer);
    drop->offer = रिक्त;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(दत्त_device->seat->display->display);
    wl_callback_सङ्कलय_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

स्थिर शून्य दत्त_device_handle_drop(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device)
{
    SDL_Wayland_दत्त_Device *दत्त_device = दत्त;

    यदि (दत्त_device->drag_offer && दत्त_device->dnd_गवाक्षः &&
        (दत्त_device->has_mime_file || दत्त_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)दत्त_device->drag_offer->offer),
                     SDL_Get_गवाक्षः_ID(दत्त_device->dnd_गवाक्षः), दत्त_device->drag_serial);

        Wayland_JobThreadContext *ctx = दत्त_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_दत्त *drop = SDL_calloc(1, परिमाण(Wayland_Drop_दत्त));
        यदि (drop) {
            drop->offer = दत्त_device->drag_offer;
            drop->dnd_गवाक्षः = दत्त_device->dnd_गवाक्षः;
            drop->text_mime_type = दत्त_device->text_mime_type;

            WAYLAND_wl_list_निवेशय(&दत्त_device->pending_drops, &drop->link);
            Wayland_Job_Thread_सङ्कलय_Job(ctx, drop_dispatch_handler, drop, &drop->id);
        } अन्यथा {
            Wayland_दत्त_Offer_Destroy(दत्त_device->drag_offer);
        }
    } अन्यथा {
        SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_दत्त_Offer_Destroy(दत्त_device->drag_offer);
    }

    दत्त_device->drag_offer = रिक्त;
}

स्थिर शून्य दत्त_device_handle_selection(शून्य *दत्त, संरचना wl_दत्त_device *wl_दत्त_device,
                                         संरचना wl_दत्त_offer *id)
{
    SDL_Wayland_दत्त_Device *दत्त_device = दत्त;
    SDL_Wayland_दत्त_Offer *offer = रिक्त;

    यदि (id) {
        offer = wl_दत्त_offer_get_user_दत्त(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));

    Wayland_दत्त_Device_समुच्चयः_Selection_Offer(दत्त_device, offer);
}

स्थिर ध्रुव संरचना wl_दत्त_device_listener दत्त_device_listener = {
    दत्त_device_handle_दत्त_offer,
    दत्त_device_handle_enter,
    दत्त_device_handle_leave,
    दत्त_device_handle_motion,
    दत्त_device_handle_drop,
    दत्त_device_handle_selection
};

स्थिर शून्य primary_selection_device_handle_offer(शून्य *दत्त, संरचना zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  संरचना zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, परिमाण(*primary_selection_offer));
    यदि (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)दत्त;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_समुच्चयः_user_दत्त(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_सङ्कलय_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर शून्य primary_selection_device_handle_selection(शून्य *दत्त, संरचना zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      संरचना zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = दत्त;
    SDL_WaylandPrimarySelectionOffer *offer = रिक्त;

    यदि (id) {
        offer = zwp_primary_selection_offer_v1_get_user_दत्त(id);
    }

    यदि (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((संरचना wl_proxy *)id) : -1));
}

स्थिर ध्रुव संरचना zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

स्थिर शून्य text_निवेशः_enter(शून्य *दत्त,
                             संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_निवेशः_leave(शून्य *दत्त,
                             संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                             संरचना wl_surface *surface)
{
    // No-op
}

स्थिर शून्य text_निवेशः_preedit_string(शून्य *दत्त,
                                      संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                                      ध्रुव वर्ण *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_अन्तः)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    seat->text_निवेशः.has_preedit = true;
    यदि (text) {
        पूर्णाङ्क cursor_begin_utf8 = cursor_begin >= 0 ? (पूर्णाङ्क)SDL_utf8strnlen(text, cursor_begin) : -1;
        पूर्णाङ्क cursor_अन्तः_utf8 = cursor_अन्तः >= 0 ? (पूर्णाङ्क)SDL_utf8strnlen(text, cursor_अन्तः) : -1;
        पूर्णाङ्क cursor_आकार_utf8;
        यदि (cursor_अन्तः_utf8 >= 0) {
            यदि (cursor_begin_utf8 >= 0) {
                cursor_आकार_utf8 = cursor_अन्तः_utf8 - cursor_begin_utf8;
            } अन्यथा {
                cursor_आकार_utf8 = cursor_अन्तः_utf8;
            }
        } अन्यथा {
            cursor_आकार_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_आकार_utf8);
    } अन्यथा {
        SDL_SendEditingText("", 0, 0);
    }
}

स्थिर शून्य text_निवेशः_commit_string(शून्य *दत्त,
                                     संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                                     ध्रुव वर्ण *text)
{
    SDL_SendKeyboardText(text);
}

स्थिर शून्य text_निवेशः_delete_surrounding_text(शून्य *दत्त,
                                               संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                                               uint32_t before_दीर्घता,
                                               uint32_t after_दीर्घता)
{
    // FIXME: Do we care about this event?
}

स्थिर शून्य text_निवेशः_समाप्तम्(शून्य *दत्त,
                            संरचना zwp_text_निवेशः_v3 *zwp_text_निवेशः_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    यदि (!seat->text_निवेशः.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_निवेशः.has_preedit = false;
}

स्थिर ध्रुव संरचना zwp_text_निवेशः_v3_listener text_निवेशः_listener = {
    text_निवेशः_enter,
    text_निवेशः_leave,
    text_निवेशः_preedit_string,
    text_निवेशः_commit_string,
    text_निवेशः_delete_surrounding_text,
    text_निवेशः_समाप्तम्
};

स्थिर शून्य Wayland_दत्त_Device_समुच्चयः_ID(SDL_Wayland_दत्त_Device *दत्त_device)
{
    यदि (!दत्त_device->id_str)
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        यदि (dbus) {
            ध्रुव वर्ण *id = dbus->bus_get_unique_name(dbus->session_conn);
            यदि (id) {
                दत्त_device->id_str = SDL_strdup(id);
            }
        }
    }
    यदि (!दत्त_device->id_str)
#यदि_अन्तः
    {
        वर्ण id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, परिमाण(id), "%" SDL_PRIu64, pid);
        दत्त_device->id_str = SDL_strdup(id);
    }
}

स्थिर शून्य Wayland_Seat_Create_दत्त_Device(SDL_WaylandSeat *seat)
{
    यदि (!seat->display->दत्त_device_manager) {
        प्रत्यागम;
    }

    SDL_Wayland_दत्त_Device *दत्त_device = SDL_calloc(1, परिमाण(*दत्त_device));
    यदि (!दत्त_device) {
        प्रत्यागम;
    }

    दत्त_device->दत्त_device = wl_दत्त_device_manager_get_दत्त_device(
        seat->display->दत्त_device_manager, seat->wl_seat);
    दत्त_device->seat = seat;

    यदि (!दत्त_device->दत्त_device) {
        SDL_free(दत्त_device);
        प्रत्यागम;
    }

    Wayland_दत्त_Device_समुच्चयः_ID(दत्त_device);
    WAYLAND_wl_list_init(&दत्त_device->pending_drops);
    wl_दत्त_device_समुच्चयः_user_दत्त(दत्त_device->दत्त_device, दत्त_device);
    wl_दत्त_device_सङ्कलय_listener(दत्त_device->दत्त_device, &दत्त_device_listener, दत्त_device);
    seat->दत्त_device = दत्त_device;
}

शून्य Wayland_Display_Init_दत्त_Device_Manager(SDL_Video_दत्त *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_दत्त_Device(seat);
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
        zwp_primary_selection_device_v1_समुच्चयः_user_दत्त(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_सङ्कलय_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

शून्य Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_दत्त *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

स्थिर शून्य Wayland_Seat_Create_Text_निवेशः(SDL_WaylandSeat *seat)
{
    यदि (seat->display->text_निवेशः_manager) {
        seat->text_निवेशः.zwp_text_निवेशः = zwp_text_निवेशः_manager_v3_get_text_निवेशः(seat->display->text_निवेशः_manager, seat->wl_seat);

        यदि (seat->text_निवेशः.zwp_text_निवेशः) {
            zwp_text_निवेशः_v3_समुच्चयः_user_दत्त(seat->text_निवेशः.zwp_text_निवेशः, seat);
            zwp_text_निवेशः_v3_सङ्कलय_listener(seat->text_निवेशः.zwp_text_निवेशः,
                                           &text_निवेशः_listener, seat);
        }
    }
}

शून्य Wayland_Display_Init_Text_निवेशः_Manager(SDL_Video_दत्त *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_Text_निवेशः(seat);
    }
}

// Pen/Tablet support...
स्थिर शून्य tablet_tool_handle_type(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    विकल्प (type) {
        #परिभाषय CASE(typ) पक्ष ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; प्रत्यागम
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #अपरिभाषय CASE
        स्वभाव: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

स्थिर शून्य tablet_tool_handle_hardware_serial(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

स्थिर शून्य tablet_tool_handle_hardware_id_wacom(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->info.wacom_id = id_lo;
}

स्थिर शून्य tablet_tool_handle_capability(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    विकल्प (capability) {
        #परिभाषय CASE(wltyp,sdltyp) पक्ष ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; प्रत्यागम
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #अपरिभाषय CASE
        स्वभाव: भङ्ग;  // unsupported here.
    }
}

स्थिर शून्य tablet_tool_handle_समाप्तम्(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    यदि (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_गवाक्षः *गवाक्षः = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
        sdltool->instance_id = SDL_सङ्कलय_Pen_Device(0, रिक्त, गवाक्षः, &sdltool->info, sdltool, false);
    }
}

स्थिर शून्य tablet_tool_handle_removed(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    यदि (sdltool->instance_id) {
        SDL_गवाक्षः *गवाक्षः = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
        SDL_RemovePenDevice(0, गवाक्षः, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

स्थिर शून्य tablet_tool_handle_proximity_अन्तर्(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial, संरचना zwp_tablet_v2 *tablet, संरचना wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    SDL_गवाक्षः_दत्त *windowdata = surface ? Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(surface) : रिक्त;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : रिक्त;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.अन्तर्_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

स्थिर शून्य tablet_tool_handle_proximity_बहिर्गमनम्(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.have_proximity = true;
    sdltool->frame.अन्तर्_proximity = false;
}

स्थिर शून्य tablet_tool_handle_अधस्तात्(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_अधस्तात्;
}

स्थिर शून्य tablet_tool_handle_ऊर्ध्वम्(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_ऊर्ध्वम्;
}

स्थिर शून्य tablet_tool_handle_motion(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    SDL_गवाक्षः_दत्त *windowdata = sdltool->focus;
    यदि (windowdata) {
        sdltool->frame.x = (भिन्न)(wl_fixed_गन्तव्यम्_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (भिन्न)(wl_fixed_गन्तव्यम्_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

स्थिर शून्य tablet_tool_handle_pressure(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((भिन्न) pressure) / 65535.0f;
    sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_PRESSURE);
    यदि (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

स्थिर शून्य tablet_tool_handle_distance(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((भिन्न) distance) / 65535.0f;
    sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_DISTANCE);
    यदि (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

स्थिर शून्य tablet_tool_handle_tilt(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (भिन्न)(wl_fixed_गन्तव्यम्_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (भिन्न)(wl_fixed_गन्तव्यम्_double(ytilt));
    sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

स्थिर शून्य tablet_tool_handle_button(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
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
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_अधस्तात् : WAYLAND_TABLET_TOOL_BUTTON_ऊर्ध्वम्;
}

स्थिर शून्य tablet_tool_handle_rotation(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    ध्रुव भिन्न rotation = (भिन्न)(wl_fixed_गन्तव्यम्_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_ROTATION);
}

स्थिर शून्य tablet_tool_handle_slider(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_समुच्चयः |= (1u << SDL_PEN_AXIS_SLIDER);
}

स्थिर शून्य tablet_tool_handle_wheel(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

स्थिर शून्य tablet_tool_handle_frame(शून्य *दत्त, संरचना zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) दत्त;
    ध्रुव SDL_PenID instance_id = sdltool->instance_id;
    यदि (!instance_id) {
        प्रत्यागम;  // Not a pen we report on.
    }

    ध्रुव Uint64 timestamp = Wayland_Adjust_Event_Timestamp_आधारः(Wayland_EventTimestampMSToNS(time));
    SDL_गवाक्षः *गवाक्षः = sdltool->focus ? sdltool->focus->sdlwindow : रिक्त;
    ध्रुव bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    यदि (sdltool->frame.have_proximity && sdltool->frame.अन्तर्_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, गवाक्षः, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    यदि (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        यदि (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_अधस्तात्) {
            SDL_SendPenMotion(timestamp, instance_id, गवाक्षः, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, गवाक्षः, is_eraser, true);
        } अन्यथा {
            SDL_SendPenTouch(timestamp, instance_id, गवाक्षः, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, गवाक्षः, sdltool->frame.x, sdltool->frame.y);
        }
    } अन्यथा {
        यदि (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, गवाक्षः, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_अधस्तात्);
        }

        यदि (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, गवाक्षः, sdltool->frame.x, sdltool->frame.y);
        }
    }

    प्रति (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_गणनम्; i++) {
        यदि (sdltool->frame.axes_समुच्चयः & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, गवाक्षः, i, sdltool->frame.axes[i]);
        }
    }

    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        ध्रुव पूर्णाङ्क state = sdltool->frame.buttons[i];
        यदि (state) {
            SDL_SendPenButton(timestamp, instance_id, गवाक्षः, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_अधस्तात्);
        }
    }

    यदि (sdltool->frame.have_proximity && !sdltool->frame.अन्तर्_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, गवाक्षः, false, false);
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
    tablet_tool_handle_समाप्तम्,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_अन्तर्,
    tablet_tool_handle_proximity_बहिर्गमनम्,
    tablet_tool_handle_अधस्तात्,
    tablet_tool_handle_ऊर्ध्वम्,
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


स्थिर शून्य tablet_seat_handle_tablet_added(शून्य *दत्त, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

स्थिर शून्य tablet_seat_handle_tool_added(शून्य *दत्त, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)दत्त;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, परिमाण(*sdltool));

    यदि (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.अङ्कः_buttons = -1;

        यदि (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_निवेशय(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_सङ्कलय_listener(tool, &tablet_tool_listener, sdltool);
    }
}

स्थिर शून्य tablet_seat_handle_pad_added(शून्य *दत्त, संरचना zwp_tablet_seat_v2 *zwp_tablet_seat_v2, संरचना zwp_tablet_pad_v2 *pad)
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
    zwp_tablet_seat_v2_सङ्कलय_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

शून्य Wayland_DisplayInitTabletManager(SDL_Video_दत्त *display)
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

स्थिर शून्य Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_अधस्तात्)
{
    यदि (!shutting_अधस्तात्) {
        SDL_WaylandPenTool *tool, *अस्थायी;
        wl_list_for_each_safe (tool, अस्थायी, &seat->tablet.tool_list, link) {
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

शून्य Wayland_DisplayCreateSeat(SDL_Video_दत्त *display, संरचना wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, परिमाण(SDL_WaylandSeat));
    यदि (!seat) {
        प्रत्यागम;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_निवेशय(display->seat_list.पूर्व, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_दत्त_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_Text_निवेशः(seat);

    wl_seat_समुच्चयः_user_दत्त(seat->wl_seat, seat);
    wl_seat_सङ्कलय_listener(seat->wl_seat, &seat_listener, seat);

    यदि (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

शून्य Wayland_Display_Remove_गवाक्षः_References_From_Seats(SDL_Video_दत्त *display, SDL_गवाक्षः_दत्त *गवाक्षः)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        यदि (seat->keyboard.focus == गवाक्षः) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, गवाक्षः->surface);
        }

        यदि (seat->pointer.focus == गवाक्षः) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = रिक्त;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *अस्थायी;
        wl_list_for_each_safe (tp, अस्थायी, &seat->touch.points, link) {
            यदि (tp->surface == गवाक्षः->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            यदि (tool->focus == गवाक्षः) {
                tool->focus = रिक्त;
                Wayland_TabletToolUpdateCursor(tool);
                यदि (tool->instance_id) {
                    SDL_RemovePenDevice(0, गवाक्षः->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_दत्त *drop, *drop_अस्थायी;
        wl_list_for_each_safe (drop, drop_अस्थायी, &seat->दत्त_device->pending_drops, link) {
            यदि (drop->dnd_गवाक्षः == गवाक्षः->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                यदि (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_दत्त_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

शून्य Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_अधस्तात्)
{
    यदि (!seat) {
        प्रत्यागम;
    }

    SDL_free(seat->name);

    यदि (seat->दत्त_device) {
        यदि (seat->दत्त_device->selection_offer) {
            Wayland_दत्त_Offer_Destroy(seat->दत्त_device->selection_offer);
        }
        यदि (seat->दत्त_device->selection_source) {
            Wayland_दत्त_Source_Destroy(seat->दत्त_device->selection_source);
        }
        यदि (seat->दत्त_device->drag_offer) {
            Wayland_दत्त_Offer_Destroy(seat->दत्त_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_दत्त *drop, *drop_अस्थायी;
        wl_list_for_each_safe (drop, drop_अस्थायी, &seat->दत्त_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            यदि (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_दत्त_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        यदि (seat->दत्त_device->दत्त_device) {
            यदि (wl_दत्त_device_get_संस्करणम्(seat->दत्त_device->दत्त_device) >= WL_दत्त_DEVICE_RELEASE_SINCE_संस्करणम्) {
                wl_दत्त_device_release(seat->दत्त_device->दत्त_device);
            } अन्यथा {
                wl_दत्त_device_destroy(seat->दत्त_device->दत्त_device);
            }
        }
        SDL_free(seat->दत्त_device->id_str);
        SDL_free(seat->दत्त_device);
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

    यदि (seat->text_निवेशः.zwp_text_निवेशः) {
        zwp_text_निवेशः_v3_destroy(seat->text_निवेशः.zwp_text_निवेशः);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_अधस्तात्);

    यदि (wl_seat_get_संस्करणम्(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_संस्करणम्) {
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
            यदि (seat->pointer.focus->sdlwindow->flags & SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्) {
                यदि (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } अन्यथा {
                    relative_focus = seat->pointer.focus->keyboard_focus_गणनम् != 0;
                }
            } अन्यथा {
                relative_focus = SDL_GetMouse()->warp_emulation_सक्रिय;
            }
        }

        यदि (relative_focus) {
            यदि (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_सङ्कलय_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } अन्यथा यदि (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = रिक्त;
        }
    }
}

स्थिर शून्य Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_दत्त *display = seat->display;

    यदि (display->कुञ्चिका_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        यदि (seat->keyboard.कुञ्चिका_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.कुञ्चिका_inhibitor);
            seat->keyboard.कुञ्चिका_inhibitor = रिक्त;
        }

        यदि (seat->keyboard.wl_keyboard) {
            SDL_गवाक्षः_दत्त *w = seat->keyboard.focus;
            यदि (w) {
                SDL_गवाक्षः *गवाक्षः = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                यदि (गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED) {
                    seat->keyboard.कुञ्चिका_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->कुञ्चिका_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

शून्य Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_दत्त *display = seat->display;
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

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_तालकम्_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, रिक्त,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_सङ्कलय_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

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

            SDL_गवाक्षः_दत्त *w = seat->pointer.focus;
            यदि (!w) {
                प्रत्यागम;
            }

            SDL_गवाक्षः *गवाक्षः = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            यदि (!(गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) ||
                (!(गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED) && SDL_Rect_रिक्तानि(&गवाक्षः->mouse_rect))) {
                प्रत्यागम;
            }

            संरचना wl_region *confine_rect = रिक्त;
            यदि (!SDL_Rect_रिक्तानि(&गवाक्षः->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(गवाक्षः, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_सङ्कलय(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                यदि (!SDL_Point_अन्तर्_Rect(&seat->pointer.चरमः_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    पूर्णाङ्क closest_x = seat->pointer.चरमः_motion.x;
                    पूर्णाङ्क closest_y = seat->pointer.चरमः_motion.y;

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

            यदि (confine_rect || (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED)) {
                यदि (गवाक्षः->mouse_rect.w != 1 && गवाक्षः->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_सङ्कलय_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } अन्यथा {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_तालकम्_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                रिक्त,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_सङ्कलय_listener(seat->pointer.locked_pointer,
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

शून्य Wayland_DisplayUpdatePointerGrabs(SDL_Video_दत्त *display, SDL_गवाक्षः_दत्त *गवाक्षः)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        यदि (!गवाक्षः || seat->pointer.focus == गवाक्षः) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

शून्य Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_दत्त *display, SDL_गवाक्षः_दत्त *गवाक्षः)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        यदि (!गवाक्षः || seat->keyboard.focus == गवाक्षः) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

शून्य Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    यदि (serial > seat->चरमः_implicit_grab_serial) {
        seat->चरमः_implicit_grab_serial = serial;
        seat->display->चरमः_implicit_grab_seat = seat;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
