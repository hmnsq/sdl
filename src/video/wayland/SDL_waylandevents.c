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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_scancode_tables_c.h"
#شامل "../../events/SDL_keysym_to_keycode_c.h"
#شامل "../../core/linux/SDL_system_theme.h"
#شامل "../SDL_sysvideo.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylandmouse.h"
#شامل "SDL_waylandclipboard.h"
#شامل "SDL_waylandkeyboard.h"

#شامل "pointer-constraints-unstable-v1-client-protocol.h"
#شامل "relative-pointer-unstable-v1-client-protocol.h"
#شامل "xdg-shell-client-protocol.h"
#شامل "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#شامل "text-input-unstable-v3-client-protocol.h"
#شامل "tablet-v2-client-protocol.h"
#شامل "primary-selection-unstable-v1-client-protocol.h"
#شامل "input-timestamps-unstable-v1-client-protocol.h"
#شامل "pointer-gestures-unstable-v1-client-protocol.h"
#شامل "cursor-shape-v1-client-protocol.h"
#شامل "viewporter-client-protocol.h"

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
#شامل <libdecor.h>
#اگر_ختم

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
#شامل <linux/input.h>
#ورنہ
#تعریف_کرو BTN_بایاں    (0x110)
#تعریف_کرو BTN_دایاں   (0x111)
#تعریف_کرو BTN_درمیان  (0x112)
#تعریف_کرو BTN_SIDE    (0x113)
#تعریف_کرو BTN_EXTRA   (0x114)
#تعریف_کرو BTN_STYLUS  (0x14b)
#تعریف_کرو BTN_STYLUS2 (0x14c)
#تعریف_کرو BTN_STYLUS3 (0x149)
#اگر_ختم
#شامل "../../events/SDL_keysym_to_scancode_c.h"
#شامل "../../events/imKStoUCS.h"
#شامل <errno.h>
#شامل <sys/mman.h>
#شامل <unistd.h>
#شامل <xkbcommon/xkbcommon-compose.h>
#شامل <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#تعریف_کرو WAYLAND_WHEEL_AXIS_UNIT 10

#اگر_غیر_تعریف_شدہ XKB_MOD_NAME_MOD3
#تعریف_کرو XKB_MOD_NAME_MOD3 "Mod3"
#اگر_ختم

#اگر_غیر_تعریف_شدہ XKB_MOD_NAME_MOD5
#تعریف_کرو XKB_MOD_NAME_MOD5 "Mod5"
#اگر_ختم

// Keyboard and mouse names to match XWayland
#تعریف_کرو WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#تعریف_کرو WAYLAND_DEFAULT_اشارہ_گر_NAME "Virtual core pointer"
#تعریف_کرو WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#تعریف_کرو WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_مقصد_NS(10)

// Timer rollover detection thresholds
#تعریف_کرو WAYLAND_TIMER_ROLLOVER_INTERVAL_کم  (SDL_MAX_UINT32 / 16U)
#تعریف_کرو WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند (WAYLAND_TIMER_ROLLOVER_INTERVAL_کم * 15U)

// Scoped function declarations
ساکن خالی Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

قسمتعریف ساخت
{
    Uint32 کلید;
    SDL_Scancode scancode;
} Wayland_Reserved_کلید;

قسمتعریف ساخت
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    ساخت wl_surface *surface;

    ساخت wl_list link;
} SDL_Wayland_Touch_نقطہ;

ساکن خالی Wayland_Seat_جوڑو_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ساخت wl_surface *surface)
{
    SDL_Wayland_Touch_نقطہ *tp = SDL_malloc(حجم(SDL_Wayland_Touch_نقطہ));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_داخل_کرو(&seat->touch.points, &tp->link);
}

ساکن خالی Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_نقطہ *tp)
{
    اگر (tp->surface) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(tp->surface);

        اگر (کھڑکی_ڈیٹا_2) {
            ثابت اعشاری x = (اعشاری)(wl_fixed_مقصد_double(tp->fx) / کھڑکی_ڈیٹا_2->current.logical_چوڑائی);
            ثابت اعشاری y = (اعشاری)(wl_fixed_مقصد_double(tp->fy) / کھڑکی_ڈیٹا_2->current.logical_اونچائی);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), کھڑکی_ڈیٹا_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --کھڑکی_ڈیٹا_2->فعال_touch_گنتی;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            اگر (SDL_GetMouseFocus() == کھڑکی_ڈیٹا_2->sdlwindow && !کھڑکی_ڈیٹا_2->keyboard_focus_گنتی &&
                !کھڑکی_ڈیٹا_2->اشارہ_گر_focus_گنتی && !کھڑکی_ڈیٹا_2->فعال_touch_گنتی) {
                SDL_سیٹ_Mouse_Focus(تہی);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساکن خالی Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, ساخت wl_surface **surface)
{
    SDL_Wayland_Touch_نقطہ *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        اگر (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            اگر (surface) {
                *surface = tp->surface;
            }
            توڑو;
        }
    }
}

ساکن خالی Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, ساخت wl_surface **surface)
{
    SDL_Wayland_Touch_نقطہ *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        اگر (tp->id == id) {
            اگر (fx) {
                *fx = tp->fx;
            }
            اگر (fy) {
                *fy = tp->fy;
            }
            اگر (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            توڑو;
        }
    }
}

ساکن خالی Wayland_GetScaledMouseRect(SDL_کھڑکی *کھڑکی, SDL_Rect *scaled_rect)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = کھڑکی->اندرونی_2;

    scaled_rect->x = (صحیح)SDL_floor(کھڑکی->mouse_rect.x / کھڑکی_ڈیٹا_2->اشارہ_گر_scale.x);
    scaled_rect->y = (صحیح)SDL_floor(کھڑکی->mouse_rect.y / کھڑکی_ڈیٹا_2->اشارہ_گر_scale.y);
    scaled_rect->w = (صحیح)SDL_ceil(کھڑکی->mouse_rect.w / کھڑکی_ڈیٹا_2->اشارہ_گر_scale.x);
    scaled_rect->h = (صحیح)SDL_ceil(کھڑکی->mouse_rect.h / کھڑکی_ڈیٹا_2->اشارہ_گر_scale.y);
}

ساکن Uint64 Wayland_Adjust_Event_Timestamp_بنیاد(Uint64 nsTimestamp)
{
    ساکن Uint64 timestamp_انحراف = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    اگر (!timestamp_انحراف) {
        timestamp_انحراف = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_انحراف;

    اگر (nsTimestamp > now) {
        timestamp_انحراف -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    واپس nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساکن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساکن Uint64 timestamp_انحراف = 0;
    ساکن Uint32 آخری = 0;
    Uint64 timestamp = SDL_MS_مقصد_NS(wl_timestamp_ms) + timestamp_انحراف;

    اگر (wl_timestamp_ms >= آخری) {
        اگر (timestamp_انحراف && آخری < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
        } ورنہ {
            آخری = wl_timestamp_ms;
        }
    } ورنہ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        اگر (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && آخری > WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند) {
            timestamp_انحراف += SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
            آخری = wl_timestamp_ms;
        }
    }

    واپس timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ساکن Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    واپس Wayland_Adjust_Event_Timestamp_بنیاد(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساکن Uint64 Wayland_Get_اشارہ_گر_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    واپس Wayland_Adjust_Event_Timestamp_بنیاد(seat->اشارہ_گر_2.timestamps ? seat->اشارہ_گر_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    واپس Wayland_Adjust_Event_Timestamp_بنیاد(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساکن خالی داخلہ_timestamp_listener(خالی *ڈیٹا, ساخت zwp_داخلہ_timestamps_v1 *zwp_داخلہ_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)ڈیٹا) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_فی_دوسرا) + tv_nsec;
}

ساکن ثابت ساخت zwp_داخلہ_timestamps_v1_listener timestamp_listener = {
    داخلہ_timestamp_listener
};

ساکن خالی Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    اگر (seat->display->داخلہ_timestamps_manager) {
        اگر (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_داخلہ_timestamps_manager_v1_get_keyboard_timestamps(seat->display->داخلہ_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        اگر (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.timestamps) {
            seat->اشارہ_گر_2.timestamps = zwp_داخلہ_timestamps_manager_v1_get_اشارہ_گر_timestamps(seat->display->داخلہ_timestamps_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->اشارہ_گر_2.timestamps, &timestamp_listener, &seat->اشارہ_گر_2.highres_timestamp_ns);
        }

        اگر (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_داخلہ_timestamps_manager_v1_get_touch_timestamps(seat->display->داخلہ_timestamps_manager, seat->touch.wl_touch);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

خالی Wayland_Display_Init_داخلہ_Timestamp_Manager(SDL_Video_ڈیٹا *display)
{
    اگر (display->داخلہ_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(seat);
        }
    }
}

ساکن خالی handle_pinch_begin(خالی *ڈیٹا, ساخت zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t serial, uint32_t وقت, ساخت wl_surface *surface, uint32_t fingers)
{
    اگر (!surface) {
        واپس;
    }

    SDL_کھڑکی_ڈیٹا *wind = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);
    اگر (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
        seat->اشارہ_گر_2.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساکن خالی handle_pinch_update(خالی *ڈیٹا, ساخت zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t وقت,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;

    اگر (seat->اشارہ_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);
        ثابت اعشاری s = (اعشاری)wl_fixed_مقصد_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->اشارہ_گر_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساکن خالی handle_pinch_انتہا(خالی *ڈیٹا, ساخت zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t serial, uint32_t وقت, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;

    اگر (seat->اشارہ_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);
        SDL_SendPinch(SDL_EVENT_PINCH_انتہا, timestamp, seat->اشارہ_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->اشارہ_گر_2.gesture_focus = تہی;
    }
}

ساکن ثابت ساخت zwp_اشارہ_گر_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_انتہا
};

ساکن خالی Wayland_Seat_Create_اشارہ_گر_Gestures(SDL_WaylandSeat *seat)
{
    اگر (seat->display->zwp_اشارہ_گر_gestures) {
        اگر (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.gesture_pinch) {
            seat->اشارہ_گر_2.gesture_pinch = zwp_اشارہ_گر_gestures_v1_get_pinch_gesture(seat->display->zwp_اشارہ_گر_gestures, seat->اشارہ_گر_2.wl_اشارہ_گر);
            zwp_اشارہ_گر_gesture_pinch_v1_سیٹ_user_ڈیٹا(seat->اشارہ_گر_2.gesture_pinch, seat);
            zwp_اشارہ_گر_gesture_pinch_v1_جوڑو_listener(seat->اشارہ_گر_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

خالی Wayland_Display_Init_اشارہ_گر_Gesture_Manager(SDL_Video_ڈیٹا *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_اشارہ_گر_Gestures(seat);
    }
}

ساکن خالی Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    اگر (seat->display->cursor_shape_manager) {
        اگر (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.cursor_state.cursor_shape) {
            seat->اشارہ_گر_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_اشارہ_گر(seat->display->cursor_shape_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            اگر (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

خالی Wayland_DisplayInitCursorShapeManager(SDL_Video_ڈیٹا *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ساکن خالی Wayland_Seat_سیٹ_Keymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    اگر (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_سیٹ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_سیٹ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساکن خالی keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    جب (elapsed >= repeat_info->اگلا_repeat_ns) {
        اگر (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->بنیاد_وقت_ns + repeat_info->اگلا_repeat_ns;
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_بنیاد(timestamp), repeat_info->keyboard_id, repeat_info->کلید, repeat_info->scancode, true);
        }
        اگر (repeat_info->متن[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(repeat_info->متن);
        }
        repeat_info->اگلا_repeat_ns += SDL_NS_فی_دوسرا / (Uint64)repeat_info->repeat_شرح;
    }
}

ساکن خالی keyboard_repeat_سیٹ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کلید, Uint32 wl_press_وقت_ms,
                                Uint64 بنیاد_وقت_ns, uint32_t scancode, ثابت حرف *متن)
{
    اگر (!repeat_info->repeat_شرح) {
        واپس;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کلید = کلید;
    repeat_info->wl_press_وقت_ms = wl_press_وقت_ms;
    repeat_info->بنیاد_وقت_ns = بنیاد_وقت_ns;
    repeat_info->sdl_press_وقت_ns = SDL_GetTicksNS();
    repeat_info->اگلا_repeat_ns = SDL_MS_مقصد_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    اگر (متن) {
        SDL_strlcpy(repeat_info->متن, متن, SDL_arraysize(repeat_info->متن));
    } ورنہ {
        repeat_info->متن[0] = '\0';
    }
}

ساکن خالی sync_مکمل_handler(خالی *ڈیٹا, ساخت wl_callback *callback, uint32_t callback_ڈیٹا)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساکن ساخت wl_callback_listener sync_listener = {
    sync_مکمل_handler
};

خالی Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *d = _this->اندرونی_2;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    ساخت wl_callback *cb = wl_display_sync(d->display);
    wl_callback_جوڑو_listener(cb, &sync_listener, تہی);
    WAYLAND_wl_display_flush(d->display);
}

صحیح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_ڈیٹا *d = _this->اندرونی_2;
    SDL_WaylandSeat *seat;
    Uint64 آغاز = SDL_GetTicksNS();
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحیح ret;
    bool poll_alarm_سیٹ = false;

#اگر_تعریف_شدہ SDL_USE_IME
    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
    اگر (!d->متن_داخلہ_manager && keyboard_focus && SDL_متن_داخلہ_فعال(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        اگر (timeoutNS < 0 || SDL_MS_مقصد_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_مقصد_NS(200);
            poll_alarm_سیٹ = true;
        }
    }
#اگر_ختم

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        اگر (seat->keyboard.repeat.کلید) {
            ثابت Uint64 elapsed = آغاز - seat->keyboard.repeat.sdl_press_وقت_ns;
            ثابت Uint64 اگلا_repeat_wait_وقت = (seat->keyboard.repeat.اگلا_repeat_ns - elapsed) + 1;
            اگر (timeoutNS < 0 || اگلا_repeat_wait_وقت <= timeoutNS) {
                timeoutNS = اگلا_repeat_wait_وقت;
                poll_alarm_سیٹ = true;
            }
        }
    }

    اگر (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        اگر (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - آغاز;
            آغاز = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        اگر (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            اگر (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        اگر (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            واپس errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        اگر (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - آغاز;
            آغاز = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        اگر (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            اگر (ret == 0) {
                واپس poll_alarm_سیٹ ? 1 : 0;
            } ورنہ {
                // Pump events on an interrupt or broken pipe to handle the error.
                واپس errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        اگر (ret == -1) {
            واپس ret;
        }
    }

    // Signal to the caller that there might be an event available.
    واپس 1;
}

خالی Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *d = _this->اندرونی_2;
    SDL_WaylandSeat *seat;
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحیح ret = 0;

#اگر_تعریف_شدہ SDL_USE_IME
    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
    اگر (!d->متن_داخلہ_manager && keyboard_focus && SDL_متن_داخلہ_فعال(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#اگر_ختم

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    اگر (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        اگر (ret < 0) {
            جاؤ connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    اگر (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        اگر (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_مقصد_NS(4));
            اگر (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        اگر (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            جاؤ connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        اگر (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            اگر (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ورنہ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ورنہ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    اگر (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            اگر (seat->keyboard.repeat.کلید) {
                Wayland_Seat_سیٹ_Keymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_وقت_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    اگر (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساکن خالی اشارہ_گر_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = seat->اشارہ_گر_2.focus;
    SDL_کھڑکی *کھڑکی = کھڑکی_ڈیٹا_2 ? کھڑکی_ڈیٹا_2->sdlwindow : تہی;

    اگر (کھڑکی_ڈیٹا_2) {
        دوہرا sx = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx);
        دوہرا sy = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy);

        اگر (seat->اشارہ_گر_2.focus_surface == کھڑکی_ڈیٹا_2->نقاب.surface) {
            sx += (دوہرا)کھڑکی_ڈیٹا_2->نقاب.انحراف_x;
            sy += (دوہرا)کھڑکی_ڈیٹا_2->نقاب.انحراف_y;
        }

        sx *= کھڑکی_ڈیٹا_2->اشارہ_گر_scale.x;
        sy *= کھڑکی_ڈیٹا_2->اشارہ_گر_scale.y;
        اگر (!warp) {
            SDL_SendMouseMotion(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی_ڈیٹا_2->sdlwindow, seat->اشارہ_گر_2.sdl_id, false, (اعشاری)sx, (اعشاری)sy);
        } ورنہ {
            SDL_SendMouseWarp(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی_ڈیٹا_2->sdlwindow, seat->اشارہ_گر_2.sdl_id, (اعشاری)sx, (اعشاری)sy);
        }

        seat->اشارہ_گر_2.آخری_motion.x = (صحیح)SDL_floor(sx);
        seat->اشارہ_گر_2.آخری_motion.y = (صحیح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        اگر (!SDL_Rect_خالی_خانے(&کھڑکی->mouse_rect) && !seat->اشارہ_گر_2.is_confined) {
            Wayland_Seat_Update_اشارہ_گر_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        اگر (!(کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE) && کھڑکی->کامیابی_test) {
            SDL_کامیابی_Test_نتیجہ rc = کھڑکی->کامیابی_test(کھڑکی, &seat->اشارہ_گر_2.آخری_motion, کھڑکی->کامیابی_test_ڈیٹا);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            انتخاب (rc) {
            حالت SDL_HITTEST_RESIZE_TOPLEFT:
                اگر ((کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) &&
                    (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں)) {
                    rc = SDL_HITTEST_معمول;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_RESIZE_بایاں;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_RESIZE_چوٹی;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_چوٹی:
                اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_معمول;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_TOPRIGHT:
                اگر ((کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) &&
                    (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں)) {
                    rc = SDL_HITTEST_معمول;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_RESIZE_دایاں;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_RESIZE_چوٹی;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_دایاں:
                اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_معمول;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                اگر ((کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں)) {
                    rc = SDL_HITTEST_معمول;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_دایاں;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_BOTTOM:
                اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_معمول;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
                اگر ((کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں)) {
                    rc = SDL_HITTEST_معمول;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_بایاں;
                } ورنہ اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                توڑو;
            حالت SDL_HITTEST_RESIZE_بایاں:
                اگر (کھڑکی_ڈیٹا_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_معمول;
                }
                توڑو;
            طےشدہ:
                توڑو;
            }

            اگر (rc != کھڑکی_ڈیٹا_2->کامیابی_test_نتیجہ) {
                کھڑکی_ڈیٹا_2->کامیابی_test_نتیجہ = rc;
                Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
            }
        }
    }
}

ساکن خالی اشارہ_گر_handle_motion(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                  uint32_t وقت, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);

    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = sx;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = sy;

    اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        اگر (!seat->اشارہ_گر_2.pending_چوکھٹا.have_relative || seat->اشارہ_گر_2.timestamps) {
            seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = timestamp;
        }
    } ورنہ {
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = timestamp;
        اشارہ_گر_dispatch_absolute_motion(seat, false);
    }
}

ساکن خالی اشارہ_گر_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface);
    اگر (!کھڑکی) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        واپس;
    }

    اگر (کھڑکی->surface != seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_سیٹ_Default_Cursor(seat);
        واپس;
    }

    seat->اشارہ_گر_2.focus = کھڑکی;
    seat->اشارہ_گر_2.focus_surface = seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface;
    ++کھڑکی->اشارہ_گر_focus_گنتی;
    SDL_سیٹ_Mouse_Focus(کھڑکی->sdlwindow);

    // Send the initial position.
    اشارہ_گر_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_اشارہ_گر_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
}

ساکن خالی اشارہ_گر_handle_enter(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                 uint32_t serial, ساخت wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    اگر (!surface) {
        // Enter event for a destroyed surface.
        واپس;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface = surface;
    seat->اشارہ_گر_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = sx_w;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = sy_w;

    اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = 0;
        اشارہ_گر_dispatch_enter(seat);
    }
}

ساکن خالی اشارہ_گر_dispatch_leave(SDL_WaylandSeat *seat, bool update_اشارہ_گر)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface);

    اگر (کھڑکی) {
        اگر (seat->اشارہ_گر_2.focus) {
            اگر (seat->اشارہ_گر_2.focus->surface == seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
                // Clear the capture flag and raise all buttons
                کھڑکی->sdlwindow->flags &= ~SDL_کھڑکی_MOUSE_CAPTURE;

                seat->اشارہ_گر_2.focus = تہی;
                seat->اشارہ_گر_2.focus_surface = تہی;
                برائے (Uint8 i = 1; seat->اشارہ_گر_2.buttons_pressed; ++i) {
                    اگر (seat->اشارہ_گر_2.buttons_pressed & SDL_BUTTON_نقاب(i)) {
                        SDL_SendMouseButton(0, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, i, false);
                        seat->اشارہ_گر_2.buttons_pressed &= ~SDL_BUTTON_نقاب(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_کھڑکی *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && کھڑکی->sdlwindow == mouse_focus;
                اگر (!--کھڑکی->اشارہ_گر_focus_گنتی && had_focus && !کھڑکی->فعال_touch_گنتی) {
                    SDL_سیٹ_Mouse_Focus(تہی);
                }

                اگر (update_اشارہ_گر) {
                    Wayland_Seat_Update_اشارہ_گر_Grab(seat);
                    Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
                }
            }
        } ورنہ اگر (update_اشارہ_گر) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساکن خالی اشارہ_گر_handle_leave(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                 uint32_t serial, ساخت wl_surface *surface)
{
    اگر (!surface) {
        // Leave event for a destroyed surface.
        واپس;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = surface;
    اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        اشارہ_گر_dispatch_leave(seat, true);
    }
}

ساکن bool Wayland_Process_کامیابی_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    اگر (seat->اشارہ_گر_2.locked_اشارہ_گر) {
        واپس false;
    }

    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = seat->اشارہ_گر_2.focus;
    SDL_کھڑکی *کھڑکی = کھڑکی_ڈیٹا_2->sdlwindow;

    اگر (کھڑکی->کامیابی_test) {
        ساکن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_کنارہ_چوٹی_بایاں, XDG_TOPLEVEL_RESIZE_کنارہ_چوٹی,
            XDG_TOPLEVEL_RESIZE_کنارہ_چوٹی_دایاں, XDG_TOPLEVEL_RESIZE_کنارہ_دایاں,
            XDG_TOPLEVEL_RESIZE_کنارہ_BOTTOM_دایاں, XDG_TOPLEVEL_RESIZE_کنارہ_BOTTOM,
            XDG_TOPLEVEL_RESIZE_کنارہ_BOTTOM_بایاں, XDG_TOPLEVEL_RESIZE_کنارہ_بایاں
        };

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
        ساکن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_کنارہ_چوٹی_بایاں, LIBDECOR_RESIZE_کنارہ_چوٹی,
            LIBDECOR_RESIZE_کنارہ_چوٹی_دایاں, LIBDECOR_RESIZE_کنارہ_دایاں,
            LIBDECOR_RESIZE_کنارہ_BOTTOM_دایاں, LIBDECOR_RESIZE_کنارہ_BOTTOM,
            LIBDECOR_RESIZE_کنارہ_BOTTOM_بایاں, LIBDECOR_RESIZE_کنارہ_بایاں
        };
#اگر_ختم

        انتخاب (کھڑکی_ڈیٹا_2->کامیابی_test_نتیجہ) {
        حالت SDL_HITTEST_DRAGGABLE:
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
            اگر (کھڑکی_ڈیٹا_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                اگر (کھڑکی_ڈیٹا_2->shell_surface.libdecor.چوکھٹا) {
                    libdecor_چوکھٹا_move(کھڑکی_ڈیٹا_2->shell_surface.libdecor.چوکھٹا,
                                        seat->wl_seat,
                                        serial);
                }
            } ورنہ
#اگر_ختم
                اگر (کھڑکی_ڈیٹا_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                اگر (کھڑکی_ڈیٹا_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(کھڑکی_ڈیٹا_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            واپس true;

        حالت SDL_HITTEST_RESIZE_TOPLEFT:
        حالت SDL_HITTEST_RESIZE_چوٹی:
        حالت SDL_HITTEST_RESIZE_TOPRIGHT:
        حالت SDL_HITTEST_RESIZE_دایاں:
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالت SDL_HITTEST_RESIZE_BOTTOM:
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالت SDL_HITTEST_RESIZE_بایاں:
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
            اگر (کھڑکی_ڈیٹا_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                اگر (کھڑکی_ڈیٹا_2->shell_surface.libdecor.چوکھٹا) {
                    libdecor_چوکھٹا_resize(کھڑکی_ڈیٹا_2->shell_surface.libdecor.چوکھٹا,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[کھڑکی_ڈیٹا_2->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ورنہ
#اگر_ختم
                اگر (کھڑکی_ڈیٹا_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                اگر (کھڑکی_ڈیٹا_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(کھڑکی_ڈیٹا_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[کھڑکی_ڈیٹا_2->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            واپس true;

        طےشدہ:
            واپس false;
        }
    }

    واپس false;
}

ساکن خالی اشارہ_گر_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool نیچے_کو)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = seat->اشارہ_گر_2.focus;

    اگر (کھڑکی) {
        bool ignore_click = false;

        اگر (نیچے_کو) {
            seat->اشارہ_گر_2.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);

            اگر (sdl_button == SDL_BUTTON_بایاں && Wayland_Process_کامیابی_Test(seat, seat->آخری_implicit_grab_serial)) {
                واپس; // don't pass this event on to app.
            }
        } ورنہ {
            seat->اشارہ_گر_2.buttons_pressed &= ~SDL_BUTTON_نقاب(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        اگر (کھڑکی->آخری_focus_event_وقت_ns) {
            اگر (نیچے_کو && (SDL_GetTicksNS() - کھڑکی->آخری_focus_event_وقت_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            کھڑکی->آخری_focus_event_وقت_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        اگر (!seat->اشارہ_گر_2.relative_اشارہ_گر) {
            اگر (seat->اشارہ_گر_2.buttons_pressed != 0) {
                کھڑکی->sdlwindow->flags |= SDL_کھڑکی_MOUSE_CAPTURE;
            } ورنہ {
                کھڑکی->sdlwindow->flags &= ~SDL_کھڑکی_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                اگر (seat->اشارہ_گر_2.focus_surface != کھڑکی->surface) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = کھڑکی->surface;
                }
            }
        }

        اگر (!ignore_click) {
            SDL_SendMouseButton(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, sdl_button, نیچے_کو);
        }
    }
}

ساکن خالی اشارہ_گر_handle_button(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2, uint32_t serial,
                                  uint32_t وقت, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    Uint8 sdl_button;

    انتخاب (button) {
    حالت BTN_بایاں:
        sdl_button = SDL_BUTTON_بایاں;
        توڑو;
    حالت BTN_درمیان:
        sdl_button = SDL_BUTTON_درمیان;
        توڑو;
    حالت BTN_دایاں:
        sdl_button = SDL_BUTTON_دایاں;
        توڑو;
    طےشدہ:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        توڑو;
    }

    اگر (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);

    اگر (wl_seat_get_نسخہ(seat->wl_seat) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        اگر (state_w) {
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);
        } ورنہ {
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released |= SDL_BUTTON_نقاب(sdl_button);
        }
    } ورنہ {
        اشارہ_گر_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساکن خالی اشارہ_گر_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t قدر)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = seat->اشارہ_گر_2.focus;
    ثابت شمار wl_اشارہ_گر_axis a = axis;

    اگر (seat->اشارہ_گر_2.focus) {
        اعشاری x, y;

        انتخاب (a) {
        حالت WL_اشارہ_گر_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (اعشاری)wl_fixed_مقصد_double(قدر);
            توڑو;
        حالت WL_اشارہ_گر_AXIS_HORIZONTAL_SCROLL:
            x = (اعشاری)wl_fixed_مقصد_double(قدر);
            y = 0;
            توڑو;
        طےشدہ:
            واپس;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y, SDL_MOUSEWHEEL_معمول);
    }
}

ساکن خالی اشارہ_گر_handle_axis_common(SDL_WaylandSeat *seat, شمار SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t قدر)
{
    ثابت شمار wl_اشارہ_گر_axis a = axis;

    اگر (seat->اشارہ_گر_2.focus) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_axis = true;

        انتخاب (a) {
        حالت WL_اشارہ_گر_AXIS_VERTICAL_SCROLL:
            انتخاب (type) {
            حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0.0f;
                }
                seat->اشارہ_گر_2.pending_چوکھٹا.axis.y += 0 - (اعشاری)wl_fixed_مقصد_double(قدر);
                توڑو;
            حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0 - (اعشاری)wl_fixed_مقصد_double(قدر);
                }
                توڑو;
            حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0 - (اعشاری)wl_fixed_مقصد_double(قدر);
                }
                توڑو;
            }
            توڑو;
        حالت WL_اشارہ_گر_AXIS_HORIZONTAL_SCROLL:
            انتخاب (type) {
            حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = 0.0f;
                }
                seat->اشارہ_گر_2.pending_چوکھٹا.axis.x += (اعشاری)wl_fixed_مقصد_double(قدر);
                توڑو;
            حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = (اعشاری)wl_fixed_مقصد_double(قدر);
                }
                توڑو;
            حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                اگر (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = (اعشاری)wl_fixed_مقصد_double(قدر);
                }
                توڑو;
            }
            توڑو;
        }
    }
}

ساکن خالی اشارہ_گر_handle_axis(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                uint32_t وقت, uint32_t axis, wl_fixed_t قدر)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    ثابت Uint64 nsTimestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, وقت);

    اگر (wl_seat_get_نسخہ(seat->wl_seat) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = nsTimestamp;
        اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, قدر);
    } ورنہ {
        اشارہ_گر_handle_axis_common_v1(seat, nsTimestamp, axis, قدر);
    }
}

ساکن خالی اشارہ_گر_handle_axis_relative_direction(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = ڈیٹا;

    انتخاب (axis_relative_direction) {
    حالت WL_اشارہ_گر_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction = SDL_MOUSEWHEEL_معمول;
        توڑو;
    حالت WL_اشارہ_گر_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        توڑو;
    }
}

ساکن خالی اشارہ_گر_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = seat->اشارہ_گر_2.focus;

    اگر (کھڑکی) {
        SDL_Mouse *mouse = SDL_GetMouse();
        دوہرا dx;
        دوہرا dy;
        اگر (mouse->داخلہ_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx_unaccel);
            dy = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy_unaccel);
        } ورنہ {
            dx = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx) * کھڑکی->اشارہ_گر_scale.x;
            dy = wl_fixed_مقصد_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy) * کھڑکی->اشارہ_گر_scale.y;
        }

        SDL_SendMouseMotion(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, true, (اعشاری)dx, (اعشاری)dy);
    }
}

ساکن خالی اشارہ_گر_dispatch_axis(SDL_WaylandSeat *seat)
{
    اعشاری x, y;
    SDL_MouseWheelDirection direction = seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction;

    انتخاب (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type) {
    حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        توڑو;
    حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x;
        توڑو;
    حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x / 120.0f;
        توڑو;
    طےشدہ:
        x = 0.0f;
        توڑو;
    }

    انتخاب (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type) {
    حالت SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        توڑو;
    حالت SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y;
        توڑو;
    حالت SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y / 120.0f;
        توڑو;
    طےشدہ:
        y = 0.0f;
        توڑو;
    }

    SDL_SendMouseWheel(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns,
                       seat->اشارہ_گر_2.focus->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y, direction);
}

ساکن خالی اشارہ_گر_handle_چوکھٹا(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2)
{
    SDL_WaylandSeat *seat = ڈیٹا;

    اگر (seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
        اگر (seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
            SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = seat->اشارہ_گر_2.focus;
            SDL_کھڑکی_ڈیٹا *new_focus = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface);

            اگر (کھڑکی_ڈیٹا_2 && (کھڑکی_ڈیٹا_2->sdlwindow->flags & SDL_کھڑکی_MOUSE_CAPTURE) && کھڑکی_ڈیٹا_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->اشارہ_گر_2.focus_surface = seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface;
                seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface = تہی;
                seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = تہی;
            } ورنہ {
                // Leaving the previous surface before entering a new surface.
                اشارہ_گر_dispatch_leave(seat, false);
                seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = تہی;
            }
        }

        اگر (seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
            اشارہ_گر_dispatch_enter(seat);
        }
    }

    اگر (seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute) {
        اشارہ_گر_dispatch_absolute_motion(seat, seat->اشارہ_گر_2.pending_چوکھٹا.have_warp);
    }

    اگر (seat->اشارہ_گر_2.pending_چوکھٹا.have_relative) {
        اشارہ_گر_dispatch_relative_motion(seat);
    }

    برائے (Uint8 i = 1; seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed || seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released; ++i) {
        ثابت Uint32 نقاب = SDL_BUTTON_نقاب(i);
        اگر (seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed & نقاب) {
            اشارہ_گر_dispatch_button(seat, i, true);
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed &= ~نقاب;
        }
        اگر (seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released & نقاب) {
            اشارہ_گر_dispatch_button(seat, i, false);
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released &= ~نقاب;
        }
    }

    اگر (seat->اشارہ_گر_2.pending_چوکھٹا.have_axis) {
        اشارہ_گر_dispatch_axis(seat);
    }

    اگر (seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
        اشارہ_گر_dispatch_leave(seat, true);
    }

    SDL_zero(seat->اشارہ_گر_2.pending_چوکھٹا);
}

ساکن خالی اشارہ_گر_handle_axis_ماخذ(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                       uint32_t axis_ماخذ)
{
    // unimplemented
}

ساکن خالی اشارہ_گر_handle_axis_stop(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                     uint32_t وقت, uint32_t axis)
{
    // unimplemented
}

ساکن خالی اشارہ_گر_handle_axis_discrete(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساکن خالی اشارہ_گر_handle_axis_value120(خالی *ڈیٹا, ساخت wl_اشارہ_گر *اشارہ_گر_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساکن خالی اشارہ_گر_handle_warp(خالی *ڈیٹا, ساخت wl_اشارہ_گر *wl_اشارہ_گر, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;

    seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute = true;
    seat->اشارہ_گر_2.pending_چوکھٹا.have_warp = true;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = surface_x;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = surface_y;
}

ساکن ثابت ساخت wl_اشارہ_گر_listener اشارہ_گر_listener = {
    اشارہ_گر_handle_enter,
    اشارہ_گر_handle_leave,
    اشارہ_گر_handle_motion,
    اشارہ_گر_handle_button,
    اشارہ_گر_handle_axis,
    اشارہ_گر_handle_چوکھٹا,                   // Version 5
    اشارہ_گر_handle_axis_ماخذ,             // Version 5
    اشارہ_گر_handle_axis_stop,               // Version 5
    اشارہ_گر_handle_axis_discrete,           // Version 5
    اشارہ_گر_handle_axis_value120,           // Version 8
    اشارہ_گر_handle_axis_relative_direction, // Version 9
    اشارہ_گر_handle_warp                     // Version 11
};

ساکن خالی relative_اشارہ_گر_handle_relative_motion(خالی *ڈیٹا,
                                                    ساخت zwp_relative_اشارہ_گر_v1 *اشارہ_گر_2,
                                                    uint32_t وقت_hi,
                                                    uint32_t وقت_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = ڈیٹا;

    // Relative pointer event times are in microsecond granularity.
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx = dx;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy = dy;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx_unaccel = dx_unaccel;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy_unaccel = dy_unaccel;
    seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = Wayland_Adjust_Event_Timestamp_بنیاد(SDL_US_مقصد_NS(((Uint64)وقت_hi << 32) | (Uint64)وقت_lo));

    اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_relative = true;
    } ورنہ {
        اشارہ_گر_dispatch_relative_motion(seat);
    }
}

ساکن ثابت ساخت zwp_relative_اشارہ_گر_v1_listener relative_اشارہ_گر_listener = {
    relative_اشارہ_گر_handle_relative_motion,
};

ساکن خالی locked_اشارہ_گر_locked(خالی *ڈیٹا, ساخت zwp_locked_اشارہ_گر_v1 *locked_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.is_confined = true;
}

ساکن خالی locked_اشارہ_گر_unlocked(خالی *ڈیٹا, ساخت zwp_locked_اشارہ_گر_v1 *locked_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.is_confined = false;
}

ساکن ثابت ساخت zwp_locked_اشارہ_گر_v1_listener locked_اشارہ_گر_listener = {
    locked_اشارہ_گر_locked,
    locked_اشارہ_گر_unlocked,
};

ساکن خالی confined_اشارہ_گر_confined(خالی *ڈیٹا, ساخت zwp_confined_اشارہ_گر_v1 *confined_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.is_confined = true;
}

ساکن خالی confined_اشارہ_گر_unconfined(خالی *ڈیٹا, ساخت zwp_confined_اشارہ_گر_v1 *confined_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->اشارہ_گر_2.is_confined = false;
}

ساکن ثابت ساخت zwp_confined_اشارہ_گر_v1_listener confined_اشارہ_گر_listener = {
    confined_اشارہ_گر_confined,
    confined_اشارہ_گر_unconfined,
};

ساکن خالی touch_handler_نیچے_کو(خالی *ڈیٹا, ساخت wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, ساخت wl_surface *surface,
                               صحیح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2;

    // Check that this surface is valid.
    اگر (!surface) {
        واپس;
    }

    Wayland_Seat_جوڑو_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    کھڑکی_ڈیٹا_2 = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);

    اگر (کھڑکی_ڈیٹا_2 && کھڑکی_ڈیٹا_2->surface == surface) {
        اعشاری x, y;

        اگر (کھڑکی_ڈیٹا_2->current.logical_چوڑائی <= 1) {
            x = 0.5f;
        } ورنہ {
            x = (اعشاری)wl_fixed_مقصد_double(fx) / (کھڑکی_ڈیٹا_2->current.logical_چوڑائی - 1);
        }
        اگر (کھڑکی_ڈیٹا_2->current.logical_اونچائی <= 1) {
            y = 0.5f;
        } ورنہ {
            y = (اعشاری)wl_fixed_مقصد_double(fy) / (کھڑکی_ڈیٹا_2->current.logical_اونچائی - 1);
        }

        ++کھڑکی_ڈیٹا_2->فعال_touch_گنتی;
        SDL_سیٹ_Mouse_Focus(کھڑکی_ڈیٹا_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), کھڑکی_ڈیٹا_2->sdlwindow, SDL_EVENT_FINGER_نیچے_کو, x, y, 1.0f);
    }
}

ساکن خالی touch_handler_اوپر(خالی *ڈیٹا, ساخت wl_touch *touch, uint32_t serial, uint32_t timestamp, صحیح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    wl_fixed_t fx = 0, fy = 0;
    ساخت wl_surface *surface = تہی;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    اگر (surface) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);

        اگر (کھڑکی_ڈیٹا_2 && کھڑکی_ڈیٹا_2->surface == surface) {
            ثابت اعشاری x = (اعشاری)wl_fixed_مقصد_double(fx) / کھڑکی_ڈیٹا_2->current.logical_چوڑائی;
            ثابت اعشاری y = (اعشاری)wl_fixed_مقصد_double(fy) / کھڑکی_ڈیٹا_2->current.logical_اونچائی;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), کھڑکی_ڈیٹا_2->sdlwindow, SDL_EVENT_FINGER_اوپر, x, y, 0.0f);

            --کھڑکی_ڈیٹا_2->فعال_touch_گنتی;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            اگر (SDL_GetMouseFocus() == کھڑکی_ڈیٹا_2->sdlwindow && !کھڑکی_ڈیٹا_2->keyboard_focus_گنتی &&
                !کھڑکی_ڈیٹا_2->اشارہ_گر_focus_گنتی && !کھڑکی_ڈیٹا_2->فعال_touch_گنتی) {
                SDL_سیٹ_Mouse_Focus(تہی);
            }
        }
    }
}

ساکن خالی touch_handler_motion(خالی *ڈیٹا, ساخت wl_touch *touch, uint32_t timestamp, صحیح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    ساخت wl_surface *surface = تہی;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    اگر (surface) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);

        اگر (کھڑکی_ڈیٹا_2 && کھڑکی_ڈیٹا_2->surface == surface) {
            ثابت اعشاری x = (اعشاری)wl_fixed_مقصد_double(fx) / کھڑکی_ڈیٹا_2->current.logical_چوڑائی;
            ثابت اعشاری y = (اعشاری)wl_fixed_مقصد_double(fy) / کھڑکی_ڈیٹا_2->current.logical_اونچائی;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), کھڑکی_ڈیٹا_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ساکن خالی touch_handler_چوکھٹا(خالی *ڈیٹا, ساخت wl_touch *touch)
{
}

ساکن خالی touch_handler_cancel(خالی *ڈیٹا, ساخت wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    SDL_Wayland_Touch_نقطہ *tp, *عارضی;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_محفوظ (tp, عارضی, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ساکن خالی touch_handler_shape(خالی *ڈیٹا, ساخت wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ساکن خالی touch_handler_orientation(خالی *ڈیٹا, ساخت wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ساکن ثابت ساخت wl_touch_listener touch_listener = {
    touch_handler_نیچے_کو,
    touch_handler_اوپر,
    touch_handler_motion,
    touch_handler_چوکھٹا,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#اگر !SDL_XKBCOMMON_CHECK_نسخہ(1, 0, 0)
ساکن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کلید, xkb_layout_اشاریہ_t layout, xkb_level_اشاریہ_t level, xkb_mod_نقاب_t *masks_برآمد, size_t masks_سائز)
{
    اگر (!masks_برآمد || !masks_سائز) {
        واپس 0;
    }

    // Level 0 is always unmodified, so early out.
    اگر (level == 0) {
        *masks_برآمد = 0;
        واپس 1;
    }

    size_t نقاب_idx = 0;
    ثابت xkb_mod_نقاب_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.سرکاؤ_نقاب,
        seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.سرکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.سرکاؤ_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.سرکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.سرکاؤ_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.سرکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2
    };
    ثابت xkb_mod_نقاب_t pressed_mod_نقاب = seat->keyboard.xkb.سرکاؤ_نقاب | seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.level5_نقاب;
    ثابت xkb_mod_نقاب_t locked_mod_نقاب = seat->keyboard.xkb.caps_نقاب_2;

    برائے (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_نقاب, 0, keymod_masks[i] & locked_mod_نقاب, 0, 0, layout);
        اگر (WAYLAND_xkb_state_کلید_get_level(seat->keyboard.xkb.state, کلید, layout) == level) {
            masks_برآمد[نقاب_idx] = keymod_masks[i];

            اگر (++نقاب_idx == masks_سائز) {
                توڑو;
            }
        }
    }

    واپس نقاب_idx;
}
#اگر_ختم

ساکن خالی Wayland_KeymapIterator(ساخت xkb_keymap *keymap, xkb_keycode_t کلید, خالی *ڈیٹا)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_نقاب_t xkb_valid_mod_نقاب = seat->keyboard.xkb.سرکاؤ_نقاب |
                                              seat->keyboard.xkb.alt_نقاب |
                                              seat->keyboard.xkb.level3_نقاب |
                                              seat->keyboard.xkb.level5_نقاب |
                                              seat->keyboard.xkb.caps_نقاب_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    اگر (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلید - 8);
    }

    برائے (xkb_layout_اشاریہ_t layout = 0; layout < seat->keyboard.xkb.عدد_layouts; ++layout) {
        ثابت xkb_level_اشاریہ_t عدد_سطحیں = WAYLAND_xkb_keymap_عدد_سطحیں_for_کلید(seat->keyboard.xkb.keymap, کلید, layout);
        برائے (xkb_level_اشاریہ_t level = 0; level < عدد_سطحیں; ++level) {
            اگر (WAYLAND_xkb_keymap_کلید_get_syms_by_level(seat->keyboard.xkb.keymap, کلید, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                اگر (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_کلید_Sym(syms[0], کلید);
                    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
                        جاری;
                    }
                }

                xkb_mod_نقاب_t xkb_mod_masks[16];
#اگر SDL_XKBCOMMON_CHECK_نسخہ(1, 0, 0)
                ثابت size_t عدد_masks = WAYLAND_xkb_keymap_کلید_get_mods_for_level(seat->keyboard.xkb.keymap, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ورنہ
                ثابت size_t عدد_masks = xkb_legacy_get_mods_for_level(seat, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#اگر_ختم
                برائے (size_t نقاب = 0; نقاب < عدد_masks; ++نقاب) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    اگر ((xkb_mod_masks[نقاب] | xkb_valid_mod_نقاب) != xkb_valid_mod_نقاب) {
                        جاری;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[نقاب] & seat->keyboard.xkb.سرکاؤ_نقاب ? SDL_KMOD_سرکاؤ : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level3_نقاب ? SDL_KMOD_منوال : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level5_نقاب ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.caps_نقاب_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کلید_رمز_From_کلید_Sym(syms[0], کلید, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    اگر (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_اگلا_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        اگر (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کلید *res = WAYLAND_wl_array_جوڑو(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_کلید));
                        اگر (res) {
                            res->scancode = scancode;
                            res->کلید = کلید - 8;
                        }
                    }

                    اگر (!keycode) {
                        انتخاب (scancode) {
                        حالت SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            توڑو;
                        حالت SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            توڑو;
                        حالت SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            توڑو;
                        حالت SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            توڑو;
                        طےشدہ:
                            keycode = SDL_SCANCODE_مقصد_KEYCODE(scancode);
                            توڑو;
                        }
                    }

                    SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساکن خالی keyboard_handle_keymap(خالی *ڈیٹا, ساخت wl_keyboard *keyboard,
                                   uint32_t format, صحیح fd, uint32_t سائز)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    حرف *map_str;

    اگر (!ڈیٹا) {
        close(fd);
        واپس;
    }

    اگر (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        واپس;
    }

    map_str = mmap(تہی, سائز, PROT_READ, MAP_PRIVATE, fd, 0);
    اگر (map_str == MAP_FAILED) {
        close(fd);
        واپس;
    }

    اگر (seat->keyboard.xkb.keymap != تہی) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = تہی;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_متن_V1,
                                                                   0);
    munmap(map_str, سائز);
    close(fd);

    اگر (!seat->keyboard.xkb.keymap) {
        SDL_سیٹ_Error("failed to compile keymap");
        واپس;
    }

    // Clear the old layouts.
    برائے (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = تہی;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.عدد_layouts = 0;

#اگر SDL_XKBCOMMON_CHECK_نسخہ(1, 10, 0)
    seat->keyboard.xkb.سرکاؤ_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_سرکاؤ);
    seat->keyboard.xkb.ctrl_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.عدد_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_عدد);
    seat->keyboard.xkb.caps_نقاب_2 = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ورنہ
#تعریف_کرو GET_MOD_اشاریہ(mod) \
    WAYLAND_xkb_keymap_mod_get_اشاریہ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.سرکاؤ_نقاب = 1 << GET_MOD_اشاریہ(سرکاؤ_2);
    seat->keyboard.xkb.ctrl_نقاب = 1 << GET_MOD_اشاریہ(CTRL);
    seat->keyboard.xkb.alt_نقاب = 1 << GET_MOD_اشاریہ(ALT);
    seat->keyboard.xkb.gui_نقاب = 1 << GET_MOD_اشاریہ(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_نقاب = 1 << GET_MOD_اشاریہ(MOD5);
    seat->keyboard.xkb.level5_نقاب = 1 << GET_MOD_اشاریہ(MOD3);
    seat->keyboard.xkb.عدد_نقاب = 1 << GET_MOD_اشاریہ(عدد_2);
    seat->keyboard.xkb.caps_نقاب_2 = 1 << GET_MOD_اشاریہ(CAPS);
#تعریف_منسوخ GET_MOD_اشاریہ
#اگر_ختم

    اگر (seat->keyboard.xkb.state != تہی) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = تہی;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    اگر (!seat->keyboard.xkb.state) {
        SDL_سیٹ_Error("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = تہی;
        واپس;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == تہی;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.عدد_layouts = WAYLAND_xkb_keymap_عدد_layouts(seat->keyboard.xkb.keymap);
    اگر (seat->keyboard.xkb.عدد_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.عدد_layouts, حجم(SDL_Keymap *));
        اگر (!seat->keyboard.sdl_keymap) {
            واپس;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        برائے (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            اگر (!seat->keyboard.sdl_keymap[i]) {
                برائے (xkb_layout_اشاریہ_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = تہی;
                واپس;
            }
        }

        WAYLAND_xkb_keymap_کلید_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_سیٹ_Keymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ثابت حرف *locale = SDL_getenv("LC_ALL");
    اگر (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        اگر (!locale) {
            locale = SDL_getenv("LANG");
            اگر (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    اگر (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        اگر (seat->keyboard.xkb.compose_جدول != تہی) {
            WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
            seat->keyboard.xkb.compose_جدول = تہی;
        }
        seat->keyboard.xkb.compose_جدول = WAYLAND_xkb_compose_جدول_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        اگر (seat->keyboard.xkb.compose_جدول) {
            // Set up XKB compose state
            اگر (seat->keyboard.xkb.compose_state != تہی) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = تہی;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_جدول,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            اگر (!seat->keyboard.xkb.compose_state) {
                SDL_سیٹ_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
                seat->keyboard.xkb.compose_جدول = تہی;
            }
        }
    } ورنہ اگر (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ساکن SDL_Scancode Wayland_Get_Scancode_For_کلید(SDL_WaylandSeat *seat, Uint32 کلید, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    اگر (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلید);

        // No table entry? Check the reserved list.
        اگر (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_کلید *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                اگر (i->کلید == کلید) {
                    واپس i->scancode;
                }
            }
        }
    } ورنہ {
        ثابت xkb_keysym_t *keysym;
        اگر (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_کلید_Sym(keysym[0], کلید + 8);
            اگر (syms) {
                *syms = keysym;
            }
        }
    }

    واپس scancode;
}

ساکن خالی Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    اگر (!کلید_pressed) {
        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.سرکاؤ_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_سرکاؤ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_سرکاؤ;
            }
        } ورنہ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_سرکاؤ;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ورنہ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ورنہ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ورنہ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_منوال)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_منوال;
            }
        } ورنہ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_منوال;
        }

        اگر (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_نقاب) {
            اگر (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ورنہ {
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
    ثابت xkb_mod_نقاب_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.سرکاؤ_نقاب) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_سرکاؤ) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_سرکاؤ;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_سرکاؤ);
        } ورنہ اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_سرکاؤ)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_سرکاؤ;
        }
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_سرکاؤ;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_نقاب) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ورنہ اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.alt_نقاب) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ورنہ اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.gui_نقاب) {
        اگر (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ورنہ اگر (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.level3_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_منوال;
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_منوال;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.level5_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    اگر (xkb_locked_modifiers & seat->keyboard.xkb.caps_نقاب_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    اگر (xkb_locked_modifiers & seat->keyboard.xkb.عدد_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_عدد;
    } ورنہ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_عدد;
    }

    SDL_سیٹ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساکن خالی Wayland_Handle_Modifier_کلیدیں(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    انتخاب (keycode) {
    حالت SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        توڑو;
    حالت SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        توڑو;
    حالت SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        توڑو;
    حالت SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        توڑو;
    حالت SDLK_LALT:
        mod = SDL_KMOD_LALT;
        توڑو;
    حالت SDLK_RALT:
        mod = SDL_KMOD_RALT;
        توڑو;
    حالت SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        توڑو;
    حالت SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        توڑو;
    حالت SDLK_منوال:
        mod = SDL_KMOD_منوال;
        توڑو;
    حالت SDLK_LEVEL5_سرکاؤ:
        mod = SDL_KMOD_LEVEL5;
        توڑو;
    طےشدہ:
        واپس;
    }

    اگر (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ورنہ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ساکن خالی keyboard_handle_enter(خالی *ڈیٹا, ساخت wl_keyboard *keyboard,
                                  uint32_t serial, ساخت wl_surface *surface,
                                  ساخت wl_array *کلیدیں)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    uint32_t *کلید;

    اگر (!surface) {
        // Enter event for a destroyed surface.
        واپس;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_کھڑکی_ڈیٹا *کھڑکی = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);
    اگر (!کھڑکی) {
        // Not a surface owned by SDL.
        واپس;
    }

    ++کھڑکی->keyboard_focus_گنتی;
    seat->keyboard.focus = کھڑکی;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_سیٹ_Keyboard_Focus(کھڑکی->sdlwindow->keyboard_focus ? کھڑکی->sdlwindow->keyboard_focus : کھڑکی->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشارہ_گر_Grabs(seat->display, کھڑکی);

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_داخلہ(seat);

#اگر_تعریف_شدہ SDL_USE_IME
    اگر (!seat->متن_داخلہ.zwp_متن_داخلہ) {
        SDL_IME_سیٹ_Focus(true);
    }
#اگر_ختم

    Uint64 timestamp = SDL_GetTicksNS();
    کھڑکی->آخری_focus_event_وقت_ns = timestamp;

    Wayland_Seat_سیٹ_Keymap(seat);

    wl_array_for_each (کلید, کلیدیں) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, *کلید, تہی);
        اگر (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false);

            انتخاب (keycode) {
            حالت SDLK_LSHIFT:
            حالت SDLK_RSHIFT:
            حالت SDLK_LCTRL:
            حالت SDLK_RCTRL:
            حالت SDLK_LALT:
            حالت SDLK_RALT:
            حالت SDLK_LGUI:
            حالت SDLK_RGUI:
            حالت SDLK_منوال:
            حالت SDLK_LEVEL5_سرکاؤ:
                Wayland_Handle_Modifier_کلیدیں(seat, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کلید, scancode, true);
                توڑو;
            طےشدہ:
                توڑو;
            }
        }
    }
}

ساکن خالی keyboard_handle_leave(خالی *ڈیٹا, ساخت wl_keyboard *keyboard,
                                  uint32_t serial, ساخت wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;

    اگر (!surface) {
        // Leave event for a destroyed surface.
        واپس;
    }

    SDL_کھڑکی_ڈیٹا *کھڑکی = Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface);
    اگر (!کھڑکی) {
        // Not a surface owned by SDL.
        واپس;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کلید = 0;

    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    جب (keyboard_focus && SDL_کھڑکی_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->والد;
    }

    ثابت bool had_focus = keyboard_focus && کھڑکی->sdlwindow == keyboard_focus;
    seat->keyboard.focus = تہی;
    --کھڑکی->keyboard_focus_گنتی;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    اگر (!کھڑکی->keyboard_focus_گنتی && had_focus) {
        SDL_سیٹ_Keyboard_Focus(تہی);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشارہ_گر_Grabs(seat->display, کھڑکی);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_داخلہ(seat);

#اگر_تعریف_شدہ SDL_USE_IME
    اگر (!seat->متن_داخلہ.zwp_متن_داخلہ && !کھڑکی->keyboard_focus_گنتی) {
        SDL_IME_سیٹ_Focus(false);
    }
#اگر_ختم

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    اگر (SDL_GetMouseFocus() == کھڑکی->sdlwindow && !کھڑکی->اشارہ_گر_focus_گنتی && !کھڑکی->فعال_touch_گنتی) {
        SDL_سیٹ_Mouse_Focus(تہی);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_ڈیٹا_Device_سیٹ_Selection_Offer(seat->ڈیٹا_device, تہی);
}

ساکن bool keyboard_داخلہ_get_متن(حرف متن[8], ثابت SDL_WaylandSeat *seat, uint32_t کلید, bool نیچے_کو, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    اگر (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        واپس false;
    }

    // TODO: Can this happen?
    اگر (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &syms) != 1) {
        واپس false;
    }
    sym = syms[0];

#اگر_تعریف_شدہ SDL_USE_IME
    اگر (SDL_IME_Process_کلید_Event(sym, کلید + 8, نیچے_کو)) {
        اگر (handled_by_ime) {
            *handled_by_ime = true;
        }
        واپس true;
    }
#اگر_ختم

    اگر (!نیچے_کو) {
        واپس false;
    }

    اگر (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        انتخاب (WAYLAND_xkb_compose_state_get_حالت(seat->keyboard.xkb.compose_state)) {
        حالت XKB_COMPOSE_COMPOSING:
            اگر (handled_by_ime) {
                *handled_by_ime = true;
            }
            واپس true;
        حالت XKB_COMPOSE_CANCELLED:
        طےشدہ:
            sym = XKB_کلید_No_علامت;
            توڑو;
        حالت XKB_COMPOSE_NOTHING:
            توڑو;
        حالت XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            توڑو;
        }
    }

    واپس WAYLAND_xkb_keysym_مقصد_utf8(sym, متن, 8) > 0;
}

ساکن خالی keyboard_handle_کلید(خالی *ڈیٹا, ساخت wl_keyboard *keyboard,
                                uint32_t serial, uint32_t وقت, uint32_t کلید,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    شمار wl_keyboard_کلید_state state = state_w;
    حرف متن[8];
    bool has_متن = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, وقت);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    اگر (state == WL_KEYBOARD_کلید_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        اگر (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            واپس;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کلید_STATE_PRESSED;
    }

    Wayland_Seat_سیٹ_Keymap(seat);

    اگر (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
        اگر (keyboard_focus && SDL_متن_داخلہ_فعال(keyboard_focus)) {
            has_متن = keyboard_داخلہ_get_متن(متن, seat, کلید, true, &handled_by_ime);
        }
    } ورنہ {
        اگر (کلید == seat->keyboard.repeat.کلید) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_مقصد_NS(وقت - seat->keyboard.repeat.wl_press_وقت_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کلید = 0;
        }
        keyboard_داخلہ_get_متن(متن, seat, کلید, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = تہی;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, کلید, &syms);
    Wayland_Handle_Modifier_کلیدیں(seat, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    اگر (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کلید_Sym_مقصد_Ucs4(syms[0]);
        اگر (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            اگر (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_نقاب) {
                scancode = SDL_Get_Keymap_اگلا_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, کلید, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    اگر (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        اگر (handled_by_ime) {
            has_متن = false;
        }
        اگر (has_متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(متن);
        }
        اگر (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            keyboard_repeat_سیٹ(&seat->keyboard.repeat, seat->keyboard.sdl_id, کلید, وقت, timestamp_ns, scancode, has_متن ? متن : تہی);
        }
    }
}

ساکن خالی keyboard_handle_modifiers(خالی *ڈیٹا, ساخت wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t گروہ)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    ثابت uint32_t پچھلا_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = گروہ;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    اگر (!seat->keyboard.xkb.state) {
        واپس;
    }

    WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, گروہ);

    // If a key is repeating, update the text to apply the modifier.
    اگر (seat->keyboard.repeat.کلید) {
        حرف متن[8];

        اگر (keyboard_داخلہ_get_متن(متن, seat, seat->keyboard.repeat.کلید, true, تہی)) {
            SDL_strlcpy(seat->keyboard.repeat.متن, متن, SDL_arraysize(seat->keyboard.repeat.متن));
        }
    }

    اگر (گروہ != پچھلا_layout) {
        Wayland_Seat_سیٹ_Keymap(seat);

        اگر (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ساکن خالی keyboard_handle_repeat_info(خالی *ڈیٹا, ساخت wl_keyboard *wl_keyboard,
                                        int32_t شرح, int32_t delay)
{
    SDL_WaylandSeat *seat = ڈیٹا;
    seat->keyboard.repeat.repeat_شرح = شرح;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    اگر (!شرح) {
        seat->keyboard.repeat.کلید = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ساکن ثابت ساخت wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_کلید,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ساکن خالی Wayland_Seat_Destroy_اشارہ_گر(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->اشارہ_گر_2.cursor_state);

    // End any active gestures.
    اگر (seat->اشارہ_گر_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_انتہا, 0, seat->اشارہ_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    اگر (seat->اشارہ_گر_2.focus) {
        seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = seat->اشارہ_گر_2.focus->surface;
        اشارہ_گر_dispatch_leave(seat, false);
        seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = تہی;
    }

    SDL_RemoveMouse(seat->اشارہ_گر_2.sdl_id);

    اگر (seat->اشارہ_گر_2.confined_اشارہ_گر) {
        zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
    }

    اگر (seat->اشارہ_گر_2.locked_اشارہ_گر) {
        zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
    }

    اگر (seat->اشارہ_گر_2.relative_اشارہ_گر) {
        zwp_relative_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.relative_اشارہ_گر);
    }

    اگر (seat->اشارہ_گر_2.timestamps) {
        zwp_داخلہ_timestamps_v1_destroy(seat->اشارہ_گر_2.timestamps);
    }

    اگر (seat->اشارہ_گر_2.gesture_pinch) {
        zwp_اشارہ_گر_gesture_pinch_v1_destroy(seat->اشارہ_گر_2.gesture_pinch);
    }

    اگر (seat->اشارہ_گر_2.wl_اشارہ_گر) {
        اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_RELEASE_SINCE_نسخہ) {
            wl_اشارہ_گر_release(seat->اشارہ_گر_2.wl_اشارہ_گر);
        } ورنہ {
            wl_اشارہ_گر_destroy(seat->اشارہ_گر_2.wl_اشارہ_گر);
        }
    }

    SDL_zero(seat->اشارہ_گر_2);
}

ساکن خالی Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    اگر (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    اگر (seat->keyboard.sdl_keymap) {
        اگر (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_سیٹ_Mod_State(SDL_KMOD_NONE);
        }
        برائے (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = تہی;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    اگر (seat->keyboard.کلید_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
    }

    اگر (seat->keyboard.timestamps) {
        zwp_داخلہ_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    اگر (seat->keyboard.wl_keyboard) {
        اگر (wl_keyboard_get_نسخہ(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_نسخہ) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ورنہ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    اگر (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    اگر (seat->keyboard.xkb.compose_جدول) {
        WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
    }

    اگر (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    اگر (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ساکن خالی Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    اگر (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    اگر (seat->touch.timestamps) {
        zwp_داخلہ_timestamps_v1_destroy(seat->touch.timestamps);
    }

    اگر (seat->touch.wl_touch) {
        اگر (wl_touch_get_نسخہ(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_نسخہ) {
            wl_touch_release(seat->touch.wl_touch);
        } ورنہ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ساکن خالی seat_handle_capabilities(خالی *ڈیٹا, ساخت wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    حرف name_fmt[256];

    اگر ((capabilities & WL_SEAT_CAPABILITY_اشارہ_گر) && !seat->اشارہ_گر_2.wl_اشارہ_گر) {
        seat->اشارہ_گر_2.wl_اشارہ_گر = wl_seat_get_اشارہ_گر(wl_seat);
        SDL_zero(seat->اشارہ_گر_2.pending_چوکھٹا.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_اشارہ_گر_سیٹ_user_ڈیٹا(seat->اشارہ_گر_2.wl_اشارہ_گر, seat);
        wl_اشارہ_گر_جوڑو_listener(seat->اشارہ_گر_2.wl_اشارہ_گر, &اشارہ_گر_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_اشارہ_گر_Gestures(seat);

        seat->اشارہ_گر_2.sdl_id = SDL_Get_اگلا_Object_ID();

        اگر (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_اشارہ_گر_NAME, seat->name);
        } ورنہ {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_اشارہ_گر_NAME, seat->اشارہ_گر_2.sdl_id);
        }

        SDL_جوڑو_Mouse(seat->اشارہ_گر_2.sdl_id, name_fmt);
    } ورنہ اگر (!(capabilities & WL_SEAT_CAPABILITY_اشارہ_گر) && seat->اشارہ_گر_2.wl_اشارہ_گر) {
        Wayland_Seat_Destroy_اشارہ_گر(seat);
    }

    اگر ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_سیٹ_user_ڈیٹا(seat->touch.wl_touch, seat);
        wl_touch_جوڑو_listener(seat->touch.wl_touch, &touch_listener, seat);

        اگر (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ورنہ {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_جوڑو_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_براہ_راست, name_fmt);
    } ورنہ اگر (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    اگر ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_سیٹ_user_ڈیٹا(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_جوڑو_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_اگلا_Object_ID();

        اگر (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ورنہ {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_جوڑو_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } ورنہ اگر (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(seat);
}

ساکن خالی seat_handle_name(خالی *ڈیٹا, ساخت wl_seat *wl_seat, ثابت حرف *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;

    اگر (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ساکن ثابت ساخت wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ساکن خالی ڈیٹا_offer_handle_offer(خالی *ڈیٹا, ساخت wl_ڈیٹا_offer *wl_ڈیٹا_offer,
                                    ثابت حرف *mime_type)
{
    SDL_Wayland_ڈیٹا_Offer *offer = ڈیٹا;
    Wayland_ڈیٹا_Offer_جوڑو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_ڈیٹا_offer ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)wl_ڈیٹا_offer) : -1),
                 mime_type);
}

ساکن خالی ڈیٹا_offer_handle_ماخذ_actions(خالی *ڈیٹا, ساخت wl_ڈیٹا_offer *wl_ڈیٹا_offer,
                                             uint32_t ماخذ_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_ڈیٹا_offer ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)wl_ڈیٹا_offer) : -1),
                 ماخذ_actions);
}

ساکن خالی ڈیٹا_offer_handle_actions(خالی *ڈیٹا, ساخت wl_ڈیٹا_offer *wl_ڈیٹا_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_ڈیٹا_offer ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)wl_ڈیٹا_offer) : -1),
                 dnd_action);
}

ساکن ثابت ساخت wl_ڈیٹا_offer_listener ڈیٹا_offer_listener = {
    ڈیٹا_offer_handle_offer,
    ڈیٹا_offer_handle_ماخذ_actions, // Version 3
    ڈیٹا_offer_handle_actions,        // Version 3
};

ساکن خالی primary_selection_offer_handle_offer(خالی *ڈیٹا, ساخت zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = ڈیٹا;
    Wayland_Primary_Selection_Offer_جوڑو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ساکن ثابت ساخت zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ساکن خالی ڈیٹا_device_handle_ڈیٹا_offer(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device,
                                          ساخت wl_ڈیٹا_offer *id)
{
    SDL_Wayland_ڈیٹا_Offer *ڈیٹا_offer = SDL_calloc(1, حجم(*ڈیٹا_offer));
    اگر (ڈیٹا_offer) {
        SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = (SDL_Wayland_ڈیٹا_Device *)ڈیٹا;
        ڈیٹا_offer->offer = id;
        ڈیٹا_offer->ڈیٹا_device = ڈیٹا_device;
        ڈیٹا_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(ڈیٹا_offer->mimes));
        wl_ڈیٹا_offer_سیٹ_user_ڈیٹا(id, ڈیٹا_offer);
        wl_ڈیٹا_offer_جوڑو_listener(id, &ڈیٹا_offer_listener, ڈیٹا_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id) : -1));
    }
}

ساکن خالی ڈیٹا_device_handle_enter(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device,
                                     uint32_t serial, ساخت wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, ساخت wl_ڈیٹا_offer *id)
{
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ڈیٹا;
    SDL_کھڑکی_ڈیٹا *کھڑکی = surface ? Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface) : تہی;
    ڈیٹا_device->has_mime_file = false;
    ڈیٹا_device->متن_mime_type = تہی;

    ڈیٹا_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    اگر (id) {
        ڈیٹا_device->drag_offer = wl_ڈیٹا_offer_get_user_ڈیٹا(id);
    }

    اگر (ڈیٹا_device->drag_offer && کھڑکی && کھڑکی->قبول_کرتا_drag_and_drop) {
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
        اگر (Wayland_ڈیٹا_Offer_Has_MIME(ڈیٹا_device->drag_offer, FILE_PORTAL_MIME)) {
            ڈیٹا_device->has_mime_file = true;
            wl_ڈیٹا_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#اگر_ختم
        اگر (Wayland_ڈیٹا_Offer_Has_MIME(ڈیٹا_device->drag_offer, FILE_MIME)) {
            ڈیٹا_device->has_mime_file = true;
            wl_ڈیٹا_offer_accept(id, serial, FILE_MIME);
        }

        اگر (!ڈیٹا_device->has_mime_file) {
            size_t mime_گنتی = 0;
            ثابت حرف *ثابت *متن_mime_types = Wayland_Get_متن_Mime_Types(SDL_GetVideoDevice(), &mime_گنتی);
            برائے (size_t i = 0; i < mime_گنتی; ++i) {
                اگر (Wayland_ڈیٹا_Offer_Has_MIME(ڈیٹا_device->drag_offer, متن_mime_types[i])) {
                    ڈیٹا_device->متن_mime_type = متن_mime_types[i];
                    wl_ڈیٹا_offer_accept(id, serial, متن_mime_types[i]);
                    توڑو;
                }
            }
        }

        اگر (ڈیٹا_device->has_mime_file || ڈیٹا_device->متن_mime_type) {
            // SDL only supports "copy" style drag and drop
            اگر (wl_ڈیٹا_offer_get_نسخہ(ڈیٹا_device->drag_offer->offer) >= WL_ڈیٹا_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_ڈیٹا_offer_سیٹ_actions(ڈیٹا_device->drag_offer->offer, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_COPY, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            ڈیٹا_device->dnd_کھڑکی = کھڑکی->sdlwindow;
            ڈیٹا_device->dnd_surface = surface;
            دوہرا dx = wl_fixed_مقصد_double(x);
            دوہرا dy = wl_fixed_مقصد_double(y);

            // If over the mask, adjust the offset.
            اگر (surface == کھڑکی->نقاب.surface) {
                dx += (دوہرا)کھڑکی->نقاب.انحراف_x;
                dy += (دوہرا)کھڑکی->نقاب.انحراف_y;
            }

            dx *= کھڑکی->اشارہ_گر_scale.x;
            dy *= کھڑکی->اشارہ_گر_scale.y;

            SDL_SendDropPosition(ڈیٹا_device->dnd_کھڑکی, (اعشاری)dx, (اعشاری)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id),
                         wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), SDL_Get_کھڑکی_ID(ڈیٹا_device->dnd_کھڑکی), serial);
        } ورنہ {
            // Decline the offer.
            wl_ڈیٹا_offer_accept(id, serial, تہی);
            اگر (wl_ڈیٹا_offer_get_نسخہ(ڈیٹا_device->drag_offer->offer) >= WL_ڈیٹا_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_ڈیٹا_offer_سیٹ_actions(ڈیٹا_device->drag_offer->offer, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_NONE, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id), wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), serial);
        }
    } ورنہ {
        ڈیٹا_device->dnd_کھڑکی = تہی;
        ڈیٹا_device->dnd_surface = تہی;

        // Decline the offer.
        اگر (id) {
            wl_ڈیٹا_offer_accept(id, serial, تہی);
            اگر (wl_ڈیٹا_offer_get_نسخہ(ڈیٹا_device->drag_offer->offer) >= WL_ڈیٹا_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_ڈیٹا_offer_سیٹ_actions(ڈیٹا_device->drag_offer->offer, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_NONE, WL_ڈیٹا_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id) : -1,
                     wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), serial);
    }
}

ساکن خالی ڈیٹا_device_handle_leave(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device)
{
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ڈیٹا;

    اگر (ڈیٹا_device->drag_offer) {
        اگر (ڈیٹا_device->dnd_کھڑکی) {
            SDL_SendDropComplete(ڈیٹا_device->dnd_کھڑکی);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)ڈیٹا_device->drag_offer->offer),
                         SDL_Get_کھڑکی_ID(ڈیٹا_device->dnd_کھڑکی), ڈیٹا_device->drag_serial);
        } ورنہ {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)ڈیٹا_device->drag_offer->offer),
                         ڈیٹا_device->drag_serial);
        }
        Wayland_ڈیٹا_Offer_Destroy(ڈیٹا_device->drag_offer);
        ڈیٹا_device->drag_offer = تہی;
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    ڈیٹا_device->has_mime_file = false;
    ڈیٹا_device->متن_mime_type = تہی;
}

ساکن خالی ڈیٹا_device_handle_motion(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device,
                                      uint32_t وقت, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ڈیٹا;

    اگر (ڈیٹا_device->drag_offer && ڈیٹا_device->dnd_کھڑکی && (ڈیٹا_device->has_mime_file || ڈیٹا_device->متن_mime_type)) {
        SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = ڈیٹا_device->dnd_کھڑکی->اندرونی_2;
        دوہرا dx = wl_fixed_مقصد_double(x);
        دوہرا dy = wl_fixed_مقصد_double(y);

        // If over the mask, adjust the offset.
        اگر (ڈیٹا_device->dnd_surface == کھڑکی_ڈیٹا_2->نقاب.surface) {
            dx += (دوہرا)کھڑکی_ڈیٹا_2->نقاب.انحراف_x;
            dy += (دوہرا)کھڑکی_ڈیٹا_2->نقاب.انحراف_y;
        }

        dx *= کھڑکی_ڈیٹا_2->اشارہ_گر_scale.x;
        dy *= کھڑکی_ڈیٹا_2->اشارہ_گر_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(ڈیٹا_device->dnd_کھڑکی, (اعشاری)dx, (اعشاری)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)ڈیٹا_device->drag_offer->offer),
                     wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y),
                     SDL_Get_کھڑکی_ID(ڈیٹا_device->dnd_کھڑکی), ڈیٹا_device->drag_serial);
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), -1);
    }
}

ساکن خالی drop_cleanup_handler(خالی *ڈیٹا, ساخت wl_callback *callback, uint32_t callback_ڈیٹا)
{
    Wayland_Drop_ڈیٹا *drop = (Wayland_Drop_ڈیٹا *)ڈیٹا;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ساکن ثابت ساخت wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ساکن خالی drop_dispatch_handler(خالی *ڈیٹا)
{
    Wayland_Drop_ڈیٹا *drop = (Wayland_Drop_ڈیٹا *)ڈیٹا;
    SDL_Wayland_ڈیٹا_Offer *offer = drop->offer;
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = offer->ڈیٹا_device;

    اگر (drop->dnd_کھڑکی) {
        size_t لمبائی;
        bool drop_handled = false;

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
        اگر (Wayland_ڈیٹا_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            خالی *بفر_2 = Wayland_ڈیٹا_Offer_Receive(offer, FILE_PORTAL_MIME, &لمبائی);
            اگر (بفر_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                اگر (dbus) {
                    صحیح راستہ_گنتی = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(بفر_2, &راستہ_گنتی);
                    // If dropped files contain a directory the list is empty
                    اگر (paths && راستہ_گنتی > 0) {
                        برائے (صحیح i = 0; i < راستہ_گنتی; i++) {
                            SDL_SendDropFile(drop->dnd_کھڑکی, تہی, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(بفر_2);
            }
        }
#اگر_ختم
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        اگر (!drop_handled) {
            اگر (Wayland_ڈیٹا_Offer_Has_MIME(offer, FILE_MIME)) {
                خالی *بفر_2 = Wayland_ڈیٹا_Offer_Receive(offer, FILE_MIME, &لمبائی);
                اگر (بفر_2) {
                    حرف *saveptr = تہی;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    جب (token) {
                        اگر (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_کھڑکی, تہی, token);
                        }
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            } ورنہ اگر (Wayland_ڈیٹا_Offer_Has_MIME(offer, drop->متن_mime_type)) {
                خالی *بفر_2 = Wayland_ڈیٹا_Offer_Receive(offer, drop->متن_mime_type, &لمبائی);
                اگر (بفر_2) {
                    حرف *saveptr = تہی;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    جب (token) {
                        SDL_Send_Drop_متن(drop->dnd_کھڑکی, token);
                        token = SDL_strtok_r(تہی, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            }
        }

        اگر (drop_handled && wl_ڈیٹا_offer_get_نسخہ(offer->offer) >= WL_ڈیٹا_OFFER_اختتام_SINCE_نسخہ) {
            wl_ڈیٹا_offer_اختتام(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_کھڑکی);
    }

    Wayland_ڈیٹا_Offer_Destroy(drop->offer);
    drop->offer = تہی;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(ڈیٹا_device->seat->display->display);
    wl_callback_جوڑو_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساکن خالی ڈیٹا_device_handle_drop(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device)
{
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ڈیٹا;

    اگر (ڈیٹا_device->drag_offer && ڈیٹا_device->dnd_کھڑکی &&
        (ڈیٹا_device->has_mime_file || ڈیٹا_device->متن_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)ڈیٹا_device->drag_offer->offer),
                     SDL_Get_کھڑکی_ID(ڈیٹا_device->dnd_کھڑکی), ڈیٹا_device->drag_serial);

        Wayland_کام_Thread_Context *ctx = ڈیٹا_device->seat->display->کام_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_ڈیٹا *drop = SDL_calloc(1, حجم(Wayland_Drop_ڈیٹا));
        اگر (drop) {
            drop->offer = ڈیٹا_device->drag_offer;
            drop->dnd_کھڑکی = ڈیٹا_device->dnd_کھڑکی;
            drop->متن_mime_type = ڈیٹا_device->متن_mime_type;

            WAYLAND_wl_list_داخل_کرو(&ڈیٹا_device->pending_drops, &drop->link);
            Wayland_کام_Thread_جوڑو_کام(ctx, drop_dispatch_handler, drop, &drop->id);
        } ورنہ {
            Wayland_ڈیٹا_Offer_Destroy(ڈیٹا_device->drag_offer);
        }
    } ورنہ {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_ڈیٹا_Offer_Destroy(ڈیٹا_device->drag_offer);
    }

    ڈیٹا_device->drag_offer = تہی;
}

ساکن خالی ڈیٹا_device_handle_selection(خالی *ڈیٹا, ساخت wl_ڈیٹا_device *wl_ڈیٹا_device,
                                         ساخت wl_ڈیٹا_offer *id)
{
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ڈیٹا;
    SDL_Wayland_ڈیٹا_Offer *offer = تہی;

    اگر (id) {
        offer = wl_ڈیٹا_offer_get_user_ڈیٹا(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id) : -1));

    Wayland_ڈیٹا_Device_سیٹ_Selection_Offer(ڈیٹا_device, offer);
}

ساکن ثابت ساخت wl_ڈیٹا_device_listener ڈیٹا_device_listener = {
    ڈیٹا_device_handle_ڈیٹا_offer,
    ڈیٹا_device_handle_enter,
    ڈیٹا_device_handle_leave,
    ڈیٹا_device_handle_motion,
    ڈیٹا_device_handle_drop,
    ڈیٹا_device_handle_selection
};

ساکن خالی primary_selection_device_handle_offer(خالی *ڈیٹا, ساخت zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  ساخت zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, حجم(*primary_selection_offer));
    اگر (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)ڈیٹا;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_سیٹ_user_ڈیٹا(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_جوڑو_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id) : -1));
}

ساکن خالی primary_selection_device_handle_selection(خالی *ڈیٹا, ساخت zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      ساخت zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = ڈیٹا;
    SDL_WaylandPrimarySelectionOffer *offer = تہی;

    اگر (id) {
        offer = zwp_primary_selection_offer_v1_get_user_ڈیٹا(id);
    }

    اگر (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((ساخت wl_proxy *)id) : -1));
}

ساکن ثابت ساخت zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساکن خالی متن_داخلہ_enter(خالی *ڈیٹا,
                             ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                             ساخت wl_surface *surface)
{
    // No-op
}

ساکن خالی متن_داخلہ_leave(خالی *ڈیٹا,
                             ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                             ساخت wl_surface *surface)
{
    // No-op
}

ساکن خالی متن_داخلہ_preedit_string(خالی *ڈیٹا,
                                      ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                      ثابت حرف *متن,
                                      int32_t cursor_begin,
                                      int32_t cursor_انتہا)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    seat->متن_داخلہ.has_preedit = true;
    اگر (متن) {
        صحیح cursor_begin_utf8 = cursor_begin >= 0 ? (صحیح)SDL_utf8strnlen(متن, cursor_begin) : -1;
        صحیح cursor_انتہا_utf8 = cursor_انتہا >= 0 ? (صحیح)SDL_utf8strnlen(متن, cursor_انتہا) : -1;
        صحیح cursor_سائز_utf8;
        اگر (cursor_انتہا_utf8 >= 0) {
            اگر (cursor_begin_utf8 >= 0) {
                cursor_سائز_utf8 = cursor_انتہا_utf8 - cursor_begin_utf8;
            } ورنہ {
                cursor_سائز_utf8 = cursor_انتہا_utf8;
            }
        } ورنہ {
            cursor_سائز_utf8 = -1;
        }
        SDL_Send_Editing_متن(متن, cursor_begin_utf8, cursor_سائز_utf8);
    } ورنہ {
        SDL_Send_Editing_متن("", 0, 0);
    }
}

ساکن خالی متن_داخلہ_commit_string(خالی *ڈیٹا,
                                     ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                     ثابت حرف *متن)
{
    SDL_Send_Keyboard_متن(متن);
}

ساکن خالی متن_داخلہ_delete_surrounding_متن(خالی *ڈیٹا,
                                               ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                               uint32_t before_لمبائی,
                                               uint32_t after_لمبائی)
{
    // FIXME: Do we care about this event?
}

ساکن خالی متن_داخلہ_مکمل(خالی *ڈیٹا,
                            ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    اگر (!seat->متن_داخلہ.has_preedit) {
        SDL_Send_Editing_متن("", 0, 0);
    }
    seat->متن_داخلہ.has_preedit = false;
}

ساکن ثابت ساخت zwp_متن_داخلہ_v3_listener متن_داخلہ_listener = {
    متن_داخلہ_enter,
    متن_داخلہ_leave,
    متن_داخلہ_preedit_string,
    متن_داخلہ_commit_string,
    متن_داخلہ_delete_surrounding_متن,
    متن_داخلہ_مکمل
};

ساکن خالی Wayland_ڈیٹا_Device_سیٹ_ID(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device)
{
    اگر (!ڈیٹا_device->id_str)
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        اگر (dbus) {
            ثابت حرف *id = dbus->bus_get_unique_name(dbus->session_conn);
            اگر (id) {
                ڈیٹا_device->id_str = SDL_strdup(id);
            }
        }
    }
    اگر (!ڈیٹا_device->id_str)
#اگر_ختم
    {
        حرف id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, حجم(id), "%" SDL_PRIu64, pid);
        ڈیٹا_device->id_str = SDL_strdup(id);
    }
}

ساکن خالی Wayland_Seat_Create_ڈیٹا_Device(SDL_WaylandSeat *seat)
{
    اگر (!seat->display->ڈیٹا_device_manager) {
        واپس;
    }

    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = SDL_calloc(1, حجم(*ڈیٹا_device));
    اگر (!ڈیٹا_device) {
        واپس;
    }

    ڈیٹا_device->ڈیٹا_device = wl_ڈیٹا_device_manager_get_ڈیٹا_device(
        seat->display->ڈیٹا_device_manager, seat->wl_seat);
    ڈیٹا_device->seat = seat;

    اگر (!ڈیٹا_device->ڈیٹا_device) {
        SDL_free(ڈیٹا_device);
        واپس;
    }

    Wayland_ڈیٹا_Device_سیٹ_ID(ڈیٹا_device);
    WAYLAND_wl_list_init(&ڈیٹا_device->pending_drops);
    wl_ڈیٹا_device_سیٹ_user_ڈیٹا(ڈیٹا_device->ڈیٹا_device, ڈیٹا_device);
    wl_ڈیٹا_device_جوڑو_listener(ڈیٹا_device->ڈیٹا_device, &ڈیٹا_device_listener, ڈیٹا_device);
    seat->ڈیٹا_device = ڈیٹا_device;
}

خالی Wayland_Display_Init_ڈیٹا_Device_Manager(SDL_Video_ڈیٹا *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_ڈیٹا_Device(seat);
    }
}

ساکن خالی Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    اگر (!seat->display->primary_selection_device_manager) {
        واپس;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, حجم(*primary_selection_device));
    اگر (!primary_selection_device) {
        واپس;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    اگر (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ورنہ {
        zwp_primary_selection_device_v1_سیٹ_user_ڈیٹا(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_جوڑو_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

خالی Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ڈیٹا *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ساکن خالی Wayland_Seat_Create_متن_داخلہ(SDL_WaylandSeat *seat)
{
    اگر (seat->display->متن_داخلہ_manager) {
        seat->متن_داخلہ.zwp_متن_داخلہ = zwp_متن_داخلہ_manager_v3_get_متن_داخلہ(seat->display->متن_داخلہ_manager, seat->wl_seat);

        اگر (seat->متن_داخلہ.zwp_متن_داخلہ) {
            zwp_متن_داخلہ_v3_سیٹ_user_ڈیٹا(seat->متن_داخلہ.zwp_متن_داخلہ, seat);
            zwp_متن_داخلہ_v3_جوڑو_listener(seat->متن_داخلہ.zwp_متن_داخلہ,
                                           &متن_داخلہ_listener, seat);
        }
    }
}

خالی Wayland_Display_Init_متن_داخلہ_Manager(SDL_Video_ڈیٹا *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_متن_داخلہ(seat);
    }
}

// Pen/Tablet support...
ساکن خالی tablet_tool_handle_type(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    انتخاب (type) {
        #تعریف_کرو CASE(typ) حالت ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; واپس
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #تعریف_منسوخ CASE
        طےشدہ: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ساکن خالی tablet_tool_handle_hardware_serial(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ساکن خالی tablet_tool_handle_hardware_id_wacom(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->info.wacom_id = id_lo;
}

ساکن خالی tablet_tool_handle_capability(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    انتخاب (capability) {
        #تعریف_کرو CASE(wltyp,sdltyp) حالت ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; واپس
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(فاصلہ_2, SDL_PEN_CAPABILITY_فاصلہ);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #تعریف_منسوخ CASE
        طےشدہ: توڑو;  // unsupported here.
    }
}

ساکن خالی tablet_tool_handle_مکمل(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    اگر (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : تہی;
        sdltool->instance_id = SDL_جوڑو_Pen_Device(0, تہی, کھڑکی, &sdltool->info, sdltool, false);
    }
}

ساکن خالی tablet_tool_handle_removed(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    اگر (sdltool->instance_id) {
        SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : تہی;
        SDL_RemovePenDevice(0, کھڑکی, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساکن خالی tablet_tool_handle_proximity_اندر(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t serial, ساخت zwp_tablet_v2 *tablet, ساخت wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    SDL_کھڑکی_ڈیٹا *windowdata = surface ? Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(surface) : تہی;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : تہی;
    sdltool->proximity_serial = serial;
    sdltool->چوکھٹا.have_proximity = true;
    sdltool->چوکھٹا.اندر_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساکن خالی tablet_tool_handle_proximity_برآمد(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.have_proximity = true;
    sdltool->چوکھٹا.اندر_proximity = false;
}

ساکن خالی tablet_tool_handle_نیچے_کو(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.tool_state = WAYLAND_TABLET_TOOL_STATE_نیچے_کو;
}

ساکن خالی tablet_tool_handle_اوپر(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.tool_state = WAYLAND_TABLET_TOOL_STATE_اوپر;
}

ساکن خالی tablet_tool_handle_motion(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    SDL_کھڑکی_ڈیٹا *windowdata = sdltool->focus;
    اگر (windowdata) {
        sdltool->چوکھٹا.x = (اعشاری)(wl_fixed_مقصد_double(sx_w) * windowdata->اشارہ_گر_scale.x);
        sdltool->چوکھٹا.y = (اعشاری)(wl_fixed_مقصد_double(sy_w) * windowdata->اشارہ_گر_scale.y);
        sdltool->چوکھٹا.have_motion = true;
    }
}

ساکن خالی tablet_tool_handle_pressure(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_PRESSURE] = ((اعشاری) pressure) / 65535.0f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_PRESSURE);
    اگر (pressure) {
        sdltool->چوکھٹا.axes[SDL_PEN_AXIS_فاصلہ] = 0.0f;
        sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_فاصلہ);
    }
}

ساکن خالی tablet_tool_handle_فاصلہ(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t فاصلہ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_فاصلہ] = ((اعشاری) فاصلہ) / 65535.0f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_فاصلہ);
    اگر (فاصلہ) {
        sdltool->چوکھٹا.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساکن خالی tablet_tool_handle_tilt(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_XTILT] = (اعشاری)(wl_fixed_مقصد_double(xtilt));
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_YTILT] = (اعشاری)(wl_fixed_مقصد_double(ytilt));
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ساکن خالی tablet_tool_handle_button(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    صحیح sdlbutton;

    انتخاب (button) {
    حالت BTN_STYLUS:
        sdlbutton = 1;
        توڑو;
    حالت BTN_STYLUS2:
        sdlbutton = 2;
        توڑو;
    حالت BTN_STYLUS3:
        sdlbutton = 3;
        توڑو;
    طےشدہ:
        واپس;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->چوکھٹا.buttons)));
    sdltool->چوکھٹا.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_نیچے_کو : WAYLAND_TABLET_TOOL_BUTTON_اوپر;
}

ساکن خالی tablet_tool_handle_rotation(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    ثابت اعشاری rotation = (اعشاری)(wl_fixed_مقصد_double(degrees));
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساکن خالی tablet_tool_handle_slider(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساکن خالی tablet_tool_handle_wheel(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساکن خالی tablet_tool_handle_چوکھٹا(خالی *ڈیٹا, ساخت zwp_tablet_tool_v2 *tool, uint32_t وقت)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) ڈیٹا;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    اگر (!instance_id) {
        واپس;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_Adjust_Event_Timestamp_بنیاد(Wayland_EventTimestampMSToNS(وقت));
    SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : تہی;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    اگر (sdltool->چوکھٹا.have_proximity && sdltool->چوکھٹا.اندر_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کھڑکی, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    اگر (sdltool->چوکھٹا.have_motion && sdltool->چوکھٹا.tool_state) {
        اگر (sdltool->چوکھٹا.tool_state == WAYLAND_TABLET_TOOL_STATE_نیچے_کو) {
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, true);
        } ورنہ {
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
        }
    } ورنہ {
        اگر (sdltool->چوکھٹا.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, sdltool->چوکھٹا.tool_state == WAYLAND_TABLET_TOOL_STATE_نیچے_کو);
        }

        اگر (sdltool->چوکھٹا.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
        }
    }

    برائے (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_گنتی; i++) {
        اگر (sdltool->چوکھٹا.axes_سیٹ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, کھڑکی, i, sdltool->چوکھٹا.axes[i]);
        }
    }

    برائے (صحیح i = 0; i < SDL_arraysize(sdltool->چوکھٹا.buttons); i++) {
        ثابت صحیح state = sdltool->چوکھٹا.buttons[i];
        اگر (state) {
            SDL_SendPenButton(timestamp, instance_id, کھڑکی, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_نیچے_کو);
        }
    }

    اگر (sdltool->چوکھٹا.have_proximity && !sdltool->چوکھٹا.اندر_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کھڑکی, false, false);
        sdltool->focus = تہی;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->چوکھٹا);
}

ساکن ثابت ساخت zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_مکمل,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_اندر,
    tablet_tool_handle_proximity_برآمد,
    tablet_tool_handle_نیچے_کو,
    tablet_tool_handle_اوپر,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_فاصلہ,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_چوکھٹا
};


ساکن خالی tablet_seat_handle_tablet_added(خالی *ڈیٹا, ساخت zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساخت zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ساکن خالی tablet_seat_handle_tool_added(خالی *ڈیٹا, ساخت zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساخت zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)ڈیٹا;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, حجم(*sdltool));

    اگر (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.عدد_buttons = -1;

        اگر (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_داخل_کرو(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_جوڑو_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ساکن خالی tablet_seat_handle_pad_added(خالی *ڈیٹا, ساخت zwp_tablet_seat_v2 *zwp_tablet_seat_v2, ساخت zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ساکن ثابت ساخت zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ساکن خالی Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_جوڑو_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

خالی Wayland_DisplayInitTabletManager(SDL_Video_ڈیٹا *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ساکن خالی Wayland_remove_all_pens_callback(SDL_PenID instance_id, خالی *handle, خالی *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ساکن خالی Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_نیچے_کو)
{
    اگر (!shutting_نیچے_کو) {
        SDL_WaylandPenTool *tool, *عارضی;
        wl_list_for_each_محفوظ (tool, عارضی, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ورنہ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, تہی);
    }

    اگر (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = تہی;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

خالی Wayland_DisplayCreateSeat(SDL_Video_ڈیٹا *display, ساخت wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, حجم(SDL_WaylandSeat));
    اگر (!seat) {
        واپس;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_داخل_کرو(display->seat_list.پچھلا, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_ڈیٹا_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_متن_داخلہ(seat);

    wl_seat_سیٹ_user_ڈیٹا(seat->wl_seat, seat);
    wl_seat_جوڑو_listener(seat->wl_seat, &seat_listener, seat);

    اگر (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

خالی Wayland_Display_Remove_کھڑکی_References_From_Seats(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        اگر (seat->keyboard.focus == کھڑکی) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, کھڑکی->surface);
        }

        اگر (seat->اشارہ_گر_2.focus == کھڑکی) {
            seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = seat->اشارہ_گر_2.focus->surface;
            اشارہ_گر_dispatch_leave(seat, true);
            seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = تہی;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_نقطہ *tp, *عارضی;
        wl_list_for_each_محفوظ (tp, عارضی, &seat->touch.points, link) {
            اگر (tp->surface == کھڑکی->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->focus == کھڑکی) {
                tool->focus = تہی;
                Wayland_TabletToolUpdateCursor(tool);
                اگر (tool->instance_id) {
                    SDL_RemovePenDevice(0, کھڑکی->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_ڈیٹا *drop, *drop_عارضی;
        wl_list_for_each_محفوظ (drop, drop_عارضی, &seat->ڈیٹا_device->pending_drops, link) {
            اگر (drop->dnd_کھڑکی == کھڑکی->sdlwindow) {
                Wayland_کام_Thread_Cancel_کام(display->کام_thread_context, drop->id);

                اگر (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_ڈیٹا_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

خالی Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_نیچے_کو)
{
    اگر (!seat) {
        واپس;
    }

    SDL_free(seat->name);

    اگر (seat->ڈیٹا_device) {
        اگر (seat->ڈیٹا_device->selection_offer) {
            Wayland_ڈیٹا_Offer_Destroy(seat->ڈیٹا_device->selection_offer);
        }
        اگر (seat->ڈیٹا_device->selection_ماخذ) {
            Wayland_ڈیٹا_ماخذ_Destroy(seat->ڈیٹا_device->selection_ماخذ);
        }
        اگر (seat->ڈیٹا_device->drag_offer) {
            Wayland_ڈیٹا_Offer_Destroy(seat->ڈیٹا_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_ڈیٹا *drop, *drop_عارضی;
        wl_list_for_each_محفوظ (drop, drop_عارضی, &seat->ڈیٹا_device->pending_drops, link) {
            Wayland_کام_Thread_Cancel_کام(seat->display->کام_thread_context, drop->id);

            اگر (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_ڈیٹا_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        اگر (seat->ڈیٹا_device->ڈیٹا_device) {
            اگر (wl_ڈیٹا_device_get_نسخہ(seat->ڈیٹا_device->ڈیٹا_device) >= WL_ڈیٹا_DEVICE_RELEASE_SINCE_نسخہ) {
                wl_ڈیٹا_device_release(seat->ڈیٹا_device->ڈیٹا_device);
            } ورنہ {
                wl_ڈیٹا_device_destroy(seat->ڈیٹا_device->ڈیٹا_device);
            }
        }
        SDL_free(seat->ڈیٹا_device->id_str);
        SDL_free(seat->ڈیٹا_device);
    }

    اگر (seat->primary_selection_device) {
        اگر (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        اگر (seat->primary_selection_device->selection_ماخذ) {
            Wayland_Primary_Selection_ماخذ_Destroy(seat->primary_selection_device->selection_ماخذ);
        }
        اگر (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    اگر (seat->متن_داخلہ.zwp_متن_داخلہ) {
        zwp_متن_داخلہ_v3_destroy(seat->متن_داخلہ.zwp_متن_داخلہ);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_اشارہ_گر(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_نیچے_کو);

    اگر (wl_seat_get_نسخہ(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_نسخہ) {
        wl_seat_release(seat->wl_seat);
    } ورنہ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساکن خالی Wayland_Seat_Update_Relative_اشارہ_گر(SDL_WaylandSeat *seat)
{
    اگر (seat->display->relative_اشارہ_گر_manager) {
        bool relative_focus = false;

        اگر (seat->اشارہ_گر_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            اگر (seat->اشارہ_گر_2.focus->sdlwindow->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال) {
                اگر (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->اشارہ_گر_2.focus;
                } ورنہ {
                    relative_focus = seat->اشارہ_گر_2.focus->keyboard_focus_گنتی != 0;
                }
            } ورنہ {
                relative_focus = SDL_GetMouse()->warp_emulation_فعال;
            }
        }

        اگر (relative_focus) {
            اگر (!seat->اشارہ_گر_2.relative_اشارہ_گر) {
                seat->اشارہ_گر_2.relative_اشارہ_گر = zwp_relative_اشارہ_گر_manager_v1_get_relative_اشارہ_گر(seat->display->relative_اشارہ_گر_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
                zwp_relative_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.relative_اشارہ_گر, &relative_اشارہ_گر_listener, seat);
            }
        } ورنہ اگر (seat->اشارہ_گر_2.relative_اشارہ_گر) {
            zwp_relative_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.relative_اشارہ_گر);
            seat->اشارہ_گر_2.relative_اشارہ_گر = تہی;
        }
    }
}

ساکن خالی Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_ڈیٹا *display = seat->display;

    اگر (display->کلید_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        اگر (seat->keyboard.کلید_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
            seat->keyboard.کلید_inhibitor = تہی;
        }

        اگر (seat->keyboard.wl_keyboard) {
            SDL_کھڑکی_ڈیٹا *w = seat->keyboard.focus;
            اگر (w) {
                SDL_کھڑکی *کھڑکی = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                اگر (کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
                    seat->keyboard.کلید_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کلید_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

خالی Wayland_Seat_Update_اشارہ_گر_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_ڈیٹا *display = seat->display;
    Wayland_Seat_Update_Relative_اشارہ_گر(seat);

    اگر (display->اشارہ_گر_constraints) {
        اگر (seat->اشارہ_گر_2.locked_اشارہ_گر && !seat->اشارہ_گر_2.relative_اشارہ_گر) {
            zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
            seat->اشارہ_گر_2.locked_اشارہ_گر = تہی;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
        }

        اگر (seat->اشارہ_گر_2.wl_اشارہ_گر) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            اگر (seat->اشارہ_گر_2.relative_اشارہ_گر) {
                اگر (!seat->اشارہ_گر_2.locked_اشارہ_گر) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    اگر (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                        zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                        seat->اشارہ_گر_2.confined_اشارہ_گر = تہی;
                    }

                    seat->اشارہ_گر_2.locked_اشارہ_گر = zwp_اشارہ_گر_constraints_v1_تالا_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                                           seat->اشارہ_گر_2.focus->surface,
                                                                                           seat->اشارہ_گر_2.wl_اشارہ_گر, تہی,
                                                                                           ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.locked_اشارہ_گر, &locked_اشارہ_گر_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                واپس;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            اگر (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                seat->اشارہ_گر_2.confined_اشارہ_گر = تہی;
            }

            SDL_کھڑکی_ڈیٹا *w = seat->اشارہ_گر_2.focus;
            اگر (!w) {
                واپس;
            }

            SDL_کھڑکی *کھڑکی = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            اگر (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) ||
                (!(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED) && SDL_Rect_خالی_خانے(&کھڑکی->mouse_rect))) {
                واپس;
            }

            ساخت wl_region *confine_rect = تہی;
            اگر (!SDL_Rect_خالی_خانے(&کھڑکی->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(کھڑکی, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_جوڑو(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                اگر (!SDL_نقطہ_اندر_Rect(&seat->اشارہ_گر_2.آخری_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحیح closest_x = seat->اشارہ_گر_2.آخری_motion.x;
                    صحیح closest_y = seat->اشارہ_گر_2.آخری_motion.y;

                    اگر (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ورنہ اگر (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    اگر (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ورنہ اگر (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            اگر (confine_rect || (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
                اگر (کھڑکی->mouse_rect.w != 1 && کھڑکی->mouse_rect.h != 1) {
                    seat->اشارہ_گر_2.confined_اشارہ_گر =
                        zwp_اشارہ_گر_constraints_v1_confine_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                   w->surface,
                                                                   seat->اشارہ_گر_2.wl_اشارہ_گر,
                                                                   confine_rect,
                                                                   ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.confined_اشارہ_گر,
                                                         &confined_اشارہ_گر_listener,
                                                         seat);
                } ورنہ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->اشارہ_گر_2.locked_اشارہ_گر =
                        zwp_اشارہ_گر_constraints_v1_تالا_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                w->surface,
                                                                seat->اشارہ_گر_2.wl_اشارہ_گر,
                                                                تہی,
                                                                ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.locked_اشارہ_گر,
                                                       &locked_اشارہ_گر_listener,
                                                       seat);
                }
                اگر (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

خالی Wayland_Display_Update_اشارہ_گر_Grabs(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        اگر (!کھڑکی || seat->اشارہ_گر_2.focus == کھڑکی) {
            Wayland_Seat_Update_اشارہ_گر_Grab(seat);
        }
    }
}

خالی Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        اگر (!کھڑکی || seat->keyboard.focus == کھڑکی) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

خالی Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    اگر (serial > seat->آخری_implicit_grab_serial) {
        seat->آخری_implicit_grab_serial = serial;
        seat->display->آخری_implicit_grab_seat = seat;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
