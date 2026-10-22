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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

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

#جے_تعریف_شدہ HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جے_انت

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
#ضمن <linux/input.h>
#وإلا
#تعریف_کرو BTN_بایاں    (0x110)
#تعریف_کرو BTN_دایاں   (0x111)
#تعریف_کرو BTN_درمیان  (0x112)
#تعریف_کرو BTN_SIDE    (0x113)
#تعریف_کرو BTN_EXTRA   (0x114)
#تعریف_کرو BTN_STYLUS  (0x14b)
#تعریف_کرو BTN_STYLUS2 (0x14c)
#تعریف_کرو BTN_STYLUS3 (0x149)
#جے_انت
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/imKStoUCS.h"
#ضمن <errno.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>
#ضمن <xkbcommon/xkbcommon-compose.h>
#ضمن <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#تعریف_کرو WAYLAND_WHEEL_AXIS_UNIT 10

#جے_بنا_تعریف XKB_MOD_NAME_MOD3
#تعریف_کرو XKB_MOD_NAME_MOD3 "Mod3"
#جے_انت

#جے_بنا_تعریف XKB_MOD_NAME_MOD5
#تعریف_کرو XKB_MOD_NAME_MOD5 "Mod5"
#جے_انت

// Keyboard and mouse names to match XWayland
#تعریف_کرو WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#تعریف_کرو WAYLAND_DEFAULT_اشارہ_گر_NAME "Virtual core pointer"
#تعریف_کرو WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#تعریف_کرو WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_منزل_NS(10)

// Timer rollover detection thresholds
#تعریف_کرو WAYLAND_TIMER_ROLLOVER_INTERVAL_کم  (SDL_MAX_UINT32 / 16U)
#تعریف_کرو WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند (WAYLAND_TIMER_ROLLOVER_INTERVAL_کم * 15U)

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
} SDL_Wayland_Touch_نقطہ;

ساكن فراغ Wayland_Seat_جوڑو_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface *surface)
{
    SDL_Wayland_Touch_نقطہ *tp = SDL_malloc(حجم(SDL_Wayland_Touch_نقطہ));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_داخل_کرو(&seat->touch.points, &tp->link);
}

ساكن فراغ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_نقطہ *tp)
{
    إذا (tp->surface) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(tp->surface);

        إذا (کھڑکی_انکڑے_2) {
            ثابت عائم x = (عائم)(wl_fixed_منزل_double(tp->fx) / کھڑکی_انکڑے_2->current.logical_چوڑائی);
            ثابت عائم y = (عائم)(wl_fixed_منزل_double(tp->fy) / کھڑکی_انکڑے_2->current.logical_اچائی);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), کھڑکی_انکڑے_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --کھڑکی_انکڑے_2->سرگرم_touch_گنتی;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == کھڑکی_انکڑے_2->sdlwindow && !کھڑکی_انکڑے_2->keyboard_focus_گنتی &&
                !کھڑکی_انکڑے_2->اشارہ_گر_focus_گنتی && !کھڑکی_انکڑے_2->سرگرم_touch_گنتی) {
                SDL_سیٹ_Mouse_Focus(عدم);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساكن فراغ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface **surface)
{
    SDL_Wayland_Touch_نقطہ *tp;

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
    SDL_Wayland_Touch_نقطہ *tp;

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

ساكن فراغ Wayland_GetScaledMouseRect(SDL_کھڑکی *کھڑکی, SDL_Rect *scaled_rect)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = کھڑکی->اندرونی;

    scaled_rect->x = (صحيح)SDL_floor(کھڑکی->mouse_rect.x / کھڑکی_انکڑے_2->اشارہ_گر_scale.x);
    scaled_rect->y = (صحيح)SDL_floor(کھڑکی->mouse_rect.y / کھڑکی_انکڑے_2->اشارہ_گر_scale.y);
    scaled_rect->w = (صحيح)SDL_ceil(کھڑکی->mouse_rect.w / کھڑکی_انکڑے_2->اشارہ_گر_scale.x);
    scaled_rect->h = (صحيح)SDL_ceil(کھڑکی->mouse_rect.h / کھڑکی_انکڑے_2->اشارہ_گر_scale.y);
}

ساكن Uint64 Wayland_Adjust_Event_Timestamp_ادھار(Uint64 nsTimestamp)
{
    ساكن Uint64 timestamp_وتھ = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    إذا (!timestamp_وتھ) {
        timestamp_وتھ = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_وتھ;

    إذا (nsTimestamp > now) {
        timestamp_وتھ -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    أرجع nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساكن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساكن Uint64 timestamp_وتھ = 0;
    ساكن Uint32 آخری = 0;
    Uint64 timestamp = SDL_MS_منزل_NS(wl_timestamp_ms) + timestamp_وتھ;

    إذا (wl_timestamp_ms >= آخری) {
        إذا (timestamp_وتھ && آخری < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
        } وإلا {
            آخری = wl_timestamp_ms;
        }
    } وإلا {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        إذا (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_کم && آخری > WAYLAND_TIMER_ROLLOVER_INTERVAL_بلند) {
            timestamp_وتھ += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            آخری = wl_timestamp_ms;
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
    أرجع Wayland_Adjust_Event_Timestamp_ادھار(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن Uint64 Wayland_Get_اشارہ_گر_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_ادھار(seat->اشارہ_گر_2.timestamps ? seat->اشارہ_گر_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_ادھار(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن فراغ داخلہ_timestamp_listener(فراغ *انکڑے, بنية zwp_داخلہ_timestamps_v1 *zwp_داخلہ_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)انکڑے) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_فی_دوجا) + tv_nsec;
}

ساكن ثابت بنية zwp_داخلہ_timestamps_v1_listener timestamp_listener = {
    داخلہ_timestamp_listener
};

ساكن فراغ Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    إذا (seat->display->داخلہ_timestamps_manager) {
        إذا (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_داخلہ_timestamps_manager_v1_get_keyboard_timestamps(seat->display->داخلہ_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        إذا (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.timestamps) {
            seat->اشارہ_گر_2.timestamps = zwp_داخلہ_timestamps_manager_v1_get_اشارہ_گر_timestamps(seat->display->داخلہ_timestamps_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->اشارہ_گر_2.timestamps, &timestamp_listener, &seat->اشارہ_گر_2.highres_timestamp_ns);
        }

        إذا (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_داخلہ_timestamps_manager_v1_get_touch_timestamps(seat->display->داخلہ_timestamps_manager, seat->touch.wl_touch);
            zwp_داخلہ_timestamps_v1_جوڑو_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

فراغ Wayland_Display_Init_داخلہ_Timestamp_Manager(SDL_Video_انکڑے *display)
{
    إذا (display->داخلہ_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(seat);
        }
    }
}

ساكن فراغ handle_pinch_begin(فراغ *انکڑے, بنية zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t serial, uint32_t ویلا, بنية wl_surface *surface, uint32_t fingers)
{
    إذا (!surface) {
        أرجع;
    }

    SDL_کھڑکی_انکڑے *wind = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);
    إذا (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
        seat->اشارہ_گر_2.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_update(فراغ *انکڑے, بنية zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t ویلا,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;

    إذا (seat->اشارہ_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);
        ثابت عائم s = (عائم)wl_fixed_منزل_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->اشارہ_گر_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_سرا(فراغ *انکڑے, بنية zwp_اشارہ_گر_gesture_pinch_v1 *zwp_اشارہ_گر_gesture_pinch_v1, uint32_t serial, uint32_t ویلا, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;

    إذا (seat->اشارہ_گر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);
        SDL_SendPinch(SDL_EVENT_PINCH_سرا, timestamp, seat->اشارہ_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->اشارہ_گر_2.gesture_focus = عدم;
    }
}

ساكن ثابت بنية zwp_اشارہ_گر_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_سرا
};

ساكن فراغ Wayland_Seat_Create_اشارہ_گر_Gestures(SDL_WaylandSeat *seat)
{
    إذا (seat->display->zwp_اشارہ_گر_gestures) {
        إذا (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.gesture_pinch) {
            seat->اشارہ_گر_2.gesture_pinch = zwp_اشارہ_گر_gestures_v1_get_pinch_gesture(seat->display->zwp_اشارہ_گر_gestures, seat->اشارہ_گر_2.wl_اشارہ_گر);
            zwp_اشارہ_گر_gesture_pinch_v1_سیٹ_user_انکڑے(seat->اشارہ_گر_2.gesture_pinch, seat);
            zwp_اشارہ_گر_gesture_pinch_v1_جوڑو_listener(seat->اشارہ_گر_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_اشارہ_گر_Gesture_Manager(SDL_Video_انکڑے *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_اشارہ_گر_Gestures(seat);
    }
}

ساكن فراغ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    إذا (seat->display->cursor_shape_manager) {
        إذا (seat->اشارہ_گر_2.wl_اشارہ_گر && !seat->اشارہ_گر_2.cursor_state.cursor_shape) {
            seat->اشارہ_گر_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_اشارہ_گر(seat->display->cursor_shape_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            إذا (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

فراغ Wayland_DisplayInitCursorShapeManager(SDL_Video_انکڑے *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ساكن فراغ Wayland_Seat_سیٹ_Keymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    إذا (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_سیٹ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_سیٹ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساكن فراغ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    طالما (elapsed >= repeat_info->اگلا_repeat_ns) {
        إذا (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->ادھار_ویلا_ns + repeat_info->اگلا_repeat_ns;
            SDL_Send_Keyboard_کلید_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_ادھار(timestamp), repeat_info->keyboard_id, repeat_info->کلید, repeat_info->scancode, true);
        }
        إذا (repeat_info->متن[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(repeat_info->متن);
        }
        repeat_info->اگلا_repeat_ns += SDL_NS_فی_دوجا / (Uint64)repeat_info->repeat_شرح;
    }
}

ساكن فراغ keyboard_repeat_سیٹ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کلید, Uint32 wl_press_ویلا_ms,
                                Uint64 ادھار_ویلا_ns, uint32_t scancode, ثابت حرف *متن)
{
    إذا (!repeat_info->repeat_شرح) {
        أرجع;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کلید = کلید;
    repeat_info->wl_press_ویلا_ms = wl_press_ویلا_ms;
    repeat_info->ادھار_ویلا_ns = ادھار_ویلا_ns;
    repeat_info->sdl_press_ویلا_ns = SDL_GetTicksNS();
    repeat_info->اگلا_repeat_ns = SDL_MS_منزل_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    إذا (متن) {
        SDL_strlcpy(repeat_info->متن, متن, SDL_arraysize(repeat_info->متن));
    } وإلا {
        repeat_info->متن[0] = '\0';
    }
}

ساكن فراغ sync_پورا_handler(فراغ *انکڑے, بنية wl_callback *callback, uint32_t callback_انکڑے)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener sync_listener = {
    sync_پورا_handler
};

فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *d = _this->اندرونی;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    بنية wl_callback *cb = wl_display_sync(d->display);
    wl_callback_جوڑو_listener(cb, &sync_listener, عدم);
    WAYLAND_wl_display_flush(d->display);
}

صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_انکڑے *d = _this->اندرونی;
    SDL_WaylandSeat *seat;
    Uint64 شروع = SDL_GetTicksNS();
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret;
    bool poll_alarm_سیٹ = false;

#جے_تعریف_شدہ SDL_USE_IME
    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_داخلہ_manager && keyboard_focus && SDL_متن_داخلہ_سرگرم(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        إذا (timeoutNS < 0 || SDL_MS_منزل_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_منزل_NS(200);
            poll_alarm_سیٹ = true;
        }
    }
#جے_انت

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->keyboard.repeat.کلید) {
            ثابت Uint64 elapsed = شروع - seat->keyboard.repeat.sdl_press_ویلا_ns;
            ثابت Uint64 اگلا_repeat_wait_ویلا = (seat->keyboard.repeat.اگلا_repeat_ns - elapsed) + 1;
            إذا (timeoutNS < 0 || اگلا_repeat_wait_ویلا <= timeoutNS) {
                timeoutNS = اگلا_repeat_wait_ویلا;
                poll_alarm_سیٹ = true;
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
                أرجع poll_alarm_سیٹ ? 1 : 0;
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
    SDL_Video_انکڑے *d = _this->اندرونی;
    SDL_WaylandSeat *seat;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret = 0;

#جے_تعریف_شدہ SDL_USE_IME
    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_داخلہ_manager && keyboard_focus && SDL_متن_داخلہ_سرگرم(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#جے_انت

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#جے_انت

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
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_منزل_NS(4));
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
                Wayland_Seat_سیٹ_Keymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_ویلا_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    إذا (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساكن فراغ اشارہ_گر_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = seat->اشارہ_گر_2.focus;
    SDL_کھڑکی *کھڑکی = کھڑکی_انکڑے_2 ? کھڑکی_انکڑے_2->sdlwindow : عدم;

    إذا (کھڑکی_انکڑے_2) {
        مزدوج sx = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx);
        مزدوج sy = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy);

        إذا (seat->اشارہ_گر_2.focus_surface == کھڑکی_انکڑے_2->نقاب.surface) {
            sx += (مزدوج)کھڑکی_انکڑے_2->نقاب.وتھ_x;
            sy += (مزدوج)کھڑکی_انکڑے_2->نقاب.وتھ_y;
        }

        sx *= کھڑکی_انکڑے_2->اشارہ_گر_scale.x;
        sy *= کھڑکی_انکڑے_2->اشارہ_گر_scale.y;
        إذا (!warp) {
            SDL_SendMouseMotion(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی_انکڑے_2->sdlwindow, seat->اشارہ_گر_2.sdl_id, false, (عائم)sx, (عائم)sy);
        } وإلا {
            SDL_SendMouseWarp(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی_انکڑے_2->sdlwindow, seat->اشارہ_گر_2.sdl_id, (عائم)sx, (عائم)sy);
        }

        seat->اشارہ_گر_2.آخری_motion.x = (صحيح)SDL_floor(sx);
        seat->اشارہ_گر_2.آخری_motion.y = (صحيح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        إذا (!SDL_Rect_خالی_تھاواں(&کھڑکی->mouse_rect) && !seat->اشارہ_گر_2.is_confined) {
            Wayland_Seat_Update_اشارہ_گر_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        إذا (!(کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE) && کھڑکی->کامیابی_test) {
            SDL_کامیابی_Test_نتیجہ rc = کھڑکی->کامیابی_test(کھڑکی, &seat->اشارہ_گر_2.آخری_motion, کھڑکی->کامیابی_test_انکڑے);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            بدل (rc) {
            حالة SDL_HITTEST_RESIZE_TOPLEFT:
                إذا ((کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) &&
                    (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_RESIZE_بایاں;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_RESIZE_چوٹی;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_چوٹی:
                إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                إذا ((کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) &&
                    (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی) {
                    rc = SDL_HITTEST_RESIZE_دایاں;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_RESIZE_چوٹی;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_دایاں:
                إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                إذا ((کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_دایاں;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_دایاں) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOM:
                إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                إذا ((کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_بایاں;
                } وإلا إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_بایاں:
                إذا (کھڑکی_انکڑے_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_بایاں) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            افتراضي:
                اكسر;
            }

            إذا (rc != کھڑکی_انکڑے_2->کامیابی_test_نتیجہ) {
                کھڑکی_انکڑے_2->کامیابی_test_نتیجہ = rc;
                Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
            }
        }
    }
}

ساكن فراغ اشارہ_گر_handle_motion(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                  uint32_t ویلا, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    ثابت Uint64 timestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);

    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = sx;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = sy;

    إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        إذا (!seat->اشارہ_گر_2.pending_چوکھٹا.have_relative || seat->اشارہ_گر_2.timestamps) {
            seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = timestamp;
        }
    } وإلا {
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = timestamp;
        اشارہ_گر_dispatch_absolute_motion(seat, false);
    }
}

ساكن فراغ اشارہ_گر_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_کھڑکی_انکڑے *کھڑکی = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface);
    إذا (!کھڑکی) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        أرجع;
    }

    إذا (کھڑکی->surface != seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_سیٹ_Default_Cursor(seat);
        أرجع;
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

ساكن فراغ اشارہ_گر_handle_enter(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                 uint32_t serial, بنية wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface = surface;
    seat->اشارہ_گر_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = sx_w;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = sy_w;

    إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = 0;
        اشارہ_گر_dispatch_enter(seat);
    }
}

ساكن فراغ اشارہ_گر_dispatch_leave(SDL_WaylandSeat *seat, bool update_اشارہ_گر)
{
    SDL_کھڑکی_انکڑے *کھڑکی = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface);

    إذا (کھڑکی) {
        إذا (seat->اشارہ_گر_2.focus) {
            إذا (seat->اشارہ_گر_2.focus->surface == seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
                // Clear the capture flag and raise all buttons
                کھڑکی->sdlwindow->flags &= ~SDL_کھڑکی_MOUSE_CAPTURE;

                seat->اشارہ_گر_2.focus = عدم;
                seat->اشارہ_گر_2.focus_surface = عدم;
                لكل (Uint8 i = 1; seat->اشارہ_گر_2.buttons_pressed; ++i) {
                    إذا (seat->اشارہ_گر_2.buttons_pressed & SDL_BUTTON_نقاب(i)) {
                        SDL_SendMouseButton(0, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, i, false);
                        seat->اشارہ_گر_2.buttons_pressed &= ~SDL_BUTTON_نقاب(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_کھڑکی *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && کھڑکی->sdlwindow == mouse_focus;
                إذا (!--کھڑکی->اشارہ_گر_focus_گنتی && had_focus && !کھڑکی->سرگرم_touch_گنتی) {
                    SDL_سیٹ_Mouse_Focus(عدم);
                }

                إذا (update_اشارہ_گر) {
                    Wayland_Seat_Update_اشارہ_گر_Grab(seat);
                    Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
                }
            }
        } وإلا إذا (update_اشارہ_گر) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساكن فراغ اشارہ_گر_handle_leave(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                 uint32_t serial, بنية wl_surface *surface)
{
    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = surface;
    إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        اشارہ_گر_dispatch_leave(seat, true);
    }
}

ساكن bool Wayland_Process_کامیابی_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    إذا (seat->اشارہ_گر_2.locked_اشارہ_گر) {
        أرجع false;
    }

    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = seat->اشارہ_گر_2.focus;
    SDL_کھڑکی *کھڑکی = کھڑکی_انکڑے_2->sdlwindow;

    إذا (کھڑکی->کامیابی_test) {
        ساكن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_کنارا_چوٹی_بایاں, XDG_TOPLEVEL_RESIZE_کنارا_چوٹی,
            XDG_TOPLEVEL_RESIZE_کنارا_چوٹی_دایاں, XDG_TOPLEVEL_RESIZE_کنارا_دایاں,
            XDG_TOPLEVEL_RESIZE_کنارا_BOTTOM_دایاں, XDG_TOPLEVEL_RESIZE_کنارا_BOTTOM,
            XDG_TOPLEVEL_RESIZE_کنارا_BOTTOM_بایاں, XDG_TOPLEVEL_RESIZE_کنارا_بایاں
        };

#جے_تعریف_شدہ HAVE_LIBDECOR_H
        ساكن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_کنارا_چوٹی_بایاں, LIBDECOR_RESIZE_کنارا_چوٹی,
            LIBDECOR_RESIZE_کنارا_چوٹی_دایاں, LIBDECOR_RESIZE_کنارا_دایاں,
            LIBDECOR_RESIZE_کنارا_BOTTOM_دایاں, LIBDECOR_RESIZE_کنارا_BOTTOM,
            LIBDECOR_RESIZE_کنارا_BOTTOM_بایاں, LIBDECOR_RESIZE_کنارا_بایاں
        };
#جے_انت

        بدل (کھڑکی_انکڑے_2->کامیابی_test_نتیجہ) {
        حالة SDL_HITTEST_DRAGGABLE:
#جے_تعریف_شدہ HAVE_LIBDECOR_H
            إذا (کھڑکی_انکڑے_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (کھڑکی_انکڑے_2->shell_surface.libdecor.چوکھٹا) {
                    libdecor_چوکھٹا_move(کھڑکی_انکڑے_2->shell_surface.libdecor.چوکھٹا,
                                        seat->wl_seat,
                                        serial);
                }
            } وإلا
#جے_انت
                إذا (کھڑکی_انکڑے_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (کھڑکی_انکڑے_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(کھڑکی_انکڑے_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_چوٹی:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_دایاں:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_بایاں:
#جے_تعریف_شدہ HAVE_LIBDECOR_H
            إذا (کھڑکی_انکڑے_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (کھڑکی_انکڑے_2->shell_surface.libdecor.چوکھٹا) {
                    libdecor_چوکھٹا_resize(کھڑکی_انکڑے_2->shell_surface.libdecor.چوکھٹا,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[کھڑکی_انکڑے_2->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وإلا
#جے_انت
                إذا (کھڑکی_انکڑے_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (کھڑکی_انکڑے_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(کھڑکی_انکڑے_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[کھڑکی_انکڑے_2->کامیابی_test_نتیجہ - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ اشارہ_گر_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool تھلے)
{
    SDL_کھڑکی_انکڑے *کھڑکی = seat->اشارہ_گر_2.focus;

    إذا (کھڑکی) {
        bool ignore_click = false;

        إذا (تھلے) {
            seat->اشارہ_گر_2.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);

            إذا (sdl_button == SDL_BUTTON_بایاں && Wayland_Process_کامیابی_Test(seat, seat->آخری_implicit_grab_serial)) {
                أرجع; // don't pass this event on to app.
            }
        } وإلا {
            seat->اشارہ_گر_2.buttons_pressed &= ~SDL_BUTTON_نقاب(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        إذا (کھڑکی->آخری_focus_event_ویلا_ns) {
            إذا (تھلے && (SDL_GetTicksNS() - کھڑکی->آخری_focus_event_ویلا_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            کھڑکی->آخری_focus_event_ویلا_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        إذا (!seat->اشارہ_گر_2.relative_اشارہ_گر) {
            إذا (seat->اشارہ_گر_2.buttons_pressed != 0) {
                کھڑکی->sdlwindow->flags |= SDL_کھڑکی_MOUSE_CAPTURE;
            } وإلا {
                کھڑکی->sdlwindow->flags &= ~SDL_کھڑکی_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                إذا (seat->اشارہ_گر_2.focus_surface != کھڑکی->surface) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = کھڑکی->surface;
                }
            }
        }

        إذا (!ignore_click) {
            SDL_SendMouseButton(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, sdl_button, تھلے);
        }
    }
}

ساكن فراغ اشارہ_گر_handle_button(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2, uint32_t serial,
                                  uint32_t ویلا, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = انکڑے;
    Uint8 sdl_button;

    بدل (button) {
    حالة BTN_بایاں:
        sdl_button = SDL_BUTTON_بایاں;
        اكسر;
    حالة BTN_درمیان:
        sdl_button = SDL_BUTTON_درمیان;
        اكسر;
    حالة BTN_دایاں:
        sdl_button = SDL_BUTTON_دایاں;
        اكسر;
    افتراضي:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        اكسر;
    }

    إذا (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);

    إذا (wl_seat_get_نسخہ(seat->wl_seat) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        إذا (state_w) {
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);
        } وإلا {
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released |= SDL_BUTTON_نقاب(sdl_button);
        }
    } وإلا {
        اشارہ_گر_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساكن فراغ اشارہ_گر_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t قدر)
{
    SDL_کھڑکی_انکڑے *کھڑکی = seat->اشارہ_گر_2.focus;
    ثابت تعداد wl_اشارہ_گر_axis a = axis;

    إذا (seat->اشارہ_گر_2.focus) {
        عائم x, y;

        بدل (a) {
        حالة WL_اشارہ_گر_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (عائم)wl_fixed_منزل_double(قدر);
            اكسر;
        حالة WL_اشارہ_گر_AXIS_HORIZONTAL_SCROLL:
            x = (عائم)wl_fixed_منزل_double(قدر);
            y = 0;
            اكسر;
        افتراضي:
            أرجع;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y, SDL_MOUSEWHEEL_عام);
    }
}

ساكن فراغ اشارہ_گر_handle_axis_common(SDL_WaylandSeat *seat, تعداد SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t قدر)
{
    ثابت تعداد wl_اشارہ_گر_axis a = axis;

    إذا (seat->اشارہ_گر_2.focus) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_axis = true;

        بدل (a) {
        حالة WL_اشارہ_گر_AXIS_VERTICAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0.0f;
                }
                seat->اشارہ_گر_2.pending_چوکھٹا.axis.y += 0 - (عائم)wl_fixed_منزل_double(قدر);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0 - (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.y = 0 - (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            }
            اكسر;
        حالة WL_اشارہ_گر_AXIS_HORIZONTAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = 0.0f;
                }
                seat->اشارہ_گر_2.pending_چوکھٹا.axis.x += (عائم)wl_fixed_منزل_double(قدر);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارہ_گر_2.pending_چوکھٹا.axis.x = (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            }
            اكسر;
        }
    }
}

ساكن فراغ اشارہ_گر_handle_axis(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                uint32_t ویلا, uint32_t axis, wl_fixed_t قدر)
{
    SDL_WaylandSeat *seat = انکڑے;
    ثابت Uint64 nsTimestamp = Wayland_Get_اشارہ_گر_Timestamp(seat, ویلا);

    إذا (wl_seat_get_نسخہ(seat->wl_seat) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = nsTimestamp;
        اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, قدر);
    } وإلا {
        اشارہ_گر_handle_axis_common_v1(seat, nsTimestamp, axis, قدر);
    }
}

ساكن فراغ اشارہ_گر_handle_axis_relative_direction(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = انکڑے;

    بدل (axis_relative_direction) {
    حالة WL_اشارہ_گر_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction = SDL_MOUSEWHEEL_عام;
        اكسر;
    حالة WL_اشارہ_گر_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        اكسر;
    }
}

ساكن فراغ اشارہ_گر_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_کھڑکی_انکڑے *کھڑکی = seat->اشارہ_گر_2.focus;

    إذا (کھڑکی) {
        SDL_Mouse *mouse = SDL_GetMouse();
        مزدوج dx;
        مزدوج dy;
        إذا (mouse->داخلہ_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx_unaccel);
            dy = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy_unaccel);
        } وإلا {
            dx = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx) * کھڑکی->اشارہ_گر_scale.x;
            dy = wl_fixed_منزل_double(seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy) * کھڑکی->اشارہ_گر_scale.y;
        }

        SDL_SendMouseMotion(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, true, (عائم)dx, (عائم)dy);
    }
}

ساكن فراغ اشارہ_گر_dispatch_axis(SDL_WaylandSeat *seat)
{
    عائم x, y;
    SDL_MouseWheelDirection direction = seat->اشارہ_گر_2.pending_چوکھٹا.axis.direction;

    بدل (seat->اشارہ_گر_2.pending_چوکھٹا.axis.x_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->اشارہ_گر_2.pending_چوکھٹا.axis.x / 120.0f;
        اكسر;
    افتراضي:
        x = 0.0f;
        اكسر;
    }

    بدل (seat->اشارہ_گر_2.pending_چوکھٹا.axis.y_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->اشارہ_گر_2.pending_چوکھٹا.axis.y / 120.0f;
        اكسر;
    افتراضي:
        y = 0.0f;
        اكسر;
    }

    SDL_SendMouseWheel(seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns,
                       seat->اشارہ_گر_2.focus->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y, direction);
}

ساكن فراغ اشارہ_گر_handle_چوکھٹا(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2)
{
    SDL_WaylandSeat *seat = انکڑے;

    إذا (seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
        إذا (seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
            SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = seat->اشارہ_گر_2.focus;
            SDL_کھڑکی_انکڑے *new_focus = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface);

            إذا (کھڑکی_انکڑے_2 && (کھڑکی_انکڑے_2->sdlwindow->flags & SDL_کھڑکی_MOUSE_CAPTURE) && کھڑکی_انکڑے_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->اشارہ_گر_2.focus_surface = seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface;
                seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface = عدم;
                seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = عدم;
            } وإلا {
                // Leaving the previous surface before entering a new surface.
                اشارہ_گر_dispatch_leave(seat, false);
                seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = عدم;
            }
        }

        إذا (seat->اشارہ_گر_2.pending_چوکھٹا.enter_surface) {
            اشارہ_گر_dispatch_enter(seat);
        }
    }

    إذا (seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute) {
        اشارہ_گر_dispatch_absolute_motion(seat, seat->اشارہ_گر_2.pending_چوکھٹا.have_warp);
    }

    إذا (seat->اشارہ_گر_2.pending_چوکھٹا.have_relative) {
        اشارہ_گر_dispatch_relative_motion(seat);
    }

    لكل (Uint8 i = 1; seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed || seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released; ++i) {
        ثابت Uint32 نقاب = SDL_BUTTON_نقاب(i);
        إذا (seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed & نقاب) {
            اشارہ_گر_dispatch_button(seat, i, true);
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_pressed &= ~نقاب;
        }
        إذا (seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released & نقاب) {
            اشارہ_گر_dispatch_button(seat, i, false);
            seat->اشارہ_گر_2.pending_چوکھٹا.buttons_released &= ~نقاب;
        }
    }

    إذا (seat->اشارہ_گر_2.pending_چوکھٹا.have_axis) {
        اشارہ_گر_dispatch_axis(seat);
    }

    إذا (seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface) {
        اشارہ_گر_dispatch_leave(seat, true);
    }

    SDL_zero(seat->اشارہ_گر_2.pending_چوکھٹا);
}

ساكن فراغ اشارہ_گر_handle_axis_سروت(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                       uint32_t axis_سروت)
{
    // unimplemented
}

ساكن فراغ اشارہ_گر_handle_axis_stop(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                     uint32_t ویلا, uint32_t axis)
{
    // unimplemented
}

ساكن فراغ اشارہ_گر_handle_axis_discrete(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = انکڑے;
    اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساكن فراغ اشارہ_گر_handle_axis_value120(فراغ *انکڑے, بنية wl_اشارہ_گر *اشارہ_گر_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = انکڑے;
    اشارہ_گر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساكن فراغ اشارہ_گر_handle_warp(فراغ *انکڑے, بنية wl_اشارہ_گر *wl_اشارہ_گر, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;

    seat->اشارہ_گر_2.pending_چوکھٹا.have_absolute = true;
    seat->اشارہ_گر_2.pending_چوکھٹا.have_warp = true;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sx = surface_x;
    seat->اشارہ_گر_2.pending_چوکھٹا.absolute.sy = surface_y;
}

ساكن ثابت بنية wl_اشارہ_گر_listener اشارہ_گر_listener = {
    اشارہ_گر_handle_enter,
    اشارہ_گر_handle_leave,
    اشارہ_گر_handle_motion,
    اشارہ_گر_handle_button,
    اشارہ_گر_handle_axis,
    اشارہ_گر_handle_چوکھٹا,                   // Version 5
    اشارہ_گر_handle_axis_سروت,             // Version 5
    اشارہ_گر_handle_axis_stop,               // Version 5
    اشارہ_گر_handle_axis_discrete,           // Version 5
    اشارہ_گر_handle_axis_value120,           // Version 8
    اشارہ_گر_handle_axis_relative_direction, // Version 9
    اشارہ_گر_handle_warp                     // Version 11
};

ساكن فراغ relative_اشارہ_گر_handle_relative_motion(فراغ *انکڑے,
                                                    بنية zwp_relative_اشارہ_گر_v1 *اشارہ_گر_2,
                                                    uint32_t ویلا_hi,
                                                    uint32_t ویلا_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = انکڑے;

    // Relative pointer event times are in microsecond granularity.
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx = dx;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy = dy;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dx_unaccel = dx_unaccel;
    seat->اشارہ_گر_2.pending_چوکھٹا.relative.dy_unaccel = dy_unaccel;
    seat->اشارہ_گر_2.pending_چوکھٹا.timestamp_ns = Wayland_Adjust_Event_Timestamp_ادھار(SDL_US_منزل_NS(((Uint64)ویلا_hi << 32) | (Uint64)ویلا_lo));

    إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_چوکھٹا_SINCE_نسخہ) {
        seat->اشارہ_گر_2.pending_چوکھٹا.have_relative = true;
    } وإلا {
        اشارہ_گر_dispatch_relative_motion(seat);
    }
}

ساكن ثابت بنية zwp_relative_اشارہ_گر_v1_listener relative_اشارہ_گر_listener = {
    relative_اشارہ_گر_handle_relative_motion,
};

ساكن فراغ locked_اشارہ_گر_locked(فراغ *انکڑے, بنية zwp_locked_اشارہ_گر_v1 *locked_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.is_confined = true;
}

ساكن فراغ locked_اشارہ_گر_unlocked(فراغ *انکڑے, بنية zwp_locked_اشارہ_گر_v1 *locked_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.is_confined = false;
}

ساكن ثابت بنية zwp_locked_اشارہ_گر_v1_listener locked_اشارہ_گر_listener = {
    locked_اشارہ_گر_locked,
    locked_اشارہ_گر_unlocked,
};

ساكن فراغ confined_اشارہ_گر_confined(فراغ *انکڑے, بنية zwp_confined_اشارہ_گر_v1 *confined_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.is_confined = true;
}

ساكن فراغ confined_اشارہ_گر_unconfined(فراغ *انکڑے, بنية zwp_confined_اشارہ_گر_v1 *confined_اشارہ_گر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->اشارہ_گر_2.is_confined = false;
}

ساكن ثابت بنية zwp_confined_اشارہ_گر_v1_listener confined_اشارہ_گر_listener = {
    confined_اشارہ_گر_confined,
    confined_اشارہ_گر_unconfined,
};

ساكن فراغ touch_handler_تھلے(فراغ *انکڑے, بنية wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, بنية wl_surface *surface,
                               صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2;

    // Check that this surface is valid.
    إذا (!surface) {
        أرجع;
    }

    Wayland_Seat_جوڑو_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    کھڑکی_انکڑے_2 = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);

    إذا (کھڑکی_انکڑے_2 && کھڑکی_انکڑے_2->surface == surface) {
        عائم x, y;

        إذا (کھڑکی_انکڑے_2->current.logical_چوڑائی <= 1) {
            x = 0.5f;
        } وإلا {
            x = (عائم)wl_fixed_منزل_double(fx) / (کھڑکی_انکڑے_2->current.logical_چوڑائی - 1);
        }
        إذا (کھڑکی_انکڑے_2->current.logical_اچائی <= 1) {
            y = 0.5f;
        } وإلا {
            y = (عائم)wl_fixed_منزل_double(fy) / (کھڑکی_انکڑے_2->current.logical_اچائی - 1);
        }

        ++کھڑکی_انکڑے_2->سرگرم_touch_گنتی;
        SDL_سیٹ_Mouse_Focus(کھڑکی_انکڑے_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), کھڑکی_انکڑے_2->sdlwindow, SDL_EVENT_FINGER_تھلے, x, y, 1.0f);
    }
}

ساكن فراغ touch_handler_اتے(فراغ *انکڑے, بنية wl_touch *touch, uint32_t serial, uint32_t timestamp, صحيح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    wl_fixed_t fx = 0, fy = 0;
    بنية wl_surface *surface = عدم;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    إذا (surface) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);

        إذا (کھڑکی_انکڑے_2 && کھڑکی_انکڑے_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / کھڑکی_انکڑے_2->current.logical_چوڑائی;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / کھڑکی_انکڑے_2->current.logical_اچائی;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), کھڑکی_انکڑے_2->sdlwindow, SDL_EVENT_FINGER_اتے, x, y, 0.0f);

            --کھڑکی_انکڑے_2->سرگرم_touch_گنتی;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == کھڑکی_انکڑے_2->sdlwindow && !کھڑکی_انکڑے_2->keyboard_focus_گنتی &&
                !کھڑکی_انکڑے_2->اشارہ_گر_focus_گنتی && !کھڑکی_انکڑے_2->سرگرم_touch_گنتی) {
                SDL_سیٹ_Mouse_Focus(عدم);
            }
        }
    }
}

ساكن فراغ touch_handler_motion(فراغ *انکڑے, بنية wl_touch *touch, uint32_t timestamp, صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    بنية wl_surface *surface = عدم;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    إذا (surface) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);

        إذا (کھڑکی_انکڑے_2 && کھڑکی_انکڑے_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / کھڑکی_انکڑے_2->current.logical_چوڑائی;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / کھڑکی_انکڑے_2->current.logical_اچائی;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), کھڑکی_انکڑے_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ساكن فراغ touch_handler_چوکھٹا(فراغ *انکڑے, بنية wl_touch *touch)
{
}

ساكن فراغ touch_handler_cancel(فراغ *انکڑے, بنية wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    SDL_Wayland_Touch_نقطہ *tp, *عارضی;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_محفوظ (tp, عارضی, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ساكن فراغ touch_handler_shape(فراغ *انکڑے, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ساكن فراغ touch_handler_orientation(فراغ *انکڑے, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ساكن ثابت بنية wl_touch_listener touch_listener = {
    touch_handler_تھلے,
    touch_handler_اتے,
    touch_handler_motion,
    touch_handler_چوکھٹا,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#إذا !SDL_XKBCOMMON_CHECK_نسخہ(1, 0, 0)
ساكن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کلید, xkb_layout_اشاریہ_t layout, xkb_level_اشاریہ_t level, xkb_mod_نقاب_t *masks_باہرلا, size_t masks_ناپ)
{
    إذا (!masks_باہرلا || !masks_ناپ) {
        أرجع 0;
    }

    // Level 0 is always unmodified, so early out.
    إذا (level == 0) {
        *masks_باہرلا = 0;
        أرجع 1;
    }

    size_t نقاب_idx = 0;
    ثابت xkb_mod_نقاب_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.کھسکاؤ_نقاب,
        seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.کھسکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.کھسکاؤ_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.کھسکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.کھسکاؤ_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.کھسکاؤ_نقاب | seat->keyboard.xkb.caps_نقاب_2
    };
    ثابت xkb_mod_نقاب_t pressed_mod_نقاب = seat->keyboard.xkb.کھسکاؤ_نقاب | seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.level5_نقاب;
    ثابت xkb_mod_نقاب_t locked_mod_نقاب = seat->keyboard.xkb.caps_نقاب_2;

    لكل (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_نقاب, 0, keymod_masks[i] & locked_mod_نقاب, 0, 0, layout);
        إذا (WAYLAND_xkb_state_کلید_get_level(seat->keyboard.xkb.state, کلید, layout) == level) {
            masks_باہرلا[نقاب_idx] = keymod_masks[i];

            إذا (++نقاب_idx == masks_ناپ) {
                اكسر;
            }
        }
    }

    أرجع نقاب_idx;
}
#جے_انت

ساكن فراغ Wayland_KeymapIterator(بنية xkb_keymap *keymap, xkb_keycode_t کلید, فراغ *انکڑے)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_نقاب_t xkb_valid_mod_نقاب = seat->keyboard.xkb.کھسکاؤ_نقاب |
                                              seat->keyboard.xkb.alt_نقاب |
                                              seat->keyboard.xkb.level3_نقاب |
                                              seat->keyboard.xkb.level5_نقاب |
                                              seat->keyboard.xkb.caps_نقاب_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلید - 8);
    }

    لكل (xkb_layout_اشاریہ_t layout = 0; layout < seat->keyboard.xkb.عدد_layouts; ++layout) {
        ثابت xkb_level_اشاریہ_t عدد_پدھراں = WAYLAND_xkb_keymap_عدد_پدھراں_for_کلید(seat->keyboard.xkb.keymap, کلید, layout);
        لكل (xkb_level_اشاریہ_t level = 0; level < عدد_پدھراں; ++level) {
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

                xkb_mod_نقاب_t xkb_mod_masks[16];
#إذا SDL_XKBCOMMON_CHECK_نسخہ(1, 0, 0)
                ثابت size_t عدد_masks = WAYLAND_xkb_keymap_کلید_get_mods_for_level(seat->keyboard.xkb.keymap, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وإلا
                ثابت size_t عدد_masks = xkb_legacy_get_mods_for_level(seat, کلید, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#جے_انت
                لكل (size_t نقاب = 0; نقاب < عدد_masks; ++نقاب) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    إذا ((xkb_mod_masks[نقاب] | xkb_valid_mod_نقاب) != xkb_valid_mod_نقاب) {
                        استمر;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[نقاب] & seat->keyboard.xkb.کھسکاؤ_نقاب ? SDL_KMOD_کھسکاؤ : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level3_نقاب ? SDL_KMOD_منوال : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level5_نقاب ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.caps_نقاب_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کلید_کوڈ_From_کلید_Sym(syms[0], کلید, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    إذا (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_اگلا_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        إذا (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کلید *res = WAYLAND_wl_array_جوڑو(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_کلید));
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
                            keycode = SDL_SCANCODE_منزل_KEYCODE(scancode);
                            اكسر;
                        }
                    }

                    SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساكن فراغ keyboard_handle_keymap(فراغ *انکڑے, بنية wl_keyboard *keyboard,
                                   uint32_t format, صحيح fd, uint32_t ناپ)
{
    SDL_WaylandSeat *seat = انکڑے;
    حرف *map_str;

    إذا (!انکڑے) {
        close(fd);
        أرجع;
    }

    إذا (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        أرجع;
    }

    map_str = mmap(عدم, ناپ, PROT_READ, MAP_PRIVATE, fd, 0);
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
    munmap(map_str, ناپ);
    close(fd);

    إذا (!seat->keyboard.xkb.keymap) {
        SDL_سیٹ_Error("failed to compile keymap");
        أرجع;
    }

    // Clear the old layouts.
    لكل (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = عدم;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.عدد_layouts = 0;

#إذا SDL_XKBCOMMON_CHECK_نسخہ(1, 10, 0)
    seat->keyboard.xkb.کھسکاؤ_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_کھسکاؤ);
    seat->keyboard.xkb.ctrl_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.عدد_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_عدد);
    seat->keyboard.xkb.caps_نقاب_2 = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وإلا
#تعریف_کرو GET_MOD_اشاریہ(mod) \
    WAYLAND_xkb_keymap_mod_get_اشاریہ(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.کھسکاؤ_نقاب = 1 << GET_MOD_اشاریہ(کھسکاؤ_2);
    seat->keyboard.xkb.ctrl_نقاب = 1 << GET_MOD_اشاریہ(CTRL);
    seat->keyboard.xkb.alt_نقاب = 1 << GET_MOD_اشاریہ(ALT);
    seat->keyboard.xkb.gui_نقاب = 1 << GET_MOD_اشاریہ(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_نقاب = 1 << GET_MOD_اشاریہ(MOD5);
    seat->keyboard.xkb.level5_نقاب = 1 << GET_MOD_اشاریہ(MOD3);
    seat->keyboard.xkb.عدد_نقاب = 1 << GET_MOD_اشاریہ(عدد_2);
    seat->keyboard.xkb.caps_نقاب_2 = 1 << GET_MOD_اشاریہ(CAPS);
#تعریف_رد GET_MOD_اشاریہ
#جے_انت

    إذا (seat->keyboard.xkb.state != عدم) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = عدم;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    إذا (!seat->keyboard.xkb.state) {
        SDL_سیٹ_Error("failed to create XKB state");
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
    seat->keyboard.xkb.عدد_layouts = WAYLAND_xkb_keymap_عدد_layouts(seat->keyboard.xkb.keymap);
    إذا (seat->keyboard.xkb.عدد_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.عدد_layouts, حجم(SDL_Keymap *));
        إذا (!seat->keyboard.sdl_keymap) {
            أرجع;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        لكل (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            إذا (!seat->keyboard.sdl_keymap[i]) {
                لكل (xkb_layout_اشاریہ_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = عدم;
                أرجع;
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
                SDL_سیٹ_Error("could not create XKB compose state");
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
        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.کھسکاؤ_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_کھسکاؤ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_کھسکاؤ;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_کھسکاؤ;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_منوال)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_منوال;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_منوال;
        }

        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_نقاب) {
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
    ثابت xkb_mod_نقاب_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.کھسکاؤ_نقاب) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_کھسکاؤ) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_کھسکاؤ;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_کھسکاؤ);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_کھسکاؤ)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_کھسکاؤ;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_کھسکاؤ;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_نقاب) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.alt_نقاب) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.gui_نقاب) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level3_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_منوال;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_منوال;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.level5_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    إذا (xkb_locked_modifiers & seat->keyboard.xkb.caps_نقاب_2) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.عدد_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_عدد;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_عدد;
    }

    SDL_سیٹ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساكن فراغ Wayland_Handle_Modifier_کلیدیں(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
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
    حالة SDLK_منوال:
        mod = SDL_KMOD_منوال;
        اكسر;
    حالة SDLK_LEVEL5_کھسکاؤ:
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

ساكن فراغ keyboard_handle_enter(فراغ *انکڑے, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface,
                                  بنية wl_array *کلیدیں)
{
    SDL_WaylandSeat *seat = انکڑے;
    uint32_t *کلید;

    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_کھڑکی_انکڑے *کھڑکی = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);
    إذا (!کھڑکی) {
        // Not a surface owned by SDL.
        أرجع;
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

#جے_تعریف_شدہ SDL_USE_IME
    إذا (!seat->متن_داخلہ.zwp_متن_داخلہ) {
        SDL_IME_سیٹ_Focus(true);
    }
#جے_انت

    Uint64 timestamp = SDL_GetTicksNS();
    کھڑکی->آخری_focus_event_ویلا_ns = timestamp;

    Wayland_Seat_سیٹ_Keymap(seat);

    wl_array_for_each (کلید, کلیدیں) {
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
            حالة SDLK_منوال:
            حالة SDLK_LEVEL5_کھسکاؤ:
                Wayland_Handle_Modifier_کلیدیں(seat, scancode, true);
                SDL_Send_Keyboard_کلید_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کلید, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        }
    }
}

ساكن فراغ keyboard_handle_leave(فراغ *انکڑے, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;

    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_کھڑکی_انکڑے *کھڑکی = Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface);
    إذا (!کھڑکی) {
        // Not a surface owned by SDL.
        أرجع;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کلید = 0;

    SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    طالما (keyboard_focus && SDL_کھڑکی_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->ماپا;
    }

    ثابت bool had_focus = keyboard_focus && کھڑکی->sdlwindow == keyboard_focus;
    seat->keyboard.focus = عدم;
    --کھڑکی->keyboard_focus_گنتی;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    إذا (!کھڑکی->keyboard_focus_گنتی && had_focus) {
        SDL_سیٹ_Keyboard_Focus(عدم);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشارہ_گر_Grabs(seat->display, کھڑکی);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_داخلہ(seat);

#جے_تعریف_شدہ SDL_USE_IME
    إذا (!seat->متن_داخلہ.zwp_متن_داخلہ && !کھڑکی->keyboard_focus_گنتی) {
        SDL_IME_سیٹ_Focus(false);
    }
#جے_انت

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    إذا (SDL_GetMouseFocus() == کھڑکی->sdlwindow && !کھڑکی->اشارہ_گر_focus_گنتی && !کھڑکی->سرگرم_touch_گنتی) {
        SDL_سیٹ_Mouse_Focus(عدم);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_انکڑے_Device_سیٹ_Selection_Offer(seat->انکڑے_device, عدم);
}

ساكن bool keyboard_داخلہ_get_متن(حرف متن[8], ثابت SDL_WaylandSeat *seat, uint32_t کلید, bool تھلے, bool *handled_by_ime)
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

#جے_تعریف_شدہ SDL_USE_IME
    إذا (SDL_IME_Process_کلید_Event(sym, کلید + 8, تھلے)) {
        إذا (handled_by_ime) {
            *handled_by_ime = true;
        }
        أرجع true;
    }
#جے_انت

    إذا (!تھلے) {
        أرجع false;
    }

    إذا (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        بدل (WAYLAND_xkb_compose_state_get_حالت(seat->keyboard.xkb.compose_state)) {
        حالة XKB_COMPOSE_COMPOSING:
            إذا (handled_by_ime) {
                *handled_by_ime = true;
            }
            أرجع true;
        حالة XKB_COMPOSE_CANCELLED:
        افتراضي:
            sym = XKB_کلید_No_علامت;
            اكسر;
        حالة XKB_COMPOSE_NOTHING:
            اكسر;
        حالة XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            اكسر;
        }
    }

    أرجع WAYLAND_xkb_keysym_منزل_utf8(sym, متن, 8) > 0;
}

ساكن فراغ keyboard_handle_کلید(فراغ *انکڑے, بنية wl_keyboard *keyboard,
                                uint32_t serial, uint32_t ویلا, uint32_t کلید,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = انکڑے;
    تعداد wl_keyboard_کلید_state state = state_w;
    حرف متن[8];
    bool has_متن = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, ویلا);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    إذا (state == WL_KEYBOARD_کلید_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        إذا (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کلید_repeats(seat->keyboard.xkb.keymap, کلید + 8)) {
            أرجع;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کلید_STATE_PRESSED;
    }

    Wayland_Seat_سیٹ_Keymap(seat);

    إذا (state == WL_KEYBOARD_کلید_STATE_PRESSED) {
        SDL_کھڑکی *keyboard_focus = SDL_GetKeyboardFocus();
        إذا (keyboard_focus && SDL_متن_داخلہ_سرگرم(keyboard_focus)) {
            has_متن = keyboard_داخلہ_get_متن(متن, seat, کلید, true, &handled_by_ime);
        }
    } وإلا {
        إذا (کلید == seat->keyboard.repeat.کلید) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_منزل_NS(ویلا - seat->keyboard.repeat.wl_press_ویلا_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کلید = 0;
        }
        keyboard_داخلہ_get_متن(متن, seat, کلید, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = عدم;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کلید(seat, کلید, &syms);
    Wayland_Handle_Modifier_کلیدیں(seat, scancode, state == WL_KEYBOARD_کلید_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    إذا (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کلید_Sym_منزل_Ucs4(syms[0]);
        إذا (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_نقاب) {
                scancode = SDL_Get_Keymap_اگلا_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_سیٹ_Keymap_اندراج(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
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
            keyboard_repeat_سیٹ(&seat->keyboard.repeat, seat->keyboard.sdl_id, کلید, ویلا, timestamp_ns, scancode, has_متن ? متن : عدم);
        }
    }
}

ساكن فراغ keyboard_handle_modifiers(فراغ *انکڑے, بنية wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t گروہ)
{
    SDL_WaylandSeat *seat = انکڑے;
    ثابت uint32_t پچھلا_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = گروہ;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    إذا (!seat->keyboard.xkb.state) {
        أرجع;
    }

    WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, گروہ);

    // If a key is repeating, update the text to apply the modifier.
    إذا (seat->keyboard.repeat.کلید) {
        حرف متن[8];

        إذا (keyboard_داخلہ_get_متن(متن, seat, seat->keyboard.repeat.کلید, true, عدم)) {
            SDL_strlcpy(seat->keyboard.repeat.متن, متن, SDL_arraysize(seat->keyboard.repeat.متن));
        }
    }

    إذا (گروہ != پچھلا_layout) {
        Wayland_Seat_سیٹ_Keymap(seat);

        إذا (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ساكن فراغ keyboard_handle_repeat_info(فراغ *انکڑے, بنية wl_keyboard *wl_keyboard,
                                        int32_t شرح, int32_t delay)
{
    SDL_WaylandSeat *seat = انکڑے;
    seat->keyboard.repeat.repeat_شرح = شرح;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    إذا (!شرح) {
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

ساكن فراغ Wayland_Seat_Destroy_اشارہ_گر(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->اشارہ_گر_2.cursor_state);

    // End any active gestures.
    إذا (seat->اشارہ_گر_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_سرا, 0, seat->اشارہ_گر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    إذا (seat->اشارہ_گر_2.focus) {
        seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = seat->اشارہ_گر_2.focus->surface;
        اشارہ_گر_dispatch_leave(seat, false);
        seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = عدم;
    }

    SDL_RemoveMouse(seat->اشارہ_گر_2.sdl_id);

    إذا (seat->اشارہ_گر_2.confined_اشارہ_گر) {
        zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
    }

    إذا (seat->اشارہ_گر_2.locked_اشارہ_گر) {
        zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
    }

    إذا (seat->اشارہ_گر_2.relative_اشارہ_گر) {
        zwp_relative_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.relative_اشارہ_گر);
    }

    إذا (seat->اشارہ_گر_2.timestamps) {
        zwp_داخلہ_timestamps_v1_destroy(seat->اشارہ_گر_2.timestamps);
    }

    إذا (seat->اشارہ_گر_2.gesture_pinch) {
        zwp_اشارہ_گر_gesture_pinch_v1_destroy(seat->اشارہ_گر_2.gesture_pinch);
    }

    إذا (seat->اشارہ_گر_2.wl_اشارہ_گر) {
        إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) >= WL_اشارہ_گر_RELEASE_SINCE_نسخہ) {
            wl_اشارہ_گر_release(seat->اشارہ_گر_2.wl_اشارہ_گر);
        } وإلا {
            wl_اشارہ_گر_destroy(seat->اشارہ_گر_2.wl_اشارہ_گر);
        }
    }

    SDL_zero(seat->اشارہ_گر_2);
}

ساكن فراغ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    إذا (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    إذا (seat->keyboard.sdl_keymap) {
        إذا (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_سیٹ_Mod_State(SDL_KMOD_NONE);
        }
        لكل (xkb_layout_اشاریہ_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
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
        zwp_داخلہ_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    إذا (seat->keyboard.wl_keyboard) {
        إذا (wl_keyboard_get_نسخہ(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_نسخہ) {
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
        zwp_داخلہ_timestamps_v1_destroy(seat->touch.timestamps);
    }

    إذا (seat->touch.wl_touch) {
        إذا (wl_touch_get_نسخہ(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_نسخہ) {
            wl_touch_release(seat->touch.wl_touch);
        } وإلا {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

ساكن فراغ seat_handle_capabilities(فراغ *انکڑے, بنية wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    حرف name_fmt[256];

    إذا ((capabilities & WL_SEAT_CAPABILITY_اشارہ_گر) && !seat->اشارہ_گر_2.wl_اشارہ_گر) {
        seat->اشارہ_گر_2.wl_اشارہ_گر = wl_seat_get_اشارہ_گر(wl_seat);
        SDL_zero(seat->اشارہ_گر_2.pending_چوکھٹا.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_اشارہ_گر_سیٹ_user_انکڑے(seat->اشارہ_گر_2.wl_اشارہ_گر, seat);
        wl_اشارہ_گر_جوڑو_listener(seat->اشارہ_گر_2.wl_اشارہ_گر, &اشارہ_گر_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_اشارہ_گر_Gestures(seat);

        seat->اشارہ_گر_2.sdl_id = SDL_Get_اگلا_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_اشارہ_گر_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_اشارہ_گر_NAME, seat->اشارہ_گر_2.sdl_id);
        }

        SDL_جوڑو_Mouse(seat->اشارہ_گر_2.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_اشارہ_گر) && seat->اشارہ_گر_2.wl_اشارہ_گر) {
        Wayland_Seat_Destroy_اشارہ_گر(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_سیٹ_user_انکڑے(seat->touch.wl_touch, seat);
        wl_touch_جوڑو_listener(seat->touch.wl_touch, &touch_listener, seat);

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_جوڑو_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_سدھا, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_سیٹ_user_انکڑے(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_جوڑو_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_اگلا_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_جوڑو_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_رجسٹر_داخلہ_Timestamp_Listeners(seat);
}

ساكن فراغ seat_handle_name(فراغ *انکڑے, بنية wl_seat *wl_seat, ثابت حرف *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;

    إذا (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ساكن ثابت بنية wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ساكن فراغ انکڑے_offer_handle_offer(فراغ *انکڑے, بنية wl_انکڑے_offer *wl_انکڑے_offer,
                                    ثابت حرف *mime_type)
{
    SDL_Wayland_انکڑے_Offer *offer = انکڑے;
    Wayland_انکڑے_Offer_جوڑو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_انکڑے_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_انکڑے_offer) : -1),
                 mime_type);
}

ساكن فراغ انکڑے_offer_handle_سروت_actions(فراغ *انکڑے, بنية wl_انکڑے_offer *wl_انکڑے_offer,
                                             uint32_t سروت_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_انکڑے_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_انکڑے_offer) : -1),
                 سروت_actions);
}

ساكن فراغ انکڑے_offer_handle_actions(فراغ *انکڑے, بنية wl_انکڑے_offer *wl_انکڑے_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_انکڑے_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_انکڑے_offer) : -1),
                 dnd_action);
}

ساكن ثابت بنية wl_انکڑے_offer_listener انکڑے_offer_listener = {
    انکڑے_offer_handle_offer,
    انکڑے_offer_handle_سروت_actions, // Version 3
    انکڑے_offer_handle_actions,        // Version 3
};

ساكن فراغ primary_selection_offer_handle_offer(فراغ *انکڑے, بنية zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = انکڑے;
    Wayland_Primary_Selection_Offer_جوڑو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ساكن ثابت بنية zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ساكن فراغ انکڑے_device_handle_انکڑے_offer(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device,
                                          بنية wl_انکڑے_offer *id)
{
    SDL_Wayland_انکڑے_Offer *انکڑے_offer = SDL_calloc(1, حجم(*انکڑے_offer));
    إذا (انکڑے_offer) {
        SDL_Wayland_انکڑے_Device *انکڑے_device = (SDL_Wayland_انکڑے_Device *)انکڑے;
        انکڑے_offer->offer = id;
        انکڑے_offer->انکڑے_device = انکڑے_device;
        انکڑے_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(انکڑے_offer->mimes));
        wl_انکڑے_offer_سیٹ_user_انکڑے(id, انکڑے_offer);
        wl_انکڑے_offer_جوڑو_listener(id, &انکڑے_offer_listener, انکڑے_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
    }
}

ساكن فراغ انکڑے_device_handle_enter(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device,
                                     uint32_t serial, بنية wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, بنية wl_انکڑے_offer *id)
{
    SDL_Wayland_انکڑے_Device *انکڑے_device = انکڑے;
    SDL_کھڑکی_انکڑے *کھڑکی = surface ? Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface) : عدم;
    انکڑے_device->has_mime_file = false;
    انکڑے_device->متن_mime_type = عدم;

    انکڑے_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    إذا (id) {
        انکڑے_device->drag_offer = wl_انکڑے_offer_get_user_انکڑے(id);
    }

    إذا (انکڑے_device->drag_offer && کھڑکی && کھڑکی->مندا_drag_and_drop) {
#جے_تعریف_شدہ SDL_USE_LIBDBUS
        إذا (Wayland_انکڑے_Offer_Has_MIME(انکڑے_device->drag_offer, FILE_PORTAL_MIME)) {
            انکڑے_device->has_mime_file = true;
            wl_انکڑے_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#جے_انت
        إذا (Wayland_انکڑے_Offer_Has_MIME(انکڑے_device->drag_offer, FILE_MIME)) {
            انکڑے_device->has_mime_file = true;
            wl_انکڑے_offer_accept(id, serial, FILE_MIME);
        }

        إذا (!انکڑے_device->has_mime_file) {
            size_t mime_گنتی = 0;
            ثابت حرف *ثابت *متن_mime_types = Wayland_Get_متن_Mime_Types(SDL_GetVideoDevice(), &mime_گنتی);
            لكل (size_t i = 0; i < mime_گنتی; ++i) {
                إذا (Wayland_انکڑے_Offer_Has_MIME(انکڑے_device->drag_offer, متن_mime_types[i])) {
                    انکڑے_device->متن_mime_type = متن_mime_types[i];
                    wl_انکڑے_offer_accept(id, serial, متن_mime_types[i]);
                    اكسر;
                }
            }
        }

        إذا (انکڑے_device->has_mime_file || انکڑے_device->متن_mime_type) {
            // SDL only supports "copy" style drag and drop
            إذا (wl_انکڑے_offer_get_نسخہ(انکڑے_device->drag_offer->offer) >= WL_انکڑے_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_انکڑے_offer_سیٹ_actions(انکڑے_device->drag_offer->offer, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_COPY, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            انکڑے_device->dnd_کھڑکی = کھڑکی->sdlwindow;
            انکڑے_device->dnd_surface = surface;
            مزدوج dx = wl_fixed_منزل_double(x);
            مزدوج dy = wl_fixed_منزل_double(y);

            // If over the mask, adjust the offset.
            إذا (surface == کھڑکی->نقاب.surface) {
                dx += (مزدوج)کھڑکی->نقاب.وتھ_x;
                dy += (مزدوج)کھڑکی->نقاب.وتھ_y;
            }

            dx *= کھڑکی->اشارہ_گر_scale.x;
            dy *= کھڑکی->اشارہ_گر_scale.y;

            SDL_SendDropPosition(انکڑے_device->dnd_کھڑکی, (عائم)dx, (عائم)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id),
                         wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), SDL_Get_کھڑکی_ID(انکڑے_device->dnd_کھڑکی), serial);
        } وإلا {
            // Decline the offer.
            wl_انکڑے_offer_accept(id, serial, عدم);
            إذا (wl_انکڑے_offer_get_نسخہ(انکڑے_device->drag_offer->offer) >= WL_انکڑے_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_انکڑے_offer_سیٹ_actions(انکڑے_device->drag_offer->offer, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_NONE, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id), wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
        }
    } وإلا {
        انکڑے_device->dnd_کھڑکی = عدم;
        انکڑے_device->dnd_surface = عدم;

        // Decline the offer.
        إذا (id) {
            wl_انکڑے_offer_accept(id, serial, عدم);
            إذا (wl_انکڑے_offer_get_نسخہ(انکڑے_device->drag_offer->offer) >= WL_انکڑے_OFFER_سیٹ_ACTIONS_SINCE_نسخہ) {
                wl_انکڑے_offer_سیٹ_actions(انکڑے_device->drag_offer->offer, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_NONE, WL_انکڑے_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1,
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
    }
}

ساكن فراغ انکڑے_device_handle_leave(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device)
{
    SDL_Wayland_انکڑے_Device *انکڑے_device = انکڑے;

    إذا (انکڑے_device->drag_offer) {
        إذا (انکڑے_device->dnd_کھڑکی) {
            SDL_SendDropComplete(انکڑے_device->dnd_کھڑکی);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)انکڑے_device->drag_offer->offer),
                         SDL_Get_کھڑکی_ID(انکڑے_device->dnd_کھڑکی), انکڑے_device->drag_serial);
        } وإلا {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)انکڑے_device->drag_offer->offer),
                         انکڑے_device->drag_serial);
        }
        Wayland_انکڑے_Offer_Destroy(انکڑے_device->drag_offer);
        انکڑے_device->drag_offer = عدم;
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    انکڑے_device->has_mime_file = false;
    انکڑے_device->متن_mime_type = عدم;
}

ساكن فراغ انکڑے_device_handle_motion(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device,
                                      uint32_t ویلا, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_انکڑے_Device *انکڑے_device = انکڑے;

    إذا (انکڑے_device->drag_offer && انکڑے_device->dnd_کھڑکی && (انکڑے_device->has_mime_file || انکڑے_device->متن_mime_type)) {
        SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = انکڑے_device->dnd_کھڑکی->اندرونی;
        مزدوج dx = wl_fixed_منزل_double(x);
        مزدوج dy = wl_fixed_منزل_double(y);

        // If over the mask, adjust the offset.
        إذا (انکڑے_device->dnd_surface == کھڑکی_انکڑے_2->نقاب.surface) {
            dx += (مزدوج)کھڑکی_انکڑے_2->نقاب.وتھ_x;
            dy += (مزدوج)کھڑکی_انکڑے_2->نقاب.وتھ_y;
        }

        dx *= کھڑکی_انکڑے_2->اشارہ_گر_scale.x;
        dy *= کھڑکی_انکڑے_2->اشارہ_گر_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(انکڑے_device->dnd_کھڑکی, (عائم)dx, (عائم)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)انکڑے_device->drag_offer->offer),
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y),
                     SDL_Get_کھڑکی_ID(انکڑے_device->dnd_کھڑکی), انکڑے_device->drag_serial);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), -1);
    }
}

ساكن فراغ drop_cleanup_handler(فراغ *انکڑے, بنية wl_callback *callback, uint32_t callback_انکڑے)
{
    Wayland_Drop_انکڑے *drop = (Wayland_Drop_انکڑے *)انکڑے;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ساكن ثابت بنية wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ساكن فراغ drop_dispatch_handler(فراغ *انکڑے)
{
    Wayland_Drop_انکڑے *drop = (Wayland_Drop_انکڑے *)انکڑے;
    SDL_Wayland_انکڑے_Offer *offer = drop->offer;
    SDL_Wayland_انکڑے_Device *انکڑے_device = offer->انکڑے_device;

    إذا (drop->dnd_کھڑکی) {
        size_t لمائی;
        bool drop_handled = false;

#جے_تعریف_شدہ SDL_USE_LIBDBUS
        إذا (Wayland_انکڑے_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            فراغ *بفر_2 = Wayland_انکڑے_Offer_Receive(offer, FILE_PORTAL_MIME, &لمائی);
            إذا (بفر_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                إذا (dbus) {
                    صحيح رستہ_گنتی = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(بفر_2, &رستہ_گنتی);
                    // If dropped files contain a directory the list is empty
                    إذا (paths && رستہ_گنتی > 0) {
                        لكل (صحيح i = 0; i < رستہ_گنتی; i++) {
                            SDL_SendDropFile(drop->dnd_کھڑکی, عدم, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(بفر_2);
            }
        }
#جے_انت
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        إذا (!drop_handled) {
            إذا (Wayland_انکڑے_Offer_Has_MIME(offer, FILE_MIME)) {
                فراغ *بفر_2 = Wayland_انکڑے_Offer_Receive(offer, FILE_MIME, &لمائی);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_کھڑکی, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            } وإلا إذا (Wayland_انکڑے_Offer_Has_MIME(offer, drop->متن_mime_type)) {
                فراغ *بفر_2 = Wayland_انکڑے_Offer_Receive(offer, drop->متن_mime_type, &لمائی);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        SDL_Send_Drop_متن(drop->dnd_کھڑکی, token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            }
        }

        إذا (drop_handled && wl_انکڑے_offer_get_نسخہ(offer->offer) >= WL_انکڑے_OFFER_انت_SINCE_نسخہ) {
            wl_انکڑے_offer_انت(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_کھڑکی);
    }

    Wayland_انکڑے_Offer_Destroy(drop->offer);
    drop->offer = عدم;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(انکڑے_device->seat->display->display);
    wl_callback_جوڑو_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساكن فراغ انکڑے_device_handle_drop(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device)
{
    SDL_Wayland_انکڑے_Device *انکڑے_device = انکڑے;

    إذا (انکڑے_device->drag_offer && انکڑے_device->dnd_کھڑکی &&
        (انکڑے_device->has_mime_file || انکڑے_device->متن_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)انکڑے_device->drag_offer->offer),
                     SDL_Get_کھڑکی_ID(انکڑے_device->dnd_کھڑکی), انکڑے_device->drag_serial);

        Wayland_کم_Thread_Context *ctx = انکڑے_device->seat->display->کم_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_انکڑے *drop = SDL_calloc(1, حجم(Wayland_Drop_انکڑے));
        إذا (drop) {
            drop->offer = انکڑے_device->drag_offer;
            drop->dnd_کھڑکی = انکڑے_device->dnd_کھڑکی;
            drop->متن_mime_type = انکڑے_device->متن_mime_type;

            WAYLAND_wl_list_داخل_کرو(&انکڑے_device->pending_drops, &drop->link);
            Wayland_کم_Thread_جوڑو_کم(ctx, drop_dispatch_handler, drop, &drop->id);
        } وإلا {
            Wayland_انکڑے_Offer_Destroy(انکڑے_device->drag_offer);
        }
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_انکڑے_Offer_Destroy(انکڑے_device->drag_offer);
    }

    انکڑے_device->drag_offer = عدم;
}

ساكن فراغ انکڑے_device_handle_selection(فراغ *انکڑے, بنية wl_انکڑے_device *wl_انکڑے_device,
                                         بنية wl_انکڑے_offer *id)
{
    SDL_Wayland_انکڑے_Device *انکڑے_device = انکڑے;
    SDL_Wayland_انکڑے_Offer *offer = عدم;

    إذا (id) {
        offer = wl_انکڑے_offer_get_user_انکڑے(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));

    Wayland_انکڑے_Device_سیٹ_Selection_Offer(انکڑے_device, offer);
}

ساكن ثابت بنية wl_انکڑے_device_listener انکڑے_device_listener = {
    انکڑے_device_handle_انکڑے_offer,
    انکڑے_device_handle_enter,
    انکڑے_device_handle_leave,
    انکڑے_device_handle_motion,
    انکڑے_device_handle_drop,
    انکڑے_device_handle_selection
};

ساكن فراغ primary_selection_device_handle_offer(فراغ *انکڑے, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, حجم(*primary_selection_offer));
    إذا (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)انکڑے;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_سیٹ_user_انکڑے(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_جوڑو_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن فراغ primary_selection_device_handle_selection(فراغ *انکڑے, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = انکڑے;
    SDL_WaylandPrimarySelectionOffer *offer = عدم;

    إذا (id) {
        offer = zwp_primary_selection_offer_v1_get_user_انکڑے(id);
    }

    إذا (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن ثابت بنية zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساكن فراغ متن_داخلہ_enter(فراغ *انکڑے,
                             بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_داخلہ_leave(فراغ *انکڑے,
                             بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_داخلہ_preedit_string(فراغ *انکڑے,
                                      بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                      ثابت حرف *متن,
                                      int32_t cursor_begin,
                                      int32_t cursor_سرا)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    seat->متن_داخلہ.has_preedit = true;
    إذا (متن) {
        صحيح cursor_begin_utf8 = cursor_begin >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_begin) : -1;
        صحيح cursor_سرا_utf8 = cursor_سرا >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_سرا) : -1;
        صحيح cursor_ناپ_utf8;
        إذا (cursor_سرا_utf8 >= 0) {
            إذا (cursor_begin_utf8 >= 0) {
                cursor_ناپ_utf8 = cursor_سرا_utf8 - cursor_begin_utf8;
            } وإلا {
                cursor_ناپ_utf8 = cursor_سرا_utf8;
            }
        } وإلا {
            cursor_ناپ_utf8 = -1;
        }
        SDL_Send_Editing_متن(متن, cursor_begin_utf8, cursor_ناپ_utf8);
    } وإلا {
        SDL_Send_Editing_متن("", 0, 0);
    }
}

ساكن فراغ متن_داخلہ_commit_string(فراغ *انکڑے,
                                     بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                     ثابت حرف *متن)
{
    SDL_Send_Keyboard_متن(متن);
}

ساكن فراغ متن_داخلہ_delete_surrounding_متن(فراغ *انکڑے,
                                               بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                                               uint32_t before_لمائی,
                                               uint32_t after_لمائی)
{
    // FIXME: Do we care about this event?
}

ساكن فراغ متن_داخلہ_پورا(فراغ *انکڑے,
                            بنية zwp_متن_داخلہ_v3 *zwp_متن_داخلہ_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    إذا (!seat->متن_داخلہ.has_preedit) {
        SDL_Send_Editing_متن("", 0, 0);
    }
    seat->متن_داخلہ.has_preedit = false;
}

ساكن ثابت بنية zwp_متن_داخلہ_v3_listener متن_داخلہ_listener = {
    متن_داخلہ_enter,
    متن_داخلہ_leave,
    متن_داخلہ_preedit_string,
    متن_داخلہ_commit_string,
    متن_داخلہ_delete_surrounding_متن,
    متن_داخلہ_پورا
};

ساكن فراغ Wayland_انکڑے_Device_سیٹ_ID(SDL_Wayland_انکڑے_Device *انکڑے_device)
{
    إذا (!انکڑے_device->id_str)
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        إذا (dbus) {
            ثابت حرف *id = dbus->bus_get_unique_name(dbus->session_conn);
            إذا (id) {
                انکڑے_device->id_str = SDL_strdup(id);
            }
        }
    }
    إذا (!انکڑے_device->id_str)
#جے_انت
    {
        حرف id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, حجم(id), "%" SDL_PRIu64, pid);
        انکڑے_device->id_str = SDL_strdup(id);
    }
}

ساكن فراغ Wayland_Seat_Create_انکڑے_Device(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->انکڑے_device_manager) {
        أرجع;
    }

    SDL_Wayland_انکڑے_Device *انکڑے_device = SDL_calloc(1, حجم(*انکڑے_device));
    إذا (!انکڑے_device) {
        أرجع;
    }

    انکڑے_device->انکڑے_device = wl_انکڑے_device_manager_get_انکڑے_device(
        seat->display->انکڑے_device_manager, seat->wl_seat);
    انکڑے_device->seat = seat;

    إذا (!انکڑے_device->انکڑے_device) {
        SDL_free(انکڑے_device);
        أرجع;
    }

    Wayland_انکڑے_Device_سیٹ_ID(انکڑے_device);
    WAYLAND_wl_list_init(&انکڑے_device->pending_drops);
    wl_انکڑے_device_سیٹ_user_انکڑے(انکڑے_device->انکڑے_device, انکڑے_device);
    wl_انکڑے_device_جوڑو_listener(انکڑے_device->انکڑے_device, &انکڑے_device_listener, انکڑے_device);
    seat->انکڑے_device = انکڑے_device;
}

فراغ Wayland_Display_Init_انکڑے_Device_Manager(SDL_Video_انکڑے *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_انکڑے_Device(seat);
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
        zwp_primary_selection_device_v1_سیٹ_user_انکڑے(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_جوڑو_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_انکڑے *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ساكن فراغ Wayland_Seat_Create_متن_داخلہ(SDL_WaylandSeat *seat)
{
    إذا (seat->display->متن_داخلہ_manager) {
        seat->متن_داخلہ.zwp_متن_داخلہ = zwp_متن_داخلہ_manager_v3_get_متن_داخلہ(seat->display->متن_داخلہ_manager, seat->wl_seat);

        إذا (seat->متن_داخلہ.zwp_متن_داخلہ) {
            zwp_متن_داخلہ_v3_سیٹ_user_انکڑے(seat->متن_داخلہ.zwp_متن_داخلہ, seat);
            zwp_متن_داخلہ_v3_جوڑو_listener(seat->متن_داخلہ.zwp_متن_داخلہ,
                                           &متن_داخلہ_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_متن_داخلہ_Manager(SDL_Video_انکڑے *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_متن_داخلہ(seat);
    }
}

// Pen/Tablet support...
ساكن فراغ tablet_tool_handle_type(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    بدل (type) {
        #تعریف_کرو CASE(typ) حالة ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; أرجع
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #تعریف_رد CASE
        افتراضي: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ساكن فراغ tablet_tool_handle_hardware_serial(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ساكن فراغ tablet_tool_handle_hardware_id_wacom(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->info.wacom_id = id_lo;
}

ساكن فراغ tablet_tool_handle_capability(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    بدل (capability) {
        #تعریف_کرو CASE(wltyp,sdltyp) حالة ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; أرجع
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(فاصلہ_2, SDL_PEN_CAPABILITY_فاصلہ);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #تعریف_رد CASE
        افتراضي: اكسر;  // unsupported here.
    }
}

ساكن فراغ tablet_tool_handle_پورا(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    إذا (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        sdltool->instance_id = SDL_جوڑو_Pen_Device(0, عدم, کھڑکی, &sdltool->info, sdltool, false);
    }
}

ساكن فراغ tablet_tool_handle_removed(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    إذا (sdltool->instance_id) {
        SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        SDL_RemovePenDevice(0, کھڑکی, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساكن فراغ tablet_tool_handle_proximity_وچ(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, بنية zwp_tablet_v2 *tablet, بنية wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    SDL_کھڑکی_انکڑے *windowdata = surface ? Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(surface) : عدم;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : عدم;
    sdltool->proximity_serial = serial;
    sdltool->چوکھٹا.have_proximity = true;
    sdltool->چوکھٹا.وچ_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساكن فراغ tablet_tool_handle_proximity_باہرلا(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.have_proximity = true;
    sdltool->چوکھٹا.وچ_proximity = false;
}

ساكن فراغ tablet_tool_handle_تھلے(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.tool_state = WAYLAND_TABLET_TOOL_STATE_تھلے;
}

ساكن فراغ tablet_tool_handle_اتے(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.tool_state = WAYLAND_TABLET_TOOL_STATE_اتے;
}

ساكن فراغ tablet_tool_handle_motion(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    SDL_کھڑکی_انکڑے *windowdata = sdltool->focus;
    إذا (windowdata) {
        sdltool->چوکھٹا.x = (عائم)(wl_fixed_منزل_double(sx_w) * windowdata->اشارہ_گر_scale.x);
        sdltool->چوکھٹا.y = (عائم)(wl_fixed_منزل_double(sy_w) * windowdata->اشارہ_گر_scale.y);
        sdltool->چوکھٹا.have_motion = true;
    }
}

ساكن فراغ tablet_tool_handle_pressure(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_PRESSURE] = ((عائم) pressure) / 65535.0f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_PRESSURE);
    إذا (pressure) {
        sdltool->چوکھٹا.axes[SDL_PEN_AXIS_فاصلہ] = 0.0f;
        sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_فاصلہ);
    }
}

ساكن فراغ tablet_tool_handle_فاصلہ(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t فاصلہ)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_فاصلہ] = ((عائم) فاصلہ) / 65535.0f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_فاصلہ);
    إذا (فاصلہ) {
        sdltool->چوکھٹا.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساكن فراغ tablet_tool_handle_tilt(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_XTILT] = (عائم)(wl_fixed_منزل_double(xtilt));
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_YTILT] = (عائم)(wl_fixed_منزل_double(ytilt));
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ساكن فراغ tablet_tool_handle_button(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
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

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->چوکھٹا.buttons)));
    sdltool->چوکھٹا.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_تھلے : WAYLAND_TABLET_TOOL_BUTTON_اتے;
}

ساكن فراغ tablet_tool_handle_rotation(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    ثابت عائم rotation = (عائم)(wl_fixed_منزل_double(degrees));
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساكن فراغ tablet_tool_handle_slider(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    sdltool->چوکھٹا.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->چوکھٹا.axes_سیٹ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساكن فراغ tablet_tool_handle_wheel(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساكن فراغ tablet_tool_handle_چوکھٹا(فراغ *انکڑے, بنية zwp_tablet_tool_v2 *tool, uint32_t ویلا)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) انکڑے;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    إذا (!instance_id) {
        أرجع;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_Adjust_Event_Timestamp_ادھار(Wayland_EventTimestampMSToNS(ویلا));
    SDL_کھڑکی *کھڑکی = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    إذا (sdltool->چوکھٹا.have_proximity && sdltool->چوکھٹا.وچ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کھڑکی, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    إذا (sdltool->چوکھٹا.have_motion && sdltool->چوکھٹا.tool_state) {
        إذا (sdltool->چوکھٹا.tool_state == WAYLAND_TABLET_TOOL_STATE_تھلے) {
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, true);
        } وإلا {
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
        }
    } وإلا {
        إذا (sdltool->چوکھٹا.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, کھڑکی, is_eraser, sdltool->چوکھٹا.tool_state == WAYLAND_TABLET_TOOL_STATE_تھلے);
        }

        إذا (sdltool->چوکھٹا.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, کھڑکی, sdltool->چوکھٹا.x, sdltool->چوکھٹا.y);
        }
    }

    لكل (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_گنتی; i++) {
        إذا (sdltool->چوکھٹا.axes_سیٹ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, کھڑکی, i, sdltool->چوکھٹا.axes[i]);
        }
    }

    لكل (صحيح i = 0; i < SDL_arraysize(sdltool->چوکھٹا.buttons); i++) {
        ثابت صحيح state = sdltool->چوکھٹا.buttons[i];
        إذا (state) {
            SDL_SendPenButton(timestamp, instance_id, کھڑکی, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_تھلے);
        }
    }

    إذا (sdltool->چوکھٹا.have_proximity && !sdltool->چوکھٹا.وچ_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کھڑکی, false, false);
        sdltool->focus = عدم;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->چوکھٹا);
}

ساكن ثابت بنية zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_پورا,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_وچ,
    tablet_tool_handle_proximity_باہرلا,
    tablet_tool_handle_تھلے,
    tablet_tool_handle_اتے,
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


ساكن فراغ tablet_seat_handle_tablet_added(فراغ *انکڑے, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ساكن فراغ tablet_seat_handle_tool_added(فراغ *انکڑے, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)انکڑے;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, حجم(*sdltool));

    إذا (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.عدد_buttons = -1;

        إذا (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_داخل_کرو(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_جوڑو_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ساكن فراغ tablet_seat_handle_pad_added(فراغ *انکڑے, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_pad_v2 *pad)
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
    zwp_tablet_seat_v2_جوڑو_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

فراغ Wayland_DisplayInitTabletManager(SDL_Video_انکڑے *display)
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

ساكن فراغ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_تھلے)
{
    إذا (!shutting_تھلے) {
        SDL_WaylandPenTool *tool, *عارضی;
        wl_list_for_each_محفوظ (tool, عارضی, &seat->tablet.tool_list, link) {
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

فراغ Wayland_DisplayCreateSeat(SDL_Video_انکڑے *display, بنية wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, حجم(SDL_WaylandSeat));
    إذا (!seat) {
        أرجع;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_داخل_کرو(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_انکڑے_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_متن_داخلہ(seat);

    wl_seat_سیٹ_user_انکڑے(seat->wl_seat, seat);
    wl_seat_جوڑو_listener(seat->wl_seat, &seat_listener, seat);

    إذا (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

فراغ Wayland_Display_Remove_کھڑکی_References_From_Seats(SDL_Video_انکڑے *display, SDL_کھڑکی_انکڑے *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        إذا (seat->keyboard.focus == کھڑکی) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, کھڑکی->surface);
        }

        إذا (seat->اشارہ_گر_2.focus == کھڑکی) {
            seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = seat->اشارہ_گر_2.focus->surface;
            اشارہ_گر_dispatch_leave(seat, true);
            seat->اشارہ_گر_2.pending_چوکھٹا.leave_surface = عدم;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_نقطہ *tp, *عارضی;
        wl_list_for_each_محفوظ (tp, عارضی, &seat->touch.points, link) {
            إذا (tp->surface == کھڑکی->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == کھڑکی) {
                tool->focus = عدم;
                Wayland_TabletToolUpdateCursor(tool);
                إذا (tool->instance_id) {
                    SDL_RemovePenDevice(0, کھڑکی->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_انکڑے *drop, *drop_عارضی;
        wl_list_for_each_محفوظ (drop, drop_عارضی, &seat->انکڑے_device->pending_drops, link) {
            إذا (drop->dnd_کھڑکی == کھڑکی->sdlwindow) {
                Wayland_کم_Thread_Cancel_کم(display->کم_thread_context, drop->id);

                إذا (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_انکڑے_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_تھلے)
{
    إذا (!seat) {
        أرجع;
    }

    SDL_free(seat->name);

    إذا (seat->انکڑے_device) {
        إذا (seat->انکڑے_device->selection_offer) {
            Wayland_انکڑے_Offer_Destroy(seat->انکڑے_device->selection_offer);
        }
        إذا (seat->انکڑے_device->selection_سروت) {
            Wayland_انکڑے_سروت_Destroy(seat->انکڑے_device->selection_سروت);
        }
        إذا (seat->انکڑے_device->drag_offer) {
            Wayland_انکڑے_Offer_Destroy(seat->انکڑے_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_انکڑے *drop, *drop_عارضی;
        wl_list_for_each_محفوظ (drop, drop_عارضی, &seat->انکڑے_device->pending_drops, link) {
            Wayland_کم_Thread_Cancel_کم(seat->display->کم_thread_context, drop->id);

            إذا (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_انکڑے_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        إذا (seat->انکڑے_device->انکڑے_device) {
            إذا (wl_انکڑے_device_get_نسخہ(seat->انکڑے_device->انکڑے_device) >= WL_انکڑے_DEVICE_RELEASE_SINCE_نسخہ) {
                wl_انکڑے_device_release(seat->انکڑے_device->انکڑے_device);
            } وإلا {
                wl_انکڑے_device_destroy(seat->انکڑے_device->انکڑے_device);
            }
        }
        SDL_free(seat->انکڑے_device->id_str);
        SDL_free(seat->انکڑے_device);
    }

    إذا (seat->primary_selection_device) {
        إذا (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        إذا (seat->primary_selection_device->selection_سروت) {
            Wayland_Primary_Selection_سروت_Destroy(seat->primary_selection_device->selection_سروت);
        }
        إذا (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    إذا (seat->متن_داخلہ.zwp_متن_داخلہ) {
        zwp_متن_داخلہ_v3_destroy(seat->متن_داخلہ.zwp_متن_داخلہ);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_اشارہ_گر(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_تھلے);

    إذا (wl_seat_get_نسخہ(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_نسخہ) {
        wl_seat_release(seat->wl_seat);
    } وإلا {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساكن فراغ Wayland_Seat_Update_Relative_اشارہ_گر(SDL_WaylandSeat *seat)
{
    إذا (seat->display->relative_اشارہ_گر_manager) {
        bool relative_focus = false;

        إذا (seat->اشارہ_گر_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            إذا (seat->اشارہ_گر_2.focus->sdlwindow->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال) {
                إذا (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->اشارہ_گر_2.focus;
                } وإلا {
                    relative_focus = seat->اشارہ_گر_2.focus->keyboard_focus_گنتی != 0;
                }
            } وإلا {
                relative_focus = SDL_GetMouse()->warp_emulation_سرگرم;
            }
        }

        إذا (relative_focus) {
            إذا (!seat->اشارہ_گر_2.relative_اشارہ_گر) {
                seat->اشارہ_گر_2.relative_اشارہ_گر = zwp_relative_اشارہ_گر_manager_v1_get_relative_اشارہ_گر(seat->display->relative_اشارہ_گر_manager, seat->اشارہ_گر_2.wl_اشارہ_گر);
                zwp_relative_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.relative_اشارہ_گر, &relative_اشارہ_گر_listener, seat);
            }
        } وإلا إذا (seat->اشارہ_گر_2.relative_اشارہ_گر) {
            zwp_relative_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.relative_اشارہ_گر);
            seat->اشارہ_گر_2.relative_اشارہ_گر = عدم;
        }
    }
}

ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_انکڑے *display = seat->display;

    إذا (display->کلید_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        إذا (seat->keyboard.کلید_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلید_inhibitor);
            seat->keyboard.کلید_inhibitor = عدم;
        }

        إذا (seat->keyboard.wl_keyboard) {
            SDL_کھڑکی_انکڑے *w = seat->keyboard.focus;
            إذا (w) {
                SDL_کھڑکی *کھڑکی = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                إذا (کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
                    seat->keyboard.کلید_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کلید_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

فراغ Wayland_Seat_Update_اشارہ_گر_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_انکڑے *display = seat->display;
    Wayland_Seat_Update_Relative_اشارہ_گر(seat);

    إذا (display->اشارہ_گر_constraints) {
        إذا (seat->اشارہ_گر_2.locked_اشارہ_گر && !seat->اشارہ_گر_2.relative_اشارہ_گر) {
            zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
            seat->اشارہ_گر_2.locked_اشارہ_گر = عدم;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
        }

        إذا (seat->اشارہ_گر_2.wl_اشارہ_گر) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            إذا (seat->اشارہ_گر_2.relative_اشارہ_گر) {
                إذا (!seat->اشارہ_گر_2.locked_اشارہ_گر) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    إذا (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                        zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                        seat->اشارہ_گر_2.confined_اشارہ_گر = عدم;
                    }

                    seat->اشارہ_گر_2.locked_اشارہ_گر = zwp_اشارہ_گر_constraints_v1_جندرا_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                                           seat->اشارہ_گر_2.focus->surface,
                                                                                           seat->اشارہ_گر_2.wl_اشارہ_گر, عدم,
                                                                                           ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.locked_اشارہ_گر, &locked_اشارہ_گر_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                أرجع;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            إذا (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                seat->اشارہ_گر_2.confined_اشارہ_گر = عدم;
            }

            SDL_کھڑکی_انکڑے *w = seat->اشارہ_گر_2.focus;
            إذا (!w) {
                أرجع;
            }

            SDL_کھڑکی *کھڑکی = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            إذا (!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) ||
                (!(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED) && SDL_Rect_خالی_تھاواں(&کھڑکی->mouse_rect))) {
                أرجع;
            }

            بنية wl_region *confine_rect = عدم;
            إذا (!SDL_Rect_خالی_تھاواں(&کھڑکی->mouse_rect)) {
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
                إذا (!SDL_نقطہ_وچ_Rect(&seat->اشارہ_گر_2.آخری_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحيح closest_x = seat->اشارہ_گر_2.آخری_motion.x;
                    صحيح closest_y = seat->اشارہ_گر_2.آخری_motion.y;

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

            إذا (confine_rect || (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
                إذا (کھڑکی->mouse_rect.w != 1 && کھڑکی->mouse_rect.h != 1) {
                    seat->اشارہ_گر_2.confined_اشارہ_گر =
                        zwp_اشارہ_گر_constraints_v1_confine_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                   w->surface,
                                                                   seat->اشارہ_گر_2.wl_اشارہ_گر,
                                                                   confine_rect,
                                                                   ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.confined_اشارہ_گر,
                                                         &confined_اشارہ_گر_listener,
                                                         seat);
                } وإلا {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->اشارہ_گر_2.locked_اشارہ_گر =
                        zwp_اشارہ_گر_constraints_v1_جندرا_اشارہ_گر(display->اشارہ_گر_constraints,
                                                                w->surface,
                                                                seat->اشارہ_گر_2.wl_اشارہ_گر,
                                                                عدم,
                                                                ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارہ_گر_v1_جوڑو_listener(seat->اشارہ_گر_2.locked_اشارہ_گر,
                                                       &locked_اشارہ_گر_listener,
                                                       seat);
                }
                إذا (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

فراغ Wayland_Display_Update_اشارہ_گر_Grabs(SDL_Video_انکڑے *display, SDL_کھڑکی_انکڑے *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!کھڑکی || seat->اشارہ_گر_2.focus == کھڑکی) {
            Wayland_Seat_Update_اشارہ_گر_Grab(seat);
        }
    }
}

فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_انکڑے *display, SDL_کھڑکی_انکڑے *کھڑکی)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!کھڑکی || seat->keyboard.focus == کھڑکی) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    إذا (serial > seat->آخری_implicit_grab_serial) {
        seat->آخری_implicit_grab_serial = serial;
        seat->display->آخری_implicit_grab_seat = seat;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND
