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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_waylandevents_h_
#define SDL_waylandevents_h_

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keymap_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylanddatamanager.h"

ಗಣನಾ SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 ಕೀಲಿ;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 next_repeat_ns;    // Next repeat event in nanoseconds
    ವರ್ಣ text[8];
} SDL_WaylandKeyboardRepeat;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandCursorState
{
    SDL_CursorData *current_cursor;
    ಸಂರಚನಾ wp_cursor_shape_device_v1 *cursor_shape;
    ಸಂರಚನಾ wl_surface *surface;
    ಸಂರಚನಾ wp_viewport *viewport;

    ದ್ವಿಗುಣ scale;

    // Pointer to the internal data for system cursors.
    ಶೂನ್ಯ *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    ಸಂರಚನಾ wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    ಪೂರ್ಣಾಙ್ಕ current_frame;

    SDL_HitTestResult hit_test_result;
} SDL_WaylandCursorState;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_WindowData *focus;
    ಸಂರಚನಾ zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    ಸಂರಚನಾ
    {
        ಭಿನ್ನ x;
        ಭಿನ್ನ y;

        ಭಿನ್ನ axes[SDL_PEN_AXIS_ಎಣಿಕೆ];
        Uint32 axes_set;

        ಗಣನಾ
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_DOWN,
            WAYLAND_TABLET_TOOL_BUTTON_UP
        } buttons[3];

        ಗಣನಾ
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
    ಸಂರಚನಾ wl_list link;
} SDL_WaylandPenTool;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_WaylandSeat
{
    SDL_VideoData *display;
    ಸಂರಚನಾ wl_seat *wl_seat;
    SDL_WaylandDataDevice *data_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    ವರ್ಣ *name;
    ಸಂರಚನಾ wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ wl_keyboard *wl_keyboard;
        ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        ಸಂರಚನಾ zwp_keyboard_shortcuts_inhibitor_v1 *ಕೀಲಿ_inhibitor;
        SDL_WindowData *focus;
        SDL_Keymap **sdl_keymap;
        ಸಂರಚನಾ wl_array reserved_scancodes;
        ವರ್ಣ *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        ಸಂರಚನಾ
        {
            ಸಂರಚನಾ xkb_keymap *keymap;
            ಸಂರಚನಾ xkb_state *state;
            ಸಂರಚನಾ xkb_compose_table *compose_table;
            ಸಂರಚನಾ xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_index_t ಅಂಕೆ_layouts;
            xkb_layout_index_t current_layout;

            // Modifier bitshift values
            xkb_mod_mask_t shift_mask;
            xkb_mod_mask_t ctrl_mask;
            xkb_mod_mask_t alt_mask;
            xkb_mod_mask_t gui_mask;
            xkb_mod_mask_t level3_mask;
            xkb_mod_mask_t level5_mask;
            xkb_mod_mask_t ಅಂಕೆ_mask;
            xkb_mod_mask_t caps_mask;

            // Current system modifier flags
            xkb_mod_mask_t wl_pressed_modifiers;
            xkb_mod_mask_t wl_latched_modifiers;
            xkb_mod_mask_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ wl_pointer *wl_pointer;
        ಸಂರಚನಾ zwp_relative_pointer_v1 *relative_pointer;
        ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        ಸಂರಚನಾ zwp_locked_pointer_v1 *locked_pointer;
        ಸಂರಚನಾ zwp_confined_pointer_v1 *confined_pointer;
        ಸಂರಚನಾ zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_WindowData *focus;
        ಸಂರಚನಾ wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_WindowData *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        ಸಂರಚನಾ
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            ಸಂರಚನಾ
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            ಸಂರಚನಾ
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            ಸಂರಚನಾ
            {
                ಗಣನಾ SDL_WaylandAxisEvent x_axis_type;
                ಭಿನ್ನ x;

                ಗಣನಾ SDL_WaylandAxisEvent y_axis_type;
                ಭಿನ್ನ y;

                SDL_MouseWheelDirection direction;
            } axis;

            ಸಂರಚನಾ wl_surface *enter_surface;
            ಸಂರಚನಾ wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ wl_touch *wl_touch;
        ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        ಸಂರಚನಾ wl_list points;
    } touch;

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_v3 *zwp_text_ಒಳಹರಿವು;
        SDL_Rect text_ಒಳಹರಿವು_rect;
        ಪೂರ್ಣಾಙ್ಕ text_ಒಳಹರಿವು_cursor;
        bool enabled;
        bool has_preedit;
    } text_ಒಳಹರಿವು;

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ zwp_tablet_seat_v2 *wl_tablet_seat;
        ಸಂರಚನಾ wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


ಬಾಹ್ಯ Uint64 Wayland_GetTouchTimestamp(ಸಂರಚನಾ SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PumpEvents(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_ಒಳಹರಿವು_Timestamp_Manager(SDL_VideoData *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitTabletManager(SDL_VideoData *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_Text_ಒಳಹರಿವು_Manager(SDL_VideoData *d, uint32_t id);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayCreateSeat(SDL_VideoData *display, ಸಂರಚನಾ wl_seat *wl_seat, Uint32 id);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#endif // SDL_waylandevents_h_
