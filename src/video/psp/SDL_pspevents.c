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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pspvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pspevents_c.h"
#ଅନ୍ତର୍ଭାଵ "../../thread/SDL_systhread.h"
#ଅନ୍ତର୍ଭାଵ <psphprm.h>
#ଅନ୍ତର୍ଭାଵ <pspthreadman.h>

#ifdef PSPIRKEYB
#ଅନ୍ତର୍ଭାଵ <pspirkeyb.h>
#ଅନ୍ତର୍ଭାଵ <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE ଖାଲି // this will take ms0:/seplugins/pspirkeyb.ini

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା irkbd_ready = 0;
ସ୍ଥିର SDL_Scancode keymap[256];
#endif

ସ୍ଥିର ଗଣନା Psp_Hprm_ଚାବିଗୁଡ଼ିକ hprm = 0;
ସ୍ଥିର SDL_Semaphore *event_sem = ଖାଲି;
ସ୍ଥିର SDL_Thread *thread = ଖାଲି;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା running = 0;
ସ୍ଥିର ସଂରଚନା
{
    ଗଣନା Psp_Hprm_ଚାବିଗୁଡ଼ିକ id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା EventUpdate(ଶୂନ୍ୟ *data)
{
    ଯେତେବେଳେ (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_ଚାବି((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଗଣନା Psp_Hprm_ଚାବିଗୁଡ଼ିକ ଚାବିଗୁଡ଼ିକ;
    ଗଣନା Psp_Hprm_ଚାବିଗୁଡ଼ିକ changed;
    ସ୍ଥିର ଗଣନା Psp_Hprm_ଚାବିଗୁଡ଼ିକ old_ଚାବିଗୁଡ଼ିକ = 0;

    SDL_WaitSemaphore(event_sem);
    ଚାବିଗୁଡ଼ିକ = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_ଚାବିଗୁଡ଼ିକ ^ ଚାବିଗୁଡ଼ିକ;
    old_ଚାବିଗୁଡ଼ିକ = ଚାବିଗୁଡ଼ିକ;
    ଯଦି (changed) {
        ପାଇଁ (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            ଯଦି (changed & keymap_psp[i].id) {
                bool down = ((ଚାବିଗୁଡ଼ିକ & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_ଚାବି(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    ଯଦି (irkbd_ready) {
        unsigned ଅକ୍ଷର buffer[255];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, length, ଗଣନା_2;
        SIrKeybScanCodeData *scanData;

        ଯଦି (pspIrKeybReadinput(buffer, &length) >= 0) {
            ଯଦି ((length % ଆକାର(SIrKeybScanCodeData)) == 0) {
                ଗଣନା_2 = length / ଆକାର(SIrKeybScanCodeData);
                ପାଇଁ (i = 0; i < ଗଣନା_2; i++) {
                    unsigned ଅକ୍ଷର raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_ଚାବି(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    ଫେରନ୍ତୁ;
}

ଶୂନ୍ୟ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[ଚାବି_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[ଚାବି_F1] = SDL_SCANCODE_F1;
    keymap[ଚାବି_F2] = SDL_SCANCODE_F2;
    keymap[ଚାବି_F3] = SDL_SCANCODE_F3;
    keymap[ଚାବି_F4] = SDL_SCANCODE_F4;
    keymap[ଚାବି_F5] = SDL_SCANCODE_F5;
    keymap[ଚାବି_F6] = SDL_SCANCODE_F6;
    keymap[ଚାବି_F7] = SDL_SCANCODE_F7;
    keymap[ଚାବି_F8] = SDL_SCANCODE_F8;
    keymap[ଚାବି_F9] = SDL_SCANCODE_F9;
    keymap[ଚାବି_F10] = SDL_SCANCODE_F10;
    keymap[ଚାବି_F11] = SDL_SCANCODE_F11;
    keymap[ଚାବି_F12] = SDL_SCANCODE_F12;
    keymap[ଚାବି_F13] = SDL_SCANCODE_PRINT;
    keymap[ଚାବି_F14] = SDL_SCANCODE_PAUSE;

    keymap[ଚାବି_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[ଚାବି_1] = SDL_SCANCODE_1;
    keymap[ଚାବି_2_2] = SDL_SCANCODE_2;
    keymap[ଚାବି_3] = SDL_SCANCODE_3;
    keymap[ଚାବି_4] = SDL_SCANCODE_4;
    keymap[ଚାବି_5] = SDL_SCANCODE_5;
    keymap[ଚାବି_6] = SDL_SCANCODE_6;
    keymap[ଚାବି_7] = SDL_SCANCODE_7;
    keymap[ଚାବି_8] = SDL_SCANCODE_8;
    keymap[ଚାବି_9] = SDL_SCANCODE_9;
    keymap[ଚାବି_0] = SDL_SCANCODE_0;
    keymap[ଚାବି_MINUS] = SDL_SCANCODE_MINUS;
    keymap[ଚାବି_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[ଚାବି_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[ଚାବି_TAB] = SDL_SCANCODE_TAB;
    keymap[ଚାବି_Q] = SDL_SCANCODE_q;
    keymap[ଚାବି_W] = SDL_SCANCODE_w;
    keymap[ଚାବି_E] = SDL_SCANCODE_e;
    keymap[ଚାବି_R] = SDL_SCANCODE_r;
    keymap[ଚାବି_T] = SDL_SCANCODE_t;
    keymap[ଚାବି_Y] = SDL_SCANCODE_y;
    keymap[ଚାବି_U] = SDL_SCANCODE_u;
    keymap[ଚାବି_I] = SDL_SCANCODE_i;
    keymap[ଚାବି_O] = SDL_SCANCODE_o;
    keymap[ଚାବି_P] = SDL_SCANCODE_p;
    keymap[ଚାବି_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[ଚାବି_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[ଚାବି_ENTER] = SDL_SCANCODE_RETURN;

    keymap[ଚାବି_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[ଚାବି_A] = SDL_SCANCODE_a;
    keymap[ଚାବି_S] = SDL_SCANCODE_s;
    keymap[ଚାବି_D] = SDL_SCANCODE_d;
    keymap[ଚାବି_F] = SDL_SCANCODE_f;
    keymap[ଚାବି_G] = SDL_SCANCODE_g;
    keymap[ଚାବି_H] = SDL_SCANCODE_h;
    keymap[ଚାବି_J] = SDL_SCANCODE_j;
    keymap[ଚାବି_K] = SDL_SCANCODE_k;
    keymap[ଚାବି_L] = SDL_SCANCODE_l;
    keymap[ଚାବି_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[ଚାବି_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[ଚାବି_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[ଚାବି_Z] = SDL_SCANCODE_z;
    keymap[ଚାବି_X] = SDL_SCANCODE_x;
    keymap[ଚାବି_C] = SDL_SCANCODE_c;
    keymap[ଚାବି_V] = SDL_SCANCODE_v;
    keymap[ଚାବି_B] = SDL_SCANCODE_b;
    keymap[ଚାବି_N] = SDL_SCANCODE_n;
    keymap[ଚାବି_M] = SDL_SCANCODE_m;
    keymap[ଚାବି_COMMA] = SDL_SCANCODE_COMMA;
    keymap[ଚାବି_DOT] = SDL_SCANCODE_PERIOD;
    keymap[ଚାବି_SLASH] = SDL_SCANCODE_SLASH;

    keymap[ଚାବି_SPACE] = SDL_SCANCODE_SPACE;

    keymap[ଚାବି_UP] = SDL_SCANCODE_UP;
    keymap[ଚାବି_DOWN] = SDL_SCANCODE_DOWN;
    keymap[ଚାବି_ବାମ] = SDL_SCANCODE_ବାମ;
    keymap[ଚାବି_ଡାହାଣ] = SDL_SCANCODE_ଡାହାଣ;

    keymap[ଚାବି_HOME] = SDL_SCANCODE_HOME;
    keymap[ଚାବି_END] = SDL_SCANCODE_END;
    keymap[ଚାବି_ଭର୍ତ୍ତି] = SDL_SCANCODE_ଭର୍ତ୍ତି;
    keymap[ଚାବି_DELETE] = SDL_SCANCODE_DELETE;

    keymap[ଚାବି_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[ଚାବି_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[ଚାବି_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[ଚାବି_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[ଚାବି_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[ଚାବି_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[ଚାବି_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[ଚାବି_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[ଚାବି_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[ଚାବି_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[ଚାବି_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[ଚାବି_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[ଚାବି_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[ଚାବି_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    ଯଦି (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } ଅନ୍ୟଥା {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    ଯଦି ((event_sem = SDL_CreateSemaphore(1)) == ଖାଲି) {
        ଫେରନ୍ତୁ SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    ଯଦି ((thread = SDL_Create_Thread_With_ଗଦା_Size(EventUpdate, "PSPInputThread", 4096, ଖାଲି)) == ଖାଲି) {
        ଫେରନ୍ତୁ SDL_SetError("Can't create input thread");
    }
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, ଖାଲି);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    ଯଦି (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
