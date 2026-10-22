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

#جے_بنا_تعریف SDL_x11video_h_
#تعریف_کرو SDL_x11video_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keymap_c.h"

#ضمن "../../core/linux/SDL_dbus.h"
#ضمن "../../core/linux/SDL_ime.h"

#ضمن "SDL_x11dyn.h"

#ضمن "SDL_x11clipboard.h"
#ضمن "SDL_x11events.h"
#ضمن "SDL_x11keyboard.h"
#ضمن "SDL_x11modes.h"
#ضمن "SDL_x11mouse.h"
#ضمن "SDL_x11opengl.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11window.h"
#ضمن "SDL_x11vulkan.h"

// Private display data

بنية SDL_Video_انکڑے
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    صحيح numwindows;
    SDL_کھڑکی_انکڑے **windowlist;
    صحيح windowlistlength;
    XID کھڑکی_گروہ;
    کھڑکی_2 clipboard_کھڑکی;
    SDLX11_Clipboard_انکڑے clipboard;
    SDLX11_Clipboard_انکڑے primary_selection;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_کھڑکی *سرگرم_cursor_confined_کھڑکی;
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
    کھڑکی_2 xsettings_کھڑکی;
    SDLX11_Settings_انکڑے xsettings_انکڑے;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    بنية {
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
        Atom _NET_WM_SYNC_REQUEST_COUNTER;
        Atom NET_WM_کھڑکی_OPACITY;
        Atom NET_WM_USER_ویلا;
        Atom NET_سرگرم_کھڑکی;
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
        Atom Xdnd_مکمل;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_ضرب_حاصل_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_اڈیک;
    bool selection_incr_اڈیک;

    bool broken_اشارہ_گر_grab; // true if XGrabPointer seems unreliable.

    Uint64 آخری_منوال_change_deadline;

    bool global_mouse_بدلیا;
    SDL_نقطہ global_mouse_position;
    Uint32 global_mouse_buttons;

    بنانشانی لما xinput_آخری_button_serial;
    بنانشانی لما xinput_آخری_کلید_serial;
    صحيح xinput_آخری_keyboard_device;
    صحيح xinput_master_اشارہ_گر_device;
    bool xinput_hierarchy_بدلیا;

    صحيح xrandr_event_ادھار;
    بنية
    {
        bool xkb_enabled;
        SDL_Scancode کلید_layout[256];

        اتحاد
        {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            بنية
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_عدد_Kbd_Groups];
                بنانشانی لما آخری_map_serial;
                صحيح event;
                Uint32 current_گروہ;
            } xkb; // Modern XKB keyboard handling
#جے_انت
            بنية
            {
                کلید_Sym *keysym_map;
                صحيح keysyms_فی_کلید;
                صحيح min_keycode;
                صحيح max_keycode;
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

#جے_تعریف_شدہ SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#جے_انت

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

خارجي bool X11_Use_سدھا_Color_Visuals(فراغ);

#جے_انت // SDL_x11video_h_
