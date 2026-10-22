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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#شامل "../../events/SDL_mouse_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_dosframebuffer_c.h"

// DOS declarations
#شامل "SDL_dosmodes.h"
#شامل "SDL_dosvideo.h"
#شامل <sys/movedata.h> // for dosmemput (banked framebuffer access)

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
#تعریف_کرو VBE_MEMMODEL_براہ_راست_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#تعریف_کرو VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#تعریف_کرو VBE_MODELIST_انتہا 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#تعریف_کرو VGA_منوال_13_H_SENTINEL 0xFFEE
#تعریف_کرو VGA_منوال_13_H_SEGMENT  0xA000

#ہدایت pack(ڈالو, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
قسمتعریف ساخت SDL_VESAHardwareInfo
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
    Uint8 Oem_ڈیٹا[256];
} SDL_VESAHardwareInfo;

قسمتعریف ساخت SDL_VESAModeHardwareInfo
{
    Uint16 منوال_اوصاف;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_سائز;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 بائٹیں_فی_جائزہ_سطر;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_سائز;
    Uint8 YChar_سائز;
    Uint8 نمبر_کا_Planes;
    Uint8 بٹ_فی_Pixel;
    Uint8 نمبر_کا_Banks;
    Uint8 حافظہ_Model;
    Uint8 Bank_سائز;
    Uint8 نمبر_کا_Image_صفحات;
    Uint8 Reserved_صفحہ;
    Uint8 Red_نقاب_سائز;
    Uint8 Red_نقاب_Pos;
    Uint8 Green_نقاب_سائز;
    Uint8 Green_نقاب_Pos;
    Uint8 Blue_نقاب_سائز;
    Uint8 Blue_نقاب_Pos;
    Uint8 Reserved_نقاب_سائز;
    Uint8 Reserved_نقاب_Pos;
    Uint8 براہ_راست_Color_منوال_Info;
    Uint32 Phys_بنیاد_Ptr;
    Uint32 Off_Screen_Mem_انحراف;
    Uint16 Off_Screen_Mem_سائز;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#ہدایت pack(نکالو)

قسمتعریف ساخت SDL_VESAInfo
{
    Uint16 نسخہ;              // 0x200 == 2.0, etc.
    Uint32 کل_حافظہ_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *منوال_list;           // copied out of conventional memory before freeing
    صحیح عدد_modes;
    Uint16 oem_software_revision;
    حرف *oem_string;
    حرف *oem_vendor;
    حرف *oem_حاصل_ضرب;
    حرف *oem_revision;
} SDL_VESAInfo;

ساکن SDL_VESAInfo *vesa_info = تہی;

خالی DOSVESA_FreeVESAInfo(خالی)
{
    اگر (vesa_info) {
        SDL_free(vesa_info->منوال_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_حاصل_ضرب);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = تہی;
    }
}

ساکن ثابت SDL_VESAInfo *GetVESAInfo(خالی)
{
    اگر (vesa_info) {
        واپس vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_حافظہ(حجم(*hwinfo), &hwinfo_seginfo);
    اگر (!hwinfo) {
        واپس تہی;
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
    اگر ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_سیٹ_Error("VESA video not supported on this system");
    } ورنہ {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, حجم(*vesa_info));
        اگر (vesa_info) {
            vesa_info->نسخہ = hwinfo->VESAVersion;
            vesa_info->کل_حافظہ_2 = ((Uint32)hwinfo->کل_حافظہ) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_منوال_Ptr;
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
                صحیح گنتی = 0;
                جب (DOS_PeekUint16(segoffset + گنتی * حجم(Uint16)) != VBE_MODELIST_انتہا) {
                    گنتی++;
                    اگر (گنتی > 64)
                        توڑو; // sanity limit
                }
                vesa_info->عدد_modes = گنتی;
                vesa_info->منوال_list = (Uint16 *)SDL_malloc(گنتی * حجم(Uint16));
                اگر (vesa_info->منوال_list) {
                    برائے (صحیح i = 0; i < گنتی; i++) {
                        vesa_info->منوال_list[i] = DOS_PeekUint16(segoffset + i * حجم(Uint16));
                    }
                } ورنہ {
                    vesa_info->عدد_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_حافظہ(&hwinfo_seginfo);

    واپس vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
ساکن bool DetectVGA(خالی)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    واپس ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(خالی)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    اگر (!DetectVGA()) {
        واپس SDL_سیٹ_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (خالی)GetVESAInfo();

    واپس true;
}

ثابت حرف *DOSVESA_GetGPUName(خالی)
{
    ثابت SDL_VESAInfo *vinfo = GetVESAInfo();
    اگر (!vinfo) {
        واپس "VGA";
    }

    اگر (vinfo->oem_حاصل_ضرب && *vinfo->oem_حاصل_ضرب) {
        واپس vinfo->oem_حاصل_ضرب;
    }
    اگر (vinfo->oem_vendor && *vinfo->oem_vendor) {
        واپس vinfo->oem_vendor;
    }
    اگر (vinfo->oem_string && *vinfo->oem_string) {
        واپس vinfo->oem_string;
    }

    واپس "VESA";
}

Uint32 DOSVESA_Get_VESATotal_حافظہ(خالی)
{
    ثابت SDL_VESAInfo *info = GetVESAInfo();
    واپس info ? info->کل_حافظہ_2 : 0;
}

ساکن bool GetVESAModeInfo(Uint16 منوال_id, SDL_Display_منوال_ڈیٹا *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_حافظہ(حجم(*hwinfo), &hwinfo_seginfo);
    اگر (!hwinfo) {
        واپس false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_خطی_مقصد_Physical(hwinfo) / 16;
    regs.x.di = DOS_خطی_مقصد_Physical(hwinfo) & 0xF;
    regs.x.cx = منوال_id;
    __dpmi_int(0x10, &regs);

    ثابت bool retval = (regs.x.ax == 0x004F);
    اگر (retval) {
        SDL_zerop(info);
        info->منوال_id = منوال_id;
        info->اوصاف = hwinfo->منوال_اوصاف;
        info->pitch = hwinfo->بائٹیں_فی_جائزہ_سطر;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->عدد_planes = hwinfo->نمبر_کا_Planes;
        info->bpp = hwinfo->بٹ_فی_Pixel;
        info->حافظہ_model = hwinfo->حافظہ_Model;
        info->عدد_image_صفحات = hwinfo->نمبر_کا_Image_صفحات;
        info->red_نقاب_سائز = hwinfo->Red_نقاب_سائز;
        info->red_نقاب_pos = hwinfo->Red_نقاب_Pos;
        info->green_نقاب_سائز = hwinfo->Green_نقاب_سائز;
        info->green_نقاب_pos = hwinfo->Green_نقاب_Pos;
        info->blue_نقاب_سائز = hwinfo->Blue_نقاب_سائز;
        info->blue_نقاب_pos = hwinfo->Blue_نقاب_Pos;
        info->physical_بنیاد_addr = hwinfo->Phys_بنیاد_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->منوال_اوصاف & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_سائز = hwinfo->Win_سائز;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_اوصاف = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_حافظہ(&hwinfo_seginfo);

    واپس retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ثابت SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    صحیح عدد_vesa_modes = (vinfo && vinfo->نسخہ >= 0x102) ? vinfo->عدد_modes : 0;

    برائے (صحیح mi = 0; mi < عدد_vesa_modes; mi++) {
        ثابت Uint16 modeid = vinfo->منوال_list[mi];

        SDL_Display_منوال_ڈیٹا info;
        اگر (!GetVESAModeInfo(modeid, &info)) {
            جاری;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        اگر (info.bpp == 8 && info.w == 320 && info.h == 200) {
            جاری;
        }

        اگر ((info.اوصاف & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            جاری;
        }

        اگر (!(info.اوصاف & VBE_MODEATTR_LFB) && (info.win_a_اوصاف & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            جاری;
        }

        اگر (info.عدد_planes != 1) {
            جاری; // skip planar pixel layouts.
        } ورنہ اگر (info.bpp < 8) {
            جاری; // skip anything below 8-bit.
        } ورنہ اگر (!info.w || !info.h) {
            جاری; // zero-area display mode?!
        } ورنہ اگر (!info.has_lfb && !info.win_granularity) {
            جاری; // banked mode with zero granularity would cause division by zero.
        } ورنہ اگر ((info.حافظہ_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.حافظہ_model != VBE_MEMMODEL_براہ_راست_COLOR)) {
            جاری; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        اگر (info.حافظہ_model == VBE_MEMMODEL_PACKED_PIXEL) {
            انتخاب (info.bpp) {
            حالت 8:
                format = SDL_PIXELFORMAT_INDEX8;
                توڑو;
            حالت 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                توڑو;
            حالت 16:
                format = SDL_PIXELFORMAT_RGB565;
                توڑو;
            حالت 24:
                format = SDL_PIXELFORMAT_RGB24;
                توڑو;
            حالت 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                توڑو;
            طےشدہ:
                توڑو;
            }
        } ورنہ {
            SDL_assert(info.حافظہ_model == VBE_MEMMODEL_براہ_راست_COLOR);
            ثابت Uint32 rmask = ((((Uint32)1) << info.red_نقاب_سائز) - 1) << info.red_نقاب_pos;
            ثابت Uint32 gmask = ((((Uint32)1) << info.green_نقاب_سائز) - 1) << info.green_نقاب_pos;
            ثابت Uint32 bmask = ((((Uint32)1) << info.blue_نقاب_سائز) - 1) << info.blue_نقاب_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        اگر (format == SDL_PIXELFORMAT_UNKNOWN) {
            جاری; // don't know what to do with this one.
        }

        SDL_Display_منوال_ڈیٹا *اندرونی_2 = (SDL_Display_منوال_ڈیٹا *)SDL_malloc(حجم(*اندرونی_2));
        اگر (!اندرونی_2) {
            جاری; // oof.
        }

        SDL_copyp(اندرونی_2, &info);

        SDL_Display_منوال منوال;
        SDL_zero(منوال);
        منوال.format = format;
        منوال.w = (صحیح)info.w;
        منوال.h = (صحیح)info.h;
        منوال.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        منوال.اندرونی_2 = اندرونی_2;

        اگر (!SDL_جوڑو_Fullscreen_Display_منوال(sdl_display, &منوال)) {
            SDL_free(اندرونی_2); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_منوال_ڈیٹا *اندرونی_2 = (SDL_Display_منوال_ڈیٹا *)SDL_malloc(حجم(*اندرونی_2));
        اگر (اندرونی_2) {
            SDL_zerop(اندرونی_2);
            اندرونی_2->منوال_id = VGA_منوال_13_H_SENTINEL;
            اندرونی_2->اوصاف = VBE_MODEATTR_REQUIRED;
            اندرونی_2->pitch = 320;
            اندرونی_2->w = 320;
            اندرونی_2->h = 200;
            اندرونی_2->عدد_planes = 1;
            اندرونی_2->bpp = 8;
            اندرونی_2->حافظہ_model = VBE_MEMMODEL_PACKED_PIXEL;
            اندرونی_2->عدد_image_صفحات = 0; // no page flipping in mode 13h
            اندرونی_2->physical_بنیاد_addr = 0;
            اندرونی_2->has_lfb = false;
            اندرونی_2->win_granularity = 64;
            اندرونی_2->win_سائز = 64;
            اندرونی_2->win_a_segment = VGA_منوال_13_H_SEGMENT;
            اندرونی_2->win_func_ptr = 0;
            اندرونی_2->win_a_اوصاف = VBE_WINATTR_USABLE;

            SDL_Display_منوال منوال;
            SDL_zero(منوال);
            منوال.format = SDL_PIXELFORMAT_INDEX8;
            منوال.w = 320;
            منوال.h = 200;
            منوال.pixel_density = 1.0f;
            منوال.اندرونی_2 = اندرونی_2;

            اگر (!SDL_جوڑو_Fullscreen_Display_منوال(sdl_display, &منوال)) {
                SDL_free(اندرونی_2);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    برائے (صحیح i = 0; i < sdl_display->عدد_fullscreen_modes - 1; i++) {
        برائے (صحیح j = i + 1; j < sdl_display->عدد_fullscreen_modes; j++) {
            ثابت SDL_Display_منوال *a = &sdl_display->fullscreen_modes[i];
            ثابت SDL_Display_منوال *b = &sdl_display->fullscreen_modes[j];
            bool تبادلہ = false;
            اگر (b->w > a->w) {
                تبادلہ = true;
            } ورنہ اگر (b->w == a->w) {
                اگر (b->h > a->h) {
                    تبادلہ = true;
                } ورنہ اگر (b->h == a->h) {
                    اگر (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        تبادلہ = true;
                    }
                }
            }
            اگر (تبادلہ) {
                SDL_Display_منوال tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    واپس true;
}

bool DOSVESA_سیٹ_Display_منوال(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_منوال *منوال)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    ثابت SDL_Display_منوال_ڈیٹا *modedata = منوال->اندرونی_2;

    اگر (ڈیٹا->current_منوال.اندرونی_2 && (ڈیٹا->current_منوال.اندرونی_2->منوال_id == modedata->منوال_id)) {
        واپس true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    اگر (ڈیٹا->mapping.سائز) {
        __dpmi_free_physical_address_mapping(&ڈیٹا->mapping); // dump existing video mapping.
        SDL_zero(ڈیٹا->mapping);
    }

    __dpmi_regs regs;

    اگر (modedata->منوال_id == VGA_منوال_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        ڈیٹا->banked_منوال = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&ڈیٹا->current_منوال, منوال);

        ڈیٹا->صفحہ_flip_دستیاب = false;
        ڈیٹا->current_صفحہ = 0;
        ڈیٹا->صفحہ_انحراف[0] = 0;
        ڈیٹا->صفحہ_انحراف[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_بنیاد = (Uint32)VGA_منوال_13_H_SEGMENT << 4;
            برائے (صحیح صف = 0; صف < 200; صف++) {
                dosmemput(zero_buf, 320, vga_بنیاد + صف * 320);
            }
        }

        اگر (SDL_GetMouse()->اندرونی_2 != تہی) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(منوال->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(منوال->h - 1);
            __dpmi_int(0x33, &regs);
        }

        واپس true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ثابت bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_سائز > 0 &&
                                  (modedata->win_a_اوصاف & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ثابت bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_براہ_راست_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->منوال_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    اگر (regs.x.ax != 0x004F) {
        واپس SDL_سیٹ_Error("Failed to set VESA video mode");
    }

    ڈیٹا->banked_منوال = !use_lfb;

    اگر (use_lfb) {
        ڈیٹا->mapping.پتہ = modedata->physical_بنیاد_addr;
        ڈیٹا->mapping.سائز = DOSVESA_Get_VESATotal_حافظہ();
        اگر (__dpmi_physical_address_mapping(&ڈیٹا->mapping) != 0) {
            SDL_zero(ڈیٹا->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(ڈیٹا->current_منوال);
            واپس SDL_سیٹ_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_مقصد_خطی(ڈیٹا->mapping.پتہ), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } ورنہ {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 کل_بائٹیں = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_بائٹیں = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_سائز_بائٹیں = (Uint32)modedata->win_سائز * 1024;
        Uint32 win_بنیاد = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 انحراف_2 = 0;
        صحیح current_bank = -1;
        جب (انحراف_2 < کل_بائٹیں) {
            صحیح bank = (صحیح)(انحراف_2 / win_gran_بائٹیں);
            Uint32 off_اندر_win = انحراف_2 % win_gran_بائٹیں;
            Uint32 n = win_سائز_بائٹیں - off_اندر_win;
            اگر (n > کل_بائٹیں - انحراف_2) {
                n = کل_بائٹیں - انحراف_2;
            }

            اگر (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                اگر (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } ورنہ {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            جب (written < n) {
                Uint32 chunk = n - written;
                اگر (chunk > حجم(zero_buf)) {
                    chunk = حجم(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_بنیاد + off_اندر_win + written);
                written += chunk;
            }
            انحراف_2 += n;
        }
    }

    SDL_copyp(&ڈیٹا->current_منوال, منوال);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    اگر (!ڈیٹا->banked_منوال && modedata->عدد_image_صفحات >= 1) {
        ڈیٹا->صفحہ_flip_دستیاب = true;
        ڈیٹا->current_صفحہ = 0;
        ڈیٹا->صفحہ_انحراف[0] = 0;
        ڈیٹا->صفحہ_انحراف[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_انتہا = ڈیٹا->صفحہ_انحراف[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        اگر (page1_انتہا > ڈیٹا->mapping.سائز) {
            ڈیٹا->صفحہ_flip_دستیاب = false;
            ڈیٹا->صفحہ_انحراف[1] = 0;
        } ورنہ {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_مقصد_خطی(ڈیٹا->mapping.پتہ) + ڈیٹا->صفحہ_انحراف[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } ورنہ {
        ڈیٹا->صفحہ_flip_دستیاب = false;
        ڈیٹا->current_صفحہ = 0;
        ڈیٹا->صفحہ_انحراف[0] = 0;
        ڈیٹا->صفحہ_انحراف[1] = 0;
    }

    اگر (SDL_GetMouse()->اندرونی_2 != تہی) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(منوال->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(منوال->h - 1);
        __dpmi_int(0x33, &regs);
    }

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_DOSVESA
