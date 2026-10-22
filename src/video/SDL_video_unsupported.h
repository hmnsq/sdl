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

#यदि !defined(SDL_VIDEO_DRIVER_WINDOWS)

#यदि defined(SDL_PLATFORM_WINDOWS)

बाह्य SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(अचर वर्ण *name, Uint32 style, शून्य *hInst);
बाह्य SDL_DECLSPEC शून्य SDLCALL SDL_UnregisterApp(शून्य);
बाह्य SDL_DECLSPEC शून्य SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, शून्य *userdata);

#endif /* SDL_PLATFORM_WINDOWS */

बाह्य SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णाङ्क *adapterIndex, पूर्णाङ्क *outputIndex);
बाह्य SDL_DECLSPEC पूर्णाङ्क SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#अथवायदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

बाह्य SDL_DECLSPEC पूर्णाङ्क SDLCALL SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID);

#endif /* !SDL_VIDEO_DRIVER_WINDOWS */

#यदि !defined(SDL_PLATFORM_GDK)

प्रकारनिर्देश संरचना XTaskQueueHandle XTaskQueueHandle;

बाह्य SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#endif /* !SDL_PLATFORM_GDK */

#यदि !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

बाह्य SDL_DECLSPEC शून्य SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(शून्य);

#endif

#यदि !defined(SDL_VIDEO_DRIVER_UIKIT)

प्रकारनिर्देश शून्य (SDLCALL *SDL_iOSAnimationCallback)(शून्य *userdata);

बाह्य SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, पूर्णाङ्क interval, SDL_iOSAnimationCallback callback, शून्य *callbackParam);
बाह्य SDL_DECLSPEC शून्य SDLCALL SDL_SetiOSEventPump(bool enabled);
#endif
