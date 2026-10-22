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

بیرونی SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(ثابت نویسه *name, Uint32 style, تهی *hInst);
بیرونی SDL_DECLSPEC تهی SDLCALL SDL_UnregisterApp(تهی);
بیرونی SDL_DECLSPEC تهی SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, تهی *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

بیرونی SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, صحیح *adapterIndex, صحیح *outputIndex);
بیرونی SDL_DECLSPEC صحیح SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#وگرنهاگر defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

بیرونی SDL_DECLSPEC صحیح SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#اگر !defined(SDL_PLATFORM_GDK)

تعریفنوع ساختار XTaskQueueHandle XTaskQueueHandle;

بیرونی SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#اگر !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

بیرونی SDL_DECLSPEC تهی SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(تهی);

#endif

#اگر !defined(SDL_VIDEO_DRIVER_UIKIT)

تعریفنوع تهی (SDLCALL *SDL_iOSAnimationCallback)(تهی *userdata);

بیرونی SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, صحیح interval, SDL_iOSAnimationCallback callback, تهی *callbackParam);
بیرونی SDL_DECLSPEC تهی SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
