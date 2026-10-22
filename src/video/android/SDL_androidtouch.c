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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID

#समावेश <android/log.h>

#समावेश "SDL_androidtouch.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_touch_c.h"
#समावेश "../../core/android/SDL_android.h"

#घोषणा ACTION_DOWN 0
#घोषणा ACTION_UP   1
#घोषणा ACTION_MOVE 2
#घोषणा ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#घोषणा ACTION_POINTER_DOWN 5
#घोषणा ACTION_POINTER_UP   6

व्योम Android_InitTouch(व्योम)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

व्योम Android_QuitTouch(व्योम)
{
}


SDL_TouchID Android_ConvertJavaTouchID(पूर्णांक touchID)
{
    SDL_TouchID retval = touchID;

    अगर (touchID < 0) {
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
    वापस retval;
}

व्योम Android_OnTouch(SDL_Window *window, पूर्णांक touch_device_id_in, पूर्णांक pointer_finger_id_in, पूर्णांक action, भग्न x, भग्न y, भग्न p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    अगर (!window) {
        वापस;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_in);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(pointer_finger_id_in + 1);

    अगर (SDL_AddTouch(touchDeviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        वापस;
    }

    चयन (action) {
    हाल ACTION_DOWN:
    हाल ACTION_POINTER_DOWN:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_DOWN, x, y, p);
        अवरोध;

    हाल ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, window, x, y, p);
        अवरोध;

    हाल ACTION_UP:
    हाल ACTION_POINTER_UP:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_UP, x, y, p);
        अवरोध;

    हाल ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, window, SDL_EVENT_FINGER_CANCELED, x, y, p);
        अवरोध;

    शेष:
        अवरोध;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_ANDROID
