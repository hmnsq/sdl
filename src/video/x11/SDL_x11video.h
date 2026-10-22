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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11video_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11video_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keymap_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_dbus.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_ime.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11dyn.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11clipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11events.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11keyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11modes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11mouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11window.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11vulkan.h"

// Private display data

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    ਪੂਰਨ numwindows;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ **windowlist;
    ਪੂਰਨ windowlistlength;
    XID ਖਿੜਕੀ_ਸਮੂਹ;
    ਖਿੜਕੀ_2 clipboard_ਖਿੜਕੀ;
    SDLX11_Clipboard_ਅੰਕੜੇ clipboard;
    SDLX11_Clipboard_ਅੰਕੜੇ primary_selection;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_ਖਿੜਕੀ *ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
    ਖਿੜਕੀ_2 xsettings_ਖਿੜਕੀ;
    SDLX11_Settings_ਅੰਕੜੇ xsettings_ਅੰਕੜੇ;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    ਬਣਤਰ {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_ਖਿੜਕੀ;
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
        Atom NET_WM_ਖਿੜਕੀ_OPACITY;
        Atom NET_WM_USER_ਸਮਾਂ;
        Atom NET_ਸਰਗਰਮ_ਖਿੜਕੀ;
        Atom NET_ਚੌਖਟਾ_EXTENTS;
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
        Atom Xdnd_ਸਥਿਤੀ;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom Xdnd_ਮੁਕੰਮਲ;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_ਗੁਣਨਫਲ_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_ਉਡੀਕ;
    bool selection_incr_ਉਡੀਕ;

    bool broken_ਸੂਚਕ_grab; // true if XGrabPointer seems unreliable.

    Uint64 ਆਖਰੀ_ਬਹੁਲਕ_change_deadline;

    bool global_mouse_ਬਦਲਿਆ;
    SDL_ਬਿੰਦੂ global_mouse_position;
    Uint32 global_mouse_buttons;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ xinput_ਆਖਰੀ_button_serial;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ xinput_ਆਖਰੀ_ਕੁੰਜੀ_serial;
    ਪੂਰਨ xinput_ਆਖਰੀ_keyboard_device;
    ਪੂਰਨ xinput_master_ਸੂਚਕ_device;
    bool xinput_hierarchy_ਬਦਲਿਆ;

    ਪੂਰਨ xrandr_event_ਅਧਾਰ;
    ਬਣਤਰ
    {
        bool xkb_enabled;
        SDL_Scancode ਕੁੰਜੀ_layout[256];

        ਸੰਘ
        {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            ਬਣਤਰ
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_ਅੰਕ_Kbd_Groups];
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਆਖਰੀ_map_serial;
                ਪੂਰਨ event;
                Uint32 current_ਸਮੂਹ;
            } xkb; // Modern XKB keyboard handling
#ਜੇ_ਅੰਤ
            ਬਣਤਰ
            {
                ਕੁੰਜੀ_Sym *keysym_map;
                ਪੂਰਨ keysyms_ਪ੍ਰਤੀ_ਕੁੰਜੀ;
                ਪੂਰਨ min_keycode;
                ਪੂਰਨ max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_ਨਕਾਬ;
        Uint32 gui_ਨਕਾਬ;
        Uint32 level3_ਨਕਾਬ;
        Uint32 level5_ਨਕਾਬ;
        Uint32 numlock_ਨਕਾਬ;
        Uint32 scrolllock_ਨਕਾਬ;
    } keyboard;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#ਜੇ_ਅੰਤ

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

ਬਾਹਰੀ bool X11_Use_ਸਿੱਧਾ_Color_Visuals(ਖਾਲੀ);

#ਜੇ_ਅੰਤ // SDL_x11video_h_
