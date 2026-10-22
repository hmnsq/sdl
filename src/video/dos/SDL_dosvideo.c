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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../SDL_sysvideo.h"

// DOS declarations
#شامل "SDL_dosevents_c.h"
#شامل "SDL_dosframebuffer_c.h"
#شامل "SDL_dosmodes.h"
#شامل "SDL_dosmouse.h"
#شامل "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
ساکن خالی DOSVESA_Apply_منوال_For_کھڑکی(SDL_VideoDisplay *display, SDL_کھڑکی *کھڑکی, SDL_Display_منوال *منوال)
{
    SDL_سیٹ_Display_منوال_For_Display(display, منوال);

    اگر (منوال) {
        SDL_copyp(&کھڑکی->requested_fullscreen_منوال, منوال);
        کھڑکی->floating.w = کھڑکی->windowed.w = کھڑکی->w = منوال->w;
        کھڑکی->floating.h = کھڑکی->windowed.h = کھڑکی->h = منوال->h;
    }
}

ساکن bool DOSVESA_Create_کھڑکی(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_کھڑکی_ڈیٹا *wdata = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!wdata) {
        واپس false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = wdata;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
        اگر (!display) {
            واپس true;
        }

        SDL_Display_منوال *منوال = تہی;
        SDL_Display_منوال closest;
        اگر (کھڑکی->requested_fullscreen_منوال.اندرونی_2) {
            // App explicitly set a fullscreen mode.
            منوال = &کھڑکی->requested_fullscreen_منوال;
        } ورنہ اگر (کھڑکی->floating.w > 0 && کھڑکی->floating.h > 0) {
            اگر (SDL_Get_Closest_Fullscreen_Display_منوال(display->id, کھڑکی->floating.w, کھڑکی->floating.h, 0.0f, false, &closest)) {
                منوال = &closest;
            }
        }
        اگر (!منوال) {
            واپس true;
        }

        DOSVESA_Apply_منوال_For_کھڑکی(display, کھڑکی, منوال);
    }

    واپس true;
}

ساکن خالی DOSVESA_سیٹ_کھڑکی_سائز(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    اگر (!display) {
        واپس;
    }

    SDL_Display_منوال closest;
    SDL_Display_منوال *منوال = تہی;
    اگر (SDL_Get_Closest_Fullscreen_Display_منوال(display->id, کھڑکی->floating.w, کھڑکی->floating.h, 0.0f, false, &closest)) {
        منوال = &closest;
    }

    DOSVESA_Apply_منوال_For_کھڑکی(display, کھڑکی, منوال);

    // Invalidate the framebuffer so it gets recreated at the new size.
    کھڑکی->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
ساکن خالی DOSVESA_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    *w = کھڑکی->w;
    *h = کھڑکی->h;
}

ساکن خالی DOSVESA_Destroy_کھڑکی(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی)
{
    SDL_free(کھڑکی->اندرونی_2);
    کھڑکی->اندرونی_2 = تہی;
}

ساکن bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    اگر (__djgpp_conventional_base == 0) {
        واپس SDL_سیٹ_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_منوال منوال;
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_RGB565;
    منوال.w = 320;
    منوال.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_منوال, &منوال, حجم(منوال));
    vdisplay.name = (حرف *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_جوڑو_Video_Display(&vdisplay, false);
    اگر (!display_id) {
        واپس false;
    }

    SDL_zero(ڈیٹا->current_منوال);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    اگر (!display || !DOSVESA_GetDisplayModes(device, display)) {
        واپس false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_منوال closest;
        اگر (SDL_Get_Closest_Fullscreen_Display_منوال(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_منوال_ڈیٹا *desktop_اندرونی = (SDL_Display_منوال_ڈیٹا *)SDL_malloc(حجم(*desktop_اندرونی));
            اگر (desktop_اندرونی) {
                SDL_copyp(desktop_اندرونی, (ثابت SDL_Display_منوال_ڈیٹا *)closest.اندرونی_2);
                SDL_copyp(&display->desktop_منوال, &closest);
                display->desktop_منوال.اندرونی_2 = desktop_اندرونی;
            }
        }
    }

    // Save the current video mode so we can restore it on quit.
    // The VBE calls (0x4F03, 0x4F04) return 0x004F on success; on cards
    // without VBE support (or VBE < 1.2) they simply fail and we fall
    // back to restoring standard text mode 0x03.
    {
        __dpmi_regs regs;
        SDL_zero(regs);
        regs.x.ax = 0x4F03; // VBE Get Current Mode
        __dpmi_int(0x10, &regs);
        اگر (regs.x.ax == 0x004F) {
            ڈیٹا->original_vbe_منوال = regs.x.bx;
        } ورنہ {
            ڈیٹا->original_vbe_منوال = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        اگر (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_سائز = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            خالی *state_buf = DOS_Allocate_Conventional_حافظہ(state_سائز, &state_seginfo);
            اگر (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_خطی_مقصد_Physical(state_buf) / 16;
                regs.x.bx = DOS_خطی_مقصد_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                اگر (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    ڈیٹا->vbe_state_بفر = SDL_malloc(state_سائز);
                    اگر (ڈیٹا->vbe_state_بفر) {
                        SDL_memcpy(ڈیٹا->vbe_state_بفر, state_buf, state_سائز);
                        ڈیٹا->vbe_state_بفر_سائز = state_سائز;
                    }
                }
                DOS_Free_Conventional_حافظہ(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    واپس true;
}

ساکن خالی DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;

    اگر (ڈیٹا->mapping.سائز) {
        __dpmi_free_physical_address_mapping(&ڈیٹا->mapping); // dump existing video mapping.
        SDL_zero(ڈیٹا->mapping);
    }

    // Restore saved VBE state if available.
    اگر (ڈیٹا->vbe_state_بفر && ڈیٹا->vbe_state_بفر_سائز > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        خالی *restore_buf = DOS_Allocate_Conventional_حافظہ(ڈیٹا->vbe_state_بفر_سائز, &restore_seginfo);
        اگر (restore_buf) {
            SDL_memcpy(restore_buf, ڈیٹا->vbe_state_بفر, ڈیٹا->vbe_state_بفر_سائز);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_خطی_مقصد_Physical(restore_buf) / 16;
            regs.x.bx = DOS_خطی_مقصد_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_حافظہ(&restore_seginfo);
        }
        SDL_free(ڈیٹا->vbe_state_بفر);
        ڈیٹا->vbe_state_بفر = تہی;
        ڈیٹا->vbe_state_بفر_سائز = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        اگر (ڈیٹا->original_vbe_منوال != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = ڈیٹا->original_vbe_منوال;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        اگر (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(ڈیٹا->current_منوال);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

ساکن خالی DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    SDL_free(ڈیٹا->vbe_state_بفر);
    SDL_free(device->اندرونی_2);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

ساکن SDL_VideoDevice *DOSVESA_CreateDevice(خالی)
{
    اگر (!DOSVESA_SupportsVESA()) {
        واپس تہی;
    }

    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal data
    phdata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!phdata) {
        SDL_free(device);
        واپس تہی;
    }

    device->اندرونی_2 = phdata;
    device->آزاد = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->سیٹ_Display_منوال = DOSVESA_سیٹ_Display_منوال;
    device->CreateSDLWindow = DOSVESA_Create_کھڑکی;
    device->سیٹ_کھڑکی_سائز = DOSVESA_سیٹ_کھڑکی_سائز;
    device->Destroy_کھڑکی = DOSVESA_Destroy_کھڑکی;
    device->Create_کھڑکی_Framebuffer = DOSVESA_Create_کھڑکی_Framebuffer;
    device->سیٹ_کھڑکی_Framebuffer_VSync = DOSVESA_سیٹ_کھڑکی_Framebuffer_VSync;
    device->Get_کھڑکی_Framebuffer_VSync = DOSVESA_Get_کھڑکی_Framebuffer_VSync;
    device->Update_کھڑکی_Framebuffer = DOSVESA_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = DOSVESA_Destroy_کھڑکی_Framebuffer;
    device->Get_کھڑکی_سائز_اندر_Pixels = DOSVESA_Get_کھڑکی_سائز_اندر_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    تہی, // no ShowMessageBox implementation
    false
};

#اگر_ختم // SDL_VIDEO_DRIVER_DOSVESA
