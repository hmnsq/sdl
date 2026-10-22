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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_dosframebuffer_c.h"

// DOS declarations
#അന്തര്ഭാവ "SDL_dosmodes.h"
#അന്തര്ഭാവ "SDL_dosvideo.h"
#അന്തര്ഭാവ <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#define VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#define VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#define VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#define VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#define VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#define VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#define VBE_MEMMODEL_DIRECT_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#define VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#define VBE_MODELIST_END 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#define VGA_MODE_13H_SENTINEL 0xFFEE
#define VGA_MODE_13H_SEGMENT  0xA000

#pragma pack(തള്ളുക, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
തരനിർവചനം ഘടന SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 VideoModePtr; // segment:offset
    Uint16 TotalMemory;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 OemData[256];
} SDL_VESAHardwareInfo;

തരനിർവചനം ഘടന SDL_VESAModeHardwareInfo
{
    Uint16 ModeAttributes;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 WinSize;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 Bytes_Per_Scan_വരി;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XCharSize;
    Uint8 YCharSize;
    Uint8 സംഖ്യ_Of_Planes;
    Uint8 BitsPerPixel;
    Uint8 സംഖ്യ_Of_Banks;
    Uint8 MemoryModel;
    Uint8 BankSize;
    Uint8 സംഖ്യ_Of_Image_Pages;
    Uint8 Reserved_page;
    Uint8 RedMaskSize;
    Uint8 RedMaskPos;
    Uint8 GreenMaskSize;
    Uint8 GreenMaskPos;
    Uint8 BlueMaskSize;
    Uint8 BlueMaskPos;
    Uint8 ReservedMaskSize;
    Uint8 ReservedMaskPos;
    Uint8 DirectColorModeInfo;
    Uint32 PhysBasePtr;
    Uint32 OffScreenMemOffset;
    Uint16 OffScreenMemSize;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#pragma pack(എടുക്കുക)

തരനിർവചനം ഘടന SDL_VESAInfo
{
    Uint16 version;              // 0x200 == 2.0, etc.
    Uint32 total_memory;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *mode_list;           // copied out of conventional memory before freeing
    പൂർണ്ണസംഖ്യ അക്കം_modes;
    Uint16 oem_software_revision;
    അക്ഷരം *oem_string;
    അക്ഷരം *oem_vendor;
    അക്ഷരം *oem_product;
    അക്ഷരം *oem_revision;
} SDL_VESAInfo;

സ്ഥിതം SDL_VESAInfo *vesa_info = ശൂന്യ;

ശൂന്യം DOSVESA_FreeVESAInfo(ശൂന്യം)
{
    എങ്കിൽ (vesa_info) {
        SDL_free(vesa_info->mode_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_product);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = ശൂന്യ;
    }
}

സ്ഥിതം സ്ഥിരം SDL_VESAInfo *GetVESAInfo(ശൂന്യം)
{
    എങ്കിൽ (vesa_info) {
        തിരികെ vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_AllocateConventionalMemory(വലുപ്പം(*hwinfo), &hwinfo_seginfo);
    എങ്കിൽ (!hwinfo) {
        തിരികെ ശൂന്യ;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_LinearToPhysical(hwinfo) / 16;
    regs.x.di = DOS_LinearToPhysical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    എങ്കിൽ ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_SetError("VESA video not supported on this system");
    } അല്ലെങ്കിൽ {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, വലുപ്പം(*vesa_info));
        എങ്കിൽ (vesa_info) {
            vesa_info->version = hwinfo->VESAVersion;
            vesa_info->total_memory = ((Uint32)hwinfo->TotalMemory) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->VideoModePtr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_product = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                പൂർണ്ണസംഖ്യ എണ്ണം = 0;
                ആകുമ്പോൾ (DOS_PeekUint16(segoffset + എണ്ണം * വലുപ്പം(Uint16)) != VBE_MODELIST_END) {
                    എണ്ണം++;
                    എങ്കിൽ (എണ്ണം > 64)
                        നിർത്തുക; // sanity limit
                }
                vesa_info->അക്കം_modes = എണ്ണം;
                vesa_info->mode_list = (Uint16 *)SDL_malloc(എണ്ണം * വലുപ്പം(Uint16));
                എങ്കിൽ (vesa_info->mode_list) {
                    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം; i++) {
                        vesa_info->mode_list[i] = DOS_PeekUint16(segoffset + i * വലുപ്പം(Uint16));
                    }
                } അല്ലെങ്കിൽ {
                    vesa_info->അക്കം_modes = 0;
                }
            }
        }
    }

    DOS_FreeConventionalMemory(&hwinfo_seginfo);

    തിരികെ vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
സ്ഥിതം bool DetectVGA(ശൂന്യം)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    തിരികെ ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(ശൂന്യം)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    എങ്കിൽ (!DetectVGA()) {
        തിരികെ SDL_SetError("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (ശൂന്യം)GetVESAInfo();

    തിരികെ true;
}

സ്ഥിരം അക്ഷരം *DOSVESA_GetGPUName(ശൂന്യം)
{
    സ്ഥിരം SDL_VESAInfo *vinfo = GetVESAInfo();
    എങ്കിൽ (!vinfo) {
        തിരികെ "VGA";
    }

    എങ്കിൽ (vinfo->oem_product && *vinfo->oem_product) {
        തിരികെ vinfo->oem_product;
    }
    എങ്കിൽ (vinfo->oem_vendor && *vinfo->oem_vendor) {
        തിരികെ vinfo->oem_vendor;
    }
    എങ്കിൽ (vinfo->oem_string && *vinfo->oem_string) {
        തിരികെ vinfo->oem_string;
    }

    തിരികെ "VESA";
}

Uint32 DOSVESA_GetVESATotalMemory(ശൂന്യം)
{
    സ്ഥിരം SDL_VESAInfo *info = GetVESAInfo();
    തിരികെ info ? info->total_memory : 0;
}

സ്ഥിതം bool GetVESAModeInfo(Uint16 mode_id, SDL_DisplayModeData *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_AllocateConventionalMemory(വലുപ്പം(*hwinfo), &hwinfo_seginfo);
    എങ്കിൽ (!hwinfo) {
        തിരികെ false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_LinearToPhysical(hwinfo) / 16;
    regs.x.di = DOS_LinearToPhysical(hwinfo) & 0xF;
    regs.x.cx = mode_id;
    __dpmi_int(0x10, &regs);

    സ്ഥിരം bool retval = (regs.x.ax == 0x004F);
    എങ്കിൽ (retval) {
        SDL_zerop(info);
        info->mode_id = mode_id;
        info->attributes = hwinfo->ModeAttributes;
        info->pitch = hwinfo->Bytes_Per_Scan_വരി;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->അക്കം_planes = hwinfo->സംഖ്യ_Of_Planes;
        info->bpp = hwinfo->BitsPerPixel;
        info->memory_model = hwinfo->MemoryModel;
        info->അക്കം_image_pages = hwinfo->സംഖ്യ_Of_Image_Pages;
        info->red_mask_size = hwinfo->RedMaskSize;
        info->red_mask_pos = hwinfo->RedMaskPos;
        info->green_mask_size = hwinfo->GreenMaskSize;
        info->green_mask_pos = hwinfo->GreenMaskPos;
        info->blue_mask_size = hwinfo->BlueMaskSize;
        info->blue_mask_pos = hwinfo->BlueMaskPos;
        info->physical_base_addr = hwinfo->PhysBasePtr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->ModeAttributes & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_size = hwinfo->WinSize;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_attributes = hwinfo->WinAAttributes;
    }

    DOS_FreeConventionalMemory(&hwinfo_seginfo);

    തിരികെ retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    സ്ഥിരം SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    പൂർണ്ണസംഖ്യ അക്കം_vesa_modes = (vinfo && vinfo->version >= 0x102) ? vinfo->അക്കം_modes : 0;

    വേണ്ടി (പൂർണ്ണസംഖ്യ mi = 0; mi < അക്കം_vesa_modes; mi++) {
        സ്ഥിരം Uint16 modeid = vinfo->mode_list[mi];

        SDL_DisplayModeData info;
        എങ്കിൽ (!GetVESAModeInfo(modeid, &info)) {
            തുടരുക;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        എങ്കിൽ (info.bpp == 8 && info.w == 320 && info.h == 200) {
            തുടരുക;
        }

        എങ്കിൽ ((info.attributes & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            തുടരുക;
        }

        എങ്കിൽ (!(info.attributes & VBE_MODEATTR_LFB) && (info.win_a_attributes & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            തുടരുക;
        }

        എങ്കിൽ (info.അക്കം_planes != 1) {
            തുടരുക; // skip planar pixel layouts.
        } അല്ലെങ്കിൽ എങ്കിൽ (info.bpp < 8) {
            തുടരുക; // skip anything below 8-bit.
        } അല്ലെങ്കിൽ എങ്കിൽ (!info.w || !info.h) {
            തുടരുക; // zero-area display mode?!
        } അല്ലെങ്കിൽ എങ്കിൽ (!info.has_lfb && !info.win_granularity) {
            തുടരുക; // banked mode with zero granularity would cause division by zero.
        } അല്ലെങ്കിൽ എങ്കിൽ ((info.memory_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.memory_model != VBE_MEMMODEL_DIRECT_COLOR)) {
            തുടരുക; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        എങ്കിൽ (info.memory_model == VBE_MEMMODEL_PACKED_PIXEL) {
            തിരഞ്ഞെടുപ്പ് (info.bpp) {
            അവസ്ഥ 8:
                format = SDL_PIXELFORMAT_INDEX8;
                നിർത്തുക;
            അവസ്ഥ 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                നിർത്തുക;
            അവസ്ഥ 16:
                format = SDL_PIXELFORMAT_RGB565;
                നിർത്തുക;
            അവസ്ഥ 24:
                format = SDL_PIXELFORMAT_RGB24;
                നിർത്തുക;
            അവസ്ഥ 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
            }
        } അല്ലെങ്കിൽ {
            SDL_assert(info.memory_model == VBE_MEMMODEL_DIRECT_COLOR);
            സ്ഥിരം Uint32 rmask = ((((Uint32)1) << info.red_mask_size) - 1) << info.red_mask_pos;
            സ്ഥിരം Uint32 gmask = ((((Uint32)1) << info.green_mask_size) - 1) << info.green_mask_pos;
            സ്ഥിരം Uint32 bmask = ((((Uint32)1) << info.blue_mask_size) - 1) << info.blue_mask_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        എങ്കിൽ (format == SDL_PIXELFORMAT_UNKNOWN) {
            തുടരുക; // don't know what to do with this one.
        }

        SDL_DisplayModeData *internal = (SDL_DisplayModeData *)SDL_malloc(വലുപ്പം(*internal));
        എങ്കിൽ (!internal) {
            തുടരുക; // oof.
        }

        SDL_copyp(internal, &info);

        SDL_DisplayMode mode;
        SDL_zero(mode);
        mode.format = format;
        mode.w = (പൂർണ്ണസംഖ്യ)info.w;
        mode.h = (പൂർണ്ണസംഖ്യ)info.h;
        mode.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        mode.internal = internal;

        എങ്കിൽ (!SDL_AddFullscreenDisplayMode(sdl_display, &mode)) {
            SDL_free(internal); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_DisplayModeData *internal = (SDL_DisplayModeData *)SDL_malloc(വലുപ്പം(*internal));
        എങ്കിൽ (internal) {
            SDL_zerop(internal);
            internal->mode_id = VGA_MODE_13H_SENTINEL;
            internal->attributes = VBE_MODEATTR_REQUIRED;
            internal->pitch = 320;
            internal->w = 320;
            internal->h = 200;
            internal->അക്കം_planes = 1;
            internal->bpp = 8;
            internal->memory_model = VBE_MEMMODEL_PACKED_PIXEL;
            internal->അക്കം_image_pages = 0; // no page flipping in mode 13h
            internal->physical_base_addr = 0;
            internal->has_lfb = false;
            internal->win_granularity = 64;
            internal->win_size = 64;
            internal->win_a_segment = VGA_MODE_13H_SEGMENT;
            internal->win_func_ptr = 0;
            internal->win_a_attributes = VBE_WINATTR_USABLE;

            SDL_DisplayMode mode;
            SDL_zero(mode);
            mode.format = SDL_PIXELFORMAT_INDEX8;
            mode.w = 320;
            mode.h = 200;
            mode.pixel_density = 1.0f;
            mode.internal = internal;

            എങ്കിൽ (!SDL_AddFullscreenDisplayMode(sdl_display, &mode)) {
                SDL_free(internal);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < sdl_display->അക്കം_fullscreen_modes - 1; i++) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = i + 1; j < sdl_display->അക്കം_fullscreen_modes; j++) {
            സ്ഥിരം SDL_DisplayMode *a = &sdl_display->fullscreen_modes[i];
            സ്ഥിരം SDL_DisplayMode *b = &sdl_display->fullscreen_modes[j];
            bool swap = false;
            എങ്കിൽ (b->w > a->w) {
                swap = true;
            } അല്ലെങ്കിൽ എങ്കിൽ (b->w == a->w) {
                എങ്കിൽ (b->h > a->h) {
                    swap = true;
                } അല്ലെങ്കിൽ എങ്കിൽ (b->h == a->h) {
                    എങ്കിൽ (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        swap = true;
                    }
                }
            }
            എങ്കിൽ (swap) {
                SDL_DisplayMode tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    തിരികെ true;
}

bool DOSVESA_SetDisplayMode(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *data = device->internal;
    സ്ഥിരം SDL_DisplayModeData *modedata = mode->internal;

    എങ്കിൽ (data->current_mode.internal && (data->current_mode.internal->mode_id == modedata->mode_id)) {
        തിരികെ true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    എങ്കിൽ (data->mapping.size) {
        __dpmi_free_physical_address_mapping(&data->mapping); // dump existing video mapping.
        SDL_zero(data->mapping);
    }

    __dpmi_regs regs;

    എങ്കിൽ (modedata->mode_id == VGA_MODE_13H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        data->banked_mode = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&data->current_mode, mode);

        data->page_flip_available = false;
        data->current_page = 0;
        data->page_offset[0] = 0;
        data->page_offset[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_base = (Uint32)VGA_MODE_13H_SEGMENT << 4;
            വേണ്ടി (പൂർണ്ണസംഖ്യ row = 0; row < 200; row++) {
                dosmemput(zero_buf, 320, vga_base + row * 320);
            }
        }

        എങ്കിൽ (SDL_GetMouse()->internal != ശൂന്യ) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(mode->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(mode->h - 1);
            __dpmi_int(0x33, &regs);
        }

        തിരികെ true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    സ്ഥിരം bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_size > 0 &&
                                  (modedata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    സ്ഥിരം bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_DIRECT_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->mode_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    എങ്കിൽ (regs.x.ax != 0x004F) {
        തിരികെ SDL_SetError("Failed to set VESA video mode");
    }

    data->banked_mode = !use_lfb;

    എങ്കിൽ (use_lfb) {
        data->mapping.address = modedata->physical_base_addr;
        data->mapping.size = DOSVESA_GetVESATotalMemory();
        എങ്കിൽ (__dpmi_physical_address_mapping(&data->mapping) != 0) {
            SDL_zero(data->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(data->current_mode);
            തിരികെ SDL_SetError("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_PhysicalToLinear(data->mapping.address), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } അല്ലെങ്കിൽ {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 total_bytes = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_bytes = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_size_bytes = (Uint32)modedata->win_size * 1024;
        Uint32 win_base = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 offset = 0;
        പൂർണ്ണസംഖ്യ current_bank = -1;
        ആകുമ്പോൾ (offset < total_bytes) {
            പൂർണ്ണസംഖ്യ bank = (പൂർണ്ണസംഖ്യ)(offset / win_gran_bytes);
            Uint32 off_in_win = offset % win_gran_bytes;
            Uint32 n = win_size_bytes - off_in_win;
            എങ്കിൽ (n > total_bytes - offset) {
                n = total_bytes - offset;
            }

            എങ്കിൽ (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                എങ്കിൽ (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } അല്ലെങ്കിൽ {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            ആകുമ്പോൾ (written < n) {
                Uint32 chunk = n - written;
                എങ്കിൽ (chunk > വലുപ്പം(zero_buf)) {
                    chunk = വലുപ്പം(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_base + off_in_win + written);
                written += chunk;
            }
            offset += n;
        }
    }

    SDL_copyp(&data->current_mode, mode);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    എങ്കിൽ (!data->banked_mode && modedata->അക്കം_image_pages >= 1) {
        data->page_flip_available = true;
        data->current_page = 0;
        data->page_offset[0] = 0;
        data->page_offset[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_end = data->page_offset[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        എങ്കിൽ (page1_end > data->mapping.size) {
            data->page_flip_available = false;
            data->page_offset[1] = 0;
        } അല്ലെങ്കിൽ {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } അല്ലെങ്കിൽ {
        data->page_flip_available = false;
        data->current_page = 0;
        data->page_offset[0] = 0;
        data->page_offset[1] = 0;
    }

    എങ്കിൽ (SDL_GetMouse()->internal != ശൂന്യ) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(mode->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(mode->h - 1);
        __dpmi_int(0x33, &regs);
    }

    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_DOSVESA
