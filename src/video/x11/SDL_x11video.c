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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل <unistd.h> // For getpid() and readlink()

#شامل "../../core/linux/SDL_system_theme.h"
#شامل "../../core/linux/SDL_progressbar.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../SDL_pixels_c.h"
#شامل "../SDL_sysvideo.h"

#شامل "SDL_x11framebuffer.h"
#شامل "SDL_x11pen.h"
#شامل "SDL_x11touch.h"
#شامل "SDL_x11video.h"
#شامل "SDL_x11xfixes.h"
#شامل "SDL_x11xinput2.h"
#شامل "SDL_x11messagebox.h"
#شامل "SDL_x11shape.h"
#شامل "SDL_x11xsync.h"
#شامل "SDL_x11xtest.h"

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#شامل "SDL_x11opengles.h"
#اگر_ختم

// Initialization/Query functions
ساکن bool X11_VideoInit(SDL_VideoDevice *_this);
ساکن خالی X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساکن خالی X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    اگر (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    اگر (ڈیٹا->display) {
        X11_XCloseDisplay(ڈیٹا->display);
    }
    اگر (ڈیٹا->request_display) {
        X11_XCloseDisplay(ڈیٹا->request_display);
    }
    SDL_free(ڈیٹا->windowlist);
    SDL_free(device->اندرونی_2);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

ساکن bool X11_IsXWayland(Display *d)
{
    صحیح opcode, event, error;
    واپس X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

ساکن bool X11_IsWSL(خالی)
{
#اگر_تعریف_شدہ SDL_PLATFORM_LINUX
    اگر (SDL_Get_راستہ_Info("/proc/sys/fs/binfmt_misc/WSLInterop", تہی) || SDL_Get_راستہ_Info("/run/WSL", تہی)) { // if either of these exist, we're on WSL.
         واپس true;
    }
#اگر_ختم
    واپس false;
}

ساکن SDL_VideoDevice *X11_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;
    ثابت حرف *display = تہی; // Use the DISPLAY environment variable
    Display *x11_display = تہی;

    اگر (!SDL_X11_بھرو_Symbols()) {
        واپس تہی;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_دھاگے();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    اگر (!x11_display) {
        SDL_X11_UnloadSymbols();

        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        اگر (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } ورنہ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        واپس تہی;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }
    ڈیٹا = (ساخت SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!ڈیٹا) {
        SDL_free(device);
        واپس تہی;
    }
    device->اندرونی_2 = ڈیٹا;

    ڈیٹا->global_mouse_بدلا = true;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    ڈیٹا->فعال_cursor_confined_کھڑکی = تہی;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES

    ڈیٹا->display = x11_display;
    ڈیٹا->request_display = X11_XOpenDisplay(display);
    اگر (!ڈیٹا->request_display) {
        X11_XCloseDisplay(ڈیٹا->display);
        SDL_free(device->اندرونی_2);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        واپس تہی;
    }

#اگر_تعریف_شدہ X11_DEBUG
    X11_XSynchronize(ڈیٹا->display, True);
#اگر_ختم

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    ڈیٹا->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

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
    device->سیٹ_کھڑکی_سائز = X11_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Minimum_سائز = X11_سیٹ_کھڑکی_Minimum_سائز;
    device->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز = X11_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز;
    device->سیٹ_کھڑکی_Aspect_تناسب = X11_سیٹ_کھڑکی_Aspect_تناسب;
    device->Get_کھڑکی_Borders_سائز = X11_Get_کھڑکی_Borders_سائز;
    device->سیٹ_کھڑکی_Opacity = X11_سیٹ_کھڑکی_Opacity;
    device->سیٹ_کھڑکی_والد = X11_سیٹ_کھڑکی_والد;
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
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    device->Apply_کھڑکی_پیش_رفت = DBUS_Apply_کھڑکی_پیش_رفت;
#اگر_ختم // SDL_USE_LIBDBUS
    device->Show_کھڑکی_System_Menu = X11_Show_کھڑکی_System_Menu;
    device->سیٹ_کھڑکی_Focusable = X11_سیٹ_کھڑکی_Focusable;
    device->Sync_کھڑکی = X11_Sync_کھڑکی;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    device->سیٹ_کھڑکی_Mouse_Rect = X11_سیٹ_کھڑکی_Mouse_Rect;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    device->GL_بھرو_Library = X11_GL_بھرو_Library;
    device->GL_Get_Proc_پتہ = X11_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = X11_GL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = X11_GL_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = X11_GL_تبادلہ_کھڑکی;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = تہی;
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#اگر_ختم
        device->GL_بھرو_Library = X11_GLES_بھرو_Library;
        device->GL_Get_Proc_پتہ = X11_GLES_Get_Proc_پتہ;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_سیٹ_تبادلہ_Interval = X11_GLES_سیٹ_تبادلہ_Interval;
        device->GL_Get_تبادلہ_Interval = X11_GLES_Get_تبادلہ_Interval;
        device->GL_تبادلہ_کھڑکی = X11_GLES_تبادلہ_کھڑکی;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_سیٹ_Default_Profile_Config = X11_GLES_سیٹ_Default_Profile_Config;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_GLX
    }
#اگر_ختم
#اگر_ختم

    device->Get_متن_Mime_Types = X11_Get_متن_Mime_Types;
    device->سیٹ_Clipboard_ڈیٹا = X11_سیٹ_Clipboard_ڈیٹا;
    device->Get_Clipboard_ڈیٹا = X11_Get_Clipboard_ڈیٹا;
    device->Has_Clipboard_ڈیٹا = X11_Has_Clipboard_ڈیٹا;
    device->سیٹ_Primary_Selection_متن = X11_سیٹ_Primary_Selection_متن;
    device->Get_Primary_Selection_متن = X11_Get_Primary_Selection_متن;
    device->Has_Primary_Selection_متن = X11_Has_Primary_Selection_متن;
    device->آغاز_متن_داخلہ = X11_آغاز_متن_داخلہ;
    device->Stop_متن_داخلہ = X11_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = X11_Update_متن_داخلہ_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->آزاد = X11_DeleteDevice;

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = X11_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#اگر_ختم

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    اگر (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#اگر_ختم

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ڈیٹا->is_xwayland = X11_IsXWayland(x11_display);
    اگر (ڈیٹا->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    اگر (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    واپس device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_پیغام_Box,
    false
};

ساکن صحیح (*handler)(Display *, XErrorEvent *) = تہی;
ساکن صحیح X11_Check_کھڑکی_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    اگر (e->error_رمز == Bad_کھڑکی) {
        واپس 0;
    } ورنہ {
        واپس handler(d, e);
    }
}

ساکن خالی X11_Check_کھڑکی_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Display *display = ڈیٹا->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحیح حالت_2, real_format;
    Atom real_type;
    غیرعلامتی طویل اشیاء_read = 0, اشیاء_بایاں = 0;
    غیرعلامتی حرف *propdata = تہی;
    کھڑکی_2 wm_کھڑکی = 0;
#اگر_تعریف_شدہ DEBUG_کھڑکی_MANAGER
    حرف *wm_name;
#اگر_ختم

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_کھڑکی_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    حالت_2 = X11_XGet_کھڑکی_Property(display, Default_جڑ_کھڑکی(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کھڑکی, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
    اگر (حالت_2 == Success) {
        اگر (اشیاء_read) {
            wm_کھڑکی = ((کھڑکی_2 *)propdata)[0];
        }
        اگر (propdata) {
            X11_XFree(propdata);
            propdata = تہی;
        }
    }

    اگر (wm_کھڑکی) {
        حالت_2 = X11_XGet_کھڑکی_Property(display, wm_کھڑکی, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_کھڑکی, &real_type, &real_format, &اشیاء_read, &اشیاء_بایاں, &propdata);
        اگر (حالت_2 != Success || !اشیاء_read || wm_کھڑکی != ((کھڑکی_2 *)propdata)[0]) {
            wm_کھڑکی = None;
        }
        اگر (حالت_2 == Success && propdata) {
            X11_XFree(propdata);
            propdata = تہی;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    اگر (!wm_کھڑکی) {
#اگر_تعریف_شدہ DEBUG_کھڑکی_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#اگر_ختم
        واپس;
    }
    ڈیٹا->net_wm = true;

#اگر_تعریف_شدہ DEBUG_کھڑکی_MANAGER
    wm_name = X11_Get_کھڑکی_Title(_this, wm_کھڑکی);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#اگر_ختم
}

ساکن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    // Get the process PID to be associated to the window
    ڈیٹا->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    ڈیٹا->کھڑکی_گروہ = (XID)(((size_t)ڈیٹا->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#تعریف_کرو GET_ATOM(X) ڈیٹا->atoms.X = X11_XInternAtom(ڈیٹا->display, #X, False)
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
    GET_ATOM(NET_WM_SYNC_REQUEST_شمار);
    GET_ATOM(NET_WM_کھڑکی_OPACITY);
    GET_ATOM(NET_WM_USER_وقت);
    GET_ATOM(NET_فعال_کھڑکی);
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
    GET_ATOM(Xdnd_ختم_شدہ);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_کھڑکی_Manager(_this);

    اگر (!X11_InitModes(_this)) {
        واپس false;
    }

    اگر (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, تہی);
        SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, تہی);
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#اگر_ختم

    X11_InitXsettings(_this);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#اگر_ختم

#اگر_غیر_تعریف_شدہ X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced اندر_2 2000! This is likely مقصد become a hard error اندر_2 a future libSDL3.
#اگر_ختم

    اگر (!X11_InitKeyboard(_this)) {
        واپس false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(ڈیٹا->display, ڈیٹا->atoms.CLIPBOARD, ڈیٹا->atoms.TARGETS,
            ڈیٹا->atoms.SDL_FORMATS, Get_کھڑکی(_this), Current_وقت);

    واپس true;
}

خالی X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->clipboard_کھڑکی) {
        X11_XDestroy_کھڑکی(ڈیٹا->display, ڈیٹا->clipboard_کھڑکی);
    }

    اگر (ڈیٹا->xsettings_کھڑکی) {
        X11_XDestroy_کھڑکی(ڈیٹا->display, ڈیٹا->xsettings_کھڑکی);
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

bool X11_Use_براہ_راست_Color_Visuals(خالی)
{
    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        واپس false;
    }
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
