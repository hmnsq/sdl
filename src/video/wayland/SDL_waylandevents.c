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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

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

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جيڪڏهن_پورو

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
#ضمن <linux/input.h>
#وإلا
#وصف_ڪريو BTN_کاٻو    (0x110)
#وصف_ڪريو BTN_ساڄو   (0x111)
#وصف_ڪريو BTN_وچ  (0x112)
#وصف_ڪريو BTN_SIDE    (0x113)
#وصف_ڪريو BTN_EXTRA   (0x114)
#وصف_ڪريو BTN_STYLUS  (0x14b)
#وصف_ڪريو BTN_STYLUS2 (0x14c)
#وصف_ڪريو BTN_STYLUS3 (0x149)
#جيڪڏهن_پورو
#ضمن "../../events/SDL_keysym_to_scancode_c.h"
#ضمن "../../events/imKStoUCS.h"
#ضمن <errno.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>
#ضمن <xkbcommon/xkbcommon-compose.h>
#ضمن <xkbcommon/xkbcommon.h>

// Weston uses a ratio of 10 units per scroll tick
#وصف_ڪريو WAYLAND_WHEEL_AXIS_UNIT 10

#جيڪڏهن_وصف_نه_ٿيل XKB_MOD_NAME_MOD3
#وصف_ڪريو XKB_MOD_NAME_MOD3 "Mod3"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل XKB_MOD_NAME_MOD5
#وصف_ڪريو XKB_MOD_NAME_MOD5 "Mod5"
#جيڪڏهن_پورو

// Keyboard and mouse names to match XWayland
#وصف_ڪريو WAYLAND_DEFAULT_KEYBOARD_NAME "Virtual core keyboard"
#وصف_ڪريو WAYLAND_DEFAULT_اشارو_NAME "Virtual core pointer"
#وصف_ڪريو WAYLAND_DEFAULT_TOUCH_NAME "Virtual core touch"

// Focus clickthrough timeout
#وصف_ڪريو WAYLAND_FOCUS_CLICK_TIMEOUT_NS SDL_MS_منزل_NS(10)

// Timer rollover detection thresholds
#وصف_ڪريو WAYLAND_TIMER_ROLLOVER_INTERVAL_هيٺيون  (SDL_MAX_UINT32 / 16U)
#وصف_ڪريو WAYLAND_TIMER_ROLLOVER_INTERVAL_مٿاهون (WAYLAND_TIMER_ROLLOVER_INTERVAL_هيٺيون * 15U)

// Scoped function declarations
ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

تعريفنوع بنية
{
    Uint32 ڪنجي;
    SDL_Scancode scancode;
} Wayland_Reserved_ڪنجي;

تعريفنوع بنية
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    بنية wl_surface *surface;

    بنية wl_list link;
} SDL_Wayland_Touch_نقطو;

ساكن فراغ Wayland_Seat_جوڙيو_Touch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface *surface)
{
    SDL_Wayland_Touch_نقطو *tp = SDL_malloc(حجم(SDL_Wayland_Touch_نقطو));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_وجهو(&seat->touch.points, &tp->link);
}

ساكن فراغ Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_Wayland_Touch_نقطو *tp)
{
    إذا (tp->surface) {
        SDL_دري_معلومات *دري_معلومات_2 = Wayland_Get_دري_معلومات_For_Owned_Surface(tp->surface);

        إذا (دري_معلومات_2) {
            ثابت عائم x = (عائم)(wl_fixed_منزل_double(tp->fx) / دري_معلومات_2->current.logical_ويڪر);
            ثابت عائم y = (عائم)(wl_fixed_منزل_double(tp->fy) / دري_معلومات_2->current.logical_اوچائي);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), دري_معلومات_2->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --دري_معلومات_2->سرگرم_touch_ڳڻپ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == دري_معلومات_2->sdlwindow && !دري_معلومات_2->keyboard_focus_ڳڻپ &&
                !دري_معلومات_2->اشارو_focus_ڳڻپ && !دري_معلومات_2->سرگرم_touch_ڳڻپ) {
                SDL_سيٽ_Mouse_Focus(عدم);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

ساكن فراغ Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, بنية wl_surface **surface)
{
    SDL_Wayland_Touch_نقطو *tp;

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
    SDL_Wayland_Touch_نقطو *tp;

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

ساكن فراغ Wayland_GetScaledMouseRect(SDL_دري *دري, SDL_Rect *scaled_rect)
{
    SDL_دري_معلومات *دري_معلومات_2 = دري->اندروني;

    scaled_rect->x = (صحيح)SDL_floor(دري->mouse_rect.x / دري_معلومات_2->اشارو_scale.x);
    scaled_rect->y = (صحيح)SDL_floor(دري->mouse_rect.y / دري_معلومات_2->اشارو_scale.y);
    scaled_rect->w = (صحيح)SDL_ceil(دري->mouse_rect.w / دري_معلومات_2->اشارو_scale.x);
    scaled_rect->h = (صحيح)SDL_ceil(دري->mouse_rect.h / دري_معلومات_2->اشارو_scale.y);
}

ساكن Uint64 Wayland_Adjust_Event_Timestamp_بنياد(Uint64 nsTimestamp)
{
    ساكن Uint64 timestamp_وٿي = 0;
    ثابت Uint64 now = SDL_GetTicksNS();

    إذا (!timestamp_وٿي) {
        timestamp_وٿي = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_وٿي;

    إذا (nsTimestamp > now) {
        timestamp_وٿي -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    أرجع nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
ساكن Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    ساكن Uint64 timestamp_وٿي = 0;
    ساكن Uint32 آخري = 0;
    Uint64 timestamp = SDL_MS_منزل_NS(wl_timestamp_ms) + timestamp_وٿي;

    إذا (wl_timestamp_ms >= آخري) {
        إذا (timestamp_وٿي && آخري < WAYLAND_TIMER_ROLLOVER_INTERVAL_هيٺيون && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_مٿاهون) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
        } وإلا {
            آخري = wl_timestamp_ms;
        }
    } وإلا {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        إذا (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_هيٺيون && آخري > WAYLAND_TIMER_ROLLOVER_INTERVAL_مٿاهون) {
            timestamp_وٿي += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_منزل_NS(SDL_UINT64_C(0x100000000));
            آخري = wl_timestamp_ms;
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
    أرجع Wayland_Adjust_Event_Timestamp_بنياد(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن Uint64 Wayland_Get_اشارو_Timestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_بنياد(seat->اشارو_2.timestamps ? seat->اشارو_2.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    ثابت Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    أرجع Wayland_Adjust_Event_Timestamp_بنياد(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

ساكن فراغ داخلا_timestamp_listener(فراغ *معلومات, بنية zwp_داخلا_timestamps_v1 *zwp_داخلا_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)معلومات) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_في_ٻيو) + tv_nsec;
}

ساكن ثابت بنية zwp_داخلا_timestamps_v1_listener timestamp_listener = {
    داخلا_timestamp_listener
};

ساكن فراغ Wayland_Seat_رجسٽر_داخلا_Timestamp_Listeners(SDL_WaylandSeat *seat)
{
    إذا (seat->display->داخلا_timestamps_manager) {
        إذا (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_داخلا_timestamps_manager_v1_get_keyboard_timestamps(seat->display->داخلا_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_داخلا_timestamps_v1_جوڙيو_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        إذا (seat->اشارو_2.wl_اشارو && !seat->اشارو_2.timestamps) {
            seat->اشارو_2.timestamps = zwp_داخلا_timestamps_manager_v1_get_اشارو_timestamps(seat->display->داخلا_timestamps_manager, seat->اشارو_2.wl_اشارو);
            zwp_داخلا_timestamps_v1_جوڙيو_listener(seat->اشارو_2.timestamps, &timestamp_listener, &seat->اشارو_2.highres_timestamp_ns);
        }

        إذا (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_داخلا_timestamps_manager_v1_get_touch_timestamps(seat->display->داخلا_timestamps_manager, seat->touch.wl_touch);
            zwp_داخلا_timestamps_v1_جوڙيو_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

فراغ Wayland_Display_Init_داخلا_Timestamp_Manager(SDL_Video_معلومات *display)
{
    إذا (display->داخلا_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_Seat_رجسٽر_داخلا_Timestamp_Listeners(seat);
        }
    }
}

ساكن فراغ handle_pinch_begin(فراغ *معلومات, بنية zwp_اشارو_gesture_pinch_v1 *zwp_اشارو_gesture_pinch_v1, uint32_t serial, uint32_t وقت, بنية wl_surface *surface, uint32_t fingers)
{
    إذا (!surface) {
        أرجع;
    }

    SDL_دري_معلومات *wind = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);
    إذا (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
        seat->اشارو_2.gesture_focus = wind;

        ثابت Uint64 timestamp = Wayland_Get_اشارو_Timestamp(seat, وقت);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_update(فراغ *معلومات, بنية zwp_اشارو_gesture_pinch_v1 *zwp_اشارو_gesture_pinch_v1, uint32_t وقت,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (seat->اشارو_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارو_Timestamp(seat, وقت);
        ثابت عائم s = (عائم)wl_fixed_منزل_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->اشارو_2.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

ساكن فراغ handle_pinch_پڇاڙي(فراغ *معلومات, بنية zwp_اشارو_gesture_pinch_v1 *zwp_اشارو_gesture_pinch_v1, uint32_t serial, uint32_t وقت, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    إذا (seat->اشارو_2.gesture_focus) {
        ثابت Uint64 timestamp = Wayland_Get_اشارو_Timestamp(seat, وقت);
        SDL_SendPinch(SDL_EVENT_PINCH_پڇاڙي, timestamp, seat->اشارو_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->اشارو_2.gesture_focus = عدم;
    }
}

ساكن ثابت بنية zwp_اشارو_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_پڇاڙي
};

ساكن فراغ Wayland_Seat_Create_اشارو_Gestures(SDL_WaylandSeat *seat)
{
    إذا (seat->display->zwp_اشارو_gestures) {
        إذا (seat->اشارو_2.wl_اشارو && !seat->اشارو_2.gesture_pinch) {
            seat->اشارو_2.gesture_pinch = zwp_اشارو_gestures_v1_get_pinch_gesture(seat->display->zwp_اشارو_gestures, seat->اشارو_2.wl_اشارو);
            zwp_اشارو_gesture_pinch_v1_سيٽ_user_معلومات(seat->اشارو_2.gesture_pinch, seat);
            zwp_اشارو_gesture_pinch_v1_جوڙيو_listener(seat->اشارو_2.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_اشارو_Gesture_Manager(SDL_Video_معلومات *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_Seat_Create_اشارو_Gestures(seat);
    }
}

ساكن فراغ Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    إذا (seat->display->cursor_shape_manager) {
        إذا (seat->اشارو_2.wl_اشارو && !seat->اشارو_2.cursor_state.cursor_shape) {
            seat->اشارو_2.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_اشارو(seat->display->cursor_shape_manager, seat->اشارو_2.wl_اشارو);
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

ساكن فراغ Wayland_Seat_سيٽ_Keymap(SDL_WaylandSeat *seat)
{
    ثابت bool send_event = !seat->display->initializing;

    إذا (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.انگ_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_سيٽ_Keymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_سيٽ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
ساكن فراغ keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    طالما (elapsed >= repeat_info->ايندڙ_repeat_ns) {
        إذا (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت Uint64 timestamp = repeat_info->بنياد_وقت_ns + repeat_info->ايندڙ_repeat_ns;
            SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(Wayland_Adjust_Event_Timestamp_بنياد(timestamp), repeat_info->keyboard_id, repeat_info->ڪنجي, repeat_info->scancode, true);
        }
        إذا (repeat_info->متن[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(repeat_info->متن);
        }
        repeat_info->ايندڙ_repeat_ns += SDL_NS_في_ٻيو / (Uint64)repeat_info->repeat_شرح;
    }
}

ساكن فراغ keyboard_repeat_سيٽ(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t ڪنجي, Uint32 wl_press_وقت_ms,
                                Uint64 بنياد_وقت_ns, uint32_t scancode, ثابت حرف *متن)
{
    إذا (!repeat_info->repeat_شرح) {
        أرجع;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->ڪنجي = ڪنجي;
    repeat_info->wl_press_وقت_ms = wl_press_وقت_ms;
    repeat_info->بنياد_وقت_ns = بنياد_وقت_ns;
    repeat_info->sdl_press_وقت_ns = SDL_GetTicksNS();
    repeat_info->ايندڙ_repeat_ns = SDL_MS_منزل_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    إذا (متن) {
        SDL_strlcpy(repeat_info->متن, متن, SDL_arraysize(repeat_info->متن));
    } وإلا {
        repeat_info->متن[0] = '\0';
    }
}

ساكن فراغ sync_پورو_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener sync_listener = {
    sync_پورو_handler
};

فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *d = _this->اندروني;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    بنية wl_callback *cb = wl_display_sync(d->display);
    wl_callback_جوڙيو_listener(cb, &sync_listener, عدم);
    WAYLAND_wl_display_flush(d->display);
}

صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_Video_معلومات *d = _this->اندروني;
    SDL_WaylandSeat *seat;
    Uint64 شروعات = SDL_GetTicksNS();
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret;
    bool poll_alarm_سيٽ = false;

#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    SDL_دري *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_داخلا_manager && keyboard_focus && SDL_متن_داخلا_سرگرم(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        إذا (timeoutNS < 0 || SDL_MS_منزل_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_منزل_NS(200);
            poll_alarm_سيٽ = true;
        }
    }
#جيڪڏهن_پورو

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->keyboard.repeat.ڪنجي) {
            ثابت Uint64 elapsed = شروعات - seat->keyboard.repeat.sdl_press_وقت_ns;
            ثابت Uint64 ايندڙ_repeat_wait_وقت = (seat->keyboard.repeat.ايندڙ_repeat_ns - elapsed) + 1;
            إذا (timeoutNS < 0 || ايندڙ_repeat_wait_وقت <= timeoutNS) {
                timeoutNS = ايندڙ_repeat_wait_وقت;
                poll_alarm_سيٽ = true;
            }
        }
    }

    إذا (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        إذا (timeoutNS > 0) {
            ثابت Uint64 now = SDL_GetTicksNS();
            ثابت Uint64 elapsed = now - شروعات;
            شروعات = now;
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
            ثابت Uint64 elapsed = now - شروعات;
            شروعات = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        إذا (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            إذا (ret == 0) {
                أرجع poll_alarm_سيٽ ? 1 : 0;
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
    SDL_Video_معلومات *d = _this->اندروني;
    SDL_WaylandSeat *seat;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(d->display);
    صحيح ret = 0;

#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    SDL_دري *keyboard_focus = SDL_GetKeyboardFocus();
    إذا (!d->متن_داخلا_manager && keyboard_focus && SDL_متن_داخلا_سرگرم(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#جيڪڏهن_پورو

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
            إذا (seat->keyboard.repeat.ڪنجي) {
                Wayland_Seat_سيٽ_Keymap(seat);

                ثابت Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_وقت_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    إذا (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

ساكن فراغ اشارو_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_دري_معلومات *دري_معلومات_2 = seat->اشارو_2.focus;
    SDL_دري *دري = دري_معلومات_2 ? دري_معلومات_2->sdlwindow : عدم;

    إذا (دري_معلومات_2) {
        مزدوج sx = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.absolute.sx);
        مزدوج sy = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.absolute.sy);

        إذا (seat->اشارو_2.focus_surface == دري_معلومات_2->نقاب.surface) {
            sx += (مزدوج)دري_معلومات_2->نقاب.وٿي_x;
            sy += (مزدوج)دري_معلومات_2->نقاب.وٿي_y;
        }

        sx *= دري_معلومات_2->اشارو_scale.x;
        sy *= دري_معلومات_2->اشارو_scale.y;
        إذا (!warp) {
            SDL_SendMouseMotion(seat->اشارو_2.pending_چوکٺو.timestamp_ns, دري_معلومات_2->sdlwindow, seat->اشارو_2.sdl_id, false, (عائم)sx, (عائم)sy);
        } وإلا {
            SDL_SendMouseWarp(seat->اشارو_2.pending_چوکٺو.timestamp_ns, دري_معلومات_2->sdlwindow, seat->اشارو_2.sdl_id, (عائم)sx, (عائم)sy);
        }

        seat->اشارو_2.آخري_motion.x = (صحيح)SDL_floor(sx);
        seat->اشارو_2.آخري_motion.y = (صحيح)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        إذا (!SDL_Rect_خالي_جايون(&دري->mouse_rect) && !seat->اشارو_2.is_confined) {
            Wayland_Seat_Update_اشارو_Grab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        إذا (!(دري->flags & SDL_دري_MOUSE_CAPTURE) && دري->ڪاميابي_test) {
            SDL_ڪاميابي_Test_نتيجو rc = دري->ڪاميابي_test(دري, &seat->اشارو_2.آخري_motion, دري->ڪاميابي_test_معلومات);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            بدل (rc) {
            حالة SDL_HITTEST_RESIZE_TOPLEFT:
                إذا ((دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي) &&
                    (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي) {
                    rc = SDL_HITTEST_RESIZE_کاٻو;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو) {
                    rc = SDL_HITTEST_RESIZE_چوٽي;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_چوٽي:
                إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_TOPRIGHT:
                إذا ((دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي) &&
                    (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي) {
                    rc = SDL_HITTEST_RESIZE_ساڄو;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو) {
                    rc = SDL_HITTEST_RESIZE_چوٽي;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_ساڄو:
                إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                إذا ((دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_ساڄو;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOM:
                إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
                إذا ((دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو)) {
                    rc = SDL_HITTEST_عام;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_کاٻو;
                } وإلا إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                اكسر;
            حالة SDL_HITTEST_RESIZE_کاٻو:
                إذا (دري_معلومات_2->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو) {
                    rc = SDL_HITTEST_عام;
                }
                اكسر;
            افتراضي:
                اكسر;
            }

            إذا (rc != دري_معلومات_2->ڪاميابي_test_نتيجو) {
                دري_معلومات_2->ڪاميابي_test_نتيجو = rc;
                Wayland_Seat_Update_اشارو_Cursor(seat);
            }
        }
    }
}

ساكن فراغ اشارو_handle_motion(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                  uint32_t وقت, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    ثابت Uint64 timestamp = Wayland_Get_اشارو_Timestamp(seat, وقت);

    seat->اشارو_2.pending_چوکٺو.absolute.sx = sx;
    seat->اشارو_2.pending_چوکٺو.absolute.sy = sy;

    إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) >= WL_اشارو_چوکٺو_SINCE_نسخو) {
        seat->اشارو_2.pending_چوکٺو.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        إذا (!seat->اشارو_2.pending_چوکٺو.have_relative || seat->اشارو_2.timestamps) {
            seat->اشارو_2.pending_چوکٺو.timestamp_ns = timestamp;
        }
    } وإلا {
        seat->اشارو_2.pending_چوکٺو.timestamp_ns = timestamp;
        اشارو_dispatch_absolute_motion(seat, false);
    }
}

ساكن فراغ اشارو_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_دري_معلومات *دري = Wayland_Get_دري_معلومات_For_Owned_Surface(seat->اشارو_2.pending_چوکٺو.enter_surface);
    إذا (!دري) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        أرجع;
    }

    إذا (دري->surface != seat->اشارو_2.pending_چوکٺو.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_Seat_سيٽ_Default_Cursor(seat);
        أرجع;
    }

    seat->اشارو_2.focus = دري;
    seat->اشارو_2.focus_surface = seat->اشارو_2.pending_چوکٺو.enter_surface;
    ++دري->اشارو_focus_ڳڻپ;
    SDL_سيٽ_Mouse_Focus(دري->sdlwindow);

    // Send the initial position.
    اشارو_dispatch_absolute_motion(seat, false);

    // Update the pointer grab state.
    Wayland_Seat_Update_اشارو_Grab(seat);

    /* If the cursor was changed while our window didn't have pointer
     * focus, we might need to trigger another call to
     * wl_pointer_set_cursor() for the new cursor to be displayed.
     *
     * This will also update the cursor if a second pointer entered a
     * window that already has focus, as the focus change sequence
     * won't be run.
     */
    Wayland_Seat_Update_اشارو_Cursor(seat);
}

ساكن فراغ اشارو_handle_enter(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                 uint32_t serial, بنية wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.pending_چوکٺو.enter_surface = surface;
    seat->اشارو_2.enter_serial = serial;

    /* In the case of e.g. a pointer confine warp, we may receive an enter
     * event with no following motion event, but with the new coordinates
     * as part of the enter event.
     */
    seat->اشارو_2.pending_چوکٺو.absolute.sx = sx_w;
    seat->اشارو_2.pending_چوکٺو.absolute.sy = sy_w;

    إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) < WL_اشارو_چوکٺو_SINCE_نسخو) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->اشارو_2.pending_چوکٺو.timestamp_ns = 0;
        اشارو_dispatch_enter(seat);
    }
}

ساكن فراغ اشارو_dispatch_leave(SDL_WaylandSeat *seat, bool update_اشارو)
{
    SDL_دري_معلومات *دري = Wayland_Get_دري_معلومات_For_Owned_Surface(seat->اشارو_2.pending_چوکٺو.leave_surface);

    إذا (دري) {
        إذا (seat->اشارو_2.focus) {
            إذا (seat->اشارو_2.focus->surface == seat->اشارو_2.pending_چوکٺو.leave_surface) {
                // Clear the capture flag and raise all buttons
                دري->sdlwindow->flags &= ~SDL_دري_MOUSE_CAPTURE;

                seat->اشارو_2.focus = عدم;
                seat->اشارو_2.focus_surface = عدم;
                لكل (Uint8 i = 1; seat->اشارو_2.buttons_pressed; ++i) {
                    إذا (seat->اشارو_2.buttons_pressed & SDL_BUTTON_نقاب(i)) {
                        SDL_SendMouseButton(0, دري->sdlwindow, seat->اشارو_2.sdl_id, i, false);
                        seat->اشارو_2.buttons_pressed &= ~SDL_BUTTON_نقاب(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_دري *mouse_focus = SDL_GetMouseFocus();
                ثابت bool had_focus = mouse_focus && دري->sdlwindow == mouse_focus;
                إذا (!--دري->اشارو_focus_ڳڻپ && had_focus && !دري->سرگرم_touch_ڳڻپ) {
                    SDL_سيٽ_Mouse_Focus(عدم);
                }

                إذا (update_اشارو) {
                    Wayland_Seat_Update_اشارو_Grab(seat);
                    Wayland_Seat_Update_اشارو_Cursor(seat);
                }
            }
        } وإلا إذا (update_اشارو) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

ساكن فراغ اشارو_handle_leave(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                 uint32_t serial, بنية wl_surface *surface)
{
    إذا (!surface) {
        // Leave event for a destroyed surface.
        أرجع;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.pending_چوکٺو.leave_surface = surface;
    إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) < WL_اشارو_چوکٺو_SINCE_نسخو) {
        اشارو_dispatch_leave(seat, true);
    }
}

ساكن bool Wayland_Process_ڪاميابي_Test(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    إذا (seat->اشارو_2.locked_اشارو) {
        أرجع false;
    }

    SDL_دري_معلومات *دري_معلومات_2 = seat->اشارو_2.focus;
    SDL_دري *دري = دري_معلومات_2->sdlwindow;

    إذا (دري->ڪاميابي_test) {
        ساكن ثابت uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_ڪنارو_چوٽي_کاٻو, XDG_TOPLEVEL_RESIZE_ڪنارو_چوٽي,
            XDG_TOPLEVEL_RESIZE_ڪنارو_چوٽي_ساڄو, XDG_TOPLEVEL_RESIZE_ڪنارو_ساڄو,
            XDG_TOPLEVEL_RESIZE_ڪنارو_BOTTOM_ساڄو, XDG_TOPLEVEL_RESIZE_ڪنارو_BOTTOM,
            XDG_TOPLEVEL_RESIZE_ڪنارو_BOTTOM_کاٻو, XDG_TOPLEVEL_RESIZE_ڪنارو_کاٻو
        };

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
        ساكن ثابت uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_ڪنارو_چوٽي_کاٻو, LIBDECOR_RESIZE_ڪنارو_چوٽي,
            LIBDECOR_RESIZE_ڪنارو_چوٽي_ساڄو, LIBDECOR_RESIZE_ڪنارو_ساڄو,
            LIBDECOR_RESIZE_ڪنارو_BOTTOM_ساڄو, LIBDECOR_RESIZE_ڪنارو_BOTTOM,
            LIBDECOR_RESIZE_ڪنارو_BOTTOM_کاٻو, LIBDECOR_RESIZE_ڪنارو_کاٻو
        };
#جيڪڏهن_پورو

        بدل (دري_معلومات_2->ڪاميابي_test_نتيجو) {
        حالة SDL_HITTEST_DRAGGABLE:
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
            إذا (دري_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (دري_معلومات_2->shell_surface.libdecor.چوکٺو) {
                    libdecor_چوکٺو_move(دري_معلومات_2->shell_surface.libdecor.چوکٺو,
                                        seat->wl_seat,
                                        serial);
                }
            } وإلا
#جيڪڏهن_پورو
                إذا (دري_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (دري_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(دري_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            أرجع true;

        حالة SDL_HITTEST_RESIZE_TOPLEFT:
        حالة SDL_HITTEST_RESIZE_چوٽي:
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
        حالة SDL_HITTEST_RESIZE_ساڄو:
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        حالة SDL_HITTEST_RESIZE_BOTTOM:
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
        حالة SDL_HITTEST_RESIZE_کاٻو:
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
            إذا (دري_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                إذا (دري_معلومات_2->shell_surface.libdecor.چوکٺو) {
                    libdecor_چوکٺو_resize(دري_معلومات_2->shell_surface.libdecor.چوکٺو,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[دري_معلومات_2->ڪاميابي_test_نتيجو - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } وإلا
#جيڪڏهن_پورو
                إذا (دري_معلومات_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                إذا (دري_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(دري_معلومات_2->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[دري_معلومات_2->ڪاميابي_test_نتيجو - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            أرجع true;

        افتراضي:
            أرجع false;
        }
    }

    أرجع false;
}

ساكن فراغ اشارو_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool هيٺ_ڏانهن)
{
    SDL_دري_معلومات *دري = seat->اشارو_2.focus;

    إذا (دري) {
        bool ignore_click = false;

        إذا (هيٺ_ڏانهن) {
            seat->اشارو_2.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);

            إذا (sdl_button == SDL_BUTTON_کاٻو && Wayland_Process_ڪاميابي_Test(seat, seat->آخري_implicit_grab_serial)) {
                أرجع; // don't pass this event on to app.
            }
        } وإلا {
            seat->اشارو_2.buttons_pressed &= ~SDL_BUTTON_نقاب(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        إذا (دري->آخري_focus_event_وقت_ns) {
            إذا (هيٺ_ڏانهن && (SDL_GetTicksNS() - دري->آخري_focus_event_وقت_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
                ignore_click = !SDL_GetHintBoolean(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, false);
            }

            دري->آخري_focus_event_وقت_ns = 0;
        }

        /* Wayland won't let you "capture" the mouse, but it will automatically track
         * the mouse outside the window if you drag outside of it, until you let go
         * of all buttons (even if you add or remove presses outside the window, as
         * long as any button is still down, the capture remains).
         *
         * The mouse is not captured in relative mode.
         */
        إذا (!seat->اشارو_2.relative_اشارو) {
            إذا (seat->اشارو_2.buttons_pressed != 0) {
                دري->sdlwindow->flags |= SDL_دري_MOUSE_CAPTURE;
            } وإلا {
                دري->sdlwindow->flags &= ~SDL_دري_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                إذا (seat->اشارو_2.focus_surface != دري->surface) {
                    seat->اشارو_2.pending_چوکٺو.leave_surface = دري->surface;
                }
            }
        }

        إذا (!ignore_click) {
            SDL_SendMouseButton(seat->اشارو_2.pending_چوکٺو.timestamp_ns, دري->sdlwindow, seat->اشارو_2.sdl_id, sdl_button, هيٺ_ڏانهن);
        }
    }
}

ساكن فراغ اشارو_handle_button(فراغ *معلومات, بنية wl_اشارو *اشارو_2, uint32_t serial,
                                  uint32_t وقت, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = معلومات;
    Uint8 sdl_button;

    بدل (button) {
    حالة BTN_کاٻو:
        sdl_button = SDL_BUTTON_کاٻو;
        اكسر;
    حالة BTN_وچ:
        sdl_button = SDL_BUTTON_وچ;
        اكسر;
    حالة BTN_ساڄو:
        sdl_button = SDL_BUTTON_ساڄو;
        اكسر;
    افتراضي:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        اكسر;
    }

    إذا (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->اشارو_2.pending_چوکٺو.timestamp_ns = Wayland_Get_اشارو_Timestamp(seat, وقت);

    إذا (wl_seat_get_نسخو(seat->wl_seat) >= WL_اشارو_چوکٺو_SINCE_نسخو) {
        إذا (state_w) {
            seat->اشارو_2.pending_چوکٺو.buttons_pressed |= SDL_BUTTON_نقاب(sdl_button);
        } وإلا {
            seat->اشارو_2.pending_چوکٺو.buttons_released |= SDL_BUTTON_نقاب(sdl_button);
        }
    } وإلا {
        اشارو_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

ساكن فراغ اشارو_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t قدر)
{
    SDL_دري_معلومات *دري = seat->اشارو_2.focus;
    ثابت تعداد wl_اشارو_axis a = axis;

    إذا (seat->اشارو_2.focus) {
        عائم x, y;

        بدل (a) {
        حالة WL_اشارو_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (عائم)wl_fixed_منزل_double(قدر);
            اكسر;
        حالة WL_اشارو_AXIS_HORIZONTAL_SCROLL:
            x = (عائم)wl_fixed_منزل_double(قدر);
            y = 0;
            اكسر;
        افتراضي:
            أرجع;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, دري->sdlwindow, seat->اشارو_2.sdl_id, x, y, SDL_MOUSEWHEEL_عام);
    }
}

ساكن فراغ اشارو_handle_axis_common(SDL_WaylandSeat *seat, تعداد SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t قدر)
{
    ثابت تعداد wl_اشارو_axis a = axis;

    إذا (seat->اشارو_2.focus) {
        seat->اشارو_2.pending_چوکٺو.have_axis = true;

        بدل (a) {
        حالة WL_اشارو_AXIS_VERTICAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشارو_2.pending_چوکٺو.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارو_2.pending_چوکٺو.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارو_2.pending_چوکٺو.axis.y = 0.0f;
                }
                seat->اشارو_2.pending_چوکٺو.axis.y += 0 - (عائم)wl_fixed_منزل_double(قدر);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشارو_2.pending_چوکٺو.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارو_2.pending_چوکٺو.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارو_2.pending_چوکٺو.axis.y = 0 - (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشارو_2.pending_چوکٺو.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارو_2.pending_چوکٺو.axis.y = 0 - (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            }
            اكسر;
        حالة WL_اشارو_AXIS_HORIZONTAL_SCROLL:
            بدل (type) {
            حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                إذا (seat->اشارو_2.pending_چوکٺو.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->اشارو_2.pending_چوکٺو.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->اشارو_2.pending_چوکٺو.axis.x = 0.0f;
                }
                seat->اشارو_2.pending_چوکٺو.axis.x += (عائم)wl_fixed_منزل_double(قدر);
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                إذا (seat->اشارو_2.pending_چوکٺو.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->اشارو_2.pending_چوکٺو.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->اشارو_2.pending_چوکٺو.axis.x = (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                إذا (seat->اشارو_2.pending_چوکٺو.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->اشارو_2.pending_چوکٺو.axis.x = (عائم)wl_fixed_منزل_double(قدر);
                }
                اكسر;
            }
            اكسر;
        }
    }
}

ساكن فراغ اشارو_handle_axis(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                uint32_t وقت, uint32_t axis, wl_fixed_t قدر)
{
    SDL_WaylandSeat *seat = معلومات;
    ثابت Uint64 nsTimestamp = Wayland_Get_اشارو_Timestamp(seat, وقت);

    إذا (wl_seat_get_نسخو(seat->wl_seat) >= WL_اشارو_چوکٺو_SINCE_نسخو) {
        seat->اشارو_2.pending_چوکٺو.timestamp_ns = nsTimestamp;
        اشارو_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, قدر);
    } وإلا {
        اشارو_handle_axis_common_v1(seat, nsTimestamp, axis, قدر);
    }
}

ساكن فراغ اشارو_handle_axis_relative_direction(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = معلومات;

    بدل (axis_relative_direction) {
    حالة WL_اشارو_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->اشارو_2.pending_چوکٺو.axis.direction = SDL_MOUSEWHEEL_عام;
        اكسر;
    حالة WL_اشارو_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->اشارو_2.pending_چوکٺو.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        اكسر;
    }
}

ساكن فراغ اشارو_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_دري_معلومات *دري = seat->اشارو_2.focus;

    إذا (دري) {
        SDL_Mouse *mouse = SDL_GetMouse();
        مزدوج dx;
        مزدوج dy;
        إذا (mouse->داخلا_Transform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.relative.dx_unaccel);
            dy = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.relative.dy_unaccel);
        } وإلا {
            dx = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.relative.dx) * دري->اشارو_scale.x;
            dy = wl_fixed_منزل_double(seat->اشارو_2.pending_چوکٺو.relative.dy) * دري->اشارو_scale.y;
        }

        SDL_SendMouseMotion(seat->اشارو_2.pending_چوکٺو.timestamp_ns, دري->sdlwindow, seat->اشارو_2.sdl_id, true, (عائم)dx, (عائم)dy);
    }
}

ساكن فراغ اشارو_dispatch_axis(SDL_WaylandSeat *seat)
{
    عائم x, y;
    SDL_MouseWheelDirection direction = seat->اشارو_2.pending_چوکٺو.axis.direction;

    بدل (seat->اشارو_2.pending_چوکٺو.axis.x_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->اشارو_2.pending_چوکٺو.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->اشارو_2.pending_چوکٺو.axis.x;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->اشارو_2.pending_چوکٺو.axis.x / 120.0f;
        اكسر;
    افتراضي:
        x = 0.0f;
        اكسر;
    }

    بدل (seat->اشارو_2.pending_چوکٺو.axis.y_axis_type) {
    حالة SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->اشارو_2.pending_چوکٺو.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->اشارو_2.pending_چوکٺو.axis.y;
        اكسر;
    حالة SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->اشارو_2.pending_چوکٺو.axis.y / 120.0f;
        اكسر;
    افتراضي:
        y = 0.0f;
        اكسر;
    }

    SDL_SendMouseWheel(seat->اشارو_2.pending_چوکٺو.timestamp_ns,
                       seat->اشارو_2.focus->sdlwindow, seat->اشارو_2.sdl_id, x, y, direction);
}

ساكن فراغ اشارو_handle_چوکٺو(فراغ *معلومات, بنية wl_اشارو *اشارو_2)
{
    SDL_WaylandSeat *seat = معلومات;

    إذا (seat->اشارو_2.pending_چوکٺو.enter_surface) {
        إذا (seat->اشارو_2.pending_چوکٺو.leave_surface) {
            SDL_دري_معلومات *دري_معلومات_2 = seat->اشارو_2.focus;
            SDL_دري_معلومات *new_focus = Wayland_Get_دري_معلومات_For_Owned_Surface(seat->اشارو_2.pending_چوکٺو.enter_surface);

            إذا (دري_معلومات_2 && (دري_معلومات_2->sdlwindow->flags & SDL_دري_MOUSE_CAPTURE) && دري_معلومات_2 == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->اشارو_2.focus_surface = seat->اشارو_2.pending_چوکٺو.enter_surface;
                seat->اشارو_2.pending_چوکٺو.enter_surface = عدم;
                seat->اشارو_2.pending_چوکٺو.leave_surface = عدم;
            } وإلا {
                // Leaving the previous surface before entering a new surface.
                اشارو_dispatch_leave(seat, false);
                seat->اشارو_2.pending_چوکٺو.leave_surface = عدم;
            }
        }

        إذا (seat->اشارو_2.pending_چوکٺو.enter_surface) {
            اشارو_dispatch_enter(seat);
        }
    }

    إذا (seat->اشارو_2.pending_چوکٺو.have_absolute) {
        اشارو_dispatch_absolute_motion(seat, seat->اشارو_2.pending_چوکٺو.have_warp);
    }

    إذا (seat->اشارو_2.pending_چوکٺو.have_relative) {
        اشارو_dispatch_relative_motion(seat);
    }

    لكل (Uint8 i = 1; seat->اشارو_2.pending_چوکٺو.buttons_pressed || seat->اشارو_2.pending_چوکٺو.buttons_released; ++i) {
        ثابت Uint32 نقاب = SDL_BUTTON_نقاب(i);
        إذا (seat->اشارو_2.pending_چوکٺو.buttons_pressed & نقاب) {
            اشارو_dispatch_button(seat, i, true);
            seat->اشارو_2.pending_چوکٺو.buttons_pressed &= ~نقاب;
        }
        إذا (seat->اشارو_2.pending_چوکٺو.buttons_released & نقاب) {
            اشارو_dispatch_button(seat, i, false);
            seat->اشارو_2.pending_چوکٺو.buttons_released &= ~نقاب;
        }
    }

    إذا (seat->اشارو_2.pending_چوکٺو.have_axis) {
        اشارو_dispatch_axis(seat);
    }

    إذا (seat->اشارو_2.pending_چوکٺو.leave_surface) {
        اشارو_dispatch_leave(seat, true);
    }

    SDL_zero(seat->اشارو_2.pending_چوکٺو);
}

ساكن فراغ اشارو_handle_axis_ذريعو(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                       uint32_t axis_ذريعو)
{
    // unimplemented
}

ساكن فراغ اشارو_handle_axis_stop(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                     uint32_t وقت, uint32_t axis)
{
    // unimplemented
}

ساكن فراغ اشارو_handle_axis_discrete(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = معلومات;
    اشارو_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

ساكن فراغ اشارو_handle_axis_value120(فراغ *معلومات, بنية wl_اشارو *اشارو_2,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = معلومات;
    اشارو_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

ساكن فراغ اشارو_handle_warp(فراغ *معلومات, بنية wl_اشارو *wl_اشارو, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;

    seat->اشارو_2.pending_چوکٺو.have_absolute = true;
    seat->اشارو_2.pending_چوکٺو.have_warp = true;
    seat->اشارو_2.pending_چوکٺو.absolute.sx = surface_x;
    seat->اشارو_2.pending_چوکٺو.absolute.sy = surface_y;
}

ساكن ثابت بنية wl_اشارو_listener اشارو_listener = {
    اشارو_handle_enter,
    اشارو_handle_leave,
    اشارو_handle_motion,
    اشارو_handle_button,
    اشارو_handle_axis,
    اشارو_handle_چوکٺو,                   // Version 5
    اشارو_handle_axis_ذريعو,             // Version 5
    اشارو_handle_axis_stop,               // Version 5
    اشارو_handle_axis_discrete,           // Version 5
    اشارو_handle_axis_value120,           // Version 8
    اشارو_handle_axis_relative_direction, // Version 9
    اشارو_handle_warp                     // Version 11
};

ساكن فراغ relative_اشارو_handle_relative_motion(فراغ *معلومات,
                                                    بنية zwp_relative_اشارو_v1 *اشارو_2,
                                                    uint32_t وقت_hi,
                                                    uint32_t وقت_lo,
                                                    wl_fixed_t dx,
                                                    wl_fixed_t dy,
                                                    wl_fixed_t dx_unaccel,
                                                    wl_fixed_t dy_unaccel)
{
    SDL_WaylandSeat *seat = معلومات;

    // Relative pointer event times are in microsecond granularity.
    seat->اشارو_2.pending_چوکٺو.relative.dx = dx;
    seat->اشارو_2.pending_چوکٺو.relative.dy = dy;
    seat->اشارو_2.pending_چوکٺو.relative.dx_unaccel = dx_unaccel;
    seat->اشارو_2.pending_چوکٺو.relative.dy_unaccel = dy_unaccel;
    seat->اشارو_2.pending_چوکٺو.timestamp_ns = Wayland_Adjust_Event_Timestamp_بنياد(SDL_US_منزل_NS(((Uint64)وقت_hi << 32) | (Uint64)وقت_lo));

    إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) >= WL_اشارو_چوکٺو_SINCE_نسخو) {
        seat->اشارو_2.pending_چوکٺو.have_relative = true;
    } وإلا {
        اشارو_dispatch_relative_motion(seat);
    }
}

ساكن ثابت بنية zwp_relative_اشارو_v1_listener relative_اشارو_listener = {
    relative_اشارو_handle_relative_motion,
};

ساكن فراغ locked_اشارو_locked(فراغ *معلومات, بنية zwp_locked_اشارو_v1 *locked_اشارو)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.is_confined = true;
}

ساكن فراغ locked_اشارو_unlocked(فراغ *معلومات, بنية zwp_locked_اشارو_v1 *locked_اشارو)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.is_confined = false;
}

ساكن ثابت بنية zwp_locked_اشارو_v1_listener locked_اشارو_listener = {
    locked_اشارو_locked,
    locked_اشارو_unlocked,
};

ساكن فراغ confined_اشارو_confined(فراغ *معلومات, بنية zwp_confined_اشارو_v1 *confined_اشارو)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.is_confined = true;
}

ساكن فراغ confined_اشارو_unconfined(فراغ *معلومات, بنية zwp_confined_اشارو_v1 *confined_اشارو)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->اشارو_2.is_confined = false;
}

ساكن ثابت بنية zwp_confined_اشارو_v1_listener confined_اشارو_listener = {
    confined_اشارو_confined,
    confined_اشارو_unconfined,
};

ساكن فراغ touch_handler_هيٺ_ڏانهن(فراغ *معلومات, بنية wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, بنية wl_surface *surface,
                               صحيح id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    SDL_دري_معلومات *دري_معلومات_2;

    // Check that this surface is valid.
    إذا (!surface) {
        أرجع;
    }

    Wayland_Seat_جوڙيو_Touch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    دري_معلومات_2 = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);

    إذا (دري_معلومات_2 && دري_معلومات_2->surface == surface) {
        عائم x, y;

        إذا (دري_معلومات_2->current.logical_ويڪر <= 1) {
            x = 0.5f;
        } وإلا {
            x = (عائم)wl_fixed_منزل_double(fx) / (دري_معلومات_2->current.logical_ويڪر - 1);
        }
        إذا (دري_معلومات_2->current.logical_اوچائي <= 1) {
            y = 0.5f;
        } وإلا {
            y = (عائم)wl_fixed_منزل_double(fy) / (دري_معلومات_2->current.logical_اوچائي - 1);
        }

        ++دري_معلومات_2->سرگرم_touch_ڳڻپ;
        SDL_سيٽ_Mouse_Focus(دري_معلومات_2->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), دري_معلومات_2->sdlwindow, SDL_EVENT_FINGER_هيٺ_ڏانهن, x, y, 1.0f);
    }
}

ساكن فراغ touch_handler_مٿي(فراغ *معلومات, بنية wl_touch *touch, uint32_t serial, uint32_t timestamp, صحيح id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    wl_fixed_t fx = 0, fy = 0;
    بنية wl_surface *surface = عدم;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    إذا (surface) {
        SDL_دري_معلومات *دري_معلومات_2 = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);

        إذا (دري_معلومات_2 && دري_معلومات_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / دري_معلومات_2->current.logical_ويڪر;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / دري_معلومات_2->current.logical_اوچائي;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), دري_معلومات_2->sdlwindow, SDL_EVENT_FINGER_مٿي, x, y, 0.0f);

            --دري_معلومات_2->سرگرم_touch_ڳڻپ;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            إذا (SDL_GetMouseFocus() == دري_معلومات_2->sdlwindow && !دري_معلومات_2->keyboard_focus_ڳڻپ &&
                !دري_معلومات_2->اشارو_focus_ڳڻپ && !دري_معلومات_2->سرگرم_touch_ڳڻپ) {
                SDL_سيٽ_Mouse_Focus(عدم);
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
        SDL_دري_معلومات *دري_معلومات_2 = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);

        إذا (دري_معلومات_2 && دري_معلومات_2->surface == surface) {
            ثابت عائم x = (عائم)wl_fixed_منزل_double(fx) / دري_معلومات_2->current.logical_ويڪر;
            ثابت عائم y = (عائم)wl_fixed_منزل_double(fy) / دري_معلومات_2->current.logical_اوچائي;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), دري_معلومات_2->sdlwindow, x, y, 1.0f);
        }
    }
}

ساكن فراغ touch_handler_چوکٺو(فراغ *معلومات, بنية wl_touch *touch)
{
}

ساكن فراغ touch_handler_cancel(فراغ *معلومات, بنية wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    SDL_Wayland_Touch_نقطو *tp, *عارضي;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_محفوظ (tp, عارضي, &seat->touch.points, link) {
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
    touch_handler_هيٺ_ڏانهن,
    touch_handler_مٿي,
    touch_handler_motion,
    touch_handler_چوکٺو,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#إذا !SDL_XKBCOMMON_CHECK_نسخو(1, 0, 0)
ساكن size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t ڪنجي, xkb_layout_اشاريو_t layout, xkb_level_اشاريو_t level, xkb_mod_نقاب_t *masks_ٻاهريون, size_t masks_سائيز)
{
    إذا (!masks_ٻاهريون || !masks_سائيز) {
        أرجع 0;
    }

    // Level 0 is always unmodified, so early out.
    إذا (level == 0) {
        *masks_ٻاهريون = 0;
        أرجع 1;
    }

    size_t نقاب_idx = 0;
    ثابت xkb_mod_نقاب_t keymod_masks[] = {
        0,
        seat->keyboard.xkb.سرڪايو_نقاب,
        seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.سرڪايو_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.سرڪايو_نقاب,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.سرڪايو_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.سرڪايو_نقاب,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.caps_نقاب_2,
        seat->keyboard.xkb.level5_نقاب | seat->keyboard.xkb.سرڪايو_نقاب | seat->keyboard.xkb.caps_نقاب_2
    };
    ثابت xkb_mod_نقاب_t pressed_mod_نقاب = seat->keyboard.xkb.سرڪايو_نقاب | seat->keyboard.xkb.level3_نقاب | seat->keyboard.xkb.level5_نقاب;
    ثابت xkb_mod_نقاب_t locked_mod_نقاب = seat->keyboard.xkb.caps_نقاب_2;

    لكل (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_نقاب, 0, keymod_masks[i] & locked_mod_نقاب, 0, 0, layout);
        إذا (WAYLAND_xkb_state_ڪنجي_get_level(seat->keyboard.xkb.state, ڪنجي, layout) == level) {
            masks_ٻاهريون[نقاب_idx] = keymod_masks[i];

            إذا (++نقاب_idx == masks_سائيز) {
                اكسر;
            }
        }
    }

    أرجع نقاب_idx;
}
#جيڪڏهن_پورو

ساكن فراغ Wayland_KeymapIterator(بنية xkb_keymap *keymap, xkb_keycode_t ڪنجي, فراغ *معلومات)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    ثابت xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    ثابت xkb_mod_نقاب_t xkb_valid_mod_نقاب = seat->keyboard.xkb.سرڪايو_نقاب |
                                              seat->keyboard.xkb.alt_نقاب |
                                              seat->keyboard.xkb.level3_نقاب |
                                              seat->keyboard.xkb.level5_نقاب |
                                              seat->keyboard.xkb.caps_نقاب_2;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, ڪنجي - 8);
    }

    لكل (xkb_layout_اشاريو_t layout = 0; layout < seat->keyboard.xkb.انگ_layouts; ++layout) {
        ثابت xkb_level_اشاريو_t انگ_سطحون = WAYLAND_xkb_keymap_انگ_سطحون_for_ڪنجي(seat->keyboard.xkb.keymap, ڪنجي, layout);
        لكل (xkb_level_اشاريو_t level = 0; level < انگ_سطحون; ++level) {
            إذا (WAYLAND_xkb_keymap_ڪنجي_get_syms_by_level(seat->keyboard.xkb.keymap, ڪنجي, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                إذا (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_Get_Scancode_From_ڪنجي_Sym(syms[0], ڪنجي);
                    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
                        استمر;
                    }
                }

                xkb_mod_نقاب_t xkb_mod_masks[16];
#إذا SDL_XKBCOMMON_CHECK_نسخو(1, 0, 0)
                ثابت size_t انگ_masks = WAYLAND_xkb_keymap_ڪنجي_get_mods_for_level(seat->keyboard.xkb.keymap, ڪنجي, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#وإلا
                ثابت size_t انگ_masks = xkb_legacy_get_mods_for_level(seat, ڪنجي, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#جيڪڏهن_پورو
                لكل (size_t نقاب = 0; نقاب < انگ_masks; ++نقاب) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    إذا ((xkb_mod_masks[نقاب] | xkb_valid_mod_نقاب) != xkb_valid_mod_نقاب) {
                        استمر;
                    }

                    ثابت SDL_Keymod sdl_mod = (xkb_mod_masks[نقاب] & seat->keyboard.xkb.سرڪايو_نقاب ? SDL_KMOD_سرڪايو : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.alt_نقاب ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level3_نقاب ? SDL_KMOD_گهڻائي : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.level5_نقاب ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[نقاب] & seat->keyboard.xkb.caps_نقاب_2 ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_Get_ڪنجي_ڪوڊ_From_ڪنجي_Sym(syms[0], ڪنجي, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    إذا (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_Get_Keymap_ايندڙ_Reserved_Scancode(seat->keyboard.sdl_keymap[0]);
                        إذا (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_سيٽ_Keymap_داخلا(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_Reserved_ڪنجي *res = WAYLAND_wl_array_جوڙيو(&seat->keyboard.reserved_scancodes, حجم(Wayland_Reserved_ڪنجي));
                        إذا (res) {
                            res->scancode = scancode;
                            res->ڪنجي = ڪنجي - 8;
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

                    SDL_سيٽ_Keymap_داخلا(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

ساكن فراغ keyboard_handle_keymap(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                   uint32_t format, صحيح fd, uint32_t سائيز)
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

    map_str = mmap(عدم, سائيز, PROT_READ, MAP_PRIVATE, fd, 0);
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
    munmap(map_str, سائيز);
    close(fd);

    إذا (!seat->keyboard.xkb.keymap) {
        SDL_سيٽ_Error("failed to compile keymap");
        أرجع;
    }

    // Clear the old layouts.
    لكل (xkb_layout_اشاريو_t i = 0; i < seat->keyboard.xkb.انگ_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = عدم;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.انگ_layouts = 0;

#إذا SDL_XKBCOMMON_CHECK_نسخو(1, 10, 0)
    seat->keyboard.xkb.سرڪايو_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_سرڪايو);
    seat->keyboard.xkb.ctrl_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.انگ_نقاب = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_انگ);
    seat->keyboard.xkb.caps_نقاب_2 = WAYLAND_xkb_keymap_mod_get_نقاب(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#وإلا
#وصف_ڪريو GET_MOD_اشاريو(mod) \
    WAYLAND_xkb_keymap_mod_get_اشاريو(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.سرڪايو_نقاب = 1 << GET_MOD_اشاريو(سرڪايو_2);
    seat->keyboard.xkb.ctrl_نقاب = 1 << GET_MOD_اشاريو(CTRL);
    seat->keyboard.xkb.alt_نقاب = 1 << GET_MOD_اشاريو(ALT);
    seat->keyboard.xkb.gui_نقاب = 1 << GET_MOD_اشاريو(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_نقاب = 1 << GET_MOD_اشاريو(MOD5);
    seat->keyboard.xkb.level5_نقاب = 1 << GET_MOD_اشاريو(MOD3);
    seat->keyboard.xkb.انگ_نقاب = 1 << GET_MOD_اشاريو(انگ_2);
    seat->keyboard.xkb.caps_نقاب_2 = 1 << GET_MOD_اشاريو(CAPS);
#وصف_رد GET_MOD_اشاريو
#جيڪڏهن_پورو

    إذا (seat->keyboard.xkb.state != عدم) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = عدم;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    إذا (!seat->keyboard.xkb.state) {
        SDL_سيٽ_Error("failed to create XKB state");
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
    seat->keyboard.xkb.انگ_layouts = WAYLAND_xkb_keymap_انگ_layouts(seat->keyboard.xkb.keymap);
    إذا (seat->keyboard.xkb.انگ_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.انگ_layouts, حجم(SDL_Keymap *));
        إذا (!seat->keyboard.sdl_keymap) {
            أرجع;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        لكل (xkb_layout_اشاريو_t i = 0; i < seat->keyboard.xkb.انگ_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            إذا (!seat->keyboard.sdl_keymap[i]) {
                لكل (xkb_layout_اشاريو_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = عدم;
                أرجع;
            }
        }

        WAYLAND_xkb_keymap_ڪنجي_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.انگ_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_Seat_سيٽ_Keymap(seat);
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
                SDL_سيٽ_Error("could not create XKB compose state");
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
ساكن SDL_Scancode Wayland_Get_Scancode_For_ڪنجي(SDL_WaylandSeat *seat, Uint32 ڪنجي, ثابت xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    إذا (!seat->keyboard.is_virtual) {
        scancode = SDL_Get_Scancode_From_جدول(SDL_SCANCODE_جدول_LINUX, ڪنجي);

        // No table entry? Check the reserved list.
        إذا (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_Reserved_ڪنجي *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                إذا (i->ڪنجي == ڪنجي) {
                    أرجع i->scancode;
                }
            }
        }
    } وإلا {
        ثابت xkb_keysym_t *keysym;
        إذا (WAYLAND_xkb_state_ڪنجي_get_syms(seat->keyboard.xkb.state, ڪنجي + 8, &keysym) > 0) {
            scancode = SDL_Get_Scancode_From_ڪنجي_Sym(keysym[0], ڪنجي + 8);
            إذا (syms) {
                *syms = keysym;
            }
        }
    }

    أرجع scancode;
}

ساكن فراغ Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool ڪنجي_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    إذا (!ڪنجي_pressed) {
        إذا (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.سرڪايو_نقاب) {
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_سرڪايو)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_سرڪايو;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_سرڪايو;
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
            إذا (!(seat->keyboard.pressed_modifiers & SDL_KMOD_گهڻائي)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_گهڻائي;
            }
        } وإلا {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_گهڻائي;
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

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.سرڪايو_نقاب) {
        إذا (seat->keyboard.pressed_modifiers & SDL_KMOD_سرڪايو) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_سرڪايو;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_سرڪايو);
        } وإلا إذا (!(seat->keyboard.locked_modifiers & SDL_KMOD_سرڪايو)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_سرڪايو;
        }
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_سرڪايو;
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
        seat->keyboard.locked_modifiers |= SDL_KMOD_گهڻائي;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_گهڻائي;
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

    إذا (xkb_locked_modifiers & seat->keyboard.xkb.انگ_نقاب) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_انگ;
    } وإلا {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_انگ;
    }

    SDL_سيٽ_Mod_State(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

ساكن فراغ Wayland_Handle_Modifier_ڪنجيون(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    ثابت SDL_Keycode keycode = SDL_Get_ڪنجي_From_Scancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
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
    حالة SDLK_گهڻائي:
        mod = SDL_KMOD_گهڻائي;
        اكسر;
    حالة SDLK_LEVEL5_سرڪايو:
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
                                  بنية wl_array *ڪنجيون)
{
    SDL_WaylandSeat *seat = معلومات;
    uint32_t *ڪنجي;

    إذا (!surface) {
        // Enter event for a destroyed surface.
        أرجع;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_دري_معلومات *دري = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);
    إذا (!دري) {
        // Not a surface owned by SDL.
        أرجع;
    }

    ++دري->keyboard_focus_ڳڻپ;
    seat->keyboard.focus = دري;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_سيٽ_Keyboard_Focus(دري->sdlwindow->keyboard_focus ? دري->sdlwindow->keyboard_focus : دري->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشارو_Grabs(seat->display, دري);

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_داخلا(seat);

#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    إذا (!seat->متن_داخلا.zwp_متن_داخلا) {
        SDL_IME_سيٽ_Focus(true);
    }
#جيڪڏهن_پورو

    Uint64 timestamp = SDL_GetTicksNS();
    دري->آخري_focus_event_وقت_ns = timestamp;

    Wayland_Seat_سيٽ_Keymap(seat);

    wl_array_for_each (ڪنجي, ڪنجيون) {
        ثابت SDL_Scancode scancode = Wayland_Get_Scancode_For_ڪنجي(seat, *ڪنجي, عدم);
        إذا (scancode != SDL_SCANCODE_UNKNOWN) {
            ثابت SDL_Keycode keycode = SDL_Get_ڪنجي_From_Scancode(scancode, SDL_KMOD_NONE, false);

            بدل (keycode) {
            حالة SDLK_LSHIFT:
            حالة SDLK_RSHIFT:
            حالة SDLK_LCTRL:
            حالة SDLK_RCTRL:
            حالة SDLK_LALT:
            حالة SDLK_RALT:
            حالة SDLK_LGUI:
            حالة SDLK_RGUI:
            حالة SDLK_گهڻائي:
            حالة SDLK_LEVEL5_سرڪايو:
                Wayland_Handle_Modifier_ڪنجيون(seat, scancode, true);
                SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(timestamp, seat->keyboard.sdl_id, *ڪنجي, scancode, true);
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

    SDL_دري_معلومات *دري = Wayland_Get_دري_معلومات_For_Owned_Surface(surface);
    إذا (!دري) {
        // Not a surface owned by SDL.
        أرجع;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.ڪنجي = 0;

    SDL_دري *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    طالما (keyboard_focus && SDL_دري_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->والد;
    }

    ثابت bool had_focus = keyboard_focus && دري->sdlwindow == keyboard_focus;
    seat->keyboard.focus = عدم;
    --دري->keyboard_focus_ڳڻپ;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    إذا (!دري->keyboard_focus_ڳڻپ && had_focus) {
        SDL_سيٽ_Keyboard_Focus(عدم);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_Display_Update_اشارو_Grabs(seat->display, دري);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_Seat_Update_متن_داخلا(seat);

#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    إذا (!seat->متن_داخلا.zwp_متن_داخلا && !دري->keyboard_focus_ڳڻپ) {
        SDL_IME_سيٽ_Focus(false);
    }
#جيڪڏهن_پورو

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    إذا (SDL_GetMouseFocus() == دري->sdlwindow && !دري->اشارو_focus_ڳڻپ && !دري->سرگرم_touch_ڳڻپ) {
        SDL_سيٽ_Mouse_Focus(عدم);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_معلومات_Device_سيٽ_Selection_Offer(seat->معلومات_device, عدم);
}

ساكن bool keyboard_داخلا_get_متن(حرف متن[8], ثابت SDL_WaylandSeat *seat, uint32_t ڪنجي, bool هيٺ_ڏانهن, bool *handled_by_ime)
{
    ثابت xkb_keysym_t *syms;
    xkb_keysym_t sym;

    إذا (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        أرجع false;
    }

    // TODO: Can this happen?
    إذا (WAYLAND_xkb_state_ڪنجي_get_syms(seat->keyboard.xkb.state, ڪنجي + 8, &syms) != 1) {
        أرجع false;
    }
    sym = syms[0];

#جيڪڏهن_وصف_ٿيل SDL_USE_IME
    إذا (SDL_IME_Process_ڪنجي_Event(sym, ڪنجي + 8, هيٺ_ڏانهن)) {
        إذا (handled_by_ime) {
            *handled_by_ime = true;
        }
        أرجع true;
    }
#جيڪڏهن_پورو

    إذا (!هيٺ_ڏانهن) {
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
            sym = XKB_ڪنجي_No_نشان;
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

ساكن فراغ keyboard_handle_ڪنجي(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                uint32_t serial, uint32_t وقت, uint32_t ڪنجي,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = معلومات;
    تعداد wl_keyboard_ڪنجي_state state = state_w;
    حرف متن[8];
    bool has_متن = false;
    bool handled_by_ime = false;
    ثابت Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, وقت);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    إذا (state == WL_KEYBOARD_ڪنجي_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        إذا (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_ڪنجي_repeats(seat->keyboard.xkb.keymap, ڪنجي + 8)) {
            أرجع;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_ڪنجي_STATE_PRESSED;
    }

    Wayland_Seat_سيٽ_Keymap(seat);

    إذا (state == WL_KEYBOARD_ڪنجي_STATE_PRESSED) {
        SDL_دري *keyboard_focus = SDL_GetKeyboardFocus();
        إذا (keyboard_focus && SDL_متن_داخلا_سرگرم(keyboard_focus)) {
            has_متن = keyboard_داخلا_get_متن(متن, seat, ڪنجي, true, &handled_by_ime);
        }
    } وإلا {
        إذا (ڪنجي == seat->keyboard.repeat.ڪنجي) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            ثابت Uint64 elapsed = SDL_MS_منزل_NS(وقت - seat->keyboard.repeat.wl_press_وقت_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.ڪنجي = 0;
        }
        keyboard_داخلا_get_متن(متن, seat, ڪنجي, false, &handled_by_ime);
    }

    ثابت xkb_keysym_t *syms = عدم;
    SDL_Scancode scancode = Wayland_Get_Scancode_For_ڪنجي(seat, ڪنجي, &syms);
    Wayland_Handle_Modifier_ڪنجيون(seat, scancode, state == WL_KEYBOARD_ڪنجي_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    إذا (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        ثابت SDL_Keycode keycode = (SDL_Keycode)SDL_ڪنجي_Sym_منزل_Ucs4(syms[0]);
        إذا (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            إذا (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_نقاب) {
                scancode = SDL_Get_Keymap_ايندڙ_Reserved_Scancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_سيٽ_Keymap_داخلا(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_Send_Keyboard_ڪنجي_Ignore_Modifiers(timestamp_ns, seat->keyboard.sdl_id, ڪنجي, scancode, state == WL_KEYBOARD_ڪنجي_STATE_PRESSED);

    إذا (state == WL_KEYBOARD_ڪنجي_STATE_PRESSED) {
        إذا (handled_by_ime) {
            has_متن = false;
        }
        إذا (has_متن && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_Send_Keyboard_متن(متن);
        }
        إذا (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_ڪنجي_repeats(seat->keyboard.xkb.keymap, ڪنجي + 8)) {
            keyboard_repeat_سيٽ(&seat->keyboard.repeat, seat->keyboard.sdl_id, ڪنجي, وقت, timestamp_ns, scancode, has_متن ? متن : عدم);
        }
    }
}

ساكن فراغ keyboard_handle_modifiers(فراغ *معلومات, بنية wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t گروهه)
{
    SDL_WaylandSeat *seat = معلومات;
    ثابت uint32_t اڳيون_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = گروهه;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    إذا (!seat->keyboard.xkb.state) {
        أرجع;
    }

    WAYLAND_xkb_state_update_نقاب(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, گروهه);

    // If a key is repeating, update the text to apply the modifier.
    إذا (seat->keyboard.repeat.ڪنجي) {
        حرف متن[8];

        إذا (keyboard_داخلا_get_متن(متن, seat, seat->keyboard.repeat.ڪنجي, true, عدم)) {
            SDL_strlcpy(seat->keyboard.repeat.متن, متن, SDL_arraysize(seat->keyboard.repeat.متن));
        }
    }

    إذا (گروهه != اڳيون_layout) {
        Wayland_Seat_سيٽ_Keymap(seat);

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
        seat->keyboard.repeat.ڪنجي = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

ساكن ثابت بنية wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_ڪنجي,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

ساكن فراغ Wayland_Seat_Destroy_اشارو(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->اشارو_2.cursor_state);

    // End any active gestures.
    إذا (seat->اشارو_2.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_پڇاڙي, 0, seat->اشارو_2.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    إذا (seat->اشارو_2.focus) {
        seat->اشارو_2.pending_چوکٺو.leave_surface = seat->اشارو_2.focus->surface;
        اشارو_dispatch_leave(seat, false);
        seat->اشارو_2.pending_چوکٺو.leave_surface = عدم;
    }

    SDL_RemoveMouse(seat->اشارو_2.sdl_id);

    إذا (seat->اشارو_2.confined_اشارو) {
        zwp_confined_اشارو_v1_destroy(seat->اشارو_2.confined_اشارو);
    }

    إذا (seat->اشارو_2.locked_اشارو) {
        zwp_locked_اشارو_v1_destroy(seat->اشارو_2.locked_اشارو);
    }

    إذا (seat->اشارو_2.relative_اشارو) {
        zwp_relative_اشارو_v1_destroy(seat->اشارو_2.relative_اشارو);
    }

    إذا (seat->اشارو_2.timestamps) {
        zwp_داخلا_timestamps_v1_destroy(seat->اشارو_2.timestamps);
    }

    إذا (seat->اشارو_2.gesture_pinch) {
        zwp_اشارو_gesture_pinch_v1_destroy(seat->اشارو_2.gesture_pinch);
    }

    إذا (seat->اشارو_2.wl_اشارو) {
        إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) >= WL_اشارو_RELEASE_SINCE_نسخو) {
            wl_اشارو_release(seat->اشارو_2.wl_اشارو);
        } وإلا {
            wl_اشارو_destroy(seat->اشارو_2.wl_اشارو);
        }
    }

    SDL_zero(seat->اشارو_2);
}

ساكن فراغ Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    إذا (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    إذا (seat->keyboard.sdl_keymap) {
        إذا (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.انگ_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_سيٽ_Mod_State(SDL_KMOD_NONE);
        }
        لكل (xkb_layout_اشاريو_t i = 0; i < seat->keyboard.xkb.انگ_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = عدم;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    إذا (seat->keyboard.ڪنجي_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ڪنجي_inhibitor);
    }

    إذا (seat->keyboard.timestamps) {
        zwp_داخلا_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    إذا (seat->keyboard.wl_keyboard) {
        إذا (wl_keyboard_get_نسخو(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_نسخو) {
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
        zwp_داخلا_timestamps_v1_destroy(seat->touch.timestamps);
    }

    إذا (seat->touch.wl_touch) {
        إذا (wl_touch_get_نسخو(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_نسخو) {
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

    إذا ((capabilities & WL_SEAT_CAPABILITY_اشارو) && !seat->اشارو_2.wl_اشارو) {
        seat->اشارو_2.wl_اشارو = wl_seat_get_اشارو(wl_seat);
        SDL_zero(seat->اشارو_2.pending_چوکٺو.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_اشارو_سيٽ_user_معلومات(seat->اشارو_2.wl_اشارو, seat);
        wl_اشارو_جوڙيو_listener(seat->اشارو_2.wl_اشارو, &اشارو_listener, seat);

        // Pointer gestures
        Wayland_Seat_Create_اشارو_Gestures(seat);

        seat->اشارو_2.sdl_id = SDL_Get_ايندڙ_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_اشارو_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_اشارو_NAME, seat->اشارو_2.sdl_id);
        }

        SDL_جوڙيو_Mouse(seat->اشارو_2.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_اشارو) && seat->اشارو_2.wl_اشارو) {
        Wayland_Seat_Destroy_اشارو(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_سيٽ_user_معلومات(seat->touch.wl_touch, seat);
        wl_touch_جوڙيو_listener(seat->touch.wl_touch, &touch_listener, seat);

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_جوڙيو_Touch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_سڌو, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    إذا ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_سيٽ_user_معلومات(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_جوڙيو_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_Get_ايندڙ_Object_ID();

        إذا (seat->name) {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } وإلا {
            SDL_snprintf(name_fmt, حجم(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_جوڙيو_Keyboard(seat->keyboard.sdl_id, name_fmt);
    } وإلا إذا (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_Seat_رجسٽر_داخلا_Timestamp_Listeners(seat);
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
    Wayland_معلومات_Offer_جوڙيو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 mime_type);
}

ساكن فراغ معلومات_offer_handle_ذريعو_actions(فراغ *معلومات, بنية wl_معلومات_offer *wl_معلومات_offer,
                                             uint32_t ذريعو_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 ذريعو_actions);
}

ساكن فراغ معلومات_offer_handle_actions(فراغ *معلومات, بنية wl_معلومات_offer *wl_معلومات_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_معلومات_offer ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)wl_معلومات_offer) : -1),
                 dnd_action);
}

ساكن ثابت بنية wl_معلومات_offer_listener معلومات_offer_listener = {
    معلومات_offer_handle_offer,
    معلومات_offer_handle_ذريعو_actions, // Version 3
    معلومات_offer_handle_actions,        // Version 3
};

ساكن فراغ primary_selection_offer_handle_offer(فراغ *معلومات, بنية zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 ثابت حرف *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = معلومات;
    Wayland_Primary_Selection_Offer_جوڙيو_MIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
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
        wl_معلومات_offer_سيٽ_user_معلومات(id, معلومات_offer);
        wl_معلومات_offer_جوڙيو_listener(id, &معلومات_offer_listener, معلومات_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
    }
}

ساكن فراغ معلومات_device_handle_enter(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                     uint32_t serial, بنية wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, بنية wl_معلومات_offer *id)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;
    SDL_دري_معلومات *دري = surface ? Wayland_Get_دري_معلومات_For_Owned_Surface(surface) : عدم;
    معلومات_device->has_mime_file = false;
    معلومات_device->متن_mime_type = عدم;

    معلومات_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    إذا (id) {
        معلومات_device->drag_offer = wl_معلومات_offer_get_user_معلومات(id);
    }

    إذا (معلومات_device->drag_offer && دري && دري->قبولي_drag_and_drop) {
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
        إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, FILE_PORTAL_MIME)) {
            معلومات_device->has_mime_file = true;
            wl_معلومات_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#جيڪڏهن_پورو
        إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, FILE_MIME)) {
            معلومات_device->has_mime_file = true;
            wl_معلومات_offer_accept(id, serial, FILE_MIME);
        }

        إذا (!معلومات_device->has_mime_file) {
            size_t mime_ڳڻپ = 0;
            ثابت حرف *ثابت *متن_mime_types = Wayland_Get_متن_Mime_Types(SDL_GetVideoDevice(), &mime_ڳڻپ);
            لكل (size_t i = 0; i < mime_ڳڻپ; ++i) {
                إذا (Wayland_معلومات_Offer_Has_MIME(معلومات_device->drag_offer, متن_mime_types[i])) {
                    معلومات_device->متن_mime_type = متن_mime_types[i];
                    wl_معلومات_offer_accept(id, serial, متن_mime_types[i]);
                    اكسر;
                }
            }
        }

        إذا (معلومات_device->has_mime_file || معلومات_device->متن_mime_type) {
            // SDL only supports "copy" style drag and drop
            إذا (wl_معلومات_offer_get_نسخو(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سيٽ_ACTIONS_SINCE_نسخو) {
                wl_معلومات_offer_سيٽ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_COPY, WL_معلومات_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            معلومات_device->dnd_دري = دري->sdlwindow;
            معلومات_device->dnd_surface = surface;
            مزدوج dx = wl_fixed_منزل_double(x);
            مزدوج dy = wl_fixed_منزل_double(y);

            // If over the mask, adjust the offset.
            إذا (surface == دري->نقاب.surface) {
                dx += (مزدوج)دري->نقاب.وٿي_x;
                dy += (مزدوج)دري->نقاب.وٿي_y;
            }

            dx *= دري->اشارو_scale.x;
            dy *= دري->اشارو_scale.y;

            SDL_SendDropPosition(معلومات_device->dnd_دري, (عائم)dx, (عائم)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id),
                         wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), SDL_Get_دري_ID(معلومات_device->dnd_دري), serial);
        } وإلا {
            // Decline the offer.
            wl_معلومات_offer_accept(id, serial, عدم);
            إذا (wl_معلومات_offer_get_نسخو(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سيٽ_ACTIONS_SINCE_نسخو) {
                wl_معلومات_offer_سيٽ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id), wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
        }
    } وإلا {
        معلومات_device->dnd_دري = عدم;
        معلومات_device->dnd_surface = عدم;

        // Decline the offer.
        إذا (id) {
            wl_معلومات_offer_accept(id, serial, عدم);
            إذا (wl_معلومات_offer_get_نسخو(معلومات_device->drag_offer->offer) >= WL_معلومات_OFFER_سيٽ_ACTIONS_SINCE_نسخو) {
                wl_معلومات_offer_سيٽ_actions(معلومات_device->drag_offer->offer, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE, WL_معلومات_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1,
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y), serial);
    }
}

ساكن فراغ معلومات_device_handle_leave(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer) {
        إذا (معلومات_device->dnd_دري) {
            SDL_SendDropComplete(معلومات_device->dnd_دري);
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                         SDL_Get_دري_ID(معلومات_device->dnd_دري), معلومات_device->drag_serial);
        } وإلا {
            SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                         معلومات_device->drag_serial);
        }
        Wayland_معلومات_Offer_Destroy(معلومات_device->drag_offer);
        معلومات_device->drag_offer = عدم;
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    معلومات_device->has_mime_file = false;
    معلومات_device->متن_mime_type = عدم;
}

ساكن فراغ معلومات_device_handle_motion(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device,
                                      uint32_t وقت, wl_fixed_t x, wl_fixed_t y)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer && معلومات_device->dnd_دري && (معلومات_device->has_mime_file || معلومات_device->متن_mime_type)) {
        SDL_دري_معلومات *دري_معلومات_2 = معلومات_device->dnd_دري->اندروني;
        مزدوج dx = wl_fixed_منزل_double(x);
        مزدوج dy = wl_fixed_منزل_double(y);

        // If over the mask, adjust the offset.
        إذا (معلومات_device->dnd_surface == دري_معلومات_2->نقاب.surface) {
            dx += (مزدوج)دري_معلومات_2->نقاب.وٿي_x;
            dy += (مزدوج)دري_معلومات_2->نقاب.وٿي_y;
        }

        dx *= دري_معلومات_2->اشارو_scale.x;
        dy *= دري_معلومات_2->اشارو_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(معلومات_device->dnd_دري, (عائم)dx, (عائم)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                     wl_fixed_منزل_int(x), wl_fixed_منزل_int(y),
                     SDL_Get_دري_ID(معلومات_device->dnd_دري), معلومات_device->drag_serial);
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
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

    إذا (drop->dnd_دري) {
        size_t ڊيگهائي;
        bool drop_handled = false;

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
        إذا (Wayland_معلومات_Offer_Has_MIME(offer, FILE_PORTAL_MIME)) {
            فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, FILE_PORTAL_MIME, &ڊيگهائي);
            إذا (بفر_2) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                إذا (dbus) {
                    صحيح رستو_ڳڻپ = 0;
                    حرف **paths = SDL_DBus_DocumentsPortalRetrieveFiles(بفر_2, &رستو_ڳڻپ);
                    // If dropped files contain a directory the list is empty
                    إذا (paths && رستو_ڳڻپ > 0) {
                        لكل (صحيح i = 0; i < رستو_ڳڻپ; i++) {
                            SDL_SendDropFile(drop->dnd_دري, عدم, paths[i]);
                        }
                        dbus->free_string_array(paths);
                        drop_handled = true;
                    }
                }
                SDL_free(بفر_2);
            }
        }
#جيڪڏهن_پورو
        /* If the XDG document portal fails, fall back to text/uri-list, if available.
         * When running inside of a flatpak sandbox, this will most likely be a list of
         * non-paths that are not visible to the application.
         */
        إذا (!drop_handled) {
            إذا (Wayland_معلومات_Offer_Has_MIME(offer, FILE_MIME)) {
                فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, FILE_MIME, &ڊيگهائي);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        إذا (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_دري, عدم, token);
                        }
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            } وإلا إذا (Wayland_معلومات_Offer_Has_MIME(offer, drop->متن_mime_type)) {
                فراغ *بفر_2 = Wayland_معلومات_Offer_Receive(offer, drop->متن_mime_type, &ڊيگهائي);
                إذا (بفر_2) {
                    حرف *saveptr = عدم;
                    حرف *token = SDL_strtok_r((حرف *)بفر_2, "\r\n", &saveptr);
                    طالما (token) {
                        SDL_Send_Drop_متن(drop->dnd_دري, token);
                        token = SDL_strtok_r(عدم, "\r\n", &saveptr);
                    }
                    SDL_free(بفر_2);
                    drop_handled = true;
                }
            }
        }

        إذا (drop_handled && wl_معلومات_offer_get_نسخو(offer->offer) >= WL_معلومات_OFFER_پڄاڻي_SINCE_نسخو) {
            wl_معلومات_offer_پڄاڻي(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_دري);
    }

    Wayland_معلومات_Offer_Destroy(drop->offer);
    drop->offer = عدم;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(معلومات_device->seat->display->display);
    wl_callback_جوڙيو_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

ساكن فراغ معلومات_device_handle_drop(فراغ *معلومات, بنية wl_معلومات_device *wl_معلومات_device)
{
    SDL_Wayland_معلومات_Device *معلومات_device = معلومات;

    إذا (معلومات_device->drag_offer && معلومات_device->dnd_دري &&
        (معلومات_device->has_mime_file || معلومات_device->متن_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((بنية wl_proxy *)معلومات_device->drag_offer->offer),
                     SDL_Get_دري_ID(معلومات_device->dnd_دري), معلومات_device->drag_serial);

        Wayland_ڪم_Thread_Context *ctx = معلومات_device->seat->display->ڪم_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_Drop_معلومات *drop = SDL_calloc(1, حجم(Wayland_Drop_معلومات));
        إذا (drop) {
            drop->offer = معلومات_device->drag_offer;
            drop->dnd_دري = معلومات_device->dnd_دري;
            drop->متن_mime_type = معلومات_device->متن_mime_type;

            WAYLAND_wl_list_وجهو(&معلومات_device->pending_drops, &drop->link);
            Wayland_ڪم_Thread_جوڙيو_ڪم(ctx, drop_dispatch_handler, drop, &drop->id);
        } وإلا {
            Wayland_معلومات_Offer_Destroy(معلومات_device->drag_offer);
        }
    } وإلا {
        SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
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

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));

    Wayland_معلومات_Device_سيٽ_Selection_Offer(معلومات_device, offer);
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
        zwp_primary_selection_offer_v1_سيٽ_user_معلومات(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_جوڙيو_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
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
    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((بنية wl_proxy *)id) : -1));
}

ساكن ثابت بنية zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

ساكن فراغ متن_داخلا_enter(فراغ *معلومات,
                             بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_داخلا_leave(فراغ *معلومات,
                             بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                             بنية wl_surface *surface)
{
    // No-op
}

ساكن فراغ متن_داخلا_preedit_string(فراغ *معلومات,
                                      بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                                      ثابت حرف *متن,
                                      int32_t cursor_begin,
                                      int32_t cursor_پڇاڙي)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    seat->متن_داخلا.has_preedit = true;
    إذا (متن) {
        صحيح cursor_begin_utf8 = cursor_begin >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_begin) : -1;
        صحيح cursor_پڇاڙي_utf8 = cursor_پڇاڙي >= 0 ? (صحيح)SDL_utf8strnlen(متن, cursor_پڇاڙي) : -1;
        صحيح cursor_سائيز_utf8;
        إذا (cursor_پڇاڙي_utf8 >= 0) {
            إذا (cursor_begin_utf8 >= 0) {
                cursor_سائيز_utf8 = cursor_پڇاڙي_utf8 - cursor_begin_utf8;
            } وإلا {
                cursor_سائيز_utf8 = cursor_پڇاڙي_utf8;
            }
        } وإلا {
            cursor_سائيز_utf8 = -1;
        }
        SDL_Send_Editing_متن(متن, cursor_begin_utf8, cursor_سائيز_utf8);
    } وإلا {
        SDL_Send_Editing_متن("", 0, 0);
    }
}

ساكن فراغ متن_داخلا_commit_string(فراغ *معلومات,
                                     بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                                     ثابت حرف *متن)
{
    SDL_Send_Keyboard_متن(متن);
}

ساكن فراغ متن_داخلا_delete_surrounding_متن(فراغ *معلومات,
                                               بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                                               uint32_t before_ڊيگهائي,
                                               uint32_t after_ڊيگهائي)
{
    // FIXME: Do we care about this event?
}

ساكن فراغ متن_داخلا_پورو(فراغ *معلومات,
                            بنية zwp_متن_داخلا_v3 *zwp_متن_داخلا_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)معلومات;
    إذا (!seat->متن_داخلا.has_preedit) {
        SDL_Send_Editing_متن("", 0, 0);
    }
    seat->متن_داخلا.has_preedit = false;
}

ساكن ثابت بنية zwp_متن_داخلا_v3_listener متن_داخلا_listener = {
    متن_داخلا_enter,
    متن_داخلا_leave,
    متن_داخلا_preedit_string,
    متن_داخلا_commit_string,
    متن_داخلا_delete_surrounding_متن,
    متن_داخلا_پورو
};

ساكن فراغ Wayland_معلومات_Device_سيٽ_ID(SDL_Wayland_معلومات_Device *معلومات_device)
{
    إذا (!معلومات_device->id_str)
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
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
#جيڪڏهن_پورو
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

    Wayland_معلومات_Device_سيٽ_ID(معلومات_device);
    WAYLAND_wl_list_init(&معلومات_device->pending_drops);
    wl_معلومات_device_سيٽ_user_معلومات(معلومات_device->معلومات_device, معلومات_device);
    wl_معلومات_device_جوڙيو_listener(معلومات_device->معلومات_device, &معلومات_device_listener, معلومات_device);
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
        zwp_primary_selection_device_v1_سيٽ_user_معلومات(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_جوڙيو_listener(primary_selection_device->primary_selection_device,
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

ساكن فراغ Wayland_Seat_Create_متن_داخلا(SDL_WaylandSeat *seat)
{
    إذا (seat->display->متن_داخلا_manager) {
        seat->متن_داخلا.zwp_متن_داخلا = zwp_متن_داخلا_manager_v3_get_متن_داخلا(seat->display->متن_داخلا_manager, seat->wl_seat);

        إذا (seat->متن_داخلا.zwp_متن_داخلا) {
            zwp_متن_داخلا_v3_سيٽ_user_معلومات(seat->متن_داخلا.zwp_متن_داخلا, seat);
            zwp_متن_داخلا_v3_جوڙيو_listener(seat->متن_داخلا.zwp_متن_داخلا,
                                           &متن_داخلا_listener, seat);
        }
    }
}

فراغ Wayland_Display_Init_متن_داخلا_Manager(SDL_Video_معلومات *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_Seat_Create_متن_داخلا(seat);
    }
}

// Pen/Tablet support...
ساكن فراغ tablet_tool_handle_type(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    بدل (type) {
        #وصف_ڪريو CASE(typ) حالة ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; أرجع
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #وصف_رد CASE
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
        #وصف_ڪريو CASE(wltyp,sdltyp) حالة ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; أرجع
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(مفاصلو_2, SDL_PEN_CAPABILITY_مفاصلو);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #وصف_رد CASE
        افتراضي: اكسر;  // unsupported here.
    }
}

ساكن فراغ tablet_tool_handle_پورو(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    إذا (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_دري *دري = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        sdltool->instance_id = SDL_جوڙيو_Pen_Device(0, عدم, دري, &sdltool->info, sdltool, false);
    }
}

ساكن فراغ tablet_tool_handle_removed(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    إذا (sdltool->instance_id) {
        SDL_دري *دري = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
        SDL_RemovePenDevice(0, دري, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

ساكن فراغ tablet_tool_handle_proximity_اندريون(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial, بنية zwp_tablet_v2 *tablet, بنية wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    SDL_دري_معلومات *windowdata = surface ? Wayland_Get_دري_معلومات_For_Owned_Surface(surface) : عدم;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : عدم;
    sdltool->proximity_serial = serial;
    sdltool->چوکٺو.have_proximity = true;
    sdltool->چوکٺو.اندريون_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

ساكن فراغ tablet_tool_handle_proximity_ٻاهريون(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.have_proximity = true;
    sdltool->چوکٺو.اندريون_proximity = false;
}

ساكن فراغ tablet_tool_handle_هيٺ_ڏانهن(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.tool_state = WAYLAND_TABLET_TOOL_STATE_هيٺ_ڏانهن;
}

ساكن فراغ tablet_tool_handle_مٿي(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.tool_state = WAYLAND_TABLET_TOOL_STATE_مٿي;
}

ساكن فراغ tablet_tool_handle_motion(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    SDL_دري_معلومات *windowdata = sdltool->focus;
    إذا (windowdata) {
        sdltool->چوکٺو.x = (عائم)(wl_fixed_منزل_double(sx_w) * windowdata->اشارو_scale.x);
        sdltool->چوکٺو.y = (عائم)(wl_fixed_منزل_double(sy_w) * windowdata->اشارو_scale.y);
        sdltool->چوکٺو.have_motion = true;
    }
}

ساكن فراغ tablet_tool_handle_pressure(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_PRESSURE] = ((عائم) pressure) / 65535.0f;
    sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_PRESSURE);
    إذا (pressure) {
        sdltool->چوکٺو.axes[SDL_PEN_AXIS_مفاصلو] = 0.0f;
        sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_مفاصلو);
    }
}

ساكن فراغ tablet_tool_handle_مفاصلو(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t مفاصلو)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_مفاصلو] = ((عائم) مفاصلو) / 65535.0f;
    sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_مفاصلو);
    إذا (مفاصلو) {
        sdltool->چوکٺو.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

ساكن فراغ tablet_tool_handle_tilt(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_XTILT] = (عائم)(wl_fixed_منزل_double(xtilt));
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_YTILT] = (عائم)(wl_fixed_منزل_double(ytilt));
    sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
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

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->چوکٺو.buttons)));
    sdltool->چوکٺو.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_هيٺ_ڏانهن : WAYLAND_TABLET_TOOL_BUTTON_مٿي;
}

ساكن فراغ tablet_tool_handle_rotation(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    ثابت عائم rotation = (عائم)(wl_fixed_منزل_double(degrees));
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_ROTATION);
}

ساكن فراغ tablet_tool_handle_slider(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    sdltool->چوکٺو.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->چوکٺو.axes_سيٽ |= (1u << SDL_PEN_AXIS_SLIDER);
}

ساكن فراغ tablet_tool_handle_wheel(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

ساكن فراغ tablet_tool_handle_چوکٺو(فراغ *معلومات, بنية zwp_tablet_tool_v2 *tool, uint32_t وقت)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) معلومات;
    ثابت SDL_PenID instance_id = sdltool->instance_id;
    إذا (!instance_id) {
        أرجع;  // Not a pen we report on.
    }

    ثابت Uint64 timestamp = Wayland_Adjust_Event_Timestamp_بنياد(Wayland_EventTimestampMSToNS(وقت));
    SDL_دري *دري = sdltool->focus ? sdltool->focus->sdlwindow : عدم;
    ثابت bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    إذا (sdltool->چوکٺو.have_proximity && sdltool->چوکٺو.اندريون_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, دري, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    إذا (sdltool->چوکٺو.have_motion && sdltool->چوکٺو.tool_state) {
        إذا (sdltool->چوکٺو.tool_state == WAYLAND_TABLET_TOOL_STATE_هيٺ_ڏانهن) {
            SDL_SendPenMotion(timestamp, instance_id, دري, sdltool->چوکٺو.x, sdltool->چوکٺو.y);
            SDL_SendPenTouch(timestamp, instance_id, دري, is_eraser, true);
        } وإلا {
            SDL_SendPenTouch(timestamp, instance_id, دري, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, دري, sdltool->چوکٺو.x, sdltool->چوکٺو.y);
        }
    } وإلا {
        إذا (sdltool->چوکٺو.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, دري, is_eraser, sdltool->چوکٺو.tool_state == WAYLAND_TABLET_TOOL_STATE_هيٺ_ڏانهن);
        }

        إذا (sdltool->چوکٺو.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, دري, sdltool->چوکٺو.x, sdltool->چوکٺو.y);
        }
    }

    لكل (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_ڳڻپ; i++) {
        إذا (sdltool->چوکٺو.axes_سيٽ & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, دري, i, sdltool->چوکٺو.axes[i]);
        }
    }

    لكل (صحيح i = 0; i < SDL_arraysize(sdltool->چوکٺو.buttons); i++) {
        ثابت صحيح state = sdltool->چوکٺو.buttons[i];
        إذا (state) {
            SDL_SendPenButton(timestamp, instance_id, دري, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_هيٺ_ڏانهن);
        }
    }

    إذا (sdltool->چوکٺو.have_proximity && !sdltool->چوکٺو.اندريون_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, دري, false, false);
        sdltool->focus = عدم;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->چوکٺو);
}

ساكن ثابت بنية zwp_tablet_tool_v2_listener tablet_tool_listener = {
    tablet_tool_handle_type,
    tablet_tool_handle_hardware_serial,
    tablet_tool_handle_hardware_id_wacom,
    tablet_tool_handle_capability,
    tablet_tool_handle_پورو,
    tablet_tool_handle_removed,
    tablet_tool_handle_proximity_اندريون,
    tablet_tool_handle_proximity_ٻاهريون,
    tablet_tool_handle_هيٺ_ڏانهن,
    tablet_tool_handle_مٿي,
    tablet_tool_handle_motion,
    tablet_tool_handle_pressure,
    tablet_tool_handle_مفاصلو,
    tablet_tool_handle_tilt,
    tablet_tool_handle_rotation,
    tablet_tool_handle_slider,
    tablet_tool_handle_wheel,
    tablet_tool_handle_button,
    tablet_tool_handle_چوکٺو
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
        sdltool->info.انگ_buttons = -1;

        إذا (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_وجهو(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_جوڙيو_listener(tool, &tablet_tool_listener, sdltool);
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
    zwp_tablet_seat_v2_جوڙيو_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
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

ساكن فراغ Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_هيٺ_ڏانهن)
{
    إذا (!shutting_هيٺ_ڏانهن) {
        SDL_WaylandPenTool *tool, *عارضي;
        wl_list_for_each_محفوظ (tool, عارضي, &seat->tablet.tool_list, link) {
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
    WAYLAND_wl_list_وجهو(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_Seat_Create_معلومات_Device(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_Seat_Create_متن_داخلا(seat);

    wl_seat_سيٽ_user_معلومات(seat->wl_seat, seat);
    wl_seat_جوڙيو_listener(seat->wl_seat, &seat_listener, seat);

    إذا (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

فراغ Wayland_Display_Remove_دري_References_From_Seats(SDL_Video_معلومات *display, SDL_دري_معلومات *دري)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        إذا (seat->keyboard.focus == دري) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, دري->surface);
        }

        إذا (seat->اشارو_2.focus == دري) {
            seat->اشارو_2.pending_چوکٺو.leave_surface = seat->اشارو_2.focus->surface;
            اشارو_dispatch_leave(seat, true);
            seat->اشارو_2.pending_چوکٺو.leave_surface = عدم;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_Wayland_Touch_نقطو *tp, *عارضي;
        wl_list_for_each_محفوظ (tp, عارضي, &seat->touch.points, link) {
            إذا (tp->surface == دري->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == دري) {
                tool->focus = عدم;
                Wayland_TabletToolUpdateCursor(tool);
                إذا (tool->instance_id) {
                    SDL_RemovePenDevice(0, دري->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_Drop_معلومات *drop, *drop_عارضي;
        wl_list_for_each_محفوظ (drop, drop_عارضي, &seat->معلومات_device->pending_drops, link) {
            إذا (drop->dnd_دري == دري->sdlwindow) {
                Wayland_ڪم_Thread_Cancel_ڪم(display->ڪم_thread_context, drop->id);

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

فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_هيٺ_ڏانهن)
{
    إذا (!seat) {
        أرجع;
    }

    SDL_free(seat->name);

    إذا (seat->معلومات_device) {
        إذا (seat->معلومات_device->selection_offer) {
            Wayland_معلومات_Offer_Destroy(seat->معلومات_device->selection_offer);
        }
        إذا (seat->معلومات_device->selection_ذريعو) {
            Wayland_معلومات_ذريعو_Destroy(seat->معلومات_device->selection_ذريعو);
        }
        إذا (seat->معلومات_device->drag_offer) {
            Wayland_معلومات_Offer_Destroy(seat->معلومات_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_Drop_معلومات *drop, *drop_عارضي;
        wl_list_for_each_محفوظ (drop, drop_عارضي, &seat->معلومات_device->pending_drops, link) {
            Wayland_ڪم_Thread_Cancel_ڪم(seat->display->ڪم_thread_context, drop->id);

            إذا (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_معلومات_Offer_Destroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        إذا (seat->معلومات_device->معلومات_device) {
            إذا (wl_معلومات_device_get_نسخو(seat->معلومات_device->معلومات_device) >= WL_معلومات_DEVICE_RELEASE_SINCE_نسخو) {
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
        إذا (seat->primary_selection_device->selection_ذريعو) {
            Wayland_Primary_Selection_ذريعو_Destroy(seat->primary_selection_device->selection_ذريعو);
        }
        إذا (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    إذا (seat->متن_داخلا.zwp_متن_داخلا) {
        zwp_متن_داخلا_v3_destroy(seat->متن_داخلا.zwp_متن_داخلا);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_Seat_Destroy_اشارو(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_هيٺ_ڏانهن);

    إذا (wl_seat_get_نسخو(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_نسخو) {
        wl_seat_release(seat->wl_seat);
    } وإلا {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

ساكن فراغ Wayland_Seat_Update_Relative_اشارو(SDL_WaylandSeat *seat)
{
    إذا (seat->display->relative_اشارو_manager) {
        bool relative_focus = false;

        إذا (seat->اشارو_2.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            إذا (seat->اشارو_2.focus->sdlwindow->flags & SDL_دري_MOUSE_RELATIVE_گهڻائي) {
                إذا (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->اشارو_2.focus;
                } وإلا {
                    relative_focus = seat->اشارو_2.focus->keyboard_focus_ڳڻپ != 0;
                }
            } وإلا {
                relative_focus = SDL_GetMouse()->warp_emulation_سرگرم;
            }
        }

        إذا (relative_focus) {
            إذا (!seat->اشارو_2.relative_اشارو) {
                seat->اشارو_2.relative_اشارو = zwp_relative_اشارو_manager_v1_get_relative_اشارو(seat->display->relative_اشارو_manager, seat->اشارو_2.wl_اشارو);
                zwp_relative_اشارو_v1_جوڙيو_listener(seat->اشارو_2.relative_اشارو, &relative_اشارو_listener, seat);
            }
        } وإلا إذا (seat->اشارو_2.relative_اشارو) {
            zwp_relative_اشارو_v1_destroy(seat->اشارو_2.relative_اشارو);
            seat->اشارو_2.relative_اشارو = عدم;
        }
    }
}

ساكن فراغ Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_Video_معلومات *display = seat->display;

    إذا (display->ڪنجي_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        إذا (seat->keyboard.ڪنجي_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.ڪنجي_inhibitor);
            seat->keyboard.ڪنجي_inhibitor = عدم;
        }

        إذا (seat->keyboard.wl_keyboard) {
            SDL_دري_معلومات *w = seat->keyboard.focus;
            إذا (w) {
                SDL_دري *دري = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                إذا (دري->flags & SDL_دري_KEYBOARD_GRABBED) {
                    seat->keyboard.ڪنجي_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->ڪنجي_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

فراغ Wayland_Seat_Update_اشارو_Grab(SDL_WaylandSeat *seat)
{
    SDL_Video_معلومات *display = seat->display;
    Wayland_Seat_Update_Relative_اشارو(seat);

    إذا (display->اشارو_constraints) {
        إذا (seat->اشارو_2.locked_اشارو && !seat->اشارو_2.relative_اشارو) {
            zwp_locked_اشارو_v1_destroy(seat->اشارو_2.locked_اشارو);
            seat->اشارو_2.locked_اشارو = عدم;

            // Update the cursor after destroying a relative move lock.
            Wayland_Seat_Update_اشارو_Cursor(seat);
        }

        إذا (seat->اشارو_2.wl_اشارو) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            إذا (seat->اشارو_2.relative_اشارو) {
                إذا (!seat->اشارو_2.locked_اشارو) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    إذا (seat->اشارو_2.confined_اشارو) {
                        zwp_confined_اشارو_v1_destroy(seat->اشارو_2.confined_اشارو);
                        seat->اشارو_2.confined_اشارو = عدم;
                    }

                    seat->اشارو_2.locked_اشارو = zwp_اشارو_constraints_v1_تالو_اشارو(display->اشارو_constraints,
                                                                                           seat->اشارو_2.focus->surface,
                                                                                           seat->اشارو_2.wl_اشارو, عدم,
                                                                                           ZWP_اشارو_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارو_v1_جوڙيو_listener(seat->اشارو_2.locked_اشارو, &locked_اشارو_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_Seat_Update_اشارو_Cursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                أرجع;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            إذا (seat->اشارو_2.confined_اشارو) {
                zwp_confined_اشارو_v1_destroy(seat->اشارو_2.confined_اشارو);
                seat->اشارو_2.confined_اشارو = عدم;
            }

            SDL_دري_معلومات *w = seat->اشارو_2.focus;
            إذا (!w) {
                أرجع;
            }

            SDL_دري *دري = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            إذا (!(دري->flags & SDL_دري_داخلا_FOCUS) ||
                (!(دري->flags & SDL_دري_MOUSE_GRABBED) && SDL_Rect_خالي_جايون(&دري->mouse_rect))) {
                أرجع;
            }

            بنية wl_region *confine_rect = عدم;
            إذا (!SDL_Rect_خالي_جايون(&دري->mouse_rect)) {
                SDL_Rect scaled_mouse_rect;
                Wayland_GetScaledMouseRect(دري, &scaled_mouse_rect);

                confine_rect = wl_compositor_create_region(display->compositor);
                wl_region_جوڙيو(confine_rect,
                              scaled_mouse_rect.x,
                              scaled_mouse_rect.y,
                              scaled_mouse_rect.w,
                              scaled_mouse_rect.h);

                /* Some compositors will only confine the pointer to an arbitrary region if the pointer
                 * is already within the confinement area when it is created. Warp the pointer to the
                 * closest point within the confinement zone if outside.
                 */
                إذا (!SDL_نقطو_اندريون_Rect(&seat->اشارو_2.آخري_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    صحيح closest_x = seat->اشارو_2.آخري_motion.x;
                    صحيح closest_y = seat->اشارو_2.آخري_motion.y;

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

            إذا (confine_rect || (دري->flags & SDL_دري_MOUSE_GRABBED)) {
                إذا (دري->mouse_rect.w != 1 && دري->mouse_rect.h != 1) {
                    seat->اشارو_2.confined_اشارو =
                        zwp_اشارو_constraints_v1_confine_اشارو(display->اشارو_constraints,
                                                                   w->surface,
                                                                   seat->اشارو_2.wl_اشارو,
                                                                   confine_rect,
                                                                   ZWP_اشارو_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_اشارو_v1_جوڙيو_listener(seat->اشارو_2.confined_اشارو,
                                                         &confined_اشارو_listener,
                                                         seat);
                } وإلا {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->اشارو_2.locked_اشارو =
                        zwp_اشارو_constraints_v1_تالو_اشارو(display->اشارو_constraints,
                                                                w->surface,
                                                                seat->اشارو_2.wl_اشارو,
                                                                عدم,
                                                                ZWP_اشارو_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_اشارو_v1_جوڙيو_listener(seat->اشارو_2.locked_اشارو,
                                                       &locked_اشارو_listener,
                                                       seat);
                }
                إذا (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

فراغ Wayland_Display_Update_اشارو_Grabs(SDL_Video_معلومات *display, SDL_دري_معلومات *دري)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!دري || seat->اشارو_2.focus == دري) {
            Wayland_Seat_Update_اشارو_Grab(seat);
        }
    }
}

فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_معلومات *display, SDL_دري_معلومات *دري)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        إذا (!دري || seat->keyboard.focus == دري) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    إذا (serial > seat->آخري_implicit_grab_serial) {
        seat->آخري_implicit_grab_serial = serial;
        seat->display->آخري_implicit_grab_seat = seat;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND
