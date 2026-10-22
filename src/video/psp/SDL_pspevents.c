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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "SDL_pspvideo.h"
#அந்தர்பாவ "SDL_pspevents_c.h"
#அந்தர்பாவ "../../thread/SDL_systhread.h"
#அந்தர்பாவ <psphprm.h>
#அந்தர்பாவ <pspthreadman.h>

#ifdef PSPIRKEYB
#அந்தர்பாவ <pspirkeyb.h>
#அந்தர்பாவ <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE வெற்று // this will take ms0:/seplugins/pspirkeyb.ini

நிலையான முழு irkbd_ready = 0;
நிலையான SDL_Scancode keymap[256];
#endif

நிலையான எண்ணிக்கை Psp_Hprm_சாவிகள் hprm = 0;
நிலையான SDL_Semaphore *event_sem = வெற்று;
நிலையான SDL_Thread *thread = வெற்று;
நிலையான முழு running = 0;
நிலையான கட்டமைப்பு
{
    எண்ணிக்கை Psp_Hprm_சாவிகள் id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

முழு EventUpdate(வெறுமை *data)
{
    போது (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_சாவி((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    திரும்பு 0;
}

வெறுமை PSP_PumpEvents(SDL_VideoDevice *_this)
{
    முழு i;
    எண்ணிக்கை Psp_Hprm_சாவிகள் சாவிகள்;
    எண்ணிக்கை Psp_Hprm_சாவிகள் changed;
    நிலையான எண்ணிக்கை Psp_Hprm_சாவிகள் old_சாவிகள் = 0;

    SDL_WaitSemaphore(event_sem);
    சாவிகள் = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_சாவிகள் ^ சாவிகள்;
    old_சாவிகள் = சாவிகள்;
    எனில் (changed) {
        க்கு (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            எனில் (changed & keymap_psp[i].id) {
                bool down = ((சாவிகள் & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    எனில் (irkbd_ready) {
        unsigned எழுத்து buffer[255];
        முழு i, length, மொத்தம்;
        SIrKeybScanCodeData *scanData;

        எனில் (pspIrKeybReadinput(buffer, &length) >= 0) {
            எனில் ((length % அளவு(SIrKeybScanCodeData)) == 0) {
                மொத்தம் = length / அளவு(SIrKeybScanCodeData);
                க்கு (i = 0; i < மொத்தம்; i++) {
                    unsigned எழுத்து raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_சாவி(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    திரும்பு;
}

வெறுமை PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    முழு i;
    க்கு (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[சாவி_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[சாவி_F1] = SDL_SCANCODE_F1;
    keymap[சாவி_F2] = SDL_SCANCODE_F2;
    keymap[சாவி_F3] = SDL_SCANCODE_F3;
    keymap[சாவி_F4] = SDL_SCANCODE_F4;
    keymap[சாவி_F5] = SDL_SCANCODE_F5;
    keymap[சாவி_F6] = SDL_SCANCODE_F6;
    keymap[சாவி_F7] = SDL_SCANCODE_F7;
    keymap[சாவி_F8] = SDL_SCANCODE_F8;
    keymap[சாவி_F9] = SDL_SCANCODE_F9;
    keymap[சாவி_F10] = SDL_SCANCODE_F10;
    keymap[சாவி_F11] = SDL_SCANCODE_F11;
    keymap[சாவி_F12] = SDL_SCANCODE_F12;
    keymap[சாவி_F13] = SDL_SCANCODE_PRINT;
    keymap[சாவி_F14] = SDL_SCANCODE_PAUSE;

    keymap[சாவி_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[சாவி_1] = SDL_SCANCODE_1;
    keymap[சாவி_2_2] = SDL_SCANCODE_2;
    keymap[சாவி_3] = SDL_SCANCODE_3;
    keymap[சாவி_4] = SDL_SCANCODE_4;
    keymap[சாவி_5] = SDL_SCANCODE_5;
    keymap[சாவி_6] = SDL_SCANCODE_6;
    keymap[சாவி_7] = SDL_SCANCODE_7;
    keymap[சாவி_8] = SDL_SCANCODE_8;
    keymap[சாவி_9] = SDL_SCANCODE_9;
    keymap[சாவி_0] = SDL_SCANCODE_0;
    keymap[சாவி_MINUS] = SDL_SCANCODE_MINUS;
    keymap[சாவி_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[சாவி_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[சாவி_TAB] = SDL_SCANCODE_TAB;
    keymap[சாவி_Q] = SDL_SCANCODE_q;
    keymap[சாவி_W] = SDL_SCANCODE_w;
    keymap[சாவி_E] = SDL_SCANCODE_e;
    keymap[சாவி_R] = SDL_SCANCODE_r;
    keymap[சாவி_T] = SDL_SCANCODE_t;
    keymap[சாவி_Y] = SDL_SCANCODE_y;
    keymap[சாவி_U] = SDL_SCANCODE_u;
    keymap[சாவி_I] = SDL_SCANCODE_i;
    keymap[சாவி_O] = SDL_SCANCODE_o;
    keymap[சாவி_P] = SDL_SCANCODE_p;
    keymap[சாவி_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[சாவி_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[சாவி_ENTER] = SDL_SCANCODE_RETURN;

    keymap[சாவி_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[சாவி_A] = SDL_SCANCODE_a;
    keymap[சாவி_S] = SDL_SCANCODE_s;
    keymap[சாவி_D] = SDL_SCANCODE_d;
    keymap[சாவி_F] = SDL_SCANCODE_f;
    keymap[சாவி_G] = SDL_SCANCODE_g;
    keymap[சாவி_H] = SDL_SCANCODE_h;
    keymap[சாவி_J] = SDL_SCANCODE_j;
    keymap[சாவி_K] = SDL_SCANCODE_k;
    keymap[சாவி_L] = SDL_SCANCODE_l;
    keymap[சாவி_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[சாவி_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[சாவி_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[சாவி_Z] = SDL_SCANCODE_z;
    keymap[சாவி_X] = SDL_SCANCODE_x;
    keymap[சாவி_C] = SDL_SCANCODE_c;
    keymap[சாவி_V] = SDL_SCANCODE_v;
    keymap[சாவி_B] = SDL_SCANCODE_b;
    keymap[சாவி_N] = SDL_SCANCODE_n;
    keymap[சாவி_M] = SDL_SCANCODE_m;
    keymap[சாவி_COMMA] = SDL_SCANCODE_COMMA;
    keymap[சாவி_DOT] = SDL_SCANCODE_PERIOD;
    keymap[சாவி_SLASH] = SDL_SCANCODE_SLASH;

    keymap[சாவி_SPACE] = SDL_SCANCODE_SPACE;

    keymap[சாவி_UP] = SDL_SCANCODE_UP;
    keymap[சாவி_DOWN] = SDL_SCANCODE_DOWN;
    keymap[சாவி_இடது] = SDL_SCANCODE_இடது;
    keymap[சாவி_வலது] = SDL_SCANCODE_வலது;

    keymap[சாவி_HOME] = SDL_SCANCODE_HOME;
    keymap[சாவி_END] = SDL_SCANCODE_END;
    keymap[சாவி_செருகு] = SDL_SCANCODE_செருகு;
    keymap[சாவி_DELETE] = SDL_SCANCODE_DELETE;

    keymap[சாவி_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[சாவி_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[சாவி_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[சாவி_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[சாவி_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[சாவி_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[சாவி_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[சாவி_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[சாவி_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[சாவி_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[சாவி_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[சாவி_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[சாவி_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[சாவி_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    முழு outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    முழு ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    எனில் (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } இல்லையெனில் {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    எனில் ((event_sem = SDL_CreateSemaphore(1)) == வெற்று) {
        திரும்பு SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    எனில் ((thread = SDL_Create_Thread_With_அடுக்கு_Size(EventUpdate, "PSPInputThread", 4096, வெற்று)) == வெற்று) {
        திரும்பு SDL_SetError("Can't create input thread");
    }
    திரும்பு true;
}

வெறுமை PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, வெற்று);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    எனில் (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
