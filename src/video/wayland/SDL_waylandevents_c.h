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

#ifndef SDL_waylandevents_h_
#define SDL_waylandevents_h_

#شامل "../../events/SDL_keymap_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_pen_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylanddatamanager.h"

شمارش SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

تعریفنوع ساختار
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 کلید;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 next_repeat_ns;    // Next repeat event in nanoseconds
    نویسه text[8];
} SDL_WaylandKeyboardRepeat;

تعریفنوع ساختار SDL_WaylandCursorState
{
    SDL_CursorData *current_cursor;
    ساختار wp_cursor_shape_device_v1 *cursor_shape;
    ساختار wl_surface *surface;
    ساختار wp_viewport *viewport;

    دوگانه scale;

    // Pointer to the internal data for system cursors.
    تهی *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    ساختار wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    صحیح current_frame;

    SDL_HitTestResult hit_test_result;
} SDL_WaylandCursorState;

تعریفنوع ساختار SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_WindowData *focus;
    ساختار zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    ساختار
    {
        اعشاری x;
        اعشاری y;

        اعشاری axes[SDL_PEN_AXIS_شمار];
        Uint32 axes_set;

        شمارش
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_DOWN,
            WAYLAND_TABLET_TOOL_BUTTON_UP
        } buttons[3];

        شمارش
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
    ساختار wl_list link;
} SDL_WaylandPenTool;

تعریفنوع ساختار SDL_WaylandSeat
{
    SDL_VideoData *display;
    ساختار wl_seat *wl_seat;
    SDL_WaylandDataDevice *data_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    نویسه *name;
    ساختار wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    ساختار
    {
        ساختار wl_keyboard *wl_keyboard;
        ساختار zwp_درون_داد_timestamps_v1 *timestamps;
        ساختار zwp_keyboard_shortcuts_inhibitor_v1 *کلید_inhibitor;
        SDL_WindowData *focus;
        SDL_Keymap **sdl_keymap;
        ساختار wl_array reserved_scancodes;
        نویسه *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        ساختار
        {
            ساختار xkb_keymap *keymap;
            ساختار xkb_state *state;
            ساختار xkb_compose_table *compose_table;
            ساختار xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_index_t رقم_layouts;
            xkb_layout_index_t current_layout;

            // Modifier bitshift values
            xkb_mod_mask_t shift_mask;
            xkb_mod_mask_t ctrl_mask;
            xkb_mod_mask_t alt_mask;
            xkb_mod_mask_t gui_mask;
            xkb_mod_mask_t level3_mask;
            xkb_mod_mask_t level5_mask;
            xkb_mod_mask_t رقم_mask;
            xkb_mod_mask_t caps_mask;

            // Current system modifier flags
            xkb_mod_mask_t wl_pressed_modifiers;
            xkb_mod_mask_t wl_latched_modifiers;
            xkb_mod_mask_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    ساختار
    {
        ساختار wl_pointer *wl_pointer;
        ساختار zwp_relative_pointer_v1 *relative_pointer;
        ساختار zwp_درون_داد_timestamps_v1 *timestamps;
        ساختار zwp_locked_pointer_v1 *locked_pointer;
        ساختار zwp_confined_pointer_v1 *confined_pointer;
        ساختار zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_WindowData *focus;
        ساختار wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_WindowData *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        ساختار
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            ساختار
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            ساختار
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            ساختار
            {
                شمارش SDL_WaylandAxisEvent x_axis_type;
                اعشاری x;

                شمارش SDL_WaylandAxisEvent y_axis_type;
                اعشاری y;

                SDL_MouseWheelDirection direction;
            } axis;

            ساختار wl_surface *enter_surface;
            ساختار wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    ساختار
    {
        ساختار wl_touch *wl_touch;
        ساختار zwp_درون_داد_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        ساختار wl_list points;
    } touch;

    ساختار
    {
        ساختار zwp_text_درون_داد_v3 *zwp_text_درون_داد;
        SDL_Rect text_درون_داد_rect;
        صحیح text_درون_داد_cursor;
        bool enabled;
        bool has_preedit;
    } text_درون_داد;

    ساختار
    {
        ساختار zwp_tablet_seat_v2 *wl_tablet_seat;
        ساختار wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


بیرونی Uint64 Wayland_GetTouchTimestamp(ساختار SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

بیرونی تهی Wayland_PumpEvents(SDL_VideoDevice *_this);
بیرونی تهی Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی صحیح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

بیرونی تهی Wayland_Display_Init_درون_داد_Timestamp_Manager(SDL_VideoData *display);
بیرونی تهی Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display);
بیرونی تهی Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display);
بیرونی تهی Wayland_DisplayInitTabletManager(SDL_VideoData *display);
بیرونی تهی Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display);
بیرونی تهی Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display);

بیرونی تهی Wayland_Display_Init_Text_درون_داد_Manager(SDL_VideoData *d, uint32_t id);

بیرونی تهی Wayland_DisplayCreateSeat(SDL_VideoData *display, ساختار wl_seat *wl_seat, Uint32 id);
بیرونی تهی Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

بیرونی تهی Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
بیرونی تهی Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window);
بیرونی تهی Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window);
بیرونی تهی Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
بیرونی تهی Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#endif // SDL_waylandevents_h_
