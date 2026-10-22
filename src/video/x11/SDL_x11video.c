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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

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

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#جے_انت

// Initialization/Query functions
ساكن bool X11_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساكن فراغ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_انکڑے *انکڑے = device->اندرونی;
    إذا (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    إذا (انکڑے->display) {
        X11_XCloseDisplay(انکڑے->display);
    }
    إذا (انکڑے->request_display) {
        X11_XCloseDisplay(انکڑے->request_display);
    }
    SDL_free(انکڑے->windowlist);
    SDL_free(device->اندرونی);
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
#جے_تعریف_شدہ SDL_PLATFORM_LINUX
    إذا (SDL_Get_رستہ_Info("/proc/sys/fs/binfmt_misc/WSLInterop", عدم) || SDL_Get_رستہ_Info("/run/WSL", عدم)) { // if either of these exist, we're on WSL.
         أرجع true;
    }
#جے_انت
    أرجع false;
}

ساكن SDL_VideoDevice *X11_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *انکڑے;
    ثابت حرف *display = عدم; // Use the DISPLAY environment variable
    Display *x11_display = عدم;

    إذا (!SDL_X11_لدو_Symbols()) {
        أرجع عدم;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_دھاگے();

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
    انکڑے = (بنية SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!انکڑے) {
        SDL_free(device);
        أرجع عدم;
    }
    device->اندرونی = انکڑے;

    انکڑے->global_mouse_بدلیا = true;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    انکڑے->سرگرم_cursor_confined_کھڑکی = عدم;
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES

    انکڑے->display = x11_display;
    انکڑے->request_display = X11_XOpenDisplay(display);
    إذا (!انکڑے->request_display) {
        X11_XCloseDisplay(انکڑے->display);
        SDL_free(device->اندرونی);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        أرجع عدم;
    }

#جے_تعریف_شدہ X11_DEBUG
    X11_XSynchronize(انکڑے->display, True);
#جے_انت

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    انکڑے->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_کھڑکی_ICCProfile = X11_Get_کھڑکی_ICCProfile;
    device->سیٹ_Display_منوال = X11_سیٹ_Display_منوال;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = X11_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = X11_سیٹ_کھڑکی_Icon;
    device->سیٹ_کھڑکی_Position = X11_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = X11_سیٹ_کھڑکی_ناپ;
    device->سیٹ_کھڑکی_Minimum_ناپ = X11_سیٹ_کھڑکی_Minimum_ناپ;
    device->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ = X11_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ;
    device->سیٹ_کھڑکی_Aspect_تناسب = X11_سیٹ_کھڑکی_Aspect_تناسب;
    device->Get_کھڑکی_Borders_ناپ = X11_Get_کھڑکی_Borders_ناپ;
    device->سیٹ_کھڑکی_Opacity = X11_سیٹ_کھڑکی_Opacity;
    device->سیٹ_کھڑکی_ماپا = X11_سیٹ_کھڑکی_ماپا;
    device->سیٹ_کھڑکی_Modal = X11_سیٹ_کھڑکی_Modal;
    device->Show_کھڑکی = X11_Show_کھڑکی;
    device->Hide_کھڑکی = X11_Hide_کھڑکی;
    device->Raise_کھڑکی = X11_Raise_کھڑکی;
    device->Maximize_کھڑکی = X11_Maximize_کھڑکی;
    device->Minimize_کھڑکی = X11_Minimize_کھڑکی;
    device->Restore_کھڑکی = X11_Restore_کھڑکی;
    device->سیٹ_کھڑکی_Bordered = X11_سیٹ_کھڑکی_Bordered;
    device->سیٹ_کھڑکی_Resizable = X11_سیٹ_کھڑکی_Resizable;
    device->سیٹ_کھڑکی_Always_On_چوٹی = X11_سیٹ_کھڑکی_Always_On_چوٹی;
    device->سیٹ_کھڑکی_Fullscreen = X11_سیٹ_کھڑکی_Fullscreen;
    device->سیٹ_کھڑکی_Mouse_Grab = X11_سیٹ_کھڑکی_Mouse_Grab;
    device->سیٹ_کھڑکی_Keyboard_Grab = X11_سیٹ_کھڑکی_Keyboard_Grab;
    device->Destroy_کھڑکی = X11_Destroy_کھڑکی;
    device->Create_کھڑکی_Framebuffer = X11_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = X11_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = X11_Destroy_کھڑکی_Framebuffer;
    device->سیٹ_کھڑکی_کامیابی_Test = X11_سیٹ_کھڑکی_کامیابی_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_کھڑکی_Shape = X11_Update_کھڑکی_Shape;
    device->Flash_کھڑکی = X11_Flash_کھڑکی;
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    device->Apply_کھڑکی_ترقی = DBUS_Apply_کھڑکی_ترقی;
#جے_انت // SDL_USE_LIBDBUS
    device->Show_کھڑکی_System_Menu = X11_Show_کھڑکی_System_Menu;
    device->سیٹ_کھڑکی_Focusable = X11_سیٹ_کھڑکی_Focusable;
    device->Sync_کھڑکی = X11_Sync_کھڑکی;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    device->سیٹ_کھڑکی_Mouse_Rect = X11_سیٹ_کھڑکی_Mouse_Rect;
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    device->GL_لدو_Library = X11_GL_لدو_Library;
    device->GL_Get_Proc_پتہ = X11_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = X11_GL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = X11_GL_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = X11_GL_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#جے_انت
        device->GL_لدو_Library = X11_GLES_لدو_Library;
        device->GL_Get_Proc_پتہ = X11_GLES_Get_Proc_پتہ;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_سیٹ_وٹاندرا_Interval = X11_GLES_سیٹ_وٹاندرا_Interval;
        device->GL_Get_وٹاندرا_Interval = X11_GLES_Get_وٹاندرا_Interval;
        device->GL_وٹاندرا_کھڑکی = X11_GLES_وٹاندرا_کھڑکی;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_سیٹ_Default_Profile_Config = X11_GLES_سیٹ_Default_Profile_Config;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    }
#جے_انت
#جے_انت

    device->Get_متن_Mime_Types = X11_Get_متن_Mime_Types;
    device->سیٹ_Clipboard_انکڑے = X11_سیٹ_Clipboard_انکڑے;
    device->Get_Clipboard_انکڑے = X11_Get_Clipboard_انکڑے;
    device->Has_Clipboard_انکڑے = X11_Has_Clipboard_انکڑے;
    device->سیٹ_Primary_Selection_متن = X11_سیٹ_Primary_Selection_متن;
    device->Get_Primary_Selection_متن = X11_Get_Primary_Selection_متن;
    device->Has_Primary_Selection_متن = X11_Has_Primary_Selection_متن;
    device->شروع_متن_داخلہ = X11_شروع_متن_داخلہ;
    device->Stop_متن_داخلہ = X11_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = X11_Update_متن_داخلہ_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->حرر = X11_DeleteDevice;

#جے_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_لدو_Library = X11_Vulkan_لدو_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#جے_انت

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#جے_انت

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    انکڑے->is_xwayland = X11_IsXWayland(x11_display);
    إذا (انکڑے->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED |
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
    X11_Show_سنیہا_Box,
    false
};

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح X11_Check_کھڑکی_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوڈ == Bad_کھڑکی) {
        أرجع 0;
    } وإلا {
        أرجع handler(d, e);
    }
}

ساكن فراغ X11_Check_کھڑکی_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    Display *display = انکڑے->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحيح حالت, real_format;
    Atom real_type;
    بنانشانی لما اشیاء_read = 0, اشیاء_بایاں = 0;
    بنانشانی حرف *propdata = عدم;
    کھڑکی_2 wm_کھڑکی = 0;
#جے_تعریف_شدہ DEBUG_کھڑکی_MANAGER
    حرف *wm_name;
#جے_انت

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_کھڑکی_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    حالت = X11_XGet_کھڑکی_Property(display, Default_جڑ_کھڑکی(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کھڑکی, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
    إذا (حالت == Success) {
        إذا (اشیاء_read) {
            wm_کھڑکی = ((کھڑکی_2 *)propdata)[0];
        }
        إذا (propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    إذا (wm_کھڑکی) {
        حالت = X11_XGet_کھڑکی_Property(display, wm_کھڑکی, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کھڑکی, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
        إذا (حالت != Success || !اشیاء_read || wm_کھڑکی != ((کھڑکی_2 *)propdata)[0]) {
            wm_کھڑکی = None;
        }
        إذا (حالت == Success && propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    إذا (!wm_کھڑکی) {
#جے_تعریف_شدہ DEBUG_کھڑکی_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#جے_انت
        أرجع;
    }
    انکڑے->net_wm = true;

#جے_تعریف_شدہ DEBUG_کھڑکی_MANAGER
    wm_name = X11_Get_کھڑکی_Title(_this, wm_کھڑکی);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#جے_انت
}

ساكن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    // Get the process PID to be associated to the window
    انکڑے->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    انکڑے->کھڑکی_گروہ = (XID)(((size_t)انکڑے->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#تعریف_کرو GET_ATOM(X) انکڑے->atoms.X = X11_XInternAtom(انکڑے->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_کھڑکی);
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
    GET_ATOM(NET_WM_کھڑکی_OPACITY);
    GET_ATOM(NET_WM_USER_ویلا);
    GET_ATOM(NET_سرگرم_کھڑکی);
    GET_ATOM(NET_چوکھٹا_EXTENTS);
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
    GET_ATOM(Xdnd_مکمل);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_کھڑکی_Manager(_this);

    إذا (!X11_InitModes(_this)) {
        أرجع false;
    }

    إذا (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
        SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#جے_انت

    X11_InitXsettings(_this);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#جے_انت

#جے_بنا_تعریف X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced وچ_2 2000! This is likely منزل become a hard error وچ_2 a future libSDL3.
#جے_انت

    إذا (!X11_InitKeyboard(_this)) {
        أرجع false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(انکڑے->display, انکڑے->atoms.CLIPBOARD, انکڑے->atoms.TARGETS,
            انکڑے->atoms.SDL_FORMATS, Get_کھڑکی(_this), Current_ویلا);

    أرجع true;
}

فراغ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    إذا (انکڑے->clipboard_کھڑکی) {
        X11_XDestroy_کھڑکی(انکڑے->display, انکڑے->clipboard_کھڑکی);
    }

    إذا (انکڑے->xsettings_کھڑکی) {
        X11_XDestroy_کھڑکی(انکڑے->display, انکڑے->xsettings_کھڑکی);
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

bool X11_Use_سدھا_Color_Visuals(فراغ)
{
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        أرجع false;
    }
    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_X11
