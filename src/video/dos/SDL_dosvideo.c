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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../SDL_sysvideo.h"

// DOS declarations
#समावेश "SDL_dosevents_c.h"
#समावेश "SDL_dosframebuffer_c.h"
#समावेश "SDL_dosmodes.h"
#समावेश "SDL_dosmouse.h"
#समावेश "SDL_dosvideo.h"

// Apply a display mode for a window: set the hardware mode, store it as
// the window's requested fullscreen mode, and update window dimensions.
अटल व्योम DOSVESA_ApplyModeForWindow(SDL_VideoDisplay *display, SDL_Window *window, SDL_DisplayMode *mode)
{
    SDL_SetDisplayModeForDisplay(display, mode);

    अगर (mode) {
        SDL_copyp(&window->requested_fullscreen_mode, mode);
        window->floating.w = window->windowed.w = window->w = mode->w;
        window->floating.h = window->windowed.h = window->h = mode->h;
    }
}

अटल bool DOSVESA_CreateWindow(SDL_VideoDevice *device, SDL_Window *window, SDL_PropertiesID create_props)
{
    // Allocate window internal data
    SDL_Window_तथ्य *wdata = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!wdata) {
        वापस false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    // One window, it always has focus
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    {
        SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
        अगर (!display) {
            वापस true;
        }

        SDL_DisplayMode *mode = शून्य;
        SDL_DisplayMode closest;
        अगर (window->requested_fullscreen_mode.internal) {
            // App explicitly set a fullscreen mode.
            mode = &window->requested_fullscreen_mode;
        } अन्यथा अगर (window->floating.w > 0 && window->floating.h > 0) {
            अगर (SDL_GetClosestFullscreenDisplayMode(display->id, window->floating.w, window->floating.h, 0.0f, false, &closest)) {
                mode = &closest;
            }
        }
        अगर (!mode) {
            वापस true;
        }

        DOSVESA_ApplyModeForWindow(display, window, mode);
    }

    वापस true;
}

अटल व्योम DOSVESA_Set_Window_आकार(SDL_VideoDevice *device, SDL_Window *window)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    अगर (!display) {
        वापस;
    }

    SDL_DisplayMode closest;
    SDL_DisplayMode *mode = शून्य;
    अगर (SDL_GetClosestFullscreenDisplayMode(display->id, window->floating.w, window->floating.h, 0.0f, false, &closest)) {
        mode = &closest;
    }

    DOSVESA_ApplyModeForWindow(display, window, mode);

    // Invalidate the framebuffer so it gets recreated at the new size.
    window->surface_valid = false;
}

// Critical for performance: this function must be implemented and as simple
// as possible to avoid slowdowns during calls to SDL_UpdateWindowSurface().
// A few pointer dereferences here can cost 10% of performance easily.
अटल व्योम DOSVESA_Get_Window_आकार_In_Pixels(SDL_VideoDevice *device, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    *w = window->w;
    *h = window->h;
}

अटल व्योम DOSVESA_DestroyWindow(SDL_VideoDevice *device, SDL_Window *window)
{
    SDL_free(window->internal);
    window->internal = शून्य;
}

अटल bool DOSVESA_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;

    // Verify that the "fat DS" nearptr trick is active. Without it,
    // DOS_PhysicalToLinear() produces garbage pointers and we crash.
    // SDL_RunApp() enables this automatically; if the app defined
    // SDL_MAIN_HANDLED it must call __djgpp_nearptr_enable() itself.
    अगर (__djgpp_conventional_base == 0) {
        वापस SDL_SetError("DOSVESA: __djgpp_nearptr_enable() was not called. "
                            "Did you define SDL_MAIN_HANDLED without enabling the fat DS trick?");
    }

    // We are probably in text mode at startup, so we don't have a real "desktop mode" atm.
    // Pick something _super_ conservative for now.
    //  We'll change to a real video mode after enumerating available modes below.
    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_RGB565;
    mode.w = 320;
    mode.h = 200;

    SDL_VideoDisplay vdisplay;
    SDL_zero(vdisplay);
    SDL_memcpy(&vdisplay.desktop_mode, &mode, माप(mode));
    vdisplay.name = (अक्षर *)DOSVESA_GetGPUName();
    SDL_DisplayID display_id = SDL_AddVideoDisplay(&vdisplay, false);
    अगर (!display_id) {
        वापस false;
    }

    SDL_zero(तथ्य->current_mode);

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(display_id);
    अगर (!display || !DOSVESA_GetDisplayModes(device, display)) {
        वापस false;
    }

    // Pick a sensible default desktop mode. This determines the window
    // size for FULLSCREEN_ONLY. Target 640x480 as a safe default; apps
    // that want something else should call SDL_SetWindowFullscreenMode.
    {
        SDL_DisplayMode closest;
        अगर (SDL_GetClosestFullscreenDisplayMode(display_id, 640, 480, 0.0f, false, &closest)) {
            // Deep-copy the mode into desktop_mode. We need our own
            // internal allocation because SDL frees desktop_mode.internal
            // and fullscreen_modes[].internal independently.
            SDL_Display_Mode_तथ्य *desktop_internal = (SDL_Display_Mode_तथ्य *)SDL_malloc(माप(*desktop_internal));
            अगर (desktop_internal) {
                SDL_copyp(desktop_internal, (स्थिर SDL_Display_Mode_तथ्य *)closest.internal);
                SDL_copyp(&display->desktop_mode, &closest);
                display->desktop_mode.internal = desktop_internal;
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
        अगर (regs.x.ax == 0x004F) {
            तथ्य->original_vbe_mode = regs.x.bx;
        } अन्यथा {
            तथ्य->original_vbe_mode = 0x03; // assume text mode
        }

        // Save VBE state via VBE function 0x4F04 so we can do a full restore later.
        // Step 1: query the required buffer size (subfunction 0x00).
        SDL_zero(regs);
        regs.x.ax = 0x4F04;
        regs.x.dx = 0x00; // subfunction 0: get state buffer size
        regs.x.cx = 0x0F; // save all state: hardware + BIOS data + DAC + SVGA
        __dpmi_int(0x10, &regs);
        अगर (regs.x.ax == 0x004F) {
            // regs.x.bx contains size in 64-byte blocks.
            Uint32 state_आकार = (Uint32)regs.x.bx * 64;
            _go32_dpmi_seginfo state_seginfo;
            व्योम *state_buf = DOS_AllocateConventionalMemory(state_आकार, &state_seginfo);
            अगर (state_buf) {
                // Step 2: save state (subfunction 0x01) into conventional memory buffer.
                SDL_zero(regs);
                regs.x.ax = 0x4F04;
                regs.x.dx = 0x01; // subfunction 1: save state
                regs.x.cx = 0x0F; // all state
                regs.x.es = DOS_LinearToPhysical(state_buf) / 16;
                regs.x.bx = DOS_LinearToPhysical(state_buf) & 0xF;
                __dpmi_int(0x10, &regs);
                अगर (regs.x.ax == 0x004F) {
                    // Copy state from conventional memory to our heap so we
                    // can free the low-memory buffer now.
                    तथ्य->vbe_state_बफर = SDL_malloc(state_आकार);
                    अगर (तथ्य->vbe_state_बफर) {
                        SDL_memcpy(तथ्य->vbe_state_बफर, state_buf, state_आकार);
                        तथ्य->vbe_state_बफर_आकार = state_आकार;
                    }
                }
                DOS_FreeConventionalMemory(&state_seginfo);
            }
        }
    }

    DOSVESA_InitMouse(device);
    DOSVESA_InitKeyboard(device);

    वापस true;
}

अटल व्योम DOSVESA_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;

    अगर (तथ्य->mapping.आकार) {
        __dpmi_free_physical_address_mapping(&तथ्य->mapping); // dump existing video mapping.
        SDL_zero(तथ्य->mapping);
    }

    // Restore saved VBE state if available.
    अगर (तथ्य->vbe_state_बफर && तथ्य->vbe_state_बफर_आकार > 0) {
        _go32_dpmi_seginfo restore_seginfo;
        व्योम *restore_buf = DOS_AllocateConventionalMemory(तथ्य->vbe_state_बफर_आकार, &restore_seginfo);
        अगर (restore_buf) {
            SDL_memcpy(restore_buf, तथ्य->vbe_state_बफर, तथ्य->vbe_state_बफर_आकार);
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F04;
            regs.x.dx = 0x02; // subfunction 2: restore state
            regs.x.cx = 0x0F; // all state
            regs.x.es = DOS_LinearToPhysical(restore_buf) / 16;
            regs.x.bx = DOS_LinearToPhysical(restore_buf) & 0xF;
            __dpmi_int(0x10, &regs);
            DOS_FreeConventionalMemory(&restore_seginfo);
        }
        SDL_free(तथ्य->vbe_state_बफर);
        तथ्य->vbe_state_बफर = शून्य;
        तथ्य->vbe_state_बफर_आकार = 0;
    }

    // Restore the original video mode.
    {
        __dpmi_regs regs;
        bool restored = false;

        // Try VBE mode restore first (only works on VBE 1.2+).
        अगर (तथ्य->original_vbe_mode != 0x03) {
            SDL_zero(regs);
            regs.x.ax = 0x4F02;
            regs.x.bx = तथ्य->original_vbe_mode;
            __dpmi_int(0x10, &regs);
            restored = (regs.x.ax == 0x004F);
        }

        // Fall back to standard BIOS text mode (works on any VGA).
        अगर (!restored) {
            SDL_zero(regs);
            regs.x.ax = 0x0003;
            __dpmi_int(0x10, &regs);
        }
    }

    SDL_zero(तथ्य->current_mode);

    DOSVESA_QuitMouse(device);
    DOSVESA_QuitKeyboard(device);
}

अटल व्योम DOSVESA_Destroy(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;
    SDL_free(तथ्य->vbe_state_बफर);
    SDL_free(device->internal);
    SDL_free(device);
    DOSVESA_FreeVESAInfo();
}

अटल SDL_VideoDevice *DOSVESA_CreateDevice(व्योम)
{
    अगर (!DOSVESA_SupportsVESA()) {
        वापस शून्य;
    }

    SDL_VideoDevice *device;
    SDL_Video_तथ्य *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal data
    phdata = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!phdata) {
        SDL_free(device);
        वापस शून्य;
    }

    device->internal = phdata;
    device->मुक्त = DOSVESA_Destroy;
    device->VideoInit = DOSVESA_VideoInit;
    device->VideoQuit = DOSVESA_VideoQuit;
    device->GetDisplayModes = DOSVESA_GetDisplayModes;
    device->SetDisplayMode = DOSVESA_SetDisplayMode;
    device->CreateSDLWindow = DOSVESA_CreateWindow;
    device->Set_Window_आकार = DOSVESA_Set_Window_आकार;
    device->DestroyWindow = DOSVESA_DestroyWindow;
    device->CreateWindowFramebuffer = DOSVESA_CreateWindowFramebuffer;
    device->SetWindowFramebufferVSync = DOSVESA_SetWindowFramebufferVSync;
    device->GetWindowFramebufferVSync = DOSVESA_GetWindowFramebufferVSync;
    device->UpdateWindowFramebuffer = DOSVESA_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = DOSVESA_DestroyWindowFramebuffer;
    device->Get_Window_आकार_In_Pixels = DOSVESA_Get_Window_आकार_In_Pixels;
    device->PumpEvents = DOSVESA_PumpEvents;
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    वापस device;
}

VideoBootStrap DOSVESA_bootstrap = {
    "vesa",
    "DOS VESA Video Driver",
    DOSVESA_CreateDevice,
    शून्य, // no ShowMessageBox implementation
    false
};

#पूर्ण_अगर // SDL_VIDEO_DRIVER_DOSVESA
