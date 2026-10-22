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

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_pspvideo.h"
#अन्तर्भाव "SDL_pspevents_c.h"
#अन्तर्भाव "../../thread/SDL_systhread.h"
#अन्तर्भाव <psphprm.h>
#अन्तर्भाव <pspthreadman.h>

#ifdef PSPIRKEYB
#अन्तर्भाव <pspirkeyb.h>
#अन्तर्भाव <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE रिक्त // this will take ms0:/seplugins/pspirkeyb.ini

स्थिर पूर्णांक irkbd_ready = 0;
स्थिर SDL_Scancode keymap[256];
#endif

स्थिर गणना Psp_Hprm_किल्ल्या hprm = 0;
स्थिर SDL_Semaphore *event_sem = रिक्त;
स्थिर SDL_Thread *thread = रिक्त;
स्थिर पूर्णांक running = 0;
स्थिर संरचना
{
    गणना Psp_Hprm_किल्ल्या id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

पूर्णांक EventUpdate(शून्य *data)
{
    पर्यंत (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_किल्ली((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    परत 0;
}

शून्य PSP_PumpEvents(SDL_VideoDevice *_this)
{
    पूर्णांक i;
    गणना Psp_Hprm_किल्ल्या किल्ल्या;
    गणना Psp_Hprm_किल्ल्या changed;
    स्थिर गणना Psp_Hprm_किल्ल्या old_किल्ल्या = 0;

    SDL_WaitSemaphore(event_sem);
    किल्ल्या = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_किल्ल्या ^ किल्ल्या;
    old_किल्ल्या = किल्ल्या;
    जर (changed) {
        साठी (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            जर (changed & keymap_psp[i].id) {
                bool down = ((किल्ल्या & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    जर (irkbd_ready) {
        अचिन्हित अक्षर buffer[255];
        पूर्णांक i, length, मोजणी;
        SIrKeybScanCodeData *scanData;

        जर (pspIrKeybReadinput(buffer, &length) >= 0) {
            जर ((length % आकार(SIrKeybScanCodeData)) == 0) {
                मोजणी = length / आकार(SIrKeybScanCodeData);
                साठी (i = 0; i < मोजणी; i++) {
                    अचिन्हित अक्षर raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_किल्ली(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    परत;
}

शून्य PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णांक i;
    साठी (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[किल्ली_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[किल्ली_F1] = SDL_SCANCODE_F1;
    keymap[किल्ली_F2] = SDL_SCANCODE_F2;
    keymap[किल्ली_F3] = SDL_SCANCODE_F3;
    keymap[किल्ली_F4] = SDL_SCANCODE_F4;
    keymap[किल्ली_F5] = SDL_SCANCODE_F5;
    keymap[किल्ली_F6] = SDL_SCANCODE_F6;
    keymap[किल्ली_F7] = SDL_SCANCODE_F7;
    keymap[किल्ली_F8] = SDL_SCANCODE_F8;
    keymap[किल्ली_F9] = SDL_SCANCODE_F9;
    keymap[किल्ली_F10] = SDL_SCANCODE_F10;
    keymap[किल्ली_F11] = SDL_SCANCODE_F11;
    keymap[किल्ली_F12] = SDL_SCANCODE_F12;
    keymap[किल्ली_F13] = SDL_SCANCODE_PRINT;
    keymap[किल्ली_F14] = SDL_SCANCODE_PAUSE;

    keymap[किल्ली_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[किल्ली_1] = SDL_SCANCODE_1;
    keymap[किल्ली_2_2] = SDL_SCANCODE_2;
    keymap[किल्ली_3] = SDL_SCANCODE_3;
    keymap[किल्ली_4] = SDL_SCANCODE_4;
    keymap[किल्ली_5] = SDL_SCANCODE_5;
    keymap[किल्ली_6] = SDL_SCANCODE_6;
    keymap[किल्ली_7] = SDL_SCANCODE_7;
    keymap[किल्ली_8] = SDL_SCANCODE_8;
    keymap[किल्ली_9] = SDL_SCANCODE_9;
    keymap[किल्ली_0] = SDL_SCANCODE_0;
    keymap[किल्ली_MINUS] = SDL_SCANCODE_MINUS;
    keymap[किल्ली_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[किल्ली_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[किल्ली_TAB] = SDL_SCANCODE_TAB;
    keymap[किल्ली_Q] = SDL_SCANCODE_q;
    keymap[किल्ली_W] = SDL_SCANCODE_w;
    keymap[किल्ली_E] = SDL_SCANCODE_e;
    keymap[किल्ली_R] = SDL_SCANCODE_r;
    keymap[किल्ली_T] = SDL_SCANCODE_t;
    keymap[किल्ली_Y] = SDL_SCANCODE_y;
    keymap[किल्ली_U] = SDL_SCANCODE_u;
    keymap[किल्ली_I] = SDL_SCANCODE_i;
    keymap[किल्ली_O] = SDL_SCANCODE_o;
    keymap[किल्ली_P] = SDL_SCANCODE_p;
    keymap[किल्ली_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[किल्ली_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[किल्ली_ENTER] = SDL_SCANCODE_RETURN;

    keymap[किल्ली_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[किल्ली_A] = SDL_SCANCODE_a;
    keymap[किल्ली_S] = SDL_SCANCODE_s;
    keymap[किल्ली_D] = SDL_SCANCODE_d;
    keymap[किल्ली_F] = SDL_SCANCODE_f;
    keymap[किल्ली_G] = SDL_SCANCODE_g;
    keymap[किल्ली_H] = SDL_SCANCODE_h;
    keymap[किल्ली_J] = SDL_SCANCODE_j;
    keymap[किल्ली_K] = SDL_SCANCODE_k;
    keymap[किल्ली_L] = SDL_SCANCODE_l;
    keymap[किल्ली_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[किल्ली_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[किल्ली_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[किल्ली_Z] = SDL_SCANCODE_z;
    keymap[किल्ली_X] = SDL_SCANCODE_x;
    keymap[किल्ली_C] = SDL_SCANCODE_c;
    keymap[किल्ली_V] = SDL_SCANCODE_v;
    keymap[किल्ली_B] = SDL_SCANCODE_b;
    keymap[किल्ली_N] = SDL_SCANCODE_n;
    keymap[किल्ली_M] = SDL_SCANCODE_m;
    keymap[किल्ली_COMMA] = SDL_SCANCODE_COMMA;
    keymap[किल्ली_DOT] = SDL_SCANCODE_PERIOD;
    keymap[किल्ली_SLASH] = SDL_SCANCODE_SLASH;

    keymap[किल्ली_SPACE] = SDL_SCANCODE_SPACE;

    keymap[किल्ली_UP] = SDL_SCANCODE_UP;
    keymap[किल्ली_DOWN] = SDL_SCANCODE_DOWN;
    keymap[किल्ली_डावा] = SDL_SCANCODE_डावा;
    keymap[किल्ली_उजवा] = SDL_SCANCODE_उजवा;

    keymap[किल्ली_HOME] = SDL_SCANCODE_HOME;
    keymap[किल्ली_END] = SDL_SCANCODE_END;
    keymap[किल्ली_घाला] = SDL_SCANCODE_घाला;
    keymap[किल्ली_DELETE] = SDL_SCANCODE_DELETE;

    keymap[किल्ली_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[किल्ली_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[किल्ली_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[किल्ली_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[किल्ली_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[किल्ली_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[किल्ली_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[किल्ली_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[किल्ली_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[किल्ली_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[किल्ली_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[किल्ली_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[किल्ली_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[किल्ली_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णांक outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    पूर्णांक ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    जर (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } अन्यथा {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    जर ((event_sem = SDL_CreateSemaphore(1)) == रिक्त) {
        परत SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    जर ((thread = SDL_Create_Thread_With_चळत_Size(EventUpdate, "PSPInputThread", 4096, रिक्त)) == रिक्त) {
        परत SDL_SetError("Can't create input thread");
    }
    परत true;
}

शून्य PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, रिक्त);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    जर (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP
