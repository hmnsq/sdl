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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosframebuffer_c.h"

// DOS declarations
#ಅನ್ತರ್ಭಾವ "SDL_dosmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosvideo.h"
#ಅನ್ತರ್ಭಾವ <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MEMMODEL_ನೇರ_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_MODELIST_ಕೊನೆ 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_ಬಹುಲಕ_13_H_SENTINEL 0xFFEE
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_ಬಹುಲಕ_13_H_SEGMENT  0xA000

#ಸೂಚನೆ pack(ತಳ್ಳು, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_ಬಹುಲಕ_Ptr; // segment:offset
    Uint16 ಒಟ್ಟು_ಸ್ಮರಣೆ;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_ದತ್ತಾಂಶ[256];
} SDL_VESAHardwareInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_VESAModeHardwareInfo
{
    Uint16 ಬಹುಲಕ_ಗುಣಲಕ್ಷಣಗಳು;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_ಗಾತ್ರ;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 ಬೈಟುಗಳು_ಪ್ರತಿ_ಪರಿಶೀಲನೆ_ಸಾಲು;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_ಗಾತ್ರ;
    Uint8 YChar_ಗಾತ್ರ;
    Uint8 ಸಂಖ್ಯೆ_ದ_Planes;
    Uint8 ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_Pixel;
    Uint8 ಸಂಖ್ಯೆ_ದ_Banks;
    Uint8 ಸ್ಮರಣೆ_Model;
    Uint8 Bank_ಗಾತ್ರ;
    Uint8 ಸಂಖ್ಯೆ_ದ_Image_ಪುಟಗಳು;
    Uint8 Reserved_ಪುಟ;
    Uint8 Red_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 Red_ಮುಖವಾಡ_Pos;
    Uint8 Green_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 Green_ಮುಖವಾಡ_Pos;
    Uint8 Blue_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 Blue_ಮುಖವಾಡ_Pos;
    Uint8 Reserved_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 Reserved_ಮುಖವಾಡ_Pos;
    Uint8 ನೇರ_Color_ಬಹುಲಕ_Info;
    Uint32 Phys_ತಳ_Ptr;
    Uint32 Off_Screen_Mem_ಸ್ಥಾನಾಂತರ;
    Uint16 Off_Screen_Mem_ಗಾತ್ರ;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#ಸೂಚನೆ pack(ತೆಗೆ)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_VESAInfo
{
    Uint16 ಆವೃತ್ತಿ;              // 0x200 == 2.0, etc.
    Uint32 ಒಟ್ಟು_ಸ್ಮರಣೆ_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *ಬಹುಲಕ_list;           // copied out of conventional memory before freeing
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_modes;
    Uint16 oem_software_revision;
    ಅಕ್ಷರ *oem_string;
    ಅಕ್ಷರ *oem_vendor;
    ಅಕ್ಷರ *oem_ಗುಣಲಬ್ಧ;
    ಅಕ್ಷರ *oem_revision;
} SDL_VESAInfo;

ಸ್ಥಿರ SDL_VESAInfo *vesa_info = ಖಾಲಿ;

ಶೂನ್ಯ DOSVESA_FreeVESAInfo(ಶೂನ್ಯ)
{
    ಆದರೆ (vesa_info) {
        SDL_free(vesa_info->ಬಹುಲಕ_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_ಗುಣಲಬ್ಧ);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_VESAInfo *GetVESAInfo(ಶೂನ್ಯ)
{
    ಆದರೆ (vesa_info) {
        ಹಿಂತಿರುಗಿ vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_ಸ್ಮರಣೆ(ಗಾತ್ರ(*hwinfo), &hwinfo_seginfo);
    ಆದರೆ (!hwinfo) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(hwinfo) / 16;
    regs.x.di = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    ಆದರೆ ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_ಗಣ_Error("VESA video not supported on this system");
    } ಇಲ್ಲದಿದ್ದರೆ {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, ಗಾತ್ರ(*vesa_info));
        ಆದರೆ (vesa_info) {
            vesa_info->ಆವೃತ್ತಿ = hwinfo->VESAVersion;
            vesa_info->ಒಟ್ಟು_ಸ್ಮರಣೆ_2 = ((Uint32)hwinfo->ಒಟ್ಟು_ಸ್ಮರಣೆ) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_ಬಹುಲಕ_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_ಗುಣಲಬ್ಧ = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;
                ಆಗ (DOS_PeekUint16(segoffset + ಎಣಿಕೆ_2 * ಗಾತ್ರ(Uint16)) != VBE_MODELIST_ಕೊನೆ) {
                    ಎಣಿಕೆ_2++;
                    ಆದರೆ (ಎಣಿಕೆ_2 > 64)
                        ನಿಲ್ಲಿಸು; // sanity limit
                }
                vesa_info->ಅಂಕೆ_modes = ಎಣಿಕೆ_2;
                vesa_info->ಬಹುಲಕ_list = (Uint16 *)SDL_malloc(ಎಣಿಕೆ_2 * ಗಾತ್ರ(Uint16));
                ಆದರೆ (vesa_info->ಬಹುಲಕ_list) {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; i++) {
                        vesa_info->ಬಹುಲಕ_list[i] = DOS_PeekUint16(segoffset + i * ಗಾತ್ರ(Uint16));
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    vesa_info->ಅಂಕೆ_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_ಸ್ಮರಣೆ(&hwinfo_seginfo);

    ಹಿಂತಿರುಗಿ vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
ಸ್ಥಿರ bool DetectVGA(ಶೂನ್ಯ)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    ಹಿಂತಿರುಗಿ ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(ಶೂನ್ಯ)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    ಆದರೆ (!DetectVGA()) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (ಶೂನ್ಯ)GetVESAInfo();

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *DOSVESA_GetGPUName(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ SDL_VESAInfo *vinfo = GetVESAInfo();
    ಆದರೆ (!vinfo) {
        ಹಿಂತಿರುಗಿ "VGA";
    }

    ಆದರೆ (vinfo->oem_ಗುಣಲಬ್ಧ && *vinfo->oem_ಗುಣಲಬ್ಧ) {
        ಹಿಂತಿರುಗಿ vinfo->oem_ಗುಣಲಬ್ಧ;
    }
    ಆದರೆ (vinfo->oem_vendor && *vinfo->oem_vendor) {
        ಹಿಂತಿರುಗಿ vinfo->oem_vendor;
    }
    ಆದರೆ (vinfo->oem_string && *vinfo->oem_string) {
        ಹಿಂತಿರುಗಿ vinfo->oem_string;
    }

    ಹಿಂತಿರುಗಿ "VESA";
}

Uint32 DOSVESA_Get_VESATotal_ಸ್ಮರಣೆ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ SDL_VESAInfo *info = GetVESAInfo();
    ಹಿಂತಿರುಗಿ info ? info->ಒಟ್ಟು_ಸ್ಮರಣೆ_2 : 0;
}

ಸ್ಥಿರ bool GetVESAModeInfo(Uint16 ಬಹುಲಕ_id, SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_ಸ್ಮರಣೆ(ಗಾತ್ರ(*hwinfo), &hwinfo_seginfo);
    ಆದರೆ (!hwinfo) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(hwinfo) / 16;
    regs.x.di = DOS_ರೇಖೀಯ_ಗಮ್ಯ_Physical(hwinfo) & 0xF;
    regs.x.cx = ಬಹುಲಕ_id;
    __dpmi_int(0x10, &regs);

    ಸ್ಥಿರಾಂಕ bool retval = (regs.x.ax == 0x004F);
    ಆದರೆ (retval) {
        SDL_zerop(info);
        info->ಬಹುಲಕ_id = ಬಹುಲಕ_id;
        info->ಗುಣಲಕ್ಷಣಗಳು = hwinfo->ಬಹುಲಕ_ಗುಣಲಕ್ಷಣಗಳು;
        info->pitch = hwinfo->ಬೈಟುಗಳು_ಪ್ರತಿ_ಪರಿಶೀಲನೆ_ಸಾಲು;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->ಅಂಕೆ_planes = hwinfo->ಸಂಖ್ಯೆ_ದ_Planes;
        info->bpp = hwinfo->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_Pixel;
        info->ಸ್ಮರಣೆ_model = hwinfo->ಸ್ಮರಣೆ_Model;
        info->ಅಂಕೆ_image_ಪುಟಗಳು = hwinfo->ಸಂಖ್ಯೆ_ದ_Image_ಪುಟಗಳು;
        info->red_ಮುಖವಾಡ_ಗಾತ್ರ = hwinfo->Red_ಮುಖವಾಡ_ಗಾತ್ರ;
        info->red_ಮುಖವಾಡ_pos = hwinfo->Red_ಮುಖವಾಡ_Pos;
        info->green_ಮುಖವಾಡ_ಗಾತ್ರ = hwinfo->Green_ಮುಖವಾಡ_ಗಾತ್ರ;
        info->green_ಮುಖವಾಡ_pos = hwinfo->Green_ಮುಖವಾಡ_Pos;
        info->blue_ಮುಖವಾಡ_ಗಾತ್ರ = hwinfo->Blue_ಮುಖವಾಡ_ಗಾತ್ರ;
        info->blue_ಮುಖವಾಡ_pos = hwinfo->Blue_ಮುಖವಾಡ_Pos;
        info->physical_ತಳ_addr = hwinfo->Phys_ತಳ_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->ಬಹುಲಕ_ಗುಣಲಕ್ಷಣಗಳು & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_ಗಾತ್ರ = hwinfo->Win_ಗಾತ್ರ;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_ಗುಣಲಕ್ಷಣಗಳು = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_ಸ್ಮರಣೆ(&hwinfo_seginfo);

    ಹಿಂತಿರುಗಿ retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ಸ್ಥಿರಾಂಕ SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_vesa_modes = (vinfo && vinfo->ಆವೃತ್ತಿ >= 0x102) ? vinfo->ಅಂಕೆ_modes : 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ mi = 0; mi < ಅಂಕೆ_vesa_modes; mi++) {
        ಸ್ಥಿರಾಂಕ Uint16 modeid = vinfo->ಬಹುಲಕ_list[mi];

        SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ info;
        ಆದರೆ (!GetVESAModeInfo(modeid, &info)) {
            ಮುಂದುವರಿ;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        ಆದರೆ (info.bpp == 8 && info.w == 320 && info.h == 200) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ ((info.ಗುಣಲಕ್ಷಣಗಳು & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (!(info.ಗುಣಲಕ್ಷಣಗಳು & VBE_MODEATTR_LFB) && (info.win_a_ಗುಣಲಕ್ಷಣಗಳು & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (info.ಅಂಕೆ_planes != 1) {
            ಮುಂದುವರಿ; // skip planar pixel layouts.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (info.bpp < 8) {
            ಮುಂದುವರಿ; // skip anything below 8-bit.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!info.w || !info.h) {
            ಮುಂದುವರಿ; // zero-area display mode?!
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!info.has_lfb && !info.win_granularity) {
            ಮುಂದುವರಿ; // banked mode with zero granularity would cause division by zero.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((info.ಸ್ಮರಣೆ_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.ಸ್ಮರಣೆ_model != VBE_MEMMODEL_ನೇರ_COLOR)) {
            ಮುಂದುವರಿ; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        ಆದರೆ (info.ಸ್ಮರಣೆ_model == VBE_MEMMODEL_PACKED_PIXEL) {
            ಆಯ್ಕೆ (info.bpp) {
            ಸ್ಥಿತಿ 8:
                format = SDL_PIXELFORMAT_INDEX8;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 16:
                format = SDL_PIXELFORMAT_RGB565;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 24:
                format = SDL_PIXELFORMAT_RGB24;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_assert(info.ಸ್ಮರಣೆ_model == VBE_MEMMODEL_ನೇರ_COLOR);
            ಸ್ಥಿರಾಂಕ Uint32 rmask = ((((Uint32)1) << info.red_ಮುಖವಾಡ_ಗಾತ್ರ) - 1) << info.red_ಮುಖವಾಡ_pos;
            ಸ್ಥಿರಾಂಕ Uint32 gmask = ((((Uint32)1) << info.green_ಮುಖವಾಡ_ಗಾತ್ರ) - 1) << info.green_ಮುಖವಾಡ_pos;
            ಸ್ಥಿರಾಂಕ Uint32 bmask = ((((Uint32)1) << info.blue_ಮುಖವಾಡ_ಗಾತ್ರ) - 1) << info.blue_ಮುಖವಾಡ_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        ಆದರೆ (format == SDL_PIXELFORMAT_UNKNOWN) {
            ಮುಂದುವರಿ; // don't know what to do with this one.
        }

        SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_malloc(ಗಾತ್ರ(*ಆಂತರಿಕ));
        ಆದರೆ (!ಆಂತರಿಕ) {
            ಮುಂದುವರಿ; // oof.
        }

        SDL_copyp(ಆಂತರಿಕ, &info);

        SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
        SDL_zero(ಬಹುಲಕ);
        ಬಹುಲಕ.format = format;
        ಬಹುಲಕ.w = (ಪೂರ್ಣಾಂಕ)info.w;
        ಬಹುಲಕ.h = (ಪೂರ್ಣಾಂಕ)info.h;
        ಬಹುಲಕ.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        ಬಹುಲಕ.ಆಂತರಿಕ = ಆಂತರಿಕ;

        ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(sdl_display, &ಬಹುಲಕ)) {
            SDL_free(ಆಂತರಿಕ); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_malloc(ಗಾತ್ರ(*ಆಂತರಿಕ));
        ಆದರೆ (ಆಂತರಿಕ) {
            SDL_zerop(ಆಂತರಿಕ);
            ಆಂತರಿಕ->ಬಹುಲಕ_id = VGA_ಬಹುಲಕ_13_H_SENTINEL;
            ಆಂತರಿಕ->ಗುಣಲಕ್ಷಣಗಳು = VBE_MODEATTR_REQUIRED;
            ಆಂತರಿಕ->pitch = 320;
            ಆಂತರಿಕ->w = 320;
            ಆಂತರಿಕ->h = 200;
            ಆಂತರಿಕ->ಅಂಕೆ_planes = 1;
            ಆಂತರಿಕ->bpp = 8;
            ಆಂತರಿಕ->ಸ್ಮರಣೆ_model = VBE_MEMMODEL_PACKED_PIXEL;
            ಆಂತರಿಕ->ಅಂಕೆ_image_ಪುಟಗಳು = 0; // no page flipping in mode 13h
            ಆಂತರಿಕ->physical_ತಳ_addr = 0;
            ಆಂತರಿಕ->has_lfb = false;
            ಆಂತರಿಕ->win_granularity = 64;
            ಆಂತರಿಕ->win_ಗಾತ್ರ = 64;
            ಆಂತರಿಕ->win_a_segment = VGA_ಬಹುಲಕ_13_H_SEGMENT;
            ಆಂತರಿಕ->win_func_ptr = 0;
            ಆಂತರಿಕ->win_a_ಗುಣಲಕ್ಷಣಗಳು = VBE_WINATTR_USABLE;

            SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
            SDL_zero(ಬಹುಲಕ);
            ಬಹುಲಕ.format = SDL_PIXELFORMAT_INDEX8;
            ಬಹುಲಕ.w = 320;
            ಬಹುಲಕ.h = 200;
            ಬಹುಲಕ.pixel_density = 1.0f;
            ಬಹುಲಕ.ಆಂತರಿಕ = ಆಂತರಿಕ;

            ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(sdl_display, &ಬಹುಲಕ)) {
                SDL_free(ಆಂತರಿಕ);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < sdl_display->ಅಂಕೆ_fullscreen_modes - 1; i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = i + 1; j < sdl_display->ಅಂಕೆ_fullscreen_modes; j++) {
            ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *a = &sdl_display->fullscreen_modes[i];
            ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *b = &sdl_display->fullscreen_modes[j];
            bool ಅದಲುಬದಲು = false;
            ಆದರೆ (b->w > a->w) {
                ಅದಲುಬದಲು = true;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (b->w == a->w) {
                ಆದರೆ (b->h > a->h) {
                    ಅದಲುಬದಲು = true;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (b->h == a->h) {
                    ಆದರೆ (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        ಅದಲುಬದಲು = true;
                    }
                }
            }
            ಆದರೆ (ಅದಲುಬದಲು) {
                SDL_Display_ಬಹುಲಕ tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool DOSVESA_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = ಬಹುಲಕ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->current_ಬಹುಲಕ.ಆಂತರಿಕ && (ದತ್ತಾಂಶ->current_ಬಹುಲಕ.ಆಂತರಿಕ->ಬಹುಲಕ_id == modedata->ಬಹುಲಕ_id)) {
        ಹಿಂತಿರುಗಿ true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    ಆದರೆ (ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2) {
        __dpmi_free_physical_address_mapping(&ದತ್ತಾಂಶ->mapping); // dump existing video mapping.
        SDL_zero(ದತ್ತಾಂಶ->mapping);
    }

    __dpmi_regs regs;

    ಆದರೆ (modedata->ಬಹುಲಕ_id == VGA_ಬಹುಲಕ_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        ದತ್ತಾಂಶ->banked_ಬಹುಲಕ = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&ದತ್ತಾಂಶ->current_ಬಹುಲಕ, ಬಹುಲಕ);

        ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ = false;
        ದತ್ತಾಂಶ->current_ಪುಟ = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[0] = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_ತಳ = (Uint32)VGA_ಬಹುಲಕ_13_H_SEGMENT << 4;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < 200; ಅಡ್ಡಸಾಲು++) {
                dosmemput(zero_buf, 320, vga_ತಳ + ಅಡ್ಡಸಾಲು * 320);
            }
        }

        ಆದರೆ (SDL_GetMouse()->ಆಂತರಿಕ != ಖಾಲಿ) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ಬಹುಲಕ->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ಬಹುಲಕ->h - 1);
            __dpmi_int(0x33, &regs);
        }

        ಹಿಂತಿರುಗಿ true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ಸ್ಥಿರಾಂಕ bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_ಗಾತ್ರ > 0 &&
                                  (modedata->win_a_ಗುಣಲಕ್ಷಣಗಳು & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ಸ್ಥಿರಾಂಕ bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_ನೇರ_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->ಬಹುಲಕ_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    ಆದರೆ (regs.x.ax != 0x004F) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to set VESA video mode");
    }

    ದತ್ತಾಂಶ->banked_ಬಹುಲಕ = !use_lfb;

    ಆದರೆ (use_lfb) {
        ದತ್ತಾಂಶ->mapping.ವಿಳಾಸ = modedata->physical_ತಳ_addr;
        ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2 = DOSVESA_Get_VESATotal_ಸ್ಮರಣೆ();
        ಆದರೆ (__dpmi_physical_address_mapping(&ದತ್ತಾಂಶ->mapping) != 0) {
            SDL_zero(ದತ್ತಾಂಶ->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(ದತ್ತಾಂಶ->current_ಬಹುಲಕ);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(ದತ್ತಾಂಶ->mapping.ವಿಳಾಸ), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 ಒಟ್ಟು_ಬೈಟುಗಳು = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_ಬೈಟುಗಳು = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_ಗಾತ್ರ_ಬೈಟುಗಳು = (Uint32)modedata->win_ಗಾತ್ರ * 1024;
        Uint32 win_ತಳ = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 ಸ್ಥಾನಾಂತರ_2 = 0;
        ಪೂರ್ಣಾಂಕ current_bank = -1;
        ಆಗ (ಸ್ಥಾನಾಂತರ_2 < ಒಟ್ಟು_ಬೈಟುಗಳು) {
            ಪೂರ್ಣಾಂಕ bank = (ಪೂರ್ಣಾಂಕ)(ಸ್ಥಾನಾಂತರ_2 / win_gran_ಬೈಟುಗಳು);
            Uint32 off_ಒಳ_win = ಸ್ಥಾನಾಂತರ_2 % win_gran_ಬೈಟುಗಳು;
            Uint32 n = win_ಗಾತ್ರ_ಬೈಟುಗಳು - off_ಒಳ_win;
            ಆದರೆ (n > ಒಟ್ಟು_ಬೈಟುಗಳು - ಸ್ಥಾನಾಂತರ_2) {
                n = ಒಟ್ಟು_ಬೈಟುಗಳು - ಸ್ಥಾನಾಂತರ_2;
            }

            ಆದರೆ (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                ಆದರೆ (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            ಆಗ (written < n) {
                Uint32 chunk = n - written;
                ಆದರೆ (chunk > ಗಾತ್ರ(zero_buf)) {
                    chunk = ಗಾತ್ರ(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_ತಳ + off_ಒಳ_win + written);
                written += chunk;
            }
            ಸ್ಥಾನಾಂತರ_2 += n;
        }
    }

    SDL_copyp(&ದತ್ತಾಂಶ->current_ಬಹುಲಕ, ಬಹುಲಕ);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    ಆದರೆ (!ದತ್ತಾಂಶ->banked_ಬಹುಲಕ && modedata->ಅಂಕೆ_image_ಪುಟಗಳು >= 1) {
        ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ = true;
        ದತ್ತಾಂಶ->current_ಪುಟ = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[0] = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_ಕೊನೆ = ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        ಆದರೆ (page1_ಕೊನೆ > ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2) {
            ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ = false;
            ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1] = 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(ದತ್ತಾಂಶ->mapping.ವಿಳಾಸ) + ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ = false;
        ದತ್ತಾಂಶ->current_ಪುಟ = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[0] = 0;
        ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[1] = 0;
    }

    ಆದರೆ (SDL_GetMouse()->ಆಂತರಿಕ != ಖಾಲಿ) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ಬಹುಲಕ->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ಬಹುಲಕ->h - 1);
        __dpmi_int(0x33, &regs);
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_DOSVESA
