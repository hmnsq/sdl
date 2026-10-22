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

#ଯଦି !defined(SDL_VIDEO_DRIVER_WINDOWS)

#ଯଦି defined(SDL_PLATFORM_WINDOWS)

ବାହ୍ୟ SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(ଅଚଳ ଅକ୍ଷର *name, Uint32 style, ଶୂନ୍ୟ *hInst);
ବାହ୍ୟ SDL_DECLSPEC ଶୂନ୍ୟ SDLCALL SDL_UnregisterApp(ଶୂନ୍ୟ);
ବାହ୍ୟ SDL_DECLSPEC ଶୂନ୍ୟ SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ଶୂନ୍ୟ *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

ବାହ୍ୟ SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *adapterIndex, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *outputIndex);
ବାହ୍ୟ SDL_DECLSPEC ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#ନଚେତଯଦି defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ବାହ୍ୟ SDL_DECLSPEC ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#ଯଦି !defined(SDL_PLATFORM_GDK)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା XTaskQueueHandle XTaskQueueHandle;

ବାହ୍ୟ SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#ଯଦି !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ବାହ୍ୟ SDL_DECLSPEC ଶୂନ୍ୟ SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(ଶୂନ୍ୟ);

#endif

#ଯଦି !defined(SDL_VIDEO_DRIVER_UIKIT)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (SDLCALL *SDL_iOSAnimationCallback)(ଶୂନ୍ୟ *userdata);

ବାହ୍ୟ SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval, SDL_iOSAnimationCallback callback, ଶୂନ୍ୟ *callbackParam);
ବାହ୍ୟ SDL_DECLSPEC ଶୂନ୍ୟ SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
