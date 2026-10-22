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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_video_unsupported.h"

#నిర్వచితం_కాకపోతే SDL_VIDEO_DRIVER_WINDOWS

#ఒకవేళ defined(SDL_PLATFORM_WINDOWS)

bool SDL_రిజిస్టరు_App(స్థిరరాశి అక్షరం *name, Uint32 style, శూన్య *hInst)
{
    (శూన్య)name;
    (శూన్య)style;
    (శూన్య)hInst;
    తిరిగి true;
}

శూన్య SDL_UnregisterApp(శూన్య)
{
}

శూన్య SDL_సమితి_Windows_సందేశం_Hook(SDL_Windows_సందేశం_Hook callback, శూన్య *userdata)
{
}

#అయితే_ముగింపు // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, పూర్ణాంకం *adapter_సూచీ, పూర్ణాంకం *output_సూచీ)
{
    (శూన్య)displayID;
    (శూన్య)adapter_సూచీ;
    (శూన్య)output_సూచీ;
    తిరిగి SDL_Unsupported();
}

పూర్ణాంకం SDL_Get_Direct3_D9_Adapter_సూచీ(SDL_DisplayID displayID)
{
    (శూన్య)displayID;
    SDL_Unsupported();
    తిరిగి -1;
}

#లేదావేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

పూర్ణాంకం SDL_Get_Direct3_D9_Adapter_సూచీ(SDL_DisplayID displayID)
{
    (శూన్య)displayID;
    SDL_Unsupported();
    తిరిగి -1;
}

#అయితే_ముగింపు // !SDL_VIDEO_DRIVER_WINDOWS

#నిర్వచితం_కాకపోతే SDL_PLATFORM_GDK

bool SDL_Get_GDKTask_వరుస(XTask_వరుస_Handle *బహిర్గతం_Task_వరుస)
{
    (శూన్య)బహిర్గతం_Task_వరుస;
    తిరిగి SDL_Unsupported();
}

#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

శూన్య SDL_On_Application_Did_Change_స్థితి_Bar_Orientation(శూన్య)
{
    SDL_Unsupported();
}

#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_కిటికీ *కిటికీ, పూర్ణాంకం interval, SDL_iOSAnimationCallback callback, శూన్య *callbackParam)
{
    (శూన్య)కిటికీ;
    (శూన్య)interval;
    (శూన్య)callback;
    (శూన్య)callbackParam;
    తిరిగి SDL_Unsupported();
}

శూన్య SDL_SetiOSEventPump(bool enabled)
{
    (శూన్య)enabled;
    SDL_Unsupported();
}
#అయితే_ముగింపు

