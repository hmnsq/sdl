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

#যদি !defined(SDL_VIDEO_DRIVER_WINDOWS)

#যদি defined(SDL_PLATFORM_WINDOWS)

বাহ্য SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(ধ্রুব বর্ণ *name, Uint32 style, শূন্য *hInst);
বাহ্য SDL_DECLSPEC শূন্য SDLCALL SDL_UnregisterApp(শূন্য);
বাহ্য SDL_DECLSPEC শূন্য SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, শূন্য *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

বাহ্য SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, পূর্ণাঙ্ক *adapterIndex, পূর্ণাঙ্ক *outputIndex);
বাহ্য SDL_DECLSPEC পূর্ণাঙ্ক SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#নোচেদ্যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

বাহ্য SDL_DECLSPEC পূর্ণাঙ্ক SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#যদি !defined(SDL_PLATFORM_GDK)

প্রকারনির্দেশ সংরচনা XTaskQueueHandle XTaskQueueHandle;

বাহ্য SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#যদি !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

বাহ্য SDL_DECLSPEC শূন্য SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(শূন্য);

#endif

#যদি !defined(SDL_VIDEO_DRIVER_UIKIT)

প্রকারনির্দেশ শূন্য (SDLCALL *SDL_iOSAnimationCallback)(শূন্য *userdata);

বাহ্য SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, পূর্ণাঙ্ক interval, SDL_iOSAnimationCallback callback, শূন্য *callbackParam);
বাহ্য SDL_DECLSPEC শূন্য SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
