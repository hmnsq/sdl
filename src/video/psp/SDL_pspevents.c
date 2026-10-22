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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_pspvideo.h"
#അന്തര്ഭാവ "SDL_pspevents_c.h"
#അന്തര്ഭാവ "../../thread/SDL_systhread.h"
#അന്തര്ഭാവ <psphprm.h>
#അന്തര്ഭാവ <pspthreadman.h>

#ifdef PSPIRKEYB
#അന്തര്ഭാവ <pspirkeyb.h>
#അന്തര്ഭാവ <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE ശൂന്യ // this will take ms0:/seplugins/pspirkeyb.ini

സ്ഥിതം പൂർണ്ണസംഖ്യ irkbd_ready = 0;
സ്ഥിതം SDL_Scancode keymap[256];
#endif

സ്ഥിതം എണ്ണൽ Psp_Hprm_താക്കോലുകൾ hprm = 0;
സ്ഥിതം SDL_Semaphore *event_sem = ശൂന്യ;
സ്ഥിതം SDL_Thread *thread = ശൂന്യ;
സ്ഥിതം പൂർണ്ണസംഖ്യ running = 0;
സ്ഥിതം ഘടന
{
    എണ്ണൽ Psp_Hprm_താക്കോലുകൾ id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

പൂർണ്ണസംഖ്യ EventUpdate(ശൂന്യം *data)
{
    ആകുമ്പോൾ (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_താക്കോൽ((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    തിരികെ 0;
}

ശൂന്യം PSP_PumpEvents(SDL_VideoDevice *_this)
{
    പൂർണ്ണസംഖ്യ i;
    എണ്ണൽ Psp_Hprm_താക്കോലുകൾ താക്കോലുകൾ;
    എണ്ണൽ Psp_Hprm_താക്കോലുകൾ changed;
    സ്ഥിതം എണ്ണൽ Psp_Hprm_താക്കോലുകൾ old_താക്കോലുകൾ = 0;

    SDL_WaitSemaphore(event_sem);
    താക്കോലുകൾ = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_താക്കോലുകൾ ^ താക്കോലുകൾ;
    old_താക്കോലുകൾ = താക്കോലുകൾ;
    എങ്കിൽ (changed) {
        വേണ്ടി (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            എങ്കിൽ (changed & keymap_psp[i].id) {
                bool down = ((താക്കോലുകൾ & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    എങ്കിൽ (irkbd_ready) {
        unsigned അക്ഷരം buffer[255];
        പൂർണ്ണസംഖ്യ i, length, എണ്ണം;
        SIrKeybScanCodeData *scanData;

        എങ്കിൽ (pspIrKeybReadinput(buffer, &length) >= 0) {
            എങ്കിൽ ((length % വലുപ്പം(SIrKeybScanCodeData)) == 0) {
                എണ്ണം = length / വലുപ്പം(SIrKeybScanCodeData);
                വേണ്ടി (i = 0; i < എണ്ണം; i++) {
                    unsigned അക്ഷരം raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_താക്കോൽ(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    തിരികെ;
}

ശൂന്യം PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[താക്കോൽ_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[താക്കോൽ_F1] = SDL_SCANCODE_F1;
    keymap[താക്കോൽ_F2] = SDL_SCANCODE_F2;
    keymap[താക്കോൽ_F3] = SDL_SCANCODE_F3;
    keymap[താക്കോൽ_F4] = SDL_SCANCODE_F4;
    keymap[താക്കോൽ_F5] = SDL_SCANCODE_F5;
    keymap[താക്കോൽ_F6] = SDL_SCANCODE_F6;
    keymap[താക്കോൽ_F7] = SDL_SCANCODE_F7;
    keymap[താക്കോൽ_F8] = SDL_SCANCODE_F8;
    keymap[താക്കോൽ_F9] = SDL_SCANCODE_F9;
    keymap[താക്കോൽ_F10] = SDL_SCANCODE_F10;
    keymap[താക്കോൽ_F11] = SDL_SCANCODE_F11;
    keymap[താക്കോൽ_F12] = SDL_SCANCODE_F12;
    keymap[താക്കോൽ_F13] = SDL_SCANCODE_PRINT;
    keymap[താക്കോൽ_F14] = SDL_SCANCODE_PAUSE;

    keymap[താക്കോൽ_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[താക്കോൽ_1] = SDL_SCANCODE_1;
    keymap[താക്കോൽ_2_2] = SDL_SCANCODE_2;
    keymap[താക്കോൽ_3] = SDL_SCANCODE_3;
    keymap[താക്കോൽ_4] = SDL_SCANCODE_4;
    keymap[താക്കോൽ_5] = SDL_SCANCODE_5;
    keymap[താക്കോൽ_6] = SDL_SCANCODE_6;
    keymap[താക്കോൽ_7] = SDL_SCANCODE_7;
    keymap[താക്കോൽ_8] = SDL_SCANCODE_8;
    keymap[താക്കോൽ_9] = SDL_SCANCODE_9;
    keymap[താക്കോൽ_0] = SDL_SCANCODE_0;
    keymap[താക്കോൽ_MINUS] = SDL_SCANCODE_MINUS;
    keymap[താക്കോൽ_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[താക്കോൽ_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[താക്കോൽ_TAB] = SDL_SCANCODE_TAB;
    keymap[താക്കോൽ_Q] = SDL_SCANCODE_q;
    keymap[താക്കോൽ_W] = SDL_SCANCODE_w;
    keymap[താക്കോൽ_E] = SDL_SCANCODE_e;
    keymap[താക്കോൽ_R] = SDL_SCANCODE_r;
    keymap[താക്കോൽ_T] = SDL_SCANCODE_t;
    keymap[താക്കോൽ_Y] = SDL_SCANCODE_y;
    keymap[താക്കോൽ_U] = SDL_SCANCODE_u;
    keymap[താക്കോൽ_I] = SDL_SCANCODE_i;
    keymap[താക്കോൽ_O] = SDL_SCANCODE_o;
    keymap[താക്കോൽ_P] = SDL_SCANCODE_p;
    keymap[താക്കോൽ_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[താക്കോൽ_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[താക്കോൽ_ENTER] = SDL_SCANCODE_RETURN;

    keymap[താക്കോൽ_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[താക്കോൽ_A] = SDL_SCANCODE_a;
    keymap[താക്കോൽ_S] = SDL_SCANCODE_s;
    keymap[താക്കോൽ_D] = SDL_SCANCODE_d;
    keymap[താക്കോൽ_F] = SDL_SCANCODE_f;
    keymap[താക്കോൽ_G] = SDL_SCANCODE_g;
    keymap[താക്കോൽ_H] = SDL_SCANCODE_h;
    keymap[താക്കോൽ_J] = SDL_SCANCODE_j;
    keymap[താക്കോൽ_K] = SDL_SCANCODE_k;
    keymap[താക്കോൽ_L] = SDL_SCANCODE_l;
    keymap[താക്കോൽ_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[താക്കോൽ_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[താക്കോൽ_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[താക്കോൽ_Z] = SDL_SCANCODE_z;
    keymap[താക്കോൽ_X] = SDL_SCANCODE_x;
    keymap[താക്കോൽ_C] = SDL_SCANCODE_c;
    keymap[താക്കോൽ_V] = SDL_SCANCODE_v;
    keymap[താക്കോൽ_B] = SDL_SCANCODE_b;
    keymap[താക്കോൽ_N] = SDL_SCANCODE_n;
    keymap[താക്കോൽ_M] = SDL_SCANCODE_m;
    keymap[താക്കോൽ_COMMA] = SDL_SCANCODE_COMMA;
    keymap[താക്കോൽ_DOT] = SDL_SCANCODE_PERIOD;
    keymap[താക്കോൽ_SLASH] = SDL_SCANCODE_SLASH;

    keymap[താക്കോൽ_SPACE] = SDL_SCANCODE_SPACE;

    keymap[താക്കോൽ_UP] = SDL_SCANCODE_UP;
    keymap[താക്കോൽ_DOWN] = SDL_SCANCODE_DOWN;
    keymap[താക്കോൽ_ഇടത്] = SDL_SCANCODE_ഇടത്;
    keymap[താക്കോൽ_വലത്] = SDL_SCANCODE_വലത്;

    keymap[താക്കോൽ_HOME] = SDL_SCANCODE_HOME;
    keymap[താക്കോൽ_END] = SDL_SCANCODE_END;
    keymap[താക്കോൽ_തിരുകുക] = SDL_SCANCODE_തിരുകുക;
    keymap[താക്കോൽ_DELETE] = SDL_SCANCODE_DELETE;

    keymap[താക്കോൽ_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[താക്കോൽ_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[താക്കോൽ_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[താക്കോൽ_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[താക്കോൽ_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[താക്കോൽ_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[താക്കോൽ_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[താക്കോൽ_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[താക്കോൽ_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[താക്കോൽ_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[താക്കോൽ_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[താക്കോൽ_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[താക്കോൽ_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[താക്കോൽ_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    പൂർണ്ണസംഖ്യ outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    പൂർണ്ണസംഖ്യ ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    എങ്കിൽ (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } അല്ലെങ്കിൽ {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    എങ്കിൽ ((event_sem = SDL_CreateSemaphore(1)) == ശൂന്യ) {
        തിരികെ SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    എങ്കിൽ ((thread = SDL_Create_Thread_With_അട്ടി_Size(EventUpdate, "PSPInputThread", 4096, ശൂന്യ)) == ശൂന്യ) {
        തിരികെ SDL_SetError("Can't create input thread");
    }
    തിരികെ true;
}

ശൂന്യം PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, ശൂന്യ);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    എങ്കിൽ (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
