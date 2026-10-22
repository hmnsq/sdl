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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

// DOS declarations
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
ਸਥਿਰ ਖਾਲੀ DOSVESA_Apply_ਬਹੁਲਕ_For_ਖਿੜਕੀ(SDL_VideoDisplay *display, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(display, ਬਹੁਲਕ);

    ਜੇ (ਬਹੁਲਕ) {
        SDL_copyp(&ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ, ਬਹੁਲਕ);
        ਖਿੜਕੀ->floating.w = ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->w = ਬਹੁਲਕ->w;
        ਖਿੜਕੀ->floating.h = ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->h = ਬਹੁਲਕ->h;
    }
}

ਸਥਿਰ bool DOSVESA_Create_ਖਿੜਕੀ(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!wdata) {
        ਵਾਪਸ false;
    }

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = wdata;

    // One window, it always has focus
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਜੇ (!display) {
            ਵਾਪਸ true;
        }

        SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ = ਨਿਰਾ;
        SDL_Display_ਬਹੁਲਕ closest;
        ਜੇ (ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ) {
            // App explicitly set a fullscreen mode.
            ਬਹੁਲਕ = &ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ;
        } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->floating.w > 0 && ਖਿੜਕੀ->floating.h > 0) {
            ਜੇ (SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(display->id, ਖਿੜਕੀ->floating.w, ਖਿੜਕੀ->floating.h, 0.0f, false, &closest)) {
                ਬਹੁਲਕ = &closest;
            }
        }
        ਜੇ (!ਬਹੁਲਕ) {
            ਵਾਪਸ true;
        }

        DOSVESA_Apply_ਬਹੁਲਕ_For_ਖਿੜਕੀ(display, ਖਿੜਕੀ, ਬਹੁਲਕ);
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ DOSVESA_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਜੇ (!display) {
        ਵਾਪਸ;
    }

    SDL_Display_ਬਹੁਲਕ closest;
    SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ = ਨਿਰਾ;
    ਜੇ (SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(display->id, ਖਿੜਕੀ->floating.w, ਖਿੜਕੀ->floating.h, 0.0f, false, &closest)) {
        ਬਹੁਲਕ = &closest;
    }

    DOSVESA_Apply_ਬਹੁਲਕ_For_ਖਿੜਕੀ(display, ਖਿੜਕੀ, ਬਹੁਲਕ);

    // Invalidate the framebuffer so it gets recreated at the new size.
    ਖਿੜਕੀ->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
ਸਥਿਰ ਖਾਲੀ DOSVESA_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    *w = ਖਿੜਕੀ->w;
    *h = ਖਿੜਕੀ->h;
}

ਸਥਿਰ ਖਾਲੀ DOSVESA_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

ਸਥਿਰ bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    ਜੇ (__djgpp_conventional_base == 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_RGB565;
    ਬਹੁਲਕ.w = 320;
    ਬਹੁਲਕ.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_ਬਹੁਲਕ, &ਬਹੁਲਕ, ਆਕਾਰ(ਬਹੁਲਕ));
    vdisplay.name = (ਅੱਖਰ *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_ਜੋੜੋ_Video_Display(&vdisplay, false);
    ਜੇ (!display_id) {
        ਵਾਪਸ false;
    }

    SDL_zero(ਅੰਕੜੇ->current_ਬਹੁਲਕ);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    ਜੇ (!display || !DOSVESA_GetDisplayModes(device, display)) {
        ਵਾਪਸ false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_ਬਹੁਲਕ closest;
        ਜੇ (SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *desktop_ਅੰਦਰੂਨੀ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_malloc(ਆਕਾਰ(*desktop_ਅੰਦਰੂਨੀ));
            ਜੇ (desktop_ਅੰਦਰੂਨੀ) {
                SDL_copyp(desktop_ਅੰਦਰੂਨੀ, (ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)closest.ਅੰਦਰੂਨੀ);
                SDL_copyp(&display->desktop_ਬਹੁਲਕ, &closest);
                display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = desktop_ਅੰਦਰੂਨੀ;
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
        ਜੇ (regs.x.ax == 0x004F) {
            ਅੰਕੜੇ->original_vbe_ਬਹੁਲਕ = regs.x.bx;
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->original_vbe_ਬਹੁਲਕ = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        ਜੇ (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_ਮਾਪ = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            ਖਾਲੀ *state_buf = DOS_Allocate_Conventional_ਸਮ੍ਰਿਤੀ(state_ਮਾਪ, &state_seginfo);
            ਜੇ (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(state_buf) / 16;
                regs.x.bx = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                ਜੇ (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    ਅੰਕੜੇ->vbe_state_ਬਫਰ = SDL_malloc(state_ਮਾਪ);
                    ਜੇ (ਅੰਕੜੇ->vbe_state_ਬਫਰ) {
                        SDL_memcpy(ਅੰਕੜੇ->vbe_state_ਬਫਰ, state_buf, state_ਮਾਪ);
                        ਅੰਕੜੇ->vbe_state_ਬਫਰ_ਮਾਪ = state_ਮਾਪ;
                    }
                }
                DOS_Free_Conventional_ਸਮ੍ਰਿਤੀ(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->mapping.ਮਾਪ) {
        __dpmi_free_physical_address_mapping(&ਅੰਕੜੇ->mapping); // dump existing video mapping.
        SDL_zero(ਅੰਕੜੇ->mapping);
    }

    // Restore saved VBE state if available.
    ਜੇ (ਅੰਕੜੇ->vbe_state_ਬਫਰ && ਅੰਕੜੇ->vbe_state_ਬਫਰ_ਮਾਪ > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        ਖਾਲੀ *restore_buf = DOS_Allocate_Conventional_ਸਮ੍ਰਿਤੀ(ਅੰਕੜੇ->vbe_state_ਬਫਰ_ਮਾਪ, &restore_seginfo);
        ਜੇ (restore_buf) {
            SDL_memcpy(restore_buf, ਅੰਕੜੇ->vbe_state_ਬਫਰ, ਅੰਕੜੇ->vbe_state_ਬਫਰ_ਮਾਪ);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(restore_buf) / 16;
            regs.x.bx = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_ਸਮ੍ਰਿਤੀ(&restore_seginfo);
        }
        SDL_free(ਅੰਕੜੇ->vbe_state_ਬਫਰ);
        ਅੰਕੜੇ->vbe_state_ਬਫਰ = ਨਿਰਾ;
        ਅੰਕੜੇ->vbe_state_ਬਫਰ_ਮਾਪ = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        ਜੇ (ਅੰਕੜੇ->original_vbe_ਬਹੁਲਕ != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = ਅੰਕੜੇ->original_vbe_ਬਹੁਲਕ;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        ਜੇ (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(ਅੰਕੜੇ->current_ਬਹੁਲਕ);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

ਸਥਿਰ ਖਾਲੀ DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    SDL_free(ਅੰਕੜੇ->vbe_state_ਬਫਰ);
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

ਸਥਿਰ SDL_VideoDevice *DOSVESA_CreateDevice(ਖਾਲੀ)
{
    ਜੇ (!DOSVESA_SupportsVESA()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal data
    phdata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!phdata) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = phdata;
    device->ਮੁਕਤ = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = DOSVESA_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->CreateSDLWindow = DOSVESA_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = DOSVESA_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Destroy_ਖਿੜਕੀ = DOSVESA_Destroy_ਖਿੜਕੀ;
    device->Create_ਖਿੜਕੀ_Framebuffer = DOSVESA_Create_ਖਿੜਕੀ_Framebuffer;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync = DOSVESA_ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync;
    device->Get_ਖਿੜਕੀ_Framebuffer_VSync = DOSVESA_Get_ਖਿੜਕੀ_Framebuffer_VSync;
    device->Update_ਖਿੜਕੀ_Framebuffer = DOSVESA_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = DOSVESA_Destroy_ਖਿੜਕੀ_Framebuffer;
    device->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels = DOSVESA_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DOSVESA
