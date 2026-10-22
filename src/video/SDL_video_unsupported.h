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

#اگر !defined(SDL_VIDEO_DRIVER_WINDOWS)

#اگر defined(SDL_PLATFORM_WINDOWS)

خارجی SDL_DECLSPEC bool SDLCALL SDL_رجسٹر_App(ثابت حرف *name, Uint32 style, خالی *hInst);
خارجی SDL_DECLSPEC خالی SDLCALL SDL_UnregisterApp(خالی);
خارجی SDL_DECLSPEC خالی SDLCALL SDL_سیٹ_Windows_پیغام_Hook(SDL_Windows_پیغام_Hook callback, خالی *userdata);

#اگر_ختم /* SDL_PLATFORM_WINDOWS */

خارجی SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحیح *adapter_اشاریہ, صحیح *output_اشاریہ);
خارجی SDL_DECLSPEC صحیح SDLCALL SDL_Get_Direct3_D9_Adapter_اشاریہ(SDL_DisplayID displayID);

#وگرنہ_اگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

خارجی SDL_DECLSPEC صحیح SDLCALL SDL_Get_Direct3_D9_Adapter_اشاریہ(SDL_DisplayID displayID);

#اگر_ختم /* !SDL_VIDEO_DRIVER_WINDOWS */

#اگر !defined(SDL_PLATFORM_GDK)

قسمتعریف ساخت XTask_قطار_Handle XTask_قطار_Handle;

خارجی SDL_DECLSPEC bool SDLCALL SDL_Get_GDKTask_قطار(XTask_قطار_Handle *برآمد_Task_قطار);

#اگر_ختم /* !SDL_PLATFORM_GDK */

#اگر !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

خارجی SDL_DECLSPEC خالی SDLCALL SDL_On_Application_Did_Change_حالت_Bar_Orientation(خالی);

#اگر_ختم

#اگر !defined(SDL_VIDEO_DRIVER_UIKIT)

قسمتعریف خالی (SDLCALL *SDL_iOSAnimationCallback)(خالی *userdata);

خارجی SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_کھڑکی *کھڑکی, صحیح interval, SDL_iOSAnimationCallback callback, خالی *callbackParam);
خارجی SDL_DECLSPEC خالی SDLCALL SDL_SetiOSEventPump(bool enabled);
#اگر_ختم
