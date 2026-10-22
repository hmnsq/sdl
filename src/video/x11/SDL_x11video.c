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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ <unistd.h> // For getpid() and readlink()

#అన్తర్భావ "../../core/linux/SDL_system_theme.h"
#అన్తర్భావ "../../core/linux/SDL_progressbar.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ "SDL_x11framebuffer.h"
#అన్తర్భావ "SDL_x11pen.h"
#అన్తర్భావ "SDL_x11touch.h"
#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xfixes.h"
#అన్తర్భావ "SDL_x11xinput2.h"
#అన్తర్భావ "SDL_x11messagebox.h"
#అన్తర్భావ "SDL_x11shape.h"
#అన్తర్భావ "SDL_x11xsync.h"
#అన్తర్భావ "SDL_x11xtest.h"

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#అన్తర్భావ "SDL_x11opengles.h"
#అయితే_ముగింపు

// Initialization/Query functions
స్థిర bool X11_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

స్థిర శూన్య X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;
    ఒకవేళ (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    ఒకవేళ (దత్తాంశం->display) {
        X11_XCloseDisplay(దత్తాంశం->display);
    }
    ఒకవేళ (దత్తాంశం->request_display) {
        X11_XCloseDisplay(దత్తాంశం->request_display);
    }
    SDL_free(దత్తాంశం->windowlist);
    SDL_free(device->అంతర్గత);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

స్థిర bool X11_IsXWayland(Display *d)
{
    పూర్ణాంకం opcode, event, error;
    తిరిగి X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

స్థిర bool X11_IsWSL(శూన్య)
{
#నిర్వచితమైతే SDL_PLATFORM_LINUX
    ఒకవేళ (SDL_Get_మార్గం_Info("/proc/sys/fs/binfmt_misc/WSLInterop", ఖాళీ) || SDL_Get_మార్గం_Info("/run/WSL", ఖాళీ)) { // if either of these exist, we're on WSL.
         తిరిగి true;
    }
#అయితే_ముగింపు
    తిరిగి false;
}

స్థిర SDL_VideoDevice *X11_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;
    స్థిరరాశి అక్షరం *display = ఖాళీ; // Use the DISPLAY environment variable
    Display *x11_display = ఖాళీ;

    ఒకవేళ (!SDL_X11_ఎక్కించు_Symbols()) {
        తిరిగి ఖాళీ;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_దారాలు();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    ఒకవేళ (!x11_display) {
        SDL_X11_UnloadSymbols();

        స్థిరరాశి అక్షరం *session = SDL_getenv("XDG_SESSION_TYPE");
        ఒకవేళ (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } లేకపోతే {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        తిరిగి ఖాళీ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }
    దత్తాంశం = (నిర్మాణం SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }
    device->అంతర్గత = దత్తాంశం;

    దత్తాంశం->global_mouse_మారింది = true;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    దత్తాంశం->చురుకైన_cursor_confined_కిటికీ = ఖాళీ;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES

    దత్తాంశం->display = x11_display;
    దత్తాంశం->request_display = X11_XOpenDisplay(display);
    ఒకవేళ (!దత్తాంశం->request_display) {
        X11_XCloseDisplay(దత్తాంశం->display);
        SDL_free(device->అంతర్గత);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        తిరిగి ఖాళీ;
    }

#నిర్వచితమైతే X11_DEBUG
    X11_XSynchronize(దత్తాంశం->display, True);
#అయితే_ముగింపు

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    దత్తాంశం->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_కిటికీ_ICCProfile = X11_Get_కిటికీ_ICCProfile;
    device->సమితి_Display_బహుళకం = X11_సమితి_Display_బహుళకం;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = X11_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Icon = X11_సమితి_కిటికీ_Icon;
    device->సమితి_కిటికీ_Position = X11_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = X11_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Minimum_కొలత = X11_సమితి_కిటికీ_Minimum_కొలత;
    device->సమితి_కిటికీ_గరిష్ఠ_కొలత = X11_సమితి_కిటికీ_గరిష్ఠ_కొలత;
    device->సమితి_కిటికీ_Aspect_నిష్పత్తి = X11_సమితి_కిటికీ_Aspect_నిష్పత్తి;
    device->Get_కిటికీ_Borders_కొలత = X11_Get_కిటికీ_Borders_కొలత;
    device->సమితి_కిటికీ_Opacity = X11_సమితి_కిటికీ_Opacity;
    device->సమితి_కిటికీ_మాతృ = X11_సమితి_కిటికీ_మాతృ;
    device->సమితి_కిటికీ_Modal = X11_సమితి_కిటికీ_Modal;
    device->Show_కిటికీ = X11_Show_కిటికీ;
    device->Hide_కిటికీ = X11_Hide_కిటికీ;
    device->Raise_కిటికీ = X11_Raise_కిటికీ;
    device->Maximize_కిటికీ = X11_Maximize_కిటికీ;
    device->Minimize_కిటికీ = X11_Minimize_కిటికీ;
    device->Restore_కిటికీ = X11_Restore_కిటికీ;
    device->సమితి_కిటికీ_Bordered = X11_సమితి_కిటికీ_Bordered;
    device->సమితి_కిటికీ_Resizable = X11_సమితి_కిటికీ_Resizable;
    device->సమితి_కిటికీ_Always_On_శిఖరం = X11_సమితి_కిటికీ_Always_On_శిఖరం;
    device->సమితి_కిటికీ_Fullscreen = X11_సమితి_కిటికీ_Fullscreen;
    device->సమితి_కిటికీ_Mouse_Grab = X11_సమితి_కిటికీ_Mouse_Grab;
    device->సమితి_కిటికీ_Keyboard_Grab = X11_సమితి_కిటికీ_Keyboard_Grab;
    device->Destroy_కిటికీ = X11_Destroy_కిటికీ;
    device->Create_కిటికీ_Framebuffer = X11_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = X11_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = X11_Destroy_కిటికీ_Framebuffer;
    device->సమితి_కిటికీ_తగిలింది_Test = X11_సమితి_కిటికీ_తగిలింది_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_కిటికీ_Shape = X11_Update_కిటికీ_Shape;
    device->Flash_కిటికీ = X11_Flash_కిటికీ;
#నిర్వచితమైతే SDL_USE_LIBDBUS
    device->Apply_కిటికీ_పురోగతి = DBUS_Apply_కిటికీ_పురోగతి;
#అయితే_ముగింపు // SDL_USE_LIBDBUS
    device->Show_కిటికీ_System_Menu = X11_Show_కిటికీ_System_Menu;
    device->సమితి_కిటికీ_Focusable = X11_సమితి_కిటికీ_Focusable;
    device->Sync_కిటికీ = X11_Sync_కిటికీ;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    device->సమితి_కిటికీ_Mouse_Rect = X11_సమితి_కిటికీ_Mouse_Rect;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES

#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
    device->GL_ఎక్కించు_Library = X11_GL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = X11_GL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = X11_GL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = X11_GL_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = X11_GL_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = ఖాళీ;
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#అయితే_ముగింపు
        device->GL_ఎక్కించు_Library = X11_GLES_ఎక్కించు_Library;
        device->GL_Get_Proc_చిరునామా = X11_GLES_Get_Proc_చిరునామా;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_సమితి_మార్పిడి_Interval = X11_GLES_సమితి_మార్పిడి_Interval;
        device->GL_Get_మార్పిడి_Interval = X11_GLES_Get_మార్పిడి_Interval;
        device->GL_మార్పిడి_కిటికీ = X11_GLES_మార్పిడి_కిటికీ;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_సమితి_Default_Profile_Config = X11_GLES_సమితి_Default_Profile_Config;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_GLX
    }
#అయితే_ముగింపు
#అయితే_ముగింపు

    device->Get_పాఠ్యం_Mime_Types = X11_Get_పాఠ్యం_Mime_Types;
    device->సమితి_Clipboard_దత్తాంశం = X11_సమితి_Clipboard_దత్తాంశం;
    device->Get_Clipboard_దత్తాంశం = X11_Get_Clipboard_దత్తాంశం;
    device->Has_Clipboard_దత్తాంశం = X11_Has_Clipboard_దత్తాంశం;
    device->సమితి_Primary_Selection_పాఠ్యం = X11_సమితి_Primary_Selection_పాఠ్యం;
    device->Get_Primary_Selection_పాఠ్యం = X11_Get_Primary_Selection_పాఠ్యం;
    device->Has_Primary_Selection_పాఠ్యం = X11_Has_Primary_Selection_పాఠ్యం;
    device->ప్రారంభం_పాఠ్యం_ఆదానం = X11_ప్రారంభం_పాఠ్యం_ఆదానం;
    device->Stop_పాఠ్యం_ఆదానం = X11_Stop_పాఠ్యం_ఆదానం;
    device->Update_పాఠ్యం_ఆదానం_Area = X11_Update_పాఠ్యం_ఆదానం_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->విడుదల = X11_DeleteDevice;

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = X11_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_USE_LIBDBUS
    ఒకవేళ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#అయితే_ముగింపు

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_కిటికీ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    దత్తాంశం->is_xwayland = X11_IsXWayland(x11_display);
    ఒకవేళ (దత్తాంశం->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_బహుళకం_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    ఒకవేళ (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    తిరిగి device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_సందేశం_Box,
    false
};

స్థిర పూర్ణాంకం (*handler)(Display *, XErrorEvent *) = ఖాళీ;
స్థిర పూర్ణాంకం X11_Check_కిటికీ_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    ఒకవేళ (e->error_సంకేతం == Bad_కిటికీ) {
        తిరిగి 0;
    } లేకపోతే {
        తిరిగి handler(d, e);
    }
}

స్థిర శూన్య X11_Check_కిటికీ_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *display = దత్తాంశం->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    పూర్ణాంకం స్థితి_2, real_format;
    Atom real_type;
    గుర్తులేని దీర్ఘ వస్తువులు_read = 0, వస్తువులు_ఎడమ = 0;
    గుర్తులేని అక్షరం *propdata = ఖాళీ;
    కిటికీ_2 wm_కిటికీ = 0;
#నిర్వచితమైతే DEBUG_కిటికీ_MANAGER
    అక్షరం *wm_name;
#అయితే_ముగింపు

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_కిటికీ_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    స్థితి_2 = X11_XGet_కిటికీ_Property(display, Default_మూలం_కిటికీ(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_కిటికీ, &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
    ఒకవేళ (స్థితి_2 == Success) {
        ఒకవేళ (వస్తువులు_read) {
            wm_కిటికీ = ((కిటికీ_2 *)propdata)[0];
        }
        ఒకవేళ (propdata) {
            X11_XFree(propdata);
            propdata = ఖాళీ;
        }
    }

    ఒకవేళ (wm_కిటికీ) {
        స్థితి_2 = X11_XGet_కిటికీ_Property(display, wm_కిటికీ, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_కిటికీ, &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
        ఒకవేళ (స్థితి_2 != Success || !వస్తువులు_read || wm_కిటికీ != ((కిటికీ_2 *)propdata)[0]) {
            wm_కిటికీ = None;
        }
        ఒకవేళ (స్థితి_2 == Success && propdata) {
            X11_XFree(propdata);
            propdata = ఖాళీ;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    ఒకవేళ (!wm_కిటికీ) {
#నిర్వచితమైతే DEBUG_కిటికీ_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#అయితే_ముగింపు
        తిరిగి;
    }
    దత్తాంశం->net_wm = true;

#నిర్వచితమైతే DEBUG_కిటికీ_MANAGER
    wm_name = X11_Get_కిటికీ_Title(_this, wm_కిటికీ);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#అయితే_ముగింపు
}

స్థిర bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    // Get the process PID to be associated to the window
    దత్తాంశం->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    దత్తాంశం->కిటికీ_సమూహం = (XID)(((size_t)దత్తాంశం->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#నిర్వచించు GET_ATOM(X) దత్తాంశం->atoms.X = X11_XInternAtom(దత్తాంశం->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_కిటికీ);
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
    GET_ATOM(NET_WM_కిటికీ_OPACITY);
    GET_ATOM(NET_WM_USER_సమయం);
    GET_ATOM(NET_చురుకైన_కిటికీ);
    GET_ATOM(NET_చట్రం_EXTENTS);
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
    GET_ATOM(Xdnd_స్థితి);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_ముగిసిన);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_కిటికీ_Manager(_this);

    ఒకవేళ (!X11_InitModes(_this)) {
        తిరిగి false;
    }

    ఒకవేళ (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_కూడు_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ఖాళీ);
        SDL_కూడు_Mouse(SDL_DEFAULT_MOUSE_ID, ఖాళీ);
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#అయితే_ముగింపు

    X11_InitXsettings(_this);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced లోపల_2 2000! This is likely గమ్యం become a hard error లోపల_2 a future libSDL3.
#అయితే_ముగింపు

    ఒకవేళ (!X11_InitKeyboard(_this)) {
        తిరిగి false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(దత్తాంశం->display, దత్తాంశం->atoms.CLIPBOARD, దత్తాంశం->atoms.TARGETS,
            దత్తాంశం->atoms.SDL_FORMATS, Get_కిటికీ(_this), Current_సమయం);

    తిరిగి true;
}

శూన్య X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->clipboard_కిటికీ) {
        X11_XDestroy_కిటికీ(దత్తాంశం->display, దత్తాంశం->clipboard_కిటికీ);
    }

    ఒకవేళ (దత్తాంశం->xsettings_కిటికీ) {
        X11_XDestroy_కిటికీ(దత్తాంశం->display, దత్తాంశం->xsettings_కిటికీ);
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

bool X11_Use_ప్రత్యక్ష_Color_Visuals(శూన్య)
{
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        తిరిగి false;
    }
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
