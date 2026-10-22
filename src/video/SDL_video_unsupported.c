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

#ಅನ್ತರ್ಭಾವ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#ಯದಿ defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(ಧ್ರುವ ವರ್ಣ *name, Uint32 style, ಶೂನ್ಯ *hInst)
{
    (ಶೂನ್ಯ)name;
    (ಶೂನ್ಯ)style;
    (ಶೂನ್ಯ)hInst;
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_UnregisterApp(ಶೂನ್ಯ)
{
}

ಶೂನ್ಯ SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ಶೂನ್ಯ *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ಪೂರ್ಣಾಙ್ಕ *adapterIndex, ಪೂರ್ಣಾಙ್ಕ *outputIndex)
{
    (ಶೂನ್ಯ)displayID;
    (ಶೂನ್ಯ)adapterIndex;
    (ಶೂನ್ಯ)outputIndex;
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ಪೂರ್ಣಾಙ್ಕ SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ಶೂನ್ಯ)displayID;
    SDL_Unsupported();
    ಪ್ರತ್ಯಾಗಮ -1;
}

#ನೋಚೇದ್ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ಪೂರ್ಣಾಙ್ಕ SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ಶೂನ್ಯ)displayID;
    SDL_Unsupported();
    ಪ್ರತ್ಯಾಗಮ -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (ಶೂನ್ಯ)outTaskQueue;
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

#endif

#ಯದಿ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ಶೂನ್ಯ SDL_OnApplicationDidChangeStatusBarOrientation(ಶೂನ್ಯ)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ interval, SDL_iOSAnimationCallback callback, ಶೂನ್ಯ *callbackParam)
{
    (ಶೂನ್ಯ)window;
    (ಶೂನ್ಯ)interval;
    (ಶೂನ್ಯ)callback;
    (ಶೂನ್ಯ)callbackParam;
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ಶೂನ್ಯ SDL_SetiOSEventPump(bool enabled)
{
    (ಶೂನ್ಯ)enabled;
    SDL_Unsupported();
}
#endif

