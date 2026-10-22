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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_dosframebuffer_c.h"

// DOS declarations
#ضمن "SDL_dosmodes.h"
#ضمن "SDL_dosvideo.h"
#ضمن <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#تعریف_کرو VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#تعریف_کرو VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#تعریف_کرو VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#تعریف_کرو VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#تعریف_کرو VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#تعریف_کرو VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#تعریف_کرو VBE_MEMMODEL_سدھا_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#تعریف_کرو VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#تعریف_کرو VBE_MODELIST_سرا 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#تعریف_کرو VGA_منوال_13_H_SENTINEL 0xFFEE
#تعریف_کرو VGA_منوال_13_H_SEGMENT  0xA000

#ہدایت pack(ڈالو, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
تعريفنوع بنية SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_منوال_Ptr; // segment:offset
    Uint16 کل_حافظہ;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_انکڑے[256];
} SDL_VESAHardwareInfo;

تعريفنوع بنية SDL_VESAModeHardwareInfo
{
    Uint16 منوال_گن;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_ناپ;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 بائٹاں_فی_جانچ_سطر;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_ناپ;
    Uint8 YChar_ناپ;
    Uint8 نمبر_دا_Planes;
    Uint8 بٹ_فی_Pixel;
    Uint8 نمبر_دا_Banks;
    Uint8 حافظہ_Model;
    Uint8 Bank_ناپ;
    Uint8 نمبر_دا_Image_ورقے;
    Uint8 Reserved_ورقہ;
    Uint8 Red_نقاب_ناپ;
    Uint8 Red_نقاب_Pos;
    Uint8 Green_نقاب_ناپ;
    Uint8 Green_نقاب_Pos;
    Uint8 Blue_نقاب_ناپ;
    Uint8 Blue_نقاب_Pos;
    Uint8 Reserved_نقاب_ناپ;
    Uint8 Reserved_نقاب_Pos;
    Uint8 سدھا_Color_منوال_Info;
    Uint32 Phys_ادھار_Ptr;
    Uint32 Off_Screen_Mem_وتھ;
    Uint16 Off_Screen_Mem_ناپ;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#ہدایت pack(نکالو)

تعريفنوع بنية SDL_VESAInfo
{
    Uint16 نسخہ;              // 0x200 == 2.0, etc.
    Uint32 کل_حافظہ_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *منوال_list;           // copied out of conventional memory before freeing
    صحيح عدد_modes;
    Uint16 oem_software_revision;
    حرف *oem_string;
    حرف *oem_vendor;
    حرف *oem_ضرب_حاصل;
    حرف *oem_revision;
} SDL_VESAInfo;

ساكن SDL_VESAInfo *vesa_info = عدم;

فراغ DOSVESA_FreeVESAInfo(فراغ)
{
    إذا (vesa_info) {
        SDL_free(vesa_info->منوال_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_ضرب_حاصل);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = عدم;
    }
}

ساكن ثابت SDL_VESAInfo *GetVESAInfo(فراغ)
{
    إذا (vesa_info) {
        أرجع vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_حافظہ(حجم(*hwinfo), &hwinfo_seginfo);
    إذا (!hwinfo) {
        أرجع عدم;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_خطی_منزل_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطی_منزل_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    إذا ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_سیٹ_Error("VESA video not supported on this system");
    } وإلا {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, حجم(*vesa_info));
        إذا (vesa_info) {
            vesa_info->نسخہ = hwinfo->VESAVersion;
            vesa_info->کل_حافظہ_2 = ((Uint32)hwinfo->کل_حافظہ) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_منوال_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_ضرب_حاصل = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                صحيح گنتی = 0;
                طالما (DOS_PeekUint16(segoffset + گنتی * حجم(Uint16)) != VBE_MODELIST_سرا) {
                    گنتی++;
                    إذا (گنتی > 64)
                        اكسر; // sanity limit
                }
                vesa_info->عدد_modes = گنتی;
                vesa_info->منوال_list = (Uint16 *)SDL_malloc(گنتی * حجم(Uint16));
                إذا (vesa_info->منوال_list) {
                    لكل (صحيح i = 0; i < گنتی; i++) {
                        vesa_info->منوال_list[i] = DOS_PeekUint16(segoffset + i * حجم(Uint16));
                    }
                } وإلا {
                    vesa_info->عدد_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_حافظہ(&hwinfo_seginfo);

    أرجع vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
ساكن bool DetectVGA(فراغ)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    أرجع ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(فراغ)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    إذا (!DetectVGA()) {
        أرجع SDL_سیٹ_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (فراغ)GetVESAInfo();

    أرجع true;
}

ثابت حرف *DOSVESA_GetGPUName(فراغ)
{
    ثابت SDL_VESAInfo *vinfo = GetVESAInfo();
    إذا (!vinfo) {
        أرجع "VGA";
    }

    إذا (vinfo->oem_ضرب_حاصل && *vinfo->oem_ضرب_حاصل) {
        أرجع vinfo->oem_ضرب_حاصل;
    }
    إذا (vinfo->oem_vendor && *vinfo->oem_vendor) {
        أرجع vinfo->oem_vendor;
    }
    إذا (vinfo->oem_string && *vinfo->oem_string) {
        أرجع vinfo->oem_string;
    }

    أرجع "VESA";
}

Uint32 DOSVESA_Get_VESATotal_حافظہ(فراغ)
{
    ثابت SDL_VESAInfo *info = GetVESAInfo();
    أرجع info ? info->کل_حافظہ_2 : 0;
}

ساكن bool GetVESAModeInfo(Uint16 منوال_id, SDL_Display_منوال_انکڑے *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_حافظہ(حجم(*hwinfo), &hwinfo_seginfo);
    إذا (!hwinfo) {
        أرجع false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_خطی_منزل_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطی_منزل_Physical(hwinfo) & 0xF;
    regs.x.cx = منوال_id;
    __dpmi_int(0x10, &regs);

    ثابت bool retval = (regs.x.ax == 0x004F);
    إذا (retval) {
        SDL_zerop(info);
        info->منوال_id = منوال_id;
        info->گن = hwinfo->منوال_گن;
        info->pitch = hwinfo->بائٹاں_فی_جانچ_سطر;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->عدد_planes = hwinfo->نمبر_دا_Planes;
        info->bpp = hwinfo->بٹ_فی_Pixel;
        info->حافظہ_model = hwinfo->حافظہ_Model;
        info->عدد_image_ورقے = hwinfo->نمبر_دا_Image_ورقے;
        info->red_نقاب_ناپ = hwinfo->Red_نقاب_ناپ;
        info->red_نقاب_pos = hwinfo->Red_نقاب_Pos;
        info->green_نقاب_ناپ = hwinfo->Green_نقاب_ناپ;
        info->green_نقاب_pos = hwinfo->Green_نقاب_Pos;
        info->blue_نقاب_ناپ = hwinfo->Blue_نقاب_ناپ;
        info->blue_نقاب_pos = hwinfo->Blue_نقاب_Pos;
        info->physical_ادھار_addr = hwinfo->Phys_ادھار_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->منوال_گن & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_ناپ = hwinfo->Win_ناپ;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_گن = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_حافظہ(&hwinfo_seginfo);

    أرجع retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ثابت SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    صحيح عدد_vesa_modes = (vinfo && vinfo->نسخہ >= 0x102) ? vinfo->عدد_modes : 0;

    لكل (صحيح mi = 0; mi < عدد_vesa_modes; mi++) {
        ثابت Uint16 modeid = vinfo->منوال_list[mi];

        SDL_Display_منوال_انکڑے info;
        إذا (!GetVESAModeInfo(modeid, &info)) {
            استمر;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        إذا (info.bpp == 8 && info.w == 320 && info.h == 200) {
            استمر;
        }

        إذا ((info.گن & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            استمر;
        }

        إذا (!(info.گن & VBE_MODEATTR_LFB) && (info.win_a_گن & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            استمر;
        }

        إذا (info.عدد_planes != 1) {
            استمر; // skip planar pixel layouts.
        } وإلا إذا (info.bpp < 8) {
            استمر; // skip anything below 8-bit.
        } وإلا إذا (!info.w || !info.h) {
            استمر; // zero-area display mode?!
        } وإلا إذا (!info.has_lfb && !info.win_granularity) {
            استمر; // banked mode with zero granularity would cause division by zero.
        } وإلا إذا ((info.حافظہ_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.حافظہ_model != VBE_MEMMODEL_سدھا_COLOR)) {
            استمر; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        إذا (info.حافظہ_model == VBE_MEMMODEL_PACKED_PIXEL) {
            بدل (info.bpp) {
            حالة 8:
                format = SDL_PIXELFORMAT_INDEX8;
                اكسر;
            حالة 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                اكسر;
            حالة 16:
                format = SDL_PIXELFORMAT_RGB565;
                اكسر;
            حالة 24:
                format = SDL_PIXELFORMAT_RGB24;
                اكسر;
            حالة 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                اكسر;
            افتراضي:
                اكسر;
            }
        } وإلا {
            SDL_assert(info.حافظہ_model == VBE_MEMMODEL_سدھا_COLOR);
            ثابت Uint32 rmask = ((((Uint32)1) << info.red_نقاب_ناپ) - 1) << info.red_نقاب_pos;
            ثابت Uint32 gmask = ((((Uint32)1) << info.green_نقاب_ناپ) - 1) << info.green_نقاب_pos;
            ثابت Uint32 bmask = ((((Uint32)1) << info.blue_نقاب_ناپ) - 1) << info.blue_نقاب_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        إذا (format == SDL_PIXELFORMAT_UNKNOWN) {
            استمر; // don't know what to do with this one.
        }

        SDL_Display_منوال_انکڑے *اندرونی = (SDL_Display_منوال_انکڑے *)SDL_malloc(حجم(*اندرونی));
        إذا (!اندرونی) {
            استمر; // oof.
        }

        SDL_copyp(اندرونی, &info);

        SDL_Display_منوال منوال;
        SDL_zero(منوال);
        منوال.format = format;
        منوال.w = (صحيح)info.w;
        منوال.h = (صحيح)info.h;
        منوال.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        منوال.اندرونی = اندرونی;

        إذا (!SDL_جوڑو_Fullscreen_Display_منوال(sdl_display, &منوال)) {
            SDL_free(اندرونی); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_منوال_انکڑے *اندرونی = (SDL_Display_منوال_انکڑے *)SDL_malloc(حجم(*اندرونی));
        إذا (اندرونی) {
            SDL_zerop(اندرونی);
            اندرونی->منوال_id = VGA_منوال_13_H_SENTINEL;
            اندرونی->گن = VBE_MODEATTR_REQUIRED;
            اندرونی->pitch = 320;
            اندرونی->w = 320;
            اندرونی->h = 200;
            اندرونی->عدد_planes = 1;
            اندرونی->bpp = 8;
            اندرونی->حافظہ_model = VBE_MEMMODEL_PACKED_PIXEL;
            اندرونی->عدد_image_ورقے = 0; // no page flipping in mode 13h
            اندرونی->physical_ادھار_addr = 0;
            اندرونی->has_lfb = false;
            اندرونی->win_granularity = 64;
            اندرونی->win_ناپ = 64;
            اندرونی->win_a_segment = VGA_منوال_13_H_SEGMENT;
            اندرونی->win_func_ptr = 0;
            اندرونی->win_a_گن = VBE_WINATTR_USABLE;

            SDL_Display_منوال منوال;
            SDL_zero(منوال);
            منوال.format = SDL_PIXELFORMAT_INDEX8;
            منوال.w = 320;
            منوال.h = 200;
            منوال.pixel_density = 1.0f;
            منوال.اندرونی = اندرونی;

            إذا (!SDL_جوڑو_Fullscreen_Display_منوال(sdl_display, &منوال)) {
                SDL_free(اندرونی);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    لكل (صحيح i = 0; i < sdl_display->عدد_fullscreen_modes - 1; i++) {
        لكل (صحيح j = i + 1; j < sdl_display->عدد_fullscreen_modes; j++) {
            ثابت SDL_Display_منوال *a = &sdl_display->fullscreen_modes[i];
            ثابت SDL_Display_منوال *b = &sdl_display->fullscreen_modes[j];
            bool وٹاندرا = false;
            إذا (b->w > a->w) {
                وٹاندرا = true;
            } وإلا إذا (b->w == a->w) {
                إذا (b->h > a->h) {
                    وٹاندرا = true;
                } وإلا إذا (b->h == a->h) {
                    إذا (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        وٹاندرا = true;
                    }
                }
            }
            إذا (وٹاندرا) {
                SDL_Display_منوال tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    أرجع true;
}

bool DOSVESA_سیٹ_Display_منوال(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_منوال *منوال)
{
    SDL_Video_انکڑے *انکڑے = device->اندرونی;
    ثابت SDL_Display_منوال_انکڑے *modedata = منوال->اندرونی;

    إذا (انکڑے->current_منوال.اندرونی && (انکڑے->current_منوال.اندرونی->منوال_id == modedata->منوال_id)) {
        أرجع true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    إذا (انکڑے->mapping.ناپ) {
        __dpmi_free_physical_address_mapping(&انکڑے->mapping); // dump existing video mapping.
        SDL_zero(انکڑے->mapping);
    }

    __dpmi_regs regs;

    إذا (modedata->منوال_id == VGA_منوال_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        انکڑے->banked_منوال = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&انکڑے->current_منوال, منوال);

        انکڑے->ورقہ_flip_دستیاب = false;
        انکڑے->current_ورقہ = 0;
        انکڑے->ورقہ_وتھ[0] = 0;
        انکڑے->ورقہ_وتھ[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_ادھار = (Uint32)VGA_منوال_13_H_SEGMENT << 4;
            لكل (صحيح صف = 0; صف < 200; صف++) {
                dosmemput(zero_buf, 320, vga_ادھار + صف * 320);
            }
        }

        إذا (SDL_GetMouse()->اندرونی != عدم) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(منوال->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(منوال->h - 1);
            __dpmi_int(0x33, &regs);
        }

        أرجع true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ثابت bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_ناپ > 0 &&
                                  (modedata->win_a_گن & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ثابت bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_سدھا_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->منوال_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    إذا (regs.x.ax != 0x004F) {
        أرجع SDL_سیٹ_Error("Failed to set VESA video mode");
    }

    انکڑے->banked_منوال = !use_lfb;

    إذا (use_lfb) {
        انکڑے->mapping.پتہ = modedata->physical_ادھار_addr;
        انکڑے->mapping.ناپ = DOSVESA_Get_VESATotal_حافظہ();
        إذا (__dpmi_physical_address_mapping(&انکڑے->mapping) != 0) {
            SDL_zero(انکڑے->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(انکڑے->current_منوال);
            أرجع SDL_سیٹ_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_منزل_خطی(انکڑے->mapping.پتہ), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } وإلا {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 کل_بائٹاں = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_بائٹاں = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_ناپ_بائٹاں = (Uint32)modedata->win_ناپ * 1024;
        Uint32 win_ادھار = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 وتھ_2 = 0;
        صحيح current_bank = -1;
        طالما (وتھ_2 < کل_بائٹاں) {
            صحيح bank = (صحيح)(وتھ_2 / win_gran_بائٹاں);
            Uint32 off_وچ_win = وتھ_2 % win_gran_بائٹاں;
            Uint32 n = win_ناپ_بائٹاں - off_وچ_win;
            إذا (n > کل_بائٹاں - وتھ_2) {
                n = کل_بائٹاں - وتھ_2;
            }

            إذا (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                إذا (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } وإلا {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            طالما (written < n) {
                Uint32 chunk = n - written;
                إذا (chunk > حجم(zero_buf)) {
                    chunk = حجم(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_ادھار + off_وچ_win + written);
                written += chunk;
            }
            وتھ_2 += n;
        }
    }

    SDL_copyp(&انکڑے->current_منوال, منوال);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    إذا (!انکڑے->banked_منوال && modedata->عدد_image_ورقے >= 1) {
        انکڑے->ورقہ_flip_دستیاب = true;
        انکڑے->current_ورقہ = 0;
        انکڑے->ورقہ_وتھ[0] = 0;
        انکڑے->ورقہ_وتھ[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_سرا = انکڑے->ورقہ_وتھ[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        إذا (page1_سرا > انکڑے->mapping.ناپ) {
            انکڑے->ورقہ_flip_دستیاب = false;
            انکڑے->ورقہ_وتھ[1] = 0;
        } وإلا {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_منزل_خطی(انکڑے->mapping.پتہ) + انکڑے->ورقہ_وتھ[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } وإلا {
        انکڑے->ورقہ_flip_دستیاب = false;
        انکڑے->current_ورقہ = 0;
        انکڑے->ورقہ_وتھ[0] = 0;
        انکڑے->ورقہ_وتھ[1] = 0;
    }

    إذا (SDL_GetMouse()->اندرونی != عدم) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(منوال->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(منوال->h - 1);
        __dpmi_int(0x33, &regs);
    }

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_DOSVESA
