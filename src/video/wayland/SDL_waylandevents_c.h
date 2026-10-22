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

#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylandevents_h_
#define SDL_waylandevents_h_

#અન્તર્ભાવ "../../events/SDL_keymap_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_pen_c.h"

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandwindow.h"
#અન્તર્ભાવ "SDL_waylanddatamanager.h"

ગણના SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

પ્રકારવ્યાખ્યા સંરચના
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 ચાવી;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 next_repeat_ns;    // Next repeat event in nanoseconds
    અક્ષર text[8];
} SDL_WaylandKeyboardRepeat;

પ્રકારવ્યાખ્યા સંરચના SDL_WaylandCursorState
{
    SDL_CursorData *current_cursor;
    સંરચના wp_cursor_shape_device_v1 *cursor_shape;
    સંરચના wl_surface *surface;
    સંરચના wp_viewport *viewport;

    દ્વિગુણ scale;

    // Pointer to the internal data for system cursors.
    શૂન્ય *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    સંરચના wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    પૂર્ણાંક current_frame;

    SDL_HitTestResult hit_test_result;
} SDL_WaylandCursorState;

પ્રકારવ્યાખ્યા સંરચના SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_WindowData *focus;
    સંરચના zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    સંરચના
    {
        દશાંશ x;
        દશાંશ y;

        દશાંશ axes[SDL_PEN_AXIS_ગણતરી];
        Uint32 axes_set;

        ગણના
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_DOWN,
            WAYLAND_TABLET_TOOL_BUTTON_UP
        } buttons[3];

        ગણના
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
    સંરચના wl_list link;
} SDL_WaylandPenTool;

પ્રકારવ્યાખ્યા સંરચના SDL_WaylandSeat
{
    SDL_VideoData *display;
    સંરચના wl_seat *wl_seat;
    SDL_WaylandDataDevice *data_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    અક્ષર *name;
    સંરચના wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    સંરચના
    {
        સંરચના wl_keyboard *wl_keyboard;
        સંરચના zwp_આગત_timestamps_v1 *timestamps;
        સંરચના zwp_keyboard_shortcuts_inhibitor_v1 *ચાવી_inhibitor;
        SDL_WindowData *focus;
        SDL_Keymap **sdl_keymap;
        સંરચના wl_array reserved_scancodes;
        અક્ષર *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        સંરચના
        {
            સંરચના xkb_keymap *keymap;
            સંરચના xkb_state *state;
            સંરચના xkb_compose_table *compose_table;
            સંરચના xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_index_t અંક_layouts;
            xkb_layout_index_t current_layout;

            // Modifier bitshift values
            xkb_mod_mask_t shift_mask;
            xkb_mod_mask_t ctrl_mask;
            xkb_mod_mask_t alt_mask;
            xkb_mod_mask_t gui_mask;
            xkb_mod_mask_t level3_mask;
            xkb_mod_mask_t level5_mask;
            xkb_mod_mask_t અંક_mask;
            xkb_mod_mask_t caps_mask;

            // Current system modifier flags
            xkb_mod_mask_t wl_pressed_modifiers;
            xkb_mod_mask_t wl_latched_modifiers;
            xkb_mod_mask_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    સંરચના
    {
        સંરચના wl_pointer *wl_pointer;
        સંરચના zwp_relative_pointer_v1 *relative_pointer;
        સંરચના zwp_આગત_timestamps_v1 *timestamps;
        સંરચના zwp_locked_pointer_v1 *locked_pointer;
        સંરચના zwp_confined_pointer_v1 *confined_pointer;
        સંરચના zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_WindowData *focus;
        સંરચના wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_WindowData *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        સંરચના
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            સંરચના
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            સંરચના
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            સંરચના
            {
                ગણના SDL_WaylandAxisEvent x_axis_type;
                દશાંશ x;

                ગણના SDL_WaylandAxisEvent y_axis_type;
                દશાંશ y;

                SDL_MouseWheelDirection direction;
            } axis;

            સંરચના wl_surface *enter_surface;
            સંરચના wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    સંરચના
    {
        સંરચના wl_touch *wl_touch;
        સંરચના zwp_આગત_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        સંરચના wl_list points;
    } touch;

    સંરચના
    {
        સંરચના zwp_text_આગત_v3 *zwp_text_આગત;
        SDL_Rect text_આગત_rect;
        પૂર્ણાંક text_આગત_cursor;
        bool enabled;
        bool has_preedit;
    } text_આગત;

    સંરચના
    {
        સંરચના zwp_tablet_seat_v2 *wl_tablet_seat;
        સંરચના wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


બાહ્ય Uint64 Wayland_GetTouchTimestamp(સંરચના SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

બાહ્ય શૂન્ય Wayland_PumpEvents(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય પૂર્ણાંક Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

બાહ્ય શૂન્ય Wayland_Display_Init_આગત_Timestamp_Manager(SDL_VideoData *display);
બાહ્ય શૂન્ય Wayland_DisplayInitCursorShapeManager(SDL_VideoData *display);
બાહ્ય શૂન્ય Wayland_DisplayInitPointerGestureManager(SDL_VideoData *display);
બાહ્ય શૂન્ય Wayland_DisplayInitTabletManager(SDL_VideoData *display);
બાહ્ય શૂન્ય Wayland_DisplayInitDataDeviceManager(SDL_VideoData *display);
બાહ્ય શૂન્ય Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_VideoData *display);

બાહ્ય શૂન્ય Wayland_Display_Init_Text_આગત_Manager(SDL_VideoData *d, uint32_t id);

બાહ્ય શૂન્ય Wayland_DisplayCreateSeat(SDL_VideoData *display, સંરચના wl_seat *wl_seat, Uint32 id);
બાહ્ય શૂન્ય Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

બાહ્ય શૂન્ય Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
બાહ્ય શૂન્ય Wayland_DisplayUpdatePointerGrabs(SDL_VideoData *display, SDL_WindowData *window);
બાહ્ય શૂન્ય Wayland_DisplayUpdateKeyboardGrabs(SDL_VideoData *display, SDL_WindowData *window);
બાહ્ય શૂન્ય Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_VideoData *display, SDL_WindowData *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
બાહ્ય શૂન્ય Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#endif // SDL_waylandevents_h_
