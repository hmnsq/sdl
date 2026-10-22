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

বাহ্যিক SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(ধ্রুবক অক্ষর *name, Uint32 style, শূন্য *hInst);
বাহ্যিক SDL_DECLSPEC শূন্য SDLCALL SDL_UnregisterApp(শূন্য);
বাহ্যিক SDL_DECLSPEC শূন্য SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, শূন্য *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

বাহ্যিক SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, পূর্ণসংখ্যা *adapter_সূচক, পূর্ণসংখ্যা *output_সূচক);
বাহ্যিক SDL_DECLSPEC পূর্ণসংখ্যা SDLCALL SDL_Get_Direct3_D9_Adapter_সূচক(SDL_DisplayID displayID);

#নতুবা_যদি defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

বাহ্যিক SDL_DECLSPEC পূর্ণসংখ্যা SDLCALL SDL_Get_Direct3_D9_Adapter_সূচক(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#যদি !defined(SDL_PLATFORM_GDK)

প্রকারলেখ কাঠামো XTaskQueueHandle XTaskQueueHandle;

বাহ্যিক SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#যদি !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

বাহ্যিক SDL_DECLSPEC শূন্য SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(শূন্য);

#endif

#যদি !defined(SDL_VIDEO_DRIVER_UIKIT)

প্রকারলেখ শূন্য (SDLCALL *SDL_iOSAnimationCallback)(শূন্য *userdata);

বাহ্যিক SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, পূর্ণসংখ্যা interval, SDL_iOSAnimationCallback callback, শূন্য *callbackParam);
বাহ্যিক SDL_DECLSPEC শূন্য SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
