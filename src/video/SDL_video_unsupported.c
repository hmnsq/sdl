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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#എങ്കിൽ defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(സ്ഥിരം അക്ഷരം *name, Uint32 style, ശൂന്യം *hInst)
{
    (ശൂന്യം)name;
    (ശൂന്യം)style;
    (ശൂന്യം)hInst;
    തിരികെ true;
}

ശൂന്യം SDL_UnregisterApp(ശൂന്യം)
{
}

ശൂന്യം SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ശൂന്യം *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, പൂർണ്ണസംഖ്യ *adapterIndex, പൂർണ്ണസംഖ്യ *outputIndex)
{
    (ശൂന്യം)displayID;
    (ശൂന്യം)adapterIndex;
    (ശൂന്യം)outputIndex;
    തിരികെ SDL_Unsupported();
}

പൂർണ്ണസംഖ്യ SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ശൂന്യം)displayID;
    SDL_Unsupported();
    തിരികെ -1;
}

#അല്ലെങ്കിലെങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

പൂർണ്ണസംഖ്യ SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (ശൂന്യം)displayID;
    SDL_Unsupported();
    തിരികെ -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (ശൂന്യം)outTaskQueue;
    തിരികെ SDL_Unsupported();
}

#endif

#എങ്കിൽ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ശൂന്യം SDL_OnApplicationDidChangeStatusBarOrientation(ശൂന്യം)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, പൂർണ്ണസംഖ്യ interval, SDL_iOSAnimationCallback callback, ശൂന്യം *callbackParam)
{
    (ശൂന്യം)window;
    (ശൂന്യം)interval;
    (ശൂന്യം)callback;
    (ശൂന്യം)callbackParam;
    തിരികെ SDL_Unsupported();
}

ശൂന്യം SDL_SetiOSEventPump(bool enabled)
{
    (ശൂന്യം)enabled;
    SDL_Unsupported();
}
#endif

