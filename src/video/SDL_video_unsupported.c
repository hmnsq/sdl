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
#समावेश "SDL_internal.h"

#समावेश "SDL_video_unsupported.h"

#अगर_अघोषित SDL_VIDEO_DRIVER_WINDOWS

#अगर defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(स्थिर अक्षर *name, Uint32 style, व्योम *hInst)
{
    (व्योम)name;
    (व्योम)style;
    (व्योम)hInst;
    वापस true;
}

व्योम SDL_UnregisterApp(व्योम)
{
}

व्योम SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, व्योम *userdata)
{
}

#पूर्ण_अगर // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णांक *adapter_सूचकांक, पूर्णांक *output_सूचकांक)
{
    (व्योम)displayID;
    (व्योम)adapter_सूचकांक;
    (व्योम)output_सूचकांक;
    वापस SDL_Unsupported();
}

पूर्णांक SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    (व्योम)displayID;
    SDL_Unsupported();
    वापस -1;
}

#या_अगर defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

पूर्णांक SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    (व्योम)displayID;
    SDL_Unsupported();
    वापस -1;
}

#पूर्ण_अगर // !SDL_VIDEO_DRIVER_WINDOWS

#अगर_अघोषित SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (व्योम)outTaskQueue;
    वापस SDL_Unsupported();
}

#पूर्ण_अगर

#अगर !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

व्योम SDL_OnApplicationDidChangeStatusBarOrientation(व्योम)
{
    SDL_Unsupported();
}

#पूर्ण_अगर

#अगर_अघोषित SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, पूर्णांक interval, SDL_iOSAnimationCallback callback, व्योम *callbackParam)
{
    (व्योम)window;
    (व्योम)interval;
    (व्योम)callback;
    (व्योम)callbackParam;
    वापस SDL_Unsupported();
}

व्योम SDL_SetiOSEventPump(bool enabled)
{
    (व्योम)enabled;
    SDL_Unsupported();
}
#पूर्ण_अगर

