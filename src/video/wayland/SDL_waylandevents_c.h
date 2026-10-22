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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandevents_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandevents_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keymap_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_pen_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylanddatamanager.h"

ਗਿਣਤੀ SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    Sint32 repeat_ਦਰ;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 ਕੁੰਜੀ;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_ਸਮਾਂ_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 ਅਧਾਰ_ਸਮਾਂ_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_ਸਮਾਂ_ns; // Key press time expressed in SDL ticks
    Uint64 ਅਗਲਾ_repeat_ns;    // Next repeat event in nanoseconds
    ਅੱਖਰ ਪਾਠ[8];
} SDL_WaylandKeyboardRepeat;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_WaylandCursorState
{
    SDL_Cursor_ਅੰਕੜੇ *current_cursor;
    ਬਣਤਰ wp_cursor_shape_device_v1 *cursor_shape;
    ਬਣਤਰ wl_surface *surface;
    ਬਣਤਰ wp_viewport *viewport;

    ਦੁੱਗਣਾ scale;

    // Pointer to the internal data for system cursors.
    ਖਾਲੀ *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    ਬਣਤਰ wl_callback *ਚੌਖਟਾ_callback;

    Uint64 ਆਖਰੀ_ਚੌਖਟਾ_callback_ਸਮਾਂ_ms;
    Uint32 current_ਚੌਖਟਾ_ਸਮਾਂ_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    ਪੂਰਨ current_ਚੌਖਟਾ;

    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ;
} SDL_WaylandCursorState;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus;
    ਬਣਤਰ zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    ਬਣਤਰ
    {
        ਦਸ਼ਮਲਵ x;
        ਦਸ਼ਮਲਵ y;

        ਦਸ਼ਮਲਵ axes[SDL_PEN_AXIS_ਗਿਣਤੀ];
        Uint32 axes_ਸੈੱਟ;

        ਗਿਣਤੀ
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_ਥੱਲੇ,
            WAYLAND_TABLET_TOOL_BUTTON_ਉੱਪਰ
        } buttons[3];

        ਗਿਣਤੀ
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_ਥੱਲੇ,
            WAYLAND_TABLET_TOOL_STATE_ਉੱਪਰ
        } tool_state;

        bool ਵਿੱਚ_proximity;

        bool have_motion;
        bool have_proximity;
    } ਚੌਖਟਾ;

    SDL_WaylandCursorState cursor_state;
    ਬਣਤਰ wl_list link;
} SDL_WaylandPenTool;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_WaylandSeat
{
    SDL_Video_ਅੰਕੜੇ *display;
    ਬਣਤਰ wl_seat *wl_seat;
    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    ਅੱਖਰ *name;
    ਬਣਤਰ wl_list link;

    Uint32 ਆਖਰੀ_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    ਬਣਤਰ
    {
        ਬਣਤਰ wl_keyboard *wl_keyboard;
        ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_v1 *timestamps;
        ਬਣਤਰ zwp_keyboard_shortcuts_inhibitor_v1 *ਕੁੰਜੀ_inhibitor;
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus;
        SDL_Keymap **sdl_keymap;
        ਬਣਤਰ wl_array reserved_scancodes;
        ਅੱਖਰ *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        ਬਣਤਰ
        {
            ਬਣਤਰ xkb_keymap *keymap;
            ਬਣਤਰ xkb_state *state;
            ਬਣਤਰ xkb_compose_ਸਾਰਣੀ *compose_ਸਾਰਣੀ;
            ਬਣਤਰ xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_ਸੂਚਕਾਂਕ_t ਅੰਕ_layouts;
            xkb_layout_ਸੂਚਕਾਂਕ_t current_layout;

            // Modifier bitshift values
            xkb_mod_ਨਕਾਬ_t ਖਿਸਕਾਓ_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t ctrl_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t alt_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t gui_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t level3_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t level5_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t ਅੰਕ_ਨਕਾਬ;
            xkb_mod_ਨਕਾਬ_t caps_ਨਕਾਬ_2;

            // Current system modifier flags
            xkb_mod_ਨਕਾਬ_t wl_pressed_modifiers;
            xkb_mod_ਨਕਾਬ_t wl_latched_modifiers;
            xkb_mod_ਨਕਾਬ_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    ਬਣਤਰ
    {
        ਬਣਤਰ wl_ਸੂਚਕ *wl_ਸੂਚਕ;
        ਬਣਤਰ zwp_relative_ਸੂਚਕ_v1 *relative_ਸੂਚਕ;
        ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_v1 *timestamps;
        ਬਣਤਰ zwp_locked_ਸੂਚਕ_v1 *locked_ਸੂਚਕ;
        ਬਣਤਰ zwp_confined_ਸੂਚਕ_v1 *confined_ਸੂਚਕ;
        ਬਣਤਰ zwp_ਸੂਚਕ_gesture_pinch_v1 *gesture_pinch;

        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus;
        ਬਣਤਰ wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_ਬਿੰਦੂ ਆਖਰੀ_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        ਬਣਤਰ
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            ਬਣਤਰ
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            ਬਣਤਰ
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            ਬਣਤਰ
            {
                ਗਿਣਤੀ SDL_WaylandAxisEvent x_axis_type;
                ਦਸ਼ਮਲਵ x;

                ਗਿਣਤੀ SDL_WaylandAxisEvent y_axis_type;
                ਦਸ਼ਮਲਵ y;

                SDL_MouseWheelDirection direction;
            } axis;

            ਬਣਤਰ wl_surface *enter_surface;
            ਬਣਤਰ wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_ਚੌਖਟਾ;

        SDL_WaylandCursorState cursor_state;
    } ਸੂਚਕ_2;

    ਬਣਤਰ
    {
        ਬਣਤਰ wl_touch *wl_touch;
        ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        ਬਣਤਰ wl_list points;
    } touch;

    ਬਣਤਰ
    {
        ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_v3 *zwp_ਪਾਠ_ਨਿਵੇਸ਼;
        SDL_Rect ਪਾਠ_ਨਿਵੇਸ਼_rect;
        ਪੂਰਨ ਪਾਠ_ਨਿਵੇਸ਼_cursor;
        bool enabled;
        bool has_preedit;
    } ਪਾਠ_ਨਿਵੇਸ਼;

    ਬਣਤਰ
    {
        ਬਣਤਰ zwp_tablet_seat_v2 *wl_tablet_seat;
        ਬਣਤਰ wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


ਬਾਹਰੀ Uint64 Wayland_GetTouchTimestamp(ਬਣਤਰ SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

ਬਾਹਰੀ ਖਾਲੀ Wayland_PumpEvents(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਪੂਰਨ Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Init_ਨਿਵੇਸ਼_Timestamp_Manager(SDL_Video_ਅੰਕੜੇ *display);
ਬਾਹਰੀ ਖਾਲੀ Wayland_DisplayInitCursorShapeManager(SDL_Video_ਅੰਕੜੇ *display);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Init_ਸੂਚਕ_Gesture_Manager(SDL_Video_ਅੰਕੜੇ *display);
ਬਾਹਰੀ ਖਾਲੀ Wayland_DisplayInitTabletManager(SDL_Video_ਅੰਕੜੇ *display);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Init_ਅੰਕੜੇ_Device_Manager(SDL_Video_ਅੰਕੜੇ *display);
ਬਾਹਰੀ ਖਾਲੀ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ਅੰਕੜੇ *display);

ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Init_ਪਾਠ_ਨਿਵੇਸ਼_Manager(SDL_Video_ਅੰਕੜੇ *d, uint32_t id);

ਬਾਹਰੀ ਖਾਲੀ Wayland_DisplayCreateSeat(SDL_Video_ਅੰਕੜੇ *display, ਬਣਤਰ wl_seat *wl_seat, Uint32 id);
ਬਾਹਰੀ ਖਾਲੀ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ਥੱਲੇ);

ਬਾਹਰੀ ਖਾਲੀ Wayland_Seat_Update_ਸੂਚਕ_Grab(SDL_WaylandSeat *seat);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Update_ਸੂਚਕ_Grabs(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Display_Remove_ਖਿੜਕੀ_References_From_Seats(SDL_Video_ਅੰਕੜੇ *display, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
ਬਾਹਰੀ ਖਾਲੀ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#ਜੇ_ਅੰਤ // SDL_waylandevents_h_
