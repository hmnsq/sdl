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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../thread/SDL_systhread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <psphprm.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pspthreadman.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PSPIRKEYB
#ਅਨ੍ਤਰ੍ਭਾਵ <pspirkeyb.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pspirkeyb_rawkeys.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IRKBD_CONFIG_FILE ਨਿਰਾ // this will take ms0:/seplugins/pspirkeyb.ini

ਸਥਿਰ ਪੂਰਨ irkbd_ready = 0;
ਸਥਿਰ SDL_Scancode keymap[256];
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਗਿਣਤੀ Psp_Hprm_ਕੁੰਜੀਆਂ hprm = 0;
ਸਥਿਰ SDL_Semaphore *event_sem = ਨਿਰਾ;
ਸਥਿਰ SDL_Thread *thread = ਨਿਰਾ;
ਸਥਿਰ ਪੂਰਨ running = 0;
ਸਥਿਰ ਬਣਤਰ
{
    ਗਿਣਤੀ Psp_Hprm_ਕੁੰਜੀਆਂ id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_ਪਿੱਠ, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_ਉੱਪਰ, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_ਥੱਲੇ, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

ਪੂਰਨ EventUpdate(ਖਾਲੀ *ਅੰਕੜੇ)
{
    ਜਦੋਂ (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_ਕੁੰਜੀ((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    ਵਾਪਸ 0;
}

ਖਾਲੀ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    ਪੂਰਨ i;
    ਗਿਣਤੀ Psp_Hprm_ਕੁੰਜੀਆਂ ਕੁੰਜੀਆਂ;
    ਗਿਣਤੀ Psp_Hprm_ਕੁੰਜੀਆਂ ਬਦਲਿਆ;
    ਸਥਿਰ ਗਿਣਤੀ Psp_Hprm_ਕੁੰਜੀਆਂ old_ਕੁੰਜੀਆਂ = 0;

    SDL_WaitSemaphore(event_sem);
    ਕੁੰਜੀਆਂ = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    ਬਦਲਿਆ = old_ਕੁੰਜੀਆਂ ^ ਕੁੰਜੀਆਂ;
    old_ਕੁੰਜੀਆਂ = ਕੁੰਜੀਆਂ;
    ਜੇ (ਬਦਲਿਆ) {
        ਲਈ (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            ਜੇ (ਬਦਲਿਆ & keymap_psp[i].id) {
                bool ਥੱਲੇ = ((ਕੁੰਜੀਆਂ & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, ਥੱਲੇ);
            }
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PSPIRKEYB
    ਜੇ (irkbd_ready) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਬਫਰ_2[255];
        ਪੂਰਨ i, ਲੰਮਾਈ, ਗਿਣਤੀ_2;
        SIr_Keyb_ਜਾਂਚ_ਕੋਡ_ਅੰਕੜੇ *ਜਾਂਚ_ਅੰਕੜੇ;

        ਜੇ (pspIrKeybReadinput(ਬਫਰ_2, &ਲੰਮਾਈ) >= 0) {
            ਜੇ ((ਲੰਮਾਈ % ਆਕਾਰ(SIr_Keyb_ਜਾਂਚ_ਕੋਡ_ਅੰਕੜੇ)) == 0) {
                ਗਿਣਤੀ_2 = ਲੰਮਾਈ / ਆਕਾਰ(SIr_Keyb_ਜਾਂਚ_ਕੋਡ_ਅੰਕੜੇ);
                ਲਈ (i = 0; i < ਗਿਣਤੀ_2; i++) {
                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ raw;
                    bool ਥੱਲੇ;
                    ਜਾਂਚ_ਅੰਕੜੇ = (SIr_Keyb_ਜਾਂਚ_ਕੋਡ_ਅੰਕੜੇ *)ਬਫਰ_2 + i;
                    raw = ਜਾਂਚ_ਅੰਕੜੇ->raw;
                    ਥੱਲੇ = (ਜਾਂਚ_ਅੰਕੜੇ->pressed != 0);
                    SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], ਥੱਲੇ);
                }
            }
        }
    }
#ਜੇ_ਅੰਤ
    sceKernelDelayThread(0);

    ਵਾਪਸ;
}

ਖਾਲੀ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PSPIRKEYB
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[ਕੁੰਜੀ_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[ਕੁੰਜੀ_F1] = SDL_SCANCODE_F1;
    keymap[ਕੁੰਜੀ_F2] = SDL_SCANCODE_F2;
    keymap[ਕੁੰਜੀ_F3] = SDL_SCANCODE_F3;
    keymap[ਕੁੰਜੀ_F4] = SDL_SCANCODE_F4;
    keymap[ਕੁੰਜੀ_F5] = SDL_SCANCODE_F5;
    keymap[ਕੁੰਜੀ_F6] = SDL_SCANCODE_F6;
    keymap[ਕੁੰਜੀ_F7] = SDL_SCANCODE_F7;
    keymap[ਕੁੰਜੀ_F8] = SDL_SCANCODE_F8;
    keymap[ਕੁੰਜੀ_F9] = SDL_SCANCODE_F9;
    keymap[ਕੁੰਜੀ_F10] = SDL_SCANCODE_F10;
    keymap[ਕੁੰਜੀ_F11] = SDL_SCANCODE_F11;
    keymap[ਕੁੰਜੀ_F12] = SDL_SCANCODE_F12;
    keymap[ਕੁੰਜੀ_F13] = SDL_SCANCODE_PRINT;
    keymap[ਕੁੰਜੀ_F14] = SDL_SCANCODE_PAUSE;

    keymap[ਕੁੰਜੀ_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[ਕੁੰਜੀ_1] = SDL_SCANCODE_1;
    keymap[ਕੁੰਜੀ_2_2] = SDL_SCANCODE_2;
    keymap[ਕੁੰਜੀ_3] = SDL_SCANCODE_3;
    keymap[ਕੁੰਜੀ_4] = SDL_SCANCODE_4;
    keymap[ਕੁੰਜੀ_5] = SDL_SCANCODE_5;
    keymap[ਕੁੰਜੀ_6] = SDL_SCANCODE_6;
    keymap[ਕੁੰਜੀ_7] = SDL_SCANCODE_7;
    keymap[ਕੁੰਜੀ_8] = SDL_SCANCODE_8;
    keymap[ਕੁੰਜੀ_9] = SDL_SCANCODE_9;
    keymap[ਕੁੰਜੀ_0] = SDL_SCANCODE_0;
    keymap[ਕੁੰਜੀ_MINUS] = SDL_SCANCODE_MINUS;
    keymap[ਕੁੰਜੀ_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[ਕੁੰਜੀ_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[ਕੁੰਜੀ_TAB] = SDL_SCANCODE_TAB;
    keymap[ਕੁੰਜੀ_Q] = SDL_SCANCODE_q;
    keymap[ਕੁੰਜੀ_W] = SDL_SCANCODE_w;
    keymap[ਕੁੰਜੀ_E] = SDL_SCANCODE_e;
    keymap[ਕੁੰਜੀ_R] = SDL_SCANCODE_r;
    keymap[ਕੁੰਜੀ_T] = SDL_SCANCODE_t;
    keymap[ਕੁੰਜੀ_Y] = SDL_SCANCODE_y;
    keymap[ਕੁੰਜੀ_U] = SDL_SCANCODE_u;
    keymap[ਕੁੰਜੀ_I] = SDL_SCANCODE_i;
    keymap[ਕੁੰਜੀ_O] = SDL_SCANCODE_o;
    keymap[ਕੁੰਜੀ_P] = SDL_SCANCODE_p;
    keymap[ਕੁੰਜੀ_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[ਕੁੰਜੀ_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[ਕੁੰਜੀ_ENTER] = SDL_SCANCODE_RETURN;

    keymap[ਕੁੰਜੀ_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[ਕੁੰਜੀ_A] = SDL_SCANCODE_a;
    keymap[ਕੁੰਜੀ_S] = SDL_SCANCODE_s;
    keymap[ਕੁੰਜੀ_D] = SDL_SCANCODE_d;
    keymap[ਕੁੰਜੀ_F] = SDL_SCANCODE_f;
    keymap[ਕੁੰਜੀ_G] = SDL_SCANCODE_g;
    keymap[ਕੁੰਜੀ_H] = SDL_SCANCODE_h;
    keymap[ਕੁੰਜੀ_J] = SDL_SCANCODE_j;
    keymap[ਕੁੰਜੀ_K] = SDL_SCANCODE_k;
    keymap[ਕੁੰਜੀ_L] = SDL_SCANCODE_l;
    keymap[ਕੁੰਜੀ_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[ਕੁੰਜੀ_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[ਕੁੰਜੀ_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[ਕੁੰਜੀ_Z] = SDL_SCANCODE_z;
    keymap[ਕੁੰਜੀ_X] = SDL_SCANCODE_x;
    keymap[ਕੁੰਜੀ_C] = SDL_SCANCODE_c;
    keymap[ਕੁੰਜੀ_V] = SDL_SCANCODE_v;
    keymap[ਕੁੰਜੀ_B] = SDL_SCANCODE_b;
    keymap[ਕੁੰਜੀ_N] = SDL_SCANCODE_n;
    keymap[ਕੁੰਜੀ_M] = SDL_SCANCODE_m;
    keymap[ਕੁੰਜੀ_COMMA] = SDL_SCANCODE_COMMA;
    keymap[ਕੁੰਜੀ_DOT] = SDL_SCANCODE_PERIOD;
    keymap[ਕੁੰਜੀ_SLASH] = SDL_SCANCODE_SLASH;

    keymap[ਕੁੰਜੀ_SPACE] = SDL_SCANCODE_SPACE;

    keymap[ਕੁੰਜੀ_ਉੱਪਰ] = SDL_SCANCODE_ਉੱਪਰ;
    keymap[ਕੁੰਜੀ_ਥੱਲੇ] = SDL_SCANCODE_ਥੱਲੇ;
    keymap[ਕੁੰਜੀ_ਖੱਬਾ] = SDL_SCANCODE_ਖੱਬਾ;
    keymap[ਕੁੰਜੀ_ਸੱਜਾ] = SDL_SCANCODE_ਸੱਜਾ;

    keymap[ਕੁੰਜੀ_HOME] = SDL_SCANCODE_HOME;
    keymap[ਕੁੰਜੀ_ਸਿਰਾ] = SDL_SCANCODE_ਸਿਰਾ;
    keymap[ਕੁੰਜੀ_ਪਾਓ] = SDL_SCANCODE_ਪਾਓ;
    keymap[ਕੁੰਜੀ_DELETE] = SDL_SCANCODE_DELETE;

    keymap[ਕੁੰਜੀ_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[ਕੁੰਜੀ_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[ਕੁੰਜੀ_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[ਕੁੰਜੀ_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[ਕੁੰਜੀ_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[ਕੁੰਜੀ_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[ਕੁੰਜੀ_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[ਕੁੰਜੀ_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[ਕੁੰਜੀ_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[ਕੁੰਜੀ_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[ਕੁੰਜੀ_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[ਕੁੰਜੀ_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[ਕੁੰਜੀ_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[ਕੁੰਜੀ_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#ਜੇ_ਅੰਤ
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PSPIRKEYB
    ਪੂਰਨ outputmode = PSP_IRKBD_OUTPUT_ਬਹੁਲਕ_SCANCODE;
    ਪੂਰਨ ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    ਜੇ (ret == PSP_IRKBD_ਨਤੀਜਾ_OK) {
        psp_Ir_Keyb_Output_ਬਹੁਲਕ(outputmode);
        irkbd_ready = 1;
    } ਨਹੀਂਤਾਂ {
        irkbd_ready = 0;
    }
#ਜੇ_ਅੰਤ
    // Start thread to read data
    ਜੇ ((event_sem = SDL_CreateSemaphore(1)) == ਨਿਰਾ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't create input semaphore");
    }
    running = 1;
    ਜੇ ((thread = SDL_Create_Thread_With_ਢੇਰ_ਮਾਪ(EventUpdate, "PSPInputThread", 4096, ਨਿਰਾ)) == ਨਿਰਾ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Can't create input thread");
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, ਨਿਰਾ);
    SDL_DestroySemaphore(event_sem);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PSPIRKEYB
    ਜੇ (irkbd_ready) {
        psp_Ir_Keyb_ਅੰਤ();
        irkbd_ready = 0;
    }
#ਜੇ_ਅੰਤ
}

// end of SDL_pspevents.c ...

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_PSP
