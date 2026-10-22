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

#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن <emscripten/html5.h>
#ضمن <emscripten/dom_pk_codes.h>

#ضمن "../../events/SDL_dropevents_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_emscriptenevents.h"
#ضمن "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ساكن ثابت SDL_Scancode emscripten_scancode_جدول[] = {
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

ساكن SDL_Scancode Emscripten_Map_پیمایش_کد(ثابت حرف *کد)
{
    ثابت DOM_PK_کد_TYPE pk_کد = emscripten_compute_dom_pk_کد(کد);
    إذا (pk_کد < SDL_arraysize(emscripten_scancode_جدول)) {
        أرجع emscripten_scancode_جدول[pk_کد];
    }

    بدل (pk_کد) {
    حالة DOM_PK_PASTE:
        أرجع SDL_SCANCODE_PASTE;
    حالة DOM_PK_MEDIA_TRACK_قبلی:
        أرجع SDL_SCANCODE_MEDIA_قبلی_TRACK;
    حالة DOM_PK_CUT:
        أرجع SDL_SCANCODE_CUT;
    حالة DOM_PK_COPY:
        أرجع SDL_SCANCODE_COPY;
    حالة DOM_PK_MEDIA_TRACK_بعدی:
        أرجع SDL_SCANCODE_MEDIA_بعدی_TRACK;
    حالة DOM_PK_NUMPAD_ENTER:
        أرجع SDL_SCANCODE_KP_ENTER;
    حالة DOM_PK_CONTROL_راست:
        أرجع SDL_SCANCODE_RCTRL;
    حالة DOM_PK_AUDIO_VOLUME_MUTE:
        أرجع SDL_SCANCODE_MUTE;
    حالة DOM_PK_MEDIA_PLAY_PAUSE:
        أرجع SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    حالة DOM_PK_MEDIA_STOP:
        أرجع SDL_SCANCODE_MEDIA_STOP;
    حالة DOM_PK_EJECT:
        أرجع SDL_SCANCODE_MEDIA_EJECT;
    حالة DOM_PK_AUDIO_VOLUME_پایین:
        أرجع SDL_SCANCODE_VOLUMEDOWN;
    حالة DOM_PK_AUDIO_VOLUME_به_بالا:
        أرجع SDL_SCANCODE_VOLUMEUP;
    حالة DOM_PK_BROWSER_HOME:
        أرجع SDL_SCANCODE_AC_HOME;
    حالة DOM_PK_NUMPAD_DIVIDE:
        أرجع SDL_SCANCODE_KP_DIVIDE;
    حالة DOM_PK_ALT_راست:
        أرجع SDL_SCANCODE_RALT;
    حالة DOM_PK_HELP:
        أرجع SDL_SCANCODE_HELP;
    حالة DOM_PK_رقم_قفل:
        أرجع SDL_SCANCODE_NUMLOCKCLEAR;
    حالة DOM_PK_HOME:
        أرجع SDL_SCANCODE_HOME;
    حالة DOM_PK_ARROW_به_بالا:
        أرجع SDL_SCANCODE_به_بالا;
    حالة DOM_PK_صفحه_به_بالا:
        أرجع SDL_SCANCODE_PAGEUP;
    حالة DOM_PK_ARROW_چپ:
        أرجع SDL_SCANCODE_چپ;
    حالة DOM_PK_ARROW_راست:
        أرجع SDL_SCANCODE_راست;
    حالة DOM_PK_انتها:
        أرجع SDL_SCANCODE_انتها;
    حالة DOM_PK_ARROW_پایین:
        أرجع SDL_SCANCODE_پایین;
    حالة DOM_PK_صفحه_پایین:
        أرجع SDL_SCANCODE_PAGEDOWN;
    حالة DOM_PK_درج:
        أرجع SDL_SCANCODE_درج;
    حالة DOM_PK_DELETE:
        أرجع SDL_SCANCODE_DELETE;
    حالة DOM_PK_META_چپ:
        أرجع SDL_SCANCODE_LGUI;
    حالة DOM_PK_META_راست:
        أرجع SDL_SCANCODE_RGUI;
    حالة DOM_PK_CONTEXT_MENU:
        أرجع SDL_SCANCODE_APPLICATION;
    حالة DOM_PK_POWER:
        أرجع SDL_SCANCODE_POWER;
    حالة DOM_PK_BROWSER_جستجو:
        أرجع SDL_SCANCODE_AC_جستجو;
    حالة DOM_PK_BROWSER_FAVORITES:
        أرجع SDL_SCANCODE_AC_BOOKMARKS;
    حالة DOM_PK_BROWSER_REFRESH:
        أرجع SDL_SCANCODE_AC_REFRESH;
    حالة DOM_PK_BROWSER_STOP:
        أرجع SDL_SCANCODE_AC_STOP;
    حالة DOM_PK_BROWSER_FORWARD:
        أرجع SDL_SCANCODE_AC_FORWARD;
    حالة DOM_PK_BROWSER_پشت:
        أرجع SDL_SCANCODE_AC_پشت;
    حالة DOM_PK_MEDIA_SELECT:
        أرجع SDL_SCANCODE_MEDIA_SELECT;
    }

    أرجع SDL_SCANCODE_UNKNOWN;
}

ساكن SDL_پنجره *Emscripten_Get_Focused_پنجره(SDL_VideoDevice *device)
{
    SDL_پنجره *پنجره;
    لكل (پنجره = device->windows; پنجره; پنجره = پنجره->بعدی) {
        SDL_پنجره_داده *wdata = پنجره->داخلی;

        ثابت صحيح focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_مقصد_String($0);
            try
            {
                var canvas = document.querySelector(id);
                إذا (canvas) {
                    أرجع canvas === document.فعال_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            أرجع false;
        }, wdata->canvas_id);

        إذا (focused) {
            اكسر;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    إذا (!پنجره) {
        ثابت صحيح focused = MAIN_THREAD_EM_ASM_INT({
            أرجع document.hasFocus();
        });
        إذا (focused) {
            پنجره = device->windows;
        }
    }
    أرجع پنجره;
}

ساكن EM_BOOL Emscripten_Handle_اشاره_گر_قفل_Change(صحيح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = (SDL_پنجره_داده *)user_داده;
    // keep track of lock losses, so we can regrab if/when appropriate.
    پنجره_داده_2->has_اشاره_گر_قفل = changeEvent->is_فعال;
    أرجع 0;
}

ساكن EM_BOOL Emscripten_Handle_اشاره_گر_قفل_Change_Global(صحيح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, فراغ *user_داده)
{
    SDL_VideoDevice *device = user_داده;
    bool prevent_default = false;
    SDL_پنجره *پنجره;

    لكل (پنجره = device->windows; پنجره; پنجره = پنجره->بعدی) {
        prevent_default |= Emscripten_Handle_اشاره_گر_قفل_Change(eventType, changeEvent, پنجره->داخلی);
    }

    أرجع prevent_default;
}

ساكن EM_BOOL Emscripten_HandleWheel(صحيح eventType, ثابت EmscriptenWheelEvent *wheelEvent, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = user_داده;

    عائم deltaY = wheelEvent->deltaY;
    عائم deltaX = wheelEvent->deltaX;

    بدل (wheelEvent->delta_نما) {
    حالة DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        اكسر;
    حالة DOM_DELTA_سطر:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        اكسر;
    حالة DOM_DELTA_صفحه:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        اكسر;
    }

    SDL_SendMouseWheel(0, پنجره_داده_2->پنجره, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_نرمال);
    أرجع SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ساكن EM_BOOL Emscripten_HandleFocus(صحيح eventType, ثابت EmscriptenFocusEvent *focusEvent, فراغ *user_داده)
{
    SDL_VideoDevice *device = user_داده;
    SDL_پنجره *پنجره = Emscripten_Get_Focused_پنجره(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    إذا (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_پنجره_FOCUS_GAINED : SDL_EVENT_پنجره_FOCUS_گمشده;
    SDL_مجموعه_Keyboard_Focus(sdl_event_type == SDL_EVENT_پنجره_FOCUS_GAINED ? پنجره : عدم);
    أرجع SDL_EventEnabled(sdl_event_type);
}

ساكن bool Is_Function_کلید(SDL_Scancode scancode)
{
    إذا (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        أرجع true;
    }
    إذا (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        أرجع true;
    }
    أرجع false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ساكن EM_BOOL Emscripten_Handle_کلید(صحيح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = (SDL_پنجره_داده *)user_داده;
    SDL_Scancode scancode = Emscripten_Map_پیمایش_کد(کلید_Event->کد);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_کلید = false;

    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
        إذا (SDL_strcmp(کلید_Event->کلید, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_رکورد;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        إذا (SDL_strcmp(کلید_Event->کلید, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } وإلا إذا (SDL_strcmp(کلید_Event->کلید, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_پشت;
        }
    }

    إذا (کلید_Event->location == 0 && SDL_utf8strlen(کلید_Event->کلید) == 1) {
        ثابت حرف *کلید = کلید_Event->کلید;
        keycode = SDL_گام_UTF8(&کلید, عدم);
        إذا (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    إذا (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_کلید_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } وإلا {
        prevent_default = SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    إذا ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_چپ) ||
        (scancode == SDL_SCANCODE_به_بالا) ||
        (scancode == SDL_SCANCODE_راست) ||
        (scancode == SDL_SCANCODE_پایین) ||
        Is_Function_کلید(scancode) ||
        کلید_Event->ctrl_کلید) {
        is_nav_کلید = true;
    }

    إذا ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_متن_درون_داد_فعال(پنجره_داده_2->پنجره) && !is_nav_کلید) {
        prevent_default = false;
    }

    أرجع prevent_default;
}

ساكن EM_BOOL Emscripten_Handle_کلید_Press(صحيح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = (SDL_پنجره_داده *)user_داده;

    إذا (SDL_متن_درون_داد_فعال(پنجره_داده_2->پنجره)) {
        إذا (SDL_utf8strlen(کلید_Event->کلید) == 1) {
            SDL_Send_Keyboard_متن(کلید_Event->کلید);
            أرجع EM_TRUE;
        }
    }
    أرجع EM_FALSE;
}

ساكن EM_BOOL Emscripten_HandleFullscreenChange(صحيح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = user_داده;

    پنجره_داده_2->fullscreen_change_درون_پیشرفت = false;

    إذا (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_پنجره_Event(پنجره_داده_2->پنجره, SDL_EVENT_پنجره_ENTER_FULLSCREEN, 0, 0);
        پنجره_داده_2->fullscreen_نما_flags = 0;
    } وإلا {
        SDL_Send_پنجره_Event(پنجره_داده_2->پنجره, SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_نما(پنجره_داده_2->پنجره, fullscreenChangeEvent->isFullscreen, false);

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleFullscreenChangeGlobal(صحيح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, فراغ *user_داده)
{
    SDL_VideoDevice *device = user_داده;
    SDL_پنجره *پنجره = عدم;
    لكل (پنجره = device->windows; پنجره != عدم; پنجره = پنجره->بعدی) {
        ثابت حرف *canvas_id = پنجره->داخلی->canvas_id;
        إذا (*canvas_id == '#') {
            canvas_id++;
        }
        إذا (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            اكسر;  // this is the window.
        }
    }

    إذا (پنجره) {
        أرجع Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, پنجره->داخلی);
    }

    أرجع EM_FALSE;
}

ساكن EM_BOOL Emscripten_HandleResize(صحيح eventType, ثابت EmscriptenUiEvent *uiEvent, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = user_داده;

    bool force = false;

    // update pixel ratio
    إذا (پنجره_داده_2->پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) {
        إذا (پنجره_داده_2->pixel_نسبت != emscripten_get_device_pixel_نسبت()) {
            پنجره_داده_2->pixel_نسبت = emscripten_get_device_pixel_نسبت();
            force = true;
        }
    }

    ثابت bool fill_document = (Emscripten_fill_document_پنجره == پنجره_داده_2->پنجره);
    ثابت bool fullscreen = (پنجره_داده_2->پنجره->flags & SDL_پنجره_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ثابت bool resizable = (پنجره_داده_2->پنجره->flags & SDL_پنجره_RESIZABLE) != 0;
    إذا (fill_document || fullscreen || resizable) {
        مزدوج w, h;
        إذا (fill_document || fullscreen) {
            w = (مزدوج) uiEvent->پنجره_Inner_عرض;
            h = (مزدوج) uiEvent->پنجره_Inner_ارتفاع;
        } وإلا {
            SDL_assert(پنجره_داده_2->پنجره->flags & SDL_پنجره_RESIZABLE);
            w = پنجره_داده_2->پنجره->w;
            h = پنجره_داده_2->پنجره->h;
            // this will only work if the canvas size is set through css
            إذا (پنجره_داده_2->external_اندازه) {
                emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &w, &h);
            }
        }

        emscripten_مجموعه_canvas_element_اندازه(پنجره_داده_2->canvas_id, SDL_lroundf(w * پنجره_داده_2->pixel_نسبت), SDL_lroundf(h * پنجره_داده_2->pixel_نسبت));

        // set_canvas_size unsets this
        إذا (!پنجره_داده_2->external_اندازه && پنجره_داده_2->pixel_نسبت != 1.0f) {
            emscripten_مجموعه_element_css_اندازه(پنجره_داده_2->canvas_id, w, h);
        }

        إذا (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            پنجره_داده_2->پنجره->w = 0;
            پنجره_داده_2->پنجره->h = 0;
        }

        SDL_Send_پنجره_Event(پنجره_داده_2->پنجره, SDL_EVENT_پنجره_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleResizeGlobal(صحيح eventType, ثابت EmscriptenUiEvent *uiEvent, فراغ *user_داده)
{
    SDL_VideoDevice *device = user_داده;
    bool prevent_default = false;
    SDL_پنجره *پنجره;

    لكل (پنجره = device->windows; پنجره; پنجره = پنجره->بعدی) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, پنجره->داخلی);
    }

    أرجع prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(صحيح eventType, ثابت فراغ *reserved, فراغ *user_داده)
{
    // this is used during fullscreen changes
    SDL_پنجره_داده *پنجره_داده_2 = user_داده;

    إذا (پنجره_داده_2->fullscreen_resize) {
        مزدوج css_w, css_h;
        emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &css_w, &css_h);
        SDL_Send_پنجره_Event(پنجره_داده_2->پنجره, SDL_EVENT_پنجره_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleVisibilityChange(صحيح eventType, ثابت EmscriptenVisibilityChangeEvent *visEvent, فراغ *user_داده)
{
    SDL_پنجره_داده *پنجره_داده_2 = user_داده;
    SDL_Send_پنجره_Event(پنجره_داده_2->پنجره, visEvent->hidden ? SDL_EVENT_پنجره_HIDDEN : SDL_EVENT_پنجره_SHOWN, 0, 0);
    أرجع 0;
}

ساكن ثابت حرف *Emscripten_HandleBeforeUnload(صحيح eventType, ثابت فراغ *reserved, فراغ *user_داده)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    أرجع ""; // don't trigger confirmation dialog
}

ساكن EM_BOOL Emscripten_HandleOrientationChange(صحيح eventType, ثابت EmscriptenOrientationChangeEvent *orientationChangeEvent, فراغ *user_داده)
{
    SDL_DisplayOrientation orientation;
    بدل (orientationChangeEvent->orientation_شاخص) {
        #تعریف_کن CHECK_ORIENTATION(emsdk, sdl) حالة EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; اكسر
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #لغو_تعریف CHECK_ORIENTATION
        افتراضي: orientation = SDL_ORIENTATION_UNKNOWN; اكسر;
    }

    SDL_پنجره_داده *پنجره_داده_2 = (SDL_پنجره_داده *) user_داده;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_پنجره(پنجره_داده_2->پنجره), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_عرض = MAIN_THREAD_EM_ASM_INT( { أرجع document.body.client_عرض; } );
    uiEvent.document_Body_Client_ارتفاع = MAIN_THREAD_EM_ASM_INT( { أرجع document.body.client_ارتفاع; } );
    uiEvent.پنجره_Inner_عرض = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.inner_عرض; } );
    uiEvent.پنجره_Inner_ارتفاع = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.inner_ارتفاع; } );
    uiEvent.پنجره_Outer_عرض = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.outer_عرض; } );
    uiEvent.پنجره_Outer_ارتفاع = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.outer_ارتفاع; } );
    uiEvent.scroll_بالاترین = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.صفحه_XOffset; } );
    uiEvent.scroll_چپ = MAIN_THREAD_EM_ASM_INT( { أرجع پنجره.صفحه_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_داده);

    أرجع 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#تعریف_کن PTRTYPE_MOUSE 1
#تعریف_کن PTRTYPE_TOUCH 2
#تعریف_کن PTRTYPE_PEN 3
تعريفنوع بنية Emscripten_اشاره_گر_Event
{
    صحيح اشاره_گر_type;
    صحيح pointerid;
    صحيح button;
    صحيح buttons;
    صحيح پایین;
    عائم movementX;
    عائم movementY;
    عائم هدف_X;
    عائم هدف_Y;
    عائم pressure;
    عائم tangential_pressure;
    عائم tiltx;
    عائم tilty;
    عائم rotation;
} Emscripten_اشاره_گر_Event;

ساكن فراغ Emscripten_HandleMouseButton(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    Uint8 sdl_button;
    bool پایین = false;
    بدل (event->button) {
        #تعریف_کن CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) حالة jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; پایین = (event->پایین != 0) || ((event->buttons & downflag) != 0); اكسر
        CHECK_MOUSE_BUTTON(0, 1, چپ_2);
        CHECK_MOUSE_BUTTON(1, 4, میانه_2);
        CHECK_MOUSE_BUTTON(2, 2, راست_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #لغو_تعریف CHECK_MOUSE_BUTTON
        افتراضي: sdl_button = 0; اكسر;
    }

    إذا (sdl_button) {
        ثابت SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != عدم);

        إذا (پایین) {
            إذا (mouse->relative_نما && !پنجره_داده_2->has_اشاره_گر_قفل) {
                emscripten_request_pointerlock(پنجره_داده_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, پنجره_داده_2->پنجره, SDL_DEFAULT_MOUSE_ID, sdl_button, پایین);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        إذا (mouse->auto_capture) {
            إذا (SDL_GetMouseState(عدم, عدم) != 0) {
                پنجره_داده_2->پنجره->flags |= SDL_پنجره_MOUSE_CAPTURE;
            } وإلا {
                پنجره_داده_2->پنجره->flags &= ~SDL_پنجره_MOUSE_CAPTURE;
            }
        }

        إذا (!پایین && پنجره_داده_2->mouse_focus_loss_pending) {
            پنجره_داده_2->mouse_focus_loss_pending = (پنجره_داده_2->پنجره->flags & SDL_پنجره_MOUSE_CAPTURE) != 0;
            إذا (!پنجره_داده_2->mouse_focus_loss_pending) {
                SDL_مجموعه_Mouse_Focus(عدم);
            }
        }
    }
}

ساكن فراغ Emscripten_UpdateMouseFromEvent(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    إذا (پنجره_داده_2->پنجره->flags & SDL_پنجره_HIDDEN) {
        أرجع;
    }

    // rescale (in case canvas is being scaled)
    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &client_w, &client_h);
    ثابت مزدوج xscale = پنجره_داده_2->پنجره->w / client_w;
    ثابت مزدوج yscale = پنجره_داده_2->پنجره->h / client_h;

    ثابت bool is_اشاره_گر_Locked = پنجره_داده_2->has_اشاره_گر_قفل;
    عائم mx, my;
    إذا (is_اشاره_گر_Locked) {
        mx = (عائم)(event->movementX * xscale);
        my = (عائم)(event->movementY * yscale);
    } وإلا {
        mx = (عائم)(event->هدف_X * xscale);
        my = (عائم)(event->هدف_Y * yscale);
    }

    SDL_SendMouseMotion(0, پنجره_داده_2->پنجره, SDL_DEFAULT_MOUSE_ID, is_اشاره_گر_Locked, mx, my);

    Emscripten_HandleMouseButton(پنجره_داده_2, event);
}

ساكن فراغ Emscripten_UpdateTouchFromEvent(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    إذا (SDL_جمع_کن_Touch(deviceId, SDL_TOUCH_DEVICE_مستقیم, "") < 0) {
        أرجع;
    }

    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    عائم x, y;
    إذا (client_w <= 1) {
        x = 0.5f;
    } وإلا {
        x = event->هدف_X / (client_w - 1);
    }
    إذا (client_h <= 1) {
        y = 0.5f;
    } وإلا {
        y = event->هدف_Y / (client_h - 1);
    }

    ثابت bool پایین = (event->buttons & 1) != 0;
    إذا (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        إذا (پایین) {
            SDL_SendTouch(0, deviceId, id, پنجره_داده_2->پنجره, SDL_EVENT_FINGER_پایین, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, پنجره_داده_2->پنجره, x, y, 1.0f);

    إذا (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        إذا (!پایین) {
            SDL_SendTouch(0, deviceId, id, پنجره_داده_2->پنجره, SDL_EVENT_FINGER_به_بالا, x, y, 1.0f);
        }
    }
}

ساكن فراغ Emscripten_UpdatePenFromEvent(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_PEN);
    ثابت SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle((فراغ *) (size_t) 1);   // something > 0 for the single pen handle.
    إذا (pen) {
        // rescale (in case canvas is being scaled)
        مزدوج client_w, client_h;
        emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &client_w, &client_h);
        ثابت مزدوج xscale = پنجره_داده_2->پنجره->w / client_w;
        ثابت مزدوج yscale = پنجره_داده_2->پنجره->h / client_h;

        ثابت bool is_اشاره_گر_Locked = پنجره_داده_2->has_اشاره_گر_قفل;
        عائم mx, my;
        إذا (is_اشاره_گر_Locked) {
            mx = (عائم)(event->movementX * xscale);
            my = (عائم)(event->movementY * yscale);
        } وإلا {
            mx = (عائم)(event->هدف_X * xscale);
            my = (عائم)(event->هدف_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, پنجره_داده_2->پنجره, mx, my);

        إذا (event->button == 0) {  // pen touch
            bool پایین = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, پنجره_داده_2->پنجره, false, پایین);
        } وإلا إذا (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool پایین = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, پنجره_داده_2->پنجره, true, پایین);
        } وإلا إذا (event->button == 1) {
            bool پایین = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, پنجره_داده_2->پنجره, 2, پایین);
        } وإلا إذا (event->button == 2) {
            bool پایین = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, پنجره_داده_2->پنجره, 1, پایین);
        }

        SDL_SendPenAxis(0, pen, پنجره_داده_2->پنجره, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, پنجره_داده_2->پنجره, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, پنجره_داده_2->پنجره, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, پنجره_داده_2->پنجره, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, پنجره_داده_2->پنجره, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ساكن فراغ Emscripten_Update_اشاره_گر_From_Event(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_گر_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(پنجره_داده_2, event);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(پنجره_داده_2, event);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(پنجره_داده_2, event);
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساكن فراغ Emscripten_HandleMouseFocus(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event, bool isenter)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    إذا (پنجره_داده_2->پنجره->flags & SDL_پنجره_HIDDEN) {
        أرجع;
    }

    ثابت bool is_اشاره_گر_Locked = پنجره_داده_2->has_اشاره_گر_قفل;

    إذا (!is_اشاره_گر_Locked) {
        // rescale (in case canvas is being scaled)
        عائم mx, my;
        مزدوج client_w, client_h;
        emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &client_w, &client_h);

        mx = (عائم)(event->هدف_X * (پنجره_داده_2->پنجره->w / client_w));
        my = (عائم)(event->هدف_Y * (پنجره_داده_2->پنجره->h / client_h));
        SDL_SendMouseMotion(0, پنجره_داده_2->پنجره, SDL_GLOBAL_MOUSE_ID, is_اشاره_گر_Locked, mx, my);
    }

    إذا (isenter && پنجره_داده_2->mouse_focus_loss_pending) {
        پنجره_داده_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } وإلا إذا (!isenter && (پنجره_داده_2->پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
        پنجره_داده_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } وإلا {
        SDL_مجموعه_Mouse_Focus(isenter ? پنجره_داده_2->پنجره : عدم);
    }
}

ساكن فراغ Emscripten_HandlePenEnter(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle((فراغ *) (size_t) 1);  // something > 0 for the single pen handle.
    إذا (pen) {
        SDL_SendPenProximity(0, pen, پنجره_داده_2->پنجره, true, true);
    } وإلا {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.رقم_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_جمع_کن_Pen_Device(0, عدم, پنجره_داده_2->پنجره, &peninfo, (فراغ *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(پنجره_داده_2, event);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_گر_Enter(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_گر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(پنجره_داده_2, event, true);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(پنجره_داده_2, event);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_TOUCH) {
        // do nothing.
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساكن فراغ Emscripten_HandlePenLeave(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    ثابت SDL_PenID pen = SDL_پیدا_کن_Pen_By_Handle((فراغ *) (size_t) 1);   // something > 0 for the single pen handle.
    إذا (pen) {
        Emscripten_Update_اشاره_گر_From_Event(پنجره_داده_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, پنجره_داده_2->پنجره, false, false);
    }
}

ساكن فراغ Emscripten_HandleTouchCancel(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event->اشاره_گر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    إذا (SDL_جمع_کن_Touch(deviceId, SDL_TOUCH_DEVICE_مستقیم, "") < 0) {
        أرجع;
    }

    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(پنجره_داده_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    عائم x, y;
    إذا (client_w <= 1) {
        x = 0.5f;
    } وإلا {
        x = event->هدف_X / (client_w - 1);
    }
    إذا (client_h <= 1) {
        y = 0.5f;
    } وإلا {
        y = event->هدف_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, پنجره_داده_2->پنجره, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_گر_Leave(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_گر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(پنجره_داده_2, event, false);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(پنجره_داده_2, event);
    } وإلا إذا (event->اشاره_گر_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(پنجره_داده_2, event);
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_گر_Generic(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(event != عدم);
    Emscripten_Update_اشاره_گر_From_Event(پنجره_داده_2, event);
}

ساكن فراغ Emscripten_prep_اشاره_گر_event_callbacks(فراغ)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        إذا (SDL3.make_اشاره_گر_Event_CStruct === undefined) {
            SDL3.make_اشاره_گر_Event_CStruct = function(چپ, بالاترین, event) {
                var ptrtype = 0;
                إذا (event.اشاره_گر_Type == "mouse") {
                    ptrtype = 1;
                } وإلا إذا (event.اشاره_گر_Type == "touch") {
                    ptrtype = 2;
                } وإلا إذا (event.اشاره_گر_Type == "pen") {
                    ptrtype = 3;
                } وإلا {
                    أرجع 0;
                }

                var ptr = _SDL_malloc($0);
                إذا (ptr != 0) {
                    var idx = SDL3.CPtr_مقصد_Heap32_شاخص(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.اشاره_گر_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - چپ;
                    HEAPF32[idx++] = event.clientY - بالاترین;
                    إذا (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                أرجع ptr;
            };
        }
    }, حجم (Emscripten_اشاره_گر_Event));
}

ساكن فراغ Emscripten_مجموعه_اشاره_گر_event_callbacks(SDL_پنجره_داده *داده)
{
    Emscripten_prep_اشاره_گر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var هدف = document.querySelector(UTF8_مقصد_String($1));
        إذا (هدف) {
            var SDL3 = Module['SDL3'];
            var داده = $0;
            هدف.sdl_Event_Handler_اشاره_گر_Enter = function(event) {
                var rect = هدف.getBoundingClientRect();
                var d = SDL3.make_اشاره_گر_Event_CStruct(rect.چپ, rect.بالاترین, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_گر_Enter_2(SDL3.JSVar_مقصد_CPtr(داده), d);
                    _SDL_free(d);
                }
            };
            هدف.sdl_Event_Handler_اشاره_گر_Leave = function(event) {
                var rect = هدف.getBoundingClientRect();
                var d = SDL3.make_اشاره_گر_Event_CStruct(rect.چپ, rect.بالاترین, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_گر_Leave_2(SDL3.JSVar_مقصد_CPtr(داده), d);
                    _SDL_free(d);
                }
            };
            هدف.sdl_Event_Handler_اشاره_گر_Generic = function(event) {
                var rect = هدف.getBoundingClientRect();
                var d = SDL3.make_اشاره_گر_Event_CStruct(rect.چپ, rect.بالاترین, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_گر_Generic_2(SDL3.JSVar_مقصد_CPtr(داده), d);
                    _SDL_free(d);
                }
            };

            هدف.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            هدف.جمع_کن_Event_Listener("pointerenter", هدف.sdl_Event_Handler_اشاره_گر_Enter);
            هدف.جمع_کن_Event_Listener("pointerleave", هدف.sdl_Event_Handler_اشاره_گر_Leave);
            هدف.جمع_کن_Event_Listener("pointercancel", هدف.sdl_Event_Handler_اشاره_گر_Leave);
            هدف.جمع_کن_Event_Listener("pointerdown", هدف.sdl_Event_Handler_اشاره_گر_Generic);
            هدف.جمع_کن_Event_Listener("pointermove", هدف.sdl_Event_Handler_اشاره_گر_Generic);
            هدف.جمع_کن_Event_Listener("pointerup", هدف.sdl_Event_Handler_اشاره_گر_Generic);
        }
    }, داده, داده->canvas_id);
}

ساكن فراغ Emscripten_unset_اشاره_گر_event_callbacks(SDL_پنجره_داده *داده)
{
    MAIN_THREAD_EM_ASM({
        var هدف = document.querySelector(UTF8_مقصد_String($0));
        إذا (هدف) {
            هدف.removeEventListener("pointerenter", هدف.sdl_Event_Handler_اشاره_گر_Enter);
            هدف.removeEventListener("pointerleave", هدف.sdl_Event_Handler_اشاره_گر_Leave);
            هدف.removeEventListener("pointercancel", هدف.sdl_Event_Handler_اشاره_گر_Leave);
            هدف.removeEventListener("pointerdown", هدف.sdl_Event_Handler_اشاره_گر_Generic);
            هدف.removeEventListener("pointermove", هدف.sdl_Event_Handler_اشاره_گر_Generic);
            هدف.removeEventListener("pointerup", هدف.sdl_Event_Handler_اشاره_گر_Generic);
            هدف.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            هدف.sdl_Event_Handler_اشاره_گر_Enter = undefined;
            هدف.sdl_Event_Handler_اشاره_گر_Leave = undefined;
            هدف.sdl_Event_Handler_اشاره_گر_Generic = undefined;
        }
    }, داده->canvas_id);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_Mouse_Button_به_بالا_Global(SDL_VideoDevice *device, ثابت Emscripten_اشاره_گر_Event *event)
{
    SDL_assert(device != عدم);
    SDL_assert(event != عدم);
    إذا (event->اشاره_گر_type == PTRTYPE_MOUSE) {
        لكل (SDL_پنجره *پنجره = device->windows; پنجره; پنجره = پنجره->بعدی) {
            Emscripten_HandleMouseButton(پنجره->داخلی, event);
        }
    }
}

ساكن فراغ Emscripten_مجموعه_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_اشاره_گر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var هدف = document;
        إذا (هدف) {
            هدف.sdl_Event_Handler_Mouse_Button_به_بالا_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_اشاره_گر_Event_CStruct(0, 0, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_به_بالا_Global_2(SDL3.JSVar_مقصد_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            هدف.جمع_کن_Event_Listener("pointerup", هدف.sdl_Event_Handler_Mouse_Button_به_بالا_Global);
        }
    }, device);
}

ساكن فراغ Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var هدف = document;
        إذا (هدف) {
            هدف.removeEventListener("pointerup", هدف.sdl_Event_Handler_Mouse_Button_به_بالا_Global);
            هدف.sdl_Event_Handler_Mouse_Button_به_بالا_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
تعريفنوع بنية Emscripten_DropEvent
{
    صحيح x;
    صحيح y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragEvent(SDL_پنجره_داده *پنجره_داده_2, ثابت Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(پنجره_داده_2->پنجره, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragCompleteEvent(SDL_پنجره_داده *پنجره_داده_2)
{
    SDL_SendDropComplete(پنجره_داده_2->پنجره);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Send_Drag_متن_Event(SDL_پنجره_داده *پنجره_داده_2, حرف *متن)
{
    SDL_Send_Drop_متن(پنجره_داده_2->پنجره, متن);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragFileEvent(SDL_پنجره_داده *پنجره_داده_2, حرف *filename)
{
    SDL_SendDropFile(پنجره_داده_2->پنجره, عدم, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ساكن فراغ Emscripten_مجموعه_drag_event_callbacks(SDL_پنجره_داده *داده)
{
    MAIN_THREAD_EM_ASM({
        var هدف = document.querySelector(UTF8_مقصد_String($1));
        إذا (هدف) {
            var داده = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                إذا (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = هدف.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.چپ;
                    HEAP32[idx++] = event.clientY - rect.بالاترین;
                }
                أرجع ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); إذا (d != 0) { _Emscripten_SendDragEvent(داده, d); _SDL_free(d); }
            };
            هدف.جمع_کن_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_شمار = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                إذا (event.داده_Transfer.types.includes("text/plain")) {
                    let plain_متن = string_مقصد_New_UTF8(event.داده_Transfer.get_داده("text/plain"));
                    Emscripten_Send_Drag_متن_Event_2(داده, plain_متن);
                    _Emscripten_force_free(plain_متن);
                } وإلا إذا (event.داده_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ثابت files_مقصد_read = event.داده_Transfer.files.درازی;
                    لكل (let i = 0; i < files_مقصد_read; i++) {
                        ثابت file = event.داده_Transfer.files.قلم(i);
                        ثابت file_reader = new FileReader();
                        file_reader.read_As_Array_میانگیر(file);
                        file_reader.onload = function(event) {
                            ثابت fs_dropdir = `/tmp/filedrop/${SDL3.drop_شمار}`;
                            SDL3.drop_شمار += 1;

                            ثابت fs_filepath = `${fs_dropdir}/${file.name}`;
                            ثابت c_fs_filepath = string_مقصد_New_UTF8(fs_filepath);
                            ثابت contents_array8 = new Uint8Array(event.هدف.نتیجه);

                            try {
                                FS.mkdir(fs_dropdir);
                                var جریان = FS.open(fs_filepath, "w");
                                FS.اكتب(جریان, contents_array8, 0, contents_array8.درازی, 0);
                                FS.close(جریان);
                                _Emscripten_SendDragFileEvent(داده, c_fs_filepath);
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
                        إذا (files_read === files_مقصد_read) {
                            _Emscripten_SendDragCompleteEvent(داده);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(داده);
            };
            هدف.جمع_کن_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(داده);
            };
            هدف.جمع_کن_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            هدف.جمع_کن_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, داده, داده->canvas_id, حجم (Emscripten_DropEvent));
}

ساكن فراغ Emscripten_unset_drag_event_callbacks(SDL_پنجره_داده *داده)
{
    MAIN_THREAD_EM_ASM({
        var هدف = document.querySelector(UTF8_مقصد_String($0));
        إذا (هدف) {
            var SDL3 = Module['SDL3'];
            هدف.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            هدف.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            هدف.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_شمار = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ثابت p = `${dirpath}/${filename}`;
                    ثابت p_s = FS.stat(p);
                    إذا (FS.isFile(p_s.نما)) {
                        FS.unlink(p);
                    } وإلا إذا (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            هدف.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, داده->canvas_id);
}

ساكن ثابت حرف *Emscripten_Get_Keyboard_هدف_Element(ثابت حرف *هدف)
{
    إذا (SDL_strcmp(هدف, "#none") == 0) {
        أرجع عدم;
    } وإلا إذا (SDL_strcmp(هدف, "#window") == 0) {
        أرجع EMSCRIPTEN_EVENT_هدف_پنجره;
    } وإلا إذا (SDL_strcmp(هدف, "#document") == 0) {
        أرجع EMSCRIPTEN_EVENT_هدف_DOCUMENT;
    } وإلا إذا (SDL_strcmp(هدف, "#screen") == 0) {
        أرجع EMSCRIPTEN_EVENT_هدف_SCREEN;
    }

    أرجع هدف;
}

فراغ Emscripten_ثبات_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_مجموعه_global_mouseup_callback(device);

    emscripten_مجموعه_focus_callback(EMSCRIPTEN_EVENT_هدف_پنجره, device, 0, Emscripten_HandleFocus);
    emscripten_مجموعه_blur_callback(EMSCRIPTEN_EVENT_هدف_پنجره, device, 0, Emscripten_HandleFocus);

    emscripten_مجموعه_pointerlockchange_callback(EMSCRIPTEN_EVENT_هدف_DOCUMENT, device, 0, Emscripten_Handle_اشاره_گر_قفل_Change_Global);

    emscripten_مجموعه_fullscreenchange_callback(EMSCRIPTEN_EVENT_هدف_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_مجموعه_resize_callback(EMSCRIPTEN_EVENT_هدف_پنجره, device, 0, Emscripten_HandleResizeGlobal);
}

فراغ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_مجموعه_focus_callback(EMSCRIPTEN_EVENT_هدف_پنجره, عدم, 0, عدم);
    emscripten_مجموعه_blur_callback(EMSCRIPTEN_EVENT_هدف_پنجره, عدم, 0, عدم);

    emscripten_مجموعه_pointerlockchange_callback(EMSCRIPTEN_EVENT_هدف_DOCUMENT, عدم, 0, عدم);

    emscripten_مجموعه_fullscreenchange_callback(EMSCRIPTEN_EVENT_هدف_DOCUMENT, عدم, 0, عدم);

    emscripten_مجموعه_resize_callback(EMSCRIPTEN_EVENT_هدف_پنجره, عدم, 0, عدم);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_قفل_کلیدها_Check(SDL_پنجره_داده *پنجره_داده_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ثابت SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_رقم : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    إذا ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_رقم|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_رقم|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_مجموعه_Mod_State(modstate);
    }
}

فراغ Emscripten_ثبات_Event_Handlers(SDL_پنجره_داده *داده)
{
    ثابت حرف *کلید_Element;

    // There is only one window and that window is the canvas
    emscripten_مجموعه_wheel_callback(داده->canvas_id, داده, 0, Emscripten_HandleWheel);

    emscripten_مجموعه_orientationchange_callback(داده, 0, Emscripten_HandleOrientationChange);

    کلید_Element = Emscripten_Get_Keyboard_هدف_Element(داده->keyboard_element);
    إذا (کلید_Element) {
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
        emscripten_مجموعه_keydown_callback(کلید_Element, عدم, 0, عدم);
        emscripten_مجموعه_keyup_callback(کلید_Element, عدم, 0, عدم);
        emscripten_مجموعه_keypress_callback(کلید_Element, عدم, 0, عدم);

        MAIN_THREAD_EM_ASM_INT({
            var داده = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            إذا (document.sdl_Event_Handler_قفل_کلیدها_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_قفل_کلیدها_Check);
            }

            document.sdl_Event_Handler_قفل_کلیدها_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                إذا ((event.کلید != "CapsLock") && (event.کلید != "NumLock") && (event.کلید != "ScrollLock"))
                {
                    Emscripten_Handle_قفل_کلیدها_Check_2(Module['SDL3'].JSVar_مقصد_CPtr(داده), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.جمع_کن_Event_Listener("keydown", document.sdl_Event_Handler_قفل_کلیدها_Check);
        }, داده);
        emscripten_مجموعه_keydown_callback(کلید_Element, داده, 0, Emscripten_Handle_کلید);
        emscripten_مجموعه_keyup_callback(کلید_Element, داده, 0, Emscripten_Handle_کلید);
        emscripten_مجموعه_keypress_callback(کلید_Element, داده, 0, Emscripten_Handle_کلید_Press);
    }

    emscripten_مجموعه_visibilitychange_callback(داده, 0, Emscripten_HandleVisibilityChange);

    emscripten_مجموعه_beforeunload_callback(داده, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_مجموعه_اشاره_گر_event_callbacks(داده);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_مجموعه_drag_event_callbacks(داده);
}

فراغ Emscripten_UnregisterEventHandlers(SDL_پنجره_داده *داده)
{
    ثابت حرف *کلید_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(داده);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_اشاره_گر_event_callbacks(داده);

    // only works due to having one window
    emscripten_مجموعه_wheel_callback(داده->canvas_id, عدم, 0, عدم);

    emscripten_مجموعه_orientationchange_callback(عدم, 0, عدم);

    کلید_Element = Emscripten_Get_Keyboard_هدف_Element(داده->keyboard_element);
    إذا (کلید_Element) {
        emscripten_مجموعه_keydown_callback(کلید_Element, عدم, 0, عدم);
        emscripten_مجموعه_keyup_callback(کلید_Element, عدم, 0, عدم);
        emscripten_مجموعه_keypress_callback(کلید_Element, عدم, 0, عدم);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_قفل_کلیدها_Check);
        });
    }

    emscripten_مجموعه_visibilitychange_callback(عدم, 0, عدم);

    emscripten_مجموعه_beforeunload_callback(عدم, عدم);
}

#پایان_اگر // SDL_VIDEO_DRIVER_EMSCRIPTEN
