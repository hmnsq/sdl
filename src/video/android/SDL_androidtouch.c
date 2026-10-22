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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#അന്തര്ഭാവ <android/log.h>

#അന്തര്ഭാവ "SDL_androidtouch.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"
#അന്തര്ഭാവ "../../core/android/SDL_android.h"

#define ACTION_DOWN 0
#define ACTION_UP   1
#define ACTION_MOVE 2
#define ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#define ACTION_POINTER_DOWN 5
#define ACTION_POINTER_UP   6

ശൂന്യം Android_InitTouch(ശൂന്യം)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

ശൂന്യം Android_QuitTouch(ശൂന്യം)
{
}


SDL_TouchID Android_ConvertJavaTouchID(പൂർണ്ണസംഖ്യ touchID)
{
    SDL_TouchID retval = touchID;

    എങ്കിൽ (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } അല്ലെങ്കിൽ {
        // Touch ID 0 is invalid
        retval += 1;
    }
    തിരികെ retval;
}

ശൂന്യം Android_OnTouch(SDL_Window *window, പൂർണ്ണസംഖ്യ touch_device_id_in, പൂർണ്ണസംഖ്യ pointer_finger_id_in, പൂർണ്ണസംഖ്യ action, ദശാംശം x, ദശാംശം y, ദശാംശം p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    എങ്കിൽ (!window) {
        തിരികെ;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_in);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(pointer_finger_id_in + 1);

    എങ്കിൽ (SDL_AddTouch(touchDeviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        തിരികെ;
    }

    തിരഞ്ഞെടുപ്പ് (action) {
    അവസ്ഥ ACTION_DOWN:
    അവസ്ഥ ACTION_POINTER_DOWN:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_DOWN, x, y, p);
        നിർത്തുക;

    അവസ്ഥ ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, window, x, y, p);
        നിർത്തുക;

    അവസ്ഥ ACTION_UP:
    അവസ്ഥ ACTION_POINTER_UP:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_UP, x, y, p);
        നിർത്തുക;

    അവസ്ഥ ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_CANCELED, x, y, p);
        നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
