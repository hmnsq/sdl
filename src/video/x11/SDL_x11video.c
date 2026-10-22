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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن <unistd.h> // For getpid() and readlink()

#ضمن "../../core/linux/SDL_system_theme.h"
#ضمن "../../core/linux/SDL_progressbar.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11touch.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xfixes.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11messagebox.h"
#ضمن "SDL_x11shape.h"
#ضمن "SDL_x11xsync.h"
#ضمن "SDL_x11xtest.h"

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#د_که_پای

// Initialization/Query functions
ساكن bool X11_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساكن فراغ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;
    إذا (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    إذا (معلومات->display) {
        X11_XCloseDisplay(معلومات->display);
    }
    إذا (معلومات->request_display) {
        X11_XCloseDisplay(معلومات->request_display);
    }
    SDL_free(معلومات->windowlist);
    SDL_free(device->دننی);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

ساكن bool X11_IsXWayland(Display *d)
{
    صحيح opcode, event, error;
    أرجع X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

ساكن bool X11_IsWSL(فراغ)
{
#که_تعریف_شوی SDL_PLATFORM_LINUX
    إذا (SDL_Get_لار_Info("/proc/sys/fs/binfmt_misc/WSLInterop", عدم) || SDL_Get_لار_Info("/run/WSL", عدم)) { // if either of these exist, we're on WSL.
         أرجع true;
    }
#د_که_پای
    أرجع false;
}

ساكن SDL_VideoDevice *X11_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;
    ثابت حرف *display = عدم; // Use the DISPLAY environment variable
    Display *x11_display = عدم;

    إذا (!SDL_X11_بارول_Symbols()) {
        أرجع عدم;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_تارونه();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    إذا (!x11_display) {
        SDL_X11_UnloadSymbols();

        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        إذا (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } وإلا {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        أرجع عدم;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }
    معلومات = (بنية SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!معلومات) {
        SDL_free(device);
        أرجع عدم;
    }
    device->دننی = معلومات;

    معلومات->global_mouse_بدل_شوی = true;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    معلومات->فعال_cursor_confined_کړکۍ = عدم;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES

    معلومات->display = x11_display;
    معلومات->request_display = X11_XOpenDisplay(display);
    إذا (!معلومات->request_display) {
        X11_XCloseDisplay(معلومات->display);
        SDL_free(device->دننی);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        أرجع عدم;
    }

#که_تعریف_شوی X11_DEBUG
    X11_XSynchronize(معلومات->display, True);
#د_که_پای

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    معلومات->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_کړکۍ_ICCProfile = X11_Get_کړکۍ_ICCProfile;
    device->سېټ_Display_ډېرپېښ = X11_سېټ_Display_ډېرپېښ;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = X11_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Icon = X11_سېټ_کړکۍ_Icon;
    device->سېټ_کړکۍ_Position = X11_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = X11_سېټ_کړکۍ_اندازه;
    device->سېټ_کړکۍ_Minimum_اندازه = X11_سېټ_کړکۍ_Minimum_اندازه;
    device->سېټ_کړکۍ_اعظمي_اندازه = X11_سېټ_کړکۍ_اعظمي_اندازه;
    device->سېټ_کړکۍ_Aspect_نسبت = X11_سېټ_کړکۍ_Aspect_نسبت;
    device->Get_کړکۍ_Borders_اندازه = X11_Get_کړکۍ_Borders_اندازه;
    device->سېټ_کړکۍ_Opacity = X11_سېټ_کړکۍ_Opacity;
    device->سېټ_کړکۍ_پلار = X11_سېټ_کړکۍ_پلار;
    device->سېټ_کړکۍ_Modal = X11_سېټ_کړکۍ_Modal;
    device->Show_کړکۍ = X11_Show_کړکۍ;
    device->Hide_کړکۍ = X11_Hide_کړکۍ;
    device->Raise_کړکۍ = X11_Raise_کړکۍ;
    device->Maximize_کړکۍ = X11_Maximize_کړکۍ;
    device->Minimize_کړکۍ = X11_Minimize_کړکۍ;
    device->Restore_کړکۍ = X11_Restore_کړکۍ;
    device->سېټ_کړکۍ_Bordered = X11_سېټ_کړکۍ_Bordered;
    device->سېټ_کړکۍ_Resizable = X11_سېټ_کړکۍ_Resizable;
    device->سېټ_کړکۍ_Always_On_سر = X11_سېټ_کړکۍ_Always_On_سر;
    device->سېټ_کړکۍ_Fullscreen = X11_سېټ_کړکۍ_Fullscreen;
    device->سېټ_کړکۍ_Mouse_Grab = X11_سېټ_کړکۍ_Mouse_Grab;
    device->سېټ_کړکۍ_Keyboard_Grab = X11_سېټ_کړکۍ_Keyboard_Grab;
    device->Destroy_کړکۍ = X11_Destroy_کړکۍ;
    device->Create_کړکۍ_Framebuffer = X11_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = X11_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = X11_Destroy_کړکۍ_Framebuffer;
    device->سېټ_کړکۍ_موندنه_Test = X11_سېټ_کړکۍ_موندنه_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_کړکۍ_Shape = X11_Update_کړکۍ_Shape;
    device->Flash_کړکۍ = X11_Flash_کړکۍ;
#که_تعریف_شوی SDL_USE_LIBDBUS
    device->Apply_کړکۍ_پرمختګ = DBUS_Apply_کړکۍ_پرمختګ;
#د_که_پای // SDL_USE_LIBDBUS
    device->Show_کړکۍ_System_Menu = X11_Show_کړکۍ_System_Menu;
    device->سېټ_کړکۍ_Focusable = X11_سېټ_کړکۍ_Focusable;
    device->Sync_کړکۍ = X11_Sync_کړکۍ;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    device->سېټ_کړکۍ_Mouse_Rect = X11_سېټ_کړکۍ_Mouse_Rect;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES

#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
    device->GL_بارول_Library = X11_GL_بارول_Library;
    device->GL_Get_Proc_پته = X11_GL_Get_Proc_پته;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = X11_GL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = X11_GL_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = X11_GL_بدلون_کړکۍ;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#د_که_پای
        device->GL_بارول_Library = X11_GLES_بارول_Library;
        device->GL_Get_Proc_پته = X11_GLES_Get_Proc_پته;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_سېټ_بدلون_Interval = X11_GLES_سېټ_بدلون_Interval;
        device->GL_Get_بدلون_Interval = X11_GLES_Get_بدلون_Interval;
        device->GL_بدلون_کړکۍ = X11_GLES_بدلون_کړکۍ;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_سېټ_Default_Profile_Config = X11_GLES_سېټ_Default_Profile_Config;
#که_تعریف_شوی SDL_VIDEO_OPENGL_GLX
    }
#د_که_پای
#د_که_پای

    device->Get_متن_Mime_Types = X11_Get_متن_Mime_Types;
    device->سېټ_Clipboard_معلومات = X11_سېټ_Clipboard_معلومات;
    device->Get_Clipboard_معلومات = X11_Get_Clipboard_معلومات;
    device->Has_Clipboard_معلومات = X11_Has_Clipboard_معلومات;
    device->سېټ_Primary_Selection_متن = X11_سېټ_Primary_Selection_متن;
    device->Get_Primary_Selection_متن = X11_Get_Primary_Selection_متن;
    device->Has_Primary_Selection_متن = X11_Has_Primary_Selection_متن;
    device->پیل_متن_ننوت = X11_پیل_متن_ننوت;
    device->Stop_متن_ننوت = X11_Stop_متن_ننوت;
    device->Update_متن_ننوت_Area = X11_Update_متن_ننوت_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->حرر = X11_DeleteDevice;

#که_تعریف_شوی SDL_VIDEO_VULKAN
    device->Vulkan_بارول_Library = X11_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#د_که_پای

#که_تعریف_شوی SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#د_که_پای

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کړکۍ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    معلومات->is_xwayland = X11_IsXWayland(x11_display);
    إذا (معلومات->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_ډېرپېښ_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    إذا (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    أرجع device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_پیغام_Box,
    false
};

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح X11_Check_کړکۍ_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوډ == Bad_کړکۍ) {
        أرجع 0;
    } وإلا {
        أرجع handler(d, e);
    }
}

ساكن فراغ X11_Check_کړکۍ_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    Display *display = معلومات->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحيح حالت, real_format;
    Atom real_type;
    بینښه اوږد توکي_read = 0, توکي_کیڼ = 0;
    بینښه حرف *propdata = عدم;
    کړکۍ_2 wm_کړکۍ = 0;
#که_تعریف_شوی DEBUG_کړکۍ_MANAGER
    حرف *wm_name;
#د_که_پای

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_کړکۍ_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    حالت = X11_XGet_کړکۍ_Property(display, Default_ریښه_کړکۍ(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کړکۍ, &real_type, &real_format, &توکي_read, &توکي_کیڼ, &propdata);
    إذا (حالت == Success) {
        إذا (توکي_read) {
            wm_کړکۍ = ((کړکۍ_2 *)propdata)[0];
        }
        إذا (propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    إذا (wm_کړکۍ) {
        حالت = X11_XGet_کړکۍ_Property(display, wm_کړکۍ, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کړکۍ, &real_type, &real_format, &توکي_read, &توکي_کیڼ, &propdata);
        إذا (حالت != Success || !توکي_read || wm_کړکۍ != ((کړکۍ_2 *)propdata)[0]) {
            wm_کړکۍ = None;
        }
        إذا (حالت == Success && propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    إذا (!wm_کړکۍ) {
#که_تعریف_شوی DEBUG_کړکۍ_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#د_که_پای
        أرجع;
    }
    معلومات->net_wm = true;

#که_تعریف_شوی DEBUG_کړکۍ_MANAGER
    wm_name = X11_Get_کړکۍ_Title(_this, wm_کړکۍ);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#د_که_پای
}

ساكن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    // Get the process PID to be associated to the window
    معلومات->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    معلومات->کړکۍ_ډله = (XID)(((size_t)معلومات->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#تعریف_کړه GET_ATOM(X) معلومات->atoms.X = X11_XInternAtom(معلومات->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_کړکۍ);
    GET_ATOM(WM_NAME);
    GET_ATOM(WM_TRANSIENT_FOR);
    GET_ATOM(WM_STATE);
    GET_ATOM(_NET_WM_STATE);
    GET_ATOM(_NET_WM_STATE_HIDDEN);
    GET_ATOM(_NET_WM_STATE_FOCUSED);
    GET_ATOM(_NET_WM_STATE_MAXIMIZED_VERT);
    GET_ATOM(_NET_WM_STATE_MAXIMIZED_HORZ);
    GET_ATOM(_NET_WM_STATE_FULLSCREEN);
    GET_ATOM(_NET_WM_STATE_ABOVE);
    GET_ATOM(_NET_WM_STATE_SKIP_TASKBAR);
    GET_ATOM(_NET_WM_STATE_SKIP_PAGER);
    GET_ATOM(_NET_WM_MOVERESIZE);
    GET_ATOM(_NET_WM_STATE_MODAL);
    GET_ATOM(_NET_WM_ALLOWED_ACTIONS);
    GET_ATOM(_NET_WM_ACTION_FULLSCREEN);
    GET_ATOM(_NET_WM_NAME);
    GET_ATOM(_NET_WM_ICON_NAME);
    GET_ATOM(_NET_WM_ICON);
    GET_ATOM(_NET_WM_PING);
    GET_ATOM(_NET_WM_SYNC_REQUEST);
    GET_ATOM(_NET_WM_SYNC_REQUEST_COUNTER);
    GET_ATOM(NET_WM_کړکۍ_OPACITY);
    GET_ATOM(NET_WM_USER_وخت);
    GET_ATOM(NET_فعال_کړکۍ);
    GET_ATOM(NET_چوکاټ_EXTENTS);
    GET_ATOM(_SDL_WAKEUP);
    GET_ATOM(UTF8_STRING);
    GET_ATOM(PRIMARY);
    GET_ATOM(CLIPBOARD);
    GET_ATOM(INCR);
    GET_ATOM(SDL_SELECTION);
    GET_ATOM(TARGETS);
    GET_ATOM(SDL_FORMATS);
    GET_ATOM(RESOURCE_MANAGER);
    GET_ATOM(XdndAware);
    GET_ATOM(XdndEnter);
    GET_ATOM(XdndLeave);
    GET_ATOM(XdndPosition);
    GET_ATOM(Xdnd_حالت);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_پای_ته_رسېدلی);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_کړکۍ_Manager(_this);

    إذا (!X11_InitModes(_this)) {
        أرجع false;
    }

    إذا (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_جمع_کړه_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
        SDL_جمع_کړه_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#د_که_پای

    X11_InitXsettings(_this);

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#د_که_پای

#که_نه_تعریف_شوی X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced دننه_2 2000! This is likely منزل become a hard error دننه_2 a future libSDL3.
#د_که_پای

    إذا (!X11_InitKeyboard(_this)) {
        أرجع false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(معلومات->display, معلومات->atoms.CLIPBOARD, معلومات->atoms.TARGETS,
            معلومات->atoms.SDL_FORMATS, Get_کړکۍ(_this), Current_وخت);

    أرجع true;
}

فراغ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    إذا (معلومات->clipboard_کړکۍ) {
        X11_XDestroy_کړکۍ(معلومات->display, معلومات->clipboard_کړکۍ);
    }

    إذا (معلومات->xsettings_کړکۍ) {
        X11_XDestroy_کړکۍ(معلومات->display, معلومات->xsettings_کړکۍ);
    }

    X11_QuitXinput2(_this);
    X11_QuitModes(_this);
    X11_QuitKeyboard(_this);
    X11_QuitMouse(_this);
    X11_QuitTouch(_this);
    X11_QuitPen(_this);
    X11_QuitClipboard(_this);
    X11_QuitXsettings(_this);
}

bool X11_Use_مستقیم_Color_Visuals(فراغ)
{
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        أرجع false;
    }
    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
