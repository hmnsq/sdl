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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव <android/log.h>

#अन्तर्भाव "SDL_androidtouch.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"
#अन्तर्भाव "../../core/android/SDL_android.h"

#परिभाषय ACTION_अधस्तात् 0
#परिभाषय ACTION_ऊर्ध्वम्   1
#परिभाषय ACTION_MOVE 2
#परिभाषय ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#परिभाषय ACTION_POINTER_अधस्तात् 5
#परिभाषय ACTION_POINTER_ऊर्ध्वम्   6

शून्य Android_InitTouch(शून्य)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

शून्य Android_QuitTouch(शून्य)
{
}


SDL_TouchID Android_ConvertJavaTouchID(पूर्णाङ्क touchID)
{
    SDL_TouchID retval = touchID;

    यदि (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } अन्यथा {
        // Touch ID 0 is invalid
        retval += 1;
    }
    प्रत्यागम retval;
}

शून्य Android_OnTouch(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क touch_device_id_अन्तर्, पूर्णाङ्क pointer_finger_id_अन्तर्, पूर्णाङ्क action, भिन्न x, भिन्न y, भिन्न p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    यदि (!गवाक्षः) {
        प्रत्यागम;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_अन्तर्);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(pointer_finger_id_अन्तर् + 1);

    यदि (SDL_सङ्कलय_Touch(touchDeviceId, SDL_TOUCH_DEVICE_प्रत्यक्षम्, "") < 0) {
        प्रत्यागम;
    }

    विकल्प (action) {
    पक्ष ACTION_अधस्तात्:
    पक्ष ACTION_POINTER_अधस्तात्:
        SDL_SendTouch(0, touchDeviceId, fingerId, गवाक्षः, SDL_EVENT_FINGER_अधस्तात्, x, y, p);
        भङ्ग;

    पक्ष ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, गवाक्षः, x, y, p);
        भङ्ग;

    पक्ष ACTION_ऊर्ध्वम्:
    पक्ष ACTION_POINTER_ऊर्ध्वम्:
        SDL_SendTouch(0, touchDeviceId, fingerId, गवाक्षः, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, p);
        भङ्ग;

    पक्ष ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, गवाक्षः, SDL_EVENT_FINGER_CANCELED, x, y, p);
        भङ्ग;

    स्वभाव:
        भङ्ग;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_ANDROID
