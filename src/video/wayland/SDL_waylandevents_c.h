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

#اگر_غیر_تعریف_شدہ SDL_waylandevents_h_
#تعریف_کرو SDL_waylandevents_h_

#شامل "../../events/SDL_keymap_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_pen_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylanddatamanager.h"

شمار SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

قسمتعریف ساخت
{
    Sint32 repeat_شرح;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 کلید;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_وقت_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 بنیاد_وقت_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_وقت_ns; // Key press time expressed in SDL ticks
    Uint64 اگلا_repeat_ns;    // Next repeat event in nanoseconds
    حرف متن[8];
} SDL_WaylandKeyboardRepeat;

قسمتعریف ساخت SDL_WaylandCursorState
{
    SDL_Cursor_ڈیٹا *current_cursor;
    ساخت wp_cursor_shape_device_v1 *cursor_shape;
    ساخت wl_surface *surface;
    ساخت wp_viewport *viewport;

    دوہرا scale;

    // Pointer to the internal data for system cursors.
    خالی *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    ساخت wl_callback *چوکھٹا_callback;

    Uint64 آخری_چوکھٹا_callback_وقت_ms;
    Uint32 current_چوکھٹا_وقت_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    صحیح current_چوکھٹا;

    SDL_کامیابی_Test_نتیجہ کامیابی_test_نتیجہ;
} SDL_WaylandCursorState;

قسمتعریف ساخت SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_کھڑکی_ڈیٹا *focus;
    ساخت zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    ساخت
    {
        اعشاری x;
        اعشاری y;

        اعشاری axes[SDL_PEN_AXIS_گنتی];
        Uint32 axes_سیٹ;

        شمار
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_نیچے_کو,
            WAYLAND_TABLET_TOOL_BUTTON_اوپر
        } buttons[3];

        شمار
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_نیچے_کو,
            WAYLAND_TABLET_TOOL_STATE_اوپر
        } tool_state;

        bool اندر_proximity;

        bool have_motion;
        bool have_proximity;
    } چوکھٹا;

    SDL_WaylandCursorState cursor_state;
    ساخت wl_list link;
} SDL_WaylandPenTool;

قسمتعریف ساخت SDL_WaylandSeat
{
    SDL_Video_ڈیٹا *display;
    ساخت wl_seat *wl_seat;
    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    حرف *name;
    ساخت wl_list link;

    Uint32 آخری_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    ساخت
    {
        ساخت wl_keyboard *wl_keyboard;
        ساخت zwp_داخلہ_timestamps_v1 *timestamps;
        ساخت zwp_keyboard_shortcuts_inhibitor_v1 *کلید_inhibitor;
        SDL_کھڑکی_ڈیٹا *focus;
        SDL_Keymap **sdl_keymap;
        ساخت wl_array reserved_scancodes;
        حرف *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        ساخت
        {
            ساخت xkb_keymap *keymap;
            ساخت xkb_state *state;
            ساخت xkb_compose_جدول *compose_جدول;
            ساخت xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_اشاریہ_t عدد_layouts;
            xkb_layout_اشاریہ_t current_layout;

            // Modifier bitshift values
            xkb_mod_نقاب_t سرکاؤ_نقاب;
            xkb_mod_نقاب_t ctrl_نقاب;
            xkb_mod_نقاب_t alt_نقاب;
            xkb_mod_نقاب_t gui_نقاب;
            xkb_mod_نقاب_t level3_نقاب;
            xkb_mod_نقاب_t level5_نقاب;
            xkb_mod_نقاب_t عدد_نقاب;
            xkb_mod_نقاب_t caps_نقاب_2;

            // Current system modifier flags
            xkb_mod_نقاب_t wl_pressed_modifiers;
            xkb_mod_نقاب_t wl_latched_modifiers;
            xkb_mod_نقاب_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    ساخت
    {
        ساخت wl_اشارہ_گر *wl_اشارہ_گر;
        ساخت zwp_relative_اشارہ_گر_v1 *relative_اشارہ_گر;
        ساخت zwp_داخلہ_timestamps_v1 *timestamps;
        ساخت zwp_locked_اشارہ_گر_v1 *locked_اشارہ_گر;
        ساخت zwp_confined_اشارہ_گر_v1 *confined_اشارہ_گر;
        ساخت zwp_اشارہ_گر_gesture_pinch_v1 *gesture_pinch;

        SDL_کھڑکی_ڈیٹا *focus;
        ساخت wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_کھڑکی_ڈیٹا *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_نقطہ آخری_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        ساخت
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            ساخت
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            ساخت
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            ساخت
            {
                شمار SDL_WaylandAxisEvent x_axis_type;
                اعشاری x;

                شمار SDL_WaylandAxisEvent y_axis_type;
                اعشاری y;

                SDL_MouseWheelDirection direction;
            } axis;

            ساخت wl_surface *enter_surface;
            ساخت wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_چوکھٹا;

        SDL_WaylandCursorState cursor_state;
    } اشارہ_گر_2;

    ساخت
    {
        ساخت wl_touch *wl_touch;
        ساخت zwp_داخلہ_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        ساخت wl_list points;
    } touch;

    ساخت
    {
        ساخت zwp_متن_داخلہ_v3 *zwp_متن_داخلہ;
        SDL_Rect متن_داخلہ_rect;
        صحیح متن_داخلہ_cursor;
        bool enabled;
        bool has_preedit;
    } متن_داخلہ;

    ساخت
    {
        ساخت zwp_tablet_seat_v2 *wl_tablet_seat;
        ساخت wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


خارجی Uint64 Wayland_GetTouchTimestamp(ساخت SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

خارجی خالی Wayland_PumpEvents(SDL_VideoDevice *_this);
خارجی خالی Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی صحیح Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

خارجی خالی Wayland_Display_Init_داخلہ_Timestamp_Manager(SDL_Video_ڈیٹا *display);
خارجی خالی Wayland_DisplayInitCursorShapeManager(SDL_Video_ڈیٹا *display);
خارجی خالی Wayland_Display_Init_اشارہ_گر_Gesture_Manager(SDL_Video_ڈیٹا *display);
خارجی خالی Wayland_DisplayInitTabletManager(SDL_Video_ڈیٹا *display);
خارجی خالی Wayland_Display_Init_ڈیٹا_Device_Manager(SDL_Video_ڈیٹا *display);
خارجی خالی Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_ڈیٹا *display);

خارجی خالی Wayland_Display_Init_متن_داخلہ_Manager(SDL_Video_ڈیٹا *d, uint32_t id);

خارجی خالی Wayland_DisplayCreateSeat(SDL_Video_ڈیٹا *display, ساخت wl_seat *wl_seat, Uint32 id);
خارجی خالی Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_نیچے_کو);

خارجی خالی Wayland_Seat_Update_اشارہ_گر_Grab(SDL_WaylandSeat *seat);
خارجی خالی Wayland_Display_Update_اشارہ_گر_Grabs(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی);
خارجی خالی Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی);
خارجی خالی Wayland_Display_Remove_کھڑکی_References_From_Seats(SDL_Video_ڈیٹا *display, SDL_کھڑکی_ڈیٹا *کھڑکی);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
خارجی خالی Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#اگر_ختم // SDL_waylandevents_h_
