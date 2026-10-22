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

#అన్తర్భావ <android/log.h>

#అన్తర్భావ "SDL_androidtouch.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"
#అన్తర్భావ "../../core/android/SDL_android.h"

#నిర్వచించు ACTION_కిందికి 0
#నిర్వచించు ACTION_పైకి   1
#నిర్వచించు ACTION_MOVE 2
#నిర్వచించు ACTION_CANCEL 3
// #define ACTION_OUTSIDE 4
#నిర్వచించు ACTION_సూచిక_కిందికి 5
#నిర్వచించు ACTION_సూచిక_పైకి   6

శూన్య Android_InitTouch(శూన్య)
{
    // Add all touch devices
    Android_JNI_InitTouch();
}

శూన్య Android_QuitTouch(శూన్య)
{
}


SDL_TouchID Android_ConvertJavaTouchID(పూర్ణాంకం touchID)
{
    SDL_TouchID retval = touchID;

    ఒకవేళ (touchID < 0) {
        // Touch ID -1 appears when using Android emulator, eg:
        //  adb shell input mouse tap 100 100
        //  adb shell input touchscreen tap 100 100
        //
        // Prevent the values -1 and -2, since they're used in SDL internal for synthetic events:
        retval -= 2;
    } లేకపోతే {
        // Touch ID 0 is invalid
        retval += 1;
    }
    తిరిగి retval;
}

శూన్య Android_OnTouch(SDL_కిటికీ *కిటికీ, పూర్ణాంకం touch_device_id_లోపల, పూర్ణాంకం సూచిక_finger_id_లోపల, పూర్ణాంకం action, దశాంశం x, దశాంశం y, దశాంశం p)
{
    SDL_TouchID touchDeviceId = 0;
    SDL_FingerID fingerId = 0;

    ఒకవేళ (!కిటికీ) {
        తిరిగి;
    }

    touchDeviceId = Android_ConvertJavaTouchID(touch_device_id_లోపల);

    // Finger ID should be greater than 0
    fingerId = (SDL_FingerID)(సూచిక_finger_id_లోపల + 1);

    ఒకవేళ (SDL_కూడు_Touch(touchDeviceId, SDL_TOUCH_DEVICE_ప్రత్యక్ష, "") < 0) {
        తిరిగి;
    }

    ఎంపిక (action) {
    స్థితి ACTION_కిందికి:
    స్థితి ACTION_సూచిక_కిందికి:
        SDL_SendTouch(0, touchDeviceId, fingerId, కిటికీ, SDL_EVENT_FINGER_కిందికి, x, y, p);
        ఆపు;

    స్థితి ACTION_MOVE:
        SDL_SendTouchMotion(0, touchDeviceId, fingerId, కిటికీ, x, y, p);
        ఆపు;

    స్థితి ACTION_పైకి:
    స్థితి ACTION_సూచిక_పైకి:
        SDL_SendTouch(0, touchDeviceId, fingerId, కిటికీ, SDL_EVENT_FINGER_పైకి, x, y, p);
        ఆపు;

    స్థితి ACTION_CANCEL:
        SDL_SendTouch(0, touchDeviceId, fingerId, కిటికీ, SDL_EVENT_FINGER_CANCELED, x, y, p);
        ఆపు;

    అప్రమేయ:
        ఆపు;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
