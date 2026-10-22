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

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#अन्तर्भाव <emscripten/html5.h>
#अन्तर्भाव <emscripten/dom_pk_codes.h>

#अन्तर्भाव "../../events/SDL_dropevents_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

#अन्तर्भाव "SDL_emscriptenevents.h"
#अन्तर्भाव "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
स्थिर ध्रुव SDL_Scancode emscripten_scancode_table[] = {
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

स्थिर SDL_Scancode Emscripten_MapScanCode(ध्रुव वर्ण *code)
{
    ध्रुव DOM_PK_CODE_TYPE pk_code = emscripten_compute_dom_pk_code(code);
    यदि (pk_code < SDL_arraysize(emscripten_scancode_table)) {
        प्रत्यागम emscripten_scancode_table[pk_code];
    }

    विकल्प (pk_code) {
    पक्ष DOM_PK_PASTE:
        प्रत्यागम SDL_SCANCODE_PASTE;
    पक्ष DOM_PK_MEDIA_TRACK_PREVIOUS:
        प्रत्यागम SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
    पक्ष DOM_PK_CUT:
        प्रत्यागम SDL_SCANCODE_CUT;
    पक्ष DOM_PK_COPY:
        प्रत्यागम SDL_SCANCODE_COPY;
    पक्ष DOM_PK_MEDIA_TRACK_NEXT:
        प्रत्यागम SDL_SCANCODE_MEDIA_NEXT_TRACK;
    पक्ष DOM_PK_NUMPAD_ENTER:
        प्रत्यागम SDL_SCANCODE_KP_ENTER;
    पक्ष DOM_PK_CONTROL_उजवा:
        प्रत्यागम SDL_SCANCODE_RCTRL;
    पक्ष DOM_PK_AUDIO_VOLUME_MUTE:
        प्रत्यागम SDL_SCANCODE_MUTE;
    पक्ष DOM_PK_MEDIA_PLAY_PAUSE:
        प्रत्यागम SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    पक्ष DOM_PK_MEDIA_STOP:
        प्रत्यागम SDL_SCANCODE_MEDIA_STOP;
    पक्ष DOM_PK_EJECT:
        प्रत्यागम SDL_SCANCODE_MEDIA_EJECT;
    पक्ष DOM_PK_AUDIO_VOLUME_DOWN:
        प्रत्यागम SDL_SCANCODE_VOLUMEDOWN;
    पक्ष DOM_PK_AUDIO_VOLUME_UP:
        प्रत्यागम SDL_SCANCODE_VOLUMEUP;
    पक्ष DOM_PK_BROWSER_HOME:
        प्रत्यागम SDL_SCANCODE_AC_HOME;
    पक्ष DOM_PK_NUMPAD_DIVIDE:
        प्रत्यागम SDL_SCANCODE_KP_DIVIDE;
    पक्ष DOM_PK_ALT_उजवा:
        प्रत्यागम SDL_SCANCODE_RALT;
    पक्ष DOM_PK_HELP:
        प्रत्यागम SDL_SCANCODE_HELP;
    पक्ष DOM_PK_अंक_LOCK:
        प्रत्यागम SDL_SCANCODE_NUMLOCKCLEAR;
    पक्ष DOM_PK_HOME:
        प्रत्यागम SDL_SCANCODE_HOME;
    पक्ष DOM_PK_ARROW_UP:
        प्रत्यागम SDL_SCANCODE_UP;
    पक्ष DOM_PK_PAGE_UP:
        प्रत्यागम SDL_SCANCODE_PAGEUP;
    पक्ष DOM_PK_ARROW_डावा:
        प्रत्यागम SDL_SCANCODE_डावा;
    पक्ष DOM_PK_ARROW_उजवा:
        प्रत्यागम SDL_SCANCODE_उजवा;
    पक्ष DOM_PK_END:
        प्रत्यागम SDL_SCANCODE_END;
    पक्ष DOM_PK_ARROW_DOWN:
        प्रत्यागम SDL_SCANCODE_DOWN;
    पक्ष DOM_PK_PAGE_DOWN:
        प्रत्यागम SDL_SCANCODE_PAGEDOWN;
    पक्ष DOM_PK_घाला:
        प्रत्यागम SDL_SCANCODE_घाला;
    पक्ष DOM_PK_DELETE:
        प्रत्यागम SDL_SCANCODE_DELETE;
    पक्ष DOM_PK_META_डावा:
        प्रत्यागम SDL_SCANCODE_LGUI;
    पक्ष DOM_PK_META_उजवा:
        प्रत्यागम SDL_SCANCODE_RGUI;
    पक्ष DOM_PK_CONTEXT_MENU:
        प्रत्यागम SDL_SCANCODE_APPLICATION;
    पक्ष DOM_PK_POWER:
        प्रत्यागम SDL_SCANCODE_POWER;
    पक्ष DOM_PK_BROWSER_शोध:
        प्रत्यागम SDL_SCANCODE_AC_शोध;
    पक्ष DOM_PK_BROWSER_FAVORITES:
        प्रत्यागम SDL_SCANCODE_AC_BOOKMARKS;
    पक्ष DOM_PK_BROWSER_REFRESH:
        प्रत्यागम SDL_SCANCODE_AC_REFRESH;
    पक्ष DOM_PK_BROWSER_STOP:
        प्रत्यागम SDL_SCANCODE_AC_STOP;
    पक्ष DOM_PK_BROWSER_FORWARD:
        प्रत्यागम SDL_SCANCODE_AC_FORWARD;
    पक्ष DOM_PK_BROWSER_BACK:
        प्रत्यागम SDL_SCANCODE_AC_BACK;
    पक्ष DOM_PK_MEDIA_SELECT:
        प्रत्यागम SDL_SCANCODE_MEDIA_SELECT;
    }

    प्रत्यागम SDL_SCANCODE_UNKNOWN;
}

स्थिर SDL_Window *Emscripten_GetFocusedWindow(SDL_VideoDevice *device)
{
    SDL_Window *window;
    प्रति (window = device->windows; window; window = window->next) {
        SDL_WindowData *wdata = window->internal;

        ध्रुव पूर्णाङ्क focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8ToString($0);
            try
            {
                var canvas = document.querySelector(id);
                यदि (canvas) {
                    प्रत्यागम canvas === document.activeElement;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            प्रत्यागम false;
        }, wdata->canvas_id);

        यदि (focused) {
            भङ्ग;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    यदि (!window) {
        ध्रुव पूर्णाङ्क focused = MAIN_THREAD_EM_ASM_INT({
            प्रत्यागम document.hasFocus();
        });
        यदि (focused) {
            window = device->windows;
        }
    }
    प्रत्यागम window;
}

स्थिर EM_BOOL Emscripten_HandlePointerLockChange(पूर्णाङ्क eventType, ध्रुव EmscriptenPointerlockChangeEvent *changeEvent, शून्य *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;
    // keep track of lock losses, so we can regrab if/when appropriate.
    window_data->has_pointer_lock = changeEvent->isActive;
    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandlePointerLockChangeGlobal(पूर्णाङ्क eventType, ध्रुव EmscriptenPointerlockChangeEvent *changeEvent, शून्य *userData)
{
    SDL_VideoDevice *device = userData;
    bool prevent_default = false;
    SDL_Window *window;

    प्रति (window = device->windows; window; window = window->next) {
        prevent_default |= Emscripten_HandlePointerLockChange(eventType, changeEvent, window->internal);
    }

    प्रत्यागम prevent_default;
}

स्थिर EM_BOOL Emscripten_HandleWheel(पूर्णाङ्क eventType, ध्रुव EmscriptenWheelEvent *wheelEvent, शून्य *userData)
{
    SDL_WindowData *window_data = userData;

    भिन्न deltaY = wheelEvent->deltaY;
    भिन्न deltaX = wheelEvent->deltaX;

    विकल्प (wheelEvent->deltaMode) {
    पक्ष DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        भङ्ग;
    पक्ष DOM_DELTA_ओळ:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        भङ्ग;
    पक्ष DOM_DELTA_PAGE:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        भङ्ग;
    }

    SDL_SendMouseWheel(0, window_data->window, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_NORMAL);
    प्रत्यागम SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

स्थिर EM_BOOL Emscripten_HandleFocus(पूर्णाङ्क eventType, ध्रुव EmscriptenFocusEvent *focusEvent, शून्य *userData)
{
    SDL_VideoDevice *device = userData;
    SDL_Window *window = Emscripten_GetFocusedWindow(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    यदि (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_SetKeyboardFocus(sdl_event_type == SDL_EVENT_WINDOW_FOCUS_GAINED ? window : रिक्त);
    प्रत्यागम SDL_EventEnabled(sdl_event_type);
}

स्थिर bool Is_Function_किल्ली(SDL_Scancode scancode)
{
    यदि (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        प्रत्यागम true;
    }
    यदि (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
स्थिर EM_BOOL Emscripten_Handle_किल्ली(पूर्णाङ्क eventType, ध्रुव EmscriptenKeyboardEvent *किल्ली_Event, शून्य *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;
    SDL_Scancode scancode = Emscripten_MapScanCode(किल्ली_Event->code);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_किल्ली = false;

    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
        यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_RECORD;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        यदि (SDL_strcmp(किल्ली_Event->किल्ली, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } अन्यथा यदि (SDL_strcmp(किल्ली_Event->किल्ली, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_BACK;
        }
    }

    यदि (किल्ली_Event->location == 0 && SDL_utf8strlen(किल्ली_Event->किल्ली) == 1) {
        ध्रुव वर्ण *किल्ली = किल्ली_Event->किल्ली;
        keycode = SDL_StepUTF8(&किल्ली, रिक्त);
        यदि (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    यदि (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_किल्ली_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } अन्यथा {
        prevent_default = SDL_Send_Keyboard_किल्ली(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    यदि ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_डावा) ||
        (scancode == SDL_SCANCODE_UP) ||
        (scancode == SDL_SCANCODE_उजवा) ||
        (scancode == SDL_SCANCODE_DOWN) ||
        Is_Function_किल्ली(scancode) ||
        किल्ली_Event->ctrl_किल्ली) {
        is_nav_किल्ली = true;
    }

    यदि ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_Text_आदान_Active(window_data->window) && !is_nav_किल्ली) {
        prevent_default = false;
    }

    प्रत्यागम prevent_default;
}

स्थिर EM_BOOL Emscripten_Handle_किल्ली_Press(पूर्णाङ्क eventType, ध्रुव EmscriptenKeyboardEvent *किल्ली_Event, शून्य *userData)
{
    SDL_WindowData *window_data = (SDL_WindowData *)userData;

    यदि (SDL_Text_आदान_Active(window_data->window)) {
        यदि (SDL_utf8strlen(किल्ली_Event->किल्ली) == 1) {
            SDL_SendKeyboardText(किल्ली_Event->किल्ली);
            प्रत्यागम EM_TRUE;
        }
    }
    प्रत्यागम EM_FALSE;
}

स्थिर EM_BOOL Emscripten_HandleFullscreenChange(पूर्णाङ्क eventType, ध्रुव EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, शून्य *userData)
{
    SDL_WindowData *window_data = userData;

    window_data->fullscreen_change_in_progress = false;

    यदि (fullscreenChangeEvent->isFullscreen) {
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
        window_data->fullscreen_mode_flags = 0;
    } अन्यथा {
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_UpdateFullscreenMode(window_data->window, fullscreenChangeEvent->isFullscreen, false);

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleFullscreenChangeGlobal(पूर्णाङ्क eventType, ध्रुव EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, शून्य *userData)
{
    SDL_VideoDevice *device = userData;
    SDL_Window *window = रिक्त;
    प्रति (window = device->windows; window != रिक्त; window = window->next) {
        ध्रुव वर्ण *canvas_id = window->internal->canvas_id;
        यदि (*canvas_id == '#') {
            canvas_id++;
        }
        यदि (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            भङ्ग;  // this is the window.
        }
    }

    यदि (window) {
        प्रत्यागम Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, window->internal);
    }

    प्रत्यागम EM_FALSE;
}

स्थिर EM_BOOL Emscripten_HandleResize(पूर्णाङ्क eventType, ध्रुव EmscriptenUiEvent *uiEvent, शून्य *userData)
{
    SDL_WindowData *window_data = userData;

    bool force = false;

    // update pixel ratio
    यदि (window_data->window->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY) {
        यदि (window_data->pixel_ratio != emscripten_get_device_pixel_ratio()) {
            window_data->pixel_ratio = emscripten_get_device_pixel_ratio();
            force = true;
        }
    }

    ध्रुव bool fill_document = (Emscripten_fill_document_window == window_data->window);
    ध्रुव bool fullscreen = (window_data->window->flags & SDL_WINDOW_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ध्रुव bool resizable = (window_data->window->flags & SDL_WINDOW_RESIZABLE) != 0;
    यदि (fill_document || fullscreen || resizable) {
        द्विगुण w, h;
        यदि (fill_document || fullscreen) {
            w = (द्विगुण) uiEvent->windowInnerWidth;
            h = (द्विगुण) uiEvent->windowInnerHeight;
        } अन्यथा {
            SDL_assert(window_data->window->flags & SDL_WINDOW_RESIZABLE);
            w = window_data->window->w;
            h = window_data->window->h;
            // this will only work if the canvas size is set through css
            यदि (window_data->external_size) {
                emscripten_get_element_css_size(window_data->canvas_id, &w, &h);
            }
        }

        emscripten_set_canvas_element_size(window_data->canvas_id, SDL_lroundf(w * window_data->pixel_ratio), SDL_lroundf(h * window_data->pixel_ratio));

        // set_canvas_size unsets this
        यदि (!window_data->external_size && window_data->pixel_ratio != 1.0f) {
            emscripten_set_element_css_size(window_data->canvas_id, w, h);
        }

        यदि (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            window_data->window->w = 0;
            window_data->window->h = 0;
        }

        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleResizeGlobal(पूर्णाङ्क eventType, ध्रुव EmscriptenUiEvent *uiEvent, शून्य *userData)
{
    SDL_VideoDevice *device = userData;
    bool prevent_default = false;
    SDL_Window *window;

    प्रति (window = device->windows; window; window = window->next) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, window->internal);
    }

    प्रत्यागम prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(पूर्णाङ्क eventType, ध्रुव शून्य *reserved, शून्य *userData)
{
    // this is used during fullscreen changes
    SDL_WindowData *window_data = userData;

    यदि (window_data->fullscreen_resize) {
        द्विगुण css_w, css_h;
        emscripten_get_element_css_size(window_data->canvas_id, &css_w, &css_h);
        SDL_SendWindowEvent(window_data->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleVisibilityChange(पूर्णाङ्क eventType, ध्रुव EmscriptenVisibilityChangeEvent *visEvent, शून्य *userData)
{
    SDL_WindowData *window_data = userData;
    SDL_SendWindowEvent(window_data->window, visEvent->hidden ? SDL_EVENT_WINDOW_HIDDEN : SDL_EVENT_WINDOW_SHOWN, 0, 0);
    प्रत्यागम 0;
}

स्थिर ध्रुव वर्ण *Emscripten_HandleBeforeUnload(पूर्णाङ्क eventType, ध्रुव शून्य *reserved, शून्य *userData)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    प्रत्यागम ""; // don't trigger confirmation dialog
}

स्थिर EM_BOOL Emscripten_HandleOrientationChange(पूर्णाङ्क eventType, ध्रुव EmscriptenOrientationChangeEvent *orientationChangeEvent, शून्य *userData)
{
    SDL_DisplayOrientation orientation;
    विकल्प (orientationChangeEvent->orientationIndex) {
        #define CHECK_ORIENTATION(emsdk, sdl) पक्ष EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; भङ्ग
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #undef CHECK_ORIENTATION
        स्वभाव: orientation = SDL_ORIENTATION_UNKNOWN; भङ्ग;
    }

    SDL_WindowData *window_data = (SDL_WindowData *) userData;
    SDL_SendDisplayEvent(SDL_GetVideoDisplayForWindow(window_data->window), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.documentBodyClientWidth = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम document.body.clientWidth; } );
    uiEvent.documentBodyClientHeight = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम document.body.clientHeight; } );
    uiEvent.windowInnerWidth = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.innerWidth; } );
    uiEvent.windowInnerHeight = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.innerHeight; } );
    uiEvent.windowOuterWidth = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.outerWidth; } );
    uiEvent.windowOuterHeight = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.outerHeight; } );
    uiEvent.scroll_शीर्ष = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.pageXOffset; } );
    uiEvent.scroll_डावा = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम window.pageYOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, userData);

    प्रत्यागम 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#define PTRTYPE_MOUSE 1
#define PTRTYPE_TOUCH 2
#define PTRTYPE_PEN 3
प्रकारनिर्देश संरचना Emscripten_PointerEvent
{
    पूर्णाङ्क pointer_type;
    पूर्णाङ्क pointerid;
    पूर्णाङ्क button;
    पूर्णाङ्क buttons;
    पूर्णाङ्क down;
    भिन्न movementX;
    भिन्न movementY;
    भिन्न targetX;
    भिन्न targetY;
    भिन्न pressure;
    भिन्न tangential_pressure;
    भिन्न tiltx;
    भिन्न tilty;
    भिन्न rotation;
} Emscripten_PointerEvent;

स्थिर शून्य Emscripten_HandleMouseButton(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    Uint8 sdl_button;
    bool down = false;
    विकल्प (event->button) {
        #define CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) पक्ष jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; down = (event->down != 0) || ((event->buttons & downflag) != 0); भङ्ग
        CHECK_MOUSE_BUTTON(0, 1, डावा_2);
        CHECK_MOUSE_BUTTON(1, 4, मधला_2);
        CHECK_MOUSE_BUTTON(2, 2, उजवा_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #undef CHECK_MOUSE_BUTTON
        स्वभाव: sdl_button = 0; भङ्ग;
    }

    यदि (sdl_button) {
        ध्रुव SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != रिक्त);

        यदि (down) {
            यदि (mouse->relative_mode && !window_data->has_pointer_lock) {
                emscripten_request_pointerlock(window_data->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, window_data->window, SDL_DEFAULT_MOUSE_ID, sdl_button, down);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        यदि (mouse->auto_capture) {
            यदि (SDL_GetMouseState(रिक्त, रिक्त) != 0) {
                window_data->window->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } अन्यथा {
                window_data->window->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;
            }
        }

        यदि (!down && window_data->mouse_focus_loss_pending) {
            window_data->mouse_focus_loss_pending = (window_data->window->flags & SDL_WINDOW_MOUSE_CAPTURE) != 0;
            यदि (!window_data->mouse_focus_loss_pending) {
                SDL_SetMouseFocus(रिक्त);
            }
        }
    }
}

स्थिर शून्य Emscripten_UpdateMouseFromEvent(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    यदि (window_data->window->flags & SDL_WINDOW_HIDDEN) {
        प्रत्यागम;
    }

    // rescale (in case canvas is being scaled)
    द्विगुण client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);
    ध्रुव द्विगुण xscale = window_data->window->w / client_w;
    ध्रुव द्विगुण yscale = window_data->window->h / client_h;

    ध्रुव bool isPointerLocked = window_data->has_pointer_lock;
    भिन्न mx, my;
    यदि (isPointerLocked) {
        mx = (भिन्न)(event->movementX * xscale);
        my = (भिन्न)(event->movementY * yscale);
    } अन्यथा {
        mx = (भिन्न)(event->targetX * xscale);
        my = (भिन्न)(event->targetY * yscale);
    }

    SDL_SendMouseMotion(0, window_data->window, SDL_DEFAULT_MOUSE_ID, isPointerLocked, mx, my);

    Emscripten_HandleMouseButton(window_data, event);
}

स्थिर शून्य Emscripten_UpdateTouchFromEvent(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ध्रुव SDL_TouchID deviceId = 1;
    यदि (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        प्रत्यागम;
    }

    द्विगुण client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

    ध्रुव SDL_FingerID id = event->pointerid + 1;
    भिन्न x, y;
    यदि (client_w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = event->targetX / (client_w - 1);
    }
    यदि (client_h <= 1) {
        y = 0.5f;
    } अन्यथा {
        y = event->targetY / (client_h - 1);
    }

    ध्रुव bool down = (event->buttons & 1) != 0;
    यदि (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        यदि (down) {
            SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, window_data->window, x, y, 1.0f);

    यदि (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        यदि (!down) {
            SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
        }
    }
}

स्थिर शून्य Emscripten_UpdatePenFromEvent(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);
    ध्रुव SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);   // something > 0 for the single pen handle.
    यदि (pen) {
        // rescale (in case canvas is being scaled)
        द्विगुण client_w, client_h;
        emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);
        ध्रुव द्विगुण xscale = window_data->window->w / client_w;
        ध्रुव द्विगुण yscale = window_data->window->h / client_h;

        ध्रुव bool isPointerLocked = window_data->has_pointer_lock;
        भिन्न mx, my;
        यदि (isPointerLocked) {
            mx = (भिन्न)(event->movementX * xscale);
            my = (भिन्न)(event->movementY * yscale);
        } अन्यथा {
            mx = (भिन्न)(event->targetX * xscale);
            my = (भिन्न)(event->targetY * yscale);
        }

        SDL_SendPenMotion(0, pen, window_data->window, mx, my);

        यदि (event->button == 0) {  // pen touch
            bool down = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, window_data->window, false, down);
        } अन्यथा यदि (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool down = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, window_data->window, true, down);
        } अन्यथा यदि (event->button == 1) {
            bool down = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, window_data->window, 2, down);
        } अन्यथा यदि (event->button == 2) {
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

स्थिर शून्य Emscripten_UpdatePointerFromEvent(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(window_data, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(window_data, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(window_data, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

स्थिर शून्य Emscripten_HandleMouseFocus(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event, bool isenter)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    यदि (window_data->window->flags & SDL_WINDOW_HIDDEN) {
        प्रत्यागम;
    }

    ध्रुव bool isPointerLocked = window_data->has_pointer_lock;

    यदि (!isPointerLocked) {
        // rescale (in case canvas is being scaled)
        भिन्न mx, my;
        द्विगुण client_w, client_h;
        emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

        mx = (भिन्न)(event->targetX * (window_data->window->w / client_w));
        my = (भिन्न)(event->targetY * (window_data->window->h / client_h));
        SDL_SendMouseMotion(0, window_data->window, SDL_GLOBAL_MOUSE_ID, isPointerLocked, mx, my);
    }

    यदि (isenter && window_data->mouse_focus_loss_pending) {
        window_data->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } अन्यथा यदि (!isenter && (window_data->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        window_data->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } अन्यथा {
        SDL_SetMouseFocus(isenter ? window_data->window : रिक्त);
    }
}

स्थिर शून्य Emscripten_HandlePenEnter(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);  // something > 0 for the single pen handle.
    यदि (pen) {
        SDL_SendPenProximity(0, pen, window_data->window, true, true);
    } अन्यथा {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.अंक_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_AddPenDevice(0, रिक्त, window_data->window, &peninfo, (शून्य *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(window_data, event);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerEnter(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_data, event, true);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(window_data, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        // do nothing.
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

स्थिर शून्य Emscripten_HandlePenLeave(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    ध्रुव SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);   // something > 0 for the single pen handle.
    यदि (pen) {
        Emscripten_UpdatePointerFromEvent(window_data, event);  // last data updates?
        SDL_SendPenProximity(0, pen, window_data->window, false, false);
    }
}

स्थिर शून्य Emscripten_HandleTouchCancel(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ध्रुव SDL_TouchID deviceId = 1;
    यदि (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        प्रत्यागम;
    }

    द्विगुण client_w, client_h;
    emscripten_get_element_css_size(window_data->canvas_id, &client_w, &client_h);

    ध्रुव SDL_FingerID id = event->pointerid + 1;
    भिन्न x, y;
    यदि (client_w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = event->targetX / (client_w - 1);
    }
    यदि (client_h <= 1) {
        y = 0.5f;
    } अन्यथा {
        y = event->targetY / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, window_data->window, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerLeave(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_data, event, false);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(window_data, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(window_data, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerGeneric(SDL_WindowData *window_data, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    Emscripten_UpdatePointerFromEvent(window_data, event);
}

स्थिर शून्य Emscripten_prep_pointer_event_callbacks(शून्य)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        यदि (SDL3.makePointerEventCStruct === undefined) {
            SDL3.makePointerEventCStruct = function(डावा, शीर्ष, event) {
                var ptrtype = 0;
                यदि (event.pointerType == "mouse") {
                    ptrtype = 1;
                } अन्यथा यदि (event.pointerType == "touch") {
                    ptrtype = 2;
                } अन्यथा यदि (event.pointerType == "pen") {
                    ptrtype = 3;
                } अन्यथा {
                    प्रत्यागम 0;
                }

                var ptr = _SDL_malloc($0);
                यदि (ptr != 0) {
                    var idx = SDL3.CPtrToHeap32Index(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.pointerId;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - डावा;
                    HEAPF32[idx++] = event.clientY - शीर्ष;
                    यदि (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                प्रत्यागम ptr;
            };
        }
    }, परिमाण (Emscripten_PointerEvent));
}

स्थिर शून्य Emscripten_set_pointer_event_callbacks(SDL_WindowData *data)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        यदि (target) {
            var SDL3 = Module['SDL3'];
            var data = $0;
            target.sdlEventHandlerPointerEnter = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.डावा, rect.शीर्ष, event);
                यदि (d != 0)
                {
                    _Emscripten_HandlePointerEnter(SDL3.JSVarToCPtr(data), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerLeave = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.डावा, rect.शीर्ष, event);
                यदि (d != 0)
                {
                    _Emscripten_HandlePointerLeave(SDL3.JSVarToCPtr(data), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerGeneric = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.डावा, rect.शीर्ष, event);
                यदि (d != 0)
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

स्थिर शून्य Emscripten_unset_pointer_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        यदि (target) {
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

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandleMouseButtonUpGlobal(SDL_VideoDevice *device, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(device != रिक्त);
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        प्रति (SDL_Window *window = device->windows; window; window = window->next) {
            Emscripten_HandleMouseButton(window->internal, event);
        }
    }
}

स्थिर शून्य Emscripten_set_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document;
        यदि (target) {
            target.sdlEventHandlerMouseButtonUpGlobal = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.makePointerEventCStruct(0, 0, event);
                यदि (d != 0)
                {
                    _Emscripten_HandleMouseButtonUpGlobal(SDL3.JSVarToCPtr($0), d);
                    _SDL_free(d);
                }
            };
            target.addEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
        }
    }, device);
}

स्थिर शून्य Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var target = document;
        यदि (target) {
            target.removeEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
            target.sdlEventHandlerMouseButtonUpGlobal = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
प्रकारनिर्देश संरचना Emscripten_DropEvent
{
    पूर्णाङ्क x;
    पूर्णाङ्क y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragEvent(SDL_WindowData *window_data, ध्रुव Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(window_data->window, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragCompleteEvent(SDL_WindowData *window_data)
{
    SDL_SendDropComplete(window_data->window);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragTextEvent(SDL_WindowData *window_data, वर्ण *text)
{
    SDL_SendDropText(window_data->window, text);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragFileEvent(SDL_WindowData *window_data, वर्ण *filename)
{
    SDL_SendDropFile(window_data->window, रिक्त, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

स्थिर शून्य Emscripten_set_drag_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        यदि (target) {
            var data = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                यदि (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = target.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.डावा;
                    HEAP32[idx++] = event.clientY - rect.शीर्ष;
                }
                प्रत्यागम ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); यदि (d != 0) { _Emscripten_SendDragEvent(data, d); _SDL_free(d); }
            };
            target.addEventListener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_मोजणी = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                यदि (event.dataTransfer.types.includes("text/plain")) {
                    let plain_text = stringToNewUTF8(event.dataTransfer.getData("text/plain"));
                    _Emscripten_SendDragTextEvent(data, plain_text);
                    _Emscripten_force_free(plain_text);
                } अन्यथा यदि (event.dataTransfer.types.includes("Files")) {
                    let files_read = 0;
                    ध्रुव files_to_read = event.dataTransfer.files.length;
                    प्रति (let i = 0; i < files_to_read; i++) {
                        ध्रुव file = event.dataTransfer.files.item(i);
                        ध्रुव file_reader = new FileReader();
                        file_reader.readAsArrayBuffer(file);
                        file_reader.onload = function(event) {
                            ध्रुव fs_dropdir = `/tmp/filedrop/${SDL3.drop_मोजणी}`;
                            SDL3.drop_मोजणी += 1;

                            ध्रुव fs_filepath = `${fs_dropdir}/${file.name}`;
                            ध्रुव c_fs_filepath = stringToNewUTF8(fs_filepath);
                            ध्रुव contents_array8 = new Uint8Array(event.target.result);

                            try {
                                FS.mkdir(fs_dropdir);
                                var stream = FS.open(fs_filepath, "w");
                                FS.लिख(stream, contents_array8, 0, contents_array8.length, 0);
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
                        यदि (files_read === files_to_read) {
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
    }, data, data->canvas_id, परिमाण (Emscripten_DropEvent));
}

स्थिर शून्य Emscripten_unset_drag_event_callbacks(SDL_WindowData *data)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        यदि (target) {
            var SDL3 = Module['SDL3'];
            target.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            target.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_मोजणी = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ध्रुव p = `${dirpath}/${filename}`;
                    ध्रुव p_s = FS.stat(p);
                    यदि (FS.isFile(p_s.mode)) {
                        FS.unlink(p);
                    } अन्यथा यदि (FS.isDir(p)) {
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

स्थिर ध्रुव वर्ण *Emscripten_GetKeyboardTargetElement(ध्रुव वर्ण *target)
{
    यदि (SDL_strcmp(target, "#none") == 0) {
        प्रत्यागम रिक्त;
    } अन्यथा यदि (SDL_strcmp(target, "#window") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_WINDOW;
    } अन्यथा यदि (SDL_strcmp(target, "#document") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_DOCUMENT;
    } अन्यथा यदि (SDL_strcmp(target, "#screen") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_SCREEN;
    }

    प्रत्यागम target;
}

शून्य Emscripten_RegisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_set_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandlePointerLockChangeGlobal);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleResizeGlobal);
}

शून्य Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, रिक्त, 0, रिक्त);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, रिक्त, 0, रिक्त);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, रिक्त, 0, रिक्त);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, रिक्त, 0, रिक्त);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, रिक्त, 0, रिक्त);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_Handle_Lock_किल्ल्या_Check(SDL_WindowData *window_data, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ध्रुव SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_अंक : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    यदि ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_अंक|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_अंक|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_SetModState(modstate);
    }
}

शून्य Emscripten_RegisterEventHandlers(SDL_WindowData *data)
{
    ध्रुव वर्ण *किल्ली_Element;

    // There is only one window and that window is the canvas
    emscripten_set_wheel_callback(data->canvas_id, data, 0, Emscripten_HandleWheel);

    emscripten_set_orientationchange_callback(data, 0, Emscripten_HandleOrientationChange);

    किल्ली_Element = Emscripten_GetKeyboardTargetElement(data->keyboard_element);
    यदि (किल्ली_Element) {
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
        emscripten_set_keydown_callback(किल्ली_Element, रिक्त, 0, रिक्त);
        emscripten_set_keyup_callback(किल्ली_Element, रिक्त, 0, रिक्त);
        emscripten_set_keypress_callback(किल्ली_Element, रिक्त, 0, रिक्त);

        MAIN_THREAD_EM_ASM_INT({
            var data = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            यदि (document.sdl_Event_Handler_Lock_किल्ल्या_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_किल्ल्या_Check);
            }

            document.sdl_Event_Handler_Lock_किल्ल्या_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                यदि ((event.किल्ली != "CapsLock") && (event.किल्ली != "NumLock") && (event.किल्ली != "ScrollLock"))
                {
                    Emscripten_Handle_Lock_किल्ल्या_Check_2(Module['SDL3'].JSVarToCPtr(data), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.addEventListener("keydown", document.sdl_Event_Handler_Lock_किल्ल्या_Check);
        }, data);
        emscripten_set_keydown_callback(किल्ली_Element, data, 0, Emscripten_Handle_किल्ली);
        emscripten_set_keyup_callback(किल्ली_Element, data, 0, Emscripten_Handle_किल्ली);
        emscripten_set_keypress_callback(किल्ली_Element, data, 0, Emscripten_Handle_किल्ली_Press);
    }

    emscripten_set_visibilitychange_callback(data, 0, Emscripten_HandleVisibilityChange);

    emscripten_set_beforeunload_callback(data, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_set_pointer_event_callbacks(data);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_set_drag_event_callbacks(data);
}

शून्य Emscripten_UnregisterEventHandlers(SDL_WindowData *data)
{
    ध्रुव वर्ण *किल्ली_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(data);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_pointer_event_callbacks(data);

    // only works due to having one window
    emscripten_set_wheel_callback(data->canvas_id, रिक्त, 0, रिक्त);

    emscripten_set_orientationchange_callback(रिक्त, 0, रिक्त);

    किल्ली_Element = Emscripten_GetKeyboardTargetElement(data->keyboard_element);
    यदि (किल्ली_Element) {
        emscripten_set_keydown_callback(किल्ली_Element, रिक्त, 0, रिक्त);
        emscripten_set_keyup_callback(किल्ली_Element, रिक्त, 0, रिक्त);
        emscripten_set_keypress_callback(किल्ली_Element, रिक्त, 0, रिक्त);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_किल्ल्या_Check);
        });
    }

    emscripten_set_visibilitychange_callback(रिक्त, 0, रिक्त);

    emscripten_set_beforeunload_callback(रिक्त, रिक्त);
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN
