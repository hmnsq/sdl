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
#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_x11video_h_
#परिभाषय SDL_x11video_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_keymap_c.h"

#अन्तर्भाव "../../core/linux/SDL_dbus.h"
#अन्तर्भाव "../../core/linux/SDL_ime.h"

#अन्तर्भाव "SDL_x11dyn.h"

#अन्तर्भाव "SDL_x11clipboard.h"
#अन्तर्भाव "SDL_x11events.h"
#अन्तर्भाव "SDL_x11keyboard.h"
#अन्तर्भाव "SDL_x11modes.h"
#अन्तर्भाव "SDL_x11mouse.h"
#अन्तर्भाव "SDL_x11opengl.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "SDL_x11window.h"
#अन्तर्भाव "SDL_x11vulkan.h"

// Private display data

संरचना SDL_Video_दत्त
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    पूर्णाङ्क numwindows;
    SDL_गवाक्षः_दत्त **windowlist;
    पूर्णाङ्क windowlistlength;
    XID गवाक्षः_गणः;
    गवाक्षः_2 clipboard_गवाक्षः;
    SDLX11_Clipboard_दत्त clipboard;
    SDLX11_Clipboard_दत्त primary_selection;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_गवाक्षः *सक्रिय_cursor_confined_गवाक्षः;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
    गवाक्षः_2 xsettings_गवाक्षः;
    SDLX11_Settings_दत्त xsettings_दत्त;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    संरचना {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_गवाक्षः;
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
        Atom NET_WM_गवाक्षः_OPACITY;
        Atom _NET_WM_USER_TIME;
        Atom NET_सक्रिय_गवाक्षः;
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
        Atom Xdnd_स्थितिः;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom Xdnd_परिसमाप्तम्;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_गुणनफलम्_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_प्रतीक्षा;
    bool selection_incr_प्रतीक्षा;

    bool broken_pointer_grab; // true if XGrabPointer seems unreliable.

    Uint64 चरमः_बहुलकम्_change_deadline;

    bool global_mouse_परिवर्तितम्;
    SDL_Point global_mouse_position;
    Uint32 global_mouse_buttons;

    अचिह्नित दीर्घ xinput_चरमः_button_serial;
    अचिह्नित दीर्घ xinput_चरमः_कुञ्चिका_serial;
    पूर्णाङ्क xinput_चरमः_keyboard_device;
    पूर्णाङ्क xinput_master_pointer_device;
    bool xinput_hierarchy_परिवर्तितम्;

    पूर्णाङ्क xrandr_event_आधारः;
    संरचना
    {
        bool xkb_enabled;
        SDL_Scancode कुञ्चिका_layout[256];

        सङ्घ
        {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            संरचना
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_अङ्कः_Kbd_Groups];
                अचिह्नित दीर्घ चरमः_map_serial;
                पूर्णाङ्क event;
                Uint32 current_गणः;
            } xkb; // Modern XKB keyboard handling
#यदि_अन्तः
            संरचना
            {
                कुञ्चिका_Sym *keysym_map;
                पूर्णाङ्क keysyms_प्रत्येकम्_कुञ्चिका;
                पूर्णाङ्क min_keycode;
                पूर्णाङ्क max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_आवरणम्;
        Uint32 gui_आवरणम्;
        Uint32 level3_आवरणम्;
        Uint32 level5_आवरणम्;
        Uint32 numlock_आवरणम्;
        Uint32 scrolllock_आवरणम्;
    } keyboard;

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#यदि_अन्तः

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

बाह्य bool X11_Use_प्रत्यक्षम्_Color_Visuals(शून्य);

#यदि_अन्तः // SDL_x11video_h_
