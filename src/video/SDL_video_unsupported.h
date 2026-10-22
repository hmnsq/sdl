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

#ਜੇ !defined(SDL_VIDEO_DRIVER_WINDOWS)

#ਜੇ defined(SDL_PLATFORM_WINDOWS)

ਬਾਹਰੀ SDL_DECLSPEC bool SDLCALL SDL_ਰਜਿਸਟਰ_App(ਅਚਲ ਅੱਖਰ *name, Uint32 style, ਖਾਲੀ *hInst);
ਬਾਹਰੀ SDL_DECLSPEC ਖਾਲੀ SDLCALL SDL_UnregisterApp(ਖਾਲੀ);
ਬਾਹਰੀ SDL_DECLSPEC ਖਾਲੀ SDLCALL SDL_ਸੈੱਟ_Windows_ਸੁਨੇਹਾ_Hook(SDL_Windows_ਸੁਨੇਹਾ_Hook callback, ਖਾਲੀ *userdata);

#ਜੇ_ਅੰਤ /* SDL_PLATFORM_WINDOWS */

ਬਾਹਰੀ SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ਪੂਰਨ *adapter_ਸੂਚਕਾਂਕ, ਪੂਰਨ *output_ਸੂਚਕਾਂਕ);
ਬਾਹਰੀ SDL_DECLSPEC ਪੂਰਨ SDLCALL SDL_Get_Direct3_D9_Adapter_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID);

#ਜਾਂਜੇ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ਬਾਹਰੀ SDL_DECLSPEC ਪੂਰਨ SDLCALL SDL_Get_Direct3_D9_Adapter_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID);

#ਜੇ_ਅੰਤ /* !SDL_VIDEO_DRIVER_WINDOWS */

#ਜੇ !defined(SDL_PLATFORM_GDK)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XTask_ਕਤਾਰ_Handle XTask_ਕਤਾਰ_Handle;

ਬਾਹਰੀ SDL_DECLSPEC bool SDLCALL SDL_Get_GDKTask_ਕਤਾਰ(XTask_ਕਤਾਰ_Handle *ਬਾਹਰਲਾ_Task_ਕਤਾਰ);

#ਜੇ_ਅੰਤ /* !SDL_PLATFORM_GDK */

#ਜੇ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ਬਾਹਰੀ SDL_DECLSPEC ਖਾਲੀ SDLCALL SDL_On_Application_Did_Change_ਸਥਿਤੀ_Bar_Orientation(ਖਾਲੀ);

#ਜੇ_ਅੰਤ

#ਜੇ !defined(SDL_VIDEO_DRIVER_UIKIT)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (SDLCALL *SDL_iOSAnimationCallback)(ਖਾਲੀ *userdata);

ਬਾਹਰੀ SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ interval, SDL_iOSAnimationCallback callback, ਖਾਲੀ *callbackParam);
ਬਾਹਰੀ SDL_DECLSPEC ਖਾਲੀ SDLCALL SDL_SetiOSEventPump(bool enabled);
#ਜੇ_ਅੰਤ
