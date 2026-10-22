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

#که_نه_تعریف_شوی SDL_waylandevents_h_
#تعریف_کړه SDL_waylandevents_h_

#ضمن "../../events/SDL_keymap_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_pen_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "SDL_waylanddatamanager.h"

تعداد SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

تعريفنوع بنية
{
    Sint32 repeat_شرح;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 کلی;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_وخت_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 بنسټ_وخت_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_وخت_ns; // Key press time expressed in SDL ticks
    Uint64 بل_repeat_ns;    // Next repeat event in nanoseconds
    حرف متن[8];
} SDL_WaylandKeyboardRepeat;

تعريفنوع بنية SDL_WaylandCursorState
{
    SDL_Cursor_معلومات *current_cursor;
    بنية wp_cursor_shape_device_v1 *cursor_shape;
    بنية wl_surface *surface;
    بنية wp_viewport *viewport;

    مزدوج scale;

    // Pointer to the internal data for system cursors.
    فراغ *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    بنية wl_callback *چوکاټ_callback;

    Uint64 وروستی_چوکاټ_callback_وخت_ms;
    Uint32 current_چوکاټ_وخت_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    صحيح current_چوکاټ;

    SDL_موندنه_Test_پایله موندنه_test_پایله;
} SDL_WaylandCursorState;

تعريفنوع بنية SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_کړکۍ_معلومات *focus;
    بنية zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    بنية
    {
        عائم x;
        عائم y;

        عائم axes[SDL_PEN_AXIS_شمېر];
        Uint32 axes_سېټ;

        تعداد
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_ښکته,
            WAYLAND_TABLET_TOOL_BUTTON_پورته
        } buttons[3];

        تعداد
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_ښکته,
            WAYLAND_TABLET_TOOL_STATE_پورته
        } tool_state;

        bool دننه_proximity;

        bool have_motion;
        bool have_proximity;
    } چوکاټ;

    SDL_WaylandCursorState cursor_state;
    بنية wl_list link;
} SDL_WaylandPenTool;

تعريفنوع بنية SDL_WaylandSeat
{
    SDL_Video_معلومات *display;
    بنية wl_seat *wl_seat;
    SDL_Wayland_معلومات_Device *معلومات_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    حرف *name;
    بنية wl_list link;

    Uint32 وروستی_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    بنية
    {
        بنية wl_keyboard *wl_keyboard;
        بنية zwp_ننوت_timestamps_v1 *timestamps;
        بنية zwp_keyboard_shortcuts_inhibitor_v1 *کلی_inhibitor;
        SDL_کړکۍ_معلومات *focus;
        SDL_Keymap **sdl_keymap;
        بنية wl_array reserved_scancodes;
        حرف *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        بنية
        {
            بنية xkb_keymap *keymap;
            بنية xkb_state *state;
            بنية xkb_compose_جدول *compose_جدول;
            بنية xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_شاخص_t عدد_layouts;
            xkb_layout_شاخص_t current_layout;

            // Modifier bitshift values
            xkb_mod_ماسک_t ښويدنه_ماسک;
            xkb_mod_ماسک_t ctrl_ماسک;
            xkb_mod_ماسک_t alt_ماسک;
            xkb_mod_ماسک_t gui_ماسک;
            xkb_mod_ماسک_t level3_ماسک;
            xkb_mod_ماسک_t level5_ماسک;
            xkb_mod_ماسک_t عدد_ماسک;
            xkb_mod_ماسک_t caps_ماسک_2;

            // Current system modifier flags
            xkb_mod_ماسک_t wl_pressed_modifiers;
            xkb_mod_ماسک_t wl_latched_modifiers;
            xkb_mod_ماسک_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    بنية
    {
        بنية wl_اشاره_ګر *wl_اشاره_ګر;
        بنية zwp_relative_اشاره_ګر_v1 *relative_اشاره_ګر;
        بنية zwp_ننوت_timestamps_v1 *timestamps;
        بنية zwp_locked_اشاره_ګر_v1 *locked_اشاره_ګر;
        بنية zwp_confined_اشاره_ګر_v1 *confined_اشاره_ګر;
        بنية zwp_اشاره_ګر_gesture_pinch_v1 *gesture_pinch;

        SDL_کړکۍ_معلومات *focus;
        بنية wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_کړکۍ_معلومات *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_ټکی وروستی_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        بنية
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            بنية
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            بنية
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            بنية
            {
                تعداد SDL_WaylandAxisEvent x_axis_type;
                عائم x;

                تعداد SDL_WaylandAxisEvent y_axis_type;
                عائم y;

                SDL_MouseWheelDirection direction;
            } axis;

            بنية wl_surface *enter_surface;
            بنية wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_چوکاټ;

        SDL_WaylandCursorState cursor_state;
    } اشاره_ګر_2;

    بنية
    {
        بنية wl_touch *wl_touch;
        بنية zwp_ننوت_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        بنية wl_list points;
    } touch;

    بنية
    {
        بنية zwp_متن_ننوت_v3 *zwp_متن_ننوت;
        SDL_Rect متن_ننوت_rect;
        صحيح متن_ننوت_cursor;
        bool enabled;
        bool has_preedit;
    } متن_ننوت;

    بنية
    {
        بنية zwp_tablet_seat_v2 *wl_tablet_seat;
        بنية wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


خارجي Uint64 Wayland_GetTouchTimestamp(بنية SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

خارجي فراغ Wayland_PumpEvents(SDL_VideoDevice *_this);
خارجي فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

خارجي فراغ Wayland_Display_Init_ننوت_Timestamp_Manager(SDL_Video_معلومات *display);
خارجي فراغ Wayland_DisplayInitCursorShapeManager(SDL_Video_معلومات *display);
خارجي فراغ Wayland_Display_Init_اشاره_ګر_Gesture_Manager(SDL_Video_معلومات *display);
خارجي فراغ Wayland_DisplayInitTabletManager(SDL_Video_معلومات *display);
خارجي فراغ Wayland_Display_Init_معلومات_Device_Manager(SDL_Video_معلومات *display);
خارجي فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_معلومات *display);

خارجي فراغ Wayland_Display_Init_متن_ننوت_Manager(SDL_Video_معلومات *d, uint32_t id);

خارجي فراغ Wayland_DisplayCreateSeat(SDL_Video_معلومات *display, بنية wl_seat *wl_seat, Uint32 id);
خارجي فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_ښکته);

خارجي فراغ Wayland_Seat_Update_اشاره_ګر_Grab(SDL_WaylandSeat *seat);
خارجي فراغ Wayland_Display_Update_اشاره_ګر_Grabs(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ);
خارجي فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ);
خارجي فراغ Wayland_Display_Remove_کړکۍ_References_From_Seats(SDL_Video_معلومات *display, SDL_کړکۍ_معلومات *کړکۍ);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
خارجي فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#د_که_پای // SDL_waylandevents_h_
