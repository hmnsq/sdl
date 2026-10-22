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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#ଯଦି defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(ଅଚଳ ଅକ୍ଷର *name, Uint32 style, ଶୂନ୍ୟ *hInst)
{
    (ଶୂନ୍ୟ)name;
    (ଶୂନ୍ୟ)style;
    (ଶୂନ୍ୟ)hInst;
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ SDL_UnregisterApp(ଶୂନ୍ୟ)
{
}

ଶୂନ୍ୟ SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ଶୂନ୍ୟ *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *adapterIndex, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *outputIndex)
{
    (ଶୂନ୍ୟ)displayID;
    (ଶୂନ୍ୟ)adapterIndex;
    (ଶୂନ୍ୟ)outputIndex;
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ଶୂନ୍ୟ)displayID;
    SDL_Unsupported();
    ଫେରନ୍ତୁ -1;
}

#ନଚେତଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ଶୂନ୍ୟ)displayID;
    SDL_Unsupported();
    ଫେରନ୍ତୁ -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (ଶୂନ୍ୟ)outTaskQueue;
    ଫେରନ୍ତୁ SDL_Unsupported();
}

#endif

#ଯଦି !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ଶୂନ୍ୟ SDL_OnApplicationDidChangeStatusBarOrientation(ଶୂନ୍ୟ)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval, SDL_iOSAnimationCallback callback, ଶୂନ୍ୟ *callbackParam)
{
    (ଶୂନ୍ୟ)window;
    (ଶୂନ୍ୟ)interval;
    (ଶୂନ୍ୟ)callback;
    (ଶୂନ୍ୟ)callbackParam;
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ଶୂନ୍ୟ SDL_SetiOSEventPump(bool enabled)
{
    (ଶୂନ୍ୟ)enabled;
    SDL_Unsupported();
}
#endif

