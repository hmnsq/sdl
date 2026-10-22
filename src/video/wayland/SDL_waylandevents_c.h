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

#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_waylandevents_h_
#define SDL_waylandevents_h_

#অন্তর্ভাৱ "../../events/SDL_keymap_c.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/SDL_pen_c.h"

#অন্তর্ভাৱ "SDL_waylandvideo.h"
#অন্তর্ভাৱ "SDL_waylandwindow.h"
#অন্তর্ভাৱ "SDL_waylanddatamanager.h"

গণনা SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

প্রকারনির্দেশ সংরচনা
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 চাবি;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 next_repeat_ns;    // Next repeat event in nanoseconds
    ৱর্ণ text[8];
} SDL_WaylandKeyboardRepeat;

প্রকারনির্দেশ সংরচনা SDL_WaylandCursorState
{
    SDL_CursorData *current_cursor;
    সংরচনা wp_cursor_shape_device_v1 *cursor_shape;
    সংরচনা wl_surface *surface;
    সংরচনা wp_viewport *viewport;

    দ্ৱিগুণ scale;

    // Pointer to the internal data for system cursors.
    শূন্য *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    সংরচনা wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    পূর্ণাঙ্ক current_frame;

    SDL_HitTestResult hit_test_result;
} SDL_WaylandCursorState;

প্রকারনির্দেশ সংরচনা SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_WindowData *focus;
    সংরচনা zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    সংরচনা
    {
        ভিন্ন x;
        ভিন্ন y;

        ভিন্ন axes[SDL_PEN_AXIS_গুনতি];
        Uint32 axes_set;

        গণনা
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_DOWN,
            WAYLAND_TABLET_TOOL_BUTTON_UP
        } buttons[3];

        গণনা
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_DOWN,
            WAYLAND_TABLET_TOOL_STATE_UP
        } tool_state;

        bool in_proximity;

        bool have_motion;
        bool have_proximity;
    } frame;

    SDL_WaylandCursorState cursor_state;
    সংরচনা wl_list link;
} SDL_WaylandPenTool;

প্রকারনির্দেশ সংরচনা SDL_WaylandSeat
{
    SDL_VideoData *display;
    সংরচনা wl_seat *wl_seat;
    SDL_WaylandDataDevice *data_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    ৱর্ণ *name;
    সংরচনা wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    সংরচনা
    {
        সংরচনা wl_keyboard *wl_keyboard;
        সংরচনা zwp_প্ৰবেশ_timestamps_v1 *timestamps;
        সংরচনা zwp_keyboard_shortcuts_inhibitor_v1 *চাবি_inhibitor;
        SDL_WindowData *focus;
        SDL_Keymap **sdl_keymap;
        সংরচনা wl_array reserved_scancodes;
        ৱর্ণ *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        সংরচনা
        {
            সংরচনা xkb_keymap *keymap;
            সংরচনা xkb_state *state;
            সংরচনা xkb_compose_table *compose_table;
            সংরচনা xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_index_t অঙ্ক_layouts;
            xkb_layout_index_t current_layout;

            // Modifier bitshift values
            xkb_mod_mask_t shift_mask;
            xkb_mod_mask_t ctrl_mask;
            xkb_mod_mask_t alt_mask;
            xkb_mod_mask_t gui_mask;
            xkb_mod_mask_t level3_mask;
            xkb_mod_mask_t level5_mask;
            xkb_mod_mask_t অঙ্ক_mask;
            xkb_mod_mask_t caps_mask;

            // Current system modifier flags
            xkb_mod_mask_t wl_pressed_modifiers;
            xkb_mod_mask_t wl_latched_modifiers;
            xkb_mod_mask_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    সংরচনা
    {
        সংরচনা wl_pointer *wl_pointer;
        সংরচনা zwp_relative_pointer_v1 *relative_pointer;
        সংরচনা zwp_প্ৰবেশ_timestamps_v1 *timestamps;
        সংরচনা zwp_locked_pointer_v1 *locked_pointer;
        সংরচনা zwp_confined_pointer_v1 *confined_pointer;
        সংরচনা zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_WindowData *focus;
        সংরচনা wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_WindowData *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        সংরচনা
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            সংরচনা
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            সংরচনা
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            সংরচনা
            {
                গণনা SDL_WaylandAxisEvent x_axis_type;
                ভিন্ন x;

                গণনা SDL_WaylandAxisEvent y_axis_type;
                ভিন্ন y;

                SDL_MouseWheelDirection direction;
            } axis;

            সংরচনা wl_surface *enter_surface;
            সংরচনা wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    সংরচনা
    {
        সংরচনা wl_touch *wl_touch;
        সংরচনা zwp_প্ৰবেশ_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        সংরচনা wl_list points;
    } touch;

    সংরচনা
    {
        সংরচনা zwp_text_প্ৰবেশ_v3 *zwp_text_প্ৰবেশ;
        SDL_Rect text_প্ৰবেশ_rect;
        পূর্ণাঙ্ক text_প্ৰবেশ_cursor;
        bool enabled;
        bool has_preedit;
    } text_প্ৰবেশ;

    সংরচনা
    {
        সংরচনা zwp_tablet_seat_v2 *wl_tablet_seat;
        সংরচনা wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


বাহ্য Uint64 Wayland_GetTouchTimestamp(সংরচনা SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

বাহ্য শূন্য Wayland_PumpEvents(SDL_VideoDevice *_this);
বাহ্য শূন্য Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য পূর্ণাঙ্ক Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

বাহ্য শূন্য Wayland_Display_Init_প্ৰবেশ_Timestamp_Manager(SDL_VideoData *display);
বাহ্য শূন্য Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display);
বাহ্য শূন্য Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display);
বাহ্য শূন্য Wayland_DisplayInitTabletManager(SDL_VideoData *display);
বাহ্য শূন্য Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display);
বাহ্য শূন্য Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display);

বাহ্য শূন্য Wayland_Display_Init_Text_প্ৰবেশ_Manager(SDL_VideoData *d, uint32_t id);

বাহ্য শূন্য Wayland_DisplayCreateSeat(SDL_VideoData *display, সংরচনা wl_seat *wl_seat, Uint32 id);
বাহ্য শূন্য Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

বাহ্য শূন্য Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
বাহ্য শূন্য Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window);
বাহ্য শূন্য Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window);
বাহ্য শূন্য Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
বাহ্য শূন্য Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#endif // SDL_waylandevents_h_
