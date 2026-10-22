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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_pspvideo.h"
#અન્તર્ભાવ "SDL_pspevents_c.h"
#અન્તર્ભાવ "../../thread/SDL_systhread.h"
#અન્તર્ભાવ <psphprm.h>
#અન્તર્ભાવ <pspthreadman.h>

#ifdef PSPIRKEYB
#અન્તર્ભાવ <pspirkeyb.h>
#અન્તર્ભાવ <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE ખાલી // this will take ms0:/seplugins/pspirkeyb.ini

સ્થિર પૂર્ણાંક irkbd_ready = 0;
સ્થિર SDL_Scancode keymap[256];
#endif

સ્થિર ગણના Psp_Hprm_ચાવીઓ hprm = 0;
સ્થિર SDL_Semaphore *event_sem = ખાલી;
સ્થિર SDL_Thread *thread = ખાલી;
સ્થિર પૂર્ણાંક running = 0;
સ્થિર સંરચના
{
    ગણના Psp_Hprm_ચાવીઓ id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

પૂર્ણાંક EventUpdate(શૂન્ય *data)
{
    જ્યારે (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_ચાવી((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    પાછા 0;
}

શૂન્ય PSP_PumpEvents(SDL_VideoDevice *_this)
{
    પૂર્ણાંક i;
    ગણના Psp_Hprm_ચાવીઓ ચાવીઓ;
    ગણના Psp_Hprm_ચાવીઓ changed;
    સ્થિર ગણના Psp_Hprm_ચાવીઓ old_ચાવીઓ = 0;

    SDL_WaitSemaphore(event_sem);
    ચાવીઓ = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_ચાવીઓ ^ ચાવીઓ;
    old_ચાવીઓ = ચાવીઓ;
    જો (changed) {
        માટે (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            જો (changed & keymap_psp[i].id) {
                bool down = ((ચાવીઓ & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_ચાવી(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    જો (irkbd_ready) {
        unsigned અક્ષર buffer[255];
        પૂર્ણાંક i, length, ગણતરી;
        SIrKeybScanCodeData *scanData;

        જો (pspIrKeybReadinput(buffer, &length) >= 0) {
            જો ((length % કદ(SIrKeybScanCodeData)) == 0) {
                ગણતરી = length / કદ(SIrKeybScanCodeData);
                માટે (i = 0; i < ગણતરી; i++) {
                    unsigned અક્ષર raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_ચાવી(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    પાછા;
}

શૂન્ય PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    પૂર્ણાંક i;
    માટે (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[ચાવી_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[ચાવી_F1] = SDL_SCANCODE_F1;
    keymap[ચાવી_F2] = SDL_SCANCODE_F2;
    keymap[ચાવી_F3] = SDL_SCANCODE_F3;
    keymap[ચાવી_F4] = SDL_SCANCODE_F4;
    keymap[ચાવી_F5] = SDL_SCANCODE_F5;
    keymap[ચાવી_F6] = SDL_SCANCODE_F6;
    keymap[ચાવી_F7] = SDL_SCANCODE_F7;
    keymap[ચાવી_F8] = SDL_SCANCODE_F8;
    keymap[ચાવી_F9] = SDL_SCANCODE_F9;
    keymap[ચાવી_F10] = SDL_SCANCODE_F10;
    keymap[ચાવી_F11] = SDL_SCANCODE_F11;
    keymap[ચાવી_F12] = SDL_SCANCODE_F12;
    keymap[ચાવી_F13] = SDL_SCANCODE_PRINT;
    keymap[ચાવી_F14] = SDL_SCANCODE_PAUSE;

    keymap[ચાવી_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[ચાવી_1] = SDL_SCANCODE_1;
    keymap[ચાવી_2_2] = SDL_SCANCODE_2;
    keymap[ચાવી_3] = SDL_SCANCODE_3;
    keymap[ચાવી_4] = SDL_SCANCODE_4;
    keymap[ચાવી_5] = SDL_SCANCODE_5;
    keymap[ચાવી_6] = SDL_SCANCODE_6;
    keymap[ચાવી_7] = SDL_SCANCODE_7;
    keymap[ચાવી_8] = SDL_SCANCODE_8;
    keymap[ચાવી_9] = SDL_SCANCODE_9;
    keymap[ચાવી_0] = SDL_SCANCODE_0;
    keymap[ચાવી_MINUS] = SDL_SCANCODE_MINUS;
    keymap[ચાવી_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[ચાવી_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[ચાવી_TAB] = SDL_SCANCODE_TAB;
    keymap[ચાવી_Q] = SDL_SCANCODE_q;
    keymap[ચાવી_W] = SDL_SCANCODE_w;
    keymap[ચાવી_E] = SDL_SCANCODE_e;
    keymap[ચાવી_R] = SDL_SCANCODE_r;
    keymap[ચાવી_T] = SDL_SCANCODE_t;
    keymap[ચાવી_Y] = SDL_SCANCODE_y;
    keymap[ચાવી_U] = SDL_SCANCODE_u;
    keymap[ચાવી_I] = SDL_SCANCODE_i;
    keymap[ચાવી_O] = SDL_SCANCODE_o;
    keymap[ચાવી_P] = SDL_SCANCODE_p;
    keymap[ચાવી_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[ચાવી_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[ચાવી_ENTER] = SDL_SCANCODE_RETURN;

    keymap[ચાવી_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[ચાવી_A] = SDL_SCANCODE_a;
    keymap[ચાવી_S] = SDL_SCANCODE_s;
    keymap[ચાવી_D] = SDL_SCANCODE_d;
    keymap[ચાવી_F] = SDL_SCANCODE_f;
    keymap[ચાવી_G] = SDL_SCANCODE_g;
    keymap[ચાવી_H] = SDL_SCANCODE_h;
    keymap[ચાવી_J] = SDL_SCANCODE_j;
    keymap[ચાવી_K] = SDL_SCANCODE_k;
    keymap[ચાવી_L] = SDL_SCANCODE_l;
    keymap[ચાવી_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[ચાવી_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[ચાવી_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[ચાવી_Z] = SDL_SCANCODE_z;
    keymap[ચાવી_X] = SDL_SCANCODE_x;
    keymap[ચાવી_C] = SDL_SCANCODE_c;
    keymap[ચાવી_V] = SDL_SCANCODE_v;
    keymap[ચાવી_B] = SDL_SCANCODE_b;
    keymap[ચાવી_N] = SDL_SCANCODE_n;
    keymap[ચાવી_M] = SDL_SCANCODE_m;
    keymap[ચાવી_COMMA] = SDL_SCANCODE_COMMA;
    keymap[ચાવી_DOT] = SDL_SCANCODE_PERIOD;
    keymap[ચાવી_SLASH] = SDL_SCANCODE_SLASH;

    keymap[ચાવી_SPACE] = SDL_SCANCODE_SPACE;

    keymap[ચાવી_UP] = SDL_SCANCODE_UP;
    keymap[ચાવી_DOWN] = SDL_SCANCODE_DOWN;
    keymap[ચાવી_ડાબું] = SDL_SCANCODE_ડાબું;
    keymap[ચાવી_જમણું] = SDL_SCANCODE_જમણું;

    keymap[ચાવી_HOME] = SDL_SCANCODE_HOME;
    keymap[ચાવી_END] = SDL_SCANCODE_END;
    keymap[ચાવી_ઉમેરો] = SDL_SCANCODE_ઉમેરો;
    keymap[ચાવી_DELETE] = SDL_SCANCODE_DELETE;

    keymap[ચાવી_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[ચાવી_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[ચાવી_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[ચાવી_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[ચાવી_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[ચાવી_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[ચાવી_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[ચાવી_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[ચાવી_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[ચાવી_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[ચાવી_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[ચાવી_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[ચાવી_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[ચાવી_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    પૂર્ણાંક outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    પૂર્ણાંક ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    જો (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } નહીંતર {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    જો ((event_sem = SDL_CreateSemaphore(1)) == ખાલી) {
        પાછા SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    જો ((thread = SDL_Create_Thread_With_ઢગલો_Size(EventUpdate, "PSPInputThread", 4096, ખાલી)) == ખાલી) {
        પાછા SDL_SetError("Can't create input thread");
    }
    પાછા true;
}

શૂન્ય PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, ખાલી);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    જો (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
