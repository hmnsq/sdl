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

#ਅਨ੍ਤਰ੍ਭਾਵ <android/log.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidtouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਥੱਲੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਉੱਪਰ   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_MOVE 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਸੂਚਕ_ਥੱਲੇ 5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਸੂਚਕ_ਉੱਪਰ   6

ਖਾਲੀ Android_InitTouch(ਖਾਲੀ)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

ਖਾਲੀ Android_QuitTouch(ਖਾਲੀ)
{
}


SDL_TouchID Android_ConvertJavaTouchID(ਪੂਰਨ touchID)
{
    SDL_TouchID retval = touchID;

    ਜੇ (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } ਨਹੀਂਤਾਂ {
        // Touch ID 0 is invalid
        retval += 1;
    }
    ਵਾਪਸ retval;
}

ਖਾਲੀ Android_OnTouch(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ touch_device_id_ਵਿੱਚ, ਪੂਰਨ ਸੂਚਕ_finger_id_ਵਿੱਚ, ਪੂਰਨ action, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, ਦਸ਼ਮਲਵ p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_ਵਿੱਚ);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(ਸੂਚਕ_finger_id_ਵਿੱਚ + 1);

    ਜੇ (SDL_ਜੋੜੋ_Touch(touchDeviceId, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, "") < 0) {
        ਵਾਪਸ;
    }

    ਚੋਣ (action) {
    ਹਾਲਤ ACTION_ਥੱਲੇ:
    ਹਾਲਤ ACTION_ਸੂਚਕ_ਥੱਲੇ:
        SDL_SendTouch(0, touchDeviceId, fingerId, ਖਿੜਕੀ, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, p);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, ਖਿੜਕੀ, x, y, p);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_ਉੱਪਰ:
    ਹਾਲਤ ACTION_ਸੂਚਕ_ਉੱਪਰ:
        SDL_SendTouch(0, touchDeviceId, fingerId, ਖਿੜਕੀ, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, p);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, ਖਿੜਕੀ, SDL_EVENT_FINGER_CANCELED, x, y, p);
        ਰੋਕੋ;

    ਮੂਲ:
        ਰੋਕੋ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID
