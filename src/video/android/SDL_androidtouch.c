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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ <android/log.h>

#ಅನ್ತರ್ಭಾವ "SDL_androidtouch.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಕೆಳಕ್ಕೆ 0
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಮೇಲೆ   1
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_MOVE 2
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಸೂಚಕ_ಕೆಳಕ್ಕೆ 5
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಸೂಚಕ_ಮೇಲೆ   6

ಶೂನ್ಯ Android_InitTouch(ಶೂನ್ಯ)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

ಶೂನ್ಯ Android_QuitTouch(ಶೂನ್ಯ)
{
}


SDL_TouchID Android_ConvertJavaTouchID(ಪೂರ್ಣಾಂಕ touchID)
{
    SDL_TouchID retval = touchID;

    ಆದರೆ (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Touch ID 0 is invalid
        retval += 1;
    }
    ಹಿಂತಿರುಗಿ retval;
}

ಶೂನ್ಯ Android_OnTouch(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ touch_device_id_ಒಳ, ಪೂರ್ಣಾಂಕ ಸೂಚಕ_finger_id_ಒಳ, ಪೂರ್ಣಾಂಕ action, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, ದಶಮಾಂಶ p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_ಒಳ);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(ಸೂಚಕ_finger_id_ಒಳ + 1);

    ಆದರೆ (SDL_ಕೂಡಿಸು_Touch(touchDeviceId, SDL_TOUCH_DEVICE_ನೇರ, "") < 0) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆಯ್ಕೆ (action) {
    ಸ್ಥಿತಿ ACTION_ಕೆಳಕ್ಕೆ:
    ಸ್ಥಿತಿ ACTION_ಸೂಚಕ_ಕೆಳಕ್ಕೆ:
        SDL_SendTouch(0, touchDeviceId, fingerId, ಕಿಟಕಿ, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, p);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, ಕಿಟಕಿ, x, y, p);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_ಮೇಲೆ:
    ಸ್ಥಿತಿ ACTION_ಸೂಚಕ_ಮೇಲೆ:
        SDL_SendTouch(0, touchDeviceId, fingerId, ಕಿಟಕಿ, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, p);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, ಕಿಟಕಿ, SDL_EVENT_FINGER_CANCELED, x, y, p);
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
