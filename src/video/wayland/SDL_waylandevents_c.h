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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandevents_h_
#నిర్వచించు SDL_waylandevents_h_

#అన్తర్భావ "../../events/SDL_keymap_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_pen_c.h"

#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandwindow.h"
#అన్తర్భావ "SDL_waylanddatamanager.h"

గణన SDL_WaylandAxisEvent
{
    SDL_WAYLAND_AXIS_EVENT_CONTINUOUS = 0,
    SDL_WAYLAND_AXIS_EVENT_DISCRETE,
    SDL_WAYLAND_AXIS_EVENT_VALUE120
};

రకనిర్వచనం నిర్మాణం
{
    Sint32 repeat_రేటు;     // Repeat rate in range of [1, 1000] character(s) per second
    Sint32 repeat_delay_ms; // Time to first repeat event in milliseconds

    Uint32 కీలకం;               // Key code of the repeating key
    Uint32 scancode;          // Scancode of the repeating key
    Uint32 keyboard_id;       // ID of the source keyboard
    Uint32 wl_press_సమయం_ms;  // Key press time as reported by the Wayland API in milliseconds
    Uint64 పునాది_సమయం_ns;      // Key press time as reported by the Wayland API in nanoseconds
    Uint64 sdl_press_సమయం_ns; // Key press time expressed in SDL ticks
    Uint64 తదుపరి_repeat_ns;    // Next repeat event in nanoseconds
    అక్షరం పాఠ్యం[8];
} SDL_WaylandKeyboardRepeat;

రకనిర్వచనం నిర్మాణం SDL_WaylandCursorState
{
    SDL_Cursor_దత్తాంశం *current_cursor;
    నిర్మాణం wp_cursor_shape_device_v1 *cursor_shape;
    నిర్మాణం wl_surface *surface;
    నిర్మాణం wp_viewport *viewport;

    ద్విగుణ scale;

    // Pointer to the internal data for system cursors.
    శూన్య *system_cursor_handle;

    // The cursor animation thread lock must be held when modifying this.
    నిర్మాణం wl_callback *చట్రం_callback;

    Uint64 చివరి_చట్రం_callback_సమయం_ms;
    Uint32 current_చట్రం_సమయం_ms;

    // 0 or greater if a buffer is attached, -1 if in the reset state.
    పూర్ణాంకం current_చట్రం;

    SDL_తగిలింది_Test_ఫలితం తగిలింది_test_ఫలితం;
} SDL_WaylandCursorState;

రకనిర్వచనం నిర్మాణం SDL_WaylandPenTool  // a stylus, etc, on a tablet.
{
    SDL_PenID instance_id;
    SDL_PenInfo info;
    SDL_కిటికీ_దత్తాంశం *focus;
    నిర్మాణం zwp_tablet_tool_v2 *wltool;
    Uint32 proximity_serial;

    నిర్మాణం
    {
        దశాంశం x;
        దశాంశం y;

        దశాంశం axes[SDL_PEN_AXIS_లెక్క];
        Uint32 axes_సమితి;

        గణన
        {
            WAYLAND_TABLET_TOOL_BUTTON_NONE = 0,
            WAYLAND_TABLET_TOOL_BUTTON_కిందికి,
            WAYLAND_TABLET_TOOL_BUTTON_పైకి
        } buttons[3];

        గణన
        {
            WAYLAND_TABLET_TOOL_STATE_NONE = 0,
            WAYLAND_TABLET_TOOL_STATE_కిందికి,
            WAYLAND_TABLET_TOOL_STATE_పైకి
        } tool_state;

        bool లోపల_proximity;

        bool have_motion;
        bool have_proximity;
    } చట్రం;

    SDL_WaylandCursorState cursor_state;
    నిర్మాణం wl_list link;
} SDL_WaylandPenTool;

రకనిర్వచనం నిర్మాణం SDL_WaylandSeat
{
    SDL_Video_దత్తాంశం *display;
    నిర్మాణం wl_seat *wl_seat;
    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device;
    SDL_WaylandPrimarySelectionDevice *primary_selection_device;
    అక్షరం *name;
    నిర్మాణం wl_list link;

    Uint32 చివరి_implicit_grab_serial; // The serial of the last implicit grab event for window activation and selection data.
    Uint32 registry_id;               // The ID of the Wayland seat object,

    నిర్మాణం
    {
        నిర్మాణం wl_keyboard *wl_keyboard;
        నిర్మాణం zwp_ఆదానం_timestamps_v1 *timestamps;
        నిర్మాణం zwp_keyboard_shortcuts_inhibitor_v1 *కీలకం_inhibitor;
        SDL_కిటికీ_దత్తాంశం *focus;
        SDL_Keymap **sdl_keymap;
        నిర్మాణం wl_array reserved_scancodes;
        అక్షరం *current_locale;

        SDL_WaylandKeyboardRepeat repeat;
        Uint64 highres_timestamp_ns;

        // Current SDL modifier flags
        SDL_Keymod pressed_modifiers;
        SDL_Keymod locked_modifiers;

        SDL_KeyboardID sdl_id;
        bool is_virtual;

        నిర్మాణం
        {
            నిర్మాణం xkb_keymap *keymap;
            నిర్మాణం xkb_state *state;
            నిర్మాణం xkb_compose_పట్టిక *compose_పట్టిక;
            నిర్మాణం xkb_compose_state *compose_state;

            // Current keyboard layout (aka 'group')
            xkb_layout_సూచీ_t అంకె_layouts;
            xkb_layout_సూచీ_t current_layout;

            // Modifier bitshift values
            xkb_mod_ముసుగు_t జరుపు_ముసుగు;
            xkb_mod_ముసుగు_t ctrl_ముసుగు;
            xkb_mod_ముసుగు_t alt_ముసుగు;
            xkb_mod_ముసుగు_t gui_ముసుగు;
            xkb_mod_ముసుగు_t level3_ముసుగు;
            xkb_mod_ముసుగు_t level5_ముసుగు;
            xkb_mod_ముసుగు_t అంకె_ముసుగు;
            xkb_mod_ముసుగు_t caps_ముసుగు_2;

            // Current system modifier flags
            xkb_mod_ముసుగు_t wl_pressed_modifiers;
            xkb_mod_ముసుగు_t wl_latched_modifiers;
            xkb_mod_ముసుగు_t wl_locked_modifiers;
        } xkb;
    } keyboard;

    నిర్మాణం
    {
        నిర్మాణం wl_సూచిక *wl_సూచిక;
        నిర్మాణం zwp_relative_సూచిక_v1 *relative_సూచిక;
        నిర్మాణం zwp_ఆదానం_timestamps_v1 *timestamps;
        నిర్మాణం zwp_locked_సూచిక_v1 *locked_సూచిక;
        నిర్మాణం zwp_confined_సూచిక_v1 *confined_సూచిక;
        నిర్మాణం zwp_సూచిక_gesture_pinch_v1 *gesture_pinch;

        SDL_కిటికీ_దత్తాంశం *focus;
        నిర్మాణం wl_surface *focus_surface;

        // According to the spec, a seat can only have one active gesture of any type at a time.
        SDL_కిటికీ_దత్తాంశం *gesture_focus;

        Uint64 highres_timestamp_ns;
        Uint32 enter_serial;
        SDL_MouseButtonFlags buttons_pressed;
        SDL_బిందువు చివరి_motion;
        bool is_confined;

        SDL_MouseID sdl_id;

        // Information about axis events on the current frame
        నిర్మాణం
        {
            bool have_absolute;
            bool have_relative;
            bool have_warp;
            bool have_axis;

            Uint32 buttons_pressed;
            Uint32 buttons_released;

            నిర్మాణం
            {
                wl_fixed_t sx;
                wl_fixed_t sy;
            } absolute;

            నిర్మాణం
            {
                wl_fixed_t dx;
                wl_fixed_t dy;
                wl_fixed_t dx_unaccel;
                wl_fixed_t dy_unaccel;
            } relative;

            నిర్మాణం
            {
                గణన SDL_WaylandAxisEvent x_axis_type;
                దశాంశం x;

                గణన SDL_WaylandAxisEvent y_axis_type;
                దశాంశం y;

                SDL_MouseWheelDirection direction;
            } axis;

            నిర్మాణం wl_surface *enter_surface;
            నిర్మాణం wl_surface *leave_surface;

            // Event timestamp in nanoseconds
            Uint64 timestamp_ns;
        } pending_చట్రం;

        SDL_WaylandCursorState cursor_state;
    } సూచిక_2;

    నిర్మాణం
    {
        నిర్మాణం wl_touch *wl_touch;
        నిర్మాణం zwp_ఆదానం_timestamps_v1 *timestamps;
        Uint64 highres_timestamp_ns;
        నిర్మాణం wl_list points;
    } touch;

    నిర్మాణం
    {
        నిర్మాణం zwp_పాఠ్యం_ఆదానం_v3 *zwp_పాఠ్యం_ఆదానం;
        SDL_Rect పాఠ్యం_ఆదానం_rect;
        పూర్ణాంకం పాఠ్యం_ఆదానం_cursor;
        bool enabled;
        bool has_preedit;
    } పాఠ్యం_ఆదానం;

    నిర్మాణం
    {
        నిర్మాణం zwp_tablet_seat_v2 *wl_tablet_seat;
        నిర్మాణం wl_list tool_list;
    } tablet;
} SDL_WaylandSeat;


బాహ్య Uint64 Wayland_GetTouchTimestamp(నిర్మాణం SDL_WaylandSeat *seat, Uint32 wl_timestamp_ms);

బాహ్య శూన్య Wayland_PumpEvents(SDL_VideoDevice *_this);
బాహ్య శూన్య Wayland_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య పూర్ణాంకం Wayland_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);

బాహ్య శూన్య Wayland_Display_Init_ఆదానం_Timestamp_Manager(SDL_Video_దత్తాంశం *display);
బాహ్య శూన్య Wayland_DisplayInitCursorShapeManager(SDL_Video_దత్తాంశం *display);
బాహ్య శూన్య Wayland_Display_Init_సూచిక_Gesture_Manager(SDL_Video_దత్తాంశం *display);
బాహ్య శూన్య Wayland_DisplayInitTabletManager(SDL_Video_దత్తాంశం *display);
బాహ్య శూన్య Wayland_Display_Init_దత్తాంశం_Device_Manager(SDL_Video_దత్తాంశం *display);
బాహ్య శూన్య Wayland_DisplayInitPrimarySelectionDeviceManager(SDL_Video_దత్తాంశం *display);

బాహ్య శూన్య Wayland_Display_Init_పాఠ్యం_ఆదానం_Manager(SDL_Video_దత్తాంశం *d, uint32_t id);

బాహ్య శూన్య Wayland_DisplayCreateSeat(SDL_Video_దత్తాంశం *display, నిర్మాణం wl_seat *wl_seat, Uint32 id);
బాహ్య శూన్య Wayland_SeatDestroy(SDL_WaylandSeat *seat, bool shutting_కిందికి);

బాహ్య శూన్య Wayland_Seat_Update_సూచిక_Grab(SDL_WaylandSeat *seat);
బాహ్య శూన్య Wayland_Display_Update_సూచిక_Grabs(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ);
బాహ్య శూన్య Wayland_DisplayUpdateKeyboardGrabs(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ);
బాహ్య శూన్య Wayland_Display_Remove_కిటికీ_References_From_Seats(SDL_Video_దత్తాంశం *display, SDL_కిటికీ_దత్తాంశం *కిటికీ);

/* The implicit grab serial needs to be updated on:
 * - Gaining keyboard focus
 * - Keyboard key down/up
 * - Mouse button down
 * - Touch event down
 * - Tablet tool down
 * - Tablet tool button down/up
 */
బాహ్య శూన్య Wayland_UpdateImplicitGrabSerial(SDL_WaylandSeat *seat, Uint32 serial);

#అయితే_ముగింపు // SDL_waylandevents_h_
