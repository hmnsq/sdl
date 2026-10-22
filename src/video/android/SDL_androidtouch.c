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
#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#ضمن <android/log.h>

#ضمن "SDL_androidtouch.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_touch_c.h"
#ضمن "../../core/android/SDL_android.h"

#تعریف_کرو ACTION_تھلے 0
#تعریف_کرو ACTION_اتے   1
#تعریف_کرو ACTION_MOVE 2
#تعریف_کرو ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#تعریف_کرو ACTION_اشارہ_گر_تھلے 5
#تعریف_کرو ACTION_اشارہ_گر_اتے   6

فراغ Android_InitTouch(فراغ)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

فراغ Android_QuitTouch(فراغ)
{
}


SDL_TouchID Android_ConvertJavaTouchID(صحيح touchID)
{
    SDL_TouchID retval = touchID;

    إذا (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } وإلا {
        // Touch ID 0 is invalid
        retval += 1;
    }
    أرجع retval;
}

فراغ Android_OnTouch(SDL_کھڑکی *کھڑکی, صحيح touch_device_id_وچ, صحيح اشارہ_گر_finger_id_وچ, صحيح action, عائم x, عائم y, عائم p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    إذا (!کھڑکی) {
        أرجع;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_وچ);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(اشارہ_گر_finger_id_وچ + 1);

    إذا (SDL_جوڑو_Touch(touchDeviceId, SDL_TOUCH_DEVICE_سدھا, "") < 0) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_تھلے:
    حالة ACTION_اشارہ_گر_تھلے:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_تھلے, x, y, p);
        اكسر;

    حالة ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, کھڑکی, x, y, p);
        اكسر;

    حالة ACTION_اتے:
    حالة ACTION_اشارہ_گر_اتے:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_اتے, x, y, p);
        اكسر;

    حالة ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_CANCELED, x, y, p);
        اكسر;

    افتراضي:
        اكسر;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_ANDROID
