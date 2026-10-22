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

#જો !defined(SDL_VIDEO_DRIVER_WINDOWS)

#જો defined(SDL_PLATFORM_WINDOWS)

બાહ્ય SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(અચલ અક્ષર *name, Uint32 style, શૂન્ય *hInst);
બાહ્ય SDL_DECLSPEC શૂન્ય SDLCALL SDL_UnregisterApp(શૂન્ય);
બાહ્ય SDL_DECLSPEC શૂન્ય SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, શૂન્ય *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

બાહ્ય SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, પૂર્ણાંક *adapterIndex, પૂર્ણાંક *outputIndex);
બાહ્ય SDL_DECLSPEC પૂર્ણાંક SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#અથવાજો defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

બાહ્ય SDL_DECLSPEC પૂર્ણાંક SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#જો !defined(SDL_PLATFORM_GDK)

પ્રકારવ્યાખ્યા સંરચના XTaskQueueHandle XTaskQueueHandle;

બાહ્ય SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#જો !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

બાહ્ય SDL_DECLSPEC શૂન્ય SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(શૂન્ય);

#endif

#જો !defined(SDL_VIDEO_DRIVER_UIKIT)

પ્રકારવ્યાખ્યા શૂન્ય (SDLCALL *SDL_iOSAnimationCallback)(શૂન્ય *userdata);

બાહ્ય SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, પૂર્ણાંક interval, SDL_iOSAnimationCallback callback, શૂન્ય *callbackParam);
બાહ્ય SDL_DECLSPEC શૂન્ય SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
