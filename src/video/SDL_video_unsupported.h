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

#अगर !defined(SDL_VIDEO_DRIVER_WINDOWS)

#अगर defined(SDL_PLATFORM_WINDOWS)

बाह्य SDL_DECLSPEC bool SDLCALL SDL_RegisterApp(स्थिर अक्षर *name, Uint32 style, व्योम *hInst);
बाह्य SDL_DECLSPEC व्योम SDLCALL SDL_UnregisterApp(व्योम);
बाह्य SDL_DECLSPEC व्योम SDLCALL SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, व्योम *userdata);

#पूर्ण_अगर /* SDL_PLATFORM_WINDOWS */

बाह्य SDL_DECLSPEC bool SDLCALL SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णांक *adapter_सूचकांक, पूर्णांक *output_सूचकांक);
बाह्य SDL_DECLSPEC पूर्णांक SDLCALL SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID);

#या_अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

बाह्य SDL_DECLSPEC पूर्णांक SDLCALL SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID);

#पूर्ण_अगर /* !SDL_VIDEO_DRIVER_WINDOWS */

#अगर !defined(SDL_PLATFORM_GDK)

प्रकार काष्ठा XTaskQueueHandle XTaskQueueHandle;

बाह्य SDL_DECLSPEC bool SDLCALL SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue);

#पूर्ण_अगर /* !SDL_PLATFORM_GDK */

#अगर !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

बाह्य SDL_DECLSPEC व्योम SDLCALL SDL_OnApplicationDidChangeStatusBarOrientation(व्योम);

#पूर्ण_अगर

#अगर !defined(SDL_VIDEO_DRIVER_UIKIT)

प्रकार व्योम (SDLCALL *SDL_iOSAnimationCallback)(व्योम *userdata);

बाह्य SDL_DECLSPEC bool SDLCALL SDL_SetiOSAnimationCallback(SDL_Window *window, पूर्णांक interval, SDL_iOSAnimationCallback callback, व्योम *callbackParam);
बाह्य SDL_DECLSPEC व्योम SDLCALL SDL_SetiOSEventPump(bool enabled);
#पूर्ण_अगर
