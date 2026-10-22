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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव <unistd.h> // For getpid() and readlink()

#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#अन्तर्भाव "../../core/linux/SDL_progressbar.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_x11framebuffer.h"
#अन्तर्भाव "SDL_x11pen.h"
#अन्तर्भाव "SDL_x11touch.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xfixes.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "SDL_x11messagebox.h"
#अन्तर्भाव "SDL_x11shape.h"
#अन्तर्भाव "SDL_x11xsync.h"
#अन्तर्भाव "SDL_x11xtest.h"

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "SDL_x11opengles.h"
#यदि_अन्तः

// Initialization/Query functions
स्थिर bool X11_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

स्थिर शून्य X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;
    यदि (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    यदि (दत्त->display) {
        X11_XCloseDisplay(दत्त->display);
    }
    यदि (दत्त->request_display) {
        X11_XCloseDisplay(दत्त->request_display);
    }
    SDL_free(दत्त->windowlist);
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

स्थिर bool X11_IsXWayland(Display *d)
{
    पूर्णाङ्क opcode, event, error;
    प्रत्यागम X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

स्थिर bool X11_IsWSL(शून्य)
{
#यदि_परिभाषितम् SDL_PLATFORM_LINUX
    यदि (SDL_Get_मार्गः_Info("/proc/sys/fs/binfmt_misc/WSLInterop", रिक्त) || SDL_Get_मार्गः_Info("/run/WSL", रिक्त)) { // if either of these exist, we're on WSL.
         प्रत्यागम true;
    }
#यदि_अन्तः
    प्रत्यागम false;
}

स्थिर SDL_VideoDevice *X11_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;
    ध्रुव वर्ण *display = रिक्त; // Use the DISPLAY environment variable
    Display *x11_display = रिक्त;

    यदि (!SDL_X11_आरोपय_Symbols()) {
        प्रत्यागम रिक्त;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_तन्तवः();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    यदि (!x11_display) {
        SDL_X11_UnloadSymbols();

        ध्रुव वर्ण *session = SDL_getenv("XDG_SESSION_TYPE");
        यदि (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } अन्यथा {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        प्रत्यागम रिक्त;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }
    दत्त = (संरचना SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!दत्त) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }
    device->आन्तरिकम् = दत्त;

    दत्त->global_mouse_परिवर्तितम् = true;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    दत्त->सक्रिय_cursor_confined_गवाक्षः = रिक्त;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES

    दत्त->display = x11_display;
    दत्त->request_display = X11_XOpenDisplay(display);
    यदि (!दत्त->request_display) {
        X11_XCloseDisplay(दत्त->display);
        SDL_free(device->आन्तरिकम्);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

#यदि_परिभाषितम् X11_DEBUG
    X11_XSynchronize(दत्त->display, True);
#यदि_अन्तः

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    दत्त->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_गवाक्षः_ICCProfile = X11_Get_गवाक्षः_ICCProfile;
    device->समुच्चयः_Display_बहुलकम् = X11_समुच्चयः_Display_बहुलकम्;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = X11_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Icon = X11_समुच्चयः_गवाक्षः_Icon;
    device->समुच्चयः_गवाक्षः_Position = X11_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = X11_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Minimum_आकार = X11_समुच्चयः_गवाक्षः_Minimum_आकार;
    device->समुच्चयः_गवाक्षः_अधिकतमम्_आकार = X11_समुच्चयः_गवाक्षः_अधिकतमम्_आकार;
    device->समुच्चयः_गवाक्षः_Aspect_अनुपातः = X11_समुच्चयः_गवाक्षः_Aspect_अनुपातः;
    device->Get_गवाक्षः_Borders_आकार = X11_Get_गवाक्षः_Borders_आकार;
    device->समुच्चयः_गवाक्षः_Opacity = X11_समुच्चयः_गवाक्षः_Opacity;
    device->समुच्चयः_गवाक्षः_Parent = X11_समुच्चयः_गवाक्षः_Parent;
    device->समुच्चयः_गवाक्षः_Modal = X11_समुच्चयः_गवाक्षः_Modal;
    device->Show_गवाक्षः = X11_Show_गवाक्षः;
    device->Hide_गवाक्षः = X11_Hide_गवाक्षः;
    device->Raise_गवाक्षः = X11_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = X11_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = X11_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = X11_Restore_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Bordered = X11_समुच्चयः_गवाक्षः_Bordered;
    device->समुच्चयः_गवाक्षः_Resizable = X11_समुच्चयः_गवाक्षः_Resizable;
    device->समुच्चयः_गवाक्षः_Always_On_शिखरम् = X11_समुच्चयः_गवाक्षः_Always_On_शिखरम्;
    device->समुच्चयः_गवाक्षः_Fullscreen = X11_समुच्चयः_गवाक्षः_Fullscreen;
    device->समुच्चयः_गवाक्षः_Mouse_Grab = X11_समुच्चयः_गवाक्षः_Mouse_Grab;
    device->समुच्चयः_गवाक्षः_Keyboard_Grab = X11_समुच्चयः_गवाक्षः_Keyboard_Grab;
    device->Destroy_गवाक्षः = X11_Destroy_गवाक्षः;
    device->Create_गवाक्षः_Framebuffer = X11_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = X11_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = X11_Destroy_गवाक्षः_Framebuffer;
    device->समुच्चयः_गवाक्षः_लब्धम्_Test = X11_समुच्चयः_गवाक्षः_लब्धम्_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_गवाक्षः_Shape = X11_Update_गवाक्षः_Shape;
    device->Flash_गवाक्षः = X11_Flash_गवाक्षः;
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    device->Apply_गवाक्षः_प्रगतिः = DBUS_Apply_गवाक्षः_प्रगतिः;
#यदि_अन्तः // SDL_USE_LIBDBUS
    device->Show_गवाक्षः_System_Menu = X11_Show_गवाक्षः_System_Menu;
    device->समुच्चयः_गवाक्षः_Focusable = X11_समुच्चयः_गवाक्षः_Focusable;
    device->Sync_गवाक्षः = X11_Sync_गवाक्षः;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    device->समुच्चयः_गवाक्षः_Mouse_Rect = X11_समुच्चयः_गवाक्षः_Mouse_Rect;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
    device->GL_आरोपय_Library = X11_GL_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = X11_GL_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = X11_GL_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = X11_GL_GetSwapInterval;
    device->GL_Swap_गवाक्षः = X11_GL_Swap_गवाक्षः;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = रिक्त;
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#यदि_अन्तः
        device->GL_आरोपय_Library = X11_GLES_आरोपय_Library;
        device->GL_Get_Proc_स्थानाङ्कः = X11_GLES_Get_Proc_स्थानाङ्कः;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_समुच्चयः_Swap_Interval = X11_GLES_समुच्चयः_Swap_Interval;
        device->GL_GetSwapInterval = X11_GLES_GetSwapInterval;
        device->GL_Swap_गवाक्षः = X11_GLES_Swap_गवाक्षः;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_समुच्चयः_Default_Profile_Config = X11_GLES_समुच्चयः_Default_Profile_Config;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_GLX
    }
#यदि_अन्तः
#यदि_अन्तः

    device->GetTextMimeTypes = X11_GetTextMimeTypes;
    device->समुच्चयः_Clipboard_दत्त = X11_समुच्चयः_Clipboard_दत्त;
    device->Get_Clipboard_दत्त = X11_Get_Clipboard_दत्त;
    device->Has_Clipboard_दत्त = X11_Has_Clipboard_दत्त;
    device->समुच्चयः_Primary_Selection_Text = X11_समुच्चयः_Primary_Selection_Text;
    device->GetPrimarySelectionText = X11_GetPrimarySelectionText;
    device->HasPrimarySelectionText = X11_HasPrimarySelectionText;
    device->Start_Text_निवेशः = X11_Start_Text_निवेशः;
    device->Stop_Text_निवेशः = X11_Stop_Text_निवेशः;
    device->Update_Text_निवेशः_Area = X11_Update_Text_निवेशः_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->मुक्त = X11_DeleteDevice;

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = X11_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    यदि (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#यदि_अन्तः

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_गवाक्षः_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    दत्त->is_xwayland = X11_IsXWayland(x11_display);
    यदि (दत्त->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_बहुलकम्_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    यदि (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    प्रत्यागम device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_सन्देशः_Box,
    false
};

स्थिर पूर्णाङ्क (*handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णाङ्क X11_Check_गवाक्षः_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    यदि (e->error_संहिता == Bad_गवाक्षः) {
        प्रत्यागम 0;
    } अन्यथा {
        प्रत्यागम handler(d, e);
    }
}

स्थिर शून्य X11_Check_गवाक्षः_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *display = दत्त->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    पूर्णाङ्क स्थितिः, real_format;
    Atom real_type;
    अचिह्नित दीर्घ वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    अचिह्नित वर्ण *propdata = रिक्त;
    गवाक्षः_2 wm_गवाक्षः = 0;
#यदि_परिभाषितम् DEBUG_गवाक्षः_MANAGER
    वर्ण *wm_name;
#यदि_अन्तः

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_गवाक्षः_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    स्थितिः = X11_XGet_गवाक्षः_Property(display, Default_मूलम्_गवाक्षः(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_गवाक्षः, &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
    यदि (स्थितिः == Success) {
        यदि (वस्तूनि_read) {
            wm_गवाक्षः = ((गवाक्षः_2 *)propdata)[0];
        }
        यदि (propdata) {
            X11_XFree(propdata);
            propdata = रिक्त;
        }
    }

    यदि (wm_गवाक्षः) {
        स्थितिः = X11_XGet_गवाक्षः_Property(display, wm_गवाक्षः, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_गवाक्षः, &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
        यदि (स्थितिः != Success || !वस्तूनि_read || wm_गवाक्षः != ((गवाक्षः_2 *)propdata)[0]) {
            wm_गवाक्षः = None;
        }
        यदि (स्थितिः == Success && propdata) {
            X11_XFree(propdata);
            propdata = रिक्त;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    यदि (!wm_गवाक्षः) {
#यदि_परिभाषितम् DEBUG_गवाक्षः_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#यदि_अन्तः
        प्रत्यागम;
    }
    दत्त->net_wm = true;

#यदि_परिभाषितम् DEBUG_गवाक्षः_MANAGER
    wm_name = X11_Get_गवाक्षः_Title(_this, wm_गवाक्षः);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#यदि_अन्तः
}

स्थिर bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    // Get the process PID to be associated to the window
    दत्त->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    दत्त->गवाक्षः_गणः = (XID)(((size_t)दत्त->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#परिभाषय GET_ATOM(X) दत्त->atoms.X = X11_XInternAtom(दत्त->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_गवाक्षः);
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
    GET_ATOM(NET_WM_गवाक्षः_OPACITY);
    GET_ATOM(_NET_WM_USER_TIME);
    GET_ATOM(NET_सक्रिय_गवाक्षः);
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
    GET_ATOM(Xdnd_स्थितिः);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_परिसमाप्तम्);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_गवाक्षः_Manager(_this);

    यदि (!X11_InitModes(_this)) {
        प्रत्यागम false;
    }

    यदि (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_सङ्कलय_Keyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
        SDL_सङ्कलय_Mouse(SDL_DEFAULT_MOUSE_ID, रिक्त);
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#यदि_अन्तः

    X11_InitXsettings(_this);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#यदि_अन्तः

#यदि_अपरिभाषितम् X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced अन्तर्_2 2000! This is likely गन्तव्यम् become a hard error अन्तर्_2 a future libSDL3.
#यदि_अन्तः

    यदि (!X11_InitKeyboard(_this)) {
        प्रत्यागम false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(दत्त->display, दत्त->atoms.CLIPBOARD, दत्त->atoms.TARGETS,
            दत्त->atoms.SDL_FORMATS, Get_गवाक्षः(_this), CurrentTime);

    प्रत्यागम true;
}

शून्य X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->clipboard_गवाक्षः) {
        X11_XDestroy_गवाक्षः(दत्त->display, दत्त->clipboard_गवाक्षः);
    }

    यदि (दत्त->xsettings_गवाक्षः) {
        X11_XDestroy_गवाक्षः(दत्त->display, दत्त->xsettings_गवाक्षः);
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

bool X11_Use_प्रत्यक्षम्_Color_Visuals(शून्य)
{
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
