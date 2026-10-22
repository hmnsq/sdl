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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ಅನ್ತರ್ಭಾವ <emscripten/html5.h>
#ಅನ್ತರ್ಭಾವ <emscripten/dom_pk_codes.h>

#ಅನ್ತರ್ಭಾವ "../../events/SDL_dropevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_emscriptenevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_Scancode emscripten_scancode_ಕೋಷ್ಟಕ[] = {
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

ಸ್ಥಿರ SDL_Scancode Emscripten_Map_ಪರಿಶೀಲನೆ_ಸಂಕೇತ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂಕೇತ_2)
{
    ಸ್ಥಿರಾಂಕ DOM_PK_ಸಂಕೇತ_TYPE pk_ಸಂಕೇತ = emscripten_compute_dom_pk_ಸಂಕೇತ(ಸಂಕೇತ_2);
    ಆದರೆ (pk_ಸಂಕೇತ < SDL_arraysize(emscripten_scancode_ಕೋಷ್ಟಕ)) {
        ಹಿಂತಿರುಗಿ emscripten_scancode_ಕೋಷ್ಟಕ[pk_ಸಂಕೇತ];
    }

    ಆಯ್ಕೆ (pk_ಸಂಕೇತ) {
    ಸ್ಥಿತಿ DOM_PK_PASTE:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_PASTE;
    ಸ್ಥಿತಿ DOM_PK_MEDIA_TRACK_ಹಿಂದಿನ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_ಹಿಂದಿನ_TRACK;
    ಸ್ಥಿತಿ DOM_PK_CUT:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_CUT;
    ಸ್ಥಿತಿ DOM_PK_COPY:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_COPY;
    ಸ್ಥಿತಿ DOM_PK_MEDIA_TRACK_ಮುಂದಿನ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_ಮುಂದಿನ_TRACK;
    ಸ್ಥಿತಿ DOM_PK_NUMPAD_ENTER:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_KP_ENTER;
    ಸ್ಥಿತಿ DOM_PK_CONTROL_ಬಲ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_RCTRL;
    ಸ್ಥಿತಿ DOM_PK_AUDIO_VOLUME_MUTE:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MUTE;
    ಸ್ಥಿತಿ DOM_PK_MEDIA_PLAY_PAUSE:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    ಸ್ಥಿತಿ DOM_PK_MEDIA_STOP:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_STOP;
    ಸ್ಥಿತಿ DOM_PK_EJECT:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_EJECT;
    ಸ್ಥಿತಿ DOM_PK_AUDIO_VOLUME_ಕೆಳಕ್ಕೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_VOLUMEDOWN;
    ಸ್ಥಿತಿ DOM_PK_AUDIO_VOLUME_ಮೇಲೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_VOLUMEUP;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_HOME:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_HOME;
    ಸ್ಥಿತಿ DOM_PK_NUMPAD_DIVIDE:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_KP_DIVIDE;
    ಸ್ಥಿತಿ DOM_PK_ALT_ಬಲ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_RALT;
    ಸ್ಥಿತಿ DOM_PK_HELP:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_HELP;
    ಸ್ಥಿತಿ DOM_PK_ಅಂಕೆ_ಬೀಗ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_NUMLOCKCLEAR;
    ಸ್ಥಿತಿ DOM_PK_HOME:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_HOME;
    ಸ್ಥಿತಿ DOM_PK_ARROW_ಮೇಲೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಮೇಲೆ;
    ಸ್ಥಿತಿ DOM_PK_ಪುಟ_ಮೇಲೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_PAGEUP;
    ಸ್ಥಿತಿ DOM_PK_ARROW_ಎಡ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಎಡ;
    ಸ್ಥಿತಿ DOM_PK_ARROW_ಬಲ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಬಲ;
    ಸ್ಥಿತಿ DOM_PK_ಕೊನೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಕೊನೆ;
    ಸ್ಥಿತಿ DOM_PK_ARROW_ಕೆಳಕ್ಕೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಕೆಳಕ್ಕೆ;
    ಸ್ಥಿತಿ DOM_PK_ಪುಟ_ಕೆಳಕ್ಕೆ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_PAGEDOWN;
    ಸ್ಥಿತಿ DOM_PK_ಸೇರಿಸು:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_ಸೇರಿಸು;
    ಸ್ಥಿತಿ DOM_PK_DELETE:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_DELETE;
    ಸ್ಥಿತಿ DOM_PK_META_ಎಡ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_LGUI;
    ಸ್ಥಿತಿ DOM_PK_META_ಬಲ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_RGUI;
    ಸ್ಥಿತಿ DOM_PK_CONTEXT_MENU:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_APPLICATION;
    ಸ್ಥಿತಿ DOM_PK_POWER:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_POWER;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_ಹುಡುಕು:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_ಹುಡುಕು;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_FAVORITES:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_BOOKMARKS;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_REFRESH:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_REFRESH;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_STOP:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_STOP;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_FORWARD:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_FORWARD;
    ಸ್ಥಿತಿ DOM_PK_BROWSER_ಹಿಂಭಾಗ:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_AC_ಹಿಂಭಾಗ;
    ಸ್ಥಿತಿ DOM_PK_MEDIA_SELECT:
        ಹಿಂತಿರುಗಿ SDL_SCANCODE_MEDIA_SELECT;
    }

    ಹಿಂತಿರುಗಿ SDL_SCANCODE_UNKNOWN;
}

ಸ್ಥಿರ SDL_ಕಿಟಕಿ *Emscripten_Get_Focused_ಕಿಟಕಿ(SDL_VideoDevice *device)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    ಗಾಗಿ (ಕಿಟಕಿ = device->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_ಗಮ್ಯ_String($0);
            try
            {
                var canvas = document.querySelector(id);
                ಆದರೆ (canvas) {
                    ಹಿಂತಿರುಗಿ canvas === document.ಸಕ್ರಿಯ_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            ಹಿಂತಿರುಗಿ false;
        }, wdata->canvas_id);

        ಆದರೆ (focused) {
            ನಿಲ್ಲಿಸು;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ focused = MAIN_THREAD_EM_ASM_INT({
            ಹಿಂತಿರುಗಿ document.hasFocus();
        });
        ಆದರೆ (focused) {
            ಕಿಟಕಿ = device->windows;
        }
    }
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
}

ಸ್ಥಿರ EM_BOOL Emscripten_Handle_ಸೂಚಕ_ಬೀಗ_Change(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenPointerlockChangeEvent *changeEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ;
    // keep track of lock losses, so we can regrab if/when appropriate.
    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->has_ಸೂಚಕ_ಬೀಗ = changeEvent->is_ಸಕ್ರಿಯ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ EM_BOOL Emscripten_Handle_ಸೂಚಕ_ಬೀಗ_Change_Global(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenPointerlockChangeEvent *changeEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_VideoDevice *device = user_ದತ್ತಾಂಶ;
    bool prevent_default = false;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    ಗಾಗಿ (ಕಿಟಕಿ = device->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        prevent_default |= Emscripten_Handle_ಸೂಚಕ_ಬೀಗ_Change(eventType, changeEvent, ಕಿಟಕಿ->ಆಂತರಿಕ);
    }

    ಹಿಂತಿರುಗಿ prevent_default;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleWheel(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenWheelEvent *wheelEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = user_ದತ್ತಾಂಶ;

    ದಶಮಾಂಶ deltaY = wheelEvent->deltaY;
    ದಶಮಾಂಶ deltaX = wheelEvent->deltaX;

    ಆಯ್ಕೆ (wheelEvent->delta_ಬಹುಲಕ) {
    ಸ್ಥಿತಿ DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ DOM_DELTA_ಸಾಲು:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ DOM_DELTA_ಪುಟ:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        ನಿಲ್ಲಿಸು;
    }

    SDL_SendMouseWheel(0, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
    ಹಿಂತಿರುಗಿ SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleFocus(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenFocusEvent *focusEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_VideoDevice *device = user_ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = Emscripten_Get_Focused_ಕಿಟಕಿ(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    ಆದರೆ (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_ಕಿಟಕಿ_FOCUS_GAINED : SDL_EVENT_ಕಿಟಕಿ_FOCUS_ಕಳೆದುಹೋದ;
    SDL_ಗಣ_Keyboard_Focus(sdl_event_type == SDL_EVENT_ಕಿಟಕಿ_FOCUS_GAINED ? ಕಿಟಕಿ : ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ SDL_EventEnabled(sdl_event_type);
}

ಸ್ಥಿರ bool Is_Function_ಕೀಲಿ(SDL_Scancode scancode)
{
    ಆದರೆ (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಆದರೆ (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ಸ್ಥಿರ EM_BOOL Emscripten_Handle_ಕೀಲಿ(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenKeyboardEvent *ಕೀಲಿ_Event, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ;
    SDL_Scancode scancode = Emscripten_Map_ಪರಿಶೀಲನೆ_ಸಂಕೇತ(ಕೀಲಿ_Event->ಸಂಕೇತ_2);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_ಕೀಲಿ = false;

    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
        ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_ದಾಖಲೆ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಕೀಲಿ_Event->ಕೀಲಿ, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_ಹಿಂಭಾಗ;
        }
    }

    ಆದರೆ (ಕೀಲಿ_Event->location == 0 && SDL_utf8strlen(ಕೀಲಿ_Event->ಕೀಲಿ) == 1) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ = ಕೀಲಿ_Event->ಕೀಲಿ;
        keycode = SDL_ಹೆಜ್ಜೆ_UTF8(&ಕೀಲಿ, ಖಾಲಿ);
        ಆದರೆ (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    ಆದರೆ (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_ಕೀಲಿ_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } ಇಲ್ಲದಿದ್ದರೆ {
        prevent_default = SDL_Send_Keyboard_ಕೀಲಿ(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    ಆದರೆ ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_ಎಡ) ||
        (scancode == SDL_SCANCODE_ಮೇಲೆ) ||
        (scancode == SDL_SCANCODE_ಬಲ) ||
        (scancode == SDL_SCANCODE_ಕೆಳಕ್ಕೆ) ||
        Is_Function_ಕೀಲಿ(scancode) ||
        ಕೀಲಿ_Event->ctrl_ಕೀಲಿ) {
        is_nav_ಕೀಲಿ = true;
    }

    ಆದರೆ ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ) && !is_nav_ಕೀಲಿ) {
        prevent_default = false;
    }

    ಹಿಂತಿರುಗಿ prevent_default;
}

ಸ್ಥಿರ EM_BOOL Emscripten_Handle_ಕೀಲಿ_Press(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenKeyboardEvent *ಕೀಲಿ_Event, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ;

    ಆದರೆ (SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ)) {
        ಆದರೆ (SDL_utf8strlen(ಕೀಲಿ_Event->ಕೀಲಿ) == 1) {
            SDL_Send_Keyboard_ಪಠ್ಯ(ಕೀಲಿ_Event->ಕೀಲಿ);
            ಹಿಂತಿರುಗಿ EM_TRUE;
        }
    }
    ಹಿಂತಿರುಗಿ EM_FALSE;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleFullscreenChange(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = user_ದತ್ತಾಂಶ;

    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->fullscreen_change_ಒಳ_ಪ್ರಗತಿ = false;

    ಆದರೆ (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN, 0, 0);
        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->fullscreen_ಬಹುಲಕ_flags = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, fullscreenChangeEvent->isFullscreen, false);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleFullscreenChangeGlobal(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_VideoDevice *device = user_ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ಖಾಲಿ;
    ಗಾಗಿ (ಕಿಟಕಿ = device->windows; ಕಿಟಕಿ != ಖಾಲಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *canvas_id = ಕಿಟಕಿ->ಆಂತರಿಕ->canvas_id;
        ಆದರೆ (*canvas_id == '#') {
            canvas_id++;
        }
        ಆದರೆ (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            ನಿಲ್ಲಿಸು;  // this is the window.
        }
    }

    ಆದರೆ (ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, ಕಿಟಕಿ->ಆಂತರಿಕ);
    }

    ಹಿಂತಿರುಗಿ EM_FALSE;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleResize(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenUiEvent *uiEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = user_ದತ್ತಾಂಶ;

    bool force = false;

    // update pixel ratio
    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) {
        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pixel_ಅನುಪಾತ != emscripten_get_device_pixel_ಅನುಪಾತ()) {
            ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pixel_ಅನುಪಾತ = emscripten_get_device_pixel_ಅನುಪಾತ();
            force = true;
        }
    }

    ಸ್ಥಿರಾಂಕ bool fill_document = (Emscripten_fill_document_ಕಿಟಕಿ == ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ);
    ಸ್ಥಿರಾಂಕ bool fullscreen = (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ಸ್ಥಿರಾಂಕ bool resizable = (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) != 0;
    ಆದರೆ (fill_document || fullscreen || resizable) {
        ದ್ವಿಗುಣ w, h;
        ಆದರೆ (fill_document || fullscreen) {
            w = (ದ್ವಿಗುಣ) uiEvent->ಕಿಟಕಿ_Inner_ಅಗಲ;
            h = (ದ್ವಿಗುಣ) uiEvent->ಕಿಟಕಿ_Inner_ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_assert(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE);
            w = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->w;
            h = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->h;
            // this will only work if the canvas size is set through css
            ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->external_ಗಾತ್ರ) {
                emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &w, &h);
            }
        }

        emscripten_ಗಣ_canvas_element_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, SDL_lroundf(w * ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pixel_ಅನುಪಾತ), SDL_lroundf(h * ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pixel_ಅನುಪಾತ));

        // set_canvas_size unsets this
        ಆದರೆ (!ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->external_ಗಾತ್ರ && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pixel_ಅನುಪಾತ != 1.0f) {
            emscripten_ಗಣ_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, w, h);
        }

        ಆದರೆ (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->w = 0;
            ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->h = 0;
        }

        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleResizeGlobal(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenUiEvent *uiEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_VideoDevice *device = user_ದತ್ತಾಂಶ;
    bool prevent_default = false;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    ಗಾಗಿ (ಕಿಟಕಿ = device->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, ಕಿಟಕಿ->ಆಂತರಿಕ);
    }

    ಹಿಂತಿರುಗಿ prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *reserved, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    // this is used during fullscreen changes
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = user_ದತ್ತಾಂಶ;

    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->fullscreen_resize) {
        ದ್ವಿಗುಣ css_w, css_h;
        emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &css_w, &css_h);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleVisibilityChange(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenVisibilityChangeEvent *visEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = user_ದತ್ತಾಂಶ;
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, visEvent->hidden ? SDL_EVENT_ಕಿಟಕಿ_HIDDEN : SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *Emscripten_HandleBeforeUnload(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *reserved, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    ಹಿಂತಿರುಗಿ ""; // don't trigger confirmation dialog
}

ಸ್ಥಿರ EM_BOOL Emscripten_HandleOrientationChange(ಪೂರ್ಣಾಂಕ eventType, ಸ್ಥಿರಾಂಕ EmscriptenOrientationChangeEvent *orientationChangeEvent, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ)
{
    SDL_DisplayOrientation orientation;
    ಆಯ್ಕೆ (orientationChangeEvent->orientation_ಸೂಚ್ಯಂಕ) {
        #ವ್ಯಾಖ್ಯಾನಿಸು CHECK_ORIENTATION(emsdk, sdl) ಸ್ಥಿತಿ EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; ನಿಲ್ಲಿಸು
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHECK_ORIENTATION
        ಪೂರ್ವನಿಯೋಜಿತ: orientation = SDL_ORIENTATION_UNKNOWN; ನಿಲ್ಲಿಸು;
    }

    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *) user_ದತ್ತಾಂಶ;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_ಅಗಲ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ document.body.client_ಅಗಲ; } );
    uiEvent.document_Body_Client_ಎತ್ತರ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ document.body.client_ಎತ್ತರ; } );
    uiEvent.ಕಿಟಕಿ_Inner_ಅಗಲ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಅಗಲ; } );
    uiEvent.ಕಿಟಕಿ_Inner_ಎತ್ತರ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.inner_ಎತ್ತರ; } );
    uiEvent.ಕಿಟಕಿ_Outer_ಅಗಲ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.outer_ಅಗಲ; } );
    uiEvent.ಕಿಟಕಿ_Outer_ಎತ್ತರ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.outer_ಎತ್ತರ; } );
    uiEvent.scroll_ತುದಿ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.ಪುಟ_XOffset; } );
    uiEvent.scroll_ಎಡ = MAIN_THREAD_EM_ASM_INT( { ಹಿಂತಿರುಗಿ ಕಿಟಕಿ.ಪುಟ_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#ವ್ಯಾಖ್ಯಾನಿಸು PTRTYPE_MOUSE 1
#ವ್ಯಾಖ್ಯಾನಿಸು PTRTYPE_TOUCH 2
#ವ್ಯಾಖ್ಯಾನಿಸು PTRTYPE_PEN 3
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Emscripten_ಸೂಚಕ_Event
{
    ಪೂರ್ಣಾಂಕ ಸೂಚಕ_type;
    ಪೂರ್ಣಾಂಕ pointerid;
    ಪೂರ್ಣಾಂಕ button;
    ಪೂರ್ಣಾಂಕ buttons;
    ಪೂರ್ಣಾಂಕ ಕೆಳಕ್ಕೆ;
    ದಶಮಾಂಶ movementX;
    ದಶಮಾಂಶ movementY;
    ದಶಮಾಂಶ ಗುರಿ_X;
    ದಶಮಾಂಶ ಗುರಿ_Y;
    ದಶಮಾಂಶ pressure;
    ದಶಮಾಂಶ tangential_pressure;
    ದಶಮಾಂಶ tiltx;
    ದಶಮಾಂಶ tilty;
    ದಶಮಾಂಶ rotation;
} Emscripten_ಸೂಚಕ_Event;

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_HandleMouseButton(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    Uint8 sdl_button;
    bool ಕೆಳಕ್ಕೆ = false;
    ಆಯ್ಕೆ (event->button) {
        #ವ್ಯಾಖ್ಯಾನಿಸು CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) ಸ್ಥಿತಿ jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; ಕೆಳಕ್ಕೆ = (event->ಕೆಳಕ್ಕೆ != 0) || ((event->buttons & downflag) != 0); ನಿಲ್ಲಿಸು
        CHECK_MOUSE_BUTTON(0, 1, ಎಡ_2);
        CHECK_MOUSE_BUTTON(1, 4, ಮಧ್ಯ_2);
        CHECK_MOUSE_BUTTON(2, 2, ಬಲ_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHECK_MOUSE_BUTTON
        ಪೂರ್ವನಿಯೋಜಿತ: sdl_button = 0; ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (sdl_button) {
        ಸ್ಥಿರಾಂಕ SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != ಖಾಲಿ);

        ಆದರೆ (ಕೆಳಕ್ಕೆ) {
            ಆದರೆ (mouse->relative_ಬಹುಲಕ && !ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->has_ಸೂಚಕ_ಬೀಗ) {
                emscripten_request_pointerlock(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, sdl_button, ಕೆಳಕ್ಕೆ);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        ಆದರೆ (mouse->auto_capture) {
            ಆದರೆ (SDL_GetMouseState(ಖಾಲಿ, ಖಾಲಿ) != 0) {
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MOUSE_CAPTURE;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_CAPTURE;
            }
        }

        ಆದರೆ (!ಕೆಳಕ್ಕೆ && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending) {
            ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending = (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE) != 0;
            ಆದರೆ (!ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending) {
                SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_UpdateMouseFromEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಹಿಂತಿರುಗಿ;
    }

    // rescale (in case canvas is being scaled)
    ದ್ವಿಗುಣ client_w, client_h;
    emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &client_w, &client_h);
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ xscale = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->w / client_w;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ yscale = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->h / client_h;

    ಸ್ಥಿರಾಂಕ bool is_ಸೂಚಕ_Locked = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->has_ಸೂಚಕ_ಬೀಗ;
    ದಶಮಾಂಶ mx, my;
    ಆದರೆ (is_ಸೂಚಕ_Locked) {
        mx = (ದಶಮಾಂಶ)(event->movementX * xscale);
        my = (ದಶಮಾಂಶ)(event->movementY * yscale);
    } ಇಲ್ಲದಿದ್ದರೆ {
        mx = (ದಶಮಾಂಶ)(event->ಗುರಿ_X * xscale);
        my = (ದಶಮಾಂಶ)(event->ಗುರಿ_Y * yscale);
    }

    SDL_SendMouseMotion(0, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_DEFAULT_MOUSE_ID, is_ಸೂಚಕ_Locked, mx, my);

    Emscripten_HandleMouseButton(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_UpdateTouchFromEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_TOUCH);

    ಸ್ಥಿರಾಂಕ SDL_TouchID deviceId = 1;
    ಆದರೆ (SDL_ಕೂಡಿಸು_Touch(deviceId, SDL_TOUCH_DEVICE_ನೇರ, "") < 0) {
        ಹಿಂತಿರುಗಿ;
    }

    ದ್ವಿಗುಣ client_w, client_h;
    emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &client_w, &client_h);

    ಸ್ಥಿರಾಂಕ SDL_FingerID id = event->pointerid + 1;
    ದಶಮಾಂಶ x, y;
    ಆದರೆ (client_w <= 1) {
        x = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        x = event->ಗುರಿ_X / (client_w - 1);
    }
    ಆದರೆ (client_h <= 1) {
        y = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        y = event->ಗುರಿ_Y / (client_h - 1);
    }

    ಸ್ಥಿರಾಂಕ bool ಕೆಳಕ್ಕೆ = (event->buttons & 1) != 0;
    ಆದರೆ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ಆದರೆ (ಕೆಳಕ್ಕೆ) {
            SDL_SendTouch(0, deviceId, id, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_FINGER_ಕೆಳಕ್ಕೆ, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, x, y, 1.0f);

    ಆದರೆ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ಆದರೆ (!ಕೆಳಕ್ಕೆ) {
            SDL_SendTouch(0, deviceId, id, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_FINGER_ಮೇಲೆ, x, y, 1.0f);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_UpdatePenFromEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_PEN);
    ಸ್ಥಿರಾಂಕ SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle((ಶೂನ್ಯ *) (size_t) 1);   // something > 0 for the single pen handle.
    ಆದರೆ (pen) {
        // rescale (in case canvas is being scaled)
        ದ್ವಿಗುಣ client_w, client_h;
        emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &client_w, &client_h);
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ xscale = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->w / client_w;
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ yscale = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->h / client_h;

        ಸ್ಥಿರಾಂಕ bool is_ಸೂಚಕ_Locked = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->has_ಸೂಚಕ_ಬೀಗ;
        ದಶಮಾಂಶ mx, my;
        ಆದರೆ (is_ಸೂಚಕ_Locked) {
            mx = (ದಶಮಾಂಶ)(event->movementX * xscale);
            my = (ದಶಮಾಂಶ)(event->movementY * yscale);
        } ಇಲ್ಲದಿದ್ದರೆ {
            mx = (ದಶಮಾಂಶ)(event->ಗುರಿ_X * xscale);
            my = (ದಶಮಾಂಶ)(event->ಗುರಿ_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, mx, my);

        ಆದರೆ (event->button == 0) {  // pen touch
            bool ಕೆಳಕ್ಕೆ = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, false, ಕೆಳಕ್ಕೆ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool ಕೆಳಕ್ಕೆ = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, true, ಕೆಳಕ್ಕೆ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->button == 1) {
            bool ಕೆಳಕ್ಕೆ = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, 2, ಕೆಳಕ್ಕೆ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->button == 2) {
            bool ಕೆಳಕ್ಕೆ = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, 1, ಕೆಳಕ್ಕೆ);
        }

        SDL_SendPenAxis(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_Update_ಸೂಚಕ_From_Event(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event != ಖಾಲಿ);
    ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_HandleMouseFocus(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event, bool isenter)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಹಿಂತಿರುಗಿ;
    }

    ಸ್ಥಿರಾಂಕ bool is_ಸೂಚಕ_Locked = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->has_ಸೂಚಕ_ಬೀಗ;

    ಆದರೆ (!is_ಸೂಚಕ_Locked) {
        // rescale (in case canvas is being scaled)
        ದಶಮಾಂಶ mx, my;
        ದ್ವಿಗುಣ client_w, client_h;
        emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &client_w, &client_h);

        mx = (ದಶಮಾಂಶ)(event->ಗುರಿ_X * (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->w / client_w));
        my = (ದಶಮಾಂಶ)(event->ಗುರಿ_Y * (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->h / client_h));
        SDL_SendMouseMotion(0, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, is_ಸೂಚಕ_Locked, mx, my);
    }

    ಆದರೆ (isenter && ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending) {
        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!isenter && (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Mouse_Focus(isenter ? ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ : ಖಾಲಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_HandlePenEnter(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle((ಶೂನ್ಯ *) (size_t) 1);  // something > 0 for the single pen handle.
    ಆದರೆ (pen) {
        SDL_SendPenProximity(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, true, true);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.ಅಂಕೆ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_ಕೂಡಿಸು_Pen_Device(0, ಖಾಲಿ, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, &peninfo, (ಶೂನ್ಯ *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Handle_ಸೂಚಕ_Enter(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event != ಖಾಲಿ);
    ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event, true);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_TOUCH) {
        // do nothing.
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_HandlePenLeave(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    ಸ್ಥಿರಾಂಕ SDL_PenID pen = SDL_ಕಂಡುಹಿಡಿ_Pen_By_Handle((ಶೂನ್ಯ *) (size_t) 1);   // something > 0 for the single pen handle.
    ಆದರೆ (pen) {
        Emscripten_Update_ಸೂಚಕ_From_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, false, false);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_HandleTouchCancel(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event->ಸೂಚಕ_type == PTRTYPE_TOUCH);

    ಸ್ಥಿರಾಂಕ SDL_TouchID deviceId = 1;
    ಆದರೆ (SDL_ಕೂಡಿಸು_Touch(deviceId, SDL_TOUCH_DEVICE_ನೇರ, "") < 0) {
        ಹಿಂತಿರುಗಿ;
    }

    ದ್ವಿಗುಣ client_w, client_h;
    emscripten_get_element_css_ಗಾತ್ರ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->canvas_id, &client_w, &client_h);

    ಸ್ಥಿರಾಂಕ SDL_FingerID id = event->pointerid + 1;
    ದಶಮಾಂಶ x, y;
    ಆದರೆ (client_w <= 1) {
        x = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        x = event->ಗುರಿ_X / (client_w - 1);
    }
    ಆದರೆ (client_h <= 1) {
        y = 0.5f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        y = event->ಗುರಿ_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Handle_ಸೂಚಕ_Leave(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event != ಖಾಲಿ);
    ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event, false);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Handle_ಸೂಚಕ_Generic(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(event != ಖಾಲಿ);
    Emscripten_Update_ಸೂಚಕ_From_Event(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, event);
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_prep_ಸೂಚಕ_event_callbacks(ಶೂನ್ಯ)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        ಆದರೆ (SDL3.make_ಸೂಚಕ_Event_CStruct === undefined) {
            SDL3.make_ಸೂಚಕ_Event_CStruct = function(ಎಡ, ತುದಿ, event) {
                var ptrtype = 0;
                ಆದರೆ (event.ಸೂಚಕ_Type == "mouse") {
                    ptrtype = 1;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event.ಸೂಚಕ_Type == "touch") {
                    ptrtype = 2;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event.ಸೂಚಕ_Type == "pen") {
                    ptrtype = 3;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಹಿಂತಿರುಗಿ 0;
                }

                var ptr = _SDL_malloc($0);
                ಆದರೆ (ptr != 0) {
                    var idx = SDL3.CPtr_ಗಮ್ಯ_Heap32_ಸೂಚ್ಯಂಕ(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.ಸೂಚಕ_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - ಎಡ;
                    HEAPF32[idx++] = event.clientY - ತುದಿ;
                    ಆದರೆ (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                ಹಿಂತಿರುಗಿ ptr;
            };
        }
    }, ಗಾತ್ರ (Emscripten_ಸೂಚಕ_Event));
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_ಸೂಚಕ_event_callbacks(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    Emscripten_prep_ಸೂಚಕ_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document.querySelector(UTF8_ಗಮ್ಯ_String($1));
        ಆದರೆ (ಗುರಿ) {
            var SDL3 = Module['SDL3'];
            var ದತ್ತಾಂಶ = $0;
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Enter = function(event) {
                var rect = ಗುರಿ.getBoundingClientRect();
                var d = SDL3.make_ಸೂಚಕ_Event_CStruct(rect.ಎಡ, rect.ತುದಿ, event);
                ಆದರೆ (d != 0)
                {
                    Emscripten_Handle_ಸೂಚಕ_Enter_2(SDL3.JSVar_ಗಮ್ಯ_CPtr(ದತ್ತಾಂಶ), d);
                    _SDL_free(d);
                }
            };
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave = function(event) {
                var rect = ಗುರಿ.getBoundingClientRect();
                var d = SDL3.make_ಸೂಚಕ_Event_CStruct(rect.ಎಡ, rect.ತುದಿ, event);
                ಆದರೆ (d != 0)
                {
                    Emscripten_Handle_ಸೂಚಕ_Leave_2(SDL3.JSVar_ಗಮ್ಯ_CPtr(ದತ್ತಾಂಶ), d);
                    _SDL_free(d);
                }
            };
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic = function(event) {
                var rect = ಗುರಿ.getBoundingClientRect();
                var d = SDL3.make_ಸೂಚಕ_Event_CStruct(rect.ಎಡ, rect.ತುದಿ, event);
                ಆದರೆ (d != 0)
                {
                    Emscripten_Handle_ಸೂಚಕ_Generic_2(SDL3.JSVar_ಗಮ್ಯ_CPtr(ದತ್ತಾಂಶ), d);
                    _SDL_free(d);
                }
            };

            ಗುರಿ.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointerenter", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Enter);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointerleave", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointercancel", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointerdown", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointermove", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointerup", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
        }
    }, ದತ್ತಾಂಶ, ದತ್ತಾಂಶ->canvas_id);
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_unset_ಸೂಚಕ_event_callbacks(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document.querySelector(UTF8_ಗಮ್ಯ_String($0));
        ಆದರೆ (ಗುರಿ) {
            ಗುರಿ.removeEventListener("pointerenter", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Enter);
            ಗುರಿ.removeEventListener("pointerleave", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave);
            ಗುರಿ.removeEventListener("pointercancel", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave);
            ಗುರಿ.removeEventListener("pointerdown", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
            ಗುರಿ.removeEventListener("pointermove", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
            ಗುರಿ.removeEventListener("pointerup", ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic);
            ಗುರಿ.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Enter = undefined;
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Leave = undefined;
            ಗುರಿ.sdl_Event_Handler_ಸೂಚಕ_Generic = undefined;
        }
    }, ದತ್ತಾಂಶ->canvas_id);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Handle_Mouse_Button_ಮೇಲೆ_Global(SDL_VideoDevice *device, ಸ್ಥಿರಾಂಕ Emscripten_ಸೂಚಕ_Event *event)
{
    SDL_assert(device != ಖಾಲಿ);
    SDL_assert(event != ಖಾಲಿ);
    ಆದರೆ (event->ಸೂಚಕ_type == PTRTYPE_MOUSE) {
        ಗಾಗಿ (SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = device->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            Emscripten_HandleMouseButton(ಕಿಟಕಿ->ಆಂತರಿಕ, event);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_ಸೂಚಕ_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document;
        ಆದರೆ (ಗುರಿ) {
            ಗುರಿ.sdl_Event_Handler_Mouse_Button_ಮೇಲೆ_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_ಸೂಚಕ_Event_CStruct(0, 0, event);
                ಆದರೆ (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_ಮೇಲೆ_Global_2(SDL3.JSVar_ಗಮ್ಯ_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("pointerup", ಗುರಿ.sdl_Event_Handler_Mouse_Button_ಮೇಲೆ_Global);
        }
    }, device);
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document;
        ಆದರೆ (ಗುರಿ) {
            ಗುರಿ.removeEventListener("pointerup", ಗುರಿ.sdl_Event_Handler_Mouse_Button_ಮೇಲೆ_Global);
            ಗುರಿ.sdl_Event_Handler_Mouse_Button_ಮೇಲೆ_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Emscripten_DropEvent
{
    ಪೂರ್ಣಾಂಕ x;
    ಪೂರ್ಣಾಂಕ y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_SendDragEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಸ್ಥಿರಾಂಕ Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_SendDragCompleteEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2)
{
    SDL_SendDropComplete(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Send_Drag_ಪಠ್ಯ_Event(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಅಕ್ಷರ *ಪಠ್ಯ)
{
    SDL_Send_Drop_ಪಠ್ಯ(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, ಪಠ್ಯ);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_SendDragFileEvent(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ಅಕ್ಷರ *filename)
{
    SDL_SendDropFile(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, ಖಾಲಿ, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_ಗಣ_drag_event_callbacks(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document.querySelector(UTF8_ಗಮ್ಯ_String($1));
        ಆದರೆ (ಗುರಿ) {
            var ದತ್ತಾಂಶ = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                ಆದರೆ (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = ಗುರಿ.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.ಎಡ;
                    HEAP32[idx++] = event.clientY - rect.ತುದಿ;
                }
                ಹಿಂತಿರುಗಿ ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); ಆದರೆ (d != 0) { _Emscripten_SendDragEvent(ದತ್ತಾಂಶ, d); _SDL_free(d); }
            };
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_ಎಣಿಕೆ = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                ಆದರೆ (event.ದತ್ತಾಂಶ_Transfer.types.includes("text/plain")) {
                    let plain_ಪಠ್ಯ = string_ಗಮ್ಯ_New_UTF8(event.ದತ್ತಾಂಶ_Transfer.get_ದತ್ತಾಂಶ("text/plain"));
                    Emscripten_Send_Drag_ಪಠ್ಯ_Event_2(ದತ್ತಾಂಶ, plain_ಪಠ್ಯ);
                    _Emscripten_force_free(plain_ಪಠ್ಯ);
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (event.ದತ್ತಾಂಶ_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ಸ್ಥಿರಾಂಕ files_ಗಮ್ಯ_read = event.ದತ್ತಾಂಶ_Transfer.files.ಉದ್ದಳತೆ;
                    ಗಾಗಿ (let i = 0; i < files_ಗಮ್ಯ_read; i++) {
                        ಸ್ಥಿರಾಂಕ file = event.ದತ್ತಾಂಶ_Transfer.files.ಅಂಶ(i);
                        ಸ್ಥಿರಾಂಕ file_reader = new FileReader();
                        file_reader.read_As_Array_ಬಫರ್(file);
                        file_reader.onload = function(event) {
                            ಸ್ಥಿರಾಂಕ fs_dropdir = `/tmp/filedrop/${SDL3.drop_ಎಣಿಕೆ}`;
                            SDL3.drop_ಎಣಿಕೆ += 1;

                            ಸ್ಥಿರಾಂಕ fs_filepath = `${fs_dropdir}/${file.name}`;
                            ಸ್ಥಿರಾಂಕ c_fs_filepath = string_ಗಮ್ಯ_New_UTF8(fs_filepath);
                            ಸ್ಥಿರಾಂಕ contents_array8 = new Uint8Array(event.ಗುರಿ.ಫಲಿತಾಂಶ);

                            try {
                                FS.mkdir(fs_dropdir);
                                var ಹರಿವು = FS.open(fs_filepath, "w");
                                FS.ಲಿಖ(ಹರಿವು, contents_array8, 0, contents_array8.ಉದ್ದಳತೆ, 0);
                                FS.close(ಹರಿವು);
                                _Emscripten_SendDragFileEvent(ದತ್ತಾಂಶ, c_fs_filepath);
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
                        ಆದರೆ (files_read === files_ಗಮ್ಯ_read) {
                            _Emscripten_SendDragCompleteEvent(ದತ್ತಾಂಶ);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(ದತ್ತಾಂಶ);
            };
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(ದತ್ತಾಂಶ);
            };
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            ಗುರಿ.ಕೂಡಿಸು_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, ದತ್ತಾಂಶ, ದತ್ತಾಂಶ->canvas_id, ಗಾತ್ರ (Emscripten_DropEvent));
}

ಸ್ಥಿರ ಶೂನ್ಯ Emscripten_unset_drag_event_callbacks(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    MAIN_THREAD_EM_ASM({
        var ಗುರಿ = document.querySelector(UTF8_ಗಮ್ಯ_String($0));
        ಆದರೆ (ಗುರಿ) {
            var SDL3 = Module['SDL3'];
            ಗುರಿ.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            ಗುರಿ.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            ಗುರಿ.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_ಎಣಿಕೆ = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ಸ್ಥಿರಾಂಕ p = `${dirpath}/${filename}`;
                    ಸ್ಥಿರಾಂಕ p_s = FS.stat(p);
                    ಆದರೆ (FS.isFile(p_s.ಬಹುಲಕ)) {
                        FS.unlink(p);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            ಗುರಿ.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, ದತ್ತಾಂಶ->canvas_id);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *Emscripten_Get_Keyboard_ಗುರಿ_Element(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಗುರಿ)
{
    ಆದರೆ (SDL_strcmp(ಗುರಿ, "#none") == 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಗುರಿ, "#window") == 0) {
        ಹಿಂತಿರುಗಿ EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಗುರಿ, "#document") == 0) {
        ಹಿಂತಿರುಗಿ EMSCRIPTEN_EVENT_ಗುರಿ_DOCUMENT;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(ಗುರಿ, "#screen") == 0) {
        ಹಿಂತಿರುಗಿ EMSCRIPTEN_EVENT_ಗುರಿ_SCREEN;
    }

    ಹಿಂತಿರುಗಿ ಗುರಿ;
}

ಶೂನ್ಯ Emscripten_ರಿಜಿಸ್ಟರ್_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_ಗಣ_global_mouseup_callback(device);

    emscripten_ಗಣ_focus_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, device, 0, Emscripten_HandleFocus);
    emscripten_ಗಣ_blur_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, device, 0, Emscripten_HandleFocus);

    emscripten_ಗಣ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ಗುರಿ_DOCUMENT, device, 0, Emscripten_Handle_ಸೂಚಕ_ಬೀಗ_Change_Global);

    emscripten_ಗಣ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ಗುರಿ_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_ಗಣ_resize_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, device, 0, Emscripten_HandleResizeGlobal);
}

ಶೂನ್ಯ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_ಗಣ_focus_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, ಖಾಲಿ, 0, ಖಾಲಿ);
    emscripten_ಗಣ_blur_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, ಖಾಲಿ, 0, ಖಾಲಿ);

    emscripten_ಗಣ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ಗುರಿ_DOCUMENT, ಖಾಲಿ, 0, ಖಾಲಿ);

    emscripten_ಗಣ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ಗುರಿ_DOCUMENT, ಖಾಲಿ, 0, ಖಾಲಿ);

    emscripten_ಗಣ_resize_callback(EMSCRIPTEN_EVENT_ಗುರಿ_ಕಿಟಕಿ, ಖಾಲಿ, 0, ಖಾಲಿ);
}

EMSCRIPTEN_KEEPALIVE ಶೂನ್ಯ Emscripten_Handle_ಬೀಗ_ಕೀಲಿಗಳು_Check(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ಸ್ಥಿರಾಂಕ SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_ಅಂಕೆ : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    ಆದರೆ ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_ಅಂಕೆ|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_ಅಂಕೆ|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_ಗಣ_Mod_State(modstate);
    }
}

ಶೂನ್ಯ Emscripten_ರಿಜಿಸ್ಟರ್_Event_Handlers(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_Element;

    // There is only one window and that window is the canvas
    emscripten_ಗಣ_wheel_callback(ದತ್ತಾಂಶ->canvas_id, ದತ್ತಾಂಶ, 0, Emscripten_HandleWheel);

    emscripten_ಗಣ_orientationchange_callback(ದತ್ತಾಂಶ, 0, Emscripten_HandleOrientationChange);

    ಕೀಲಿ_Element = Emscripten_Get_Keyboard_ಗುರಿ_Element(ದತ್ತಾಂಶ->keyboard_element);
    ಆದರೆ (ಕೀಲಿ_Element) {
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
        emscripten_ಗಣ_keydown_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);
        emscripten_ಗಣ_keyup_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);
        emscripten_ಗಣ_keypress_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);

        MAIN_THREAD_EM_ASM_INT({
            var ದತ್ತಾಂಶ = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            ಆದರೆ (document.sdl_Event_Handler_ಬೀಗ_ಕೀಲಿಗಳು_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_ಬೀಗ_ಕೀಲಿಗಳು_Check);
            }

            document.sdl_Event_Handler_ಬೀಗ_ಕೀಲಿಗಳು_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                ಆದರೆ ((event.ಕೀಲಿ != "CapsLock") && (event.ಕೀಲಿ != "NumLock") && (event.ಕೀಲಿ != "ScrollLock"))
                {
                    Emscripten_Handle_ಬೀಗ_ಕೀಲಿಗಳು_Check_2(Module['SDL3'].JSVar_ಗಮ್ಯ_CPtr(ದತ್ತಾಂಶ), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.ಕೂಡಿಸು_Event_Listener("keydown", document.sdl_Event_Handler_ಬೀಗ_ಕೀಲಿಗಳು_Check);
        }, ದತ್ತಾಂಶ);
        emscripten_ಗಣ_keydown_callback(ಕೀಲಿ_Element, ದತ್ತಾಂಶ, 0, Emscripten_Handle_ಕೀಲಿ);
        emscripten_ಗಣ_keyup_callback(ಕೀಲಿ_Element, ದತ್ತಾಂಶ, 0, Emscripten_Handle_ಕೀಲಿ);
        emscripten_ಗಣ_keypress_callback(ಕೀಲಿ_Element, ದತ್ತಾಂಶ, 0, Emscripten_Handle_ಕೀಲಿ_Press);
    }

    emscripten_ಗಣ_visibilitychange_callback(ದತ್ತಾಂಶ, 0, Emscripten_HandleVisibilityChange);

    emscripten_ಗಣ_beforeunload_callback(ದತ್ತಾಂಶ, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_ಗಣ_ಸೂಚಕ_event_callbacks(ದತ್ತಾಂಶ);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_ಗಣ_drag_event_callbacks(ದತ್ತಾಂಶ);
}

ಶೂನ್ಯ Emscripten_UnregisterEventHandlers(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(ದತ್ತಾಂಶ);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_ಸೂಚಕ_event_callbacks(ದತ್ತಾಂಶ);

    // only works due to having one window
    emscripten_ಗಣ_wheel_callback(ದತ್ತಾಂಶ->canvas_id, ಖಾಲಿ, 0, ಖಾಲಿ);

    emscripten_ಗಣ_orientationchange_callback(ಖಾಲಿ, 0, ಖಾಲಿ);

    ಕೀಲಿ_Element = Emscripten_Get_Keyboard_ಗುರಿ_Element(ದತ್ತಾಂಶ->keyboard_element);
    ಆದರೆ (ಕೀಲಿ_Element) {
        emscripten_ಗಣ_keydown_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);
        emscripten_ಗಣ_keyup_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);
        emscripten_ಗಣ_keypress_callback(ಕೀಲಿ_Element, ಖಾಲಿ, 0, ಖಾಲಿ);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_ಬೀಗ_ಕೀಲಿಗಳು_Check);
        });
    }

    emscripten_ಗಣ_visibilitychange_callback(ಖಾಲಿ, 0, ಖಾಲಿ);

    emscripten_ಗಣ_beforeunload_callback(ಖಾಲಿ, ಖಾಲಿ);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_EMSCRIPTEN
