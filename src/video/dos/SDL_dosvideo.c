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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

// DOS declarations
#ಅನ್ತರ್ಭಾವ "SDL_dosevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_Apply_ಬಹುಲಕ_For_ಕಿಟಕಿ(SDL_VideoDisplay *display, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(display, ಬಹುಲಕ);

    ಆದರೆ (ಬಹುಲಕ) {
        SDL_copyp(&ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ, ಬಹುಲಕ);
        ಕಿಟಕಿ->floating.w = ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->w = ಬಹುಲಕ->w;
        ಕಿಟಕಿ->floating.h = ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->h = ಬಹುಲಕ->h;
    }
}

ಸ್ಥಿರ bool DOSVESA_Create_ಕಿಟಕಿ(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!wdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = wdata;

    // One window, it always has focus
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಆದರೆ (!display) {
            ಹಿಂತಿರುಗಿ true;
        }

        SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ = ಖಾಲಿ;
        SDL_Display_ಬಹುಲಕ closest;
        ಆದರೆ (ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.ಆಂತರಿಕ) {
            // App explicitly set a fullscreen mode.
            ಬಹುಲಕ = &ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->floating.w > 0 && ಕಿಟಕಿ->floating.h > 0) {
            ಆದರೆ (SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(display->id, ಕಿಟಕಿ->floating.w, ಕಿಟಕಿ->floating.h, 0.0f, false, &closest)) {
                ಬಹುಲಕ = &closest;
            }
        }
        ಆದರೆ (!ಬಹುಲಕ) {
            ಹಿಂತಿರುಗಿ true;
        }

        DOSVESA_Apply_ಬಹುಲಕ_For_ಕಿಟಕಿ(display, ಕಿಟಕಿ, ಬಹುಲಕ);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಆದರೆ (!display) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Display_ಬಹುಲಕ closest;
    SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ = ಖಾಲಿ;
    ಆದರೆ (SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(display->id, ಕಿಟಕಿ->floating.w, ಕಿಟಕಿ->floating.h, 0.0f, false, &closest)) {
        ಬಹುಲಕ = &closest;
    }

    DOSVESA_Apply_ಬಹುಲಕ_For_ಕಿಟಕಿ(display, ಕಿಟಕಿ, ಬಹುಲಕ);

    // Invalidate the framebuffer so it gets recreated at the new size.
    ಕಿಟಕಿ->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    *w = ಕಿಟಕಿ->w;
    *h = ಕಿಟಕಿ->h;
}

ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

ಸ್ಥಿರ bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    ಆದರೆ (__djgpp_conventional_base == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_RGB565;
    ಬಹುಲಕ.w = 320;
    ಬಹುಲಕ.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_ಬಹುಲಕ, &ಬಹುಲಕ, ಗಾತ್ರ(ಬಹುಲಕ));
    vdisplay.name = (ಅಕ್ಷರ *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_ಕೂಡಿಸು_Video_Display(&vdisplay, false);
    ಆದರೆ (!display_id) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zero(ದತ್ತಾಂಶ->current_ಬಹುಲಕ);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    ಆದರೆ (!display || !DOSVESA_GetDisplayModes(device, display)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_ಬಹುಲಕ closest;
        ಆದರೆ (SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *desktop_ಆಂತರಿಕ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_malloc(ಗಾತ್ರ(*desktop_ಆಂತರಿಕ));
            ಆದರೆ (desktop_ಆಂತರಿಕ) {
                SDL_copyp(desktop_ಆಂತರಿಕ, (ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)closest.ಆಂತರಿಕ);
                SDL_copyp(&display->desktop_ಬಹುಲಕ, &closest);
                display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ = desktop_ಆಂತರಿಕ;
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
        ಆದರೆ (regs.x.ax == 0x004F) {
            ದತ್ತಾಂಶ->original_vbe_ಬಹುಲಕ = regs.x.bx;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->original_vbe_ಬಹುಲಕ = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        ಆದರೆ (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_ಗಾತ್ರ = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            ಶೂನ್ಯ *state_buf = DOS_Allocate_Conventional_ಸ್ಮರಣೆ(state_ಗಾತ್ರ, &state_seginfo);
            ಆದರೆ (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(state_buf) / 16;
                regs.x.bx = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                ಆದರೆ (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    ದತ್ತಾಂಶ->vbe_state_ಬಫರ್ = SDL_malloc(state_ಗಾತ್ರ);
                    ಆದರೆ (ದತ್ತಾಂಶ->vbe_state_ಬಫರ್) {
                        SDL_memcpy(ದತ್ತಾಂಶ->vbe_state_ಬಫರ್, state_buf, state_ಗಾತ್ರ);
                        ದತ್ತಾಂಶ->vbe_state_ಬಫರ್_ಗಾತ್ರ = state_ಗಾತ್ರ;
                    }
                }
                DOS_Free_Conventional_ಸ್ಮರಣೆ(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2) {
        __dpmi_free_physical_address_mapping(&ದತ್ತಾಂಶ->mapping); // dump existing video mapping.
        SDL_zero(ದತ್ತಾಂಶ->mapping);
    }

    // Restore saved VBE state if available.
    ಆದರೆ (ದತ್ತಾಂಶ->vbe_state_ಬಫರ್ && ದತ್ತಾಂಶ->vbe_state_ಬಫರ್_ಗಾತ್ರ > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        ಶೂನ್ಯ *restore_buf = DOS_Allocate_Conventional_ಸ್ಮರಣೆ(ದತ್ತಾಂಶ->vbe_state_ಬಫರ್_ಗಾತ್ರ, &restore_seginfo);
        ಆದರೆ (restore_buf) {
            SDL_memcpy(restore_buf, ದತ್ತಾಂಶ->vbe_state_ಬಫರ್, ದತ್ತಾಂಶ->vbe_state_ಬಫರ್_ಗಾತ್ರ);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(restore_buf) / 16;
            regs.x.bx = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_ಸ್ಮರಣೆ(&restore_seginfo);
        }
        SDL_free(ದತ್ತಾಂಶ->vbe_state_ಬಫರ್);
        ದತ್ತಾಂಶ->vbe_state_ಬಫರ್ = ಖಾಲಿ;
        ದತ್ತಾಂಶ->vbe_state_ಬಫರ್_ಗಾತ್ರ = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        ಆದರೆ (ದತ್ತಾಂಶ->original_vbe_ಬಹುಲಕ != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = ದತ್ತಾಂಶ->original_vbe_ಬಹುಲಕ;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        ಆದರೆ (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(ದತ್ತಾಂಶ->current_ಬಹುಲಕ);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

ಸ್ಥಿರ ಶೂನ್ಯ DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    SDL_free(ದತ್ತಾಂಶ->vbe_state_ಬಫರ್);
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

ಸ್ಥಿರ SDL_VideoDevice *DOSVESA_CreateDevice(ಶೂನ್ಯ)
{
    ಆದರೆ (!DOSVESA_SupportsVESA()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal data
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = phdata;
    device->ಬಿಡುಗಡೆ = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = DOSVESA_ಗಣ_Display_ಬಹುಲಕ;
    device->CreateSDLWindow = DOSVESA_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = DOSVESA_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Destroy_ಕಿಟಕಿ = DOSVESA_Destroy_ಕಿಟಕಿ;
    device->Create_ಕಿಟಕಿ_Framebuffer = DOSVESA_Create_ಕಿಟಕಿ_Framebuffer;
    device->ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync = DOSVESA_ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync;
    device->Get_ಕಿಟಕಿ_Framebuffer_VSync = DOSVESA_Get_ಕಿಟಕಿ_Framebuffer_VSync;
    device->Update_ಕಿಟಕಿ_Framebuffer = DOSVESA_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = DOSVESA_Destroy_ಕಿಟಕಿ_Framebuffer;
    device->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels = DOSVESA_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_DOSVESA
