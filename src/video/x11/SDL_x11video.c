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

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश <unistd.h> // For getpid() and readlink()

#समावेश "../../core/linux/SDL_system_theme.h"
#समावेश "../../core/linux/SDL_progressbar.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../SDL_sysvideo.h"

#समावेश "SDL_x11framebuffer.h"
#समावेश "SDL_x11pen.h"
#समावेश "SDL_x11touch.h"
#समावेश "SDL_x11video.h"
#समावेश "SDL_x11xfixes.h"
#समावेश "SDL_x11xinput2.h"
#समावेश "SDL_x11messagebox.h"
#समावेश "SDL_x11shape.h"
#समावेश "SDL_x11xsync.h"
#समावेश "SDL_x11xtest.h"

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#समावेश "SDL_x11opengles.h"
#पूर्ण_अगर

// Initialization/Query functions
अटल bool X11_VideoInit(SDL_VideoDevice *_this);
अटल व्योम X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

अटल व्योम X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;
    अगर (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    अगर (तथ्य->display) {
        X11_XCloseDisplay(तथ्य->display);
    }
    अगर (तथ्य->request_display) {
        X11_XCloseDisplay(तथ्य->request_display);
    }
    SDL_free(तथ्य->windowlist);
    SDL_free(device->internal);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

अटल bool X11_IsXWayland(Display *d)
{
    पूर्णांक opcode, event, error;
    वापस X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

अटल bool X11_IsWSL(व्योम)
{
#अगर_घोषित SDL_PLATFORM_LINUX
    अगर (SDL_GetPathInfo("/proc/sys/fs/binfmt_misc/WSLInterop", शून्य) || SDL_GetPathInfo("/run/WSL", शून्य)) { // if either of these exist, we're on WSL.
         वापस true;
    }
#पूर्ण_अगर
    वापस false;
}

अटल SDL_VideoDevice *X11_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;
    स्थिर अक्षर *display = शून्य; // Use the DISPLAY environment variable
    Display *x11_display = शून्य;

    अगर (!SDL_X11_LoadSymbols()) {
        वापस शून्य;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInitThreads();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    अगर (!x11_display) {
        SDL_X11_UnloadSymbols();

        स्थिर अक्षर *session = SDL_getenv("XDG_SESSION_TYPE");
        अगर (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } अन्यथा {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        वापस शून्य;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }
    तथ्य = (काष्ठा SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!तथ्य) {
        SDL_free(device);
        वापस शून्य;
    }
    device->internal = तथ्य;

    तथ्य->global_mouse_changed = true;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    तथ्य->active_cursor_confined_window = शून्य;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XFIXES

    तथ्य->display = x11_display;
    तथ्य->request_display = X11_XOpenDisplay(display);
    अगर (!तथ्य->request_display) {
        X11_XCloseDisplay(तथ्य->display);
        SDL_free(device->internal);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        वापस शून्य;
    }

#अगर_घोषित X11_DEBUG
    X11_XSynchronize(तथ्य->display, True);
#पूर्ण_अगर

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    तथ्य->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

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
    device->Set_Window_आकार = X11_Set_Window_आकार;
    device->Set_Window_Minimum_आकार = X11_Set_Window_Minimum_आकार;
    device->Set_Window_Maximum_आकार = X11_Set_Window_Maximum_आकार;
    device->SetWindowAspectRatio = X11_SetWindowAspectRatio;
    device->Get_Window_Borders_आकार = X11_Get_Window_Borders_आकार;
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
    device->Set_Window_Always_On_शीर्ष = X11_Set_Window_Always_On_शीर्ष;
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
#अगर_घोषित SDL_USE_LIBDBUS
    device->ApplyWindowProgress = DBUS_ApplyWindowProgress;
#पूर्ण_अगर // SDL_USE_LIBDBUS
    device->ShowWindowSystemMenu = X11_ShowWindowSystemMenu;
    device->SetWindowFocusable = X11_SetWindowFocusable;
    device->SyncWindow = X11_SyncWindow;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    device->SetWindowMouseRect = X11_SetWindowMouseRect;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XFIXES

#अगर_घोषित SDL_VIDEO_OPENGL_GLX
    device->GL_LoadLibrary = X11_GL_LoadLibrary;
    device->GL_GetProcAddress = X11_GL_GetProcAddress;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_SetSwapInterval = X11_GL_SetSwapInterval;
    device->GL_GetSwapInterval = X11_GL_GetSwapInterval;
    device->GL_SwapWindow = X11_GL_SwapWindow;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = शून्य;
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#अगर_घोषित SDL_VIDEO_OPENGL_GLX
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#पूर्ण_अगर
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
#अगर_घोषित SDL_VIDEO_OPENGL_GLX
    }
#पूर्ण_अगर
#पूर्ण_अगर

    device->GetTextMimeTypes = X11_GetTextMimeTypes;
    device->Set_Clipboard_तथ्य = X11_Set_Clipboard_तथ्य;
    device->Get_Clipboard_तथ्य = X11_Get_Clipboard_तथ्य;
    device->Has_Clipboard_तथ्य = X11_Has_Clipboard_तथ्य;
    device->SetPrimarySelectionText = X11_SetPrimarySelectionText;
    device->GetPrimarySelectionText = X11_GetPrimarySelectionText;
    device->HasPrimarySelectionText = X11_HasPrimarySelectionText;
    device->Start_Text_निवेश = X11_Start_Text_निवेश;
    device->Stop_Text_निवेश = X11_Stop_Text_निवेश;
    device->Update_Text_निवेश_Area = X11_Update_Text_निवेश_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->मुक्त = X11_DeleteDevice;

#अगर_घोषित SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = X11_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#पूर्ण_अगर

#अगर_घोषित SDL_USE_LIBDBUS
    अगर (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#पूर्ण_अगर

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    तथ्य->is_xwayland = X11_IsXWayland(x11_display);
    अगर (तथ्य->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    अगर (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    वापस device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_ShowMessageBox,
    false
};

अटल पूर्णांक (*handler)(Display *, XErrorEvent *) = शून्य;
अटल पूर्णांक X11_CheckWindowManagerErrorHandler(Display *d, XErrorEvent *e)
{
    अगर (e->error_code == BadWindow) {
        वापस 0;
    } अन्यथा {
        वापस handler(d, e);
    }
}

अटल व्योम X11_CheckWindowManager(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Display *display = तथ्य->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    पूर्णांक status, real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुएँ_read = 0, वस्तुएँ_बायाँ = 0;
    अचिन्हित अक्षर *propdata = शून्य;
    Window wm_window = 0;
#अगर_घोषित DEBUG_WINDOW_MANAGER
    अक्षर *wm_name;
#पूर्ण_अगर

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_CheckWindowManagerErrorHandler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    status = X11_XGetWindowProperty(display, Default_मूल_Window(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_WINDOW, &real_type, &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
    अगर (status == Success) {
        अगर (वस्तुएँ_read) {
            wm_window = ((Window *)propdata)[0];
        }
        अगर (propdata) {
            X11_XFree(propdata);
            propdata = शून्य;
        }
    }

    अगर (wm_window) {
        status = X11_XGetWindowProperty(display, wm_window, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_WINDOW, &real_type, &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
        अगर (status != Success || !वस्तुएँ_read || wm_window != ((Window *)propdata)[0]) {
            wm_window = None;
        }
        अगर (status == Success && propdata) {
            X11_XFree(propdata);
            propdata = शून्य;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    अगर (!wm_window) {
#अगर_घोषित DEBUG_WINDOW_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#पूर्ण_अगर
        वापस;
    }
    तथ्य->net_wm = true;

#अगर_घोषित DEBUG_WINDOW_MANAGER
    wm_name = X11_GetWindowTitle(_this, wm_window);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#पूर्ण_अगर
}

अटल bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    // Get the process PID to be associated to the window
    तथ्य->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    तथ्य->window_group = (XID)(((माप_प्रकार)तथ्य->pid) ^ ((माप_प्रकार)_this));

    // Look up some useful Atoms
#घोषणा GET_ATOM(X) तथ्य->atoms.X = X11_XInternAtom(तथ्य->display, #X, False)
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
    GET_ATOM(NET_WM_SYNC_REQUEST_गणक);
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

    अगर (!X11_InitModes(_this)) {
        वापस false;
    }

    अगर (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, शून्य);
        SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, शून्य);
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#पूर्ण_अगर

    X11_InitXsettings(_this);

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#पूर्ण_अगर

#अगर_अघोषित X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced in 2000! This is likely to become a hard error in a future libSDL3.
#पूर्ण_अगर

    अगर (!X11_InitKeyboard(_this)) {
        वापस false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(तथ्य->display, तथ्य->atoms.CLIPBOARD, तथ्य->atoms.TARGETS,
            तथ्य->atoms.SDL_FORMATS, GetWindow(_this), CurrentTime);

    वापस true;
}

व्योम X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->clipboard_window) {
        X11_XDestroyWindow(तथ्य->display, तथ्य->clipboard_window);
    }

    अगर (तथ्य->xsettings_window) {
        X11_XDestroyWindow(तथ्य->display, तथ्य->xsettings_window);
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

bool X11_UseDirectColorVisuals(व्योम)
{
    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        वापस false;
    }
    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
