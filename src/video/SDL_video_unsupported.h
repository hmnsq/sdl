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

#ఒకవేళ !defined(SDL_VIDEO_DRIVER_WINDOWS)

#ఒకవేళ defined(SDL_PLATFORM_WINDOWS)

బాహ్య SDL_DECLSPEC bool SDLCALL SDL_రిజిస్టరు_App(స్థిరరాశి అక్షరం *name, Uint32 style, శూన్య *hInst);
బాహ్య SDL_DECLSPEC శూన్య SDLCALL SDL_UnregisterApp(శూన్య);
బాహ్య SDL_DECLSPEC శూన్య SDLCALL SDL_సమితి_Windows_సందేశం_Hook(SDL_Windows_సందేశం_Hook callback, శూన్య *userdata);

#అయితే_ముగింపు /* SDL_PLATFORM_WINDOWS */

బాహ్య SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, పూర్ణాంకం *adapter_సూచీ, పూర్ణాంకం *output_సూచీ);
బాహ్య SDL_DECLSPEC పూర్ణాంకం SDLCALL SDL_Get_Direct3_D9_Adapter_సూచీ(SDL_DisplayID displayID);

#లేదావేళ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

బాహ్య SDL_DECLSPEC పూర్ణాంకం SDLCALL SDL_Get_Direct3_D9_Adapter_సూచీ(SDL_DisplayID displayID);

#అయితే_ముగింపు /* !SDL_VIDEO_DRIVER_WINDOWS */

#ఒకవేళ !defined(SDL_PLATFORM_GDK)

రకనిర్వచనం నిర్మాణం XTask_వరుస_Handle XTask_వరుస_Handle;

బాహ్య SDL_DECLSPEC bool SDLCALL SDL_Get_GDKTask_వరుస(XTask_వరుస_Handle *బహిర్గతం_Task_వరుస);

#అయితే_ముగింపు /* !SDL_PLATFORM_GDK */

#ఒకవేళ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

బాహ్య SDL_DECLSPEC శూన్య SDLCALL SDL_On_Application_Did_Change_స్థితి_Bar_Orientation(శూన్య);

#అయితే_ముగింపు

#ఒకవేళ !defined(SDL_VIDEO_DRIVER_UIKIT)

రకనిర్వచనం శూన్య (SDLCALL *SDL_iOSAnimationCallback)(శూన్య *userdata);

బాహ్య SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_కిటికీ *కిటికీ, పూర్ణాంకం interval, SDL_iOSAnimationCallback callback, శూన్య *callbackParam);
బాహ్య SDL_DECLSPEC శూన్య SDLCALL SDL_SetiOSEventPump(bool enabled);
#అయితే_ముగింపు
