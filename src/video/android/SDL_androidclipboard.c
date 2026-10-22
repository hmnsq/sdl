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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID

#అన్తర్భావ "SDL_androidvideo.h"
#అన్తర్భావ "SDL_androidclipboard.h"
#అన్తర్భావ "../../core/android/SDL_android.h"

bool Android_సమితి_Clipboard_పాఠ్యం(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    తిరిగి Android_JNI_సమితి_Clipboard_పాఠ్యం(పాఠ్యం);
}

అక్షరం *Android_Get_Clipboard_పాఠ్యం(SDL_VideoDevice *_this)
{
    తిరిగి Android_JNI_Get_Clipboard_పాఠ్యం();
}

bool Android_Has_Clipboard_పాఠ్యం(SDL_VideoDevice *_this)
{
    తిరిగి Android_JNI_Has_Clipboard_పాఠ్యం();
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
