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
#ضمن "SDL_internal.h"

#ضمن "SDL_video_unsupported.h"

#اگر_تعریف_نشده SDL_VIDEO_DRIVER_WINDOWS

#إذا defined(SDL_PLATFORM_WINDOWS)

bool SDL_ثبات_App(ثابت حرف *name, Uint32 style, فراغ *hInst)
{
    (فراغ)name;
    (فراغ)style;
    (فراغ)hInst;
    أرجع true;
}

فراغ SDL_UnregisterApp(فراغ)
{
}

فراغ SDL_مجموعه_Windows_پیام_Hook(SDL_Windows_پیام_Hook callback, فراغ *userdata)
{
}

#پایان_اگر // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحيح *adapter_شاخص, صحيح *output_شاخص)
{
    (فراغ)displayID;
    (فراغ)adapter_شاخص;
    (فراغ)output_شاخص;
    أرجع SDL_Unsupported();
}

صحيح SDL_Get_Direct3_D9_Adapter_شاخص(SDL_DisplayID displayID)
{
    (فراغ)displayID;
    SDL_Unsupported();
    أرجع -1;
}

#وإلاإذا defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

صحيح SDL_Get_Direct3_D9_Adapter_شاخص(SDL_DisplayID displayID)
{
    (فراغ)displayID;
    SDL_Unsupported();
    أرجع -1;
}

#پایان_اگر // !SDL_VIDEO_DRIVER_WINDOWS

#اگر_تعریف_نشده SDL_PLATFORM_GDK

bool SDL_Get_GDKTask_صف(XTask_صف_Handle *بیرون_Task_صف)
{
    (فراغ)بیرون_Task_صف;
    أرجع SDL_Unsupported();
}

#پایان_اگر

#إذا !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

فراغ SDL_On_Application_Did_Change_وضعیت_Bar_Orientation(فراغ)
{
    SDL_Unsupported();
}

#پایان_اگر

#اگر_تعریف_نشده SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_پنجره *پنجره, صحيح interval, SDL_iOSAnimationCallback callback, فراغ *callbackParam)
{
    (فراغ)پنجره;
    (فراغ)interval;
    (فراغ)callback;
    (فراغ)callbackParam;
    أرجع SDL_Unsupported();
}

فراغ SDL_SetiOSEventPump(bool enabled)
{
    (فراغ)enabled;
    SDL_Unsupported();
}
#پایان_اگر

