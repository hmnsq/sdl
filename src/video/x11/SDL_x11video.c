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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

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

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#پایان_اگر

// Initialization/Query functions
ساكن bool X11_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساكن فراغ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_داده *داده = device->داخلی;
    إذا (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    إذا (داده->display) {
        X11_XCloseDisplay(داده->display);
    }
    إذا (داده->request_display) {
        X11_XCloseDisplay(داده->request_display);
    }
    SDL_free(داده->windowlist);
    SDL_free(device->داخلی);
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
#اگر_تعریف_شده SDL_PLATFORM_LINUX
    إذا (SDL_Get_مسیر_Info("/proc/sys/fs/binfmt_misc/WSLInterop", عدم) || SDL_Get_مسیر_Info("/run/WSL", عدم)) { // if either of these exist, we're on WSL.
         أرجع true;
    }
#پایان_اگر
    أرجع false;
}

ساكن SDL_VideoDevice *X11_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *داده;
    ثابت حرف *display = عدم; // Use the DISPLAY environment variable
    Display *x11_display = عدم;

    إذا (!SDL_X11_بارگیری_Symbols()) {
        أرجع عدم;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_نخها();

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
    داده = (بنية SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!داده) {
        SDL_free(device);
        أرجع عدم;
    }
    device->داخلی = داده;

    داده->global_mouse_تغییریافته = true;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
    داده->فعال_cursor_confined_پنجره = عدم;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES

    داده->display = x11_display;
    داده->request_display = X11_XOpenDisplay(display);
    إذا (!داده->request_display) {
        X11_XCloseDisplay(داده->display);
        SDL_free(device->داخلی);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        أرجع عدم;
    }

#اگر_تعریف_شده X11_DEBUG
    X11_XSynchronize(داده->display, True);
#پایان_اگر

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    داده->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_پنجره_ICCProfile = X11_Get_پنجره_ICCProfile;
    device->مجموعه_Display_نما = X11_مجموعه_Display_نما;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_پنجره;
    device->مجموعه_پنجره_Title = X11_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Icon = X11_مجموعه_پنجره_Icon;
    device->مجموعه_پنجره_Position = X11_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = X11_مجموعه_پنجره_اندازه;
    device->مجموعه_پنجره_Minimum_اندازه = X11_مجموعه_پنجره_Minimum_اندازه;
    device->مجموعه_پنجره_بیشینه_اندازه = X11_مجموعه_پنجره_بیشینه_اندازه;
    device->مجموعه_پنجره_Aspect_نسبت = X11_مجموعه_پنجره_Aspect_نسبت;
    device->Get_پنجره_Borders_اندازه = X11_Get_پنجره_Borders_اندازه;
    device->مجموعه_پنجره_Opacity = X11_مجموعه_پنجره_Opacity;
    device->مجموعه_پنجره_والد = X11_مجموعه_پنجره_والد;
    device->مجموعه_پنجره_Modal = X11_مجموعه_پنجره_Modal;
    device->Show_پنجره = X11_Show_پنجره;
    device->Hide_پنجره = X11_Hide_پنجره;
    device->Raise_پنجره = X11_Raise_پنجره;
    device->Maximize_پنجره = X11_Maximize_پنجره;
    device->Minimize_پنجره = X11_Minimize_پنجره;
    device->Restore_پنجره = X11_Restore_پنجره;
    device->مجموعه_پنجره_Bordered = X11_مجموعه_پنجره_Bordered;
    device->مجموعه_پنجره_Resizable = X11_مجموعه_پنجره_Resizable;
    device->مجموعه_پنجره_Always_On_بالاترین = X11_مجموعه_پنجره_Always_On_بالاترین;
    device->مجموعه_پنجره_Fullscreen = X11_مجموعه_پنجره_Fullscreen;
    device->مجموعه_پنجره_Mouse_Grab = X11_مجموعه_پنجره_Mouse_Grab;
    device->مجموعه_پنجره_Keyboard_Grab = X11_مجموعه_پنجره_Keyboard_Grab;
    device->Destroy_پنجره = X11_Destroy_پنجره;
    device->Create_پنجره_Framebuffer = X11_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = X11_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = X11_Destroy_پنجره_Framebuffer;
    device->مجموعه_پنجره_اصابت_Test = X11_مجموعه_پنجره_اصابت_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_پنجره_Shape = X11_Update_پنجره_Shape;
    device->Flash_پنجره = X11_Flash_پنجره;
#اگر_تعریف_شده SDL_USE_LIBDBUS
    device->Apply_پنجره_پیشرفت = DBUS_Apply_پنجره_پیشرفت;
#پایان_اگر // SDL_USE_LIBDBUS
    device->Show_پنجره_System_Menu = X11_Show_پنجره_System_Menu;
    device->مجموعه_پنجره_Focusable = X11_مجموعه_پنجره_Focusable;
    device->Sync_پنجره = X11_Sync_پنجره;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
    device->مجموعه_پنجره_Mouse_Rect = X11_مجموعه_پنجره_Mouse_Rect;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XFIXES

#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
    device->GL_بارگیری_Library = X11_GL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = X11_GL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = X11_GL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = X11_GL_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = X11_GL_جابجا_پنجره;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#پایان_اگر
        device->GL_بارگیری_Library = X11_GLES_بارگیری_Library;
        device->GL_Get_Proc_آدرس = X11_GLES_Get_Proc_آدرس;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_مجموعه_جابجا_Interval = X11_GLES_مجموعه_جابجا_Interval;
        device->GL_Get_جابجا_Interval = X11_GLES_Get_جابجا_Interval;
        device->GL_جابجا_پنجره = X11_GLES_جابجا_پنجره;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_مجموعه_Default_Profile_Config = X11_GLES_مجموعه_Default_Profile_Config;
#اگر_تعریف_شده SDL_VIDEO_OPENGL_GLX
    }
#پایان_اگر
#پایان_اگر

    device->Get_متن_Mime_Types = X11_Get_متن_Mime_Types;
    device->مجموعه_Clipboard_داده = X11_مجموعه_Clipboard_داده;
    device->Get_Clipboard_داده = X11_Get_Clipboard_داده;
    device->Has_Clipboard_داده = X11_Has_Clipboard_داده;
    device->مجموعه_Primary_Selection_متن = X11_مجموعه_Primary_Selection_متن;
    device->Get_Primary_Selection_متن = X11_Get_Primary_Selection_متن;
    device->Has_Primary_Selection_متن = X11_Has_Primary_Selection_متن;
    device->شروع_متن_درون_داد = X11_شروع_متن_درون_داد;
    device->Stop_متن_درون_داد = X11_Stop_متن_درون_داد;
    device->Update_متن_درون_داد_Area = X11_Update_متن_درون_داد_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->حرر = X11_DeleteDevice;

#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = X11_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#پایان_اگر

#اگر_تعریف_شده SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#پایان_اگر

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_پنجره_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    داده->is_xwayland = X11_IsXWayland(x11_display);
    إذا (داده->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_نما_SWITCHING_EMULATED |
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
    X11_Show_پیام_Box,
    false
};

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح X11_Check_پنجره_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کد == Bad_پنجره) {
        أرجع 0;
    } وإلا {
        أرجع handler(d, e);
    }
}

ساكن فراغ X11_Check_پنجره_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    Display *display = داده->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحيح وضعیت, real_format;
    Atom real_type;
    بیعلامت دراز اقلام_read = 0, اقلام_چپ = 0;
    بیعلامت حرف *propdata = عدم;
    پنجره_2 wm_پنجره = 0;
#اگر_تعریف_شده DEBUG_پنجره_MANAGER
    حرف *wm_name;
#پایان_اگر

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_پنجره_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    وضعیت = X11_XGet_پنجره_Property(display, Default_ریشه_پنجره(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_پنجره, &real_type, &real_format, &اقلام_read, &اقلام_چپ, &propdata);
    إذا (وضعیت == Success) {
        إذا (اقلام_read) {
            wm_پنجره = ((پنجره_2 *)propdata)[0];
        }
        إذا (propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    إذا (wm_پنجره) {
        وضعیت = X11_XGet_پنجره_Property(display, wm_پنجره, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_پنجره, &real_type, &real_format, &اقلام_read, &اقلام_چپ, &propdata);
        إذا (وضعیت != Success || !اقلام_read || wm_پنجره != ((پنجره_2 *)propdata)[0]) {
            wm_پنجره = None;
        }
        إذا (وضعیت == Success && propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    إذا (!wm_پنجره) {
#اگر_تعریف_شده DEBUG_پنجره_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#پایان_اگر
        أرجع;
    }
    داده->net_wm = true;

#اگر_تعریف_شده DEBUG_پنجره_MANAGER
    wm_name = X11_Get_پنجره_Title(_this, wm_پنجره);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#پایان_اگر
}

ساكن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    // Get the process PID to be associated to the window
    داده->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    داده->پنجره_گروه = (XID)(((size_t)داده->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#تعریف_کن GET_ATOM(X) داده->atoms.X = X11_XInternAtom(داده->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_پنجره);
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
    GET_ATOM(NET_WM_پنجره_OPACITY);
    GET_ATOM(NET_WM_USER_زمان);
    GET_ATOM(NET_فعال_پنجره);
    GET_ATOM(NET_قاب_EXTENTS);
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
    GET_ATOM(Xdnd_وضعیت);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_پایانیافته);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_پنجره_Manager(_this);

    إذا (!X11_InitModes(_this)) {
        أرجع false;
    }

    إذا (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_جمع_کن_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
        SDL_جمع_کن_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#پایان_اگر

    X11_InitXsettings(_this);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#پایان_اگر

#اگر_تعریف_نشده X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced درون_2 2000! This is likely مقصد become a hard error درون_2 a future libSDL3.
#پایان_اگر

    إذا (!X11_InitKeyboard(_this)) {
        أرجع false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(داده->display, داده->atoms.CLIPBOARD, داده->atoms.TARGETS,
            داده->atoms.SDL_FORMATS, Get_پنجره(_this), Current_زمان);

    أرجع true;
}

فراغ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    إذا (داده->clipboard_پنجره) {
        X11_XDestroy_پنجره(داده->display, داده->clipboard_پنجره);
    }

    إذا (داده->xsettings_پنجره) {
        X11_XDestroy_پنجره(داده->display, داده->xsettings_پنجره);
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

#پایان_اگر // SDL_VIDEO_DRIVER_X11
