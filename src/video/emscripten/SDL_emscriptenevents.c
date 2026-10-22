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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_EMSCRIPTEN

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
स्थिर ध्रुव SDL_Scancode emscripten_scancode_सारणी[] = {
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

स्थिर SDL_Scancode Emscripten_Map_अवलोकनम्_संहिता(ध्रुव वर्ण *संहिता)
{
    ध्रुव DOM_PK_संहिता_TYPE pk_संहिता = emscripten_compute_dom_pk_संहिता(संहिता);
    यदि (pk_संहिता < SDL_arraysize(emscripten_scancode_सारणी)) {
        प्रत्यागम emscripten_scancode_सारणी[pk_संहिता];
    }

    विकल्प (pk_संहिता) {
    पक्ष DOM_PK_PASTE:
        प्रत्यागम SDL_SCANCODE_PASTE;
    पक्ष DOM_PK_MEDIA_TRACK_PREVIOUS:
        प्रत्यागम SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
    पक्ष DOM_PK_CUT:
        प्रत्यागम SDL_SCANCODE_CUT;
    पक्ष DOM_PK_COPY:
        प्रत्यागम SDL_SCANCODE_COPY;
    पक्ष DOM_PK_MEDIA_TRACK_अग्र:
        प्रत्यागम SDL_SCANCODE_MEDIA_अग्र_TRACK;
    पक्ष DOM_PK_NUMPAD_ENTER:
        प्रत्यागम SDL_SCANCODE_KP_ENTER;
    पक्ष DOM_PK_CONTROL_दक्षिणः:
        प्रत्यागम SDL_SCANCODE_RCTRL;
    पक्ष DOM_PK_AUDIO_VOLUME_MUTE:
        प्रत्यागम SDL_SCANCODE_MUTE;
    पक्ष DOM_PK_MEDIA_PLAY_PAUSE:
        प्रत्यागम SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    पक्ष DOM_PK_MEDIA_STOP:
        प्रत्यागम SDL_SCANCODE_MEDIA_STOP;
    पक्ष DOM_PK_EJECT:
        प्रत्यागम SDL_SCANCODE_MEDIA_EJECT;
    पक्ष DOM_PK_AUDIO_VOLUME_अधस्तात्:
        प्रत्यागम SDL_SCANCODE_VOLUMEDOWN;
    पक्ष DOM_PK_AUDIO_VOLUME_ऊर्ध्वम्:
        प्रत्यागम SDL_SCANCODE_VOLUMEUP;
    पक्ष DOM_PK_BROWSER_HOME:
        प्रत्यागम SDL_SCANCODE_AC_HOME;
    पक्ष DOM_PK_NUMPAD_DIVIDE:
        प्रत्यागम SDL_SCANCODE_KP_DIVIDE;
    पक्ष DOM_PK_ALT_दक्षिणः:
        प्रत्यागम SDL_SCANCODE_RALT;
    पक्ष DOM_PK_HELP:
        प्रत्यागम SDL_SCANCODE_HELP;
    पक्ष DOM_PK_अङ्कः_तालकम्:
        प्रत्यागम SDL_SCANCODE_NUMLOCKCLEAR;
    पक्ष DOM_PK_HOME:
        प्रत्यागम SDL_SCANCODE_HOME;
    पक्ष DOM_PK_ARROW_ऊर्ध्वम्:
        प्रत्यागम SDL_SCANCODE_ऊर्ध्वम्;
    पक्ष DOM_PK_PAGE_ऊर्ध्वम्:
        प्रत्यागम SDL_SCANCODE_PAGEUP;
    पक्ष DOM_PK_ARROW_वामः:
        प्रत्यागम SDL_SCANCODE_वामः;
    पक्ष DOM_PK_ARROW_दक्षिणः:
        प्रत्यागम SDL_SCANCODE_दक्षिणः;
    पक्ष DOM_PK_अन्तः:
        प्रत्यागम SDL_SCANCODE_अन्तः;
    पक्ष DOM_PK_ARROW_अधस्तात्:
        प्रत्यागम SDL_SCANCODE_अधस्तात्;
    पक्ष DOM_PK_PAGE_अधस्तात्:
        प्रत्यागम SDL_SCANCODE_PAGEDOWN;
    पक्ष DOM_PK_निवेशय:
        प्रत्यागम SDL_SCANCODE_निवेशय;
    पक्ष DOM_PK_DELETE:
        प्रत्यागम SDL_SCANCODE_DELETE;
    पक्ष DOM_PK_META_वामः:
        प्रत्यागम SDL_SCANCODE_LGUI;
    पक्ष DOM_PK_META_दक्षिणः:
        प्रत्यागम SDL_SCANCODE_RGUI;
    पक्ष DOM_PK_CONTEXT_MENU:
        प्रत्यागम SDL_SCANCODE_APPLICATION;
    पक्ष DOM_PK_POWER:
        प्रत्यागम SDL_SCANCODE_POWER;
    पक्ष DOM_PK_BROWSER_अन्वेषणम्:
        प्रत्यागम SDL_SCANCODE_AC_अन्वेषणम्;
    पक्ष DOM_PK_BROWSER_FAVORITES:
        प्रत्यागम SDL_SCANCODE_AC_BOOKMARKS;
    पक्ष DOM_PK_BROWSER_REFRESH:
        प्रत्यागम SDL_SCANCODE_AC_REFRESH;
    पक्ष DOM_PK_BROWSER_STOP:
        प्रत्यागम SDL_SCANCODE_AC_STOP;
    पक्ष DOM_PK_BROWSER_FORWARD:
        प्रत्यागम SDL_SCANCODE_AC_FORWARD;
    पक्ष DOM_PK_BROWSER_पृष्ठभागः:
        प्रत्यागम SDL_SCANCODE_AC_पृष्ठभागः;
    पक्ष DOM_PK_MEDIA_SELECT:
        प्रत्यागम SDL_SCANCODE_MEDIA_SELECT;
    }

    प्रत्यागम SDL_SCANCODE_UNKNOWN;
}

स्थिर SDL_गवाक्षः *Emscripten_Get_Focused_गवाक्षः(SDL_VideoDevice *device)
{
    SDL_गवाक्षः *गवाक्षः;
    प्रति (गवाक्षः = device->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        SDL_गवाक्षः_दत्त *wdata = गवाक्षः->आन्तरिकम्;

        ध्रुव पूर्णाङ्क focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_गन्तव्यम्_String($0);
            try
            {
                var canvas = document.querySelector(id);
                यदि (canvas) {
                    प्रत्यागम canvas === document.सक्रिय_Element;
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
    यदि (!गवाक्षः) {
        ध्रुव पूर्णाङ्क focused = MAIN_THREAD_EM_ASM_INT({
            प्रत्यागम document.hasFocus();
        });
        यदि (focused) {
            गवाक्षः = device->windows;
        }
    }
    प्रत्यागम गवाक्षः;
}

स्थिर EM_BOOL Emscripten_Handle_Pointer_तालकम्_Change(पूर्णाङ्क eventType, ध्रुव EmscriptenPointerlockChangeEvent *changeEvent, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = (SDL_गवाक्षः_दत्त *)user_दत्त;
    // keep track of lock losses, so we can regrab if/when appropriate.
    गवाक्षः_दत्त_2->has_pointer_तालकम् = changeEvent->is_सक्रिय;
    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_Handle_Pointer_तालकम्_Change_Global(पूर्णाङ्क eventType, ध्रुव EmscriptenPointerlockChangeEvent *changeEvent, शून्य *user_दत्त)
{
    SDL_VideoDevice *device = user_दत्त;
    bool prevent_default = false;
    SDL_गवाक्षः *गवाक्षः;

    प्रति (गवाक्षः = device->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        prevent_default |= Emscripten_Handle_Pointer_तालकम्_Change(eventType, changeEvent, गवाक्षः->आन्तरिकम्);
    }

    प्रत्यागम prevent_default;
}

स्थिर EM_BOOL Emscripten_HandleWheel(पूर्णाङ्क eventType, ध्रुव EmscriptenWheelEvent *wheelEvent, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = user_दत्त;

    भिन्न deltaY = wheelEvent->deltaY;
    भिन्न deltaX = wheelEvent->deltaX;

    विकल्प (wheelEvent->delta_बहुलकम्) {
    पक्ष DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        भङ्ग;
    पक्ष DOM_DELTA_पङ्क्तिः:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        भङ्ग;
    पक्ष DOM_DELTA_PAGE:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        भङ्ग;
    }

    SDL_SendMouseWheel(0, गवाक्षः_दत्त_2->गवाक्षः, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_प्रसामान्यम्);
    प्रत्यागम SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

स्थिर EM_BOOL Emscripten_HandleFocus(पूर्णाङ्क eventType, ध्रुव EmscriptenFocusEvent *focusEvent, शून्य *user_दत्त)
{
    SDL_VideoDevice *device = user_दत्त;
    SDL_गवाक्षः *गवाक्षः = Emscripten_Get_Focused_गवाक्षः(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    यदि (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_गवाक्षः_FOCUS_GAINED : SDL_EVENT_गवाक्षः_FOCUS_नष्टम्;
    SDL_समुच्चयः_Keyboard_Focus(sdl_event_type == SDL_EVENT_गवाक्षः_FOCUS_GAINED ? गवाक्षः : रिक्त);
    प्रत्यागम SDL_EventEnabled(sdl_event_type);
}

स्थिर bool Is_Function_कुञ्चिका(SDL_Scancode scancode)
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
स्थिर EM_BOOL Emscripten_Handle_कुञ्चिका(पूर्णाङ्क eventType, ध्रुव EmscriptenKeyboardEvent *कुञ्चिका_Event, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = (SDL_गवाक्षः_दत्त *)user_दत्त;
    SDL_Scancode scancode = Emscripten_Map_अवलोकनम्_संहिता(कुञ्चिका_Event->संहिता);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_कुञ्चिका = false;

    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
        यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_लेखः;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    यदि (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } अन्यथा यदि (SDL_strcmp(कुञ्चिका_Event->कुञ्चिका, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_पृष्ठभागः;
        }
    }

    यदि (कुञ्चिका_Event->location == 0 && SDL_utf8strlen(कुञ्चिका_Event->कुञ्चिका) == 1) {
        ध्रुव वर्ण *कुञ्चिका = कुञ्चिका_Event->कुञ्चिका;
        keycode = SDL_चरणः_UTF8(&कुञ्चिका, रिक्त);
        यदि (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    यदि (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_कुञ्चिका_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } अन्यथा {
        prevent_default = SDL_Send_Keyboard_कुञ्चिका(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    यदि ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_वामः) ||
        (scancode == SDL_SCANCODE_ऊर्ध्वम्) ||
        (scancode == SDL_SCANCODE_दक्षिणः) ||
        (scancode == SDL_SCANCODE_अधस्तात्) ||
        Is_Function_कुञ्चिका(scancode) ||
        कुञ्चिका_Event->ctrl_कुञ्चिका) {
        is_nav_कुञ्चिका = true;
    }

    यदि ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_Text_निवेशः_सक्रिय(गवाक्षः_दत्त_2->गवाक्षः) && !is_nav_कुञ्चिका) {
        prevent_default = false;
    }

    प्रत्यागम prevent_default;
}

स्थिर EM_BOOL Emscripten_Handle_कुञ्चिका_Press(पूर्णाङ्क eventType, ध्रुव EmscriptenKeyboardEvent *कुञ्चिका_Event, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = (SDL_गवाक्षः_दत्त *)user_दत्त;

    यदि (SDL_Text_निवेशः_सक्रिय(गवाक्षः_दत्त_2->गवाक्षः)) {
        यदि (SDL_utf8strlen(कुञ्चिका_Event->कुञ्चिका) == 1) {
            SDL_SendKeyboardText(कुञ्चिका_Event->कुञ्चिका);
            प्रत्यागम EM_TRUE;
        }
    }
    प्रत्यागम EM_FALSE;
}

स्थिर EM_BOOL Emscripten_HandleFullscreenChange(पूर्णाङ्क eventType, ध्रुव EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = user_दत्त;

    गवाक्षः_दत्त_2->fullscreen_change_अन्तर्_प्रगतिः = false;

    यदि (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_गवाक्षः_Event(गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN, 0, 0);
        गवाक्षः_दत्त_2->fullscreen_बहुलकम्_flags = 0;
    } अन्यथा {
        SDL_Send_गवाक्षः_Event(गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_बहुलकम्(गवाक्षः_दत्त_2->गवाक्षः, fullscreenChangeEvent->isFullscreen, false);

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleFullscreenChangeGlobal(पूर्णाङ्क eventType, ध्रुव EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, शून्य *user_दत्त)
{
    SDL_VideoDevice *device = user_दत्त;
    SDL_गवाक्षः *गवाक्षः = रिक्त;
    प्रति (गवाक्षः = device->windows; गवाक्षः != रिक्त; गवाक्षः = गवाक्षः->अग्र) {
        ध्रुव वर्ण *canvas_id = गवाक्षः->आन्तरिकम्->canvas_id;
        यदि (*canvas_id == '#') {
            canvas_id++;
        }
        यदि (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            भङ्ग;  // this is the window.
        }
    }

    यदि (गवाक्षः) {
        प्रत्यागम Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, गवाक्षः->आन्तरिकम्);
    }

    प्रत्यागम EM_FALSE;
}

स्थिर EM_BOOL Emscripten_HandleResize(पूर्णाङ्क eventType, ध्रुव EmscriptenUiEvent *uiEvent, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = user_दत्त;

    bool force = false;

    // update pixel ratio
    यदि (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) {
        यदि (गवाक्षः_दत्त_2->pixel_अनुपातः != emscripten_get_device_pixel_अनुपातः()) {
            गवाक्षः_दत्त_2->pixel_अनुपातः = emscripten_get_device_pixel_अनुपातः();
            force = true;
        }
    }

    ध्रुव bool fill_document = (Emscripten_fill_document_गवाक्षः == गवाक्षः_दत्त_2->गवाक्षः);
    ध्रुव bool fullscreen = (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ध्रुव bool resizable = (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) != 0;
    यदि (fill_document || fullscreen || resizable) {
        द्विगुण w, h;
        यदि (fill_document || fullscreen) {
            w = (द्विगुण) uiEvent->गवाक्षः_Inner_विस्तारः;
            h = (द्विगुण) uiEvent->गवाक्षः_Inner_Height;
        } अन्यथा {
            SDL_assert(गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE);
            w = गवाक्षः_दत्त_2->गवाक्षः->w;
            h = गवाक्षः_दत्त_2->गवाक्षः->h;
            // this will only work if the canvas size is set through css
            यदि (गवाक्षः_दत्त_2->external_आकार) {
                emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &w, &h);
            }
        }

        emscripten_समुच्चयः_canvas_element_आकार(गवाक्षः_दत्त_2->canvas_id, SDL_lroundf(w * गवाक्षः_दत्त_2->pixel_अनुपातः), SDL_lroundf(h * गवाक्षः_दत्त_2->pixel_अनुपातः));

        // set_canvas_size unsets this
        यदि (!गवाक्षः_दत्त_2->external_आकार && गवाक्षः_दत्त_2->pixel_अनुपातः != 1.0f) {
            emscripten_समुच्चयः_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, w, h);
        }

        यदि (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            गवाक्षः_दत्त_2->गवाक्षः->w = 0;
            गवाक्षः_दत्त_2->गवाक्षः->h = 0;
        }

        SDL_Send_गवाक्षः_Event(गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleResizeGlobal(पूर्णाङ्क eventType, ध्रुव EmscriptenUiEvent *uiEvent, शून्य *user_दत्त)
{
    SDL_VideoDevice *device = user_दत्त;
    bool prevent_default = false;
    SDL_गवाक्षः *गवाक्षः;

    प्रति (गवाक्षः = device->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, गवाक्षः->आन्तरिकम्);
    }

    प्रत्यागम prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(पूर्णाङ्क eventType, ध्रुव शून्य *reserved, शून्य *user_दत्त)
{
    // this is used during fullscreen changes
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = user_दत्त;

    यदि (गवाक्षः_दत्त_2->fullscreen_resize) {
        द्विगुण css_w, css_h;
        emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &css_w, &css_h);
        SDL_Send_गवाक्षः_Event(गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    प्रत्यागम 0;
}

स्थिर EM_BOOL Emscripten_HandleVisibilityChange(पूर्णाङ्क eventType, ध्रुव EmscriptenVisibilityChangeEvent *visEvent, शून्य *user_दत्त)
{
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = user_दत्त;
    SDL_Send_गवाक्षः_Event(गवाक्षः_दत्त_2->गवाक्षः, visEvent->hidden ? SDL_EVENT_गवाक्षः_HIDDEN : SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
    प्रत्यागम 0;
}

स्थिर ध्रुव वर्ण *Emscripten_HandleBeforeUnload(पूर्णाङ्क eventType, ध्रुव शून्य *reserved, शून्य *user_दत्त)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    प्रत्यागम ""; // don't trigger confirmation dialog
}

स्थिर EM_BOOL Emscripten_HandleOrientationChange(पूर्णाङ्क eventType, ध्रुव EmscriptenOrientationChangeEvent *orientationChangeEvent, शून्य *user_दत्त)
{
    SDL_DisplayOrientation orientation;
    विकल्प (orientationChangeEvent->orientation_सूचकांक) {
        #परिभाषय CHECK_ORIENTATION(emsdk, sdl) पक्ष EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; भङ्ग
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #अपरिभाषय CHECK_ORIENTATION
        स्वभाव: orientation = SDL_ORIENTATION_UNKNOWN; भङ्ग;
    }

    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = (SDL_गवाक्षः_दत्त *) user_दत्त;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः_दत्त_2->गवाक्षः), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_विस्तारः = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम document.body.client_विस्तारः; } );
    uiEvent.documentBodyClientHeight = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम document.body.clientHeight; } );
    uiEvent.गवाक्षः_Inner_विस्तारः = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.inner_विस्तारः; } );
    uiEvent.गवाक्षः_Inner_Height = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.innerHeight; } );
    uiEvent.गवाक्षः_Outer_विस्तारः = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.outer_विस्तारः; } );
    uiEvent.गवाक्षः_Outer_Height = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.outerHeight; } );
    uiEvent.scroll_शिखरम् = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.pageXOffset; } );
    uiEvent.scroll_वामः = MAIN_THREAD_EM_ASM_INT( { प्रत्यागम गवाक्षः.pageYOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_दत्त);

    प्रत्यागम 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#परिभाषय PTRTYPE_MOUSE 1
#परिभाषय PTRTYPE_TOUCH 2
#परिभाषय PTRTYPE_PEN 3
प्रकारनिर्देश संरचना Emscripten_PointerEvent
{
    पूर्णाङ्क pointer_type;
    पूर्णाङ्क pointerid;
    पूर्णाङ्क button;
    पूर्णाङ्क buttons;
    पूर्णाङ्क अधस्तात्;
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

स्थिर शून्य Emscripten_HandleMouseButton(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    Uint8 sdl_button;
    bool अधस्तात् = false;
    विकल्प (event->button) {
        #परिभाषय CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) पक्ष jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; अधस्तात् = (event->अधस्तात् != 0) || ((event->buttons & downflag) != 0); भङ्ग
        CHECK_MOUSE_BUTTON(0, 1, वामः_2);
        CHECK_MOUSE_BUTTON(1, 4, मध्यः_2);
        CHECK_MOUSE_BUTTON(2, 2, दक्षिणः_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #अपरिभाषय CHECK_MOUSE_BUTTON
        स्वभाव: sdl_button = 0; भङ्ग;
    }

    यदि (sdl_button) {
        ध्रुव SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != रिक्त);

        यदि (अधस्तात्) {
            यदि (mouse->relative_बहुलकम् && !गवाक्षः_दत्त_2->has_pointer_तालकम्) {
                emscripten_request_pointerlock(गवाक्षः_दत्त_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, गवाक्षः_दत्त_2->गवाक्षः, SDL_DEFAULT_MOUSE_ID, sdl_button, अधस्तात्);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        यदि (mouse->auto_capture) {
            यदि (SDL_GetMouseState(रिक्त, रिक्त) != 0) {
                गवाक्षः_दत्त_2->गवाक्षः->flags |= SDL_गवाक्षः_MOUSE_CAPTURE;
            } अन्यथा {
                गवाक्षः_दत्त_2->गवाक्षः->flags &= ~SDL_गवाक्षः_MOUSE_CAPTURE;
            }
        }

        यदि (!अधस्तात् && गवाक्षः_दत्त_2->mouse_focus_loss_pending) {
            गवाक्षः_दत्त_2->mouse_focus_loss_pending = (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE) != 0;
            यदि (!गवाक्षः_दत्त_2->mouse_focus_loss_pending) {
                SDL_समुच्चयः_Mouse_Focus(रिक्त);
            }
        }
    }
}

स्थिर शून्य Emscripten_UpdateMouseFromEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    यदि (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        प्रत्यागम;
    }

    // rescale (in case canvas is being scaled)
    द्विगुण client_w, client_h;
    emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &client_w, &client_h);
    ध्रुव द्विगुण xscale = गवाक्षः_दत्त_2->गवाक्षः->w / client_w;
    ध्रुव द्विगुण yscale = गवाक्षः_दत्त_2->गवाक्षः->h / client_h;

    ध्रुव bool isPointerLocked = गवाक्षः_दत्त_2->has_pointer_तालकम्;
    भिन्न mx, my;
    यदि (isPointerLocked) {
        mx = (भिन्न)(event->movementX * xscale);
        my = (भिन्न)(event->movementY * yscale);
    } अन्यथा {
        mx = (भिन्न)(event->targetX * xscale);
        my = (भिन्न)(event->targetY * yscale);
    }

    SDL_SendMouseMotion(0, गवाक्षः_दत्त_2->गवाक्षः, SDL_DEFAULT_MOUSE_ID, isPointerLocked, mx, my);

    Emscripten_HandleMouseButton(गवाक्षः_दत्त_2, event);
}

स्थिर शून्य Emscripten_UpdateTouchFromEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ध्रुव SDL_TouchID deviceId = 1;
    यदि (SDL_सङ्कलय_Touch(deviceId, SDL_TOUCH_DEVICE_प्रत्यक्षम्, "") < 0) {
        प्रत्यागम;
    }

    द्विगुण client_w, client_h;
    emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &client_w, &client_h);

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

    ध्रुव bool अधस्तात् = (event->buttons & 1) != 0;
    यदि (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        यदि (अधस्तात्) {
            SDL_SendTouch(0, deviceId, id, गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_FINGER_अधस्तात्, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, गवाक्षः_दत्त_2->गवाक्षः, x, y, 1.0f);

    यदि (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        यदि (!अधस्तात्) {
            SDL_SendTouch(0, deviceId, id, गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_FINGER_ऊर्ध्वम्, x, y, 1.0f);
        }
    }
}

स्थिर शून्य Emscripten_UpdatePenFromEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);
    ध्रुव SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);   // something > 0 for the single pen handle.
    यदि (pen) {
        // rescale (in case canvas is being scaled)
        द्विगुण client_w, client_h;
        emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &client_w, &client_h);
        ध्रुव द्विगुण xscale = गवाक्षः_दत्त_2->गवाक्षः->w / client_w;
        ध्रुव द्विगुण yscale = गवाक्षः_दत्त_2->गवाक्षः->h / client_h;

        ध्रुव bool isPointerLocked = गवाक्षः_दत्त_2->has_pointer_तालकम्;
        भिन्न mx, my;
        यदि (isPointerLocked) {
            mx = (भिन्न)(event->movementX * xscale);
            my = (भिन्न)(event->movementY * yscale);
        } अन्यथा {
            mx = (भिन्न)(event->targetX * xscale);
            my = (भिन्न)(event->targetY * yscale);
        }

        SDL_SendPenMotion(0, pen, गवाक्षः_दत्त_2->गवाक्षः, mx, my);

        यदि (event->button == 0) {  // pen touch
            bool अधस्तात् = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, गवाक्षः_दत्त_2->गवाक्षः, false, अधस्तात्);
        } अन्यथा यदि (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool अधस्तात् = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, गवाक्षः_दत्त_2->गवाक्षः, true, अधस्तात्);
        } अन्यथा यदि (event->button == 1) {
            bool अधस्तात् = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, गवाक्षः_दत्त_2->गवाक्षः, 2, अधस्तात्);
        } अन्यथा यदि (event->button == 2) {
            bool अधस्तात् = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, गवाक्षः_दत्त_2->गवाक्षः, 1, अधस्तात्);
        }

        SDL_SendPenAxis(0, pen, गवाक्षः_दत्त_2->गवाक्षः, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, गवाक्षः_दत्त_2->गवाक्षः, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, गवाक्षः_दत्त_2->गवाक्षः, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, गवाक्षः_दत्त_2->गवाक्षः, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, गवाक्षः_दत्त_2->गवाक्षः, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

स्थिर शून्य Emscripten_UpdatePointerFromEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(गवाक्षः_दत्त_2, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(गवाक्षः_दत्त_2, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(गवाक्षः_दत्त_2, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

स्थिर शून्य Emscripten_HandleMouseFocus(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event, bool isenter)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    यदि (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        प्रत्यागम;
    }

    ध्रुव bool isPointerLocked = गवाक्षः_दत्त_2->has_pointer_तालकम्;

    यदि (!isPointerLocked) {
        // rescale (in case canvas is being scaled)
        भिन्न mx, my;
        द्विगुण client_w, client_h;
        emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &client_w, &client_h);

        mx = (भिन्न)(event->targetX * (गवाक्षः_दत्त_2->गवाक्षः->w / client_w));
        my = (भिन्न)(event->targetY * (गवाक्षः_दत्त_2->गवाक्षः->h / client_h));
        SDL_SendMouseMotion(0, गवाक्षः_दत्त_2->गवाक्षः, SDL_GLOBAL_MOUSE_ID, isPointerLocked, mx, my);
    }

    यदि (isenter && गवाक्षः_दत्त_2->mouse_focus_loss_pending) {
        गवाक्षः_दत्त_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } अन्यथा यदि (!isenter && (गवाक्षः_दत्त_2->गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
        गवाक्षः_दत्त_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } अन्यथा {
        SDL_समुच्चयः_Mouse_Focus(isenter ? गवाक्षः_दत्त_2->गवाक्षः : रिक्त);
    }
}

स्थिर शून्य Emscripten_HandlePenEnter(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);  // something > 0 for the single pen handle.
    यदि (pen) {
        SDL_SendPenProximity(0, pen, गवाक्षः_दत्त_2->गवाक्षः, true, true);
    } अन्यथा {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.अङ्कः_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_सङ्कलय_Pen_Device(0, रिक्त, गवाक्षः_दत्त_2->गवाक्षः, &peninfo, (शून्य *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(गवाक्षः_दत्त_2, event);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerEnter(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(गवाक्षः_दत्त_2, event, true);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(गवाक्षः_दत्त_2, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        // do nothing.
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

स्थिर शून्य Emscripten_HandlePenLeave(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    ध्रुव SDL_PenID pen = SDL_FindPenByHandle((शून्य *) (size_t) 1);   // something > 0 for the single pen handle.
    यदि (pen) {
        Emscripten_UpdatePointerFromEvent(गवाक्षः_दत्त_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, गवाक्षः_दत्त_2->गवाक्षः, false, false);
    }
}

स्थिर शून्य Emscripten_HandleTouchCancel(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ध्रुव SDL_TouchID deviceId = 1;
    यदि (SDL_सङ्कलय_Touch(deviceId, SDL_TOUCH_DEVICE_प्रत्यक्षम्, "") < 0) {
        प्रत्यागम;
    }

    द्विगुण client_w, client_h;
    emscripten_get_element_css_आकार(गवाक्षः_दत्त_2->canvas_id, &client_w, &client_h);

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

    SDL_SendTouch(0, deviceId, id, गवाक्षः_दत्त_2->गवाक्षः, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerLeave(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(गवाक्षः_दत्त_2, event, false);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(गवाक्षः_दत्त_2, event);
    } अन्यथा यदि (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(गवाक्षः_दत्त_2, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_HandlePointerGeneric(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(event != रिक्त);
    Emscripten_UpdatePointerFromEvent(गवाक्षः_दत्त_2, event);
}

स्थिर शून्य Emscripten_prep_pointer_event_callbacks(शून्य)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        यदि (SDL3.makePointerEventCStruct === undefined) {
            SDL3.makePointerEventCStruct = function(वामः, शिखरम्, event) {
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
                    var idx = SDL3.CPtr_गन्तव्यम्_Heap32_सूचकांक(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.pointerId;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - वामः;
                    HEAPF32[idx++] = event.clientY - शिखरम्;
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

स्थिर शून्य Emscripten_समुच्चयः_pointer_event_callbacks(SDL_गवाक्षः_दत्त *दत्त)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8_गन्तव्यम्_String($1));
        यदि (target) {
            var SDL3 = Module['SDL3'];
            var दत्त = $0;
            target.sdlEventHandlerPointerEnter = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.वामः, rect.शिखरम्, event);
                यदि (d != 0)
                {
                    _Emscripten_HandlePointerEnter(SDL3.JSVar_गन्तव्यम्_CPtr(दत्त), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerLeave = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.वामः, rect.शिखरम्, event);
                यदि (d != 0)
                {
                    _Emscripten_HandlePointerLeave(SDL3.JSVar_गन्तव्यम्_CPtr(दत्त), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerGeneric = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.वामः, rect.शिखरम्, event);
                यदि (d != 0)
                {
                    _Emscripten_HandlePointerGeneric(SDL3.JSVar_गन्तव्यम्_CPtr(दत्त), d);
                    _SDL_free(d);
                }
            };

            target.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            target.सङ्कलय_Event_Listener("pointerenter", target.sdlEventHandlerPointerEnter);
            target.सङ्कलय_Event_Listener("pointerleave", target.sdlEventHandlerPointerLeave);
            target.सङ्कलय_Event_Listener("pointercancel", target.sdlEventHandlerPointerLeave);
            target.सङ्कलय_Event_Listener("pointerdown", target.sdlEventHandlerPointerGeneric);
            target.सङ्कलय_Event_Listener("pointermove", target.sdlEventHandlerPointerGeneric);
            target.सङ्कलय_Event_Listener("pointerup", target.sdlEventHandlerPointerGeneric);
        }
    }, दत्त, दत्त->canvas_id);
}

स्थिर शून्य Emscripten_unset_pointer_event_callbacks(SDL_गवाक्षः_दत्त *दत्त)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8_गन्तव्यम्_String($0));
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
    }, दत्त->canvas_id);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_Handle_Mouse_Button_ऊर्ध्वम्_Global(SDL_VideoDevice *device, ध्रुव Emscripten_PointerEvent *event)
{
    SDL_assert(device != रिक्त);
    SDL_assert(event != रिक्त);
    यदि (event->pointer_type == PTRTYPE_MOUSE) {
        प्रति (SDL_गवाक्षः *गवाक्षः = device->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            Emscripten_HandleMouseButton(गवाक्षः->आन्तरिकम्, event);
        }
    }
}

स्थिर शून्य Emscripten_समुच्चयः_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document;
        यदि (target) {
            target.sdl_Event_Handler_Mouse_Button_ऊर्ध्वम्_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.makePointerEventCStruct(0, 0, event);
                यदि (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_ऊर्ध्वम्_Global_2(SDL3.JSVar_गन्तव्यम्_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            target.सङ्कलय_Event_Listener("pointerup", target.sdl_Event_Handler_Mouse_Button_ऊर्ध्वम्_Global);
        }
    }, device);
}

स्थिर शून्य Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var target = document;
        यदि (target) {
            target.removeEventListener("pointerup", target.sdl_Event_Handler_Mouse_Button_ऊर्ध्वम्_Global);
            target.sdl_Event_Handler_Mouse_Button_ऊर्ध्वम्_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
प्रकारनिर्देश संरचना Emscripten_DropEvent
{
    पूर्णाङ्क x;
    पूर्णाङ्क y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, ध्रुव Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(गवाक्षः_दत्त_2->गवाक्षः, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragCompleteEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2)
{
    SDL_SendDropComplete(गवाक्षः_दत्त_2->गवाक्षः);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragTextEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, वर्ण *text)
{
    SDL_SendDropText(गवाक्षः_दत्त_2->गवाक्षः, text);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_SendDragFileEvent(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, वर्ण *filename)
{
    SDL_SendDropFile(गवाक्षः_दत्त_2->गवाक्षः, रिक्त, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

स्थिर शून्य Emscripten_समुच्चयः_drag_event_callbacks(SDL_गवाक्षः_दत्त *दत्त)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8_गन्तव्यम्_String($1));
        यदि (target) {
            var दत्त = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                यदि (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = target.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.वामः;
                    HEAP32[idx++] = event.clientY - rect.शिखरम्;
                }
                प्रत्यागम ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); यदि (d != 0) { _Emscripten_SendDragEvent(दत्त, d); _SDL_free(d); }
            };
            target.सङ्कलय_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_गणनम् = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                यदि (event.दत्त_Transfer.types.includes("text/plain")) {
                    let plain_text = string_गन्तव्यम्_New_UTF8(event.दत्त_Transfer.get_दत्त("text/plain"));
                    _Emscripten_SendDragTextEvent(दत्त, plain_text);
                    _Emscripten_force_free(plain_text);
                } अन्यथा यदि (event.दत्त_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ध्रुव files_गन्तव्यम्_read = event.दत्त_Transfer.files.दीर्घता;
                    प्रति (let i = 0; i < files_गन्तव्यम्_read; i++) {
                        ध्रुव file = event.दत्त_Transfer.files.item(i);
                        ध्रुव file_reader = new FileReader();
                        file_reader.read_As_Array_बफर(file);
                        file_reader.onload = function(event) {
                            ध्रुव fs_dropdir = `/tmp/filedrop/${SDL3.drop_गणनम्}`;
                            SDL3.drop_गणनम् += 1;

                            ध्रुव fs_filepath = `${fs_dropdir}/${file.name}`;
                            ध्रुव c_fs_filepath = string_गन्तव्यम्_New_UTF8(fs_filepath);
                            ध्रुव contents_array8 = new Uint8Array(event.target.परिणाम);

                            try {
                                FS.mkdir(fs_dropdir);
                                var प्रवाहः = FS.उद्घाटय(fs_filepath, "w");
                                FS.लिख(प्रवाहः, contents_array8, 0, contents_array8.दीर्घता, 0);
                                FS.close(प्रवाहः);
                                _Emscripten_SendDragFileEvent(दत्त, c_fs_filepath);
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
                        यदि (files_read === files_गन्तव्यम्_read) {
                            _Emscripten_SendDragCompleteEvent(दत्त);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(दत्त);
            };
            target.सङ्कलय_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(दत्त);
            };
            target.सङ्कलय_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            target.सङ्कलय_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, दत्त, दत्त->canvas_id, परिमाण (Emscripten_DropEvent));
}

स्थिर शून्य Emscripten_unset_drag_event_callbacks(SDL_गवाक्षः_दत्त *दत्त)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8_गन्तव्यम्_String($0));
        यदि (target) {
            var SDL3 = Module['SDL3'];
            target.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            target.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_गणनम् = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ध्रुव p = `${dirpath}/${filename}`;
                    ध्रुव p_s = FS.stat(p);
                    यदि (FS.isFile(p_s.बहुलकम्)) {
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
    }, दत्त->canvas_id);
}

स्थिर ध्रुव वर्ण *Emscripten_GetKeyboardTargetElement(ध्रुव वर्ण *target)
{
    यदि (SDL_strcmp(target, "#none") == 0) {
        प्रत्यागम रिक्त;
    } अन्यथा यदि (SDL_strcmp(target, "#window") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_गवाक्षः;
    } अन्यथा यदि (SDL_strcmp(target, "#document") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_DOCUMENT;
    } अन्यथा यदि (SDL_strcmp(target, "#screen") == 0) {
        प्रत्यागम EMSCRIPTEN_EVENT_TARGET_SCREEN;
    }

    प्रत्यागम target;
}

शून्य Emscripten_पञ्जिकाकोशः_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_समुच्चयः_global_mouseup_callback(device);

    emscripten_समुच्चयः_focus_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, device, 0, Emscripten_HandleFocus);
    emscripten_समुच्चयः_blur_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, device, 0, Emscripten_HandleFocus);

    emscripten_समुच्चयः_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_Handle_Pointer_तालकम्_Change_Global);

    emscripten_समुच्चयः_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_समुच्चयः_resize_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, device, 0, Emscripten_HandleResizeGlobal);
}

शून्य Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_समुच्चयः_focus_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, रिक्त, 0, रिक्त);
    emscripten_समुच्चयः_blur_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, रिक्त, 0, रिक्त);

    emscripten_समुच्चयः_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, रिक्त, 0, रिक्त);

    emscripten_समुच्चयः_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, रिक्त, 0, रिक्त);

    emscripten_समुच्चयः_resize_callback(EMSCRIPTEN_EVENT_TARGET_गवाक्षः, रिक्त, 0, रिक्त);
}

EMSCRIPTEN_KEEPALIVE शून्य Emscripten_Handle_तालकम्_कुञ्चिकाः_Check(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ध्रुव SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_अङ्कः : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    यदि ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_अङ्कः|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_अङ्कः|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_समुच्चयः_Mod_State(modstate);
    }
}

शून्य Emscripten_पञ्जिकाकोशः_Event_Handlers(SDL_गवाक्षः_दत्त *दत्त)
{
    ध्रुव वर्ण *कुञ्चिका_Element;

    // There is only one window and that window is the canvas
    emscripten_समुच्चयः_wheel_callback(दत्त->canvas_id, दत्त, 0, Emscripten_HandleWheel);

    emscripten_समुच्चयः_orientationchange_callback(दत्त, 0, Emscripten_HandleOrientationChange);

    कुञ्चिका_Element = Emscripten_GetKeyboardTargetElement(दत्त->keyboard_element);
    यदि (कुञ्चिका_Element) {
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
        emscripten_समुच्चयः_keydown_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);
        emscripten_समुच्चयः_keyup_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);
        emscripten_समुच्चयः_keypress_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);

        MAIN_THREAD_EM_ASM_INT({
            var दत्त = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            यदि (document.sdl_Event_Handler_तालकम्_कुञ्चिकाः_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_तालकम्_कुञ्चिकाः_Check);
            }

            document.sdl_Event_Handler_तालकम्_कुञ्चिकाः_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                यदि ((event.कुञ्चिका != "CapsLock") && (event.कुञ्चिका != "NumLock") && (event.कुञ्चिका != "ScrollLock"))
                {
                    Emscripten_Handle_तालकम्_कुञ्चिकाः_Check_2(Module['SDL3'].JSVar_गन्तव्यम्_CPtr(दत्त), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.सङ्कलय_Event_Listener("keydown", document.sdl_Event_Handler_तालकम्_कुञ्चिकाः_Check);
        }, दत्त);
        emscripten_समुच्चयः_keydown_callback(कुञ्चिका_Element, दत्त, 0, Emscripten_Handle_कुञ्चिका);
        emscripten_समुच्चयः_keyup_callback(कुञ्चिका_Element, दत्त, 0, Emscripten_Handle_कुञ्चिका);
        emscripten_समुच्चयः_keypress_callback(कुञ्चिका_Element, दत्त, 0, Emscripten_Handle_कुञ्चिका_Press);
    }

    emscripten_समुच्चयः_visibilitychange_callback(दत्त, 0, Emscripten_HandleVisibilityChange);

    emscripten_समुच्चयः_beforeunload_callback(दत्त, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_समुच्चयः_pointer_event_callbacks(दत्त);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_समुच्चयः_drag_event_callbacks(दत्त);
}

शून्य Emscripten_UnregisterEventHandlers(SDL_गवाक्षः_दत्त *दत्त)
{
    ध्रुव वर्ण *कुञ्चिका_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(दत्त);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_pointer_event_callbacks(दत्त);

    // only works due to having one window
    emscripten_समुच्चयः_wheel_callback(दत्त->canvas_id, रिक्त, 0, रिक्त);

    emscripten_समुच्चयः_orientationchange_callback(रिक्त, 0, रिक्त);

    कुञ्चिका_Element = Emscripten_GetKeyboardTargetElement(दत्त->keyboard_element);
    यदि (कुञ्चिका_Element) {
        emscripten_समुच्चयः_keydown_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);
        emscripten_समुच्चयः_keyup_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);
        emscripten_समुच्चयः_keypress_callback(कुञ्चिका_Element, रिक्त, 0, रिक्त);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_तालकम्_कुञ्चिकाः_Check);
        });
    }

    emscripten_समुच्चयः_visibilitychange_callback(रिक्त, 0, रिक्त);

    emscripten_समुच्चयः_beforeunload_callback(रिक्त, रिक्त);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_EMSCRIPTEN
