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

#شامل "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#اگر defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(ثابت نویسه *name, Uint32 style, تهی *hInst)
{
    (تهی)name;
    (تهی)style;
    (تهی)hInst;
    بازگشت true;
}

تهی SDL_UnregisterApp(تهی)
{
}

تهی SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, تهی *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحیح *adapterIndex, صحیح *outputIndex)
{
    (تهی)displayID;
    (تهی)adapterIndex;
    (تهی)outputIndex;
    بازگشت SDL_Unsupported();
}

صحیح SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (تهی)displayID;
    SDL_Unsupported();
    بازگشت -1;
}

#وگرنهاگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

صحیح SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (تهی)displayID;
    SDL_Unsupported();
    بازگشت -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (تهی)outTaskQueue;
    بازگشت SDL_Unsupported();
}

#endif

#اگر !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

تهی SDL_OnApplicationDidChangeStatusBarOrientation(تهی)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, صحیح interval, SDL_iOSAnimationCallback callback, تهی *callbackParam)
{
    (تهی)window;
    (تهی)interval;
    (تهی)callback;
    (تهی)callbackParam;
    بازگشت SDL_Unsupported();
}

تهی SDL_SetiOSEventPump(bool enabled)
{
    (تهی)enabled;
    SDL_Unsupported();
}
#endif

