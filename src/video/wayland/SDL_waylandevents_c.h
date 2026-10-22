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

#اگر_تعریف_نشده SDL_waylandevents_h_
#تعریف_کن SDL_waylandevents_h_

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
    Sint32 repeat_نرخ;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 کلید;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_زمان_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 پایه_زمان_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_زمان_ns; // Key press time expressed in SDL ticks
    Uint64 بعدی_repeat_ns;    // Next repeat event in nanoseconds
    حرف متن[8];
} SDL_WaylandKeyboardRepeat;

تعريفنوع بنية SDL_WaylandCursorState
{
    SDL_Cursor_داده *current_cursor;
    بنية wp_cursor_shape_device_v1 *cursor_shape;
    بنية wl_surface *surface;
    بنية wp_viewport *viewport;

    مزدوج scale;

    // Pointer to the internal data for system cursors.
    فراغ *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    بنية wl_callback *قاب_callback;

    Uint64 آخرین_قاب_callback_زمان_ms;
    Uint32 current_قاب_زمان_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    صحيح current_قاب;

    SDL_اصابت_Test_نتیجه اصابت_test_نتیجه;
} SDL_WaylandCursorState;

تعريفنوع بنية SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_پنجره_داده *focus;
    بنية zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    بنية
    {
        عائم x;
        عائم y;

        عائم axes[SDL_PEN_AXIS_شمار];
        Uint32 axes_مجموعه;

        تعداد
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_پایین,
            WAYLAND_TABLET_TOOL_BUTTON_به_بالا
        } buttons[3];

        تعداد
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_پایین,
            WAYLAND_TABLET_TOOL_STATE_به_بالا
        } tool_state;

        bool درون_proximity;

        bool have_motion;
        bool have_proximity;
    } قاب;

    SDL_WaylandCursorState cursor_state;
    بنية wl_list link;
} SDL_WaylandPenTool;

تعريفنوع بنية SDL_WaylandSeat
{
    SDL_Video_داده *display;
    بنية wl_seat *wl_seat;
    SDL_Wayland_داده_Device *داده_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    حرف *name;
    بنية wl_list link;

    Uint32 آخرین_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    بنية
    {
        بنية wl_keyboard *wl_keyboard;
        بنية zwp_درون_داد_timestamps_v1 *timestamps;
        بنية zwp_keyboard_shortcuts_inhibitor_v1 *کلید_inhibitor;
        SDL_پنجره_داده *focus;
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
            xkb_layout_شاخص_t رقم_layouts;
            xkb_layout_شاخص_t current_layout;

            // Modifier bitshift values
            xkb_mod_ماسک_t لغزش_ماسک;
            xkb_mod_ماسک_t ctrl_ماسک;
            xkb_mod_ماسک_t alt_ماسک;
            xkb_mod_ماسک_t gui_ماسک;
            xkb_mod_ماسک_t level3_ماسک;
            xkb_mod_ماسک_t level5_ماسک;
            xkb_mod_ماسک_t رقم_ماسک;
            xkb_mod_ماسک_t caps_ماسک_2;

            // Current system modifier flags
            xkb_mod_ماسک_t wl_pressed_modifiers;
            xkb_mod_ماسک_t wl_latched_modifiers;
            xkb_mod_ماسک_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    بنية
    {
        بنية wl_اشاره_گر *wl_اشاره_گر;
        بنية zwp_relative_اشاره_گر_v1 *relative_اشاره_گر;
        بنية zwp_درون_داد_timestamps_v1 *timestamps;
        بنية zwp_locked_اشاره_گر_v1 *locked_اشاره_گر;
        بنية zwp_confined_اشاره_گر_v1 *confined_اشاره_گر;
        بنية zwp_اشاره_گر_gesture_pinch_v1 *gesture_pinch;

        SDL_پنجره_داده *focus;
        بنية wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_پنجره_داده *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_نقطه آخرین_motion;
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
        } pending_قاب;

        SDL_WaylandCursorState cursor_state;
    } اشاره_گر_2;

    بنية
    {
        بنية wl_touch *wl_touch;
        بنية zwp_درون_داد_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        بنية wl_list points;
    } touch;

    بنية
    {
        بنية zwp_متن_درون_داد_v3 *zwp_متن_درون_داد;
        SDL_Rect متن_درون_داد_rect;
        صحيح متن_درون_داد_cursor;
        bool enabled;
        bool has_preedit;
    } متن_درون_داد;

    بنية
    {
        بنية zwp_tablet_seat_v2 *wl_tablet_seat;
        بنية wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


خارجي Uint64 Wayland_GetTouchTimestamp(بنية SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

خارجي فراغ Wayland_PumpEvents(SDL_VideoDevice *_this);
خارجي فراغ Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي صحيح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

خارجي فراغ Wayland_Display_Init_درون_داد_Timestamp_Manager(SDL_Video_داده *display);
خارجي فراغ Wayland_DisplayInitCursorShapeManager(SDL_Video_داده *display);
خارجي فراغ Wayland_Display_Init_اشاره_گر_Gesture_Manager(SDL_Video_داده *display);
خارجي فراغ Wayland_DisplayInitTabletManager(SDL_Video_داده *display);
خارجي فراغ Wayland_Display_Init_داده_Device_Manager(SDL_Video_داده *display);
خارجي فراغ Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_داده *display);

خارجي فراغ Wayland_Display_Init_متن_درون_داد_Manager(SDL_Video_داده *d, uint32_t id);

خارجي فراغ Wayland_DisplayCreateSeat(SDL_Video_داده *display, بنية wl_seat *wl_seat, Uint32 id);
خارجي فراغ Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_پایین);

خارجي فراغ Wayland_Seat_Update_اشاره_گر_Grab(SDL_WaylandSeat *seat);
خارجي فراغ Wayland_Display_Update_اشاره_گر_Grabs(SDL_Video_داده *display, SDL_پنجره_داده *پنجره);
خارجي فراغ Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_داده *display, SDL_پنجره_داده *پنجره);
خارجي فراغ Wayland_Display_Remove_پنجره_References_From_Seats(SDL_Video_داده *display, SDL_پنجره_داده *پنجره);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
خارجي فراغ Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#پایان_اگر // SDL_waylandevents_h_
