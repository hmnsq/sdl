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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

bool Android_ਸੈੱਟ_Clipboard_ਪਾਠ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    ਵਾਪਸ Android_JNI_ਸੈੱਟ_Clipboard_ਪਾਠ(ਪਾਠ);
}

ਅੱਖਰ *Android_Get_Clipboard_ਪਾਠ(SDL_VideoDevice *_this)
{
    ਵਾਪਸ Android_JNI_Get_Clipboard_ਪਾਠ();
}

bool Android_Has_Clipboard_ਪਾਠ(SDL_VideoDevice *_this)
{
    ਵਾਪਸ Android_JNI_Has_Clipboard_ਪਾਠ();
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID
