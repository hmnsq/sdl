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

#अगर_अघोषित SDL_x11video_h_
#घोषणा SDL_x11video_h_

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_keymap_c.h"

#समावेश "../../core/linux/SDL_dbus.h"
#समावेश "../../core/linux/SDL_ime.h"

#समावेश "SDL_x11dyn.h"

#समावेश "SDL_x11clipboard.h"
#समावेश "SDL_x11events.h"
#समावेश "SDL_x11keyboard.h"
#समावेश "SDL_x11modes.h"
#समावेश "SDL_x11mouse.h"
#समावेश "SDL_x11opengl.h"
#समावेश "SDL_x11settings.h"
#समावेश "SDL_x11window.h"
#समावेश "SDL_x11vulkan.h"

// Private display data

काष्ठा SDL_Video_तथ्य
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    पूर्णांक numwindows;
    SDL_Window_तथ्य **windowlist;
    पूर्णांक windowlistlength;
    XID window_group;
    Window clipboard_window;
    SDLX11_Clipboard_तथ्य clipboard;
    SDLX11_Clipboard_तथ्य primary_selection;
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_Window *active_cursor_confined_window;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XFIXES
    Window xsettings_window;
    SDLX11_Settings_तथ्य xsettings_तथ्य;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    काष्ठा {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_WINDOW;
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
        Atom NET_WM_SYNC_REQUEST_गणक;
        Atom _NET_WM_WINDOW_OPACITY;
        Atom _NET_WM_USER_TIME;
        Atom _NET_ACTIVE_WINDOW;
        Atom _NET_FRAME_EXTENTS;
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
        Atom XdndStatus;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom XdndFinished;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_product_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_waiting;
    bool selection_incr_waiting;

    bool broken_pointer_grab; // true if XGrabPointer seems unreliable.

    Uint64 last_mode_change_deadline;

    bool global_mouse_changed;
    SDL_Point global_mouse_position;
    Uint32 global_mouse_buttons;

    अचिन्हित दीर्घ xinput_last_button_serial;
    अचिन्हित दीर्घ xinput_last_कुंजी_serial;
    पूर्णांक xinput_last_keyboard_device;
    पूर्णांक xinput_master_pointer_device;
    bool xinput_hierarchy_changed;

    पूर्णांक xrandr_event_base;
    काष्ठा
    {
        bool xkb_enabled;
        SDL_Scancode कुंजी_layout[256];

        जोड़
        {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            काष्ठा
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_अंक_Kbd_Groups];
                अचिन्हित दीर्घ last_map_serial;
                पूर्णांक event;
                Uint32 current_group;
            } xkb; // Modern XKB keyboard handling
#पूर्ण_अगर
            काष्ठा
            {
                कुंजी_Sym *keysym_map;
                पूर्णांक keysyms_per_कुंजी;
                पूर्णांक min_keycode;
                पूर्णांक max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_mask;
        Uint32 gui_mask;
        Uint32 level3_mask;
        Uint32 level5_mask;
        Uint32 numlock_mask;
        Uint32 scrolllock_mask;
    } keyboard;

#अगर_घोषित SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#पूर्ण_अगर

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

बाह्य bool X11_UseDirectColorVisuals(व्योम);

#पूर्ण_अगर // SDL_x11video_h_
