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

#ಯದಿ !defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಯದಿ defined(SDL_PLATFORM_WINDOWS)

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(ಧ್ರುವ ವರ್ಣ *name, Uint32 style, ಶೂನ್ಯ *hInst);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_UnregisterApp(ಶೂನ್ಯ);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ಶೂನ್ಯ *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ಪೂರ್ಣಾಙ್ಕ *adapterIndex, ಪೂರ್ಣಾಙ್ಕ *outputIndex);
ಬಾಹ್ಯ SDL_DECLSPEC ಪೂರ್ಣಾಙ್ಕ SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#ನೋಚೇದ್ಯದಿ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ಬಾಹ್ಯ SDL_DECLSPEC ಪೂರ್ಣಾಙ್ಕ SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#ಯದಿ !defined(SDL_PLATFORM_GDK)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XTaskQueueHandle XTaskQueueHandle;

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#ಯದಿ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(ಶೂನ್ಯ);

#endif

#ಯದಿ !defined(SDL_VIDEO_DRIVER_UIKIT)

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (SDLCALL *SDL_iOSAnimationCallback)(ಶೂನ್ಯ *userdata);

ಬಾಹ್ಯ SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ interval, SDL_iOSAnimationCallback callback, ಶೂನ್ಯ *callbackParam);
ಬಾಹ್ಯ SDL_DECLSPEC ಶೂನ್ಯ SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
