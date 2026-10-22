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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_video_unsupported.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS

#ਜੇ defined(SDL_PLATFORM_WINDOWS)

bool SDL_ਰਜਿਸਟਰ_App(ਅਚਲ ਅੱਖਰ *name, Uint32 style, ਖਾਲੀ *hInst)
{
    (ਖਾਲੀ)name;
    (ਖਾਲੀ)style;
    (ਖਾਲੀ)hInst;
    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_UnregisterApp(ਖਾਲੀ)
{
}

ਖਾਲੀ SDL_ਸੈੱਟ_Windows_ਸੁਨੇਹਾ_Hook(SDL_Windows_ਸੁਨੇਹਾ_Hook callback, ਖਾਲੀ *userdata)
{
}

#ਜੇ_ਅੰਤ // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ਪੂਰਨ *adapter_ਸੂਚਕਾਂਕ, ਪੂਰਨ *output_ਸੂਚਕਾਂਕ)
{
    (ਖਾਲੀ)displayID;
    (ਖਾਲੀ)adapter_ਸੂਚਕਾਂਕ;
    (ਖਾਲੀ)output_ਸੂਚਕਾਂਕ;
    ਵਾਪਸ SDL_Unsupported();
}

ਪੂਰਨ SDL_Get_Direct3_D9_Adapter_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID)
{
    (ਖਾਲੀ)displayID;
    SDL_Unsupported();
    ਵਾਪਸ -1;
}

#ਜਾਂਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ਪੂਰਨ SDL_Get_Direct3_D9_Adapter_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID)
{
    (ਖਾਲੀ)displayID;
    SDL_Unsupported();
    ਵਾਪਸ -1;
}

#ਜੇ_ਅੰਤ // !SDL_VIDEO_DRIVER_WINDOWS

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_GDK

bool SDL_Get_GDKTask_ਕਤਾਰ(XTask_ਕਤਾਰ_Handle *ਬਾਹਰਲਾ_Task_ਕਤਾਰ)
{
    (ਖਾਲੀ)ਬਾਹਰਲਾ_Task_ਕਤਾਰ;
    ਵਾਪਸ SDL_Unsupported();
}

#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ਖਾਲੀ SDL_On_Application_Did_Change_ਸਥਿਤੀ_Bar_Orientation(ਖਾਲੀ)
{
    SDL_Unsupported();
}

#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ interval, SDL_iOSAnimationCallback callback, ਖਾਲੀ *callbackParam)
{
    (ਖਾਲੀ)ਖਿੜਕੀ;
    (ਖਾਲੀ)interval;
    (ਖਾਲੀ)callback;
    (ਖਾਲੀ)callbackParam;
    ਵਾਪਸ SDL_Unsupported();
}

ਖਾਲੀ SDL_SetiOSEventPump(bool enabled)
{
    (ਖਾਲੀ)enabled;
    SDL_Unsupported();
}
#ਜੇ_ਅੰਤ

