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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_DOSVESA

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
#تعریف_کن VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#تعریف_کن VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#تعریف_کن VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#تعریف_کن VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#تعریف_کن VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#تعریف_کن VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#تعریف_کن VBE_MEMMODEL_مستقیم_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#تعریف_کن VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#تعریف_کن VBE_MODELIST_انتها 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#تعریف_کن VGA_نما_13_H_SENTINEL 0xFFEE
#تعریف_کن VGA_نما_13_H_SEGMENT  0xA000

#رهنمود pack(افزودن, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
تعريفنوع بنية SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_نما_Ptr; // segment:offset
    Uint16 مجموع_حافظه;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_داده[256];
} SDL_VESAHardwareInfo;

تعريفنوع بنية SDL_VESAModeHardwareInfo
{
    Uint16 نما_صفات;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_اندازه;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 بایتها_در_هر_پیمایش_سطر;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_اندازه;
    Uint8 YChar_اندازه;
    Uint8 عدد_از_Planes;
    Uint8 بیتها_در_هر_Pixel;
    Uint8 عدد_از_Banks;
    Uint8 حافظه_Model;
    Uint8 Bank_اندازه;
    Uint8 عدد_از_Image_صفحات;
    Uint8 Reserved_صفحه;
    Uint8 Red_ماسک_اندازه;
    Uint8 Red_ماسک_Pos;
    Uint8 Green_ماسک_اندازه;
    Uint8 Green_ماسک_Pos;
    Uint8 Blue_ماسک_اندازه;
    Uint8 Blue_ماسک_Pos;
    Uint8 Reserved_ماسک_اندازه;
    Uint8 Reserved_ماسک_Pos;
    Uint8 مستقیم_Color_نما_Info;
    Uint32 Phys_پایه_Ptr;
    Uint32 Off_Screen_Mem_جابه_جایی;
    Uint16 Off_Screen_Mem_اندازه;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#رهنمود pack(برداشت)

تعريفنوع بنية SDL_VESAInfo
{
    Uint16 نسخه;              // 0x200 == 2.0, etc.
    Uint32 مجموع_حافظه_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *نما_list;           // copied out of conventional memory before freeing
    صحيح رقم_modes;
    Uint16 oem_software_revision;
    حرف *oem_string;
    حرف *oem_vendor;
    حرف *oem_حاصلضرب;
    حرف *oem_revision;
} SDL_VESAInfo;

ساكن SDL_VESAInfo *vesa_info = عدم;

فراغ DOSVESA_FreeVESAInfo(فراغ)
{
    إذا (vesa_info) {
        SDL_free(vesa_info->نما_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_حاصلضرب);
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
    regs.x.es = DOS_خطی_مقصد_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطی_مقصد_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    إذا ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_مجموعه_Error("VESA video not supported on this system");
    } وإلا {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, حجم(*vesa_info));
        إذا (vesa_info) {
            vesa_info->نسخه = hwinfo->VESAVersion;
            vesa_info->مجموع_حافظه_2 = ((Uint32)hwinfo->مجموع_حافظه) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_نما_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_حاصلضرب = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                صحيح شمار = 0;
                طالما (DOS_PeekUint16(segoffset + شمار * حجم(Uint16)) != VBE_MODELIST_انتها) {
                    شمار++;
                    إذا (شمار > 64)
                        اكسر; // sanity limit
                }
                vesa_info->رقم_modes = شمار;
                vesa_info->نما_list = (Uint16 *)SDL_malloc(شمار * حجم(Uint16));
                إذا (vesa_info->نما_list) {
                    لكل (صحيح i = 0; i < شمار; i++) {
                        vesa_info->نما_list[i] = DOS_PeekUint16(segoffset + i * حجم(Uint16));
                    }
                } وإلا {
                    vesa_info->رقم_modes = 0;
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
        أرجع SDL_مجموعه_Error("No VGA card detected");
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

    إذا (vinfo->oem_حاصلضرب && *vinfo->oem_حاصلضرب) {
        أرجع vinfo->oem_حاصلضرب;
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
    أرجع info ? info->مجموع_حافظه_2 : 0;
}

ساكن bool GetVESAModeInfo(Uint16 نما_id, SDL_Display_نما_داده *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_حافظه(حجم(*hwinfo), &hwinfo_seginfo);
    إذا (!hwinfo) {
        أرجع false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_خطی_مقصد_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطی_مقصد_Physical(hwinfo) & 0xF;
    regs.x.cx = نما_id;
    __dpmi_int(0x10, &regs);

    ثابت bool retval = (regs.x.ax == 0x004F);
    إذا (retval) {
        SDL_zerop(info);
        info->نما_id = نما_id;
        info->صفات = hwinfo->نما_صفات;
        info->pitch = hwinfo->بایتها_در_هر_پیمایش_سطر;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->رقم_planes = hwinfo->عدد_از_Planes;
        info->bpp = hwinfo->بیتها_در_هر_Pixel;
        info->حافظه_model = hwinfo->حافظه_Model;
        info->رقم_image_صفحات = hwinfo->عدد_از_Image_صفحات;
        info->red_ماسک_اندازه = hwinfo->Red_ماسک_اندازه;
        info->red_ماسک_pos = hwinfo->Red_ماسک_Pos;
        info->green_ماسک_اندازه = hwinfo->Green_ماسک_اندازه;
        info->green_ماسک_pos = hwinfo->Green_ماسک_Pos;
        info->blue_ماسک_اندازه = hwinfo->Blue_ماسک_اندازه;
        info->blue_ماسک_pos = hwinfo->Blue_ماسک_Pos;
        info->physical_پایه_addr = hwinfo->Phys_پایه_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->نما_صفات & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_اندازه = hwinfo->Win_اندازه;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_صفات = hwinfo->WinAAttributes;
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
    صحيح رقم_vesa_modes = (vinfo && vinfo->نسخه >= 0x102) ? vinfo->رقم_modes : 0;

    لكل (صحيح mi = 0; mi < رقم_vesa_modes; mi++) {
        ثابت Uint16 modeid = vinfo->نما_list[mi];

        SDL_Display_نما_داده info;
        إذا (!GetVESAModeInfo(modeid, &info)) {
            استمر;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        إذا (info.bpp == 8 && info.w == 320 && info.h == 200) {
            استمر;
        }

        إذا ((info.صفات & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            استمر;
        }

        إذا (!(info.صفات & VBE_MODEATTR_LFB) && (info.win_a_صفات & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            استمر;
        }

        إذا (info.رقم_planes != 1) {
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

        SDL_Display_نما_داده *داخلی = (SDL_Display_نما_داده *)SDL_malloc(حجم(*داخلی));
        إذا (!داخلی) {
            استمر; // oof.
        }

        SDL_copyp(داخلی, &info);

        SDL_Display_نما نما;
        SDL_zero(نما);
        نما.format = format;
        نما.w = (صحيح)info.w;
        نما.h = (صحيح)info.h;
        نما.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        نما.داخلی = داخلی;

        إذا (!SDL_جمع_کن_Fullscreen_Display_نما(sdl_display, &نما)) {
            SDL_free(داخلی); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_نما_داده *داخلی = (SDL_Display_نما_داده *)SDL_malloc(حجم(*داخلی));
        إذا (داخلی) {
            SDL_zerop(داخلی);
            داخلی->نما_id = VGA_نما_13_H_SENTINEL;
            داخلی->صفات = VBE_MODEATTR_REQUIRED;
            داخلی->pitch = 320;
            داخلی->w = 320;
            داخلی->h = 200;
            داخلی->رقم_planes = 1;
            داخلی->bpp = 8;
            داخلی->حافظه_model = VBE_MEMMODEL_PACKED_PIXEL;
            داخلی->رقم_image_صفحات = 0; // no page flipping in mode 13h
            داخلی->physical_پایه_addr = 0;
            داخلی->has_lfb = false;
            داخلی->win_granularity = 64;
            داخلی->win_اندازه = 64;
            داخلی->win_a_segment = VGA_نما_13_H_SEGMENT;
            داخلی->win_func_ptr = 0;
            داخلی->win_a_صفات = VBE_WINATTR_USABLE;

            SDL_Display_نما نما;
            SDL_zero(نما);
            نما.format = SDL_PIXELFORMAT_INDEX8;
            نما.w = 320;
            نما.h = 200;
            نما.pixel_density = 1.0f;
            نما.داخلی = داخلی;

            إذا (!SDL_جمع_کن_Fullscreen_Display_نما(sdl_display, &نما)) {
                SDL_free(داخلی);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    لكل (صحيح i = 0; i < sdl_display->رقم_fullscreen_modes - 1; i++) {
        لكل (صحيح j = i + 1; j < sdl_display->رقم_fullscreen_modes; j++) {
            ثابت SDL_Display_نما *a = &sdl_display->fullscreen_modes[i];
            ثابت SDL_Display_نما *b = &sdl_display->fullscreen_modes[j];
            bool جابجا = false;
            إذا (b->w > a->w) {
                جابجا = true;
            } وإلا إذا (b->w == a->w) {
                إذا (b->h > a->h) {
                    جابجا = true;
                } وإلا إذا (b->h == a->h) {
                    إذا (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        جابجا = true;
                    }
                }
            }
            إذا (جابجا) {
                SDL_Display_نما tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    أرجع true;
}

bool DOSVESA_مجموعه_Display_نما(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_نما *نما)
{
    SDL_Video_داده *داده = device->داخلی;
    ثابت SDL_Display_نما_داده *modedata = نما->داخلی;

    إذا (داده->current_نما.داخلی && (داده->current_نما.داخلی->نما_id == modedata->نما_id)) {
        أرجع true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    إذا (داده->mapping.اندازه) {
        __dpmi_free_physical_address_mapping(&داده->mapping); // dump existing video mapping.
        SDL_zero(داده->mapping);
    }

    __dpmi_regs regs;

    إذا (modedata->نما_id == VGA_نما_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        داده->banked_نما = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&داده->current_نما, نما);

        داده->صفحه_flip_موجود = false;
        داده->current_صفحه = 0;
        داده->صفحه_جابه_جایی[0] = 0;
        داده->صفحه_جابه_جایی[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_پایه = (Uint32)VGA_نما_13_H_SEGMENT << 4;
            لكل (صحيح ردیف = 0; ردیف < 200; ردیف++) {
                dosmemput(zero_buf, 320, vga_پایه + ردیف * 320);
            }
        }

        إذا (SDL_GetMouse()->داخلی != عدم) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(نما->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(نما->h - 1);
            __dpmi_int(0x33, &regs);
        }

        أرجع true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ثابت bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_اندازه > 0 &&
                                  (modedata->win_a_صفات & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ثابت bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_مستقیم_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->نما_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    إذا (regs.x.ax != 0x004F) {
        أرجع SDL_مجموعه_Error("Failed to set VESA video mode");
    }

    داده->banked_نما = !use_lfb;

    إذا (use_lfb) {
        داده->mapping.آدرس = modedata->physical_پایه_addr;
        داده->mapping.اندازه = DOSVESA_Get_VESATotal_حافظه();
        إذا (__dpmi_physical_address_mapping(&داده->mapping) != 0) {
            SDL_zero(داده->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(داده->current_نما);
            أرجع SDL_مجموعه_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_مقصد_خطی(داده->mapping.آدرس), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } وإلا {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 مجموع_بایتها = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_بایتها = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_اندازه_بایتها = (Uint32)modedata->win_اندازه * 1024;
        Uint32 win_پایه = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 جابه_جایی_2 = 0;
        صحيح current_bank = -1;
        طالما (جابه_جایی_2 < مجموع_بایتها) {
            صحيح bank = (صحيح)(جابه_جایی_2 / win_gran_بایتها);
            Uint32 off_درون_win = جابه_جایی_2 % win_gran_بایتها;
            Uint32 n = win_اندازه_بایتها - off_درون_win;
            إذا (n > مجموع_بایتها - جابه_جایی_2) {
                n = مجموع_بایتها - جابه_جایی_2;
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
                dosmemput(zero_buf, chunk, win_پایه + off_درون_win + written);
                written += chunk;
            }
            جابه_جایی_2 += n;
        }
    }

    SDL_copyp(&داده->current_نما, نما);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    إذا (!داده->banked_نما && modedata->رقم_image_صفحات >= 1) {
        داده->صفحه_flip_موجود = true;
        داده->current_صفحه = 0;
        داده->صفحه_جابه_جایی[0] = 0;
        داده->صفحه_جابه_جایی[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_انتها = داده->صفحه_جابه_جایی[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        إذا (page1_انتها > داده->mapping.اندازه) {
            داده->صفحه_flip_موجود = false;
            داده->صفحه_جابه_جایی[1] = 0;
        } وإلا {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_مقصد_خطی(داده->mapping.آدرس) + داده->صفحه_جابه_جایی[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } وإلا {
        داده->صفحه_flip_موجود = false;
        داده->current_صفحه = 0;
        داده->صفحه_جابه_جایی[0] = 0;
        داده->صفحه_جابه_جایی[1] = 0;
    }

    إذا (SDL_GetMouse()->داخلی != عدم) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(نما->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(نما->h - 1);
        __dpmi_int(0x33, &regs);
    }

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_DOSVESA
