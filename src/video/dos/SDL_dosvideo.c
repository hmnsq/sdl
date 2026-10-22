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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"

// DOS declarations
#अन्तर्भाव "SDL_dosevents_c.h"
#अन्तर्भाव "SDL_dosframebuffer_c.h"
#अन्तर्भाव "SDL_dosmodes.h"
#अन्तर्भाव "SDL_dosmouse.h"
#अन्तर्भाव "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
स्थिर शून्य DOSVESA_Apply_बहुलकम्_For_गवाक्षः(SDL_VideoDisplay *display, SDL_गवाक्षः *गवाक्षः, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_समुच्चयः_Display_बहुलकम्_For_Display(display, बहुलकम्);

    यदि (बहुलकम्) {
        SDL_copyp(&गवाक्षः->requested_fullscreen_बहुलकम्, बहुलकम्);
        गवाक्षः->floating.w = गवाक्षः->windowed.w = गवाक्षः->w = बहुलकम्->w;
        गवाक्षः->floating.h = गवाक्षः->windowed.h = गवाक्षः->h = बहुलकम्->h;
    }
}

स्थिर bool DOSVESA_Create_गवाक्षः(SDL_VideoDevice *device, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_गवाक्षः_दत्त *wdata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!wdata) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = wdata;

    // One window, it always has focus
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    {
        SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
        यदि (!display) {
            प्रत्यागम true;
        }

        SDL_Display_बहुलकम् *बहुलकम् = रिक्त;
        SDL_Display_बहुलकम् closest;
        यदि (गवाक्षः->requested_fullscreen_बहुलकम्.आन्तरिकम्) {
            // App explicitly set a fullscreen mode.
            बहुलकम् = &गवाक्षः->requested_fullscreen_बहुलकम्;
        } अन्यथा यदि (गवाक्षः->floating.w > 0 && गवाक्षः->floating.h > 0) {
            यदि (SDL_Get_Closest_Fullscreen_Display_बहुलकम्(display->id, गवाक्षः->floating.w, गवाक्षः->floating.h, 0.0f, false, &closest)) {
                बहुलकम् = &closest;
            }
        }
        यदि (!बहुलकम्) {
            प्रत्यागम true;
        }

        DOSVESA_Apply_बहुलकम्_For_गवाक्षः(display, गवाक्षः, बहुलकम्);
    }

    प्रत्यागम true;
}

स्थिर शून्य DOSVESA_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *device, SDL_गवाक्षः *गवाक्षः)
{
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    यदि (!display) {
        प्रत्यागम;
    }

    SDL_Display_बहुलकम् closest;
    SDL_Display_बहुलकम् *बहुलकम् = रिक्त;
    यदि (SDL_Get_Closest_Fullscreen_Display_बहुलकम्(display->id, गवाक्षः->floating.w, गवाक्षः->floating.h, 0.0f, false, &closest)) {
        बहुलकम् = &closest;
    }

    DOSVESA_Apply_बहुलकम्_For_गवाक्षः(display, गवाक्षः, बहुलकम्);

    // Invalidate the framebuffer so it gets recreated at the new size.
    गवाक्षः->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
स्थिर शून्य DOSVESA_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *device, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    *w = गवाक्षः->w;
    *h = गवाक्षः->h;
}

स्थिर शून्य DOSVESA_Destroy_गवाक्षः(SDL_VideoDevice *device, SDL_गवाक्षः *गवाक्षः)
{
    SDL_free(गवाक्षः->आन्तरिकम्);
    गवाक्षः->आन्तरिकम् = रिक्त;
}

स्थिर bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    यदि (__djgpp_conventional_base == 0) {
        प्रत्यागम SDL_समुच्चयः_Error("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_zero(बहुलकम्);
    बहुलकम्.format = SDL_PIXELFORMAT_RGB565;
    बहुलकम्.w = 320;
    बहुलकम्.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_बहुलकम्, &बहुलकम्, परिमाण(बहुलकम्));
    vdisplay.name = (वर्ण *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_सङ्कलय_Video_Display(&vdisplay, false);
    यदि (!display_id) {
        प्रत्यागम false;
    }

    SDL_zero(दत्त->current_बहुलकम्);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    यदि (!display || !DOSVESA_GetDisplayModes(device, display)) {
        प्रत्यागम false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_Display_बहुलकम् closest;
        यदि (SDL_Get_Closest_Fullscreen_Display_बहुलकम्(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_बहुलकम्_दत्त *desktop_आन्तरिकम् = (SDL_Display_बहुलकम्_दत्त *)SDL_malloc(परिमाण(*desktop_आन्तरिकम्));
            यदि (desktop_आन्तरिकम्) {
                SDL_copyp(desktop_आन्तरिकम्, (ध्रुव SDL_Display_बहुलकम्_दत्त *)closest.आन्तरिकम्);
                SDL_copyp(&display->desktop_बहुलकम्, &closest);
                display->desktop_बहुलकम्.आन्तरिकम् = desktop_आन्तरिकम्;
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
        यदि (regs.x.ax == 0x004F) {
            दत्त->original_vbe_बहुलकम् = regs.x.bx;
        } अन्यथा {
            दत्त->original_vbe_बहुलकम् = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        यदि (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_आकार = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            शून्य *state_buf = DOS_Allocate_Conventional_स्मृतिः(state_आकार, &state_seginfo);
            यदि (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_रैखिकम्_गन्तव्यम्_Physical(state_buf) / 16;
                regs.x.bx = DOS_रैखिकम्_गन्तव्यम्_Physical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                यदि (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    दत्त->vbe_state_बफर = SDL_malloc(state_आकार);
                    यदि (दत्त->vbe_state_बफर) {
                        SDL_memcpy(दत्त->vbe_state_बफर, state_buf, state_आकार);
                        दत्त->vbe_state_बफर_आकार = state_आकार;
                    }
                }
                DOS_Free_Conventional_स्मृतिः(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    प्रत्यागम true;
}

स्थिर शून्य DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;

    यदि (दत्त->mapping.आकार) {
        __dpmi_free_physical_address_mapping(&दत्त->mapping); // dump existing video mapping.
        SDL_zero(दत्त->mapping);
    }

    // Restore saved VBE state if available.
    यदि (दत्त->vbe_state_बफर && दत्त->vbe_state_बफर_आकार > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        शून्य *restore_buf = DOS_Allocate_Conventional_स्मृतिः(दत्त->vbe_state_बफर_आकार, &restore_seginfo);
        यदि (restore_buf) {
            SDL_memcpy(restore_buf, दत्त->vbe_state_बफर, दत्त->vbe_state_बफर_आकार);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_रैखिकम्_गन्तव्यम्_Physical(restore_buf) / 16;
            regs.x.bx = DOS_रैखिकम्_गन्तव्यम्_Physical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_Free_Conventional_स्मृतिः(&restore_seginfo);
        }
        SDL_free(दत्त->vbe_state_बफर);
        दत्त->vbe_state_बफर = रिक्त;
        दत्त->vbe_state_बफर_आकार = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        यदि (दत्त->original_vbe_बहुलकम् != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = दत्त->original_vbe_बहुलकम्;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        यदि (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(दत्त->current_बहुलकम्);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

स्थिर शून्य DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;
    SDL_free(दत्त->vbe_state_बफर);
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

स्थिर SDL_VideoDevice *DOSVESA_CreateDevice(शून्य)
{
    यदि (!DOSVESA_SupportsVESA()) {
        प्रत्यागम रिक्त;
    }

    SDL_VideoDevice *device;
    SDL_Video_दत्त *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = phdata;
    device->मुक्त = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = DOSVESA_समुच्चयः_Display_बहुलकम्;
    device->CreateSDLWindow = DOSVESA_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_आकार = DOSVESA_समुच्चयः_गवाक्षः_आकार;
    device->Destroy_गवाक्षः = DOSVESA_Destroy_गवाक्षः;
    device->Create_गवाक्षः_Framebuffer = DOSVESA_Create_गवाक्षः_Framebuffer;
    device->समुच्चयः_गवाक्षः_Framebuffer_VSync = DOSVESA_समुच्चयः_गवाक्षः_Framebuffer_VSync;
    device->Get_गवाक्षः_Framebuffer_VSync = DOSVESA_Get_गवाक्षः_Framebuffer_VSync;
    device->Update_गवाक्षः_Framebuffer = DOSVESA_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = DOSVESA_Destroy_गवाक्षः_Framebuffer;
    device->Get_गवाक्षः_आकार_अन्तर्_Pixels = DOSVESA_Get_गवाक्षः_आकार_अन्तर्_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

#यदि_अन्तः // SDL_VIDEO_DRIVER_DOSVESA
