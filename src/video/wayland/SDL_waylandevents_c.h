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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandevents_h_
#घोषणा SDL_waylandevents_h_

#समावेश "../../events/SDL_keymap_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_pen_c.h"

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandwindow.h"
#समावेश "SDL_waylanddatamanager.h"

क्रमागत SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

प्रकार काष्ठा
{
    Sint32 repeat_rate;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 कुंजी;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_time_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 base_time_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_time_ns; // Key press time expressed in SDL ticks
    Uint64 अग्र_repeat_ns;    // Next repeat event in nanoseconds
    अक्षर text[8];
} SDL_WaylandKeyboardRepeat;

प्रकार काष्ठा SDL_WaylandCursorState
{
    SDL_Cursor_तथ्य *current_cursor;
    काष्ठा wp_cursor_shape_device_v1 *cursor_shape;
    काष्ठा wl_surface *surface;
    काष्ठा wp_viewport *viewport;

    द्विगुन scale;

    // Pointer to the internal data for system cursors.
    व्योम *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    काष्ठा wl_callback *frame_callback;

    Uint64 last_frame_callback_time_ms;
    Uint32 current_frame_time_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    पूर्णांक current_frame;

    SDL_Hit_Test_परिणाम hit_test_परिणाम;
} SDL_WaylandCursorState;

प्रकार काष्ठा SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_Window_तथ्य *focus;
    काष्ठा zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    काष्ठा
    {
        भग्न x;
        भग्न y;

        भग्न axes[SDL_PEN_AXIS_गिनती];
        Uint32 axes_set;

        क्रमागत
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_DOWN,
            WAYLAND_TABLET_TOOL_BUTTON_UP
        } buttons[3];

        क्रमागत
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
    काष्ठा wl_list link;
} SDL_WaylandPenTool;

प्रकार काष्ठा SDL_WaylandSeat
{
    SDL_Video_तथ्य *display;
    काष्ठा wl_seat *wl_seat;
    SDL_Wayland_तथ्य_Device *तथ्य_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    अक्षर *name;
    काष्ठा wl_list link;

    Uint32 last_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    काष्ठा
    {
        काष्ठा wl_keyboard *wl_keyboard;
        काष्ठा zwp_निवेश_timestamps_v1 *timestamps;
        काष्ठा zwp_keyboard_shortcuts_inhibitor_v1 *कुंजी_inhibitor;
        SDL_Window_तथ्य *focus;
        SDL_Keymap **sdl_keymap;
        काष्ठा wl_array reserved_scancodes;
        अक्षर *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        काष्ठा
        {
            काष्ठा xkb_keymap *keymap;
            काष्ठा xkb_state *state;
            काष्ठा xkb_compose_table *compose_table;
            काष्ठा xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_सूचकांक_t अंक_layouts;
            xkb_layout_सूचकांक_t current_layout;

            // Modifier bitshift values
            xkb_mod_mask_t shift_mask;
            xkb_mod_mask_t ctrl_mask;
            xkb_mod_mask_t alt_mask;
            xkb_mod_mask_t gui_mask;
            xkb_mod_mask_t level3_mask;
            xkb_mod_mask_t level5_mask;
            xkb_mod_mask_t अंक_mask;
            xkb_mod_mask_t caps_mask;

            // Current system modifier flags
            xkb_mod_mask_t wl_pressed_modifiers;
            xkb_mod_mask_t wl_latched_modifiers;
            xkb_mod_mask_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    काष्ठा
    {
        काष्ठा wl_pointer *wl_pointer;
        काष्ठा zwp_relative_pointer_v1 *relative_pointer;
        काष्ठा zwp_निवेश_timestamps_v1 *timestamps;
        काष्ठा zwp_locked_pointer_v1 *locked_pointer;
        काष्ठा zwp_confined_pointer_v1 *confined_pointer;
        काष्ठा zwp_pointer_gesture_pinch_v1 *gesture_pinch;

        SDL_Window_तथ्य *focus;
        काष्ठा wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_Window_तथ्य *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_Point last_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        काष्ठा
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            काष्ठा
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            काष्ठा
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            काष्ठा
            {
                क्रमागत SDL_WaylandAxisEvent x_axis_type;
                भग्न x;

                क्रमागत SDL_WaylandAxisEvent y_axis_type;
                भग्न y;

                SDL_MouseWheelDirection direction;
            } axis;

            काष्ठा wl_surface *enter_surface;
            काष्ठा wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_frame;

        SDL_WaylandCursorState cursor_state;
    } pointer;

    काष्ठा
    {
        काष्ठा wl_touch *wl_touch;
        काष्ठा zwp_निवेश_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        काष्ठा wl_list points;
    } touch;

    काष्ठा
    {
        काष्ठा zwp_text_निवेश_v3 *zwp_text_निवेश;
        SDL_Rect text_निवेश_rect;
        पूर्णांक text_निवेश_cursor;
        bool enabled;
        bool has_preedit;
    } text_निवेश;

    काष्ठा
    {
        काष्ठा zwp_tablet_seat_v2 *wl_tablet_seat;
        काष्ठा wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


बाह्य Uint64 Wayland_GetTouchTimestamp(काष्ठा SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

बाह्य व्योम Wayland_PumpEvents(SDL_VideoDevice *_this);
बाह्य व्योम Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य पूर्णांक Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

बाह्य व्योम Wayland_Display_Init_निवेश_Timestamp_Manager(SDL_Video_तथ्य *display);
बाह्य व्योम Wayland_DisplayInitCursorShapeManager(SDL_Video_तथ्य *display);
बाह्य व्योम Wayland_DisplayInitPointerGestureManager(SDL_Video_तथ्य *display);
बाह्य व्योम Wayland_DisplayInitTabletManager(SDL_Video_तथ्य *display);
बाह्य व्योम Wayland_Display_Init_तथ्य_Device_Manager(SDL_Video_तथ्य *display);
बाह्य व्योम Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_तथ्य *display);

बाह्य व्योम Wayland_Display_Init_Text_निवेश_Manager(SDL_Video_तथ्य *d, uint32_t id);

बाह्य व्योम Wayland_DisplayCreateSeat(SDL_Video_तथ्य *display, काष्ठा wl_seat *wl_seat, Uint32 id);
बाह्य व्योम Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_down);

बाह्य व्योम Wayland_SeatUpdatePointerGrab(SDL_WaylandSeat *seat);
बाह्य व्योम Wayland_DisplayUpdatePointerGrabs(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window);
बाह्य व्योम Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window);
बाह्य व्योम Wayland_DisplayRemoveWindowReferencesFromSeats(SDL_Video_तथ्य *display, SDL_Window_तथ्य *window);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
बाह्य व्योम Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#पूर्ण_अगर // SDL_waylandevents_h_
