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

#ifdef SDL_VIDEO_DRIVER_DOSVESA

#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_dosvideo.h"

#अन्तर्भाव "../../core/dos/SDL_dos_scheduler.h"
#अन्तर्भाव "SDL_dosevents_c.h"

// PS/2 keyboard controller port
#define KBD_DATA_PORT 0x60

// Scancode byte structure
#define SCANCODE_MASK    0x7F // bits 0-6: scancode index
#define SCANCODE_RELEASE 0x80 // bit 7: key released (break code)

// Multi-byte scancode prefixes
#define SCANCODE_PREFIX_EXTENDED 0xE0 // extended key prefix
#define SCANCODE_PREFIX_PAUSE    0xE1 // pause key sequence prefix

// VGA Input Status Register 1 (for vblank detection)
#define VGA_STATUS_PORT   0x3DA
#define VGA_STATUS_VBLANK 0x08 // bit 3: vertical retrace active

// Scancode table: https://www.plantation-productions.com/Webster/www.artofasm.com/DOS/pdf/apndxc.pdf
स्थिर ध्रुव SDL_Scancode DOSVESA_ScancodeMapping[] = { // index is the scancode from the IRQ1 handler bitwise-ANDed against 0x7F.
    /* 0x00 */ SDL_SCANCODE_UNKNOWN,
    /* 0x01 */ SDL_SCANCODE_ESCAPE,
    /* 0x02 */ SDL_SCANCODE_1,
    /* 0x03 */ SDL_SCANCODE_2,
    /* 0x04 */ SDL_SCANCODE_3,
    /* 0x05 */ SDL_SCANCODE_4,
    /* 0x06 */ SDL_SCANCODE_5,
    /* 0x07 */ SDL_SCANCODE_6,
    /* 0x08 */ SDL_SCANCODE_7,
    /* 0x09 */ SDL_SCANCODE_8,
    /* 0x0A */ SDL_SCANCODE_9,
    /* 0x0B */ SDL_SCANCODE_0,
    /* 0x0C */ SDL_SCANCODE_MINUS,
    /* 0x0D */ SDL_SCANCODE_EQUALS,
    /* 0x0E */ SDL_SCANCODE_BACKSPACE,
    /* 0x0F */ SDL_SCANCODE_TAB,

    /* 0x10 */ SDL_SCANCODE_Q,
    /* 0x11 */ SDL_SCANCODE_W,
    /* 0x12 */ SDL_SCANCODE_E,
    /* 0x13 */ SDL_SCANCODE_R,
    /* 0x14 */ SDL_SCANCODE_T,
    /* 0x15 */ SDL_SCANCODE_Y,
    /* 0x16 */ SDL_SCANCODE_U,
    /* 0x17 */ SDL_SCANCODE_I,
    /* 0x18 */ SDL_SCANCODE_O,
    /* 0x19 */ SDL_SCANCODE_P,
    /* 0x1A */ SDL_SCANCODE_LEFTBRACKET,
    /* 0x1B */ SDL_SCANCODE_RIGHTBRACKET,
    /* 0x1C */ SDL_SCANCODE_RETURN,
    /* 0x1D */ SDL_SCANCODE_LCTRL,
    /* 0x1E */ SDL_SCANCODE_A,
    /* 0x1F */ SDL_SCANCODE_S,

    /* 0x20 */ SDL_SCANCODE_D,
    /* 0x21 */ SDL_SCANCODE_F,
    /* 0x22 */ SDL_SCANCODE_G,
    /* 0x23 */ SDL_SCANCODE_H,
    /* 0x24 */ SDL_SCANCODE_J,
    /* 0x25 */ SDL_SCANCODE_K,
    /* 0x26 */ SDL_SCANCODE_L,
    /* 0x27 */ SDL_SCANCODE_SEMICOLON,
    /* 0x28 */ SDL_SCANCODE_APOSTROPHE,
    /* 0x29 */ SDL_SCANCODE_GRAVE,
    /* 0x2A */ SDL_SCANCODE_LSHIFT,
    /* 0x2B */ SDL_SCANCODE_BACKSLASH,
    /* 0x2C */ SDL_SCANCODE_Z,
    /* 0x2D */ SDL_SCANCODE_X,
    /* 0x2E */ SDL_SCANCODE_C,
    /* 0x2F */ SDL_SCANCODE_V,

    /* 0x30 */ SDL_SCANCODE_B,
    /* 0x31 */ SDL_SCANCODE_N,
    /* 0x32 */ SDL_SCANCODE_M,
    /* 0x33 */ SDL_SCANCODE_COMMA,
    /* 0x34 */ SDL_SCANCODE_PERIOD,
    /* 0x35 */ SDL_SCANCODE_SLASH,
    /* 0x36 */ SDL_SCANCODE_RSHIFT,
    /* 0x37 */ SDL_SCANCODE_KP_MULTIPLY,
    /* 0x38 */ SDL_SCANCODE_LALT,
    /* 0x39 */ SDL_SCANCODE_SPACE,
    /* 0x3A */ SDL_SCANCODE_CAPSLOCK,
    /* 0x3B */ SDL_SCANCODE_F1,
    /* 0x3C */ SDL_SCANCODE_F2,
    /* 0x3D */ SDL_SCANCODE_F3,
    /* 0x3E */ SDL_SCANCODE_F4,
    /* 0x3F */ SDL_SCANCODE_F5,

    /* 0x040 */ SDL_SCANCODE_F6,
    /* 0x041 */ SDL_SCANCODE_F7,
    /* 0x042 */ SDL_SCANCODE_F8,
    /* 0x043 */ SDL_SCANCODE_F9,
    /* 0x044 */ SDL_SCANCODE_F10,
    /* 0x045 */ SDL_SCANCODE_NUMLOCKCLEAR,
    /* 0x046 */ SDL_SCANCODE_SCROLLLOCK,
    /* 0x047 */ SDL_SCANCODE_KP_7,
    /* 0x048 */ SDL_SCANCODE_KP_8,
    /* 0x049 */ SDL_SCANCODE_KP_9,
    /* 0x04A */ SDL_SCANCODE_KP_MINUS,
    /* 0x04B */ SDL_SCANCODE_KP_4,
    /* 0x04C */ SDL_SCANCODE_KP_5,
    /* 0x04D */ SDL_SCANCODE_KP_6,
    /* 0x04E */ SDL_SCANCODE_KP_PLUS,
    /* 0x04F */ SDL_SCANCODE_KP_1,

    /* 0x050 */ SDL_SCANCODE_KP_2,
    /* 0x051 */ SDL_SCANCODE_KP_3,
    /* 0x052 */ SDL_SCANCODE_KP_0,
    /* 0x053 */ SDL_SCANCODE_KP_PERIOD,
    /* 0x054 */ SDL_SCANCODE_UNKNOWN,
    /* 0x055 */ SDL_SCANCODE_UNKNOWN,
    /* 0x056 */ SDL_SCANCODE_UNKNOWN,
    /* 0x057 */ SDL_SCANCODE_F11,
    /* 0x058 */ SDL_SCANCODE_F12
};

// Extended scancode table for keys prefixed with 0xE0
स्थिर ध्रुव SDL_Scancode DOSVESA_ExtendedScancodeMapping[] = { // index is the scancode byte following the 0xE0 prefix, masked with 0x7F.
    /* 0x00 */ SDL_SCANCODE_UNKNOWN,
    /* 0x01 */ SDL_SCANCODE_UNKNOWN,
    /* 0x02 */ SDL_SCANCODE_UNKNOWN,
    /* 0x03 */ SDL_SCANCODE_UNKNOWN,
    /* 0x04 */ SDL_SCANCODE_UNKNOWN,
    /* 0x05 */ SDL_SCANCODE_UNKNOWN,
    /* 0x06 */ SDL_SCANCODE_UNKNOWN,
    /* 0x07 */ SDL_SCANCODE_UNKNOWN,
    /* 0x08 */ SDL_SCANCODE_UNKNOWN,
    /* 0x09 */ SDL_SCANCODE_UNKNOWN,
    /* 0x0A */ SDL_SCANCODE_UNKNOWN,
    /* 0x0B */ SDL_SCANCODE_UNKNOWN,
    /* 0x0C */ SDL_SCANCODE_UNKNOWN,
    /* 0x0D */ SDL_SCANCODE_UNKNOWN,
    /* 0x0E */ SDL_SCANCODE_UNKNOWN,
    /* 0x0F */ SDL_SCANCODE_UNKNOWN,

    /* 0x10 */ SDL_SCANCODE_UNKNOWN,
    /* 0x11 */ SDL_SCANCODE_UNKNOWN,
    /* 0x12 */ SDL_SCANCODE_UNKNOWN,
    /* 0x13 */ SDL_SCANCODE_UNKNOWN,
    /* 0x14 */ SDL_SCANCODE_UNKNOWN,
    /* 0x15 */ SDL_SCANCODE_UNKNOWN,
    /* 0x16 */ SDL_SCANCODE_UNKNOWN,
    /* 0x17 */ SDL_SCANCODE_UNKNOWN,
    /* 0x18 */ SDL_SCANCODE_UNKNOWN,
    /* 0x19 */ SDL_SCANCODE_UNKNOWN,
    /* 0x1A */ SDL_SCANCODE_UNKNOWN,
    /* 0x1B */ SDL_SCANCODE_UNKNOWN,
    /* 0x1C */ SDL_SCANCODE_KP_ENTER,
    /* 0x1D */ SDL_SCANCODE_RCTRL,
    /* 0x1E */ SDL_SCANCODE_UNKNOWN,
    /* 0x1F */ SDL_SCANCODE_UNKNOWN,

    /* 0x20 */ SDL_SCANCODE_UNKNOWN,
    /* 0x21 */ SDL_SCANCODE_UNKNOWN,
    /* 0x22 */ SDL_SCANCODE_UNKNOWN,
    /* 0x23 */ SDL_SCANCODE_UNKNOWN,
    /* 0x24 */ SDL_SCANCODE_UNKNOWN,
    /* 0x25 */ SDL_SCANCODE_UNKNOWN,
    /* 0x26 */ SDL_SCANCODE_UNKNOWN,
    /* 0x27 */ SDL_SCANCODE_UNKNOWN,
    /* 0x28 */ SDL_SCANCODE_UNKNOWN,
    /* 0x29 */ SDL_SCANCODE_UNKNOWN,
    /* 0x2A */ SDL_SCANCODE_UNKNOWN, // fake left shift, ignore
    /* 0x2B */ SDL_SCANCODE_UNKNOWN,
    /* 0x2C */ SDL_SCANCODE_UNKNOWN,
    /* 0x2D */ SDL_SCANCODE_UNKNOWN,
    /* 0x2E */ SDL_SCANCODE_UNKNOWN,
    /* 0x2F */ SDL_SCANCODE_UNKNOWN,

    /* 0x30 */ SDL_SCANCODE_UNKNOWN,
    /* 0x31 */ SDL_SCANCODE_UNKNOWN,
    /* 0x32 */ SDL_SCANCODE_UNKNOWN,
    /* 0x33 */ SDL_SCANCODE_UNKNOWN,
    /* 0x34 */ SDL_SCANCODE_UNKNOWN,
    /* 0x35 */ SDL_SCANCODE_KP_DIVIDE,
    /* 0x36 */ SDL_SCANCODE_UNKNOWN, // fake right shift, ignore
    /* 0x37 */ SDL_SCANCODE_PRINTSCREEN,
    /* 0x38 */ SDL_SCANCODE_RALT,
    /* 0x39 */ SDL_SCANCODE_UNKNOWN,
    /* 0x3A */ SDL_SCANCODE_UNKNOWN,
    /* 0x3B */ SDL_SCANCODE_UNKNOWN,
    /* 0x3C */ SDL_SCANCODE_UNKNOWN,
    /* 0x3D */ SDL_SCANCODE_UNKNOWN,
    /* 0x3E */ SDL_SCANCODE_UNKNOWN,
    /* 0x3F */ SDL_SCANCODE_UNKNOWN,

    /* 0x40 */ SDL_SCANCODE_UNKNOWN,
    /* 0x41 */ SDL_SCANCODE_UNKNOWN,
    /* 0x42 */ SDL_SCANCODE_UNKNOWN,
    /* 0x43 */ SDL_SCANCODE_UNKNOWN,
    /* 0x44 */ SDL_SCANCODE_UNKNOWN,
    /* 0x45 */ SDL_SCANCODE_UNKNOWN,
    /* 0x46 */ SDL_SCANCODE_PAUSE, // Ctrl+Break sends E0 46 E0 C6
    /* 0x47 */ SDL_SCANCODE_HOME,
    /* 0x48 */ SDL_SCANCODE_UP,
    /* 0x49 */ SDL_SCANCODE_PAGEUP,
    /* 0x4A */ SDL_SCANCODE_UNKNOWN,
    /* 0x4B */ SDL_SCANCODE_वामः,
    /* 0x4C */ SDL_SCANCODE_UNKNOWN,
    /* 0x4D */ SDL_SCANCODE_दक्षिणः,
    /* 0x4E */ SDL_SCANCODE_UNKNOWN,
    /* 0x4F */ SDL_SCANCODE_END,

    /* 0x50 */ SDL_SCANCODE_DOWN,
    /* 0x51 */ SDL_SCANCODE_PAGEDOWN,
    /* 0x52 */ SDL_SCANCODE_निवेशय,
    /* 0x53 */ SDL_SCANCODE_DELETE,
    /* 0x54 */ SDL_SCANCODE_UNKNOWN,
    /* 0x55 */ SDL_SCANCODE_UNKNOWN,
    /* 0x56 */ SDL_SCANCODE_UNKNOWN,
    /* 0x57 */ SDL_SCANCODE_UNKNOWN,
    /* 0x58 */ SDL_SCANCODE_UNKNOWN,
    /* 0x59 */ SDL_SCANCODE_UNKNOWN,
    /* 0x5A */ SDL_SCANCODE_UNKNOWN,
    /* 0x5B */ SDL_SCANCODE_LGUI,
    /* 0x5C */ SDL_SCANCODE_RGUI,
    /* 0x5D */ SDL_SCANCODE_APPLICATION
};

स्थिर Uint8 keyevents_ringbuffer[256];
स्थिर पूर्णाङ्क keyevents_head = 0;
स्थिर पूर्णाङ्क keyevents_tail = 0;

स्थिर शून्य DOSVESA_DrainBIOSKeyboardBuffer(शून्य)
{
    __dpmi_regs regs;
    प्रति (;;) {
        regs.h.ah = 0x01; // BIOS: check for keystroke
        __dpmi_int(0x16, &regs);
        जइ (regs.x.flags & 0x40) { // ZF set = buffer empty
            भङ्ग;
        }
        regs.h.ah = 0x00; // BIOS: read keystroke (removes it)
        __dpmi_int(0x16, &regs);
    }
}

शून्य DOSVESA_PumpEvents(SDL_VideoDevice *device)
{
    /* Give cooperative threads a chance to run.  Audio mixing now runs
       in its own cooperative thread (via SDL's normal audio thread),
       so it will execute during this yield along with loading threads
       and anything else that is runnable. */
    DOS_Yield();

    स्थिर bool is_extended = false;
    स्थिर पूर्णाङ्क pause_sequence_remaining = 0;

    जाव (keyevents_head != keyevents_tail) {
        ध्रुव Uint8 event = keyevents_ringbuffer[keyevents_tail];
        keyevents_tail = (keyevents_tail + 1) & (SDL_arraysize(keyevents_ringbuffer) - 1);

        // Handle remaining bytes of E1 Pause key sequence (E1 1D 45 E1 9D C5).
        जइ (pause_sequence_remaining > 0) {
            pause_sequence_remaining--;
            अनुवर्त;
        }

        // Pause key sends a multi-byte sequence: E1 1D 45 E1 9D C5. Emit PAUSE press+release and consume the rest.
        जइ (event == SCANCODE_PREFIX_PAUSE) {
            pause_sequence_remaining = 5; // skip the next 5 bytes
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_PAUSE, true);
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, SDL_SCANCODE_PAUSE, false);
            अनुवर्त;
        }

        जइ (event == SCANCODE_PREFIX_EXTENDED) {
            is_extended = true;
            अनुवर्त;
        }

        ध्रुव पूर्णाङ्क scancode = (पूर्णाङ्क)(event & SCANCODE_MASK);
        ध्रुव bool pressed = ((event & SCANCODE_RELEASE) == 0);

        SDL_Scancode sc = SDL_SCANCODE_UNKNOWN;

        जइ (is_extended) {
            is_extended = false;
            जइ (scancode < SDL_arraysize(DOSVESA_ExtendedScancodeMapping)) {
                sc = DOSVESA_ExtendedScancodeMapping[scancode];
            }
        } अण्णहा {
            जइ (scancode < SDL_arraysize(DOSVESA_ScancodeMapping)) {
                sc = DOSVESA_ScancodeMapping[scancode];
            }
        }

        जइ (sc != SDL_SCANCODE_UNKNOWN) {
            SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, 0, sc, pressed);

            // Generate text input events for key-down on printable characters.
            // SDL keycodes below SDLK_SCANCODE_MASK are Unicode codepoints.
            जइ (pressed) {
                SDL_Keymod mod = SDL_GetModState();
                जइ (!(mod & (SDL_KMOD_CTRL | SDL_KMOD_ALT))) {
                    SDL_Keycode keycode = SDL_Get_कुञ्चिका_From_Scancode(sc, mod, false);
                    जइ (keycode > 0 && keycode < SDLK_SCANCODE_MASK && !SDL_iscntrl((पूर्णाङ्क)keycode)) {
                        वर्ण text[5];
                        वर्ण *end = SDL_UCS4ToUTF8((Uint32)keycode, text);
                        *end = '\0';
                        SDL_SendKeyboardText(text);
                    }
                }
            }
        }
    }

    // We chain IRQ1 to BIOS, so drain its keyboard queue continuously to prevent
    // BIOS buffer overflow beeps during long key autorepeat.
    DOSVESA_DrainBIOSKeyboardBuffer();

    SDL_Mouse *mouse = SDL_GetMouse();
    जइ (mouse->internal) { // if non-NULL, there's a mouse detected on the system.
        __dpmi_regs regs;

        regs.x.ax = 0x3; // read mouse buttons and position.
        __dpmi_int(0x33, &regs);
        ध्रुव Uint16 buttons = (पूर्णाङ्क)(Sint16)regs.x.bx;

        SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, SDL_BUTTON_वामः, (buttons & (1 << 0)) != 0);
        SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, SDL_BUTTON_दक्षिणः, (buttons & (1 << 1)) != 0);
        SDL_SendMouseButton(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, SDL_BUTTON_मध्यः, (buttons & (1 << 2)) != 0);

        जइ (!mouse->relative_mode) {
            ध्रुव पूर्णाङ्क x = (पूर्णाङ्क)(Sint16)regs.x.cx; // part of function 0x3's return value.
            ध्रुव पूर्णाङ्क y = (पूर्णाङ्क)(Sint16)regs.x.dx;
            SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, false, x, y);
        } अण्णहा {
            regs.x.ax = 0xB; // read motion counters
            __dpmi_int(0x33, &regs);
            // values returned here are -32768 to 32767
            ध्रुव SDL_VideoData *viddata = device->internal;
            ध्रुव भिन्न MICKEYS_PER_HPIXEL = viddata->mickeys_per_hpixel;
            ध्रुव भिन्न MICKEYS_PER_VPIXEL = viddata->mickeys_per_vpixel;
            ध्रुव पूर्णाङ्क mickeys_x = (पूर्णाङ्क)(Sint16)regs.x.cx;
            ध्रुव पूर्णाङ्क mickeys_y = (पूर्णाङ्क)(Sint16)regs.x.dx;
            SDL_SendMouseMotion(0, mouse->focus, SDL_DEFAULT_MOUSE_ID, true, mickeys_x / MICKEYS_PER_HPIXEL, mickeys_y / MICKEYS_PER_VPIXEL);
        }
    }
}

स्थिर शून्य KeyboardIRQHandler(शून्य) // this is wrapped in a thing that handles IRET, etc.
{
    keyevents_ringbuffer[keyevents_head] = inportb(KBD_DATA_PORT);
    keyevents_head = (keyevents_head + 1) & (SDL_arraysize(keyevents_ringbuffer) - 1);
    DOS_EndOfInterrupt(1);
}
स्थिर शून्य KeyboardIRQHandler_End(शून्य) {} // end-of-ISR label for memory locking

शून्य DOSVESA_InitKeyboard(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;

    // Lock ISR code and data to prevent page faults during interrupts
    DOS_LockCode(KeyboardIRQHandler, KeyboardIRQHandler_End);
    DOS_LockVariable(keyevents_ringbuffer);
    DOS_LockVariable(keyevents_head);
    DOS_LockVariable(keyevents_tail);

    DOS_HookInterrupt(1, KeyboardIRQHandler, &data->keyboard_interrupt_hook);
}

शून्य DOSVESA_QuitKeyboard(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;
    DOS_UnhookInterrupt(&data->keyboard_interrupt_hook, false);

    // Drain the BIOS keyboard buffer so held keys (like ESC) don't
    // bleed through to the DOS command line after we exit.
    DOSVESA_DrainBIOSKeyboardBuffer();
}

#endif // SDL_VIDEO_DRIVER_DOSVESA
