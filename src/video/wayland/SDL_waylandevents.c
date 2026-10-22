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

#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_scancode_tables_c.h"
#ضمن "../../events/SDL_keysym_to_keycode_c.h"
#ضمن "../../core/linux/SDL_system_theme.h"
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "SDL_waylandmouse.h"
#ضمن "SDL_waylandclipboard.h"
#ضمن "SDL_waylandkeyboard.h"

#ضمن "pointer-constraints-unstable-v1-client-protocol.h"
#ضمن "relative-pointer-unstable-v1-client-protocol.h"
#ضمن "xdg-shell-client-protocol.h"
#ضمن "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ضمن "text-input-unstable-v3-client-protocol.h"
#ضمن "tablet-v2-client-protocol.h"
#ضمن "primary-selection-unstable-v1-client-protocol.h"
#ضمن "input-timestamps-unstable-v1-client-protocol.h"
#ضمن "pointer-gestures-unstable-v1-client-protocol.h"
#ضمن "cursor-shape-v1-client-protocol.h"
#ضمن "viewporter-client-protocol.h"

#اگر_تعریف_شده HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#پایان_اگر

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#اگر_تعریف_شده SDL_درون_داد_LINUXEV
#ضمن <linux/input.h>
#وإلا
#تعریف_کن BTN_چپ    (0x110)
#تعریف_کن BTN_راست   (0x111)
#تعریف_کن BTN_میانه  (0x112)
#تعریف_کن BTN_SIDE    (0x113)
#تعریف_کن BTN_EXTRA   (0x114)
#تعریف_کن BTN_STYLUS  (0x14b)
#تعریف_کن BTN_STYLUS2 (0x14c)
#تعریف_کن BTN_STYLUS3 (0x149)
#پایان_اگر
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/imKStoUCS.h"
#ضمن <errno.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>
#ضمن <xkbcommon/xkbcommon-compose.h>
#ضمن <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#تعریف_کن WAYLAND_WHEEL_AXIS_UNIT 10

#اگر_تعریف_نشده XKB_MOD_NAME_MOD3
#تعریف_کن XKB_MOD_NAME_MOD3 "Mod3"
#پایان_اگر

#اگر_تعریف_نشده XKB_MOD_NAME_MOD5
#تعریف_کن XKB_MOD_NAME_MOD5 "Mod5"
#پایان_اگر

// Keyboard and mouse names to match XWayland
#تعریف_کن WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#تعریف_کن WAYLAND_DEFAULT_اشاره_گر_NAME "Virtual core pointer"
#تعریف_کن WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#تعریف_کن WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_مقصد_NS(10)

// Timer rollover detection thresholds
#تعریف_کن WAYLAND_TIMER_ROLLOVER_INTERVAL_کم  (SDL_MAX_UINT32 / 16U)
#تعریف_کن WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا (WAYLAND_TIMER_ROLLOVER_INTERVAL_کم * 15U)

// Scoped function declarations
ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

تعريفنوع بنية
{
    Uint32 کلید;
    SDL_Scancode scancode;
} Wayland_Reserved_کلید;

تعريفنوع بنية
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    بنية wl_surface *surface;

    بنية wl_list link;
} SDL_Wayland_Touch_نقطه;

ساكن فراغ Wayland_Seat_جمع_کن_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface *surface)
{
    SDL_Wayland_Touch_نقطه *tp = SDL_malloc(حجم(SDL_Wayland_Touch_نقطه));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_درج(&seat->touch.points, &tp->link);
}

ساكن فراغ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_نقطه *tp)
{
    إذا (tp->surface) {
        SDL_پنجره_داده *پنجره_داده_2 = Wayland_Get_پنجره_داده_For_Owned_Surface(tp->surface);

        إذا (پنجره_داده_2) {
            ثابت عائم x = (عائم)(wl_fixed_مقصد_double(tp->fx) / پنجره_داده_2->current.logical_عرض);
            ثابت عائم y = (عائم)(wl_fixed_مقصد_double(tp->fy) / پنجره_داده_2->current.logical_ارتفاع);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), پنجره_داده_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --پنجره_داده_2->فعال_touch_شمار;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == پنجره_داده_2->sdlwindow && !پنجره_داده_2->keyboard_focus_شمار &&
                !پنجره_داده_2->اشاره_گر_focus_شمار && !پنجره_داده_2->فعال_touch_شمار) {
                SDL_مجموعه_Mouse_Focus(عدم);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساكن فراغ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface **surface)
{
    SDL_Wayland_Touch_نقطه *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        إذا (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            إذا (surface) {
                *surface = tp->surface;
            }
            اكسر;
        }
    }
}

ساكن فراغ Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, بنية wl_surface **surface)
{
    SDL_Wayland_Touch_نقطه *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        إذا (tp->id == id) {
            إذا (fx) {
                *fx = tp->fx;
            }
            إذا (fy) {
                *fy = tp->fy;
            }
            إذا (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            اكسر;
        }
    }
}

ساكن فراغ Wayland_GetScaledMouseRect(SDL_پنجره *پنجره, SDL_Rect *scaled_rect)
{
    SDL_پنجره_داده *پنجره_داده_2 = پنجره->داخلی;

    scaled_rect->x = (صحيح)SDL_floor(پنجره->mouse_rect.x / پنجره_داده_2->اشاره_گر_scale.x);
    scaled_rect->y = (صحيح)SDL_floor(پنجره->mouse_rect.y / پنجره_داده_2->اشاره_گر_scale.y);
    scaled_rect->w = (صحيح)SDL_ceil(پنجره->mouse_rect.w / پنجره_داده_2->اشاره_گر_scale.x);
    scaled_rect->h = (صحيح)SDL_ceil(پنجره->mouse_rect.h / پنجره_داده_2->اشاره_گر_scale.y);
}

ساكن Uint64 Wayland_Adjust_Event_Timestamp_پایه(Uint64 nsTimestamp)
{
    ساكن Uint64 timestamp_جابه_جایی = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    إذا (!timestamp_جابه_جایی) {
        timestamp_جابه_جایی = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_جابه_جایی;

    إذا (nsTimestamp > now) {
        timestamp_جابه_جایی -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    أرجع nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساكن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساكن Uint64 timestamp_جابه_جایی = 0;
    ساكن Uint32 آخرین = 0;
    Uint64 timestamp = SDL_MS_مقصد_NS(wl_timestamp_ms) + timestamp_جابه_جایی;

    إذا (wl_timestamp_ms >= آخرین) {
        إذا (timestamp_جابه_جایی && آخرین < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
        } وإلا {
            آخرین = wl_timestamp_ms;
        }
    } وإلا {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        إذا (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && آخرین > WAYLAND_TIMER_ROLLOVER_INTERVAL_بالا) {
            timestamp_جابه_جایی += SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_مقصد_NS(SDL_UINT64_C(0x100000000));
            آخرین = wl_timestamp_ms;
        }
    }

    أرجع timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

ساكن Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_پایه(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن Uint64 Wayland_Get_اشاره_گر_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_پایه(seat->اشاره_گر_2.timestamps ? seat->اشاره_گر_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_پایه(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن فراغ درون_داد_timestamp_listener(فراغ *داده, بنية zwp_درون_داد_timestamps_v1 *zwp_درون_داد_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)داده) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_در_هر_دومی) + tv_nsec;
}

ساكن ثابت بنية zwp_درون_داد_timestamps_v1_listener timestamp_listener = {
    درون_داد_timestamp_listener
};

ساكن فراغ Wayland_Seat_ثبات_درون_داد_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    إذا (seat->display->درون_داد_timestamps_manager) {
        إذا (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_درون_داد_timestamps_manager_v1_get_keyboard_timestamps(seat->display->درون_داد_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_درون_داد_timestamps_v1_جمع_کن_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        إذا (seat->اشاره_گر_2.wl_اشاره_گر && !seat->اشاره_گر_2.timestamps) {
            seat->اشاره_گر_2.timestamps = zwp_درون_داد_timestamps_manager_v1_get_اشاره_گر_timestamps(seat->display->درون_داد_timestamps_manager, seat->اشاره_گر_2.wl_اشاره_گر);
            zwp_درون_داد_timestamps_v1_جمع_کن_listener(seat->اشاره_گر_2.timestamps, &timestamp_listener, &seat->اشاره_گر_2.highres_timestamp_ns);
        }

        إذا (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_درون_داد_timestamps_manager_v1_get_touch_timestamps(seat->display->درون_داد_timestamps_manager, seat->touch.wl_touch);
            zwp_درون_داد_timestamps_v1_جمع_کن_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

فراغ Wayland_Display_Init_درون_داد_Timestamp_Manager(SDL_Video_داده *display)
{
    إذا (display->درون_داد_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_ثبات_درون_داد_Timestamp_Listeners(seat);
        }
    }
}

ساكن فراغ handle_pinch_begin(فراغ *داده, بنية zwp_اشاره_گر_gesture_pinch_v1 *zwp_اشاره_گر_gesture_pinch_v1, uint32_t serial, uint32_t زمان, بنية wl_surface *surface, uint32_t fingers)
{
    إذا (!surface) {
        أرجع;
    }

    SDL_پنجره_داده *wind = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);
    إذا (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
        seat->اشاره_گر_2.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_update(فراغ *داده, بنية zwp_اشاره_گر_gesture_pinch_v1 *zwp_اشاره_گر_gesture_pinch_v1, uint32_t زمان,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;

    إذا (seat->اشاره_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);
        ثابت عائم s = (عائم)wl_fixed_مقصد_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->اشاره_گر_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_انتها(فراغ *داده, بنية zwp_اشاره_گر_gesture_pinch_v1 *zwp_اشاره_گر_gesture_pinch_v1, uint32_t serial, uint32_t زمان, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;

    إذا (seat->اشاره_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);
        SDL_SendPinch(SDL_EVENT_PINCH_انتها, timestamp, seat->اشاره_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->اشاره_گر_2.gesture_focus = عدم;
    }
}

ساكن ثابت بنية zwp_اشاره_گر_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_انتها
};

ساكن فراغ Wayland_Seat_Create_اشاره_گر_Gestures(SDL_WaylandSeat *seat)
{
    إذا (seat->display->zwp_اشاره_گر_gestures) {
        إذا (seat->اشاره_گر_2.wl_اشاره_گر && !seat->اشاره_گر_2.gesture_pinch) {
            seat->اشاره_گر_2.gesture_pinch = zwp_اشاره_گر_gestures_v1_get_pinch_gesture(seat->display->zwp_اشاره_گر_gestures, seat->اشاره_گر_2.wl_اشاره_گر);
            zwp_اشاره_گر_gesture_pinch_v1_مجموعه_user_داده(seat->اشاره_گر_2.gesture_pinch, seat);
            zwp_اشاره_گر_gesture_pinch_v1_جمع_کن_listener(seat->اشاره_گر_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_اشاره_گر_Gesture_Manager(SDL_Video_داده *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_اشاره_گر_Gestures(seat);
    }
}

ساكن فراغ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    إذا (seat->display->cursor_shape_manager) {
        إذا (seat->اشاره_گر_2.wl_اشاره_گر && !seat->اشاره_گر_2.cursor_state.cursor_shape) {
            seat->اشاره_گر_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_اشاره_گر(seat->display->cursor_shape_manager, seat->اشاره_گر_2.wl_اشاره_گر);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            إذا (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

فراغ Wayland_DisplayInitCursorShapeManager(SDL_Video_داده *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ساكن فراغ Wayland_Seat_مجموعه_Keymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    إذا (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_مجموعه_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_مجموعه_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساكن فراغ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    طالما (elapsed >= repeat_info->بعدی_repeat_ns) {
        إذا (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->پایه_زمان_ns + repeat_info->بعدی_repeat_ns;
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_پایه(timestamp), repeat_info->keyboard_id, repeat_info->کلید, repeat_info->scancode, true);
        }
        إذا (repeat_info->متن[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(repeat_info->متن);
        }
        repeat_info->بعدی_repeat_ns += SDL_NS_در_هر_دومی / (Uint64)repeat_info->repeat_نرخ;
    }
}

ساكن فراغ keyboard_repeat_مجموعه(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کلید, Uint32 wl_press_زمان_ms,
                                Uint64 پایه_زمان_ns, uint32_t scancode, ثابت حرف *متن)
{
    إذا (!repeat_info->repeat_نرخ) {
        أرجع;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کلید = کلید;
    repeat_info->wl_press_زمان_ms = wl_press_زمان_ms;
    repeat_info->پایه_زمان_ns = پایه_زمان_ns;
    repeat_info->sdl_press_زمان_ns = SDL_GetTicksNS();
    repeat_info->بعدی_repeat_ns = SDL_MS_مقصد_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    إذا (متن) {
        SDL_strlcpy(repeat_info->متن, متن, SDL_arraysize(repeat_info->متن));
    } وإلا {
        repeat_info->متن[0] = '\0';
    }
}

ساكن فراغ sync_انجامشده_handler(فراغ *داده, بنية wl_callback *callback, uint32_t callback_داده)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener sync_listener = {
    sync_انجامشده_handler
};

فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *d = _this->داخلی;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    بنية wl_callback *cb = wl_display_sync(d->display);
    wl_callback_جمع_کن_listener(cb, &sync_listener, عدم);
    WAYLAND_wl_display_flush(d->display);
}

صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_داده *d = _this->داخلی;
    SDL_WaylandSeat *seat;
    Uint64 شروع = SDL_GetTicksNS();
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret;
    bool poll_alarm_مجموعه = false;

#اگر_تعریف_شده SDL_USE_IME
    SDL_پنجره *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_درون_داد_manager && keyboard_focus && SDL_متن_درون_داد_فعال(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        إذا (timeoutNS < 0 || SDL_MS_مقصد_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_مقصد_NS(200);
            poll_alarm_مجموعه = true;
        }
    }
#پایان_اگر

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->keyboard.repeat.کلید) {
            ثابت Uint64 elapsed = شروع - seat->keyboard.repeat.sdl_press_زمان_ns;
            ثابت Uint64 بعدی_repeat_wait_زمان = (seat->keyboard.repeat.بعدی_repeat_ns - elapsed) + 1;
            إذا (timeoutNS < 0 || بعدی_repeat_wait_زمان <= timeoutNS) {
                timeoutNS = بعدی_repeat_wait_زمان;
                poll_alarm_مجموعه = true;
            }
        }
    }

    إذا (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - شروع;
            شروع = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        إذا (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            إذا (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        إذا (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            أرجع errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - شروع;
            شروع = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        إذا (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            إذا (ret == 0) {
                أرجع poll_alarm_مجموعه ? 1 : 0;
            } وإلا {
                // Pump events on an interrupt or broken pipe to handle the error.
                أرجع errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        إذا (ret == -1) {
            أرجع ret;
        }
    }

    // Signal to the caller that there might be an event available.
    أرجع 1;
}

فراغ Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_Video_داده *d = _this->داخلی;
    SDL_WaylandSeat *seat;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret = 0;

#اگر_تعریف_شده SDL_USE_IME
    SDL_پنجره *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_درون_داد_manager && keyboard_focus && SDL_متن_درون_داد_فعال(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#پایان_اگر

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#پایان_اگر

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    إذا (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        إذا (ret < 0) {
            اذهب connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    إذا (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        إذا (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_مقصد_NS(4));
            إذا (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        إذا (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            اذهب connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        إذا (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            إذا (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } وإلا {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } وإلا {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    إذا (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (seat->keyboard.repeat.کلید) {
                Wayland_Seat_مجموعه_Keymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_زمان_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    إذا (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساكن فراغ اشاره_گر_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_پنجره_داده *پنجره_داده_2 = seat->اشاره_گر_2.focus;
    SDL_پنجره *پنجره = پنجره_داده_2 ? پنجره_داده_2->sdlwindow : عدم;

    إذا (پنجره_داده_2) {
        مزدوج sx = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.absolute.sx);
        مزدوج sy = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.absolute.sy);

        إذا (seat->اشاره_گر_2.focus_surface == پنجره_داده_2->ماسک.surface) {
            sx += (مزدوج)پنجره_داده_2->ماسک.جابه_جایی_x;
            sy += (مزدوج)پنجره_داده_2->ماسک.جابه_جایی_y;
        }

        sx *= پنجره_داده_2->اشاره_گر_scale.x;
        sy *= پنجره_داده_2->اشاره_گر_scale.y;
        إذا (!warp) {
            SDL_SendMouseMotion(seat->اشاره_گر_2.pending_قاب.timestamp_ns, پنجره_داده_2->sdlwindow, seat->اشاره_گر_2.sdl_id, false, (عائم)sx, (عائم)sy);
        } وإلا {
            SDL_SendMouseWarp(seat->اشاره_گر_2.pending_قاب.timestamp_ns, پنجره_داده_2->sdlwindow, seat->اشاره_گر_2.sdl_id, (عائم)sx, (عائم)sy);
        }

        seat->اشاره_گر_2.آخرین_motion.x = (صحيح)SDL_floor(sx);
        seat->اشاره_گر_2.آخرین_motion.y = (صحيح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        إذا (!SDL_Rect_خالی(&پنجره->mouse_rect) && !seat->اشاره_گر_2.is_confined) {
            Wayland_Seat_Update_اشاره_گر_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        إذا (!(پنجره->flags & SDL_پنجره_MOUSE_CAPTURE) && پنجره->اصابت_test) {
            SDL_اصابت_Test_نتیجه rc = پنجره->اصابت_test(پنجره, &seat->اشاره_گر_2.آخرین_motion, پنجره->اصابت_test_داده);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            بدل (rc) {
            حالة SDL_HITTEST_RESIZE_TOPLEFT:
                إذا ((پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) &&
                    (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ)) {
                    rc = SDL_HITTEST_نرمال;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_RESIZE_چپ;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_RESIZE_بالاترین;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_بالاترین:
                إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_نرمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                إذا ((پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) &&
                    (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست)) {
                    rc = SDL_HITTEST_نرمال;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین) {
                    rc = SDL_HITTEST_RESIZE_راست;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_RESIZE_بالاترین;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_راست:
                إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_نرمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                إذا ((پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست)) {
                    rc = SDL_HITTEST_نرمال;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_راست;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_راست) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOM:
                إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_نرمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                إذا ((پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ)) {
                    rc = SDL_HITTEST_نرمال;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_چپ;
                } وإلا إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_چپ:
                إذا (پنجره_داده_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چپ) {
                    rc = SDL_HITTEST_نرمال;
                }
                اكسر;
            افتراضي:
                اكسر;
            }

            إذا (rc != پنجره_داده_2->اصابت_test_نتیجه) {
                پنجره_داده_2->اصابت_test_نتیجه = rc;
                Wayland_Seat_Update_اشاره_گر_Cursor(seat);
            }
        }
    }
}

ساكن فراغ اشاره_گر_handle_motion(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                  uint32_t زمان, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    ثابت Uint64 timestamp = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);

    seat->اشاره_گر_2.pending_قاب.absolute.sx = sx;
    seat->اشاره_گر_2.pending_قاب.absolute.sy = sy;

    إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) >= WL_اشاره_گر_قاب_SINCE_نسخه) {
        seat->اشاره_گر_2.pending_قاب.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        إذا (!seat->اشاره_گر_2.pending_قاب.have_relative || seat->اشاره_گر_2.timestamps) {
            seat->اشاره_گر_2.pending_قاب.timestamp_ns = timestamp;
        }
    } وإلا {
        seat->اشاره_گر_2.pending_قاب.timestamp_ns = timestamp;
        اشاره_گر_dispatch_absolute_motion(seat, false);
    }
}

ساكن فراغ اشاره_گر_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_پنجره_داده *پنجره = Wayland_Get_پنجره_داده_For_Owned_Surface(seat->اشاره_گر_2.pending_قاب.enter_surface);
    إذا (!پنجره) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        أرجع;
    }

    إذا (پنجره->surface != seat->اشاره_گر_2.pending_قاب.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_مجموعه_Default_Cursor(seat);
        أرجع;
    }

    seat->اشاره_گر_2.focus = پنجره;
    seat->اشاره_گر_2.focus_surface = seat->اشاره_گر_2.pending_قاب.enter_surface;
    ++پنجره->اشاره_گر_focus_شمار;
    SDL_مجموعه_Mouse_Focus(پنجره->sdlwindow);

    // Send the initial position.
    اشاره_گر_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_اشاره_گر_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_اشاره_گر_Cursor(seat);
}

ساكن فراغ اشاره_گر_handle_enter(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                 uint32_t serial, بنية wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.pending_قاب.enter_surface = surface;
    seat->اشاره_گر_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->اشاره_گر_2.pending_قاب.absolute.sx = sx_w;
    seat->اشاره_گر_2.pending_قاب.absolute.sy = sy_w;

    إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) < WL_اشاره_گر_قاب_SINCE_نسخه) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->اشاره_گر_2.pending_قاب.timestamp_ns = 0;
        اشاره_گر_dispatch_enter(seat);
    }
}

ساكن فراغ اشاره_گر_dispatch_leave(SDL_WaylandSeat *seat, bool update_اشاره_گر)
{
    SDL_پنجره_داده *پنجره = Wayland_Get_پنجره_داده_For_Owned_Surface(seat->اشاره_گر_2.pending_قاب.leave_surface);

    إذا (پنجره) {
        إذا (seat->اشاره_گر_2.focus) {
            إذا (seat->اشاره_گر_2.focus->surface == seat->اشاره_گر_2.pending_قاب.leave_surface) {
                // Clear the capture flag and raise all buttons
                پنجره->sdlwindow->flags &= ~SDL_پنجره_MOUSE_CAPTURE;

                seat->اشاره_گر_2.focus = عدم;
                seat->اشاره_گر_2.focus_surface = عدم;
                لكل (Uint8 i = 1; seat->اشاره_گر_2.buttons_pressed; ++i) {
                    إذا (seat->اشاره_گر_2.buttons_pressed & SDL_BUTTON_ماسک(i)) {
                        SDL_SendMouseButton(0, پنجره->sdlwindow, seat->اشاره_گر_2.sdl_id, i, false);
                        seat->اشاره_گر_2.buttons_pressed &= ~SDL_BUTTON_ماسک(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_پنجره *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && پنجره->sdlwindow == mouse_focus;
                إذا (!--پنجره->اشاره_گر_focus_شمار && had_focus && !پنجره->فعال_touch_شمار) {
                    SDL_مجموعه_Mouse_Focus(عدم);
                }

                إذا (update_اشاره_گر) {
                    Wayland_Seat_Update_اشاره_گر_Grab(seat);
                    Wayland_Seat_Update_اشاره_گر_Cursor(seat);
                }
            }
        } وإلا إذا (update_اشاره_گر) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساكن فراغ اشاره_گر_handle_leave(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                 uint32_t serial, بنية wl_surface *surface)
{
    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.pending_قاب.leave_surface = surface;
    إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) < WL_اشاره_گر_قاب_SINCE_نسخه) {
        اشاره_گر_dispatch_leave(seat, true);
    }
}

ساكن bool Wayland_Process_اصابت_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    إذا (seat->اشاره_گر_2.locked_اشاره_گر) {
        أرجع false;
    }

    SDL_پنجره_داده *پنجره_داده_2 = seat->اشاره_گر_2.focus;
    SDL_پنجره *پنجره = پنجره_داده_2->sdlwindow;

    إذا (پنجره->اصابت_test) {
        ساكن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_یال_بالاترین_چپ, XDG_TOPLEVEL_RESIZE_یال_بالاترین,
            XDG_TOPLEVEL_RESIZE_یال_بالاترین_راست, XDG_TOPLEVEL_RESIZE_یال_راست,
            XDG_TOPLEVEL_RESIZE_یال_BOTTOM_راست, XDG_TOPLEVEL_RESIZE_یال_BOTTOM,
            XDG_TOPLEVEL_RESIZE_یال_BOTTOM_چپ, XDG_TOPLEVEL_RESIZE_یال_چپ
        };

#اگر_تعریف_شده HAVE_LIBDECOR_H
        ساكن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_یال_بالاترین_چپ, LIBDECOR_RESIZE_یال_بالاترین,
            LIBDECOR_RESIZE_یال_بالاترین_راست, LIBDECOR_RESIZE_یال_راست,
            LIBDECOR_RESIZE_یال_BOTTOM_راست, LIBDECOR_RESIZE_یال_BOTTOM,
            LIBDECOR_RESIZE_یال_BOTTOM_چپ, LIBDECOR_RESIZE_یال_چپ
        };
#پایان_اگر

        بدل (پنجره_داده_2->اصابت_test_نتیجه) {
        حالة SDL_HITTEST_DRAGGABLE:
#اگر_تعریف_شده HAVE_LIBDECOR_H
            إذا (پنجره_داده_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (پنجره_داده_2->shell_surface.libdecor.قاب) {
                    libdecor_قاب_move(پنجره_داده_2->shell_surface.libdecor.قاب,
                                        seat->wl_seat,
                                        serial);
                }
            } وإلا
#پایان_اگر
                إذا (پنجره_داده_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (پنجره_داده_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(پنجره_داده_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_بالاترین:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_راست:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_چپ:
#اگر_تعریف_شده HAVE_LIBDECOR_H
            إذا (پنجره_داده_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (پنجره_داده_2->shell_surface.libdecor.قاب) {
                    libdecor_قاب_resize(پنجره_داده_2->shell_surface.libdecor.قاب,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[پنجره_داده_2->اصابت_test_نتیجه - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وإلا
#پایان_اگر
                إذا (پنجره_داده_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (پنجره_داده_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(پنجره_داده_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[پنجره_داده_2->اصابت_test_نتیجه - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ اشاره_گر_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool پایین)
{
    SDL_پنجره_داده *پنجره = seat->اشاره_گر_2.focus;

    إذا (پنجره) {
        bool ignore_click = false;

        إذا (پایین) {
            seat->اشاره_گر_2.buttons_pressed |= SDL_BUTTON_ماسک(sdl_button);

            إذا (sdl_button == SDL_BUTTON_چپ && Wayland_Process_اصابت_Test(seat, seat->آخرین_implicit_grab_serial)) {
                أرجع; // don't pass this event on to app.
            }
        } وإلا {
            seat->اشاره_گر_2.buttons_pressed &= ~SDL_BUTTON_ماسک(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        إذا (پنجره->آخرین_focus_event_زمان_ns) {
            إذا (پایین && (SDL_GetTicksNS() - پنجره->آخرین_focus_event_زمان_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            پنجره->آخرین_focus_event_زمان_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        إذا (!seat->اشاره_گر_2.relative_اشاره_گر) {
            إذا (seat->اشاره_گر_2.buttons_pressed != 0) {
                پنجره->sdlwindow->flags |= SDL_پنجره_MOUSE_CAPTURE;
            } وإلا {
                پنجره->sdlwindow->flags &= ~SDL_پنجره_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                إذا (seat->اشاره_گر_2.focus_surface != پنجره->surface) {
                    seat->اشاره_گر_2.pending_قاب.leave_surface = پنجره->surface;
                }
            }
        }

        إذا (!ignore_click) {
            SDL_SendMouseButton(seat->اشاره_گر_2.pending_قاب.timestamp_ns, پنجره->sdlwindow, seat->اشاره_گر_2.sdl_id, sdl_button, پایین);
        }
    }
}

ساكن فراغ اشاره_گر_handle_button(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2, uint32_t serial,
                                  uint32_t زمان, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = داده;
    Uint8 sdl_button;

    بدل (button) {
    حالة BTN_چپ:
        sdl_button = SDL_BUTTON_چپ;
        اكسر;
    حالة BTN_میانه:
        sdl_button = SDL_BUTTON_میانه;
        اكسر;
    حالة BTN_راست:
        sdl_button = SDL_BUTTON_راست;
        اكسر;
    افتراضي:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        اكسر;
    }

    إذا (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->اشاره_گر_2.pending_قاب.timestamp_ns = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_اشاره_گر_قاب_SINCE_نسخه) {
        إذا (state_w) {
            seat->اشاره_گر_2.pending_قاب.buttons_pressed |= SDL_BUTTON_ماسک(sdl_button);
        } وإلا {
            seat->اشاره_گر_2.pending_قاب.buttons_released |= SDL_BUTTON_ماسک(sdl_button);
        }
    } وإلا {
        اشاره_گر_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساكن فراغ اشاره_گر_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t مقدار)
{
    SDL_پنجره_داده *پنجره = seat->اشاره_گر_2.focus;
    ثابت تعداد wl_اشاره_گر_axis a = axis;

    إذا (seat->اشاره_گر_2.focus) {
        عائم x, y;

        بدل (a) {
        حالة WL_اشاره_گر_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (عائم)wl_fixed_مقصد_double(مقدار);
            اكسر;
        حالة WL_اشاره_گر_AXIS_HORIZONTAL_SCROLL:
            x = (عائم)wl_fixed_مقصد_double(مقدار);
            y = 0;
            اكسر;
        افتراضي:
            أرجع;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, پنجره->sdlwindow, seat->اشاره_گر_2.sdl_id, x, y, SDL_MOUSEWHEEL_نرمال);
    }
}

ساكن فراغ اشاره_گر_handle_axis_common(SDL_WaylandSeat *seat, تعداد SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t مقدار)
{
    ثابت تعداد wl_اشاره_گر_axis a = axis;

    إذا (seat->اشاره_گر_2.focus) {
        seat->اشاره_گر_2.pending_قاب.have_axis = true;

        بدل (a) {
        حالة WL_اشاره_گر_AXIS_VERTICAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشاره_گر_2.pending_قاب.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشاره_گر_2.pending_قاب.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشاره_گر_2.pending_قاب.axis.y = 0.0f;
                }
                seat->اشاره_گر_2.pending_قاب.axis.y += 0 - (عائم)wl_fixed_مقصد_double(مقدار);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشاره_گر_2.pending_قاب.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشاره_گر_2.pending_قاب.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشاره_گر_2.pending_قاب.axis.y = 0 - (عائم)wl_fixed_مقصد_double(مقدار);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشاره_گر_2.pending_قاب.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشاره_گر_2.pending_قاب.axis.y = 0 - (عائم)wl_fixed_مقصد_double(مقدار);
                }
                اكسر;
            }
            اكسر;
        حالة WL_اشاره_گر_AXIS_HORIZONTAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشاره_گر_2.pending_قاب.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشاره_گر_2.pending_قاب.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشاره_گر_2.pending_قاب.axis.x = 0.0f;
                }
                seat->اشاره_گر_2.pending_قاب.axis.x += (عائم)wl_fixed_مقصد_double(مقدار);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشاره_گر_2.pending_قاب.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشاره_گر_2.pending_قاب.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشاره_گر_2.pending_قاب.axis.x = (عائم)wl_fixed_مقصد_double(مقدار);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشاره_گر_2.pending_قاب.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشاره_گر_2.pending_قاب.axis.x = (عائم)wl_fixed_مقصد_double(مقدار);
                }
                اكسر;
            }
            اكسر;
        }
    }
}

ساكن فراغ اشاره_گر_handle_axis(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                uint32_t زمان, uint32_t axis, wl_fixed_t مقدار)
{
    SDL_WaylandSeat *seat = داده;
    ثابت Uint64 nsTimestamp = Wayland_Get_اشاره_گر_Timestamp(seat, زمان);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_اشاره_گر_قاب_SINCE_نسخه) {
        seat->اشاره_گر_2.pending_قاب.timestamp_ns = nsTimestamp;
        اشاره_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, مقدار);
    } وإلا {
        اشاره_گر_handle_axis_common_v1(seat, nsTimestamp, axis, مقدار);
    }
}

ساكن فراغ اشاره_گر_handle_axis_relative_direction(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = داده;

    بدل (axis_relative_direction) {
    حالة WL_اشاره_گر_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->اشاره_گر_2.pending_قاب.axis.direction = SDL_MOUSEWHEEL_نرمال;
        اكسر;
    حالة WL_اشاره_گر_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->اشاره_گر_2.pending_قاب.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        اكسر;
    }
}

ساكن فراغ اشاره_گر_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_پنجره_داده *پنجره = seat->اشاره_گر_2.focus;

    إذا (پنجره) {
        SDL_Mouse *mouse = SDL_GetMouse();
        مزدوج dx;
        مزدوج dy;
        إذا (mouse->درون_داد_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.relative.dx_unaccel);
            dy = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.relative.dy_unaccel);
        } وإلا {
            dx = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.relative.dx) * پنجره->اشاره_گر_scale.x;
            dy = wl_fixed_مقصد_double(seat->اشاره_گر_2.pending_قاب.relative.dy) * پنجره->اشاره_گر_scale.y;
        }

        SDL_SendMouseMotion(seat->اشاره_گر_2.pending_قاب.timestamp_ns, پنجره->sdlwindow, seat->اشاره_گر_2.sdl_id, true, (عائم)dx, (عائم)dy);
    }
}

ساكن فراغ اشاره_گر_dispatch_axis(SDL_WaylandSeat *seat)
{
    عائم x, y;
    SDL_MouseWheelDirection direction = seat->اشاره_گر_2.pending_قاب.axis.direction;

    بدل (seat->اشاره_گر_2.pending_قاب.axis.x_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->اشاره_گر_2.pending_قاب.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->اشاره_گر_2.pending_قاب.axis.x;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->اشاره_گر_2.pending_قاب.axis.x / 120.0f;
        اكسر;
    افتراضي:
        x = 0.0f;
        اكسر;
    }

    بدل (seat->اشاره_گر_2.pending_قاب.axis.y_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->اشاره_گر_2.pending_قاب.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->اشاره_گر_2.pending_قاب.axis.y;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->اشاره_گر_2.pending_قاب.axis.y / 120.0f;
        اكسر;
    افتراضي:
        y = 0.0f;
        اكسر;
    }

    SDL_SendMouseWheel(seat->اشاره_گر_2.pending_قاب.timestamp_ns,
                       seat->اشاره_گر_2.focus->sdlwindow, seat->اشاره_گر_2.sdl_id, x, y, direction);
}

ساكن فراغ اشاره_گر_handle_قاب(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2)
{
    SDL_WaylandSeat *seat = داده;

    إذا (seat->اشاره_گر_2.pending_قاب.enter_surface) {
        إذا (seat->اشاره_گر_2.pending_قاب.leave_surface) {
            SDL_پنجره_داده *پنجره_داده_2 = seat->اشاره_گر_2.focus;
            SDL_پنجره_داده *new_focus = Wayland_Get_پنجره_داده_For_Owned_Surface(seat->اشاره_گر_2.pending_قاب.enter_surface);

            إذا (پنجره_داده_2 && (پنجره_داده_2->sdlwindow->flags & SDL_پنجره_MOUSE_CAPTURE) && پنجره_داده_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->اشاره_گر_2.focus_surface = seat->اشاره_گر_2.pending_قاب.enter_surface;
                seat->اشاره_گر_2.pending_قاب.enter_surface = عدم;
                seat->اشاره_گر_2.pending_قاب.leave_surface = عدم;
            } وإلا {
                // Leaving the previous surface before entering a new surface.
                اشاره_گر_dispatch_leave(seat, false);
                seat->اشاره_گر_2.pending_قاب.leave_surface = عدم;
            }
        }

        إذا (seat->اشاره_گر_2.pending_قاب.enter_surface) {
            اشاره_گر_dispatch_enter(seat);
        }
    }

    إذا (seat->اشاره_گر_2.pending_قاب.have_absolute) {
        اشاره_گر_dispatch_absolute_motion(seat, seat->اشاره_گر_2.pending_قاب.have_warp);
    }

    إذا (seat->اشاره_گر_2.pending_قاب.have_relative) {
        اشاره_گر_dispatch_relative_motion(seat);
    }

    لكل (Uint8 i = 1; seat->اشاره_گر_2.pending_قاب.buttons_pressed || seat->اشاره_گر_2.pending_قاب.buttons_released; ++i) {
        ثابت Uint32 ماسک = SDL_BUTTON_ماسک(i);
        إذا (seat->اشاره_گر_2.pending_قاب.buttons_pressed & ماسک) {
            اشاره_گر_dispatch_button(seat, i, true);
            seat->اشاره_گر_2.pending_قاب.buttons_pressed &= ~ماسک;
        }
        إذا (seat->اشاره_گر_2.pending_قاب.buttons_released & ماسک) {
            اشاره_گر_dispatch_button(seat, i, false);
            seat->اشاره_گر_2.pending_قاب.buttons_released &= ~ماسک;
        }
    }

    إذا (seat->اشاره_گر_2.pending_قاب.have_axis) {
        اشاره_گر_dispatch_axis(seat);
    }

    إذا (seat->اشاره_گر_2.pending_قاب.leave_surface) {
        اشاره_گر_dispatch_leave(seat, true);
    }

    SDL_zero(seat->اشاره_گر_2.pending_قاب);
}

ساكن فراغ اشاره_گر_handle_axis_منبع(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                       uint32_t axis_منبع)
{
    // unimplemented
}

ساكن فراغ اشاره_گر_handle_axis_stop(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                     uint32_t زمان, uint32_t axis)
{
    // unimplemented
}

ساكن فراغ اشاره_گر_handle_axis_discrete(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = داده;
    اشاره_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساكن فراغ اشاره_گر_handle_axis_value120(فراغ *داده, بنية wl_اشاره_گر *اشاره_گر_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = داده;
    اشاره_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساكن فراغ اشاره_گر_handle_warp(فراغ *داده, بنية wl_اشاره_گر *wl_اشاره_گر, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;

    seat->اشاره_گر_2.pending_قاب.have_absolute = true;
    seat->اشاره_گر_2.pending_قاب.have_warp = true;
    seat->اشاره_گر_2.pending_قاب.absolute.sx = surface_x;
    seat->اشاره_گر_2.pending_قاب.absolute.sy = surface_y;
}

ساكن ثابت بنية wl_اشاره_گر_listener اشاره_گر_listener = {
    اشاره_گر_handle_enter,
    اشاره_گر_handle_leave,
    اشاره_گر_handle_motion,
    اشاره_گر_handle_button,
    اشاره_گر_handle_axis,
    اشاره_گر_handle_قاب,                   // Version 5
    اشاره_گر_handle_axis_منبع,             // Version 5
    اشاره_گر_handle_axis_stop,               // Version 5
    اشاره_گر_handle_axis_discrete,           // Version 5
    اشاره_گر_handle_axis_value120,           // Version 8
    اشاره_گر_handle_axis_relative_direction, // Version 9
    اشاره_گر_handle_warp                     // Version 11
};

ساكن فراغ relative_اشاره_گر_handle_relative_motion(فراغ *داده,
                                                    بنية zwp_relative_اشاره_گر_v1 *اشاره_گر_2,
                                                    uint32_t زمان_hi,
                                                    uint32_t زمان_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = داده;

    // Relative pointer event times are in microsecond granularity.
    seat->اشاره_گر_2.pending_قاب.relative.dx = dx;
    seat->اشاره_گر_2.pending_قاب.relative.dy = dy;
    seat->اشاره_گر_2.pending_قاب.relative.dx_unaccel = dx_unaccel;
    seat->اشاره_گر_2.pending_قاب.relative.dy_unaccel = dy_unaccel;
    seat->اشاره_گر_2.pending_قاب.timestamp_ns = Wayland_Adjust_Event_Timestamp_پایه(SDL_US_مقصد_NS(((Uint64)زمان_hi << 32) | (Uint64)زمان_lo));

    إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) >= WL_اشاره_گر_قاب_SINCE_نسخه) {
        seat->اشاره_گر_2.pending_قاب.have_relative = true;
    } وإلا {
        اشاره_گر_dispatch_relative_motion(seat);
    }
}

ساكن ثابت بنية zwp_relative_اشاره_گر_v1_listener relative_اشاره_گر_listener = {
    relative_اشاره_گر_handle_relative_motion,
};

ساكن فراغ locked_اشاره_گر_locked(فراغ *داده, بنية zwp_locked_اشاره_گر_v1 *locked_اشاره_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.is_confined = true;
}

ساكن فراغ locked_اشاره_گر_unlocked(فراغ *داده, بنية zwp_locked_اشاره_گر_v1 *locked_اشاره_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.is_confined = false;
}

ساكن ثابت بنية zwp_locked_اشاره_گر_v1_listener locked_اشاره_گر_listener = {
    locked_اشاره_گر_locked,
    locked_اشاره_گر_unlocked,
};

ساكن فراغ confined_اشاره_گر_confined(فراغ *داده, بنية zwp_confined_اشاره_گر_v1 *confined_اشاره_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.is_confined = true;
}

ساكن فراغ confined_اشاره_گر_unconfined(فراغ *داده, بنية zwp_confined_اشاره_گر_v1 *confined_اشاره_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->اشاره_گر_2.is_confined = false;
}

ساكن ثابت بنية zwp_confined_اشاره_گر_v1_listener confined_اشاره_گر_listener = {
    confined_اشاره_گر_confined,
    confined_اشاره_گر_unconfined,
};

ساكن فراغ touch_handler_پایین(فراغ *داده, بنية wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, بنية wl_surface *surface,
                               صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    SDL_پنجره_داده *پنجره_داده_2;

    // Check that this surface is valid.
    إذا (!surface) {
        أرجع;
    }

    Wayland_Seat_جمع_کن_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    پنجره_داده_2 = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);

    إذا (پنجره_داده_2 && پنجره_داده_2->surface == surface) {
        عائم x, y;

        إذا (پنجره_داده_2->current.logical_عرض <= 1) {
            x = 0.5f;
        } وإلا {
            x = (عائم)wl_fixed_مقصد_double(fx) / (پنجره_داده_2->current.logical_عرض - 1);
        }
        إذا (پنجره_داده_2->current.logical_ارتفاع <= 1) {
            y = 0.5f;
        } وإلا {
            y = (عائم)wl_fixed_مقصد_double(fy) / (پنجره_داده_2->current.logical_ارتفاع - 1);
        }

        ++پنجره_داده_2->فعال_touch_شمار;
        SDL_مجموعه_Mouse_Focus(پنجره_داده_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), پنجره_داده_2->sdlwindow, SDL_EVENT_FINGER_پایین, x, y, 1.0f);
    }
}

ساكن فراغ touch_handler_به_بالا(فراغ *داده, بنية wl_touch *touch, uint32_t serial, uint32_t timestamp, صحيح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    wl_fixed_t fx = 0, fy = 0;
    بنية wl_surface *surface = عدم;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    إذا (surface) {
        SDL_پنجره_داده *پنجره_داده_2 = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);

        إذا (پنجره_داده_2 && پنجره_داده_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_مقصد_double(fx) / پنجره_داده_2->current.logical_عرض;
            ثابت عائم y = (عائم)wl_fixed_مقصد_double(fy) / پنجره_داده_2->current.logical_ارتفاع;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), پنجره_داده_2->sdlwindow, SDL_EVENT_FINGER_به_بالا, x, y, 0.0f);

            --پنجره_داده_2->فعال_touch_شمار;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == پنجره_داده_2->sdlwindow && !پنجره_داده_2->keyboard_focus_شمار &&
                !پنجره_داده_2->اشاره_گر_focus_شمار && !پنجره_داده_2->فعال_touch_شمار) {
                SDL_مجموعه_Mouse_Focus(عدم);
            }
        }
    }
}

ساكن فراغ touch_handler_motion(فراغ *داده, بنية wl_touch *touch, uint32_t timestamp, صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    بنية wl_surface *surface = عدم;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    إذا (surface) {
        SDL_پنجره_داده *پنجره_داده_2 = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);

        إذا (پنجره_داده_2 && پنجره_داده_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_مقصد_double(fx) / پنجره_داده_2->current.logical_عرض;
            ثابت عائم y = (عائم)wl_fixed_مقصد_double(fy) / پنجره_داده_2->current.logical_ارتفاع;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), پنجره_داده_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ساكن فراغ touch_handler_قاب(فراغ *داده, بنية wl_touch *touch)
{
}

ساكن فراغ touch_handler_cancel(فراغ *داده, بنية wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    SDL_Wayland_Touch_نقطه *tp, *موقت;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_امن (tp, موقت, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ساكن فراغ touch_handler_shape(فراغ *داده, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ساكن فراغ touch_handler_orientation(فراغ *داده, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ساكن ثابت بنية wl_touch_listener touch_listener = {
    touch_handler_پایین,
    touch_handler_به_بالا,
    touch_handler_motion,
    touch_handler_قاب,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#إذا !SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
ساكن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کلید, xkb_layout_شاخص_t layout, xkb_level_شاخص_t level, xkb_mod_ماسک_t *masks_بیرون, size_t masks_اندازه)
{
    إذا (!masks_بیرون || !masks_اندازه) {
        أرجع 0;
    }

    // Level 0 is always unmodified, so early out.
    إذا (level == 0) {
        *masks_بیرون = 0;
        أرجع 1;
    }

    size_t ماسک_idx = 0;
    ثابت xkb_mod_ماسک_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.لغزش_ماسک,
        seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.لغزش_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level3_ماسک,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.لغزش_ماسک,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.لغزش_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level5_ماسک,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.لغزش_ماسک,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.لغزش_ماسک | seat->keyboard.xkb.caps_ماسک_2
    };
    ثابت xkb_mod_ماسک_t pressed_mod_ماسک = seat->keyboard.xkb.لغزش_ماسک | seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.level5_ماسک;
    ثابت xkb_mod_ماسک_t locked_mod_ماسک = seat->keyboard.xkb.caps_ماسک_2;

    لكل (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_ماسک, 0, keymod_masks[i] & locked_mod_ماسک, 0, 0, layout);
        إذا (WAYLAND_xkb_state_کلید_get_level(seat->keyboard.xkb.state, کلید, layout) == level) {
            masks_بیرون[ماسک_idx] = keymod_masks[i];

            إذا (++ماسک_idx == masks_اندازه) {
                اكسر;
            }
        }
    }

    أرجع ماسک_idx;
}
#پایان_اگر

ساكن فراغ Wayland_KeymapIterator(بنية xkb_keymap *keymap, xkb_keycode_t کلید, فراغ *داده)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_ماسک_t xkb_valid_mod_ماسک = seat->keyboard.xkb.لغزش_ماسک |
                                              seat->keyboard.xkb.alt_ماسک |
                                              seat->keyboard.xkb.level3_ماسک |
                                              seat->keyboard.xkb.level5_ماسک |
                                              seat->keyboard.xkb.caps_ماسک_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلید - 8);
    }

    لكل (xkb_layout_شاخص_t layout = 0; layout < seat->keyboard.xkb.رقم_layouts; ++layout) {
        ثابت xkb_level_شاخص_t رقم_سطوح = WAYLAND_xkb_keymap_رقم_سطوح_for_کلید(seat->keyboard.xkb.keymap, کلید, layout);
        لكل (xkb_level_شاخص_t level = 0; level < رقم_سطوح; ++level) {
            إذا (WAYLAND_xkb_keymap_کلید_get_syms_by_level(seat->keyboard.xkb.keymap, کلید, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                إذا (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_کلید_Sym(syms[0], کلید);
                    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                        استمر;
                    }
                }

                xkb_mod_ماسک_t xkb_mod_masks[16];
#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
                ثابت size_t رقم_masks = WAYLAND_xkb_keymap_کلید_get_mods_for_level(seat->keyboard.xkb.keymap, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وإلا
                ثابت size_t رقم_masks = xkb_legacy_get_mods_for_level(seat, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#پایان_اگر
                لكل (size_t ماسک = 0; ماسک < رقم_masks; ++ماسک) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    إذا ((xkb_mod_masks[ماسک] | xkb_valid_mod_ماسک) != xkb_valid_mod_ماسک) {
                        استمر;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[ماسک] & seat->keyboard.xkb.لغزش_ماسک ? SDL_KMOD_لغزش : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.alt_ماسک ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.level3_ماسک ? SDL_KMOD_نما : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.level5_ماسک ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.caps_ماسک_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کلید_کد_From_کلید_Sym(syms[0], کلید, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    إذا (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_بعدی_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        إذا (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_مجموعه_Keymap_مدخل(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کلید *res = WAYLAND_wl_array_جمع_کن(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_کلید));
                        إذا (res) {
                            res->scancode = scancode;
                            res->کلید = کلید - 8;
                        }
                    }

                    إذا (!keycode) {
                        بدل (scancode) {
                        حالة SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            اكسر;
                        حالة SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            اكسر;
                        حالة SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            اكسر;
                        حالة SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            اكسر;
                        افتراضي:
                            keycode = SDL_SCANCODE_مقصد_KEYCODE(scancode);
                            اكسر;
                        }
                    }

                    SDL_مجموعه_Keymap_مدخل(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساكن فراغ keyboard_handle_keymap(فراغ *داده, بنية wl_keyboard *keyboard,
                                   uint32_t format, صحيح fd, uint32_t اندازه)
{
    SDL_WaylandSeat *seat = داده;
    حرف *map_str;

    إذا (!داده) {
        close(fd);
        أرجع;
    }

    إذا (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        أرجع;
    }

    map_str = mmap(عدم, اندازه, PROT_READ, MAP_PRIVATE, fd, 0);
    إذا (map_str == MAP_FAILED) {
        close(fd);
        أرجع;
    }

    إذا (seat->keyboard.xkb.keymap != عدم) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = عدم;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_متن_V1,
                                                                   0);
    munmap(map_str, اندازه);
    close(fd);

    إذا (!seat->keyboard.xkb.keymap) {
        SDL_مجموعه_Error("failed to compile keymap");
        أرجع;
    }

    // Clear the old layouts.
    لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = عدم;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.رقم_layouts = 0;

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 10, 0)
    seat->keyboard.xkb.لغزش_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_لغزش);
    seat->keyboard.xkb.ctrl_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.رقم_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_رقم);
    seat->keyboard.xkb.caps_ماسک_2 = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وإلا
#تعریف_کن GET_MOD_شاخص(mod) \
    WAYLAND_xkb_keymap_mod_get_شاخص(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.لغزش_ماسک = 1 << GET_MOD_شاخص(لغزش_2);
    seat->keyboard.xkb.ctrl_ماسک = 1 << GET_MOD_شاخص(CTRL);
    seat->keyboard.xkb.alt_ماسک = 1 << GET_MOD_شاخص(ALT);
    seat->keyboard.xkb.gui_ماسک = 1 << GET_MOD_شاخص(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_ماسک = 1 << GET_MOD_شاخص(MOD5);
    seat->keyboard.xkb.level5_ماسک = 1 << GET_MOD_شاخص(MOD3);
    seat->keyboard.xkb.رقم_ماسک = 1 << GET_MOD_شاخص(رقم_2);
    seat->keyboard.xkb.caps_ماسک_2 = 1 << GET_MOD_شاخص(CAPS);
#لغو_تعریف GET_MOD_شاخص
#پایان_اگر

    إذا (seat->keyboard.xkb.state != عدم) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = عدم;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    إذا (!seat->keyboard.xkb.state) {
        SDL_مجموعه_Error("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = عدم;
        أرجع;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == عدم;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.رقم_layouts = WAYLAND_xkb_keymap_رقم_layouts(seat->keyboard.xkb.keymap);
    إذا (seat->keyboard.xkb.رقم_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.رقم_layouts, حجم(SDL_Keymap *));
        إذا (!seat->keyboard.sdl_keymap) {
            أرجع;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            إذا (!seat->keyboard.sdl_keymap[i]) {
                لكل (xkb_layout_شاخص_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = عدم;
                أرجع;
            }
        }

        WAYLAND_xkb_keymap_کلید_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_مجموعه_Keymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    ثابت حرف *locale = SDL_getenv("LC_ALL");
    إذا (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        إذا (!locale) {
            locale = SDL_getenv("LANG");
            إذا (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    إذا (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        إذا (seat->keyboard.xkb.compose_جدول != عدم) {
            WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
            seat->keyboard.xkb.compose_جدول = عدم;
        }
        seat->keyboard.xkb.compose_جدول = WAYLAND_xkb_compose_جدول_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        إذا (seat->keyboard.xkb.compose_جدول) {
            // Set up XKB compose state
            إذا (seat->keyboard.xkb.compose_state != عدم) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = عدم;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_جدول,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            إذا (!seat->keyboard.xkb.compose_state) {
                SDL_مجموعه_Error("could not create XKB compose state");
                WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
                seat->keyboard.xkb.compose_جدول = عدم;
            }
        }
    } وإلا إذا (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
ساكن SDL_Scancode Wayland_Get_Scancode_For_کلید(SDL_WaylandSeat *seat, Uint32 کلید, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلید);

        // No table entry? Check the reserved list.
        إذا (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_کلید *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                إذا (i->کلید == کلید) {
                    أرجع i->scancode;
                }
            }
        }
    } وإلا {
        ثابت xkb_keysym_t *keysym;
        إذا (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_کلید_Sym(keysym[0], کلید + 8);
            إذا (syms) {
                *syms = keysym;
            }
        }
    }

    أرجع scancode;
}

ساكن فراغ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool کلید_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    إذا (!کلید_pressed) {
        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.لغزش_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_لغزش)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_لغزش;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_لغزش;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_نما)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_نما;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_نما;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } وإلا {
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
    ثابت xkb_mod_ماسک_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.لغزش_ماسک) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_لغزش) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_لغزش;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_لغزش);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_لغزش)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_لغزش;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_لغزش;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_ماسک) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.alt_ماسک) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.gui_ماسک) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level3_ماسک) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_نما;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_نما;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level5_ماسک) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    إذا (xkb_locked_modifiers & seat->keyboard.xkb.caps_ماسک_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.رقم_ماسک) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_رقم;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_رقم;
    }

    SDL_مجموعه_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساكن فراغ Wayland_Handle_Modifier_کلیدها(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    بدل (keycode) {
    حالة SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        اكسر;
    حالة SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        اكسر;
    حالة SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        اكسر;
    حالة SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        اكسر;
    حالة SDLK_LALT:
        mod = SDL_KMOD_LALT;
        اكسر;
    حالة SDLK_RALT:
        mod = SDL_KMOD_RALT;
        اكسر;
    حالة SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        اكسر;
    حالة SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        اكسر;
    حالة SDLK_نما:
        mod = SDL_KMOD_نما;
        اكسر;
    حالة SDLK_LEVEL5_لغزش:
        mod = SDL_KMOD_LEVEL5;
        اكسر;
    افتراضي:
        أرجع;
    }

    إذا (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } وإلا {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

ساكن فراغ keyboard_handle_enter(فراغ *داده, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface,
                                  بنية wl_array *کلیدها)
{
    SDL_WaylandSeat *seat = داده;
    uint32_t *کلید;

    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_پنجره_داده *پنجره = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);
    إذا (!پنجره) {
        // Not a surface owned by SDL.
        أرجع;
    }

    ++پنجره->keyboard_focus_شمار;
    seat->keyboard.focus = پنجره;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_مجموعه_Keyboard_Focus(پنجره->sdlwindow->keyboard_focus ? پنجره->sdlwindow->keyboard_focus : پنجره->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشاره_گر_Grabs(seat->display, پنجره);

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_درون_داد(seat);

#اگر_تعریف_شده SDL_USE_IME
    إذا (!seat->متن_درون_داد.zwp_متن_درون_داد) {
        SDL_IME_مجموعه_Focus(true);
    }
#پایان_اگر

    Uint64 timestamp = SDL_GetTicksNS();
    پنجره->آخرین_focus_event_زمان_ns = timestamp;

    Wayland_Seat_مجموعه_Keymap(seat);

    wl_array_for_each (کلید, کلیدها) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, *کلید, عدم);
        إذا (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_کلید_From_Scancode(scancode, SDL_KMOD_NONE, false);

            بدل (keycode) {
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_نما:
            حالة SDLK_LEVEL5_لغزش:
                Wayland_Handle_Modifier_کلیدها(seat, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کلید, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        }
    }
}

ساكن فراغ keyboard_handle_leave(فراغ *داده, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;

    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_پنجره_داده *پنجره = Wayland_Get_پنجره_داده_For_Owned_Surface(surface);
    إذا (!پنجره) {
        // Not a surface owned by SDL.
        أرجع;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کلید = 0;

    SDL_پنجره *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    طالما (keyboard_focus && SDL_پنجره_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->والد;
    }

    ثابت bool had_focus = keyboard_focus && پنجره->sdlwindow == keyboard_focus;
    seat->keyboard.focus = عدم;
    --پنجره->keyboard_focus_شمار;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    إذا (!پنجره->keyboard_focus_شمار && had_focus) {
        SDL_مجموعه_Keyboard_Focus(عدم);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشاره_گر_Grabs(seat->display, پنجره);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_درون_داد(seat);

#اگر_تعریف_شده SDL_USE_IME
    إذا (!seat->متن_درون_داد.zwp_متن_درون_داد && !پنجره->keyboard_focus_شمار) {
        SDL_IME_مجموعه_Focus(false);
    }
#پایان_اگر

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    إذا (SDL_GetMouseFocus() == پنجره->sdlwindow && !پنجره->اشاره_گر_focus_شمار && !پنجره->فعال_touch_شمار) {
        SDL_مجموعه_Mouse_Focus(عدم);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_داده_Device_مجموعه_Selection_Offer(seat->داده_device, عدم);
}

ساكن bool keyboard_درون_داد_get_متن(حرف متن[8], ثابت SDL_WaylandSeat *seat, uint32_t کلید, bool پایین, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    إذا (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        أرجع false;
    }

    // TODO: Can this happen?
    إذا (WAYLAND_xkb_state_کلید_get_syms(seat->keyboard.xkb.state, کلید + 8, &syms) != 1) {
        أرجع false;
    }
    sym = syms[0];

#اگر_تعریف_شده SDL_USE_IME
    إذا (SDL_IME_Process_کلید_Event(sym, کلید + 8, پایین)) {
        إذا (handled_by_ime) {
            *handled_by_ime = true;
        }
        أرجع true;
    }
#پایان_اگر

    إذا (!پایین) {
        أرجع false;
    }

    إذا (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        بدل (WAYLAND_xkb_compose_state_get_وضعیت(seat->keyboard.xkb.compose_state)) {
        حالة XKB_COMPOSE_COMPOSING:
            إذا (handled_by_ime) {
                *handled_by_ime = true;
            }
            أرجع true;
        حالة XKB_COMPOSE_CANCELLED:
        افتراضي:
            sym = XKB_کلید_No_نماد;
            اكسر;
        حالة XKB_COMPOSE_NOTHING:
            اكسر;
        حالة XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            اكسر;
        }
    }

    أرجع WAYLAND_xkb_keysym_مقصد_utf8(sym, متن, 8) > 0;
}

ساكن فراغ keyboard_handle_کلید(فراغ *داده, بنية wl_keyboard *keyboard,
                                uint32_t serial, uint32_t زمان, uint32_t کلید,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = داده;
    تعداد wl_keyboard_کلید_state state = state_w;
    حرف متن[8];
    bool has_متن = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, زمان);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    إذا (state == WL_KEYBOARD_کلید_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        إذا (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            أرجع;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کلید_STATE_PRESSED;
    }

    Wayland_Seat_مجموعه_Keymap(seat);

    إذا (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        SDL_پنجره *keyboard_focus = SDL_GetKeyboardFocus();
        إذا (keyboard_focus && SDL_متن_درون_داد_فعال(keyboard_focus)) {
            has_متن = keyboard_درون_داد_get_متن(متن, seat, کلید, true, &handled_by_ime);
        }
    } وإلا {
        إذا (کلید == seat->keyboard.repeat.کلید) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_مقصد_NS(زمان - seat->keyboard.repeat.wl_press_زمان_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کلید = 0;
        }
        keyboard_درون_داد_get_متن(متن, seat, کلید, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = عدم;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, کلید, &syms);
    Wayland_Handle_Modifier_کلیدها(seat, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    إذا (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کلید_Sym_مقصد_Ucs4(syms[0]);
        إذا (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_ماسک) {
                scancode = SDL_Get_Keymap_بعدی_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_مجموعه_Keymap_مدخل(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, کلید, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    إذا (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        إذا (handled_by_ime) {
            has_متن = false;
        }
        إذا (has_متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(متن);
        }
        إذا (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            keyboard_repeat_مجموعه(&seat->keyboard.repeat, seat->keyboard.sdl_id, کلید, زمان, timestamp_ns, scancode, has_متن ? متن : عدم);
        }
    }
}

ساكن فراغ keyboard_handle_modifiers(فراغ *داده, بنية wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t گروه)
{
    SDL_WaylandSeat *seat = داده;
    ثابت uint32_t قبلی_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = گروه;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    إذا (!seat->keyboard.xkb.state) {
        أرجع;
    }

    WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, گروه);

    // If a key is repeating, update the text to apply the modifier.
    إذا (seat->keyboard.repeat.کلید) {
        حرف متن[8];

        إذا (keyboard_درون_داد_get_متن(متن, seat, seat->keyboard.repeat.کلید, true, عدم)) {
            SDL_strlcpy(seat->keyboard.repeat.متن, متن, SDL_arraysize(seat->keyboard.repeat.متن));
        }
    }

    إذا (گروه != قبلی_layout) {
        Wayland_Seat_مجموعه_Keymap(seat);

        إذا (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ساكن فراغ keyboard_handle_repeat_info(فراغ *داده, بنية wl_keyboard *wl_keyboard,
                                        int32_t نرخ, int32_t delay)
{
    SDL_WaylandSeat *seat = داده;
    seat->keyboard.repeat.repeat_نرخ = نرخ;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    إذا (!نرخ) {
        seat->keyboard.repeat.کلید = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ساكن ثابت بنية wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_کلید,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ساكن فراغ Wayland_Seat_Destroy_اشاره_گر(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->اشاره_گر_2.cursor_state);

    // End any active gestures.
    إذا (seat->اشاره_گر_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_انتها, 0, seat->اشاره_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    إذا (seat->اشاره_گر_2.focus) {
        seat->اشاره_گر_2.pending_قاب.leave_surface = seat->اشاره_گر_2.focus->surface;
        اشاره_گر_dispatch_leave(seat, false);
        seat->اشاره_گر_2.pending_قاب.leave_surface = عدم;
    }

    SDL_RemoveMouse(seat->اشاره_گر_2.sdl_id);

    إذا (seat->اشاره_گر_2.confined_اشاره_گر) {
        zwp_confined_اشاره_گر_v1_destroy(seat->اشاره_گر_2.confined_اشاره_گر);
    }

    إذا (seat->اشاره_گر_2.locked_اشاره_گر) {
        zwp_locked_اشاره_گر_v1_destroy(seat->اشاره_گر_2.locked_اشاره_گر);
    }

    إذا (seat->اشاره_گر_2.relative_اشاره_گر) {
        zwp_relative_اشاره_گر_v1_destroy(seat->اشاره_گر_2.relative_اشاره_گر);
    }

    إذا (seat->اشاره_گر_2.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->اشاره_گر_2.timestamps);
    }

    إذا (seat->اشاره_گر_2.gesture_pinch) {
        zwp_اشاره_گر_gesture_pinch_v1_destroy(seat->اشاره_گر_2.gesture_pinch);
    }

    إذا (seat->اشاره_گر_2.wl_اشاره_گر) {
        إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) >= WL_اشاره_گر_RELEASE_SINCE_نسخه) {
            wl_اشاره_گر_release(seat->اشاره_گر_2.wl_اشاره_گر);
        } وإلا {
            wl_اشاره_گر_destroy(seat->اشاره_گر_2.wl_اشاره_گر);
        }
    }

    SDL_zero(seat->اشاره_گر_2);
}

ساكن فراغ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    إذا (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    إذا (seat->keyboard.sdl_keymap) {
        إذا (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.رقم_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_مجموعه_Mod_State(SDL_KMOD_NONE);
        }
        لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.رقم_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = عدم;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    إذا (seat->keyboard.کلید_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
    }

    إذا (seat->keyboard.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    إذا (seat->keyboard.wl_keyboard) {
        إذا (wl_keyboard_get_نسخه(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_نسخه) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } وإلا {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    إذا (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    إذا (seat->keyboard.xkb.compose_جدول) {
        WAYLAND_xkb_compose_جدول_unref(seat->keyboard.xkb.compose_جدول);
    }

    إذا (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    إذا (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

ساكن فراغ Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    إذا (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    إذا (seat->touch.timestamps) {
        zwp_درون_داد_timestamps_v1_destroy(seat->touch.timestamps);
    }

    إذا (seat->touch.wl_touch) {
        إذا (wl_touch_get_نسخه(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_نسخه) {
            wl_touch_release(seat->touch.wl_touch);
        } وإلا {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ساكن فراغ seat_handle_capabilities(فراغ *داده, بنية wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    حرف name_fmt[256];

    إذا ((capabilities & WL_SEAT_CAPABILITY_اشاره_گر) && !seat->اشاره_گر_2.wl_اشاره_گر) {
        seat->اشاره_گر_2.wl_اشاره_گر = wl_seat_get_اشاره_گر(wl_seat);
        SDL_zero(seat->اشاره_گر_2.pending_قاب.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_اشاره_گر_مجموعه_user_داده(seat->اشاره_گر_2.wl_اشاره_گر, seat);
        wl_اشاره_گر_جمع_کن_listener(seat->اشاره_گر_2.wl_اشاره_گر, &اشاره_گر_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_اشاره_گر_Gestures(seat);

        seat->اشاره_گر_2.sdl_id = SDL_Get_بعدی_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_اشاره_گر_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_اشاره_گر_NAME, seat->اشاره_گر_2.sdl_id);
        }

        SDL_جمع_کن_Mouse(seat->اشاره_گر_2.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_اشاره_گر) && seat->اشاره_گر_2.wl_اشاره_گر) {
        Wayland_Seat_Destroy_اشاره_گر(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_مجموعه_user_داده(seat->touch.wl_touch, seat);
        wl_touch_جمع_کن_listener(seat->touch.wl_touch, &touch_listener, seat);

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_جمع_کن_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_مستقیم, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_مجموعه_user_داده(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_جمع_کن_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_بعدی_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_جمع_کن_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_ثبات_درون_داد_Timestamp_Listeners(seat);
}

ساكن فراغ seat_handle_name(فراغ *داده, بنية wl_seat *wl_seat, ثابت حرف *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;

    إذا (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ساكن ثابت بنية wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ساكن فراغ داده_offer_handle_offer(فراغ *داده, بنية wl_داده_offer *wl_داده_offer,
                                    ثابت حرف *mime_type)
{
    SDL_Wayland_داده_Offer *offer = داده;
    Wayland_داده_Offer_جمع_کن_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_داده_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_داده_offer) : -1),
                 mime_type);
}

ساكن فراغ داده_offer_handle_منبع_actions(فراغ *داده, بنية wl_داده_offer *wl_داده_offer,
                                             uint32_t منبع_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_داده_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_داده_offer) : -1),
                 منبع_actions);
}

ساكن فراغ داده_offer_handle_actions(فراغ *داده, بنية wl_داده_offer *wl_داده_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_داده_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_داده_offer) : -1),
                 dnd_action);
}

ساكن ثابت بنية wl_داده_offer_listener داده_offer_listener = {
    داده_offer_handle_offer,
    داده_offer_handle_منبع_actions, // Version 3
    داده_offer_handle_actions,        // Version 3
};

ساكن فراغ primary_selection_offer_handle_offer(فراغ *داده, بنية zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = داده;
    Wayland_Primary_Selection_Offer_جمع_کن_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ساكن ثابت بنية zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ساكن فراغ داده_device_handle_داده_offer(فراغ *داده, بنية wl_داده_device *wl_داده_device,
                                          بنية wl_داده_offer *id)
{
    SDL_Wayland_داده_Offer *داده_offer = SDL_calloc(1, حجم(*داده_offer));
    إذا (داده_offer) {
        SDL_Wayland_داده_Device *داده_device = (SDL_Wayland_داده_Device *)داده;
        داده_offer->offer = id;
        داده_offer->داده_device = داده_device;
        داده_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(داده_offer->mimes));
        wl_داده_offer_مجموعه_user_داده(id, داده_offer);
        wl_داده_offer_جمع_کن_listener(id, &داده_offer_listener, داده_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
    }
}

ساكن فراغ داده_device_handle_enter(فراغ *داده, بنية wl_داده_device *wl_داده_device,
                                     uint32_t serial, بنية wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, بنية wl_داده_offer *id)
{
    SDL_Wayland_داده_Device *داده_device = داده;
    SDL_پنجره_داده *پنجره = surface ? Wayland_Get_پنجره_داده_For_Owned_Surface(surface) : عدم;
    داده_device->has_mime_file = false;
    داده_device->متن_mime_type = عدم;

    داده_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    إذا (id) {
        داده_device->drag_offer = wl_داده_offer_get_user_داده(id);
    }

    إذا (داده_device->drag_offer && پنجره && پنجره->میپذیرد_drag_and_drop) {
#اگر_تعریف_شده SDL_USE_LIBDBUS
        إذا (Wayland_داده_Offer_Has_MIME(داده_device->drag_offer, FILE_PORTAL_MIME)) {
            داده_device->has_mime_file = true;
            wl_داده_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#پایان_اگر
        إذا (Wayland_داده_Offer_Has_MIME(داده_device->drag_offer, FILE_MIME)) {
            داده_device->has_mime_file = true;
            wl_داده_offer_accept(id, serial, FILE_MIME);
        }

        إذا (!داده_device->has_mime_file) {
            size_t mime_شمار = 0;
            ثابت حرف *ثابت *متن_mime_types = Wayland_Get_متن_Mime_Types(SDL_GetVideoDevice(), &mime_شمار);
            لكل (size_t i = 0; i < mime_شمار; ++i) {
                إذا (Wayland_داده_Offer_Has_MIME(داده_device->drag_offer, متن_mime_types[i])) {
                    داده_device->متن_mime_type = متن_mime_types[i];
                    wl_داده_offer_accept(id, serial, متن_mime_types[i]);
                    اكسر;
                }
            }
        }

        إذا (داده_device->has_mime_file || داده_device->متن_mime_type) {
            // SDL only supports "copy" style drag and drop
            إذا (wl_داده_offer_get_نسخه(داده_device->drag_offer->offer) >= WL_داده_OFFER_مجموعه_ACTIONS_SINCE_نسخه) {
                wl_داده_offer_مجموعه_actions(داده_device->drag_offer->offer, WL_داده_DEVICE_MANAGER_DND_ACTION_COPY, WL_داده_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            داده_device->dnd_پنجره = پنجره->sdlwindow;
            داده_device->dnd_surface = surface;
            مزدوج dx = wl_fixed_مقصد_double(x);
            مزدوج dy = wl_fixed_مقصد_double(y);

            // If over the mask, adjust the offset.
            إذا (surface == پنجره->ماسک.surface) {
                dx += (مزدوج)پنجره->ماسک.جابه_جایی_x;
                dy += (مزدوج)پنجره->ماسک.جابه_جایی_y;
            }

            dx *= پنجره->اشاره_گر_scale.x;
            dy *= پنجره->اشاره_گر_scale.y;

            SDL_SendDropPosition(داده_device->dnd_پنجره, (عائم)dx, (عائم)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id),
                         wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), SDL_Get_پنجره_ID(داده_device->dnd_پنجره), serial);
        } وإلا {
            // Decline the offer.
            wl_داده_offer_accept(id, serial, عدم);
            إذا (wl_داده_offer_get_نسخه(داده_device->drag_offer->offer) >= WL_داده_OFFER_مجموعه_ACTIONS_SINCE_نسخه) {
                wl_داده_offer_مجموعه_actions(داده_device->drag_offer->offer, WL_داده_DEVICE_MANAGER_DND_ACTION_NONE, WL_داده_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id), wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), serial);
        }
    } وإلا {
        داده_device->dnd_پنجره = عدم;
        داده_device->dnd_surface = عدم;

        // Decline the offer.
        إذا (id) {
            wl_داده_offer_accept(id, serial, عدم);
            إذا (wl_داده_offer_get_نسخه(داده_device->drag_offer->offer) >= WL_داده_OFFER_مجموعه_ACTIONS_SINCE_نسخه) {
                wl_داده_offer_مجموعه_actions(داده_device->drag_offer->offer, WL_داده_DEVICE_MANAGER_DND_ACTION_NONE, WL_داده_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1,
                     wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), serial);
    }
}

ساكن فراغ داده_device_handle_leave(فراغ *داده, بنية wl_داده_device *wl_داده_device)
{
    SDL_Wayland_داده_Device *داده_device = داده;

    إذا (داده_device->drag_offer) {
        إذا (داده_device->dnd_پنجره) {
            SDL_SendDropComplete(داده_device->dnd_پنجره);
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)داده_device->drag_offer->offer),
                         SDL_Get_پنجره_ID(داده_device->dnd_پنجره), داده_device->drag_serial);
        } وإلا {
            SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)داده_device->drag_offer->offer),
                         داده_device->drag_serial);
        }
        Wayland_داده_Offer_Destroy(داده_device->drag_offer);
        داده_device->drag_offer = عدم;
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    داده_device->has_mime_file = false;
    داده_device->متن_mime_type = عدم;
}

ساكن فراغ داده_device_handle_motion(فراغ *داده, بنية wl_داده_device *wl_داده_device,
                                      uint32_t زمان, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_داده_Device *داده_device = داده;

    إذا (داده_device->drag_offer && داده_device->dnd_پنجره && (داده_device->has_mime_file || داده_device->متن_mime_type)) {
        SDL_پنجره_داده *پنجره_داده_2 = داده_device->dnd_پنجره->داخلی;
        مزدوج dx = wl_fixed_مقصد_double(x);
        مزدوج dy = wl_fixed_مقصد_double(y);

        // If over the mask, adjust the offset.
        إذا (داده_device->dnd_surface == پنجره_داده_2->ماسک.surface) {
            dx += (مزدوج)پنجره_داده_2->ماسک.جابه_جایی_x;
            dy += (مزدوج)پنجره_داده_2->ماسک.جابه_جایی_y;
        }

        dx *= پنجره_داده_2->اشاره_گر_scale.x;
        dy *= پنجره_داده_2->اشاره_گر_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(داده_device->dnd_پنجره, (عائم)dx, (عائم)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)داده_device->drag_offer->offer),
                     wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y),
                     SDL_Get_پنجره_ID(داده_device->dnd_پنجره), داده_device->drag_serial);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_مقصد_int(x), wl_fixed_مقصد_int(y), -1);
    }
}

ساكن فراغ drop_cleanup_handler(فراغ *داده, بنية wl_callback *callback, uint32_t callback_داده)
{
    Wayland_Drop_داده *drop = (Wayland_Drop_داده *)داده;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ساكن ثابت بنية wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ساكن فراغ drop_dispatch_handler(فراغ *داده)
{
    Wayland_Drop_داده *drop = (Wayland_Drop_داده *)داده;
    SDL_Wayland_داده_Offer *offer = drop->offer;
    SDL_Wayland_داده_Device *داده_device = offer->داده_device;

    إذا (drop->dnd_پنجره) {
        size_t درازی;
        bool drop_handled = false;

#اگر_تعریف_شده SDL_USE_LIBDBUS
        إذا (Wayland_داده_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            فراغ *میانگیر_2 = Wayland_داده_Offer_Receive(offer, FILE_PORTAL_MIME, &درازی);
            إذا (میانگیر_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                إذا (dbus) {
                    صحيح مسیر_شمار = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(میانگیر_2, &مسیر_شمار);
                    // If dropped files contain a directory the list is empty
                    إذا (paths && مسیر_شمار > 0) {
                        لكل (صحيح i = 0; i < مسیر_شمار; i++) {
                            SDL_SendDropFile(drop->dnd_پنجره, عدم, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(میانگیر_2);
            }
        }
#پایان_اگر
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        إذا (!drop_handled) {
            إذا (Wayland_داده_Offer_Has_MIME(offer, FILE_MIME)) {
                فراغ *میانگیر_2 = Wayland_داده_Offer_Receive(offer, FILE_MIME, &درازی);
                إذا (میانگیر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)میانگیر_2, "\r\n", &saveptr);
                    طالما (token) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_پنجره, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(میانگیر_2);
                    drop_handled = true;
                }
            } وإلا إذا (Wayland_داده_Offer_Has_MIME(offer, drop->متن_mime_type)) {
                فراغ *میانگیر_2 = Wayland_داده_Offer_Receive(offer, drop->متن_mime_type, &درازی);
                إذا (میانگیر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)میانگیر_2, "\r\n", &saveptr);
                    طالما (token) {
                        SDL_Send_Drop_متن(drop->dnd_پنجره, token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(میانگیر_2);
                    drop_handled = true;
                }
            }
        }

        إذا (drop_handled && wl_داده_offer_get_نسخه(offer->offer) >= WL_داده_OFFER_پایان_SINCE_نسخه) {
            wl_داده_offer_پایان(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_پنجره);
    }

    Wayland_داده_Offer_Destroy(drop->offer);
    drop->offer = عدم;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(داده_device->seat->display->display);
    wl_callback_جمع_کن_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساكن فراغ داده_device_handle_drop(فراغ *داده, بنية wl_داده_device *wl_داده_device)
{
    SDL_Wayland_داده_Device *داده_device = داده;

    إذا (داده_device->drag_offer && داده_device->dnd_پنجره &&
        (داده_device->has_mime_file || داده_device->متن_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)داده_device->drag_offer->offer),
                     SDL_Get_پنجره_ID(داده_device->dnd_پنجره), داده_device->drag_serial);

        Wayland_کار_Thread_Context *ctx = داده_device->seat->display->کار_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_داده *drop = SDL_calloc(1, حجم(Wayland_Drop_داده));
        إذا (drop) {
            drop->offer = داده_device->drag_offer;
            drop->dnd_پنجره = داده_device->dnd_پنجره;
            drop->متن_mime_type = داده_device->متن_mime_type;

            WAYLAND_wl_list_درج(&داده_device->pending_drops, &drop->link);
            Wayland_کار_Thread_جمع_کن_کار(ctx, drop_dispatch_handler, drop, &drop->id);
        } وإلا {
            Wayland_داده_Offer_Destroy(داده_device->drag_offer);
        }
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_داده_Offer_Destroy(داده_device->drag_offer);
    }

    داده_device->drag_offer = عدم;
}

ساكن فراغ داده_device_handle_selection(فراغ *داده, بنية wl_داده_device *wl_داده_device,
                                         بنية wl_داده_offer *id)
{
    SDL_Wayland_داده_Device *داده_device = داده;
    SDL_Wayland_داده_Offer *offer = عدم;

    إذا (id) {
        offer = wl_داده_offer_get_user_داده(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));

    Wayland_داده_Device_مجموعه_Selection_Offer(داده_device, offer);
}

ساكن ثابت بنية wl_داده_device_listener داده_device_listener = {
    داده_device_handle_داده_offer,
    داده_device_handle_enter,
    داده_device_handle_leave,
    داده_device_handle_motion,
    داده_device_handle_drop,
    داده_device_handle_selection
};

ساكن فراغ primary_selection_device_handle_offer(فراغ *داده, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, حجم(*primary_selection_offer));
    إذا (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)داده;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_مجموعه_user_داده(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_جمع_کن_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن فراغ primary_selection_device_handle_selection(فراغ *داده, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = داده;
    SDL_WaylandPrimarySelectionOffer *offer = عدم;

    إذا (id) {
        offer = zwp_primary_selection_offer_v1_get_user_داده(id);
    }

    إذا (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن ثابت بنية zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساكن فراغ متن_درون_داد_enter(فراغ *داده,
                             بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_درون_داد_leave(فراغ *داده,
                             بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_درون_داد_preedit_string(فراغ *داده,
                                      بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                                      ثابت حرف *متن,
                                      int32_t cursor_begin,
                                      int32_t cursor_انتها)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    seat->متن_درون_داد.has_preedit = true;
    إذا (متن) {
        صحيح cursor_begin_utf8 = cursor_begin >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_begin) : -1;
        صحيح cursor_انتها_utf8 = cursor_انتها >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_انتها) : -1;
        صحيح cursor_اندازه_utf8;
        إذا (cursor_انتها_utf8 >= 0) {
            إذا (cursor_begin_utf8 >= 0) {
                cursor_اندازه_utf8 = cursor_انتها_utf8 - cursor_begin_utf8;
            } وإلا {
                cursor_اندازه_utf8 = cursor_انتها_utf8;
            }
        } وإلا {
            cursor_اندازه_utf8 = -1;
        }
        SDL_Send_Editing_متن(متن, cursor_begin_utf8, cursor_اندازه_utf8);
    } وإلا {
        SDL_Send_Editing_متن("", 0, 0);
    }
}

ساكن فراغ متن_درون_داد_commit_string(فراغ *داده,
                                     بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                                     ثابت حرف *متن)
{
    SDL_Send_Keyboard_متن(متن);
}

ساكن فراغ متن_درون_داد_delete_surrounding_متن(فراغ *داده,
                                               بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                                               uint32_t before_درازی,
                                               uint32_t after_درازی)
{
    // FIXME: Do we care about this event?
}

ساكن فراغ متن_درون_داد_انجامشده(فراغ *داده,
                            بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    إذا (!seat->متن_درون_داد.has_preedit) {
        SDL_Send_Editing_متن("", 0, 0);
    }
    seat->متن_درون_داد.has_preedit = false;
}

ساكن ثابت بنية zwp_متن_درون_داد_v3_listener متن_درون_داد_listener = {
    متن_درون_داد_enter,
    متن_درون_داد_leave,
    متن_درون_داد_preedit_string,
    متن_درون_داد_commit_string,
    متن_درون_داد_delete_surrounding_متن,
    متن_درون_داد_انجامشده
};

ساكن فراغ Wayland_داده_Device_مجموعه_ID(SDL_Wayland_داده_Device *داده_device)
{
    إذا (!داده_device->id_str)
#اگر_تعریف_شده SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        إذا (dbus) {
            ثابت حرف *id = dbus->bus_get_unique_name(dbus->session_conn);
            إذا (id) {
                داده_device->id_str = SDL_strdup(id);
            }
        }
    }
    إذا (!داده_device->id_str)
#پایان_اگر
    {
        حرف id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, حجم(id), "%" SDL_PRIu64, pid);
        داده_device->id_str = SDL_strdup(id);
    }
}

ساكن فراغ Wayland_Seat_Create_داده_Device(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->داده_device_manager) {
        أرجع;
    }

    SDL_Wayland_داده_Device *داده_device = SDL_calloc(1, حجم(*داده_device));
    إذا (!داده_device) {
        أرجع;
    }

    داده_device->داده_device = wl_داده_device_manager_get_داده_device(
        seat->display->داده_device_manager, seat->wl_seat);
    داده_device->seat = seat;

    إذا (!داده_device->داده_device) {
        SDL_free(داده_device);
        أرجع;
    }

    Wayland_داده_Device_مجموعه_ID(داده_device);
    WAYLAND_wl_list_init(&داده_device->pending_drops);
    wl_داده_device_مجموعه_user_داده(داده_device->داده_device, داده_device);
    wl_داده_device_جمع_کن_listener(داده_device->داده_device, &داده_device_listener, داده_device);
    seat->داده_device = داده_device;
}

فراغ Wayland_Display_Init_داده_Device_Manager(SDL_Video_داده *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_داده_Device(seat);
    }
}

ساكن فراغ Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->primary_selection_device_manager) {
        أرجع;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, حجم(*primary_selection_device));
    إذا (!primary_selection_device) {
        أرجع;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    إذا (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } وإلا {
        zwp_primary_selection_device_v1_مجموعه_user_داده(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_جمع_کن_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_داده *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ساكن فراغ Wayland_Seat_Create_متن_درون_داد(SDL_WaylandSeat *seat)
{
    إذا (seat->display->متن_درون_داد_manager) {
        seat->متن_درون_داد.zwp_متن_درون_داد = zwp_متن_درون_داد_manager_v3_get_متن_درون_داد(seat->display->متن_درون_داد_manager, seat->wl_seat);

        إذا (seat->متن_درون_داد.zwp_متن_درون_داد) {
            zwp_متن_درون_داد_v3_مجموعه_user_داده(seat->متن_درون_داد.zwp_متن_درون_داد, seat);
            zwp_متن_درون_داد_v3_جمع_کن_listener(seat->متن_درون_داد.zwp_متن_درون_داد,
                                           &متن_درون_داد_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_متن_درون_داد_Manager(SDL_Video_داده *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_متن_درون_داد(seat);
    }
}

// Pen/Tablet support...
ساكن فراغ tablet_tool_handle_type(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    بدل (type) {
        #تعریف_کن CASE(typ) حالة ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; أرجع
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #لغو_تعریف CASE
        افتراضي: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ساكن فراغ tablet_tool_handle_hardware_serial(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ساكن فراغ tablet_tool_handle_hardware_id_wacom(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->info.wacom_id = id_lo;
}

ساكن فراغ tablet_tool_handle_capability(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    بدل (capability) {
        #تعریف_کن CASE(wltyp,sdltyp) حالة ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; أرجع
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(فاصله_2, SDL_PEN_CAPABILITY_فاصله);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #لغو_تعریف CASE
        افتراضي: اكسر;  // unsupported here.
    }
}

ساكن فراغ tablet_tool_handle_انجامشده(فراغ *داده, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    إذا (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_پنجره *پنجره = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        sdltool->instance_id = SDL_جمع_کن_Pen_Device(0, عدم, پنجره, &sdltool->info, sdltool, false);
    }
}

ساكن فراغ tablet_tool_handle_removed(فراغ *داده, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    إذا (sdltool->instance_id) {
        SDL_پنجره *پنجره = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        SDL_RemovePenDevice(0, پنجره, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساكن فراغ tablet_tool_handle_proximity_درون(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, بنية zwp_tablet_v2 *tablet, بنية wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    SDL_پنجره_داده *windowdata = surface ? Wayland_Get_پنجره_داده_For_Owned_Surface(surface) : عدم;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : عدم;
    sdltool->proximity_serial = serial;
    sdltool->قاب.have_proximity = true;
    sdltool->قاب.درون_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساكن فراغ tablet_tool_handle_proximity_بیرون(فراغ *داده, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.have_proximity = true;
    sdltool->قاب.درون_proximity = false;
}

ساكن فراغ tablet_tool_handle_پایین(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.tool_state = WAYLAND_TABLET_TOOL_STATE_پایین;
}

ساكن فراغ tablet_tool_handle_به_بالا(فراغ *داده, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.tool_state = WAYLAND_TABLET_TOOL_STATE_به_بالا;
}

ساكن فراغ tablet_tool_handle_motion(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    SDL_پنجره_داده *windowdata = sdltool->focus;
    إذا (windowdata) {
        sdltool->قاب.x = (عائم)(wl_fixed_مقصد_double(sx_w) * windowdata->اشاره_گر_scale.x);
        sdltool->قاب.y = (عائم)(wl_fixed_مقصد_double(sy_w) * windowdata->اشاره_گر_scale.y);
        sdltool->قاب.have_motion = true;
    }
}

ساكن فراغ tablet_tool_handle_pressure(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.axes[SDL_PEN_AXIS_PRESSURE] = ((عائم) pressure) / 65535.0f;
    sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_PRESSURE);
    إذا (pressure) {
        sdltool->قاب.axes[SDL_PEN_AXIS_فاصله] = 0.0f;
        sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_فاصله);
    }
}

ساكن فراغ tablet_tool_handle_فاصله(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t فاصله)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.axes[SDL_PEN_AXIS_فاصله] = ((عائم) فاصله) / 65535.0f;
    sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_فاصله);
    إذا (فاصله) {
        sdltool->قاب.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساكن فراغ tablet_tool_handle_tilt(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.axes[SDL_PEN_AXIS_XTILT] = (عائم)(wl_fixed_مقصد_double(xtilt));
    sdltool->قاب.axes[SDL_PEN_AXIS_YTILT] = (عائم)(wl_fixed_مقصد_double(ytilt));
    sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ساكن فراغ tablet_tool_handle_button(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    صحيح sdlbutton;

    بدل (button) {
    حالة BTN_STYLUS:
        sdlbutton = 1;
        اكسر;
    حالة BTN_STYLUS2:
        sdlbutton = 2;
        اكسر;
    حالة BTN_STYLUS3:
        sdlbutton = 3;
        اكسر;
    افتراضي:
        أرجع;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->قاب.buttons)));
    sdltool->قاب.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_پایین : WAYLAND_TABLET_TOOL_BUTTON_به_بالا;
}

ساكن فراغ tablet_tool_handle_rotation(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    ثابت عائم rotation = (عائم)(wl_fixed_مقصد_double(degrees));
    sdltool->قاب.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساكن فراغ tablet_tool_handle_slider(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    sdltool->قاب.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->قاب.axes_مجموعه |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساكن فراغ tablet_tool_handle_wheel(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساكن فراغ tablet_tool_handle_قاب(فراغ *داده, بنية zwp_tablet_tool_v2 *tool, uint32_t زمان)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) داده;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    إذا (!instance_id) {
        أرجع;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_Adjust_Event_Timestamp_پایه(Wayland_EventTimestampMSToNS(زمان));
    SDL_پنجره *پنجره = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    إذا (sdltool->قاب.have_proximity && sdltool->قاب.درون_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, پنجره, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    إذا (sdltool->قاب.have_motion && sdltool->قاب.tool_state) {
        إذا (sdltool->قاب.tool_state == WAYLAND_TABLET_TOOL_STATE_پایین) {
            SDL_SendPenMotion(timestamp, instance_id, پنجره, sdltool->قاب.x, sdltool->قاب.y);
            SDL_SendPenTouch(timestamp, instance_id, پنجره, is_eraser, true);
        } وإلا {
            SDL_SendPenTouch(timestamp, instance_id, پنجره, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, پنجره, sdltool->قاب.x, sdltool->قاب.y);
        }
    } وإلا {
        إذا (sdltool->قاب.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, پنجره, is_eraser, sdltool->قاب.tool_state == WAYLAND_TABLET_TOOL_STATE_پایین);
        }

        إذا (sdltool->قاب.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, پنجره, sdltool->قاب.x, sdltool->قاب.y);
        }
    }

    لكل (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_شمار; i++) {
        إذا (sdltool->قاب.axes_مجموعه & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, پنجره, i, sdltool->قاب.axes[i]);
        }
    }

    لكل (صحيح i = 0; i < SDL_arraysize(sdltool->قاب.buttons); i++) {
        ثابت صحيح state = sdltool->قاب.buttons[i];
        إذا (state) {
            SDL_SendPenButton(timestamp, instance_id, پنجره, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_پایین);
        }
    }

    إذا (sdltool->قاب.have_proximity && !sdltool->قاب.درون_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, پنجره, false, false);
        sdltool->focus = عدم;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->قاب);
}

ساكن ثابت بنية zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_انجامشده,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_درون,
    tablet_tool_handle_proximity_بیرون,
    tablet_tool_handle_پایین,
    tablet_tool_handle_به_بالا,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_فاصله,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_قاب
};


ساكن فراغ tablet_seat_handle_tablet_added(فراغ *داده, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ساكن فراغ tablet_seat_handle_tool_added(فراغ *داده, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)داده;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, حجم(*sdltool));

    إذا (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.رقم_buttons = -1;

        إذا (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_درج(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_جمع_کن_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ساكن فراغ tablet_seat_handle_pad_added(فراغ *داده, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

ساكن ثابت بنية zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

ساكن فراغ Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_جمع_کن_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

فراغ Wayland_DisplayInitTabletManager(SDL_Video_داده *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

ساكن فراغ Wayland_remove_all_pens_callback(SDL_PenID instance_id, فراغ *handle, فراغ *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

ساكن فراغ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_پایین)
{
    إذا (!shutting_پایین) {
        SDL_WaylandPenTool *tool, *موقت;
        wl_list_for_each_امن (tool, موقت, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } وإلا {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, عدم);
    }

    إذا (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = عدم;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

فراغ Wayland_DisplayCreateSeat(SDL_Video_داده *display, بنية wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, حجم(SDL_WaylandSeat));
    إذا (!seat) {
        أرجع;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_درج(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_داده_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_متن_درون_داد(seat);

    wl_seat_مجموعه_user_داده(seat->wl_seat, seat);
    wl_seat_جمع_کن_listener(seat->wl_seat, &seat_listener, seat);

    إذا (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

فراغ Wayland_Display_Remove_پنجره_References_From_Seats(SDL_Video_داده *display, SDL_پنجره_داده *پنجره)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        إذا (seat->keyboard.focus == پنجره) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, پنجره->surface);
        }

        إذا (seat->اشاره_گر_2.focus == پنجره) {
            seat->اشاره_گر_2.pending_قاب.leave_surface = seat->اشاره_گر_2.focus->surface;
            اشاره_گر_dispatch_leave(seat, true);
            seat->اشاره_گر_2.pending_قاب.leave_surface = عدم;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_نقطه *tp, *موقت;
        wl_list_for_each_امن (tp, موقت, &seat->touch.points, link) {
            إذا (tp->surface == پنجره->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == پنجره) {
                tool->focus = عدم;
                Wayland_TabletToolUpdateCursor(tool);
                إذا (tool->instance_id) {
                    SDL_RemovePenDevice(0, پنجره->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_داده *drop, *drop_موقت;
        wl_list_for_each_امن (drop, drop_موقت, &seat->داده_device->pending_drops, link) {
            إذا (drop->dnd_پنجره == پنجره->sdlwindow) {
                Wayland_کار_Thread_Cancel_کار(display->کار_thread_context, drop->id);

                إذا (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_داده_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_پایین)
{
    إذا (!seat) {
        أرجع;
    }

    SDL_free(seat->name);

    إذا (seat->داده_device) {
        إذا (seat->داده_device->selection_offer) {
            Wayland_داده_Offer_Destroy(seat->داده_device->selection_offer);
        }
        إذا (seat->داده_device->selection_منبع) {
            Wayland_داده_منبع_Destroy(seat->داده_device->selection_منبع);
        }
        إذا (seat->داده_device->drag_offer) {
            Wayland_داده_Offer_Destroy(seat->داده_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_داده *drop, *drop_موقت;
        wl_list_for_each_امن (drop, drop_موقت, &seat->داده_device->pending_drops, link) {
            Wayland_کار_Thread_Cancel_کار(seat->display->کار_thread_context, drop->id);

            إذا (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_داده_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        إذا (seat->داده_device->داده_device) {
            إذا (wl_داده_device_get_نسخه(seat->داده_device->داده_device) >= WL_داده_DEVICE_RELEASE_SINCE_نسخه) {
                wl_داده_device_release(seat->داده_device->داده_device);
            } وإلا {
                wl_داده_device_destroy(seat->داده_device->داده_device);
            }
        }
        SDL_free(seat->داده_device->id_str);
        SDL_free(seat->داده_device);
    }

    إذا (seat->primary_selection_device) {
        إذا (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        إذا (seat->primary_selection_device->selection_منبع) {
            Wayland_Primary_Selection_منبع_Destroy(seat->primary_selection_device->selection_منبع);
        }
        إذا (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    إذا (seat->متن_درون_داد.zwp_متن_درون_داد) {
        zwp_متن_درون_داد_v3_destroy(seat->متن_درون_داد.zwp_متن_درون_داد);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_اشاره_گر(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_پایین);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_نسخه) {
        wl_seat_release(seat->wl_seat);
    } وإلا {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساكن فراغ Wayland_Seat_Update_Relative_اشاره_گر(SDL_WaylandSeat *seat)
{
    إذا (seat->display->relative_اشاره_گر_manager) {
        bool relative_focus = false;

        إذا (seat->اشاره_گر_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            إذا (seat->اشاره_گر_2.focus->sdlwindow->flags & SDL_پنجره_MOUSE_RELATIVE_نما) {
                إذا (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->اشاره_گر_2.focus;
                } وإلا {
                    relative_focus = seat->اشاره_گر_2.focus->keyboard_focus_شمار != 0;
                }
            } وإلا {
                relative_focus = SDL_GetMouse()->warp_emulation_فعال;
            }
        }

        إذا (relative_focus) {
            إذا (!seat->اشاره_گر_2.relative_اشاره_گر) {
                seat->اشاره_گر_2.relative_اشاره_گر = zwp_relative_اشاره_گر_manager_v1_get_relative_اشاره_گر(seat->display->relative_اشاره_گر_manager, seat->اشاره_گر_2.wl_اشاره_گر);
                zwp_relative_اشاره_گر_v1_جمع_کن_listener(seat->اشاره_گر_2.relative_اشاره_گر, &relative_اشاره_گر_listener, seat);
            }
        } وإلا إذا (seat->اشاره_گر_2.relative_اشاره_گر) {
            zwp_relative_اشاره_گر_v1_destroy(seat->اشاره_گر_2.relative_اشاره_گر);
            seat->اشاره_گر_2.relative_اشاره_گر = عدم;
        }
    }
}

ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_داده *display = seat->display;

    إذا (display->کلید_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        إذا (seat->keyboard.کلید_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
            seat->keyboard.کلید_inhibitor = عدم;
        }

        إذا (seat->keyboard.wl_keyboard) {
            SDL_پنجره_داده *w = seat->keyboard.focus;
            إذا (w) {
                SDL_پنجره *پنجره = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                إذا (پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED) {
                    seat->keyboard.کلید_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کلید_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

فراغ Wayland_Seat_Update_اشاره_گر_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_داده *display = seat->display;
    Wayland_Seat_Update_Relative_اشاره_گر(seat);

    إذا (display->اشاره_گر_constraints) {
        إذا (seat->اشاره_گر_2.locked_اشاره_گر && !seat->اشاره_گر_2.relative_اشاره_گر) {
            zwp_locked_اشاره_گر_v1_destroy(seat->اشاره_گر_2.locked_اشاره_گر);
            seat->اشاره_گر_2.locked_اشاره_گر = عدم;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_اشاره_گر_Cursor(seat);
        }

        إذا (seat->اشاره_گر_2.wl_اشاره_گر) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            إذا (seat->اشاره_گر_2.relative_اشاره_گر) {
                إذا (!seat->اشاره_گر_2.locked_اشاره_گر) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    إذا (seat->اشاره_گر_2.confined_اشاره_گر) {
                        zwp_confined_اشاره_گر_v1_destroy(seat->اشاره_گر_2.confined_اشاره_گر);
                        seat->اشاره_گر_2.confined_اشاره_گر = عدم;
                    }

                    seat->اشاره_گر_2.locked_اشاره_گر = zwp_اشاره_گر_constraints_v1_قفل_اشاره_گر(display->اشاره_گر_constraints,
                                                                                           seat->اشاره_گر_2.focus->surface,
                                                                                           seat->اشاره_گر_2.wl_اشاره_گر, عدم,
                                                                                           ZWP_اشاره_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشاره_گر_v1_جمع_کن_listener(seat->اشاره_گر_2.locked_اشاره_گر, &locked_اشاره_گر_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_اشاره_گر_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                أرجع;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            إذا (seat->اشاره_گر_2.confined_اشاره_گر) {
                zwp_confined_اشاره_گر_v1_destroy(seat->اشاره_گر_2.confined_اشاره_گر);
                seat->اشاره_گر_2.confined_اشاره_گر = عدم;
            }

            SDL_پنجره_داده *w = seat->اشاره_گر_2.focus;
            إذا (!w) {
                أرجع;
            }

            SDL_پنجره *پنجره = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            إذا (!(پنجره->flags & SDL_پنجره_درون_داد_FOCUS) ||
                (!(پنجره->flags & SDL_پنجره_MOUSE_GRABBED) && SDL_Rect_خالی(&پنجره->mouse_rect))) {
                أرجع;
            }

            بنية wl_region *confine_rect = عدم;
            إذا (!SDL_Rect_خالی(&پنجره->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(پنجره, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_جمع_کن(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                إذا (!SDL_نقطه_درون_Rect(&seat->اشاره_گر_2.آخرین_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحيح closest_x = seat->اشاره_گر_2.آخرین_motion.x;
                    صحيح closest_y = seat->اشاره_گر_2.آخرین_motion.y;

                    إذا (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } وإلا إذا (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    إذا (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } وإلا إذا (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            إذا (confine_rect || (پنجره->flags & SDL_پنجره_MOUSE_GRABBED)) {
                إذا (پنجره->mouse_rect.w != 1 && پنجره->mouse_rect.h != 1) {
                    seat->اشاره_گر_2.confined_اشاره_گر =
                        zwp_اشاره_گر_constraints_v1_confine_اشاره_گر(display->اشاره_گر_constraints,
                                                                   w->surface,
                                                                   seat->اشاره_گر_2.wl_اشاره_گر,
                                                                   confine_rect,
                                                                   ZWP_اشاره_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_اشاره_گر_v1_جمع_کن_listener(seat->اشاره_گر_2.confined_اشاره_گر,
                                                         &confined_اشاره_گر_listener,
                                                         seat);
                } وإلا {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->اشاره_گر_2.locked_اشاره_گر =
                        zwp_اشاره_گر_constraints_v1_قفل_اشاره_گر(display->اشاره_گر_constraints,
                                                                w->surface,
                                                                seat->اشاره_گر_2.wl_اشاره_گر,
                                                                عدم,
                                                                ZWP_اشاره_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشاره_گر_v1_جمع_کن_listener(seat->اشاره_گر_2.locked_اشاره_گر,
                                                       &locked_اشاره_گر_listener,
                                                       seat);
                }
                إذا (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

فراغ Wayland_Display_Update_اشاره_گر_Grabs(SDL_Video_داده *display, SDL_پنجره_داده *پنجره)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!پنجره || seat->اشاره_گر_2.focus == پنجره) {
            Wayland_Seat_Update_اشاره_گر_Grab(seat);
        }
    }
}

فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_داده *display, SDL_پنجره_داده *پنجره)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!پنجره || seat->keyboard.focus == پنجره) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    إذا (serial > seat->آخرین_implicit_grab_serial) {
        seat->آخرین_implicit_grab_serial = serial;
        seat->display->آخرین_implicit_grab_seat = seat;
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND
