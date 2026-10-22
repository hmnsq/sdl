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

#నిర్వచితం_కాకపోతే SDL_x11video_h_
#నిర్వచించు SDL_x11video_h_

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_keymap_c.h"

#అన్తర్భావ "../../core/linux/SDL_dbus.h"
#అన్తర్భావ "../../core/linux/SDL_ime.h"

#అన్తర్భావ "SDL_x11dyn.h"

#అన్తర్భావ "SDL_x11clipboard.h"
#అన్తర్భావ "SDL_x11events.h"
#అన్తర్భావ "SDL_x11keyboard.h"
#అన్తర్భావ "SDL_x11modes.h"
#అన్తర్భావ "SDL_x11mouse.h"
#అన్తర్భావ "SDL_x11opengl.h"
#అన్తర్భావ "SDL_x11settings.h"
#అన్తర్భావ "SDL_x11window.h"
#అన్తర్భావ "SDL_x11vulkan.h"

// Private display data

నిర్మాణం SDL_Video_దత్తాంశం
{
    Display *display;
    Display *request_display;
    pid_t pid;
    XIM im;
    Uint64 screensaver_activity;
    పూర్ణాంకం numwindows;
    SDL_కిటికీ_దత్తాంశం **windowlist;
    పూర్ణాంకం windowlistlength;
    XID కిటికీ_సమూహం;
    కిటికీ_2 clipboard_కిటికీ;
    SDLX11_Clipboard_దత్తాంశం clipboard;
    SDLX11_Clipboard_దత్తాంశం primary_selection;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    SDL_కిటికీ *చురుకైన_cursor_confined_కిటికీ;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
    కిటికీ_2 xsettings_కిటికీ;
    SDLX11_Settings_దత్తాంశం xsettings_దత్తాంశం;

    // This is true for ICCCM2.0-compliant window managers
    bool net_wm;

    // Useful atoms
    నిర్మాణం {
        Atom WM_PROTOCOLS;
        Atom WM_DELETE_కిటికీ;
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
        Atom NET_WM_కిటికీ_OPACITY;
        Atom NET_WM_USER_సమయం;
        Atom NET_చురుకైన_కిటికీ;
        Atom NET_చట్రం_EXTENTS;
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
        Atom Xdnd_స్థితి;
        Atom XdndTypeList;
        Atom XdndActionCopy;
        Atom XdndDrop;
        Atom Xdnd_ముగిసిన;
        Atom XdndSelection;
        Atom XKLAVIER_STATE;

        // Pen atoms (these have names that don't map well to C symbols)
        Atom pen_atom_device_లబ్ధం_id;
        Atom pen_atom_abs_pressure;
        Atom pen_atom_abs_tilt_x;
        Atom pen_atom_abs_tilt_y;
        Atom pen_atom_wacom_serial_ids;
        Atom pen_atom_wacom_tool_type;
    } atoms;

    bool selection_నిరీక్షణ;
    bool selection_incr_నిరీక్షణ;

    bool broken_సూచిక_grab; // true if XGrabPointer seems unreliable.

    Uint64 చివరి_బహుళకం_change_deadline;

    bool global_mouse_మారింది;
    SDL_బిందువు global_mouse_position;
    Uint32 global_mouse_buttons;

    గుర్తులేని దీర్ఘ xinput_చివరి_button_serial;
    గుర్తులేని దీర్ఘ xinput_చివరి_కీలకం_serial;
    పూర్ణాంకం xinput_చివరి_keyboard_device;
    పూర్ణాంకం xinput_master_సూచిక_device;
    bool xinput_hierarchy_మారింది;

    పూర్ణాంకం xrandr_event_పునాది;
    నిర్మాణం
    {
        bool xkb_enabled;
        SDL_Scancode కీలకం_layout[256];

        సంఘం
        {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
            నిర్మాణం
            {
                XkbDescPtr desc_ptr;
                SDL_Keymap *keymaps[Xkb_అంకె_Kbd_Groups];
                గుర్తులేని దీర్ఘ చివరి_map_serial;
                పూర్ణాంకం event;
                Uint32 current_సమూహం;
            } xkb; // Modern XKB keyboard handling
#అయితే_ముగింపు
            నిర్మాణం
            {
                కీలకం_Sym *keysym_map;
                పూర్ణాంకం keysyms_చొప్పున_కీలకం;
                పూర్ణాంకం min_keycode;
                పూర్ణాంకం max_keycode;
            } core; // Legacy core keyboard handling
        };
        Uint32 pressed_modifiers;
        Uint32 locked_modifiers;
        SDL_Keymod sdl_pressed_modifiers;
        SDL_Keymod sdl_physically_pressed_modifiers;
        SDL_Keymod sdl_locked_modifiers;

        // Virtual modifiers looked up by name.
        Uint32 alt_ముసుగు;
        Uint32 gui_ముసుగు;
        Uint32 level3_ముసుగు;
        Uint32 level5_ముసుగు;
        Uint32 numlock_ముసుగు;
        Uint32 scrolllock_ముసుగు;
    } keyboard;

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    // Vulkan variables only valid if _this->vulkan_config.loader_handle is not NULL
    SDL_SharedObject *vulkan_xlib_xcb_library;
    PFN_XGetXCBConnection vulkan_XGetXCBConnection;
#అయితే_ముగింపు

    // Used to interact with the on-screen keyboard
    bool use_steam_screen_keyboard;

    bool is_xwayland;
};

బాహ్య bool X11_Use_ప్రత్యక్ష_Color_Visuals(శూన్య);

#అయితే_ముగింపు // SDL_x11video_h_
