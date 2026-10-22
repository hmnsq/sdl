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
#অন্তর্ভাৱ "SDL_internal.h"

#অন্তর্ভাৱ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#যদি defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(ধ্রুৱ ৱর্ণ *name, Uint32 style, শূন্য *hInst)
{
    (শূন্য)name;
    (শূন্য)style;
    (শূন্য)hInst;
    ঘূৰাই true;
}

শূন্য SDL_UnregisterApp(শূন্য)
{
}

শূন্য SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, শূন্য *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, পূর্ণাঙ্ক *adapterIndex, পূর্ণাঙ্ক *outputIndex)
{
    (শূন্য)displayID;
    (শূন্য)adapterIndex;
    (শূন্য)outputIndex;
    ঘূৰাই SDL_Unsupported();
}

পূর্ণাঙ্ক SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (শূন্য)displayID;
    SDL_Unsupported();
    ঘূৰাই -1;
}

#নোচেদ্যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

পূর্ণাঙ্ক SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (শূন্য)displayID;
    SDL_Unsupported();
    ঘূৰাই -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (শূন্য)outTaskQueue;
    ঘূৰাই SDL_Unsupported();
}

#endif

#যদি !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

শূন্য SDL_OnApplicationDidChangeStatusBarOrientation(শূন্য)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, পূর্ণাঙ্ক interval, SDL_iOSAnimationCallback callback, শূন্য *callbackParam)
{
    (শূন্য)window;
    (শূন্য)interval;
    (শূন্য)callback;
    (শূন্য)callbackParam;
    ঘূৰাই SDL_Unsupported();
}

শূন্য SDL_SetiOSEventPump(bool enabled)
{
    (শূন্য)enabled;
    SDL_Unsupported();
}
#endif

