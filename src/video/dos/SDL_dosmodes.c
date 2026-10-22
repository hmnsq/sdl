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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DOSVESA

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosframebuffer_c.h"

// DOS declarations
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/movedata.h> // for dosmemput (banked framebuffer access)

// Some VESA usage information:
//   https://delorie.com/djgpp/doc/ug/graphics/vesa.html.en
//   https://delorie.com/djgpp/doc/ug/graphics/vbe20.html
//   https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
//   https://wiki.osdev.org/VESA_Video_Modes
//   https://www.phatcode.net/res/221/files/vbe20.pdf

// VBE mode attribute bits (ModeAttributes field)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODEATTR_SUPPORTED 0x01 // bit 0: mode supported in hardware
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODEATTR_COLOR     0x08 // bit 3: color mode (vs. monochrome)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODEATTR_GRAPHICS  0x10 // bit 4: graphics mode (vs. text)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODEATTR_LFB       0x80 // bit 7: linear framebuffer available

// Minimum required mode attributes for usable graphics modes
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODEATTR_REQUIRED (VBE_MODEATTR_SUPPORTED | VBE_MODEATTR_COLOR | VBE_MODEATTR_GRAPHICS)

// VBE memory model types (MemoryModel field)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MEMMODEL_PACKED_PIXEL 4 // packed pixel (includes 8-bit indexed)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MEMMODEL_ਸਿੱਧਾ_COLOR 6 // direct color (RGB with masks)

// VBE set-mode flag
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_SETMODE_LFB 0x4000 // request linear framebuffer when setting mode

// VBE mode list sentinel
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_MODELIST_ਸਿਰਾ 0xFFFF

// VGA mode 13h (320x200x256) is universally supported, but most VESA
// BIOSes do not include it in their VESA mode list. This sentinel
// value is used to identify the legacy fallback.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_ਬਹੁਲਕ_13_H_SENTINEL 0xFFEE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_ਬਹੁਲਕ_13_H_SEGMENT  0xA000

#ਹਦਾਇਤ pack(ਧੱਕੋ, 1)
// this is the struct from the hardware; we save only a few parts from this, later, in SDL_VESAInfo.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_VESAHardwareInfo
{
    Uint8 VESASignature[4];
    Uint16 VESAVersion;
    Uint32 OEMStringPtr; // segment:offset
    Uint8 Capabilities[4];
    Uint32 Video_ਬਹੁਲਕ_Ptr; // segment:offset
    Uint16 ਕੁੱਲ_ਸਮ੍ਰਿਤੀ;
    Uint16 OEMSoftwareRev;
    Uint32 OEMVendorNamePtr;  // segment:offset
    Uint32 OEMProductNamePtr; // segment:offset
    Uint32 OEMProductRevPtr;  // segment:offset
    Uint8 Reserved[222];
    Uint8 Oem_ਅੰਕੜੇ[256];
} SDL_VESAHardwareInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_VESAModeHardwareInfo
{
    Uint16 ਬਹੁਲਕ_ਗੁਣ;
    Uint8 WinAAttributes;
    Uint8 WinBAttributes;
    Uint16 WinGranularity;
    Uint16 Win_ਮਾਪ;
    Uint16 WinASegment;
    Uint16 WinBSegment;
    Uint32 WinFuncPtr;
    Uint16 ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਜਾਂਚ_ਸਤਰ;
    Uint16 XResolution;
    Uint16 YResolution;
    Uint8 XChar_ਮਾਪ;
    Uint8 YChar_ਮਾਪ;
    Uint8 ਸੰਖਿਆ_ਦਾ_Planes;
    Uint8 ਬਿੱਟ_ਪ੍ਰਤੀ_Pixel;
    Uint8 ਸੰਖਿਆ_ਦਾ_Banks;
    Uint8 ਸਮ੍ਰਿਤੀ_Model;
    Uint8 Bank_ਮਾਪ;
    Uint8 ਸੰਖਿਆ_ਦਾ_Image_ਪੰਨੇ;
    Uint8 Reserved_ਪੰਨਾ;
    Uint8 Red_ਨਕਾਬ_ਮਾਪ;
    Uint8 Red_ਨਕਾਬ_Pos;
    Uint8 Green_ਨਕਾਬ_ਮਾਪ;
    Uint8 Green_ਨਕਾਬ_Pos;
    Uint8 Blue_ਨਕਾਬ_ਮਾਪ;
    Uint8 Blue_ਨਕਾਬ_Pos;
    Uint8 Reserved_ਨਕਾਬ_ਮਾਪ;
    Uint8 Reserved_ਨਕਾਬ_Pos;
    Uint8 ਸਿੱਧਾ_Color_ਬਹੁਲਕ_Info;
    Uint32 Phys_ਅਧਾਰ_Ptr;
    Uint32 Off_Screen_Mem_ਵਿੱਥ;
    Uint16 Off_Screen_Mem_ਮਾਪ;
    Uint8 Reserved[206];
} SDL_VESAModeHardwareInfo;
#ਹਦਾਇਤ pack(ਕੱਢੋ)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_VESAInfo
{
    Uint16 ਸੰਸਕਰਣ;              // 0x200 == 2.0, etc.
    Uint32 ਕੁੱਲ_ਸਮ੍ਰਿਤੀ_2;         // in bytes (SDL_VESAHardwareInfo::TotalMemory does it in 64k pages).
    Uint32 video_addr_segoffset; // real mode segment:offset (only valid while VBE info block is allocated!)
    Uint16 *ਬਹੁਲਕ_list;           // copied out of conventional memory before freeing
    ਪੂਰਨ ਅੰਕ_modes;
    Uint16 oem_software_revision;
    ਅੱਖਰ *oem_string;
    ਅੱਖਰ *oem_vendor;
    ਅੱਖਰ *oem_ਗੁਣਨਫਲ;
    ਅੱਖਰ *oem_revision;
} SDL_VESAInfo;

ਸਥਿਰ SDL_VESAInfo *vesa_info = ਨਿਰਾ;

ਖਾਲੀ DOSVESA_FreeVESAInfo(ਖਾਲੀ)
{
    ਜੇ (vesa_info) {
        SDL_free(vesa_info->ਬਹੁਲਕ_list);
        SDL_free(vesa_info->oem_string);
        SDL_free(vesa_info->oem_vendor);
        SDL_free(vesa_info->oem_ਗੁਣਨਫਲ);
        SDL_free(vesa_info->oem_revision);
        SDL_free(vesa_info);
        vesa_info = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਅਚਲ SDL_VESAInfo *GetVESAInfo(ਖਾਲੀ)
{
    ਜੇ (vesa_info) {
        ਵਾਪਸ vesa_info;
    }

    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAHardwareInfo *hwinfo = (SDL_VESAHardwareInfo *)DOS_Allocate_Conventional_ਸਮ੍ਰਿਤੀ(ਆਕਾਰ(*hwinfo), &hwinfo_seginfo);
    ਜੇ (!hwinfo) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_zerop(hwinfo);
    SDL_memcpy(hwinfo->VESASignature, "VBE2", 4);

    __dpmi_regs regs;
    regs.x.ax = 0x4F00;
    regs.x.es = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(hwinfo) / 16;
    regs.x.di = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(hwinfo) & 0xF;
    __dpmi_int(0x10, &regs);

    // al is 0x4F if VESA is supported, ah is 0x00 if this specific call succeeded.
    // If the interrupt call didn't replace VESASignature with "VESA" then something went wrong, too.
    ਜੇ ((regs.x.ax != 0x004F) || (SDL_memcmp(hwinfo->VESASignature, "VESA", 4) != 0)) {
        SDL_ਸੈੱਟ_Error("VESA video not supported on this system");
    } ਨਹੀਂਤਾਂ {
        vesa_info = (SDL_VESAInfo *)SDL_calloc(1, ਆਕਾਰ(*vesa_info));
        ਜੇ (vesa_info) {
            vesa_info->ਸੰਸਕਰਣ = hwinfo->VESAVersion;
            vesa_info->ਕੁੱਲ_ਸਮ੍ਰਿਤੀ_2 = ((Uint32)hwinfo->ਕੁੱਲ_ਸਮ੍ਰਿਤੀ) * (64 * 1024); // TotalMemory is 64k chunks, convert to bytes.
            vesa_info->video_addr_segoffset = hwinfo->Video_ਬਹੁਲਕ_Ptr;
            vesa_info->oem_software_revision = hwinfo->OEMSoftwareRev;
            // these strings are often empty (or maybe NULL), but it's fine. We don't _actually_ need them.
            vesa_info->oem_string = DOS_GetFarPtrCString(hwinfo->OEMStringPtr);
            vesa_info->oem_vendor = DOS_GetFarPtrCString(hwinfo->OEMVendorNamePtr);
            vesa_info->oem_ਗੁਣਨਫਲ = DOS_GetFarPtrCString(hwinfo->OEMProductNamePtr);
            vesa_info->oem_revision = DOS_GetFarPtrCString(hwinfo->OEMProductRevPtr);

            // Copy the mode list out of conventional memory BEFORE freeing
            // the VBE info block. Some VESA BIOSes store the mode list
            // inside the 512-byte info block itself. If we free the block
            // first, the mode list pointer becomes dangling and we read
            // garbage, silently losing modes.
            {
                Uint32 segoffset = vesa_info->video_addr_segoffset;
                ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
                ਜਦੋਂ (DOS_PeekUint16(segoffset + ਗਿਣਤੀ_2 * ਆਕਾਰ(Uint16)) != VBE_MODELIST_ਸਿਰਾ) {
                    ਗਿਣਤੀ_2++;
                    ਜੇ (ਗਿਣਤੀ_2 > 64)
                        ਰੋਕੋ; // sanity limit
                }
                vesa_info->ਅੰਕ_modes = ਗਿਣਤੀ_2;
                vesa_info->ਬਹੁਲਕ_list = (Uint16 *)SDL_malloc(ਗਿਣਤੀ_2 * ਆਕਾਰ(Uint16));
                ਜੇ (vesa_info->ਬਹੁਲਕ_list) {
                    ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; i++) {
                        vesa_info->ਬਹੁਲਕ_list[i] = DOS_PeekUint16(segoffset + i * ਆਕਾਰ(Uint16));
                    }
                } ਨਹੀਂਤਾਂ {
                    vesa_info->ਅੰਕ_modes = 0;
                }
            }
        }
    }

    DOS_Free_Conventional_ਸਮ੍ਰਿਤੀ(&hwinfo_seginfo);

    ਵਾਪਸ vesa_info;
}

// Check for VGA using BIOS function GET DISPLAY COMBINATION CODE.
// Call INT 0x10 with AX=0x1A00; function is supported if AL=0x1A.
// Returns true for VGA-compatible hardware. 
ਸਥਿਰ bool DetectVGA(ਖਾਲੀ)
{
    __dpmi_regs regs = {};
    regs.x.ax = 0x1A00;
    __dpmi_int(0x10, &regs);
    ਵਾਪਸ ((regs.x.ax & 0x00FF) == 0x001A);
}

bool DOSVESA_SupportsVESA(ਖਾਲੀ)
{
    // We need at least VGA hardware (for mode 13h). EGA and CGA cards
    // do not support 256 colors or programmable palettes.
    ਜੇ (!DetectVGA()) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No VGA card detected");
    }

    // Cache VESA info if available (NULL mean we only have VGA).
    (ਖਾਲੀ)GetVESAInfo();

    ਵਾਪਸ true;
}

ਅਚਲ ਅੱਖਰ *DOSVESA_GetGPUName(ਖਾਲੀ)
{
    ਅਚਲ SDL_VESAInfo *vinfo = GetVESAInfo();
    ਜੇ (!vinfo) {
        ਵਾਪਸ "VGA";
    }

    ਜੇ (vinfo->oem_ਗੁਣਨਫਲ && *vinfo->oem_ਗੁਣਨਫਲ) {
        ਵਾਪਸ vinfo->oem_ਗੁਣਨਫਲ;
    }
    ਜੇ (vinfo->oem_vendor && *vinfo->oem_vendor) {
        ਵਾਪਸ vinfo->oem_vendor;
    }
    ਜੇ (vinfo->oem_string && *vinfo->oem_string) {
        ਵਾਪਸ vinfo->oem_string;
    }

    ਵਾਪਸ "VESA";
}

Uint32 DOSVESA_Get_VESATotal_ਸਮ੍ਰਿਤੀ(ਖਾਲੀ)
{
    ਅਚਲ SDL_VESAInfo *info = GetVESAInfo();
    ਵਾਪਸ info ? info->ਕੁੱਲ_ਸਮ੍ਰਿਤੀ_2 : 0;
}

ਸਥਿਰ bool GetVESAModeInfo(Uint16 ਬਹੁਲਕ_id, SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *info)
{
    _go32_dpmi_seginfo hwinfo_seginfo;
    SDL_VESAModeHardwareInfo *hwinfo = (SDL_VESAModeHardwareInfo *)DOS_Allocate_Conventional_ਸਮ੍ਰਿਤੀ(ਆਕਾਰ(*hwinfo), &hwinfo_seginfo);
    ਜੇ (!hwinfo) {
        ਵਾਪਸ false;
    }

    SDL_zerop(hwinfo);

    __dpmi_regs regs;
    regs.x.ax = 0x4F01;
    regs.x.es = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(hwinfo) / 16;
    regs.x.di = DOS_ਰੇਖਿਕ_ਮੰਜ਼ਿਲ_Physical(hwinfo) & 0xF;
    regs.x.cx = ਬਹੁਲਕ_id;
    __dpmi_int(0x10, &regs);

    ਅਚਲ bool retval = (regs.x.ax == 0x004F);
    ਜੇ (retval) {
        SDL_zerop(info);
        info->ਬਹੁਲਕ_id = ਬਹੁਲਕ_id;
        info->ਗੁਣ = hwinfo->ਬਹੁਲਕ_ਗੁਣ;
        info->pitch = hwinfo->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਜਾਂਚ_ਸਤਰ;
        info->w = hwinfo->XResolution;
        info->h = hwinfo->YResolution;
        info->ਅੰਕ_planes = hwinfo->ਸੰਖਿਆ_ਦਾ_Planes;
        info->bpp = hwinfo->ਬਿੱਟ_ਪ੍ਰਤੀ_Pixel;
        info->ਸਮ੍ਰਿਤੀ_model = hwinfo->ਸਮ੍ਰਿਤੀ_Model;
        info->ਅੰਕ_image_ਪੰਨੇ = hwinfo->ਸੰਖਿਆ_ਦਾ_Image_ਪੰਨੇ;
        info->red_ਨਕਾਬ_ਮਾਪ = hwinfo->Red_ਨਕਾਬ_ਮਾਪ;
        info->red_ਨਕਾਬ_pos = hwinfo->Red_ਨਕਾਬ_Pos;
        info->green_ਨਕਾਬ_ਮਾਪ = hwinfo->Green_ਨਕਾਬ_ਮਾਪ;
        info->green_ਨਕਾਬ_pos = hwinfo->Green_ਨਕਾਬ_Pos;
        info->blue_ਨਕਾਬ_ਮਾਪ = hwinfo->Blue_ਨਕਾਬ_ਮਾਪ;
        info->blue_ਨਕਾਬ_pos = hwinfo->Blue_ਨਕਾਬ_Pos;
        info->physical_ਅਧਾਰ_addr = hwinfo->Phys_ਅਧਾਰ_Ptr;

        // VBE 1.2 banked framebuffer fields
        info->has_lfb = (hwinfo->ਬਹੁਲਕ_ਗੁਣ & VBE_MODEATTR_LFB) != 0;
        info->win_granularity = hwinfo->WinGranularity;
        info->win_ਮਾਪ = hwinfo->Win_ਮਾਪ;
        info->win_a_segment = hwinfo->WinASegment;
        info->win_func_ptr = hwinfo->WinFuncPtr;
        info->win_a_ਗੁਣ = hwinfo->WinAAttributes;
    }

    DOS_Free_Conventional_ਸਮ੍ਰਿਤੀ(&hwinfo_seginfo);

    ਵਾਪਸ retval;
}

bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display)
{
    ਅਚਲ SDL_VESAInfo *vinfo = GetVESAInfo();

    // Enumerate VESA modes if we have a VBE 1.2+ BIOS.  Older VBE versions
    // (1.0, 1.1) or no VESA at all just skip this loop and fall through to
    // the VGA mode 13h fallback below.
    ਪੂਰਨ ਅੰਕ_vesa_modes = (vinfo && vinfo->ਸੰਸਕਰਣ >= 0x102) ? vinfo->ਅੰਕ_modes : 0;

    ਲਈ (ਪੂਰਨ mi = 0; mi < ਅੰਕ_vesa_modes; mi++) {
        ਅਚਲ Uint16 modeid = vinfo->ਬਹੁਲਕ_list[mi];

        SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ info;
        ਜੇ (!GetVESAModeInfo(modeid, &info)) {
            ਜਾਰੀ;
        }

        // Skip 320x200x8 from VESA. We always want VGA mode 13h for this
        // resolution (no page flip, no LFB overhead, universal compatibility).
        ਜੇ (info.bpp == 8 && info.w == 320 && info.h == 200) {
            ਜਾਰੀ;
        }

        ਜੇ ((info.ਗੁਣ & VBE_MODEATTR_REQUIRED) != VBE_MODEATTR_REQUIRED) {
            ਜਾਰੀ;
        }

        ਜੇ (!(info.ਗੁਣ & VBE_MODEATTR_LFB) && (info.win_a_ਗੁਣ & VBE_WINATTR_USABLE) != VBE_WINATTR_USABLE) {
            ਜਾਰੀ;
        }

        ਜੇ (info.ਅੰਕ_planes != 1) {
            ਜਾਰੀ; // skip planar pixel layouts.
        } ਨਹੀਂਤਾਂ ਜੇ (info.bpp < 8) {
            ਜਾਰੀ; // skip anything below 8-bit.
        } ਨਹੀਂਤਾਂ ਜੇ (!info.w || !info.h) {
            ਜਾਰੀ; // zero-area display mode?!
        } ਨਹੀਂਤਾਂ ਜੇ (!info.has_lfb && !info.win_granularity) {
            ਜਾਰੀ; // banked mode with zero granularity would cause division by zero.
        } ਨਹੀਂਤਾਂ ਜੇ ((info.ਸਮ੍ਰਿਤੀ_model != VBE_MEMMODEL_PACKED_PIXEL) && (info.ਸਮ੍ਰਿਤੀ_model != VBE_MEMMODEL_ਸਿੱਧਾ_COLOR)) {
            ਜਾਰੀ; // must be either packed pixel or Direct Color.
            // Note: 8-bit indexed modes are packed pixel.
        }

        SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
        ਜੇ (info.ਸਮ੍ਰਿਤੀ_model == VBE_MEMMODEL_PACKED_PIXEL) {
            ਚੋਣ (info.bpp) {
            ਹਾਲਤ 8:
                format = SDL_PIXELFORMAT_INDEX8;
                ਰੋਕੋ;
            ਹਾਲਤ 15:
                format = SDL_PIXELFORMAT_XRGB1555;
                ਰੋਕੋ;
            ਹਾਲਤ 16:
                format = SDL_PIXELFORMAT_RGB565;
                ਰੋਕੋ;
            ਹਾਲਤ 24:
                format = SDL_PIXELFORMAT_RGB24;
                ਰੋਕੋ;
            ਹਾਲਤ 32:
                format = SDL_PIXELFORMAT_XRGB8888;
                ਰੋਕੋ;
            ਮੂਲ:
                ਰੋਕੋ;
            }
        } ਨਹੀਂਤਾਂ {
            SDL_assert(info.ਸਮ੍ਰਿਤੀ_model == VBE_MEMMODEL_ਸਿੱਧਾ_COLOR);
            ਅਚਲ Uint32 rmask = ((((Uint32)1) << info.red_ਨਕਾਬ_ਮਾਪ) - 1) << info.red_ਨਕਾਬ_pos;
            ਅਚਲ Uint32 gmask = ((((Uint32)1) << info.green_ਨਕਾਬ_ਮਾਪ) - 1) << info.green_ਨਕਾਬ_pos;
            ਅਚਲ Uint32 bmask = ((((Uint32)1) << info.blue_ਨਕਾਬ_ਮਾਪ) - 1) << info.blue_ਨਕਾਬ_pos;
            format = SDL_GetPixelFormatForMasks(info.bpp, rmask, gmask, bmask, 0x00000000);
        }

        ਜੇ (format == SDL_PIXELFORMAT_UNKNOWN) {
            ਜਾਰੀ; // don't know what to do with this one.
        }

        SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_malloc(ਆਕਾਰ(*ਅੰਦਰੂਨੀ));
        ਜੇ (!ਅੰਦਰੂਨੀ) {
            ਜਾਰੀ; // oof.
        }

        SDL_copyp(ਅੰਦਰੂਨੀ, &info);

        SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
        SDL_zero(ਬਹੁਲਕ);
        ਬਹੁਲਕ.format = format;
        ਬਹੁਲਕ.w = (ਪੂਰਨ)info.w;
        ਬਹੁਲਕ.h = (ਪੂਰਨ)info.h;
        ਬਹੁਲਕ.pixel_density = 1.0f; // no HighDPI scaling here.

        // !!! FIXME: we need to parse EDID data (VESA function 0x4F15, subfunction 0x01) to get refresh rates. Leaving as 0 for now.
        // float refresh_rate;             /**< refresh rate (or 0.0f for unspecified) */
        // int refresh_rate_numerator;     /**< precise refresh rate numerator (or 0 for unspecified) */
        // int refresh_rate_denominator;   /**< precise refresh rate denominator */

        ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = ਅੰਦਰੂਨੀ;

        ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(sdl_display, &ਬਹੁਲਕ)) {
            SDL_free(ਅੰਦਰੂਨੀ); // oh well, carry on without it.
        }
    }

    // Always add VGA mode 13h for 320x200x8. We skipped any VESA 320x200x8
    // modes above so this is the only entry at that resolution.
    {
        SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_malloc(ਆਕਾਰ(*ਅੰਦਰੂਨੀ));
        ਜੇ (ਅੰਦਰੂਨੀ) {
            SDL_zerop(ਅੰਦਰੂਨੀ);
            ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_id = VGA_ਬਹੁਲਕ_13_H_SENTINEL;
            ਅੰਦਰੂਨੀ->ਗੁਣ = VBE_MODEATTR_REQUIRED;
            ਅੰਦਰੂਨੀ->pitch = 320;
            ਅੰਦਰੂਨੀ->w = 320;
            ਅੰਦਰੂਨੀ->h = 200;
            ਅੰਦਰੂਨੀ->ਅੰਕ_planes = 1;
            ਅੰਦਰੂਨੀ->bpp = 8;
            ਅੰਦਰੂਨੀ->ਸਮ੍ਰਿਤੀ_model = VBE_MEMMODEL_PACKED_PIXEL;
            ਅੰਦਰੂਨੀ->ਅੰਕ_image_ਪੰਨੇ = 0; // no page flipping in mode 13h
            ਅੰਦਰੂਨੀ->physical_ਅਧਾਰ_addr = 0;
            ਅੰਦਰੂਨੀ->has_lfb = false;
            ਅੰਦਰੂਨੀ->win_granularity = 64;
            ਅੰਦਰੂਨੀ->win_ਮਾਪ = 64;
            ਅੰਦਰੂਨੀ->win_a_segment = VGA_ਬਹੁਲਕ_13_H_SEGMENT;
            ਅੰਦਰੂਨੀ->win_func_ptr = 0;
            ਅੰਦਰੂਨੀ->win_a_ਗੁਣ = VBE_WINATTR_USABLE;

            SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
            SDL_zero(ਬਹੁਲਕ);
            ਬਹੁਲਕ.format = SDL_PIXELFORMAT_INDEX8;
            ਬਹੁਲਕ.w = 320;
            ਬਹੁਲਕ.h = 200;
            ਬਹੁਲਕ.pixel_density = 1.0f;
            ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = ਅੰਦਰੂਨੀ;

            ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(sdl_display, &ਬਹੁਲਕ)) {
                SDL_free(ਅੰਦਰੂਨੀ);
            }
        }
    }

    // Sort modes descending: largest to smallest (by width first, then height, then bpp).
    ਲਈ (ਪੂਰਨ i = 0; i < sdl_display->ਅੰਕ_fullscreen_modes - 1; i++) {
        ਲਈ (ਪੂਰਨ j = i + 1; j < sdl_display->ਅੰਕ_fullscreen_modes; j++) {
            ਅਚਲ SDL_Display_ਬਹੁਲਕ *a = &sdl_display->fullscreen_modes[i];
            ਅਚਲ SDL_Display_ਬਹੁਲਕ *b = &sdl_display->fullscreen_modes[j];
            bool ਅਦਲਾ_ਬਦਲੀ = false;
            ਜੇ (b->w > a->w) {
                ਅਦਲਾ_ਬਦਲੀ = true;
            } ਨਹੀਂਤਾਂ ਜੇ (b->w == a->w) {
                ਜੇ (b->h > a->h) {
                    ਅਦਲਾ_ਬਦਲੀ = true;
                } ਨਹੀਂਤਾਂ ਜੇ (b->h == a->h) {
                    ਜੇ (SDL_BITSPERPIXEL(b->format) > SDL_BITSPERPIXEL(a->format)) {
                        ਅਦਲਾ_ਬਦਲੀ = true;
                    }
                }
            }
            ਜੇ (ਅਦਲਾ_ਬਦਲੀ) {
                SDL_Display_ਬਹੁਲਕ tmp = sdl_display->fullscreen_modes[i];
                sdl_display->fullscreen_modes[i] = sdl_display->fullscreen_modes[j];
                sdl_display->fullscreen_modes[j] = tmp;
            }
        }
    }

    ਵਾਪਸ true;
}

bool DOSVESA_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->current_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ && (ਅੰਕੜੇ->current_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ->ਬਹੁਲਕ_id == modedata->ਬਹੁਲਕ_id)) {
        ਵਾਪਸ true;
    }

    DOSVESA_InvalidateCachedFramebuffer();

    ਜੇ (ਅੰਕੜੇ->mapping.ਮਾਪ) {
        __dpmi_free_physical_address_mapping(&ਅੰਕੜੇ->mapping); // dump existing video mapping.
        SDL_zero(ਅੰਕੜੇ->mapping);
    }

    __dpmi_regs regs;

    ਜੇ (modedata->ਬਹੁਲਕ_id == VGA_ਬਹੁਲਕ_13_H_SENTINEL) {
        // Set VGA mode 13h (320x200x256) via legacy BIOS call.
        SDL_zero(regs);
        regs.x.ax = 0x0013;
        __dpmi_int(0x10, &regs);
        // Mode 13h always succeeds on VGA hardware; no status to check.

        ਅੰਕੜੇ->banked_ਬਹੁਲਕ = true; // uses A000:0000 segment, no LFB

        SDL_copyp(&ਅੰਕੜੇ->current_ਬਹੁਲਕ, ਬਹੁਲਕ);

        ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ = false;
        ਅੰਕੜੇ->current_ਪੰਨਾ = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[0] = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1] = 0;

        // Clear the framebuffer
        {
            Uint8 zero_buf[320];
            SDL_zeroa(zero_buf);
            Uint32 vga_ਅਧਾਰ = (Uint32)VGA_ਬਹੁਲਕ_13_H_SEGMENT << 4;
            ਲਈ (ਪੂਰਨ ਪੰਕਤੀ = 0; ਪੰਕਤੀ < 200; ਪੰਕਤੀ++) {
                dosmemput(zero_buf, 320, vga_ਅਧਾਰ + ਪੰਕਤੀ * 320);
            }
        }

        ਜੇ (SDL_GetMouse()->ਅੰਦਰੂਨੀ != ਨਿਰਾ) {
            regs.x.ax = 0x7;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ਬਹੁਲਕ->w - 1);
            __dpmi_int(0x33, &regs);

            regs.x.ax = 0x8;
            regs.x.cx = 0;
            regs.x.dx = (Uint16)(ਬਹੁਲਕ->h - 1);
            __dpmi_int(0x33, &regs);
        }

        ਵਾਪਸ true;
    }

    // When the direct-FB hint is active, prefer banked mode. This needs
    // to be set explicitly for some cards (Intel 740).
    ਅਚਲ bool is_banked_usable = modedata->win_a_segment &&
                                  modedata->win_ਮਾਪ > 0 &&
                                  (modedata->win_a_ਗੁਣ & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE;
    ਅਚਲ bool use_lfb = modedata->has_lfb &&
                         (!is_banked_usable || !SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_ਸਿੱਧਾ_FRAMEBUFFER, false));

    regs.x.ax = 0x4F02;
    regs.x.bx = modedata->ਬਹੁਲਕ_id | (use_lfb ? VBE_SETMODE_LFB : 0);
    __dpmi_int(0x10, &regs);

    ਜੇ (regs.x.ax != 0x004F) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to set VESA video mode");
    }

    ਅੰਕੜੇ->banked_ਬਹੁਲਕ = !use_lfb;

    ਜੇ (use_lfb) {
        ਅੰਕੜੇ->mapping.ਪਤਾ = modedata->physical_ਅਧਾਰ_addr;
        ਅੰਕੜੇ->mapping.ਮਾਪ = DOSVESA_Get_VESATotal_ਸਮ੍ਰਿਤੀ();
        ਜੇ (__dpmi_physical_address_mapping(&ਅੰਕੜੇ->mapping) != 0) {
            SDL_zero(ਅੰਕੜੇ->mapping);
            regs.x.ax = 0x03; // try to dump us back into text mode. Not sure if this is a good idea, though.
            __dpmi_int(0x10, &regs);
            SDL_zero(ਅੰਕੜੇ->current_ਬਹੁਲਕ);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to map VESA video memory");
        }

        // make sure framebuffer is blanked out.
        SDL_memset(DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(ਅੰਕੜੇ->mapping.ਪਤਾ), '\0', (Uint32)modedata->h * (Uint32)modedata->pitch);
    } ਨਹੀਂਤਾਂ {
        // Banked mode: no physical address mapping needed.
        // Blank the visible framebuffer through the banked window.
        Uint32 ਕੁੱਲ_ਬਾਈਟਾਂ = (Uint32)modedata->h * (Uint32)modedata->pitch;
        Uint32 win_gran_ਬਾਈਟਾਂ = (Uint32)modedata->win_granularity * 1024;
        Uint32 win_ਮਾਪ_ਬਾਈਟਾਂ = (Uint32)modedata->win_ਮਾਪ * 1024;
        Uint32 win_ਅਧਾਰ = (Uint32)modedata->win_a_segment << 4;
        Uint8 zero_buf[1024];
        SDL_zeroa(zero_buf);

        Uint32 ਵਿੱਥ_2 = 0;
        ਪੂਰਨ current_bank = -1;
        ਜਦੋਂ (ਵਿੱਥ_2 < ਕੁੱਲ_ਬਾਈਟਾਂ) {
            ਪੂਰਨ bank = (ਪੂਰਨ)(ਵਿੱਥ_2 / win_gran_ਬਾਈਟਾਂ);
            Uint32 off_ਵਿੱਚ_win = ਵਿੱਥ_2 % win_gran_ਬਾਈਟਾਂ;
            Uint32 n = win_ਮਾਪ_ਬਾਈਟਾਂ - off_ਵਿੱਚ_win;
            ਜੇ (n > ਕੁੱਲ_ਬਾਈਟਾਂ - ਵਿੱਥ_2) {
                n = ਕੁੱਲ_ਬਾਈਟਾਂ - ਵਿੱਥ_2;
            }

            ਜੇ (bank != current_bank) {
                __dpmi_regs bregs;
                SDL_zero(bregs);
                bregs.x.bx = 0; // Window A
                bregs.x.dx = (Uint16)bank;
                ਜੇ (modedata->win_func_ptr) {
                    // Call WinFuncPtr directly — faster than INT 10h.
                    bregs.x.cs = (Uint16)(modedata->win_func_ptr >> 16);
                    bregs.x.ip = (Uint16)(modedata->win_func_ptr & 0xFFFF);
                    __dpmi_simulate_real_mode_procedure_retf(&bregs);
                } ਨਹੀਂਤਾਂ {
                    bregs.x.ax = 0x4F05;
                    __dpmi_int(0x10, &bregs);
                }
                current_bank = bank;
            }

            // Zero in 1KB chunks via dosmemput
            Uint32 written = 0;
            ਜਦੋਂ (written < n) {
                Uint32 chunk = n - written;
                ਜੇ (chunk > ਆਕਾਰ(zero_buf)) {
                    chunk = ਆਕਾਰ(zero_buf);
                }
                dosmemput(zero_buf, chunk, win_ਅਧਾਰ + off_ਵਿੱਚ_win + written);
                written += chunk;
            }
            ਵਿੱਥ_2 += n;
        }
    }

    SDL_copyp(&ਅੰਕੜੇ->current_ਬਹੁਲਕ, ਬਹੁਲਕ);

    // Set up page-flipping if the mode has at least 1 image page (meaning 2 total)
    // Note: page-flipping is only supported with LFB modes. With banked modes,
    // we would still need to bank-switch through the same 64KB window to write
    // to the back page, so the performance benefit is minimal (just tear-free).
    // For simplicity, disable page-flipping in banked mode for now.
    ਜੇ (!ਅੰਕੜੇ->banked_ਬਹੁਲਕ && modedata->ਅੰਕ_image_ਪੰਨੇ >= 1) {
        ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ = true;
        ਅੰਕੜੇ->current_ਪੰਨਾ = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[0] = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1] = (Uint32)modedata->pitch * (Uint32)modedata->h;

        // Check that both pages fit within the mapped region.
        Uint32 page1_ਸਿਰਾ = ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1] + (Uint32)modedata->pitch * (Uint32)modedata->h;
        ਜੇ (page1_ਸਿਰਾ > ਅੰਕੜੇ->mapping.ਮਾਪ) {
            ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ = false;
            ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1] = 0;
        } ਨਹੀਂਤਾਂ {
            // Also blank the second page
            SDL_memset((Uint8 *)DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(ਅੰਕੜੇ->mapping.ਪਤਾ) + ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1],
                       '\0', (Uint32)modedata->pitch * (Uint32)modedata->h);

            // Start display at page 0
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0000; // set display start, wait for retrace
            regs.x.cx = 0;      // first pixel in scan line
            regs.x.dx = 0;      // first scan line
            __dpmi_int(0x10, &regs);
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ = false;
        ਅੰਕੜੇ->current_ਪੰਨਾ = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[0] = 0;
        ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[1] = 0;
    }

    ਜੇ (SDL_GetMouse()->ਅੰਦਰੂਨੀ != ਨਿਰਾ) { // internal != NULL) == int 33h services available.
        regs.x.ax = 0x7;                    // set mouse min/max horizontal position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ਬਹੁਲਕ->w - 1);
        __dpmi_int(0x33, &regs);

        regs.x.ax = 0x8; // set mouse min/max vertical position.
        regs.x.cx = 0;
        regs.x.dx = (Uint16)(ਬਹੁਲਕ->h - 1);
        __dpmi_int(0x33, &regs);
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DOSVESA
