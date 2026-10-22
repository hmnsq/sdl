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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#எனில் defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(மாறிலி எழுத்து *name, Uint32 style, வெறுமை *hInst)
{
    (வெறுமை)name;
    (வெறுமை)style;
    (வெறுமை)hInst;
    திரும்பு true;
}

வெறுமை SDL_UnregisterApp(வெறுமை)
{
}

வெறுமை SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, வெறுமை *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, முழு *adapterIndex, முழு *outputIndex)
{
    (வெறுமை)displayID;
    (வெறுமை)adapterIndex;
    (வெறுமை)outputIndex;
    திரும்பு SDL_Unsupported();
}

முழு SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (வெறுமை)displayID;
    SDL_Unsupported();
    திரும்பு -1;
}

#அல்லதெனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

முழு SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (வெறுமை)displayID;
    SDL_Unsupported();
    திரும்பு -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (வெறுமை)outTaskQueue;
    திரும்பு SDL_Unsupported();
}

#endif

#எனில் !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

வெறுமை SDL_OnApplicationDidChangeStatusBarOrientation(வெறுமை)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, முழு interval, SDL_iOSAnimationCallback callback, வெறுமை *callbackParam)
{
    (வெறுமை)window;
    (வெறுமை)interval;
    (வெறுமை)callback;
    (வெறுமை)callbackParam;
    திரும்பு SDL_Unsupported();
}

வெறுமை SDL_SetiOSEventPump(bool enabled)
{
    (வெறுமை)enabled;
    SDL_Unsupported();
}
#endif

