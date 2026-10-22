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

#అన్తర్భావ "SDL_androidmouse.h"

#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#నిర్వచించు ACTION_కిందికి           0
#నిర్వచించు ACTION_పైకి             1
#నిర్వచించు ACTION_MOVE           2
#నిర్వచించు ACTION_CANCEL         3
#నిర్వచించు ACTION_HOVER_MOVE     7
#నిర్వచించు ACTION_SCROLL         8
#నిర్వచించు ACTION_HOVER_ENTER    9
#నిర్వచించు ACTION_HOVER_EXIT     10
#నిర్వచించు ACTION_BUTTON_PRESS   11
#నిర్వచించు ACTION_BUTTON_RELEASE 12

#నిర్వచించు BUTTON_PRIMARY        1
#నిర్వచించు BUTTON_SECONDARY      2
#నిర్వచించు BUTTON_TERTIARY       4
#నిర్వచించు BUTTON_వెనుక           8
#నిర్వచించు BUTTON_FORWARD        16

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    పూర్ణాంకం custom_cursor;
    పూర్ణాంకం system_cursor;
};

స్థిర స్థిరరాశి అక్షరం k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_వెనుక, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
స్థిర పూర్ణాంకం చివరి_state;

// Blank cursor
స్థిర SDL_Cursor *ఖాళీలు_cursor;

స్థిర SDL_Cursor *Android_WrapCursor(పూర్ణాంకం custom_cursor, పూర్ణాంకం system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
        ఒకవేళ (దత్తాంశం) {
            దత్తాంశం->custom_cursor = custom_cursor;
            దత్తాంశం->system_cursor = system_cursor;
            cursor->అంతర్గత = దత్తాంశం;
        } లేకపోతే {
            SDL_free(cursor);
            cursor = ఖాళీ;
        }
    }

    తిరిగి cursor;
}

స్థిర SDL_Cursor *Android_CreateDefaultCursor(శూన్య)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    తిరిగి Android_WrapCursor(0, id);
}

స్థిర SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    పూర్ణాంకం custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ఒకవేళ (!converted) {
        తిరిగి ఖాళీ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ఒకవేళ (!custom_cursor) {
        SDL_Unsupported();
        తిరిగి ఖాళీ;
    }
    తిరిగి Android_WrapCursor(custom_cursor, 0);
}

స్థిర SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    తిరిగి Android_WrapCursor(0, id);
}

స్థిర శూన్య Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;
    ఒకవేళ (దత్తాంశం->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(దత్తాంశం->custom_cursor);
    }
    SDL_free(cursor->అంతర్గత);
    SDL_free(cursor);
}

స్థిర SDL_Cursor *Android_Create_ఖాళీలు_Cursor(శూన్య)
{
    ఒకవేళ (!ఖాళీలు_cursor) {
        SDL_Surface *ఖాళీలు_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (ఖాళీలు_surface) {
            ఖాళీలు_cursor = Android_CreateCursor(ఖాళీలు_surface, 0, 0);
            SDL_DestroySurface(ఖాళీలు_surface);
        }
    }
    తిరిగి ఖాళీలు_cursor;
}

స్థిర శూన్య Android_Destroy_ఖాళీలు_Cursor(శూన్య)
{
    ఒకవేళ (ఖాళీలు_cursor) {
        Android_FreeCursor(ఖాళీలు_cursor);
        ఖాళీలు_cursor = ఖాళీ;
    }
}

స్థిర bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ఒకవేళ (!cursor) {
        cursor = Android_Create_ఖాళీలు_Cursor();
    }
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;
        ఒకవేళ (దత్తాంశం->custom_cursor) {
            ఒకవేళ (!Android_JNI_సమితి_Custom_Cursor(దత్తాంశం->custom_cursor)) {
                తిరిగి SDL_Unsupported();
            }
        } లేకపోతే {
            ఒకవేళ (!Android_JNI_సమితి_System_Cursor(దత్తాంశం->system_cursor)) {
                తిరిగి SDL_Unsupported();
            }
        }
        తిరిగి true;
    } లేకపోతే {
        // SDL error set inside Android_CreateEmptyCursor()
        తిరిగి false;
    }
}

స్థిర bool Android_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    ఒకవేళ (!Android_JNI_SupportsRelativeMouse()) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (!Android_JNI_సమితి_Relative_Mouse_Enabled(enabled)) {
        తిరిగి SDL_Unsupported();
    }

    తిరిగి true;
}

శూన్య Android_InitMouse(శూన్య)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Android_CreateCursor;
    mouse->CreateSystemCursor = Android_CreateSystemCursor;
    mouse->ShowCursor = Android_ShowCursor;
    mouse->FreeCursor = Android_FreeCursor;
    mouse->సమితి_Relative_Mouse_బహుళకం = Android_సమితి_Relative_Mouse_బహుళకం;

    SDL_సమితి_Default_Cursor(Android_CreateDefaultCursor());

    చివరి_state = 0;
}

శూన్య Android_QuitMouse(శూన్య)
{
    Android_Destroy_ఖాళీలు_Cursor();
}

// Translate Android mouse button state to SDL mouse button
స్థిర Uint8 TranslateButton(పూర్ణాంకం state)
{
    ఒకవేళ (state & BUTTON_PRIMARY) {
        తిరిగి SDL_BUTTON_ఎడమ;
    } లేకపోతే ఒకవేళ (state & BUTTON_SECONDARY) {
        తిరిగి SDL_BUTTON_కుడి;
    } లేకపోతే ఒకవేళ (state & BUTTON_TERTIARY) {
        తిరిగి SDL_BUTTON_మధ్య;
    } లేకపోతే ఒకవేళ (state & BUTTON_FORWARD) {
        తిరిగి SDL_BUTTON_X1;
    } లేకపోతే ఒకవేళ (state & BUTTON_వెనుక) {
        తిరిగి SDL_BUTTON_X2;
    } లేకపోతే {
        తిరిగి 0;
    }
}

శూన్య Android_OnMouse(SDL_కిటికీ *కిటికీ, పూర్ణాంకం state, పూర్ణాంకం action, దశాంశం x, దశాంశం y, bool relative)
{
    పూర్ణాంకం changes_press;
    పూర్ణాంకం changes_release;
    Uint8 button;

    ఒకవేళ (!కిటికీ) {
        తిరిగి;
    }

    ఎంపిక (action) {
    స్థితి ACTION_MOVE:
    స్థితి ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, కిటికీ, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ఆపు;

    స్థితి ACTION_SCROLL:
        SDL_SendMouseWheel(0, కిటికీ, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_సాధారణ);
        ఆపు;

    స్థితి ACTION_పైకి:
    స్థితి ACTION_కిందికి:
    స్థితి ACTION_BUTTON_PRESS:
    స్థితి ACTION_BUTTON_RELEASE:
    స్థితి ACTION_HOVER_ENTER:
    స్థితి ACTION_HOVER_EXIT:
        // Some Android versions will send mouse buttons as ACTION_BUTTON_PRESS and 
        // ACTION_BUTTON_RELEASE. Some will use ACTION_DOWN and ACTION_UP.
        //
        // Some will send ACTION_HOVER_EXIT when a button is pressed (to go into 
        // drag/move mode) and ACTION_HOVER_ENTER when the button is released (to 
        // go back into hover mode).
        //
        // Some will, in fact, cluster a BUTTON_PRIMARY release and BUTTON_SECONDARY 
        // press into the same message, simply changing the button state.
        //
        // To ensure we work correctly on as many Android variants as possible, we
        // take the button state on any of these and generate press/release events
        // ourselves as needed when the button state changes.

        changes_press = state & ~చివరి_state;
        changes_release = చివరి_state & ~state;

        SDL_SendMouseMotion(0, కిటికీ, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        ఒకవేళ (changes_press) {
            కొరకు (పూర్ణాంకం i = 0; i < పరిమాణం(k_aAndroidButtons); i++) {
                ఒకవేళ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, కిటికీ, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            చివరి_state = state;
        }

        ఒకవేళ (changes_release) {
            కొరకు (పూర్ణాంకం i = 0; i < పరిమాణం(k_aAndroidButtons); i++) {
                ఒకవేళ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, కిటికీ, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            చివరి_state = state;
        }
        ఆపు;        

    అప్రమేయ:
        ఆపు;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
