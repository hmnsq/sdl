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

#எனில் !defined(SDL_VIDEO_DRIVER_WINDOWS)

#எனில் defined(SDL_PLATFORM_WINDOWS)

வெளி SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(மாறிலி எழுத்து *name, Uint32 style, வெறுமை *hInst);
வெளி SDL_DECLSPEC வெறுமை SDLCALL SDL_UnregisterApp(வெறுமை);
வெளி SDL_DECLSPEC வெறுமை SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, வெறுமை *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

வெளி SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, முழு *adapterIndex, முழு *outputIndex);
வெளி SDL_DECLSPEC முழு SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#அல்லதெனில் defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

வெளி SDL_DECLSPEC முழு SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#எனில் !defined(SDL_PLATFORM_GDK)

வகைவரை கட்டமைப்பு XTaskQueueHandle XTaskQueueHandle;

வெளி SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#எனில் !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

வெளி SDL_DECLSPEC வெறுமை SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(வெறுமை);

#endif

#எனில் !defined(SDL_VIDEO_DRIVER_UIKIT)

வகைவரை வெறுமை (SDLCALL *SDL_iOSAnimationCallback)(வெறுமை *userdata);

வெளி SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, முழு interval, SDL_iOSAnimationCallback callback, வெறுமை *callbackParam);
வெளி SDL_DECLSPEC வெறுமை SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
