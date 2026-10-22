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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"

// DOS declarations
#అన్తర్భావ "SDL_dosevents_c.h"
#అన్తర్భావ "SDL_dosframebuffer_c.h"
#అన్తర్భావ "SDL_dosmodes.h"
#అన్తర్భావ "SDL_dosmouse.h"
#అన్తర్భావ "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
స్థిర శూన్య DOSVESA_Apply_బహుళకం_For_కిటికీ(SDL_VideoDisplay *display, SDL_కిటికీ *కిటికీ, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_సమితి_Display_బహుళకం_For_Display(display, బహుళకం);

    ఒకవేళ (బహుళకం) {
        SDL_copyp(&కిటికీ->requested_fullscreen_బహుళకం, బహుళకం);
        కిటికీ->floating.w = కిటికీ->windowed.w = కిటికీ->w = బహుళకం->w;
        కిటికీ->floating.h = కిటికీ->windowed.h = కిటికీ->h = బహుళకం->h;
    }
}

స్థిర bool DOSVESA_Create_కిటికీ(SDL_VideoDevice *device, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_కిటికీ_దత్తాంశం *wdata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!wdata) {
        తిరిగి false;
    }

    // Setup driver data for this window
    కిటికీ->అంతర్గత = wdata;

    // One window, it always has focus
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
        ఒకవేళ (!display) {
            తిరిగి true;
        }

        SDL_Display_బహుళకం *బహుళకం = ఖాళీ;
        SDL_Display_బహుళకం closest;
        ఒకవేళ (కిటికీ->requested_fullscreen_బహుళకం.అంతర్గత) {
            // App explicitly set a fullscreen mode.
            బహుళకం = &కిటికీ->requested_fullscreen_బహుళకం;
        } లేకపోతే ఒకవేళ (కిటికీ->floating.w > 0 && కిటికీ->floating.h > 0) {
            ఒకవేళ (SDL_Get_Closest_Fullscreen_Display_బహుళకం(display->id, కిటికీ->floating.w, కిటికీ->floating.h, 0.0f, false, &closest)) {
                బహుళకం = &closest;
            }
        }
        ఒకవేళ (!బహుళకం) {
            తిరిగి true;
        }

        DOSVESA_Apply_బహుళకం_For_కిటికీ(display, కిటికీ, బహుళకం);
    }

    తిరిగి true;
}

స్థిర శూన్య DOSVESA_సమితి_కిటికీ_కొలత(SDL_VideoDevice *device, SDL_కిటికీ *కిటికీ)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    ఒకవేళ (!display) {
        తిరిగి;
    }

    SDL_Display_బహుళకం closest;
    SDL_Display_బహుళకం *బహుళకం = ఖాళీ;
    ఒకవేళ (SDL_Get_Closest_Fullscreen_Display_బహుళకం(display->id, కిటికీ->floating.w, కిటికీ->floating.h, 0.0f, false, &closest)) {
        బహుళకం = &closest;
    }

    DOSVESA_Apply_బహుళకం_For_కిటికీ(display, కిటికీ, బహుళకం);

    // Invalidate the framebuffer so it gets recreated at the new size.
    కిటికీ->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
స్థిర శూన్య DOSVESA_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *device, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    *w = కిటికీ->w;
    *h = కిటికీ->h;
}

స్థిర శూన్య DOSVESA_Destroy_కిటికీ(SDL_VideoDevice *device, SDL_కిటికీ *కిటికీ)
{
    SDL_free(కిటికీ->అంతర్గత);
    కిటికీ->అంతర్గత = ఖాళీ;
}

స్థిర bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    ఒకవేళ (__djgpp_conventional_base == 0) {
        తిరిగి SDL_సమితి_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_బహుళకం బహుళకం;
    SDL_zero(బహుళకం);
    బహుళకం.format = SDL_PIXELFORMAT_RGB565;
    బహుళకం.w = 320;
    బహుళకం.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_బహుళకం, &బహుళకం, పరిమాణం(బహుళకం));
    vdisplay.name = (అక్షరం *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_కూడు_Video_Display(&vdisplay, false);
    ఒకవేళ (!display_id) {
        తిరిగి false;
    }

    SDL_zero(దత్తాంశం->current_బహుళకం);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    ఒకవేళ (!display || !DOSVESA_GetDisplayModes(device, display)) {
        తిరిగి false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_బహుళకం closest;
        ఒకవేళ (SDL_Get_Closest_Fullscreen_Display_బహుళకం(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_బహుళకం_దత్తాంశం *desktop_అంతర్గత = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_malloc(పరిమాణం(*desktop_అంతర్గత));
            ఒకవేళ (desktop_అంతర్గత) {
                SDL_copyp(desktop_అంతర్గత, (స్థిరరాశి SDL_Display_బహుళకం_దత్తాంశం *)closest.అంతర్గత);
                SDL_copyp(&display->desktop_బహుళకం, &closest);
                display->desktop_బహుళకం.అంతర్గత = desktop_అంతర్గత;
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
        ఒకవేళ (regs.x.ax == 0x004F) {
            దత్తాంశం->original_vbe_బహుళకం = regs.x.bx;
        } లేకపోతే {
            దత్తాంశం->original_vbe_బహుళకం = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        ఒకవేళ (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_కొలత = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            శూన్య *state_buf = DOS_Allocate_Conventional_జ్ఞాపకం(state_కొలత, &state_seginfo);
            ఒకవేళ (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_రేఖీయ_గమ్యం_Physical(state_buf) / 16;
                regs.x.bx = DOS_రేఖీయ_గమ్యం_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                ఒకవేళ (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    దత్తాంశం->vbe_state_బఫరు = SDL_malloc(state_కొలత);
                    ఒకవేళ (దత్తాంశం->vbe_state_బఫరు) {
                        SDL_memcpy(దత్తాంశం->vbe_state_బఫరు, state_buf, state_కొలత);
                        దత్తాంశం->vbe_state_బఫరు_కొలత = state_కొలత;
                    }
                }
                DOS_Free_Conventional_జ్ఞాపకం(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    తిరిగి true;
}

స్థిర శూన్య DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;

    ఒకవేళ (దత్తాంశం->mapping.కొలత) {
        __dpmi_free_physical_address_mapping(&దత్తాంశం->mapping); // dump existing video mapping.
        SDL_zero(దత్తాంశం->mapping);
    }

    // Restore saved VBE state if available.
    ఒకవేళ (దత్తాంశం->vbe_state_బఫరు && దత్తాంశం->vbe_state_బఫరు_కొలత > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        శూన్య *restore_buf = DOS_Allocate_Conventional_జ్ఞాపకం(దత్తాంశం->vbe_state_బఫరు_కొలత, &restore_seginfo);
        ఒకవేళ (restore_buf) {
            SDL_memcpy(restore_buf, దత్తాంశం->vbe_state_బఫరు, దత్తాంశం->vbe_state_బఫరు_కొలత);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_రేఖీయ_గమ్యం_Physical(restore_buf) / 16;
            regs.x.bx = DOS_రేఖీయ_గమ్యం_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_జ్ఞాపకం(&restore_seginfo);
        }
        SDL_free(దత్తాంశం->vbe_state_బఫరు);
        దత్తాంశం->vbe_state_బఫరు = ఖాళీ;
        దత్తాంశం->vbe_state_బఫరు_కొలత = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        ఒకవేళ (దత్తాంశం->original_vbe_బహుళకం != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = దత్తాంశం->original_vbe_బహుళకం;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        ఒకవేళ (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(దత్తాంశం->current_బహుళకం);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

స్థిర శూన్య DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;
    SDL_free(దత్తాంశం->vbe_state_బఫరు);
    SDL_free(device->అంతర్గత);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

స్థిర SDL_VideoDevice *DOSVESA_CreateDevice(శూన్య)
{
    ఒకవేళ (!DOSVESA_SupportsVESA()) {
        తిరిగి ఖాళీ;
    }

    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal data
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = phdata;
    device->విడుదల = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->సమితి_Display_బహుళకం = DOSVESA_సమితి_Display_బహుళకం;
    device->CreateSDLWindow = DOSVESA_Create_కిటికీ;
    device->సమితి_కిటికీ_కొలత = DOSVESA_సమితి_కిటికీ_కొలత;
    device->Destroy_కిటికీ = DOSVESA_Destroy_కిటికీ;
    device->Create_కిటికీ_Framebuffer = DOSVESA_Create_కిటికీ_Framebuffer;
    device->సమితి_కిటికీ_Framebuffer_VSync = DOSVESA_సమితి_కిటికీ_Framebuffer_VSync;
    device->Get_కిటికీ_Framebuffer_VSync = DOSVESA_Get_కిటికీ_Framebuffer_VSync;
    device->Update_కిటికీ_Framebuffer = DOSVESA_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = DOSVESA_Destroy_కిటికీ_Framebuffer;
    device->Get_కిటికీ_కొలత_లోపల_Pixels = DOSVESA_Get_కిటికీ_కొలత_లోపల_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_DOSVESA
