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

#ಅನ್ತರ್ಭಾವ "SDL_androidmouse.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಕೆಳಕ್ಕೆ           0
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ಮೇಲೆ             1
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_MOVE           2
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_CANCEL         3
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_HOVER_MOVE     7
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_SCROLL         8
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_HOVER_ENTER    9
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_HOVER_EXIT     10
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_BUTTON_PRESS   11
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_BUTTON_RELEASE 12

#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_PRIMARY        1
#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_SECONDARY      2
#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_TERTIARY       4
#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_ಹಿಂಭಾಗ           8
#ವ್ಯಾಖ್ಯಾನಿಸು BUTTON_FORWARD        16

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ custom_cursor;
    ಪೂರ್ಣಾಂಕ system_cursor;
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_ಹಿಂಭಾಗ, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_state;

// Blank cursor
ಸ್ಥಿರ SDL_Cursor *ಖಾಲಿಗಳು_cursor;

ಸ್ಥಿರ SDL_Cursor *Android_WrapCursor(ಪೂರ್ಣಾಂಕ custom_cursor, ಪೂರ್ಣಾಂಕ system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
        ಆದರೆ (ದತ್ತಾಂಶ) {
            ದತ್ತಾಂಶ->custom_cursor = custom_cursor;
            ದತ್ತಾಂಶ->system_cursor = system_cursor;
            cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_free(cursor);
            cursor = ಖಾಲಿ;
        }
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಹಿಂತಿರುಗಿ Android_WrapCursor(0, id);
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    ಪೂರ್ಣಾಂಕ custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ಆದರೆ (!converted) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ಆದರೆ (!custom_cursor) {
        SDL_Unsupported();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ Android_WrapCursor(custom_cursor, 0);
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    ಹಿಂತಿರುಗಿ Android_WrapCursor(0, id);
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(ದತ್ತಾಂಶ->custom_cursor);
    }
    SDL_free(cursor->ಆಂತರಿಕ);
    SDL_free(cursor);
}

ಸ್ಥಿರ SDL_Cursor *Android_Create_ಖಾಲಿಗಳು_Cursor(ಶೂನ್ಯ)
{
    ಆದರೆ (!ಖಾಲಿಗಳು_cursor) {
        SDL_Surface *ಖಾಲಿಗಳು_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (ಖಾಲಿಗಳು_surface) {
            ಖಾಲಿಗಳು_cursor = Android_CreateCursor(ಖಾಲಿಗಳು_surface, 0, 0);
            SDL_DestroySurface(ಖಾಲಿಗಳು_surface);
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿಗಳು_cursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_Destroy_ಖಾಲಿಗಳು_Cursor(ಶೂನ್ಯ)
{
    ಆದರೆ (ಖಾಲಿಗಳು_cursor) {
        Android_FreeCursor(ಖಾಲಿಗಳು_cursor);
        ಖಾಲಿಗಳು_cursor = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ಆದರೆ (!cursor) {
        cursor = Android_Create_ಖಾಲಿಗಳು_Cursor();
    }
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;
        ಆದರೆ (ದತ್ತಾಂಶ->custom_cursor) {
            ಆದರೆ (!Android_JNI_ಗಣ_Custom_Cursor(ದತ್ತಾಂಶ->custom_cursor)) {
                ಹಿಂತಿರುಗಿ SDL_Unsupported();
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (!Android_JNI_ಗಣ_System_Cursor(ದತ್ತಾಂಶ->system_cursor)) {
                ಹಿಂತಿರುಗಿ SDL_Unsupported();
            }
        }
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // SDL error set inside Android_CreateEmptyCursor()
        ಹಿಂತಿರುಗಿ false;
    }
}

ಸ್ಥಿರ bool Android_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    ಆದರೆ (!Android_JNI_SupportsRelativeMouse()) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (!Android_JNI_ಗಣ_Relative_Mouse_Enabled(enabled)) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Android_InitMouse(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Android_CreateCursor;
    mouse->CreateSystemCursor = Android_CreateSystemCursor;
    mouse->ShowCursor = Android_ShowCursor;
    mouse->FreeCursor = Android_FreeCursor;
    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = Android_ಗಣ_Relative_Mouse_ಬಹುಲಕ;

    SDL_ಗಣ_Default_Cursor(Android_CreateDefaultCursor());

    ಕೊನೆಯ_state = 0;
}

ಶೂನ್ಯ Android_QuitMouse(ಶೂನ್ಯ)
{
    Android_Destroy_ಖಾಲಿಗಳು_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ಸ್ಥಿರ Uint8 TranslateButton(ಪೂರ್ಣಾಂಕ state)
{
    ಆದರೆ (state & BUTTON_PRIMARY) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಎಡ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state & BUTTON_SECONDARY) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಬಲ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state & BUTTON_TERTIARY) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_ಮಧ್ಯ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state & BUTTON_FORWARD) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_X1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state & BUTTON_ಹಿಂಭಾಗ) {
        ಹಿಂತಿರುಗಿ SDL_BUTTON_X2;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ 0;
    }
}

ಶೂನ್ಯ Android_OnMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ state, ಪೂರ್ಣಾಂಕ action, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y, bool relative)
{
    ಪೂರ್ಣಾಂಕ changes_press;
    ಪೂರ್ಣಾಂಕ changes_release;
    Uint8 button;

    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆಯ್ಕೆ (action) {
    ಸ್ಥಿತಿ ACTION_MOVE:
    ಸ್ಥಿತಿ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_SCROLL:
        SDL_SendMouseWheel(0, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ ACTION_ಮೇಲೆ:
    ಸ್ಥಿತಿ ACTION_ಕೆಳಕ್ಕೆ:
    ಸ್ಥಿತಿ ACTION_BUTTON_PRESS:
    ಸ್ಥಿತಿ ACTION_BUTTON_RELEASE:
    ಸ್ಥಿತಿ ACTION_HOVER_ENTER:
    ಸ್ಥಿತಿ ACTION_HOVER_EXIT:
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

        changes_press = state & ~ಕೊನೆಯ_state;
        changes_release = ಕೊನೆಯ_state & ~state;

        SDL_SendMouseMotion(0, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        ಆದರೆ (changes_press) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಗಾತ್ರ(k_aAndroidButtons); i++) {
                ಆದರೆ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            ಕೊನೆಯ_state = state;
        }

        ಆದರೆ (changes_release) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಗಾತ್ರ(k_aAndroidButtons); i++) {
                ಆದರೆ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            ಕೊನೆಯ_state = state;
        }
        ನಿಲ್ಲಿಸು;        

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
