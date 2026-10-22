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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#include "../../core/unix/SDL_poll.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_scancode_tables_c.h"
#include "../../events/SDL_keysym_to_keycode_c.h"
#include "../../core/linux/SDL_system_theme.h"
#include "../SDL_sysvideo.h"

#include "SDL_waylandvideo.h"
#include "SDL_waylandevents_c.h"
#include "SDL_waylandwindow.h"
#include "SDL_waylandmouse.h"
#include "SDL_waylandclipboard.h"
#include "SDL_waylandkeyboard.h"

#include "pointer-constraints-unstable-v1-client-protocol.h"
#include "relative-pointer-unstable-v1-client-protocol.h"
#include "xdg-shell-client-protocol.h"
#include "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#include "text-input-unstable-v3-client-protocol.h"
#include "tablet-v2-client-protocol.h"
#include "primary-selection-unstable-v1-client-protocol.h"
#include "input-timestamps-unstable-v1-client-protocol.h"
#include "pointer-gestures-unstable-v1-client-protocol.h"
#include "cursor-shape-v1-client-protocol.h"
#include "viewporter-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#include <libdecor.h>
#endif

// Per the spec, Wayland mouse and stylus buttons are defined as Linux event codes.
#ifdef SDL_INPUT_LINUXEV
#include <linux/input.h>
#ᬮᬶᬬ
#define BTN_LEFT    (0x110)
#define BTN_RIGHT   (0x111)
#define BTN_MIDDLE  (0x112)
#define BTN_SIDE    (0x113)
#define BTN_EXTRA   (0x114)
#define BTN_STYLUS  (0x14b)
#define BTN_STYLUS2 (0x14c)
#define BTN_STYLUS3 (0x149)
#endif
#include "../../events/SDL_keysym_to_scancode_c.h"
#include "../../events/imKStoUCS.h"
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <xkbcommon/xkbcommon-compose.h>
#include <xkbcommon/xkbcommon.h>

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
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_LOW  (SDL_MAX_UINT32 / 16U)
#define WAYLAND_TIMER_ROLLOVER_INTERVAL_HIGH (WAYLAND_TIMER_ROLLOVER_INTERVAL_LOW * 15U)

// Scoped function declarations
static void Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat);

typedef sa_nracanaa
{
    Uint32 key;
    SDL_Scancode scancode;
} Wayland_ReservedKey;

typedef sa_nracanaa
{
    SDL_TouchID id;
    wl_fixed_t fx;
    wl_fixed_t fy;
    sa_nracanaa wl_surface *surface;

    sa_nracanaa wl_list link;
} SDL_WaylandTouchPoint;

static void Wayland_SeatAddTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, sa_nracanaa wl_surface *surface)
{
    SDL_WaylandTouchPoint *tp = SDL_malloc(parimaa_na(SDL_WaylandTouchPoint));

    SDL_zerop(tp);
    tp->id = id;
    tp->fx = fx;
    tp->fy = fy;
    tp->surface = surface;

    WAYLAND_wl_list_insert(&seat->touch.points, &tp->link);
}

static void Wayland_SeatCancelTouch(SDL_WaylandSeat *seat, SDL_WaylandTouchPoint *tp)
{
    ᬬᬾᬦ᭄ (tp->surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(tp->surface);

        ᬬᬾᬦ᭄ (window_data) {
            const float x = (float)(wl_fixed_to_double(tp->fx) / window_data->current.logical_width);
            const float y = (float)(wl_fixed_to_double(tp->fy) / window_data->current.logical_height);

            SDL_SendTouch(0, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch,
                          (SDL_FingerID)(tp->id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_CANCELED, x, y, 0.0f);

            --window_data->active_touch_count;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ᬬᬾᬦ᭄ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_count &&
                !window_data->pointer_focus_count && !window_data->active_touch_count) {
                SDL_SetMouseFocus(NULL);
            }
        }
    }

    WAYLAND_wl_list_remove(&tp->link);
    SDL_free(tp);
}

static void Wayland_SeatUpdateTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t fx, wl_fixed_t fy, sa_nracanaa wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ᬬᬾᬦ᭄ (tp->id == id) {
            tp->fx = fx;
            tp->fy = fy;
            ᬬᬾᬦ᭄ (surface) {
                *surface = tp->surface;
            }
            bha_nga;
        }
    }
}

static void Wayland_SeatRemoveTouch(SDL_WaylandSeat *seat, SDL_TouchID id, wl_fixed_t *fx, wl_fixed_t *fy, sa_nracanaa wl_surface **surface)
{
    SDL_WaylandTouchPoint *tp;

    wl_list_for_each (tp, &seat->touch.points, link) {
        ᬬᬾᬦ᭄ (tp->id == id) {
            ᬬᬾᬦ᭄ (fx) {
                *fx = tp->fx;
            }
            ᬬᬾᬦ᭄ (fy) {
                *fy = tp->fy;
            }
            ᬬᬾᬦ᭄ (surface) {
                *surface = tp->surface;
            }

            WAYLAND_wl_list_remove(&tp->link);
            SDL_free(tp);
            bha_nga;
        }
    }
}

static void Wayland_GetScaledMouseRect(SDL_Window *window, SDL_Rect *scaled_rect)
{
    SDL_WindowData *window_data = window->internal;

    scaled_rect->x = (puur_naa_nka)SDL_floor(window->mouse_rect.x / window_data->pointer_scale.x);
    scaled_rect->y = (puur_naa_nka)SDL_floor(window->mouse_rect.y / window_data->pointer_scale.y);
    scaled_rect->w = (puur_naa_nka)SDL_ceil(window->mouse_rect.w / window_data->pointer_scale.x);
    scaled_rect->h = (puur_naa_nka)SDL_ceil(window->mouse_rect.h / window_data->pointer_scale.y);
}

static Uint64 Wayland_AdjustEventTimestampBase(Uint64 nsTimestamp)
{
    static Uint64 timestamp_offset = 0;
    const Uint64 now = SDL_GetTicksNS();

    ᬬᬾᬦ᭄ (!timestamp_offset) {
        timestamp_offset = (now - nsTimestamp);
    }
    nsTimestamp += timestamp_offset;

    ᬬᬾᬦ᭄ (nsTimestamp > now) {
        timestamp_offset -= (nsTimestamp - now);
        nsTimestamp = now;
    }

    ᬯᬮᬶ nsTimestamp;
}

/* This should only be called with 32-bit millisecond timestamps received in Wayland events!
 * No synthetic or high-res timestamps, as they can corrupt the rollover offset!
 */
static Uint64 Wayland_EventTimestampMSToNS(Uint32 wl_timestamp_ms)
{
    static Uint64 timestamp_offset = 0;
    static Uint32 last = 0;
    Uint64 timestamp = SDL_MS_TO_NS(wl_timestamp_ms) + timestamp_offset;

    ᬬᬾᬦ᭄ (wl_timestamp_ms >= last) {
        ᬬᬾᬦ᭄ (timestamp_offset && last < WAYLAND_TIMER_ROLLOVER_INTERVAL_LOW && wl_timestamp_ms > WAYLAND_TIMER_ROLLOVER_INTERVAL_HIGH) {
            // A time that crossed backwards across zero was received. Subtract the increased time base offset.
            timestamp -= SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
        } ᬮᬶᬬ {
            last = wl_timestamp_ms;
        }
    } ᬮᬶᬬ {
        /* Only increment the base time offset if the timer actually crossed forward across 0,
         * and not if this is just a timestamp from a slightly older event.
         */
        ᬬᬾᬦ᭄ (wl_timestamp_ms < WAYLAND_TIMER_ROLLOVER_INTERVAL_LOW && last > WAYLAND_TIMER_ROLLOVER_INTERVAL_HIGH) {
            timestamp_offset += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            timestamp += SDL_MS_TO_NS(SDL_UINT64_C(0x100000000));
            last = wl_timestamp_ms;
        }
    }

    ᬯᬮᬶ timestamp;
}

/* Even if high-res timestamps are available, the millisecond timestamps are still processed
 * to accumulate the rollover offset if needed later.
 */

static Uint64 Wayland_GetKeyboardTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    const Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ᬯᬮᬶ Wayland_AdjustEventTimestampBase(seat->keyboard.timestamps ? seat->keyboard.highres_timestamp_ns : adjustedTimestampNS);
}

static Uint64 Wayland_GetPointerTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    const Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ᬯᬮᬶ Wayland_AdjustEventTimestampBase(seat->pointer.timestamps ? seat->pointer.highres_timestamp_ns : adjustedTimestampNS);
}

Uint64 Wayland_GetTouchTimestamp(SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms)
{
    const Uint64 adjustedTimestampNS = Wayland_EventTimestampMSToNS(wl_timestamp_ms);
    ᬯᬮᬶ Wayland_AdjustEventTimestampBase(seat->touch.timestamps ? seat->touch.highres_timestamp_ns : adjustedTimestampNS);
}

static void input_timestamp_listener(void *data, sa_nracanaa zwp_input_timestamps_v1 *zwp_input_timestamps_v1,
                                             uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    *((Uint64 *)data) = ((((Uint64)tv_sec_hi << 32) | (Uint64)tv_sec_lo) * SDL_NS_PER_SECOND) + tv_nsec;
}

static const sa_nracanaa zwp_input_timestamps_v1_listener timestamp_listener = {
    input_timestamp_listener
};

static void Wayland_SeatRegisterInputTimestampListeners(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (seat->display->input_timestamps_manager) {
        ᬬᬾᬦ᭄ (seat->keyboard.wl_keyboard && !seat->keyboard.timestamps) {
            seat->keyboard.timestamps = zwp_input_timestamps_manager_v1_get_keyboard_timestamps(seat->display->input_timestamps_manager, seat->keyboard.wl_keyboard);
            zwp_input_timestamps_v1_add_listener(seat->keyboard.timestamps, &timestamp_listener, &seat->keyboard.highres_timestamp_ns);
        }

        ᬬᬾᬦ᭄ (seat->pointer.wl_pointer && !seat->pointer.timestamps) {
            seat->pointer.timestamps = zwp_input_timestamps_manager_v1_get_pointer_timestamps(seat->display->input_timestamps_manager, seat->pointer.wl_pointer);
            zwp_input_timestamps_v1_add_listener(seat->pointer.timestamps, &timestamp_listener, &seat->pointer.highres_timestamp_ns);
        }

        ᬬᬾᬦ᭄ (seat->touch.wl_touch && !seat->touch.timestamps) {
            seat->touch.timestamps = zwp_input_timestamps_manager_v1_get_touch_timestamps(seat->display->input_timestamps_manager, seat->touch.wl_touch);
            zwp_input_timestamps_v1_add_listener(seat->touch.timestamps, &timestamp_listener, &seat->touch.highres_timestamp_ns);
        }
    }
}

void Wayland_DisplayInitInputTimestampManager(SDL_VideoData *display)
{
    ᬬᬾᬦ᭄ (display->input_timestamps_manager) {
        SDL_WaylandSeat *seat;
        wl_list_for_each (seat, &display->seat_list, link) {
            Wayland_SeatRegisterInputTimestampListeners(seat);
        }
    }
}

static void handle_pinch_begin(void *data, sa_nracanaa zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, sa_nracanaa wl_surface *surface, uint32_t fingers)
{
    ᬬᬾᬦ᭄ (!surface) {
        ᬯᬮᬶ;
    }

    SDL_WindowData *wind = Wayland_GetWindowDataForOwnedSurface(surface);
    ᬬᬾᬦ᭄ (wind) {
        SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
        seat->pointer.gesture_focus = wind;

        const Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_BEGIN, timestamp, wind->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

static void handle_pinch_update(void *data, sa_nracanaa zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t time,
                                wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t scale, wl_fixed_t rotation)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ᬬᬾᬦ᭄ (seat->pointer.gesture_focus) {
        const Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        const float s = (float)wl_fixed_to_double(scale);
        SDL_SendPinch(SDL_EVENT_PINCH_UPDATE, timestamp, seat->pointer.gesture_focus->sdlwindow, s, -1.0f, -1.0f, -1.0f, -1.0f);
    }
}

static void handle_pinch_end(void *data, sa_nracanaa zwp_pointer_gesture_pinch_v1 *zwp_pointer_gesture_pinch_v1, uint32_t serial, uint32_t time, int32_t cancelled)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ᬬᬾᬦ᭄ (seat->pointer.gesture_focus) {
        const Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);
        SDL_SendPinch(SDL_EVENT_PINCH_END, timestamp, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);

        seat->pointer.gesture_focus = NULL;
    }
}

static const sa_nracanaa zwp_pointer_gesture_pinch_v1_listener gesture_pinch_listener = {
    handle_pinch_begin,
    handle_pinch_update,
    handle_pinch_end
};

static void Wayland_SeatCreatePointerGestures(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (seat->display->zwp_pointer_gestures) {
        ᬬᬾᬦ᭄ (seat->pointer.wl_pointer && !seat->pointer.gesture_pinch) {
            seat->pointer.gesture_pinch = zwp_pointer_gestures_v1_get_pinch_gesture(seat->display->zwp_pointer_gestures, seat->pointer.wl_pointer);
            zwp_pointer_gesture_pinch_v1_set_user_data(seat->pointer.gesture_pinch, seat);
            zwp_pointer_gesture_pinch_v1_add_listener(seat->pointer.gesture_pinch, &gesture_pinch_listener, seat);
        }
    }
}

void Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePointerGestures(seat);
    }
}

static void Wayland_SeatCreateCursorShape(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (seat->display->cursor_shape_manager) {
        ᬬᬾᬦ᭄ (seat->pointer.wl_pointer && !seat->pointer.cursor_state.cursor_shape) {
            seat->pointer.cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_pointer(seat->display->cursor_shape_manager, seat->pointer.wl_pointer);
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            ᬬᬾᬦ᭄ (!tool->cursor_state.cursor_shape) {
                tool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool->wltool);
            }
        }
    }
}

void Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateCursorShape(seat);
    }
}

static void Wayland_SeatSetKeymap(SDL_WaylandSeat *seat)
{
    const bool send_event = !seat->display->initializing;

    ᬬᬾᬦ᭄ (seat->keyboard.sdl_keymap &&
        seat->keyboard.xkb.current_layout < seat->keyboard.xkb.num_layouts &&
        seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] != SDL_GetCurrentKeymap(true)) {
        SDL_SetKeymap(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], send_event);
        SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
    }
}

// Synthesize key repeat events
static void keyboard_repeat_handle(SDL_WaylandKeyboardRepeat *repeat_info, Uint64 elapsed)
{
    ᬲᭂᬤᭂᬮ (elapsed >= repeat_info->next_repeat_ns) {
        ᬬᬾᬦ᭄ (repeat_info->scancode != SDL_SCANCODE_UNKNOWN) {
            const Uint64 timestamp = repeat_info->base_time_ns + repeat_info->next_repeat_ns;
            SDL_SendKeyboardKeyIgnoreModifiers(Wayland_AdjustEventTimestampBase(timestamp), repeat_info->keyboard_id, repeat_info->key, repeat_info->scancode, true);
        }
        ᬬᬾᬦ᭄ (repeat_info->text[0] && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(repeat_info->text);
        }
        repeat_info->next_repeat_ns += SDL_NS_PER_SECOND / (Uint64)repeat_info->repeat_rate;
    }
}

static void keyboard_repeat_set(SDL_WaylandKeyboardRepeat *repeat_info, Uint32 keyboard_id, uint32_t key, Uint32 wl_press_time_ms,
                                Uint64 base_time_ns, uint32_t scancode, const var_na *text)
{
    ᬬᬾᬦ᭄ (!repeat_info->repeat_rate) {
        ᬯᬮᬶ;
    }
    repeat_info->keyboard_id = keyboard_id;
    repeat_info->key = key;
    repeat_info->wl_press_time_ms = wl_press_time_ms;
    repeat_info->base_time_ns = base_time_ns;
    repeat_info->sdl_press_time_ns = SDL_GetTicksNS();
    repeat_info->next_repeat_ns = SDL_MS_TO_NS(repeat_info->repeat_delay_ms);
    repeat_info->scancode = scancode;
    ᬬᬾᬦ᭄ (text) {
        SDL_strlcpy(repeat_info->text, text, SDL_arraysize(repeat_info->text));
    } ᬮᬶᬬ {
        repeat_info->text[0] = '\0';
    }
}

static void sync_done_handler(void *data, sa_nracanaa wl_callback *callback, uint32_t callback_data)
{
    // Nothing to do, just destroy the callback
    wl_callback_destroy(callback);
}

static sa_nracanaa wl_callback_listener sync_listener = {
    sync_done_handler
};

void Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *d = _this->internal;

    // Queue a sync event to unblock the main event queue if it's being waited on.
    sa_nracanaa wl_callback *cb = wl_display_sync(d->display);
    wl_callback_add_listener(cb, &sync_listener, NULL);
    WAYLAND_wl_display_flush(d->display);
}

puur_naa_nka Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    Uint64 start = SDL_GetTicksNS();
    const puur_naa_nka display_fd = WAYLAND_wl_display_get_fd(d->display);
    puur_naa_nka ret;
    bool poll_alarm_set = false;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ᬬᬾᬦ᭄ (!d->text_input_manager && keyboard_focus && SDL_TextInputActive(keyboard_focus)) {
        // If a DBus IME is active with no text input protocol, periodically wake to poll it.
        ᬬᬾᬦ᭄ (timeoutNS < 0 || SDL_MS_TO_NS(200) <= timeoutNS) {
            timeoutNS = SDL_MS_TO_NS(200);
            poll_alarm_set = true;
        }
    }
#endif

    // If key repeat is active, we'll need to cap our maximum wait time to handle repeats
    wl_list_for_each (seat, &d->seat_list, link) {
        ᬬᬾᬦ᭄ (seat->keyboard.repeat.key) {
            const Uint64 elapsed = start - seat->keyboard.repeat.sdl_press_time_ns;
            const Uint64 next_repeat_wait_time = (seat->keyboard.repeat.next_repeat_ns - elapsed) + 1;
            ᬬᬾᬦ᭄ (timeoutNS < 0 || next_repeat_wait_time <= timeoutNS) {
                timeoutNS = next_repeat_wait_time;
                poll_alarm_set = true;
            }
        }
    }

    ᬬᬾᬦ᭄ (WAYLAND_wl_display_prepare_read(d->display) == 0) {
        ᬬᬾᬦ᭄ (timeoutNS > 0) {
            const Uint64 now = SDL_GetTicksNS();
            const Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        ret = WAYLAND_wl_display_flush(d->display);

        ᬬᬾᬦ᭄ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; poll until the socket can be written to, it times out, or is interrupted.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE | SDL_IOR_NO_RETRY, timeoutNS);

            ᬬᬾᬦ᭄ (ret <= 0) {
                // The poll operation timed out or experienced an error, so see if there are any events to read without waiting.
                timeoutNS = 0;
            }
        }

        ᬬᬾᬦ᭄ (ret < 0) {
            // Pump events on an interrupt or broken pipe to handle the error.
            WAYLAND_wl_display_cancel_read(d->display);
            ᬯᬮᬶ errno == EINTR || errno == EPIPE ? 1 : ret;
        }

        ᬬᬾᬦ᭄ (timeoutNS > 0) {
            const Uint64 now = SDL_GetTicksNS();
            const Uint64 elapsed = now - start;
            start = now;
            timeoutNS = elapsed <= timeoutNS ? timeoutNS - elapsed : 0;
        }

        // Use SDL_IOR_NO_RETRY to catch EINTR.
        ret = SDL_IOReady(display_fd, SDL_IOR_READ | SDL_IOR_NO_RETRY, timeoutNS);
        ᬬᬾᬦ᭄ (ret <= 0) {
            // Timeout or error, cancel the read.
            WAYLAND_wl_display_cancel_read(d->display);

            // The poll timed out with no data to read, but signal the caller to pump events if polling is required.
            ᬬᬾᬦ᭄ (ret == 0) {
                ᬯᬮᬶ poll_alarm_set ? 1 : 0;
            } ᬮᬶᬬ {
                // Pump events on an interrupt or broken pipe to handle the error.
                ᬯᬮᬶ errno == EINTR || errno == EPIPE ? 1 : ret;
            }
        }

        ret = WAYLAND_wl_display_read_events(d->display);
        ᬬᬾᬦ᭄ (ret == -1) {
            ᬯᬮᬶ ret;
        }
    }

    // Signal to the caller that there might be an event available.
    ᬯᬮᬶ 1;
}

void Wayland_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_VideoData *d = _this->internal;
    SDL_WaylandSeat *seat;
    const puur_naa_nka display_fd = WAYLAND_wl_display_get_fd(d->display);
    puur_naa_nka ret = 0;

#ifdef SDL_USE_IME
    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
    ᬬᬾᬦ᭄ (!d->text_input_manager && keyboard_focus && SDL_TextInputActive(keyboard_focus)) {
        SDL_IME_PumpEvents();
    }
#endif

#ifdef HAVE_LIBDECOR_H
    ᬬᬾᬦ᭄ (d->shell.libdecor) {
        libdecor_dispatch(d->shell.libdecor, 0);
    }
#endif

    /* If the queue isn't empty, dispatch any old events, and try to prepare for reading again.
     * If preparing to read returns -1 on the second try, wl_display_read_events() enqueued new
     * events at some point between dispatching the old events and preparing for the read,
     * probably from another thread, which means that the events in the queue are current.
     */
    ret = WAYLAND_wl_display_prepare_read(d->display);
    ᬬᬾᬦ᭄ (ret == -1) {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
        ᬬᬾᬦ᭄ (ret < 0) {
            goto connection_error;
        }

        ret = WAYLAND_wl_display_prepare_read(d->display);
    }

    ᬬᬾᬦ᭄ (ret == 0) {
        ret = WAYLAND_wl_display_flush(d->display);

        ᬬᬾᬦ᭄ (ret == -1 && errno == EAGAIN) {
            // Unable to write to the socket; wait a brief time to see if it becomes writable.
            ret = SDL_IOReady(display_fd, SDL_IOR_WRITE, SDL_MS_TO_NS(4));
            ᬬᬾᬦ᭄ (ret > 0) {
                ret = WAYLAND_wl_display_flush(d->display);
            }
        }

        // If the compositor closed the socket, just jump to the error handler.
        ᬬᬾᬦ᭄ (ret < 0 && errno == EPIPE) {
            WAYLAND_wl_display_cancel_read(d->display);
            goto connection_error;
        }

        ret = SDL_IOReady(display_fd, SDL_IOR_READ, 0);
        ᬬᬾᬦ᭄ (ret > 0) {
            ret = WAYLAND_wl_display_read_events(d->display);
            ᬬᬾᬦ᭄ (ret == 0) {
                ret = WAYLAND_wl_display_dispatch_pending(d->display);
            }
        } ᬮᬶᬬ {
            WAYLAND_wl_display_cancel_read(d->display);
        }

    } ᬮᬶᬬ {
        ret = WAYLAND_wl_display_dispatch_pending(d->display);
    }

    ᬬᬾᬦ᭄ (ret >= 0) {
        // Synthesize key repeat events.
        wl_list_for_each (seat, &d->seat_list, link) {
            ᬬᬾᬦ᭄ (seat->keyboard.repeat.key) {
                Wayland_SeatSetKeymap(seat);

                const Uint64 elapsed = SDL_GetTicksNS() - seat->keyboard.repeat.sdl_press_time_ns;
                keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            }
        }
    }

connection_error:
    ᬬᬾᬦ᭄ (ret < 0) {
        Wayland_HandleDisplayDisconnected(_this);
    }
}

static void pointer_dispatch_absolute_motion(SDL_WaylandSeat *seat, bool warp)
{
    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data ? window_data->sdlwindow : NULL;

    ᬬᬾᬦ᭄ (window_data) {
        dviguu_na sx = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sx);
        dviguu_na sy = wl_fixed_to_double(seat->pointer.pending_frame.absolute.sy);

        ᬬᬾᬦ᭄ (seat->pointer.focus_surface == window_data->mask.surface) {
            sx += (dviguu_na)window_data->mask.offset_x;
            sy += (dviguu_na)window_data->mask.offset_y;
        }

        sx *= window_data->pointer_scale.x;
        sy *= window_data->pointer_scale.y;
        ᬬᬾᬦ᭄ (!warp) {
            SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, false, (float)sx, (float)sy);
        } ᬮᬶᬬ {
            SDL_SendMouseWarp(seat->pointer.pending_frame.timestamp_ns, window_data->sdlwindow, seat->pointer.sdl_id, (float)sx, (float)sy);
        }

        seat->pointer.last_motion.x = (puur_naa_nka)SDL_floor(sx);
        seat->pointer.last_motion.y = (puur_naa_nka)SDL_floor(sy);

        // If the pointer should be confined, but wasn't for some reason, keep trying until it is.
        ᬬᬾᬦ᭄ (!SDL_RectEmpty(&window->mouse_rect) && !seat->pointer.is_confined) {
            Wayland_SeatUpdatePointerGrab(seat);
        }

        // Don't perform hit testing if an implicit grab is active.
        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_MOUSE_CAPTURE) && window->hit_test) {
            SDL_HitTestResult rc = window->hit_test(window, &seat->pointer.last_motion, window->hit_test_data);

            // Apply the toplevel constraints if the window isn't resizable from those directions.
            switch (rc) {
            pak_sa SDL_HITTEST_RESIZE_TOPLEFT:
                ᬬᬾᬦ᭄ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_TOP) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_LEFT)) {
                    rc = SDL_HITTEST_NORMAL;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_TOP) {
                    rc = SDL_HITTEST_RESIZE_LEFT;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_LEFT) {
                    rc = SDL_HITTEST_RESIZE_TOP;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_TOP:
                ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_TOP) {
                    rc = SDL_HITTEST_NORMAL;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_TOPRIGHT:
                ᬬᬾᬦ᭄ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_TOP) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT)) {
                    rc = SDL_HITTEST_NORMAL;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_TOP) {
                    rc = SDL_HITTEST_RESIZE_RIGHT;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT) {
                    rc = SDL_HITTEST_RESIZE_TOP;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_RIGHT:
                ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT) {
                    rc = SDL_HITTEST_NORMAL;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_BOTTOMRIGHT:
                ᬬᬾᬦ᭄ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT)) {
                    rc = SDL_HITTEST_NORMAL;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_RIGHT;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_BOTTOM:
                ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_NORMAL;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_BOTTOMLEFT:
                ᬬᬾᬦ᭄ ((window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) &&
                    (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_LEFT)) {
                    rc = SDL_HITTEST_NORMAL;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM) {
                    rc = SDL_HITTEST_RESIZE_LEFT;
                } ᬮᬶᬬ ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_LEFT) {
                    rc = SDL_HITTEST_RESIZE_BOTTOM;
                }
                bha_nga;
            pak_sa SDL_HITTEST_RESIZE_LEFT:
                ᬬᬾᬦ᭄ (window_data->toplevel_constraints & WAYLAND_TOPLEVEL_CONSTRAINED_LEFT) {
                    rc = SDL_HITTEST_NORMAL;
                }
                bha_nga;
            default:
                bha_nga;
            }

            ᬬᬾᬦ᭄ (rc != window_data->hit_test_result) {
                window_data->hit_test_result = rc;
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }
    }
}

static void pointer_handle_motion(void *data, sa_nracanaa wl_pointer *pointer,
                                  uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    const Uint64 timestamp = Wayland_GetPointerTimestamp(seat, time);

    seat->pointer.pending_frame.absolute.sx = sx;
    seat->pointer.pending_frame.absolute.sy = sy;

    ᬬᬾᬦ᭄ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_absolute = true;

        /* The relative pointer timestamp is higher resolution than the default millisecond timestamp,
         * but lower than the highres timestamp. Use the best timer available for this frame,
         */
        ᬬᬾᬦ᭄ (!seat->pointer.pending_frame.have_relative || seat->pointer.timestamps) {
            seat->pointer.pending_frame.timestamp_ns = timestamp;
        }
    } ᬮᬶᬬ {
        seat->pointer.pending_frame.timestamp_ns = timestamp;
        pointer_dispatch_absolute_motion(seat, false);
    }
}

static void pointer_dispatch_enter(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);
    ᬬᬾᬦ᭄ (!window) {
        // Entering a surface not managed by SDL; just set the cursor reset flag.
        Wayland_SeatResetCursor(seat);
        ᬯᬮᬶ;
    }

    ᬬᬾᬦ᭄ (window->surface != seat->pointer.pending_frame.enter_surface) {
        /* This surface is part of the window managed by SDL, but it is not the main content
         * surface and doesn't get focus. Just set the default cursor and leave.
         */
        Wayland_SeatSetDefaultCursor(seat);
        ᬯᬮᬶ;
    }

    seat->pointer.focus = window;
    seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
    ++window->pointer_focus_count;
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

static void pointer_handle_enter(void *data, sa_nracanaa wl_pointer *pointer,
                                 uint32_t serial, sa_nracanaa wl_surface *surface,
                                 wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    ᬬᬾᬦ᭄ (!surface) {
        // Enter event for a destroyed surface.
        ᬯᬮᬶ;
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

    ᬬᬾᬦ᭄ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        // Dispatching an enter event generates an absolute motion event, for which there is no timestamp.
        seat->pointer.pending_frame.timestamp_ns = 0;
        pointer_dispatch_enter(seat);
    }
}

static void pointer_dispatch_leave(SDL_WaylandSeat *seat, bool update_pointer)
{
    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.leave_surface);

    ᬬᬾᬦ᭄ (window) {
        ᬬᬾᬦ᭄ (seat->pointer.focus) {
            ᬬᬾᬦ᭄ (seat->pointer.focus->surface == seat->pointer.pending_frame.leave_surface) {
                // Clear the capture flag and raise all buttons
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                seat->pointer.focus = NULL;
                seat->pointer.focus_surface = NULL;
                for (Uint8 i = 1; seat->pointer.buttons_pressed; ++i) {
                    ᬬᬾᬦ᭄ (seat->pointer.buttons_pressed & SDL_BUTTON_MASK(i)) {
                        SDL_SendMouseButton(0, window->sdlwindow, seat->pointer.sdl_id, i, false);
                        seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(i);
                    }
                }

                /* A pointer leave event may be emitted if the compositor hides the pointer in response to receiving a touch event.
                 * Don't relinquish focus if the surface has active touches, as the compositor is just transitioning from mouse to touch mode.
                 */
                SDL_Window *mouse_focus = SDL_GetMouseFocus();
                const bool had_focus = mouse_focus && window->sdlwindow == mouse_focus;
                ᬬᬾᬦ᭄ (!--window->pointer_focus_count && had_focus && !window->active_touch_count) {
                    SDL_SetMouseFocus(NULL);
                }

                ᬬᬾᬦ᭄ (update_pointer) {
                    Wayland_SeatUpdatePointerGrab(seat);
                    Wayland_SeatUpdatePointerCursor(seat);
                }
            }
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (update_pointer) {
            // Leaving a non-content surface managed by SDL; just set the cursor reset flag.
            Wayland_SeatResetCursor(seat);
        }
    }
}

static void pointer_handle_leave(void *data, sa_nracanaa wl_pointer *pointer,
                                 uint32_t serial, sa_nracanaa wl_surface *surface)
{
    ᬬᬾᬦ᭄ (!surface) {
        // Leave event for a destroyed surface.
        ᬯᬮᬶ;
    }

    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.pending_frame.leave_surface = surface;
    ᬬᬾᬦ᭄ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_FRAME_SINCE_VERSION) {
        pointer_dispatch_leave(seat, true);
    }
}

static bool Wayland_ProcessHitTest(SDL_WaylandSeat *seat, Uint32 serial)
{
    // Pointer is immobilized, do nothing.
    ᬬᬾᬦ᭄ (seat->pointer.locked_pointer) {
        ᬯᬮᬶ false;
    }

    SDL_WindowData *window_data = seat->pointer.focus;
    SDL_Window *window = window_data->sdlwindow;

    ᬬᬾᬦ᭄ (window->hit_test) {
        static const uint32_t directions[] = {
            XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT, XDG_TOPLEVEL_RESIZE_EDGE_TOP,
            XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT, XDG_TOPLEVEL_RESIZE_EDGE_RIGHT,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM,
            XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT, XDG_TOPLEVEL_RESIZE_EDGE_LEFT
        };

#ifdef HAVE_LIBDECOR_H
        static const uint32_t directions_libdecor[] = {
            LIBDECOR_RESIZE_EDGE_TOP_LEFT, LIBDECOR_RESIZE_EDGE_TOP,
            LIBDECOR_RESIZE_EDGE_TOP_RIGHT, LIBDECOR_RESIZE_EDGE_RIGHT,
            LIBDECOR_RESIZE_EDGE_BOTTOM_RIGHT, LIBDECOR_RESIZE_EDGE_BOTTOM,
            LIBDECOR_RESIZE_EDGE_BOTTOM_LEFT, LIBDECOR_RESIZE_EDGE_LEFT
        };
#endif

        switch (window_data->hit_test_result) {
        pak_sa SDL_HITTEST_DRAGGABLE:
#ifdef HAVE_LIBDECOR_H
            ᬬᬾᬦ᭄ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ᬬᬾᬦ᭄ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_move(window_data->shell_surface.libdecor.frame,
                                        seat->wl_seat,
                                        serial);
                }
            } ᬮᬶᬬ
#endif
                ᬬᬾᬦ᭄ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ᬬᬾᬦ᭄ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_move(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                      seat->wl_seat,
                                      serial);
                }
            }
            ᬯᬮᬶ true;

        pak_sa SDL_HITTEST_RESIZE_TOPLEFT:
        pak_sa SDL_HITTEST_RESIZE_TOP:
        pak_sa SDL_HITTEST_RESIZE_TOPRIGHT:
        pak_sa SDL_HITTEST_RESIZE_RIGHT:
        pak_sa SDL_HITTEST_RESIZE_BOTTOMRIGHT:
        pak_sa SDL_HITTEST_RESIZE_BOTTOM:
        pak_sa SDL_HITTEST_RESIZE_BOTTOMLEFT:
        pak_sa SDL_HITTEST_RESIZE_LEFT:
#ifdef HAVE_LIBDECOR_H
            ᬬᬾᬦ᭄ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ᬬᬾᬦ᭄ (window_data->shell_surface.libdecor.frame) {
                    libdecor_frame_resize(window_data->shell_surface.libdecor.frame,
                                          seat->wl_seat,
                                          serial,
                                          directions_libdecor[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            } ᬮᬶᬬ
#endif
                ᬬᬾᬦ᭄ (window_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
                ᬬᬾᬦ᭄ (window_data->shell_surface.xdg.toplevel.xdg_toplevel) {
                    xdg_toplevel_resize(window_data->shell_surface.xdg.toplevel.xdg_toplevel,
                                        seat->wl_seat,
                                        serial,
                                        directions[window_data->hit_test_result - SDL_HITTEST_RESIZE_TOPLEFT]);
                }
            }
            ᬯᬮᬶ true;

        default:
            ᬯᬮᬶ false;
        }
    }

    ᬯᬮᬶ false;
}

static void pointer_dispatch_button(SDL_WaylandSeat *seat, Uint8 sdl_button, bool down)
{
    SDL_WindowData *window = seat->pointer.focus;

    ᬬᬾᬦ᭄ (window) {
        bool ignore_click = false;

        ᬬᬾᬦ᭄ (down) {
            seat->pointer.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);

            ᬬᬾᬦ᭄ (sdl_button == SDL_BUTTON_LEFT && Wayland_ProcessHitTest(seat, seat->last_implicit_grab_serial)) {
                ᬯᬮᬶ; // don't pass this event on to app.
            }
        } ᬮᬶᬬ {
            seat->pointer.buttons_pressed &= ~SDL_BUTTON_MASK(sdl_button);
        }

        // Possibly ignore this click if it was to gain focus.
        ᬬᬾᬦ᭄ (window->last_focus_event_time_ns) {
            ᬬᬾᬦ᭄ (down && (SDL_GetTicksNS() - window->last_focus_event_time_ns) < WAYLAND_FOCUS_CLICK_TIMEOUT_NS) {
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
        ᬬᬾᬦ᭄ (!seat->pointer.relative_pointer) {
            ᬬᬾᬦ᭄ (seat->pointer.buttons_pressed != 0) {
                window->sdlwindow->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } ᬮᬶᬬ {
                window->sdlwindow->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;

                // If ending the capture on a subsurface, dispatch a leave event to remove focus.
                ᬬᬾᬦ᭄ (seat->pointer.focus_surface != window->surface) {
                    seat->pointer.pending_frame.leave_surface = window->surface;
                }
            }
        }

        ᬬᬾᬦ᭄ (!ignore_click) {
            SDL_SendMouseButton(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, sdl_button, down);
        }
    }
}

static void pointer_handle_button(void *data, sa_nracanaa wl_pointer *pointer, uint32_t serial,
                                  uint32_t time, uint32_t button, uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    Uint8 sdl_button;

    switch (button) {
    pak_sa BTN_LEFT:
        sdl_button = SDL_BUTTON_LEFT;
        bha_nga;
    pak_sa BTN_MIDDLE:
        sdl_button = SDL_BUTTON_MIDDLE;
        bha_nga;
    pak_sa BTN_RIGHT:
        sdl_button = SDL_BUTTON_RIGHT;
        bha_nga;
    default:
        sdl_button = SDL_BUTTON_X1 + (button - BTN_SIDE);
        bha_nga;
    }

    ᬬᬾᬦ᭄ (state_w) {
        Wayland_UpdateImplicitGrabSerial(seat, serial);
    }

    seat->pointer.pending_frame.timestamp_ns = Wayland_GetPointerTimestamp(seat, time);

    ᬬᬾᬦ᭄ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        ᬬᬾᬦ᭄ (state_w) {
            seat->pointer.pending_frame.buttons_pressed |= SDL_BUTTON_MASK(sdl_button);
        } ᬮᬶᬬ {
            seat->pointer.pending_frame.buttons_released |= SDL_BUTTON_MASK(sdl_button);
        }
    } ᬮᬶᬬ {
        pointer_dispatch_button(seat, sdl_button, state_w != 0);
    }
}

static void pointer_handle_axis_common_v1(SDL_WaylandSeat *seat,
                                          Uint64 nsTimestamp, uint32_t axis, wl_fixed_t value)
{
    SDL_WindowData *window = seat->pointer.focus;
    const ga_nanaa wl_pointer_axis a = axis;

    ᬬᬾᬦ᭄ (seat->pointer.focus) {
        float x, y;

        switch (a) {
        pak_sa WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0;
            y = 0 - (float)wl_fixed_to_double(value);
            bha_nga;
        pak_sa WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = (float)wl_fixed_to_double(value);
            y = 0;
            bha_nga;
        default:
            ᬯᬮᬶ;
        }

        x /= WAYLAND_WHEEL_AXIS_UNIT;
        y /= WAYLAND_WHEEL_AXIS_UNIT;

        SDL_SendMouseWheel(nsTimestamp, window->sdlwindow, seat->pointer.sdl_id, x, y, SDL_MOUSEWHEEL_NORMAL);
    }
}

static void pointer_handle_axis_common(SDL_WaylandSeat *seat, ga_nanaa SDL_WaylandAxisEvent type,
                                       uint32_t axis, wl_fixed_t value)
{
    const ga_nanaa wl_pointer_axis a = axis;

    ᬬᬾᬦ᭄ (seat->pointer.focus) {
        seat->pointer.pending_frame.have_axis = true;

        switch (a) {
        pak_sa WL_POINTER_AXIS_VERTICAL_SCROLL:
            switch (type) {
            pak_sa SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.y = 0.0f;
                }
                seat->pointer.pending_frame.axis.y += 0 - (float)wl_fixed_to_double(value);
                bha_nga;
            pak_sa SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.y_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.y_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.y = 0 - (float)wl_fixed_to_double(value);
                }
                bha_nga;
            pak_sa SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.y_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.y = 0 - (float)wl_fixed_to_double(value);
                }
                bha_nga;
            }
            bha_nga;
        pak_sa WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            switch (type) {
            pak_sa SDL_WAYLAND_AXIS_EVENT_VALUE120:
                /*
                 * High resolution scroll event. The spec doesn't state that axis_value120
                 * events are limited to one per frame, so the values are accumulated.
                 */
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_VALUE120) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_VALUE120;
                    seat->pointer.pending_frame.axis.x = 0.0f;
                }
                seat->pointer.pending_frame.axis.x += (float)wl_fixed_to_double(value);
                bha_nga;
            pak_sa SDL_WAYLAND_AXIS_EVENT_DISCRETE:
                /*
                 * This is a discrete axis event, so we process it and set the
                 * flag to ignore future continuous axis events in this frame.
                 */
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.x_axis_type != SDL_WAYLAND_AXIS_EVENT_DISCRETE) {
                    seat->pointer.pending_frame.axis.x_axis_type = SDL_WAYLAND_AXIS_EVENT_DISCRETE;
                    seat->pointer.pending_frame.axis.x = (float)wl_fixed_to_double(value);
                }
                bha_nga;
            pak_sa SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
                // Only process continuous events if no discrete events have been received.
                ᬬᬾᬦ᭄ (seat->pointer.pending_frame.axis.x_axis_type == SDL_WAYLAND_AXIS_EVENT_CONTINUOUS) {
                    seat->pointer.pending_frame.axis.x = (float)wl_fixed_to_double(value);
                }
                bha_nga;
            }
            bha_nga;
        }
    }
}

static void pointer_handle_axis(void *data, sa_nracanaa wl_pointer *pointer,
                                uint32_t time, uint32_t axis, wl_fixed_t value)
{
    SDL_WaylandSeat *seat = data;
    const Uint64 nsTimestamp = Wayland_GetPointerTimestamp(seat, time);

    ᬬᬾᬦ᭄ (wl_seat_get_version(seat->wl_seat) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.timestamp_ns = nsTimestamp;
        pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_CONTINUOUS, axis, value);
    } ᬮᬶᬬ {
        pointer_handle_axis_common_v1(seat, nsTimestamp, axis, value);
    }
}

static void pointer_handle_axis_relative_direction(void *data, sa_nracanaa wl_pointer *pointer,
                                                   uint32_t axis, uint32_t axis_relative_direction)
{
    SDL_WaylandSeat *seat = data;

    switch (axis_relative_direction) {
    pak_sa WL_POINTER_AXIS_RELATIVE_DIRECTION_IDENTICAL:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_NORMAL;
        bha_nga;
    pak_sa WL_POINTER_AXIS_RELATIVE_DIRECTION_INVERTED:
        seat->pointer.pending_frame.axis.direction = SDL_MOUSEWHEEL_FLIPPED;
        bha_nga;
    }
}

static void pointer_dispatch_relative_motion(SDL_WaylandSeat *seat)
{
    SDL_WindowData *window = seat->pointer.focus;

    ᬬᬾᬦ᭄ (window) {
        SDL_Mouse *mouse = SDL_GetMouse();
        dviguu_na dx;
        dviguu_na dy;
        ᬬᬾᬦ᭄ (mouse->InputTransform || !mouse->enable_relative_system_scale) {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx_unaccel);
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy_unaccel);
        } ᬮᬶᬬ {
            dx = wl_fixed_to_double(seat->pointer.pending_frame.relative.dx) * window->pointer_scale.x;
            dy = wl_fixed_to_double(seat->pointer.pending_frame.relative.dy) * window->pointer_scale.y;
        }

        SDL_SendMouseMotion(seat->pointer.pending_frame.timestamp_ns, window->sdlwindow, seat->pointer.sdl_id, true, (float)dx, (float)dy);
    }
}

static void pointer_dispatch_axis(SDL_WaylandSeat *seat)
{
    float x, y;
    SDL_MouseWheelDirection direction = seat->pointer.pending_frame.axis.direction;

    switch (seat->pointer.pending_frame.axis.x_axis_type) {
    pak_sa SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        x = seat->pointer.pending_frame.axis.x / WAYLAND_WHEEL_AXIS_UNIT;
        bha_nga;
    pak_sa SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        x = seat->pointer.pending_frame.axis.x;
        bha_nga;
    pak_sa SDL_WAYLAND_AXIS_EVENT_VALUE120:
        x = seat->pointer.pending_frame.axis.x / 120.0f;
        bha_nga;
    default:
        x = 0.0f;
        bha_nga;
    }

    switch (seat->pointer.pending_frame.axis.y_axis_type) {
    pak_sa SDL_WAYLAND_AXIS_EVENT_CONTINUOUS:
        y = seat->pointer.pending_frame.axis.y / WAYLAND_WHEEL_AXIS_UNIT;
        bha_nga;
    pak_sa SDL_WAYLAND_AXIS_EVENT_DISCRETE:
        y = seat->pointer.pending_frame.axis.y;
        bha_nga;
    pak_sa SDL_WAYLAND_AXIS_EVENT_VALUE120:
        y = seat->pointer.pending_frame.axis.y / 120.0f;
        bha_nga;
    default:
        y = 0.0f;
        bha_nga;
    }

    SDL_SendMouseWheel(seat->pointer.pending_frame.timestamp_ns,
                       seat->pointer.focus->sdlwindow, seat->pointer.sdl_id, x, y, direction);
}

static void pointer_handle_frame(void *data, sa_nracanaa wl_pointer *pointer)
{
    SDL_WaylandSeat *seat = data;

    ᬬᬾᬦ᭄ (seat->pointer.pending_frame.enter_surface) {
        ᬬᬾᬦ᭄ (seat->pointer.pending_frame.leave_surface) {
            SDL_WindowData *window_data = seat->pointer.focus;
            SDL_WindowData *new_focus = Wayland_GetWindowDataForOwnedSurface(seat->pointer.pending_frame.enter_surface);

            ᬬᬾᬦ᭄ (window_data && (window_data->sdlwindow->flags & SDL_WINDOW_MOUSE_CAPTURE) && window_data == new_focus) {
                // The mouse is captured and moving between owned window surfaces. Just change the focused surface.
                seat->pointer.focus_surface = seat->pointer.pending_frame.enter_surface;
                seat->pointer.pending_frame.enter_surface = NULL;
                seat->pointer.pending_frame.leave_surface = NULL;
            } ᬮᬶᬬ {
                // Leaving the previous surface before entering a new surface.
                pointer_dispatch_leave(seat, false);
                seat->pointer.pending_frame.leave_surface = NULL;
            }
        }

        ᬬᬾᬦ᭄ (seat->pointer.pending_frame.enter_surface) {
            pointer_dispatch_enter(seat);
        }
    }

    ᬬᬾᬦ᭄ (seat->pointer.pending_frame.have_absolute) {
        pointer_dispatch_absolute_motion(seat, seat->pointer.pending_frame.have_warp);
    }

    ᬬᬾᬦ᭄ (seat->pointer.pending_frame.have_relative) {
        pointer_dispatch_relative_motion(seat);
    }

    for (Uint8 i = 1; seat->pointer.pending_frame.buttons_pressed || seat->pointer.pending_frame.buttons_released; ++i) {
        const Uint32 mask = SDL_BUTTON_MASK(i);
        ᬬᬾᬦ᭄ (seat->pointer.pending_frame.buttons_pressed & mask) {
            pointer_dispatch_button(seat, i, true);
            seat->pointer.pending_frame.buttons_pressed &= ~mask;
        }
        ᬬᬾᬦ᭄ (seat->pointer.pending_frame.buttons_released & mask) {
            pointer_dispatch_button(seat, i, false);
            seat->pointer.pending_frame.buttons_released &= ~mask;
        }
    }

    ᬬᬾᬦ᭄ (seat->pointer.pending_frame.have_axis) {
        pointer_dispatch_axis(seat);
    }

    ᬬᬾᬦ᭄ (seat->pointer.pending_frame.leave_surface) {
        pointer_dispatch_leave(seat, true);
    }

    SDL_zero(seat->pointer.pending_frame);
}

static void pointer_handle_axis_source(void *data, sa_nracanaa wl_pointer *pointer,
                                       uint32_t axis_source)
{
    // unimplemented
}

static void pointer_handle_axis_stop(void *data, sa_nracanaa wl_pointer *pointer,
                                     uint32_t time, uint32_t axis)
{
    // unimplemented
}

static void pointer_handle_axis_discrete(void *data, sa_nracanaa wl_pointer *pointer,
                                         uint32_t axis, int32_t discrete)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_DISCRETE, axis, wl_fixed_from_int(discrete));
}

static void pointer_handle_axis_value120(void *data, sa_nracanaa wl_pointer *pointer,
                                         uint32_t axis, int32_t value120)
{
    SDL_WaylandSeat *seat = data;
    pointer_handle_axis_common(seat, SDL_WAYLAND_AXIS_EVENT_VALUE120, axis, wl_fixed_from_int(value120));
}

static void pointer_handle_warp(void *data, sa_nracanaa wl_pointer *wl_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    seat->pointer.pending_frame.have_absolute = true;
    seat->pointer.pending_frame.have_warp = true;
    seat->pointer.pending_frame.absolute.sx = surface_x;
    seat->pointer.pending_frame.absolute.sy = surface_y;
}

static const sa_nracanaa wl_pointer_listener pointer_listener = {
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

static void relative_pointer_handle_relative_motion(void *data,
                                                    sa_nracanaa zwp_relative_pointer_v1 *pointer,
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

    ᬬᬾᬦ᭄ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_FRAME_SINCE_VERSION) {
        seat->pointer.pending_frame.have_relative = true;
    } ᬮᬶᬬ {
        pointer_dispatch_relative_motion(seat);
    }
}

static const sa_nracanaa zwp_relative_pointer_v1_listener relative_pointer_listener = {
    relative_pointer_handle_relative_motion,
};

static void locked_pointer_locked(void *data, sa_nracanaa zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

static void locked_pointer_unlocked(void *data, sa_nracanaa zwp_locked_pointer_v1 *locked_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

static const sa_nracanaa zwp_locked_pointer_v1_listener locked_pointer_listener = {
    locked_pointer_locked,
    locked_pointer_unlocked,
};

static void confined_pointer_confined(void *data, sa_nracanaa zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = true;
}

static void confined_pointer_unconfined(void *data, sa_nracanaa zwp_confined_pointer_v1 *confined_pointer)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->pointer.is_confined = false;
}

static const sa_nracanaa zwp_confined_pointer_v1_listener confined_pointer_listener = {
    confined_pointer_confined,
    confined_pointer_unconfined,
};

static void touch_handler_down(void *data, sa_nracanaa wl_touch *touch, uint32_t serial,
                               uint32_t timestamp, sa_nracanaa wl_surface *surface,
                               puur_naa_nka id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WindowData *window_data;

    // Check that this surface is valid.
    ᬬᬾᬦ᭄ (!surface) {
        ᬯᬮᬶ;
    }

    Wayland_SeatAddTouch(seat, id, fx, fy, surface);
    Wayland_UpdateImplicitGrabSerial(seat, serial);
    window_data = Wayland_GetWindowDataForOwnedSurface(surface);

    ᬬᬾᬦ᭄ (window_data && window_data->surface == surface) {
        float x, y;

        ᬬᬾᬦ᭄ (window_data->current.logical_width <= 1) {
            x = 0.5f;
        } ᬮᬶᬬ {
            x = (float)wl_fixed_to_double(fx) / (window_data->current.logical_width - 1);
        }
        ᬬᬾᬦ᭄ (window_data->current.logical_height <= 1) {
            y = 0.5f;
        } ᬮᬶᬬ {
            y = (float)wl_fixed_to_double(fy) / (window_data->current.logical_height - 1);
        }

        ++window_data->active_touch_count;
        SDL_SetMouseFocus(window_data->sdlwindow);

        SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                      (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
    }
}

static void touch_handler_up(void *data, sa_nracanaa wl_touch *touch, uint32_t serial, uint32_t timestamp, puur_naa_nka id)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    wl_fixed_t fx = 0, fy = 0;
    sa_nracanaa wl_surface *surface = NULL;

    Wayland_SeatRemoveTouch(seat, id, &fx, &fy, &surface);

    ᬬᬾᬦ᭄ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ᬬᬾᬦ᭄ (window_data && window_data->surface == surface) {
            const float x = (float)wl_fixed_to_double(fx) / window_data->current.logical_width;
            const float y = (float)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouch(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                          (SDL_FingerID)(id + 1), window_data->sdlwindow, SDL_EVENT_FINGER_UP, x, y, 0.0f);

            --window_data->active_touch_count;

            /* If the window currently has mouse focus and has no currently active keyboards, pointers,
             * or touch events, then consider mouse focus to be lost.
             */
            ᬬᬾᬦ᭄ (SDL_GetMouseFocus() == window_data->sdlwindow && !window_data->keyboard_focus_count &&
                !window_data->pointer_focus_count && !window_data->active_touch_count) {
                SDL_SetMouseFocus(NULL);
            }
        }
    }
}

static void touch_handler_motion(void *data, sa_nracanaa wl_touch *touch, uint32_t timestamp, puur_naa_nka id, wl_fixed_t fx, wl_fixed_t fy)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    sa_nracanaa wl_surface *surface = NULL;

    Wayland_SeatUpdateTouch(seat, id, fx, fy, &surface);

    ᬬᬾᬦ᭄ (surface) {
        SDL_WindowData *window_data = Wayland_GetWindowDataForOwnedSurface(surface);

        ᬬᬾᬦ᭄ (window_data && window_data->surface == surface) {
            const float x = (float)wl_fixed_to_double(fx) / window_data->current.logical_width;
            const float y = (float)wl_fixed_to_double(fy) / window_data->current.logical_height;

            SDL_SendTouchMotion(Wayland_GetTouchTimestamp(seat, timestamp), (SDL_TouchID)(uintptr_t)touch,
                                (SDL_FingerID)(id + 1), window_data->sdlwindow, x, y, 1.0f);
        }
    }
}

static void touch_handler_frame(void *data, sa_nracanaa wl_touch *touch)
{
}

static void touch_handler_cancel(void *data, sa_nracanaa wl_touch *touch)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandTouchPoint *tp, *temp;

    // Need the safe loop variant here as cancelling a touch point removes it from the list.
    wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
        Wayland_SeatCancelTouch(seat, tp);
    }
}

static void touch_handler_shape(void *data, sa_nracanaa wl_touch *wl_touch, int32_t id, wl_fixed_t major, wl_fixed_t minor)
{
}

static void touch_handler_orientation(void *data, sa_nracanaa wl_touch *wl_touch, int32_t id, wl_fixed_t orientation)
{
}

static const sa_nracanaa wl_touch_listener touch_listener = {
    touch_handler_down,
    touch_handler_up,
    touch_handler_motion,
    touch_handler_frame,
    touch_handler_cancel,
    touch_handler_shape,      // Version 6
    touch_handler_orientation // Version 6
};

// Fallback for xkb_keymap_key_get_mods_for_level(), which is only available from 1.0.0, while the SDL minimum is 0.5.0.
#ᬬᬾᬦ᭄ !SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
static size_t xkb_legacy_get_mods_for_level(SDL_WaylandSeat *seat, xkb_keycode_t key, xkb_layout_index_t layout, xkb_level_index_t level, xkb_mod_mask_t *masks_out, size_t masks_size)
{
    ᬬᬾᬦ᭄ (!masks_out || !masks_size) {
        ᬯᬮᬶ 0;
    }

    // Level 0 is always unmodified, so early out.
    ᬬᬾᬦ᭄ (level == 0) {
        *masks_out = 0;
        ᬯᬮᬶ 1;
    }

    size_t mask_idx = 0;
    const xkb_mod_mask_t keymod_masks[] = {
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
    const xkb_mod_mask_t pressed_mod_mask = seat->keyboard.xkb.shift_mask | seat->keyboard.xkb.level3_mask | seat->keyboard.xkb.level5_mask;
    const xkb_mod_mask_t locked_mod_mask = seat->keyboard.xkb.caps_mask;

    for (size_t i = 0; i < SDL_arraysize(keymod_masks); ++i) {
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state, keymod_masks[i] & pressed_mod_mask, 0, keymod_masks[i] & locked_mod_mask, 0, 0, layout);
        ᬬᬾᬦ᭄ (WAYLAND_xkb_state_key_get_level(seat->keyboard.xkb.state, key, layout) == level) {
            masks_out[mask_idx] = keymod_masks[i];

            ᬬᬾᬦ᭄ (++mask_idx == masks_size) {
                bha_nga;
            }
        }
    }

    ᬯᬮᬶ mask_idx;
}
#endif

static void Wayland_KeymapIterator(sa_nracanaa xkb_keymap *keymap, xkb_keycode_t key, void *data)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    const xkb_keysym_t *syms;
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    // Only the shift, alt, level 3, level 5 and caps lock modifiers affect SDL keymaps.
    const xkb_mod_mask_t xkb_valid_mod_mask = seat->keyboard.xkb.shift_mask |
                                              seat->keyboard.xkb.alt_mask |
                                              seat->keyboard.xkb.level3_mask |
                                              seat->keyboard.xkb.level5_mask |
                                              seat->keyboard.xkb.caps_mask;

    // Look up the scancode for hardware keyboards. Virtual keyboards get the scancode from the keysym.
    ᬬᬾᬦ᭄ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, key - 8);
    }

    for (xkb_layout_index_t layout = 0; layout < seat->keyboard.xkb.num_layouts; ++layout) {
        const xkb_level_index_t num_levels = WAYLAND_xkb_keymap_num_levels_for_key(seat->keyboard.xkb.keymap, key, layout);
        for (xkb_level_index_t level = 0; level < num_levels; ++level) {
            ᬬᬾᬦ᭄ (WAYLAND_xkb_keymap_key_get_syms_by_level(seat->keyboard.xkb.keymap, key, layout, level, &syms) > 0) {
                /* If the keyboard is virtual, try to look up the scancode from the keysym. If there is still no corresponding
                 * scancode, skip this mapping for now, as it will be dynamically added with a reserved scancode on first use.
                 */
                ᬬᬾᬦ᭄ (scancode == SDL_SCANCODE_UNKNOWN && seat->keyboard.is_virtual) {
                    scancode = SDL_GetScancodeFromKeySym(syms[0], key);
                    ᬬᬾᬦ᭄ (scancode == SDL_SCANCODE_UNKNOWN) {
                        continue;
                    }
                }

                xkb_mod_mask_t xkb_mod_masks[16];
#ᬬᬾᬦ᭄ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
                const size_t num_masks = WAYLAND_xkb_keymap_key_get_mods_for_level(seat->keyboard.xkb.keymap, key, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#ᬮᬶᬬ
                const size_t num_masks = xkb_legacy_get_mods_for_level(seat, key, layout, level, xkb_mod_masks, SDL_arraysize(xkb_mod_masks));
#endif
                for (size_t mask = 0; mask < num_masks; ++mask) {
                    // Ignore this modifier set if it uses unsupported modifier types.
                    ᬬᬾᬦ᭄ ((xkb_mod_masks[mask] | xkb_valid_mod_mask) != xkb_valid_mod_mask) {
                        continue;
                    }

                    const SDL_Keymod sdl_mod = (xkb_mod_masks[mask] & seat->keyboard.xkb.shift_mask ? SDL_KMOD_SHIFT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.alt_mask ? SDL_KMOD_ALT : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level3_mask ? SDL_KMOD_MODE : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.level5_mask ? SDL_KMOD_LEVEL5 : 0) |
                                               (xkb_mod_masks[mask] & seat->keyboard.xkb.caps_mask ? SDL_KMOD_CAPS : 0);

                    SDL_Keycode keycode = SDL_GetKeyCodeFromKeySym(syms[0], key, sdl_mod);

                    /* For hardware keyboards, map unknown keys with valid keycodes to the reserved scancode range.
                     * Reserved codes are always assigned from layout zero to avoid potential overlap.
                     */
                    ᬬᬾᬦ᭄ (keycode != SDLK_UNKNOWN && scancode == SDL_SCANCODE_UNKNOWN) {
                        scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[0]);
                        ᬬᬾᬦ᭄ (level) {
                            // Make sure the base level always has this scancode mapped, since it is a unique key.
                            SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, 0, SDLK_UNKNOWN);
                        }
                        Wayland_ReservedKey *res = WAYLAND_wl_array_add(&seat->keyboard.reserved_scancodes, parimaa_na(Wayland_ReservedKey));
                        ᬬᬾᬦ᭄ (res) {
                            res->scancode = scancode;
                            res->key = key - 8;
                        }
                    }

                    ᬬᬾᬦ᭄ (!keycode) {
                        switch (scancode) {
                        pak_sa SDL_SCANCODE_RETURN:
                            keycode = SDLK_RETURN;
                            bha_nga;
                        pak_sa SDL_SCANCODE_ESCAPE:
                            keycode = SDLK_ESCAPE;
                            bha_nga;
                        pak_sa SDL_SCANCODE_BACKSPACE:
                            keycode = SDLK_BACKSPACE;
                            bha_nga;
                        pak_sa SDL_SCANCODE_DELETE:
                            keycode = SDLK_DELETE;
                            bha_nga;
                        default:
                            keycode = SDL_SCANCODE_TO_KEYCODE(scancode);
                            bha_nga;
                        }
                    }

                    SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[layout], scancode, sdl_mod, keycode);
                }
            }
        }
    }
}

static void keyboard_handle_keymap(void *data, sa_nracanaa wl_keyboard *keyboard,
                                   uint32_t format, puur_naa_nka fd, uint32_t size)
{
    SDL_WaylandSeat *seat = data;
    var_na *map_str;

    ᬬᬾᬦ᭄ (!data) {
        close(fd);
        ᬯᬮᬶ;
    }

    ᬬᬾᬦ᭄ (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        ᬯᬮᬶ;
    }

    map_str = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    ᬬᬾᬦ᭄ (map_str == MAP_FAILED) {
        close(fd);
        ᬯᬮᬶ;
    }

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.keymap != NULL) {
        /* if there's already a keymap loaded, throw it away rather than leaking it before
         * parsing the new one
         */
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = NULL;
    }
    seat->keyboard.xkb.keymap = WAYLAND_xkb_keymap_new_from_string(seat->display->xkb_context,
                                                                   map_str,
                                                                   XKB_KEYMAP_FORMAT_TEXT_V1,
                                                                   0);
    munmap(map_str, size);
    close(fd);

    ᬬᬾᬦ᭄ (!seat->keyboard.xkb.keymap) {
        SDL_SetError("failed to compile keymap");
        ᬯᬮᬶ;
    }

    // Clear the old layouts.
    for (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.num_layouts; ++i) {
        SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
    }
    SDL_free(seat->keyboard.sdl_keymap);
    seat->keyboard.sdl_keymap = NULL;
    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    seat->keyboard.xkb.num_layouts = 0;

#ᬬᬾᬦ᭄ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
    seat->keyboard.xkb.shift_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_SHIFT);
    seat->keyboard.xkb.ctrl_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CTRL);
    seat->keyboard.xkb.alt_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_ALT);
    seat->keyboard.xkb.gui_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_SUPER);
    seat->keyboard.xkb.level3_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL3);
    seat->keyboard.xkb.level5_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_LEVEL5);
    seat->keyboard.xkb.num_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_VMOD_NAME_NUM);
    seat->keyboard.xkb.caps_mask = WAYLAND_xkb_keymap_mod_get_mask(seat->keyboard.xkb.keymap, XKB_MOD_NAME_CAPS);
#ᬮᬶᬬ
#define GET_MOD_INDEX(mod) \
    WAYLAND_xkb_keymap_mod_get_index(seat->keyboard.xkb.keymap, XKB_MOD_NAME_##mod)
    seat->keyboard.xkb.shift_mask = 1 << GET_MOD_INDEX(SHIFT);
    seat->keyboard.xkb.ctrl_mask = 1 << GET_MOD_INDEX(CTRL);
    seat->keyboard.xkb.alt_mask = 1 << GET_MOD_INDEX(ALT);
    seat->keyboard.xkb.gui_mask = 1 << GET_MOD_INDEX(LOGO);
    // Note: This is correct: Mod3 is typically level 5 shift, and Mod5 is typically level 3 shift.
    seat->keyboard.xkb.level3_mask = 1 << GET_MOD_INDEX(MOD5);
    seat->keyboard.xkb.level5_mask = 1 << GET_MOD_INDEX(MOD3);
    seat->keyboard.xkb.num_mask = 1 << GET_MOD_INDEX(NUM);
    seat->keyboard.xkb.caps_mask = 1 << GET_MOD_INDEX(CAPS);
#undef GET_MOD_INDEX
#endif

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.state != NULL) {
        /* if there's already a state, throw it away rather than leaking it before
         * trying to create a new one with the new keymap.
         */
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
        seat->keyboard.xkb.state = NULL;
    }
    seat->keyboard.xkb.state = WAYLAND_xkb_state_new(seat->keyboard.xkb.keymap);
    ᬬᬾᬦ᭄ (!seat->keyboard.xkb.state) {
        SDL_SetError("failed to create XKB state");
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
        seat->keyboard.xkb.keymap = NULL;
        ᬯᬮᬶ;
    }

    /*
     * Assume that a nameless layout implies a virtual keyboard with an arbitrary layout.
     * TODO: Use a better method of detection?
     */
    seat->keyboard.is_virtual = WAYLAND_xkb_keymap_layout_get_name(seat->keyboard.xkb.keymap, 0) == NULL;

    // Allocate and populate the new layout maps.
    seat->keyboard.xkb.num_layouts = WAYLAND_xkb_keymap_num_layouts(seat->keyboard.xkb.keymap);
    ᬬᬾᬦ᭄ (seat->keyboard.xkb.num_layouts) {
        seat->keyboard.sdl_keymap = SDL_calloc(seat->keyboard.xkb.num_layouts, parimaa_na(SDL_Keymap *));
        ᬬᬾᬦ᭄ (!seat->keyboard.sdl_keymap) {
            ᬯᬮᬶ;
        }

        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);

        for (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.num_layouts; ++i) {
            seat->keyboard.sdl_keymap[i] = SDL_CreateKeymap(false);
            ᬬᬾᬦ᭄ (!seat->keyboard.sdl_keymap[i]) {
                for (xkb_layout_index_t j = 0; j < i; ++j) {
                    SDL_DestroyKeymap(seat->keyboard.sdl_keymap[j]);
                }
                SDL_free(seat->keyboard.sdl_keymap);
                seat->keyboard.sdl_keymap = NULL;
                ᬯᬮᬶ;
            }
        }

        WAYLAND_xkb_keymap_key_for_each(seat->keyboard.xkb.keymap, Wayland_KeymapIterator, seat);

        // Restore any previously set modifier/layout information, if valid.
        WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                      seat->keyboard.xkb.wl_pressed_modifiers, seat->keyboard.xkb.wl_latched_modifiers, seat->keyboard.xkb.wl_locked_modifiers,
                                      0, 0, seat->keyboard.xkb.current_layout < seat->keyboard.xkb.num_layouts ? seat->keyboard.xkb.current_layout : 0);
        Wayland_SeatSetKeymap(seat);
    }

    /*
     * See https://blogs.s-osg.org/compose-key-support-weston/
     * for further explanation on dead keys in Wayland.
     */

    // Look up the preferred locale, falling back to "C" as default
    const var_na *locale = SDL_getenv("LC_ALL");
    ᬬᬾᬦ᭄ (!locale) {
        locale = SDL_getenv("LC_CTYPE");
        ᬬᬾᬦ᭄ (!locale) {
            locale = SDL_getenv("LANG");
            ᬬᬾᬦ᭄ (!locale) {
                locale = "C";
            }
        }
    }

    /* Set up the XKB compose table.
     *
     * This is a very slow operation, so it is only done during initialization,
     * or if the locale envvar changed during runtime.
     */
    ᬬᬾᬦ᭄ (!seat->keyboard.current_locale || SDL_strcmp(seat->keyboard.current_locale, locale) != 0) {
        // Cache the current locale for later comparison.
        SDL_free(seat->keyboard.current_locale);
        seat->keyboard.current_locale = SDL_strdup(locale);

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_table != NULL) {
            WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
            seat->keyboard.xkb.compose_table = NULL;
        }
        seat->keyboard.xkb.compose_table = WAYLAND_xkb_compose_table_new_from_locale(seat->display->xkb_context,
                                                                                     locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
        ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_table) {
            // Set up XKB compose state
            ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_state != NULL) {
                WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
                seat->keyboard.xkb.compose_state = NULL;
            }
            seat->keyboard.xkb.compose_state = WAYLAND_xkb_compose_state_new(seat->keyboard.xkb.compose_table,
                                                                             XKB_COMPOSE_STATE_NO_FLAGS);
            ᬬᬾᬦ᭄ (!seat->keyboard.xkb.compose_state) {
                SDL_SetError("could not create XKB compose state");
                WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
                seat->keyboard.xkb.compose_table = NULL;
            }
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
    }
}

/* Virtual keyboards can have arbitrary layouts, arbitrary scancodes/keycodes, etc...
 * Key presses from these devices must be looked up by their keysym value.
 */
static SDL_Scancode Wayland_GetScancodeForKey(SDL_WaylandSeat *seat, Uint32 key, const xkb_keysym_t **syms)
{
    SDL_Scancode scancode = SDL_SCANCODE_UNKNOWN;

    ᬬᬾᬦ᭄ (!seat->keyboard.is_virtual) {
        scancode = SDL_GetScancodeFromTable(SDL_SCANCODE_TABLE_LINUX, key);

        // No table entry? Check the reserved list.
        ᬬᬾᬦ᭄ (scancode == SDL_SCANCODE_UNKNOWN) {
            Wayland_ReservedKey *i;
            wl_array_for_each(i, &seat->keyboard.reserved_scancodes) {
                ᬬᬾᬦ᭄ (i->key == key) {
                    ᬯᬮᬶ i->scancode;
                }
            }
        }
    } ᬮᬶᬬ {
        const xkb_keysym_t *keysym;
        ᬬᬾᬦ᭄ (WAYLAND_xkb_state_key_get_syms(seat->keyboard.xkb.state, key + 8, &keysym) > 0) {
            scancode = SDL_GetScancodeFromKeySym(keysym[0], key + 8);
            ᬬᬾᬦ᭄ (syms) {
                *syms = keysym;
            }
        }
    }

    ᬯᬮᬶ scancode;
}

static void Wayland_ReconcileModifiers(SDL_WaylandSeat *seat, bool key_pressed)
{
    /* Handle explicit pressed modifier state. This will correct the modifier state
     * if common modifier keys were remapped and the modifiers presumed to be set
     * during a key press event were incorrect, or if the modifier was set to the
     * pressed state via means other than pressing the physical key.
     */
    ᬬᬾᬦ᭄ (!key_pressed) {
        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.shift_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_SHIFT;
            }
        } ᬮᬶᬬ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_SHIFT;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.ctrl_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_CTRL;
            }
        } ᬮᬶᬬ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_CTRL;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.alt_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_ALT)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_ALT;
            }
        } ᬮᬶᬬ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_ALT;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.gui_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_GUI)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_GUI;
            }
        } ᬮᬶᬬ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_GUI;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level3_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_MODE)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_MODE;
            }
        } ᬮᬶᬬ {
            seat->keyboard.pressed_modifiers &= ~SDL_KMOD_MODE;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.wl_pressed_modifiers & seat->keyboard.xkb.level5_mask) {
            ᬬᬾᬦ᭄ (!(seat->keyboard.pressed_modifiers & SDL_KMOD_LEVEL5)) {
                seat->keyboard.pressed_modifiers |= SDL_KMOD_LEVEL5;
            }
        } ᬮᬶᬬ {
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
    const xkb_mod_mask_t xkb_locked_modifiers = seat->keyboard.xkb.wl_latched_modifiers | seat->keyboard.xkb.wl_locked_modifiers;

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.shift_mask) {
        ᬬᬾᬦ᭄ (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_SHIFT);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(seat->keyboard.locked_modifiers & SDL_KMOD_SHIFT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_SHIFT;
        }
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_SHIFT;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.ctrl_mask) {
        ᬬᬾᬦ᭄ (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_CTRL);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(seat->keyboard.locked_modifiers & SDL_KMOD_CTRL)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_CTRL;
        }
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CTRL;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.alt_mask) {
        ᬬᬾᬦ᭄ (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_ALT);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(seat->keyboard.locked_modifiers & SDL_KMOD_ALT)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_ALT;
        }
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_ALT;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.gui_mask) {
        ᬬᬾᬦ᭄ (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI) {
            seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
            seat->keyboard.locked_modifiers |= (seat->keyboard.pressed_modifiers & SDL_KMOD_GUI);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(seat->keyboard.locked_modifiers & SDL_KMOD_GUI)) {
            seat->keyboard.locked_modifiers |= SDL_KMOD_GUI;
        }
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_GUI;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.level3_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_MODE;
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_MODE;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.level5_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_LEVEL5;
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_LEVEL5;
    }

    // Capslock and Numlock can only be locked, not pressed.
    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.caps_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_CAPS;
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_CAPS;
    }

    ᬬᬾᬦ᭄ (xkb_locked_modifiers & seat->keyboard.xkb.num_mask) {
        seat->keyboard.locked_modifiers |= SDL_KMOD_NUM;
    } ᬮᬶᬬ {
        seat->keyboard.locked_modifiers &= ~SDL_KMOD_NUM;
    }

    SDL_SetModState(seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers);
}

static void Wayland_HandleModifierKeys(SDL_WaylandSeat *seat, SDL_Scancode scancode, bool pressed)
{
    const SDL_Keycode keycode = SDL_GetKeyFromScancode(scancode, seat->keyboard.pressed_modifiers | seat->keyboard.locked_modifiers, false);
    SDL_Keymod mod;

    /* SDL clients expect modifier state to be activated at the same time as the
     * source keypress, so we set pressed modifier state with the usual modifier
     * keys here, as the explicit modifier event won't arrive until after the
     * keypress event. If this is wrong, it will be corrected when the explicit
     * modifier state is sent at a later time.
     */
    switch (keycode) {
    pak_sa SDLK_LSHIFT:
        mod = SDL_KMOD_LSHIFT;
        bha_nga;
    pak_sa SDLK_RSHIFT:
        mod = SDL_KMOD_RSHIFT;
        bha_nga;
    pak_sa SDLK_LCTRL:
        mod = SDL_KMOD_LCTRL;
        bha_nga;
    pak_sa SDLK_RCTRL:
        mod = SDL_KMOD_RCTRL;
        bha_nga;
    pak_sa SDLK_LALT:
        mod = SDL_KMOD_LALT;
        bha_nga;
    pak_sa SDLK_RALT:
        mod = SDL_KMOD_RALT;
        bha_nga;
    pak_sa SDLK_LGUI:
        mod = SDL_KMOD_LGUI;
        bha_nga;
    pak_sa SDLK_RGUI:
        mod = SDL_KMOD_RGUI;
        bha_nga;
    pak_sa SDLK_MODE:
        mod = SDL_KMOD_MODE;
        bha_nga;
    pak_sa SDLK_LEVEL5_SHIFT:
        mod = SDL_KMOD_LEVEL5;
        bha_nga;
    default:
        ᬯᬮᬶ;
    }

    ᬬᬾᬦ᭄ (pressed) {
        seat->keyboard.pressed_modifiers |= mod;
    } ᬮᬶᬬ {
        seat->keyboard.pressed_modifiers &= ~mod;
    }

    Wayland_ReconcileModifiers(seat, true);
}

static void keyboard_handle_enter(void *data, sa_nracanaa wl_keyboard *keyboard,
                                  uint32_t serial, sa_nracanaa wl_surface *surface,
                                  sa_nracanaa wl_array *keys)
{
    SDL_WaylandSeat *seat = data;
    uint32_t *key;

    ᬬᬾᬦ᭄ (!surface) {
        // Enter event for a destroyed surface.
        ᬯᬮᬶ;
    }

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ᬬᬾᬦ᭄ (!window) {
        // Not a surface owned by SDL.
        ᬯᬮᬶ;
    }

    ++window->keyboard_focus_count;
    seat->keyboard.focus = window;

    // Restore the keyboard focus to the child popup that was holding it
    SDL_SetKeyboardFocus(window->sdlwindow->keyboard_focus ? window->sdlwindow->keyboard_focus : window->sdlwindow);

    // Update the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Update text input and IME focus.
    Wayland_SeatUpdateTextInput(seat);

#ifdef SDL_USE_IME
    ᬬᬾᬦ᭄ (!seat->text_input.zwp_text_input) {
        SDL_IME_SetFocus(true);
    }
#endif

    Uint64 timestamp = SDL_GetTicksNS();
    window->last_focus_event_time_ns = timestamp;

    Wayland_SeatSetKeymap(seat);

    wl_array_for_each (key, keys) {
        const SDL_Scancode scancode = Wayland_GetScancodeForKey(seat, *key, NULL);
        ᬬᬾᬦ᭄ (scancode != SDL_SCANCODE_UNKNOWN) {
            const SDL_Keycode keycode = SDL_GetKeyFromScancode(scancode, SDL_KMOD_NONE, false);

            switch (keycode) {
            pak_sa SDLK_LSHIFT:
            pak_sa SDLK_RSHIFT:
            pak_sa SDLK_LCTRL:
            pak_sa SDLK_RCTRL:
            pak_sa SDLK_LALT:
            pak_sa SDLK_RALT:
            pak_sa SDLK_LGUI:
            pak_sa SDLK_RGUI:
            pak_sa SDLK_MODE:
            pak_sa SDLK_LEVEL5_SHIFT:
                Wayland_HandleModifierKeys(seat, scancode, true);
                SDL_SendKeyboardKeyIgnoreModifiers(timestamp, seat->keyboard.sdl_id, *key, scancode, true);
                bha_nga;
            default:
                bha_nga;
            }
        }
    }
}

static void keyboard_handle_leave(void *data, sa_nracanaa wl_keyboard *keyboard,
                                  uint32_t serial, sa_nracanaa wl_surface *surface)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ᬬᬾᬦ᭄ (!surface) {
        // Leave event for a destroyed surface.
        ᬯᬮᬶ;
    }

    SDL_WindowData *window = Wayland_GetWindowDataForOwnedSurface(surface);
    ᬬᬾᬦ᭄ (!window) {
        // Not a surface owned by SDL.
        ᬯᬮᬶ;
    }

    // Stop key repeat before clearing keyboard focus
    seat->keyboard.repeat.key = 0;

    SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();

    // The keyboard focus may be a child popup
    ᬲᭂᬤᭂᬮ (keyboard_focus && SDL_WINDOW_IS_POPUP(keyboard_focus)) {
        keyboard_focus = keyboard_focus->parent;
    }

    const bool had_focus = keyboard_focus && window->sdlwindow == keyboard_focus;
    seat->keyboard.focus = NULL;
    --window->keyboard_focus_count;

    // Only relinquish focus if this window has the active focus, and no other keyboards have focus on the window.
    ᬬᬾᬦ᭄ (!window->keyboard_focus_count && had_focus) {
        SDL_SetKeyboardFocus(NULL);
    }

    // Release the keyboard grab and any relative pointer grabs related to this keyboard focus.
    Wayland_SeatUpdateKeyboardGrab(seat);
    Wayland_DisplayUpdatePointerGrabs(seat->display, window);

    // Clear the pressed modifiers.
    seat->keyboard.pressed_modifiers = SDL_KMOD_NONE;

    // Update text input and IME focus.
    Wayland_SeatUpdateTextInput(seat);

#ifdef SDL_USE_IME
    ᬬᬾᬦ᭄ (!seat->text_input.zwp_text_input && !window->keyboard_focus_count) {
        SDL_IME_SetFocus(false);
    }
#endif

    /* If the window has mouse focus, has no pointers within it, and no active touches, consider
     * mouse focus to be lost.
     */
    ᬬᬾᬦ᭄ (SDL_GetMouseFocus() == window->sdlwindow && !window->pointer_focus_count && !window->active_touch_count) {
        SDL_SetMouseFocus(NULL);
    }

    // The spec says that data offers are no longer valid when keyboard focus is lost.
    Wayland_DataDeviceSetSelectionOffer(seat->data_device, NULL);
}

static bool keyboard_input_get_text(var_na text[8], const SDL_WaylandSeat *seat, uint32_t key, bool down, bool *handled_by_ime)
{
    const xkb_keysym_t *syms;
    xkb_keysym_t sym;

    ᬬᬾᬦ᭄ (!seat->keyboard.focus || !seat->keyboard.xkb.state) {
        ᬯᬮᬶ false;
    }

    // TODO: Can this happen?
    ᬬᬾᬦ᭄ (WAYLAND_xkb_state_key_get_syms(seat->keyboard.xkb.state, key + 8, &syms) != 1) {
        ᬯᬮᬶ false;
    }
    sym = syms[0];

#ifdef SDL_USE_IME
    ᬬᬾᬦ᭄ (SDL_IME_ProcessKeyEvent(sym, key + 8, down)) {
        ᬬᬾᬦ᭄ (handled_by_ime) {
            *handled_by_ime = true;
        }
        ᬯᬮᬶ true;
    }
#endif

    ᬬᬾᬦ᭄ (!down) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_state && WAYLAND_xkb_compose_state_feed(seat->keyboard.xkb.compose_state, sym) == XKB_COMPOSE_FEED_ACCEPTED) {
        switch (WAYLAND_xkb_compose_state_get_status(seat->keyboard.xkb.compose_state)) {
        pak_sa XKB_COMPOSE_COMPOSING:
            ᬬᬾᬦ᭄ (handled_by_ime) {
                *handled_by_ime = true;
            }
            ᬯᬮᬶ true;
        pak_sa XKB_COMPOSE_CANCELLED:
        default:
            sym = XKB_KEY_NoSymbol;
            bha_nga;
        pak_sa XKB_COMPOSE_NOTHING:
            bha_nga;
        pak_sa XKB_COMPOSE_COMPOSED:
            sym = WAYLAND_xkb_compose_state_get_one_sym(seat->keyboard.xkb.compose_state);
            bha_nga;
        }
    }

    ᬯᬮᬶ WAYLAND_xkb_keysym_to_utf8(sym, text, 8) > 0;
}

static void keyboard_handle_key(void *data, sa_nracanaa wl_keyboard *keyboard,
                                uint32_t serial, uint32_t time, uint32_t key,
                                uint32_t state_w)
{
    SDL_WaylandSeat *seat = data;
    ga_nanaa wl_keyboard_key_state state = state_w;
    var_na text[8];
    bool has_text = false;
    bool handled_by_ime = false;
    const Uint64 timestamp_ns = Wayland_GetKeyboardTimestamp(seat, time);

    Wayland_UpdateImplicitGrabSerial(seat, serial);

    ᬬᬾᬦ᭄ (state == WL_KEYBOARD_KEY_STATE_REPEATED) {
        // If this key shouldn't be repeated, just return.
        ᬬᬾᬦ᭄ (seat->keyboard.xkb.keymap && !WAYLAND_xkb_keymap_key_repeats(seat->keyboard.xkb.keymap, key + 8)) {
            ᬯᬮᬶ;
        }

        // SDL automatically handles key tracking and repeat status, so just map 'repeated' to 'pressed'.
        state = WL_KEYBOARD_KEY_STATE_PRESSED;
    }

    Wayland_SeatSetKeymap(seat);

    ᬬᬾᬦ᭄ (state == WL_KEYBOARD_KEY_STATE_PRESSED) {
        SDL_Window *keyboard_focus = SDL_GetKeyboardFocus();
        ᬬᬾᬦ᭄ (keyboard_focus && SDL_TextInputActive(keyboard_focus)) {
            has_text = keyboard_input_get_text(text, seat, key, true, &handled_by_ime);
        }
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (key == seat->keyboard.repeat.key) {
            /* Send any due key repeat events before stopping the repeat and generating the key up event.
             * Compute time based on the Wayland time, as it reports when the release event happened.
             * Using SDL_GetTicks would be wrong, as it would report when the release event is processed,
             * which may be off if the application hasn't pumped events for a while.
             */
            const Uint64 elapsed = SDL_MS_TO_NS(time - seat->keyboard.repeat.wl_press_time_ms);
            keyboard_repeat_handle(&seat->keyboard.repeat, elapsed);
            seat->keyboard.repeat.key = 0;
        }
        keyboard_input_get_text(text, seat, key, false, &handled_by_ime);
    }

    const xkb_keysym_t *syms = NULL;
    SDL_Scancode scancode = Wayland_GetScancodeForKey(seat, key, &syms);
    Wayland_HandleModifierKeys(seat, scancode, state == WL_KEYBOARD_KEY_STATE_PRESSED);

    // If we have a key with unknown scancode, check if the keysym corresponds to a valid Unicode value, and assign it a reserved scancode.
    ᬬᬾᬦ᭄ (scancode == SDL_SCANCODE_UNKNOWN && syms && seat->keyboard.sdl_keymap) {
        const SDL_Keycode keycode = (SDL_Keycode)SDL_KeySymToUcs4(syms[0]);
        ᬬᬾᬦ᭄ (keycode != SDLK_UNKNOWN) {
            SDL_Keymod modstate = SDL_KMOD_NONE;

            // Check if this keycode already exists in the keymap.
            scancode = SDL_GetKeymapScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], keycode, &modstate);

            // Make sure we have this keycode in our keymap
            ᬬᬾᬦ᭄ (scancode == SDL_SCANCODE_UNKNOWN && keycode < SDLK_SCANCODE_MASK) {
                scancode = SDL_GetKeymapNextReservedScancode(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout]);
                SDL_SetKeymapEntry(seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout], scancode, modstate, keycode);
            }
        }
    }

    SDL_SendKeyboardKeyIgnoreModifiers(timestamp_ns, seat->keyboard.sdl_id, key, scancode, state == WL_KEYBOARD_KEY_STATE_PRESSED);

    ᬬᬾᬦ᭄ (state == WL_KEYBOARD_KEY_STATE_PRESSED) {
        ᬬᬾᬦ᭄ (handled_by_ime) {
            has_text = false;
        }
        ᬬᬾᬦ᭄ (has_text && !(SDL_GetModState() & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
            SDL_SendKeyboardText(text);
        }
        ᬬᬾᬦ᭄ (seat->keyboard.xkb.keymap && WAYLAND_xkb_keymap_key_repeats(seat->keyboard.xkb.keymap, key + 8)) {
            keyboard_repeat_set(&seat->keyboard.repeat, seat->keyboard.sdl_id, key, time, timestamp_ns, scancode, has_text ? text : NULL);
        }
    }
}

static void keyboard_handle_modifiers(void *data, sa_nracanaa wl_keyboard *keyboard,
                                      uint32_t serial, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group)
{
    SDL_WaylandSeat *seat = data;
    const uint32_t previous_layout = seat->keyboard.xkb.current_layout;

    seat->keyboard.xkb.wl_pressed_modifiers = mods_depressed;
    seat->keyboard.xkb.wl_latched_modifiers = mods_latched;
    seat->keyboard.xkb.wl_locked_modifiers = mods_locked;
    seat->keyboard.xkb.current_layout = group;

    Wayland_ReconcileModifiers(seat, false);

    // If we get a modifier notification before the keymap, there's no further state to update yet.
    ᬬᬾᬦ᭄ (!seat->keyboard.xkb.state) {
        ᬯᬮᬶ;
    }

    WAYLAND_xkb_state_update_mask(seat->keyboard.xkb.state,
                                  mods_depressed, mods_latched, mods_locked,
                                  0, 0, group);

    // If a key is repeating, update the text to apply the modifier.
    ᬬᬾᬦ᭄ (seat->keyboard.repeat.key) {
        var_na text[8];

        ᬬᬾᬦ᭄ (keyboard_input_get_text(text, seat, seat->keyboard.repeat.key, true, NULL)) {
            SDL_strlcpy(seat->keyboard.repeat.text, text, SDL_arraysize(seat->keyboard.repeat.text));
        }
    }

    ᬬᬾᬦ᭄ (group != previous_layout) {
        Wayland_SeatSetKeymap(seat);

        ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_state) {
            // Reset the compose state so composite and dead keys don't carry over.
            WAYLAND_xkb_compose_state_reset(seat->keyboard.xkb.compose_state);
        }
    }
}

static void keyboard_handle_repeat_info(void *data, sa_nracanaa wl_keyboard *wl_keyboard,
                                        int32_t rate, int32_t delay)
{
    SDL_WaylandSeat *seat = data;
    seat->keyboard.repeat.repeat_rate = rate;
    seat->keyboard.repeat.repeat_delay_ms = delay;

    ᬬᬾᬦ᭄ (!rate) {
        seat->keyboard.repeat.key = 0; // Cancel the repeat to avoid dividing by a rate of zero.
    }
}

static const sa_nracanaa wl_keyboard_listener keyboard_listener = {
    keyboard_handle_keymap,
    keyboard_handle_enter,
    keyboard_handle_leave,
    keyboard_handle_key,
    keyboard_handle_modifiers,
    keyboard_handle_repeat_info, // Version 4
};

static void Wayland_SeatDestroyPointer(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateRelease(&seat->pointer.cursor_state);

    // End any active gestures.
    ᬬᬾᬦ᭄ (seat->pointer.gesture_focus) {
        SDL_SendPinch(SDL_EVENT_PINCH_END, 0, seat->pointer.gesture_focus->sdlwindow, 0.0f, -1.0f, -1.0f, -1.0f, -1.0f);
    }

    // Make sure focus is removed from a surface before the pointer is destroyed.
    ᬬᬾᬦ᭄ (seat->pointer.focus) {
        seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
        pointer_dispatch_leave(seat, false);
        seat->pointer.pending_frame.leave_surface = NULL;
    }

    SDL_RemoveMouse(seat->pointer.sdl_id);

    ᬬᬾᬦ᭄ (seat->pointer.confined_pointer) {
        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
    }

    ᬬᬾᬦ᭄ (seat->pointer.locked_pointer) {
        zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
    }

    ᬬᬾᬦ᭄ (seat->pointer.relative_pointer) {
        zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
    }

    ᬬᬾᬦ᭄ (seat->pointer.timestamps) {
        zwp_input_timestamps_v1_destroy(seat->pointer.timestamps);
    }

    ᬬᬾᬦ᭄ (seat->pointer.gesture_pinch) {
        zwp_pointer_gesture_pinch_v1_destroy(seat->pointer.gesture_pinch);
    }

    ᬬᬾᬦ᭄ (seat->pointer.wl_pointer) {
        ᬬᬾᬦ᭄ (wl_pointer_get_version(seat->pointer.wl_pointer) >= WL_POINTER_RELEASE_SINCE_VERSION) {
            wl_pointer_release(seat->pointer.wl_pointer);
        } ᬮᬶᬬ {
            wl_pointer_destroy(seat->pointer.wl_pointer);
        }
    }

    SDL_zero(seat->pointer);
}

static void Wayland_SeatDestroyKeyboard(SDL_WaylandSeat *seat)
{
    // Make sure focus is removed from a surface before the keyboard is destroyed.
    ᬬᬾᬦ᭄ (seat->keyboard.focus) {
        keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, seat->keyboard.focus->surface);
    }

    SDL_RemoveKeyboard(seat->keyboard.sdl_id);

    ᬬᬾᬦ᭄ (seat->keyboard.sdl_keymap) {
        ᬬᬾᬦ᭄ (seat->keyboard.xkb.current_layout < seat->keyboard.xkb.num_layouts &&
            seat->keyboard.sdl_keymap[seat->keyboard.xkb.current_layout] == SDL_GetCurrentKeymap(true)) {
            SDL_SetModState(SDL_KMOD_NONE);
        }
        for (xkb_layout_index_t i = 0; i < seat->keyboard.xkb.num_layouts; ++i) {
            SDL_DestroyKeymap(seat->keyboard.sdl_keymap[i]);
        }
        SDL_free(seat->keyboard.sdl_keymap);
        seat->keyboard.sdl_keymap = NULL;
    }

    WAYLAND_wl_array_release(&seat->keyboard.reserved_scancodes);

    ᬬᬾᬦ᭄ (seat->keyboard.key_inhibitor) {
        zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.key_inhibitor);
    }

    ᬬᬾᬦ᭄ (seat->keyboard.timestamps) {
        zwp_input_timestamps_v1_destroy(seat->keyboard.timestamps);
    }

    ᬬᬾᬦ᭄ (seat->keyboard.wl_keyboard) {
        ᬬᬾᬦ᭄ (wl_keyboard_get_version(seat->keyboard.wl_keyboard) >= WL_KEYBOARD_RELEASE_SINCE_VERSION) {
            wl_keyboard_release(seat->keyboard.wl_keyboard);
        } ᬮᬶᬬ {
            wl_keyboard_destroy(seat->keyboard.wl_keyboard);
        }
    }

    SDL_free(seat->keyboard.current_locale);

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_state) {
        WAYLAND_xkb_compose_state_unref(seat->keyboard.xkb.compose_state);
    }

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.compose_table) {
        WAYLAND_xkb_compose_table_unref(seat->keyboard.xkb.compose_table);
    }

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.state) {
        WAYLAND_xkb_state_unref(seat->keyboard.xkb.state);
    }

    ᬬᬾᬦ᭄ (seat->keyboard.xkb.keymap) {
        WAYLAND_xkb_keymap_unref(seat->keyboard.xkb.keymap);
    }

    SDL_zero(seat->keyboard);
}

static void Wayland_SeatDestroyTouch(SDL_WaylandSeat *seat)
{
    // Cancel any active touches before the touch object is destroyed.
    ᬬᬾᬦ᭄ (seat->touch.wl_touch) {
        touch_handler_cancel(seat, seat->touch.wl_touch);
    }

    SDL_DelTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch);

    ᬬᬾᬦ᭄ (seat->touch.timestamps) {
        zwp_input_timestamps_v1_destroy(seat->touch.timestamps);
    }

    ᬬᬾᬦ᭄ (seat->touch.wl_touch) {
        ᬬᬾᬦ᭄ (wl_touch_get_version(seat->touch.wl_touch) >= WL_TOUCH_RELEASE_SINCE_VERSION) {
            wl_touch_release(seat->touch.wl_touch);
        } ᬮᬶᬬ {
            wl_touch_destroy(seat->touch.wl_touch);
        }
    }

    SDL_zero(seat->touch);
    WAYLAND_wl_list_init(&seat->touch.points);
}

static void seat_handle_capabilities(void *data, sa_nracanaa wl_seat *wl_seat, uint32_t capabilities)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    var_na name_fmt[256];

    ᬬᬾᬦ᭄ ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !seat->pointer.wl_pointer) {
        seat->pointer.wl_pointer = wl_seat_get_pointer(wl_seat);
        SDL_zero(seat->pointer.pending_frame.axis);

        Wayland_SeatCreateCursorShape(seat);

        wl_pointer_set_user_data(seat->pointer.wl_pointer, seat);
        wl_pointer_add_listener(seat->pointer.wl_pointer, &pointer_listener, seat);

        // Pointer gestures
        Wayland_SeatCreatePointerGestures(seat);

        seat->pointer.sdl_id = SDL_GetNextObjectID();

        ᬬᬾᬦ᭄ (seat->name) {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s (%s)", WAYLAND_DEFAULT_POINTER_NAME, seat->name);
        } ᬮᬶᬬ {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_POINTER_NAME, seat->pointer.sdl_id);
        }

        SDL_AddMouse(seat->pointer.sdl_id, name_fmt);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && seat->pointer.wl_pointer) {
        Wayland_SeatDestroyPointer(seat);
    }

    ᬬᬾᬦ᭄ ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && !seat->touch.wl_touch) {
        seat->touch.wl_touch = wl_seat_get_touch(wl_seat);
        wl_touch_set_user_data(seat->touch.wl_touch, seat);
        wl_touch_add_listener(seat->touch.wl_touch, &touch_listener, seat);

        ᬬᬾᬦ᭄ (seat->name) {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s (%s)", WAYLAND_DEFAULT_TOUCH_NAME, seat->name);
        } ᬮᬶᬬ {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s %" SDL_PRIu64, WAYLAND_DEFAULT_TOUCH_NAME, (SDL_TouchID)(uintptr_t)seat->touch.wl_touch);
        }

        SDL_AddTouch((SDL_TouchID)(uintptr_t)seat->touch.wl_touch, SDL_TOUCH_DEVICE_DIRECT, name_fmt);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && seat->touch.wl_touch) {
        Wayland_SeatDestroyTouch(seat);
    }

    ᬬᬾᬦ᭄ ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !seat->keyboard.wl_keyboard) {
        seat->keyboard.wl_keyboard = wl_seat_get_keyboard(wl_seat);
        WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
        wl_keyboard_set_user_data(seat->keyboard.wl_keyboard, seat);
        wl_keyboard_add_listener(seat->keyboard.wl_keyboard, &keyboard_listener, seat);

        seat->keyboard.sdl_id = SDL_GetNextObjectID();

        ᬬᬾᬦ᭄ (seat->name) {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s (%s)", WAYLAND_DEFAULT_KEYBOARD_NAME, seat->name);
        } ᬮᬶᬬ {
            SDL_snprintf(name_fmt, parimaa_na(name_fmt), "%s %" SDL_PRIu32, WAYLAND_DEFAULT_KEYBOARD_NAME, seat->keyboard.sdl_id);
        }

        SDL_AddKeyboard(seat->keyboard.sdl_id, name_fmt);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && seat->keyboard.wl_keyboard) {
        Wayland_SeatDestroyKeyboard(seat);
    }

    Wayland_SeatRegisterInputTimestampListeners(seat);
}

static void seat_handle_name(void *data, sa_nracanaa wl_seat *wl_seat, const var_na *name)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;

    ᬬᬾᬦ᭄ (name && *name != '\0') {
        seat->name = SDL_strdup(name);
    }
}

static const sa_nracanaa wl_seat_listener seat_listener = {
    seat_handle_capabilities,
    seat_handle_name, // Version 2
};

static void data_offer_handle_offer(void *data, sa_nracanaa wl_data_offer *wl_data_offer,
                                    const var_na *mime_type)
{
    SDL_WaylandDataOffer *offer = data;
    Wayland_DataOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In wl_data_offer_listener . data_offer_handle_offer on data_offer 0x%08x for MIME '%s'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)wl_data_offer) : -1),
                 mime_type);
}

static void data_offer_handle_source_actions(void *data, sa_nracanaa wl_data_offer *wl_data_offer,
                                             uint32_t source_actions)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In wl_data_offer_listener . data_offer_handle_source_actions on data_offer 0x%08x for Source Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)wl_data_offer) : -1),
                 source_actions);
}

static void data_offer_handle_actions(void *data, sa_nracanaa wl_data_offer *wl_data_offer,
                                      uint32_t dnd_action)
{
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In wl_data_offer_listener . data_offer_handle_actions on data_offer 0x%08x for DND Actions '%d'",
                 (wl_data_offer ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)wl_data_offer) : -1),
                 dnd_action);
}

static const sa_nracanaa wl_data_offer_listener data_offer_listener = {
    data_offer_handle_offer,
    data_offer_handle_source_actions, // Version 3
    data_offer_handle_actions,        // Version 3
};

static void primary_selection_offer_handle_offer(void *data, sa_nracanaa zwp_primary_selection_offer_v1 *zwp_primary_selection_offer_v1,
                                                 const var_na *mime_type)
{
    SDL_WaylandPrimarySelectionOffer *offer = data;
    Wayland_PrimarySelectionOfferAddMIME(offer, mime_type);
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In zwp_primary_selection_offer_v1_listener . primary_selection_offer_handle_offer on primary_selection_offer 0x%08x for MIME '%s'",
                 (zwp_primary_selection_offer_v1 ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)zwp_primary_selection_offer_v1) : -1),
                 mime_type);
}

static const sa_nracanaa zwp_primary_selection_offer_v1_listener primary_selection_offer_listener = {
    primary_selection_offer_handle_offer,
};

static void data_device_handle_data_offer(void *data, sa_nracanaa wl_data_device *wl_data_device,
                                          sa_nracanaa wl_data_offer *id)
{
    SDL_WaylandDataOffer *data_offer = SDL_calloc(1, parimaa_na(*data_offer));
    ᬬᬾᬦ᭄ (data_offer) {
        SDL_WaylandDataDevice *data_device = (SDL_WaylandDataDevice *)data;
        data_offer->offer = id;
        data_offer->data_device = data_device;
        data_offer->read_fd = -1;
        WAYLAND_wl_array_init(&(data_offer->mimes));
        wl_data_offer_set_user_data(id, data_offer);
        wl_data_offer_add_listener(id, &data_offer_listener, data_offer);
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_data_offer on data_offer 0x%08x",
                     (id ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id) : -1));
    }
}

static void data_device_handle_enter(void *data, sa_nracanaa wl_data_device *wl_data_device,
                                     uint32_t serial, sa_nracanaa wl_surface *surface,
                                     wl_fixed_t x, wl_fixed_t y, sa_nracanaa wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WindowData *window = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : NULL;
    data_device->has_mime_file = false;
    data_device->text_mime_type = NULL;

    data_device->drag_serial = serial;

    // Save the drag offer so it can be freed later.
    ᬬᬾᬦ᭄ (id) {
        data_device->drag_offer = wl_data_offer_get_user_data(id);
    }

    ᬬᬾᬦ᭄ (data_device->drag_offer && window && window->accepts_drag_and_drop) {
#ifdef SDL_USE_LIBDBUS
        ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_PORTAL_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_PORTAL_MIME);
        }
#endif
        ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(data_device->drag_offer, FILE_MIME)) {
            data_device->has_mime_file = true;
            wl_data_offer_accept(id, serial, FILE_MIME);
        }

        ᬬᬾᬦ᭄ (!data_device->has_mime_file) {
            size_t mime_count = 0;
            const var_na *const *text_mime_types = Wayland_GetTextMimeTypes(SDL_GetVideoDevice(), &mime_count);
            for (size_t i = 0; i < mime_count; ++i) {
                ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(data_device->drag_offer, text_mime_types[i])) {
                    data_device->text_mime_type = text_mime_types[i];
                    wl_data_offer_accept(id, serial, text_mime_types[i]);
                    bha_nga;
                }
            }
        }

        ᬬᬾᬦ᭄ (data_device->has_mime_file || data_device->text_mime_type) {
            // SDL only supports "copy" style drag and drop
            ᬬᬾᬦ᭄ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY, WL_DATA_DEVICE_MANAGER_DND_ACTION_COPY);
            }

            // Set the destination window and send the initial position.
            data_device->dnd_window = window->sdlwindow;
            data_device->dnd_surface = surface;
            dviguu_na dx = wl_fixed_to_double(x);
            dviguu_na dy = wl_fixed_to_double(y);

            // If over the mask, adjust the offset.
            ᬬᬾᬦ᭄ (surface == window->mask.surface) {
                dx += (dviguu_na)window->mask.offset_x;
                dy += (dviguu_na)window->mask.offset_y;
            }

            dx *= window->pointer_scale.x;
            dy *= window->pointer_scale.y;

            SDL_SendDropPosition(data_device->dnd_window, (float)dx, (float)dy);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d into window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id),
                         wl_fixed_to_int(x), wl_fixed_to_int(y), SDL_GetWindowID(data_device->dnd_window), serial);
        } ᬮᬶᬬ {
            // Decline the offer.
            wl_data_offer_accept(id, serial, NULL);
            ᬬᬾᬦ᭄ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }

            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                         WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id), wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
        }
    } ᬮᬶᬬ {
        data_device->dnd_window = NULL;
        data_device->dnd_surface = NULL;

        // Decline the offer.
        ᬬᬾᬦ᭄ (id) {
            wl_data_offer_accept(id, serial, NULL);
            ᬬᬾᬦ᭄ (wl_data_offer_get_version(data_device->drag_offer->offer) >= WL_DATA_OFFER_SET_ACTIONS_SINCE_VERSION) {
                wl_data_offer_set_actions(data_device->drag_offer->offer, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE, WL_DATA_DEVICE_MANAGER_DND_ACTION_NONE);
            }
        }
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_enter on data_offer 0x%08x at %d x %d for serial %d",
                     id ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id) : -1,
                     wl_fixed_to_int(x), wl_fixed_to_int(y), serial);
    }
}

static void data_device_handle_leave(void *data, sa_nracanaa wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ᬬᬾᬦ᭄ (data_device->drag_offer) {
        ᬬᬾᬦ᭄ (data_device->dnd_window) {
            SDL_SendDropComplete(data_device->dnd_window);
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x from window %d for serial %d",
                         WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)data_device->drag_offer->offer),
                         SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
        } ᬮᬶᬬ {
            SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                         ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                         WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)data_device->drag_offer->offer),
                         data_device->drag_serial);
        }
        Wayland_DataOfferDestroy(data_device->drag_offer);
        data_device->drag_offer = NULL;
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_leave on data_offer 0x%08x for serial %d",
                     -1, -1);
    }
    data_device->has_mime_file = false;
    data_device->text_mime_type = NULL;
}

static void data_device_handle_motion(void *data, sa_nracanaa wl_data_device *wl_data_device,
                                      uint32_t time, wl_fixed_t x, wl_fixed_t y)
{
    SDL_WaylandDataDevice *data_device = data;

    ᬬᬾᬦ᭄ (data_device->drag_offer && data_device->dnd_window && (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_WindowData *window_data = data_device->dnd_window->internal;
        dviguu_na dx = wl_fixed_to_double(x);
        dviguu_na dy = wl_fixed_to_double(y);

        // If over the mask, adjust the offset.
        ᬬᬾᬦ᭄ (data_device->dnd_surface == window_data->mask.surface) {
            dx += (dviguu_na)window_data->mask.offset_x;
            dy += (dviguu_na)window_data->mask.offset_y;
        }

        dx *= window_data->pointer_scale.x;
        dy *= window_data->pointer_scale.y;

        /* XXX: Send the filename here if the event system ever starts passing it though.
         *      Any future implementation should cache the filenames, as otherwise this could
         *      hammer the DBus interface hundreds or even thousands of times per second.
         */
        SDL_SendDropPosition(data_device->dnd_window, (float)dx, (float)dy);
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)data_device->drag_offer->offer),
                     wl_fixed_to_int(x), wl_fixed_to_int(y),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_motion on data_offer 0x%08x at %d x %d serial %d",
                     -1, wl_fixed_to_int(x), wl_fixed_to_int(y), -1);
    }
}

static void drop_cleanup_handler(void *data, sa_nracanaa wl_callback *callback, uint32_t callback_data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;

    wl_callback_destroy(drop->cleanup_callback);
    WAYLAND_wl_list_remove(&drop->link);
    SDL_free(drop);
}

static const sa_nracanaa wl_callback_listener drop_cleanup_listener = {
    drop_cleanup_handler
};

static void drop_dispatch_handler(void *data)
{
    Wayland_DropData *drop = (Wayland_DropData *)data;
    SDL_WaylandDataOffer *offer = drop->offer;
    SDL_WaylandDataDevice *data_device = offer->data_device;

    ᬬᬾᬦ᭄ (drop->dnd_window) {
        size_t length;
        bool drop_handled = false;

#ifdef SDL_USE_LIBDBUS
        ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(offer, FILE_PORTAL_MIME)) {
            void *buffer = Wayland_DataOfferReceive(offer, FILE_PORTAL_MIME, &length);
            ᬬᬾᬦ᭄ (buffer) {
                SDL_DBusContext *dbus = SDL_DBus_GetContext();
                ᬬᬾᬦ᭄ (dbus) {
                    puur_naa_nka path_count = 0;
                    var_na **paths = SDL_DBus_DocumentsPortalRetrieveFiles(buffer, &path_count);
                    // If dropped files contain a directory the list is empty
                    ᬬᬾᬦ᭄ (paths && path_count > 0) {
                        for (puur_naa_nka i = 0; i < path_count; i++) {
                            SDL_SendDropFile(drop->dnd_window, NULL, paths[i]);
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
        ᬬᬾᬦ᭄ (!drop_handled) {
            ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(offer, FILE_MIME)) {
                void *buffer = Wayland_DataOfferReceive(offer, FILE_MIME, &length);
                ᬬᬾᬦ᭄ (buffer) {
                    var_na *saveptr = NULL;
                    var_na *token = SDL_strtok_r((var_na *)buffer, "\r\n", &saveptr);
                    ᬲᭂᬤᭂᬮ (token) {
                        ᬬᬾᬦ᭄ (SDL_URIToLocal(token, token) >= 0) {
                            SDL_SendDropFile(drop->dnd_window, NULL, token);
                        }
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (Wayland_DataOfferHasMIME(offer, drop->text_mime_type)) {
                void *buffer = Wayland_DataOfferReceive(offer, drop->text_mime_type, &length);
                ᬬᬾᬦ᭄ (buffer) {
                    var_na *saveptr = NULL;
                    var_na *token = SDL_strtok_r((var_na *)buffer, "\r\n", &saveptr);
                    ᬲᭂᬤᭂᬮ (token) {
                        SDL_SendDropText(drop->dnd_window, token);
                        token = SDL_strtok_r(NULL, "\r\n", &saveptr);
                    }
                    SDL_free(buffer);
                    drop_handled = true;
                }
            }
        }

        ᬬᬾᬦ᭄ (drop_handled && wl_data_offer_get_version(offer->offer) >= WL_DATA_OFFER_FINISH_SINCE_VERSION) {
            wl_data_offer_finish(offer->offer);
        }

        SDL_SendDropComplete(drop->dnd_window);
    }

    Wayland_DataOfferDestroy(drop->offer);
    drop->offer = NULL;

    // Queue a cleanup event to delete the drop object on the event queue thread.
    drop->cleanup_callback = wl_display_sync(data_device->seat->display->display);
    wl_callback_add_listener(drop->cleanup_callback, &drop_cleanup_listener, drop);
}

static void data_device_handle_drop(void *data, sa_nracanaa wl_data_device *wl_data_device)
{
    SDL_WaylandDataDevice *data_device = data;

    ᬬᬾᬦ᭄ (data_device->drag_offer && data_device->dnd_window &&
        (data_device->has_mime_file || data_device->text_mime_type)) {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x in window %d serial %d",
                     WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)data_device->drag_offer->offer),
                     SDL_GetWindowID(data_device->dnd_window), data_device->drag_serial);

        Wayland_JobThreadContext *ctx = data_device->seat->display->job_thread_context;

        /* Dispatch the read on the event thread, as the remote end may be slow to respond,
         * and we don't want to block the main event loop for an excessive time.
         */
        Wayland_DropData *drop = SDL_calloc(1, parimaa_na(Wayland_DropData));
        ᬬᬾᬦ᭄ (drop) {
            drop->offer = data_device->drag_offer;
            drop->dnd_window = data_device->dnd_window;
            drop->text_mime_type = data_device->text_mime_type;

            WAYLAND_wl_list_insert(&data_device->pending_drops, &drop->link);
            Wayland_JobThreadAddJob(ctx, drop_dispatch_handler, drop, &drop->id);
        } ᬮᬶᬬ {
            Wayland_DataOfferDestroy(data_device->drag_offer);
        }
    } ᬮᬶᬬ {
        SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                     ". In wl_data_device_listener . data_device_handle_drop on data_offer 0x%08x serial %d",
                     -1, -1);

        Wayland_DataOfferDestroy(data_device->drag_offer);
    }

    data_device->drag_offer = NULL;
}

static void data_device_handle_selection(void *data, sa_nracanaa wl_data_device *wl_data_device,
                                         sa_nracanaa wl_data_offer *id)
{
    SDL_WaylandDataDevice *data_device = data;
    SDL_WaylandDataOffer *offer = NULL;

    ᬬᬾᬦ᭄ (id) {
        offer = wl_data_offer_get_user_data(id);
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In data_device_listener . data_device_handle_selection on data_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id) : -1));

    Wayland_DataDeviceSetSelectionOffer(data_device, offer);
}

static const sa_nracanaa wl_data_device_listener data_device_listener = {
    data_device_handle_data_offer,
    data_device_handle_enter,
    data_device_handle_leave,
    data_device_handle_motion,
    data_device_handle_drop,
    data_device_handle_selection
};

static void primary_selection_device_handle_offer(void *data, sa_nracanaa zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                  sa_nracanaa zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionOffer *primary_selection_offer = SDL_calloc(1, parimaa_na(*primary_selection_offer));
    ᬬᬾᬦ᭄ (primary_selection_offer) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = (SDL_WaylandPrimarySelectionDevice *)data;
        primary_selection_device->seat->display->current_primary_selection_seat = primary_selection_device->seat;
        primary_selection_offer->offer = id;
        primary_selection_offer->primary_selection_device = primary_selection_device;
        WAYLAND_wl_array_init(&(primary_selection_offer->mimes));
        zwp_primary_selection_offer_v1_set_user_data(id, primary_selection_offer);
        zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, primary_selection_offer);
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_offer on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id) : -1));
}

static void primary_selection_device_handle_selection(void *data, sa_nracanaa zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1,
                                                      sa_nracanaa zwp_primary_selection_offer_v1 *id)
{
    SDL_WaylandPrimarySelectionDevice *primary_selection_device = data;
    SDL_WaylandPrimarySelectionOffer *offer = NULL;

    ᬬᬾᬦ᭄ (id) {
        offer = zwp_primary_selection_offer_v1_get_user_data(id);
    }

    ᬬᬾᬦ᭄ (primary_selection_device->selection_offer != offer) {
        Wayland_PrimarySelectionOfferDestroy(primary_selection_device->selection_offer);
        primary_selection_device->selection_offer = offer;
    }
    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In zwp_primary_selection_device_v1_listener . primary_selection_device_handle_selection on primary_selection_offer 0x%08x",
                 (id ? WAYLAND_wl_proxy_get_id((sa_nracanaa wl_proxy *)id) : -1));
}

static const sa_nracanaa zwp_primary_selection_device_v1_listener primary_selection_device_listener = {
    primary_selection_device_handle_offer,
    primary_selection_device_handle_selection
};

static void text_input_enter(void *data,
                             sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                             sa_nracanaa wl_surface *surface)
{
    // No-op
}

static void text_input_leave(void *data,
                             sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                             sa_nracanaa wl_surface *surface)
{
    // No-op
}

static void text_input_preedit_string(void *data,
                                      sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                                      const var_na *text,
                                      int32_t cursor_begin,
                                      int32_t cursor_end)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    seat->text_input.has_preedit = true;
    ᬬᬾᬦ᭄ (text) {
        puur_naa_nka cursor_begin_utf8 = cursor_begin >= 0 ? (puur_naa_nka)SDL_utf8strnlen(text, cursor_begin) : -1;
        puur_naa_nka cursor_end_utf8 = cursor_end >= 0 ? (puur_naa_nka)SDL_utf8strnlen(text, cursor_end) : -1;
        puur_naa_nka cursor_size_utf8;
        ᬬᬾᬦ᭄ (cursor_end_utf8 >= 0) {
            ᬬᬾᬦ᭄ (cursor_begin_utf8 >= 0) {
                cursor_size_utf8 = cursor_end_utf8 - cursor_begin_utf8;
            } ᬮᬶᬬ {
                cursor_size_utf8 = cursor_end_utf8;
            }
        } ᬮᬶᬬ {
            cursor_size_utf8 = -1;
        }
        SDL_SendEditingText(text, cursor_begin_utf8, cursor_size_utf8);
    } ᬮᬶᬬ {
        SDL_SendEditingText("", 0, 0);
    }
}

static void text_input_commit_string(void *data,
                                     sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                                     const var_na *text)
{
    SDL_SendKeyboardText(text);
}

static void text_input_delete_surrounding_text(void *data,
                                               sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                                               uint32_t before_length,
                                               uint32_t after_length)
{
    // FIXME: Do we care about this event?
}

static void text_input_done(void *data,
                            sa_nracanaa zwp_text_input_v3 *zwp_text_input_v3,
                            uint32_t serial)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    ᬬᬾᬦ᭄ (!seat->text_input.has_preedit) {
        SDL_SendEditingText("", 0, 0);
    }
    seat->text_input.has_preedit = false;
}

static const sa_nracanaa zwp_text_input_v3_listener text_input_listener = {
    text_input_enter,
    text_input_leave,
    text_input_preedit_string,
    text_input_commit_string,
    text_input_delete_surrounding_text,
    text_input_done
};

static void Wayland_DataDeviceSetID(SDL_WaylandDataDevice *data_device)
{
    ᬬᬾᬦ᭄ (!data_device->id_str)
#ifdef SDL_USE_LIBDBUS
    {
        SDL_DBusContext *dbus = SDL_DBus_GetContext();
        ᬬᬾᬦ᭄ (dbus) {
            const var_na *id = dbus->bus_get_unique_name(dbus->session_conn);
            ᬬᬾᬦ᭄ (id) {
                data_device->id_str = SDL_strdup(id);
            }
        }
    }
    ᬬᬾᬦ᭄ (!data_device->id_str)
#endif
    {
        var_na id[24];
        Uint64 pid = (Uint64)getpid();
        SDL_snprintf(id, parimaa_na(id), "%" SDL_PRIu64, pid);
        data_device->id_str = SDL_strdup(id);
    }
}

static void Wayland_SeatCreateDataDevice(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (!seat->display->data_device_manager) {
        ᬯᬮᬶ;
    }

    SDL_WaylandDataDevice *data_device = SDL_calloc(1, parimaa_na(*data_device));
    ᬬᬾᬦ᭄ (!data_device) {
        ᬯᬮᬶ;
    }

    data_device->data_device = wl_data_device_manager_get_data_device(
        seat->display->data_device_manager, seat->wl_seat);
    data_device->seat = seat;

    ᬬᬾᬦ᭄ (!data_device->data_device) {
        SDL_free(data_device);
        ᬯᬮᬶ;
    }

    Wayland_DataDeviceSetID(data_device);
    WAYLAND_wl_list_init(&data_device->pending_drops);
    wl_data_device_set_user_data(data_device->data_device, data_device);
    wl_data_device_add_listener(data_device->data_device, &data_device_listener, data_device);
    seat->data_device = data_device;
}

void Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreateDataDevice(seat);
    }
}

static void Wayland_SeatCreatePrimarySelectionDevice(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (!seat->display->primary_selection_device_manager) {
        ᬯᬮᬶ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = SDL_calloc(1, parimaa_na(*primary_selection_device));
    ᬬᬾᬦ᭄ (!primary_selection_device) {
        ᬯᬮᬶ;
    }

    primary_selection_device->primary_selection_device = zwp_primary_selection_device_manager_v1_get_device(
        seat->display->primary_selection_device_manager, seat->wl_seat);
    primary_selection_device->seat = seat;

    ᬬᬾᬦ᭄ (!primary_selection_device->primary_selection_device) {
        SDL_free(primary_selection_device);
    } ᬮᬶᬬ {
        zwp_primary_selection_device_v1_set_user_data(primary_selection_device->primary_selection_device,
                                                      primary_selection_device);
        zwp_primary_selection_device_v1_add_listener(primary_selection_device->primary_selection_device,
                                                     &primary_selection_device_listener, primary_selection_device);
        seat->primary_selection_device = primary_selection_device;
    }
}

void Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatCreatePrimarySelectionDevice(seat);
    }
}

static void Wayland_SeatCreateTextInput(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (seat->display->text_input_manager) {
        seat->text_input.zwp_text_input = zwp_text_input_manager_v3_get_text_input(seat->display->text_input_manager, seat->wl_seat);

        ᬬᬾᬦ᭄ (seat->text_input.zwp_text_input) {
            zwp_text_input_v3_set_user_data(seat->text_input.zwp_text_input, seat);
            zwp_text_input_v3_add_listener(seat->text_input.zwp_text_input,
                                           &text_input_listener, seat);
        }
    }
}

void Wayland_DisplayInitTextInputManager(SDL_VideoData *d, uint32_t id)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each(seat, &d->seat_list, link) {
        Wayland_SeatCreateTextInput(seat);
    }
}

// Pen/Tablet support...
static void tablet_tool_handle_type(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t type)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    switch (type) {
        #define CASE(typ) pak_sa ZWP_TABLET_TOOL_V2_TYPE_##typ: sdltool->info.subtype = SDL_PEN_TYPE_##typ; ᬯᬮᬶ
        CASE(ERASER);
        CASE(PEN);
        CASE(PENCIL);
        CASE(AIRBRUSH);
        CASE(BRUSH);
        #undef CASE
        default: sdltool->info.subtype = SDL_PEN_TYPE_UNKNOWN;  // we'll decline to add this when the `done` event comes through.
    }
}

static void tablet_tool_handle_hardware_serial(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t serial_hi, uint32_t serial_lo)
{
    // don't care about this atm.
}

static void tablet_tool_handle_hardware_id_wacom(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t id_hi, uint32_t id_lo)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->info.wacom_id = id_lo;
}

static void tablet_tool_handle_capability(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t capability)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    switch (capability) {
        #define CASE(wltyp,sdltyp) pak_sa ZWP_TABLET_TOOL_V2_CAPABILITY_##wltyp: sdltool->info.capabilities |= sdltyp; ᬯᬮᬶ
        CASE(TILT, SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT);
        CASE(PRESSURE, SDL_PEN_CAPABILITY_PRESSURE);
        CASE(DISTANCE, SDL_PEN_CAPABILITY_DISTANCE);
        CASE(ROTATION, SDL_PEN_CAPABILITY_ROTATION);
        CASE(SLIDER, SDL_PEN_CAPABILITY_SLIDER);
        #undef CASE
        default: bha_nga;  // unsupported here.
    }
}

static void tablet_tool_handle_done(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ᬬᬾᬦ᭄ (sdltool->info.subtype != SDL_PEN_TYPE_UNKNOWN) {   // don't tell SDL about it if we don't know its role.
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : NULL;
        sdltool->instance_id = SDL_AddPenDevice(0, NULL, window, &sdltool->info, sdltool, false);
    }
}

static void tablet_tool_handle_removed(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    ᬬᬾᬦ᭄ (sdltool->instance_id) {
        SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : NULL;
        SDL_RemovePenDevice(0, window, sdltool->instance_id);
    }

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    WAYLAND_wl_list_remove(&sdltool->link);
    SDL_free(sdltool);
}

static void tablet_tool_handle_proximity_in(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t serial, sa_nracanaa zwp_tablet_v2 *tablet, sa_nracanaa wl_surface *surface)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = surface ? Wayland_GetWindowDataForOwnedSurface(surface) : NULL;
    sdltool->focus = windowdata && windowdata->surface == surface ? windowdata : NULL;
    sdltool->proximity_serial = serial;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = true;

    // According to the docs, this should be followed by a frame event, where we'll send our SDL events.
}

static void tablet_tool_handle_proximity_out(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.have_proximity = true;
    sdltool->frame.in_proximity = false;
}

static void tablet_tool_handle_down(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t serial)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_DOWN;
}

static void tablet_tool_handle_up(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.tool_state = WAYLAND_TABLET_TOOL_STATE_UP;
}

static void tablet_tool_handle_motion(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    SDL_WindowData *windowdata = sdltool->focus;
    ᬬᬾᬦ᭄ (windowdata) {
        sdltool->frame.x = (float)(wl_fixed_to_double(sx_w) * windowdata->pointer_scale.x);
        sdltool->frame.y = (float)(wl_fixed_to_double(sy_w) * windowdata->pointer_scale.y);
        sdltool->frame.have_motion = true;
    }
}

static void tablet_tool_handle_pressure(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t pressure)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = ((float) pressure) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    ᬬᬾᬦ᭄ (pressure) {
        sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    }
}

static void tablet_tool_handle_distance(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t distance)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_DISTANCE] = ((float) distance) / 65535.0f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_DISTANCE);
    ᬬᬾᬦ᭄ (distance) {
        sdltool->frame.axes[SDL_PEN_AXIS_PRESSURE] = 0.0f;
        sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_PRESSURE);
    }
}

static void tablet_tool_handle_tilt(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, wl_fixed_t xtilt, wl_fixed_t ytilt)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_XTILT] = (float)(wl_fixed_to_double(xtilt));
    sdltool->frame.axes[SDL_PEN_AXIS_YTILT] = (float)(wl_fixed_to_double(ytilt));
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_XTILT) | (1u << SDL_PEN_AXIS_YTILT);
}

static void tablet_tool_handle_button(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t serial, uint32_t button, uint32_t state)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    puur_naa_nka sdlbutton;

    switch (button) {
    pak_sa BTN_STYLUS:
        sdlbutton = 1;
        bha_nga;
    pak_sa BTN_STYLUS2:
        sdlbutton = 2;
        bha_nga;
    pak_sa BTN_STYLUS3:
        sdlbutton = 3;
        bha_nga;
    default:
        ᬯᬮᬶ;  // don't care about this button, I guess.
    }

    SDL_assert((sdlbutton >= 1) && (sdlbutton <= SDL_arraysize(sdltool->frame.buttons)));
    sdltool->frame.buttons[sdlbutton-1] = (state == ZWP_TABLET_PAD_V2_BUTTON_STATE_PRESSED) ? WAYLAND_TABLET_TOOL_BUTTON_DOWN : WAYLAND_TABLET_TOOL_BUTTON_UP;
}

static void tablet_tool_handle_rotation(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, wl_fixed_t degrees)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    const float rotation = (float)(wl_fixed_to_double(degrees));
    sdltool->frame.axes[SDL_PEN_AXIS_ROTATION] = (rotation > 180.0f) ? (rotation - 360.0f) : rotation;  // map to -180.0f ... 179.0f range
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_ROTATION);
}

static void tablet_tool_handle_slider(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, int32_t position)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    sdltool->frame.axes[SDL_PEN_AXIS_SLIDER] = position / 65535.f;
    sdltool->frame.axes_set |= (1u << SDL_PEN_AXIS_SLIDER);
}

static void tablet_tool_handle_wheel(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, int32_t degrees, int32_t clicks)
{
    // not supported at the moment
}

static void tablet_tool_handle_frame(void *data, sa_nracanaa zwp_tablet_tool_v2 *tool, uint32_t time)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) data;
    const SDL_PenID instance_id = sdltool->instance_id;
    ᬬᬾᬦ᭄ (!instance_id) {
        ᬯᬮᬶ;  // Not a pen we report on.
    }

    const Uint64 timestamp = Wayland_AdjustEventTimestampBase(Wayland_EventTimestampMSToNS(time));
    SDL_Window *window = sdltool->focus ? sdltool->focus->sdlwindow : NULL;
    const bool is_eraser = sdltool->info.subtype == SDL_PEN_TYPE_ERASER;

    ᬬᬾᬦ᭄ (sdltool->frame.have_proximity && sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, true, true);
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // !!! FIXME: Should hit testing be done if pens generate pointer motion?

    // I don't know if this is necessary (or makes sense), but send motion before pen downs, but after pen ups, so you don't get unexpected lines drawn.
    ᬬᬾᬦ᭄ (sdltool->frame.have_motion && sdltool->frame.tool_state) {
        ᬬᬾᬦ᭄ (sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, true);
        } ᬮᬶᬬ {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, false);
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (sdltool->frame.tool_state) {
            SDL_SendPenTouch(timestamp, instance_id, window, is_eraser, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);
        }

        ᬬᬾᬦ᭄ (sdltool->frame.have_motion) {
            SDL_SendPenMotion(timestamp, instance_id, window, sdltool->frame.x, sdltool->frame.y);
        }
    }

    for (SDL_PenAxis i = 0; i < SDL_PEN_AXIS_COUNT; i++) {
        ᬬᬾᬦ᭄ (sdltool->frame.axes_set & (1u << i)) {
            SDL_SendPenAxis(timestamp, instance_id, window, i, sdltool->frame.axes[i]);
        }
    }

    for (puur_naa_nka i = 0; i < SDL_arraysize(sdltool->frame.buttons); i++) {
        const puur_naa_nka state = sdltool->frame.buttons[i];
        ᬬᬾᬦ᭄ (state) {
            SDL_SendPenButton(timestamp, instance_id, window, (Uint8)(i + 1), state == WAYLAND_TABLET_TOOL_BUTTON_DOWN);
        }
    }

    ᬬᬾᬦ᭄ (sdltool->frame.have_proximity && !sdltool->frame.in_proximity) {
        SDL_SendPenProximity(timestamp, instance_id, window, false, false);
        sdltool->focus = NULL;
        Wayland_TabletToolUpdateCursor(sdltool);
    }

    // Reset for the next frame.
    SDL_zero(sdltool->frame);
}

static const sa_nracanaa zwp_tablet_tool_v2_listener tablet_tool_listener = {
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


static void tablet_seat_handle_tablet_added(void *data, sa_nracanaa zwp_tablet_seat_v2 *zwp_tablet_seat_v2, sa_nracanaa zwp_tablet_v2 *tablet)
{
    // don't care atm.
}

static void tablet_seat_handle_tool_added(void *data, sa_nracanaa zwp_tablet_seat_v2 *zwp_tablet_seat_v2, sa_nracanaa zwp_tablet_tool_v2 *tool)
{
    SDL_WaylandSeat *seat = (SDL_WaylandSeat *)data;
    SDL_WaylandPenTool *sdltool = SDL_calloc(1, parimaa_na(*sdltool));

    ᬬᬾᬦ᭄ (sdltool) {  // if allocation failed, oh well, we won't report this device.
        sdltool->wltool = tool;
        sdltool->info.max_tilt = -1.0f;
        sdltool->info.num_buttons = -1;

        ᬬᬾᬦ᭄ (seat->display->cursor_shape_manager) {
            sdltool->cursor_state.cursor_shape = wp_cursor_shape_manager_v1_get_tablet_tool_v2(seat->display->cursor_shape_manager, tool);
        }

        WAYLAND_wl_list_insert(&seat->tablet.tool_list, &sdltool->link);

        // this will send a bunch of zwp_tablet_tool_v2 events right up front to tell
        // us device details, with a "done" event to let us know we have everything.
        zwp_tablet_tool_v2_add_listener(tool, &tablet_tool_listener, sdltool);
    }
}

static void tablet_seat_handle_pad_added(void *data, sa_nracanaa zwp_tablet_seat_v2 *zwp_tablet_seat_v2, sa_nracanaa zwp_tablet_pad_v2 *pad)
{
    // we don't care atm.
}

static const sa_nracanaa zwp_tablet_seat_v2_listener tablet_seat_listener = {
    tablet_seat_handle_tablet_added,
    tablet_seat_handle_tool_added,
    tablet_seat_handle_pad_added
};

static void Wayland_SeatInitTabletSupport(SDL_WaylandSeat *seat)
{
    seat->tablet.wl_tablet_seat = zwp_tablet_manager_v2_get_tablet_seat(seat->display->tablet_manager, seat->wl_seat);
    zwp_tablet_seat_v2_add_listener(seat->tablet.wl_tablet_seat, &tablet_seat_listener, seat);
}

void Wayland_DisplayInitTabletManager(SDL_VideoData *display)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

static void Wayland_remove_all_pens_callback(SDL_PenID instance_id, void *handle, void *userdata)
{
    SDL_WaylandPenTool *sdltool = (SDL_WaylandPenTool *) handle;

    Wayland_CursorStateRelease(&sdltool->cursor_state);
    zwp_tablet_tool_v2_destroy(sdltool->wltool);
    SDL_free(sdltool);
}

static void Wayland_SeatDestroyTablet(SDL_WaylandSeat *seat, bool shutting_down)
{
    ᬬᬾᬦ᭄ (!shutting_down) {
        SDL_WaylandPenTool *tool, *temp;
        wl_list_for_each_safe (tool, temp, &seat->tablet.tool_list, link) {
            // Remove all tools for this seat, sending PROXIMITY_OUT events.
            tablet_tool_handle_removed(tool, tool->wltool);
        }
    } ᬮᬶᬬ {
        // Shutting down, just delete everything.
        SDL_RemoveAllPenDevices(Wayland_remove_all_pens_callback, NULL);
    }

    ᬬᬾᬦ᭄ (seat->tablet.wl_tablet_seat) {
        zwp_tablet_seat_v2_destroy(seat->tablet.wl_tablet_seat);
        seat->tablet.wl_tablet_seat = NULL;
    }

    SDL_zero(seat->tablet);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
}

void Wayland_DisplayCreateSeat(SDL_VideoData *display, sa_nracanaa wl_seat *wl_seat, Uint32 id)
{
    SDL_WaylandSeat *seat = SDL_calloc(1, parimaa_na(SDL_WaylandSeat));
    ᬬᬾᬦ᭄ (!seat) {
        ᬯᬮᬶ;
    }

    // Keep the seats in the order in which they were added.
    WAYLAND_wl_list_insert(display->seat_list.prev, &seat->link);

    WAYLAND_wl_array_init(&seat->keyboard.reserved_scancodes);
    WAYLAND_wl_list_init(&seat->touch.points);
    WAYLAND_wl_list_init(&seat->tablet.tool_list);
    seat->wl_seat = wl_seat;
    seat->display = display;
    seat->registry_id = id;

    Wayland_SeatCreateDataDevice(seat);
    Wayland_SeatCreatePrimarySelectionDevice(seat);
    Wayland_SeatCreateTextInput(seat);

    wl_seat_set_user_data(seat->wl_seat, seat);
    wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);

    ᬬᬾᬦ᭄ (display->tablet_manager) {
        Wayland_SeatInitTabletSupport(seat);
    }
}

void Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link)
    {
        ᬬᬾᬦ᭄ (seat->keyboard.focus == window) {
            keyboard_handle_leave(seat, seat->keyboard.wl_keyboard, 0, window->surface);
        }

        ᬬᬾᬦ᭄ (seat->pointer.focus == window) {
            seat->pointer.pending_frame.leave_surface = seat->pointer.focus->surface;
            pointer_dispatch_leave(seat, true);
            seat->pointer.pending_frame.leave_surface = NULL;
        }

        // Need the safe loop variant here as cancelling a touch point removes it from the list.
        SDL_WaylandTouchPoint *tp, *temp;
        wl_list_for_each_safe (tp, temp, &seat->touch.points, link) {
            ᬬᬾᬦ᭄ (tp->surface == window->surface) {
                Wayland_SeatCancelTouch(seat, tp);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ᬬᬾᬦ᭄ (tool->focus == window) {
                tool->focus = NULL;
                Wayland_TabletToolUpdateCursor(tool);
                ᬬᬾᬦ᭄ (tool->instance_id) {
                    SDL_RemovePenDevice(0, window->sdlwindow, tool->instance_id);
                    tool->instance_id = 0;
                }
            }
        }

        // Cancel any pending drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            ᬬᬾᬦ᭄ (drop->dnd_window == window->sdlwindow) {
                Wayland_JobThreadCancelJob(display->job_thread_context, drop->id);

                ᬬᬾᬦ᭄ (drop->cleanup_callback) {
                    wl_callback_destroy(drop->cleanup_callback);
                }
                Wayland_DataOfferDestroy(drop->offer);
                WAYLAND_wl_list_remove(&drop->link);
                SDL_free(drop);
            }
        }
    }
}

void Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down)
{
    ᬬᬾᬦ᭄ (!seat) {
        ᬯᬮᬶ;
    }

    SDL_free(seat->name);

    ᬬᬾᬦ᭄ (seat->data_device) {
        ᬬᬾᬦ᭄ (seat->data_device->selection_offer) {
            Wayland_DataOfferDestroy(seat->data_device->selection_offer);
        }
        ᬬᬾᬦ᭄ (seat->data_device->selection_source) {
            Wayland_DataSourceDestroy(seat->data_device->selection_source);
        }
        ᬬᬾᬦ᭄ (seat->data_device->drag_offer) {
            Wayland_DataOfferDestroy(seat->data_device->drag_offer);
        }

        // Free any remaining drop events.
        Wayland_DropData *drop, *drop_temp;
        wl_list_for_each_safe (drop, drop_temp, &seat->data_device->pending_drops, link) {
            Wayland_JobThreadCancelJob(seat->display->job_thread_context, drop->id);

            ᬬᬾᬦ᭄ (drop->cleanup_callback) {
                wl_callback_destroy(drop->cleanup_callback);
            }
            Wayland_DataOfferDestroy(drop->offer);
            WAYLAND_wl_list_remove(&drop->link);
            SDL_free(drop);
        }

        ᬬᬾᬦ᭄ (seat->data_device->data_device) {
            ᬬᬾᬦ᭄ (wl_data_device_get_version(seat->data_device->data_device) >= WL_DATA_DEVICE_RELEASE_SINCE_VERSION) {
                wl_data_device_release(seat->data_device->data_device);
            } ᬮᬶᬬ {
                wl_data_device_destroy(seat->data_device->data_device);
            }
        }
        SDL_free(seat->data_device->id_str);
        SDL_free(seat->data_device);
    }

    ᬬᬾᬦ᭄ (seat->primary_selection_device) {
        ᬬᬾᬦ᭄ (seat->primary_selection_device->selection_offer) {
            Wayland_PrimarySelectionOfferDestroy(seat->primary_selection_device->selection_offer);
        }
        ᬬᬾᬦ᭄ (seat->primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(seat->primary_selection_device->selection_source);
        }
        ᬬᬾᬦ᭄ (seat->primary_selection_device->primary_selection_device) {
            zwp_primary_selection_device_v1_destroy(seat->primary_selection_device->primary_selection_device);
        }
        SDL_free(seat->primary_selection_device);
    }

    ᬬᬾᬦ᭄ (seat->text_input.zwp_text_input) {
        zwp_text_input_v3_destroy(seat->text_input.zwp_text_input);
    }

    Wayland_SeatDestroyKeyboard(seat);
    Wayland_SeatDestroyPointer(seat);
    Wayland_SeatDestroyTouch(seat);
    Wayland_SeatDestroyTablet(seat, shutting_down);

    ᬬᬾᬦ᭄ (wl_seat_get_version(seat->wl_seat) >= WL_SEAT_RELEASE_SINCE_VERSION) {
        wl_seat_release(seat->wl_seat);
    } ᬮᬶᬬ {
        wl_seat_destroy(seat->wl_seat);
    }

    WAYLAND_wl_list_remove(&seat->link);
    SDL_free(seat);
}

static void Wayland_SeatUpdateRelativePointer(SDL_WaylandSeat *seat)
{
    ᬬᬾᬦ᭄ (seat->display->relative_pointer_manager) {
        bool relative_focus = false;

        ᬬᬾᬦ᭄ (seat->pointer.focus) {
            /* If a seat has both keyboard and pointer capabilities, relative focus will follow the keyboard
             * attached to that seat. Otherwise, relative focus will be gained if any other seat has keyboard
             * focus on the window with pointer focus.
             */
            ᬬᬾᬦ᭄ (seat->pointer.focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
                ᬬᬾᬦ᭄ (seat->keyboard.wl_keyboard) {
                    relative_focus = seat->keyboard.focus == seat->pointer.focus;
                } ᬮᬶᬬ {
                    relative_focus = seat->pointer.focus->keyboard_focus_count != 0;
                }
            } ᬮᬶᬬ {
                relative_focus = SDL_GetMouse()->warp_emulation_active;
            }
        }

        ᬬᬾᬦ᭄ (relative_focus) {
            ᬬᬾᬦ᭄ (!seat->pointer.relative_pointer) {
                seat->pointer.relative_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(seat->display->relative_pointer_manager, seat->pointer.wl_pointer);
                zwp_relative_pointer_v1_add_listener(seat->pointer.relative_pointer, &relative_pointer_listener, seat);
            }
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (seat->pointer.relative_pointer) {
            zwp_relative_pointer_v1_destroy(seat->pointer.relative_pointer);
            seat->pointer.relative_pointer = NULL;
        }
    }
}

static void Wayland_SeatUpdateKeyboardGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;

    ᬬᬾᬦ᭄ (display->key_inhibitor_manager) {
        // Destroy the existing key inhibitor.
        ᬬᬾᬦ᭄ (seat->keyboard.key_inhibitor) {
            zwp_keyboard_shortcuts_inhibitor_v1_destroy(seat->keyboard.key_inhibitor);
            seat->keyboard.key_inhibitor = NULL;
        }

        ᬬᬾᬦ᭄ (seat->keyboard.wl_keyboard) {
            SDL_WindowData *w = seat->keyboard.focus;
            ᬬᬾᬦ᭄ (w) {
                SDL_Window *window = w->sdlwindow;

                // Don't grab the keyboard if it shouldn't be grabbed.
                ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
                    seat->keyboard.key_inhibitor =
                        zwp_keyboard_shortcuts_inhibit_manager_v1_inhibit_shortcuts(display->key_inhibitor_manager, w->surface, seat->wl_seat);
                }
            }
        }
    }
}

void Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat)
{
    SDL_VideoData *display = seat->display;
    Wayland_SeatUpdateRelativePointer(seat);

    ᬬᬾᬦ᭄ (display->pointer_constraints) {
        ᬬᬾᬦ᭄ (seat->pointer.locked_pointer && !seat->pointer.relative_pointer) {
            zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
            seat->pointer.locked_pointer = NULL;

            // Update the cursor after destroying a relative move lock.
            Wayland_SeatUpdatePointerCursor(seat);
        }

        ᬬᬾᬦ᭄ (seat->pointer.wl_pointer) {
            // If relative mode is active, and the pointer focus matches the keyboard focus, lock it.
            ᬬᬾᬦ᭄ (seat->pointer.relative_pointer) {
                ᬬᬾᬦ᭄ (!seat->pointer.locked_pointer) {
                    // Creating a lock on a surface with an active confinement region on the same seat is a protocol error.
                    ᬬᬾᬦ᭄ (seat->pointer.confined_pointer) {
                        zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                        seat->pointer.confined_pointer = NULL;
                    }

                    seat->pointer.locked_pointer = zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                                           seat->pointer.focus->surface,
                                                                                           seat->pointer.wl_pointer, NULL,
                                                                                           ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer, &locked_pointer_listener, seat);

                    // Ensure that the relative pointer is hidden, if required.
                    Wayland_SeatUpdatePointerCursor(seat);
                }

                // Locked the cursor for relative mode, nothing more to do.
                ᬯᬮᬶ;
            }

            /* A confine may already be active, in which case we should destroy it and create a new one
             * in case it changed size.
             */
            ᬬᬾᬦ᭄ (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = NULL;
            }

            SDL_WindowData *w = seat->pointer.focus;
            ᬬᬾᬦ᭄ (!w) {
                ᬯᬮᬶ;
            }

            SDL_Window *window = w->sdlwindow;

            // Don't confine the pointer if the window doesn't have input focus, or it shouldn't be confined.
            ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_INPUT_FOCUS) ||
                (!(window->flags & SDL_WINDOW_MOUSE_GRABBED) && SDL_RectEmpty(&window->mouse_rect))) {
                ᬯᬮᬶ;
            }

            sa_nracanaa wl_region *confine_rect = NULL;
            ᬬᬾᬦ᭄ (!SDL_RectEmpty(&window->mouse_rect)) {
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
                ᬬᬾᬦ᭄ (!SDL_PointInRect(&seat->pointer.last_motion, &scaled_mouse_rect)) {
                    /* Warp the pointer to the closest point within the confinement zone if outside,
                     * The confinement region will be created when a true position event is received.
                     */
                    puur_naa_nka closest_x = seat->pointer.last_motion.x;
                    puur_naa_nka closest_y = seat->pointer.last_motion.y;

                    ᬬᬾᬦ᭄ (closest_x < scaled_mouse_rect.x) {
                        closest_x = scaled_mouse_rect.x;
                    } ᬮᬶᬬ ᬬᬾᬦ᭄ (closest_x >= scaled_mouse_rect.x + scaled_mouse_rect.w) {
                        closest_x = (scaled_mouse_rect.x + scaled_mouse_rect.w) - 1;
                    }

                    ᬬᬾᬦ᭄ (closest_y < scaled_mouse_rect.y) {
                        closest_y = scaled_mouse_rect.y;
                    } ᬮᬶᬬ ᬬᬾᬦ᭄ (closest_y >= scaled_mouse_rect.y + scaled_mouse_rect.h) {
                        closest_y = (scaled_mouse_rect.y + scaled_mouse_rect.h) - 1;
                    }

                    Wayland_SeatWarpMouse(seat, w, closest_x, closest_y);
                }
            }

            ᬬᬾᬦ᭄ (confine_rect || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
                ᬬᬾᬦ᭄ (window->mouse_rect.w != 1 && window->mouse_rect.h != 1) {
                    seat->pointer.confined_pointer =
                        zwp_pointer_constraints_v1_confine_pointer(display->pointer_constraints,
                                                                   w->surface,
                                                                   seat->pointer.wl_pointer,
                                                                   confine_rect,
                                                                   ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_confined_pointer_v1_add_listener(seat->pointer.confined_pointer,
                                                         &confined_pointer_listener,
                                                         seat);
                } ᬮᬶᬬ {
                    /* Use a lock for 1x1 confinement regions, as the pointer can exhibit subpixel motion otherwise.
                     * A null region is used since the warp *should* have placed the pointer where we want it, but
                     * better to lock it slightly off than let the pointer escape, as confining to a specific region
                     * seems to be a racy operation on some compositors.
                     */
                    seat->pointer.locked_pointer =
                        zwp_pointer_constraints_v1_lock_pointer(display->pointer_constraints,
                                                                w->surface,
                                                                seat->pointer.wl_pointer,
                                                                NULL,
                                                                ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
                    zwp_locked_pointer_v1_add_listener(seat->pointer.locked_pointer,
                                                       &locked_pointer_listener,
                                                       seat);
                }
                ᬬᬾᬦ᭄ (confine_rect) {
                    wl_region_destroy(confine_rect);
                }
            }
        }
    }
}

void Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ᬬᬾᬦ᭄ (!window || seat->pointer.focus == window) {
            Wayland_SeatUpdatePointerGrab(seat);
        }
    }
}

void Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window)
{
    SDL_WaylandSeat *seat;
    wl_list_for_each (seat, &display->seat_list, link) {
        ᬬᬾᬦ᭄ (!window || seat->keyboard.focus == window) {
            Wayland_SeatUpdateKeyboardGrab(seat);
        }
    }
}

void Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial)
{
    ᬬᬾᬦ᭄ (serial > seat->last_implicit_grab_serial) {
        seat->last_implicit_grab_serial = serial;
        seat->display->last_implicit_grab_seat = seat;
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
