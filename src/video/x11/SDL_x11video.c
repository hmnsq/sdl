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

#ifdef SDL_VIDEO_DRIVER_X11

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

#ifdef SDL_VIDEO_OPENGL_EGL
#ضمن "SDL_x11opengles.h"
#endif

// Initialization/Query functions
ساكن bool X11_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ساكن فراغ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;
    إذا (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    إذا (data->display) {
        X11_XCloseDisplay(data->display);
    }
    إذا (data->request_display) {
        X11_XCloseDisplay(data->request_display);
    }
    SDL_free(data->windowlist);
    SDL_free(device->internal);
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
#ifdef SDL_PLATFORM_LINUX
    إذا (SDL_GetPathInfo("/proc/sys/fs/binfmt_misc/WSLInterop", عدم) || SDL_GetPathInfo("/run/WSL", عدم)) { // if either of these exist, we're on WSL.
         أرجع true;
    }
#endif
    أرجع false;
}

ساكن SDL_VideoDevice *X11_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    ثابت حرف *display = عدم; // Use the DISPLAY environment variable
    Display *x11_display = عدم;

    إذا (!SDL_X11_LoadSymbols()) {
        أرجع عدم;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInitThreads();

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
    data = (بنية SDL_VideoData *)SDL_calloc(1, حجم(SDL_VideoData));
    إذا (!data) {
        SDL_free(device);
        أرجع عدم;
    }
    device->internal = data;

    data->global_mouse_changed = true;

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    data->active_cursor_confined_window = عدم;
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

    data->display = x11_display;
    data->request_display = X11_XOpenDisplay(display);
    إذا (!data->request_display) {
        X11_XCloseDisplay(data->display);
        SDL_free(device->internal);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        أرجع عدم;
    }

#ifdef X11_DEBUG
    X11_XSynchronize(data->display, True);
#endif

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    data->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->GetWindowICCProfile = X11_GetWindowICCProfile;
    device->SetDisplayMode = X11_SetDisplayMode;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_CreateWindow;
    device->SetWindowTitle = X11_SetWindowTitle;
    device->SetWindowIcon = X11_SetWindowIcon;
    device->SetWindowPosition = X11_SetWindowPosition;
    device->SetWindowSize = X11_SetWindowSize;
    device->SetWindowMinimumSize = X11_SetWindowMinimumSize;
    device->SetWindowMaximumSize = X11_SetWindowMaximumSize;
    device->SetWindowAspectRatio = X11_SetWindowAspectRatio;
    device->GetWindowBordersSize = X11_GetWindowBordersSize;
    device->SetWindowOpacity = X11_SetWindowOpacity;
    device->SetWindowParent = X11_SetWindowParent;
    device->SetWindowModal = X11_SetWindowModal;
    device->ShowWindow = X11_ShowWindow;
    device->HideWindow = X11_HideWindow;
    device->RaiseWindow = X11_RaiseWindow;
    device->MaximizeWindow = X11_MaximizeWindow;
    device->MinimizeWindow = X11_MinimizeWindow;
    device->RestoreWindow = X11_RestoreWindow;
    device->SetWindowBordered = X11_SetWindowBordered;
    device->SetWindowResizable = X11_SetWindowResizable;
    device->Set_Window_Always_On_اتس = X11_Set_Window_Always_On_اتس;
    device->SetWindowFullscreen = X11_SetWindowFullscreen;
    device->SetWindowMouseGrab = X11_SetWindowMouseGrab;
    device->SetWindowKeyboardGrab = X11_SetWindowKeyboardGrab;
    device->DestroyWindow = X11_DestroyWindow;
    device->CreateWindowFramebuffer = X11_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = X11_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = X11_DestroyWindowFramebuffer;
    device->SetWindowHitTest = X11_SetWindowHitTest;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->UpdateWindowShape = X11_UpdateWindowShape;
    device->FlashWindow = X11_FlashWindow;
#ifdef SDL_USE_LIBDBUS
    device->ApplyWindowProgress = DBUS_ApplyWindowProgress;
#endif // SDL_USE_LIBDBUS
    device->ShowWindowSystemMenu = X11_ShowWindowSystemMenu;
    device->SetWindowFocusable = X11_SetWindowFocusable;
    device->SyncWindow = X11_SyncWindow;

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    device->SetWindowMouseRect = X11_SetWindowMouseRect;
#endif // SDL_VIDEO_DRIVER_X11_XFIXES

#ifdef SDL_VIDEO_OPENGL_GLX
    device->GL_LoadLibrary = X11_GL_LoadLibrary;
    device->GL_GetProcAddress = X11_GL_GetProcAddress;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_SetSwapInterval = X11_GL_SetSwapInterval;
    device->GL_GetSwapInterval = X11_GL_GetSwapInterval;
    device->GL_SwapWindow = X11_GL_SwapWindow;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = عدم;
#endif
#ifdef SDL_VIDEO_OPENGL_EGL
#ifdef SDL_VIDEO_OPENGL_GLX
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#endif
        device->GL_LoadLibrary = X11_GLES_LoadLibrary;
        device->GL_GetProcAddress = X11_GLES_GetProcAddress;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_SetSwapInterval = X11_GLES_SetSwapInterval;
        device->GL_GetSwapInterval = X11_GLES_GetSwapInterval;
        device->GL_SwapWindow = X11_GLES_SwapWindow;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_SetDefaultProfileConfig = X11_GLES_SetDefaultProfileConfig;
#ifdef SDL_VIDEO_OPENGL_GLX
    }
#endif
#endif

    device->GetTextMimeTypes = X11_GetTextMimeTypes;
    device->SetClipboardData = X11_SetClipboardData;
    device->GetClipboardData = X11_GetClipboardData;
    device->HasClipboardData = X11_HasClipboardData;
    device->SetPrimarySelectionText = X11_SetPrimarySelectionText;
    device->GetPrimarySelectionText = X11_GetPrimarySelectionText;
    device->HasPrimarySelectionText = X11_HasPrimarySelectionText;
    device->Start_Text_ماسوقن = X11_Start_Text_ماسوقن;
    device->Stop_Text_ماسوقن = X11_Stop_Text_ماسوقن;
    device->Update_Text_ماسوقن_Area = X11_Update_Text_ماسوقن_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->حرر = X11_DeleteDevice;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = X11_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#endif

#ifdef SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#endif

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    data->is_xwayland = X11_IsXWayland(x11_display);
    إذا (data->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
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
    X11_ShowMessageBox,
    false
};

ساكن صحيح (*handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح X11_CheckWindowManagerErrorHandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_code == BadWindow) {
        أرجع 0;
    } وإلا {
        أرجع handler(d, e);
    }
}

ساكن فراغ X11_CheckWindowManager(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    صحيح status, real_format;
    Atom real_type;
    unsigned long بارڠن_read = 0, بارڠن_کيري = 0;
    unsigned حرف *propdata = عدم;
    Window wm_window = 0;
#ifdef DEBUG_WINDOW_MANAGER
    حرف *wm_name;
#endif

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_CheckWindowManagerErrorHandler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    status = X11_XGetWindowProperty(display, Default_اکر_Window(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_WINDOW, &real_type, &real_format, &بارڠن_read, &بارڠن_کيري, &propdata);
    إذا (status == Success) {
        إذا (بارڠن_read) {
            wm_window = ((Window *)propdata)[0];
        }
        إذا (propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    إذا (wm_window) {
        status = X11_XGetWindowProperty(display, wm_window, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_WINDOW, &real_type, &real_format, &بارڠن_read, &بارڠن_کيري, &propdata);
        إذا (status != Success || !بارڠن_read || wm_window != ((Window *)propdata)[0]) {
            wm_window = None;
        }
        إذا (status == Success && propdata) {
            X11_XFree(propdata);
            propdata = عدم;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    إذا (!wm_window) {
#ifdef DEBUG_WINDOW_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#endif
        أرجع;
    }
    data->net_wm = true;

#ifdef DEBUG_WINDOW_MANAGER
    wm_name = X11_GetWindowTitle(_this, wm_window);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#endif
}

ساكن bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    // Get the process PID to be associated to the window
    data->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    data->window_group = (XID)(((size_t)data->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#define GET_ATOM(X) data->atoms.X = X11_XInternAtom(data->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_WINDOW);
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
    GET_ATOM(_NET_WM_WINDOW_OPACITY);
    GET_ATOM(_NET_WM_USER_TIME);
    GET_ATOM(_NET_ACTIVE_WINDOW);
    GET_ATOM(_NET_FRAME_EXTENTS);
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
    GET_ATOM(XdndStatus);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(XdndFinished);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_CheckWindowManager(_this);

    إذا (!X11_InitModes(_this)) {
        أرجع false;
    }

    إذا (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
        SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, عدم);
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#endif

    X11_InitXsettings(_this);

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#endif

#ifndef X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced in 2000! This is likely to become a hard error in a future libSDL3.
#endif

    إذا (!X11_InitKeyboard(_this)) {
        أرجع false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(data->display, data->atoms.CLIPBOARD, data->atoms.TARGETS,
            data->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);

    أرجع true;
}

فراغ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    إذا (data->clipboard_window) {
        X11_XDestroyWindow(data->display, data->clipboard_window);
    }

    إذا (data->xsettings_window) {
        X11_XDestroyWindow(data->display, data->xsettings_window);
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

bool X11_UseDirectColorVisuals(فراغ)
{
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        أرجع false;
    }
    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_X11
