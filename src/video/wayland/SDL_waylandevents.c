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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_scancode_tables_c.h"
#అన్తర్భావ "../../events/SDL_keysym_to_keycode_c.h"
#అన్తర్భావ "../../core/linux/SDL_system_theme.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylandwindow.h"
#అన్తర్భావ "SDL_waylandmouse.h"
#అన్తర్భావ "SDL_waylandclipboard.h"
#అన్తర్భావ "SDL_waylandkeyboard.h"

#అన్తర్భావ "pointer-constraints-unstable-v1-client-protocol.h"
#అన్తర్భావ "relative-pointer-unstable-v1-client-protocol.h"
#అన్తర్భావ "xdg-shell-client-protocol.h"
#అన్తర్భావ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#అన్తర్భావ "text-input-unstable-v3-client-protocol.h"
#అన్తర్భావ "tablet-v2-client-protocol.h"
#అన్తర్భావ "primary-selection-unstable-v1-client-protocol.h"
#అన్తర్భావ "input-timestamps-unstable-v1-client-protocol.h"
#అన్తర్భావ "pointer-gestures-unstable-v1-client-protocol.h"
#అన్తర్భావ "cursor-shape-v1-client-protocol.h"
#అన్తర్భావ "viewporter-client-protocol.h"

#నిర్వచితమైతే HAVE_LIBDECOR_H
#అన్తర్భావ <libdecor.h>
#అయితే_ముగింపు

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ <linux/input.h>
#లేకపోతే
#నిర్వచించు BTN_ఎడమ    (0x110)
#నిర్వచించు BTN_కుడి   (0x111)
#నిర్వచించు BTN_మధ్య  (0x112)
#నిర్వచించు BTN_SIDE    (0x113)
#నిర్వచించు BTN_EXTRA   (0x114)
#నిర్వచించు BTN_STYLUS  (0x14b)
#నిర్వచించు BTN_STYLUS2 (0x14c)
#నిర్వచించు BTN_STYLUS3 (0x149)
#అయితే_ముగింపు
#అన్తర్భావ "../../events/SDL_keysym_to_scancode_c.h"
#అన్తర్భావ "../../events/imKStoUCS.h"
#అన్తర్భావ <errno.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <xkbcommon/xkbcommon-compose.h>
#అన్తర్భావ <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#నిర్వచించు WAYLAND_WHEEL_AXIS_UNIT 10

#నిర్వచితం_కాకపోతే XKB_MOD_NAME_MOD3
#నిర్వచించు XKB_MOD_NAME_MOD3 "Mod3"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే XKB_MOD_NAME_MOD5
#నిర్వచించు XKB_MOD_NAME_MOD5 "Mod5"
#అయితే_ముగింపు

// Keyboard and mouse names to match XWayland
#నిర్వచించు WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#నిర్వచించు WAYLAND_DEFAULT_సూచిక_NAME "Virtual core pointer"
#నిర్వచించు WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#నిర్వచించు WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_గమ్యం_NS(10)

// Timer rollover detection thresholds
#నిర్వచించు WAYLAND_TIMER_ROLLOVER_INTERVAL_దిగువ  (SDL_MAX_UINT32 / 16U)
#నిర్వచించు WAYLAND_TIMER_ROLLOVER_INTERVAL_ఎగువ (WAYLAND_TIMER_ROLLOVER_INTERVAL_దిగువ * 15U)

// Scoped function declarations
స్థిర శూన్య Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

రకనిర్వచనం నిర్మాణం
{
    Uint32 కీలకం;
    SDL_Scancode scancode;
} Wayland_Reserved_కీలకం;

రకనిర్వచనం నిర్మాణం
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    నిర్మాణం wl_surface *surface;

    నిర్మాణం wl_list link;
} SDL_Wayland_Touch_బిందువు;

స్థిర శూన్య Wayland_Seat_కూడు_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, నిర్మాణం wl_surface *surface)
{
    SDL_Wayland_Touch_బిందువు *tp = SDL_malloc(పరిమాణం(SDL_Wayland_Touch_బిందువు));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_చొప్పించు(&seat->touch.points, &tp->link);
}

స్థిర శూన్య Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_బిందువు *tp)
{
    ఒకవేళ (tp->surface) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(tp->surface);

        ఒకవేళ (కిటికీ_దత్తాంశం_2) {
            స్థిరరాశి దశాంశం x = (దశాంశం)(wl_fixed_గమ్యం_double(tp->fx) / కిటికీ_దత్తాంశం_2->current.logical_వెడల్పు);
            స్థిరరాశి దశాంశం y = (దశాంశం)(wl_fixed_గమ్యం_double(tp->fy) / కిటికీ_దత్తాంశం_2->current.logical_ఎత్తు);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), కిటికీ_దత్తాంశం_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --కిటికీ_దత్తాంశం_2->చురుకైన_touch_లెక్క;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ఒకవేళ (SDL_GetMouseFocus() == కిటికీ_దత్తాంశం_2->sdlwindow && !కిటికీ_దత్తాంశం_2->keyboard_focus_లెక్క &&
                !కిటికీ_దత్తాంశం_2->సూచిక_focus_లెక్క && !కిటికీ_దత్తాంశం_2->చురుకైన_touch_లెక్క) {
                SDL_సమితి_Mouse_Focus(ఖాళీ);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

స్థిర శూన్య Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, నిర్మాణం wl_surface **surface)
{
    SDL_Wayland_Touch_బిందువు *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ఒకవేళ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ఒకవేళ (surface) {
                *surface = tp->surface;
            }
            ఆపు;
        }
    }
}

స్థిర శూన్య Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, నిర్మాణం wl_surface **surface)
{
    SDL_Wayland_Touch_బిందువు *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ఒకవేళ (tp->id == id) {
            ఒకవేళ (fx) {
                *fx = tp->fx;
            }
            ఒకవేళ (fy) {
                *fy = tp->fy;
            }
            ఒకవేళ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            ఆపు;
        }
    }
}

స్థిర శూన్య Wayland_GetScaledMouseRect(SDL_కిటికీ *కిటికీ, SDL_Rect *scaled_rect)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = కిటికీ->అంతర్గత;

    scaled_rect->x = (పూర్ణాంకం)SDL_floor(కిటికీ->mouse_rect.x / కిటికీ_దత్తాంశం_2->సూచిక_scale.x);
    scaled_rect->y = (పూర్ణాంకం)SDL_floor(కిటికీ->mouse_rect.y / కిటికీ_దత్తాంశం_2->సూచిక_scale.y);
    scaled_rect->w = (పూర్ణాంకం)SDL_ceil(కిటికీ->mouse_rect.w / కిటికీ_దత్తాంశం_2->సూచిక_scale.x);
    scaled_rect->h = (పూర్ణాంకం)SDL_ceil(కిటికీ->mouse_rect.h / కిటికీ_దత్తాంశం_2->సూచిక_scale.y);
}

స్థిర Uint64 Wayland_Adjust_Event_Timestamp_పునాది(Uint64 nsTimestamp)
{
    స్థిర Uint64 timestamp_స్థానభ్రంశం = 0;
    స్థిరరాశి Uint64 now = SDL_GetTicksNS();

    ఒకవేళ (!timestamp_స్థానభ్రంశం) {
        timestamp_స్థానభ్రంశం = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_స్థానభ్రంశం;

    ఒకవేళ (nsTimestamp > now) {
        timestamp_స్థానభ్రంశం -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    తిరిగి nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
స్థిర Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    స్థిర Uint64 timestamp_స్థానభ్రంశం = 0;
    స్థిర Uint32 చివరి = 0;
    Uint64 timestamp = SDL_MS_గమ్యం_NS(wl_timestamp_ms) + timestamp_స్థానభ్రంశం;

    ఒకవేళ (wl_timestamp_ms >= చివరి) {
        ఒకవేళ (timestamp_స్థానభ్రంశం && చివరి < WAYLAND_TIMER_ROLLOVER_INTERVAL_దిగువ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_ఎగువ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_గమ్యం_NS(SDL_UINT64_C(0x100000000));
        } లేకపోతే {
            చివరి = wl_timestamp_ms;
        }
    } లేకపోతే {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ఒకవేళ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_దిగువ && చివరి > WAYLAND_TIMER_ROLLOVER_INTERVAL_ఎగువ) {
            timestamp_స్థానభ్రంశం += SDL_MS_గమ్యం_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_గమ్యం_NS(SDL_UINT64_C(0x100000000));
            చివరి = wl_timestamp_ms;
        }
    }

    తిరిగి timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

స్థిర Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    స్థిరరాశి Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    తిరిగి Wayland_Adjust_Event_Timestamp_పునాది(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

స్థిర Uint64 Wayland_Get_సూచిక_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    స్థిరరాశి Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    తిరిగి Wayland_Adjust_Event_Timestamp_పునాది(seat->సూచిక_2.timestamps ? seat->సూచిక_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    స్థిరరాశి Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    తిరిగి Wayland_Adjust_Event_Timestamp_పునాది(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

స్థిర శూన్య ఆదానం_timestamp_listener(శూన్య *దత్తాంశం, నిర్మాణం zwp_ఆదానం_timestamps_v1 *zwp_ఆదానం_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)దత్తాంశం) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_చొప్పున_రెండవ) + tv_nsec;
}

స్థిర స్థిరరాశి నిర్మాణం zwp_ఆదానం_timestamps_v1_listener timestamp_listener = {
    ఆదానం_timestamp_listener
};

స్థిర శూన్య Wayland_Seat_రిజిస్టరు_ఆదానం_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->display->ఆదానం_timestamps_manager) {
        ఒకవేళ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ఆదానం_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ఆదానం_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ఆదానం_timestamps_v1_కూడు_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ఒకవేళ (seat->సూచిక_2.wl_సూచిక && !seat->సూచిక_2.timestamps) {
            seat->సూచిక_2.timestamps = zwp_ఆదానం_timestamps_manager_v1_get_సూచిక_timestamps(seat->display->ఆదానం_timestamps_manager, seat->సూచిక_2.wl_సూచిక);
            zwp_ఆదానం_timestamps_v1_కూడు_listener(seat->సూచిక_2.timestamps, &timestamp_listener, &seat->సూచిక_2.highres_timestamp_ns);
        }

        ఒకవేళ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ఆదానం_timestamps_manager_v1_get_touch_timestamps(seat->display->ఆదానం_timestamps_manager, seat->touch.wl_touch);
            zwp_ఆదానం_timestamps_v1_కూడు_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

శూన్య Wayland_Display_Init_ఆదానం_Timestamp_Manager(SDL_Video_దత్తాంశం *display)
{
    ఒకవేళ (display->ఆదానం_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_రిజిస్టరు_ఆదానం_Timestamp_Listeners(seat);
        }
    }
}

స్థిర శూన్య handle_pinch_begin(శూన్య *దత్తాంశం, నిర్మాణం zwp_సూచిక_gesture_pinch_v1 *zwp_సూచిక_gesture_pinch_v1, uint32_t serial, uint32_t సమయం, నిర్మాణం wl_surface *surface, uint32_t fingers)
{
    ఒకవేళ (!surface) {
        తిరిగి;
    }

    SDL_కిటికీ_దత్తాంశం *wind = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);
    ఒకవేళ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
        seat->సూచిక_2.gesture_focus = wind;

        స్థిరరాశి Uint64 timestamp = Wayland_Get_సూచిక_Timestamp(seat, సమయం);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

స్థిర శూన్య handle_pinch_update(శూన్య *దత్తాంశం, నిర్మాణం zwp_సూచిక_gesture_pinch_v1 *zwp_సూచిక_gesture_pinch_v1, uint32_t సమయం,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;

    ఒకవేళ (seat->సూచిక_2.gesture_focus) {
        స్థిరరాశి Uint64 timestamp = Wayland_Get_సూచిక_Timestamp(seat, సమయం);
        స్థిరరాశి దశాంశం s = (దశాంశం)wl_fixed_గమ్యం_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->సూచిక_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

స్థిర శూన్య handle_pinch_చివర(శూన్య *దత్తాంశం, నిర్మాణం zwp_సూచిక_gesture_pinch_v1 *zwp_సూచిక_gesture_pinch_v1, uint32_t serial, uint32_t సమయం, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;

    ఒకవేళ (seat->సూచిక_2.gesture_focus) {
        స్థిరరాశి Uint64 timestamp = Wayland_Get_సూచిక_Timestamp(seat, సమయం);
        SDL_SendPinch(SDL_EVENT_PINCH_చివర, timestamp, seat->సూచిక_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->సూచిక_2.gesture_focus = ఖాళీ;
    }
}

స్థిర స్థిరరాశి నిర్మాణం zwp_సూచిక_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_చివర
};

స్థిర శూన్య Wayland_Seat_Create_సూచిక_Gestures(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->display->zwp_సూచిక_gestures) {
        ఒకవేళ (seat->సూచిక_2.wl_సూచిక && !seat->సూచిక_2.gesture_pinch) {
            seat->సూచిక_2.gesture_pinch = zwp_సూచిక_gestures_v1_get_pinch_gesture(seat->display->zwp_సూచిక_gestures, seat->సూచిక_2.wl_సూచిక);
            zwp_సూచిక_gesture_pinch_v1_సమితి_user_దత్తాంశం(seat->సూచిక_2.gesture_pinch, seat);
            zwp_సూచిక_gesture_pinch_v1_కూడు_listener(seat->సూచిక_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

శూన్య Wayland_Display_Init_సూచిక_Gesture_Manager(SDL_Video_దత్తాంశం *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_సూచిక_Gestures(seat);
    }
}

స్థిర శూన్య Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->display->cursor_shape_manager) {
        ఒకవేళ (seat->సూచిక_2.wl_సూచిక && !seat->సూచిక_2.cursor_state.cursor_shape) {
            seat->సూచిక_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_సూచిక(seat->display->cursor_shape_manager, seat->సూచిక_2.wl_సూచిక);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ఒకవేళ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

శూన్య Wayland_DisplayInitCursorShapeManager(SDL_Video_దత్తాంశం *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

స్థిర శూన్య Wayland_Seat_సమితి_Keymap(SDL_WaylandSeat *seat)
{
    స్థిరరాశి bool send_event = !seat->display->initializing;

    ఒకవేళ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.అంకె_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_సమితి_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_సమితి_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
స్థిర శూన్య keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    అయితే (elapsed >= repeat_info->తదుపరి_repeat_ns) {
        ఒకవేళ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            స్థిరరాశి Uint64 timestamp = repeat_info->పునాది_సమయం_ns + repeat_info->తదుపరి_repeat_ns;
            SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_పునాది(timestamp), repeat_info->keyboard_id, repeat_info->కీలకం, repeat_info->scancode, true);
        }
        ఒకవేళ (repeat_info->పాఠ్యం[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_పాఠ్యం(repeat_info->పాఠ్యం);
        }
        repeat_info->తదుపరి_repeat_ns += SDL_NS_చొప్పున_రెండవ / (Uint64)repeat_info->repeat_రేటు;
    }
}

స్థిర శూన్య keyboard_repeat_సమితి(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t కీలకం, Uint32 wl_press_సమయం_ms,
                                Uint64 పునాది_సమయం_ns, uint32_t scancode, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    ఒకవేళ (!repeat_info->repeat_రేటు) {
        తిరిగి;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->కీలకం = కీలకం;
    repeat_info->wl_press_సమయం_ms = wl_press_సమయం_ms;
    repeat_info->పునాది_సమయం_ns = పునాది_సమయం_ns;
    repeat_info->sdl_press_సమయం_ns = SDL_GetTicksNS();
    repeat_info->తదుపరి_repeat_ns = SDL_MS_గమ్యం_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ఒకవేళ (పాఠ్యం) {
        SDL_strlcpy(repeat_info->పాఠ్యం, పాఠ్యం, SDL_arraysize(repeat_info->పాఠ్యం));
    } లేకపోతే {
        repeat_info->పాఠ్యం[0] = '\0';
    }
}

స్థిర శూన్య sync_పూర్తి_handler(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *callback, uint32_t callback_దత్తాంశం)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

స్థిర నిర్మాణం wl_callback_listener sync_listener = {
    sync_పూర్తి_handler
};

శూన్య Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *d = _this->అంతర్గత;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    నిర్మాణం wl_callback *cb = wl_display_sync(d->display);
    wl_callback_కూడు_listener(cb, &sync_listener, ఖాళీ);
    WAYLAND_wl_display_flush(d->display);
}

పూర్ణాంకం Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_దత్తాంశం *d = _this->అంతర్గత;
    SDL_WaylandSeat *seat;
    Uint64 ప్రారంభం = SDL_GetTicksNS();
    స్థిరరాశి పూర్ణాంకం display_fd = WAYLAND_wl_display_get_fd(d->display);
    పూర్ణాంకం ret;
    bool poll_alarm_సమితి = false;

#నిర్వచితమైతే SDL_USE_IME
    SDL_కిటికీ *keyboard_focus = SDL_GetKeyboardFocus();
    ఒకవేళ (!d->పాఠ్యం_ఆదానం_manager && keyboard_focus && SDL_పాఠ్యం_ఆదానం_చురుకైన(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ఒకవేళ (timeoutNS < 0 || SDL_MS_గమ్యం_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_గమ్యం_NS(200);
            poll_alarm_సమితి = true;
        }
    }
#అయితే_ముగింపు

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ఒకవేళ (seat->keyboard.repeat.కీలకం) {
            స్థిరరాశి Uint64 elapsed = ప్రారంభం - seat->keyboard.repeat.sdl_press_సమయం_ns;
            స్థిరరాశి Uint64 తదుపరి_repeat_wait_సమయం = (seat->keyboard.repeat.తదుపరి_repeat_ns - elapsed) + 1;
            ఒకవేళ (timeoutNS < 0 || తదుపరి_repeat_wait_సమయం <= timeoutNS) {
                timeoutNS = తదుపరి_repeat_wait_సమయం;
                poll_alarm_సమితి = true;
            }
        }
    }

    ఒకవేళ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ఒకవేళ (timeoutNS > 0) {
            స్థిరరాశి Uint64 now = SDL_GetTicksNS();
            స్థిరరాశి Uint64 elapsed = now - ప్రారంభం;
            ప్రారంభం = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ఒకవేళ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ఒకవేళ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ఒకవేళ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            తిరిగి errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ఒకవేళ (timeoutNS > 0) {
            స్థిరరాశి Uint64 now = SDL_GetTicksNS();
            స్థిరరాశి Uint64 elapsed = now - ప్రారంభం;
            ప్రారంభం = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ఒకవేళ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ఒకవేళ (ret == 0) {
                తిరిగి poll_alarm_సమితి ? 1 : 0;
            } లేకపోతే {
                // Pump events on an interrupt or broken pipe to handle the error.
                తిరిగి errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ఒకవేళ (ret == -1) {
            తిరిగి ret;
        }
    }

    // Signal to the caller that there might be an event available.
    తిరిగి 1;
}

శూన్య Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *d = _this->అంతర్గత;
    SDL_WaylandSeat *seat;
    స్థిరరాశి పూర్ణాంకం display_fd = WAYLAND_wl_display_get_fd(d->display);
    పూర్ణాంకం ret = 0;

#నిర్వచితమైతే SDL_USE_IME
    SDL_కిటికీ *keyboard_focus = SDL_GetKeyboardFocus();
    ఒకవేళ (!d->పాఠ్యం_ఆదానం_manager && keyboard_focus && SDL_పాఠ్యం_ఆదానం_చురుకైన(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#అయితే_ముగింపు

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ఒకవేళ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ఒకవేళ (ret < 0) {
            వెళ్ళు connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ఒకవేళ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ఒకవేళ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_గమ్యం_NS(4));
            ఒకవేళ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ఒకవేళ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            వెళ్ళు connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ఒకవేళ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ఒకవేళ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } లేకపోతే {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } లేకపోతే {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ఒకవేళ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ఒకవేళ (seat->keyboard.repeat.కీలకం) {
                Wayland_Seat_సమితి_Keymap(seat);

                స్థిరరాశి Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_సమయం_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ఒకవేళ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

స్థిర శూన్య సూచిక_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = seat->సూచిక_2.focus;
    SDL_కిటికీ *కిటికీ = కిటికీ_దత్తాంశం_2 ? కిటికీ_దత్తాంశం_2->sdlwindow : ఖాళీ;

    ఒకవేళ (కిటికీ_దత్తాంశం_2) {
        ద్విగుణ sx = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.absolute.sx);
        ద్విగుణ sy = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.absolute.sy);

        ఒకవేళ (seat->సూచిక_2.focus_surface == కిటికీ_దత్తాంశం_2->ముసుగు.surface) {
            sx += (ద్విగుణ)కిటికీ_దత్తాంశం_2->ముసుగు.స్థానభ్రంశం_x;
            sy += (ద్విగుణ)కిటికీ_దత్తాంశం_2->ముసుగు.స్థానభ్రంశం_y;
        }

        sx *= కిటికీ_దత్తాంశం_2->సూచిక_scale.x;
        sy *= కిటికీ_దత్తాంశం_2->సూచిక_scale.y;
        ఒకవేళ (!warp) {
            SDL_SendMouseMotion(seat->సూచిక_2.pending_చట్రం.timestamp_ns, కిటికీ_దత్తాంశం_2->sdlwindow, seat->సూచిక_2.sdl_id, false, (దశాంశం)sx, (దశాంశం)sy);
        } లేకపోతే {
            SDL_SendMouseWarp(seat->సూచిక_2.pending_చట్రం.timestamp_ns, కిటికీ_దత్తాంశం_2->sdlwindow, seat->సూచిక_2.sdl_id, (దశాంశం)sx, (దశాంశం)sy);
        }

        seat->సూచిక_2.చివరి_motion.x = (పూర్ణాంకం)SDL_floor(sx);
        seat->సూచిక_2.చివరి_motion.y = (పూర్ణాంకం)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ఒకవేళ (!SDL_Rect_ఖాళీలు(&కిటికీ->mouse_rect) && !seat->సూచిక_2.is_confined) {
            Wayland_Seat_Update_సూచిక_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE) && కిటికీ->తగిలింది_test) {
            SDL_తగిలింది_Test_ఫలితం rc = కిటికీ->తగిలింది_test(కిటికీ, &seat->సూచిక_2.చివరి_motion, కిటికీ->తగిలింది_test_దత్తాంశం);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            ఎంపిక (rc) {
            స్థితి SDL_HITTEST_RESIZE_TOPLEFT:
                ఒకవేళ ((కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం) &&
                    (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ)) {
                    rc = SDL_HITTEST_సాధారణ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం) {
                    rc = SDL_HITTEST_RESIZE_ఎడమ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ) {
                    rc = SDL_HITTEST_RESIZE_శిఖరం;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_శిఖరం:
                ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం) {
                    rc = SDL_HITTEST_సాధారణ;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_TOPRIGHT:
                ఒకవేళ ((కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం) &&
                    (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_కుడి)) {
                    rc = SDL_HITTEST_సాధారణ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం) {
                    rc = SDL_HITTEST_RESIZE_కుడి;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_కుడి) {
                    rc = SDL_HITTEST_RESIZE_శిఖరం;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_కుడి:
                ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_కుడి) {
                    rc = SDL_HITTEST_సాధారణ;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ఒకవేళ ((కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_కుడి)) {
                    rc = SDL_HITTEST_సాధారణ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_కుడి;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_కుడి) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_BOTTOM:
                ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_సాధారణ;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ఒకవేళ ((కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ)) {
                    rc = SDL_HITTEST_సాధారణ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ఎడమ;
                } లేకపోతే ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                ఆపు;
            స్థితి SDL_HITTEST_RESIZE_ఎడమ:
                ఒకవేళ (కిటికీ_దత్తాంశం_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ) {
                    rc = SDL_HITTEST_సాధారణ;
                }
                ఆపు;
            అప్రమేయ:
                ఆపు;
            }

            ఒకవేళ (rc != కిటికీ_దత్తాంశం_2->తగిలింది_test_ఫలితం) {
                కిటికీ_దత్తాంశం_2->తగిలింది_test_ఫలితం = rc;
                Wayland_Seat_Update_సూచిక_Cursor(seat);
            }
        }
    }
}

స్థిర శూన్య సూచిక_handle_motion(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                  uint32_t సమయం, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    స్థిరరాశి Uint64 timestamp = Wayland_Get_సూచిక_Timestamp(seat, సమయం);

    seat->సూచిక_2.pending_చట్రం.absolute.sx = sx;
    seat->సూచిక_2.pending_చట్రం.absolute.sy = sy;

    ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) >= WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        seat->సూచిక_2.pending_చట్రం.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ఒకవేళ (!seat->సూచిక_2.pending_చట్రం.have_relative || seat->సూచిక_2.timestamps) {
            seat->సూచిక_2.pending_చట్రం.timestamp_ns = timestamp;
        }
    } లేకపోతే {
        seat->సూచిక_2.pending_చట్రం.timestamp_ns = timestamp;
        సూచిక_dispatch_absolute_motion(seat, false);
    }
}

స్థిర శూన్య సూచిక_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(seat->సూచిక_2.pending_చట్రం.enter_surface);
    ఒకవేళ (!కిటికీ) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        తిరిగి;
    }

    ఒకవేళ (కిటికీ->surface != seat->సూచిక_2.pending_చట్రం.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_సమితి_Default_Cursor(seat);
        తిరిగి;
    }

    seat->సూచిక_2.focus = కిటికీ;
    seat->సూచిక_2.focus_surface = seat->సూచిక_2.pending_చట్రం.enter_surface;
    ++కిటికీ->సూచిక_focus_లెక్క;
    SDL_సమితి_Mouse_Focus(కిటికీ->sdlwindow);

    // Send the initial position.
    సూచిక_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_సూచిక_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_సూచిక_Cursor(seat);
}

స్థిర శూన్య సూచిక_handle_enter(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                 uint32_t serial, నిర్మాణం wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ఒకవేళ (!surface) {
        // Enter event for a destroyed surface.
        తిరిగి;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.pending_చట్రం.enter_surface = surface;
    seat->సూచిక_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->సూచిక_2.pending_చట్రం.absolute.sx = sx_w;
    seat->సూచిక_2.pending_చట్రం.absolute.sy = sy_w;

    ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) < WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->సూచిక_2.pending_చట్రం.timestamp_ns = 0;
        సూచిక_dispatch_enter(seat);
    }
}

స్థిర శూన్య సూచిక_dispatch_leave(SDL_WaylandSeat *seat, bool update_సూచిక)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(seat->సూచిక_2.pending_చట్రం.leave_surface);

    ఒకవేళ (కిటికీ) {
        ఒకవేళ (seat->సూచిక_2.focus) {
            ఒకవేళ (seat->సూచిక_2.focus->surface == seat->సూచిక_2.pending_చట్రం.leave_surface) {
                // Clear the capture flag and raise all buttons
                కిటికీ->sdlwindow->flags &= ~SDL_కిటికీ_MOUSE_CAPTURE;

                seat->సూచిక_2.focus = ఖాళీ;
                seat->సూచిక_2.focus_surface = ఖాళీ;
                కొరకు (Uint8 i = 1; seat->సూచిక_2.buttons_pressed; ++i) {
                    ఒకవేళ (seat->సూచిక_2.buttons_pressed & SDL_BUTTON_ముసుగు(i)) {
                        SDL_SendMouseButton(0, కిటికీ->sdlwindow, seat->సూచిక_2.sdl_id, i, false);
                        seat->సూచిక_2.buttons_pressed &= ~SDL_BUTTON_ముసుగు(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_కిటికీ *mouse_focus = SDL_GetMouseFocus();
                స్థిరరాశి bool had_focus = mouse_focus && కిటికీ->sdlwindow == mouse_focus;
                ఒకవేళ (!--కిటికీ->సూచిక_focus_లెక్క && had_focus && !కిటికీ->చురుకైన_touch_లెక్క) {
                    SDL_సమితి_Mouse_Focus(ఖాళీ);
                }

                ఒకవేళ (update_సూచిక) {
                    Wayland_Seat_Update_సూచిక_Grab(seat);
                    Wayland_Seat_Update_సూచిక_Cursor(seat);
                }
            }
        } లేకపోతే ఒకవేళ (update_సూచిక) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

స్థిర శూన్య సూచిక_handle_leave(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                 uint32_t serial, నిర్మాణం wl_surface *surface)
{
    ఒకవేళ (!surface) {
        // Leave event for a destroyed surface.
        తిరిగి;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.pending_చట్రం.leave_surface = surface;
    ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) < WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        సూచిక_dispatch_leave(seat, true);
    }
}

స్థిర bool Wayland_Process_తగిలింది_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ఒకవేళ (seat->సూచిక_2.locked_సూచిక) {
        తిరిగి false;
    }

    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = seat->సూచిక_2.focus;
    SDL_కిటికీ *కిటికీ = కిటికీ_దత్తాంశం_2->sdlwindow;

    ఒకవేళ (కిటికీ->తగిలింది_test) {
        స్థిర స్థిరరాశి uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_అంచు_శిఖరం_ఎడమ, XDG_TOPLEVEL_RESIZE_అంచు_శిఖరం,
            XDG_TOPLEVEL_RESIZE_అంచు_శిఖరం_కుడి, XDG_TOPLEVEL_RESIZE_అంచు_కుడి,
            XDG_TOPLEVEL_RESIZE_అంచు_BOTTOM_కుడి, XDG_TOPLEVEL_RESIZE_అంచు_BOTTOM,
            XDG_TOPLEVEL_RESIZE_అంచు_BOTTOM_ఎడమ, XDG_TOPLEVEL_RESIZE_అంచు_ఎడమ
        };

#నిర్వచితమైతే HAVE_LIBDECOR_H
        స్థిర స్థిరరాశి uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_అంచు_శిఖరం_ఎడమ, LIBDECOR_RESIZE_అంచు_శిఖరం,
            LIBDECOR_RESIZE_అంచు_శిఖరం_కుడి, LIBDECOR_RESIZE_అంచు_కుడి,
            LIBDECOR_RESIZE_అంచు_BOTTOM_కుడి, LIBDECOR_RESIZE_అంచు_BOTTOM,
            LIBDECOR_RESIZE_అంచు_BOTTOM_ఎడమ, LIBDECOR_RESIZE_అంచు_ఎడమ
        };
#అయితే_ముగింపు

        ఎంపిక (కిటికీ_దత్తాంశం_2->తగిలింది_test_ఫలితం) {
        స్థితి SDL_HITTEST_DRAGGABLE:
#నిర్వచితమైతే HAVE_LIBDECOR_H
            ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface.libdecor.చట్రం) {
                    libdecor_చట్రం_move(కిటికీ_దత్తాంశం_2->shell_surface.libdecor.చట్రం,
                                        seat->wl_seat,
                                        serial);
                }
            } లేకపోతే
#అయితే_ముగింపు
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(కిటికీ_దత్తాంశం_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            తిరిగి true;

        స్థితి SDL_HITTEST_RESIZE_TOPLEFT:
        స్థితి SDL_HITTEST_RESIZE_శిఖరం:
        స్థితి SDL_HITTEST_RESIZE_TOPRIGHT:
        స్థితి SDL_HITTEST_RESIZE_కుడి:
        స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        స్థితి SDL_HITTEST_RESIZE_BOTTOM:
        స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT:
        స్థితి SDL_HITTEST_RESIZE_ఎడమ:
#నిర్వచితమైతే HAVE_LIBDECOR_H
            ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface.libdecor.చట్రం) {
                    libdecor_చట్రం_resize(కిటికీ_దత్తాంశం_2->shell_surface.libdecor.చట్రం,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[కిటికీ_దత్తాంశం_2->తగిలింది_test_ఫలితం - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } లేకపోతే
#అయితే_ముగింపు
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ఒకవేళ (కిటికీ_దత్తాంశం_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(కిటికీ_దత్తాంశం_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[కిటికీ_దత్తాంశం_2->తగిలింది_test_ఫలితం - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            తిరిగి true;

        అప్రమేయ:
            తిరిగి false;
        }
    }

    తిరిగి false;
}

స్థిర శూన్య సూచిక_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool కిందికి)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = seat->సూచిక_2.focus;

    ఒకవేళ (కిటికీ) {
        bool ignore_click = false;

        ఒకవేళ (కిందికి) {
            seat->సూచిక_2.buttons_pressed |= SDL_BUTTON_ముసుగు(sdl_button);

            ఒకవేళ (sdl_button == SDL_BUTTON_ఎడమ && Wayland_Process_తగిలింది_Test(seat, seat->చివరి_implicit_grab_serial)) {
                తిరిగి; // don't pass this event on to app.
            }
        } లేకపోతే {
            seat->సూచిక_2.buttons_pressed &= ~SDL_BUTTON_ముసుగు(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ఒకవేళ (కిటికీ->చివరి_focus_event_సమయం_ns) {
            ఒకవేళ (కిందికి && (SDL_GetTicksNS() - కిటికీ->చివరి_focus_event_సమయం_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            కిటికీ->చివరి_focus_event_సమయం_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        ఒకవేళ (!seat->సూచిక_2.relative_సూచిక) {
            ఒకవేళ (seat->సూచిక_2.buttons_pressed != 0) {
                కిటికీ->sdlwindow->flags |= SDL_కిటికీ_MOUSE_CAPTURE;
            } లేకపోతే {
                కిటికీ->sdlwindow->flags &= ~SDL_కిటికీ_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ఒకవేళ (seat->సూచిక_2.focus_surface != కిటికీ->surface) {
                    seat->సూచిక_2.pending_చట్రం.leave_surface = కిటికీ->surface;
                }
            }
        }

        ఒకవేళ (!ignore_click) {
            SDL_SendMouseButton(seat->సూచిక_2.pending_చట్రం.timestamp_ns, కిటికీ->sdlwindow, seat->సూచిక_2.sdl_id, sdl_button, కిందికి);
        }
    }
}

స్థిర శూన్య సూచిక_handle_button(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2, uint32_t serial,
                                  uint32_t సమయం, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    Uint8 sdl_button;

    ఎంపిక (button) {
    స్థితి BTN_ఎడమ:
        sdl_button = SDL_BUTTON_ఎడమ;
        ఆపు;
    స్థితి BTN_మధ్య:
        sdl_button = SDL_BUTTON_మధ్య;
        ఆపు;
    స్థితి BTN_కుడి:
        sdl_button = SDL_BUTTON_కుడి;
        ఆపు;
    అప్రమేయ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        ఆపు;
    }

    ఒకవేళ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->సూచిక_2.pending_చట్రం.timestamp_ns = Wayland_Get_సూచిక_Timestamp(seat, సమయం);

    ఒకవేళ (wl_seat_get_సంస్కరణ(seat->wl_seat) >= WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        ఒకవేళ (state_w) {
            seat->సూచిక_2.pending_చట్రం.buttons_pressed |= SDL_BUTTON_ముసుగు(sdl_button);
        } లేకపోతే {
            seat->సూచిక_2.pending_చట్రం.buttons_released |= SDL_BUTTON_ముసుగు(sdl_button);
        }
    } లేకపోతే {
        సూచిక_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

స్థిర శూన్య సూచిక_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t విలువ)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = seat->సూచిక_2.focus;
    స్థిరరాశి గణన wl_సూచిక_axis a = axis;

    ఒకవేళ (seat->సూచిక_2.focus) {
        దశాంశం x, y;

        ఎంపిక (a) {
        స్థితి WL_సూచిక_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
            ఆపు;
        స్థితి WL_సూచిక_AXIS_HORIZONTAL_SCROLL:
            x = (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
            y = 0;
            ఆపు;
        అప్రమేయ:
            తిరిగి;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, కిటికీ->sdlwindow, seat->సూచిక_2.sdl_id, x, y, SDL_MOUSEWHEEL_సాధారణ);
    }
}

స్థిర శూన్య సూచిక_handle_axis_common(SDL_WaylandSeat *seat, గణన SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t విలువ)
{
    స్థిరరాశి గణన wl_సూచిక_axis a = axis;

    ఒకవేళ (seat->సూచిక_2.focus) {
        seat->సూచిక_2.pending_చట్రం.have_axis = true;

        ఎంపిక (a) {
        స్థితి WL_సూచిక_AXIS_VERTICAL_SCROLL:
            ఎంపిక (type) {
            స్థితి SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->సూచిక_2.pending_చట్రం.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->సూచిక_2.pending_చట్రం.axis.y = 0.0f;
                }
                seat->సూచిక_2.pending_చట్రం.axis.y += 0 - (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                ఆపు;
            స్థితి SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->సూచిక_2.pending_చట్రం.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->సూచిక_2.pending_చట్రం.axis.y = 0 - (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                }
                ఆపు;
            స్థితి SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->సూచిక_2.pending_చట్రం.axis.y = 0 - (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                }
                ఆపు;
            }
            ఆపు;
        స్థితి WL_సూచిక_AXIS_HORIZONTAL_SCROLL:
            ఎంపిక (type) {
            స్థితి SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->సూచిక_2.pending_చట్రం.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->సూచిక_2.pending_చట్రం.axis.x = 0.0f;
                }
                seat->సూచిక_2.pending_చట్రం.axis.x += (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                ఆపు;
            స్థితి SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->సూచిక_2.pending_చట్రం.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->సూచిక_2.pending_చట్రం.axis.x = (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                }
                ఆపు;
            స్థితి SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ఒకవేళ (seat->సూచిక_2.pending_చట్రం.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->సూచిక_2.pending_చట్రం.axis.x = (దశాంశం)wl_fixed_గమ్యం_double(విలువ);
                }
                ఆపు;
            }
            ఆపు;
        }
    }
}

స్థిర శూన్య సూచిక_handle_axis(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                uint32_t సమయం, uint32_t axis, wl_fixed_t విలువ)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    స్థిరరాశి Uint64 nsTimestamp = Wayland_Get_సూచిక_Timestamp(seat, సమయం);

    ఒకవేళ (wl_seat_get_సంస్కరణ(seat->wl_seat) >= WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        seat->సూచిక_2.pending_చట్రం.timestamp_ns = nsTimestamp;
        సూచిక_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, విలువ);
    } లేకపోతే {
        సూచిక_handle_axis_common_v1(seat, nsTimestamp, axis, విలువ);
    }
}

స్థిర శూన్య సూచిక_handle_axis_relative_direction(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = దత్తాంశం;

    ఎంపిక (axis_relative_direction) {
    స్థితి WL_సూచిక_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->సూచిక_2.pending_చట్రం.axis.direction = SDL_MOUSEWHEEL_సాధారణ;
        ఆపు;
    స్థితి WL_సూచిక_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->సూచిక_2.pending_చట్రం.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        ఆపు;
    }
}

స్థిర శూన్య సూచిక_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = seat->సూచిక_2.focus;

    ఒకవేళ (కిటికీ) {
        SDL_Mouse *mouse = SDL_GetMouse();
        ద్విగుణ dx;
        ద్విగుణ dy;
        ఒకవేళ (mouse->ఆదానం_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.relative.dx_unaccel);
            dy = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.relative.dy_unaccel);
        } లేకపోతే {
            dx = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.relative.dx) * కిటికీ->సూచిక_scale.x;
            dy = wl_fixed_గమ్యం_double(seat->సూచిక_2.pending_చట్రం.relative.dy) * కిటికీ->సూచిక_scale.y;
        }

        SDL_SendMouseMotion(seat->సూచిక_2.pending_చట్రం.timestamp_ns, కిటికీ->sdlwindow, seat->సూచిక_2.sdl_id, true, (దశాంశం)dx, (దశాంశం)dy);
    }
}

స్థిర శూన్య సూచిక_dispatch_axis(SDL_WaylandSeat *seat)
{
    దశాంశం x, y;
    SDL_MouseWheelDirection direction = seat->సూచిక_2.pending_చట్రం.axis.direction;

    ఎంపిక (seat->సూచిక_2.pending_చట్రం.axis.x_axis_type) {
    స్థితి SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->సూచిక_2.pending_చట్రం.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        ఆపు;
    స్థితి SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->సూచిక_2.pending_చట్రం.axis.x;
        ఆపు;
    స్థితి SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->సూచిక_2.pending_చట్రం.axis.x / 120.0f;
        ఆపు;
    అప్రమేయ:
        x = 0.0f;
        ఆపు;
    }

    ఎంపిక (seat->సూచిక_2.pending_చట్రం.axis.y_axis_type) {
    స్థితి SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->సూచిక_2.pending_చట్రం.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        ఆపు;
    స్థితి SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->సూచిక_2.pending_చట్రం.axis.y;
        ఆపు;
    స్థితి SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->సూచిక_2.pending_చట్రం.axis.y / 120.0f;
        ఆపు;
    అప్రమేయ:
        y = 0.0f;
        ఆపు;
    }

    SDL_SendMouseWheel(seat->సూచిక_2.pending_చట్రం.timestamp_ns,
                       seat->సూచిక_2.focus->sdlwindow, seat->సూచిక_2.sdl_id, x, y, direction);
}

స్థిర శూన్య సూచిక_handle_చట్రం(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2)
{
    SDL_WaylandSeat *seat = దత్తాంశం;

    ఒకవేళ (seat->సూచిక_2.pending_చట్రం.enter_surface) {
        ఒకవేళ (seat->సూచిక_2.pending_చట్రం.leave_surface) {
            SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = seat->సూచిక_2.focus;
            SDL_కిటికీ_దత్తాంశం *new_focus = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(seat->సూచిక_2.pending_చట్రం.enter_surface);

            ఒకవేళ (కిటికీ_దత్తాంశం_2 && (కిటికీ_దత్తాంశం_2->sdlwindow->flags & SDL_కిటికీ_MOUSE_CAPTURE) && కిటికీ_దత్తాంశం_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->సూచిక_2.focus_surface = seat->సూచిక_2.pending_చట్రం.enter_surface;
                seat->సూచిక_2.pending_చట్రం.enter_surface = ఖాళీ;
                seat->సూచిక_2.pending_చట్రం.leave_surface = ఖాళీ;
            } లేకపోతే {
                // Leaving the previous surface before entering a new surface.
                సూచిక_dispatch_leave(seat, false);
                seat->సూచిక_2.pending_చట్రం.leave_surface = ఖాళీ;
            }
        }

        ఒకవేళ (seat->సూచిక_2.pending_చట్రం.enter_surface) {
            సూచిక_dispatch_enter(seat);
        }
    }

    ఒకవేళ (seat->సూచిక_2.pending_చట్రం.have_absolute) {
        సూచిక_dispatch_absolute_motion(seat, seat->సూచిక_2.pending_చట్రం.have_warp);
    }

    ఒకవేళ (seat->సూచిక_2.pending_చట్రం.have_relative) {
        సూచిక_dispatch_relative_motion(seat);
    }

    కొరకు (Uint8 i = 1; seat->సూచిక_2.pending_చట్రం.buttons_pressed || seat->సూచిక_2.pending_చట్రం.buttons_released; ++i) {
        స్థిరరాశి Uint32 ముసుగు = SDL_BUTTON_ముసుగు(i);
        ఒకవేళ (seat->సూచిక_2.pending_చట్రం.buttons_pressed & ముసుగు) {
            సూచిక_dispatch_button(seat, i, true);
            seat->సూచిక_2.pending_చట్రం.buttons_pressed &= ~ముసుగు;
        }
        ఒకవేళ (seat->సూచిక_2.pending_చట్రం.buttons_released & ముసుగు) {
            సూచిక_dispatch_button(seat, i, false);
            seat->సూచిక_2.pending_చట్రం.buttons_released &= ~ముసుగు;
        }
    }

    ఒకవేళ (seat->సూచిక_2.pending_చట్రం.have_axis) {
        సూచిక_dispatch_axis(seat);
    }

    ఒకవేళ (seat->సూచిక_2.pending_చట్రం.leave_surface) {
        సూచిక_dispatch_leave(seat, true);
    }

    SDL_zero(seat->సూచిక_2.pending_చట్రం);
}

స్థిర శూన్య సూచిక_handle_axis_ఆధారం(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                       uint32_t axis_ఆధారం)
{
    // unimplemented
}

స్థిర శూన్య సూచిక_handle_axis_stop(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                     uint32_t సమయం, uint32_t axis)
{
    // unimplemented
}

స్థిర శూన్య సూచిక_handle_axis_discrete(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    సూచిక_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

స్థిర శూన్య సూచిక_handle_axis_value120(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *సూచిక_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    సూచిక_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

స్థిర శూన్య సూచిక_handle_warp(శూన్య *దత్తాంశం, నిర్మాణం wl_సూచిక *wl_సూచిక, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;

    seat->సూచిక_2.pending_చట్రం.have_absolute = true;
    seat->సూచిక_2.pending_చట్రం.have_warp = true;
    seat->సూచిక_2.pending_చట్రం.absolute.sx = surface_x;
    seat->సూచిక_2.pending_చట్రం.absolute.sy = surface_y;
}

స్థిర స్థిరరాశి నిర్మాణం wl_సూచిక_listener సూచిక_listener = {
    సూచిక_handle_enter,
    సూచిక_handle_leave,
    సూచిక_handle_motion,
    సూచిక_handle_button,
    సూచిక_handle_axis,
    సూచిక_handle_చట్రం,                   // Version 5
    సూచిక_handle_axis_ఆధారం,             // Version 5
    సూచిక_handle_axis_stop,               // Version 5
    సూచిక_handle_axis_discrete,           // Version 5
    సూచిక_handle_axis_value120,           // Version 8
    సూచిక_handle_axis_relative_direction, // Version 9
    సూచిక_handle_warp                     // Version 11
};

స్థిర శూన్య relative_సూచిక_handle_relative_motion(శూన్య *దత్తాంశం,
                                                    నిర్మాణం zwp_relative_సూచిక_v1 *సూచిక_2,
                                                    uint32_t సమయం_hi,
                                                    uint32_t సమయం_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = దత్తాంశం;

    // Relative pointer event times are in microsecond granularity.
    seat->సూచిక_2.pending_చట్రం.relative.dx = dx;
    seat->సూచిక_2.pending_చట్రం.relative.dy = dy;
    seat->సూచిక_2.pending_చట్రం.relative.dx_unaccel = dx_unaccel;
    seat->సూచిక_2.pending_చట్రం.relative.dy_unaccel = dy_unaccel;
    seat->సూచిక_2.pending_చట్రం.timestamp_ns = Wayland_Adjust_Event_Timestamp_పునాది(SDL_US_గమ్యం_NS(((Uint64)సమయం_hi << 32) | (Uint64)సమయం_lo));

    ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) >= WL_సూచిక_చట్రం_SINCE_సంస్కరణ) {
        seat->సూచిక_2.pending_చట్రం.have_relative = true;
    } లేకపోతే {
        సూచిక_dispatch_relative_motion(seat);
    }
}

స్థిర స్థిరరాశి నిర్మాణం zwp_relative_సూచిక_v1_listener relative_సూచిక_listener = {
    relative_సూచిక_handle_relative_motion,
};

స్థిర శూన్య locked_సూచిక_locked(శూన్య *దత్తాంశం, నిర్మాణం zwp_locked_సూచిక_v1 *locked_సూచిక)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.is_confined = true;
}

స్థిర శూన్య locked_సూచిక_unlocked(శూన్య *దత్తాంశం, నిర్మాణం zwp_locked_సూచిక_v1 *locked_సూచిక)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.is_confined = false;
}

స్థిర స్థిరరాశి నిర్మాణం zwp_locked_సూచిక_v1_listener locked_సూచిక_listener = {
    locked_సూచిక_locked,
    locked_సూచిక_unlocked,
};

స్థిర శూన్య confined_సూచిక_confined(శూన్య *దత్తాంశం, నిర్మాణం zwp_confined_సూచిక_v1 *confined_సూచిక)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.is_confined = true;
}

స్థిర శూన్య confined_సూచిక_unconfined(శూన్య *దత్తాంశం, నిర్మాణం zwp_confined_సూచిక_v1 *confined_సూచిక)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->సూచిక_2.is_confined = false;
}

స్థిర స్థిరరాశి నిర్మాణం zwp_confined_సూచిక_v1_listener confined_సూచిక_listener = {
    confined_సూచిక_confined,
    confined_సూచిక_unconfined,
};

స్థిర శూన్య touch_handler_కిందికి(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, నిర్మాణం wl_surface *surface,
                               పూర్ణాంకం id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2;

    // Check that this surface is valid.
    ఒకవేళ (!surface) {
        తిరిగి;
    }

    Wayland_Seat_కూడు_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    కిటికీ_దత్తాంశం_2 = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);

    ఒకవేళ (కిటికీ_దత్తాంశం_2 && కిటికీ_దత్తాంశం_2->surface == surface) {
        దశాంశం x, y;

        ఒకవేళ (కిటికీ_దత్తాంశం_2->current.logical_వెడల్పు <= 1) {
            x = 0.5f;
        } లేకపోతే {
            x = (దశాంశం)wl_fixed_గమ్యం_double(fx) / (కిటికీ_దత్తాంశం_2->current.logical_వెడల్పు - 1);
        }
        ఒకవేళ (కిటికీ_దత్తాంశం_2->current.logical_ఎత్తు <= 1) {
            y = 0.5f;
        } లేకపోతే {
            y = (దశాంశం)wl_fixed_గమ్యం_double(fy) / (కిటికీ_దత్తాంశం_2->current.logical_ఎత్తు - 1);
        }

        ++కిటికీ_దత్తాంశం_2->చురుకైన_touch_లెక్క;
        SDL_సమితి_Mouse_Focus(కిటికీ_దత్తాంశం_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), కిటికీ_దత్తాంశం_2->sdlwindow, SDL_EVENT_FINGER_కిందికి, x, y, 1.0f);
    }
}

స్థిర శూన్య touch_handler_పైకి(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *touch, uint32_t serial, uint32_t timestamp, పూర్ణాంకం id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    wl_fixed_t fx = 0, fy = 0;
    నిర్మాణం wl_surface *surface = ఖాళీ;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ఒకవేళ (surface) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);

        ఒకవేళ (కిటికీ_దత్తాంశం_2 && కిటికీ_దత్తాంశం_2->surface == surface) {
            స్థిరరాశి దశాంశం x = (దశాంశం)wl_fixed_గమ్యం_double(fx) / కిటికీ_దత్తాంశం_2->current.logical_వెడల్పు;
            స్థిరరాశి దశాంశం y = (దశాంశం)wl_fixed_గమ్యం_double(fy) / కిటికీ_దత్తాంశం_2->current.logical_ఎత్తు;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), కిటికీ_దత్తాంశం_2->sdlwindow, SDL_EVENT_FINGER_పైకి, x, y, 0.0f);

            --కిటికీ_దత్తాంశం_2->చురుకైన_touch_లెక్క;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ఒకవేళ (SDL_GetMouseFocus() == కిటికీ_దత్తాంశం_2->sdlwindow && !కిటికీ_దత్తాంశం_2->keyboard_focus_లెక్క &&
                !కిటికీ_దత్తాంశం_2->సూచిక_focus_లెక్క && !కిటికీ_దత్తాంశం_2->చురుకైన_touch_లెక్క) {
                SDL_సమితి_Mouse_Focus(ఖాళీ);
            }
        }
    }
}

స్థిర శూన్య touch_handler_motion(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *touch, uint32_t timestamp, పూర్ణాంకం id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    నిర్మాణం wl_surface *surface = ఖాళీ;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ఒకవేళ (surface) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);

        ఒకవేళ (కిటికీ_దత్తాంశం_2 && కిటికీ_దత్తాంశం_2->surface == surface) {
            స్థిరరాశి దశాంశం x = (దశాంశం)wl_fixed_గమ్యం_double(fx) / కిటికీ_దత్తాంశం_2->current.logical_వెడల్పు;
            స్థిరరాశి దశాంశం y = (దశాంశం)wl_fixed_గమ్యం_double(fy) / కిటికీ_దత్తాంశం_2->current.logical_ఎత్తు;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), కిటికీ_దత్తాంశం_2->sdlwindow, x, y, 1.0f);
        }
    }
}

స్థిర శూన్య touch_handler_చట్రం(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *touch)
{
}

స్థిర శూన్య touch_handler_cancel(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    SDL_Wayland_Touch_బిందువు *tp, *తాత్కాలిక;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_సురక్షిత (tp, తాత్కాలిక, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

స్థిర శూన్య touch_handler_shape(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

స్థిర శూన్య touch_handler_orientation(శూన్య *దత్తాంశం, నిర్మాణం wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

స్థిర స్థిరరాశి నిర్మాణం wl_touch_listener touch_listener = {
    touch_handler_కిందికి,
    touch_handler_పైకి,
    touch_handler_motion,
    touch_handler_చట్రం,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ఒకవేళ !SDL_XKBCOMMON_CHECK_సంస్కరణ(1, 0, 0)
స్థిర size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t కీలకం, xkb_layout_సూచీ_t layout, xkb_level_సూచీ_t level, xkb_mod_ముసుగు_t *masks_బహిర్గతం, size_t masks_కొలత)
{
    ఒకవేళ (!masks_బహిర్గతం || !masks_కొలత) {
        తిరిగి 0;
    }

    // Level 0 is always unmodified, so early out.
    ఒకవేళ (level == 0) {
        *masks_బహిర్గతం = 0;
        తిరిగి 1;
    }

    size_t ముసుగు_idx = 0;
    స్థిరరాశి xkb_mod_ముసుగు_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.జరుపు_ముసుగు,
        seat->keyboard.xkb.caps_ముసుగు_2,
        seat->keyboard.xkb.జరుపు_ముసుగు | seat->keyboard.xkb.caps_ముసుగు_2,
        seat->keyboard.xkb.level3_ముసుగు,
        seat->keyboard.xkb.level3_ముసుగు | seat->keyboard.xkb.జరుపు_ముసుగు,
        seat->keyboard.xkb.level3_ముసుగు | seat->keyboard.xkb.caps_ముసుగు_2,
        seat->keyboard.xkb.level3_ముసుగు | seat->keyboard.xkb.జరుపు_ముసుగు | seat->keyboard.xkb.caps_ముసుగు_2,
        seat->keyboard.xkb.level5_ముసుగు,
        seat->keyboard.xkb.level5_ముసుగు | seat->keyboard.xkb.జరుపు_ముసుగు,
        seat->keyboard.xkb.level5_ముసుగు | seat->keyboard.xkb.caps_ముసుగు_2,
        seat->keyboard.xkb.level5_ముసుగు | seat->keyboard.xkb.జరుపు_ముసుగు | seat->keyboard.xkb.caps_ముసుగు_2
    };
    స్థిరరాశి xkb_mod_ముసుగు_t pressed_mod_ముసుగు = seat->keyboard.xkb.జరుపు_ముసుగు | seat->keyboard.xkb.level3_ముసుగు | seat->keyboard.xkb.level5_ముసుగు;
    స్థిరరాశి xkb_mod_ముసుగు_t locked_mod_ముసుగు = seat->keyboard.xkb.caps_ముసుగు_2;

    కొరకు (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_ముసుగు(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_ముసుగు, 0, keymod_masks[i] & locked_mod_ముసుగు, 0, 0, layout);
        ఒకవేళ (WAYLAND_xkb_state_కీలకం_get_level(seat->keyboard.xkb.state, కీలకం, layout) == level) {
            masks_బహిర్గతం[ముసుగు_idx] = keymod_masks[i];

            ఒకవేళ (++ముసుగు_idx == masks_కొలత) {
                ఆపు;
            }
        }
    }

    తిరిగి ముసుగు_idx;
}
#అయితే_ముగింపు

స్థిర శూన్య Wayland_KeymapIterator(నిర్మాణం xkb_keymap *keymap, xkb_keycode_t కీలకం, శూన్య *దత్తాంశం)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    స్థిరరాశి xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    స్థిరరాశి xkb_mod_ముసుగు_t xkb_valid_mod_ముసుగు = seat->keyboard.xkb.జరుపు_ముసుగు |
                                              seat->keyboard.xkb.alt_ముసుగు |
                                              seat->keyboard.xkb.level3_ముసుగు |
                                              seat->keyboard.xkb.level5_ముసుగు |
                                              seat->keyboard.xkb.caps_ముసుగు_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ఒకవేళ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_పట్టిక(SDL_SCANCODE_పట్టిక_LINUX, కీలకం - 8);
    }

    కొరకు (xkb_layout_సూచీ_t layout = 0; layout < seat->keyboard.xkb.అంకె_layouts; ++layout) {
        స్థిరరాశి xkb_level_సూచీ_t అంకె_స్థాయిలు = WAYLAND_xkb_keymap_అంకె_స్థాయిలు_for_కీలకం(seat->keyboard.xkb.keymap, కీలకం, layout);
        కొరకు (xkb_level_సూచీ_t level = 0; level < అంకె_స్థాయిలు; ++level) {
            ఒకవేళ (WAYLAND_xkb_keymap_కీలకం_get_syms_by_level(seat->keyboard.xkb.keymap, కీలకం, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_కీలకం_Sym(syms[0], కీలకం);
                    ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
                        కొనసాగు;
                    }
                }

                xkb_mod_ముసుగు_t xkb_mod_masks[16];
#ఒకవేళ SDL_XKBCOMMON_CHECK_సంస్కరణ(1, 0, 0)
                స్థిరరాశి size_t అంకె_masks = WAYLAND_xkb_keymap_కీలకం_get_mods_for_level(seat->keyboard.xkb.keymap, కీలకం, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#లేకపోతే
                స్థిరరాశి size_t అంకె_masks = xkb_legacy_get_mods_for_level(seat, కీలకం, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#అయితే_ముగింపు
                కొరకు (size_t ముసుగు = 0; ముసుగు < అంకె_masks; ++ముసుగు) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ఒకవేళ ((xkb_mod_masks[ముసుగు] | xkb_valid_mod_ముసుగు) != xkb_valid_mod_ముసుగు) {
                        కొనసాగు;
                    }

                    స్థిరరాశి SDL_Keymod sdl_mod = (xkb_mod_masks[ముసుగు] & seat->keyboard.xkb.జరుపు_ముసుగు ? SDL_KMOD_జరుపు : 0) |
                                               (xkb_mod_masks[ముసుగు] & seat->keyboard.xkb.alt_ముసుగు ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[ముసుగు] & seat->keyboard.xkb.level3_ముసుగు ? SDL_KMOD_బహుళకం : 0) |
                                               (xkb_mod_masks[ముసుగు] & seat->keyboard.xkb.level5_ముసుగు ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[ముసుగు] & seat->keyboard.xkb.caps_ముసుగు_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_కీలకం_సంకేతం_From_కీలకం_Sym(syms[0], కీలకం, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ఒకవేళ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_తదుపరి_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        ఒకవేళ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_సమితి_Keymap_నమోదు(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_కీలకం *res = WAYLAND_wl_array_కూడు(&seat->keyboard.reserved_scancodes, పరిమాణం(Wayland_Reserved_కీలకం));
                        ఒకవేళ (res) {
                            res->scancode = scancode;
                            res->కీలకం = కీలకం - 8;
                        }
                    }

                    ఒకవేళ (!keycode) {
                        ఎంపిక (scancode) {
                        స్థితి SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            ఆపు;
                        స్థితి SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            ఆపు;
                        స్థితి SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            ఆపు;
                        స్థితి SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            ఆపు;
                        అప్రమేయ:
                            keycode = SDL_SCANCODE_గమ్యం_KEYCODE(scancode);
                            ఆపు;
                        }
                    }

                    SDL_సమితి_Keymap_నమోదు(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

స్థిర శూన్య keyboard_handle_keymap(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *keyboard,
                                   uint32_t format, పూర్ణాంకం fd, uint32_t కొలత)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    అక్షరం *map_str;

    ఒకవేళ (!దత్తాంశం) {
        close(fd);
        తిరిగి;
    }

    ఒకవేళ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        తిరిగి;
    }

    map_str = mmap(ఖాళీ, కొలత, PROT_READ, MAP_PRIVATE, fd, 0);
    ఒకవేళ (map_str == MAP_FAILED) {
        close(fd);
        తిరిగి;
    }

    ఒకవేళ (seat->keyboard.xkb.keymap != ఖాళీ) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ఖాళీ;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_పాఠ్యం_V1,
                                                                   0);
    munmap(map_str, కొలత);
    close(fd);

    ఒకవేళ (!seat->keyboard.xkb.keymap) {
        SDL_సమితి_Error("failed to compile keymap");
        తిరిగి;
    }

    // Clear the old layouts.
    కొరకు (xkb_layout_సూచీ_t i = 0; i < seat->keyboard.xkb.అంకె_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = ఖాళీ;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.అంకె_layouts = 0;

#ఒకవేళ SDL_XKBCOMMON_CHECK_సంస్కరణ(1, 10, 0)
    seat->keyboard.xkb.జరుపు_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_MOD_NAME_జరుపు);
    seat->keyboard.xkb.ctrl_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.అంకె_ముసుగు = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_అంకె);
    seat->keyboard.xkb.caps_ముసుగు_2 = WAYLAND_xkb_keymap_mod_get_ముసుగు(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#లేకపోతే
#నిర్వచించు GET_MOD_సూచీ(mod) \
    WAYLAND_xkb_keymap_mod_get_సూచీ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.జరుపు_ముసుగు = 1 << GET_MOD_సూచీ(జరుపు_2);
    seat->keyboard.xkb.ctrl_ముసుగు = 1 << GET_MOD_సూచీ(CTRL);
    seat->keyboard.xkb.alt_ముసుగు = 1 << GET_MOD_సూచీ(ALT);
    seat->keyboard.xkb.gui_ముసుగు = 1 << GET_MOD_సూచీ(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_ముసుగు = 1 << GET_MOD_సూచీ(MOD5);
    seat->keyboard.xkb.level5_ముసుగు = 1 << GET_MOD_సూచీ(MOD3);
    seat->keyboard.xkb.అంకె_ముసుగు = 1 << GET_MOD_సూచీ(అంకె_2);
    seat->keyboard.xkb.caps_ముసుగు_2 = 1 << GET_MOD_సూచీ(CAPS);
#నిర్వచనం_రద్దు GET_MOD_సూచీ
#అయితే_ముగింపు

    ఒకవేళ (seat->keyboard.xkb.state != ఖాళీ) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = ఖాళీ;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ఒకవేళ (!seat->keyboard.xkb.state) {
        SDL_సమితి_Error("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = ఖాళీ;
        తిరిగి;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == ఖాళీ;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.అంకె_layouts = WAYLAND_xkb_keymap_అంకె_layouts(seat->keyboard.xkb.keymap);
    ఒకవేళ (seat->keyboard.xkb.అంకె_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.అంకె_layouts, పరిమాణం(SDL_Keymap *));
        ఒకవేళ (!seat->keyboard.sdl_keymap) {
            తిరిగి;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        కొరకు (xkb_layout_సూచీ_t i = 0; i < seat->keyboard.xkb.అంకె_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ఒకవేళ (!seat->keyboard.sdl_keymap[i]) {
                కొరకు (xkb_layout_సూచీ_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = ఖాళీ;
                తిరిగి;
            }
        }

        WAYLAND_xkb_keymap_కీలకం_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_ముసుగు(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.అంకె_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_సమితి_Keymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    స్థిరరాశి అక్షరం *locale = SDL_getenv("LC_ALL");
    ఒకవేళ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ఒకవేళ (!locale) {
            locale = SDL_getenv("LANG");
            ఒకవేళ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ఒకవేళ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ఒకవేళ (seat->keyboard.xkb.compose_పట్టిక != ఖాళీ) {
            WAYLAND_xkb_compose_పట్టిక_unref(seat->keyboard.xkb.compose_పట్టిక);
            seat->keyboard.xkb.compose_పట్టిక = ఖాళీ;
        }
        seat->keyboard.xkb.compose_పట్టిక = WAYLAND_xkb_compose_పట్టిక_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ఒకవేళ (seat->keyboard.xkb.compose_పట్టిక) {
            // Set up XKB compose state
            ఒకవేళ (seat->keyboard.xkb.compose_state != ఖాళీ) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = ఖాళీ;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_పట్టిక,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ఒకవేళ (!seat->keyboard.xkb.compose_state) {
                SDL_సమితి_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_పట్టిక_unref(seat->keyboard.xkb.compose_పట్టిక);
                seat->keyboard.xkb.compose_పట్టిక = ఖాళీ;
            }
        }
    } లేకపోతే ఒకవేళ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
స్థిర SDL_Scancode Wayland_Get_Scancode_For_కీలకం(SDL_WaylandSeat *seat, Uint32 కీలకం, స్థిరరాశి xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ఒకవేళ (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_పట్టిక(SDL_SCANCODE_పట్టిక_LINUX, కీలకం);

        // No table entry? Check the reserved list.
        ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_కీలకం *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ఒకవేళ (i->కీలకం == కీలకం) {
                    తిరిగి i->scancode;
                }
            }
        }
    } లేకపోతే {
        స్థిరరాశి xkb_keysym_t *keysym;
        ఒకవేళ (WAYLAND_xkb_state_కీలకం_get_syms(seat->keyboard.xkb.state, కీలకం + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_కీలకం_Sym(keysym[0], కీలకం + 8);
            ఒకవేళ (syms) {
                *syms = keysym;
            }
        }
    }

    తిరిగి scancode;
}

స్థిర శూన్య Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool కీలకం_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ఒకవేళ (!కీలకం_pressed) {
        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.జరుపు_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_జరుపు)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_జరుపు;
            }
        } లేకపోతే {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_జరుపు;
        }

        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } లేకపోతే {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } లేకపోతే {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } లేకపోతే {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_బహుళకం)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_బహుళకం;
            }
        } లేకపోతే {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_బహుళకం;
        }

        ఒకవేళ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_ముసుగు) {
            ఒకవేళ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } లేకపోతే {
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
    స్థిరరాశి xkb_mod_ముసుగు_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.జరుపు_ముసుగు) {
        ఒకవేళ (seat->keyboard.pressed_modifiers & SDL_KMOD_జరుపు) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_జరుపు;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_జరుపు);
        } లేకపోతే ఒకవేళ (!(seat->keyboard.locked_modifiers & SDL_KMOD_జరుపు)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_జరుపు;
        }
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_జరుపు;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_ముసుగు) {
        ఒకవేళ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } లేకపోతే ఒకవేళ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.alt_ముసుగు) {
        ఒకవేళ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } లేకపోతే ఒకవేళ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.gui_ముసుగు) {
        ఒకవేళ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } లేకపోతే ఒకవేళ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.level3_ముసుగు) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_బహుళకం;
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_బహుళకం;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.level5_ముసుగు) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.caps_ముసుగు_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ఒకవేళ (xkb_locked_modifiers & seat->keyboard.xkb.అంకె_ముసుగు) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_అంకె;
    } లేకపోతే {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_అంకె;
    }

    SDL_సమితి_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

స్థిర శూన్య Wayland_Handle_Modifier_కీలకాలు(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    స్థిరరాశి SDL_Keycode keycode = SDL_Get_కీలకం_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    ఎంపిక (keycode) {
    స్థితి SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        ఆపు;
    స్థితి SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        ఆపు;
    స్థితి SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        ఆపు;
    స్థితి SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        ఆపు;
    స్థితి SDLK_LALT:
        mod = SDL_KMOD_LALT;
        ఆపు;
    స్థితి SDLK_RALT:
        mod = SDL_KMOD_RALT;
        ఆపు;
    స్థితి SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        ఆపు;
    స్థితి SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        ఆపు;
    స్థితి SDLK_బహుళకం:
        mod = SDL_KMOD_బహుళకం;
        ఆపు;
    స్థితి SDLK_LEVEL5_జరుపు:
        mod = SDL_KMOD_LEVEL5;
        ఆపు;
    అప్రమేయ:
        తిరిగి;
    }

    ఒకవేళ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } లేకపోతే {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

స్థిర శూన్య keyboard_handle_enter(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *keyboard,
                                  uint32_t serial, నిర్మాణం wl_surface *surface,
                                  నిర్మాణం wl_array *కీలకాలు)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    uint32_t *కీలకం;

    ఒకవేళ (!surface) {
        // Enter event for a destroyed surface.
        తిరిగి;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_కిటికీ_దత్తాంశం *కిటికీ = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);
    ఒకవేళ (!కిటికీ) {
        // Not a surface owned by SDL.
        తిరిగి;
    }

    ++కిటికీ->keyboard_focus_లెక్క;
    seat->keyboard.focus = కిటికీ;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_సమితి_Keyboard_Focus(కిటికీ->sdlwindow->keyboard_focus ? కిటికీ->sdlwindow->keyboard_focus : కిటికీ->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_సూచిక_Grabs(seat->display, కిటికీ);

    // Update text input and IME focus.
    Wayland_Seat_Update_పాఠ్యం_ఆదానం(seat);

#నిర్వచితమైతే SDL_USE_IME
    ఒకవేళ (!seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం) {
        SDL_IME_సమితి_Focus(true);
    }
#అయితే_ముగింపు

    Uint64 timestamp = SDL_GetTicksNS();
    కిటికీ->చివరి_focus_event_సమయం_ns = timestamp;

    Wayland_Seat_సమితి_Keymap(seat);

    wl_array_for_each (కీలకం, కీలకాలు) {
        స్థిరరాశి SDL_Scancode scancode = Wayland_Get_Scancode_For_కీలకం(seat, *కీలకం, ఖాళీ);
        ఒకవేళ (scancode != SDL_SCANCODE_UNKNOWN) {
            స్థిరరాశి SDL_Keycode keycode = SDL_Get_కీలకం_From_Scancode(scancode, SDL_KMOD_NONE, false);

            ఎంపిక (keycode) {
            స్థితి SDLK_LSHIFT:
            స్థితి SDLK_RSHIFT:
            స్థితి SDLK_LCTRL:
            స్థితి SDLK_RCTRL:
            స్థితి SDLK_LALT:
            స్థితి SDLK_RALT:
            స్థితి SDLK_LGUI:
            స్థితి SDLK_RGUI:
            స్థితి SDLK_బహుళకం:
            స్థితి SDLK_LEVEL5_జరుపు:
                Wayland_Handle_Modifier_కీలకాలు(seat, scancode, true);
                SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *కీలకం, scancode, true);
                ఆపు;
            అప్రమేయ:
                ఆపు;
            }
        }
    }
}

స్థిర శూన్య keyboard_handle_leave(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *keyboard,
                                  uint32_t serial, నిర్మాణం wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;

    ఒకవేళ (!surface) {
        // Leave event for a destroyed surface.
        తిరిగి;
    }

    SDL_కిటికీ_దత్తాంశం *కిటికీ = Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface);
    ఒకవేళ (!కిటికీ) {
        // Not a surface owned by SDL.
        తిరిగి;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.కీలకం = 0;

    SDL_కిటికీ *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    అయితే (keyboard_focus && SDL_కిటికీ_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->మాతృ;
    }

    స్థిరరాశి bool had_focus = keyboard_focus && కిటికీ->sdlwindow == keyboard_focus;
    seat->keyboard.focus = ఖాళీ;
    --కిటికీ->keyboard_focus_లెక్క;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ఒకవేళ (!కిటికీ->keyboard_focus_లెక్క && had_focus) {
        SDL_సమితి_Keyboard_Focus(ఖాళీ);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_సూచిక_Grabs(seat->display, కిటికీ);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_పాఠ్యం_ఆదానం(seat);

#నిర్వచితమైతే SDL_USE_IME
    ఒకవేళ (!seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం && !కిటికీ->keyboard_focus_లెక్క) {
        SDL_IME_సమితి_Focus(false);
    }
#అయితే_ముగింపు

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ఒకవేళ (SDL_GetMouseFocus() == కిటికీ->sdlwindow && !కిటికీ->సూచిక_focus_లెక్క && !కిటికీ->చురుకైన_touch_లెక్క) {
        SDL_సమితి_Mouse_Focus(ఖాళీ);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_దత్తాంశం_Device_సమితి_Selection_Offer(seat->దత్తాంశం_device, ఖాళీ);
}

స్థిర bool keyboard_ఆదానం_get_పాఠ్యం(అక్షరం పాఠ్యం[8], స్థిరరాశి SDL_WaylandSeat *seat, uint32_t కీలకం, bool కిందికి, bool *handled_by_ime)
{
    స్థిరరాశి xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ఒకవేళ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        తిరిగి false;
    }

    // TODO: Can this happen?
    ఒకవేళ (WAYLAND_xkb_state_కీలకం_get_syms(seat->keyboard.xkb.state, కీలకం + 8, &syms) != 1) {
        తిరిగి false;
    }
    sym = syms[0];

#నిర్వచితమైతే SDL_USE_IME
    ఒకవేళ (SDL_IME_Process_కీలకం_Event(sym, కీలకం + 8, కిందికి)) {
        ఒకవేళ (handled_by_ime) {
            *handled_by_ime = true;
        }
        తిరిగి true;
    }
#అయితే_ముగింపు

    ఒకవేళ (!కిందికి) {
        తిరిగి false;
    }

    ఒకవేళ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        ఎంపిక (WAYLAND_xkb_compose_state_get_స్థితి(seat->keyboard.xkb.compose_state)) {
        స్థితి XKB_COMPOSE_COMPOSING:
            ఒకవేళ (handled_by_ime) {
                *handled_by_ime = true;
            }
            తిరిగి true;
        స్థితి XKB_COMPOSE_CANCELLED:
        అప్రమేయ:
            sym = XKB_కీలకం_No_చిహ్నం;
            ఆపు;
        స్థితి XKB_COMPOSE_NOTHING:
            ఆపు;
        స్థితి XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            ఆపు;
        }
    }

    తిరిగి WAYLAND_xkb_keysym_గమ్యం_utf8(sym, పాఠ్యం, 8) > 0;
}

స్థిర శూన్య keyboard_handle_కీలకం(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *keyboard,
                                uint32_t serial, uint32_t సమయం, uint32_t కీలకం,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    గణన wl_keyboard_కీలకం_state state = state_w;
    అక్షరం పాఠ్యం[8];
    bool has_పాఠ్యం = false;
    bool handled_by_ime = false;
    స్థిరరాశి Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, సమయం);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ఒకవేళ (state == WL_KEYBOARD_కీలకం_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ఒకవేళ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_కీలకం_repeats(seat->keyboard.xkb.keymap, కీలకం + 8)) {
            తిరిగి;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_కీలకం_STATE_PRESSED;
    }

    Wayland_Seat_సమితి_Keymap(seat);

    ఒకవేళ (state == WL_KEYBOARD_కీలకం_STATE_PRESSED) {
        SDL_కిటికీ *keyboard_focus = SDL_GetKeyboardFocus();
        ఒకవేళ (keyboard_focus && SDL_పాఠ్యం_ఆదానం_చురుకైన(keyboard_focus)) {
            has_పాఠ్యం = keyboard_ఆదానం_get_పాఠ్యం(పాఠ్యం, seat, కీలకం, true, &handled_by_ime);
        }
    } లేకపోతే {
        ఒకవేళ (కీలకం == seat->keyboard.repeat.కీలకం) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            స్థిరరాశి Uint64 elapsed = SDL_MS_గమ్యం_NS(సమయం - seat->keyboard.repeat.wl_press_సమయం_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.కీలకం = 0;
        }
        keyboard_ఆదానం_get_పాఠ్యం(పాఠ్యం, seat, కీలకం, false, &handled_by_ime);
    }

    స్థిరరాశి xkb_keysym_t *syms = ఖాళీ;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_కీలకం(seat, కీలకం, &syms);
    Wayland_Handle_Modifier_కీలకాలు(seat, scancode, state == WL_KEYBOARD_కీలకం_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        స్థిరరాశి SDL_Keycode keycode = (SDL_Keycode)SDL_కీలకం_Sym_గమ్యం_Ucs4(syms[0]);
        ఒకవేళ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_ముసుగు) {
                scancode = SDL_Get_Keymap_తదుపరి_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_సమితి_Keymap_నమోదు(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_కీలకం_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, కీలకం, scancode, state == WL_KEYBOARD_కీలకం_STATE_PRESSED);

    ఒకవేళ (state == WL_KEYBOARD_కీలకం_STATE_PRESSED) {
        ఒకవేళ (handled_by_ime) {
            has_పాఠ్యం = false;
        }
        ఒకవేళ (has_పాఠ్యం && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_పాఠ్యం(పాఠ్యం);
        }
        ఒకవేళ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_కీలకం_repeats(seat->keyboard.xkb.keymap, కీలకం + 8)) {
            keyboard_repeat_సమితి(&seat->keyboard.repeat, seat->keyboard.sdl_id, కీలకం, సమయం, timestamp_ns, scancode, has_పాఠ్యం ? పాఠ్యం : ఖాళీ);
        }
    }
}

స్థిర శూన్య keyboard_handle_modifiers(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t సమూహం)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    స్థిరరాశి uint32_t మునుపటి_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = సమూహం;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ఒకవేళ (!seat->keyboard.xkb.state) {
        తిరిగి;
    }

    WAYLAND_xkb_state_update_ముసుగు(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, సమూహం);

    // If a key is repeating, update the text to apply the modifier.
    ఒకవేళ (seat->keyboard.repeat.కీలకం) {
        అక్షరం పాఠ్యం[8];

        ఒకవేళ (keyboard_ఆదానం_get_పాఠ్యం(పాఠ్యం, seat, seat->keyboard.repeat.కీలకం, true, ఖాళీ)) {
            SDL_strlcpy(seat->keyboard.repeat.పాఠ్యం, పాఠ్యం, SDL_arraysize(seat->keyboard.repeat.పాఠ్యం));
        }
    }

    ఒకవేళ (సమూహం != మునుపటి_layout) {
        Wayland_Seat_సమితి_Keymap(seat);

        ఒకవేళ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

స్థిర శూన్య keyboard_handle_repeat_info(శూన్య *దత్తాంశం, నిర్మాణం wl_keyboard *wl_keyboard,
                                        int32_t రేటు, int32_t delay)
{
    SDL_WaylandSeat *seat = దత్తాంశం;
    seat->keyboard.repeat.repeat_రేటు = రేటు;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ఒకవేళ (!రేటు) {
        seat->keyboard.repeat.కీలకం = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_కీలకం,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

స్థిర శూన్య Wayland_Seat_Destroy_సూచిక(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->సూచిక_2.cursor_state);

    // End any active gestures.
    ఒకవేళ (seat->సూచిక_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_చివర, 0, seat->సూచిక_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ఒకవేళ (seat->సూచిక_2.focus) {
        seat->సూచిక_2.pending_చట్రం.leave_surface = seat->సూచిక_2.focus->surface;
        సూచిక_dispatch_leave(seat, false);
        seat->సూచిక_2.pending_చట్రం.leave_surface = ఖాళీ;
    }

    SDL_RemoveMouse(seat->సూచిక_2.sdl_id);

    ఒకవేళ (seat->సూచిక_2.confined_సూచిక) {
        zwp_confined_సూచిక_v1_destroy(seat->సూచిక_2.confined_సూచిక);
    }

    ఒకవేళ (seat->సూచిక_2.locked_సూచిక) {
        zwp_locked_సూచిక_v1_destroy(seat->సూచిక_2.locked_సూచిక);
    }

    ఒకవేళ (seat->సూచిక_2.relative_సూచిక) {
        zwp_relative_సూచిక_v1_destroy(seat->సూచిక_2.relative_సూచిక);
    }

    ఒకవేళ (seat->సూచిక_2.timestamps) {
        zwp_ఆదానం_timestamps_v1_destroy(seat->సూచిక_2.timestamps);
    }

    ఒకవేళ (seat->సూచిక_2.gesture_pinch) {
        zwp_సూచిక_gesture_pinch_v1_destroy(seat->సూచిక_2.gesture_pinch);
    }

    ఒకవేళ (seat->సూచిక_2.wl_సూచిక) {
        ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) >= WL_సూచిక_RELEASE_SINCE_సంస్కరణ) {
            wl_సూచిక_release(seat->సూచిక_2.wl_సూచిక);
        } లేకపోతే {
            wl_సూచిక_destroy(seat->సూచిక_2.wl_సూచిక);
        }
    }

    SDL_zero(seat->సూచిక_2);
}

స్థిర శూన్య Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ఒకవేళ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ఒకవేళ (seat->keyboard.sdl_keymap) {
        ఒకవేళ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.అంకె_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_సమితి_Mod_State(SDL_KMOD_NONE);
        }
        కొరకు (xkb_layout_సూచీ_t i = 0; i < seat->keyboard.xkb.అంకె_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = ఖాళీ;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ఒకవేళ (seat->keyboard.కీలకం_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.కీలకం_inhibitor);
    }

    ఒకవేళ (seat->keyboard.timestamps) {
        zwp_ఆదానం_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ఒకవేళ (seat->keyboard.wl_keyboard) {
        ఒకవేళ (wl_keyboard_get_సంస్కరణ(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_సంస్కరణ) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } లేకపోతే {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ఒకవేళ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ఒకవేళ (seat->keyboard.xkb.compose_పట్టిక) {
        WAYLAND_xkb_compose_పట్టిక_unref(seat->keyboard.xkb.compose_పట్టిక);
    }

    ఒకవేళ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ఒకవేళ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

స్థిర శూన్య Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ఒకవేళ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ఒకవేళ (seat->touch.timestamps) {
        zwp_ఆదానం_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ఒకవేళ (seat->touch.wl_touch) {
        ఒకవేళ (wl_touch_get_సంస్కరణ(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_సంస్కరణ) {
            wl_touch_release(seat->touch.wl_touch);
        } లేకపోతే {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

స్థిర శూన్య seat_handle_capabilities(శూన్య *దత్తాంశం, నిర్మాణం wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    అక్షరం name_fmt[256];

    ఒకవేళ ((capabilities & WL_SEAT_CAPABILITY_సూచిక) && !seat->సూచిక_2.wl_సూచిక) {
        seat->సూచిక_2.wl_సూచిక = wl_seat_get_సూచిక(wl_seat);
        SDL_zero(seat->సూచిక_2.pending_చట్రం.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_సూచిక_సమితి_user_దత్తాంశం(seat->సూచిక_2.wl_సూచిక, seat);
        wl_సూచిక_కూడు_listener(seat->సూచిక_2.wl_సూచిక, &సూచిక_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_సూచిక_Gestures(seat);

        seat->సూచిక_2.sdl_id = SDL_Get_తదుపరి_Object_ID();

        ఒకవేళ (seat->name) {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s (%s)", WAYLAND_DEFAULT_సూచిక_NAME, seat->name);
        } లేకపోతే {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_సూచిక_NAME, seat->సూచిక_2.sdl_id);
        }

        SDL_కూడు_Mouse(seat->సూచిక_2.sdl_id, name_fmt);
    } లేకపోతే ఒకవేళ (!(capabilities & WL_SEAT_CAPABILITY_సూచిక) && seat->సూచిక_2.wl_సూచిక) {
        Wayland_Seat_Destroy_సూచిక(seat);
    }

    ఒకవేళ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_సమితి_user_దత్తాంశం(seat->touch.wl_touch, seat);
        wl_touch_కూడు_listener(seat->touch.wl_touch, &touch_listener, seat);

        ఒకవేళ (seat->name) {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } లేకపోతే {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_కూడు_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_ప్రత్యక్ష, name_fmt);
    } లేకపోతే ఒకవేళ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ఒకవేళ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_సమితి_user_దత్తాంశం(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_కూడు_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_తదుపరి_Object_ID();

        ఒకవేళ (seat->name) {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } లేకపోతే {
            SDL_snprintf(name_fmt, పరిమాణం(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_కూడు_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } లేకపోతే ఒకవేళ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_రిజిస్టరు_ఆదానం_Timestamp_Listeners(seat);
}

స్థిర శూన్య seat_handle_name(శూన్య *దత్తాంశం, నిర్మాణం wl_seat *wl_seat, స్థిరరాశి అక్షరం *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;

    ఒకవేళ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

స్థిర శూన్య దత్తాంశం_offer_handle_offer(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_offer *wl_దత్తాంశం_offer,
                                    స్థిరరాశి అక్షరం *mime_type)
{
    SDL_Wayland_దత్తాంశం_Offer *offer = దత్తాంశం;
    Wayland_దత్తాంశం_Offer_కూడు_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_దత్తాంశం_offer ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)wl_దత్తాంశం_offer) : -1),
                 mime_type);
}

స్థిర శూన్య దత్తాంశం_offer_handle_ఆధారం_actions(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_offer *wl_దత్తాంశం_offer,
                                             uint32_t ఆధారం_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_దత్తాంశం_offer ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)wl_దత్తాంశం_offer) : -1),
                 ఆధారం_actions);
}

స్థిర శూన్య దత్తాంశం_offer_handle_actions(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_offer *wl_దత్తాంశం_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_దత్తాంశం_offer ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)wl_దత్తాంశం_offer) : -1),
                 dnd_action);
}

స్థిర స్థిరరాశి నిర్మాణం wl_దత్తాంశం_offer_listener దత్తాంశం_offer_listener = {
    దత్తాంశం_offer_handle_offer,
    దత్తాంశం_offer_handle_ఆధారం_actions, // Version 3
    దత్తాంశం_offer_handle_actions,        // Version 3
};

స్థిర శూన్య primary_selection_offer_handle_offer(శూన్య *దత్తాంశం, నిర్మాణం zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 స్థిరరాశి అక్షరం *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = దత్తాంశం;
    Wayland_Primary_Selection_Offer_కూడు_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

స్థిర స్థిరరాశి నిర్మాణం zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

స్థిర శూన్య దత్తాంశం_device_handle_దత్తాంశం_offer(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device,
                                          నిర్మాణం wl_దత్తాంశం_offer *id)
{
    SDL_Wayland_దత్తాంశం_Offer *దత్తాంశం_offer = SDL_calloc(1, పరిమాణం(*దత్తాంశం_offer));
    ఒకవేళ (దత్తాంశం_offer) {
        SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = (SDL_Wayland_దత్తాంశం_Device *)దత్తాంశం;
        దత్తాంశం_offer->offer = id;
        దత్తాంశం_offer->దత్తాంశం_device = దత్తాంశం_device;
        దత్తాంశం_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(దత్తాంశం_offer->mimes));
        wl_దత్తాంశం_offer_సమితి_user_దత్తాంశం(id, దత్తాంశం_offer);
        wl_దత్తాంశం_offer_కూడు_listener(id, &దత్తాంశం_offer_listener, దత్తాంశం_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id) : -1));
    }
}

స్థిర శూన్య దత్తాంశం_device_handle_enter(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device,
                                     uint32_t serial, నిర్మాణం wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, నిర్మాణం wl_దత్తాంశం_offer *id)
{
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *కిటికీ = surface ? Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface) : ఖాళీ;
    దత్తాంశం_device->has_mime_file = false;
    దత్తాంశం_device->పాఠ్యం_mime_type = ఖాళీ;

    దత్తాంశం_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ఒకవేళ (id) {
        దత్తాంశం_device->drag_offer = wl_దత్తాంశం_offer_get_user_దత్తాంశం(id);
    }

    ఒకవేళ (దత్తాంశం_device->drag_offer && కిటికీ && కిటికీ->స్వీకరించు_drag_and_drop) {
#నిర్వచితమైతే SDL_USE_LIBDBUS
        ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(దత్తాంశం_device->drag_offer, FILE_PORTAL_MIME)) {
            దత్తాంశం_device->has_mime_file = true;
            wl_దత్తాంశం_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#అయితే_ముగింపు
        ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(దత్తాంశం_device->drag_offer, FILE_MIME)) {
            దత్తాంశం_device->has_mime_file = true;
            wl_దత్తాంశం_offer_accept(id, serial, FILE_MIME);
        }

        ఒకవేళ (!దత్తాంశం_device->has_mime_file) {
            size_t mime_లెక్క = 0;
            స్థిరరాశి అక్షరం *స్థిరరాశి *పాఠ్యం_mime_types = Wayland_Get_పాఠ్యం_Mime_Types(SDL_GetVideoDevice(), &mime_లెక్క);
            కొరకు (size_t i = 0; i < mime_లెక్క; ++i) {
                ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(దత్తాంశం_device->drag_offer, పాఠ్యం_mime_types[i])) {
                    దత్తాంశం_device->పాఠ్యం_mime_type = పాఠ్యం_mime_types[i];
                    wl_దత్తాంశం_offer_accept(id, serial, పాఠ్యం_mime_types[i]);
                    ఆపు;
                }
            }
        }

        ఒకవేళ (దత్తాంశం_device->has_mime_file || దత్తాంశం_device->పాఠ్యం_mime_type) {
            // SDL only supports "copy" style drag and drop
            ఒకవేళ (wl_దత్తాంశం_offer_get_సంస్కరణ(దత్తాంశం_device->drag_offer->offer) >= WL_దత్తాంశం_OFFER_సమితి_ACTIONS_SINCE_సంస్కరణ) {
                wl_దత్తాంశం_offer_సమితి_actions(దత్తాంశం_device->drag_offer->offer, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_COPY, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            దత్తాంశం_device->dnd_కిటికీ = కిటికీ->sdlwindow;
            దత్తాంశం_device->dnd_surface = surface;
            ద్విగుణ dx = wl_fixed_గమ్యం_double(x);
            ద్విగుణ dy = wl_fixed_గమ్యం_double(y);

            // If over the mask, adjust the offset.
            ఒకవేళ (surface == కిటికీ->ముసుగు.surface) {
                dx += (ద్విగుణ)కిటికీ->ముసుగు.స్థానభ్రంశం_x;
                dy += (ద్విగుణ)కిటికీ->ముసుగు.స్థానభ్రంశం_y;
            }

            dx *= కిటికీ->సూచిక_scale.x;
            dy *= కిటికీ->సూచిక_scale.y;

            SDL_SendDropPosition(దత్తాంశం_device->dnd_కిటికీ, (దశాంశం)dx, (దశాంశం)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id),
                         wl_fixed_గమ్యం_int(x), wl_fixed_గమ్యం_int(y), SDL_Get_కిటికీ_ID(దత్తాంశం_device->dnd_కిటికీ), serial);
        } లేకపోతే {
            // Decline the offer.
            wl_దత్తాంశం_offer_accept(id, serial, ఖాళీ);
            ఒకవేళ (wl_దత్తాంశం_offer_get_సంస్కరణ(దత్తాంశం_device->drag_offer->offer) >= WL_దత్తాంశం_OFFER_సమితి_ACTIONS_SINCE_సంస్కరణ) {
                wl_దత్తాంశం_offer_సమితి_actions(దత్తాంశం_device->drag_offer->offer, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_NONE, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id), wl_fixed_గమ్యం_int(x), wl_fixed_గమ్యం_int(y), serial);
        }
    } లేకపోతే {
        దత్తాంశం_device->dnd_కిటికీ = ఖాళీ;
        దత్తాంశం_device->dnd_surface = ఖాళీ;

        // Decline the offer.
        ఒకవేళ (id) {
            wl_దత్తాంశం_offer_accept(id, serial, ఖాళీ);
            ఒకవేళ (wl_దత్తాంశం_offer_get_సంస్కరణ(దత్తాంశం_device->drag_offer->offer) >= WL_దత్తాంశం_OFFER_సమితి_ACTIONS_SINCE_సంస్కరణ) {
                wl_దత్తాంశం_offer_సమితి_actions(దత్తాంశం_device->drag_offer->offer, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_NONE, WL_దత్తాంశం_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id) : -1,
                     wl_fixed_గమ్యం_int(x), wl_fixed_గమ్యం_int(y), serial);
    }
}

స్థిర శూన్య దత్తాంశం_device_handle_leave(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device)
{
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = దత్తాంశం;

    ఒకవేళ (దత్తాంశం_device->drag_offer) {
        ఒకవేళ (దత్తాంశం_device->dnd_కిటికీ) {
            SDL_SendDropComplete(దత్తాంశం_device->dnd_కిటికీ);
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)దత్తాంశం_device->drag_offer->offer),
                         SDL_Get_కిటికీ_ID(దత్తాంశం_device->dnd_కిటికీ), దత్తాంశం_device->drag_serial);
        } లేకపోతే {
            SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)దత్తాంశం_device->drag_offer->offer),
                         దత్తాంశం_device->drag_serial);
        }
        Wayland_దత్తాంశం_Offer_Destroy(దత్తాంశం_device->drag_offer);
        దత్తాంశం_device->drag_offer = ఖాళీ;
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    దత్తాంశం_device->has_mime_file = false;
    దత్తాంశం_device->పాఠ్యం_mime_type = ఖాళీ;
}

స్థిర శూన్య దత్తాంశం_device_handle_motion(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device,
                                      uint32_t సమయం, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = దత్తాంశం;

    ఒకవేళ (దత్తాంశం_device->drag_offer && దత్తాంశం_device->dnd_కిటికీ && (దత్తాంశం_device->has_mime_file || దత్తాంశం_device->పాఠ్యం_mime_type)) {
        SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = దత్తాంశం_device->dnd_కిటికీ->అంతర్గత;
        ద్విగుణ dx = wl_fixed_గమ్యం_double(x);
        ద్విగుణ dy = wl_fixed_గమ్యం_double(y);

        // If over the mask, adjust the offset.
        ఒకవేళ (దత్తాంశం_device->dnd_surface == కిటికీ_దత్తాంశం_2->ముసుగు.surface) {
            dx += (ద్విగుణ)కిటికీ_దత్తాంశం_2->ముసుగు.స్థానభ్రంశం_x;
            dy += (ద్విగుణ)కిటికీ_దత్తాంశం_2->ముసుగు.స్థానభ్రంశం_y;
        }

        dx *= కిటికీ_దత్తాంశం_2->సూచిక_scale.x;
        dy *= కిటికీ_దత్తాంశం_2->సూచిక_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(దత్తాంశం_device->dnd_కిటికీ, (దశాంశం)dx, (దశాంశం)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)దత్తాంశం_device->drag_offer->offer),
                     wl_fixed_గమ్యం_int(x), wl_fixed_గమ్యం_int(y),
                     SDL_Get_కిటికీ_ID(దత్తాంశం_device->dnd_కిటికీ), దత్తాంశం_device->drag_serial);
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_గమ్యం_int(x), wl_fixed_గమ్యం_int(y), -1);
    }
}

స్థిర శూన్య drop_cleanup_handler(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *callback, uint32_t callback_దత్తాంశం)
{
    Wayland_Drop_దత్తాంశం *drop = (Wayland_Drop_దత్తాంశం *)దత్తాంశం;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

స్థిర శూన్య drop_dispatch_handler(శూన్య *దత్తాంశం)
{
    Wayland_Drop_దత్తాంశం *drop = (Wayland_Drop_దత్తాంశం *)దత్తాంశం;
    SDL_Wayland_దత్తాంశం_Offer *offer = drop->offer;
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = offer->దత్తాంశం_device;

    ఒకవేళ (drop->dnd_కిటికీ) {
        size_t నిడివి;
        bool drop_handled = false;

#నిర్వచితమైతే SDL_USE_LIBDBUS
        ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            శూన్య *బఫరు_2 = Wayland_దత్తాంశం_Offer_Receive(offer, FILE_PORTAL_MIME, &నిడివి);
            ఒకవేళ (బఫరు_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ఒకవేళ (dbus) {
                    పూర్ణాంకం మార్గం_లెక్క = 0;
                    అక్షరం **paths = SDL_DBus_DocumentsPortalRetrieveFiles(బఫరు_2, &మార్గం_లెక్క);
                    // If dropped files contain a directory the list is empty
                    ఒకవేళ (paths && మార్గం_లెక్క > 0) {
                        కొరకు (పూర్ణాంకం i = 0; i < మార్గం_లెక్క; i++) {
                            SDL_SendDropFile(drop->dnd_కిటికీ, ఖాళీ, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(బఫరు_2);
            }
        }
#అయితే_ముగింపు
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        ఒకవేళ (!drop_handled) {
            ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(offer, FILE_MIME)) {
                శూన్య *బఫరు_2 = Wayland_దత్తాంశం_Offer_Receive(offer, FILE_MIME, &నిడివి);
                ఒకవేళ (బఫరు_2) {
                    అక్షరం *saveptr = ఖాళీ;
                    అక్షరం *token = SDL_strtok_r((అక్షరం *)బఫరు_2, "\r\n", &saveptr);
                    అయితే (token) {
                        ఒకవేళ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_కిటికీ, ఖాళీ, token);
                        }
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    SDL_free(బఫరు_2);
                    drop_handled = true;
                }
            } లేకపోతే ఒకవేళ (Wayland_దత్తాంశం_Offer_Has_MIME(offer, drop->పాఠ్యం_mime_type)) {
                శూన్య *బఫరు_2 = Wayland_దత్తాంశం_Offer_Receive(offer, drop->పాఠ్యం_mime_type, &నిడివి);
                ఒకవేళ (బఫరు_2) {
                    అక్షరం *saveptr = ఖాళీ;
                    అక్షరం *token = SDL_strtok_r((అక్షరం *)బఫరు_2, "\r\n", &saveptr);
                    అయితే (token) {
                        SDL_Send_Drop_పాఠ్యం(drop->dnd_కిటికీ, token);
                        token = SDL_strtok_r(ఖాళీ, "\r\n", &saveptr);
                    }
                    SDL_free(బఫరు_2);
                    drop_handled = true;
                }
            }
        }

        ఒకవేళ (drop_handled && wl_దత్తాంశం_offer_get_సంస్కరణ(offer->offer) >= WL_దత్తాంశం_OFFER_ముగింపు_SINCE_సంస్కరణ) {
            wl_దత్తాంశం_offer_ముగింపు(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_కిటికీ);
    }

    Wayland_దత్తాంశం_Offer_Destroy(drop->offer);
    drop->offer = ఖాళీ;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(దత్తాంశం_device->seat->display->display);
    wl_callback_కూడు_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

స్థిర శూన్య దత్తాంశం_device_handle_drop(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device)
{
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = దత్తాంశం;

    ఒకవేళ (దత్తాంశం_device->drag_offer && దత్తాంశం_device->dnd_కిటికీ &&
        (దత్తాంశం_device->has_mime_file || దత్తాంశం_device->పాఠ్యం_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)దత్తాంశం_device->drag_offer->offer),
                     SDL_Get_కిటికీ_ID(దత్తాంశం_device->dnd_కిటికీ), దత్తాంశం_device->drag_serial);

        Wayland_పని_Thread_Context *ctx = దత్తాంశం_device->seat->display->పని_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_దత్తాంశం *drop = SDL_calloc(1, పరిమాణం(Wayland_Drop_దత్తాంశం));
        ఒకవేళ (drop) {
            drop->offer = దత్తాంశం_device->drag_offer;
            drop->dnd_కిటికీ = దత్తాంశం_device->dnd_కిటికీ;
            drop->పాఠ్యం_mime_type = దత్తాంశం_device->పాఠ్యం_mime_type;

            WAYLAND_wl_list_చొప్పించు(&దత్తాంశం_device->pending_drops, &drop->link);
            Wayland_పని_Thread_కూడు_పని(ctx, drop_dispatch_handler, drop, &drop->id);
        } లేకపోతే {
            Wayland_దత్తాంశం_Offer_Destroy(దత్తాంశం_device->drag_offer);
        }
    } లేకపోతే {
        SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_దత్తాంశం_Offer_Destroy(దత్తాంశం_device->drag_offer);
    }

    దత్తాంశం_device->drag_offer = ఖాళీ;
}

స్థిర శూన్య దత్తాంశం_device_handle_selection(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_device *wl_దత్తాంశం_device,
                                         నిర్మాణం wl_దత్తాంశం_offer *id)
{
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = దత్తాంశం;
    SDL_Wayland_దత్తాంశం_Offer *offer = ఖాళీ;

    ఒకవేళ (id) {
        offer = wl_దత్తాంశం_offer_get_user_దత్తాంశం(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id) : -1));

    Wayland_దత్తాంశం_Device_సమితి_Selection_Offer(దత్తాంశం_device, offer);
}

స్థిర స్థిరరాశి నిర్మాణం wl_దత్తాంశం_device_listener దత్తాంశం_device_listener = {
    దత్తాంశం_device_handle_దత్తాంశం_offer,
    దత్తాంశం_device_handle_enter,
    దత్తాంశం_device_handle_leave,
    దత్తాంశం_device_handle_motion,
    దత్తాంశం_device_handle_drop,
    దత్తాంశం_device_handle_selection
};

స్థిర శూన్య primary_selection_device_handle_offer(శూన్య *దత్తాంశం, నిర్మాణం zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  నిర్మాణం zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, పరిమాణం(*primary_selection_offer));
    ఒకవేళ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)దత్తాంశం;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_సమితి_user_దత్తాంశం(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_కూడు_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id) : -1));
}

స్థిర శూన్య primary_selection_device_handle_selection(శూన్య *దత్తాంశం, నిర్మాణం zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      నిర్మాణం zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = దత్తాంశం;
    SDL_WaylandPrimarySelectionOffer *offer = ఖాళీ;

    ఒకవేళ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_దత్తాంశం(id);
    }

    ఒకవేళ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((నిర్మాణం wl_proxy *)id) : -1));
}

స్థిర స్థిరరాశి నిర్మాణం zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

స్థిర శూన్య పాఠ్యం_ఆదానం_enter(శూన్య *దత్తాంశం,
                             నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                             నిర్మాణం wl_surface *surface)
{
    // No-op
}

స్థిర శూన్య పాఠ్యం_ఆదానం_leave(శూన్య *దత్తాంశం,
                             నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                             నిర్మాణం wl_surface *surface)
{
    // No-op
}

స్థిర శూన్య పాఠ్యం_ఆదానం_preedit_string(శూన్య *దత్తాంశం,
                                      నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                                      స్థిరరాశి అక్షరం *పాఠ్యం,
                                      int32_t cursor_begin,
                                      int32_t cursor_చివర)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    seat->పాఠ్యం_ఆదానం.has_preedit = true;
    ఒకవేళ (పాఠ్యం) {
        పూర్ణాంకం cursor_begin_utf8 = cursor_begin >= 0 ? (పూర్ణాంకం)SDL_utf8strnlen(పాఠ్యం, cursor_begin) : -1;
        పూర్ణాంకం cursor_చివర_utf8 = cursor_చివర >= 0 ? (పూర్ణాంకం)SDL_utf8strnlen(పాఠ్యం, cursor_చివర) : -1;
        పూర్ణాంకం cursor_కొలత_utf8;
        ఒకవేళ (cursor_చివర_utf8 >= 0) {
            ఒకవేళ (cursor_begin_utf8 >= 0) {
                cursor_కొలత_utf8 = cursor_చివర_utf8 - cursor_begin_utf8;
            } లేకపోతే {
                cursor_కొలత_utf8 = cursor_చివర_utf8;
            }
        } లేకపోతే {
            cursor_కొలత_utf8 = -1;
        }
        SDL_Send_Editing_పాఠ్యం(పాఠ్యం, cursor_begin_utf8, cursor_కొలత_utf8);
    } లేకపోతే {
        SDL_Send_Editing_పాఠ్యం("", 0, 0);
    }
}

స్థిర శూన్య పాఠ్యం_ఆదానం_commit_string(శూన్య *దత్తాంశం,
                                     నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                                     స్థిరరాశి అక్షరం *పాఠ్యం)
{
    SDL_Send_Keyboard_పాఠ్యం(పాఠ్యం);
}

స్థిర శూన్య పాఠ్యం_ఆదానం_delete_surrounding_పాఠ్యం(శూన్య *దత్తాంశం,
                                               నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                                               uint32_t before_నిడివి,
                                               uint32_t after_నిడివి)
{
    // FIXME: Do we care about this event?
}

స్థిర శూన్య పాఠ్యం_ఆదానం_పూర్తి(శూన్య *దత్తాంశం,
                            నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    ఒకవేళ (!seat->పాఠ్యం_ఆదానం.has_preedit) {
        SDL_Send_Editing_పాఠ్యం("", 0, 0);
    }
    seat->పాఠ్యం_ఆదానం.has_preedit = false;
}

స్థిర స్థిరరాశి నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3_listener పాఠ్యం_ఆదానం_listener = {
    పాఠ్యం_ఆదానం_enter,
    పాఠ్యం_ఆదానం_leave,
    పాఠ్యం_ఆదానం_preedit_string,
    పాఠ్యం_ఆదానం_commit_string,
    పాఠ్యం_ఆదానం_delete_surrounding_పాఠ్యం,
    పాఠ్యం_ఆదానం_పూర్తి
};

స్థిర శూన్య Wayland_దత్తాంశం_Device_సమితి_ID(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device)
{
    ఒకవేళ (!దత్తాంశం_device->id_str)
#నిర్వచితమైతే SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ఒకవేళ (dbus) {
            స్థిరరాశి అక్షరం *id = dbus->bus_get_unique_name(dbus->session_conn);
            ఒకవేళ (id) {
                దత్తాంశం_device->id_str = SDL_strdup(id);
            }
        }
    }
    ఒకవేళ (!దత్తాంశం_device->id_str)
#అయితే_ముగింపు
    {
        అక్షరం id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, పరిమాణం(id), "%" SDL_PRIu64, pid);
        దత్తాంశం_device->id_str = SDL_strdup(id);
    }
}

స్థిర శూన్య Wayland_Seat_Create_దత్తాంశం_Device(SDL_WaylandSeat *seat)
{
    ఒకవేళ (!seat->display->దత్తాంశం_device_manager) {
        తిరిగి;
    }

    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = SDL_calloc(1, పరిమాణం(*దత్తాంశం_device));
    ఒకవేళ (!దత్తాంశం_device) {
        తిరిగి;
    }

    దత్తాంశం_device->దత్తాంశం_device = wl_దత్తాంశం_device_manager_get_దత్తాంశం_device(
        seat->display->దత్తాంశం_device_manager, seat->wl_seat);
    దత్తాంశం_device->seat = seat;

    ఒకవేళ (!దత్తాంశం_device->దత్తాంశం_device) {
        SDL_free(దత్తాంశం_device);
        తిరిగి;
    }

    Wayland_దత్తాంశం_Device_సమితి_ID(దత్తాంశం_device);
    WAYLAND_wl_list_init(&దత్తాంశం_device->pending_drops);
    wl_దత్తాంశం_device_సమితి_user_దత్తాంశం(దత్తాంశం_device->దత్తాంశం_device, దత్తాంశం_device);
    wl_దత్తాంశం_device_కూడు_listener(దత్తాంశం_device->దత్తాంశం_device, &దత్తాంశం_device_listener, దత్తాంశం_device);
    seat->దత్తాంశం_device = దత్తాంశం_device;
}

శూన్య Wayland_Display_Init_దత్తాంశం_Device_Manager(SDL_Video_దత్తాంశం *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_దత్తాంశం_Device(seat);
    }
}

స్థిర శూన్య Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ఒకవేళ (!seat->display->primary_selection_device_manager) {
        తిరిగి;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, పరిమాణం(*primary_selection_device));
    ఒకవేళ (!primary_selection_device) {
        తిరిగి;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ఒకవేళ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } లేకపోతే {
        zwp_primary_selection_device_v1_సమితి_user_దత్తాంశం(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_కూడు_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

శూన్య Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_దత్తాంశం *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

స్థిర శూన్య Wayland_Seat_Create_పాఠ్యం_ఆదానం(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->display->పాఠ్యం_ఆదానం_manager) {
        seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం = zwp_పాఠ్యం_ఆదానం_manager_v3_get_పాఠ్యం_ఆదానం(seat->display->పాఠ్యం_ఆదానం_manager, seat->wl_seat);

        ఒకవేళ (seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం) {
            zwp_పాఠ్యం_ఆదానం_v3_సమితి_user_దత్తాంశం(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం, seat);
            zwp_పాఠ్యం_ఆదానం_v3_కూడు_listener(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం,
                                           &పాఠ్యం_ఆదానం_listener, seat);
        }
    }
}

శూన్య Wayland_Display_Init_పాఠ్యం_ఆదానం_Manager(SDL_Video_దత్తాంశం *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_పాఠ్యం_ఆదానం(seat);
    }
}

// Pen/Tablet support...
స్థిర శూన్య tablet_tool_handle_type(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    ఎంపిక (type) {
        #నిర్వచించు CASE(typ) స్థితి ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; తిరిగి
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #నిర్వచనం_రద్దు CASE
        అప్రమేయ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

స్థిర శూన్య tablet_tool_handle_hardware_serial(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

స్థిర శూన్య tablet_tool_handle_hardware_id_wacom(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->info.wacom_id = id_lo;
}

స్థిర శూన్య tablet_tool_handle_capability(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    ఎంపిక (capability) {
        #నిర్వచించు CASE(wltyp,sdltyp) స్థితి ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; తిరిగి
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(దూరం_2, SDL_PEN_CAPABILITY_దూరం);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #నిర్వచనం_రద్దు CASE
        అప్రమేయ: ఆపు;  // unsupported here.
    }
}

స్థిర శూన్య tablet_tool_handle_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    ఒకవేళ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_కిటికీ *కిటికీ = sdltool->focus ? sdltool->focus->sdlwindow : ఖాళీ;
        sdltool->instance_id = SDL_కూడు_Pen_Device(0, ఖాళీ, కిటికీ, &sdltool->info, sdltool, false);
    }
}

స్థిర శూన్య tablet_tool_handle_removed(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    ఒకవేళ (sdltool->instance_id) {
        SDL_కిటికీ *కిటికీ = sdltool->focus ? sdltool->focus->sdlwindow : ఖాళీ;
        SDL_RemovePenDevice(0, కిటికీ, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

స్థిర శూన్య tablet_tool_handle_proximity_లోపల(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t serial, నిర్మాణం zwp_tablet_v2 *tablet, నిర్మాణం wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *windowdata = surface ? Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(surface) : ఖాళీ;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : ఖాళీ;
    sdltool->proximity_serial = serial;
    sdltool->చట్రం.have_proximity = true;
    sdltool->చట్రం.లోపల_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

స్థిర శూన్య tablet_tool_handle_proximity_బహిర్గతం(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.have_proximity = true;
    sdltool->చట్రం.లోపల_proximity = false;
}

స్థిర శూన్య tablet_tool_handle_కిందికి(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.tool_state = WAYLAND_TABLET_TOOL_STATE_కిందికి;
}

స్థిర శూన్య tablet_tool_handle_పైకి(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.tool_state = WAYLAND_TABLET_TOOL_STATE_పైకి;
}

స్థిర శూన్య tablet_tool_handle_motion(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *windowdata = sdltool->focus;
    ఒకవేళ (windowdata) {
        sdltool->చట్రం.x = (దశాంశం)(wl_fixed_గమ్యం_double(sx_w) * windowdata->సూచిక_scale.x);
        sdltool->చట్రం.y = (దశాంశం)(wl_fixed_గమ్యం_double(sy_w) * windowdata->సూచిక_scale.y);
        sdltool->చట్రం.have_motion = true;
    }
}

స్థిర శూన్య tablet_tool_handle_pressure(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.axes[SDL_PEN_AXIS_PRESSURE] = ((దశాంశం) pressure) / 65535.0f;
    sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_PRESSURE);
    ఒకవేళ (pressure) {
        sdltool->చట్రం.axes[SDL_PEN_AXIS_దూరం] = 0.0f;
        sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_దూరం);
    }
}

స్థిర శూన్య tablet_tool_handle_దూరం(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t దూరం)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.axes[SDL_PEN_AXIS_దూరం] = ((దశాంశం) దూరం) / 65535.0f;
    sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_దూరం);
    ఒకవేళ (దూరం) {
        sdltool->చట్రం.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

స్థిర శూన్య tablet_tool_handle_tilt(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.axes[SDL_PEN_AXIS_XTILT] = (దశాంశం)(wl_fixed_గమ్యం_double(xtilt));
    sdltool->చట్రం.axes[SDL_PEN_AXIS_YTILT] = (దశాంశం)(wl_fixed_గమ్యం_double(ytilt));
    sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

స్థిర శూన్య tablet_tool_handle_button(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    పూర్ణాంకం sdlbutton;

    ఎంపిక (button) {
    స్థితి BTN_STYLUS:
        sdlbutton = 1;
        ఆపు;
    స్థితి BTN_STYLUS2:
        sdlbutton = 2;
        ఆపు;
    స్థితి BTN_STYLUS3:
        sdlbutton = 3;
        ఆపు;
    అప్రమేయ:
        తిరిగి;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->చట్రం.buttons)));
    sdltool->చట్రం.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_కిందికి : WAYLAND_TABLET_TOOL_BUTTON_పైకి;
}

స్థిర శూన్య tablet_tool_handle_rotation(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    స్థిరరాశి దశాంశం rotation = (దశాంశం)(wl_fixed_గమ్యం_double(degrees));
    sdltool->చట్రం.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_ROTATION);
}

స్థిర శూన్య tablet_tool_handle_slider(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    sdltool->చట్రం.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->చట్రం.axes_సమితి |= (1u << SDL_PEN_AXIS_SLIDER);
}

స్థిర శూన్య tablet_tool_handle_wheel(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

స్థిర శూన్య tablet_tool_handle_చట్రం(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_tool_v2 *tool, uint32_t సమయం)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) దత్తాంశం;
    స్థిరరాశి SDL_PenID instance_id = sdltool->instance_id;
    ఒకవేళ (!instance_id) {
        తిరిగి;  // Not a pen we report on.
    }

    స్థిరరాశి Uint64 timestamp = Wayland_Adjust_Event_Timestamp_పునాది(Wayland_EventTimestampMSToNS(సమయం));
    SDL_కిటికీ *కిటికీ = sdltool->focus ? sdltool->focus->sdlwindow : ఖాళీ;
    స్థిరరాశి bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ఒకవేళ (sdltool->చట్రం.have_proximity && sdltool->చట్రం.లోపల_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, కిటికీ, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ఒకవేళ (sdltool->చట్రం.have_motion && sdltool->చట్రం.tool_state) {
        ఒకవేళ (sdltool->చట్రం.tool_state == WAYLAND_TABLET_TOOL_STATE_కిందికి) {
            SDL_SendPenMotion(timestamp, instance_id, కిటికీ, sdltool->చట్రం.x, sdltool->చట్రం.y);
            SDL_SendPenTouch(timestamp, instance_id, కిటికీ, is_eraser, true);
        } లేకపోతే {
            SDL_SendPenTouch(timestamp, instance_id, కిటికీ, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, కిటికీ, sdltool->చట్రం.x, sdltool->చట్రం.y);
        }
    } లేకపోతే {
        ఒకవేళ (sdltool->చట్రం.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, కిటికీ, is_eraser, sdltool->చట్రం.tool_state == WAYLAND_TABLET_TOOL_STATE_కిందికి);
        }

        ఒకవేళ (sdltool->చట్రం.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, కిటికీ, sdltool->చట్రం.x, sdltool->చట్రం.y);
        }
    }

    కొరకు (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_లెక్క; i++) {
        ఒకవేళ (sdltool->చట్రం.axes_సమితి & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, కిటికీ, i, sdltool->చట్రం.axes[i]);
        }
    }

    కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(sdltool->చట్రం.buttons); i++) {
        స్థిరరాశి పూర్ణాంకం state = sdltool->చట్రం.buttons[i];
        ఒకవేళ (state) {
            SDL_SendPenButton(timestamp, instance_id, కిటికీ, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_కిందికి);
        }
    }

    ఒకవేళ (sdltool->చట్రం.have_proximity && !sdltool->చట్రం.లోపల_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, కిటికీ, false, false);
        sdltool->focus = ఖాళీ;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->చట్రం);
}

స్థిర స్థిరరాశి నిర్మాణం zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_పూర్తి,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_లోపల,
    tablet_tool_handle_proximity_బహిర్గతం,
    tablet_tool_handle_కిందికి,
    tablet_tool_handle_పైకి,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_దూరం,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_చట్రం
};


స్థిర శూన్య tablet_seat_handle_tablet_added(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_seat_v2 *zwp_tablet_seat_v2, నిర్మాణం zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

స్థిర శూన్య tablet_seat_handle_tool_added(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_seat_v2 *zwp_tablet_seat_v2, నిర్మాణం zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)దత్తాంశం;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, పరిమాణం(*sdltool));

    ఒకవేళ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.అంకె_buttons = -1;

        ఒకవేళ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_చొప్పించు(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_కూడు_listener(tool, &tablet_tool_listener, sdltool);
    }
}

స్థిర శూన్య tablet_seat_handle_pad_added(శూన్య *దత్తాంశం, నిర్మాణం zwp_tablet_seat_v2 *zwp_tablet_seat_v2, నిర్మాణం zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

స్థిర స్థిరరాశి నిర్మాణం zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

స్థిర శూన్య Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_కూడు_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

శూన్య Wayland_DisplayInitTabletManager(SDL_Video_దత్తాంశం *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

స్థిర శూన్య Wayland_remove_all_pens_callback(SDL_PenID instance_id, శూన్య *handle, శూన్య *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

స్థిర శూన్య Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_కిందికి)
{
    ఒకవేళ (!shutting_కిందికి) {
        SDL_WaylandPenTool *tool, *తాత్కాలిక;
        wl_list_for_each_సురక్షిత (tool, తాత్కాలిక, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } లేకపోతే {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, ఖాళీ);
    }

    ఒకవేళ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = ఖాళీ;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

శూన్య Wayland_DisplayCreateSeat(SDL_Video_దత్తాంశం *display, నిర్మాణం wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, పరిమాణం(SDL_WaylandSeat));
    ఒకవేళ (!seat) {
        తిరిగి;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_చొప్పించు(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_దత్తాంశం_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_పాఠ్యం_ఆదానం(seat);

    wl_seat_సమితి_user_దత్తాంశం(seat->wl_seat, seat);
    wl_seat_కూడు_listener(seat->wl_seat, &seat_listener, seat);

    ఒకవేళ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

శూన్య Wayland_Display_Remove_కిటికీ_References_From_Seats(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ఒకవేళ (seat->keyboard.focus == కిటికీ) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, కిటికీ->surface);
        }

        ఒకవేళ (seat->సూచిక_2.focus == కిటికీ) {
            seat->సూచిక_2.pending_చట్రం.leave_surface = seat->సూచిక_2.focus->surface;
            సూచిక_dispatch_leave(seat, true);
            seat->సూచిక_2.pending_చట్రం.leave_surface = ఖాళీ;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_బిందువు *tp, *తాత్కాలిక;
        wl_list_for_each_సురక్షిత (tp, తాత్కాలిక, &seat->touch.points, link) {
            ఒకవేళ (tp->surface == కిటికీ->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ఒకవేళ (tool->focus == కిటికీ) {
                tool->focus = ఖాళీ;
                Wayland_TabletToolUpdateCursor(tool);
                ఒకవేళ (tool->instance_id) {
                    SDL_RemovePenDevice(0, కిటికీ->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_దత్తాంశం *drop, *drop_తాత్కాలిక;
        wl_list_for_each_సురక్షిత (drop, drop_తాత్కాలిక, &seat->దత్తాంశం_device->pending_drops, link) {
            ఒకవేళ (drop->dnd_కిటికీ == కిటికీ->sdlwindow) {
                Wayland_పని_Thread_Cancel_పని(display->పని_thread_context, drop->id);

                ఒకవేళ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_దత్తాంశం_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

శూన్య Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_కిందికి)
{
    ఒకవేళ (!seat) {
        తిరిగి;
    }

    SDL_free(seat->name);

    ఒకవేళ (seat->దత్తాంశం_device) {
        ఒకవేళ (seat->దత్తాంశం_device->selection_offer) {
            Wayland_దత్తాంశం_Offer_Destroy(seat->దత్తాంశం_device->selection_offer);
        }
        ఒకవేళ (seat->దత్తాంశం_device->selection_ఆధారం) {
            Wayland_దత్తాంశం_ఆధారం_Destroy(seat->దత్తాంశం_device->selection_ఆధారం);
        }
        ఒకవేళ (seat->దత్తాంశం_device->drag_offer) {
            Wayland_దత్తాంశం_Offer_Destroy(seat->దత్తాంశం_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_దత్తాంశం *drop, *drop_తాత్కాలిక;
        wl_list_for_each_సురక్షిత (drop, drop_తాత్కాలిక, &seat->దత్తాంశం_device->pending_drops, link) {
            Wayland_పని_Thread_Cancel_పని(seat->display->పని_thread_context, drop->id);

            ఒకవేళ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_దత్తాంశం_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ఒకవేళ (seat->దత్తాంశం_device->దత్తాంశం_device) {
            ఒకవేళ (wl_దత్తాంశం_device_get_సంస్కరణ(seat->దత్తాంశం_device->దత్తాంశం_device) >= WL_దత్తాంశం_DEVICE_RELEASE_SINCE_సంస్కరణ) {
                wl_దత్తాంశం_device_release(seat->దత్తాంశం_device->దత్తాంశం_device);
            } లేకపోతే {
                wl_దత్తాంశం_device_destroy(seat->దత్తాంశం_device->దత్తాంశం_device);
            }
        }
        SDL_free(seat->దత్తాంశం_device->id_str);
        SDL_free(seat->దత్తాంశం_device);
    }

    ఒకవేళ (seat->primary_selection_device) {
        ఒకవేళ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ఒకవేళ (seat->primary_selection_device->selection_ఆధారం) {
            Wayland_Primary_Selection_ఆధారం_Destroy(seat->primary_selection_device->selection_ఆధారం);
        }
        ఒకవేళ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ఒకవేళ (seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం) {
        zwp_పాఠ్యం_ఆదానం_v3_destroy(seat->పాఠ్యం_ఆదానం.zwp_పాఠ్యం_ఆదానం);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_సూచిక(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_కిందికి);

    ఒకవేళ (wl_seat_get_సంస్కరణ(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_సంస్కరణ) {
        wl_seat_release(seat->wl_seat);
    } లేకపోతే {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

స్థిర శూన్య Wayland_Seat_Update_Relative_సూచిక(SDL_WaylandSeat *seat)
{
    ఒకవేళ (seat->display->relative_సూచిక_manager) {
        bool relative_focus = false;

        ఒకవేళ (seat->సూచిక_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ఒకవేళ (seat->సూచిక_2.focus->sdlwindow->flags & SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం) {
                ఒకవేళ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->సూచిక_2.focus;
                } లేకపోతే {
                    relative_focus = seat->సూచిక_2.focus->keyboard_focus_లెక్క != 0;
                }
            } లేకపోతే {
                relative_focus = SDL_GetMouse()->warp_emulation_చురుకైన;
            }
        }

        ఒకవేళ (relative_focus) {
            ఒకవేళ (!seat->సూచిక_2.relative_సూచిక) {
                seat->సూచిక_2.relative_సూచిక = zwp_relative_సూచిక_manager_v1_get_relative_సూచిక(seat->display->relative_సూచిక_manager, seat->సూచిక_2.wl_సూచిక);
                zwp_relative_సూచిక_v1_కూడు_listener(seat->సూచిక_2.relative_సూచిక, &relative_సూచిక_listener, seat);
            }
        } లేకపోతే ఒకవేళ (seat->సూచిక_2.relative_సూచిక) {
            zwp_relative_సూచిక_v1_destroy(seat->సూచిక_2.relative_సూచిక);
            seat->సూచిక_2.relative_సూచిక = ఖాళీ;
        }
    }
}

స్థిర శూన్య Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_దత్తాంశం *display = seat->display;

    ఒకవేళ (display->కీలకం_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ఒకవేళ (seat->keyboard.కీలకం_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.కీలకం_inhibitor);
            seat->keyboard.కీలకం_inhibitor = ఖాళీ;
        }

        ఒకవేళ (seat->keyboard.wl_keyboard) {
            SDL_కిటికీ_దత్తాంశం *w = seat->keyboard.focus;
            ఒకవేళ (w) {
                SDL_కిటికీ *కిటికీ = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED) {
                    seat->keyboard.కీలకం_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->కీలకం_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

శూన్య Wayland_Seat_Update_సూచిక_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_దత్తాంశం *display = seat->display;
    Wayland_Seat_Update_Relative_సూచిక(seat);

    ఒకవేళ (display->సూచిక_constraints) {
        ఒకవేళ (seat->సూచిక_2.locked_సూచిక && !seat->సూచిక_2.relative_సూచిక) {
            zwp_locked_సూచిక_v1_destroy(seat->సూచిక_2.locked_సూచిక);
            seat->సూచిక_2.locked_సూచిక = ఖాళీ;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_సూచిక_Cursor(seat);
        }

        ఒకవేళ (seat->సూచిక_2.wl_సూచిక) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ఒకవేళ (seat->సూచిక_2.relative_సూచిక) {
                ఒకవేళ (!seat->సూచిక_2.locked_సూచిక) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ఒకవేళ (seat->సూచిక_2.confined_సూచిక) {
                        zwp_confined_సూచిక_v1_destroy(seat->సూచిక_2.confined_సూచిక);
                        seat->సూచిక_2.confined_సూచిక = ఖాళీ;
                    }

                    seat->సూచిక_2.locked_సూచిక = zwp_సూచిక_constraints_v1_తాళం_సూచిక(display->సూచిక_constraints,
                                                                                           seat->సూచిక_2.focus->surface,
                                                                                           seat->సూచిక_2.wl_సూచిక, ఖాళీ,
                                                                                           ZWP_సూచిక_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_సూచిక_v1_కూడు_listener(seat->సూచిక_2.locked_సూచిక, &locked_సూచిక_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_సూచిక_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                తిరిగి;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ఒకవేళ (seat->సూచిక_2.confined_సూచిక) {
                zwp_confined_సూచిక_v1_destroy(seat->సూచిక_2.confined_సూచిక);
                seat->సూచిక_2.confined_సూచిక = ఖాళీ;
            }

            SDL_కిటికీ_దత్తాంశం *w = seat->సూచిక_2.focus;
            ఒకవేళ (!w) {
                తిరిగి;
            }

            SDL_కిటికీ *కిటికీ = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) ||
                (!(కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED) && SDL_Rect_ఖాళీలు(&కిటికీ->mouse_rect))) {
                తిరిగి;
            }

            నిర్మాణం wl_region *confine_rect = ఖాళీ;
            ఒకవేళ (!SDL_Rect_ఖాళీలు(&కిటికీ->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(కిటికీ, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_కూడు(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                ఒకవేళ (!SDL_బిందువు_లోపల_Rect(&seat->సూచిక_2.చివరి_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    పూర్ణాంకం closest_x = seat->సూచిక_2.చివరి_motion.x;
                    పూర్ణాంకం closest_y = seat->సూచిక_2.చివరి_motion.y;

                    ఒకవేళ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } లేకపోతే ఒకవేళ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ఒకవేళ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } లేకపోతే ఒకవేళ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ఒకవేళ (confine_rect || (కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED)) {
                ఒకవేళ (కిటికీ->mouse_rect.w != 1 && కిటికీ->mouse_rect.h != 1) {
                    seat->సూచిక_2.confined_సూచిక =
                        zwp_సూచిక_constraints_v1_confine_సూచిక(display->సూచిక_constraints,
                                                                   w->surface,
                                                                   seat->సూచిక_2.wl_సూచిక,
                                                                   confine_rect,
                                                                   ZWP_సూచిక_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_సూచిక_v1_కూడు_listener(seat->సూచిక_2.confined_సూచిక,
                                                         &confined_సూచిక_listener,
                                                         seat);
                } లేకపోతే {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->సూచిక_2.locked_సూచిక =
                        zwp_సూచిక_constraints_v1_తాళం_సూచిక(display->సూచిక_constraints,
                                                                w->surface,
                                                                seat->సూచిక_2.wl_సూచిక,
                                                                ఖాళీ,
                                                                ZWP_సూచిక_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_సూచిక_v1_కూడు_listener(seat->సూచిక_2.locked_సూచిక,
                                                       &locked_సూచిక_listener,
                                                       seat);
                }
                ఒకవేళ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

శూన్య Wayland_Display_Update_సూచిక_Grabs(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ఒకవేళ (!కిటికీ || seat->సూచిక_2.focus == కిటికీ) {
            Wayland_Seat_Update_సూచిక_Grab(seat);
        }
    }
}

శూన్య Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ఒకవేళ (!కిటికీ || seat->keyboard.focus == కిటికీ) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

శూన్య Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ఒకవేళ (serial > seat->చివరి_implicit_grab_serial) {
        seat->చివరి_implicit_grab_serial = serial;
        seat->display->చివరి_implicit_grab_seat = seat;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
