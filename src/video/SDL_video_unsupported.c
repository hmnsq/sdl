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

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_WINDOWS

#यदि defined(SDL_PLATFORM_WINDOWS)

bool SDL_पञ्जिकाकोशः_App(ध्रुव वर्ण *name, Uint32 style, शून्य *hInst)
{
    (शून्य)name;
    (शून्य)style;
    (शून्य)hInst;
    प्रत्यागम true;
}

शून्य SDL_UnregisterApp(शून्य)
{
}

शून्य SDL_समुच्चयः_Windows_सन्देशः_Hook(SDL_Windows_सन्देशः_Hook callback, शून्य *userdata)
{
}

#यदि_अन्तः // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, पूर्णाङ्क *adapter_सूचकांक, पूर्णाङ्क *output_सूचकांक)
{
    (शून्य)displayID;
    (शून्य)adapter_सूचकांक;
    (शून्य)output_सूचकांक;
    प्रत्यागम SDL_Unsupported();
}

पूर्णाङ्क SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    (शून्य)displayID;
    SDL_Unsupported();
    प्रत्यागम -1;
}

#नोचेद्यदि defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

पूर्णाङ्क SDL_Get_Direct3_D9_Adapter_सूचकांक(SDL_DisplayID displayID)
{
    (शून्य)displayID;
    SDL_Unsupported();
    प्रत्यागम -1;
}

#यदि_अन्तः // !SDL_VIDEO_DRIVER_WINDOWS

#यदि_अपरिभाषितम् SDL_PLATFORM_GDK

bool SDL_GetGDKTaskQueue(XTaskQueueHandle *बहिर्गमनम्_Task_Queue)
{
    (शून्य)बहिर्गमनम्_Task_Queue;
    प्रत्यागम SDL_Unsupported();
}

#यदि_अन्तः

#यदि !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

शून्य SDL_On_Application_Did_Change_स्थितिः_Bar_Orientation(शून्य)
{
    SDL_Unsupported();
}

#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क interval, SDL_iOSAnimationCallback callback, शून्य *callbackParam)
{
    (शून्य)गवाक्षः;
    (शून्य)interval;
    (शून्य)callback;
    (शून्य)callbackParam;
    प्रत्यागम SDL_Unsupported();
}

शून्य SDL_SetiOSEventPump(bool enabled)
{
    (शून्य)enabled;
    SDL_Unsupported();
}
#यदि_अन्तः

