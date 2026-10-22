/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "SDL3/SDL_scancode.h"
#ضمن "SDL3/SDL_events.h"
#ضمن "SDL_qnx.h"
#ضمن <sys/keycodes.h>

/**
 * A map that translates Screen key names to SDL scan codes.
 * This map is incomplete, but should include most major keys.
 */
ساكن صحيح کلی_منزل_sdl[] = {
    [KEYCODE_SPACE] = SDL_SCANCODE_SPACE,
    [KEYCODE_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE,
    [KEYCODE_COMMA] = SDL_SCANCODE_COMMA,
    [KEYCODE_MINUS] = SDL_SCANCODE_MINUS,
    [KEYCODE_PERIOD] = SDL_SCANCODE_PERIOD,
    [KEYCODE_SLASH] = SDL_SCANCODE_SLASH,
    [KEYCODE_ZERO] = SDL_SCANCODE_0,
    [KEYCODE_ONE] = SDL_SCANCODE_1,
    [KEYCODE_TWO] = SDL_SCANCODE_2,
    [KEYCODE_THREE] = SDL_SCANCODE_3,
    [KEYCODE_FOUR] = SDL_SCANCODE_4,
    [KEYCODE_FIVE] = SDL_SCANCODE_5,
    [KEYCODE_SIX] = SDL_SCANCODE_6,
    [KEYCODE_SEVEN] = SDL_SCANCODE_7,
    [KEYCODE_EIGHT] = SDL_SCANCODE_8,
    [KEYCODE_NINE] = SDL_SCANCODE_9,
    [KEYCODE_SEMICOLON] = SDL_SCANCODE_SEMICOLON,
    [KEYCODE_EQUAL] = SDL_SCANCODE_EQUALS,
    [KEYCODE_کیڼ_BRACKET] = SDL_SCANCODE_LEFTBRACKET,
    [KEYCODE_شا_SLASH] = SDL_SCANCODE_BACKSLASH,
    [KEYCODE_ښی_BRACKET] = SDL_SCANCODE_RIGHTBRACKET,
    [KEYCODE_GRAVE] = SDL_SCANCODE_GRAVE,
    [KEYCODE_A] = SDL_SCANCODE_A,
    [KEYCODE_B] = SDL_SCANCODE_B,
    [KEYCODE_C] = SDL_SCANCODE_C,
    [KEYCODE_D] = SDL_SCANCODE_D,
    [KEYCODE_E] = SDL_SCANCODE_E,
    [KEYCODE_F] = SDL_SCANCODE_F,
    [KEYCODE_G] = SDL_SCANCODE_G,
    [KEYCODE_H] = SDL_SCANCODE_H,
    [KEYCODE_I] = SDL_SCANCODE_I,
    [KEYCODE_J] = SDL_SCANCODE_J,
    [KEYCODE_K] = SDL_SCANCODE_K,
    [KEYCODE_L] = SDL_SCANCODE_L,
    [KEYCODE_M] = SDL_SCANCODE_M,
    [KEYCODE_N] = SDL_SCANCODE_N,
    [KEYCODE_O] = SDL_SCANCODE_O,
    [KEYCODE_P] = SDL_SCANCODE_P,
    [KEYCODE_Q] = SDL_SCANCODE_Q,
    [KEYCODE_R] = SDL_SCANCODE_R,
    [KEYCODE_S] = SDL_SCANCODE_S,
    [KEYCODE_T] = SDL_SCANCODE_T,
    [KEYCODE_U] = SDL_SCANCODE_U,
    [KEYCODE_V] = SDL_SCANCODE_V,
    [KEYCODE_W] = SDL_SCANCODE_W,
    [KEYCODE_X] = SDL_SCANCODE_X,
    [KEYCODE_Y] = SDL_SCANCODE_Y,
    [KEYCODE_Z] = SDL_SCANCODE_Z,
    [KEYCODE_پورته] = SDL_SCANCODE_پورته,
    [KEYCODE_ښکته] = SDL_SCANCODE_ښکته,
    [KEYCODE_کیڼ] = SDL_SCANCODE_کیڼ,
    [KEYCODE_PG_پورته] = SDL_SCANCODE_PAGEUP,
    [KEYCODE_PG_ښکته] = SDL_SCANCODE_PAGEDOWN,
    [KEYCODE_PRINT] = SDL_SCANCODE_PRINTSCREEN,
    [KEYCODE_SCROLL_قلف] = SDL_SCANCODE_SCROLLLOCK,
    [KEYCODE_PAUSE] = SDL_SCANCODE_PAUSE,
    [KEYCODE_ورننباسه] = SDL_SCANCODE_ورننباسه,
    [KEYCODE_HOME] = SDL_SCANCODE_HOME,
    [KEYCODE_DELETE] = SDL_SCANCODE_DELETE,
    [KEYCODE_پای_ټکی] = SDL_SCANCODE_پای_ټکی,
    [KEYCODE_عدد_قلف] = SDL_SCANCODE_NUMLOCKCLEAR,
    [KEYCODE_ښی] = SDL_SCANCODE_ښی,
    [KEYCODE_RETURN] = SDL_SCANCODE_RETURN,
    [KEYCODE_TAB] = SDL_SCANCODE_TAB,
    [KEYCODE_ESCAPE] = SDL_SCANCODE_ESCAPE,
    [KEYCODE_کیڼ_CTRL] = SDL_SCANCODE_LCTRL,
    [KEYCODE_ښی_CTRL] = SDL_SCANCODE_RCTRL,
    [KEYCODE_کیڼ_ښويدنه] = SDL_SCANCODE_LSHIFT,
    [KEYCODE_ښی_ښويدنه] = SDL_SCANCODE_RSHIFT,
    [KEYCODE_کیڼ_ALT] = SDL_SCANCODE_LALT,
    [KEYCODE_ښی_ALT] = SDL_SCANCODE_RALT,
    [KEYCODE_BACKSPACE] = SDL_SCANCODE_BACKSPACE,
    [KEYCODE_CAPS_قلف] = SDL_SCANCODE_CAPSLOCK,
    [KEYCODE_F1] = SDL_SCANCODE_F1,
    [KEYCODE_F2] = SDL_SCANCODE_F2,
    [KEYCODE_F3] = SDL_SCANCODE_F3,
    [KEYCODE_F4] = SDL_SCANCODE_F4,
    [KEYCODE_F5] = SDL_SCANCODE_F5,
    [KEYCODE_F6] = SDL_SCANCODE_F6,
    [KEYCODE_F7] = SDL_SCANCODE_F7,
    [KEYCODE_F8] = SDL_SCANCODE_F8,
    [KEYCODE_F9] = SDL_SCANCODE_F9,
    [KEYCODE_F10] = SDL_SCANCODE_F10,
    [KEYCODE_F11] = SDL_SCANCODE_F11,
    [KEYCODE_F12] = SDL_SCANCODE_F12,
    [KEYCODE_KP_DIVIDE] = SDL_SCANCODE_KP_DIVIDE,
    [KEYCODE_KP_MULTIPLY] = SDL_SCANCODE_KP_MULTIPLY,
    [KEYCODE_KP_MINUS] = SDL_SCANCODE_KP_MINUS,
    [KEYCODE_KP_PLUS] = SDL_SCANCODE_KP_PLUS,
    [KEYCODE_KP_ENTER] = SDL_SCANCODE_KP_ENTER,
    [KEYCODE_KP_ورننباسه] = SDL_SCANCODE_KP_0,
    [KEYCODE_KP_پای_ټکی] = SDL_SCANCODE_KP_1,
    [KEYCODE_KP_ښکته] = SDL_SCANCODE_KP_2,
    [KEYCODE_KP_PG_ښکته] = SDL_SCANCODE_KP_3,
    [KEYCODE_KP_کیڼ] = SDL_SCANCODE_KP_4,
    [KEYCODE_KP_FIVE] = SDL_SCANCODE_KP_5,
    [KEYCODE_KP_ښی] = SDL_SCANCODE_KP_6,
    [KEYCODE_KP_HOME] = SDL_SCANCODE_KP_7,
    [KEYCODE_KP_پورته] = SDL_SCANCODE_KP_8,
    [KEYCODE_KP_PG_پورته] = SDL_SCANCODE_KP_9,
    [KEYCODE_KP_DELETE] = SDL_SCANCODE_KP_PERIOD,
    [KEYCODE_POWER] = SDL_SCANCODE_POWER,
    [KEYCODE_PLAY] = SDL_SCANCODE_EXECUTE,
    [KEYCODE_HELP] = SDL_SCANCODE_HELP,
    [KEYCODE_MENU] = SDL_SCANCODE_MENU,
    [KEYCODE_AC_SELECT_ALL] = SDL_SCANCODE_SELECT,
    [KEYCODE_STOP] = SDL_SCANCODE_STOP,
    [KEYCODE_AC_UNDO] = SDL_SCANCODE_UNDO,
    [KEYCODE_AC_CUT] = SDL_SCANCODE_CUT,
    [KEYCODE_AC_COPY] = SDL_SCANCODE_COPY,
    [KEYCODE_AC_PASTE] = SDL_SCANCODE_PASTE,
    [KEYCODE_AC_پیدا_کړه] = SDL_SCANCODE_پیدا_کړه,
    [KEYCODE_MUTE] = SDL_SCANCODE_MUTE,
    [KEYCODE_VOLUME_پورته] = SDL_SCANCODE_VOLUMEUP,
    [KEYCODE_VOLUME_ښکته] = SDL_SCANCODE_VOLUMEDOWN,
    [KEYCODE_SYSREQ] = SDL_SCANCODE_SYSREQ,
    [KEYCODE_AC_CANCEL] = SDL_SCANCODE_CANCEL,
    [KEYCODE_AC_پلټنه] = SDL_SCANCODE_AC_پلټنه,
    [KEYCODE_AC_HOME] = SDL_SCANCODE_AC_HOME,
    [KEYCODE_AC_شا] = SDL_SCANCODE_AC_شا,
    [KEYCODE_AC_FORWARD] = SDL_SCANCODE_AC_FORWARD,
    [KEYCODE_AC_STOP] = SDL_SCANCODE_AC_STOP,
    [KEYCODE_AC_REFRESH] = SDL_SCANCODE_AC_REFRESH,
    [KEYCODE_AC_BOOKMARKS] = SDL_SCANCODE_AC_BOOKMARKS,
    [KEYCODE_EJECT] = SDL_SCANCODE_MEDIA_EJECT,
    [KEYCODE_SLEEP] = SDL_SCANCODE_SLEEP,
};

/**
 * Called from the event dispatcher when a keyboard event is encountered.
 * Translates the event such that it can be handled by SDL.
 */
فراغ handleKeyboardEvent(screen_event_t event)
{
    صحيح             val;
    صحيح             cap;
    حرف            ascii_متن[2];
    SDL_Scancode    scancode;

    // Get the key value.
    إذا (screen_get_event_property_iv(event, SCREEN_PROPERTY_SYM, &val) < 0) {
        أرجع;
    }

    إذا (screen_get_event_property_iv(event, SCREEN_PROPERTY_کلی_CAP, &cap) < 0) {
        أرجع;
    }

    // Skip unrecognized keys.
    إذا ((val < 0) || (val >= SDL_arraysize(کلی_منزل_sdl))) {
        أرجع;
    }

    // Translate to an SDL scan code.
    scancode = کلی_منزل_sdl[val];
    إذا (scancode == 0) {
        أرجع;
    }

    // Get event flags (key state).
    إذا (screen_get_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &val) < 0) {
        أرجع;
    }

    // Propagate the event to SDL.
    // FIXME:
    // Need to handle more key states (such as key combinations).
    إذا (val & کلی_ښکته) {
        SDL_Send_Keyboard_کلی(0, SDL_DEFAULT_KEYBOARD_ID, val, scancode, true);

        // TODO: To simplify, we're ignoring keycodes that aren't just ascii.
        إذا ((val < UNICODE_شخصي_USE_AREA_لومړی) && ((cap & 0xFF) == cap)) {
            ascii_متن[0] = cap;
            ascii_متن[1] = 0;
            SDL_Send_Keyboard_متن(ascii_متن);
        } وإلا إذا ((KEYCODE_PC_کلیګانې <= val) && (val < KEYCODE_مصرفوونکی_کلیګانې)) {
            ascii_متن[0] = val & 0xFF;
            ascii_متن[1] = 0;
            SDL_Send_Keyboard_متن(ascii_متن);
        }
    } وإلا {
        SDL_Send_Keyboard_کلی(0, SDL_DEFAULT_KEYBOARD_ID, val, scancode, false);
    }
}
