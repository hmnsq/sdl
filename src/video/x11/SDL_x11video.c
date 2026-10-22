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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ <unistd.h> // For getpid() and readlink()

#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_progressbar.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_x11framebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11pen.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11touch.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xfixes.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11messagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11shape.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xtest.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ "SDL_x11opengles.h"
#ಆದರೆ_ಅಂತ್ಯ

// Initialization/Query functions
ಸ್ಥಿರ bool X11_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ X11_VideoQuit(SDL_VideoDevice *_this);

// X11 driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ X11_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    ಆದರೆ (device->vulkan_config.loader_handle) {
        device->Vulkan_UnloadLibrary(device);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->display) {
        X11_XCloseDisplay(ದತ್ತಾಂಶ->display);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->request_display) {
        X11_XCloseDisplay(ದತ್ತಾಂಶ->request_display);
    }
    SDL_free(ದತ್ತಾಂಶ->windowlist);
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);

    SDL_X11_UnloadSymbols();
}

ಸ್ಥಿರ bool X11_IsXWayland(Display *d)
{
    ಪೂರ್ಣಾಂಕ opcode, event, error;
    ಹಿಂತಿರುಗಿ X11_XQueryExtension(d, "XWAYLAND", &opcode, &event, &error) == True;
}

ಸ್ಥಿರ bool X11_IsWSL(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_LINUX
    ಆದರೆ (SDL_Get_ಮಾರ್ಗ_Info("/proc/sys/fs/binfmt_misc/WSLInterop", ಖಾಲಿ) || SDL_Get_ಮಾರ್ಗ_Info("/run/WSL", ಖಾಲಿ)) { // if either of these exist, we're on WSL.
         ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ SDL_VideoDevice *X11_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *display = ಖಾಲಿ; // Use the DISPLAY environment variable
    Display *x11_display = ಖಾಲಿ;

    ಆದರೆ (!SDL_X11_ತುಂಬು_Symbols()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* Need for threading gl calls. This is also required for the proprietary
        nVidia driver to be threaded. */
    X11_XInit_ಎಳೆಗಳು();

    // Open the display first to be sure that X11 is available
    x11_display = X11_XOpenDisplay(display);

    ಆದರೆ (!x11_display) {
        SDL_X11_UnloadSymbols();

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *session = SDL_getenv("XDG_SESSION_TYPE");
        ಆದರೆ (session && SDL_strcasecmp(session, "wayland") == 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 (XWayland) display server");
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the X11 display server");
        }

        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ದತ್ತಾಂಶ = (ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ->global_mouse_ಬದಲಾಯಿತು = true;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    ದತ್ತಾಂಶ->ಸಕ್ರಿಯ_cursor_confined_ಕಿಟಕಿ = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES

    ದತ್ತಾಂಶ->display = x11_display;
    ದತ್ತಾಂಶ->request_display = X11_XOpenDisplay(display);
    ಆದರೆ (!ದತ್ತಾಂಶ->request_display) {
        X11_XCloseDisplay(ದತ್ತಾಂಶ->display);
        SDL_free(device->ಆಂತರಿಕ);
        SDL_free(device);
        SDL_X11_UnloadSymbols();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11_DEBUG
    X11_XSynchronize(ದತ್ತಾಂಶ->display, True);
#ಆದರೆ_ಅಂತ್ಯ

    /* Steam Deck will have an on-screen keyboard, so check their environment
     * variable so we can make use of SDL_StartTextInput.
     */
    ದತ್ತಾಂಶ->use_steam_screen_keyboard = SDL_GetHintBoolean(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD, false);

    // Set the function pointers
    device->VideoInit = X11_VideoInit;
    device->VideoQuit = X11_VideoQuit;
    device->ResetTouch = X11_ResetTouch;
    device->GetDisplayModes = X11_GetDisplayModes;
    device->GetDisplayBounds = X11_GetDisplayBounds;
    device->GetDisplayUsableBounds = X11_GetDisplayUsableBounds;
    device->Get_ಕಿಟಕಿ_ICCProfile = X11_Get_ಕಿಟಕಿ_ICCProfile;
    device->ಗಣ_Display_ಬಹುಲಕ = X11_ಗಣ_Display_ಬಹುಲಕ;
    device->SuspendScreenSaver = X11_SuspendScreenSaver;
    device->PumpEvents = X11_PumpEvents;
    device->WaitEventTimeout = X11_WaitEventTimeout;
    device->SendWakeupEvent = X11_SendWakeupEvent;

    device->CreateSDLWindow = X11_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = X11_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Icon = X11_ಗಣ_ಕಿಟಕಿ_Icon;
    device->ಗಣ_ಕಿಟಕಿ_Position = X11_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = X11_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ = X11_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ = X11_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ = X11_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ;
    device->Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ = X11_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Opacity = X11_ಗಣ_ಕಿಟಕಿ_Opacity;
    device->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ = X11_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ;
    device->ಗಣ_ಕಿಟಕಿ_Modal = X11_ಗಣ_ಕಿಟಕಿ_Modal;
    device->Show_ಕಿಟಕಿ = X11_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = X11_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = X11_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = X11_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = X11_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = X11_Restore_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Bordered = X11_ಗಣ_ಕಿಟಕಿ_Bordered;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = X11_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ = X11_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = X11_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Grab = X11_ಗಣ_ಕಿಟಕಿ_Mouse_Grab;
    device->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab = X11_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab;
    device->Destroy_ಕಿಟಕಿ = X11_Destroy_ಕಿಟಕಿ;
    device->Create_ಕಿಟಕಿ_Framebuffer = X11_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = X11_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = X11_Destroy_ಕಿಟಕಿ_Framebuffer;
    device->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test = X11_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test;
    device->AcceptDragAndDrop = X11_AcceptDragAndDrop;
    device->Update_ಕಿಟಕಿ_Shape = X11_Update_ಕಿಟಕಿ_Shape;
    device->Flash_ಕಿಟಕಿ = X11_Flash_ಕಿಟಕಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    device->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ = DBUS_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_USE_LIBDBUS
    device->Show_ಕಿಟಕಿ_System_Menu = X11_Show_ಕಿಟಕಿ_System_Menu;
    device->ಗಣ_ಕಿಟಕಿ_Focusable = X11_ಗಣ_ಕಿಟಕಿ_Focusable;
    device->Sync_ಕಿಟಕಿ = X11_Sync_ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Rect = X11_ಗಣ_ಕಿಟಕಿ_Mouse_Rect;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
    device->GL_ತುಂಬು_Library = X11_GL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = X11_GL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = X11_GL_UnloadLibrary;
    device->GL_CreateContext = X11_GL_CreateContext;
    device->GL_MakeCurrent = X11_GL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = X11_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = X11_GL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = X11_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = X11_GL_DestroyContext;
    device->GL_GetEGLSurface = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_FORCE_EGL, false)) {
#ಆದರೆ_ಅಂತ್ಯ
        device->GL_ತುಂಬು_Library = X11_GLES_ತುಂಬು_Library;
        device->GL_Get_Proc_ವಿಳಾಸ = X11_GLES_Get_Proc_ವಿಳಾಸ;
        device->GL_UnloadLibrary = X11_GLES_UnloadLibrary;
        device->GL_CreateContext = X11_GLES_CreateContext;
        device->GL_MakeCurrent = X11_GLES_MakeCurrent;
        device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = X11_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
        device->GL_Get_ಅದಲುಬದಲು_Interval = X11_GLES_Get_ಅದಲುಬದಲು_Interval;
        device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = X11_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
        device->GL_DestroyContext = X11_GLES_DestroyContext;
        device->GL_GetEGLSurface = X11_GLES_GetEGLSurface;
        device->GL_ಗಣ_Default_Profile_Config = X11_GLES_ಗಣ_Default_Profile_Config;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_GLX
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

    device->Get_ಪಠ್ಯ_Mime_Types = X11_Get_ಪಠ್ಯ_Mime_Types;
    device->ಗಣ_Clipboard_ದತ್ತಾಂಶ = X11_ಗಣ_Clipboard_ದತ್ತಾಂಶ;
    device->Get_Clipboard_ದತ್ತಾಂಶ = X11_Get_Clipboard_ದತ್ತಾಂಶ;
    device->Has_Clipboard_ದತ್ತಾಂಶ = X11_Has_Clipboard_ದತ್ತಾಂಶ;
    device->ಗಣ_Primary_Selection_ಪಠ್ಯ = X11_ಗಣ_Primary_Selection_ಪಠ್ಯ;
    device->Get_Primary_Selection_ಪಠ್ಯ = X11_Get_Primary_Selection_ಪಠ್ಯ;
    device->Has_Primary_Selection_ಪಠ್ಯ = X11_Has_Primary_Selection_ಪಠ್ಯ;
    device->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು = X11_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Stop_ಪಠ್ಯ_ಒಳಹರಿವು = X11_Stop_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area = X11_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area;
    device->HasScreenKeyboardSupport = X11_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = X11_ShowScreenKeyboard;
    device->HideScreenKeyboard = X11_HideScreenKeyboard;

    device->ಬಿಡುಗಡೆ = X11_DeleteDevice;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = X11_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = X11_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = X11_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = X11_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = X11_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = X11_Vulkan_GetPresentationSupport;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    ಆದರೆ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#ಆದರೆ_ಅಂತ್ಯ

    device->device_caps = VIDEO_DEVICE_CAPS_HAS_POPUP_ಕಿಟಕಿ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ದತ್ತಾಂಶ->is_xwayland = X11_IsXWayland(x11_display);
    ಆದರೆ (ದತ್ತಾಂಶ->is_xwayland) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Detected XWayland");

        device->device_caps |= VIDEO_DEVICE_CAPS_ಬಹುಲಕ_SWITCHING_EMULATED |
                               VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;
    }
    ಆದರೆ (X11_IsWSL()) {
        // On WSL, direct X11 is faster than using OpenGL for window framebuffers, so try to detect WSL and avoid texture framebuffer.
        device->device_caps &= ~VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;
    }

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap X11_bootstrap = {
    "x11", "SDL X11 video driver",
    X11_CreateDevice,
    X11_Show_ಸಂದೇಶ_Box,
    false
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ (*handler)(Display *, XErrorEvent *) = ಖಾಲಿ;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_Check_ಕಿಟಕಿ_Manager_Error_Handler(Display *d, XErrorEvent *e)
{
    ಆದರೆ (e->error_ಸಂಕೇತ == Bad_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ handler(d, e);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Check_ಕಿಟಕಿ_Manager(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->display;
    Atom _NET_SUPPORTING_WM_CHECK;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2, real_format;
    Atom real_type;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata = ಖಾಲಿ;
    ಕಿಟಕಿ_2 wm_ಕಿಟಕಿ = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_ಕಿಟಕಿ_MANAGER
    ಅಕ್ಷರ *wm_name;
#ಆದರೆ_ಅಂತ್ಯ

    // Set up a handler to gracefully catch errors
    X11_XSync(display, False);
    handler = X11_XSetErrorHandler(X11_Check_ಕಿಟಕಿ_Manager_Error_Handler);

    _NET_SUPPORTING_WM_CHECK = X11_XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, Default_ಬೇರು_ಕಿಟಕಿ(display), _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_ಕಿಟಕಿ, &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == Success) {
        ಆದರೆ (ವಸ್ತುಗಳು_read) {
            wm_ಕಿಟಕಿ = ((ಕಿಟಕಿ_2 *)propdata)[0];
        }
        ಆದರೆ (propdata) {
            X11_XFree(propdata);
            propdata = ಖಾಲಿ;
        }
    }

    ಆದರೆ (wm_ಕಿಟಕಿ) {
        ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, wm_ಕಿಟಕಿ, _NET_SUPPORTING_WM_CHECK, 0L, 1L, False, XA_ಕಿಟಕಿ, &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
        ಆದರೆ (ಸ್ಥಿತಿ_2 != Success || !ವಸ್ತುಗಳು_read || wm_ಕಿಟಕಿ != ((ಕಿಟಕಿ_2 *)propdata)[0]) {
            wm_ಕಿಟಕಿ = None;
        }
        ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
            X11_XFree(propdata);
            propdata = ಖಾಲಿ;
        }
    }

    // Reset the error handler, we're done checking
    X11_XSync(display, False);
    X11_XSetErrorHandler(handler);

    ಆದರೆ (!wm_ಕಿಟಕಿ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_ಕಿಟಕಿ_MANAGER
        SDL_Log("Couldn't get _NET_SUPPORTING_WM_CHECK property");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ;
    }
    ದತ್ತಾಂಶ->net_wm = true;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG_ಕಿಟಕಿ_MANAGER
    wm_name = X11_Get_ಕಿಟಕಿ_Title(_this, wm_ಕಿಟಕಿ);
    SDL_Log("Window manager: %s", wm_name);
    SDL_free(wm_name);
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ bool X11_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    // Get the process PID to be associated to the window
    ದತ್ತಾಂಶ->pid = getpid();

    // I have no idea how random this actually is, or has to be.
    ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಗುಂಪು = (XID)(((size_t)ದತ್ತಾಂಶ->pid) ^ ((size_t)_this));

    // Look up some useful Atoms
#ವ್ಯಾಖ್ಯಾನಿಸು GET_ATOM(X) ದತ್ತಾಂಶ->atoms.X = X11_XInternAtom(ದತ್ತಾಂಶ->display, #X, False)
    GET_ATOM(WM_PROTOCOLS);
    GET_ATOM(WM_DELETE_ಕಿಟಕಿ);
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
    GET_ATOM(NET_WM_ಕಿಟಕಿ_OPACITY);
    GET_ATOM(NET_WM_USER_ಸಮಯ);
    GET_ATOM(NET_ಸಕ್ರಿಯ_ಕಿಟಕಿ);
    GET_ATOM(NET_ಚೌಕಟ್ಟು_EXTENTS);
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
    GET_ATOM(Xdnd_ಸ್ಥಿತಿ);
    GET_ATOM(XdndTypeList);
    GET_ATOM(XdndActionCopy);
    GET_ATOM(XdndDrop);
    GET_ATOM(Xdnd_ಪೂರ್ಣಗೊಂಡ);
    GET_ATOM(XdndSelection);
    GET_ATOM(XKLAVIER_STATE);

    // Detect the window manager
    X11_Check_ಕಿಟಕಿ_Manager(_this);

    ಆದರೆ (!X11_InitModes(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!X11_InitXinput2(_this)) {
        // Assume a mouse and keyboard are attached
        SDL_ಕೂಡಿಸು_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ಖಾಲಿ);
        SDL_ಕೂಡಿಸು_Mouse(SDL_DEFAULT_MOUSE_ID, ಖಾಲಿ);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    X11_InitXfixes(_this);
#ಆದರೆ_ಅಂತ್ಯ

    X11_InitXsettings(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_InitXsync(_this);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XTEST
    X11_InitXTest(_this);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ X_HAVE_UTF8_STRING
#warning X server does not support UTF8_STRING, a feature introduced ಒಳ_2 2000! This is likely ಗಮ್ಯ become a hard error ಒಳ_2 a future libSDL3.
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!X11_InitKeyboard(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }
    X11_InitMouse(_this);

    X11_InitTouch(_this);

    X11_InitPen(_this);

    // Request currently available mime-types in the clipboard.
    X11_XConvertSelection(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->atoms.CLIPBOARD, ದತ್ತಾಂಶ->atoms.TARGETS,
            ದತ್ತಾಂಶ->atoms.SDL_FORMATS, Get_ಕಿಟಕಿ(_this), Current_ಸಮಯ);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->clipboard_ಕಿಟಕಿ) {
        X11_XDestroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->clipboard_ಕಿಟಕಿ);
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xsettings_ಕಿಟಕಿ) {
        X11_XDestroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->xsettings_ಕಿಟಕಿ);
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

bool X11_Use_ನೇರ_Color_Visuals(ಶೂನ್ಯ)
{
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_NODIRECTCOLOR, false)) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
