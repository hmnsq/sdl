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

#എങ്കിൽ !defined(SDL_VIDEO_DRIVER_WINDOWS)

#എങ്കിൽ defined(SDL_PLATFORM_WINDOWS)

ബാഹ്യ SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(സ്ഥിരം അക്ഷരം *name, Uint32 style, ശൂന്യം *hInst);
ബാഹ്യ SDL_DECLSPEC ശൂന്യം SDLCALL SDL_UnregisterApp(ശൂന്യം);
ബാഹ്യ SDL_DECLSPEC ശൂന്യം SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, ശൂന്യം *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

ബാഹ്യ SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, പൂർണ്ണസംഖ്യ *adapterIndex, പൂർണ്ണസംഖ്യ *outputIndex);
ബാഹ്യ SDL_DECLSPEC പൂർണ്ണസംഖ്യ SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#അല്ലെങ്കിലെങ്കിൽ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ബാഹ്യ SDL_DECLSPEC പൂർണ്ണസംഖ്യ SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#എങ്കിൽ !defined(SDL_PLATFORM_GDK)

തരനിർവചനം ഘടന XTaskQueueHandle XTaskQueueHandle;

ബാഹ്യ SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#എങ്കിൽ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ബാഹ്യ SDL_DECLSPEC ശൂന്യം SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(ശൂന്യം);

#endif

#എങ്കിൽ !defined(SDL_VIDEO_DRIVER_UIKIT)

തരനിർവചനം ശൂന്യം (SDLCALL *SDL_iOSAnimationCallback)(ശൂന്യം *userdata);

ബാഹ്യ SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, പൂർണ്ണസംഖ്യ interval, SDL_iOSAnimationCallback callback, ശൂന്യം *callbackParam);
ബാഹ്യ SDL_DECLSPEC ശൂന്യം SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
