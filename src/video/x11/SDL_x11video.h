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

#اگر_غیر_تعریف_شدہ SDL_x11video_h_
#تعریف_کرو SDL_x11video_h_

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_keymap_c.h"

#شامل "../../core/linux/SDL_dbus.h"
#شامل "../../core/linux/SDL_ime.h"

#شامل "SDL_x11dyn.h"

#شامل "SDL_x11clipboard.h"
#شامل "SDL_x11events.h"
#شامل "SDL_x11keyboard.h"
#شامل "SDL_x11modes.h"
#شامل "SDL_x11mouse.h"
#شامل "SDL_x11opengl.h"
#شامل "SDL_x11settings.h"
#شامل "SDL_x11window.h"
#شامل "SDL_x11vulkan.h"

// Private display data

ساخت SDL_Video_ڈیٹا
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    صحیح numwindows;
    SDL_کھڑکی_ڈیٹا **windowlist;
    صحیح windowlistlength;
    XID کھڑکی_گروہ;
    کھڑکی_2 clipboard_کھڑکی;
    SDLX11_Clipboard_ڈیٹا clipboard;
    SDLX11_Clipboard_ڈیٹا primary_selection;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_کھڑکی *فعال_cursor_confined_کھڑکی;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
    کھڑکی_2 xsettings_کھڑکی;
    SDLX11_Settings_ڈیٹا xsettings_ڈیٹا;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    ساخت {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_کھڑکی;
        Atom WM_NAME;
        Atom WM_TRANSIENT_FOR;
        Atom WM_STATE;
        Atom _NET_WM_STATE;
        Atom _NET_WM_STATE_HIDDEN;
        Atom _NET_WM_STATE_FOCUSED;
        Atom _NET_WM_STATE_MAXIMIZED_VERT;
        Atom _NET_WM_STATE_MAXIMIZED_HORZ;
        Atom _NET_WM_STATE_FULLSCREEN;
        Atom _NET_WM_STATE_ABOVE;
        Atom _NET_WM_STATE_SKIP_TASKBAR;
        Atom _NET_WM_STATE_SKIP_PAGER;
        Atom _NET_WM_STATE_MODAL;
        Atom _NET_WM_MOVERESIZE;
        Atom _NET_WM_ALLOWED_ACTIONS;
        Atom _NET_WM_ACTION_FULLSCREEN;
        Atom _NET_WM_NAME;
        Atom _NET_WM_ICON_NAME;
        Atom _NET_WM_ICON;
        Atom _NET_WM_PING;
        Atom _NET_WM_SYNC_REQUEST;
        Atom NET_WM_SYNC_REQUEST_شمار;
        Atom NET_WM_کھڑکی_OPACITY;
        Atom NET_WM_USER_وقت;
        Atom NET_فعال_کھڑکی;
        Atom NET_چوکھٹا_EXTENTS;
        Atom _SDL_WAKEUP;
        Atom UTF8_STRING;
        Atom PRIMARY;
        Atom CLIPBOARD;
        Atom INCR;
        Atom SDL_SELECTION;
        Atom TARGETS;
        Atom SDL_FORMATS;
        Atom RESOURCE_MANAGER;
        Atom XdndAware;
        Atom XdndEnter;
        Atom XdndLeave;
        Atom XdndPosition;
        Atom Xdnd_حالت;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom Xdnd_ختم_شدہ;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_حاصل_ضرب_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_انتظار;
    bool selection_incr_انتظار;

    bool broken_اشارہ_گر_grab; // true if XGrabPointer seems unreliable.

    Uint64 آخری_منوال_change_deadline;

    bool global_mouse_بدلا;
    SDL_نقطہ global_mouse_position;
    Uint32 global_mouse_buttons;

    غیرعلامتی طویل xinput_آخری_button_serial;
    غیرعلامتی طویل xinput_آخری_کلید_serial;
    صحیح xinput_آخری_keyboard_device;
    صحیح xinput_master_اشارہ_گر_device;
    bool xinput_hierarchy_بدلا;

    صحیح xrandr_event_بنیاد;
    ساخت
    {
        bool xkb_enabled;
        SDL_Scancode کلید_layout[256];

        اتحاد
        {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            ساخت
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_عدد_Kbd_Groups];
                غیرعلامتی طویل آخری_map_serial;
                صحیح event;
                Uint32 current_گروہ;
            } xkb; // Modern XKB keyboard handling
#اگر_ختم
            ساخت
            {
                کلید_Sym *keysym_map;
                صحیح keysyms_فی_کلید;
                صحیح min_keycode;
                صحیح max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_نقاب;
        Uint32 gui_نقاب;
        Uint32 level3_نقاب;
        Uint32 level5_نقاب;
        Uint32 numlock_نقاب;
        Uint32 scrolllock_نقاب;
    } keyboard;

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#اگر_ختم

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

خارجی bool X11_Use_براہ_راست_Color_Visuals(خالی);

#اگر_ختم // SDL_x11video_h_
