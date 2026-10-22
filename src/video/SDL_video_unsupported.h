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

#ಆದರೆ !defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಆದರೆ defined(SDL_PLATFORM_WINDOWS)

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_ರಿಜಿಸ್ಟರ್_App(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, Uint32 style, ಶೂನ್ಯ *hInst);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_UnregisterApp(ಶೂನ್ಯ);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_ಗಣ_Windows_ಸಂದೇಶ_Hook(SDL_Windows_ಸಂದೇಶ_Hook callback, ಶೂನ್ಯ *userdata);

#ಆದರೆ_ಅಂತ್ಯ /* SDL_PLATFORM_WINDOWS */

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ಪೂರ್ಣಾಂಕ *adapter_ಸೂಚ್ಯಂಕ, ಪೂರ್ಣಾಂಕ *output_ಸೂಚ್ಯಂಕ);
ಬಾಹ್ಯ SDL_DECLSPEC ಪೂರ್ಣಾಂಕ SDLCALL SDL_Get_Direct3_D9_Adapter_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID);

#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ಬಾಹ್ಯ SDL_DECLSPEC ಪೂರ್ಣಾಂಕ SDLCALL SDL_Get_Direct3_D9_Adapter_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID);

#ಆದರೆ_ಅಂತ್ಯ /* !SDL_VIDEO_DRIVER_WINDOWS */

#ಆದರೆ !defined(SDL_PLATFORM_GDK)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XTask_ಸರತಿ_Handle XTask_ಸರತಿ_Handle;

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_Get_GDKTask_ಸರತಿ(XTask_ಸರತಿ_Handle *ಹೊರಹೋಗು_Task_ಸರತಿ);

#ಆದರೆ_ಅಂತ್ಯ /* !SDL_PLATFORM_GDK */

#ಆದರೆ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_On_Application_Did_Change_ಸ್ಥಿತಿ_Bar_Orientation(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_VIDEO_DRIVER_UIKIT)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (SDLCALL *SDL_iOSAnimationCallback)(ಶೂನ್ಯ *userdata);

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ interval, SDL_iOSAnimationCallback callback, ಶೂನ್ಯ *callbackParam);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_SetiOSEventPump(bool enabled);
#ಆದರೆ_ಅಂತ್ಯ
