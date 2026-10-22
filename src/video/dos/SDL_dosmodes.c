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
#تعریف_کړه VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#تعریف_کړه VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#تعریف_کړه VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#تعریف_کړه VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#تعریف_کړه VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#تعریف_کړه VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#تعریف_کړه VBE_MEMMODEL_مستقیم_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#تعریف_کړه VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#تعریف_کړه VBE_MODELIST_پای_ټکی 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#تعریف_کړه VGA_ډېرپېښ_13_H_SENTINEL 0xFFEE
#تعریف_کړه VGA_ډېرپېښ_13_H_SEGMENT  0xA000

#لارښوونه pack(ټېل, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
تعريفنوع بنية SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_ډېرپېښ_Ptr; // segment:offset
    Uint16 ټول_حافظه;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_معلومات[256];
} SDL_VESAHardwareInfo;

تعريفنوع بنية SDL_VESAModeHardwareInfo
{
    Uint16 ډېرپېښ_ځانګړتیاوې;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_اندازه;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 بایټونه_فی_لټون_کرښه;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_اندازه;
    Uint8 YChar_اندازه;
    Uint8 شمېره_د_Planes;
    Uint8 بټونه_فی_Pixel;
    Uint8 شمېره_د_Banks;
    Uint8 حافظه_Model;
    Uint8 Bank_اندازه;
    Uint8 شمېره_د_Image_پاڼې;
    Uint8 Reserved_پاڼه;
    Uint8 Red_ماسک_اندازه;
    Uint8 Red_ماسک_Pos;
    Uint8 Green_ماسک_اندازه;
    Uint8 Green_ماسک_Pos;
    Uint8 Blue_ماسک_اندازه;
    Uint8 Blue_ماسک_Pos;
    Uint8 Reserved_ماسک_اندازه;
    Uint8 Reserved_ماسک_Pos;
    Uint8 مستقیم_Color_ډېرپېښ_Info;
    Uint32 Phys_بنسټ_Ptr;
    Uint32 Off_Screen_Mem_دننه_واټن;
    Uint16 Off_Screen_Mem_اندازه;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#لارښوونه pack(راوباسه)

تعريفنوع بنية SDL_VESAInfo
{
    Uint16 نسخه;              // 0x200 == 2.0, etc.
    Uint32 ټول_حافظه_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *ډېرپېښ_list;           // copied out of conventional memory before freeing
    صحيح عدد_modes;
    Uint16 oem_software_revision;
    حرف *oem_string;
    حرف *oem_vendor;
    حرف *oem_حاصل_ضرب;
    حرف *oem_revision;
} SDL_VESAInfo;

ساكن SDL_VESAInfo *vesa_info = عدم;

فراغ DOSVESA_FreeVESAInfo(فراغ)
{
    إذا (vesa_info) {
        SDL_free(vesa_info->ډېرپېښ_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_حاصل_ضرب);
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
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_حافظه(حجم(*hwinfo), &hwinfo_seginfo);
    إذا (!hwinfo) {
        أرجع عدم;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_خطي_منزل_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطي_منزل_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    إذا ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_سېټ_Error("VESA video not supported on this system");
    } وإلا {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, حجم(*vesa_info));
        إذا (vesa_info) {
            vesa_info->نسخه = hwinfo->VESAVersion;
            vesa_info->ټول_حافظه_2 = ((Uint32)hwinfo->ټول_حافظه) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_ډېرپېښ_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_حاصل_ضرب = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                صحيح شمېر = 0;
                طالما (DOS_PeekUint16(segoffset + شمېر * حجم(Uint16)) != VBE_MODELIST_پای_ټکی) {
                    شمېر++;
                    إذا (شمېر > 64)
                        اكسر; // sanity limit
                }
                vesa_info->عدد_modes = شمېر;
                vesa_info->ډېرپېښ_list = (Uint16 *)SDL_malloc(شمېر * حجم(Uint16));
                إذا (vesa_info->ډېرپېښ_list) {
                    لكل (صحيح i = 0; i < شمېر; i++) {
                        vesa_info->ډېرپېښ_list[i] = DOS_PeekUint16(segoffset + i * حجم(Uint16));
                    }
                } وإلا {
                    vesa_info->عدد_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_حافظه(&hwinfo_seginfo);

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
        أرجع SDL_سېټ_Error("No VGA card detected");
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

    إذا (vinfo->oem_حاصل_ضرب && *vinfo->oem_حاصل_ضرب) {
        أرجع vinfo->oem_حاصل_ضرب;
    }
    إذا (vinfo->oem_vendor && *vinfo->oem_vendor) {
        أرجع vinfo->oem_vendor;
    }
    إذا (vinfo->oem_string && *vinfo->oem_string) {
        أرجع vinfo->oem_string;
    }

    أرجع "VESA";
}

Uint32 DOSVESA_Get_VESATotal_حافظه(فراغ)
{
    ثابت SDL_VESAInfo *info = GetVESAInfo();
    أرجع info ? info->ټول_حافظه_2 : 0;
}

ساكن bool GetVESAModeInfo(Uint16 ډېرپېښ_id, SDL_Display_ډېرپېښ_معلومات *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_حافظه(حجم(*hwinfo), &hwinfo_seginfo);
    إذا (!hwinfo) {
        أرجع false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_خطي_منزل_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطي_منزل_Physical(hwinfo) & 0xF;
    regs.x.cx = ډېرپېښ_id;
    __dpmi_int(0x10, &regs);

    ثابت bool retval = (regs.x.ax == 0x004F);
    إذا (retval) {
        SDL_zerop(info);
        info->ډېرپېښ_id = ډېرپېښ_id;
        info->ځانګړتیاوې = hwinfo->ډېرپېښ_ځانګړتیاوې;
        info->pitch = hwinfo->بایټونه_فی_لټون_کرښه;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->عدد_planes = hwinfo->شمېره_د_Planes;
        info->bpp = hwinfo->بټونه_فی_Pixel;
        info->حافظه_model = hwinfo->حافظه_Model;
        info->عدد_image_پاڼې = hwinfo->شمېره_د_Image_پاڼې;
        info->red_ماسک_اندازه = hwinfo->Red_ماسک_اندازه;
        info->red_ماسک_pos = hwinfo->Red_ماسک_Pos;
        info->green_ماسک_اندازه = hwinfo->Green_ماسک_اندازه;
        info->green_ماسک_pos = hwinfo->Green_ماسک_Pos;
        info->blue_ماسک_اندازه = hwinfo->Blue_ماسک_اندازه;
        info->blue_ماسک_pos = hwinfo->Blue_ماسک_Pos;
        info->physical_بنسټ_addr = hwinfo->Phys_بنسټ_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->ډېرپېښ_ځانګړتیاوې & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_اندازه = hwinfo->Win_اندازه;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_ځانګړتیاوې = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_حافظه(&hwinfo_seginfo);

    أرجع retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ثابت SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    صحيح عدد_vesa_modes = (vinfo && vinfo->نسخه >= 0x102) ? vinfo->عدد_modes : 0;

    لكل (صحيح mi = 0; mi < عدد_vesa_modes; mi++) {
        ثابت Uint16 modeid = vinfo->ډېرپېښ_list[mi];

        SDL_Display_ډېرپېښ_معلومات info;
        إذا (!GetVESAModeInfo(modeid, &info)) {
            استمر;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        إذا (info.bpp == 8 && info.w == 320 && info.h == 200) {
            استمر;
        }

        إذا ((info.ځانګړتیاوې & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            استمر;
        }

        إذا (!(info.ځانګړتیاوې & VBE_MODEATTR_LFB) && (info.win_a_ځانګړتیاوې & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
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
        } وإلا إذا ((info.حافظه_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.حافظه_model != VBE_MEMMODEL_مستقیم_COLOR)) {
            استمر; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        إذا (info.حافظه_model == VBE_MEMMODEL_PACKED_PIXEL) {
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
            SDL_assert(info.حافظه_model == VBE_MEMMODEL_مستقیم_COLOR);
            ثابت Uint32 rmask = ((((Uint32)1) << info.red_ماسک_اندازه) - 1) << info.red_ماسک_pos;
            ثابت Uint32 gmask = ((((Uint32)1) << info.green_ماسک_اندازه) - 1) << info.green_ماسک_pos;
            ثابت Uint32 bmask = ((((Uint32)1) << info.blue_ماسک_اندازه) - 1) << info.blue_ماسک_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        إذا (format == SDL_PIXELFORMAT_UNKNOWN) {
            استمر; // don't know what to do with this one.
        }

        SDL_Display_ډېرپېښ_معلومات *دننی = (SDL_Display_ډېرپېښ_معلومات *)SDL_malloc(حجم(*دننی));
        إذا (!دننی) {
            استمر; // oof.
        }

        SDL_copyp(دننی, &info);

        SDL_Display_ډېرپېښ ډېرپېښ;
        SDL_zero(ډېرپېښ);
        ډېرپېښ.format = format;
        ډېرپېښ.w = (صحيح)info.w;
        ډېرپېښ.h = (صحيح)info.h;
        ډېرپېښ.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        ډېرپېښ.دننی = دننی;

        إذا (!SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(sdl_display, &ډېرپېښ)) {
            SDL_free(دننی); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_ډېرپېښ_معلومات *دننی = (SDL_Display_ډېرپېښ_معلومات *)SDL_malloc(حجم(*دننی));
        إذا (دننی) {
            SDL_zerop(دننی);
            دننی->ډېرپېښ_id = VGA_ډېرپېښ_13_H_SENTINEL;
            دننی->ځانګړتیاوې = VBE_MODEATTR_REQUIRED;
            دننی->pitch = 320;
            دننی->w = 320;
            دننی->h = 200;
            دننی->عدد_planes = 1;
            دننی->bpp = 8;
            دننی->حافظه_model = VBE_MEMMODEL_PACKED_PIXEL;
            دننی->عدد_image_پاڼې = 0; // no page flipping in mode 13h
            دننی->physical_بنسټ_addr = 0;
            دننی->has_lfb = false;
            دننی->win_granularity = 64;
            دننی->win_اندازه = 64;
            دننی->win_a_segment = VGA_ډېرپېښ_13_H_SEGMENT;
            دننی->win_func_ptr = 0;
            دننی->win_a_ځانګړتیاوې = VBE_WINATTR_USABLE;

            SDL_Display_ډېرپېښ ډېرپېښ;
            SDL_zero(ډېرپېښ);
            ډېرپېښ.format = SDL_PIXELFORMAT_INDEX8;
            ډېرپېښ.w = 320;
            ډېرپېښ.h = 200;
            ډېرپېښ.pixel_density = 1.0f;
            ډېرپېښ.دننی = دننی;

            إذا (!SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(sdl_display, &ډېرپېښ)) {
                SDL_free(دننی);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    لكل (صحيح i = 0; i < sdl_display->عدد_fullscreen_modes - 1; i++) {
        لكل (صحيح j = i + 1; j < sdl_display->عدد_fullscreen_modes; j++) {
            ثابت SDL_Display_ډېرپېښ *a = &sdl_display->fullscreen_modes[i];
            ثابت SDL_Display_ډېرپېښ *b = &sdl_display->fullscreen_modes[j];
            bool بدلون = false;
            إذا (b->w > a->w) {
                بدلون = true;
            } وإلا إذا (b->w == a->w) {
                إذا (b->h > a->h) {
                    بدلون = true;
                } وإلا إذا (b->h == a->h) {
                    إذا (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        بدلون = true;
                    }
                }
            }
            إذا (بدلون) {
                SDL_Display_ډېرپېښ tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    أرجع true;
}

bool DOSVESA_سېټ_Display_ډېرپېښ(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Video_معلومات *معلومات = device->دننی;
    ثابت SDL_Display_ډېرپېښ_معلومات *modedata = ډېرپېښ->دننی;

    إذا (معلومات->current_ډېرپېښ.دننی && (معلومات->current_ډېرپېښ.دننی->ډېرپېښ_id == modedata->ډېرپېښ_id)) {
        أرجع true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    إذا (معلومات->mapping.اندازه) {
        __dpmi_free_physical_address_mapping(&معلومات->mapping); // dump existing video mapping.
        SDL_zero(معلومات->mapping);
    }

    __dpmi_regs regs;

    إذا (modedata->ډېرپېښ_id == VGA_ډېرپېښ_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        معلومات->banked_ډېرپېښ = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&معلومات->current_ډېرپېښ, ډېرپېښ);

        معلومات->پاڼه_flip_شته = false;
        معلومات->current_پاڼه = 0;
        معلومات->پاڼه_دننه_واټن[0] = 0;
        معلومات->پاڼه_دننه_واټن[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_بنسټ = (Uint32)VGA_ډېرپېښ_13_H_SEGMENT << 4;
            لكل (صحيح لیکه = 0; لیکه < 200; لیکه++) {
                dosmemput(zero_buf, 320, vga_بنسټ + لیکه * 320);
            }
        }

        إذا (SDL_GetMouse()->دننی != عدم) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ډېرپېښ->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ډېرپېښ->h - 1);
            __dpmi_int(0x33, &regs);
        }

        أرجع true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ثابت bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_اندازه > 0 &&
                                  (modedata->win_a_ځانګړتیاوې & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ثابت bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_مستقیم_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->ډېرپېښ_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    إذا (regs.x.ax != 0x004F) {
        أرجع SDL_سېټ_Error("Failed to set VESA video mode");
    }

    معلومات->banked_ډېرپېښ = !use_lfb;

    إذا (use_lfb) {
        معلومات->mapping.پته = modedata->physical_بنسټ_addr;
        معلومات->mapping.اندازه = DOSVESA_Get_VESATotal_حافظه();
        إذا (__dpmi_physical_address_mapping(&معلومات->mapping) != 0) {
            SDL_zero(معلومات->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(معلومات->current_ډېرپېښ);
            أرجع SDL_سېټ_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_منزل_خطي(معلومات->mapping.پته), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } وإلا {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 ټول_بایټونه = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_بایټونه = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_اندازه_بایټونه = (Uint32)modedata->win_اندازه * 1024;
        Uint32 win_بنسټ = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 دننه_واټن_2 = 0;
        صحيح current_bank = -1;
        طالما (دننه_واټن_2 < ټول_بایټونه) {
            صحيح bank = (صحيح)(دننه_واټن_2 / win_gran_بایټونه);
            Uint32 off_دننه_win = دننه_واټن_2 % win_gran_بایټونه;
            Uint32 n = win_اندازه_بایټونه - off_دننه_win;
            إذا (n > ټول_بایټونه - دننه_واټن_2) {
                n = ټول_بایټونه - دننه_واټن_2;
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
                dosmemput(zero_buf, chunk, win_بنسټ + off_دننه_win + written);
                written += chunk;
            }
            دننه_واټن_2 += n;
        }
    }

    SDL_copyp(&معلومات->current_ډېرپېښ, ډېرپېښ);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    إذا (!معلومات->banked_ډېرپېښ && modedata->عدد_image_پاڼې >= 1) {
        معلومات->پاڼه_flip_شته = true;
        معلومات->current_پاڼه = 0;
        معلومات->پاڼه_دننه_واټن[0] = 0;
        معلومات->پاڼه_دننه_واټن[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_پای_ټکی = معلومات->پاڼه_دننه_واټن[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        إذا (page1_پای_ټکی > معلومات->mapping.اندازه) {
            معلومات->پاڼه_flip_شته = false;
            معلومات->پاڼه_دننه_واټن[1] = 0;
        } وإلا {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_منزل_خطي(معلومات->mapping.پته) + معلومات->پاڼه_دننه_واټن[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } وإلا {
        معلومات->پاڼه_flip_شته = false;
        معلومات->current_پاڼه = 0;
        معلومات->پاڼه_دننه_واټن[0] = 0;
        معلومات->پاڼه_دننه_واټن[1] = 0;
    }

    إذا (SDL_GetMouse()->دننی != عدم) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ډېرپېښ->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ډېرپېښ->h - 1);
        __dpmi_int(0x33, &regs);
    }

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_DOSVESA
