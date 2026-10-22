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

#अन्तर्भाव "SDL_androidmouse.h"

#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#परिभाषय ACTION_अधस्तात्           0
#परिभाषय ACTION_ऊर्ध्वम्             1
#परिभाषय ACTION_MOVE           2
#परिभाषय ACTION_CANCEL         3
#परिभाषय ACTION_HOVER_MOVE     7
#परिभाषय ACTION_SCROLL         8
#परिभाषय ACTION_HOVER_ENTER    9
#परिभाषय ACTION_HOVER_EXIT     10
#परिभाषय ACTION_BUTTON_PRESS   11
#परिभाषय ACTION_BUTTON_RELEASE 12

#परिभाषय BUTTON_PRIMARY        1
#परिभाषय BUTTON_SECONDARY      2
#परिभाषय BUTTON_TERTIARY       4
#परिभाषय BUTTON_पृष्ठभागः           8
#परिभाषय BUTTON_FORWARD        16

संरचना SDL_Cursor_दत्त
{
    पूर्णाङ्क custom_cursor;
    पूर्णाङ्क system_cursor;
};

स्थिर ध्रुव वर्ण k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_पृष्ठभागः, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
स्थिर पूर्णाङ्क चरमः_state;

// Blank cursor
स्थिर SDL_Cursor *रिक्तानि_cursor;

स्थिर SDL_Cursor *Android_WrapCursor(पूर्णाङ्क custom_cursor, पूर्णाङ्क system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, परिमाण(*cursor));
    यदि (cursor) {
        SDL_Cursor_दत्त *दत्त = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
        यदि (दत्त) {
            दत्त->custom_cursor = custom_cursor;
            दत्त->system_cursor = system_cursor;
            cursor->आन्तरिकम् = दत्त;
        } अन्यथा {
            SDL_free(cursor);
            cursor = रिक्त;
        }
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *Android_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम Android_WrapCursor(0, id);
}

स्थिर SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    पूर्णाङ्क custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    यदि (!converted) {
        प्रत्यागम रिक्त;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    यदि (!custom_cursor) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम Android_WrapCursor(custom_cursor, 0);
}

स्थिर SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    प्रत्यागम Android_WrapCursor(0, id);
}

स्थिर शून्य Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;
    यदि (दत्त->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(दत्त->custom_cursor);
    }
    SDL_free(cursor->आन्तरिकम्);
    SDL_free(cursor);
}

स्थिर SDL_Cursor *Android_Create_रिक्तानि_Cursor(शून्य)
{
    यदि (!रिक्तानि_cursor) {
        SDL_Surface *रिक्तानि_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        यदि (रिक्तानि_surface) {
            रिक्तानि_cursor = Android_CreateCursor(रिक्तानि_surface, 0, 0);
            SDL_DestroySurface(रिक्तानि_surface);
        }
    }
    प्रत्यागम रिक्तानि_cursor;
}

स्थिर शून्य Android_Destroy_रिक्तानि_Cursor(शून्य)
{
    यदि (रिक्तानि_cursor) {
        Android_FreeCursor(रिक्तानि_cursor);
        रिक्तानि_cursor = रिक्त;
    }
}

स्थिर bool Android_ShowCursor(SDL_Cursor *cursor)
{
    यदि (!cursor) {
        cursor = Android_Create_रिक्तानि_Cursor();
    }
    यदि (cursor) {
        SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;
        यदि (दत्त->custom_cursor) {
            यदि (!Android_JNI_समुच्चयः_Custom_Cursor(दत्त->custom_cursor)) {
                प्रत्यागम SDL_Unsupported();
            }
        } अन्यथा {
            यदि (!Android_JNI_समुच्चयः_System_Cursor(दत्त->system_cursor)) {
                प्रत्यागम SDL_Unsupported();
            }
        }
        प्रत्यागम true;
    } अन्यथा {
        // SDL error set inside Android_CreateEmptyCursor()
        प्रत्यागम false;
    }
}

स्थिर bool Android_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    यदि (!Android_JNI_SupportsRelativeMouse()) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (!Android_JNI_समुच्चयः_Relative_Mouse_Enabled(enabled)) {
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम true;
}

शून्य Android_InitMouse(शून्य)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Android_CreateCursor;
    mouse->CreateSystemCursor = Android_CreateSystemCursor;
    mouse->ShowCursor = Android_ShowCursor;
    mouse->FreeCursor = Android_FreeCursor;
    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = Android_समुच्चयः_Relative_Mouse_बहुलकम्;

    SDL_समुच्चयः_Default_Cursor(Android_CreateDefaultCursor());

    चरमः_state = 0;
}

शून्य Android_QuitMouse(शून्य)
{
    Android_Destroy_रिक्तानि_Cursor();
}

// Translate Android mouse button state to SDL mouse button
स्थिर Uint8 TranslateButton(पूर्णाङ्क state)
{
    यदि (state & BUTTON_PRIMARY) {
        प्रत्यागम SDL_BUTTON_वामः;
    } अन्यथा यदि (state & BUTTON_SECONDARY) {
        प्रत्यागम SDL_BUTTON_दक्षिणः;
    } अन्यथा यदि (state & BUTTON_TERTIARY) {
        प्रत्यागम SDL_BUTTON_मध्यः;
    } अन्यथा यदि (state & BUTTON_FORWARD) {
        प्रत्यागम SDL_BUTTON_X1;
    } अन्यथा यदि (state & BUTTON_पृष्ठभागः) {
        प्रत्यागम SDL_BUTTON_X2;
    } अन्यथा {
        प्रत्यागम 0;
    }
}

शून्य Android_OnMouse(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क state, पूर्णाङ्क action, भिन्न x, भिन्न y, bool relative)
{
    पूर्णाङ्क changes_press;
    पूर्णाङ्क changes_release;
    Uint8 button;

    यदि (!गवाक्षः) {
        प्रत्यागम;
    }

    विकल्प (action) {
    पक्ष ACTION_MOVE:
    पक्ष ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, गवाक्षः, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        भङ्ग;

    पक्ष ACTION_SCROLL:
        SDL_SendMouseWheel(0, गवाक्षः, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_प्रसामान्यम्);
        भङ्ग;

    पक्ष ACTION_ऊर्ध्वम्:
    पक्ष ACTION_अधस्तात्:
    पक्ष ACTION_BUTTON_PRESS:
    पक्ष ACTION_BUTTON_RELEASE:
    पक्ष ACTION_HOVER_ENTER:
    पक्ष ACTION_HOVER_EXIT:
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

        changes_press = state & ~चरमः_state;
        changes_release = चरमः_state & ~state;

        SDL_SendMouseMotion(0, गवाक्षः, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        यदि (changes_press) {
            प्रति (पूर्णाङ्क i = 0; i < परिमाण(k_aAndroidButtons); i++) {
                यदि (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, गवाक्षः, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            चरमः_state = state;
        }

        यदि (changes_release) {
            प्रति (पूर्णाङ्क i = 0; i < परिमाण(k_aAndroidButtons); i++) {
                यदि (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, गवाक्षः, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            चरमः_state = state;
        }
        भङ्ग;        

    स्वभाव:
        भङ्ग;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_ANDROID
