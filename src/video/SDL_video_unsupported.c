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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_video_unsupported.h"

#ifndef SDL_VIDEO_DRIVER_WINDOWS

#यदि defined(SDL_PLATFORM_WINDOWS)

bool SDL_RegisterApp(अचर वर्ण *name, Uint32 style, शून्य *hInst)
{
    (शून्य)name;
    (शून्य)style;
    (शून्य)hInst;
    फर्काऊ true;
}

शून्य SDL_UnregisterApp(शून्य)
{
}

शून्य SDL_SetWindowsMessageHook(SDL_WindowsMessageHook callback, शून्य *userdata)
{
}

#endif // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णाङ्क *adapterIndex, पूर्णाङ्क *outputIndex)
{
    (शून्य)displayID;
    (शून्य)adapterIndex;
    (शून्य)outputIndex;
    फर्काऊ SDL_Unsupported();
}

पूर्णाङ्क SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (शून्य)displayID;
    SDL_Unsupported();
    फर्काऊ -1;
}

#अथवायदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

पूर्णाङ्क SDL_GetDirect3D9AdapterIndex(SDL_DisplayID displayID)
{
    (शून्य)displayID;
    SDL_Unsupported();
    फर्काऊ -1;
}

#endif // !SDL_VIDEO_DRIVER_WINDOWS

#ifndef SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *outTaskQueue)
{
    (शून्य)outTaskQueue;
    फर्काऊ SDL_Unsupported();
}

#endif

#यदि !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

शून्य SDL_OnApplicationDidChangeStatusBarOrientation(शून्य)
{
    SDL_Unsupported();
}

#endif

#ifndef SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_Window *window, पूर्णाङ्क interval, SDL_iOSAnimationCallback callback, शून्य *callbackParam)
{
    (शून्य)window;
    (शून्य)interval;
    (शून्य)callback;
    (शून्य)callbackParam;
    फर्काऊ SDL_Unsupported();
}

शून्य SDL_SetiOSEventPump(bool enabled)
{
    (शून्य)enabled;
    SDL_Unsupported();
}
#endif

