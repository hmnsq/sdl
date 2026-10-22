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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_pspvideo.h"
#అన్తర్భావ "SDL_pspevents_c.h"
#అన్తర్భావ "../../thread/SDL_systhread.h"
#అన్తర్భావ <psphprm.h>
#అన్తర్భావ <pspthreadman.h>

#నిర్వచితమైతే PSPIRKEYB
#అన్తర్భావ <pspirkeyb.h>
#అన్తర్భావ <pspirkeyb_rawkeys.h>

#నిర్వచించు IRKBD_CONFIG_FILE ఖాళీ // this will take ms0:/seplugins/pspirkeyb.ini

స్థిర పూర్ణాంకం irkbd_ready = 0;
స్థిర SDL_Scancode keymap[256];
#అయితే_ముగింపు

స్థిర గణన Psp_Hprm_కీలకాలు hprm = 0;
స్థిర SDL_Semaphore *event_sem = ఖాళీ;
స్థిర SDL_Thread *thread = ఖాళీ;
స్థిర పూర్ణాంకం running = 0;
స్థిర నిర్మాణం
{
    గణన Psp_Hprm_కీలకాలు id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_వెనుక, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_పైకి, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_కిందికి, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

పూర్ణాంకం EventUpdate(శూన్య *దత్తాంశం)
{
    అయితే (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_కీలకం((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    తిరిగి 0;
}

శూన్య PSP_PumpEvents(SDL_VideoDevice *_this)
{
    పూర్ణాంకం i;
    గణన Psp_Hprm_కీలకాలు కీలకాలు;
    గణన Psp_Hprm_కీలకాలు మారింది;
    స్థిర గణన Psp_Hprm_కీలకాలు old_కీలకాలు = 0;

    SDL_WaitSemaphore(event_sem);
    కీలకాలు = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    మారింది = old_కీలకాలు ^ కీలకాలు;
    old_కీలకాలు = కీలకాలు;
    ఒకవేళ (మారింది) {
        కొరకు (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            ఒకవేళ (మారింది & keymap_psp[i].id) {
                bool కిందికి = ((కీలకాలు & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, కిందికి);
            }
        }
    }

#నిర్వచితమైతే PSPIRKEYB
    ఒకవేళ (irkbd_ready) {
        గుర్తులేని అక్షరం బఫరు_2[255];
        పూర్ణాంకం i, నిడివి, లెక్క;
        SIr_Keyb_పరిశీలన_సంకేతం_దత్తాంశం *పరిశీలన_దత్తాంశం;

        ఒకవేళ (pspIrKeybReadinput(బఫరు_2, &నిడివి) >= 0) {
            ఒకవేళ ((నిడివి % పరిమాణం(SIr_Keyb_పరిశీలన_సంకేతం_దత్తాంశం)) == 0) {
                లెక్క = నిడివి / పరిమాణం(SIr_Keyb_పరిశీలన_సంకేతం_దత్తాంశం);
                కొరకు (i = 0; i < లెక్క; i++) {
                    గుర్తులేని అక్షరం raw;
                    bool కిందికి;
                    పరిశీలన_దత్తాంశం = (SIr_Keyb_పరిశీలన_సంకేతం_దత్తాంశం *)బఫరు_2 + i;
                    raw = పరిశీలన_దత్తాంశం->raw;
                    కిందికి = (పరిశీలన_దత్తాంశం->pressed != 0);
                    SDL_Send_Keyboard_కీలకం(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], కిందికి);
                }
            }
        }
    }
#అయితే_ముగింపు
    sceKernelDelayThread(0);

    తిరిగి;
}

శూన్య PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే PSPIRKEYB
    పూర్ణాంకం i;
    కొరకు (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[కీలకం_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[కీలకం_F1] = SDL_SCANCODE_F1;
    keymap[కీలకం_F2] = SDL_SCANCODE_F2;
    keymap[కీలకం_F3] = SDL_SCANCODE_F3;
    keymap[కీలకం_F4] = SDL_SCANCODE_F4;
    keymap[కీలకం_F5] = SDL_SCANCODE_F5;
    keymap[కీలకం_F6] = SDL_SCANCODE_F6;
    keymap[కీలకం_F7] = SDL_SCANCODE_F7;
    keymap[కీలకం_F8] = SDL_SCANCODE_F8;
    keymap[కీలకం_F9] = SDL_SCANCODE_F9;
    keymap[కీలకం_F10] = SDL_SCANCODE_F10;
    keymap[కీలకం_F11] = SDL_SCANCODE_F11;
    keymap[కీలకం_F12] = SDL_SCANCODE_F12;
    keymap[కీలకం_F13] = SDL_SCANCODE_PRINT;
    keymap[కీలకం_F14] = SDL_SCANCODE_PAUSE;

    keymap[కీలకం_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[కీలకం_1] = SDL_SCANCODE_1;
    keymap[కీలకం_2_2] = SDL_SCANCODE_2;
    keymap[కీలకం_3] = SDL_SCANCODE_3;
    keymap[కీలకం_4] = SDL_SCANCODE_4;
    keymap[కీలకం_5] = SDL_SCANCODE_5;
    keymap[కీలకం_6] = SDL_SCANCODE_6;
    keymap[కీలకం_7] = SDL_SCANCODE_7;
    keymap[కీలకం_8] = SDL_SCANCODE_8;
    keymap[కీలకం_9] = SDL_SCANCODE_9;
    keymap[కీలకం_0] = SDL_SCANCODE_0;
    keymap[కీలకం_MINUS] = SDL_SCANCODE_MINUS;
    keymap[కీలకం_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[కీలకం_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[కీలకం_TAB] = SDL_SCANCODE_TAB;
    keymap[కీలకం_Q] = SDL_SCANCODE_q;
    keymap[కీలకం_W] = SDL_SCANCODE_w;
    keymap[కీలకం_E] = SDL_SCANCODE_e;
    keymap[కీలకం_R] = SDL_SCANCODE_r;
    keymap[కీలకం_T] = SDL_SCANCODE_t;
    keymap[కీలకం_Y] = SDL_SCANCODE_y;
    keymap[కీలకం_U] = SDL_SCANCODE_u;
    keymap[కీలకం_I] = SDL_SCANCODE_i;
    keymap[కీలకం_O] = SDL_SCANCODE_o;
    keymap[కీలకం_P] = SDL_SCANCODE_p;
    keymap[కీలకం_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[కీలకం_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[కీలకం_ENTER] = SDL_SCANCODE_RETURN;

    keymap[కీలకం_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[కీలకం_A] = SDL_SCANCODE_a;
    keymap[కీలకం_S] = SDL_SCANCODE_s;
    keymap[కీలకం_D] = SDL_SCANCODE_d;
    keymap[కీలకం_F] = SDL_SCANCODE_f;
    keymap[కీలకం_G] = SDL_SCANCODE_g;
    keymap[కీలకం_H] = SDL_SCANCODE_h;
    keymap[కీలకం_J] = SDL_SCANCODE_j;
    keymap[కీలకం_K] = SDL_SCANCODE_k;
    keymap[కీలకం_L] = SDL_SCANCODE_l;
    keymap[కీలకం_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[కీలకం_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[కీలకం_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[కీలకం_Z] = SDL_SCANCODE_z;
    keymap[కీలకం_X] = SDL_SCANCODE_x;
    keymap[కీలకం_C] = SDL_SCANCODE_c;
    keymap[కీలకం_V] = SDL_SCANCODE_v;
    keymap[కీలకం_B] = SDL_SCANCODE_b;
    keymap[కీలకం_N] = SDL_SCANCODE_n;
    keymap[కీలకం_M] = SDL_SCANCODE_m;
    keymap[కీలకం_COMMA] = SDL_SCANCODE_COMMA;
    keymap[కీలకం_DOT] = SDL_SCANCODE_PERIOD;
    keymap[కీలకం_SLASH] = SDL_SCANCODE_SLASH;

    keymap[కీలకం_SPACE] = SDL_SCANCODE_SPACE;

    keymap[కీలకం_పైకి] = SDL_SCANCODE_పైకి;
    keymap[కీలకం_కిందికి] = SDL_SCANCODE_కిందికి;
    keymap[కీలకం_ఎడమ] = SDL_SCANCODE_ఎడమ;
    keymap[కీలకం_కుడి] = SDL_SCANCODE_కుడి;

    keymap[కీలకం_HOME] = SDL_SCANCODE_HOME;
    keymap[కీలకం_చివర] = SDL_SCANCODE_చివర;
    keymap[కీలకం_చొప్పించు] = SDL_SCANCODE_చొప్పించు;
    keymap[కీలకం_DELETE] = SDL_SCANCODE_DELETE;

    keymap[కీలకం_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[కీలకం_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[కీలకం_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[కీలకం_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[కీలకం_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[కీలకం_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[కీలకం_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[కీలకం_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[కీలకం_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[కీలకం_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[కీలకం_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[కీలకం_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[కీలకం_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[కీలకం_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#అయితే_ముగింపు
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే PSPIRKEYB
    పూర్ణాంకం outputmode = PSP_IRKBD_OUTPUT_బహుళకం_SCANCODE;
    పూర్ణాంకం ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    ఒకవేళ (ret == PSP_IRKBD_ఫలితం_OK) {
        psp_Ir_Keyb_Output_బహుళకం(outputmode);
        irkbd_ready = 1;
    } లేకపోతే {
        irkbd_ready = 0;
    }
#అయితే_ముగింపు
    // Start thread to read data
    ఒకవేళ ((event_sem = SDL_CreateSemaphore(1)) == ఖాళీ) {
        తిరిగి SDL_సమితి_Error("Can't create input semaphore");
    }
    running = 1;
    ఒకవేళ ((thread = SDL_Create_Thread_With_దొంతర_కొలత(EventUpdate, "PSPInputThread", 4096, ఖాళీ)) == ఖాళీ) {
        తిరిగి SDL_సమితి_Error("Can't create input thread");
    }
    తిరిగి true;
}

శూన్య PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, ఖాళీ);
    SDL_DestroySemaphore(event_sem);
#నిర్వచితమైతే PSPIRKEYB
    ఒకవేళ (irkbd_ready) {
        psp_Ir_Keyb_ముగింపు();
        irkbd_ready = 0;
    }
#అయితే_ముగింపు
}

// end of SDL_pspevents.c ...

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_PSP
