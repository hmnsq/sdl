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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandevents_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandevents_h_

#ಅನ್ತರ್ಭಾವ "../../events/SDL_keymap_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylanddatamanager.h"

ಎಣಿಕೆ SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    Sint32 repeat_ದರ;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 ಕೀಲಿ;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_ಸಮಯ_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 ತಳ_ಸಮಯ_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_ಸಮಯ_ns; // Key press time expressed in SDL ticks
    Uint64 ಮುಂದಿನ_repeat_ns;    // Next repeat event in nanoseconds
    ಅಕ್ಷರ ಪಠ್ಯ[8];
} SDL_WaylandKeyboardRepeat;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_WaylandCursorState
{
    SDL_Cursor_ದತ್ತಾಂಶ *current_cursor;
    ರಚನೆ wp_cursor_shape_device_v1 *cursor_shape;
    ರಚನೆ wl_surface *surface;
    ರಚನೆ wp_viewport *viewport;

    ದ್ವಿಗುಣ scale;

    // Pointer to the internal data for system cursors.
    ಶೂನ್ಯ *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    ರಚನೆ wl_callback *ಚೌಕಟ್ಟು_callback;

    Uint64 ಕೊನೆಯ_ಚೌಕಟ್ಟು_callback_ಸಮಯ_ms;
    Uint32 current_ಚೌಕಟ್ಟು_ಸಮಯ_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    ಪೂರ್ಣಾಂಕ current_ಚೌಕಟ್ಟು;

    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ ದೊರಕಿತು_test_ಫಲಿತಾಂಶ;
} SDL_WaylandCursorState;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus;
    ರಚನೆ zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    ರಚನೆ
    {
        ದಶಮಾಂಶ x;
        ದಶಮಾಂಶ y;

        ದಶಮಾಂಶ axes[SDL_PEN_AXIS_ಎಣಿಕೆ];
        Uint32 axes_ಗಣ;

        ಎಣಿಕೆ
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_ಕೆಳಕ್ಕೆ,
            WAYLAND_TABLET_TOOL_BUTTON_ಮೇಲೆ
        } buttons[3];

        ಎಣಿಕೆ
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_ಕೆಳಕ್ಕೆ,
            WAYLAND_TABLET_TOOL_STATE_ಮೇಲೆ
        } tool_state;

        bool ಒಳ_proximity;

        bool have_motion;
        bool have_proximity;
    } ಚೌಕಟ್ಟು;

    SDL_WaylandCursorState cursor_state;
    ರಚನೆ wl_list link;
} SDL_WaylandPenTool;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_WaylandSeat
{
    SDL_Video_ದತ್ತಾಂಶ *display;
    ರಚನೆ wl_seat *wl_seat;
    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    ಅಕ್ಷರ *name;
    ರಚನೆ wl_list link;

    Uint32 ಕೊನೆಯ_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    ರಚನೆ
    {
        ರಚನೆ wl_keyboard *wl_keyboard;
        ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        ರಚನೆ zwp_keyboard_shortcuts_inhibitor_v1 *ಕೀಲಿ_inhibitor;
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus;
        SDL_Keymap **sdl_keymap;
        ರಚನೆ wl_array reserved_scancodes;
        ಅಕ್ಷರ *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        ರಚನೆ
        {
            ರಚನೆ xkb_keymap *keymap;
            ರಚನೆ xkb_state *state;
            ರಚನೆ xkb_compose_ಕೋಷ್ಟಕ *compose_ಕೋಷ್ಟಕ;
            ರಚನೆ xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_ಸೂಚ್ಯಂಕ_t ಅಂಕೆ_layouts;
            xkb_layout_ಸೂಚ್ಯಂಕ_t current_layout;

            // Modifier bitshift values
            xkb_mod_ಮುಖವಾಡ_t ಸರಿಸು_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t ctrl_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t alt_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t gui_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t level3_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t level5_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t ಅಂಕೆ_ಮುಖವಾಡ;
            xkb_mod_ಮುಖವಾಡ_t caps_ಮುಖವಾಡ_2;

            // Current system modifier flags
            xkb_mod_ಮುಖವಾಡ_t wl_pressed_modifiers;
            xkb_mod_ಮುಖವಾಡ_t wl_latched_modifiers;
            xkb_mod_ಮುಖವಾಡ_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    ರಚನೆ
    {
        ರಚನೆ wl_ಸೂಚಕ *wl_ಸೂಚಕ;
        ರಚನೆ zwp_relative_ಸೂಚಕ_v1 *relative_ಸೂಚಕ;
        ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        ರಚನೆ zwp_locked_ಸೂಚಕ_v1 *locked_ಸೂಚಕ;
        ರಚನೆ zwp_confined_ಸೂಚಕ_v1 *confined_ಸೂಚಕ;
        ರಚನೆ zwp_ಸೂಚಕ_gesture_pinch_v1 *gesture_pinch;

        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus;
        ರಚನೆ wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_ಬಿಂದು ಕೊನೆಯ_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        ರಚನೆ
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            ರಚನೆ
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            ರಚನೆ
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            ರಚನೆ
            {
                ಎಣಿಕೆ SDL_WaylandAxisEvent x_axis_type;
                ದಶಮಾಂಶ x;

                ಎಣಿಕೆ SDL_WaylandAxisEvent y_axis_type;
                ದಶಮಾಂಶ y;

                SDL_MouseWheelDirection direction;
            } axis;

            ರಚನೆ wl_surface *enter_surface;
            ರಚನೆ wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_ಚೌಕಟ್ಟು;

        SDL_WaylandCursorState cursor_state;
    } ಸೂಚಕ_2;

    ರಚನೆ
    {
        ರಚನೆ wl_touch *wl_touch;
        ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        ರಚನೆ wl_list points;
    } touch;

    ರಚನೆ
    {
        ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_v3 *zwp_ಪಠ್ಯ_ಒಳಹರಿವು;
        SDL_Rect ಪಠ್ಯ_ಒಳಹರಿವು_rect;
        ಪೂರ್ಣಾಂಕ ಪಠ್ಯ_ಒಳಹರಿವು_cursor;
        bool enabled;
        bool has_preedit;
    } ಪಠ್ಯ_ಒಳಹರಿವು;

    ರಚನೆ
    {
        ರಚನೆ zwp_tablet_seat_v2 *wl_tablet_seat;
        ರಚನೆ wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


ಬಾಹ್ಯ Uint64 Wayland_GetTouchTimestamp(ರಚನೆ SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_PumpEvents(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_ಒಳಹರಿವು_Timestamp_Manager(SDL_Video_ದತ್ತಾಂಶ *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitCursorShapeManager(SDL_Video_ದತ್ತಾಂಶ *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_ಸೂಚಕ_Gesture_Manager(SDL_Video_ದತ್ತಾಂಶ *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitTabletManager(SDL_Video_ದತ್ತಾಂಶ *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_ದತ್ತಾಂಶ_Device_Manager(SDL_Video_ದತ್ತಾಂಶ *display);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ದತ್ತಾಂಶ *display);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Init_ಪಠ್ಯ_ಒಳಹರಿವು_Manager(SDL_Video_ದತ್ತಾಂಶ *d, uint32_t id);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayCreateSeat(SDL_Video_ದತ್ತಾಂಶ *display, ರಚನೆ wl_seat *wl_seat, Uint32 id);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ಕೆಳಕ್ಕೆ);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Seat_Update_ಸೂಚಕ_Grab(SDL_WaylandSeat *seat);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Update_ಸೂಚಕ_Grabs(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Display_Remove_ಕಿಟಕಿ_References_From_Seats(SDL_Video_ದತ್ತಾಂಶ *display, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylandevents_h_
