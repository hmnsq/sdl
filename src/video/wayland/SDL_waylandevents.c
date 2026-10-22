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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

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

#که_تعریف_شوی HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#د_که_پای

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#که_تعریف_شوی SDL_ننوت_LINUXEV
#ضمن <linux/input.h>
#وإلا
#تعریف_کړه BTN_کیڼ    (0x110)
#تعریف_کړه BTN_ښی   (0x111)
#تعریف_کړه BTN_منځ  (0x112)
#تعریف_کړه BTN_SIDE    (0x113)
#تعریف_کړه BTN_EXTRA   (0x114)
#تعریف_کړه BTN_STYLUS  (0x14b)
#تعریف_کړه BTN_STYLUS2 (0x14c)
#تعریف_کړه BTN_STYLUS3 (0x149)
#د_که_پای
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/imKStoUCS.h"
#ضمن <errno.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>
#ضمن <xkbcommon/xkbcommon-compose.h>
#ضمن <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#تعریف_کړه WAYLAND_WHEEL_AXIS_UNIT 10

#که_نه_تعریف_شوی XKB_MOD_NAME_MOD3
#تعریف_کړه XKB_MOD_NAME_MOD3 "Mod3"
#د_که_پای

#که_نه_تعریف_شوی XKB_MOD_NAME_MOD5
#تعریف_کړه XKB_MOD_NAME_MOD5 "Mod5"
#د_که_پای

// Keyboard and mouse names to match XWayland
#تعریف_کړه WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#تعریف_کړه WAYLAND_DEFAULT_اشاره_ګر_NAME "Virtual core pointer"
#تعریف_کړه WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#تعریف_کړه WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_منزل_NS(10)

// Timer rollover detection thresholds
#تعریف_کړه WAYLAND_TIMER_ROLLOVER_INTERVAL_ټیټ  (SDL_MAX_UINT32 / 16U)
#تعریف_کړه WAYLAND_TIMER_ROLLOVER_INTERVAL_لوړ (WAYLAND_TIMER_ROLLOVER_INTERVAL_ټیټ * 15U)

// Scoped function declarations
ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

تعريفنوع بنية
{
    Uint32 کلی;
    SDL_Scancode scancode;
} Wayland_Reserved_کلی;

تعريفنوع بنية
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    بنية wl_surface *surface;

    بنية wl_list link;
} SDL_Wayland_Touch_ټکی;

ساكن فراغ Wayland_Seat_جمع_کړه_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface *surface)
{
    SDL_Wayland_Touch_ټکی *tp = SDL_malloc(حجم(SDL_Wayland_Touch_ټکی));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_ورننباسه(&seat->touch.points, &tp->link);
}

ساكن فراغ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_ټکی *tp)
{
    إذا (tp->surface) {
        SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(tp->surface);

        إذا (کړکۍ_معلومات_2) {
            ثابت عائم x = (عائم)(wl_fixed_منزل_double(tp->fx) / کړکۍ_معلومات_2->current.logical_پلنوالی);
            ثابت عائم y = (عائم)(wl_fixed_منزل_double(tp->fy) / کړکۍ_معلومات_2->current.logical_لوړوالی);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), کړکۍ_معلومات_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --کړکۍ_معلومات_2->فعال_touch_شمېر;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == کړکۍ_معلومات_2->sdlwindow && !کړکۍ_معلومات_2->keyboard_focus_شمېر &&
                !کړکۍ_معلومات_2->اشاره_ګر_focus_شمېر && !کړکۍ_معلومات_2->فعال_touch_شمېر) {
                SDL_سېټ_Mouse_Focus(عدم);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساكن فراغ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface **surface)
{
    SDL_Wayland_Touch_ټکی *tp;

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
    SDL_Wayland_Touch_ټکی *tp;

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

ساكن فراغ Wayland_GetScaledMouseRect(SDL_کړکۍ *کړکۍ, SDL_Rect *scaled_rect)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = کړکۍ->دننی;

    scaled_rect->x = (صحيح)SDL_floor(کړکۍ->mouse_rect.x / کړکۍ_معلومات_2->اشاره_ګر_scale.x);
    scaled_rect->y = (صحيح)SDL_floor(کړکۍ->mouse_rect.y / کړکۍ_معلومات_2->اشاره_ګر_scale.y);
    scaled_rect->w = (صحيح)SDL_ceil(کړکۍ->mouse_rect.w / کړکۍ_معلومات_2->اشاره_ګر_scale.x);
    scaled_rect->h = (صحيح)SDL_ceil(کړکۍ->mouse_rect.h / کړکۍ_معلومات_2->اشاره_ګر_scale.y);
}

ساكن Uint64 Wayland_Adjust_Event_Timestamp_بنسټ(Uint64 nsTimestamp)
{
    ساكن Uint64 timestamp_دننه_واټن = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    إذا (!timestamp_دننه_واټن) {
        timestamp_دننه_واټن = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_دننه_واټن;

    إذا (nsTimestamp > now) {
        timestamp_دننه_واټن -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    أرجع nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساكن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساكن Uint64 timestamp_دننه_واټن = 0;
    ساكن Uint32 وروستی = 0;
    Uint64 timestamp = SDL_MS_منزل_NS(wl_timestamp_ms) + timestamp_دننه_واټن;

    إذا (wl_timestamp_ms >= وروستی) {
        إذا (timestamp_دننه_واټن && وروستی < WAYLAND_TIMER_ROLLOVER_INTERVAL_ټیټ && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_لوړ) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
        } وإلا {
            وروستی = wl_timestamp_ms;
        }
    } وإلا {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        إذا (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_ټیټ && وروستی > WAYLAND_TIMER_ROLLOVER_INTERVAL_لوړ) {
            timestamp_دننه_واټن += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            وروستی = wl_timestamp_ms;
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
    أرجع Wayland_Adjust_Event_Timestamp_بنسټ(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن Uint64 Wayland_Get_اشاره_ګر_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_بنسټ(seat->اشاره_ګر_2.timestamps ? seat->اشاره_ګر_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_بنسټ(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن فراغ ننوت_timestamp_listener(فراغ *معلومات, بنية zwp_ننوت_timestamps_v1 *zwp_ننوت_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)معلومات) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_فی_دوهم) + tv_nsec;
}

ساكن ثابت بنية zwp_ننوت_timestamps_v1_listener timestamp_listener = {
    ننوت_timestamp_listener
};

ساكن فراغ Wayland_Seat_ثبتوونکی_ننوت_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    إذا (seat->display->ننوت_timestamps_manager) {
        إذا (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_ننوت_timestamps_manager_v1_get_keyboard_timestamps(seat->display->ننوت_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_ننوت_timestamps_v1_جمع_کړه_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        إذا (seat->اشاره_ګر_2.wl_اشاره_ګر && !seat->اشاره_ګر_2.timestamps) {
            seat->اشاره_ګر_2.timestamps = zwp_ننوت_timestamps_manager_v1_get_اشاره_ګر_timestamps(seat->display->ننوت_timestamps_manager, seat->اشاره_ګر_2.wl_اشاره_ګر);
            zwp_ننوت_timestamps_v1_جمع_کړه_listener(seat->اشاره_ګر_2.timestamps, &timestamp_listener, &seat->اشاره_ګر_2.highres_timestamp_ns);
        }

        إذا (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_ننوت_timestamps_manager_v1_get_touch_timestamps(seat->display->ننوت_timestamps_manager, seat->touch.wl_touch);
            zwp_ننوت_timestamps_v1_جمع_کړه_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

فراغ Wayland_Display_Init_ننوت_Timestamp_Manager(SDL_Video_معلومات *display)
{
    إذا (display->ننوت_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_ثبتوونکی_ننوت_Timestamp_Listeners(seat);
        }
    }
}

ساكن فراغ handle_pinch_begin(فراغ *معلومات, بنية zwp_اشاره_ګر_gesture_pinch_v1 *zwp_اشاره_ګر_gesture_pinch_v1, uint32_t serial, uint32_t وخت, بنية wl_surface *surface, uint32_t fingers)
{
    إذا (!surface) {
        أرجع;
    }

    SDL_کړکۍ_معلومات *wind = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);
    إذا (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
        seat->اشاره_ګر_2.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_update(فراغ *معلومات, بنية zwp_اشاره_ګر_gesture_pinch_v1 *zwp_اشاره_ګر_gesture_pinch_v1, uint32_t وخت,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (seat->اشاره_ګر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);
        ثابت عائم s = (عائم)wl_fixed_منزل_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->اشاره_ګر_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_پای_ټکی(فراغ *معلومات, بنية zwp_اشاره_ګر_gesture_pinch_v1 *zwp_اشاره_ګر_gesture_pinch_v1, uint32_t serial, uint32_t وخت, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (seat->اشاره_ګر_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);
        SDL_SendPinch(SDL_EVENT_PINCH_پای_ټکی, timestamp, seat->اشاره_ګر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->اشاره_ګر_2.gesture_focus = عدم;
    }
}

ساكن ثابت بنية zwp_اشاره_ګر_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_پای_ټکی
};

ساكن فراغ Wayland_Seat_Create_اشاره_ګر_Gestures(SDL_WaylandSeat *seat)
{
    إذا (seat->display->zwp_اشاره_ګر_gestures) {
        إذا (seat->اشاره_ګر_2.wl_اشاره_ګر && !seat->اشاره_ګر_2.gesture_pinch) {
            seat->اشاره_ګر_2.gesture_pinch = zwp_اشاره_ګر_gestures_v1_get_pinch_gesture(seat->display->zwp_اشاره_ګر_gestures, seat->اشاره_ګر_2.wl_اشاره_ګر);
            zwp_اشاره_ګر_gesture_pinch_v1_سېټ_user_معلومات(seat->اشاره_ګر_2.gesture_pinch, seat);
            zwp_اشاره_ګر_gesture_pinch_v1_جمع_کړه_listener(seat->اشاره_ګر_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_اشاره_ګر_Gesture_Manager(SDL_Video_معلومات *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_اشاره_ګر_Gestures(seat);
    }
}

ساكن فراغ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    إذا (seat->display->cursor_shape_manager) {
        إذا (seat->اشاره_ګر_2.wl_اشاره_ګر && !seat->اشاره_ګر_2.cursor_state.cursor_shape) {
            seat->اشاره_ګر_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_اشاره_ګر(seat->display->cursor_shape_manager, seat->اشاره_ګر_2.wl_اشاره_ګر);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            إذا (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

فراغ Wayland_DisplayInitCursorShapeManager(SDL_Video_معلومات *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

ساكن فراغ Wayland_Seat_سېټ_Keymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    إذا (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_سېټ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_سېټ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساكن فراغ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    طالما (elapsed >= repeat_info->بل_repeat_ns) {
        إذا (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->بنسټ_وخت_ns + repeat_info->بل_repeat_ns;
            SDL_Send_Keyboard_کلی_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_بنسټ(timestamp), repeat_info->keyboard_id, repeat_info->کلی, repeat_info->scancode, true);
        }
        إذا (repeat_info->متن[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(repeat_info->متن);
        }
        repeat_info->بل_repeat_ns += SDL_NS_فی_دوهم / (Uint64)repeat_info->repeat_شرح;
    }
}

ساكن فراغ keyboard_repeat_سېټ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t کلی, Uint32 wl_press_وخت_ms,
                                Uint64 بنسټ_وخت_ns, uint32_t scancode, ثابت حرف *متن)
{
    إذا (!repeat_info->repeat_شرح) {
        أرجع;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->کلی = کلی;
    repeat_info->wl_press_وخت_ms = wl_press_وخت_ms;
    repeat_info->بنسټ_وخت_ns = بنسټ_وخت_ns;
    repeat_info->sdl_press_وخت_ns = SDL_GetTicksNS();
    repeat_info->بل_repeat_ns = SDL_MS_منزل_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    إذا (متن) {
        SDL_strlcpy(repeat_info->متن, متن, SDL_arraysize(repeat_info->متن));
    } وإلا {
        repeat_info->متن[0] = '\0';
    }
}

ساكن فراغ sync_بشپړ_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener sync_listener = {
    sync_بشپړ_handler
};

فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *d = _this->دننی;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    بنية wl_callback *cb = wl_display_sync(d->display);
    wl_callback_جمع_کړه_listener(cb, &sync_listener, عدم);
    WAYLAND_wl_display_flush(d->display);
}

صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_معلومات *d = _this->دننی;
    SDL_WaylandSeat *seat;
    Uint64 پیل = SDL_GetTicksNS();
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret;
    bool poll_alarm_سېټ = false;

#که_تعریف_شوی SDL_USE_IME
    SDL_کړکۍ *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_ننوت_manager && keyboard_focus && SDL_متن_ننوت_فعال(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        إذا (timeoutNS < 0 || SDL_MS_منزل_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_منزل_NS(200);
            poll_alarm_سېټ = true;
        }
    }
#د_که_پای

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->keyboard.repeat.کلی) {
            ثابت Uint64 elapsed = پیل - seat->keyboard.repeat.sdl_press_وخت_ns;
            ثابت Uint64 بل_repeat_wait_وخت = (seat->keyboard.repeat.بل_repeat_ns - elapsed) + 1;
            إذا (timeoutNS < 0 || بل_repeat_wait_وخت <= timeoutNS) {
                timeoutNS = بل_repeat_wait_وخت;
                poll_alarm_سېټ = true;
            }
        }
    }

    إذا (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - پیل;
            پیل = now;
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
            ثابت Uint64 elapsed = now - پیل;
            پیل = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        إذا (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            إذا (ret == 0) {
                أرجع poll_alarm_سېټ ? 1 : 0;
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
    SDL_Video_معلومات *d = _this->دننی;
    SDL_WaylandSeat *seat;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret = 0;

#که_تعریف_شوی SDL_USE_IME
    SDL_کړکۍ *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_ننوت_manager && keyboard_focus && SDL_متن_ننوت_فعال(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#د_که_پای

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#د_که_پای

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
            إذا (seat->keyboard.repeat.کلی) {
                Wayland_Seat_سېټ_Keymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_وخت_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    إذا (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساكن فراغ اشاره_ګر_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = seat->اشاره_ګر_2.focus;
    SDL_کړکۍ *کړکۍ = کړکۍ_معلومات_2 ? کړکۍ_معلومات_2->sdlwindow : عدم;

    إذا (کړکۍ_معلومات_2) {
        مزدوج sx = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.absolute.sx);
        مزدوج sy = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.absolute.sy);

        إذا (seat->اشاره_ګر_2.focus_surface == کړکۍ_معلومات_2->ماسک.surface) {
            sx += (مزدوج)کړکۍ_معلومات_2->ماسک.دننه_واټن_x;
            sy += (مزدوج)کړکۍ_معلومات_2->ماسک.دننه_واټن_y;
        }

        sx *= کړکۍ_معلومات_2->اشاره_ګر_scale.x;
        sy *= کړکۍ_معلومات_2->اشاره_ګر_scale.y;
        إذا (!warp) {
            SDL_SendMouseMotion(seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns, کړکۍ_معلومات_2->sdlwindow, seat->اشاره_ګر_2.sdl_id, false, (عائم)sx, (عائم)sy);
        } وإلا {
            SDL_SendMouseWarp(seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns, کړکۍ_معلومات_2->sdlwindow, seat->اشاره_ګر_2.sdl_id, (عائم)sx, (عائم)sy);
        }

        seat->اشاره_ګر_2.وروستی_motion.x = (صحيح)SDL_floor(sx);
        seat->اشاره_ګر_2.وروستی_motion.y = (صحيح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        إذا (!SDL_Rect_تشه(&کړکۍ->mouse_rect) && !seat->اشاره_ګر_2.is_confined) {
            Wayland_Seat_Update_اشاره_ګر_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        إذا (!(کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE) && کړکۍ->موندنه_test) {
            SDL_موندنه_Test_پایله rc = کړکۍ->موندنه_test(کړکۍ, &seat->اشاره_ګر_2.وروستی_motion, کړکۍ->موندنه_test_معلومات);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            بدل (rc) {
            حالة SDL_HITTEST_RESIZE_TOPLEFT:
                إذا ((کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_سر) &&
                    (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ)) {
                    rc = SDL_HITTEST_نورمال;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_سر) {
                    rc = SDL_HITTEST_RESIZE_کیڼ;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ) {
                    rc = SDL_HITTEST_RESIZE_سر;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_سر:
                إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_سر) {
                    rc = SDL_HITTEST_نورمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                إذا ((کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_سر) &&
                    (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ښی)) {
                    rc = SDL_HITTEST_نورمال;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_سر) {
                    rc = SDL_HITTEST_RESIZE_ښی;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ښی) {
                    rc = SDL_HITTEST_RESIZE_سر;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_ښی:
                إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ښی) {
                    rc = SDL_HITTEST_نورمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                إذا ((کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ښی)) {
                    rc = SDL_HITTEST_نورمال;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ښی;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ښی) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOM:
                إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_نورمال;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                إذا ((کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ)) {
                    rc = SDL_HITTEST_نورمال;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_کیڼ;
                } وإلا إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_کیڼ:
                إذا (کړکۍ_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ) {
                    rc = SDL_HITTEST_نورمال;
                }
                اكسر;
            افتراضي:
                اكسر;
            }

            إذا (rc != کړکۍ_معلومات_2->موندنه_test_پایله) {
                کړکۍ_معلومات_2->موندنه_test_پایله = rc;
                Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
            }
        }
    }
}

ساكن فراغ اشاره_ګر_handle_motion(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                  uint32_t وخت, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    ثابت Uint64 timestamp = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);

    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sx = sx;
    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sy = sy;

    إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) >= WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        seat->اشاره_ګر_2.pending_چوکاټ.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        إذا (!seat->اشاره_ګر_2.pending_چوکاټ.have_relative || seat->اشاره_ګر_2.timestamps) {
            seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = timestamp;
        }
    } وإلا {
        seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = timestamp;
        اشاره_ګر_dispatch_absolute_motion(seat, false);
    }
}

ساكن فراغ اشاره_ګر_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_کړکۍ_معلومات *کړکۍ = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(seat->اشاره_ګر_2.pending_چوکاټ.enter_surface);
    إذا (!کړکۍ) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        أرجع;
    }

    إذا (کړکۍ->surface != seat->اشاره_ګر_2.pending_چوکاټ.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_سېټ_Default_Cursor(seat);
        أرجع;
    }

    seat->اشاره_ګر_2.focus = کړکۍ;
    seat->اشاره_ګر_2.focus_surface = seat->اشاره_ګر_2.pending_چوکاټ.enter_surface;
    ++کړکۍ->اشاره_ګر_focus_شمېر;
    SDL_سېټ_Mouse_Focus(کړکۍ->sdlwindow);

    // Send the initial position.
    اشاره_ګر_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_اشاره_ګر_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
}

ساكن فراغ اشاره_ګر_handle_enter(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                 uint32_t serial, بنية wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.pending_چوکاټ.enter_surface = surface;
    seat->اشاره_ګر_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sx = sx_w;
    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sy = sy_w;

    إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) < WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = 0;
        اشاره_ګر_dispatch_enter(seat);
    }
}

ساكن فراغ اشاره_ګر_dispatch_leave(SDL_WaylandSeat *seat, bool update_اشاره_ګر)
{
    SDL_کړکۍ_معلومات *کړکۍ = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(seat->اشاره_ګر_2.pending_چوکاټ.leave_surface);

    إذا (کړکۍ) {
        إذا (seat->اشاره_ګر_2.focus) {
            إذا (seat->اشاره_ګر_2.focus->surface == seat->اشاره_ګر_2.pending_چوکاټ.leave_surface) {
                // Clear the capture flag and raise all buttons
                کړکۍ->sdlwindow->flags &= ~SDL_کړکۍ_MOUSE_CAPTURE;

                seat->اشاره_ګر_2.focus = عدم;
                seat->اشاره_ګر_2.focus_surface = عدم;
                لكل (Uint8 i = 1; seat->اشاره_ګر_2.buttons_pressed; ++i) {
                    إذا (seat->اشاره_ګر_2.buttons_pressed & SDL_BUTTON_ماسک(i)) {
                        SDL_SendMouseButton(0, کړکۍ->sdlwindow, seat->اشاره_ګر_2.sdl_id, i, false);
                        seat->اشاره_ګر_2.buttons_pressed &= ~SDL_BUTTON_ماسک(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_کړکۍ *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && کړکۍ->sdlwindow == mouse_focus;
                إذا (!--کړکۍ->اشاره_ګر_focus_شمېر && had_focus && !کړکۍ->فعال_touch_شمېر) {
                    SDL_سېټ_Mouse_Focus(عدم);
                }

                إذا (update_اشاره_ګر) {
                    Wayland_Seat_Update_اشاره_ګر_Grab(seat);
                    Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
                }
            }
        } وإلا إذا (update_اشاره_ګر) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساكن فراغ اشاره_ګر_handle_leave(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                 uint32_t serial, بنية wl_surface *surface)
{
    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = surface;
    إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) < WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        اشاره_ګر_dispatch_leave(seat, true);
    }
}

ساكن bool Wayland_Process_موندنه_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    إذا (seat->اشاره_ګر_2.locked_اشاره_ګر) {
        أرجع false;
    }

    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = seat->اشاره_ګر_2.focus;
    SDL_کړکۍ *کړکۍ = کړکۍ_معلومات_2->sdlwindow;

    إذا (کړکۍ->موندنه_test) {
        ساكن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_څنډه_سر_کیڼ, XDG_TOPLEVEL_RESIZE_څنډه_سر,
            XDG_TOPLEVEL_RESIZE_څنډه_سر_ښی, XDG_TOPLEVEL_RESIZE_څنډه_ښی,
            XDG_TOPLEVEL_RESIZE_څنډه_BOTTOM_ښی, XDG_TOPLEVEL_RESIZE_څنډه_BOTTOM,
            XDG_TOPLEVEL_RESIZE_څنډه_BOTTOM_کیڼ, XDG_TOPLEVEL_RESIZE_څنډه_کیڼ
        };

#که_تعریف_شوی HAVE_LIBDECOR_H
        ساكن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_څنډه_سر_کیڼ, LIBDECOR_RESIZE_څنډه_سر,
            LIBDECOR_RESIZE_څنډه_سر_ښی, LIBDECOR_RESIZE_څنډه_ښی,
            LIBDECOR_RESIZE_څنډه_BOTTOM_ښی, LIBDECOR_RESIZE_څنډه_BOTTOM,
            LIBDECOR_RESIZE_څنډه_BOTTOM_کیڼ, LIBDECOR_RESIZE_څنډه_کیڼ
        };
#د_که_پای

        بدل (کړکۍ_معلومات_2->موندنه_test_پایله) {
        حالة SDL_HITTEST_DRAGGABLE:
#که_تعریف_شوی HAVE_LIBDECOR_H
            إذا (کړکۍ_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (کړکۍ_معلومات_2->shell_surface.libdecor.چوکاټ) {
                    libdecor_چوکاټ_move(کړکۍ_معلومات_2->shell_surface.libdecor.چوکاټ,
                                        seat->wl_seat,
                                        serial);
                }
            } وإلا
#د_که_پای
                إذا (کړکۍ_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (کړکۍ_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(کړکۍ_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_سر:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_ښی:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_کیڼ:
#که_تعریف_شوی HAVE_LIBDECOR_H
            إذا (کړکۍ_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (کړکۍ_معلومات_2->shell_surface.libdecor.چوکاټ) {
                    libdecor_چوکاټ_resize(کړکۍ_معلومات_2->shell_surface.libdecor.چوکاټ,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[کړکۍ_معلومات_2->موندنه_test_پایله - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وإلا
#د_که_پای
                إذا (کړکۍ_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (کړکۍ_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(کړکۍ_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[کړکۍ_معلومات_2->موندنه_test_پایله - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ اشاره_ګر_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool ښکته)
{
    SDL_کړکۍ_معلومات *کړکۍ = seat->اشاره_ګر_2.focus;

    إذا (کړکۍ) {
        bool ignore_click = false;

        إذا (ښکته) {
            seat->اشاره_ګر_2.buttons_pressed |= SDL_BUTTON_ماسک(sdl_button);

            إذا (sdl_button == SDL_BUTTON_کیڼ && Wayland_Process_موندنه_Test(seat, seat->وروستی_implicit_grab_serial)) {
                أرجع; // don't pass this event on to app.
            }
        } وإلا {
            seat->اشاره_ګر_2.buttons_pressed &= ~SDL_BUTTON_ماسک(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        إذا (کړکۍ->وروستی_focus_event_وخت_ns) {
            إذا (ښکته && (SDL_GetTicksNS() - کړکۍ->وروستی_focus_event_وخت_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            کړکۍ->وروستی_focus_event_وخت_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        إذا (!seat->اشاره_ګر_2.relative_اشاره_ګر) {
            إذا (seat->اشاره_ګر_2.buttons_pressed != 0) {
                کړکۍ->sdlwindow->flags |= SDL_کړکۍ_MOUSE_CAPTURE;
            } وإلا {
                کړکۍ->sdlwindow->flags &= ~SDL_کړکۍ_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                إذا (seat->اشاره_ګر_2.focus_surface != کړکۍ->surface) {
                    seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = کړکۍ->surface;
                }
            }
        }

        إذا (!ignore_click) {
            SDL_SendMouseButton(seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns, کړکۍ->sdlwindow, seat->اشاره_ګر_2.sdl_id, sdl_button, ښکته);
        }
    }
}

ساكن فراغ اشاره_ګر_handle_button(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2, uint32_t serial,
                                  uint32_t وخت, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = معلومات;
    Uint8 sdl_button;

    بدل (button) {
    حالة BTN_کیڼ:
        sdl_button = SDL_BUTTON_کیڼ;
        اكسر;
    حالة BTN_منځ:
        sdl_button = SDL_BUTTON_منځ;
        اكسر;
    حالة BTN_ښی:
        sdl_button = SDL_BUTTON_ښی;
        اكسر;
    افتراضي:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        اكسر;
    }

    إذا (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        إذا (state_w) {
            seat->اشاره_ګر_2.pending_چوکاټ.buttons_pressed |= SDL_BUTTON_ماسک(sdl_button);
        } وإلا {
            seat->اشاره_ګر_2.pending_چوکاټ.buttons_released |= SDL_BUTTON_ماسک(sdl_button);
        }
    } وإلا {
        اشاره_ګر_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساكن فراغ اشاره_ګر_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t ارزښت)
{
    SDL_کړکۍ_معلومات *کړکۍ = seat->اشاره_ګر_2.focus;
    ثابت تعداد wl_اشاره_ګر_axis a = axis;

    إذا (seat->اشاره_ګر_2.focus) {
        عائم x, y;

        بدل (a) {
        حالة WL_اشاره_ګر_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (عائم)wl_fixed_منزل_double(ارزښت);
            اكسر;
        حالة WL_اشاره_ګر_AXIS_HORIZONTAL_SCROLL:
            x = (عائم)wl_fixed_منزل_double(ارزښت);
            y = 0;
            اكسر;
        افتراضي:
            أرجع;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, کړکۍ->sdlwindow, seat->اشاره_ګر_2.sdl_id, x, y, SDL_MOUSEWHEEL_نورمال);
    }
}

ساكن فراغ اشاره_ګر_handle_axis_common(SDL_WaylandSeat *seat, تعداد SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t ارزښت)
{
    ثابت تعداد wl_اشاره_ګر_axis a = axis;

    إذا (seat->اشاره_ګر_2.focus) {
        seat->اشاره_ګر_2.pending_چوکاټ.have_axis = true;

        بدل (a) {
        حالة WL_اشاره_ګر_AXIS_VERTICAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.y = 0.0f;
                }
                seat->اشاره_ګر_2.pending_چوکاټ.axis.y += 0 - (عائم)wl_fixed_منزل_double(ارزښت);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.y = 0 - (عائم)wl_fixed_منزل_double(ارزښت);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.y = 0 - (عائم)wl_fixed_منزل_double(ارزښت);
                }
                اكسر;
            }
            اكسر;
        حالة WL_اشاره_ګر_AXIS_HORIZONTAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.x = 0.0f;
                }
                seat->اشاره_ګر_2.pending_چوکاټ.axis.x += (عائم)wl_fixed_منزل_double(ارزښت);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.x = (عائم)wl_fixed_منزل_double(ارزښت);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشاره_ګر_2.pending_چوکاټ.axis.x = (عائم)wl_fixed_منزل_double(ارزښت);
                }
                اكسر;
            }
            اكسر;
        }
    }
}

ساكن فراغ اشاره_ګر_handle_axis(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                uint32_t وخت, uint32_t axis, wl_fixed_t ارزښت)
{
    SDL_WaylandSeat *seat = معلومات;
    ثابت Uint64 nsTimestamp = Wayland_Get_اشاره_ګر_Timestamp(seat, وخت);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = nsTimestamp;
        اشاره_ګر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, ارزښت);
    } وإلا {
        اشاره_ګر_handle_axis_common_v1(seat, nsTimestamp, axis, ارزښت);
    }
}

ساكن فراغ اشاره_ګر_handle_axis_relative_direction(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = معلومات;

    بدل (axis_relative_direction) {
    حالة WL_اشاره_ګر_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->اشاره_ګر_2.pending_چوکاټ.axis.direction = SDL_MOUSEWHEEL_نورمال;
        اكسر;
    حالة WL_اشاره_ګر_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->اشاره_ګر_2.pending_چوکاټ.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        اكسر;
    }
}

ساكن فراغ اشاره_ګر_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_کړکۍ_معلومات *کړکۍ = seat->اشاره_ګر_2.focus;

    إذا (کړکۍ) {
        SDL_Mouse *mouse = SDL_GetMouse();
        مزدوج dx;
        مزدوج dy;
        إذا (mouse->ننوت_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.relative.dx_unaccel);
            dy = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.relative.dy_unaccel);
        } وإلا {
            dx = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.relative.dx) * کړکۍ->اشاره_ګر_scale.x;
            dy = wl_fixed_منزل_double(seat->اشاره_ګر_2.pending_چوکاټ.relative.dy) * کړکۍ->اشاره_ګر_scale.y;
        }

        SDL_SendMouseMotion(seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns, کړکۍ->sdlwindow, seat->اشاره_ګر_2.sdl_id, true, (عائم)dx, (عائم)dy);
    }
}

ساكن فراغ اشاره_ګر_dispatch_axis(SDL_WaylandSeat *seat)
{
    عائم x, y;
    SDL_MouseWheelDirection direction = seat->اشاره_ګر_2.pending_چوکاټ.axis.direction;

    بدل (seat->اشاره_ګر_2.pending_چوکاټ.axis.x_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->اشاره_ګر_2.pending_چوکاټ.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->اشاره_ګر_2.pending_چوکاټ.axis.x;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->اشاره_ګر_2.pending_چوکاټ.axis.x / 120.0f;
        اكسر;
    افتراضي:
        x = 0.0f;
        اكسر;
    }

    بدل (seat->اشاره_ګر_2.pending_چوکاټ.axis.y_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->اشاره_ګر_2.pending_چوکاټ.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->اشاره_ګر_2.pending_چوکاټ.axis.y;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->اشاره_ګر_2.pending_چوکاټ.axis.y / 120.0f;
        اكسر;
    افتراضي:
        y = 0.0f;
        اكسر;
    }

    SDL_SendMouseWheel(seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns,
                       seat->اشاره_ګر_2.focus->sdlwindow, seat->اشاره_ګر_2.sdl_id, x, y, direction);
}

ساكن فراغ اشاره_ګر_handle_چوکاټ(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2)
{
    SDL_WaylandSeat *seat = معلومات;

    إذا (seat->اشاره_ګر_2.pending_چوکاټ.enter_surface) {
        إذا (seat->اشاره_ګر_2.pending_چوکاټ.leave_surface) {
            SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = seat->اشاره_ګر_2.focus;
            SDL_کړکۍ_معلومات *new_focus = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(seat->اشاره_ګر_2.pending_چوکاټ.enter_surface);

            إذا (کړکۍ_معلومات_2 && (کړکۍ_معلومات_2->sdlwindow->flags & SDL_کړکۍ_MOUSE_CAPTURE) && کړکۍ_معلومات_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->اشاره_ګر_2.focus_surface = seat->اشاره_ګر_2.pending_چوکاټ.enter_surface;
                seat->اشاره_ګر_2.pending_چوکاټ.enter_surface = عدم;
                seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = عدم;
            } وإلا {
                // Leaving the previous surface before entering a new surface.
                اشاره_ګر_dispatch_leave(seat, false);
                seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = عدم;
            }
        }

        إذا (seat->اشاره_ګر_2.pending_چوکاټ.enter_surface) {
            اشاره_ګر_dispatch_enter(seat);
        }
    }

    إذا (seat->اشاره_ګر_2.pending_چوکاټ.have_absolute) {
        اشاره_ګر_dispatch_absolute_motion(seat, seat->اشاره_ګر_2.pending_چوکاټ.have_warp);
    }

    إذا (seat->اشاره_ګر_2.pending_چوکاټ.have_relative) {
        اشاره_ګر_dispatch_relative_motion(seat);
    }

    لكل (Uint8 i = 1; seat->اشاره_ګر_2.pending_چوکاټ.buttons_pressed || seat->اشاره_ګر_2.pending_چوکاټ.buttons_released; ++i) {
        ثابت Uint32 ماسک = SDL_BUTTON_ماسک(i);
        إذا (seat->اشاره_ګر_2.pending_چوکاټ.buttons_pressed & ماسک) {
            اشاره_ګر_dispatch_button(seat, i, true);
            seat->اشاره_ګر_2.pending_چوکاټ.buttons_pressed &= ~ماسک;
        }
        إذا (seat->اشاره_ګر_2.pending_چوکاټ.buttons_released & ماسک) {
            اشاره_ګر_dispatch_button(seat, i, false);
            seat->اشاره_ګر_2.pending_چوکاټ.buttons_released &= ~ماسک;
        }
    }

    إذا (seat->اشاره_ګر_2.pending_چوکاټ.have_axis) {
        اشاره_ګر_dispatch_axis(seat);
    }

    إذا (seat->اشاره_ګر_2.pending_چوکاټ.leave_surface) {
        اشاره_ګر_dispatch_leave(seat, true);
    }

    SDL_zero(seat->اشاره_ګر_2.pending_چوکاټ);
}

ساكن فراغ اشاره_ګر_handle_axis_سرچینه(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                       uint32_t axis_سرچینه)
{
    // unimplemented
}

ساكن فراغ اشاره_ګر_handle_axis_stop(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                     uint32_t وخت, uint32_t axis)
{
    // unimplemented
}

ساكن فراغ اشاره_ګر_handle_axis_discrete(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = معلومات;
    اشاره_ګر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساكن فراغ اشاره_ګر_handle_axis_value120(فراغ *معلومات, بنية wl_اشاره_ګر *اشاره_ګر_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = معلومات;
    اشاره_ګر_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساكن فراغ اشاره_ګر_handle_warp(فراغ *معلومات, بنية wl_اشاره_ګر *wl_اشاره_ګر, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    seat->اشاره_ګر_2.pending_چوکاټ.have_absolute = true;
    seat->اشاره_ګر_2.pending_چوکاټ.have_warp = true;
    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sx = surface_x;
    seat->اشاره_ګر_2.pending_چوکاټ.absolute.sy = surface_y;
}

ساكن ثابت بنية wl_اشاره_ګر_listener اشاره_ګر_listener = {
    اشاره_ګر_handle_enter,
    اشاره_ګر_handle_leave,
    اشاره_ګر_handle_motion,
    اشاره_ګر_handle_button,
    اشاره_ګر_handle_axis,
    اشاره_ګر_handle_چوکاټ,                   // Version 5
    اشاره_ګر_handle_axis_سرچینه,             // Version 5
    اشاره_ګر_handle_axis_stop,               // Version 5
    اشاره_ګر_handle_axis_discrete,           // Version 5
    اشاره_ګر_handle_axis_value120,           // Version 8
    اشاره_ګر_handle_axis_relative_direction, // Version 9
    اشاره_ګر_handle_warp                     // Version 11
};

ساكن فراغ relative_اشاره_ګر_handle_relative_motion(فراغ *معلومات,
                                                    بنية zwp_relative_اشاره_ګر_v1 *اشاره_ګر_2,
                                                    uint32_t وخت_hi,
                                                    uint32_t وخت_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = معلومات;

    // Relative pointer event times are in microsecond granularity.
    seat->اشاره_ګر_2.pending_چوکاټ.relative.dx = dx;
    seat->اشاره_ګر_2.pending_چوکاټ.relative.dy = dy;
    seat->اشاره_ګر_2.pending_چوکاټ.relative.dx_unaccel = dx_unaccel;
    seat->اشاره_ګر_2.pending_چوکاټ.relative.dy_unaccel = dy_unaccel;
    seat->اشاره_ګر_2.pending_چوکاټ.timestamp_ns = Wayland_Adjust_Event_Timestamp_بنسټ(SDL_US_منزل_NS(((Uint64)وخت_hi << 32) | (Uint64)وخت_lo));

    إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) >= WL_اشاره_ګر_چوکاټ_SINCE_نسخه) {
        seat->اشاره_ګر_2.pending_چوکاټ.have_relative = true;
    } وإلا {
        اشاره_ګر_dispatch_relative_motion(seat);
    }
}

ساكن ثابت بنية zwp_relative_اشاره_ګر_v1_listener relative_اشاره_ګر_listener = {
    relative_اشاره_ګر_handle_relative_motion,
};

ساكن فراغ locked_اشاره_ګر_locked(فراغ *معلومات, بنية zwp_locked_اشاره_ګر_v1 *locked_اشاره_ګر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.is_confined = true;
}

ساكن فراغ locked_اشاره_ګر_unlocked(فراغ *معلومات, بنية zwp_locked_اشاره_ګر_v1 *locked_اشاره_ګر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.is_confined = false;
}

ساكن ثابت بنية zwp_locked_اشاره_ګر_v1_listener locked_اشاره_ګر_listener = {
    locked_اشاره_ګر_locked,
    locked_اشاره_ګر_unlocked,
};

ساكن فراغ confined_اشاره_ګر_confined(فراغ *معلومات, بنية zwp_confined_اشاره_ګر_v1 *confined_اشاره_ګر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.is_confined = true;
}

ساكن فراغ confined_اشاره_ګر_unconfined(فراغ *معلومات, بنية zwp_confined_اشاره_ګر_v1 *confined_اشاره_ګر)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشاره_ګر_2.is_confined = false;
}

ساكن ثابت بنية zwp_confined_اشاره_ګر_v1_listener confined_اشاره_ګر_listener = {
    confined_اشاره_ګر_confined,
    confined_اشاره_ګر_unconfined,
};

ساكن فراغ touch_handler_ښکته(فراغ *معلومات, بنية wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, بنية wl_surface *surface,
                               صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2;

    // Check that this surface is valid.
    إذا (!surface) {
        أرجع;
    }

    Wayland_Seat_جمع_کړه_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    کړکۍ_معلومات_2 = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);

    إذا (کړکۍ_معلومات_2 && کړکۍ_معلومات_2->surface == surface) {
        عائم x, y;

        إذا (کړکۍ_معلومات_2->current.logical_پلنوالی <= 1) {
            x = 0.5f;
        } وإلا {
            x = (عائم)wl_fixed_منزل_double(fx) / (کړکۍ_معلومات_2->current.logical_پلنوالی - 1);
        }
        إذا (کړکۍ_معلومات_2->current.logical_لوړوالی <= 1) {
            y = 0.5f;
        } وإلا {
            y = (عائم)wl_fixed_منزل_double(fy) / (کړکۍ_معلومات_2->current.logical_لوړوالی - 1);
        }

        ++کړکۍ_معلومات_2->فعال_touch_شمېر;
        SDL_سېټ_Mouse_Focus(کړکۍ_معلومات_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), کړکۍ_معلومات_2->sdlwindow, SDL_EVENT_FINGER_ښکته, x, y, 1.0f);
    }
}

ساكن فراغ touch_handler_پورته(فراغ *معلومات, بنية wl_touch *touch, uint32_t serial, uint32_t timestamp, صحيح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    wl_fixed_t fx = 0, fy = 0;
    بنية wl_surface *surface = عدم;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    إذا (surface) {
        SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);

        إذا (کړکۍ_معلومات_2 && کړکۍ_معلومات_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / کړکۍ_معلومات_2->current.logical_پلنوالی;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / کړکۍ_معلومات_2->current.logical_لوړوالی;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), کړکۍ_معلومات_2->sdlwindow, SDL_EVENT_FINGER_پورته, x, y, 0.0f);

            --کړکۍ_معلومات_2->فعال_touch_شمېر;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == کړکۍ_معلومات_2->sdlwindow && !کړکۍ_معلومات_2->keyboard_focus_شمېر &&
                !کړکۍ_معلومات_2->اشاره_ګر_focus_شمېر && !کړکۍ_معلومات_2->فعال_touch_شمېر) {
                SDL_سېټ_Mouse_Focus(عدم);
            }
        }
    }
}

ساكن فراغ touch_handler_motion(فراغ *معلومات, بنية wl_touch *touch, uint32_t timestamp, صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    بنية wl_surface *surface = عدم;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    إذا (surface) {
        SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);

        إذا (کړکۍ_معلومات_2 && کړکۍ_معلومات_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / کړکۍ_معلومات_2->current.logical_پلنوالی;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / کړکۍ_معلومات_2->current.logical_لوړوالی;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), کړکۍ_معلومات_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ساكن فراغ touch_handler_چوکاټ(فراغ *معلومات, بنية wl_touch *touch)
{
}

ساكن فراغ touch_handler_cancel(فراغ *معلومات, بنية wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    SDL_Wayland_Touch_ټکی *tp, *لنډمهاله;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_خوندي (tp, لنډمهاله, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

ساكن فراغ touch_handler_shape(فراغ *معلومات, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

ساكن فراغ touch_handler_orientation(فراغ *معلومات, بنية wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

ساكن ثابت بنية wl_touch_listener touch_listener = {
    touch_handler_ښکته,
    touch_handler_پورته,
    touch_handler_motion,
    touch_handler_چوکاټ,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#إذا !SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
ساكن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t کلی, xkb_layout_شاخص_t layout, xkb_level_شاخص_t level, xkb_mod_ماسک_t *masks_بهر, size_t masks_اندازه)
{
    إذا (!masks_بهر || !masks_اندازه) {
        أرجع 0;
    }

    // Level 0 is always unmodified, so early out.
    إذا (level == 0) {
        *masks_بهر = 0;
        أرجع 1;
    }

    size_t ماسک_idx = 0;
    ثابت xkb_mod_ماسک_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.ښويدنه_ماسک,
        seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.ښويدنه_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level3_ماسک,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.ښويدنه_ماسک,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.ښويدنه_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level5_ماسک,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.ښويدنه_ماسک,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.caps_ماسک_2,
        seat->keyboard.xkb.level5_ماسک | seat->keyboard.xkb.ښويدنه_ماسک | seat->keyboard.xkb.caps_ماسک_2
    };
    ثابت xkb_mod_ماسک_t pressed_mod_ماسک = seat->keyboard.xkb.ښويدنه_ماسک | seat->keyboard.xkb.level3_ماسک | seat->keyboard.xkb.level5_ماسک;
    ثابت xkb_mod_ماسک_t locked_mod_ماسک = seat->keyboard.xkb.caps_ماسک_2;

    لكل (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_ماسک, 0, keymod_masks[i] & locked_mod_ماسک, 0, 0, layout);
        إذا (WAYLAND_xkb_state_کلی_get_level(seat->keyboard.xkb.state, کلی, layout) == level) {
            masks_بهر[ماسک_idx] = keymod_masks[i];

            إذا (++ماسک_idx == masks_اندازه) {
                اكسر;
            }
        }
    }

    أرجع ماسک_idx;
}
#د_که_پای

ساكن فراغ Wayland_KeymapIterator(بنية xkb_keymap *keymap, xkb_keycode_t کلی, فراغ *معلومات)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_ماسک_t xkb_valid_mod_ماسک = seat->keyboard.xkb.ښويدنه_ماسک |
                                              seat->keyboard.xkb.alt_ماسک |
                                              seat->keyboard.xkb.level3_ماسک |
                                              seat->keyboard.xkb.level5_ماسک |
                                              seat->keyboard.xkb.caps_ماسک_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلی - 8);
    }

    لكل (xkb_layout_شاخص_t layout = 0; layout < seat->keyboard.xkb.عدد_layouts; ++layout) {
        ثابت xkb_level_شاخص_t عدد_پوړونه = WAYLAND_xkb_keymap_عدد_پوړونه_for_کلی(seat->keyboard.xkb.keymap, کلی, layout);
        لكل (xkb_level_شاخص_t level = 0; level < عدد_پوړونه; ++level) {
            إذا (WAYLAND_xkb_keymap_کلی_get_syms_by_level(seat->keyboard.xkb.keymap, کلی, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                إذا (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_کلی_Sym(syms[0], کلی);
                    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                        استمر;
                    }
                }

                xkb_mod_ماسک_t xkb_mod_masks[16];
#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
                ثابت size_t عدد_masks = WAYLAND_xkb_keymap_کلی_get_mods_for_level(seat->keyboard.xkb.keymap, کلی, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وإلا
                ثابت size_t عدد_masks = xkb_legacy_get_mods_for_level(seat, کلی, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#د_که_پای
                لكل (size_t ماسک = 0; ماسک < عدد_masks; ++ماسک) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    إذا ((xkb_mod_masks[ماسک] | xkb_valid_mod_ماسک) != xkb_valid_mod_ماسک) {
                        استمر;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[ماسک] & seat->keyboard.xkb.ښويدنه_ماسک ? SDL_KMOD_ښويدنه : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.alt_ماسک ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.level3_ماسک ? SDL_KMOD_ډېرپېښ : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.level5_ماسک ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[ماسک] & seat->keyboard.xkb.caps_ماسک_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_کلی_کوډ_From_کلی_Sym(syms[0], کلی, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    إذا (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_بل_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        إذا (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_سېټ_Keymap_ثبت(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_کلی *res = WAYLAND_wl_array_جمع_کړه(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_کلی));
                        إذا (res) {
                            res->scancode = scancode;
                            res->کلی = کلی - 8;
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

                    SDL_سېټ_Keymap_ثبت(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساكن فراغ keyboard_handle_keymap(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                   uint32_t format, صحيح fd, uint32_t اندازه)
{
    SDL_WaylandSeat *seat = معلومات;
    حرف *map_str;

    إذا (!معلومات) {
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
        SDL_سېټ_Error("failed to compile keymap");
        أرجع;
    }

    // Clear the old layouts.
    لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = عدم;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.عدد_layouts = 0;

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 10, 0)
    seat->keyboard.xkb.ښويدنه_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_ښويدنه);
    seat->keyboard.xkb.ctrl_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.عدد_ماسک = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_عدد);
    seat->keyboard.xkb.caps_ماسک_2 = WAYLAND_xkb_keymap_mod_get_ماسک(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وإلا
#تعریف_کړه GET_MOD_شاخص(mod) \
    WAYLAND_xkb_keymap_mod_get_شاخص(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.ښويدنه_ماسک = 1 << GET_MOD_شاخص(ښويدنه_2);
    seat->keyboard.xkb.ctrl_ماسک = 1 << GET_MOD_شاخص(CTRL);
    seat->keyboard.xkb.alt_ماسک = 1 << GET_MOD_شاخص(ALT);
    seat->keyboard.xkb.gui_ماسک = 1 << GET_MOD_شاخص(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_ماسک = 1 << GET_MOD_شاخص(MOD5);
    seat->keyboard.xkb.level5_ماسک = 1 << GET_MOD_شاخص(MOD3);
    seat->keyboard.xkb.عدد_ماسک = 1 << GET_MOD_شاخص(عدد_2);
    seat->keyboard.xkb.caps_ماسک_2 = 1 << GET_MOD_شاخص(CAPS);
#تعریف_لغوه GET_MOD_شاخص
#د_که_پای

    إذا (seat->keyboard.xkb.state != عدم) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = عدم;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    إذا (!seat->keyboard.xkb.state) {
        SDL_سېټ_Error("failed to create XKB state");
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

        لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
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

        WAYLAND_xkb_keymap_کلی_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.عدد_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_سېټ_Keymap(seat);
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
                SDL_سېټ_Error("could not create XKB compose state");
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
ساكن SDL_Scancode Wayland_Get_Scancode_For_کلی(SDL_WaylandSeat *seat, Uint32 کلی, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, کلی);

        // No table entry? Check the reserved list.
        إذا (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_کلی *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                إذا (i->کلی == کلی) {
                    أرجع i->scancode;
                }
            }
        }
    } وإلا {
        ثابت xkb_keysym_t *keysym;
        إذا (WAYLAND_xkb_state_کلی_get_syms(seat->keyboard.xkb.state, کلی + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_کلی_Sym(keysym[0], کلی + 8);
            إذا (syms) {
                *syms = keysym;
            }
        }
    }

    أرجع scancode;
}

ساكن فراغ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool کلی_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    إذا (!کلی_pressed) {
        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ښويدنه_ماسک) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ښويدنه)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ښويدنه;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ښويدنه;
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
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ډېرپېښ)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ډېرپېښ;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ډېرپېښ;
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

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.ښويدنه_ماسک) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_ښويدنه) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ښويدنه;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ښويدنه);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_ښويدنه)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ښويدنه;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ښويدنه;
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
        seat->keyboard.locked_modifiers |= SDL_KMOD_ډېرپېښ;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ډېرپېښ;
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

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.عدد_ماسک) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_عدد;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_عدد;
    }

    SDL_سېټ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساكن فراغ Wayland_Handle_Modifier_کلیګانې(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_کلی_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
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
    حالة SDLK_ډېرپېښ:
        mod = SDL_KMOD_ډېرپېښ;
        اكسر;
    حالة SDLK_LEVEL5_ښويدنه:
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

ساكن فراغ keyboard_handle_enter(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface,
                                  بنية wl_array *کلیګانې)
{
    SDL_WaylandSeat *seat = معلومات;
    uint32_t *کلی;

    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_کړکۍ_معلومات *کړکۍ = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);
    إذا (!کړکۍ) {
        // Not a surface owned by SDL.
        أرجع;
    }

    ++کړکۍ->keyboard_focus_شمېر;
    seat->keyboard.focus = کړکۍ;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_سېټ_Keyboard_Focus(کړکۍ->sdlwindow->keyboard_focus ? کړکۍ->sdlwindow->keyboard_focus : کړکۍ->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشاره_ګر_Grabs(seat->display, کړکۍ);

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_ننوت(seat);

#که_تعریف_شوی SDL_USE_IME
    إذا (!seat->متن_ننوت.zwp_متن_ننوت) {
        SDL_IME_سېټ_Focus(true);
    }
#د_که_پای

    Uint64 timestamp = SDL_GetTicksNS();
    کړکۍ->وروستی_focus_event_وخت_ns = timestamp;

    Wayland_Seat_سېټ_Keymap(seat);

    wl_array_for_each (کلی, کلیګانې) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_کلی(seat, *کلی, عدم);
        إذا (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_کلی_From_Scancode(scancode, SDL_KMOD_NONE, false);

            بدل (keycode) {
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_ډېرپېښ:
            حالة SDLK_LEVEL5_ښويدنه:
                Wayland_Handle_Modifier_کلیګانې(seat, scancode, true);
                SDL_Send_Keyboard_کلی_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *کلی, scancode, true);
                اكسر;
            افتراضي:
                اكسر;
            }
        }
    }
}

ساكن فراغ keyboard_handle_leave(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                  uint32_t serial, بنية wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_کړکۍ_معلومات *کړکۍ = Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface);
    إذا (!کړکۍ) {
        // Not a surface owned by SDL.
        أرجع;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.کلی = 0;

    SDL_کړکۍ *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    طالما (keyboard_focus && SDL_کړکۍ_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->پلار;
    }

    ثابت bool had_focus = keyboard_focus && کړکۍ->sdlwindow == keyboard_focus;
    seat->keyboard.focus = عدم;
    --کړکۍ->keyboard_focus_شمېر;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    إذا (!کړکۍ->keyboard_focus_شمېر && had_focus) {
        SDL_سېټ_Keyboard_Focus(عدم);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشاره_ګر_Grabs(seat->display, کړکۍ);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_ننوت(seat);

#که_تعریف_شوی SDL_USE_IME
    إذا (!seat->متن_ننوت.zwp_متن_ننوت && !کړکۍ->keyboard_focus_شمېر) {
        SDL_IME_سېټ_Focus(false);
    }
#د_که_پای

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    إذا (SDL_GetMouseFocus() == کړکۍ->sdlwindow && !کړکۍ->اشاره_ګر_focus_شمېر && !کړکۍ->فعال_touch_شمېر) {
        SDL_سېټ_Mouse_Focus(عدم);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_معلومات_Device_سېټ_Selection_Offer(seat->معلومات_device, عدم);
}

ساكن bool keyboard_ننوت_get_متن(حرف متن[8], ثابت SDL_WaylandSeat *seat, uint32_t کلی, bool ښکته, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    إذا (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        أرجع false;
    }

    // TODO: Can this happen?
    إذا (WAYLAND_xkb_state_کلی_get_syms(seat->keyboard.xkb.state, کلی + 8, &syms) != 1) {
        أرجع false;
    }
    sym = syms[0];

#که_تعریف_شوی SDL_USE_IME
    إذا (SDL_IME_Process_کلی_Event(sym, کلی + 8, ښکته)) {
        إذا (handled_by_ime) {
            *handled_by_ime = true;
        }
        أرجع true;
    }
#د_که_پای

    إذا (!ښکته) {
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
            sym = XKB_کلی_No_نښه;
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

ساكن فراغ keyboard_handle_کلی(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                uint32_t serial, uint32_t وخت, uint32_t کلی,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = معلومات;
    تعداد wl_keyboard_کلی_state state = state_w;
    حرف متن[8];
    bool has_متن = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, وخت);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    إذا (state == WL_KEYBOARD_کلی_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        إذا (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_کلی_repeats(seat->keyboard.xkb.keymap, کلی + 8)) {
            أرجع;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_کلی_STATE_PRESSED;
    }

    Wayland_Seat_سېټ_Keymap(seat);

    إذا (state == WL_KEYBOARD_کلی_STATE_PRESSED) {
        SDL_کړکۍ *keyboard_focus = SDL_GetKeyboardFocus();
        إذا (keyboard_focus && SDL_متن_ننوت_فعال(keyboard_focus)) {
            has_متن = keyboard_ننوت_get_متن(متن, seat, کلی, true, &handled_by_ime);
        }
    } وإلا {
        إذا (کلی == seat->keyboard.repeat.کلی) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_منزل_NS(وخت - seat->keyboard.repeat.wl_press_وخت_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.کلی = 0;
        }
        keyboard_ننوت_get_متن(متن, seat, کلی, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = عدم;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_کلی(seat, کلی, &syms);
    Wayland_Handle_Modifier_کلیګانې(seat, scancode, state == WL_KEYBOARD_کلی_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    إذا (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_کلی_Sym_منزل_Ucs4(syms[0]);
        إذا (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_ماسک) {
                scancode = SDL_Get_Keymap_بل_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_سېټ_Keymap_ثبت(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_کلی_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, کلی, scancode, state == WL_KEYBOARD_کلی_STATE_PRESSED);

    إذا (state == WL_KEYBOARD_کلی_STATE_PRESSED) {
        إذا (handled_by_ime) {
            has_متن = false;
        }
        إذا (has_متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(متن);
        }
        إذا (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_کلی_repeats(seat->keyboard.xkb.keymap, کلی + 8)) {
            keyboard_repeat_سېټ(&seat->keyboard.repeat, seat->keyboard.sdl_id, کلی, وخت, timestamp_ns, scancode, has_متن ? متن : عدم);
        }
    }
}

ساكن فراغ keyboard_handle_modifiers(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t ډله)
{
    SDL_WaylandSeat *seat = معلومات;
    ثابت uint32_t پخوانی_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = ډله;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    إذا (!seat->keyboard.xkb.state) {
        أرجع;
    }

    WAYLAND_xkb_state_update_ماسک(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, ډله);

    // If a key is repeating, update the text to apply the modifier.
    إذا (seat->keyboard.repeat.کلی) {
        حرف متن[8];

        إذا (keyboard_ننوت_get_متن(متن, seat, seat->keyboard.repeat.کلی, true, عدم)) {
            SDL_strlcpy(seat->keyboard.repeat.متن, متن, SDL_arraysize(seat->keyboard.repeat.متن));
        }
    }

    إذا (ډله != پخوانی_layout) {
        Wayland_Seat_سېټ_Keymap(seat);

        إذا (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

ساكن فراغ keyboard_handle_repeat_info(فراغ *معلومات, بنية wl_keyboard *wl_keyboard,
                                        int32_t شرح, int32_t delay)
{
    SDL_WaylandSeat *seat = معلومات;
    seat->keyboard.repeat.repeat_شرح = شرح;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    إذا (!شرح) {
        seat->keyboard.repeat.کلی = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ساكن ثابت بنية wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_کلی,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ساكن فراغ Wayland_Seat_Destroy_اشاره_ګر(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->اشاره_ګر_2.cursor_state);

    // End any active gestures.
    إذا (seat->اشاره_ګر_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_پای_ټکی, 0, seat->اشاره_ګر_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    إذا (seat->اشاره_ګر_2.focus) {
        seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = seat->اشاره_ګر_2.focus->surface;
        اشاره_ګر_dispatch_leave(seat, false);
        seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = عدم;
    }

    SDL_RemoveMouse(seat->اشاره_ګر_2.sdl_id);

    إذا (seat->اشاره_ګر_2.confined_اشاره_ګر) {
        zwp_confined_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.confined_اشاره_ګر);
    }

    إذا (seat->اشاره_ګر_2.locked_اشاره_ګر) {
        zwp_locked_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.locked_اشاره_ګر);
    }

    إذا (seat->اشاره_ګر_2.relative_اشاره_ګر) {
        zwp_relative_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.relative_اشاره_ګر);
    }

    إذا (seat->اشاره_ګر_2.timestamps) {
        zwp_ننوت_timestamps_v1_destroy(seat->اشاره_ګر_2.timestamps);
    }

    إذا (seat->اشاره_ګر_2.gesture_pinch) {
        zwp_اشاره_ګر_gesture_pinch_v1_destroy(seat->اشاره_ګر_2.gesture_pinch);
    }

    إذا (seat->اشاره_ګر_2.wl_اشاره_ګر) {
        إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) >= WL_اشاره_ګر_RELEASE_SINCE_نسخه) {
            wl_اشاره_ګر_release(seat->اشاره_ګر_2.wl_اشاره_ګر);
        } وإلا {
            wl_اشاره_ګر_destroy(seat->اشاره_ګر_2.wl_اشاره_ګر);
        }
    }

    SDL_zero(seat->اشاره_ګر_2);
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
            SDL_سېټ_Mod_State(SDL_KMOD_NONE);
        }
        لكل (xkb_layout_شاخص_t i = 0; i < seat->keyboard.xkb.عدد_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = عدم;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    إذا (seat->keyboard.کلی_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلی_inhibitor);
    }

    إذا (seat->keyboard.timestamps) {
        zwp_ننوت_timestamps_v1_destroy(seat->keyboard.timestamps);
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
        zwp_ننوت_timestamps_v1_destroy(seat->touch.timestamps);
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

ساكن فراغ seat_handle_capabilities(فراغ *معلومات, بنية wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    حرف name_fmt[256];

    إذا ((capabilities & WL_SEAT_CAPABILITY_اشاره_ګر) && !seat->اشاره_ګر_2.wl_اشاره_ګر) {
        seat->اشاره_ګر_2.wl_اشاره_ګر = wl_seat_get_اشاره_ګر(wl_seat);
        SDL_zero(seat->اشاره_ګر_2.pending_چوکاټ.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_اشاره_ګر_سېټ_user_معلومات(seat->اشاره_ګر_2.wl_اشاره_ګر, seat);
        wl_اشاره_ګر_جمع_کړه_listener(seat->اشاره_ګر_2.wl_اشاره_ګر, &اشاره_ګر_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_اشاره_ګر_Gestures(seat);

        seat->اشاره_ګر_2.sdl_id = SDL_Get_بل_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_اشاره_ګر_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_اشاره_ګر_NAME, seat->اشاره_ګر_2.sdl_id);
        }

        SDL_جمع_کړه_Mouse(seat->اشاره_ګر_2.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_اشاره_ګر) && seat->اشاره_ګر_2.wl_اشاره_ګر) {
        Wayland_Seat_Destroy_اشاره_ګر(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_سېټ_user_معلومات(seat->touch.wl_touch, seat);
        wl_touch_جمع_کړه_listener(seat->touch.wl_touch, &touch_listener, seat);

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_جمع_کړه_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_مستقیم, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_سېټ_user_معلومات(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_جمع_کړه_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_بل_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_جمع_کړه_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_ثبتوونکی_ننوت_Timestamp_Listeners(seat);
}

ساكن فراغ seat_handle_name(فراغ *معلومات, بنية wl_seat *wl_seat, ثابت حرف *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

ساكن ثابت بنية wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

ساكن فراغ معلومات_offer_handle_offer(فراغ *معلومات, بنية wl_معلومات_offer *wl_معلومات_offer,
                                    ثابت حرف *mime_type)
{
    SDL_Wayland_معلومات_Offer *offer = معلومات;
    Wayland_معلومات_Offer_جمع_کړه_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 mime_type);
}

ساكن فراغ معلومات_offer_handle_سرچینه_actions(فراغ *معلومات, بنية wl_معلومات_offer *wl_معلومات_offer,
                                             uint32_t سرچینه_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 سرچینه_actions);
}

ساكن فراغ معلومات_offer_handle_actions(فراغ *معلومات, بنية wl_معلومات_offer *wl_معلومات_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 dnd_action);
}

ساكن ثابت بنية wl_معلومات_offer_listener معلومات_offer_listener = {
    معلومات_offer_handle_offer,
    معلومات_offer_handle_سرچینه_actions, // Version 3
    معلومات_offer_handle_actions,        // Version 3
};

ساكن فراغ primary_selection_offer_handle_offer(فراغ *معلومات, بنية zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = معلومات;
    Wayland_Primary_Selection_Offer_جمع_کړه_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

ساكن ثابت بنية zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

ساكن فراغ معلومات_device_handle_معلومات_offer(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                          بنية wl_معلومات_offer *id)
{
    SDL_Wayland_معلومات_Offer *معلومات_offer = SDL_calloc(1, حجم(*معلومات_offer));
    إذا (معلومات_offer) {
        SDL_Wayland_معلومات_Device *معلومات_device = (SDL_Wayland_معلومات_Device *)معلومات;
        معلومات_offer->offer = id;
        معلومات_offer->معلومات_device = معلومات_device;
        معلومات_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(معلومات_offer->mimes));
        wl_معلومات_offer_سېټ_user_معلومات(id, معلومات_offer);
        wl_معلومات_offer_جمع_کړه_listener(id, &معلومات_offer_listener, معلومات_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
    }
}

ساكن فراغ معلومات_device_handle_enter(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                     uint32_t serial, بنية wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, بنية wl_معلومات_offer *id)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;
    SDL_کړکۍ_معلومات *کړکۍ = surface ? Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface) : عدم;
    معلومات_device->has_mime_file = false;
    معلومات_device->متن_mime_type = عدم;

    معلومات_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    إذا (id) {
        معلومات_device->drag_offer = wl_معلومات_offer_get_user_معلومات(id);
    }

    إذا (معلومات_device->drag_offer && کړکۍ && کړکۍ->مني_drag_and_drop) {
#که_تعریف_شوی SDL_USE_LIBDBUS
        إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, FILE_PORTAL_MIME)) {
            معلومات_device->has_mime_file = true;
            wl_معلومات_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#د_که_پای
        إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, FILE_MIME)) {
            معلومات_device->has_mime_file = true;
            wl_معلومات_offer_accept(id, serial, FILE_MIME);
        }

        إذا (!معلومات_device->has_mime_file) {
            size_t mime_شمېر = 0;
            ثابت حرف *ثابت *متن_mime_types = Wayland_Get_متن_Mime_Types(SDL_GetVideoDevice(), &mime_شمېر);
            لكل (size_t i = 0; i < mime_شمېر; ++i) {
                إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, متن_mime_types[i])) {
                    معلومات_device->متن_mime_type = متن_mime_types[i];
                    wl_معلومات_offer_accept(id, serial, متن_mime_types[i]);
                    اكسر;
                }
            }
        }

        إذا (معلومات_device->has_mime_file || معلومات_device->متن_mime_type) {
            // SDL only supports "copy" style drag and drop
            إذا (wl_معلومات_offer_get_نسخه(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سېټ_ACTIONS_SINCE_نسخه) {
                wl_معلومات_offer_سېټ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_COPY, WL_معلومات_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            معلومات_device->dnd_کړکۍ = کړکۍ->sdlwindow;
            معلومات_device->dnd_surface = surface;
            مزدوج dx = wl_fixed_منزل_double(x);
            مزدوج dy = wl_fixed_منزل_double(y);

            // If over the mask, adjust the offset.
            إذا (surface == کړکۍ->ماسک.surface) {
                dx += (مزدوج)کړکۍ->ماسک.دننه_واټن_x;
                dy += (مزدوج)کړکۍ->ماسک.دننه_واټن_y;
            }

            dx *= کړکۍ->اشاره_ګر_scale.x;
            dy *= کړکۍ->اشاره_ګر_scale.y;

            SDL_SendDropPosition(معلومات_device->dnd_کړکۍ, (عائم)dx, (عائم)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id),
                         wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), SDL_Get_کړکۍ_ID(معلومات_device->dnd_کړکۍ), serial);
        } وإلا {
            // Decline the offer.
            wl_معلومات_offer_accept(id, serial, عدم);
            إذا (wl_معلومات_offer_get_نسخه(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سېټ_ACTIONS_SINCE_نسخه) {
                wl_معلومات_offer_سېټ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id), wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
        }
    } وإلا {
        معلومات_device->dnd_کړکۍ = عدم;
        معلومات_device->dnd_surface = عدم;

        // Decline the offer.
        إذا (id) {
            wl_معلومات_offer_accept(id, serial, عدم);
            إذا (wl_معلومات_offer_get_نسخه(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سېټ_ACTIONS_SINCE_نسخه) {
                wl_معلومات_offer_سېټ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1,
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
    }
}

ساكن فراغ معلومات_device_handle_leave(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer) {
        إذا (معلومات_device->dnd_کړکۍ) {
            SDL_SendDropComplete(معلومات_device->dnd_کړکۍ);
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                         SDL_Get_کړکۍ_ID(معلومات_device->dnd_کړکۍ), معلومات_device->drag_serial);
        } وإلا {
            SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                         معلومات_device->drag_serial);
        }
        Wayland_معلومات_Offer_Destroy(معلومات_device->drag_offer);
        معلومات_device->drag_offer = عدم;
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    معلومات_device->has_mime_file = false;
    معلومات_device->متن_mime_type = عدم;
}

ساكن فراغ معلومات_device_handle_motion(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                      uint32_t وخت, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer && معلومات_device->dnd_کړکۍ && (معلومات_device->has_mime_file || معلومات_device->متن_mime_type)) {
        SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = معلومات_device->dnd_کړکۍ->دننی;
        مزدوج dx = wl_fixed_منزل_double(x);
        مزدوج dy = wl_fixed_منزل_double(y);

        // If over the mask, adjust the offset.
        إذا (معلومات_device->dnd_surface == کړکۍ_معلومات_2->ماسک.surface) {
            dx += (مزدوج)کړکۍ_معلومات_2->ماسک.دننه_واټن_x;
            dy += (مزدوج)کړکۍ_معلومات_2->ماسک.دننه_واټن_y;
        }

        dx *= کړکۍ_معلومات_2->اشاره_ګر_scale.x;
        dy *= کړکۍ_معلومات_2->اشاره_ګر_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(معلومات_device->dnd_کړکۍ, (عائم)dx, (عائم)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y),
                     SDL_Get_کړکۍ_ID(معلومات_device->dnd_کړکۍ), معلومات_device->drag_serial);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), -1);
    }
}

ساكن فراغ drop_cleanup_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    Wayland_Drop_معلومات *drop = (Wayland_Drop_معلومات *)معلومات;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

ساكن ثابت بنية wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

ساكن فراغ drop_dispatch_handler(فراغ *معلومات)
{
    Wayland_Drop_معلومات *drop = (Wayland_Drop_معلومات *)معلومات;
    SDL_Wayland_معلومات_Offer *offer = drop->offer;
    SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;

    إذا (drop->dnd_کړکۍ) {
        size_t اوږدتیا;
        bool drop_handled = false;

#که_تعریف_شوی SDL_USE_LIBDBUS
        إذا (Wayland_معلومات_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, FILE_PORTAL_MIME, &اوږدتیا);
            إذا (بفر_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                إذا (dbus) {
                    صحيح لار_شمېر = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(بفر_2, &لار_شمېر);
                    // If dropped files contain a directory the list is empty
                    إذا (paths && لار_شمېر > 0) {
                        لكل (صحيح i = 0; i < لار_شمېر; i++) {
                            SDL_SendDropFile(drop->dnd_کړکۍ, عدم, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(بفر_2);
            }
        }
#د_که_پای
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        إذا (!drop_handled) {
            إذا (Wayland_معلومات_Offer_Has_MIME(offer, FILE_MIME)) {
                فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, FILE_MIME, &اوږدتیا);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_کړکۍ, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            } وإلا إذا (Wayland_معلومات_Offer_Has_MIME(offer, drop->متن_mime_type)) {
                فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, drop->متن_mime_type, &اوږدتیا);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        SDL_Send_Drop_متن(drop->dnd_کړکۍ, token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            }
        }

        إذا (drop_handled && wl_معلومات_offer_get_نسخه(offer->offer) >= WL_معلومات_OFFER_پای_SINCE_نسخه) {
            wl_معلومات_offer_پای(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_کړکۍ);
    }

    Wayland_معلومات_Offer_Destroy(drop->offer);
    drop->offer = عدم;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(معلومات_device->seat->display->display);
    wl_callback_جمع_کړه_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساكن فراغ معلومات_device_handle_drop(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer && معلومات_device->dnd_کړکۍ &&
        (معلومات_device->has_mime_file || معلومات_device->متن_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                     SDL_Get_کړکۍ_ID(معلومات_device->dnd_کړکۍ), معلومات_device->drag_serial);

        Wayland_دنده_Thread_Context *ctx = معلومات_device->seat->display->دنده_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_معلومات *drop = SDL_calloc(1, حجم(Wayland_Drop_معلومات));
        إذا (drop) {
            drop->offer = معلومات_device->drag_offer;
            drop->dnd_کړکۍ = معلومات_device->dnd_کړکۍ;
            drop->متن_mime_type = معلومات_device->متن_mime_type;

            WAYLAND_wl_list_ورننباسه(&معلومات_device->pending_drops, &drop->link);
            Wayland_دنده_Thread_جمع_کړه_دنده(ctx, drop_dispatch_handler, drop, &drop->id);
        } وإلا {
            Wayland_معلومات_Offer_Destroy(معلومات_device->drag_offer);
        }
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_معلومات_Offer_Destroy(معلومات_device->drag_offer);
    }

    معلومات_device->drag_offer = عدم;
}

ساكن فراغ معلومات_device_handle_selection(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                         بنية wl_معلومات_offer *id)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;
    SDL_Wayland_معلومات_Offer *offer = عدم;

    إذا (id) {
        offer = wl_معلومات_offer_get_user_معلومات(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));

    Wayland_معلومات_Device_سېټ_Selection_Offer(معلومات_device, offer);
}

ساكن ثابت بنية wl_معلومات_device_listener معلومات_device_listener = {
    معلومات_device_handle_معلومات_offer,
    معلومات_device_handle_enter,
    معلومات_device_handle_leave,
    معلومات_device_handle_motion,
    معلومات_device_handle_drop,
    معلومات_device_handle_selection
};

ساكن فراغ primary_selection_device_handle_offer(فراغ *معلومات, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, حجم(*primary_selection_offer));
    إذا (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)معلومات;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_سېټ_user_معلومات(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_جمع_کړه_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن فراغ primary_selection_device_handle_selection(فراغ *معلومات, بنية zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      بنية zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = معلومات;
    SDL_WaylandPrimarySelectionOffer *offer = عدم;

    إذا (id) {
        offer = zwp_primary_selection_offer_v1_get_user_معلومات(id);
    }

    إذا (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن ثابت بنية zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساكن فراغ متن_ننوت_enter(فراغ *معلومات,
                             بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_ننوت_leave(فراغ *معلومات,
                             بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_ننوت_preedit_string(فراغ *معلومات,
                                      بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                                      ثابت حرف *متن,
                                      int32_t cursor_begin,
                                      int32_t cursor_پای_ټکی)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->متن_ننوت.has_preedit = true;
    إذا (متن) {
        صحيح cursor_begin_utf8 = cursor_begin >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_begin) : -1;
        صحيح cursor_پای_ټکی_utf8 = cursor_پای_ټکی >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_پای_ټکی) : -1;
        صحيح cursor_اندازه_utf8;
        إذا (cursor_پای_ټکی_utf8 >= 0) {
            إذا (cursor_begin_utf8 >= 0) {
                cursor_اندازه_utf8 = cursor_پای_ټکی_utf8 - cursor_begin_utf8;
            } وإلا {
                cursor_اندازه_utf8 = cursor_پای_ټکی_utf8;
            }
        } وإلا {
            cursor_اندازه_utf8 = -1;
        }
        SDL_Send_Editing_متن(متن, cursor_begin_utf8, cursor_اندازه_utf8);
    } وإلا {
        SDL_Send_Editing_متن("", 0, 0);
    }
}

ساكن فراغ متن_ننوت_commit_string(فراغ *معلومات,
                                     بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                                     ثابت حرف *متن)
{
    SDL_Send_Keyboard_متن(متن);
}

ساكن فراغ متن_ننوت_delete_surrounding_متن(فراغ *معلومات,
                                               بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                                               uint32_t before_اوږدتیا,
                                               uint32_t after_اوږدتیا)
{
    // FIXME: Do we care about this event?
}

ساكن فراغ متن_ننوت_بشپړ(فراغ *معلومات,
                            بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    إذا (!seat->متن_ننوت.has_preedit) {
        SDL_Send_Editing_متن("", 0, 0);
    }
    seat->متن_ننوت.has_preedit = false;
}

ساكن ثابت بنية zwp_متن_ننوت_v3_listener متن_ننوت_listener = {
    متن_ننوت_enter,
    متن_ننوت_leave,
    متن_ننوت_preedit_string,
    متن_ننوت_commit_string,
    متن_ننوت_delete_surrounding_متن,
    متن_ننوت_بشپړ
};

ساكن فراغ Wayland_معلومات_Device_سېټ_ID(SDL_Wayland_معلومات_Device *معلومات_device)
{
    إذا (!معلومات_device->id_str)
#که_تعریف_شوی SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        إذا (dbus) {
            ثابت حرف *id = dbus->bus_get_unique_name(dbus->session_conn);
            إذا (id) {
                معلومات_device->id_str = SDL_strdup(id);
            }
        }
    }
    إذا (!معلومات_device->id_str)
#د_که_پای
    {
        حرف id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, حجم(id), "%" SDL_PRIu64, pid);
        معلومات_device->id_str = SDL_strdup(id);
    }
}

ساكن فراغ Wayland_Seat_Create_معلومات_Device(SDL_WaylandSeat *seat)
{
    إذا (!seat->display->معلومات_device_manager) {
        أرجع;
    }

    SDL_Wayland_معلومات_Device *معلومات_device = SDL_calloc(1, حجم(*معلومات_device));
    إذا (!معلومات_device) {
        أرجع;
    }

    معلومات_device->معلومات_device = wl_معلومات_device_manager_get_معلومات_device(
        seat->display->معلومات_device_manager, seat->wl_seat);
    معلومات_device->seat = seat;

    إذا (!معلومات_device->معلومات_device) {
        SDL_free(معلومات_device);
        أرجع;
    }

    Wayland_معلومات_Device_سېټ_ID(معلومات_device);
    WAYLAND_wl_list_init(&معلومات_device->pending_drops);
    wl_معلومات_device_سېټ_user_معلومات(معلومات_device->معلومات_device, معلومات_device);
    wl_معلومات_device_جمع_کړه_listener(معلومات_device->معلومات_device, &معلومات_device_listener, معلومات_device);
    seat->معلومات_device = معلومات_device;
}

فراغ Wayland_Display_Init_معلومات_Device_Manager(SDL_Video_معلومات *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_معلومات_Device(seat);
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
        zwp_primary_selection_device_v1_سېټ_user_معلومات(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_جمع_کړه_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_معلومات *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

ساكن فراغ Wayland_Seat_Create_متن_ننوت(SDL_WaylandSeat *seat)
{
    إذا (seat->display->متن_ننوت_manager) {
        seat->متن_ننوت.zwp_متن_ننوت = zwp_متن_ننوت_manager_v3_get_متن_ننوت(seat->display->متن_ننوت_manager, seat->wl_seat);

        إذا (seat->متن_ننوت.zwp_متن_ننوت) {
            zwp_متن_ننوت_v3_سېټ_user_معلومات(seat->متن_ننوت.zwp_متن_ننوت, seat);
            zwp_متن_ننوت_v3_جمع_کړه_listener(seat->متن_ننوت.zwp_متن_ننوت,
                                           &متن_ننوت_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_متن_ننوت_Manager(SDL_Video_معلومات *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_متن_ننوت(seat);
    }
}

// Pen/Tablet support...
ساكن فراغ tablet_tool_handle_type(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    بدل (type) {
        #تعریف_کړه CASE(typ) حالة ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; أرجع
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #تعریف_لغوه CASE
        افتراضي: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

ساكن فراغ tablet_tool_handle_hardware_serial(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

ساكن فراغ tablet_tool_handle_hardware_id_wacom(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->info.wacom_id = id_lo;
}

ساكن فراغ tablet_tool_handle_capability(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    بدل (capability) {
        #تعریف_کړه CASE(wltyp,sdltyp) حالة ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; أرجع
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(واټن_2, SDL_PEN_CAPABILITY_واټن);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #تعریف_لغوه CASE
        افتراضي: اكسر;  // unsupported here.
    }
}

ساكن فراغ tablet_tool_handle_بشپړ(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    إذا (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_کړکۍ *کړکۍ = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        sdltool->instance_id = SDL_جمع_کړه_Pen_Device(0, عدم, کړکۍ, &sdltool->info, sdltool, false);
    }
}

ساكن فراغ tablet_tool_handle_removed(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    إذا (sdltool->instance_id) {
        SDL_کړکۍ *کړکۍ = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        SDL_RemovePenDevice(0, کړکۍ, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساكن فراغ tablet_tool_handle_proximity_دننه(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, بنية zwp_tablet_v2 *tablet, بنية wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    SDL_کړکۍ_معلومات *windowdata = surface ? Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(surface) : عدم;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : عدم;
    sdltool->proximity_serial = serial;
    sdltool->چوکاټ.have_proximity = true;
    sdltool->چوکاټ.دننه_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساكن فراغ tablet_tool_handle_proximity_بهر(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.have_proximity = true;
    sdltool->چوکاټ.دننه_proximity = false;
}

ساكن فراغ tablet_tool_handle_ښکته(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.tool_state = WAYLAND_TABLET_TOOL_STATE_ښکته;
}

ساكن فراغ tablet_tool_handle_پورته(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.tool_state = WAYLAND_TABLET_TOOL_STATE_پورته;
}

ساكن فراغ tablet_tool_handle_motion(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    SDL_کړکۍ_معلومات *windowdata = sdltool->focus;
    إذا (windowdata) {
        sdltool->چوکاټ.x = (عائم)(wl_fixed_منزل_double(sx_w) * windowdata->اشاره_ګر_scale.x);
        sdltool->چوکاټ.y = (عائم)(wl_fixed_منزل_double(sy_w) * windowdata->اشاره_ګر_scale.y);
        sdltool->چوکاټ.have_motion = true;
    }
}

ساكن فراغ tablet_tool_handle_pressure(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_PRESSURE] = ((عائم) pressure) / 65535.0f;
    sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_PRESSURE);
    إذا (pressure) {
        sdltool->چوکاټ.axes[SDL_PEN_AXIS_واټن] = 0.0f;
        sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_واټن);
    }
}

ساكن فراغ tablet_tool_handle_واټن(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t واټن)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_واټن] = ((عائم) واټن) / 65535.0f;
    sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_واټن);
    إذا (واټن) {
        sdltool->چوکاټ.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساكن فراغ tablet_tool_handle_tilt(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_XTILT] = (عائم)(wl_fixed_منزل_double(xtilt));
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_YTILT] = (عائم)(wl_fixed_منزل_double(ytilt));
    sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

ساكن فراغ tablet_tool_handle_button(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
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

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->چوکاټ.buttons)));
    sdltool->چوکاټ.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_ښکته : WAYLAND_TABLET_TOOL_BUTTON_پورته;
}

ساكن فراغ tablet_tool_handle_rotation(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    ثابت عائم rotation = (عائم)(wl_fixed_منزل_double(degrees));
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساكن فراغ tablet_tool_handle_slider(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکاټ.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->چوکاټ.axes_سېټ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساكن فراغ tablet_tool_handle_wheel(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساكن فراغ tablet_tool_handle_چوکاټ(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t وخت)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    إذا (!instance_id) {
        أرجع;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_Adjust_Event_Timestamp_بنسټ(Wayland_EventTimestampMSToNS(وخت));
    SDL_کړکۍ *کړکۍ = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    إذا (sdltool->چوکاټ.have_proximity && sdltool->چوکاټ.دننه_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کړکۍ, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    إذا (sdltool->چوکاټ.have_motion && sdltool->چوکاټ.tool_state) {
        إذا (sdltool->چوکاټ.tool_state == WAYLAND_TABLET_TOOL_STATE_ښکته) {
            SDL_SendPenMotion(timestamp, instance_id, کړکۍ, sdltool->چوکاټ.x, sdltool->چوکاټ.y);
            SDL_SendPenTouch(timestamp, instance_id, کړکۍ, is_eraser, true);
        } وإلا {
            SDL_SendPenTouch(timestamp, instance_id, کړکۍ, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, کړکۍ, sdltool->چوکاټ.x, sdltool->چوکاټ.y);
        }
    } وإلا {
        إذا (sdltool->چوکاټ.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, کړکۍ, is_eraser, sdltool->چوکاټ.tool_state == WAYLAND_TABLET_TOOL_STATE_ښکته);
        }

        إذا (sdltool->چوکاټ.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, کړکۍ, sdltool->چوکاټ.x, sdltool->چوکاټ.y);
        }
    }

    لكل (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_شمېر; i++) {
        إذا (sdltool->چوکاټ.axes_سېټ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, کړکۍ, i, sdltool->چوکاټ.axes[i]);
        }
    }

    لكل (صحيح i = 0; i < SDL_arraysize(sdltool->چوکاټ.buttons); i++) {
        ثابت صحيح state = sdltool->چوکاټ.buttons[i];
        إذا (state) {
            SDL_SendPenButton(timestamp, instance_id, کړکۍ, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_ښکته);
        }
    }

    إذا (sdltool->چوکاټ.have_proximity && !sdltool->چوکاټ.دننه_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, کړکۍ, false, false);
        sdltool->focus = عدم;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->چوکاټ);
}

ساكن ثابت بنية zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_بشپړ,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_دننه,
    tablet_tool_handle_proximity_بهر,
    tablet_tool_handle_ښکته,
    tablet_tool_handle_پورته,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_واټن,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_چوکاټ
};


ساكن فراغ tablet_seat_handle_tablet_added(فراغ *معلومات, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

ساكن فراغ tablet_seat_handle_tool_added(فراغ *معلومات, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, حجم(*sdltool));

    إذا (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.عدد_buttons = -1;

        إذا (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_ورننباسه(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_جمع_کړه_listener(tool, &tablet_tool_listener, sdltool);
    }
}

ساكن فراغ tablet_seat_handle_pad_added(فراغ *معلومات, بنية zwp_tablet_seat_v2 *zwp_tablet_seat_v2, بنية zwp_tablet_pad_v2 *pad)
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
    zwp_tablet_seat_v2_جمع_کړه_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

فراغ Wayland_DisplayInitTabletManager(SDL_Video_معلومات *display)
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

ساكن فراغ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_ښکته)
{
    إذا (!shutting_ښکته) {
        SDL_WaylandPenTool *tool, *لنډمهاله;
        wl_list_for_each_خوندي (tool, لنډمهاله, &seat->tablet.tool_list, link) {
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

فراغ Wayland_DisplayCreateSeat(SDL_Video_معلومات *display, بنية wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, حجم(SDL_WaylandSeat));
    إذا (!seat) {
        أرجع;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_ورننباسه(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_معلومات_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_متن_ننوت(seat);

    wl_seat_سېټ_user_معلومات(seat->wl_seat, seat);
    wl_seat_جمع_کړه_listener(seat->wl_seat, &seat_listener, seat);

    إذا (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

فراغ Wayland_Display_Remove_کړکۍ_References_From_Seats(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        إذا (seat->keyboard.focus == کړکۍ) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, کړکۍ->surface);
        }

        إذا (seat->اشاره_ګر_2.focus == کړکۍ) {
            seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = seat->اشاره_ګر_2.focus->surface;
            اشاره_ګر_dispatch_leave(seat, true);
            seat->اشاره_ګر_2.pending_چوکاټ.leave_surface = عدم;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_ټکی *tp, *لنډمهاله;
        wl_list_for_each_خوندي (tp, لنډمهاله, &seat->touch.points, link) {
            إذا (tp->surface == کړکۍ->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == کړکۍ) {
                tool->focus = عدم;
                Wayland_TabletToolUpdateCursor(tool);
                إذا (tool->instance_id) {
                    SDL_RemovePenDevice(0, کړکۍ->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_معلومات *drop, *drop_لنډمهاله;
        wl_list_for_each_خوندي (drop, drop_لنډمهاله, &seat->معلومات_device->pending_drops, link) {
            إذا (drop->dnd_کړکۍ == کړکۍ->sdlwindow) {
                Wayland_دنده_Thread_Cancel_دنده(display->دنده_thread_context, drop->id);

                إذا (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_معلومات_Offer_Destroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ښکته)
{
    إذا (!seat) {
        أرجع;
    }

    SDL_free(seat->name);

    إذا (seat->معلومات_device) {
        إذا (seat->معلومات_device->selection_offer) {
            Wayland_معلومات_Offer_Destroy(seat->معلومات_device->selection_offer);
        }
        إذا (seat->معلومات_device->selection_سرچینه) {
            Wayland_معلومات_سرچینه_Destroy(seat->معلومات_device->selection_سرچینه);
        }
        إذا (seat->معلومات_device->drag_offer) {
            Wayland_معلومات_Offer_Destroy(seat->معلومات_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_معلومات *drop, *drop_لنډمهاله;
        wl_list_for_each_خوندي (drop, drop_لنډمهاله, &seat->معلومات_device->pending_drops, link) {
            Wayland_دنده_Thread_Cancel_دنده(seat->display->دنده_thread_context, drop->id);

            إذا (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_معلومات_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        إذا (seat->معلومات_device->معلومات_device) {
            إذا (wl_معلومات_device_get_نسخه(seat->معلومات_device->معلومات_device) >= WL_معلومات_DEVICE_RELEASE_SINCE_نسخه) {
                wl_معلومات_device_release(seat->معلومات_device->معلومات_device);
            } وإلا {
                wl_معلومات_device_destroy(seat->معلومات_device->معلومات_device);
            }
        }
        SDL_free(seat->معلومات_device->id_str);
        SDL_free(seat->معلومات_device);
    }

    إذا (seat->primary_selection_device) {
        إذا (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        إذا (seat->primary_selection_device->selection_سرچینه) {
            Wayland_Primary_Selection_سرچینه_Destroy(seat->primary_selection_device->selection_سرچینه);
        }
        إذا (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    إذا (seat->متن_ننوت.zwp_متن_ننوت) {
        zwp_متن_ننوت_v3_destroy(seat->متن_ننوت.zwp_متن_ننوت);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_اشاره_ګر(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_ښکته);

    إذا (wl_seat_get_نسخه(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_نسخه) {
        wl_seat_release(seat->wl_seat);
    } وإلا {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساكن فراغ Wayland_Seat_Update_Relative_اشاره_ګر(SDL_WaylandSeat *seat)
{
    إذا (seat->display->relative_اشاره_ګر_manager) {
        bool relative_focus = false;

        إذا (seat->اشاره_ګر_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            إذا (seat->اشاره_ګر_2.focus->sdlwindow->flags & SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ) {
                إذا (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->اشاره_ګر_2.focus;
                } وإلا {
                    relative_focus = seat->اشاره_ګر_2.focus->keyboard_focus_شمېر != 0;
                }
            } وإلا {
                relative_focus = SDL_GetMouse()->warp_emulation_فعال;
            }
        }

        إذا (relative_focus) {
            إذا (!seat->اشاره_ګر_2.relative_اشاره_ګر) {
                seat->اشاره_ګر_2.relative_اشاره_ګر = zwp_relative_اشاره_ګر_manager_v1_get_relative_اشاره_ګر(seat->display->relative_اشاره_ګر_manager, seat->اشاره_ګر_2.wl_اشاره_ګر);
                zwp_relative_اشاره_ګر_v1_جمع_کړه_listener(seat->اشاره_ګر_2.relative_اشاره_ګر, &relative_اشاره_ګر_listener, seat);
            }
        } وإلا إذا (seat->اشاره_ګر_2.relative_اشاره_ګر) {
            zwp_relative_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.relative_اشاره_ګر);
            seat->اشاره_ګر_2.relative_اشاره_ګر = عدم;
        }
    }
}

ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_معلومات *display = seat->display;

    إذا (display->کلی_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        إذا (seat->keyboard.کلی_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.کلی_inhibitor);
            seat->keyboard.کلی_inhibitor = عدم;
        }

        إذا (seat->keyboard.wl_keyboard) {
            SDL_کړکۍ_معلومات *w = seat->keyboard.focus;
            إذا (w) {
                SDL_کړکۍ *کړکۍ = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                إذا (کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED) {
                    seat->keyboard.کلی_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->کلی_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

فراغ Wayland_Seat_Update_اشاره_ګر_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_معلومات *display = seat->display;
    Wayland_Seat_Update_Relative_اشاره_ګر(seat);

    إذا (display->اشاره_ګر_constraints) {
        إذا (seat->اشاره_ګر_2.locked_اشاره_ګر && !seat->اشاره_ګر_2.relative_اشاره_ګر) {
            zwp_locked_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.locked_اشاره_ګر);
            seat->اشاره_ګر_2.locked_اشاره_ګر = عدم;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
        }

        إذا (seat->اشاره_ګر_2.wl_اشاره_ګر) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            إذا (seat->اشاره_ګر_2.relative_اشاره_ګر) {
                إذا (!seat->اشاره_ګر_2.locked_اشاره_ګر) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    إذا (seat->اشاره_ګر_2.confined_اشاره_ګر) {
                        zwp_confined_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.confined_اشاره_ګر);
                        seat->اشاره_ګر_2.confined_اشاره_ګر = عدم;
                    }

                    seat->اشاره_ګر_2.locked_اشاره_ګر = zwp_اشاره_ګر_constraints_v1_قلف_اشاره_ګر(display->اشاره_ګر_constraints,
                                                                                           seat->اشاره_ګر_2.focus->surface,
                                                                                           seat->اشاره_ګر_2.wl_اشاره_ګر, عدم,
                                                                                           ZWP_اشاره_ګر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشاره_ګر_v1_جمع_کړه_listener(seat->اشاره_ګر_2.locked_اشاره_ګر, &locked_اشاره_ګر_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                أرجع;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            إذا (seat->اشاره_ګر_2.confined_اشاره_ګر) {
                zwp_confined_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.confined_اشاره_ګر);
                seat->اشاره_ګر_2.confined_اشاره_ګر = عدم;
            }

            SDL_کړکۍ_معلومات *w = seat->اشاره_ګر_2.focus;
            إذا (!w) {
                أرجع;
            }

            SDL_کړکۍ *کړکۍ = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            إذا (!(کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) ||
                (!(کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED) && SDL_Rect_تشه(&کړکۍ->mouse_rect))) {
                أرجع;
            }

            بنية wl_region *confine_rect = عدم;
            إذا (!SDL_Rect_تشه(&کړکۍ->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(کړکۍ, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_جمع_کړه(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                إذا (!SDL_ټکی_دننه_Rect(&seat->اشاره_ګر_2.وروستی_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحيح closest_x = seat->اشاره_ګر_2.وروستی_motion.x;
                    صحيح closest_y = seat->اشاره_ګر_2.وروستی_motion.y;

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

            إذا (confine_rect || (کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED)) {
                إذا (کړکۍ->mouse_rect.w != 1 && کړکۍ->mouse_rect.h != 1) {
                    seat->اشاره_ګر_2.confined_اشاره_ګر =
                        zwp_اشاره_ګر_constraints_v1_confine_اشاره_ګر(display->اشاره_ګر_constraints,
                                                                   w->surface,
                                                                   seat->اشاره_ګر_2.wl_اشاره_ګر,
                                                                   confine_rect,
                                                                   ZWP_اشاره_ګر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_اشاره_ګر_v1_جمع_کړه_listener(seat->اشاره_ګر_2.confined_اشاره_ګر,
                                                         &confined_اشاره_ګر_listener,
                                                         seat);
                } وإلا {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->اشاره_ګر_2.locked_اشاره_ګر =
                        zwp_اشاره_ګر_constraints_v1_قلف_اشاره_ګر(display->اشاره_ګر_constraints,
                                                                w->surface,
                                                                seat->اشاره_ګر_2.wl_اشاره_ګر,
                                                                عدم,
                                                                ZWP_اشاره_ګر_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشاره_ګر_v1_جمع_کړه_listener(seat->اشاره_ګر_2.locked_اشاره_ګر,
                                                       &locked_اشاره_ګر_listener,
                                                       seat);
                }
                إذا (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

فراغ Wayland_Display_Update_اشاره_ګر_Grabs(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!کړکۍ || seat->اشاره_ګر_2.focus == کړکۍ) {
            Wayland_Seat_Update_اشاره_ګر_Grab(seat);
        }
    }
}

فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!کړکۍ || seat->keyboard.focus == کړکۍ) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    إذا (serial > seat->وروستی_implicit_grab_serial) {
        seat->وروستی_implicit_grab_serial = serial;
        seat->display->وروستی_implicit_grab_seat = seat;
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND
