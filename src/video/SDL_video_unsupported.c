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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#જો defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(અચલ અક્ષર *name, Uint32 style, શૂન્ય *hInst)
{
    (શૂન્ય)name;
    (શૂન્ય)style;
    (શૂન્ય)hInst;
    પાછા true;
}

શૂન્ય SDL_UnregisterApp(શૂન્ય)
{
}

શૂન્ય SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, શૂન્ય *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, પૂર્ણાંક *adapterIndex, પૂર્ણાંક *outputIndex)
{
    (શૂન્ય)displayID;
    (શૂન્ય)adapterIndex;
    (શૂન્ય)outputIndex;
    પાછા SDL_Unsupported();
}

પૂર્ણાંક SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (શૂન્ય)displayID;
    SDL_Unsupported();
    પાછા -1;
}

#અથવાજો defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

પૂર્ણાંક SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (શૂન્ય)displayID;
    SDL_Unsupported();
    પાછા -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (શૂન્ય)outTaskQueue;
    પાછા SDL_Unsupported();
}

#endif

#જો !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

શૂન્ય SDL_OnApplicationDidChangeStatusBarOrientation(શૂન્ય)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, પૂર્ણાંક interval, SDL_iOSAnimationCallback callback, શૂન્ય *callbackParam)
{
    (શૂન્ય)window;
    (શૂન્ય)interval;
    (શૂન્ય)callback;
    (શૂન્ય)callbackParam;
    પાછા SDL_Unsupported();
}

શૂન્ય SDL_SetiOSEventPump(bool enabled)
{
    (શૂન્ય)enabled;
    SDL_Unsupported();
}
#endif

