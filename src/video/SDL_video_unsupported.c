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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_video_unsupported.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_DRIVER_WINDOWS

#ಆದರೆ defined(SDL_PLATFORM_WINDOWS)

bool SDL_ರಿಜಿಸ್ಟರ್_App(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, Uint32 style, ಶೂನ್ಯ *hInst)
{
    (ಶೂನ್ಯ)name;
    (ಶೂನ್ಯ)style;
    (ಶೂನ್ಯ)hInst;
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_UnregisterApp(ಶೂನ್ಯ)
{
}

ಶೂನ್ಯ SDL_ಗಣ_Windows_ಸಂದೇಶ_Hook(SDL_Windows_ಸಂದೇಶ_Hook callback, ಶೂನ್ಯ *userdata)
{
}

#ಆದರೆ_ಅಂತ್ಯ // defined(SDL_PLATFORM_WINDOWS)

bool SDL_GetDXGIOutputInfo(SDL_DisplayID displayID, ಪೂರ್ಣಾಂಕ *adapter_ಸೂಚ್ಯಂಕ, ಪೂರ್ಣಾಂಕ *output_ಸೂಚ್ಯಂಕ)
{
    (ಶೂನ್ಯ)displayID;
    (ಶೂನ್ಯ)adapter_ಸೂಚ್ಯಂಕ;
    (ಶೂನ್ಯ)output_ಸೂಚ್ಯಂಕ;
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ಪೂರ್ಣಾಂಕ SDL_Get_Direct3_D9_Adapter_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID)
{
    (ಶೂನ್ಯ)displayID;
    SDL_Unsupported();
    ಹಿಂತಿರುಗಿ -1;
}

#ಅಥವಾಆದರೆ defined(SDL_PLATFORM_XBOXONE) || defined(SDL_PLATFORM_XBOXSERIES)

ಪೂರ್ಣಾಂಕ SDL_Get_Direct3_D9_Adapter_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID)
{
    (ಶೂನ್ಯ)displayID;
    SDL_Unsupported();
    ಹಿಂತಿರುಗಿ -1;
}

#ಆದರೆ_ಅಂತ್ಯ // !SDL_VIDEO_DRIVER_WINDOWS

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_GDK

bool SDL_Get_GDKTask_ಸರತಿ(XTask_ಸರತಿ_Handle *ಹೊರಹೋಗು_Task_ಸರತಿ)
{
    (ಶೂನ್ಯ)ಹೊರಹೋಗು_Task_ಸರತಿ;
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(SDL_PLATFORM_IOS) || defined(SDL_PLATFORM_TVOS) || defined(SDL_PLATFORM_VISIONOS)

ಶೂನ್ಯ SDL_On_Application_Did_Change_ಸ್ಥಿತಿ_Bar_Orientation(ಶೂನ್ಯ)
{
    SDL_Unsupported();
}

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_DRIVER_UIKIT

bool SDL_SetiOSAnimationCallback(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ interval, SDL_iOSAnimationCallback callback, ಶೂನ್ಯ *callbackParam)
{
    (ಶೂನ್ಯ)ಕಿಟಕಿ;
    (ಶೂನ್ಯ)interval;
    (ಶೂನ್ಯ)callback;
    (ಶೂನ್ಯ)callbackParam;
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ಶೂನ್ಯ SDL_SetiOSEventPump(bool enabled)
{
    (ಶೂನ್ಯ)enabled;
    SDL_Unsupported();
}
#ಆದರೆ_ಅಂತ್ಯ

