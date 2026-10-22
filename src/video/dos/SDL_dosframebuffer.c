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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

#include "../../SDL_properties_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../SDL_sysvideo.h"
#include "SDL_dosframebuffer_c.h"
#include "SDL_dosmodes.h"
#include "SDL_dosmouse.h"
#include "SDL_dosvideo.h"

#include <pc.h>           // for inportb, outportb
#include <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#define DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
typedef sa_nracanaa DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool direct_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    puur_naa_nka vram_pitch;
    puur_naa_nka vram_w;
    puur_naa_nka vram_h;
    puur_naa_nka bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_bytes; // bank granularity in bytes
    Uint32 win_size_bytes; // bank window size in bytes
    Uint32 win_base;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    puur_naa_nka src_pitch;      // == surface->pitch
    Uint32 fb_size;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_match; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

static DOSFramebufferState fb_state;

// Convert cursor to the current format.
static SDL_Surface *GetConvertedCursorSurface(SDL_CursorData *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    ᬬᬾᬦ᭄ (!pal) {
        ᬯᬮᬶ NULL;
    }

    Uint32 pal_version = pal ? pal->version : 0;

    ᬬᬾᬦ᭄ (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_version == pal_version) {
        ᬯᬮᬶ curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = NULL;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    puur_naa_nka w = src->w;
    puur_naa_nka h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    ᬬᬾᬦ᭄ (!conv) {
        ᬯᬮᬶ NULL;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    ᬬᬾᬦ᭄ (conv_pal) {
        SDL_SetPaletteColors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool used[256];
    SDL_zeroa(used);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, NULL, conv, NULL);
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    for (puur_naa_nka y = 0; y < h; y++) {
        const Uint32 *srcrow = (const Uint32 *)((const Uint8 *)src->pixels + y * src->pitch);
        const Uint8 *convrow = (const Uint8 *)conv->pixels + y * conv->pitch;
        for (puur_naa_nka x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ᬬᬾᬦ᭄ (srcA > 0) {
                used[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    for (puur_naa_nka i = 0; i < 256; i++) {
        ᬬᬾᬦ᭄ (!used[i]) {
            colorkey = (Uint32)i;
            bha_nga;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    for (puur_naa_nka y = 0; y < h; y++) {
        const Uint32 *srcrow = (const Uint32 *)((const Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        for (puur_naa_nka x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ᬬᬾᬦ᭄ (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_SetSurfaceColorKey(conv, true, colorkey);
    SDL_SetSurfaceBlendMode(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_version = pal_version;
    ᬯᬮᬶ conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
void DOSVESA_InvalidateCachedFramebuffer(void)
{
    fb_state.direct_fb = false;
    fb_state.vram_ptr = NULL;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = NULL;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
static SDL_Surface *CreateSystemSurface(SDL_VideoData *data, puur_naa_nka w, puur_naa_nka h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ᬬᬾᬦ᭄ (!surface) {
        ᬯᬮᬶ NULL;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    ᬬᬾᬦ᭄ (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ᬬᬾᬦ᭄ (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            for (puur_naa_nka i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_SetPaletteColors(palette, black, 0, 256);
        }
        data->palette_version = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_INDEX, 0);
        for (puur_naa_nka i = 0; i < 256; i++) {
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
        }
    }

    ᬯᬮᬶ surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
static bool CreateNormalFramebuffer(SDL_VideoDevice *device, SDL_Window *window,
                                    SDL_PixelFormat *format, void **pixels, puur_naa_nka *pitch)
{
    SDL_VideoData *data = device->internal;
    const SDL_DisplayMode *mode = &data->current_mode;
    const SDL_DisplayModeData *mdata = mode->internal;
    const SDL_PixelFormat surface_format = mode->format;
    puur_naa_nka w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
    ᬬᬾᬦ᭄ (!surface) {
        ᬯᬮᬶ false;
    }

    SDL_Surface *lfb_surface = NULL;

    ᬬᬾᬦ᭄ (!data->banked_mode) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        puur_naa_nka back_page = data->page_flip_available ? (1 - data->current_page) : 0;
        void *lfb_pixels = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
        lfb_surface = SDL_CreateSurfaceFrom(mode->w, mode->h, surface_format, lfb_pixels, mdata->pitch);
        ᬬᬾᬦ᭄ (!lfb_surface) {
            SDL_DestroySurface(surface);
            ᬯᬮᬶ false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        ᬬᬾᬦ᭄ (src_palette) {
            SDL_SetSurfacePalette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    ᬬᬾᬦ᭄ (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ᬯᬮᬶ true;
}

bool DOSVESA_CreateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, SDL_PixelFormat *format, void **pixels, puur_naa_nka *pitch)
{
    SDL_zero(fb_state);

    SDL_VideoData *data = device->internal;
    const SDL_DisplayMode *mode = &data->current_mode;
    const SDL_DisplayModeData *mdata = mode->internal;
    const SDL_PixelFormat surface_format = mode->format;
    puur_naa_nka w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    ᬬᬾᬦ᭄ (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_DIRECT_FRAMEBUFFER, false)) {
        puur_naa_nka vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        ᬬᬾᬦ᭄ (mdata->win_a_segment && mdata->win_size > 0 &&
            (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (!data->banked_mode && data->mapping.size) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        ᬬᬾᬦ᭄ (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
            ᬬᬾᬦ᭄ (!surface) {
                ᬯᬮᬶ false;
            }

            SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.direct_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_size = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_match = (surface->pitch == vram_pitch);

            // Prefer dosmemput via the banked VGA window (0xA0000). Real
            // hardware testing shows dosmemput is significantly faster
            // than nearptr writes to DPMI-mapped LFB, even with bank
            // switching overhead at higher resolutions.
            //
            // The banked window always maps to page 0, so page flipping is
            // not possible through this path. We accept tearing: the app
            // opted into the direct-FB hint for maximum throughput, and
            // games like Quake never used page flipping for their software
            // renderers anyway.
            ᬬᬾᬦ᭄ (mdata->win_a_segment && mdata->win_size > 0 &&
                (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_bytes = (Uint32)mdata->win_size * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = NULL;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_base = fb_state.vram_phys;
                fb_state.win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_size_bytes = win_bytes;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_size > win_bytes);
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (!data->banked_mode && data->mapping.size) {
                // Fallback: nearptr to LFB.
                puur_naa_nka back_page = data->page_flip_available ? (1 - data->current_page) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } ᬮᬶᬬ {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                ᬯᬮᬶ CreateNormalFramebuffer(device, window, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            ᬯᬮᬶ true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    ᬯᬮᬶ CreateNormalFramebuffer(device, window, format, pixels, pitch);
}

bool DOSVESA_SetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, puur_naa_nka vsync)
{
    ᬬᬾᬦ᭄ (vsync < 0) {
        ᬯᬮᬶ SDL_SetError("Unsupported vsync type");
    }
    SDL_WindowData *data = window->internal;
    data->framebuffer_vsync = vsync;
    ᬯᬮᬶ true;
}

bool DOSVESA_GetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, puur_naa_nka *vsync)
{
    ᬬᬾᬦ᭄ (vsync) {
        SDL_WindowData *data = window->internal;
        *vsync = data->framebuffer_vsync;
    }
    ᬯᬮᬶ true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE void SwitchBank(puur_naa_nka bank, puur_naa_nka *current_bank, Uint32 win_func_ptr)
{
    ᬬᬾᬦ᭄ (bank == *current_bank) {
        ᬯᬮᬶ;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    ᬬᬾᬦ᭄ (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } ᬮᬶᬬ {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE void BankedDosmemput(const Uint8 *src, Uint32 total_bytes, Uint32 dst_offset,
                                      Uint32 win_gran_bytes, Uint32 win_size_bytes,
                                      Uint32 win_base, Uint32 win_func_ptr,
                                      puur_naa_nka *current_bank)
{
    Uint32 src_off = 0;
    ᬲᭂᬤᭂᬮ (total_bytes > 0) {
        puur_naa_nka bank = (puur_naa_nka)(dst_offset / win_gran_bytes);
        Uint32 off_in_win = dst_offset % win_gran_bytes;
        Uint32 avail = win_size_bytes - off_in_win;
        Uint32 n = total_bytes;
        ᬬᬾᬦ᭄ (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_base + off_in_win);
        src_off += n;
        dst_offset += n;
        total_bytes -= n;
    }
}

// Bank-switched copy of a rectangular region from a system RAM surface to the
// VGA banked window.  `src_rect` is in source-surface coordinates; `dst_x` and
// `dst_y` give the top-left of the *surface's* position on screen (the
// centering offset).  The routine handles bank boundaries correctly even when a
// scanline spans two banks.
//
// `current_bank` is an in/out parameter so that consecutive calls (one per dirty
// rect) can avoid redundant bank switches when rects happen to fall in the same
// bank.  Initialise it to -1 before the first call.
static void BankedFramebufferCopyRect(const SDL_DisplayModeData *mdata,
                                      const SDL_Surface *src,
                                      const SDL_Rect *src_rect,
                                      puur_naa_nka dst_x, puur_naa_nka dst_y,
                                      Uint32 win_gran_bytes,
                                      Uint32 win_size_bytes,
                                      Uint32 win_base,
                                      puur_naa_nka *current_bank,
                                      Uint32 win_func_ptr)
{
    const Uint16 dst_pitch = mdata->pitch;
    const puur_naa_nka bytes_per_pixel = SDL_BYTESPERPIXEL(src->format);
    const puur_naa_nka row_bytes = src_rect->w * bytes_per_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    ᬬᬾᬦ᭄ (row_bytes == src->pitch && row_bytes == dst_pitch) {
        const Uint8 *src_data = (const Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_data, (Uint32)(row_bytes * src_rect->h), dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
        ᬯᬮᬶ;
    }

    for (puur_naa_nka y = 0; y < src_rect->h; y++) {
        const Uint8 *src_row = (const Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_row, (Uint32)row_bytes, dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
    }
}

static void WaitForVBlank(void)
{
    ᬲᭂᬤᭂᬮ (inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    ᬲᭂᬤᭂᬮ (!(inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

static void ProgramVGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_INDEX, 0);
    for (puur_naa_nka i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_DATA, palette->colors[i].r >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].g >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_UpdateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, const SDL_Rect *rects, puur_naa_nka numrects)
{
    SDL_VideoData *vdata = device->internal;

    // ===================================================================
    //  Direct-FB fast path: copy system-RAM to VRAM, program palette,
    //  optionally page-flip. No cursor compositing, no SDL_BlitSurface.
    //
    //  This path prefers banked dosmemput (through the VGA window at
    //  0xA0000) over nearptr writes to the DPMI-mapped LFB. Real
    //  hardware testing on multiple NVIDIA cards showed dosmemput is
    //  significantly faster, even with bank-switching overhead at
    //  higher resolutions. The nearptr LFB path is only used as a
    // fallback if no usable banked window is available.
    // ===================================================================
    ᬬᬾᬦ᭄ (fb_state.direct_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        ᬬᬾᬦ᭄ (window->surface) {
            SDL_Palette *pal = window->surface->palette;
            ᬬᬾᬦ᭄ (pal && pal->version != vdata->palette_version) {
                vdata->palette_version = pal->version;
                ProgramVGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        ᬬᬾᬦ᭄ (numrects <= 0) {
            ᬯᬮᬶ true;
        }

        ᬬᬾᬦ᭄ (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            const puur_naa_nka src_pitch = fb_state.src_pitch;
            const puur_naa_nka dst_pitch = fb_state.vram_pitch;
            const Uint8 *pixels = fb_state.pixels;

            ᬬᬾᬦ᭄ (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                ᬬᬾᬦ᭄ (fb_state.pitches_match) {
                    dosmemput(pixels, fb_state.fb_size, fb_state.vram_phys);
                } ᬮᬶᬬ {
                    for (puur_naa_nka i = 0; i < numrects; i++) {
                        puur_naa_nka rx = rects[i].x, ry = rects[i].y;
                        puur_naa_nka rw = rects[i].w, rh = rects[i].h;
                        ᬬᬾᬦ᭄ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ᬬᬾᬦ᭄ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ᬬᬾᬦ᭄ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ᬬᬾᬦ᭄ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ᬬᬾᬦ᭄ (rw <= 0 || rh <= 0) {
                            continue;
                        }
                        const puur_naa_nka bx = rx * fb_state.bpp;
                        const puur_naa_nka bw = rw * fb_state.bpp;
                        const Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        for (puur_naa_nka row = 0; row < rh; row++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } ᬮᬶᬬ {
                // Multi-bank: bank-switch as needed.
                const Uint32 gran = fb_state.win_gran_bytes;
                const Uint32 wsize = fb_state.win_size_bytes;
                const Uint32 wbase = fb_state.win_base;
                const Uint32 wfunc = fb_state.win_func_ptr;
                puur_naa_nka current_bank = -1;

                ᬬᬾᬦ᭄ (fb_state.pitches_match) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_size, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } ᬮᬶᬬ {
                    // Per-rect with bank switching.
                    for (puur_naa_nka i = 0; i < numrects; i++) {
                        puur_naa_nka rx = rects[i].x, ry = rects[i].y;
                        puur_naa_nka rw = rects[i].w, rh = rects[i].h;
                        ᬬᬾᬦ᭄ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ᬬᬾᬦ᭄ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ᬬᬾᬦ᭄ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ᬬᬾᬦ᭄ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ᬬᬾᬦ᭄ (rw <= 0 || rh <= 0) {
                            continue;
                        }
                        const puur_naa_nka bx = rx * fb_state.bpp;
                        const puur_naa_nka bw = rw * fb_state.bpp;

                        for (puur_naa_nka row = 0; row < rh; row++) {
                            const Uint8 *sp = pixels + (ry + row) * src_pitch + bx;
                            Uint32 dst_offset = (Uint32)(ry + row) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_offset,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } ᬮᬶᬬ {
            // nearptr path (LFB fallback)
            ᬬᬾᬦ᭄ (fb_state.pitches_match) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_size);
            } ᬮᬶᬬ {
                const puur_naa_nka bpp = fb_state.bpp;
                const puur_naa_nka src_pitch = fb_state.src_pitch;
                const puur_naa_nka dst_pitch = fb_state.vram_pitch;
                const Uint8 *pixels = fb_state.pixels;

                for (puur_naa_nka i = 0; i < numrects; i++) {
                    puur_naa_nka rx = rects[i].x, ry = rects[i].y;
                    puur_naa_nka rw = rects[i].w, rh = rects[i].h;
                    ᬬᬾᬦ᭄ (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    ᬬᬾᬦ᭄ (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    ᬬᬾᬦ᭄ (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    ᬬᬾᬦ᭄ (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    ᬬᬾᬦ᭄ (rw <= 0 || rh <= 0) {
                        continue;
                    }
                    const puur_naa_nka bw = rw * bpp;
                    const Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    for (puur_naa_nka row = 0; row < rh; row++) {
                        SDL_memcpy(dp, sp, bw);
                        sp += src_pitch;
                        dp += dst_pitch;
                    }
                }
            }
        }

        // Page flipping is only used with the nearptr LFB path. The banked
        // dosmemput path always writes to page 0 (the visible page) and
        // accepts tearing, avoiding a BIOS call.
        ᬬᬾᬦ᭄ (!fb_state.use_dosmemput && vdata->page_flip_available) {
            const SDL_DisplayModeData *mdata = vdata->current_mode.internal;
            puur_naa_nka back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            puur_naa_nka new_back = 1 - vdata->current_page;
            fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        }

        ᬯᬮᬶ true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    ᬬᬾᬦ᭄ (!src) {
        src = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DOS_SURFACE, NULL);
    }
    ᬬᬾᬦ᭄ (!src) {
        ᬯᬮᬶ SDL_SetError("Couldn't find DOS surface for window");
    }

    const SDL_DisplayModeData *mdata = vdata->current_mode.internal;
    SDL_WindowData *windata = window->internal;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = NULL;
    bool dac_needs_update = false;

    ᬬᬾᬦ᭄ (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = window->surface ? SDL_GetSurfacePalette(window->surface) : NULL;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        ᬬᬾᬦ᭄ (win_palette && src_palette && win_palette != src_palette &&
            win_palette->version != src_palette->version) {
            SDL_SetPaletteColors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            ᬬᬾᬦ᭄ (!vdata->banked_mode && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                ᬬᬾᬦ᭄ (dst_palette && dst_palette != src_palette) {
                    SDL_SetPaletteColors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        ᬬᬾᬦ᭄ (dac_palette && dac_palette->version != vdata->palette_version) {
            dac_needs_update = true;
        }
    }

    ᬬᬾᬦ᭄ (vdata->banked_mode) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        const puur_naa_nka dst_x = ((puur_naa_nka)mdata->w - src->w) / 2;
        const puur_naa_nka dst_y = ((puur_naa_nka)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = NULL;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = NULL;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : NULL;
        ᬬᬾᬦ᭄ (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        ᬬᬾᬦ᭄ (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            ᬬᬾᬦ᭄ (cursor) {
                cursorrect.x = SDL_clamp((puur_naa_nka)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = SDL_clamp((puur_naa_nka)mouse->y, 0, window->h) - cur->internal->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                ᬬᬾᬦ᭄ (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                ᬬᬾᬦ᭄ (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                ᬬᬾᬦ᭄ (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                ᬬᬾᬦ᭄ (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                ᬬᬾᬦ᭄ (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    ᬬᬾᬦ᭄ (cursor_save) {
                        ᬬᬾᬦ᭄ (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            ᬬᬾᬦ᭄ (sp) {
                                SDL_SetSurfacePalette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, NULL);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, NULL, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        const puur_naa_nka vsync_interval = windata->framebuffer_vsync;
        ᬬᬾᬦ᭄ (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        ᬬᬾᬦ᭄ (dac_needs_update) {
            vdata->palette_version = dac_palette->version;
            ProgramVGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        const Uint32 win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
        const Uint32 win_size_bytes = (Uint32)mdata->win_size * 1024;
        const Uint32 win_base = (Uint32)mdata->win_a_segment << 4;
        puur_naa_nka current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        for (puur_naa_nka r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            ᬬᬾᬦ᭄ (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            ᬬᬾᬦ᭄ (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            ᬬᬾᬦ᭄ (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            ᬬᬾᬦ᭄ (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            ᬬᬾᬦ᭄ (rect.w <= 0 || rect.h <= 0) {
                continue;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            ᬬᬾᬦ᭄ (have_cursor_rect && !cursor_covered) {
                ᬬᬾᬦ᭄ (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        ᬬᬾᬦ᭄ (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        ᬬᬾᬦ᭄ (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, NULL, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } ᬮᬶᬬ {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        ᬬᬾᬦ᭄ (!dst) {
            ᬯᬮᬶ SDL_SetError("Couldn't find VESA linear framebuffer surface for window");
        }

        const SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = NULL;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : NULL;
        ᬬᬾᬦ᭄ (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        ᬬᬾᬦ᭄ (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            ᬬᬾᬦ᭄ (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((puur_naa_nka)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((puur_naa_nka)mouse->y, 0, window->h) - cur->internal->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        ᬬᬾᬦ᭄ (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            const Uint8 *sp = (const Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            ᬬᬾᬦ᭄ (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } ᬮᬶᬬ {
                for (puur_naa_nka row = 0; row < dstrect.h; row++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } ᬮᬶᬬ {
            // Blit to the back page (or the only page, if no page-flipping)
            ᬬᬾᬦ᭄ (!SDL_BlitSurface(src, NULL, dst, &dstrect)) {
                ᬯᬮᬶ false;
            }
        }

        ᬬᬾᬦ᭄ (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, dst);
            ᬬᬾᬦ᭄ (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, NULL, dst, &cursorrect)) {
                ᬯᬮᬶ false;
            }
        }

        ᬬᬾᬦ᭄ (vdata->page_flip_available) {
            // Page-flip with optional vsync.
            const puur_naa_nka vsync_interval = windata->framebuffer_vsync;
            puur_naa_nka back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            ᬬᬾᬦ᭄ (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            ᬬᬾᬦ᭄ (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }

            // Flip: make the back page (which we just drew to) the visible page.
            // Always use subfunction 0x0080 (set display start, don't wait) —
            // vsync is controlled by our manual vblank wait above.
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0; // first pixel in scan line
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            // Update LFB surface to point at the new back page (the old front page)
            puur_naa_nka new_back = 1 - vdata->current_page;
            dst->pixels = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        } ᬮᬶᬬ {
            // No page-flipping: wait for vsync, then update DAC atomically
            const puur_naa_nka vsync_interval = windata->framebuffer_vsync;
            ᬬᬾᬦ᭄ (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            ᬬᬾᬦ᭄ (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }
        }
    }

    ᬯᬮᬶ true;
}

void DOSVESA_DestroyWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (void)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_GetWindowProperties(window), DOS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DOSVESA
