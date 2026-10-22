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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "SDL_pspvideo.h"
#অন্তর্ভাব "SDL_pspevents_c.h"
#অন্তর্ভাব "../../thread/SDL_systhread.h"
#অন্তর্ভাব <psphprm.h>
#অন্তর্ভাব <pspthreadman.h>

#ifdef PSPIRKEYB
#অন্তর্ভাব <pspirkeyb.h>
#অন্তর্ভাব <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE রিক্ত // this will take ms0:/seplugins/pspirkeyb.ini

স্থির পূর্ণাঙ্ক irkbd_ready = 0;
স্থির SDL_Scancode keymap[256];
#endif

স্থির গণনা Psp_Hprm_চাবিগুলি hprm = 0;
স্থির SDL_Semaphore *event_sem = রিক্ত;
স্থির SDL_Thread *thread = রিক্ত;
স্থির পূর্ণাঙ্ক running = 0;
স্থির সংরচনা
{
    গণনা Psp_Hprm_চাবিগুলি id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

পূর্ণাঙ্ক EventUpdate(শূন্য *data)
{
    যাবত্ (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_চাবি((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    প্রত্যাগম 0;
}

শূন্য PSP_PumpEvents(SDL_VideoDevice *_this)
{
    পূর্ণাঙ্ক i;
    গণনা Psp_Hprm_চাবিগুলি চাবিগুলি;
    গণনা Psp_Hprm_চাবিগুলি changed;
    স্থির গণনা Psp_Hprm_চাবিগুলি old_চাবিগুলি = 0;

    SDL_WaitSemaphore(event_sem);
    চাবিগুলি = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_চাবিগুলি ^ চাবিগুলি;
    old_চাবিগুলি = চাবিগুলি;
    যদি (changed) {
        প্রতি (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            যদি (changed & keymap_psp[i].id) {
                bool down = ((চাবিগুলি & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    যদি (irkbd_ready) {
        unsigned বর্ণ buffer[255];
        পূর্ণাঙ্ক i, length, গুনতি;
        SIrKeybScanCodeData *scanData;

        যদি (pspIrKeybReadinput(buffer, &length) >= 0) {
            যদি ((length % পরিমাণ(SIrKeybScanCodeData)) == 0) {
                গুনতি = length / পরিমাণ(SIrKeybScanCodeData);
                প্রতি (i = 0; i < গুনতি; i++) {
                    unsigned বর্ণ raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_চাবি(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    প্রত্যাগম;
}

শূন্য PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    পূর্ণাঙ্ক i;
    প্রতি (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[চাবি_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[চাবি_F1] = SDL_SCANCODE_F1;
    keymap[চাবি_F2] = SDL_SCANCODE_F2;
    keymap[চাবি_F3] = SDL_SCANCODE_F3;
    keymap[চাবি_F4] = SDL_SCANCODE_F4;
    keymap[চাবি_F5] = SDL_SCANCODE_F5;
    keymap[চাবি_F6] = SDL_SCANCODE_F6;
    keymap[চাবি_F7] = SDL_SCANCODE_F7;
    keymap[চাবি_F8] = SDL_SCANCODE_F8;
    keymap[চাবি_F9] = SDL_SCANCODE_F9;
    keymap[চাবি_F10] = SDL_SCANCODE_F10;
    keymap[চাবি_F11] = SDL_SCANCODE_F11;
    keymap[চাবি_F12] = SDL_SCANCODE_F12;
    keymap[চাবি_F13] = SDL_SCANCODE_PRINT;
    keymap[চাবি_F14] = SDL_SCANCODE_PAUSE;

    keymap[চাবি_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[চাবি_1] = SDL_SCANCODE_1;
    keymap[চাবি_2_2] = SDL_SCANCODE_2;
    keymap[চাবি_3] = SDL_SCANCODE_3;
    keymap[চাবি_4] = SDL_SCANCODE_4;
    keymap[চাবি_5] = SDL_SCANCODE_5;
    keymap[চাবি_6] = SDL_SCANCODE_6;
    keymap[চাবি_7] = SDL_SCANCODE_7;
    keymap[চাবি_8] = SDL_SCANCODE_8;
    keymap[চাবি_9] = SDL_SCANCODE_9;
    keymap[চাবি_0] = SDL_SCANCODE_0;
    keymap[চাবি_MINUS] = SDL_SCANCODE_MINUS;
    keymap[চাবি_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[চাবি_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[চাবি_TAB] = SDL_SCANCODE_TAB;
    keymap[চাবি_Q] = SDL_SCANCODE_q;
    keymap[চাবি_W] = SDL_SCANCODE_w;
    keymap[চাবি_E] = SDL_SCANCODE_e;
    keymap[চাবি_R] = SDL_SCANCODE_r;
    keymap[চাবি_T] = SDL_SCANCODE_t;
    keymap[চাবি_Y] = SDL_SCANCODE_y;
    keymap[চাবি_U] = SDL_SCANCODE_u;
    keymap[চাবি_I] = SDL_SCANCODE_i;
    keymap[চাবি_O] = SDL_SCANCODE_o;
    keymap[চাবি_P] = SDL_SCANCODE_p;
    keymap[চাবি_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[চাবি_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[চাবি_ENTER] = SDL_SCANCODE_RETURN;

    keymap[চাবি_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[চাবি_A] = SDL_SCANCODE_a;
    keymap[চাবি_S] = SDL_SCANCODE_s;
    keymap[চাবি_D] = SDL_SCANCODE_d;
    keymap[চাবি_F] = SDL_SCANCODE_f;
    keymap[চাবি_G] = SDL_SCANCODE_g;
    keymap[চাবি_H] = SDL_SCANCODE_h;
    keymap[চাবি_J] = SDL_SCANCODE_j;
    keymap[চাবি_K] = SDL_SCANCODE_k;
    keymap[চাবি_L] = SDL_SCANCODE_l;
    keymap[চাবি_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[চাবি_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[চাবি_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[চাবি_Z] = SDL_SCANCODE_z;
    keymap[চাবি_X] = SDL_SCANCODE_x;
    keymap[চাবি_C] = SDL_SCANCODE_c;
    keymap[চাবি_V] = SDL_SCANCODE_v;
    keymap[চাবি_B] = SDL_SCANCODE_b;
    keymap[চাবি_N] = SDL_SCANCODE_n;
    keymap[চাবি_M] = SDL_SCANCODE_m;
    keymap[চাবি_COMMA] = SDL_SCANCODE_COMMA;
    keymap[চাবি_DOT] = SDL_SCANCODE_PERIOD;
    keymap[চাবি_SLASH] = SDL_SCANCODE_SLASH;

    keymap[চাবি_SPACE] = SDL_SCANCODE_SPACE;

    keymap[চাবি_UP] = SDL_SCANCODE_UP;
    keymap[চাবি_DOWN] = SDL_SCANCODE_DOWN;
    keymap[চাবি_বাম] = SDL_SCANCODE_বাম;
    keymap[চাবি_ডান] = SDL_SCANCODE_ডান;

    keymap[চাবি_HOME] = SDL_SCANCODE_HOME;
    keymap[চাবি_END] = SDL_SCANCODE_END;
    keymap[চাবি_ঢোকাও] = SDL_SCANCODE_ঢোকাও;
    keymap[চাবি_DELETE] = SDL_SCANCODE_DELETE;

    keymap[চাবি_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[চাবি_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[চাবি_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[চাবি_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[চাবি_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[চাবি_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[চাবি_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[চাবি_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[চাবি_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[চাবি_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[চাবি_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[চাবি_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[চাবি_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[চাবি_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    পূর্ণাঙ্ক outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    পূর্ণাঙ্ক ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    যদি (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } অন্যথা {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    যদি ((event_sem = SDL_CreateSemaphore(1)) == রিক্ত) {
        প্রত্যাগম SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    যদি ((thread = SDL_Create_Thread_With_স্তূপ_Size(EventUpdate, "PSPInputThread", 4096, রিক্ত)) == রিক্ত) {
        প্রত্যাগম SDL_SetError("Can't create input thread");
    }
    প্রত্যাগম true;
}

শূন্য PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, রিক্ত);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    যদি (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
