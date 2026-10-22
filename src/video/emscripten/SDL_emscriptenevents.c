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

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#شامل <emscripten/html5.h>
#شامل <emscripten/dom_pk_codes.h>

#شامل "../../events/SDL_dropevents_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_touch_c.h"

#شامل "SDL_emscriptenevents.h"
#شامل "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ایستا ثابت SDL_Scancode emscripten_scancode_table[] = {
    /* 0x00 "Unidentified"   */ SDL_SCANCODE_UNKNOWN,
    /* 0x01 "Escape"         */ SDL_SCANCODE_ESCAPE,
    /* 0x02 "Digit0"         */ SDL_SCANCODE_0,
    /* 0x03 "Digit1"         */ SDL_SCANCODE_1,
    /* 0x04 "Digit2"         */ SDL_SCANCODE_2,
    /* 0x05 "Digit3"         */ SDL_SCANCODE_3,
    /* 0x06 "Digit4"         */ SDL_SCANCODE_4,
    /* 0x07 "Digit5"         */ SDL_SCANCODE_5,
    /* 0x08 "Digit6"         */ SDL_SCANCODE_6,
    /* 0x09 "Digit7"         */ SDL_SCANCODE_7,
    /* 0x0A "Digit8"         */ SDL_SCANCODE_8,
    /* 0x0B "Digit9"         */ SDL_SCANCODE_9,
    /* 0x0C "Minus"          */ SDL_SCANCODE_MINUS,
    /* 0x0D "Equal"          */ SDL_SCANCODE_EQUALS,
    /* 0x0E "Backspace"      */ SDL_SCANCODE_BACKSPACE,
    /* 0x0F "Tab"            */ SDL_SCANCODE_TAB,
    /* 0x10 "KeyQ"           */ SDL_SCANCODE_Q,
    /* 0x11 "KeyW"           */ SDL_SCANCODE_W,
    /* 0x12 "KeyE"           */ SDL_SCANCODE_E,
    /* 0x13 "KeyR"           */ SDL_SCANCODE_R,
    /* 0x14 "KeyT"           */ SDL_SCANCODE_T,
    /* 0x15 "KeyY"           */ SDL_SCANCODE_Y,
    /* 0x16 "KeyU"           */ SDL_SCANCODE_U,
    /* 0x17 "KeyI"           */ SDL_SCANCODE_I,
    /* 0x18 "KeyO"           */ SDL_SCANCODE_O,
    /* 0x19 "KeyP"           */ SDL_SCANCODE_P,
    /* 0x1A "BracketLeft"    */ SDL_SCANCODE_LEFTBRACKET,
    /* 0x1B "BracketRight"   */ SDL_SCANCODE_RIGHTBRACKET,
    /* 0x1C "Enter"          */ SDL_SCANCODE_RETURN,
    /* 0x1D "ControlLeft"    */ SDL_SCANCODE_LCTRL,
    /* 0x1E "KeyA"           */ SDL_SCANCODE_A,
    /* 0x1F "KeyS"           */ SDL_SCANCODE_S,
    /* 0x20 "KeyD"           */ SDL_SCANCODE_D,
    /* 0x21 "KeyF"           */ SDL_SCANCODE_F,
    /* 0x22 "KeyG"           */ SDL_SCANCODE_G,
    /* 0x23 "KeyH"           */ SDL_SCANCODE_H,
    /* 0x24 "KeyJ"           */ SDL_SCANCODE_J,
    /* 0x25 "KeyK"           */ SDL_SCANCODE_K,
    /* 0x26 "KeyL"           */ SDL_SCANCODE_L,
    /* 0x27 "Semicolon"      */ SDL_SCANCODE_SEMICOLON,
    /* 0x28 "Quote"          */ SDL_SCANCODE_APOSTROPHE,
    /* 0x29 "Backquote"      */ SDL_SCANCODE_GRAVE,
    /* 0x2A "ShiftLeft"      */ SDL_SCANCODE_LSHIFT,
    /* 0x2B "Backslash"      */ SDL_SCANCODE_BACKSLASH,
    /* 0x2C "KeyZ"           */ SDL_SCANCODE_Z,
    /* 0x2D "KeyX"           */ SDL_SCANCODE_X,
    /* 0x2E "KeyC"           */ SDL_SCANCODE_C,
    /* 0x2F "KeyV"           */ SDL_SCANCODE_V,
    /* 0x30 "KeyB"           */ SDL_SCANCODE_B,
    /* 0x31 "KeyN"           */ SDL_SCANCODE_N,
    /* 0x32 "KeyM"           */ SDL_SCANCODE_M,
    /* 0x33 "Comma"          */ SDL_SCANCODE_COMMA,
    /* 0x34 "Period"         */ SDL_SCANCODE_PERIOD,
    /* 0x35 "Slash"          */ SDL_SCANCODE_SLASH,
    /* 0x36 "ShiftRight"     */ SDL_SCANCODE_RSHIFT,
    /* 0x37 "NumpadMultiply" */ SDL_SCANCODE_KP_MULTIPLY,
    /* 0x38 "AltLeft"        */ SDL_SCANCODE_LALT,
    /* 0x39 "Space"          */ SDL_SCANCODE_SPACE,
    /* 0x3A "CapsLock"       */ SDL_SCANCODE_CAPSLOCK,
    /* 0x3B "F1"             */ SDL_SCANCODE_F1,
    /* 0x3C "F2"             */ SDL_SCANCODE_F2,
    /* 0x3D "F3"             */ SDL_SCANCODE_F3,
    /* 0x3E "F4"             */ SDL_SCANCODE_F4,
    /* 0x3F "F5"             */ SDL_SCANCODE_F5,
    /* 0x40 "F6"             */ SDL_SCANCODE_F6,
    /* 0x41 "F7"             */ SDL_SCANCODE_F7,
    /* 0x42 "F8"             */ SDL_SCANCODE_F8,
    /* 0x43 "F9"             */ SDL_SCANCODE_F9,
    /* 0x44 "F10"            */ SDL_SCANCODE_F10,
    /* 0x45 "Pause"          */ SDL_SCANCODE_PAUSE,
    /* 0x46 "ScrollLock"     */ SDL_SCANCODE_SCROLLLOCK,
    /* 0x47 "Numpad7"        */ SDL_SCANCODE_KP_7,
    /* 0x48 "Numpad8"        */ SDL_SCANCODE_KP_8,
    /* 0x49 "Numpad9"        */ SDL_SCANCODE_KP_9,
    /* 0x4A "NumpadSubtract" */ SDL_SCANCODE_KP_MINUS,
    /* 0x4B "Numpad4"        */ SDL_SCANCODE_KP_4,
    /* 0x4C "Numpad5"        */ SDL_SCANCODE_KP_5,
    /* 0x4D "Numpad6"        */ SDL_SCANCODE_KP_6,
    /* 0x4E "NumpadAdd"      */ SDL_SCANCODE_KP_PLUS,
    /* 0x4F "Numpad1"        */ SDL_SCANCODE_KP_1,
    /* 0x50 "Numpad2"        */ SDL_SCANCODE_KP_2,
    /* 0x51 "Numpad3"        */ SDL_SCANCODE_KP_3,
    /* 0x52 "Numpad0"        */ SDL_SCANCODE_KP_0,
    /* 0x53 "NumpadDecimal"  */ SDL_SCANCODE_KP_PERIOD,
    /* 0x54 "PrintScreen"    */ SDL_SCANCODE_PRINTSCREEN,
    /* 0x55                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x56 "IntlBackslash"  */ SDL_SCANCODE_NONUSBACKSLASH,
    /* 0x57 "F11"            */ SDL_SCANCODE_F11,
    /* 0x58 "F12"            */ SDL_SCANCODE_F12,
    /* 0x59 "NumpadEqual"    */ SDL_SCANCODE_KP_EQUALS,
    /* 0x5A                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5B                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5C                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5D                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5E                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5F                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x60                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x61                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x62                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x63                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x64 "F13"            */ SDL_SCANCODE_F13,
    /* 0x65 "F14"            */ SDL_SCANCODE_F14,
    /* 0x66 "F15"            */ SDL_SCANCODE_F15,
    /* 0x67 "F16"            */ SDL_SCANCODE_F16,
    /* 0x68 "F17"            */ SDL_SCANCODE_F17,
    /* 0x69 "F18"            */ SDL_SCANCODE_F18,
    /* 0x6A "F19"            */ SDL_SCANCODE_F19,
    /* 0x6B "F20"            */ SDL_SCANCODE_F20,
    /* 0x6C "F21"            */ SDL_SCANCODE_F21,
    /* 0x6D "F22"            */ SDL_SCANCODE_F22,
    /* 0x6E "F23"            */ SDL_SCANCODE_F23,
    /* 0x6F                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x70 "KanaMode"       */ SDL_SCANCODE_INTERNATIONAL2,
    /* 0x71 "Lang2"          */ SDL_SCANCODE_LANG2,
    /* 0x72 "Lang1"          */ SDL_SCANCODE_LANG1,
    /* 0x73 "IntlRo"         */ SDL_SCANCODE_INTERNATIONAL1,
    /* 0x74                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x75                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x76 "F24"            */ SDL_SCANCODE_F24,
    /* 0x77                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x78                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x79 "Convert"        */ SDL_SCANCODE_INTERNATIONAL4,
    /* 0x7A                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x7B "NonConvert"     */ SDL_SCANCODE_INTERNATIONAL5,
    /* 0x7C                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x7D "IntlYen"        */ SDL_SCANCODE_INTERNATIONAL3,
    /* 0x7E "NumpadComma"    */ SDL_SCANCODE_KP_COMMA
};

ایستا SDL_Scancode Emscripten_MapScanCode(ثابت نویسه *code)
{
    ثابت DOM_PK_CODE_TYPE pk_code = emscripten_compute_dom_pk_code(code);
    اگر (pk_code < SDL_arraysize(emscripten_scancode_table)) {
        بازگشت emscripten_scancode_table[pk_code];
    }

    انتخاب (pk_code) {
    حالت DOM_PK_PASTE:
        بازگشت SDL_SCANCODE_PASTE;
    حالت DOM_PK_MEDIA_TRACK_PREVIOUS:
        بازگشت SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
    حالت DOM_PK_CUT:
        بازگشت SDL_SCANCODE_CUT;
    حالت DOM_PK_COPY:
        بازگشت SDL_SCANCODE_COPY;
    حالت DOM_PK_MEDIA_TRACK_NEXT:
        بازگشت SDL_SCANCODE_MEDIA_NEXT_TRACK;
    حالت DOM_PK_NUMPAD_ENTER:
        بازگشت SDL_SCANCODE_KP_ENTER;
    حالت DOM_PK_CONTROL_راست:
        بازگشت SDL_SCANCODE_RCTRL;
    حالت DOM_PK_AUDIO_VOLUME_MUTE:
        بازگشت SDL_SCANCODE_MUTE;
    حالت DOM_PK_MEDIA_PLAY_PAUSE:
        بازگشت SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    حالت DOM_PK_MEDIA_STOP:
        بازگشت SDL_SCANCODE_MEDIA_STOP;
    حالت DOM_PK_EJECT:
        بازگشت SDL_SCANCODE_MEDIA_EJECT;
    حالت DOM_PK_AUDIO_VOLUME_DOWN:
        بازگشت SDL_SCANCODE_VOLUMEDOWN;
    حالت DOM_PK_AUDIO_VOLUME_UP:
        بازگشت SDL_SCANCODE_VOLUMEUP;
    حالت DOM_PK_BROWSER_HOME:
        بازگشت SDL_SCANCODE_AC_HOME;
    حالت DOM_PK_NUMPAD_DIVIDE:
        بازگشت SDL_SCANCODE_KP_DIVIDE;
    حالت DOM_PK_ALT_راست:
        بازگشت SDL_SCANCODE_RALT;
    حالت DOM_PK_HELP:
        بازگشت SDL_SCANCODE_HELP;
    حالت DOM_PK_رقم_LOCK:
        بازگشت SDL_SCANCODE_NUMLOCKCLEAR;
    حالت DOM_PK_HOME:
        بازگشت SDL_SCANCODE_HOME;
    حالت DOM_PK_ARROW_UP:
        بازگشت SDL_SCANCODE_UP;
    حالت DOM_PK_PAGE_UP:
        بازگشت SDL_SCANCODE_PAGEUP;
    حالت DOM_PK_ARROW_چپ:
        بازگشت SDL_SCANCODE_چپ;
    حالت DOM_PK_ARROW_راست:
        بازگشت SDL_SCANCODE_راست;
    حالت DOM_PK_END:
        بازگشت SDL_SCANCODE_END;
    حالت DOM_PK_ARROW_DOWN:
        بازگشت SDL_SCANCODE_DOWN;
    حالت DOM_PK_PAGE_DOWN:
        بازگشت SDL_SCANCODE_PAGEDOWN;
    حالت DOM_PK_درج:
        بازگشت SDL_SCANCODE_درج;
    حالت DOM_PK_DELETE:
        بازگشت SDL_SCANCODE_DELETE;
    حالت DOM_PK_META_چپ:
        بازگشت SDL_SCANCODE_LGUI;
    حالت DOM_PK_META_راست:
        بازگشت SDL_SCANCODE_RGUI;
    حالت DOM_PK_CONTEXT_MENU:
        بازگشت SDL_SCANCODE_APPLICATION;
    حالت DOM_PK_POWER:
        بازگشت SDL_SCANCODE_POWER;
    حالت DOM_PK_BROWSER_جستجو:
        بازگشت SDL_SCANCODE_AC_جستجو;
    حالت DOM_PK_BROWSER_FAVORITES:
        بازگشت SDL_SCANCODE_AC_BOOKMARKS;
    حالت DOM_PK_BROWSER_REFRESH:
        بازگشت SDL_SCANCODE_AC_REFRESH;
    حالت DOM_PK_BROWSER_STOP:
        بازگشت SDL_SCANCODE_AC_STOP;
    حالت DOM_PK_BROWSER_FORWARD:
        بازگشت SDL_SCANCODE_AC_FORWARD;
    حالت DOM_PK_BROWSER_BACK:
        بازگشت SDL_SCANCODE_AC_BACK;
    حالت DOM_PK_MEDIA_SELECT:
        بازگشت SDL_SCANCODE_MEDIA_SELECT;
    }

    بازگشت SDL_SCANCODE_UNKNOWN;
}

ایستا SDL_Window *Emscripten_GetFocusedWindow(SDL_VideoDevice *device)
{
    SDL_Window *window;
    برای (window = device->windows; window; window = window->next) {
        SDL_WindowData *wdata = window->internal;

        ثابت صحیح focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8ToString($0);
            try
            {
                var canvas = document.querySelector(id);
                اگر (canvas) {
                    بازگشت canvas === document.activeElement;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            بازگشت false;
        }, wdata->canvas_id);

        اگر (focused) {
            بشکن;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    اگر (!window) {
        ثابت صحیح focused = MAIN_THREAD_EM_ASM_INT({
            بازگشت document.hasFocus();
        });
        اگر (focused) {
            window = device->windows;
        }
    }
    بازگشت window;
}

ایستا EM_BOOL Emscripten_HandlePointerLockChange(صحیح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, تهی *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;
    // keep track of lock losses, so we can regrab if/when appropriate.
    window_data->has_pointer_lock = changeEvent->isActive;
    بازگشت 0;
}

ایستا EM_BOOL Emscripten_HandlePointerLockChangeGlobal(صحیح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, تهی *userData)
{
    SDL_VideoDevice *device = userData;
    bool prevent_default = false;
    SDL_Window *window;

    برای (window = device->windows; window; window = window->next) {
        prevent_default |= Emscripten_HandlePointerLockChange(eventType, changeEvent, window->internal);
    }

    بازگشت prevent_default;
}

ایستا EM_BOOL Emscripten_HandleWheel(صحیح eventType, ثابت EmscriptenWheelEvent *wheelEvent, تهی *userData)
{
    SDL_WindowData *window_data = userData;

    اعشاری deltaY = wheelEvent->deltaY;
    اعشاری deltaX = wheelEvent->deltaX;

    انتخاب (wheelEvent->deltaMode) {
    حالت DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        بشکن;
    حالت DOM_DELTA_سطر:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        بشکن;
    حالت DOM_DELTA_PAGE:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        بشکن;
    }

    SDL_SendMouseWheel(0, window_data->window, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_NORMAL);
    بازگشت SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ایستا EM_BOOL Emscripten_HandleFocus(صحیح eventType, ثابت EmscriptenFocusEvent *focusEvent, تهی *userData)
{
    SDL_VideoDevice *device = userData;
    SDL_Window *window = Emscripten_GetFocusedWindow(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    اگر (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_SetKeyboardFocus(sdl_event_type == SDL_EVENT_WINDOW_FOCUS_GAINED ? window : پوچ);
    بازگشت SDL_EventEnabled(sdl_event_type);
}

ایستا bool Is_Function_کلید(SDL_Scancode scancode)
{
    اگر (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        بازگشت true;
    }
    اگر (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        بازگشت true;
    }
    بازگشت false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ایستا EM_BOOL Emscripten_Handle_کلید(صحیح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, تهی *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;
    SDL_Scancode scancode = Emscripten_MapScanCode(کلید_Event->code);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_کلید = false;

    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
        اگر (SDL_strcmp(کلید_Event->کلید, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_RECORD;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        اگر (SDL_strcmp(کلید_Event->کلید, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } وگرنه اگر (SDL_strcmp(کلید_Event->کلید, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_BACK;
        }
    }

    اگر (کلید_Event->location == 0 && SDL_utf8strlen(کلید_Event->کلید) == 1) {
        ثابت نویسه *کلید = کلید_Event->کلید;
        keycode = SDL_StepUTF8(&کلید, پوچ);
        اگر (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    اگر (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_کلید_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } وگرنه {
        prevent_default = SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    اگر ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_چپ) ||
        (scancode == SDL_SCANCODE_UP) ||
        (scancode == SDL_SCANCODE_راست) ||
        (scancode == SDL_SCANCODE_DOWN) ||
        Is_Function_کلید(scancode) ||
        کلید_Event->ctrl_کلید) {
        is_nav_کلید = true;
    }

    اگر ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_Text_درون_داد_Active(window_data->window) && !is_nav_کلید) {
        prevent_default = false;
    }

    بازگشت prevent_default;
}

ایستا EM_BOOL Emscripten_Handle_کلید_Press(صحیح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, تهی *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;

    اگر (SDL_Text_درون_داد_Active(window_data->window)) {
        اگر (SDL_utf8strlen(کلید_Event->کلید) == 1) {
            SDL_SendKeyboardText(کلید_Event->کلید);
            بازگشت EM_TRUE;
        }
    }
    بازگشت EM_FALSE;
}

ایستا EM_BOOL Emscripten_HandleFullscreenChange(صحیح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, تهی *userData)
{
    SDL_WindowData *window_data = userData;

    window_data->fullscreen_change_in_progress = false;

    اگر (fullscreenChangeEvent->isFullscreen) {
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
        window_data->fullscreen_mode_flags = 0;
    } وگرنه {
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_UpdateFullscreenMode(window_data->window, fullscreenChangeEvent->isFullscreen, false);

    بازگشت 0;
}

ایستا EM_BOOL Emscripten_HandleFullscreenChangeGlobal(صحیح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, تهی *userData)
{
    SDL_VideoDevice *device = userData;
    SDL_Window *window = پوچ;
    برای (window = device->windows; window != پوچ; window = window->next) {
        ثابت نویسه *canvas_id = window->internal->canvas_id;
        اگر (*canvas_id == '#') {
            canvas_id++;
        }
        اگر (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            بشکن;  // this is the window.
        }
    }

    اگر (window) {
        بازگشت Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, window->internal);
    }

    بازگشت EM_FALSE;
}

ایستا EM_BOOL Emscripten_HandleResize(صحیح eventType, ثابت EmscriptenUiEvent *uiEvent, تهی *userData)
{
    SDL_WindowData *window_data = userData;

    bool force = false;

    // update pixel ratio
    اگر (window_data->window->flags & SDL_WINDOW_بالا_PIXEL_DENSITY) {
        اگر (window_data->pixel_ratio != emscripten_get_device_pixel_ratio()) {
            window_data->pixel_ratio = emscripten_get_device_pixel_ratio();
            force = true;
        }
    }

    ثابت bool fill_document = (Emscripten_fill_document_window == window_data->window);
    ثابت bool fullscreen = (window_data->window->flags & SDL_WINDOW_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ثابت bool resizable = (window_data->window->flags & SDL_WINDOW_RESIZABLE) != 0;
    اگر (fill_document || fullscreen || resizable) {
        دوگانه w, h;
        اگر (fill_document || fullscreen) {
            w = (دوگانه) uiEvent->windowInnerWidth;
            h = (دوگانه) uiEvent->windowInnerHeight;
        } وگرنه {
            SDL_assert(window_data->window->flags & SDL_WINDOW_RESIZABLE);
            w = window_data->window->w;
            h = window_data->window->h;
            // this will only work if the canvas size is set through css
            اگر (window_data->external_size) {
                emscripten_get_element_css_size(window_data->canvas_id, &w, &h);
            }
        }

        emscripten_set_canvas_element_size(window_data->canvas_id, SDL_lroundf(w * window_data->pixel_ratio), SDL_lroundf(h * window_data->pixel_ratio));

        // set_canvas_size unsets this
        اگر (!window_data->external_size && window_data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(window_data->canvas_id, w, h);
        }

        اگر (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            window_data->window->w = 0;
            window_data->window->h = 0;
        }

        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    بازگشت 0;
}

ایستا EM_BOOL Emscripten_HandleResizeGlobal(صحیح eventType, ثابت EmscriptenUiEvent *uiEvent, تهی *userData)
{
    SDL_VideoDevice *device = userData;
    bool prevent_default = false;
    SDL_Window *window;

    برای (window = device->windows; window; window = window->next) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, window->internal);
    }

    بازگشت prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(صحیح eventType, ثابت تهی *reserved, تهی *userData)
{
    // this is used during fullscreen changes
    SDL_WindowData *window_data = userData;

    اگر (window_data->fullscreen_resize) {
        دوگانه css_w, css_h;
        emscripten_get_element_css_size(window_data->canvas_id, &css_w, &css_h);
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    بازگشت 0;
}

ایستا EM_BOOL Emscripten_HandleVisibilityChange(صحیح eventType, ثابت EmscriptenVisibilityChangeEvent *visEvent, تهی *userData)
{
    SDL_WindowData *window_data = userData;
    SDL_SendWindowEvent(window_data->window, visEvent->hidden ? SDL_EVENT_WINDOW_HIDDEN : SDL_EVENT_WINDOW_SHOWN, 0, 0);
    بازگشت 0;
}

ایستا ثابت نویسه *Emscripten_HandleBeforeUnload(صحیح eventType, ثابت تهی *reserved, تهی *userData)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    بازگشت ""; // don't trigger confirmation dialog
}

ایستا EM_BOOL Emscripten_HandleOrientationChange(صحیح eventType, ثابت EmscriptenOrientationChangeEvent *orientationChangeEvent, تهی *userData)
{
    SDL_DisplayOrientation orientation;
    انتخاب (orientationChangeEvent->orientationIndex) {
        #define CHECK_ORIENTATION(emsdk, sdl) حالت EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; بشکن
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #undef CHECK_ORIENTATION
        پیشفرض: orientation = SDL_ORIENTATION_UNKNOWN; بشکن;
    }

    SDL_WindowData *window_data = (SDL_WindowData *) userData;
    SDL_SendDisplayEvent(SDL_GetVideoDisplayForWindow(window_data->window), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.documentBodyClientWidth = MAIN_THREAD_EM_ASM_INT( { بازگشت document.body.clientWidth; } );
    uiEvent.documentBodyClientHeight = MAIN_THREAD_EM_ASM_INT( { بازگشت document.body.clientHeight; } );
    uiEvent.windowInnerWidth = MAIN_THREAD_EM_ASM_INT( { بازگشت window.innerWidth; } );
    uiEvent.windowInnerHeight = MAIN_THREAD_EM_ASM_INT( { بازگشت window.innerHeight; } );
    uiEvent.windowOuterWidth = MAIN_THREAD_EM_ASM_INT( { بازگشت window.outerWidth; } );
    uiEvent.windowOuterHeight = MAIN_THREAD_EM_ASM_INT( { بازگشت window.outerHeight; } );
    uiEvent.scroll_بالاترین = MAIN_THREAD_EM_ASM_INT( { بازگشت window.pageXOffset; } );
    uiEvent.scroll_چپ = MAIN_THREAD_EM_ASM_INT( { بازگشت window.pageYOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, userData);

    بازگشت 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#define PTRTYPE_MOUSE 1
#define PTRTYPE_TOUCH 2
#define PTRTYPE_PEN 3
تعریفنوع ساختار Emscripten_PointerEvent
{
    صحیح pointer_type;
    صحیح pointerid;
    صحیح button;
    صحیح buttons;
    صحیح down;
    اعشاری movementX;
    اعشاری movementY;
    اعشاری targetX;
    اعشاری targetY;
    اعشاری pressure;
    اعشاری tangential_pressure;
    اعشاری tiltx;
    اعشاری tilty;
    اعشاری rotation;
} Emscripten_PointerEvent;

ایستا تهی Emscripten_HandleMouseButton(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    Uint8 sdl_button;
    bool down = false;
    انتخاب (event->button) {
        #define CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) حالت jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; down = (event->down != 0) || ((event->buttons & downflag) != 0); بشکن
        CHECK_MOUSE_BUTTON(0, 1, چپ_2);
        CHECK_MOUSE_BUTTON(1, 4, میانه_2);
        CHECK_MOUSE_BUTTON(2, 2, راست_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #undef CHECK_MOUSE_BUTTON
        پیشفرض: sdl_button = 0; بشکن;
    }

    اگر (sdl_button) {
        ثابت SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != پوچ);

        اگر (down) {
            اگر (mouse->relative_mode && !window_data->has_pointer_lock) {
                emscripten_request_pointerlock(window_data->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, window_data->window, SDL_DEFAULT_MOUSE_ID, sdl_button, down);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        اگر (mouse->auto_capture) {
            اگر (SDL_GetMouseState(پوچ, پوچ) != 0) {
                window_data->window->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } وگرنه {
                window_data->window->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;
            }
        }

        اگر (!down && window_data->mouse_focus_loss_pending) {
            window_data->mouse_focus_loss_pending = (window_data->window->flags & SDL_WINDOW_MOUSE_CAPTURE) != 0;
            اگر (!window_data->mouse_focus_loss_pending) {
                SDL_SetMouseFocus(پوچ);
            }
        }
    }
}

ایستا تهی Emscripten_UpdateMouseFromEvent(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    اگر (window_data->window->flags & SDL_WINDOW_HIDDEN) {
        بازگشت;
    }

    // rescale (in case canvas is being scaled)
    دوگانه client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);
    ثابت دوگانه xscale = window_data->window->w / client_w;
    ثابت دوگانه yscale = window_data->window->h / client_h;

    ثابت bool isPointerLocked = window_data->has_pointer_lock;
    اعشاری mx, my;
    اگر (isPointerLocked) {
        mx = (اعشاری)(event->movementX * xscale);
        my = (اعشاری)(event->movementY * yscale);
    } وگرنه {
        mx = (اعشاری)(event->targetX * xscale);
        my = (اعشاری)(event->targetY * yscale);
    }

    SDL_SendMouseMotion(0, window_data->window, SDL_DEFAULT_MOUSE_ID, isPointerLocked, mx, my);

    Emscripten_HandleMouseButton(window_data, event);
}

ایستا تهی Emscripten_UpdateTouchFromEvent(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    اگر (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        بازگشت;
    }

    دوگانه client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    اعشاری x, y;
    اگر (client_w <= 1) {
        x = 0.5f;
    } وگرنه {
        x = event->targetX / (client_w - 1);
    }
    اگر (client_h <= 1) {
        y = 0.5f;
    } وگرنه {
        y = event->targetY / (client_h - 1);
    }

    ثابت bool down = (event->buttons & 1) != 0;
    اگر (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        اگر (down) {
            SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, window_data->window, x, y, 1.0f);

    اگر (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        اگر (!down) {
            SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
        }
    }
}

ایستا تهی Emscripten_UpdatePenFromEvent(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);
    ثابت SDL_PenID pen = SDL_FindPenByHandle((تهی *) (size_t) 1);   // something > 0 for the single pen handle.
    اگر (pen) {
        // rescale (in case canvas is being scaled)
        دوگانه client_w, client_h;
        emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);
        ثابت دوگانه xscale = window_data->window->w / client_w;
        ثابت دوگانه yscale = window_data->window->h / client_h;

        ثابت bool isPointerLocked = window_data->has_pointer_lock;
        اعشاری mx, my;
        اگر (isPointerLocked) {
            mx = (اعشاری)(event->movementX * xscale);
            my = (اعشاری)(event->movementY * yscale);
        } وگرنه {
            mx = (اعشاری)(event->targetX * xscale);
            my = (اعشاری)(event->targetY * yscale);
        }

        SDL_SendPenMotion(0, pen, window_data->window, mx, my);

        اگر (event->button == 0) {  // pen touch
            bool down = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, window_data->window, false, down);
        } وگرنه اگر (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool down = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, window_data->window, true, down);
        } وگرنه اگر (event->button == 1) {
            bool down = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, window_data->window, 2, down);
        } وگرنه اگر (event->button == 2) {
            bool down = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, window_data->window, 1, down);
        }

        SDL_SendPenAxis(0, pen, window_data->window, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, window_data->window, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, window_data->window, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, window_data->window, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, window_data->window, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ایستا تهی Emscripten_UpdatePointerFromEvent(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event != پوچ);
    اگر (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(window_data, event);
    } وگرنه اگر (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(window_data, event);
    } وگرنه اگر (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(window_data, event);
    } وگرنه {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ایستا تهی Emscripten_HandleMouseFocus(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event, bool isenter)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    اگر (window_data->window->flags & SDL_WINDOW_HIDDEN) {
        بازگشت;
    }

    ثابت bool isPointerLocked = window_data->has_pointer_lock;

    اگر (!isPointerLocked) {
        // rescale (in case canvas is being scaled)
        اعشاری mx, my;
        دوگانه client_w, client_h;
        emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

        mx = (اعشاری)(event->targetX * (window_data->window->w / client_w));
        my = (اعشاری)(event->targetY * (window_data->window->h / client_h));
        SDL_SendMouseMotion(0, window_data->window, SDL_GLOBAL_MOUSE_ID, isPointerLocked, mx, my);
    }

    اگر (isenter && window_data->mouse_focus_loss_pending) {
        window_data->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } وگرنه اگر (!isenter && (window_data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        window_data->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } وگرنه {
        SDL_SetMouseFocus(isenter ? window_data->window : پوچ);
    }
}

ایستا تهی Emscripten_HandlePenEnter(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_FindPenByHandle((تهی *) (size_t) 1);  // something > 0 for the single pen handle.
    اگر (pen) {
        SDL_SendPenProximity(0, pen, window_data->window, true, true);
    } وگرنه {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.رقم_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_AddPenDevice(0, پوچ, window_data->window, &peninfo, (تهی *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(window_data, event);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_HandlePointerEnter(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event != پوچ);
    اگر (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_data, event, true);
    } وگرنه اگر (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(window_data, event);
    } وگرنه اگر (event->pointer_type == PTRTYPE_TOUCH) {
        // do nothing.
    } وگرنه {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ایستا تهی Emscripten_HandlePenLeave(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    ثابت SDL_PenID pen = SDL_FindPenByHandle((تهی *) (size_t) 1);   // something > 0 for the single pen handle.
    اگر (pen) {
        Emscripten_UpdatePointerFromEvent(window_data, event);  // last data updates?
        SDL_SendPenProximity(0, pen, window_data->window, false, false);
    }
}

ایستا تهی Emscripten_HandleTouchCancel(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    اگر (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        بازگشت;
    }

    دوگانه client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    اعشاری x, y;
    اگر (client_w <= 1) {
        x = 0.5f;
    } وگرنه {
        x = event->targetX / (client_w - 1);
    }
    اگر (client_h <= 1) {
        y = 0.5f;
    } وگرنه {
        y = event->targetY / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_HandlePointerLeave(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event != پوچ);
    اگر (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_data, event, false);
    } وگرنه اگر (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(window_data, event);
    } وگرنه اگر (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(window_data, event);
    } وگرنه {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_HandlePointerGeneric(SDL_WindowData *window_data, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(event != پوچ);
    Emscripten_UpdatePointerFromEvent(window_data, event);
}

ایستا تهی Emscripten_prep_pointer_event_callbacks(تهی)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        اگر (SDL3.makePointerEventCStruct === undefined) {
            SDL3.makePointerEventCStruct = function(چپ, بالاترین, event) {
                var ptrtype = 0;
                اگر (event.pointerType == "mouse") {
                    ptrtype = 1;
                } وگرنه اگر (event.pointerType == "touch") {
                    ptrtype = 2;
                } وگرنه اگر (event.pointerType == "pen") {
                    ptrtype = 3;
                } وگرنه {
                    بازگشت 0;
                }

                var ptr = _SDL_malloc($0);
                اگر (ptr != 0) {
                    var idx = SDL3.CPtrToHeap32Index(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.pointerId;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - چپ;
                    HEAPF32[idx++] = event.clientY - بالاترین;
                    اگر (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                بازگشت ptr;
            };
        }
    }, اندازه (Emscripten_PointerEvent));
}

ایستا تهی Emscripten_set_pointer_event_callbacks(SDL_WindowData *data)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        اگر (target) {
            var SDL3 = Module['SDL3'];
            var data = $0;
            target.sdlEventHandlerPointerEnter = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.چپ, rect.بالاترین, event);
                اگر (d != 0)
                {
                    _Emscripten_HandlePointerEnter(SDL3.JSVarToCPtr(data), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerLeave = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.چپ, rect.بالاترین, event);
                اگر (d != 0)
                {
                    _Emscripten_HandlePointerLeave(SDL3.JSVarToCPtr(data), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerGeneric = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.چپ, rect.بالاترین, event);
                اگر (d != 0)
                {
                    _Emscripten_HandlePointerGeneric(SDL3.JSVarToCPtr(data), d);
                    _SDL_free(d);
                }
            };

            target.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            target.addEventListener("pointerenter", target.sdlEventHandlerPointerEnter);
            target.addEventListener("pointerleave", target.sdlEventHandlerPointerLeave);
            target.addEventListener("pointercancel", target.sdlEventHandlerPointerLeave);
            target.addEventListener("pointerdown", target.sdlEventHandlerPointerGeneric);
            target.addEventListener("pointermove", target.sdlEventHandlerPointerGeneric);
            target.addEventListener("pointerup", target.sdlEventHandlerPointerGeneric);
        }
    }, data, data->canvas_id);
}

ایستا تهی Emscripten_unset_pointer_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        اگر (target) {
            target.removeEventListener("pointerenter", target.sdlEventHandlerPointerEnter);
            target.removeEventListener("pointerleave", target.sdlEventHandlerPointerLeave);
            target.removeEventListener("pointercancel", target.sdlEventHandlerPointerLeave);
            target.removeEventListener("pointerdown", target.sdlEventHandlerPointerGeneric);
            target.removeEventListener("pointermove", target.sdlEventHandlerPointerGeneric);
            target.removeEventListener("pointerup", target.sdlEventHandlerPointerGeneric);
            target.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            target.sdlEventHandlerPointerEnter = undefined;
            target.sdlEventHandlerPointerLeave = undefined;
            target.sdlEventHandlerPointerGeneric = undefined;
        }
    }, data->canvas_id);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_HandleMouseButtonUpGlobal(SDL_VideoDevice *device, ثابت Emscripten_PointerEvent *event)
{
    SDL_assert(device != پوچ);
    SDL_assert(event != پوچ);
    اگر (event->pointer_type == PTRTYPE_MOUSE) {
        برای (SDL_Window *window = device->windows; window; window = window->next) {
            Emscripten_HandleMouseButton(window->internal, event);
        }
    }
}

ایستا تهی Emscripten_set_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document;
        اگر (target) {
            target.sdlEventHandlerMouseButtonUpGlobal = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.makePointerEventCStruct(0, 0, event);
                اگر (d != 0)
                {
                    _Emscripten_HandleMouseButtonUpGlobal(SDL3.JSVarToCPtr($0), d);
                    _SDL_free(d);
                }
            };
            target.addEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
        }
    }, device);
}

ایستا تهی Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var target = document;
        اگر (target) {
            target.removeEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
            target.sdlEventHandlerMouseButtonUpGlobal = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
تعریفنوع ساختار Emscripten_DropEvent
{
    صحیح x;
    صحیح y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE تهی Emscripten_SendDragEvent(SDL_WindowData *window_data, ثابت Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(window_data->window, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_SendDragCompleteEvent(SDL_WindowData *window_data)
{
    SDL_SendDropComplete(window_data->window);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_SendDragTextEvent(SDL_WindowData *window_data, نویسه *text)
{
    SDL_SendDropText(window_data->window, text);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_SendDragFileEvent(SDL_WindowData *window_data, نویسه *filename)
{
    SDL_SendDropFile(window_data->window, پوچ, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ایستا تهی Emscripten_set_drag_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        اگر (target) {
            var data = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                اگر (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = target.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.چپ;
                    HEAP32[idx++] = event.clientY - rect.بالاترین;
                }
                بازگشت ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); اگر (d != 0) { _Emscripten_SendDragEvent(data, d); _SDL_free(d); }
            };
            target.addEventListener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_شمار = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                اگر (event.dataTransfer.types.includes("text/plain")) {
                    let plain_text = stringToNewUTF8(event.dataTransfer.getData("text/plain"));
                    _Emscripten_SendDragTextEvent(data, plain_text);
                    _Emscripten_force_free(plain_text);
                } وگرنه اگر (event.dataTransfer.types.includes("Files")) {
                    let files_read = 0;
                    ثابت files_to_read = event.dataTransfer.files.length;
                    برای (let i = 0; i < files_to_read; i++) {
                        ثابت file = event.dataTransfer.files.item(i);
                        ثابت file_reader = new FileReader();
                        file_reader.readAsArrayBuffer(file);
                        file_reader.onload = function(event) {
                            ثابت fs_dropdir = `/tmp/filedrop/${SDL3.drop_شمار}`;
                            SDL3.drop_شمار += 1;

                            ثابت fs_filepath = `${fs_dropdir}/${file.name}`;
                            ثابت c_fs_filepath = stringToNewUTF8(fs_filepath);
                            ثابت contents_array8 = new Uint8Array(event.target.result);

                            try {
                                FS.mkdir(fs_dropdir);
                                var stream = FS.open(fs_filepath, "w");
                                FS.اكتب(stream, contents_array8, 0, contents_array8.length, 0);
                                FS.close(stream);
                                _Emscripten_SendDragFileEvent(data, c_fs_filepath);
                            } catch (e) {
                                // if this threw an exception at any point, we skip this drop event. Sorry!
                            }
                            _Emscripten_force_free(c_fs_filepath);
                            onFileRead();
                        };
                        file_reader.onerror = function(event) {
                            // Handle when error occurs to ensure that the drag event can still complete
                            onFileRead();
                        };
                    }
                    function onFileRead() {
                        ++files_read;
                        اگر (files_read === files_to_read) {
                            _Emscripten_SendDragCompleteEvent(data);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(data);
            };
            target.addEventListener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(data);
            };
            target.addEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.addEventListener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, data, data->canvas_id, اندازه (Emscripten_DropEvent));
}

ایستا تهی Emscripten_unset_drag_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        اگر (target) {
            var SDL3 = Module['SDL3'];
            target.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            target.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_شمار = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ثابت p = `${dirpath}/${filename}`;
                    ثابت p_s = FS.stat(p);
                    اگر (FS.isFile(p_s.mode)) {
                        FS.unlink(p);
                    } وگرنه اگر (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            target.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, data->canvas_id);
}

ایستا ثابت نویسه *Emscripten_GetKeyboardTargetElement(ثابت نویسه *target)
{
    اگر (SDL_strcmp(target, "#none") == 0) {
        بازگشت پوچ;
    } وگرنه اگر (SDL_strcmp(target, "#window") == 0) {
        بازگشت EMSCRIPTEN_EVENT_TARGET_WINDOW;
    } وگرنه اگر (SDL_strcmp(target, "#document") == 0) {
        بازگشت EMSCRIPTEN_EVENT_TARGET_DOCUMENT;
    } وگرنه اگر (SDL_strcmp(target, "#screen") == 0) {
        بازگشت EMSCRIPTEN_EVENT_TARGET_SCREEN;
    }

    بازگشت target;
}

تهی Emscripten_RegisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_set_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandlePointerLockChangeGlobal);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleResizeGlobal);
}

تهی Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, پوچ, 0, پوچ);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, پوچ, 0, پوچ);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, پوچ, 0, پوچ);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, پوچ, 0, پوچ);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, پوچ, 0, پوچ);
}

EMSCRIPTEN_KEEPALIVE تهی Emscripten_Handle_Lock_کلیدها_Check(SDL_WindowData *window_data, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ثابت SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_رقم : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    اگر ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_رقم|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_رقم|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_SetModState(modstate);
    }
}

تهی Emscripten_RegisterEventHandlers(SDL_WindowData *data)
{
    ثابت نویسه *کلید_Element;

    // There is only one window and that window is the canvas
    emscripten_set_wheel_callback(data->canvas_id, data, 0, Emscripten_HandleWheel);

    emscripten_set_orientationchange_callback(data, 0, Emscripten_HandleOrientationChange);

    کلید_Element = Emscripten_GetKeyboardTargetElement(data->keyboard_element);
    اگر (کلید_Element) {
        // Emscripten's HTML5 helpers do not deduplicate `addEventListener` calls:
        // see `registerOrRemoveHandler` in `emscripten/src/lib/libhtml5.js`.
        //
        // If a previous SDL window already registered keyboard handlers on the same
        // target, the new registration would *stack* a second listener, causing every
        // browser keydown to fire `Emscripten_HandleKey` twice.
        //
        // The duplicate calls then produce two `SDL_EVENT_KEY_DOWN` events per physical
        // keypress (the second one with `repeat=true`, due to the keystate-based repeat
        // detection in `SDL_SendKeyboardKeyInternal`).
        //
        // We must clear any prior handler on this target before installing ours:
        emscripten_set_keydown_callback(کلید_Element, پوچ, 0, پوچ);
        emscripten_set_keyup_callback(کلید_Element, پوچ, 0, پوچ);
        emscripten_set_keypress_callback(کلید_Element, پوچ, 0, پوچ);

        MAIN_THREAD_EM_ASM_INT({
            var data = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            اگر (document.sdl_Event_Handler_Lock_کلیدها_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_کلیدها_Check);
            }

            document.sdl_Event_Handler_Lock_کلیدها_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                اگر ((event.کلید != "CapsLock") && (event.کلید != "NumLock") && (event.کلید != "ScrollLock"))
                {
                    Emscripten_Handle_Lock_کلیدها_Check_2(Module['SDL3'].JSVarToCPtr(data), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.addEventListener("keydown", document.sdl_Event_Handler_Lock_کلیدها_Check);
        }, data);
        emscripten_set_keydown_callback(کلید_Element, data, 0, Emscripten_Handle_کلید);
        emscripten_set_keyup_callback(کلید_Element, data, 0, Emscripten_Handle_کلید);
        emscripten_set_keypress_callback(کلید_Element, data, 0, Emscripten_Handle_کلید_Press);
    }

    emscripten_set_visibilitychange_callback(data, 0, Emscripten_HandleVisibilityChange);

    emscripten_set_beforeunload_callback(data, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_set_pointer_event_callbacks(data);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_set_drag_event_callbacks(data);
}

تهی Emscripten_UnregisterEventHandlers(SDL_WindowData *data)
{
    ثابت نویسه *کلید_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(data);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_pointer_event_callbacks(data);

    // only works due to having one window
    emscripten_set_wheel_callback(data->canvas_id, پوچ, 0, پوچ);

    emscripten_set_orientationchange_callback(پوچ, 0, پوچ);

    کلید_Element = Emscripten_GetKeyboardTargetElement(data->keyboard_element);
    اگر (کلید_Element) {
        emscripten_set_keydown_callback(کلید_Element, پوچ, 0, پوچ);
        emscripten_set_keyup_callback(کلید_Element, پوچ, 0, پوچ);
        emscripten_set_keypress_callback(کلید_Element, پوچ, 0, پوچ);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_کلیدها_Check);
        });
    }

    emscripten_set_visibilitychange_callback(پوچ, 0, پوچ);

    emscripten_set_beforeunload_callback(پوچ, پوچ);
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
