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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#شامل <android/log.h>

#شامل "SDL_androidtouch.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_touch_c.h"
#شامل "../../core/android/SDL_android.h"

#تعریف_کرو ACTION_نیچے_کو 0
#تعریف_کرو ACTION_اوپر   1
#تعریف_کرو ACTION_MOVE 2
#تعریف_کرو ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#تعریف_کرو ACTION_اشارہ_گر_نیچے_کو 5
#تعریف_کرو ACTION_اشارہ_گر_اوپر   6

خالی Android_InitTouch(خالی)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

خالی Android_QuitTouch(خالی)
{
}


SDL_TouchID Android_ConvertJavaTouchID(صحیح touchID)
{
    SDL_TouchID retval = touchID;

    اگر (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } ورنہ {
        // Touch ID 0 is invalid
        retval += 1;
    }
    واپس retval;
}

خالی Android_OnTouch(SDL_کھڑکی *کھڑکی, صحیح touch_device_id_اندر, صحیح اشارہ_گر_finger_id_اندر, صحیح action, اعشاری x, اعشاری y, اعشاری p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    اگر (!کھڑکی) {
        واپس;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_اندر);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(اشارہ_گر_finger_id_اندر + 1);

    اگر (SDL_جوڑو_Touch(touchDeviceId, SDL_TOUCH_DEVICE_براہ_راست, "") < 0) {
        واپس;
    }

    انتخاب (action) {
    حالت ACTION_نیچے_کو:
    حالت ACTION_اشارہ_گر_نیچے_کو:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_نیچے_کو, x, y, p);
        توڑو;

    حالت ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, کھڑکی, x, y, p);
        توڑو;

    حالت ACTION_اوپر:
    حالت ACTION_اشارہ_گر_اوپر:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_اوپر, x, y, p);
        توڑو;

    حالت ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, کھڑکی, SDL_EVENT_FINGER_CANCELED, x, y, p);
        توڑو;

    طےشدہ:
        توڑو;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID
