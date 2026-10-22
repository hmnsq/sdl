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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11video_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11video_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keymap_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_ime.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11clipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11events.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11keyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11modes.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11mouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11opengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11window.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11vulkan.h"

// Private display data

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    ಪೂರ್ಣಾಂಕ numwindows;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ **windowlist;
    ಪೂರ್ಣಾಂಕ windowlistlength;
    XID ಕಿಟಕಿ_ಗುಂಪು;
    ಕಿಟಕಿ_2 clipboard_ಕಿಟಕಿ;
    SDLX11_Clipboard_ದತ್ತಾಂಶ clipboard;
    SDLX11_Clipboard_ದತ್ತಾಂಶ primary_selection;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_ಕಿಟಕಿ *ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
    ಕಿಟಕಿ_2 xsettings_ಕಿಟಕಿ;
    SDLX11_Settings_ದತ್ತಾಂಶ xsettings_ದತ್ತಾಂಶ;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    ರಚನೆ {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_ಕಿಟಕಿ;
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
        Atom NET_WM_ಕಿಟಕಿ_OPACITY;
        Atom NET_WM_USER_ಸಮಯ;
        Atom NET_ಸಕ್ರಿಯ_ಕಿಟಕಿ;
        Atom NET_ಚೌಕಟ್ಟು_EXTENTS;
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
        Atom Xdnd_ಸ್ಥಿತಿ;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom Xdnd_ಪೂರ್ಣಗೊಂಡ;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_ಗುಣಲಬ್ಧ_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_ಕಾಯುವಿಕೆ;
    bool selection_incr_ಕಾಯುವಿಕೆ;

    bool broken_ಸೂಚಕ_grab; // true if XGrabPointer seems unreliable.

    Uint64 ಕೊನೆಯ_ಬಹುಲಕ_change_deadline;

    bool global_mouse_ಬದಲಾಯಿತು;
    SDL_ಬಿಂದು global_mouse_position;
    Uint32 global_mouse_buttons;

    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ xinput_ಕೊನೆಯ_button_serial;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ xinput_ಕೊನೆಯ_ಕೀಲಿ_serial;
    ಪೂರ್ಣಾಂಕ xinput_ಕೊನೆಯ_keyboard_device;
    ಪೂರ್ಣಾಂಕ xinput_master_ಸೂಚಕ_device;
    bool xinput_hierarchy_ಬದಲಾಯಿತು;

    ಪೂರ್ಣಾಂಕ xrandr_event_ತಳ;
    ರಚನೆ
    {
        bool xkb_enabled;
        SDL_Scancode ಕೀಲಿ_layout[256];

        ಒಕ್ಕೂಟ
        {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            ರಚನೆ
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_ಅಂಕೆ_Kbd_Groups];
                ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಕೊನೆಯ_map_serial;
                ಪೂರ್ಣಾಂಕ event;
                Uint32 current_ಗುಂಪು;
            } xkb; // Modern XKB keyboard handling
#ಆದರೆ_ಅಂತ್ಯ
            ರಚನೆ
            {
                ಕೀಲಿ_Sym *keysym_map;
                ಪೂರ್ಣಾಂಕ keysyms_ಪ್ರತಿ_ಕೀಲಿ;
                ಪೂರ್ಣಾಂಕ min_keycode;
                ಪೂರ್ಣಾಂಕ max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_ಮುಖವಾಡ;
        Uint32 gui_ಮುಖವಾಡ;
        Uint32 level3_ಮುಖವಾಡ;
        Uint32 level5_ಮುಖವಾಡ;
        Uint32 numlock_ಮುಖವಾಡ;
        Uint32 scrolllock_ಮುಖವಾಡ;
    } keyboard;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#ಆದರೆ_ಅಂತ್ಯ

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

ಬಾಹ್ಯ bool X11_Use_ನೇರ_Color_Visuals(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11video_h_
