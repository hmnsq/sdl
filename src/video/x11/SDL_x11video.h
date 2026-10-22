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

#که_نه_تعریف_شوی SDL_x11video_h_
#تعریف_کړه SDL_x11video_h_

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

بنية SDL_Video_معلومات
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    صحيح numwindows;
    SDL_کړکۍ_معلومات **windowlist;
    صحيح windowlistlength;
    XID کړکۍ_ډله;
    کړکۍ_2 clipboard_کړکۍ;
    SDLX11_Clipboard_معلومات clipboard;
    SDLX11_Clipboard_معلومات primary_selection;
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_کړکۍ *فعال_cursor_confined_کړکۍ;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
    کړکۍ_2 xsettings_کړکۍ;
    SDLX11_Settings_معلومات xsettings_معلومات;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    بنية {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_کړکۍ;
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
        Atom NET_WM_کړکۍ_OPACITY;
        Atom NET_WM_USER_وخت;
        Atom NET_فعال_کړکۍ;
        Atom NET_چوکاټ_EXTENTS;
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
        Atom Xdnd_پای_ته_رسېدلی;
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

    bool broken_اشاره_ګر_grab; // true if XGrabPointer seems unreliable.

    Uint64 وروستی_ډېرپېښ_change_deadline;

    bool global_mouse_بدل_شوی;
    SDL_ټکی global_mouse_position;
    Uint32 global_mouse_buttons;

    بینښه اوږد xinput_وروستی_button_serial;
    بینښه اوږد xinput_وروستی_کلی_serial;
    صحيح xinput_وروستی_keyboard_device;
    صحيح xinput_master_اشاره_ګر_device;
    bool xinput_hierarchy_بدل_شوی;

    صحيح xrandr_event_بنسټ;
    بنية
    {
        bool xkb_enabled;
        SDL_Scancode کلی_layout[256];

        اتحاد
        {
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            بنية
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_عدد_Kbd_Groups];
                بینښه اوږد وروستی_map_serial;
                صحيح event;
                Uint32 current_ډله;
            } xkb; // Modern XKB keyboard handling
#د_که_پای
            بنية
            {
                کلی_Sym *keysym_map;
                صحيح keysyms_فی_کلی;
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
        Uint32 alt_ماسک;
        Uint32 gui_ماسک;
        Uint32 level3_ماسک;
        Uint32 level5_ماسک;
        Uint32 numlock_ماسک;
        Uint32 scrolllock_ماسک;
    } keyboard;

#که_تعریف_شوی SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#د_که_پای

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

خارجي bool X11_Use_مستقیم_Color_Visuals(فراغ);

#د_که_پای // SDL_x11video_h_
