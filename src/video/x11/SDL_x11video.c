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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h> // For getpid() and readlink()

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_system_theme.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_progressbar.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11framebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11pen.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11touch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xfixes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11messagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11shape.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xtest.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11opengles.h"
#ਜੇ_ਅੰਤ

// Initialization/Query functions
ਸਥਿਰ bool X11_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ਸਥਿਰ ਖਾਲੀ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    ਜੇ (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    ਜੇ (ਅੰਕੜੇ->display) {
        X11_XCloseDisplay(ਅੰਕੜੇ->display);
    }
    ਜੇ (ਅੰਕੜੇ->request_display) {
        X11_XCloseDisplay(ਅੰਕੜੇ->request_display);
    }
    SDL_free(ਅੰਕੜੇ->windowlist);
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

ਸਥਿਰ bool X11_IsXWayland(Display *d)
{
    ਪੂਰਨ opcode, event, error;
    ਵਾਪਸ X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

ਸਥਿਰ bool X11_IsWSL(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_LINUX
    ਜੇ (SDL_Get_ਰਸਤਾ_Info("/proc/sys/fs/binfmt_misc/WSLInterop", ਨਿਰਾ) || SDL_Get_ਰਸਤਾ_Info("/run/WSL", ਨਿਰਾ)) { // if either of these exist, we're on WSL.
         ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ false;
}

ਸਥਿਰ SDL_VideoDevice *X11_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਅਚਲ ਅੱਖਰ *display = ਨਿਰਾ; // Use the DISPLAY environment variable
    Display *x11_display = ਨਿਰਾ;

    ਜੇ (!SDL_X11_ਲੱਦੋ_Symbols()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_ਧਾਗੇ();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    ਜੇ (!x11_display) {
        SDL_X11_UnloadSymbols();

        ਅਚਲ ਅੱਖਰ *session = SDL_getenv("XDG_SESSION_TYPE");
        ਜੇ (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } ਨਹੀਂਤਾਂ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਅੰਕੜੇ = (ਬਣਤਰ SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }
    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    ਅੰਕੜੇ->global_mouse_ਬਦਲਿਆ = true;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    ਅੰਕੜੇ->ਸਰਗਰਮ_cursor_confined_ਖਿੜਕੀ = ਨਿਰਾ;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES

    ਅੰਕੜੇ->display = x11_display;
    ਅੰਕੜੇ->request_display = X11_XOpenDisplay(display);
    ਜੇ (!ਅੰਕੜੇ->request_display) {
        X11_XCloseDisplay(ਅੰਕੜੇ->display);
        SDL_free(device->ਅੰਦਰੂਨੀ);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        ਵਾਪਸ ਨਿਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11_DEBUG
    X11_XSynchronize(ਅੰਕੜੇ->display, True);
#ਜੇ_ਅੰਤ

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    ਅੰਕੜੇ->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_ਖਿੜਕੀ_ICCProfile = X11_Get_ਖਿੜਕੀ_ICCProfile;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = X11_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = X11_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Icon = X11_ਸੈੱਟ_ਖਿੜਕੀ_Icon;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = X11_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ = X11_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ = X11_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ = X11_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ;
    device->Get_ਖਿੜਕੀ_Borders_ਮਾਪ = X11_Get_ਖਿੜਕੀ_Borders_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Opacity = X11_ਸੈੱਟ_ਖਿੜਕੀ_Opacity;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ = X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Modal = X11_ਸੈੱਟ_ਖਿੜਕੀ_Modal;
    device->Show_ਖਿੜਕੀ = X11_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = X11_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = X11_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = X11_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = X11_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = X11_Restore_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Bordered = X11_ਸੈੱਟ_ਖਿੜਕੀ_Bordered;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = X11_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ = X11_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab = X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab = X11_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab;
    device->Destroy_ਖਿੜਕੀ = X11_Destroy_ਖਿੜਕੀ;
    device->Create_ਖਿੜਕੀ_Framebuffer = X11_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = X11_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = X11_Destroy_ਖਿੜਕੀ_Framebuffer;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test = X11_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_ਖਿੜਕੀ_Shape = X11_Update_ਖਿੜਕੀ_Shape;
    device->Flash_ਖਿੜਕੀ = X11_Flash_ਖਿੜਕੀ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    device->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ = DBUS_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ;
#ਜੇ_ਅੰਤ // SDL_USE_LIBDBUS
    device->Show_ਖਿੜਕੀ_System_Menu = X11_Show_ਖਿੜਕੀ_System_Menu;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Focusable = X11_ਸੈੱਟ_ਖਿੜਕੀ_Focusable;
    device->Sync_ਖਿੜਕੀ = X11_Sync_ਖਿੜਕੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect = X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
    device->GL_ਲੱਦੋ_Library = X11_GL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = X11_GL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = X11_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = ਨਿਰਾ;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ਜੇ_ਅੰਤ
        device->GL_ਲੱਦੋ_Library = X11_GLES_ਲੱਦੋ_Library;
        device->GL_Get_Proc_ਪਤਾ = X11_GLES_Get_Proc_ਪਤਾ;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
        device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = X11_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
        device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = X11_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_ਸੈੱਟ_Default_Profile_Config = X11_GLES_ਸੈੱਟ_Default_Profile_Config;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_GLX
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

    device->Get_ਪਾਠ_Mime_Types = X11_Get_ਪਾਠ_Mime_Types;
    device->ਸੈੱਟ_Clipboard_ਅੰਕੜੇ = X11_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ;
    device->Get_Clipboard_ਅੰਕੜੇ = X11_Get_Clipboard_ਅੰਕੜੇ;
    device->Has_Clipboard_ਅੰਕੜੇ = X11_Has_Clipboard_ਅੰਕੜੇ;
    device->ਸੈੱਟ_Primary_Selection_ਪਾਠ = X11_ਸੈੱਟ_Primary_Selection_ਪਾਠ;
    device->Get_Primary_Selection_ਪਾਠ = X11_Get_Primary_Selection_ਪਾਠ;
    device->Has_Primary_Selection_ਪਾਠ = X11_Has_Primary_Selection_ਪਾਠ;
    device->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼ = X11_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Stop_ਪਾਠ_ਨਿਵੇਸ਼ = X11_Stop_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area = X11_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->ਮੁਕਤ = X11_DeleteDevice;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = X11_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    ਜੇ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#ਜੇ_ਅੰਤ

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_ਖਿੜਕੀ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ਅੰਕੜੇ->is_xwayland = X11_IsXWayland(x11_display);
    ਜੇ (ਅੰਕੜੇ->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_ਬਹੁਲਕ_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    ਜੇ (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    ਵਾਪਸ device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_ਸੁਨੇਹਾ_Box,
    false
};

ਸਥਿਰ ਪੂਰਨ (*handler)(Display *, XErrorEvent *) = ਨਿਰਾ;
ਸਥਿਰ ਪੂਰਨ X11_Check_ਖਿੜਕੀ_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    ਜੇ (e->error_ਕੋਡ == Bad_ਖਿੜਕੀ) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ handler(d, e);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_Check_ਖਿੜਕੀ_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    ਪੂਰਨ ਸਥਿਤੀ, real_format;
    Atom real_type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read = 0, ਚੀਜ਼ਾਂ_ਖੱਬਾ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata = ਨਿਰਾ;
    ਖਿੜਕੀ_2 wm_ਖਿੜਕੀ = 0;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_ਖਿੜਕੀ_MANAGER
    ਅੱਖਰ *wm_name;
#ਜੇ_ਅੰਤ

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_ਖਿੜਕੀ_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_ਖਿੜਕੀ, &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
    ਜੇ (ਸਥਿਤੀ == Success) {
        ਜੇ (ਚੀਜ਼ਾਂ_read) {
            wm_ਖਿੜਕੀ = ((ਖਿੜਕੀ_2 *)propdata)[0];
        }
        ਜੇ (propdata) {
            X11_XFree(propdata);
            propdata = ਨਿਰਾ;
        }
    }

    ਜੇ (wm_ਖਿੜਕੀ) {
        ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, wm_ਖਿੜਕੀ, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_ਖਿੜਕੀ, &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
        ਜੇ (ਸਥਿਤੀ != Success || !ਚੀਜ਼ਾਂ_read || wm_ਖਿੜਕੀ != ((ਖਿੜਕੀ_2 *)propdata)[0]) {
            wm_ਖਿੜਕੀ = None;
        }
        ਜੇ (ਸਥਿਤੀ == Success && propdata) {
            X11_XFree(propdata);
            propdata = ਨਿਰਾ;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    ਜੇ (!wm_ਖਿੜਕੀ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_ਖਿੜਕੀ_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ;
    }
    ਅੰਕੜੇ->net_wm = true;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ DEBUG_ਖਿੜਕੀ_MANAGER
    wm_name = X11_Get_ਖਿੜਕੀ_Title(_this, wm_ਖਿੜਕੀ);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    // Get the process PID to be associated to the window
    ਅੰਕੜੇ->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    ਅੰਕੜੇ->ਖਿੜਕੀ_ਸਮੂਹ = (XID)(((size_t)ਅੰਕੜੇ->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_ATOM(X) ਅੰਕੜੇ->atoms.X = X11_XInternAtom(ਅੰਕੜੇ->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_ਖਿੜਕੀ);
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
    GET_ATOM(NET_WM_ਖਿੜਕੀ_OPACITY);
    GET_ATOM(NET_WM_USER_ਸਮਾਂ);
    GET_ATOM(NET_ਸਰਗਰਮ_ਖਿੜਕੀ);
    GET_ATOM(NET_ਚੌਖਟਾ_EXTENTS);
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
    GET_ATOM(Xdnd_ਸਥਿਤੀ);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_ਮੁਕੰਮਲ);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_ਖਿੜਕੀ_Manager(_this);

    ਜੇ (!X11_InitModes(_this)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_ਜੋੜੋ_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ਨਿਰਾ);
        SDL_ਜੋੜੋ_Mouse(SDL_DEFAULT_MOUSE_ID, ਨਿਰਾ);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#ਜੇ_ਅੰਤ

    X11_InitXsettings(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced ਵਿੱਚ_2 2000! This is likely ਮੰਜ਼ਿਲ become a hard error ਵਿੱਚ_2 a future libSDL3.
#ਜੇ_ਅੰਤ

    ਜੇ (!X11_InitKeyboard(_this)) {
        ਵਾਪਸ false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(ਅੰਕੜੇ->display, ਅੰਕੜੇ->atoms.CLIPBOARD, ਅੰਕੜੇ->atoms.TARGETS,
            ਅੰਕੜੇ->atoms.SDL_FORMATS, Get_ਖਿੜਕੀ(_this), Current_ਸਮਾਂ);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ) {
        X11_XDestroy_ਖਿੜਕੀ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->clipboard_ਖਿੜਕੀ);
    }

    ਜੇ (ਅੰਕੜੇ->xsettings_ਖਿੜਕੀ) {
        X11_XDestroy_ਖਿੜਕੀ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->xsettings_ਖਿੜਕੀ);
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

bool X11_Use_ਸਿੱਧਾ_Color_Visuals(ਖਾਲੀ)
{
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
