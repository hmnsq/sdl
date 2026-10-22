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
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_dosframebuffer_c.h"

// DOS declarations
#అన్తర్భావ "SDL_dosmodes.h"
#అన్తర్భావ "SDL_dosvideo.h"
#అన్తర్భావ <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#నిర్వచించు VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#నిర్వచించు VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#నిర్వచించు VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#నిర్వచించు VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#నిర్వచించు VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#నిర్వచించు VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#నిర్వచించు VBE_MEMMODEL_ప్రత్యక్ష_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#నిర్వచించు VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#నిర్వచించు VBE_MODELIST_చివర 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#నిర్వచించు VGA_బహుళకం_13_H_SENTINEL 0xFFEE
#నిర్వచించు VGA_బహుళకం_13_H_SEGMENT  0xA000

#సూచన pack(నెట్టు, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
రకనిర్వచనం నిర్మాణం SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_బహుళకం_Ptr; // segment:offset
    Uint16 మొత్తం_జ్ఞాపకం;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_దత్తాంశం[256];
} SDL_VESAHardwareInfo;

రకనిర్వచనం నిర్మాణం SDL_VESAModeHardwareInfo
{
    Uint16 బహుళకం_లక్షణాలు;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_కొలత;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 బైట్లు_చొప్పున_పరిశీలన_పంక్తి;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_కొలత;
    Uint8 YChar_కొలత;
    Uint8 సంఖ్య_యొక్క_Planes;
    Uint8 బిట్లు_చొప్పున_Pixel;
    Uint8 సంఖ్య_యొక్క_Banks;
    Uint8 జ్ఞాపకం_Model;
    Uint8 Bank_కొలత;
    Uint8 సంఖ్య_యొక్క_Image_పుటలు;
    Uint8 Reserved_పుట;
    Uint8 Red_ముసుగు_కొలత;
    Uint8 Red_ముసుగు_Pos;
    Uint8 Green_ముసుగు_కొలత;
    Uint8 Green_ముసుగు_Pos;
    Uint8 Blue_ముసుగు_కొలత;
    Uint8 Blue_ముసుగు_Pos;
    Uint8 Reserved_ముసుగు_కొలత;
    Uint8 Reserved_ముసుగు_Pos;
    Uint8 ప్రత్యక్ష_Color_బహుళకం_Info;
    Uint32 Phys_పునాది_Ptr;
    Uint32 Off_Screen_Mem_స్థానభ్రంశం;
    Uint16 Off_Screen_Mem_కొలత;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#సూచన pack(తీయి)

రకనిర్వచనం నిర్మాణం SDL_VESAInfo
{
    Uint16 సంస్కరణ;              // 0x200 == 2.0, etc.
    Uint32 మొత్తం_జ్ఞాపకం_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *బహుళకం_list;           // copied out of conventional memory before freeing
    పూర్ణాంకం అంకె_modes;
    Uint16 oem_software_revision;
    అక్షరం *oem_string;
    అక్షరం *oem_vendor;
    అక్షరం *oem_లబ్ధం;
    అక్షరం *oem_revision;
} SDL_VESAInfo;

స్థిర SDL_VESAInfo *vesa_info = ఖాళీ;

శూన్య DOSVESA_FreeVESAInfo(శూన్య)
{
    ఒకవేళ (vesa_info) {
        SDL_free(vesa_info->బహుళకం_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_లబ్ధం);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = ఖాళీ;
    }
}

స్థిర స్థిరరాశి SDL_VESAInfo *GetVESAInfo(శూన్య)
{
    ఒకవేళ (vesa_info) {
        తిరిగి vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_జ్ఞాపకం(పరిమాణం(*hwinfo), &hwinfo_seginfo);
    ఒకవేళ (!hwinfo) {
        తిరిగి ఖాళీ;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_రేఖీయ_గమ్యం_Physical(hwinfo) / 16;
    regs.x.di = DOS_రేఖీయ_గమ్యం_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    ఒకవేళ ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_సమితి_Error("VESA video not supported on this system");
    } లేకపోతే {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, పరిమాణం(*vesa_info));
        ఒకవేళ (vesa_info) {
            vesa_info->సంస్కరణ = hwinfo->VESAVersion;
            vesa_info->మొత్తం_జ్ఞాపకం_2 = ((Uint32)hwinfo->మొత్తం_జ్ఞాపకం) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_బహుళకం_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_లబ్ధం = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                పూర్ణాంకం లెక్క = 0;
                అయితే (DOS_PeekUint16(segoffset + లెక్క * పరిమాణం(Uint16)) != VBE_MODELIST_చివర) {
                    లెక్క++;
                    ఒకవేళ (లెక్క > 64)
                        ఆపు; // sanity limit
                }
                vesa_info->అంకె_modes = లెక్క;
                vesa_info->బహుళకం_list = (Uint16 *)SDL_malloc(లెక్క * పరిమాణం(Uint16));
                ఒకవేళ (vesa_info->బహుళకం_list) {
                    కొరకు (పూర్ణాంకం i = 0; i < లెక్క; i++) {
                        vesa_info->బహుళకం_list[i] = DOS_PeekUint16(segoffset + i * పరిమాణం(Uint16));
                    }
                } లేకపోతే {
                    vesa_info->అంకె_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_జ్ఞాపకం(&hwinfo_seginfo);

    తిరిగి vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
స్థిర bool DetectVGA(శూన్య)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    తిరిగి ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(శూన్య)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    ఒకవేళ (!DetectVGA()) {
        తిరిగి SDL_సమితి_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (శూన్య)GetVESAInfo();

    తిరిగి true;
}

స్థిరరాశి అక్షరం *DOSVESA_GetGPUName(శూన్య)
{
    స్థిరరాశి SDL_VESAInfo *vinfo = GetVESAInfo();
    ఒకవేళ (!vinfo) {
        తిరిగి "VGA";
    }

    ఒకవేళ (vinfo->oem_లబ్ధం && *vinfo->oem_లబ్ధం) {
        తిరిగి vinfo->oem_లబ్ధం;
    }
    ఒకవేళ (vinfo->oem_vendor && *vinfo->oem_vendor) {
        తిరిగి vinfo->oem_vendor;
    }
    ఒకవేళ (vinfo->oem_string && *vinfo->oem_string) {
        తిరిగి vinfo->oem_string;
    }

    తిరిగి "VESA";
}

Uint32 DOSVESA_Get_VESATotal_జ్ఞాపకం(శూన్య)
{
    స్థిరరాశి SDL_VESAInfo *info = GetVESAInfo();
    తిరిగి info ? info->మొత్తం_జ్ఞాపకం_2 : 0;
}

స్థిర bool GetVESAModeInfo(Uint16 బహుళకం_id, SDL_Display_బహుళకం_దత్తాంశం *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_జ్ఞాపకం(పరిమాణం(*hwinfo), &hwinfo_seginfo);
    ఒకవేళ (!hwinfo) {
        తిరిగి false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_రేఖీయ_గమ్యం_Physical(hwinfo) / 16;
    regs.x.di = DOS_రేఖీయ_గమ్యం_Physical(hwinfo) & 0xF;
    regs.x.cx = బహుళకం_id;
    __dpmi_int(0x10, &regs);

    స్థిరరాశి bool retval = (regs.x.ax == 0x004F);
    ఒకవేళ (retval) {
        SDL_zerop(info);
        info->బహుళకం_id = బహుళకం_id;
        info->లక్షణాలు = hwinfo->బహుళకం_లక్షణాలు;
        info->pitch = hwinfo->బైట్లు_చొప్పున_పరిశీలన_పంక్తి;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->అంకె_planes = hwinfo->సంఖ్య_యొక్క_Planes;
        info->bpp = hwinfo->బిట్లు_చొప్పున_Pixel;
        info->జ్ఞాపకం_model = hwinfo->జ్ఞాపకం_Model;
        info->అంకె_image_పుటలు = hwinfo->సంఖ్య_యొక్క_Image_పుటలు;
        info->red_ముసుగు_కొలత = hwinfo->Red_ముసుగు_కొలత;
        info->red_ముసుగు_pos = hwinfo->Red_ముసుగు_Pos;
        info->green_ముసుగు_కొలత = hwinfo->Green_ముసుగు_కొలత;
        info->green_ముసుగు_pos = hwinfo->Green_ముసుగు_Pos;
        info->blue_ముసుగు_కొలత = hwinfo->Blue_ముసుగు_కొలత;
        info->blue_ముసుగు_pos = hwinfo->Blue_ముసుగు_Pos;
        info->physical_పునాది_addr = hwinfo->Phys_పునాది_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->బహుళకం_లక్షణాలు & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_కొలత = hwinfo->Win_కొలత;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_లక్షణాలు = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_జ్ఞాపకం(&hwinfo_seginfo);

    తిరిగి retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    స్థిరరాశి SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    పూర్ణాంకం అంకె_vesa_modes = (vinfo && vinfo->సంస్కరణ >= 0x102) ? vinfo->అంకె_modes : 0;

    కొరకు (పూర్ణాంకం mi = 0; mi < అంకె_vesa_modes; mi++) {
        స్థిరరాశి Uint16 modeid = vinfo->బహుళకం_list[mi];

        SDL_Display_బహుళకం_దత్తాంశం info;
        ఒకవేళ (!GetVESAModeInfo(modeid, &info)) {
            కొనసాగు;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        ఒకవేళ (info.bpp == 8 && info.w == 320 && info.h == 200) {
            కొనసాగు;
        }

        ఒకవేళ ((info.లక్షణాలు & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            కొనసాగు;
        }

        ఒకవేళ (!(info.లక్షణాలు & VBE_MODEATTR_LFB) && (info.win_a_లక్షణాలు & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            కొనసాగు;
        }

        ఒకవేళ (info.అంకె_planes != 1) {
            కొనసాగు; // skip planar pixel layouts.
        } లేకపోతే ఒకవేళ (info.bpp < 8) {
            కొనసాగు; // skip anything below 8-bit.
        } లేకపోతే ఒకవేళ (!info.w || !info.h) {
            కొనసాగు; // zero-area display mode?!
        } లేకపోతే ఒకవేళ (!info.has_lfb && !info.win_granularity) {
            కొనసాగు; // banked mode with zero granularity would cause division by zero.
        } లేకపోతే ఒకవేళ ((info.జ్ఞాపకం_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.జ్ఞాపకం_model != VBE_MEMMODEL_ప్రత్యక్ష_COLOR)) {
            కొనసాగు; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        ఒకవేళ (info.జ్ఞాపకం_model == VBE_MEMMODEL_PACKED_PIXEL) {
            ఎంపిక (info.bpp) {
            స్థితి 8:
                format = SDL_PIXELFORMAT_INDEX8;
                ఆపు;
            స్థితి 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                ఆపు;
            స్థితి 16:
                format = SDL_PIXELFORMAT_RGB565;
                ఆపు;
            స్థితి 24:
                format = SDL_PIXELFORMAT_RGB24;
                ఆపు;
            స్థితి 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                ఆపు;
            అప్రమేయ:
                ఆపు;
            }
        } లేకపోతే {
            SDL_assert(info.జ్ఞాపకం_model == VBE_MEMMODEL_ప్రత్యక్ష_COLOR);
            స్థిరరాశి Uint32 rmask = ((((Uint32)1) << info.red_ముసుగు_కొలత) - 1) << info.red_ముసుగు_pos;
            స్థిరరాశి Uint32 gmask = ((((Uint32)1) << info.green_ముసుగు_కొలత) - 1) << info.green_ముసుగు_pos;
            స్థిరరాశి Uint32 bmask = ((((Uint32)1) << info.blue_ముసుగు_కొలత) - 1) << info.blue_ముసుగు_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        ఒకవేళ (format == SDL_PIXELFORMAT_UNKNOWN) {
            కొనసాగు; // don't know what to do with this one.
        }

        SDL_Display_బహుళకం_దత్తాంశం *అంతర్గత = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_malloc(పరిమాణం(*అంతర్గత));
        ఒకవేళ (!అంతర్గత) {
            కొనసాగు; // oof.
        }

        SDL_copyp(అంతర్గత, &info);

        SDL_Display_బహుళకం బహుళకం;
        SDL_zero(బహుళకం);
        బహుళకం.format = format;
        బహుళకం.w = (పూర్ణాంకం)info.w;
        బహుళకం.h = (పూర్ణాంకం)info.h;
        బహుళకం.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        బహుళకం.అంతర్గత = అంతర్గత;

        ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(sdl_display, &బహుళకం)) {
            SDL_free(అంతర్గత); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_బహుళకం_దత్తాంశం *అంతర్గత = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_malloc(పరిమాణం(*అంతర్గత));
        ఒకవేళ (అంతర్గత) {
            SDL_zerop(అంతర్గత);
            అంతర్గత->బహుళకం_id = VGA_బహుళకం_13_H_SENTINEL;
            అంతర్గత->లక్షణాలు = VBE_MODEATTR_REQUIRED;
            అంతర్గత->pitch = 320;
            అంతర్గత->w = 320;
            అంతర్గత->h = 200;
            అంతర్గత->అంకె_planes = 1;
            అంతర్గత->bpp = 8;
            అంతర్గత->జ్ఞాపకం_model = VBE_MEMMODEL_PACKED_PIXEL;
            అంతర్గత->అంకె_image_పుటలు = 0; // no page flipping in mode 13h
            అంతర్గత->physical_పునాది_addr = 0;
            అంతర్గత->has_lfb = false;
            అంతర్గత->win_granularity = 64;
            అంతర్గత->win_కొలత = 64;
            అంతర్గత->win_a_segment = VGA_బహుళకం_13_H_SEGMENT;
            అంతర్గత->win_func_ptr = 0;
            అంతర్గత->win_a_లక్షణాలు = VBE_WINATTR_USABLE;

            SDL_Display_బహుళకం బహుళకం;
            SDL_zero(బహుళకం);
            బహుళకం.format = SDL_PIXELFORMAT_INDEX8;
            బహుళకం.w = 320;
            బహుళకం.h = 200;
            బహుళకం.pixel_density = 1.0f;
            బహుళకం.అంతర్గత = అంతర్గత;

            ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(sdl_display, &బహుళకం)) {
                SDL_free(అంతర్గత);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    కొరకు (పూర్ణాంకం i = 0; i < sdl_display->అంకె_fullscreen_modes - 1; i++) {
        కొరకు (పూర్ణాంకం j = i + 1; j < sdl_display->అంకె_fullscreen_modes; j++) {
            స్థిరరాశి SDL_Display_బహుళకం *a = &sdl_display->fullscreen_modes[i];
            స్థిరరాశి SDL_Display_బహుళకం *b = &sdl_display->fullscreen_modes[j];
            bool మార్పిడి = false;
            ఒకవేళ (b->w > a->w) {
                మార్పిడి = true;
            } లేకపోతే ఒకవేళ (b->w == a->w) {
                ఒకవేళ (b->h > a->h) {
                    మార్పిడి = true;
                } లేకపోతే ఒకవేళ (b->h == a->h) {
                    ఒకవేళ (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        మార్పిడి = true;
                    }
                }
            }
            ఒకవేళ (మార్పిడి) {
                SDL_Display_బహుళకం tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    తిరిగి true;
}

bool DOSVESA_సమితి_Display_బహుళకం(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;
    స్థిరరాశి SDL_Display_బహుళకం_దత్తాంశం *modedata = బహుళకం->అంతర్గత;

    ఒకవేళ (దత్తాంశం->current_బహుళకం.అంతర్గత && (దత్తాంశం->current_బహుళకం.అంతర్గత->బహుళకం_id == modedata->బహుళకం_id)) {
        తిరిగి true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    ఒకవేళ (దత్తాంశం->mapping.కొలత) {
        __dpmi_free_physical_address_mapping(&దత్తాంశం->mapping); // dump existing video mapping.
        SDL_zero(దత్తాంశం->mapping);
    }

    __dpmi_regs regs;

    ఒకవేళ (modedata->బహుళకం_id == VGA_బహుళకం_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        దత్తాంశం->banked_బహుళకం = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&దత్తాంశం->current_బహుళకం, బహుళకం);

        దత్తాంశం->పుట_flip_అందుబాటు = false;
        దత్తాంశం->current_పుట = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[0] = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_పునాది = (Uint32)VGA_బహుళకం_13_H_SEGMENT << 4;
            కొరకు (పూర్ణాంకం అడ్డువరుస = 0; అడ్డువరుస < 200; అడ్డువరుస++) {
                dosmemput(zero_buf, 320, vga_పునాది + అడ్డువరుస * 320);
            }
        }

        ఒకవేళ (SDL_GetMouse()->అంతర్గత != ఖాళీ) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(బహుళకం->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(బహుళకం->h - 1);
            __dpmi_int(0x33, &regs);
        }

        తిరిగి true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    స్థిరరాశి bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_కొలత > 0 &&
                                  (modedata->win_a_లక్షణాలు & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    స్థిరరాశి bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_ప్రత్యక్ష_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->బహుళకం_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    ఒకవేళ (regs.x.ax != 0x004F) {
        తిరిగి SDL_సమితి_Error("Failed to set VESA video mode");
    }

    దత్తాంశం->banked_బహుళకం = !use_lfb;

    ఒకవేళ (use_lfb) {
        దత్తాంశం->mapping.చిరునామా = modedata->physical_పునాది_addr;
        దత్తాంశం->mapping.కొలత = DOSVESA_Get_VESATotal_జ్ఞాపకం();
        ఒకవేళ (__dpmi_physical_address_mapping(&దత్తాంశం->mapping) != 0) {
            SDL_zero(దత్తాంశం->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(దత్తాంశం->current_బహుళకం);
            తిరిగి SDL_సమితి_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_గమ్యం_రేఖీయ(దత్తాంశం->mapping.చిరునామా), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } లేకపోతే {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 మొత్తం_బైట్లు = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_బైట్లు = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_కొలత_బైట్లు = (Uint32)modedata->win_కొలత * 1024;
        Uint32 win_పునాది = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 స్థానభ్రంశం_2 = 0;
        పూర్ణాంకం current_bank = -1;
        అయితే (స్థానభ్రంశం_2 < మొత్తం_బైట్లు) {
            పూర్ణాంకం bank = (పూర్ణాంకం)(స్థానభ్రంశం_2 / win_gran_బైట్లు);
            Uint32 off_లోపల_win = స్థానభ్రంశం_2 % win_gran_బైట్లు;
            Uint32 n = win_కొలత_బైట్లు - off_లోపల_win;
            ఒకవేళ (n > మొత్తం_బైట్లు - స్థానభ్రంశం_2) {
                n = మొత్తం_బైట్లు - స్థానభ్రంశం_2;
            }

            ఒకవేళ (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                ఒకవేళ (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } లేకపోతే {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            అయితే (written < n) {
                Uint32 chunk = n - written;
                ఒకవేళ (chunk > పరిమాణం(zero_buf)) {
                    chunk = పరిమాణం(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_పునాది + off_లోపల_win + written);
                written += chunk;
            }
            స్థానభ్రంశం_2 += n;
        }
    }

    SDL_copyp(&దత్తాంశం->current_బహుళకం, బహుళకం);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    ఒకవేళ (!దత్తాంశం->banked_బహుళకం && modedata->అంకె_image_పుటలు >= 1) {
        దత్తాంశం->పుట_flip_అందుబాటు = true;
        దత్తాంశం->current_పుట = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[0] = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_చివర = దత్తాంశం->పుట_స్థానభ్రంశం[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        ఒకవేళ (page1_చివర > దత్తాంశం->mapping.కొలత) {
            దత్తాంశం->పుట_flip_అందుబాటు = false;
            దత్తాంశం->పుట_స్థానభ్రంశం[1] = 0;
        } లేకపోతే {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_గమ్యం_రేఖీయ(దత్తాంశం->mapping.చిరునామా) + దత్తాంశం->పుట_స్థానభ్రంశం[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } లేకపోతే {
        దత్తాంశం->పుట_flip_అందుబాటు = false;
        దత్తాంశం->current_పుట = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[0] = 0;
        దత్తాంశం->పుట_స్థానభ్రంశం[1] = 0;
    }

    ఒకవేళ (SDL_GetMouse()->అంతర్గత != ఖాళీ) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(బహుళకం->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(బహుళకం->h - 1);
        __dpmi_int(0x33, &regs);
    }

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_DOSVESA
