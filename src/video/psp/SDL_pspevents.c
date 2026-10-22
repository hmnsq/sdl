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

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspevents_c.h"
#ضمن "../../thread/SDL_systhread.h"
#ضمن <psphprm.h>
#ضمن <pspthreadman.h>

#ifdef PSPIRKEYB
#ضمن <pspirkeyb.h>
#ضمن <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE عدم // this will take ms0:/seplugins/pspirkeyb.ini

ساكن صحيح irkbd_ready = 0;
ساكن SDL_Scancode keymap[256];
#endif

ساكن تعداد Psp_Hprm_کونچي_سموا hprm = 0;
ساكن SDL_Semaphore *event_sem = عدم;
ساكن SDL_Thread *thread = عدم;
ساكن صحيح running = 0;
ساكن بنية
{
    تعداد Psp_Hprm_کونچي_سموا id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحيح EventUpdate(فراغ *data)
{
    طالما (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_کونچي((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    أرجع 0;
}

فراغ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحيح i;
    تعداد Psp_Hprm_کونچي_سموا کونچي_سموا;
    تعداد Psp_Hprm_کونچي_سموا changed;
    ساكن تعداد Psp_Hprm_کونچي_سموا old_کونچي_سموا = 0;

    SDL_WaitSemaphore(event_sem);
    کونچي_سموا = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_کونچي_سموا ^ کونچي_سموا;
    old_کونچي_سموا = کونچي_سموا;
    إذا (changed) {
        لكل (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            إذا (changed & keymap_psp[i].id) {
                bool down = ((کونچي_سموا & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_کونچي(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    إذا (irkbd_ready) {
        unsigned حرف buffer[255];
        صحيح i, length, کيراءن;
        SIrKeybScanCodeData *scanData;

        إذا (pspIrKeybReadinput(buffer, &length) >= 0) {
            إذا ((length % حجم(SIrKeybScanCodeData)) == 0) {
                کيراءن = length / حجم(SIrKeybScanCodeData);
                لكل (i = 0; i < کيراءن; i++) {
                    unsigned حرف raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_کونچي(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    أرجع;
}

فراغ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    صحيح i;
    لكل (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[کونچي_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[کونچي_F1] = SDL_SCANCODE_F1;
    keymap[کونچي_F2] = SDL_SCANCODE_F2;
    keymap[کونچي_F3] = SDL_SCANCODE_F3;
    keymap[کونچي_F4] = SDL_SCANCODE_F4;
    keymap[کونچي_F5] = SDL_SCANCODE_F5;
    keymap[کونچي_F6] = SDL_SCANCODE_F6;
    keymap[کونچي_F7] = SDL_SCANCODE_F7;
    keymap[کونچي_F8] = SDL_SCANCODE_F8;
    keymap[کونچي_F9] = SDL_SCANCODE_F9;
    keymap[کونچي_F10] = SDL_SCANCODE_F10;
    keymap[کونچي_F11] = SDL_SCANCODE_F11;
    keymap[کونچي_F12] = SDL_SCANCODE_F12;
    keymap[کونچي_F13] = SDL_SCANCODE_PRINT;
    keymap[کونچي_F14] = SDL_SCANCODE_PAUSE;

    keymap[کونچي_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[کونچي_1] = SDL_SCANCODE_1;
    keymap[کونچي_2_2] = SDL_SCANCODE_2;
    keymap[کونچي_3] = SDL_SCANCODE_3;
    keymap[کونچي_4] = SDL_SCANCODE_4;
    keymap[کونچي_5] = SDL_SCANCODE_5;
    keymap[کونچي_6] = SDL_SCANCODE_6;
    keymap[کونچي_7] = SDL_SCANCODE_7;
    keymap[کونچي_8] = SDL_SCANCODE_8;
    keymap[کونچي_9] = SDL_SCANCODE_9;
    keymap[کونچي_0] = SDL_SCANCODE_0;
    keymap[کونچي_MINUS] = SDL_SCANCODE_MINUS;
    keymap[کونچي_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[کونچي_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[کونچي_TAB] = SDL_SCANCODE_TAB;
    keymap[کونچي_Q] = SDL_SCANCODE_q;
    keymap[کونچي_W] = SDL_SCANCODE_w;
    keymap[کونچي_E] = SDL_SCANCODE_e;
    keymap[کونچي_R] = SDL_SCANCODE_r;
    keymap[کونچي_T] = SDL_SCANCODE_t;
    keymap[کونچي_Y] = SDL_SCANCODE_y;
    keymap[کونچي_U] = SDL_SCANCODE_u;
    keymap[کونچي_I] = SDL_SCANCODE_i;
    keymap[کونچي_O] = SDL_SCANCODE_o;
    keymap[کونچي_P] = SDL_SCANCODE_p;
    keymap[کونچي_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[کونچي_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[کونچي_ENTER] = SDL_SCANCODE_RETURN;

    keymap[کونچي_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[کونچي_A] = SDL_SCANCODE_a;
    keymap[کونچي_S] = SDL_SCANCODE_s;
    keymap[کونچي_D] = SDL_SCANCODE_d;
    keymap[کونچي_F] = SDL_SCANCODE_f;
    keymap[کونچي_G] = SDL_SCANCODE_g;
    keymap[کونچي_H] = SDL_SCANCODE_h;
    keymap[کونچي_J] = SDL_SCANCODE_j;
    keymap[کونچي_K] = SDL_SCANCODE_k;
    keymap[کونچي_L] = SDL_SCANCODE_l;
    keymap[کونچي_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[کونچي_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[کونچي_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[کونچي_Z] = SDL_SCANCODE_z;
    keymap[کونچي_X] = SDL_SCANCODE_x;
    keymap[کونچي_C] = SDL_SCANCODE_c;
    keymap[کونچي_V] = SDL_SCANCODE_v;
    keymap[کونچي_B] = SDL_SCANCODE_b;
    keymap[کونچي_N] = SDL_SCANCODE_n;
    keymap[کونچي_M] = SDL_SCANCODE_m;
    keymap[کونچي_COMMA] = SDL_SCANCODE_COMMA;
    keymap[کونچي_DOT] = SDL_SCANCODE_PERIOD;
    keymap[کونچي_SLASH] = SDL_SCANCODE_SLASH;

    keymap[کونچي_SPACE] = SDL_SCANCODE_SPACE;

    keymap[کونچي_UP] = SDL_SCANCODE_UP;
    keymap[کونچي_DOWN] = SDL_SCANCODE_DOWN;
    keymap[کونچي_کيري] = SDL_SCANCODE_کيري;
    keymap[کونچي_کانن] = SDL_SCANCODE_کانن;

    keymap[کونچي_HOME] = SDL_SCANCODE_HOME;
    keymap[کونچي_END] = SDL_SCANCODE_END;
    keymap[کونچي_سيسيڤ] = SDL_SCANCODE_سيسيڤ;
    keymap[کونچي_DELETE] = SDL_SCANCODE_DELETE;

    keymap[کونچي_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[کونچي_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[کونچي_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[کونچي_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[کونچي_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[کونچي_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[کونچي_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[کونچي_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[کونچي_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[کونچي_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[کونچي_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[کونچي_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[کونچي_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[کونچي_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    صحيح outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    صحيح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    إذا (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } وإلا {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    إذا ((event_sem = SDL_CreateSemaphore(1)) == عدم) {
        أرجع SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    إذا ((thread = SDL_Create_Thread_With_تيندنن_Size(EventUpdate, "PSPInputThread", 4096, عدم)) == عدم) {
        أرجع SDL_SetError("Can't create input thread");
    }
    أرجع true;
}

فراغ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, عدم);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    إذا (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
