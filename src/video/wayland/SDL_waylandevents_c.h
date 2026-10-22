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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylandevents_h_
#define SDL_waylandevents_h_

#অন্তর্ভাব "../../events/SDL_keymap_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_pen_c.h"

#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandwindow.h"
#অন্তর্ভাব "SDL_waylanddatamanager.h"

গণনা SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

প্রকারলেখ কাঠামো
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 চাবি;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 পরবর্তী_repeat_ns;    // Next repeat event in nanoseconds
    অক্ষর text[8];
} SDL_WaylandKeyboardRepeat;

প্রকারলেখ কাঠামো SDL_WaylandCursorState
{
    SDL_Cursor_তথ্য *current_cursor;
    কাঠামো wp_cursor_shape_device_v1 *cursor_shape;
    কাঠামো wl_surface *surface;
    কাঠামো wp_viewport *viewport;

    দ্বিগুণ scale;

    // Pointer to the internal data for system cursors.
    শূন্য *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    কাঠামো wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    পূর্ণসংখ্যা current_frame;

    SDL_Hit_Test_ফলাফল hit_test_ফলাফল;
} SDL_WaylandCursorState;

প্রকারলেখ কাঠামো SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_Window_তথ্য *focus;
    কাঠামো zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    কাঠামো
    {
        দশমিক x;
        দশমিক y;

        দশমিক axes[SDL_PEN_AXIS_গুনতি];
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
    কাঠামো wl_list link;
} SDL_WaylandPenTool;

প্রকারলেখ কাঠামো SDL_WaylandSeat
{
    SDL_Video_তথ্য *display;
    কাঠামো wl_seat *wl_seat;
    SDL_Wayland_তথ্য_Device *তথ্য_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    অক্ষর *name;
    কাঠামো wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    কাঠামো
    {
        কাঠামো wl_keyboard *wl_keyboard;
        কাঠামো zwp_প্রবেশ_timestamps_v1 *timestamps;
        কাঠামো zwp_keyboard_shortcuts_inhibitor_v1 *চাবি_inhibitor;
        SDL_Window_তথ্য *focus;
        SDL_Keymap **sdl_keymap;
        কাঠামো wl_array reserved_scancodes;
        অক্ষর *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        কাঠামো
        {
            কাঠামো xkb_keymap *keymap;
            কাঠামো xkb_state *state;
            কাঠামো xkb_compose_table *compose_table;
            কাঠামো xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_সূচক_t অঙ্ক_layouts;
            xkb_layout_সূচক_t current_layout;

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

    কাঠামো
    {
        কাঠামো wl_pointer *wl_pointer;
        কাঠামো zwp_relative_pointer_v1 *relative_pointer;
        কাঠামো zwp_প্রবেশ_timestamps_v1 *timestamps;
        কাঠামো zwp_locked_pointer_v1 *locked_pointer;
        কাঠামো zwp_confined_pointer_v1 *confined_pointer;
        কাঠামো zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_Window_তথ্য *focus;
        কাঠামো wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_Window_তথ্য *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        কাঠামো
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            কাঠামো
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            কাঠামো
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            কাঠামো
            {
                গণনা SDL_WaylandAxisEvent x_axis_type;
                দশমিক x;

                গণনা SDL_WaylandAxisEvent y_axis_type;
                দশমিক y;

                SDL_MouseWheelDirection direction;
            } axis;

            কাঠামো wl_surface *enter_surface;
            কাঠামো wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    কাঠামো
    {
        কাঠামো wl_touch *wl_touch;
        কাঠামো zwp_প্রবেশ_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        কাঠামো wl_list points;
    } touch;

    কাঠামো
    {
        কাঠামো zwp_text_প্রবেশ_v3 *zwp_text_প্রবেশ;
        SDL_Rect text_প্রবেশ_rect;
        পূর্ণসংখ্যা text_প্রবেশ_cursor;
        bool enabled;
        bool has_preedit;
    } text_প্রবেশ;

    কাঠামো
    {
        কাঠামো zwp_tablet_seat_v2 *wl_tablet_seat;
        কাঠামো wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


বাহ্যিক Uint64 Wayland_GetTouchTimestamp(কাঠামো SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

বাহ্যিক শূন্য Wayland_PumpEvents(SDL_VideoDevice *_this);
বাহ্যিক শূন্য Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক পূর্ণসংখ্যা Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

বাহ্যিক শূন্য Wayland_Display_Init_প্রবেশ_Timestamp_Manager(SDL_Video_তথ্য *display);
বাহ্যিক শূন্য Wayland_DisplayInitCursorShapeManager(SDL_Video_তথ্য *display);
বাহ্যিক শূন্য Wayland_DisplayInitPointerGestureManager(SDL_Video_তথ্য *display);
বাহ্যিক শূন্য Wayland_DisplayInitTabletManager(SDL_Video_তথ্য *display);
বাহ্যিক শূন্য Wayland_Display_Init_তথ্য_Device_Manager(SDL_Video_তথ্য *display);
বাহ্যিক শূন্য Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_তথ্য *display);

বাহ্যিক শূন্য Wayland_Display_Init_Text_প্রবেশ_Manager(SDL_Video_তথ্য *d, uint32_t id);

বাহ্যিক শূন্য Wayland_DisplayCreateSeat(SDL_Video_তথ্য *display, কাঠামো wl_seat *wl_seat, Uint32 id);
বাহ্যিক শূন্য Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

বাহ্যিক শূন্য Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
বাহ্যিক শূন্য Wayland_DisplayUpdatePointerGrabs(SDL_Video_তথ্য *display, SDL_Window_তথ্য *window);
বাহ্যিক শূন্য Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_তথ্য *display, SDL_Window_তথ্য *window);
বাহ্যিক শূন্য Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_Video_তথ্য *display, SDL_Window_তথ্য *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
বাহ্যিক শূন্য Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#endif // SDL_waylandevents_h_
