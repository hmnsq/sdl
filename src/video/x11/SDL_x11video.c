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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#جيڪڏهن_پورو

// Initialization/Query functions
ساكن bool X11_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساكن فراغ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->اندروني;
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
    SDL_free(device->اندروني);
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
#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_LINUX
    إذا (SDL_Get_رستو_Info("/proc/sys/fs/binfmt_misc/WSLInterop", عدم) || SDL_Get_رستو_Info("/run/WSL", عدم)) { // if either of these exist, we're on WSL.
         أرجع true;
    }
#جيڪڏهن_پورو
    أرجع false;
}

ساكن SDL_VideoDevice *X11_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;
    ثابت حرف *display = عدم; // Use the DISPLAY environment variable
    Display *x11_display = عدم;

    إذا (!SDL_X11_ڀريو_Symbols()) {
        أرجع عدم;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_ڌاڳا();

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
    device->اندروني = معلومات;

    معلومات->global_mouse_بدليو = true;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    معلومات->سرگرم_cursor_confined_دري = عدم;
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES

    معلومات->display = x11_display;
    معلومات->request_display = X11_XOpenDisplay(display);
    إذا (!معلومات->request_display) {
        X11_XCloseDisplay(معلومات->display);
        SDL_free(device->اندروني);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        أرجع عدم;
    }

#جيڪڏهن_وصف_ٿيل X11_DEBUG
    X11_XSynchronize(معلومات->display, True);
#جيڪڏهن_پورو

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
    device->Get_دري_ICCProfile = X11_Get_دري_ICCProfile;
    device->سيٽ_Display_گهڻائي = X11_سيٽ_Display_گهڻائي;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_دري;
    device->سيٽ_دري_Title = X11_سيٽ_دري_Title;
    device->سيٽ_دري_Icon = X11_سيٽ_دري_Icon;
    device->سيٽ_دري_Position = X11_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = X11_سيٽ_دري_سائيز;
    device->سيٽ_دري_Minimum_سائيز = X11_سيٽ_دري_Minimum_سائيز;
    device->سيٽ_دري_وڌ_کان_وڌ_سائيز = X11_سيٽ_دري_وڌ_کان_وڌ_سائيز;
    device->سيٽ_دري_Aspect_تناسب = X11_سيٽ_دري_Aspect_تناسب;
    device->Get_دري_Borders_سائيز = X11_Get_دري_Borders_سائيز;
    device->سيٽ_دري_Opacity = X11_سيٽ_دري_Opacity;
    device->سيٽ_دري_والد = X11_سيٽ_دري_والد;
    device->سيٽ_دري_Modal = X11_سيٽ_دري_Modal;
    device->Show_دري = X11_Show_دري;
    device->Hide_دري = X11_Hide_دري;
    device->Raise_دري = X11_Raise_دري;
    device->Maximize_دري = X11_Maximize_دري;
    device->Minimize_دري = X11_Minimize_دري;
    device->Restore_دري = X11_Restore_دري;
    device->سيٽ_دري_Bordered = X11_سيٽ_دري_Bordered;
    device->سيٽ_دري_Resizable = X11_سيٽ_دري_Resizable;
    device->سيٽ_دري_Always_On_چوٽي = X11_سيٽ_دري_Always_On_چوٽي;
    device->سيٽ_دري_Fullscreen = X11_سيٽ_دري_Fullscreen;
    device->سيٽ_دري_Mouse_Grab = X11_سيٽ_دري_Mouse_Grab;
    device->سيٽ_دري_Keyboard_Grab = X11_سيٽ_دري_Keyboard_Grab;
    device->Destroy_دري = X11_Destroy_دري;
    device->Create_دري_Framebuffer = X11_Create_دري_Framebuffer;
    device->Update_دري_Framebuffer = X11_Update_دري_Framebuffer;
    device->Destroy_دري_Framebuffer = X11_Destroy_دري_Framebuffer;
    device->سيٽ_دري_ڪاميابي_Test = X11_سيٽ_دري_ڪاميابي_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_دري_Shape = X11_Update_دري_Shape;
    device->Flash_دري = X11_Flash_دري;
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    device->Apply_دري_ترقي = DBUS_Apply_دري_ترقي;
#جيڪڏهن_پورو // SDL_USE_LIBDBUS
    device->Show_دري_System_Menu = X11_Show_دري_System_Menu;
    device->سيٽ_دري_Focusable = X11_سيٽ_دري_Focusable;
    device->Sync_دري = X11_Sync_دري;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    device->سيٽ_دري_Mouse_Rect = X11_سيٽ_دري_Mouse_Rect;
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
    device->GL_ڀريو_Library = X11_GL_ڀريو_Library;
    device->GL_Get_Proc_پتو = X11_GL_Get_Proc_پتو;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = X11_GL_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = X11_GL_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = X11_GL_مٽا_سٽا_دري;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#جيڪڏهن_پورو
        device->GL_ڀريو_Library = X11_GLES_ڀريو_Library;
        device->GL_Get_Proc_پتو = X11_GLES_Get_Proc_پتو;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_سيٽ_مٽا_سٽا_Interval = X11_GLES_سيٽ_مٽا_سٽا_Interval;
        device->GL_Get_مٽا_سٽا_Interval = X11_GLES_Get_مٽا_سٽا_Interval;
        device->GL_مٽا_سٽا_دري = X11_GLES_مٽا_سٽا_دري;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_سيٽ_Default_Profile_Config = X11_GLES_سيٽ_Default_Profile_Config;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_GLX
    }
#جيڪڏهن_پورو
#جيڪڏهن_پورو

    device->Get_متن_Mime_Types = X11_Get_متن_Mime_Types;
    device->سيٽ_Clipboard_معلومات = X11_سيٽ_Clipboard_معلومات;
    device->Get_Clipboard_معلومات = X11_Get_Clipboard_معلومات;
    device->Has_Clipboard_معلومات = X11_Has_Clipboard_معلومات;
    device->سيٽ_Primary_Selection_متن = X11_سيٽ_Primary_Selection_متن;
    device->Get_Primary_Selection_متن = X11_Get_Primary_Selection_متن;
    device->Has_Primary_Selection_متن = X11_Has_Primary_Selection_متن;
    device->شروعات_متن_داخلا = X11_شروعات_متن_داخلا;
    device->Stop_متن_داخلا = X11_Stop_متن_داخلا;
    device->Update_متن_داخلا_Area = X11_Update_متن_داخلا_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->حرر = X11_DeleteDevice;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = X11_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#جيڪڏهن_پورو

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_دري_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    معلومات->is_xwayland = X11_IsXWayland(x11_display);
    إذا (معلومات->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_گهڻائي_SWITCHING_EMULATED |
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
    X11_Show_پيغام_Box,
    false
};

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح X11_Check_دري_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_ڪوڊ == Bad_دري) {
        أرجع 0;
    } وإلا {
        أرجع handler(d, e);
    }
}

ساكن فراغ X11_Check_دري_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    Display *display = معلومات->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحيح حالت, real_format;
    Atom real_type;
    بنانشان ڊگهو شيون_read = 0, شيون_کاٻو = 0;
    بنانشان حرف *propdata = عدم;
    دري_2 wm_دري = 0;
#جيڪڏهن_وصف_ٿيل DEBUG_دري_MANAGER
    حرف *wm_name;
#جيڪڏهن_پورو

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_دري_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    حالت = X11_XGet_دري_Property(display, Default_پاڙ_دري(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_دري, &real_type, &real_format, &شيون_read, &شيون_کاٻو, &propdata);
    إذا (حالت == Success) {
        إذا (شيون_read) {
            wm_دري = ((دري_2 *)propdata)[0];
        }
        إذا (propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    إذا (wm_دري) {
        حالت = X11_XGet_دري_Property(display, wm_دري, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_دري, &real_type, &real_format, &شيون_read, &شيون_کاٻو, &propdata);
        إذا (حالت != Success || !شيون_read || wm_دري != ((دري_2 *)propdata)[0]) {
            wm_دري = None;
        }
        إذا (حالت == Success && propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    إذا (!wm_دري) {
#جيڪڏهن_وصف_ٿيل DEBUG_دري_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#جيڪڏهن_پورو
        أرجع;
    }
    معلومات->net_wm = true;

#جيڪڏهن_وصف_ٿيل DEBUG_دري_MANAGER
    wm_name = X11_Get_دري_Title(_this, wm_دري);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#جيڪڏهن_پورو
}

ساكن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    // Get the process PID to be associated to the window
    معلومات->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    معلومات->دري_گروهه = (XID)(((size_t)معلومات->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#وصف_ڪريو GET_ATOM(X) معلومات->atoms.X = X11_XInternAtom(معلومات->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_دري);
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
    GET_ATOM(NET_WM_دري_OPACITY);
    GET_ATOM(NET_WM_USER_وقت);
    GET_ATOM(NET_سرگرم_دري);
    GET_ATOM(NET_چوکٺو_EXTENTS);
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
    GET_ATOM(Xdnd_ختم);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_دري_Manager(_this);

    إذا (!X11_InitModes(_this)) {
        أرجع false;
    }

    إذا (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_جوڙيو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
        SDL_جوڙيو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#جيڪڏهن_پورو

    X11_InitXsettings(_this);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced اندريون_2 2000! This is likely منزل become a hard error اندريون_2 a future libSDL3.
#جيڪڏهن_پورو

    إذا (!X11_InitKeyboard(_this)) {
        أرجع false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(معلومات->display, معلومات->atoms.CLIPBOARD, معلومات->atoms.TARGETS,
            معلومات->atoms.SDL_FORMATS, Get_دري(_this), Current_وقت);

    أرجع true;
}

فراغ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    إذا (معلومات->clipboard_دري) {
        X11_XDestroy_دري(معلومات->display, معلومات->clipboard_دري);
    }

    إذا (معلومات->xsettings_دري) {
        X11_XDestroy_دري(معلومات->display, معلومات->xsettings_دري);
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

bool X11_Use_سڌو_Color_Visuals(فراغ)
{
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        أرجع false;
    }
    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
