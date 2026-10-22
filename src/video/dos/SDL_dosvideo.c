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

#که_تعریف_شوی SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../SDL_sysvideo.h"

// DOS declarations
#ضمن "SDL_dosevents_c.h"
#ضمن "SDL_dosframebuffer_c.h"
#ضمن "SDL_dosmodes.h"
#ضمن "SDL_dosmouse.h"
#ضمن "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
ساكن فراغ DOSVESA_Apply_ډېرپېښ_For_کړکۍ(SDL_VideoDisplay *display, SDL_کړکۍ *کړکۍ, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_سېټ_Display_ډېرپېښ_For_Display(display, ډېرپېښ);

    إذا (ډېرپېښ) {
        SDL_copyp(&کړکۍ->requested_fullscreen_ډېرپېښ, ډېرپېښ);
        کړکۍ->floating.w = کړکۍ->windowed.w = کړکۍ->w = ډېرپېښ->w;
        کړکۍ->floating.h = کړکۍ->windowed.h = کړکۍ->h = ډېرپېښ->h;
    }
}

ساكن bool DOSVESA_Create_کړکۍ(SDL_VideoDevice *device, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_کړکۍ_معلومات *wdata = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    کړکۍ->دننی = wdata;

    // One window, it always has focus
    SDL_سېټ_Mouse_Focus(کړکۍ);
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
        إذا (!display) {
            أرجع true;
        }

        SDL_Display_ډېرپېښ *ډېرپېښ = عدم;
        SDL_Display_ډېرپېښ closest;
        إذا (کړکۍ->requested_fullscreen_ډېرپېښ.دننی) {
            // App explicitly set a fullscreen mode.
            ډېرپېښ = &کړکۍ->requested_fullscreen_ډېرپېښ;
        } وإلا إذا (کړکۍ->floating.w > 0 && کړکۍ->floating.h > 0) {
            إذا (SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(display->id, کړکۍ->floating.w, کړکۍ->floating.h, 0.0f, false, &closest)) {
                ډېرپېښ = &closest;
            }
        }
        إذا (!ډېرپېښ) {
            أرجع true;
        }

        DOSVESA_Apply_ډېرپېښ_For_کړکۍ(display, کړکۍ, ډېرپېښ);
    }

    أرجع true;
}

ساكن فراغ DOSVESA_سېټ_کړکۍ_اندازه(SDL_VideoDevice *device, SDL_کړکۍ *کړکۍ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    إذا (!display) {
        أرجع;
    }

    SDL_Display_ډېرپېښ closest;
    SDL_Display_ډېرپېښ *ډېرپېښ = عدم;
    إذا (SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(display->id, کړکۍ->floating.w, کړکۍ->floating.h, 0.0f, false, &closest)) {
        ډېرپېښ = &closest;
    }

    DOSVESA_Apply_ډېرپېښ_For_کړکۍ(display, کړکۍ, ډېرپېښ);

    // Invalidate the framebuffer so it gets recreated at the new size.
    کړکۍ->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
ساكن فراغ DOSVESA_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *device, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    *w = کړکۍ->w;
    *h = کړکۍ->h;
}

ساكن فراغ DOSVESA_Destroy_کړکۍ(SDL_VideoDevice *device, SDL_کړکۍ *کړکۍ)
{
    SDL_free(کړکۍ->دننی);
    کړکۍ->دننی = عدم;
}

ساكن bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    إذا (__djgpp_conventional_base == 0) {
        أرجع SDL_سېټ_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_ډېرپېښ ډېرپېښ;
    SDL_zero(ډېرپېښ);
    ډېرپېښ.format = SDL_PIXELFORMAT_RGB565;
    ډېرپېښ.w = 320;
    ډېرپېښ.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_ډېرپېښ, &ډېرپېښ, حجم(ډېرپېښ));
    vdisplay.name = (حرف *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_جمع_کړه_Video_Display(&vdisplay, false);
    إذا (!display_id) {
        أرجع false;
    }

    SDL_zero(معلومات->current_ډېرپېښ);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    إذا (!display || !DOSVESA_GetDisplayModes(device, display)) {
        أرجع false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_ډېرپېښ closest;
        إذا (SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_ډېرپېښ_معلومات *desktop_دننی = (SDL_Display_ډېرپېښ_معلومات *)SDL_malloc(حجم(*desktop_دننی));
            إذا (desktop_دننی) {
                SDL_copyp(desktop_دننی, (ثابت SDL_Display_ډېرپېښ_معلومات *)closest.دننی);
                SDL_copyp(&display->desktop_ډېرپېښ, &closest);
                display->desktop_ډېرپېښ.دننی = desktop_دننی;
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
        إذا (regs.x.ax == 0x004F) {
            معلومات->original_vbe_ډېرپېښ = regs.x.bx;
        } وإلا {
            معلومات->original_vbe_ډېرپېښ = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        إذا (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_اندازه = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            فراغ *state_buf = DOS_Allocate_Conventional_حافظه(state_اندازه, &state_seginfo);
            إذا (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_خطي_منزل_Physical(state_buf) / 16;
                regs.x.bx = DOS_خطي_منزل_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                إذا (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    معلومات->vbe_state_بفر = SDL_malloc(state_اندازه);
                    إذا (معلومات->vbe_state_بفر) {
                        SDL_memcpy(معلومات->vbe_state_بفر, state_buf, state_اندازه);
                        معلومات->vbe_state_بفر_اندازه = state_اندازه;
                    }
                }
                DOS_Free_Conventional_حافظه(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    أرجع true;
}

ساكن فراغ DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;

    إذا (معلومات->mapping.اندازه) {
        __dpmi_free_physical_address_mapping(&معلومات->mapping); // dump existing video mapping.
        SDL_zero(معلومات->mapping);
    }

    // Restore saved VBE state if available.
    إذا (معلومات->vbe_state_بفر && معلومات->vbe_state_بفر_اندازه > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        فراغ *restore_buf = DOS_Allocate_Conventional_حافظه(معلومات->vbe_state_بفر_اندازه, &restore_seginfo);
        إذا (restore_buf) {
            SDL_memcpy(restore_buf, معلومات->vbe_state_بفر, معلومات->vbe_state_بفر_اندازه);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_خطي_منزل_Physical(restore_buf) / 16;
            regs.x.bx = DOS_خطي_منزل_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_حافظه(&restore_seginfo);
        }
        SDL_free(معلومات->vbe_state_بفر);
        معلومات->vbe_state_بفر = عدم;
        معلومات->vbe_state_بفر_اندازه = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        إذا (معلومات->original_vbe_ډېرپېښ != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = معلومات->original_vbe_ډېرپېښ;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        إذا (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(معلومات->current_ډېرپېښ);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

ساكن فراغ DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->دننی;
    SDL_free(معلومات->vbe_state_بفر);
    SDL_free(device->دننی);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

ساكن SDL_VideoDevice *DOSVESA_CreateDevice(فراغ)
{
    إذا (!DOSVESA_SupportsVESA()) {
        أرجع عدم;
    }

    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->دننی = phdata;
    device->حرر = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = DOSVESA_سېټ_Display_ډېرپېښ;
    device->CreateSDLWindow = DOSVESA_Create_کړکۍ;
    device->سېټ_کړکۍ_اندازه = DOSVESA_سېټ_کړکۍ_اندازه;
    device->Destroy_کړکۍ = DOSVESA_Destroy_کړکۍ;
    device->Create_کړکۍ_Framebuffer = DOSVESA_Create_کړکۍ_Framebuffer;
    device->سېټ_کړکۍ_Framebuffer_VSync = DOSVESA_سېټ_کړکۍ_Framebuffer_VSync;
    device->Get_کړکۍ_Framebuffer_VSync = DOSVESA_Get_کړکۍ_Framebuffer_VSync;
    device->Update_کړکۍ_Framebuffer = DOSVESA_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = DOSVESA_Destroy_کړکۍ_Framebuffer;
    device->Get_کړکۍ_اندازه_دننه_Pixels = DOSVESA_Get_کړکۍ_اندازه_دننه_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

#د_که_پای // SDL_VIDEO_DRIVER_DOSVESA
